/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem Module  R0.13c                              /
/-----------------------------------------------------------------------------/
/
/ Copyright (C) 2018, ChaN, all right reserved.
/
/ FatFs module is an open source software. Redistribution and use of FatFs in
/ source and binary forms, with or without modification, are permitted provided
/ that the following condition is met:
/
/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/---------------------------------------------------------------------------*/


#include "ff.h"			/* Declarations of FatFs API */
#include <user_copy.h>
#include "diskio.h"		/* Declarations of device I/O functions */

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
#include "virpartff.h"
#endif

/*--------------------------------------------------------------------------

   Module Private Definitions

---------------------------------------------------------------------------*/

#if FF_DEFINED != 86604	/* Revision ID */
#error Wrong include file (ff.h).
#endif


/* Limits and boundaries */
#define MAX_DIR		0x200000		/* Max size of FAT directory */
#define MAX_FAT12	0xFF5			/* Max FAT12 clusters (differs from specs, but right for real DOS/Windows behavior) */
#define MAX_FAT16	0xFFF5			/* Max FAT16 clusters (differs from specs, but right for real DOS/Windows behavior) */
#define MAX_FAT32	0x0FFFFFF5		/* Max FAT32 clusters (not specified, practical limit) */


/* Character code support macros */
#define IsUpper(c)		((c) >= 'A' && (c) <= 'Z')
#define IsLower(c)		((c) >= 'a' && (c) <= 'z')
#define IsDigit(c)		((c) >= '0' && (c) <= '9')
#define IsSurrogate(c)	((c) >= 0xD800 && (c) <= 0xDFFF)
#define IsSurrogateH(c)	((c) >= 0xD800 && (c) <= 0xDBFF)
#define IsSurrogateL(c)	((c) >= 0xDC00 && (c) <= 0xDFFF)


/* Additional file access control and file status flags for internal use */
#define FA_SEEKEND	0x20	/* Seek to end of the file on file open */
#define FA_MODIFIED	0x40	/* File has been modified */
#define FA_DIRTY	0x80	/* FIL.buf[] needs to be written-back */


/* Additional file attribute bits for internal use */
#define AM_VOL		0x08	/* Volume label */
#define AM_LFN		0x0F	/* LFN entry */
#define AM_MASK		0x3F	/* Mask of defined bits */


/* Name status flags in fn[11] */
#define NSFLAG		11		/* Index of the name status byte */
#define NS_LOSS		0x01	/* Out of 8.3 format */
#define NS_LFN		0x02	/* Force to create LFN entry */
#define NS_LAST		0x04	/* Last segment */
#define NS_BODY		0x08	/* Lower case flag (body) */
#define NS_EXT		0x10	/* Lower case flag (ext) */
#define NS_DOT		0x20	/* Dot entry */
#define NS_NOLFN	0x40	/* Do not find LFN */
#define NS_NONAME	0x80	/* Not followed */


/* FatFs refers the FAT structure as simple byte array instead of structure member
/ because the C structure is not binary compatible between different platforms */

#define BS_JmpBoot			0		/* x86 jump instruction (3-byte) */
#define BS_OEMName			3		/* OEM name (8-byte) */
#define BPB_BytsPerSec		11		/* Sector size [byte] (WORD) */
#define BPB_SecPerClus		13		/* Cluster size [sector] (BYTE) */
#define BPB_RsvdSecCnt		14		/* Size of reserved area [sector] (WORD) */
#define BPB_NumFATs			16		/* Number of FATs (BYTE) */
#define BPB_RootEntCnt		17		/* Size of root directory area for FAT [entry] (WORD) */
#define BPB_TotSec16		19		/* Volume size (16-bit) [sector] (WORD) */
#define BPB_Media			21		/* Media descriptor byte (BYTE) */
#define BPB_FATSz16			22		/* FAT size (16-bit) [sector] (WORD) */
#define BPB_SecPerTrk		24		/* Number of sectors per track for int13h [sector] (WORD) */
#define BPB_NumHeads		26		/* Number of heads for int13h (WORD) */
#define BPB_HiddSec			28		/* Volume offset from top of the drive (DWORD) */
#define BPB_TotSec32		32		/* Volume size (32-bit) [sector] (DWORD) */
#define BS_DrvNum			36		/* Physical drive number for int13h (BYTE) */
#define BS_NTres			37		/* WindowsNT error flag (BYTE) */
#define BS_BootSig			38		/* Extended boot signature (BYTE) */
#define BS_VolID			39		/* Volume serial number (DWORD) */
#define BS_VolLab			43		/* Volume label string (8-byte) */
#define BS_FilSysType		54		/* Filesystem type string (8-byte) */
#define BS_BootCode			62		/* Boot code (448-byte) */
#define BS_55AA				510		/* Signature word (WORD) */

#define BPB_FATSz32			36		/* FAT32: FAT size [sector] (DWORD) */
#define BPB_ExtFlags32		40		/* FAT32: Extended flags (WORD) */
#define BPB_FSVer32			42		/* FAT32: Filesystem version (WORD) */
#define BPB_RootClus32		44		/* FAT32: Root directory cluster (DWORD) */
#define BPB_FSInfo32		48		/* FAT32: Offset of FSINFO sector (WORD) */
#define BPB_BkBootSec32		50		/* FAT32: Offset of backup boot sector (WORD) */
#define BS_DrvNum32			64		/* FAT32: Physical drive number for int13h (BYTE) */
#define BS_NTres32			65		/* FAT32: Error flag (BYTE) */
#define BS_BootSig32		66		/* FAT32: Extended boot signature (BYTE) */
#define BS_VolID32			67		/* FAT32: Volume serial number (DWORD) */
#define BS_VolLab32			71		/* FAT32: Volume label string (8-byte) */
#define BS_FilSysType32		82		/* FAT32: Filesystem type string (8-byte) */
#define BS_BootCode32		90		/* FAT32: Boot code (420-byte) */

#define DIR_Name			0		/* Short file name (11-byte) */
#define DIR_Attr			11		/* Attribute (BYTE) */
#define DIR_NTres			12		/* Lower case flag (BYTE) */
#define DIR_CrtTime10		13		/* Created time sub-second (BYTE) */
#define DIR_CrtTime			14		/* Created time (DWORD) */
#define DIR_LstAccDate		18		/* Last accessed date (WORD) */
#define DIR_FstClusHI		20		/* Higher 16-bit of first cluster (WORD) */
#define DIR_ModTime			22		/* Modified time (DWORD) */
#define DIR_FstClusLO		26		/* Lower 16-bit of first cluster (WORD) */
#define DIR_FileSize		28		/* File size (DWORD) */
#define LDIR_Ord			0		/* LFN: LFN order and LLE flag (BYTE) */
#define LDIR_Attr			11		/* LFN: LFN attribute (BYTE) */
#define LDIR_Type			12		/* LFN: Entry type (BYTE) */
#define LDIR_Chksum			13		/* LFN: Checksum of the SFN (BYTE) */
#define LDIR_FstClusLO		26		/* LFN: MBZ field (WORD) */

#define SZDIRE				32		/* Size of a directory entry */
#define DDEM				0xE5	/* Deleted directory entry mark set to DIR_Name[0] */
#define RDDEM				0x05	/* Replacement of the character collides with DDEM */
#define LLEF				0x40	/* Last long entry flag in LDIR_Ord */

#define FSI_LeadSig			0		/* FAT32 FSI: Leading signature (DWORD) */
#define FSI_StrucSig		484		/* FAT32 FSI: Structure signature (DWORD) */
#define FSI_Free_Count		488		/* FAT32 FSI: Number of free clusters (DWORD) */
#define FSI_Nxt_Free		492		/* FAT32 FSI: Last allocated cluster (DWORD) */

#define MBR_Table			446		/* MBR: Offset of partition table in the MBR */
#define SZ_PTE				16		/* MBR: Size of a partition table entry */
#define PTE_Boot			0		/* MBR PTE: Boot indicator */
#define PTE_StHead			1		/* MBR PTE: Start head */
#define PTE_StSec			2		/* MBR PTE: Start sector */
#define PTE_StCyl			3		/* MBR PTE: Start cylinder */
#define PTE_System			4		/* MBR PTE: System ID */
#define PTE_EdHead			5		/* MBR PTE: End head */
#define PTE_EdSec			6		/* MBR PTE: End sector */
#define PTE_EdCyl			7		/* MBR PTE: End cylinder */
#define PTE_StLba			8		/* MBR PTE: Start in LBA */
#define PTE_SizLba			12		/* MBR PTE: Size in LBA */


/* Post process on fatal error in the file operations */
#define ABORT(fs, res)		{ fp->err = (BYTE)(res); LEAVE_FF(fs, res); }


/* Re-entrancy related */
#if FF_FS_REENTRANT
#if FF_USE_LFN == 1
#error Static LFN work area cannot be used at thread-safe configuration
#endif
#define LEAVE_FF(fs, res)	{ unlock_fs(fs, res); return res; }
#else
#define LEAVE_FF(fs, res)	return res
#endif


/* Definitions of sector size */
#if (FF_MAX_SS < FF_MIN_SS) || (FF_MAX_SS != 512 && FF_MAX_SS != 1024 && FF_MAX_SS != 2048 && FF_MAX_SS != 4096) || (FF_MIN_SS != 512 && FF_MIN_SS != 1024 && FF_MIN_SS != 2048 && FF_MIN_SS != 4096)
#error Wrong sector size configuration
#endif


/* Timestamp */
#if FF_FS_NORTC == 1
#if FF_NORTC_YEAR < 1980 || FF_NORTC_YEAR > 2107 || FF_NORTC_MON < 1 || FF_NORTC_MON > 12 || FF_NORTC_MDAY < 1 || FF_NORTC_MDAY > 31
#error Invalid FF_FS_NORTC settings
#endif
#define GET_FATTIME()	((DWORD)(FF_NORTC_YEAR - 1980) << 25 | (DWORD)FF_NORTC_MON << 21 | (DWORD)FF_NORTC_MDAY << 16)
#else
#define GET_FATTIME()	get_fattime()
#endif


/* File lock controls */
#if FF_FS_LOCK != 0
#if FF_FS_READONLY
#error FF_FS_LOCK must be 0 at read-only configuration
#endif
typedef struct {
	FATFS *fs;		/* Object ID 1, volume (NULL:blank entry) */
	DWORD clu;		/* Object ID 2, containing directory (0:root) */
	DWORD ofs;		/* Object ID 3, offset in the directory */
	WORD ctr;		/* Object open counter, 0:none, 0x01..0xFF:read mode open count, 0x100:write mode */
} FILESEM;
#endif


