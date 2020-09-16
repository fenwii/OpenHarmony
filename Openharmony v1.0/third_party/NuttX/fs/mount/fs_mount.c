/****************************************************************************
 * fs/mount/fs_mount.c
 *
 *   Copyright (C) 2007-2009, 2011-2013, 2015, 2017-2019 Gregory Nutt. All
 *     rights reserved.
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

#include "sys/mount.h"
#include "string.h"
#include "errno.h"
#include "assert.h"
#include "debug.h"

#include "fs/fs.h"

#include "inode/inode.h"
#include "stdlib.h"
#include "driver/driver.h"
#if defined(LOSCFG_FS_JFFS)
#include "mtd_partition.h"
#endif
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
#include "errcode_fat.h"
#endif
#include "los_tables.h"

/* At least one filesystem must be defined, or this file will not compile.
 * It may be desire-able to make filesystems dynamically registered at
 * some time in the future, but at present, this file needs to know about
 * every configured filesystem.
 */

#ifdef CONFIG_FS_READABLE

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Configuration ************************************************************/
/* In the canonical case, a file system is bound to a block driver.  However,
 * some less typical cases a block driver is not required.  Examples are
 * pseudo file systems (like BINFS or PROCFS) and MTD file systems (like NXFFS).
 *
 * These file systems all require block drivers:
 */

#define BLKDRVR_NOT_MOUNTED 2

extern struct fsmap_t g_fsmap[];
LOS_HAL_TABLE_BEGIN(g_fsmap, fsmap);

extern struct fsmap_t g_fsmap_end;
LOS_HAL_TABLE_END(g_fsmap_end, fsmap);

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mount_findfs
 *
 * Description:
 *    find the specified filesystem
 *
 ****************************************************************************/

