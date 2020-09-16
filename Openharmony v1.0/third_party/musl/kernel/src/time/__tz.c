#include "time_impl.h"
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "libc.h"
#include <pthread.h>

long  __timezone = 0;
int   __daylight = 0;
char *__tzname[2] = { 0, 0 };

weak_alias(__timezone, timezone);
weak_alias(__daylight, daylight);
weak_alias(__tzname, tzname);

static pthread_mutex_t locallock = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

static int LOCK(void)
{
	return pthread_mutex_lock(&locallock);
}

static void UNLOCK(void)
{
	(void)pthread_mutex_unlock(&locallock);
}


const char __utc[] = "UTC";

static int dst_off;
static int r0[5], r1[5];

static const unsigned char *zi, *trans, *index, *types, *abbrevs, *abbrevs_end;

#define VEC(...) ((const unsigned char[]){__VA_ARGS__})

static uint32_t zi_read32(const unsigned char *z)
{
	return (unsigned)z[0]<<24 | z[1]<<16 | z[2]<<8 | z[3];
}

static void do_tzset(void)
{
}

/* Search zoneinfo rules to find the one that applies to the given time,
 * and determine alternate opposite-DST-status rule that may be needed. */

static size_t scan_trans(long long t, int local, size_t *alt)
{
	int scale = 3 - (trans == zi+44);
	uint64_t x;
	int off = 0;

	size_t a = 0, n = (index-trans)>>scale, m;

	if (!n) {
		if (alt) *alt = 0;
		return 0;
	}

	/* Binary search for 'most-recent rule before t'. */
	while (n > 1) {
		m = a + n/2;
		x = zi_read32(trans + (m<<scale));
		if (scale == 3) x = x<<32 | zi_read32(trans + (m<<scale) + 4);
		else x = (int32_t)x;
		if (local) off = (int32_t)zi_read32(types + 6 * index[m-1]);
		if (t - off < (int64_t)x) {
			n /= 2;
		} else {
			a = m;
			n -= n/2;
		}
	}

	/* First and last entry are special. First means to use lowest-index
	 * non-DST type. Last means to apply POSIX-style rule if available. */
	n = (index-trans)>>scale;
	if (a == n-1) return -1;
	if (a == 0) {
		x = zi_read32(trans + (a<<scale));
		if (scale == 3) x = x<<32 | zi_read32(trans + (a<<scale) + 4);
		else x = (int32_t)x;
		if (local) off = (int32_t)zi_read32(types + 6 * index[a-1]);
		if (t - off < (int64_t)x) {
			for (a=0; a<(abbrevs-types)/6; a++) {
				if (types[6*a+4] != types[4]) break;
			}
			if (a == (abbrevs-types)/6) a = 0;
			if (types[6*a+4]) {
				*alt = a;
				return 0;
			} else {
				*alt = 0;
				return a;
			}
		}
	}

	/* Try to find a neighboring opposite-DST-status rule. */
	if (alt) {
		if (a && types[6*index[a-1]+4] != types[6*index[a]+4])
			*alt = index[a-1];
		else if (a+1<n && types[6*index[a+1]+4] != types[6*index[a]+4])
			*alt = index[a+1];
		else
			*alt = index[a];
	}

	return index[a];
}

static int days_in_month(int m, int is_leap)
{
	if (m==2) return 28+is_leap;
	else return 30+((0xad5>>(m-1))&1);
}

/* Convert a POSIX DST rule plus year to seconds since epoch. */

static long long rule_to_secs(const int *rule, int year)
{
	int is_leap;
	long long t = __year_to_secs(year, &is_leap);
	int x, m, n, d;
	if (rule[0]!='M') {
		x = rule[1];
		if (rule[0]=='J' && (x < 60 || !is_leap)) x--;
		t += 86400 * x;
	} else {
		m = rule[1];
		n = rule[2];
		d = rule[3];
		t += __month_to_secs(m-1, is_leap);
		int wday = (int)((t + 4*86400) % (7*86400)) / 86400;
		int days = d - wday;
		if (days < 0) days += 7;
		if (n == 5 && days+28 >= days_in_month(m, is_leap)) n = 4;
		t += 86400 * (days + 7*(n-1));
	}
	t += rule[4];
	return t;
}

/* Determine the time zone in effect for a given time in seconds since the
 * epoch. It can be given in local or universal time. The results will
 * indicate whether DST is in effect at the queried time, and will give both
 * the GMT offset for the active zone/DST rule and the opposite DST. This
 * enables a caller to efficiently adjust for the case where an explicit
 * DST specification mismatches what would be in effect at the time. */

void __secs_to_zone(long long t, int local, int *isdst, long *offset, long *oppoff, const char **zonename)
{
	LOCK();

	do_tzset();

	if (zi) {
		size_t alt, i = scan_trans(t, local, &alt);
		if (i != -1) {
			*isdst = types[6*i+4];
			*offset = (int32_t)zi_read32(types+6*i);
			*zonename = (const char *)abbrevs + types[6*i+5];
			if (oppoff) *oppoff = (int32_t)zi_read32(types+6*alt);
			UNLOCK();
			return;
		}
	}

	if (!__daylight) goto std;

	/* FIXME: may be broken if DST changes right at year boundary?
	 * Also, this could be more efficient.*/
	long long y = t / 31556952 + 70;
	while (__year_to_secs(y, 0) > t) y--;
	while (__year_to_secs(y+1, 0) < t) y++;

	long long t0 = rule_to_secs(r0, y);
	long long t1 = rule_to_secs(r1, y);

	if (!local) {
		t0 += __timezone;
		t1 += dst_off;
	}
	if (t0 < t1) {
		if (t >= t0 && t < t1) goto dst;
		goto std;
	} else {
		if (t >= t1 && t < t0) goto std;
		goto dst;
	}
std:
	*isdst = 0;
	*offset = -__timezone;
	if (oppoff) *oppoff = -dst_off;
	*zonename = __tzname[0];
	UNLOCK();
	return;
dst:
	*isdst = 1;
	*offset = -dst_off;
	if (oppoff) *oppoff = -__timezone;
	*zonename = __tzname[1];
	UNLOCK();
}

static void __tzset(void)
{
	LOCK();
	do_tzset();
	UNLOCK();
}

weak_alias(__tzset, tzset);

const char *__tm_to_tzname(const struct tm *tm)
{
	const void *p = tm->tm_zone;
	LOCK();
	do_tzset();
	if (p != __utc && p != __tzname[0] && p != __tzname[1] &&
	    (!zi || (uintptr_t)p-(uintptr_t)abbrevs >= abbrevs_end - abbrevs))
		p = "";
	UNLOCK();
	return p;
}
