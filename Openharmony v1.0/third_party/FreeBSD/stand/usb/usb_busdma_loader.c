/* $FreeBSD: releng/11.4/stand/usb/usb_busdma_loader.c 291399 2015-11-27 18:13:28Z zbb $ */
/*-
 * Copyright (c) 2013 Hans Petter Selasky. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <los_memory.h>
#include "los_vm_iomap.h"
#include "los_vm_map.h"
#include <asm/dma.h>
#include <user_copy.h>

#include "implementation/global_implementation.h"

#if USB_HAVE_BUSDMA
static void	usb_pc_common_mem_cb(struct usb_page_cache *pc,
							    void *vaddr, uint32_t length);
#endif

void
usb_dma_cache_invalid(void *addr, unsigned int size)
{
	UINTPTR start = (UINTPTR)addr & ~(USB_CACHE_ALIGN_SIZE - 1);
	UINTPTR end = (UINTPTR)addr + size;

	end = ALIGN(end, USB_CACHE_ALIGN_SIZE);
	DCacheInvRange(start, end);
}

void
usb_dma_cache_flush(void *addr, unsigned int size)
{
	UINTPTR start = (UINTPTR)addr & ~(USB_CACHE_ALIGN_SIZE - 1);
	UINTPTR end = (UINTPTR)addr + size;

	end = ALIGN(end, USB_CACHE_ALIGN_SIZE);
	DCacheFlushRange(start, end);
}

/*------------------------------------------------------------------------*
 *  usbd_get_page - lookup DMA-able memory for the given offset
 *
 * NOTE: Only call this function when the "page_cache" structure has
 * been properly initialized !
 *------------------------------------------------------------------------*/
void
usbd_get_page(struct usb_page_cache *pc, usb_frlength_t offset,
	struct usb_page_search *res)
{
#if USB_HAVE_BUSDMA
	struct usb_page *page;
	if (pc->page_start) {
		/* Case 1 - something has been loaded into DMA */

		if (pc->buffer) {

			/* Case 1a - Kernel Virtual Address */

			res->buffer = USB_ADD_BYTES(pc->buffer, offset);
		}
		offset += pc->page_offset_buf;

		/* compute destination page */

		page = pc->page_start;

		if (pc->ismultiseg) {

			page += (offset / USB_PAGE_SIZE);

			offset %= USB_PAGE_SIZE;

			res->length = USB_PAGE_SIZE - offset;
			res->physaddr = page->physaddr + offset;
		} else {
			res->length = (usb_size_t)-1;
			res->physaddr = page->physaddr + offset;
		}
		if (!pc->buffer) {

			/* Case 1b - Non Kernel Virtual Address */

			res->buffer = USB_ADD_BYTES(page->buffer, offset);
		}
		return;
	}
#endif
	/* Case 2 - Plain PIO */

	res->buffer = USB_ADD_BYTES(pc->buffer, offset);
	res->length = (usb_size_t)-1;
#if USB_HAVE_BUSDMA
	res->physaddr = 0;
#endif
}

/*------------------------------------------------------------------------*
 *  usbd_copy_in - copy directly to DMA-able memory
 *------------------------------------------------------------------------*/
void
usbd_copy_in(struct usb_page_cache *cache, usb_frlength_t offset,
	const void *ptr, usb_frlength_t len)
{
	struct usb_page_search buf_res;
	int ret;

	while (len != 0) {

		usbd_get_page(cache, offset, &buf_res);

		if (buf_res.length > len) {
			buf_res.length = len;
		}
		ret = memcpy_s(buf_res.buffer, buf_res.length, ptr, buf_res.length);
		if (ret != EOK) {
			return;
		}

		offset += buf_res.length;
		len -= buf_res.length;
		ptr = USB_ADD_BYTES(ptr, buf_res.length);
	}
}

/*------------------------------------------------------------------------*
 *  usbd_copy_out - copy directly from DMA-able memory
 *------------------------------------------------------------------------*/
