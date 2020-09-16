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

#include "liteipc_adapter.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <threads.h>
#include <time.h>
#include "liteipc.h"
#include "utils_list.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define ENABLE_IPC_CB_TIMER YES

static IpcContext* g_context = NULL;
static pthread_mutex_t g_ipcContextMutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    bool usedFlag;
    IpcMsgHandler hdler;
    void* arg;
} IpcMsgHandlerPair;

typedef struct {
    UTILS_DL_LIST list;
    uint32_t handle;
    IpcMsgHandlerPair hdlerPairs[MAX_DEATHCB_PER_SVC];
    size_t size;
    bool isCallbackRuning;
} Testament;

typedef struct {
    UTILS_DL_LIST list;
    uint32_t token;
    IpcMsgHandlerPair hdlerPair;
#if (ENABLE_IPC_CB_TIMER == YES)
    uint32_t mode;
    uint32_t timeout;
    timer_t timerId;
#endif
} AnonymousApi;

typedef void (*TimerHandler)(int);

typedef struct {
    pthread_mutex_t mutex;
    int32_t handleId;
    bool threadWorking;
    UTILS_DL_LIST apis;
    UTILS_DL_LIST testaments;
} IpcCallckCb;

static IpcCallckCb g_ipcCallbackCb = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .handleId = -1,
    .threadWorking = false
};

#define DEATH_HANDLE UINT32_MAX
#define MAX_ERR_STR 60

#define NS_PER_MS  1000000ULL
#define NS_PER_SEC 1000000000ULL

static void Perror(int msgErrno);

