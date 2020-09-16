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

#include "hiview_command.h"
#include "securec.h"
#include "hos_types.h"
#include "hiview_util.h"
#include "hiview_config.h"
#include "hiview_log.h"

#define CMD_MIN_LEN     2
#define CMD_MAX_LEN     32
#define CMD_HILOGCAT    "hilog"
#define CMD_HIEVENT     "hievent"
#define OPTION_TAG      '-'
#define OPTION_LIST     'l'
#define OPTION_SET      'c'
#define OPTION_SIMULATE 's'
#define OPTION_HELP     'h'
#define PARA_LEVEL      " level"
#define PARA_LEVEL_LEN  6
#define PARA_MODULE     " mod"
#define PARA_MODULE_LEN 4
#define OP_ASSIGN       '='
#define STR_MAX_LEN     128

static boolean CheckCmdStr(const char *cmd);
static void HilogHelpProc(void);
static void HilogListProc(const char *cmd);
static void HilogSetProc(const char *cmd);
static void ListLevelInfo(void);
static void ListModuleInfo(void);
static void SetOutputLevel(const char *cmd);
static void SetOutputModule(const char *cmd);
static void HieventHelpProc(void);
static void HieventSetProc(const char *cmd);
static void DumpHelpProc(void);
static void DumpSetProc(const char *cmd);
static void DumpSimulateProc(void);

/* Command does not contain the "hilogcat". */
void HilogCmdProc(const char *cmd)
{
    if (cmd == NULL) {
        return;
    }

    int32 len = strnlen(cmd, CMD_MAX_LEN + 1);
    if (len < CMD_MIN_LEN || len > CMD_MAX_LEN || (CheckCmdStr(cmd) == FALSE)) {
        HIVIEW_UartPrint("Invalid command.\n");
        return;
    }
    int i = 0;
    if (cmd[i++] == OPTION_TAG) {
        switch (cmd[i++]) {
            case OPTION_HELP:
                HilogHelpProc();
                return;
            case OPTION_LIST:
                HilogListProc(&cmd[i]);
                return;
            case OPTION_SET:
                HilogSetProc(&cmd[i]);
                return;
            default:
                HIVIEW_UartPrint("Invalid command.\n");
                return;
        }
    }
    HIVIEW_UartPrint("Invalid command.\n");
}

/* Command does not contain the "hievent". */
void HieventCmdProc(const char *cmd)
{
    if (cmd == NULL) {
        return;
    }

    int32 len = strnlen(cmd, CMD_MAX_LEN + 1);
    if ((len < CMD_MIN_LEN) || (len > CMD_MAX_LEN) || (CheckCmdStr(cmd) == FALSE)) {
        HIVIEW_UartPrint("Invalid command.\n");
        return;
    }
    int i = 0;
    if (cmd[i++] == OPTION_TAG) {
        switch (cmd[i++]) {
            case OPTION_HELP:
                HieventHelpProc();
                return;
            case OPTION_SET:
                HieventSetProc(&cmd[i]);
                return;
            default:
                HIVIEW_UartPrint("Invalid command.\n");
                return;
        }
    }
    HIVIEW_UartPrint("Invalid command.\n");
}

/* Command does not contain the "dump". */
void DumpCmdProc(const char *cmd)
{
    if (cmd == NULL) {
        return;
    }

    int32 len = strnlen(cmd, CMD_MAX_LEN + 1);
    if (len < CMD_MIN_LEN || len > CMD_MAX_LEN || (CheckCmdStr(cmd) == FALSE)) {
        HIVIEW_UartPrint("Invalid command.\n");
        return;
    }
    int i = 0;
    if (cmd[i++] == OPTION_TAG) {
        switch (cmd[i++]) {
            case OPTION_HELP:
                DumpHelpProc();
                return;
            case OPTION_SET:
                DumpSetProc(&cmd[i]);
                return;
            case OPTION_SIMULATE:
                DumpSimulateProc();
                return;
            default:
                HIVIEW_UartPrint("Invalid command.\n");
                return;
        }
    }
    HIVIEW_UartPrint("Invalid command.\n");
}

static void HilogHelpProc(void)
{
    HIVIEW_UartPrint("hilog [-h] [-l level/mod] [-c level=<1>] [-c mod=<3>]\n");
    HIVIEW_UartPrint(" -h            Help\n");
    HIVIEW_UartPrint(" -l            Query the level and module definition information\n");
    HIVIEW_UartPrint(" -l level      Query the level definition information\n");
    HIVIEW_UartPrint(" -l mod        Query the level definition information\n");
    HIVIEW_UartPrint(" -c            Enable all level logs of all modules\n");
    HIVIEW_UartPrint(" -c level=<id> Set the lowest log level\n");
    HIVIEW_UartPrint(" -c mod=<id>   Enable the logs of a specified module and disable other modules\n");
}

static void HilogListProc(const char *cmd)
{
    if (*cmd == '\0') {
        ListLevelInfo();
        ListModuleInfo();
    } else if (strncmp(cmd, PARA_LEVEL, PARA_LEVEL_LEN) == 0) {
        ListLevelInfo();
    } else if (strncmp(cmd, PARA_MODULE, PARA_MODULE_LEN) == 0) {
        ListModuleInfo();
    }
}

