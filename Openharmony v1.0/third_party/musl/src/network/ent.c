#include <netdb.h>
#include <unsupported_api.h>

void sethostent(int x)
{
	unsupported_api(__FUNCTION__);
}

struct hostent *gethostent()
{
	unsupported_api(__FUNCTION__);
	return 0;
}

struct netent *getnetent()
{
	unsupported_api(__FUNCTION__);
	return 0;
}

void endhostent(void)
{
	unsupported_api(__FUNCTION__);
}

weak_alias(sethostent, setnetent);
weak_alias(endhostent, endnetent);
