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

#include "fs_other.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"
#include "unistd.h"
#include "sys/select.h"
#include "sys/stat.h"
#include "sys/prctl.h"
#include "fs/fd_table.h"
#include "fs/fs.h"
#include "linux/spinlock.h"
#include "los_process_pri.h"
#include "los_task_pri.h"
#include "inode/inode.h"
#include "capability_api.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define MAX_DIR_ENT 1024

int fstat(int fd, struct stat *buf)
{
    struct file *filep = NULL;

    int ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        return VFS_ERROR;
    }

    return stat(filep->f_path, buf);
}

int fstat64(int fd, struct stat64 *buf)
{
    struct file *filep = NULL;

    int ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        return VFS_ERROR;
    }

    return stat64(filep->f_path, buf);
}

int lstat(const char *path, struct stat *buffer)
{
    return stat(path, buffer);
}

int VfsPermissionCheck(uint fuid, uint fgid, mode_t fileMode, int accMode)
{
    uint uid = OsCurrUserGet()->effUserID;
    mode_t tmpMode = fileMode;

    if (uid == fuid) {
        tmpMode >>= USER_MODE_SHIFT;
    } else if (LOS_CheckInGroups(fgid)) {
        tmpMode >>= GROUP_MODE_SHIFT;
    }

    tmpMode &= (READ_OP | WRITE_OP | EXEC_OP);

    if ((accMode & tmpMode) == accMode) {
        return 0;
    }

    tmpMode = 0;
    if (S_ISDIR(fileMode)) {
        if ((accMode & EXEC_OP) && (IsCapPermit(CAP_DAC_READ_SEARCH))) {
            tmpMode |= EXEC_OP;
        }
    } else {
        if ((accMode & EXEC_OP) && (IsCapPermit(CAP_DAC_EXECUTE)) && (fileMode & MODE_IXUGO)) {
            tmpMode |= EXEC_OP;
        }
    }

    if ((accMode & WRITE_OP) && IsCapPermit(CAP_DAC_WRITE)) {
        tmpMode |= WRITE_OP;
    }

    if ((accMode & READ_OP) && IsCapPermit(CAP_DAC_READ_SEARCH)) {
        tmpMode |= READ_OP;
    }

    if ((accMode & tmpMode) == accMode) {
        return 0;
    }

    return 1;
}

#ifdef VFS_USING_WORKDIR
int SetWorkDir(char *dir, size_t len)
{
  errno_t ret;
  uint lock_flags;
  LosProcessCB *curr = OsCurrProcessGet();

  spin_lock_irqsave(&curr->files->workdir_lock, lock_flags);
  ret = strncpy_s(curr->files->workdir, PATH_MAX, dir, len);
  curr->files->workdir[PATH_MAX - 1] = '\0';
  spin_unlock_irqrestore(&curr->files->workdir_lock, lock_flags);
  if (ret != EOK) {
      return -1;
  }

  return 0;
}
#endif

int chdir(const char *path)
{
    int ret;
    char *fullpath = NULL;
    char *fullpath_bak = NULL;
    struct stat statBuff;

    if (!path) {
        set_errno(EFAULT);
        return -1;
    }

    if (!strlen(path)) {
        set_errno(ENOENT);
        return -1;
    }

    if (strlen(path) > PATH_MAX) {
        set_errno(ENAMETOOLONG);
        return -1;
    }

    ret = vfs_normalize_path((const char *)NULL, path, &fullpath);
    if (ret < 0) {
        set_errno(-ret);
        return -1; /* build path failed */
    }
    fullpath_bak = fullpath;
    ret = stat(fullpath, &statBuff);
    if (ret < 0) {
        free(fullpath_bak);
        return -1;
    }

    if (!S_ISDIR(statBuff.st_mode)) {
        set_errno(ENOTDIR);
        free(fullpath_bak);
        return -1;
    }

    if (VfsPermissionCheck(statBuff.st_uid, statBuff.st_gid, statBuff.st_mode, EXEC_OP)) {
        set_errno(EACCES);
        free(fullpath_bak);
        return -1;
    }

#ifdef VFS_USING_WORKDIR
    ret = SetWorkDir(fullpath, strlen(fullpath));
    if (ret != 0)
      {
        PRINT_ERR("chdir path error!\n");
        ret = -1;
      }
#endif

    /* release normalize directory path name */

    free(fullpath_bak);

    return ret;
}

