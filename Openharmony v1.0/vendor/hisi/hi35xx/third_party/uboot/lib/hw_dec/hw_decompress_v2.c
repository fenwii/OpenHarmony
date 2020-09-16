/*
 * hw_decompress_v2.c
 *
 * Files related to software decompression and hardware decompression
 *
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
 */

#include <asm/io.h>
#ifndef error
#define error(fmt, args...) do { \
	printf("ERROR: " pr_fmt(fmt) "\nat %s:%d/%s()\n", \
		##args, __FILE__, __LINE__, __func__);	\
} while (0)
#endif

#include "hw_decompress_v2.h"

#if (defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100)
#include "hw_decompress_hi3559av100.c"
#endif


#if (defined CONFIG_TARGET_HI3569V100) || (defined CONFIG_HI3569V100)
#include "hw_decompress_hi3569v100.c"
#endif

#if (defined CONFIG_TARGET_HI3556AV100)
#include "hw_decompress_hi3556av100.c"
#endif

#if (defined CONFIG_TARGET_HI3519AV100)
#include "hw_decompress_hi3519av100.c"
#endif

unsigned int hw_dec_type = 0;
static unsigned int hw_dec_sop;
static unsigned int hw_dec_eop;
static unsigned int hw_dec_cur_blk;
static unsigned int hw_blk_total_num;


void hw_dec_sop_eop_first_set(int block_num)
{
	if (block_num == 1) {
		hw_dec_sop = 1;
		hw_dec_eop = 1;
	} else {
		hw_dec_sop = 1;
		hw_dec_eop = 0;
	}

	hw_dec_cur_blk = 0;
	hw_blk_total_num = block_num;
}

static inline void hw_dec_work_en_set(int work_en_flg)
{
	/* Enable the emar */
	writel(work_en_flg, HW_DEC_REG_BASE_ADDR + EAMR_WORK_EN_REG_OFST);
}

static inline void hw_dec_rtn_baddr_h32_set(unsigned int addr)
{
	writel(addr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_RTN_BADDR_H32);
}

static inline void hw_dec_rtn_baddr_l32_set(unsigned int addr)
{
	writel(addr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_RTN_BADDR_L32);
}

static inline void hw_dec_dprs_data_baddr_h32_set(unsigned int addr)
{
	writel(addr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_INFO_BADDR_H32);
}

static inline void hw_dec_dprs_data_baddr_l32_set(unsigned int addr)
{
	writel(addr, HW_DEC_REG_BASE_ADDR + DPRS_DATA_INFO_BADDR_L32);
}

static inline void hw_dec_data_rtn_len_set(unsigned int len)
{
	writel(len, HW_DEC_REG_BASE_ADDR + DPRS_DATA_RTN_LEN);
}

static inline void hw_dec_dprs_data_len_set(unsigned int len)
{
	writel(len, HW_DEC_REG_BASE_ADDR + DPRS_DATA_INFO_LEN);
}

static inline void hw_dec_crc_check_en(unsigned int crc_en)
{
	writel(crc_en, HW_DEC_REG_BASE_ADDR + CRC_CHECK_EN);
}

static inline void hw_dec_data_crc32_set(unsigned int crc32)
{
	writel(crc32, HW_DEC_REG_BASE_ADDR + DPRS_DATA_CRC32);
}

static inline unsigned int hw_dec_buf_status_get(void)
{
	return readl(HW_DEC_REG_BASE_ADDR + BUF_INFO);
}

static inline unsigned int hw_dec_dprs_rtn_status_get(void)
{
	return readl(HW_DEC_REG_BASE_ADDR + DPRS_RTN_INFO);
}

static inline void hw_dec_buf_status_clr(void)
{
	writel(0x1, HW_DEC_REG_BASE_ADDR + BUF_INFO_CLR);
}

static inline void hw_dec_dprs_rtn_status_clr(void)
{
	writel(0x1, HW_DEC_REG_BASE_ADDR + RLT_INFO_CLR);
}

static void hw_dec_intr_en_set(int blk_intr_en, int task_intr_en)
{
	u_intr_en intr_en;
	intr_en.bits.task_intrpt_en = task_intr_en;
	intr_en.bits.block_intrpt_en = blk_intr_en;
	writel(intr_en.u32, HW_DEC_REG_BASE_ADDR + INT_EN_REG_ADDR);
}

static inline unsigned int hw_dec_intr_status_get(void)
{
	return readl(HW_DEC_REG_BASE_ADDR + INT_STATUS_REG_ADDR);
}

