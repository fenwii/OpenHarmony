/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright © 2001-2007 Red Hat, Inc.
 * Copyright © 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 */

#include <linux/delay.h>
#include "nodelist.h"

int calculate_inocache_hashsize(uint32_t flash_size)
{
	/*
	 * Pick a inocache hash size based on the size of the medium.
	 * Count how many megabytes we're dealing with, apply a hashsize twice
	 * that size, but rounding down to the usual big powers of 2. And keep
	 * to sensible bounds.
	 */

	int size_mb = flash_size / 1024 / 1024;
	int hashsize = (size_mb * 2) & ~0x3f;

	if (hashsize < INOCACHE_HASHSIZE_MIN)
		return INOCACHE_HASHSIZE_MIN;
	if (hashsize > INOCACHE_HASHSIZE_MAX)
		return INOCACHE_HASHSIZE_MAX;

	return hashsize;
}
