/****************************************************************************
 * fs/inode/fs_files.c
 *
 *   Copyright (C) 2007-2009, 2011-2013, 2016-2017 Gregory Nutt. All rights
 *     reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include "unistd.h"
#include "vfs_config.h"

#include "sys/types.h"
#include "string.h"
#include "semaphore.h"
#include "assert.h"
#include "errno.h"

#include "fs/fs.h"
#include "fs/file.h"
#include "stdio.h"
#include "stdlib.h"
#include "inode/inode.h"
#include "los_mux.h"
#include "fs/fd_table.h"
#ifdef LOSCFG_NET_LWIP_SACK
#include "lwip/sockets.h"
#include "fs_file.h"
#endif
#include "los_process_pri.h"
#include "los_vm_filemap.h"
#define ferr PRINTK

#if CONFIG_NFILE_DESCRIPTORS > 0
struct filelist tg_filelist;
#endif

#if CONFIG_NFILE_STREAMS > 0
struct streamlist tg_streamlist;
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

struct filelist *sched_getfiles(void)
{
#if CONFIG_NFILE_DESCRIPTORS > 0
  return &tg_filelist;
#else
  return NULL;
#endif
}

/* 32: An unsigned int takes 32 bits */

static unsigned int bitmap[CONFIG_NFILE_DESCRIPTORS / 32 + 1] = {0};

static void set_bit(int i, void *addr)
{
  unsigned int tem = (unsigned int)i >> 5; /* Get the bitmap subscript */
  unsigned int *addri = (unsigned int *)addr + tem;
  unsigned int old = *addri;
  old = old | (1UL << ((unsigned int)i & 0x1f)); /* set the new map bit */
  *addri = old;
}

static void clear_bit(int i, void *addr)
{
  unsigned int tem = (unsigned int)i >> 5; /* Get the bitmap subscript */
  unsigned int *addri = (unsigned int *)addr + tem;
  unsigned int old = *addri;
  old = old & ~(1UL << ((unsigned int)i & 0x1f)); /* Clear the old map bit */
  *addri = old;
}

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: _files_semtake
 ****************************************************************************/

static void _files_semtake(FAR struct filelist *list)
{
  /* Take the semaphore (perhaps waiting) */

  while (sem_wait(&list->fl_sem) != 0)
    {
      /* The only case that an error should occur here is if the wait was
       * awakened by a signal.
       */

      LOS_ASSERT(get_errno() == EINTR);
    }
}

/****************************************************************************
 * Name: _files_semgive
 ****************************************************************************/

#define _files_semgive(list)  (void)sem_post(&list->fl_sem)

/****************************************************************************
 * Name: _files_close
 *
 * Description:
 *   Close an inode (if open)
 *
 * Assumuptions:
 *   Caller holds the list semaphore because the file descriptor will be freed.
 *
 ****************************************************************************/

