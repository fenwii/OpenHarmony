/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Description: Control hieth register
 */


#define HIETH_SFV300

#include "hieth.h"
#include "ctrl.h"

static inline u32 _hieth_irq_enable(struct hieth_netdev_local *ld, u32 irqs)
{
	u32 old = hieth_readl(ld, GLB_RW_IRQ_ENA);

	hieth_writel(ld, old | irqs, GLB_RW_IRQ_ENA);

	return old;
}

static inline u32 _hieth_irq_disable(struct hieth_netdev_local *ld, u32 irqs)
{
	u32 old = hieth_readl(ld, GLB_RW_IRQ_ENA);

	hieth_writel(ld, old & (~irqs), GLB_RW_IRQ_ENA);

	return old;
}

static inline u32 _hieth_read_irqstatus(struct hieth_netdev_local *ld)
{
	u32 status;

	status = hieth_readl(ld, GLB_RO_IRQ_STAT);

	return status;
}

static inline int _test_xmit_queue_ready(struct hieth_netdev_local *ld)
{
	return hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT),
							BITS_XMITQ_RDY);
}

static inline int _test_recv_queue_ready(struct hieth_netdev_local *ld)
{
	return hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT),
							BITS_RECVQ_RDY);
}

u32 hieth_irq_enable(struct hieth_netdev_local *ld, u32 irqs)
{
	u32 old;

	local_lock(ld);
	old = _hieth_irq_enable(ld, irqs);
	local_unlock(ld);

	return old;
}

u32 hieth_irq_disable(struct hieth_netdev_local *ld, u32 irqs)
{
	u32 old;

	local_lock(ld);
	old = _hieth_irq_disable(ld, irqs);
	local_unlock(ld);

	return old;
}

u32 hieth_read_irqstatus(struct hieth_netdev_local *ld)
{
	u32 status;

	local_lock(ld);
	status = _hieth_read_irqstatus(ld);
	local_unlock(ld);

	return status;
}

u32 hieth_read_raw_irqstatus(struct hieth_netdev_local *ld)
{
	u32 status;

	local_lock(ld);
	status = hieth_readl(ld, GLB_RO_IRQ_STAT);
	local_unlock(ld);

	return status;
}

u32 hieth_clear_irqstatus(struct hieth_netdev_local *ld, u32 irqs)
{
	u32 status;

	local_lock(ld);
	hieth_writel(ld, irqs, GLB_RW_IRQ_RAW);
	status = _hieth_read_irqstatus(ld);
	local_unlock(ld);

	return status;
}

u32 hieth_set_endian_mode(struct hieth_netdev_local *ld, u32 mode)
{
	u32 old;

	local_lock(ld);
	old = hieth_readl_bits(ld, GLB_ENDIAN_MOD, BITS_ENDIAN);
	hieth_writel_bits(ld, mode, GLB_ENDIAN_MOD, BITS_ENDIAN);
	local_unlock(ld);

	return old;
}

void hw_xmitq_setfd(struct hieth_netdev_local *ld, struct hieth_frame_desc fd)
{
	hieth_writel(ld, fd.frm_addr, ud_reg_name(GLB_EQ_ADDR));
	hieth_writel_bits(ld, fd.frm_len, ud_reg_name(GLB_EQFRM_LEN), BITS_TXINQ_LEN);
}

u32 hieth_readl(struct hieth_netdev_local *ld, u32 ofs)
{
	u32 reg = _readl((uintptr_t)(ld->iobase_phys + ofs));
	hieth_trace(HIETH_TRACE_ETH, "_readl(0x%08X) = 0x%08X",
		(u32)(ld->iobase_phys + ofs), reg);
	return reg;
}

void hieth_writel(struct hieth_netdev_local *ld, u32 v, u32 ofs)
{
	_writel(v, (uintptr_t)(ld->iobase_phys + ofs));
	hieth_trace(HIETH_TRACE_ETH, "_writel(0x%08X) = 0x%08X",
		(u32)(ld->iobase_phys + ofs), v);
}


u32 hieth_readl_bits(struct hieth_netdev_local *ld, u32 ofs, u32 bits_desc)
{
	u32 _bits_desc = bits_desc;
	u32 _shift = _bits_desc >> 16; /* shift 16 bit */
	u32 _mask = ((1 << (_bits_desc & 0x1F)) - 1) << _shift;
	u32 reg = (hieth_readl(ld, ofs) & _mask) >> _shift;
	return reg;
}

void hieth_writel_bits(struct hieth_netdev_local *ld, u32 v, u32 ofs, u32 bits_desc)
{
	u32 _bits_desc = bits_desc;
	u32 _shift = _bits_desc >> 16; /* shift 16 bit */
	u32 _reg = hieth_readl(ld, ofs);
	u32 _mask = ((1 << (_bits_desc & 0x1F)) - 1) << _shift;
	hieth_writel(ld, (_reg & (~_mask)) | ((v << _shift) & _mask), ofs);
}

void hieth_trace(int level, const char *fmt, ...)
{
	if (level >= HIETH_TRACE_LEVEL) {
		va_list args;
		va_start(args, fmt);
		printf("hieth_trace:");
		printf(fmt, args);
		printf("\n");
		va_end(args);
	}
}

void hieth_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("hieth:");
	printf(fmt, args);
	printf("\n");
	va_end(args);
}

void hieth_assert(bool cond)
{
	if (!cond)
		printf("Assert:hieth:%s:%d\n", __FILE__, __LINE__);
}
