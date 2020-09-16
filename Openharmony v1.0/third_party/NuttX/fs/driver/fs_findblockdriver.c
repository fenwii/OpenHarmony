/****************************************************************************
 * fs/driver/fs_findblockdriver.c
 *
 *   Copyright (C) 2008, 2017 Gregory Nutt. All rights reserved.
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

#include "sys/types.h"
#include "sys/mount.h"
#include "debug.h"
#include "errno.h"

#include "fs/fs.h"

#include "inode/inode.h"
#include "driver/driver.h"
#include "string.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

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
 *   ENOENT  - No block driver of this name is registered
 *   ENOTBLK - The inode associated with the pathname is not a block driver
 *   EACCESS - The MS_RDONLY option was not set but this driver does not
 *             support write access
 *
 ****************************************************************************/

int find_blockdriver(FAR const char *pathname, int mountflags,
                     FAR struct inode **ppinode)
{
  FAR struct inode *inode_ptr = NULL;
  int ret = 0; /* Assume success */
  struct inode_search_s desc;

  /* Sanity checks */

#ifdef CONFIG_DEBUG
  if (pathname == NULL || ppinode == NULL)
    {
      ret = -EINVAL;
      goto errout;
    }
#endif


  /* Find the inode registered with this pathname */
  SETUP_SEARCH(&desc, pathname, false);
  ret = inode_find(&desc);
  if (ret < 0)
    {
      ret = -EACCES;
      goto errout;
    }
  /* Get the search results */
  inode_ptr = desc.node;

  /* Verify that the inode is a block driver. */

  if (!INODE_IS_BLOCK(inode_ptr))
    {
      fdbg("%s is not a block driver\n", pathname);
      ret = -ENOTBLK;
      goto errout_with_inode;
    }

  /* Make sure that the inode supports the requested access */

  if (inode_ptr->u.i_bops == NULL || inode_ptr->u.i_bops->read == NULL ||
      (inode_ptr->u.i_bops->write == NULL && (mountflags & MS_RDONLY) == 0))
    {
      fdbg("%s does not support requested access\n", pathname);
      ret = -EACCES;
      goto errout_with_inode;
    }

  *ppinode = inode_ptr;
  return OK;

errout_with_inode:
  inode_release(inode_ptr);
errout:
  return ret;
}
