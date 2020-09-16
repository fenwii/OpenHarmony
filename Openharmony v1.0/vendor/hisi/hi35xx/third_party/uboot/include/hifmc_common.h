/*
 * hifmc_common.h
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

#ifndef __HIFMC_COMMON_H__
#define __HIFMC_COMMON_H__

/*****************************************************************************/
#define _32B					32
#define _64B					64
#define _128B					128
#define _218B					218
#define _224B					224
#define _232B					232
#define _256B					256
#define _448B					448
#define _512B					512
#define _640B					640
#define _744B					744
#define _1K					1024
#define _1280B					1280
#define _2K					2048
#define _4K					4096
#define _8K					8192
#define _16K					16384
#define _32K					32768
#define _64K					0x10000UL
#define _128K					0x20000UL
#define _256K					0x40000UL
#define _512K					0x80000UL
#define _1M					0x100000UL
#define _2M					0x200000UL
#define _4M					0x400000UL
#define _8M					0x800000UL
#define _16M					0x1000000UL
#define _32M					0x2000000UL
#define _64M					0x4000000UL
#define _128M					0x8000000UL
#define _256M					0x10000000UL
#define _512M					0x20000000UL
#define _1G					0x40000000ULL
#define _2G					0x80000000ULL
#define _4G					0x100000000ULL
#define _8G					0x200000000ULL
#define _16G					0x400000000ULL
#define _64G					0x1000000000ULL

#define ECC_TYPE_0BIT				0x0
#define ECC_TYPE_8BIT				0x1
#define ECC_TYPE_16BIT				0x2
#define ECC_TYPE_24BIT				0x3
#define ECC_TYPE_28BIT				0x4
#define ECC_TYPE_40BIT				0x5
#define ECC_TYPE_64BIT				0x6

#define PAGE_SIZE_2KB				0x0
#define PAGE_SIZE_4KB				0x1
#define PAGE_SIZE_8KB				0x2
#define PAGE_SIZE_16KB				0x3

/* id len */
#define _2B					2
#define _3B					3
#define _4B					4
#define _5B					5
#define _6B					6
#define _7B					7
#define _8B					8
#define _9B					9
#define _10B					10
#define _11B					11
#define _12B					12

#ifdef CONFIG_HIFMC
/*****************************************************************************/
/* HIFMC REG */
/*****************************************************************************/
#define FMC_CFG					0x00
#define fmc_cfg_spi_nand_sel(_type)		(((_size) & 0x3) << 11)
#define fmc_cfg_spi_nor_addr_mode(_mode)	((_mode) << 10)
#define fmc_cfg_block_size(_size)		(((_size) & 0x3) << 8)
#define fmc_cfg_ecc_type(_type)			(((_type) & 0x7) << 5)
#define fmc_cfg_page_size(_size)		(((_size) & 0x3) << 3)
#define fmc_cfg_flash_sel(_type)		(((_type) & 0x3) << 1)
#define fmc_cfg_op_mode(_mode)			((_mode) & 0x1)

#define SPI_NAND_MFR_OTHER			0x0
#define SPI_NAND_MFR_WINBOND			0x1
#define SPI_NAND_MFR_ESMT			0x2
#define SPI_NAND_MFR_MICRON			0x3

#define SPI_NAND_SEL_SHIFT			11
#define SPI_NAND_SEL_MASK			(0x3 << SPI_NAND_SEL_SHIFT)

#define SPI_NOR_ADDR_MODE_3_BYTES		0x0
#define SPI_NOR_ADDR_MODE_4_BYTES		0x1

#define SPI_NOR_ADDR_MODE_SHIFT			10
#define SPI_NOR_ADDR_MODE_MASK			(0x1 << SPI_NOR_ADDR_MODE_SHIFT)

#define BLOCK_SIZE_64_PAGE			0x0
#define BLOCK_SIZE_128_PAGE			0x1
#define BLOCK_SIZE_256_PAGE			0x2
#define BLOCK_SIZE_512_PAGE			0x3

#define _64_PAGES				64
#define _128_PAGES				128
#define _256_PAGES				256
#define _512_PAGES				512

#define EB_NORMAL				28
#define EB_2K_16_BIT				4
#define EB_4K_16_BIT				12

#define BLOCK_SIZE_MASK				(0x3 << 8)

