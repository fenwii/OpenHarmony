/**
 * ddr_ddrt_v2_0_shf0.h
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

 * DDRT register offset address, mask, bit.
 */

/* register offset address */
/* base address: DDR_REG_BASE_DDRT */
#define DDRT_OP			0x0	/* DDRT operation config */
#define DDRT_STATUS		0x4	/* DDRT status indicating */
#define DDRT_BURST_CONFIG	0x8	/* DDRT burst transfer config */
#define DDRT_MEM_CONFIG		0xc	/* DDRT SDRAM config */
#define DDRT_BURST_NUM		0x10	/* DDRT burst number config */
/* DDRT burst number config register while testing address */
#define DDRT_ADDR_NUM		0x14
#define DDRT_LOOP_NUM		0x18	/* DDRT loop number config */
/* This register specified the system DDR starting address */
#define DDRT_DDR_BASE_ADDR	0x1c
#define DDRT_ADDR		0x20	/* DDRT test start address config  */
#define DDRT_REVERSED_DQ	0x30	/* DDRT reversed DQ indicating */
#define DDRT_SEED		0x38	/* DDRT starting random seed */
#define DDRT_KDATA		0x3c	/* DDRT kdata config */
#define DDRT_DATA0		0x40	/* DDRT PRBS7 data config register0 */
#define DDRT_DATA1		0x44	/* DDRT PRBS7 data config register1 */
#define DDRT_DATA2		0x48	/* DDRT PRBS7 data config register2 */
#define DDRT_DATA3		0x4c	/* DDRT PRBS7 data config register3 */

/* DQ3~DQ0 error number indicator, every 8bit for each DQ */
#define DDRT_DQ_ERR_CNT(n)	(0x60 + ((n) << 2))
/* DQ31~DQ0 error number overflow indicator, every bit for each DQ. */
#define DDRT_DQ_ERR_OVFL	0x80

/* register mask */
#define DDRT_TEST_MODE_MASK	0x300	/* DDRT Test Mode */
#define DDRT_TEST_DONE_MASK	0x1	/* [0] DDRT operation finish signal.*/
/* [1] DDRT Test result indicator. No error occurred, test pass. */
#define DDRT_TEST_PASS_MASK	0x2

/* register bit */
#define DDRT_DDR_MEM_WIDTH	12	/* SDRAM total width */

/* register value */
#define DDRT_CFG_START		0x1
#define DDRT_CFG_BURST_CFG_DATAEYE	0x4f
#define DDRT_CFG_BURST_CFG_GATE	0x43
#ifdef CFG_EDA_VERIFY
#define DDRT_CFG_BURST_NUM 0x5 /* ddrt test number */
#else
#define DDRT_CFG_BURST_NUM 0x7f /* ddrt test number */
#endif
#define DDRT_CFG_SEED		0x6d6d6d6d
#define DDRT_CFG_REVERSED	0x55aa55aa
#ifndef DDRT_CFG_BASE_ADDR
/* [CUSTOM] DDR training start address. MEM_BASE_DDR */
#define DDRT_CFG_BASE_ADDR	0x0
#endif
/* [CUSTOM] DDRT test address. 0x800000 = 8M */
#define DDRT_CFG_TEST_ADDR_CMD	(DDRT_CFG_BASE_ADDR + 0x800000)
/* [CUSTOM] DDRT test start address. */
#define DDRT_CFG_TEST_ADDR_BOOT	DDRT_CFG_BASE_ADDR
#define DDRT_CFG_ADDR_NUM	0xffffffff
#define DDRT_CFG_LOOP_NUM	0x0

/* [2:0]000:8 bit; 001:9 bit; 010:10 bit; 011:11 bit; 100:12 bit.
single SDRAM column number.*/
#define DDRT_DDR_COL_WIDTH	0x2
/* [6:4]000:11 bit; 001:12 bit; 010:13 bit; 011:14 bit; 100:15 bit; 101:16 bit.
single SDRAM row number */
#define DDRT_DDR_ROW_WIDTH	0x50
/* [8]0:4 Bank; 1:8 Bank. single SDRAM bank number */
#define DDRT_DDR_BANK_WIDTH	0x100


#define DDRT_WR_COMPRARE_MODE	(0<<8)	/* Write read & compare mode */
#define DDRT_WRITE_ONLY_MODE	(1<<8)	/* Write only mode */
#define DDRT_READ_ONLY_MODE	(2<<8)	/* Read only mode */
#define DDRT_RANDOM_WR_MODE	(3<<8)	/* Random write & read mode */

#define DDRT_PATTERM_PRBS9	(0<<12)
#define DDRT_PATTERM_PRBS7	(1<<12)
#define DDRT_PATTERM_PRBS11	(2<<12)
#define DDRT_PATTERM_K28_5	(3<<12)

/* other */
#define DDRT_WAIT_TIMEOUT	(1000000)
#define DDRT_READ_TIMEOUT	(20)
#define DDRT_PCODE_WAIT_TIMEOUT	(100000)

/* DDRT test DDR using space */
#define DDRT_GET_TEST_ADDR(addr) (addr)
