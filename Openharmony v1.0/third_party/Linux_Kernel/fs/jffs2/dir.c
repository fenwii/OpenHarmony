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

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include "los_crc32.h"
#include "nodelist.h"
#include "vfs_jffs2.h"
#include "porting.h"

/* We keep the dirent list sorted in increasing order of name hash,
   and we use the same hash function as the dentries. Makes this
   nice and simple
*/
struct _inode *jffs2_lookup(struct _inode *dir_i, const unsigned char *d_name, int namelen)
{
	struct jffs2_inode_info *dir_f;
	struct jffs2_full_dirent *fd = NULL, *fd_list;
	uint32_t ino = 0;
	uint32_t hash = full_name_hash(d_name, namelen);
	struct _inode *inode = NULL;

	jffs2_dbg(1, "jffs2_lookup()\n");

	if (namelen > JFFS2_MAX_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	dir_f = JFFS2_INODE_INFO(dir_i);

	mutex_lock(&dir_f->sem);

	/* NB: The 2.2 backport will need to explicitly check for '.' and '..' here */
	for (fd_list = dir_f->dents; fd_list && fd_list->nhash <= hash; fd_list = fd_list->next) {
		if (fd_list->nhash == hash &&
		    (!fd || fd_list->version > fd->version) &&
		    strlen((char *)fd_list->name) == namelen&&
		    !strncmp((char *)fd_list->name, (char *)d_name, namelen)) {
			fd = fd_list;
		}
	}
	if (fd)
		ino = fd->ino;
	mutex_unlock(&dir_f->sem);
	if (ino) {
		inode = jffs2_iget(dir_i->i_sb, ino);
		if (IS_ERR(inode))
			pr_warn("iget() failed for ino #%u\n", ino);
	}

	return inode;
}


/***********************************************************************/


int jffs2_unlink(struct _inode *dir_i, struct _inode *d_inode, const unsigned char *d_name)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(dir_i->i_sb);
	struct jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	struct jffs2_inode_info *dead_f = JFFS2_INODE_INFO(d_inode);
	int ret;
	uint32_t now = get_seconds();

	ret = jffs2_do_unlink(c, dir_f, (const char *)d_name,
		strlen((char *)d_name), dead_f, now);
	if (dead_f->inocache)
		d_inode->i_nlink = dead_f->inocache->pino_nlink;
	if (!ret)
		dir_i->i_mtime = dir_i->i_ctime = now;
	return ret;
}
/***********************************************************************/


int jffs2_link(struct _inode *old_d_inode, struct _inode *dir_i, const unsigned char *d_name)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(old_d_inode->i_sb);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(old_d_inode);
	struct jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	int ret;
	uint8_t type;
	uint32_t now;

	/* XXX: This is ugly */
	type = (old_d_inode->i_mode & S_IFMT) >> 12;
	if (!type) type = DT_REG;

	now = get_seconds();
	ret = jffs2_do_link(c, dir_f, f->inocache->ino, type, (const char *)d_name,
	    strlen((char *)d_name), now);

	if (!ret) {
		mutex_lock(&f->sem);
		old_d_inode->i_nlink = ++f->inocache->pino_nlink;
		mutex_unlock(&f->sem);
		dir_i->i_mtime = dir_i->i_ctime = now;
	}
	return ret;
}

/***********************************************************************/

