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

#include "telnet_dev.h"
#ifdef LOSCFG_NET_TELNET
#include "unistd.h"
#include "stdlib.h"
#include "sys/ioctl.h"
#include "sys/types.h"
#include "pthread.h"

#include "los_printf.h"
#if (LOSCFG_BASE_CORE_SWTMR == YES)
#include "los_swtmr_pri.h"
#endif
#include "console.h"
#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "telnet_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* event: there are more commands left in the FIFO to run */
#define TELNET_EVENT_MORE_CMD   0x01
#define TELNET_DEV_DRV_MODE     0666

STATIC TELNET_DEV_S g_telnetDev;
STATIC EVENT_CB_S *g_event;
STATIC struct inode *g_currentInode;

STATIC INLINE TELNET_DEV_S *GetTelnetDevByFile(const struct file *file, BOOL isOpenOp)
{
    struct inode *telnetInode = NULL;
    TELNET_DEV_S *telnetDev = NULL;

    if (file == NULL) {
        return NULL;
    }
    telnetInode = file->f_inode;
    if (telnetInode == NULL) {
        return NULL;
    }
    /*
     * Check if the f_inode is valid here for non-open ops (open is supposed to get invalid f_inode):
     * when telnet is disconnected, there still may be 'TelentShellTask' tasks trying to write
     * to the file, but the file has illegal f_inode because the file is used by others.
     */
    if (!isOpenOp) {
        if (telnetInode != g_currentInode) {
            return NULL;
        }
    }
    telnetDev = (TELNET_DEV_S *)telnetInode->i_private;
    return telnetDev;
}

/*
 * Description : When receive user's input commands, first copy commands to the FIFO of the telnet device.
 *               Then, notify a command resolver task (an individual shell task) to take out and run commands.
 * Return      : -1                   --- On failure
 *               Non-negative integer --- length of written commands
 */
INT32 TelnetTx(const CHAR *buf, UINT32 bufLen)
{
    UINT32 i;
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = &g_telnetDev;
    if ((buf == NULL) || (telnetDev->cmdFifo == NULL)) {
        TelnetUnlock();
        return -1;
    }

    /* size limited */
    if (bufLen > telnetDev->cmdFifo->fifoNum) {
        bufLen = telnetDev->cmdFifo->fifoNum;
    }

    if (bufLen == 0) {
        TelnetUnlock();
        return 0;
    }

    /* copy commands to the fifo of the telnet device */
    for (i = 0; i < bufLen; i++) {
        telnetDev->cmdFifo->rxBuf[telnetDev->cmdFifo->rxIndex] = *buf;
        telnetDev->cmdFifo->rxIndex++;
        telnetDev->cmdFifo->rxIndex %= FIFO_MAX;
        buf++;
    }
    telnetDev->cmdFifo->fifoNum -= bufLen;

    if (telnetDev->eventPend) {
        /* signal that there are some works to do */
        (VOID)LOS_EventWrite(&telnetDev->eventTelnet, TELNET_EVENT_MORE_CMD);
    }
    /* notify the command resolver task */
    notify_poll(&telnetDev->wait);
    TelnetUnlock();

    return (INT32)bufLen;
}

/*
 * Description : When open the telnet device, init the FIFO, wait queue etc.
 */
STATIC INT32 TelnetOpen(struct file *file)
{
    struct wait_queue_head *wait = NULL;
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = GetTelnetDevByFile(file, TRUE);
    if (telnetDev == NULL) {
        TelnetUnlock();
        return -1;
    }

    if (telnetDev->cmdFifo == NULL) {
        wait = &telnetDev->wait;
        (VOID)LOS_EventInit(&telnetDev->eventTelnet);
        g_event = &telnetDev->eventTelnet;
        telnetDev->cmdFifo = (TELNTE_FIFO_S *)malloc(sizeof(TELNTE_FIFO_S));
        if (telnetDev->cmdFifo == NULL) {
            TelnetUnlock();
            return -1;
        }
        (VOID)memset_s(telnetDev->cmdFifo, sizeof(TELNTE_FIFO_S), 0, sizeof(TELNTE_FIFO_S));
        telnetDev->cmdFifo->fifoNum = FIFO_MAX;
        LOS_ListInit(&wait->poll_queue);
    }
    g_currentInode = file->f_inode;
    TelnetUnlock();
    return 0;
}

