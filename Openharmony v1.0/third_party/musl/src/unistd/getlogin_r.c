#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <unsupported_api.h>

int getlogin_r(char *name, size_t size)
{
	char *logname = getlogin();
	unsupported_api(__FUNCTION__);
	if (!logname) return ENXIO; /* or...? */
	if (strlen(logname) >= size) return ERANGE;
	strcpy(name, logname);
	return 0;
}
