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
        unsigned int hdmitx_ctrl_bus_srst_req : 1;  /* [0] */
        unsigned int hdmitx_ctrl_srst_req     : 1;  /* [1] */
        unsigned int hdmitx_ctrl_cec_srst_req : 1;  /* [2] */
        unsigned int hdmitx_ssc_srst_req      : 1;  /* [3] */
        unsigned int ssc_in_cken              : 1;  /* [4] */
        unsigned int ssc_bypass_cken          : 1;  /* [5] */
        unsigned int hdmitx_ctrl_osc_24m_cken : 1;  /* [6] */
        unsigned int hdmitx_ctrl_cec_cken     : 1;  /* [7] */
        unsigned int hdmitx_ctrl_os_cken      : 1;  /* [8] */
        unsigned int hdmitx_ctrl_as_cken      : 1;  /* [9] */
        unsigned int hdmitx_pxl_cken          : 1;  /* [10] */
        unsigned int reserved_0               : 13; /* [11..23] */
        unsigned int ssc_clk_div              : 4;  /* [24..27] */
        unsigned int ssc_bypass_clk_sel       : 1;  /* [28] */
        unsigned int reserved_1               : 3;  /* [29..31] */
    } bits;
    unsigned int u32;
} peri_crg8144;

typedef union {
    struct {
        unsigned int hdmitx_phy_srst_req : 1;  /* [0] */
        unsigned int phy_tmds_srst_req   : 1;  /* [1] */
        unsigned int reserved_0          : 2;  /* [2..3] */
        unsigned int phy_tmds_cken       : 1;  /* [4] */
        unsigned int reserved_1          : 19; /* [5..23] */
        unsigned int tmds_clk_div        : 3;  /* [24..26] */
        unsigned int reserved_2          : 5;  /* [27..31] */
    } bits;
    unsigned int u32;
} peri_crg8152;

typedef struct {
    volatile peri_crg8144 crg8144;     /* 0x7F40 */
    volatile unsigned int reserved[7]; /* 0x7F44~0x0x7F5C */
    volatile peri_crg8152 crg8152;     /* 0x7F60 */
} hdmi_reg_crg;

int hdmi_reg_crg_init(void);
int hdmi_reg_crg_deinit(void);
int hdmi_reg_ssc_in_cken_set(unsigned int ssc_in_cken);
int hdmi_reg_ssc_bypass_cken_set(unsigned int ssc_bypass_cken);
int hdmi_reg_ctrl_osc_24m_cken_set(unsigned int hdmitx_ctrl_osc_24m_cken);
int hdmi_reg_ctrl_cec_cken_set(unsigned int hdmitx_ctrl_cec_cken);
int hdmi_reg_ctrl_os_cken_set(unsigned int hdmitx_ctrl_os_cken);
int hdmi_reg_ctrl_as_cken_set(unsigned int hdmitx_ctrl_as_cken);
int hdmi_reg_ctrl_bus_srst_req_set(unsigned int hdmitx_ctrl_bus_srst_req);
int hdmi_reg_ctrl_srst_req_set(unsigned int hdmitx_ctrl_srst_req);
int hdmi_reg_cec_srst_req_set(unsigned int hdmitx_ctrl_cec_srst_req);
int hdmi_reg_ssc_srst_req_set(unsigned int hdmitx_ssc_srst_req);
int hdmi_reg_ssc_clk_div_set(unsigned int ssc_clk_div);
int hdmi_reg_pxl_cken_set(unsigned int hdmitx_pxl_cken);
int hdmi_reg_hdmirx_phy_tmds_cken_set(unsigned int phy_tmds_cken);
int hdmi_reg_phy_srst_req_set(unsigned int hdmitx_phy_srst_req);
int hdmi_reg_phy_srst_req_get(hi_void);
int hdmi_reg_phy_tmds_srst_req_set(unsigned int phy_tmds_srst_req);
int hdmi_reg_phy_tmds_srst_req_get(hi_void);
int hdmi_reg_phy_srst_req_get(hi_void);
int hdmi_reg_tmds_clk_div_set(unsigned int tmds_clk_div);
#endif /* __HDMI_REG_CRG_H__ */

