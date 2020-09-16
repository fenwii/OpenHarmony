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
 */

#ifndef DDR_TRAINING_CUSTOM_H
#define DDR_TRAINING_CUSTOM_H

/* config DDRC, PHY, DDRT typte */
#define DDR_DDRC_V520_CONFIG
#define DDR_PHY_T12_V100_CONFIG
#define DDR_DDRT_T12_V100_CONFIG

/* config special item */
/* s40/t28/t16 not support dcc training */
#define DDR_VREF_TRAINING_CONFIG
#define DDR_VREF_WITHOUT_BDL_CONFIG
#define DDR_DCC_TRAINING_CONFIG

#define DDR_WL_TRAINING_DISABLE
#define DDR_GATE_TRAINING_DISABLE
#define DDR_TRAINING_UART_DISABLE
/* Disable write dm */
#define DDR_WRITE_DM_DISABLE

#define DDR_PHY_NUM              2 /* phy number */

#define DDR_DMC_PER_PHY_MAX      2 /* dmc number per phy max */

#define DDR_AXI_SWITCH_NUM       4 /* ddr training axi switch number */

/* config DDRC, PHY, DDRT base address */
/* [CUSTOM] DDR DMC0 base register */
#define DDR_REG_BASE_DMC0		0x12068000
/* [CUSTOM] DDR DMC1 base register */
#define DDR_REG_BASE_DMC1		0x12069000
/* [CUSTOM] DDR DMC2 base register */
#define DDR_REG_BASE_DMC2		0x1206a000
/* [CUSTOM] DDR DMC3 base register */
#define DDR_REG_BASE_DMC3		0x1206b000
/* [CUSTOM] DDR PHY0 base register */
#define DDR_REG_BASE_PHY0		0x1206c000
/* [CUSTOM] DDR PHY1 base register */
#define DDR_REG_BASE_PHY1		0x1206e000
/* [CUSTOM] DDR DDRT base register, ddrt1:0x1ff30000 */
#define DDR_REG_BASE_DDRT		0x12420000
/* [CUSTOM] DDR training item system control */
#define DDR_REG_BASE_SYSCTRL		0x12020000
#define DDR_REG_BASE_AXI		0x12060000

/* Serial Configuration */
#define DDR_REG_BASE_UART0		0x12100000

/* config offset address */
/* Assume sysctrl offset address for DDR training as follows,
if not please define. */
/* [CUSTOM] ddrt reversed data */
#define SYSCTRL_DDRT_PATTERN			0xa8
/* [CUSTOM] PHY2 ddrt reversed data */
#define SYSCTRL_DDRT_PATTERN_SEC		0xac
/* [CUSTOM] ddr training item */
#define SYSCTRL_DDR_TRAINING_CFG		0xa0
#define SYSCTRL_DDR_TRAINING_CFG_SEC		0xa4
/* [CUSTOM] ddr training version flag */
#define SYSCTRL_DDR_TRAINING_VERSION_FLAG	0x158
/* [CUSTOM] ddr training stat */
#define SYSCTRL_DDR_TRAINING_STAT		0x300

/* [CUSTOM] ddr hw training item */
#define SYSCTRL_DDR_HW_PHY0_RANK0		0x90
#define SYSCTRL_DDR_HW_PHY0_RANK1		0x94
#define SYSCTRL_DDR_HW_PHY1_RANK0		0x98
#define SYSCTRL_DDR_HW_PHY1_RANK1		0x9c

/* config other special */
/* [CUSTOM] DDR training start address. MEM_BASE_DDR */
#define DDRT_CFG_BASE_ADDR		0x40000000
/* [CUSTOM] SRAM start address.
NOTE: Makefile will parse it, plase define it as Hex. eg: 0xFFFF0C00 */
#define DDR_TRAINING_RUN_STACK		0x08000C00

#define DDR_TRAINING_SAVE_REG_FUNC(relate_reg, mask) \
	ddr_training_save_reg_custom(relate_reg, mask)

#define DDR_TRAINING_RESTORE_REG_FUNC(relate_reg) \
	ddr_training_restore_reg_custom(relate_reg)

void ddr_training_save_reg_custom(void *relate_reg, unsigned int mask);
void ddr_training_restore_reg_custom(void *relate_reg);
#endif /* DDR_TRAINING_CUSTOM_H */
