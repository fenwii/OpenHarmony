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

#include "virpart.h"
#include "errno.h"
#include "fatfs.h"
#include "dirop_fat.h"
#include "errcode_fat.h"
#include "disk.h"

#ifdef LOSCFG_FS_FAT_CACHE
#include "bcache.h"
#endif

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION

#include "virpartff.h"

char g_devPartName[DISK_NAME + 1] = {0};

static INT FatFsCheckPercent(virpartinfo *virtualinfo)
{
    double virtPercent = 0.0;
    INT partCount;

    for (partCount = 0; partCount < virtualinfo->virpartnum; partCount++) {
        if (virtualinfo->virpartpercent[partCount] <= _FLOAT_ACC ||
            virtualinfo->virpartpercent[partCount] >= (1 - _FLOAT_ACC)) {
            set_errno(VIRERR_PARMPERCENTERR);
            g_fatVirPart.isparamset = FALSE;
            return -1;
        }
        virtPercent += virtualinfo->virpartpercent[partCount];
    }

    if (virtPercent >= (1 + _FLOAT_ACC)) {
        set_errno(VIRERR_PARMPERCENTERR);
        g_fatVirPart.isparamset = FALSE;
        return -1;
    }

    return 0;
}

static INT FatFsCheckName(virpartinfo *virtualinfo)
{
    INT partCount, loopCount, len;
    FRESULT res;

    for (partCount = 0; partCount < virtualinfo->virpartnum; partCount++) {
        len = ff_strnlen(virtualinfo->virpartname[partCount], _MAX_ENTRYLENGTH + 1);
        if (len <= 0 || len > _MAX_ENTRYLENGTH) {
            set_errno(VIRERR_PARMNAMEERR);
            g_fatVirPart.isparamset = FALSE;
            return -1;
        }

        res = f_checkname(virtualinfo->virpartname[partCount]);
        if (res != FR_OK) {
            set_errno(VIRERR_PARMNAMEERR);
            g_fatVirPart.isparamset = FALSE;
            return -1;
        }
    }

    for (partCount = 0; partCount < virtualinfo->virpartnum; partCount++) {
        for (loopCount = partCount + 1; loopCount < virtualinfo->virpartnum; loopCount++) {
            if ((memcmp(virtualinfo->virpartname[partCount], virtualinfo->virpartname[loopCount],
                        _MAX_ENTRYLENGTH)) == 0) {
                set_errno(VIRERR_PARMNAMEERR);
                g_fatVirPart.isparamset = FALSE;
                return -1;
            }
        }
    }

    return 0;
}

INT los_set_virpartparam(virpartinfo virtualinfo)
{
    INT ret;
    UINT minSize;
    UINT dstNameSize;
    char devHead[DISK_NAME + 1] = "/dev/";

    g_fatVirPart.virtualinfo.devpartpath = g_devPartName;

    if (g_fatVirPart.isparamset == TRUE) {
        set_errno(VIRERR_PARMLOCKED);
        return -1;
    }

    g_fatVirPart.isparamset = TRUE;

    if (virtualinfo.virpartnum < 1 || virtualinfo.virpartnum > _MAX_VIRVOLUMES) {
        set_errno(VIRERR_PARMNUMERR);
        g_fatVirPart.isparamset = FALSE;
        return -1;
    }

    ret = FatFsCheckPercent(&virtualinfo);
    if (ret != 0) {
        return ret;
    }

    ret = FatFsCheckName(&virtualinfo);
    if (ret != 0) {
        return ret;
    }

    if (strlen(virtualinfo.devpartpath) <= strlen(devHead)) {
        set_errno(VIRERR_PARMDEVERR);
        g_fatVirPart.isparamset = FALSE;
        return -1;
    }

    if (memcmp(virtualinfo.devpartpath, devHead, strlen(devHead)) != 0) {
        set_errno(VIRERR_PARMDEVERR);
        g_fatVirPart.isparamset = FALSE;
        return -1;
    }

    dstNameSize = sizeof(g_devPartName);
    minSize = dstNameSize < strlen(virtualinfo.devpartpath) ? dstNameSize : strlen(virtualinfo.devpartpath);
    ret = strncpy_s(g_fatVirPart.virtualinfo.devpartpath, dstNameSize, virtualinfo.devpartpath, minSize);
    if (ret != EOK) {
        set_errno(VIRERR_PARMNAMEERR);
        g_fatVirPart.isparamset = FALSE;
        return -1;
    }
    g_fatVirPart.virtualinfo.devpartpath[dstNameSize - 1] = '\0';

    (void)memcpy_s(g_fatVirPart.virtualinfo.virpartname, sizeof(g_fatVirPart.virtualinfo.virpartname),
                   virtualinfo.virpartname, sizeof(virtualinfo.virpartname));
    (void)memcpy_s(g_fatVirPart.virtualinfo.virpartpercent, sizeof(g_fatVirPart.virtualinfo.virpartpercent),
                   virtualinfo.virpartpercent, sizeof(virtualinfo.virpartpercent));
    g_fatVirPart.virtualinfo.virpartnum = virtualinfo.virpartnum;

    return 0;
}

