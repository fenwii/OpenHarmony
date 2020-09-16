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

#include "dirop_fat.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "integer.h"
#include "inode/inode.h"
#include "fs/fs.h"
#include "fatfs.h"

#ifdef LOSCFG_FS_FAT

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif	/* __cplusplus */

extern const struct mountpt_operations fat_operations;
#define SECTOR_SIZE		512
#define FIRST_MALLOC_SIZE	10

static INT vfat_check_path(const char *path)
{
	struct inode *inode_ptr = NULL;
	char *fullpath = NULL;
	INT ret = vfs_normalize_path((const char *)NULL, path, &fullpath);
	struct inode_search_s desc;

	if (ret < ENOERR) {
		ret = -ret;
		set_errno(ret);
		return FAT_ERROR;
	}

	SETUP_SEARCH(&desc, fullpath, false);
	ret = inode_find(&desc);
	if (ret < 0) {
		PRINT_ERR("ERROR: Failed to find %s\n", fullpath);
		ret = -ret;
		set_errno(ret);
		return FAT_ERROR;
	}
	inode_ptr = desc.node;

	free(fullpath);

	if (inode_ptr && (inode_ptr->u.i_mops == &fat_operations)) {
		inode_release(inode_ptr);
		return ENOERR;
	}

	return FAT_ERROR;
}

static DIR_FAT *initdir_fat(DIR *dp)
{
	DIR_FAT *dir_fat = NULL;

	if (dp != NULL) {
		dir_fat = (DIR_FAT *)malloc(sizeof(DIR_FAT) + PATH_MAX);
		if (dir_fat != NULL) {
			(void)memset_s(dir_fat, sizeof(DIR_FAT) + PATH_MAX, 0, sizeof(DIR_FAT) + PATH_MAX);

			dir_fat->stDirStream.dd_nextloc = 0;
			dir_fat->stDirStream.dd_size = 0;
			dir_fat->stBuf.d_count = SECTOR_SIZE;
			dir_fat->stBuf.d_usecount = 0;

			(void)pthread_mutex_init(&(dir_fat->stDirStream.dd_lock), (const pthread_mutexattr_t *)NULL);
			dir_fat->stDirStream.dp = dp;

			return dir_fat;
		}

	(void)closedir(dp);
	}

	return NULL;
}

DIR_FAT *opendir_fat(const char *name)
{
	INT ret;
	DIR *dp = NULL;

	ret = vfat_check_path(name);
	if (ret) {
		return NULL;
	}

	dp = opendir(name);

	return initdir_fat(dp);
}

int closedir_fat(DIR_FAT *dir_fat)
{
	INT ret;

	if (dir_fat == NULL) {
		return FAT_ERROR;
	}

	ret = closedir(dir_fat->stDirStream.dp);
	if (ret == ENOERR) {
		(void)pthread_mutex_destroy(&(dir_fat->stDirStream.dd_lock));
		free(dir_fat);
	}

	return ret;
}

extern int fatfs_readdir_all(DIR_FAT *dir_fat);

struct fat_direntall *readdir_fat(DIR_FAT *dir_fat)
{
	INT ret;
	struct fat_direntall *de = (struct fat_direntall *)NULL;

	if (dir_fat == NULL) {
		return NULL;
	}

	if (pthread_mutex_lock(&(dir_fat->stDirStream.dd_lock)) != ENOERR) {
		return NULL;
	}

	ret = fatfs_readdir_all(dir_fat);
	if (!ret) {
		de = &(dir_fat->stBuf.direntall);
	}

	if (pthread_mutex_unlock(&(dir_fat->stDirStream.dd_lock)) != ENOERR)
		PRINT_ERR("readdir_fat mutex unlock error \n");
	return de;
}

static struct fat_direntall **scandir_fat_remalloc_names(struct fat_direntall **names,
	UINT *names_size, UINT pos, bool *failed)
{
	struct fat_direntall **new_direntall = NULL;
	INT32 ret;

	if (pos == *names_size) {

		if (*names_size == 0) {
			*names_size = FIRST_MALLOC_SIZE;
		} else {
			*names_size <<= 1;
		}

		new_direntall = (struct fat_direntall **)malloc(*names_size * sizeof(struct fat_direntall *));
		if (new_direntall == NULL) {
			*failed = 1;
			return  names;
		}

		if (names != NULL) {
			ret = memcpy_s(new_direntall, (*names_size) * sizeof(struct fat_direntall *),
				names, pos * sizeof(struct fat_direntall *));
			if (ret != EOK){
				*failed = 1;
				free(new_direntall);
				return names;
			}
			free(names);
		}
		return new_direntall;
	}
	return names;
}

int scandir_fat(const char *dir, struct fat_direntall ***namelist,
	int (*selector) (const struct fat_direntall *),
	int (*compar) (const struct fat_direntall **, const struct fat_direntall **))
{
	DIR_FAT *dp = opendir_fat(dir);
	struct fat_direntall *current = NULL;
	struct fat_direntall **names = NULL;
	struct fat_direntall *vnew = NULL;
	UINT names_size = 0;
	UINT pos = 0;
	UINT dsize;
	bool failed = 0;
	INT use_it;

	if (dp == NULL) {
		return FAT_ERROR;
	}

	current = readdir_fat(dp);
	while (current != NULL) {
		use_it = (selector == NULL);
		if (!use_it) {
			use_it = (*selector) (current);
		}
		if (use_it) {
			names = scandir_fat_remalloc_names(names, &names_size, pos, &failed);
			if (failed == 1) {
				break;
			}

			dsize = current->d_reclen;
			vnew = (struct fat_direntall *)malloc(dsize);
			if (vnew == NULL) {
				failed = 1;
			    break;
			}

			(void)memcpy_s(vnew, dsize, current, dsize);
			names[pos++] = vnew;
		}
		current = readdir_fat(dp);
	}

	if (failed == 1) {
		(void)closedir_fat(dp);
		while (pos > 0) {
			free(names[--pos]);
		}

		if (names != NULL) {
			free(names);
		}

		return FAT_ERROR;
	}

	(void)closedir_fat(dp);

	/* Sort the list if we have a comparison function to sort with.  */
	if (compar != NULL && names != NULL) {
		qsort((void *)names, pos, sizeof (struct fat_direntall *), (int (*)(const void *, const void *))*compar);
	}
	*namelist = names;
	return pos;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif	/* __cplusplus */
#endif	/* CONFIG_FS_FAT */
