/* $FreeBSD: releng/11.4/sys/dev/usb/usb_process.c 331722 2018-03-29 02:50:57Z eadler $ */
/*-
 * Copyright (c) 2008 Hans Petter Selasky. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "implementation/global_implementation.h"

struct usb_process usb_process[USB_PROC_MAX];
struct mtx sched_lock;

#undef USB_DEBUG_VAR
#define USB_DEBUG_VAR   usb_proc_debug
#ifdef LOSCFG_USB_DEBUG
static int usb_proc_debug;
void
usb_process_debug_func(int level)
{
	usb_proc_debug = level;
	PRINTK("The level of usb process debug is %d\n", level);
}
DEBUG_MODULE(process, usb_process_debug_func);
#endif

SPIN_LOCK_INIT(g_usb_process_queue_spinlock);

/*------------------------------------------------------------------------*
 *	usb_process
 *
 * This function is the USB process dispatcher.
 *------------------------------------------------------------------------*/
static void*
usb_process_thread(UINTPTR para)
{
	struct usb_process *up = (struct usb_process*)para;
	struct usb_proc_msg *pm;
	struct thread *td;
	uint32_t int_save;

	/* in case of attach error, check for suspended */
	USB_THREAD_SUSPEND_CHECK();

	/* adjust priority */
	td = (struct thread *)(UINTPTR)curthread;
	thread_lock(td);
	sched_prio(td, up->up_prio);
	thread_unlock(td);

	mtx_lock(up->up_mtx);

	up->up_curtd = td;
	while (1) {
		if (up->up_gone)
			break;

		/*
		 * NOTE to reimplementors: dequeueing a command from the
		 * "used" queue and executing it must be atomic, with regard
		 * to the "up_mtx" mutex. That means any attempt to queue a
		 * command by another thread must be blocked until either:
		 *
		 * 1) the command sleeps
		 *
		 * 2) the command returns
		 *
		 * Here is a practical example that shows how this helps
		 * solving a problem:
		 *
		 * Assume that you want to set the baud rate on a USB serial
		 * device. During the programming of the device you don't
		 * want to receive nor transmit any data, because it will be
		 * garbage most likely anyway. The programming of our USB
		 * device takes 20 milliseconds and it needs to call
		 * functions that sleep.
		 *
		 * Non-working solution: Before we queue the programming
		 * command, we stop transmission and reception of data. Then
		 * we queue a programming command. At the end of the
		 * programming command we enable transmission and reception
		 * of data.
		 *
		 * Problem: If a second programming command is queued while the
		 * first one is sleeping, we end up enabling transmission
		 * and reception of data too early.
		 *
		 * Working solution: Before we queue the programming command,
		 * we stop transmission and reception of data. Then we queue
		 * a programming command. Then we queue a second command
		 * that only enables transmission and reception of data.
		 *
		 * Why it works: If a second programming command is queued
		 * while the first one is sleeping, then the queueing of a
		 * second command to enable the data transfers, will cause
		 * the previous one, which is still on the queue, to be
		 * removed from the queue, and re-inserted after the last
		 * baud rate programming command, which then gives the
		 * desired result.
		 */

		LOS_SpinLockSave(&g_usb_process_queue_spinlock, &int_save);
		pm = TAILQ_FIRST(&up->up_qhead);
		LOS_SpinUnlockRestore(&g_usb_process_queue_spinlock, int_save);
		if (pm) {
			DPRINTF("Message pm=%p, cb=%p (enter)\n",
			    pm, pm->pm_callback);

			if (pm->pm_callback)
				(pm->pm_callback) (pm);

			LOS_SpinLockSave(&g_usb_process_queue_spinlock, &int_save);
			if (pm == TAILQ_FIRST(&up->up_qhead)) {
				/* nothing changed */
				TAILQ_REMOVE(&up->up_qhead, pm, pm_qentry);
				pm->pm_qentry.tqe_prev = NULL;
			}
			LOS_SpinUnlockRestore(&g_usb_process_queue_spinlock, int_save);
			DPRINTF("Message pm=%p (leave)\n", pm);

			continue;
		}
		/* end if messages - check if anyone is waiting for sync */
		if (up->up_dsleep) {
			up->up_dsleep = 0;
			(void)cv_broadcast(&up->up_drain);
		}
		up->up_msleep = 1;
		(void)cv_wait(&up->up_cv, up->up_mtx);
	}

	up->up_ptr = NULL;
	(void)cv_signal(&up->up_cv);
	mtx_unlock(up->up_mtx);
	USB_THREAD_EXIT(0);
	return NULL;
}

uint32_t
usb_os_task_creat(pthread_t *taskid, TSK_ENTRY_FUNC func, uint32_t prio, const char *nm, UINTPTR para)
{
	uint32_t ret;
	TSK_INIT_PARAM_S attr;

	(void)memset_s(&attr, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));

	attr.pfnTaskEntry = func;
	attr.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
	attr.auwArgs[0] = (UINTPTR)para;
	attr.usTaskPrio = prio;
	attr.pcName = (char *)nm;
	attr.uwResved = LOS_TASK_STATUS_DETACHED;

	ret = LOS_TaskCreate((uint32_t *)taskid, &attr);
	if (ret != LOS_OK) {
		PRINTK("create %s task error!\n",nm);
	}
	return (ret);
}

