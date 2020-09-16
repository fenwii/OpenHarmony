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

#define HDMI_CHIP_HI3531DV200      0x3531d200
#define HDMI_CTRL_BASE_ADDR        0x17B40000
#define HDMI_ADDR_BASE_IO_CFG      0x17C70000
#define CRG_BASE_ADDR              0x11010000
#define HDMI_CRG_ADDR_OFFSET       0x7F40
#define HDMI_CRG_ADDR              ((CRG_BASE_ADDR) + (HDMI_CRG_ADDR_OFFSET))
#define BASE_ADDR_TX_DPHY          0x17BC0000
/* the mux IO reg should not config on FPGA board */
#define HDMI_ADDR_IO_CFG_HOTPLUG   (HDMI_ADDR_BASE_IO_CFG + 0x0)
#define HDMI_ADDR_IO_CFG_SDA       (HDMI_ADDR_BASE_IO_CFG + 0x4)
#define HDMI_ADDR_IO_CFG_SCL       (HDMI_ADDR_BASE_IO_CFG + 0x8)
#define HDMI_COLOR_BAR_MASK        0x60000000
#define HDMI_COLOR_BAR_UPDATE_MASK 0x00000001
#define HDMI_COLOR_BAR_BASE        0x17A0D000
/* HDMI TX CRG */
#define HDMI_TX_BASE_ADDR          0x17B40000
#define HDMI_TX_REG_LEN            0x20000
/* HDMI TX SUB-module */
#define HDMI_TX_BASE_ADDR_CTRL     0x0000
#define HDMI_TX_BASE_ADDR_AIDEO    0x0800
#define HDMI_TX_BASE_ADDR_AUDIO    0x1000
#define HDMI_TX_BASE_ADDR_HDMITX   0x1800
#define HDMI_TX_BASE_ADDR_HDCP1X   0x2000
#define HDMI_TX_BASE_ADDR_AON      0x4000
#define HDMI_TX_BASE_ADDR_CEC      0x4800
#define HDMI_TX_BASE_ADDR_MCU_PRAM 0x10000
#define HDMI_TX_BASE_ADDR_MCU_DRAM 0x18000
#define HDMI_TX_BASE_ADDR_MCU      0x1c000
#define HDMI_TX_BASE_ADDR_DPHY     0x10000
/* HDMI PHY,31dv200 ctrl and phy address is not continuous */
#define HDMI_TX_PHY_ADDR           0x17BC0000
#define BASE_ADDR_TX_CTRL_REG     (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_CTRL)
#define BASE_ADDR_VIDEO_PATH_REG  (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_AIDEO)
#define BASE_ADDR_AUDIO_PATH_REG  (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_AUDIO)
#define BASE_ADDR_TX_HDMI_REG     (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_HDMITX)
#define BASE_ADDR_TX_HDCP_REG     (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_HDCP1X)
#define BASE_ADDR_TX_AON_REG      (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_AON)
#define BASE_ADDR_TX_CEC_REG      (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_CEC)
#define BASE_ADDR_MCU_CPU_REG     (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_MCU)
#define BASE_ADDR_MCU_PARAM       (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_MCU_PRAM)
#define BASE_ADDR_MCU_DRAM        (HDMI_TX_BASE_ADDR | HDMI_TX_BASE_ADDR_MCU_DRAM)
#define HDMI_MMZ_ALIGN_BYTES       16
#define HDMI_FILE_MODE             0777

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

