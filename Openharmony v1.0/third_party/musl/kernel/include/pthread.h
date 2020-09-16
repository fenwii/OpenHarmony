#ifndef _PTHREAD_H
#define _PTHREAD_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>
#include "los_task_pri.h"
#include "los_mux_pri.h"

#define __NEED_time_t
#define __NEED_clockid_t
#define __NEED_struct_timespec
#define __NEED_sigset_t
#define __NEED_pthread_t
#define __NEED_pthread_attr_t
#define __NEED_pthread_mutexattr_t
#define __NEED_pthread_condattr_t
#define __NEED_pthread_rwlockattr_t
#define __NEED_pthread_barrierattr_t

#define __NEED_pthread_rwlock_t
#define __NEED_pthread_barrier_t
#define __NEED_pthread_spinlock_t
#define __NEED_pthread_key_t
#define __NEED_pthread_once_t
#define __NEED_size_t
#define __NEED_locale_t

#include <bits/alltypes.h>

#define __NEED_pthread_mutex_t
#define __NEED_pthread_cond_t

#ifndef POSIX_MUTEX_DEFAULT_INHERIT
#define POSIX_MUTEX_DEFAULT_INHERIT 1
#endif

#if defined(__NEED_pthread_mutexattr_t) && !defined(__DEFINED_pthread_mutexattr_t)
typedef LosMuxAttr pthread_mutexattr_t;
#define __DEFINED_pthread_mutexattr_t
#endif

#if defined(__NEED_pthread_mutex_t) && !defined(__DEFINED_pthread_mutex_t)
typedef LosMux pthread_mutex_t;
#define pthread_mutex OsMux
#define __DEFINED_pthread_mutex_t
#endif

#if defined(__NEED_pthread_cond_t) && !defined(__DEFINED_pthread_cond_t)
typedef struct pthread_cond {
  volatile int count;      /**< The number of tasks blocked by condition */
  EVENT_CB_S event;        /**< Event object*/
  pthread_mutex_t* mutex;  /**< Mutex locker for condition variable protection */
  volatile int value;      /**< Condition variable state value*/
} pthread_cond_t;
#define __DEFINED_pthread_cond_t
#endif

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

#define PTHREAD_MUTEX_NORMAL LOS_MUX_NORMAL
#define PTHREAD_MUTEX_DEFAULT PTHREAD_MUTEX_NORMAL
#define PTHREAD_MUTEX_RECURSIVE LOS_MUX_RECURSIVE
#define PTHREAD_MUTEX_ERRORCHECK LOS_MUX_ERRORCHECK

#define PTHREAD_MUTEX_ERRORCHECK_NP PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE

#define PTHREAD_MUTEX_STALLED 0
#define PTHREAD_MUTEX_ROBUST 1

#define PTHREAD_PRIO_NONE    LOS_MUX_PRIO_NONE
#define PTHREAD_PRIO_INHERIT LOS_MUX_PRIO_INHERIT
#define PTHREAD_PRIO_PROTECT LOS_MUX_PRIO_PROTECT

#define PTHREAD_INHERIT_SCHED 0
#define PTHREAD_EXPLICIT_SCHED 1

#define PTHREAD_SCOPE_SYSTEM 0
#define PTHREAD_SCOPE_PROCESS 1

#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED 1

#ifndef POSIX_MUTEX_DEFAULT_INHERIT
#define POSIX_MUTEX_DEFAULT_INHERIT
#endif
#if defined POSIX_MUTEX_DEFAULT_INHERIT

#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
    { OS_MUX_MAGIC, { PTHREAD_PRIO_INHERIT, OS_TASK_PRIORITY_LOWEST, PTHREAD_MUTEX_RECURSIVE_NP, 0 }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     (VOID *)NULL, 0 }

#define PTHREAD_MUTEX_INITIALIZER \
    { OS_MUX_MAGIC, { PTHREAD_PRIO_INHERIT, OS_TASK_PRIORITY_LOWEST, 0, 0 }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     (VOID *)NULL, 0 }
#elif defined POSIX_MUTEX_DEFAULT_PROTECT

#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
    { OS_MUX_MAGIC, { PTHREAD_PRIO_PROTECT, OS_TASK_PRIORITY_LOWEST, PTHREAD_MUTEX_RECURSIVE_NP, 0 }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     (VOID *)NULL, 0 }

#define PTHREAD_MUTEX_INITIALIZER \
    { OS_MUX_MAGIC, { PTHREAD_PRIO_PROTECT, OS_TASK_PRIORITY_LOWEST, 0, 0 },  \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     (VOID *)NULL, 0 }
#else

#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
    { OS_MUX_MAGIC, { PTHREAD_PRIO_NONE, OS_TASK_PRIORITY_LOWEST, PTHREAD_MUTEX_RECURSIVE_NP, 0 }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     (VOID *)NULL, 0 }