uint32_t
usb_os_task_delete(pthread_t taskid)
{
	uint32_t ret;

	ret = LOS_TaskDelete(taskid);
	if (ret != LOS_OK) {
		PRINTK("delete task error!\n");
	}
	return (ret);
}

/*------------------------------------------------------------------------*
 *	usb_proc_create
 *
 * This function will create a process using the given "prio" that can
 * execute callbacks. The mutex pointed to by "p_mtx" will be applied
 * before calling the callbacks and released after that the callback
 * has returned. The structure pointed to by "up" is assumed to be
 * zeroed before this function is called.
 *
 * Return values:
 *    0: success
 * Else: failure
 *------------------------------------------------------------------------*/
int
usb_proc_create(struct usb_process *up, struct mtx *p_mtx,
    const char *pmesg, uint8_t prio)
{
	uint32_t ret;
	pthread_t td = 0;
	up->up_mtx = p_mtx;
	up->up_prio = prio;

	TAILQ_INIT(&up->up_qhead);

	cv_init(&up->up_cv, "-");
	cv_init(&up->up_drain, "usbdrain");

	ret = usb_os_task_creat(&td, (TSK_ENTRY_FUNC)usb_process_thread, prio, pmesg, (UINTPTR)up);
	if (ret != LOS_OK) {
		DPRINTFN(0, "Unable to create USB process.");
		up->up_ptr = NULL;
		goto error;
	}
	up->up_ptr = (struct thread *)(UINTPTR)td;
	return (0);

error:
	usb_proc_free(up);
	return (ENOMEM);
}

/*------------------------------------------------------------------------*
 *	usb_proc_free
 *
 * NOTE: If the structure pointed to by "up" is all zero, this
 * function does nothing.
 *
 * NOTE: Messages that are pending on the process queue will not be
 * removed nor called.
 *------------------------------------------------------------------------*/
void
usb_proc_free(struct usb_process *up)
{
	/* check if not initialised */
	if (up->up_mtx == NULL)
		return;

	usb_proc_drain(up);

	cv_destroy(&up->up_cv);
	cv_destroy(&up->up_drain);

	/* make sure that we do not enter here again */
	up->up_mtx = NULL;
}

/*------------------------------------------------------------------------*
 *	usb_proc_msignal
 *
 * This function will queue one of the passed USB process messages on
 * the USB process queue. The first message that is not already queued
 * will get queued. If both messages are already queued the one queued
 * last will be removed from the queue and queued in the end. The USB
 * process mutex must be locked when calling this function. This
 * function exploits the fact that a process can only do one callback
 * at a time. The message that was queued is returned.
 *------------------------------------------------------------------------*/
void   *
usb_proc_msignal(struct usb_process *up, void *_pm0, void *_pm1)
{
	struct usb_proc_msg *pm0 = _pm0;
	struct usb_proc_msg *pm1 = _pm1;
	struct usb_proc_msg *pm2;
	usb_size_t d;
	uint8_t t;
	uint32_t int_save;

	/* check if gone, return dummy value */
	if (up->up_gone)
		return (_pm0);

	t = 0;

	LOS_SpinLockSave(&g_usb_process_queue_spinlock, &int_save);
	if (pm0->pm_qentry.tqe_prev) {
		t |= 1;
	}
	if (pm1->pm_qentry.tqe_prev) {
		t |= 2;
	}
	if (t == 0) {
		/*
		 * No entries are queued. Queue "pm0" and use the existing
		 * message number.
		 */
		pm2 = pm0;
	} else if (t == 1) {
		/* Check if we need to increment the message number. */
		if (pm0->pm_num == up->up_msg_num) {
			up->up_msg_num++;
		}
		pm2 = pm1;
	} else if (t == 2) {
		/* Check if we need to increment the message number. */
		if (pm1->pm_num == up->up_msg_num) {
			up->up_msg_num++;
		}
		pm2 = pm0;
	} else if (t == 3) {
		/*
		 * Both entries are queued. Re-queue the entry closest to
		 * the end.
		 */
		d = (pm1->pm_num - pm0->pm_num);

		/* Check sign after subtraction */
		if (d & 0x80000000) {
			pm2 = pm0;
		} else {
			pm2 = pm1;
		}

		TAILQ_REMOVE(&up->up_qhead, pm2, pm_qentry);
		pm2->pm_qentry.tqe_prev = NULL;
	} else {
		pm2 = NULL;		/* panic - should not happen */
	}

	DPRINTF(" t=%u, num=%u\n", t, up->up_msg_num);

	/* Put message last on queue */

	pm2->pm_num = up->up_msg_num;
	TAILQ_INSERT_TAIL(&up->up_qhead, pm2, pm_qentry);
	LOS_SpinUnlockRestore(&g_usb_process_queue_spinlock, int_save);

	/* Check if we need to wakeup the USB process. */

	up->up_msleep = 0;	/* save "cv_signal()" calls */
	(void)cv_signal(&up->up_cv);

	return (pm2);
}

