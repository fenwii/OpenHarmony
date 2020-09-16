#include <sys/sem.h>
#include <unsupported_api.h>

#include "syscall.h"
#include "ipc.h"

int semop(int id, struct sembuf *buf, size_t n)
{
	unsupported_api(__FUNCTION__);
#ifndef SYS_ipc
	return syscall(SYS_semop, id, buf, n);
#else
	return syscall(SYS_ipc, IPCOP_semop, id, n, 0, buf);
#endif
}