static int _files_close(FAR struct file *filep)
{
  struct inode *inode = filep->f_inode;
  int ret = OK;

  /* Check if the struct file is open (i.e., assigned an inode) */

  if (inode)
    {
      if (filep->f_oflags & O_DIRECTORY)
        {
          ret = closedir(filep->f_dir);
          if (ret != OK)
            {
              return ret;
            }
        }
      else
        {
          /* Close the file, driver, or mountpoint. */

          if (inode->u.i_ops && inode->u.i_ops->close)
            {
              /* Perform the close operation */

              ret = inode->u.i_ops->close(filep);
              if (ret != OK)
                {
                  return ret;
                }
            }
        }

      /* And release the inode */

      inode_release(inode);

      /* Release the path of file */

      free(filep->f_path);

      /* Release the file descriptor */

      filep->f_magicnum = 0;
      filep->f_oflags   = 0;
      filep->f_pos      = 0;
      filep->f_path     = NULL;
      filep->f_priv     = NULL;
      filep->f_inode    = NULL;
      filep->f_refcount = 0;
      filep->f_mapping  = NULL;
      filep->f_dir      = NULL;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: files_initialize
 *
 * Description:
 *   This is called from the FS initialization logic to configure the files.
 *
 ****************************************************************************/

void files_initialize(void)
{
}

/****************************************************************************
 * Name: files_initlist
 *
 * Description: Initializes the list of files for a new task
 *
 ****************************************************************************/

void files_initlist(FAR struct filelist *list)
{
  DEBUGASSERT(list);

  /* Initialize the list access mutex */

  (void)sem_init(&list->fl_sem, 0, 1);
}

/****************************************************************************
 * Name: files_releaselist
 *
 * Description:
 *   Release a reference to the file list
 *
 ****************************************************************************/

void files_releaselist(FAR struct filelist *list)
{
  int i;

  DEBUGASSERT(list);

  /* Close each file descriptor .. Normally, you would need take the list
   * semaphore, but it is safe to ignore the semaphore in this context because
   * there should not be any references in this context.
   */

  for (i = 0; i < CONFIG_NFILE_DESCRIPTORS; i++)
    {
      (void)_files_close(&list->fl_files[i]);
    }

  /* Destroy the semaphore */

  (void)sem_destroy(&list->fl_sem);
}

/****************************************************************************
 * Name: file_dup2
 *
 * Description:
 *   Assign an inode to a specific files structure.  This is the heart of
 *   dup2.
 *
 *   Equivalent to the non-standard fs_dupfd2() function except that it
 *   accepts struct file instances instead of file descriptors and it does
 *   not set the errno variable.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is return on
 *   any failure.
 *
 ****************************************************************************/

int file_dup2(FAR struct file *filep1, FAR struct file *filep2)
{
  FAR struct filelist *list = NULL;
  FAR struct inode *inode_ptr = NULL;
  char *fullpath = NULL;
  const char *relpath = NULL;
  int err;
  int len;
  int ret;
  struct inode_search_s desc;

  if (!filep1 || !filep1->f_inode || !filep2)
    {
      err = EBADF;
      goto errout;
    }

  list = sched_getfiles();
  DEBUGASSERT(list);
  /* The file list can be NULL under two cases:  (1) One is an obscure
   * cornercase:  When memory management debug output is enabled.  Then
   * there may be attempts to write to stdout from malloc before the group
   * data has been allocated.  The other other is (2) if this is a kernel
   * thread.  Kernel threads have no allocated file descriptors.
   */

  if (list != NULL)
    {
      _files_semtake(list);
    }

  /* If there is already an inode contained in the new file structure,
   * close the file and release the inode.
   */

  ret = _files_close(filep2);
  if (ret < 0)
    {
      /* An error occurred while closing the driver */

      goto errout_with_ret;
    }

  len = strlen(filep1->f_path);
  if ((len == 0) || (len >= PATH_MAX))
    {
      ret = -EINVAL;
      goto errout_with_ret;
    }

  fullpath = (char *)zalloc(len + 1);
  if (fullpath == NULL)
    {
      ret = -ENOMEM;
      goto errout_with_ret;
    }

  /* Increment the reference count on the contained inode */

  inode_ptr = filep1->f_inode;

  /* Then clone the file structure */

  filep2->f_oflags = filep1->f_oflags;
  filep2->f_pos    = filep1->f_pos;
  filep2->f_inode  = inode_ptr;
  filep2->f_priv   = filep1->f_priv;

  (void)strncpy_s(fullpath, len + 1, filep1->f_path, len);
  SETUP_SEARCH(&desc, fullpath, false);
  if (inode_find(&desc) < 0)
    {
      ret = -EACCES;
      free(fullpath);
      goto errout_with_ret;
    }
  relpath = desc.relpath;
  filep2->f_path = fullpath;
  filep2->f_relpath = relpath;

  /* Call the open method on the file, driver, mountpoint so that it
   * can maintain the correct open counts.
   */

  if (inode_ptr->u.i_ops)
    {
#ifndef CONFIG_DISABLE_MOUNTPOINT
      if (INODE_IS_MOUNTPT(inode_ptr))
        {
          /* Dup the open file on the in the new file structure */

          if (inode_ptr->u.i_mops->dup)
            {
              ret = inode_ptr->u.i_mops->dup(filep1, filep2);
            }
          else
            {
              ret = -ENOSYS;
            }
        }
      else
#endif
        {
          /* (Re-)open the pseudo file or device driver */

          if (inode_ptr->u.i_ops->open)
            {
              ret = inode_ptr->u.i_ops->open(filep2);
            }
          else
            {
              ret = -ENOSYS;
            }
        }

      /* Handle open failures */

      if (ret < 0)
        {
          goto errout_with_inode;
        }
    }

  if (list != NULL)
    {
      _files_semgive(list);
    }
  return OK;

  /* Handle various error conditions */

errout_with_inode:

  inode_release(filep2->f_inode);
  free(filep2->f_path);
  filep2->f_oflags  = 0;
  filep2->f_pos     = 0;
  filep2->f_inode   = NULL;
  filep2->f_priv    = NULL;
  filep2->f_path    = NULL;
  filep2->f_relpath = NULL;

errout_with_ret:
  err               = -ret;
  _files_semgive(list);

errout:
  set_errno(err);
  return VFS_ERROR;
}

#define FILE_START_FD 3

static inline unsigned int files_magic_generate(void)
{
    static unsigned int files_magic = 0;
    return files_magic++;
}

/****************************************************************************
 * Name: files_allocate
 *
 * Description:
 *   Allocate a struct files instance and associate it with an inode instance.
 *   Returns the file descriptor == index into the files array.
 *
 ****************************************************************************/

int files_allocate(FAR struct inode *inode_ptr, int oflags, off_t pos,void* priv, int minfd)
{
  FAR struct filelist *list = NULL;
  unsigned int *p = NULL;
  unsigned int mask;
  unsigned int i;
  struct files_struct *process_files = NULL;

  /* minfd should be a positive number,and 0,1,2 had be distributed to stdin,stdout,stderr */

  if (minfd < FILE_START_FD)
    {
      minfd = FILE_START_FD;
    }
  i = (unsigned int)minfd;

  list = sched_getfiles();
  DEBUGASSERT(list);

  _files_semtake(list);

  while (i < CONFIG_NFILE_DESCRIPTORS)
    {
      p = ((unsigned int *)bitmap) + (i >> 5); /* Gets the location in the bitmap */
      mask = 1 << (i & 0x1f); /* Gets the mask for the current bit int bitmap */
      if ((~(*p) & mask))
        {
          set_bit(i, bitmap);
          list->fl_files[i].f_oflags   = oflags;
          list->fl_files[i].f_pos      = pos;
          list->fl_files[i].f_inode    = inode_ptr;
          list->fl_files[i].f_priv     = priv;
          list->fl_files[i].f_refcount = 1;
          list->fl_files[i].f_mapping  = NULL;
          list->fl_files[i].f_dir      = NULL;
          list->fl_files[i].f_magicnum = files_magic_generate();
          process_files = OsCurrProcessGet()->files;
          if (process_files)
            {
              FD_SET(i, process_files->fdt->open_fds);
            }
          else
            {
              PRINT_ERR("process files is NULL, %s %d\n", __FUNCTION__ ,__LINE__);
              _files_semgive(list);
              return VFS_ERROR;
            }
          _files_semgive(list);
          return (int)i;
        }
      i++;
    }


  _files_semgive(list);
  return VFS_ERROR;
}

static int files_close_internal(int fd, LosProcessCB *processCB)
{
  FAR struct filelist *list = NULL;
  int                  ret  = OK;
  struct files_struct *process_files = NULL;

  /* 0,1,2 fd is not opened in system, no need to close them */

  if ((fd >= STDIN_FILENO) && (fd <= STDERR_FILENO))
    {
      return OK;
    }

  /* Get the thread-specific file list.  It should never be NULL in this
   * context.
   */

  list = sched_getfiles();
  DEBUGASSERT(list != NULL);

  /* If the file was properly opened, there should be an inode assigned */

  if (fd < 0 || fd >= CONFIG_NFILE_DESCRIPTORS || !list->fl_files[fd].f_inode)
    {
      return -EBADF;
    }

  /* Perform the protected close operation */

  _files_semtake(list);
  process_files = processCB->files;
  if (process_files)
    {
      FD_CLR(fd, process_files->fdt->open_fds);
    }
  else
    {
      PRINT_ERR("process files is NULL, %s %d\n", __FUNCTION__ ,__LINE__);
      _files_semgive(list);
      return -EINVAL;
    }
  if (list->fl_files[fd].f_mapping)
    {
      OsFileCacheFlush(list->fl_files[fd].f_mapping);
      dec_mapping(list->fl_files[fd].f_mapping);
    }
  list->fl_files[fd].f_refcount--;

  /* The filep->f_refcount may not be zero here, when the filep is shared in parent-child processes.
     so, upon closing the filep in current process, relevant region must be released immediately */

  OsVmmFileRegionFree(&list->fl_files[fd], processCB);

  if (list->fl_files[fd].f_refcount == 0)
    {
      ret = _files_close(&list->fl_files[fd]);
      if (ret == OK)
        {
          clear_bit(fd, bitmap);
        }
    }

  _files_semgive(list);
  return ret;
}

/****************************************************************************
 * Name: files_close
 *
 * Description:
 *   Close an inode (if open)
 *
 * Assumuptions:
 *   Caller holds the list semaphore because the file descriptor will be freed.
 *
 ****************************************************************************/

int files_close(int fd)
{
  return files_close_internal(fd, OsCurrProcessGet());
}

/****************************************************************************
 * Name: files_release
 *
 * Assumuptions:
 *   Similar to files_close().  Called only from open() logic on error
 *   conditions.
 *
 ****************************************************************************/

void files_release(int fd)
{
  FAR struct filelist *list = NULL;
  struct files_struct *process_files = NULL;

  list = sched_getfiles();
  DEBUGASSERT(list);

  if (fd >=0 && fd < CONFIG_NFILE_DESCRIPTORS)
    {
      _files_semtake(list);

      list->fl_files[fd].f_magicnum = 0;
      list->fl_files[fd].f_oflags   = 0;
      list->fl_files[fd].f_inode    = NULL;
      list->fl_files[fd].f_pos      = 0;
      list->fl_files[fd].f_refcount = 0;
      list->fl_files[fd].f_path     = NULL;
      list->fl_files[fd].f_relpath  = NULL;
      list->fl_files[fd].f_priv     = NULL;
      list->fl_files[fd].f_mapping  = NULL;
      list->fl_files[fd].f_dir      = NULL;

      process_files = OsCurrProcessGet()->files;
      if (process_files)
        {
          FD_CLR(fd, process_files->fdt->open_fds);
        }
      clear_bit(fd, bitmap);
      _files_semgive(list);
    }
}

struct inode * files_get_openfile(int fd)
{
  FAR struct filelist *list = NULL;
  unsigned int *p = NULL;
  unsigned int mask;

  list = sched_getfiles();
  DEBUGASSERT(list);

  p = ((unsigned int *)bitmap) + ((unsigned int)fd >> 5); /* Gets the location in the bitmap */
  mask = 1 << ((unsigned int)fd & 0x1f); /* Gets the mask for the current bit int bitmap */
  if ((~(*p) & mask))
    {
      return NULL;
    }

  return list->fl_files[fd].f_inode;
}

int alloc_fd(int minfd)
{
  FAR struct filelist *list = NULL;
  unsigned int *p = NULL;
  unsigned int mask;
  unsigned int i;

  /* minfd should be a positive number,and 0,1,2 had be distributed to stdin,stdout,stderr */

  if (minfd < FILE_START_FD)
    {
      minfd = FILE_START_FD;
    }
  i = (unsigned int)minfd;

  list = sched_getfiles();
  DEBUGASSERT(list);

  _files_semtake(list);

  while (i < CONFIG_NFILE_DESCRIPTORS)
    {
      p = ((unsigned int *)bitmap) + (i >> 5); /* Gets the location in the bitmap */
      mask = 1 << (i & 0x1f); /* Gets the mask for the current bit int bitmap */
      if ((~(*p) & mask))
        {
          set_bit(i, bitmap);
          _files_semgive(list);
          return (int)i;
        }
      i++;
    }
  _files_semgive(list);
  return VFS_ERROR;
}

void clear_fd(int fd)
{
  clear_bit(fd, bitmap);
}

int close_files(struct inode *inode)
{
  int fd = 0;
  int ret = 0;
  FAR struct inode *open_file_inode = NULL;

  for (fd = FILE_START_FD; fd < CONFIG_NFILE_DESCRIPTORS; fd++)
    {
      open_file_inode = files_get_openfile(fd);
      if (open_file_inode && (open_file_inode == inode))
        {
          ret = files_close(fd);
          if (ret < 0)
            {
              return -EBUSY;
            }
        }
    }

  return 0;
}

void files_refer(int fd)
{
  FAR struct filelist *list = sched_getfiles();
  if (!list || fd < 0 || fd >= CONFIG_NFILE_DESCRIPTORS)
    {
      return;
    }
  _files_semtake(list);
  list->fl_files[fd].f_refcount++;
  _files_semgive(list);
}

static void copy_fds(const struct fd_table_s *new_fdt, const struct fd_table_s *old_fdt)
{
  unsigned int sz;

  sz = new_fdt->max_fds * sizeof(struct file_table_s);
  if (sz)
    {
      (void)memcpy_s(new_fdt->ft_fds, sz, old_fdt->ft_fds, sz);
    }
  (void)memcpy_s(new_fdt->open_fds, sizeof(fd_set), old_fdt->open_fds, sizeof(fd_set));
  (void)memcpy_s(new_fdt->proc_fds, sizeof(fd_set), old_fdt->proc_fds, sizeof(fd_set));
}

static void copy_fd_table(struct fd_table_s *new_fdt, struct fd_table_s *old_fdt)
{
  copy_fds((const struct fd_table_s *)new_fdt, (const struct fd_table_s *)old_fdt);
  for (int i = 0; i < new_fdt->max_fds; i++)
    {
      if (FD_ISSET(i, new_fdt->open_fds))
        {
          files_refer(i);
        }
#if defined(LOSCFG_NET_LWIP_SACK)
      if (FD_ISSET(i, new_fdt->proc_fds))
        {
          int sysFd = GetAssociatedSystemFd(i);
          if (sysFd >= CONFIG_NFILE_DESCRIPTORS && sysFd < (CONFIG_NFILE_DESCRIPTORS + CONFIG_NSOCKET_DESCRIPTORS))
            {
              socks_refer(sysFd);
            }
        }
#endif
    }
}

static struct fd_table_s * alloc_fd_table(unsigned int numbers)
{
  struct fd_table_s *fdt;
  void *data;

  fdt = LOS_MemAlloc(m_aucSysMem0, sizeof(struct fd_table_s));
  if (!fdt)
    {
      goto out;
    }
  fdt->max_fds = numbers;
  if (!numbers)
    {
      fdt->ft_fds = NULL;
      fdt->open_fds = NULL;
      fdt->proc_fds = NULL;
      return fdt;
    }
  data = LOS_MemAlloc(m_aucSysMem0, numbers * sizeof(struct file_table_s));
  if (!data)
    {
      goto out_fdt;
    }
  fdt->ft_fds = data;

  /* 0,1,2 be distributed to stdin,stdout,stderr default */
  fdt->ft_fds[STDIN_FILENO].sysFd = STDIN_FILENO;
  fdt->ft_fds[STDOUT_FILENO].sysFd = STDOUT_FILENO;
  fdt->ft_fds[STDERR_FILENO].sysFd = STDERR_FILENO;
  for (int i = STDERR_FILENO + 1; i < numbers; i++)
    {
        fdt->ft_fds[i].sysFd = -1;
    }

  data = LOS_MemAlloc(m_aucSysMem0, sizeof(fd_set));
  if (!data)
    {
      goto out_arr;
    }
  (VOID)memset_s(data, sizeof(fd_set), 0, sizeof(fd_set));
  fdt->open_fds = data;
  FD_SET(STDIN_FILENO, fdt->open_fds);
  FD_SET(STDOUT_FILENO, fdt->open_fds);
  FD_SET(STDERR_FILENO, fdt->open_fds);

  data = LOS_MemAlloc(m_aucSysMem0, sizeof(fd_set));
  if (!data)
    {
      goto out_all;
    }
  (VOID)memset_s(data, sizeof(fd_set), 0, sizeof(fd_set));
  fdt->proc_fds = data;
  FD_SET(STDIN_FILENO, fdt->proc_fds);
  FD_SET(STDOUT_FILENO, fdt->proc_fds);
  FD_SET(STDERR_FILENO, fdt->proc_fds);

  (void)sem_init(&fdt->ft_sem, 0, 1);

  return fdt;

out_all:
  (VOID)LOS_MemFree(m_aucSysMem0, fdt->open_fds);
out_arr:
  (VOID)LOS_MemFree(m_aucSysMem0, fdt->ft_fds);
out_fdt:
  (VOID)LOS_MemFree(m_aucSysMem0, fdt);
out:
  return NULL;
}

struct files_struct *alloc_files(void)
{
  struct files_struct *files = LOS_MemAlloc(m_aucSysMem0, sizeof(struct files_struct));
  if (!files)
    {
      ferr("malloc file_struct error\n");
      return NULL;
    }
  files->count = 1;
  files->file_lock = 0;
  files->next_fd = 3;
#ifdef VFS_USING_WORKDIR
  spin_lock_init(&files->workdir_lock);
  memset_s(files->workdir, PATH_MAX, 0, PATH_MAX);
  files->workdir[0] = '/';
#endif
  files->fdt = alloc_fd_table(NR_OPEN_DEFAULT);
  if (!files->fdt)
    {
      ferr("malloc fdt error\n");
      (VOID)LOS_MemFree(m_aucSysMem0, files);
      return NULL;
    }

  return files;
}

struct files_struct *dup_fd(struct files_struct *old_files)
{
  struct fd_table_s *old_fdt = NULL;
  struct fd_table_s *new_fdt = NULL;
  struct files_struct *files = NULL;
  if((old_files == NULL) || (old_files->fdt == NULL) || (old_files->fdt->max_fds == 0))
    {
      return alloc_files();
    }
  files = LOS_MemAlloc(m_aucSysMem0, sizeof(struct files_struct));
  if(!files)
    {
      ferr("malloc file_struct error\n");
      return NULL;
    }
  files->count = 1;
  files->file_lock = 0;
  files->next_fd = old_files->next_fd;
#ifdef VFS_USING_WORKDIR
  spin_lock_init(&files->workdir_lock);
  memset_s(files->workdir, PATH_MAX, 0, PATH_MAX);
  strncpy_s(files->workdir, PATH_MAX - 1, old_files->workdir, PATH_MAX - 1);
#endif
  old_fdt = old_files->fdt;
  new_fdt = alloc_fd_table(old_fdt->max_fds);
  if(new_fdt == NULL)
    {
      PRINT_ERR("alloc fd_table failed\n");
      (VOID)LOS_MemFree(m_aucSysMem0, files);
      return NULL;
    }
  copy_fd_table(new_fdt, old_fdt);
  files->fdt = new_fdt;

  return files;
}

/****************************************************************************
 * Name: delete_files
 *
 * Description:
 *   Close a processCB's files specified by processCB and files
 *
 * Assumuptions:
 *   processCB->files may != files and processCB may != current processCB.
 *
 ****************************************************************************/
void delete_files(LosProcessCB *processCB, struct files_struct *files)
{
  if (files == NULL || processCB == NULL)
    {
      return;
    }

  if (files->fdt == NULL)
    {
      goto out_file;
    }

  for (int i = 0; i < files->fdt->max_fds; i++)
    {
      if (FD_ISSET(i, files->fdt->open_fds))
        {
          files_close_internal(i, processCB);
        }
#if defined(LOSCFG_NET_LWIP_SACK)
      if (FD_ISSET(i, files->fdt->proc_fds))
        {
          int sysFd = GetAssociatedSystemFd(i);
          if (sysFd >= CONFIG_NFILE_DESCRIPTORS && sysFd < (CONFIG_NFILE_DESCRIPTORS + CONFIG_NSOCKET_DESCRIPTORS))
            {
              close(sysFd);
            }
        }
#endif
    }

  (VOID)sem_destroy(&files->fdt->ft_sem);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt->ft_fds);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt->open_fds);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt->proc_fds);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt);
