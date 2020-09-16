/****************************************************************************
 * drivers/pipes/pipe_common.c
 *
 *   Copyright (C) 2008-2009, 2011, 2015-2016, 2018 Gregory Nutt. All
 *     rights reserved.
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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <debug.h>
#include <poll.h>
#include "linux/wait.h"
#include "fs/fs.h"
#include "fs_poll_pri.h"
#include <assert.h>

#ifdef CONFIG_DEBUG_FEATURES
#  include <nuttx/arch.h>
#endif
#include <semaphore.h>
#include <fs/fs.h>
#include "pipe_common.h"
#include "los_printf.h"
#include "user_copy.h"
#ifdef LOSCFG_KERNEL_PIPE

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CONFIG_DEV_PIPEDUMP will dump the contents of each transfer into and out
 * of the pipe.
 */

#ifdef CONFIG_DEV_PIPEDUMP
#  define pipe_dumpbuffer(m,a,n) lib_dumpbuffer(m,a,n)
#else
#  define pipe_dumpbuffer(m,a,n)
#endif

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static void pipecommon_semtake(sem_t *sem);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pipecommon_semtake
 ****************************************************************************/

static void pipecommon_semtake(FAR sem_t *sem)
{
  int ret;

  do
    {
      /* Take the semaphore (perhaps waiting) */

      ret = sem_wait(sem);

    }
  while (ret == -EINTR);
}

/****************************************************************************
 * Name: pipecommon_pollnotify
 ****************************************************************************/

