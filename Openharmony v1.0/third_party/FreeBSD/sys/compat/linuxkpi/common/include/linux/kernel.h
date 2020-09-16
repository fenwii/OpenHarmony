/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2016 Mellanox Technologies, Ltd.
 * Copyright (c) 2014-2015 François Tigeot
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/kernel.h 347791 2019-05-16 17:01:39Z hselasky $
 */
#ifndef	_LINUX_KERNEL_H_
#define	_LINUX_KERNEL_H_

#include "errno.h"
#include "string.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/systm.h"
#include "sys/time.h"
#include "sys/mman.h"

#include "linux/types.h"
#include "linux/slab.h"
#include "linux/semaphore.h"
#include "linux/atomic.h"
#include "linux/spinlock.h"
#include "linux/list.h"
#include "linux/io.h"
#include "linux/compiler.h"
#include "user_copy.h"
#ifdef LOSCFG_FS_VFS
#include "fs/fs.h"
#endif
#include "los_exc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define printk    dprintf  /* Do not modify for code check */

#define jiffies     0
#ifndef HZ
#define HZ          LOSCFG_BASE_CORE_TICK_PER_SECOND
#endif

#define SZ_1K       (0x00000400)
#define __init
#define __exit
#define __user

#define ERR_PTR(err) ((void*)(unsigned long)(err))
#define PTR_ERR(err) ((unsigned long)(err))
#define IS_ERR(err)  ((unsigned long)(err) > (unsigned long)-1000L)
#define ERR_CAST(err) ((void *)err)

#define    COMPAT_KERN_EMERG              "<0>" /* system is unusable */
#define    COMPAT_KERN_ALERT              "<1>" /* action must be taken immediately */
#define    COMPAT_KERN_CRIT               "<2>" /* critical conditions */
#define    COMPAT_KERN_ERR                "<3>" /* error conditions */
#define    COMPAT_KERN_WARNING            "<4>" /* warning conditions */
#define    COMPAT_KERN_NOTICE             "<5>" /* normal but significant condition */
#define    COMPAT_KERN_INFO               "<6>" /* informational */
#define    COMPAT_KERN_DEBUG              "<7>" /* debug-level messages */
#define    COMPAT_KERN_CONT               "<c>"

#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

