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

#ifndef FS_OPERATION_H
#define FS_OPERATION_H

#include "fs/fs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* vfs/fs_file_mapping.c ****************************************************/
/****************************************************************************
 * Name: init_file_mapping
 *
 * Description:
 *   Init the global management structure of path <-> page_mapping
 *
 ****************************************************************************/

extern UINT32 init_file_mapping(void);

/****************************************************************************
 * Name: add_mapping
 *
 * Description:
 *   Create a new path <-> page_mapping mapping and add to global list.
 *
 ****************************************************************************/

extern void add_mapping(struct file *filep, const char *fullpath);

/****************************************************************************
 * Name: find_mapping
 *
 * Description:
 *   Find the page_mapping for path in global list.
 *
 ****************************************************************************/

extern struct page_mapping *find_mapping(const char *path);

/****************************************************************************
 * Name: remove_mapping
 *
 * Description:
 *   Drop all the page-caches for the file, and then remove mapping between
 *   the file and pagecache.
 *   ex_filp NULL: do not exclude any file, just matching the fullpath;
 *   ex_filp not NULL: exclude it, which means, ex_filp can be open.
 *
 ****************************************************************************/

extern int remove_mapping(const char *fullpath, const struct file *ex_filp);

/****************************************************************************
 * Name: remove_mapping_nolock
 *
 * Description:
 *   This function is similar with the function "remove_mapping" above,
 *   except that this function do not protect global file list.
 *
 ****************************************************************************/

extern int remove_mapping_nolock(const char *fullpath, const struct file *ex_filp);

/****************************************************************************
 * Name: rename_mapping
 *
 * Description:
 *   Rename the mapping from global path <-> page_mapping list.
 *
 ****************************************************************************/

extern void rename_mapping(const char *src, const char *dst);

/****************************************************************************
 * Name: dec_mapping
 *
 * Description:
 *   Decrease the refcnt of mapping.
 *
 ****************************************************************************/

extern void dec_mapping(struct page_mapping *mapping);

/**
 * @ingroup  fs
 * @brief Initializes the vfs filesystem
 *
 * @par Description:
 * This API is used to initializes the vfs filesystem
 *
 * @attention
 * <ul>
 * <li>Called only once, multiple calls will cause file system error.</li>
 * </ul>
 *
 * @param none
 *
 * @retval none
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see NULL
 */

void los_vfs_init(void);

void clear_fd(int fd);

/**
 * @ingroup  fs
 * @brief    locate character in string.
 *
 * @par Description:
 * The API function returns a pointer to the last occurrence of the character c in the string s.
 *
 * @attention
 * <ul>
 * <li>The parameter s must point a valid string, which end with the terminating null byte.</li>
 * </ul>
 *
 * @param s [IN]  Type #const char*  A pointer to string.
 * @param c [IN]  Type #int          The character.
 *
 * @retval #char*        a pointer to the matched character or NULL if the character is not found.
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see rindex
 */

extern char *rindex(const char *s, int c);

/**
 * @ingroup  fs
 * @brief   list directory contents.
 *
 * @par Description:
 * Get the volume label of the FAT partition.
 *
 * @attention
 * <ul>
 * <li>The function support FAT filesystem only.</li>
 * <li>The label must allocated more than 11 charactors space first</li>
 * </ul>
 *
 * @param target   [IN]   Type #const char*  The file pathname.
 * @param label    [OUT]  Type #const char*  The string pointer transform the label massge back.
 *
 * @retval #int  Point the status which is successed or failed.
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 */

int getlabel(const char *target, char *label);

/**
 * @ingroup fs
 *
 * @par Description:
 * The set_label() function shall set the value of a global varible,
 * the value will be used to set the label of SD card in format().
 *
 * @param name  [IN] label to set, the length must be less than 12
 *
 * @attention
 * <ul>
 * <li>The function must be called before format().</li>
 * </ul>
 *
 * @retval #void   None.
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see format
 */

extern void set_label(const char *name);

