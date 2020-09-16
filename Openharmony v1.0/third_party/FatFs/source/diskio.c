/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* Declarations of disk functions */
#include "fs/fs.h"
#include "string.h"
#include "disk.h"

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

#define CARD_UNPLUGED   1
extern int get_cardstatus(int pdrv);
#define GET_CARD_STATUS					\
	do {						\
		if (get_cardstatus(pdrv) == 0)		\
			return STA_NOINIT;		\
	} while (0)
extern  struct tm tm;

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	QWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	int result;

	result = los_part_read((int)pdrv, (void *)buff, sector, (UINT32)count);

	if (result == 0)
		return RES_OK;
	else
		return RES_ERROR;
}

DRESULT disk_raw_read (int id, void *buff, QWORD sector, UINT32 count)
{
	int result;

	result = los_disk_read(id, buff, sector, count);

	if (result == 0)
		return RES_OK;
	else
		return RES_ERROR;
}


/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	QWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	int result;

	result = los_part_write((int)pdrv, (void *)buff, sector, (UINT32)count);

	if (result == 0)
		return RES_OK;
	else
		return RES_ERROR;
}

DRESULT disk_raw_write(int id, void *buff, QWORD sector, UINT32 count){
	int result;
	void *uwBuff = buff;

	result = los_disk_write(id, (const void*)uwBuff, sector, count);

	if (result == 0)
		return RES_OK;
	else
		return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	int result;

	result = los_part_ioctl((int)pdrv, (int)cmd, buff);

	if (result == 0)
		return RES_OK;
	else
		return RES_ERROR;
}

DWORD get_fattime (void)
{
	time_t seconds = 0;
	struct tm local_time = {0};

	seconds = time(NULL);

	if (localtime_r(&seconds, &local_time) == NULL)
		return 0;
	if ((local_time.tm_year + 1900) < 1980) {	/* year must start at 1980 */
		return 0;
	}

	/* get system time */
	return  ((DWORD)(local_time.tm_year - 80) << 25) |
			((DWORD)(local_time.tm_mon + 1) << 21) |
			((DWORD)local_time.tm_mday << 16) |
			((DWORD)local_time.tm_hour << 11) |
			((DWORD)local_time.tm_min << 5) |
			((DWORD)local_time.tm_sec >> 1);
}


