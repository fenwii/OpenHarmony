#include <signal.h>
#include <errno.h>
#include <string.h>
#include "stdbool.h"
#include "syscall.h"
#include "pthread_impl.h"
#include "libc.h"
#include "lock.h"
#include "ksigaction.h"

#define DEFAULT_SIG_NUM 64
#define SIGNO2SET(s)            ((sigset_t)1 << (s))
#define NULL_SIGNAL_SET         ((sigset_t)0x00000000)
#define SET_BIT(bitmap, pos)    (bitmap |= (1u << pos))
#define CLEAR_BIT(bitmap, pos)  (bitmap &= ~(1u << pos))
#define CHECK_BIT(bitmap, pos)  ((bitmap & (1u << pos)) ? 1 : 0)
#define SIG_FLAG_NOIGNORE 1


struct sigactq {
	struct sigaction act;
	bool	ign_flag;
	unsigned char   signo;
	unsigned char   sigmask;
	unsigned char   reserve[2];
};
typedef struct sigactq sigactq_t;




typedef void (*sa_sighandler_t)(int);
typedef struct sigaction sigaction_t;

static sigactq_t g_sig_arr[DEFAULT_SIG_NUM];
static pthread_spinlock_t sig_lite_lock;

struct sig_default_act {
	unsigned char singNo;
	unsigned char flag;
	sa_sighandler_t action;
};


static void __sig_core(int signo);
static void __sig_kill(int signo);
static void __sig_cont(int signo);
static void __sig_stop(int signo);
static void __sig_ignore(int signo);
static const struct sig_default_act sig_default_action[] = {
	{SIGHUP, 0, __sig_kill},
	{SIGINT, 0, __sig_kill},
	{SIGQUIT, 0, __sig_core},
	{SIGILL, 0, __sig_core},
	{SIGTRAP, 0, __sig_core},
	{SIGABRT, 0, __sig_core},
	{SIGBUS, 0, __sig_core},
	{SIGFPE, 0, __sig_core},
	{SIGKILL, SIG_FLAG_NOIGNORE, __sig_kill},
	{SIGUSR1, 0, __sig_kill},
	{SIGSEGV, 0, __sig_core},
	{SIGUSR2, 0, __sig_kill},
	{SIGPIPE, 0, __sig_kill},
	{SIGALRM, 0, __sig_kill},
	{SIGTERM, 0, __sig_kill},
	{SIGSTKFLT, 0, __sig_kill},
	{SIGCHLD, 0, __sig_ignore},
	{SIGCONT, SIG_FLAG_NOIGNORE, __sig_cont},
	{SIGSTOP, SIG_FLAG_NOIGNORE, __sig_stop},
	{SIGTSTP, 0, __sig_stop},
	{SIGTTIN, 0, __sig_stop},
	{SIGTTOU, 0, __sig_stop},
	{SIGURG, 0, __sig_ignore},
	{SIGXCPU, 0, __sig_core},
	{SIGXFSZ, 0, __sig_core},
	{SIGVTALRM, 0, __sig_kill},
	{SIGPROF, 0, __sig_kill},
	{SIGWINCH, 0, __sig_ignore},
	{SIGIO, 0, __sig_kill},
	{SIGPWR, 0, __sig_kill},
	{SIGSYS, 0, __sig_ignore},
	{32, 0, __sig_ignore},
	{33, 0, __sig_ignore},
	{34, 0, __sig_ignore},
	{35, 0, __sig_ignore},
	{36, 0, __sig_ignore},
	{37, 0, __sig_ignore},
	{38, 0, __sig_ignore},
	{39, 0, __sig_ignore},
	{40, 0, __sig_ignore},
	{41, 0, __sig_ignore},
	{42, 0, __sig_ignore},
	{43, 0, __sig_ignore},
	{44, 0, __sig_ignore},
	{45, 0, __sig_ignore},
	{46, 0, __sig_ignore},
	{47, 0, __sig_ignore},
	{48, 0, __sig_ignore},
	{49, 0, __sig_ignore},
	{50, 0, __sig_ignore},
	{51, 0, __sig_ignore},
	{52, 0, __sig_ignore},
	{53, 0, __sig_ignore},
	{54, 0, __sig_ignore},
	{55, 0, __sig_ignore},
	{56, 0, __sig_ignore},
	{57, 0, __sig_ignore},
	{58, 0, __sig_ignore},
	{59, 0, __sig_ignore},
	{60, 0, __sig_ignore},
	{61, 0, __sig_ignore},
	{62, 0, __sig_ignore},
	{63, 0, __sig_ignore},
	{64, 0, __sig_ignore},
};

