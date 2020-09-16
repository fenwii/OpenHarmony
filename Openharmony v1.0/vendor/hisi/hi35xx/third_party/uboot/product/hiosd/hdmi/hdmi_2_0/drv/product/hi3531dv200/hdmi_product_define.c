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

#include "hdmi_product_define.h"
#include "hdmi_reg_dphy.h"
#include "hdmi_reg_crg.h"

#define HDMI_IO_CFG_FUNCTION1_SEL 0x1

hi_s32 hdmi_tx_reg_write(hi_u32 *reg_addr, hi_u32 value)
{
    hdmi_if_null_return(reg_addr, HI_FAILURE);
    *(volatile hi_u32*)reg_addr = value;
    return HI_SUCCESS;
}

hi_u32 hdmi_tx_reg_read(hi_u32 *reg_addr)
{
    hdmi_if_null_return(reg_addr, HI_FAILURE);
    return *(volatile hi_u32*)(reg_addr);
}

hi_s32 hdmi_reg_write_u32(hi_u32 reg_addr, hi_u32 value)
{
    volatile hi_u32 *addr = HI_NULL;

    addr = (volatile hi_u32 *)(uintptr_t)HDMI_IO_MAP(reg_addr, HDMI_REG_SIZE);
    if (addr != HI_NULL) {
        *addr = value ;
        HDMI_IO_UNMAP(addr);
        return HI_SUCCESS;
    } else {
        hdmi_err("HDMI_IO_MAP addr=0x%x err!\n", reg_addr);
        return HI_FAILURE;
    }
}

hi_u32 hdmi_reg_read_u32 (hi_u32 reg_addr)
{
    hi_u32 value = 0;
    volatile hi_u32 *addr = HI_NULL;

    addr = (volatile hi_u32 *)(uintptr_t)HDMI_IO_MAP(reg_addr, HDMI_REG_SIZE);
    if (addr != HI_NULL) {
        value = *addr ;
        HDMI_IO_UNMAP(addr);
    } else {
        hdmi_err("HDMI_IO_MAP addr=0x%x\n err!\n", reg_addr);
    }

    return value;
}

hi_void drv_hdmi_prod_io_cfg_set(hi_void)
{
#ifndef HDMI_FPGA_SUPPORT
    (hi_void)hdmi_reg_write_u32(HDMI_ADDR_IO_CFG_HOTPLUG, HDMI_IO_CFG_FUNCTION1_SEL);
    (hi_void)hdmi_reg_write_u32(HDMI_ADDR_IO_CFG_SDA, HDMI_IO_CFG_FUNCTION1_SEL);
    (hi_void)hdmi_reg_write_u32(HDMI_ADDR_IO_CFG_SCL, HDMI_IO_CFG_FUNCTION1_SEL);
#endif

    return;
}

hi_void drv_hdmi_prod_crg_gate_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    /* gate */
    hdmi_reg_ssc_in_cken_set(enable);
    hdmi_reg_ssc_bypass_cken_set(enable);
    hdmi_reg_ctrl_osc_24m_cken_set(enable);
    hdmi_reg_ctrl_cec_cken_set(enable);
    hdmi_reg_ctrl_os_cken_set(enable);
    hdmi_reg_ctrl_as_cken_set(enable);
    hdmi_reg_pxl_cken_set(enable);
    hdmi_reg_hdmirx_phy_tmds_cken_set(enable);
#endif

    return;
}

hi_void drv_hdmi_prod_crg_all_reset_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    hdmi_reg_ctrl_bus_srst_req_set(enable);
    hdmi_reg_ctrl_srst_req_set(enable);
    hdmi_reg_cec_srst_req_set(enable);
    hdmi_reg_ssc_srst_req_set(enable);
    hdmi_reg_phy_srst_req_set(enable);
    hdmi_reg_phy_tmds_srst_req_set(enable);
    enable = !enable;
    /* delay 1us, to insure ctrl reset success. */
    udelay(1);
    hdmi_reg_ctrl_bus_srst_req_set(enable);
    hdmi_reg_ctrl_srst_req_set(enable);
    hdmi_reg_cec_srst_req_set(enable);
    hdmi_reg_ssc_srst_req_set(enable);
    hdmi_reg_phy_srst_req_set(enable);
    hdmi_reg_phy_tmds_srst_req_set(enable);
