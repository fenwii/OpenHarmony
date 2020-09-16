/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "vfs_config.h"
#include "sys/types.h"
#include "assert.h"
#include "errno.h"
#include "fcntl.h"
#include "sched.h"
#include "unistd.h"

#include "inode/inode.h"


/****************************************************************************
 * Name: file_fallocate
 ****************************************************************************/

ssize_t file_fallocate64(FAR struct file *filep, int mode, off64_t offset, off64_t len)
{
    FAR struct inode *inode = NULL;
    int ret;
    int err;

    if (len <= 0) {
        err = EINVAL;
        goto errout;
    }

    /* Was this file opened for write access? */

    if (((unsigned int)(filep->f_oflags) & O_ACCMODE) == O_RDONLY) {
        err = EACCES;
        goto errout;
    }

    /* Is a driver registered? Does it support the fallocate method? */

    inode = filep->f_inode;
    if (!inode || !inode->u.i_mops || !inode->u.i_mops->fallocate64) {
        err = EBADF;
        goto errout;
    }

    /* Yes, then let the driver perform the fallocate */

    ret = inode->u.i_mops->fallocate64(filep, mode, offset, len);
    if (ret < 0) {
        err = -ret;
        goto errout;
    }

    return ret;

errout:
    set_errno(err);
    return VFS_ERROR;
}

/***************************************************************************
 * Name: fallocate
 *
 * Description:
 * The fallocate() function prepares or allocates a contiguous data area to the file.
 * Thus the write file is guaranteed be contiguous and no allocation delay until the
 * size reaches that size at least unless any other changes to the volume is performed.
 *
 * Parameters:
 * fp Pointer to the open file object.
 * mode Operation mode. only support FALLOC_FL_KEEP_SIZE.
 * offset offset of the file to allocated.
 * len The size to allocate for the file.
 *
 * Returned Value:
 *  On success, allocate contiguous data area to the file . On error, -1 is returned, and errno is set appro-
 *  priately:
 *
 *
 ********************************************************************************************/

int fallocate64(int fd, int mode, off64_t offset, off64_t len)
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

    /* Perform the fallocate operation using the file descriptor as an index */

    return file_fallocate64(filep, mode, offset, len);
#endif
}
