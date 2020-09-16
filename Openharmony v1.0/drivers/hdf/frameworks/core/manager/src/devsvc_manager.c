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

#include "devsvc_manager.h"
#include "devmgr_service.h"
#include "hdf_base.h"
#include "hdf_cstring.h"
#include "hdf_log.h"
#include "hdf_object_manager.h"
#include "hdf_service_record.h"

#define HDF_LOG_TAG devsvc_manager

struct DevSvcRecord *DevSvcManagerSearchService(struct IDevSvcManager *inst, uint32_t serviceKey)
{
    struct HdfSListIterator it;
    struct DevSvcRecord *record = NULL;
    struct DevSvcRecord *searchResult = NULL;
    struct DevSvcManager *devSvcManager = (struct DevSvcManager *)inst;
    if (devSvcManager == NULL) {
        HDF_LOGE("Search service failed, devSvcManager is null");
        return NULL;
    }

    OsalMutexLock(&devSvcManager->mutex);
    HdfSListIteratorInit(&it, &devSvcManager->services);
    while (HdfSListIteratorHasNext(&it)) {
        record = (struct DevSvcRecord *)HdfSListIteratorNext(&it);
        if ((record != NULL) && (record->key == serviceKey)) {
            searchResult = record;
            break;
        }
    }
    OsalMutexUnlock(&devSvcManager->mutex);
    return searchResult;
}

int DevSvcManagerAddService(struct IDevSvcManager *inst, const char *svcName, struct HdfDeviceObject *service)
{
    struct DevSvcManager *devSvcManager = (struct DevSvcManager *)inst;
    if ((devSvcManager == NULL) || (service == NULL) || (svcName == NULL)) {
        HDF_LOGE("Add service failed, input param is null");
        return HDF_FAILURE;
    }

    struct DevSvcRecord *record = DevSvcRecordNewInstance();
    if (record == NULL) {
        HDF_LOGE("Add service failed, record is null");
        return HDF_FAILURE;
    }

    record->key = HdfStringMakeHashKey(svcName, 0);
    record->value = service;
    OsalMutexLock(&devSvcManager->mutex);
    HdfSListAdd(&devSvcManager->services, &record->entry);
    OsalMutexUnlock(&devSvcManager->mutex);
    return HdfServiceObserverPublishService(
        &devSvcManager->observer, svcName, 0, SERVICE_POLICY_PUBLIC, (struct HdfObject *)service->service);
}

int DevSvcManagerSubscribeService(struct IDevSvcManager *inst, const char *svcName, struct SubscriberCallback callBack)
{
    int ret = HDF_FAILURE;
    struct DevSvcManager *devSvcMgr = (struct DevSvcManager *)inst;
    if (svcName == NULL || devSvcMgr == NULL) {
        return ret;
    }

    ret = HdfServiceObserverSubscribeService(&devSvcMgr->observer, svcName, 0, callBack);
    if (ret != HDF_SUCCESS) {
        return ret;
    }

    struct HdfObject *deviceService = DevSvcManagerGetService(inst, svcName);
    if (deviceService != NULL) {
        if (callBack.OnServiceConnected != NULL) {
            callBack.OnServiceConnected(callBack.deviceObject, deviceService);
        }
        return HDF_SUCCESS;
    }

    return DevmgrServiceLoadDevice(svcName);
}

int DevSvcManagerUnsubscribeService(struct IDevSvcManager *inst, const char *svcName)
{
    struct DevSvcManager *devSvcMgr = (struct DevSvcManager *)inst;
    if (devSvcMgr == NULL) {
        return HDF_FAILURE;
    }
    HdfServiceObserverRemoveRecord(&devSvcMgr->observer, svcName);
    return HDF_SUCCESS;
}


void DevSvcManagerRemoveService(struct IDevSvcManager *inst, const char *svcName)
{
    struct DevSvcManager *devSvcManager = (struct DevSvcManager *)inst;
    uint32_t serviceKey = HdfStringMakeHashKey(svcName, 0);
    if (svcName == NULL || devSvcManager == NULL) {
        return;
    }
    struct DevSvcRecord *serviceRecord = DevSvcManagerSearchService(inst, serviceKey);
    if (serviceRecord != NULL) {
        OsalMutexLock(&devSvcManager->mutex);
        HdfSListRemove(&devSvcManager->services, &serviceRecord->entry);
        OsalMutexUnlock(&devSvcManager->mutex);
    }
}

struct HdfDeviceObject *DevSvcManagerGetObject(struct IDevSvcManager *inst, const char *svcName)
{
    uint32_t serviceKey = HdfStringMakeHashKey(svcName, 0);
    if (svcName == NULL) {
        HDF_LOGE("Get service failed, svcName is null");
        return NULL;
    }
    struct DevSvcRecord *serviceRecord = DevSvcManagerSearchService(inst, serviceKey);
    if (serviceRecord != NULL) {
        return serviceRecord->value;
    }
    HDF_LOGE("Get object failed, serviceRecord is null, svcName is %s", svcName);
    return NULL;
}

struct HdfObject *DevSvcManagerGetService(struct IDevSvcManager *inst, const char *svcName)
{
    struct HdfDeviceObject *deviceObject = DevSvcManagerGetObject(inst, svcName);
    if (deviceObject == NULL) {
        HDF_LOGE("Get service failed");
        return NULL;
    }
    return (struct HdfObject *)deviceObject->service;
}

static bool DevSvcManagerConstruct(struct DevSvcManager *inst)
{
    struct IDevSvcManager *devSvcMgrIf = &inst->super;
    devSvcMgrIf->AddService = DevSvcManagerAddService;
    devSvcMgrIf->SubscribeService = DevSvcManagerSubscribeService;
    devSvcMgrIf->UnsubscribeService = DevSvcManagerUnsubscribeService;
    devSvcMgrIf->RemoveService = DevSvcManagerRemoveService;
    devSvcMgrIf->GetService = DevSvcManagerGetService;
    devSvcMgrIf->GetObject = DevSvcManagerGetObject;
    HdfSListInit(&inst->services);
    if (OsalMutexInit(&inst->mutex) != HDF_SUCCESS) {
        HDF_LOGE("Device service manager create mutex failed!");
        return false;
    }
    return true;
}

struct HdfObject *DevSvcManagerCreate()
{
    static bool isDevSvcManagerInit = false;
    static struct DevSvcManager devSvcManagerInstance;
    if (!isDevSvcManagerInit) {
        if (!DevSvcManagerConstruct(&devSvcManagerInstance)) {
            return NULL;
        }
        isDevSvcManagerInit = true;
    }
    return (struct HdfObject *)&devSvcManagerInstance;
}

void DevSvcManagerRelease(struct HdfObject *object)
{
    struct DevSvcManager *devSvcManager = (struct DevSvcManager *)object;
    if (object == NULL) {
        return;
    }
    HdfSListFlush(&devSvcManager->services, DevSvcRecordDelete);
    OsalMutexDestroy(&devSvcManager->mutex);
}

struct IDevSvcManager *DevSvcManagerGetInstance()
{
    static struct IDevSvcManager *instance = NULL;
    if (instance == NULL) {
        instance = (struct IDevSvcManager *)HdfObjectManagerGetObject(HDF_OBJECT_ID_DEVSVC_MANAGER);
    }
    return instance;
}

