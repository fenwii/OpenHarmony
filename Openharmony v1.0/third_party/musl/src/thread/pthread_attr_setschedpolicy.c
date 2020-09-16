#include "pthread_impl.h"

int pthread_attr_setschedpolicy(pthread_attr_t *a, int policy)
{
	if (policy != SCHED_RR && policy != SCHED_FIFO) {
		return EINVAL;
	}

	a->_a_policy = policy;
	return 0;
}