/**
 * this function is a POSIX compliant version, which will return current
 * working directory.
 *
 * @param buf the returned current directory.
 * @param size the buffer size.
 *
 * @return the returned current directory.
 */

char *getcwd(char *buf, size_t n)
{
#ifdef VFS_USING_WORKDIR
    int ret;
    unsigned int len;
    UINTPTR lock_flags;
    LosProcessCB *curr = OsCurrProcessGet();
#endif
    if (buf == NULL) {
        set_errno(EINVAL);
        return buf;
    }
#ifdef VFS_USING_WORKDIR
    spin_lock_irqsave(&curr->files->workdir_lock, lock_flags);
    len = strlen(curr->files->workdir);
    if (n <= len)
      {
        set_errno(ERANGE);
        spin_unlock_irqrestore(&curr->files->workdir_lock, lock_flags);
        return NULL;
      }
    ret = memcpy_s(buf, n, curr->files->workdir, len + 1);
    if (ret != EOK)
      {
        set_errno(ENAMETOOLONG);
        spin_unlock_irqrestore(&curr->files->workdir_lock, lock_flags);
        return NULL;
      }
    spin_unlock_irqrestore(&curr->files->workdir_lock, lock_flags);
#else
    PRINT_ERR("NO_WORKING_DIR\n");
#endif

    return buf;
}

int chmod(const char *path, mode_t mode)
{
    int result;
    struct stat buf;

    result = stat(path, &buf);
    if (result != ENOERR) {
        return VFS_ERROR;
    }

    /* no access/permission control for files now, just return OK if stat is okay*/
    return OK;
}

int access(const char *path, int amode)
{
    int result;
    struct stat buf;

    result = stat(path, &buf);

    if (result != ENOERR) {
        return VFS_ERROR;
    }

    /* no access/permission control for files now, just return OK if stat is okay*/
    return OK;
}

bool IS_MOUNTPT(const char *dev)
{
    struct inode *node = NULL;
    bool ret = 0;
    struct inode_search_s desc;

    SETUP_SEARCH(&desc, dev, false);
    if (inode_find(&desc) < 0) {
        return 0;
    }
    node = desc.node;

    ret = INODE_IS_MOUNTPT(node);
    inode_release(node);
    return ret;
}

static struct dirent **scandir_get_file_list(const char *dir, int *num, int(*filter)(const struct dirent *))
{
    DIR *od = NULL;
    int listSize = MAX_DIR_ENT;
    int n = *num;
    struct dirent **list = NULL;
    struct dirent **newList = NULL;
    struct dirent *ent = NULL;
    struct dirent *p = NULL;
    int err;

    od = opendir(dir);
    if (od == NULL) {
        return NULL;
    }

    list = (struct dirent **)malloc(listSize * sizeof(struct dirent *));
    if (list == NULL) {
        (void)closedir(od);
        return NULL;
    }

    for (ent = readdir(od); ent != NULL; ent = readdir(od)) {
        if (filter && !filter(ent)) {
            continue;
        }

        if (n == listSize) {
            listSize += MAX_DIR_ENT;
            newList = (struct dirent **)malloc(listSize * sizeof(struct dirent *));
            if (newList == NULL) {
                break;
            }

            err = memcpy_s(newList, listSize * sizeof(struct dirent *), list, n * sizeof(struct dirent *));
            if (err != EOK) {
                free(newList);
                break;
            }
            free(list);
            list = newList;
        }

        p = (struct dirent *)malloc(sizeof(struct dirent));
        if (p == NULL) {
            break;
        }

        (void)memcpy_s((void *)p, sizeof(struct dirent), (void *)ent, sizeof(struct dirent));
        list[n] = p;

        n++;
    }

    if (closedir(od) < 0) {
        while (n--) {
            free(list[n]);
        }
        free(list);
        return NULL;
    }

    *num = n;
    return list;
}

int scandir(const char *dir, struct dirent ***namelist,
            int(*filter)(const struct dirent *),
            int(*compar)(const struct dirent **,
                         const struct dirent **))
{
    int n = 0;
    struct dirent **list = NULL;

    if ((dir == NULL) || (namelist == NULL)) {
        return -1;
    }

    list = scandir_get_file_list(dir, &n, filter);
    if (list == NULL) {
        return -1;
    }

    /* Change to return to the array size */

    *namelist = (struct dirent **)malloc(n * sizeof(struct dirent *));
    if (*namelist == NULL && n > 0) {
        *namelist = list;
    } else if (*namelist != NULL) {
        (void)memcpy_s(*namelist, n * sizeof(struct dirent *), list, n * sizeof(struct dirent *));
        free(list);
    } else {
        free(list);
    }

    /* Sort array */

    if (compar && *namelist) {
        qsort((void *)*namelist, (size_t)n, sizeof(struct dirent *), (int (*)(const void *, const void *))*compar);
    }

    return n;
}

