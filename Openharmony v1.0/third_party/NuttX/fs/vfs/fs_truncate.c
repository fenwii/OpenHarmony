/****************************************************************************
 * fs/vfs/fs_truncate.c
 *
 *   Copyright (C) 2018 Gregory Nutt. All rights reserved.
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
#include "unistd.h"
#include "fcntl.h"
#include "sched.h"
#include "assert.h"
#include "errno.h"

#include "inode/inode.h"

/****************************************************************************
 * Name: file_truncate
 *
 * Description:
 *   Equivalent to the standard ftruncate() function except that is accepts
 *   a struct file instance instead of a file descriptor and it does not set
 *   the errno variable.
 *
 ****************************************************************************/
static int file_truncate(FAR struct file *filep, off_t length)
{
  FAR struct inode *inode = NULL;
  int ret;
  int err;

  /* Was this file opened for write access? */

  if (((unsigned int)(filep->f_oflags) & O_ACCMODE) == O_RDONLY)
    {
      err = EACCES;
      goto errout;
    }

  /* Is this inode a registered mountpoint? Does it support the
   * truncate operations may be relevant to device drivers but only
   * the mountpoint operations vtable contains a truncate method.
   */

  inode = filep->f_inode;
  if (!inode || !inode->u.i_mops || !inode->u.i_mops->truncate)
    {
      err = EBADF;
      goto errout;
    }

  /* Does the file system support the truncate method?  It should if it is
   * a write-able file system.
   */

  ret = inode->u.i_mops->truncate(filep, length);
  if (ret < 0)
    {
      err = -ret;
      goto errout;
    }

  return ret;

errout:
  set_errno(err);
  return VFS_ERROR;
}

/****************************************************************************
 * Name: ftruncate
 *
 * Description:
 *   The ftruncate() function causes the regular file referenced by fd to
 *   have a size of length bytes.
 *
 *   If the file previously was larger than length, the extra data is
 *   discarded.  If it was previously shorter than length, it is unspecified
 *   whether the file is changed or its size increased.  If the file is
 *   extended, the extended area appears as if it were zero-filled.  If fd
 *   references a shared memory object, ftruncate() sets the size of the
 *   shared memory object to length. If the file is not a regular file or
 *   a shared memory object, the result is unspecified.

 *   With ftruncate(), the file must be open for writing; for truncate(),
 *   the process must have write permission for the file.
 *
 *   ftruncate() does not modify the file offset for any open file
 *   descriptions associated with the file.
 *
 * Input Parameters:
 *   fd     - A reference to an open, regular file or shared memory object
 *            to be truncated.
 *   length - The new length of the file or shared memory object.
 *
 * Returned Value:
 * On success, 0.
 * On error, -1 is returned, and errno is set appro-priately:
 *
 *
 ****************************************************************************/

int ftruncate(int fd, off_t length)
{
#if CONFIG_NFILE_DESCRIPTORS > 0
  FAR struct file *filep = NULL;
#endif

  /* Did we get a valid file descriptor? */

#if CONFIG_NFILE_DESCRIPTORS > 0
  if ((unsigned int)fd >= CONFIG_NFILE_DESCRIPTORS)
#endif
    {
      set_errno(EBADF);
      return VFS_ERROR;
    }

#if CONFIG_NFILE_DESCRIPTORS > 0
  /* The descriptor is in the right range to be a file descriptor... write
   * to the file.
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

  /* Perform the truncate operation using the file descriptor as an index */

  return file_truncate(filep, length);
#endif
}

int truncate(const char *path, off_t length)
{
  int fd;
  int ret;

  fd = open(path, O_RDWR);
  if (fd == VFS_ERROR)
    {
      /* The errno value has already been set */
      return VFS_ERROR;
    }

  ret = ftruncate(fd, length);
  close(fd);

  return ret;
}
