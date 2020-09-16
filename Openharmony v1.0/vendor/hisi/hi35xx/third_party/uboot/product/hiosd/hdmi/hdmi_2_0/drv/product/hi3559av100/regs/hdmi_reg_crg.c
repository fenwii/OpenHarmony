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

#include "hi_type.h"
#include "hdmi_reg_crg.h"
#include "hdmi_product_define.h"

volatile hdmi_reg_crg *g_reg_crg = NULL;

int reg_hdmi_crg_reg_init(void)
{
    if (g_reg_crg != NULL) {
        return HI_SUCCESS;
    }

    g_reg_crg  = (volatile hdmi_reg_crg *)(hi_uintptr_t)HDMI_IO_MAP(HDMI_ADDR_CRG, sizeof(hdmi_reg_crg));
    if (g_reg_crg == NULL) {
        hdmi_err("ioremap_nocache gophdmi2tx_dphy_regAllReg failed!!!!!!!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

int reg_hdmi_crg_reg_deinit(void)
{
    if (g_reg_crg != HI_NULL) {
        HDMI_IO_UNMAP(g_reg_crg);
        g_reg_crg = HI_NULL;
    }

    return HI_SUCCESS;
}

int reg_mpll_crg_mpll_postdiv1_set(unsigned int mpll_postdiv1)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg_mpll0 o_peri_crgmpll0;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg_mpll0.u32);
    o_peri_crgmpll0.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crgmpll0.bits.mpll_postdiv1 = mpll_postdiv1;
    hdmi_tx_reg_write(reg_addr, o_peri_crgmpll0.u32);

    return HI_SUCCESS;
}

int reg_mpll_crg_mpll_postdiv2_set(unsigned int mpll_postdiv2)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg_mpll0 o_peri_crgmpll0;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg_mpll0.u32);
    o_peri_crgmpll0.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crgmpll0.bits.mpll_postdiv2 = mpll_postdiv2;
    hdmi_tx_reg_write(reg_addr, o_peri_crgmpll0.u32);

    return HI_SUCCESS;
}

int reg_mpll_crg_mpll_dsmpd_set(unsigned int mpll_dsmpd)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg_mpll1 o_peri_crgmpll1;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg_mpll1.u32);
    o_peri_crgmpll1.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crgmpll1.bits.mpll_dsmpd = mpll_dsmpd;
    hdmi_tx_reg_write(reg_addr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int reg_mpll_crg_mpll_refdiv_set(unsigned int mpll_refdiv)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg_mpll1 o_peri_crgmpll1;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg_mpll1.u32);
    o_peri_crgmpll1.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crgmpll1.bits.mpll_refdiv = mpll_refdiv;
    hdmi_tx_reg_write(reg_addr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int reg_mpll_crg_mpll_fbdiv_set(unsigned int mpll_fbdiv)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg_mpll1 o_peri_crgmpll1;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg_mpll1.u32);
    o_peri_crgmpll1.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crgmpll1.bits.mpll_fbdiv = mpll_fbdiv;
    hdmi_tx_reg_write(reg_addr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int reg_mpll_crg_mpll_pd_set(unsigned int mpll_pd)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg_mpll1 o_peri_crgmpll1;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg_mpll1.u32);
    o_peri_crgmpll1.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crgmpll1.bits.mpll_pd = mpll_pd;
    hdmi_tx_reg_write(reg_addr, o_peri_crgmpll1.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_osc_24m_cken_set(unsigned int hdmitx_ctrl_osc_24m_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_osc_24m_cken = hdmitx_ctrl_osc_24m_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_cec_cken_set(unsigned int hdmitx_ctrl_cec_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_cec_cken = hdmitx_ctrl_cec_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_os_cken_set(unsigned int hdmitx_ctrl_os_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_os_cken = hdmitx_ctrl_os_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_as_cken_set(unsigned int hdmitx_ctrl_as_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_as_cken = hdmitx_ctrl_as_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_bus_srst_req_set(unsigned int hdmitx_ctrl_bus_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_bus_srst_req = hdmitx_ctrl_bus_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_srst_req_set(unsigned int hdmitx_ctrl_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_srst_req = hdmitx_ctrl_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_ctrl_cec_srst_req_set(unsigned int hdmitx_ctrl_cec_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.hdmitx_ctrl_cec_srst_req = hdmitx_ctrl_cec_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_mpll_tmds_cken_set(unsigned int mpll_tmds_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.mpll_tmds_cken = mpll_tmds_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_mpll_refclk_cksel_set(unsigned int mpll_refclk_cksel)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg68 o_peri_crg68;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg68.u32);
    o_peri_crg68.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg68.bits.mpll_refclk_cksel = mpll_refclk_cksel;
    hdmi_tx_reg_write(reg_addr, o_peri_crg68.u32);

    return HI_SUCCESS;

}

int reg_hdmi_crg_hdmirx_phy_tmds_cken_set(unsigned int uhdmirx_phy_tmds_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.hdmirx_phy_tmds_cken = uhdmirx_phy_tmds_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmirx_phy_modclk_cken_set(unsigned int uhdmirx_phy_modclk_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.hdmirx_phy_modclk_cken = uhdmirx_phy_modclk_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_ac_ctrl_modclk_cken_set(unsigned int uac_ctrl_modclk_cken)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.ctrl_modclk_cken = uac_ctrl_modclk_cken;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_phy_srst_req_set(unsigned int hdmitx_phy_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.hdmitx_phy_srst_req = hdmitx_phy_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_phy_srst_req_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    return o_peri_crg70.bits.hdmitx_phy_srst_req;
}

int reg_hdmi_crg_hdmitx_phy_bus_srst_req_set(unsigned int hdmitx_phy_bus_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.hdmitx_phy_bus_srst_req = hdmitx_phy_bus_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_ac_ctrl_srst_req_set(unsigned int uac_ctrl_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.ctrl_srst_req = uac_ctrl_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_ac_ctrl_bus_srst_req_set(unsigned int uac_ctrl_bus_srst_req)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.ctrl_bus_srst_req = uac_ctrl_bus_srst_req;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_hdmitx_phy_clk_pctrl_set(unsigned int hdmitx_phy_clk_pctrl)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.hdmitx_phy_clk_pctrl = hdmitx_phy_clk_pctrl;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

int reg_hdmi_crg_mpll_tmds_cksel_set(unsigned int mpll_tmds_cksel)
{
    hi_u32 *reg_addr = NULL;
    r_peri_crg70 o_peri_crg70;

    reg_addr = (hi_u32*)&(g_reg_crg->peri_crg70.u32);
    o_peri_crg70.u32 = hdmi_tx_reg_read(reg_addr);
    o_peri_crg70.bits.mpll_tmds_cksel = mpll_tmds_cksel;
    hdmi_tx_reg_write(reg_addr, o_peri_crg70.u32);

    return HI_SUCCESS;
}