#define LOG(level, format, ...)                      \
    do {                                             \
        printf("[%s : %d]", __FUNCTION__, __LINE__); \
        printf(format, ##__VA_ARGS__);               \
        printf("\n");                                \
    } while (0)

#define LOG_ERRNO(format, ...)                       \
    do {                                             \
        printf("[%s : %d]", __FUNCTION__, __LINE__); \
        Perror(errno);                               \
        printf(format, ##__VA_ARGS__);               \
        printf("\n");                                \
    } while (0)

#define RETURN_IF_IPC_IOCTL_FAILED(retVal)             \
    do {                                               \
        if (ret < 0) {                                 \
            LOG_ERRNO("Liteipc driver ioctl failed."); \
            return (retVal);                           \
        }                                              \
    } while (0)

static void Perror(int msgErrno)
{
    char errbuf[MAX_ERR_STR];
    int rv = strerror_r(msgErrno, errbuf, sizeof(errbuf));
    if (rv == -1) {
        printf("[errno:%d]", msgErrno);
    } else {
        printf("[errnoStr:%s]", errbuf);
    }
}

static inline void InitCallbackCb()
{
    UtilsListInit(&g_ipcCallbackCb.apis);
    UtilsListInit(&g_ipcCallbackCb.testaments);
}

static int32_t GetLiteIpcContext(size_t mmapSize, IpcContext* context)
{
    void* addr = NULL;
    int32_t fd = -1;
    IpcContext* con = NULL;

    if (g_context != NULL) {
        if (context != NULL) {
            *context = *g_context;
        }
        return LITEIPC_OK;
    }

    if (pthread_mutex_lock(&g_ipcContextMutex) != 0) {
        LOG_ERRNO("Get ipc context mutex failed.");
        return LITEIPC_EINTNL;
    }
    if (g_context == NULL) {
        fd = open(LITEIPC_DRIVER, O_RDONLY);
        if (fd == -1) {
            LOG_ERRNO("Open liteipc driver failed.");
            goto OPEN_ERR;
        }
        /* 0 means use default size */
        if (mmapSize == 0) {
            mmapSize = MMAP_DEFAULT_SIZE;
        }
        addr = mmap(NULL, mmapSize, PROT_READ, MAP_PRIVATE, fd, 0);
        if (addr == MAP_FAILED) {
            LOG_ERRNO("Mmap failed.(size=%u)", mmapSize);
            goto MMAP_ERR;
        }

        con = malloc(sizeof(IpcContext));
        if (con == NULL) {
            LOG(ERROR, "Malloc failed.(size=%u)", sizeof(IpcContext));
            goto MALLOC_ERR;
        }
        con->fd = fd;
        con->mmapSize = mmapSize;
        InitCallbackCb();
        g_context = con;
    }
    if (context != NULL) {
        *context = *g_context;
    }
    pthread_mutex_unlock(&g_ipcContextMutex);
    return LITEIPC_OK;

MALLOC_ERR:
    munmap(addr, mmapSize);
MMAP_ERR:
    close(fd);
OPEN_ERR:
    pthread_mutex_unlock(&g_ipcContextMutex);
    return LITEIPC_EINTNL;
}

IpcContext* OpenLiteIpc(size_t mmapSize)
{
    if ((mmapSize == 0) || (mmapSize > MMAP_MAX_SIZE)) {
        LOG(ERROR, "MmapSize not available");
        return NULL;
    }
    return (IpcContext*)(intptr_t)(GetLiteIpcContext(mmapSize, NULL) == LITEIPC_OK);
}

void CloseLiteIpc(IpcContext* context)
{
}

int32_t SetSaManager(const IpcContext* con, size_t maxMsgSize)
{
    IpcContext context;
    int32_t ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    ret = ioctl(context.fd, IPC_SET_CMS, maxMsgSize);
    RETURN_IF_IPC_IOCTL_FAILED(LITEIPC_EBADF);

    return LITEIPC_OK;
}

int32_t AddServiceAccess(SvcIdentity sid, pid_t pid)
{
    IpcContext context;
    int32_t ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    CmsCmdContent content = {
        .cmd = CMS_ADD_ACCESS,
        .taskID = pid,
        .serviceHandle = sid.handle
    };
    ret = ioctl(context.fd, IPC_CMS_CMD, &content);
    RETURN_IF_IPC_IOCTL_FAILED(LITEIPC_EBADF);

    return LITEIPC_OK;
}

int32_t GenServiceHandle(SvcIdentity* sid, pid_t tid)
{
    IpcContext context;
    int32_t ret;

    if (sid == NULL) {
        LOG(ERROR, "Invalid parameter, sid is null pointer.");
        return LITEIPC_EINVAL;
    }

    ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    CmsCmdContent content = {
        .cmd = CMS_GEN_HANDLE,
        .taskID = tid
    };
    ret = ioctl(context.fd, IPC_CMS_CMD, &content);
    RETURN_IF_IPC_IOCTL_FAILED(LITEIPC_EBADF);

    sid->handle = content.serviceHandle;
    return LITEIPC_OK;
}

int32_t StartLoop(const IpcContext* con, IpcMsgHandler func, void* arg)
{
    IpcContext context;
    int32_t ret;

    if (func == NULL) {
        return LITEIPC_EINVAL;
    }

    ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    while (1) {
        IpcContent content = {.flag = RECV};
        ret = ioctl(context.fd, IPC_SEND_RECV_MSG, &content);
        if (ret < 0) {
            LOG_ERRNO("Bad ioctl request.");
            continue;
        }

        IpcIo io;
        IpcIoInitFromMsg(&io, content.inMsg);
        /* Dispatch the receiving message */
        (void)func(con, content.inMsg, &io, arg);
    }

    return LITEIPC_OK;
}

int32_t GetToken(const void* ipcMsg, uint32_t* token)
{
    if ((ipcMsg == NULL) || (token == NULL)) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    *token = in->target.token;
    return LITEIPC_OK;
}

int32_t GetCode(const void* ipcMsg, uint32_t* code)
{
    if ((ipcMsg == NULL) || (code == NULL)) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    *code = in->code;
    return LITEIPC_OK;
}

int32_t GetFlag(const void* ipcMsg, uint32_t* flag)
{
    if ((ipcMsg == NULL) || (flag == NULL)) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    *flag = in->flag;
    return LITEIPC_OK;
}

pid_t GetCallingTid(const void* ipcMsg)
{
    if (ipcMsg == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    return (pid_t)in->taskID;
}

pid_t GetCallingPid(const void* ipcMsg)
{
    if (ipcMsg == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    return (pid_t)in->processID;
}

pid_t GetCallingUid(const void* ipcMsg)
{
    if (ipcMsg == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    return (pid_t)in->userID;
}

pid_t GetCallingGid(const void* ipcMsg)
{
    if (ipcMsg == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    const IpcMsg* in = (const IpcMsg*)ipcMsg;
    return (pid_t)in->gid;
}

static int32_t CheckIpcIo(IpcIo* data)
{
    uint32_t totalSize;
    /* It's OK if data is null */
    if (data == NULL) {
        return LITEIPC_OK;
    }
    if ((IpcIoAvailable(data) == false) ||
        (data->bufferCur == NULL) ||
        (data->bufferBase == NULL) ||
        (data->offsetsCur == NULL) ||
        (data->offsetsBase == NULL) ||
        ((intptr_t)data->bufferBase < (intptr_t)data->offsetsCur)) {
        return LITEIPC_EINVAL;
    }
    totalSize = data->bufferCur - data->bufferBase + ((char*)data->offsetsCur - (char*)data->offsetsBase);
    if (totalSize > IPC_IO_DATA_MAX) {
        LOG(ERROR, "IpcIo data too big, please use IpcIoPushDataBuff to push big data.");
        return LITEIPC_EINVAL;
    }
    return LITEIPC_OK;
}

int32_t Transact(const IpcContext* con, SvcIdentity sid, uint32_t code, IpcIo* data, IpcIo* reply, IpcFlag flag, uintptr_t* ptr)
{
    IpcContext context;
    int32_t ret;

    if ((flag > LITEIPC_FLAG_ONEWAY) || ((flag == LITEIPC_FLAG_DEFAULT) && (ptr == NULL))) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    ret = CheckIpcIo(data);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "CheckIpcIo failed.");
        return ret;
    }

    ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    IpcMsg msg = {
        .type = MT_REQUEST,
        .target = sid,
        .code = code,
        .flag = flag,
        .dataSz = (data == NULL) ? 0 : data->bufferCur - data->bufferBase,
        .data =  (data == NULL) ? NULL : data->bufferBase,
        .offsets =  (data == NULL) ? NULL : data->offsetsBase,
        .spObjNum =  (data == NULL) ? 0 : ((char*)data->offsetsCur - (char*)data->offsetsBase) / sizeof(size_t)
    };
    IpcContent content = {.outMsg = &msg};
    content.flag = (flag == LITEIPC_FLAG_ONEWAY) ? SEND : (SEND | RECV);
    ret = ioctl(context.fd, IPC_SEND_RECV_MSG, &content);
    IpcIoFreeDataBuff(data);
    if (ret < 0) {
        LOG_ERRNO("Liteipc driver ioctl failed.");
        return (errno == ENOENT) ? LITEIPC_ENOENT : LITEIPC_EBADF;
    }

    if (flag != LITEIPC_FLAG_ONEWAY) {
        if (reply != NULL) {
            IpcIoInitFromMsg(reply, content.inMsg);
        }
        *ptr = (uintptr_t)content.inMsg;
    }
    return LITEIPC_OK;
}

int32_t SendReply(const IpcContext* con, void* ipcMsg, IpcIo* reply)
{
    IpcContext context;
    int32_t ret;

    if (ipcMsg == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    ret = CheckIpcIo(reply);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "CheckIpcIo failed.");
        return ret;
    }

    ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    IpcMsg* in = (IpcMsg*)ipcMsg;
    IpcMsg out = {
        .type = MT_REPLY,
        .target.handle = in->taskID,
        .code = in->code,
        .flag = in->flag,
        .timestamp = in->timestamp,
        .dataSz = (reply == NULL) ? 0 : reply->bufferCur - reply->bufferBase,
        .data = (reply == NULL) ? NULL : (void*)reply->bufferBase,
        .offsets = (reply == NULL) ? NULL : reply->offsetsBase,
        .spObjNum = (reply == NULL) ? 0 : ((char*)reply->offsetsCur - (char*)reply->offsetsBase) / sizeof(size_t)
    };
    IpcContent content = {
        .flag = SEND | BUFF_FREE,
        .outMsg = &out,
        .buffToFree = in
    };

    ret = ioctl(context.fd, IPC_SEND_RECV_MSG, &content);
    IpcIoFreeDataBuff(reply);
    RETURN_IF_IPC_IOCTL_FAILED(LITEIPC_EBADF);

    return ret;
}

int32_t FreeBuffer(const IpcContext* con, void* ptr)
{
    IpcContext context;
    int32_t ret;

    if (ptr == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return LITEIPC_EINVAL;
    }

    ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return ret;
    }

    IpcContent content = {
        .flag = BUFF_FREE,
        .buffToFree = (IpcMsg*)ptr
    };
    ret = ioctl(context.fd, IPC_SEND_RECV_MSG, &content);
    RETURN_IF_IPC_IOCTL_FAILED(LITEIPC_EBADF);

    return ret;
}

static void SendFailedReply(IpcMsg* in)
{
    IpcContext context;
    int32_t ret;

    if (in == NULL) {
        LOG(ERROR, "Invalid parameter, null pointer.");
        return;
    }

    ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return;
    }

    IpcMsg out = {
        .type = MT_FAILED_REPLY,
        .target.handle = in->taskID,
        .code = in->code,
        .flag = in->flag,
        .timestamp = in->timestamp,
        .dataSz = 0,
        .data = NULL,
        .offsets = NULL,
        .spObjNum = 0
    };
    IpcContent content = {
        .flag = SEND | BUFF_FREE,
        .outMsg = &out,
        .buffToFree = in
    };

    ret = ioctl(context.fd, IPC_SEND_RECV_MSG, &content);
    if (ret < 0) {
        LOG_ERRNO("Liteipc driver ioctl failed.");
    }
}

typedef struct {
    uint32_t num;
    void* msg;
    IpcIo io;
    IpcMsgHandlerPair* cbs;
} HdlerArg;

static void RemoveDeathCallback(uint32_t handle);
static void* CallbackBatchHandler(void* arg)
{
    pthread_detach(pthread_self());
    HdlerArg* hdlerArg = (HdlerArg*)arg;
    IpcMsg* msg = hdlerArg->msg;
    uint32_t handle = msg->target.token;
    uint32_t i;

    for (i = 0; i < hdlerArg->num; i++) {
        if (hdlerArg->cbs[i].usedFlag == true) {
            (hdlerArg->cbs[i].hdler)(0, hdlerArg->msg, &hdlerArg->io, hdlerArg->cbs[i].arg);
        }
    }
    free(arg);
    if (msg->type == MT_DEATH_NOTIFY) {
        RemoveDeathCallback(handle);
    }
    return NULL;
}

#if (ENABLE_IPC_CB_TIMER == YES)
static struct itimerspec IpcTimeout2Timerspec(uint32_t timeoutMs)
{
    struct itimerspec its;
    uint64_t nanosecs;
    nanosecs = (uint64_t)timeoutMs * NS_PER_MS;
    its.it_value.tv_sec = nanosecs / NS_PER_SEC;
    its.it_value.tv_nsec = nanosecs % NS_PER_SEC;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    return its;
}
#endif

static void GetIpcCallback(IpcMsg* msg, HdlerArg* arg)
{
    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return;
    }
    IpcIoInitFromMsg(&arg->io, msg);
    arg->msg = msg;

    AnonymousApi* node = NULL;
    UTILS_DL_LIST_FOR_EACH_ENTRY(node, &g_ipcCallbackCb.apis, AnonymousApi, list)
    {
        if (node->token == msg->target.token) {
            arg->num = 1;
            arg->cbs = &node->hdlerPair;
#if (ENABLE_IPC_CB_TIMER == YES)
            if ((node->timerId != IPC_INVAILD_TIMER_ID) && (node->mode == RESET_AFTER_USE)) {
                struct itimerspec its = IpcTimeout2Timerspec(node->timeout);
                timer_settime(node->timerId, 0, &its, 0);
            }
#endif
            (void)pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
            return;
        }
    }
    arg->num = 0;
    arg->cbs = NULL;
    (void)pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
}