static void __sig_core(int signo)
{
	exit(-1);
}

static void __sig_kill(int signo)
{
	exit(-1);
}

static void __sig_cont(int signo)
{
	return;
}

static void __sig_stop(int signo)
{
    return;
}

static void __sig_ignore(int signo)
{
    return;
}

static sigactq_t *__sig_find_action(int sig)
{
	int i;

	for (i = 0; i < sizeof(sig_default_action) / sizeof(struct sig_default_act); i++) {
		if (g_sig_arr[i].signo == sig) {
			return (g_sig_arr + i);
		}
	}
}

static void __sig_copy_sigaction(sigaction_t *src, sigaction_t *dst)
{
	dst->sa_handler = src->sa_handler;
	dst->sa_mask = src->sa_mask;
	dst->sa_flags = src->sa_flags;
}

static int __sig_cannot_catche(int sig, sa_sighandler_t handler)
{
	int i;

	for (i = 0; i < sizeof(sig_default_action) / sizeof(struct sig_default_act); i++) {
		if (sig == sig_default_action[i].singNo) {
			return (sig_default_action[i].flag == SIG_FLAG_NOIGNORE) && (handler != SIG_DFL);
		}
	}
	/* This sig can be catch and ignore return false */
	return 0;
}

static void __sig_operation(unsigned int receivedSigno)
{
	int i;

	for (i = 0; i < sizeof(sig_default_action) / sizeof(struct sig_default_act); i++) {
		if (!g_sig_arr[i].ign_flag && g_sig_arr[i].signo == receivedSigno && g_sig_arr[i].act.sa_handler) {
			(*g_sig_arr[i].act.sa_handler)(g_sig_arr[i].signo);
		}
	}
}

void arm_signal_process(unsigned int receivedSig)
{
	__sig_operation(receivedSig);
}

static void __sig_add_def_action()
{
	int i;

	for (i = 0; i < sizeof(sig_default_action) / sizeof(struct sig_default_act); i++) {
		g_sig_arr[i].signo = (unsigned char)sig_default_action[i].singNo;
		g_sig_arr[i].act.sa_handler = sig_default_action[i].action;
		sigemptyset(&g_sig_arr[i].act.sa_mask);
		g_sig_arr[i].act.sa_flags = sig_default_action[i].flag;
		g_sig_arr[i].ign_flag = false;
	}
}

static sa_sighandler_t __sig_find_def_action(unsigned char signo)
{
	int i;

	for (i = 0; i < sizeof(sig_default_action) / sizeof(struct sig_default_act); i++) {
		if (signo == sig_default_action[i].singNo) {
			return sig_default_action[i].action;
		}
	}
	return NULL;
}

static int __sig_dfl_opr(int sig, sigactq_t *sigact, const sigaction_t *act)
{
	sa_sighandler_t def_handler = NULL;

	def_handler = __sig_find_def_action(sig);

	if (def_handler != NULL) {
		/* Replace it from signal action queue */
		sigact->act.sa_handler = def_handler;
		sigact->act.sa_mask = act->sa_mask;
		sigact->act.sa_flags = act->sa_flags;
	}
	return 0;
}

