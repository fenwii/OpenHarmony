#include <unistd.h>
#include <stdlib.h>
#include <unsupported_api.h>

char *getlogin(void)
{
	unsupported_api(__FUNCTION__);
	return getenv("LOGNAME");
}
