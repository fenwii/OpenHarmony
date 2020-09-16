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

#include <los_sys.h>
#include <linux/kernel.h>
#include <fcntl.h>

#include "hirandom.h"
#include "hisoc/random.h"


static int random_hw_open(struct file *filep)
{
    HiRandomHwInit();
    return ENOERR;
}

static int random_hw_close(struct file *filep)
{
    HiRandomHwDeinit();
    return ENOERR;
}

static int random_hw_ioctl(struct file *filep, int cmd, unsigned long arg)
{
    int ret = ENOERR;

    switch (cmd) {
        default:
            PRINT_ERR("!!!bad command!!!\n");
            return -EINVAL;
    }
    return ret;
}

static ssize_t random_hw_read( struct file *filep, char *buffer, size_t buflen)
{
    int ret = ENOERR;

    ret = HiRandomHwGetNumber(buffer, buflen);
    if (ret == ENOERR) {
        ret = buflen;
    }
    return ret;
}

static ssize_t random_map(FAR struct file *filep, FAR LosVmMapRegion *region)
{
    PRINTK("%s %d, mmap is not support\n", __FUNCTION__, __LINE__);
    return 0;
}

static const struct file_operations_vfs random_hw_dev_ops =
{
    random_hw_open,  /* open */
    random_hw_close, /* close */
    random_hw_read,  /* read */
    NULL,            /* write */
    NULL,            /* seek */
    random_hw_ioctl, /* ioctl */
    random_map,      /* mmap */
#ifndef CONFIG_DISABLE_POLL
    NULL,            /* poll */
#endif
    NULL,            /* unlink */
};

int ran_dev_register(void)
{
    int ret = 0;

    ret = HiRandomHwSupport();
    if (ret) {
        return register_driver("/dev/urandom", &random_hw_dev_ops, 0666, 0);
    }
    return -EPERM;
}