void
usbd_copy_out(struct usb_page_cache *cache, usb_frlength_t offset,
	void *ptr, usb_frlength_t len)
{
	struct usb_page_search res;

	while (len != 0) {

		usbd_get_page(cache, offset, &res);

		if (res.length > len) {
			res.length = len;
		}
		(void)memcpy_s(ptr, len, res.buffer, res.length);

		offset += res.length;
		len -= res.length;
		ptr = USB_ADD_BYTES(ptr, res.length);
	}
}

int
copyin(const void *uaddr, void *kaddr, size_t len)
{
	size_t ret = LOS_ArchCopyFromUser(kaddr, uaddr, len);
	return ret ? EFAULT : 0;
}

int
copyout(const void *kaddr, void *uaddr, size_t len)
{
	size_t ret = LOS_ArchCopyToUser(uaddr, kaddr, len);
	return ret ? EFAULT : 0;
}

/* In user mode, the src buffer is from user */
int
usbd_copy_from_user(void *dest, uint32_t dest_len, const void *src, uint32_t src_len)
{
    int ret;

    if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)src, src_len)) {
        ret = memcpy_s(dest, dest_len, src, src_len);
    } else {
        ret = ((dest_len >= src_len) ? LOS_ArchCopyFromUser(dest, src, src_len) : ERANGE_AND_RESET);
    }

    return ret ? EFAULT : 0;
}

/* In user mode, the dest buffer is from user */
int
usbd_copy_to_user(void *dest, uint32_t dest_len, const void *src, uint32_t src_len)
{
    int ret;

    if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)dest, dest_len)) {
        ret = memcpy_s(dest, dest_len, src, src_len);
    } else {
        ret = ((dest_len >= src_len) ? LOS_ArchCopyToUser(dest, src, src_len) : ERANGE_AND_RESET);
    }

    return ret ? EFAULT : 0;
}

/*------------------------------------------------------------------------*
 *  usbd_frame_zero - zero DMA-able memory
 *------------------------------------------------------------------------*/
void
usbd_frame_zero(struct usb_page_cache *cache, usb_frlength_t offset,
	usb_frlength_t len)
{
	struct usb_page_search res;

	while (len != 0) {

		usbd_get_page(cache, offset, &res);

		if (res.length > len) {
			res.length = len;
		}
		(void)memset_s(res.buffer, res.length, 0, res.length);

		offset += res.length;
		len -= res.length;
	}
}

#if USB_HAVE_BUSDMA
/*------------------------------------------------------------------------*
 *	usb_pc_common_mem_cb - BUS-DMA callback function
 *------------------------------------------------------------------------*/
static void
usb_pc_common_mem_cb(struct usb_page_cache *pc, void *dma_handle, uint32_t length)
{
	struct usb_page *pg;
	usb_size_t rem;
	bus_size_t off;
	bus_addr_t phys = (bus_addr_t)(UINTPTR)dma_handle;

	pg = pc->page_start;
	pg->physaddr = phys & ~(USB_PAGE_SIZE - 1);
	rem = phys & (USB_PAGE_SIZE - 1);
	pc->page_offset_buf = rem;
	pc->page_offset_end += rem;
	length += rem;

	for (off = USB_PAGE_SIZE; off < length; off += USB_PAGE_SIZE) {
		pg++;
		pg->physaddr = (phys + off) & ~(USB_PAGE_SIZE - 1);
	}
}

/*------------------------------------------------------------------------*
 *	usb_pc_alloc_mem - allocate DMA'able memory
 *
 * Returns:
 *	0: Success
 * Else: Failure
 *------------------------------------------------------------------------*/
