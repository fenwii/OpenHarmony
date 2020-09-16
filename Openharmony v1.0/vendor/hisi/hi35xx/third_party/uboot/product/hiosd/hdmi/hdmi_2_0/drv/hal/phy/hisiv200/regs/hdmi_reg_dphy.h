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

#define PR_OFFSET 0x20000

typedef union {
    struct {
        unsigned int stb_cs_en : 16; /* [15:0] */
        unsigned int rsv_2     : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} phy_csen;

typedef union {
    struct {
        unsigned int stb_wen : 1;  /* [0] */
        unsigned int rsv_3   : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} phy_wr;

typedef union {
    struct {
        unsigned int reset  : 1;  /* [0] */
        unsigned int rsv_4  : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} resetn;

typedef union {
    struct {
        unsigned int stb_addr : 4;  /* [3:0] */
        unsigned int rsv_5    : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} phy_addr;

typedef union {
    struct {
        unsigned int stb_wdata : 8;  /* [7:0] */
        unsigned int rsv_6     : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} phy_wdata;

typedef union {
    struct {
        unsigned int stb_rdata : 8;  /* [7:0] */
        unsigned int rsv_7     : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} phy_rdata;

typedef union {
    struct {
        unsigned int src_lock_val      : 8;  /* [7:0] */
        unsigned int src_lock_cnt      : 8;  /* [15:8] */
        unsigned int src_enable        : 1;  /* [16] */
        unsigned int fdsrcparam_unused : 3;  /* [19:17] */
        unsigned int rsv_13            : 12; /* [31:20] */
    } bits;
    unsigned int u32;
} fd_src_param;

typedef union {
    struct {
        unsigned int src_cnt_opt        : 3;  /* [2:0] */
        unsigned int fdsrcfreq_unused_1 : 1;  /* [3] */
        unsigned int src_freq_opt       : 2;  /* [5:4] */
        unsigned int fdsrcfreq_unused_2 : 2;  /* [7:6] */
        unsigned int src_freq_ext       : 16; /* [23:8] */
        unsigned int rsv_14             : 8;  /* [31:24] */
    } bits;
    unsigned int u32;
} fdsrcfreq;

typedef union {
    struct {
        unsigned int src_det_stat : 4;  /* [3:0] */
        unsigned int src_cnt_out  : 20; /* [23:4] */
        unsigned int rsv_15       : 8;  /* [31:24] */
    } bits;
    unsigned int u32;
} fdsrcres;

typedef union {
    struct {
        unsigned int i_enable      : 1;  /* [0] */
        unsigned int i_run         : 1;  /* [1] */
        unsigned int ctset0_unused : 2;  /* [3:2] */
        unsigned int rsv_16        : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} ctset0;

typedef union {
    struct {
        unsigned int i_mpll_fcon   : 10; /* [9:0] */
        unsigned int i_mpll_divn   : 3;  /* [12:10] */
        unsigned int i_mpll_ctlck  : 1;  /* [13] */
        unsigned int ctset1_unused : 18; /* [31:14] */
    } bits;
    unsigned int u32;
} ctset1;

typedef union {
    struct {
        unsigned int i_deci_cnt_len     : 8; /* [7:0] */
        unsigned int i_vco_st_wait_len  : 8; /* [15:8] */
        unsigned int i_vco_end_wait_len : 8; /* [23:16] */
        unsigned int i_ref_cnt_len      : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} fccntr0;

typedef union {
    struct {
        unsigned int i_ct_sel       : 1;  /* [0] */
        unsigned int i_clkdet_sel   : 1;  /* [1] */
        unsigned int i_ct_mode      : 2;  /* [3:2] */
        unsigned int fcopt_unused_1 : 4;  /* [7:4] */
        unsigned int i_ct_en        : 1;  /* [8] */
        unsigned int fcopt_unused_2 : 3;  /* [11:9] */
        unsigned int i_ct_idx_sel   : 1;  /* [12] */
        unsigned int i_deci_try_sel : 1;  /* [13] */
        unsigned int fcopt_unused   : 2;  /* [15:14] */
        unsigned int rsv_17         : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} fcopt;

typedef union {
    struct {
        unsigned int clk_ok          : 1;  /* [0] */
        unsigned int busy            : 1;  /* [1] */
        unsigned int done            : 1;  /* [2] */
        unsigned int error           : 1;  /* [3] */
        unsigned int divn            : 3;  /* [6:4] */
        unsigned int fcstat_unused_1 : 1;  /* [7] */
        unsigned int ref_clk_stat    : 1;  /* [8] */
        unsigned int pllvco_clk_stat : 1;  /* [9] */
        unsigned int fcstat_unused_2 : 2;  /* [11:10] */
        unsigned int confin_stat     : 6;  /* [17:12] */
        unsigned int fcstat_unused_3 : 2;  /* [19:18] */
        unsigned int fcon_init       : 10; /* [29:20] */
        unsigned int rsv_18          : 2;  /* [31:30] */
    } bits;
    unsigned int u32;
} fcstat;

typedef union {
    struct {
        unsigned int divn_h20             : 3;  /* [2:0] */
        unsigned int fcdstepset_unused    : 1;  /* [3] */
        unsigned int up_sampler_ratio_sel : 1;  /* [4] */
        unsigned int rsv_22               : 27; /* [31:5] */
    } bits;
    unsigned int u32;
} fcdstepset;

typedef union {
    struct {
        unsigned int i_ref_cnt : 16; /* [15:0] */
        unsigned int rsv_24    : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} fccntr1;

typedef union {
    struct {
        unsigned int contin_upd_en       : 1;  /* [0] */
        unsigned int contin_upd_opt      : 1;  /* [1] */
        unsigned int contin_upd_pol      : 1;  /* [2] */
        unsigned int fccontinset0_unused : 1;  /* [3] */
        unsigned int contin_upd_step     : 4;  /* [7:4] */
        unsigned int rsv_25              : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} fccontinset0;

typedef union {
    struct {
        unsigned int contin_upd_rate : 28; /* [27:0] */
        unsigned int contin_upd_time : 4;  /* [31:28] */
    } bits;
    unsigned int u32;
} fccontinset1;

typedef union {
    struct {
        unsigned int contin_upd_th_dn    : 10; /* [9:0] */
        unsigned int fccontinset2_unused : 2;  /* [11:10] */
        unsigned int contin_upd_th_up    : 10; /* [21:12] */
        unsigned int rsv_26              : 10; /* [31:22] */
    } bits;
    unsigned int u32;
} fccontinset2;

typedef union {
    struct {
        unsigned int init   : 1;  /* [0] */
        unsigned int ctrl   : 1;  /* [1] */
        unsigned int mod    : 1;  /* [2] */
        unsigned int sdm    : 1;  /* [3] */
        unsigned int rsv_27 : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} fdivset0;

typedef union {
    struct {
        unsigned int mod_len : 8;  /* [7:0] */
        unsigned int mod_t   : 8;  /* [15:8] */
        unsigned int mod_n   : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} fdivset3;

typedef union {
    struct {
        unsigned int mod_d  : 16; /* [15:0] */
        unsigned int rsv_29 : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} fdivset4;

typedef union {
    struct {
        unsigned int i_fdiv_in : 32; /* [31:0] */
    } bits;
    unsigned int u32;
} fdivstat1;

typedef union {
    struct {
        unsigned int i_manual_en       : 4; /* [3:0] */
        unsigned int i_divn            : 3; /* [6:4] */
        unsigned int fdivmanual_unused : 1; /* [7] */
        unsigned int i_mdiv            : 4; /* [11:8] */
        unsigned int i_ref_cnt_div     : 2; /* [13:12] */
        unsigned int i_dc_sel          : 2; /* [15:14] */
        unsigned int i_vic             : 8; /* [23:16] */
        unsigned int rsv_34            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} fdivmanual;

typedef union {
    struct {
        unsigned int t2_refclksel       : 1;  /* [0] */
        unsigned int t2_refclksel2      : 1;  /* [1] */
        unsigned int i_ref_clk_sel      : 1;  /* [2] */
        unsigned int refclksel_unused_1 : 1;  /* [3] */
        unsigned int t2_pixelclksel     : 1;  /* [4] */
        unsigned int refclksel_unused_2 : 1;  /* [5] */
        unsigned int pr_enc_val         : 2;  /* [7:6] */
        unsigned int rsv_35             : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} refclksel;

typedef union {
    struct {
        unsigned int fcg_en        : 1;  /* [0] */
        unsigned int fcg_dlf_en    : 1;  /* [1] */
        unsigned int fcg_dither_en : 1;  /* [2] */
        unsigned int fcg_lock_en   : 1;  /* [3] */
        unsigned int rsv_39        : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} fcgset;

typedef union {
    struct {
        unsigned int pr_en_h20         : 1;  /* [0] */
        unsigned int enable_h20        : 1;  /* [1] */
        unsigned int txfifoset0_unused : 6;  /* [7:2] */
        unsigned int rsv_46            : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} txfifoset0;

typedef union {
    struct {
        unsigned int ch_out_sel : 2;  /* [1:0] */
        unsigned int rsv_52     : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} txdataoutsel;

typedef union {
    struct {
        unsigned int reg_hdmi_mode_en : 1;  /* [0] */
        unsigned int rsv_53           : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} hdmi_mode;

typedef union {
    struct {
        unsigned int hsset   : 2;  /* [1:0] */
        unsigned int rsv_58  : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} hsset;

typedef union {
    struct {
        unsigned int fd_clk_sel  : 2;  /* [1:0] */
        unsigned int refclk_sel  : 2;  /* [3:2] */
        unsigned int ctman       : 2;  /* [5:4] */
        unsigned int modclk_sel  : 1;  /* [6] */
        unsigned int fdivclk_sel : 1;  /* [7] */
        unsigned int mod_div_val : 4;  /* [11:8] */
        unsigned int rsv_63      : 20; /* [31:12] */
    } bits;
    unsigned int u32;
} clkset;

typedef union {
    struct {
        unsigned int sw_reset_mod_clock          : 1;  /* [0] */
        unsigned int sw_reset_tmds_clock         : 1;  /* [1] */
        unsigned int sw_reset_mpll_clock         : 1;  /* [2] */
        unsigned int sw_reset_nco_clock          : 1;  /* [3] */
        unsigned int sw_reset_fd_clock           : 1;  /* [4] */
        unsigned int sw_reset_mod_and_mpll_clock : 1;  /* [5] */
        unsigned int sw_reset_mod_and_nco_clock  : 1;  /* [6] */
        unsigned int sw_reset_mod_and_fd_clock   : 1;  /* [7] */
        unsigned int sw_reset_hsfifo_clock       : 1;  /* [8] */
        unsigned int sw_reset_txfifo_clock       : 1;  /* [9] */
        unsigned int sw_reset_data_clock         : 1;  /* [10] */
        unsigned int sw_reset_hs_clock           : 1;  /* [11] */
        unsigned int sw_reset_pllref_clock       : 1;  /* [12] */
        unsigned int sw_reset_dac_clock          : 1;  /* [13] */
        unsigned int dac_clock_gat               : 1;  /* [14] */
        unsigned int up_sample_fifo_clock_swrst  : 1;  /* [15] */
        unsigned int sw_reset_frl_clock          : 1;  /* [16] */
        unsigned int swreset_unused              : 14; /* [30:17] */
        unsigned int global_reset                : 1;  /* [31] */
    } bits;
    unsigned int u32;
} swreset;

typedef union {
    struct {
        unsigned int req_length  : 2;  /* [1:0] */
        unsigned int stb_delay2  : 4;  /* [5:2] */
        unsigned int stb_delay1  : 4;  /* [9:6] */
        unsigned int stb_delay0  : 4;  /* [13:10] */
        unsigned int stb_acc_sel : 1;  /* [14] */
        unsigned int stb_cs_sel  : 1;  /* [15] */
        unsigned int rsv_65      : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} stbopt;

typedef struct {
    unsigned int          reserved_0[2];    /* 0-4 */
    volatile phy_csen     reg_phy_csen;     /* 8 */
    volatile phy_wr       reg_phy_wr;       /* C */
    volatile resetn       reg_resetn;       /* 10 */
    volatile phy_addr     reg_phy_addr;     /* 14 */
    volatile phy_wdata    reg_phy_wdata;    /* 18 */
    volatile phy_rdata    reg_phy_rdata;    /* 1C */
    unsigned int          reserved_1[4];    /* 20-2C */
    volatile fd_src_param reg_fd_src_param; /* 30 */
    volatile fdsrcfreq    reg_fdsrcfreq;    /* 34 */
    volatile fdsrcres     reg_fdsrcres;     /* 38 */
    volatile ctset0       reg_ctset0;       /* 3C */
    volatile ctset1       reg_ctset1;       /* 40 */
    unsigned int          reserved_2;       /* 44 */
    volatile fccntr0      reg_fccntr0;      /* 48 */
    volatile fcopt        reg_fcopt;        /* 4C */
    volatile fcstat       reg_fcstat;       /* 50 */
    unsigned int          reserved_3[3];    /* 54-5C */
    volatile fcdstepset   reg_fcdstepset;   /* 60 */
    unsigned int          reserved_4[3];    /* 64-6C */
    volatile fccntr1      reg_fccntr1;      /* 70 */
    volatile fccontinset0 reg_fccontinset0; /* 74 */
    volatile fccontinset1 reg_fccontinset1; /* 78 */
    volatile fccontinset2 reg_fccontinset2; /* 7C */
    unsigned int          reserved_6[4];    /* 80-8C */
    volatile fdivset0     reg_fdivset0;     /* 90 */
    unsigned int          reserved_7[2];    /* 94-98 */
    volatile fdivset3     reg_fdivset3;     /* 9C */
    volatile fdivset4     reg_fdivset4;     /* A0 */
    unsigned int          reserved_8[2];    /* A4-A8 */
    volatile fdivstat1    reg_fdivstat1;    /* AC */
    unsigned int          reserved_9[3];    /* B0-B8 */
    volatile fdivmanual   reg_fdivmanual;   /* BC */
    volatile refclksel    reg_refclksel;    /* C0 */
    unsigned int          reserved_10[23];  /* c4-11c */
    volatile fcgset       reg_fcgset;       /* 120 */
    unsigned int          reserved_11[59];  /* 124-20C */
    volatile txfifoset0   tx_fifo_set0;     /* 210 */
    unsigned int          reserved_12[6];   /* 214-228 */
    volatile txdataoutsel tx_data_out_sel;  /* 22C */
    volatile hdmi_mode    reg_hdmi_mode;    /* 230 */
    unsigned int          reserved_13[11];  /* 234-25c */
    volatile hsset        reg_hsset;        /* 260 */
    unsigned int          reserved_14[42];  /* 264-308 */
    volatile clkset       reg_clkset;       /* 30C */
    volatile swreset      reg_swreset;      /* 310 */
    unsigned int          reserved_15[251]; /* 314-6FC */
    volatile stbopt       reg_stbopt;       /* 700 */
    unsigned int          reserved_16[2];   /* 704-408 */
} hdmitx21_dphy_regs_type;

hi_s32 hdmi_hdmitx_phy_reg_init(hi_void);
hi_s32 hdmi_hdmitx_phy_reg_deinit(hi_void);
int hdmi_phy_csen_stb_cs_en_set(unsigned int stb_cs_en);
int hdmi_phy_wr_stb_wen_set(unsigned int stb_wen);
int hdmi_resetn_resetn_set(unsigned int resetn);
int hdmi_resetn_resetn_get(hi_void);
int hdmi_phy_addr_stb_addr_set(unsigned int stb_addr);
int hdmi_phy_wdata_stb_wdata_set(unsigned int stb_wdata);
int hdmi_phy_rdata_stb_rdata_get(hi_void);
int hdmi_fdsrcparam_src_lock_val_set(unsigned int src_lock_val);
int hdmi_fdsrcparam_src_lock_cnt_set(unsigned int src_lock_cnt);
int hdmi_fdsrcparam_src_enable_set(unsigned int src_enable);
int hdmi_fdsrcfreq_src_cnt_opt_set(unsigned int src_cnt_opt);
int hdmi_fdsrcfreq_unused_1_set(unsigned int fdsrcfreq_unused_1);
int hdmi_fdsrcfreq_src_freq_opt_set(unsigned int src_freq_opt);
int hdmi_fdsrcfreq_unused_2_set(unsigned int fdsrcfreq_unused_2);
int hdmi_fdsrcfreq_src_freq_ext_set(unsigned int src_freq_ext);
int hdmi_fdsrcres_src_det_stat_get(hi_void);
int hdmi_fdsrcres_src_cnt_out_get(hi_void);
int hdmi_ctset0_i_enable_set(unsigned int enable);
int hdmi_ctset0_i_run_set(unsigned int run);
int hdmi_ctset0_unused_set(unsigned int ctset0_unused);
int hdmi_fccntr0_i_vco_st_wait_len_set(unsigned int vco_st_wait_len);
int hdmi_fccntr0_i_vco_end_wait_len_set(unsigned int vco_end_wait_len);
int hdmi_fccntr0_i_ref_cnt_len_set(unsigned int ref_cnt_len);
int hdmi_fcopt_i_ct_sel_set(unsigned int ct_sel);
int hdmi_fcopt_i_clkdet_sel_set(unsigned int clkdet_sel);
int hdmi_fcopt_i_ct_mode_set(unsigned int ct_mode);
int hdmi_fcopt_unused_1_set(unsigned int fcopt_unused_1);
int hdmi_fcopt_i_ct_en_set(unsigned int ct_en);
int hdmi_fcopt_unused_2_set(unsigned int fcopt_unused_2);
int hdmi_fcopt_i_ct_idx_sel_set(unsigned int ct_idx_sel);
int hdmi_fcopt_unused_set(unsigned int fcopt_unused);
int hdmi_fcstat_busy_get(hi_void);
int hdmi_fcdstepset_p_divn_h20_set(unsigned int divn_h20);
int hdmi_fcdstepset_up_sampler_ratio_sel_set(unsigned int sampler_ratio_sel);
int hdmi_fccntr1_i_ref_cnt_set(unsigned int ref_cnt);
int hdmi_fccontinset0_p_contin_upd_en_set(unsigned int contin_upd_en);
int hdmi_fccontinset0_p_contin_upd_opt_set(unsigned int contin_upd_opt);
int hdmi_fccontinset0_p_contin_upd_pol_set(unsigned int contin_upd_pol);
int hdmi_fccontinset0_p_contin_upd_step_set(unsigned int contin_upd_step);
int hdmi_fccontinset1_p_contin_upd_rate_set(unsigned int contin_upd_rate);
int hdmi_fccontinset1_p_contin_upd_time_set(unsigned int contin_upd_time);
int hdmi_fccontinset2_p_contin_upd_th_dn_set(unsigned int contin_upd_th_dn);
int hdmi_fccontinset2_unused_set(unsigned int fccontinset2_unused);
int hdmi_fccontinset2_p_contin_upd_th_up_set(unsigned int contin_upd_th_up);
int hdmi_fdivset0_init_set(unsigned int init);
int hdmi_fdivset0_en_ctrl_set(unsigned int ctrl);
int hdmi_fdivset0_en_ctrl_get(hi_void);
int hdmi_fdivset0_en_mod_set(unsigned int mod);
int hdmi_fdivset0_en_mod_get(hi_void);
int hdmi_fdivset0_en_sdm_set(unsigned int sdm);
int hdmi_fdivset0_en_sdm_get(hi_void);
int hdmi_fdivset3_mod_len_set(unsigned int mod_len);
int hdmi_fdivset3_mod_t_set(unsigned int mod_t);
int hdmi_fdivset3_mod_n_set(unsigned int mod_n);
int hdmi_fdivset4_mod_d_set(unsigned int mod_d);
int hdmi_fdivstat1_i_fdiv_in_set(unsigned int fdiv_in);
int hdmi_fdivmanual_i_manual_en_set(unsigned int manual_en);
int hdmi_fdivmanual_i_mdiv_set(unsigned int mdiv);
int hdmi_refclksel_i_ref_clk_sel_set(unsigned int ref_clk_sel);
int hdmi_txfifoset0_p_pr_en_h20_set(unsigned int pr_en_h20);
int hdmi_txfifoset0_p_enable_h20_set(unsigned int enable_h20);
int hdmi_txdataoutsel_p_ch_out_sel_set(unsigned int ch_out_sel);
int hdmi_hsset_p_hsset_set(unsigned int hsset);
int hdmi_clkset_p_fd_clk_sel_set(unsigned int fd_clk_sel);
int hdmi_clkset_p_refclk_sel_set(unsigned int refclk_sel);
int hdmi_clkset_p_ctman_set(unsigned int ctman);
int hdmi_clkset_p_modclk_sel_set(unsigned int modclk_sel);
int hdmi_clkset_p_fdivclk_sel_set(unsigned int fdivclk_sel);
int hdmi_clkset_mod_div_val_set(unsigned int mod_div_val);
int hdmi_swreset_dac_clock_gat_set(unsigned int dac_clock_gat);
int hdmi_swreset_unused_set(unsigned int swreset_unused);
int hdmi_swreset_global_reset_set(unsigned int global_reset);
int hdmi_swreset_sw_reset_mod_clock_set(unsigned int sw_reset_mod_clock);
int hdmi_swreset_sw_reset_tmds_clock_set(unsigned int sw_reset_tmds_clock);
int hdmi_swreset_sw_reset_mpll_clock_set(unsigned int sw_reset_mpll_clock);
int hdmi_swreset_sw_reset_nco_clock_set(unsigned int sw_reset_nco_clock);
int hdmi_swreset_sw_reset_fd_clock_set(unsigned int sw_reset_fd_clock);
int hdmi_swreset_sw_reset_mod_and_mpll_clock_set(unsigned int sw_reset_mod_and_mpll_clock);
int hdmi_swreset_sw_reset_mod_and_nco_clock_set(unsigned int sw_reset_mod_and_nco_clock);
int hdmi_swreset_sw_reset_mod_and_fd_clock_set(unsigned int sw_reset_mod_and_fd_clock);
int hdmi_swreset_sw_reset_hsfifo_clock_set(unsigned int sw_reset_hsfifo_clock);
int hdmi_swreset_sw_reset_txfifo_clock_set(unsigned int sw_reset_txfifo_clock);
int hdmi_swreset_sw_reset_data_clock_set(unsigned int sw_reset_data_clock);
int hdmi_swreset_sw_reset_hs_clock_set(unsigned int sw_reset_hs_clock);
int hdmi_swreset_sw_reset_pllref_clock_set(unsigned int sw_reset_pllref_clock);
int hdmi_swreset_sw_reset_dac_clock_set(unsigned int sw_reset_dac_clock);
int hdmi_swreset_up_sample_fifo_clock_swrst_set(unsigned int sample_fifo_clock_swrst);
int hdmi_fccontinset0_unused_set(unsigned int fccontinset0_unused);
int hdmi_ctset1_i_mpll_fcon_set(unsigned int mpll_fcon);
int hdmi_ctset1_i_mpll_ctlck_set(unsigned int mpll_ctlck);
int hdmi_ctset1_ctset1_unused_set(unsigned int ctset1_unused);
int hdmi_fcdstepset_unused_set(unsigned int fcdstepset_unused);
int hdmi_stbopt_req_length_set(unsigned int req_length);
int hdmi_stbopt_stb_cs_sel_set(unsigned int stb_cs_sel);
int hdmi_fdsrcparam_unused_set(unsigned int fdsrcparam_unused);
int hdmi_fcgset_p_fcg_en_set(unsigned int fcg_en);
int hdmi_fcgset_p_fcg_dlf_en_set(unsigned int fcg_dlf_en);
int hdmi_fcgset_p_fcg_dither_en_set(unsigned int fcg_dither_en);
int hdmi_fcgset_p_fcg_lock_en_set(unsigned int fcg_lock_en);
int hdmi_txfifoset0_unused_set(unsigned int txfifoset0_unused);
int hdmi_hdmi_mode_reg_hdmi_mode_en_set(unsigned int reg_hdmi_mode_en);
int hdmi_swreset_sw_reset_frl_clock_set(unsigned int sw_reset_frl_clock);
int hdmi_stbopt_stb_delay2_set(unsigned int stb_delay2);
int hdmi_stbopt_stb_delay1_set(unsigned int stb_delay1);
int hdmi_stbopt_stb_delay0_set(unsigned int stb_delay0);
int hdmi_stbopt_stb_acc_sel_set(unsigned int stb_acc_sel);
int hdmi_fcstat_clk_ok_get(hi_void);
int hdmi_fcstat_done_get(hi_void);
int hdmi_fcstat_error_get(hi_void);

#endif /* __TX_DPHY_REG_C_UNION_DEFINE_H__ */

