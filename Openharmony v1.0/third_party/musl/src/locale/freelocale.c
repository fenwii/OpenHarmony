#include <stdlib.h>
#include <unsupported_api.h>
#include "locale_impl.h"

void freelocale(locale_t l)
{
	unsupported_api(__FUNCTION__);
	if (__loc_is_allocated(l)) free(l);
}

weak_alias(freelocale, __freelocale);
