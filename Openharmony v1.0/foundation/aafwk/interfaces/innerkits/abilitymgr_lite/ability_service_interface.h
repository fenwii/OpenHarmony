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

#ifndef OHOS_AMS_INTERFACE_H
#define OHOS_AMS_INTERFACE_H

#include "feature.h"
#include "iproxy_server.h"
#include "want.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

const char AMS_SERVICE[] = "abilityms";
const char AMS_FEATURE[] = "AmsFeature";
const char AMS_INNER_FEATURE[] = "AmsInnerFeature";

enum AmsCommand {
    START_ABILITY = 0,
    TERMINATE_ABILITY,
    ATTACH_BUNDLE,
    CONNECT_ABILITY,
    CONNECT_ABILITY_DONE,
    DISCONNECT_ABILITY,
    DISCONNECT_ABILITY_DONE,
    ABILITY_TRANSACTION_DONE,
    TERMINATE_SERVICE,
    INNER_BEGIN,
    TERMINATE_APP = INNER_BEGIN,
    DUMP_ABILITY,
    COMMAND_END,
};

/**
 * Expose to start or terminate ability.
 */
struct AmsInterface {
    INHERIT_SERVER_IPROXY;
    int32 (*StartAbility)(const Want *want);
    int32 (*TerminateAbility)(uint64_t token);
    int32 (*ConnectAbility)(const Want *want, SvcIdentity *svc, uint64_t token);
    int32 (*DisconnectAbility)(SvcIdentity *svc, uint64_t token);
    int32 (*StopAbility)(const Want *want);
};

struct AmsInnerInterface {
    INHERIT_SERVER_IPROXY;
    int32 (*StartKeepAliveApps)();
    int32 (*TerminateApp)(const char *bundleName);
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif // OHOS_AMS_INTERFACE_H
