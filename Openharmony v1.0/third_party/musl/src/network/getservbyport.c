#define _GNU_SOURCE
#include <netdb.h>
#include <unsupported_api.h>

struct servent *getservbyport(int port, const char *prots)
{
	static struct servent se;
	static long buf[32/sizeof(long)];
	struct servent *res;
	unsupported_api(__FUNCTION__);
	if (getservbyport_r(port, prots, &se, (void *)buf, sizeof buf, &res))
		return 0;
	return &se;
}
