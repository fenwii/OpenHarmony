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

#include "hdf_workqueue.h"
#include "linux/workqueue.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG hdf_workqueue

struct WorkWrapper {
    HdfWorkFunc workFunc;
    void *para;
    void *work;
};

int32_t HdfWorkQueueInit(HdfWorkQueue *queue, char *name)
{
    if (queue == NULL || name == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    queue->realWorkQueue = create_singlethread_workqueue(name);
    if (queue->realWorkQueue == NULL) {
        HDF_LOGE("%s create queue fail", __func__);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

static void WorkEntry(struct work_struct *para)
{
    HdfWork *work = NULL;
    struct WorkWrapper *wrapper = NULL;
    if (para != NULL && para->data != 0) {
        work = (HdfWork *)(uintptr_t)para->data;
        wrapper = (struct WorkWrapper *)work->realWork;
        if (wrapper != NULL && wrapper->workFunc != NULL) {
            wrapper->workFunc(wrapper->para);
        } else {
            HDF_LOGE("%s routine null", __func__);
        }
    } else {
        HDF_LOGE("%s work null", __func__);
    }
}

int32_t HdfWorkInit(HdfWork *work, HdfWorkFunc func, void *para)
{
    struct work_struct *realWork = NULL;
    struct WorkWrapper *wrapper = NULL;
    char *base = NULL;

    if (work == NULL || func == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    work->realWork = NULL;

    base = (char *)OsalMemCalloc(sizeof(*realWork) + sizeof(*wrapper));
    if (base == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        return HDF_ERR_MALLOC_FAIL;
    }
    wrapper = (struct WorkWrapper *)base;
    realWork = (struct work_struct *)(base + sizeof(*wrapper));
    wrapper->work = realWork;
    wrapper->workFunc = func;
    wrapper->para = para;

    INIT_WORK(realWork, WorkEntry);
    realWork->data = (atomic_long_t)(uintptr_t)work;
    work->realWork = wrapper;

    return HDF_SUCCESS;
}

int32_t HdfDelayedWorkInit(HdfWork *work, HdfWorkFunc func, void *para)
{
    struct delayed_work *realWork = NULL;
    struct WorkWrapper *wrapper = NULL;
    char *base = NULL;

    if (work == NULL || func == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    work->realWork = NULL;

    base = (char *)OsalMemCalloc(sizeof(*realWork) + sizeof(*wrapper));
    if (base == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        return HDF_ERR_MALLOC_FAIL;
    }
    wrapper = (struct WorkWrapper *)base;
    realWork = (struct delayed_work *)(base + sizeof(*wrapper));
    wrapper->work = realWork;
    wrapper->workFunc = func;
    wrapper->para = para;

    INIT_DELAYED_WORK(realWork, WorkEntry);
    realWork->work.data = (atomic_long_t)(uintptr_t)work;
    work->realWork = wrapper;

    return HDF_SUCCESS;
}

void HdfWorkDestroy(HdfWork *work)
{
    if (work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return;
    }

    OsalMemFree(work->realWork);
    work->realWork = NULL;

    return;
}

void HdfDelayedWorkDestroy(HdfWork *work)
{
    if (work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return;
    }

    return HdfWorkDestroy(work);
}

void HdfWorkQueueDestroy(HdfWorkQueue *queue)
{
    if (queue == NULL || queue->realWorkQueue == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return;
    }

    destroy_workqueue(queue->realWorkQueue);

    return;
}

bool HdfAddWork(HdfWorkQueue *queue, HdfWork *work)
{
    if (queue == NULL || queue->realWorkQueue == NULL || work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return false;
    }

    return queue_work(queue->realWorkQueue, ((struct WorkWrapper *)work->realWork)->work);
}

bool HdfAddDelayedWork(HdfWorkQueue *queue, HdfWork *work, unsigned long ms)
{
    if (queue == NULL || queue->realWorkQueue == NULL || work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return false;
    }

    return queue_delayed_work(queue->realWorkQueue, ((struct WorkWrapper *)work->realWork)->work, LOS_MS2Tick(ms));
}

unsigned int HdfWorkBusy(HdfWork *work)
{
    if (work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return 0;
    }

    return work_busy(((struct WorkWrapper *)work->realWork)->work);
}

bool HdfCancelWorkSync(HdfWork *work)
{
    if (work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return false;
    }

    return cancel_work_sync(((struct WorkWrapper *)work->realWork)->work);
}

bool HdfCancelDelayedWorkSync(HdfWork *work)
{
    if (work == NULL || work->realWork == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return false;
    }

    return cancel_delayed_work_sync(((struct WorkWrapper *)work->realWork)->work);
}