/*
 * Description : When close the telnet device, free the FIFO, wait queue etc.
 */
STATIC INT32 TelnetClose(struct file *file)
{
    struct wait_queue_head *wait = NULL;
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = GetTelnetDevByFile(file, FALSE);
    if (telnetDev != NULL) {
        wait = &telnetDev->wait;
        LOS_ListDelete(&wait->poll_queue);
        free(telnetDev->cmdFifo);
        telnetDev->cmdFifo = NULL;
        (VOID)LOS_EventDestroy(&telnetDev->eventTelnet);
        g_event = NULL;
    }
    g_currentInode = NULL;
    TelnetUnlock();
    return 0;
}

/*
 * Description : When a command resolver task trys to read the telnet device,
 *               this method is called, and it will take out user's commands from the FIFO to run.
 * Return      : -1                   --- On failure
 *               Non-negative integer --- length of commands taken out from the FIFO of the telnet device.
 */
STATIC ssize_t TelnetRead(struct file *file, CHAR *buf, size_t bufLen)
{
    UINT32 i;
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = GetTelnetDevByFile(file, FALSE);
    if ((buf == NULL) || (telnetDev == NULL) || (telnetDev->cmdFifo == NULL)) {
        TelnetUnlock();
        return -1;
    }

    if (telnetDev->eventPend) {
        TelnetUnlock();
        (VOID)LOS_EventRead(g_event, TELNET_EVENT_MORE_CMD, LOS_WAITMODE_OR, LOS_WAIT_FOREVER);
        TelnetLock();
    }

    if (bufLen > (FIFO_MAX - telnetDev->cmdFifo->fifoNum)) {
        bufLen = FIFO_MAX - telnetDev->cmdFifo->fifoNum;
    }

    for (i = 0; i < bufLen; i++) {
        *buf++ = telnetDev->cmdFifo->rxBuf[telnetDev->cmdFifo->rxOutIndex++];
        if (telnetDev->cmdFifo->rxOutIndex >= FIFO_MAX) {
            telnetDev->cmdFifo->rxOutIndex = 0;
        }
    }
    telnetDev->cmdFifo->fifoNum += bufLen;
    /* check if no more commands left to run */
    if (telnetDev->cmdFifo->fifoNum == FIFO_MAX) {
        (VOID)LOS_EventClear(&telnetDev->eventTelnet, ~TELNET_EVENT_MORE_CMD);
    }

    TelnetUnlock();
    return (ssize_t)bufLen;
}

/*
 * Description : When a command resolver task trys to write command results to the telnet device,
 *               just use lwIP send function to send out results.
 * Return      : -1                   --- buffer is NULL
 *               Non-negative integer --- length of written data, maybe 0.
 */
STATIC ssize_t TelnetWrite(struct file *file, const CHAR *buf, const size_t bufLen)
{
    INT32 ret = 0;
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = GetTelnetDevByFile(file, FALSE);
    if ((buf == NULL) || (telnetDev == NULL) || (telnetDev->cmdFifo == NULL)) {
        TelnetUnlock();
        return -1;
    }

    if (OS_INT_ACTIVE) {
        TelnetUnlock();
        return ret;
    }

    if (!OsPreemptable()) {
        TelnetUnlock();
        return ret;
    }

    if (telnetDev->clientFd != 0) {
#if (LOSCFG_BASE_CORE_SWTMR == YES)
         /* DO NOT call blocking API in software timer task */
        if (((LosTaskCB*)OsCurrTaskGet())->taskEntry == (TSK_ENTRY_FUNC)OsSwtmrTask) {
            TelnetUnlock();
            return ret;
        }
#endif
        ret = send(telnetDev->clientFd, buf, bufLen, 0);
    }
    TelnetUnlock();
    return ret;
}

