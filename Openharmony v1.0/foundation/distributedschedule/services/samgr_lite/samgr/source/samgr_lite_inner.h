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
#ifndef LITE_SAMGR_LITE_INNER_H
#define LITE_SAMGR_LITE_INNER_H

#include "samgr_lite.h"
#include "task_manager.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#ifndef MAX_SERVICE_NUM
#define MAX_SERVICE_NUM 0x7FF0
#endif

#define DEFAULT_SIZE 1
#define SINGLE_SIZE 1
#define MAX_POOL_NUM 8
#define PROPERTY_STEP 8
#define DEFAULT_TASK_CFG(pos) {LEVEL_HIGH,  (int16) ((pos) * PROPERTY_STEP + 1), 0x800, 25, SHARED_TASK}
#define WDG_SAMGR_INIT_TIME 1000
#define WDG_SVC_REG_TIME 5000
#define WDG_SVC_BOOT_TIME 5000
#define WDG_SVC_TEST_TIME 100000

#define BOOT_FMT(status) ((status) == BOOT_SYS_WAIT ? "Bootstrap core services(count:%d)." : \
((status) == BOOT_APP_WAIT ? "Bootstrap system and application services(count:%d)." : \
((status) == BOOT_DYNAMIC_WAIT ? "Bootstrap dynamic registered services(count:%d)." : \
"Bootstrap other services(count:%d).")))

typedef enum {
    BOOT_SYS = 0,
    BOOT_SYS_WAIT = 1,
    BOOT_APP = 2,
    BOOT_APP_WAIT = 3,
    BOOT_DYNAMIC = 4,
    BOOT_DYNAMIC_WAIT = 5,
} BootStatus;

typedef struct SamgrLiteImpl SamgrLiteImpl;
struct SamgrLiteImpl {
    SamgrLite vtbl;
    MutexId mutex;
    BootStatus status;
    Vector services;
    TaskPool *sharedPool[MAX_POOL_NUM];
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_SAMGR_LITE_INNER_H