/*------------------------------------------------------------------------*
 *	usb_proc_is_gone
 *
 * Return values:
 *    0: USB process is running
 * Else: USB process is tearing down
 *------------------------------------------------------------------------*/
uint8_t
usb_proc_is_gone(struct usb_process *up)
{
	if (up->up_gone) {
		return (1);
	}

	/*
	 * Allow calls when up_mtx is NULL, before the USB process
	 * structure is initialised.
	 */
	if (up->up_mtx != NULL) {
		mtx_assert(up->up_mtx, MA_OWNED);
	}
	return (0);
}

/*------------------------------------------------------------------------*
 *	usb_proc_mwait
 *
 * This function will return when the USB process message pointed to
 * by "pm" is no longer on a queue. This function must be called
 * having "up->up_mtx" locked.
 *------------------------------------------------------------------------*/
void
usb_proc_mwait(struct usb_process *up, void *_pm0, void *_pm1)
{
	struct usb_proc_msg *pm0 = _pm0;
	struct usb_proc_msg *pm1 = _pm1;
	uint32_t int_save;

	/* check if gone */
	if (up->up_gone)
		return;

	mtx_assert(up->up_mtx, MA_OWNED);

	if (up->up_curtd == (struct thread *)(UINTPTR)curthread) {
		LOS_SpinLockSave(&g_usb_process_queue_spinlock, &int_save);
		/* Just remove the messages from the queue. */
		if (pm0->pm_qentry.tqe_prev) {
			TAILQ_REMOVE(&up->up_qhead, pm0, pm_qentry);
			pm0->pm_qentry.tqe_prev = NULL;
		}
		if (pm1->pm_qentry.tqe_prev) {
			TAILQ_REMOVE(&up->up_qhead, pm1, pm_qentry);
			pm1->pm_qentry.tqe_prev = NULL;
		}
		LOS_SpinUnlockRestore(&g_usb_process_queue_spinlock, int_save);
	} else
		while (pm0->pm_qentry.tqe_prev ||
		    pm1->pm_qentry.tqe_prev) {
			/* check if config thread is gone */
			if (up->up_gone)
				break;
			up->up_dsleep = 1;
			(void)cv_wait(&up->up_drain, up->up_mtx);
		}
}

/*------------------------------------------------------------------------*
 *	usb_proc_drain
 *
 * This function will tear down an USB process, waiting for the
 * currently executing command to return.
 *
 * NOTE: If the structure pointed to by "up" is all zero,
 * this function does nothing.
 *------------------------------------------------------------------------*/
void
usb_proc_drain(struct usb_process *up)
{
	/* check if not initialised */
	if (up->up_mtx == NULL) {
		return;
	}

	/* handle special case with Giant */
	if (up->up_mtx != &Giant) {
		mtx_assert(up->up_mtx, MA_NOTOWNED);
	}

	mtx_lock(up->up_mtx);

	/* Set the gone flag */

	up->up_gone = 1;

	while (up->up_ptr) {

		/* Check if we need to wakeup the USB process */

		if (up->up_msleep || up->up_csleep) {
			up->up_msleep = 0;
			up->up_csleep = 0;
			(void)cv_signal(&up->up_cv);
		}
		(void)cv_wait(&up->up_cv, up->up_mtx);
	}
	/* Check if someone is waiting - should not happen */

	if (up->up_dsleep) {
		up->up_dsleep = 0;
		(void)cv_broadcast(&up->up_drain);
		DPRINTF("WARNING: Someone is waiting "
		    "for USB process drain!\n");
	}
	mtx_unlock(up->up_mtx);
}

/*------------------------------------------------------------------------*
 *	usb_proc_rewakeup
 *
 * This function is called to re-wakeup the given USB
 * process. This usually happens after that the USB system has been in
 * polling mode, like during a panic. This function must be called
 * having "up->up_mtx" locked.
 *------------------------------------------------------------------------*/
void
usb_proc_rewakeup(struct usb_process *up)
{
	/* check if not initialised */
	if (up->up_mtx == NULL)
		return;
	/* check if gone */
	if (up->up_gone)
		return;

	mtx_assert(up->up_mtx, MA_OWNED);

	if (up->up_msleep == 0) {
		/* re-wakeup */
		(void)cv_signal(&up->up_cv);
	}
}

/*------------------------------------------------------------------------*
 *	usb_proc_is_called_from
 *
 * This function will return non-zero if called from inside the USB
 * process passed as first argument. Else this function returns zero.
 *------------------------------------------------------------------------*/
int
usb_proc_is_called_from(struct usb_process *up)
{
	return (up->up_curtd == (struct thread *)(UINTPTR)curthread);
}

#undef USB_DEBUG_VAR