STATIC INT32 TelnetIoctl(struct file *file, const INT32 cmd, unsigned long arg)
{
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = GetTelnetDevByFile(file, FALSE);
    if (telnetDev == NULL) {
        TelnetUnlock();
        return -1;
    }

    if (cmd == CFG_TELNET_EVENT_PEND) {
        if (arg == 0) {
            telnetDev->eventPend = FALSE;
            (VOID)LOS_EventWrite(&(telnetDev->eventTelnet), TELNET_EVENT_MORE_CMD);
            (VOID)LOS_EventClear(&(telnetDev->eventTelnet), ~TELNET_EVENT_MORE_CMD);
        } else {
            telnetDev->eventPend = TRUE;
        }
    } else if (cmd == CFG_TELNET_SET_FD) {
        if (arg >= (FD_SETSIZE - 1)) {
            TelnetUnlock();
            return -1;
        }
        telnetDev->clientFd = (INT32)arg;
    }
    TelnetUnlock();
    return 0;
}

STATIC INT32 TelnetPoll(struct file *file, poll_table *table)
{
    TELNET_DEV_S *telnetDev = NULL;

    TelnetLock();

    telnetDev = GetTelnetDevByFile(file, FALSE);
    if ((telnetDev == NULL) || (telnetDev->cmdFifo == NULL)) {
        TelnetUnlock();
        return -1;
    }

    poll_wait(file, &telnetDev->wait, table);

    /* check if there are some commands to run */
    if (telnetDev->cmdFifo->fifoNum != FIFO_MAX) {
        TelnetUnlock();
        return POLLIN | POLLRDNORM;
    }
    TelnetUnlock();
    return 0;
}

STATIC const struct file_operations_vfs g_telnetOps = {
    TelnetOpen,
    TelnetClose,
    TelnetRead,
    TelnetWrite,
    NULL,
    TelnetIoctl,
    NULL,
#ifndef CONFIG_DISABLE_POLL
    TelnetPoll,
#endif
    NULL,
};

/* Once the telnet server stopped, remove the telnet device file. */
INT32 TelnetedUnregister(VOID)
{
    free(g_telnetDev.cmdFifo);
    g_telnetDev.cmdFifo = NULL;
    (VOID)unregister_driver(TELNET);

    return 0;
}

/* Once the telnet server started, setup the telnet device file. */
INT32 TelnetedRegister(VOID)
{
    INT32 ret;

    g_telnetDev.id = 0;
    g_telnetDev.cmdFifo = NULL;
    g_telnetDev.eventPend = TRUE;

    ret = register_driver(TELNET, &g_telnetOps, TELNET_DEV_DRV_MODE, &g_telnetDev);
    if (ret != 0) {
        PRINT_ERR("Telnet register driver error.\n");
    }
    return ret;
}

/* When a telnet client connection established, update the output console for tasks. */
INT32 TelnetDevInit(INT32 clientFd)
{
    INT32 ret;

    if (clientFd < 0) {
        PRINT_ERR("Invalid telnet clientFd.\n");
        return -1;
    }
    ret = system_console_init(TELNET);
    if (ret != 0) {
        PRINT_ERR("Telnet console init error.\n");
        return ret;
    }
    ret = ioctl(STDIN_FILENO, CFG_TELNET_SET_FD, clientFd);
    if (ret != 0) {
        PRINT_ERR("Telnet device ioctl error.\n");
        (VOID)system_console_deinit(TELNET);
    }
    return ret;
}

/* When closing the telnet client connection, reset the output console for tasks. */
INT32 TelnetDevDeinit(VOID)
{
    INT32 ret;

    ret = system_console_deinit(TELNET);
    if (ret != 0) {
        PRINT_ERR("Telnet console deinit error.\n");
    }
    return ret;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
