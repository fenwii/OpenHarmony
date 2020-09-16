/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fatfs.h"

#ifdef LOSCFG_FS_FAT
#include <string.h>
#include <sys/mount.h>

#include "errno.h"
#include "ff.h"
#include "dirop_fat.h"
#include "disk_pri.h"
#include "los_tables.h"

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
#include "virpart.h"
#include "errcode_fat.h"
#include "virpartff.h"
#endif

#ifdef LOSCFG_FS_FAT_CACHE
#include "bcache.h"
#endif

#include "los_config.h"
#include "los_vm_filemap.h"
#include "los_process_pri.h"
#include "capability_type.h"
#include "capability_api.h"
#include "fs_other.h"
#include "los_strncpy_from_user.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
FAT_VIR_PART g_fatVirPart = {0};
static pthread_mutex_t fatfsVirtMutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
static void FatfsVirtLock(void)
{
    (void)pthread_mutex_lock(&fatfsVirtMutex);
}
static void FatfsVirtUnlock(void)
{
    (void)pthread_mutex_unlock(&fatfsVirtMutex);
}
#endif

PARTITION VolToPart[FF_VOLUMES];
static struct inode *DiskDev[FF_VOLUMES];
char FatLabel[LABEL_LEN];

#define DRIVER_NAME_LEN    8

/* Returns -1 if there is no space to install fatfs driver, else returns >=0 */
static INT FatGetDisk(struct inode *node)
{
    INT index;

    for (index = 0; index < FF_VOLUMES; index++) {
        if (DiskDev[index] == node) {
            return index;
        }
    }

    return FAT_ERROR;
}

static INT FatfsSdSync(unsigned long mountflags, FATFS *fat)
{
#ifdef LOSCFG_FS_FAT_CACHE
    los_part *part = NULL;
    if (mountflags != MS_NOSYNC) {
        part = get_part((INT)fat->pdrv);
        if (part == NULL) {
            return -ENODEV;
        }

        (void)OsSdSync(part->disk_id);
    }
#endif
    return ENOERR;
}

INT fatfs_2_vfs(INT result)
{
    INT status = ENOERR;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
    if (result < 0 || result >= VIRERR_BASE) {
        return result;
    }
#else
    if (result < 0) {
        return result;
    }
#endif

    /* FatFs errno to Libc errno */
    switch (result) {
        case FR_OK:
            break;

        case FR_NO_FILE:
        case FR_NO_PATH:
        case FR_NO_FILESYSTEM:
            status = -ENOENT;
            break;

        case FR_INVALID_NAME:
            status = -EINVAL;
            break;

        case FR_EXIST:
        case FR_INVALID_OBJECT:
            status = -EEXIST;
            break;

        case FR_DISK_ERR:
        case FR_NOT_READY:
        case FR_INT_ERR:
            status = -EIO;
            break;

        case FR_WRITE_PROTECTED:
            status = -EROFS;
            break;
        case FR_MKFS_ABORTED:
        case FR_INVALID_PARAMETER:
            status = -EINVAL;
            break;

        case FR_NO_SPACE_LEFT:
            status = -ENOSPC;
            break;
        case FR_NO_DIRENTRY:
            status = -ENFILE;
            break;
        case FR_NO_EMPTY_DIR:
            status = -ENOTEMPTY;
            break;
        case FR_IS_DIR:
            status = -EISDIR;
            break;
        case FR_NO_DIR:
            status = -ENOTDIR;
            break;
        case FR_NO_EPERM:
        case FR_DENIED:
            status = -EPERM;
            break;
        case FR_LOCKED:
            status = -EBUSY;
            break;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
        case FR_MODIFIED:
            status = VIRERR_MODIFIED;
            break;
        case FR_CHAIN_ERR:
            status = VIRERR_CHAIN_ERR;
            break;
        case FR_OCCUPIED:
            status = VIRERR_OCCUPIED;
            break;
        case FR_NOTCLEAR:
            status = VIRERR_NOTCLEAR;
            break;
        case FR_NOTFIT:
            status = VIRERR_NOTFIT;
            break;
        case FR_INVAILD_FATFS:
            status = VIRERR_INTER_ERR;
            break;
#endif
        default:
            status = FAT_ERROR;
            break;
    }

    return status;
}

static int FatfsBindCheck(struct inode *blkdriver, los_part **partition)
{
    los_part *part = NULL;
    if (blkdriver == NULL || blkdriver->u.i_bops == NULL) {
        return -ENODEV;
    }

    if (blkdriver->u.i_bops->open != NULL && blkdriver->u.i_bops->open(blkdriver) != 0) {
        return -ENODEV;
    }

    part = los_part_find(blkdriver);
    if (part == NULL) {
        return -ENODEV;
    }

    if (part->part_name != NULL) {
        return -EACCES;
    }

#ifndef FF_MULTI_PARTITION
    if (part->part_no_mbr > 1) {
        return -EPERM;
    }
#endif

    *partition = part;
    return ENOERR;
}

struct FatfsMountOpts {
    uid_t FsUid;
    gid_t FsGid;
    unsigned short FsDmask;
    unsigned short FsFmask;
};
struct MatchOption {
    int opt;
    const char *pattern;
};
typedef struct MatchOption MatchTable[];
enum {
    OptionUid,
    OptionGid,
    OptionUmask,
    OptionDmask,
    OptionFmask,
    OptionErr,
};
static const MatchTable FatFsTokens = {
    {OptionUid, "uid=%u"},
    {OptionGid, "gid=%u"},
    {OptionUmask, "umask=%o"},
    {OptionDmask, "dmask=%o"},
    {OptionFmask, "fmask=%o"},
    {OptionErr, NULL},
};

static int MatchOption(char *s, const MatchTable table, char **args)
{
    struct MatchOption opt = {0};
    const char *p = NULL;
    char *meta = NULL;
    for (unsigned int i = 0; i < (sizeof(FatFsTokens) / sizeof(struct MatchOption)); i++) {
        opt = table[i];
        p = opt.pattern;
        if (p == NULL) {
            continue;
        }
        meta = strchr(table[i].pattern, '%');
        if ((meta == NULL) || (strncmp(p, s, meta - p) != 0)) {
            continue;
        }
        *args = s + (meta - p);
        break;
    }

    return opt.opt;
}
static void FatParseOptions(char *data, struct FatfsMountOpts *opts)
{
    char *args = NULL;
    int opt;
    char *p = NULL;

    if ((data == NULL) || (opts == NULL)) {
        return;
    }

    opts->FsUid = OsCurrUserGet()->effUserID;
    opts->FsGid = OsCurrUserGet()->effGid;
    opts->FsDmask = GetUmask();
    opts->FsFmask = GetUmask();

    while ((p = strsep((char**)&data, ",")) != NULL) {
        if (!*p)
            continue;

        opt = MatchOption(p, FatFsTokens, &args);
        if (args == NULL) {
            continue;
        }

        switch (opt) {
            case OptionUid:
                opts->FsUid = strtoul(args, NULL, 0);
                break;
            case OptionGid:
                opts->FsGid = strtoul(args, NULL, 0);
                break;
            case OptionUmask:
                opts->FsDmask = opts->FsFmask = strtoul(args, NULL, 8); /* 8: octal formats */
                break;
            case OptionDmask:
                opts->FsDmask = strtoul(args, NULL, 8); /* 8: octal formats */
                break;
            case OptionFmask:
                opts->FsFmask = strtoul(args, NULL, 8); /* 8: octal formats */
                break;
            default:
                PRINTK("Not Match\n");
                break;
        }
    }
    return;
}