/**
 * @ingroup  fs
 * @brief formatting sd card
 *
 * @par Description:
 * formatting sd card.
 *
 * @attention
 * <ul>
 * <li>The prefix of the parameter dev must be "/dev", and the length must be less than the value defined by PATH_MAX.
 *     There are four kind of format option: FMT_FAT16, FMT_FAT32, FMT_ANY, FMT_ERASE. If users input anything else,
 *     the default format option is FMT_ANY. Format option is decided by the number of clusters. Choosing the wrong
 *     option will cause error of format. The detailed information of (FAT16,FAT32) is ff.h.
 * </li>
 * </ul>
 *
 * @param  dev          [IN] Type #const char*  path of the block device to format, which must be a really
 *                           existing block device node.
 * @param  sectors      [IN] Type #int number of sectors per cluster.
 * @param  option       [IN] Type #int option of format.
 *
 * @retval #0      Format success.
 * @retval #-1     Format failed.
 *
 * @par Dependency:
 * <ul><li>unistd.h: the header file that contains the API declaration.</li></ul>
 * @see
 *
 */

extern int format(const char *dev, int sectors, int option);

/**
 * @ingroup  fs
 * @brief   list directory contents.
 *
 * @par Description:
 * List information about the FILEs (the current directory by default).
 *
 * @attention
 * <ul>
 * <li>The total length of parameter pathname must be less than the value defined by PATH_MAX.</li>
 * </ul>
 *
 * @param pathname [IN]  Type #const char*  The file pathname.
 *
 * @retval
 * <ul>None.</ul>
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see ls
 */

extern void ls(const char *pathname);

/**
 * @ingroup  fs
 * @brief set current system time is valid or invalid for FAT file system.
 *
 * @par Description:
 * The function is used for setting current system time is valid or invalid for FAT file system.
 * The value can be set as FAT_SYSTEM_TIME_ENABLE/FAT_SYSTEM_TIME_DISABLE.
 *
 * @attention
 * <ul>
 * <li>When the system time is valid, it should set FAT_SYSTEM_TIME_ENABLE.</li>
 * <li>When the system time is invalid, it should set FAT_SYSTEM_TIME_DISABLE.</li>
 * </ul>
 *
 * @param  b_status             [IN] Type #BOOL    system time status.
 *
 * @retval #0      set status success
 * @retval #-22    Invalid argument
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see
 *
 */

extern int los_set_systime_status(BOOL b_status);

/**
 * @ingroup  fs
 * @check the three latest files in path
 *
 * @par Description:
 * The fscheck() function check the latest three files in path and subdirectories.
 * The function will fix the FAT when the file size info of directory is not matched with FAT.
 *
 * @attention
 * <ul>
 * <li>This function only support for FAT32.</li>
 * </ul>
 *
 * @param  path     [IN] Type #const char *   The path of the directory to be checked.
 *
 * @retval #0      truncate success.
 * @retval #-1     truncate failed.
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see
 *
 */

FAR int fscheck(FAR const char *path);

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
/**
 * @ingroup  fs
 * @get the virtual partitions' or free space information in virtual parition feature.
 *
 * @par Description:
 * The virstatfs() function returns the information about the a virtual partition or the free space
 * outside the virtual partition.
 *
 * @attention
 * <ul>
 * <li>This function only support for FAT32.</li>
 * <li>This function only support for the virtual partition feature.</li>
 * <li>The parameter 'buf' need to be allocate enough memeory space outside the function first.</li>
 * </ul>
 *
 * @param  path     [IN]  Type #const char *   The path which virtual partition or free space to be checked.
 * @param  buf      [OUT] Type #struct statfs *   The statfs buffer saving the information.
 *
 * @retval #0      virstatfs success.
 * @retval #-1     virstatfs failed.
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see
 *
 */

extern int virstatfs(FAR const char *path, FAR struct statfs *buf);

/**
 * @ingroup  fs
 * @set the virtual partition information.
 *
 * @par Description:
 * The los_set_virpartparam() function use for set virtual partition parameter.
 * The parameter include virtual partition number, virtual partition percent, virtual partition name
 * and the partition path which need mount virtual partition.
 *
 * @attention
 * <ul>
 * <li>This function only support for FAT32.</li>
 * <li>This function only support for the virtual partition feature.</li>
 * <li>This function only can be used before mount function.</li>
 * <li>The function can be invoked once before umount partition.</li>
 * <li>Now support set single partition,the partition information will be replaced
 * if it used for set another partition name.</li>
 * <li>The function has no effert if virtual partition information is already in the partition.</li>
 * </ul>
 *
 * @param  virtualinfo  [IN] Type #virpartinfo   The struct which include virtual partition information.
 *
 * @retval #0      los_set_virpartparam success.
 * @retval #-1     los_set_virpartparam failed.
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see
 *
 */

int los_set_virpartparam(virpartinfo virtualinfo);

#endif