static int __sig_action_opr(int sig, const sigaction_t *act, sigaction_t *oact)
{
	int ret = 0;
	sa_sighandler_t handler = NULL;
	sigactq_t *sigact = NULL;

	if (act == NULL) return -EINVAL;

	if (sig < SIGHUP || sig > (_NSIG - 1)) return -EINVAL;

	handler = act->sa_handler;
	/* Skip sig that can not be catched */
	if (__sig_cannot_catche(sig, handler)) return -EINVAL;

	pthread_spin_lock(&sig_lite_lock);
	sigact = __sig_find_action(sig);
	if (sigact && oact) __sig_copy_sigaction(&sigact->act, oact);

	sigact->ign_flag = false;

	if (handler == SIG_IGN && sigact) {
		sigact->ign_flag = true;
	} else if (handler == SIG_DFL) {
		ret = __sig_dfl_opr(sig, sigact, act);
	} else {
		sigact->act.sa_handler = handler;
		sigact->act.sa_mask = act->sa_mask;
		sigact->act.sa_flags = act->sa_flags;
	}
	pthread_spin_unlock(&sig_lite_lock);
	return ret;
}

void __sig_init(void)
{
	signal(SIGSYS, arm_do_signal);
	pthread_spin_init(&sig_lite_lock, 0);
	__sig_add_def_action();
}

static volatile int dummy_lock[1] = { 0 };

extern hidden volatile int __abort_lock[1];

weak_alias(dummy_lock, __abort_lock);

static int unmask_done;
static unsigned long handler_set[_NSIG/(8*sizeof(long))];

void __get_handler_set(sigset_t *set)
{
	memcpy(set, handler_set, sizeof handler_set);
}

volatile int __eintr_valid_flag;

int __libc_sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	sigaction_t ksa, ksa_old;
	unsigned long set[_NSIG/(8*sizeof(long))];
	int r = 0;

	if (sa) {
		if ((uintptr_t)sa->sa_handler > 1UL) {
			a_or_l(handler_set+(sig-1)/(8*sizeof(long)),
				1UL<<(sig-1)%(8*sizeof(long)));

			/* If pthread_create has not yet been called,
			 * implementation-internal signals might not
			 * yet have been unblocked. They must be
			 * unblocked before any signal handler is
			 * installed, so that an application cannot
			 * receive an illegal sigset_t (with them
			 * blocked) as part of the ucontext_t passed
			 * to the signal handler. */
			if (!libc.threaded && !unmask_done) {
				__syscall(SYS_rt_sigprocmask, SIG_UNBLOCK,
					SIGPT_SET, 0, _NSIG/8);
				unmask_done = 1;
			}

			if (!(sa->sa_flags & SA_RESTART)) {
				a_store(&__eintr_valid_flag, 1);
			}
		}
		/* Changing the disposition of SIGABRT to anything but
		 * SIG_DFL requires a lock, so that it cannot be changed
		 * while abort is terminating the process after simply
		 * calling raise(SIGABRT) failed to do so. */
		if (sa->sa_handler != SIG_DFL && sig == SIGABRT) {
			__block_all_sigs(&set);
			LOCK(__abort_lock);
		}
		ksa.sa_handler = sa->sa_handler;
		ksa.sa_flags = sa->sa_flags | SA_RESTORER;
		ksa.sa_restorer = (sa->sa_flags & SA_SIGINFO) ? __restore_rt : __restore;
		memcpy(&ksa.sa_mask, &sa->sa_mask, _NSIG/8);
	}

	if (sig == SIGSYS) {
		return __syscall(SYS_rt_sigaction, sig, sa?&ksa:0, old?&ksa_old:0, _NSIG/8);
	} else {
		r = __sig_action_opr(sig, (const sigaction_t*)sa?&ksa:0, (sigaction_t*)old?&ksa_old:0);
	}
	if (sig == SIGABRT && sa && sa->sa_handler != SIG_DFL) {
		UNLOCK(__abort_lock);
		__restore_sigs(&set);
	}
	if (old && !r) {
		old->sa_handler = ksa_old.sa_handler;
		old->sa_flags = ksa_old.sa_flags;
		memcpy(&old->sa_mask, &ksa_old.sa_mask, _NSIG/8);
	}
	return __syscall_ret(r);
}

int __sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	if (sig-32U < 3 || sig-1U >= _NSIG-1) {
		errno = EINVAL;
		return -1;
	}
	return __libc_sigaction(sig, sa, old);
}

weak_alias(__sigaction, sigaction);