#define pr_emerg(fmt, ...) \
    dprintf(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
#define pr_alert(fmt, ...) \
    dprintf(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
#define pr_crit(fmt, ...) \
    dprintf(KERN_CRIT pr_fmt(fmt), ##__VA_ARGS__)
#define pr_err(fmt, ...) \
    dprintf(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warning(fmt, ...) \
    dprintf(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn pr_warning
#define pr_notice(fmt, ...) \
    dprintf(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
#define pr_info(fmt, ...) \
    dprintf(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
#define pr_cont(fmt, ...) \
    dprintf(KERN_CONT fmt, ##__VA_ARGS__)

/* pr_devel() should produce zero code unless DEBUG is defined */
#ifdef DEBUG
#define pr_devel(fmt, ...) \
    dprintf(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_devel(fmt, ...) do {} while (0)
#endif
/* If you are writing a driver, please use dev_dbg instead */
#if defined(DEBUG)
#define pr_debug(fmt, ...) \
    dprintf(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...) do {} while (0)
#endif

#define WARN_ON(condition) do {} while (0)

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

#ifndef min_t
#define min_t(t, x, y) ((t)(x) < (t)(y) ? (t)(x) : (t)(y))
#endif

#define BUG() do { \
        diag_printf("BUG() at %s %d\n", __FUNCTION__, __LINE__); \
} while (0)

#define BUG_ON(condition) do {  \
    if (condition) {            \
        BUG();                  \
    }                           \
} while (0)

#define __setup(str, fn)

/**
 * @ingroup  linux_kernel
 * @brief change jiffies time to tick (not supported).
 *
 * @par Description:
 * This API is used to change jiffies time to tick time.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  j   [IN] the jiffies time value.
 *
 * @retval Tick time value          The value of tick time.
 * @par Dependency:
 * <ul><li> kernel.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT64 jiffies_to_tick(unsigned long j);

/**
 * @ingroup  linux_kernel
 * @brief Delay a task.
 *
 * @par Description:
 * This API is used to delay the execution of the current task. The task is able to be scheduled
 * after it is delayed for a specified number of Ticks.
 *
 * @attention
 * <ul>
 * <li>The task fails to be delayed if it is being delayed during interrupt processing or it is locked.</li>
 * <li>If 0 is passed in and the task scheduling is not locked, execute the next task in the queue of
 * tasks with the priority of the current task.
 * If no ready task with the priority of the current task is available, the task scheduling will not occur,
 * and the current task continues to be executed.</li>
 * </ul>
 *
 * @param  timeout [IN] Type #signed long Number of Ticks for which the task is delayed(unit: Tick).
 *
 * @retval #LOS_ERRNO_SWTMR_HWI_ACTIVE   The software timer is being used during an interrupt.
 * @retval #LOS_OK                       The task is successfully delayed.
 * @retval #LOS_ERRNO_SWTMR_NOT_STARTED  The software timer is not started.
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
signed long schedule_timeout(signed long timeout);
#define schedule_timeout_uninterruptible(t) schedule_timeout(t)
#define schedule_timeout_interruptible(t) schedule_timeout(t)

#define in_interrupt()        (0)

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the remainder
 *
 * @attention
 * <ul>
 * <li>the param n should point to a valid address.</li>
 * <li>the param base should not be 0.</li>
 * </ul>
 *
 * @param  n    [IN/OUT]     the dividend as IN,the  quotient as OUT
 * @param  base [IN]         the divisor
 * @retval remainder
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 do_div_imp(UINT64 *n, UINT32 base);

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the remainder
 *
 * @attention
 * <ul>
 * <li>the param n should point to a valid address.</li>
 * <li>the param base should not be 0.</li>
 * </ul>
 *
 * @param  n    [IN/OUT]  the dividend as IN,the quotient as OUT
 * @param  base [IN]      the divisor > 0
 * @retval remainder
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern INT32 do_div_s64_imp(INT64 *n, INT32 base);

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient
 *
 * @attention
 * <ul>
 * <li>the param divisor should not be 0.</li>
 * </ul>
 *
 * @param  dividend [IN]     the dividend as IN
 * @param  divisor  [IN]     the divisor > 0
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline UINT64 div64_u64(UINT64 dividend, UINT64 divisor)
{
    return dividend / divisor;
}

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient
 *
 * @attention
 * <ul>
 * <li>the param divisor should not be 0.</li>
 * </ul>
 *
 * @param  dividend [IN]     the dividend as IN
 * @param  divisor  [IN]     the divisor not is 0
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline INT64 div64_s64(INT64 dividend, INT64 divisor)
{
    return dividend / divisor;
}

#define do_div(n, base) ({             \
    UINT32 tmpBase = (base);           \
    UINT32 rem;                        \
    rem = ((UINT64)(n)) % tmpBase;     \
    (n) = ((UINT64)(n)) / tmpBase;     \
    rem;                               \
})

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient ,and remainder as OUT
 *
 * @attention
 * <ul>
 * <li>the param divisor should not be 0.</li>
 * <li>the param remainder should point to a valid address.</li>
 * </ul>
 *
 * @param  dividend  [IN]    the dividend as IN
 * @param  divisor   [IN]    the divisor is not 0 ,and as IN
 * @param  remainder [OUT]   the remainder should point to a valid address. remainder as OUT
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration and implimentation.</li></ul>
 * @see
 */
static inline INT64 div_s64_rem(INT64 dividend, INT32 divisor, INT32 *remainder)
{
    *remainder = dividend % divisor;
    return dividend / divisor;
}

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient, and remainder as OUT
 *
 * @attention
 * <ul>
 * <li>the param divisor should be greater than 0.</li>
 * <li>the param remainder should point to a valid address.</li>
 * </ul>
 *
 * @param  dividend  [IN]    the dividend as IN
 * @param  divisor   [IN]    the divisor is greater than 0, and as IN
 * @param  remainder [OUT]   the remainder should point to a valid address. remainder as OUT
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration and implimentation.</li></ul>
 * @see
 */
static inline UINT64 div64_u64_rem(UINT64 dividend, UINT64 divisor, UINT64 *remainder)
{
    *remainder = dividend % divisor;
    return dividend / divisor;
}

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient,and  remainder as OUT
 *
 * @attention
 * <ul>
 * <li>the param divisor should be greater than 0.</li>
 * <li>the param remainder should point to a valid address.</li>
 * </ul>
 *
 * @param  dividend  [IN]    the dividend as IN
 * @param  divisor   [IN]    the divisor is greater than 0, and as IN
 * @param  remainder [OUT]   the remainder should point to a valid address. remainder as OUT
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration and implimentation.</li></ul>
 * @see
 */
static inline UINT64 div_u64_rem(UINT64 dividend, UINT32 divisor, UINT32 *remainder)
{
    *remainder = dividend % divisor;
    return dividend / divisor;
}

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient
 *
 * @attention
 * <ul>
 * <li>the param divisor should not be 0.</li>
 * </ul>
 *
 * @param dividend [IN]     the dividend as IN
 * @param divisor  [IN]     the divisor is not 0, and as IN
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration and implimentation.</li></ul>
 * @see
 */
static inline INT64 div_s64(INT64 dividend, INT32 divisor)
{
    INT32 remainder;
    return div_s64_rem(dividend, divisor, &remainder);
}

/**
 * @ingroup  linux_kernel
 * @brief do division implimentation.
 *
 * @par Description:
 * This API is used to do a division implimentation,and return the quotient
 *
 * @attention
 * <ul>
 * <li>the param divisor should be greater than 0.</li>
 * </ul>
 *
 * @param dividend [IN]     the dividend as IN
 * @param divisor  [IN]     the divisor is greater than 0, and as IN
 * @retval quotient
 * @par Dependency:
 * <ul><li>kernel.h: the header file that contains the API declaration and implimentation.</li></ul>
 * @see
 */
static inline UINT64 div_u64(UINT64 dividend, UINT32 divisor)
{
    UINT32 remainder;
    return div_u64_rem(dividend, divisor, &remainder);
}

static inline unsigned long copy_from_user(void *to, const void *from, unsigned long n)
{
    if ((to == NULL) || (from == NULL)) {
        return (unsigned long)-1;
    }

    return LOS_ArchCopyFromUser(to, from, n);
}

static inline unsigned long copy_to_user(void *to, const void *from, unsigned long n)
{
    if ((to == NULL) || (from == NULL)) {
        return (unsigned long)-1;
    }

    return LOS_ArchCopyToUser(to, from, n);
}

extern void *ioremap(unsigned long phys_addr, unsigned long size);
extern void *ioremap_cached(unsigned long phys_addr, unsigned long size);
extern void *ioremap_nocache(unsigned long phys_addr, unsigned long size);
extern void iounmap(void *addr);
extern int remap_pfn_range(unsigned long addr, unsigned long pfn, unsigned long size, unsigned long prot);

#ifndef io_remap_pfn_range
#define io_remap_pfn_range remap_pfn_range
#endif

#define EXPORT_SYMBOL(x)

typedef VOID (*unused_func_t)(VOID);

struct file_operations {
    struct module *owner;
    unused_func_t   llseek;
    unused_func_t   read;
    unused_func_t   write;
    unused_func_t   aio_read;
    unused_func_t   aio_write;
    unused_func_t   readdir;
    unused_func_t   poll;
    unused_func_t   unlocked_ioctl;
    unused_func_t   compat_ioctl;
    unused_func_t   mmap;
    unused_func_t   open;
    unused_func_t   flush;
    unused_func_t   release;
    unused_func_t   fsync;
    unused_func_t   aio_fsync;
    unused_func_t   fasync;
    unused_func_t   lock;
    unused_func_t   sendpage;
    unused_func_t   get_unmapped_area;
    unused_func_t   check_flags;
    unused_func_t   flock;
    unused_func_t   splice_write;
    unused_func_t   splice_read;
    unused_func_t   setlease;
    unused_func_t   fallocate;
};

#define simple_strtol       strtol
#define do_gettimeofday(a)  gettimeofday(a, NULL)
#define DEFINE_MUTEX(m)     pthread_mutex_t m;
#define mutex_lock          pthread_mutex_lock
#define mutex_unlock        pthread_mutex_unlock
#define mutex_init(m)       pthread_mutex_init(m, NULL)
#define mutex_destroy(m)    pthread_mutex_destroy((m))

static inline void printtime(void)
{
    struct timeval time;

    (VOID)gettimeofday(&time, NULL);
    PRINTK("[time:%d.%03d]", time.tv_sec, time.tv_usec / 1000); /* 1000: millisecond to microseconds */
    return;
}

#define TRACETIME() do {                                     \
    printtime();                                             \
    printk("func:%s, line %d\r\n", __FUNCTION__, __LINE__);  \
} while (0)

extern void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
extern int munmap(void *addr, size_t length);

#define    KERN_EMERG              COMPAT_KERN_EMERG
#define    KERN_ALERT              COMPAT_KERN_ALERT
#define    KERN_CRIT               COMPAT_KERN_CRIT
#define    KERN_ERR                COMPAT_KERN_ERR
#define    KERN_WARNING            COMPAT_KERN_WARNING
#define    KERN_NOTICE             COMPAT_KERN_NOTICE
#define    KERN_INFO               COMPAT_KERN_INFO
#define    KERN_DEBUG              COMPAT_KERN_DEBUG
#define    KERN_CONT               COMPAT_KERN_CONT

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_KERNEL_H_ */
