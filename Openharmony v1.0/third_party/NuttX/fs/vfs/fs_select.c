/****************************************************************************
 * fs/vfs/fs_select.c
 *
 *   Copyright (C) 2008-2009, 2012-2013 Gregory Nutt. All rights reserved.
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

#include "vfs_config.h"

#include "sys/select.h"

#include "string.h"
#include "unistd.h"
#include "poll.h"
#include "assert.h"
#include "errno.h"
#include "debug.h"

#include "stdlib.h"
#include "fs/fs.h"

#include "los_syscall.h"

#include "inode/inode.h"
#ifndef CONFIG_DISABLE_POLL


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define POLL_IN_SET (POLLIN | POLLRDNORM | POLLRDBAND | POLLHUP | POLLERR)
#define POLL_OUT_SET (POLLOUT | POLLWRBAND | POLLWRNORM | POLLERR)
#define POLL_EX_SET (POLLPRI)

/* pollfd count in stack, optimization in order to avoid small memory allocation */

#define POLL_STACK_CNT 5

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/
extern unsigned int sleep(unsigned int seconds);

/****************************************************************************
 * Name: select
 *
 * Description:
 *   select() allows a program to monitor multiple file descriptors, waiting
 *   until one or more of the file descriptors become "ready" for some class
 *   of I/O operation (e.g., input possible).  A file descriptor is
 *   considered  ready if it is possible to perform the corresponding I/O
 *   operation (e.g., read(2)) without blocking.
 *
 *   NOTE: poll() is the fundamental API for performing such monitoring
 *   operation under NuttX.  select() is provided for compatibility and
 *   is simply a layer of added logic on top of poll().  As such, select()
 *   is more wasteful of resources and poll() is the recommended API to be
 *   used.
 *
 * Input Parameters:
 *   nfds - the maximum fd number (+1) of any descriptor in any of the
 *     three sets.
 *   readfds - the set of descriptions to monitor for read-ready events
 *   writefds - the set of descriptions to monitor for write-ready events
 *   exceptfds - the set of descriptions to monitor for error events
 *   timeout - Return at this time if none of these events of interest
 *     occur.
 *
 *  Returned Value:
 *   0: Timer expired
 *  >0: The number of bits set in the three sets of descriptors
 *  -1: An error occurred (errno will be set appropriately)
 *
 ****************************************************************************/