int alphasort(const struct dirent **a, const struct dirent **b)
{
    return strcoll((*a)->d_name, (*b)->d_name);
}

char *rindex(const char *s, int c)
{
    if (s == NULL) {
        return NULL;
    }

    /* Don't bother tracing - strrchr can do that */
    return (char *)strrchr(s, c);
}

int (*sd_sync_fn)(int) = NULL;

int (*nand_sync_fn)(void) = NULL;

void set_sd_sync_fn(int (*sync_fn)(int))
{
    sd_sync_fn = sync_fn;
}

void sync(void)
{
#ifdef LOSCFG_FS_FAT_CACHE
    if (sd_sync_fn != NULL)
      {
        (void)sd_sync_fn(0);
        (void)sd_sync_fn(1);
      }
#endif
}

static char *ls_get_fullpath(const char *path, struct dirent *pdirent)
{
    char *fullpath = NULL;
    int ret = 0;

    if (path[1] != '\0') {
        /* 2: The position of the path character: / and the end character /0 */

        fullpath = (char *)malloc(strlen(path) + strlen(pdirent->d_name) + 2);
        if (fullpath == NULL) {
            goto exit_with_nomem;
        }

        /* 2: The position of the path character: / and the end character /0 */

        ret = snprintf_s(fullpath, strlen(path) + strlen(pdirent->d_name) + 2,
                         strlen(path) + strlen(pdirent->d_name) + 1, "%s/%s", path, pdirent->d_name);
        if (ret < 0) {
            free(fullpath);
            set_errno(ENAMETOOLONG);
            return NULL;
        }
    } else {
        /* 2: The position of the path character: / and the end character /0 */

        fullpath = (char *)malloc(strlen(pdirent->d_name) + 2);
        if (fullpath == NULL) {
            goto exit_with_nomem;
        }

        /* 2: The position of the path character: / and the end character /0 */

        ret = snprintf_s(fullpath, strlen(pdirent->d_name) + 2, strlen(pdirent->d_name) + 1,
                         "/%s", pdirent->d_name);
        if (ret < 0) {
            free(fullpath);
            set_errno(ENAMETOOLONG);
            return NULL;
        }
    }
    return fullpath;

exit_with_nomem:
    set_errno(ENOSPC);
    return (char *)NULL;
}

static void PrintFileInfo64(const struct stat64 *stat64Info, const char *name)
{
    mode_t mode;
    char str[UGO_NUMS][UGO_NUMS + 1] = {0};
    char dirFlag;
    int i;

    for (i = 0; i < UGO_NUMS; i++) {
        mode = stat64Info->st_mode >> (USER_MODE_SHIFT - i * UGO_NUMS);
        str[i][0] = (mode & READ_OP) ? 'r' : '-';
        str[i][1] = (mode & WRITE_OP) ? 'w' : '-';
        str[i][UGO_NUMS - 1] = (mode & EXEC_OP) ? 'x' : '-';
    }

    dirFlag = (S_ISDIR(stat64Info->st_mode)) ? 'd' : '-';

    PRINTK("%c%s%s%s %-8lld u:%-5d g:%-5d %-10s\n", dirFlag,
           str[0], str[1], str[UGO_NUMS - 1], stat64Info->st_size, stat64Info->st_uid, stat64Info->st_gid, name);
}

static void PrintFileInfo(const struct stat *statInfo, const char *name)
{
    mode_t mode;
    char str[UGO_NUMS][UGO_NUMS + 1] = {0};
    char dirFlag;
    int i;

    for (i = 0; i < UGO_NUMS; i++) {
        mode = statInfo->st_mode >> (USER_MODE_SHIFT - i * UGO_NUMS);
        str[i][0] = (mode & READ_OP) ? 'r' : '-';
        str[i][1] = (mode & WRITE_OP) ? 'w' : '-';
        str[i][UGO_NUMS - 1] = (mode & EXEC_OP) ? 'x' : '-';
    }

    dirFlag = (S_ISDIR(statInfo->st_mode)) ? 'd' : '-';

    PRINTK("%c%s%s%s %-8lld u:%-5d g:%-5d %-10s\n", dirFlag,
           str[0], str[1], str[UGO_NUMS - 1], statInfo->st_size, statInfo->st_uid, statInfo->st_gid, name);
}