#define ECC_TYPE_SHIFT				5
#define ECC_TYPE_MASK				(0x7 << ECC_TYPE_SHIFT)

#define PAGE_SIZE_SHIFT				3
#define PAGE_SIZE_MASK				(0x3 << PAGE_SIZE_SHIFT)

#define FLASH_TYPE_SPI_NOR			0x0
#define FLASH_TYPE_SPI_NAND			0x1
#define FLASH_TYPE_NAND				0x2
#define FLASH_TYPE_DEFAULT			0x3

#define FLASH_SEL_SHIFT				1
#define FLASH_SEL_MASK				(0x3 << FLASH_SEL_SHIFT)

#define OP_MODE_BOOT				0x0
#define OP_MODE_NORMAL				0x1

#define OP_MODE_MASK				0x1

/*****************************************************************************/
#define FMC_GLOBAL_CFG				0x04
#define FMC_GLOBAL_CFG_WP_ENABLE		(1 << 6)
#define FMC_GLOBAL_CFG_RANDOMIZER_EN		(1 << 2)

/*****************************************************************************/
#define FMC_SPI_TIMING_CFG			0x08
#define timing_cfg_tcsh(_n)			(((_n) & 0xf) << 8)
#define timing_cfg_tcss(_n)			(((_n) & 0xf) << 4)
#define timing_cfg_tshsl(_n)			((_n) & 0xf)

#define CS_HOLD_TIME				0x6
#define CS_SETUP_TIME				0x6
#define CS_DESELECT_TIME			0xf

/*****************************************************************************/
#define FMC_PND_PWIDTH_CFG			0x0c
#define pwidth_cfg_rw_hcnt(_n)			(((_n) & 0xf) << 8)
#define pwidth_cfg_r_lcnt(_n)			(((_n) & 0xf) << 4)
#define pwidth_cfg_w_lcnt(_n)			((_n) & 0xf)

#ifdef CONFIG_NAND_EDO_MODE
#define RW_H_WIDTH				0x3
#define R_L_WIDTH				0x2
#define W_L_WIDTH				0x2
#define NAND_EDO_MODE_SHIFT		9
#define NAND_EDO_MODE_MASK		(1<<NAND_EDO_MODE_SHIFT)
#define set_nand_edo_mode_en(reg)	((reg) | NAND_EDO_MODE_MASK)
#else
#define RW_H_WIDTH				0xa
#define R_L_WIDTH				0xa
#define W_L_WIDTH				0xa
#endif
/*****************************************************************************/
#define FMC_INT					0x18
#define FMC_INT_AHB_OP				(1 << 7)
#define FMC_INT_WR_LOCK				(1 << 6)
#define FMC_INT_DMA_ERR				(1 << 5)
#define FMC_INT_ERR_ALARM			(1 << 4)
#define FMC_INT_ERR_INVALID			(1 << 3)
#define FMC_INT_ERR_VALID			(1 << 2)
#define FMC_INT_OP_FAIL				(1 << 1)
#define FMC_INT_OP_DONE				(1 << 0)

/*****************************************************************************/
#define FMC_INT_EN				0x1c
#define FMC_INT_EN_AHB_OP			(1 << 7)
#define FMC_INT_EN_WR_LOCK			(1 << 6)
#define FMC_INT_EN_DMA_ERR			(1 << 5)
#define FMC_INT_EN_ERR_ALARM			(1 << 4)
#define FMC_INT_EN_ERR_INVALID			(1 << 3)
#define FMC_INT_EN_ERR_VALID			(1 << 2)
#define FMC_INT_EN_OP_FAIL			(1 << 1)
#define FMC_INT_EN_OP_DONE			(1 << 0)

/*****************************************************************************/
#define FMC_INT_CLR				0x20
#define FMC_INT_CLR_AHB_OP			(1 << 7)
#define FMC_INT_CLR_WR_LOCK			(1 << 6)
#define FMC_INT_CLR_DMA_ERR			(1 << 5)
#define FMC_INT_CLR_ERR_ALARM			(1 << 4)
#define FMC_INT_CLR_ERR_INVALID			(1 << 3)
#define FMC_INT_CLR_ERR_VALID			(1 << 2)
#define FMC_INT_CLR_OP_FAIL			(1 << 1)
#define FMC_INT_CLR_OP_DONE			(1 << 0)

#define FMC_INT_CLR_ALL				0xff

