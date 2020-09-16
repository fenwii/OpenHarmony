/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "log.h"
#include "securec.h"


#define HILOG_DRIVER "/dev/hilog"
#define HILOG_LOGBUFFER 1024
#undef LOG_DOMAIN
#undef LOG_TAG

#define LOG_DOMAIN 0xD002D00
#define LOG_TAG "hilogcat"

#define CMD_MIN_LEN 2
#define CMD_MAX_LEN 32
#define CMD_HILOGCAT "hilog"
#define CMD_HIEVENT "hievent"
#define OPTION_TAG '-'
#define OPTION_LIST 'l'
#define OPTION_SET 'C'
#define OPTION_SIMULATE 's'
#define OPTION_HELP 'h'
#define OPTION_2_FILE 'f'
#define OPTION_START 't'
#define OPTION_UART 'R'


#define PARA_LEVEL "level"
#define PARA_LEVEL_LEN 5
#define PARA_MODULE "mod"
#define PARA_MODULE_LEN 3
#define OP_ASSIGN '='
#define STR_MAX_LEN 128

typedef struct {
    const unsigned char outputOption : 4; /* Control log output mode. Cannot be modified during running. */
    unsigned char hiviewInited : 1;       /* Indicates whether the hiview service is inited. */
    unsigned char level : 3;              /* Control log output level. HILOG_LV_XXX */
    unsigned char logSwitch : 1;          /* Indicates whether to enable the log component. */
    unsigned char eventSwitch : 1;        /* Indicates whether to enable the event component. */
    unsigned char dumpSwitch : 1;         /* Indicates whether to enable the dump component. */
    unsigned char logOutputModule;        /* Control log output module. */
    unsigned short writeFailureCount;
} HiviewConfig;

typedef enum {
    OUTPUT_OPTION_DEBUG = 0, /* Output to the UART without buffer. Commercial versions are forbidden. */
    OUTPUT_OPTION_FLOW,      /* Output to UART via SAMR */
    OUTPUT_OPTION_TEXT_FILE,
    OUTPUT_OPTION_BIN_FILE,
    OUTPUT_OPTION_MAX
} HiviewOutputOption;

#define HIVIEW_FEATURE_ON 1
#define HIVIEW_FEATURE_OFF 0
#define HILOG_MODULE_ALL 0xff

static char g_logLevelInfo[HILOG_LEVEL_MAX] = {
    'N', // "NONE"
    'N', // "NONE"
    'N', // "NONE"
    'D', // "DEBUG"
    'I', // "INFO"
    'W', // "WARN"
    'E', // "ERROR"
    'F'  // "FATAL"
};

#define HILOG_MODULE_MAX_NUM 50
#define DOMIAN_ID_LENTH 6
static char g_logModuleInfo[HILOG_MODULE_MAX_NUM][DOMIAN_ID_LENTH] = {
    "00000",
    "01100", // "NONE"
    "01200", // "NONE"
    "01300", // "NONE"
    "01400", // "NONE"
    "01500", // "NONE"
    "01600", // "NONE"
    "01700", // "NONE"
    "01800", // "NONE"
    "01900", // "NONE"
    "02500", // "NONE"
    "02600", // "NONE"
    "02D00", // "NONE"
};

HiviewConfig g_hiviewConfig = {
    .outputOption = OUTPUT_OPTION_FLOW,
    .level = LOG_DEBUG,
    .logSwitch = HIVIEW_FEATURE_ON,
    .dumpSwitch = HIVIEW_FEATURE_OFF,
    .eventSwitch = HIVIEW_FEATURE_OFF,
};

static void HilogHelpProc(void)
{
    printf("hilog [-h] [-l level/mod] [-C level <1>] [-C mod <3>]\n");
    printf(" -h            Help\n");
    printf(" -l            Query the level and module definition information\n");
    printf(" -l level      Query the level definition information\n");
    printf(" -l mod        Query the level definition information\n");
    printf(" -C            Enable all level logs of all modules\n");
    printf(" -C level <id> Set the lowest log level\n");
    printf(" -C mod <id>   Enable the logs of a specified module and disable other modules\n");
    printf(" -f <filename> Enable the logs to a specified file\n");
}

static void ListLevelInfo(void)
{
    printf("======Level Information======\n");
    printf(" 3 - DEBUG\n");
    printf(" 4 - INFO\n");
    printf(" 5 - WARN\n");
    printf(" 6 - ERROR\n");
    printf(" 7 - FATAL\n");
}

static void ListModuleInfo(void)
{
    int i, ret;
    char modInfo[STR_MAX_LEN] = { '\0' };
    printf("======Module Information======\n");
    for (i = 0; i < HILOG_MODULE_MAX_NUM; i++) {
        if (g_logModuleInfo[i][0] == 0) {
            break;
        }
        ret = snprintf_s(modInfo, sizeof(modInfo), sizeof(modInfo) - 1, " %d - %s\n", i, g_logModuleInfo[i]);
        if (ret > 0) {
            modInfo[ret] = '\0';
            printf((const char *)modInfo);
        }
    }
}

