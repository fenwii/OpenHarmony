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

#include "osal_irq.h"
#include "los_hwi.h"
#include "hdf_log.h"

#define OSAL_LOG_TAG osal_irq

static void *g_irqDev[OS_HWI_MAX_NUM] = {0};

int32_t OsalRegisterIrq(uint32_t irqId, uint32_t config, OsalIRQHandle handle, const char *name, void *dev)
{
    uint32_t ret;
    HwiIrqParam irqParam;

    if (irqId >= OS_HWI_MAX_NUM) {
        HDF_LOGE("invalid irq number %d\n", irqId);
        return HDF_ERR_INVALID_PARAM;
    }

    g_irqDev[irqId] = dev;
    irqParam.swIrq = (INT32)irqId;
    irqParam.pDevId = dev;
    irqParam.pName = name;
    ret = LOS_HwiCreate(irqId, 0, (HWI_MODE_T)config, (HWI_PROC_FUNC)handle, &irqParam);
    if (ret != LOS_OK) {
        HDF_LOGE("%s %d register fail 0x%x", __func__, irqId, ret);
        return HDF_FAILURE;
    }
    HalIrqUnmask(irqId);

    return HDF_SUCCESS;
}

int32_t OsalUnregisterIrq(uint32_t irqId)
{
    uint32_t ret;
    HwiIrqParam irqParam;

    if (irqId >= OS_HWI_MAX_NUM) {
        HDF_LOGE("invalid irq number %d\n", irqId);
        return HDF_ERR_INVALID_PARAM;
    }

    irqParam.swIrq = (INT32)irqId;
    irqParam.pDevId = g_irqDev[irqId];
    ret = LOS_HwiDelete(irqId, &irqParam);
    if (ret != LOS_OK) {
        HDF_LOGE("irq %d unregister fail %d\n", irqId, ret);
        return HDF_FAILURE;
    }

    g_irqDev[irqId] = NULL;

    return HDF_SUCCESS;
}

int32_t OsalEnableIrq(uint32_t irqId)
{
    if (irqId >= OS_HWI_MAX_NUM) {
        HDF_LOGE("invalid irq number %d\n", irqId);
        return HDF_ERR_INVALID_PARAM;
    }

    HalIrqUnmask(irqId);

    return HDF_SUCCESS;
}

int32_t OsalDisableIrq(uint32_t irqId)
{
    if (irqId >= OS_HWI_MAX_NUM) {
        HDF_LOGE("invalid irq number %d\n", irqId);
        return HDF_ERR_INVALID_PARAM;
    }

    HalIrqMask(irqId);

    return HDF_SUCCESS;
}

