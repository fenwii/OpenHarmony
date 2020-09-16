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

#ifndef _LOS_SIGNAL_H
#define _LOS_SIGNAL_H

#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <signal.h>
#include "los_event.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define LOS_BIT_SET(val, bit) ((val) = (val) | (1ULL << (UINT32)(bit)))
#define LOS_BIT_CLR(val, bit) ((val) = (val) & ~(1ULL << (UINT32)(bit)))
#define LOS_IS_BIT_SET(val, bit) (bool)((((val) >> (UINT32)(bit)) & 1ULL))

#define OS_SYSCALL_SET_CPSR(regs, cpsr) (*((unsigned long *)((UINTPTR)(regs) - 4)) = (cpsr))
#define OS_SYSCALL_SET_SR(regs, cpsr) (*((unsigned long *)((UINTPTR)(regs))) = (cpsr))
#define OS_SYSCALL_GET_CPSR(regs) (*((unsigned long *)((UINTPTR)(regs) - 4)))
#define SIG_STOP_VISIT 1

#define OS_KERNEL_KILL_PERMISSION 0U
#define OS_USER_KILL_PERMISSION   3U

#define OS_RETURN_IF(expr, errcode) \
    if ((expr)) {                   \
        return errcode;             \
    }

#define OS_RETURN_IF_VOID(expr) \
    if ((expr)) {               \
        return;                 \
    }
#define OS_GOTO_EXIT_IF(expr, errcode) \
    if (expr) {                        \
        ret = errcode;                 \
        goto EXIT;                     \
    }
#define OS_GOTO_EXIT_IF_ONLY(expr) \
    if (expr) {                    \
        goto EXIT;                 \
    }

#define OS_RETURN_VOID_IF_NULL(pPara) \
    if (NULL == (pPara)) {            \
        return;                       \
    }
#define OS_RETURN_IF_NULL(pPara) \
    if (NULL == (pPara)) {       \
        return (-EINVAL);          \
    }

#define OS_GOTO_EXIT_IF_NULL(pPara) \
    if (NULL == (pPara)) {          \
        ret = -EINVAL;              \
        goto EXIT;                  \
    }

typedef void (*sa_sighandler_t)(int);
typedef void (*sa_siginfoaction_t)(int, siginfo_t *, void *);

#define SIGNO2SET(s) ((sigset_t)1ULL << (s))
#define NULL_SIGNAL_SET ((sigset_t)0ULL)
#define FULL_SIGNAL_SET ((sigset_t)~0ULL)

static inline int GOOD_SIGNO(unsigned int sig)
{
    return (sig < _NSIG) ? 1 : 0;
}

#define MAX_SIG_ARRAY_IN_MUSL 128

typedef struct {
    unsigned long sig[MAX_SIG_ARRAY_IN_MUSL / sizeof(unsigned long)];
} sigset_t_l;

typedef struct sigaction sigaction_t;

struct sigactq {
    struct sigactq *flink; /* Forward link */
    sigaction_t act;       /* Sigaction data */
    uint8_t signo;         /* Signal associated with action */
};
typedef struct sigactq sigactq_t;

struct sq_entry_s {
    struct sq_entry_s *flink;
};
typedef struct sq_entry_s sq_entry_t;

struct sigpendq {
    struct sigpendq *flink; /* Forward link */
    siginfo_t info;         /* Signal information */
    uint8_t type;           /* (Used to manage allocations) */
};
typedef struct sigpendq sigpendq_t;

struct sq_queue_s {
    sq_entry_t *head;
    sq_entry_t *tail;
};
typedef struct sq_queue_s sq_queue_t;

#define TASK_IRQ_CONTEXT \
        unsigned int R0;     \
        unsigned int R1;     \
        unsigned int R2;     \
        unsigned int R3;     \
        unsigned int R12;    \
        unsigned int USP;    \
        unsigned int ULR;    \
        unsigned int CPSR;   \
        unsigned int PC;

typedef struct {
    TASK_IRQ_CONTEXT
} TaskIrqDataSize;

typedef struct {
    TASK_IRQ_CONTEXT
    unsigned int R7;
    unsigned int count;
} sig_switch_context;

typedef struct {
    sigset_t sigFlag;
    sigset_t sigPendFlag;
    sigset_t sigprocmask; /* Signals that are blocked            */
    sq_queue_t sigactionq;
    LOS_DL_LIST waitList;
    sigset_t sigwaitmask; /* Waiting for pending signals         */
    siginfo_t sigunbinfo; /* Signal info when task unblocked     */
    sig_switch_context context;
} sig_cb;

#define SIGEV_THREAD_ID 4

int sys_sigqueue(pid_t, int, const union sigval);
int sys_sigpending(sigset_t *);
int sys_rt_sigtimedwait(const sigset_t *mask, siginfo_t *si, const struct timespec *ts, size_t sigsetsize);
int sys_sigsuspend(const sigset_t *);
int OsKillLock(pid_t pid, int sig);
int OsSigAction(int sig, const sigaction_t *act, sigaction_t *oact);
int OsSigprocMask(int how, const sigset_t_l *set, sigset_t_l *oldset);
int OsPthreadKill(UINT32 tid, int signo);
int OsSigEmptySet(sigset_t *);
int OsSigAddSet(sigset_t *, int);
int OsSigIsMember(const sigset_t *, int);
void OsSaveSignalContext(unsigned int *sp);
void OsRestorSignalContext(unsigned int *sp);
int OsKill(pid_t pid, int sig, int permission);
int OsDispatch(pid_t pid, siginfo_t *info, int permission);
int OsSigTimedWait(sigset_t *set, siginfo_t *info, unsigned int timeout);
int OsPause(void);
int OsSigPending(sigset_t *set);
int OsSigSuspend(const sigset_t *set);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_SIGNAL_H */
