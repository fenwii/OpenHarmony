/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <poll.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <securec.h>
#include <osal_thread.h>
#include <osal_time.h>
#include "hdf_log.h"
#include "hdf_base.h"
#include "hdf_sbuf.h"
#include "osal_mem.h"
#include "hdf_syscall_adapter.h"

#define HDF_LOG_TAG hdf_syscall_adapter
#define EPOLL_MAX_EVENT_SIZE 4
#define TASK_EXIT_WAIT_TIME_MS 10
#define HDF_DEFAULT_BWR_READ_SIZE 1024
#define EVENT_READ_BUFF_GROWTH_RATE 2
#define EVENT_READ_BUFF_MAX (20 * 1024) // 20k

static bool HaveOnlyOneElement(const struct DListHead *head)
{
    if (head->next != head && head->next->next == head) {
        return true;
    }

    return false;
}

static int HdfDevEventGrowReadBuffer(struct HdfWriteReadBuf *buffer)
{
    int newSize = buffer->readSize;

    if (newSize > EVENT_READ_BUFF_MAX) {
        HDF_LOGE("%s: report event size out of max limit", __func__);
        return HDF_DEV_ERR_NORANGE;
    }

    void *newBuff = OsalMemAlloc(newSize);
    if (newBuff == NULL) {
        HDF_LOGE("%s:oom,%d", __func__, newSize);
        return HDF_DEV_ERR_NO_MEMORY;
    }

    OsalMemFree((void*)buffer->readBuffer);
    buffer->readBuffer = (uintptr_t)newBuff;
    return HDF_SUCCESS;
}

static int HdfDevEventReadAndDispatch(struct HdfDevListenerThread *thread)
{
    struct HdfWriteReadBuf bwr = {0};
    struct HdfSBuf *sbuf = NULL;
    int ret = HDF_SUCCESS;

    bwr.readBuffer = (uintptr_t)OsalMemAlloc(HDF_DEFAULT_BWR_READ_SIZE);
    bwr.cmdCode = -1;
    bwr.readConsumed = 0;
    bwr.readSize = HDF_DEFAULT_BWR_READ_SIZE;
    if (bwr.readBuffer == (uintptr_t)NULL) {
        HDF_LOGE("%s: oom", __func__);
        return HDF_DEV_ERR_NO_MEMORY;
    }

    OsalMutexLock(&thread->mutex);
    if (thread->adapter == NULL) {
        goto finish;
    }

    while (true) {
        ret = ioctl(thread->adapter->fd, HDF_READ_DEV_EVENT, &bwr);
        if (ret == 0) {
            break;
        }
        if (errno == -HDF_DEV_ERR_NORANGE) {
            if (HdfDevEventGrowReadBuffer(&bwr) == HDF_SUCCESS) {
                continue;  /* read buffer may not enough, grow read buffer and try again */
            }
        }

        HDF_LOGE("%s:ioctl fail %d %s", __func__, errno, strerror(errno));
        goto finish;
    }

    if (bwr.readConsumed == 0) {
        HDF_LOGE("%s:event read nothing", __func__);
        ret = HDF_DEV_ERR_NODATA;
        goto finish;
    }
    sbuf = HdfSBufBind(bwr.readBuffer, bwr.readConsumed);
    if (sbuf == NULL) {
        HDF_LOGE("%s:sbuf oom", __func__);
        ret = HDF_DEV_ERR_NO_MEMORY;
        goto finish;
    }
    struct HdfDevEventlistener *listener = NULL;
    DLIST_FOR_EACH_ENTRY(listener, &thread->adapter->listenerList, struct HdfDevEventlistener, listNode) {
        (void)listener->callBack(listener->priv, bwr.cmdCode, sbuf);
        HdfSbufFlush(sbuf);
        sbuf->writePos = bwr.readConsumed;
    }
finish:
    HdfSBufRecycle(sbuf);
    OsalMemFree((void*)bwr.readBuffer);
    OsalMutexUnlock(&thread->mutex);
    return ret;
}

