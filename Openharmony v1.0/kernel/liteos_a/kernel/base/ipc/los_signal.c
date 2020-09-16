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

#include "los_signal.h"
#include "pthread.h"
#include "los_process_pri.h"
#include "los_hw_pri.h"
#include "user_copy.h"
#ifdef LOSCFG_SECURITY_CAPABILITY
#include "capability_api.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

int raise(int sig)
{
    (VOID)sig;
    PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
    errno = ENOSYS;
    return -1;
}

#define GETUNMASKSET(procmask, pendFlag) ((~(procmask)) & (sigset_t)(pendFlag))
#define UINT64_BIT_SIZE 64

int OsSigIsMember(const sigset_t *set, int signo)
{
    int ret = LOS_NOK;
    /* In musl, sig No bits 00000100 present sig No 3, but  1<< 3 = 00001000, so signo needs minus 1 */
    signo -= 1;
    /* Verify the signal */
    if (GOOD_SIGNO(signo)) {
        /* Check if the signal is in the set */
        ret = ((*set & SIGNO2SET((unsigned int)signo)) != 0);
    }

    return ret;
}

int OsTcbDispatch(LosTaskCB *stcb, siginfo_t *info)
{
    bool masked = FALSE;
    sig_cb *sigcb = &stcb->sig;

    OS_RETURN_IF_NULL(sigcb);
    /* If signo is 0, not send signal, just check process or pthread exist */
    if (info->si_signo == 0) {
        return 0;
    }
    masked = (bool)OsSigIsMember(&sigcb->sigprocmask, info->si_signo);
    if (masked) {
        /* If signal is in wait list and mask list, need unblock it */
        if (!LOS_ListEmpty(&sigcb->waitList) && OsSigIsMember(&sigcb->sigwaitmask, info->si_signo)) {
            OsTaskWake(stcb);
            OsSigEmptySet(&sigcb->sigwaitmask);
        } else {
            OsSigAddSet(&sigcb->sigPendFlag, info->si_signo);
        }
    } else {
        /* unmasked signal actions */
        OsSigAddSet(&sigcb->sigFlag, info->si_signo);
        if (!LOS_ListEmpty(&sigcb->waitList) && OsSigIsMember(&sigcb->sigwaitmask, info->si_signo)) {
            OsTaskWake(stcb);
            OsSigEmptySet(&sigcb->sigwaitmask);
        }
    }
    (void) memcpy_s(&sigcb->sigunbinfo, sizeof(siginfo_t), info, sizeof(siginfo_t));
    return 0;
}

void OsSigMaskSwitch(LosTaskCB * const rtcb, sigset_t set)
{
    sigset_t unmaskset;

    rtcb->sig.sigprocmask = set;
    unmaskset = GETUNMASKSET(rtcb->sig.sigprocmask, rtcb->sig.sigPendFlag);
    if (unmaskset != NULL_SIGNAL_SET) {
        /* pendlist do */
        rtcb->sig.sigFlag |= unmaskset;
        rtcb->sig.sigPendFlag ^= unmaskset;
    }
}

