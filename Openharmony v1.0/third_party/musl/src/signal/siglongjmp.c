#include <setjmp.h>
#include <signal.h>
#include <unsupported_api.h>

#include "syscall.h"
#include "pthread_impl.h"

_Noreturn void siglongjmp(sigjmp_buf buf, int ret)
{
	unsupported_api(__FUNCTION__);
	longjmp(buf, ret);
}