static void GetDeathCallback(IpcMsg* msg, HdlerArg* arg)
{
    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return;
    }
    IpcIoInitFromMsg(&arg->io, msg);
    arg->msg = msg;

    Testament* node = NULL;
    UTILS_DL_LIST_FOR_EACH_ENTRY(node, &g_ipcCallbackCb.testaments, Testament, list)
    {
        if (node->handle == msg->target.token) {
            node->isCallbackRuning = true;
            arg->num = MAX_DEATHCB_PER_SVC;
            arg->cbs = node->hdlerPairs;
            (void)pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
            return;
        }
    }
    arg->num = 0;
    arg->cbs = NULL;
    (void)pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
}

static void* CallbackDispatch(void* arg)
{
    IpcContext context;
    int32_t ret = GetLiteIpcContext(0, &context);
    if (ret != LITEIPC_OK) {
        LOG(ERROR, "GetLiteIpcContext failed.");
        return (void*)(intptr_t)LITEIPC_EBADF;
    }

    ret = ioctl(context.fd, IPC_SET_IPC_THREAD, 0);
    RETURN_IF_IPC_IOCTL_FAILED((void*)(intptr_t)LITEIPC_EBADF);
    g_ipcCallbackCb.handleId = ret;
    g_ipcCallbackCb.threadWorking = true;

    while (1) {
        IpcContent content = {.flag = RECV};
        ret = ioctl(context.fd, IPC_SEND_RECV_MSG, &content);
        if (ret < 0) {
            continue;
        }

        HdlerArg* tArg = (HdlerArg*)malloc(sizeof(HdlerArg));
        if (tArg == NULL) {
            goto ERROR_MALLOC;
        }

        switch (content.inMsg->type) {
            case MT_DEATH_NOTIFY:
                GetDeathCallback(content.inMsg, tArg);
                break;
            case MT_REQUEST:
                GetIpcCallback(content.inMsg, tArg);
                break;
            default:
                LOG(ERROR, "Callback thread received an unrecognized message.(type=%d)", content.inMsg->type);
                goto ERROR_MSG;
        }

        if (tArg->num == 0) {
            goto ERROR_MSG;
        }
        pthread_t tid;
        ret = pthread_create(&tid, NULL, CallbackBatchHandler, tArg);
        if (ret == 0) {
            continue;
        }
        LOG_ERRNO("Create handle thread failed.");
ERROR_MSG:
        free(tArg);
ERROR_MALLOC:
        if ((content.inMsg->type == MT_REQUEST) && (content.inMsg->flag == LITEIPC_FLAG_DEFAULT)) {
            SendFailedReply(content.inMsg);
        } else {
            (void)FreeBuffer(NULL, content.inMsg);
        }
    }
    g_ipcCallbackCb.threadWorking = false;
}

