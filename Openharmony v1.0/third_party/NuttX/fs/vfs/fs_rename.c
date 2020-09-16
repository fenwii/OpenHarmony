/****************************************************************************
 * fs/vfs/fs_rename.c
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

#include "stdio.h"
#include "errno.h"
#include "fs/fs.h"
#include "stdlib.h"
#include "inode/inode.h"
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

#undef FS_HAVE_RENAME
#if defined(FS_HAVE_WRITABLE_MOUNTPOINT) || defined(FS_HAVE_PSEUDOFS_OPERATIONS)
#  define FS_HAVE_RENAME 1
#endif

#ifdef FS_HAVE_RENAME

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int do_rename(int oldfd, FAR const char *oldpath, int newfd, FAR const char *newpath)
{
  FAR struct inode *oldinode;
  FAR struct inode *newinode;
  const char       *oldrelpath      = NULL;
  char             *fulloldpath     = NULL;
  char             *fulloldpath_bak = NULL;
  char             *fullnewpath     = NULL;
  char             *fullnewpath_bak = NULL;
#ifndef CONFIG_DISABLE_MOUNTPOINT
  const char       *newrelpath      = NULL;
#endif
  int               errcode         = ENOERR;
  int               ret;
  struct inode_search_s old_desc, new_desc;

  /* Ignore paths that are interpreted as the root directory which has no name
   * and cannot be moved
   */

  if (!oldpath || *oldpath == '\0' ||
      !newpath || *newpath == '\0')
    {
      errcode = EINVAL;
      goto errout;
    }

  ret = vfs_normalize_pathat(oldfd, oldpath, &fulloldpath);
  if (ret < 0)
   {
     errcode = -ret;
     goto errout;
   }
  fulloldpath_bak = fulloldpath;

  ret = vfs_normalize_pathat(newfd, newpath, &fullnewpath);
  if (ret < 0)
   {
     errcode = -ret;
     goto errout_with_path;
   }
  fullnewpath_bak = fullnewpath;

  /* Get an inode that includes the oldpath */
  SETUP_SEARCH(&old_desc, fulloldpath, false);
  ret = inode_find(&old_desc);
  if (ret < 0)
    {
      errcode = EACCES;
      free(fullnewpath_bak);
      goto errout_with_path;
    }
  oldinode = old_desc.node;
  oldrelpath = old_desc.relpath;

#ifndef CONFIG_DISABLE_MOUNTPOINT
  /* Verify that the old inode is a valid mountpoint. */

  if (INODE_IS_MOUNTPT(oldinode) && oldinode->u.i_mops)
    {
      /* Get an inode for the new relpath -- it should like on the same
       * mountpoint
       */
      SETUP_SEARCH(&new_desc, fullnewpath, false);
      ret = inode_find(&new_desc);
      if (ret < 0)
        {
          errcode = EACCES;
          goto errout_with_oldinode;
        }
      newinode = new_desc.node;
      newrelpath = new_desc.relpath;

      /* Verify that the two paths lie on the same mountpoint inode */

      if (oldinode != newinode)
        {
          errcode = EXDEV;
          goto errout_with_newinode;
        }

      /* Perform the rename operation using the relative paths
       * at the common mountpoint.
       */

      if (oldinode->u.i_mops->rename)
        {
          ret = oldinode->u.i_mops->rename(oldinode, oldrelpath, newrelpath);
          if (ret < 0)
            {
              errcode = -ret;
              goto errout_with_newinode;
            }
        }
      else
        {
          errcode = ENOSYS;
          goto errout_with_newinode;
        }

      /* Successfully renamed */

      inode_release(newinode);
    }
  else
#endif
#ifndef CONFIG_DISABLE_PSEUDOFS_OPERATIONS
    {
      /* Create a new, empty inode at the destination location */
      if (VfsPermissionCheck(old_desc.parent->i_uid, old_desc.parent->i_gid,
                              old_desc.parent->i_mode, EXEC_OP | WRITE_OP))
        {
          ret = EACCES;
          goto errout_with_oldinode;
        }
      SETUP_SEARCH(&new_desc, fullnewpath, false);
      ret = inode_find(&new_desc);
      if (ret < 0)
        {
          errcode = EACCES;
          goto errout_with_oldinode;
        }
      newinode = new_desc.node;
      newrelpath = new_desc.relpath;

      if (VfsPermissionCheck(new_desc.parent->i_uid, new_desc.parent->i_gid,
                              new_desc.parent->i_mode, EXEC_OP | WRITE_OP))
        {
          ret = EACCES;
          goto errout_with_oldinode;
        }
      inode_semtake();
      ret = inode_reserve(fullnewpath, &newinode);
      if (ret < 0)
        {
          /* It is an error if a node at newpath already exists in the tree
           * OR if we fail to allocate memory for the new inode (and possibly
           * any new intermediate path segments).
           */

          inode_semgive();
          errcode = EEXIST;
          goto errout_with_oldinode;
        }

      /* Copy the inode state from the old inode to the newly allocated inode */

      newinode->i_child   = oldinode->i_child;   /* Link to lower level inode */
      newinode->i_flags   = oldinode->i_flags;   /* Flags for inode */
      newinode->u.i_ops   = oldinode->u.i_ops;   /* Inode operations */
#ifdef LOSCFG_FILE_MODE
      newinode->i_mode    = oldinode->i_mode;    /* Access mode flags */
#endif
      newinode->i_private = oldinode->i_private; /* Per inode driver private data */

      /* We now have two copies of the inode.  One with a reference count of
       * zero (the new one), and one that may have multiple references
       * including one by this logic (the old one)
       *
       * Remove the old inode.  Because we hold a reference count on the
       * inode, it will not be deleted now.  It will be deleted when all of
       * the references to to the inode have been released (perhaps when
       * inode_release() is called below).  inode_remove() should return
       * -EBUSY to indicate that the inode was not deleted now.
       */

      ret = inode_remove(fulloldpath);
      if (ret < 0 && ret != -EBUSY)
        {
          /* Remove the new node we just recreated */

          (void)inode_remove(fullnewpath);
          inode_semgive();

          errcode = -ret;
          goto errout_with_oldinode;
        }

      /* Remove all of the children from the unlinked inode */

      oldinode->i_child = NULL;
      inode_semgive();
    }
#else
    {
      errcode = ENXIO;
      goto errout_with_oldinode;
    }
#endif

  /* rename file page cache mapping if necessary */

  rename_mapping(fulloldpath, fullnewpath);

  /* Successfully renamed */

  inode_release(oldinode);
  free(fulloldpath_bak);
  free(fullnewpath_bak);

  return OK;

#ifndef CONFIG_DISABLE_MOUNTPOINT
errout_with_newinode:
  inode_release(newinode);
#endif
errout_with_oldinode:
  inode_release(oldinode);
  free(fullnewpath_bak);
errout_with_path:
  free(fulloldpath_bak);
errout:
  set_errno(errcode);
  return VFS_ERROR;
}

/****************************************************************************
 * Name: rename
 *
 * Description:  Rename a file managed a mountpoint
 *
 ****************************************************************************/

int rename(FAR const char *oldpath, FAR const char *newpath)
{
  return do_rename(AT_FDCWD, oldpath, AT_FDCWD, newpath);
}

/****************************************************************************
 * Name: renameat
 *
 * Description:  Rename a file managed a mountpoint with relatively fds.
 *
 ****************************************************************************/

int renameat(int oldfd, FAR const char *oldpath, int newdfd, FAR const char *newpath)
{
  return do_rename(oldfd, oldpath, newdfd, newpath);
}

#endif /* FS_HAVE_RENAME */
