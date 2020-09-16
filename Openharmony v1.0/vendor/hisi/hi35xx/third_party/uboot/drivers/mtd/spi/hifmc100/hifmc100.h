/*
 * hifmc100.h
 *
 * The Flash Memory Controller v100 Device Driver for hisilicon
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

#ifndef __HIFMC100_H__
#define __HIFMC100_H__

#include <spi_flash.h>
#include <hifmc_common.h>
#include "../../hifmc_spi_ids.h"
#include <cpu_func.h>

/*****************************************************************************/
/* These macroes are for debug only, reg read is slower then dma read,
    so we don't define it */
#undef HIFMC100_SPI_NOR_SUPPORT_REG_READ
#undef HIFMC100_SPI_NOR_SUPPORT_REG_WRITE

/*****************************************************************************/
#define HIFMC100_DMA_WR_MAX_SIZE		4096
#define HIFMC100_DMA_WR_MASK			(HIFMC100_DMA_WR_MAX_SIZE - 1)
#define HIFMC100_DMA_RD_MAX_SIZE		(_2M)
#define HIFMC100_DMA_RD_MASK			(HIFMC100_DMA_RD_MAX_SIZE - 1)
#define HIFMC100_REG_RD_MAX_SIZE		(_16K)
#define HIFMC100_REG_RD_MASK			(HIFMC100_REG_RD_MAX_SIZE - 1)

/*****************************************************************************/
#define SPI_NOR_CR_SHIFT	8   /* Config Register shift(bit) */

#define SPI_NOR_CR_4BYTE_SHIFT  5
#define SPI_NOR_CR_4BYTE_MASK	   (1 << SPI_NOR_CR_4BYTE_SHIFT)
#define spi_nor_get_4byte_by_cr(cr) (((cr) & SPI_NOR_CR_4BYTE_MASK) \
						>> SPI_NOR_CR_4BYTE_SHIFT)

#define SPI_NOR_CR_QE_SHIFT	 1
#define SPI_NOR_CR_QE_MASK	  (1 << SPI_NOR_CR_QE_SHIFT)
#define spi_nor_get_qe_by_cr(cr)	(((cr) & SPI_NOR_CR_QE_MASK) \
						>> SPI_NOR_CR_QE_SHIFT)

#define SPI_NOR_CR_RST_HOLD_SHIFT   7
#define SPI_NOR_CR_RST_HOLD_MASK	(1 << SPI_NOR_CR_RST_HOLD_SHIFT)
#define SPI_NOR_CR_HOLD_MASK		(~(1 << SPI_NOR_CR_RST_HOLD_SHIFT))
#define spi_nor_get_rst_hold_by_cr(cr)  (((cr) & SPI_NOR_CR_RST_HOLD_MASK) \
						>> SPI_NOR_CR_RST_HOLD_SHIFT)
#define spi_nor_set_rst_by_cr(cr)   ((cr) | SPI_NOR_CR_RST_HOLD_MASK)
#define spi_nor_set_hold_by_cr(cr)  ((cr) & SPI_NOR_CR_HOLD_MASK)

#ifdef CONFIG_SPI_BLOCK_PROTECT
#define DEBUG_SPI_NOR_BP	0

#define SPI_NOR_SR_SRWD_SHIFT   7
#define SPI_NOR_SR_SRWD_MASK	(1 << SPI_NOR_SR_SRWD_SHIFT)

#define SPI_NOR_SR_BP0_SHIFT	2
#define SPI_NOR_SR_BP_WIDTH_4   0xf
#define SPI_NOR_SR_BP_MASK_4	(SPI_NOR_SR_BP_WIDTH_4 << SPI_NOR_SR_BP0_SHIFT)

#define SPI_NOR_SR_BP_WIDTH_3   0x7
#define SPI_NOR_SR_BP_MASK_3	(SPI_NOR_SR_BP_WIDTH_3 << SPI_NOR_SR_BP0_SHIFT)

#define SPI_NOR_SR_TB_SHIFT 3
#define SPI_NOR_SR_TB_MASK  (1 << SPI_NOR_SR_TB_SHIFT)

#define SPI_NOR_SR_TB_SHIFT_S   5
#define SPI_NOR_SR_TB_MASK_S	(1 << SPI_NOR_SR_TB_SHIFT_S)

#define spi_bp_bottom_rdcr_set_s(config)	((config) | \
					(0x01 << SPI_NOR_SR_TB_SHIFT_S))
#define spi_bp_bottom_rdcr_set(config)	  ((config) | \
					(0x01 << SPI_NOR_SR_TB_SHIFT))

#define spi_bp_bottom_rdsr_set_1(bp_num)	(0x1 << (2 + bp_num))
#define spi_bp_bottom_rdsr_set_0(bp_num)	(~(0x1 << (2 + bp_num)))

#define lock_level_max(bp_num)		  (((0x01) << bp_num) - 1)

#endif /* CONFIG_SPI_BLOCK_PROTECT */

