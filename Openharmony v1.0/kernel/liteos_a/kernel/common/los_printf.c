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

#include "los_base.h"
#ifdef LOSCFG_LIB_LIBC
#include "stdlib.h"
#include "unistd.h"
#endif
#include "los_hwi.h"
#include "los_memory_pri.h"
#include "uart.h"
#ifdef LOSCFG_FS_VFS
#include "console.h"
#endif
#ifdef LOSCFG_SHELL_DMESG
#include "dmesg_pri.h"
#endif
#ifdef LOSCFG_SHELL_EXCINFO
#include "los_excinfo_pri.h"
#endif
#include "los_exc_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define SIZEBUF  256

const CHAR *g_logString[] = {
    "EMG",
    "COMMON",
    "ERR",
    "WARN",
    "INFO",
    "DEBUG",
    "TRACE"
};

const CHAR *OsLogLvGet(INT32 level)
{
    return g_logString[level];
}

STATIC VOID ErrorMsg(VOID)
{
    const CHAR *p = "Output illegal string! vsnprintf_s failed!\n";
    UartPuts(p, (UINT32)strlen(p), UART_WITH_LOCK);
}

STATIC VOID UartOutput(const CHAR *str, UINT32 len, BOOL isLock)
{
#ifdef LOSCFG_SHELL_DMESG
    if (!OsCheckUartLock()) {
        UartPuts(str, len, isLock);
    }
    if (isLock != UART_WITHOUT_LOCK) {
        (VOID)OsLogMemcpyRecord(str, len);
    }
#else
    UartPuts(str, len, isLock);
#endif
}

VOID OutputControl(const CHAR *str, UINT32 len, OutputType type)
{
    switch (type) {
        case CONSOLE_OUTPUT:
#ifdef LOSCFG_PLATFORM_CONSOLE
            if (ConsoleEnable() == TRUE) {
                (VOID)write(STDOUT_FILENO, str, (size_t)len);
                break;
            }
#endif
            /* fall-through */
        case UART_OUTPUT:
            UartOutput(str, len, UART_WITH_LOCK);
            break;
        case EXC_OUTPUT:
            UartOutput(str, len, UART_WITHOUT_LOCK);
            break;
        default:
            break;
    }
    return;
}

STATIC VOID OsVprintfFree(CHAR *buf, UINT32 bufLen)
{
    if (bufLen != SIZEBUF) {
        (VOID)LOS_MemFree(m_aucSysMem0, buf);
    }
}

VOID OsVprintf(const CHAR *fmt, va_list ap, OutputType type)
{
    INT32 len;
    const CHAR *errMsgMalloc = "OsVprintf, malloc failed!\n";
    const CHAR *errMsgLen = "OsVprintf, length overflow!\n";
    CHAR aBuf[SIZEBUF] = {0};
    CHAR *bBuf = NULL;
    UINT32 bufLen = SIZEBUF;
    UINT32 systemStatus;

    bBuf = aBuf;
    len = vsnprintf_s(bBuf, bufLen, bufLen - 1, fmt, ap);
    if ((len == -1) && (*bBuf == '\0')) {
        /* parameter is illegal or some features in fmt dont support */
        ErrorMsg();
        return;
    }

    while (len == -1) {
        /* bBuf is not enough */
        OsVprintfFree(bBuf, bufLen);

        bufLen = bufLen << 1;
        if ((INT32)bufLen <= 0) {
            UartPuts(errMsgLen, (UINT32)strlen(errMsgLen), UART_WITH_LOCK);
            return;
        }
        bBuf = (CHAR *)LOS_MemAlloc(m_aucSysMem0, bufLen);
        if (bBuf == NULL) {
            UartPuts(errMsgMalloc, (UINT32)strlen(errMsgMalloc), UART_WITH_LOCK);
            return;
        }
        len = vsnprintf_s(bBuf, bufLen, bufLen - 1, fmt, ap);
        if (*bBuf == '\0') {
            /* parameter is illegal or some features in fmt dont support */
            (VOID)LOS_MemFree(m_aucSysMem0, bBuf);
            ErrorMsg();
            return;
        }
    }
    *(bBuf + len) = '\0';

    systemStatus = OsGetSystemStatus();
    if ((systemStatus == OS_SYSTEM_NORMAL) || (systemStatus == OS_SYSTEM_EXC_OTHER_CPU)) {
        OutputControl(bBuf, len, type);
    } else if (systemStatus == OS_SYSTEM_EXC_CURR_CPU) {
        OutputControl(bBuf, len, EXC_OUTPUT);
    }
    OsVprintfFree(bBuf, bufLen);
}

VOID UartVprintf(const CHAR *fmt, va_list ap)
{
    OsVprintf(fmt, ap, UART_OUTPUT);
}

__attribute__((noinline)) VOID UartPrintf(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    OsVprintf(fmt, ap, UART_OUTPUT);
    va_end(ap);
}

__attribute__ ((noinline)) VOID dprintf(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    OsVprintf(fmt, ap, CONSOLE_OUTPUT);
    va_end(ap);
}

VOID LkDprintf(const CHAR *fmt, va_list ap)
{
    OsVprintf(fmt, ap, CONSOLE_OUTPUT);
}

#ifdef LOSCFG_SHELL_DMESG
VOID DmesgPrintf(const CHAR *fmt, va_list ap)
{
    OsVprintf(fmt, ap, CONSOLE_OUTPUT);
}
#endif

#ifdef LOSCFG_PLATFORM_UART_WITHOUT_VFS
__attribute__ ((noinline)) INT32 printf(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    OsVprintf(fmt, ap, UART_OUTPUT);
    va_end(ap);
    return 0;
}
#endif

__attribute__((noinline)) VOID syslog(INT32 level, const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    OsVprintf(fmt, ap, CONSOLE_OUTPUT);
    va_end(ap);
    (VOID)level;
}

__attribute__((noinline)) VOID ExcPrintf(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    /* uart output without print-spinlock */
    OsVprintf(fmt, ap, EXC_OUTPUT);
    va_end(ap);
}

VOID PrintExcInfo(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    /* uart output without print-spinlock */
    OsVprintf(fmt, ap, EXC_OUTPUT);
#ifdef LOSCFG_SHELL_EXCINFO
    WriteExcBufVa(fmt, ap);
#endif
    va_end(ap);
}

#ifndef LOSCFG_SHELL_LK
VOID LOS_LkPrint(INT32 level, const CHAR *func, INT32 line, const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    if (level > PRINT_LEVEL) {
        return;
    }

    if ((level != LOS_COMMON_LEVEL) && ((level > LOS_EMG_LEVEL) && (level <= LOS_TRACE_LEVEL))) {
        dprintf("[%s]", g_logString[level]);
    }
    OsVprintf(fmt, ap, CONSOLE_OUTPUT);
    va_end(ap);
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
