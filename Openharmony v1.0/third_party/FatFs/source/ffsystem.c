/*------------------------------------------------------------------------*/
/* Sample Code of OS Dependent Functions for FatFs                        */
/* (C)ChaN, 2018                                                          */
/*------------------------------------------------------------------------*/


#include "ff.h"


void ff_memset (void* dst,
	int val,
	UINT cnt
)
{
	BYTE *d = (BYTE*)dst;

	do {
		*d++ = (BYTE)val;
	} while (--cnt);
}


int ff_strnlen(const void *str,
	size_t maxlen
)
{
	const BYTE *p = (const BYTE *)NULL;
	const BYTE *c = (const BYTE*)str;
	for (p = c; maxlen-- != 0 && *p != '\0'; ++p);

	return p - c;
}

/*------------------------------------------------------------------------*/
/* Allocate a memory block                                                */
/*------------------------------------------------------------------------*/

void* ff_memalloc (	/* Returns pointer to the allocated memory block (null if not enough core) */
	UINT msize		/* Number of bytes to allocate */
)
{
	void* ptr = NULL;

	if(msize == 0)
		return NULL;

	ptr = LOS_MemAlloc((void *)OS_SYS_MEM_ADDR,  msize);	/* Allocate a new memory block*/
	if (ptr != NULL) {
		ff_memset((void *)ptr, (int)0, msize);
	}

	return ptr;
}


/*------------------------------------------------------------------------*/
/* Free a memory block                                                    */
/*------------------------------------------------------------------------*/

void ff_memfree (
	void* mblock	/* Pointer to the memory block to free (nothing to do if null) */
)
{
	if (mblock == NULL)
		return;

	(VOID)LOS_MemFree((void *)OS_SYS_MEM_ADDR, mblock);
}



#if FF_FS_REENTRANT	/* Mutal exclusion */

/*------------------------------------------------------------------------*/
/* Create a Synchronization Object                                        */
/*------------------------------------------------------------------------*/
/* This function is called in f_mount() function to create a new
/  synchronization object for the volume, such as semaphore and mutex.
/  When a 0 is returned, the f_mount() function fails with FR_INT_ERR.
*/

//const osMutexDef_t Mutex[FF_VOLUMES];	/* Table of CMSIS-RTOS mutex */


int ff_cre_syncobj (	/* 1:Function succeeded, 0:Could not create the sync object */
	BYTE vol,			/* Corresponding volume (logical drive number) */
	FF_SYNC_t* sobj		/* Pointer to return the created sync object */
)
{
	int ret;


	ret = LOS_MuxInit(sobj, NULL);
	if (ret == LOS_OK ) {
		return TRUE;
	} else
		return FALSE;
}


/*------------------------------------------------------------------------*/
/* Delete a Synchronization Object                                        */
/*------------------------------------------------------------------------*/
/* This function is called in f_mount() function to delete a synchronization
/  object that created with ff_cre_syncobj() function. When a 0 is returned,
/  the f_mount() function fails with FR_INT_ERR.
*/

int ff_del_syncobj (	/* 1:Function succeeded, 0:Could not delete due to an error */
	FF_SYNC_t* sobj		/* Sync object tied to the logical drive to be deleted */
)
{
	int ret;
	ret = LOS_MuxDestroy(sobj);
	if(ret == LOS_OK) {
		return TRUE;
	} else {
		return FALSE;
	}
}


/*------------------------------------------------------------------------*/
/* Request Grant to Access the Volume                                     */
/*------------------------------------------------------------------------*/
/* This function is called on entering file functions to lock the volume.
/  When a 0 is returned, the file function fails with FR_TIMEOUT.
*/

int ff_req_grant (	/* 1:Got a grant to access the volume, 0:Could not get a grant */
	FF_SYNC_t* sobj	/* Sync object to wait */
)
{
	if (LOS_MuxLock(sobj, FF_FS_TIMEOUT) == LOS_OK) {
		return TRUE;
	}

	return FALSE;
}


/*------------------------------------------------------------------------*/
/* Release Grant to Access the Volume                                     */
/*------------------------------------------------------------------------*/
/* This function is called on leaving file functions to unlock the volume.
*/

void ff_rel_grant (
	FF_SYNC_t* sobj	/* Sync object to be signaled */
)
{
	(void)LOS_MuxUnlock(sobj);
}

#endif

