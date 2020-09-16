/****************************************************************************
 * fs/inode/fs_registerreserve.c
 *
 *   Copyright (C) 2007-2009, 2011-2012, 2015, 2017 Gregory Nutt. All
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

#include "assert.h"
#include "errno.h"

#include "stdlib.h"
#include "fs/fs.h"
#include "fs/dirent_fs.h"
#include "string.h"
#include "inode/inode.h"
#include "capability_api.h"
#include "fs_other.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: check_name
 ****************************************************************************/

static bool check_name(FAR const char *name)
{
  while (*name != '\0')
    {
      if ((*name == '/') && *(name+1) != '\0')
        {
          return false;
        }
      name ++;
    }
  return true;
}

/****************************************************************************
 * Name: inode_namelen
 ****************************************************************************/

static int inode_namelen(FAR const char *name)
{
  const char *tmp = name;
  while (*tmp && *tmp != '/')
    {
      tmp++;
    }

  return tmp - name;
}

/****************************************************************************
 * Name: inode_namecpy
 ****************************************************************************/

static void inode_namecpy(char *dest, const char *src)
{
  while (*src && *src != '/')
    {
      *dest++ = *src++;
    }

  *dest = '\0';
}

/****************************************************************************
 * Name: inode_alloc
 ****************************************************************************/

static FAR struct inode *inode_alloc(FAR const char *name)
{
  FAR struct inode *node;
  int namelen;

  namelen = inode_namelen(name);
  node = (FAR struct inode*)LOS_MemAlloc(m_aucSysMem0, FSNODE_SIZE(namelen));
  if (node)
    {
      (void)memset_s(node, FSNODE_SIZE(namelen), 0, FSNODE_SIZE(namelen));
      inode_namecpy(node->i_name, name);
    }

  return node;
}

/****************************************************************************
 * Name: IsInRootfs
 ****************************************************************************/

bool IsInRootfs(const char *relpath)
{
    bool ret = true;
    char *name = NULL;
    char *path = NULL;
    struct stat statInfo;

    if ((!g_root_inode->u.i_mops) || (!g_root_inode->u.i_mops->stat)) {
        return false;
    }

    name = strdup(relpath);
    if (name) {
        path = strsep(&name, "/");
        if (g_root_inode->u.i_mops->stat(g_root_inode, path, &statInfo) == -ENOENT) {
            ret = false;
        }
        free(path);
    }

    return ret;
}

/****************************************************************************
 * Name: inode_insert
 ****************************************************************************/

static void inode_insert(FAR struct inode *node,
                         FAR struct inode *peer,
                         FAR struct inode *parent)
{
  /* If peer is non-null, then new node simply goes to the right
   * of that peer node.
   */

  if (peer)
    {
      node->i_peer = peer->i_peer;
      peer->i_peer = node;
    }

  /* If parent is non-null, then it must go at the head of its
   * list of children.
   */

  else if (parent)
    {
      node->i_peer    = parent->i_child;
      parent->i_child = node;
    }

  /* Otherwise, this must be the new root_inode */

  else
    {
      node->i_peer = g_root_inode;
      g_root_inode = node;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: inode_reserve
 *
 * Description:
 *   Reserve an (initialized) inode the pseudo file system.  The initial
 *   reference count on the new inode is zero.
 *
 * Input Parameters:
 *   path - The path to the inode to create
 *   inode - The location to return the inode pointer
 *
 * Returned Value:
 *   Zero on success (with the inode point in 'inode'); A negated errno
 *   value is returned on failure:
 *
 *   EINVAL - 'path' is invalid for this operation
 *   EEXIST - An inode already exists at 'path'
 *   ENOMEM - Failed to allocate in-memory resources for the operation
 *
 * Assumptions:
 *   Caller must hold the inode semaphore
 *
 ****************************************************************************/

int inode_reserve(FAR const char *path, FAR struct inode **inode_ptr)
{
  FAR const char   *name = path;
  FAR const char   *relpath;
  FAR struct inode *pathnode;
  FAR struct inode *left;
  FAR struct inode *parent;

  /* Assume failure */

  DEBUGASSERT(path && inode_ptr);
  *inode_ptr = NULL;

  /* Handle paths that are interpreted as the root directory */

  if (!*path || path[0] != '/')
    {
      return -EINVAL;
    }

  /* Find the location to insert the new subtree */

  pathnode = inode_search(&name, &left, &parent, &relpath);
  if (pathnode)
    {
      if (!*(relpath))
        {
          /* It is an error if the node already exists in the tree */

          return -EEXIST;
        }
#ifndef CONFIG_DISABLE_MOUNTPOINT
      else if (INODE_IS_MOUNTPT(pathnode))
        {
          if ((pathnode != g_root_inode) || IsInRootfs(relpath))
            {
              /* The node cannot be a child of a mounted point, except the root node. */

              return -EINVAL;
            }
        }
#endif
    }
  else
    {
      /* not find pathnode and the node is not g_root_inode express you have no access authority */

      if (g_root_inode != NULL)
        {
           return -EACCES;
        }
    }

  if (check_name(name) == false)
    {
      /* check the path has no '/' symbol, prevent to create multilevel directory */

      return -EINVAL;
    }

  /* Now we now where to insert the subtree */

  for (; ; )
    {
      FAR struct inode *node;

      /* Create a new node -- we need to know if this is the
       * the leaf node or some intermediary.  We can find this
       * by looking at the next name.
       */

      FAR const char *next_name = inode_nextname(name);
      if (*next_name)
        {
          /* Insert an operationless node */

          node = inode_alloc(name);
          if (node)
            {
              inode_insert(node, left, parent);

              /* Set up for the next time through the loop */

              name   = next_name;
              left   = NULL;
              parent = node;
              continue;
            }
        }
      else
        {
          node = inode_alloc(name);
          if (node)
            {
              inode_insert(node, left, parent);
              *inode_ptr = node;
              return OK;
            }
        }

      /* We get here on failures to allocate node memory */

      return -ENOMEM;
    }
}