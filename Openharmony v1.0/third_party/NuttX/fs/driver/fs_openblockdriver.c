/****************************************************************************
 * fs/driver/fs_openblockdriver.c
 *
 *   Copyright (C) 2008-2009 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in pathname and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of pathname code must retain the above copyright
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

#include "debug.h"
#include "errno.h"
#include "fs/fs.h"

#include "inode/inode.h"
#include "driver/driver.h"
#include "disk.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: open_blockdriver
 *
 * Description:
 *   Return the inode of the block driver specified by 'pathname'
 *
 * Input Parameters:
 *   pathname - the full path to the block driver to be opened
 *   mountflags - if MS_RDONLY is not set, then driver must support write
 *     operations (see include/sys/mount.h)
 *   ppinode - address of the location to return the inode reference
 *
 * Returned Value:
 *   Returns zero on success or a negated errno on failure:
 *
 *   EINVAL  - pathname or pinode is NULL
 *   ENOENT  - No block driver of this name is registered
 *   ENOTBLK - The inode associated with the pathname is not a block driver
 *   EACCESS - The MS_RDONLY option was not set but this driver does not
 *     support write access
 *
 ****************************************************************************/

int open_blockdriver(FAR const char *pathname, int mountflags,
                     FAR struct inode **ppinode)
{
  FAR struct inode *inode_ptr = NULL;
  los_part *part = NULL;
  los_disk *disk = NULL;
  int ret;

  /* Minimal sanity checks */

#ifdef CONFIG_DEBUG
  if (ppinode == NULL)
    {
      ret = -EINVAL;
      goto errout;
    }
#endif

  /* Find the inode associated with this block driver name.  find_blockdriver
   * will perform all additional error checking.
   */

  ret = find_blockdriver(pathname, mountflags, &inode_ptr);
  if (ret < 0)
    {
      fdbg("Failed to file %s block driver\n", pathname);
      goto errout;
    }

  /* Open the block driver.  Note that no mutually exclusive access
   * to the driver is enforced here.  That must be done in the driver
   * if needed.
   */

  part = los_part_find(inode_ptr);
  if (part != NULL)
    {
      disk = get_disk(part->disk_id);
      if (disk == NULL)
        {
          ret = -EINVAL;
          goto errout_with_inode;
        }

      if (pthread_mutex_lock(&disk->disk_mutex) != ENOERR)
        {
          PRINT_ERR("%s %d, mutex lock fail!\n", __FUNCTION__, __LINE__);
          inode_release(inode_ptr);
          return -1;
        }
      if (disk->disk_status == STAT_INUSED)
        {

          if (inode_ptr->u.i_bops->open != NULL)
            {
              ret = inode_ptr->u.i_bops->open(inode_ptr);
              if (ret < 0)
                {
                  fdbg("%s driver open failed\n", pathname);
                  (void)pthread_mutex_unlock(&disk->disk_mutex);
                  goto errout_with_inode;
                }
            }
         }

      if (pthread_mutex_unlock(&disk->disk_mutex) != ENOERR)
        {
          PRINT_ERR("%s %d, mutex unlock fail!\n", __FUNCTION__, __LINE__);
          inode_release(inode_ptr);
          return -1;
        }

    }
  else
    {
      if ((inode_ptr->i_flags & FSNODEFLAG_DELETED) == 0 && inode_ptr->u.i_bops->open != NULL)
        {
          ret = inode_ptr->u.i_bops->open(inode_ptr);
          if (ret < 0)
            {
              fdbg("%s driver open failed\n", pathname);
              goto errout_with_inode;
            }
        }
    }

  *ppinode = inode_ptr;
  return OK;

errout_with_inode:
  inode_release(inode_ptr);
errout:
  return ret;
}