int fatfs_bind(struct inode *blkdriver, const void *data, void **handle, const char *relpath)
{
    FATFS *fat = NULL;
    INT result;
    BYTE index;
    INT err;
    los_part *part = NULL;
    char drive[DRIVER_NAME_LEN];
    struct FatfsMountOpts opts = {0};
    struct inode_search_s desc;
    FAR struct inode *inode;

    FatParseOptions((char *)data, &opts);

    result = FatfsBindCheck(blkdriver, &part);
    if (result != 0)
        return result;

    err = SetDiskPartName(part, relpath);
    if (err != 0)
        return -ENOMEM;

    index = (BYTE)FatGetDisk((struct inode *)NULL);
    if (index >= FF_VOLUMES || (INT8)index < 0) {
        err = -EBUSY;
        goto ERROUT;
    }
    VolToPart[index].di = part->disk_id;
    VolToPart[index].pd = part->part_id;
    VolToPart[index].pt = part->part_no_mbr;
    VolToPart[index].ps = part->sector_start;
    VolToPart[index].pc = part->sector_count;

    fat = (FATFS *)zalloc(sizeof(FATFS));
    if (fat == NULL) {
        err = -ENOMEM;
        goto ERROUT_WITH_DISK;
    }
    result = snprintf_s(drive, sizeof(drive), sizeof(drive) - 1, "%d:/", index);
    if (result < 0) {
        err = -EINVAL;
        free(fat);
        goto ERROUT_WITH_DISK;
    }

    fat->fs_uid = opts.FsUid;
    fat->fs_gid = opts.FsGid;
    fat->fs_dmask = opts.FsDmask;
    fat->fs_fmask = opts.FsFmask;

    /* save blockdriver inode : driver will use in f_mount */
    DiskDev[index] = blkdriver;
    /* mount fatfs, mmc always 0 logic driver */
    result = f_mount(fat, drive, 1);
    if (result == FR_OK) {
        DIR *dir = NULL;

        dir = (DIR *)malloc(sizeof(DIR));
        if (dir == NULL) {
            err = -ENOMEM;
            goto ERROUT_WITH_MOUNT;
        }

#if FF_FS_MINIMIZE <= 1
        /* open the root directory, returns error if fatfs is invalid */
        result = f_opendir(dir, drive);
        if (result != FR_OK) {
            err = fatfs_2_vfs(result);
            free(dir);
            goto ERROUT_WITH_MOUNT;
        }
        result = f_closedir(dir);
        if (result != FR_OK) {
            err = fatfs_2_vfs(result);
            free(dir);
            goto ERROUT_WITH_MOUNT;
        }
#else
        PRINT_ERR("cannot open root directory to check if fatfs is invalid!\n");
#endif
        /* mount ok! */
        *handle = (void *)fat;
        free(dir);
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
        /* Parent Partition Mount Success, then process virtual partition mount operation */
        if (result == FR_OK) {
            if (fat->fs_type != FS_FAT32)
                return VIRERR_NOTFIT;
            SETUP_SEARCH(&desc, g_fatVirPart.virtualinfo.devpartpath, false);
            result = inode_find(&desc);
            if (result < 0)
                return VIRERR_NOPARAM;
            inode = desc.node;

            if (blkdriver != inode) {
                return VIRERR_NOPARAM;
            } else {
                FatfsVirtLock();
                result = FatFsBindVirPart(fat, index);
                FatfsVirtUnlock();
                if (result != FR_OK && result < VIRERR_BASE) {
                    result = VIRERR_INTER_ERR;
                }
            }
        }
#endif
        return fatfs_2_vfs(result);
    } else {
        err = fatfs_2_vfs(result);
    }
ERROUT_WITH_MOUNT:
    (void)f_mount((FATFS *)NULL, drive, 0);
    if (fat->win != NULL)
        free(fat->win);
    free(fat);

ERROUT_WITH_DISK:
    DiskDev[index] = (struct inode *)NULL;

ERROUT:
    free(part->part_name);
    part->part_name = NULL;

    return err;
}

int fatfs_unbind(void *handle, struct inode **blkdriver)
{
    BYTE index;
    FATFS *fat = NULL;
    INT result;
    los_part *part = NULL;
    char drive[DRIVER_NAME_LEN];
    struct inode_search_s desc;
    FAR struct inode *inode;

    fat = (FATFS *)handle;
    if (fat == NULL)
        return -EINVAL;
    index = (BYTE)fatfs_get_vol(fat);
    if (index >= FF_VOLUMES || (INT8)index < 0)
        return -EINVAL;
    result = snprintf_s(drive, sizeof(drive), sizeof(drive) - 1, "%d:/", index);
    if (result < 0)
        return -EINVAL;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
    /* Release virtual partition objects before unbind real partition */
    SETUP_SEARCH(&desc, g_fatVirPart.virtualinfo.devpartpath, false);
    FatfsVirtLock();
    result = FatFsUnbindVirPart(fat);
    FatfsVirtLock();
    if (result == FR_OK) {
        part = los_part_find(DiskDev[index]);
        (void)inode_find(&desc);
        inode = desc.node;
        if (part == NULL || part->dev == inode) {
            (void)memset_s(g_devPartName, sizeof(g_devPartName), 0, sizeof(g_devPartName));
            (void)memset_s(&g_fatVirPart.virtualinfo, sizeof(virpartinfo), 0, sizeof(virpartinfo));
            g_fatVirPart.isparamset = FALSE;
        }
    } else {
        return fatfs_2_vfs(result);
    }

#endif
    result = f_mount((FATFS *)NULL, drive, 0);
    if (result != FR_OK)
        return fatfs_2_vfs(result);

    VolToPart[index].di = 0;
    VolToPart[index].pd = 0;
    VolToPart[index].pt = 0;
    VolToPart[index].ps = 0;
    VolToPart[index].pc = 0;

    part = los_part_find(DiskDev[index]);
    if (part != NULL && part->part_name) {
        free(part->part_name);
        part->part_name = NULL;
    }

    if (blkdriver != NULL)
        *blkdriver = DiskDev[index];
    DiskDev[index] = (struct inode *)NULL;
    if (fat->win != NULL) {
        free(fat->win);
        fat->win = NULL;
    }
    if (fat != NULL) {
        free(fat);
        fat = NULL;
    }

    return OK;
}

static BYTE FatFsGetMode(int oflags, int *accMode)
{
    BYTE fmode = FA_READ;
    *accMode = READ_OP;

    if ((UINT)oflags & O_WRONLY) {
        fmode |= FA_WRITE;
        *accMode |= WRITE_OP;
    }

    if (((UINT)oflags & O_ACCMODE) & O_RDWR) {
        fmode |= FA_WRITE;
        *accMode |= WRITE_OP;
    }
    /* Creates a new file if the file is not existing, otherwise, just open it. */
    if ((UINT)oflags & O_CREAT) {
        fmode |= FA_OPEN_ALWAYS;
        *accMode |= WRITE_OP;
        /* Creates a new file. If the file already exists, the function shall fail. */
        if ((UINT)oflags & O_EXCL)
            fmode |= FA_CREATE_NEW;
    }
    /* Creates a new file. If the file already exists, its length shall be truncated to 0. */
    if ((UINT)oflags & O_TRUNC) {
        fmode |= FA_CREATE_ALWAYS;
        *accMode |= WRITE_OP;
    }

    return fmode;
}

