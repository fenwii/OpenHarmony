#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "menuconfig.h"
#include "fs/fs.h"
#include "fs/file.h"

int remove(const char *path)
{
	int r = unlink(path);
	if (r==-EISDIR) r = rmdir(path);
	return r;
}
