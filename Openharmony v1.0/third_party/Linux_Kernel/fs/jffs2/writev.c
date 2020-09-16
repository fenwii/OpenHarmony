/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright © 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 */

#include <linux/kernel.h>
#include "mtd_dev.h"
#include "nodelist.h"

int jffs2_flash_direct_writev(struct jffs2_sb_info *c, const struct kvec *vecs,
			      unsigned long count, loff_t to, size_t *retlen)
{
	unsigned long i;
	size_t totlen = 0, thislen;
	int ret = 0;

	for (i = 0; i < count; i++) {
		// writes need to be aligned but the data we're passed may not be
		// Observation suggests most unaligned writes are small, so we
		// optimize for that case.

		if (((vecs[i].iov_len & (sizeof(int) - 1))) ||
		(((unsigned long) vecs[i].iov_base & (sizeof(unsigned long) - 1)))) {
			// are there iov's after this one? Or is it so much we'd need
			// to do multiple writes anyway?
			if ((i + 1) < count || vecs[i].iov_len > 256) {
				// cop out and malloc
				unsigned long j;
				size_t sizetomalloc = 0, totvecsize = 0;
				char *cbuf, *cbufptr;

				for (j = i; j < count; j++)
					totvecsize += vecs[j].iov_len;

				// pad up in case unaligned
				sizetomalloc = totvecsize + sizeof(int) - 1;
				sizetomalloc &= ~(sizeof(int) - 1);
				cbuf = (char *) malloc(sizetomalloc);
				// malloc returns aligned memory
				if (!cbuf) {
					ret = -ENOMEM;
					goto writev_out;
				}
				cbufptr = cbuf;
				for (j = i; j < count; j++) {
					(void)memcpy_s(cbufptr, vecs[j].iov_len, vecs[j].iov_base, vecs[j].iov_len);
					cbufptr += vecs[j].iov_len;
				}
				ret = jffs2_flash_write(c, to, sizetomalloc, &thislen,
					(unsigned char *) cbuf);
				if (thislen > totvecsize) // in case it was aligned up
					thislen = totvecsize;
				totlen += thislen;
				free(cbuf);
				goto writev_out;
			} else {
				// otherwise optimize for the common case
				int buf[256/sizeof(int)]; // int, so int aligned
				size_t lentowrite;

				lentowrite = vecs[i].iov_len;
				// pad up in case its unaligned
				lentowrite += sizeof(int) - 1;
				lentowrite &= ~(sizeof(int) - 1);
				ret = memcpy_s(buf, sizeof(buf), vecs[i].iov_base, vecs[i].iov_len);
				if (ret != EOK)
					goto writev_out;

				ret = jffs2_flash_write(c, to, lentowrite, &thislen,
					(unsigned char *) &buf[0]);
				if (thislen > vecs[i].iov_len)
					thislen = vecs[i].iov_len;
			}
		} else {
				ret = jffs2_flash_write(c, to, vecs[i].iov_len, &thislen,
					vecs[i].iov_base);
		}
		totlen += thislen;
		if (ret || thislen != vecs[i].iov_len) break;
		to += vecs[i].iov_len;
	}

writev_out:
	if (retlen) *retlen = totlen;

	return ret;
}

int jffs2_flash_direct_write(struct jffs2_sb_info *c, loff_t ofs, size_t len,
			size_t *retlen, const u_char *buf)
{
	int ret;
	ret = c->mtd->write(c->mtd, ofs, len, (char *)buf);
	if (ret >= 0) {
		*retlen = ret;
		return 0;
	}
	*retlen = 0;
	return ret;
}
