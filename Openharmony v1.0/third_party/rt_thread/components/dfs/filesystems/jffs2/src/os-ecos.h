/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2002-2003 Free Software Foundation, Inc.
 *
 * Created by David Woodhouse <dwmw2@cambridge.redhat.com>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: os-ecos.h,v 1.24 2005/02/09 09:23:55 pavlov Exp $
 *
 */

#ifndef __JFFS2_OS_ECOS_H__
#define __JFFS2_OS_ECOS_H__
#include <asm/atomic.h>
#include <linux/compiler.h>
#include <string.h>
#include <linux/types.h>
#include "jffs2_config.h"
#include "los_event.h"
#include "los_mux.h"
#include "los_task.h"
#include "errno.h"
#include "jffs2_fs_i.h"
#include "jffs2_fs_sb.h"
#include "spinor.h"
#include "fileio.h"
#include "sys/uio.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

struct jffs2_dirent {
#ifdef CYGPKG_FILEIO_DIRENT_DTYPE

	unsigned long  d_type; // Only supported with FATFS, RAMFS, ROMFS,
	// and JFFS2.
	// d_type is not part of POSIX so
	// should be used with caution.
#endif
	char        d_name[JFFS2_NAME_MAX+1];
};

struct _inode;
struct super_block;

static inline unsigned int full_name_hash(const unsigned char * name, unsigned int len) {

	unsigned hash = 0;
	while (len--) {
		hash = (hash << 4) | (hash >> 28);
		hash ^= *(name++);
	}
	return hash;
}

#ifdef CYGOPT_FS_JFFS2_WRITE
#define jffs2_is_readonly(c) (0)
#else
#define jffs2_is_readonly(c) (1)
#endif

#define JFFS2_INODE_INFO(i) (&(i)->jffs2_i)
#define OFNI_EDONI_2SFFJ(f)  \
	((struct _inode *) ( ((char *)f) - ((char *)(&((struct _inode *)NULL)->jffs2_i)) ) )

#define JFFS2_F_I_SIZE(f) (OFNI_EDONI_2SFFJ(f)->i_size)
#define JFFS2_F_I_MODE(f) (OFNI_EDONI_2SFFJ(f)->i_mode)
#define JFFS2_F_I_UID(f) (OFNI_EDONI_2SFFJ(f)->i_uid)
#define JFFS2_F_I_GID(f) (OFNI_EDONI_2SFFJ(f)->i_gid)
#define JFFS2_F_I_CTIME(f) (OFNI_EDONI_2SFFJ(f)->i_ctime)
#define JFFS2_F_I_MTIME(f) (OFNI_EDONI_2SFFJ(f)->i_mtime)
#define JFFS2_F_I_ATIME(f) (OFNI_EDONI_2SFFJ(f)->i_atime)

#define JFFS2_F_I_RDEV_MIN(f) ((OFNI_EDONI_2SFFJ(f)->i_rdev)&0xff)
#define JFFS2_F_I_RDEV_MAJ(f) ((OFNI_EDONI_2SFFJ(f)->i_rdev)>>8)

#define get_seconds jffs2_get_timestamp

struct _inode {
	uint32_t		i_ino;
	int			    i_count;
	mode_t			i_mode;
	nlink_t			i_nlink; // Could we dispense with this?
	uid_t			i_uid;
	gid_t			i_gid;
	time_t			i_atime;
	time_t			i_mtime;
	time_t			i_ctime;
//	union {
		unsigned short	i_rdev; // For devices only
		struct _inode *	i_parent; // For directories only
		off_t		i_size; // For files only
//	};
	struct super_block *	i_sb;

	struct jffs2_inode_info	jffs2_i;

        struct _inode *		i_cache_prev; // We need doubly-linked?
        struct _inode *		i_cache_next;
};

#define JFFS2_SB_INFO(sb) (&(sb)->jffs2_sb)
#define OFNI_BS_2SFFJ(c)  \
	((struct super_block *) ( ((char *)c) - ((char *)(&((struct super_block *)NULL)->jffs2_sb)) ) )
typedef void* cyg_io_handle_t;

struct super_block {
	struct jffs2_sb_info	jffs2_sb;
	struct _inode *		s_root;
	unsigned long		s_mount_count;
	cyg_io_handle_t	s_dev;

#ifdef CYGOPT_FS_JFFS2_GCTHREAD
	UINT32			s_lock;             // Lock the inode cache
	EVENT_CB_S		s_gc_thread_flags;  // Communication with the gcthread
	unsigned int		s_gc_thread;
#endif

};

#ifndef BUG_ON
#define BUG_ON(x) do {if (unlikely(x)) BUG();} while (0)
#endif

// fs-ecos.c

int jffs2_oflag_to_accmode(int oflags);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __JFFS2_OS_ECOS_H__ */