static void hw_dec_block_intr_status_clr(void)
{
	u_intr_clr intr_clr;

	intr_clr.u32 = readl(HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
	intr_clr.bits.block_intrpt_clr = 0x1;
	writel(intr_clr.u32, HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
}

static void hw_dec_task_intr_status_clr(void)
{
	u_intr_clr intr_clr;

	intr_clr.u32 = readl(HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
	intr_clr.bits.task_intrpt_clr = 0x1;
	writel(intr_clr.u32, HW_DEC_REG_BASE_ADDR + INT_CLEAR_REG_ADDR);
}

int hw_dec_intr_proc(int irq, void *para)
{
	u_buf_status buf_status;
	u_intr_status intr_status;
	u_dprs_rtn_status dprs_status;
	int ret = 0;

	intr_status.u32 = hw_dec_intr_status_get();
	if (intr_status.bits.block_intrpt) {
		buf_status.u32 = hw_dec_buf_status_get();
		if (buf_status.bits.aval_flg)
			hw_dec_buf_status_clr();

		hw_dec_block_intr_status_clr();
	}

	if (!intr_status.bits.task_intrpt)
		return -1;

	dprs_status.u32 = hw_dec_dprs_rtn_status_get();
	if (dprs_status.bits.aval_flg) {
		if (dprs_status.bits.err_info) {
			if (dprs_status.bits.err_info == 0x81)
				error("\n[hw_dec_intr_proc] error = 0x81\n");
			else if (dprs_status.bits.err_info == 0x85)
				error("\n[hw_dec_intr_proc] error = 0x85\n");
			else if (dprs_status.bits.err_info == 0x87)
				error("\n[hw_dec_intr_proc] error = 0x87\n");
			else if (dprs_status.bits.err_info == 0x89)
				error("\n[hw_dec_intr_proc] error = 0x89\n");
			else if (dprs_status.bits.err_info == 0x8a)
				error("\n[hw_dec_intr_proc] error = 0x8a\n");
			else if (dprs_status.bits.err_info == 0x8b)
				error("\n[hw_dec_intr_proc] error = 0x8b\n");
			else
				error("\n[hw_dec_intr_proc] other error !!\n");
			ret = -2; /* -2:failed */
		}

		hw_dec_dprs_rtn_status_clr();
	}

	hw_dec_task_intr_status_clr();
	return ret;
}

void hw_dec_start(unsigned int src_baddr_h32,
			unsigned int src_baddr_l32,
			unsigned int dst_baddr_h32,
			unsigned int dst_baddr_l32,
			unsigned int src_len,
			unsigned int dst_len,
			unsigned int crc_en,
			unsigned int crc32,
			unsigned int dec_type)
{
	unsigned int val;

	if (hw_dec_sop) {
		if (!dec_type) {
			/* set the parameters of output buffer */
			hw_dec_rtn_baddr_h32_set(dst_baddr_h32);
			hw_dec_rtn_baddr_l32_set(dst_baddr_l32);
			hw_dec_data_rtn_len_set(dst_len);
		} else {
			/* set the parameter of output buffer */
			hw_dec_dprs_data_baddr_h32_set(dst_baddr_h32);
			hw_dec_dprs_data_baddr_l32_set(dst_baddr_l32);
			hw_dec_dprs_data_len_set(page_nr(dst_len) * 4); /* 4:Align */
		}
	}

	/* set the parameter of input buffer */
	writel(src_baddr_l32, HW_DEC_REG_BASE_ADDR + DPRS_DATA_SRC_BADDR_L32);

	val = src_len |
		(hw_dec_sop << 28) | (hw_dec_eop << 29) | (!dec_type << 31); /* 28,29,31 Move Left bit */
	writel(val, HW_DEC_REG_BASE_ADDR + DPRS_DATA_SRC_LEN);

	hw_dec_crc_check_en(crc_en);
}

static inline void delay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 100: Cycle */
		__asm__ __volatile__("nop");
}

int hw_dec_wait_finish(void)
{
	int ret;
	int times = 0;

	do {
		ret = hw_dec_intr_proc(HW_DEC_INTR, NULL);
		times++;
		if (times > 2000000) { /* 2000000 ms */
			error("\nhardware decompress overtime!\n");
			break;
		}
		delay(1);
	} while (-1 == ret);

	return ret;
}

int hw_dec_decompress(unsigned char *dst_h32, unsigned char *dst_l32,
				int *dstlen, unsigned char *src_h32,
				unsigned char *src_l32, int srclen, void *unused)
{
	int ret;

	if (srclen > GZIP_MAX_LEN) {
		error("\nThe max lenth GZIP decompress supported is (16MB - 1) !!!!\n");
		return -1;
	}

	hw_dec_sop_eop_first_set(1);

	hw_dec_start((unsigned int)(uintptr_t)src_h32, (unsigned int)(uintptr_t)src_l32,
				 (unsigned int)(uintptr_t)dst_h32, (unsigned int)(uintptr_t)dst_l32,
				 srclen, *dstlen, 0, 0, hw_dec_type);

	ret = hw_dec_wait_finish();

	*dstlen = readl(HW_DEC_REG_BASE_ADDR + DPRS_RTN_LEN);

	if (ret)
		return -1;

	return 0;
}

void hw_dec_init(void)
{
	/* enable decompress clock */
	enable_decompress_clock();
	/* Init the emar interface */
	/* bit[31:28] : Emar Write Outstanding
	   bit[27:24] : Emar Read Outstanding
	   bit[23: 0] : reserve */
	writel(0, HW_DEC_REG_BASE_ADDR + EAMR_OSD_REG_OFST);
	writel((0x3 << 24), HW_DEC_REG_BASE_ADDR + EAMR_OSD_REG_OFST); /* 0x3 Move Left 24bit */
	writel((0x3 << 28), HW_DEC_REG_BASE_ADDR + EAMR_OSD_REG_OFST); /* 0x3 Move Left 28bit */

	/* Enable interrupt */
	hw_dec_intr_en_set(0x1, 0x1);

	/* Enable emar */
	hw_dec_work_en_set(0x1);
}

void hw_dec_uinit(void)
{
	hw_dec_work_en_set(0x0);
	hw_dec_intr_en_set(0x0, 0x0);

	/* disable decompress clock */
	disable_decompress_clock();
}
