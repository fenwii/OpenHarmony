/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "common_info_manager.h"

#include "coap_discover.h"
#include "discovery_error.h"
#include "discovery_service.h"
#include "hks_client.h"
#include "nstackx.h"
#include "os_adapter.h"
#include "securec.h"

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include "utils_file.h"
#else
#include <fcntl.h>
#include <unistd.h>
#endif
static DeviceInfo *g_deviceInfo = NULL;
#define MAX_VALUE_SIZE 64
#define DEVICEID_MAX_NUM 96
#define DEVICE_ID_FILE   "/storage/data/softbus/deviceid"
#define TWO_NUM 2
#define NUM_TEN 10
#define FOUR_BIT 4
#define NUM_SIXTEEN 16

int GetRandomStr(const unsigned char *data, int len, char *str, int maxCnt)
{
    char tmp[TWO_NUM];
    int cnt = 0;

    if (data == NULL || str == NULL) {
        return ERROR_FAIL;
    }

    for (int i = 0; i < len; i++) {
        tmp[0] = (data[i] & 0xF0) >> FOUR_BIT;
        tmp[1] = data[i] & 0x0F;

        for (int j = 0; j < TWO_NUM; j++) {
            if (tmp[j] < NUM_TEN) {
                tmp[j] += 0x30;
            } else if (tmp[j] < NUM_SIXTEEN) {
                tmp[j] = tmp[j] - NUM_TEN + 'A';
            }
            if (cnt < maxCnt) {
                str[cnt] = tmp[j];
                cnt++;
            } else {
                return ERROR_SUCCESS;
            }
        }
    }

    return ERROR_SUCCESS;
}

#if defined(__LITEOS_A__) || defined(__LINUX__)
int ReadFile(char *deviceId, int len)
{
    if (deviceId == NULL || len <= 0) {
        return ERROR_FAIL;
    }

    int fd = open(DEVICE_ID_FILE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        SOFTBUS_PRINT("[DISCOVERY] ReadFile get deviceid open file fail\n");
        return ERROR_FAIL;
    }

    int ret = lseek(fd, 0, SEEK_SET);
    if (ret < 0) {
        SOFTBUS_PRINT("[DISCOVERY] ReadFile get deviceid lseek file fail\n");
        close(fd);
        return ERROR_FAIL;
    }

    ret = read(fd, deviceId, len);
    if (ret < 0) {
        SOFTBUS_PRINT("[DISCOVERY] ReadFile read deviceid fail, ret=%d len=%d\n", ret, len);
        close(fd);
        return ERROR_FAIL;
    }

    close(fd);
    return ERROR_SUCCESS;
}
#endif

int ReadDeviceId(char *deviceId, unsigned int len)
{
    int ret;
    if (deviceId == NULL) {
        return ERROR_FAIL;
    }

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    unsigned int fileLen = 0;
    int fd = UtilsFileOpen(DEVICE_ID_FILE, O_RDWR_FS | O_CREAT_FS, 0);
    if (fd < 0) {
        SOFTBUS_PRINT("[DISCOVERY] Read UtilsFileOpen fail\n");
        return ERROR_FAIL;
    }

    ret = UtilsFileStat(DEVICE_ID_FILE, &fileLen);
    if (ret < 0) {
        UtilsFileClose(fd);
        SOFTBUS_PRINT("[DISCOVERY] Read UtilsFileStat fail\n");
        return ERROR_FAIL;
    }

    ret = UtilsFileSeek(fd, 0, SEEK_SET_FS);
    if (ret < 0) {
        SOFTBUS_PRINT("[DISCOVERY] Read UtilsFileSeek fail\n");
        UtilsFileClose(fd);
        return ERROR_FAIL;
    }

    if (fileLen > len) {
        SOFTBUS_PRINT("[DISCOVERY] Read file len not legal, clear buf\n");
        UtilsFileClose(fd);
        return 0;
    }

    ret = UtilsFileRead(fd, deviceId, len);
    if (ret < 0) {
        SOFTBUS_PRINT("[DISCOVERY] Read UtilsFileRead, ret=%d len=%d\n", ret, len);
        UtilsFileClose(fd);
        return ERROR_FAIL;
    }

    UtilsFileClose(fd);
    return ERROR_SUCCESS;
#else
    ret = ReadFile(deviceId, len);
    return ret;
#endif
}