/*****************************************************************************/
#define FMC_CMD					0x24
#define fmc_cmd_cmd2(_cmd)			(((_cmd) & 0xff) << 8)
#define fmc_cmd_cmd1(_cmd)			((_cmd) & 0xff)

/*****************************************************************************/
#define FMC_ADDRH				0x28
#define fmc_addrh_set(_addr)			((_addr) & 0xff)

/*****************************************************************************/
#define FMC_ADDRL				0x2c
#define fmc_addrl_block_h_mask(_page)		(((_page) & 0xffff) << 16)
#define fmc_addrl_block_l_mask(_page)		((_page) & 0xffc0)

#define READ_ID_ADDR				0x00
#define PROTECT_ADDR				0xa0
#define FEATURE_ADDR				0xb0
#define STATUS_ADDR				0xc0

/*****************************************************************************/
#define FMC_OP_CFG				0x30
#define op_cfg_fm_cs(_cs)			((_cs) << 11)
#define op_cfg_force_cs_en(_en)			((_en) << 10)
#define op_cfg_mem_if_type(_type)		(((_type) & 0x7) << 7)
#define op_cfg_addr_num(_addr)			(((_addr) & 0x7) << 4)
#define op_cfg_dummy_num(_dummy)		((_dummy) & 0xf)
#define OP_CFG_OEN_EN				(0x1 << 13)

#define IF_TYPE_STD				0x0
#define IF_TYPE_DUAL				0x1
#define IF_TYPE_DIO				0x2
#define IF_TYPE_QUAD				0x3
#define IF_TYPE_QIO				0x4
#define IF_TYPE_DTR				0x4

#define IF_TYPE_SHIFT				7
#define IF_TYPE_MASK				(0x7 << IF_TYPE_SHIFT)

#define READ_ID_ADDR_NUM			1
#define FEATURES_OP_ADDR_NUM			1
#define STD_OP_ADDR_NUM				3

/*****************************************************************************/
#define FMC_SPI_OP_ADDR				0x34

/*****************************************************************************/
#define FMC_DATA_NUM				0x38
#define fmc_data_num_cnt(_n)			((_n) & 0x3fff)

#define SPI_NOR_SR_LEN				1 /* Status Register length */
#define SPI_NOR_CR_LEN				1 /* Config Register length */
#define FEATURES_DATA_LEN			1
#define READ_OOB_BB_LEN				1
#define MAX_SPI_NOR_ID_LEN			8
#define MAX_NAND_ID_LEN				8
#define MAX_SPI_NAND_ID_LEN			3

#define PROTECT_BRWD_MASK			(1 << 7)
#define PROTECT_BP3_MASK			(1 << 6)
#define PROTECT_BP2_MASK			(1 << 5)
#define PROTECT_BP1_MASK			(1 << 4)
#define PROTECT_BP0_MASK			(1 << 3)

#define any_bp_enable(_val) ((PROTECT_BP3_MASK & _val) || \
		(PROTECT_BP2_MASK & _val) || (PROTECT_BP1_MASK & _val) || \
		(PROTECT_BP0_MASK & _val))

#define ALL_BP_MASK				(PROTECT_BP3_MASK \
						| PROTECT_BP2_MASK \
						| PROTECT_BP1_MASK \
						| PROTECT_BP0_MASK)

#define FEATURE_ECC_ENABLE			(1 << 4)
#define FEATURE_QE_ENABLE			(1 << 0)

/* read nand id or nand status, return from nand data length */
#define MAX_NANDINFO_LEN			0x10

/*****************************************************************************/
#define FMC_OP					0x3c
#define fmc_op_dummy_en(_en)			((_en) << 8)
#define fmc_op_cmd1_en(_en)			((_en) << 7)
#define fmc_op_addr_en(_en)			((_en) << 6)
#define fmc_op_write_data_en(_en)		((_en) << 5)
#define fmc_op_cmd2_en(_en)			((_en) << 4)
#define fmc_op_wait_ready_en(_en)		((_en) << 3)
#define fmc_op_read_data_en(_en)		((_en) << 2)
#define fmc_op_read_status_en(_en)		((_en) << 1)
#define FMC_OP_REG_OP_START			1

