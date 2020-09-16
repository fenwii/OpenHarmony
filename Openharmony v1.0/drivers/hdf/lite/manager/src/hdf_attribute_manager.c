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

#include "hdf_attribute_manager.h"
#include <string.h>
#include "hcs_blob_if.h"
#include "hcs_parser.h"
#include "hcs_tree_if.h"
#include "hdf_device_info.h"
#include "hdf_host_info.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define ATTR_HOST_NAME "hostName"
#define ATTR_DEV_POLICY "policy"
#define ATTR_DEV_PRIORITY "priority"
#define ATTR_DEV_PRELOAD "preload"
#define ATTR_DEV_PERMISSION "permission"
#define ATTR_DEV_MODULENAME "moduleName"
#define ATTR_DEV_SVCNAME "serviceName"
#define ATTR_DEV_MATCHATTR "deviceMatchAttr"
#define MANAGER_NODE_MATCH_ATTR "hdf_manager"

static struct DeviceResourceNode *g_hcsTreeRoot = NULL;

void ReleaseHcsTree(void)
{
    OsalMemFree(g_hcsTreeRoot);
    g_hcsTreeRoot = NULL;
}

void HdfGetBuildInConfigData(const unsigned char **data, unsigned int *size);
static bool CreateHcsToTree(void)
{
    uint32_t length;
    const unsigned char *hcsBlob = NULL;
    HdfGetBuildInConfigData(&hcsBlob, &length);
    if (!HcsCheckBlobFormat((const char *)hcsBlob, length)) {
        return false;
    }
    if (!HcsDecompile((const char *)hcsBlob, HBC_HEADER_LENGTH, &g_hcsTreeRoot)) {
        return false;
    }
    return true;
}

const struct DeviceResourceNode *HcsGetRootNode(void)
{
    if ((g_hcsTreeRoot == NULL) && !CreateHcsToTree()) {
        HDF_LOGE("%s failed", __func__);
        return NULL;
    }
    return g_hcsTreeRoot;
}

static bool HdfHostListCompare(struct HdfSListNode *listEntryFirst, struct HdfSListNode *listEntrySecond)
{
    if (listEntryFirst == NULL || listEntrySecond == NULL) {
        return false;
    }
    struct HdfHostInfo *attrFirst = (struct HdfHostInfo *)listEntryFirst;
    struct HdfHostInfo *attrSecond = (struct HdfHostInfo *)listEntrySecond;
    return attrFirst->priority <= attrSecond->priority;
}

static const struct DeviceResourceNode *GetHdfManagerNode(const struct DeviceResourceNode *node)
{
    return HcsGetNodeByMatchAttr(node, MANAGER_NODE_MATCH_ATTR);
}

static bool GetHostInfo(const struct DeviceResourceNode *hostNode, struct HdfHostInfo *hostInfo)
{
    uint16_t readNum = 0;
    if ((HcsGetString(hostNode, ATTR_HOST_NAME, &hostInfo->hostName, NULL) != HDF_SUCCESS) ||
        (strcmp(hostInfo->hostName, "") == 0)) {
        HDF_LOGW("%s get host name failed", __func__);
        return false;
    }
    if ((HcsGetUint16(hostNode, ATTR_DEV_PRIORITY, &readNum, 0) != HDF_SUCCESS) ||
        (readNum > MAX_PRIORITY_NUM)) {
        HDF_LOGW("%s get host priority failed, priority is: %d", __func__, readNum);
        return false;
    }
    hostInfo->priority = readNum;
    return true;
}

bool HdfAttributeManagerGetHostList(struct HdfSList *hostList)
{
    const struct DeviceResourceNode *hdfManagerNode = NULL;
    const struct DeviceResourceNode *hostNode = NULL;
    uint16_t hostId = 0;
    if (hostList == NULL) {
        return false;
    }

    hdfManagerNode = GetHdfManagerNode(HcsGetRootNode());
    if (hdfManagerNode == NULL) {
        HDF_LOGE("%s get hdf manager node is null", __func__);
        return false;
    }

    hostNode = hdfManagerNode->child;
    while (hostNode != NULL) {
        struct HdfHostInfo *hostInfo = HdfHostInfoNewInstance();
        if (hostInfo == NULL) {
            HdfSListFlush(hostList, HdfHostInfoDelete);
            HDF_LOGE("%s new hostInfo is null", __func__);
            return false;
        }
        if (!GetHostInfo(hostNode, hostInfo)) {
            HdfHostInfoFreeInstance(hostInfo);
            hostInfo = NULL;
            hostNode = hostNode->sibling;
            continue;
        }
        hostInfo->hostId = hostId;
        if (!HdfSListAddOrder(hostList, &hostInfo->node, HdfHostListCompare)) {
            HdfHostInfoFreeInstance(hostInfo);
            hostInfo = NULL;
            hostNode = hostNode->sibling;
            continue;
        }
        hostId++;
        hostNode = hostNode->sibling;
    }
    return true;
}

static bool HdfDeviceListCompare(struct HdfSListNode *listEntryFirst, struct HdfSListNode *listEntrySecond)
{
    if (listEntryFirst == NULL || listEntrySecond == NULL) {
        return false;
    }
    struct HdfDeviceInfo *attrFirst = (struct HdfDeviceInfo *)listEntryFirst;
    struct HdfDeviceInfo *attrSecond = (struct HdfDeviceInfo *)listEntrySecond;
    return attrFirst->priority <= attrSecond->priority;
}

