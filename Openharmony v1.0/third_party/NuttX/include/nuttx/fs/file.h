/****************************************************************************
 * include/fs/file.h
 *
 *   Copyright (C) 2007-2009, 2011-2013, 2015-2018 Gregory Nutt. All rights
 *     reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_FS_FILE_H
#define __INCLUDE_FS_FILE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "vfs_config.h"
#include "compiler.h"

#include "sys/types.h"
#include "stdarg.h"
#include "stdint.h"
#include "fs/fs.h"

#include "semaphore.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/****************************************************************************
 * Global Function Prototypes
 ****************************************************************************/

/* Callback used by foreach_mountpoints to traverse all mountpoints in the
 * pseudo-file system.
 */

#ifndef CONFIG_DISABLE_MOUNTPOINT
struct statfs;                    /* Forward reference */
typedef int (*foreach_mountpoint_t)(FAR const char *mountpoint,
                                    FAR struct statfs *statbuf,
                                    FAR void *arg);
#endif

struct filelist *sched_getfiles(void);

/* fs/fs_sendfile.c *************************************************/
/****************************************************************************
 * Name: sendfile
 *
 * Description:
 *   Copy data between one file descriptor and another.
 *
 ****************************************************************************/
ssize_t sendfile(int outfd, int infd, off_t *offset, size_t count);

/**
 * @ingroup  fs
 * @brief get the path by a given file fd.
 *
 * @par Description:
 * The function is used for getting the path by a given file fd.
 *
 * @attention
 * <ul>
 * <li>Only support file fd, not any dir fd.</li>
 * </ul>
 *
 * @param  fd               [IN] Type #int     file fd.
 * @param  path             [IN] Type #char ** address of the location to return the path reference.
 *
 * @retval #0      get path success
 * @retval #~0     get path failed
 *
 * @par Dependency:
 * <ul><li>fs.h: the header file that contains the API declaration.</li></ul>
 * @see
 *
 * @since 2020-1-8
 */

extern int get_path_from_fd(int fd, char **path);

/****************************************************************************
 * Name: foreach_mountpoint
 *
 * Description:
 *   Visit each mountpoint in the pseudo-file system.  The traversal is
 *   terminated when the callback 'handler' returns a non-zero value, or when
 *   all of the mountpoints have been visited.
 *
 *   This is just a front end "filter" to foreach_inode() that forwards only
 *   mountpoint inodes.  It is intended to support the mount() command to
 *   when the mount command is used to enumerate mounts.
 *
 *   NOTE 1: Use with caution... The pseudo-file system is locked throughout
 *   the traversal.
 *   NOTE 2: The search algorithm is recursive and could, in principle, use
 *   an indeterminant amount of stack space.  This will not usually be a
 *   real work issue.
 *
 * Input Parameters:
 *   handler - Operation function when find a mount point.
 *   arg - Private data.
 *
 ****************************************************************************/

#ifndef CONFIG_DISABLE_MOUNTPOINT
int foreach_mountpoint(foreach_mountpoint_t handler, FAR void *arg);
#endif

/****************************************************************************
 * Name: find_blockdriver
 *
 * Description:
 *   Return the inode of the block driver specified by 'pathname'
 *
 * Input Parameters:
 *   pathname   - The full path to the block driver to be located
 *   mountflags - If MS_RDONLY is not set, then driver must support write
 *                operations (see include/sys/mount.h)
 *   ppinode    - Address of the location to return the inode reference
 *
 * Returned Value:
 *   Returns zero on success or a negated errno on failure:
 *
 *   EINVAL  - Pathname or pinode is NULL.
 *   ENOENT  - No block driver of this name is registered
 *   ENOTBLK - The inode associated with the pathname is not a block driver
 *   EACCESS - The MS_RDONLY option was not set but this driver does not
 *             support write access
 *
 * Attention:
 *   The parameter pathname is a full path, which begin with '/'.
 *   The parameter ppinode must point a valid memory, which size must be enough for storing struct inode.
 *
 ****************************************************************************/

#if CONFIG_NFILE_DESCRIPTORS > 0
int find_blockdriver(FAR const char *pathname, int mountflags,
                     FAR struct inode **ppinode);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* __INCLUDE_FS_FILE_H */
