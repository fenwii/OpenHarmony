#ifndef _PORTING_H
#define _PORTING_H

#include "los_mux.h"
#include "los_event.h"
#include "los_typedef.h"
#include "jffs2.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* the following should be same with os_sys_stat.h */
#define JFFS2_S_IFMT	 0x00000f000
#define JFFS2_S_IFDIR	 0040000
#define JFFS2_S_IFREG	 0100000

struct jffs2_fs_info {
	unsigned long   sector_size; /* a erasing block size*/
	unsigned long   nr_blocks; /* number of blocks in flash */
	unsigned long   free_size; /* size of free flash */
};

struct jffs2_stat {
    unsigned long   st_mode;     /* File mode */
    uint32_t        st_ino;      /* File serial number */
    uint32_t        st_dev;      /* ID of device containing file */
    unsigned long   st_nlink;    /* Number of hard links */
    unsigned long   st_uid;      /* User ID of the file owner */
    unsigned long   st_gid;      /* Group ID of the file's group */
    long  st_size;        /* File size (regular files only) */
    long  sddst_atime;    /* Last access time */
    long  sddst_mtime;    /* Last data modification time */
    long  sddst_ctime;    /* Last file status change time */
};

extern cyg_fileops jffs2_fileops;
extern cyg_fileops jffs2_dirops;
extern struct cyg_fstab_entry jffs2_fste;

time_t jffs2_get_timestamp(void);
void jffs2_get_info_from_sb(void *data, struct jffs2_fs_info *info);

void jffs_mutex_take(LosMux *mutex, uint32_t time_out);

void jffs_mutex_release(LosMux *mutex);

void jffs_mutex_create(LosMux *mutex);

void jffs_mutex_delete(LosMux *mutex);
void jffs_event_create(PEVENT_CB_S event_CB);
void jffs_event_send(PEVENT_CB_S event_CB, uint32_t events);
uint32_t jffs_event_recv(PEVENT_CB_S event_CB, uint32_t event_mask, uint32_t mode, uint32_t time_out);
void jffs_event_detach(PEVENT_CB_S event_CB);
void jffs_lock(void);
void jffs_unlock(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
