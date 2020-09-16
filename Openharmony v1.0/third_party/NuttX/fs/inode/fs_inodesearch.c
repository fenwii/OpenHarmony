/****************************************************************************
 * fs/inode/fs_inodesearch.c
 *
 *   Copyright (C) 2007-2009, 2011-2012, 2016-2017 Gregory Nutt. All rights reserved.
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
#include "semaphore.h"
#include "stdlib.h"
#include "fs/fs.h"

#include "fs_other.h"
#include "inode/inode.h"
/****************************************************************************
 * Public Data
 ****************************************************************************/

FAR struct inode *g_root_inode = NULL;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: _inode_compare
 *
 * Description:
 *   Compare two inode names
 *
 ****************************************************************************/

static int _inode_compare(FAR const char *fname, FAR struct inode *node)
{
  char *nname = node->i_name;

  if (!nname)
    {
      return 1;
    }

  if (!fname)
    {
      return -1;
    }

  for (; ; )
    {
      /* At the end of the node name? */

      if (!*nname)
        {
          /* Yes.. also at the end of find name? */

          if (!*fname || *fname == '/')
            {
              /* Yes.. return match */

              return 0;
            }
          else
            {
              /* No... return find name > node name */

              return 1;
            }
        }

      /* At end of the find name? */

      else if (!*fname || *fname == '/')
        {
          /* Yes... return find name < node name */

          return -1;
        }

      /* Check for non-matching characters */

      else if (*fname > *nname)
        {
          return 1;
        }
      else if (*fname < *nname)
        {
          return -1;
        }

      /* Not at the end of either string and all of the
       * characters still match.  keep looking.
       */

      else
        {
          fname++;
          nname++;
        }
    }
}



/****************************************************************************
 * Name: inode_search
 *
 * Description:
 *   Find the inode associated with 'path' returning the inode references
 *   and references to its companion nodes.
 *
 * Assumptions:
 *   The caller holds the g_inode_sem semaphore
 *
 * TODO: Nuttx 8.2 inode_search() uses struct inode_search_s as parameter
 ****************************************************************************/

FAR struct inode *inode_search(FAR const char **path,
                                      FAR struct inode **peer,
                                      FAR struct inode **parent,
                                      FAR const char **relpath)
{
  FAR const char   *name  = *path;
  FAR struct inode *ret_inode = NULL;
  FAR struct inode *node  = g_root_inode;
  FAR struct inode *left  = NULL;
  FAR struct inode *above = NULL;

  while (node)
    {
      int result = _inode_compare(name, node);

      /* Case 1:  The name is less than the name of the node.
       * Since the names are ordered, these means that there
       * is no peer node with this name and that there can be
       * no match in the fileystem.
       */

      if (result < 0)
        {
          node = NULL;
          break;
        }

      /* Case 2: the name is greater than the name of the node.
       * In this case, the name may still be in the list to the
       * "right"
       */

      else if (result > 0)
        {
          left = node;
          node = node->i_peer;
        }

      /* The names match */

      else
        {
          /* Now there are three more possibilities:
           *   (1) This is the node that we are looking for or,
           *   (2) The node we are looking for is "below" this one.
           *   (3) This node is a mountpoint and will absorb all request
           *       below this one
           */

          name = inode_nextname(name);

          if (!INODE_IS_MOUNTPT(g_root_inode))
          {
            /* This g_root_inode is not a mountpoint and will handle the
              * remaining part of the pathname
              */

            if (relpath != NULL)
              {
                ret_inode = node;
                *relpath = name;
              }
          }

          if (INODE_IS_MOUNTPT(node))
            {
              /* This node is a mountpoint and will handle the
               * remaining part of the pathname
               */

              if (relpath != NULL)
                {
                  ret_inode = node;
                  *relpath = name;
                }
            }

          if (!*name)
            {
              /* We are at the end of the path, so this must be the
               * node we are looking for
               */
              ret_inode = node;
              if (relpath != NULL)
                {
                  *relpath = name;
                }
              break;
            }
          else
            {
              /* More to go, keep looking at the next level "down" */
              above = node;
              left  = NULL;
              if ((g_root_inode != NULL) && VfsPermissionCheck(node->i_uid, node->i_gid, node->i_mode, EXEC_OP))
                {
                  /* If g_root_inode has set and node has not execution authority, while break */

                  ret_inode = NULL;
                  node = NULL;
                  break;
                }

              node = node->i_child;
            }
        }
    }

  /* The node may or may not be null as per one of the following four cases
   * cases:
   *
   * With node = NULL
   *
   *   (1) We went left past the final peer:  The new node name is larger
   *       than any existing node name at that level.
   *   (2) We broke out in the middle of the list of peers because the name
   *       was not found in the ordered list.
   *   (3) We went down past the final parent:  The new node name is
   *       "deeper" than anything that we currently have in the tree.
   *
   * With node != NULL
   *
   *   (4) When the node matching the full path is found
   */

  if (peer != NULL)
    {
      *peer = left;
    }

  if (parent != NULL)
    {
      *parent = above;
    }

  *path = name;
  return ret_inode;
}

/****************************************************************************
 * Name: inode_free
 *
 * Description:
 *   Free resources used by an inode
 *
 ****************************************************************************/

void inode_free(FAR struct inode *node)
{
  if (node != NULL)
    {
      inode_free(node->i_peer);
      inode_free(node->i_child);
      (VOID)LOS_MemFree(m_aucSysMem0, node);
    }
}

/****************************************************************************
 * Name: inode_nextname
 *
 * Description:
 *   Given a path with node names separated by '/', return the next path
 *   segment name.
 *
 ****************************************************************************/

FAR const char *inode_nextname(FAR const char *name)
{
  /* Search for the '/' delimiter or the NUL terminator at the end of the
   * path segment.
   */

  while (*name != '\0' && *name != '/')
    {
      name++;
    }

  /* If we found the '/' delimiter, then the path segment we want begins at
   * the next character (which might also be the NUL terminator).
   */

  while (*name == '/')
    {
      name++;
    }

  return name;
}
