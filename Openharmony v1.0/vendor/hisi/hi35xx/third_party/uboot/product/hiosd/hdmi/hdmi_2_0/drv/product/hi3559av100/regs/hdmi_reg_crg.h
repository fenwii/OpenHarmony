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

#ifndef __HDMI_REG_CRG_H__
#define __HDMI_REG_CRG_H__

typedef union {
    struct {
        unsigned int mpll_frac     : 24; /* [23..0] */
        unsigned int mpll_postdiv1 : 3;  /* [26..24] */
        unsigned int reserved0     : 1;  /* [27] */
        unsigned int mpll_postdiv2 : 3;  /* [30..28] */
        unsigned int reserved1     : 1;  /* [31] */
    } bits;
    unsigned int u32;
} r_peri_crg_mpll0;

typedef union {
    struct {
        unsigned int mpll_fbdiv        : 12; /* [11..0] */
        unsigned int mpll_refdiv       : 6;  /* [17..12] */
        unsigned int reserved0         : 2;  /* [19..18] */
        unsigned int mpll_fout4phasepd : 1;  /* [20] */
        unsigned int mpll_postdivpd    : 1;  /* [21] */
        unsigned int mpll_foutvcopd    : 1;  /* [22] */
        unsigned int mpll_pd           : 1;  /* [23] */
        unsigned int mpll_dsmpd        : 1;  /* [24] */
        unsigned int mpll_dacpd        : 1;  /* [25] */
        unsigned int mpll_bypass       : 1;  /* [26] */
        unsigned int mpll_foutvco2xpd  : 1;  /* [27] */
        unsigned int reserved1         : 4;  /* [31..28] */
    } bits;
    unsigned int u32;
} r_peri_crg_mpll1;

typedef union {
    struct {
        unsigned int reserved_0               : 2;  /* [1..0] */
        unsigned int hdmitx_ctrl_osc_24m_cken : 1;  /* [2] */
        unsigned int hdmitx_ctrl_cec_cken     : 1;  /* [3] */
        unsigned int hdmitx_ctrl_os_cken      : 1;  /* [4] */
        unsigned int hdmitx_ctrl_as_cken      : 1;  /* [5] */
        unsigned int hdmitx_ctrl_bus_srst_req : 1;  /* [6] */
        unsigned int hdmitx_ctrl_srst_req     : 1;  /* [7] */
        unsigned int hdmitx_ctrl_cec_srst_req : 1;  /* [8] */
        unsigned int reserved_1               : 7;  /* [15..9] */
        unsigned int mpll_tmds_cken           : 1;  /* [16] */
        unsigned int mpll_refclk_cksel        : 1;  /* [17] */
        unsigned int reserved_2               : 14; /* [31..18]*/
    } bits;
    unsigned int u32;

} r_peri_crg68;

typedef union {
    struct {
        unsigned int hdmirx_phy_tmds_cken    : 1;  /* [0] */
        unsigned int hdmirx_phy_modclk_cken  : 1;  /* [1] */
        unsigned int ctrl_modclk_cken        : 1;  /* [2] */
        unsigned int reserved_0              : 1;  /* [3] */
        unsigned int hdmitx_phy_srst_req     : 1;  /* [4] */
        unsigned int hdmitx_phy_bus_srst_req : 1;  /* [5] */
        unsigned int ctrl_srst_req           : 1;  /* [6] */
        unsigned int ctrl_bus_srst_req       : 1;  /* [7] */
        unsigned int hdmitx_phy_clk_pctrl    : 1;  /* [8] */
        unsigned int mpll_tmds_cksel         : 1;  /* [10..9] */
        unsigned int reserved_1              : 22; /* [31..11] */
    } bits;
    unsigned int u32;
} r_peri_crg70;

typedef struct {
    volatile unsigned int     reserved_0[12]; /* 0x00~0x2c */
    volatile r_peri_crg_mpll0 peri_crg_mpll0; /* 0x30 */
    volatile r_peri_crg_mpll0 peri_crg_mpll1; /* 0x34 */
    volatile unsigned int     reserved_1[54]; /* 0x38~0x10c */
    volatile r_peri_crg68     peri_crg68;     /* 0x0110 */
    volatile unsigned int     reserved_2;
    volatile r_peri_crg70     peri_crg70;     /* 0x0118 */
} hdmi_reg_crg;

int reg_hdmi_crg_reg_init(void);
int reg_hdmi_crg_reg_deinit(void);
int reg_mpll_crg_mpll_postdiv1_set(unsigned int mpll_postdiv1);
int reg_mpll_crg_mpll_postdiv2_set(unsigned int mpll_postdiv2);
int reg_mpll_crg_mpll_dsmpd_set(unsigned int mpll_dsmpd);
int reg_mpll_crg_mpll_refdiv_set(unsigned int mpll_refdiv);
int reg_mpll_crg_mpll_fbdiv_set(unsigned int mpll_fbdiv);
int reg_mpll_crg_mpll_pd_set(unsigned int mpll_pd);
int reg_hdmi_crg_hdmitx_ctrl_osc_24m_cken_set(unsigned int hdmitx_ctrl_osc_24m_cken);
int reg_hdmi_crg_hdmitx_ctrl_cec_cken_set(unsigned int hdmitx_ctrl_cec_cken);
int reg_hdmi_crg_hdmitx_ctrl_os_cken_set(unsigned int hdmitx_ctrl_os_cken);
int reg_hdmi_crg_hdmitx_ctrl_as_cken_set(unsigned int hdmitx_ctrl_as_cken);
int reg_hdmi_crg_hdmitx_ctrl_bus_srst_req_set(unsigned int hdmitx_ctrl_bus_srst_req);
int reg_hdmi_crg_hdmitx_ctrl_srst_req_set(unsigned int hdmitx_ctrl_srst_req);
int reg_hdmi_crg_hdmitx_ctrl_cec_srst_req_set(unsigned int hdmitx_ctrl_cec_srst_req);
int reg_hdmi_crg_mpll_tmds_cken_set(unsigned int mpll_tmds_cken);
int reg_hdmi_crg_mpll_refclk_cksel_set(unsigned int mpll_refclk_cksel);
int reg_hdmi_crg_hdmirx_phy_tmds_cken_set(unsigned int uhdmirx_phy_tmds_cken);
int reg_hdmi_crg_hdmirx_phy_modclk_cken_set(unsigned int uhdmirx_phy_modclk_cken);
int reg_hdmi_crg_ac_ctrl_modclk_cken_set(unsigned int ac_ctrl_modclk_cken);
int reg_hdmi_crg_hdmitx_phy_srst_req_set(unsigned int hdmitx_phy_srst_req);
int reg_hdmi_crg_hdmitx_phy_srst_req_get(void);
int reg_hdmi_crg_hdmitx_phy_bus_srst_req_set(unsigned int hdmitx_phy_bus_srst_req);
int reg_hdmi_crg_ac_ctrl_srst_req_set(unsigned int ac_ctrl_srst_req);
int reg_hdmi_crg_ac_ctrl_bus_srst_req_set(unsigned int ac_ctrl_bus_srst_req);
int reg_hdmi_crg_hdmitx_phy_clk_pctrl_set(unsigned int hdmitx_phy_clk_pctrl);
int reg_hdmi_crg_mpll_tmds_cksel_set(unsigned int mpll_tmds_cksel);
#endif /* __HDMI_REG_CRG_H__ */

