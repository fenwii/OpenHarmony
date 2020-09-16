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
#include "hi_type.h"

typedef union {
    struct {
        unsigned int ssc_in_cken              : 1; /* [0]  */
        unsigned int ssc_bypass_cken          : 1; /* [1]  */
        unsigned int hdmitx_ctrl_osc_24m_cken : 1; /* [2]  */
        unsigned int hdmitx_ctrl_cec_cken     : 1; /* [3]  */
        unsigned int hdmitx_ctrl_os_cken      : 1; /* [4]  */
        unsigned int hdmitx_ctrl_as_cken      : 1; /* [5]  */
        unsigned int hdmitx_ctrl_bus_srst_req : 1; /* [6]  */
        unsigned int hdmitx_ctrl_srst_req     : 1; /* [7]  */
        unsigned int hdmitx_ctrl_cec_srst_req : 1; /* [8]  */
        unsigned int hdmitx_ssc_srst_req      : 1; /* [9]  */
        unsigned int ssc_clk_div              : 4; /* [13..10]  */
        unsigned int reserved_0               : 2; /* [15..14]  */
        unsigned int hdmitx_pxl_cken          : 1; /* [16]  */
        unsigned int reserved_1               : 2; /* [18..17]  */
        unsigned int ssc_bypass_clk_sel       : 1; /* [19]  */
    } bits;
    unsigned int u32;
} r_peri_crg68;

typedef union {
    struct {
        unsigned int phy_tmds_cken       : 1;  /* [0] */
        unsigned int reserved_0          : 3;  /* [3..1] */
        unsigned int hdmitx_phy_srst_req : 1;  /* [4] */
        unsigned int phy_tmds_srst_req   : 1;  /* [5] */
        unsigned int tmds_clk_div        : 3;  /* [8..6] */
        unsigned int reserved_1          : 23; /* [31..9] */
    } bits;
    unsigned int u32;
} r_peri_crg69;

typedef struct {
    volatile unsigned int reserved_0[68]; /* 0x00~0x10c  */
    volatile r_peri_crg68 peri_crg68;     /* 0x110 */
    volatile r_peri_crg69 peri_crg69;     /* 0x114 */
} hdmi_reg_crg;

int hdmi_reg_crg_init(void);
int hdmi_reg_crg_deinit(void);
int reg_hdmi_crg_ssc_in_cken_set(unsigned int ssc_in_cken);
int reg_hdmi_crg_ssc_bypass_cken_set(unsigned int ssc_bypass_cken);
int reg_hdmi_crg_hdmitx_ctrl_osc_24m_cken_set(unsigned int hdmitx_ctrl_osc_24m_cken);
int reg_hdmi_crg_hdmitx_ctrl_cec_cken_set(unsigned int hdmitx_ctrl_cec_cken);
int reg_hdmi_crg_hdmitx_ctrl_os_cken_set(unsigned int hdmitx_ctrl_os_cken);
int reg_hdmi_crg_hdmitx_ctrl_as_cken_set(unsigned int hdmitx_ctrl_as_cken);
int reg_hdmi_crg_hdmitx_ctrl_bus_srst_req_set(unsigned int hdmitx_ctrl_bus_srst_req);
int reg_hdmi_crg_hdmitx_ctrl_srst_req_set(unsigned int hdmitx_ctrl_srst_req);
int reg_hdmi_crg_hdmitx_ctrl_cec_srst_req_set(unsigned int hdmitx_ctrl_cec_srst_req);
int reg_hdmi_crg_hdmitx_ssc_srst_req_set(unsigned int hdmitx_ssc_srst_req);
int reg_hdmi_crg_ssc_clk_div_set(unsigned int ssc_clk_div);
int reg_hdmi_crg_hdmitx_pxl_cken_set(unsigned int hdmitx_pxl_cken);
int reg_hdmi_crg_phy_tmds_cken_set(unsigned int phy_tmds_cken);
int reg_hdmi_crg_hdmitx_phy_srst_req_set(unsigned int hdmitx_phy_srst_req);
int reg_hdmi_crg_hdmitx_phy_srst_req_get(hi_void);
int reg_hdmi_crg_phy_tmds_srst_req_set(unsigned int phy_tmds_srst_req);
int reg_hdmi_crg_phy_tmds_srst_req_get(hi_void);
int reg_hdmi_crg_hdmitx_phy_srst_req_get(hi_void);
int reg_hdmi_crg_tmds_clk_div_set(unsigned int tmds_clk_div);
#endif

