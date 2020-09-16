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

#ifndef OHOS_DISTRIBUTEDSCHEDULE_INTERFACE_H
#define OHOS_DISTRIBUTEDSCHEDULE_INTERFACE_H

#include "feature.h"
#include "iproxy_server.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define DISTRIBUTED_SCHEDULE_SERVICE "dtbschedsrv"
#define DMSLITE_FEATURE "dmslite"

typedef enum {
    DMS_EC_SUCCESS = 0,
    DMS_EC_START_ABILITY_SYNC_SUCCESS = 1,
    DMS_EC_START_ABILITY_ASYNC_SUCCESS = 2,
    DMS_EC_PARSE_TLV_FAILURE = 3,
    DMS_EC_UNKNOWN_COMMAND_ID = 4,
    DMS_EC_GET_BMS_FAILURE = 5,
    DMS_EC_GET_BUNDLEINFO_FAILURE = 6,
    DMS_EC_CHECK_PERMISSION_FAILURE = 7,
    DMS_EC_GET_AMS_FAILURE = 8,
    DMS_EC_REGISTE_IPC_CALLBACK_FAILURE = 9,
    DMS_EC_FILL_WANT_FAILURE = 10,
    DMS_EC_START_ABILITY_SYNC_FAILURE = 11,
    DMS_EC_START_ABILITY_ASYNC_FAILURE = 12,
    DMS_EC_FAILURE = 13
} DmsLiteCommonErrorCode;

typedef struct {
    INHERIT_SERVER_IPROXY;
} DmsLiteInterface;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // OHOS_DISTRIBUTEDSCHEDULE_INTERFACE_H
