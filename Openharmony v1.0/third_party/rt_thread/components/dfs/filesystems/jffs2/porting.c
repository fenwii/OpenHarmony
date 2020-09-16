#include <linux/kernel.h>
#include "nodelist.h"
#include "porting.h"

time_t jffs2_get_timestamp(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		return 0;
	return (uint32_t)(tv.tv_sec);
}

void jffs2_get_info_from_sb(void *data, struct jffs2_fs_info *info)
{
	struct jffs2_fs_info;
	struct super_block *jffs2_sb = NULL;
	struct jffs2_sb_info *c = NULL;

	jffs2_sb = (struct super_block *)(data);
	c = JFFS2_SB_INFO(jffs2_sb);

	info->sector_size = c->sector_size;
	info->nr_blocks = c->nr_blocks;
	info->free_size = c->free_size + c->dirty_size; // fixme need test!
}

static pthread_mutex_t jffs_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

void jffs_lock(void)
{
	(void)pthread_mutex_lock(&jffs_mutex);
}

void jffs_unlock(void)
{
	(void)pthread_mutex_unlock(&jffs_mutex);
}

void jffs_mutex_take(LosMux *mutex, uint32_t time_out)
{
    (void)LOS_MuxLock(mutex, time_out);
}

void jffs_mutex_release(LosMux *mutex)
{
    (void)LOS_MuxUnlock(mutex);
}

void jffs_mutex_create(LosMux *mutex)
{
    (void)LOS_MuxInit(mutex, NULL);
}

void jffs_mutex_delete(LosMux *mutex)
{
    (void)LOS_MuxDestroy(mutex);
}

void jffs_event_create(PEVENT_CB_S event_CB)
{
	(void)LOS_EventInit(event_CB);
}

void jffs_event_send(PEVENT_CB_S event_CB, uint32_t events)
{
	(void)LOS_EventWrite(event_CB, events);
}

uint32_t jffs_event_recv(PEVENT_CB_S event_CB, uint32_t event_mask, uint32_t mode, uint32_t time_out)
{
	return(LOS_EventRead(event_CB, event_mask, mode, time_out));
}

void jffs_event_detach(PEVENT_CB_S event_CB)
{
	(void)LOS_EventWrite(event_CB, 0xFFFFFFFF);
}


