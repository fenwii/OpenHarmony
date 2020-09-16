#include "pthread_impl.h"

int pthread_attr_setschedparam(pthread_attr_t *restrict a, const struct sched_param *restrict param)
{
	if (param->sched_priority < 0 || param->sched_priority > PTHREAD_PRIORITY_LOWEST) {
		return EINVAL;
	}

	a->_a_prio = param->sched_priority;
	return 0;
}
