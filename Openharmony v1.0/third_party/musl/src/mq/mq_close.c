#include <mqueue.h>
#include "syscall.h"

int mq_close(mqd_t mqd)
{
	return syscall(SYS_mqclose, mqd);
}
