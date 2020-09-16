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

#include "telnet_loop.h"
#ifdef LOSCFG_NET_TELNET
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "netinet/tcp.h"
#include "sys/select.h"
#include "sys/types.h"
#include "sys/prctl.h"

#include "los_task.h"
#include "linux/atomic.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "console.h"
#ifdef LOSCFG_SHELL
#include "shell.h"
#include "shcmd.h"
#endif
#include "telnet_pri.h"
#include "telnet_dev.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* TELNET commands in RFC854 */
#define TELNET_SB   250 /* Indicates that what follows is subnegotiation of the indicated option */
#define TELNET_WILL 251 /* Indicates the desire to perform the indicated option */
#define TELNET_DO   253 /* Indicates the request for the other party to perform the indicated option */
#define TELNET_IAC  255 /* Interpret as Command */

/* telnet options in IANA */
#define TELNET_ECHO 1    /* Echo */
#define TELNET_SGA  3    /* Suppress Go Ahead */
#define TELNET_NAWS 31   /* Negotiate About Window Size */
#define TELNET_NOP  0xf1 /* Unassigned in IANA, putty use this to keepalive */

#define LEN_IAC_CMD      2 /* Only 2 char: |IAC|cmd| */
#define LEN_IAC_CMD_OPT  3 /* Only 3 char: |IAC|cmd|option| */
#define LEN_IAC_CMD_NAWS 9 /* NAWS: |IAC|SB|NAWS|x1|x2|x3|x4|IAC|SE| */

/* server/client settings */
#define TELNET_TASK_STACK_SIZE  0x2000
#define TELNET_TASK_PRIORITY    9

/* server settings */
#define TELNET_LISTEN_BACKLOG   128
#define TELNET_ACCEPT_INTERVAL  200

/* client settings */
#define TELNET_CLIENT_POLL_TIMEOUT  2000
#define TELNET_CLIENT_READ_BUF_SIZE 256
#define TELNET_CLIENT_READ_FILTER_BUF_SIZE (8 * 1024)

/* limitation: only support 1 telnet client connection */
STATIC volatile INT32 g_telnetClientFd = -1;  /* client fd */

/* limitation: only support 1 telnet server */
STATIC volatile INT32 g_telnetListenFd = -1;  /* listen fd of telnetd */

/* each bit for a client connection, although only support 1 connection for now */
STATIC volatile UINT32 g_telnetMask = 0;
/* taskID of telnetd */
STATIC atomic_t g_telnetTaskId = 0;
/* protect listenFd, clientFd etc. */
pthread_mutex_t g_telnetMutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

VOID TelnetLock(VOID)
{
    (VOID)pthread_mutex_lock(&g_telnetMutex);
}

VOID TelnetUnlock(VOID)
{
    (VOID)pthread_mutex_unlock(&g_telnetMutex);
}

/* filter out iacs from client stream */
STATIC UINT8 *ReadFilter(const UINT8 *src, UINT32 srcLen, UINT32 *dstLen)
{
    STATIC UINT8 buf[TELNET_CLIENT_READ_FILTER_BUF_SIZE];
    UINT8 *dst = buf;
    UINT32 left = srcLen;

    while (left > 0) {
        if (*src != TELNET_IAC) {
            *dst = *src;
            dst++;
            src++;
            left--;
            continue;
        }

        /*
         * if starting with IAC, filter out IAC as following
         * |IAC|          --> skip
         * |IAC|NOP|...   --> ... : skip for putty keepalive etc.
         * |IAC|x|        --> skip
         * |IAC|IAC|x|... --> |IAC|... : skip for literal cmds
         * |IAC|SB|NAWS|x1|x2|x3|x4|IAC|SE|... --> ... : skip NAWS(unsupported)
         * |IAC|x|x|...   --> ... : skip unsupported IAC
         */
        if (left == 1) {
            break;
        }
        /* left no less than 2 */
        if (*(src + 1) == TELNET_NOP) {
            src += LEN_IAC_CMD;
            left -= LEN_IAC_CMD;
            continue;
        }
        if (left == LEN_IAC_CMD) {
            break;
        }
        /* left no less than 3 */
        if (*(src + 1) == TELNET_IAC) {
            *dst = TELNET_IAC;
            dst++;
            src += LEN_IAC_CMD;
            left -= LEN_IAC_CMD;
            continue;
        }
        if ((*(src + 1) == TELNET_SB) && (*(src + LEN_IAC_CMD) == TELNET_NAWS)) {
            if (left > LEN_IAC_CMD_NAWS) {
                src += LEN_IAC_CMD_NAWS;
                left -= LEN_IAC_CMD_NAWS;
                continue;
            }
            break;
        }
        src += LEN_IAC_CMD_OPT;
        left -= LEN_IAC_CMD_OPT;
    }

    if (dstLen != NULL) {
        *dstLen = dst - buf;
    }
    return buf;
}