#define POLL_WAIT_TIME_MS 100
static int32_t HdfDevEventLintenTask(void *para)
{
    struct HdfDevListenerThread *thread = (struct HdfDevListenerThread *)para;
    struct pollfd pfd;

    thread->status = LISTENER_RUNNING;
    pfd.fd = thread->adapter->fd;
    pfd.events = POLLIN;
    pfd.revents = 0;

    while (!thread->shouldStop) {
        int pollSize = poll(&pfd, 1, -1);
        int ret = HDF_FAILURE;
        if (pollSize > 0) {
            if (((uint32_t)pfd.revents) & POLLIN) {
                ret = HdfDevEventReadAndDispatch(thread);
            } else if (((uint32_t)pfd.revents) & POLLHUP) {
                break;
            }
        }

        if (ret != HDF_SUCCESS) {
            OsalMSleep(POLL_WAIT_TIME_MS);
        }
    }

    HDF_LOGE("event listener task exit");
    OsalMutexDestroy(&thread->mutex);
    OsalThreadDestroy(&thread->thread);

    if (thread->shouldStop == true) {
        OsalMemFree(thread);
    } else {
        thread->status = LISTENER_STOPPED;
    }
    return HDF_SUCCESS;
}

static int HdfDevListenerThreadInit(struct HdfDevListenerThread *thread)
{
    if (thread->status != LISTENER_UNINIT) {
        return HDF_SUCCESS;
    }

    thread->status = LISTENER_STOPPED;
    thread->shouldStop = false;

    if (OsalMutexInit(&thread->mutex) != HDF_SUCCESS) {
        HDF_LOGE("%s: fail to create thread", __func__);
        thread->status = LISTENER_UNINIT;
        return HDF_ERR_BAD_FD;
    }

    int32_t ret = OsalThreadCreate(&thread->thread, HdfDevEventLintenTask, thread);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: fail to create thread", __func__);
        thread->status = LISTENER_UNINIT;
        OsalMutexDestroy(&thread->mutex);
        return HDF_ERR_BAD_FD;
    }

    return HDF_SUCCESS;
}

static int HdfDevListenerThreadStart(struct HdfDevListenerThread *thread)
{
    if (thread->status == LISTENER_UNINIT) {
        if (HdfDevListenerThreadInit(thread) != HDF_SUCCESS) {
            return HDF_FAILURE;
        }
    }
    int ret = HDF_FAILURE;
    do {
        if (ioctl(thread->adapter->fd, HDF_LISTEN_EVENT_START, 0) != 0) {
            HDF_LOGE("%s: fail to tell drv start %d %s", __func__, errno, strerror(errno));
            ret = HDF_ERR_IO;
            break;
        }

        struct OsalThreadParam config = {
            .name = "hdf_event_listener",
            .priority = OSAL_THREAD_PRI_DEFAULT,
            .stackSize = 0,
        };

        if (OsalThreadStart(&thread->thread, &config) != HDF_SUCCESS) {
            HDF_LOGE("%s:OsalThreadStart failed", __func__);
            ret = HDF_FAILURE;
            break;
        }
        thread->status = LISTENER_RUNNING;
        return HDF_SUCCESS;
    } while (0);

    OsalThreadDestroy(&thread->thread);
    OsalMutexDestroy(&thread->mutex);
    return ret;
}

static void HdfDevListenerThreadDestory(struct HdfDevListenerThread *thread)
{
    if (thread == NULL || thread->adapter == NULL) {
        return;
    }
    if (ioctl(thread->adapter->fd, HDF_LISTEN_EVENT_STOP, 0) != 0) {
        HDF_LOGE("%s: fail to tell drv stop, use async stop", __func__);
        OsalMutexLock(&thread->mutex);
        thread->adapter = NULL;
        OsalMutexUnlock(&thread->mutex);
        thread->shouldStop = true;
        return;
    }

    while (thread->status != LISTENER_STOPPED) {
        OsalMSleep(TASK_EXIT_WAIT_TIME_MS);
    }
    OsalMemFree(thread);
}

