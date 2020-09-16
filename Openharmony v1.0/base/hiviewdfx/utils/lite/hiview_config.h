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

#ifndef HOS_LITE_HIVIEW_CONFIG_H
#define HOS_LITE_HIVIEW_CONFIG_H

#include "hos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/* Set the following parameters for different products based on their own resources. */
#ifdef HI3861_PRODUCT_TYPE
#define HIVIEW_FILE_DIR                    ""
#else
#define HIVIEW_FILE_DIR                    "user/log/"
#endif
/* file path config */
#define HIVIEW_FILE_PATH_LOG               HIVIEW_FILE_DIR"debug.log"
#define HIVIEW_FILE_PATH_FAULT_EVENT       HIVIEW_FILE_DIR"fault.event"
#define HIVIEW_FILE_PATH_UE_EVENT          HIVIEW_FILE_DIR"ue.event"
#define HIVIEW_FILE_PATH_STAT_EVENT        HIVIEW_FILE_DIR"stat.event"
#define HIVIEW_FILE_PATH_DUMP              HIVIEW_FILE_DIR"dump.dat"

/* file size config */
#define HIVIEW_LOG_FILE_SIZE               (8 * 1024)
#define FAULT_EVENT_FILE_SIZE              (1 * 1024)
#define UE_EVENT_FILE_SIZE                 (1 * 1024)
#define STAT_EVENT_FILE_SIZE               (1 * 1024)

/* cache size config */
#define LOG_STATIC_CACHE_SIZE              1024            /* Must be greater than HIVIEW_FILE_BUF_SIZE. */
#define EVENT_CACHE_SIZE                   256             /* Must be greater than HIVIEW_FILE_BUF_SIZE. */
#define JS_LOG_CACHE_SIZE                  512
#define HIVIEW_FILE_BUF_SIZE               128

/* RAM dump config */
#define HIVIEW_DUMP_PRE_SIZE               (384 * 1024)
#define HIVIEW_DUMP_HEADER_OFFSET          0x400
#define HIVIEW_DUMP_RAM_ADDR               0x10000400      /* 10000000 ~ 100003FF reserved for NVIC, no need save */
#define HIVIEW_DUMP_RAM_SIZE               (HIVIEW_DUMP_PRE_SIZE - HIVIEW_DUMP_HEADER_OFFSET)

/* feature switch */
#define HIVIEW_FEATURE_ON                  1
#define HIVIEW_FEATURE_OFF                 0

#pragma pack(1)
typedef struct {
    const uint8 outputOption : 4; /* Control log output mode. Cannot be modified during running. */
    uint8 hiviewInited : 1;       /* Indicates whether the hiview service is inited. */
    uint8 level : 3;              /* Control log output level. HILOG_LV_XXX */
    uint8 logSwitch : 1;          /* Indicates whether to enable the log component. */
    uint8 eventSwitch : 1;        /* Indicates whether to enable the event component. */
    uint8 dumpSwitch : 1;         /* Indicates whether to enable the dump component. */
    uint64 logOutputModule;       /* Control log output module. */
    uint16 writeFailureCount;
} HiviewConfig;
#pragma pack()

typedef enum {
    OUTPUT_OPTION_DEBUG = 0,    /* Output to the UART without buffer. Commercial versions are forbidden. */
    OUTPUT_OPTION_FLOW,         /* Output to UART via SAMR */
    OUTPUT_OPTION_TEXT_FILE,
    OUTPUT_OPTION_BIN_FILE,
    OUTPUT_OPTION_MAX
} HiviewOutputOption;

extern HiviewConfig g_hiviewConfig;

/**
 * Dynamically adjusting the Log Output Level.
 * @param level log level. Logs of this level or higher will be generated.
 * @return TRUE/FALSE
 **/
boolean SetLogLevel(uint8 level);

/**
 * Enabling or disabling the log function.
 * @param flag HIVIEW_FEATURE_ON/HIVIEW_FEATURE_OFF
 **/
void SwitchLog(uint8 flag);

/**
 * Enabling or disabling the event function.
 * @param flag HIVIEW_FEATURE_ON/HIVIEW_FEATURE_OFF
 **/
void SwitchEvent(uint8 flag);

/**
 * Enabling or disabling the dump function.
 * @param flag HIVIEW_FEATURE_ON/HIVIEW_FEATURE_OFF
 **/
void SwitchDump(uint8 flag);

/**
 * Enable the log output of a specified module.
 * @param mod module id.
 * @return TRUE/FALSE
 **/
boolean OpenLogOutputModule(uint8 mod);

/**
 * Disable the log output of a specified module.
 * @param mod module id.
 * @return TRUE/FALSE
 **/
boolean CloseLogOutputModule(uint8 mod);

/**
 * Enable the log output of a specified module and disable the log output of other modules.
 * @param mod module id. If the value of the module id is HILOG_MODULE_MAX, the log output of all modules is enabled.
 * @return TRUE/FALSE
 **/
boolean SetLogOutputModule(uint8 mod);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HOS_LITE_HIVIEW_CONFIG_H */