static int32_t StartCallbackDispatch()
{
    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

    pthread_t tid;
    int32_t ret = pthread_create(&tid, &threadAttr, CallbackDispatch, NULL);
    if (ret != 0) {
        LOG_ERRNO("Create callback dispatch thread failed.");
        return LITEIPC_EINTNL;
    }

    struct timespec spark, now;
    clock_gettime(CLOCK_REALTIME, &spark);
    thrd_yield();
    while (!g_ipcCallbackCb.threadWorking) {
        clock_gettime(CLOCK_REALTIME, &now);
        if (now.tv_sec - spark.tv_sec > 1) {
            LOG(ERROR, "Wait callback thread starting timeout.");
            return LITEIPC_EINTNL;
        }
        thrd_yield();
    }
    return LITEIPC_OK;
}

#if (ENABLE_IPC_CB_TIMER == YES)
static void TimeoutHandler(int signo, void *arg)
{
    AnonymousApi* node = (AnonymousApi*)arg;
    SvcIdentity sid = {
        .handle = g_ipcCallbackCb.handleId,
        .token = node->token
    };
    UnRegisteIpcCallback(sid);
}

int32_t StartIpcCbTimer(uint32_t mode, uint32_t timeoutMs, AnonymousApi* node, timer_t* timerId)
{
    int ret;
    struct itimerspec its;
    struct sigevent sev;
    struct sigaction sa;

    sa.sa_flags = 0;
    sa.sa_handler = (TimerHandler)TimeoutHandler;
    sigemptyset(&sa.sa_mask);
    ret = sigaction(SIGUSR1, &sa, NULL);
    if (ret != 0) {
        LOG(ERROR, "sigaction failed.");
        return LITEIPC_EINTNL;
    }

    /* Create the timer */
    memset_s(&sev, sizeof(struct sigevent), 0, sizeof(struct sigevent));
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGUSR1;
    sev.sigev_value.sival_ptr = node;
    ret = timer_create(CLOCK_REALTIME, &sev, timerId);
    if (ret != 0) {
        LOG(ERROR, "timer_create failed.");
        return LITEIPC_EINTNL;
    }

    /* Start the timer */
    its = IpcTimeout2Timerspec(timeoutMs);
    ret = timer_settime(*timerId, 0, &its, NULL);
    if (ret != 0) {
        LOG(ERROR, "timer_settime failed.");
        timer_delete(*timerId);
        return LITEIPC_EINTNL;
    }

    return LITEIPC_OK;
}
#endif