/*
 * Description : Write data to fd.
 * Input       : fd     --- the fd to write.
 *             : src    --- data pointer.
 *             : srcLen --- data length.
 * Return      : length of written data.
 */
STATIC ssize_t WriteToFd(INT32 fd, const CHAR *src, size_t srcLen)
{
    size_t sizeLeft;
    ssize_t sizeWritten;

    sizeLeft = srcLen;
    while (sizeLeft > 0) {
        sizeWritten = write(fd, src, sizeLeft);
        if (sizeWritten < 0) {
            /* last write failed */
            if (sizeLeft == srcLen) {
                /* nothing was written in any loop */
                return -1;
            } else {
                /* something was written in previous loop */
                break;
            }
        } else if (sizeWritten == 0) {
            break;
        }
        sizeLeft -= (size_t)sizeWritten;
        src += sizeWritten;
    }

    return (ssize_t)(srcLen - sizeLeft);
}

/* Try to remove the client device if there is any client connection */
STATIC VOID TelnetClientClose(VOID)
{
    /* check if there is any client connection */
    if (g_telnetMask == 0) {
        return;
    }
    (VOID)TelnetDevDeinit();
    g_telnetMask = 0;
    printf("telnet client disconnected.\n");
}

/* Release the client and server fd */
STATIC VOID TelnetRelease(VOID)
{
    if (g_telnetClientFd >= 0) {
        (VOID)close(g_telnetClientFd);
        g_telnetClientFd = -1;
    }

    if (g_telnetListenFd >= 0) {
        (VOID)close(g_telnetListenFd);
        g_telnetListenFd = -1;
    }
}

/* Stop telnet server */
STATIC VOID TelnetdDeinit(VOID)
{
    if (atomic_read(&g_telnetTaskId) == 0) {
        PRINTK("telnet server is not running!\n");
        return;
    }

    TelnetRelease();
    (VOID)TelnetedUnregister();
    atomic_set(&g_telnetTaskId, 0);
    PRINTK("telnet server closed.\n");
}

/*
 * Description : Setup the listen fd for telnetd with specific port.
 * Input       : port --- the port at which telnet server listens.
 * Return      : -1           --- on error
 *             : non-negative --- listen fd if OK
 */
STATIC INT32 TelnetdInit(UINT16 port)
{
    INT32 listenFd;
    INT32 reuseAddr = 1;
    struct sockaddr_in inTelnetAddr;

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd == -1) {
        PRINT_ERR("TelnetdInit : socket error.\n");
        goto ERR_OUT;
    }

    /* reuse listen port */
    if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) != 0) {
        PRINT_ERR("TelnetdInit : setsockopt REUSEADDR error.\n");
        goto ERR_CLOSE_FD;
    }

    (VOID)memset_s(&inTelnetAddr, sizeof(struct sockaddr_in), 0, sizeof(struct sockaddr_in));
    inTelnetAddr.sin_family = AF_INET;
    inTelnetAddr.sin_addr.s_addr = INADDR_ANY;
    inTelnetAddr.sin_port = htons(port);

    if (bind(listenFd, (const struct sockaddr *)&inTelnetAddr, sizeof(struct sockaddr_in)) == -1) {
        PRINT_ERR("TelnetdInit : bind error.\n");
        goto ERR_CLOSE_FD;
    }

    if (listen(listenFd, TELNET_LISTEN_BACKLOG) == -1) {
        PRINT_ERR("TelnetdInit : listen error.\n");
        goto ERR_CLOSE_FD;
    }

    return listenFd;

ERR_CLOSE_FD:
    (VOID)close(listenFd);
ERR_OUT:
    return -1;
}