static int HdfSyscallAdapterDispatch(struct HdfObject *object, int code, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    if (object == NULL) {
        HDF_LOGE("Input object is null");
        return HDF_FAILURE;
    }
    struct HdfSyscallAdapter *ioService = (struct HdfSyscallAdapter *)object;
    struct HdfWriteReadBuf wrBuf;
    if (reply != NULL) {
        wrBuf.readBuffer = (uintptr_t)HdfSbufGetData(reply);
        wrBuf.readSize =  HdfSbufGetCapacity(reply);
    } else {
        wrBuf.readBuffer = 0;
        wrBuf.readSize = 0;
    }
    if (data != NULL) {
        wrBuf.writeBuffer = (uintptr_t)HdfSbufGetData(data);
        wrBuf.writeSize =  HdfSbufGetDataSize(data);
    } else {
        wrBuf.writeBuffer = 0;
        wrBuf.writeSize = 0;
    }

    wrBuf.readConsumed = 0;
    wrBuf.writeConsumed = 0;
    wrBuf.cmdCode = code;
    int ret = ioctl(ioService->fd,  HDF_WRITE_READ, &wrBuf);
    if (ret < 0) {
        HDF_LOGE("dispatch serv call ioctl fail %d", errno);
    }
    if (reply != NULL) {
        reply->writePos = wrBuf.readConsumed;
    }
    return ret;
}

static int32_t HdfLoadDriverByServiceName(const char *serviceName)
{
    int32_t ret = HDF_FAILURE;
    struct HdfSBuf *data = NULL;
    struct HdfIoService *ioService = HdfIoServiceBind(DEV_MGR_NODE, 0);
    if (ioService == NULL) {
        HDF_LOGE("Fail to get %s service", DEV_MGR_NODE);
        return ret;
    }
    data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        HDF_LOGE("fail to obtain sbuf data");
        ret = HDF_DEV_ERR_NO_MEMORY;
        goto out;
    }
    if (!HdfSbufWriteString(data, serviceName)) {
        HDF_LOGE("fail to write sbuf");
        ret = HDF_FAILURE;
        goto out;
    }
    ret = ioService->dispatcher->Dispatch(&ioService->object, 0, data, NULL);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("fail to send service call");
    }
out:
    HdfIoServiceRecycle(ioService);
    HdfSBufRecycle(data);
    return ret;
}

struct HdfIoService *HdfIoServiceAdapterObtain(const char *serviceName, mode_t mode)
{
    struct HdfSyscallAdapter *adapter = NULL;
    struct HdfIoService *ioService = NULL;
    char devNodePath[PATH_MAX] = {0};
    char realPath[PATH_MAX] = {0};
    if (mode > MAX_MODE_SIZE) {
        return NULL;
    }

    if (sprintf_s(devNodePath, PATH_MAX - 1, "%s%s", DEV_NODE_PATH, serviceName) < 0) {
        HDF_LOGE("Get node path failed");
        return NULL;
    }

    if (realpath(devNodePath, realPath) == NULL) {
        HDF_LOGE("%s file name %s is invalid", __func__, devNodePath);
        if (HdfLoadDriverByServiceName(serviceName) != HDF_SUCCESS) {
            HDF_LOGE("%s load %s driver failed", __func__, serviceName);
            return NULL;
        }
        if (realpath(devNodePath, realPath) == NULL) {
            return NULL;
        }
    }

    adapter = (struct HdfSyscallAdapter *)OsalMemCalloc(sizeof(struct HdfSyscallAdapter));
    if (adapter == NULL) {
        HDF_LOGE("Alloc syscall adapter failed");
        return NULL;
    }