/* SBCS up-case tables (\x80-\xFF) */
#define TBL_CT437  {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
					0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT720  {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT737  {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0x90,0x92,0x92,0x93,0x94,0x95,0x96,0x97,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, \
					0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0xAA,0x92,0x93,0x94,0x95,0x96, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0x97,0xEA,0xEB,0xEC,0xE4,0xED,0xEE,0xEF,0xF5,0xF0,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT771  {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDC,0xDE,0xDE, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0xF0,0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF8,0xFA,0xFA,0xFC,0xFC,0xFE,0xFF}
#define TBL_CT775  {0x80,0x9A,0x91,0xA0,0x8E,0x95,0x8F,0x80,0xAD,0xED,0x8A,0x8A,0xA1,0x8D,0x8E,0x8F, \
					0x90,0x92,0x92,0xE2,0x99,0x95,0x96,0x97,0x97,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9F, \
					0xA0,0xA1,0xE0,0xA3,0xA3,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xB5,0xB6,0xB7,0xB8,0xBD,0xBE,0xC6,0xC7,0xA5,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE5,0xE5,0xE6,0xE3,0xE8,0xE8,0xEA,0xEA,0xEE,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT850  {0x43,0x55,0x45,0x41,0x41,0x41,0x41,0x43,0x45,0x45,0x45,0x49,0x49,0x49,0x41,0x41, \
					0x45,0x92,0x92,0x4F,0x4F,0x4F,0x55,0x55,0x59,0x4F,0x55,0x4F,0x9C,0x4F,0x9E,0x9F, \
					0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0x41,0x41,0x41,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0x41,0x41,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD1,0xD1,0x45,0x45,0x45,0x49,0x49,0x49,0x49,0xD9,0xDA,0xDB,0xDC,0xDD,0x49,0xDF, \
					0x4F,0xE1,0x4F,0x4F,0x4F,0x4F,0xE6,0xE8,0xE8,0x55,0x55,0x55,0x59,0x59,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT852  {0x80,0x9A,0x90,0xB6,0x8E,0xDE,0x8F,0x80,0x9D,0xD3,0x8A,0x8A,0xD7,0x8D,0x8E,0x8F, \
					0x90,0x91,0x91,0xE2,0x99,0x95,0x95,0x97,0x97,0x99,0x9A,0x9B,0x9B,0x9D,0x9E,0xAC, \
					0xB5,0xD6,0xE0,0xE9,0xA4,0xA4,0xA6,0xA6,0xA8,0xA8,0xAA,0x8D,0xAC,0xB8,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBD,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC6,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD1,0xD1,0xD2,0xD3,0xD2,0xD5,0xD6,0xD7,0xB7,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE3,0xD5,0xE6,0xE6,0xE8,0xE9,0xE8,0xEB,0xED,0xED,0xDD,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xEB,0xFC,0xFC,0xFE,0xFF}
#define TBL_CT855  {0x81,0x81,0x83,0x83,0x85,0x85,0x87,0x87,0x89,0x89,0x8B,0x8B,0x8D,0x8D,0x8F,0x8F, \
					0x91,0x91,0x93,0x93,0x95,0x95,0x97,0x97,0x99,0x99,0x9B,0x9B,0x9D,0x9D,0x9F,0x9F, \
					0xA1,0xA1,0xA3,0xA3,0xA5,0xA5,0xA7,0xA7,0xA9,0xA9,0xAB,0xAB,0xAD,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB6,0xB6,0xB8,0xB8,0xB9,0xBA,0xBB,0xBC,0xBE,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC7,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD1,0xD1,0xD3,0xD3,0xD5,0xD5,0xD7,0xD7,0xDD,0xD9,0xDA,0xDB,0xDC,0xDD,0xE0,0xDF, \
					0xE0,0xE2,0xE2,0xE4,0xE4,0xE6,0xE6,0xE8,0xE8,0xEA,0xEA,0xEC,0xEC,0xEE,0xEE,0xEF, \
					0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF8,0xFA,0xFA,0xFC,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT857  {0x80,0x9A,0x90,0xB6,0x8E,0xB7,0x8F,0x80,0xD2,0xD3,0xD4,0xD8,0xD7,0x49,0x8E,0x8F, \
					0x90,0x92,0x92,0xE2,0x99,0xE3,0xEA,0xEB,0x98,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9E, \
					0xB5,0xD6,0xE0,0xE9,0xA5,0xA5,0xA6,0xA6,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC7,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0x49,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE5,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xDE,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT860  {0x80,0x9A,0x90,0x8F,0x8E,0x91,0x86,0x80,0x89,0x89,0x92,0x8B,0x8C,0x98,0x8E,0x8F, \
					0x90,0x91,0x92,0x8C,0x99,0xA9,0x96,0x9D,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x86,0x8B,0x9F,0x96,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT861  {0x80,0x9A,0x90,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x8B,0x8B,0x8D,0x8E,0x8F, \
					0x90,0x92,0x92,0x4F,0x99,0x8D,0x55,0x97,0x97,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9F, \
					0xA4,0xA5,0xA6,0xA7,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT862  {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT863  {0x43,0x55,0x45,0x41,0x41,0x41,0x86,0x43,0x45,0x45,0x45,0x49,0x49,0x8D,0x41,0x8F, \
					0x45,0x45,0x45,0x4F,0x45,0x49,0x55,0x55,0x98,0x4F,0x55,0x9B,0x9C,0x55,0x55,0x9F, \
					0xA0,0xA1,0x4F,0x55,0xA4,0xA5,0xA6,0xA7,0x49,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT864  {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
					0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT865  {0x80,0x9A,0x90,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
					0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
					0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT866  {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
					0xF0,0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}
#define TBL_CT869  {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
					0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x86,0x9C,0x8D,0x8F,0x90, \
					0x91,0x90,0x92,0x95,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
					0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
					0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
					0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xA4,0xA5,0xA6,0xD9,0xDA,0xDB,0xDC,0xA7,0xA8,0xDF, \
					0xA9,0xAA,0xAC,0xAD,0xB5,0xB6,0xB7,0xB8,0xBD,0xBE,0xC6,0xC7,0xCF,0xCF,0xD0,0xEF, \
					0xF0,0xF1,0xD1,0xD2,0xD3,0xF5,0xD4,0xF7,0xF8,0xF9,0xD5,0x96,0x95,0x98,0xFE,0xFF}


/* DBCS code range |----- 1st byte -----|  |----------- 2nd byte -----------| */
#define TBL_DC932 {0x81, 0x9F, 0xE0, 0xFC, 0x40, 0x7E, 0x80, 0xFC, 0x00, 0x00}
#define TBL_DC936 {0x81, 0xFE, 0x00, 0x00, 0x40, 0x7E, 0x80, 0xFE, 0x00, 0x00}
#define TBL_DC949 {0x81, 0xFE, 0x00, 0x00, 0x41, 0x5A, 0x61, 0x7A, 0x81, 0xFE}
#define TBL_DC950 {0x81, 0xFE, 0x00, 0x00, 0x40, 0x7E, 0xA1, 0xFE, 0x00, 0x00}


/* Macros for table definitions */
#define MERGE_2STR(a, b) a ## b
#define MKCVTBL(hd, cp) MERGE_2STR(hd, cp)




/*--------------------------------------------------------------------------

   Module Private Work Area

---------------------------------------------------------------------------*/
/* Remark: Variables defined here without initial value shall be guaranteed
/  zero/null at start-up. If not, the linker option or start-up routine is
/  not compliance with C standard. */

/*--------------------------------*/
/* File/Volume controls           */
/*--------------------------------*/

#if FF_VOLUMES < 1
#error Wrong FF_VOLUMES setting
#endif
FATFS* FatFs[FF_VOLUMES];			/* Pointer to the filesystem objects (logical drives) */
static WORD Fsid;					/* Filesystem mount ID */
static UINT	time_status = SYSTEM_TIME_ENABLE;	/*system time status */

#if FF_FS_RPATH != 0 && FF_VOLUMES >= 2
static BYTE CurrVol;				/* Current drive */
#endif

#if FF_FS_LOCK != 0
static FILESEM Files[FF_FS_LOCK];	/* Open object lock semaphores */
#endif

#if FF_STR_VOLUME_ID
#ifdef FF_VOLUME_STRS
static const char* const VolumeStr[FF_VOLUMES] = {FF_VOLUME_STRS};	/* Pre-defined volume ID */
#endif
#endif


/*--------------------------------*/
/* LFN/Directory working buffer   */
/*--------------------------------*/

#if FF_USE_LFN == 0		/* Non-LFN configuration */
#define DEF_NAMBUF
#define INIT_NAMBUF(fs)
#define FREE_NAMBUF()
#define LEAVE_MKFS(res)	return res

#else					/* LFN configurations */
#if FF_MAX_LFN < 12 || FF_MAX_LFN > 255
#error Wrong setting of FF_MAX_LFN
#endif
#if FF_LFN_BUF < FF_SFN_BUF || FF_SFN_BUF < 12
#error Wrong setting of FF_LFN_BUF or FF_SFN_BUF
#endif
#if FF_LFN_UNICODE < 0 || FF_LFN_UNICODE > 3
#error Wrong setting of FF_LFN_UNICODE
#endif
static const BYTE LfnOfs[] = {1,3,5,7,9,14,16,18,20,22,24,28,30};	/* FAT: Offset of LFN characters in the directory entry */

#if FF_USE_LFN == 1		/* LFN enabled with static working buffer */
static WCHAR LfnBuf[FF_MAX_LFN + 1];		/* LFN working buffer */
#define DEF_NAMBUF
#define INIT_NAMBUF(fs)
#define FREE_NAMBUF()
#define LEAVE_MKFS(res)	return res

#elif FF_USE_LFN == 2 	/* LFN enabled with dynamic working buffer on the stack */
#define DEF_NAMBUF		WCHAR lbuf[FF_MAX_LFN+1];	/* LFN working buffer */
#define INIT_NAMBUF(fs)	{ (fs)->lfnbuf = lbuf; }
#define FREE_NAMBUF()
#define LEAVE_MKFS(res)	return res

#elif FF_USE_LFN == 3 	/* LFN enabled with dynamic working buffer on the heap */
#define DEF_NAMBUF		WCHAR *lfn;	/* Pointer to LFN working buffer and directory entry block scratchpad buffer */
#define INIT_NAMBUF(fs)	{ lfn = ff_memalloc((FF_MAX_LFN+1)*2); if (!lfn) LEAVE_FF(fs, FR_NOT_ENOUGH_CORE); (fs)->lfnbuf = lfn; }
#define FREE_NAMBUF()	ff_memfree(lfn)
#define LEAVE_MKFS(res)	{ if (!work) ff_memfree(buf); return res; }
#define MAX_MALLOC	0x8000	/* Must be >=FF_MAX_SS */

#else
#error Wrong setting of FF_USE_LFN

#endif	/* FF_USE_LFN == 1 */
#endif	/* FF_USE_LFN == 0 */



/*--------------------------------*/
/* Code conversion tables         */
/*--------------------------------*/

#if FF_CODE_PAGE == 0		/* Run-time code page configuration */
#define CODEPAGE CodePage
static WORD CodePage;	/* Current code page */
static const BYTE *ExCvt, *DbcTbl;	/* Pointer to current SBCS up-case table and DBCS code range table below */

static const BYTE Ct437[] = TBL_CT437;
static const BYTE Ct720[] = TBL_CT720;
static const BYTE Ct737[] = TBL_CT737;
static const BYTE Ct771[] = TBL_CT771;
static const BYTE Ct775[] = TBL_CT775;
static const BYTE Ct850[] = TBL_CT850;
static const BYTE Ct852[] = TBL_CT852;
static const BYTE Ct855[] = TBL_CT855;
static const BYTE Ct857[] = TBL_CT857;
static const BYTE Ct860[] = TBL_CT860;
static const BYTE Ct861[] = TBL_CT861;
static const BYTE Ct862[] = TBL_CT862;
static const BYTE Ct863[] = TBL_CT863;
static const BYTE Ct864[] = TBL_CT864;
static const BYTE Ct865[] = TBL_CT865;
static const BYTE Ct866[] = TBL_CT866;
static const BYTE Ct869[] = TBL_CT869;
static const BYTE Dc932[] = TBL_DC932;
static const BYTE Dc936[] = TBL_DC936;
static const BYTE Dc949[] = TBL_DC949;
static const BYTE Dc950[] = TBL_DC950;

#elif FF_CODE_PAGE < 900	/* Static code page configuration (SBCS) */
#define CODEPAGE FF_CODE_PAGE
static const BYTE ExCvt[] = MKCVTBL(TBL_CT, FF_CODE_PAGE);

#else					/* Static code page configuration (DBCS) */
#define CODEPAGE FF_CODE_PAGE
static const BYTE DbcTbl[] = MKCVTBL(TBL_DC, FF_CODE_PAGE);

#endif




/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Load/Store multi-byte word in the FAT structure                       */
/*-----------------------------------------------------------------------*/

WORD ld_word (const BYTE* ptr)	/*	 Load a 2-byte little-endian word */
{
	WORD rv;

	rv = ptr[1];
	rv = rv << 8 | ptr[0];
	return rv;
}

DWORD ld_dword (const BYTE* ptr)	/* Load a 4-byte little-endian word */
{
	DWORD rv;

	rv = ptr[3];
	rv = rv << 8 | ptr[2];
	rv = rv << 8 | ptr[1];
	rv = rv << 8 | ptr[0];
	return rv;
}

#if !FF_FS_READONLY
void st_word (BYTE* ptr, WORD val)	/* Store a 2-byte word in little-endian */
{
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val;
}

void st_dword (BYTE* ptr, DWORD val)	/* Store a 4-byte word in little-endian */
{
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val; val >>= 8;
	*ptr++ = (BYTE)val;
}
#endif /* !FF_FS_READONLY */



/*-----------------------------------------------------------------------*/
/* String functions                                                      */
/*-----------------------------------------------------------------------*/

/* Copy memory to memory */
static void mem_cpy (void* dst, const void* src, UINT cnt)
{
	BYTE *d = (BYTE*)dst;
	const BYTE *s = (const BYTE*)src;

	if (cnt != 0) {
		do {
			*d++ = *s++;
		} while (--cnt);
	}
}


/* Fill memory block */
static void mem_set (void* dst, int val, UINT cnt)
{
	BYTE *d = (BYTE*)dst;

	do {
		*d++ = (BYTE)val;
	} while (--cnt);
}


/* Compare memory block */
static int mem_cmp (const void* dst, const void* src, UINT cnt)	/* ZR:same, NZ:different */
{
	const BYTE *d = (const BYTE *)dst, *s = (const BYTE *)src;
	int r = 0;

	do {
		r = *d++ - *s++;
	} while (--cnt && r == 0);

	return r;
}


/* Check if chr is contained in the string */
static int chk_chr (const char* str, int chr)	/* NZ:contained, ZR:not contained */
{
	while (*str && *str != chr) str++;
	return *str;
}


/* Test if the character is DBC 1st byte */
static int dbc_1st (BYTE c)
{
#if FF_CODE_PAGE == 0		/* Variable code page */
	if (DbcTbl && c >= DbcTbl[0]) {
		if (c <= DbcTbl[1]) return 1;					/* 1st byte range 1 */
		if (c >= DbcTbl[2] && c <= DbcTbl[3]) return 1;	/* 1st byte range 2 */
	}
#elif FF_CODE_PAGE >= 900	/* DBCS fixed code page */
	if (c >= DbcTbl[0]) {
		if (c <= DbcTbl[1]) return 1;
		if (c >= DbcTbl[2] && c <= DbcTbl[3]) return 1;
	}
#else						/* SBCS fixed code page */
	if (c != 0) return 0;	/* Always false */
#endif
	return 0;
}


/* Test if the character is DBC 2nd byte */
static int dbc_2nd (BYTE c)
{
#if FF_CODE_PAGE == 0		/* Variable code page */
	if (DbcTbl && c >= DbcTbl[4]) {
		if (c <= DbcTbl[5]) return 1;					/* 2nd byte range 1 */
		if (c >= DbcTbl[6] && c <= DbcTbl[7]) return 1;	/* 2nd byte range 2 */
		if (c >= DbcTbl[8] && c <= DbcTbl[9]) return 1;	/* 2nd byte range 3 */
	}
#elif FF_CODE_PAGE >= 900	/* DBCS fixed code page */
	if (c >= DbcTbl[4]) {
		if (c <= DbcTbl[5]) return 1;
		if (c >= DbcTbl[6] && c <= DbcTbl[7]) return 1;
		if (c >= DbcTbl[8] && c <= DbcTbl[9]) return 1;
	}
#else						/* SBCS fixed code page */
	if (c != 0) return 0;	/* Always false */
#endif
	return 0;
}


#if FF_USE_LFN

/* Get a character from TCHAR string in defined API encodeing */
static DWORD tchar2uni (	/* Returns character in UTF-16 encoding (>=0x10000 on double encoding unit, 0xFFFFFFFF on decode error) */
	const TCHAR** str		/* Pointer to pointer to TCHAR string in configured encoding */
)
{
	DWORD uc;
	const TCHAR *p = *str;

#if FF_LFN_UNICODE == 1		/* UTF-16 input */
	WCHAR wc;

	uc = *p++;	/* Get a unit */
	if (IsSurrogate(uc)) {	/* Surrogate? */
		wc = *p++;		/* Get low surrogate */
		if (!IsSurrogateH(uc) || !IsSurrogateL(wc)) return 0xFFFFFFFF;	/* Wrong surrogate? */
		uc = uc << 16 | wc;
	}

#elif FF_LFN_UNICODE == 2	/* UTF-8 input */
	BYTE b;
	int nf;

	uc = (BYTE)*p++;	/* Get a unit */
	if (uc & 0x80) {	/* Multiple byte code? */
		if ((uc & 0xE0) == 0xC0) {	/* 2-byte sequence? */
			uc &= 0x1F; nf = 1;
		} else {
			if ((uc & 0xF0) == 0xE0) {	/* 3-byte sequence? */
				uc &= 0x0F; nf = 2;
			} else {
				if ((uc & 0xF8) == 0xF0) {	/* 4-byte sequence? */
					uc &= 0x07; nf = 3;
				} else {					/* Wrong sequence */
					return 0xFFFFFFFF;
				}
			}
		}
		do {	/* Get trailing bytes */
			b = (BYTE)*p++;
			if ((b & 0xC0) != 0x80) return 0xFFFFFFFF;	/* Wrong sequence? */
			uc = uc << 6 | (b & 0x3F);
		} while (--nf != 0);
		if (uc < 0x80 || IsSurrogate(uc) || uc >= 0x110000) return 0xFFFFFFFF;	/* Wrong code? */
		if (uc >= 0x010000) uc = 0xD800DC00 | ((uc - 0x10000) << 6 & 0x3FF0000) | (uc & 0x3FF);	/* Make a surrogate pair if needed */
	}

#elif FF_LFN_UNICODE == 3	/* UTF-32 input */
	uc = (TCHAR)*p++;	/* Get a unit */
	if (uc >= 0x110000) return 0xFFFFFFFF;	/* Wrong code? */
	if (uc >= 0x010000) uc = 0xD800DC00 | ((uc - 0x10000) << 6 & 0x3FF0000) | (uc & 0x3FF);	/* Make a surrogate pair if needed */

#else		/* ANSI/OEM input */
	BYTE b;
	WCHAR wc;

	wc = (BYTE)*p++;			/* Get a byte */
	if (dbc_1st((BYTE)wc)) {	/* Is it a DBC 1st byte? */
		b = (BYTE)*p++;			/* Get 2nd byte */
		if (!dbc_2nd(b)) return 0xFFFFFFFF;	/* Invalid code? */
		wc = (wc << 8) + b;		/* Make a DBC */
	}
	if (wc != 0) {
		wc = ff_oem2uni(wc, CODEPAGE);	/* ANSI/OEM ==> Unicode */
		if (wc == 0) return 0xFFFFFFFF;	/* Invalid code? */
	}
	uc = wc;

#endif
	*str = p;	/* Next read pointer */
	return uc;
}


/* Output a TCHAR string in defined API encoding */
static BYTE put_utf (	/* Returns number of encoding units written (0:buffer overflow or wrong encoding) */
	DWORD chr,	/* UTF-16 encoded character (Double encoding unit char if >=0x10000) */
	TCHAR* buf,	/* Output buffer */
	UINT szb	/* Size of the buffer */
)
{
#if FF_LFN_UNICODE == 1	/* UTF-16 output */
	WCHAR hs, wc;

	hs = (WCHAR)(chr >> 16);
	wc = (WCHAR)chr;
	if (hs == 0) {	/* Single encoding unit? */
		if (szb < 1 || IsSurrogate(wc)) return 0;	/* Buffer overflow or wrong code? */
		*buf = wc;
		return 1;
	}
	if (szb < 2 || !IsSurrogateH(hs) || !IsSurrogateL(wc)) return 0;	/* Buffer overflow or wrong surrogate? */
	*buf++ = hs;
	*buf++ = wc;
	return 2;

#elif FF_LFN_UNICODE == 2	/* UTF-8 output */
	DWORD hc;

	if (chr < 0x80) {	/* Single byte code? */
		if (szb < 1) return 0;	/* Buffer overflow? */
		*buf = (TCHAR)chr;
		return 1;
	}
	if (chr < 0x800) {	/* 2-byte sequence? */
		if (szb < 2) return 0;	/* Buffer overflow? */
		*buf++ = (TCHAR)(0xC0 | (chr >> 6 & 0x1F));
		*buf++ = (TCHAR)(0x80 | (chr >> 0 & 0x3F));
		return 2;
	}
	if (chr < 0x10000) {	/* 3-byte sequence? */
		if (szb < 3 || IsSurrogate(chr)) return 0;	/* Buffer overflow or wrong code? */
		*buf++ = (TCHAR)(0xE0 | (chr >> 12 & 0x0F));
		*buf++ = (TCHAR)(0x80 | (chr >> 6 & 0x3F));
		*buf++ = (TCHAR)(0x80 | (chr >> 0 & 0x3F));
		return 3;
	}
	/* 4-byte sequence */
	if (szb < 4) return 0;	/* Buffer overflow? */
	hc = ((chr & 0xFFFF0000) - 0xD8000000) >> 6;	/* Get high 10 bits */
	chr = (chr & 0xFFFF) - 0xDC00;					/* Get low 10 bits */
	if (hc >= 0x100000 || chr >= 0x400) return 0;	/* Wrong surrogate? */
	chr = (hc | chr) + 0x10000;
	*buf++ = (TCHAR)(0xF0 | (chr >> 18 & 0x07));
	*buf++ = (TCHAR)(0x80 | (chr >> 12 & 0x3F));
	*buf++ = (TCHAR)(0x80 | (chr >> 6 & 0x3F));
	*buf++ = (TCHAR)(0x80 | (chr >> 0 & 0x3F));
	return 4;

#elif FF_LFN_UNICODE == 3	/* UTF-32 output */
	DWORD hc;

	if (szb < 1) return 0;	/* Buffer overflow? */
	if (chr >= 0x10000) {	/* Out of BMP? */
		hc = ((chr & 0xFFFF0000) - 0xD8000000) >> 6;	/* Get high 10 bits */
		chr = (chr & 0xFFFF) - 0xDC00;					/* Get low 10 bits */
		if (hc >= 0x100000 || chr >= 0x400) return 0;	/* Wrong surrogate? */
		chr = (hc | chr) + 0x10000;
	}
	*buf++ = (TCHAR)chr;
	return 1;

#else						/* ANSI/OEM output */
	WCHAR wc;

	wc = ff_uni2oem(chr, CODEPAGE);
	if (wc >= 0x100) {	/* Is this a DBC? */
		if (szb < 2) return 0;
		*buf++ = (char)(wc >> 8);	/* Store DBC 1st byte */
		*buf++ = (TCHAR)wc;			/* Store DBC 2nd byte */
		return 2;
	}
	if (wc == 0 || szb < 1) return 0;	/* Invalid char or buffer overflow? */
	*buf++ = (TCHAR)wc;					/* Store the character */
	return 1;
#endif
}
#endif	/* FF_USE_LFN */


#if FF_FS_REENTRANT
/*-----------------------------------------------------------------------*/
/* Request/Release grant to access the volume                            */
/*-----------------------------------------------------------------------*/
int lock_fs (		/* 1:Ok, 0:timeout */
	FATFS* fs		/* Filesystem object */
)
{
	return (fs && ff_req_grant(&fs->sobj)) ? 1 : 0;
}


void unlock_fs (
	FATFS* fs,		/* Filesystem object */
	FRESULT res		/* Result code to be returned */
)
{
	if (fs && res != FR_NOT_ENABLED && res != FR_INVALID_DRIVE && res != FR_TIMEOUT) {
		ff_rel_grant(&fs->sobj);
	}
}

#endif



#if FF_FS_LOCK != 0
/*-----------------------------------------------------------------------*/
/* File lock control functions                                           */
/*-----------------------------------------------------------------------*/

static FRESULT chk_lock (	/* Check if the file can be accessed */
	DIR* dp,				/* Directory object pointing the file to be checked */
	int acc					/* Desired access type (0:Read mode open, 1:Write mode open, 2:Delete or rename) */
)
{
	UINT i, be;

	/* Search open object table for the object */
	be = 0;
	for (i = 0; i < FF_FS_LOCK; i++) {
		if (Files[i].fs) {	/* Existing entry */
			if (Files[i].fs == dp->obj.fs &&	 	/* Check if the object matches with an open object */
				Files[i].clu == dp->obj.sclust &&
				Files[i].ofs == dp->dptr) break;
		} else {			/* Blank entry */
			be = 1;
		}
	}
	if (i == FF_FS_LOCK) {	/* The object has not been opened */
		return (!be && acc != 2) ? FR_TOO_MANY_OPEN_FILES : FR_OK;	/* Is there a blank entry for new object? */
	}

	/* The object was opened. Reject any open against writing file and all write mode open */
	return (acc != 0 || Files[i].ctr == 0x100) ? FR_LOCKED : FR_OK;
}


static int enq_lock (void)	/* Check if an entry is available for a new object */
{
	UINT i;

	for (i = 0; i < FF_FS_LOCK && Files[i].fs; i++) ;
	return (i == FF_FS_LOCK) ? 0 : 1;
}


static UINT inc_lock (	/* Increment object open counter and returns its index (0:Internal error) */
	DIR* dp,	/* Directory object pointing the file to register or increment */
	int acc		/* Desired access (0:Read, 1:Write, 2:Delete/Rename) */
)
{
	UINT i;


	for (i = 0; i < FF_FS_LOCK; i++) {	/* Find the object */
		if (Files[i].fs == dp->obj.fs &&
			Files[i].clu == dp->obj.sclust &&
			Files[i].ofs == dp->dptr) break;
	}

	if (i == FF_FS_LOCK) {				/* Not opened. Register it as new. */
		for (i = 0; i < FF_FS_LOCK && Files[i].fs; i++) ;
		if (i == FF_FS_LOCK) return 0;	/* No free entry to register (int err) */
		Files[i].fs = dp->obj.fs;
		Files[i].clu = dp->obj.sclust;
		Files[i].ofs = dp->dptr;
		Files[i].ctr = 0;
	}

	if (acc >= 1 && Files[i].ctr) return 0;	/* Access violation (int err) */

	Files[i].ctr = Files[i].ctr + 1;		/* Set semaphore value */

	return i + 1;	/* Index number origin from 1 */
}


static FRESULT dec_lock (	/* Decrement object open counter */
	UINT i			/* Semaphore index (1..) */
)
{
	WORD n;
	FRESULT res;


	if (--i < FF_FS_LOCK) {	/* Index number origin from 0 */
		n = Files[i].ctr;
		if (n == 0x100) n = 0;		/* If write mode open, delete the entry */
		if (n > 0) n--;				/* Decrement read mode open count */
		Files[i].ctr = n;
		if (n == 0) Files[i].fs = 0;	/* Delete the entry if open count gets zero */
		res = FR_OK;
	} else {
		res = FR_INT_ERR;			/* Invalid index nunber */
	}
	return res;
}


static void clear_lock (	/* Clear lock entries of the volume */
	FATFS *fs
)
{
	UINT i;

	for (i = 0; i < FF_FS_LOCK; i++) {
		if (Files[i].fs == fs) Files[i].fs = 0;
	}
}

static
FRESULT empty_lock(FATFS* fs)		/* check lock entries is empty or not. */
{
	UINT i;

	for (i = 0; i < FF_FS_LOCK; i++) {
		if (Files[i].fs == fs) return FR_LOCKED;
	}

	return FR_OK;
}
#endif	/* FF_FS_LOCK != 0 */

FRESULT f_checkopenlock(int index)		/* check lock entries is empty or not by index. */
{
#if FF_FS_LOCK != 0
	if (FatFs[index])
		return empty_lock(FatFs[index]);
#endif
	return FR_OK;
}

/*-----------------------------------------------------------------------*/
/* Move/Flush disk access window in the filesystem object                */
/*-----------------------------------------------------------------------*/
#if !FF_FS_READONLY
static FRESULT sync_window (	/* Returns FR_OK or FR_DISK_ERR */
	FATFS* fs			/* Filesystem object */
)
{
	FRESULT res = FR_OK;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	/* Forced the fs point to its parents */
	if (ISCHILD(fs)) fs = PARENTFS(fs);
#endif

	if (fs->wflag) {	/* Is the disk access window dirty */
		if (disk_write(fs->pdrv, fs->win, fs->winsect, 1) == RES_OK) {	/* Write back the window */
			fs->wflag = 0;	/* Clear window dirty flag */
			if (fs->winsect - fs->fatbase < fs->fsize) {	/* Is it in the 1st FAT? */
				if (fs->n_fats == 2) disk_write(fs->pdrv, fs->win, fs->winsect + fs->fsize, 1);	/* Reflect it to 2nd FAT if needed */
			}
		} else {
			res = FR_DISK_ERR;
		}
	}
	return res;
}
#endif


static FRESULT move_window (	/* Returns FR_OK or FR_DISK_ERR */
	FATFS* fs,		    /* File system object */
	QWORD	sector		/* Sector number to make appearance in the fs->win[] */
)
{
	FRESULT res = FR_OK;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	/* Forced the fs point to its parents */
	if (ISCHILD(fs)) fs = PARENTFS(fs);
#endif

	if (sector != fs->winsect) {	/* Window offset changed? */
#if !FF_FS_READONLY
		res = sync_window(fs);		/* Write-back changes */
#endif
		if (res == FR_OK) {			/* Fill sector window with new data */
			if (disk_read(fs->pdrv, fs->win, sector, 1) != RES_OK) {
				sector = 0xFFFFFFFF;	/* Invalidate window if read data is not valid */
				res = FR_DISK_ERR;
			}
			fs->winsect = sector;
		}
	}
	return res;
}




#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Synchronize filesystem and data on the storage                        */
/*-----------------------------------------------------------------------*/

static FRESULT sync_fs (	/* Returns FR_OK or FR_DISK_ERR */
	FATFS* fs		/* Filesystem object */
)
{
	FRESULT res;


	res = sync_window(fs);
	if (res == FR_OK) {
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		/* Forced the fs point to its parents */
		if (ISCHILD(fs)) fs = PARENTFS(fs);
#endif
		if (fs->fs_type == FS_FAT32 && fs->fsi_flag == 1) {	/* FAT32: Update FSInfo sector if needed */
			/* Create FSInfo structure */
			mem_set(fs->win, 0, SS(fs));
			st_word(fs->win + BS_55AA, 0xAA55);
			st_dword(fs->win + FSI_LeadSig, 0x41615252);
			st_dword(fs->win + FSI_StrucSig, 0x61417272);
			st_dword(fs->win + FSI_Free_Count, fs->free_clst);
			st_dword(fs->win + FSI_Nxt_Free, fs->last_clst);
			/* Write it into the FSInfo sector */
			fs->winsect = fs->volbase + 1;
			disk_write(fs->pdrv, fs->win, fs->winsect, 1);
			fs->fsi_flag = 0;
		}
		/* Make sure that no pending write process in the lower layer */
		if (disk_ioctl(fs->pdrv, CTRL_SYNC, 0) != RES_OK) res = FR_DISK_ERR;
	}

	return res;
}

#endif



/*-----------------------------------------------------------------------*/
/* Get physical sector number from cluster number                        */
/*-----------------------------------------------------------------------*/

static QWORD clst2sect (	/* !=0:Sector number, 0:Failed (invalid cluster#) */
	FATFS* fs,		/* Filesystem object */
	DWORD clst		/* Cluster# to be converted */
)
{
	clst -= 2;		/* Cluster number is origin from 2 */
	if (clst >= fs->n_fatent - 2) return 0;		/* Is it invalid cluster number? */
	return (QWORD)clst * fs->csize + fs->database;		/* Start sector number of the cluster */
}




/*-----------------------------------------------------------------------*/
/* FAT access - Read value of a FAT entry                                */
/*-----------------------------------------------------------------------*/

DWORD get_fat (		/* 0xFFFFFFFF:Disk error, 1:Internal error, 2..0x7FFFFFFF:Cluster status */
	FFOBJID* obj,	/* Corresponding object */
	DWORD clst		/* Cluster number to get the value */
)
{
	UINT wc, bc;
	DWORD val;
	FATFS *fs = obj->fs;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	/* Forced the fs point to its parents */
	if (ISCHILD(fs)) fs = PARENTFS(fs);
#endif

	if (clst < 2 || clst >= fs->n_fatent) {	/* Check if in valid range */
		val = 1;	/* Internal error */
	} else {
		val = 0xFFFFFFFF;	/* Default value falls on disk error */

		switch (fs->fs_type) {
		case FS_FAT12 :
			bc = (UINT)clst; bc += bc / 2;
			if (move_window(fs, fs->fatbase + (bc / SS(fs))) != FR_OK) break;
			wc = fs->win[bc++ % SS(fs)];		/* Get 1st byte of the entry */
			if (move_window(fs, fs->fatbase + (bc / SS(fs))) != FR_OK) break;
			wc |= fs->win[bc % SS(fs)] << 8;	/* Merge 2nd byte of the entry */
			val = (clst & 1) ? (wc >> 4) : (wc & 0xFFF);	/* Adjust bit position */
			break;

		case FS_FAT16 :
			if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 2))) != FR_OK) break;
			val = ld_word(fs->win + clst * 2 % SS(fs));		/* Simple WORD array */
			break;

		case FS_FAT32 :
			if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 4))) != FR_OK) break;
			val = ld_dword(fs->win + clst * 4 % SS(fs)) & 0x0FFFFFFF;
			break;

		default:
			val = 1;	/* Internal error */
		}
	}

	return val;
}




#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* FAT access - Change value of a FAT entry                              */
/*-----------------------------------------------------------------------*/

static FRESULT put_fat (	/* FR_OK(0):succeeded, !=0:error */
	FATFS* fs,				/* Corresponding filesystem object */
	DWORD clst,				/* FAT index number (cluster number) to be changed */
	DWORD val				/* New value to be set to the entry */
)
{
	UINT bc;
	BYTE *p;
	FRESULT res = FR_INT_ERR;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	/* Forced the fs point to its parents */
	if (ISCHILD(fs)) fs = PARENTFS(fs);
#endif

	if (clst >= 2 && clst < fs->n_fatent) {	/* Check if in valid range */
		switch (fs->fs_type) {
		case FS_FAT12 :
			bc = (UINT)clst; bc += bc / 2;	/* bc: byte offset of the entry */
			res = move_window(fs, fs->fatbase + (bc / SS(fs)));
			if (res != FR_OK) break;
			p = fs->win + bc++ % SS(fs);
			*p = (clst & 1) ? ((*p & 0x0F) | ((BYTE)val << 4)) : (BYTE)val;		/* Put 1st byte */
			fs->wflag = 1;
			res = move_window(fs, fs->fatbase + (bc / SS(fs)));
			if (res != FR_OK) break;
			p = fs->win + bc % SS(fs);
			*p = (clst & 1) ? (BYTE)(val >> 4) : ((*p & 0xF0) | ((BYTE)(val >> 8) & 0x0F));	/* Put 2nd byte */
			fs->wflag = 1;
			break;

		case FS_FAT16 :
			res = move_window(fs, fs->fatbase + (clst / (SS(fs) / 2)));
			if (res != FR_OK) break;
			st_word(fs->win + clst * 2 % SS(fs), (WORD)val);	/* Simple WORD array */
			fs->wflag = 1;
			break;

		case FS_FAT32 :
			res = move_window(fs, fs->fatbase + (clst / (SS(fs) / 4)));
			if (res != FR_OK) break;
			val = (val & 0x0FFFFFFF) | (ld_dword(fs->win + clst * 4 % SS(fs)) & 0xF0000000);
			st_dword(fs->win + clst * 4 % SS(fs), val);
			fs->wflag = 1;
			break;
		}
	}
	return res;
}

#endif /* !FF_FS_READONLY */


#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* FAT handling - Remove a cluster chain                                 */
/*-----------------------------------------------------------------------*/

static FRESULT remove_chain (	/* FR_OK(0):succeeded, !=0:error */
	FFOBJID* obj,		/* Corresponding object */
	DWORD clst,			/* Cluster to remove a chain from */
	DWORD pclst			/* Previous cluster of clst (0 if entire chain) */
)
{
	FRESULT res = FR_OK;
	DWORD nxt;
	FATFS *fs = obj->fs;
#if FF_USE_TRIM
	DWORD scl = clst, ecl = clst;
	DWORD rt[2];
#endif

	if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;	/* Check if in valid range */

	/* Mark the previous cluster 'EOC' on the FAT if it exists */
	if (pclst) {
		res = put_fat(fs, pclst, 0xFFFFFFFF);
		if (res != FR_OK) return res;
	}

	/* Remove the chain */
	do {
		nxt = get_fat(obj, clst);			/* Get cluster status */
		if (nxt == 0) break;				/* Empty cluster? */
		if (nxt == 1) return FR_INT_ERR;	/* Internal error? */
		if (nxt == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error? */
		res = put_fat(fs, clst, 0);		    /* Mark the cluster 'free' on the FAT */
		if (res != FR_OK) return res;

#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (fs->free_clst < fs->n_fatent - 2) {	/* Update FSINFO */
			fs->free_clst++;
			fs->fsi_flag |= 1;
		}
#else
		/* Update free_clst for both virtual FATFS and parent FATFS */
		if (fs->free_clst < fs->ct_clst && ISCHILD(fs) && ISVIRPART(fs))
			fs->free_clst++;
		/* Update FSINFO */
		if (PARENTFS(fs)->free_clst < PARENTFS(fs)->n_fatent - 2) {
			PARENTFS(fs)->free_clst++;
			PARENTFS(fs)->fsi_flag |= 1;
		}
#endif
#if FF_USE_TRIM
		if (ecl + 1 == nxt) {	/* Is next cluster contiguous? */
			ecl = nxt;
		} else {				/* End of contiguous cluster block */
			rt[0] = clst2sect(fs, scl);					/* Start of data area freed */
			rt[1] = clst2sect(fs, ecl) + fs->csize - 1;	/* End of data area freed */
			disk_ioctl(fs->pdrv, CTRL_TRIM, rt);		/* Inform device the data in the block is no longer needed */
			scl = ecl = nxt;
		}
#endif
		clst = nxt;					/* Next cluster */
	} while (clst < fs->n_fatent);	/* Repeat while not the last link */

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* FAT handling - Stretch a chain or Create a new chain                  */
/*-----------------------------------------------------------------------*/

static DWORD create_chain (	/* 0:No free cluster, 1:Internal error, 0xFFFFFFFF:Disk error, >=2:New cluster# */
	FFOBJID* obj,		/* Corresponding object */
	DWORD clst			/* Cluster# to stretch, 0:Create a new chain */
)
{
	DWORD cs, ncl, scl;
	FRESULT res;
	FATFS *fs = obj->fs;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	if (ISVIRPART(fs) && (fs->st_clst == 0xFFFFFFFF || fs->ct_clst == 0xFFFFFFFF)) {
		return 0;
	}
#endif

	if (clst == 0) {	/* Create a new chain */
		scl = fs->last_clst;				/* Suggested cluster to start to find */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISVIRPART(fs)) {
			if (scl == 0 || scl >= fs->n_fatent)
				scl = fs->st_clst - 1 ;
			if (scl == 0 || scl < fs->st_clst || scl >= fs->st_clst + fs->ct_clst)
				scl = fs->st_clst - 1;
		} else
#endif
		{
			if (scl == 0 || scl >= fs->n_fatent) scl = 1;
		}
	} else {		/* Stretch a chain */
		cs = get_fat(obj, clst);            /* Check the cluster status */
		if (cs < 2) return 1;				/* Test for insanity */
		if (cs == 0xFFFFFFFF) return cs;	/* Test for disk error */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISVIRPART(fs)) {
			/* Chain has already follow inside the virtual parition limit boundary */
			if (cs < fs->st_clst + fs->ct_clst && cs >= fs->st_clst)
				return cs;			/* return the followed cluster */
			/* Chain has already follow outside the virutal partition limit boundary */
			if ((cs >= fs->st_clst + fs->ct_clst && cs < fs->n_fatent) || cs < fs->st_clst)
				return 1;			/* Denied the following cluster, abort ths operation */
		} else
#endif
		{
			if (cs < fs->n_fatent) return cs;	/* It is already followed by next cluster */
		}
		scl = clst;                             /* Cluster to start to find */
	}
	if (fs->free_clst == 0) return 0;		    /* No free cluster */

	/* On the FAT/FAT32 volume */
	ncl = 0;
	if (scl == clst) {						/* Stretching an existing chain? */
		ncl = scl + 1;						/* Test if next cluster is free */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISVIRPART(fs)) {
			/* Current cluster has reached the bottom boundary of the virtual partition */
			if (ncl >= fs->st_clst + fs->ct_clst || ncl < fs->st_clst)
				ncl = fs->st_clst;
		} else
#endif
		{
			if (ncl >= fs->n_fatent) ncl = 2;
		}
		cs = get_fat(obj, ncl);						/* Get next cluster status */
		if (cs == 1 || cs == 0xFFFFFFFF) return cs;	/* Test for error */
		if (cs != 0) {								/* Not free? */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			if (ISVIRPART(fs)) {
				cs = PARENTFS(fs)->last_clst;		/* Start at suggested cluster if it is valid */
				if (cs >= fs->st_clst && cs < fs->st_clst + fs->ct_clst) scl = cs;
			} else
#endif
			{
				cs = fs->last_clst;				/* Start at suggested cluster if it is valid */
				if (cs >= 2 && cs < fs->n_fatent) scl = cs;
			}
			ncl = 0;
		}
	}

	if (ncl == 0) { /* The new cluster cannot be contiguous and find another fragment */
		ncl = scl;	/* Start cluster */
		for (;;) {
			ncl++;				/* Next cluster */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			if (ISVIRPART(fs)) {
				/* Current cluster has reached the bottom boundary of the virtual partition */
				if (ncl >= fs->st_clst + fs->ct_clst || ncl < fs->st_clst) {
					ncl = fs->st_clst;
					if (ncl > scl) return 0;	/* No free cluster */
				}
			} else
#endif
			{
				if (ncl >= fs->n_fatent) {	/* Check wrap-around */
					ncl = 2;
					if (ncl > scl) return 0;	/* No free cluster */
				}
			}
			cs = get_fat(obj, ncl);				/* Get the cluster status */
			if (cs == 0) break;				    /* Found a free cluster? */
			if (cs == 1 || cs == 0xFFFFFFFF) return cs;	/* Test for error */
			if (ncl == scl) return 0;		    /* No free cluster found? */
		}
	}
	res = put_fat(fs, ncl, 0xFFFFFFFF);	/* Mark the new cluster 'EOC' */
	if (res == FR_OK && clst != 0) {
		res = put_fat(fs, clst, ncl);	/* Link it from the previous one if needed */
	}

	if (res == FR_OK) {         /* Update FSINFO if function succeeded. */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		/* Update Last Cluster info for both parent FATFS and child FATFS */
		if (ISVIRPART(fs)) {
			fs->last_clst = ncl;
			PARENTFS(fs)->last_clst = ncl;
			if (fs->free_clst <= fs->ct_clst && ISCHILD(fs))
				fs->free_clst--;
			if (PARENTFS(fs)->free_clst <= PARENTFS(fs)->n_fatent - 2)
				(PARENTFS(fs))->free_clst--;
			PARENTFS(fs)->fsi_flag |= 1;
		} else
#endif
		{
			fs->last_clst = ncl;
			if (fs->free_clst <= fs->n_fatent - 2) fs->free_clst--;
			fs->fsi_flag |= 1;
		}
	} else {
		ncl = (res == FR_DISK_ERR) ? 0xFFFFFFFF : 1;	/* Failed. Generate error status */
	}

	return ncl;		/* Return new cluster number or error status */
}

#endif /* !FF_FS_READONLY */




#if FF_USE_FASTSEEK
/*-----------------------------------------------------------------------*/
/* FAT handling - Convert offset into cluster with link map table        */
/*-----------------------------------------------------------------------*/

static DWORD clmt_clust (	/* <2:Error, >=2:Cluster number */
	FIL* fp,		/* Pointer to the file object */
	FSIZE_t ofs		/* File offset to be converted to cluster# */
)
{
	DWORD cl, ncl, *tbl;
	FATFS *fs = fp->obj.fs;


	tbl = fp->cltbl + 1;	/* Top of CLMT */
	cl = (DWORD)(ofs / SS(fs) / fs->csize);	/* Cluster order from top of the file */
	for (;;) {
		ncl = *tbl++;			/* Number of cluters in the fragment */
		if (ncl == 0) return 0;	/* End of table? (error) */
		if (cl < ncl) break;	/* In this fragment? */
		cl -= ncl; tbl++;		/* Next fragment */
	}
	return cl + *tbl;	/* Return the cluster number */
}

#endif	/* FF_USE_FASTSEEK */




/*-----------------------------------------------------------------------*/
/* Directory handling - Fill a cluster with zeros                        */
/*-----------------------------------------------------------------------*/

#if !FF_FS_READONLY
static FRESULT dir_clear (	/* Returns FR_OK or FR_DISK_ERR */
	FATFS *fs,		/* Filesystem object */
	DWORD clst		/* Directory table to clear */
)
{
	DWORD sect;
	UINT n, szb;
	BYTE *ibuf;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		/* Forced the fs point to its parents */
		if (ISCHILD(fs)) fs = PARENTFS(fs);
#endif

	if (sync_window(fs) != FR_OK) return FR_DISK_ERR;	/* Flush disk access window */
	sect = clst2sect(fs, clst);		/* Top of the cluster */
	fs->winsect = sect;				/* Set window to top of the cluster */
	mem_set(fs->win, 0, SS(fs));	/* Clear window buffer */
#if FF_USE_LFN == 3		/* Quick table clear by using multi-secter write */
	/* Allocate a temporary buffer */
	for (szb = ((DWORD)fs->csize * SS(fs) >= MAX_MALLOC) ? MAX_MALLOC : fs->csize * SS(fs), ibuf = 0; szb > SS(fs) && (ibuf = ff_memalloc(szb)) == 0; szb /= 2) ;
	if (szb > SS(fs)) {		/* Buffer allocated? */
		mem_set(ibuf, 0, szb);
		szb /= SS(fs);		/* Bytes -> Sectors */
		for (n = 0; n < fs->csize && disk_write(fs->pdrv, ibuf, sect + n, szb) == RES_OK; n += szb) ;	/* Fill the cluster with 0 */
		ff_memfree(ibuf);
	} else
#endif
	{
		ibuf = fs->win; szb = 1;	/* Use window buffer (many single-sector writes may take a time) */
		for (n = 0; n < fs->csize && disk_write(fs->pdrv, ibuf, sect + n, szb) == RES_OK; n += szb) ;	/* Fill the cluster with 0 */
	}
	return (n == fs->csize) ? FR_OK : FR_DISK_ERR;
}
#endif	/* !FF_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Directory handling - Set directory index                              */
/*-----------------------------------------------------------------------*/

