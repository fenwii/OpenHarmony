#include "pthread_impl.h"
#include <threads.h>

pthread_t __pthread_self()
{
	uintptr_t p;
	p = __syscall(SYS_get_thread_area);
	return (void *)(p - sizeof(struct pthread));
}

static pthread_t __pthread_self_internal()
{
	return __pthread_self();
}

weak_alias(__pthread_self_internal, pthread_self);
weak_alias(__pthread_self_internal, thrd_current);