#define PTHREAD_MUTEX_INITIALIZER \
    { OS_MUX_MAGIC, { PTHREAD_PRIO_NONE, OS_TASK_PRIORITY_LOWEST, 0, 0 }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     { (struct LOS_DL_LIST *)NULL, (struct LOS_DL_LIST *)NULL }, \
     (VOID *)NULL, 0 }
#endif
#define PTHREAD_RWLOCK_INITIALIZER {{{0}}}
#define PTHREAD_COND_INITIALIZER { -1, { 0, { NULL, NULL } } , NULL, -1 }
#define PTHREAD_ONCE_INIT 0


#define PTHREAD_CANCEL_ENABLE 0
#define PTHREAD_CANCEL_DISABLE 1
#define PTHREAD_CANCEL_MASKED 2

#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_ASYNCHRONOUS 1

#define PTHREAD_CANCELED ((void *)-1)


#define PTHREAD_BARRIER_SERIAL_THREAD (-1)


int pthread_create(pthread_t *__restrict, const pthread_attr_t *__restrict, void *(*)(void *), void *__restrict);
int pthread_detach(pthread_t);
void pthread_exit(void *);
int pthread_join(pthread_t, void **);

#ifdef __GNUC__
__attribute__((const))
#endif
pthread_t pthread_self(void);

int pthread_equal(pthread_t, pthread_t);

int pthread_setcancelstate(int, int *);
int pthread_setcanceltype(int, int *);
void pthread_testcancel(void);
int pthread_cancel(pthread_t);

int pthread_getschedparam(pthread_t, int *__restrict, struct sched_param *__restrict);
int pthread_setschedparam(pthread_t, int, const struct sched_param *);
int pthread_setschedprio(pthread_t, int);

int pthread_once(pthread_once_t *, void (*)(void));

int pthread_mutex_init(pthread_mutex_t *__restrict, const pthread_mutexattr_t *__restrict);
int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_mutex_trylock(pthread_mutex_t *);
int pthread_mutex_timedlock(pthread_mutex_t *__restrict, const struct timespec *__restrict);
int pthread_mutex_destroy(pthread_mutex_t *);
int pthread_mutex_consistent(pthread_mutex_t *);

int pthread_mutex_getprioceiling(const pthread_mutex_t *__restrict, int *__restrict);
int pthread_mutex_setprioceiling(pthread_mutex_t *__restrict, int, int *__restrict);

int pthread_cond_init(pthread_cond_t *__restrict, const pthread_condattr_t *__restrict);
int pthread_cond_destroy(pthread_cond_t *);
int pthread_cond_wait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict);
int pthread_cond_timedwait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict, const struct timespec *__restrict);
int pthread_cond_broadcast(pthread_cond_t *);
int pthread_cond_signal(pthread_cond_t *);

int pthread_rwlock_init(pthread_rwlock_t *__restrict, const pthread_rwlockattr_t *__restrict);
int pthread_rwlock_destroy(pthread_rwlock_t *);
int pthread_rwlock_rdlock(pthread_rwlock_t *);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int pthread_rwlock_timedrdlock(pthread_rwlock_t *__restrict, const struct timespec *__restrict);
int pthread_rwlock_wrlock(pthread_rwlock_t *);
int pthread_rwlock_trywrlock(pthread_rwlock_t *);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *__restrict, const struct timespec *__restrict);
int pthread_rwlock_unlock(pthread_rwlock_t *);

int pthread_spin_init(pthread_spinlock_t *, int);
int pthread_spin_destroy(pthread_spinlock_t *);
int pthread_spin_lock(pthread_spinlock_t *);
int pthread_spin_trylock(pthread_spinlock_t *);
int pthread_spin_unlock(pthread_spinlock_t *);

int pthread_barrier_init(pthread_barrier_t *__restrict, const pthread_barrierattr_t *__restrict, unsigned);
int pthread_barrier_destroy(pthread_barrier_t *);
int pthread_barrier_wait(pthread_barrier_t *);

int pthread_key_create(pthread_key_t *, void (*)(void *));
int pthread_key_delete(pthread_key_t);
void *pthread_getspecific(pthread_key_t);
int pthread_setspecific(pthread_key_t, const void *);

int pthread_attr_init(pthread_attr_t *);
int pthread_attr_destroy(pthread_attr_t *);