static FRESULT dir_sdi (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp,				/* Pointer to directory object */
	DWORD ofs				/* Offset of directory table */
)
{
	DWORD csz, clst;
	FATFS *fs = dp->obj.fs;

	if (ofs >= (DWORD)MAX_DIR || ofs % SZDIRE) {
		/* Check range of offset and alignment */
		return FR_INT_ERR;
	}
	dp->dptr = ofs;				/* Set current offset */
	clst = dp->obj.sclust;		/* Table start cluster (0:root) */
	if (clst == 0 && fs->fs_type >= FS_FAT32) {	/* Replace cluster# 0 with root cluster# */
		clst = fs->dirbase;
	}

	if (clst == 0) {	/* Static table (root-directory on the FAT volume) */
		if (ofs / SZDIRE >= fs->n_rootdir) return FR_INT_ERR;	/* Is index out of range? */
		dp->sect = fs->dirbase;

	} else {		/* Dynamic table (sub-directory or root-directory in FAT32+) */
		csz = (DWORD)fs->csize * SS(fs);	/* Bytes per cluster */
		while (ofs >= csz) {				/* Follow cluster chain */
			clst = get_fat(&dp->obj, clst);				/* Get next cluster */
			if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
			if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;	/* Reached to end of table or internal error */
			ofs -= csz;
		}
		dp->sect = clst2sect(fs, clst);
	}
	dp->clust = clst;					/* Current cluster# */
	if (dp->sect == 0) return FR_INT_ERR;
	dp->sect += ofs / SS(fs);			/* Sector# of the directory entry */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	dp->dir = fs->win + (ofs % SS(fs));	/* Pointer to the entry in the win[] */
#else
	dp->dir = PARENTFS(fs)->win + (ofs % SS(PARENTFS(fs)));
#endif
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Move directory table index next                  */
/*-----------------------------------------------------------------------*/

static FRESULT dir_next (	/* FR_OK(0):succeeded, FR_NO_FILE:End of table, FR_DENIED:Could not stretch */
	DIR* dp,				/* Pointer to the directory object */
	int stretch				/* 0: Do not stretch table, 1: Stretch table if needed */
)
{
	DWORD ofs, clst;
	FATFS *fs = dp->obj.fs;


	ofs = dp->dptr + SZDIRE;	/* Next entry */
	if (ofs >= (DWORD)MAX_DIR) dp->sect = 0;
	if (dp->sect == 0) return FR_NO_FILE;	/* Report EOT if it has been disabled */

	if (ofs % SS(fs) == 0) {	/* Sector changed? */
		dp->sect++;				/* Next sector */

		if (dp->clust == 0) {	/* Static table */
			if (ofs / SZDIRE >= fs->n_rootdir) {	/* Report EOT if it reached end of static table */
				dp->sect = 0; return FR_NO_FILE;
			}
		}
		else {					/* Dynamic table */
			if ((ofs / SS(fs) & (fs->csize - 1)) == 0) {	/* Cluster changed? */
				clst = get_fat(&dp->obj, dp->clust);		/* Get next cluster */
				if (clst <= 1) return FR_INT_ERR;			/* Internal error */
				if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
				if (clst >= fs->n_fatent) {					/* It reached end of dynamic table */
#if !FF_FS_READONLY
					if (!stretch) {								/* If no stretch, report EOT */
						dp->sect = 0; return FR_NO_FILE;
					}
					clst = create_chain(&dp->obj, dp->clust);	/* Allocate a cluster */
					if (clst == 0) return FR_NO_SPACE_LEFT;		/* No free cluster */
					if (clst == 1) return FR_INT_ERR;			/* Internal error */
					if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
					if (dir_clear(fs, clst) != FR_OK) return FR_DISK_ERR;	/* Clean up the stretched table */
#else
					if (!stretch) dp->sect = 0;					/* (this line is to suppress compiler warning) */
					dp->sect = 0; return FR_NO_FILE;			/* Report EOT */
#endif
				}
				dp->clust = clst;		/* Initialize data for new cluster */
				dp->sect = clst2sect(fs, clst);
			}
		}
	}
	dp->dptr = ofs;		/* Current entry */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	dp->dir = fs->win + ofs % SS(fs);	/* Pointer to the entry in the win[] */
#else
	dp->dir = PARENTFS(fs)->win + (ofs % SS(PARENTFS(fs)));
#endif
	return FR_OK;
}




#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Directory handling - Reserve a block of directory entries             */
/*-----------------------------------------------------------------------*/

static FRESULT dir_alloc (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp,				/* Pointer to the directory object */
	UINT nent				/* Number of contiguous entries to allocate */
)
{
	FRESULT res;
	UINT n;
	FATFS *fs = dp->obj.fs;


	res = dir_sdi(dp, 0);
	if (res == FR_OK) {
		n = 0;
		do {
			res = move_window(fs, dp->sect);
			if (res != FR_OK) break;
			if (dp->dir[DIR_Name] == DDEM || dp->dir[DIR_Name] == 0) {
				if (++n == nent) break;	/* A block of contiguous free entries is found */
			} else {
				n = 0;					/* Not a blank entry. Restart to search */
			}
			res = dir_next(dp, 1);
		} while (res == FR_OK);	/* Next entry with table stretch enabled */
	}

	if (res == FR_NO_FILE) res = FR_DENIED;	/* No directory entry to allocate */
	return res;
}

#endif	/* !FF_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* FAT: Directory handling - Load/Store start cluster number             */
/*-----------------------------------------------------------------------*/

static DWORD ld_clust (	/* Returns the top cluster value of the SFN entry */
	FATFS* fs,			/* Pointer to the fs object */
	const BYTE* dir		/* Pointer to the key entry */
)
{
	DWORD cl;

	cl = ld_word(dir + DIR_FstClusLO);
	if (fs->fs_type == FS_FAT32) {
		cl |= (DWORD)ld_word(dir + DIR_FstClusHI) << 16;
	}

	return cl;
}


#if !FF_FS_READONLY
static void st_clust (
	FATFS* fs,	/* Pointer to the fs object */
	BYTE* dir,	/* Pointer to the key entry */
	DWORD cl	/* Value to be set */
)
{
	st_word(dir + DIR_FstClusLO, (WORD)cl);
	if (fs->fs_type == FS_FAT32) {
		st_word(dir + DIR_FstClusHI, (WORD)(cl >> 16));
	}
}
#endif



#if FF_USE_LFN
/*--------------------------------------------------------*/
/* FAT-LFN: Compare a part of file name with an LFN entry */
/*--------------------------------------------------------*/

static int cmp_lfn (		/* 1:matched, 0:not matched */
	const WCHAR* lfnbuf,	/* Pointer to the LFN working buffer to be compared */
	BYTE* dir				/* Pointer to the directory entry containing the part of LFN */
)
{
	UINT i, s;
	WCHAR wc, uc;


	if (ld_word(dir + LDIR_FstClusLO) != 0) return 0;	/* Check LDIR_FstClusLO */

	i = ((dir[LDIR_Ord] & 0x3F) - 1) * 13;	/* Offset in the LFN buffer */

	for (wc = 1, s = 0; s < 13; s++) {		/* Process all characters in the entry */
		uc = ld_word(dir + LfnOfs[s]);		/* Pick an LFN character */
		if (wc != 0) {
			if (i >= FF_MAX_LFN || ff_wtoupper(uc) != ff_wtoupper(lfnbuf[i++])) {	/* Compare it */
				return 0;					/* Not matched */
			}
			wc = uc;
		} else {
			if (uc != 0xFFFF) return 0;		/* Check filler */
		}
	}

	if ((dir[LDIR_Ord] & LLEF) && wc && lfnbuf[i]) return 0;	/* Last segment matched but different length */

	return 1;		/* The part of LFN matched */
}


#if FF_FS_MINIMIZE <= 1 || FF_FS_RPATH >= 2 || FF_USE_LABEL
/*-----------------------------------------------------*/
/* FAT-LFN: Pick a part of file name from an LFN entry */
/*-----------------------------------------------------*/

static int pick_lfn (	/* 1:succeeded, 0:buffer overflow or invalid LFN entry */
	WCHAR* lfnbuf,		/* Pointer to the LFN working buffer */
	BYTE* dir			/* Pointer to the LFN entry */
)
{
	UINT i, s;
	WCHAR wc, uc;


	if (ld_word(dir + LDIR_FstClusLO) != 0) return 0;	/* Check LDIR_FstClusLO is 0 */

	i = ((dir[LDIR_Ord] & ~LLEF) - 1) * 13;	/* Offset in the LFN buffer */

	for (wc = 1, s = 0; s < 13; s++) {		/* Process all characters in the entry */
		uc = ld_word(dir + LfnOfs[s]);		/* Pick an LFN character */
		if (wc != 0) {
			if (i >= FF_MAX_LFN) return 0;	/* Buffer overflow? */
			lfnbuf[i++] = wc = uc;			/* Store it */
		} else {
			if (uc != 0xFFFF) return 0;		/* Check filler */
		}
	}

	if (dir[LDIR_Ord] & LLEF) {				/* Put terminator if it is the last LFN part */
		if (i >= FF_MAX_LFN) return 0;		/* Buffer overflow? */
		lfnbuf[i] = 0;
	}

	return 1;		/* The part of LFN is valid */
}
#endif


#if !FF_FS_READONLY
/*-----------------------------------------*/
/* FAT-LFN: Create an entry of LFN entries */
/*-----------------------------------------*/

static void put_lfn (
	const WCHAR* lfn,	/* Pointer to the LFN */
	BYTE* dir,			/* Pointer to the LFN entry to be created */
	BYTE ord,			/* LFN order (1-20) */
	BYTE sum			/* Checksum of the corresponding SFN */
)
{
	UINT i, s;
	WCHAR wc;


	dir[LDIR_Chksum] = sum;			/* Set checksum */
	dir[LDIR_Attr] = AM_LFN;		/* Set attribute. LFN entry */
	dir[LDIR_Type] = 0;
	st_word(dir + LDIR_FstClusLO, 0);

	i = (ord - 1) * 13;				/* Get offset in the LFN working buffer */
	s = wc = 0;
	do {
		if (wc != 0xFFFF) wc = lfn[i++];	/* Get an effective character */
		st_word(dir + LfnOfs[s], wc);		/* Put it */
		if (wc == 0) wc = 0xFFFF;		/* Padding characters for left locations */
	} while (++s < 13);
	if (wc == 0xFFFF || !lfn[i]) ord |= LLEF;	/* Last LFN part is the start of LFN sequence */
	dir[LDIR_Ord] = ord;			/* Set the LFN order */
}

#endif	/* !FF_FS_READONLY */
#endif	/* FF_USE_LFN */



#if FF_USE_LFN && !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* FAT-LFN: Create a Numbered SFN                                        */
/*-----------------------------------------------------------------------*/

static void gen_numname (
	BYTE* dst,			/* Pointer to the buffer to store numbered SFN */
	const BYTE* src,	/* Pointer to SFN */
	const WCHAR* lfn,	/* Pointer to LFN */
	UINT seq			/* Sequence number */
)
{
	BYTE ns[8], c;
	UINT i, j;
	WCHAR wc;
	DWORD sr;


	mem_cpy(dst, src, 11);

	if (seq > 5) {	/* In case of many collisions, generate a hash number instead of sequential number */
		sr = seq;
		while (*lfn) {	/* Create a CRC as hash value */
			wc = *lfn++;
			for (i = 0; i < 16; i++) {
				sr = (sr << 1) + (wc & 1);
				wc >>= 1;
				if (sr & 0x10000) sr ^= 0x11021;
			}
		}
		seq = (UINT)sr;
	}

	/* itoa (hexdecimal) */
	i = 7;
	do {
		c = (BYTE)((seq % 16) + '0');
		if (c > '9') c += 7;
		ns[i--] = c;
		seq /= 16;
	} while (seq);
	ns[i] = '~';

	/* Append the number to the SFN body */
	for (j = 0; j < i && dst[j] != ' '; j++) {
		if (dbc_1st(dst[j])) {
			if (j == i - 1) break;
			j++;
		}
	}
	do {
		dst[j++] = (i < 8) ? ns[i++] : ' ';
	} while (j < 8);
}
#endif	/* FF_USE_LFN && !FF_FS_READONLY */



#if FF_USE_LFN
/*-----------------------------------------------------------------------*/
/* FAT-LFN: Calculate checksum of an SFN entry                           */
/*-----------------------------------------------------------------------*/

static BYTE sum_sfn (
	const BYTE* dir		/* Pointer to the SFN entry */
)
{
	BYTE sum = 0;
	UINT n = 11;

	do {
		sum = (sum >> 1) + (sum << 7) + *dir++;
	} while (--n);
	return sum;
}

#endif	/* FF_USE_LFN */




#if FF_FS_MINIMIZE <= 1 || FF_FS_RPATH >= 2 || FF_USE_LABEL
/*-----------------------------------------------------------------------*/
/* Read an object from the directory                                     */
/*-----------------------------------------------------------------------*/

#define DIR_READ_FILE(dp) dir_read(dp, 0)
#define DIR_READ_LABEL(dp) dir_read(dp, 1)

static FRESULT dir_read (
	DIR* dp,		/* Pointer to the directory object */
	int vol			/* Filtered by 0:file/directory or 1:volume label */
)
{
	FRESULT res = FR_NO_FILE;
	FATFS *fs = dp->obj.fs;
	BYTE attr, b;
#if FF_USE_LFN
	BYTE ord = 0xFF, sum = 0xFF;
#endif

	while (dp->sect) {
		res = move_window(fs, dp->sect);
		if (res != FR_OK) break;
		b = dp->dir[DIR_Name];	/* Test for the entry type */
		if (b == 0) {
			res = FR_NO_FILE; break; /* Reached to end of the directory */
		}

		/* On the FAT/FAT32 volume */
		dp->obj.attr = attr = dp->dir[DIR_Attr] & AM_MASK;	/* Get attribute */
#if FF_USE_LFN		/* LFN configuration */
		if (b == DDEM || b == '.' || (int)((attr & ~AM_ARC) == AM_VOL) != vol) {	/* An entry without valid data */
			ord = 0xFF;
		} else {
			if (attr == AM_LFN) {			/* An LFN entry is found */
				if (b & LLEF) {			/* Is it start of an LFN sequence? */
					sum = dp->dir[LDIR_Chksum];
					b &= (BYTE)~LLEF; ord = b;
					dp->blk_ofs = dp->dptr;
				}
				/* Check LFN validity and capture it */
				ord = (b == ord && sum == dp->dir[LDIR_Chksum] && pick_lfn(fs->lfnbuf, dp->dir)) ? ord - 1 : 0xFF;
			} else {					/* An SFN entry is found */
				if (ord != 0 || sum != sum_sfn(dp->dir)) {	/* Is there a valid LFN? */
					dp->blk_ofs = 0xFFFFFFFF;			/* It has no LFN. */
				}
				break;
			}
		}
#else	/* Non LFN configuration */
		if (b != DDEM && b != '.' && attr != AM_LFN && (int)((attr & ~AM_ARC) == AM_VOL) == vol) {	/* Is it a valid entry? */
			break;
		}
#endif
		res = dir_next(dp, 0);		/* Next entry */
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dp->sect = 0;		/* Terminate the read operation on error or EOT */
	return res;
}

#endif	/* FF_FS_MINIMIZE <= 1 || FF_USE_LABEL || FF_FS_RPATH >= 2 */



/*-----------------------------------------------------------------------*/
/* Directory handling - Find an object in the directory                  */
/*-----------------------------------------------------------------------*/

static FRESULT dir_find (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp					/* Pointer to the directory object with the file name */
)
{
	FRESULT res;
	FATFS *fs = dp->obj.fs;
	BYTE c;
#if FF_USE_LFN
	BYTE a, ord, sum;
#endif

	res = dir_sdi(dp, 0);			/* Rewind directory object */
	if (res != FR_OK) return res;

	/* On the FAT/FAT32 volume */
#if FF_USE_LFN
	ord = sum = 0xFF; dp->blk_ofs = 0xFFFFFFFF;	/* Reset LFN sequence */
#endif
	do {
		res = move_window(fs, dp->sect);
		if (res != FR_OK) break;
		c = dp->dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
#if FF_USE_LFN		/* LFN configuration */
		dp->obj.attr = a = dp->dir[DIR_Attr] & AM_MASK;
		if (c == DDEM || ((a & AM_VOL) && a != AM_LFN)) {	/* An entry without valid data */
			ord = 0xFF; dp->blk_ofs = 0xFFFFFFFF;	/* Reset LFN sequence */
		} else {
			if (a == AM_LFN) {			/* An LFN entry is found */
				if (!(dp->fn[NSFLAG] & NS_NOLFN)) {
					if (c & LLEF) {		/* Is it start of LFN sequence? */
						sum = dp->dir[LDIR_Chksum];
						c &= (BYTE)~LLEF; ord = c;	/* LFN start order */
						dp->blk_ofs = dp->dptr;	/* Start offset of LFN */
					}
					/* Check validity of the LFN entry and compare it with given name */
					ord = (c == ord && sum == dp->dir[LDIR_Chksum] && cmp_lfn(fs->lfnbuf, dp->dir)) ? ord - 1 : 0xFF;
				}
			} else {					/* An SFN entry is found */
				if (ord == 0 && sum == sum_sfn(dp->dir)) break;	/* LFN matched? */
				if (!(dp->fn[NSFLAG] & NS_LOSS) && !mem_cmp(dp->dir, dp->fn, 11)) break;	/* SFN matched? */
				ord = 0xFF; dp->blk_ofs = 0xFFFFFFFF;	/* Reset LFN sequence */
			}
		}
#else		/* Non LFN configuration */
		dp->obj.attr = dp->dir[DIR_Attr] & AM_MASK;
		if (!(dp->dir[DIR_Attr] & AM_VOL) && !mem_cmp(dp->dir, dp->fn, 11)) break;	/* Is it a valid entry? */
#endif
		res = dir_next(dp, 0);	/* Next entry */
	} while (res == FR_OK);

	return res;
}




#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Register an object to the directory                                   */
/*-----------------------------------------------------------------------*/

static FRESULT dir_register (	/* FR_OK:succeeded, FR_DENIED:no free entry or too many SFN collision, FR_DISK_ERR:disk error */
	DIR* dp						/* Target directory with object name to be created */
)
{
	FRESULT res;
	FATFS *fs = dp->obj.fs;
#if FF_USE_LFN		/* LFN configuration */
	UINT n, nlen, nent;
	BYTE sn[12], sum;


	if (dp->fn[NSFLAG] & (NS_DOT | NS_NONAME)) return FR_INVALID_NAME;	/* Check name validity */
	for (nlen = 0; fs->lfnbuf[nlen]; nlen++) ;	/* Get lfn length */

	/* On the FAT/FAT32 volume */
	mem_cpy(sn, dp->fn, 12);
	if (sn[NSFLAG] & NS_LOSS) {			/* When LFN is out of 8.3 format, generate a numbered name */
		dp->fn[NSFLAG] = NS_NOLFN;		/* Find only SFN */
		for (n = 1; n < 100; n++) {
			gen_numname(dp->fn, sn, fs->lfnbuf, n);	/* Generate a numbered name */
			res = dir_find(dp);				/* Check if the name collides with existing SFN */
			if (res != FR_OK) break;
		}
		if (n == 100) return FR_DENIED;		/* Abort if too many collisions */
		if (res != FR_NO_FILE) return res;	/* Abort if the result is other than 'not collided' */
		dp->fn[NSFLAG] = sn[NSFLAG];
	}

	/* Create an SFN with/without LFNs. */
	nent = (sn[NSFLAG] & NS_LFN) ? (nlen + 12) / 13 + 1 : 1;	/* Number of entries to allocate */
	res = dir_alloc(dp, nent);		/* Allocate entries */
	if (res == FR_OK && --nent) {	/* Set LFN entry if needed */
		res = dir_sdi(dp, dp->dptr - nent * SZDIRE);
		if (res == FR_OK) {
			sum = sum_sfn(dp->fn);	/* Checksum value of the SFN tied to the LFN */
			do {					/* Store LFN entries in bottom first */
				res = move_window(fs, dp->sect);
				if (res != FR_OK) break;
				put_lfn(fs->lfnbuf, dp->dir, (BYTE)nent, sum);
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
				fs->wflag = 1;
#else
				PARENTFS(fs)->wflag = 1;
#endif
				res = dir_next(dp, 0);	/* Next entry */
			} while (res == FR_OK && --nent);
		}
	}

#else	/* Non LFN configuration */
	res = dir_alloc(dp, 1);		/* Allocate an entry for SFN */

#endif

	/* Set SFN entry */
	if (res == FR_OK) {
		res = move_window(fs, dp->sect);
		if (res == FR_OK) {
			mem_set(dp->dir, 0, SZDIRE);	/* Clean the entry */
			mem_cpy(dp->dir + DIR_Name, dp->fn, 11);	/* Put SFN */
#if FF_USE_LFN
			dp->dir[DIR_NTres] = dp->fn[NSFLAG] & (NS_BODY | NS_EXT);	/* Put NT flag */
#endif
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			fs->wflag = 1;
#else
			PARENTFS(fs)->wflag = 1;
#endif
		}
	}

	return res;
}

#endif /* !FF_FS_READONLY */



#if !FF_FS_READONLY && FF_FS_MINIMIZE == 0
/*-----------------------------------------------------------------------*/
/* Remove an object from the directory                                   */
/*-----------------------------------------------------------------------*/

static FRESULT dir_remove (	/* FR_OK:Succeeded, FR_DISK_ERR:A disk error */
	DIR* dp					/* Directory object pointing the entry to be removed */
)
{
	FRESULT res;
	FATFS *fs = dp->obj.fs;
#if FF_USE_LFN		/* LFN configuration */
	DWORD last = dp->dptr;
	res = (dp->blk_ofs == 0xFFFFFFFF) ? FR_OK : dir_sdi(dp, dp->blk_ofs);	/* Goto top of the entry block if LFN is exist */
	if (res == FR_OK) {
		do {
			res = move_window(fs, dp->sect);
			if (res != FR_OK) break;
			/* Mark an entry 'deleted' */  	/* On the FAT/32 volume */
			dp->dir[DIR_Name] = DDEM;

#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			fs->wflag = 1;
#else
			PARENTFS(fs)->wflag = 1;
#endif
			if (dp->dptr >= last) break;	/* If reached last entry then all entries of the object has been deleted. */
			res = dir_next(dp, 0);		/* Next entry */
		} while (res == FR_OK);
		if (res == FR_NO_FILE) res = FR_INT_ERR;
	}
#else			/* Non LFN configuration */

	res = move_window(fs, dp->sect);
	if (res == FR_OK) {
		dp->dir[DIR_Name] = DDEM;	/* Mark the entry 'deleted'.*/
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		fs->wflag = 1;
#else
		PARENTFS(fs)->wflag = 1;
#endif
	}
#endif
	return res;
}

#endif /* !FF_FS_READONLY && FF_FS_MINIMIZE == 0 */



#if FF_FS_MINIMIZE <= 1 || FF_FS_RPATH >= 2
/*-----------------------------------------------------------------------*/
/* Get file information from directory entry                             */
/*-----------------------------------------------------------------------*/

static void get_fileinfo (
	DIR* dp,			/* Pointer to the directory object */
	FILINFO* fno		/* Pointer to the file information to be filled */
)
{
	UINT si, di;
#if FF_USE_LFN
	WCHAR wc, hs;
	FATFS *fs = dp->obj.fs;
#else
	TCHAR c;
#endif


	fno->fname[0] = 0;			/* Invaidate file info */
	if (dp->sect == 0) return;	/* Exit if read pointer has reached end of directory */

#if FF_USE_LFN		/* LFN configuration */
	/* On the FAT/32 volume */
	if (dp->blk_ofs != 0xFFFFFFFF) {	/* Get LFN if available */
		si = di = hs = 0;
		while (fs->lfnbuf[si] != 0) {
			wc = fs->lfnbuf[si++];		/* Get an LFN character (UTF-16) */
			if (hs == 0 && IsSurrogate(wc)) {	/* Is it a surrogate? */
				hs = wc; continue;		/* Get low surrogate */
			}
			wc = put_utf((DWORD)hs << 16 | wc, &fno->fname[di], FF_LFN_BUF - di);	/* Store it in UTF-16 or UTF-8 encoding */
			if (wc == 0) { di = 0; break; }	/* Invalid char or buffer overflow? */
			di += wc;
			hs = 0;
		}
		if (hs != 0) di = 0;	/* Broken surrogate pair? */
		fno->fname[di] = 0;		/* Terminate the LFN (null string means LFN is invalid) */
	}
	si = di = 0;
	while (si < 11) {		/* Get SFN from SFN entry */
		wc = dp->dir[si++];			/* Get a char */
		if (wc == ' ') continue;	/* Skip padding spaces */
		if (wc == RDDEM) wc = DDEM;	/* Restore replaced DDEM character */
		if (si == 9 && di < FF_SFN_BUF) fno->altname[di++] = '.';	/* Insert a . if extension is exist */
#if FF_LFN_UNICODE >= 1	/* Unicode output */
		if (dbc_1st((BYTE)wc) && si != 8 && si != 11 && dbc_2nd(dp->dir[si])) {	/* Make a DBC if needed */
			wc = wc << 8 | dp->dir[si++];
		}
		wc = ff_oem2uni(wc, CODEPAGE);		/* ANSI/OEM -> Unicode */
		if (wc == 0) { di = 0; break; }		/* Wrong char in the current code page? */
		wc = put_utf(wc, &fno->altname[di], FF_SFN_BUF - di);	/* Store it in Unicode */
		if (wc == 0) { di = 0; break; }		/* Buffer overflow? */
		di += wc;
#else					/* ANSI/OEM output */
		fno->altname[di++] = (TCHAR)wc;	/* Store it without any conversion */
#endif
	}
	fno->altname[di] = 0;	/* Terminate the SFN  (null string means SFN is invalid) */

	if (fno->fname[0] == 0) {	/* If LFN is invalid, altname[] needs to be copied to fname[] */
		if (di == 0) {	/* If LFN and SFN both are invalid, this object is inaccesible */
			fno->fname[di++] = '?';
		} else {
			for (si = di = 0; fno->altname[si]; si++, di++) {	/* Copy altname[] to fname[] with case information */
				wc = (WCHAR)fno->altname[si];
				if (IsUpper(wc) && (dp->dir[DIR_NTres] & ((si >= 9) ? NS_EXT : NS_BODY))) wc += 0x20;
				fno->fname[di] = (TCHAR)wc;
			}
		}
		fno->fname[di] = 0;	/* Terminate the LFN */
		if (!dp->dir[DIR_NTres]) fno->altname[0] = 0;	/* Altname is not needed if neither LFN nor case info is exist. */
	}

#else	/* Non-LFN configuration */
	si = di = 0;
	while (si < 11) {		/* Copy name body and extension */
		c = (TCHAR)dp->dir[si++];
		if (c == ' ') continue;		/* Skip padding spaces */
		if (c == RDDEM) c = DDEM;	/* Restore replaced DDEM character */
		if (si == 9) fno->fname[di++] = '.';/* Insert a . if extension is exist */
		fno->fname[di++] = c;
	}
	fno->fname[di] = 0;
#endif

	fno->fattrib = dp->dir[DIR_Attr];					/* Attribute */
	fno->fsize = ld_dword(dp->dir + DIR_FileSize);		/* Size */
	fno->ftime = ld_word(dp->dir + DIR_ModTime + 0);	/* Time */
	fno->fdate = ld_word(dp->dir + DIR_ModTime + 2);	/* Date */
#if FF_USE_LFN != 0
	fno->sclst = ld_clust(fs, dp->dir);
#endif
}

#endif /* FF_FS_MINIMIZE <= 1 || FF_FS_RPATH >= 2 */



#if FF_USE_FIND && FF_FS_MINIMIZE <= 1
/*-----------------------------------------------------------------------*/
/* Pattern matching                                                      */
/*-----------------------------------------------------------------------*/

static DWORD get_achar (	/* Get a character and advances ptr */
	const TCHAR** ptr		/* Pointer to pointer to the ANSI/OEM or Unicode string */
)
{
	DWORD chr;


#if FF_USE_LFN && FF_LFN_UNICODE >= 1	/* Unicode input */
	chr = tchar2uni(ptr);
	if (chr == 0xFFFFFFFF) chr = 0;		/* Wrong UTF encoding is recognized as end of the string */
	chr = ff_wtoupper(chr);

#else									/* ANSI/OEM input */
	chr = (BYTE)*(*ptr)++;				/* Get a byte */
	if (IsLower(chr)) chr -= 0x20;		/* To upper ASCII char */
#if FF_CODE_PAGE == 0
	if (ExCvt && chr >= 0x80) chr = ExCvt[chr - 0x80];	/* To upper SBCS extended char */
#elif FF_CODE_PAGE < 900
	if (chr >= 0x80) chr = ExCvt[chr - 0x80];	/* To upper SBCS extended char */
#endif
#if FF_CODE_PAGE == 0 || FF_CODE_PAGE >= 900
	if (dbc_1st((BYTE)chr)) {	/* Get DBC 2nd byte if needed */
		chr = dbc_2nd((BYTE)**ptr) ? chr << 8 | (BYTE)*(*ptr)++ : 0;
	}
#endif

#endif
	return chr;
}


static int pattern_matching (	/* 0:not matched, 1:matched */
	const TCHAR* pat,	/* Matching pattern */
	const TCHAR* nam,	/* String to be tested */
	int skip,			/* Number of pre-skip chars (number of ?s) */
	int inf				/* Infinite search (* specified) */
)
{
	const TCHAR *pp, *np;
	DWORD pc, nc;
	int nm, nx;


	while (skip--) {				/* Pre-skip name chars */
		if (!get_achar(&nam)) return 0;	/* Branch mismatched if less name chars */
	}
	if (*pat == 0 && inf) return 1;	/* (short circuit) */

	do {
		pp = pat; np = nam;			/* Top of pattern and name to match */
		for (;;) {
			if (*pp == '?' || *pp == '*') {	/* Wildcard? */
				nm = nx = 0;
				do {				/* Analyze the wildcard block */
					if (*pp++ == '?') nm++; else nx = 1;
				} while (*pp == '?' || *pp == '*');
				if (pattern_matching(pp, np, nm, nx)) return 1;	/* Test new branch (recurs upto number of wildcard blocks in the pattern) */
				nc = *np; break;	/* Branch mismatched */
			}
			pc = get_achar(&pp);	/* Get a pattern char */
			nc = get_achar(&np);	/* Get a name char */
			if (pc != nc) break;	/* Branch mismatched? */
			if (pc == 0) return 1;	/* Branch matched? (matched at end of both strings) */
		}
		get_achar(&nam);			/* nam++ */
	} while (inf && nc);			/* Retry until end of name if infinite search is specified */

	return 0;
}

#endif /* FF_USE_FIND && FF_FS_MINIMIZE <= 1 */



/*-----------------------------------------------------------------------*/
/* Pick a top segment and create the object name in directory form       */
/*-----------------------------------------------------------------------*/

FRESULT create_name (		/* FR_OK: successful, FR_INVALID_NAME: could not create */
	DIR* dp,				/* Pointer to the directory object */
	const TCHAR** path		/* Pointer to pointer to the segment in the path string */
)
{
#if FF_USE_LFN		/* LFN configuration */
	BYTE b, cf;
	WCHAR wc, *lfn;
	DWORD uc;
	UINT i, ni, si, di;
	const TCHAR *p;


	/* Create LFN into LFN working buffer */
	p = *path; lfn = dp->obj.fs->lfnbuf; di = 0;
	for (;;) {
		uc = tchar2uni(&p);			/* Get a character */
		if (uc == 0xFFFFFFFF) return FR_INVALID_NAME;		/* Invalid code or UTF decode error */
		if (uc >= 0x10000) lfn[di++] = (WCHAR)(uc >> 16);	/* Store high surrogate if needed */
		wc = (WCHAR)uc;
		if (wc < ' ' || wc == '/' || wc == '\\') break;	/* Break if end of the path or a separator is found */
		if (wc < 0x80 && chk_chr("\"*:<>\?|\x7F", wc)) return FR_INVALID_NAME;	/* Reject illegal characters for LFN */
		if (di >= FF_MAX_LFN) return FR_INVALID_NAME;	/* Reject too long name */
		lfn[di++] = wc;					/* Store the Unicode character */
	}
	while (*p == '/' || *p == '\\') p++;	/* Skip duplicated separators if exist */
	*path = p;							/* Return pointer to the next segment */
	cf = (wc < ' ') ? NS_LAST : 0;		/* Set last segment flag if end of the path */

#if FF_FS_RPATH != 0
	if ((di == 1 && lfn[di - 1] == '.') ||
		(di == 2 && lfn[di - 1] == '.' && lfn[di - 2] == '.')) {	/* Is this segment a dot name? */
		lfn[di] = 0;
		for (i = 0; i < 11; i++) {		/* Create dot name for SFN entry */
			dp->fn[i] = (i < di) ? '.' : ' ';
		}
		dp->fn[i] = cf | NS_DOT;		/* This is a dot entry */
		return FR_OK;
	}
#endif
	while (di) {						/* Snip off trailing spaces and dots if exist */
		wc = lfn[di - 1];
		if (wc != ' ' && wc != '.') break;
		di--;
	}
	lfn[di] = 0;							/* LFN is created into the working buffer */
	if (di == 0) return FR_INVALID_NAME;	/* Reject null name */

	/* Create SFN in directory form */
	for (si = 0; lfn[si] == ' '; si++) ;	/* Remove leading spaces */
	if (si > 0 || lfn[si] == '.') cf |= NS_LOSS | NS_LFN;	/* Is there any leading space or dot? */
	while (di > 0 && lfn[di - 1] != '.') di--;	/* Find last dot (di<=si: no extension) */

	mem_set(dp->fn, ' ', 11);
	i = b = 0; ni = 8;
	for (;;) {
		wc = lfn[si++];					/* Get an LFN character */
		if (wc == 0) break;				/* Break on end of the LFN */
		if (wc == ' ' || (wc == '.' && si != di)) {	/* Remove embedded spaces and dots */
			cf |= NS_LOSS | NS_LFN;
			continue;
		}

		if (i >= ni || si == di) {		/* End of field? */
			if (ni == 11) {				/* Name extension overflow? */
				cf |= NS_LOSS | NS_LFN;
				break;
			}
			if (si != di) cf |= NS_LOSS | NS_LFN;	/* Name body overflow? */
			if (si > di) break;						/* No name extension? */
			si = di; i = 8; ni = 11; b <<= 2;		/* Enter name extension */
			continue;
		}

		if (wc >= 0x80) {	/* Is this a non-ASCII character? */
			cf |= NS_LFN;	/* LFN entry needs to be created */
#if FF_CODE_PAGE == 0
			if (ExCvt) {	/* At SBCS */
				wc = ff_uni2oem(wc, CODEPAGE);			/* Unicode ==> ANSI/OEM code */
				if (wc & 0x80) wc = ExCvt[wc & 0x7F];	/* Convert extended character to upper (SBCS) */
			} else {		/* At DBCS */
				wc = ff_uni2oem(ff_wtoupper(wc), CODEPAGE);	/* Unicode ==> Upper convert ==> ANSI/OEM code */
			}
#elif FF_CODE_PAGE < 900	/* SBCS cfg */
			wc = ff_uni2oem(wc, CODEPAGE);			/* Unicode ==> ANSI/OEM code */
			if (wc & 0x80) wc = ExCvt[wc & 0x7F];	/* Convert extended character to upper (SBCS) */
#else						/* DBCS cfg */
			wc = ff_uni2oem(ff_wtoupper(wc), CODEPAGE);	/* Unicode ==> Upper convert ==> ANSI/OEM code */
#endif
		}

		if (wc >= 0x100) {				/* Is this a DBC? */
			if (i >= ni - 1) {			/* Field overflow? */
				cf |= NS_LOSS | NS_LFN;
				i = ni; continue;		/* Next field */
			}
			dp->fn[i++] = (BYTE)(wc >> 8);	/* Put 1st byte */
		} else {						/* SBC */
			if (wc == 0 || chk_chr("+,;=[]", wc)) {	/* Replace illegal characters for SFN if needed */
				wc = '_'; cf |= NS_LOSS | NS_LFN;/* Lossy conversion */
			} else {
				if (IsUpper(wc)) {		/* ASCII upper case? */
					b |= 2;
				}
				if (IsLower(wc)) {		/* ASCII lower case? */
					b |= 1; wc -= 0x20;
				}
			}
		}
		dp->fn[i++] = (BYTE)wc;
	}

	if (dp->fn[0] == DDEM) dp->fn[0] = RDDEM;	/* If the first character collides with DDEM, replace it with RDDEM */

	if (ni == 8) b <<= 2;				/* Shift capital flags if no extension */
	if ((b & 0x0C) == 0x0C || (b & 0x03) == 0x03) cf |= NS_LFN;	/* LFN entry needs to be created if composite capitals */
	if (!(cf & NS_LFN)) {				/* When LFN is in 8.3 format without extended character, NT flags are created */
		if (b & 0x01) cf |= NS_EXT;		/* NT flag (Extension has small capital letters only) */
		if (b & 0x04) cf |= NS_BODY;	/* NT flag (Body has small capital letters only) */
	}

	dp->fn[NSFLAG] = cf;	/* SFN is created into dp->fn[] */

	return FR_OK;


#else	/* FF_USE_LFN : Non-LFN configuration */
	BYTE c, d, *sfn;
	UINT ni, si, i;
	const char *p;

	/* Create file name in directory form */
	p = *path; sfn = dp->fn;
	mem_set(sfn, ' ', 11);
	si = i = 0; ni = 8;
#if FF_FS_RPATH != 0
	if (p[si] == '.') { /* Is this a dot entry? */
		for (;;) {
			c = (BYTE)p[si++];
			if (c != '.' || si >= 3) break;
			sfn[i++] = c;
		}
		if (c != '/' && c != '\\' && c > ' ') return FR_INVALID_NAME;
		*path = p + si;								/* Return pointer to the next segment */
		sfn[NSFLAG] = (c <= ' ') ? NS_LAST | NS_DOT : NS_DOT;	/* Set last segment flag if end of the path */
		return FR_OK;
	}
#endif
	for (;;) {
		c = (BYTE)p[si++];				/* Get a byte */
		if (c <= ' ') break; 			/* Break if end of the path name */
		if (c == '/' || c == '\\') {	/* Break if a separator is found */
			while (p[si] == '/' || p[si] == '\\') si++;	/* Skip duplicated separator if exist */
			break;
		}
		if (c == '.' || i >= ni) {		/* End of body or field overflow? */
			if (ni == 11 || c != '.') return FR_INVALID_NAME;	/* Field overflow or invalid dot? */
			i = 8; ni = 11;				/* Enter file extension field */
			continue;
		}
#if FF_CODE_PAGE == 0
		if (ExCvt && c >= 0x80) {		/* Is SBC extended character? */
			c = ExCvt[c & 0x7F];		/* To upper SBC extended character */
		}
#elif FF_CODE_PAGE < 900
		if (c >= 0x80) {				/* Is SBC extended character? */
			c = ExCvt[c & 0x7F];		/* To upper SBC extended character */
		}
#endif
		if (dbc_1st(c)) {				/* Check if it is a DBC 1st byte */
			d = (BYTE)p[si++];			/* Get 2nd byte */
			if (!dbc_2nd(d) || i >= ni - 1) return FR_INVALID_NAME;	/* Reject invalid DBC */
			sfn[i++] = c;
			sfn[i++] = d;
		} else {						/* SBC */
			if (chk_chr("\"*+,:;<=>\?[]|\x7F", c)) return FR_INVALID_NAME;	/* Reject illegal chrs for SFN */
			if (IsLower(c)) c -= 0x20;	/* To upper */
			sfn[i++] = c;
		}
	}
	*path = p + si;						/* Return pointer to the next segment */
	if (i == 0) return FR_INVALID_NAME;	/* Reject nul string */

	if (sfn[0] == DDEM) sfn[0] = RDDEM;	/* If the first character collides with DDEM, replace it with RDDEM */
	sfn[NSFLAG] = (c <= ' ') ? NS_LAST : 0;		/* Set last segment flag if end of the path */

	return FR_OK;
#endif /* FF_USE_LFN */
}




/*-----------------------------------------------------------------------*/
/* Follow a file path                                                    */
/*-----------------------------------------------------------------------*/

static FRESULT follow_path (	/* FR_OK(0): successful, !=0: error code */
	DIR* dp,					/* Directory object to return last directory and found object */
	const TCHAR* path			/* Full-path string to find a file or directory */
)
{
	FRESULT res;
	BYTE ns;
	FATFS *fs = dp->obj.fs;


#if FF_FS_RPATH != 0
	if (*path != '/' && *path != '\\') {	/* Without heading separator */
		dp->obj.sclust = fs->cdir;				/* Start from current directory */
	} else
#endif
	{										/* With heading separator */
		while (*path == '/' || *path == '\\') path++;	/* Strip heading separator */
		dp->obj.sclust = 0;					/* Start from root directory */
	}

	if ((UINT)*path < ' ') {				/* Null path name is the origin directory itself */
		dp->fn[NSFLAG] = NS_NONAME;
		res = dir_sdi(dp, 0);

	} else {								/* Follow path */
		for (;;) {
			res = create_name(dp, &path);	/* Get a segment name of the path */
			if (res != FR_OK) break;
			res = dir_find(dp);				/* Find an object with the segment name */
			ns = dp->fn[NSFLAG];
			if (res != FR_OK) {				/* Failed to find the object */
				if (res == FR_NO_FILE) {	/* Object is not found */
					if (FF_FS_RPATH && (ns & NS_DOT)) {	/* If dot entry is not exist, stay there */
						if (!(ns & NS_LAST)) continue;	/* Continue to follow if not last segment */
						dp->fn[NSFLAG] = NS_NONAME;
						res = FR_OK;
					} else {							/* Could not find the object */
						if (!(ns & NS_LAST)) res = FR_NO_PATH;	/* Adjust error code if not last segment */
					}
				}
				break;
			}
			if (ns & NS_LAST) break;			/* Last segment matched. Function completed. */
			/* Get into the sub-directory */
			if (!(dp->obj.attr & AM_DIR)) {		/* It is not a sub-directory and cannot follow */
				res = FR_NO_PATH; break;
			}
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			dp->obj.sclust = ld_clust(fs, fs->win + dp->dptr % SS(fs));	/* Open next directory */
#else
			dp->obj.sclust = ld_clust(PARENTFS(fs), PARENTFS(fs)->win + dp->dptr % SS(PARENTFS(fs)));
#endif
		}
	}

	return res;
}




/*-----------------------------------------------------------------------*/
/* Get logical drive number from path name                               */
/*-----------------------------------------------------------------------*/

static int get_ldnumber (	/* Returns logical drive number (-1:invalid drive number or null pointer) */
	const TCHAR** path		/* Pointer to pointer to the path name */
)
{
	const TCHAR *tp, *tt;
	TCHAR tc;
	int i, vol = -1;
#if FF_STR_VOLUME_ID		/* Find string volume ID */
	const char *sp;
	char c;
#endif

	tt = tp = *path;
	if (!tp) return vol;	/* Invalid path name? */
	do tc = *tt++; while ((UINT)tc >= (FF_USE_LFN ? ' ' : '!') && tc != ':');	/* Find a colon in the path */

	if (tc == ':') {	/* DOS/Windows style volume ID? */
		i = *tp++ - '0';
		if (IsDigit(*tp) && tp != tt) { /* Is there a numeric volume ID + colon? */
			i = 10 * i + *tp - '0';       /* Get the LD number */
		}
#if FF_STR_VOLUME_ID == 1	/* Arbitrary string is enabled */
		else {
			i = 0;
			do {
				sp = VolumeStr[i]; tp = *path;	/* This string volume ID and path name */
				do {	/* Compare the volume ID with path name */
					c = *sp++; tc = *tp++;
					if (IsLower(c)) c -= 0x20;
					if (IsLower(tc)) tc -= 0x20;
				} while (c && (TCHAR)c == tc);
			} while ((c || tp != tt) && ++i < FF_VOLUMES);	/* Repeat for each id until pattern match */
		}
#endif
		if (i < FF_VOLUMES) {	/* If a volume ID is found, get the drive number and strip it */
			vol = i;		/* Drive number */
			*path = tt;		/* Snip the drive prefix off */
		}
		return vol;
	}
#if FF_STR_VOLUME_ID == 2		/* Unix style volume ID is enabled */
	if (*tp == '/') {
		i = 0;
		do {
			sp = VolumeStr[i]; tp = *path;	/* This string volume ID and path name */
			do {	/* Compare the volume ID with path name */
				c = *sp++; tc = *(++tp);
				if (IsLower(c)) c -= 0x20;
				if (IsLower(tc)) tc -= 0x20;
			} while (c && (TCHAR)c == tc);
		} while ((c || (tc != '/' && (UINT)tc >= (FF_USE_LFN ? ' ' : '!'))) && ++i < FF_VOLUMES);	/* Repeat for each ID until pattern match */
		if (i < FF_VOLUMES) {	/* If a volume ID is found, get the drive number and strip it */
			vol = i;		/* Drive number */
			*path = tp;		/* Snip the drive prefix off */
			return vol;
		}
	}
#endif
	/* No drive prefix is found */
#if FF_FS_RPATH != 0
	vol = CurrVol;	/* Default drive is current drive */
#else
	vol = 0;		/* Default drive is 0 */
#endif
	return vol;		/* Return the default drive */
}




/*-----------------------------------------------------------------------*/
/* Load a sector and check if it is an FAT VBR                           */
/*-----------------------------------------------------------------------*/

static BYTE check_fs (	/* 0:FAT, 2:Valid BS but not FAT, 3:Not a BS, 4:Disk error */
	FATFS* fs,	/* File system object */
	QWORD sect	/* Sector# (lba) to load and check if it is an FAT-VBR or not */
)
{
	fs->wflag = 0; fs->winsect = 0xFFFFFFFF;	/* Invaidate window */
	if (move_window(fs, sect) != FR_OK) return 4;	/* Load boot record */

	if (ld_word(fs->win + BS_55AA) != 0xAA55) return 3;	/* Check boot record signature (always here regardless of the sector size) */

	if (fs->win[BS_JmpBoot] == 0xE9 || fs->win[BS_JmpBoot] == 0xEB || fs->win[BS_JmpBoot] == 0xE8) {	/* Valid JumpBoot code? */
		if (!mem_cmp(fs->win + BS_FilSysType, "FAT", 3)) return 0;		/* Is it an FAT VBR? */
		if (!mem_cmp(fs->win + BS_FilSysType32, "FAT32", 5)) return 0;	/* Is it an FAT32 VBR? */
	}
	return 2;
}




/*-----------------------------------------------------------------------*/
/* Determine logical drive number and mount the volume if needed         */
/*-----------------------------------------------------------------------*/

FRESULT find_volume (	/* FR_OK(0): successful, !=0: an error occurred */
	const TCHAR** path,			/* Pointer to pointer to the path name (drive number) */
	FATFS** rfs,				/* Pointer to pointer to the found filesystem object */
	BYTE mode					/* !=0: Check write protection for write access */
)
{
	BYTE fmt, *pt;
	int vol;
	DSTATUS stat;
	DWORD fasize, tsect, sysect, nclst, szbfat;
	QWORD bsect;
	WORD nrsv;
	FATFS *fs;
	UINT i;
	int extended_br;
	int extended_pos = -1;
	DWORD offset = 0;


	/* Get logical drive number */
	*rfs = 0;
	vol = get_ldnumber(path);
	if (vol < 0) return FR_INVALID_DRIVE;

	/* Check if the filesystem object is valid or not */
	fs = FatFs[vol];					/* Get pointer to the filesystem object */
	if (!fs) return FR_NOT_ENABLED;		/* Is the filesystem object available? */
#if FF_FS_REENTRANT
	if (!lock_fs(fs)) return FR_TIMEOUT;	/* Lock the volume */
#endif
	*rfs = fs;							/* Return pointer to the filesystem object */

	mode &= (BYTE)~FA_READ;				/* Desired access mode, write access or not */
	if (fs->fs_type != 0) {				/* If the volume has been mounted */
		stat = disk_status(fs->pdrv);
		if (!(stat & STA_NOINIT)) {		/* and the physical drive is kept initialized */
			if (!FF_FS_READONLY && mode && (stat & STA_PROTECT)) {	/* Check write protection if needed */
				return FR_WRITE_PROTECTED;
			}
			return FR_OK;				/* The filesystem object is valid */
		}
	}

	/* The filesystem object is not valid. */
	/* Following code attempts to mount the volume. (analyze BPB and initialize the filesystem object) */

	fs->fs_type = 0;					/* Clear the filesystem object */
	fs->pdrv = LD2PD(vol);				/* Bind the logical drive and a physical drive */
	stat = disk_initialize(fs->pdrv);	/* Initialize the physical drive */
	if (stat & STA_NOINIT) { 			/* Check if the initialization succeeded */
		return FR_NOT_READY;			/* Failed to initialize due to no medium or hard error */
	}
	if (!FF_FS_READONLY && mode && (stat & STA_PROTECT)) { /* Check disk write protection if needed */
		return FR_WRITE_PROTECTED;
	}
#if FF_MAX_SS != FF_MIN_SS				/* Get sector size (multiple sector size cfg only) */
	if (disk_ioctl(fs->pdrv, GET_SECTOR_SIZE, &SS(fs)) != RES_OK) return FR_DISK_ERR;
	if (SS(fs) > FF_MAX_SS || SS(fs) < FF_MIN_SS || (SS(fs) & (SS(fs) - 1))) return FR_DISK_ERR;
#endif

	if (fs->win == NULL) {
		fs->win = (BYTE*) ff_memalloc(SS(fs));
		if (fs->win == NULL)
			return FR_NOT_ENOUGH_CORE;
	}

	/* Find an FAT partition on the drive. Supports only generic partitioning rules, FDISK (MBR) and SFD (w/o partition). */
	bsect = 0;
	fmt = check_fs(fs, bsect);		/* Load sector 0 and check if it is an FAT-VBR as SFD */
	if (fmt == 2 || (fmt < 2 && LD2PT(vol) != 0)) {	/* Not an FAT-VBR or forced partition number */
		if (fs->win[MBR_Table + 4] != 0xEE) {	/* The partition type is GPT, not MBR */
			/* Read MBR and EBR to get right boot sector. */
			extended_br = LD2PT(vol) - 4;
			if (extended_br > 0) {
				for (i = 0; i < 4; i++) {
					pt = fs->win + MBR_Table + i * SZ_PTE;
					if (pt[4] == 0x0F || pt[4] == 0x05) extended_pos = i;
				}
				pt = fs->win + MBR_Table + extended_pos * SZ_PTE;
				bsect = ld_dword(&pt[8]);
				do {
					mem_set(fs->win, 0, SS(fs));
					if (disk_raw_read(LD2DI(vol), fs->win, bsect + offset, 1) != RES_OK) return FR_DISK_ERR;
					pt = fs->win + MBR_Table;
					offset = ld_dword(&pt[SZ_PTE + 8]);
				} while (--extended_br);
			}
			i = LD2PT(vol);				/* Partition number: 0:auto, 1-4:primary, >4:logical */
			if (i) {					/* Find an FAT volume */
				bsect = LD2PS(vol);
			} else {
				pt = fs->win + MBR_Table;
				bsect = pt[4] ? ld_dword(&pt[8]) : 0;
			}
		}
		else {
			bsect = LD2PS(vol);		/* Volume start sector */
		}
		fmt = bsect ? check_fs(fs, bsect) : 2;		/* Check the partition */
	}

	if (fmt == 4) return FR_DISK_ERR;		/* An error occured in the disk I/O layer */
	if (fmt >= 2) return FR_NO_FILESYSTEM;	/* No FAT volume is found */

	/* An FAT volume is found. Following code initializes the file system object */

	if (ld_word(fs->win + BPB_BytsPerSec) != SS(fs)) return FR_NO_FILESYSTEM;	/* (BPB_BytsPerSec must be equal to the physical sector size) */

	fasize = ld_word(fs->win + BPB_FATSz16);		/* Number of sectors per FAT */
	if (fasize == 0) fasize = ld_dword(fs->win + BPB_FATSz32);
	fs->fsize = fasize;

	fs->n_fats = fs->win[BPB_NumFATs];				/* Number of FATs */
	if (fs->n_fats != 1 && fs->n_fats != 2) return FR_NO_FILESYSTEM;	/* (Must be 1 or 2) */
	fasize *= fs->n_fats;								/* Number of sectors for FAT area */

	fs->csize = fs->win[BPB_SecPerClus];			/* Cluster size */
	if (fs->csize == 0 || (fs->csize & (fs->csize - 1))) return FR_NO_FILESYSTEM;	/* (Must be power of 2) */

	fs->n_rootdir = ld_word(fs->win + BPB_RootEntCnt);	/* Number of root directory entries */
	if (fs->n_rootdir % (SS(fs) / SZDIRE)) return FR_NO_FILESYSTEM;	/* (Must be sector aligned) */

	tsect = ld_word(fs->win + BPB_TotSec16);		/* Number of sectors on the volume */
	if (tsect == 0) tsect = ld_dword(fs->win + BPB_TotSec32);

	nrsv = ld_word(fs->win + BPB_RsvdSecCnt);		/* Number of reserved sectors */
	if (nrsv == 0) return FR_NO_FILESYSTEM;			/* (Must not be 0) */

	/* Determine the FAT sub type */
	sysect = nrsv + fasize + fs->n_rootdir / (SS(fs) / SZDIRE);	/* RSV + FAT + DIR */
	if (tsect < sysect) return FR_NO_FILESYSTEM;		/* (Invalid volume size) */
	nclst = (tsect - sysect) / fs->csize;				/* Number of clusters */
	if (nclst == 0) return FR_NO_FILESYSTEM;			/* (Invalid volume size) */
	fmt = 0;
	if (nclst <= MAX_FAT32) fmt = FS_FAT32;
	if (nclst <= MAX_FAT16) fmt = FS_FAT16;
	if (nclst <= MAX_FAT12) fmt = FS_FAT12;
	if (fmt == 0) return FR_NO_FILESYSTEM;

	/* Boundaries and Limits */
	fs->n_fatent = nclst + 2;							/* Number of FAT entries */
	fs->volbase = bsect;								/* Volume start sector */
	fs->fatbase = bsect + nrsv; 						/* FAT start sector */
	fs->database = bsect + sysect;						/* Data start sector */
	if (fmt == FS_FAT32) {
		if (ld_word(fs->win + BPB_FSVer32) != 0) return FR_NO_FILESYSTEM;	/* (Must be FAT32 revision 0.0) */
		if (fs->n_rootdir != 0) return FR_NO_FILESYSTEM;	/* (BPB_RootEntCnt must be 0) */
		fs->dirbase = ld_dword(fs->win + BPB_RootClus32);	/* Root directory start cluster */
		szbfat = fs->n_fatent * 4;					/* (Needed FAT size) */
	} else {
		if (fs->n_rootdir == 0) return FR_NO_FILESYSTEM;	/* (BPB_RootEntCnt must not be 0) */
		fs->dirbase = fs->fatbase + fasize;			/* Root directory start sector */
		szbfat = (fmt == FS_FAT16) ?				/* (Needed FAT size) */
		fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
	}
	if (fs->fsize < (szbfat + (SS(fs) - 1)) / SS(fs)) return FR_NO_FILESYSTEM;	/* (BPB_FATSz must not be less than the size needed) */

#if !FF_FS_READONLY
	/* Get FSInfo if available */
	fs->last_clst = fs->free_clst = 0xFFFFFFFF;		/* Initialize cluster allocation information */
	fs->fsi_flag = 0x80;
#if (FF_FS_NOFSINFO & 3) != 3
	if (fmt == FS_FAT32				/* Allow to update FSInfo only if BPB_FSInfo32 == 1 */
		&& ld_word(fs->win + BPB_FSInfo32) == 1
		&& move_window(fs, bsect + 1) == FR_OK)
	{
		fs->fsi_flag = 0;
		if (ld_word(fs->win + BS_55AA) == 0xAA55	/* Load FSInfo data if available */
			&& ld_dword(fs->win + FSI_LeadSig) == 0x41615252
			&& ld_dword(fs->win + FSI_StrucSig) == 0x61417272)
		{
#if (FF_FS_NOFSINFO & 1) == 0
			fs->free_clst = ld_dword(fs->win + FSI_Free_Count);
#endif
#if (FF_FS_NOFSINFO & 2) == 0
			fs->last_clst = ld_dword(fs->win + FSI_Nxt_Free);
#endif
		}
	}
#endif	/* (FF_FS_NOFSINFO & 3) != 3 */
#endif	/* !FF_FS_READONLY */


	fs->fs_type = fmt;		/* FAT sub-type */
	fs->id = ++Fsid;		/* Volume mount ID */
#if FF_USE_LFN == 1
	fs->lfnbuf = LfnBuf;	/* Static LFN working buffer */
#endif
#if FF_FS_RPATH != 0
	fs->cdir = 0;			/* Initialize current directory */
#endif
#if FF_FS_LOCK != 0			/* Clear file lock semaphores */
	clear_lock(fs);
#endif
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Check if the file/directory object is valid or not                    */
/*-----------------------------------------------------------------------*/

static FRESULT validate (	/* Returns FR_OK or FR_INVALID_OBJECT */
	FFOBJID* obj,			/* Pointer to the FFOBJID, the 1st member in the FIL/DIR object, to check validity */
	FATFS** rfs				/* Pointer to pointer to the owner filesystem object to return */
)
{
	FRESULT res = FR_INVALID_OBJECT;


	if (obj && obj->fs && obj->fs->fs_type && obj->id == obj->fs->id) {	/* Test if the object is valid */
#if FF_FS_REENTRANT
		if (lock_fs(obj->fs)) {	/* Obtain the filesystem object */
			if (!(disk_status(obj->fs->pdrv) & STA_NOINIT)) { /* Test if the phsical drive is kept initialized */
				res = FR_OK;
			} else {
				unlock_fs(obj->fs, FR_OK);
			}
		} else {
			res = FR_TIMEOUT;
		}
#else
		if (!(disk_status(obj->fs->pdrv) & STA_NOINIT)) { /* Test if the phsical drive is kept initialized */
			res = FR_OK;
		}
#endif
	}
	*rfs = (res == FR_OK) ? obj->fs : 0;	/* Corresponding filesystem object */
	return res;
}


static
UINT get_clustinfo(FIL* fp,
	DWORD* fclust
)
{
	UINT count = 0;
	DWORD fsclust = 0, val;

	if (fp->obj.sclust != 0) {
		val = fp->obj.sclust;
		do {
			fsclust = val;
			val = get_fat(&fp->obj, fsclust);
			count++;
		} while ((val != 0x0FFFFFFF) && (val != 1));
	}
	*fclust = fsclust;
	return count;
}


/*---------------------------------------------------------------------------

   Public Functions (FatFs API)

----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/* Mount/Unmount a Logical Drive                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_mount (
	FATFS* fs,			/* Pointer to the filesystem object (NULL:unmount)*/
	const TCHAR* path,	/* Logical drive number to be mounted/unmounted */
	BYTE opt			/* Mode option 0:Do not mount (delayed mount), 1:Mount immediately */
)
{
	FATFS *cfs;
	int vol;
	FRESULT res;
	const TCHAR *rp = path;


	/* Get logical drive number */
	vol = get_ldnumber(&rp);
	if (vol < 0) return FR_INVALID_DRIVE;
	cfs = FatFs[vol];					/* Pointer to fs object */

	if (cfs) {
#if FF_FS_LOCK != 0
		clear_lock(cfs);
#endif
#if FF_FS_REENTRANT						/* Discard sync object of the current volume */
		if (!ff_del_syncobj(&cfs->sobj)) return FR_INT_ERR;
#endif
		cfs->fs_type = 0;				/* Clear old fs object */
	}

	if (fs) {
		fs->fs_type = 0;				/* Clear new fs object */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		fs->vir_flag = FS_PARENT;
		fs->parent_fs = fs;
		fs->vir_amount = 0xFFFFFFFF;
		fs->vir_avail = FS_VIRDISABLE;
#endif
#if FF_FS_REENTRANT						/* Create sync object for the new volume */
		if (!ff_cre_syncobj((BYTE)vol, &fs->sobj)) return FR_INT_ERR;
#endif
	}
	FatFs[vol] = fs;					/* Register new fs object */

	if (opt == 0) return FR_OK;			/* Do not mount now, it will be mounted later */

	res = find_volume(&path, &fs, 0);	/* Force mounted the volume */
	LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Open or Create a File                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_open (
	FIL* fp,			/* Pointer to the blank file object */
	const TCHAR* path,	/* Pointer to the file name */
	BYTE mode			/* Access mode and file open mode flags */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	FATFS *fs_bak;
#if !FF_FS_READONLY
	DWORD clst, cl, bcs;
	QWORD sc, dw;
	FSIZE_t ofs;
#endif
	DEF_NAMBUF


	if (!fp) return FR_INVALID_OBJECT;

	/* Get logical drive number */
	mode &= FF_FS_READONLY ? FA_READ : FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_CREATE_NEW | FA_OPEN_ALWAYS | FA_OPEN_APPEND | FA_SEEKEND;
	res = find_volume(&path, &fs, mode);
	fs_bak = fs;
	if (res == FR_OK) {
		dj.obj.fs = fs;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISCHILD(fs)) LEAVE_FF(fs_bak,FR_INVAILD_FATFS);
		if (ISVIRPART(fs)) {
			/* Check the virtual partition top directory, and match the virtual fs */
			res = follow_virentry(&dj.obj,path);
			if (res == FR_INT_ERR) LEAVE_FF(fs_bak,res);
			if (res == FR_OK)
			 	fs = dj.obj.fs;
			}
#endif
		INIT_NAMBUF(fs);
		res = follow_path(&dj, path);	/* Follow the file path */
#if !FF_FS_READONLY	/* Read/Write configuration */
		if (res == FR_OK) {
			if (dj.fn[NSFLAG] & NS_NONAME) {	/* Origin directory itself? */
				res = FR_INVALID_NAME;
			}
#if FF_FS_LOCK != 0
			else {
				res = chk_lock(&dj, (mode & ~FA_READ) ? 1 : 0);		/* Check if the file can be used */
			}
#endif
		}

		/* Create or Open a file */
		if (mode & (FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW)) {
			if (res != FR_OK) {					/* No file, create new */
				if ((res == FR_NO_FILE) && (mode & FA_OPEN_ALWAYS)) {		/* There is no file to open, create a new entry */
#if FF_FS_LOCK != 0
					res = enq_lock() ? dir_register(&dj) : FR_TOO_MANY_OPEN_FILES;
#else
					res = dir_register(&dj);
#endif
				}
				if (res == FR_OK)
					mode |= FA_CREATE_ALWAYS;		/* File is created */
			}
			else {								/* Any object with the same name is already existing */
				if (dj.obj.attr & (AM_RDO | AM_DIR)) {	/* Cannot overwrite it (R/O or DIR) */
					res = FR_IS_DIR;
				} else {
					if (mode & FA_CREATE_NEW) res = FR_EXIST;	/* Cannot create as new file */
				}
			}
			if (res == FR_OK && (mode & FA_CREATE_ALWAYS)) {	/* Truncate it if overwrite mode */
				dw = GET_FATTIME();

				/* Clean directory info */
				if (SYSTEM_TIME_ENABLE == time_status) {
					st_dword(dj.dir + DIR_CrtTime, dw);	/* Set created time */
					st_dword(dj.dir + DIR_ModTime, dw);	/* Set modified time */
				} else if (SYSTEM_TIME_DISABLE == time_status) {
					st_dword(dj.dir + DIR_CrtTime, 0);	/* Set created time as 0*/
					st_dword(dj.dir + DIR_ModTime, 0);	/* Set modified time as 0*/
				}
				dj.dir[DIR_Attr] = AM_ARC;		/* Reset attribute */
				cl = ld_clust(fs, dj.dir);		/* Get cluster chain */
				st_clust(fs, dj.dir, 0);		/* Reset file allocation info */
				st_dword(dj.dir + DIR_FileSize, 0);
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
				PARENTFS(fs)->wflag = 1;
#else
				fs->wflag = 1;
#endif
				if (cl != 0) {						/* Remove the cluster chain if exist */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
					dw = fs->winsect;
					res = remove_chain(&dj.obj, cl, 0);
					if (res == FR_OK) {
						res = move_window(fs, dw);
						fs->last_clst = cl - 1;		/* Reuse the cluster hole */
					}

#else
					dw = PARENTFS(fs)->winsect;
					res = remove_chain(&dj.obj, cl, 0);
					if (res == FR_OK) {
						res = move_window(fs, dw);
						if (ISVIRPART(fs) && ISCHILD(fs))
							fs->last_clst = cl - 1;    /* Reuse the cluster hole */
						PARENTFS(fs)->last_clst = cl -1;
					}
#endif
				}
			}
		}
		else {	/* Open an existing file */
			if (res == FR_OK) {					/* Following succeeded */
				if (dj.obj.attr & AM_DIR) {		/* It is a directory */
					res = FR_IS_DIR;
				} else {
					if ((mode & FA_WRITE) && (dj.obj.attr & AM_RDO)) {	/* R/O violation */
						res = FR_DENIED;
					}
				}
			}
		}
		if (res == FR_OK) {
			if (mode & FA_CREATE_ALWAYS) mode |= FA_MODIFIED;	/* Set file change flag if created or overwritten */
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			fp->dir_sect = PARENTFS(fs)->winsect;	/* Pointer to the directory entry */
#else
			fp->dir_sect = fs->winsect;
#endif
			fp->dir_ptr = dj.dir;
#if FF_FS_LOCK != 0
			fp->obj.lockid = inc_lock(&dj, (mode & ~FA_READ) ? 1 : 0);	/* Lock the file for this session */
			if (fp->obj.lockid == 0) res = FR_INT_ERR;
#endif
		}
#else		/* R/O configuration */
		if (res == FR_OK) {
			if (dj.fn[NSFLAG] & NS_NONAME) {	/* Is it origin directory itself? */
				res = FR_INVALID_NAME;
			} else {
				if (dj.obj.attr & AM_DIR) {		/* Is it a directory? */
					res = FR_NO_FILE;
				}
			}
		}
#endif

		if (res == FR_OK) {

			fp->obj.sclust = ld_clust(fs, dj.dir);		/* Get object allocation info */
			fp->obj.objsize = ld_dword(dj.dir + DIR_FileSize);
#if FF_USE_FASTSEEK
			fp->cltbl = 0;			/* Disable fast seek mode */
#endif
			fp->obj.fs = fs;	 	/* Validate the file object */
			fp->obj.id = fs->id;
			fp->flag = mode;		/* Set file access mode */
			fp->err = 0;			/* Clear error flag */
			fp->sect = 0;			/* Invalidate current data sector */
			fp->fptr = 0;			/* Set file pointer top of the file */
#if !FF_FS_READONLY
#if !FF_FS_TINY
			fp->buf = (BYTE*) ff_memalloc(SS(fs));
			if (fp->buf == NULL) res = FR_NOT_ENOUGH_CORE;
#endif
			if ((mode & FA_SEEKEND) && fp->obj.objsize > 0) {	/* Seek to end of file if FA_OPEN_APPEND is specified */
				fp->fptr = fp->obj.objsize;			/* Offset to seek */
				bcs = (DWORD)fs->csize * SS(fs);	/* Cluster size in byte */
				clst = fp->obj.sclust;				/* Follow the cluster chain */
				for (ofs = fp->obj.objsize; res == FR_OK && ofs > bcs; ofs -= bcs) {
					clst = get_fat(&fp->obj, clst);
					if (clst <= 1) res = FR_INT_ERR;
					if (clst == 0xFFFFFFFF) res = FR_DISK_ERR;
				}
				fp->clust = clst;
				if (res == FR_OK && ofs % SS(fs)) {	/* Fill sector buffer if not on the sector boundary */
					if ((sc = clst2sect(fs, clst)) == 0) {
						res = FR_INT_ERR;
					} else {
						fp->sect = sc + (DWORD)(ofs / SS(fs));
#if !FF_FS_TINY
						if (disk_read(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) res = FR_DISK_ERR;
#endif
					}
				}
			}
#endif
		}

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		/*  Scan the file cluster chain and check whether the virtual partition has been occuiped
		    more than two virtual partitions */
		if (res == FR_OK && (mode & ~FA_READ) && ISVIRPART(fs) &&
		    (ISCHILD(fs) || (ISPARENT(fs) && fs->st_clst != 0xFFFFFFFF && fs->ct_clst != 0xFFFFFFFF))) {
			clst = fp->obj.sclust;
			if (clst != 0) {
				while (1) {
					if (clst == 0xFFFFFFFF) {
						res = FR_DISK_ERR;
						break;
					}
					if (clst == 0x0FFFFFFF) {
						res = FR_OK;
						break;
					}
					if (clst < 2 || clst >= fs->n_fatent) {
						res = FR_INT_ERR;
						break;
					}
					if (clst < fs->st_clst || clst >= fs->st_clst + fs->ct_clst) {
						res = FR_INT_ERR;
						break;
					}
					clst = get_fat(&fp->obj, clst);
				}
			}

			if (res != FR_OK) {
				/* If the chain is occupied, Recycle the file lock ,pass out an error*/
				dec_lock(fp->obj.lockid);
			}
		}
#endif
		FREE_NAMBUF();
	}

	if (res != FR_OK) fp->obj.fs = 0;	/* Invalidate file object on error */

	LEAVE_FF(fs_bak, res);
}




/*-----------------------------------------------------------------------*/
/* Read File                                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_read (
	FIL* fp, 	/* Pointer to the file object */
	void* buff,	/* Pointer to data buffer */
	UINT btr,	/* Number of bytes to read */
	UINT* br	/* Pointer to number of bytes read */
)
{
	FRESULT res;
	FATFS *fs;
	QWORD sect;
	DWORD clst;
	FSIZE_t remain;
	UINT rcnt, cc, csect;
	BYTE *rbuff = (BYTE*)buff;
	UINT copy_ret;

	*br = 0;	/* Clear read byte counter */
	res = validate(&fp->obj, &fs);				/* Check validity of the file object */
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res);	/* Check validity */
	if (!(fp->flag & FA_READ)) LEAVE_FF(fs, FR_NO_EPERM);	/* Check access mode */
	remain = fp->obj.objsize - fp->fptr;
	if (btr > remain) btr = (UINT)remain;		/* Truncate btr by remaining bytes */

	for ( ;  btr;								/* Repeat until btr bytes read */
		btr -= rcnt, *br += rcnt, rbuff += rcnt, fp->fptr += rcnt) {
		if (fp->fptr % SS(fs) == 0) {			/* On the sector boundary? */
			csect = (UINT)(fp->fptr / SS(fs) & (fs->csize - 1));	/* Sector offset in the cluster */
			if (csect == 0) {					/* On the cluster boundary? */
				if (fp->fptr == 0) {			/* On the top of the file? */
					clst = fp->obj.sclust;		/* Follow cluster chain from the origin */
				} else {						/* Middle or end of the file */
#if FF_USE_FASTSEEK
					if (fp->cltbl) {
						clst = clmt_clust(fp, fp->fptr);	/* Get cluster# from the CLMT */
					} else
#endif
					{
						clst = get_fat(&fp->obj, fp->clust);	/* Follow cluster chain on the FAT */
					}
				}
				if (clst < 2) ABORT(fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
				fp->clust = clst;				/* Update current cluster */
			}
			sect = clst2sect(fs, fp->clust);	/* Get current sector */
			if (sect == 0) ABORT(fs, FR_INT_ERR);
			sect += csect;
			cc = btr / SS(fs);					/* When remaining bytes >= sector size, */
			if (cc > 0) {						/* Read maximum contiguous sectors directly */
				if (csect + cc > fs->csize) {	/* Clip at cluster boundary */
					cc = fs->csize - csect;
				}
				if (disk_read(fs->pdrv, rbuff, sect, cc) != RES_OK) ABORT(fs, FR_DISK_ERR);
#if !FF_FS_READONLY && FF_FS_MINIMIZE <= 2		/* Replace one of the read sectors with cached data if it contains a dirty sector */
#if FF_FS_TINY
				if (fs->wflag && fs->winsect - sect < cc) {
					copy_ret = LOS_CopyFromKernel(rbuff + ((fs->winsect - sect) * SS(fs)), SS(fs), fs->win, SS(fs));
					if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
				}
#else
				if ((fp->flag & FA_DIRTY) && fp->sect - sect < cc) {
					copy_ret = LOS_CopyFromKernel(rbuff + ((fp->sect - sect) * SS(fs)), SS(fs), fp->buf, SS(fs));
					if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
				}
#endif
#endif
				rcnt = SS(fs) * cc;				/* Number of bytes transferred */
				continue;
			}
#if !FF_FS_TINY
			if (fp->sect != sect) {			/* Load data sector if not in cache */
#if !FF_FS_READONLY
				if (fp->flag & FA_DIRTY) {		/* Write-back dirty sector cache */
					if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
					fp->flag &= (BYTE)~FA_DIRTY;
				}
#endif
				if (disk_read(fs->pdrv, fp->buf, sect, 1) != RES_OK)	ABORT(fs, FR_DISK_ERR);	/* Fill sector cache */
			}
#endif
			fp->sect = sect;
		}
		rcnt = SS(fs) - (UINT)fp->fptr % SS(fs);	/* Number of bytes left in the sector */
		if (rcnt > btr) rcnt = btr;					/* Clip it by btr if needed */
#if FF_FS_TINY
		if (move_window(fs, fp->sect) != FR_OK) ABORT(fs, FR_DISK_ERR);	/* Move sector window */

		copy_ret = LOS_CopyFromKernel(rbuff, rcnt, fs->win + fp->fptr % SS(fs), rcnt);
		if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
#else
		/* Extract partial sector */
		copy_ret = LOS_CopyFromKernel(rbuff, rcnt, fp->buf + fp->fptr % SS(fs), rcnt);
		if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
#endif
	}

	LEAVE_FF(fs, FR_OK);
}

#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Write File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_write (
	FIL* fp,			/* Pointer to the file object */
	const void* buff,	/* Pointer to the data to be written */
	UINT btw,			/* Number of bytes to write */
	UINT* bw			/* Pointer to number of bytes written */
)
{
	FRESULT res;
	FATFS *fs;
	QWORD sect;
	DWORD clst;
	UINT wcnt, cc, csect;
	const BYTE *wbuff = (const BYTE*)buff;
	UINT copy_ret;

	*bw = 0;	/* Clear write byte counter */
	res = validate(&fp->obj, &fs);			/* Check validity of the file object */
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res);	/* Check validity */
	if (!(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_NO_EPERM);	/* Check access mode */

	/* Check fptr wrap-around (file size cannot reach 4 GiB at FAT volume) */
	if ((DWORD)(fp->fptr + btw) < (DWORD)fp->fptr) {
		btw = (UINT)(0xFFFFFFFF - (DWORD)fp->fptr);
	}

	for ( ;  btw;							/* Repeat until all data written */
		btw -= wcnt, *bw += wcnt, wbuff += wcnt, fp->fptr += wcnt, fp->obj.objsize = (fp->fptr > fp->obj.objsize) ? fp->fptr : fp->obj.objsize) {
		if (fp->fptr % SS(fs) == 0) {		/* On the sector boundary? */
			csect = (UINT)(fp->fptr / SS(fs)) & (fs->csize - 1);	/* Sector offset in the cluster */
			if (csect == 0) {				/* On the cluster boundary? */
				if (fp->fptr == 0) {		/* On the top of the file? */
					clst = fp->obj.sclust;	/* Follow from the origin */
					if (clst == 0) {		/* If no cluster is allocated, */
						clst = create_chain(&fp->obj, 0);	/* create a new cluster chain */
					}
				} else {					/* On the middle or end of the file */
#if FF_USE_FASTSEEK
					if (fp->cltbl) {
						clst = clmt_clust(fp, fp->fptr);	/* Get cluster# from the CLMT */
					} else
#endif
					{
						clst = create_chain(&fp->obj, fp->clust);	/* Follow or stretch cluster chain on the FAT */
					}
				}
				if (clst == 0) break;		/* Could not allocate a new cluster (disk full) */
				if (clst == 1) ABORT(fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
				fp->clust = clst;			/* Update current cluster */
				if (fp->obj.sclust == 0) fp->obj.sclust = clst;	/* Set start cluster if the first write */
			}
#if FF_FS_TINY
			if (fs->winsect == fp->sect && sync_window(fs) != FR_OK) ABORT(fs, FR_DISK_ERR);	/* Write-back sector cache */
#else
			if (fp->flag & FA_DIRTY) {		/* Write-back sector cache */
				if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
				fp->flag &= (BYTE)~FA_DIRTY;
			}
#endif
			sect = clst2sect(fs, fp->clust);	/* Get current sector */
			if (sect == 0) ABORT(fs, FR_INT_ERR);
			sect += csect;
			cc = btw / SS(fs);				/* When remaining bytes >= sector size, */
			if (cc > 0) {					/* Write maximum contiguous sectors directly */
				if (csect + cc > fs->csize) {	/* Clip at cluster boundary */
					cc = fs->csize - csect;
				}
				if (disk_write(fs->pdrv, wbuff, sect, cc) != RES_OK) ABORT(fs, FR_DISK_ERR);
#if FF_FS_MINIMIZE <= 2
#if FF_FS_TINY
				if (fs->winsect - sect < cc) {	/* Refill sector cache if it gets invalidated by the direct write */
					copy_ret = LOS_CopyToKernel(fs->win, SS(fs), wbuff + ((fs->winsect - sect) * SS(fs)), SS(fs));
					if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
					fs->wflag = 0;
				}
#else
				if (fp->sect - sect < cc) { /* Refill sector cache if it gets invalidated by the direct write */
					copy_ret = LOS_CopyToKernel(fp->buf, SS(fs), wbuff + ((fp->sect - sect) * SS(fs)), SS(fs));
					if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
					fp->flag &= (BYTE)~FA_DIRTY;
				}
#endif
#endif
				wcnt = SS(fs) * cc;		/* Number of bytes transferred */
				continue;
			}
#if FF_FS_TINY
			if (fp->fptr >= fp->obj.objsize) {	/* Avoid silly cache filling on the growing edge */
				if (sync_window(fs) != FR_OK) ABORT(fs, FR_DISK_ERR);
				fs->winsect = sect;
			}
#else
			if (fp->sect != sect && 		/* Fill sector cache with file data */
				fp->fptr < fp->obj.objsize &&
				disk_read(fs->pdrv, fp->buf, sect, 1) != RES_OK) {
					ABORT(fs, FR_DISK_ERR);
			}
#endif
			fp->sect = sect;
		}
		wcnt = SS(fs) - (UINT)fp->fptr % SS(fs);	/* Number of bytes left in the sector */
		if (wcnt > btw) wcnt = btw;					/* Clip it by btw if needed */
#if FF_FS_TINY
		if (move_window(fs, fp->sect) != FR_OK) ABORT(fs, FR_DISK_ERR);	/* Move sector window */

		copy_ret = LOS_CopyToKernel(fs->win + fp->fptr % SS(fs), wcnt, wbuff, wcnt);
		if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
		fs->wflag = 1;
#else
		copy_ret = LOS_CopyToKernel(fp->buf + fp->fptr % SS(fs), wcnt, wbuff, wcnt);
		if (copy_ret != EOK) ABORT(fs, FR_INVALID_PARAMETER);
		fp->flag |= FA_DIRTY;
#endif

	}

	fp->flag |= FA_MODIFIED;				/* Set file change flag */

	LEAVE_FF(fs, FR_OK);
}

/*-----------------------------------------------------------------------*/
/* Synchronize the File                                                  */
/*-----------------------------------------------------------------------*/

FRESULT f_sync (
	FIL* fp		/* Pointer to the file object */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD tm;
	BYTE *dir;


	res = validate(&fp->obj, &fs);	/* Check validity of the file object */
	if (res == FR_OK) {
		if (fp->flag & FA_MODIFIED) {	/* Is there any change to the file? */
#if !FF_FS_TINY
			if (fp->flag & FA_DIRTY) {	/* Write-back cached data if needed */
				if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) LEAVE_FF(fs, FR_DISK_ERR);
				fp->flag &= (BYTE)~FA_DIRTY;
			}
#endif
			/* Update the directory entry */
			tm = GET_FATTIME();		/* Modified time */

			res = move_window(fs, fp->dir_sect);

			if (res == FR_OK) {
				dir = fp->dir_ptr;
				dir[DIR_Attr] |= AM_ARC;						/* Set archive attribute to indicate that the file has been changed */
				st_clust(fp->obj.fs, dir, fp->obj.sclust);		/* Update file allocation information  */
				st_dword(dir + DIR_FileSize, (DWORD)fp->obj.objsize);	/* Update file size */
				if (SYSTEM_TIME_ENABLE == time_status) {
					st_dword(dir + DIR_ModTime, tm);			/* Update modified time */
				} else if (SYSTEM_TIME_DISABLE == time_status) {
					st_dword(dir + DIR_ModTime, 0);				/* Update modified time */
				}
				st_word(dir + DIR_LstAccDate, 0);
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
				fs->wflag = 1;
#else
				PARENTFS(fs)->wflag = 1;
#endif

				res = sync_fs(fs);					/* Restore it to the directory */
				fp->flag &= (BYTE)~FA_MODIFIED;
			}
		}
	}

	LEAVE_FF(fs, res);
}

#endif /* !FF_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Close File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_close (
	FIL* fp		/* Pointer to the file object to be closed */
)
{
	FRESULT res;
	FATFS *fs;

#if !FF_FS_READONLY
	res = f_sync(fp);					/* Flush cached data */
	if (res == FR_OK || res == FR_DISK_ERR)
#endif
	{
		res = validate(&fp->obj, &fs);	/* Lock volume */
		if (res == FR_OK) {
#if FF_FS_LOCK != 0
			res = dec_lock(fp->obj.lockid);		/* Decrement file open counter */
			if (res == FR_OK) fp->obj.fs = 0;	/* Invalidate file object */
#else
			fp->obj.fs = 0;	/* Invalidate file object */
#endif
#if FF_FS_REENTRANT
			unlock_fs(fs, FR_OK);		/* Unlock volume */
#endif
		}
	}
	return res;
}




