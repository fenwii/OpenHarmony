/****************************************************************************
 * drivers/bch/bchlib_cache.c
 *
 *   Copyright (C) 2008-2009, 2014, 2016 Gregory Nutt. All rights reserved.
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
#include <stdbool.h>
#include <errno.h>
#include <assert.h>
#include <debug.h>
#include "bch.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: bchlib_flushsector
 *
 * Description:
 *   Flush the current contents of the sector buffer (if dirty)
 *
 * Assumptions:
 *   Caller must assume mutual exclusion
 *
 ****************************************************************************/

int bchlib_flushsector(FAR struct bchlib_s *bch)
{
  int ret = OK;

  /* Check if the sector has been modified and is out of synch with the
   * media.
   */

  if (bch->dirty)
    {
      /* Write the sector to the media */

      ret = los_disk_write(bch->disk->disk_id, (FAR const void *)bch->buffer, bch->sector, 1);
      if (ret < 0)
        {
          PRINTK("bchlib_flushsector Write failed: %d\n", ret);
          return ret;
        }

      /* The sector is now in sync with the media */

      bch->dirty = false;
    }

  return ret;
}

/****************************************************************************
 * Name: bchlib_readsector
 *
 * Description:
 *   Flush the current contents of the sector buffer (if dirty)
 *
 * Assumptions:
 *   Caller must assume mutual exclusion
 *
 ****************************************************************************/

int bchlib_readsector(FAR struct bchlib_s *bch, unsigned long long sector)
{
  int ret = OK;

  if (bch->sector != sector)
    {
      ret = bchlib_flushsector(bch);
      if (ret < 0)
        {
          return ret;
        }

      bch->sector = (unsigned long long)-1;
      ret = los_disk_read(bch->disk->disk_id, (FAR void *)bch->buffer, sector, 1);
      if (ret < 0)
        {
          PRINTK("Read failed: %d\n", ret);
          return ret;
        }
      bch->sector = sector;
    }
  return ret;
}

