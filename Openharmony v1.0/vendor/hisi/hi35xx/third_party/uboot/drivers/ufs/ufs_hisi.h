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
 * Description: ufs header
 */

#ifndef __UFS_HISI_H__
#define __UFS_HISI_H__

#define COMBO_PHY_V120
#define UFS_USE_HISI_MPHY_TC
#define CLOSE_CLK_GATING

#define REG_BASE_UFSHCI_ADDRESS   0x10010000
/* SYNOPSYS UniPro register */
#define UNIPRO_DME_RESET		0xD010
#define UNIPRO_DME_LAYBER_ENABLE	0xD000

/* MPHY registers addr */
#define AD_DIF_P_LS_TIMEOUT_VAL		0x0003
#define PWM_PREPARE_TO			0x00000080
#define SKP_DET_SEL			0x0009
#define SKP_DET_SEL_EN			0x00000001

#define MRX_EN				0x00F0
#define MRX_ENABLE			(0x01 << 0)
#define RX_SQ_VREF			0x00F1
#define RX_SQ_VREF_175			0x00000002
#define VCO_AUTO_CHG			0x00DF
#define VCO_AUTO_CHG_EN			(0x01 << 0)
#define VCO_FORCE_ON_EN			(0x01 << 1)

#define RG_PLL_PRE_DIV			0x00C2
#define RG_PLL_FBK_P			0x00C3
#define RG_PLL_FBK_S			0x00C4
#define RG_PLL_SWC_EN			0x00C9
#define RG_PLL_RXHSGR			0x00CD
#define RG_PLL_RXLSGR			0x00CE
#define RG_PLL_TXHSGR			0x00CF
#define HS_R_A_FBK_P			0x41
#define HS_R_B_FBK_P			0x4C
#define RG_PLL_TXLSGR			0x00D0

#define RG_PLL_TXHS_EN			0x00C7
#define RG_PLL_TXHS_ENANBLE		(0x01 << 0)
#define RG_PLL_TXHS_EN_CONTROL		(0x01 << 1)
#define RG_PLL_TXLS_EN			0x00C8
#define RG_PLL_TXLS_ENABLE		(0x01 << 0)
#define RG_PLL_TXLS_EN_CONTROL		(0x01 << 1)

#define CGE          BIT(12)
#define LP_AH8_PGE   BIT(17)

static inline void dwc_ufs_write_reg(uint32_t reg_offset, uint32_t value)
{
	writel(value, (uintptr_t)(REG_BASE_UFSHCI_ADDRESS + reg_offset));
}

static inline uint32_t dwc_ufs_read_reg(uint32_t reg_offset)
{
	return readl((uintptr_t)(REG_BASE_UFSHCI_ADDRESS + reg_offset));
}

#endif