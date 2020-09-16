#include "stdio_impl.h"
#include <string.h>
#include "menuconfig.h"
#ifdef LOSCFG_LLTSER
#include "gcov_ser.h"
#endif
#include "fs/fs.h"
#include "fs/file.h"

#define MIN(a,b) ((a)<(b) ? (a) : (b))

size_t fread(void *restrict destv, size_t size, size_t nmemb, FILE *restrict f)
{
	unsigned char *dest = destv;
	size_t len = size*nmemb, l = len, k;
	if (!size) nmemb = 0;

	FLOCK(f);
#ifdef LOSCFG_LLTSER
	GCOV_FREAD(f, destv, size, nmemb);
#endif
	f->mode |= f->mode-1;

	if (f->rpos != f->rend) {
		/* First exhaust the buffer. */
		k = MIN(f->rend - f->rpos, l);
		memcpy(dest, f->rpos, k);
		f->rpos += k;
		dest += k;
		l -= k;
	}
	
	/* Read the remainder directly */
	for (; l; l-=k, dest+=k) {
		k = __toread(f) ? 0 : f->read(f, dest, l);
		if (!k) {
			FUNLOCK(f);
			return (len-l)/size;
		}
	}

	FUNLOCK(f);
	return nmemb;
}

weak_alias(fread, fread_unlocked);