#if FF_FS_RPATH >= 1
/*-----------------------------------------------------------------------*/
/* Change Current Directory or Current Drive, Get Current Directory      */
/*-----------------------------------------------------------------------*/

FRESULT f_chdrive (
	const TCHAR* path		/* Drive number to set */
)
{
	int vol;


	/* Get logical drive number */
	vol = get_ldnumber(&path);
	if (vol < 0) return FR_INVALID_DRIVE;
	CurrVol = (BYTE)vol;	/* Set it as current volume */

	return FR_OK;
}



FRESULT f_chdir (
	const TCHAR* path	/* Pointer to the directory path */
)
{
#if FF_STR_VOLUME_ID == 2
	UINT i;
#endif
	FRESULT res;
	DIR dj;
	FATFS *fs;
	DEF_NAMBUF


	/* Get logical drive */
	res = find_volume(&path, &fs, 0);
	if (res == FR_OK) {
		dj.obj.fs = fs;
		INIT_NAMBUF(fs);
		res = follow_path(&dj, path);		/* Follow the path */
		if (res == FR_OK) {					/* Follow completed */
			if (dj.fn[NSFLAG] & NS_NONAME) {
				fs->cdir = dj.obj.sclust;	/* Is it the start directory itself? */
			} else {
				if (dj.obj.attr & AM_DIR) {	/* It is a sub-directory */
					fs->cdir = ld_clust(fs, dj.dir);	/* Sub-directory cluster */
				} else {
					res = FR_NO_PATH;		/* Reached but a file */
				}
			}
		}
		FREE_NAMBUF();
		if (res == FR_NO_FILE) res = FR_NO_PATH;
#if FF_STR_VOLUME_ID == 2	/* Also current drive is changed at Unix style volume ID */
		if (res == FR_OK) {
			for (i = FF_VOLUMES - 1; i && fs != FatFs[i]; i--) ;	/* Set current drive */
			CurrVol = (BYTE)i;
		}
#endif
	}

	LEAVE_FF(fs, res);
}


