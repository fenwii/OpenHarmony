/****************************************************************************
 * graphics/fb/fb.c
 * Framebuffer character driver
 *
 *   Copyright (C) 2017 Gregory Nutt. All rights reserved.
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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "fb.h"
#include "fs/fs.h"
#include "assert.h"
#include "errno.h"
#include "user_copy.h"

#define gerr PRINT_ERR

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* This structure defines one framebuffer device.  Note that which is
 * everything in this structure is constant data set up and initialization
 * time.  Therefore, no there is requirement for serialized access to this
 * structure.
 */

struct fb_chardev_s
{
  FAR struct fb_vtable_s *vtable; /* Framebuffer interface */
  FAR void *fbmem;                /* Start of frame buffer memory */
  size_t fblen;                   /* Size of the framebuffer */
  uint8_t plane;                  /* Video plan number */
  uint8_t bpp;                    /* Bits per pixel */
};

#define FB_DEV_MAXNUM   32
static struct fb_chardev_s *g_fb_dev[FB_DEV_MAXNUM] = {NULL};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int     fb_open(FAR struct file *filep);
static int     fb_close(FAR struct file *filep);
static ssize_t fb_read(FAR struct file *filep, FAR char *buffer,
                 size_t buflen);
static ssize_t fb_write(FAR struct file *filep, FAR const char *buffer,
                 size_t buflen);