static INT FatfsDisablePart(void *handle)
{
    FATFS *fs = (FATFS *)handle;
    return fatfs_2_vfs(f_disvirfs(fs));
}

/*
 * FatfsScanFat:
 * Scan the FAT inside the boundary of CHILD FATFS limit, and update the free cluster and last cluster
 * for all CHILD FATFS.
 * Acceptable Return Value:
 * - FR_OK              : Successfully scaned the FAT and update field.
 * Others Return Value:
 * - FR_INVAILD_FATFS   : The FATFS object has error or the info in it has been occuried
 * - FR_DENIED          : The virtual partition feature has been shut down by switcher
 * - FR_DISK_ERR        : A disk error happened
 */
static INT FatfsScanFat(void *handle)
{
    FATFS *fat = (FATFS *)handle;
    UINT i;
    INT ret;

    for (i = 0; i < fat->vir_amount; i++) {
        /* Assert error will not abort the scanning process */
        ret = f_scanfat(CHILDFS(fat, i));
        if (ret != FR_OK) {
            break;
        }
    }

    return fatfs_2_vfs(ret);
}

/*
 * FatfsScanClear:
 * Scan the root directory clean completely, regardless of the virtual partition entry.
 * Acceptable Return Value:
 * - FR_OK          : The root directory is completely clean.
 * - FR_NOTCLEAR    : The root dircotory is not clean.
 * Others Return Value:
 * Followed the by the lower API.
 */