static const struct fsmap_t *mount_findfs(const char *filesystemtype)
{
  struct fsmap_t *m = NULL;

  for (m = &g_fsmap[0]; m != &g_fsmap_end; ++m)
    {
      if (m->fs_filesystemtype &&
          strcmp(filesystemtype, m->fs_filesystemtype) == 0)
        {
          return m;
        }
    }

  return (const struct fsmap_t *)NULL;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mount
 *
 * Description:
 *   mount() attaches the filesystem specified by the 'source' block device
 *   name into the root file system at the path specified by 'target.'
 *
 * Return:
 *   Zero is returned on success; -1 is returned on an error and errno is
 *   set appropriately:
 *
 *   EACCES A component of a path was not searchable or mounting a read-only
 *      filesystem was attempted without giving the MS_RDONLY flag.
 *   EBUSY 'source' is already  mounted.
 *   EFAULT One of the pointer arguments points outside the user address
 *      space.
 *   EINVAL 'source' had an invalid superblock.
 *   ENODEV 'filesystemtype' not configured
 *   ENOENT A pathname was empty or had a nonexistent component.
 *   ENOMEM Could not allocate a memory to copy filenames or data into.
 *   ENOTBLK 'source' is not a block device
 *
 ****************************************************************************/

int mount(const char *source, const char *target,
          const char *filesystemtype, unsigned long mountflags,
          const void *data)
{
  int ret;
  void *fshandle = NULL;
  int errcode = 0;
  char *fullpath = NULL;
  char *fullpath_bak = NULL;

  struct inode *blkdrvr_inode = NULL;
  struct inode *mountpt_inode = NULL;
  const struct fsmap_t *fsmap = NULL;
  const struct mountpt_operations *mops = NULL;

#if defined(LOSCFG_FS_JFFS)
  mtd_partition *partition = NULL;
#endif

  if (filesystemtype == NULL)
    {
      errcode = EINVAL;
      goto errout;
    }

  /* Verify required pointer arguments */

  DEBUGASSERT(target && filesystemtype);

  ret = vfs_normalize_path((const char *)NULL, target, &fullpath);
  if (ret < 0)
    {
      PRINT_ERR("Failed to get fullpath,target: %s\n", target);
      errcode = -ret;
      goto errout;
    }
  fullpath_bak = fullpath;

  /* Find the specified filesystem.  Try the block driver file systems first */

  if ((fsmap = mount_findfs(filesystemtype)) == NULL ||
      (fsmap->is_bdfs && !source))
    {
      PRINT_ERR("Failed to find file system %s\n", filesystemtype);
      errcode = ENODEV;
      free(fullpath_bak);
      goto errout;
    }

  mops = fsmap->fs_mops;

  if (fsmap->is_bdfs && source)
    {
      /* Make sure that a block driver argument was provided */

      DEBUGASSERT(source);

      /* Find the block driver */

      ret = find_blockdriver(source, mountflags, &blkdrvr_inode);
      if (ret < 0)
        {
          PRINT_ERR("Failed to find block driver %s\n", source);
          errcode = -ret;
          free(fullpath_bak);
          goto errout;
        }
    }

  /* Insert a dummy node -- we need to hold the inode semaphore
   * to do this because we will have a momentarily bad structure.
   */

  inode_semtake();

  mountpt_inode = inode_search((const char **)&fullpath, (struct inode **)NULL, (struct inode **)NULL, \
                               (const char **)NULL);

  /* The mount point must be an existed inode. */

  if (mountpt_inode == NULL)
    {
      PRINT_ERR("Failed to find valid mountpoint %s\n", target);
      errcode = EINVAL;
      goto errout_with_semaphore;
    }

  /* The mount point must be a dangling node with no children and
   * no operations. If this inode is mounted, or it has children
   * (except "/"), or it has operations, it cannot be mounted.
   */

  if (INODE_IS_MOUNTPT(mountpt_inode) || (mountpt_inode->i_child && strcmp(target, "/")) || mountpt_inode->u.i_ops)
    {
      PRINT_ERR("Can't to mount to this inode %s\n", target);
      errcode = EINVAL;
      goto errout_with_semaphore;
    }

  mountpt_inode ->mountflags = mountflags;

  /* Bind the block driver to an instance of the file system.  The file
   * system returns a reference to some opaque, fs-dependent structure
   * that encapsulates this binding.
   */

  if (mops->bind == NULL)
    {
      /* The filesystem does not support the bind operation ??? */

      fdbg("ERROR: Filesystem does not support bind\n");
      errcode = EINVAL;
      goto errout_with_mountpt;
    }

  /* Increment reference count for the reference we pass to the file system */

  if (blkdrvr_inode != NULL)
    {
      blkdrvr_inode->i_crefs++;

      /* On failure, the bind method returns -errorcode */

      if (blkdrvr_inode->e_status != STAT_UNMOUNTED)
        {
          fdbg("ERROR: The node is busy\n");
          errcode = EBUSY;
          blkdrvr_inode->i_crefs--;
          goto errout_with_mountpt;
        }
    }
#if defined(LOSCFG_FS_JFFS)
  if (fsmap->is_mtd_support && (blkdrvr_inode != NULL))
    {
      partition = (mtd_partition *)blkdrvr_inode->i_private;
      partition->mountpoint_name = (char *)zalloc(strlen(target) + 1);
      if (partition->mountpoint_name == NULL)
        {
          errcode = ENOMEM;
          blkdrvr_inode->i_crefs--;
          goto errout_with_mountpt;
        }

      (void)strncpy_s(partition->mountpoint_name, strlen(target) + 1, target, strlen(target));
      partition->mountpoint_name[strlen(target)] = '\0';
    }
#endif
  mountpt_inode ->mountflags = mountflags;
  ret = mops->bind(blkdrvr_inode, data, &fshandle, fullpath_bak);
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
  if (ret >= VIRERR_BASE)
    {
      errcode = ret;
    }
  else
#endif
  if (ret != 0)
    {
      /* The inode is unhappy with the blkdrvr for some reason.  Back out
       * the count for the reference we failed to pass and exit with an
       * error.
       */

      fdbg("ERROR: Bind method failed: %d\n", ret);
      if (blkdrvr_inode != NULL)
        {
          blkdrvr_inode->i_crefs--;
        }

      errcode = -ret;
#if defined(LOSCFG_FS_JFFS)
      if (fsmap->is_mtd_support && (blkdrvr_inode != NULL) && (partition != NULL))
        {
          free(partition->mountpoint_name);
          partition->mountpoint_name = NULL;
        }
#endif
      goto errout_with_mountpt;
    }

  /* We have it, now populate it with driver specific information. */

  INODE_SET_MOUNTPT(mountpt_inode);

  mountpt_inode->u.i_mops  = mops;
  mountpt_inode->i_private = fshandle;
#ifdef LOSCFG_FILE_MODE
  struct stat statinfo = {0};
  if ((g_root_inode != mountpt_inode) && (stat(target, &statinfo) == 0))
    {
      mountpt_inode->i_mode = statinfo.st_mode;
      mountpt_inode->i_uid = statinfo.st_uid;
      mountpt_inode->i_gid = statinfo.st_gid;
    }

#endif

  if (blkdrvr_inode)
    {
      blkdrvr_inode->e_status = STAT_MOUNTED;
    }
  inode_semgive();

  /* We can release our reference to the blkdrver_inode, if the filesystem
   * wants to retain the blockdriver inode (which it should), then it must
   * have called inode_addref().  There is one reference on mountpt_inode
   * that will persist until umount() is called.
   */

  if (blkdrvr_inode != NULL)
    {
      inode_release(blkdrvr_inode);
    }

  free(fullpath_bak);

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
  if (errcode >= VIRERR_BASE)
    {
      set_errno(errcode);
    }
#endif

  return OK;

  /* A lot of goto's!  But they make the error handling much simpler */

errout_with_mountpt:
  (void)inode_remove(fullpath);

errout_with_semaphore:
  inode_semgive();
  if (blkdrvr_inode != NULL)
    {
      inode_release(blkdrvr_inode);
    }
  free(fullpath_bak);

errout:
  set_errno(errcode);
  return VFS_ERROR;
}

#endif /* CONFIG_FS_READABLE */