static void pipecommon_pollnotify(FAR struct pipe_dev_s *dev,
                                  pollevent_t eventset)
{
  if (eventset & POLLERR)
    {
      eventset &= ~(POLLOUT | POLLIN);
    }

  notify_poll_with_key(&dev->wq, eventset);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pipecommon_allocdev
 ****************************************************************************/

FAR struct pipe_dev_s *pipecommon_allocdev(size_t bufsize, const char *name)
{
  FAR struct pipe_dev_s *dev;
  int ret;

  if (bufsize > CONFIG_DEV_PIPE_MAXSIZE)
    {
      return NULL;
    }

  /* Allocate a private structure to manage the pipe */

  dev = (FAR struct pipe_dev_s *)malloc(sizeof(struct pipe_dev_s));
  if (dev)
    {
      /* Initialize the private structure */

      (void)memset_s(dev, sizeof(struct pipe_dev_s), 0, sizeof(struct pipe_dev_s));
      ret = strcpy_s(dev->name, sizeof(dev->name), name);
      if (ret < 0)
        {
          free(dev);
          return NULL;
        }
      sem_init(&dev->d_bfsem, 0, 1);
      sem_init(&dev->d_rdsem, 0, 0);
      sem_init(&dev->d_wrsem, 0, 0);
      LOS_ListInit(&dev->wq.poll_queue);
     /* The read/write wait semaphores are used for signaling and, hence,
      * should not have priority inheritance enabled.
      */

      dev->d_bufsize = bufsize;
    }

  return dev;
}

/****************************************************************************
 * Name: pipecommon_freedev
 ****************************************************************************/

void pipecommon_freedev(FAR struct pipe_dev_s *dev)
{
  sem_destroy(&dev->d_bfsem);
  sem_destroy(&dev->d_rdsem);
  sem_destroy(&dev->d_wrsem);
  free(dev);
}

/****************************************************************************
 * Name: pipecommon_open
 ****************************************************************************/

int pipecommon_open(FAR struct file *filep)
{
  FAR struct inode      *inode = filep->f_inode;
  FAR struct pipe_dev_s *dev   = inode->i_private;
  int                    sval;
  int                    ret;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  /* Make sure that we have exclusive access to the device structure.  The
   * sem_wait() call should fail only if we are awakened by a signal.
   */

  ret = sem_wait(&dev->d_bfsem);
  if (ret < 0)
    {
      PRINT_ERR("ERROR: sem_wait failed: %d\n", ret);
      return ret;
    }

  /* If this the first reference on the device, then allocate the buffer.
   * In the case of policy 1, the buffer already be present when the pipe
   * is first opened.
   */

  if (inode->i_crefs == 1 && dev->d_buffer == NULL)
    {
      dev->d_buffer = (FAR uint8_t *)malloc(dev->d_bufsize);
      if (!dev->d_buffer)
        {
          (void)sem_post(&dev->d_bfsem);
          return -ENOMEM;
        }
    }


  /* If opened for writing, increment the count of writers on the pipe instance */

  if ((filep->f_oflags & O_WRONLY) != 0)
    {
      dev->d_nwriters++;

      /* If this this is the first writer, then the read semaphore indicates the
       * number of readers waiting for the first writer.  Wake them all up.
       */

      if (dev->d_nwriters == 1)
        {
          while (sem_getvalue(&dev->d_rdsem, &sval) == 0 && sval == 0)
            {
              sem_post(&dev->d_rdsem);
            }
        }
    }

  /* If opened for reading, increment the count of reader on on the pipe instance */

  if ((filep->f_oflags & O_WRONLY) == 0)
    {
      dev->d_nreaders++;
    }

  /* If opened for read-only, then wait for either (1) at least one writer
   * on the pipe (policy == 0), or (2) until there is buffered data to be
   * read (policy == 1).
   */

  (void)sem_post(&dev->d_bfsem);

  if ((filep->f_oflags & O_WRONLY) == 0 &&       /* Read-only */
      dev->d_nwriters < 1 &&                     /* No writers on the pipe */
      dev->d_wrndx == dev->d_rdndx)              /* Buffer is empty */
    {
      /* NOTE: d_rdsem is normally used when the read logic waits for more
       * data to be written.  But until the first writer has opened the
       * pipe, the meaning is different: it is used prevent O_RDONLY open
       * calls from returning until there is at least one writer on the pipe.
       * This is required both by spec and also because it prevents
       * subsequent read() calls from returning end-of-file because there is
       * no writer on the pipe.
       */

      ret = sem_wait(&dev->d_rdsem);
      if (ret < 0)
        {
          /* The sem_wait() call should fail only if we are awakened by
           * a signal.
           */

          PRINT_ERR("ERROR: sem_wait failed: %d\n", ret);

          /* Immediately close the pipe that we just opened */

          (void)pipecommon_close(filep);
        }
    }

  return ret;
}

/****************************************************************************
 * Name: pipecommon_close
 ****************************************************************************/

int pipecommon_close(FAR struct file *filep)
{
  FAR struct inode      *inode = filep->f_inode;
  FAR struct pipe_dev_s *dev   = inode->i_private;
  int                    sval;

  if (dev == NULL || filep->f_inode->i_crefs <= 0)
    {
      return -EINVAL;
    }

  /* Make sure that we have exclusive access to the device structure.
   * NOTE: close() is supposed to return EINTR if interrupted, however
   * I've never seen anyone check that.
   */

  pipecommon_semtake(&dev->d_bfsem);

  /* Decrement the number of references on the pipe.  Check if there are
   * still outstanding references to the pipe.
   */

  /* Check if the decremented inode reference count would go to zero */

  if (inode->i_crefs > 1)
    {
      /* More references.. If opened for writing, decrement the count of
       * writers on the pipe instance.
       */

      if ((filep->f_oflags & O_WRONLY) != 0)
        {
          /* If there are no longer any writers on the pipe, then notify all of the
           * waiting readers that they must return end-of-file.
           */

          if (--dev->d_nwriters <= 0)
            {
              while (sem_getvalue(&dev->d_rdsem, &sval) == 0 && sval == 0)
                {
                  sem_post(&dev->d_rdsem);
                }

              /* Inform poll readers that other end closed. */

              pipecommon_pollnotify(dev, POLLHUP);
            }
        }

      /* If opened for reading, decrement the count of readers on the pipe
       * instance.
       */

      if ((filep->f_oflags & O_WRONLY) == 0)
        {
          if (--dev->d_nreaders <= 0)
            {
              if (PIPE_IS_POLICY_0(dev->d_flags))
                {
                  /* Inform poll writers that other end closed. */

                  pipecommon_pollnotify(dev, POLLERR);
                }
            }
        }
    }

  /* What is the buffer management policy?  Do we free the buffer when the
   * last client closes the pipe policy 0, or when the buffer becomes empty.
   * In the latter case, the buffer data will remain valid and can be
   * obtained when the pipe is re-opened.
   */

  else if (PIPE_IS_POLICY_0(dev->d_flags) || dev->d_wrndx == dev->d_rdndx)
    {
      /* Policy 0 or the buffer is empty ... deallocate the buffer now. */

      free(dev->d_buffer);
      dev->d_buffer = NULL;

      /* And reset all counts and indices */

      dev->d_wrndx    = 0;
      dev->d_rdndx    = 0;
      dev->d_nwriters = 0;
      dev->d_nreaders = 0;
    }

  sem_post(&dev->d_bfsem);
  return OK;
}

/****************************************************************************
 * Name: pipecommon_read
 ****************************************************************************/

ssize_t pipecommon_read(FAR struct file *filep, FAR char *buffer, size_t len)
{
  FAR struct inode      *inode  = filep->f_inode;
  FAR struct pipe_dev_s *dev    = inode->i_private;
  ssize_t                nread  = 0;
  int                    sval;
  int                    ret;

  if (dev == NULL)
    {
      return -EINVAL;
    }

  if (len == 0)
    {
      return 0;
    }

  if (len > MAX_READ_WRITE_LEN)
    {
      return -EINVAL;
    }

  /* Make sure that we have exclusive access to the device structure */

  ret = sem_wait(&dev->d_bfsem);
  if (ret < 0)
    {
      return ret;
    }

  /* If the pipe is empty, then wait for something to be written to it */

  while (dev->d_wrndx == dev->d_rdndx)
    {
      /* If O_NONBLOCK was set, then return EGAIN */

      if (filep->f_oflags & O_NONBLOCK)
        {
          sem_post(&dev->d_bfsem);
          return -EAGAIN;
        }

      /* If there are no writers on the pipe, then return end of file */

      if (dev->d_nwriters <= 0)
        {
          sem_post(&dev->d_bfsem);
          return 0;
        }

      /* Otherwise, wait for something to be written to the pipe */

      sem_post(&dev->d_bfsem);
      ret = sem_wait(&dev->d_rdsem);

      if (ret < 0 || (ret = sem_wait(&dev->d_bfsem)) < 0)
        {
          return ret;
        }
    }

  /* Then return whatever is available in the pipe (which is at least one byte) */

  nread = 0;
  for (; ; )
    {
      while ((size_t)nread < len && dev->d_wrndx != dev->d_rdndx)
        {
          ret = LOS_ArchCopyToUser(buffer, dev->d_buffer + dev->d_rdndx, sizeof(char));
          if (ret != 0)
            {
              sem_post(&dev->d_bfsem);
              return -EFAULT;
            }
          buffer++;
          if (++dev->d_rdndx >= dev->d_bufsize)
            {
              dev->d_rdndx = 0;
            }

          nread++;
        }

       /* If O_NONBLOCK was set, then break */

      if (filep->f_oflags & O_NONBLOCK)
        {
          break;
        }

      /* Is the read complete?  */

      if ((size_t)nread >= len)
        {
          break;
        }

      /* wait for something to be written to the pipe */

      sem_post(&dev->d_wrsem);
      pipecommon_pollnotify(dev, POLLOUT);
      sem_post(&dev->d_bfsem);

      ret = sem_wait(&dev->d_rdsem);
      if (ret < 0)
        {
          return ret;
        }

      ret = sem_wait(&dev->d_bfsem);
      if (ret < 0)
        {
          return ret;
        }

      /* If there are no writers on the pipe, then return end of file */

      if (dev->d_nwriters <= 0)
        {
          sem_post(&dev->d_wrsem);
          pipecommon_pollnotify(dev, POLLOUT);
          sem_post(&dev->d_bfsem);
          return nread;
        }
    }

  /* Notify all waiting writers that bytes have been removed from the buffer */

  while (sem_getvalue(&dev->d_wrsem, &sval) == 0 && sval == 0)
    {
      sem_post(&dev->d_wrsem);
    }

  /* Notify all poll/select waiters that they can write to the FIFO */

  pipecommon_pollnotify(dev, POLLOUT);
  sem_post(&dev->d_bfsem);
  return nread;
}

/****************************************************************************
 * Name: pipecommon_write
 ****************************************************************************/

ssize_t pipecommon_write(FAR struct file *filep, FAR const char *buffer,
                         size_t len)
{
  FAR struct inode      *inode    = filep->f_inode;
  FAR struct pipe_dev_s *dev      = inode->i_private;
  ssize_t                nwritten = 0;
  ssize_t                last;
  int                    nxtwrndx;
  int                    sval;
  int                    ret;


  if (dev == NULL)
    {
      return -EINVAL;
    }

  /* Handle zero-length writes */

  if (len == 0)
    {
      return 0;
    }

  if (len > MAX_READ_WRITE_LEN)
    {
      return -EINVAL;
    }

  /* REVISIT:  "If all file descriptors referring to the read end of a pipe
   * have been closed, then a write will cause a SIGPIPE signal to be
   * generated for the calling process.  If the calling process is ignoring
   * this signal, then write(2) fails with the error EPIPE."
   */

  if (dev->d_nreaders <= 0)
    {
      return -EPIPE;
    }

  /* At present, this method cannot be called from interrupt handlers.  That
   * is because it calls sem_wait (via pipecommon_semtake below) and
   * sem_wait cannot be called from interrupt level.  This actually
   * happens fairly commonly IF [a-z]err() is called from interrupt handlers
   * and stdout is being redirected via a pipe.  In that case, the debug
   * output will try to go out the pipe (interrupt handlers should use the
   * _err() APIs).
   *
   * On the other hand, it would be very valuable to be able to feed the pipe
   * from an interrupt handler!  TODO:  Consider disabling interrupts instead
   * of taking semaphores so that pipes can be written from interrupt handlers
   */

  /* Make sure that we have exclusive access to the device structure */

  ret = sem_wait(&dev->d_bfsem);
  if (ret < 0)
    {
      return ret;
    }

  /* Loop until all of the bytes have been written */

  last = 0;
  for (; ; )
    {
      /* Calculate the write index AFTER the next byte is written */

      nxtwrndx = dev->d_wrndx + 1;
      if (nxtwrndx >= dev->d_bufsize)
        {
          nxtwrndx = 0;
        }

      /* Would the next write overflow the circular buffer? */

      if (nxtwrndx != dev->d_rdndx)
        {
          /* No... copy the byte */


          ret = LOS_ArchCopyFromUser(dev->d_buffer + dev->d_wrndx, buffer, sizeof(char));
          if (ret != 0)
            {
              sem_post(&dev->d_bfsem);
              return -EFAULT;
            }
          buffer++;
          dev->d_wrndx = nxtwrndx;

          /* Is the write complete? */

          nwritten++;
          if ((size_t)nwritten >= len)
            {
              /* Yes.. Notify all of the waiting readers that more data is available */
              while (sem_getvalue(&dev->d_rdsem, &sval) == 0 && sval == 0)
                {
                  sem_post(&dev->d_rdsem);
                }

              /* Notify all poll/select waiters that they can read from the FIFO */

              pipecommon_pollnotify(dev, POLLIN);

              /* Return the number of bytes written */

              sem_post(&dev->d_bfsem);
              return len;
            }
        }
      else
        {
          /* There is not enough room for the next byte.  Was anything written in this pass? */

          if (last < nwritten)
            {
              /* Yes.. Notify all of the waiting readers that more data is available */

              while (sem_getvalue(&dev->d_rdsem, &sval) == 0 && sval == 0)
                {
                  sem_post(&dev->d_rdsem);
                }

              /* Notify all poll/select waiters that they can read from the FIFO */

              pipecommon_pollnotify(dev, POLLIN);
            }

          last = nwritten;

          /* If O_NONBLOCK was set, then return partial bytes written or EGAIN */

          if (filep->f_oflags & O_NONBLOCK)
            {
              if (nwritten == 0)
                {
                  nwritten = -EAGAIN;
                }

              sem_post(&dev->d_bfsem);
              return nwritten;
            }

          /* There is more to be written.. wait for data to be removed from the pipe */

          sem_post(&dev->d_bfsem);
          pipecommon_semtake(&dev->d_wrsem);
          pipecommon_semtake(&dev->d_bfsem);
        }
    }
}

/****************************************************************************
 * Name: pipecommon_poll
 ****************************************************************************/

int pipecommon_poll(FAR struct file *filep, poll_table *table)
{
  FAR struct inode      *inode    = filep->f_inode;
  FAR struct pipe_dev_s *dev      = inode->i_private;
  pollevent_t            eventset;
  pipe_ndx_t             nbytes;
  int                    ret      = OK;

  if (dev == NULL || table == NULL)
    {
      return -EINVAL;
    }

  /* Are we setting up the poll?  Or tearing it down? */

  pipecommon_semtake(&dev->d_bfsem);

  /* Should immediately notify on any of the requested events?
   * First, determine how many bytes are in the buffer
   */

  if (dev->d_wrndx >= dev->d_rdndx)
    {
      nbytes = dev->d_wrndx - dev->d_rdndx;
    }
  else
    {
      nbytes = dev->d_bufsize + dev->d_wrndx - dev->d_rdndx;
    }

  /* Notify the POLLOUT event if the pipe is not full, but only if
   * there is readers.
   */

  eventset = 0;
  if (((filep->f_oflags & O_WRONLY) != 0) && (nbytes < (dev->d_bufsize - 1)))
    {
      eventset |= POLLOUT;
    }

  /* Notify the POLLIN event if the pipe is not empty */

  if (((filep->f_oflags & O_WRONLY) == 0) && (nbytes > 0))
    {
      eventset |= POLLIN;
    }

  /* Notify the POLLHUP event if the pipe is empty and no writers */

  if (nbytes == 0 && dev->d_nwriters <= 0)
    {
      eventset |= POLLHUP;
    }

  /* Change POLLOUT to POLLERR, if no readers and policy 0. */

  if ((eventset | POLLOUT) &&
      PIPE_IS_POLICY_0(dev->d_flags) &&
      dev->d_nreaders <= 0)
    {
      eventset |= POLLERR;
    }

  ret = eventset & table->key;
  if (ret == 0)
    {
      poll_wait(NULL, &dev->wq, table);
    }
  sem_post(&dev->d_bfsem);

  return ret;
}

/****************************************************************************
 * Name: pipecommon_ioctl
 ****************************************************************************/

int pipecommon_ioctl(FAR struct file *filep, int cmd, unsigned long arg)
{
  return -ENOSYS;
}

/****************************************************************************
 * Name: pipecommon_unlink
 ****************************************************************************/

#ifndef CONFIG_DISABLE_PSEUDOFS_OPERATIONS
int pipecommon_unlink(FAR struct inode *inode)
{
  FAR struct pipe_dev_s *dev;

  if (inode == NULL || inode->i_private == NULL)
    {
      return -EINVAL;
    }

  dev = (FAR struct pipe_dev_s *)inode->i_private;

  /* Are the any open references to the driver? */

  if (inode->i_crefs == 1)
    {
      /* No.. free the buffer (if there is one) */

      if (dev->d_buffer)
        {
          free(dev->d_buffer);
        }

      /* And free the device structure. */
      unregister_driver(dev->name);
      pipecommon_freedev(dev);
    }
  else
    {
      PRINTK("Device busy!\n");
      return -EBUSY;
    }

  return OK;
}
#endif

#endif /* LOSCFG_KERNEL_PIPE */