/*****************************************************************************/
#define FMC_DMA_LEN				0x40
#define fmc_dma_len_set(_len)			((_len) & 0x0fffffff)
#define byte_to_mb(_x)				((_x) >> 20)
/*****************************************************************************/
#define FMC_DMA_AHB_CTRL			0x48
#define FMC_DMA_AHB_CTRL_DMA_PP_EN		(1 << 3)
#define FMC_DMA_AHB_CTRL_BURST16_EN		(1 << 2)
#define FMC_DMA_AHB_CTRL_BURST8_EN		(1 << 1)
#define FMC_DMA_AHB_CTRL_BURST4_EN		1

#define ALL_BURST_ENABLE			(FMC_DMA_AHB_CTRL_BURST16_EN \
						| FMC_DMA_AHB_CTRL_BURST8_EN \
						| FMC_DMA_AHB_CTRL_BURST4_EN)

#define FMC_DMA_ADDR_OFFSET			4096

/*****************************************************************************/
#define FMC_DMA_SADDR_D0			0x4c

/*****************************************************************************/
#define FMC_DMA_SADDR_D1			0x50

/*****************************************************************************/
#define FMC_DMA_SADDR_D2			0x54

/*****************************************************************************/
#define FMC_DMA_SADDR_D3			0x58

/*****************************************************************************/
#define FMC_DMA_SADDR_OOB			0x5c

/*****************************************************************************/
#define FMC_DMA_SADDRH_D0			0x200
#define FMC_DMA_SADDRH_SHIFT		0x3LL
#define FMC_DMA_SADDRH_MASK			(FMC_DMA_SADDRH_SHIFT << 32)

/*****************************************************************************/
#define FMC_DMA_SADDRH_OOB			0x210

/*****************************************************************************/
#define FMC_DMA_BLK_SADDR			0x60
#define fmc_dma_blk_saddr_set(_addr)		((_addr) & 0xffffff)

/*****************************************************************************/
#define FMC_DMA_BLK_LEN				0x64
#define fmc_dma_blk_len_set(_len)		((_len) & 0xffff)

/*****************************************************************************/
#define FMC_OP_CTRL				0x68
#define op_ctrl_rd_opcode(_code)		(((_code) & 0xff) << 16)
#define op_ctrl_wr_opcode(_code)		(((_code) & 0xff) << 8)
#define op_ctrl_rd_op_sel(_op)			(((_op) & 0x3) << 4)
#define op_ctrl_dma_op(_type)			((_type) << 2)
#define op_ctrl_rw_op(_op)			((_op) << 1)
#define OP_CTRL_DMA_OP_READY			1

#define RD_OP_READ_ALL_PAGE			0x0
#define RD_OP_READ_OOB				0x1
#define RD_OP_BLOCK_READ			0x2

#define RD_OP_SHIFT				4
#define RD_OP_MASK				(0x3 << RD_OP_SHIFT)

#define OP_TYPE_DMA				0x0
#define OP_TYPE_REG				0x1

#define RW_OP_READ				0x0
#define RW_OP_WRITE				0x1

/*****************************************************************************/
#define FMC_OP_PARA				0x70
#define FMC_OP_PARA_RD_OOB_ONLY			(1 << 1)

/*****************************************************************************/
#define FMC_BOOT_SET				0x74
#define FMC_BOOT_SET_DEVICE_ECC_EN		(1 << 3)
#define FMC_BOOT_SET_BOOT_QUAD_EN		(1 << 1)

/*****************************************************************************/
#define FMC_STATUS				0xac

#define GET_OP					0
#define SET_OP					1

#define STATUS_ECC_MASK				(0x3 << 4)
#define STATUS_P_FAIL_MASK			(1 << 3)
#define STATUS_E_FAIL_MASK			(1 << 2)
#define STATUS_WEL_MASK				(1 << 1)
#define STATUS_OIP_MASK				(1 << 0)

/*****************************************************************************/
#define FMC_VERSION				0xbc

/* Hifmc IP version */
#define HIFMC_VER_100				0x100

#endif /* End of CONFIG_HIFMC */

/*****************************************************************************/
#define DISABLE					0
#define ENABLE					1

/*****************************************************************************/
/* DMA address align with 32 bytes. */
#define FMC_DMA_ALIGN				32

#define FMC_CHIP_DELAY				25

#define TMP_BUF_LEN				128
/*****************************************************************************/
#define hifmc_read(_host, _reg) \
	readl((uintptr_t)((char *)_host->regbase + (_reg)))