static FRESULT FatfsScanClear(INT vol)
{
    FRESULT ret;
    DIR dir;
    FILINFO fno;
    CHAR path[MAX_LFNAME_LENTH];
    INT num;
    INT res;

    /* num : for the amount of all item in root directory */
    num = 0;

    (void)memset_s(path, sizeof(path), 0, sizeof(path));

    res = snprintf_s(path, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:/", vol);
    if (res < 0) {
        return FR_INVALID_NAME;
    }

    ret = f_opendir(&dir, path);
    if (ret != FR_OK) {
        return ret;
    }

    /* Scan all entry for searching virtual partition directory and others in root directory */
    while (1) {
        (void)memset_s(&fno, sizeof(FILINFO), 0, sizeof(FILINFO));
        ret = f_readdir(&dir, &fno);
        /* Reach the end of directory, or the root direcotry is empty, abort the scanning operation */
        if (fno.fname[0] == 0x00 || fno.fname[0] == (TCHAR)0xFF) {
            break;
        }

        if (ret != FR_OK) {
            (void)f_closedir(&dir);
            return ret;
        }
        num++;
    }

    /* Close the directory */
    ret = f_closedir(&dir);
    if ((ret == FR_OK) && (num != 0)) {
        return FR_NOTCLEAR;
    }

    return ret;
}

/*
 * FatfsBuildEntry:
 * Scan virtual partition entry in root directory, and try to rebuild the
 * error virtual partition, according to the scanning result.
 * Acceptable Return Value:
 * - FR_OK          : The root directory is completely clean.
 * - FR_OCCUPIED    : The virtual partition entry has been occupied by the same name file.
 * - FR_CHAIN_ERR   : The virtual partition entry has been rebuilt along the invaild cluster
 *                    chain.
 * Others Return Value:
 * Followed the by the lower API
 */
static FRESULT FatfsBuildEntry(FATFS *fat, INT vol)
{
    UINT i;
    CHAR path[MAX_LFNAME_LENTH];
    FRESULT ret;
    DIR dir;
    INT res;

    for (i = 0; i < fat->vir_amount; i++) {
        res = snprintf_s(path, MAX_LFNAME_LENTH, MAX_LFNAME_LENTH - 1, "%d:%s", vol, CHILDFS(fat, i)->namelabel);
        if (res < 0) {
            return FR_INVALID_NAME;
        }

        ret = f_mkdir(path);
        if (ret == FR_EXIST) {
            (void)memset_s(&dir, sizeof(dir), 0, sizeof(dir));
            ret = f_opendir(&dir, path);
            if (ret == FR_NO_DIR) {
                return FR_OCCUPIED;
            }
            if (ret == FR_OK) {
                ret = f_boundary(CHILDFS(fat, i), dir.obj.sclust);
                if (ret != FR_OK) {
                    (void)f_closedir(&dir);
                    return ret;
                }
            } else {
                return ret;
            }
            ret = f_closedir(&dir);
            if (ret != FR_OK) {
                return ret;
            }
        } else if (ret != FR_OK) {
            return ret;
        }
    }

    return FR_OK;
}

/*
 * FatFsUnbindVirPart:
 * Uninitialized the CHILD FATFS object
 *
 * Acceptable Return Value:
 * - ENOERR : Successfully initialized the CHILD FATFS object.
 */
INT FatFsUnbindVirPart(void *handle)
{
    INT ret;
    FATFS *fat = (FATFS *)handle;
    ret = f_unregvirfs(fat);
    return fatfs_2_vfs(ret);
}

/*
 * FatFsBindVirPart:
 * Bind the virtual partition
 *
 * Acceptable Return Value:
 * - FR_OK : Finished the virtual partition.
 * The virtual partition result can refer by API
 */
INT FatFsBindVirPart(void *handle, BYTE vol)
{
    INT ret;
    FATFS *fat = (FATFS *)handle;
    char path[MAX_LFNAME_LENTH] = {0};

    if (fat == NULL) {
        return -EINVAL;
    }

    ret = snprintf_s(path, sizeof(path), sizeof(path) - 1, "%d:/", vol);
    if (ret < 0) {
        return -EINVAL;
    }

    /* Detect the information in the reserve sector and try to set virtual partition by sector info */
    ret = f_checkvirpart(fat, path, vol);
    if (ret == FR_NOVIRPART) {
        /* Failed to use the External SD setting, try to use the current setting to external SD and rebuild entries */
        /* Check the enviorment whether it is fit for virtual parition */
        ret = FatfsScanClear(vol);
        if (ret != FR_OK) {
            /* A error happened in the file operation */
            (void)FatfsDisablePart(fat);
            return fatfs_2_vfs(ret);
        }
        /* Ready to fit the SD card to virtual partition featrue */
        ret = f_makevirpart(fat, path, vol);
        if (ret != FR_OK) {
            (void)FatfsDisablePart(fat);
            return fatfs_2_vfs(ret);
        }
    } else if (ret != FR_OK) {
        return fatfs_2_vfs(ret);
    }
    /* Try to build the virtual entry */
    ret = FatfsBuildEntry(fat, vol);
    if (ret != FR_OK) {
        (void)FatfsDisablePart(fat);
        return fatfs_2_vfs(ret);
    }
#ifdef LOSCFG_FS_FAT_CACHE
    los_part *part = NULL;
    if (ret == FR_OK) {
        part = get_part((int)fat->pdrv);
        if (part != NULL) {
            ret = OsSdSync(part->disk_id);
            if (ret < 0) {
                ret = -EIO;
            }
        } else {
            return -ENODEV;
        }
    }
#endif
    if (ret == FR_OK) {
        ret = FatfsScanFat(fat);
        if (ret != FR_OK) {
            (void)FatfsDisablePart(fat);
            return fatfs_2_vfs(ret);
        }
    }
    return fatfs_2_vfs(ret);
}

/*
 * FatFsMakeVirPart:
 * Bind the virtual partition
 *
 * Acceptable Return Value:
 * - FR_OK : Finished the virtual partition.
 * The virtual partition result can refer by API
 */
INT FatFsMakeVirPart(void *handle, BYTE vol)
{
    INT ret;
    FATFS *fat = (FATFS *)handle;
    char path[MAX_LFNAME_LENTH] = {0};

    if (fat == NULL) {
        return -EINVAL;
    }

    ret = snprintf_s(path, sizeof(path), sizeof(path) - 1, "%d:/", vol);
    if (ret < 0) {
        return -EINVAL;
    }

    /* Ready to fit the SD card to virtual partition featrue */
    ret = f_makevirpart(fat, path, vol);
    if (ret != FR_OK) {
        (void)FatfsDisablePart(fat);
        return fatfs_2_vfs(ret);
    }

    /* Try to build the virtual entry */
    ret = FatfsBuildEntry(fat, vol);
    if (ret != FR_OK) {
        (void)FatfsDisablePart(fat);
        return fatfs_2_vfs(ret);
    }

    return fatfs_2_vfs(ret);
}

INT fatfs_virstatfs_internel(struct inode *mountpt, const char *relpath, struct statfs *buf)
{
    char drive[MAX_LFNAME_LENTH];
    DWORD freClust, allClust;
    FATFS *fat = NULL;
    INT result, vol;

    fat = (FATFS *)mountpt->i_private;
    FAT_CHECK(fat);

    if (fat->vir_flag != FS_PARENT) {
        return -EINVAL;
    }

    vol = fatfs_get_vol(fat);
    if (vol < 0 || vol > FF_VOLUMES) {
        return -ENOENT;
    }

    if (strlen(relpath) > MAX_LFNAME_LENTH) {
        return -EFAULT;
    }

    result = snprintf_s(drive, sizeof(drive), sizeof(drive) - 1, "%d:%s", vol, relpath);
    if (result < 0) {
        return -EINVAL;
    }

    result = f_getvirfree(drive, &freClust, &allClust);
    if (result != FR_OK) {
        result = fatfs_2_vfs(result);
        goto EXIT;
    }

    (void)memset_s((void *)buf, sizeof(struct statfs), 0, sizeof(struct statfs));
    buf->f_type = MSDOS_SUPER_MAGIC;
    buf->f_bfree = freClust;
    buf->f_bavail = freClust;
    buf->f_blocks = allClust;
#if FF_MAX_SS != FF_MIN_SS
    buf->f_bsize = fat->ssize * fat->csize;
#else
    buf->f_bsize = FF_MIN_SS * fat->csize;
#endif
#if FF_USE_LFN
    buf->f_namelen = FF_MAX_LFN; /* Maximum length of filenames */
#else
    /*
     * Maximum length of filenames,'8' is the effective length, '1' is the terminator,
     * and '3' is the special length
     */
    buf->f_namelen = (8 + 1 + 3);
#endif

EXIT:
    return result;
}

#endif