out_file:
  (VOID)LOS_MemFree(m_aucSysMem0, files);
  return;
}

struct files_struct *create_files_snapshot(const struct files_struct *old_files)
{
  struct fd_table_s *old_fdt = NULL;
  struct fd_table_s *new_fdt = NULL;
  struct files_struct *files = NULL;
  if ((old_files == NULL) || (old_files->fdt == NULL) || (old_files->fdt->max_fds == 0))
    {
      return NULL;
    }
  files = LOS_MemAlloc(m_aucSysMem0, sizeof(struct files_struct));
  if (!files)
    {
      PRINT_ERR("malloc file_struct error\n");
      return NULL;
    }
  files->count = 1;
  files->file_lock = 0;
  files->next_fd = old_files->next_fd;
#ifdef VFS_USING_WORKDIR
  spin_lock_init(&files->workdir_lock);
  memset_s(files->workdir, PATH_MAX, 0, PATH_MAX);
  strncpy_s(files->workdir, PATH_MAX - 1, old_files->workdir, PATH_MAX - 1);
#endif
  old_fdt = old_files->fdt;
  new_fdt = alloc_fd_table(old_fdt->max_fds);
  if (new_fdt == NULL)
    {
      PRINT_ERR("alloc fd_table failed\n");
      (VOID)LOS_MemFree(m_aucSysMem0, files);
      return NULL;
    }
  copy_fds((const struct fd_table_s *)new_fdt, (const struct fd_table_s *)old_fdt);
  files->fdt = new_fdt;

  return files;

}

void delete_files_snapshot(struct files_struct *files)
{
  if (files == NULL)
    {
      return;
    }
  if (files->fdt == NULL)
    {
      goto out_file;
    }

  (VOID)sem_destroy(&files->fdt->ft_sem);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt->ft_fds);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt->open_fds);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt->proc_fds);
  (VOID)LOS_MemFree(m_aucSysMem0, files->fdt);
out_file:
  (VOID)LOS_MemFree(m_aucSysMem0, files);
  return;
}
