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

/**
 * @addtogroup Init OHOS Init
 * @{
 *
 * @brief Provides the entries for initializing and starting services and features.
 *
 * This module provides the entries for initializing services and features during service
 * development. \n
 * Services and features are initialized in the following sequence: core phase, core system
 * service, core system feature, system startup, system service, system feature, application-layer
 * service, and application-layer feature. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ohos_init.h
 *
 * @brief Provides the entries for initializing and starting services and features.
 *
 * This file provides the entries for initializing services and features during service
 * development. \n
 *
 * @since 1.0
 * @version 1.0
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

/**
 * @brief Identifies the entry for initializing and starting a core phase by the priority 2.
 *
 * This macro is used when Samgr is initialized and started. \n
 * This macro is used to identify the entry called at the priority 2 of the core phase of
 * the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a core phase.
 * The type is void (*)(void).
 */
#define CORE_INIT(func) LAYER_INITCALL_DEF(func, core, "core")
/**
 * @brief Identifies the entry for initializing and starting a core phase by the specified
 * priority.
 *
 * This macro is used when Samgr is initialized and started. \n
 * This macro is used to identify the entry called at the specified priority of the core phase of
 * the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a core phase.
 * The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the core phase.
 * The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define CORE_INIT_PRI(func, priority) LAYER_INITCALL(func, core, "core", priority)

/**
 * @brief Identifies the entry for initializing and starting a core system service by the
 * priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 in the core system
 * service phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a core system service.
 * The type is void (*)(void).
 */
#define SYS_SERVICE_INIT(func) LAYER_INITCALL_DEF(func, sys_service, "sys.service")
/**
 * @brief Identifies the entry for initializing and starting a core system service by the
 * specified priority.
 *
 * This macro is used to identify the entry called at the specified priority in the core system
 * service phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a core system service.
 * The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the core system service in the
 * startup phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define SYS_SERVICE_INIT_PRI(func, priority) LAYER_INITCALL(func, sys_service, "sys.service", priority)

/**
 * @brief Identifies the entry for initializing and starting a core system feature by the
 * priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 in the core system
 * feature phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a core system service.
 * The type is void (*)(void).
 */
#define SYS_FEATURE_INIT(func) LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")
/**
 * @brief Identifies the entry for initializing and starting a core system feature by the
 * specified priority.
 *
 * This macro is used to identify the entry called at the specified priority in the core system
 * feature phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a core system feature.
 * The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the core system feature phase.
 * The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define SYS_FEATURE_INIT_PRI(func, priority) LAYER_INITCALL(func, sys_feature, "sys.feature", priority)

/**
 * @brief Identifies the entry for initializing and starting a system running phase by the
 * priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 in the system startup
 * phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a system running phase.
 * The type is void (*)(void).
 */
#define SYS_RUN(func) LAYER_INITCALL_DEF(func, run, "run")
/**
 * @brief Identifies the entry for initializing and starting a system running phase by the
 * specified priority.
 *
 * This macro is used to identify the entry called at the specified priority in the system startup
 * phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a system running phase.
 * The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the system startup phase.
 * The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define SYS_RUN_PRI(func, priority) LAYER_INITCALL(func, run, "run", priority)

/**
 * @brief Identifies the entry for initializing and starting a system service by the priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 in the system service
 * phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a system service.
 * The type is void (*)(void).
 */
#define SYSEX_SERVICE_INIT(func) LAYER_INITCALL_DEF(func, app_service, "app.service")
/**
 * @brief Identifies the entry for initializing and starting a system service by the specified
 * priority.
 *
 * This macro is used to identify the entry called at the specified priority of the system service
 * phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a system service.
 * The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the system service phase.
 * The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define SYSEX_SERVICE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_service, "app.service", priority)

/**
 * @brief Identifies the entry for initializing and starting a system feature by the priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 of the system feature
 * phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a system feature.
 * The type is void (*)(void).
 */
#define SYSEX_FEATURE_INIT(func) LAYER_INITCALL_DEF(func, app_feature, "app.feature")
/**
 * @brief Identifies the entry for initializing and starting a system feature by the specified
 * priority.
 *
 * This macro is used to identify the entry called at the specified priority of the system feature
 * phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting a system feature.
 * The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the system feature phase.
 * The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define SYSEX_FEATURE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_feature, "app.feature", priority)

/**
 * @brief Identifies the entry for initializing and starting an application-layer service by the
 * priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 of the application-layer
 * service phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting an application-layer
 * service. The type is void (*)(void).
 */
#define APP_SERVICE_INIT(func) LAYER_INITCALL_DEF(func, app_service, "app.service")
/**
 * @brief Identifies the entry for initializing and starting an application-layer service by the
 * specified priority.
 *
 * This macro is used to identify the entry called at the specified priority of the
 * application-layer service phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting an application-layer
 * service. The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the application-layer service
 * phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define APP_SERVICE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_service, "app.service", priority)

/**
 * @brief Identifies the entry for initializing and starting an application-layer feature by the
 * priority 2.
 *
 * This macro is used to identify the entry called at the priority 2 of the application-layer
 * feature phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting an application-layer
 * feature. The type is void (*)(void).
 */
#define APP_FEATURE_INIT(func) LAYER_INITCALL_DEF(func, app_feature, "app.feature")
/**
 * @brief Identifies the entry for initializing and starting an application-layer feature by
 * the specified priority.
 *
 * This macro is used to identify the entry called at the specified priority of the
 * application-layer feature phase of the startup process. \n
 *
 * @param func Indicates the entry function for initializing and starting an application-layer
 * feature. The type is void (*)(void).
 * @param priority Indicates the calling priority when starting the application-layer feature.
 * The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4.
 */
#define APP_FEATURE_INIT_PRI(func, priority) LAYER_INITCALL(func, app_feature, "app.feature", priority)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // OHOS_LAYER_INIT_H
/** @} */
