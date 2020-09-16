#include <unistd.h>
#include <unsupported_api.h>

long gethostid()
{
	unsupported_api(__FUNCTION__);
	return 0;
}
