#ifndef _SIGNAL_H
#define _SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) \
 || defined(_BSD_SOURCE)

#ifdef _GNU_SOURCE
#define __ucontext ucontext
#endif

#define __NEED_size_t
#define __NEED_pid_t
#define __NEED_uid_t
#define __NEED_struct_timespec
#define __NEED_pthread_t
#define __NEED_pthread_attr_t
#define __NEED_time_t
#define __NEED_clock_t
#define __NEED_sigset_t

#include <bits/alltypes.h>

#define SIG_BLOCK     0
#define SIG_UNBLOCK   1
#define SIG_SETMASK   2
#define NUM_SIGNAL_ACTIONS 16

#define SI_ASYNCNL (-60)
#define SI_TKILL (-6)
#define SI_SIGIO (-5)
#define SI_ASYNCIO 4
#define SI_MESGQ 5
#define SI_TIMER (-2)
#define SI_QUEUE 2
#define SI_USER 1
#define SI_KERNEL 128

typedef struct sigaltstack stack_t;

#endif

#include <bits/signal.h>

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) \
 || defined(_BSD_SOURCE)

#define SIG_HOLD ((void (*)(int)) 2)

#define FPE_INTDIV 1
#define FPE_INTOVF 2
#define FPE_FLTDIV 3
#define FPE_FLTOVF 4
#define FPE_FLTUND 5
#define FPE_FLTRES 6
#define FPE_FLTINV 7
#define FPE_FLTSUB 8

#define ILL_ILLOPC 1
#define ILL_ILLOPN 2
#define ILL_ILLADR 3
#define ILL_ILLTRP 4
#define ILL_PRVOPC 5
#define ILL_PRVREG 6
#define ILL_COPROC 7
#define ILL_BADSTK 8

#define SEGV_MAPERR 1
#define SEGV_ACCERR 2
#define SEGV_BNDERR 3
#define SEGV_PKUERR 4

#define BUS_ADRALN 1
#define BUS_ADRERR 2
#define BUS_OBJERR 3
#define BUS_MCEERR_AR 4
#define BUS_MCEERR_AO 5

#define CLD_EXITED 1
#define CLD_KILLED 2
#define CLD_DUMPED 3
#define CLD_TRAPPED 4
#define CLD_STOPPED 5
#define CLD_CONTINUED 6

union sigval {
    int sival_int;
    void *sival_ptr;
};

typedef struct {
    int si_signo, si_errno, si_code;
    union {
        char __pad[128 - 2*sizeof(int) - sizeof(long)];
        struct {
            union {
                struct {
                    pid_t si_pid;
                    uid_t si_uid;
                } __piduid;
                struct {
                    int si_timerid;
                    int si_overrun;
                } __timer;
            } __first;
            union {
                union sigval si_value;
                struct {
                    int si_status;
                    clock_t si_utime, si_stime;
                } __sigchld;
            } __second;
        } __si_common;
    } __si_fields;
} siginfo_t;
#define si_pid     __si_fields.__si_common.__first.__piduid.si_pid
#define si_uid     __si_fields.__si_common.__first.__piduid.si_uid
#define si_status  __si_fields.__si_common.__second.__sigchld.si_status
#define si_utime   __si_fields.__si_common.__second.__sigchld.si_utime
#define si_stime   __si_fields.__si_common.__second.__sigchld.si_stime
#define si_value   __si_fields.__si_common.__second.si_value
#define si_timerid __si_fields.__si_common.__first.__timer.si_timerid
#define si_overrun __si_fields.__si_common.__first.__timer.si_overrun

struct sigaction {
    union {
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t *, void *);
    } sa_sigactionhandler;
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};
#define sa_handler   sa_sigactionhandler.sa_handler
#define sa_sigaction sa_sigactionhandler.sa_sigaction

struct sigevent {
    union sigval sigev_value;
    int sigev_signo;
    int sigev_notify;
    void (*sigev_notify_function)(union sigval);
    void *sigev_notify_attributes;
};

#define SIGEV_SIGNAL 0
#define SIGEV_NONE 1
#define SIGEV_THREAD 2

#define SIGRTMIN  35
#define SIGRTMAX  (_NSIG - 1)

int pthread_sigmask(int, const sigset_t *, sigset_t *);
int sigfillset(sigset_t *);
int sigdelset(sigset_t *, int);
#endif

#if defined(_XOPEN_SOURCE) || defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
void (*sigset(int, void (*)(int)))(int);
#define TRAP_BRKPT 1
#define TRAP_TRACE 2
#define TRAP_BRANCH 3
#define TRAP_HWBKPT 4
#define TRAP_UNK 5
#define POLL_IN 1
#define POLL_OUT 2
#define POLL_MSG 3
#define POLL_ERR 4
#define POLL_PRI 5
#define POLL_HUP 6
#define SS_ONSTACK    1
#define SS_DISABLE    2
#define SS_AUTODISARM (1U << 31)
#define SS_FLAG_BITS SS_AUTODISARM
#endif

#if defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
#define NSIG _NSIG
typedef void (*sig_t)(int);
#endif

#ifdef _GNU_SOURCE
typedef void (*sighandler_t)(int);
void (*bsd_signal(int, void (*)(int)))(int);

#define SA_NOMASK SA_NODEFER
#define SA_ONESHOT SA_RESETHAND
#endif

#define SIG_ERR  ((void (*)(int)) 0)
#define SIG_DFL  ((void (*)(int)) 0)
#define SIG_IGN  ((void (*)(int)) 0)

typedef int sig_atomic_t;

void (*signal(int, void (*)(int)))(int);
int raise(int);

#if _REDIR_TIME64
#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) \
 || defined(_BSD_SOURCE)
__REDIR(sigtimedwait, __sigtimedwait_time64);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
