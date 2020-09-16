/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2001-2003 Free Software Foundation, Inc.
 *
 * Created by Dominic Ostrowski <dominic.ostrowski@3glab.com>
 * Contributors: David Woodhouse, Nick Garnett, Richard Panton.
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: fs-ecos.c,v 1.44 2005/07/24 15:29:57 dedekind Exp $
 *
 */

#include <stdio.h>    //prife for SEEK_SET SEEK_CUR SEEK_END
#include <linux/kernel.h>
#include <string.h>
#include <linux/pagemap.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include "mtd_list.h"
#include "jffs2/nodelist.h"
#include "los_crc32.h"
#include "jffs2/compr.h"
#include "port/fcntl.h"
#include "porting.h"
#include "spinor.h"
#include "limits.h"
#include "los_process_pri.h"
#include "capability_type.h"
#include "capability_api.h"
#include "mtd_partition.h"
#include "vfs_jffs2.h"

// Filesystem operations
static int jffs2_mount(cyg_mtab_entry *mte, int partition_num);
static int jffs2_umount(cyg_mtab_entry *mte);
static int jffs2_open (cyg_mtab_entry *mte, const char *name, int flags,
                    int mode,  cyg_file *fte);
static int jffs2_ops_unlink(cyg_mtab_entry *mte, const char *name);
static int jffs2_ops_mkdir(cyg_mtab_entry *mte, const char *name, int mode);
static int jffs2_ops_rmdir(cyg_mtab_entry *mte, const char *name);
static int jffs2_ops_rename(cyg_mtab_entry *mte, const char *name1, const char *name2);
static int jffs2_opendir(cyg_mtab_entry *mte, const char *name, cyg_file *fte);
static int jffs2_stat(cyg_mtab_entry *mte, const char *name, struct jffs2_stat *buf);
static int jffs2_fo_chattr(cyg_mtab_entry *mte, const char *name, iattr *attr);

