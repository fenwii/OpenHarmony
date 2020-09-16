#ifndef LIBC_H
#define LIBC_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct __locale_map;

struct __locale_struct {
	const struct __locale_map *cat[6];
};

#define __NEED_locale_t
#include <bits/alltypes.h>



#endif
