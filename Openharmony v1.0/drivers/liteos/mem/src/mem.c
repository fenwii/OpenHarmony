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
#include <fcntl.h>
#include "linux/kernel.h"
#include "los_vm_map.h"
#include "los_arch_mmu.h"


static int mem_open(struct file *filep)
{
    return 0;
}

static int mem_close(struct file *filep)
{
    return 0;
}

static ssize_t mem_read(FAR struct file *filep, FAR char *buffer, size_t buflen)
{
    return 0;
}

static ssize_t mem_write(FAR struct file *filep, FAR const char *buffer, size_t buflen)
{
    return 0;
}

static ssize_t mem_map(FAR struct file* filep, FAR LosVmMapRegion *region)
{
    size_t size = region->range.size;
    PADDR_T paddr = region->pgOff << PAGE_SHIFT;
    VADDR_T vaddr = region->range.base;
    LosVmSpace *space = LOS_SpaceGet(vaddr);

    if ((paddr >= SYS_MEM_BASE) && (paddr < SYS_MEM_END)) {
        return -EINVAL;
    }

    /* Peripheral register memory adds strongly ordered attributes */
    region->regionFlags |= VM_MAP_REGION_FLAG_UNCACHED;

    if (space == NULL) {
        return -EAGAIN;
    }
    if (LOS_ArchMmuMap(&space->archMmu, vaddr, paddr, size >> PAGE_SHIFT, region->regionFlags) <= 0) {
        return -EAGAIN;
    }

    return 0;
}

static const struct file_operations_vfs mem_dev_ops =
{
    mem_open,  /* open */
    mem_close, /* close */
    mem_read,  /* read */
    mem_write, /* write */
    NULL,      /* seek */
    NULL,      /* ioctl */
    mem_map,   /* mmap */
#ifndef CONFIG_DISABLE_POLL
    NULL,      /* poll */
#endif
    NULL,      /* unlink */
};


extern int mem_dev_register(void)
{

    return register_driver("/dev/mem", &mem_dev_ops, 0666, 0);
}

