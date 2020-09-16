/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-1-7       prife        the first version
 */

#include "los_typedef.h"
#include "fileio.h"
#include "fcntl.h"
#include "sys/stat.h"
#undef mode_t

#include "vfs_jffs2.h"
#include "jffs2_config.h"
#include "porting.h"
#include "los_mux.h"
#include "inode/inode.h"
#include "sys/statfs.h"
#include "fs/dirent_fs.h"
#include "fs/fs.h"
#include "los_tables.h"
#include "mtd_list.h"
#include "port/fcntl.h"
#include "los_vm_filemap.h"

#ifdef LOSCFG_FS_JFFS

#if DEVICE_PART_MAX > 1
	#error "support only one jffs2 partition on a flash device!"
#endif

LosMux jffs2_lock;
cyg_mtab_entry *mte[CONFIG_MTD_PATTITION_NUM];
static const char jffs2_root_path[] = ".";
#define BLOCK_SIZE    4096

int jffs2_result_to_vfs(int result)
{
	if (result > 0)
		result = -result;
	return result;
}

struct inode *jffs_block[CONFIG_MTD_PATTITION_NUM];
static int vfs_jffs_bind(FAR struct inode *blkdriver,
				FAR const void *data,
				FAR void **handle,
				FAR const char *relpath)
{
	int result;
	mtd_partition *p = (mtd_partition *)blkdriver->i_private;
	int partition_num = p->patitionnum;
	struct MtdDev *mtd = (struct MtdDev *)(p->mtd_info);
	/* find a empty entry in partition table */
	if (mtd == NULL) {
		return -EINVAL;
	}
	if (mtd->type != MTD_NORFLASH) {
		return -EINVAL;
	}

	mte[partition_num] = (cyg_mtab_entry*)malloc(sizeof(cyg_mtab_entry));
	if (mte[partition_num] == NULL) {
		return -ENOMEM;
	}

	mte[partition_num]->name = "jffs2";

	/* note that, i use mte->n_private to store rtt's device
	 * while, in jffs2_mount, mte->n_private will be copy into
	 * s_dev in struct super_block, and mte->n_private will be
	 * filled with jffs2_sb(see the source of jffs2_mount.
	 */
	/* after jffs2_mount, mte->n_private will not be dev_id any more */
	result = jffs2_fs_type.mount(mte[partition_num], partition_num);
	if (result != 0) {
		free(mte[partition_num]);
		mte[partition_num] = NULL;
		return jffs2_result_to_vfs(result);
	}
	*handle = (void *)p;
	jffs_block[partition_num] = blkdriver;
	return 0;
}

static int vfs_jffs_unbind(FAR void *handle, FAR struct inode **blkdriver)
{
	int result;
	mtd_partition *p = (mtd_partition *)handle;
	int partition_num;

	if (p == NULL)
		return -EINVAL;

	partition_num = p->patitionnum;
	result = jffs2_fs_type.umount(mte[partition_num]);
	if (result)
		return jffs2_result_to_vfs(result);

	free(mte[partition_num]);
	mte[partition_num] = NULL;
	free(p->mountpoint_name);
	p->mountpoint_name = NULL;
	*blkdriver = jffs_block[partition_num];
	return 0;
}

static bool oflag_convert_and_check(FAR struct file *filep, int oflags)
{
	int acc_mode = 0;
	if ((oflags & O_ACCMODE) == O_RDONLY)
	acc_mode |= READ_OP;
	if (oflags & O_WRONLY)
	acc_mode |= WRITE_OP;
	if (oflags & O_RDWR)
	acc_mode |= READ_OP | WRITE_OP;

	if (oflags & O_CREAT)
	acc_mode |= WRITE_OP;

	if (oflags & O_TRUNC)
	acc_mode |= WRITE_OP;

	if (oflags & O_EXCL)
	acc_mode |= WRITE_OP;
	if (oflags & O_APPEND)
	acc_mode |= WRITE_OP;

	if (oflags & O_EXECVE)
	acc_mode |= EXEC_OP;

	if (filep->f_inode->mountflags == MS_RDONLY && (acc_mode & WRITE_OP) != 0) {
		return false;
	}
	return true;
}