// File operations
static int jffs2_fo_read(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
static int jffs2_fo_write(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
static int jffs2_fo_lseek(struct CYG_FILE_TAG *fp, off_t *apos, int whence);
static int jffs2_fo_close(struct CYG_FILE_TAG *fp);

// Directory operations
static int jffs2_fo_dirread(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
static int jffs2_fo_dirlseek(struct CYG_FILE_TAG *fp, off_t *pos, int whence);

static int jffs2_read_inode (struct _inode *inode);
static void jffs2_clear_inode (struct _inode *inode);
static int jffs2_truncate_file (struct _inode *inode);
static int jffsfs_IsPathDivider(char ch);
static int jffs_check_path(const char *path);
static unsigned int CheckPermission(struct _inode *node, int accMode);
int jffs2_chattr (struct _inode *dir_i, const unsigned char *d_name, iattr *attr, struct _inode *node_old);


struct MtdNorDev jffs_part[CONFIG_MTD_PATTITION_NUM];
//==========================================================================
// STATIC VARIABLES !!!

static unsigned char gc_buffer[PAGE_CACHE_SIZE];	//avoids malloc when user may be under memory pressure
static unsigned char n_fs_mounted = 0;  // a counter to track the number of jffs2 instances mounted

#define JFFS_PATH_DIVIDERS  "/"
//==========================================================================
// Directory operations

struct jffs2_dirsearch {
	struct _inode *dir;    // directory to search
	const unsigned char *path;  // path to follow
	struct _inode *node;        // Node found
	const unsigned char *name;  // last name fragment used
	int namelen;            // name fragment length
	int last;            // last name in path?
	int accMode;            // access mode
};

typedef struct jffs2_dirsearch jffs2_dirsearch;

//==========================================================================
// Ref count and nlink management

// FIXME: This seems like real cruft. Wouldn't it be better just to do the
// right thing?
static void icache_evict(struct _inode *root_i, struct _inode *i)
{
	struct _inode *this = root_i;
	struct _inode *next = NULL;
	struct _inode *temp = NULL;
	struct jffs2_inode_info *f = NULL;
	jffs_lock();
 restart:
	D2(PRINTK("icache_evict\n"));
	// If this is an absolute search path from the root,
	// remove all cached inodes with i_count of zero (these are only
	// held where needed for dotdot filepaths)

	while (this) {
		next = this->i_cache_next;
		if (this != i && this->i_count == 0) {
			struct _inode *parent = this->i_parent;

			if (this->i_cache_next)
				this->i_cache_next->i_cache_prev = this->i_cache_prev;
			if (this->i_cache_prev)
				this->i_cache_prev->i_cache_next = this->i_cache_next;
			jffs2_clear_inode(this);
			f = JFFS2_INODE_INFO(this);
			(void)mutex_destroy(&(f->sem));
			(void)memset_s(this, sizeof(*this), 0x5a, sizeof(*this));
			temp = this;
			free(this);
			if (parent && parent != temp) {
				parent->i_count--;
				this = root_i;
				goto restart;
			}
		}
		this = next;
	}
	jffs_unlock();
}

//==========================================================================
// Directory search

// -------------------------------------------------------------------------
// init_dirsearch()
// Initialize a dirsearch object to start a search

void init_dirsearch(jffs2_dirsearch * ds,
	struct _inode *dir, const unsigned char *name,  int flags)
{
	D2(PRINTK("init_dirsearch name = %s\n", name));
	D2(PRINTK("init_dirsearch dir = %x\n", dir));

	dir->i_count++;
	ds->dir = dir;
	ds->path = name;
	ds->node = dir;
	ds->name = name;
	ds->namelen = 0;
	ds->last = false;
	ds->accMode = flags;
}

// -------------------------------------------------------------------------
// find_entry()
// Search a single directory for the next name in a path and update the
// dirsearch object appropriately.

static int find_entry(jffs2_dirsearch * ds)
{
	struct _inode *dir = ds->dir;
	const unsigned char *name = ds->path;
	const unsigned char *n = name;
	char namelen = 0;
	struct _inode *d;
	int accMode = 0;

	// Isolate the next element of the path name.
	while (*n != '\0' && *n != '/') {
		n++;
		namelen++;
	}

	// Check if this is the last path element.
	while( *n == '/') n++;
	if (*n == '\0')
		ds->last = true;

	// update name in dirsearch object
	ds->name = name;
	ds->namelen = namelen;
	if (name[0] == '.')
		switch (namelen) {
		default:
			break;
		case 2:
			// Dot followed by not Dot, treat as any other name
			if (name[1] != '.')
				break;
			// Dot Dot
			// Move back up the search path
			ds->dir = ds->node;
			ds->node = ds->dir->i_parent;
			ds->node->i_count++;
			return ENOERR;
		case 1:
			// Dot is consumed
			ds->node = ds->dir;
			ds->dir->i_count++;
			return ENOERR;
		}

	// Here we have the name and its length set up.
	// Search the directory for a matching entry
	d = jffs2_lookup(dir, name, namelen);

	if (d == NULL) {
		return ENOENT;
	}
	if (IS_ERR(d)) {
		return -(int)(PTR_ERR(d));}

	// If it's a new directory inode, increase refcount on its parent
	if (S_ISDIR(d->i_mode) && !d->i_parent) {
		d->i_parent = dir;
		dir->i_count++;
	}

	accMode = (ds->last) ? ds->accMode : EXEC_OP;

	if (CheckPermission(d, accMode)) {
		jffs2_iput(d);
		return EACCES;
	}

	// pass back the node we have found
	ds->node = d;
	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_find()
// Main interface to directory search code. This is used in all file
// level operations to locate the object named by the pathname.

// Returns with use count incremented on both the sought object and
// the directory it was found in
static int jffs2_find(jffs2_dirsearch * d)
{
	int err;

	D2(PRINTK("jffs2_find for path =%s\n", d->path));
	// Short circuit empty paths
	if (*(d->path) == '\0') {
		d->node->i_count++;
		return ENOERR;
	}

	// iterate down directory tree until we find the object
	// we want.
	for (;;) {
		// check that we really have a directory
		if (!S_ISDIR(d->dir->i_mode)) {
			return ENOTDIR;
		}

		err = find_entry(d);
		if (err != ENOERR) {
			return err;
		}
		if (d->last)
			return ENOERR;

		/* We're done with it, although it we found a subdir that
		   will have caused the refcount to have been increased */
		jffs2_iput(d->dir);

		// Update dirsearch object to search next directory.
		d->dir = d->node;
		d->path += d->namelen;
		while (*(d->path) == '/')
			d->path++;    // skip dirname separators
	}
}


//==========================================================================
// Filesystem operations
// -------------------------------------------------------------------------
// jffs2_mount()
// Process a mount request. This mainly creates a root for the
// filesystem.
static int jffs2_read_super(struct super_block *sb)
{
	int err;
	struct jffs2_sb_info *c;
	struct MtdNorDev *device;

	c = JFFS2_SB_INFO(sb);
	device = (struct MtdNorDev*)(sb->s_dev);

	/* initialize mutex lock */
	(void)mutex_init(&c->alloc_sem);
	(void)mutex_init(&c->erase_free_sem);
	spin_lock_init(&c->erase_completion_lock);
	spin_lock_init(&c->inocache_lock);

	/* sector size is the erase block size */
	c->sector_size = device->blockSize;
	c->flash_size  = (device->blockEnd - device->blockStart + 1) * device->blockSize;
	c->cleanmarker_size = sizeof(struct jffs2_unknown_node);
	err = jffs2_do_mount_fs(c);

	if (err) {
		(void)mutex_destroy(&c->alloc_sem);
		(void)mutex_destroy(&c->erase_free_sem);
		return -err;
	}
	D1(printk(KERN_DEBUG "jffs2_read_super(): Getting root inode\n"));

	sb->s_root = jffs2_iget(sb, 1);

	if (IS_ERR(sb->s_root)) {
		D1(printk(KERN_WARNING "get root inode failed\n"));
		err = PTR_ERR(sb->s_root);
		sb->s_root = NULL;
		goto out_nodes;
	}
	return 0;

out_nodes:
	jffs2_free_ino_caches(c);
	jffs2_free_raw_node_refs(c);
	free(c->blocks);
	(void)mutex_destroy(&c->alloc_sem);
	(void)mutex_destroy(&c->erase_free_sem);

	return err;
}

static int jffs2_mount(cyg_mtab_entry *mte, int partition_num)
{
	struct super_block *jffs2_sb = NULL;
	struct jffs2_sb_info *c = NULL;
	mtd_partition *current_node = GetSpinorPartitionHead();
	LOS_DL_LIST *patition_head = NULL;
	int err;
	struct MtdDev *spinor_mtd = NULL;

	jffs2_dbg(1, "begin los_jffs2_mount:%d\n", partition_num);

	jffs2_sb = malloc(sizeof (struct super_block));

	if (jffs2_sb == NULL) {
		return ENOMEM;
	}
	c = JFFS2_SB_INFO(jffs2_sb);
	(void)memset_s(jffs2_sb, sizeof (struct super_block), 0, sizeof (struct super_block));
	patition_head = &(GetSpinorPartitionHead()->node_info);
	LOS_DL_LIST_FOR_EACH_ENTRY(current_node,patition_head, mtd_partition, node_info) {
		if (current_node->patitionnum == partition_num)
			break;
	}
	spinor_mtd = GetMtd("spinor");
	if (spinor_mtd == NULL) {
		free(jffs2_sb);
		return EPERM;
	}
	jffs_part[partition_num].blockEnd = current_node->end_block;
	jffs_part[partition_num].blockSize = spinor_mtd->eraseSize;
	jffs_part[partition_num].blockStart = current_node->start_block;
	(void)FreeMtd(spinor_mtd);
	jffs2_sb->jffs2_sb.mtd = current_node->mtd_info;
	jffs2_sb->s_dev = (cyg_io_handle_t)(&jffs_part[partition_num]);

	c->flash_size  = (current_node->end_block - current_node->start_block + 1) * spinor_mtd->eraseSize;
	c->inocache_hashsize = calculate_inocache_hashsize(c->flash_size);
	c->sector_size = spinor_mtd->eraseSize;

	jffs2_dbg(1, "C mtd_size:%d,mtd-erase:%d,blocks:%d,hashsize:%d\n",
		c->flash_size, c->sector_size, c->flash_size / c->sector_size, c->inocache_hashsize);

	c->inocache_list = malloc(sizeof(struct jffs2_inode_cache *) * c->inocache_hashsize);
	if (c->inocache_list == NULL) {
		free(jffs2_sb);
		return ENOMEM;
	}
	(void)memset_s(c->inocache_list, sizeof(struct jffs2_inode_cache *) * c->inocache_hashsize, 0,
		sizeof(struct jffs2_inode_cache *) * c->inocache_hashsize);
	if (n_fs_mounted++ == 0) {
		(void)jffs2_create_slab_caches(); // No error check, cannot fail
		(void)jffs2_compressors_init();
	}

	err = jffs2_read_super(jffs2_sb);

	if (err) {
		if (--n_fs_mounted == 0) {
			jffs2_destroy_slab_caches();
			(void)jffs2_compressors_exit();
		}

		free(jffs2_sb);
		free(c->inocache_list);
		c->inocache_list = NULL;
		return err;
	}
	jffs2_sb->s_root->i_parent = jffs2_sb->s_root;    // points to itself, no dotdot paths above mountpoint
	jffs2_sb->s_root->i_cache_prev = NULL;    // root inode, so always null
	jffs2_sb->s_root->i_cache_next = NULL;
	jffs2_sb->s_root->i_count = 1;    // Ensures the root inode is always in ram until umount

#ifdef CYGOPT_FS_JFFS2_GCTHREAD
	jffs2_start_garbage_collect_thread(c);
#endif

	mte->data = (CYG_ADDRWORD)jffs2_sb;
	jffs2_sb->s_mount_count++;
	mte->root = (cyg_dir)jffs2_sb->s_root;
	D2(PRINTK("jffs2_mounted superblock at %x\n", mte->root));
	return ENOERR;
}


// -------------------------------------------------------------------------
// jffs2_umount()
// Unmount the filesystem.

static int jffs2_umount(cyg_mtab_entry *mte)
{
	struct _inode *root = (struct _inode *) mte->root;
	struct super_block *jffs2_sb = root->i_sb;
	struct jffs2_sb_info *c = JFFS2_SB_INFO(jffs2_sb);
	struct jffs2_full_dirent *fd, *next;

	D2(PRINTK("jffs2_umount\n"));

	// Only really umount if this is the only mount
	if (jffs2_sb->s_mount_count == 1) {
		icache_evict(root, NULL);
		if (root->i_cache_next != NULL) {
			struct _inode *inode = root;
			while (inode) {
				PRINTK("Ino #%u has use count %d\n",
					   inode->i_ino, inode->i_count);
				inode = inode->i_cache_next;
			}
			// root icount was set to 1 on mount
			return EBUSY;
		}
		if (root->i_count != 1) {
			PRINTK("Ino #1 has use count %d\n",
				   root->i_count);
			return EBUSY;
		}
#ifdef CYGOPT_FS_JFFS2_GCTHREAD
		jffs2_stop_garbage_collect_thread(c);
#endif
		jffs2_iput(root); // Time to free the root inode

		// free directory entries
		for (fd = root->jffs2_i.dents; fd; fd = next) {
			next = fd->next;
			jffs2_free_full_dirent(fd);
		}

		free(root);

		// Clean up the super block and root inode
		jffs2_free_ino_caches(c);
		jffs2_free_raw_node_refs(c);
		free(c->blocks);
		c->blocks = NULL;
		free(c->inocache_list);
		c->inocache_list = NULL;

		(void)mutex_destroy(&c->alloc_sem);
		(void)mutex_destroy(&c->erase_free_sem);
		free(jffs2_sb);
		// Clear superblock & root pointer
		mte->root = 0;
		mte->data = 0;
		// That's all folks.
		D2(PRINTK("jffs2_umount No current mounts\n"));
	} else {
		jffs2_sb->s_mount_count--;
	}
	if (--n_fs_mounted == 0) {
		jffs2_destroy_slab_caches();
		(void)jffs2_compressors_exit();
	}
	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_open()
// Open a file for reading or writing.

static int jffs2_open (cyg_mtab_entry *mte, const char *name, int flags,
                    int mode,  cyg_file *fte)
{
	jffs2_dirsearch ds;
	struct _inode *node = NULL;
	int err;
	jffs2_dbg(1, "open %s at mode: %d\n",name,mode);

#ifndef CYGOPT_FS_JFFS2_WRITE
	if (flags & (O_CREAT | O_TRUNC | O_WRONLY))
		return EROFS;
#endif

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *)mte->root,
		(const unsigned char *) name,  jffs2_oflag_to_accmode(flags));

	err = jffs2_find(&ds);

	if (err == ENOENT) {
#ifdef CYGOPT_FS_JFFS2_WRITE
		if (ds.last && (flags & O_CREAT)) {

			// No node there, if the O_CREAT bit is set then we must
			// create a new one. The dir and name fields of the dirsearch
			// object will have been updated so we know where to put it.
			err = jffs2_create(ds.dir, ds.name, mode, &node);
		if (err != 0) {
			//Possible orphaned inode on the flash - but will be gc'd
			jffs2_iput(ds.dir);
			return -err;
		}

		err = ENOERR;
		}
#endif
	} else if (err == ENOERR) {
		// The node exists. If the O_CREAT and O_EXCL bits are set, we
		// must fail the open.

		if ((flags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL)) {
			jffs2_iput(ds.node);
			err = EEXIST;
		}  else
			node = ds.node;
	} else if (err == EACCES) {
		jffs2_iput(ds.dir);
		return -err;
	}

	D1(PRINTK("%s, %d, uid %d gid %d mode %d%d%d\n", __FUNCTION__, __LINE__, node->i_uid, node->i_gid,
		(node->i_mode >> JFFS2_USER_SHFIT) & JFFS2_MODE_ALL, (node->i_mode >> JFFS2_GROUP_SHFIT) & JFFS2_MODE_ALL,
		(node->i_mode) & JFFS2_MODE_ALL));

	// Finished with the directory now
	jffs2_iput(ds.dir);

	if (err != ENOERR) {
		return err;
	}
	// Check that we actually have a file here
	if (S_ISDIR(node->i_mode)) {
		jffs2_iput(node);
		return EISDIR;
	}

	// If the O_TRUNC bit is set we must clean out the file data.
	if (flags & O_TRUNC) {
#ifdef CYGOPT_FS_JFFS2_WRITE
		err = jffs2_truncate_file(node);
		if (err) {
			jffs2_iput(node);
			return err;
		}
#else
		jffs2_iput(node);
		return EROFS;
#endif
	}

	// Initialise the file object
	fte->f_flag = flags & JFFS2_O_ACCMODE;
	fte->f_offset = (flags & O_APPEND) ? node->i_size : 0;
	fte->f_data = (UINTPTR) node;

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_ops_unlink()
// Remove a file link from its directory.

static int jffs2_ops_unlink(cyg_mtab_entry *mte, const char *name)
{
	jffs2_dirsearch ds;
	int err;

	jffs2_dbg(1, "unlink: %s\n", name);

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *) mte->root,
		(const unsigned char *)name, 0);

	err = jffs2_find(&ds);

	if (err != ENOERR) {
		jffs2_iput(ds.dir);
		return err;
	}

	if (CheckPermission(ds.dir, WRITE_OP | EXEC_OP)) {
		jffs2_iput(ds.dir);
		jffs2_iput(ds.node);
		return EACCES;
	}

	// Cannot unlink directories, use rmdir() instead
	if (S_ISDIR(ds.node->i_mode)) {
		jffs2_iput(ds.dir);
		jffs2_iput(ds.node);
		return EISDIR;
	}

	// Delete it from its directory

	err = jffs2_unlink(ds.dir, ds.node, ds.name);
	jffs2_iput(ds.dir);
	jffs2_iput(ds.node);

	return -err;
}

// -------------------------------------------------------------------------
// jffs2_ops_mkdir()
// Create a new directory.

static int jffs2_ops_mkdir(cyg_mtab_entry *mte, const char *name,int mode)
{
	jffs2_dirsearch ds;
	int err;

	jffs2_dbg(1, "mkdir: %s\n",name);

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *)mte->root, (const unsigned char *)name, 0);

	err = jffs2_find(&ds);
	if (err == ENOENT) {
		if (ds.last) {
			// The entry does not exist, and it is the last element in
			// the pathname, so we can create it here.
			err = jffs2_mkdir(ds.dir, ds.name, mode);
		}
		// If this was not the last element, then an intermediate
		// directory does not exist.
	} else {
		// If there we no error, something already exists with that
		// name, so we cannot create another one.
		if (err == ENOERR) {
			jffs2_iput(ds.node);
			err = -EEXIST;
		}
	}
	jffs2_iput(ds.dir);
	if (err == EACCES) {
		err = -EACCES;
	}
	return err;
}

