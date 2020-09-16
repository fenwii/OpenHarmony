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

#ifndef OHOS_ABILITY_MESSAGE_ID_H
#define OHOS_ABILITY_MESSAGE_ID_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum AmsMsgType {
#ifndef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    AMS_BUTTON_EVENT = 10,
    AMS_STARTNUMBER = 4100,
    AMS_SERVICE_INITED = AMS_STARTNUMBER,
    AMS_START_ABILITY,
    AMS_ONSTART,
    AMS_ONACTIVE,
    AMS_ONBACKGROUND,
    AMS_TERMINATE_ABILITY,
    AMS_ONDESTROY,
    LAUNCHER_SCHEDULE_START, /* msgId used to communicated with Launcher */
    LAUNCHER_SCHEDULE_ACTIVE,
    LAUNCHER_SCHEDULE_INACTIVE,
    LAUNCHER_SCHEDULE_BACKGROUND,
    LAUNCHER_SCHEDULE_DESTROY,
    LAUNCHER_SCHEDULE_INSTALLED,
    AMS_SENDMESSAGE = 0x1011,
    AMS_REGISTER,
    AMS_UNREGISTER,

    AMS_START_CHECK_REQUEST,
    AMS_START_CHECK_RESPONSE,

    // The above value is for watch gt, don't change the order
#else
    AMS_SERVICE_INITED = 0,
    AMS_START_ABILITY,
    AMS_TERMINATE_ABILITY,

    AMS_ATTACH_BUNDLE,
    AMS_TRANSACTION_DONE,

    AMS_CONNECT_ABILITY,
    AMS_CONNECT_ABILITY_DONE,
    AMS_DISCONNECT_ABILITY,
    AMS_DISCONNECT_ABILITY_DONE,
    AMS_TERMINATE_SERVICE,
    AMS_TERMINATE_APP,
    AMS_RESTART_APP,
    AMS_DUMP_ABILITY,
#endif
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // OHOS_ABILITY_MESSAGE_ID_H
