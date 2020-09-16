/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "show.h"
#include "shmsg.h"
#include "shcmd.h"
#include "console.h"
#include "asm/hal_platform_ints.h"
#ifdef LOSCFG_DRIVERS_HDF_PLATFORM_UART
#include "hisoc/uart.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC BOOL g_shellSourceFlag = FALSE;

STATIC UINT32 OsShellCmdInit(VOID)
{
    UINT32 ret = OsCmdInit();
    if (ret != LOS_OK) {
        return ret;
    }

    return OsShellSysCmdRegister();
}

STATIC UINT32 OsShellCreateTask(ShellCB *shellCB)
{
    UINT32 ret = ShellTaskInit(shellCB);
    if (ret != LOS_OK) {
        return ret;
    }

    return ShellEntryInit(shellCB);
}

STATIC UINT32 OsShellSourceInit(INT32 consoleId)
{
    UINT32 ret = LOS_NOK;
    CONSOLE_CB *consoleCB = OsGetConsoleByID(consoleId);
    if ((consoleCB == NULL) || (consoleCB->shellHandle != NULL)) {
        return LOS_NOK;
    }
    consoleCB->shellHandle = LOS_MemAlloc((VOID *)m_aucSysMem0, sizeof(ShellCB));
    if (consoleCB->shellHandle == NULL) {
        return LOS_NOK;
    }
    ShellCB *shellCB = (ShellCB *)consoleCB->shellHandle;
    if (memset_s(shellCB, sizeof(ShellCB), 0, sizeof(ShellCB)) != EOK) {
        goto ERR_OUT1;
    }

    shellCB->consoleID = (UINT32)consoleId;
    ret = (UINT32)pthread_mutex_init(&shellCB->keyMutex, NULL);
    if (ret != LOS_OK) {
        goto ERR_OUT1;
    }
    ret = (UINT32)pthread_mutex_init(&shellCB->historyMutex, NULL);
    if (ret != LOS_OK) {
        goto ERR_OUT2;
    }

    ret = OsShellKeyInit(shellCB);
    if (ret != LOS_OK) {
        goto ERR_OUT3;
    }
    if (strncpy_s(shellCB->shellWorkingDirectory, PATH_MAX, "/", 2) != EOK) { /* 2:space for "/" */
        ret = LOS_NOK;
        goto ERR_OUT4;
    }
    if (consoleId == CONSOLE_TELNET) {
        ret = OsShellCreateTask(shellCB);
        if (ret != LOS_OK) {
            goto ERR_OUT4;
        }
    }

    return LOS_OK;
ERR_OUT4:
    (VOID)LOS_MemFree((VOID *)m_aucSysMem0, shellCB->cmdKeyLink);
    (VOID)LOS_MemFree((VOID *)m_aucSysMem0, shellCB->cmdHistoryKeyLink);
ERR_OUT3:
    (VOID)pthread_mutex_destroy(&shellCB->historyMutex);
ERR_OUT2:
    (VOID)pthread_mutex_destroy(&shellCB->keyMutex);
ERR_OUT1:
    (VOID)LOS_MemFree((VOID *)m_aucSysMem0, shellCB);
    consoleCB->shellHandle = NULL;
    return ret;
}


UINT32 OsShellInit(INT32 consoleId)
{
    if (g_shellSourceFlag == FALSE) {
        UINT32 ret = OsShellCmdInit();
        if (ret == LOS_OK) {
            g_shellSourceFlag = TRUE;
        } else {
            return ret;
        }
    }
    return OsShellSourceInit(consoleId);
}

INT32 OsShellDeinit(INT32 consoleId)
{
    CONSOLE_CB *consoleCB = NULL;
    ShellCB *shellCB = NULL;

    consoleCB = OsGetConsoleByID(consoleId);
    if (consoleCB == NULL) {
        PRINT_ERR("shell deinit error.\n");
        return -1;
    }

    shellCB = (ShellCB *)consoleCB->shellHandle;
    consoleCB->shellHandle = NULL;
    if (shellCB == NULL) {
        PRINT_ERR("shell deinit error.\n");
        return -1;
    }

    (VOID)LOS_TaskDelete(shellCB->shellEntryHandle);
    (VOID)LOS_EventWrite(&shellCB->shellEvent, CONSOLE_SHELL_KEY_EVENT);

    return 0;
}

CHAR *OsShellGetWorkingDirtectory(VOID)
{
    CONSOLE_CB *consoleCB = OsGetConsoleByTaskID(OsCurrTaskGet()->taskID);
    ShellCB *shellCB = NULL;

    if (consoleCB == NULL) {
        return NULL;
    }
    shellCB = (ShellCB *)consoleCB->shellHandle;
    if (shellCB == NULL) {
        return NULL;
    }
    return shellCB->shellWorkingDirectory;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