int OsSigprocMask(int how, const sigset_t_l *setl, sigset_t_l *oldset)
{
    LosTaskCB *spcb = NULL;
    sigset_t oldSigprocmask;
    int ret = LOS_OK;
    unsigned int intSave;
    sigset_t set;
    int retVal;

    if (setl != NULL) {
        retVal = LOS_ArchCopyFromUser(&set, &(setl->sig[0]), sizeof(sigset_t));
        if (retVal != 0) {
            return -EFAULT;
        }
    }
    SCHEDULER_LOCK(intSave);
    spcb = OsCurrTaskGet();
    /* If requested, copy the old mask to user. */
    oldSigprocmask = spcb->sig.sigprocmask;

    /* If requested, modify the current signal mask. */
    if (setl != NULL) {
        /* Okay, determine what we are supposed to do */
        switch (how) {
            /* Set the union of the current set and the signal
             * set pointed to by set as the new sigprocmask.
             */
            case SIG_BLOCK:
                spcb->sig.sigprocmask |= set;
                break;
            /* Set the intersection of the current set and the
             * signal set pointed to by set as the new sigprocmask.
             */
            case SIG_UNBLOCK:
                spcb->sig.sigprocmask &= ~(set);
                break;
            /* Set the signal set pointed to by set as the new sigprocmask. */
            case SIG_SETMASK:
                spcb->sig.sigprocmask = set;
                break;
            default:
                ret = -EINVAL;
                break;
        }
        /* If pending mask not in sigmask, need set sigflag. */
        OsSigMaskSwitch(spcb, spcb->sig.sigprocmask);
    }
    SCHEDULER_UNLOCK(intSave);

    if (oldset != NULL) {
        retVal = LOS_ArchCopyToUser(&(oldset->sig[0]), &oldSigprocmask, sizeof(sigset_t));
        if (retVal != 0) {
            return -EFAULT;
        }
    }
    return ret;
}

int OsSigProcessForeachChild(LosProcessCB *spcb, ForEachTaskCB handler, void *arg)
{
    int ret;

    /* Visit the main thread last (if present) */
    LosTaskCB *taskCB = NULL;
    LOS_DL_LIST_FOR_EACH_ENTRY(taskCB, &(spcb->threadSiblingList), LosTaskCB, threadList) {
        ret = handler(taskCB, arg);
        OS_RETURN_IF(ret != 0, ret);
    }
    return LOS_OK;
}

static int SigProcessSignalHandler(LosTaskCB *tcb, void *arg)
{
    struct ProcessSignalInfo *info = (struct ProcessSignalInfo *)arg;
    int ret;
    int isMember;

    if (tcb == NULL) {
        return 0;
    }

    /* If the default tcb is not setted, then set this one as default. */
    if (!info->defaultTcb) {
        info->defaultTcb = tcb;
    }

    isMember = OsSigIsMember(&tcb->sig.sigwaitmask, info->sigInfo->si_signo);
    if (isMember && (!info->awakenedTcb)) {
        /* This means the task is waiting for this signal. Stop looking for it and use this tcb.
         * The requirement is: if more than one task in this task group is waiting for the signal,
         * then only one indeterminate task in the group will receive the signal.
         */
        ret = OsTcbDispatch(tcb, info->sigInfo);
        OS_RETURN_IF(ret < 0, ret);

        /* set this tcb as awakenedTcb */
        info->awakenedTcb = tcb;
        OS_RETURN_IF(info->receivedTcb != NULL, SIG_STOP_VISIT); /* Stop search */
    }
    /* Is this signal unblocked on this thread? */
    isMember = OsSigIsMember(&tcb->sig.sigprocmask, info->sigInfo->si_signo);
    if ((!isMember) && (!info->receivedTcb) && (tcb != info->awakenedTcb)) {
        /* if unblockedTcb of this signal is not setted, then set it. */
        if (!info->unblockedTcb) {
            info->unblockedTcb = tcb;
        }

        ret = OsTcbDispatch(tcb, info->sigInfo);
        OS_RETURN_IF(ret < 0, ret);
        /* set this tcb as receivedTcb */
        info->receivedTcb = tcb;
        OS_RETURN_IF(info->awakenedTcb != NULL, SIG_STOP_VISIT); /* Stop search */
    }
    return 0; /* Keep searching */
}

static int SigProcessKillSigHandler(LosTaskCB *tcb, void *arg)
{
    struct ProcessSignalInfo *info = (struct ProcessSignalInfo *)arg;

    if ((tcb != NULL) && (info != NULL) && (info->sigInfo != NULL)) {
        sig_cb *sigcb = &tcb->sig;
        if (!LOS_ListEmpty(&sigcb->waitList) && OsSigIsMember(&sigcb->sigwaitmask, info->sigInfo->si_signo)) {
            OsTaskWake(tcb);
            OsSigEmptySet(&sigcb->sigwaitmask);
        }
    }
    return 0;
}