static int vfs_jffs_open(FAR struct file *filep,
				FAR const char *relpath,
				int oflags,
				mode_t mode)
{
	int result;
	int partition_num;
	const char *name = NULL;

	cyg_file *jffs2_file = NULL;
	mtd_partition *p = NULL;

	p = (mtd_partition *)filep->f_inode->i_private;
	partition_num = p->patitionnum;
	jffs2_file = malloc(sizeof(cyg_file));
	if (jffs2_file == NULL) {
		return -ENOMEM;
	}
	name = relpath;
	if ((name[0] == '/') && (name[1] == 0))
		name = jffs2_root_path;
	else if (name[0] == '/') /* name[0] still will be '/' */
		name++;

	if (oflag_convert_and_check(filep, oflags) != true) {
		free(jffs2_file);
		return -EACCES;
	}


	if (oflags & O_DIRECTORY) { /* operations about dir */
		free(jffs2_file);
		return -EACCES;
	}


	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.open(mte[partition_num], name, oflags, mode, jffs2_file);
	if (result != 0) {
		jffs_mutex_release(&jffs2_lock);
		free(jffs2_file);
		return jffs2_result_to_vfs(result);
	}
	/* save this pointer, it will be used when calling read(),write(),
	 * flush(), lessk(), and will be free when calling close()
	 */
	filep->f_priv = jffs2_file;
	filep->f_pos = jffs2_file->f_offset;
	jffs_mutex_release(&jffs2_lock);
	return 0;
}

static int vfs_jffs_close(FAR struct file *filep)
{
	int result;
	cyg_file *jffs2_file = NULL;

	LOS_ASSERT(filep->f_priv != NULL);
	jffs2_file = (cyg_file *)(filep->f_priv);

	/* regular file operations */
	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.close(jffs2_file);
	jffs_mutex_release(&jffs2_lock);
	if (result) {
		return jffs2_result_to_vfs(result);
	}
	return 0;
}

static ssize_t vfs_jffs_read(FAR struct file *filep, FAR char *buffer, size_t buflen)
{
	cyg_file *jffs2_file = NULL;
	struct CYG_UIO_TAG uio_s;
	struct CYG_IOVEC_TAG iovec;
	int result;

	LOS_ASSERT(filep->f_priv != NULL);
	jffs2_file = (cyg_file *)(filep->f_priv);
	uio_s.uio_iov = &iovec;
	uio_s.uio_iov->iov_base = buffer;
	uio_s.uio_iov->iov_len = buflen;
	uio_s.uio_iovcnt = 1; /* must be 1 */
	uio_s.uio_resid = uio_s.uio_iov->iov_len; /* seem no use in jffs2 */

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.read(jffs2_file, &uio_s);
	jffs_mutex_release(&jffs2_lock);
	if (result)
		return jffs2_result_to_vfs(result);

	/* update position */
	filep->f_pos= (loff_t)jffs2_file->f_offset;
	return uio_s.uio_iov->iov_len - uio_s.uio_resid;
}

static ssize_t vfs_jffs_write(FAR struct file *filep,
				FAR const char *buffer,
				size_t buflen)
{
	cyg_file *jffs2_file = NULL;
	struct CYG_UIO_TAG uio_s;
	struct CYG_IOVEC_TAG iovec;
	int result;

	if (filep->f_inode->mountflags == MS_RDONLY) {
		return -EACCES;
	}

	LOS_ASSERT(filep->f_priv != NULL);
	jffs2_file = (cyg_file *)(filep->f_priv);
	uio_s.uio_iov = &iovec;
	uio_s.uio_iov->iov_base = (void *)buffer;
	uio_s.uio_iov->iov_len = buflen;
	uio_s.uio_iovcnt = 1; /* must be 1 */

	uio_s.uio_resid = uio_s.uio_iov->iov_len; /* seem no use in jffs2 */

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.write(jffs2_file, &uio_s);
	jffs_mutex_release(&jffs2_lock);
	/* update position */
	filep->f_pos = (loff_t)jffs2_file->f_offset;
	if (result) {
		return jffs2_result_to_vfs(result);
	}
	return  uio_s.uio_iov->iov_len - uio_s.uio_resid;
}
static off_t vfs_jffs_seek(FAR struct file *filep, off_t offset, int whence)
{
	cyg_file *jffs2_file = NULL;
	int result;
	LOS_ASSERT(filep->f_priv != NULL);
	jffs2_file = (cyg_file *)(filep->f_priv);

	/* set offset as current offset */
	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.lseek(jffs2_file, &offset, whence);
	jffs_mutex_release(&jffs2_lock);
	if (result)
		return jffs2_result_to_vfs(result);
	/* update file position */
	filep->f_pos = (loff_t)offset;
	return offset;
}

