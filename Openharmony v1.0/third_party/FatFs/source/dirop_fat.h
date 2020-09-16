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

/**
 * @defgroup fat Fat
 * @ingroup filesystem
 */

#ifndef _DIROP_FAT_H
#define _DIROP_FAT_H

#include "pthread.h"
#include "dirent.h"
#ifdef LOSCFG_FS_FAT

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TIME_LENGTH 8

struct fat_direntall {
	unsigned long	d_ino;
	unsigned long	d_off;
	unsigned char	d_type;
	unsigned int	d_size;
	char		d_createtime[TIME_LENGTH];
	unsigned short	d_reclen;
	char		d_name[1];
};

struct fat_direntall_buf {
	int	d_count;
	int	d_usecount;
	struct fat_direntall	direntall;
};

struct dirstream_fat {
	DIR		*dp;

	/* offset of the next dir entry in buffer */
	unsigned int	dd_nextloc;

	/* bytes of valid entries in buffer */
	unsigned int	dd_size;

	pthread_mutex_t	dd_lock;
};

typedef struct fat_dir{
	struct dirstream_fat		stDirStream;
	struct fat_direntall_buf	stBuf;
} DIR_FAT;

/**
 * @ingroup  fat
 * @brief open a directory
 *
 * @par Description:
 * This API is used to open a directory stream corresponding to the directory name, and
 * returns a pointer to the directory stream.
 *
 * @attention
 * <ul>
 * <li>The parameter name should be a valid string.</li>
 * </ul>
 *
 * @param  name [IN] the directory to open.
 *
 * @retval #NULL                           Open directory unsuccessfully and set errno.
 * @retval #DIR_FAT*                       A pointer to the directory stream.
 * @par Dependency:
 * <ul><li>dirop_fat.h: the header file that contains the API declaration.</li></ul>
 * @see closedir_fat
 */
DIR_FAT *opendir_fat(const char *name);

/**
 * @ingroup  fat
 * @brief close a directory
 *
 * @par Description:
 * This API is used to close the directory stream associated with dirp.
 *
 * @attention
 * <ul>
 * <li>The parameter dir_fat should be a valid pointer which opendir_fat returns.</li>
 * </ul>
 *
 * @param  dir_fat [IN] Directory object structure pointer which opendir_fat returns.
 *
 * @retval #FAT_ERROR                     The directory dirp close unsuccessfully and set errno.
 * @retval #OK                            The directory dirp close successfully.
 * @par Dependency:
 * <ul><li>dirop_fat.h: the header file that contains the API declaration.</li></ul>
 * @see opendir_fat
 */
int closedir_fat(DIR_FAT *dir_fat);

/**
 * @ingroup  fat
 * @brief read a directory
 *
 * @par Description:
 * This API is used to get a pointer to a dirent structure
 * representing the next directory entry in the directory stream pointed
 * to by dirp.
 *
 * @attention
 * <ul>
 * <li>The parameter dir_fat should be a valid pointer which opendir_fat returns.</li>
 * </ul>
 *
 * @param  dir_fat [IN] An instance of type DIR created by a previous call to opendir_fat().
 *
 * @retval #NULL                       Reaching the end of the directory stream or if an error occurred and set errno.
 * @retval #fat_direntall*             A pointer to a dirent structure.
 * @par Dependency:
 * <ul><li>dirop_fat.h: the header file that contains the API declaration.</li></ul>
 * @see opendir_fat
 */
struct fat_direntall *readdir_fat(DIR_FAT *dir_fat);

/**
* @ingroup fat
* @brief scan a directory for matching entries.
*
* @par Description:
* The scandir_fat() function scans the directory dirp, calling selector() in
* each directory entry. Entries for which selector() returns nonzero are
* stored in strings allocated via malloc, sorted using qsort with
* the comparison function compar(), and collected in array namelist
* which is allocated via malloc. If filter is NULL, all entries are
* selected, compare with scandir(), scandir_fat() can get the create-time of
* file.
*
* @attention
* <ul>
* <li></li>
* </ul>
*
* @param dir      [IN]  Type #const char* a pointer to directory information.
* @param namelist [OUT] Type #const struct fat_direntall*** a pointer to collected directory entries.
* @param selector [IN]  Type #int(*selector)(const struct fat_direntall*) a filter type function.
* @param compar   [IN]  Type #int(*compar)(const struct fat_direntall**,const struct dirent**) a compar type function.
*
* @retval #int The number of directory entries selected.
* @retval #<0  An error occurred.
* @par Dependency:
* <ul><li>dirop_fat.h: the header file that contains the API declaration.</li></ul>
* @see readdir_fat
*/
int scandir_fat(const char *dir, struct fat_direntall ***namelist,
	int (*selector) (const struct fat_direntall *),
	int (*compar) (const struct fat_direntall **, const struct fat_direntall **));

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* LOSCFG_FS_FAT */

#endif /* _DIROP_FAT_H */