uint8_t
usb_pc_alloc_mem(struct usb_page_cache *pc, struct usb_page *pg,
			    usb_size_t size, usb_size_t align)
{
	void *ptr;
	DMA_ADDR_T dma_handle;

	/* allocate zeroed memory */
	if (align < USB_CACHE_ALIGN_SIZE) {
		ptr = LOS_DmaMemAlloc(&dma_handle, size, USB_CACHE_ALIGN_SIZE, DMA_NOCACHE);
	} else {
		ptr = LOS_DmaMemAlloc(&dma_handle, size, align, DMA_NOCACHE);
	}
	if (ptr == NULL)
		goto error;

	(void)memset_s(ptr, size, 0, size);
	/* setup page cache */
	pc->buffer = (uint8_t *)ptr;
	pc->page_start = pg;
	pc->page_offset_buf = 0;
	pc->page_offset_end = size;
	pc->map = NULL;
	pc->tag = (bus_dma_tag_t)ptr;
	pc->ismultiseg = (align == 1);

	/* compute physical address */
	usb_pc_common_mem_cb(pc, (void *)(UINTPTR)dma_handle, size);

	usb_pc_cpu_flush(pc);
	return (0);

error:
	/* reset most of the page cache */
	pc->buffer = NULL;
	pc->page_start = NULL;
	pc->page_offset_buf = 0;
	pc->page_offset_end = 0;
	pc->map = NULL;
	pc->tag = NULL;
	return (1);
}

/*------------------------------------------------------------------------*
 *	usb_pc_free_mem - free DMA memory
 *
 * This function is NULL safe.
 *------------------------------------------------------------------------*/
void
usb_pc_free_mem(struct usb_page_cache *pc)
{
	if ((pc != NULL) && (pc->buffer != NULL)) {
		LOS_DmaMemFree(pc->tag);
		pc->buffer = NULL;
	}
}

/*------------------------------------------------------------------------*
 *	usb_pc_load_mem - load virtual memory into DMA
 *
 * Return values:
 * 0: Success
 * Else: Error
 *------------------------------------------------------------------------*/
uint8_t
usb_pc_load_mem(struct usb_page_cache *pc, usb_size_t size, uint8_t data_sync)
{
	/* setup page cache */
	pc->page_offset_buf = 0;
	pc->page_offset_end = size;
	pc->ismultiseg = 1;

	mtx_assert(pc->tag_parent->mtx, MA_OWNED);

	if (size > 0) {
		/* compute physical address */
		usb_pc_common_mem_cb(pc, (void *)(UINTPTR)LOS_DmaVaddrToPaddr(pc->buffer), size);
	}
	if (data_sync == 0) {
		/*
		 * Call callback so that refcount is decremented
		 * properly:
		 */
		pc->tag_parent->dma_error = 0;
		(pc->tag_parent->func) (pc->tag_parent);
	}
	return (0);
}

/*------------------------------------------------------------------------*
 *	usb_pc_cpu_invalidate - invalidate CPU cache
 *------------------------------------------------------------------------*/
void
usb_pc_cpu_invalidate(struct usb_page_cache *pc)
{
	if (pc->page_offset_end == pc->page_offset_buf) {
		/* nothing has been loaded into this page cache! */
		return;
	}
	usb_dma_cache_invalid(pc->buffer, pc->page_offset_end - pc->page_offset_buf);
}

/*------------------------------------------------------------------------*
 *	usb_pc_cpu_flush - flush CPU cache
 *------------------------------------------------------------------------*/
void
usb_pc_cpu_flush(struct usb_page_cache *pc)
{
	if (pc->page_offset_end == pc->page_offset_buf) {
		/* nothing has been loaded into this page cache! */
		return;
	}
	usb_dma_cache_flush(pc->buffer, pc->page_offset_end - pc->page_offset_buf);
}

/*------------------------------------------------------------------------*
 *	usb_pc_dmamap_create - create a DMA map
 *
 * Returns:
 *	0: Success
 * Else: Failure
 *------------------------------------------------------------------------*/
uint8_t
usb_pc_dmamap_create(struct usb_page_cache *pc, usb_size_t size)
{
	return (0);	/* NOP, success */
}

/*------------------------------------------------------------------------*
 *	usb_pc_dmamap_destroy
 *
 * This function is NULL safe.
 *------------------------------------------------------------------------*/
