#include <unsupported_api.h>
#include "pwf.h"

static FILE *f;
static char *line;
static struct passwd pw;
static size_t size;

void setpwent()
{
	unsupported_api(__FUNCTION__);
	if (f) fclose(f);
	f = 0;
}

weak_alias(setpwent, endpwent);

struct passwd *getpwent()
{
	struct passwd *res;
	unsupported_api(__FUNCTION__);
	if (!f) f = fopen("/etc/passwd", "rbe");
	if (!f) return 0;
	__getpwent_a(f, &pw, &line, &size, &res);
	return res;
}

struct passwd *getpwuid(uid_t uid)
{
	struct passwd *res;
	unsupported_api(__FUNCTION__);
	__getpw_a(0, uid, &pw, &line, &size, &res);
	return res;
}

struct passwd *getpwnam(const char *name)
{
	struct passwd *res;
	unsupported_api(__FUNCTION__);
	__getpw_a(name, 0, &pw, &line, &size, &res);
	return res;
}
