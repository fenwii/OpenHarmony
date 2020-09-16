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

#include "sys/mount.h"
#include "errno.h"
#include "fs/fs.h"

#include "inode/inode.h"
#include "stdlib.h"

#include "string.h"
#include "disk.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Variables
 ****************************************************************************/

/****************************************************************************
 * Public Variables
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: getlabel()
 *
 * Description:
 *   getlabel() get the volume label of partition(disk) from FAT filesystem by
 *   the 'target' path
 *
 * Parameters:
 *   target : the path which is the mount point of FAT filesystem device.
 *   label  : the string var pointer, by which passed out label string.
 *
 * Return:
 *   Zero is returned on success; -1 is returned on an error and errno is
 *   set appropriately:
 *
 *   ENOMEM There is no memory for allocated space for var.
 *   EFAULT The pointer 'target' does not pass in corretly.
 *   ENOENT The pointer 'target' pointed to a wrong location.
 *   EPERM The pointer 'target' does not point to a mount inode.
 *   EINVAL The pointer 'label' does not pass in correctly.
 *   EACCES The filesystem which 'target' point to is not supported.
 *
 ****************************************************************************/

int getlabel(const char *target, char *label)
{
    FAR struct inode *mountpt_inode = NULL;
    int errcode = OK;
    int status;
    char *fullpath = NULL;
    struct inode_search_s desc;
    int ret;
    /* Verify required pointer arguments */

    if (target == NULL || label == NULL) {
        errcode = EFAULT;
        goto errout;
    }

    /* Get a absolute path */

    errcode = vfs_normalize_path((const char *)NULL, target, &fullpath);
    if (errcode < 0) {
        errcode = -errcode;
        goto errout;
    }

    /* Find the mountpt */
    SETUP_SEARCH(&desc, fullpath, false);
    ret = inode_find(&desc);
    if (ret < 0) {
        errcode = EACCES;
        goto errout_with_fullpath;
    }
    mountpt_inode = desc.node;

    /* Verfy the path is a mountpoint path or file path */

    if (!INODE_IS_MOUNTPT(mountpt_inode) && !INODE_IS_BLOCK(mountpt_inode)) {
        errcode = EPERM;
        goto errout_with_release;
    }

    if (mountpt_inode->u.i_mops && mountpt_inode->u.i_mops->getlabel) {
        status = mountpt_inode->u.i_mops->getlabel(mountpt_inode->i_private, label);
        if (status < 0) {
            /* The inode is unhappy with the blkdrvr for some reason */

            errcode = -status;
            goto errout_with_release;
        }
        inode_release(mountpt_inode);
        free(fullpath);
        return OK;
    } else {
        errcode = EACCES;
        goto errout_with_release;
    }

    /* A lot of goto's!  But they make the error handling much simpler */

errout_with_release:
    inode_release(mountpt_inode);
errout_with_fullpath:
    free(fullpath);
errout:
    set_errno(errcode);
    return VFS_ERROR;
}
