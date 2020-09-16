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

#ifndef __HDMI_REG_DPHY_H__
#define __HDMI_REG_DPHY_H__

#include "hi_type.h"

typedef union {
    struct {
        unsigned int reg_set               : 24; /* [23:0] */
        unsigned int reg_set_load          : 1;  /* [24] */
        unsigned int reg_sscfifo_tune_en   : 1;  /* [25] */
        unsigned int reg_sscfifo_depth_clr : 1;  /* [26] */
        unsigned int reg_deep_color        : 2;  /* [28:27] */
        unsigned int reg_ssc_mode          : 1;  /* [29] */
        unsigned int reg_pllfbmash111_en   : 1;  /* [30] */
        unsigned int reg_sscin_bypass_en   : 1;  /* [31] */
    } bits;
    unsigned int u32;
} hdmitx_inssc_set;

typedef union {
    struct {
        unsigned int reg_dphy_srst_req : 1;  /* [0] */
        unsigned int rsv_0             : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} hdmitx_dphy_rst;

typedef union {
    struct {
        unsigned int reg_txafifo_status_rst : 1;  /* [0] */
        unsigned int reg_txafifo_rst        : 1;  /* [1] */
        unsigned int reg_aphy_data_ch0_sel  : 1;  /* [2] */
        unsigned int reg_aphy_data_ch1_sel  : 1;  /* [3] */
        unsigned int reg_aphy_data_ch2_sel  : 1;  /* [4] */
        unsigned int txafifo_aful_status    : 1;  /* [5] */
        unsigned int txafifo_full_status    : 1;  /* [6] */
        unsigned int txafifo_aempt_status   : 1;  /* [7] */
        unsigned int txafifo_empt_status    : 1;  /* [8] */
        unsigned int reg_aphy_data_clk_h    : 10; /* [18:9] */
        unsigned int rsv_12                 : 13; /* [31:19] */
    } bits;
    unsigned int u32;
} hdmitx_afifo_data_sel;

typedef union {
    struct {
        unsigned int reg_aphy_data_clk_l : 30; /* [29:0] */
        unsigned int rsv_13              : 2;  /* [31:30] */
    } bits;
    unsigned int u32;
} hdmitx_afifo_clk;

typedef union {
    struct {
        unsigned int reg_gc_pd         : 4; /* [3:0] */
        unsigned int reg_gc_pd_bist    : 1; /* [4] */
        unsigned int reg_gc_pd_de      : 4; /* [8:5] */
        unsigned int reg_gc_pd_ldo     : 2; /* [10:9] */
        unsigned int reg_gc_pd_rterm   : 8; /* [18:11] */
        unsigned int reg_gc_pd_rxsense : 1; /* [19] */
        unsigned int reg_gc_txpll_pd   : 1; /* [20] */
        unsigned int reg_divsel        : 2; /* [22:21] */
        unsigned int rsv_17            : 9; /* [31:23] */
    } bits;
    unsigned int u32;
} aphy_top_pd;

typedef union {
    struct {
        unsigned int reg_isel_main_clk    : 6; /* [5:0] */
        unsigned int reg_isel_main_d0     : 6; /* [11:6] */
        unsigned int reg_isel_main_d1     : 6; /* [17:12] */
        unsigned int reg_isel_main_d2     : 6; /* [23:18] */
        unsigned int reg_isel_main_de_clk : 6; /* [29:24] */
        unsigned int rsv_18               : 2; /* [31:30] */
    } bits;
    unsigned int u32;
} aphy_driver_imain;

typedef union {
    struct {
        unsigned int reg_isel_main_de_d0 : 6; /* [5:0] */
        unsigned int reg_isel_main_de_d1 : 6; /* [11:6] */
        unsigned int reg_isel_main_de_d2 : 6; /* [17:12] */
        unsigned int reg_isel_pre_clk    : 6; /* [23:18] */
        unsigned int reg_isel_pre_d0     : 6; /* [29:24] */
        unsigned int rsv_19              : 2; /* [31:30] */
    } bits;
    unsigned int u32;
} aphy_driver_ipre;

typedef union {
    struct {
        unsigned int reg_isel_pre_d1     : 6; /* [5:0] */
        unsigned int reg_isel_pre_d2     : 6; /* [11:6] */
        unsigned int reg_isel_pre_de_clk : 6; /* [17:12] */
        unsigned int reg_isel_pre_de_d0  : 6; /* [23:18] */
        unsigned int reg_isel_pre_de_d1  : 6; /* [29:24] */
        unsigned int rsv_20              : 2; /* [31:30] */
    } bits;
    unsigned int u32;
} aphy_driver_iprede;

typedef union {
    struct {
        unsigned int reg_isel_pre_de_d2  : 6; /* [5:0] */
        unsigned int reg_rsel_pre_clk    : 3; /* [8:6] */
        unsigned int reg_rsel_pre_d0     : 3; /* [11:9] */
        unsigned int reg_rsel_pre_d1     : 3; /* [14:12] */
        unsigned int reg_rsel_pre_d2     : 3; /* [17:15] */
        unsigned int reg_rsel_pre_de_clk : 3; /* [20:18] */
        unsigned int reg_rsel_pre_de_d0  : 3; /* [23:21] */
        unsigned int reg_rsel_pre_de_d1  : 3; /* [26:24] */
        unsigned int reg_rsel_pre_de_d2  : 3; /* [29:27] */
        unsigned int rsv_21              : 2; /* [31:30] */
    } bits;
    unsigned int u32;
} aphy_driver_rpre;

typedef union {
    struct {
        unsigned int reg_rt_clk : 8; /* [7:0] */
        unsigned int reg_rt_d0  : 8; /* [15:8] */
        unsigned int reg_rt_d1  : 8; /* [23:16] */
        unsigned int reg_rt_d2  : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} aphy_rterm_ctrl;

typedef union {
    struct {
        unsigned int reg_test    : 16; /* [15:0] */
        unsigned int reg_test_dc : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} aphy_test_ctrl;

typedef union {
    struct {
        unsigned int reg_txpll_clkin_sel         : 2;  /* [1:0] */
        unsigned int reg_txpll_divsel_in         : 3;  /* [4:2] */
        unsigned int reg_txpll_divsel_loop       : 7;  /* [11:5] */
        unsigned int reg_txpll_divsel_post       : 2;  /* [13:12] */
        unsigned int reg_txpll_icp_ictrl         : 4;  /* [17:14] */
        unsigned int reg_gc_txpll_en_ref_fb_div2 : 1;  /* [18] */
        unsigned int reg_gc_txpll_en_sscdiv      : 1;  /* [19] */
        unsigned int rsv_23                      : 12; /* [31:20] */
    } bits;
    unsigned int u32;
} aphy_txpll_ctrl;

typedef union {
    struct {
        unsigned int reg_txpll_test : 20; /* [19:0] */
        unsigned int rsv_24         : 12; /* [31:20] */
    } bits;
    unsigned int u32;
} aphy_txpll_test;

typedef union {
    struct {
        unsigned int reg_set_fb               : 24; /* [23:0] */
        unsigned int reg_set_load_fb          : 1;  /* [24] */
        unsigned int reg_sscfifo_tune_en_fb   : 1;  /* [25] */
        unsigned int reg_sscfifo_depth_clr_fb : 1;  /* [26] */
        unsigned int reg_ssc_mode_fb          : 1;  /* [27] */
        unsigned int rsv_27                   : 4;  /* [31:28] */
    } bits;
    unsigned int u32;
} hdmitx_fbssc_set;

typedef union {
    struct {
        unsigned int reg_step_fb  : 10; /* [9:0] */
        unsigned int reg_span_fb  : 14; /* [23:10] */
        unsigned int reg_testd_fb : 8;  /* [31:24] */
    } bits;
    unsigned int u32;
} hdmitx_fbssc_step;

typedef struct {
    volatile hdmitx_inssc_set      inssc_set;       /* 0 */
    volatile unsigned int          reserved_0[3];   /* 4~c */
    volatile hdmitx_dphy_rst       dphy_rst;        /* 0x10 */
    volatile unsigned int          reserved_1[15];  /* 0x14~0x4c */
    volatile hdmitx_afifo_data_sel afifo_data_sel;  /* 50 */
    volatile hdmitx_afifo_clk      afifo_clk;       /* 54 */
    volatile unsigned int          reserved_2[3];   /* 0x58~0x60 */
    volatile aphy_top_pd           top_pd;          /* 64 */
    volatile aphy_driver_imain     driver_i_main;   /* 68 */
    volatile aphy_driver_ipre      driver_i_pre;    /* 6C */
    volatile aphy_driver_iprede    driver_i_pre_de; /* 70 */
    volatile aphy_driver_rpre      driver_r_pre;    /* 74 */
    volatile aphy_rterm_ctrl       rterm_ctrl;      /* 78 */
    volatile unsigned int          reserved_3;      /* 0x7C */
    volatile aphy_test_ctrl        test_ctrl_aphy;  /* 80 */
    volatile unsigned int          reserved_4[2];   /* 84~88 */
    volatile aphy_txpll_ctrl       txpll_ctrl;      /* 8C */
    volatile aphy_txpll_test       txpll_test;      /* 90 */
    volatile unsigned int          reserved_5[7];   /* 0x94~0xac */
    volatile hdmitx_fbssc_set      fbssc_set;       /* B0 */
    volatile unsigned int          reserved_6[1];   /* 0xB4 */
    volatile hdmitx_fbssc_step     fbssc_step;      /* B8 */
} hdmi2tx_dphy_regs;

hi_s32 hdmi_hdmitx_phy_reg_init(hi_void);
hi_void hdmi_hdmitx_phy_reg_deinit(hi_void);
hi_void hdmi_hdmitx_inssc_set_reg_pllfbmash111_en_set(hi_u32 reg_pllfbmash111_en);
hi_void hdmi_hdmitx_inssc_set_reg_sscin_bypass_en_set(hi_u32 reg_sscin_bypass_en);
hi_void hdmi_hdmitx_dphy_rst_reg_rstset(hi_u32 reg_rst);
hi_void hdmi_hdmitx_afifo_data_sel_reg_aphy_data_clk_h_set(hi_u32 reg_aphy_data_clk_h);
hi_void hdmi_hdmitx_afifo_clk_reg_aphy_data_clk_l_set(hi_u32 reg_aphy_data_clk_l);
hi_void hdmi_aphy_top_pd_reg_gc_pd_set(hi_u32 reg_gc_pd);
hi_s32 hdmi_aphy_top_pd_reg_gc_pd_get(hi_void);
hi_void hdmi_aphy_top_pd_reg_gc_pd_bist_set(hi_u32 reg_gc_pd_bist);
hi_s32 hdmi_aphy_top_pd_reg_gc_pd_bist_get(hi_void);
hi_void hdmi_aphy_top_pd_reg_gc_pd_de_set(hi_u32 reg_gc_pd_de);
hi_s32 hdmi_aphy_top_pd_reg_gc_pd_de_get(hi_void);
hi_void hdmi_aphy_top_pd_reg_gc_pd_ldo_set(hi_u32 reg_gc_pd_ldo);
hi_s32 hdmi_aphy_top_pd_reg_gc_pd_ldo_get(hi_void);
hi_s32 hdmi_aphy_top_pd_reg_gc_pd_rterm_get(hi_void);
hi_void hdmi_aphy_top_pd_reg_gc_pd_rterm_set(hi_u32 reg_gc_pd_rterm);
hi_void hdmi_aphy_top_pd_reg_gc_pd_rxsense_set(hi_u32 reg_gc_pd_rxsense);
hi_s32 hdmi_aphy_top_pd_reg_gc_pd_rxsense_get(hi_void);
hi_void hdmi_aphy_top_pd_reg_gc_txpll_pd_set(hi_u32 reg_gc_txpll_pd);
hi_s32 hdmi_aphy_top_pd_reg_gc_txpll_pd_get(hi_void);
hi_void hdmi_aphy_top_pd_reg_divsel_set(hi_u32 reg_divsel);
hi_void hdmi_aphy_driver_imain_reg_isel_main_clk_set(hi_u32 reg_isel_main_clk);
hi_void hdmi_aphy_driver_imain_reg_isel_main_d0_set(hi_u32 reg_isel_main_d0);
hi_void hdmi_aphy_driver_imain_reg_isel_main_d1_set(hi_u32 reg_isel_main_d1);
hi_void hdmi_aphy_driver_imain_reg_isel_main_d2_set(hi_u32 reg_isel_main_d2);
hi_void hdmi_aphy_driver_imain_reg_isel_main_de_clk_set(hi_u32 reg_isel_main_de_clk);
hi_s32 hdmi_aphy_driver_imain_reg_isel_main_de_clk_get(hi_void);
hi_void hdmi_aphy_driver_ipre_reg_isel_main_de_d0_set(hi_u32 reg_isel_main_de_d0);
hi_s32 hdmi_aphy_driver_ipre_reg_isel_main_de_d0_get(hi_void);
hi_void hdmi_aphy_driver_ipre_reg_isel_main_de_d1_set(hi_u32 reg_isel_main_de_d1);
hi_s32 hdmi_aphy_driver_ipre_reg_isel_main_de_d1_get(hi_void);
hi_void hdmi_aphy_driver_ipre_reg_isel_main_de_d2_set(hi_u32 reg_isel_main_de_d2);
hi_s32 hdmi_aphy_driver_ipre_reg_isel_main_de_d2_get(hi_void);
hi_void hdmi_aphy_driver_ipre_reg_isel_pre_clk_set(hi_u32 reg_isel_pre_clk);
hi_void hdmi_aphy_driver_ipre_reg_isel_pre_d0_set(hi_u32 reg_isel_pre_d0);
hi_void hdmi_aphy_driver_iprede_reg_isel_pre_d1_set(hi_u32 reg_isel_pre_d1);
hi_void hdmi_aphy_driver_iprede_reg_isel_pre_d2_set(hi_u32 reg_isel_pre_d2);
hi_void hdmi_aphy_driver_iprede_reg_isel_pre_de_clk_set(hi_u32 reg_isel_pre_de_clk);
hi_void hdmi_aphy_driver_iprede_reg_isel_pre_de_d0_set(hi_u32 reg_isel_pre_de_d0);
hi_void hdmi_aphy_driver_iprede_reg_isel_pre_de_d1_set(hi_u32 reg_isel_pre_de_d1);
hi_void hdmi_aphy_driver_rpre_reg_isel_pre_de_d2_set(hi_u32 reg_isel_pre_de_d2);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_clk_set(hi_u32 reg_rsel_pre_clk);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_d0_set(hi_u32 reg_rsel_pre_d0);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_d1_set(hi_u32 reg_rsel_pre_d1);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_d2_set(hi_u32 reg_rsel_pre_d2);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_de_clk_set(hi_u32 reg_rsel_pre_de_clk);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_de_d0_set(hi_u32 reg_rsel_pre_de_d0);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_de_d1_set(hi_u32 reg_rsel_pre_de_d1);
hi_void hdmi_aphy_driver_rpre_reg_rsel_pre_de_d2_set(hi_u32 reg_rsel_pre_de_d2);
hi_void hdmi_aphy_rterm_ctrl_reg_rt_clk_set(hi_u32 reg_rt_clk);
hi_void hdmi_aphy_rterm_ctrl_reg_rt_d0_set(hi_u32 reg_rt_d0);
hi_void hdmi_aphy_rterm_ctrl_reg_rt_d1_set(hi_u32 reg_rt_d1);
hi_void hdmi_aphy_rterm_ctrl_reg_rt_d2_set(hi_u32 reg_rt_d2);
hi_void hdmi_aphy_txpll_ctrl_reg_txpll_divsel_loop_set(hi_u32 reg_txpll_divsel_loop);
hi_void hdmi_aphy_txpll_ctrl_reg_txpll_icp_ictrl_set(hi_u32 reg_txpll_icp_ictrl);
hi_void hdmi_aphy_txpll_ctrl_reg_gc_txpll_en_sscdiv_set(hi_u32 reg_gc_txpll_en_sscdiv);
hi_void hdmi_aphy_txpll_test_reg_txpll_test_set(hi_u32 reg_txpll_test);
hi_void hdmi_hdmitx_fbssc_set_reg_set_fb_set(hi_u32 reg_set_fb);
hi_void hdmi_hdmitx_fbssc_set_reg_set_load_fb_set(hi_u32 reg_set_load_fb);
hi_void hdmi_hdmitx_fbssc_set_reg_ssc_mode_fb_set(hi_u32 reg_ssc_mode_fb);
hi_void hdmi_hdmitx_fbssc_step_reg_step_fb_set(hi_u32 reg_step_fb);
hi_s32 hdmi_hdmitx_fbssc_step_reg_step_fb_get(hi_void);
hi_void hdmi_hdmitx_fbssc_step_reg_span_fb_set(hi_u32 reg_span_fb);
hi_s32 hdmi_hdmitx_fbssc_step_reg_span_fb_get(hi_void);
hi_s32 hdmi_reg_test_set(hi_u32 reg_test);
#endif /* __HDMI_REG_DPHY_H__ */

