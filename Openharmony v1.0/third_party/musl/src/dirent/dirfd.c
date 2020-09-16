#include <dirent.h>
#include "__dirent.h"
#include <unsupported_api.h>

int dirfd(DIR *d)
{
	unsupported_api(__FUNCTION__);
	return d->fd;
}