int do_select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout, PollFun poll)
{
  struct pollfd *pollset = NULL;
  struct pollfd pfd[POLL_STACK_CNT];
  int pfd_alloc_flag = 0;
  int fd;
  int npfds;
  int msec;
  int ndx;
  int ret;

  if (nfds < 0)
    {
      set_errno(EINVAL);
      return VFS_ERROR;
    }

  /* How many pollfd structures do we need to allocate? */

  /* Initialize the descriptor list for poll() */

  for (fd = 0, npfds = 0; fd < nfds; fd++)
    {
      /* Check if any monitor operation is requested on this fd */

      if ((readfds   && FD_ISSET(fd, readfds))  ||
          (writefds  && FD_ISSET(fd, writefds)) ||
          (exceptfds && FD_ISSET(fd, exceptfds)))
        {
          /* Yes.. increment the count of pollfds structures needed */

          npfds++;
        }
    }

  /* Allocate the descriptor list for poll() */

  if (npfds != 0)
    {
      /* use stack variable in order to avoid small memory allocation. */

      if (npfds <= POLL_STACK_CNT)
        {
          pollset = pfd;
          (void)memset_s(pollset, npfds * sizeof(struct pollfd), 0, npfds * sizeof(struct pollfd));
        }
      else
        {
          pollset = (struct pollfd *)zalloc(npfds * sizeof(struct pollfd));
          if (pollset == NULL)
            {
              set_errno(ENOMEM);
              return VFS_ERROR;
            }
          pfd_alloc_flag = 1;
        }
    }
  else
    {
      /* If the readfds, writefds, and exceptfds arguments are all null pointers and
       * the timeout argument is not a null pointer, the select() function shall block for
       * the time specified. If the readfds, writefds, and exceptfds arguments are all
       * null pointers and the timeout argument is a null pointer, this is NOT permitted
       * as LiteOS doesn't support Signal machanism, so select() can't come back anymore.
       */

      if (timeout != NULL)
        {
          /* 1000000 : Convert seconds to microseconds. */

          if ((long long)timeout->tv_sec * 1000000 > 0xffffffff)
            {
              (void)sleep(timeout->tv_sec);
            }
          else
            {
              (void)usleep(timeout->tv_sec * 1000000 + timeout->tv_usec);
            }
          return OK;
        }
      else
        {
          set_errno(EINVAL);
          return VFS_ERROR;
        }
    }

  /* Initialize the descriptor list for poll() */

  for (fd = 0, ndx = 0; fd < nfds; fd++)
    {
      int incr = 0;

      /* The readfs set holds the set of FDs that the caller can be assured
       * of reading from without blocking.  Note that POLLHUP is included as
       * a read-able condition.  POLLHUP will be reported at the end-of-file
       * or when a connection is lost.  In either case, the read() can then
       * be performed without blocking.
       */

      if (readfds && FD_ISSET(fd, readfds))
        {
          pollset[ndx].fd = fd;
          pollset[ndx].events |= (POLLIN | POLLRDNORM);
          incr = 1;
        }

      /* The writefds set holds the set of FDs that the caller can be assured
       * of writing to without blocking.
       */

      if (writefds && FD_ISSET(fd, writefds))
        {
          pollset[ndx].fd      = fd;
          pollset[ndx].events |= (POLLOUT | POLLWRNORM);
          incr                 = 1;
        }

      /* The exceptfds set holds the set of FDs that are watched for exceptions */

      if (exceptfds && FD_ISSET(fd, exceptfds))
        {
          pollset[ndx].fd      = fd;
          incr                  = 1;
        }

      ndx += incr;
    }

  DEBUGASSERT(ndx == npfds);

  /* Convert the timeout to milliseconds */

  if (timeout)
    {
      /* Calculate the timeout in milliseconds */

      msec = timeout->tv_sec * 1000 + timeout->tv_usec / 1000;
    }
  else
    {
      /* Any negative value of msec means no timeout */

      msec = -1;
    }

  /* Then let poll do all of the real work. */

  ret = poll(pollset, npfds, msec);

  /* Now set up the return values */

  if (readfds)
    {
      (void)memset_s(readfds, sizeof(fd_set), 0, sizeof(fd_set));
    }

  if (writefds)
    {
      (void)memset_s(writefds, sizeof(fd_set), 0, sizeof(fd_set));
    }

  if (exceptfds)
    {
      (void)memset_s(exceptfds, sizeof(fd_set), 0, sizeof(fd_set));
    }

  /* Convert the poll descriptor list back into selects 3 bitsets */

  if (ret > 0)
    {
      ret = 0;
      for (ndx = 0; ndx < npfds; ndx++)
        {
          /* Check for read conditions.  Note that POLLHUP is included as a
           * read condition.  POLLHUP will be reported when no more data will
           * be available (such as when a connection is lost).  In either
           * case, the read() can then be performed without blocking.
           */

          if (readfds)
            {
              if (pollset[ndx].revents & POLL_IN_SET)
                {
                  FD_SET(pollset[ndx].fd, readfds);
                  ret++;
                }
            }

          /* Check for write conditions */

          if (writefds)
            {
              if (pollset[ndx].revents & POLL_OUT_SET)
                {
                  FD_SET(pollset[ndx].fd, writefds);
                  ret++;
                }
            }

          /* Check for exceptions */

          if (exceptfds)
            {
              if (pollset[ndx].revents & POLL_EX_SET)
                {
                  FD_SET(pollset[ndx].fd, exceptfds);
                  ret++;
                }
            }
        }
    }

  if (pfd_alloc_flag)
    {
      free(pollset);
    }
  return ret;
}

int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout)
{
  return do_select(nfds, readfds, writefds, exceptfds, timeout, poll);
}

#endif /* CONFIG_DISABLE_POLL */
