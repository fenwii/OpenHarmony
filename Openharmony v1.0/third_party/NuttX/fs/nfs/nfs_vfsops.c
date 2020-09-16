/****************************************************************************
 * fs/nfs/nfs_vfsops.c
 *
 *   Copyright (C) 2012-2013, 2015, 2017-2018 Gregory Nutt. All rights reserved.
 *   Copyright (C) 2012 Jose Pablo Rojas Vargas. All rights reserved.
 *   Author: Jose Pablo Rojas Vargas <jrojas@nx-engineering.com>
 *           Gregory Nutt <gnutt@nuttx.org>
 *
 * Leveraged from OpenBSD:
 *
 *   Copyright (c) 1989, 1993, 1995
 *   The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <sys/mount.h>
#include <sys/socket.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <pthread.h>
#include <unistd.h>
#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "vfs_config.h"
#include "dirent.h"
#include "fs/fs.h"
#include "fs/dirent_fs.h"
#include "nfs.h"
#include "nfs_node.h"
#include "xdr_subs.h"
#include "los_tables.h"
#include "inode/inode.h"
#include "los_vm_filemap.h"
#include "user_copy.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifdef LOSCFG_FS_NFS
/* The V3 EXCLUSIVE file creation logic is not fully supported. */

#define USE_GUARDED_CREATE    1

/* include/nuttx/fs/dirent.h has its own version of these lengths.  They must
 * match the NFS versions.
 */

#if NFSX_V3FHMAX != DIRENT_NFS_MAXHANDLE
#  error "Length of file handle in fs_dirent_s is incorrect"
#endif

#if NFSX_V3COOKIEVERF != DIRENT_NFS_VERFLEN
#  error "Length of cookie verify in fs_dirent_s is incorrect"
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Use to pass file information to nfs_stat_common() */

struct nfs_statinfo_s
{
  uint16_t ns_mode;    /* File access mode */
  uint8_t  ns_type;    /* File type */
  uint64_t ns_size;    /* File size */
  time_t   ns_atime;   /* Time of last access */
  time_t   ns_mtime;   /* Time of last modification */
  time_t   ns_ctime;   /* Time of last status change */
};

#define MIN_IPv4_UDP_MSS (IP_FRAG_MAX_MTU - (14 + 20)) /* (Ethernet MTU - (Eth header size + IP header size)) */

#define FILENAME_MAX_LEN 50

/****************************************************************************
 * Public Data
 ****************************************************************************/

uint32_t nfs_true;
uint32_t nfs_false;
uint32_t nfs_xdrneg1;
NFSMOUNT_HOOK g_NFSMOUNT_HOOK = (NFSMOUNT_HOOK)(UINTPTR)NULL;

#ifdef CONFIG_NFS_STATISTICS
struct nfsstats nfsstats;
#endif

/****************************************************************************
 * Private Type Definitions
 ****************************************************************************/

#define NFS_DIR_ENTRY_MALLOC(entry)                                           \
  do                                                                          \
    {                                                                         \
      entry = (struct entry3 *)malloc(sizeof(struct entry3));                 \
      if (entry == NULL)                                                      \
        {                                                                     \
          fvdbg("malloc failed\n");                                           \
          error = ENOMEM;                                                     \
          goto errout_with_memory;                                            \
        }                                                                     \
      (void)memset_s(entry, sizeof(struct entry3), 0, sizeof(struct entry3)); \
    }                                                                         \
  while (0)

#define NFS_DIR_ENTRY_FREE(entry)  \
  do                               \
    {                              \
      free(entry->contents);       \
      entry->contents = NULL;      \
      free(entry);                 \
      entry = NULL;                \
    }                              \
  while (0)


/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int     nfs_filecreate(FAR struct nfsmount *nmp,
                   FAR struct nfsnode *np, FAR const char *relpath,
                   int oflags, mode_t mode);
static int     nfs_filetruncate(FAR struct nfsmount *nmp,
                   FAR struct nfsnode *np, uint32_t length);
static int     nfs_fileopen(FAR struct nfsmount *nmp,
                   FAR struct nfsnode *np, FAR const char *relpath,
                   int oflags, mode_t mode);

static int     nfs_open(FAR struct file *filep, const char *relpath,
                   int oflags, mode_t mode);
static int     nfs_close(FAR struct file *filep);
static ssize_t nfs_read(FAR struct file *filep, char *buffer, size_t buflen);
static ssize_t nfs_write(FAR struct file *filep, const char *buffer,
                   size_t buflen);
static off_t   nfs_seek(FAR struct file *filep, off_t offset, int whence);
static loff_t  nfs_seek64(FAR struct file *filep, loff_t offset, int whence);
static int     nfs_dup(FAR const struct file *oldp, FAR struct file *newp);
static int     nfs_opendir(struct inode *mountpt, const char *relpath,
                   struct fs_dirent_s *dir);
static int     nfs_closedir(FAR struct inode *mountpt, FAR struct fs_dirent_s *dir);
static int     nfs_readdir(struct inode *mountpt, struct fs_dirent_s *dir);
static int     nfs_rewinddir(FAR struct inode *mountpt,
                   FAR struct fs_dirent_s *dir);
static void    nfs_decode_args(FAR struct nfs_mount_parameters *nprmt,
                   FAR struct nfs_args *argp);
static int     nfs_bind(FAR struct inode *blkdriver, const void *data,
                   void **handle, FAR const char *realpath);
static int     nfs_unbind(void *handle, FAR struct inode **blkdriver);
static int     nfs_statfs(FAR struct inode *mountpt,
                   FAR struct statfs *buf);
static int     nfs_remove(FAR struct inode *mountpt,
                   FAR const char *relpath);
static int     nfs_mkdir(FAR struct inode *mountpt,
                   FAR const char *relpath, mode_t mode);
static int     nfs_rmdir(FAR struct inode *mountpt,
                   FAR const char *relpath);
static int     nfs_rename(FAR struct inode *mountpt,
                   FAR const char *oldrelpath, FAR const char *newrelpath);
static void    nfs_stat_common(FAR struct nfs_statinfo_s *info,
                   FAR struct stat *buf);
static int     nfs_stat(struct inode *mountpt, FAR const char *relpath,
                   FAR struct stat *buf);

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* nfs vfs operations. */

const struct mountpt_operations nfs_operations =
{
  nfs_open,                     /* open */
  nfs_close,                    /* close */
  nfs_read,                     /* read */
  nfs_write,                    /* write */
  nfs_seek,                     /* seek */
  NULL,                         /* ioctl */
  OsVfsFileMmap,                /* mmap */

  NULL,                         /* sync */
  nfs_dup,                      /* dup */
  NULL,                         /* fstat */
  NULL,                         /* truncate */

  nfs_opendir,                  /* opendir */
  nfs_closedir,                 /* closedir */
  nfs_readdir,                  /* readdir */
  nfs_rewinddir,                /* rewinddir */

  nfs_bind,                     /* bind */
  nfs_unbind,                   /* unbind */
  nfs_statfs,                   /* statfs */
  NULL,                         /* virstatfs */
  nfs_remove,                   /* unlink */
  nfs_mkdir,                    /* mkdir */
  nfs_rmdir,                    /* rmdir */
  nfs_rename,                   /* rename */
  nfs_stat,                     /* stat */
  NULL,                         /* for utime */
  NULL,                         /* chattr */
  nfs_seek64,                   /* seek64 */
  NULL,                         /* getlabel */
  NULL,                         /* fallocate */
  NULL,                         /* fallocate64 */
  NULL,                         /* truncate64 */
  NULL,                         /* fscheck */
  NULL,                         /* map_pages */
  NULL,                         /* readpage */
  NULL,                         /* writepage */
};

FSMAP_ENTRY(nfs_fsmap, "nfs", nfs_operations, FALSE, FALSE);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nfs_filecreate
 *
 * Description:
 *   Create a file.  This is part of the file open logic that is executed if
 *   the user asks to create a file.
 *
 * Returned Value:
 *   0 on success; a positive errno value on failure.
 *
 ****************************************************************************/

static int nfs_filecreate(FAR struct nfsmount *nmp, FAR struct nfsnode *np,
                          FAR const char *relpath, int oflags, mode_t mode)
{
  struct file_handle      fhandle;
  struct nfs_fattr        fattr;
  char                    filename[NAME_MAX + 1];
  FAR uint32_t           *ptr;
  uint32_t                tmp;
  int                     namelen;
  int                     reqlen;
  int                     error;

  /* Find the NFS node of the directory containing the file to be created */

  error = nfs_finddir(nmp, relpath, &fhandle, &fattr, filename);
  if (error != OK)
    {
      ferr("ERROR: nfs_finddir returned: %d\n", error);
      return error;
    }

  /* Create the CREATE RPC call arguments */

  ptr    = (FAR uint32_t *)&nmp->nm_msgbuffer.create.create;
  reqlen = 0;

  /* Copy the variable length, directory file handle */

  *ptr++  = txdr_unsigned(fhandle.length);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &fhandle.handle, fhandle.length);
  reqlen += (int)fhandle.length;
  ptr    += uint32_increment(fhandle.length);

  /* Copy the variable-length file name */

  namelen = strlen(filename);

  *ptr++  = txdr_unsigned(namelen);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, filename, namelen);
  ptr    += uint32_increment(namelen);
  reqlen += uint32_alignup(namelen);

  /* Set the creation mode */

#ifdef USE_GUARDED_CREATE
  *ptr++  = htonl(NFSV3CREATE_GUARDED);
#else
  *ptr++  = htonl(NFSV3CREATE_EXCLUSIVE);
#endif

  reqlen += sizeof(uint32_t);

  /* Mode information is not provided if EXCLUSIVE creation is used.
   * in this case, we must call SETATTR after successfully creating
   * the file.
   */

#ifndef USE_GUARDED_CREATE
  if ((oflags & O_CREAT) == 0)
