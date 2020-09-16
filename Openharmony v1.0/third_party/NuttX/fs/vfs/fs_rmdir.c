/****************************************************************************
 * fs/vfs/fs_rmdir.c
 *
 *   Copyright (C) 2007-2009, 2014, 2017 Gregory Nutt. All rights reserved.
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "vfs_config.h"

#include "unistd.h"
#include "errno.h"
#include "fs/fs.h"
#include "stdlib.h"
#include "inode/inode.h"
#include "sys/stat.h"
#include "string.h"
#include "fs_other.h"
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#undef FS_HAVE_WRITABLE_MOUNTPOINT
#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_FS_WRITABLE) && \
    CONFIG_NFILE_STREAMS > 0
#  define FS_HAVE_WRITABLE_MOUNTPOINT 1
#endif

#undef FS_HAVE_PSEUDOFS_OPERATIONS
#if !defined(CONFIG_DISABLE_PSEUDOFS_OPERATIONS) && CONFIG_NFILE_STREAMS > 0
#  define FS_HAVE_PSEUDOFS_OPERATIONS 1
#endif

#undef FS_HAVE_RMDIR
#if defined(FS_HAVE_WRITABLE_MOUNTPOINT) || defined(FS_HAVE_PSEUDOFS_OPERATIONS)
#  define FS_HAVE_RMDIR 1
#endif

#ifdef FS_HAVE_RMDIR

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: do_rmdir
 *
 * Description:  Remove a file managed a mountpoint
 *
 ****************************************************************************/

int do_rmdir(int dirfd, FAR const char *pathname)
{
  FAR struct inode *inode;
  const char       *relpath      = NULL;
  int               errcode;
  char             *fullpath     = NULL;
  char             *relativepath = NULL;
  int               ret;
  struct inode_search_s desc;

  /* Get relative path by dirfd*/
  ret = get_path_from_fd(dirfd, &relativepath);
  if (ret < 0)
    {
      errcode = ret;
      goto errout;
    }

  ret = vfs_normalize_path((const char *)relativepath, pathname, &fullpath);
  if (relativepath)
    {
      free(relativepath);
    }

  if (ret < 0)
    {
      errcode = -ret;
      goto errout;
    }

  /* Get an inode for this file.  inode_find() automatically increments the
   * reference count on the inode if one is found.
   */
  SETUP_SEARCH(&desc, fullpath, false);
  ret = inode_find(&desc);
  if (ret < 0)
    {
      free(fullpath);
      errcode = EACCES;
      goto errout;
    }
  inode = desc.node;
  relpath = desc.relpath;

#ifndef CONFIG_DISABLE_MOUNTPOINT
  /* Check if the inode is a valid mountpoint. */

  if (INODE_IS_MOUNTPT(inode) && inode->u.i_mops)
    {
      /* Perform the rmdir operation using the relative path
       * from the mountpoint.
       */

      if (inode->u.i_mops->rmdir)
        {
          if (!strlen(relpath))
            {
              errcode = EPERM;
              goto errout_with_inode;
            }

          ret = inode->u.i_mops->rmdir(inode, relpath);
          if (ret < 0)
            {
              errcode = -ret;
              goto errout_with_inode;
            }
        }
      else
        {
          errcode = ENOSYS;
          goto errout_with_inode;
        }
    }
  else
#endif

#ifndef CONFIG_DISABLE_PSEUDOFS_OPERATIONS
  /* If this is a "dangling" pseudo-directory node (i.e., it has no
   * operations) then rmdir should remove the node.
   */

  if (!inode->u.i_ops)
    {
      /* If the directory inode has children, however, then it cannot be
       * removed.
       */

      if (inode->i_child)
        {
          errcode = ENOTEMPTY;
          goto errout_with_inode;
        }

      /* Remove the inode.  NOTE: Because we hold a reference count on the
       * inode, it will not be deleted now.  But probably when inode_release()
       * is called below.  inode_remove should return -EBUSY to indicate that
       * the inode was not deleted now.
       */
      if (VfsPermissionCheck(desc.parent->i_uid, desc.parent->i_gid, desc.parent->i_mode, EXEC_OP | WRITE_OP))
        {
          errcode = EACCES;
          goto errout_with_inode;
        }
      inode_semtake();
      ret = inode_remove(fullpath);
      inode_semgive();

      if (ret < 0 && ret != -EBUSY)
        {
          errcode = -ret;
          goto errout_with_inode;
        }
    }
  else
    {
      errcode = ENOTDIR;
      goto errout_with_inode;
    }
#else
    {
      errcode = ENXIO;
      goto errout_with_inode;
    }
#endif

  /* Successfully removed the directory */

  inode_release(inode);
  free(fullpath);
  return OK;

errout_with_inode:
  inode_release(inode);
  free(fullpath);
errout:
  set_errno(errcode);
  return VFS_ERROR;
}

/****************************************************************************
 * Name: rmdir
 *
 * Description:  Remove a file managed a mountpoint
 *
 ****************************************************************************/

int rmdir(FAR const char *pathname)
{
  return do_rmdir(AT_FDCWD, pathname);
}

#endif /* FS_HAVE_RMDIR */