int pthread_attr_getguardsize(const pthread_attr_t *__restrict, size_t *__restrict);
int pthread_attr_setguardsize(pthread_attr_t *, size_t);
int pthread_attr_getstacksize(const pthread_attr_t *__restrict, size_t *__restrict);
int pthread_attr_setstacksize(pthread_attr_t *, size_t);
int pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int pthread_attr_setdetachstate(pthread_attr_t *, int);
int pthread_attr_getstack(const pthread_attr_t *__restrict, void **__restrict, size_t *__restrict);
int pthread_attr_setstack(pthread_attr_t *, void *, size_t);
int pthread_attr_getscope(const pthread_attr_t *__restrict, int *__restrict);
int pthread_attr_setscope(pthread_attr_t *, int);
int pthread_attr_getschedpolicy(const pthread_attr_t *__restrict, int *__restrict);
int pthread_attr_setschedpolicy(pthread_attr_t *, int);
int pthread_attr_getschedparam(const pthread_attr_t *__restrict, struct sched_param *__restrict);
int pthread_attr_setschedparam(pthread_attr_t *__restrict, const struct sched_param *__restrict);
int pthread_attr_getinheritsched(const pthread_attr_t *__restrict, int *__restrict);
int pthread_attr_setinheritsched(pthread_attr_t *, int);

int pthread_attr_setstackaddr(pthread_attr_t *, void *);
int pthread_attr_getstackaddr(const pthread_attr_t *, void **);

int pthread_mutexattr_destroy(pthread_mutexattr_t *);
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *__restrict, int *__restrict);
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *__restrict, int *__restrict);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *__restrict, int *__restrict);
int pthread_mutexattr_getrobust(const pthread_mutexattr_t *__restrict, int *__restrict);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *__restrict, int *__restrict);
int pthread_mutexattr_init(pthread_mutexattr_t *);
int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *, int);
int pthread_mutexattr_setprotocol(pthread_mutexattr_t *, int);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
int pthread_mutexattr_setrobust(pthread_mutexattr_t *, int);
int pthread_mutexattr_settype(pthread_mutexattr_t *, int);

int pthread_condattr_init(pthread_condattr_t *);
int pthread_condattr_destroy(pthread_condattr_t *);
int pthread_condattr_setclock(pthread_condattr_t *, clockid_t);
int pthread_condattr_setpshared(pthread_condattr_t *, int);
int pthread_condattr_getclock(const pthread_condattr_t *__restrict, clockid_t *__restrict);
int pthread_condattr_getpshared(const pthread_condattr_t *__restrict, int *__restrict);

int pthread_rwlockattr_init(pthread_rwlockattr_t *);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *__restrict, int *__restrict);

int pthread_barrierattr_destroy(pthread_barrierattr_t *);
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *__restrict, int *__restrict);
int pthread_barrierattr_init(pthread_barrierattr_t *);
int pthread_barrierattr_setpshared(pthread_barrierattr_t *, int);

int pthread_atfork(void (*)(void), void (*)(void), void (*)(void));

int pthread_getconcurrency(void);
int pthread_setconcurrency(int);

int pthread_getcpuclockid(pthread_t, clockid_t *);

struct pthread_cleanup_buffer {
  struct pthread_cleanup_buffer *prev;  /**< Pointer to the buffer to be cleaned*/
  void (*routine)(void *);               /**< General execution function*/
  void *arg;                            /**< Parameter of the execution function*/
};

void pthread_cleanup_push_inner(struct pthread_cleanup_buffer *, void (*)(void *), void *);
void pthread_cleanup_pop_inner(struct pthread_cleanup_buffer *, int);

#define pthread_cleanup_push(f, x)  \
{   \
  struct pthread_cleanup_buffer _buffer_; \
  pthread_cleanup_push_inner(&_buffer_, (f), (x));

#define pthread_cleanup_pop(r)  \
  pthread_cleanup_pop_inner(&_buffer_, (r)); \
}

#ifdef _GNU_SOURCE
struct cpu_set_t;
int pthread_attr_setaffinity_np(pthread_attr_t *, size_t, const cpu_set_t *);
int pthread_attr_getaffinity_np(const pthread_attr_t *, size_t, cpu_set_t *);
int pthread_getaffinity_np(pthread_t, size_t, struct cpu_set_t *);
int pthread_setaffinity_np(pthread_t, size_t, const struct cpu_set_t *);
int pthread_getattr_np(pthread_t, pthread_attr_t *);
int pthread_setname_np(pthread_t, const char *);
int pthread_getattr_default_np(pthread_attr_t *);
int pthread_setattr_default_np(const pthread_attr_t *);
int pthread_tryjoin_np(pthread_t, void **);
int pthread_timedjoin_np(pthread_t, void **, const struct timespec *);
#endif

#if _REDIR_TIME64
__REDIR(pthread_mutex_timedlock, __pthread_mutex_timedlock_time64);
__REDIR(pthread_cond_timedwait, __pthread_cond_timedwait_time64);
__REDIR(pthread_rwlock_timedrdlock, __pthread_rwlock_timedrdlock_time64);
__REDIR(pthread_rwlock_timedwrlock, __pthread_rwlock_timedwrlock_time64);
#ifdef _GNU_SOURCE
__REDIR(pthread_timedjoin_np, __pthread_timedjoin_np_time64);
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif
