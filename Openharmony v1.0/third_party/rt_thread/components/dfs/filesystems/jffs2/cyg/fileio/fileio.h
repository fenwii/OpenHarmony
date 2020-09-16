#ifndef CYGONCE_FILEIO_H
#define CYGONCE_FILEIO_H
//=============================================================================
//
//      fileio.h
//
//      Fileio header
//
//=============================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later
// version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with eCos; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// As a special exception, if other files instantiate templates or use
// macros or inline functions from this file, or you compile this file
// and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered by
// the GNU General Public License. However the source code for this file
// must still be made available in accordance with section (3) of the GNU
// General Public License v2.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
// -------------------------------------------
// ####ECOSGPLCOPYRIGHTEND####
//=============================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     nickg
// Contributors:  nickg
// Date:          2000-05-25
// Purpose:       Fileio header
// Description:   This header contains the external definitions of the general file
//                IO subsystem for POSIX and EL/IX compatability.
//
// Usage:
//              #include <fileio.h>
//              ...
//
//
//####DESCRIPTIONEND####
//
//=============================================================================
#include "fs_other.h"

#include <limits.h>
#include <stddef.h>             // NULL, size_t
#include <sys/types.h>
#include <zconf.h>
#include "fcntl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

//=============================================================================


struct  cyg_fstab_entry;
typedef struct  cyg_fstab_entry  cyg_fstab_entry;

struct CYG_FILEOPS_TAG;
typedef struct CYG_FILEOPS_TAG cyg_fileops;

struct CYG_FILE_TAG;
typedef struct CYG_FILE_TAG cyg_file;

struct CYG_IOVEC_TAG;
typedef struct CYG_IOVEC_TAG jffs2_iovec;

struct CYG_UIO_TAG;
typedef struct CYG_UIO_TAG jffs2_uio;

typedef struct  IATTR  iattr;

//=============================================================================
// Directory pointer
#define CYG_ADDRWORD UINTPTR
typedef CYG_ADDRWORD cyg_dir;

#define JFFS2_DIR_NULL 0

//=============================================================================

struct jffs2_stat;

//=============================================================================
// Mount table entry

struct cyg_mtab_entry
{
    const char          *name;          // name of mount point
    const char          *fsname;        // name of implementing filesystem
    const char          *devname;       // name of hardware device
    CYG_ADDRWORD      data;           // private data value

    // The following are filled in after a successful mount operation
    int                 valid;          // Valid entry?
    //jffs2_fstab_entry   *fs;            // pointer to fstab entry
    cyg_dir           root;           // root directory pointer
} ; // JFFS2_HAL_TABLE_TYPE;  // prife
typedef struct cyg_mtab_entry cyg_mtab_entry;
//=============================================================================
// IO vector descriptors

struct CYG_IOVEC_TAG
{
    void           *iov_base;           /* Base address. */
    ssize_t        iov_len;             /* Length. */
};

enum	cyg_uio_rw { UIO_READ, UIO_WRITE };

/* Segment flag values. */
enum cyg_uio_seg
{
    UIO_USERSPACE,		        /* from user data space */
    UIO_SYSSPACE		        /* from system space */
};

struct CYG_UIO_TAG
{
    struct CYG_IOVEC_TAG *uio_iov;	/* pointer to array of iovecs */
    int	                  uio_iovcnt;	/* number of iovecs in array */
    off_t       	      uio_offset;	/* offset into file this uio corresponds to */
    ssize_t     	      uio_resid;	/* residual i/o count */
    enum cyg_uio_seg      uio_segflg;    /* see above */
    enum cyg_uio_rw       uio_rw;        /* see above */
};

struct CYG_FILE_TAG
{
    UINT32	                    f_flag;		    /* file state                   */
    UINT16                      f_ucount;       /* use count                    */
    UINT16                      f_type;		    /* descriptor type              */
    UINT32                      f_syncmode;     /* synchronization protocol     */
    //struct CYG_FILEOPS_TAG      *f_ops;       /* file operations              */
    off_t       	            f_offset;       /* current offset               */
    CYG_ADDRWORD	            f_data;		    /* file or socket               */
    CYG_ADDRWORD                f_xops;         /* extra type specific ops      */
    cyg_mtab_entry              *f_mte;         /* mount table entry            */
};


//-----------------------------------------------------------------------------
// Type of file

#define	CYG_FILE_TYPE_FILE      1	/* file */
#define	CYG_FILE_TYPE_SOCKET	2	/* communications endpoint */
#define	CYG_FILE_TYPE_DEVICE	3	/* device */

//-----------------------------------------------------------------------------

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif // ifndef JFFS2ONCE_FILEIO_H
// End of fileio.h
