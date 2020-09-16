#include "stdio_impl.h"
#include <unistd.h>
#include "fs/fs.h"
#include "fs/file.h"

int __stdio_close(FILE *f)
{
	return close(f->fd);
}
