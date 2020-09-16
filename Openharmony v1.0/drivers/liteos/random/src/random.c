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

static unsigned long random_max =  0x7FFFFFFF;

static long do_rand(unsigned long *value)
{
    long quotient, remainder, t;

    quotient = *value / 127773L;
    remainder = *value % 127773L;
    t = 16807L * remainder - 2836L * quotient;
    if (t <= 0)
        t += 0x7fffffff;
    return ((*value = t) % (random_max + 1));
}

static unsigned long seed = 1;

int ran_open(struct file *filep)
{
    seed = (unsigned long)(hi_sched_clock() & 0xffffffff);
    return 0;
}

static int ran_close(struct file *filep)
{
    return 0;
}

int ran_ioctl(struct file * filep, int cmd, unsigned long arg)
{
    switch(cmd) {
        case RANDOM_SET_MAX:
            random_max = arg;
            break;
        default:
            PRINT_ERR("!!!bad command!!!\n");
            return -EINVAL;
    }
    return ENOERR;
}

ssize_t ran_read( struct file *filep, char *buffer, size_t buflen)
{
    ssize_t len = buflen;
    char *buf = buffer;
    unsigned int temp;
    int ret;

    if (len % sizeof(unsigned int)) {
        PRINT_ERR("random size not aligned by 4 bytes\n");
        return -EINVAL;
    }
    while (len > 0) {
        temp = do_rand(&seed);
        ret = LOS_CopyFromKernel((void *)buf, sizeof(unsigned int), (void *)&temp, sizeof(unsigned int));
        if(ret) {
            break;
        }
        len -= sizeof(unsigned int);
        buf += sizeof(unsigned int);
    }
    return (buflen - len);//return a successful len
}

static ssize_t ran_map(FAR struct file* filep, FAR LosVmMapRegion *region)
{
    PRINTK("%s %d, mmap is not support\n", __FUNCTION__, __LINE__);
    return 0;
}

static const struct file_operations_vfs ran_dev_ops =
{
    ran_open,  /* open */
    ran_close, /* close */
    ran_read,  /* read */
    NULL,      /* write */
    NULL,      /* seek */
    ran_ioctl, /* ioctl */
    ran_map,   /* mmap */
#ifndef CONFIG_DISABLE_POLL
    NULL,      /* poll */
#endif
    NULL,      /* unlink */
};

int pse_ran_dev_register(void)
{
    return register_driver("/dev/random", &ran_dev_ops, 0666, 0);
}