static loff_t vfs_jffs_seek64(FAR struct file *filep, loff_t offset, int whence)
{
	return (loff_t)vfs_jffs_seek(filep, (off_t)offset, whence);
}

static int vfs_jffs_ioctl(FAR struct file *filep, int cmd, unsigned long arg)
{
	PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
	return -ENOSYS;
}

static int vfs_jffs_sync(FAR struct file *filep)
{
	PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
	return -ENOSYS;
}

static int vfs_jffs_dup(FAR const struct file *oldp, FAR struct file *newp)
{
	PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
	return -ENOSYS;
}

static int vfs_jffs_opendir(FAR struct inode *mountpt,
				FAR const char *relpath,
				FAR struct fs_dirent_s *dir)
{
#ifdef  CONFIG_JFFS2_NO_RELATIVEDIR
	#define FILE_OFFSET   2
#endif
	int result;
	cyg_file *jffs2_file = NULL;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;

	jffs2_file = malloc(sizeof(cyg_file));
	if (jffs2_file == NULL)
		return -ENOMEM;

	/* just escape '/' provided by vfs code */
	if ((relpath[0] == '/') && (relpath[1] == 0))
		relpath = jffs2_root_path;
	else if (relpath[0] == '/') /* name[0] still will be '/' */
		relpath ++;

	/* open dir */
	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_dir_operations.opendir(mte[partition_num], relpath, jffs2_file);
	jffs_mutex_release(&jffs2_lock);
	if (result) {
		free(jffs2_file);
		return jffs2_result_to_vfs(result);
	}
#ifdef  CONFIG_JFFS2_NO_RELATIVEDIR
	jffs2_file->f_offset = FILE_OFFSET;
#endif
	dir->u.fs_dir = (fs_dir_s)jffs2_file;
	/* save this pointer, it will be used by vfs_jffs2_getdents */
	return 0;

}

static int vfs_jffs_closedir(FAR struct inode *mountpt, FAR struct fs_dirent_s *dir)
{
	int result;
	cyg_file *jffs2_file = NULL;
	jffs2_file = (cyg_file *)dir->u.fs_dir;
	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.close(jffs2_file);
	jffs_mutex_release(&jffs2_lock);
	if (result)
		return jffs2_result_to_vfs(result);
	return 0;
}

static int vfs_jffs_readdir(FAR struct inode *mountpt, FAR struct fs_dirent_s *dir)
{
/* reduced value between dir->fd_dir.d_off and jffs2_file->f_offset */
#define REDUCED_VALUE    3
	cyg_file *jffs2_file = NULL;
	struct CYG_UIO_TAG uio_s;
	struct CYG_IOVEC_TAG iovec;
	struct jffs2_dirent jffs2_d;
	int result;
	uint32_t dst_name_size;

	jffs2_file = (cyg_file *)(dir->u.fs_dir);

	/* set jffs2_d */
	(void)memset_s(&jffs2_d, sizeof(struct jffs2_dirent), 0, sizeof(struct jffs2_dirent));
	/* set CYG_UIO_TAG uio_s */
	uio_s.uio_iov = &iovec;
	uio_s.uio_iov->iov_base = &jffs2_d;
	uio_s.uio_iov->iov_len = sizeof(struct jffs2_dirent);;
	uio_s.uio_iovcnt = 1; /* must be 1 */
	uio_s.uio_offset = 0; /* not used... */
	uio_s.uio_resid = uio_s.uio_iov->iov_len; /* seem no use in jffs2; */

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_dir_operations.readdir(jffs2_file, &uio_s);
	jffs_mutex_release(&jffs2_lock);

	if (result)
		return jffs2_result_to_vfs(result);

	dir->fd_dir.d_off = jffs2_file->f_offset - REDUCED_VALUE;
	dir->fd_dir.d_type = jffs2_d.d_type;
	dir->fd_dir.d_reclen = (uint16_t)sizeof(struct dirent);
	dst_name_size = sizeof(dir->fd_dir.d_name);
	result = strncpy_s(dir->fd_dir.d_name, dst_name_size, jffs2_d.d_name, dst_name_size - 1);
	if (result != EOK) {
		return -ENAMETOOLONG;
	}
	dir->fd_dir.d_name[dst_name_size - 1] = '\0';

	return OK;
}