int WriteDeviceId(const char *deviceId, int len)
{
    int ret;
    int fd;

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    fd = UtilsFileOpen(DEVICE_ID_FILE, O_RDWR_FS | O_CREAT_FS | O_TRUNC_FS, 0);
    if (fd < 0) {
        SOFTBUS_PRINT("[DISCOVERY] WriteDeviceId UtilsFileOpen fail\n");
        return ERROR_FAIL;
    }

    ret = UtilsFileWrite(fd, deviceId, len);
    if (ret != len) {
        SOFTBUS_PRINT("[DISCOVERY] UtilsFileOpen UtilsFileWrite fail\n");
        UtilsFileClose(fd);
        return ERROR_FAIL;
    }

    UtilsFileClose(fd);
#else
    fd = open(DEVICE_ID_FILE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        SOFTBUS_PRINT("[DISCOVERY] WriteDeviceId open file fail\n");
        return ERROR_FAIL;
    }

    ret = write(fd, deviceId, len);
    if (ret != len) {
        SOFTBUS_PRINT("[DISCOVERY] WriteDeviceId write fail\n");
        close(fd);
        return ERROR_FAIL;
    }

    close(fd);
#endif

    return ERROR_SUCCESS;
}

int GetDeviceIdFromFile(char *deviceId, unsigned int len)
{
    int ret;
    unsigned char data[MAX_VALUE_SIZE] = {0};
    struct hks_blob key = {HKS_BLOB_TYPE_KEY, data, MAX_VALUE_SIZE};

    if (deviceId == NULL) {
        return ERROR_FAIL;
    }

    ret = ReadDeviceId(deviceId, len);
    if ((ret == ERROR_SUCCESS) && (strlen(deviceId) == (unsigned int)len)) {
        return ERROR_SUCCESS;
    }

    ret = hks_generate_random(&key);
    if (ret != 0) {
        SOFTBUS_PRINT("[DISCOVERY] generate key fail\n");
        return ERROR_FAIL;
    }

    ret = GetRandomStr(data, MAX_VALUE_SIZE, deviceId, len);
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] get random fail\n");
        return ERROR_FAIL;
    }

    ret = WriteDeviceId(deviceId, len);
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] write device fail\n");
        return ERROR_FAIL;
    }

    return ERROR_SUCCESS;
}

int UpdateCommonDeviceInfo(void)
{
    NSTACKX_LocalDeviceInfo localDeviceInfo;
    memset_s(&localDeviceInfo, sizeof(NSTACKX_LocalDeviceInfo), 0, sizeof(NSTACKX_LocalDeviceInfo));

    DeviceInfo *info = GetCommonDeviceInfo();
    if (info == NULL) {
        return ERROR_FAIL;
    }

    unsigned int ret;
    ret = strcpy_s(localDeviceInfo.name, sizeof(localDeviceInfo.name), info->deviceName);
    if (ret != 0) {
        return ret;
    }

    ret = strcpy_s(localDeviceInfo.deviceId, sizeof(localDeviceInfo.deviceId), info->deviceId);
    if (ret != 0) {
        return ret;
    }

    localDeviceInfo.deviceType = info->deviceType;
    ret = memcpy_s(localDeviceInfo.networkIpAddr, sizeof(localDeviceInfo.networkIpAddr),
                   info->deviceIp, sizeof(info->deviceIp));
    if (ret != 0) {
        return ret;
    }

    ret = memcpy_s(localDeviceInfo.networkName, sizeof(localDeviceInfo.networkName),
                   info->networkName, sizeof(info->networkName));
    if (ret != 0) {
        return ret;
    }

    ret = memcpy_s(localDeviceInfo.version, sizeof(localDeviceInfo.version),
                   info->version, sizeof(info->version));
    if (ret != 0) {
        return ret;
    }

    ret = NSTACKX_RegisterDeviceAn(&localDeviceInfo, 0);
    if (ret != 0) {
        return ERROR_FAIL;
    }

    return ERROR_SUCCESS;
}