static void HilogSetProc(const char *cmd)
{
    if (*cmd == '\0') {
        SetLogLevel(HILOG_LV_DEBUG);
        SetLogOutputModule(HILOG_MODULE_MAX);
    } else if (strncmp(cmd, PARA_LEVEL, PARA_LEVEL_LEN) == 0) {
        SetOutputLevel(cmd + PARA_LEVEL_LEN);
    } else if (strncmp(cmd, PARA_MODULE, PARA_MODULE_LEN) == 0) {
        SetOutputModule(cmd + PARA_MODULE_LEN);
    }
}

static void HieventHelpProc(void)
{
    HIVIEW_UartPrint("hievent [-h] [-c]\n");
    HIVIEW_UartPrint(" -h            Help\n");
    HIVIEW_UartPrint(" -c            Enable or disable event function\n");
}

static void HieventSetProc(const char *cmd)
{
    if (*cmd == '\0') {
        if (g_hiviewConfig.eventSwitch == HIVIEW_FEATURE_ON) {
            SwitchEvent(HIVIEW_FEATURE_OFF);
            HIVIEW_UartPrint("Close event function success.\n");
        } else {
            SwitchEvent(HIVIEW_FEATURE_ON);
            HIVIEW_UartPrint("Open event function success.\n");
        }
    } else {
        HIVIEW_UartPrint("Invalid command.\n");
    }
}

static void DumpHelpProc(void)
{
    HIVIEW_UartPrint("dump [-h] [-c]\n");
    HIVIEW_UartPrint(" -h            Help\n");
    HIVIEW_UartPrint(" -c            Enable or disable dump function\n");
    HIVIEW_UartPrint(" -s            Simulates and triggers a dump (Note: The system will restart.)\n");
}

static void DumpSetProc(const char *cmd)
{
    if (*cmd == '\0') {
        if (g_hiviewConfig.dumpSwitch == HIVIEW_FEATURE_ON) {
            SwitchDump(HIVIEW_FEATURE_OFF);
            HIVIEW_UartPrint("Close dump function success.\n");
        } else {
            SwitchDump(HIVIEW_FEATURE_ON);
            HIVIEW_UartPrint("Open dump function success.\n");
        }
    } else {
        HIVIEW_UartPrint("Invalid command.\n");
    }
}

static void DumpSimulateProc(void)
{
    uint32 a = 0;
    SwitchDump(1 / a);
}

static void ListLevelInfo(void)
{
    HIVIEW_UartPrint("======Level Information======\n");
    HIVIEW_UartPrint(" 1 - DEBUG\n");
    HIVIEW_UartPrint(" 2 - INFO\n");
    HIVIEW_UartPrint(" 3 - WARN\n");
    HIVIEW_UartPrint(" 4 - ERROR\n");
    HIVIEW_UartPrint(" 5 - FATAL\n");
    HIVIEW_UartPrint(" 6 - CLOSE LOG\n");
}

static void ListModuleInfo(void)
{
    int32 i, ret;
    char modInfo[STR_MAX_LEN] = { '\0' };
    HIVIEW_UartPrint("======Module Information======\n");
    for (i = 0; i < HILOG_MODULE_MAX; i++) {
        ret = snprintf_s(modInfo, sizeof(modInfo), sizeof(modInfo) - 1, " %d - %s\n", i, HiLogGetModuleName(i));
        if (ret > 0) {
            modInfo[ret] = '\0';
            HIVIEW_UartPrint((const char *) modInfo);
        }
    }
}

static void SetOutputLevel(const char *cmd)
{
    if (*cmd++ == OP_ASSIGN) {
        char *endPtr = NULL;
        errno = 0;
        int32 level = strtol(cmd, &endPtr, 0);
        if ((endPtr == NULL) || (cmd == endPtr) || (*endPtr != 0) || (errno == ERANGE)) {
            HIVIEW_UartPrint("Set the log output level call strtol failure!\n");
            return;
        }
        if (SetLogLevel((uint8)level) == TRUE) {
            HIVIEW_UartPrint("Set the log output level success.\n");
            return;
        }
    }
    HIVIEW_UartPrint("Set the log output level failure.\n");
}

static void SetOutputModule(const char *cmd)
{
    if (*cmd++ == OP_ASSIGN) {
        char *endPtr = NULL;
        errno = 0;
        int32 mod = strtol(cmd, &endPtr, 0);
        if ((endPtr == NULL) || (cmd == endPtr) || (*endPtr != 0) || (errno == ERANGE)) {
            HIVIEW_UartPrint("Set the log output module call strtol failure!\n");
            return;
        }
        if (SetLogOutputModule((uint8)mod) == TRUE) {
            HIVIEW_UartPrint("Set the log output module success.\n");
            return;
        }
    }
    HIVIEW_UartPrint("Set the log output module failure.\n");
}

static boolean CheckCmdStr(const char *cmd)
{
    while (*cmd != '\0') {
        if (!((*cmd >= 'a' && *cmd <= 'z') || (*cmd >= 'A' && *cmd <= 'Z') || (*cmd >= '0' && *cmd <= '9') ||
            (*cmd == '=') || (*cmd == '-') || (*cmd == ' ') || (*cmd == '\n'))) {
            return FALSE;
        }
        cmd++;
    }
    return TRUE;
}