int32_t RegisteIpcCallback(IpcMsgHandler func, uint32_t mode, uint32_t timeoutMs, SvcIdentity* sid, void* arg)
{
#if (ENABLE_IPC_CB_TIMER == YES)
    timer_t timerId = NULL;
#endif
    if ((func == NULL) || (sid == NULL) || (mode > RESET_AFTER_USE) || (timeoutMs < IPC_TIMEOUT_MIN)) {
        return LITEIPC_EINVAL;
    }
    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return LITEIPC_EINTNL;
    }

    int ret = LITEIPC_OK;
    /* Start callback thread if it's not working */
    if (!g_ipcCallbackCb.threadWorking) {
        ret = StartCallbackDispatch();
        if (ret != LITEIPC_OK) {
            goto ERROR;
        }
    }

    AnonymousApi* node = (AnonymousApi*)malloc(sizeof(AnonymousApi));
    if (node == NULL) {
        LOG(ERROR, "Malloc failed.(size=%u)", sizeof(AnonymousApi));
        ret = LITEIPC_EINTNL;
        goto ERROR;
    }
    node->token = (uint32_t)(uintptr_t)node;
    node->hdlerPair.usedFlag = true;
    node->hdlerPair.hdler = func;
    node->hdlerPair.arg = arg;
#if (ENABLE_IPC_CB_TIMER == YES)
    /* if timeout is not forever, create and start a cb timer */
    if (timeoutMs != IPC_WAIT_FOREVER) {
        ret = StartIpcCbTimer(mode, timeoutMs, node, &timerId);
        if (ret != LITEIPC_OK) {
            LOG(ERROR, "StartIpcCbTimer failed.");
            free(node);
            goto ERROR;
        }
        node->timerId = timerId;
    } else {
        node->timerId = IPC_INVAILD_TIMER_ID;
    }
    node->mode = mode;
    node->timeout = timeoutMs;
