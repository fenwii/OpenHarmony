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

#include "cmdmonitor.h"
#include <securec.h>
#include "smc.h"
#include "tc_ns_log.h"
#include "tzdriver_compat.h"

const char g_cmdMonitorWhiteTable[][TASK_COMM_LEN] = {
#ifdef DEF_ENG
    {"tee_test_ut"},
#endif
};
const uint32_t g_whiteTableThreadNum = sizeof(g_cmdMonitorWhiteTable) /
    TASK_COMM_LEN;

static int g_cmdNeedArchiveLog = 0;
static LINUX_LIST_HEAD(g_cmdMonitorList);
static int g_cmdMonitorListSize = 0;
/* report 2 hours */
#define MAX_CMD_MONITOR_LIST 200
#define MAX_AGENT_CALL_COUNT 250
static DEFINE_MUTEX(g_cmdMonitorLock);
struct CmdMonitor {
    struct list_head list;
    struct timespec sendTime;
    int count;
    bool returned;
    bool isReported;
    int pid;
    int tid;
    char pName[TASK_COMM_LEN];
    char tName[TASK_COMM_LEN];
    unsigned int lastCmdId;
    long long timeTotal;
    int agentCallCount;
};
static struct delayed_work g_cmdMonitorWork;
static struct delayed_work g_cmdMonitorWorkArchive;
static int g_teeDetectTaCrash = 0;
enum {
    TYPE_CRASH_TA = 1,
    TYPE_CRASH_TEE = 2,
};

void TzDebugArchiveLog(void)
{
    schedule_delayed_work(&g_cmdMonitorWorkArchive, MsecsToJiffies(0));
}

void CmdMonitorTaCrash(int32_t type)
{
    g_teeDetectTaCrash = ((type == TYPE_CRASH_TEE) ? TYPE_CRASH_TEE :
        TYPE_CRASH_TA);
    TzDebugArchiveLog();
}

static bool IsThreadInWhiteTable(const char *tName)
{
    uint32_t i;

    if (tName == NULL) {
        return false;
    }

    for (i = 0; i < g_whiteTableThreadNum; i++) {
        if (!strcmp(tName, g_cmdMonitorWhiteTable[i])) {
            return true;
        }
    }
    return false;
}

bool IsThreadReported(unsigned int tid)
{
    bool ret = false;
    struct CmdMonitor *monitor = NULL;

    mutex_lock(&g_cmdMonitorLock);
    list_for_each_entry(monitor, &g_cmdMonitorList, list) {
        if (monitor->tid == tid) {
            ret = (monitor->isReported ||
                monitor->agentCallCount > MAX_AGENT_CALL_COUNT);
            break;
        }
    }
    mutex_unlock(&g_cmdMonitorLock);
    return ret;
}

void CmdMonitorResetContext(void)
{
    struct CmdMonitor *monitor = NULL;
    int pid = OsCurrTaskGet()->processID;
    int tid = OsCurrTaskGet()->taskID;

    mutex_lock(&g_cmdMonitorLock);
    list_for_each_entry(monitor, &g_cmdMonitorList, list) {
        if (monitor->pid == pid && monitor->tid == tid) {
            monitor->sendTime = CurrentKernelTime();
            if (monitor->agentCallCount + 1 < 0) {
                tloge("agent call count add overflow\n");
            } else {
                monitor->agentCallCount++;
            }
            break;
        }
    }
    mutex_unlock(&g_cmdMonitorLock);
}

static void CmdMonitorTick(void)
{
    long long timeDif;
    struct CmdMonitor *monitor = NULL;
    struct CmdMonitor *tmp = NULL;
    struct timespec nowTime = CurrentKernelTime();

    mutex_lock(&g_cmdMonitorLock);
    list_for_each_entry_safe(monitor, tmp, &g_cmdMonitorList, list) {
        if (monitor->returned == true) {
            g_cmdMonitorListSize--;
            tloge("[CmdMonitorTick] pid:%d, pName:%s, tid:%d, tName:%s, \
lastCmdId:%u, count:%d, agent call count:%d, timeTotal:%lld us returned, remained command(s):%d\n",
                monitor->pid, monitor->pName, monitor->tid,
                monitor->tName, monitor->lastCmdId,
                monitor->count, monitor->agentCallCount,
                monitor->timeTotal, g_cmdMonitorListSize);
            list_del(&monitor->list);
            free(monitor);
            continue;
        }
        /* not return, we need to check  */

        /*
        * get time value D (timeDif=nowTime-sendTime), we do not care about overflow
        * 1 year means 1000 * (60*60*24*365) = 0x757B12C00
        * only 5bytes, will not overflow
        */
        timeDif = MSEC_PER_SEC * (nowTime.tv_sec - monitor->sendTime.tv_sec) +
            (nowTime.tv_nsec - monitor->sendTime.tv_nsec) / NSEC_PER_MSEC;

        /* Temporally change timeout to 25s, we log the teeos log,and report */
        if ((timeDif > TEMPORALLY_CHAGE_TIMEOUT) && (!monitor->isReported)) {
            monitor->isReported = true;
            /* print tee stask */
            tloge("[CmdMonitorTick] pid:%d, pName:%s, tid:%d, tName:%s, \
lastCmdId:%u, agent call count:%d, timeDif:%lld ms and report\n",
                monitor->pid, monitor->pName, monitor->tid,
                monitor->tName, monitor->lastCmdId,
                monitor->agentCallCount, timeDif);
            /* threads out of white table need info dump */
            if (!(IsThreadInWhiteTable(monitor->tName))) {
                ShowCmdBitmapWithLock();
                g_cmdNeedArchiveLog = 1;
                WakeupTcSiq();
            }
        } else if (timeDif > 1 * MSEC_PER_SEC) {
            tloge("[CmdMonitorTick] pid=%d, pName=%s, tid=%d,\
lastCmdId=%u, agent call count:%d, timeDif=%lld ms\n",
                  monitor->pid, monitor->pName, monitor->tid,
                  monitor->lastCmdId, monitor->agentCallCount,
                  timeDif);
        }
    }
    if (g_cmdMonitorListSize > 0) {
        /* if have cmd in monitor list, we need tick */
        schedule_delayed_work(&g_cmdMonitorWork, MsecsToJiffies(MSEC_PER_SEC));
    }
    mutex_unlock(&g_cmdMonitorLock);
}
static void CmdMonitorTickfn(struct work_struct *work)
{
    (void)(work);
    CmdMonitorTick();
}