void
usb_pc_dmamap_destroy(struct usb_page_cache *pc)
{
	/* NOP */
}

/*------------------------------------------------------------------------*
 *	usb_dma_tag_setup - initialise USB DMA tags
 *------------------------------------------------------------------------*/
void
usb_dma_tag_setup(struct usb_dma_parent_tag *udpt,
			    struct usb_dma_tag *udt, bus_dma_tag_t dmat,
			    struct mtx *mtx, usb_dma_callback_t *func,
			    uint8_t ndmabits, uint8_t nudt)
{
	(void)memset_s(udpt, sizeof(*udpt), 0, sizeof(*udpt));

	/* sanity checking */
	if ((nudt == 0) ||
		(ndmabits == 0) ||
		(mtx == NULL)) {
		/* something is corrupt */
		return;
	}
	/* initialise condition variable */
	cv_init(udpt->cv, "USB DMA CV");

	/* store some information */
	udpt->mtx = mtx;
	udpt->func = func;
	udpt->tag = dmat;
	udpt->utag_first = udt;
	udpt->utag_max = nudt;
	udpt->dma_bits = ndmabits;

	while (nudt--) {
		(void)memset_s(udt, sizeof(*udt), 0, sizeof(*udt));
		udt->tag_parent = udpt;
		udt++;
	}
}

/*------------------------------------------------------------------------*
 *	usb_bus_tag_unsetup - factored out code
 *------------------------------------------------------------------------*/
void
usb_dma_tag_unsetup(struct usb_dma_parent_tag *udpt)
{
	struct usb_dma_tag *udt;
	uint8_t nudt;

	udt = udpt->utag_first;
	nudt = udpt->utag_max;

	while (nudt--) {
		udt->align = 0;
		udt++;
	}

	if (udpt->utag_max) {
		/* destroy the condition variable */
		cv_destroy(udpt->cv);
	}
}

/*------------------------------------------------------------------------*
 *	usb_bdma_work_loop
 *
 * This function handles loading of virtual buffers into DMA and is
 * only called when "dma_refcount" is zero.
 *------------------------------------------------------------------------*/
void
usb_bdma_work_loop(struct usb_xfer_queue *pq)
{
	struct usb_xfer_root *info;
	struct usb_xfer *xfer;
	usb_frcount_t nframes;

	xfer = pq->curr;
	info = xfer->xroot;

	mtx_assert(info->xfer_mtx, MA_OWNED);

	if (xfer->error) {
		/* some error happened */
		USB_BUS_LOCK(info->bus);
		usbd_transfer_done(xfer, USB_ERR_NORMAL_COMPLETION);
		USB_BUS_UNLOCK(info->bus);
		return;
	}
	if (!xfer->flags_int.bdma_setup) {
		struct usb_page *pg;
		usb_frlength_t frlength_0;
		uint8_t isread;

		xfer->flags_int.bdma_setup = 1;

		/* reset BUS-DMA load state */

		info->dma_error = 0;

		if (xfer->flags_int.isochronous_xfr) {
			/* only one frame buffer */
			nframes = 1;
			frlength_0 = xfer->sumlen;
		} else {
			/* can be multiple frame buffers */
			nframes = xfer->nframes;
			frlength_0 = xfer->frlengths[0];
		}

		/*
		 * Set DMA direction first. This is needed to
		 * select the correct cache invalidate and cache
		 * flush operations.
		 */
		isread = USB_GET_DATA_ISREAD(xfer);
		pg = xfer->dma_page_ptr;

		if (xfer->flags_int.control_xfr &&
		    xfer->flags_int.control_hdr) {
			/* special case */
			if (xfer->flags_int.usb_mode == USB_MODE_DEVICE) {
				/* The device controller writes to memory */
				xfer->frbuffers[0].isread = 1;
			} else {
				/* The host controller reads from memory */
				xfer->frbuffers[0].isread = 0;
			}
		} else {
			/* default case */
			xfer->frbuffers[0].isread = isread;
		}

		/*
		 * Setup the "page_start" pointer which points to an array of
		 * USB pages where information about the physical address of a
		 * page will be stored. Also initialise the "isread" field of
		 * the USB page caches.
		 */
		xfer->frbuffers[0].page_start = pg;

		info->dma_nframes = nframes;
		info->dma_currframe = 0;
		info->dma_frlength_0 = frlength_0;

		pg += (frlength_0 / USB_PAGE_SIZE);
		pg += 2;

		while (--nframes > 0) {
			xfer->frbuffers[nframes].isread = isread;
			xfer->frbuffers[nframes].page_start = pg;

			pg += (xfer->frlengths[nframes] / USB_PAGE_SIZE);
			pg += 2;
		}

	}
	if (info->dma_error) {
		USB_BUS_LOCK(info->bus);
		usbd_transfer_done(xfer, USB_ERR_DMA_LOAD_FAILED);
		USB_BUS_UNLOCK(info->bus);
		return;
	}
	if (info->dma_currframe != info->dma_nframes) {

		if (info->dma_currframe == 0) {
			/* special case */
			(void)usb_pc_load_mem(xfer->frbuffers,
			    info->dma_frlength_0, 0);
		} else {
			/* default case */
			nframes = info->dma_currframe;
			(void)usb_pc_load_mem(xfer->frbuffers + nframes,
			    xfer->frlengths[nframes], 0);
		}

		/* advance frame index */
		info->dma_currframe++;

		return;
	}
	/* go ahead */
	usb_bdma_pre_sync(xfer);

	/* start loading next USB transfer, if any */
	usb_command_wrapper(pq, NULL);

	/* finally start the hardware */
	usbd_pipe_enter(xfer);
}

