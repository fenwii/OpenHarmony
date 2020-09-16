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

#include "hievent_driver.h"

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include <fs/fs.h>
#include <sys/types.h>
#include <linux/list.h>
#include <linux/wait.h>

#include "poll.h"
#include "hievent_driver.h"
#include "los_memory.h"
#include "los_task_pri.h"
#include "los_process_pri.h"
#include "los_task_pri.h"
#include "los_mux.h"
#include "los_mp.h"
#include "los_vm_map.h"
#include "user_copy.h"
#include "los_vm_lock.h"

#define HIEVENT_LOG_BUFFER 1024
#define DRIVER_MODE 0666

struct HieventEntry {
    uint16_t len;
    uint16_t hdrSize;
    int32_t pid;
    int32_t tid;
    int32_t sec;
    int32_t nsec;
    char msg[0];
};

FAR struct HieventCharDevice {
    int flag;
    LosMux mtx;
    unsigned char *buffer;
    wait_queue_head_t wq;
    size_t writeOffset;
    size_t headOffset;
    size_t size;
    size_t count;
} g_hieventDev;

static inline unsigned char *HieventBufferHead(void)
{
    if (g_hieventDev.headOffset > HIEVENT_LOG_BUFFER) {
        g_hieventDev.headOffset = g_hieventDev.headOffset % HIEVENT_LOG_BUFFER;
    }
    return g_hieventDev.buffer + g_hieventDev.headOffset;
}


int HieventOpen(FAR struct file *filep)
{
    (void)filep;
    return 0;
}

int HieventClose(FAR struct file *filep)
{
    (void)filep;
    return 0;
}

static void HieventBufferInc(size_t sz)
{
    if (g_hieventDev.size + sz <= HIEVENT_LOG_BUFFER) {
        g_hieventDev.size += sz;
        g_hieventDev.writeOffset += sz;
        g_hieventDev.writeOffset %= HIEVENT_LOG_BUFFER;
        g_hieventDev.count++;
    }
}

static void HieventBufferDec(size_t sz)
{
    if (g_hieventDev.size >= sz) {
        g_hieventDev.size -= sz;
        g_hieventDev.headOffset += sz;
        g_hieventDev.headOffset %= HIEVENT_LOG_BUFFER;
        g_hieventDev.count--;
    }
}

static int HieventBufferCopy(unsigned char *dst, unsigned dstLen,
                             unsigned char *src, size_t srcLen)
{
    int retval = -1;

    size_t minLen = dstLen > srcLen ? srcLen : dstLen;

    if (LOS_IsUserAddressRange((vaddr_t)(uintptr_t)dst, minLen) &&
        LOS_IsUserAddressRange((vaddr_t)(uintptr_t)src, minLen)) {
        return retval;
    }

    if (LOS_IsUserAddressRange((vaddr_t)(uintptr_t)dst, minLen)) {
        retval = LOS_ArchCopyToUser(dst, src, minLen);
    } else if (LOS_IsUserAddressRange((vaddr_t)(uintptr_t)src, minLen)) {
        retval = LOS_ArchCopyFromUser(dst, src, minLen);
    } else {
        retval = memcpy_s(dst, dstLen, src, srcLen);
    }
    return retval;
}

static int HieventReadRingBuffer(unsigned char *buffer, size_t bufLen)
{
    size_t retval;
    size_t bufLeft = HIEVENT_LOG_BUFFER - g_hieventDev.headOffset;
    if (bufLeft > bufLen) {
        retval = HieventBufferCopy(buffer, bufLen, HieventBufferHead(), bufLen);
    } else {
        retval = HieventBufferCopy(buffer, bufLen, HieventBufferHead(), bufLeft);
        if (retval < 0) {
            return retval;
        }

        retval = HieventBufferCopy(buffer + bufLeft, bufLen - bufLeft,
                                   g_hieventDev.buffer, bufLen - bufLeft);
    }
    return retval;
}

static ssize_t HieventRead(FAR struct file *filep, char *buffer, size_t bufLen)
{
    size_t retval;
    struct HieventEntry header;

    (void)filep;

    wait_event_interruptible(g_hieventDev.wq, (g_hieventDev.size > 0));

    (VOID)LOS_MuxAcquire(&g_hieventDev.mtx);

    retval = HieventReadRingBuffer((unsigned char *)&header, sizeof(header));
    if (retval < 0) {
        retval = -EINVAL;
        goto out;
    }

    if (bufLen < header.len + sizeof(header)) {
        PRINT_ERR("buffer too small\n");
        retval = -ENOMEM;
        goto out;
    }

    HieventBufferDec(sizeof(header));

    retval = HieventBufferCopy((unsigned char *)buffer, bufLen,
                               (unsigned char *)&header, sizeof(header));
    if (retval < 0) {
        retval = -EINVAL;
        goto out;
    }

    retval = HieventReadRingBuffer((unsigned char *)(buffer + sizeof(header)),
                                   header.len);
    if (retval < 0) {
        retval = -EINVAL;
        goto out;
    }

    HieventBufferDec(header.len);

    retval = header.len + sizeof(header);
out:
    (VOID)LOS_MuxRelease(&g_hieventDev.mtx);
    return retval;

}