#define FAT_USER_SHIFT 6
#define FAT_GROUP_SHIFT 3
#define FAT_NO_PERM 1
#define FAT_PERM 0
static unsigned int FatFsCheckPermission(struct inode *mountpt, bool dirFlag, int accMode)
{
    FATFS *fat = NULL;
    unsigned short umask;
    uint uid = OsCurrUserGet()->effUserID;
    uint gid = OsCurrUserGet()->effGid;
    mode_t fileMode = mountpt->i_mode;
    fat = (FATFS *)mountpt->i_private;

    if (fat == NULL) {
        umask = GetUmask();
    } else if (dirFlag) {
        umask = fat->fs_dmask;
    } else {
        umask = fat->fs_fmask;
    }

    fileMode &= (~umask);

    if (uid == mountpt->i_uid) {
        fileMode >>= FAT_USER_SHIFT;
    } else if (LOS_CheckInGroups(mountpt->i_gid)) {
        fileMode >>= FAT_GROUP_SHIFT;
    }

    fileMode &= (READ_OP | WRITE_OP | EXEC_OP);

    if ((accMode & fileMode) == accMode) {
        return FAT_PERM;
    }

    fileMode = 0;
    if (S_ISDIR(mountpt->i_mode)) {
        if ((accMode & EXEC_OP) && (IsCapPermit(CAP_DAC_READ_SEARCH))) {
            fileMode |= EXEC_OP;
        }
    } else {
        if ((accMode & EXEC_OP) && (IsCapPermit(CAP_DAC_EXECUTE))
            && (mountpt->i_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
            fileMode |= EXEC_OP;
        }
    }

    if ((accMode & WRITE_OP) && IsCapPermit(CAP_DAC_WRITE)) {
        fileMode |= WRITE_OP;
    }

    if ((accMode & READ_OP) && IsCapPermit(CAP_DAC_READ_SEARCH)) {
        fileMode |= READ_OP;
    }

    if ((accMode & fileMode) == accMode) {
        return FAT_PERM;
    }

    PRINTK("%s, %d, permission check fail,uid %d, gid %d, mode %d%d%d, accMode %d, cuid %d, cgid %d\n",
           __FUNCTION__, __LINE__, mountpt->i_uid, mountpt->i_gid,
           (mountpt->i_mode >> FAT_USER_SHIFT) & (READ_OP | WRITE_OP | EXEC_OP),
           (mountpt->i_mode >> FAT_GROUP_SHIFT) & (READ_OP | WRITE_OP | EXEC_OP),
           (mountpt->i_mode) & (READ_OP | WRITE_OP | EXEC_OP), accMode, uid, gid);

    return FAT_NO_PERM;
}

static bool oflag_convert_and_check(FAR struct file *filep, int oflags)
{
    unsigned int acc_mode = 0;

    if (((unsigned int)oflags & O_ACCMODE) == O_RDONLY)
        acc_mode |= READ_OP;
    if ((unsigned int)oflags & O_WRONLY)
        acc_mode |= WRITE_OP;
    if ((unsigned int)oflags & O_RDWR)
        acc_mode |= READ_OP | WRITE_OP;
    if ((unsigned int)oflags & O_CREAT)
        acc_mode |= WRITE_OP;
    if ((unsigned int)oflags & O_TRUNC)
        acc_mode |= WRITE_OP;
    if ((unsigned int)oflags & O_EXCL)
        acc_mode |= WRITE_OP;
    if ((unsigned int)oflags & O_APPEND)
        acc_mode |= WRITE_OP;
    if ((unsigned int)oflags & O_EXECVE)
        acc_mode |= EXEC_OP;

    if ((filep->f_inode->mountflags == MS_RDONLY) && ((acc_mode & WRITE_OP) != 0))
        return false;

    return true;
}

int fatfs_open(struct file *filep, const char *relpath, int oflags, mode_t mode)
{
    BYTE fmode;
    char *filePath = NULL;
    FATFS *fat = NULL;
    FIL *fp = NULL;
    FRESULT result;
    INT vol, ret;
    int accMode;

    if (filep == NULL || filep->f_inode == NULL || filep->f_inode->i_private == NULL || relpath == NULL) {
        return -EINVAL;
    }

    if ((UINT)oflags & O_DIRECTORY) {
        return -EACCES;
    }

    if (strlen(relpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    if (oflag_convert_and_check(filep, oflags) != true) {
        return -EACCES;
    }

    fat = (FATFS *)filep->f_inode->i_private;

    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, relpath);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    fmode = FatFsGetMode(oflags, &accMode);

    if (FatFsCheckPermission(filep->f_inode, false, accMode)) {
        free(filePath);
        return -EACCES;
    }

    fp = (FIL *)malloc(sizeof(FIL));
    if (fp == NULL) {
        free(filePath);
        return -ENOMEM;
    }
#if !FF_FS_TINY
    fp->buf = NULL;
#endif

    result = f_open(fp, filePath, fmode);
    free(filePath);
    if (result == FR_OK) {
        filep->f_pos  = fp->fptr;
        filep->f_priv = fp;

        if ((UINT)oflags & O_APPEND) {
#if FF_FS_MINIMIZE <= 2
            /* seek to the end of file */
            (void)f_lseek(fp, fp->obj.objsize);
            filep->f_pos = fp->fptr;
#else
            PRINT_ERR("f_lseek is not supported, O_APPEND won't take effect!\n");
#endif
        }
    } else {
        /* open failed, release memory and return errno */
#if !FF_FS_TINY
        if (fp->buf != NULL) {
            free(fp->buf);
        }
#endif
        free(fp);
        return fatfs_2_vfs(result);
    }

    return FatfsSdSync(filep->f_inode->mountflags, fat);
}

int fatfs_close(struct file *filep)
{
    FATFS *fat = NULL;
    FIL *fp = NULL;
    FRESULT result;
    INT vol;

    if (filep == NULL || filep->f_inode == NULL || filep->f_inode->i_private == NULL) {
        return -EINVAL;
    }

    fat = (FATFS *)filep->f_inode->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    fp = (FIL *)(filep->f_priv);
    FAT_CHECK(fp);

    result = f_close(fp);
    if (result == FR_OK) {
        /* close succeed, release memory */
#if !FF_FS_TINY
        if (fp->buf != NULL)
            free(fp->buf);
#endif
        free(fp);
        return FatfsSdSync(filep->f_inode->mountflags, fat);
    }

    return fatfs_2_vfs(result);
}

int fatfs_ioctl(FAR struct file *filep, int cmd, unsigned long arg)
{
    return -ENOSYS;
}

ssize_t fatfs_read(struct file *filep, char *buffer, size_t buflen)
{
    FIL *fp = NULL;
    FRESULT result;
    UINT byteRead;

    fp = (FIL *)(filep->f_priv);
    FAT_CHECK(fp);

    result = f_read(fp, buffer, buflen, &byteRead);
    /* file position should be updated */
    filep->f_pos = fp->fptr;

    if (result == FR_OK)
        return byteRead;

    return fatfs_2_vfs(result);
}

ssize_t fatfs_write(struct file *filep, const char *buffer, size_t buflen)
{
#if !FF_FS_READONLY
    FIL *fp = (FIL *)(filep->f_priv);
    FRESULT result;
    UINT byteWrite;

    if (filep->f_inode->mountflags == MS_RDONLY)
        return -EACCES;

    FAT_CHECK(fp);

    result = f_write(fp, buffer, buflen, &byteWrite);
    /* file position should be updated */
    filep->f_pos  = fp->fptr;
    if (f_sync(fp) != FR_OK)
        PRINT_ERR("fatfs_write f_sync error \n");
    if (result == FR_OK)
        return byteWrite;

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

int fatfs_sync(struct file *filep)
{
#if !FF_FS_READONLY
    FATFS *fat = NULL;
    FIL *fp = NULL;
    FRESULT result;
    INT vol;

    if (filep == NULL || filep->f_inode == NULL || filep->f_inode->i_private == NULL)
        return -EINVAL;

    if (filep->f_inode->mountflags == MS_RDONLY)
        return -EACCES;

    fat = (FATFS *)filep->f_inode->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES)
        return -ENOENT;

    fp = (FIL *)(filep->f_priv);
    FAT_CHECK(fp);

    result = f_sync(fp);

#ifdef LOSCFG_FS_FAT_CACHE
    los_part *part = NULL;
    if (result == FR_OK) {
        part = get_part((INT)fat->pdrv);
        if (part == NULL)
            return -ENODEV;
        (void)OsSdSync(part->disk_id);
    }
#endif
    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

int fatfs_dup(FAR const struct file *oldp, FAR struct file *newp)
{
    return -ENOSYS;
}

off_t fatfs_seek(struct file *filep, off_t offset, int whence)
{
#if FF_FS_MINIMIZE <= 2
    FRESULT result;
    FIL *fp = (FIL *)(filep->f_priv);

    FAT_CHECK(fp);

    switch (whence) {
        case SEEK_SET: /* The offset is set to offset bytes. */
            break;

        case SEEK_CUR: /* The offset is set to its current location plus offset bytes. */
            offset += (off_t)filep->f_pos;
            break;

        case SEEK_END: /* The offset is set to the size of the file plus offset bytes. */
            offset += fp->obj.objsize;
            break;

        default:
            return -EINVAL;
    }

    if (offset < 0) {
        return -EINVAL;
    }

    result = f_lseek(fp, offset);
    if (result == FR_OK) {
        /* return current position */
        filep->f_pos = (off_t)fp->fptr;
        return (off_t)fp->fptr;
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

loff_t fatfs_seek64(struct file *filep, loff_t offset, int whence)
{
#if FF_FS_MINIMIZE <= 2
    FRESULT result;
    FIL *fp = (FIL *)(filep->f_priv);

    FAT_CHECK(fp);

    switch (whence) {
        case SEEK_SET: /* The offset is set to offset bytes. */
            break;

        case SEEK_CUR: /* The offset is set to its current location plus offset bytes. */
            offset += filep->f_pos;
            break;

        case SEEK_END: /* The offset is set to the size of the file plus offset bytes. */
            offset += (loff_t)fp->obj.objsize;
            break;

        default:
            return -EINVAL;
    }

    if (offset < 0)
        return -EINVAL;

    result = f_lseek(fp, offset);
    if (result == FR_OK) {
        /* return current position */
        filep->f_pos = (loff_t)fp->fptr;
        return (loff_t)fp->fptr;
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

int fatfs_unlink(struct inode *mountpt, const char *relpath)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    FATFS *fat = NULL;
    FRESULT result;
    INT ret, vol;
    char *filePath = NULL;
    struct stat st;

    if (strlen(relpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH)
        return -ENAMETOOLONG;

    if (mountpt->mountflags == MS_RDONLY)
        return -EACCES;

    ret = fatfs_stat(mountpt, relpath, &st);
    if (ret != FR_OK)
        return ret;

    switch (st.st_mode & S_IFMT) {
        case S_IFREG:
            break;
        case S_IFDIR:
            return -EISDIR;
        default:
            /* unknown file type */
            return FAT_ERROR;
    }

    if (FatFsCheckPermission(mountpt, false, WRITE_OP | EXEC_OP)) {
        return -EACCES;
    }

    fat = (FATFS *)mountpt->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES)
        return -ENOENT;

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL)
        return -ENOMEM;

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, relpath);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    result = f_unlink(filePath);

    free(filePath);

    if (result == FR_OK) {
        return FatfsSdSync(mountpt->mountflags, fat);
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

int fatfs_rename(struct inode *mountpt, const char *oldpath, const char *newpath)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    FATFS *fat = NULL;
    FRESULT result;
    char *oldfspath = NULL;
    const char *newfspath = NULL;
    INT vol;
    size_t oldlen, newlen, len;
    INT ret;

    if (strlen(oldpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    if (mountpt->mountflags == MS_RDONLY)
        return -EACCES;

    oldlen = strlen(oldpath);
    newlen = strlen(newpath);
    if (!oldlen || !newlen) {
        return -EPERM;
    }

    len = oldlen < newlen ? oldlen : newlen;
    if (!strncmp(oldpath, newpath, len) && (oldpath[len] == '/' || newpath[len] == '/')) {
        return -EPERM;
    }

    if (FatFsCheckPermission(mountpt, false, WRITE_OP | EXEC_OP)) {
        return -EACCES;
    }

    fat = (FATFS *)mountpt->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    oldfspath = (char *)malloc(MAX_LFNAME_LENTH);
    if (oldfspath == NULL) {
        return -ENOMEM;
    }

    newfspath = newpath;
    ret = snprintf_s(oldfspath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, oldpath);
    if (ret < 0) {
        free(oldfspath);
        return -EINVAL;
    }

    result = f_rename(oldfspath, newfspath);

    free(oldfspath);

    if (result == FR_OK) {
        return FatfsSdSync(mountpt->mountflags, fat);
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

static void get_stmtime(struct stat *st, FILINFO *finfo)
{
    struct tm ftm;
    INT year, mon, day, hour, min, sec;
    WORD mtime;

    mtime = finfo->fdate;
    day = mtime & 0x1F; /* bit[4:0] Day(1..31) */
    mtime >>= 5;
    mon = mtime & 0x0F; /* bit[8:5] Month(1..12) */
    mtime >>= 4;
    year = (mtime & 0x7F) + 1980; /* bit[15:9] Year since 1980(0..127) */

    mtime = finfo->ftime;
    sec = (mtime & 0x1F) * 2; /* bit[4:0] Second/2(0..29) */
    mtime >>= 5;
    min = mtime & 0x3F; /* bit[10:5] Minute(0..59) */
    mtime >>= 6;
    hour = mtime & 0x1F; /* bit[15:11] Hour(0..23) */

    (void)memset_s(&ftm, sizeof(ftm), 0, sizeof(ftm));
    ftm.tm_year = year - 1900; /* Years since 1900 */
    ftm.tm_mon  = mon - 1; /* Months since January: 0-11 */
    ftm.tm_mday = day; /* Day: 1-31 */
    ftm.tm_hour = hour; /* Hours: 0-23 */
    ftm.tm_min  = min; /* Minutes: 0-59 */
    ftm.tm_sec  = sec; /* Seconds: 0-59 */

    st->st_mtime = mktime(&ftm);
}

int fatfs_stat(struct inode *mountpt, const char *path, struct stat *buf)
{
#if FF_FS_MINIMIZE == 0
    FILINFO finfo;
    FRESULT result;
    FATFS *fat = NULL;
    INT vol, ret;
    char *filePath = NULL;

    if (mountpt == NULL || mountpt->i_private == NULL) {
        return -EINVAL;
    }

    if (strlen(path) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    fat = (FATFS *)mountpt->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, path);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    result = f_stat(filePath, &finfo);

    (void)memset_s((void *)buf, sizeof(struct stat), 0, sizeof(struct stat));

    if (result == FR_OK) {
        buf->st_dev = 0;

        buf->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                       S_IWUSR | S_IWGRP | S_IWOTH |
                       S_IXUSR | S_IXGRP | S_IXOTH;

        if (finfo.fattrib & AM_RDO) {
            buf->st_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
        }

        if (finfo.fattrib & AM_DIR) {
            buf->st_mode &= ~S_IFREG;
            buf->st_mode |= S_IFDIR;
            buf->st_mode &= ~fat->fs_dmask;
        } else {
            buf->st_mode &= ~fat->fs_fmask;
        }

        if (!(mountpt->mountflags & MS_NOSUID)) {
            buf->st_uid = fat->fs_uid;
            buf->st_gid = fat->fs_gid;
        }

        buf->st_size    = (long long)finfo.fsize;
#if FF_MAX_SS != FF_MIN_SS
        buf->st_blksize = (unsigned long)fat->ssize * fat->csize;
#else
        buf->st_blksize = (unsigned long)FF_MIN_SS * fat->csize;
#endif
        buf->st_blocks    = (unsigned long long)(buf->st_size + buf->st_blksize - 1) / buf->st_blksize;
        get_stmtime(buf, &finfo);
    }

    if (result == FR_INVALID_NAME) { /* root directoy */
        buf->st_dev      = 0;
        buf->st_mode  = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                        S_IWUSR | S_IWGRP | S_IWOTH;

        buf->st_mode &= ~S_IFREG;
        buf->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
        if (mountpt->mountflags & MS_RDONLY) {
            buf->st_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
        }

        buf->st_mode &=     ~fat->fs_dmask;
        buf->st_mtime = 0;
        buf->st_size  = 0;
        if (!(mountpt->mountflags & MS_NOSUID)) {
            buf->st_uid = fat->fs_uid;
            buf->st_gid = fat->fs_gid;
        }

#if FF_MAX_SS != FF_MIN_SS
        buf->st_blksize = (unsigned long)fat->ssize * fat->csize;
#else
        buf->st_blksize = (unsigned long)FF_MIN_SS * fat->csize;
#endif
        buf->st_blocks  = (unsigned long long)(buf->st_size + buf->st_blksize - 1) / buf->st_blksize;
        result = FR_OK;
    }

    free(filePath);

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

#define VOL_NAME_LEN 4
int fatfs_statfs(struct inode *mountpt, struct statfs *buf)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    char drive[VOL_NAME_LEN];
    DWORD freClust;
    FATFS *fat = NULL;
    FRESULT result;
    INT vol, ret;

    FAT_CHECK(mountpt);
    FAT_CHECK(buf);

    fat = (FATFS *)mountpt->i_private;
    FAT_CHECK(fat);
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    ret = snprintf_s(drive, sizeof(drive), sizeof(drive) - 1, "%d:", vol);
    if (ret < 0) {
        return -EINVAL;
    }

    result = f_getfree(drive, &freClust, &fat);
    if (result != FR_OK) {
        return fatfs_2_vfs(result);
    }

    (void)memset_s((void *)buf, sizeof(struct statfs), 0, sizeof(struct statfs));
    buf->f_type   = MSDOS_SUPER_MAGIC;
    buf->f_bfree  = freClust;
    buf->f_bavail = freClust;
    buf->f_blocks = fat->n_fatent - 2; /* Cluster #0 and #1 is for VBR, reserve sectors and fat */
#if FF_MAX_SS != FF_MIN_SS
    buf->f_bsize  = fat->ssize * fat->csize;
#else
    buf->f_bsize  = FF_MIN_SS * fat->csize;
#endif

#if FF_USE_LFN
    /* Maximum length of filenames */
    buf->f_namelen = FF_MAX_LFN;
#else
    /* Maximum length of filenames: 8 is the basename length, 1 is the dot, 3 is the extension length */
    buf->f_namelen = (8 + 1 + 3);
#endif

    return 0;
#else
    return -ENOSYS;
#endif
}

int fatfs_utime(struct inode *mountpt, const char *pathname, const struct tm * set_tm)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    FILINFO finfo;
    FRESULT result;
    FATFS *fat = NULL;
    INT vol, status;
    char *filePath = NULL;

    if (mountpt == NULL || mountpt->i_private == NULL) {
        return -EINVAL;
    }

    if (strlen(pathname) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    if (set_tm->tm_year < 80) { /* year must be lager than 1980 */
        PRINT_ERR("modetime must be lager than 1980-1-1\n");
        return -EINVAL;
    }

    if (mountpt->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    fat = (FATFS *)mountpt->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    status = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, pathname);
    if (status < 0) {
        free(filePath);
        return -EINVAL;
    }

    /*
     * transform set_tm to be the format what we want,
     * and write in fatfs through f_utime to set modified
     * time.
     */

    /* fdate: bit[15:9] Year since 1980(0..127), bit[8:5] Month(0..11), bit[4:0] Day(1..31) */
    finfo.fdate = (WORD)(((set_tm->tm_year - 80) << 9) | (set_tm->tm_mon + 1) << 5 | set_tm->tm_mday);
    /* ftime: bit[15:11] Hour(0..23), bit[10:5] Minute(0..59), bit[4:0] Second/2(0..29) */
    finfo.ftime = (WORD)(set_tm->tm_hour << 11 | set_tm->tm_min << 5 | set_tm->tm_sec >> 1);
    result = f_utime(filePath, &finfo);
    status = fatfs_2_vfs(result);
    free(filePath);
    return status;
#else
    return -ENOSYS;
#endif
}

int fatfs_opendir(struct inode *mountpt, const char *relpath, struct fs_dirent_s *dir)
{
#if FF_FS_MINIMIZE <= 1
    char *filePath = NULL;
    DIR *fdir = NULL;
    FATFS *fat = NULL;
    FRESULT result;
    INT vol, ret;

    if (strlen(relpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    FAT_CHECK(dir);
    fat = (FATFS *)mountpt->i_private;
    FAT_CHECK(fat);
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, relpath);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    /* open directory */
    fdir = (DIR *)malloc(sizeof(DIR));
    if (fdir == NULL) {
        free(filePath);
        return -ENOMEM;
    }

    result = f_opendir(fdir, filePath);
    free(filePath);

    if (result != FR_OK) {
        free(fdir);
        return fatfs_2_vfs(result);
    }

    dir->u.fs_dir = (fs_dir_s)fdir;
    return FR_OK;
#else
    return -ENOSYS;
#endif
}

int fatfs_closedir(struct inode *mountpt, struct fs_dirent_s *dir)
{
#if FF_FS_MINIMIZE <= 1
    DIR *fdir = NULL;
    FRESULT result;

    FAT_CHECK(dir);
    fdir = (DIR *)(dir->u.fs_dir);
    FAT_CHECK(fdir);

    result = f_closedir(fdir);
    if (result == FR_OK) {
        free(fdir);
        return FR_OK;
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

int fatfs_readdir(struct inode *mountpt, struct fs_dirent_s *dir)
{
#if FF_FS_MINIMIZE <= 1
    DIR *fdir = NULL;
    FILINFO fno;
    FRESULT result;
    struct dirent *d = NULL;

    FAT_CHECK(dir);
    fdir = (DIR *)(dir->u.fs_dir);
    d = &dir->fd_dir;

    (void)memset_s(&fno, sizeof(FILINFO), 0, sizeof(FILINFO));
    result = f_readdir(fdir, &fno);
    if (result != FR_OK) {
        return fatfs_2_vfs(result);
    }

    /*
     * 0x00:Reached end of directory.
     * 0xFF:The directory is empty.
     */
    if (fno.fname[0] == 0 || fno.fname[0] == (TCHAR)0xFF) {
        return -ENOENT;
    }

    if (fno.fattrib & AM_DIR) {
        d->d_type = DT_DIR;
    } else {
        d->d_type = DT_REG;
    }

    d->d_reclen = (WORD)sizeof(struct dirent);

    if (strncpy_s(d->d_name, sizeof(d->d_name), fno.fname, strlen(fno.fname)) != EOK) {
        return -ENAMETOOLONG;
    }

    d->d_off = dir->fd_position;

    return ENOERR;
#else
    return -ENOSYS;
#endif
}

int fatfs_readdir_all(DIR_FAT *dir_fat)
{
#if FF_FS_MINIMIZE <= 1
    char *fn = NULL;
    DIR *fdir = NULL;
    FILINFO fno;
    FRESULT result;
    struct fs_dirent_s *dir = NULL;
    struct fat_direntall *d = NULL;
    INT ret;
    INT year, mon, day, hour, min, sec;
    WORD tmp;

    FAT_CHECK(dir_fat);
    dir = (struct fs_dirent_s *)dir_fat->stDirStream.dp;

    FAT_CHECK(dir);
    fdir = (DIR *)(dir->u.fs_dir);
    d = &dir_fat->stBuf.direntall;

    result = f_readdir(fdir, &fno);
    if (result != FR_OK) {
        return fatfs_2_vfs(result);
    }

    /*
     * 0x00:Reached end of directory.
     * 0xFF:The directory is empty.
     */
    if (fno.fname[0] == 0 || fno.fname[0] == (TCHAR)0xFF) {
        return -ENOENT;
    }

    fn = fno.fname;

    if (fno.fattrib & AM_DIR) {
        d->d_type = DT_DIR;
    } else {
        d->d_type = DT_REG;
    }

#ifdef _DIRENT_HAVE_D_NAMLEN
    d->d_namlen = (BYTE)strlen(fn);
#endif
    d->d_reclen = (WORD)(sizeof(struct fat_direntall) + strlen(fn));
    ret = strncpy_s(d->d_name, NAME_MAX, fn, strlen(fn));
    if (ret != EOK) {
        return -ENAMETOOLONG;
    }
#ifdef _DIRENT_HAVE_D_OFF
    d->d_off++;
#endif

    d->d_size = fno.fsize;

    /* get st_mtime. */
    tmp = fno.fdate;
    day = tmp & 0x1F; /* bit[4:0] Day(1..31) */
    tmp >>= 5;
    mon = tmp & 0x0F; /* bit[8:5] Month(1..12) */
    tmp >>= 4;
    year = tmp & 0x7F; /* bit[15:9] Year since 1980(0..127) */

    tmp = fno.ftime;
    sec = (tmp & 0x1F) * 2; /* bit[4:0] Second/2(0..29) */
    tmp >>= 5;
    min = tmp & 0x3F; /* bit[10:5] Minute(0..59) */
    tmp >>= 6;
    hour = tmp & 0x1F; /* bit[15:11] Hour(0..23) */

    d->d_createtime[0] = year;
    d->d_createtime[1] = mon;
    d->d_createtime[2] = day;
    d->d_createtime[3] = hour;
    d->d_createtime[4] = min;
    d->d_createtime[5] = sec;

    return ENOERR;
#else
    return -ENOSYS;
#endif
}

int fatfs_rewinddir(struct inode *mountpt, struct fs_dirent_s *dir)
{
#if FF_FS_MINIMIZE <= 1
    DIR *fdir = NULL;
    FRESULT result;

    FAT_CHECK(dir);
    fdir = (DIR *)(dir->u.fs_dir);
    FAT_CHECK(fdir);

    result = f_rewinddir(fdir);
    if (result != FR_OK) {
        return fatfs_2_vfs(result);
    }

    return FR_OK;
#else
    return -ENOSYS;
#endif
}

int fatfs_mkdir(struct inode *mountpt, const char *relpath, mode_t mode)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    char *filePath = NULL;
    FATFS *fat = NULL;
    FRESULT result;
    INT vol, ret;

    if (mountpt->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    if (strlen(relpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    if (FatFsCheckPermission(mountpt, true, WRITE_OP | EXEC_OP)) {
        return -EACCES;
    }

    fat = (FATFS *)mountpt->i_private;
    FAT_CHECK(fat);
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, relpath);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    result = f_mkdir(filePath);
    free(filePath);

    if (result == FR_OK) {
        return FatfsSdSync(mountpt->mountflags, fat);
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

int fatfs_rmdir(struct inode *mountpt, const char *relpath)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    char *filePath = NULL;
    FATFS *fat = NULL;
    FRESULT result;
    INT ret, vol;
    struct stat st;

    if (strlen(relpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    if (mountpt->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    ret = fatfs_stat(mountpt, relpath, &st);
    if (ret != FR_OK) {
        return ret;
    }

    switch (st.st_mode & S_IFMT) {
        case S_IFDIR:
            break;
        case S_IFREG:
            return -ENOTDIR;
        default:
            /* unknown file type */
            return FAT_ERROR;
    }

    if (FatFsCheckPermission(mountpt, true, WRITE_OP | EXEC_OP)) {
        return -EACCES;
    }

    fat = (FATFS *)mountpt->i_private;
    FAT_CHECK(fat);
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, relpath);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    result = f_unlink(filePath);
    free(filePath);

    if (result == FR_OK) {
        return FatfsSdSync(mountpt->mountflags, fat);
    }

    return fatfs_2_vfs(result);
#else
    return -ENOSYS;
#endif
}

static INT FatFsErase(INT option, los_part *part)
{
    INT opt = option;

    if ((UINT)opt & FMT_ERASE) {
        opt = (UINT)opt & (~FMT_ERASE);
        if (EraseDiskByID(part->disk_id, part->sector_start, part->sector_count) != 0) {
            PRINTK("SD card erase error.\n");
        }
    }

    if (opt != FM_FAT && opt != FM_FAT32) {
        opt = FM_ANY;
    }

    return opt;
}

static INT FatFsMountEmpty(los_part *part, char *drive, INT len, FATFS *fat)
{
    INT result, index;

    index = fatfs_get_vol((FATFS *)NULL);
    if (index == FAT_ERROR) {
        return -EEXIST; /* can't find empty fatfs */
    }

    VolToPart[index].di = part->disk_id;
    VolToPart[index].pd = part->part_id;
    VolToPart[index].pt = part->part_no_mbr;
    VolToPart[index].ps = part->sector_start;
    VolToPart[index].pc = part->sector_count;

    result = snprintf_s(drive, len, len - 1, "%d:/", index);
    if (result < 0) {
        return -EINVAL;
    }

    result = f_mount(fat, drive, 0);
    if (result != FR_OK) {
        return fatfs_2_vfs(result);
    }

    return index;
}

#define DMA_ALLGN  64
static INT FatFsSetPartInfo(INT index, los_part *part)
{
    los_disk *disk = NULL;
    char *mbrBuf = NULL;
    INT result;

    /* if there is no mbr before, the partition info needs to be changed after formatting. */
    if ((part->type != EMMC) && (part->part_no_mbr == 0)) {
        disk = get_disk(part->disk_id);
        if (disk == NULL) {
            return -EIO;
        }
        mbrBuf = (char *)memalign(DMA_ALLGN, disk->sector_size);
        if (mbrBuf == NULL) {
            return -ENOMEM;
        }
        (void)memset_s(mbrBuf, disk->sector_size, 0, disk->sector_size);
        result = los_disk_read(part->disk_id, mbrBuf, 0, 1);
        if (result < 0) {
            free(mbrBuf);
            return -EIO;
        }
        part->sector_start = LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_START_OFFSET]);
        part->sector_count = LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_COUNT_OFFSET]);
        part->part_no_mbr = 1;
        part->filesystem_type = mbrBuf[PAR_OFFSET + PAR_TYPE_OFFSET];

        VolToPart[index].pt = part->part_no_mbr;
        VolToPart[index].ps = part->sector_start;
        VolToPart[index].pc = part->sector_count;
        free(mbrBuf);
    }

    return ENOERR;
}

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
static INT FatFsVirPartMkFs(UINT flag, struct inode *mmcNode, int option, int index)
{
    INT virRet;
    struct inode_search_s desc;
    FAR struct inode *inode;
    if (flag != 0) {
        return VIRERR_NOTMOUNT;
    }

    SETUP_SEARCH(&desc, g_fatVirPart.virtualinfo.devpartpath, false);
    (void)inode_find(&desc);
    inode = desc.node;

    if (inode != mmcNode) {
        return VIRERR_NOPARAM;
    }

    inode_release(inode);

    (void)FatFsUnbindVirPart(f_getfatfs(index));

    if (option != FM_FAT32) {
        return VIRERR_NOTFIT;
    }

    virRet = FatFsMakeVirPart(f_getfatfs(index), index);
    if (virRet < VIRERR_BASE) {
        return FR_OK;
    }

    return virRet;
}
#endif

#define INDEX_LABEL_LEN 15
static INT FatFsSetLabel(int index)
{
    INT result = FR_OK;

#if FF_USE_LABEL
    char label[INDEX_LABEL_LEN] = {0};
    result = snprintf_s(label, sizeof(label), sizeof(label) - 1, "%d:%s", index, FatLabel);
    if (result < 0) {
        result = -EINVAL;
    }

    result = f_setlabel(label);
    if (result != FR_OK) {
        dprintf("Set sd card volume label failed !\n ");
    }

#endif

    return result;
}

/*
 * return  : 0 : OK; -ENODEV : "/dev/mmc0" driver not ready
 * sectors : 0~128 0:auto seclect; 1:512Byte; 2:1KB; 4 : 2KB; 128:64KB; if secotrs > 128,auto seclect;
 */
int fatfs_mkfs(const char *dev, int sectors, int option)
{
#if FF_USE_MKFS && !FF_FS_READONLY
    INT result, index, err;
    FATFS fat = {0};
    UINT flag = 0;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
    INT virRet = 0;
#endif
    los_part *part = NULL;
    char drive[DRIVER_NAME_LEN] = {0};
    char *work = NULL;
    struct inode *mmcNode = NULL;
    struct inode_search_s desc;

    fat.win = NULL;

    /* if device not register in system,it may cause serious error,so return -ENODEV */
    SETUP_SEARCH(&desc, dev, false);
    (void)inode_find(&desc);
    mmcNode = desc.node;

    if (mmcNode == NULL)
        return -ENODEV; /* "mmc0" driver not ready */

    part = los_part_find(mmcNode);
    if (part == NULL || part->dev == NULL) {
        inode_release(mmcNode);
        return -ENODEV;
    }

    index = FatGetDisk(mmcNode);
    /* if not mount, find an empty fatfs to mount */
    if (index == FAT_ERROR) {
        index = FatFsMountEmpty(part, drive, sizeof(drive), &fat);
        if (index < 0) {
            err = index;
            goto ERROUT;
        }
        DiskDev[index] = mmcNode;
        flag |= 1<<1;
    } else {
        if (f_checkopenlock(index) != FR_OK) { /* format is not allowed when a file or diretory is opened. */
            inode_release(mmcNode);
            return -EBUSY;
        }
        result = snprintf_s(drive, sizeof(drive), sizeof(drive) - 1, "%d:/", index);
        if (result < 0) {
            inode_release(mmcNode);
            return -EINVAL;
        }

        flag = 0;
    }

    option = FatFsErase(option, part);
    work = (char *)malloc(FF_MAX_SS);
    if (work == NULL) {
        err = -ENOMEM;
        goto ERROUT_WITH_MOUNT;
    }
    if (part->type == EMMC)
        option = (UINT)option | FM_SFD;
    result = f_mkfs(drive, option, sectors, work, FF_MAX_SS);
    free(work);
    if (result != FR_OK) {
        err = fatfs_2_vfs(result);
        goto ERROUT_WITH_MOUNT;
    }

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
    FatfsVirtLock();
    virRet = FatFsVirPartMkFs(flag, mmcNode, option, index);
    FatfsVirtUnlock();
#endif

    result = FatFsSetLabel(index);
#ifdef LOSCFG_FS_FAT_CACHE
    if (result == FR_OK) {
        err = OsSdSync(part->disk_id);
        if (err < 0) {
            err = -EIO;
            goto ERROUT_WITH_MOUNT;
        }
    }
#endif

    err = FatFsSetPartInfo(index, part);

ERROUT_WITH_MOUNT:
    if (flag & (1 << 1)) {
        (void)f_mount(NULL, drive, 0); /* unmount the tmp fatfs */
        DiskDev[index] = (struct inode *)NULL;
    }

ERROUT:
    inode_release(mmcNode);
    if (fat.win != NULL)
        free(fat.win);
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
    if (err == 0)
        err = virRet;
#endif
    return err;
#else
    return -ENOSYS;
#endif
}

int fatfs_chattr(struct inode *mountpt, const char *relpath, struct IATTR *fattr)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    FRESULT result;
    FATFS *fat = NULL;
    INT vol, ret;
    char *filePath = NULL;
    unsigned char attr;
    mode_t mode = 0;

    if (mountpt == NULL || mountpt->i_private == NULL) {
        return -EINVAL;
    }

    if (strlen(relpath) > MAX_LFNAME_LENTH - VOLUME_CHAR_LENGTH) {
        return -ENAMETOOLONG;
    }

    if (mountpt->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    attr = mode & (AM_RDO | AM_HID | AM_SYS | AM_ARC);

    fat = (FATFS *)mountpt->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    filePath = (char *)malloc(MAX_LFNAME_LENTH);
    if (filePath == NULL) {
        return -ENOMEM;
    }

    ret = snprintf_s(filePath, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, relpath);
    if (ret < 0) {
        free(filePath);
        return -EINVAL;
    }

    result = f_chmod(filePath, attr, 0xff);

    free(filePath);

    if (result == FR_OK) {
        return FatfsSdSync(mountpt->mountflags, fat);
    }

    return fatfs_2_vfs(result);

#else
    return -ENOSYS;
#endif
}

int fatfs_getlabel(void *handle, char *label)
{
#if FF_USE_LABEL
    BYTE index;
    FATFS *fat = NULL;
    FRESULT result;
    los_part *part = NULL;
    char drive[DRIVER_NAME_LEN];
    DWORD *vsn = NULL;
    INT ret;

    if (label == NULL) {
        return -EFAULT;
    }

    fat = (FATFS *)handle;
    if (fat == NULL) {
        return -EINVAL;
    }

    index = (BYTE)fatfs_get_vol(fat);
    if (index >= FF_VOLUMES || (INT8)index < 0) {
        return -EINVAL;
    }

    part = los_part_find(DiskDev[index]);
    if (part == NULL) {
        return -ENODEV;
    }

    ret = snprintf_s(drive, sizeof(drive), sizeof(drive) - 1, "%d:/", index);
    if (ret < 0) {
        return -EINVAL;
    }

    result = f_getlabel(drive, label, vsn);
    if (result != FR_OK) {
        return fatfs_2_vfs(result);
    }

    return OK;
#else
    return -ENOSYS;
#endif
}

int fatfs_fallocate(FAR struct file *filep, int mode, off_t offset, off_t len)
{
#if FF_USE_EXPAND && !FF_FS_READONLY
    FIL *fp = (FIL *)(filep->f_priv);
    FRESULT res;

    FAT_CHECK(fp);

    if (len <= 0 || offset < 0) {
        return -EINVAL;
    }

    if (mode != FALLOC_FL_KEEP_SIZE) {
        return -EINVAL;
    }

    if (filep->f_inode->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    res = f_expand(fp, (FSIZE_t)offset, (FSIZE_t)len, FALLOC_FL_KEEP_SIZE);

    if (res == FR_OK) {
        res = f_sync(fp);
    }

    return fatfs_2_vfs(res);
#else
    return -ENOSYS;
#endif
}

int fatfs_fallocate64(FAR struct file *filep, int mode, off64_t offset, off64_t len)
{
#if FF_USE_EXPAND && !FF_FS_READONLY
    FIL *fp = (FIL *)(filep->f_priv);
    FRESULT  res;

    FAT_CHECK(fp);

    if (len >= FAT32_MAXSZIE || len <= 0 || offset >= FAT32_MAXSZIE || offset < 0) {
        return -EINVAL;
    }

    if (mode != FALLOC_FL_KEEP_SIZE) {
        return -EINVAL;
    }

    if (filep->f_inode->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    res = f_expand(fp, (FSIZE_t)offset, (FSIZE_t)len, FALLOC_FL_KEEP_SIZE);

    if (res == FR_OK) {
        res = f_sync(fp);
    }

    return fatfs_2_vfs(res);
#else
    return -ENOSYS;
#endif
}

int los_set_systime_status(BOOL bStatus)
{
    if (bStatus != FAT_SYSTEM_TIME_ENABLE && bStatus != FAT_SYSTEM_TIME_DISABLE) {
        return -EINVAL;
    }

    f_settimestatus(bStatus);
    return FR_OK;
}

int fatfs_truncate(FAR struct file *filep, off_t length)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    FIL *fp = (FIL *)(filep->f_priv);
    FRESULT res = FR_OK;
    UINT count;
    DWORD n, fclust;
#ifdef LOSCFG_FS_FAT_CACHE
    FATFS *fat = NULL;
#endif

    if (filep->f_inode->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    FAT_CHECK(fp);

    if (length < 0) {
        return -EINVAL;
    }

    res = f_getclustinfo(fp, &fclust, &count);
    if (res != FR_OK) {
        return fatfs_2_vfs(res);
    }

    if (count == 0xFFFFFFFF) {
        return -EPERM;
    }

    n = (DWORD)(fp->obj.fs)->csize * SS(fp->obj.fs); /* Cluster size */

    if ((unsigned long)length > count * n) {
#if FF_USE_EXPAND
        res = f_expand(fp, 0, (FSIZE_t)(length), FALLOC_FL_KEEP_SIZE);
#else
        return -ENOSYS;
#endif
    } else if ((unsigned long)length < n * count) {
        res = f_truncate(fp, (FSIZE_t)length);
    }
    fp->obj.objsize = length; /* Set file size to length */
    fp->flag |= 0x40; /* Set modified flag */

    if (res == FR_OK) {
        res = f_sync(fp);
    }
#ifdef LOSCFG_FS_FAT_CACHE
    if (res == FR_OK) {
        fat = (FATFS *)filep->f_inode->i_private;
        FAT_CHECK(fat);
        return FatfsSdSync(filep->f_inode->mountflags, fat);
    }
#endif
    return fatfs_2_vfs(res);
#else
    return -ENOSYS;
#endif
}

int fatfs_truncate64(FAR struct file *filep, off64_t length)
{
#if FF_FS_MINIMIZE == 0 && !FF_FS_READONLY
    FIL *fp = (FIL *)(filep->f_priv);
    FRESULT res = FR_OK;
    UINT count;
    DWORD n, fclust;
#ifdef LOSCFG_FS_FAT_CACHE
    FATFS *fat = NULL;
#endif

    FAT_CHECK(fp);

    if (filep->f_inode->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    if (length >= FAT32_MAXSZIE || length < 0) {
        return -EINVAL;
    }

    res = f_getclustinfo(fp, &fclust, &count);
    if (res != FR_OK) {
        return fatfs_2_vfs(res);
    }

    if (count == 0xFFFFFFFF) {
        return -EPERM;
    }

    n = (DWORD)(fp->obj.fs)->csize * SS(fp->obj.fs); /* Cluster size */

    if (length > (off64_t)count * n) {
#if FF_USE_EXPAND
        res = f_expand(fp, 0, (FSIZE_t)(length), FALLOC_FL_KEEP_SIZE);
#else
        return -ENOSYS;
#endif
    } else if (length < (off64_t)count * n) {
        res = f_truncate(fp, (FSIZE_t)length);
    }

    fp->obj.objsize = length; /* Set file size to length */
    fp->flag |= 0x40; /* Set modified flag */

    if (res == FR_OK) {
        res = f_sync(fp);
    }
#ifdef LOSCFG_FS_FAT_CACHE
    if (res == FR_OK) {
        fat = (FATFS *)filep->f_inode->i_private;
        FAT_CHECK(fat);
        return FatfsSdSync(filep->f_inode->mountflags, fat);
    }
#endif
    return fatfs_2_vfs(res);
#else
    return -ENOSYS;
#endif
}

#define DATE_OFFSET 16
#define CHECK_FILE_NUM 3
static INT FatFsTimeMin(DIR_FILE dirFile[])
{
    INT min = 0;
    DWORD timeMin = 0;

    MIN((dirFile[0].fno.fdate << DATE_OFFSET | dirFile[0].fno.ftime),
        (dirFile[1].fno.fdate << DATE_OFFSET | dirFile[1].fno.ftime), timeMin);
    MIN((DWORD)(dirFile[2].fno.fdate << DATE_OFFSET | dirFile[2].fno.ftime), timeMin, timeMin);
    if (timeMin == (dirFile[0].fno.fdate << DATE_OFFSET | dirFile[0].fno.ftime)) {
        min = 0;
    } else if (timeMin == (dirFile[1].fno.fdate << DATE_OFFSET | dirFile[1].fno.ftime)) {
        min = 1;
    } else if (timeMin == (dirFile[2].fno.fdate << DATE_OFFSET | dirFile[2].fno.ftime)) {
        min = 2; /* check the latest three files */
    }

    return min;
}

int fatfs_fscheck(struct inode *mountpt, const char *relpath, struct fs_dirent_s *dir)
{
    DIR *fdir = NULL;
    FILINFO fno;
    FRESULT result;
    INT count = 0;
    INT timeOldest = 0;
    DIR dirBackup = {0};
    DIR_FILE dirFile[CHECK_FILE_NUM] = {0};
    INT loop = 0;
#ifdef LOSCFG_FS_FAT_CACHE
    FATFS *fat = NULL;
    los_part *part = NULL;
    INT vol;
#endif
    INT ret;

    if (mountpt->mountflags == MS_RDONLY) {
        return -EACCES;
    }

    FAT_CHECK(dir);

    ret = fatfs_opendir(mountpt, relpath, dir);
    if (ret != FR_OK) {
        return ret;
    }

    fdir = (DIR *)(dir->u.fs_dir);
    if ((fdir->obj.fs)->fs_type != FS_FAT32) {
        (void)fatfs_closedir(mountpt, dir);
        return -EINVAL;
    }

    do {
        (void)memcpy_s(&dirBackup, sizeof(DIR), fdir, sizeof(DIR));
        result = f_readdir(fdir, &fno);
        if (result != FR_OK) {
            break;
        }

        if ((fno.fname[0] == 0 || fno.fname[0] == (TCHAR)0xFF)) {
            break;
        }

        if (fno.fattrib == AM_DIR) {
            continue;
        }

        if (count == 0) {
            (void)memcpy_s(&dirFile[0].f_dir, sizeof(DIR), &dirBackup, sizeof(DIR));
            (void)memcpy_s(&dirFile[0].fno, sizeof(FILINFO), &fno, sizeof(FILINFO));
        } else if (count == 1) {
            (void)memcpy_s(&dirFile[1].f_dir, sizeof(DIR), &dirBackup, sizeof(DIR));
            (void)memcpy_s(&dirFile[1].fno, sizeof(FILINFO), &fno, sizeof(FILINFO));
        } else if (count == 2) { /* check the latest three files */
            (void)memcpy_s(&dirFile[2].f_dir, sizeof(DIR), &dirBackup, sizeof(DIR));
            (void)memcpy_s(&dirFile[2].fno, sizeof(FILINFO), &fno, sizeof(FILINFO));
            timeOldest = FatFsTimeMin(dirFile);
        } else {
            if ((fno.fdate << DATE_OFFSET | fno.ftime) >
                (dirFile[timeOldest].fno.fdate << DATE_OFFSET | dirFile[timeOldest].fno.ftime)) {
                (void)memcpy_s(&dirFile[timeOldest].f_dir, sizeof(DIR), &dirBackup, sizeof(DIR));
                (void)memcpy_s(&dirFile[timeOldest].fno, sizeof(FILINFO), &fno, sizeof(FILINFO));
                timeOldest = FatFsTimeMin(dirFile);
            }
        }
        count++;
    } while (result == FR_OK);
    if (count >= CHECK_FILE_NUM) {
        loop = CHECK_FILE_NUM;
    } else {
        loop = count;
    }

    ret = fatfs_closedir(mountpt, dir);
    if (ret != FR_OK) {
        return ret;
    }

    for (count = 0; count < loop; count++) {
        result = f_fcheckfat(&dirFile[count]);
        if (result != FR_OK) {
            return fatfs_2_vfs(result);
        }
    }
#ifdef LOSCFG_FS_FAT_CACHE
    fat = (FATFS *)mountpt->i_private;
    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }
    part = get_part((INT)fat->pdrv);
    if (part != NULL) {
        (void)OsSdSync(part->disk_id);
    }
#endif

    return ENOERR;
}

int fatfs_virstatfs(struct inode *mountpt, const char *relpath, struct statfs *buf)
{
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
    return fatfs_virstatfs_internel(mountpt, relpath, buf);
#else
    return 0;
#endif
}

const struct mountpt_operations fat_operations = {
    fatfs_open, /* open */
    fatfs_close, /* close */
    fatfs_read, /* read */
    fatfs_write, /* write */
    fatfs_seek, /* seek */
    fatfs_ioctl, /* ioctl */
    OsVfsFileMmap, /* mmap */
    fatfs_sync, /* sync */
    fatfs_dup, /* dup */
    NULL, /* fstat */
    fatfs_truncate, /* truncate */

    fatfs_opendir, /* opendir */
    fatfs_closedir, /* closedir */
    fatfs_readdir, /* readdir */
    fatfs_rewinddir, /* rewinddir */

    fatfs_bind, /* bind */
    fatfs_unbind, /* unbind */
    fatfs_statfs, /* statfs */
    fatfs_virstatfs, /* virstatfs */
    fatfs_unlink, /* unlinke */
    fatfs_mkdir, /* mkdir */
    fatfs_rmdir, /* rmdir */
    fatfs_rename, /* rename */
    fatfs_stat, /* stat */
    fatfs_utime, /* utime */
    fatfs_chattr, /* chattr */
    fatfs_seek64, /* seek64 */
    fatfs_getlabel, /* getlabel */
    fatfs_fallocate, /* fallocate */
    fatfs_fallocate64, /* fallocate64 */
    fatfs_truncate64, /* truncate64 */
    fatfs_fscheck, /* fscheck */
    NULL, /* map_pages */
    NULL, /* readpage */
    NULL, /* writepage */
};

FSMAP_ENTRY(fat_fsmap, "vfat", fat_operations, FALSE, TRUE);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* LOSCFG_FS_FAT */