static void CmdMonitorArchivefn(struct work_struct *work)
{
    (void)(work);
}

static struct CmdMonitor *InitMonitorLocked(void)
{
    struct CmdMonitor *newItem = NULL;

    newItem = calloc(1, sizeof(*newItem));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)newItem)) {
        tloge("[CmdMonitorTick]calloc faild\n");
        return NULL;
    }
    newItem->sendTime = CurrentKernelTime();
    newItem->count = 1;
    newItem->agentCallCount = 0;
    newItem->returned = false;
    newItem->isReported = false;
    newItem->pid = OsCurrTaskGet()->processID;
    newItem->tid = OsCurrTaskGet()->taskID;

    LosProcessCB *runProcess = OS_PCB_FROM_PID(newItem->pid);
    if (strncpy_s(newItem->pName, TASK_COMM_LEN, runProcess->processName, OS_PCB_NAME_LEN) != EOK) {
        free(newItem);
        return NULL;
    }
    if (strncpy_s(newItem->tName, TASK_COMM_LEN, OsCurrTaskGet()->taskName, OS_TCB_NAME_LEN) != EOK) {
        free(newItem);
        return NULL;
    }
    INIT_LIST_HEAD(&newItem->list);
    list_add_tail(&newItem->list, &g_cmdMonitorList);
    g_cmdMonitorListSize++;
    return newItem;
}

void CmdMonitorLog(const TcNsSmcCmd *cmd)
{
    int foundFlag = 0;
    int pid;
    int tid;
    struct CmdMonitor *monitor = NULL;
    struct CmdMonitor *newItem = NULL;

    if (cmd == NULL) {
        return;
    }
    pid = OsCurrTaskGet()->processID;
    tid = OsCurrTaskGet()->taskID;
    mutex_lock(&g_cmdMonitorLock);
    do {
        list_for_each_entry(monitor, &g_cmdMonitorList, list) {
            if (monitor->pid == pid && monitor->tid == tid) {
                foundFlag = 1;
                /* restart */
                monitor->sendTime = CurrentKernelTime();
                monitor->count++;
                monitor->returned = false;
                monitor->isReported = false;
                monitor->lastCmdId = cmd->cmdId;
                monitor->agentCallCount = 0;
                break;
            }
        }
        if (foundFlag == 0) {
            if (g_cmdMonitorListSize > MAX_CMD_MONITOR_LIST - 1) {
                tloge("[CmdMonitorTick]MAX_CMD_MONITOR_LIST\n");
                break;
            }
            newItem = InitMonitorLocked();
            if (newItem == NULL) {
                tloge("[CmdMonitorTick]init_monitor failed\n");
                break;
            }
            newItem->lastCmdId = cmd->cmdId;
            /* the first cmd will cause timer */
            if (g_cmdMonitorListSize == 1) {
                schedule_delayed_work(&g_cmdMonitorWork,
                    MsecsToJiffies(MSEC_PER_SEC));
            }
        }
    } while (0);
    mutex_unlock(&g_cmdMonitorLock);
}

void CmdMonitorLogend(void)
{
    int pid;
    int tid;
    struct CmdMonitor *monitor = NULL;

    pid = OsCurrTaskGet()->processID;
    tid = OsCurrTaskGet()->taskID;
    mutex_lock(&g_cmdMonitorLock);
    list_for_each_entry(monitor, &g_cmdMonitorList, list) {
        if (monitor->pid == pid && monitor->tid == tid &&
            monitor->returned == false) {
            struct timespec nowTime = CurrentKernelTime();
            /*
            * get time value D (timeDif=nowTime-sendTime), we do not care about overflow
            * 1 year means 1000000 * (60*60*24*365) = 0x1CAE8C13E000
            * only 6bytes, will not overflow
            */
            long long timeDif = USEC_PER_SEC *
                (nowTime.tv_sec - monitor->sendTime.tv_sec) +
                (nowTime.tv_nsec - monitor->sendTime.tv_nsec) / NSEC_PER_USEC;
            monitor->timeTotal += timeDif;
            monitor->returned = true;
            break;
        }
    }
    mutex_unlock(&g_cmdMonitorLock);
}

void DoCmdNeedArchivelog(void)
{
    if (g_cmdNeedArchiveLog == 1) {
        g_cmdNeedArchiveLog = 0;
        schedule_delayed_work(&g_cmdMonitorWorkArchive,
            MsecsToJiffies(MSEC_PER_SEC));
    }
}
void InitCmdMonitor(void)
{
    InitDeferrableWork((struct delayed_work *)(uintptr_t)&g_cmdMonitorWork, CmdMonitorTickfn);
    InitDeferrableWork((struct delayed_work *)(uintptr_t)&g_cmdMonitorWorkArchive, CmdMonitorArchivefn);
}
