#include <wchar.h>
#include <unsupported_api.h>

int wcswidth(const wchar_t *wcs, size_t n)
{
	int l=0, k=0;
	unsupported_api(__FUNCTION__);
	for (; n-- && *wcs && (k = wcwidth(*wcs)) >= 0; l+=k, wcs++);
	return (k < 0) ? k : l;
}