    DListHeadInit(&adapter->listenerList);
    if (OsalMutexInit(&adapter->mutex)) {
        HDF_LOGE("%s: create mutex fail", __func__);
        OsalMemFree(adapter);
        return NULL;
    }

    adapter->fd = open(realPath, O_RDWR);
    if (adapter->fd < 0) {
        HDF_LOGE("Open file node failed");
        OsalMutexDestroy(&adapter->mutex);
        OsalMemFree(adapter);
        return NULL;
    }

    ioService = &adapter->super;
    static struct HdfIoDispatcher dispatch = {
        .Dispatch = HdfSyscallAdapterDispatch,
    };
    ioService->dispatcher = &dispatch;
    return ioService;
}

void HdfIoServiceAdapterRecycle(struct HdfIoService *service)
{
    struct HdfSyscallAdapter *adapter = (struct HdfSyscallAdapter *)service;
    if (adapter != NULL) {
        HdfDevListenerThreadDestory(adapter->thread);
        if (adapter->fd >= 0) {
            close(adapter->fd);
            adapter->fd = -1;
        }
        OsalMutexDestroy(&adapter->mutex);
        OsalMemFree(adapter);
    }
}

static int HdfStartListenDevEvent(struct HdfDevListenerThread *thread)
{
    return HdfDevListenerThreadStart(thread);
}

static bool AddListenerToAdapterLocked(struct HdfSyscallAdapter *adapter, struct HdfDevEventlistener *listener)
{
    struct HdfDevEventlistener *it = NULL;
    DLIST_FOR_EACH_ENTRY(it, &adapter->listenerList, struct HdfDevEventlistener, listNode) {
        if (it == listener) {
            HDF_LOGE("add duplicate dev-event listener");
            return false;
        }
    }
    DListInsertTail(&listener->listNode, &adapter->listenerList);
    return true;
}

int HdfDeviceRegisterEventListener(struct HdfIoService *target, struct HdfDevEventlistener *listener)
{
    if (target == NULL || listener == NULL || listener->callBack == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }

    struct HdfSyscallAdapter *adapter = (struct HdfSyscallAdapter *)target;

    OsalMutexLock(&adapter->mutex);
    if (!AddListenerToAdapterLocked(adapter, listener)) {
        OsalMutexUnlock(&adapter->mutex);
        return HDF_ERR_INVALID_PARAM;
    }
    if (adapter->thread != NULL) {
        OsalMutexUnlock(&adapter->mutex);
        return HDF_SUCCESS;
    }

    struct HdfDevListenerThread *thread =
        (struct HdfDevListenerThread *)OsalMemAlloc(sizeof(struct HdfDevListenerThread));
    if (thread == NULL) {
        HDF_LOGE("%s:thread oom", __func__);
        DListRemove(&listener->listNode);
        OsalMutexUnlock(&adapter->mutex);
        return HDF_ERR_MALLOC_FAIL;
    }
    thread->status = LISTENER_UNINIT;
    thread->adapter = adapter;

    int ret =  HdfStartListenDevEvent(thread);
    if (ret == HDF_SUCCESS) {
        adapter->thread = thread;
    } else {
        DListRemove(&listener->listNode);
        OsalMemFree(thread);
        adapter->thread = NULL;
    }

    OsalMutexUnlock(&adapter->mutex);
    return ret;
}

int HdfDeviceUnregisterEventListener(struct HdfIoService *target, struct HdfDevEventlistener *listener)
{
    if (target == NULL || listener == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    struct HdfSyscallAdapter *adapter = (struct HdfSyscallAdapter *)target;

    OsalMutexLock(&adapter->mutex);
    if (HaveOnlyOneElement(&adapter->listenerList)) {
        if (adapter->thread != NULL) {
            HdfDevListenerThreadDestory(adapter->thread);
            adapter->thread = NULL;
        }
    }
    DListRemove(&listener->listNode);
    OsalMutexUnlock(&adapter->mutex);

    return HDF_SUCCESS;
}
