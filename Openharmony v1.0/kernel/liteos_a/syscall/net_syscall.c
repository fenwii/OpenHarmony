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

#include "los_syscall.h"
#include "los_process_pri.h"
#include "lwip/sockets.h"
#include <stdlib.h>
#include "los_vm_map.h"
#include "user_copy.h"
#include "fs_file.h"

#ifdef LOSCFG_NET_LWIP_SACK

#define SOCKET_U2K(s) do { s = GetAssociatedSystemFd(s); } while (0)
#define SOCKET_K2U(s) \
    do { \
        int fd = AllocAndAssocProcessFd(s, MIN_START_FD); \
        if (fd == -1) { \
            closesocket(s); \
            set_errno(EMFILE); \
            s = -EMFILE; \
        } else { \
            s = fd; \
        } \
    } while (0)

#define CHECK_ASPACE(ptr, len, ...) \
    do { \
        if (ptr != NULL && len != 0) { \
            if (!LOS_IsUserAddressRange((VADDR_T)ptr, len)) { \
                set_errno(EFAULT); \
                __VA_ARGS__; \
                return -get_errno(); \
            } \
            if (CheckRegion(OsCurrProcessGet()->vmSpace, (VADDR_T)ptr, len) == -1) { \
                set_errno(EFAULT); \
                __VA_ARGS__; \
                return -get_errno(); \
            } \
        } \
    } while (0)

static int CheckRegion(const LosVmSpace *space, VADDR_T ptr, size_t len)
{
    LosVmMapRegion *region = LOS_RegionFind((LosVmSpace *)space, ptr);
    if (region == NULL) {
        return -1;
    }
    if (ptr + len <= region->range.base + region->range.size) {
        return 0;
    }
    return CheckRegion(space, region->range.base + region->range.size,
                       (ptr + len) - (region->range.base + region->range.size));
}

static void *DupUserMem(const void *ptr, size_t len, int needCopy)
{
    void *p = malloc(len);
    if (p == NULL) {
        set_errno(ENOMEM);
        return NULL;
    }
    if (needCopy && LOS_ArchCopyFromUser(p, ptr, len) != 0) {
        free(p);
        set_errno(EFAULT);
        return NULL;
    }
    return p;
}

#define LEN(ptr) ((ptr) ? *(ptr) : 0)

#define DUP_FROM_USER_(ptr, size, copy, ...) \
    __typeof(ptr) ptr##bak = ptr; \
    if (ptr != NULL && (size) != 0) { \
        ptr = DupUserMem(ptr, size, copy); \
        if (ptr == NULL) { \
            ptr = ptr##bak; \
            __VA_ARGS__; \
            return -get_errno(); \
        } \
    }