#if FF_FS_RPATH >= 2
FRESULT f_getcwd (
	TCHAR* buff,	/* Pointer to the directory path */
	UINT len		/* Size of buff in unit of TCHAR */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	UINT i, n;
	DWORD ccl;
	TCHAR *tp = buff;
#if FF_VOLUMES >= 2
	UINT vl;
#endif
#if FF_STR_VOLUME_ID
	const char *vp;
#endif
	FILINFO fno;
	DEF_NAMBUF


	/* Get logical drive */
	buff[0] = 0;	/* Set null string to get current volume */
	res = find_volume((const TCHAR**)&buff, &fs, 0);	/* Get current volume */
	if (res == FR_OK) {
		dj.obj.fs = fs;
		INIT_NAMBUF(fs);

		/* Follow parent directories and create the path */
		i = len;			/* Bottom of buffer (directory stack base) */

		dj.obj.sclust = fs->cdir;		/* Start to follow upper directory from current directory */
		while ((ccl = dj.obj.sclust) != 0) {	/* Repeat while current directory is a sub-directory */
			res = dir_sdi(&dj, 1 * SZDIRE);	/* Get parent directory */
			if (res != FR_OK) break;
			res = move_window(fs, dj.sect);
			if (res != FR_OK) break;
			dj.obj.sclust = ld_clust(fs, dj.dir);	/* Goto parent directory */
			res = dir_sdi(&dj, 0);
			if (res != FR_OK) break;
			do {							/* Find the entry links to the child directory */
				res = DIR_READ_FILE(&dj);
				if (res != FR_OK) break;
				if (ccl == ld_clust(fs, dj.dir)) break;	/* Found the entry */
				res = dir_next(&dj, 0);
			} while (res == FR_OK);
			if (res == FR_NO_FILE) res = FR_INT_ERR;/* It cannot be 'not found'. */
			if (res != FR_OK) break;
			get_fileinfo(&dj, &fno);		/* Get the directory name and push it to the buffer */
			for (n = 0; fno.fname[n]; n++) ;	/* Name length */
			if (i < n + 1) {	/* Insufficient space to store the path name? */
				res = FR_NOT_ENOUGH_CORE; break;
			}
			while (n) buff[--i] = fno.fname[--n];
			buff[--i] = '/';
		}
		if (res == FR_OK) {
			if (i == len) buff[--i] = '/';	/* Is it the root-directory? */
#if FF_VOLUMES >= 2			/* Put drive prefix */
			vl = 0;
#if FF_STR_VOLUME_ID >= 1	/* String volume ID */
			for (n = 0, vp = (const char*)VolumeStr[CurrVol]; vp[n]; n++) ;
			if (i >= n + 2) {
				if (FF_STR_VOLUME_ID == 2) *tp++ = (TCHAR)'/';
				for (vl = 0; vl < n; *tp++ = (TCHAR)vp[vl], vl++) ;
				if (FF_STR_VOLUME_ID == 1) *tp++ = (TCHAR)':';
				vl++;
			}
#else						/* Numeric volume ID */
			if (i >= 3) {
				*tp++ = (TCHAR)'0' + CurrVol;
				*tp++ = (TCHAR)':';
				vl = 2;
			}
#endif
			if (vl == 0) res = FR_NOT_ENOUGH_CORE;
#endif
			/* Add current directory path */
			if (res == FR_OK) {
				do *tp++ = buff[i++]; while (i < len);	/* Copy stacked path string */
			}
		}
		FREE_NAMBUF();
	}

	*tp = 0;
	LEAVE_FF(fs, res);
}

#endif /* FF_FS_RPATH >= 2 */
#endif /* FF_FS_RPATH >= 1 */



#if FF_FS_MINIMIZE <= 2
/*-----------------------------------------------------------------------*/
/* Seek File Read/Write Pointer                                          */
/*-----------------------------------------------------------------------*/