// -------------------------------------------------------------------------
// jffs2_ops_rmdir()
// Remove a directory.

static int jffs2_ops_rmdir(cyg_mtab_entry *mte, const char *name)
{
	jffs2_dirsearch ds;
	int err;

	jffs2_dbg(1, "rmdir: %s\n",name);

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *)mte->root, (const unsigned char *)name, 0);

	err = jffs2_find(&ds);
	if (err != ENOERR) {
		jffs2_iput(ds.dir);
		return -err;
	}

	if (CheckPermission(ds.dir, WRITE_OP | EXEC_OP)) {
		jffs2_iput(ds.dir);
		jffs2_iput(ds.node);
		return -EACCES;
	}

	// Check that this is actually a directory.
	if (!S_ISDIR(ds.node->i_mode)) {
		jffs2_iput(ds.dir);
		jffs2_iput(ds.node);
		return -ENOTDIR;
	}

	err = jffs2_rmdir(ds.dir, ds.node, ds.name);

	jffs2_iput(ds.dir);
	jffs2_iput(ds.node);
	return err;
}

// -------------------------------------------------------------------------
// jffs2_ops_rename()
// Rename a file/dir.

static int jffs2_ops_rename(cyg_mtab_entry *mte, const char *name1, const char *name2)
{
	jffs2_dirsearch ds1, ds2;
	int err;
	struct jffs2_inode_info *f = NULL;
	struct jffs2_full_dirent *fd = NULL;
	unsigned int oldrelpath_len, newrelpath_len, cmp_namelen;

	jffs2_dbg(1, "from: %s to: %s\n", name1, name2);

	if (jffs_check_path(name1))
		return ENAMETOOLONG;

	if (jffs_check_path(name2))
		return ENAMETOOLONG;

	oldrelpath_len = strlen(name1);
	newrelpath_len = strlen(name2);
	if (!oldrelpath_len || !newrelpath_len)
		return EPERM;

	cmp_namelen = (oldrelpath_len <= newrelpath_len) ? oldrelpath_len : newrelpath_len;
	if ((!strncmp(name1, name2, cmp_namelen)) && ((name1[cmp_namelen] == '/') || (name2[cmp_namelen] == '/'))) {
		err = -EPERM;
		return err;
	}

	init_dirsearch(&ds1, (struct _inode *)mte->root,
		(const unsigned char *)name1, 0);

	err = jffs2_find(&ds1);

	if (err != ENOERR) {
		jffs2_iput(ds1.dir);
		return err;
	}

	if (CheckPermission(ds1.dir, WRITE_OP | EXEC_OP)) {
		jffs2_iput(ds1.dir);
		jffs2_iput(ds1.node);
		return -EACCES;
	}


	init_dirsearch(&ds2, (struct _inode *)mte->root,
		(const unsigned char *)name2, 0);

	err = jffs2_find(&ds2);

	// Allow through renames to non-existent objects.
	if (ds2.last && err == ENOENT) {
		ds2.node = NULL;
		err = ENOERR;
	} else if ((err == ENOERR) && S_ISDIR(ds2.node->i_mode)) {
		f = JFFS2_INODE_INFO(ds2.node);
		for (fd = f->dents; fd; fd = fd->next) {
			if (fd->ino) {
				jffs2_iput(ds2.node);
				err = ENOTEMPTY;
				break;
			}
		}
	}
	if (err != ENOERR) {
		jffs2_iput(ds1.dir);
		jffs2_iput(ds1.node);
		jffs2_iput(ds2.dir);
		return err;
	}

	if (CheckPermission(ds2.dir, WRITE_OP | EXEC_OP)) {
		jffs2_iput(ds1.dir);
		jffs2_iput(ds1.node);
		jffs2_iput(ds2.dir);
		jffs2_iput(ds2.node);
		return -EACCES;
	}

	// Null rename, just return
	if (ds1.node == ds2.node) {
		err = ENOERR;
		goto out;
	}

	// First deal with any entry that is at the destination
	if (ds2.node != NULL) {
		// Check that we are renaming like-for-like

		if (!S_ISDIR(ds1.node->i_mode) && S_ISDIR(ds2.node->i_mode)) {
			err = EISDIR;
			goto out;
		}

		if (S_ISDIR(ds1.node->i_mode) && !S_ISDIR(ds2.node->i_mode)) {
			err = ENOTDIR;
			goto out;
		}

		// Now delete the destination directory entry
		/* Er, what happened to atomicity of rename()? */
		err = -jffs2_unlink(ds2.dir, ds2.node, ds2.name);

		if (err != 0)
			goto out;
	}
	// Now we know that there is no clashing node at the destination,
	// make a new direntry at the destination and delete the old entry
	// at the source.

	err = -jffs2_rename(ds1.dir, ds1.node, ds1.name, ds2.dir, ds2.name);

	// Update directory times
	if (!err)
		ds1.dir->i_ctime =
			ds1.dir->i_mtime =
			ds2.dir->i_ctime = ds2.dir->i_mtime = jffs2_get_timestamp();
 out:
	jffs2_iput(ds1.dir);
	if (S_ISDIR(ds1.node->i_mode)) {
		/* Renamed a directory to elsewhere... so fix up its
		   i_parent pointer and the i_counts of its old and
		   new parents. */
		jffs2_iput(ds1.node->i_parent);
		ds1.node->i_parent = ds2.dir;
		/* We effectively increase its use count by not... */
	} else {
		jffs2_iput(ds2.dir); /* ... doing this */
	}
	jffs2_iput(ds1.node);
	if (ds2.node != NULL)
		jffs2_iput(ds2.node);

	return err;
}

