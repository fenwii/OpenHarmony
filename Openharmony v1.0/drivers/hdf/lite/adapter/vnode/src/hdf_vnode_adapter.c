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

#include <fs/fs.h>
#include <user_copy.h>
#include <fs_poll_pri.h>
#include <osal_mem.h>
#include <osal_sem.h>
#include "hdf_sbuf.h"
#include "hdf_log.h"
#include "hdf_syscall_adapter.h"
#include "hdf_device_node_ext.h"
#include "hdf_vnode_adapter.h"

#define HDF_LOG_TAG hdf_vnode_adapter

#define VOID_DATA_SIZE 4
#define EVENT_QUEUE_MAX 100
#define MAX_RW_SIZE (1024*1204) // 1M

enum HdfVNodeClientStatus {
    VNODE_CLIENT_RUNNING,
    VNODE_CLIENT_LISTENING,
    VNODE_CLIENT_STOPPED,
};
struct HdfVNodeAdapterClient {
    struct HdfVNodeAdapter *adapter;
    struct HdfDeviceIoClient ioServiceClient;
    wait_queue_head_t pollWait;
    struct HdfIoService *serv;
    struct OsalMutex mutex;
    struct DListHead eventQueue;
    struct DListHead listNode;
    int32_t eventQueueSize;
    uint32_t status;
};

static struct HdfSBuf *HdfSbufCopyFromUser(uintptr_t data, size_t size)
{
    if (size == 0) {
        return HdfSBufObtain(VOID_DATA_SIZE);
    }
    uint8_t *kData = OsalMemAlloc(size);
    if (kData == NULL) {
        HDF_LOGE("%s:oom", __func__);
        return NULL;
    }
    if (LOS_ArchCopyFromUser((void*)kData, (void*)data, size) != 0) {
        HDF_LOGE("%s:copy from user fail", __func__);
        OsalMemFree(kData);
        return NULL;
    }

    struct HdfSBuf *sbuf = HdfSBufBind((uintptr_t)kData, size);
    if (sbuf == NULL) {
        OsalMemFree(kData);
    }
    HdfSbufTransDataOwnership(sbuf);

    return sbuf;
}

static int HdfSbufCopyToUser(const struct HdfSBuf *sbuf, void *dstUser, size_t dstUserSize)
{
    size_t sbufSize = HdfSbufGetDataSize(sbuf);
    if (sbufSize == 0) {
        return HDF_SUCCESS;
    }
    if (dstUserSize < sbufSize) {
        HDF_LOGE("%s: readBuffer too small %u", __func__, sbufSize);
        return HDF_DEV_ERR_NORANGE;
    }

    if (LOS_ArchCopyToUser(dstUser, HdfSbufGetData(sbuf), sbufSize) != 0) {
        HDF_LOGE("%s: copy buff data fail", __func__);
        return HDF_ERR_IO;
    }

    return HDF_SUCCESS;
}

static void DevEventFree(struct HdfDevEvent *event)
{
    if (event == NULL) {
        return;
    }
    if (event->data != NULL) {
        HdfSBufRecycle(event->data);
        event->data = NULL;
    }
    OsalMemFree(event);
}