#endif
    UtilsListAdd(&g_ipcCallbackCb.apis, &node->list);
    sid->token = node->token;
    sid->handle = g_ipcCallbackCb.handleId;
ERROR:
    pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
    return ret;
}

int32_t UnRegisteIpcCallback(SvcIdentity sid)
{
    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return LITEIPC_EINTNL;
    }

    AnonymousApi* node = NULL;
    AnonymousApi* next = NULL;
    if (sid.handle != g_ipcCallbackCb.handleId) {
        LOG(ERROR, "Not a ipc callback sid.");
        pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
        return LITEIPC_EINVAL;
    }
    UTILS_DL_LIST_FOR_EACH_ENTRY_SAFE(node, next, &g_ipcCallbackCb.apis, AnonymousApi, list)
    {
        if (node->token == sid.token) {
#if (ENABLE_IPC_CB_TIMER == YES)
            if (node->timerId != IPC_INVAILD_TIMER_ID) {
                timer_delete(node->timerId);
            }
#endif
            UtilsListDelete(&node->list);
            free(node);
            pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
            return LITEIPC_OK;
        }
    }

    LOG(ERROR, "Input sid not exist.");
    pthread_mutex_unlock(&g_ipcCallbackCb.mutex);

    return LITEIPC_OK;
}

