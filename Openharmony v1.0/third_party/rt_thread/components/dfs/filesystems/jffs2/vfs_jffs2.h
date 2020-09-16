/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __DFS_JFFS2_H__
#define __DFS_JFFS2_H__

#include "mtd_partition.h"
#include "os-ecos.h"
#include "fileio.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifndef NOR_FLASH_BOOT_SIZE
#define NOR_FLASH_BOOT_SIZE 0x100000
#endif

#define JFFS_WAITING_FOREVER              -1    /* Block forever until get resource. */


struct los_jffs2_operations {
    int (*mount)    (cyg_mtab_entry *mte, int partition_num);
    int (*stat)     (cyg_mtab_entry *mte, const char *name, struct jffs2_stat *buf);
    int (*open)     (cyg_mtab_entry *mte, const char *name, int flags,
                    int mode,  cyg_file *fte);
    int (*close)    (struct CYG_FILE_TAG *fp);
    int (*read)     (struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
    int (*write)    (struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
    int (*lseek)    (struct CYG_FILE_TAG *fp, off_t *apos, int whence);
    int (*opendir)  (cyg_mtab_entry *mte, const char *name, cyg_file *fte);
    int (*mkdir)    (cyg_mtab_entry *mte, const char *name, int mode);
    int (*rmdir)    (cyg_mtab_entry *mte, const char *name);
    int (*unlink)   (cyg_mtab_entry *mte, const char *name);
    int (*rename)   (cyg_mtab_entry *mte, const char *name1, const char *name2);
    int (*readdir)  (struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
    int (*lseekdir) (struct CYG_FILE_TAG *fp, off_t *pos, int whence);
    int (*umount)   (cyg_mtab_entry *mte);
    int (*chattr)   (cyg_mtab_entry *mte, const char *name, iattr *attr);
};

extern struct los_jffs2_operations jffs2_fs_type;
extern struct los_jffs2_operations jffs2_file_operations;
extern struct los_jffs2_operations jffs2_dir_operations;
extern struct los_jffs2_operations jffs2_dir_inode_operations;

int JffsMutexCreate(void);
void JffsMutexDelete(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