/*------------------------------------------------------------------------*
 *	usb_bdma_done_event
 *
 * This function is called when the BUS-DMA has loaded virtual memory
 * into DMA, if any.
 *------------------------------------------------------------------------*/
void
usb_bdma_done_event(struct usb_dma_parent_tag *udpt)
{
	struct usb_xfer_root *info;

	info = USB_DMATAG_TO_XROOT(udpt);

	mtx_assert(info->xfer_mtx, MA_OWNED);

	/* copy error */
	info->dma_error = udpt->dma_error;

	/* enter workloop again */
	usb_command_wrapper(&info->dma_q,
	    info->dma_q.curr);
}

static usb_frcount_t
usb_bdma_frame_num(struct usb_xfer *xfer)
{
	if (xfer->flags_int.isochronous_xfr) {
		/* only one frame buffer */
		return (1);
	} else {
		/* can be multiple frame buffers */
		return (xfer->nframes);
	}
}

/*------------------------------------------------------------------------*
 *	usb_bdma_pre_sync
 *
 * This function handles DMA synchronisation that must be done before
 * an USB transfer is started.
 *------------------------------------------------------------------------*/
void
usb_bdma_pre_sync(struct usb_xfer *xfer)
{
	struct usb_page_cache *pc;
	usb_frcount_t nframes;

	nframes = usb_bdma_frame_num(xfer);
	pc = xfer->frbuffers;

	while (nframes--) {

		if (pc->isread) {
			usb_pc_cpu_invalidate(pc);
		} else {
			usb_pc_cpu_flush(pc);
		}
		pc++;
	}
}

/*------------------------------------------------------------------------*
 *	usb_bdma_post_sync
 *
 * This function handles DMA synchronisation that must be done after
 * an USB transfer is complete.
 *------------------------------------------------------------------------*/
void
usb_bdma_post_sync(struct usb_xfer *xfer)
{
	struct usb_page_cache *pc;
	usb_frcount_t nframes;

	nframes = usb_bdma_frame_num(xfer);
	pc = xfer->frbuffers;

	while (nframes--) {
		if (pc->isread) {
			usb_pc_cpu_invalidate(pc);
		}
		pc++;
	}
}
#endif
