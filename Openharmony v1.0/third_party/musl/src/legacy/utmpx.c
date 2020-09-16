#define _GNU_SOURCE
#include <utmpx.h>
#include <stddef.h>
#include <errno.h>
#include <unsupported_api.h>

void endutxent(void)
{
	unsupported_api(__FUNCTION__);
}

void setutxent(void)
{
	unsupported_api(__FUNCTION__);
}

struct utmpx *getutxent(void)
{
	unsupported_api(__FUNCTION__);
	return NULL;
}

struct utmpx *getutxid(const struct utmpx *ut)
{
	unsupported_api(__FUNCTION__);
	return NULL;
}

struct utmpx *getutxline(const struct utmpx *ut)
{
	unsupported_api(__FUNCTION__);
	return NULL;
}

struct utmpx *pututxline(const struct utmpx *ut)
{
	unsupported_api(__FUNCTION__);
	return NULL;
}

void updwtmpx(const char *f, const struct utmpx *u)
{
	unsupported_api(__FUNCTION__);
}

static int __utmpxname(const char *f)
{
	unsupported_api(__FUNCTION__);
	errno = ENOTSUP;
	return -1;
}

weak_alias(endutxent, endutent);
weak_alias(setutxent, setutent);
weak_alias(getutxent, getutent);
weak_alias(getutxid, getutid);
weak_alias(getutxline, getutline);
weak_alias(pututxline, pututline);
weak_alias(updwtmpx, updwtmp);
weak_alias(__utmpxname, utmpname);
weak_alias(__utmpxname, utmpxname);
