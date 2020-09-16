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
#include <stdio.h>
#include "nodelist.h"
#include "porting.h"

#if defined(CYGOPT_FS_JFFS2_GCTHREAD)

#define GC_THREAD_FLAG_TRIG 1
#define GC_THREAD_FLAG_STOP 2
#define GC_THREAD_FLAG_HAS_EXIT 4

#endif


static void jffs2_garbage_collect_thread(unsigned long data);

void jffs2_garbage_collect_trigger(struct jffs2_sb_info *c)
{
	struct super_block *sb = OFNI_BS_2SFFJ(c);
	/* Wake up the thread */
	jffs2_dbg(1, "jffs2_garbage_collect_trigger\n");
	jffs_event_send(&sb->s_gc_thread_flags, GC_THREAD_FLAG_TRIG);
}

extern struct MtdNorDev jffs_part[CONFIG_MTD_PATTITION_NUM];

/* This must only ever be called when no GC thread is currently running */
void jffs2_start_garbage_collect_thread(struct jffs2_sb_info *c)
{
	 struct super_block *sb = OFNI_BS_2SFFJ(c);
	 TSK_INIT_PARAM_S stGcTask;

	 if (c == NULL)
		return;

	 if (sb->s_root == NULL)
		return;

	 jffs_event_create(&sb->s_gc_thread_flags);

	 /* Start the thread. Doesn't matter if it fails -- it's only an
	  * optimisation anyway */
	(void)memset_s(&stGcTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));

	stGcTask.pfnTaskEntry = (TSK_ENTRY_FUNC)jffs2_garbage_collect_thread;
	stGcTask.auwArgs[0] = (UINTPTR)c;
	stGcTask.uwStackSize  = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
	stGcTask.pcName = "jffs2_gc_thread";
#if (LOSCFG_KERNEL_SMP == YES)
	unsigned int i;
	for (i = 0; i < CONFIG_MTD_PATTITION_NUM; i++) {
		if (sb->s_dev == &jffs_part[i])
			break;
	}
	stGcTask.usCpuAffiMask = CPUID_TO_AFFI_MASK(i % LOSCFG_KERNEL_CORE_NUM);
#endif
	stGcTask.usTaskPrio = CYGNUM_JFFS2_GC_THREAD_PRIORITY;

	if (LOS_TaskCreate(&sb->s_gc_thread, &stGcTask))
		JFFS2_ERROR("Create gc task failed!!!\n");
}

void jffs2_stop_garbage_collect_thread(struct jffs2_sb_info *c)
{
	 struct super_block *sb = OFNI_BS_2SFFJ(c);

	 JFFS2_DEBUG("jffs2_stop_garbage_collect_thread\n");
	 /* Stop the thread and wait for it if necessary */

	 jffs_event_send(&sb->s_gc_thread_flags,GC_THREAD_FLAG_STOP);

	 JFFS2_DEBUG("jffs2_stop_garbage_collect_thread wait\n");

	 (void)jffs_event_recv(&sb->s_gc_thread_flags,
			GC_THREAD_FLAG_HAS_EXIT,
			LOS_WAITMODE_OR | LOS_WAITMODE_CLR,
			LOS_WAIT_FOREVER);

	 // Kill and free the resources ...  this is safe due to the flag
	 // from the thread.
	 (void)LOS_TaskDelete(sb->s_gc_thread);
	 jffs_event_detach(&sb->s_gc_thread_flags);
}

static void jffs2_garbage_collect_thread(unsigned long data)
{
	struct jffs2_sb_info *c = (struct jffs2_sb_info *)data;
	struct super_block *sb = OFNI_BS_2SFFJ(c);
	unsigned int flag = 0;

	jffs2_dbg(1, "jffs2_garbage_collect_thread START\n");
	while(1) {
		flag=jffs_event_recv(&sb->s_gc_thread_flags,
			GC_THREAD_FLAG_TRIG | GC_THREAD_FLAG_STOP,
			LOS_WAITMODE_OR | LOS_WAITMODE_CLR,
			LOS_WAIT_FOREVER
		);
		if (flag & GC_THREAD_FLAG_STOP)
			break;

		jffs2_dbg(1, "jffs2: GC THREAD GC BEGIN\n");

		if (sb->s_root == NULL)
			return;

		if (jffs2_garbage_collect_pass(c) == -ENOSPC) {
			PRINTK("No space for garbage collection. "
			"Aborting JFFS2 GC thread\n");
			break;
		}
		jffs2_dbg(1, "jffs2: GC THREAD GC END\n");
	}
	JFFS2_DEBUG("jffs2_garbage_collect_thread EXIT\n");
	jffs_event_send(&sb->s_gc_thread_flags,GC_THREAD_FLAG_HAS_EXIT);
}