FRESULT f_lseek (
	FIL* fp,		/* Pointer to the file object */
	FSIZE_t ofs		/* File pointer from top of file */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD clst, bcs;
	QWORD nsect;
	FSIZE_t ifptr;
#if FF_USE_FASTSEEK
	DWORD cl, pcl, ncl, tcl, tlen, ulen, *tbl;
	QWORD dsc;
#endif

	res = validate(&fp->obj, &fs);		/* Check validity of the file object */
	if (res == FR_OK) res = (FRESULT)fp->err;
	if (res != FR_OK) LEAVE_FF(fs, res);

#if FF_USE_FASTSEEK
	if (fp->cltbl) {	/* Fast seek */
		if (ofs == CREATE_LINKMAP) {	/* Create CLMT */
			tbl = fp->cltbl;
			tlen = *tbl++; ulen = 2;	/* Given table size and required table size */
			cl = fp->obj.sclust;		/* Origin of the chain */
			if (cl != 0) {
				do {
					/* Get a fragment */
					tcl = cl; ncl = 0; ulen += 2;	/* Top, length and used items */
					do {
						pcl = cl; ncl++;
						cl = get_fat(&fp->obj, cl);
						if (cl <= 1) ABORT(fs, FR_INT_ERR);
						if (cl == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
					} while (cl == pcl + 1);
					if (ulen <= tlen) {		/* Store the length and top of the fragment */
						*tbl++ = ncl; *tbl++ = tcl;
					}
				} while (cl < fs->n_fatent);	/* Repeat until end of chain */
			}
			*fp->cltbl = ulen;	/* Number of items used */
			if (ulen <= tlen) {
				*tbl = 0;		/* Terminate table */
			} else {
				res = FR_NOT_ENOUGH_CORE;	/* Given table size is smaller than required */
			}
		} else {						/* Fast seek */
			if (ofs > fp->obj.objsize) ofs = fp->obj.objsize;	/* Clip offset at the file size */
			fp->fptr = ofs;				/* Set file pointer */
			if (ofs > 0) {
				fp->clust = clmt_clust(fp, ofs - 1);
				dsc = clst2sect(fs, fp->clust);
				if (dsc == 0) ABORT(fs, FR_INT_ERR);
				dsc += (DWORD)((ofs - 1) / SS(fs)) & (fs->csize - 1);
				if (fp->fptr % SS(fs) && dsc != fp->sect) {	/* Refill sector cache if needed */
#if !FF_FS_TINY
#if !FF_FS_READONLY
					if (fp->flag & FA_DIRTY) {		/* Write-back dirty sector cache */
						if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
						fp->flag &= (BYTE)~FA_DIRTY;
					}
#endif
					if (disk_read(fs->pdrv, fp->buf, dsc, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);	/* Load current sector */
#endif
					fp->sect = dsc;
				}
			}
		}
	} else
#endif

	/* Normal Seek */
	{
		if (ofs > fp->obj.objsize && (FF_FS_READONLY || !(fp->flag & FA_WRITE))) {	/* In read-only mode, clip offset with the file size */
			ofs = fp->obj.objsize;
		}
		ifptr = fp->fptr;
		fp->fptr = nsect = 0;
		if (ofs > 0) {
			bcs = (DWORD)fs->csize * SS(fs);	/* Cluster size (byte) */
			if (ifptr > 0 &&
				(ofs - 1) / bcs >= (ifptr - 1) / bcs) {	/* When seek to same or following cluster, */
				fp->fptr = (ifptr - 1) & ~(FSIZE_t)(bcs - 1);	/* start from the current cluster */
				ofs -= fp->fptr;
				clst = fp->clust;
			} else {									/* When seek to back cluster, */
				clst = fp->obj.sclust;					/* start from the first cluster */
#if !FF_FS_READONLY
				if (clst == 0) {						/* If no cluster chain, create a new chain */
					clst = create_chain(&fp->obj, 0);
					if (clst == 1) ABORT(fs, FR_INT_ERR);
					if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
					fp->obj.sclust = clst;
				}
#endif
				fp->clust = clst;
			}
			if (clst != 0) {
				while (ofs > bcs) {						/* Cluster following loop */
					ofs -= bcs; fp->fptr += bcs;
#if !FF_FS_READONLY
					if (fp->flag & FA_WRITE) {			/* Check if in write mode or not */
						clst = create_chain(&fp->obj, clst);	/* Follow chain with forceed stretch */
						if (clst == 0) {				/* Clip file size in case of disk full */
							ofs = 0; break;
						}
					} else
#endif
					{
						clst = get_fat(&fp->obj, clst);	/* Follow cluster chain if not in write mode */
					}
					if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
					if (clst <= 1 || clst >= fs->n_fatent) ABORT(fs, FR_INT_ERR);
					fp->clust = clst;
				}
				fp->fptr += ofs;
				if (ofs % SS(fs)) {
					nsect = clst2sect(fs, clst);	/* Current sector */
					if (nsect == 0) ABORT(fs, FR_INT_ERR);
					nsect += (DWORD)(ofs / SS(fs));
				}
			}
		}
		if (!FF_FS_READONLY && fp->fptr > fp->obj.objsize) {	/* Set file change flag if the file size is extended */
			fp->obj.objsize = fp->fptr;
			fp->flag |= FA_MODIFIED;
		}
		if (fp->fptr % SS(fs) && nsect != fp->sect) {	/* Fill sector cache if needed */
#if !FF_FS_TINY
#if !FF_FS_READONLY
			if (fp->flag & FA_DIRTY) {			/* Write-back dirty sector cache */
				if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
				fp->flag &= (BYTE)~FA_DIRTY;
			}
#endif
			if (disk_read(fs->pdrv, fp->buf, nsect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);	/* Fill sector cache */
#endif
			fp->sect = nsect;
		}
	}

	LEAVE_FF(fs, res);
}



#if FF_FS_MINIMIZE <= 1
/*-----------------------------------------------------------------------*/
/* Create a Directory Object                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_opendir (
	DIR* dp,			/* Pointer to directory object to create */
	const TCHAR* path	/* Pointer to the directory path */
)
{
	FRESULT res;
	FATFS *fs;
	DEF_NAMBUF


	if (!dp) return FR_INVALID_OBJECT;

	/* Get logical drive */
	res = find_volume(&path, &fs, 0);
	if (res == FR_OK) {
		dp->obj.fs = fs;
		INIT_NAMBUF(fs);
		res = follow_path(dp, path);			/* Follow the path to the directory */
		if (res == FR_OK) {						/* Follow completed */
			if (!(dp->fn[NSFLAG] & NS_NONAME)) {	/* It is not the origin directory itself */
				if (dp->obj.attr & AM_DIR) {		/* This object is a sub-directory */
					dp->obj.sclust = ld_clust(fs, dp->dir);		/* Get object allocation info */
				} else { 						/* This object is a file */
					res = FR_NO_DIR;
				}
			}
			if (res == FR_OK) {
				dp->obj.id = fs->id;
				res = dir_sdi(dp, 0);			/* Rewind directory */
#if FF_FS_LOCK != 0
				if (res == FR_OK) {
					if (dp->obj.sclust != 0) {
						dp->obj.lockid = inc_lock(dp, 0);	/* Lock the sub directory */
						if (!dp->obj.lockid) res = FR_TOO_MANY_OPEN_FILES;
					} else {
						dp->obj.lockid = 0;	/* Root directory need not to be locked */
					}
				}
#endif
			}
		}
		FREE_NAMBUF();
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}
	if (res != FR_OK) dp->obj.fs = 0;		/* Invalidate the directory object if function faild */

	LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Close Directory                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_closedir (
	DIR *dp		/* Pointer to the directory object to be closed */
)
{
	FRESULT res;
	FATFS *fs;


	res = validate(&dp->obj, &fs);	/* Check validity of the file object */
	if (res == FR_OK) {
#if FF_FS_LOCK != 0
		if (dp->obj.lockid) res = dec_lock(dp->obj.lockid);	/* Decrement sub-directory open counter */
		if (res == FR_OK) dp->obj.fs = 0;	/* Invalidate directory object */
#else
		dp->obj.fs = 0;	/* Invalidate directory object */
#endif
#if FF_FS_REENTRANT
		unlock_fs(fs, FR_OK);		/* Unlock volume */
#endif
	}
	return res;
}




/*-----------------------------------------------------------------------*/
/* Read Directory Entries in Sequence                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_readdir (
	DIR* dp,			/* Pointer to the open directory object */
	FILINFO* fno		/* Pointer to file information to return */
)
{
	FRESULT res;
	FATFS *fs;
	DEF_NAMBUF


	res = validate(&dp->obj, &fs);	/* Check validity of the directory object */
	if (res == FR_OK) {
		if (!fno) {
			res = dir_sdi(dp, 0);			/* Rewind the directory object */
		} else {
			INIT_NAMBUF(fs);
			res = DIR_READ_FILE(dp);		/* Read an item */
			if (res == FR_NO_FILE) res = FR_OK;	/* Ignore end of directory */
			if (res == FR_OK) {				/* A valid entry is found */
				get_fileinfo(dp, fno);		/* Get the object information */
				res = dir_next(dp, 0);		/* Increment index for next */
				if (res == FR_NO_FILE) res = FR_OK;	/* Ignore end of directory now */
			}
			FREE_NAMBUF();
		}
	}
	LEAVE_FF(fs, res);
}



#if FF_USE_FIND
/*-----------------------------------------------------------------------*/
/* Find Next File                                                        */
/*-----------------------------------------------------------------------*/

FRESULT f_findnext (
	DIR* dp,		/* Pointer to the open directory object */
	FILINFO* fno	/* Pointer to the file information structure */
)
{
	FRESULT res;


	for (;;) {
		res = f_readdir(dp, fno);		/* Get a directory item */
		if (res != FR_OK || !fno || !fno->fname[0]) break;	/* Terminate if any error or end of directory */
		if (pattern_matching(dp->pat, fno->fname, 0, 0)) break;		/* Test for the file name */
#if FF_USE_LFN && FF_USE_FIND == 2
		if (pattern_matching(dp->pat, fno->altname, 0, 0)) break;	/* Test for alternative name if exist */
#endif
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Find First File                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_findfirst (
	DIR* dp,				/* Pointer to the blank directory object */
	FILINFO* fno,			/* Pointer to the file information structure */
	const TCHAR* path,		/* Pointer to the directory to open */
	const TCHAR* pattern	/* Pointer to the matching pattern */
)
{
	FRESULT res;


	dp->pat = pattern;		/* Save pointer to pattern string */
	res = f_opendir(dp, path);		/* Open the target directory */
	if (res == FR_OK) {
		res = f_findnext(dp, fno);	/* Find the first item */
	}
	return res;
}

#endif	/* FF_USE_FIND */



#if FF_FS_MINIMIZE == 0
/*-----------------------------------------------------------------------*/
/* Get File Status                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_stat (
	const TCHAR* path,	/* Pointer to the file path */
	FILINFO* fno		/* Pointer to file information to return */
)
{
	FRESULT res;
	DIR dj;
	DEF_NAMBUF


	/* Get logical drive */
	res = find_volume(&path, &dj.obj.fs, 0);
	if (res == FR_OK) {
		INIT_NAMBUF(dj.obj.fs);
		res = follow_path(&dj, path);	/* Follow the file path */
		if (res == FR_OK) {				/* Follow completed */
			if (dj.fn[NSFLAG] & NS_NONAME) {	/* It is origin directory */
				res = FR_INVALID_NAME;
			} else {							/* Found an object */
				if (fno) get_fileinfo(&dj, fno);
			}
		}
		FREE_NAMBUF();
	}

	LEAVE_FF(dj.obj.fs, res);
}



#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Get Number of Free Clusters                                           */
/*-----------------------------------------------------------------------*/

FRESULT f_getfree (
	const TCHAR* path,	/* Logical drive number */
	DWORD* nclst,		/* Pointer to a variable to return number of free clusters */
	FATFS** fatfs		/* Pointer to return pointer to corresponding filesystem object */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD nfree, clst, stat;
	QWORD sect;
	UINT i;
	FFOBJID obj;


	/* Get logical drive */
	res = find_volume(&path, &fs, 0);
	if (res == FR_OK) {
		*fatfs = fs;				/* Return ptr to the fs object */
		/* If free_clst is valid, return it without full FAT scan */
		if (fs->free_clst <= fs->n_fatent - 2) {
			*nclst = fs->free_clst;
		} else {
			/* Scan FAT to obtain number of free clusters */
			nfree = 0;
			if (fs->fs_type == FS_FAT12) {	/* FAT12: Scan bit field FAT entries */
				clst = 2; obj.fs = fs;
				do {
					stat = get_fat(&obj, clst);
					if (stat == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
					if (stat == 1) { res = FR_INT_ERR; break; }
					if (stat == 0) nfree++;
				} while (++clst < fs->n_fatent);
			} else {
				/* FAT16/32: Scan WORD/DWORD FAT entries */
				clst = fs->n_fatent;	/* Number of entries */
				sect = fs->fatbase;		/* Top of the FAT */
				i = 0;					/* Offset in the sector */
				do {	/* Counts numbuer of entries with zero in the FAT */
					if (i == 0) {
						res = move_window(fs, sect++);
						if (res != FR_OK) break;
					}
					if (fs->fs_type == FS_FAT16) {
						if (ld_word(fs->win + i) == 0) nfree++;
						i += 2;
					} else {
						if ((ld_dword(fs->win + i) & 0x0FFFFFFF) == 0) nfree++;
						i += 4;
					}
					i %= SS(fs);
				} while (--clst);
			}
			*nclst = nfree;			/* Return the free clusters */
			fs->free_clst = nfree;	/* Now free_clst is valid */
			fs->fsi_flag |= 1;		/* FAT32: FSInfo is to be updated */
		}
	}

	LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Truncate File                                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_getclustinfo(FIL* fp,
	DWORD* fclust,
	DWORD* fcount
)
{
	UINT count = 0;
	FATFS *fs;
	FRESULT ret;
	ret = validate(&fp->obj,&fs);
	if (ret != FR_OK) LEAVE_FF(fs,ret);

	count = get_clustinfo(fp, fclust);
	if (count == 0xFFFFFFFF)
		LEAVE_FF(fs,FR_DENIED);

	*fcount = count;
	LEAVE_FF(fs,FR_OK);
}

FRESULT f_truncate (
	FIL* fp,		/* Pointer to the file object */
	FSIZE_t length
)
{
	FRESULT res;
	FATFS *fs;
	DWORD n, tcl, val, count, fclust = 0;

	res = validate(&fp->obj, &fs);	/* Check validity of the file object */
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res);
	if (!(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_NO_EPERM);	/* Check access mode */

	if (fp->fptr <= fp->obj.objsize) {	/* Process when fptr is not on the eof */
		if (fp->fptr == 0 && length == 0) {	/* When set file size to zero, remove entire cluster chain */
			res = remove_chain(&fp->obj, fp->obj.sclust, 0);
			fp->obj.sclust = 0;
		} else {	/* When truncate a part of the file, remove remaining clusters */
			n = (DWORD)fs->csize * SS(fs);	/* Cluster size */
			tcl = (DWORD)(length / n) + ((length & (n - 1)) ? 1 : 0);	/* Number of clusters required */
			val = fp->obj.sclust;
			count = 0;
			do {
				fclust = val;
				val = get_fat(&fp->obj, fclust);
				count ++;
				if (count == tcl)
					break;
			} while ((val != 0x0FFFFFFF) && (val != 1) && (val != 0xFFFFFFFF));

			res = FR_OK;
			if (val == 0xFFFFFFFF) res = FR_DISK_ERR;
			if (val == 1) res = FR_INT_ERR;
			if (res == FR_OK && val < fs->n_fatent) {
				res = remove_chain(&fp->obj, val, fclust);
			}
		}

		if (res == FR_OK) {
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			fs->last_clst = fclust;
#else
			if (ISVIRPART(fs) && ISCHILD(fs))
				fs->last_clst = fclust;
			PARENTFS(fs)->last_clst = fclust;
#endif
			fp->obj.objsize = length;	/* Set file size to length */
			if (fp->fptr > length) {
				fp->fptr = length;
				fp->clust = fclust;
			}
		}
		fp->flag |= FA_MODIFIED;
#if !FF_FS_TINY
		if (res == FR_OK && (fp->flag & FA_DIRTY)) {
			if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) {
				res = FR_DISK_ERR;
			} else {
				fp->flag &= (BYTE)~FA_DIRTY;
			}
		}
#endif
		if (res != FR_OK) ABORT(fs, res);
	}

	LEAVE_FF(fs, res);
}




/*-----------------------------------------------------------------------*/
/* Delete a File/Directory                                               */
/*-----------------------------------------------------------------------*/

FRESULT f_unlink (
	const TCHAR* path		/* Pointer to the file or directory path */
)
{
	FRESULT res;
	DIR dj, sdj;
	DWORD dclst = 0;
	FATFS *fs;
	FATFS *fs_bak;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	DWORD rtclst = 0;
	DWORD st_bak = 0;
#endif
	DEF_NAMBUF


	/* Get logical drive */
	res = find_volume(&path, &fs, FA_WRITE);
	dj.obj.fs = fs;
	fs_bak = fs;
	if (res == FR_OK) {
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISCHILD(fs)) LEAVE_FF(fs_bak,FR_INVAILD_FATFS);
		if (ISVIRPART(fs)) {
			/* Check the virtual partition top directory, and match the virtual fs */
			res = follow_virentry(&dj.obj,path);
			if (res == FR_INT_ERR) LEAVE_FF(fs_bak,res);
			if (res == FR_OK)
				fs = dj.obj.fs;
		}
#endif
		INIT_NAMBUF(fs);
		res = follow_path(&dj, path);		/* Follow the file path */
		if (FF_FS_RPATH && res == FR_OK && (dj.fn[NSFLAG] & NS_DOT)) {
			res = FR_INVALID_NAME;			/* Cannot remove dot entry */
		}
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (res == FR_OK && ISVIRPART(fs)) {
			dj.atrootdir = 0;rtclst = 2;
			st_bak = PARENTFS(dj.obj.fs)->winsect;
			/* Follow the root directory cluster chain */
			for (;;) {
				if (rtclst == 0xFFFFFFFF) LEAVE_FF(fs_bak,FR_DISK_ERR);
				if (rtclst == 0x0FFFFFFF) break;
				if (rtclst < 2 || rtclst >= fs->n_fatent) LEAVE_FF(fs_bak,FR_INT_ERR);
				if (rtclst == 0 || rtclst == 1) LEAVE_FF(fs_bak,FR_INT_ERR);
				/* If current dirent is on rootdir clust chain */
				if (dj.clust == rtclst) {
					/* Set a flag */
					dj.atrootdir = 1;
					break;
				}
				rtclst = get_fat(&(dj.obj),rtclst);
			}
			/* If current item is on rootdir clust chain */
			if (dj.atrootdir == 1) {
				if (ISCHILD(fs)) {
					/* The FATFS is child object already, that means the operation is trying to delete the virtual partition directory */
					LEAVE_FF(fs_bak,FR_DENIED);
				}
			}
			res = move_window(dj.obj.fs,st_bak);
		}
#endif

#if FF_FS_LOCK != 0
		if (res == FR_OK) res = chk_lock(&dj, 2);	/* Check if it is an open object */
#endif
		if (res == FR_OK) {					/* The object is accessible */
			if (dj.fn[NSFLAG] & NS_NONAME) {
				res = FR_INVALID_NAME;		/* Cannot remove the origin directory */
			} else {
				if (dj.obj.attr & AM_RDO) {
					res = FR_DENIED;		/* Cannot remove R/O object */
				}
			}
			if (res == FR_OK) {
				dclst = ld_clust(fs, dj.dir);
				if (dj.obj.attr & AM_DIR) {		/* Is it a sub-directory? */
#if FF_FS_RPATH != 0
					if (dclst == fs->cdir) {	/* Is it the current directory? */
						res = FR_DENIED;
					} else
#endif
					{
						sdj.obj.fs = fs;			/* Open the sub-directory */
						sdj.obj.sclust = dclst;
						res = dir_sdi(&sdj, 0);
						if (res == FR_OK) {
							res = DIR_READ_FILE(&sdj);					/* Test if the directory is empty */
							if (res == FR_OK) res = FR_NO_EMPTY_DIR;	/* Not empty? */
							if (res == FR_NO_FILE) res = FR_OK;			/* Empty? */
						}
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&dj);		/* Remove the directory entry */
				if (res == FR_OK && dclst) {	/* Remove the cluster chain if exist */
					res = remove_chain(&dj.obj, dclst, 0);
				}
				if (res == FR_OK) res = sync_fs(fs);
			}
		}
		FREE_NAMBUF();
	}

	LEAVE_FF(fs_bak, res);
}




/*-----------------------------------------------------------------------*/
/* Create a Directory                                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_mkdir (
	const TCHAR* path		/* Pointer to the directory path */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	FATFS *fs_bak;
	BYTE *dir;
	UINT n;
	DWORD dcl, pcl, tm;
	QWORD dsc;
	FFOBJID sobj;
	DEF_NAMBUF


	/* Get logical drive */
	res = find_volume(&path, &fs, FA_WRITE);
	fs_bak = fs;
	dj.obj.fs = fs;
	dj.obj.sclust = 0;
	if (res == FR_OK) {
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISCHILD(fs)) LEAVE_FF(fs_bak,FR_INVAILD_FATFS);
		if (ISVIRPART(fs)) {
			/* Check the virtual partition top directory, and match the virtual fs */
			res = follow_virentry(&dj.obj,path);
			if (res == FR_INT_ERR) LEAVE_FF(fs_bak,res);
			if (res == FR_OK)
				fs = dj.obj.fs;
		}
#endif
		INIT_NAMBUF(fs);
		res = follow_path(&dj, path);			/* Follow the file path */
		if (res == FR_OK) res = FR_EXIST;		/* Name collision? */
		if (FF_FS_RPATH && res == FR_NO_FILE && (dj.fn[NSFLAG] & NS_DOT)) {	/* Invalid name? */
			res = FR_INVALID_NAME;
		}
		if (res == FR_NO_FILE) {				/* It is clear to create a new directory */
			sobj.fs = fs;						/* New object id to create a new chain */
			dcl = create_chain(&sobj, 0);		/* Allocate a cluster for the new directory */
			res = FR_OK;
			if (dcl == 0) res = FR_NO_SPACE_LEFT;	/* No space to allocate a new cluster */
			if (dcl == 1) res = FR_INT_ERR;			/* Any insanity? */
			if (dcl == 0xFFFFFFFF) res = FR_DISK_ERR;	/* Disk error? */
			if (res == FR_OK) res = sync_window(fs);	/* Flush FAT */
			tm = GET_FATTIME();
			if (res == FR_OK) {					/* Initialize the new directory table */
				dsc = clst2sect(fs, dcl);
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
				dir = fs->win;
#else
				dir = PARENTFS(fs)->win;
#endif
				mem_set(dir, 0, SS(fs));
				mem_set(dir + DIR_Name, ' ', 11);	/* Create "." entry */
				dir[DIR_Name] = '.';
				dir[DIR_Attr] = AM_DIR;
				if (SYSTEM_TIME_ENABLE == time_status) {
					st_dword(dir + DIR_ModTime, tm);
				} else if (SYSTEM_TIME_DISABLE == time_status) {
					st_dword(dir + DIR_ModTime, 0);
				}
				st_clust(fs, dir, dcl);
				mem_cpy(dir + SZDIRE, dir, SZDIRE);	/* Create ".." entry */
				dir[SZDIRE + 1] = '.'; pcl = dj.obj.sclust;
				if (fs->fs_type == FS_FAT32 && pcl == fs->dirbase) pcl = 0;
				st_clust(fs, dir + SZDIRE, pcl);

				for (n = fs->csize; n; n--) {	/* Write dot entries and clear following sectors */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
					fs->winsect = dsc++;
					fs->wflag = 1;
					res = sync_window(fs);
					if (res != FR_OK) break;
					mem_set(dir, 0, SS(fs));
#else
					PARENTFS(fs)->winsect = dsc++;
					PARENTFS(fs)->wflag = 1;
					res = sync_window(fs);
					if (res != FR_OK) break;
					mem_set(dir, 0, SS(fs));
#endif
				}
			}
			if (res == FR_OK) {
				res = dir_register(&dj);	/* Register the object to the directoy */
			}
			if (res == FR_OK) {
				dir = dj.dir;
				if (SYSTEM_TIME_ENABLE == time_status) {
					st_dword(dir + DIR_ModTime, tm);	/* Created time */
				}
				else if (SYSTEM_TIME_DISABLE == time_status)
				{
					st_dword(dir + DIR_ModTime, 0);		/* Created time */
				}
				st_clust(fs, dir, dcl);		/* Table start cluster */
				dir[DIR_Attr] = AM_DIR;		/* Attribute */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
				fs->wflag = 1;
#else
				PARENTFS(fs)->wflag = 1;
#endif
				if (res == FR_OK) {
					res = sync_fs(fs);
				}
			} else {
				remove_chain(&dj.obj, dcl, 0);	/* Could not register, remove cluster chain */
			}
		}
		FREE_NAMBUF();
	}
	LEAVE_FF(fs_bak, res);
}

/*-----------------------------------------------------------------------*/
/* Rename a File/Directory                                               */
/*-----------------------------------------------------------------------*/

FRESULT f_rename (
	const TCHAR* path_old,	/* Pointer to the object name to be renamed */
	const TCHAR* path_new	/* Pointer to the new name */
)
{
	FRESULT res;
	DIR djo, djn;
	FATFS *fs;
	FATFS *fs_bak;
	BYTE buf[SZDIRE], *dir;
	QWORD dw;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	DWORD rtclst = 0;
	DWORD st_bak = 0;
#endif

	DEF_NAMBUF

	get_ldnumber(&path_new);						/* Snip the drive number of new name off */
	res = find_volume(&path_old, &fs, FA_WRITE);	/* Get logical drive of the old object */
	fs_bak = fs;
	if (res == FR_OK) {
		djo.obj.fs = fs;
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISCHILD(fs)) LEAVE_FF(fs,FR_INVAILD_FATFS);
		if (ISVIRPART(fs)) {
			/* Check the virtual partition top directory, and match the virtual fs */
			res = follow_virentry(&djo.obj,path_old);
			if (res == FR_INT_ERR) LEAVE_FF(fs_bak,res);
			if (res == FR_OK)
				fs = djo.obj.fs;
		}
#endif
		INIT_NAMBUF(fs);
		res = follow_path(&djo, path_old);		/* Check old object */
		if (res == FR_OK && (djo.fn[NSFLAG] & (NS_DOT | NS_NONAME))) res = FR_INVALID_NAME;	/* Check validity of name */
#if FF_FS_LOCK != 0
		if (res == FR_OK) {
			res = chk_lock(&djo, 2);
		}
#endif
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (res == FR_OK && ISVIRPART(fs)) {
			djo.atrootdir = 0;rtclst = 2;
			st_bak = PARENTFS(djo.obj.fs)->winsect;
			/* Follow the root directory cluster chain */
			for (;;) {
				if (rtclst == 0xFFFFFFFF) LEAVE_FF(fs_bak,FR_DISK_ERR);
				if (rtclst == 0x0FFFFFFF) break;
				if (rtclst < 2 || rtclst >= fs->n_fatent) LEAVE_FF(fs_bak,FR_INT_ERR);
				if (rtclst == 0 || rtclst == 1) LEAVE_FF(fs_bak,FR_INT_ERR);
				/* If current dirent is on rootdir clust chain */
				if (djo.clust == rtclst) {
					/* Set a flag */
					djo.atrootdir = 1;
				}
				rtclst = get_fat(&(djo.obj),rtclst);
			}
			/* If current item is on rootdir clust chain */
			if (djo.atrootdir == 1) {
				if (ISCHILD(fs)) {
					/* The FATFS is child object already, that means the operation is trying to delete the virtual partition directory */
					LEAVE_FF(fs_bak,FR_DENIED);
				}
			}
			res = move_window(djo.obj.fs,st_bak);
		}
#endif
		if (res == FR_OK) {		/* Object to be renamed is found */
			/* At FAT/FAT32 volume */
			mem_cpy(buf, djo.dir, SZDIRE);		/* Save directory entry of the object */
			mem_cpy(&djn, &djo, sizeof (DIR));	/* Duplicate the directory object */
			res = follow_path(&djn, path_new);	/* Make sure if new object name is not in use */
			if (res == FR_OK) {				/* Is new name already in use by any other object? */
				res = FR_EXIST;
			}
			if (res == FR_NO_FILE) { 			/* It is a valid path and no name collision */
				res = dir_register(&djn);		/* Register the new entry */
				if (res == FR_OK) {
					dir = djn.dir;				/* Copy information about object except name */
					mem_cpy(dir + 13, buf + 13, SZDIRE - 13);
					dir[DIR_Attr] = buf[DIR_Attr];
					if (!(dir[DIR_Attr] & AM_DIR)) dir[DIR_Attr] |= AM_ARC;	/* Set archive attribute if it is a file */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
					fs->wflag = 1;
#else
					PARENTFS(fs)->wflag = 1;
#endif
					if ((dir[DIR_Attr] & AM_DIR) && djo.obj.sclust != djn.obj.sclust) {	/* Update .. entry in the sub-directory if needed */
						dw = clst2sect(fs, ld_clust(fs, dir));
						if (!dw) {
							res = FR_INT_ERR;
						} else {
/* Start of critical section where an interruption can cause a cross-link */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
							res = move_window(fs, dw);
							dir = fs->win + SZDIRE * 1;	/* Ptr to .. entry */
							if (res == FR_OK && dir[1] == '.') {
								st_clust(fs, dir, djn.obj.sclust);
							fs->wflag = 1;
#else
							res = move_window(fs, dw);
							dir = PARENTFS(fs)->win + SZDIRE * 1;	/* Ptr to .. entry */
							if (res == FR_OK && dir[1] == '.') {
								st_clust(fs, dir, djn.obj.sclust);
								PARENTFS(fs)->wflag = 1;
#endif
							}
						}
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&djo);		/* Remove old entry */
				if (res == FR_OK) {
					res = sync_fs(fs);
				}
			}
/* End of the critical section */
		}
		FREE_NAMBUF();
	}

	LEAVE_FF(fs_bak, res);
}

#endif /* !FF_FS_READONLY */
#endif /* FF_FS_MINIMIZE == 0 */
#endif /* FF_FS_MINIMIZE <= 1 */
#endif /* FF_FS_MINIMIZE <= 2 */



#if FF_USE_CHMOD && !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Change Attribute                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_chmod (
	const TCHAR* path,	/* Pointer to the file path */
	BYTE attr,			/* Attribute bits */
	BYTE mask			/* Attribute mask to change */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	FATFS *fs_bak;
	DEF_NAMBUF


	res = find_volume(&path, &fs, FA_WRITE);	/* Get logical drive */
	dj.obj.fs = fs;
	fs_bak = fs;
	if (res == FR_OK) {
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		if (ISCHILD(fs)) LEAVE_FF(fs_bak,FR_INVAILD_FATFS);
		if (ISVIRPART(fs)) {
			/* Check the virtual partition top directory, and match the virtual fs */
			res = follow_virentry(&dj.obj,path);
			if (res == FR_INT_ERR) LEAVE_FF(fs_bak,res);
			if (res == FR_OK)
				fs = dj.obj.fs;
		}
#endif
		INIT_NAMBUF(fs);
		res = follow_path(&dj, path);	/* Follow the file path */
		if (res == FR_OK && (dj.fn[NSFLAG] & (NS_DOT | NS_NONAME))) res = FR_INVALID_NAME;	/* Check object validity */
		if (res == FR_OK) {
			mask &= AM_RDO|AM_HID|AM_SYS|AM_ARC;	/* Valid attribute mask */
			dj.dir[DIR_Attr] = (attr & mask) | (dj.dir[DIR_Attr] & (BYTE)~mask);	/* Apply attribute change */
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
			fs->wflag = 1;
#else
			PARENTFS(fs)->wflag = 1;
#endif
			if (res == FR_OK) {
				res = sync_fs(fs);
			}
		}
		FREE_NAMBUF();
	}

	LEAVE_FF(fs_bak, res);
}




/*-----------------------------------------------------------------------*/
/* Change Timestamp                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_utime (
	const TCHAR* path,	/* Pointer to the file/directory name */
	const FILINFO* fno	/* Pointer to the timestamp to be set */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	DEF_NAMBUF


	res = find_volume(&path, &fs, FA_WRITE);	/* Get logical drive */
	if (res == FR_OK) {
		dj.obj.fs = fs;
		INIT_NAMBUF(fs);
		res = follow_path(&dj, path);	/* Follow the file path */
		if (res == FR_OK && (dj.fn[NSFLAG] & (NS_DOT | NS_NONAME))) res = FR_INVALID_NAME;	/* Check object validity */
		if (res == FR_OK) {
			st_dword(dj.dir + DIR_ModTime, (DWORD)fno->fdate << 16 | fno->ftime);
			fs->wflag = 1;
			if (res == FR_OK) {
				res = sync_fs(fs);
			}
		}
		FREE_NAMBUF();
	}

	LEAVE_FF(fs, res);
}

#endif	/* FF_USE_CHMOD && !FF_FS_READONLY */



#if FF_USE_LABEL
/*-----------------------------------------------------------------------*/
/* Get Volume Label                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_getlabel (
	const TCHAR* path,	/* Logical drive number */
	TCHAR* label,		/* Buffer to store the volume label */
	DWORD* vsn			/* Variable to store the volume serial number */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	UINT si, di;
	WCHAR wc;

	/* Get logical drive */
	res = find_volume(&path, &fs, 0);

	/* Get volume label */
	if (res == FR_OK && label) {
		dj.obj.fs = fs; dj.obj.sclust = 0;	/* Open root directory */
		res = dir_sdi(&dj, 0);
		if (res == FR_OK) {
		 	res = DIR_READ_LABEL(&dj);		/* Find a volume label entry */
			if (res == FR_OK) {
				si = di = 0;		/* Extract volume label from AM_VOL entry */
				while (si < 11) {
					wc = dj.dir[si++];
#if FF_USE_LFN && FF_LFN_UNICODE >= 1 	/* Unicode output */
					if (dbc_1st((BYTE)wc) && si < 11) wc = wc << 8 | dj.dir[si++];	/* Is it a DBC? */
					wc = ff_oem2uni(wc, CODEPAGE);					/* Convert it into Unicode */
					if (wc != 0) wc = put_utf(wc, &label[di], 4);	/* Put it in Unicode */
					if (wc == 0) { di = 0; break; }
					di += wc;
#else									/* ANSI/OEM output */
					label[di++] = (TCHAR)wc;
#endif
				}
				do {				/* Truncate trailing spaces */
					label[di] = 0;
					if (di == 0) break;
				} while (label[--di] == ' ');
			}
		}
		if (res == FR_NO_FILE) {	/* No label entry and return nul string */
			label[0] = 0;
			res = FR_OK;
		}
	}

	/* Get volume serial number */
	if (res == FR_OK && vsn) {
		res = move_window(fs, fs->volbase);
		if (res == FR_OK) {
			switch (fs->fs_type) {
			case FS_FAT32:
				di = BS_VolID32; break;

			default:
				di = BS_VolID;
			}
			*vsn = ld_dword(fs->win + di);
		}
	}

	LEAVE_FF(fs, res);
}



