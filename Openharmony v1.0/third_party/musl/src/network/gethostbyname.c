#define _GNU_SOURCE

#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <unsupported_api.h>

struct hostent *gethostbyname(const char *name)
{
	unsupported_api(__FUNCTION__);
	return gethostbyname2(name, AF_INET);
}