int jffs2_mkdir(struct _inode *dir_i, const unsigned char *d_name, int mode)
{
	struct jffs2_inode_info *f, *dir_f;
	struct jffs2_sb_info *c;
	struct _inode *inode;
	struct jffs2_raw_inode *ri;
	struct jffs2_raw_dirent *rd;
	struct jffs2_full_dnode *fn;
	struct jffs2_full_dirent *fd;
	int namelen;
	uint32_t alloclen;
	int ret;
	mode  &= ~S_IFMT;
	mode |= S_IFDIR;

	ri = jffs2_alloc_raw_inode();
	if (!ri)
		return -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	/* Try to reserve enough space for both node and dirent.
	 * Just the node will do for now, though
	 */
	namelen = strlen((char *)d_name);
	ret = jffs2_reserve_space(c, sizeof(*ri), &alloclen, ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);

	if (ret) {
		jffs2_free_raw_inode(ri);
		return ret;
	}

	inode = jffs2_new_inode(dir_i, mode, ri);

	if (IS_ERR(inode)) {
		jffs2_free_raw_inode(ri);
		jffs2_complete_reservation(c);
		return PTR_ERR(inode);
	}
	f = JFFS2_INODE_INFO(inode);


	/* but ic->pino_nlink is the parent ino# */
	f->inocache->pino_nlink = dir_i->i_ino;

	ri->data_crc = cpu_to_je32(0);
	ri->node_crc = cpu_to_je32(crc32(0, ri, sizeof(*ri)-8));

	fn = jffs2_write_dnode(c, f, ri, NULL, 0, ALLOC_NORMAL);

	jffs2_free_raw_inode(ri);

	if (IS_ERR(fn)) {
		/* Eeek. Wave bye bye */
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);

		ret = PTR_ERR(fn);
		goto fail;
	}
	/* No data here. Only a metadata node, which will be
	   obsoleted by the first data write
	*/
	f->metadata = fn;
	mutex_unlock(&f->sem);

	jffs2_complete_reservation(c);

	ret = jffs2_reserve_space(c, sizeof(*rd)+namelen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_DIRENT_SIZE(namelen));
	if (ret)
		goto fail;

	rd = jffs2_alloc_raw_dirent();
	if (!rd) {
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		ret = -ENOMEM;
		goto fail;
	}

	dir_f = JFFS2_INODE_INFO(dir_i);
	mutex_lock(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_DIRENT);
	rd->totlen = cpu_to_je32(sizeof(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, sizeof(struct jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_i->i_ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(inode->i_ino);
	rd->mctime = cpu_to_je32(get_seconds());
	rd->nsize = namelen;
	rd->type = DT_DIR;
	rd->node_crc = cpu_to_je32(crc32(0, rd, sizeof(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, d_name, namelen));

	fd = jffs2_write_dirent(c, dir_f, rd, d_name, namelen, ALLOC_NORMAL);

	if (IS_ERR(fd)) {
		/* dirent failed to write. Delete the inode normally
		   as if it were the final unlink() */
		jffs2_complete_reservation(c);
		jffs2_free_raw_dirent(rd);
		mutex_unlock(&dir_f->sem);
		inode->i_nlink = 0;
		ret = PTR_ERR(fd);
		goto fail;
	}

	dir_i->i_mtime = dir_i->i_ctime = je32_to_cpu(rd->mctime);

	jffs2_free_raw_dirent(rd);

	/* Link the fd into the inode's list, obsoleting an old
	   one if necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	mutex_unlock(&dir_f->sem);
	jffs2_complete_reservation(c);
	jffs2_iput(inode);
	return 0;

 fail:
    inode->i_nlink = 0;
    jffs2_iput(inode);
	return ret;
}

int jffs2_rmdir (struct _inode *dir_i, struct _inode *d_inode, const unsigned char *d_name)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(dir_i->i_sb);
	struct jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode);
	struct jffs2_full_dirent *fd;
	int ret;
	uint32_t now = get_seconds();

	for (fd = f->dents ; fd; fd = fd->next) {
		if (fd->ino)
			return -ENOTEMPTY;
	}

	ret = jffs2_do_unlink(c, dir_f, (const char *)d_name,
			      strlen((char *)d_name), f, now);
	if (!ret) {
		dir_i->i_mtime = dir_i->i_ctime = now;
	}
	return ret;
}

int jffs2_rename (struct _inode *old_dir_i, struct _inode *d_inode, const unsigned char *old_d_name,
			struct _inode *new_dir_i, const unsigned char *new_d_name)
{
	int ret;
	struct jffs2_sb_info *c = JFFS2_SB_INFO(old_dir_i->i_sb);
	struct jffs2_inode_info *victim_f = NULL;
	uint8_t type;
	uint32_t now;


	/* XXX: We probably ought to alloc enough space for
	   both nodes at the same time. Writing the new link,
	   then getting -ENOSPC, is quite bad :)
	*/

	/* Make a hard link */

	/* XXX: This is ugly */
	type = (d_inode->i_mode & S_IFMT) >> 12;
	if (!type) type = DT_REG;

	now = get_seconds();
	ret = jffs2_do_link(c, JFFS2_INODE_INFO(new_dir_i),
			    d_inode->i_ino, type,
			    (const char *)new_d_name, strlen((char *)new_d_name), now);

	if (ret)
		return ret;

	if (victim_f) {
		/* There was a victim. Kill it off nicely */

		/* Don't oops if the victim was a dirent pointing to an
		   inode which didn't exist. */
		if (victim_f->inocache) {
			mutex_lock(&victim_f->sem);
		    victim_f->inocache->pino_nlink--;
			mutex_unlock(&victim_f->sem);
		}
	}


	/* Unlink the original */
	ret = jffs2_do_unlink(c, JFFS2_INODE_INFO(old_dir_i),
			      (const char *)old_d_name, strlen((char *)old_d_name), NULL, now);

	/* We don't touch inode->i_nlink */

	if (ret) {
		/* Oh shit. We really ought to make a single node which can do both atomically */
		struct jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode);
		mutex_lock(&f->sem);
		if (f->inocache)
			d_inode->i_nlink = f->inocache->pino_nlink++;
		mutex_unlock(&f->sem);

		pr_notice("%s(): Link succeeded, unlink failed (err %d). You now have a hard link\n",
			  __func__, ret);
		/* Might as well let the VFS know */
		new_dir_i->i_mtime = new_dir_i->i_ctime = now;
		return ret;
	}


	new_dir_i->i_mtime = new_dir_i->i_ctime = old_dir_i->i_mtime = old_dir_i->i_ctime = now;

	return 0;
}

/***********************************************************************/

int jffs2_create(struct _inode *dir_i, const unsigned char *d_name, int mode,
				 struct _inode **new_i)
{
	struct jffs2_raw_inode *ri;
	struct jffs2_inode_info *f, *dir_f;
	struct jffs2_sb_info *c;
	struct _inode *inode;
	int ret;
	mode  &= ~S_IFMT;
	mode |= S_IFREG;
	ri = jffs2_alloc_raw_inode();
	if (!ri)
		return -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	D1(printk(KERN_DEBUG "jffs2_create()\n"));
	inode = jffs2_new_inode(dir_i, mode, ri);

	if (IS_ERR(inode)) {
		D1(printk(KERN_DEBUG "jffs2_new_inode() failed, error:%ld\n", PTR_ERR(inode)));
		jffs2_free_raw_inode(ri);
		return PTR_ERR(inode);
	}

	f = JFFS2_INODE_INFO(inode);
	dir_f = JFFS2_INODE_INFO(dir_i);

	/* jffs2_do_create() will want to lock it, _after_ reserving
	   space and taking c-alloc_sem. If we keep it locked here,
	   lockdep gets unhappy (although it's a false positive;
	   nothing else will be looking at this inode yet so there's
	   no chance of AB-BA deadlock involving its f->sem). */
	mutex_unlock(&f->sem);
	ret = jffs2_do_create(c, dir_f, f, ri,
				(const char *)d_name,
				strlen((char *)d_name));

	if (ret) {
		inode->i_nlink = 0;
		jffs2_iput(inode);
		jffs2_free_raw_inode(ri);
		return ret;
	}

	jffs2_free_raw_inode(ri);

	D1(printk(KERN_DEBUG "jffs2_create: Created ino #%lu with mode %o, nlink %d(%d)\n",
		inode->i_ino, inode->i_mode, inode->i_nlink, f->inocache->pino_nlink));
	*new_i = inode;
	return 0;
}