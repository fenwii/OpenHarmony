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

#include "los_hilog.h"
#include "los_mp.h"
#include "los_mux.h"
#include "los_process_pri.h"
#include "los_task_pri.h"
#include "fs/fs.h"
#include "los_vm_map.h"
#include "los_vm_lock.h"
#include "user_copy.h"

#define HILOG_BUFFER 1024
#define DRIVER_MODE 0666
#define HILOG_DRIVER "/dev/hilog"

struct HiLogEntry {
    unsigned int len;
    unsigned int hdrSize;
    unsigned int pid : 16;
    unsigned int taskId : 16;
    unsigned int sec;
    unsigned int nsec;
    unsigned int reserved;
    char msg[0];
};

ssize_t HilogRead(struct file *filep, char __user *buf, size_t count);
ssize_t HilogWrite(struct file *filep, const char __user *buf, size_t count);
int HiLogOpen(FAR struct file *filep);
int HiLogClose(FAR struct file *filep);

static ssize_t HiLogWrite(FAR struct file *filep, const char *buffer, size_t bufLen);
static ssize_t HiLogRead(FAR struct file *filep, char *buffer, size_t bufLen);

STATIC struct file_operations_vfs g_hilogFops = {
    HiLogOpen,  /* open */
    HiLogClose, /* close */
    HiLogRead,  /* read */
    HiLogWrite, /* write */
    NULL,       /* seek */
    NULL,       /* ioctl */
    NULL,       /* mmap */
#ifndef CONFIG_DISABLE_POLL
    NULL, /* poll */
#endif
    NULL, /* unlink */
};

FAR struct HiLogCharDevice {
    int flag;
    LosMux mtx;
    unsigned char *buffer;
    wait_queue_head_t wq;
    size_t writeOffset;
    size_t headOffset;
    size_t size;
    size_t count;
} g_hiLogDev;

static inline unsigned char *HiLogBufferHead(void)
{
    return g_hiLogDev.buffer + g_hiLogDev.headOffset;
}

int HiLogOpen(FAR struct file *filep)
{
    (void)filep;
    return 0;
}

int HiLogClose(FAR struct file *filep)
{
    (void)filep;
    return 0;
}

static void HiLogBufferInc(size_t sz)
{
    if (g_hiLogDev.size + sz <= HILOG_BUFFER) {
        g_hiLogDev.size += sz;
        g_hiLogDev.writeOffset += sz;
        g_hiLogDev.writeOffset %= HILOG_BUFFER;
        g_hiLogDev.count++;
    }
}

static void HiLogBufferDec(size_t sz)
{
    if (g_hiLogDev.size >= sz) {
        g_hiLogDev.size -= sz;
        g_hiLogDev.headOffset += sz;
        g_hiLogDev.headOffset %= HILOG_BUFFER;
        g_hiLogDev.count--;
    }
}

static int HiLogBufferCopy(unsigned char *dst, unsigned dstLen, unsigned char *src, size_t srcLen)
{
    int retval = -1;

    size_t minLen = (dstLen > srcLen) ? srcLen : dstLen;

    if (LOS_IsUserAddressRange((VADDR_T)dst, minLen) && LOS_IsUserAddressRange((VADDR_T)src, minLen)) {
        return retval;
    }

    if (LOS_IsUserAddressRange((VADDR_T)dst, minLen)) {
        retval = LOS_ArchCopyToUser(dst, src, minLen);
    } else if (LOS_IsUserAddressRange((VADDR_T)src, minLen)) {
        retval = LOS_ArchCopyFromUser(dst, src, minLen);
    } else {
        retval = memcpy_s(dst, dstLen, src, srcLen);
    }
    return retval;
}

static int HiLogReadRingBuffer(unsigned char *buffer, size_t bufLen)
{
    size_t retval;
    size_t bufLeft = HILOG_BUFFER - g_hiLogDev.headOffset;
    if (bufLeft > bufLen) {
        retval = HiLogBufferCopy(buffer, bufLen, HiLogBufferHead(), bufLen);
    } else {
        retval = HiLogBufferCopy(buffer, bufLen, HiLogBufferHead(), bufLeft);
        if (retval < 0) {
            return retval;
        }

        retval = HiLogBufferCopy(buffer + bufLeft, bufLen - bufLeft, g_hiLogDev.buffer, bufLen - bufLeft);
    }
    return retval;
}