static off_t   fb_seek(FAR struct file *filep, off_t offset, int whence);
static int     fb_ioctl(FAR struct file *filep, int cmd, unsigned long arg);
static ssize_t fb_mmap(FAR struct file* filep, FAR LosVmMapRegion *region);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct file_operations_vfs fb_fops =
{
  fb_open,       /* open */
  fb_close,      /* close */
  fb_read,       /* read */
  fb_write,      /* write */
  fb_seek,       /* seek */
  fb_ioctl,      /* ioctl */
  fb_mmap,        /* mmap */
#ifndef CONFIG_DISABLE_POLL
  NULL,          /* poll */
#endif
#ifndef CONFIG_DISABLE_PSEUDOFS_OPERATIONS
  NULL,          /* unlink */
#endif
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static ssize_t fb_mmap(FAR struct file *filep, FAR LosVmMapRegion *region)
{
  int ret = -EINVAL;
  struct fb_chardev_s *fb;
  struct fb_vtable_s *vtable;

  fb = (struct fb_chardev_s *)filep->f_inode->i_private;
  if (fb == NULL)
    {
      return -ENODEV;
    }

  vtable = fb->vtable;
  if (vtable == NULL)
    {
      return -EINVAL;
    }

  if (vtable->fb_mmap != NULL)
    {
      ret = vtable->fb_mmap(vtable, region);
    }

  return ret;
}

/****************************************************************************
 * Name: fb_open
 *
 * Description:
 *   This function is called whenever the framebuffer device is opened.
 *
 ****************************************************************************/

static int fb_open(FAR struct file *filep)
{
  DEBUGASSERT(filep != NULL && filep->f_inode != NULL);
  struct fb_chardev_s *fb;
  struct fb_vtable_s *vtable;
  int ret = -EINVAL;

  fb = (struct fb_chardev_s *)filep->f_inode->i_private;
  if (fb == NULL)
    {
      return -ENODEV;
    }

  vtable = fb->vtable;
  if (vtable == NULL)
    {
      return -EINVAL;
    }

  if (vtable->fb_open)
    {
      ret = vtable->fb_open(vtable);
    }

  return ret;
}

/****************************************************************************
 * Name: fb_close
 *
 * Description:
 *   This function is called when the framebuffer device is closed.
 *
 ****************************************************************************/

static int fb_close(FAR struct file *filep)
{
  DEBUGASSERT(filep != NULL && filep->f_inode != NULL);
  struct fb_chardev_s *fb;
  struct fb_vtable_s *vtable;
  int ret = -EINVAL;

  fb = (struct fb_chardev_s *)filep->f_inode->i_private;
  if (fb == NULL)
    {
      return -ENODEV;
    }

  vtable = fb->vtable;
  if (vtable == NULL)
    {
      return -EINVAL;
    }

  if (vtable->fb_release)
    {
      ret = vtable->fb_release(vtable);
    }

  return ret;
}

/****************************************************************************
 * Name: fb_read
 ****************************************************************************/

static ssize_t fb_read(FAR struct file *filep, FAR char *buffer, size_t len)
{
  FAR struct inode *inode;
  FAR struct fb_chardev_s *fb;
  size_t start;
  size_t end;
  size_t size;
  int ret;

  /* Get the framebuffer instance */

  DEBUGASSERT(filep != NULL && filep->f_inode != NULL);
  inode = filep->f_inode;
  fb    = (FAR struct fb_chardev_s *)inode->i_private;

  /* Get the start and size of the transfer */

  start = filep->f_pos;
  if (start >= fb->fblen)
    {
      return 0;  /* Return end-of-file */
    }

  end = start + len;
  if (end >= fb->fblen)
    {
      end = fb->fblen;
    }

  size = end - start;

  /* And transfer the data from the frame buffer */

  ret = LOS_ArchCopyToUser(buffer, fb->fbmem, size);
  if (ret)
    {
      return -EFAULT;
    }
  filep->f_pos += size;
  return size;
}

/****************************************************************************
 * Name: fb_write
 ****************************************************************************/

static ssize_t fb_write(FAR struct file *filep, FAR const char *buffer,
                        size_t len)
{
  FAR struct inode *inode;
  FAR struct fb_chardev_s *fb;
  size_t start;
  size_t end;
  size_t size;
  int ret;

  /* Get the framebuffer instance */

  DEBUGASSERT(filep != NULL && filep->f_inode != NULL);
  inode = filep->f_inode;
  fb    = (FAR struct fb_chardev_s *)inode->i_private;

  /* Get the start and size of the transfer */

  start = filep->f_pos;
  if (start >= fb->fblen)
    {
      return -EFBIG;  /* Cannot extend the framebuffer */
    }

  end = start + len;
  if (end >= fb->fblen)
    {
      end = fb->fblen;
    }

  size = end - start;

  /* And transfer the data into the frame buffer */

  ret = LOS_ArchCopyFromUser(fb->fbmem, buffer, size);
  if (ret)
    {
      return -EFAULT;
    }
  filep->f_pos += size;
  return size;
}

/****************************************************************************
 * Name: fb_seek
 *
 * Description:
 *   Seek the logical file pointer to the specified position.  The offset
 *   is in units of pixels, with offset zero being the beginning of the
 *   framebuffer.
 *
 ****************************************************************************/

static off_t fb_seek(FAR struct file *filep, off_t offset, int whence)
{
  FAR struct inode *inode;
  FAR struct fb_chardev_s *fb;
  off_t newpos;
  int ret;

  /* Get the framebuffer instance */

  DEBUGASSERT(filep != NULL && filep->f_inode != NULL);
  inode = filep->f_inode;
  fb    = (FAR struct fb_chardev_s *)inode->i_private;

  /* Determine the new, requested file position */

  switch (whence)
    {
    case SEEK_CUR:
      newpos = filep->f_pos + offset;
      break;

    case SEEK_SET:
      newpos = offset;
      break;

    case SEEK_END:
      newpos = fb->fblen + offset;
      break;

    default:
      /* Return EINVAL if the whence argument is invalid */

      return -EINVAL;
    }

  /* Opengroup.org:
   *
   *  "The lseek() function shall allow the file offset to be set beyond the end
   *   of the existing data in the file. If data is later written at this point,
   *   subsequent reads of data in the gap shall return bytes with the value 0
   *   until data is actually written into the gap."
   *
   * We can conform to the first part, but not the second.  But return EINVAL if
   *
   *  "...the resulting file offset would be negative for a regular file, block
   *   special file, or directory."
   */

  if (newpos >= 0)
    {
      filep->f_pos = newpos;
      ret = newpos;
    }
  else
    {
      ret = -EINVAL;
    }

  return ret;
}

/****************************************************************************
 * Name: fb_ioctl
 *
 * Description:
 *   The standard ioctl method.
 *
 ****************************************************************************/

static int fb_ioctl(FAR struct file *filep, int cmd, unsigned long arg)
{
  FAR struct inode *inode;
  FAR struct fb_chardev_s *fb;
  int ret;

  /* Get the framebuffer instance */

  DEBUGASSERT(filep != NULL && filep->f_inode != NULL);
  inode = filep->f_inode;
  fb    = (FAR struct fb_chardev_s *)inode->i_private;

  /* Process the IOCTL command */

  switch (cmd)
    {
      case FIOC_MMAP:  /* Get color plane info */
        {
          FAR void **ppv = (FAR void **)((uintptr_t)arg);
          uintptr_t fbmem = (uintptr_t)fb->fbmem;

          /* Return the address corresponding to the start of frame buffer. */

          ret = LOS_ArchCopyToUser(ppv, &fbmem, sizeof(uintptr_t));
          if (ret)
            {
              ret = -EFAULT;
            }
        }
        break;

      case FBIOGET_VIDEOINFO:  /* Get color plane info */
        {
          struct fb_videoinfo_s vinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->getvideoinfo != NULL);
          ret = fb->vtable->getvideoinfo(fb->vtable, &vinfo);
          if (ret == ENOERR)
            {
              ret = LOS_ArchCopyToUser((void *)arg, &vinfo, sizeof(struct fb_videoinfo_s));
              if (ret)
                {
                  ret = -EFAULT;
                }
            }
        }
        break;

      case FBIOGET_PLANEINFO:  /* Get video plane info */
        {
          struct fb_planeinfo_s pinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->getplaneinfo != NULL);
          ret = fb->vtable->getplaneinfo(fb->vtable, fb->plane, &pinfo);
          if (ret == ENOERR)
            {
              ret = LOS_ArchCopyToUser((void *)arg, &pinfo, sizeof(struct fb_planeinfo_s));
              if (ret)
                {
                  ret = -EFAULT;
                }
            }
        }
        break;

#ifdef CONFIG_FB_CMAP
      case FBIOGET_CMAP:       /* Get RGB color mapping */
        {
          struct fb_cmap_s cmap;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->getcmap != NULL);
          ret = fb->vtable->getcmap(fb->vtable, &cmap);
          if (ret == ENOERR)
            {
              ret = LOS_ArchCopyToUser((void *)arg, &cmap, sizeof(struct fb_cmap_s));
              if (ret)
                {
                  ret = -EFAULT;
                }
            }
        }
        break;

      case FBIOPUT_CMAP:       /* Put RGB color mapping */
        {
          struct fb_cmap_s cmap;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->putcmap != NULL);
          ret = LOS_ArchCopyFromUser(&cmap, (const void *)arg, sizeof(struct fb_cmap_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->putcmap(fb->vtable, &cmap);
        }
        break;
#endif
#ifdef CONFIG_FB_HWCURSOR
      case FBIOGET_CURSOR:     /* Get cursor attributes */
        {
          struct fb_cursorattrib_s attrib;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->getcursor != NULL);
          ret = fb->vtable->getcursor(fb->vtable, &attrib);
          if (ret == ENOERR)
            {
              ret = LOS_ArchCopyToUser((void *)arg, &attrib, sizeof(struct fb_cursorattrib_s));
              if (ret)
                {
                  ret = -EFAULT;
                }
            }
        }
        break;

      case FBIOPUT_CURSOR:     /* Set cursor attibutes */
        {
          struct fb_setcursor_s cursor;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->setcursor != NULL);
          ret = LOS_ArchCopyFromUser(&cursor, (const void *)arg, sizeof(struct fb_setcursor_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->setcursor(fb->vtable, &cursor);
        }
        break;
#endif

#ifdef CONFIG_LCD_UPDATE
      case FBIO_UPDATE:  /* Update the LCD with the modified framebuffer data  */
        {
          struct nxgl_rect_s rect;
          struct fb_planeinfo_s pinfo;

          DEBUGASSERT(fb->vtable != NULL && fb->vtable->getplaneinfo != NULL);
          ret = LOS_ArchCopyFromUser(&rect, (const void *)arg, sizeof(struct nxgl_rect_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->getplaneinfo(fb->vtable, fb->plane, &pinfo);
          if (ret >= 0)
            {
               nx_notify_rectangle((FAR NX_PLANEINFOTYPE *)&pinfo, &rect);
            }
        }
        break;
#endif

#ifdef CONFIG_FB_SYNC
      case FBIO_WAITFORVSYNC:  /* Wait upon vertical sync */
        {
          ret = fb->vtable->waitforvsync(fb->vtable);
        }
        break;
#endif

#ifdef CONFIG_FB_OVERLAY
      case FBIO_SELECT_OVERLAY:  /* Select video overlay */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL && fb->vtable->getoverlayinfo != NULL);
          ret = fb->vtable->getoverlayinfo(fb->vtable, arg, &oinfo);
          if (ret == OK)
            {
              fb->fbmem = oinfo.fbmem;
              fb->fblen = oinfo.fblen;
              fb->bpp   = oinfo.bpp;
            }
        }
        break;

      case FBIOGET_OVERLAYINFO:  /* Get video overlay info */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->getoverlayinfo != NULL);
          ret = LOS_ArchCopyFromUser(&oinfo, (const void *)arg, sizeof(struct fb_overlayinfo_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->getoverlayinfo(fb->vtable, oinfo.overlay, &oinfo);
          if (ret == ENOERR)
            {
              ret = LOS_ArchCopyToUser((void *)arg, &oinfo, sizeof(struct fb_overlayinfo_s));
              if (ret)
                {
                  ret = -EFAULT;
                }
            }
        }
        break;

      case FBIOSET_TRANSP:  /* Set video overlay transparency */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->settransp != NULL);
          ret = LOS_ArchCopyFromUser(&oinfo, (const void *)arg, sizeof(struct fb_overlayinfo_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->settransp(fb->vtable, &oinfo);
        }
        break;

      case FBIOSET_CHROMAKEY:  /* Set video overlay chroma key */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->setchromakey != NULL);
          ret = LOS_ArchCopyFromUser(&oinfo, (const void *)arg, sizeof(struct fb_overlayinfo_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->setchromakey(fb->vtable, &oinfo);
        }
        break;

      case FBIOSET_COLOR:  /* Set video overlay color */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->setcolor != NULL);
          ret = LOS_ArchCopyFromUser(&oinfo, (const void *)arg, sizeof(struct fb_overlayinfo_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->setcolor(fb->vtable, &oinfo);
        }
        break;

      case FBIOSET_BLANK:  /* Blank or unblank video overlay */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->setblank != NULL);
          ret = LOS_ArchCopyFromUser(&oinfo, (const void *)arg, sizeof(struct fb_overlayinfo_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->setblank(fb->vtable, &oinfo);
        }
        break;

      case FBIOSET_AREA:  /* Set active video overlay area */
        {
          struct fb_overlayinfo_s oinfo;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->setarea != NULL);
          ret = LOS_ArchCopyFromUser(&oinfo, (const void *)arg, sizeof(struct fb_overlayinfo_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->setarea(fb->vtable, &oinfo);
        }
        break;

#ifdef CONFIG_FB_OVERLAY_BLIT
      case FBIOSET_BLIT:  /* Blit operation between video overlays */
        {
          struct fb_overlayblit_s blit;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->blit != NULL);
          ret = LOS_ArchCopyFromUser(&blit, (const void *)arg, sizeof(struct fb_overlayblit_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->blit(fb->vtable, &blit);
        }
        break;

      case FBIOSET_BLEND:  /* Blend operation between video overlays */
        {
          struct fb_overlayblend_s blend;

          DEBUGASSERT(fb->vtable != NULL &&
                      fb->vtable->blend != NULL);
          ret = LOS_ArchCopyFromUser(&blend, (const void *)arg, sizeof(struct fb_overlayblend_s));
          if (ret)
            {
              ret = -EFAULT;
              break;
            }
          ret = fb->vtable->blend(fb->vtable, &blend);
        }
        break;
#endif
#endif /* CONFIG_FB_OVERLAY */

      default:
        DEBUGASSERT(fb->vtable != NULL && fb->vtable->fb_ioctl != NULL);
        ret = fb->vtable->fb_ioctl(fb->vtable, cmd, arg);
        break;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: fb_register
 *
 * Description:
 *   Register the framebuffer character device at /dev/fbN where N is the
 *   display number if the devices supports only a single plane.  If the
 *   hardware supports multiple color planes, then the device will be
 *   registered at /dev/fbN.M where N is the again display number but M
 *   is the display plane.
 *
 * Input Parameters:
 *   display - The display number for the case of boards supporting multiple
 *             displays or for hardware that supports multiple
 *             layers (each layer is consider a display).  Typically zero.
 *   plane   - Identifies the color plane on hardware that supports separate
 *             framebuffer "planes" for each color component.
 *
 * Returned Value:
 *   Zero (OK) is returned success; a negated errno value is returned on any
 *   failure.
 *
 ****************************************************************************/

int fb_register(int display, int plane)
{
  FAR struct fb_chardev_s *fb;
  struct fb_videoinfo_s vinfo;
  struct fb_planeinfo_s pinfo;
#ifdef CONFIG_FB_OVERLAY
  struct fb_overlayinfo_s oinfo;
#endif
  char devname[16];
  int nplanes;
  int ret;

  if (display < 0 || display >= FB_DEV_MAXNUM)
    return -EINVAL;

  /* Allocate a framebuffer state instance */

  fb = (FAR struct fb_chardev_s *)malloc(sizeof(struct fb_chardev_s));
  if (fb == NULL)
    {
      return -ENOMEM;
    }

  /* Initialize the frame buffer device. */

  ret = up_fbinitialize(display);
  if (ret < 0)
    {
      gerr("ERROR: up_fbinitialize() failed for display %d: %d\n", display, ret);
      goto errout_with_fb;
    }

  DEBUGASSERT((unsigned)plane <= UINT8_MAX);
  fb->plane  = plane;

  fb->vtable = up_fbgetvplane(display, plane);
  if (fb->vtable == NULL)
    {
      gerr("ERROR: up_fbgetvplane() failed, vplane=%d\n", plane);
      goto errout_with_fb;
    }

  /* Initialize the frame buffer instance. */

  DEBUGASSERT(fb->vtable->getvideoinfo != NULL);
  ret = fb->vtable->getvideoinfo(fb->vtable, &vinfo);
  if (ret < 0)
    {
      gerr("ERROR: getvideoinfo() failed: %d\n", ret);
      goto errout_with_fb;
    }

  nplanes = vinfo.nplanes;
  DEBUGASSERT(vinfo.nplanes > 0 && (unsigned)plane < vinfo.nplanes);

  DEBUGASSERT(fb->vtable->getplaneinfo != NULL);
  ret = fb->vtable->getplaneinfo(fb->vtable, plane, &pinfo);
  if (ret < 0)
    {
      gerr("ERROR: getplaneinfo() failed: %d\n", ret);
      goto errout_with_fb;
    }

  fb->fbmem  = pinfo.fbmem;
  fb->fblen  = pinfo.fblen;
  fb->bpp    = pinfo.bpp;

  /* Clear the framebuffer memory */

  memset(pinfo.fbmem, 0, pinfo.fblen);

#ifdef CONFIG_FB_OVERLAY
  /* Initialize first overlay but do not select */

  DEBUGASSERT(fb->vtable->getoverlayinfo != NULL);
  ret = fb->vtable->getoverlayinfo(fb->vtable, 0, &oinfo);
  if (ret < 0)
    {
      gerr("ERROR: getoverlayinfo() failed: %d\n", ret);
      goto errout_with_fb;
    }

  /* Clear the overlay memory. Necessary when plane 0 and overlay 0
   * different.
   */

  memset(oinfo.fbmem, 0, oinfo.fblen);
#endif

  /* Register the framebuffer device */

  if (nplanes < 2)
    {
      (void)snprintf(devname, 16, "/dev/fb%d", display);
    }
  else
    {
      (void)snprintf(devname, 16, "/dev/fb%d.%d", display, plane);
    }

  ret = register_driver(devname, &fb_fops, 0666, (FAR void *)fb);
  if (ret < 0)
    {
      gerr("ERROR: register_driver() failed: %d\n", ret);
      goto errout_with_fb;
    }

    g_fb_dev[display] = fb;

    return OK;

errout_with_fb:
    free(fb);
    return ret;
}

int fb_unregister(int display)
{
    FAR struct fb_chardev_s *fb;

    if (display < 0 || display >= FB_DEV_MAXNUM)
        return -EINVAL;

    fb = g_fb_dev[display];

    up_fbuninitialize(display);

    free(fb);
    g_fb_dev[display] = NULL;

    return 0;
}
