#include "pthread_impl.h"

int pthread_attr_setscope(pthread_attr_t *a, int scope)
{
	switch (scope) {
	case PTHREAD_SCOPE_SYSTEM:
		return ENOTSUP;
	case PTHREAD_SCOPE_PROCESS:
		return 0;
	default:
		return EINVAL;
	}
}
