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

#ifndef OHOS_LAYER_INIT_H
#define OHOS_LAYER_INIT_H
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
typedef void (*InitCall)(void);

#define USED_ATTR __attribute__((used))

#ifdef LAYER_INIT_SHARED_LIB
#define LAYER_INIT_LEVEL_0 0
#define LAYER_INIT_LEVEL_1 1
#define LAYER_INIT_LEVEL_2 2
#define LAYER_INIT_LEVEL_3 3
#define LAYER_INIT_LEVEL_4 4
#define CTOR_VALUE_device 100
#define CTOR_VALUE_core 110
#define CTOR_VALUE_sys_service 120
#define CTOR_VALUE_sys_feature 130
#define CTOR_VALUE_app_service 140
#define CTOR_VALUE_app_feature 150
#define CTOR_VALUE_run  700
#define LAYER_INITCALL(func, layer, clayer, priority)                                     \
    static __attribute__((constructor(CTOR_VALUE_##layer + LAYER_INIT_LEVEL_##priority))) \
        void BOOT_##layer##priority##func() {func();}
#else
#define LAYER_INITCALL(func, layer, clayer, priority)            \
    static const InitCall USED_ATTR __zinitcall_##layer##_##func \
        __attribute__((section(".zinitcall." clayer #priority ".init"))) = func
#endif
// Default priority is 2, priority range is [0, 4]
#define LAYER_INITCALL_DEF(func, layer, clayer) \
    LAYER_INITCALL(func, layer, clayer, 2)

#define CORE_INIT(func) LAYER_INITCALL_DEF(func, core, "core")
#define CORE_INIT_PRI(func, priority) LAYER_INITCALL(func, core, "core", priority)


#define SYS_SERVICE_INIT(func) LAYER_INITCALL_DEF(func, sys_service, "sys.service")
#define SYS_SERVICE_INIT_PRI(func, priority) LAYER_INITCALL(func, sys_service, "sys.service", priority)


#define SYS_FEATURE_INIT(func) LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")
#define SYS_FEATURE_INIT_PRI(func, priority) LAYER_INITCALL(func, sys_feature, "sys.feature", priority)


#define SYS_RUN(func) LAYER_INITCALL_DEF(func, run, "run")
#define SYS_RUN_PRI(func, priority) LAYER_INITCALL(func, run, "run", priority)

#define SYSEX_SERVICE_INIT(func) LAYER_INITCALL_DEF(func, app_service, "app.service")
#define SYSEX_SERVICE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_service, "app.service", priority)

#define SYSEX_FEATURE_INIT(func) LAYER_INITCALL_DEF(func, app_feature, "app.feature")
#define SYSEX_FEATURE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_feature, "app.feature", priority)

#define APP_SERVICE_INIT(func) LAYER_INITCALL_DEF(func, app_service, "app.service")
#define APP_SERVICE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_service, "app.service", priority)

#define APP_FEATURE_INIT(func) LAYER_INITCALL_DEF(func, app_feature, "app.feature")
#define APP_FEATURE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_feature, "app.feature", priority)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // OHOS_LAYER_INIT_H