#endif

    return;
}

hi_void drv_hdmi_prod_crg_phy_reset_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    hdmi_reg_phy_srst_req_set(enable);
    hdmi_reg_phy_tmds_srst_req_set(enable);
    enable = !enable;
    hdmi_reg_phy_srst_req_set(enable);
    hdmi_reg_phy_tmds_srst_req_set(enable);
#endif

    return;
}

hi_void drv_hdmi_prod_crg_phy_reset_get(hi_bool *enable)
{
#ifndef HDMI_FPGA_SUPPORT
    hdmi_if_null_return_void(enable);
    if (hdmi_reg_phy_srst_req_get() || hdmi_reg_phy_tmds_srst_req_get()) {
        *enable = HI_TRUE;
    } else {
        *enable = HI_FALSE;
    }
#endif
    return;
}

hi_void drv_hdmi_prod_crg_div_set(hdmi_crg_cfg *crg_cfg)
{
#ifndef HDMI_FPGA_SUPPORT
    hi_u32 tmp;

    if (crg_cfg != HI_NULL) {
        tmp = crg_cfg->ssc_bypass_div - 1;
        hdmi_reg_ssc_clk_div_set(tmp);
        tmp = crg_cfg->tmds_clk_div - 1;
        hdmi_reg_tmds_clk_div_set(tmp);
        /* use phy reg to rest dphy, don't use CRG phy rst reg */
        hdmi_hdmitx_dphy_rst_reg_rstset(HI_TRUE);
        hdmi_hdmitx_dphy_rst_reg_rstset(HI_FALSE);
    }
#endif

    return;
}

hi_void drv_hdmi_prod_reg_defaut_cfg(hi_void)
{
    return;
}

hi_void drv_hdmi_prod_crg_init(hi_void)
{
#ifndef HDMI_FPGA_SUPPORT
    drv_hdmi_prod_io_cfg_set();
    drv_hdmi_prod_crg_gate_set(HI_TRUE);
    drv_hdmi_prod_crg_all_reset_set(HI_TRUE);
#endif
    return;
}

hi_void drv_hdmi_low_power_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    enable = !enable;
    hdmi_reg_ctrl_os_cken_set(enable);
    hdmi_reg_ctrl_as_cken_set(enable);
#endif

    return;
}

hi_void drv_hdmi_hardware_reset(hi_void)
{
#ifndef HDMI_FPGA_SUPPORT
    if (hdmi_reg_crg_init() == HI_FAILURE) {
        hdmi_err("hdmi crg reg init failed!!!!!!!\n");
        return;
    }
    hdmi_reg_ctrl_bus_srst_req_set(HI_TRUE);
    hdmi_reg_ctrl_srst_req_set(HI_TRUE);
    hdmi_reg_cec_srst_req_set(HI_TRUE);
    hdmi_reg_ssc_srst_req_set(HI_TRUE);
    hdmi_reg_phy_srst_req_set(HI_TRUE);
    hdmi_reg_phy_tmds_srst_req_set(HI_TRUE);
    hdmi_reg_ssc_in_cken_set(HI_FALSE);
    hdmi_reg_ssc_bypass_cken_set(HI_FALSE);
    hdmi_reg_ctrl_osc_24m_cken_set(HI_FALSE);
    hdmi_reg_ctrl_cec_cken_set(HI_FALSE);
    hdmi_reg_ctrl_os_cken_set(HI_FALSE);
    hdmi_reg_ctrl_as_cken_set(HI_FALSE);
    hdmi_reg_pxl_cken_set(HI_FALSE);
#endif

    return;
}