#define DUP_FROM_USER(ptr, size, ...) \
    DUP_FROM_USER_(ptr, size, 1, ##__VA_ARGS__)

#define DUP_FROM_USER_NOCOPY(ptr, size, ...) \
    DUP_FROM_USER_(ptr, size, 0, ##__VA_ARGS__)

#define DUP_TO_USER(ptr, size, ...) \
    if (ptr != NULL && (size) != 0) { \
        if (LOS_ArchCopyToUser(ptr##bak, ptr, size) != 0) { \
            set_errno(EFAULT); \
            __VA_ARGS__; \
            return -get_errno(); \
        } \
    }

#define FREE_DUP(ptr) \
    if (ptr != ptr##bak) { \
        free((void*)ptr); \
        ptr = ptr##bak; \
    }

#define CPY_FROM_USER(ptr) \
    __typeof(*ptr) ptr##cpy = {0}, *ptr##bak = ptr; \
    if (ptr != NULL) { \
        if (LOS_ArchCopyFromUser((void*)&ptr##cpy, ptr, sizeof(*ptr)) != 0) { \
            set_errno(EFAULT); \
            return -get_errno(); \
        } \
        ptr = &ptr##cpy; \
    }

#define CPY_TO_USER(ptr, ...) \
    if (ptr != NULL) { \
        if (LOS_ArchCopyToUser(ptr##bak, ptr, sizeof(*ptr)) != 0) { \
            set_errno(EFAULT); \
            __VA_ARGS__; \
            return -get_errno(); \
        } \
    }

/** Macros for sendmsg and recvmsg */

#define CONST_CAST(ptr) ((__typeof(ptr##_NONCONST))ptr)

#define CHECK_FIELD_ASPACE(ptr, field, len) \
    do { \
        if (ptr != NULL) { \
            CHECK_ASPACE(ptr->field, len); \
        } \
    } while (0)

#define CHECK_ARRAY_FIELD_ASPACE(ptr, arr, arrlen, field, len, ...) \
    do { \
        if (ptr != NULL && ptr->arr != NULL) { \
            for (size_t i = 0; i < arrlen; i++) { \
                CHECK_ASPACE(ptr->arr[i].field, ptr->arr[i].len, ##__VA_ARGS__); \
            } \
        } \
    } while (0)

#define DUP_FIELD_FROM_USER_(ptr, field, size, copy, ...) \
    if (ptr != NULL && ptr->field != NULL && (size) != 0) { \
        CONST_CAST(ptr)->field = DupUserMem(ptr->field, size, copy); \
        if (ptr->field == NULL) { \
            __VA_ARGS__; \
            return -get_errno(); \
        } \
    }

#define DUP_FIELD_FROM_USER(ptr, field, size, ...) \
    DUP_FIELD_FROM_USER_(ptr, field, size, 1, ##__VA_ARGS__)

#define DUP_FIELD_FROM_USER_NOCOPY(ptr, field, size, ...) \
    DUP_FIELD_FROM_USER_(ptr, field, size, 0, ##__VA_ARGS__)

#define DUP_ARRAY_FIELD_FROM_USER_(ext, ptr, arr, arrlen, field, len, ...) \
    /* backup the arr to ptr##arr */ \
    __typeof(*ptr##_NONCONST) ptr##arr##cpy = ptr##cpybak, ptr##arr##cpybak = ptr##cpybak; \
    __typeof(ptr##_NONCONST) ptr##arr = ptr ? &ptr##arr##cpy : NULL, ptr##arr##_NONCONST = NULL; \
    DUP_FIELD_FROM_USER(ptr##arr, arr, arrlen * sizeof(ptr->arr[0]), ##__VA_ARGS__); \
    if (ptr != NULL && ptr->arr != NULL) { \
        size_t i = 0; \
        for (; i < arrlen; i++) { \
            DUP_FIELD_FROM_USER##ext(ptr, arr[i].field, ptr->arr[i].len, break); \
        } \
        if (i != arrlen) { \
            FREE_DUP_ARRAY_FIELD(ptr, arr, i, field); \
            __VA_ARGS__; \
            return -get_errno(); \
        } \
    }

#define DUP_ARRAY_FIELD_FROM_USER(ptr, arr, arrlen, field, len, ...) \
    DUP_ARRAY_FIELD_FROM_USER_(, ptr, arr, arrlen, field, len, ##__VA_ARGS__)

#define DUP_ARRAY_FIELD_FROM_USER_NOCOPY(ptr, arr, arrlen, field, len, ...) \
    DUP_ARRAY_FIELD_FROM_USER_(_NOCOPY, ptr, arr, arrlen, field, len, ##__VA_ARGS__)

#define FREE_DUP_FIELD(ptr, field) \
    if (ptr != NULL && ptr->field != ptr##cpybak.field) { \
        free((void*)ptr->field); \
        CONST_CAST(ptr)->field = ptr##cpybak.field; \
    }

#define FREE_DUP_ARRAY_FIELD(ptr, arr, arrlen, field) \
    /* use and free the backuped arr in ptr##arr */ \
    if (ptr != NULL && ptr->arr != NULL && arrlen != 0) { \
        __typeof(ptr##cpybak.arr) tmp = ptr##cpybak.arr; \
        ptr##cpybak.arr = ptr##arr->arr; \
        for (size_t j = 0; j < arrlen; j++) { \
            FREE_DUP_FIELD(ptr, arr[j].field); \
        } \
        ptr##cpybak.arr = tmp; \
    } \
    FREE_DUP_FIELD(ptr##arr, arr);

#define CPY_FROM_CONST_USER(NonConstType, ptr) \
    CPY_FROM_USER(ptr); \
    NonConstType *ptr##_NONCONST = NULL, ptr##cpybak = ptr##cpy; \
    (void)ptr##bak;

#define CPY_FROM_NONCONST_USER(ptr) \
    CPY_FROM_USER(ptr); \
    __typeof(*ptr) *ptr##_NONCONST = NULL, ptr##cpybak = ptr##cpy;

#define DUP_FIELD_TO_USER(ptr, field, size, ...) \
    if (ptr != NULL && ptr->field != NULL && (size) != 0) { \
        if (LOS_ArchCopyToUser(ptr##cpybak.field, ptr->field, size) != 0 || \
            LOS_ArchCopyToUser(&ptr##bak->field, &ptr##cpybak.field, sizeof(ptr##cpybak.field)) != 0) { \
            set_errno(EFAULT); \
            __VA_ARGS__; \
            return -get_errno(); \
        } \
    }

#define DUP_ARRAY_FIELD_TO_USER(ptr, arr, arrlen, field, len, ...) \
    /* use the backuped arr from ptr##arr */ \
    if (ptr != NULL && ptr->arr != NULL) { \
        __typeof(ptr##cpybak.arr) tmp = ptr##cpybak.arr; \
        __typeof(ptr##bak) tmp2 = ptr##bak; \
        ptr##cpybak.arr = ptr##arr->arr; \
        ptr##arr->arr = tmp; \
        ptr##bak = ptr##arr; \
        for (size_t i = 0; i < arrlen; i++) { \
            DUP_FIELD_TO_USER(ptr, arr[i].field, ptr->arr[i].len, ##__VA_ARGS__); \
        } \
        ptr##bak = tmp2; \
        ptr##arr->arr = ptr##cpybak.arr; \
        ptr##cpybak.arr = tmp; \
    }

int SysSocket(int domain, int type, int protocol)
{
    int ret;

    ret = socket(domain, type, protocol);
    if (ret == -1) {
        return -get_errno();
    }

    SOCKET_K2U(ret);
    return ret;
}

int SysBind(int s, const struct sockaddr *name, socklen_t namelen)
{
    int ret;

    SOCKET_U2K(s);
    CHECK_ASPACE(name, namelen);

    DUP_FROM_USER(name, namelen);
    ret = bind(s, name, namelen);
    FREE_DUP(name);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

int SysConnect(int s, const struct sockaddr *name, socklen_t namelen)
{
    int ret;

    SOCKET_U2K(s);
    CHECK_ASPACE(name, namelen);

    DUP_FROM_USER(name, namelen);
    ret = connect(s, name, namelen);
    FREE_DUP(name);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

int SysListen(int sockfd, int backlog)
{
    int ret;

    SOCKET_U2K(sockfd);
    ret = listen(sockfd, backlog);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

int SysAccept(int socket, struct sockaddr *address,
              socklen_t *addressLen)
{
    int ret;

    SOCKET_U2K(socket);

    CHECK_ASPACE(addressLen, sizeof(socklen_t));
    CPY_FROM_USER(addressLen);

    CHECK_ASPACE(address, LEN(addressLen));
    DUP_FROM_USER_NOCOPY(address, LEN(addressLen));

    ret = accept(socket, address, addressLen);
    if (ret == -1) {
        FREE_DUP(address);
        return -get_errno();
    }

    CPY_TO_USER(addressLen, close(ret); FREE_DUP(address));
    DUP_TO_USER(address, LEN(addressLen), close(ret); FREE_DUP(address));
    FREE_DUP(address);

    SOCKET_K2U(ret);
    return ret;
}

int SysGetSockName (int s, struct sockaddr *name, socklen_t *namelen)
{
    int ret;

    SOCKET_U2K(s);

    CHECK_ASPACE(namelen, sizeof(socklen_t));
    CPY_FROM_USER(namelen);

    CHECK_ASPACE(name, LEN(namelen));
    DUP_FROM_USER_NOCOPY(name, LEN(namelen));

    ret = getsockname(s, name, namelen);
    if (ret == -1) {
        FREE_DUP(name);
        return -get_errno();
    }

    CPY_TO_USER(namelen, FREE_DUP(name));
    DUP_TO_USER(name, LEN(namelen), FREE_DUP(name));
    FREE_DUP(name);
    return ret;
}

int SysGetPeerName (int s, struct sockaddr *name, socklen_t *namelen)
{
    int ret;

    SOCKET_U2K(s);

    CHECK_ASPACE(namelen, sizeof(socklen_t));
    CPY_FROM_USER(namelen);

    CHECK_ASPACE(name, LEN(namelen));
    DUP_FROM_USER_NOCOPY(name, LEN(namelen));

    ret = getpeername(s, name, namelen);
    if (ret == -1) {
        FREE_DUP(name);
        return -get_errno();
    }

    CPY_TO_USER(namelen, FREE_DUP(name));
    DUP_TO_USER(name, LEN(namelen), FREE_DUP(name));
    FREE_DUP(name);
    return ret;
}

ssize_t SysSend(int s, const void *dataptr, size_t size, int flags)
{
    int ret;

    SOCKET_U2K(s);
    CHECK_ASPACE(dataptr, size);

    DUP_FROM_USER(dataptr, size);
    ret = send(s, dataptr, size, flags);
    FREE_DUP(dataptr);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

ssize_t SysSendTo(int s, const void *dataptr, size_t size, int flags,
                  const struct sockaddr *to, socklen_t tolen)
{
    int ret;

    SOCKET_U2K(s);
    CHECK_ASPACE(dataptr, size);
    CHECK_ASPACE(to, tolen);

    DUP_FROM_USER(dataptr, size);
    DUP_FROM_USER(to, tolen, FREE_DUP(dataptr););
    ret = sendto(s, dataptr, size, flags, to, tolen);
    FREE_DUP(dataptr);
    FREE_DUP(to);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

ssize_t SysRecv(int socket, void *buffer, size_t length, int flags)
{
    int ret;

    SOCKET_U2K(socket);
    CHECK_ASPACE(buffer, length);

    DUP_FROM_USER_NOCOPY(buffer, length);
    ret = recv(socket, buffer, length, flags);
    if (ret == -1) {
        FREE_DUP(buffer);
        return -get_errno();
    }

    DUP_TO_USER(buffer, ret, FREE_DUP(buffer));
    FREE_DUP(buffer);
    return ret;
}

ssize_t SysRecvFrom(int socket, void *buffer, size_t length,
                    int flags, struct sockaddr *address,
                    socklen_t *addressLen)
{
    int ret;

    SOCKET_U2K(socket);
    CHECK_ASPACE(buffer, length);

    CHECK_ASPACE(addressLen, sizeof(socklen_t));
    CPY_FROM_USER(addressLen);

    CHECK_ASPACE(address, LEN(addressLen));
    DUP_FROM_USER_NOCOPY(address, LEN(addressLen));

    DUP_FROM_USER_NOCOPY(buffer, length, FREE_DUP(address));
    ret = recvfrom(socket, buffer, length, flags, address, addressLen);
    if (ret == -1) {
        FREE_DUP(address);
        FREE_DUP(buffer);
        return -get_errno();
    }

    CPY_TO_USER(addressLen, FREE_DUP(address); FREE_DUP(buffer));
    DUP_TO_USER(address, LEN(addressLen), FREE_DUP(address); FREE_DUP(buffer));
    DUP_TO_USER(buffer, ret, FREE_DUP(address); FREE_DUP(buffer));
    FREE_DUP(address);
    FREE_DUP(buffer);
    return ret;
}

int SysShutdown(int socket, int how)
{
    int ret;

    SOCKET_U2K(socket);
    ret = shutdown(socket, how);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

int SysSetSockOpt(int socket, int level, int optName,
                  const void *optValue, socklen_t optLen)
{
    int ret;

    SOCKET_U2K(socket);
    CHECK_ASPACE(optValue, optLen);

    DUP_FROM_USER(optValue, optLen);
    ret = setsockopt(socket, level, optName, optValue, optLen);
    FREE_DUP(optValue);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

int SysGetSockOpt(int sockfd, int level, int optName,
                  void *optValue, socklen_t *optLen)
{
    int ret;

    SOCKET_U2K(sockfd);

    CHECK_ASPACE(optLen, sizeof(socklen_t));
    CPY_FROM_USER(optLen);

    CHECK_ASPACE(optValue, LEN(optLen));
    DUP_FROM_USER_NOCOPY(optValue, LEN(optLen));

    ret = getsockopt(sockfd, level, optName, optValue, optLen);
    if (ret == -1) {
        FREE_DUP(optValue);
        return -get_errno();
    }

    CPY_TO_USER(optLen, FREE_DUP(optValue));
    DUP_TO_USER(optValue, LEN(optLen), FREE_DUP(optValue));
    FREE_DUP(optValue);
    return ret;
}

ssize_t SysSendMsg(int s, const struct msghdr *message, int flags)
{
    int ret;

    SOCKET_U2K(s);

    CHECK_ASPACE(message, sizeof(struct msghdr));
    CPY_FROM_CONST_USER(struct msghdr, message);

    if (message && message->msg_iovlen > IOV_MAX) {
        set_errno(EMSGSIZE);
        return -get_errno();
    }

    CHECK_FIELD_ASPACE(message, msg_name, message->msg_namelen);
    CHECK_FIELD_ASPACE(message, msg_iov, message->msg_iovlen * sizeof(struct iovec));
    CHECK_FIELD_ASPACE(message, msg_control, message->msg_controllen);

    DUP_FIELD_FROM_USER(message, msg_iov, message->msg_iovlen * sizeof(struct iovec));
    CHECK_ARRAY_FIELD_ASPACE(message, msg_iov, message->msg_iovlen, iov_base, iov_len,
            FREE_DUP_FIELD(message, msg_iov));
    DUP_FIELD_FROM_USER(message, msg_name, message->msg_namelen,
            FREE_DUP_FIELD(message, msg_iov));
    DUP_FIELD_FROM_USER(message, msg_control, message->msg_controllen,
            FREE_DUP_FIELD(message, msg_iov);
            FREE_DUP_FIELD(message, msg_name));
    DUP_ARRAY_FIELD_FROM_USER(message, msg_iov, message->msg_iovlen, iov_base, iov_len,
            FREE_DUP_FIELD(message, msg_control);
            FREE_DUP_FIELD(message, msg_iov);
            FREE_DUP_FIELD(message, msg_name));
    ret = sendmsg(s, message, flags);
    FREE_DUP_ARRAY_FIELD(message, msg_iov, message->msg_iovlen, iov_base);
    FREE_DUP_FIELD(message, msg_control);
    FREE_DUP_FIELD(message, msg_iov);
    FREE_DUP_FIELD(message, msg_name);
    if (ret == -1) {
        return -get_errno();
    }

    return ret;
}

ssize_t SysRecvMsg(int s, struct msghdr *message, int flags)
{
    int ret;

    SOCKET_U2K(s);

    CHECK_ASPACE(message, sizeof(struct msghdr));
    CPY_FROM_NONCONST_USER(message);

    if (message && message->msg_iovlen > IOV_MAX) {
        set_errno(EMSGSIZE);
        return -get_errno();
    }

    CHECK_FIELD_ASPACE(message, msg_name, message->msg_namelen);
    CHECK_FIELD_ASPACE(message, msg_iov, message->msg_iovlen * sizeof(struct iovec));
    CHECK_FIELD_ASPACE(message, msg_control, message->msg_controllen);

    DUP_FIELD_FROM_USER(message, msg_iov, message->msg_iovlen * sizeof(struct iovec));
    CHECK_ARRAY_FIELD_ASPACE(message, msg_iov, message->msg_iovlen, iov_base, iov_len,
            FREE_DUP_FIELD(message, msg_iov));
    DUP_FIELD_FROM_USER_NOCOPY(message, msg_name, message->msg_namelen,
            FREE_DUP_FIELD(message, msg_iov));
    DUP_FIELD_FROM_USER_NOCOPY(message, msg_control, message->msg_controllen,
            FREE_DUP_FIELD(message, msg_iov);
            FREE_DUP_FIELD(message, msg_name));
    DUP_ARRAY_FIELD_FROM_USER_NOCOPY(message, msg_iov, message->msg_iovlen, iov_base, iov_len,
            FREE_DUP_FIELD(message, msg_control);
            FREE_DUP_FIELD(message, msg_iov);
            FREE_DUP_FIELD(message, msg_name));
    ret = recvmsg(s, message, flags);
    if (ret == -1) {
        goto OUT;
    }

    CPY_TO_USER(message, ret = -1; goto OUT);
    DUP_FIELD_TO_USER(message, msg_control, message->msg_controllen, ret = -1; goto OUT);
    DUP_FIELD_TO_USER(message, msg_iov, message->msg_iovlen * sizeof(struct iovec), ret = -1; goto OUT);
    DUP_FIELD_TO_USER(message, msg_name, message->msg_namelen, ret = -1; goto OUT);
    DUP_ARRAY_FIELD_TO_USER(message, msg_iov, message->msg_iovlen, iov_base, iov_len, ret = -1; goto OUT);
OUT:
    FREE_DUP_ARRAY_FIELD(message, msg_iov, message->msg_iovlen, iov_base);
    FREE_DUP_FIELD(message, msg_control);
    FREE_DUP_FIELD(message, msg_iov);
    FREE_DUP_FIELD(message, msg_name);
    return (ret == -1) ? -get_errno() : ret;
}

#endif
