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

#ifndef __HDMI_PRODUCT_DEFINE_H__
#define __HDMI_PRODUCT_DEFINE_H__

#include "ubi_uboot.h"
#include "malloc.h"
#include "boot_hdmi_intf.h"
#include "hi_type.h"

#define HDMI_CHIP_HI3559AV100       0x3559a100
#define HDMI_CTRL_BASE_ADDR         0x11140000
#define HDMI_ADDR_BASE_IO_CFG       0x12040000
#define HDMI_ADDR_CRG               0x12010000 /* CRG reg */
#define BASE_ADDR_tx_dphy           0x11160000 /* hdmi tx phy reg */
#define HDMI_ADDR_SC                0x12020000 /* system ctrol */
#define HDMI_SYS_TIMER_ADDR         0x12000000 /* timer base addr */
#define HDMI_TIMER11_OFFSET         0x5020    /* timer11 offset addr */
#define HDMI_COLOR_BAR_MASK         0x70000000
#define HDMI_COLOR_BAR_UPDATE_MASK  0x00000001
#define HDMI_COLOR_BAR_BASE         0x1110d000 /* VDP */
/* HDMI REG */
#define HDMI_TX_BASE_ADDR           0x11140000
#define HDMI_TX_REG_LEN             0x30000
#define HDMI_TX_BASE_ADDR_CTRL      0x0000
#define HDMI_TX_BASE_ADDR_AIDEO     0x08EC /* 800-8E8 useless, video_path_regs start with 8EC */
#define HDMI_TX_BASE_ADDR_AUDIO     0x1000
#define HDMI_TX_BASE_ADDR_HDMITX    0x1800
#define HDMI_TX_BASE_ADDR_HDCP1X    0x2000
#define HDMI_RX_BASE_ADDR_FRL       0x3000
#define HDMI_TX_BASE_ADDR_AON       0x4040 /* 4000-403C useless, tx_aon_reg_type start with 4040 */
#define HDMI_TX_BASE_ADDR_CEC       0x4800
#define HDMI_TX_BASE_ADDR_MCU_PRAM  0x10000
#define HDMI_TX_BASE_ADDR_MCU_DRAM  0x18000
#define HDMI_TX_BASE_ADDR_MCU       0x1c000
#define HDMI_TX_BASE_ADDR_DPHY      0x20000
#define HDMI_REGISTER_SIZE          4
/* HDMI PHY */
#define HDMI_TX_PHY_ADDR            (HDMI_TX_BASE_ADDR + HDMI_TX_BASE_ADDR_DPHY)
#define HDMI_ONE_BEAT_CLK           600000

#ifdef HI_ADVCA_FUNCTION_RELEASE
#define  CONFIG_HDMI_PROC_DISABLE
#define  CONFIG_HDMI_DEBUG_DISABLE
#endif
#define HDMI_IO_MAP(phys_addr, len) (phys_addr)
#define HDMI_IO_UNMAP(virt_addr)

typedef struct {
    hi_u32 ssc_bypass_div;
    hi_u32 tmds_clk_div;
} hdmi_crg_cfg;

hi_s32 hdmi_tx_reg_write(hi_u32 *reg_addr, hi_u32 value);

hi_u32 hdmi_tx_reg_read(hi_u32 *reg_addr);

hi_s32 hdmi_reg_write_u32(hi_u32 reg_addr, hi_u32 value);

hi_u32 hdmi_reg_read_u32 (hi_u32 reg_addr);

hi_void drv_hdmi_prod_io_cfg_set(hi_void);

hi_void drv_hdmi_prod_crg_all_reset_set(hi_bool enable);

hi_void drv_hdmi_prod_crg_gate_set(hi_bool enable);

hi_void drv_hdmi_prod_crg_div_set(hdmi_crg_cfg *crg_cfg);

hi_void drv_hdmi_prod_crg_phy_reset_set(hi_bool enable);

hi_void drv_hdmi_prod_crg_phy_reset_get(hi_bool *enable);

hi_void drv_hdmi_prod_crg_init(hi_void);

hi_void drv_hdmi_hardware_reset(hi_void);

hi_void drv_hdmi_low_power_set(hi_bool enable);

#endif  /* __HDMI_PRODUCT_DEFINE_H__ */

