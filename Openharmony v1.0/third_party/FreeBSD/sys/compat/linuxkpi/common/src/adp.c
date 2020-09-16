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

#include "linux/kernel.h"
#include "linux/module.h"
#include "math.h"
#include "limits.h"
#include "sys/statfs.h"
#include "los_sys_pri.h"
#include "los_swtmr.h"
#ifdef LOSCFG_KERNEL_DYNLOAD
#include "los_ld_elflib.h"
#endif
#ifdef LOSCFG_NET_LWIP_SACK
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/netdb.h"
#endif
#include "linux/rbtree.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef __LP64__
int dl_iterate_phdr(int (*callback)(void *info, size_t size, void *data), void *data)
{
    PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
    errno = ENOSYS;
    return -1;
}
#endif

void fs_show(const char *path)
{
    INT32 ret;
    struct statfs fss;
    if (path == NULL) {
        PRINTK("path is NULL\n");
        return;
    }
    ret = statfs(path, &fss);
    PRINTK("Filesystem %s info: \n", path);
    PRINTK("----------------------------------------\n");
    if (ret == ENOERR) {
        PRINTK("  Total clusters: %u \n", fss.f_blocks);
        PRINTK("  Cluster size: %u \n", fss.f_bsize);
        PRINTK("  Free clusters: %u \n", fss.f_bfree);
    } else {
        ret = get_errno();
        PRINT_ERR("Get fsinfo failed: %d \n", ret);
    }
}

#define MAX_JIFFY_OFFSET ((LONG_MAX >> 1) - 1)

unsigned long msecs_to_jiffies(const unsigned int m)
{
    /* Negative value, means infinite timeout: */
    if ((INT32)m < 0) {
        return (unsigned long)MAX_JIFFY_OFFSET;
    }

#if (HZ <= OS_SYS_MS_PER_SECOND) && !(OS_SYS_MS_PER_SECOND % HZ)
    /*
     * HZ is equal to or smaller than 1000, and 1000 is a nice
     * round multiple of HZ, divide with the factor between them,
     * but round upwards:
     */
    return ((m + (OS_SYS_MS_PER_SECOND / HZ)) - 1) / (OS_SYS_MS_PER_SECOND / HZ);
#else
    PRINT_ERR("HZ: %d is not supported in %s\n", HZ, __FUNCTION__);
    return ENOSUPP;
#endif
}

UINT64 jiffies_to_tick(unsigned long j)
{
    return j;
}

#define MAX_SCHEDULE_TIMEOUT UINT_MAX
signed long schedule_timeout(signed long timeout)
{
    UINT32 ret;

    if (OS_INT_ACTIVE) {
        PRINT_ERR("ERROR: OS_ERRNO_SWTMR_HWI_ACTIVE\n");
        return LOS_ERRNO_SWTMR_HWI_ACTIVE;
    }
    if (timeout < 0) {
        PRINT_ERR("schedule_timeout: wrong timeout\n");
        return 0;
    }
#ifdef __LP64__
    if (timeout > MAX_SCHEDULE_TIMEOUT) {
        timeout = LOS_WAIT_FOREVER;
    }
#endif
    ret = LOS_TaskDelay(timeout);
    if (ret == LOS_OK) {
        return ret;
    } else {
        PRINT_ERR("ERROR: OS_ERRNO_SWTMR_NOT_STARTED\n");
        return LOS_ERRNO_SWTMR_NOT_STARTED;
    }
}

UINT32 do_div_imp(UINT64 *n, UINT32 base)
{
    UINT32 r;

    if ((n == NULL) || (base == 0)) {
        PRINT_ERR("%s invalid input param, n:%p, base %u\n", __FUNCTION__, n, base);
        return 0;
    }

    r = *n % base;
    *n = *n / base;
    return r;
}

INT32 do_div_s64_imp(INT64 *n, INT32 base)
{
    INT32 r;

    if ((n == NULL) || (base == 0)) {
        PRINT_ERR("%s invalid input param, n:%p, base:%u\n", __FUNCTION__, n, base);
        return 0;
    }

    r = *n % base;
    *n = *n / base;
    return r;
}

char *basename(const char *path)
{
    STATIC const CHAR empty[] = ".";
    CHAR *first = (CHAR *)empty;
    register CHAR *last = NULL;

    if ((path != NULL) && *path) {
        first = (CHAR *)path;
        last = (CHAR *)path - 1;

        do {
            if ((*path != '/') && (path > ++last)) {
                last = first = (CHAR *)path;
            }
        } while (*++path);

        if (*first == '/') {
            last = first;
        }
        last[1] = 0;
    }

    return first;
}

void *__dso_handle = NULL;

/* Undo Linux compat changes. */
#undef RB_ROOT
#define RB_ROOT(head)   (head)->rbh_root

int
panic_cmp(struct rb_node *one, struct rb_node *two)
{
    LOS_Panic("no cmp");
    return 0;
}

RB_GENERATE(linux_root, rb_node, __entry, panic_cmp);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
