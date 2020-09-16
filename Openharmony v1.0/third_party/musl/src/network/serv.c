#include <netdb.h>
#include <unsupported_api.h>

void endservent(void)
{
	unsupported_api(__FUNCTION__);
}

void setservent(int stayopen)
{
	unsupported_api(__FUNCTION__);
}

struct servent *getservent(void)
{
	unsupported_api(__FUNCTION__);
	return 0;
}