static int jffsfs_IsPathDivider(char ch)
{
	const char *str = JFFS_PATH_DIVIDERS;
	while (*str) {
		if (*str == ch)
			return 1;
		str++;
	}
	return 0;
}

// -------------------------------------------------------------------------
// jffs2_opendir()
// Open a directory for reading.

static int jffs2_opendir(cyg_mtab_entry *mte, const char *name, cyg_file *fte)
{
	jffs2_dirsearch ds;
	int err;

	jffs2_dbg(1, "opendir: %s\n",name);

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *) mte->root,
		(const unsigned char *) name, jffs2_oflag_to_accmode(O_RDONLY | O_EXECVE));

	err = jffs2_find(&ds);

	jffs2_iput(ds.dir);

	if (err != ENOERR) {
		return err;
	}

	// check it is really a directory.
	if (!S_ISDIR(ds.node->i_mode)) {
		jffs2_iput(ds.node);
		return ENOTDIR;
	}

	// Initialize the file object, setting the f_ops field to a
	// special set of file ops.

	fte->f_flag = 0;
	fte->f_offset = 0;
	fte->f_data = (UINTPTR) ds.node;

	return ENOERR;
}

static int jffs2_fo_chattr(cyg_mtab_entry *mte, const char *name, iattr *attr)
{
	jffs2_dirsearch ds;
	int ret;
	int flags = 0;
	D2(PRINTK("jffs2_chattr: %s\n", name));

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *)mte->root, (const unsigned char *)name, flags);

	ret = jffs2_find(&ds);
	if (ret == ENOERR) {
		ret = jffs2_chattr(ds.dir, ds.name, attr, ds.node);
		jffs2_iput(ds.node);
	} else {
		ret = -ret;
	}
	jffs2_iput(ds.dir);
	return ret;
}

// -------------------------------------------------------------------------
// jffs2_stat()
// Get struct stat info for named object.

static int jffs2_stat(cyg_mtab_entry *mte, const char *name, struct jffs2_stat *buf)
{
	jffs2_dirsearch ds;
	int err;

	jffs2_dbg(1, "get %s stat\n", name);

	if (jffs_check_path(name))
		return ENAMETOOLONG;

	init_dirsearch(&ds, (struct _inode *)mte->root,
		(const unsigned char *) name, 0);

	err = jffs2_find(&ds);
	jffs2_iput(ds.dir);

	if (err != ENOERR)
		return err;

	// Fill in the status
	buf->st_mode = ds.node->i_mode;
	buf->st_ino = ds.node->i_ino;
	buf->st_dev = 0;
	buf->st_nlink = ds.node->i_nlink;
	buf->st_uid = ds.node->i_uid;
	buf->st_gid = ds.node->i_gid;
	buf->st_size = ds.node->i_size;
	buf->sddst_atime = ds.node->i_atime;
	buf->sddst_mtime = ds.node->i_mtime;
	buf->sddst_ctime = ds.node->i_ctime;

	jffs2_iput(ds.node);

	return ENOERR;
}

//==========================================================================
// File operations

// -------------------------------------------------------------------------
// jffs2_fo_read()
// Read data from the file.

static int jffs2_fo_read(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio)
{
	struct _inode *inode = (struct _inode *) fp->f_data;
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	int i;
	ssize_t resid = uio->uio_resid;
	off_t pos = fp->f_offset;

	mutex_lock(&f->sem);

	// Loop over the io vectors until there are none left
	for (i = 0; i < uio->uio_iovcnt && pos < inode->i_size; i++) {
		int ret;
		jffs2_iovec *iov = &uio->uio_iov[i];
		off_t len = min((iov->iov_len), (inode->i_size - pos));

		D2(PRINTK("jffs2_fo_read inode size %d\n", inode->i_size));

		ret = jffs2_read_inode_range(c, f,(unsigned char *) iov->iov_base, pos,len);
		if (ret) {
			D1(PRINTK
			   ("jffs2_fo_read(): read_inode_range failed %d\n",
				ret));
			uio->uio_resid = resid;
			mutex_unlock(&f->sem);
			return -ret;
		}
		resid -= len;
		pos += len;
	}

	// We successfully read some data, update the node's access time
	// and update the file offset and transfer residue.

	inode->i_atime = jffs2_get_timestamp();

	uio->uio_resid = resid;
	fp->f_offset = pos;

	mutex_unlock(&f->sem);

	return ENOERR;
}

#ifdef CYGOPT_FS_JFFS2_WRITE
// -------------------------------------------------------------------------
// jffs2_fo_write()
// Write data to file.
static int jffs2_extend_file (struct _inode *inode, struct jffs2_raw_inode *ri,
			   unsigned long offset)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_full_dnode *fn;
	uint32_t alloc_len;
	int ret = 0;

	/* Make new hole frag from old EOF to new page */
	D1(printk(KERN_DEBUG "Writing new hole frag 0x%x-0x%x between current EOF and new page\n",
		  (unsigned int)inode->i_size, offset));

	ret = jffs2_reserve_space(c, sizeof(*ri), &alloc_len, ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);
	if (ret)
		return ret;

	mutex_lock(&f->sem);

	ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri->totlen = cpu_to_je32(sizeof(*ri));
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, (sizeof(struct jffs2_unknown_node)-4)));

	ri->version = cpu_to_je32(++f->highest_version);
	ri->isize = cpu_to_je32(max((uint32_t)inode->i_size, offset));

	ri->offset = cpu_to_je32(inode->i_size);
	ri->dsize = cpu_to_je32((offset - inode->i_size));
	ri->csize = cpu_to_je32(0);
	ri->compr = JFFS2_COMPR_ZERO;
	ri->node_crc = cpu_to_je32(crc32(0, ri, (sizeof(*ri)-8)));
	ri->data_crc = cpu_to_je32(0);

	fn = jffs2_write_dnode(c, f, ri, NULL, 0, ALLOC_NORMAL);
	jffs2_complete_reservation(c);
	if (IS_ERR(fn)) {
		ret = PTR_ERR(fn);
		(void)mutex_unlock(&f->sem);
		return ret;
	}
	ret = jffs2_add_full_dnode_to_inode(c, f, fn);
	if (f->metadata) {
		jffs2_mark_node_obsolete(c, f->metadata->raw);
		jffs2_free_full_dnode(f->metadata);
		f->metadata = NULL;
	}
	if (ret) {
		D1(printk(KERN_DEBUG "Eep. add_full_dnode_to_inode() failed in prepare_write, returned %d\n", ret));
		jffs2_mark_node_obsolete(c, fn->raw);
		jffs2_free_full_dnode(fn);
		mutex_unlock(&f->sem);
		return ret;
	}
	inode->i_size = offset;
	mutex_unlock(&f->sem);
	return 0;
}

