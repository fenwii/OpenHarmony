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
#include "hdmi_reg_crg.h"

#define HDMI_IO_CFG_FUNCTION1_SEL 0x1

#define PRODUCT_NULL_CHK(p)                                    \
    do {                                                       \
        if ((p) == HI_NULL) {                                  \
            hdmi_err("%s is null pointer!return fail.\n", #p); \
            return HI_FAILURE;                                 \
        }                                                      \
    } while (0)

#define PRODUCT_NULL_CHK_NORET(p)                              \
    do {                                                       \
        if ((p) == HI_NULL) {                                  \
            hdmi_err("%s is null pointer!return fail.\n", #p); \
            return;                                            \
        }                                                      \
    } while (0)

hi_s32 hdmi_tx_reg_write  (hi_u32 *reg_addr, hi_u32 value)
{
    PRODUCT_NULL_CHK(reg_addr);
    *(volatile hi_u32*)reg_addr = value;
    return HI_SUCCESS;
}

hi_u32 hdmi_tx_reg_read(hi_u32 *reg_addr)
{
    PRODUCT_NULL_CHK(reg_addr);
    return *(volatile hi_u32*)(reg_addr);
}

hi_s32 hdmi_reg_write_u32(hi_u32 reg_addr, hi_u32 value)
{
    volatile hi_u32 *addr = HI_NULL;

    addr = (volatile hi_u32 *)(hi_uintptr_t)HDMI_IO_MAP((hi_u64)reg_addr, HDMI_REG_SIZE);
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
    volatile hi_u32 *addr = HI_NULL;
    hi_u32 value = 0;

    addr = (volatile hi_u32 *)(hi_uintptr_t)HDMI_IO_MAP((hi_u64)reg_addr, HDMI_REG_SIZE);
    if (addr != HI_NULL) {
        value = *addr ;
        HDMI_IO_UNMAP(addr);
    } else {
        hdmi_err("HDMI_IO_MAP addr=0x%x\n err!\n", reg_addr);
    }

    return  value;
}

hi_void drv_hdmi_prod_io_cfg_set(hi_void)
{
    return;
}

hi_void drv_hdmi_prod_crg_gate_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    /* Gate */
    reg_hdmi_crg_hdmitx_ctrl_osc_24m_cken_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_cec_cken_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_os_cken_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_as_cken_set(enable);
    reg_hdmi_crg_mpll_tmds_cken_set(enable);
    reg_hdmi_crg_hdmirx_phy_tmds_cken_set(enable);
    reg_hdmi_crg_hdmirx_phy_modclk_cken_set(enable);
    reg_hdmi_crg_ac_ctrl_modclk_cken_set(enable);
    reg_hdmi_crg_hdmitx_phy_clk_pctrl_set(HI_FALSE);
    reg_hdmi_crg_mpll_tmds_cksel_set(0);
#endif

    return;
}

hi_void drv_hdmi_prod_crg_all_reset_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    reg_hdmi_crg_hdmitx_ctrl_bus_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_cec_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_phy_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_phy_bus_srst_req_set(enable);
    reg_hdmi_crg_ac_ctrl_srst_req_set(enable);
    reg_hdmi_crg_ac_ctrl_bus_srst_req_set(enable);
    enable = !enable;
    /*
     * delay 2us, to ensure ctrl reset success.
     * because internal clock of HDMI is smaller than APB clock.
     */
    udelay(2);
    reg_hdmi_crg_hdmitx_ctrl_bus_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_cec_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_phy_srst_req_set(enable);
    reg_hdmi_crg_hdmitx_phy_bus_srst_req_set(enable);
    reg_hdmi_crg_ac_ctrl_srst_req_set(enable);
    reg_hdmi_crg_ac_ctrl_bus_srst_req_set(enable);
    /* delay 100ms, HPD can not read after reset when enable HPD filtering if not delay. */
    mdelay(100);
#endif
    return;
}

hi_void drv_hdmi_prod_reg_defaut_cfg(hi_void)
{
    /* The following register should be set default values */
    hdmi_reg_write_u32(HDMI_CTRL_BASE_ADDR | 0x14b8, 0x00);

    return;
}

hi_void drv_hdmi_low_power_set(hi_bool enable)
{
#ifndef HDMI_FPGA_SUPPORT
    enable = !enable;
    reg_hdmi_crg_hdmitx_ctrl_os_cken_set(enable);
    reg_hdmi_crg_hdmitx_ctrl_as_cken_set(enable);
    reg_hdmi_crg_mpll_tmds_cken_set(enable);
    reg_mpll_crg_mpll_pd_set(!enable);
#endif

    return;
}

hi_void drv_hdmi_prod_crg_init(hi_void)
{
    drv_hdmi_prod_io_cfg_set();
    drv_hdmi_prod_crg_gate_set(HI_TRUE);
    drv_hdmi_prod_crg_all_reset_set(HI_TRUE);
    drv_hdmi_prod_reg_defaut_cfg();

    return;
}

hi_void drv_hdmi_hardware_reset(hi_void)
{
#ifndef HDMI_FPGA_SUPPORT
    if (HI_SUCCESS != reg_hdmi_crg_reg_init()) {
        hdmi_err("CRG reg io map error!\n");
        return;
    }

    /* reset all module */
    reg_hdmi_crg_hdmitx_ctrl_bus_srst_req_set(HI_TRUE);
    reg_hdmi_crg_hdmitx_ctrl_srst_req_set(HI_TRUE);
    reg_hdmi_crg_hdmitx_ctrl_cec_srst_req_set(HI_TRUE);
    reg_hdmi_crg_hdmitx_phy_srst_req_set(HI_TRUE);
    reg_hdmi_crg_hdmitx_phy_bus_srst_req_set(HI_TRUE);
    reg_hdmi_crg_ac_ctrl_srst_req_set(HI_TRUE);
    reg_hdmi_crg_ac_ctrl_bus_srst_req_set(HI_TRUE);
    /* close all clk */
    drv_hdmi_prod_crg_gate_set(HI_FALSE);
    drv_hdmi_low_power_set(HI_TRUE);
    reg_hdmi_crg_reg_deinit();
#endif
}

