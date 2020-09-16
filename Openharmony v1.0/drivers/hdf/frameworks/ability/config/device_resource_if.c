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

#include "device_resource_if.h"
#include "hcs_tree_if.h"
#include "hdf_log.h"

static void HcsIfaceConstruct(struct DeviceResourceIface *instance)
{
    instance->GetRootNode = HcsGetRootNode;
    instance->GetBool = HcsGetBool;
    instance->GetUint8 = HcsGetUint8;
    instance->GetUint8ArrayElem = HcsGetUint8ArrayElem;
    instance->GetUint8Array = HcsGetUint8Array;
    instance->GetUint16 = HcsGetUint16;
    instance->GetUint16ArrayElem = HcsGetUint16ArrayElem;
    instance->GetUint16Array = HcsGetUint16Array;
    instance->GetUint32 = HcsGetUint32;
    instance->GetUint32ArrayElem = HcsGetUint32ArrayElem;
    instance->GetUint32Array = HcsGetUint32Array;
    instance->GetUint64 = HcsGetUint64;
    instance->GetUint64ArrayElem = HcsGetUint64ArrayElem;
    instance->GetUint64Array = HcsGetUint64Array;
    instance->GetString = HcsGetString;
    instance->GetStringArrayElem = HcsGetStringArrayElem;
    instance->GetElemNum = HcsGetElemNum;
    instance->GetNodeByMatchAttr = HcsGetNodeByMatchAttr;
    instance->GetChildNode = HcsGetChildNode;
    instance->GetNodeByRefAttr = HcsGetNodeByRefAttr;
}

static bool DeviceResourceIfaceConstruct(struct DeviceResourceIface *instance, DeviceResourceType type)
{
    switch (type) {
        case HDF_CONFIG_SOURCE:
            HcsIfaceConstruct(instance);
            break;
        default:
            HDF_LOGE("%s: Currently, this configuration type is not supported. the type is %d", __func__, type);
            return false;
    }
    return true;
}

struct DeviceResourceIface *DeviceResourceGetIfaceInstance(DeviceResourceType type)
{
    static struct DeviceResourceIface *instance = NULL;
    if (instance == NULL) {
        static struct DeviceResourceIface singletonInstance;
        if (!DeviceResourceIfaceConstruct(&singletonInstance, type)) {
            return NULL;
        }
        instance = &singletonInstance;
    }
    return instance;
}