#endif
    {
      /* Set the mode.  NOTE: Here we depend on the fact that the NuttX and NFS
       * bit settings are the same (at least for the bits of interest).
       */

      *ptr++  = nfs_true; /* True: mode value follows */
      reqlen += sizeof(uint32_t);

      tmp = mode & (NFSMODE_IWOTH | NFSMODE_IROTH | NFSMODE_IWGRP |
                    NFSMODE_IRGRP | NFSMODE_IWUSR | NFSMODE_IRUSR);
      *ptr++  = txdr_unsigned(tmp);
      reqlen += sizeof(uint32_t);

      /* Set the user ID to zero */

      *ptr++  = nfs_true;             /* True: Uid value follows */
      *ptr++  = 0;                    /* UID = 0 (nobody) */
      reqlen += 2*sizeof(uint32_t);

      /* Set the group ID to one */

      *ptr++  = nfs_true;            /* True: Gid value follows */
      *ptr++  = htonl(1);            /* GID = 1 (nogroup) */
      reqlen += 2*sizeof(uint32_t);

      /* Set the size to zero */

      *ptr++  = nfs_true;            /* True: Size value follows */
      *ptr++  = 0;                   /* Size = 0 */
      *ptr++  = 0;
      reqlen += 3*sizeof(uint32_t);

      /* Don't change times */

      *ptr++  = htonl(NFSV3SATTRTIME_DONTCHANGE); /* Don't change atime */
      *ptr++  = htonl(NFSV3SATTRTIME_DONTCHANGE); /* Don't change mtime */
      reqlen += 2*sizeof(uint32_t);
    }

  /* Send the NFS request.  Note there is special logic here to handle version 3
   * exclusive open semantics.
   */

  do
    {
      nfs_statistics(NFSPROC_CREATE);
      error = nfs_request(nmp, NFSPROC_CREATE,
                          (FAR void *)&nmp->nm_msgbuffer.create, reqlen,
                          (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
    }
#ifdef USE_GUARDED_CREATE
  while (0);
#else
  while (((oflags & O_CREAT) != 0) && error == EOPNOTSUPP);
#endif

  /* Check for success */

  if (error == OK)
    {
      /* Parse the returned data */

      ptr = (FAR uint32_t *)&((FAR struct rpc_reply_create *)
        nmp->nm_iobuffer)->create;

      /* Save the file handle in the file data structure */

      tmp = *ptr++;  /* handle_follows */
      if (!tmp)
        {
          ferr("ERROR: no file handle follows\n");
          return EINVAL;
        }

      tmp = *ptr++;
      tmp = fxdr_unsigned(uint32_t, tmp);
      DEBUGASSERT(tmp <= NFSX_V3FHMAX);

      np->n_fhsize      = (uint8_t)tmp;
      memcpy(&np->n_fhandle, ptr, tmp);
      ptr += uint32_increment(tmp);

      /* Save the attributes in the file data structure */

      tmp = *ptr;  /* handle_follows */
      if (!tmp)
        {
          fwarn("WARNING: no file attributes\n");
        }
      else
        {
          /* Initialize the file attributes */

          nfs_attrupdate(np, (FAR struct nfs_fattr *)ptr);
        }

      /* Any following dir_wcc data is ignored for now */
    }

  return error;
}

/****************************************************************************
 * Name: nfs_fileopen
 *
 * Description:
 *   Truncate an open file to zero length.  This is part of the file open
 *   logic.
 *
 * Returned Value:
 *   0 on success; a positive errno value on failure.
 *
 ****************************************************************************/

static int nfs_filetruncate(FAR struct nfsmount *nmp,
                            FAR struct nfsnode *np, uint32_t length)
{
  FAR uint32_t *ptr;
  int           reqlen;
  int           error;

  finfo("Truncating file\n");

  /* Create the SETATTR RPC call arguments */

  ptr    = (FAR uint32_t *)&nmp->nm_msgbuffer.setattr.setattr;
  reqlen = 0;

  /* Copy the variable length, directory file handle */

  *ptr++  = txdr_unsigned(np->n_fhsize);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &np->n_fhandle, np->n_fhsize);
  reqlen += (int)np->n_fhsize;
  ptr    += uint32_increment(np->n_fhsize);

  /* Copy the variable-length attributes */

  *ptr++  = nfs_false;                        /* Don't change mode */
  *ptr++  = nfs_false;                        /* Don't change uid */
  *ptr++  = nfs_false;                        /* Don't change gid */
  *ptr++  = nfs_true;                         /* Use the following size */
  *ptr++  = length;                           /* Truncate to the specified length */
  *ptr++  = 0;
  *ptr++  = htonl(NFSV3SATTRTIME_TOSERVER);   /* Use the server's time */
  *ptr++  = htonl(NFSV3SATTRTIME_TOSERVER);   /* Use the server's time */
  *ptr++  = nfs_false;                        /* No guard value */
  reqlen += 9 * sizeof(uint32_t);

  /* Perform the SETATTR RPC */

  nfs_statistics(NFSPROC_SETATTR);
  error = nfs_request(nmp, NFSPROC_SETATTR,
                      (FAR void *)&nmp->nm_msgbuffer.setattr, reqlen,
                      (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
  if (error != OK)
    {
      ferr("ERROR: nfs_request failed: %d\n", error);
      return error;
    }

  /* Indicate that the file now has zero length */

  np->n_size = 0;
  return OK;
}

/****************************************************************************
 * Name: nfs_fileopen
 *
 * Description:
 *   Open a file.  This is part of the file open logic that attempts to open
 *   an existing file.
 *
 * Returned Value:
 *   0 on success; a positive errno value on failure.
 *
 ****************************************************************************/

static int nfs_fileopen(FAR struct nfsmount *nmp, FAR struct nfsnode *np,
                        FAR const char *relpath, int oflags, mode_t mode)
{
  struct file_handle fhandle;
  struct nfs_fattr   fattr;
  uint32_t           tmp;
  int                error = 0;

  /* Find the NFS node associate with the path */

  error = nfs_findnode(nmp, relpath, &fhandle, &fattr, NULL);
  if (error != OK)
    {
      ferr("ERROR: nfs_findnode returned: %d\n", error);
      return error;
    }

  /* Check if the object is a directory */

  tmp = fxdr_unsigned(uint32_t, fattr.fa_type);
  if (tmp == NFDIR)
    {
      /* Exit with EISDIR if we attempt to open a directory */

      ferr("ERROR: Path is a directory\n");
      return EISDIR;
    }

  /* Check if the caller has sufficient privileges to open the file */

  if ((oflags & O_WRONLY) != 0)
    {
      /* Check if anyone has priveleges to write to the file -- owner,
       * group, or other (we are probably "other" and may still not be
       * able to write).
       */

      tmp = fxdr_unsigned(uint32_t, fattr.fa_mode);
      if ((tmp & (NFSMODE_IWOTH | NFSMODE_IWGRP | NFSMODE_IWUSR)) == 0)
        {
          ferr("ERROR: File is read-only: %08x\n", tmp);
          return EACCES;
        }
    }

  /* It would be an error if we are asked to create the file exclusively */

  if ((oflags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
    {
      /* Already exists -- can't create it exclusively */

      ferr("ERROR: File exists\n");
      return EEXIST;
    }

  /* Initialize the file private data.
   *
   * Copy the file handle.
   */

  np->n_fhsize      = (uint8_t)fhandle.length;
  memcpy(&np->n_fhandle, &fhandle.handle, fhandle.length);

  /* Save the file attributes */

  nfs_attrupdate(np, &fattr);

  /* If O_TRUNC is specified and the file is opened for writing,
   * then truncate the file.  This operation requires that the file is
   * writable, but we have already checked that. O_TRUNC without write
   * access is ignored.
   */

  if ((oflags & O_TRUNC) && (oflags & (O_WRONLY | O_RDWR)))
    {
      /* Truncate the file to zero length.  I think we can do this with
       * the SETATTR call by setting the length to zero.
       */

      return nfs_filetruncate(nmp, np, 0);
    }

  return OK;
}

/****************************************************************************
 * Name: nfs_fileupdate
 *
 * Description:
 *   This is to update the file attributes like size, type. This sends a LOOKUP msg of nfs
 *   to get latest file attributes.
 *
 * Returned Value:
 *   0 on success; a positive errno value on failure.
 *
 ****************************************************************************/

static int nfs_fileupdate(FAR struct nfsmount *nmp, struct nfsnode *np,
                          FAR const char *relpath)
{
  struct file_handle fhandle;
  struct nfs_fattr   fattr;
  int                error;

  /* Find the NFS node associate with the path */

  error = nfs_findnode(nmp, relpath, &fhandle, &fattr, (struct nfs_fattr *)NULL);
  if (error != OK)
    {
      fdbg("ERROR: nfs_findnode returned: %d\n", error);
      return error;
    }

  /* Update the file handle */

  error = memcpy_s(&np->n_fhandle, NFSX_V3FHMAX, &fhandle.handle, fhandle.length);
  if (error != EOK)
    {
      return ENOBUFS;
    }

  np->n_fhsize = fhandle.length;

  /* Save the file attributes */

  nfs_attrupdate(np, &fattr);

  return OK;
}

/****************************************************************************
 * Name: nfs_open
 *
 * Description:
 *   If oflags == O_CREAT it creates a file, if not it check to see if the
 *   type is ok and that deletion is not in progress.
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_open(FAR struct file *filep, FAR const char *relpath,
                    int oflags, mode_t mode)
{
  struct nfsmount *nmp;
  struct nfsnode *np;
  int error;

  /* Sanity checks */

  DEBUGASSERT(filep->f_inode != NULL);

  /* Get the mountpoint inode reference from the file structure and the
   * mountpoint private data from the inode structure
   */

  nmp = (FAR struct nfsmount *)filep->f_inode->i_private;
  DEBUGASSERT(nmp != NULL);

  /* Pre-allocate the file private data to describe the opened file. */

  np = (struct nfsnode *)malloc(sizeof(struct nfsnode));
  if (!np)
    {
      ferr("ERROR: Failed to allocate private data\n");
      return ENOMEM;
    }

  (void)memset_s(np, sizeof(struct nfsnode), 0, sizeof(struct nfsnode));

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Try to open an existing file at that path */

  error = nfs_fileopen(nmp, np, relpath, oflags, mode);
  if (error != OK)
    {
      /* An error occurred while trying to open the existing file. Check if
       * the open failed because the file does not exist.  That is not
       * necessarily an error; that may only mean that we have to create the
       * file.
       */

      if (error != ENOENT)
        {
          ferr("ERROR: nfs_findnode failed: %d\n", error);
          goto errout_with_mutex;
        }

      /* The file does not exist. Check if we were asked to create the file.  If
       * the O_CREAT bit is set in the oflags then we should create the file if it
       * does not exist.
       */

      if ((oflags & O_CREAT) == 0)
        {
          /* Return ENOENT if the file does not exist and we were not asked
           * to create it.
           */

          ferr("ERROR: File does not exist\n");
           error = ENOENT;
          goto errout_with_mutex;
        }

      /* Create the file */

      error = nfs_filecreate(nmp, np, relpath, oflags, mode);
      if (error != OK)
        {
          ferr("ERROR: nfs_filecreate failed: %d\n", error);
          goto errout_with_mutex;
        }
    }

  /* Initialize the file private data (only need to initialize
   * non-zero elements)
   */

  np->n_crefs = 1;

  /* Attach the private data to the struct file instance */

  filep->f_priv = np;

  /* Then insert the new instance at the head of the list in the mountpoint
   * tructure. It needs to be there (1) to handle error conditions that effect
   * all files, and (2) to inform the umount logic that we are busy.  We
   * cannot unmount the file system if this list is not empty!
   */

  np->n_next   = nmp->nm_head;
  nmp->nm_head = np;

  np->n_flags |= (NFSNODE_OPEN | NFSNODE_MODIFIED);
  np->n_oflags = oflags;

  if (filep->f_oflags & O_APPEND)
    {
      np->n_fpos = np->n_size;
    }
  else
    {
      np->n_fpos = 0;
    }
  filep->f_pos = np->n_fpos;
  np->n_filep  = filep;

  nfs_mux_release(nmp);
  return OK;

errout_with_mutex:
  if (np)
    {
      free(np);
    }

  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_close
 *
 * Description:
 *   Close a file.
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_close(FAR struct file *filep)
{
  FAR struct nfsmount *nmp;
  FAR struct nfsnode  *np;
  FAR struct nfsnode  *prev;
  FAR struct nfsnode  *curr;
  int ret;

  /* Sanity checks */

  DEBUGASSERT(filep->f_priv != NULL && filep->f_inode != NULL);

  /* Recover our private data from the struct file instance */

  nmp = (FAR struct nfsmount *) filep->f_inode->i_private;
  np  = (FAR struct nfsnode *) filep->f_priv;

  DEBUGASSERT(nmp != NULL);

  /* Get exclusive access to the mount structure. */

  nfs_mux_take(nmp);

  /* Decrement the reference count.  If the reference count would not
   * decrement to zero, then that is all we have to do.
   */

  if (np->n_crefs > 1)
    {
      np->n_crefs--;
      ret = OK;
    }

  /* There are no more references to the file structure.  Now we need to
   * free up all resources associated with the open file.
   *
   * First, find our file structure in the list of file structures
   * containted in the mount structure.
   */

  else
    {
      /* Assume file structure will not be found.  This should never happen. */

      ret = -EINVAL;

      for (prev = NULL, curr = nmp->nm_head;
           curr;
           prev = curr, curr = curr->n_next)
        {
          /* Check if this node is ours */

          if (np == curr)
            {
              /* Yes.. remove it from the list of file structures */

              if (prev)
                {
                  /* Remove from mid-list */

                  prev->n_next = np->n_next;
                }
              else
                {
                  /* Remove from the head of the list */

                  nmp->nm_head = np->n_next;
                }

              /* Then deallocate the file structure and return success */

              free(np);
              filep->f_priv = NULL;
              ret = OK;
              break;
            }
        }
    }

  nfs_mux_release(nmp);

  /* Drop the NFS file page cache if no one, except me, is working on it, to ensure
   * the close-to-open cache consistency for NFS files.
   * And because the outer "files_close" has locked the global file list already,
   * we use the nolock version here.
   */

  (void)remove_mapping_nolock(filep->f_path, filep);

  return ret;
}

/****************************************************************************
 * Name: nfs_read
 *
 * Returned Value:
 *   The (non-negative) number of bytes read on success; a negated errno
 *   value on failure.
 *
 ****************************************************************************/

static ssize_t nfs_read(FAR struct file *filep, char *buffer, size_t buflen)
{
  FAR struct nfsmount       *nmp;
  FAR struct nfsnode        *np;
  struct rpc_reply_read     *read_response;
  size_t                     readsize;
  size_t                     tmp;
  size_t                     bytesread;
  size_t                     reqlen;
  FAR uint32_t              *ptr;
  int                        error = 0;

  finfo("Read %d bytes from offset %d\n", buflen, filep->f_pos);

  /* Sanity checks */

  DEBUGASSERT(filep->f_priv != NULL && filep->f_inode != NULL);

  /* Recover our private data from the struct file instance */

  nmp = (FAR struct nfsmount *)filep->f_inode->i_private;
  np  = (FAR struct nfsnode *)filep->f_priv;

  DEBUGASSERT(nmp != NULL);

  /* Make sure that the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  fvdbg("File attributes before update, file size %d, file type %d\n", np->n_size, np->n_type);

  error = nfs_fileupdate(nmp, np, filep->f_relpath);
  if (error != OK)
    {
      fdbg("nfs_fileupdate failed: %d\n", error);
      goto errout_with_mutex;
    }

  fvdbg("File attributes after update, file size %d, file type %d\n", np->n_size, np->n_type);

  /* Get the number of bytes left in the file and truncate read count so that
   * it does not exceed the number of bytes left in the file.
   */

  tmp = np->n_size - filep->f_pos;
  if (buflen > tmp)
    {
      buflen = tmp;
      finfo("Read size truncated to %d\n", buflen);
    }

  /* Now loop until we fill the user buffer (or hit the end of the file) */

  for (bytesread = 0; bytesread < buflen; )
    {
      /* Make sure that the attempted read size does not exceed the RPC maximum */

      readsize = buflen - bytesread;
      if (readsize > nmp->nm_rsize)
        {
          readsize = nmp->nm_rsize;
        }

      /* Make sure that the attempted read size does not exceed the IO buffer size */

      tmp = SIZEOF_rpc_reply_read(readsize);
      if (tmp > nmp->nm_buflen)
        {
          readsize -= (tmp - nmp->nm_buflen);
        }

      /* Initialize the request */

      ptr     = (FAR uint32_t *)&nmp->nm_msgbuffer.read.read;
      reqlen  = 0;

      /* Copy the variable length, file handle */

      *ptr++  = txdr_unsigned((uint32_t)np->n_fhsize);
      reqlen += sizeof(uint32_t);

      memcpy(ptr, &np->n_fhandle, np->n_fhsize);
      reqlen += (int)np->n_fhsize;
      ptr    += uint32_increment((int)np->n_fhsize);

      /* Copy the file offset */

      txdr_hyper((uint64_t)filep->f_pos, ptr);
      ptr += 2;
      reqlen += 2*sizeof(uint32_t);

      /* Set the readsize */

      *ptr = txdr_unsigned(readsize);
      reqlen += sizeof(uint32_t);

      /* Perform the read */

      finfo("Reading %d bytes\n", readsize);
      nfs_statistics(NFSPROC_READ);
      error = nfs_request(nmp, NFSPROC_READ,
                          (FAR void *)&nmp->nm_msgbuffer.read, reqlen,
                          (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
      if (error)
        {
          ferr("ERROR: nfs_request failed: %d\n", error);
          goto errout_with_mutex;
        }

      /* The read was successful.  Get a pointer to the beginning of the NFS
       * response data.
       */

      read_response = (struct rpc_reply_read *)nmp->nm_iobuffer;
      readsize = fxdr_unsigned(uint32_t, read_response->read.hdr.count);

      /* Copy the read data into the user buffer */

      if (LOS_CopyFromKernel(buffer, buflen, (const void *)read_response->read.data, readsize) != 0)
        {
          error = EINVAL;
          goto errout_with_mutex;
        }

      /* Update the read state data */

      filep->f_pos += readsize;
      np->n_fpos   += readsize;
      bytesread    += readsize;
      buffer       += readsize;

      /* Check if we hit the end of file */

      if (read_response->read.hdr.eof != 0)
        {
          break;
        }
    }

  finfo("Read %d bytes\n", bytesread);
  nfs_mux_release(nmp);
  return bytesread;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_write
 *
 * Returned Value:
 *   The (non-negative) number of bytes written on success; a negated errno
 *   value on failure.
 *
 ****************************************************************************/

static ssize_t nfs_write(FAR struct file *filep, const char *buffer,
                         size_t buflen)
{
  struct nfsmount       *nmp;
  struct nfsnode        *np;
  loff_t                 f_pos;
  size_t                 writesize;
  size_t                 bufsize;
  size_t                 byteswritten;
  size_t                 reqlen;
  FAR uint32_t          *ptr;
  uint32_t               tmp;
  int                    committed = NFSV3WRITE_UNSTABLE;
  int                    error;

  /* Sanity checks */

  DEBUGASSERT(filep->f_priv != NULL && filep->f_inode != NULL);

  /* Recover our private data from the struct file instance */

  nmp = (FAR struct nfsmount *)filep->f_inode->i_private;
  np  = (FAR struct nfsnode *)filep->f_priv;

  DEBUGASSERT(nmp != NULL);

  /* Make sure that the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  if (filep->f_oflags & O_APPEND)
    {
      if (nfs_fileupdate(nmp, np, filep->f_relpath) == OK)
        {
          f_pos = np->n_size;
        }
      else
        {
          error = EAGAIN;
          goto errout_with_mutex;
        }
    }
  else
    {
      f_pos = np->n_fpos;
    }

  /* Check if the file size would exceed the range of off_t */

  if (np->n_size + buflen < np->n_size)
    {
      error = EFBIG;
      goto errout_with_mutex;
    }

  fvdbg("Write %d bytes to offset %d\n", buflen, np->n_fpos);

  /* Now loop until we send the entire user buffer */

  writesize = 0;
  for (byteswritten = 0; byteswritten < buflen; )
    {
      /* Make sure that the attempted write size does not exceed the RPC
       * maximum.
       */

      writesize = buflen - byteswritten;
      if (writesize > nmp->nm_wsize)
        {
          writesize = nmp->nm_wsize;
        }

      /* Make sure that the attempted read size does not exceed the IO
       * buffer size.
       */

      bufsize = SIZEOF_rpc_call_write(writesize);
      if (bufsize > nmp->nm_buflen)
        {
          writesize -= (bufsize - nmp->nm_buflen);
        }

      /* Initialize the request.  Here we need an offset pointer to the write
       * arguments, skipping over the RPC header.  Write is unique among the
       * RPC calls in that the entry RPC calls messasge lies in the I/O buffer
       */

      ptr     = (FAR uint32_t *)&((FAR struct rpc_call_write *)
                  nmp->nm_iobuffer)->write;
      reqlen  = 0;

      /* Copy the variable length, file handle */

      *ptr++  = txdr_unsigned((uint32_t)np->n_fhsize);
      reqlen += sizeof(uint32_t);

      memcpy(ptr, &np->n_fhandle, np->n_fhsize);
      reqlen += (int)np->n_fhsize;
      ptr    += uint32_increment((int)np->n_fhsize);

      /* Copy the file offset */

      txdr_hyper((uint64_t)f_pos, ptr);
      ptr    += 2;
      reqlen += 2*sizeof(uint32_t);

      /* Copy the count and stable values */

      *ptr++  = txdr_unsigned(writesize);
      *ptr++  = txdr_unsigned((uint32_t)committed);
      reqlen += 2*sizeof(uint32_t);

      /* Copy a chunk of the user data into the I/O buffer */

      *ptr++  = txdr_unsigned(writesize);
      reqlen += sizeof(uint32_t);
      if (LOS_CopyToKernel(ptr, writesize, buffer, writesize) != 0)
        {
          error = EINVAL;
          goto errout_with_mutex;
        }

      reqlen += uint32_alignup(writesize);

      /* Perform the write */

      nfs_statistics(NFSPROC_WRITE);
      error = nfs_request(nmp, NFSPROC_WRITE,
                          (FAR void *)nmp->nm_iobuffer, reqlen,
                          (FAR void *)&nmp->nm_msgbuffer.write,
                          sizeof(struct rpc_reply_write));
      if (error)
        {
          ferr("ERROR: nfs_request failed: %d\n", error);
          goto errout_with_mutex;
        }

      /* Get a pointer to the WRITE reply data */

      ptr = (FAR uint32_t *)&nmp->nm_msgbuffer.write.write;

      /* Parse file_wcc.  First, check if WCC attributes follow. */

      tmp = *ptr++;
      if (tmp != 0)
        {
          /* Yes.. WCC attributes follow.  But we just skip over them. */

          ptr += uint32_increment(sizeof(struct wcc_attr));
        }

      /* Check if normal file attributes follow */

      tmp = *ptr++;
      if (tmp != 0)
        {
          /* Yes.. Update the cached file status in the file structure. */

          nfs_attrupdate(np, (FAR struct nfs_fattr *)ptr);
          ptr += uint32_increment(sizeof(struct nfs_fattr));
        }

      /* Get the count of bytes actually written */

      tmp = fxdr_unsigned(uint32_t, *ptr);
      ptr++;

      if (tmp < 1 || tmp > writesize)
        {
          error = EIO;
          goto errout_with_mutex;
        }

      writesize = tmp;
      f_pos += writesize;
      filep->f_pos = f_pos;
      np->n_fpos = f_pos;

      /* Update the read state data */

      if (filep->f_pos > (loff_t)np->n_size)
        {
          np->n_size = f_pos;
        }
      byteswritten += writesize;
      buffer       += writesize;
    }

  nfs_mux_release(nmp);
  return byteswritten;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}


static off_t nfs_seek(FAR struct file *filep, off_t offset, int whence)
{
  FAR struct nfsmount       *nmp;
  FAR struct nfsnode        *np;
  int                        error;
  off_t                      position;

  fvdbg("Seek started, offset %d whence %d current file pos %lld\n", offset, whence, filep->f_pos);

  /* Sanity checks */

  DEBUGASSERT(filep->f_priv != NULL && filep->f_inode != NULL);

  /* Recover our private data from the struct file instance */

  nmp = (FAR struct nfsmount *)filep->f_inode->i_private;
  np  = (FAR struct nfsnode *)filep->f_priv;

  DEBUGASSERT(nmp != NULL);

  /* Make sure that the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      fdbg("nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }


  filep->f_pos = np->n_fpos;
  switch (whence)
    {
    case SEEK_SET: /* The offset is set to offset bytes. */
      position = offset;
      break;

    case SEEK_CUR: /* The offset is set to its current location plus offset bytes. */
      position = offset + (off_t)np->n_fpos;
      break;

    case SEEK_END: /* The offset is set to the size of the file plus offset bytes. */
      position = offset + np->n_size;
      break;

    default:
      error = EINVAL;
      goto errout_with_mutex;
    }

  /* Attempts to set the position beyound the end of file will
   * work if the file is open for write access.
   */

  if ((position > (off_t)np->n_size) && ((np->n_oflags & O_WRONLY) == 0) &&
      ((np->n_oflags & O_RDWR) == 0))
    {
      position = np->n_size;
    }

  /* position less than 0 should be reset to 0 */

  if (position < 0)
    {
      position = 0;
    }

  np->n_fpos = (loff_t)position;
  filep->f_pos = np->n_fpos;
  if (position > (off_t)np->n_size)
    {
      np->n_size = (loff_t)position;
    }

  fvdbg("Seek finished, offset %d whence %d current file pos %lld\n", offset, whence, filep->f_pos);
  nfs_mux_release(nmp);
  return (off_t)filep->f_pos;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

static loff_t nfs_seek64(FAR struct file *filep, loff_t offset, int whence)
{
  FAR struct nfsmount       *nmp;
  FAR struct nfsnode        *np;
  int                        error;
  loff_t                     position;

  fvdbg("Seek started, offset %d whence %d current file pos %d\n", offset, whence, filep->f_pos);

  /* Sanity checks */

  DEBUGASSERT(filep->f_priv != NULL && filep->f_inode != NULL);

  /* Recover our private data from the struct file instance */

  nmp = (FAR struct nfsmount *)filep->f_inode->i_private;
  np  = (FAR struct nfsnode *)filep->f_priv;

  DEBUGASSERT(nmp != NULL);

  /* Make sure that the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      fdbg("nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  filep->f_pos = np->n_fpos;
  switch (whence)
    {
    case SEEK_SET: /* The offset is set to offset bytes. */
      position = offset;
      break;

    case SEEK_CUR: /* The offset is set to its current location plus offset bytes. */
      position = offset + np->n_fpos;
      break;

    case SEEK_END: /* The offset is set to the size of the file plus offset bytes. */
      position = offset + np->n_size;
      break;

    default:
      error = EINVAL;
      goto errout_with_mutex;
    }

  /* Attempts to set the position beyound the end of file will
   * work if the file is open for write access.
   */

  if ((position > (off_t)np->n_size) && ((np->n_oflags & O_WRONLY) == 0) &&
      ((np->n_oflags & O_RDWR) == 0))
    {
      position = np->n_size;
    }

  /* position less than 0 should be reset to 0 */

  if (position < 0)
    {
      position = 0;
    }

  np->n_fpos = position;
  filep->f_pos = np->n_fpos;
  if (position > (loff_t)np->n_size)
    {
      np->n_size = (uint64_t)position;
    }

  fvdbg("Seek finished, offset %d whence %d current file pos %d\n", offset, whence, filep->f_pos);
  nfs_mux_release(nmp);
  return filep->f_pos;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_dup
 *
 * Description:
 *   Duplicate open file data in the new file structure.
 *
 ****************************************************************************/

static int nfs_dup(FAR const struct file *oldp, FAR struct file *newp)
{
  struct nfsmount *nmp;
  FAR struct nfsnode *np;
  int error;

  finfo("Dup %p->%p\n", oldp, newp);

  /* Sanity checks */

  DEBUGASSERT(oldp->f_priv != NULL && oldp->f_inode != NULL);

  /* Recover our private data from the struct file instance */

  nmp = (FAR struct nfsmount *)oldp->f_inode->i_private;
  np  = (FAR struct nfsnode *)oldp->f_priv;

  DEBUGASSERT(nmp != NULL);

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      nfs_mux_release(nmp);
      return -error;
    }

  /* Increment the reference count on the NFS node structure */

  DEBUGASSERT(np->n_crefs < 0xff);
  np->n_crefs++;

  /* And save this as the file data for the new node */

  newp->f_priv = np;

  nfs_mux_release(nmp);
  return OK;
}

/****************************************************************************
 * Name: nfs_opendir
 *
 * Description:
 *   Open a directory for read access
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_opendir(struct inode *mountpt, const char *relpath,
                       struct fs_dirent_s *dir)
{
  struct nfsmount *nmp;
  struct file_handle fhandle;
  struct nfs_fattr obj_attributes;
  struct nfsdir_s *nfs_dir;
  uint32_t objtype;
  int error;

  finfo("relpath: \"%s\"\n", relpath ? relpath : "NULL");

  /* Sanity checks */

  DEBUGASSERT(mountpt != NULL && mountpt->i_private != NULL && dir);

  /* Recover our private data from the inode instance */

  nmp = mountpt->i_private;

  /* Make sure that the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Find the NFS node associate with the path */

  error = nfs_findnode(nmp, relpath, &fhandle, &obj_attributes, NULL);
  if (error != OK)
    {
      ferr("ERROR: nfs_findnode failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* The entry is a directory */

  objtype = fxdr_unsigned(uint32_t, obj_attributes.fa_type);
  if (objtype != NFDIR)
    {
      ferr("ERROR:  Not a directory, type=%d\n", objtype);
      error = ENOTDIR;
      goto errout_with_mutex;
    }

  /* Save the directory information in struct fs_dirent_s so that it can be
   * used later when readdir() is called.
   */

  nfs_dir = (struct nfsdir_s *)malloc(sizeof(struct nfsdir_s));
  if (!nfs_dir)
    {
      error = ENOMEM;
      goto errout_with_mutex;
    }

  nfs_dir->nfs_fhsize = (uint8_t)fhandle.length;
  nfs_dir->nfs_cookie[0] = 0;
  nfs_dir->nfs_cookie[1] = 0;

  DEBUGASSERT(fhandle.length <= DIRENT_NFS_MAXHANDLE);
  (void)memcpy_s(nfs_dir->nfs_fhandle, DIRENT_NFS_MAXHANDLE, &fhandle.handle, DIRENT_NFS_MAXHANDLE);

  dir->u.fs_dir = (fs_dir_s)nfs_dir;
  error = OK;

  nfs_dir->nfs_next = nmp->nm_dir;
  nmp->nm_dir = nfs_dir;
  nfs_dir->nfs_dir = dir;
  nfs_dir->nfs_entries = NULL;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

static int nfs_closedir(FAR struct inode *mountpt, FAR struct fs_dirent_s *dir)
{
  struct nfsmount      *nmp;
  FAR struct nfsdir_s  *prev;
  FAR struct nfsdir_s  *curr;
  struct nfsdir_s      *nfs_dir;
  struct entry3        *entry_pos;
  int                  ret;

  /* Sanity checks */

  DEBUGASSERT(mountpt != NULL && mountpt->i_private != NULL && dir);

  /* Recover our private data from the inode instance */

  nmp = (struct nfsmount *)mountpt->i_private;

  nfs_dir = (struct nfsdir_s *)(dir->u.fs_dir);

  DEBUGASSERT(nmp != NULL);

  /* Get exclusive access to the mount structure. */

  nfs_mux_take(nmp);

  for (entry_pos = nfs_dir->nfs_entries; entry_pos != NULL; entry_pos = nfs_dir->nfs_entries)
    {
      nfs_dir->nfs_entries = entry_pos->next;
      NFS_DIR_ENTRY_FREE(entry_pos);
    }

  /* Assume file structure will not be found.  This should never happen. */

  ret = -EINVAL;

  for (prev = (struct nfsdir_s  *)NULL, curr = nmp->nm_dir;
       curr;
       prev = curr, curr = curr->nfs_next)
    {
      /* Check if this node is ours */

      if (nfs_dir == curr)
        {
          /* Yes.. remove it from the list of file structures */

          if (prev)
            {
              /* Remove from mid-list */

              prev->nfs_next = nfs_dir->nfs_next;
            }
          else
            {
              /* Remove from the head of the list */

              nmp->nm_dir= nfs_dir->nfs_next;
            }

          /* Then deallocate the file structure and return success */

          free(nfs_dir);
          nfs_dir = NULL;
          ret = OK;
          break;
        }
    }
  nfs_mux_release(nmp);

  return ret; /*lint !e438*/
}

/****************************************************************************
 * Name: nfs_readdir
 *
 * Description: Read from directory
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_readdir(struct inode *mountpt, struct fs_dirent_s *dir)
{
  struct nfsmount *nmp;
  struct file_handle fhandle;
  struct nfs_fattr obj_attributes;
  struct nfsdir_s *nfs_dir;
  struct entry3   *entry;
  struct entry3   *entry_pos;

  /* Use 2 cookies */

  uint32_t cookies[2];
  uint32_t tmp;
  uint32_t *ptr;
  size_t d_name_size;
  int reqlen;
  int error = 0;

  finfo("Entry\n");

  /* Sanity checks */

  DEBUGASSERT(mountpt != NULL && mountpt->i_private != NULL);

  /* Recover our private data from the inode instance */

  nmp = mountpt->i_private;

  /* Make sure that the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Request a block directory entries, copying directory information from
   * the dirent structure.
   */

  nfs_dir = (struct nfsdir_s *)dir->u.fs_dir;
  cookies[0] = 0;
  cookies[1] = 0;

  if (!nfs_dir->nfs_entries)
    {
      entry_pos = nfs_dir->nfs_entries;
      do
        {
          ptr     = (FAR uint32_t *)&nmp->nm_msgbuffer.readdir.readdir;
          reqlen  = 0;

          /* Copy the variable length, directory file handle */

          *ptr++  = txdr_unsigned((uint32_t)nfs_dir->nfs_fhsize);
          reqlen += sizeof(uint32_t);

          (void)memcpy_s(ptr, nfs_dir->nfs_fhsize, nfs_dir->nfs_fhandle, nfs_dir->nfs_fhsize);
          reqlen += (int)nfs_dir->nfs_fhsize;
          ptr    += uint32_increment((int)nfs_dir->nfs_fhsize);

          /* Cookie and cookie verifier */

          ptr[0] = cookies[0];
          ptr[1] = cookies[1];
          ptr    += 2;
          reqlen += 2 * sizeof(uint32_t);

          (void)memcpy_s(ptr, DIRENT_NFS_VERFLEN, nfs_dir->nfs_verifier, DIRENT_NFS_VERFLEN);
          ptr    += uint32_increment(DIRENT_NFS_VERFLEN);
          reqlen += DIRENT_NFS_VERFLEN;

          /* Number of directory entries (We currently only process one entry at a time) */

          *ptr    = txdr_unsigned((uint32_t)nmp->nm_readdirsize);
          reqlen += sizeof(uint32_t);

          /* And read the directory */

          nfs_statistics(NFSPROC_READDIR);
          error = nfs_request(nmp, NFSPROC_READDIR,
                              (FAR void *)&nmp->nm_msgbuffer.readdir, reqlen,
                              (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
          if (error != OK)
            {
              fdbg("ERROR: nfs_request failed: %d\n", error);
              goto errout_with_mutex;
            }

          /* A new group of entries was successfully read.  Process the
           * information contained in the response header.  This information
           * includes:
           *
           * 1) Attributes follow indication - 4 bytes
           * 2) Directory attributes         - sizeof(struct nfs_fattr)
           * 3) Cookie verifier              - NFSX_V3COOKIEVERF bytes
           * 4) Values follows indication    - 4 bytes
           */

          ptr = (uint32_t *)&((FAR struct rpc_reply_readdir *)nmp->nm_iobuffer)->readdir;

          /* Check if attributes follow, if 0 so Skip over the attributes */

          tmp = *ptr++;
          if (tmp != 0)
            {
              /* Attributes are not currently used */

              ptr += uint32_increment(sizeof(struct nfs_fattr));
            }


          /* Save the verification cookie */

          (void)memcpy_s(nfs_dir->nfs_verifier, DIRENT_NFS_VERFLEN, ptr, DIRENT_NFS_VERFLEN);
          ptr += uint32_increment(DIRENT_NFS_VERFLEN);

          /* Check if values follow.  If no values follow, then the EOF indication
           * will appear next.
           */

          tmp = *ptr++;
          if (tmp == 0)
            {
              /* No values follow, then the reply should consist only of a 4-byte
               * end-of-directory indication.
               */

              tmp = *ptr++;
              if (tmp != 0)
                {
                  fvdbg("End of directory\n");
                  error = ENOENT;
                }

              /* What would it mean if there were not data and we not at the end of
               * file?
               */

              else
                {
                  fvdbg("No data but not end of directory?\n");
                  error = EAGAIN;
                }

              goto errout_with_mutex;
            }


          /* If we are not at the end of the directory listing, then a set of entries
           * will follow the header.  Each entry is of the form:
           *
           *    File ID (8 bytes)
           *    Name length (4 bytes)
           *    Name string (varaiable size but in multiples of 4 bytes)
           *    Cookie (8 bytes)
           *    next entry (4 bytes)
           */

          do
            {
              NFS_DIR_ENTRY_MALLOC(entry);

              /* There is an entry. Skip over the file ID and point to the length */

              entry->file_id[0] = *ptr++;
              entry->file_id[1] = *ptr++; /*lint !e662 !e661*/


              /* Get the length and point to the name */

              tmp    = *ptr++; /*lint !e662 !e661*/
              entry->name_len = fxdr_unsigned(uint32_t, tmp);
              entry->contents = (uint8_t *)malloc(entry->name_len + 1);
              if (!entry->contents)
                {
                  free(entry);
                  entry = NULL;
                  goto errout_with_memory;
                }
              (void)memset_s(entry->contents, entry->name_len + 1, 0, entry->name_len + 1);

              error = strncpy_s((char *)entry->contents, entry->name_len + 1, (const char *)ptr, entry->name_len);
              if (error != EOK)
                {
                  free(entry->contents);
                  entry->contents = NULL;
                  free(entry);
                  entry = NULL;
                  error = ENOBUFS;
                  goto errout_with_memory;
                }
              /* Increment the pointer past the name (allowing for padding). ptr
               * now points to the cookie.
               */

              ptr += uint32_increment(entry->name_len);

              /* Save the cookie and increment the pointer to the next entry */

              entry->cookie[0] = *ptr++;
              entry->cookie[1] = *ptr++;

              /* Get the file attributes associated with this name and return
               * the file type.
               */

              if (strcmp((char *)entry->contents, ".") == 0 || strcmp((char *)entry->contents, "..") == 0)
                {
                  NFS_DIR_ENTRY_FREE(entry);
                  continue;
                }

              if (!nfs_dir->nfs_entries)
                {
                  entry_pos = entry;
                  nfs_dir->nfs_entries = entry;
                }
              else
                {
                  entry_pos->next = entry;
                  entry_pos = entry;
                }
            }
          while (*ptr++);
          if (entry_pos)
            {
              cookies[0] = entry_pos->cookie[0];
              cookies[1] = entry_pos->cookie[1];
            }

        }
      while (!(*ptr));

      fvdbg("End of directory\n");
      if (!nfs_dir->nfs_entries)
        {
          error = ENOENT;
          goto errout_with_mutex;
        }

      NFS_DIR_ENTRY_MALLOC(entry);

      /* There is an entry. Skip over the file ID and point to the length */

      entry->file_id[0] = (uint32_t)EOF;
      if (!entry_pos)
        {
          error = ENOENT;
          NFS_DIR_ENTRY_FREE(entry);
          goto errout_with_mutex;
        }
      entry_pos->next = entry;
      entry_pos = entry;
    }

  entry_pos = nfs_dir->nfs_entries;
  if (nfs_dir->nfs_entries->file_id[0] == (uint32_t)EOF)
    {
      fvdbg("End of directory\n");
      error = ENOENT;
      free(nfs_dir->nfs_entries);
      nfs_dir->nfs_entries = NULL;
      goto errout_with_mutex;
    }

  d_name_size = sizeof(dir->fd_dir.d_name);
  error = memcpy_s(dir->fd_dir.d_name, d_name_size, (const char *)entry_pos->contents, (size_t)entry_pos->name_len);
  if (error != EOK)
    {
      error = ENOBUFS;
      goto errout_with_memory;
    }
  if (entry_pos->name_len >= d_name_size)
    {
      dir->fd_dir.d_name[d_name_size - 1] = '\0';
    }
  else
    {
      dir->fd_dir.d_name[entry_pos->name_len] = '\0';
    }

  nfs_dir->nfs_entries = entry_pos->next;
  NFS_DIR_ENTRY_FREE(entry_pos);

  fvdbg("name: \"%s\"\n", dir->fd_dir.d_name);
  fhandle.length = (uint32_t)nfs_dir->nfs_fhsize;
  (void)memcpy_s(&fhandle.handle, DIRENT_NFS_MAXHANDLE, nfs_dir->nfs_fhandle, DIRENT_NFS_MAXHANDLE);

  error = nfs_lookup(nmp, dir->fd_dir.d_name, &fhandle, &obj_attributes, NULL);
  if (error != OK)
    {
      ferr("ERROR: nfs_lookup failed: %d\n", error);
      goto errout_with_memory;
    }

  /* Set the dirent file type */

  tmp = fxdr_unsigned(uint32_t, obj_attributes.fa_type);
  switch (tmp)
    {
    default:
    case NFNON:        /* Unknown type */
    case NFSOCK:       /* Socket */
    case NFLNK:        /* Symbolic link */
      break;

    case NFREG:        /* Regular file */
      dir->fd_dir.d_type = DT_REG;
      break;

    case NFDIR:        /* Directory */
      dir->fd_dir.d_type = DT_DIR;
      break;

    case NFBLK:        /* Block special device file */
      dir->fd_dir.d_type = DT_BLK;
      break;

    case NFFIFO:       /* Named FIFO */
    case NFCHR:        /* Character special device file */
      dir->fd_dir.d_type = DT_CHR;
      break;
    }
  dir->fd_dir.d_off = dir->fd_position;
  dir->fd_dir.d_reclen = (uint16_t)sizeof(struct dirent);
  finfo("type: %d->%d\n", (int)tmp, dir->fd_dir.d_type);

  nfs_mux_release(nmp);
  return OK;

errout_with_memory:
  for (entry_pos = nfs_dir->nfs_entries; entry_pos != NULL; entry_pos = nfs_dir->nfs_entries)
    {
      nfs_dir->nfs_entries = entry_pos->next;
      NFS_DIR_ENTRY_FREE(entry_pos);
    }
errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_rewinddir
 *
 * Description:
 *  Reset the directory traveral logic to the first entry in the open
 *  directory.
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_rewinddir(FAR struct inode *mountpt, FAR struct fs_dirent_s *dir)
{
  struct nfsmount *nmp;
  struct nfsdir_s *nfs_dir;
  struct entry3   *entry_pos;
  finfo("Entry\n");

  /* Sanity checks */

  DEBUGASSERT(mountpt != NULL && mountpt->i_private != NULL && dir != NULL);

  nmp = (struct nfsmount *)mountpt->i_private;
  nfs_mux_take(nmp);

  /* Reset the NFS-specific portions of dirent structure, retaining only the
   * file handle.
   */

  nfs_dir = (struct nfsdir_s *)dir->u.fs_dir;
  (void)memset_s(nfs_dir->nfs_verifier, DIRENT_NFS_VERFLEN, 0, DIRENT_NFS_VERFLEN);
  nfs_dir->nfs_cookie[0] = 0;
  nfs_dir->nfs_cookie[1] = 0;
  for (entry_pos = nfs_dir->nfs_entries; entry_pos != NULL; entry_pos = nfs_dir->nfs_entries)
    {
      nfs_dir->nfs_entries = entry_pos->next;
      NFS_DIR_ENTRY_FREE(entry_pos);
    }
  nfs_mux_release(nmp);
  return OK;
}

/****************************************************************************
 * Name: nfs_decode_args
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void nfs_decode_args(FAR struct nfs_mount_parameters *nprmt,
                            FAR struct nfs_args *argp)
{
  int maxio;

  /* Get the selected timeout value */

  if ((argp->flags & NFSMNT_TIMEO) != 0 && argp->timeo > 0)
    {
      uint32_t tmp = ((uint32_t)argp->timeo * NFS_HZ + 5) / 10;
      if (tmp < NFS_MINTIMEO)
        {
          tmp = NFS_MINTIMEO;
        }
      else if (tmp > NFS_MAXTIMEO)
        {
          tmp = NFS_MAXTIMEO;
        }

      nprmt->timeo = tmp;
    }

  /* Get the selected retransmission count */

  if ((argp->flags & NFSMNT_RETRANS) != 0 && argp->retrans > 1)
    {
      if  (argp->retrans < NFS_MAXREXMIT)
        {
          nprmt->retry = argp->retrans;
        }
      else
        {
          nprmt->retry = NFS_MAXREXMIT;
        }
    }

  if ((argp->flags & NFSMNT_SOFT) == 0)
    {
      nprmt->retry = NFS_MAXREXMIT + 1;  /* Past clip limit */
    }

  /* Get the maximum amount of data that can be transferred in one packet */

  if ((argp->sotype == SOCK_DGRAM) != 0)
    {
      maxio = NFS_MAXDGRAMDATA;
    }
  else
    {
      ferr("ERROR: Only SOCK_DRAM is supported\n");
      maxio = NFS_MAXDATA;
    }

  /* Get the maximum amount of data that can be transferred in one write transfer */

  if ((argp->flags & NFSMNT_WSIZE) != 0 && argp->wsize > 0)
    {
      nprmt->wsize = argp->wsize;

      /* Round down to multiple of blocksize */

      nprmt->wsize &= ~(NFS_FABLKSIZE - 1);
      if (nprmt->wsize <= 0)
        {
          nprmt->wsize = NFS_FABLKSIZE;
        }
    }

  if (nprmt->wsize > maxio)
    {
      nprmt->wsize = maxio;
    }

  if (nprmt->wsize > MAXBSIZE)
    {
      nprmt->wsize = MAXBSIZE;
    }

  /* Get the maximum amount of data that can be transferred in one read transfer */

  if ((argp->flags & NFSMNT_RSIZE) != 0 && argp->rsize > 0)
    {
      nprmt->rsize = argp->rsize;

      /* Round down to multiple of blocksize */

      nprmt->rsize &= ~(NFS_FABLKSIZE - 1);
      if (nprmt->rsize <= 0)
        {
          nprmt->rsize = NFS_FABLKSIZE;
        }
    }

  if (nprmt->rsize > maxio)
    {
      nprmt->rsize = maxio;
    }

  if (nprmt->rsize > MAXBSIZE)
    {
      nprmt->rsize = MAXBSIZE;
    }

  /* Get the maximum amount of data that can be transferred in directory transfer */

  if ((argp->flags & NFSMNT_READDIRSIZE) != 0 && argp->readdirsize > 0)
    {
      nprmt->readdirsize = argp->readdirsize;

      /* Round down to multiple of blocksize */

      nprmt->readdirsize &= ~(NFS_DIRBLKSIZ - 1);
      if (nprmt->readdirsize < NFS_DIRBLKSIZ)
        {
          nprmt->readdirsize = NFS_DIRBLKSIZ;
        }
    }
  else if (argp->flags & NFSMNT_RSIZE)
    {
      nprmt->readdirsize = nprmt->rsize;
    }

  if (nprmt->readdirsize > maxio)
    {
      nprmt->readdirsize = maxio;
    }
}

/****************************************************************************
 * Name: nfs_bind
 *
 * Description:
 *  This implements a portion of the mount operation. This function allocates
 *  and initializes the mountpoint private data and gets mount information
 *  from the NFS server.  The final binding of the private data (containing
 *  NFS server mount information) to the  mountpoint is performed by mount().
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_bind(FAR struct inode *blkdriver, FAR const void *data,
                    FAR void **handle, FAR const char *relpath)
{
  FAR struct nfs_args        *argp = (FAR struct nfs_args *)data;
  FAR struct nfsmount        *nmp;
  struct rpcclnt             *rpc;
  struct rpc_call_fs          getattr;
  struct rpc_reply_getattr    resok;
  struct nfs_mount_parameters nprmt;
  uint32_t                    buflen;
  uint32_t                    pathlen;
  uint32_t                    tmp;
  int                         error = 0;
  pthread_mutexattr_t attr;

  DEBUGASSERT(data && handle);

  /* Set default values of the parameters.  These may be overridden by
   * settings in the argp->flags.
   */

  nprmt.timeo       = NFS_TIMEO;
  nprmt.retry       = NFS_RETRANS;
  nprmt.wsize       = NFS_WSIZE;
  nprmt.rsize       = NFS_RSIZE;
  nprmt.readdirsize = NFS_READDIRSIZE;

  nfs_decode_args(&nprmt, argp);

  /* Determine the size of a buffer that will hold one RPC data transfer.
   * First, get the maximum size of a read and a write transfer.
   */

  pathlen = strlen(argp->path);
  if (pathlen >= NFS_MOUNT_PATH_MAX_SIZE) {
      return -ENAMETOOLONG;
  }

  buflen = SIZEOF_rpc_call_write(nprmt.wsize);
  tmp    = SIZEOF_rpc_reply_read(nprmt.rsize);

  /* The buffer size will be the maximum of those two sizes */

  if (tmp > buflen)
    {
      buflen = tmp;
    }

  /* But don't let the buffer size exceed the MSS of the socket type.
   *
   * In the case where there are multiple network devices with different
   * link layer protocols, each network device may support a different
   * UDP MSS value.  Here we arbitrarily select the minimum MSS for
   * that case.
   */

  /* Create an instance of the mountpt state structure */

  nmp = (FAR struct nfsmount *)malloc(SIZEOF_nfsmount(buflen));
  if (!nmp)
    {
      ferr("ERROR: Failed to allocate mountpoint structure\n");
      return -ENOMEM;
    }

  (void)memset_s(nmp, SIZEOF_nfsmount(buflen), 0, SIZEOF_nfsmount(buflen));

  /* Save the allocated I/O buffer size */

  nmp->nm_buflen = (uint16_t)buflen;

  nmp->nm_so = -1;

  /* Initialize the allocated mountpt state structure. */

  (void)pthread_mutexattr_init(&attr);
  (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  error = pthread_mutex_init(&nmp->nm_mux, &attr);
  if (error)
    {
      return -error;
    }

  /* Initialize NFS */

  nfs_true = txdr_unsigned(TRUE);
  nfs_false = txdr_unsigned(FALSE);
  nfs_xdrneg1 = txdr_unsigned(-1);

  rpcclnt_init();

  /* Set initial values of other fields */

  nmp->nm_timeo       = nprmt.timeo;
  nmp->nm_retry       = nprmt.retry;
  nmp->nm_wsize       = nprmt.wsize;
  nmp->nm_rsize       = nprmt.rsize;
  nmp->nm_readdirsize = nprmt.readdirsize;
  nmp->nm_fhsize      = NFSX_V3FHMAX;

  (void)strncpy_s(nmp->nm_path, sizeof(nmp->nm_path), argp->path, pathlen);
  (void)memcpy_s(&nmp->nm_nam, sizeof(struct sockaddr), &argp->addr, argp->addrlen);

  /* Set up the sockets and per-host congestion */

  nmp->nm_sotype  = argp->sotype;

  if (nmp->nm_sotype == SOCK_DGRAM || nmp->nm_sotype == SOCK_STREAM)
    {
      /* Connection-less... connect now */

      /* Create an instance of the rpc state structure */

      rpc = (struct rpcclnt *)malloc(sizeof(struct rpcclnt));
      if (!rpc)
        {
          ferr("ERROR: Failed to allocate rpc structure\n");
          error = ENOMEM;
          goto bad;
        }

      (void)memset_s(rpc, sizeof(struct rpcclnt), 0, sizeof(struct rpcclnt));

      finfo("Connecting\n");

      /* Translate nfsmnt flags -> rpcclnt flags */

      rpc->rc_path       = nmp->nm_path;
      rpc->rc_name       = &nmp->nm_nam;
      rpc->rc_sotype     = nmp->nm_sotype;
      rpc->rc_retry      = nmp->nm_retry;
      rpc->rc_so         = -1;

      nmp->nm_rpcclnt    = rpc;

      error = rpcclnt_connect(nmp->nm_rpcclnt);
      if (error != OK)
        {
          ferr("ERROR: nfs_connect failed: %d\n", error);
          goto bad;
        }
    }

  nmp->nm_mounted        = true;
  nmp->nm_so             = nmp->nm_rpcclnt->rc_so;
  nmp->nm_head           = NULL;
  nmp->nm_dir            = NULL;
  nmp->nm_fhsize         = nmp->nm_rpcclnt->rc_fhsize;
  memcpy(&nmp->nm_fh, &nmp->nm_rpcclnt->rc_fh, sizeof(nfsfh_t));

  /* Get the file attributes */

  getattr.fs.fsroot.length = txdr_unsigned(nmp->nm_fhsize);
  memcpy(&getattr.fs.fsroot.handle, &nmp->nm_fh, sizeof(nfsfh_t));

  error = nfs_request(nmp, NFSPROC_GETATTR,
                      (FAR void *)&getattr, /* sizeof(struct FS3args) */
                      (sizeof(getattr.fs.fsroot.length) + nmp->nm_fhsize),
                      (FAR void *)&resok, sizeof(struct rpc_reply_getattr));
  if (error)
    {
      ferr("ERROR: nfs_request failed: %d\n", error);
      goto bad;
    }

  /* Save the file attributes */

  memcpy(&nmp->nm_fattr, &resok.attr, sizeof(struct nfs_fattr));

  /* Mounted! */

  *handle = (FAR void *)nmp;
  nfs_mux_release(nmp);

  finfo("Successfully mounted\n");
  return OK;

bad:
  if (nmp)
    {
      /* Disconnect from the server */

      if (nmp->nm_rpcclnt)
        {
          rpcclnt_disconnect(nmp->nm_rpcclnt);
          free(nmp->nm_rpcclnt);
          nmp->nm_rpcclnt = NULL;
        }

      /* Free connection-related resources */

      (void)pthread_mutex_destroy(&nmp->nm_mux);

      free(nmp);
      nmp = NULL;
    }

  return -error; /*lint !e438*/
}

/****************************************************************************
 * Name: nfs_unbind
 *
 * Description: This implements the filesystem portion of the umount
 *   operation.
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_unbind(FAR void *handle, FAR struct inode **blkdriver)
{
  FAR struct nfsmount *nmp = (FAR struct nfsmount *)handle;
  int error;

  finfo("Entry\n");
  DEBUGASSERT(nmp);

  /* Get exclusive access to the mount structure */

  nfs_mux_take(nmp);

  /* Are there any open files?  We can tell if there are open files by looking
   * at the list of file structures in the mount structure.  If this list
   * not empty, then there are open files and we cannot unmount now (or a
   * crash is sure to follow).
   */

  if (nmp->nm_head != NULL || nmp->nm_dir != NULL)
    {
      ferr("ERROR;  There are open files: %p or directories: %p\n", nmp->nm_head, nmp->nm_dir);

      /* This implementation currently only supports unmounting if there are
       * no open file references.
       */

      error = EBUSY;
      goto errout_with_mutex;
    }

  /* No open file... Umount the file system. */

  error = rpcclnt_umount(nmp->nm_rpcclnt);
  if (error)
    {
      ferr("ERROR: rpcclnt_umount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Disconnect from the server */

  rpcclnt_disconnect(nmp->nm_rpcclnt);

  /* And free any allocated resources */

  nfs_mux_release(nmp);
  (void)pthread_mutex_destroy(&nmp->nm_mux);
  free(nmp->nm_rpcclnt);
  nmp->nm_rpcclnt = NULL;
  free(nmp);
  nmp = NULL;

  return -error;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_fsinfo
 *
 * Description:
 *   Return information about root directory.
 *
 * Returned Value:
 *   0 on success; positive errno value on failure
 *
 * Assumptions:
 *   The caller has exclusive access to the NFS mount structure
 *
 ****************************************************************************/

int nfs_fsinfo(FAR struct nfsmount *nmp)
{
  struct rpc_call_fs fsinfo;
  struct rpc_reply_fsinfo fsp;
  struct nfs_fsinfo *rep_info;
  uint32_t pref;
  uint32_t max;
  int error = 0;

  fsinfo.fs.fsroot.length = txdr_unsigned(nmp->nm_fhsize);
  fsinfo.fs.fsroot.handle = nmp->nm_fh;

  /* Request FSINFO from the server */

  nfs_statistics(NFSPROC_FSINFO);
  error = nfs_request(nmp, NFSPROC_FSINFO,
                      (FAR void *)&fsinfo, sizeof(struct FS3args),
                      (FAR void *)&fsp, sizeof(struct rpc_reply_fsinfo));
  if (error)
    {
      return error;
    }

  if (txdr_unsigned(fsp.fsinfo.obj_attributes.obj_attribute_follow) == 1)
    {
      rep_info = (struct nfs_fsinfo *)&fsp.fsinfo.fs_rtmax;
    }
  else
    {
      rep_info = (struct nfs_fsinfo *)((void *)(&fsp.fsinfo.obj_attributes.attributes));
    }

  /* Save the root file system attributes */

#if 0
  memcpy(&nmp->nm_fattr. &fsp.obj_attributes, sizeof(struct nfs_fattr));
#endif

  pref = fxdr_unsigned(uint32_t, rep_info->fs_wtpref);
  if (pref < nmp->nm_wsize)
    {
      nmp->nm_wsize = (pref + NFS_FABLKSIZE - 1) & ~(NFS_FABLKSIZE - 1);
    }

  max = fxdr_unsigned(uint32_t, rep_info->fs_wtmax);
  if (max < nmp->nm_wsize)
    {
      nmp->nm_wsize = max & ~(NFS_FABLKSIZE - 1);
      if (nmp->nm_wsize == 0)
        {
          nmp->nm_wsize = max;
        }
    }

  pref = fxdr_unsigned(uint32_t, rep_info->fs_rtpref);
  if (pref < nmp->nm_rsize)
    {
      nmp->nm_rsize = (pref + NFS_FABLKSIZE - 1) & ~(NFS_FABLKSIZE - 1);
    }

  max = fxdr_unsigned(uint32_t, rep_info->fs_rtmax);
  if (max < nmp->nm_rsize)
    {
      nmp->nm_rsize = max & ~(NFS_FABLKSIZE - 1);
      if (nmp->nm_rsize == 0)
        {
          nmp->nm_rsize = max;
        }
    }

  pref = fxdr_unsigned(uint32_t, rep_info->fs_dtpref);
  if (pref < nmp->nm_readdirsize)
    {
      nmp->nm_readdirsize = (pref + NFS_DIRBLKSIZ - 1) & ~(NFS_DIRBLKSIZ - 1);
    }

  if (max < nmp->nm_readdirsize)
    {
      nmp->nm_readdirsize = max & ~(NFS_DIRBLKSIZ - 1);
      if (nmp->nm_readdirsize == 0)
        {
          nmp->nm_readdirsize = max;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: nfs_statfs
 *
 * Description:
 *   Return filesystem statistics
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_statfs(FAR struct inode *mountpt, FAR struct statfs *sbp)
{
  FAR struct nfsmount *nmp;
  FAR struct rpc_call_fs *fsstat;
  FAR struct rpc_reply_fsstat *sfp;
  FAR struct nfs_statfs_ctx  *stfp;
  int error = 0;
  uint64_t tquad;

  /* Sanity checks */

  DEBUGASSERT(mountpt && mountpt->i_private);

  /* Get the mountpoint private data from the inode structure */

  nmp = (FAR struct nfsmount *)mountpt->i_private;

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Fill in the statfs info */

  sbp->f_type = NFS_SUPER_MAGIC;

  error = nfs_fsinfo(nmp);
  if (error)
    {
      fdbg("ERROR: nfs_fsinfo failed: %d\n", error);
      goto errout_with_mutex;
    }

  fsstat = &nmp->nm_msgbuffer.fsstat;
  fsstat->fs.fsroot.length = txdr_unsigned(nmp->nm_fhsize);
  memcpy(&fsstat->fs.fsroot.handle, &nmp->nm_fh, sizeof(nfsfh_t));

  nfs_statistics(NFSPROC_FSSTAT);
  error = nfs_request(nmp, NFSPROC_FSSTAT,
                      (FAR void *)fsstat, sizeof(struct FS3args),
                      (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
  if (error)
    {
      goto errout_with_mutex;
    }

  sfp                   = (FAR struct rpc_reply_fsstat *)nmp->nm_iobuffer;
  if (txdr_unsigned(sfp->fsstat.attributes_follow) == 1)
    {
      stfp = (FAR struct nfs_statfs_ctx *)&sfp->fsstat.sf_tbytes;
    }
  else
    {
      stfp = (FAR struct nfs_statfs_ctx *)&sfp->fsstat.obj_attributes;
    }

  sbp->f_bsize          = NFS_FABLKSIZE;
  tquad                 = fxdr_hyper(&stfp->sf_tbytes); /*lint !e571*/
  sbp->f_blocks         = tquad / (uint64_t) NFS_FABLKSIZE;
  tquad                 = fxdr_hyper(&stfp->sf_fbytes); /*lint !e571*/
  sbp->f_bfree          = tquad / (uint64_t) NFS_FABLKSIZE;
  tquad                 = fxdr_hyper(&stfp->sf_abytes); /*lint !e571*/
  sbp->f_bavail         = tquad / (uint64_t) NFS_FABLKSIZE;
  tquad                 = fxdr_hyper(&stfp->sf_tfiles); /*lint !e571*/
  sbp->f_files          = tquad;
  tquad                 = fxdr_hyper(&stfp->sf_ffiles); /*lint !e571*/
  sbp->f_ffree          = tquad;
  sbp->f_namelen        = NAME_MAX;

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_remove
 *
 * Description:
 *   Remove a file
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_remove(struct inode *mountpt, const char *relpath)
{
  FAR struct nfsmount    *nmp;
  struct file_handle      fhandle;
  struct file_handle      obj_fhandle;
  struct nfs_fattr        fattr;
  struct nfs_fattr        obj_fattr;
  char                    filename[NAME_MAX + 1];
  FAR uint32_t           *ptr;
  uint32_t                f_type;
  int                     namelen;
  int                     reqlen;
  int                     error;

  /* Sanity checks */

  DEBUGASSERT(mountpt && mountpt->i_private);

  /* Get the mountpoint private data from the inode structure */

  nmp = (FAR struct nfsmount *)mountpt->i_private;

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Find the NFS node of the directory containing the file to be deleted */

  error = nfs_finddir(nmp, relpath, &fhandle, &fattr, filename);
  if (error != OK)
    {
      ferr("ERROR: nfs_finddir returned: %d\n", error);
      goto errout_with_mutex;
    }

  /* Check whether the file to be deleted is a directory */

  memcpy(&obj_fhandle, &fhandle, sizeof(struct file_handle));
  error = nfs_lookup(nmp, filename, &obj_fhandle, &obj_fattr, NULL);
  if (error != OK)
    {
      ferr("ERROR: nfs_lookup returned: %d\n", error);
      goto errout_with_mutex;
    }
  f_type = fxdr_unsigned(uint32_t, obj_fattr.fa_type);
  if (f_type == NFDIR)
    {
      ferr("ERROR: try to remove a directory\n");
      error = NFSERR_ISDIR;
      goto errout_with_mutex;
    }

  /* Create the REMOVE RPC call arguments */

  ptr    = (FAR uint32_t *)&nmp->nm_msgbuffer.removef.remove;
  reqlen = 0;

  /* Copy the variable length, directory file handle */

  *ptr++  = txdr_unsigned(fhandle.length);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &fhandle.handle, fhandle.length);
  reqlen += (int)fhandle.length;
  ptr    += uint32_increment(fhandle.length);

  /* Copy the variable-length file name */

  namelen = strlen(filename);

  *ptr++  = txdr_unsigned(namelen);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, filename, namelen);
  reqlen += uint32_alignup(namelen);

  /* Perform the REMOVE RPC call */

  nfs_statistics(NFSPROC_REMOVE);
  error = nfs_request(nmp, NFSPROC_REMOVE,
                      (FAR void *)&nmp->nm_msgbuffer.removef, reqlen,
                      (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_mkdir
 *
 * Description:
 *   Create a directory
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_mkdir(struct inode *mountpt, const char *relpath, mode_t mode)
{
  struct nfsmount       *nmp;
  struct file_handle     fhandle;
  struct nfs_fattr       fattr;
  char                   dirname[NAME_MAX + 1];
  FAR uint32_t          *ptr;
  uint32_t               tmp;
  int                    namelen;
  int                    reqlen;
  int                    error;

  /* Sanity checks */

  DEBUGASSERT(mountpt && mountpt->i_private);

  /* Get the mountpoint private data from the inode structure */

  nmp = (FAR struct nfsmount *) mountpt->i_private;

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount: %d\n", error);
      goto errout_with_mutex;
    }

  /* Find the NFS node of the directory containing the directory to be created */

  error = nfs_finddir(nmp, relpath, &fhandle, &fattr, dirname);
  if (error != OK)
    {
      ferr("ERROR: nfs_finddir returned: %d\n", error);
      goto errout_with_mutex;
    }

  /* Format the MKDIR call message arguments */

  ptr    = (FAR uint32_t *)&nmp->nm_msgbuffer.mkdir.mkdir;
  reqlen = 0;

  /* Copy the variable length, directory file handle */

  *ptr++  = txdr_unsigned(fhandle.length);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &fhandle.handle, fhandle.length);
  ptr    += uint32_increment(fhandle.length);
  reqlen += (int)fhandle.length;

  /* Copy the variable-length directory name */

  namelen = strlen(dirname);

  *ptr++  = txdr_unsigned(namelen);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, dirname, namelen);
  ptr    += uint32_increment(namelen);
  reqlen += uint32_alignup(namelen);

  /* Set the mode.  NOTE: Here we depend on the fact that the NuttX and NFS
   * bit settings are the same (at least for the bits of interest).
   */

  *ptr++  = nfs_true; /* True: mode value follows */
  reqlen += sizeof(uint32_t);

  if (!mode)
    {
      mode = (NFSMODE_IXOTH | NFSMODE_IROTH |
              NFSMODE_IXGRP | NFSMODE_IRGRP |
              NFSMODE_IXUSR | NFSMODE_IWUSR | NFSMODE_IRUSR);
    }
  tmp = mode & (NFSMODE_IXOTH | NFSMODE_IWOTH | NFSMODE_IROTH |
                NFSMODE_IXGRP | NFSMODE_IWGRP | NFSMODE_IRGRP |
                NFSMODE_IXUSR | NFSMODE_IWUSR | NFSMODE_IRUSR);
  *ptr++  = txdr_unsigned(tmp);
  reqlen += sizeof(uint32_t);

  /* Set the user ID to zero */

  *ptr++  = nfs_true;             /* True: Uid value follows */
  *ptr++  = 0;                    /* UID = 0 (nobody) */
  reqlen += 2*sizeof(uint32_t);

  /* Set the group ID to one */

  *ptr++  = nfs_true;            /* True: Gid value follows */
  *ptr++  = htonl(1);            /* GID = 1 (nogroup) */
  reqlen += 2*sizeof(uint32_t);

  /* No size */

  *ptr++  = nfs_false; /* False: No size value follows */
  reqlen += sizeof(uint32_t);

  /* Don't change times */

  *ptr++  = htonl(NFSV3SATTRTIME_DONTCHANGE); /* Don't change atime */
  *ptr++  = htonl(NFSV3SATTRTIME_DONTCHANGE); /* Don't change mtime */
  reqlen += 2*sizeof(uint32_t);

  /* Perform the MKDIR RPC */

  nfs_statistics(NFSPROC_MKDIR);
  error = nfs_request(nmp, NFSPROC_MKDIR,
                      (FAR void *)&nmp->nm_msgbuffer.mkdir, reqlen,
                      (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
  if (error)
    {
      ferr("ERROR: nfs_request failed: %d\n", error);
    }

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_rmdir
 *
 * Description:
 *   Remove a directory
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_rmdir(struct inode *mountpt, const char *relpath)
{
  struct nfsmount       *nmp;
  struct file_handle     fhandle;
  struct nfs_fattr       fattr;
  char                   dirname[NAME_MAX + 1];
  FAR uint32_t          *ptr;
  int                    namelen;
  int                    reqlen;
  int                    error;

  /* Sanity checks */

  DEBUGASSERT(mountpt && mountpt->i_private);

  /* Get the mountpoint private data from the inode structure */

  nmp = (struct nfsmount *)mountpt->i_private;

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Find the NFS node of the directory containing the directory to be removed */

  error = nfs_finddir(nmp, relpath, &fhandle, &fattr, dirname);
  if (error != OK)
    {
      ferr("ERROR: nfs_finddir returned: %d\n", error);
      goto errout_with_mutex;
    }

  /* Set up the RMDIR call message arguments */

  ptr    = (FAR uint32_t *)&nmp->nm_msgbuffer.rmdir.rmdir;
  reqlen = 0;

  /* Copy the variable length, directory file handle */

  *ptr++  = txdr_unsigned(fhandle.length);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &fhandle.handle, fhandle.length);
  reqlen += (int)fhandle.length;
  ptr    += uint32_increment(fhandle.length);

  /* Copy the variable-length directory name */

  namelen = strlen(dirname);

  *ptr++  = txdr_unsigned(namelen);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, dirname, namelen);
  reqlen += uint32_alignup(namelen);

  /* Perform the RMDIR RPC */

  nfs_statistics(NFSPROC_RMDIR);
  error = nfs_request(nmp, NFSPROC_RMDIR,
                          (FAR void *)&nmp->nm_msgbuffer.rmdir, reqlen,
                          (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

static int nfs_getfilename(char *dstpath, unsigned int dstpathLen, const char *srcpath, unsigned int maxlen)
{
  int  ret;
  char *path;
  unsigned int len;

  if (srcpath == NULL)
    {
      return ENOBUFS;
    }

  len = strlen(srcpath);
  if (len > maxlen)
    {
      return ENOBUFS;
    }

  if (len == 0)
    {
      *dstpath = '\0';
      return OK;
    }

  path = (char *)srcpath + len - 1;

  while (len > 0 && *path != '/')
    {
      len--;
      path--;
    }

  /* When copy path, skip the 1 '/' in NFS URL, for example 'nfs://server/a/b' */

  ret = strncpy_s(dstpath, dstpathLen, path + 1, strlen(path + 1));
  if (ret != EOK)
    {
      return ENOBUFS;
    }
  return OK;
}

static int nfs_compare_type(struct nfsmount *nmp, const char *oldrelpath,
                            const char *newrelpath)
{
  struct file_handle fhandle;
  struct nfs_fattr   stOld_attributes;
  struct nfs_fattr   stNew_attributes;
  int                ret;
  const char         *ch1 = oldrelpath;
  const char         *ch2 = newrelpath;

  while (*ch1 == *ch2)
    {
      if (*ch1 == '\0' || *ch2 == '\0')
        {
          break;
        }
      ch1++;
      ch2++;
    }

  if ((*ch1 == '/' && *ch2 == '\0') || (*ch2 == '/' && *ch1 == '\0'))
    {
      return 1;
    }

  ret = nfs_findnode(nmp, oldrelpath, &fhandle, &stOld_attributes, (struct nfs_fattr *)NULL);
  if (ret != OK && ret != ENOTDIR)
    {
      fdbg("ERROR: old path nfs_findnode failed: %d\n", ret);
      return 1;
    }
  ret = nfs_findnode(nmp, newrelpath, &fhandle, &stNew_attributes, (struct nfs_fattr *)NULL);
  if (ret != OK)
    {
      fdbg("ERROR: new path nfs_findnode failed: %d\n", ret);
      return 0;
    }

  /* if two value are equal which should return 0;it is not equal should return 1 */

  return stOld_attributes.fa_type != stNew_attributes.fa_type;
}

/****************************************************************************
 * Name: nfs_rename
 *
 * Description:
 *   Rename a file or directory
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_rename(struct inode *mountpt, const char *oldrelpath,
                      const char *newrelpath)
{
  struct nfsmount        *nmp;
  struct nfsnode         *np;
  struct nfsdir_s        *nd;
  struct file_handle      from_handle;
  struct file_handle      to_handle;
  char                    directory[NAME_MAX + 1];
  char                    from_name[NAME_MAX + 1];
  char                    to_name[NAME_MAX + 1];
  char                    *fullpath;
  char                    *relpath;
  struct nfs_fattr        fattr;
  FAR uint32_t           *ptr;
  int                     namelen;
  int                     reqlen;
  int                     error;

  /* Sanity checks */

  DEBUGASSERT(mountpt && mountpt->i_private);

  /* Get the mountpoint private data from the inode structure */

  nmp = (struct nfsmount *)mountpt->i_private;

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount returned: %d\n", error);
      goto errout_with_mutex;
    }

  /* Find the NFS node of the directory containing the 'from' object */

  error = nfs_finddir(nmp, oldrelpath, &from_handle, &fattr, from_name);
  if (error != OK)
    {
      ferr("ERROR: nfs_finddir returned: %d\n", error);
      goto errout_with_mutex;
    }
  fdbg("nfs_finddir oldrelpath:%s, fattr->fa_type:%x, from_name: %s\n",
       oldrelpath, fattr.fa_type, from_name);

  for (nd = nmp->nm_dir; nd; nd = nd->nfs_next)
    {
      char filename[FILENAME_MAX_LEN] = {};
      error = nfs_getfilename(filename, sizeof(filename), nd->nfs_dir->fd_dir.d_name, NAME_MAX);
      if (error != OK)
        {
          goto errout_with_mutex;
        }
      if (strcmp(filename, from_name) == 0)
        {
          break;
        }
    }
  for (np = nmp->nm_head; np; np = np->n_next)
    {
      char filename[FILENAME_MAX_LEN] = {};
      error = nfs_getfilename(filename, sizeof(filename), np->n_filep->f_relpath, PATH_MAX - 1);
      if (error != OK)
        {
          goto errout_with_mutex;
        }
      if (strcmp((const char *)filename, from_name) == 0)
        {
          break;
        }
    }

  if (!np && !nd)
    {
      fdbg("INFO: not opened\n");
    }

  /* Find the NFS node of the directory containing the 'from' object */

  error = nfs_finddir(nmp, newrelpath, &to_handle, &fattr, to_name);
  if (error != OK)
    {
      ferr("ERROR: nfs_finddir returned: %d\n", error);
      goto errout_with_mutex;
    }
  fdbg("nfs_finddir newrelpath:%s, fattr->fa_type:%x, to_name: %s\n",
       newrelpath, fattr.fa_type, to_name);

  /* compare new and old type */

  error = nfs_compare_type(nmp, oldrelpath, newrelpath);
  if (error != OK)
    {
      fdbg("ERROR: nfs_compare_type returned: %d\n", error);
      goto errout_with_mutex;
    }

  /* Format the RENAME RPC arguments */

  ptr    = (FAR uint32_t *)&nmp->nm_msgbuffer.renamef.rename;
  reqlen = 0;

  /* Copy the variable length, 'from' directory file handle */

  *ptr++  = txdr_unsigned(from_handle.length);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &from_handle.handle, from_handle.length);
  reqlen += (int)from_handle.length;
  ptr    += uint32_increment(from_handle.length);

  /* Copy the variable-length 'from' object name */

  namelen = strlen(from_name);

  *ptr++  = txdr_unsigned(namelen);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, from_name, namelen);
  reqlen += uint32_alignup(namelen);
  ptr    += uint32_increment(namelen);

  /* Copy the variable length, 'to' directory file handle */

  *ptr++  = txdr_unsigned(to_handle.length);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, &to_handle.handle, to_handle.length);
  ptr    += uint32_increment(to_handle.length);
  reqlen += (int)to_handle.length;

  /* Copy the variable-length 'to' object name */

  namelen = strlen(to_name);

  *ptr++  = txdr_unsigned(namelen);
  reqlen += sizeof(uint32_t);

  memcpy(ptr, to_name, namelen);
  reqlen += uint32_alignup(namelen);

  /* Perform the RENAME RPC */

  nfs_statistics(NFSPROC_RENAME);
  error = nfs_request(nmp, NFSPROC_RENAME,
                      (FAR void *)&nmp->nm_msgbuffer.renamef, reqlen,
                      (FAR void *)nmp->nm_iobuffer, nmp->nm_buflen);
  if (error != OK)
    {
      fdbg("ERROR: nfs_request returned: %d\n", error);
      goto errout_with_mutex;
    }

  if (np)
    {
      error =  strncpy_s(directory, NAME_MAX + 1, np->n_filep->f_path, np->n_filep->f_relpath - np->n_filep->f_path);
      directory[np->n_filep->f_relpath - np->n_filep->f_path] = '\0';
      if (error != EOK)
        {
          error = ENOBUFS;
          goto errout_with_mutex;
        }
      error = vfs_normalize_path(directory, newrelpath, &fullpath);
      if (error < 0)
        {
          error = -error;
          fdbg("ERROR: vfs_normalize_path returned: %d\n", error);
          goto errout_with_mutex;
        }

      relpath = strstr(fullpath, newrelpath);
      if (relpath == NULL)
        {
          fdbg("ERROR: relpath is not sub in fullpath.\n", error);
          free(fullpath);
          goto errout_with_mutex;
        }

      /* Update the path of old file. */

      free(np->n_filep->f_path);
      np->n_filep->f_path = fullpath;
      np->n_filep->f_relpath = relpath;
    }
  else if (nd)
    {
      error = memcpy_s(nd->nfs_dir->fd_dir.d_name, strlen(to_name) + 1, to_name, strlen(to_name) + 1);
      if (error != EOK)
        {
          error = ENOBUFS;
          goto errout_with_mutex;
        }
    }

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

/****************************************************************************
 * Name: nfs_stat_common
 *
 * Description:
 *   Return information about the file system object described by 'info'
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void nfs_stat_common(FAR struct nfs_statinfo_s *info,
                            FAR struct stat *buf)
{
  mode_t mode;

  /* Here we exploit the fact that most mode bits are the same in NuttX
   * as in the NFSv3 spec.
   */

  mode = info->ns_mode &
           (NFSMODE_IXOTH | NFSMODE_IWOTH | NFSMODE_IROTH |
            NFSMODE_IXGRP | NFSMODE_IWGRP | NFSMODE_IRGRP |
            NFSMODE_IXUSR | NFSMODE_IWUSR | NFSMODE_IRUSR);

  /* Handle the cases that are not the same */

  if ((info->ns_mode & NFSMODE_ISGID) != 0)
    {
      mode |= S_ISGID;
    }

  if ((info->ns_mode & NFSMODE_ISUID) != 0)
    {
      mode |= S_ISUID;
    }

  /* Now OR in the file type */

  switch (info->ns_type)
    {
    default:
    case NFNON:   /* Unknown type */
      break;

    case NFREG:   /* Regular file */
      mode |= S_IFREG;
      break;

    case NFDIR:   /* Directory */
      mode |= S_IFDIR;
      break;

    case NFBLK:   /* Block special device file */
      mode |= S_IFBLK;
      break;

    case NFCHR:   /* Character special device file */
      mode |= S_IFCHR;
      break;

    case NFLNK:   /* Symbolic link */
      mode |= S_IFLNK;
      break;

    case NFSOCK:  /* Socket */
      mode |= S_IFSOCK;
      break;

    case NFFIFO:  /* Named pipe */
      mode |= S_IFMT;
      break;
    }

  buf->st_mode    = mode;
  buf->st_uid     = 0;
  buf->st_gid     = 0;
  buf->st_size    = (off_t)info->ns_size;
  buf->st_blksize = 0;
  buf->st_blocks  = 0;
  buf->st_mtime   = info->ns_mtime;
  buf->st_atime   = info->ns_atime;
  buf->st_ctime   = info->ns_ctime;
}

/****************************************************************************
 * Name: nfs_stat
 *
 * Description:
 *   Return information about the file system object at 'relpath'
 *
 * Returned Value:
 *   0 on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int nfs_stat(struct inode *mountpt, const char *relpath,
                    struct stat *buf)
{
  struct nfsmount *nmp;
  struct file_handle fhandle;
  struct nfs_fattr obj_attributes;
  struct nfs_statinfo_s info;
  struct timespec ts;
  int error;

  /* Sanity checks */

  DEBUGASSERT(mountpt && mountpt->i_private);

  /* Get the mountpoint private data from the inode structure */

  nmp = (FAR struct nfsmount *)mountpt->i_private;
  DEBUGASSERT(nmp && buf);

  /* Check if the mount is still healthy */

  nfs_mux_take(nmp);
  error = nfs_checkmount(nmp);
  if (error != OK)
    {
      ferr("ERROR: nfs_checkmount failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Get the file handle attributes of the requested node */

  error = nfs_findnode(nmp, relpath, &fhandle, &obj_attributes, NULL);
  if (error != OK)
    {
      ferr("ERROR: nfs_findnode failed: %d\n", error);
      goto errout_with_mutex;
    }

  /* Extract the file mode, file type, and file size. */

  info.ns_mode  = fxdr_unsigned(uint16_t, obj_attributes.fa_mode);
  info.ns_type  = fxdr_unsigned(uint8_t, obj_attributes.fa_type);
  info.ns_size  = fxdr_hyper(&obj_attributes.fa_size);

  /* Extract time values as type time_t in units of seconds */

  fxdr_nfsv3time(&obj_attributes.fa_mtime, &ts);
  info.ns_mtime = ts.tv_sec;

  fxdr_nfsv3time(&obj_attributes.fa_atime, &ts);
  info.ns_atime = ts.tv_sec;

  fxdr_nfsv3time(&obj_attributes.fa_ctime, &ts);
  info.ns_ctime = ts.tv_sec;

  /* Then update the stat buffer with this information */

  nfs_stat_common(&info, buf);

errout_with_mutex:
  nfs_mux_release(nmp);
  return -error;
}

int nfs_mount(const char *server_ip_and_path, const char *mount_path,
              unsigned int uid, unsigned int gid)
{
  struct nfs_args         nfs_args = {0};
  char                    *server_ip_addr;
  char                    *server_nfs_path;
  int                     found_colon = 0;
  unsigned int            pos;
  int                     ret = -1;
  struct sockaddr_in      *nfs_srv_addr;
  size_t len;

  rpcclnt_setuidgid(uid, gid);

  len = strlen(server_ip_and_path);
  for (pos = 0; pos < len; pos++)
    {
      if (*(server_ip_and_path + pos) == ':')
        {
          found_colon = 1;
          break;
        }
    }

  if (!found_colon)
    {
      set_errno(ENOENT);
      goto nfs_mount_out;
    }

  server_ip_addr = (char *)malloc(pos + 1);
  if (server_ip_addr == NULL)
    {
      PRINTK("malloc failure\n");
      set_errno(ENOMEM);
      goto nfs_mount_out;
    }

  ret = strncpy_s(server_ip_addr, pos + 1, server_ip_and_path, pos);
  if (ret != EOK)
    {
      set_errno(ENOBUFS);
      goto nfs_free_node_out;
    }
  *(server_ip_addr + pos) = '\0';
  server_nfs_path = (char *)(server_ip_and_path + pos + 1);

  (void)memset_s(&nfs_args, sizeof(nfs_args), 0, sizeof(nfs_args));

  if (g_NFSMOUNT_HOOK != NULL)
    {
      g_NFSMOUNT_HOOK(&nfs_args);
    }

  nfs_args.path = server_nfs_path; /* server nfs dir */

  nfs_srv_addr = (struct sockaddr_in *)&nfs_args.addr;
  nfs_srv_addr->sin_family = AF_INET;
  ret = inet_pton(AF_INET, server_ip_addr, &nfs_srv_addr->sin_addr.s_addr);
  if (ret != 1)
    {
      ret = -1;
      set_errno(ECONNREFUSED);
      goto nfs_free_node_out;
    }
  nfs_srv_addr->sin_port = htons(PMAPPORT);

  nfs_args.addrlen = sizeof(nfs_args.addr);
#if (NFS_PROTO_TYPE == NFS_IPPROTO_TCP)
  nfs_args.sotype = SOCK_STREAM;
#elif (NFS_PROTO_TYPE == NFS_IPPROTO_UDP)
  nfs_args.sotype = SOCK_DGRAM;
#endif

  PRINTK("Mount nfs on %s:%s, uid:%d, gid:%d\n", server_ip_addr, server_nfs_path, uid, gid);
  ret = mount((const char *)NULL, mount_path, "nfs", 0, &nfs_args);

nfs_free_node_out:
  free(server_ip_addr);

nfs_mount_out:
  if (ret)
    {
      perror("mount nfs error");
      return -1;
    }
  PRINTK("Mount nfs finished.\n");
  return 0;
}

#endif