// jffs2_fo_open()
// Truncate a file
static int jffs2_truncate_file (struct _inode *inode)
{
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_full_dnode *new_metadata, * old_metadata;
	struct jffs2_raw_inode *ri;
	uint32_t alloclen;
	int err;

	ri = jffs2_alloc_raw_inode();
	if (!ri) {
		return ENOMEM;
	}
	err = jffs2_reserve_space(c, sizeof(*ri), &alloclen, ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);

	if (err) {
		jffs2_free_raw_inode(ri);
		return err;
	}
	mutex_lock(&f->sem);
	ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri->totlen = cpu_to_je32(sizeof(*ri));
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, (sizeof(struct jffs2_unknown_node)-4)));

	ri->ino = cpu_to_je32(inode->i_ino);
	ri->version = cpu_to_je32(++f->highest_version);

	ri->uid = cpu_to_je16(inode->i_uid);
	ri->gid = cpu_to_je16(inode->i_gid);
	ri->mode = cpu_to_jemode(inode->i_mode);
	ri->isize = cpu_to_je32(0);
	ri->atime = cpu_to_je32(inode->i_atime);
	ri->mtime = cpu_to_je32(jffs2_get_timestamp());
	ri->offset = cpu_to_je32(0);
	ri->csize = ri->dsize = cpu_to_je32(0);
	ri->compr = JFFS2_COMPR_NONE;
	ri->node_crc = cpu_to_je32(crc32(0, ri, (sizeof(*ri)-8)));
	ri->data_crc = cpu_to_je32(0);
	new_metadata = jffs2_write_dnode(c, f, ri, NULL, 0, ALLOC_NORMAL);
	if (IS_ERR(new_metadata)) {
	jffs2_complete_reservation(c);
	jffs2_free_raw_inode(ri);
	mutex_unlock(&f->sem);
	return PTR_ERR(new_metadata);
	}

	/* It worked. Update the inode */
	inode->i_mtime = jffs2_get_timestamp();
	inode->i_size = 0;
	old_metadata = f->metadata;
	jffs2_truncate_fragtree (c, &f->fragtree, 0);
	f->metadata = new_metadata;
	if (old_metadata) {
		jffs2_mark_node_obsolete(c, old_metadata->raw);
		jffs2_free_full_dnode(old_metadata);
	}
	jffs2_free_raw_inode(ri);

mutex_unlock(&f->sem);
	jffs2_complete_reservation(c);

	return 0;
}

// jffs2_fo_open()
// Truncate a file

static int jffs2_fo_write(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio)
{
	struct _inode *inode = (struct _inode *) fp->f_data;
	off_t pos = fp->f_offset;
	ssize_t resid = uio->uio_resid;
	struct jffs2_raw_inode ri;
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	int i;

#if (LOSCFG_KERNEL_SMP == YES)
	struct super_block *sb = inode->i_sb;
	UINT16 gc_cpu_mask = LOS_TaskCpuAffiGet(sb->s_gc_thread);
	UINT32 cur_task_id = LOS_CurTaskIDGet();
	UINT16 cur_cpu_mask = LOS_TaskCpuAffiGet(cur_task_id);

	if (cur_cpu_mask != gc_cpu_mask) {
		if (cur_cpu_mask != LOSCFG_KERNEL_CPU_MASK)
			(void)LOS_TaskCpuAffiSet(sb->s_gc_thread, cur_cpu_mask);
		else
			(void)LOS_TaskCpuAffiSet(cur_task_id, gc_cpu_mask);
	}
#endif
	// If the APPEND mode bit was supplied, force all writes to
	// the end of the file.
	if (fp->f_flag & O_APPEND)
		pos = fp->f_offset = inode->i_size;

	if (pos < 0)
		return EINVAL;

	(void)memset_s(&ri, sizeof(ri), 0, sizeof(ri));

	ri.ino = cpu_to_je32(f->inocache->ino);
	ri.mode = cpu_to_jemode(inode->i_mode);
	ri.uid = cpu_to_je16(inode->i_uid);
	ri.gid = cpu_to_je16(inode->i_gid);
	ri.atime = ri.ctime = ri.mtime = cpu_to_je32(jffs2_get_timestamp());

	if (pos > inode->i_size) {
		int err;
		ri.version = cpu_to_je32(++f->highest_version);
		err = jffs2_extend_file(inode, &ri, pos);
		if (err)
			return -err;
	}
	ri.isize = cpu_to_je32(inode->i_size);

	// Now loop over the iovecs until they are all done, or
	// we get an error.
	for (i = 0; i < uio->uio_iovcnt; i++) {
		jffs2_iovec *iov = &uio->uio_iov[i];
		unsigned char *buf = iov->iov_base;
		off_t len = iov->iov_len;

		uint32_t writtenlen;
		int err;

		D2(PRINTK("jffs2_fo_write page_start_pos %d\n", pos));
		D2(PRINTK("jffs2_fo_write transfer size %d\n", len));

		err = jffs2_write_inode_range(c, f, &ri, buf,
				  pos, len, &writtenlen);
		if (err) {
			pos += writtenlen;
			resid -= writtenlen;

			inode->i_mtime = inode->i_ctime = je32_to_cpu(ri.mtime);
			if (pos > inode->i_size)
				inode->i_size = pos;

			uio->uio_resid = resid;
			fp->f_offset = pos;

			return -err;
		}

		if (writtenlen != len) {
			pos += writtenlen;
			resid -= writtenlen;

			inode->i_mtime = inode->i_ctime = je32_to_cpu(ri.mtime);
			if (pos > inode->i_size)
				inode->i_size = pos;

			uio->uio_resid = resid;
			fp->f_offset = pos;

			return ENOSPC;
		}

		pos += len;
		resid -= len;
	}

	// We wrote some data successfully, update the modified and access
	// times of the inode, increase its size appropriately, and update
	// the file offset and transfer residue.
	inode->i_mtime = inode->i_ctime = je32_to_cpu(ri.mtime);
	if (pos > inode->i_size)
		inode->i_size = pos;

	uio->uio_resid = resid;
	fp->f_offset = pos;

	return ENOERR;
}
#endif /* CYGOPT_FS_JFFS2_WRITE */

// -------------------------------------------------------------------------
// jffs2_fo_lseek()
// Seek to a new file position.

