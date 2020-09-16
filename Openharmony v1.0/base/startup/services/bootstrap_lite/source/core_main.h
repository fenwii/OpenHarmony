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
#ifndef LITE_CORE_MAIN_H
#define LITE_CORE_MAIN_H
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define SYS_NAME(name, step) ".zinitcall.sys." #name #step ".init"
#define MODULE_NAME(name, step) ".zinitcall." #name #step ".init"

#define SYS_CALL(name, step)                                      \
    do {                                                          \
        InitCall *initcall = (InitCall *)(SYS_BEGIN(name, step)); \
        InitCall *initend = (InitCall *)(SYS_END(name, step));    \
        for (; initcall < initend; initcall++) {                  \
            (*initcall)();                                        \
        }                                                         \
    } while (0)

#define MODULE_CALL(name, step)                                      \
    do {                                                             \
        InitCall *initcall = (InitCall *)(MODULE_BEGIN(name, step)); \
        InitCall *initend = (InitCall *)(MODULE_END(name, step));    \
        for (; initcall < initend; initcall++) {                     \
            (*initcall)();                                           \
        }                                                            \
    } while (0)

#if (defined(__GNUC__) || defined(__clang__))

#define SYS_BEGIN(name, step)                                 \
    ({        extern InitCall __zinitcall_sys_##name##_start;       \
        InitCall *initCall = &__zinitcall_sys_##name##_start; \
        (initCall);                                           \
    })

#define SYS_END(name, step)                                 \
    ({        extern InitCall __zinitcall_sys_##name##_end;       \
        InitCall *initCall = &__zinitcall_sys_##name##_end; \
        (initCall);                                         \
    })

#define MODULE_BEGIN(name, step)                          \
    ({        extern InitCall __zinitcall_##name##_start;       \
        InitCall *initCall = &__zinitcall_##name##_start; \
        (initCall);                                       \
    })
#define MODULE_END(name, step)                          \
    ({        extern InitCall __zinitcall_##name##_end;       \
        InitCall *initCall = &__zinitcall_##name##_end; \
        (initCall);                                     \
    })

#define SYS_INIT(name)     \
    do {                   \
        SYS_CALL(name, 0); \
    } while (0)

#define MODULE_INIT(name)     \
    do {                      \
        MODULE_CALL(name, 0); \
    } while (0)

#elif (defined(__ICCARM__))

#define SYS_BEGIN(name, step) __section_begin(SYS_NAME(name, step))
#define SYS_END(name, step) __section_end(SYS_NAME(name, step))
#define MODULE_BEGIN(name, step) __section_begin(MODULE_NAME(name, step))
#define MODULE_END(name, step) __section_end(MODULE_NAME(name, step))

#pragma section = SYS_NAME(service, 0)
#pragma section = SYS_NAME(service, 1)
#pragma section = SYS_NAME(service, 2)
#pragma section = SYS_NAME(service, 3)
#pragma section = SYS_NAME(service, 4)
#pragma section = SYS_NAME(feature, 0)
#pragma section = SYS_NAME(feature, 1)
#pragma section = SYS_NAME(feature, 2)
#pragma section = SYS_NAME(feature, 3)
#pragma section = SYS_NAME(feature, 4)
#pragma section = MODULE_NAME(bsp, 0)
#pragma section = MODULE_NAME(bsp, 1)
#pragma section = MODULE_NAME(bsp, 2)
#pragma section = MODULE_NAME(bsp, 3)
#pragma section = MODULE_NAME(bsp, 4)
#pragma section = MODULE_NAME(device, 0)
#pragma section = MODULE_NAME(device, 1)
#pragma section = MODULE_NAME(device, 2)
#pragma section = MODULE_NAME(device, 3)
#pragma section = MODULE_NAME(device, 4)
#pragma section = MODULE_NAME(core, 0)
#pragma section = MODULE_NAME(core, 1)
#pragma section = MODULE_NAME(core, 2)
#pragma section = MODULE_NAME(core, 3)
#pragma section = MODULE_NAME(core, 4)
#pragma section = MODULE_NAME(run, 0)
#pragma section = MODULE_NAME(run, 1)
#pragma section = MODULE_NAME(run, 2)
#pragma section = MODULE_NAME(run, 3)
#pragma section = MODULE_NAME(run, 4)

#define SYS_INIT(name)     \
    do {                   \
        SYS_CALL(name, 0); \
        SYS_CALL(name, 1); \
        SYS_CALL(name, 2); \
        SYS_CALL(name, 3); \
        SYS_CALL(name, 4); \
    } while (0)

#define MODULE_INIT(name)     \
    do {                      \
        MODULE_CALL(name, 0); \
        MODULE_CALL(name, 1); \
        MODULE_CALL(name, 2); \
        MODULE_CALL(name, 3); \
        MODULE_CALL(name, 4); \
    } while (0)

#else
#error Not support current compiler!
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_CORE_MAIN_H
