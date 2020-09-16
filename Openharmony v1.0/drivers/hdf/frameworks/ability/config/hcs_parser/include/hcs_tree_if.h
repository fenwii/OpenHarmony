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

#ifndef HCS_TREE_IF_H
#define HCS_TREE_IF_H

#include "device_resource_if.h"
#include "hdf_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HCS_MATCH_ATTR "match_attr"

const struct DeviceResourceNode *HcsGetRootNode(void);
bool HcsGetBool(const struct DeviceResourceNode *node, const char *attrName);
int32_t HcsGetUint8(const struct DeviceResourceNode *node, const char *attrName, uint8_t *value, uint8_t def);
int32_t HcsGetUint8ArrayElem(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
    uint8_t *value, uint8_t def);
int32_t HcsGetUint8Array(const struct DeviceResourceNode *node, const char *attrName, uint8_t *value, uint32_t len,
    uint8_t def);
int32_t HcsGetUint16(const struct DeviceResourceNode *node, const char *attrName, uint16_t *value, uint16_t def);
int32_t HcsGetUint16ArrayElem(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
    uint16_t *value, uint16_t def);
int32_t HcsGetUint16Array(const struct DeviceResourceNode *node, const char *attrName, uint16_t *value, uint32_t len,
    uint16_t def);
int32_t HcsGetUint32(const struct DeviceResourceNode *node, const char *attrName, uint32_t *value, uint32_t def);
int32_t HcsGetUint32ArrayElem(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
    uint32_t *value, uint32_t def);
int32_t HcsGetUint32Array(const struct DeviceResourceNode *node, const char *attrName, uint32_t *value,
    uint32_t len, uint32_t def);
int32_t HcsGetUint64(const struct DeviceResourceNode *node, const char *attrName, uint64_t *value, uint64_t def);
int32_t HcsGetUint64ArrayElem(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
    uint64_t *value, uint64_t def);
int32_t HcsGetUint64Array(const struct DeviceResourceNode *node, const char *attrName, uint64_t *value,
    uint32_t len, uint64_t def);
int32_t HcsGetStringArrayElem(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
    const char **value, const char *def);
int32_t HcsGetString(const struct DeviceResourceNode *node, const char *attrName, const char **value, const char *def);
int32_t HcsGetElemNum(const struct DeviceResourceNode *node, const char *attrName);
const struct DeviceResourceNode *HcsGetNodeByMatchAttr(const struct DeviceResourceNode *node, const char *attrValue);
const struct DeviceResourceNode *HcsGetChildNode(const struct DeviceResourceNode *node, const char *nodeName);
const struct DeviceResourceNode *HcsGetNodeByRefAttr(const struct DeviceResourceNode *node, const char *attrName);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // HCS_TREE_IF_H