#define hifmc_write(_host, _reg, _value) \
	writel((u_int)(_value), (uintptr_t)((char *)_host->regbase + (_reg)))

#define get_page_index(host) \
		((host->addr_value[0] >> 16) | (host->addr_value[1] << 16))

/*****************************************************************************/
#define db_msg(_fmt, arg...) \
	printf("%s(%d): " _fmt, __func__, __LINE__, ##arg);

#define db_bug(fmt, args...) \
	do { \
		printf("%s(%d): BUG: " fmt, __FILE__, __LINE__, ##args); \
		while (1) ; \
	} while (0)

/*****************************************************************************/

#ifdef CONFIG_MINI_BOOT
#define FMC_INFO    0
#else
#define FMC_INFO    1
#endif

#define BT_DBG		0 /* Boot init debug print */
#define ER_DBG		0 /* Erase debug print */
#define WR_DBG		0 /* Write debug print */
#define RD_DBG		0 /* Read debug print */
#define QE_DBG		0 /* Quad Enable debug print */
#define OP_DBG		0 /* OP command debug print */
#define DMA_DB		0 /* DMA read or write debug print */
#define AC_DBG		0 /* 3-4byte Address Cycle */
#define SR_DBG		0 /* Status Register debug print */
#define CR_DBG		0 /* Config Register debug print */
#define FT_DBG		0 /* Features debug print */
#define WE_DBG		0 /* Write Enable debug print */
#define BP_DBG		0 /* Block Protection debug print */
#define EC_DBG		0 /* enable/disable ecc0 and randomizer */
#define DTR_DB		0 /* 4DTR debug print */
#define RST_DB		0 /* enable/disable reset pin */
#define REG_DB		0 /* operation debug print */

#define fmc_pr(_type, _fmt, arg...) \
	do { \
		if (_type) \
			db_msg(_fmt, ##arg) \
	} while (0)

/*****************************************************************************/
#define FMC_WAIT_TIMEOUT	400000  /* 4s equals 400000*10us */

#define fmc_cmd_wait_cpu_finish(_host) \
	do { \
		unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
		do { \
			udelay(10);\
			regval = hifmc_read((_host), FMC_OP); \
			--timeout; \
		} while ((regval & FMC_OP_REG_OP_START) && timeout); \
		if (!timeout) \
			db_msg("Error: Wait cmd cpu finish timeout!\n"); \
	} while (0)

/*****************************************************************************/
#define fmc_dma_wait_int_finish(_host) \
	do { \
		unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
		do { \
			udelay(10);\
			regval = hifmc_read((_host), FMC_INT); \
			--timeout; \
		} while ((!(regval & FMC_INT_OP_DONE) && timeout)); \
		if (!timeout) { \
			debug_register_dump(); \
			db_msg("Error: Wait dma int finish timeout!\n"); \
		} \
	} while (0)

/*****************************************************************************/
#define fmc_dma_wait_cpu_finish(_host) \
	do { \
		unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
		do { \
			udelay(10);\
			regval = hifmc_read((_host), FMC_OP_CTRL); \
			--timeout; \
		} while ((regval & OP_CTRL_DMA_OP_READY) && timeout); \
		if (!timeout) { \
			debug_register_dump(); \
			db_msg("Error: Wait dma cpu finish timeout!\n"); \
		} \
	} while (0)

/*****************************************************************************/
#define clk_2x(_clk)    (((_clk) + 1) >> 1)
#define clk_4x(_clk)    (((_clk) + 1) >> 2)

enum OP {
	READ = 1,
	WRITE,
	ERASE,
};

/*****************************************************************************/
struct hifmc_cmd_op {
	unsigned char cs;
	unsigned char cmd;
	unsigned char l_cmd;
	unsigned char addr_h;
	unsigned int addr_l;
	unsigned int data_no;
	unsigned short option;
	unsigned short op_cfg;
};
/*****************************************************************************/
char *ulltostr(unsigned long long size);

void debug_register_dump(void);

int hifmc_ip_ver_check(void);

void hifmc_dev_type_switch(unsigned char type);

void *get_hifmc_ip(void);

unsigned char *get_cs_number(unsigned char cs);

unsigned int get_fmc_boot_mode (void);

#endif /* End of __HIFMC_COMMON_H__ */