static int vfs_jffs_rewinddir(FAR struct inode *mountpt,
				FAR struct fs_dirent_s *dir)
{
	int result;
	off_t pos = 0;
	cyg_file *jffs2_file = (cyg_file *)(dir->u.fs_dir);

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_dir_operations.lseekdir(jffs2_file, &pos, SEEK_SET);
	jffs_mutex_release(&jffs2_lock);

	if (result)
		return jffs2_result_to_vfs(result);
	return OK;
}

static int vfs_jffs_mkdir(FAR struct inode *mountpt, FAR const char *relpath, mode_t mode)
{
	int result;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;
	/* deal path */
	if (relpath[0] == '/')
		relpath++;

	if (mountpt->mountflags == MS_RDONLY)
		return -EACCES;

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_dir_inode_operations.mkdir(mte[partition_num], relpath, mode);
	jffs_mutex_release(&jffs2_lock);

	if (result)
		return jffs2_result_to_vfs(result);
	return OK;
}

static int vfs_jffs_chattr(FAR struct inode *mountpt, FAR const char *relpath, iattr *attr)
{
	int result;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;
	/* deal path */
	if (relpath[0] == '/')
		relpath++;

	if (mountpt->mountflags == MS_RDONLY)
		return -EACCES;

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_file_operations.chattr(mte[partition_num],relpath, attr);
	jffs_mutex_release(&jffs2_lock);

	if (result)
		return jffs2_result_to_vfs(result);
	return OK;
}


static int vfs_jffs_rmdir(FAR struct inode *mountpt, FAR const char *relpath)
{
	int result;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;

	/* deal path */
	if (relpath[0] == '/')
		relpath++;
	else if (relpath[0] == '\0')
		return -EBUSY;

	if (mountpt->mountflags == MS_RDONLY)
		return -EACCES;

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_dir_inode_operations.rmdir(mte[partition_num], relpath);
	jffs_mutex_release(&jffs2_lock);

	if (result)
		return jffs2_result_to_vfs(result);
	return OK;
}

static int vfs_jffs_unlink(FAR struct inode *mountpt, FAR const char *relpath)
{
	int result;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;
	struct jffs2_stat s;
	/* deal path */
	if (relpath[0] == '/')
		relpath++;

	if (mountpt->mountflags == MS_RDONLY)
		return -EACCES;

	/* judge file type, dir is to be delete by rmdir, others by unlink */
	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_fs_type.stat(mte[partition_num],relpath, &s);
	if (result) {
		jffs_mutex_release(&jffs2_lock);
		return jffs2_result_to_vfs(result);
	}
	switch (s.st_mode & JFFS2_S_IFMT) {
	case JFFS2_S_IFREG:
		result = jffs2_dir_inode_operations.unlink(mte[partition_num],relpath);
		break;
	case JFFS2_S_IFDIR:
		result = -EISDIR;
		break;
	default:
		/* unknown file type */
		jffs_mutex_release(&jffs2_lock);
		return -1;
	}
	jffs_mutex_release(&jffs2_lock);
	if (result)
		return jffs2_result_to_vfs(result);
	return 0;
}

static int vfs_jffs_rename(FAR struct inode *mountpt,
				FAR const char *oldrelpath,
				FAR const char *newrelpath)
{
	int result;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;
	if (*oldrelpath == '/')
		oldrelpath += 1;
	if (*newrelpath == '/')
		newrelpath += 1;

	if (mountpt->mountflags == MS_RDONLY)
		return -EACCES;

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_dir_inode_operations.rename(mte[partition_num],oldrelpath,newrelpath);
	jffs_mutex_release(&jffs2_lock);
	if (result)
		return jffs2_result_to_vfs(result);
	return 0;
}

