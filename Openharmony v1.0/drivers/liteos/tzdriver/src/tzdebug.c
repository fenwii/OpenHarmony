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

#include "tzdebug.h"
#include <securec.h>
#include <stdarg.h>
#include "cmdmonitor.h"
#include "mailbox_mempool.h"
#include "smc.h"
#include "tc_client_sub_driver.h"
#include "tc_ns_log.h"
#include "teek_client_api.h"
#include "teek_client_constants.h"
#include "teek_ns_client.h"
#include "tzdriver_compat.h"

typedef void (*TzdebugOptFunc)(const char *param);

struct OptOps {
    char *name;
    TzdebugOptFunc func;
};

static DEFINE_MUTEX(g_meminfoLock);
static struct TeeMem g_teeMeminfo = {0};
static int SendDumpMem(int flag, const struct TeeMem *statmem);
static void TzMemDump(const char *param);

void TeeDumpMem(void)
{
    TzMemDump(NULL);
}

/* get meminfo (TeeMem + N * ta_mem < 4Kbyte) from tee */
static int GetTeeMemInfoCmd(void)
{
    int ret;
    int sret;
    struct TeeMem *mem = (struct TeeMem *)MailboxAlloc(sizeof(*mem), MB_FLAG_ZERO);

    if (mem == NULL) {
        return -1;
    }
    ret = SendDumpMem(0, mem);
    mutex_lock(&g_meminfoLock);
    sret = memcpy_s((void *)&g_teeMeminfo, sizeof(g_teeMeminfo), mem, sizeof(*mem));
    if (sret != 0) {
        tloge("sret=%d\n", sret);
    }
    mutex_unlock(&g_meminfoLock);
    MailboxFree(mem);
    return ret;
}

static atomic_t g_cmdSend = ATOMIC_INIT(1);

void SetCmdSendState(void)
{
    atomic_set(&g_cmdSend, 1);
}

int GetTeeMeminfo(struct TeeMem *meminfo)
{
    errno_t ret;

    if (meminfo == NULL) {
        return -1;
    }
    if (atomic_read(&g_cmdSend)) {
        if (GetTeeMemInfoCmd() != 0) {
            return -1;
        }
    } else {
        atomic_set(&g_cmdSend, 0);
    }
    mutex_lock(&g_meminfoLock);
    ret = memcpy_s((void *)meminfo, sizeof(*meminfo),
        (void *)&g_teeMeminfo, sizeof(g_teeMeminfo));
    mutex_unlock(&g_meminfoLock);
    if (ret != EOK) {
        return -1;
    }

    return 0;
}
EXPORT_SYMBOL(GetTeeMeminfo);

static int SendDumpMem(int flag, const struct TeeMem *statmem)
{
    TcNsSmcCmd smcCmd = { {0}, 0 };
    struct MbCmdPack *mbPack = NULL;
    int ret;

    if (statmem == NULL) {
        tloge("statmem is NULL\n");
        return -1;
    }
    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        return -ENOMEM;
    }
    smcCmd.cmdId = GLOBAL_CMD_ID_DUMP_MEMINFO;
    smcCmd.globalCmd = true;
    mbPack->operation.paramTypes = TEEC_PARAM_TYPES(
        TEE_PARAM_TYPE_MEMREF_INOUT, TEE_PARAM_TYPE_VALUE_INPUT,
        TEE_PARAM_TYPE_NONE, TEE_PARAM_TYPE_NONE);
    mbPack->operation.params[TEE_PARAM_ONE].memref.buffer = LOS_PaddrQuery((void *)statmem);
    mbPack->operation.params[TEE_PARAM_ONE].memref.size = sizeof(*statmem);
    mbPack->operation.bufferHaddr[TEE_PARAM_ONE] = 0;
    mbPack->operation.params[TEE_PARAM_TWO].value.a = flag;
    smcCmd.operationPhys =
            (unsigned int)LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    ret = TcNsSmc(&smcCmd);
    if (ret) {
        tloge("SendDumpMem failed.\n");
    }
    MailboxFree(mbPack);
    return ret;
}

static void ArchiveLog(const char *param)
{
    (void)param;
    TzDebugArchiveLog();
}

static void TzDump(const char *param)
{
    (void)param;
    ShowCmdBitmap();
    WakeupTcSiq();
}

static void TzMemDump(const char *param)
{
    struct TeeMem *mem = NULL;

    (void)param;
    mem = (struct TeeMem *)MailboxAlloc(sizeof(*mem), MB_FLAG_ZERO);
    if (mem == NULL) {
        tloge("mailbox alloc failed\n");
        return;
    }
    if (SendDumpMem(1, mem) != 0) {
        tloge("send dump mem failed\n");
    }

    MailboxFree(mem);
}

static int MemstatThread(UINTPTR arg, int len)
{
    (void)len;
    (void)arg;
    return 0;
}

static void TzMemStat(const char *param)
{
    LosTaskCB *stat_tsk = NULL;
    (void)param;
    stat_tsk = KthreadRun(MemstatThread, NULL, 0, "tzmemstat");
    if (IS_ERR(stat_tsk)) {
        tloge("memstat failed\n");
    }
}

static void TzLogWriteDbg(const char *param)
{
    (void)param;
}

static void TzHelp(const char *param);

static struct OptOps g_optArr[] = {
    {"help", TzHelp},
    {"archivelog", ArchiveLog},
    {"dump", TzDump},
    {"memdump", TzMemDump},
    {"logwrite", TzLogWriteDbg},
    {"dump_service", DumpServicesStatus},
    {"memstat", TzMemStat},
};

static void TzHelp(const char *param)
{
    uint32_t i;
    (void)param;

    for (i = 0; i < sizeof(g_optArr) / sizeof(struct OptOps); i++) {
        tloge("cmd:%s\n", g_optArr[i].name);
    }
}

static ssize_t TzDbgOptWrite(struct file *filp,
    const char __user *ubuf, size_t cnt)
{
    char buf[128] = {0};
    char *value = NULL;
    char *p = NULL;
    uint32_t i = 0;

    if ((ubuf == NULL) || (filp == NULL)) {
        return -EINVAL;
    }

    if (cnt >= sizeof(buf)) {
        return -EINVAL;
    }

    if (cnt == 0) {
        return -EINVAL;
    }

    if (copy_from_user(buf, ubuf, cnt)) {
        return -EFAULT;
    }
    buf[cnt] = 0;
    if (cnt > 0 && buf[cnt - 1] == '\n') {
        buf[cnt - 1] = 0;
    }
    value = buf;
    p = strsep(&value, ":");
    if (p == NULL) {
        return -EINVAL;
    }
    for (i = 0; i < sizeof(g_optArr) / sizeof(struct OptOps); i++) {
        if (!strncmp(p, g_optArr[i].name, strlen(g_optArr[i].name)) &&
            strlen(p) == strlen(g_optArr[i].name)) {
            g_optArr[i].func(value);
            return cnt;
        }
    }
    return -EFAULT;
}

static const struct file_operations_vfs g_tzDbgOptFops = {
    .write = TzDbgOptWrite,
};

#define TC_NS_CLIENT_TZDEBUG "/dev/tzdebug"

int TzdebugInit(void)
{
    int ret = CreateTcClientDevice(TC_NS_CLIENT_TZDEBUG, &g_tzDbgOptFops);
    if (ret != EOK) {
        return ret;
    }
    return 0;
}
