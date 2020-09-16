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

#include "sys/types.h"
#include "sys/uio.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "fs/fs.h"
#include "inode/inode.h"
#include "user_copy.h"

static char *pread_buf_and_check(int fd, const struct iovec *iov, int iovcnt, ssize_t *totalbytesread, off_t *offset)
{
    char *buf = NULL;
    size_t buflen = 0;
    int i;

    if ((iov == NULL) || (iovcnt > IOV_MAX)) {
        *totalbytesread = VFS_ERROR;
        return NULL;
    }

    for (i = 0; i < iovcnt; ++i) {
        if (SSIZE_MAX - buflen < iov[i].iov_len) {
            set_errno(EINVAL);
            return NULL;
        }
        buflen += iov[i].iov_len;
    }

    if (buflen == 0) {
        *totalbytesread = 0;
        return NULL;
    }

    buf = (char *)LOS_VMalloc(buflen * sizeof(char));
    if (buf == NULL) {
        set_errno(ENOMEM);
        *totalbytesread = VFS_ERROR;
        return buf;
    }

    *totalbytesread = (offset == NULL) ? read(fd, buf, buflen)
                                       : pread(fd, buf, buflen, *offset);
    if ((*totalbytesread == VFS_ERROR) || (*totalbytesread == 0)) {
        LOS_VFree(buf);
        return NULL;
    }

    return buf;
}

ssize_t vfs_readv(int fd, const struct iovec *iov, int iovcnt, off_t *offset)
{
    int i;
    int ret;
    char *buf = NULL;
    char *curbuf = NULL;
    ssize_t bytestoread;
    ssize_t totalbytesread = 0;
    ssize_t bytesleft;

    buf = pread_buf_and_check(fd, iov, iovcnt, &totalbytesread, offset);
    if (buf == NULL) {
        return totalbytesread;
    }

    curbuf = buf;
    bytesleft = totalbytesread;
    for (i = 0; i < iovcnt; ++i) {
        bytestoread = iov[i].iov_len;
        if (bytestoread == 0) {
            continue;
        }

        if (bytesleft <= bytestoread) {
            ret = LOS_CopyFromKernel(iov[i].iov_base, bytesleft, curbuf, bytesleft);
            bytesleft = ret;
            goto out;
        }

        ret = LOS_CopyFromKernel(iov[i].iov_base, bytestoread, curbuf, bytestoread);
        if (ret != 0) {
            bytesleft = bytesleft - (bytestoread - ret);
            goto out;
        }
        bytesleft -= bytestoread;
        curbuf += bytestoread;
    }

out:
    LOS_VFree(buf);
    if ((i == 0) && (ret == iov[i].iov_len)) {
        /* failed in the first iovec copy, and 0 bytes copied */
        set_errno(EFAULT);
        return VFS_ERROR;
    }

    return totalbytesread - bytesleft;
}

ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
{
    return vfs_readv(fd, iov, iovcnt, NULL);
}