static const struct DeviceResourceNode *GetHostNode(const char *inHostName)
{
    const struct DeviceResourceNode *hdfManagerNode = NULL;
    const struct DeviceResourceNode *hostNode = NULL;
    const char *hostName = NULL;

    hdfManagerNode = GetHdfManagerNode(HcsGetRootNode());
    if (hdfManagerNode == NULL) {
        return NULL;
    }
    hostNode = hdfManagerNode->child;
    while (hostNode != NULL) {
        if (HcsGetString(hostNode, ATTR_HOST_NAME, &hostName, NULL) != HDF_SUCCESS) {
            hostNode = hostNode->sibling;
            continue;
        }
        if (strcmp(hostName, inHostName) == 0) {
            return hostNode;
        }
        hostNode = hostNode->sibling;
    }
    return NULL;
}

static bool CheckDeviceInfo(struct HdfDeviceInfo *deviceNodeInfo)
{
    if (deviceNodeInfo->policy > SERVICE_POLICY_PRIVATE) {
        HDF_LOGE("%s policy is invalid", __func__);
        return false;
    }

    if (deviceNodeInfo->priority > MAX_PRIORITY_NUM) {
        HDF_LOGE("%s priority is invalid", __func__);
        return false;
    }

    if (deviceNodeInfo->preload > DEVICE_PRELOAD_DISABLE) {
        HDF_LOGE("%s preload is invalid", __func__);
        return false;
    }

    return (strcmp(deviceNodeInfo->moduleName, "") != 0);
}

static bool GetDeviceNodeInfo(const struct DeviceResourceNode *deviceNode, struct HdfDeviceInfo *deviceNodeInfo)
{
    uint16_t readNum = 0;
    const char *readString = NULL;
    if (HcsGetUint16(deviceNode, ATTR_DEV_POLICY, &readNum, 0) != HDF_SUCCESS) {
        HDF_LOGE("%s get policy failed", __func__);
        return false;
    }
    deviceNodeInfo->policy = readNum;

    if (HcsGetUint16(deviceNode, ATTR_DEV_PRIORITY, &readNum, 0) != HDF_SUCCESS) {
        HDF_LOGE("%s get priority failed", __func__);
        return false;
    }
    deviceNodeInfo->priority = readNum;

    if (HcsGetUint16(deviceNode, ATTR_DEV_PRELOAD, &readNum, 0) != HDF_SUCCESS) {
        HDF_LOGE("%s get preload failed", __func__);
        return false;
    }
    deviceNodeInfo->preload = readNum;

    if (HcsGetUint16(deviceNode, ATTR_DEV_PERMISSION, &readNum, 0) != HDF_SUCCESS) {
        HDF_LOGE("%s get permission failed", __func__);
        return false;
    }
    deviceNodeInfo->permission = readNum;

    if (HcsGetString(deviceNode, ATTR_DEV_MODULENAME, &readString, NULL) != HDF_SUCCESS) {
        HDF_LOGE("%s get module name failed", __func__);
        return false;
    }
    deviceNodeInfo->moduleName = readString;

    if (HcsGetString(deviceNode, ATTR_DEV_SVCNAME, &readString, NULL) != HDF_SUCCESS) {
        HDF_LOGE("%s get service name failed", __func__);
        return false;
    }
    deviceNodeInfo->svcName = readString;

    if (HcsGetString(deviceNode, ATTR_DEV_MATCHATTR, &readString, NULL) != HDF_SUCCESS) {
        HDF_LOGE("%s get service name failed", __func__);
        return false;
    }
    deviceNodeInfo->deviceMatchAttr = readString;
    return CheckDeviceInfo(deviceNodeInfo);
}

struct HdfSList *HdfAttributeManagerGetDeviceList(uint16_t hostId, const char *hostName)
{
    uint16_t deviceIdx = 0;
    const struct DeviceResourceNode *hostNode = GetHostNode(hostName);
    if (hostNode == NULL) {
        return NULL;
    }
    struct HdfSList *deviceList = (struct HdfSList *)OsalMemCalloc(sizeof(struct HdfSList));
    if (deviceList == NULL) {
        return NULL;
    }
    const struct DeviceResourceNode *device = hostNode->child;
    while (device != NULL) {
        const struct DeviceResourceNode *deviceNode = device->child;
        while (deviceNode != NULL) {
            struct HdfDeviceInfo *deviceNodeInfo = HdfDeviceInfoNewInstance();
            if (deviceNodeInfo == NULL) {
                HdfSListFlush(deviceList, HdfDeviceInfoDelete);
                OsalMemFree(deviceList);
                return NULL;
            }
            deviceNodeInfo->hostId = hostId;
            if (!GetDeviceNodeInfo(deviceNode, deviceNodeInfo)) {
                HdfDeviceInfoFreeInstance(deviceNodeInfo);
                HDF_LOGE("%s get device failed", __func__);
                deviceNodeInfo = NULL;
                deviceNode = deviceNode->sibling;
                continue;
            }
            if (!HdfSListAddOrder(deviceList, &deviceNodeInfo->node, HdfDeviceListCompare)) {
                HDF_LOGE("%s add device %s failed", __func__, deviceNodeInfo->svcName);
                HdfDeviceInfoFreeInstance(deviceNodeInfo);
                deviceNodeInfo = NULL;
                deviceNode = deviceNode->sibling;
                continue;
            }
            deviceNodeInfo->deviceId = deviceIdx;
            deviceNode = deviceNode->sibling;
        }
        device = device->sibling;
        deviceIdx++;
    }
    if (HdfSListCount(deviceList) == 0) {
        OsalMemFree(deviceList);
        return NULL;
    }
    return deviceList;
}