static void SigProcessLoadTcb(struct ProcessSignalInfo *info, siginfo_t *sigInfo)
{
    LosTaskCB *tcb = NULL;

    if (info->awakenedTcb == NULL && info->receivedTcb == NULL) {
        if (info->unblockedTcb) {
            tcb = info->unblockedTcb;
        } else if (info->defaultTcb) {
            tcb = info->defaultTcb;
        } else {
            return;
        }
        /* Deliver the signal to the selected task */
        (void)OsTcbDispatch(tcb, sigInfo);
    }
}

int OsSigProcessSend(LosProcessCB *spcb, siginfo_t *sigInfo)
{
    int ret;
    struct ProcessSignalInfo info = {
        .sigInfo = sigInfo,
        .defaultTcb = NULL,
        .unblockedTcb = NULL,
        .awakenedTcb = NULL,
        .receivedTcb = NULL
    };

    /* visit all taskcb and dispatch signal */
    if ((info.sigInfo != NULL) && (info.sigInfo->si_signo == SIGKILL)) {
        (void)OsSigProcessForeachChild(spcb, SigProcessKillSigHandler, &info);
        OsSigAddSet(&spcb->sigShare, info.sigInfo->si_signo);
        OsWaitSignalToWakeProcess(spcb);
        return 0;
    } else {
        ret = OsSigProcessForeachChild(spcb, SigProcessSignalHandler, &info);
    }
    if (ret < 0) {
        return ret;
    }
    SigProcessLoadTcb(&info, sigInfo);
    return 0;
}

int OsSigEmptySet(sigset_t *set)
{
    *set = NULL_SIGNAL_SET;
    return 0;
}

/* Privilege process can't send to kernel and privilege process */
static int OsSignalPermissionToCheck(const LosProcessCB *spcb)
{
    UINT32 gid = spcb->group->groupID;

    if (gid == OS_KERNEL_PROCESS_GROUP) {
        return -EPERM;
    } else if (gid == OS_USER_PRIVILEGE_PROCESS_GROUP) {
        return -EPERM;
    }

    return 0;
}

int OsDispatch(pid_t pid, siginfo_t *info, int permission)
{
    LosProcessCB *spcb = OS_PCB_FROM_PID(pid);
    if (OsProcessIsUnused(spcb)) {
        return -ESRCH;
    }
#ifdef LOSCFG_SECURITY_CAPABILITY
    LosProcessCB *current = OsCurrProcessGet();

    /* If the process you want to kill had been inactive, but still exist. should return LOS_OK */
    if (OsProcessIsInactive(spcb)) {
        return LOS_OK;
    }

    /* Kernel process always has kill permission and user process should check permission */
    if (OsProcessIsUserMode(current) && !(current->processStatus & OS_PROCESS_FLAG_EXIT)) {
        if ((current != spcb) && (!IsCapPermit(CAP_KILL)) && (current->user->userID != spcb->user->userID)) {
            return -EPERM;
        }
    }
#endif
    if ((permission == OS_USER_KILL_PERMISSION) && (OsSignalPermissionToCheck(spcb) < 0)) {
        return -EPERM;
    }
    return OsSigProcessSend(spcb, info);
}

int OsKill(pid_t pid, int sig, int permission)
{
    siginfo_t info;
    int ret;

    /* Make sure that the para is valid */
    if (!GOOD_SIGNO(sig) || pid < 0) {
        return -EINVAL;
    }
    if (OsProcessIDUserCheckInvalid(pid)) {
        return -ESRCH;
    }

    /* Create the siginfo structure */
    info.si_signo = sig;
    info.si_code = SI_USER;
    info.si_value.sival_ptr = NULL;

    /* Send the signal */
    ret = OsDispatch(pid, &info, permission);
    return ret;
}

