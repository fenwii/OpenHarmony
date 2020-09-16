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
#ifndef OHOS_ABILITY_KIT_COMMAND_H
#define OHOS_ABILITY_KIT_COMMAND_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

enum AbilityKitCommand {
    SCHEDULER_APP_INIT = 0,
    SCHEDULER_ABILITY_LIFECYCLE,
    SCHEDULER_ABILITY_CONNECT,
    SCHEDULER_ABILITY_DISCONNECT,
    SCHEDULER_APP_EXIT,
    SCHEDULER_DUMP_ABILITY,
    SCHEDULER_ABILITY_CONNECT_FAIL,
};
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // OHOS_ABILITY_KIT_COMMAND_H
