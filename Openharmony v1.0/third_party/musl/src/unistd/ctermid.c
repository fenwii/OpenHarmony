#include <stdio.h>
#include <string.h>
#include <unsupported_api.h>

char *ctermid(char *s)
{
	unsupported_api(__FUNCTION__);
	return s ? strcpy(s, "/dev/tty") : "/dev/tty";
}
