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

#include "errno.h"
#include "vfs_config.h"
#include "sys/stat.h"
#include "inode/inode.h"
#include "string.h"
#include "stdlib.h"
#include "utime.h"

/****************************************************************************
 * Global Functions
 ****************************************************************************/

/****************************************************************************
 * Name: utime
 *
 * Returned Value:
 *   Zero on success; -1 on failure with errno set:
 *
 ****************************************************************************/

static int utime_pseudo(FAR struct inode *pinode, FAR const struct utimbuf *ptimes)
{
    return ENOSYS;
}

int utime(FAR const char *path, FAR const struct utimbuf *ptimes)
{
    FAR struct inode *pinode = NULL;
    const char *relpath = NULL;
    int ret = OK;
    char *fullpath = NULL;
    time_t cur_sec;
    struct tm *set_tm = NULL;
    struct inode_search_s desc;

    /* Sanity checks */

    if (path == NULL) {
        ret = EINVAL;
        goto errout;
    }

    if (!path[0]) {
        ret = ENOENT;
        goto errout;
    }

    ret = vfs_normalize_path((const char *)NULL, path, &fullpath);
    if (ret < 0) {
        ret = -ret;
        goto errout;
    }

    /* Check for the fake root directory (which has no inode) */

    if (strcmp(fullpath, "/") == 0) {
        ret = EACCES;
        goto errout_with_path;
    }

    /* Get an inode for this file */
    SETUP_SEARCH(&desc, fullpath, false);
    ret = inode_find(&desc);
    if (ret < 0) {
        /* This name does not refer to a psudeo-inode and there is no
         * mountpoint that includes in this path.
         */

        ret = EACCES;
        goto errout_with_path;
    }
    pinode = desc.node;

    /* The way we handle the utime depends on the type of inode that we
     * are dealing with.
     */

#ifndef CONFIG_DISABLE_MOUNTPOINT
    if (INODE_IS_MOUNTPT(pinode)) {
        /* The node is a file system mointpoint. Verify that the mountpoint
         * supports the utime() method.
         */

        if (pinode->u.i_mops && pinode->u.i_mops->utime) {
            if (ptimes == NULL) {
                /*get current seconds*/

                cur_sec = time(NULL);
                set_tm = localtime(&cur_sec);   /* transform seconds to struct tm */
            } else {
                set_tm = gmtime(&ptimes->modtime);   /* transform seconds to struct tm */
            }

            /* Perform the utime() operation */

            if (set_tm == NULL) {
                ret = EINVAL;
                goto errout_with_inode;
            }
            ret = pinode->u.i_mops->utime(pinode, relpath, set_tm);
        } else {
            ret = ENOSYS;
            goto errout_with_inode;
        }
    } else
#endif
    {
        /* The node is part of the root pseudo file system */

        ret = utime_pseudo(pinode, ptimes);
        goto errout_with_inode;
    }

    /* Check if the stat operation was successful */

    if (ret < 0) {
        ret = -ret;
        goto errout_with_inode;
    }

    /* Successfully stat'ed the file */

    inode_release(pinode);
    free(fullpath);
    return OK;

    /* Failure conditions always set the errno appropriately */

errout_with_inode:
    inode_release(pinode);
errout_with_path:
    free(fullpath);
errout:
    if (ret != 0) {
        set_errno(ret);
    }
    return VFS_ERROR;
}
