/****************************************************************************
 * fs/vfs/fs_open.c
 *
 *   Copyright (C) 2007-2009, 2011-2012, 2016-2018 Gregory Nutt. All rights
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "vfs_config.h"

#include "errno.h"
#include "sys/types.h"
#include "fcntl.h"
#include "sched.h"
#include "assert.h"
#ifdef LOSCFG_FILE_MODE
#include "stdarg.h"
#endif
#include "stdlib.h"
#include "fs/fs.h"

#include "inode/inode.h"
#include "driver/blockproxy.h"
#include "fs_other.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

static int oflag_convert_mode(int oflags)
{
  /* regular file operations */

  int acc_mode = 0;
  if ((oflags & O_ACCMODE) == O_RDONLY)
  acc_mode |= READ_OP;
  if (oflags & O_WRONLY)
  acc_mode |= WRITE_OP;
  if (oflags & O_RDWR)
  acc_mode |= READ_OP | WRITE_OP;

  /* Opens the file, if it is existing. If not, a new file is created. */

  if (oflags & O_CREAT)
  acc_mode |= WRITE_OP;

  /* Creates a new file. If the file is existing, it is truncated and overwritten. */

  if (oflags & O_TRUNC)
  acc_mode |= WRITE_OP;

  /* Creates a new file. The function fails if the file is already existing. */

  if (oflags & O_EXCL)
  acc_mode |= WRITE_OP;
  if (oflags & O_APPEND)
  acc_mode |= WRITE_OP;

  /* mark for executing operation */

  if (oflags & O_EXECVE)
  acc_mode |= EXEC_OP;
  return acc_mode;
}

int get_path_from_fd(int fd, char **path)
{
  FAR struct file *file     = NULL;
  char            *copypath = NULL;

  if (fd == AT_FDCWD)
    {
      return OK;
    }

  int ret = fs_getfilep(fd, &file);
  if (ret < 0)
    {
      return -ENOENT;
    }

  if ((file == NULL) || (file->f_inode == NULL) || (file->f_path == NULL))
    {
      return -EBADF;
    }

  copypath = strdup((const char*)file->f_path);
  if (copypath == NULL)
    {
      return VFS_ERROR;
    }

  char *endptr = copypath + strlen(copypath)-1;//the ptr before '\0'

  /* strip out the file name, for example:/usr/lib/xx.so, final get /usr/lib/ */
  while (endptr > copypath)
    {
      if(*endptr == '/' && endptr > copypath)
        {
          *(endptr + 1) = '\0';
          *path = copypath;
          return OK;
        }

      endptr--;
    }

  free(copypath);
  return -ENOENT;
}

int do_open(int dirfd, const char *path, int oflags, ...)
{
  FAR struct file *filep        = NULL;
  FAR struct inode *inode       = NULL;
  FAR const char *relpath       = NULL;
  char *fullpath                = NULL;
  char *relativepath            = NULL;
  struct inode_search_s desc;
#if defined(LOSCFG_FILE_MODE) || !defined(CONFIG_DISABLE_MOUNTPOINT)
  mode_t mode = DEFAULT_FILE_MODE;
#endif
  int ret;
  int fd;
  int acc_mode;
#ifdef LOSCFG_FILE_MODE
  /* If the file is opened for creation, then get the mode bits */

  if ((oflags & (O_WRONLY | O_CREAT)) != 0)
    {
      va_list ap;
      va_start(ap, oflags);
      mode = va_arg(ap, int);
      va_end(ap);
      mode &= ~GetUmask();
      mode &= (S_IRWXU|S_IRWXG|S_IRWXO);
    }
#endif

  /* Get relative path by dirfd*/
  ret = get_path_from_fd(dirfd, &relativepath);
  if (ret < 0)
    {
      ret = -ret;
      goto errout;
    }

  ret = vfs_normalize_path((const char *)relativepath, path, &fullpath);
  if (relativepath)
    {
      free(relativepath);
    }

  if (ret < 0)
    {
      ret = -ret;
      goto errout;
    }

  /* Get an inode for this file */
  SETUP_SEARCH(&desc, fullpath, false);
  ret = inode_find(&desc);
  if (ret < 0)
    {
      ret = EACCES;
      free(fullpath);
      goto errout;
    }
  inode = desc.node;
  relpath = desc.relpath;

#if !defined(CONFIG_DISABLE_MOUNTPOINT)
#ifdef LOSCFG_FS_VFS_BLOCK_DEVICE
  if (INODE_IS_BLOCK(inode))
    {
      fd = block_proxy(path, oflags);
      if (fd < 0)
        {
          ret = fd;
          goto errout_with_inode;
        }

      inode_release(inode);
      free(fullpath);
      return fd;
    }
#endif
#endif

  /* Verify that the inode is valid and either a "normal" character driver or a
   * mountpoint.  We specifically exclude block drivers and and "special"
   * inodes (semaphores, message queues, shared memory).
   */

#ifndef CONFIG_DISABLE_MOUNTPOINT
  if ((!INODE_IS_DRIVER(inode) && !INODE_IS_MOUNTPT(inode)) || !inode->u.i_ops)
#else
  if (!INODE_IS_DRIVER(inode) || !inode->u.i_ops)
#endif
    {
      ret = ENXIO;
      goto errout_with_inode;
    }

  /* Associate the inode with a file structure */

  fd = files_allocate(inode, oflags, 0, NULL, 3); /* 3: file start fd */
  if (fd < 0)
    {
      ret = EMFILE;
      goto errout_with_inode;
    }

  /* Get the file structure corresponding to the file descriptor. */

  ret = fs_getfilep(fd, &filep);
  if (ret < 0)
    {
      ret = EPERM;

      /* The errno value has already been set */
      goto errout_with_fd;
    }

  /* Perform the driver open operation.  NOTE that the open method may be
   * called many times.  The driver/mountpoint logic should handled this
   * because it may also be closed that many times.
   */

  ret = OK;
  filep->f_path = fullpath; /* The mem will free in close(fd); */
  filep->f_relpath = relpath;

  acc_mode = oflag_convert_mode(oflags);
  if (inode->u.i_ops->open)
    {
#ifndef CONFIG_DISABLE_MOUNTPOINT
      if (INODE_IS_MOUNTPT(inode))
        {
          if (VfsPermissionCheck(inode->i_uid, inode->i_gid, inode->i_mode, EXEC_OP))
            {
              ret = EACCES;
              goto errout_with_fd;
            }
          ret = inode->u.i_mops->open(filep, relpath, oflags, mode);
        }
      else
#endif
        {
          if (VfsPermissionCheck(inode->i_uid, inode->i_gid, inode->i_mode, acc_mode))
            {
              ret = EACCES;
              goto errout_with_fd;
            }
          ret = inode->u.i_ops->open(filep);
        }
    }

  if (ret < 0)
    {
      ret = -ret;
      goto errout_with_fd;
    }

  /* we do not bother to handle the NULL scenario, if so, page-cache feature will not be used
   * when we do the file fault */

  add_mapping(filep, fullpath);

  return fd;

errout_with_fd:
  files_release(fd);
errout_with_inode:
  inode_release(inode);
  free(fullpath);
errout:
  set_errno(ret);
  return VFS_ERROR;
}

/****************************************************************************
 * Name: open
 *
 * Description: Standard 'open' interface
 *
 ****************************************************************************/

int open(const char *path, int oflags, ...)
{
  mode_t mode = 0666; /* File read-write properties. */
#ifdef LOSCFG_FILE_MODE
  va_list ap;
  va_start(ap, oflags);
  mode = va_arg(ap, int);
  va_end(ap);
#endif
  return do_open(AT_FDCWD, path, oflags, mode);
}

int open64 (const char *__path, int __oflag, ...)
{
  mode_t mode = 0666; /* File read-write properties. */
#ifdef LOSCFG_FILE_MODE
  va_list ap;
  va_start(ap, __oflag);
  mode = va_arg(ap, int);
  va_end(ap);
#endif
  return open (__path, ((unsigned int)__oflag) | O_LARGEFILE, mode);
}

/****************************************************************************
 * Name: openat
 *
 * Description: open by dirfd
 *
 ****************************************************************************/

int openat(int dirfd, const char * path, int oflags, ...)
{
  mode_t mode = 0666; /* File read-write properties. */
#ifdef LOSCFG_FILE_MODE
  va_list ap;
  va_start(ap, oflags);
  mode = va_arg(ap, int);
  va_end(ap);
#endif
  return do_open(dirfd, path, oflags, mode);
}
