#include <stropts.h>
#include <fcntl.h>
#include <unsupported_api.h>
int isastream(int fd)
{
	unsupported_api(__FUNCTION__);
	return fcntl(fd, F_GETFD) < 0 ? -1 : 0;
}
