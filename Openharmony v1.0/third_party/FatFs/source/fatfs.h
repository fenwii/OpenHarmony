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

#ifndef _FATFS_H
#define _FATFS_H

#include "fs/fs.h"
#include "disk.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/stat.h"
#include "sys/statfs.h"

#include "inode/inode.h"
#include "fs/dirent_fs.h"
#include "fcntl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define MAX_LFNAME_LENTH	256
#define LABEL_LEN		12
#define FAT32_MAXSZIE		0x100000000
#define FAT_ERROR		(-1)
extern char FatLabel[LABEL_LEN];

#define VOLUME_CHAR_LENGTH	4
#define FAT_CHECK(ptr)			\
	do {				\
		if ((ptr) == NULL)	\
			return -EINVAL;	\
	} while (0)

int fatfs_bind (struct inode *blkdriver, const void *data, void **handle, const char *realpath);
int fatfs_unbind (void *handle, struct inode **blkdriver);
int fatfs_mkfs (const char *dev, int sectors, int option);
int fatfs_statfs (struct inode *mountpt, struct statfs *buf);
int fatfs_open (struct file *filep, const char *relpath, int oflags, mode_t mode);
int fatfs_close (struct file *filep);
int fatfs_ioctl (FAR struct file *filep, int cmd, unsigned long arg);
ssize_t fatfs_read (struct file *filep, char *buffer, size_t buflen);
ssize_t fatfs_write (struct file *filep, const char *buffer, size_t buflen);
int fatfs_sync (struct file *filep);
int fatfs_virstatfs_internel (struct inode *mountpt, const char *relpath, struct statfs *buf);
int fatfs_dup (FAR const struct file *oldp, FAR struct file *newp);
off_t fatfs_seek (struct file *filep, off_t offset, int whence);
int fatfs_unlink (struct inode *mountpt, const char *relpath);
int fatfs_rename (struct inode *mountpt, const char *oldpath, const char *newpath);
int fatfs_stat (struct inode *mountpt, const char *path, struct stat *st);
int fatfs_opendir (struct inode *mountpt, const char *relpath, struct fs_dirent_s *dir);
int fatfs_closedir (struct inode *mountpt, struct fs_dirent_s *dir);
int fatfs_readdir (struct inode *mountpt, struct fs_dirent_s *dir);
int fatfs_rewinddir (struct inode *mountpt, struct fs_dirent_s *dir);
int fatfs_mkdir (struct inode *mountpt, const char *relpath, mode_t mode);
int fatfs_rmdir (struct inode *mountpt, const char *relpath);
int fatfs_utime (struct inode *mountpt, const char *pathname, const struct tm *times);
int fatfs_getlabel (void *handle, char *label);
int fatfs_2_vfs (int result);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