#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Set Volume Label                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_setlabel (
	const TCHAR* label	/* Volume label to set with heading logical drive number */
)
{
	FRESULT res;
	DIR dj;
	FATFS *fs;
	BYTE dirvn[22];
	UINT di;
	WCHAR wc;
	static const char badchr[] = "\"*+,.:;<=>\?[]|\x7F";
#if FF_USE_LFN
	DWORD dc;
#endif

	/* Get logical drive */
	res = find_volume(&label, &fs, FA_WRITE);
	if (res != FR_OK) LEAVE_FF(fs, res);


	/* On the FAT/FAT32 volume */
	mem_set(dirvn, ' ', 11);
	di = 0;
	while ((UINT)*label >= ' ') {	/* Create volume label */
#if FF_USE_LFN
		dc = tchar2uni(&label);
		wc = (dc < 0x10000) ? ff_uni2oem(ff_wtoupper(dc), CODEPAGE) : 0;
#else									/* ANSI/OEM input */
		wc = (BYTE)*label++;
		if (dbc_1st((BYTE)wc)) wc = dbc_2nd((BYTE)*label) ? wc << 8 | (BYTE)*label++ : 0;
		if (IsLower(wc)) wc -= 0x20;		/* To upper ASCII characters */
#if FF_CODE_PAGE == 0
		if (ExCvt && wc >= 0x80) wc = ExCvt[wc - 0x80];	/* To upper extended characters (SBCS cfg) */
#elif FF_CODE_PAGE < 900
		if (wc >= 0x80) wc = ExCvt[wc - 0x80];	/* To upper extended characters (SBCS cfg) */
#endif
#endif
		if (wc == 0 || chk_chr(badchr + 0, (int)wc) || di >= (UINT)((wc >= 0x100) ? 10 : 11)) {	/* Reject invalid characters for volume label */
			LEAVE_FF(fs, FR_INVALID_NAME);
		}
		if (wc >= 0x100) dirvn[di++] = (BYTE)(wc >> 8);
		dirvn[di++] = (BYTE)wc;
	}
	if (dirvn[0] == DDEM) LEAVE_FF(fs, FR_INVALID_NAME);	/* Reject illegal name (heading DDEM) */
	while (di && dirvn[di - 1] == ' ') di--;				/* Snip trailing spaces */

	/* Set volume label */
	dj.obj.fs = fs; dj.obj.sclust = 0;	/* Open root directory */
	res = dir_sdi(&dj, 0);
	if (res == FR_OK) {
		res = DIR_READ_LABEL(&dj);	/* Get volume label entry */
		if (res == FR_OK) {
			if (di != 0) {
				mem_cpy(dj.dir, dirvn, 11);	/* Change the volume label */
			} else {
				dj.dir[DIR_Name] = DDEM;	/* Remove the volume label */
			}
			fs->wflag = 1;
			res = sync_fs(fs);
		} else {			/* No volume label entry or an error */
			if (res == FR_NO_FILE) {
				res = FR_OK;
				if (di != 0) {	/* Create a volume label entry */
					res = dir_alloc(&dj, 1);	/* Allocate an entry */
					if (res == FR_OK) {
						mem_set(dj.dir, 0, SZDIRE);	/* Clean the entry */
						dj.dir[DIR_Attr] = AM_VOL;	/* Create volume label entry */
						mem_cpy(dj.dir, dirvn, 11);
						fs->wflag = 1;
						res = sync_fs(fs);
					}
				}
			}
		}
	}

	LEAVE_FF(fs, res);
}

#endif /* !FF_FS_READONLY */
#endif /* FF_USE_LABEL */



#if FF_USE_EXPAND && !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Allocate a Contiguous Blocks to the File                              */
/*-----------------------------------------------------------------------*/