/**
 * @ingroup fs
 *
 * @par Description:
 * The chattr() function shall change the mode of file named by the pathname pointed to by the path argument.
 *
 * @attention
 * <ul>
 * <li>Now only fat filesystem support this function.</li>
 * </ul>
 *
 * @retval #0  On success.
 * @retval #-1 On failure with errno set.
 *
 * @par Errors
 * <ul>
 * <li><b>EINVAL</b>: The path is a null pointer or points to an empty string.</li>
 * <li><b>ENAMETOOLONG</b>: The length of a component of a pathname is longer than {NAME_MAX}.</li>
 * <li><b>ENOENT</b>: A component of the path does not exist.</li>
 * <li><b>EPERM</b>: The entry represented by the path is a mount point.</li>
 * <li><b>ENOSYS</b>: The file system doesn't support this function.</li>
 * <li><b>EACCES</b>: It is a read-only file system.</li>
 * <li><b>ENOMEM</b>: Out of memory.</li>
 * <li><b>EIO</b>: A hard error occurred in the low level disk I/O layer or the physical drive cannot work.</li>
 * <li><b>ENODEV</b>: The device is not existed.</li>
 * </ul>
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see None
 */

extern int chattr(const char *pathname, struct IATTR *attr);


/**
 * @ingroup fs
 *
 * @par Description:
 * The LOS_BcacheSyncByName() function shall sync all the data in the cache corresponding to the disk name to the disk.
 *
 * @param name  [IN] name of the disk
 *
 * @attention
 * <ul>
 * <li>Now only fat filesystem support this function.</li>
 * </ul>
 *
 * @retval #0      On success.
 * @retval #INT32  On failure.
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see None
 */

extern INT32 LOS_BcacheSyncByName(const CHAR *name);

/**
 * @ingroup fs
 *
 * @par Description:
 * The LOS_GetDirtyRatioByName() function shall return the percentage of dirty blocks in the cache corresponding
 * to the disk name.
 *
 * @param name  [IN] name of the disk
 *
 * @attention
 * <ul>
 * <li>Now only fat filesystem support this function.</li>
 * </ul>
 *
 * @retval #INT32  the percentage of dirty blocks.
 * @retval #-1     On failure.
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see None
 */

extern INT32 LOS_GetDirtyRatioByName(const CHAR *name);

#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD
/**
 * @ingroup fs
 *
 * @par Description:
 * The LOS_SetDirtyRatioThreshold() function shall set the dirty ratio threshold of bcache. When the percentage
 * of dirty blocks in the cache is greater than the threshold, write back data to disk.
 *
 * @param dirtyRatio  [IN] Threshold of the percentage of dirty blocks, expressed in %.
 *
 * @attention
 * <ul>
 * <li>The dirtyRatio must be less than or equal to 100, or the setting is invalid.</li>
 * </ul>
 *
 * @retval #VOID  None.
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see LOS_SetSyncThreadInterval | LOS_SetSyncThreadPrio
 */

extern VOID LOS_SetDirtyRatioThreshold(UINT32 dirtyRatio);

/**
 * @ingroup fs
 *
 * @par Description:
 * The LOS_SetSyncThreadInterval() function shall set the interval for the sync thread to wake up.
 *
 * @param interval [IN] the interval time for the sync thread to wake up, in milliseconds, accuracy is 10ms.
 *
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 *
 * @retval #VOID  None.
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see LOS_SetDirtyRatioThreshold | LOS_SetSyncThreadPrio
 */

extern VOID LOS_SetSyncThreadInterval(UINT32 interval);

/**
 * @ingroup fs
 *
 * @par Description:
 * The LOS_SetSyncThreadPrio() function shall set the priority of the sync thread.
 *
 * @param prio  [IN] priority of sync thread to be set
 * @param name  [IN] name of the disk
 *
 * @attention
 * <ul>
 * <li>The prio must be less than 31 and be greater than 0, or the setting is invalid.</li>
 * <li>If the parameter name is NULL, it only set the value of a global variable, and take effect the next time the
 * thread is created. If name is not NULL and can't find the disk corresponding to name, it shall return an error.</li>
 * </ul>
 *
 * @retval #INT32  On failure.
 * @retval 0       On success.
 *
 * @par Dependency:
 * <ul><li>fs.h</li></ul>
 * @see LOS_SetDirtyRatioThreshold | LOS_SetSyncThreadInterval | LOS_TaskPriSet
 */

extern INT32 LOS_SetSyncThreadPrio(UINT32 prio, const CHAR *name);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif