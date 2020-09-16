/****************************************************************************
 * fs/vfs/fs_read.c
 *
 *   Copyright (C) 2007-2009, 2012-2014, 2016-2017 Gregory Nutt. All rights
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
#include "sys/types.h"
#include "sys/socket.h"
#include "console.h"
#include "unistd.h"
#include "fcntl.h"
#include "sched.h"
#include "assert.h"
#include "errno.h"
#include "user_copy.h"
#include "inode/inode.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: file_read
 *
 * Description:
 *   file_read() is an interanl OS interface.  It is functionally similar to
 *   the standard read() interface except:
 *
 *    - It does not modify the errno variable,
 *    - It is not a cancellation point,
 *    - It does not handle socket descriptors, and
 *    - It accepts a file structure instance instead of file descriptor.
 *
 * Input Parameters:
 *   filep  - File structure instance
 *   buf    - User-provided to save the data
 *   nbytes - The maximum size of the user-provided buffer
 *
 * Returned Value:
 *   The positive non-zero number of bytes read on success, 0 on if an
 *   end-of-file condition, or a negated errno value on any failure.
 *
 ****************************************************************************/

ssize_t file_read(FAR struct file *filep, FAR void *buf, size_t nbytes)
{
  FAR struct inode *inode = NULL;
  int ret = -EBADF;

  DEBUGASSERT(filep);
  inode = filep->f_inode;

  if (buf == NULL)
    {
      ret = -EFAULT;
    }

  /* Was this file opened for read access? */

  else if (((unsigned int)(filep->f_oflags) & O_ACCMODE) == O_WRONLY)
    {
      /* No.. File is not read-able */

      ret = -EACCES;
    }

  /* Is a driver or mountpoint registered? If so, does it support the read
   * method?
   */

  else if (inode && inode->u.i_ops && inode->u.i_ops->read)
    {
      /* Yes.. then let it perform the read.  NOTE that for the case of the
       * mountpoint, we depend on the read methods being identical in
       * signature and position in the operations vtable.
       */

      ret = (int)inode->u.i_ops->read(filep, (char *)buf, (size_t)nbytes);
    }

  /* If an error occurred, set errno and return -1 (ERROR) */

  if (ret < 0)
    {
      set_errno(-ret);
      return VFS_ERROR;
    }

  /* Otherwise, return the number of bytes read */

  return ret;
}

/****************************************************************************
 * Name: read
 *
 * Description:
 *   The standard, POSIX read interface.
 *
 * Input Parameters:
 *   fd     - File descriptor to read from
 *   buf    - User-provided to save the data
 *   nbytes - The maximum size of the user-provided buffer
 *
 * Returned Value:
 *   The positive non-zero number of bytes read on success, 0 on if an
 *   end-of-file condition, or -1 on failure with errno set appropriately.
 *
 ****************************************************************************/

ssize_t read(int fd, FAR void *buf, size_t nbytes)
{
  /* Did we get a valid file descriptor? */

#if CONFIG_NFILE_DESCRIPTORS > 0
  FAR struct file *filep = NULL;

  if ((unsigned int)fd >= CONFIG_NFILE_DESCRIPTORS)
#endif
    {
      /* No.. If networking is enabled, read() is the same as recv() with
       * the flags parameter set to zero.
       */

#if defined(LOSCFG_NET_LWIP_SACK)
      FAR void *bufbak = buf;
      ssize_t ret;
      if (LOS_IsUserAddress((VADDR_T)(uintptr_t)buf))
        {
          if (buf != NULL && nbytes > 0)
            {
              buf = malloc(nbytes);
              if (buf == NULL)
                {
                  set_errno(ENOMEM);
                  return VFS_ERROR;
                }
            }
        }
      ret = recv(fd, buf, nbytes, 0);
      if (ret > 0 && buf != bufbak)
        {
          if (LOS_ArchCopyToUser(bufbak, buf, ret) != 0)
            {
              /* data lost here */
              set_errno(EFAULT);
              ret = VFS_ERROR;
            }
        }
      if (buf != bufbak)
        {
          free(buf);
        }
      return ret;
#else
      /* No networking... it is a bad descriptor in any event */

      set_errno(EBADF);
      return VFS_ERROR;
#endif
    }

#if CONFIG_NFILE_DESCRIPTORS > 0
  else
    {
      if (fd <= STDERR_FILENO && fd >= STDIN_FILENO) /* fd : [0,2] */
        {
          fd = ConsoleUpdateFd();
          if (fd < 0)
            {
              set_errno(EBADF);
              return VFS_ERROR;
            }
        }


      /* The descriptor is in a valid range to file descriptor... do the
       * read.  First, get the file structure.
       */

      int ret = fs_getfilep(fd, &filep);
      if (ret < 0)
        {
          /* The errno value has already been set */
          return VFS_ERROR;
        }

      if (filep->f_oflags & O_DIRECTORY)
        {
          set_errno(EBADF);
          return VFS_ERROR;
        }

      /* Then let file_read do all of the work */

      return file_read(filep, buf, nbytes);
    }
#endif
}