void ls(const char *pathname)
{
    struct stat64 stat64_info;
    struct stat stat_info;
    struct dirent *pdirent = NULL;
    char *path = NULL;
    char *fullpath = NULL;
    char *fullpath_bak = NULL;
    int ret;
    DIR *d = NULL;

    if (pathname == NULL) {
#ifdef VFS_USING_WORKDIR
        UINTPTR lock_flags;
        LosProcessCB *curr = OsCurrProcessGet();

        /* open current working directory */

        spin_lock_irqsave(&curr->files->workdir_lock, lock_flags);
        path = strdup(curr->files->workdir);
        spin_unlock_irqrestore(&curr->files->workdir_lock, lock_flags);
#else
        path = strdup("/");
#endif
        if (path == NULL) {
            return;
        }
    } else {
        ret = vfs_normalize_path(NULL, pathname, &path);
        if (ret < 0) {
            set_errno(-ret);
            return;
        }
    }

    /* list all directory and file*/

    d = opendir(path);
    if (d == NULL) {
        perror("ls error");
    } else {
        PRINTK("Directory %s:\n", path);
        do {
            pdirent = readdir(d);
            if (pdirent == NULL) {
                break;
            } else {
                if (!strcmp(pdirent->d_name, ".") || !strcmp(pdirent->d_name, "..")) {
                    continue;
                }
                (void)memset_s(&stat_info, sizeof(struct stat), 0, sizeof(struct stat));
                fullpath = ls_get_fullpath(path, pdirent);
                if (fullpath == NULL) {
                    free(path);
                    (void)closedir(d);
                    return;
                }

                fullpath_bak = fullpath;
                if (stat64(fullpath, &stat64_info) == 0) {
                    PrintFileInfo64(&stat64_info, pdirent->d_name);
                } else if (stat(fullpath, &stat_info) == 0) {
                    PrintFileInfo(&stat_info, pdirent->d_name);
                } else
                    PRINTK("BAD file: %s\n", pdirent->d_name);
                free(fullpath_bak);
            }
        } while (1);

        (void)closedir(d);
    }
    free(path);

    return;
}


char *realpath(const char *path, char *resolved_path)
{
    int ret, result;
    char *new_path = NULL;
    struct stat buf;

    ret = vfs_normalize_path(NULL, path, &new_path);
    if (ret < 0) {
        ret = -ret;
        set_errno(ret);
        return NULL;
    }

    result = stat(new_path, &buf);

    if (resolved_path == NULL) {
        if (result != ENOERR) {
            free(new_path);
            return NULL;
        }
        return new_path;
    }

    ret = strcpy_s(resolved_path, PATH_MAX, new_path);
    if (ret != EOK) {
        ret = -ret;
        set_errno(ret);
        free(new_path);
        return NULL;
    }

    free(new_path);
    if (result != ENOERR) {
        return NULL;
    }
    return resolved_path;
}

void lsfd(void)
{
    FAR struct filelist *f_list = NULL;
    unsigned int i = 3; /* file start fd */
    int ret;
    FAR struct inode *node = NULL;

    f_list = &tg_filelist;

    PRINTK("   fd    filename\n");
    ret = sem_wait(&f_list->fl_sem);
    if (ret < 0) {
        PRINTK("sem_wait error, ret=%d\n", ret);
        return;
    }

    while (i < CONFIG_NFILE_DESCRIPTORS) {
        node = files_get_openfile(i);
        if (node) {
            PRINTK("%5d   %s\n", i, f_list->fl_files[i].f_path);
        }
        i++;
    }
    (void)sem_post(&f_list->fl_sem);
}

mode_t GetUmask(void)
{
    return OsCurrProcessGet()->umask;
}

mode_t SysUmask(mode_t mask)
{
    UINT32 intSave;
    mode_t umask;
    mode_t oldUmask;
    umask = mask & UMASK_FULL;
    SCHEDULER_LOCK(intSave);
    oldUmask = OsCurrProcessGet()->umask;
    OsCurrProcessGet()->umask = umask;
    SCHEDULER_UNLOCK(intSave);
    return oldUmask;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