static int jffs2_fo_lseek(struct CYG_FILE_TAG *fp, off_t *apos, int whence)
{
	struct _inode *node = (struct _inode *) fp->f_data;
	off_t pos = *apos;

	D2(PRINTK("jffs2_fo_lseek\n"));

	switch (whence) {
	case SEEK_SET:
		// Pos is already where we want to be.
		break;

	case SEEK_CUR:
		// Add pos to current offset.
		pos += fp->f_offset;
		break;

	case SEEK_END:
		// Add pos to file size.
		pos += node->i_size;
		break;

	default:
		return EINVAL;
	}

	if (pos < 0)
		return EINVAL;

	// All OK, set fp offset and return new position.
	*apos = fp->f_offset = pos;

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_fo_close()
// Close a file. We just decrement the refcnt and let it go away if
// that is all that is keeping it here.

static int jffs2_fo_close(struct CYG_FILE_TAG *fp)
{
	struct _inode *node = (struct _inode *) fp->f_data;

	jffs2_dbg(1, "jffs close data: 0x%x\n",fp->f_data);
	if (node == NULL) {
		return ENOENT;
	}
	jffs2_iput(node);

	fp->f_data = 0;
	free(fp);

	return ENOERR;
}

//==========================================================================
// Directory operations

// -------------------------------------------------------------------------
// jffs2_fo_dirread()
// Read a single directory entry from a file.

static __inline void filldir(char *nbuf, int nlen, const unsigned char *name, int namlen)
{
	int len = nlen < namlen ? nlen : namlen;
	(void)memcpy_s(nbuf, nlen, name, len);
	nbuf[len] = '\0';
}

static int jffs2_fo_dirread(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio)
{
	struct _inode *d_inode = (struct _inode *) fp->f_data;
	struct jffs2_dirent *ent = (struct jffs2_dirent *) uio->uio_iov[0].iov_base;
	char *nbuf = ent->d_name;
	int nlen = sizeof(ent->d_name) - 1;
	off_t len = uio->uio_iov[0].iov_len;
	struct jffs2_inode_info *f;
	struct _inode *inode = d_inode;
	struct jffs2_full_dirent *fd;
	unsigned long offset, curofs;
	int found = 1;

	jffs2_dbg(1, "read at: 0x%x \n", fp->f_data);

	if (len < (off_t)sizeof (struct jffs2_dirent))
		return EINVAL;

	if (CheckPermission(inode, READ_OP)) {
		return EACCES;
	}

	D1(printk
	   (KERN_DEBUG "jffs2_readdir() for dir_i #%lu\n", d_inode->i_ino));

	f = JFFS2_INODE_INFO(inode);

	offset = fp->f_offset;
	if (offset == 0) {
		D1(printk
		   (KERN_DEBUG "Dirent 0: \".\", ino #%lu\n", inode->i_ino));
		filldir(nbuf, nlen, (const unsigned char *) ".", 1);
#ifdef CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
		// Flags here are the same as jffs2_mkdir. Make sure
		// d_type is the same as st_mode of calling stat.
		ent->d_type =
		  jemode_to_cpu(cpu_to_jemode(S_IRUGO | S_IXUGO | S_IWUSR | S_IFDIR));
#endif
		goto out;
	}
	if (offset == 1) {
		filldir(nbuf, nlen, (const unsigned char *) "..", 2);
#ifdef CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
		// Flags here are the same as jffs2_mkdir. Make sure
		// d_type is the same as st_mode of calling stat.
		ent->d_type =
		  jemode_to_cpu(cpu_to_jemode(S_IRUGO | S_IXUGO | S_IWUSR | S_IFDIR));
#endif
		goto out;
	}
	curofs = 1;
	mutex_lock(&f->sem);
	for (fd = f->dents; fd; fd = fd->next) {
		curofs++;
		/* First loop: curofs = 2; offset = 2 */
		if (curofs < offset) {
			D2(printk
			   (KERN_DEBUG
				"Skipping dirent: \"%s\", ino #%u, type %d, because curofs %ld < offset %ld\n",
				fd->name, fd->ino, fd->type, curofs, offset));
			continue;
		}
		if (!fd->ino) {
			D2(printk
			   (KERN_DEBUG "Skipping deletion dirent \"%s\"\n",
				fd->name));
			offset++;
			continue;
		}
		D2(printk
		   (KERN_DEBUG "Dirent %ld: \"%s\", ino #%u, type %d\n", offset,
			fd->name, fd->ino, fd->type));
		filldir(nbuf, nlen, fd->name, strlen((char *)fd->name));
		ent->d_type = fd->type;
		goto out_sem;
	}
	/* Reached the end of the directory */
	found = 0;
      out_sem:
	mutex_unlock(&f->sem);
	if (fd == NULL) {
		fp->f_offset = 2;
		D2(printk
			(KERN_DEBUG "reached the end of the directory\n"));
		return ENOENT;
	}
	  out:
	fp->f_offset = ++offset;


	if (found) {
		uio->uio_resid -= sizeof (struct jffs2_dirent);
	}
	return ENOERR;
}

static int jffs2_fo_dirlseek(struct CYG_FILE_TAG *fp, off_t *pos, int whence)
{
	// Only allow SEEK_SET to zero
	jffs2_dbg(1, "lseekdir at: %d \n", whence);

	if (whence != SEEK_SET || *pos != 0)
		return EINVAL;

	*pos = fp->f_offset = 2;

	return ENOERR;
}

//==========================================================================
//
// Called by JFFS2
// ===============
//
//
//==========================================================================

unsigned char *jffs2_gc_fetch_page(struct jffs2_sb_info *c,
			   struct jffs2_inode_info *f,
			   unsigned long offset,
			   unsigned long *priv)
{
	/* FIXME: This works only with one file system mounted at a time */
	int ret;

	ret = jffs2_read_inode_range(c, f, gc_buffer,
			 offset & ~(PAGE_CACHE_SIZE-1), PAGE_CACHE_SIZE);
	if (ret)
		return ERR_PTR(ret);

	return gc_buffer;
}

void jffs2_gc_release_page(struct jffs2_sb_info *c,
		   unsigned char *ptr,
		   unsigned long *priv)
{
	/* Do nothing */
}

struct _inode *new_inode(struct super_block *sb)
{
	struct _inode *inode;
	struct _inode *cached_inode;

	inode = malloc(sizeof (struct _inode));
	if (inode == NULL)
		return 0;

	D2(PRINTK("malloc new_inode %x ####################################\n",
		inode));

	(void)memset_s(inode, sizeof (struct _inode), 0, sizeof (struct _inode));
	inode->i_sb = sb;
	inode->i_ino = 1;
	inode->i_count = 1;
	inode->i_nlink = 1;    // Let JFFS2 manage the link count
	inode->i_size = 0;

	inode->i_cache_next = NULL;    // Newest inode, about to be cached
	// Add to the icache
	for (cached_inode = sb->s_root; cached_inode != NULL;
		 cached_inode = cached_inode->i_cache_next) {
		if (cached_inode->i_cache_next == NULL) {
			cached_inode->i_cache_next = inode;    // Current last in cache points to newcomer
			inode->i_cache_prev = cached_inode;    // Newcomer points back to last
			break;
		}
	}
	return inode;
}

static struct _inode *ilookup(struct super_block *sb, uint32_t ino)
{
	struct _inode *inode = NULL;

	D2(PRINTK("ilookup\n"));
	// Check for this inode in the cache
	jffs_lock();
	for (inode = sb->s_root; inode != NULL; inode = inode->i_cache_next) {
		if (inode->i_ino == ino) {
			inode->i_count++;
			break;
		}
	}
	jffs_unlock();
	return inode;
}

struct _inode *jffs2_iget(struct super_block *sb, uint32_t ino)
{
	// Called in super.c jffs2_read_super, dir.c jffs2_lookup,
	// and gc.c jffs2_garbage_collect_pass

	// Must first check for cached inode
	// If this fails let new_inode create one

	struct _inode *inode;
	int err;

	D2(PRINTK("jffs2_iget\n"));

	jffs_lock();
	inode = ilookup(sb, ino);
	if (inode) {
		jffs_unlock();
		return inode;
	}

	// Not cached, so malloc it

	inode = new_inode(sb);
	if (inode == NULL) {
		jffs_unlock();
		return ERR_PTR(-ENOMEM);
	}
	inode->i_ino = ino;
	err = jffs2_read_inode(inode);

	if (err) {
		PRINTK("jffs2_read_inode() failed\n");
				inode->i_nlink = 0; // free _this_ bad inode right now

		jffs2_iput(inode);
		jffs_unlock();
		return ERR_PTR(err);
	}

	jffs_unlock();
	return inode;
}

// -------------------------------------------------------------------------
// Decrement the reference count on an inode. If this makes the ref count
// zero, then this inode can be freed.

void jffs2_iput(struct _inode *i)
{
	// Called in jffs2_find
	// (and jffs2_open and jffs2_ops_mkdir?)
	// super.c jffs2_read_super,
	// and gc.c jffs2_garbage_collect_pass
	struct jffs2_inode_info *f = NULL;
	struct _inode *temp = NULL;
	jffs_lock();
 recurse:
	if (!i) {
		PRINT_ERR("jffs2_iput() called with NULL inode\n");
		// and let it fault...
		jffs_unlock();
		return;
	}
	i->i_count--;
	if (i->i_count < 0)
		BUG();

	if (i->i_count) {
		jffs_unlock();
		return;
	}

	if (!i->i_nlink) {
		struct _inode *parent;
		// Remove from the icache linked list and free immediately
		if (i->i_cache_prev)
			i->i_cache_prev->i_cache_next = i->i_cache_next;
		if (i->i_cache_next)
			i->i_cache_next->i_cache_prev = i->i_cache_prev;
		parent = i->i_parent;
		jffs2_clear_inode(i);
		f = JFFS2_INODE_INFO(i);
		(void)mutex_destroy(&(f->sem));
		(void)memset_s(i, sizeof(*i), 0x5a, sizeof(*i));
		temp = i;
		free(i);

		if (parent && parent != temp) {
			i = parent;
			goto recurse;
		}

	} else {
		// Evict some _other_ inode with i_count zero, leaving
		// this latest one in the cache for a while
		icache_evict(i->i_sb->s_root, i);
	}
	jffs_unlock();
}


// -------------------------------------------------------------------------
// EOF jffs2.c


static inline void jffs2_init_inode_info(struct jffs2_inode_info *f)
{
	(void)memset_s(f, sizeof(struct jffs2_inode_info), 0, sizeof(struct jffs2_inode_info));
	(void)mutex_init(&f->sem);
	(void)mutex_lock(&f->sem);
}

static void jffs2_clear_inode (struct _inode *inode)
{
	/* We can forget about this inode for now - drop all
	 *  the nodelists associated with it, etc.
	 */
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);

	D1(printk(KERN_DEBUG "jffs2_clear_inode(): ino #%lu mode %o\n", inode->i_ino, inode->i_mode));

	jffs2_do_clear_inode(c, f);
}


