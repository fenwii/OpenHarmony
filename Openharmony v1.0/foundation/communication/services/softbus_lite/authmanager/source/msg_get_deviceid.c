/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "msg_get_deviceid.h"

#include "message.h"

#define CMD_TAG "TECmd"
#define DATA_TAG "TEData"
#define DEVICEID_TAG "TEDeviceId"
#define CMD_GET_AUTH_INFO "getAuthInfo"
#define CMD_RET_AUTH_INFO "retAuthInfo"

#define DEVICE_CONN_CAP_WIFI 0x1f
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#define DEVICE_TYPE_DEFAULT "DEV_L0"
#else
#define DEVICE_TYPE_DEFAULT "DEV_L1"
#endif


static cJSON *MsgGetDeviceIdpack(const DeviceInfo *devInfo, const char *cmd)
{
    cJSON *msg = cJSON_CreateObject();
    if (msg == NULL) {
        return NULL;
    }

    if (cJSON_AddStringToObject(msg, CMD_TAG, cmd) == NULL) {
        cJSON_Delete(msg);
        return NULL;
    }

    if (cJSON_AddStringToObject(msg, DATA_TAG, devInfo->deviceId) == NULL) {
        cJSON_Delete(msg);
        return NULL;
    }

    return msg;
}

static int MsgGetDeviceIdunpack(const cJSON *msg, AuthConn *conn, const char *cmd)
{
    char *msgCmd = GetJsonString(msg, CMD_TAG);
    char *msgData = GetJsonString(msg, DATA_TAG);
    char *msgAuthId = GetJsonString(msg, DEVICEID_TAG);
    if (msgCmd == NULL || msgData == NULL || msgAuthId == NULL) {
        return -1;
    }

    if (strcmp(msgCmd, cmd) != 0) {
        return -1;
    }
    if (strcpy_s(conn->deviceId, sizeof(conn->deviceId), msgData) != EOK) {
        return -1;
    }
    if (strcpy_s(conn->authId, sizeof(conn->authId), msgAuthId) != EOK) {
        return -1;
    }

    return 0;
}

int MsgGetDeviceIdUnPack(const cJSON *msg, AuthConn *conn)
{
    if (msg == NULL || conn == NULL) {
        return -1;
    }

    int ret = MsgGetDeviceIdunpack(msg, conn, CMD_GET_AUTH_INFO);
    if (ret != 0) {
        return -1;
    }

    return 0;
}

cJSON *MsgGetDeviceIdPack(const DeviceInfo *devInfo)
{
    if (devInfo == NULL) {
        return NULL;
    }

    return MsgGetDeviceIdpack(devInfo, CMD_RET_AUTH_INFO);
}

cJSON* MsgVerifyIpPack(const ConnInfo *connInfo, const DeviceInfo *devInfo, int authPort, int sessionPort)
{
    if (connInfo == NULL || devInfo == NULL) {
        return NULL;
    }

    cJSON *msg = cJSON_CreateObject();
    if (msg == NULL) {
        return NULL;
    }

    if (cJSON_AddNumberToObject(msg, "CODE", CODE_VERIFY_IP) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddNumberToObject(msg, "BUS_MAX_VERSION", connInfo->maxVersion) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddNumberToObject(msg, "BUS_MIN_VERSION", connInfo->minVersion) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddNumberToObject(msg, "AUTH_PORT", authPort) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddNumberToObject(msg, "SESSION_PORT", sessionPort) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddNumberToObject(msg, "CONN_CAP", DEVICE_CONN_CAP_WIFI) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddStringToObject(msg, "DEVICE_NAME", devInfo->deviceName) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddStringToObject(msg, "DEVICE_TYPE", DEVICE_TYPE_DEFAULT) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddStringToObject(msg, "DEVICE_ID", devInfo->deviceId) == NULL) {
        goto ERR_EXIT;
    }
    if (cJSON_AddStringToObject(msg, "VERSION_TYPE", devInfo->version) == NULL) {
        goto ERR_EXIT;
    }

    return msg;
ERR_EXIT:
    if (msg != NULL) {
        cJSON_Delete(msg);
    }
    return NULL;
}

int MsgVerifyIpUnPack(const cJSON *msg, ConnInfo *connInfo, AuthConn *conn)
{
    if (msg == NULL || connInfo == NULL || conn == NULL) {
        return -1;
    }

    int maxVersion;
    if (GetJsonInt(msg, "BUS_MAX_VERSION", &maxVersion) != 0) {
        return -1;
    }

    int minVersion;
    if (GetJsonInt(msg, "BUS_MIN_VERSION", &minVersion) != 0) {
        return -1;
    }

    int connMaxVersion = connInfo->maxVersion;
    int connMinVersion = connInfo->minVersion;

    if (maxVersion > connMaxVersion) {
        maxVersion = connMaxVersion;
    }
    if (minVersion < connMinVersion) {
        minVersion = connMinVersion;
    }
    conn->busVersion = maxVersion;
    connInfo->maxVersion = maxVersion;
    connInfo->minVersion = minVersion;

    char *deviceName = GetJsonString(msg, "DEVICE_NAME");
    char *deviceType = GetJsonString(msg, "DEVICE_TYPE");
    if (deviceName == NULL || deviceType == NULL) {
        return -1;
    }

    if (strcpy_s(connInfo->deviceName, sizeof(connInfo->deviceName), deviceName) != EOK) {
        return -1;
    }
    if (strcpy_s(connInfo->deviceType, sizeof(connInfo->deviceType), deviceType) != EOK) {
        return -1;
    }

    if (GetJsonInt(msg, "AUTH_PORT", &(conn->authPort)) != 0) {
        return -1;
    }
    if (GetJsonInt(msg, "SESSION_PORT", &(conn->sessionPort)) != 0) {
        return -1;
    }

    return 0;
}

cJSON *MsgVerifyDeviceIdPack(DeviceInfo *info)
{
    if (info == NULL) {
        return NULL;
    }

    cJSON *msg = cJSON_CreateObject();
    if (msg == NULL) {
        return NULL;
    }

    if (cJSON_AddNumberToObject(msg, "CODE", CODE_VERIFY_DEVID) == NULL) {
        cJSON_Delete(msg);
        return NULL;
    }

    if (cJSON_AddStringToObject(msg, "DEVICE_ID", info->deviceId) == NULL) {
        cJSON_Delete(msg);
        return NULL;
    }

    return msg;
}