static int HdfVNodeAdapterServCall(const struct HdfVNodeAdapterClient *client, unsigned long arg)
{
    struct HdfWriteReadBuf bwr;
    struct HdfWriteReadBuf *bwrUser = (struct HdfWriteReadBuf *)((uintptr_t)arg);

    if (bwrUser == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    if (LOS_ArchCopyFromUser(&bwr, (void*)bwrUser, sizeof(bwr)) != 0) {
        HDF_LOGE("Copy from user failed");
        return HDF_FAILURE;
    }
    if (bwr.writeSize > MAX_RW_SIZE || bwr.readSize > MAX_RW_SIZE) {
        return HDF_ERR_INVALID_PARAM;
    }

    struct HdfSBuf *data = HdfSbufCopyFromUser(bwr.writeBuffer, bwr.writeSize);
    if (data == NULL) {
        HDF_LOGE("Vnode adapter bind data is null");
        return HDF_FAILURE;
    }
    struct HdfSBuf *reply = HdfSBufObtainDefaultSize();
    if (reply == NULL) {
        HDF_LOGE("%s:oom", __func__);
        HdfSBufRecycle(data);
        return HDF_FAILURE;
    }
    (void)HdfSbufWriteUint64(reply, (uintptr_t)&client->ioServiceClient);
    int ret = client->adapter->ioService.dispatcher->Dispatch(client->adapter->ioService.target,
        bwr.cmdCode, data, reply);
    if (bwr.readSize != 0 && HdfSbufCopyToUser(reply, (void*)bwr.readBuffer, bwr.readSize) != HDF_SUCCESS) {
        HdfSBufRecycle(data);
        HdfSBufRecycle(reply);
        return HDF_ERR_IO;
    }
    bwr.readConsumed = HdfSbufGetDataSize(reply);
    if (LOS_ArchCopyToUser(bwrUser, &bwr, sizeof(struct HdfWriteReadBuf)) != 0) {
        HDF_LOGE("%s: copy bwr fail", __func__);
        ret = HDF_FAILURE;
    }

    HdfSBufRecycle(data);
    HdfSBufRecycle(reply);
    return ret;
}

static int HdfVNodeAdapterReadDevEvent(struct HdfVNodeAdapterClient *client, unsigned long arg)
{
    struct HdfWriteReadBuf bwr;
    struct HdfWriteReadBuf *bwrUser = (struct HdfWriteReadBuf *)((uintptr_t)arg);
    int ret = HDF_SUCCESS;
    if (bwrUser == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }

    if (LOS_ArchCopyFromUser(&bwr, (void*)bwrUser, sizeof(bwr)) != 0) {
        HDF_LOGE("Copy from user failed");
        return HDF_FAILURE;
    }

    if (bwr.readSize > MAX_RW_SIZE) {
        return HDF_ERR_INVALID_PARAM;
    }
    OsalMutexLock(&client->mutex);

    if (DListIsEmpty(&client->eventQueue)) {
        OsalMutexUnlock(&client->mutex);
        return HDF_DEV_ERR_NODATA;
    }

    struct HdfDevEvent *event = CONTAINER_OF(client->eventQueue.next, struct HdfDevEvent, listNode);
    size_t eventSize = HdfSbufGetDataSize(event->data);
    if (eventSize > bwr.readSize) {
        bwr.readSize = eventSize;
        ret = HDF_DEV_ERR_NORANGE;
    } else {
        if (HdfSbufCopyToUser(event->data, (void *)bwr.readBuffer, bwr.readSize) != HDF_SUCCESS) {
            OsalMutexUnlock(&client->mutex);
            return HDF_ERR_IO;
        }
        bwr.readConsumed = eventSize;
        bwr.cmdCode = event->id;
    }

    if (LOS_ArchCopyToUser(bwrUser, &bwr, sizeof(struct HdfWriteReadBuf)) != 0) {
        HDF_LOGE("%s: copy bwr fail", __func__);
        ret = HDF_ERR_IO;
    }
    if (ret == HDF_SUCCESS) {
        DListRemove(&event->listNode);
        DevEventFree(event);
        client->eventQueueSize--;
    }

    OsalMutexUnlock(&client->mutex);
    return ret;
}

static void HdfVnodeAdapterDropOldEventLocked(struct HdfVNodeAdapterClient *client)
{
    HDF_LOGE("dev event queue full, drop old one");
    struct HdfDevEvent *dropEvent = CONTAINER_OF(client->eventQueue.next, struct HdfDevEvent, listNode);
    DListRemove(&dropEvent->listNode);
    DevEventFree(dropEvent);
    client->eventQueueSize--;
}

static int VNodeAdapterSendDevEventToClient(struct HdfVNodeAdapterClient *vnodeClient,
    uint32_t id, const struct HdfSBuf *data)
{
    OsalMutexLock(&vnodeClient->mutex);
    if (vnodeClient->status != VNODE_CLIENT_LISTENING) {
        OsalMutexUnlock(&vnodeClient->mutex);
        return HDF_SUCCESS;
    }
    if (vnodeClient->eventQueueSize >= EVENT_QUEUE_MAX) {
        HdfVnodeAdapterDropOldEventLocked(vnodeClient);
    }
    struct HdfDevEvent *event = OsalMemAlloc(sizeof(struct HdfDevEvent));
    if (event == NULL) {
        OsalMutexUnlock(&vnodeClient->mutex);
        return HDF_DEV_ERR_NO_MEMORY;
    }
    event->id = id;
    event->data = HdfSBufCopy(data);
    if (event->data == NULL) {
        OsalMutexUnlock(&vnodeClient->mutex);
        HDF_LOGE("%s: sbuf oom", __func__);
        OsalMemFree(event);
        return HDF_DEV_ERR_NO_MEMORY;
    }
    DListInsertTail(&event->listNode, &vnodeClient->eventQueue);
    vnodeClient->eventQueueSize++;
    wake_up_interruptible(&vnodeClient->pollWait);
    OsalMutexUnlock(&vnodeClient->mutex);

    return HDF_SUCCESS;
}

static int HdfVNodeAdapterSendDevEvent(struct HdfVNodeAdapter *adapter, struct HdfVNodeAdapterClient *vnodeClient,
    uint32_t id, const struct HdfSBuf *data)
{
    if (adapter == NULL || data == NULL || HdfSbufGetDataSize(data) == 0) {
        return HDF_ERR_INVALID_PARAM;
    }
    struct HdfVNodeAdapterClient *client = NULL;
    OsalMutexLock(&adapter->mutex);
    int ret = HDF_FAILURE;
    DLIST_FOR_EACH_ENTRY(client, &adapter->clientList, struct HdfVNodeAdapterClient, listNode) {
        if (vnodeClient != NULL && client != vnodeClient) {
            continue;
        }
        ret = VNodeAdapterSendDevEventToClient(client, id, data);
        if (ret != HDF_SUCCESS) {
            break;
        }
    }
    OsalMutexUnlock(&adapter->mutex);
    return ret;
}

static void HdfVNodeAdapterClientStartListening(struct HdfVNodeAdapterClient *client)
{
    OsalMutexLock(&client->mutex);
    client->status = VNODE_CLIENT_LISTENING;
    OsalMutexUnlock(&client->mutex);
}

static void HdfVNodeAdapterClientStopListening(struct HdfVNodeAdapterClient *client)
{
    OsalMutexLock(&client->mutex);
    client->status = VNODE_CLIENT_STOPPED;
    wake_up_interruptible(&client->pollWait);
    OsalMutexUnlock(&client->mutex);
}

static int HdfVNodeAdapterIoctl(struct file *filep, int cmd, unsigned long arg)
{
    struct HdfVNodeAdapterClient *client = (struct HdfVNodeAdapterClient *)filep->f_priv;
    if (client == NULL) {
        return HDF_DEV_ERR_NO_DEVICE;
    }
    switch (cmd) {
        case HDF_WRITE_READ:
            if (client->serv == NULL) {
                return HDF_DEV_ERR_NO_DEVICE;
            }
            return HdfVNodeAdapterServCall(client, arg);
        case HDF_READ_DEV_EVENT:
            return HdfVNodeAdapterReadDevEvent(client, arg);
        case HDF_LISTEN_EVENT_START:
            HdfVNodeAdapterClientStartListening(client);
            break;
        case HDF_LISTEN_EVENT_STOP:
            HdfVNodeAdapterClientStopListening(client);
            break;
        default:
            return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

static struct HdfVNodeAdapterClient *HdfNewVNodeAdapterClient(struct HdfVNodeAdapter *adapter)
{
    struct HdfVNodeAdapterClient *client = OsalMemAlloc(sizeof(struct HdfVNodeAdapterClient));
    if (client == NULL) {
        HDF_LOGE("%s: oom", __func__);
        return NULL;
    }
    if (OsalMutexInit(&client->mutex) != HDF_SUCCESS) {
        OsalMemFree(client);
        HDF_LOGE("%s: no mutex", __func__);
        return NULL;
    }

    DListHeadInit(&client->eventQueue);
    client->eventQueueSize = 0;
    client->serv = &adapter->ioService;
    client->status = VNODE_CLIENT_RUNNING;
    client->adapter = adapter;
    client->eventQueueSize = 0;
    client->ioServiceClient.device = (struct HdfDeviceObject *)adapter->ioService.target;
    client->ioServiceClient.priv = NULL;
    __init_waitqueue_head(&client->pollWait);
    OsalMutexLock(&adapter->mutex);
    DListInsertTail(&client->listNode, &adapter->clientList);
    OsalMutexUnlock(&adapter->mutex);

    return client;
}

static void HdfDestoryVNodeAdapterClient(struct HdfVNodeAdapterClient *client)
{
    client->status = VNODE_CLIENT_STOPPED;

    OsalMutexLock(&client->adapter->mutex);
    DListRemove(&client->listNode);
    OsalMutexUnlock(&client->adapter->mutex);

    struct HdfDevEvent *event = NULL;
    struct HdfDevEvent *eventTemp = NULL;

    OsalMutexLock(&client->mutex);
    DLIST_FOR_EACH_ENTRY_SAFE(event, eventTemp, &client->eventQueue, struct HdfDevEvent, listNode) {
        DListRemove(&event->listNode);
        DevEventFree(event);
    }
    OsalMutexUnlock(&client->mutex);
    OsalMutexDestroy(&client->mutex);
    OsalMemFree(client);
}

static int HdfVNodeAdapterOpen(FAR struct file *filep)
{
    struct HdfVNodeAdapter *adapter = (struct HdfVNodeAdapter *)filep->f_inode->i_private;
    if (adapter == NULL) {
        HDF_LOGE("Vnode adapter dispatcher is null");
        return HDF_FAILURE;
    }
    struct HdfVNodeAdapterClient *client = HdfNewVNodeAdapterClient(adapter);
    if (client == NULL) {
        return ETXTBSY;
    }
    filep->f_priv = client;
    if (client->ioServiceClient.device != NULL && client->ioServiceClient.device->service != NULL &&
        client->ioServiceClient.device->service->Open != NULL) {
        int32_t ret = client->ioServiceClient.device->service->Open(&client->ioServiceClient);
        if (ret != HDF_SUCCESS) {
            HdfDestoryVNodeAdapterClient(client);
            return ret;
        }
    }

    return HDF_SUCCESS;
}

static int HdfVNodeAdapterPoll(FAR struct file *filep, poll_table *wait)
{
    unsigned int mask = 0;
    struct HdfVNodeAdapterClient *client = (struct HdfVNodeAdapterClient *)filep->f_priv;

    poll_wait(filep, &client->pollWait, wait);
    OsalMutexLock(&client->mutex);
    if (client->status == VNODE_CLIENT_STOPPED) {
        mask |= POLLHUP;
    } else if (!DListIsEmpty(&client->eventQueue)) {
        mask |= POLLIN;
    }
    OsalMutexUnlock(&client->mutex);
    return mask;
}

static int HdfVNodeAdapterClose(FAR struct file *filep)
{
    struct HdfVNodeAdapterClient *client = (struct HdfVNodeAdapterClient *)filep->f_priv;
    if (client->ioServiceClient.device != NULL && client->ioServiceClient.device->service != NULL &&
        client->ioServiceClient.device->service->Release != NULL) {
        client->ioServiceClient.device->service->Release(&client->ioServiceClient);
    }
    HdfDestoryVNodeAdapterClient(client);
    return HDF_SUCCESS;
}

struct HdfIoService *HdfIoServiceAdapterObtain(const char *serviceName, mode_t mode)
{
    if ((serviceName == NULL) || (mode > MAX_MODE_SIZE)) {
        HDF_LOGE("Input param is invalid, mode is %x", mode);
        return NULL;
    }

    struct HdfVNodeAdapter *vnodeAdapter = (struct HdfVNodeAdapter *)OsalMemCalloc(sizeof(struct HdfVNodeAdapter));
    if (vnodeAdapter == NULL) {
        HDF_LOGE("Alloc remote service is null");
        return NULL;
    }

    int nodePathLength = strlen(serviceName) + strlen(DEV_NODE_PATH) + 1;
    vnodeAdapter->vNodePath = (char *)OsalMemCalloc(nodePathLength);
    if (vnodeAdapter->vNodePath == NULL) {
        HDF_LOGE("Alloc vnode path is null");
        OsalMemFree(vnodeAdapter);
        return NULL;
    }

    if (sprintf_s(vnodeAdapter->vNodePath, nodePathLength, "%s%s", DEV_NODE_PATH, serviceName) < 0) {
        HDF_LOGE("Get node path failed");
        OsalMemFree(vnodeAdapter->vNodePath);
        OsalMemFree(vnodeAdapter);
        return NULL;
    }
    DListHeadInit(&vnodeAdapter->clientList);
    if (OsalMutexInit(&vnodeAdapter->mutex) != HDF_SUCCESS) {
        HDF_LOGE("vnode adapter out of mutex");
        goto error;
    }
    static const struct file_operations_vfs fileOps = {
        .open = HdfVNodeAdapterOpen,
        .ioctl = HdfVNodeAdapterIoctl,
        .poll = HdfVNodeAdapterPoll,
        .close = HdfVNodeAdapterClose,
    };
    int ret = register_driver(vnodeAdapter->vNodePath, &fileOps, mode, vnodeAdapter);
    if (ret != 0) {
        HDF_LOGE("Regist driver failed, ret is: %d", ret);
        OsalMutexDestroy(&vnodeAdapter->mutex);
        goto error;
    }

    return &vnodeAdapter->ioService;
error:
    OsalMemFree(vnodeAdapter->vNodePath);
    OsalMemFree(vnodeAdapter);
    return NULL;
}

void HdfIoServiceAdapterRecycle(struct HdfIoService *service)
{
    if (service != NULL) {
        struct HdfVNodeAdapter *vnodeAdapter = (struct HdfVNodeAdapter *)service;
        if (vnodeAdapter->vNodePath != NULL) {
            (void)unregister_driver(vnodeAdapter->vNodePath);
            OsalMemFree(vnodeAdapter->vNodePath);
        }
        OsalMutexDestroy(&vnodeAdapter->mutex);
        OsalMemFree(vnodeAdapter);
    }
}

int32_t HdfDeviceSendEvent(const struct HdfDeviceObject *deviceObject, uint32_t id, const struct HdfSBuf *data)
{
    if (deviceObject == NULL || data == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }

    struct HdfDeviceNode *deviceNode = CONTAINER_OF(deviceObject, struct HdfDeviceNode, deviceObject);
    if (deviceNode->deviceInfo->policy != SERVICE_POLICY_CAPACITY) {
        return HDF_ERR_NOT_SUPPORT;
    }

    struct HdfVNodeAdapter *adapter = (struct HdfVNodeAdapter *)(((struct DeviceNodeExt*)deviceNode)->ioService);
    return HdfVNodeAdapterSendDevEvent(adapter, NULL, id, data);
}

int32_t HdfDeviceSendEventToClient(const struct HdfDeviceIoClient *client, uint32_t id, const struct HdfSBuf *data)
{
    if (client == NULL || client->device == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    HDF_LOGE("%s: client = %p", __func__, client);
    struct HdfVNodeAdapterClient *vnodeClient = CONTAINER_OF(client, struct HdfVNodeAdapterClient, ioServiceClient);
    if (vnodeClient->adapter == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    HDF_LOGE("%s: client = %p, vnodeClient = %p", __func__, client, vnodeClient);

    return HdfVNodeAdapterSendDevEvent(vnodeClient->adapter, vnodeClient, id, data);
}