/* jffs2_new_inode: allocate a new inode and inocache, add it to the hash,
   fill in the raw_inode while you're at it. */
struct _inode *jffs2_new_inode (struct _inode *dir_i, int mode, struct jffs2_raw_inode *ri)
{
	struct _inode *inode;
	struct super_block *sb = dir_i->i_sb;
	struct jffs2_sb_info *c;
	struct jffs2_inode_info *f;
	int ret;

	D1(printk(KERN_DEBUG "jffs2_new_inode(): dir_i %ld, mode 0x%x\n", dir_i->i_ino, mode));

	c = JFFS2_SB_INFO(sb);

	if (CheckPermission(dir_i, WRITE_OP | EXEC_OP)) {
		D1(PRINTK("%s, %d, check permission fail\n", __FUNCTION__, __LINE__));
		return ERR_PTR(-EACCES);
	}

	jffs_lock();
	inode = new_inode(sb);
	if (!inode) {
		jffs_unlock();
		return ERR_PTR(-ENOMEM);
	}

	f = JFFS2_INODE_INFO(inode);
	jffs2_init_inode_info(f);
	(void)memset_s(ri, sizeof(*ri), 0, sizeof(*ri));
	/* Set OS-specific defaults for new inodes */
	ri->uid = cpu_to_je16(OsCurrUserGet()->effUserID);
	ri->gid = cpu_to_je16(OsCurrUserGet()->effGid);
	ri->mode =  cpu_to_jemode(mode);
	ret = jffs2_do_new_inode (c, f, mode, ri);
	if (ret) {
		// forceful evict: f->sem is locked already, and the
		// inode is bad.
		if (inode->i_cache_prev)
			   inode->i_cache_prev->i_cache_next = inode->i_cache_next;
		if (inode->i_cache_next)
			   inode->i_cache_next->i_cache_prev = inode->i_cache_prev;
		mutex_unlock(&(f->sem));
		jffs2_clear_inode(inode);
		(void)mutex_destroy(&(f->sem));
		(void)memset_s(inode, sizeof(*inode), 0x6a, sizeof(*inode));
		free(inode);
		jffs_unlock();
		return ERR_PTR(ret);
	}
	inode->i_nlink = 1;
	inode->i_ino = je32_to_cpu(ri->ino);
	inode->i_mode = jemode_to_cpu(ri->mode);
	inode->i_gid = je16_to_cpu(ri->gid);
	inode->i_uid = je16_to_cpu(ri->uid);
	inode->i_atime = inode->i_ctime = inode->i_mtime = jffs2_get_timestamp();
	ri->atime = ri->mtime = ri->ctime = cpu_to_je32(inode->i_mtime);

	inode->i_size = 0;
	jffs_unlock();

	return inode;
}


static int jffs2_read_inode (struct _inode *inode)
{
	struct jffs2_inode_info *f;
	struct jffs2_sb_info *c;
	struct jffs2_raw_inode latest_node;
	int ret;

	D1(printk(KERN_DEBUG "jffs2_read_inode(): inode->i_ino == %lu\n", inode->i_ino));

	f = JFFS2_INODE_INFO(inode);
	c = JFFS2_SB_INFO(inode->i_sb);

	jffs2_init_inode_info(f);

	ret = jffs2_do_read_inode(c, f, inode->i_ino, &latest_node);

	if (ret) {
		(void)mutex_unlock(&f->sem);

		return ret;
	}
	inode->i_mode = jemode_to_cpu(latest_node.mode);
	inode->i_uid = je16_to_cpu(latest_node.uid);
	inode->i_gid = je16_to_cpu(latest_node.gid);
	inode->i_size = je32_to_cpu(latest_node.isize);
	inode->i_atime = je32_to_cpu(latest_node.atime);
	inode->i_mtime = je32_to_cpu(latest_node.mtime);
	inode->i_ctime = je32_to_cpu(latest_node.ctime);

	inode->i_nlink = f->inocache->pino_nlink;
	mutex_unlock(&f->sem);

	D1(printk(KERN_DEBUG "jffs2_read_inode() returning\n"));
	return 0;
}


void jffs2_gc_release_inode(struct jffs2_sb_info *c,
		   struct jffs2_inode_info *f)
{
	jffs2_iput(OFNI_EDONI_2SFFJ(f));
}

struct jffs2_inode_info *jffs2_gc_fetch_inode(struct jffs2_sb_info *c,
					 int inum, int unlinked)
{
	struct _inode *inode;
	struct jffs2_inode_cache *ic;

	if (unlinked) {
		/* The inode has zero nlink but its nodes weren't yet marked
		   obsolete. This has to be because we're still waiting for
		   the final (close() and) jffs2_iput() to happen.

		   There's a possibility that the final jffs2_iput() could have
		   happened while we were contemplating. In order to ensure
		   that we don't cause a new read_inode() (which would fail)
		   for the inode in question, we use ilookup() in this case
		   instead of jffs2_iget().

		   The nlink can't _become_ zero at this point because we're
		   holding the alloc_sem, and jffs2_do_unlink() would also
		   need that while decrementing nlink on any inode.
		*/
		inode = ilookup(OFNI_BS_2SFFJ(c), inum);
		if (!inode) {
			D1(printk(KERN_DEBUG "ilookup() failed for ino #%u; inode is probably deleted.\n",
				  inum));

			spin_lock(&c->inocache_lock);
			ic = jffs2_get_ino_cache(c, inum);
			if (!ic) {
				D1(printk(KERN_DEBUG "Inode cache for ino #%u is gone.\n", inum));
				spin_unlock(&c->inocache_lock);
				return NULL;
			}
			if (ic->state != INO_STATE_CHECKEDABSENT) {
				/* Wait for progress. Don't just loop */
				D1(printk(KERN_DEBUG "Waiting for ino #%u in state %d\n",
					  ic->ino, ic->state));
				sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			} else {
				spin_unlock(&c->inocache_lock);
			}

			return NULL;
		}
	} else {
		/* Inode has links to it still; they're not going away because
		   jffs2_do_unlink() would need the alloc_sem and we have it.
		   Just jffs2_iget() it, and if read_inode() is necessary that's OK.
		*/
		inode = jffs2_iget(OFNI_BS_2SFFJ(c), inum);
		if (IS_ERR(inode))
			return (void *)inode;
	}

	return JFFS2_INODE_INFO(inode);
}
static int jffs_check_path(const char *path)
{
	int n = 0;
	int divs = 0;
	while (*path && n < NAME_MAX && divs < 100) {  // File depth cannot exceed 100
		if (jffsfs_IsPathDivider(*path)) {
			n = 0;
			divs++;
		} else
			n++;
		path++;
	}
	return (*path) ? -1 : 0;
}

