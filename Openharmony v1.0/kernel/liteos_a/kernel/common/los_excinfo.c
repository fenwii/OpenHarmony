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
#include "los_hwi.h"
#ifdef LOSCFG_FS_VFS
#include "fs/fs.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef LOSCFG_SHELL_EXCINFO
STATIC log_read_write_fn g_excInfoRW = NULL; /* the hook of read-writing exception information */
STATIC CHAR *g_excInfoBuf = NULL;            /* pointer to the buffer for storing the exception information */
STATIC UINT32 g_excInfoIndex = 0xFFFFFFFF;   /* the index of the buffer for storing the exception information */
STATIC UINT32 g_recordAddr = 0;              /* the address of storing the exception information */
STATIC UINT32 g_recordSpace = 0;             /* the size of storing the exception information */

VOID SetExcInfoRW(log_read_write_fn func)
{
    g_excInfoRW = func;
}

log_read_write_fn GetExcInfoRW(VOID)
{
    return g_excInfoRW;
}

VOID SetExcInfoBuf(CHAR *buf)
{
    g_excInfoBuf = buf;
}

CHAR *GetExcInfoBuf(VOID)
{
    return g_excInfoBuf;
}

VOID SetExcInfoIndex(UINT32 index)
{
    g_excInfoIndex = index;
}

UINT32 GetExcInfoIndex(VOID)
{
    return g_excInfoIndex;
}

VOID SetRecordAddr(UINT32 addr)
{
    g_recordAddr = addr;
}

UINT32 GetRecordAddr(VOID)
{
    return g_recordAddr;
}

VOID SetRecordSpace(UINT32 space)
{
    g_recordSpace = space;
}

UINT32 GetRecordSpace(VOID)
{
    return g_recordSpace;
}

VOID WriteExcBufVa(const CHAR *format, va_list arglist)
{
    errno_t ret;

    if (g_recordSpace > g_excInfoIndex) {
        ret = vsnprintf_s((g_excInfoBuf + g_excInfoIndex), (g_recordSpace - g_excInfoIndex),
                          (g_recordSpace - g_excInfoIndex - 1), format, arglist);
        if (ret == -1) {
            PRINT_ERR("exc info buffer is not enough or vsnprintf_s is error.\n");
            return;
        }
        g_excInfoIndex += ret;
    }
}

VOID WriteExcInfoToBuf(const CHAR *format, ...)
{
    va_list arglist;

    va_start(arglist, format);
    WriteExcBufVa(format, arglist);
    va_end(arglist);
}

VOID LOS_ExcInfoRegHook(UINT32 startAddr, UINT32 space, CHAR *buf, log_read_write_fn hook)
{
    if ((hook == NULL) || (buf == NULL)) {
        PRINT_ERR("Buf or hook is null.\n");
        return;
    }

    g_recordAddr = startAddr;
    g_recordSpace = space;
    g_excInfoBuf = buf;
    g_excInfoRW = hook;

#ifdef LOSCFG_FS_VFS
    los_vfs_init();
#endif
}

/* Be called in the exception. */
VOID OsReadWriteExceptionInfo(UINT32 startAddr, UINT32 space, UINT32 flag, CHAR *buf)
{
    if ((buf == NULL) || (space == 0)) {
        PRINT_ERR("buffer is null or space is zero\n");
        return;
    }
    // user can write exception information to files here
}

VOID OsRecordExcInfoTime(VOID)
{
#ifdef LOSCFG_FS_VFS
#define NOW_TIME_LENGTH 24
    time_t t;
    struct tm *tmTime = NULL;
    CHAR nowTime[NOW_TIME_LENGTH];

    (VOID)time(&t);
    tmTime = localtime(&t);
    if (tmTime == NULL) {
        return;
    }
    (VOID)memset_s(nowTime, sizeof(nowTime), 0, sizeof(nowTime));
    (VOID)strftime(nowTime, NOW_TIME_LENGTH, "%Y-%m-%d %H:%M:%S", tmTime);
#undef NOW_TIME_LENGTH
    WriteExcInfoToBuf("%s \n", nowTime);
#endif
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
