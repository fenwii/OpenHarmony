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
#include <linux/slab.h>
#include <stdlib.h>
#include "nodelist.h"

#if !defined(JFFS2NUM_FS_JFFS2_RAW_NODE_REF_CACHE_POOL_SIZE)
# define JFFS2NUM_FS_JFFS2_RAW_NODE_REF_CACHE_POOL_SIZE 0
#endif

int __init jffs2_create_slab_caches(void)
{
	return 0;

}

void jffs2_destroy_slab_caches(void)
{
	return;
}


struct jffs2_full_dirent *jffs2_alloc_full_dirent(int namesize)
{
	struct jffs2_full_dirent *ret;
	ret = kmalloc(sizeof(struct jffs2_full_dirent) + namesize, GFP_KERNEL);
	dbg_memalloc("%p\n", ret);
	return ret;
}

void jffs2_free_full_dirent(struct jffs2_full_dirent *x)
{
	dbg_memalloc("%p\n", x);
	kfree(x);
}

struct jffs2_full_dnode *jffs2_alloc_full_dnode(void)
{
	struct jffs2_full_dnode *ret;
	ret = malloc(sizeof(struct jffs2_full_dnode));
	dbg_memalloc("%p\n", ret);
	return ret;
}

void jffs2_free_full_dnode(struct jffs2_full_dnode *x)
{
	dbg_memalloc("%p\n", x);
	free(x);
}

struct jffs2_raw_dirent *jffs2_alloc_raw_dirent(void)
{
	struct jffs2_raw_dirent *ret;
	ret = malloc(sizeof(struct jffs2_raw_dirent));
	dbg_memalloc("%p\n", ret);
	return ret;
}

void jffs2_free_raw_dirent(struct jffs2_raw_dirent *x)
{
	dbg_memalloc("%p\n", x);
	free(x);
}

struct jffs2_raw_inode *jffs2_alloc_raw_inode(void)
{
	struct jffs2_raw_inode *ret;
	ret = malloc(sizeof(struct jffs2_raw_inode));
	dbg_memalloc("%p\n", ret);
	return ret;
}

void jffs2_free_raw_inode(struct jffs2_raw_inode *x)
{
	dbg_memalloc("%p\n", x);
	free(x);
}

struct jffs2_tmp_dnode_info *jffs2_alloc_tmp_dnode_info(void)
{
	struct jffs2_tmp_dnode_info *ret;
	ret = malloc(sizeof(struct jffs2_tmp_dnode_info));
	dbg_memalloc("%p\n",
		ret);
	return ret;
}

void jffs2_free_tmp_dnode_info(struct jffs2_tmp_dnode_info *x)
{
	dbg_memalloc("%p\n", x);
	free(x);
}

static struct jffs2_raw_node_ref *jffs2_alloc_refblock(void)
{
	struct jffs2_raw_node_ref *ret;

	ret = malloc(sizeof(struct jffs2_raw_node_ref) * (REFS_PER_BLOCK+1));
	if (ret) {
		int i = 0;
		for (i=0; i < REFS_PER_BLOCK; i++) {
			ret[i].flash_offset = REF_EMPTY_NODE;
			ret[i].next_in_ino = NULL;
		}
		ret[i].flash_offset = REF_LINK_NODE;
		ret[i].next_in_ino = NULL;
	}
	return ret;
}

int jffs2_prealloc_raw_node_refs(struct jffs2_sb_info *c,
				 struct jffs2_eraseblock *jeb, int nr)
{
	struct jffs2_raw_node_ref **p, *ref;
	int i = nr;

	dbg_memalloc("%d\n", nr);

	p = &jeb->last_node;
	ref = *p;

	dbg_memalloc("Reserving %d refs for block @0x%08x\n", nr, jeb->offset);

	/* If jeb->last_node is really a valid node then skip over it */
	if (ref && ref->flash_offset != REF_EMPTY_NODE)
		ref++;

	while (i) {
		if (!ref) {
			dbg_memalloc("Allocating new refblock linked from %p\n", p);
			ref = *p = jffs2_alloc_refblock();
			if (!ref)
				return -ENOMEM;
		}
		if (ref->flash_offset == REF_LINK_NODE) {
			p = &ref->next_in_ino;
			ref = *p;
			continue;
		}
		i--;
		ref++;
	}
	jeb->allocated_refs = nr;

	dbg_memalloc("Reserved %d refs for block @0x%08x, last_node is %p (%08x,%p)\n",
		  nr, jeb->offset, jeb->last_node, jeb->last_node->flash_offset,
		  jeb->last_node->next_in_ino);

	return 0;
}

void jffs2_free_refblock(struct jffs2_raw_node_ref *x)
{
	dbg_memalloc("%p\n", x);
	free(x);
}

struct jffs2_node_frag *jffs2_alloc_node_frag(void)
{
	struct jffs2_node_frag *ret;
	ret = malloc(sizeof(struct jffs2_node_frag));
	dbg_memalloc("%p\n", ret);
	return ret;
}

void jffs2_free_node_frag(struct jffs2_node_frag *x)
{
	dbg_memalloc("%p\n", x);
	free(x);
}


struct jffs2_inode_cache *jffs2_alloc_inode_cache(void)
{
	struct jffs2_inode_cache *ret;
	ret = malloc(sizeof(struct jffs2_inode_cache));;
	dbg_memalloc("%p\n", ret);
	return ret;
}

void jffs2_free_inode_cache(struct jffs2_inode_cache *x)
{
	dbg_memalloc("%p\n", x);
	kfree(x);
}

#ifdef CONFIG_JFFS2_FS_XATTR
struct jffs2_xattr_datum *jffs2_alloc_xattr_datum(void)
{
	struct jffs2_xattr_datum *xd;
	xd = malloc(sizeof(struct jffs2_xattr_datum));
	dbg_memalloc("%p\n", xd);
	if (!xd)
		return NULL;

	xd->class = RAWNODE_CLASS_XATTR_DATUM;
	xd->node = (void *)xd;
	INIT_LIST_HEAD(&xd->xindex);
	return xd;
}

void jffs2_free_xattr_datum(struct jffs2_xattr_datum *xd)
{
	dbg_memalloc("%p\n", xd);
	kfree(xd);
}

struct jffs2_xattr_ref *jffs2_alloc_xattr_ref(void)
{
	struct jffs2_xattr_ref *ref;
	ref = malloc(sizeof(struct jffs2_xattr_ref));
	dbg_memalloc("%p\n", ref);
	if (!ref)
		return NULL;

	ref->class = RAWNODE_CLASS_XATTR_REF;
	ref->node = (void *)ref;
	return ref;
}

void jffs2_free_xattr_ref(struct jffs2_xattr_ref *ref)
{
	dbg_memalloc("%p\n", ref);
	kfree(ref);
}
#endif