int OsKillLock(pid_t pid, int sig)
{
    int ret;
    unsigned int intSave;

    SCHEDULER_LOCK(intSave);
    ret = OsKill(pid, sig, OS_USER_KILL_PERMISSION);
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

int OsPthreadKill(UINT32 tid, int signo)
{
    LosTaskCB *stcb = NULL;
    siginfo_t info;

    int ret;
    UINT32 intSave;

    /* Make sure that the signal is valid */
    OS_RETURN_IF(!GOOD_SIGNO(signo), -EINVAL);
    if (OS_TID_CHECK_INVALID(tid)) {
        return -ESRCH;
    }

    /* Create the siginfo structure */
    info.si_signo = signo;
    info.si_code = SI_USER;
    info.si_value.sival_ptr = NULL;
    /* Keep things stationary through the following */
    SCHEDULER_LOCK(intSave);
    /* Get the TCB associated with the thread */
    stcb = OsGetTaskCB(tid);
    OS_GOTO_EXIT_IF(stcb == NULL, -ESRCH);

    ret = OsUserTaskOperatePermissionsCheck(stcb);
    OS_GOTO_EXIT_IF(ret != LOS_OK, -ret);

    /* Dispatch the signal to thread, bypassing normal task group thread
     * dispatch rules. */
    ret = OsTcbDispatch(stcb, &info);
EXIT:
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

int OsSigAddSet(sigset_t *set, int signo)
{
    /* Verify the signal */
    if (!GOOD_SIGNO(signo)) {
        return -EINVAL;
    } else {
        /* In musl, sig No bits 00000100 present sig No 3, but  1<< 3 = 00001000, so signo needs minus 1 */
        signo -= 1;
        /* Add the signal to the set */
        *set |= SIGNO2SET((unsigned int)signo);
        return LOS_OK;
    }
}

int OsSigPending(sigset_t *set)
{
    LosTaskCB *tcb = NULL;
    unsigned int intSave;

    if (set == NULL) {
        return -EFAULT;
    }

    SCHEDULER_LOCK(intSave);
    tcb = OsCurrTaskGet();
    *set = tcb->sig.sigPendFlag;
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

STATIC int FindFirstSetedBit(UINT64 n)
{
    int count;

    if (n == 0) {
        return -1;
    }
    for (count = 0; (count < UINT64_BIT_SIZE) && (n ^ 1ULL); n >>= 1, count++) {}
    return (count < UINT64_BIT_SIZE) ? count : (-1);
}

int OsSigTimedWaitNoLock(sigset_t *set, siginfo_t *info, unsigned int timeout)
{
    LosTaskCB *task = NULL;
    sig_cb *sigcb = NULL;
    int ret;

    task = OsCurrTaskGet();
    sigcb = &task->sig;

    if (sigcb->waitList.pstNext == NULL) {
        LOS_ListInit(&sigcb->waitList);
    }
    /* If pendingflag & set > 0, shound clear pending flag */
    sigset_t clear = sigcb->sigPendFlag & *set;
    if (clear) {
        sigcb->sigPendFlag ^= clear;
        ret = FindFirstSetedBit((UINT64)clear) + 1;
    } else {
        OsSigAddSet(set, SIGKILL);
        OsSigAddSet(set, SIGSTOP);

        sigcb->sigwaitmask |= *set;
        ret = OsTaskWait(&sigcb->waitList, timeout, TRUE);
        if (ret == LOS_ERRNO_TSK_TIMEOUT) {
            ret = -EAGAIN;
        }
        sigcb->sigwaitmask = NULL_SIGNAL_SET;
    }
    if (info != NULL) {
        (void) memcpy_s(info, sizeof(siginfo_t), &sigcb->sigunbinfo, sizeof(siginfo_t));
    }
    return ret;
}

int OsSigTimedWait(sigset_t *set, siginfo_t *info, unsigned int timeout)
{
    int ret;
    unsigned int intSave;

    SCHEDULER_LOCK(intSave);

    ret = OsSigTimedWaitNoLock(set, info, timeout);

    SCHEDULER_UNLOCK(intSave);
    return ret;
}

int OsPause(void)
{
    LosTaskCB *spcb = NULL;
    sigset_t oldSigprocmask;

    spcb = OsCurrTaskGet();
    oldSigprocmask = spcb->sig.sigprocmask;
    return OsSigSuspend(&oldSigprocmask);
}

int OsSigSuspend(const sigset_t *set)
{
    unsigned int intSave;
    LosTaskCB *rtcb = NULL;
    unsigned int sigTempProcMask;
    sigset_t setSuspend;
    int ret;

    if (set == NULL) {
        return -EINVAL;
    }
    SCHEDULER_LOCK(intSave);
    rtcb = OsCurrTaskGet();
    sigTempProcMask = rtcb->sig.sigprocmask;

    /* Wait signal calc */
    setSuspend = FULL_SIGNAL_SET & (~(*set));

    /* If pending mask not in sigmask, need set sigflag */
    OsSigMaskSwitch(rtcb, *set);
    ret = OsSigTimedWaitNoLock(&setSuspend, NULL, LOS_WAIT_FOREVER);
    if (ret < 0) {
        PRINT_ERR("FUNC %s LINE = %d, ret = %x\n", __FUNCTION__, __LINE__, ret);
    }
    /* Restore old sigprocmask */
    OsSigMaskSwitch(rtcb, sigTempProcMask);

    SCHEDULER_UNLOCK(intSave);
    return -EINTR;
}

int OsSigAction(int sig, const sigaction_t *act, sigaction_t *oact)
{
    UINTPTR addr;
    sigaction_t action;

    if (!GOOD_SIGNO(sig) || sig < 1 || act == NULL) {
        return -EINVAL;
    }
    if (LOS_ArchCopyFromUser(&action, act, sizeof(sigaction_t)) != LOS_OK) {
        return -EFAULT;
    }

    if (sig == SIGSYS) {
        addr = OsGetSigHandler();
        if (addr == 0) {
            OsSetSigHandler((unsigned long)(UINTPTR)action.sa_handler);
            return LOS_OK;
        }
        return -EINVAL;
    }

    return LOS_OK;
}

void OsSaveSignalContext(unsigned int *sp)
{
    UINTPTR sigHandler;
    UINT32 intSave;
    LosTaskCB *task = NULL;
    LosProcessCB *process = NULL;
    sig_cb *sigcb = NULL;
    unsigned long cpsr;

    OS_RETURN_IF_VOID(sp == NULL);
    cpsr = OS_SYSCALL_GET_CPSR(sp);

    OS_RETURN_IF_VOID(((cpsr & CPSR_MASK_MODE) != CPSR_USER_MODE));
    SCHEDULER_LOCK(intSave);
    task = OsCurrTaskGet();
    process = OsCurrProcessGet();
    sigcb = &task->sig;

    if ((sigcb->context.count == 0) && ((sigcb->sigFlag != 0) || (process->sigShare != 0))) {
        sigHandler = OsGetSigHandler();
        if (sigHandler == 0) {
            sigcb->sigFlag = 0;
            process->sigShare = 0;
            SCHEDULER_UNLOCK(intSave);
            PRINT_ERR("The signal processing function for the current process pid =%d is NULL!\n", task->processID);
            return;
        }
        /* One pthread do the share signal */
        sigcb->sigFlag |= process->sigShare;
        unsigned int signo = (unsigned int)FindFirstSetedBit(sigcb->sigFlag) + 1;
        OsProcessExitCodeSignalSet(process, signo);
        sigcb->context.CPSR = cpsr;
        sigcb->context.PC = sp[REG_PC];
        sigcb->context.USP = sp[REG_SP];
        sigcb->context.ULR = sp[REG_LR];
        sigcb->context.R0 = sp[REG_R0];
        sigcb->context.R1 = sp[REG_R1];
        sigcb->context.R2 = sp[REG_R2];
        sigcb->context.R3 = sp[REG_R3];
        sigcb->context.R7 = sp[REG_R7];
        sigcb->context.R12 = sp[REG_R12];
        sp[REG_PC] = sigHandler;
        sp[REG_R0] = signo;
        sp[REG_R1] = (unsigned int)(UINTPTR)(sigcb->sigunbinfo.si_value.sival_ptr);
        /* sig No bits 00000100 present sig No 3, but  1<< 3 = 00001000, so signo needs minus 1 */
        sigcb->sigFlag ^= 1ULL << (signo - 1);
        sigcb->context.count++;
    }

    SCHEDULER_UNLOCK(intSave);
}

void OsSaveSignalContextIrq(unsigned int *sp, unsigned int r7)
{
    UINTPTR sigHandler;
    LosTaskCB *task = NULL;
    LosProcessCB *process = NULL;
    sig_cb *sigcb = NULL;
    unsigned long cpsr;
    UINT32 intSave;
    TaskIrqContext *context = (TaskIrqContext *)(sp);

    OS_RETURN_IF_VOID(sp == NULL);
    cpsr = context->CPSR;
    OS_RETURN_IF_VOID(((cpsr & CPSR_MASK_MODE) != CPSR_USER_MODE));

    SCHEDULER_LOCK(intSave);
    task = OsCurrTaskGet();
    process = OsCurrProcessGet();
    sigcb = &task->sig;
    if ((sigcb->context.count == 0) && ((sigcb->sigFlag != 0) || (process->sigShare != 0))) {
        sigHandler = OsGetSigHandler();
        if (sigHandler == 0) {
            sigcb->sigFlag = 0;
            process->sigShare = 0;
            SCHEDULER_UNLOCK(intSave);
            PRINT_ERR("The current process pid =%d starts fail!\n", task->processID);
            return;
        }
        sigcb->sigFlag |= process->sigShare;
        unsigned int signo = (unsigned int)FindFirstSetedBit(sigcb->sigFlag) + 1;
        OsProcessExitCodeSignalSet(process, signo);
        (VOID)memcpy_s(&sigcb->context.R0, sizeof(TaskIrqDataSize), &context->R0, sizeof(TaskIrqDataSize));
        sigcb->context.R7 = r7;
        context->PC = sigHandler;
        context->R0 = signo;
        context->R1 = (UINT32)(UINTPTR)sigcb->sigunbinfo.si_value.sival_ptr;
        /* sig No bits 00000100 present sig No 3, but  1<< 3 = 00001000, so signo needs minus 1 */
        sigcb->sigFlag ^= 1ULL << (signo - 1);
        sigcb->context.count++;
    }
    SCHEDULER_UNLOCK(intSave);
}

void OsRestorSignalContext(unsigned int *sp)
{
    LosTaskCB *task = NULL; /* Do not adjust this statement */
    LosProcessCB *process = NULL;
    sig_cb *sigcb = NULL;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    task = OsCurrTaskGet();
    sigcb = &task->sig;

    if (sigcb->context.count != 1) {
        SCHEDULER_UNLOCK(intSave);
        PRINT_ERR("sig error count : %d\n", sigcb->context.count);
        return;
    }

    process = OsCurrProcessGet();
    sp[REG_PC] = sigcb->context.PC;
    OS_SYSCALL_SET_CPSR(sp, sigcb->context.CPSR);
    sp[REG_SP] = sigcb->context.USP;
    sp[REG_LR] = sigcb->context.ULR;
    sp[REG_R0] = sigcb->context.R0;
    sp[REG_R1] = sigcb->context.R1;
    sp[REG_R2] = sigcb->context.R2;
    sp[REG_R3] = sigcb->context.R3;
    sp[REG_R7] = sigcb->context.R7;
    sp[REG_R12] = sigcb->context.R12;
    sigcb->context.count--;
    process->sigShare = 0;
    OsProcessExitCodeSignalClear(process);
    SCHEDULER_UNLOCK(intSave);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