int jffs2_oflag_to_accmode(int oflags)
{
	/* regular file operations */
	int acc_mode = 0;
	if ((oflags & O_ACCMODE) == O_RDONLY) {
		acc_mode |= READ_OP;
	}

	if (oflags & O_WRONLY) {
		acc_mode |= WRITE_OP;
	}

	if (oflags & O_RDWR) {
		acc_mode |= READ_OP | WRITE_OP;
	}

	/* Opens the file, if it is existing. If not, a new file is created. */
	if (oflags & O_CREAT) {
		acc_mode |= WRITE_OP;
	}

	/* Creates a new file. If the file is existing, it is truncated and overwritten. */
	if (oflags & O_TRUNC) {
		acc_mode |= WRITE_OP;
	}

	/* Creates a new file. The function fails if the file is already existing. */
	if (oflags & O_EXCL) {
		acc_mode |= WRITE_OP;
	}

	if (oflags & O_APPEND) {
		acc_mode |= WRITE_OP;
	}

	/* mark for executing operation */
	if (oflags & O_EXECVE) {
		acc_mode |= EXEC_OP;
	}

	return acc_mode;
}

static unsigned int CheckPermission(struct _inode *node, int accMode)
{
	uint uid = OsCurrUserGet()->effUserID;
	mode_t file_mode = node->i_mode;

	if (uid == node->i_uid) {
		file_mode >>= JFFS2_USER_SHFIT;
	} else if (LOS_CheckInGroups(node->i_gid)) {
		file_mode >>= JFFS2_GROUP_SHFIT;
	}

	file_mode &= JFFS2_MODE_ALL;

	if ((accMode & file_mode) == accMode) {
		return 0;
	}

	file_mode = 0;
	if (S_ISDIR(node->i_mode)) {
		if ((accMode & EXEC_OP) && (IsCapPermit(CAP_DAC_READ_SEARCH))) {
			file_mode |= EXEC_OP;
		}
	} else {
		if ((accMode & EXEC_OP) && (IsCapPermit(CAP_DAC_EXECUTE)) && (node->i_mode & S_IXUGO)) {
			file_mode |= EXEC_OP;
		}
	}

	if ((accMode & WRITE_OP) && IsCapPermit(CAP_DAC_WRITE)) {
		file_mode |= WRITE_OP;
	}

	if ((accMode & READ_OP) && IsCapPermit(CAP_DAC_READ_SEARCH)) {
		file_mode |= READ_OP;
	}

	if ((accMode & file_mode) == accMode) {
		return 0;
	}

	D1(PRINTK("%s, %d, permission check fail,uid %d, gid %d, mode %d, accMode %d, cuid %d\n",
		__FUNCTION__, __LINE__, node->i_uid, node->i_gid, (node->i_mode) & UMASK_FULL, accMode, uid));

	return 1;
}

static int check_to_setattr(struct jffs2_raw_inode *ri, struct jffs2_inode_info *f,
							const struct _inode *node, iattr *attr)
{
	unsigned int valid;
	mode_t tmp_mode;
	uint c_uid = OsCurrUserGet()->effUserID;
	uint c_gid = OsCurrUserGet()->effGid;

	valid = attr->attr_chg_valid;
	ri->uid = cpu_to_je16(node->i_uid);
	ri->gid = cpu_to_je16(node->i_gid);
	tmp_mode = node->i_mode;
	if (valid & CHG_UID) {
		if (((c_uid != node->i_uid) || (attr->attr_chg_uid != node->i_uid)) && (!IsCapPermit(CAP_CHOWN))) {
			return -EPERM;
		} else {
			ri->uid = cpu_to_je16(attr->attr_chg_uid);
		}
	}

	if (valid & CHG_GID) {
		if (((c_gid != node->i_gid) || (attr->attr_chg_gid != node->i_gid)) && (!IsCapPermit(CAP_CHOWN))) {
			return -EPERM;
		} else {
			ri->gid = cpu_to_je16(attr->attr_chg_gid);
		}
	}

	if (valid & CHG_MODE) {
		if (!IsCapPermit(CAP_FOWNER) && (c_uid != node->i_uid)) {
			return -EPERM;
		} else {
			attr->attr_chg_mode  &= ~S_IFMT; // delete file type
			tmp_mode &= S_IFMT;
			tmp_mode = attr->attr_chg_mode | tmp_mode; // add old file type
		}
	}
	ri->mode = cpu_to_jemode(tmp_mode);
	ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri->totlen = cpu_to_je32(sizeof(*ri));
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, (sizeof(struct jffs2_unknown_node)-4)));
	ri->ino = cpu_to_je32(node->i_ino);
	ri->version = cpu_to_je32(++f->highest_version);
	ri->isize = cpu_to_je32((uint32_t)node->i_size);
	ri->atime = cpu_to_je32(node->i_atime);
	ri->mtime = cpu_to_je32(jffs2_get_timestamp());
	ri->offset = cpu_to_je32(0);
	ri->csize = ri->dsize = cpu_to_je32(0);
	ri->compr = JFFS2_COMPR_NONE;
	ri->node_crc = cpu_to_je32(crc32(0, ri, (sizeof(*ri)-8)));
	ri->data_crc = cpu_to_je32(0);
	return 0;
}

int jffs2_chattr (struct _inode *dir_i, const unsigned char *d_name, iattr *attr, struct _inode *node_old)
{
	struct jffs2_inode_info *f = NULL;
	struct jffs2_sb_info *c = NULL;
	struct jffs2_raw_inode *ri = NULL;
	struct jffs2_full_dnode *new_metadata = NULL;
	struct jffs2_full_dnode *old_metadata = NULL;
	uint32_t alloclen;
	int ret;
	ri = jffs2_alloc_raw_inode();
	if (!ri) {
		set_errno(ENOMEM);
		return -ENOMEM;
	}
	c = JFFS2_SB_INFO(dir_i->i_sb);
	/* Try to reserve enough space for both node and dirent.
	 * Just the node will do for now, though
	 */
	ret = jffs2_reserve_space(c, sizeof(*ri), &alloclen, ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);
	if (ret) {
		jffs2_free_raw_inode(ri);
		return ret;
	}

	f = JFFS2_INODE_INFO(node_old);
	mutex_lock(&f->sem);
	ret = check_to_setattr(ri, f, node_old, attr);

	if (ret < 0) {
		set_errno(-ret);
		goto errout;
	}
	new_metadata = jffs2_write_dnode(c, f, ri, NULL, 0, ALLOC_NORMAL);
	if (IS_ERR(new_metadata)) {
		ret = PTR_ERR(new_metadata);
		set_errno(-ret);
		goto errout;
	}
	node_old->i_atime = je32_to_cpu(ri->atime);
	node_old->i_ctime = je32_to_cpu(ri->ctime);
	node_old->i_mtime = je32_to_cpu(ri->mtime);
	node_old->i_mode = jemode_to_cpu(ri->mode);
	node_old->i_uid = je16_to_cpu(ri->uid);
	node_old->i_gid = je16_to_cpu(ri->gid);

	old_metadata = f->metadata;
	f->metadata = new_metadata;
	if (old_metadata) {
		jffs2_mark_node_obsolete(c, old_metadata->raw);
		jffs2_free_full_dnode(old_metadata);
	}
	jffs2_complete_reservation(c);
	jffs2_free_raw_inode(ri);
	mutex_unlock(&f->sem);
	return 0;
errout:
	jffs2_complete_reservation(c);
	jffs2_free_raw_inode(ri);
	mutex_unlock(&f->sem);
	return ret;
}

struct los_jffs2_operations jffs2_dir_operations = {
	.opendir  =	jffs2_opendir,
	.lseekdir = jffs2_fo_dirlseek,
	.readdir  =	jffs2_fo_dirread,

};

struct los_jffs2_operations jffs2_fs_type = {
	.mount  = jffs2_mount,
	.stat   = jffs2_stat,
	.umount = jffs2_umount
};


struct los_jffs2_operations jffs2_file_operations = {
	.open   = jffs2_open,
	.close  = jffs2_fo_close,
	.read   = jffs2_fo_read,
	.write  = jffs2_fo_write,
	.lseek  = jffs2_fo_lseek,
	.chattr = jffs2_fo_chattr
};

struct los_jffs2_operations jffs2_dir_inode_operations = {
	.mkdir  = jffs2_ops_mkdir,
	.rmdir  = jffs2_ops_rmdir,
	.unlink = jffs2_ops_unlink,
	.rename = jffs2_ops_rename,
};
