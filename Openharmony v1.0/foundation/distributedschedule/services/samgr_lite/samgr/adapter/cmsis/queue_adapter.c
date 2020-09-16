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
#include "queue_adapter.h"
#include <cmsis_os.h>
#include <ohos_types.h>
#include <ohos_errno.h>

MQueueId QUEUE_Create(const char *name, int size, int count)
{
    osMessageQueueAttr_t queueAttr = {name, 0, NULL, 0, NULL, 0};
    return (MQueueId)osMessageQueueNew(count, size, &queueAttr);
}

int QUEUE_Put(MQueueId queueId, const void *element, uint8 pri, int timeout)
{
    uint32_t waitTime = (timeout <= 0) ? 0 : (uint32_t)timeout;
    osStatus_t ret = osMessageQueuePut(queueId, element, pri, waitTime);
    if (ret != osOK) {
        return EC_BUSBUSY;
    }
    return EC_SUCCESS;
}

int QUEUE_Pop(MQueueId queueId, void *element, uint8 *pri, int timeout)
{
    uint32_t waitTime = (timeout <= 0) ? osWaitForever : (uint32_t)timeout;
    osStatus_t evt = osMessageQueueGet(queueId, element, pri, waitTime);
    if (evt != osOK) {
        return EC_BUSBUSY;
    }
    return EC_SUCCESS;
}

int QUEUE_Destroy(MQueueId queueId)
{
    osStatus_t evt = osMessageQueueDelete(queueId);
    if (evt != osOK) {
        return EC_FAILURE;
    }
    return EC_SUCCESS;
}