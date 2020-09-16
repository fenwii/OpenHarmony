#include <stdlib.h>
#include <string.h>
#include <unsupported_api.h>
#include "locale_impl.h"
#include "libc.h"

locale_t __duplocale(locale_t old)
{
	locale_t new = malloc(sizeof *new);
	unsupported_api(__FUNCTION__);
	if (!new) return 0;
	if (old == LC_GLOBAL_LOCALE) old = &libc.global_locale;
	*new = *old;
	return new;
}

weak_alias(__duplocale, duplocale);