static ssize_t HiLogRead(FAR struct file *filep, char *buffer, size_t bufLen)
{
    size_t retval;
    struct HiLogEntry header;

    (void)filep;

    wait_event_interruptible(g_hiLogDev.wq, (g_hiLogDev.size > 0));

    (VOID)LOS_MuxAcquire(&g_hiLogDev.mtx);
    retval = HiLogReadRingBuffer((unsigned char *)&header, sizeof(header));
    if (retval < 0) {
        retval = -EINVAL;
        goto out;
    }

    if (bufLen < header.len + sizeof(header)) {
        dprintf("buffer too small,bufLen=%d, header.len=%d,%d\n", bufLen, header.len, header.hdrSize, header.nsec);
        retval = -ENOMEM;
        goto out;
    }

    HiLogBufferDec(sizeof(header));

    retval = HiLogBufferCopy((unsigned char *)buffer, bufLen, (unsigned char *)&header, sizeof(header));
    if (retval < 0) {
        retval = -EINVAL;
        goto out;
    }

    retval = HiLogReadRingBuffer((unsigned char *)(buffer + sizeof(header)), header.len);
    if (retval < 0) {
        retval = -EINVAL;
        goto out;
    }

    HiLogBufferDec(header.len);
    retval = header.len + sizeof(header);
out:
    (VOID)LOS_MuxRelease(&g_hiLogDev.mtx);
    return retval;
}

static int HiLogWriteRingBuffer(unsigned char *buffer, size_t bufLen)
{
    int retval;
    size_t bufLeft = HILOG_BUFFER - g_hiLogDev.writeOffset;
    if (bufLen > bufLeft) {
        retval = HiLogBufferCopy(g_hiLogDev.buffer + g_hiLogDev.writeOffset, bufLeft, buffer, bufLeft);
        if (retval) {
            return -1;
        }
        retval = HiLogBufferCopy(g_hiLogDev.buffer, HILOG_BUFFER, buffer + bufLeft, bufLen - bufLeft);
    } else {
        retval = HiLogBufferCopy(g_hiLogDev.buffer + g_hiLogDev.writeOffset, bufLeft, buffer, bufLen);
    }
    if (retval < 0) {
        return -1;
    }
    return 0;
}

static void HiLogHeadInit(struct HiLogEntry *header, size_t len)
{
    struct timespec now;
    int ret;

    ret = clock_gettime(CLOCK_REALTIME, &now);
    if (ret != 0) {
        dprintf("In %s line %d,clock_gettime fail", __FUNCTION__, __LINE__);
        return;
    }

    header->len = len;
    header->pid = LOS_GetCurrProcessID();
    header->taskId = LOS_CurTaskIDGet();
    header->sec = now.tv_sec;
    header->nsec = now.tv_nsec;
    header->hdrSize = sizeof(struct HiLogEntry);
}

static void HiLogCoverOldLog(size_t bufLen)
{
    int retval;
    struct HiLogEntry header;
    size_t totalSize = bufLen + sizeof(struct HiLogEntry);

    while (totalSize + g_hiLogDev.size >= HILOG_BUFFER) {
        retval = HiLogReadRingBuffer((unsigned char *)&header, sizeof(header));
        if (retval < 0) {
            break;
        }

        HiLogBufferDec(sizeof(header) + header.len);
    }
}

int HiLogWriteInternal(const char *buffer, size_t bufLen)
{
    struct HiLogEntry header;
    int retval;

    (VOID)LOS_MuxAcquire(&g_hiLogDev.mtx);
    HiLogCoverOldLog(bufLen);
    HiLogHeadInit(&header, bufLen);

    retval = HiLogWriteRingBuffer((unsigned char *)&header, sizeof(header));
    if (retval) {
        retval = -ENODATA;
        goto out;
    }
    HiLogBufferInc(sizeof(header));

    retval = HiLogWriteRingBuffer((unsigned char *)(buffer), header.len);
    if (retval) {
        retval = -ENODATA;
        goto out;
    }

    HiLogBufferInc(header.len);

    retval = header.len;

out:
    (VOID)LOS_MuxRelease(&g_hiLogDev.mtx);
    if (retval > 0) {
        wake_up_interruptible(&g_hiLogDev.wq);
    }
    if (retval < 0) {
        dprintf("write fail retval=%d\n", retval);
    }
    return retval;
}

static ssize_t HiLogWrite(FAR struct file *filep, const char *buffer, size_t bufLen)
{
    (void)filep;
    if (bufLen + sizeof(struct HiLogEntry) > HILOG_BUFFER) {
        dprintf("input too large\n");
        return -ENOMEM;
    }

    return HiLogWriteInternal(buffer, bufLen);
}

static void HiLogDeviceInit(void)
{
    g_hiLogDev.buffer = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, HILOG_BUFFER);
    if (g_hiLogDev.buffer == NULL) {
        dprintf("In %s line %d,LOS_MemAlloc fail", __FUNCTION__, __LINE__);
    }

    init_waitqueue_head(&g_hiLogDev.wq);
    LOS_MuxInit(&g_hiLogDev.mtx, NULL);

    g_hiLogDev.writeOffset = 0;
    g_hiLogDev.headOffset = 0;
    g_hiLogDev.size = 0;
    g_hiLogDev.count = 0;
}

int HiLogDriverInit(VOID)
{
    HiLogDeviceInit();
    return register_driver(HILOG_DRIVER, &g_hilogFops, DRIVER_MODE, NULL);
}

