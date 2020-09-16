#include <pthread.h>
#include <unsupported_api.h>

int pthread_getconcurrency()
{
	unsupported_api(__FUNCTION__);
	return 0;
}