STATIC INT32 TelnetClientPrepare(INT32 clientFd)
{
    INT32 keepAlive = TELNET_KEEPALIVE;
    INT32 keepIdle = TELNET_KEEPIDLE;
    INT32 keepInterval = TELNET_KEEPINTV;
    INT32 keepCnt = TELNET_KEEPCNT;
    const UINT8 doEcho[] = { TELNET_IAC, TELNET_DO, TELNET_ECHO };
    const UINT8 doNaws[] = { TELNET_IAC, TELNET_DO, TELNET_NAWS };
    const UINT8 willEcho[] = { TELNET_IAC, TELNET_WILL, TELNET_ECHO };
    const UINT8 willSga[] = { TELNET_IAC, TELNET_WILL, TELNET_SGA };

    if (g_telnetListenFd == -1) {
        return -1;
    }
    g_telnetClientFd = clientFd;
    if (TelnetDevInit(clientFd) != 0) {
        g_telnetClientFd = -1;
        return -1;
    }
    g_telnetMask = 1;

    /* negotiate with client */
    (VOID)WriteToFd(clientFd, (CHAR *)doEcho, sizeof(doEcho));
    (VOID)WriteToFd(clientFd, (CHAR *)doNaws, sizeof(doNaws));
    (VOID)WriteToFd(clientFd, (CHAR *)willEcho, sizeof(willEcho));
    (VOID)WriteToFd(clientFd, (CHAR *)willSga, sizeof(willSga));

    /* enable TCP keepalive to check whether telnet link is alive */
    if (setsockopt(clientFd, SOL_SOCKET, SO_KEEPALIVE, (VOID *)&keepAlive, sizeof(keepAlive)) < 0) {
        PRINT_ERR("telnet setsockopt SO_KEEPALIVE error.\n");
    }
    if (setsockopt(clientFd, IPPROTO_TCP, TCP_KEEPIDLE, (VOID *)&keepIdle, sizeof(keepIdle)) < 0) {
        PRINT_ERR("telnet setsockopt TCP_KEEPIDLE error.\n");
    }
    if (setsockopt(clientFd, IPPROTO_TCP, TCP_KEEPINTVL, (VOID *)&keepInterval, sizeof(keepInterval)) < 0) {
        PRINT_ERR("telnet setsockopt TCP_KEEPINTVL error.\n");
    }
    if (setsockopt(clientFd, IPPROTO_TCP, TCP_KEEPCNT, (VOID *)&keepCnt, sizeof(keepCnt)) < 0) {
        PRINT_ERR("telnet setsockopt TCP_KEEPCNT error.\n");
    }
    return 0;
}

STATIC VOID *TelnetClientLoop(VOID *arg)
{
    struct pollfd pollFd;
    INT32 ret;
    INT32 nRead;
    UINT32 len;
    UINT8 buf[TELNET_CLIENT_READ_BUF_SIZE];
    UINT8 *cmdBuf = NULL;
    INT32 clientFd = (INT32)(UINTPTR)arg;

    (VOID)prctl(PR_SET_NAME, "TelnetClientLoop", 0, 0, 0);
    TelnetLock();
    if (TelnetClientPrepare(clientFd) != 0) {
        TelnetUnlock();
        (VOID)close(clientFd);
        return NULL;
    }
    TelnetUnlock();

    while (1) {
        pollFd.fd = clientFd;
        pollFd.events = POLLIN | POLLRDHUP;
        pollFd.revents = 0;

        ret = poll(&pollFd, 1, TELNET_CLIENT_POLL_TIMEOUT);
        if (ret < 0) {
            break;
        }
        if (ret == 0) {
            continue;
        }
        /* connection reset, maybe keepalive failed or reset by peer */
        if ((UINT16)pollFd.revents & (POLLERR | POLLHUP | POLLRDHUP)) {
            break;
        }

        if ((UINT16)pollFd.revents & POLLIN) {
            nRead = read(clientFd, buf, sizeof(buf));
            if (nRead <= 0) {
                /* telnet client shutdown */
                break;
            }
            cmdBuf = ReadFilter(buf, (UINT32)nRead, &len);
            if (len > 0) {
                (VOID)TelnetTx((CHAR *)cmdBuf, len);
            }
        }
    }
    TelnetLock();
    TelnetClientClose();
    (VOID)close(clientFd);
    clientFd = -1;
    g_telnetClientFd = -1;
    TelnetUnlock();
    return NULL;
}

STATIC VOID TelnetClientTaskAttr(pthread_attr_t *threadAttr)
{
    (VOID)pthread_attr_init(threadAttr);
    threadAttr->inheritsched = PTHREAD_EXPLICIT_SCHED;
    threadAttr->schedparam.sched_priority = TELNET_TASK_PRIORITY;
    threadAttr->detachstate = PTHREAD_CREATE_DETACHED;
    (VOID)pthread_attr_setstacksize(threadAttr, TELNET_TASK_STACK_SIZE);
}

/*
 * Description : Handle the client connection request.
 *               Create a client connection if permitted.
 * Return      : 0  --- please continue the server accept loop
 *             : -1 --- please stop the server accept loop.
 */
STATIC INT32 TelnetdAcceptClient(INT32 clientFd, const struct sockaddr_in *inTelnetAddr)
{
    INT32 ret = 0;
    pthread_t tmp;
    pthread_attr_t useAttr;

    TelnetClientTaskAttr(&useAttr);

    if (clientFd < 0) {
        ret = -1;
        goto ERROUT;
    }

    TelnetLock();

    if (g_telnetListenFd == -1) {
        /* server already has been closed, so quit this task now */
        ret = -1;
        goto ERROUT_UNLOCK;
    }

    if (g_telnetClientFd >= 0) {
        /* alreay connected and support only one */
        goto ERROUT_UNLOCK;
    }

    g_telnetClientFd = clientFd;

    if (pthread_create(&tmp, &useAttr, TelnetClientLoop, (VOID *)(UINTPTR)clientFd) != 0) {
        PRINT_ERR("Failed to create client handle task\n");
        g_telnetClientFd = -1;
        goto ERROUT_UNLOCK;
    }
    TelnetUnlock();
    return ret;

ERROUT_UNLOCK:
    (VOID)close(clientFd);
    clientFd = -1;
    TelnetUnlock();
ERROUT:
    return ret;
}

/*
 * Waiting for client's connection. Only allow 1 connection, and others will be discarded.
 */
STATIC VOID TelnetdAcceptLoop(INT32 listenFd)
{
    INT32 clientFd = -1;
    struct sockaddr_in inTelnetAddr;
    INT32 len = sizeof(inTelnetAddr);

    TelnetLock();
    g_telnetListenFd = listenFd;

    while (g_telnetListenFd >= 0) {
        TelnetUnlock();

        (VOID)memset_s(&inTelnetAddr, sizeof(inTelnetAddr), 0, sizeof(inTelnetAddr));
        clientFd = accept(listenFd, (struct sockaddr *)&inTelnetAddr, (socklen_t *)&len);
        if (TelnetdAcceptClient(clientFd, &inTelnetAddr) == 0) {
            /*
             * Sleep sometime before next loop: mostly we already have one connection here,
             * and the next connection will be declined. So don't waste our cpu.
             */
            LOS_Msleep(TELNET_ACCEPT_INTERVAL);
        } else {
            return;
        }
        TelnetLock();
    }
    TelnetUnlock();
}

STATIC INT32 TelnetdMain(VOID)
{
    INT32 sock;
    INT32 ret;

    sock = TelnetdInit(TELNETD_PORT);
    if (sock == -1) {
        PRINT_ERR("telnet init error.\n");
        return -1;
    }

    TelnetLock();
    ret = TelnetedRegister();
    TelnetUnlock();

    if (ret != 0) {
        PRINT_ERR("telnet register error.\n");
        (VOID)close(sock);
        return -1;
    }

    PRINTK("start telnet server successfully, waiting for connection.\n");
    TelnetdAcceptLoop(sock);
    return 0;
}

/*
 * Try to create telnetd task.
 */
STATIC VOID TelnetdTaskInit(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S initParam = {0};

    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TelnetdMain;
    initParam.uwStackSize = TELNET_TASK_STACK_SIZE;
    initParam.pcName = "TelnetServer";
    initParam.usTaskPrio = TELNET_TASK_PRIORITY;
    initParam.uwResved = LOS_TASK_STATUS_DETACHED;

    if (atomic_read(&g_telnetTaskId) != 0) {
        PRINT_ERR("telnet server is already running!\n");
        return;
    }

    ret = LOS_TaskCreate((UINT32 *)&g_telnetTaskId, &initParam);
    if (ret != LOS_OK) {
        PRINT_ERR("failed to create telnet server task!\n");
    }
}

/*
 * Try to destroy telnetd task.
 */
STATIC VOID TelnetdTaskDeinit(VOID)
{
    if (atomic_read(&g_telnetTaskId) == 0) {
        PRINTK("telnet server is not running, please start up telnet server first.\n");
        return;
    }

    TelnetLock();
    TelnetClientClose();
    TelnetdDeinit();
    TelnetUnlock();
}

STATIC VOID TelnetUsage(VOID)
{
    PRINTK("Usage: telnet [OPTION]...\n");
    PRINTK("Start or close telnet server.\n\n");
    PRINTK("  on       Init the telnet server\n");
    PRINTK("  off      Deinit the telnet server\n");
}

INT32 TelnetCmd(UINT32 argc, const CHAR **argv)
{
    if (argc != 1) {
        TelnetUsage();
        return 0;
    }

    if (strcmp(argv[0], "on") == 0) {
        /* telnet on: try to start telnet server task */
        TelnetdTaskInit();
        return 0;
    }
    if (strcmp(argv[0], "off") == 0) {
        /* telnet off: try to stop clients, then stop server task */
        TelnetdTaskDeinit();
        return 0;
    }

    TelnetUsage();
    return 0;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(telnet_shellcmd, CMD_TYPE_EX, "telnet", 1, (CmdCallBackFunc)TelnetCmd);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
