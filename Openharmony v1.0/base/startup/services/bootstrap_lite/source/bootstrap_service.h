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
#ifndef LITE_BOOTSTRAP_SERVICE_H
#define LITE_BOOTSTRAP_SERVICE_H
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define APP_NAME(name, step) ".zinitcall.app." #name #step ".init"
#define MODULE_NAME(name, step) ".zinitcall." #name #step ".init"

#define APP_CALL(name, step)                                      \
    do {                                                          \
        InitCall *initcall = (InitCall *)(APP_BEGIN(name, step)); \
        InitCall *initend = (InitCall *)(APP_END(name, step));    \
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
#define APP_BEGIN(name, step)                                 \
    ({  extern InitCall __zinitcall_app_##name##_start;       \
        InitCall *initCall = &__zinitcall_app_##name##_start; \
        (initCall);                                           \
    })

#define APP_END(name, step)                                 \
    ({  extern InitCall __zinitcall_app_##name##_end;       \
        InitCall *initCall = &__zinitcall_app_##name##_end; \
        (initCall);                                         \
    })

#define MODULE_BEGIN(name, step)                          \
    ({  extern InitCall __zinitcall_##name##_start;       \
        InitCall *initCall = &__zinitcall_##name##_start; \
        (initCall);                                       \
    })
#define MODULE_END(name, step)                          \
    ({  extern InitCall __zinitcall_##name##_end;       \
        InitCall *initCall = &__zinitcall_##name##_end; \
        (initCall);                                     \
    })

#define INIT_APP_CALL(name) APP_CALL(name, 0);

#define INIT_TEST_CALL()    MODULE_CALL(test, 0);
#elif (defined(__ICCARM__))
#define APP_BEGIN(name, step) __section_begin(APP_NAME(name, step))
#define APP_END(name, step) __section_end(APP_NAME(name, step))
#define MODULE_BEGIN(name, step) __section_begin(MODULE_NAME(name, step))
#define MODULE_END(name, step) __section_end(MODULE_NAME(name, step))

#pragma section = APP_NAME(service, 0)
#pragma section = APP_NAME(service, 1)
#pragma section = APP_NAME(service, 2)
#pragma section = APP_NAME(service, 3)
#pragma section = APP_NAME(service, 4)
#pragma section = APP_NAME(feature, 0)
#pragma section = APP_NAME(feature, 1)
#pragma section = APP_NAME(feature, 2)
#pragma section = APP_NAME(feature, 3)
#pragma section = APP_NAME(feature, 4)
#pragma section = MODULE_NAME(test, 0)
#pragma section = MODULE_NAME(test, 1)
#pragma section = MODULE_NAME(test, 2)
#pragma section = MODULE_NAME(test, 3)
#pragma section = MODULE_NAME(test, 4)

#define INIT_APP_CALL(name) \
    do {                    \
        APP_CALL(name, 0);  \
        APP_CALL(name, 1);  \
        APP_CALL(name, 2);  \
        APP_CALL(name, 3);  \
        APP_CALL(name, 4);  \
    } while (0)

#define INIT_TEST_CALL()      \
    do {                      \
        MODULE_CALL(test, 0); \
        MODULE_CALL(test, 1); \
        MODULE_CALL(test, 2); \
        MODULE_CALL(test, 3); \
        MODULE_CALL(test, 4); \
    } while (0)
#else
#error Not support current compiler!
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_BOOTSTRAP_SERVICE_H
