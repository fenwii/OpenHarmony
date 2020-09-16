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

#ifndef LITE_MSG_GET_DEVICEID_H
#define LITE_MSG_GET_DEVICEID_H

#include "cJSON.h"

#include "auth_conn.h"
#include "common_info_manager.h"

cJSON *MsgGetDeviceIdPack(const DeviceInfo *devInfo);
int MsgGetDeviceIdUnPack(const cJSON *msg, AuthConn *conn);
cJSON* MsgVerifyIpPack(const ConnInfo *connInfo, const DeviceInfo *devInfo, int authPort, int sessionPort);
int MsgVerifyIpUnPack(const cJSON *msg, ConnInfo *connInfo, AuthConn *conn);
cJSON* MsgVerifyDeviceIdPack(DeviceInfo *info);

#endif