#ifdef CONFIG_DTR_MODE_SUPPORT
#define DTR_DUMMY_CYCLES_6	  6
#define DTR_DUMMY_CYCLES_8	  8
#define DTR_DUMMY_CYCLES_10	 10
#define dtr_rdcr_dc_mask(_val)	  (_val)
#define DTR_RDSR_DC_SHIFT	   14
#define DTR_RDCR_DC_SHIFT	   6
#define dtr_rdcr_dc_bit_clr(_reg)   ((_reg) & (~(3 << DTR_RDSR_DC_SHIFT)))
#define DTR_MODE_REQUEST_SHIFT	  11

#define DTR_TRAINING_POINT_NUM		  12
#define DTR_TRAINING_POINT_MASK		 12
#define dtr_training_point_clr(_reg)	((_reg) & (~(0xf << 12)))
#define DTR_TRAINING_CMP_ADDR_SHIFT (2048 + 96)
#define DTR_TRAINING_CMP_ADDR_S	 (CONFIG_SYS_TEXT_BASE_ORI + \
					DTR_TRAINING_CMP_ADDR_SHIFT)
#define DTR_TRAINING_CMP_LEN		0x100
#define SFDP_BUF_LEN			0x33
#define SFDP_DTR_BIT_SHIFT	  3
#define SFDP_DTR_BYTE_SHIFT	 0x32
#define SFDP_DTR_BIT_MASK	   0x1
#define DEVICE_ID_SUPPORT_DTR_WINBOND 0x70
#endif /* CONFIG_DTR_MODE_SUPPORT */

/* MXIC Config Register's dummy cycle bits */
#define CR_DUMMY_CYCLE	  (0x03 << 6)
#define SPI_CMD_RDCR_MX		 0x15 /* MXIC Read Config Register */
#define DTR_MODE_REQUEST_SHIFT		   11
#define SPI_NOR_SR_WIP_MASK 			(1 << 0)
/*****************************************************************************/
struct hifmc_host {
	struct spi_flash spi_nor_flash[1];
	struct mtd_info_ex *spi_nor_info;
	struct hifmc_spi spi[CONFIG_SPI_NOR_MAX_CHIP_NUM];

	void *regbase;
	void *iobase;

	void (*set_system_clock)(struct spi_op *op, int clk_en);
	void (*set_host_addr_mode)(struct hifmc_host *host, int enable);

#ifdef CONFIG_SPI_BLOCK_PROTECT
	unsigned int start_addr;
	unsigned int end_addr;
	unsigned char cmp;
	unsigned int bp_num;
	/* the BT bit location, decide the data num count */
	unsigned int bt_loc;
	unsigned char level;
#endif
#ifdef CONFIG_DTR_MODE_SUPPORT
	unsigned int dtr_mode_en;
	unsigned int dtr_training_flag;
#endif
};

#ifdef CONFIG_SPI_BLOCK_PROTECT
unsigned short hifmc100_set_spi_lock_info(struct hifmc_host *host);
void hifmc100_get_bp_lock_level(struct hifmc_host *host);
void hifmc100_spi_lock(struct hifmc_host *host, unsigned char level);
void hifmc100_spi_flash_lock(unsigned char cmp, unsigned char level,
				unsigned char op);
unsigned short hifmc100_handle_bp_rdcr_info(struct hifmc_host *host,
				u_char cmd);
unsigned char hifmc100_bp_to_level(struct hifmc_host *host);
unsigned short hifmc100_handle_bp_rdsr_info(struct hifmc_host *host,
				u_char cmd);
#endif
unsigned char spi_general_get_flash_register(struct hifmc_spi *spi,
				u_char cmd);

#define spiflash_to_host(_spiflash) ((struct hifmc_host *)(_spiflash))
/*****************************************************************************/
#ifdef CONFIG_DTR_MODE_SUPPORT
void hifmc_dtr_mode_ctrl(struct hifmc_spi *spi, int dtr_en);
unsigned int spi_dtr_training(struct hifmc_host *host);
void spi_dtr_to_sdr_switch(struct hifmc_spi *spi);
int spi_dtr_dummy_training_set(struct hifmc_host *host, int dtr_en);
void hifmc_check_spi_dtr_support(struct hifmc_spi *spi, u_char *ids, int len);
unsigned int spi_mxic_check_spi_dtr_support(struct hifmc_spi *spi);
#endif
/*****************************************************************************/
void hifmc100_read_ids(struct hifmc_spi *, u_char, u_char *);
void hifmc100_op_reg(struct hifmc_spi *spi, unsigned char opcode,
				unsigned int len, unsigned char optype);
int hifmc_spi_nor_probe(struct mtd_info_ex *mtd, struct hifmc_spi *spi);
int hifmc100_spi_nor_init(struct hifmc_host *);
struct spi_flash *hifmc100_spi_nor_scan(struct hifmc_host *host);
/*****************************************************************************/

#endif /* End of __HIFMC100_H__ */

