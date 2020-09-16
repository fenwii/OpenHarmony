#include "stdio_impl.h"
#include <pthread.h>

static FILE *ofl_head;

static pthread_mutex_t locallock = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

static int LOCK(void)
{
    return pthread_mutex_lock(&locallock);
}

static void UNLOCK(void)
{
    (void)pthread_mutex_unlock(&locallock);
}


FILE **__ofl_lock()
{
	LOCK();
	return &ofl_head;
}

void __ofl_unlock()
{
	UNLOCK();
}