static inline uint32_t SetDeathHandlerPair(Testament* node, uint32_t index, IpcMsgHandler func, void* arg)
{
    node->hdlerPairs[index].usedFlag = true;
    node->hdlerPairs[index].hdler = func;
    node->hdlerPairs[index].arg = arg;
    return index;
}

int32_t RegisteDeathCallback(const IpcContext* context, SvcIdentity sid, IpcMsgHandler func, void* arg, uint32_t* cbId)
{
    int i;
    int ret = LITEIPC_OK;
    Testament* node = NULL;

    if ((func == NULL) || (cbId == NULL)) {
        return LITEIPC_EINVAL;
    }

    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return LITEIPC_EINTNL;
    }

    /* Start callback thread if it's not working */
    if (!g_ipcCallbackCb.threadWorking && (ret = StartCallbackDispatch()) != LITEIPC_OK) {
        ret = LITEIPC_EINTNL;
        goto UNLOCK_RETURN;
    }

    UTILS_DL_LIST_FOR_EACH_ENTRY(node, &g_ipcCallbackCb.testaments, Testament, list)
    {
        if (node->handle != sid.handle) {
            continue;
        }

        if (node->size == MAX_DEATHCB_PER_SVC) {
            LOG(ERROR, "Reach max num on this svc:%d", sid.handle);
            ret = LITEIPC_EINTNL;
            goto UNLOCK_RETURN;
        }
        for (i = 0; i < MAX_DEATHCB_PER_SVC; i++) {
            if (node->hdlerPairs[i].usedFlag == false) {
                node->size++;
                *cbId = SetDeathHandlerPair(node, i, func, arg);
                break;
            }
        }
        goto UNLOCK_RETURN;
    }
    node = (Testament*)malloc(sizeof(Testament));
    if (node == NULL) {
        LOG(ERROR, "Malloc failed.(size=%u)", sizeof(Testament));
        ret = LITEIPC_ENOMEM;
        goto UNLOCK_RETURN;
    }
    (void)memset_s(node, sizeof(Testament), 0, sizeof(Testament));
    node->handle = sid.handle;
    node->size = 1;
    *cbId = SetDeathHandlerPair(node, 0, func, arg);
    UtilsListAdd(&g_ipcCallbackCb.testaments, &node->list);

UNLOCK_RETURN:
    pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
    return ret;
}

int32_t UnRegisteDeathCallback(SvcIdentity sid, uint32_t cbId)
{
    Testament* node = NULL;
    Testament* next = NULL;
    if (cbId >= MAX_DEATHCB_PER_SVC) {
        LOG(ERROR, "Wrong cbId:%u.", cbId);
        return LITEIPC_EINVAL;
    }
    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return LITEIPC_EINTNL;
    }
    UTILS_DL_LIST_FOR_EACH_ENTRY_SAFE(node, next, &g_ipcCallbackCb.testaments, Testament, list)
    {
        if (node->handle == sid.handle) {
            if ((node->isCallbackRuning == false) && (node->hdlerPairs[cbId].usedFlag == true)) {
                node->hdlerPairs[cbId].usedFlag = false;
                node->size--;
                if (node->size == 0) {
                    UtilsListDelete(&node->list);
                    free(node);
                }
            }
            pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
            return LITEIPC_OK;
        }
    }
    LOG(ERROR, "Input sid not exist.");
    pthread_mutex_unlock(&g_ipcCallbackCb.mutex);

    return LITEIPC_OK;
}

static void RemoveDeathCallback(uint32_t handle)
{
    Testament* node = NULL;
    Testament* next = NULL;

    if (pthread_mutex_lock(&g_ipcCallbackCb.mutex) != 0) {
        LOG_ERRNO("Get callback mutex failed.");
        return;
    }
    UTILS_DL_LIST_FOR_EACH_ENTRY_SAFE(node, next, &g_ipcCallbackCb.testaments, Testament, list)
    {
        if (node->handle == handle) {
            UtilsListDelete(&node->list);
            free(node);
            break;
        }
    }
    pthread_mutex_unlock(&g_ipcCallbackCb.mutex);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