static int vfs_jffs_stat(FAR struct inode *mountpt,
				FAR const char *relpath,
				FAR struct stat *buf)
{
	int result;
	struct jffs2_stat s;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;

	/* deal the path for jffs2 */
	if (relpath[0] == '/')
		relpath++;

	jffs_mutex_take(&jffs2_lock, (uint32_t)JFFS_WAITING_FOREVER);
	result = jffs2_fs_type.stat(mte[partition_num], relpath, &s);
	jffs_mutex_release(&jffs2_lock);

	if (result)
		return jffs2_result_to_vfs(result);
	/* convert to vfs stat structure */
	switch (s.st_mode & JFFS2_S_IFMT) {
	case JFFS2_S_IFREG:
		buf->st_mode = s.st_mode;
		break;

	case JFFS2_S_IFDIR:
		buf->st_mode = s.st_mode;
		break;

	default:
		buf->st_mode = DT_UNKNOWN; /* fixme */
		break;
	}

	buf->st_dev = 0;
	buf->st_size = s.st_size;
	buf->st_mtim.tv_sec = s.sddst_mtime;
	buf->st_mtim.tv_nsec = 0;
	buf->st_atim.tv_sec = s.sddst_atime;
	buf->st_atim.tv_nsec = 0;
	buf->st_ctim.tv_sec = s.sddst_ctime;
	buf->st_ctim.tv_nsec = 0;
	buf->st_blksize = BLOCK_SIZE; /* fixme: what's this field? */
	buf->st_ino = s.st_ino;
	buf->st_gid = s.st_gid;
	buf->st_uid = s.st_uid;
	buf->st_nlink = s.st_nlink;
	buf->st_blocks = s.st_size / BLOCK_SIZE;

	return 0;
}

static int vfs_jffs_statfs(FAR struct inode *mountpt, FAR struct statfs *buf)
{
	/* since the limit of unsigned long, so the max size of flash device is 4G */
	struct jffs2_fs_info info;
	mtd_partition *p = (mtd_partition *)mountpt->i_private;
	int partition_num = p->patitionnum;
	LOS_ASSERT(mte[partition_num]->data != 0);

	jffs2_get_info_from_sb((void *)mte[partition_num]->data, &info);
	buf->f_type = JFFS2_SUPER_MAGIC;
	buf->f_bsize = JFFS2_PAGE_SIZE;
	buf->f_blocks = (((uint64_t)info.nr_blocks) * info.sector_size) / JFFS2_PAGE_SIZE;
	buf->f_bfree = info.free_size / JFFS2_PAGE_SIZE;
	buf->f_bavail = buf->f_bfree;
	buf->f_namelen = CONFIG_JFFS2_ENTRY_NAME_MAX;
	buf->f_fsid.__val[0] = JFFS2_SUPER_MAGIC;
	buf->f_fsid.__val[1] = 1;
	buf->f_frsize = BLOCK_SIZE;
	buf->f_files = 0;
	buf->f_ffree = 0;
	return 0;
}

int JffsMutexCreate(void)
{
    if (LOS_MuxInit(&jffs2_lock, NULL) != LOS_OK) {
        PRINT_ERR("%s, LOS_MuxCreate failed\n", __FUNCTION__);
        return -1;
    } else {
        return 0;
    }
}

void JffsMutexDelete(void)
{
    (void)LOS_MuxDestroy(&jffs2_lock);
}

const struct mountpt_operations jffs_operations = {
	vfs_jffs_open,      /* open */
	vfs_jffs_close,     /* close */
	vfs_jffs_read,      /* read */
	vfs_jffs_write,     /* write */
	vfs_jffs_seek,      /* seek */
	vfs_jffs_ioctl,     /* ioctl */
	OsVfsFileMmap,      /* mmap */

	vfs_jffs_sync,      /* sync */
	vfs_jffs_dup,       /* dup */
	NULL,               /* fstat */
	NULL,               /* truncate */

	vfs_jffs_opendir,   /* opendir */
	vfs_jffs_closedir,  /* closedir */
	vfs_jffs_readdir,   /* readdir */

	vfs_jffs_rewinddir, /* rewinddir */

	vfs_jffs_bind,      /* bind */
	vfs_jffs_unbind,    /* unbind */
	vfs_jffs_statfs,    /* statfs */
	NULL,               /* virstatfs */
	vfs_jffs_unlink,    /* unlinke */
	vfs_jffs_mkdir,     /* mkdir */
	vfs_jffs_rmdir,     /* rmdir */
	vfs_jffs_rename,    /* rename */
	vfs_jffs_stat,      /* stat */
	NULL,               /* for utime */
	vfs_jffs_chattr,    /* chattr */
	vfs_jffs_seek64,    /* seek64 */
	NULL,               /* getlabel */
	NULL,               /* fallocate Contiguous blocks */
	NULL,               /* fallocate64 */
	NULL,               /* truncate64 */
	NULL,               /* fscheck */
	NULL,               /* map_pages */
	NULL,               /* readpage */
	NULL,               /* writepage */
};

FSMAP_ENTRY(jffs_fsmap, "jffs2", jffs_operations, TRUE, TRUE);

#endif