FRESULT f_expand (
	FIL* fp,			/* Pointer to the file object */
	FSIZE_t offset,		/* File offset to be expanded to */
	FSIZE_t fsz,		/* File size to be expanded to */
	int opt				/* Operation mode 0:Find and prepare or 1:Find and allocate */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD n, clst, stcl, scl, ncl, tcl, lclst, count, fclust = 0;
	DWORD clstbak = 0;
	FSIZE_t exsz;

	res = validate(&fp->obj, &fs);		/* Check validity of the file object */
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res);

	if (fsz == 0 || !(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_DENIED);

	n = (DWORD)fs->csize * SS(fs);	/* Cluster size */
	count = 0;
	if (fp->obj.sclust != 0) {
	    count = get_clustinfo(fp, &fclust);
	}
	if (offset + fsz <= n * count) LEAVE_FF(fs, FR_DENIED);

	exsz = offset + fsz - n * count;
	tcl = (DWORD)(exsz / n) + ((exsz & (n - 1)) ? 1 : 0);	/* Number of clusters required */
	stcl = fs->last_clst; lclst = 0;

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	if (ISVIRPART(fs)) {
		if (stcl < fs->st_clst || stcl >= fs->st_clst + fs->ct_clst) stcl = fs->st_clst;
		scl = stcl; ncl = 0; clst = stcl + 1;
		for (;;) {	/* Find a contiguous cluster block */
			n = get_fat(&fp->obj, clst);
			if (n == 1) { res = FR_INT_ERR; break; }
			if (n == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
			if (n == 0) {	/* Is it a free cluster? */
				if (clstbak != 0) {	/* Link each free cluster */
					res = put_fat(fs, clstbak, clst);
					if (res != FR_OK)
						break;
				} else {	/* Clstbak has not been update, current cluster is the head cluster of the chain */
					scl = clst;
				}
				clstbak = clst;	/* Update the current cluster to the last cluster in next loop */
				if (++ncl == tcl) {	/* Link the mark of the end of chain */
					res = put_fat(fs, clst, 0xFFFFFFFF);
					break;
				}
			}
			if (clst == stcl) {	/* No contiguous cluster? */
				res = FR_DENIED;
				break;
			}
			/* Move the current cluster to the next one */
			if (++clst >= fs->st_clst + fs->ct_clst) clst = fs->st_clst;
		}
	} else
#endif
	{
		if (stcl < 2 || stcl >= fs->n_fatent) stcl = 2;
		scl = stcl; ncl = 0; clst = stcl + 1;
		for (;;) {	/* Find a contiguous cluster block */
			n = get_fat(&fp->obj, clst);
			if (n == 1) { res = FR_INT_ERR; break; }
			if (n == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
			if (n == 0) {	/* Is it a free cluster? */
				if (clstbak != 0) {	/* Link each free cluster */
					res = put_fat(fs, clstbak, clst);
					if (res != FR_OK) break;
				} else {	/* Clstbak has not been update, current cluster is the head cluster of the chain */
					scl = clst;
				}
				clstbak = clst;	/* Update the current cluster to the last cluster in next loop */
				if (++ncl == tcl) {	/* Link the mark of the end of chain */
					res = put_fat(fs, clst, 0xFFFFFFFF);
					break;
				}
			}
			if (clst == stcl) {	/* No contiguous cluster? */
				res = FR_DENIED;
				break;
			}
			/* Move the current cluster to the next one */
			if (++clst >= fs->n_fatent) clst = 2;
		}
	}

	if (res == FR_OK) {
#ifndef LOSCFG_FS_FAT_VIRTUAL_PARTITION
		fs->last_clst = lclst;	/* Set suggested start cluster to start next */
		if (opt) {
			if (fp->obj.sclust == 0) {
				fp->obj.sclust = scl;	/* Update object allocation information */
			} else {
				res = put_fat(fs, fclust, scl);
				if (res != FR_OK) LEAVE_FF(fs, res);
			}
			fp->flag |= FA_MODIFIED;
			if (fs->free_clst  <= fs->n_fatent - 2) {	/* Update FSINFO */
				fs->free_clst -= tcl;
				fs->fsi_flag |= 1;
			}
		}
#else
		if (ISVIRPART(fs) && ISCHILD(fs))
			fs->last_clst = lclst;		/* Set suggested start cluster to start next */
		PARENTFS(fs)->last_clst = lclst;
		if (opt) {
			if (fp->obj.sclust == 0) {
				fp->obj.sclust = scl;	/* Update object allocation information */
			} else {
				res = put_fat(fs, fclust, scl);
				if (res != FR_OK) LEAVE_FF(fs, res);
			}
			fp->flag |= FA_MODIFIED;
			if (ISVIRPART(fs)) {
				if (fs->free_clst <= fs->ct_clst && ISCHILD(fs))
					fs->free_clst -= tcl;
				if (PARENTFS(fs)->free_clst  <= PARENTFS(fs)->n_fatent - 2) {
					PARENTFS(fs)->free_clst -= tcl;
					PARENTFS(fs)->fsi_flag |= 1;
				}
			} else {
				if (fs->free_clst  <= fs->n_fatent - 2) {	/* Update FSINFO */
					fs->free_clst -= tcl;
					fs->fsi_flag |= 1;
				}
			}
		}
#endif
	} else {	/* Reached error, remove the chain which built before */
		clst = scl;
		for (;;) {
			n = get_fat(&fp->obj, clst);
			if (n == 1 || n == 0) { res = FR_INT_ERR; break; }
			if (n == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
			res = put_fat(fs, clst, 0);
			if (res != FR_OK) break;
			if (n == 0x0FFFFFFF) break;	/* If the current cluster is the last cluster ,the finish this operation */
			clst = n;
		}
		res = put_fat(fs, fclust, 0xFFFFFFFF);
	}

	LEAVE_FF(fs, res);
}

#endif /* FF_USE_EXPAND && !FF_FS_READONLY */



#if FF_USE_FORWARD
/*-----------------------------------------------------------------------*/
/* Forward Data to the Stream Directly                                   */
/*-----------------------------------------------------------------------*/

FRESULT f_forward (
	FIL* fp, 						/* Pointer to the file object */
	UINT (*func)(const BYTE*,UINT),	/* Pointer to the streaming function */
	UINT btf,						/* Number of bytes to forward */
	UINT* bf						/* Pointer to number of bytes forwarded */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD clst;
	QWORD sect;
	FSIZE_t remain;
	UINT rcnt, csect;
	BYTE *dbuf;


	*bf = 0;	/* Clear transfer byte counter */
	res = validate(&fp->obj, &fs);		/* Check validity of the file object */
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res);
	if (!(fp->flag & FA_READ)) LEAVE_FF(fs, FR_NO_EPERM);	/* Check access mode */

	remain = fp->obj.objsize - fp->fptr;
	if (btf > remain) btf = (UINT)remain;			/* Truncate btf by remaining bytes */

	for ( ;  btf && (*func)(0, 0);					/* Repeat until all data transferred or stream goes busy */
		fp->fptr += rcnt, *bf += rcnt, btf -= rcnt) {
		csect = (UINT)(fp->fptr / SS(fs) & (fs->csize - 1));	/* Sector offset in the cluster */
		if (fp->fptr % SS(fs) == 0) {				/* On the sector boundary? */
			if (csect == 0) {						/* On the cluster boundary? */
				clst = (fp->fptr == 0) ?			/* On the top of the file? */
					fp->obj.sclust : get_fat(&fp->obj, fp->clust);
				if (clst <= 1) ABORT(fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fs, FR_DISK_ERR);
				fp->clust = clst;					/* Update current cluster */
			}
		}
		sect = clst2sect(fs, fp->clust);			/* Get current data sector */
		if (sect == 0) ABORT(fs, FR_INT_ERR);
		sect += csect;
#if FF_FS_TINY
		if (move_window(fs, sect) != FR_OK) ABORT(fs, FR_DISK_ERR);	/* Move sector window to the file data */
		dbuf = fs->win;
#else
		if (fp->sect != sect) {		/* Fill sector cache with file data */
#if !FF_FS_READONLY
			if (fp->flag & FA_DIRTY) {		/* Write-back dirty sector cache */
				if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
				fp->flag &= (BYTE)~FA_DIRTY;
			}
#endif
			if (disk_read(fs->pdrv, fp->buf, sect, 1) != RES_OK) ABORT(fs, FR_DISK_ERR);
		}
		dbuf = fp->buf;
#endif
		fp->sect = sect;
		rcnt = SS(fs) - (UINT)fp->fptr % SS(fs);	/* Number of bytes left in the sector */
		if (rcnt > btf) rcnt = btf;					/* Clip it by btr if needed */
		rcnt = (*func)(dbuf + ((UINT)fp->fptr % SS(fs)), rcnt);	/* Forward the file data */
		if (rcnt == 0) ABORT(fs, FR_INT_ERR);
	}

	LEAVE_FF(fs, FR_OK);
}
#endif /* FF_USE_FORWARD */



#if FF_USE_MKFS && !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Create an FAT volume                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_mkfs (
	const TCHAR* path,	/* Logical drive number */
	BYTE opt,		/* Format option */
	int sector,		/* Size of allocation unit (cluster) [byte] */
	void* work,		/* Pointer to working buffer */
	UINT len		/* Size of working buffer */
)
{
	const UINT n_fats = 1;		/* Number of FATs for FAT/FAT32 volume (1 or 2) */
	const UINT n_rootdir = 512;	/* Number of root directory entries for FAT volume */
	static const WORD cst[] = {1, 4, 16, 64, 256, 512, 0};	/* Cluster size boundary for FAT volume (4Ks unit) */
	static const WORD cst32[] = {1, 2, 4, 8, 16, 32, 0};	/* Cluster size boundary for FAT32 volume (128Ks unit) */
	BYTE fmt, sys, *buf, *pte, pdrv, part;
	size_t ss;
	DWORD au;
	QWORD szb_buf, sz_buf, sz_blk, n_clst, pau, sect, nsect, n;
	QWORD b_vol, b_fat, b_data;		/* Base LBA for volume, fat, data */
	QWORD sz_vol, sz_rsv, sz_fat, sz_dir;	/* Size for volume, fat, dir, data */
	UINT i;
	int vol;
	DSTATUS stat;
	FRESULT res = FR_OK;
#if FF_MULTI_PARTITION
	int extended_br;
	int extended_pos = -1;
	DWORD extended_base = 0;
	DWORD extended_offset = 0;
	BYTE* multi_buf = NULL;
	int gpt_part = 0;
#endif

#if FF_USE_TRIM
	QWORD tbl[3];
#endif


	/* Check mounted drive and clear work area */
	vol = get_ldnumber(&path);					/* Get target logical drive */
	if (vol < 0) return FR_INVALID_DRIVE;
	if (FatFs[vol]) FatFs[vol]->fs_type = 0;	/* Clear the volume if mounted */
	pdrv = LD2PD(vol);	/* Physical drive */
	part = LD2PT(vol);	/* Partition (0:create as new, 1-4:get from partition table) */

	/* Check physical drive status */
	stat = disk_initialize(pdrv);
	if (stat & STA_NOINIT) return FR_NOT_READY;
	if (stat & STA_PROTECT) return FR_WRITE_PROTECTED;
	if (disk_ioctl(pdrv, GET_BLOCK_SIZE, &sz_blk) != RES_OK || !sz_blk || sz_blk > 32768 || (sz_blk & (sz_blk - 1))) sz_blk = 1;	/* Erase block to align data area */
#if FF_MAX_SS != FF_MIN_SS		/* Get sector size of the medium if variable sector size cfg. */
	if (disk_ioctl(pdrv, GET_SECTOR_SIZE, &ss) != RES_OK) return FR_DISK_ERR;
	if (ss > FF_MAX_SS || ss < FF_MIN_SS || (ss & (ss - 1))) return FR_DISK_ERR;
#else
	ss = FF_MAX_SS;
#endif
	au = sector * ss;
	if ((au != 0 && au < ss) || au > 0x1000000 || (au & (au - 1))) return FR_INVALID_PARAMETER;	/* Check if au is valid */
	au /= ss;	/* Cluster size in unit of sector */

	/* Get working buffer */
	buf = (BYTE*)work;		/* Working buffer */
	sz_buf = len / ss;		/* Size of working buffer (sector) */
	szb_buf = sz_buf * ss;	/* Size of working buffer (byte) */
	if (!szb_buf) return FR_MKFS_ABORTED;

#if FF_MULTI_PARTITION
	/* Determine where the volume to be located (b_vol, sz_vol) */
	if (part != 0) {
		/* Get partition information from partition table in the MBR and EBR to set boot sector properly */
		if (disk_read(pdrv, buf, 0, 1) != RES_OK) return FR_DISK_ERR;	/* Load MBR */
		if (ld_word(buf + BS_55AA) != 0xAA55) return FR_MKFS_ABORTED;	/* Check if MBR is valid */
		if (buf[MBR_Table + 4] != 0xEE) {
			pte = buf + (MBR_Table + (part - 1) * SZ_PTE);
			extended_br = part - 4;
			if (extended_br > 0) {
				for (i = 0; i < 4; i++) {
					pte = &buf[MBR_Table + i * SZ_PTE];
					if (pte[4] == 0x0F) extended_pos = i;
				}
				pte = &buf[MBR_Table + extended_pos * SZ_PTE];
				extended_base = ld_dword(pte + 8);
				if (disk_raw_read(LD2DI(vol), buf, extended_base, 1) != RES_OK) return FR_DISK_ERR;
				pte = &buf[MBR_Table];
				for (; extended_br > 1; --extended_br) {
					pte = &buf[MBR_Table];
					extended_offset = ld_dword(pte + SZ_PTE + 8);
					mem_set(buf, 0, len);
					if (disk_raw_read(LD2DI(vol), buf, extended_base + extended_offset, 1) != RES_OK) return FR_DISK_ERR;
				}
			}
			if (!pte[4]) return FR_MKFS_ABORTED;	/* No partition? */
		} else {
			gpt_part = 1;
			b_vol = LD2PS(vol);		/* Volume start sector */
			if (disk_read(pdrv, buf, b_vol, 1) != RES_OK) return FR_DISK_ERR;	/* Load GPT partition info */
			if (ld_word(buf + BS_55AA) != 0xAA55) return FR_MKFS_ABORTED;		/* Check if GPT partition is valid */
		}

		multi_buf = ff_memalloc(ss);
		if (multi_buf == NULL)
			return FR_NOT_ENOUGH_CORE;

		mem_cpy(multi_buf, buf, ss);
		if (!gpt_part)
			if (!pte[4]) {res = FR_MKFS_ABORTED; goto EXIT;}	/* No partition? */
		b_vol = LD2PS(vol);		/* Volume start sector */
		sz_vol = LD2PC(vol);	/* Volume size */

	} else
#endif
	{
		/* Create a single-partition in this function */
		if (disk_ioctl(pdrv, GET_SECTOR_COUNT, &sz_vol) != RES_OK) {res = FR_DISK_ERR; goto EXIT;}
		b_vol = (opt & FM_SFD) ? 0 : 63;		/* Volume start sector */
		if (sz_vol < b_vol) {res = FR_MKFS_ABORTED; goto EXIT;}
		sz_vol -= b_vol;						/* Volume size */
	}
	if (sz_vol < 128) {res = FR_MKFS_ABORTED; goto EXIT;}	/* Check if volume size is >=128s */

	/* Pre-determine the FAT type */
	do {
		if (au > 128) {res = FR_INVALID_PARAMETER; goto EXIT;}	/* Too large au for FAT/FAT32 */
		if (opt & FM_FAT32) {	/* FAT32 possible? */
			if ((opt & FM_ANY) == FM_FAT32 || !(opt & FM_FAT)) {	/* FAT32 only or no-FAT? */
			    fmt = FS_FAT32; break;
			}
		}
		if (!(opt & FM_FAT)) {res = FR_INVALID_PARAMETER; goto EXIT;}	/* no-FAT? */
		fmt = FS_FAT16;
	} while (0);

	/* Create an FAT12/16/32 volume */
	do {
		pau = au;
		/* Pre-determine number of clusters and FAT sub-type */
		if (fmt == FS_FAT32) {	/* FAT32 volume */
			if (pau == 0) {	/* au auto-selection */
				n = sz_vol / 0x20000;	/* Volume size in unit of 128KS */
				for (i = 0, pau = 1; cst32[i] && cst32[i] <= n; i++, pau <<= 1) ;	/* Get from table */
			}
			n_clst = sz_vol / pau;	/* Number of clusters */
			sz_fat = (n_clst * 4 + 8 + ss - 1) / ss;	/* FAT size [sector] */
			sz_rsv = 32;	/* Number of reserved sectors */
			sz_dir = 0;	/* No static directory */
			if (n_clst <= MAX_FAT16 || n_clst > MAX_FAT32) {res = FR_MKFS_ABORTED; goto EXIT;}
		} else {				/* FAT volume */
			if (pau == 0) {	/* au auto-selection */
				n = sz_vol / 0x1000;	/* Volume size in unit of 4KS */
				for (i = 0, pau = 1; cst[i] && cst[i] <= n; i++, pau <<= 1) ;	/* Get from table */
			}
			n_clst = sz_vol / pau;
			if (n_clst > MAX_FAT12) {
				n = n_clst * 2 + 4;	/* FAT size [byte] */
			} else {
				fmt = FS_FAT12;
				n = (n_clst * 3 + 1) / 2 + 3;	/* FAT size [byte] */
			}
			sz_fat = (n + ss - 1) / ss;	/* FAT size [sector] */
			sz_rsv = 1;					/* Number of reserved sectors */
			sz_dir = (DWORD)n_rootdir * SZDIRE / ss;	/* Rootdir size [sector] */
		}
		b_fat = b_vol + sz_rsv;		/* FAT base */
		b_data = b_fat + sz_fat * n_fats + sz_dir;	/* Data base */

		/* Align data base to erase block boundary (for flash memory media) */
		n = ((b_data + sz_blk - 1) & ~(sz_blk - 1)) - b_data;	/* Next nearest erase block from current data base */
		if (fmt == FS_FAT32) {	/* FAT32: Move FAT base */
			sz_rsv += n; b_fat += n;
		} else {					/* FAT12/16: Expand FAT size */
			sz_fat += n / n_fats;
		}

		/* Determine number of clusters and final check of validity of the FAT sub-type */
		if (sz_vol < b_data + pau * 16 - b_vol) {
			res = FR_MKFS_ABORTED;
			goto EXIT;
		} /* Too small volume */
		n_clst = (sz_vol - sz_rsv - sz_fat * n_fats - sz_dir) / pau;
		if (fmt == FS_FAT32) {
			if (n_clst <= MAX_FAT16) {	/* Too few clusters for FAT32 */
				if (!au && (au = pau / 2) != 0) continue;	/* Adjust cluster size and retry */
				{res = FR_MKFS_ABORTED; goto EXIT;}
			}
		}
		if (fmt == FS_FAT16) {
			if (n_clst > MAX_FAT16) {	/* Too many clusters for FAT16 */
				if (au == 0 && (pau * 2) <= 64) {
					au = pau * 2; continue;		/* Adjust cluster size and retry */
				}
				if ((opt & FM_FAT32)) {
					fmt = FS_FAT32; continue;	/* Switch type to FAT32 and retry */
				}
				if (au == 0 && (au = pau * 2) <= 128) continue;	/* Adjust cluster size and retry */
				{res = FR_MKFS_ABORTED; goto EXIT;}
			}
			if  (n_clst <= MAX_FAT12) {	/* Too few clusters for FAT16 */
				if (au == 0 && (au = pau * 2) <= 128) continue;	/* Adjust cluster size and retry */
				{res = FR_MKFS_ABORTED; goto EXIT;}
			}
		}
		if (fmt == FS_FAT12 && n_clst > MAX_FAT12) {res = FR_MKFS_ABORTED; goto EXIT;}	/* Too many clusters for FAT12 */

		/* Ok, it is the valid cluster configuration */
		break;
	} while (1);

#if FF_USE_TRIM
	tbl[0] = b_vol; tbl[1] = b_vol + sz_vol - 1;	/* Inform the device the volume area can be erased */
	disk_ioctl(pdrv, CTRL_TRIM, tbl);
#endif
	/* Create FAT VBR */
	mem_set(buf, 0, ss);
	mem_cpy(buf + BS_JmpBoot, "\xEB\xFE\x90" "MSDOS5.0", 11);	/* Boot jump code (x86), OEM name */
	st_word(buf + BPB_BytsPerSec, ss); 				/* Sector size [byte] */
	buf[BPB_SecPerClus] = (BYTE)pau;				/* Cluster size [sector] */
	st_word(buf + BPB_RsvdSecCnt, (WORD)sz_rsv);	/* Size of reserved area */
	buf[BPB_NumFATs] = (BYTE)n_fats;				/* Number of FATs */
	st_word(buf + BPB_RootEntCnt, (WORD)((fmt == FS_FAT32) ? 0 : n_rootdir));	/* Number of root directory entries */
	if (sz_vol < 0x10000) {
		st_word(buf + BPB_TotSec16, (WORD)sz_vol);	/* Volume size in 16-bit LBA */
	} else {
		st_dword(buf + BPB_TotSec32, sz_vol);		/* Volume size in 32-bit LBA */
	}
	buf[BPB_Media] = 0xF8;						/* Media descriptor byte */
	st_word(buf + BPB_SecPerTrk, 63);				/* Number of sectors per track (for int13) */
	st_word(buf + BPB_NumHeads, 255);				/* Number of heads (for int13) */
	st_dword(buf + BPB_HiddSec, b_vol);				/* Volume offset in the physical drive [sector] */
	if (fmt == FS_FAT32) {
		st_dword(buf + BS_VolID32, GET_FATTIME());	/* VSN */
		st_dword(buf + BPB_FATSz32, sz_fat);		/* FAT size [sector] */
		st_dword(buf + BPB_RootClus32, 2);			/* Root directory cluster # (2) */
		st_word(buf + BPB_FSInfo32, 1);				/* Offset of FSINFO sector (VBR + 1) */
		st_word(buf + BPB_BkBootSec32, 6);			/* Offset of backup VBR (VBR + 6) */
		buf[BS_DrvNum32] = 0x80;					/* Drive number (for int13) */
		buf[BS_BootSig32] = 0x29;					/* Extended boot signature */
		mem_cpy(buf + BS_VolLab32, "NO NAME    " "FAT32   ", 19);	/* Volume label, FAT signature */
	} else {
		st_dword(buf + BS_VolID, GET_FATTIME());	/* VSN */
		st_word(buf + BPB_FATSz16, (WORD)sz_fat);	/* FAT size [sector] */
		buf[BS_DrvNum] = 0x80;						/* Drive number (for int13) */
		buf[BS_BootSig] = 0x29;						/* Extended boot signature */
		mem_cpy(buf + BS_VolLab, "NO NAME    " "FAT     ", 19);	/* Volume label, FAT signature */
	}
	st_word(buf + BS_55AA, 0xAA55);				/* Signature (offset is fixed here regardless of sector size) */
	if (disk_write(pdrv, buf, b_vol, 1) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }	/* Write it to the VBR sector */

	/* Create FSINFO record if needed */
	if (fmt == FS_FAT32) {
		disk_write(pdrv, buf, b_vol + 6, 1);		/* Write backup VBR (VBR + 6) */
		mem_set(buf, 0, ss);
		st_dword(buf + FSI_LeadSig, 0x41615252);
		st_dword(buf + FSI_StrucSig, 0x61417272);
		st_dword(buf + FSI_Free_Count, n_clst - 1);	/* Number of free clusters */
		st_dword(buf + FSI_Nxt_Free, 2);			/* Last allocated cluster# */
		st_word(buf + BS_55AA, 0xAA55);
		disk_write(pdrv, buf, b_vol + 7, 1);		/* Write backup FSINFO (VBR + 7) */
		disk_write(pdrv, buf, b_vol + 1, 1);		/* Write original FSINFO (VBR + 1) */
	}

	/* Initialize FAT area */
	mem_set(buf, 0, (UINT)szb_buf);
	sect = b_fat;		/* FAT start sector */
	for (i = 0; i < n_fats; i++) {			/* Initialize FATs each */
		if (fmt == FS_FAT32) {
			st_dword(buf + 0, 0xFFFFFFF8);	/* Entry 0 */
			st_dword(buf + 4, 0xFFFFFFFF);	/* Entry 1 */
			st_dword(buf + 8, 0x0FFFFFFF);	/* Entry 2 (root directory) */
		} else {
			st_dword(buf + 0, (fmt == FS_FAT12) ? 0xFFFFF8 : 0xFFFFFFF8);	/* Entry 0 and 1 */
		}
		nsect = sz_fat;		/* Number of FAT sectors */
		do {	/* Fill FAT sectors */
			n = (nsect > sz_buf) ? sz_buf : nsect;
			if (disk_write(pdrv, buf, sect, (UINT)n) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }
			mem_set(buf, 0, ss);
			sect += n; nsect -= n;
		} while (nsect);
	}

	/* Initialize root directory (fill with zero) */
	nsect = (fmt == FS_FAT32) ? pau : sz_dir;	/* Number of root directory sectors */
	do {
		n = (nsect > sz_buf) ? sz_buf : nsect;
		if (disk_write(pdrv, buf, sect, (UINT)n) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }
		sect += n; nsect -= n;
	} while (nsect);


	/* Flush the virtual partition sector */
	if (fmt == FS_FAT32) {
		sect = b_fat - 1;
		mem_set(buf, 0, (UINT)szb_buf);
		if (disk_write(pdrv, buf, sect, 1) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }
	}

	/* Determine system ID in the partition table */
	if (fmt == FS_FAT32) {
		sys = part > 4 ? 0x0B : 0x0C;	/* FAT32X */
	} else {
		if (sz_vol >= 0x10000) {
			sys = 0x06;	/* FAT12/16 (>=64KS) */
		} else {
			sys = (fmt == FS_FAT16) ? 0x04 : 0x01;	/* FAT16 (<64KS) : FAT12 (<64KS) */
		}
	}

	/* Update partition information */
#if FF_MULTI_PARTITION
	if (part != 0) {	/* Created in the existing partition */
		if (!gpt_part) {
			/* Update system ID in the partition table in MBR or EBR */
			if (part > 4) {
				pte = &multi_buf[MBR_Table];
			} else {
				pte = &multi_buf[MBR_Table + (part - 1) * SZ_PTE];
			}
			n = (part > 4) ? extended_base + extended_offset : 0;
			pte[4] = sys;
			if (disk_raw_write(LD2DI(vol), multi_buf, n, 1) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }	/* Write it to teh MBR */
		} else {
			b_vol = LD2PS(vol);		/* Volume start sector */
			if (disk_raw_read(LD2DI(vol), multi_buf, b_vol, 1) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }
			pte = &multi_buf[MBR_Table];
			pte[4] = sys;
			if (disk_raw_write(LD2DI(vol), multi_buf, b_vol, 1) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }	/* Write it to the MBR */
		}
	} else
#endif
	{		/* Created as a new single partition */
		if (!(opt & FM_SFD)) {	/* Create partition table if in FDISK format */
			mem_set(buf, 0, ss);
			st_word(buf + BS_55AA, 0xAA55);		/* MBR signature */
			pte = buf + MBR_Table;				/* Create partition table for single partition in the drive */
			pte[PTE_Boot] = 0;					/* Boot indicator */
			pte[PTE_StHead] = 1;				/* Start head */
			pte[PTE_StSec] = 1;					/* Start sector */
			pte[PTE_StCyl] = 0;					/* Start cylinder */
			pte[PTE_System] = sys;				/* System type */
			n = (b_vol + sz_vol) / (63 * 255);	/* (End CHS may be invalid) */
			pte[PTE_EdHead] = 254;				/* End head */
			pte[PTE_EdSec] = (BYTE)(n >> 2 | 63);	/* End sector */
			pte[PTE_EdCyl] = (BYTE)n;			/* End cylinder */
			st_dword(pte + PTE_StLba, b_vol);	/* Start offset in LBA */
			st_dword(pte + PTE_SizLba, sz_vol);	/* Size in sectors */
			if (disk_write(pdrv, buf, 0, 1) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }	/* Write it to the MBR */
		}
	}

	if (disk_ioctl(pdrv, CTRL_SYNC, 0) != RES_OK) { res = FR_DISK_ERR; goto EXIT; }

	switch(fmt) {
	case FS_FAT12:
		PRINTK("format to FAT12, %lld sectors per cluster.\n", pau);
		break;
	case FS_FAT16:
		PRINTK("Format to FAT16, %lld sectors per cluster.\n", pau);
		break;
	case FS_FAT32:
		PRINTK("Format to FAT32, %lld sectors per cluster.\n", pau);
	}

EXIT:
#if FF_MULTI_PARTITION
	ff_memfree(multi_buf);
#endif
	return res;
}



#if FF_MULTI_PARTITION
/*-----------------------------------------------------------------------*/
/* Create Partition Table on the Physical Drive                          */
/*-----------------------------------------------------------------------*/

FRESULT f_fdisk (
	BYTE pdrv,			/* Physical drive number */
	const DWORD* szt,	/* Pointer to the size table for each partitions */
	void* work			/* Pointer to the working buffer (null: use heap memory) */
)
{
	UINT i, n, sz_cyl, tot_cyl, b_cyl, e_cyl, p_cyl;
	BYTE s_hd, e_hd, *p, *buf = (BYTE*)work;
	DSTATUS stat;
	DWORD sz_disk, sz_part, s_part;
	FRESULT res;


	stat = disk_initialize(pdrv);
	if (stat & STA_NOINIT) return FR_NOT_READY;
	if (stat & STA_PROTECT) return FR_WRITE_PROTECTED;
	if (disk_ioctl(pdrv, GET_SECTOR_COUNT, &sz_disk)) return FR_DISK_ERR;

	buf = (BYTE*)work;
#if FF_USE_LFN == 3
	if (!buf) buf = ff_memalloc(FF_MAX_SS);	/* Use heap memory for working buffer */
#endif
	if (!buf) return FR_NOT_ENOUGH_CORE;

	/* Determine the CHS without any consideration of the drive geometry */
	for (n = 16; n < 256 && sz_disk / n / 63 > 1024; n *= 2) ;
	if (n == 256) n--;
	e_hd = (BYTE)(n - 1);
	sz_cyl = 63 * n;
	tot_cyl = sz_disk / sz_cyl;

	/* Create partition table */
	mem_set(buf, 0, FF_MAX_SS);
	p = buf + MBR_Table; b_cyl = 0;
	for (i = 0; i < 4; i++, p += SZ_PTE) {
		p_cyl = (szt[i] <= 100U) ? (DWORD)tot_cyl * szt[i] / 100 : szt[i] / sz_cyl;	/* Number of cylinders */
		if (p_cyl == 0) continue;
		s_part = (DWORD)sz_cyl * b_cyl;
		sz_part = (DWORD)sz_cyl * p_cyl;
		if (i == 0) {	/* Exclude first track of cylinder 0 */
			s_hd = 1;
			s_part += 63; sz_part -= 63;
		} else {
			s_hd = 0;
		}
		e_cyl = b_cyl + p_cyl - 1;	/* End cylinder */
		if (e_cyl >= tot_cyl) LEAVE_MKFS(FR_INVALID_PARAMETER);

		/* Set partition table */
		p[1] = s_hd;						/* Start head */
		p[2] = (BYTE)(((b_cyl >> 2) & 0xC0) | 1);	/* Start sector */
		p[3] = (BYTE)b_cyl;					/* Start cylinder */
		p[4] = 0x07;						/* System type (temporary setting) */
		p[5] = e_hd;						/* End head */
		p[6] = (BYTE)(((e_cyl >> 2) & 0xC0) | 63);	/* End sector */
		p[7] = (BYTE)e_cyl;					/* End cylinder */
		st_dword(p + 8, s_part);			/* Start sector in LBA */
		st_dword(p + 12, sz_part);			/* Number of sectors */

		/* Next partition */
		b_cyl += p_cyl;
	}
	st_word(p, 0xAA55);		/* MBR signature (always at offset 510) */

	/* Write it to the MBR */
	res = (disk_write(pdrv, buf, 0, 1) == RES_OK && disk_ioctl(pdrv, CTRL_SYNC, 0) == RES_OK) ? FR_OK : FR_DISK_ERR;
	LEAVE_MKFS(res);
}

#endif /* FF_MULTI_PARTITION */
#endif /* FF_USE_MKFS && !FF_FS_READONLY */




#if FF_USE_STRFUNC
#if FF_USE_LFN && FF_LFN_UNICODE && (FF_STRF_ENCODE < 0 || FF_STRF_ENCODE > 3)
#error Wrong FF_STRF_ENCODE setting
#endif
/*-----------------------------------------------------------------------*/
/* Get a String from the File                                            */
/*-----------------------------------------------------------------------*/

TCHAR* f_gets (
	TCHAR* buff,	/* Pointer to the string buffer to read */
	int len,		/* Size of string buffer (items) */
	FIL* fp			/* Pointer to the file object */
)
{
	int nc = 0;
	TCHAR *p = buff;
	BYTE s[4];
	UINT rc;
	DWORD dc;
#if FF_USE_LFN && FF_LFN_UNICODE && FF_STRF_ENCODE <= 2
	WCHAR wc;
#endif
#if FF_USE_LFN && FF_LFN_UNICODE && FF_STRF_ENCODE == 3
	UINT ct;
#endif

#if FF_USE_LFN && FF_LFN_UNICODE			/* With code conversion (Unicode API) */
	/* Make a room for the character and terminator  */
	if (FF_LFN_UNICODE == 1) len -= (FF_STRF_ENCODE == 0) ? 1 : 2;
	if (FF_LFN_UNICODE == 2) len -= (FF_STRF_ENCODE == 0) ? 3 : 4;
	if (FF_LFN_UNICODE == 3) len -= 1;
	while (nc < len) {
#if FF_STRF_ENCODE == 0		/* Read a character in ANSI/OEM */
		f_read(fp, s, 1, &rc);
		if (rc != 1) break;
		wc = s[0];
		if (dbc_1st((BYTE)wc)) {
			f_read(fp, s, 1, &rc);
			if (rc != 1 || !dbc_2nd(s[0])) continue;
			wc = wc << 8 | s[0];
		}
		dc = ff_oem2uni(wc, CODEPAGE);
		if (dc == 0) continue;
#elif FF_STRF_ENCODE == 1 || FF_STRF_ENCODE == 2 	/* Read a character in UTF-16LE/BE */
		f_read(fp, s, 2, &rc);
		if (rc != 2) break;
		dc = (FF_STRF_ENCODE == 1) ? ld_word(s) : s[0] << 8 | s[1];
		if (IsSurrogateL(dc)) continue;
		if (IsSurrogateH(dc)) {
			f_read(fp, s, 2, &rc);
			if (rc != 2) break;
			wc = (FF_STRF_ENCODE == 1) ? ld_word(s) : s[0] << 8 | s[1];
			if (!IsSurrogateL(wc)) continue;
			dc = ((dc & 0x3FF) + 0x40) << 10 | (wc & 0x3FF);
		}
#else	/* Read a character in UTF-8 */
		f_read(fp, s, 1, &rc);
		if (rc != 1) break;
		dc = s[0];
		if (dc >= 0x80) {	/* Multi-byte character? */
			ct = 0;
			if ((dc & 0xE0) == 0xC0) { dc &= 0x1F; ct = 1; }	/* 2-byte? */
			if ((dc & 0xF0) == 0xE0) { dc &= 0x0F; ct = 2; }	/* 3-byte? */
			if ((dc & 0xF8) == 0xF0) { dc &= 0x07; ct = 3; }	/* 4-byte? */
			if (ct == 0) continue;
			f_read(fp, s, ct, &rc);		/* Get trailing bytes */
			if (rc != ct) break;
			rc = 0;
			do {	/* Merge trailing bytes */
				if ((s[rc] & 0xC0) != 0x80) break;
				dc = dc << 6 | (s[rc] & 0x3F);
			} while (++rc < ct);
			if (rc != ct || dc < 0x80 || IsSurrogate(dc) || dc >= 0x110000) continue;	/* Wrong encoding? */
		}
#endif
		if (FF_USE_STRFUNC == 2 && dc == '\r') continue;	/* Strip \r off if needed */
#if FF_LFN_UNICODE == 1	|| FF_LFN_UNICODE == 3	/* Output it in UTF-16/32 encoding */
		if (FF_LFN_UNICODE == 1 && dc >= 0x10000) {	/* Out of BMP at UTF-16? */
			*p++ = (TCHAR)(0xD800 | ((dc >> 10) - 0x40)); nc++;	/* Make and output high surrogate */
			dc = 0xDC00 | (dc & 0x3FF);		/* Make low surrogate */
		}
		*p++ = (TCHAR)dc; nc++;
		if (dc == '\n') break;	/* End of line? */
#elif FF_LFN_UNICODE == 2		/* Output it in UTF-8 encoding */
		if (dc < 0x80) {	/* 1-byte */
			*p++ = (TCHAR)dc;
			nc++;
			if (dc == '\n') break;	/* End of line? */
		} else {
			if (dc < 0x800) {		/* 2-byte */
				*p++ = (TCHAR)(0xC0 | (dc >> 6 & 0x1F));
				*p++ = (TCHAR)(0x80 | (dc >> 0 & 0x3F));
				nc += 2;
			} else {
				if (dc < 0x10000) {	/* 3-byte */
					*p++ = (TCHAR)(0xE0 | (dc >> 12 & 0x0F));
					*p++ = (TCHAR)(0x80 | (dc >> 6 & 0x3F));
					*p++ = (TCHAR)(0x80 | (dc >> 0 & 0x3F));
					nc += 3;
				} else {			/* 4-byte */
					*p++ = (TCHAR)(0xF0 | (dc >> 18 & 0x07));
					*p++ = (TCHAR)(0x80 | (dc >> 12 & 0x3F));
					*p++ = (TCHAR)(0x80 | (dc >> 6 & 0x3F));
					*p++ = (TCHAR)(0x80 | (dc >> 0 & 0x3F));
					nc += 4;
				}
			}
		}
#endif
	}

#else			/* Byte-by-byte without any conversion (ANSI/OEM API) */
	len -= 1;	/* Make a room for the terminator */
	while (nc < len) {
		f_read(fp, s, 1, &rc);
		if (rc != 1) break;
		dc = s[0];
		if (FF_USE_STRFUNC == 2 && dc == '\r') continue;
		*p++ = (TCHAR)dc; nc++;
		if (dc == '\n') break;
	}
#endif

	*p = 0;		/* Terminate the string */
	return nc ? buff : 0;	/* When no data read due to EOF or error, return with error. */
}




#if !FF_FS_READONLY
#include <stdarg.h>
/*-----------------------------------------------------------------------*/
/* Put a Character to the File                                           */
/*-----------------------------------------------------------------------*/

typedef struct {	/* Putchar output buffer and work area */
	FIL *fp;		/* Ptr to the writing file */
	int idx, nchr;	/* Write index of buf[] (-1:error), number of encoding units written */
#if FF_USE_LFN && FF_LFN_UNICODE == 1
	WCHAR hs;
#elif FF_USE_LFN && FF_LFN_UNICODE == 2
	BYTE bs[4];
	UINT wi, ct;
#endif
	BYTE buf[64];	/* Write buffer */
} putbuff;


static void putc_bfd (		/* Buffered write with code conversion */
	putbuff* pb,
	TCHAR c
)
{
	UINT n;
	int i, nc;
#if FF_USE_LFN && FF_LFN_UNICODE
	WCHAR hs, wc;
#if FF_LFN_UNICODE == 2
	DWORD dc;
	TCHAR *tp;
#endif
#endif

	if (FF_USE_STRFUNC == 2 && c == '\n') {	 /* LF -> CRLF conversion */
		putc_bfd(pb, '\r');
	}

	i = pb->idx;			/* Write index of pb->buf[] */
	if (i < 0) return;
	nc = pb->nchr;			/* Write unit counter */

#if FF_USE_LFN && FF_LFN_UNICODE
#if FF_LFN_UNICODE == 1		/* UTF-16 input */
	if (IsSurrogateH(c)) {
		pb->hs = c; return;
	}
	hs = pb->hs; pb->hs = 0;
	if (hs != 0) {
		if (!IsSurrogateL(c)) hs = 0;
	} else {
		if (IsSurrogateL(c)) return;
	}
	wc = c;
#elif FF_LFN_UNICODE == 2	/* UTF-8 input */
	for (;;) {
		if (pb->ct == 0) {	/* Out of multi-byte sequence? */
			pb->bs[pb->wi = 0] = (BYTE)c;	/* Save 1st byte */
			if ((BYTE)c < 0x80) break;					/* 1-byte? */
			if (((BYTE)c & 0xE0) == 0xC0) pb->ct = 1;	/* 2-byte? */
			if (((BYTE)c & 0xF0) == 0xE0) pb->ct = 2;	/* 3-byte? */
			if (((BYTE)c & 0xF1) == 0xF0) pb->ct = 3;	/* 4-byte? */
			return;
		} else {				/* In the multi-byte sequence */
			if (((BYTE)c & 0xC0) != 0x80) {	/* Broken sequence? */
				pb->ct = 0; continue;
			}
			pb->bs[++pb->wi] = (BYTE)c;	/* Save the trailing byte */
			if (--pb->ct == 0) break;	/* End of multi-byte sequence? */
			return;
		}
	}
	tp = (TCHAR*)pb->bs;
	dc = tchar2uni(&tp);	/* UTF-8 ==> UTF-16 */
	if (dc == 0xFFFFFFFF) return;
	wc = (WCHAR)dc;
	hs = (WCHAR)(dc >> 16);
#elif FF_LFN_UNICODE == 3	/* UTF-32 input */
	if (IsSurrogate(c) || c >= 0x110000) return;
	if (c >= 0x10000) {
		hs = (WCHAR)(0xD800 | ((c >> 10) - 0x40)); 	/* Make high surrogate */
		wc = 0xDC00 | (c & 0x3FF);					/* Make low surrogate */
	} else {
		hs = 0;
		wc = (WCHAR)c;
	}
#endif

#if FF_STRF_ENCODE == 1		/* Write a character in UTF-16LE */
	if (hs != 0) {
		st_word(&pb->buf[i], hs);
		i += 2;
		nc++;
	}
	st_word(&pb->buf[i], wc);
	i += 2;
#elif FF_STRF_ENCODE == 2	/* Write a character in UTF-16BE */
	if (hs != 0) {
		pb->buf[i++] = (BYTE)(hs >> 8);
		pb->buf[i++] = (BYTE)hs;
		nc++;
	}
	pb->buf[i++] = (BYTE)(wc >> 8);
	pb->buf[i++] = (BYTE)wc;
#elif FF_STRF_ENCODE == 3	/* Write it in UTF-8 */
	if (hs != 0) {				/* 4-byte */
		nc += 3;
		hs = (hs & 0x3FF) + 0x40;
		pb->buf[i++] = (BYTE)(0xF0 | hs >> 8);
		pb->buf[i++] = (BYTE)(0x80 | (hs >> 2 & 0x3F));
		pb->buf[i++] = (BYTE)(0x80 | (hs & 3) << 4 | (wc >> 6 & 0x0F));
		pb->buf[i++] = (BYTE)(0x80 | (wc & 0x3F));
	} else {
		if (wc < 0x80) {		/* 1-byte */
			pb->buf[i++] = (BYTE)wc;
		} else {
			if (wc < 0x800) {	/* 2-byte */
				nc += 1;
				pb->buf[i++] = (BYTE)(0xC0 | wc >> 6);
			} else {			/* 3-byte */
				nc += 2;
				pb->buf[i++] = (BYTE)(0xE0 | wc >> 12);
				pb->buf[i++] = (BYTE)(0x80 | (wc >> 6 & 0x3F));
			}
			pb->buf[i++] = (BYTE)(0x80 | (wc & 0x3F));
		}
	}
#else						/* Write it in ANSI/OEM */
	if (hs != 0) return;
	wc = ff_uni2oem(wc, CODEPAGE);	/* UTF-16 ==> ANSI/OEM */
	if (wc == 0) return;
	if (wc >= 0x100) {
		pb->buf[i++] = (BYTE)(wc >> 8); nc++;
	}
	pb->buf[i++] = (BYTE)wc;
#endif

#else									/* ANSI/OEM input (without re-encode) */
	pb->buf[i++] = (BYTE)c;
#endif

	if (i >= (int)(sizeof pb->buf) - 4) {	/* Write buffered characters to the file */
		f_write(pb->fp, pb->buf, (UINT)i, &n);
		i = (n == (UINT)i) ? 0 : -1;
	}
	pb->idx = i;
	pb->nchr = nc + 1;
}


static int putc_flush (		/* Flush left characters in the buffer */
	putbuff* pb
)
{
	UINT nw;

	if (   pb->idx >= 0	/* Flush buffered characters to the file */
		&& f_write(pb->fp, pb->buf, (UINT)pb->idx, &nw) == FR_OK
		&& (UINT)pb->idx == nw) return pb->nchr;
	return EOF;
}


static void putc_init (		/* Initialize write buffer */
	putbuff* pb,
	FIL* fp
)
{
	mem_set(pb, 0, sizeof (putbuff));
	pb->fp = fp;
}



int f_putc (
	TCHAR c,	/* A character to be output */
	FIL* fp		/* Pointer to the file object */
)
{
	putbuff pb;


	putc_init(&pb, fp);
	putc_bfd(&pb, c);	/* Put the character */
	return putc_flush(&pb);
}




/*-----------------------------------------------------------------------*/
/* Put a String to the File                                              */
/*-----------------------------------------------------------------------*/

int f_puts (
	const TCHAR* str,	/* Pointer to the string to be output */
	FIL* fp				/* Pointer to the file object */
)
{
	putbuff pb;


	putc_init(&pb, fp);
	while (*str) putc_bfd(&pb, *str++);		/* Put the string */
	return putc_flush(&pb);
}




/*-----------------------------------------------------------------------*/
/* Put a Formatted String to the File                                    */
/*-----------------------------------------------------------------------*/

int f_printf (
	FIL* fp,			/* Pointer to the file object */
	const TCHAR* fmt,	/* Pointer to the format string */
	...					/* Optional arguments... */
)
{
	va_list arp;
	putbuff pb;
	BYTE f, r;
	UINT i, j, w;
	DWORD v;
	TCHAR c, d, str[32], *p;


	putc_init(&pb, fp);

	va_start(arp, fmt);

	for (;;) {
		c = *fmt++;
		if (c == 0) break;			/* End of string */
		if (c != '%') {				/* Non escape character */
			putc_bfd(&pb, c);
			continue;
		}
		w = f = 0;
		c = *fmt++;
		if (c == '0') {				/* Flag: '0' padding */
			f = 1; c = *fmt++;
		} else {
			if (c == '-') {			/* Flag: left justified */
				f = 2; c = *fmt++;
			}
		}
		if (c == '*') {				/* Minimum width by argument */
			w = va_arg(arp, int);
			c = *fmt++;
		} else {
			while (IsDigit(c)) {	/* Minimum width */
				w = w * 10 + c - '0';
				c = *fmt++;
			}
		}
		if (c == 'l' || c == 'L') {	/* Type prefix: Size is long int */
			f |= 4; c = *fmt++;
		}
		if (c == 0) break;
		d = c;
		if (IsLower(d)) d -= 0x20;
		switch (d) {				/* Atgument type is... */
		case 'S' :					/* String */
			p = va_arg(arp, TCHAR*);
			for (j = 0; p[j]; j++) ;
			if (!(f & 2)) {						/* Right padded */
				while (j++ < w) putc_bfd(&pb, ' ') ;
			}
			while (*p) putc_bfd(&pb, *p++) ;		/* String body */
			while (j++ < w) putc_bfd(&pb, ' ') ;	/* Left padded */
			continue;

		case 'C' :					/* Character */
			putc_bfd(&pb, (TCHAR)va_arg(arp, int)); continue;

		case 'B' :					/* Unsigned binary */
			r = 2; break;

		case 'O' :					/* Unsigned octal */
			r = 8; break;

		case 'D' :					/* Signed decimal */
		case 'U' :					/* Unsigned decimal */
			r = 10; break;

		case 'X' :					/* Unsigned hexdecimal */
			r = 16; break;

		default:					/* Unknown type (pass-through) */
			putc_bfd(&pb, c); continue;
		}

		/* Get an argument and put it in numeral */
		v = (f & 4) ? (DWORD)va_arg(arp, long) : ((d == 'D') ? (DWORD)(long)va_arg(arp, int) : (DWORD)va_arg(arp, unsigned int));
		if (d == 'D' && (v & 0x80000000)) {
			v = 0 - v;
			f |= 8;
		}
		i = 0;
		do {
			d = (TCHAR)(v % r); v /= r;
			if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
			str[i++] = d + '0';
		} while (v && i < sizeof str / sizeof *str);
		if (f & 8) str[i++] = '-';
		j = i; d = (f & 1) ? '0' : ' ';
		if (!(f & 2)) {
			while (j++ < w) putc_bfd(&pb, d);	/* Right pad */
		}
		do {
			putc_bfd(&pb, str[--i]);			/* Number body */
		} while (i);
		while (j++ < w) putc_bfd(&pb, d);		/* Left pad */
	}

	va_end(arp);

	return putc_flush(&pb);
}

#endif /* !FF_FS_READONLY */
#endif /* FF_USE_STRFUNC */


int fatfs_get_vol(FATFS *fat)
{
	int vol;

	for (vol = 0; vol < FF_VOLUMES; vol ++) {
		if (FatFs[vol] == fat)
			return vol;
	}

	return -1;
}

void f_settimestatus(UINT status)
{
	time_status = status;
}

FRESULT f_fcheckfat(DIR_FILE* dir_info)
{
	FRESULT res;
	FATFS *fs;
	DWORD val = 0, tcl, clust_size;

	res = validate(&(dir_info->f_dir.obj), &fs);	/* Lock volume */
	if (res == FR_OK) {
		clust_size  = (DWORD)fs->csize * SS(fs);	/* Cluster size */
		tcl = (DWORD)(dir_info->fno.fsize / clust_size) + ((dir_info->fno.fsize & (clust_size - 1)) ? 1 : 0);	/* Number of clusters required */
		if (dir_info->fno.fsize == 0) {	/* When set file size to zero, remove entire cluster chain */
			if (dir_info->fno.sclst != 0) {
#if !FF_FS_READONLY
				res = remove_chain(&(dir_info->f_dir.obj), dir_info->fno.sclst, 0);
#else
				res = FR_DENIED;
#endif
			} else
				res = FR_OK;
		} else {			/* When truncate a part of the file, remove remaining clusters */
			val = get_fat(&(dir_info->f_dir.obj), dir_info->fno.sclst + tcl - 1);
			if (val == 0xFFFFFFFF) {
				res = FR_DISK_ERR;
				LEAVE_FF(fs, res);
			}
			if (val == 1) {
				res = FR_INT_ERR;
				LEAVE_FF(fs, res);
			}
			if (val == 0x0FFFFFFF) {
				res = FR_OK;
				LEAVE_FF(fs, res);
			}
			if (val < fs->n_fatent) {
#if !FF_FS_READONLY
				res = remove_chain(&(dir_info->f_dir.obj), val, dir_info->fno.sclst + tcl - 1);
#else
				res = FR_DENIED;
#endif
			}
		}
	}

	LEAVE_FF(fs, res);
}


#if FF_CODE_PAGE == 0
/*-----------------------------------------------------------------------*/
/* Set Active Codepage for the Path Name                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_setcp (
	WORD cp		/* Value to be set as active code page */
)
{
	static const WORD       validcp[] = {  437,   720,   737,   771,   775,   850,   852,   857,   860,   861,   862,   863,   864,   865,   866,   869,   932,   936,   949,   950, 0};
	static const BYTE* const tables[] = {Ct437, Ct720, Ct737, Ct771, Ct775, Ct850, Ct852, Ct857, Ct860, Ct861, Ct862, Ct863, Ct864, Ct865, Ct866, Ct869, Dc932, Dc936, Dc949, Dc950, 0};
	UINT i;


	for (i = 0; validcp[i] != 0 && validcp[i] != cp; i++) ;	/* Find the code page */
	if (validcp[i] != cp) return FR_INVALID_PARAMETER;	/* Not found? */

	CodePage = cp;
	if (cp >= 900) {	/* DBCS */
		ExCvt = 0;
		DbcTbl = tables[i];
	} else {			/* SBCS */
		ExCvt = tables[i];
		DbcTbl = 0;
	}
	return FR_OK;
}
#endif	/* FF_CODE_PAGE == 0 */