static int HieventWriteRingBuffer(unsigned char *buffer, size_t bufLen)
{
    int retval;
    size_t bufLeft = HIEVENT_LOG_BUFFER - g_hieventDev.writeOffset;
    if (bufLen > bufLeft) {
        retval = HieventBufferCopy(g_hieventDev.buffer + g_hieventDev.writeOffset,
                                   bufLeft, buffer, bufLeft);
        if (retval) {
            return -1;
        }
        retval = HieventBufferCopy(g_hieventDev.buffer, HIEVENT_LOG_BUFFER,
                                   buffer + bufLeft, bufLen - bufLeft);
    } else {
        retval = HieventBufferCopy(g_hieventDev.buffer + g_hieventDev.writeOffset,
                                   bufLeft, buffer, bufLen);
    }
    if (retval < 0) {
        return -1;
    }
    return 0;
}

static void HieventHeadInit(struct HieventEntry *header, size_t len)
{
    struct timespec now;

    clock_gettime(CLOCK_REALTIME, &now);

    header->len = len;
    header->pid = LOS_GetCurrProcessID();
    header->tid = 0;
    header->sec = now.tv_sec;
    header->nsec = now.tv_nsec;
    header->hdrSize = sizeof(struct HieventEntry);
}

static void HieventCoverOldLog(size_t bufLen)
{
    int retval;
    struct HieventEntry header;
    size_t totalSize = bufLen + sizeof(struct HieventEntry);

    while (totalSize + g_hieventDev.size >= HIEVENT_LOG_BUFFER) {
        retval = HieventReadRingBuffer((unsigned char *)&header, sizeof(header));
        if (retval < 0) {
            break;
        }

        /* let count decrease twice */
        HieventBufferDec(sizeof(header));
        HieventBufferDec(header.len);
    }
}

int HieventWriteInternal(const char *buffer, size_t bufLen)
{
    struct HieventEntry header;
    int retval;

    if (bufLen < sizeof(int)) {
        return -EINVAL;
    }

    (VOID)LOS_MuxAcquire(&g_hieventDev.mtx);

    /* need userspace use writev */
    if (LOS_IsUserAddressRange((vaddr_t)(uintptr_t)buffer, bufLen)) {
        retval = -EINVAL;
        goto out;
    }

    int checkCode = *((int *)buffer);

    if (checkCode != CHECK_CODE) {
        retval = -EINVAL;
        goto out;
    }

    HieventCoverOldLog(bufLen);

    HieventHeadInit(&header, bufLen - sizeof(int));

    retval = HieventWriteRingBuffer((unsigned char *)&header, sizeof(header));
    if (retval) {
        retval = -EINVAL;
        goto out;
    }
    HieventBufferInc(sizeof(header));

    retval = HieventWriteRingBuffer((unsigned char *)(buffer + sizeof(int)),
                                    header.len);
    if (retval) {
        retval = -EINVAL;
        goto out;
    }

    HieventBufferInc(header.len);

    retval = header.len;

out:
    (VOID)LOS_MuxRelease(&g_hieventDev.mtx);
    if (retval > 0) {
        wake_up_interruptible(&g_hieventDev.wq);
    }
    return retval;

}

static ssize_t HieventWrite(FAR struct file *filep,
                            const char *buffer, size_t bufLen)
{
    (void)filep;
    if (bufLen + sizeof(struct HieventEntry) > HIEVENT_LOG_BUFFER) {
        PRINT_ERR("input too large\n");
        return -ENOMEM;
    }

    return HieventWriteInternal(buffer, bufLen);
}

static int HieventPoll(FAR struct file *filep, poll_table *fds)
{
    (void)filep;

    wait_event_interruptible(g_hieventDev.wq, (g_hieventDev.size > 0));

    return (POLLOUT | POLLWRNORM);
}

static int HieventIoctl(FAR struct file *filep, int cmd, unsigned long arg)
{
    // not support ioctl in liteos now
    (void)filep;
    (void)cmd;
    (void)arg;
    return 0;
}

static struct file_operations_vfs g_hieventFops = {
    .open  = HieventOpen,   /* open */
    .close = HieventClose,  /* close */
    .read  = HieventRead,   /* read */
    .write = HieventWrite,  /* write */
    .seek  = NULL,          /* seek */
    .ioctl = HieventIoctl,  /* ioctl */
    .mmap  = NULL,          /* mmap */
    .poll  = HieventPoll,   /* poll */
};

static void HieventDeviceInit(void)
{
    g_hieventDev.buffer = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR,
                                       HIEVENT_LOG_BUFFER);

    init_waitqueue_head(&g_hieventDev.wq);
    LOS_MuxInit(&g_hieventDev.mtx, NULL);

    g_hieventDev.writeOffset = 0;
    g_hieventDev.headOffset = 0;
    g_hieventDev.size = 0;
    g_hieventDev.count = 0;
}

int HieventInit()
{
    HieventDeviceInit();
    register_driver("/dev/hwlog_exception", &g_hieventFops,
                    DRIVER_MODE, &g_hieventDev);
    return 0;
}