static void HilogListProc(const char *cmd)
{
    if (cmd == NULL) {
        ListLevelInfo();
        ListModuleInfo();
    } else if (strncmp(cmd, PARA_LEVEL, PARA_LEVEL_LEN) == 0) {
        ListLevelInfo();
    } else if (strncmp(cmd, PARA_MODULE, PARA_MODULE_LEN) == 0) {
        ListModuleInfo();
    }
}

static bool SetLogLevel(unsigned char level)
{
    if (level >= LOG_DEBUG && level < HILOG_LEVEL_MAX) {
        g_hiviewConfig.level = level;
        return true;
    }
    return false;
}

static void SetLogOutputModule(unsigned char mod)
{
    g_hiviewConfig.logOutputModule = mod;
}

static void SetOutputModule(const char *cmd)
{
    char *endPtr = NULL;
    int mod = strtol(cmd, &endPtr, 0);
    SetLogOutputModule((unsigned char)mod);
}

static void SetOutputLevel(const char *cmd)
{
    char *endPtr = NULL;
    int level;
    if (cmd != NULL) {
        level = strtol(cmd, &endPtr, 0);
    } else {
        level = LOG_DEBUG;
    }
    if (SetLogLevel((unsigned char)level) == true) {
        printf("Set the log output level success.\n");
        return;
    }
    printf("Set the log output level failure level=%d.\n", level);
}


static void HilogSetProc(const char *option, const char *attr)
{
    if (option == NULL) {
        SetLogLevel(LOG_DEBUG);
        SetLogOutputModule(HILOG_MODULE_MAX_NUM);
    } else if (strncmp(option, PARA_LEVEL, PARA_LEVEL_LEN) == 0) {
        SetOutputLevel(attr);
    } else if (strncmp(option, PARA_MODULE, PARA_MODULE_LEN) == 0) {
        SetOutputModule(attr);
    }
}

static int HilogCmdProc(int argc, const char **argv)
{
#define ARG2 1
#define ARG3 2
#define ARG4 3

    int i = 0;

    if (argv[ARG2][i++] == OPTION_TAG) {
        switch (argv[ARG2][i++]) {
            case OPTION_HELP:
                HilogHelpProc();
                return 0;
            case OPTION_LIST:
                HilogListProc(&argv[ARG3][0]);
                return 0;
            case OPTION_SET:
                HilogSetProc(&argv[ARG3][0], &argv[ARG4][0]);
                return 1;
            case OPTION_2_FILE:
                return 0;
            default:
                printf("Invalid command.\n");
                return 0;
        }
    }
    printf("Invalid command.\n");
    return 0;
}

static bool FilterLevelLog(unsigned char setLevel, unsigned char logLevel)
{
    int logMinLevel;

    for (logMinLevel = LOG_DEBUG; logMinLevel < HILOG_LEVEL_MAX; logMinLevel++) {
        if (logLevel == g_logLevelInfo[logMinLevel]) {
            break;
        }
    }
    // Loglevel >= set level, may print log
    if (logMinLevel >= setLevel) {
        return true;
    }
    return false;
}

static bool FilterModuleLog(unsigned char setModule, const char *logModule)
{
    if (setModule == HILOG_MODULE_MAX_NUM) {
        return true;
    }
    int ret = strncmp(logModule, g_logModuleInfo[setModule], DOMAIN_LENGTH);
    // If module = setmodule, may print log
    if (ret == 0) {
        return true;
    }
    return false;
}

int main(int argc, const char **argv)
{
    int ret;
    bool printFlag = true;
    if (argc > 1) {
        ret = HilogCmdProc(argc, argv);
        if (ret == 0) {
            return 0;
        }
    }
    int fd = open(HILOG_DRIVER, O_RDONLY);
    if (fd < 0) {
        HILOG_ERROR(LOG_CORE, "open hilog driver failed\n");
        return 0;
    }
    while (1) {
        char buf[HILOG_LOGBUFFER] = {0};
        ret = read(fd, buf, HILOG_LOGBUFFER);
        if (ret < sizeof(struct HiLogEntry)) {
            continue;
        }
        struct HiLogEntry *head = (struct HiLogEntry *)buf;

        time_t rawtime;
        struct tm *info = NULL;
        unsigned int sec = head->sec;
        rawtime = (time_t)sec;
        /* Get GMT time */
        info = gmtime(&rawtime);

        printFlag = FilterLevelLog(g_hiviewConfig.level, *(head->msg));
        if (!printFlag) {
            continue;
        }
#define MODULE_OFFSET 2
        printFlag = FilterModuleLog(g_hiviewConfig.logOutputModule, (head->msg) + MODULE_OFFSET);
        if (!printFlag) {
            continue;
        }
        if (info == NULL) {
            continue;
        }
        buf[HILOG_LOGBUFFER - 1] = '\0';
        printf("%02d-%02d %02d:%02d:%02d.%03d %d %d %s\n", info->tm_mon + 1, info->tm_mday, info->tm_hour, info->tm_min,
            info->tm_sec, head->nsec / NANOSEC_PER_MIRCOSEC, head->pid, head->taskId, head->msg);
    }
    return 0;
}