DeviceInfo *GetCommonDeviceInfo(void)
{
    return g_deviceInfo;
}

int InitLocalDeviceInfo(void)
{
    char deviceId[DEVICEID_MAX_NUM] = {0};

    if (g_deviceInfo != NULL) {
        memset_s(g_deviceInfo, sizeof(DeviceInfo), 0, sizeof(DeviceInfo));
    } else {
        g_deviceInfo = (DeviceInfo *)calloc(1, sizeof(DeviceInfo));
        if (g_deviceInfo == NULL) {
            return ERROR_FAIL;
        }
    }
#if defined(__LITEOS_A__) || defined(__LINUX__)
    CoapGetIp(g_deviceInfo->deviceIp, NSTACKX_MAX_IP_STRING_LEN, 1);
#endif
    g_deviceInfo->devicePort = -1;
    g_deviceInfo->isAccountTrusted = 1;

    unsigned int ret;
    ret = GetDeviceIdFromFile(deviceId, MAX_VALUE_SIZE);
    if (ret != ERROR_SUCCESS) {
        SOFTBUS_PRINT("[DISCOVERY] Get device fail\n");
        return ERROR_FAIL;
    }

#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
    g_deviceInfo->deviceType = L0;
    ret = (unsigned int)strcpy_s(g_deviceInfo->deviceName, sizeof(g_deviceInfo->deviceName), L0_DEVICE_NAME);
#else
    g_deviceInfo->deviceType = L1;
    ret = (unsigned int)strcpy_s(g_deviceInfo->deviceName, sizeof(g_deviceInfo->deviceName), L1_DEVICE_NAME);
#endif

    ret |= (unsigned int)strcpy_s(g_deviceInfo->deviceId, sizeof(g_deviceInfo->deviceId), deviceId);
    ret |= (unsigned int)strcpy_s(g_deviceInfo->version, sizeof(g_deviceInfo->version), "1.0.0");
    if (ret != 0) {
        return ERROR_FAIL;
    }

    SOFTBUS_PRINT("[DISCOVERY] InitLocalDeviceInfo ok\n");
    return ERROR_SUCCESS;
}

int InitCommonManager(void)
{
    if (InitLocalDeviceInfo() != 0) {
        SOFTBUS_PRINT("[DISCOVERY] InitCommonManager fail\n");
        return ERROR_FAIL;
    }
    return ERROR_SUCCESS;
}

void DeinitCommonManager(void)
{
    if (g_deviceInfo != NULL) {
        free(g_deviceInfo);
        g_deviceInfo = NULL;
    }
}

void ListInitHead(List *head)
{
    head->next = head;
    head->prev = head;
}

void ListInsertHead(List *head, List *node)
{
    node->next = head->next;
    node->next->prev = node;
    node->prev = head;
    head->next = node;
}

void ListInsertTail(List *head, List *node)
{
    node->prev = head->prev;
    node->prev->next = node;
    node->next = head;
    head->prev = node;
}

void ListRemoveNode(List *node)
{
    if (node == NULL) {
        return;
    }
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = NULL;
    node->prev = NULL;
}

int ListIsEmpty(List *head)
{
    return (head == head->next);
}

List *ListGetFront(List *head)
{
    return head->next;
}

List *ListPopFront(List *head)
{
    List *element = NULL;
    if (head == NULL || ListIsEmpty(head)) {
        return NULL;
    }

    element = head->next;
    ListRemoveNode(element);
    return element;
}

int ListLength(const List *head)
{
    int len = 0;
    List *pos = NULL;
    List *tmp = NULL;

    LIST_FOR_EACH_SAFE(pos, tmp, head) {
        len++;
    }

    return len;
}
