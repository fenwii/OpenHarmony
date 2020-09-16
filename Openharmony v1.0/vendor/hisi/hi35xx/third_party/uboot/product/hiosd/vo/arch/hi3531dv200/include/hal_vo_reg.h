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

#ifndef __HAL_VO_REG_H__
#define __HAL_VO_REG_H__

#include "hal_vo_reg_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

/* define the union reg_voctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 23; /* [22..0]  */
        unsigned int g3_ck_gt_en : 1 ; /* [23]  */
        unsigned int v2_ck_gt_en : 1; /* [24]  */
        unsigned int wbc_dhd_ck_gt_en : 1; /* [25]  */
        unsigned int g1_ck_gt_en : 1; /* [26]  */
        unsigned int g0_ck_gt_en : 1; /* [27]  */
        unsigned int v1_ck_gt_en : 1; /* [28]  */
        unsigned int v0_ck_gt_en : 1; /* [29]  */
        unsigned int chk_sum_en : 1; /* [30]  */
        unsigned int vo_ck_gt_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_voctrl;

/* define the union reg_vointsta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_int : 1; /* [0]  */
        unsigned int dhd0vtthd2_int : 1; /* [1]  */
        unsigned int dhd0vtthd3_int : 1; /* [2]  */
        unsigned int dhd0uf_int : 1; /* [3]  */
        unsigned int dhd1vtthd1_int : 1; /* [4]  */
        unsigned int dhd1vtthd2_int : 1; /* [5]  */
        unsigned int dhd1vtthd3_int : 1; /* [6]  */
        unsigned int dhd1uf_int : 1; /* [7]  */
        unsigned int dsdvtthd1_int : 1; /* [8]  */
        unsigned int dsdvtthd2_int : 1; /* [9]  */
        unsigned int dsdvtthd3_int : 1; /* [10]  */
        unsigned int dsduf_int : 1; /* [11]  */
        unsigned int b0_err_int : 1; /* [12]  */
        unsigned int b1_err_int : 1; /* [13]  */
        unsigned int b2_err_int : 1; /* [14]  */
        unsigned int wbc_dhd_over_int : 1; /* [15]  */
        unsigned int vdac0_int : 1; /* [16]  */
        unsigned int vdac1_int : 1; /* [17]  */
        unsigned int vdac2_int : 1; /* [18]  */
        unsigned int vdac3_int : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vointsta;

/* define the union reg_vomskintsta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_clr : 1; /* [0]  */
        unsigned int dhd0vtthd2_clr : 1; /* [1]  */
        unsigned int dhd0vtthd3_clr : 1; /* [2]  */
        unsigned int dhd0uf_clr : 1; /* [3]  */
        unsigned int dhd1vtthd1_clr : 1; /* [4]  */
        unsigned int dhd1vtthd2_clr : 1; /* [5]  */
        unsigned int dhd1vtthd3_clr : 1; /* [6]  */
        unsigned int dhd1uf_clr : 1; /* [7]  */
        unsigned int dsdvtthd1_clr : 1; /* [8]  */
        unsigned int dsdvtthd2_clr : 1; /* [9]  */
        unsigned int dsdvtthd3_clr : 1; /* [10]  */
        unsigned int dsduf_clr : 1; /* [11]  */
        unsigned int b0_err_clr : 1; /* [12]  */
        unsigned int b1_err_clr : 1; /* [13]  */
        unsigned int b2_err_clr : 1; /* [14]  */
        unsigned int wbc_dhd_over_clr : 1; /* [15]  */
        unsigned int vdac0_clr : 1; /* [16]  */
        unsigned int vdac1_clr : 1; /* [17]  */
        unsigned int vdac2_clr : 1; /* [18]  */
        unsigned int vdac3_clr : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vomskintsta;

/* define the union reg_vointmsk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_intmask : 1; /* [0]  */
        unsigned int dhd0vtthd2_intmask : 1; /* [1]  */
        unsigned int dhd0vtthd3_intmask : 1; /* [2]  */
        unsigned int dhd0uf_intmask : 1; /* [3]  */
        unsigned int dhd1vtthd1_intmask : 1; /* [4]  */
        unsigned int dhd1vtthd2_intmask : 1; /* [5]  */
        unsigned int dhd1vtthd3_intmask : 1; /* [6]  */
        unsigned int dhd1uf_intmask : 1; /* [7]  */
        unsigned int dsdvtthd1_intmask : 1; /* [8]  */
        unsigned int dsdvtthd2_intmask : 1; /* [9]  */
        unsigned int dsdvtthd3_intmask : 1; /* [10]  */
        unsigned int dsduf_intmask : 1; /* [11]  */
        unsigned int b0_err_intmask : 1; /* [12]  */
        unsigned int b1_err_intmask : 1; /* [13]  */
        unsigned int b2_err_intmask : 1; /* [14]  */
        unsigned int wbc_dhd_over_intmask : 1; /* [15]  */
        unsigned int vdac0_intmask : 1; /* [16]  */
        unsigned int vdac1_intmask : 1; /* [17]  */
        unsigned int vdac2_intmask : 1; /* [18]  */
        unsigned int vdac3_intmask : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vointmsk;

/* define the union reg_vodebug */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rm_en_chn : 4; /* [3..0]  */
        unsigned int dhd0_ff_info : 2; /* [5..4]  */
        unsigned int dhd1_ff_info : 2; /* [7..6]  */
        unsigned int dsd0_ff_info : 2; /* [9..8]  */
        unsigned int bfm_vga_en : 1; /* [10]  */
        unsigned int bfm_cvbs_en : 1; /* [11]  */
        unsigned int bfm_lcd_en : 1; /* [12]  */
        unsigned int bfm_bt1120_en : 1; /* [13]  */
        unsigned int wbc2_ff_info : 2; /* [15..14]  */
        unsigned int wbc_mode : 4; /* [19..16]  */
        unsigned int node_num : 4; /* [23..20]  */
        unsigned int wbc_cmp_mode : 2; /* [25..24]  */
        unsigned int bfm_mode : 3; /* [28..26]  */
        unsigned int bfm_clk_sel : 3; /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vodebug;

/* define the union reg_vointsta1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_int : 1; /* [0]  */
        unsigned int dhd0vtthd2_int : 1; /* [1]  */
        unsigned int dhd0vtthd3_int : 1; /* [2]  */
        unsigned int dhd0uf_int : 1; /* [3]  */
        unsigned int dhd1vtthd1_int : 1; /* [4]  */
        unsigned int dhd1vtthd2_int : 1; /* [5]  */
        unsigned int dhd1vtthd3_int : 1; /* [6]  */
        unsigned int dhd1uf_int : 1; /* [7]  */
        unsigned int dsdvtthd1_int : 1; /* [8]  */
        unsigned int dsdvtthd2_int : 1; /* [9]  */
        unsigned int dsdvtthd3_int : 1; /* [10]  */
        unsigned int dsduf_int : 1; /* [11]  */
        unsigned int b0_err_int : 1; /* [12]  */
        unsigned int b1_err_int : 1; /* [13]  */
        unsigned int b2_err_int : 1; /* [14]  */
        unsigned int wbc_dhd_over_int : 1; /* [15]  */
        unsigned int vdac0_int : 1; /* [16]  */
        unsigned int vdac1_int : 1; /* [17]  */
        unsigned int vdac2_int : 1; /* [18]  */
        unsigned int vdac3_int : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vointsta1;

/* define the union reg_vomskintsta1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_clr : 1; /* [0]  */
        unsigned int dhd0vtthd2_clr : 1; /* [1]  */
        unsigned int dhd0vtthd3_clr : 1; /* [2]  */
        unsigned int dhd0uf_clr : 1; /* [3]  */
        unsigned int dhd1vtthd1_clr : 1; /* [4]  */
        unsigned int dhd1vtthd2_clr : 1; /* [5]  */
        unsigned int dhd1vtthd3_clr : 1; /* [6]  */
        unsigned int dhd1uf_clr : 1; /* [7]  */
        unsigned int dsdvtthd1_clr : 1; /* [8]  */
        unsigned int dsdvtthd2_clr : 1; /* [9]  */
        unsigned int dsdvtthd3_clr : 1; /* [10]  */
        unsigned int dsduf_clr : 1; /* [11]  */
        unsigned int b0_err_clr : 1; /* [12]  */
        unsigned int b1_err_clr : 1; /* [13]  */
        unsigned int b2_err_clr : 1; /* [14]  */
        unsigned int wbc_dhd_over_clr : 1; /* [15]  */
        unsigned int vdac0_clr : 1; /* [16]  */
        unsigned int vdac1_clr : 1; /* [17]  */
        unsigned int vdac2_clr : 1; /* [18]  */
        unsigned int vdac3_clr : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vomskintsta1;

/* define the union reg_vointmsk1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_intmask : 1; /* [0]  */
        unsigned int dhd0vtthd2_intmask : 1; /* [1]  */
        unsigned int dhd0vtthd3_intmask : 1; /* [2]  */
        unsigned int dhd0uf_intmask : 1; /* [3]  */
        unsigned int dhd1vtthd1_intmask : 1; /* [4]  */
        unsigned int dhd1vtthd2_intmask : 1; /* [5]  */
        unsigned int dhd1vtthd3_intmask : 1; /* [6]  */
        unsigned int dhd1uf_intmask : 1; /* [7]  */
        unsigned int dsdvtthd1_intmask : 1; /* [8]  */
        unsigned int dsdvtthd2_intmask : 1; /* [9]  */
        unsigned int dsdvtthd3_intmask : 1; /* [10]  */
        unsigned int dsduf_intmask : 1; /* [11]  */
        unsigned int b0_err_intmask : 1; /* [12]  */
        unsigned int b1_err_intmask : 1; /* [13]  */
        unsigned int b2_err_intmask : 1; /* [14]  */
        unsigned int wbc_dhd_over_intmask : 1; /* [15]  */
        unsigned int vdac0_intmask : 1; /* [16]  */
        unsigned int vdac1_intmask : 1; /* [17]  */
        unsigned int vdac2_intmask : 1; /* [18]  */
        unsigned int vdac3_intmask : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vointmsk1;

/* define the union reg_volowpower_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfs_ema : 3; /* [2..0]  */
        unsigned int rfs_emaw : 2; /* [4..3]  */
        unsigned int ret1n : 1; /* [5]  */
        unsigned int rft_emaa : 3; /* [8..6]  */
        unsigned int rft_emab : 3; /* [11..9]  */
        unsigned int rfs_colldisn : 1; /* [12]  */
        unsigned int rft_emasa : 1; /* [13]  */
        unsigned int    rftuhd_ema            : 3  ; /* [16..14]  */
        unsigned int    rftuhd_emaw           : 2  ; /* [18..17]  */
        unsigned int    rftuhd_emas           : 1  ; /* [19]  */
        unsigned int    rftuhd_emap           : 1  ; /* [20]  */
        unsigned int    rftuhd_stov           : 1  ; /* [21]  */
        unsigned int    rftuhd_stovab         : 1  ; /* [22]  */
        unsigned int    rfs_wabl              : 1  ; /* [23]  */
        unsigned int    rfs_wablm             : 2  ; /* [25..24]  */
        unsigned int    ras_ema               : 3  ; /* [28..26]  */
        unsigned int    ras_emaw              : 2  ; /* [30..29]  */
        unsigned int    ras_stov              : 1  ; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_volowpower_ctrl;

/* define the union reg_voufsta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_uf_sta : 1; /* [0]  */
        unsigned int v1_uf_sta : 1; /* [1]  */
        unsigned int reserved_0 : 1; /* [2]  */
        unsigned int v3_uf_sta : 1; /* [3]  */
        unsigned int reserved_1 : 4; /* [7..4]  */
        unsigned int g0_uf_sta : 1; /* [8]  */
        unsigned int g1_uf_sta : 1; /* [9]  */
        unsigned int g2_uf_sta : 1; /* [10]  */
        unsigned int g3_uf_sta : 1; /* [11]  */
        unsigned int g4_uf_sta : 1; /* [12]  */
        unsigned int reserved_2 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_voufsta;

/* define the union reg_voufclr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_uf_clr : 1; /* [0]  */
        unsigned int v1_uf_clr : 1; /* [1]  */
        unsigned int reserved_0 : 1; /* [2]  */
        unsigned int v3_uf_clr : 1; /* [3]  */
        unsigned int reserved_1 : 4; /* [7..4]  */
        unsigned int g0_uf_clr : 1; /* [8]  */
        unsigned int g1_uf_clr : 1; /* [9]  */
        unsigned int g2_uf_clr : 1; /* [10]  */
        unsigned int g3_uf_clr : 1; /* [11]  */
        unsigned int g4_uf_clr : 1; /* [12]  */
        unsigned int reserved_2 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_voufclr;

/* define the union reg_vointproc_tim */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vointproc_time : 24; /* [23..0]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vointproc_tim;

/* define the union reg_volowpower_ctrl1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rftf_rct : 2; /* [1..0]  */
        unsigned int rftf_kp : 3; /* [4..2]  */
        unsigned int rft_wtsel : 2; /* [6..5]  */
        unsigned int rft_rtsel : 2; /* [8..7]  */
        unsigned int rft_mtsel : 2; /* [10..9]  */
        unsigned int rasshds_wtsel : 2; /* [12..11]  */
        unsigned int rasshds_rtsel : 2; /* [14..13]  */
        unsigned int rasshdm_wtsel : 2; /* [16..15]  */
        unsigned int rasshdm_rtsel : 2; /* [18..17]  */
        unsigned int rashds_wtsel : 2; /* [20..19]  */
        unsigned int rashds_rtsel : 2; /* [22..21]  */
        unsigned int rashdm_wtsel : 2; /* [24..23]  */
        unsigned int rashdm_rtsel : 2; /* [26..25]  */
        unsigned int ras_wtsel : 2; /* [28..27]  */
        unsigned int ras_rtsel : 2; /* [30..29]  */
        unsigned int    ras_emas              : 1  ; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_volowpower_ctrl1;

/* define the union reg_vofpgadef */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_v_def : 1; /* [0]  */
        unsigned int hihdr_g_def : 1; /* [1]  */
        unsigned int hihdr_wd_def : 1; /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vofpgadef;

/* Define the union reg_volowpower_ctrl2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    s14_rfshd_rm          : 4  ; /* [3..0]  */
        unsigned int    s14_rfshs_rm          : 4  ; /* [7..4]  */
        unsigned int    s14_rasehd_rm         : 4  ; /* [11..8]  */
        unsigned int    s14_rashd_rm          : 4  ; /* [15..12]  */
        unsigned int    s14_rfshd_rme         : 1  ; /* [16]  */
        unsigned int    s14_rfshs_rme         : 1  ; /* [17]  */
        unsigned int    s14_rasehd_rme        : 1  ; /* [18]  */
        unsigned int    s14_rashd_rme         : 1  ; /* [19]  */
        unsigned int    s14_rfthd_rma         : 4  ; /* [23..20]  */
        unsigned int    s14_rfthd_rmb         : 4  ; /* [27..24]  */
        unsigned int    s14_rfthd_rmea        : 1  ; /* [28]  */
        unsigned int    s14_rfthd_rmeb        : 1  ; /* [29]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_volowpower_ctrl2;
/* Define the union reg_volowpower_ctrl3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    s14_rom_rm            : 4  ; /* [3..0]  */
        unsigned int    s14_rom_rme           : 1  ; /* [4]  */
        unsigned int    reserved_0            : 27 ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_volowpower_ctrl3;

/* Define the union reg_vomux_dac */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dac0_sel              : 4  ; /* [3..0]  */
        unsigned int    dac1_sel              : 4  ; /* [7..4]  */
        unsigned int    dac2_sel              : 4  ; /* [11..8]  */
        unsigned int    dac3_sel              : 4  ; /* [15..12]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vomux_dac;
/* Define the union reg_vomux_testsync */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    test_dv               : 1  ; /* [0]  */
        unsigned int    test_hsync            : 1  ; /* [1]  */
        unsigned int    test_vsync            : 1  ; /* [2]  */
        unsigned int    test_field            : 1  ; /* [3]  */
        unsigned int    reserved_0            : 27 ; /* [30..4]  */
        unsigned int    vo_test_en            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vomux_testsync;

/* Define the union reg_vomux_testdata */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    test_data             : 30 ; /* [29..0]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vomux_testdata;
/* Define the union reg_vo_dac_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dac_reg_rev           : 16 ; /* [15..0]  */
        unsigned int    enctr                 : 4  ; /* [19..16]  */
        unsigned int    enextref              : 1  ; /* [20]  */
        unsigned int    pdchopper             : 1  ; /* [21]  */
        unsigned int    envbg                 : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac_ctrl;

/* Define the union reg_vo_dac_otp */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dac_otp_reg           : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac_otp;

/* Define the union reg_vo_dac0_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cablectr              : 2  ; /* [1..0]  */
        unsigned int    reserved_0            : 2  ; /* [3..2]  */
        unsigned int    dacgc                 : 6  ; /* [9..4]  */
        unsigned int    reserved_1            : 21 ; /* [30..10]  */
        unsigned int    dac_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac0_ctrl;

/* Define the union reg_vo_dac1_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cablectr              : 2  ; /* [1..0]  */
        unsigned int    reserved_0            : 2  ; /* [3..2]  */
        unsigned int    dacgc                 : 6  ; /* [9..4]  */
        unsigned int    reserved_1            : 21 ; /* [30..10]  */
        unsigned int    dac_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac1_ctrl;
/* Define the union reg_vo_dac2_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cablectr              : 2  ; /* [1..0]  */
        unsigned int    reserved_0            : 2  ; /* [3..2]  */
        unsigned int    dacgc                 : 6  ; /* [9..4]  */
        unsigned int    reserved_1            : 21 ; /* [30..10]  */
        unsigned int    dac_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac2_ctrl;

/* Define the union reg_vo_dac3_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cablectr              : 2  ; /* [1..0]  */
        unsigned int    reserved_0            : 2  ; /* [3..2]  */
        unsigned int    dacgc                 : 6  ; /* [9..4]  */
        unsigned int    reserved_1            : 21 ; /* [30..10]  */
        unsigned int    dac_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac3_ctrl;

/* Define the union reg_vo_dac_stat0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cableout0             : 1  ; /* [0]  */
        unsigned int    cableout1             : 1  ; /* [1]  */
        unsigned int    cableout2             : 1  ; /* [2]  */
        unsigned int    cableout3             : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vo_dac_stat0;

/* define the union reg_cbm_bkg1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm_bkgcr1 : 10; /* [9..0]  */
        unsigned int cbm_bkgcb1 : 10; /* [19..10]  */
        unsigned int cbm_bkgy1 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_cbm_bkg1;

/* define the union reg_cbm_mix1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_prio0 : 4; /* [3..0]  */
        unsigned int mixer_prio1 : 4; /* [7..4]  */
        unsigned int mixer_prio2 : 4; /* [11..8]  */
        unsigned int mixer_prio3 : 4; /* [15..12]  */
        unsigned int mixer_prio4 : 4; /* [19..16]  */
        unsigned int reserved_0  : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_cbm_mix1;

/* define the union reg_wbc_bmp_thd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_bmp_thd : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_bmp_thd;

/* define the union reg_cbm_bkg2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm_bkgcr2 : 10; /* [9..0]  */
        unsigned int cbm_bkgcb2 : 10; /* [19..10]  */
        unsigned int cbm_bkgy2 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_cbm_bkg2;

/* define the union reg_cbm_mix2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_prio0 : 4; /* [3..0]  */
        unsigned int mixer_prio1 : 4; /* [7..4]  */
        unsigned int mixer_prio2 : 4; /* [11..8]  */
        unsigned int mixer_prio3 : 4; /* [15..12]  */
        unsigned int mixer_prio4 : 4; /* [19..16]  */
        unsigned int reserved_0  : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_cbm_mix2;

/* define the union reg_hc_bmp_thd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hc_bmp_thd : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_hc_bmp_thd;

/* define the union reg_cbm_bkg3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm_bkgcr3 : 10; /* [9..0]  */
        unsigned int cbm_bkgcb3 : 10; /* [19..10]  */
        unsigned int cbm_bkgy3 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_cbm_bkg3;

/* define the union reg_cbm_mix3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_prio0 : 4; /* [3..0]  */
        unsigned int mixer_prio1 : 4; /* [7..4]  */
        unsigned int mixer_prio2 : 4; /* [11..8]  */
        unsigned int reserved_0 : 20; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_cbm_mix3;

/* define the union reg_mixv0_bkg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_bkgcr : 10; /* [9..0]  */
        unsigned int mixer_bkgcb : 10; /* [19..10]  */
        unsigned int mixer_bkgy : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mixv0_bkg;

/* define the union reg_mixv0_mix */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_prio0 : 4; /* [3..0]  */
        unsigned int mixer_prio1 : 4; /* [7..4]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mixv0_mix;

/* define the union reg_mixg0_bkg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_bkgcr : 10; /* [9..0]  */
        unsigned int mixer_bkgcb : 10; /* [19..10]  */
        unsigned int mixer_bkgy : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mixg0_bkg;

/* define the union reg_mixg0_bkalpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mixg0_bkalpha;

/* define the union reg_mixg0_mix */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_prio0 : 4; /* [3..0]  */
        unsigned int mixer_prio1 : 4; /* [7..4]  */
        unsigned int mixer_prio2 : 4; /* [11..8]  */
        unsigned int mixer_prio3 : 4; /* [15..12]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mixg0_mix;

/* define the union reg_link_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    g2_link               : 2  ; /* [1..0]  */
        unsigned int    wbc_dhd_link          : 2  ; /* [3..2]  */
        unsigned int    v2_link               : 1  ; /* [4]  */
        unsigned int    v1_link               : 1  ; /* [5]  */
        unsigned int    reserved_0            : 1  ; /* [6]  */
        unsigned int    g3_link               : 2  ; /* [8..7]  */
        unsigned int    reserved_1            : 23 ; /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_link_ctrl;

/* define the union reg_vpss_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vpss_en : 1; /* [0]  */
        unsigned int chk_sum_en : 1; /* [1]  */
        unsigned int dei_en : 1; /* [2]  */
        unsigned int mcdi_en : 1; /* [3]  */
        unsigned int nx2_vc1_en : 1; /* [4]  */
        unsigned int rgme_en : 1; /* [5]  */
        unsigned int meds_en : 1; /* [6]  */
        unsigned int hsp_en : 1; /* [7]  */
        unsigned int snr_en : 1; /* [8]  */
        unsigned int tnr_en : 1; /* [9]  */
        unsigned int rfr_en : 1; /* [10]  */
        unsigned int ifmd_en : 1; /* [11]  */
        unsigned int igbm_en : 1; /* [12]  */
        unsigned int cue_en : 1; /* [13]  */
        unsigned int scd_en : 1; /* [14]  */
        unsigned int blk_det_en : 1; /* [15]  */
        unsigned int reserved_0 : 7; /* [22..16]  */
        unsigned int vpss_node_init : 1; /* [23]  */
        unsigned int ram_bank : 4; /* [27..24]  */
        unsigned int dei_debug_en : 1; /* [28]  */
        unsigned int dei_repeat_mode : 1; /* [29]  */
        unsigned int reserved_1 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vpss_ctrl;

/* define the union reg_vpss_miscellaneous */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 4; /* [3..0]  */
        unsigned int reserved_1 : 4; /* [7..4]  */
        unsigned int reserved_2 : 16; /* [23..8]  */
        unsigned int ck_gt_en : 1; /* [24]  */
        unsigned int ck_gt_en_calc : 1; /* [25]  */
        unsigned int reserved_3 : 2; /* [27..26]  */
        unsigned int reserved_4 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vpss_miscellaneous;

/* define the union reg_vpss_ftconfig */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int node_rst_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vpss_ftconfig;

/* define the union reg_para_up_vhd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_up_vhd_chn00 : 1; /* [0]  */
        unsigned int para_up_vhd_chn01 : 1; /* [1]  */
        unsigned int para_up_vhd_chn02 : 1; /* [2]  */
        unsigned int para_up_vhd_chn03 : 1; /* [3]  */
        unsigned int para_up_vhd_chn04 : 1; /* [4]  */
        unsigned int para_up_vhd_chn05 : 1; /* [5]  */
        unsigned int para_up_vhd_chn06 : 1; /* [6]  */
        unsigned int para_up_vhd_chn07 : 1; /* [7]  */
        unsigned int para_up_vhd_chn08 : 1; /* [8]  */
        unsigned int para_up_vhd_chn09 : 1; /* [9]  */
        unsigned int para_up_vhd_chn10 : 1; /* [10]  */
        unsigned int para_up_vhd_chn11 : 1; /* [11]  */
        unsigned int para_up_vhd_chn12 : 1; /* [12]  */
        unsigned int para_up_vhd_chn13 : 1; /* [13]  */
        unsigned int para_up_vhd_chn14 : 1; /* [14]  */
        unsigned int para_up_vhd_chn15 : 1; /* [15]  */
        unsigned int para_up_vhd_chn16 : 1; /* [16]  */
        unsigned int para_up_vhd_chn17 : 1; /* [17]  */
        unsigned int para_up_vhd_chn18 : 1; /* [18]  */
        unsigned int para_up_vhd_chn19 : 1; /* [19]  */
        unsigned int para_up_vhd_chn20 : 1; /* [20]  */
        unsigned int para_up_vhd_chn21 : 1; /* [21]  */
        unsigned int para_up_vhd_chn22 : 1; /* [22]  */
        unsigned int para_up_vhd_chn23 : 1; /* [23]  */
        unsigned int para_up_vhd_chn24 : 1; /* [24]  */
        unsigned int para_up_vhd_chn25 : 1; /* [25]  */
        unsigned int para_up_vhd_chn26 : 1; /* [26]  */
        unsigned int para_up_vhd_chn27 : 1; /* [27]  */
        unsigned int para_up_vhd_chn28 : 1; /* [28]  */
        unsigned int para_up_vhd_chn29 : 1; /* [29]  */
        unsigned int para_up_vhd_chn30 : 1; /* [30]  */
        unsigned int para_up_vhd_chn31 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_para_up_vhd;

/* define the union reg_para_up_vsd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_up_vsd_chn00 : 1; /* [0]  */
        unsigned int para_up_vsd_chn01 : 1; /* [1]  */
        unsigned int para_up_vsd_chn02 : 1; /* [2]  */
        unsigned int para_up_vsd_chn03 : 1; /* [3]  */
        unsigned int para_up_vsd_chn04 : 1; /* [4]  */
        unsigned int para_up_vsd_chn05 : 1; /* [5]  */
        unsigned int para_up_vsd_chn06 : 1; /* [6]  */
        unsigned int para_up_vsd_chn07 : 1; /* [7]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_para_up_vsd;

/* define the union reg_para_conflict_clr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_conflict_clr_hd : 1; /* [0]  */
        unsigned int para_conflict_clr_sd : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_para_conflict_clr;

/* define the union reg_para_conflict_sta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_conflict_hd : 1; /* [0]  */
        unsigned int para_conflict_sd : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_para_conflict_sta;

/* define the union reg_v0_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 20; /* [27..8]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int surface_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_ctrl;

/* define the union reg_v0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_upd;

/* define the union reg_v0_0reso_read */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_0reso_read;

/* Define the union reg_v0_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_ireso;

/* define the union reg_v0_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_dfpos;

/* define the union reg_v0_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_dlpos;

/* define the union reg_v0_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_vfpos;

/* define the union reg_v0_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_vlpos;

/* define the union reg_v0_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_bk;

/* define the union reg_v0_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_alpha;

/* define the union reg_v0_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 1; /* [30]  */
        unsigned int mute_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mute_bk;

/* define the union reg_v0_rimwidth */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_width : 5; /* [4..0]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_rimwidth;

/* define the union reg_v0_rimcol0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_v0 : 10; /* [9..0]  */
        unsigned int v0_rim_u0 : 10; /* [19..10]  */
        unsigned int v0_rim_y0 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_rimcol0;

/* define the union reg_v0_rimcol1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_v1 : 10; /* [9..0]  */
        unsigned int v0_rim_u1 : 10; /* [19..10]  */
        unsigned int v0_rim_y1 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_rimcol1;

/* define the union reg_v0_hipp_csc_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_en : 1; /* [0]  */
        unsigned int hipp_csc_demo_en : 1; /* [1]  */
        unsigned int hipp_csc_ck_gt_en : 1; /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_ctrl;

/* define the union reg_v0_hipp_csc_coef00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef00       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef00;

/* define the union reg_v0_hipp_csc_coef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef01       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef01;

/* define the union reg_v0_hipp_csc_coef02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef02       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef02;

/* define the union reg_v0_hipp_csc_coef10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef10       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef10;

/* define the union reg_v0_hipp_csc_coef11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef11       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef11;

/* define the union reg_v0_hipp_csc_coef12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef12       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef12;

/* define the union reg_v0_hipp_csc_coef20 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef20       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef20;

/* define the union reg_v0_hipp_csc_coef21 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef21       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef21;

/* define the union reg_v0_hipp_csc_coef22 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    hipp_csc_coef22       : 12 ; /* [11..0]  */
        unsigned int    reserved_0            : 20 ; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_coef22;

/* define the union reg_v0_hipp_csc_scale */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_scale;

/* define the union reg_v0_hipp_csc_idc0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_idc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_idc0;

/* define the union reg_v0_hipp_csc_idc1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_idc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_idc1;

/* define the union reg_v0_hipp_csc_idc2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_idc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_idc2;

/* define the union reg_v0_hipp_csc_odc0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_odc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_odc0;

/* define the union reg_v0_hipp_csc_odc1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_odc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_odc1;

/* define the union reg_v0_hipp_csc_odc2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_odc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_odc2;

/* define the union reg_v0_hipp_csc_min_y */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_min_y : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_min_y;

/* define the union reg_v0_hipp_csc_min_c */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_min_c : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_min_c;

/* define the union reg_v0_hipp_csc_max_y */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_max_y : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_max_y;

/* define the union reg_v0_hipp_csc_max_c */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc_max_c : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_max_c;

/* define the union reg_v0_hipp_csc2_coef00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef00;

/* define the union reg_v0_hipp_csc2_coef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef01;

/* define the union reg_v0_hipp_csc2_coef02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef02;

/* define the union reg_v0_hipp_csc2_coef10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef10;

/* define the union reg_v0_hipp_csc2_coef11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef11;

/* define the union reg_v0_hipp_csc2_coef12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef12;

/* define the union reg_v0_hipp_csc2_coef20 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef20;

/* define the union reg_v0_hipp_csc2_coef21 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef21;

/* define the union reg_v0_hipp_csc2_coef22 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_coef22;

/* define the union reg_v0_hipp_csc2_scale */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_scale;

/* define the union reg_v0_hipp_csc2_idc0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_idc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_idc0;

/* define the union reg_v0_hipp_csc2_idc1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_idc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_idc1;

/* define the union reg_v0_hipp_csc2_idc2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_idc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_idc2;

/* define the union reg_v0_hipp_csc2_odc0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_odc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_odc0;

/* define the union reg_v0_hipp_csc2_odc1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_odc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_odc1;

/* define the union reg_v0_hipp_csc2_odc2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_odc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_odc2;

/* define the union reg_v0_hipp_csc2_min_y */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_min_y : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_min_y;

/* define the union reg_v0_hipp_csc2_min_c */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_min_c : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_min_c;

/* define the union reg_v0_hipp_csc2_max_y */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_max_y : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_max_y;

/* define the union reg_v0_hipp_csc2_max_c */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hipp_csc2_max_c : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc2_max_c;

/* define the union reg_v0_hipp_csc_ink_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ink_en : 1; /* [0]  */
        unsigned int ink_sel : 1; /* [1]  */
        unsigned int data_fmt : 1; /* [2]  */
        unsigned int cross_enable : 1; /* [3]  */
        unsigned int color_mode : 2; /* [5..4]  */
        unsigned int reserved_0 : 26; /* [31..6]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_ink_ctrl;

/* define the union reg_v0_hipp_csc_ink_pos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int x_pos : 16; /* [15..0]  */
        unsigned int y_pos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hipp_csc_ink_pos;

/* Define the union reg_v0_zme_hinfo */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    out_width             : 16 ; /* [15..0]  */
        unsigned int    hzme_ck_gt_en         : 1  ; /* [16]  */
        unsigned int    reserved_0            : 15 ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hinfo;

/* Define the union reg_v0_zme_hsp */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hratio                : 24 ; /* [23..0]  */
        unsigned int    hfir_order            : 1  ; /* [24]  */
        unsigned int    chfir_mode            : 1  ; /* [25]  */
        unsigned int    lhfir_mode            : 1  ; /* [26]  */
        unsigned int    non_lnr_en            : 1  ; /* [27]  */
        unsigned int    chmid_en              : 1  ; /* [28]  */
        unsigned int    lhmid_en              : 1  ; /* [29]  */
        unsigned int    chfir_en              : 1  ; /* [30]  */
        unsigned int    lhfir_en              : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hsp;

/* Define the union reg_v0_zme_hloffset */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    lhfir_offset          : 28 ; /* [27..0]  */
        unsigned int    reserved_0            : 4  ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hloffset;

/* Define the union reg_v0_zme_hcoffset */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    chfir_offset          : 28 ; /* [27..0]  */
        unsigned int    reserved_0            : 4  ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hcoffset;

/* Define the union reg_v0_zme_hzone0delta */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    zone0_delta           : 22 ; /* [21..0]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hzone0delta;

/* Define the union reg_v0_zme_hzone2delta */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    zone2_delta           : 22 ; /* [21..0]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hzone2delta;

/* Define the union reg_v0_zme_hzoneend */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    zone0_end             : 12 ; /* [11..0]  */
        unsigned int    zone1_end             : 12 ; /* [23..12]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hzoneend;

/* Define the union reg_v0_zme_hl_shootctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hl_coring             : 8  ; /* [7..0]  */
        unsigned int    hl_gain               : 6  ; /* [13..8]  */
        unsigned int    hl_coringadj_en       : 1  ; /* [14]  */
        unsigned int    hl_flatdect_mode      : 1  ; /* [15]  */
        unsigned int    hl_shootctrl_mode     : 1  ; /* [16]  */
        unsigned int    reserved_0            : 1  ; /* [17]  */
        unsigned int    hl_shootctrl_en       : 1  ; /* [18]  */
        unsigned int    reserved_1            : 13 ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hl_shootctrl;

/* Define the union reg_v0_zme_hc_shootctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hc_coring             : 8  ; /* [7..0]  */
        unsigned int    hc_gain               : 6  ; /* [13..8]  */
        unsigned int    hc_coringadj_en       : 1  ; /* [14]  */
        unsigned int    hc_flatdect_mode      : 1  ; /* [15]  */
        unsigned int    hc_shootctrl_mode     : 1  ; /* [16]  */
        unsigned int    reserved_0            : 1  ; /* [17]  */
        unsigned int    hc_shootctrl_en       : 1  ; /* [18]  */
        unsigned int    reserved_1            : 13 ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hc_shootctrl;

/* Define the union reg_v0_zme_hcoef_ren */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    apb_vhd_hf_cren       : 1  ; /* [0]  */
        unsigned int    apb_vhd_hf_lren       : 1  ; /* [1]  */
        unsigned int    reserved_0            : 30 ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hcoef_ren;

/* Define the union reg_v0_zme_hcoef_rdata */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    apb_vhd_hcoef_raddr   : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_hcoef_rdata;

/* Define the union reg_v0_zme_vinfo */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    out_height            : 16 ; /* [15..0]  */
        unsigned int    out_fmt               : 2  ; /* [17..16]  */
        unsigned int    out_pro               : 1  ; /* [18]  */
        unsigned int    vzme_ck_gt_en         : 1  ; /* [19]  */
        unsigned int    reserved_0            : 12 ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vinfo;

/* Define the union reg_v0_zme_vsp */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vratio                : 16 ; /* [15..0]  */
        unsigned int    graphdet_en           : 1  ; /* [16]  */
        unsigned int    reserved_0            : 8  ; /* [24..17]  */
        unsigned int    cvfir_mode            : 1  ; /* [25]  */
        unsigned int    lvfir_mode            : 1  ; /* [26]  */
        unsigned int    vfir_1tap_en          : 1  ; /* [27]  */
        unsigned int    cvmid_en              : 1  ; /* [28]  */
        unsigned int    lvmid_en              : 1  ; /* [29]  */
        unsigned int    cvfir_en              : 1  ; /* [30]  */
        unsigned int    lvfir_en              : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vsp;

/* Define the union reg_v0_zme_voffset */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vchroma_offset        : 16 ; /* [15..0]  */
        unsigned int    vluma_offset          : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_voffset;

/* Define the union reg_v0_zme_vboffset */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vbchroma_offset       : 16 ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vboffset;

/* Define the union reg_v0_zme_vl_shootctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vl_coring             : 8  ; /* [7..0]  */
        unsigned int    vl_gain               : 6  ; /* [13..8]  */
        unsigned int    vl_coringadj_en       : 1  ; /* [14]  */
        unsigned int    vl_flatdect_mode      : 1  ; /* [15]  */
        unsigned int    vl_shootctrl_mode     : 1  ; /* [16]  */
        unsigned int    reserved_0            : 1  ; /* [17]  */
        unsigned int    vl_shootctrl_en       : 1  ; /* [18]  */
        unsigned int    reserved_1            : 13 ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vl_shootctrl;

/* Define the union reg_v0_zme_vc_shootctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vc_coring             : 8  ; /* [7..0]  */
        unsigned int    vc_gain               : 6  ; /* [13..8]  */
        unsigned int    vc_coringadj_en       : 1  ; /* [14]  */
        unsigned int    vc_flatdect_mode      : 1  ; /* [15]  */
        unsigned int    vc_shootctrl_mode     : 1  ; /* [16]  */
        unsigned int    reserved_0            : 1  ; /* [17]  */
        unsigned int    vc_shootctrl_en       : 1  ; /* [18]  */
        unsigned int    reserved_1            : 13 ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vc_shootctrl;

/* Define the union reg_v0_zme_vcoef_ren */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    apb_vhd_vf_cren       : 1  ; /* [0]  */
        unsigned int    apb_vhd_vf_lren       : 1  ; /* [1]  */
        unsigned int    reserved_0            : 30 ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vcoef_ren;

/* Define the union reg_v0_zme_vcoef_rdata */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    apb_vhd_vcoef_raddr   : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_zme_vcoef_rdata;

/* Define the union reg_v0_hfir_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1; /* [0]  */
        unsigned int hfir_mode : 2; /* [2..1]  */
        unsigned int mid_en : 1; /* [3]  */
        unsigned int ck_gt_en : 1; /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hfir_ctrl;

/* define the union reg_v0_hfircoef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hfircoef01;

/* define the union reg_v0_hfircoef23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hfircoef23;

/* define the union reg_v0_hfircoef45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef4 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef5 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hfircoef45;

/* define the union reg_v0_hfircoef67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef6 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef7 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_hfircoef67;

/* define the union reg_v1_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 20; /* [27..8]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int surface_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_ctrl;

/* define the union reg_v1_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_upd;

/* define the union reg_v1_0reso_read */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_0reso_read;

/* Define the union reg_v1_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_ireso;

/* Define the union reg_v1_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_dfpos;

/* define the union reg_v1_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_dlpos;

/* define the union reg_v1_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_vfpos;

/* define the union reg_v1_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_vlpos;

/* define the union reg_v1_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_bk;

/* define the union reg_v1_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_alpha;

/* define the union reg_v1_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 1; /* [30]  */
        unsigned int mute_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mute_bk;

/* define the union reg_v1_rimwidth */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_width : 5; /* [4..0]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_rimwidth;

/* define the union reg_v1_rimcol0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_v0 : 10; /* [9..0]  */
        unsigned int v0_rim_u0 : 10; /* [19..10]  */
        unsigned int v0_rim_y0 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_rimcol0;

/* define the union reg_v1_rimcol1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_v1 : 10; /* [9..0]  */
        unsigned int v0_rim_u1 : 10; /* [19..10]  */
        unsigned int v0_rim_y1 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_rimcol1;

/* define the union reg_v1_cvfir_vinfo */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16; /* [15..0]  */
        unsigned int out_fmt : 2; /* [17..16]  */
        unsigned int out_pro : 1; /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_vinfo;

/* define the union reg_v1_cvfir_vsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16; /* [15..0]  */
        unsigned int reserved_0 : 1; /* [16]  */
        unsigned int reserved_1 : 8; /* [24..17]  */
        unsigned int cvfir_mode : 1; /* [25]  */
        unsigned int reserved_2 : 1; /* [26]  */
        unsigned int reserved_3 : 1; /* [27]  */
        unsigned int cvmid_en : 1; /* [28]  */
        unsigned int reserved_4 : 1; /* [29]  */
        unsigned int cvfir_en : 1; /* [30]  */
        unsigned int reserved_5 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_vsp;

/* define the union reg_v1_cvfir_voffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_voffset;

/* define the union reg_v1_cvfir_vboffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_vboffset;

/* define the union reg_v1_cvfir_vcoef0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef02 : 10; /* [9..0]  */
        unsigned int vccoef01 : 10; /* [19..10]  */
        unsigned int vccoef00 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_vcoef0;

/* define the union reg_v1_cvfir_vcoef1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef11 : 10; /* [9..0]  */
        unsigned int vccoef10 : 10; /* [19..10]  */
        unsigned int vccoef03 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_vcoef1;

/* define the union reg_v1_cvfir_vcoef2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef13 : 10; /* [9..0]  */
        unsigned int vccoef12 : 10; /* [19..10]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_cvfir_vcoef2;

/* define the union reg_v1_hfir_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1; /* [0]  */
        unsigned int hfir_mode : 2; /* [2..1]  */
        unsigned int mid_en : 1; /* [3]  */
        unsigned int ck_gt_en : 1; /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_hfir_ctrl;

/* define the union reg_v1_hfircoef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_hfircoef01;

/* define the union reg_v1_hfircoef23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_hfircoef23;

/* define the union reg_v1_hfircoef45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef4 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef5 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_hfircoef45;

/* define the union reg_v1_hfircoef67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef6 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef7 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_hfircoef67;

/* define the union reg_v2_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 20; /* [27..8]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int surface_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_ctrl;

/* define the union reg_v2_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_upd;

/* define the union reg_v2_0reso_read */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_0reso_read;

/* Define the union reg_v2_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_ireso;

/* define the union reg_v2_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_dfpos;

/* define the union reg_v2_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_dlpos;

/* define the union reg_v2_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_vfpos;

/* define the union reg_v2_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_vlpos;

/* define the union reg_v2_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_bk;

/* define the union reg_v2_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_alpha;

/* define the union reg_v2_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int    reserved_0            : 1  ; /* [30]  */
        unsigned int    mute_en               : 1  ; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_mute_bk;

/* define the union reg_v2_cvfir_vinfo */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16; /* [15..0]  */
        unsigned int out_fmt : 2; /* [17..16]  */
        unsigned int out_pro : 1; /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_vinfo;

/* define the union reg_v2_cvfir_vsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16; /* [15..0]  */
        unsigned int reserved_0 : 1; /* [16]  */
        unsigned int reserved_1 : 8; /* [24..17]  */
        unsigned int cvfir_mode : 1; /* [25]  */
        unsigned int reserved_2 : 1; /* [26]  */
        unsigned int reserved_3 : 1; /* [27]  */
        unsigned int cvmid_en : 1; /* [28]  */
        unsigned int reserved_4 : 1; /* [29]  */
        unsigned int cvfir_en : 1; /* [30]  */
        unsigned int reserved_5 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_vsp;

/* define the union reg_v2_cvfir_voffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_voffset;

/* define the union reg_v2_cvfir_vboffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_vboffset;

/* define the union reg_v2_cvfir_vcoef0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef02 : 10; /* [9..0]  */
        unsigned int vccoef01 : 10; /* [19..10]  */
        unsigned int vccoef00 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_vcoef0;

/* define the union reg_v2_cvfir_vcoef1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef11 : 10; /* [9..0]  */
        unsigned int vccoef10 : 10; /* [19..10]  */
        unsigned int vccoef03 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_vcoef1;

/* define the union reg_v2_cvfir_vcoef2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef13 : 10; /* [9..0]  */
        unsigned int vccoef12 : 10; /* [19..10]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_cvfir_vcoef2;

/* define the union reg_v2_hfir_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1; /* [0]  */
        unsigned int hfir_mode : 2; /* [2..1]  */
        unsigned int mid_en : 1; /* [3]  */
        unsigned int ck_gt_en : 1; /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_hfir_ctrl;

/* define the union reg_v2_hfircoef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_hfircoef01;

/* define the union reg_v2_hfircoef23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_hfircoef23;

/* define the union reg_v2_hfircoef45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef4 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef5 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_hfircoef45;

/* define the union reg_v2_hfircoef67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef6 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef7 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v2_hfircoef67;

/* Define the union reg_v3_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    galpha                : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 20 ; /* [27..8]  */
        unsigned int    rupd_field            : 1  ; /* [28]  */
        unsigned int    rgup_mode             : 1  ; /* [29]  */
        unsigned int    nosec_flag            : 1  ; /* [30]  */
        unsigned int    surface_en            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_ctrl;

/* Define the union reg_v3_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_upd;

/* Define the union reg_v3_0reso_read */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ow                    : 16 ; /* [15..0]  */
        unsigned int    oh                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_0reso_read;

/* Define the union reg_v3_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_ireso;

/* Define the union reg_v3_dfpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    disp_xfpos            : 16 ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_dfpos;

/* Define the union reg_v3_dlpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    disp_xlpos            : 16 ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_dlpos;

/* Define the union reg_v3_vfpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    video_xfpos           : 16 ; /* [15..0]  */
        unsigned int    video_yfpos           : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_vfpos;

/* Define the union reg_v3_vlpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    video_xlpos           : 16 ; /* [15..0]  */
        unsigned int    video_ylpos           : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_vlpos;

/* Define the union reg_v3_bk */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vbk_cr                : 10 ; /* [9..0]  */
        unsigned int    vbk_cb                : 10 ; /* [19..10]  */
        unsigned int    vbk_y                 : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_bk;

/* Define the union reg_v3_alpha */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vbk_alpha             : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_alpha;

/* Define the union reg_v3_mute_bk */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    mute_cr               : 10 ; /* [9..0]  */
        unsigned int    mute_cb               : 10 ; /* [19..10]  */
        unsigned int    mute_y                : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 1  ; /* [30]  */
        unsigned int    mute_en               : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_mute_bk;

/* Define the union reg_v3_rimwidth */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    v0_rim_width          : 5  ; /* [4..0]  */
        unsigned int    reserved_0            : 27 ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_rimwidth;

/* Define the union reg_v3_rimcol0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    v0_rim_v0             : 10 ; /* [9..0]  */
        unsigned int    v0_rim_u0             : 10 ; /* [19..10]  */
        unsigned int    v0_rim_y0             : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_rimcol0;

/* Define the union reg_v3_rimcol1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    v0_rim_v1             : 10 ; /* [9..0]  */
        unsigned int    v0_rim_u1             : 10 ; /* [19..10]  */
        unsigned int    v0_rim_y1             : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_rimcol1;

/* Define the union reg_v3_hfir_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 1  ; /* [0]  */
        unsigned int    hfir_mode             : 2  ; /* [2..1]  */
        unsigned int    mid_en                : 1  ; /* [3]  */
        unsigned int    ck_gt_en              : 1  ; /* [4]  */
        unsigned int    reserved_1            : 27 ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_hfir_ctrl;

/* Define the union reg_v3_hfircoef01 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef0                 : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    coef1                 : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_hfircoef01;

/* Define the union reg_v3_hfircoef23 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef2                 : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    coef3                 : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_hfircoef23;

/* Define the union reg_v3_hfircoef45 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef4                 : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    coef5                 : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_hfircoef45;

/* Define the union reg_v3_hfircoef67 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef6                 : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    coef7                 : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v3_hfircoef67;

/* define the union reg_vp0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_upd;

/* define the union reg_vp0_ireso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int iw : 16; /* [15..0]  */
        unsigned int ih : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_ireso;

/* define the union reg_vp0_lbox_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_lbox_ctrl;

/* define the union reg_vp0_galpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_galpha;

/* define the union reg_vp0_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 12; /* [11..0]  */
        unsigned int disp_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_dfpos;

/* define the union reg_vp0_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 12; /* [11..0]  */
        unsigned int disp_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_dlpos;

/* define the union reg_vp0_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 12; /* [11..0]  */
        unsigned int video_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_vfpos;

/* define the union reg_vp0_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 12; /* [11..0]  */
        unsigned int video_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_vlpos;

/* define the union reg_vp0_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_bk;

/* define the union reg_vp0_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_alpha;

/* define the union reg_vp0_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vp0_mute_bk;

/* define the union reg_g0_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 19; /* [26..8]  */
        unsigned int g0_depremult : 1; /* [27]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int surface_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_ctrl;

/* define the union reg_g0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_upd;

/* define the union reg_g0_0reso_read */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_0reso_read;

/* Define the union reg_g0_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g0_ireso;

/* define the union reg_g0_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_dfpos;

/* define the union reg_g0_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_dlpos;

/* define the union reg_g0_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_vfpos;

/* define the union reg_g0_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_vlpos;

/* define the union reg_g0_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_bk;

/* define the union reg_g0_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_alpha;

/* define the union reg_g0_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int    reserved_0            : 1  ; /* [30]  */
        unsigned int    mute_en               : 1  ; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_mute_bk;

/* define the union reg_g0_lbox_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_lbox_ctrl;

/* define the union reg_g0_dof_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int dof_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_dof_ctrl;

/* define the union reg_g0_dof_step */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int left_step : 8; /* [7..0]  */
        unsigned int right_step : 8; /* [15..8]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_dof_step;

/* define the union reg_g0_dof_bkg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dof_bk_cr : 10; /* [9..0]  */
        unsigned int dof_bk_cb : 10; /* [19..10]  */
        unsigned int dof_bk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_dof_bkg;

/* define the union reg_g0_dof_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dof_bk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_dof_alpha;

/* define the union reg_g0_zme_hinfo */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_width : 16; /* [15..0]  */
        unsigned int ck_gt_en : 1; /* [16]  */
        unsigned int reserved_0 : 15; /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_hinfo;

/* define the union reg_g0_zme_hsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 24; /* [23..0]  */
        unsigned int hfir_order : 1; /* [24]  */
        unsigned int ahfir_mode : 1; /* [25]  */
        unsigned int lhfir_mode : 1; /* [26]  */
        unsigned int reserved_0 : 1; /* [27]  */
        unsigned int chfir_mid_en : 1; /* [28]  */
        unsigned int lhfir_mid_en : 1; /* [29]  */
        unsigned int ahfir_mid_en : 1; /* [30]  */
        unsigned int hfir_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_hsp;

/* define the union reg_g0_zme_hloffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lhfir_offset : 24; /* [23..0]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_hloffset;

/* define the union reg_g0_zme_hcoffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chfir_offset : 24; /* [23..0]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_hcoffset;

/* define the union reg_g0_zme_coef_ren */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1; /* [0]  */
        unsigned int apb_g0_vf_lren : 1; /* [1]  */
        unsigned int reserved_1 : 1; /* [2]  */
        unsigned int apb_g0_hf_lren : 1; /* [3]  */
        unsigned int reserved_2 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_coef_ren;

/* define the union reg_g0_zme_coef_rdata */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_coef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_coef_rdata;

/* define the union reg_g0_zme_vinfo */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16; /* [15..0]  */
        unsigned int reserved_0 : 2; /* [17..16]  */
        unsigned int out_pro : 1; /* [18]  */
        unsigned int reserved_1 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_vinfo;

/* define the union reg_g0_zme_vsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16; /* [15..0]  */
        unsigned int reserved_0 : 9; /* [24..16]  */
        unsigned int vafir_mode : 1; /* [25]  */
        unsigned int lvfir_mode : 1; /* [26]  */
        unsigned int reserved_1 : 1; /* [27]  */
        unsigned int cvfir_mid_en : 1; /* [28]  */
        unsigned int lvfir_mid_en : 1; /* [29]  */
        unsigned int avfir_mid_en : 1; /* [30]  */
        unsigned int vfir_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_vsp;

/* define the union reg_g0_zme_voffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbtm_offset : 16; /* [15..0]  */
        unsigned int vtp_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g0_zme_voffset;

/* define the union reg_g1_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 19; /* [26..8]  */
        unsigned int g1_depremult : 1; /* [27]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int surface_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_ctrl;

/* define the union reg_g1_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_upd;

/* define the union reg_g1_0reso_read */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_0reso_read;

/* Define the union reg_g1_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_ireso;

/* define the union reg_g1_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_dfpos;

/* define the union reg_g1_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_dlpos;

/* define the union reg_g1_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_vfpos;

/* define the union reg_g1_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_vlpos;

/* define the union reg_g1_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_bk;

/* define the union reg_g1_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_alpha;

/* define the union reg_g1_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_mute_bk;

/* define the union reg_g1_lbox_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g1_lbox_ctrl;

/* Define the union reg_g2_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    galpha                : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 19 ; /* [26..8]  */
        unsigned int    g1_depremult          : 1  ; /* [27]  */
        unsigned int    rupd_field            : 1  ; /* [28]  */
        unsigned int    rgup_mode             : 1  ; /* [29]  */
        unsigned int    nosec_flag            : 1  ; /* [30]  */
        unsigned int    surface_en            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_ctrl;

/* Define the union reg_g2_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_upd;

/* Define the union reg_g2_0reso_read */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ow                    : 16 ; /* [15..0]  */
        unsigned int    oh                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_0reso_read;

/* Define the union reg_g2_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_ireso;

/* Define the union reg_g2_dfpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    disp_xfpos            : 16 ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_dfpos;

/* Define the union reg_g2_dlpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    disp_xlpos            : 16 ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_dlpos;

/* Define the union reg_g2_vfpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    video_xfpos           : 16 ; /* [15..0]  */
        unsigned int    video_yfpos           : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_vfpos;

/* Define the union reg_g2_vlpos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    video_xlpos           : 16 ; /* [15..0]  */
        unsigned int    video_ylpos           : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_vlpos;

/* Define the union reg_g2_bk */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vbk_cr                : 10 ; /* [9..0]  */
        unsigned int    vbk_cb                : 10 ; /* [19..10]  */
        unsigned int    vbk_y                 : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_bk;

/* Define the union reg_g2_alpha */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vbk_alpha             : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_alpha;

/* Define the union reg_g2_mute_bk */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    mute_cr               : 10 ; /* [9..0]  */
        unsigned int    mute_cb               : 10 ; /* [19..10]  */
        unsigned int    mute_y                : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_mute_bk;

/* Define the union reg_g2_lbox_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    mute_en               : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g2_lbox_ctrl;

/* define the union reg_g3_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 19; /* [26..8]  */
        unsigned int g1_depremult : 1; /* [27]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int surface_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_ctrl;

/* define the union reg_g3_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_upd;

/* define the union reg_g3_0reso_read */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_0reso_read;

/* Define the union reg_g3_ireso */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    iw                    : 16 ; /* [15..0]  */
        unsigned int    ih                    : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_ireso;

/* Define the union reg_g3_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_dfpos;

/* define the union reg_g3_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_dlpos;

/* define the union reg_g3_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_vfpos;

/* define the union reg_g3_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_vlpos;

/* define the union reg_g3_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_bk;

/* define the union reg_g3_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_alpha;

/* define the union reg_g3_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_mute_bk;

/* define the union reg_g3_lbox_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_g3_lbox_ctrl;

/* define the union reg_gp0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_upd;

/* define the union reg_gp0_ireso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int iw : 16; /* [15..0]  */
        unsigned int ih : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_ireso;

/* define the union reg_gp0_lbox_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_lbox_ctrl;

/* define the union reg_gp0_galpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_galpha;

/* define the union reg_gp0_dfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 12; /* [11..0]  */
        unsigned int disp_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_dfpos;

/* define the union reg_gp0_dlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 12; /* [11..0]  */
        unsigned int disp_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_dlpos;

/* define the union reg_gp0_vfpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 12; /* [11..0]  */
        unsigned int video_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_vfpos;

/* define the union reg_gp0_vlpos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 12; /* [11..0]  */
        unsigned int video_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_vlpos;

/* define the union reg_gp0_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10; /* [9..0]  */
        unsigned int vbk_cb : 10; /* [19..10]  */
        unsigned int vbk_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_bk;

/* define the union reg_gp0_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_alpha;

/* define the union reg_gp0_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_mute_bk;

/* define the union reg_gp0_csc_idc */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11; /* [10..0]  */
        unsigned int cscidc1 : 11; /* [21..11]  */
        unsigned int csc_en : 1; /* [22]  */
        unsigned int reserved_0 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_idc;

/* define the union reg_gp0_csc_odc */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11; /* [10..0]  */
        unsigned int cscodc1 : 11; /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_odc;

/* define the union reg_gp0_csc_iodc */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11; /* [10..0]  */
        unsigned int cscodc2 : 11; /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_iodc;

/* define the union reg_gp0_csc_p0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15; /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15; /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_p0;

/* define the union reg_gp0_csc_p1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15; /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15; /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_p1;

/* define the union reg_gp0_csc_p2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15; /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15; /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_p2;

/* define the union reg_gp0_csc_p3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15; /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15; /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_p3;

/* define the union reg_gp0_csc_p4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15; /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gp0_csc_p4;

/* define the union reg_wbc_g0_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int auto_stop_en : 1; /* [10]  */
        unsigned int reserved_0 : 15; /* [25..11]  */
        unsigned int format_out : 2; /* [27..26]  */
        unsigned int reserved_1 : 3; /* [30..28]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_ctrl;

/* define the union reg_wbc_g0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_upd;

/* define the union reg_wbc_g0_cmp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cmp_lossy_en : 1; /* [0]  */
        unsigned int reserved_0 : 3; /* [3..1]  */
        unsigned int cmp_drr : 4; /* [7..4]  */
        unsigned int reserved_1 : 23; /* [30..8]  */
        unsigned int cmp_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_cmp;

/* define the union reg_wbc_g0_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbcstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_stride;

/* define the union reg_wbc_g0_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12; /* [11..0]  */
        unsigned int oh : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_oreso;

/* define the union reg_wbc_g0_fcrop */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wfcrop : 12; /* [11..0]  */
        unsigned int hfcrop : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_fcrop;

/* define the union reg_wbc_g0_lcrop */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlcrop : 12; /* [11..0]  */
        unsigned int hlcrop : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_g0_lcrop;

/* define the union reg_wbc_gp0_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int auto_stop_en : 1; /* [10]  */
        unsigned int reserved_0 : 1; /* [11]  */
        unsigned int wbc_vtthd_mode : 1; /* [12]  */
        unsigned int reserved_1 : 5; /* [17..13]  */
        unsigned int three_d_mode : 2; /* [19..18]  */
        unsigned int reserved_2 : 3; /* [22..20]  */
        unsigned int flip_en : 1; /* [23]  */
        unsigned int format_out : 4; /* [27..24]  */
        unsigned int mode_out : 2; /* [29..28]  */
        unsigned int reserved_3 : 1; /* [30]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_ctrl;

/* define the union reg_wbc_gp0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_upd;

/* define the union reg_wbc_gp0_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbclstride : 16; /* [15..0]  */
        unsigned int wbccstride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_stride;

/* define the union reg_wbc_gp0_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12; /* [11..0]  */
        unsigned int oh : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_oreso;

/* define the union reg_wbc_gp0_fcrop */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wfcrop : 12; /* [11..0]  */
        unsigned int hfcrop : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_fcrop;

/* define the union reg_wbc_gp0_lcrop */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlcrop : 12; /* [11..0]  */
        unsigned int hlcrop : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_lcrop;

/* define the union reg_wbc_gp0_dither_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29; /* [28..0]  */
        unsigned int dither_round : 1; /* [29]  */
        unsigned int dither_mode : 1; /* [30]  */
        unsigned int dither_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_dither_ctrl;

/* define the union reg_wbc_gp0_dither_coef0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_coef0 : 8; /* [7..0]  */
        unsigned int dither_coef1 : 8; /* [15..8]  */
        unsigned int dither_coef2 : 8; /* [23..16]  */
        unsigned int dither_coef3 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_dither_coef0;

/* define the union reg_wbc_gp0_dither_coef1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_coef4 : 8; /* [7..0]  */
        unsigned int dither_coef5 : 8; /* [15..8]  */
        unsigned int dither_coef6 : 8; /* [23..16]  */
        unsigned int dither_coef7 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_dither_coef1;

/* define the union reg_wbc_gp0_hpzme */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29; /* [28..0]  */
        unsigned int hpzme_mode : 1; /* [29]  */
        unsigned int hpzme_mid_en : 1; /* [30]  */
        unsigned int hpzme_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_gp0_hpzme;

/* define the union reg_wbc_me_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 10; /* [19..10]  */
        unsigned int ofl_master : 1; /* [20]  */
        unsigned int reserved_1 : 2; /* [22..21]  */
        unsigned int mad_data_mode : 1; /* [23]  */
        unsigned int format_out : 4; /* [27..24]  */
        unsigned int reserved_2 : 1; /* [28]  */
        unsigned int c_wbc_en : 1; /* [29]  */
        unsigned int reserved_3 : 1; /* [30]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_ctrl;

/* define the union reg_wbc_me_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_upd;

/* define the union reg_wbc_me_wlen_sel */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlen_sel : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_wlen_sel;

/* define the union reg_wbc_me_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbclstride : 16; /* [15..0]  */
        unsigned int wbccstride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_stride;

/* define the union reg_wbc_me_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12; /* [11..0]  */
        unsigned int oh : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_oreso;

/* define the union reg_wbc_me_smmu_bypass */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_bypass : 1; /* [0]  */
        unsigned int c_bypass : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_smmu_bypass;

/* define the union reg_wbc_me_paraup */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_hlcoef_upd : 1; /* [0]  */
        unsigned int wbc_hccoef_upd : 1; /* [1]  */
        unsigned int wbc_vlcoef_upd : 1; /* [2]  */
        unsigned int wbc_vccoef_upd : 1; /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_paraup;

/* define the union reg_wbc_me_dither_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29; /* [28..0]  */
        unsigned int dither_round : 1; /* [29]  */
        unsigned int dither_mode : 1; /* [30]  */
        unsigned int dither_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_dither_ctrl;

/* define the union reg_wbc_me_dither_coef0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_coef0 : 8; /* [7..0]  */
        unsigned int dither_coef1 : 8; /* [15..8]  */
        unsigned int dither_coef2 : 8; /* [23..16]  */
        unsigned int dither_coef3 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_dither_coef0;

/* define the union reg_wbc_me_dither_coef1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_coef4 : 8; /* [7..0]  */
        unsigned int dither_coef5 : 8; /* [15..8]  */
        unsigned int dither_coef6 : 8; /* [23..16]  */
        unsigned int dither_coef7 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_dither_coef1;

/* define the union reg_wbc_me_zme_hsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 24; /* [23..0]  */
        unsigned int hfir_order : 1; /* [24]  */
        unsigned int hchfir_en : 1; /* [25]  */
        unsigned int hlfir_en : 1; /* [26]  */
        unsigned int reserved_0 : 1; /* [27]  */
        unsigned int hchmid_en : 1; /* [28]  */
        unsigned int hlmid_en : 1; /* [29]  */
        unsigned int hchmsc_en : 1; /* [30]  */
        unsigned int hlmsc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_hsp;

/* define the union reg_wbc_me_zme_hloffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hor_loffset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_hloffset;

/* define the union reg_wbc_me_zme_hcoffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hor_coffset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_hcoffset;

/* define the union reg_wbc_me_zme_vsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 19; /* [18..0]  */
        unsigned int zme_in_fmt : 2; /* [20..19]  */
        unsigned int zme_out_fmt : 2; /* [22..21]  */
        unsigned int vchfir_en : 1; /* [23]  */
        unsigned int vlfir_en : 1; /* [24]  */
        unsigned int reserved_1 : 3; /* [27..25]  */
        unsigned int vchmid_en : 1; /* [28]  */
        unsigned int vlmid_en : 1; /* [29]  */
        unsigned int vchmsc_en : 1; /* [30]  */
        unsigned int vlmsc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_vsp;

/* define the union reg_wbc_me_zme_vsr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_vsr;

/* define the union reg_wbc_me_zme_voffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int vluma_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_voffset;

/* define the union reg_wbc_me_zme_vboffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int vbluma_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_me_zme_vboffset;

/* define the union reg_wbc_fi_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 3; /* [12..10]  */
        unsigned int addr_mode : 1; /* [13]  */
        unsigned int fsize_mode : 1; /* [14]  */
        unsigned int tnr_nrds_en : 1; /* [15]  */
        unsigned int reserved_1 : 4; /* [19..16]  */
        unsigned int ofl_master : 1; /* [20]  */
        unsigned int data_width : 1; /* [21]  */
        unsigned int reserved_2 : 2; /* [23..22]  */
        unsigned int format_out : 4; /* [27..24]  */
        unsigned int reserved_3 : 2; /* [29..28]  */
        unsigned int cmp_en : 1; /* [30]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_ctrl;

/* define the union reg_wbc_fi_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_upd;

/* define the union reg_wbc_fi_wlen_sel */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlen_sel : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_wlen_sel;

/* define the union reg_wbc_fi_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbclstride : 16; /* [15..0]  */
        unsigned int wbccstride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_stride;

/* define the union reg_wbc_fi_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12; /* [11..0]  */
        unsigned int oh : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_oreso;

/* define the union reg_wbc_fi_smmu_bypass */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_bypass : 1; /* [0]  */
        unsigned int c_bypass : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_smmu_bypass;

/* define the union reg_wbc_fi_frame_size */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size : 23; /* [22..0]  */
        unsigned int reserved_0 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_frame_size;

/* define the union reg_wbc_fi_hcds */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29; /* [28..0]  */
        unsigned int hchfir_en : 1; /* [29]  */
        unsigned int hchmid_en : 1; /* [30]  */
        unsigned int hcds_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_hcds;

/* define the union reg_wbc_fi_hcds_coef0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10; /* [9..0]  */
        unsigned int coef1 : 10; /* [19..10]  */
        unsigned int coef2 : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_hcds_coef0;

/* define the union reg_wbc_fi_hcds_coef1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef3 : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_hcds_coef1;

/* define the union reg_wbc_fi_cmp_mb */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_mb;

/* define the union reg_wbc_fi_cmp_max_min */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int min_bits_cnt : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int max_bits_cnt : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_max_min;

/* define the union reg_wbc_fi_cmp_adj_thr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int adj_sad_thr : 12; /* [11..0]  */
        unsigned int reserved_0 : 4; /* [15..12]  */
        unsigned int adj_sad_bit_thr : 8; /* [23..16]  */
        unsigned int adj_spec_bit_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_adj_thr;

/* define the union reg_wbc_fi_cmp_big_grad */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int big_grad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 1; /* [7]  */
        unsigned int big_grad_num_thr : 5; /* [12..8]  */
        unsigned int reserved_1 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_big_grad;

/* define the union reg_wbc_fi_cmp_blk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_thr : 6; /* [5..0]  */
        unsigned int reserved_0 : 2; /* [7..6]  */
        unsigned int blk_comp_thr : 3; /* [10..8]  */
        unsigned int reserved_1 : 21; /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_blk;

/* define the union reg_wbc_fi_cmp_graphic_judge */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int graphic_en : 1; /* [0]  */
        unsigned int reserved_0 : 15; /* [15..1]  */
        unsigned int video_sad_thr : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_graphic_judge;

/* define the union reg_wbc_fi_cmp_rc */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int sadbits_ngain : 3; /* [2..0]  */
        unsigned int reserved_0 : 5; /* [7..3]  */
        unsigned int rc_smth_gain : 3; /* [10..8]  */
        unsigned int reserved_1 : 5; /* [15..11]  */
        unsigned int max_trow_bits : 6; /* [21..16]  */
        unsigned int reserved_2 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_rc;

/* define the union reg_wbc_fi_cmp_frame_size */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size : 21; /* [20..0]  */
        unsigned int reserved_0 : 11; /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_fi_cmp_frame_size;

/* define the union reg_wbc_cmp_glb_info */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int is_lossless : 1; /* [0]  */
        unsigned int cmp_mode : 1; /* [1]  */
        unsigned int dw_mode : 1; /* [2]  */
        unsigned int sep_cmp_en : 1; /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_glb_info;

/* define the union reg_wbc_cmp_framesize */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 13; /* [12..0]  */
        unsigned int reserved_0 : 3; /* [15..13]  */
        unsigned int frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3; /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_framesize;

/* define the union reg_wbc_cmp_rc_cfg0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits_y : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int min_mb_bits_y : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg0;

/* define the union reg_wbc_cmp_rc_cfg2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_qp_y : 4; /* [3..0]  */
        unsigned int reserved_0 : 4; /* [7..4]  */
        unsigned int sad_bits_ngain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4; /* [15..12]  */
        unsigned int rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5; /* [23..19]  */
        unsigned int max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg2;

/* define the union reg_wbc_cmp_rc_cfg3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9; /* [15..7]  */
        unsigned int min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg3;

/* define the union reg_wbc_cmp_rc_cfg4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 1; /* [7]  */
        unsigned int still_thr : 7; /* [14..8]  */
        unsigned int reserved_1 : 1; /* [15]  */
        unsigned int big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg4;

/* define the union reg_wbc_cmp_rc_cfg5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_pix_num_thr : 6; /* [5..0]  */
        unsigned int reserved_0 : 2; /* [7..6]  */
        unsigned int still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2; /* [15..14]  */
        unsigned int noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg5;

/* define the union reg_wbc_cmp_rc_cfg6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int noise_sad : 7; /* [6..0]  */
        unsigned int reserved_0 : 9; /* [15..7]  */
        unsigned int pix_diff_thr : 9; /* [24..16]  */
        unsigned int reserved_1 : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg6;

/* define the union reg_wbc_cmp_rc_cfg7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25; /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg7;

/* define the union reg_wbc_cmp_rc_cfg8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int qp_inc1_bits_thr_y : 8; /* [7..0]  */
        unsigned int qp_inc2_bits_thr_y : 8; /* [15..8]  */
        unsigned int qp_dec1_bits_thr_y : 8; /* [23..16]  */
        unsigned int qp_dec2_bits_thr_y : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg8;

/* define the union reg_wbc_cmp_rc_cfg10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int est_err_gain : 5; /* [4..0]  */
        unsigned int reserved_0 : 11; /* [15..5]  */
        unsigned int max_est_err_level : 9; /* [24..16]  */
        unsigned int max_vbv_buf_loss_thr : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_rc_cfg10;

/* define the union reg_wbc_cmp_outsize0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size0_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_outsize0;

/* define the union reg_wbc_cmp_max_row */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size1_reg : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_max_row;

/* define the union reg_wbc_bmp_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 10; /* [19..10]  */
        unsigned int ofl_master : 1; /* [20]  */
        unsigned int data_width : 1; /* [21]  */
        unsigned int reserved_1 : 2; /* [23..22]  */
        unsigned int format_out : 4; /* [27..24]  */
        unsigned int reserved_2 : 3; /* [30..28]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_bmp_ctrl;

/* define the union reg_wbc_bmp_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_bmp_upd;

/* define the union reg_wbc_bmp_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12; /* [11..0]  */
        unsigned int oh : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_bmp_oreso;

/* define the union reg_wbc_bmp_sum */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bmp_sum : 25; /* [24..0]  */
        unsigned int reserved_0 : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_bmp_sum;

/* define the union reg_wbc_dhd0_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int p2i_en : 1; /* [0]  */
        unsigned int root_path : 2; /* [2..1]  */
        unsigned int reserved_0 : 19; /* [21..3]  */
        unsigned int mode_out : 2; /* [23..22]  */
        unsigned int three_d_mode : 2; /* [25..24]  */
        unsigned int auto_stop_en : 1; /* [26]  */
        unsigned int wbc_vtthd_mode : 1; /* [27]  */
        unsigned int rupd_field : 1; /* [28]  */
        unsigned int rgup_mode : 1; /* [29]  */
        unsigned int nosec_flag : 1; /* [30]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_dhd0_ctrl;

/* define the union reg_wbc_dhd0_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_dhd0_upd;

/* define the union reg_wbc_dhd0_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_dhd0_oreso;

/* define the union reg_wd_hpzme_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_en : 1; /* [0]  */
        unsigned int hfir_mode : 2; /* [2..1]  */
        unsigned int mid_en : 1; /* [3]  */
        unsigned int ck_gt_en : 1; /* [4]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hpzme_ctrl;

/* define the union reg_wd_hpzmecoef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6; /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hpzmecoef01;

/* define the union reg_wd_hpzmecoef23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6; /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hpzmecoef23;

/* define the union reg_wd_hpzmecoef45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6; /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hpzmecoef45;

/* define the union reg_wd_hpzmecoef67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6; /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hpzmecoef67;

/* define the union reg_wd_hcds_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_en : 1; /* [0]  */
        unsigned int hfir_mode : 2; /* [2..1]  */
        unsigned int mid_en : 1; /* [3]  */
        unsigned int ck_gt_en : 1; /* [4]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hcds_ctrl;

/* define the union reg_wd_hcdscoef01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hcdscoef01;

/* define the union reg_wd_hcdscoef23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hcdscoef23;

/* define the union reg_wd_hcdscoef45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6; /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hcdscoef45;

/* define the union reg_wd_hcdscoef67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6; /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_hcdscoef67;

/* define the union reg_dither_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_tap_mode : 2; /* [1..0]  */
        unsigned int dither_domain_mode : 1; /* [2]  */
        unsigned int dither_round : 1; /* [3]  */
        unsigned int dither_mode : 1; /* [4]  */
        unsigned int dither_en : 1; /* [5]  */
        unsigned int dither_round_unlim : 1; /* [6]  */
        unsigned int i_data_width_dither : 3; /* [9..7]  */
        unsigned int o_data_width_dither : 3; /* [12..10]  */
        unsigned int reserved_0 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_ctrl;

/* define the union reg_dither_sed_y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_y0;

/* define the union reg_dither_sed_u0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_u0;

/* define the union reg_dither_sed_v0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_v0;

/* define the union reg_dither_sed_w0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_w0;

/* define the union reg_dither_sed_y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_y1;

/* define the union reg_dither_sed_u1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_u1;

/* define the union reg_dither_sed_v1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_v1;

/* define the union reg_dither_sed_w1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_w1;

/* define the union reg_dither_sed_y2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_y2;

/* define the union reg_dither_sed_u2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_u2;

/* define the union reg_dither_sed_v2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_v2;

/* define the union reg_dither_sed_w2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_w2;

/* define the union reg_dither_sed_y3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_y3;

/* define the union reg_dither_sed_u3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_u3;

/* define the union reg_dither_sed_v3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_v3;

/* define the union reg_dither_sed_w3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_sed_w3;

/* define the union reg_dither_thr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_thr_min : 16; /* [15..0]  */
        unsigned int dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dither_thr;

/* define the union reg_wd_zme_hinfo */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_width : 16; /* [15..0]  */
        unsigned int hzme_ck_gt_en : 1; /* [16]  */
        unsigned int reserved_0 : 15; /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hinfo;

/* define the union reg_wd_zme_hsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 24; /* [23..0]  */
        unsigned int hfir_order : 1; /* [24]  */
        unsigned int chfir_mode : 1; /* [25]  */
        unsigned int lhfir_mode : 1; /* [26]  */
        unsigned int non_lnr_en : 1; /* [27]  */
        unsigned int chmid_en : 1; /* [28]  */
        unsigned int lhmid_en : 1; /* [29]  */
        unsigned int chfir_en : 1; /* [30]  */
        unsigned int lhfir_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hsp;

/* define the union reg_wd_zme_hloffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lhfir_offset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hloffset;

/* define the union reg_wd_zme_hcoffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chfir_offset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hcoffset;

/* define the union reg_wd_zme_hcoef_ren */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_hf_cren : 1; /* [0]  */
        unsigned int apb_vhd_hf_lren : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hcoef_ren;

/* define the union reg_wd_zme_hcoef_rdata */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_hcoef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hcoef_rdata;

/* define the union reg_wd_zme_hdraw */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hdraw_mode : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hdraw;

/* define the union reg_wd_zme_hratio */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 27; /* [26..0]  */
        unsigned int reserved_0 : 5; /* [31..27]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_hratio;

/* define the union reg_wd_zme_vinfo */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16; /* [15..0]  */
        unsigned int out_fmt : 2; /* [17..16]  */
        unsigned int out_pro : 1; /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vinfo;

/* define the union reg_wd_zme_vsp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16; /* [15..0]  */
        unsigned int graphdet_en : 1; /* [16]  */
        unsigned int reserved_1 : 8; /* [24..17]  */
        unsigned int cvfir_mode : 1; /* [25]  */
        unsigned int lvfir_mode : 1; /* [26]  */
        unsigned int vfir_1tap_en : 1; /* [27]  */
        unsigned int cvmid_en : 1; /* [28]  */
        unsigned int lvmid_en : 1; /* [29]  */
        unsigned int cvfir_en : 1; /* [30]  */
        unsigned int lvfir_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vsp;

/* define the union reg_wd_zme_voffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int vluma_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_voffset;

/* define the union reg_wd_zme_vboffset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int vbluma_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vboffset;

/* define the union reg_wd_zme_vcoef_ren */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_vf_cren : 1; /* [0]  */
        unsigned int apb_vhd_vf_lren : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vcoef_ren;

/* define the union reg_wd_zme_vcoef_rdata */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_vcoef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vcoef_rdata;

/* define the union reg_wd_zme_vdraw */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vdraw_mode : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vdraw;

/* define the union reg_wd_zme_vratio */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 19; /* [18..0]  */
        unsigned int reserved_0 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wd_zme_vratio;

/* define the union reg_dhd0_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int disp_mode : 3; /* [3..1]  */
        unsigned int iop : 1; /* [4]  */
        unsigned int intf_ivs : 1; /* [5]  */
        unsigned int intf_ihs : 1; /* [6]  */
        unsigned int intf_idv : 1; /* [7]  */
        unsigned int reserved_0 : 1; /* [8]  */
        unsigned int hdmi420c_sel : 1; /* [9]  */
        unsigned int hdmi420_en : 1; /* [10]  */
        unsigned int uf_offline_en : 1; /* [11]  */
        unsigned int reserved_1 : 2; /* [13..12]  */
        unsigned int hdmi_mode : 1; /* [14]  */
        unsigned int twochn_debug : 1; /* [15]  */
        unsigned int twochn_en : 1; /* [16]  */
        unsigned int reserved_2 : 1; /* [17]  */
        unsigned int cbar_mode : 1; /* [18]  */
        unsigned int sin_en : 1; /* [19]  */
        unsigned int fpga_lmt_width : 7; /* [26..20]  */
        unsigned int fpga_lmt_en : 1; /* [27]  */
        unsigned int p2i_en : 1; /* [28]  */
        unsigned int cbar_sel : 1; /* [29]  */
        unsigned int cbar_en : 1; /* [30]  */
        unsigned int intf_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_ctrl;

/* define the union reg_dhd0_vsync1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vact : 16; /* [15..0]  */
        unsigned int vbb : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vsync1;

/* define the union reg_dhd0_vsync2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vfb : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vsync2;

/* define the union reg_dhd0_hsync1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hact : 16; /* [15..0]  */
        unsigned int hbb : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_hsync1;

/* define the union reg_dhd0_hsync2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfb : 16; /* [15..0]  */
        unsigned int hmid : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_hsync2;

/* define the union reg_dhd0_vplus1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bvact : 16; /* [15..0]  */
        unsigned int bvbb : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vplus1;

/* define the union reg_dhd0_vplus2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bvfb : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vplus2;

/* define the union reg_dhd0_pwr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hpw : 16; /* [15..0]  */
        unsigned int vpw : 8; /* [23..16]  */
        unsigned int reserved_0 : 3; /* [26..24]  */
        unsigned int multichn_en : 2; /* [28..27]  */
        unsigned int reserved_1 : 3; /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_pwr;

/* define the union reg_dhd0_vtthd3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vtmgthd3 : 13; /* [12..0]  */
        unsigned int reserved_0 : 2; /* [14..13]  */
        unsigned int thd3_mode : 1; /* [15]  */
        unsigned int vtmgthd4 : 13; /* [28..16]  */
        unsigned int reserved_1 : 2; /* [30..29]  */
        unsigned int thd4_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vtthd3;

/* define the union reg_dhd0_vtthd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vtmgthd1 : 13; /* [12..0]  */
        unsigned int reserved_0 : 2; /* [14..13]  */
        unsigned int thd1_mode : 1; /* [15]  */
        unsigned int vtmgthd2 : 13; /* [28..16]  */
        unsigned int reserved_1 : 2; /* [30..29]  */
        unsigned int thd2_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vtthd;

/* define the union reg_dhd0_parathd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_thd : 8; /* [7..0]  */
        unsigned int reserved_0 : 23; /* [30..8]  */
        unsigned int dfs_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_parathd;

/* define the union reg_dhd0_precharge_thd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tcon_precharge_thd : 17; /* [16..0]  */
        unsigned int reserved_0 : 3; /* [19..17]  */
        unsigned int vsync_te_mode : 1; /* [20]  ---- */
        unsigned int reserved_1 : 11; /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_precharge_thd;

/* define the union reg_dhd0_start_pos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int start_pos : 8; /* [7..0]  */
        unsigned int timing_start_pos : 8; /* [15..8]  */
        unsigned int fi_start_pos : 4; /* [19..16]  */
        unsigned int req_start_pos : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_start_pos;

/* define the union reg_dhd0_start_pos1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_start_pos1 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_start_pos1;

/* define the union reg_dhd0_paraup */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int paraup_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_paraup;

/* define the union reg_dhd0_sync_inv */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lcd_dv_inv : 1; /* [0]  */
        unsigned int lcd_hs_inv : 1; /* [1]  */
        unsigned int lcd_vs_inv : 1; /* [2]  */
        unsigned int reserved_0 : 1; /* [3]  */
        unsigned int vga_dv_inv : 1; /* [4]  */
        unsigned int vga_hs_inv : 1; /* [5]  */
        unsigned int vga_vs_inv : 1; /* [6]  */
        unsigned int reserved_1 : 1; /* [7]  */
        unsigned int hdmi_dv_inv : 1; /* [8]  */
        unsigned int hdmi_hs_inv : 1; /* [9]  */
        unsigned int hdmi_vs_inv : 1; /* [10]  */
        unsigned int hdmi_f_inv : 1; /* [11]  */
        unsigned int date_dv_inv : 1; /* [12]  */
        unsigned int date_hs_inv : 1; /* [13]  */
        unsigned int date_vs_inv : 1; /* [14]  */
        unsigned int date_f_inv : 1; /* [15]  */
        unsigned int reserved_2 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_sync_inv;

/* define the union reg_dhd0_clk_dv_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int intf_clk_mux : 1; /* [0]  */
        unsigned int intf_dv_mux : 1; /* [1]  */
        unsigned int no_active_area_pos : 16; /* [17..2]  */
        unsigned int reserved_0 : 14; /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_clk_dv_ctrl;

/* define the union reg_dhd0_rgb_fix_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int fix_b : 10; /* [9..0]  */
        unsigned int fix_g : 10; /* [19..10]  */
        unsigned int fix_r : 10; /* [29..20]  */
        unsigned int rgb_fix_mux : 1; /* [30]  */
        unsigned int reserved_0 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_rgb_fix_ctrl;

/* define the union reg_dhd0_lockcfg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int measure_en : 1; /* [0]  */
        unsigned int lock_cnt_en : 1; /* [1]  */
        unsigned int vdp_measure_en : 1; /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_lockcfg;

/* define the union reg_dhd0_intf_chksum_high1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int r0_sum_high : 8; /* [7..0]  */
        unsigned int g0_sum_high : 8; /* [15..8]  */
        unsigned int b0_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_intf_chksum_high1;

/* define the union reg_dhd0_intf_chksum_high2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int r1_sum_high : 8; /* [7..0]  */
        unsigned int g1_sum_high : 8; /* [15..8]  */
        unsigned int b1_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_intf_chksum_high2;

/* define the union reg_dhd0_state */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vback_blank : 1; /* [0]  */
        unsigned int vblank : 1; /* [1]  */
        unsigned int bottom_field : 1; /* [2]  */
        unsigned int vcnt : 13; /* [15..3]  */
        unsigned int count_int : 8; /* [23..16]  */
        unsigned int dhd_even : 1; /* [24]  */
        unsigned int reserved_0 : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_state;

/* define the union reg_dhd0_uf_state */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ud_first_cnt : 13; /* [12..0]  */
        unsigned int reserved_0 : 3; /* [15..13]  */
        unsigned int start_pos : 8; /* [23..16]  */
        unsigned int reserved_1 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_uf_state;

/* define the union reg_vo_mux */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mipi_sel : 4; /* [3..0]  */
        unsigned int lcd_sel : 4; /* [7..4]  */
        unsigned int bt_sel : 4; /* [11..8]  */
        unsigned int sddate_sel : 4; /* [15..12]  */
        unsigned int hdmi_sel : 4; /* [19..16]  */
        unsigned int hdmi1_sel : 4; /* [23..20]  */
        unsigned int vga_sel : 4; /* [27..24]  */
        unsigned int digital_sel : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vo_mux;

/* define the union reg_vo_mux_sync */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int sync_dv : 1; /* [0]  */
        unsigned int sync_hsync : 1; /* [1]  */
        unsigned int sync_vsync : 1; /* [2]  */
        unsigned int sync_field : 1; /* [3]  */
        unsigned int reserved_0 : 27; /* [30..4]  */
        unsigned int sync_test_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vo_mux_sync;

/* define the union reg_vo_mux_data */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vomux_data : 30; /* [29..0]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vo_mux_data;

/* define the union reg_dhd0_vsync_te_state */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vsync_te_start_sta : 8; /* [7..0]  */
        unsigned int vsync_te_start_sta1 : 8; /* [15..8]  */
        unsigned int vsync_te_end_sta : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vsync_te_state;

/* define the union reg_dhd0_vsync_te_state1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vsync_te_vfb : 16; /* [15..0]  */
        unsigned int vsync_te_width : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_dhd0_vsync_te_state1;

typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    img_mode              : 7  ; /* [6..0]  */
        unsigned int    img_right             : 1  ; /* [7]  */
        unsigned int    img_id                : 2  ; /* [9..8]  */
        unsigned int    slave_mode            : 1  ; /* [10]  */
        unsigned int    ccd_en                : 1  ; /* [11]  */
        unsigned int    reserved_0            : 4  ; /* [15..12]  */
        unsigned int    vbi_pos               : 8  ; /* [23..16]  */
        unsigned int    reserved_1            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_ccdoimgmod;

/* Define the union reg_dhd0_ccdoposmskh */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    p32_en                : 1  ; /* [0]  */
        unsigned int    p33_en                : 1  ; /* [1]  */
        unsigned int    p34_en                : 1  ; /* [2]  */
        unsigned int    p35_en                : 1  ; /* [3]  */
        unsigned int    p36_en                : 1  ; /* [4]  */
        unsigned int    p37_en                : 1  ; /* [5]  */
        unsigned int    p38_en                : 1  ; /* [6]  */
        unsigned int    p39_en                : 1  ; /* [7]  */
        unsigned int    p40_en                : 1  ; /* [8]  */
        unsigned int    p41_en                : 1  ; /* [9]  */
        unsigned int    p42_en                : 1  ; /* [10]  */
        unsigned int    p43_en                : 1  ; /* [11]  */
        unsigned int    p44_en                : 1  ; /* [12]  */
        unsigned int    p45_en                : 1  ; /* [13]  */
        unsigned int    p46_en                : 1  ; /* [14]  */
        unsigned int    p47_en                : 1  ; /* [15]  */
        unsigned int    p48_en                : 1  ; /* [16]  */
        unsigned int    p49_en                : 1  ; /* [17]  */
        unsigned int    p50_en                : 1  ; /* [18]  */
        unsigned int    p51_en                : 1  ; /* [19]  */
        unsigned int    p52_en                : 1  ; /* [20]  */
        unsigned int    p53_en                : 1  ; /* [21]  */
        unsigned int    p54_en                : 1  ; /* [22]  */
        unsigned int    p55_en                : 1  ; /* [23]  */
        unsigned int    p56_en                : 1  ; /* [24]  */
        unsigned int    p57_en                : 1  ; /* [25]  */
        unsigned int    p58_en                : 1  ; /* [26]  */
        unsigned int    p59_en                : 1  ; /* [27]  */
        unsigned int    p60_en                : 1  ; /* [28]  */
        unsigned int    p61_en                : 1  ; /* [29]  */
        unsigned int    p62_en                : 1  ; /* [30]  */
        unsigned int    p63_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_ccdoposmskh;

/* Define the union reg_dhd0_ccdoposmskl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    p0_en                 : 1  ; /* [0]  */
        unsigned int    p1_en                 : 1  ; /* [1]  */
        unsigned int    p2_en                 : 1  ; /* [2]  */
        unsigned int    p3_en                 : 1  ; /* [3]  */
        unsigned int    p4_en                 : 1  ; /* [4]  */
        unsigned int    p5_en                 : 1  ; /* [5]  */
        unsigned int    p6_en                 : 1  ; /* [6]  */
        unsigned int    p7_en                 : 1  ; /* [7]  */
        unsigned int    p8_en                 : 1  ; /* [8]  */
        unsigned int    p9_en                 : 1  ; /* [9]  */
        unsigned int    p10_en                : 1  ; /* [10]  */
        unsigned int    p11_en                : 1  ; /* [11]  */
        unsigned int    p12_en                : 1  ; /* [12]  */
        unsigned int    p13_en                : 1  ; /* [13]  */
        unsigned int    p14_en                : 1  ; /* [14]  */
        unsigned int    p15_en                : 1  ; /* [15]  */
        unsigned int    p16_en                : 1  ; /* [16]  */
        unsigned int    p17_en                : 1  ; /* [17]  */
        unsigned int    p18_en                : 1  ; /* [18]  */
        unsigned int    p19_en                : 1  ; /* [19]  */
        unsigned int    p20_en                : 1  ; /* [20]  */
        unsigned int    p21_en                : 1  ; /* [21]  */
        unsigned int    p22_en                : 1  ; /* [22]  */
        unsigned int    p23_en                : 1  ; /* [23]  */
        unsigned int    p24_en                : 1  ; /* [24]  */
        unsigned int    p25_en                : 1  ; /* [25]  */
        unsigned int    p26_en                : 1  ; /* [26]  */
        unsigned int    p27_en                : 1  ; /* [27]  */
        unsigned int    p28_en                : 1  ; /* [28]  */
        unsigned int    p29_en                : 1  ; /* [29]  */
        unsigned int    p30_en                : 1  ; /* [30]  */
        unsigned int    p31_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_ccdoposmskl;

/* Define the union reg_dhd0_dacdet1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vdac_det_high         : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    det_line              : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_dacdet1;

/* Define the union reg_dhd0_dacdet2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    det_pixel_sta         : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    det_pixel_wid         : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 4  ; /* [30..27]  */
        unsigned int    vdac_det_en           : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_dacdet2;

/* Define the union reg_dhd0_ccd_info1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    img_mode              : 7  ; /* [6..0]  */
        unsigned int    img_right             : 1  ; /* [7]  */
        unsigned int    img_id                : 2  ; /* [9..8]  */
        unsigned int    reserved_0            : 1  ; /* [10]  */
        unsigned int    ccd_en                : 1  ; /* [11]  */
        unsigned int    reserved_1            : 20 ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_ccd_info1;

/* Define the union reg_dhd0_ccd_info2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    p32_en                : 1  ; /* [0]  */
        unsigned int    p33_en                : 1  ; /* [1]  */
        unsigned int    p34_en                : 1  ; /* [2]  */
        unsigned int    p35_en                : 1  ; /* [3]  */
        unsigned int    p36_en                : 1  ; /* [4]  */
        unsigned int    p37_en                : 1  ; /* [5]  */
        unsigned int    p38_en                : 1  ; /* [6]  */
        unsigned int    p39_en                : 1  ; /* [7]  */
        unsigned int    p40_en                : 1  ; /* [8]  */
        unsigned int    p41_en                : 1  ; /* [9]  */
        unsigned int    p42_en                : 1  ; /* [10]  */
        unsigned int    p43_en                : 1  ; /* [11]  */
        unsigned int    p44_en                : 1  ; /* [12]  */
        unsigned int    p45_en                : 1  ; /* [13]  */
        unsigned int    p46_en                : 1  ; /* [14]  */
        unsigned int    p47_en                : 1  ; /* [15]  */
        unsigned int    p48_en                : 1  ; /* [16]  */
        unsigned int    p49_en                : 1  ; /* [17]  */
        unsigned int    p50_en                : 1  ; /* [18]  */
        unsigned int    p51_en                : 1  ; /* [19]  */
        unsigned int    p52_en                : 1  ; /* [20]  */
        unsigned int    p53_en                : 1  ; /* [21]  */
        unsigned int    p54_en                : 1  ; /* [22]  */
        unsigned int    p55_en                : 1  ; /* [23]  */
        unsigned int    p56_en                : 1  ; /* [24]  */
        unsigned int    p57_en                : 1  ; /* [25]  */
        unsigned int    p58_en                : 1  ; /* [26]  */
        unsigned int    p59_en                : 1  ; /* [27]  */
        unsigned int    p60_en                : 1  ; /* [28]  */
        unsigned int    p61_en                : 1  ; /* [29]  */
        unsigned int    p62_en                : 1  ; /* [30]  */
        unsigned int    p63_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_ccd_info2;

/* Define the union reg_dhd0_ccd_info3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    p0_en                 : 1  ; /* [0]  */
        unsigned int    p1_en                 : 1  ; /* [1]  */
        unsigned int    p2_en                 : 1  ; /* [2]  */
        unsigned int    p3_en                 : 1  ; /* [3]  */
        unsigned int    p4_en                 : 1  ; /* [4]  */
        unsigned int    p5_en                 : 1  ; /* [5]  */
        unsigned int    p6_en                 : 1  ; /* [6]  */
        unsigned int    p7_en                 : 1  ; /* [7]  */
        unsigned int    p8_en                 : 1  ; /* [8]  */
        unsigned int    p9_en                 : 1  ; /* [9]  */
        unsigned int    p10_en                : 1  ; /* [10]  */
        unsigned int    p11_en                : 1  ; /* [11]  */
        unsigned int    p12_en                : 1  ; /* [12]  */
        unsigned int    p13_en                : 1  ; /* [13]  */
        unsigned int    p14_en                : 1  ; /* [14]  */
        unsigned int    p15_en                : 1  ; /* [15]  */
        unsigned int    p16_en                : 1  ; /* [16]  */
        unsigned int    p17_en                : 1  ; /* [17]  */
        unsigned int    p18_en                : 1  ; /* [18]  */
        unsigned int    p19_en                : 1  ; /* [19]  */
        unsigned int    p20_en                : 1  ; /* [20]  */
        unsigned int    p21_en                : 1  ; /* [21]  */
        unsigned int    p22_en                : 1  ; /* [22]  */
        unsigned int    p23_en                : 1  ; /* [23]  */
        unsigned int    p24_en                : 1  ; /* [24]  */
        unsigned int    p25_en                : 1  ; /* [25]  */
        unsigned int    p26_en                : 1  ; /* [26]  */
        unsigned int    p27_en                : 1  ; /* [27]  */
        unsigned int    p28_en                : 1  ; /* [28]  */
        unsigned int    p29_en                : 1  ; /* [29]  */
        unsigned int    p30_en                : 1  ; /* [30]  */
        unsigned int    p31_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd0_ccd_info3;

/* Define the union reg_intf_hdmi_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    intf_422_en           : 1  ; /* [0]  */
        unsigned int    intf_420_en           : 1  ; /* [1]  */
        unsigned int    intf_420_mode         : 2  ; /* [3..2]  */
        unsigned int    hdmi_mode             : 2  ; /* [5..4]  */
        unsigned int    reserved_0            : 26 ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_hdmi_ctrl;

/* Define the union reg_intf_hdmi_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_hdmi_upd;

/* Define the union reg_intf_hdmi_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_hdmi_sync_inv;

/* Define the union reg_hdmi_intf_chksum_high */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    r0_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b0_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_intf_chksum_high;

/* Define the union reg_hdmi_intf1_chksum_high */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    r1_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g1_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b1_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_intf1_chksum_high;

/* Define the union reg_hdmi_hfir_coef0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef0            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef1            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_hfir_coef0;

/* Define the union reg_hdmi_hfir_coef1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef2            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef3            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_hfir_coef1;

/* Define the union reg_hdmi_hfir_coef2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef4            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef5            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_hfir_coef2;

/* Define the union reg_hdmi_hfir_coef3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef6            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 22 ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_hfir_coef3;

/* Define the union reg_hdmi_csc_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_idc;

/* Define the union reg_hdmi_csc_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_odc;

/* Define the union reg_hdmi_csc_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_iodc;

/* Define the union reg_hdmi_csc_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_p0;

/* Define the union reg_hdmi_csc_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_p1;

/* Define the union reg_hdmi_csc_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_p2;

/* Define the union reg_hdmi_csc_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_p3;

/* Define the union reg_hdmi_csc_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi_csc_p4;

/* Define the union reg_intf_mipi_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    intf_422_en           : 1  ; /* [0]  */
        unsigned int    intf_420_en           : 1  ; /* [1]  */
        unsigned int    intf_420_mode         : 2  ; /* [3..2]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_mipi_ctrl;

/* Define the union reg_intf_mipi_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_mipi_upd;

/* Define the union reg_intf_mipi_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_mipi_sync_inv;

/* Define the union reg_mipi_intf_chksum_high */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    b0_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8  ; /* [15..8]  */
        unsigned int    r0_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_mipi_intf_chksum_high;

/* Define the union reg_mipi_intf1_chksum_high */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    b1_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g1_sum_high           : 8  ; /* [15..8]  */
        unsigned int    r1_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_mipi_intf1_chksum_high;

/* Define the union reg_mipi_hfir_coef0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef0            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef1            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_mipi_hfir_coef0;

/* Define the union reg_mipi_hfir_coef1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef2            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef3            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_mipi_hfir_coef1;

/* Define the union reg_mipi_hfir_coef2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef4            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef5            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_mipi_hfir_coef2;

/* Define the union reg_mipi_hfir_coef3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef6            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 22 ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_mipi_hfir_coef3;

/* Define the union reg_intf_bt_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 16 ; /* [15..0]  */
        unsigned int    data_width            : 1  ; /* [16]  */
        unsigned int    bit_inv               : 1  ; /* [17]  */
        unsigned int    uv_mode               : 1  ; /* [18]  */
        unsigned int    yc_mode               : 1  ; /* [19]  */
        unsigned int    reserved_1            : 10 ; /* [29..20]  */
        unsigned int    dfir_en               : 1  ; /* [30]  */
        unsigned int    hdmi_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_bt_ctrl;

/* Define the union reg_intf_bt_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_bt_upd;

/* Define the union reg_intf_bt_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_bt_sync_inv;

/* Define the union reg_bt_clip0_l */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    clip_cl0              : 10 ; /* [9..0]  */
        unsigned int    clip_cl1              : 10 ; /* [19..10]  */
        unsigned int    clip_cl2              : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 1  ; /* [30]  */
        unsigned int    clip_en               : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_clip0_l;

/* Define the union reg_bt_clip0_h */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    clip_ch0              : 10 ; /* [9..0]  */
        unsigned int    clip_ch1              : 10 ; /* [19..10]  */
        unsigned int    clip_ch2              : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_clip0_h;

/* Define the union reg_bt_dither_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_tap_mode       : 2  ; /* [1..0]  */
        unsigned int    dither_domain_mode    : 1  ; /* [2]  */
        unsigned int    dither_round          : 1  ; /* [3]  */
        unsigned int    dither_mode           : 1  ; /* [4]  */
        unsigned int    dither_en             : 1  ; /* [5]  */
        unsigned int    dither_round_unlim    : 1  ; /* [6]  */
        unsigned int    i_data_width_dither   : 3  ; /* [9..7]  */
        unsigned int    o_data_width_dither   : 3  ; /* [12..10]  */
        unsigned int    reserved_0            : 19 ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_ctrl;

/* Define the union reg_bt_dither_sed_y0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_y0;

/* Define the union reg_bt_dither_sed_u0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_u0;

/* Define the union reg_bt_dither_sed_v0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_v0;

/* Define the union reg_bt_dither_sed_w0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_w0;

/* Define the union reg_bt_dither_sed_y1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_y1;

/* Define the union reg_bt_dither_sed_u1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_u1;

/* Define the union reg_bt_dither_sed_v1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_v1;

/* Define the union reg_bt_dither_sed_w1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_w1;

/* Define the union reg_bt_dither_sed_y2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_y2;

/* Define the union reg_bt_dither_sed_u2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_u2;

/* Define the union reg_bt_dither_sed_v2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_v2;

/* Define the union reg_bt_dither_sed_w2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_w2;

/* Define the union reg_bt_dither_sed_y3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_y3;

/* Define the union reg_bt_dither_sed_u3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_u3;

/* Define the union reg_bt_dither_sed_v3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_v3;

/* Define the union reg_bt_dither_sed_w3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_sed_w3;

/* Define the union reg_bt_dither_thr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_thr_min        : 16 ; /* [15..0]  */
        unsigned int    dither_thr_max        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_bt_dither_thr;

/* Define the union reg_intf_lcd_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 20 ; /* [19..0]  */
        unsigned int    lcd_format            : 4  ; /* [23..20]  */
        unsigned int    lcd_bit_inv           : 1  ; /* [24]  */
        unsigned int    lcd_comp_order        : 1  ; /* [25]  */
        unsigned int    lcd_serial_perd       : 1  ; /* [26]  */
        unsigned int    reserved_1            : 3  ; /* [29..27]  */
        unsigned int    dfir_en               : 1  ; /* [30]  */
        unsigned int    hdmi_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_lcd_ctrl;

/* Define the union reg_intf_lcd_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_lcd_upd;

/* Define the union reg_intf_lcd_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_lcd_sync_inv;

/* Define the union reg_lcd_dither_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_tap_mode       : 2  ; /* [1..0]  */
        unsigned int    dither_domain_mode    : 1  ; /* [2]  */
        unsigned int    dither_round          : 1  ; /* [3]  */
        unsigned int    dither_mode           : 1  ; /* [4]  */
        unsigned int    dither_en             : 1  ; /* [5]  */
        unsigned int    dither_round_unlim    : 1  ; /* [6]  */
        unsigned int    i_data_width_dither   : 3  ; /* [9..7]  */
        unsigned int    o_data_width_dither   : 3  ; /* [12..10]  */
        unsigned int    reserved_0            : 19 ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_ctrl;

/* Define the union reg_lcd_dither_sed_y0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_y0;

/* Define the union reg_lcd_dither_sed_u0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_u0;

/* Define the union reg_lcd_dither_sed_v0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_v0;

/* Define the union reg_lcd_dither_sed_w0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_w0;

/* Define the union reg_lcd_dither_sed_y1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_y1;

/* Define the union reg_lcd_dither_sed_u1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_u1;

/* Define the union reg_lcd_dither_sed_v1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_v1;

/* Define the union reg_lcd_dither_sed_w1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_w1;

/* Define the union reg_lcd_dither_sed_y2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_y2;

/* Define the union reg_lcd_dither_sed_u2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_u2;

/* Define the union reg_lcd_dither_sed_v2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_v2;

/* Define the union reg_lcd_dither_sed_w2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_w2;

/* Define the union reg_lcd_dither_sed_y3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_y3;

/* Define the union reg_lcd_dither_sed_u3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_u3;

/* Define the union reg_lcd_dither_sed_v3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_v3;

/* Define the union reg_lcd_dither_sed_w3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_sed_w3;

/* Define the union reg_lcd_dither_thr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_thr_min        : 16 ; /* [15..0]  */
        unsigned int    dither_thr_max        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_lcd_dither_thr;

/* Define the union reg_intf_hdmi1_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    intf_422_en           : 1  ; /* [0]  */
        unsigned int    intf_420_en           : 1  ; /* [1]  */
        unsigned int    intf_420_mode         : 2  ; /* [3..2]  */
        unsigned int    hdmi_mode             : 2  ; /* [5..4]  */
        unsigned int    reserved_0            : 26 ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_hdmi1_ctrl;

/* Define the union reg_intf_hdmi1_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_hdmi1_upd;

/* Define the union reg_intf_hdmi1_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_hdmi1_sync_inv;

/* Define the union reg_hdmi1_intf_chksum_high */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    r0_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b0_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi1_intf_chksum_high;

/* Define the union reg_hdmi1_intf1_chksum_high */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    r1_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g1_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b1_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi1_intf1_chksum_high;

/* Define the union reg_hdmi1_hfir_coef0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef0            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef1            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi1_hfir_coef0;

/* Define the union reg_hdmi1_hfir_coef1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef2            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef3            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi1_hfir_coef1;

/* Define the union reg_hdmi1_hfir_coef2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef4            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    hfir_coef5            : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi1_hfir_coef2;

/* Define the union reg_hdmi1_hfir_coef3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfir_coef6            : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 22 ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_hdmi1_hfir_coef3;

/* Define the union reg_intf_vga_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 24 ; /* [23..0]  */
        unsigned int    yc_mode               : 1  ; /* [24]  */
        unsigned int    lcd_parallel_mode     : 1  ; /* [25]  */
        unsigned int    lcd_data_inv          : 1  ; /* [26]  */
        unsigned int    lcd_parallel_order    : 1  ; /* [27]  */
        unsigned int    lcd_serial_perd       : 1  ; /* [28]  */
        unsigned int    lcd_serial_mode       : 1  ; /* [29]  */
        unsigned int    dfir_en               : 1  ; /* [30]  */
        unsigned int    hdmi_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_vga_ctrl;

/* Define the union reg_intf_vga_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_vga_upd;

/* Define the union reg_intf_vga_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_vga_sync_inv;

/* Define the union reg_vga_csc_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_idc;

/* Define the union reg_vga_csc_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_odc;

/* Define the union reg_vga_csc_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_iodc;

/* Define the union reg_vga_csc_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_p0;

/* Define the union reg_vga_csc_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_p1;

/* Define the union reg_vga_csc_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_p2;

/* Define the union reg_vga_csc_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_p3;

/* Define the union reg_vga_csc_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_csc_p4;

/* Define the union reg_vga_hspcfg0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf0_tmp0          : 8  ; /* [7..0]  */
        unsigned int    hsp_hf0_tmp1          : 8  ; /* [15..8]  */
        unsigned int    hsp_hf0_tmp2          : 8  ; /* [23..16]  */
        unsigned int    hsp_hf0_tmp3          : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg0;

/* Define the union reg_vga_hspcfg1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf0_coring        : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 23 ; /* [30..8]  */
        unsigned int    hsp_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg1;

/* Define the union reg_vga_hspcfg5 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf0_gainpos       : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    hsp_hf0_gainneg       : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg5;

/* Define the union reg_vga_hspcfg6 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf0_overth        : 8  ; /* [7..0]  */
        unsigned int    hsp_hf0_underth       : 8  ; /* [15..8]  */
        unsigned int    hsp_hf0_mixratio      : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 4  ; /* [27..24]  */
        unsigned int    hsp_hf0_winsize       : 3  ; /* [30..28]  */
        unsigned int    hsp_hf0_adpshoot_en   : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg6;

/* Define the union reg_vga_hspcfg7 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf1_tmp0          : 8  ; /* [7..0]  */
        unsigned int    hsp_hf1_tmp1          : 8  ; /* [15..8]  */
        unsigned int    hsp_hf1_tmp2          : 8  ; /* [23..16]  */
        unsigned int    hsp_hf1_tmp3          : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg7;

/* Define the union reg_vga_hspcfg8 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf1_coring        : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg8;

/* Define the union reg_vga_hspcfg12 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf1_gainpos       : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    hsp_hf1_gainneg       : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg12;

/* Define the union reg_vga_hspcfg13 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_hf1_overth        : 8  ; /* [7..0]  */
        unsigned int    hsp_hf1_underth       : 8  ; /* [15..8]  */
        unsigned int    hsp_hf1_mixratio      : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 4  ; /* [27..24]  */
        unsigned int    hsp_hf1_winsize       : 3  ; /* [30..28]  */
        unsigned int    hsp_hf1_adpshoot_en   : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg13;

/* Define the union reg_vga_hspcfg14 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_cdti_gain         : 8  ; /* [7..0]  */
        unsigned int    hsp_ldti_gain         : 8  ; /* [15..8]  */
        unsigned int    hsp_lti_ratio         : 8  ; /* [23..16]  */
        unsigned int    hsp_hf_shootdiv       : 3  ; /* [26..24]  */
        unsigned int    reserved_0            : 1  ; /* [27]  */
        unsigned int    hsp_ctih_en           : 1  ; /* [28]  */
        unsigned int    hsp_ltih_en           : 1  ; /* [29]  */
        unsigned int    hsp_h1_en             : 1  ; /* [30]  */
        unsigned int    hsp_h0_en             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg14;

/* Define the union reg_vga_hspcfg15 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hsp_glb_underth       : 9  ; /* [8..0]  */
        unsigned int    reserved_0            : 1  ; /* [9]  */
        unsigned int    hsp_glb_overth        : 9  ; /* [18..10]  */
        unsigned int    reserved_1            : 1  ; /* [19]  */
        unsigned int    hsp_peak_ratio        : 8  ; /* [27..20]  */
        unsigned int    reserved_2            : 4  ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vga_hspcfg15;

/* Define the union reg_intf_date_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 23 ; /* [22..0]  */
        unsigned int    uv_mode               : 1  ; /* [23]  */
        unsigned int    yc_mode               : 1  ; /* [24]  */
        unsigned int    lcd_parallel_mode     : 1  ; /* [25]  */
        unsigned int    lcd_data_inv          : 1  ; /* [26]  */
        unsigned int    lcd_parallel_order    : 1  ; /* [27]  */
        unsigned int    lcd_serial_perd       : 1  ; /* [28]  */
        unsigned int    lcd_serial_mode       : 1  ; /* [29]  */
        unsigned int    dfir_en               : 1  ; /* [30]  */
        unsigned int    hdmi_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_date_ctrl;

/* Define the union reg_intf_date_upd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_date_upd;

/* Define the union reg_intf_date_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dv_inv                : 1  ; /* [0]  */
        unsigned int    hs_inv                : 1  ; /* [1]  */
        unsigned int    vs_inv                : 1  ; /* [2]  */
        unsigned int    f_inv                 : 1  ; /* [3]  */
        unsigned int    reserved_0            : 28 ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf_date_sync_inv;

/* Define the union reg_date_clip0_l */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    clip_cl0              : 10 ; /* [9..0]  */
        unsigned int    clip_cl1              : 10 ; /* [19..10]  */
        unsigned int    clip_cl2              : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 1  ; /* [30]  */
        unsigned int    clip_en               : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_clip0_l;

/* Define the union reg_date_clip0_h */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    clip_ch0              : 10 ; /* [9..0]  */
        unsigned int    clip_ch1              : 10 ; /* [19..10]  */
        unsigned int    clip_ch2              : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_clip0_h;

/* Define the union reg_intf0_dither_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_tap_mode       : 2  ; /* [1..0]  */
        unsigned int    dither_domain_mode    : 1  ; /* [2]  */
        unsigned int    dither_round          : 1  ; /* [3]  */
        unsigned int    dither_mode           : 1  ; /* [4]  */
        unsigned int    dither_en             : 1  ; /* [5]  */
        unsigned int    dither_round_unlim    : 1  ; /* [6]  */
        unsigned int    i_data_width_dither   : 3  ; /* [9..7]  */
        unsigned int    o_data_width_dither   : 3  ; /* [12..10]  */
        unsigned int    reserved_0            : 19 ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_ctrl;

/* Define the union reg_intf0_dither_sed_y0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_y0;

/* Define the union reg_intf0_dither_sed_u0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_u0;

/* Define the union reg_intf0_dither_sed_v0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_v0;

/* Define the union reg_intf0_dither_sed_w0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_w0;

/* Define the union reg_intf0_dither_sed_y1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_y1;

/* Define the union reg_intf0_dither_sed_u1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_u1;

/* Define the union reg_intf0_dither_sed_v1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_v1;

/* Define the union reg_intf0_dither_sed_w1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_w1;

/* Define the union reg_intf0_dither_sed_y2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_y2;

/* Define the union reg_intf0_dither_sed_u2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_u2;

/* Define the union reg_intf0_dither_sed_v2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_v2;

/* Define the union reg_intf0_dither_sed_w2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_w2;

/* Define the union reg_intf0_dither_sed_y3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_y3;

/* Define the union reg_intf0_dither_sed_u3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_u3;

/* Define the union reg_intf0_dither_sed_v3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_v3;

/* Define the union reg_intf0_dither_sed_w3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_sed_w3;

/* Define the union reg_intf0_dither_thr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_thr_min        : 16 ; /* [15..0]  */
        unsigned int    dither_thr_max        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf0_dither_thr;

/* Define the union reg_dhd1_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    disp_mode             : 3  ; /* [3..1]  */
        unsigned int    iop                   : 1  ; /* [4]  */
        unsigned int    intf_ivs              : 1  ; /* [5]  */
        unsigned int    intf_ihs              : 1  ; /* [6]  */
        unsigned int    intf_idv              : 1  ; /* [7]  */
        unsigned int    reserved_0            : 1  ; /* [8]  */
        unsigned int    hdmi420c_sel          : 1  ; /* [9]  */
        unsigned int    hdmi420_en            : 1  ; /* [10]  */
        unsigned int    uf_offline_en         : 1  ; /* [11]  */
        unsigned int    reserved_1            : 2  ; /* [13..12]  */
        unsigned int    hdmi_mode             : 1  ; /* [14]  */
        unsigned int    twochn_debug          : 1  ; /* [15]  */
        unsigned int    twochn_en             : 1  ; /* [16]  */
        unsigned int    reserved_2            : 1  ; /* [17]  */
        unsigned int    cbar_mode             : 1  ; /* [18]  */
        unsigned int    sin_en                : 1  ; /* [19]  */
        unsigned int    fpga_lmt_width        : 7  ; /* [26..20]  */
        unsigned int    fpga_lmt_en           : 1  ; /* [27]  */
        unsigned int    p2i_en                : 1  ; /* [28]  */
        unsigned int    cbar_sel              : 1  ; /* [29]  */
        unsigned int    cbar_en               : 1  ; /* [30]  */
        unsigned int    intf_en               : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_ctrl;

/* Define the union reg_dhd1_vsync1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vact                  : 16 ; /* [15..0]  */
        unsigned int    vbb                   : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vsync1;

/* Define the union reg_dhd1_vsync2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vfb                   : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vsync2;

/* Define the union reg_dhd1_hsync1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hact                  : 16 ; /* [15..0]  */
        unsigned int    hbb                   : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_hsync1;

/* Define the union reg_dhd1_hsync2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfb                   : 16 ; /* [15..0]  */
        unsigned int    hmid                  : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_hsync2;

/* Define the union reg_dhd1_vplus1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    bvact                 : 16 ; /* [15..0]  */
        unsigned int    bvbb                  : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vplus1;

/* Define the union reg_dhd1_vplus2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    bvfb                  : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vplus2;

/* Define the union reg_dhd1_pwr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hpw                   : 16 ; /* [15..0]  */
        unsigned int    vpw                   : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 3  ; /* [26..24]  */
        unsigned int    multichn_en           : 2  ; /* [28..27]  */
        unsigned int    reserved_1            : 3  ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_pwr;

/* Define the union reg_dhd1_vtthd3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vtmgthd3              : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 2  ; /* [14..13]  */
        unsigned int    thd3_mode             : 1  ; /* [15]  */
        unsigned int    vtmgthd4              : 13 ; /* [28..16]  */
        unsigned int    reserved_1            : 2  ; /* [30..29]  */
        unsigned int    thd4_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vtthd3;

/* Define the union reg_dhd1_vtthd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vtmgthd1              : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 2  ; /* [14..13]  */
        unsigned int    thd1_mode             : 1  ; /* [15]  */
        unsigned int    vtmgthd2              : 13 ; /* [28..16]  */
        unsigned int    reserved_1            : 2  ; /* [30..29]  */
        unsigned int    thd2_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vtthd;

/* Define the union reg_dhd1_parathd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    para_thd              : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 23 ; /* [30..8]  */
        unsigned int    dfs_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_parathd;

/* Define the union reg_dhd1_precharge_thd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tcon_precharge_thd    : 17 ; /* [16..0]  */
        unsigned int    reserved_0            : 3  ; /* [19..17]  */
        unsigned int    vsync_te_mode         : 1  ; /* [20]  */
        unsigned int    reserved_1            : 11 ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_precharge_thd;

/* Define the union reg_dhd1_start_pos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    start_pos             : 8  ; /* [7..0]  */
        unsigned int    timing_start_pos      : 8  ; /* [15..8]  */
        unsigned int    fi_start_pos          : 4  ; /* [19..16]  */
        unsigned int    req_start_pos         : 12 ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_start_pos;

/* Define the union reg_dhd1_start_pos1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    req_start_pos1        : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_start_pos1;

/* Define the union reg_dhd1_paraup */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 31 ; /* [30..0]  */
        unsigned int    paraup_mode           : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_paraup;

/* Define the union reg_dhd1_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    lcd_dv_inv            : 1  ; /* [0]  */
        unsigned int    lcd_hs_inv            : 1  ; /* [1]  */
        unsigned int    lcd_vs_inv            : 1  ; /* [2]  */
        unsigned int    reserved_0            : 1  ; /* [3]  */
        unsigned int    vga_dv_inv            : 1  ; /* [4]  */
        unsigned int    vga_hs_inv            : 1  ; /* [5]  */
        unsigned int    vga_vs_inv            : 1  ; /* [6]  */
        unsigned int    reserved_1            : 1  ; /* [7]  */
        unsigned int    hdmi_dv_inv           : 1  ; /* [8]  */
        unsigned int    hdmi_hs_inv           : 1  ; /* [9]  */
        unsigned int    hdmi_vs_inv           : 1  ; /* [10]  */
        unsigned int    hdmi_f_inv            : 1  ; /* [11]  */
        unsigned int    date_dv_inv           : 1  ; /* [12]  */
        unsigned int    date_hs_inv           : 1  ; /* [13]  */
        unsigned int    date_vs_inv           : 1  ; /* [14]  */
        unsigned int    date_f_inv            : 1  ; /* [15]  */
        unsigned int    reserved_2            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_sync_inv;

/* Define the union reg_dhd1_clk_dv_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    intf_clk_mux          : 1  ; /* [0]  */
        unsigned int    intf_dv_mux           : 1  ; /* [1]  */
        unsigned int    no_active_area_pos    : 16 ; /* [17..2]  */
        unsigned int    reserved_0            : 14 ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_clk_dv_ctrl;

/* Define the union reg_dhd1_rgb_fix_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fix_b                 : 10 ; /* [9..0]  */
        unsigned int    fix_g                 : 10 ; /* [19..10]  */
        unsigned int    fix_r                 : 10 ; /* [29..20]  */
        unsigned int    rgb_fix_mux           : 1  ; /* [30]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_rgb_fix_ctrl;

/* Define the union reg_dhd1_lockcfg */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    measure_en            : 1  ; /* [0]  */
        unsigned int    lock_cnt_en           : 1  ; /* [1]  */
        unsigned int    vdp_measure_en        : 1  ; /* [2]  */
        unsigned int    reserved_0            : 29 ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_lockcfg;

/* Define the union reg_dhd1_intf_chksum_high1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    y0_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b0_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_intf_chksum_high1;

/* Define the union reg_dhd1_intf_chksum_high2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    y1_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g1_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b1_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_intf_chksum_high2;

/* Define the union reg_dhd1_state */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vback_blank           : 1  ; /* [0]  */
        unsigned int    vblank                : 1  ; /* [1]  */
        unsigned int    bottom_field          : 1  ; /* [2]  */
        unsigned int    vcnt                  : 13 ; /* [15..3]  */
        unsigned int    count_int             : 8  ; /* [23..16]  */
        unsigned int    dhd_even              : 1  ; /* [24]  */
        unsigned int    reserved_0            : 7  ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_state;

/* Define the union reg_dhd1_uf_state */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ud_first_cnt          : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 3  ; /* [15..13]  */
        unsigned int    start_pos             : 8  ; /* [23..16]  */
        unsigned int    reserved_1            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_uf_state;

/* Define the union reg_dhd1_vsync_te_state */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vsync_te_start_sta    : 8  ; /* [7..0]  */
        unsigned int    vsync_te_start_sta1   : 8  ; /* [15..8]  */
        unsigned int    vsync_te_end_sta      : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vsync_te_state;

/* Define the union reg_dhd1_vsync_te_state1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vsync_te_vfb          : 16 ; /* [15..0]  */
        unsigned int    vsync_te_width        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd1_vsync_te_state1;

/* Define the union reg_intf1_dither_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_tap_mode       : 2  ; /* [1..0]  */
        unsigned int    dither_domain_mode    : 1  ; /* [2]  */
        unsigned int    dither_round          : 1  ; /* [3]  */
        unsigned int    dither_mode           : 1  ; /* [4]  */
        unsigned int    dither_en             : 1  ; /* [5]  */
        unsigned int    dither_round_unlim    : 1  ; /* [6]  */
        unsigned int    i_data_width_dither   : 3  ; /* [9..7]  */
        unsigned int    o_data_width_dither   : 3  ; /* [12..10]  */
        unsigned int    reserved_0            : 19 ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_ctrl;

/* Define the union reg_intf1_dither_sed_y0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_y0;

/* Define the union reg_intf1_dither_sed_u0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_u0;

/* Define the union reg_intf1_dither_sed_v0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_v0;

/* Define the union reg_intf1_dither_sed_w0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_w0;

/* Define the union reg_intf1_dither_sed_y1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_y1;

/* Define the union reg_intf1_dither_sed_u1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_u1;

/* Define the union reg_intf1_dither_sed_v1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_v1;

/* Define the union reg_intf1_dither_sed_w1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_w1;

/* Define the union reg_intf1_dither_sed_y2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_y2;

/* Define the union reg_intf1_dither_sed_u2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_u2;

/* Define the union reg_intf1_dither_sed_v2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_v2;

/* Define the union reg_intf1_dither_sed_w2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_w2;

/* Define the union reg_intf1_dither_sed_y3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_y3;

/* Define the union reg_intf1_dither_sed_u3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_u3;

/* Define the union reg_intf1_dither_sed_v3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_v3;

/* Define the union reg_intf1_dither_sed_w3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_sed_w3;

/* Define the union reg_intf1_dither_thr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_thr_min        : 16 ; /* [15..0]  */
        unsigned int    dither_thr_max        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf1_dither_thr;

/* Define the union reg_dhd2_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    regup                 : 1  ; /* [0]  */
        unsigned int    disp_mode             : 3  ; /* [3..1]  */
        unsigned int    iop                   : 1  ; /* [4]  */
        unsigned int    intf_ivs              : 1  ; /* [5]  */
        unsigned int    intf_ihs              : 1  ; /* [6]  */
        unsigned int    intf_idv              : 1  ; /* [7]  */
        unsigned int    reserved_0            : 1  ; /* [8]  */
        unsigned int    hdmi420c_sel          : 1  ; /* [9]  */
        unsigned int    hdmi420_en            : 1  ; /* [10]  */
        unsigned int    uf_offline_en         : 1  ; /* [11]  */
        unsigned int    reserved_1            : 2  ; /* [13..12]  */
        unsigned int    hdmi_mode             : 1  ; /* [14]  */
        unsigned int    twochn_debug          : 1  ; /* [15]  */
        unsigned int    twochn_en             : 1  ; /* [16]  */
        unsigned int    reserved_2            : 1  ; /* [17]  */
        unsigned int    cbar_mode             : 1  ; /* [18]  */
        unsigned int    sin_en                : 1  ; /* [19]  */
        unsigned int    fpga_lmt_width        : 7  ; /* [26..20]  */
        unsigned int    fpga_lmt_en           : 1  ; /* [27]  */
        unsigned int    p2i_en                : 1  ; /* [28]  */
        unsigned int    cbar_sel              : 1  ; /* [29]  */
        unsigned int    cbar_en               : 1  ; /* [30]  */
        unsigned int    intf_en               : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_ctrl;

/* Define the union reg_dhd2_vsync1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vact                  : 16 ; /* [15..0]  */
        unsigned int    vbb                   : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vsync1;

/* Define the union reg_dhd2_vsync2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vfb                   : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vsync2;

/* Define the union reg_dhd2_hsync1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hact                  : 16 ; /* [15..0]  */
        unsigned int    hbb                   : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_hsync1;

/* Define the union reg_dhd2_hsync2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hfb                   : 16 ; /* [15..0]  */
        unsigned int    hmid                  : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_hsync2;

/* Define the union reg_dhd2_vplus1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    bvact                 : 16 ; /* [15..0]  */
        unsigned int    bvbb                  : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vplus1;

/* Define the union reg_dhd2_vplus2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    bvfb                  : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vplus2;

/* Define the union reg_dhd2_pwr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    hpw                   : 16 ; /* [15..0]  */
        unsigned int    vpw                   : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 3  ; /* [26..24]  */
        unsigned int    multichn_en           : 2  ; /* [28..27]  */
        unsigned int    reserved_1            : 3  ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_pwr;

/* Define the union reg_dhd2_vtthd3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vtmgthd3              : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 2  ; /* [14..13]  */
        unsigned int    thd3_mode             : 1  ; /* [15]  */
        unsigned int    vtmgthd4              : 13 ; /* [28..16]  */
        unsigned int    reserved_1            : 2  ; /* [30..29]  */
        unsigned int    thd4_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vtthd3;

/* Define the union reg_dhd2_vtthd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vtmgthd1              : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 2  ; /* [14..13]  */
        unsigned int    thd1_mode             : 1  ; /* [15]  */
        unsigned int    vtmgthd2              : 13 ; /* [28..16]  */
        unsigned int    reserved_1            : 2  ; /* [30..29]  */
        unsigned int    thd2_mode             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vtthd;

/* Define the union reg_dhd2_parathd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    para_thd              : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 23 ; /* [30..8]  */
        unsigned int    dfs_en                : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_parathd;

/* Define the union reg_dhd2_precharge_thd */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tcon_precharge_thd    : 17 ; /* [16..0]  */
        unsigned int    reserved_0            : 3  ; /* [19..17]  */
        unsigned int    vsync_te_mode         : 1  ; /* [20]  */
        unsigned int    reserved_1            : 11 ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_precharge_thd;

/* Define the union reg_dhd2_start_pos */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    start_pos             : 8  ; /* [7..0]  */
        unsigned int    timing_start_pos      : 8  ; /* [15..8]  */
        unsigned int    fi_start_pos          : 4  ; /* [19..16]  */
        unsigned int    req_start_pos         : 12 ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_start_pos;

/* Define the union reg_dhd2_start_pos1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    req_start_pos1        : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_start_pos1;

/* Define the union reg_dhd2_paraup */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    reserved_0            : 31 ; /* [30..0]  */
        unsigned int    paraup_mode           : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_paraup;

/* Define the union reg_dhd2_sync_inv */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    lcd_dv_inv            : 1  ; /* [0]  */
        unsigned int    lcd_hs_inv            : 1  ; /* [1]  */
        unsigned int    lcd_vs_inv            : 1  ; /* [2]  */
        unsigned int    reserved_0            : 1  ; /* [3]  */
        unsigned int    vga_dv_inv            : 1  ; /* [4]  */
        unsigned int    vga_hs_inv            : 1  ; /* [5]  */
        unsigned int    vga_vs_inv            : 1  ; /* [6]  */
        unsigned int    reserved_1            : 1  ; /* [7]  */
        unsigned int    hdmi_dv_inv           : 1  ; /* [8]  */
        unsigned int    hdmi_hs_inv           : 1  ; /* [9]  */
        unsigned int    hdmi_vs_inv           : 1  ; /* [10]  */
        unsigned int    hdmi_f_inv            : 1  ; /* [11]  */
        unsigned int    date_dv_inv           : 1  ; /* [12]  */
        unsigned int    date_hs_inv           : 1  ; /* [13]  */
        unsigned int    date_vs_inv           : 1  ; /* [14]  */
        unsigned int    date_f_inv            : 1  ; /* [15]  */
        unsigned int    reserved_2            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_sync_inv;

/* Define the union reg_dhd2_clk_dv_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    intf_clk_mux          : 1  ; /* [0]  */
        unsigned int    intf_dv_mux           : 1  ; /* [1]  */
        unsigned int    no_active_area_pos    : 16 ; /* [17..2]  */
        unsigned int    reserved_0            : 14 ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_clk_dv_ctrl;

/* Define the union reg_dhd2_rgb_fix_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fix_b                 : 10 ; /* [9..0]  */
        unsigned int    fix_g                 : 10 ; /* [19..10]  */
        unsigned int    fix_r                 : 10 ; /* [29..20]  */
        unsigned int    rgb_fix_mux           : 1  ; /* [30]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_rgb_fix_ctrl;

/* Define the union reg_dhd2_lockcfg */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    measure_en            : 1  ; /* [0]  */
        unsigned int    lock_cnt_en           : 1  ; /* [1]  */
        unsigned int    vdp_measure_en        : 1  ; /* [2]  */
        unsigned int    reserved_0            : 29 ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_lockcfg;

/* Define the union reg_dhd2_intf_chksum_high1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    y0_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b0_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_intf_chksum_high1;

/* Define the union reg_dhd2_intf_chksum_high2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    y1_sum_high           : 8  ; /* [7..0]  */
        unsigned int    g1_sum_high           : 8  ; /* [15..8]  */
        unsigned int    b1_sum_high           : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_intf_chksum_high2;

/* Define the union reg_dhd2_state */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vback_blank           : 1  ; /* [0]  */
        unsigned int    vblank                : 1  ; /* [1]  */
        unsigned int    bottom_field          : 1  ; /* [2]  */
        unsigned int    vcnt                  : 13 ; /* [15..3]  */
        unsigned int    count_int             : 8  ; /* [23..16]  */
        unsigned int    dhd_even              : 1  ; /* [24]  */
        unsigned int    reserved_0            : 7  ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_state;

/* Define the union reg_dhd2_uf_state */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ud_first_cnt          : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 3  ; /* [15..13]  */
        unsigned int    start_pos             : 8  ; /* [23..16]  */
        unsigned int    reserved_1            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_uf_state;

/* Define the union reg_dhd2_vsync_te_state */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vsync_te_start_sta    : 8  ; /* [7..0]  */
        unsigned int    vsync_te_start_sta1   : 8  ; /* [15..8]  */
        unsigned int    vsync_te_end_sta      : 8  ; /* [23..16]  */
        unsigned int    reserved_0            : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vsync_te_state;

/* Define the union reg_dhd2_vsync_te_state1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vsync_te_vfb          : 16 ; /* [15..0]  */
        unsigned int    vsync_te_width        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_dhd2_vsync_te_state1;

/* Define the union reg_intf2_dither_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_tap_mode       : 2  ; /* [1..0]  */
        unsigned int    dither_domain_mode    : 1  ; /* [2]  */
        unsigned int    dither_round          : 1  ; /* [3]  */
        unsigned int    dither_mode           : 1  ; /* [4]  */
        unsigned int    dither_en             : 1  ; /* [5]  */
        unsigned int    dither_round_unlim    : 1  ; /* [6]  */
        unsigned int    i_data_width_dither   : 3  ; /* [9..7]  */
        unsigned int    o_data_width_dither   : 3  ; /* [12..10]  */
        unsigned int    reserved_0            : 19 ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_ctrl;

/* Define the union reg_intf2_dither_sed_y0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_y0;

/* Define the union reg_intf2_dither_sed_u0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_u0;

/* Define the union reg_intf2_dither_sed_v0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_v0;

/* Define the union reg_intf2_dither_sed_w0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w0         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_w0;

/* Define the union reg_intf2_dither_sed_y1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_y1;

/* Define the union reg_intf2_dither_sed_u1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_u1;

/* Define the union reg_intf2_dither_sed_v1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_v1;

/* Define the union reg_intf2_dither_sed_w1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w1         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_w1;

/* Define the union reg_intf2_dither_sed_y2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_y2;

/* Define the union reg_intf2_dither_sed_u2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_u2;

/* Define the union reg_intf2_dither_sed_v2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_v2;

/* Define the union reg_intf2_dither_sed_w2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w2         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_w2;

/* Define the union reg_intf2_dither_sed_y3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_y3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_y3;

/* Define the union reg_intf2_dither_sed_u3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_u3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_u3;

/* Define the union reg_intf2_dither_sed_v3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_v3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_v3;

/* Define the union reg_intf2_dither_sed_w3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_sed_w3         : 31 ; /* [30..0]  */
        unsigned int    reserved_0            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_sed_w3;

/* Define the union reg_intf2_dither_thr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dither_thr_min        : 16 ; /* [15..0]  */
        unsigned int    dither_thr_max        : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_intf2_dither_thr;

/* Define the union reg_date_coeff0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt_seq                : 1  ; /* [0]  */
        unsigned int    chgain_en             : 1  ; /* [1]  */
        unsigned int    sylp_en               : 1  ; /* [2]  */
        unsigned int    chlp_en               : 1  ; /* [3]  */
        unsigned int    oversam2_en           : 1  ; /* [4]  */
        unsigned int    lunt_en               : 1  ; /* [5]  */
        unsigned int    oversam_en            : 2  ; /* [7..6]  */
        unsigned int    reserved_0            : 1  ; /* [8]  */
        unsigned int    luma_dl               : 4  ; /* [12..9]  */
        unsigned int    agc_amp_sel           : 1  ; /* [13]  */
        unsigned int    length_sel            : 1  ; /* [14]  */
        unsigned int    sync_mode_scart       : 1  ; /* [15]  */
        unsigned int    sync_mode_sel         : 2  ; /* [17..16]  */
        unsigned int    style_sel             : 4  ; /* [21..18]  */
        unsigned int    fm_sel                : 1  ; /* [22]  */
        unsigned int    vbi_lpf_en            : 1  ; /* [23]  */
        unsigned int    rgb_en                : 1  ; /* [24]  */
        unsigned int    scanline              : 1  ; /* [25]  */
        unsigned int    pbpr_lpf_en           : 1  ; /* [26]  */
        unsigned int    pal_half_en           : 1  ; /* [27]  */
        unsigned int    reserved_1            : 1  ; /* [28]  */
        unsigned int    dis_ire               : 1  ; /* [29]  */
        unsigned int    clpf_sel              : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff0;

/* Define the union reg_date_coeff1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dac_test              : 10 ; /* [9..0]  */
        unsigned int    date_test_mode        : 2  ; /* [11..10]  */
        unsigned int    date_test_en          : 1  ; /* [12]  */
        unsigned int    amp_outside           : 10 ; /* [22..13]  */
        unsigned int    c_limit_en            : 1  ; /* [23]  */
        unsigned int    cc_seq                : 1  ; /* [24]  */
        unsigned int    cgms_seq              : 1  ; /* [25]  */
        unsigned int    vps_seq               : 1  ; /* [26]  */
        unsigned int    wss_seq               : 1  ; /* [27]  */
        unsigned int    cvbs_limit_en         : 1  ; /* [28]  */
        unsigned int    c_gain                : 3  ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff1;

/* Define the union reg_date_coeff3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef03                : 26 ; /* [25..0]  */
        unsigned int    reserved_0            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff3;

/* Define the union reg_date_coeff4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef04                : 30 ; /* [29..0]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff4;

/* Define the union reg_date_coeff5 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef05                : 29 ; /* [28..0]  */
        unsigned int    reserved_0            : 3  ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff5;

/* Define the union reg_date_coeff6 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    coef06_1              : 23 ; /* [22..0]  */
        unsigned int    reserved_0            : 8  ; /* [30..23]  */
        unsigned int    coef06_0              : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff6;

/* Define the union reg_date_coeff7 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt07_enf2             : 1  ; /* [0]  */
        unsigned int    tt08_enf2             : 1  ; /* [1]  */
        unsigned int    tt09_enf2             : 1  ; /* [2]  */
        unsigned int    tt10_enf2             : 1  ; /* [3]  */
        unsigned int    tt11_enf2             : 1  ; /* [4]  */
        unsigned int    tt12_enf2             : 1  ; /* [5]  */
        unsigned int    tt13_enf2             : 1  ; /* [6]  */
        unsigned int    tt14_enf2             : 1  ; /* [7]  */
        unsigned int    tt15_enf2             : 1  ; /* [8]  */
        unsigned int    tt16_enf2             : 1  ; /* [9]  */
        unsigned int    tt17_enf2             : 1  ; /* [10]  */
        unsigned int    tt18_enf2             : 1  ; /* [11]  */
        unsigned int    tt19_enf2             : 1  ; /* [12]  */
        unsigned int    tt20_enf2             : 1  ; /* [13]  */
        unsigned int    tt21_enf2             : 1  ; /* [14]  */
        unsigned int    tt22_enf2             : 1  ; /* [15]  */
        unsigned int    tt07_enf1             : 1  ; /* [16]  */
        unsigned int    tt08_enf1             : 1  ; /* [17]  */
        unsigned int    tt09_enf1             : 1  ; /* [18]  */
        unsigned int    tt10_enf1             : 1  ; /* [19]  */
        unsigned int    tt11_enf1             : 1  ; /* [20]  */
        unsigned int    tt12_enf1             : 1  ; /* [21]  */
        unsigned int    tt13_enf1             : 1  ; /* [22]  */
        unsigned int    tt14_enf1             : 1  ; /* [23]  */
        unsigned int    tt15_enf1             : 1  ; /* [24]  */
        unsigned int    tt16_enf1             : 1  ; /* [25]  */
        unsigned int    tt17_enf1             : 1  ; /* [26]  */
        unsigned int    tt18_enf1             : 1  ; /* [27]  */
        unsigned int    tt19_enf1             : 1  ; /* [28]  */
        unsigned int    tt20_enf1             : 1  ; /* [29]  */
        unsigned int    tt21_enf1             : 1  ; /* [30]  */
        unsigned int    tt22_enf1             : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff7;

/* Define the union reg_date_coeff10 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt_pktoff             : 8  ; /* [7..0]  */
        unsigned int    tt_mode               : 2  ; /* [9..8]  */
        unsigned int    tt_highest            : 1  ; /* [10]  */
        unsigned int    full_page             : 1  ; /* [11]  */
        unsigned int    nabts_100ire          : 1  ; /* [12]  */
        unsigned int    reserved_0            : 18 ; /* [30..13]  */
        unsigned int    tt_ready              : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff10;

/* Define the union reg_date_coeff11 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    date_clf2             : 10 ; /* [9..0]  */
        unsigned int    date_clf1             : 10 ; /* [19..10]  */
        unsigned int    cc_enf2               : 1  ; /* [20]  */
        unsigned int    cc_enf1               : 1  ; /* [21]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff11;

/* Define the union reg_date_coeff12 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cc_f2data             : 16 ; /* [15..0]  */
        unsigned int    cc_f1data             : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff12;

/* Define the union reg_date_coeff13 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cg_f1data             : 20 ; /* [19..0]  */
        unsigned int    cg_enf2               : 1  ; /* [20]  */
        unsigned int    cg_enf1               : 1  ; /* [21]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff13;

/* Define the union reg_date_coeff14 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cg_f2data             : 20 ; /* [19..0]  */
        unsigned int    reserved_0            : 12 ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff14;

/* Define the union reg_date_coeff15 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    wss_data              : 14 ; /* [13..0]  */
        unsigned int    wss_en                : 1  ; /* [14]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff15;

/* Define the union reg_date_coeff16 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vps_data              : 24 ; /* [23..0]  */
        unsigned int    vps_en                : 1  ; /* [24]  */
        unsigned int    reserved_0            : 7  ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff16;

/* Define the union reg_date_coeff19 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vps_data              : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff19;

/* Define the union reg_date_coeff20 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt05_enf2             : 1  ; /* [0]  */
        unsigned int    tt06_enf2             : 1  ; /* [1]  */
        unsigned int    tt06_enf1             : 1  ; /* [2]  */
        unsigned int    reserved_0            : 29 ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff20;

/* Define the union reg_date_coeff21 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dac0_in_sel           : 3  ; /* [2..0]  */
        unsigned int    reserved_0            : 1  ; /* [3]  */
        unsigned int    dac1_in_sel           : 3  ; /* [6..4]  */
        unsigned int    reserved_1            : 1  ; /* [7]  */
        unsigned int    dac2_in_sel           : 3  ; /* [10..8]  */
        unsigned int    reserved_2            : 1  ; /* [11]  */
        unsigned int    dac3_in_sel           : 3  ; /* [14..12]  */
        unsigned int    reserved_3            : 1  ; /* [15]  */
        unsigned int    dac4_in_sel           : 3  ; /* [18..16]  */
        unsigned int    reserved_4            : 1  ; /* [19]  */
        unsigned int    dac5_in_sel           : 3  ; /* [22..20]  */
        unsigned int    reserved_5            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff21;

/* Define the union reg_date_coeff22 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    video_phase_delta     : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 21 ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff22;

/* Define the union reg_date_coeff23 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dac0_out_dly          : 3  ; /* [2..0]  */
        unsigned int    reserved_0            : 1  ; /* [3]  */
        unsigned int    dac1_out_dly          : 3  ; /* [6..4]  */
        unsigned int    reserved_1            : 1  ; /* [7]  */
        unsigned int    dac2_out_dly          : 3  ; /* [10..8]  */
        unsigned int    reserved_2            : 1  ; /* [11]  */
        unsigned int    dac3_out_dly          : 3  ; /* [14..12]  */
        unsigned int    reserved_3            : 1  ; /* [15]  */
        unsigned int    dac4_out_dly          : 3  ; /* [18..16]  */
        unsigned int    reserved_4            : 1  ; /* [19]  */
        unsigned int    dac5_out_dly          : 3  ; /* [22..20]  */
        unsigned int    reserved_5            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff23;

/* Define the union reg_date_coeff25 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    x_n_coef              : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 3  ; /* [15..13]  */
        unsigned int    x_n_1_coef            : 13 ; /* [28..16]  */
        unsigned int    reserved_1            : 3  ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff25;

/* Define the union reg_date_coeff26 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    x_n_1_coef            : 13 ; /* [12..0]  */
        unsigned int    reserved_0            : 19 ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff26;

/* Define the union reg_date_coeff27 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    y_n_coef              : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    y_n_1_coef            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff27;

/* Define the union reg_date_coeff28 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pixel_begin1          : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    pixel_begin2          : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff28;

/* Define the union reg_date_coeff29 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pixel_end             : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 21 ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff29;

/* Define the union reg_date_coeff30 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    g_secam               : 7  ; /* [6..0]  */
        unsigned int    reserved_0            : 25 ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff30;

/* Define the union reg_date_isrmask */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt_mask               : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_isrmask;

/* Define the union reg_date_isrstate */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt_status             : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_isrstate;

/* Define the union reg_date_isr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    tt_int                : 1  ; /* [0]  */
        unsigned int    reserved_0            : 31 ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_isr;

/* Define the union reg_date_coeff37 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fir_y1_coeff0         : 8  ; /* [7..0]  */
        unsigned int    fir_y1_coeff1         : 8  ; /* [15..8]  */
        unsigned int    fir_y1_coeff2         : 8  ; /* [23..16]  */
        unsigned int    fir_y1_coeff3         : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff37;

/* Define the union reg_date_coeff38 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fir_y2_coeff0         : 16 ; /* [15..0]  */
        unsigned int    fir_y2_coeff1         : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff38;

/* Define the union reg_date_coeff39 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fir_y2_coeff2         : 16 ; /* [15..0]  */
        unsigned int    fir_y2_coeff3         : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff39;

/* Define the union reg_date_coeff40 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fir_c1_coeff0         : 8  ; /* [7..0]  */
        unsigned int    fir_c1_coeff1         : 8  ; /* [15..8]  */
        unsigned int    fir_c1_coeff2         : 8  ; /* [23..16]  */
        unsigned int    fir_c1_coeff3         : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff40;

/* Define the union reg_date_coeff41 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fir_c2_coeff0         : 16 ; /* [15..0]  */
        unsigned int    fir_c2_coeff1         : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff41;

/* Define the union reg_date_coeff42 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    fir_c2_coeff2         : 16 ; /* [15..0]  */
        unsigned int    fir_c2_coeff3         : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff42;

/* Define the union reg_date_dacdet1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vdac_det_high         : 10 ; /* [9..0]  */
        unsigned int    reserved_0            : 6  ; /* [15..10]  */
        unsigned int    det_line              : 10 ; /* [25..16]  */
        unsigned int    reserved_1            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_dacdet1;

/* Define the union reg_date_dacdet2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    det_pixel_sta         : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    det_pixel_wid         : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 4  ; /* [30..27]  */
        unsigned int    vdac_det_en           : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_dacdet2;

/* Define the union reg_date_coeff50 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ovs_coeff0            : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff50;

/* Define the union reg_date_coeff51 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ovs_coeff0            : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff51;

/* Define the union reg_date_coeff52 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ovs_coeff0            : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff52;

/* Define the union reg_date_coeff53 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ovs_coeff0            : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff53;

/* Define the union reg_date_coeff54 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ovs_coeff0            : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff54;

/* Define the union reg_date_coeff55 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ovs_coeff0            : 11 ; /* [10..0]  */
        unsigned int    reserved_0            : 5  ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11 ; /* [26..16]  */
        unsigned int    reserved_1            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff55;

/* Define the union reg_date_coeff56 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    oversam2_round_en     : 1 ; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff56;

/* Define the union reg_date_coeff57 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    v_gain                : 8 ; /* [7..0]  */
        unsigned int    reg_gain                : 8 ; /* [15..8]  */
        unsigned int    ycvbs_gain            : 8 ; /* [23..16]  */
        unsigned int    reserved_0            : 7 ; /* [30..24]  */
        unsigned int    cvbs_gain_en          : 1 ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff57;

/* Define the union reg_date_coeff58 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    pr_gain               : 8 ; /* [7..0]  */
        unsigned int    pb_gain               : 8 ; /* [15..8]  */
        unsigned int    ycomp_gain            : 8 ; /* [23..16]  */
        unsigned int    reserved_0            : 7 ; /* [30..24]  */
        unsigned int    comp_gain_en          : 1 ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff58;

/* Define the union reg_date_coeff59 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ynotch_clip_fullrange : 1 ; /* [0]  */
        unsigned int    clpf_clip_fullrange   : 1 ; /* [1]  */
        unsigned int    reserved_0            : 2 ; /* [3..2]  */
        unsigned int    y_os_clip_fullrange   : 1 ; /* [4]  */
        unsigned int    reserved_1            : 3 ; /* [7..5]  */
        unsigned int    reg_os_clip_fullrange   : 1 ; /* [8]  */
        unsigned int    v_os_clip_fullrange   : 1 ; /* [9]  */
        unsigned int    reserved_2            : 2 ; /* [11..10]  */
        unsigned int    cb_os_clip_fullrange  : 1 ; /* [12]  */
        unsigned int    cr_os_clip_fullrange  : 1 ; /* [13]  */
        unsigned int    reserved_3            : 2 ; /* [15..14]  */
        unsigned int    cb_gain_polar         : 1 ; /* [16]  */
        unsigned int    reserved_4            : 15; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff59;

/* Define the union reg_date_coeff60 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    line_960h_en          : 1 ; /* [0]  */
        unsigned int    reserved_0            : 31; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff60;

/* Define the union reg_date_coeff61 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    burst_start_ovrd      : 1 ; /* [0]  */
        unsigned int    burst_dura_ovrd       : 1 ; /* [1]  */
        unsigned int    cb_bound_ovrd         : 1 ; /* [2]  */
        unsigned int    pal_half_ovrd         : 1 ; /* [3]  */
        unsigned int    rgb_acrive_ovrd       : 1 ; /* [4]  */
        unsigned int    reserved_0            : 27; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_date_coeff61;

/* Define the union reg_mac_outstanding */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mstr0_routstanding : 4; /* [3..0]  */
        unsigned int mstr0_woutstanding : 4; /* [7..4]  */
        unsigned int mstr1_routstanding : 4; /* [11..8]  */
        unsigned int mstr1_woutstanding : 4; /* [15..12]  */
        unsigned int mstr2_routstanding : 4; /* [19..16]  */
        unsigned int mstr2_woutstanding : 4; /* [23..20]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_outstanding;

/* define the union reg_mac_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int split_mode : 4; /* [3..0]  */
        unsigned int arb_mode : 4; /* [7..4]  */
        unsigned int mid_enable : 1; /* [8]  */
        unsigned int reserved_0 : 3; /* [11..9]  */
        unsigned int wport_sel : 4; /* [15..12]  ---- */
        unsigned int reserved_1 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_ctrl;

/* define the union reg_mac_rchn_prio */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_prio : 1; /* [0]  */
        unsigned int v0l_prio : 1; /* [1]  */
        unsigned int v0c_prio : 1; /* [2]  */
        unsigned int v0lh_prio : 1; /* [3]  */
        unsigned int v0ch_prio : 1; /* [4]  */
        unsigned int v1l_prio : 1; /* [5]  */
        unsigned int v1c_prio : 1; /* [6]  */
        unsigned int v1lh_prio : 1; /* [7]  */
        unsigned int v1ch_prio : 1; /* [8]  */
        unsigned int g0ar_prio : 1; /* [9]  */
        unsigned int g0gb_prio : 1; /* [10]  */
        unsigned int g1ar_prio : 1; /* [11]  */
        unsigned int g1gb_prio : 1; /* [12]  */
        unsigned int v2l_prio : 1; /* [13]  */
        unsigned int v2c_prio : 1; /* [14]  */
        unsigned int v2lh_prio : 1; /* [15]  */
        unsigned int v2ch_prio : 1; /* [16]  */
        unsigned int g3ar_prio : 1; /* [17]  */
        unsigned int g3gb_prio : 1; /* [18]  */
        unsigned int reserved_0 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_rchn_prio;

/* define the union reg_mac_wchn_prio */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbcl_prio : 1; /* [0]  */
        unsigned int wbcc_prio : 1; /* [1]  */
        unsigned int wbclh_prio : 1; /* [2]  */
        unsigned int wbcch_prio : 1; /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_wchn_prio;

/* define the union reg_mac_rchn_sel0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_sel : 2; /* [1..0]  */
        unsigned int v0l_sel : 2; /* [3..2]  */
        unsigned int v0c_sel : 2; /* [5..4]  */
        unsigned int v0lh_sel : 2; /* [7..6]  */
        unsigned int v0ch_sel : 2; /* [9..8]  */
        unsigned int v1l_sel : 2; /* [11..10]  */
        unsigned int v1c_sel : 2; /* [13..12]  */
        unsigned int v1lh_sel : 2; /* [15..14]  */
        unsigned int v1ch_sel : 2; /* [17..16]  */
        unsigned int g0ar_sel : 2; /* [19..18]  */
        unsigned int g0gb_sel : 2; /* [21..20]  */
        unsigned int g1ar_sel : 2; /* [23..22]  */
        unsigned int g1gb_sel : 2; /* [25..24]  */
        unsigned int v2_sel : 2; /* [27..26]  */
        unsigned int g3_sel : 2; /* [29..28]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_rchn_sel0;

/* define the union reg_mac_wchn_sel0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbcl_sel : 2; /* [1..0]  */
        unsigned int wbcc_sel : 2; /* [3..2]  */
        unsigned int wbclh_sel : 2; /* [5..4]  */
        unsigned int wbcch_sel : 2; /* [7..6]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_wchn_sel0;

/* define the union reg_mac_bus_err_clr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bus_error_clr : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_bus_err_clr;

/* define the union reg_mac_bus_err */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mst0_r_error : 1; /* [0]  */
        unsigned int mst0_w_error : 1; /* [1]  */
        unsigned int mst1_r_error : 1; /* [2]  */
        unsigned int mst1_w_error : 1; /* [3]  */
        unsigned int mst2_r_error : 1; /* [4]  */
        unsigned int mst2_w_error : 1; /* [5]  */
        unsigned int reserved_0 : 26; /* [31..6]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_bus_err;

/* define the union reg_mac_debug_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int axi_det_enable : 1; /* [0]  */
        unsigned int reserved_0 : 3; /* [3..1]  */
        unsigned int fifo_det_mode : 4; /* [7..4]  ---- */
        unsigned int reserved_1 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_debug_ctrl;

/* define the union reg_mac_debug_clr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int axi_det_clr : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_mac_debug_clr;

/* define the union reg_vid_read_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chm_rmode : 3; /* [2..0]  */
        unsigned int reserved_0 : 1; /* [3]  */
        unsigned int lm_rmode : 3; /* [6..4]  */
        unsigned int reserved_1 : 1; /* [7]  */
        unsigned int chm_draw_mode : 2; /* [9..8]  */
        unsigned int lm_draw_mode : 2; /* [11..10]  */
        unsigned int flip_en : 1; /* [12]  */
        unsigned int chm_copy_en : 1; /* [13]  */
        unsigned int reserved_2 : 2; /* [15..14]  */
        unsigned int mute_en : 1; /* [16]  */
        unsigned int mute_req_en : 1; /* [17]  */
        unsigned int vicap_mute_en : 1; /* [18]  */
        unsigned int mrg_enable : 1; /* [19]  */
        unsigned int mrg_mute_mode : 1; /* [20]  */
        unsigned int fdr_ck_gt_en : 1; /* [21]  ---- */
        unsigned int reserved_3 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_read_ctrl;

/* define the union reg_vid_mac_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_ctrl : 2; /* [1..0]  */
        unsigned int req_len : 2; /* [3..2]  */
        unsigned int reserved_0 : 4; /* [7..4]  */
        unsigned int ofl_master : 1; /* [8]  */
        unsigned int reserved_1 : 22; /* [30..9]  */
        unsigned int pre_rd_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_mac_ctrl;

/* define the union reg_vid_out_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int draw_pixel_mode : 3; /* [2..0]  */
        unsigned int draw_pixel_en : 1; /* [3]  */
        unsigned int uv_order_en : 1; /* [4]  */
        unsigned int single_port_mode : 1; /* [5]  */
        unsigned int testpattern_en : 1; /* [6]  */
        unsigned int reserved_0 : 25; /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_out_ctrl;

/* define the union reg_vid_mute_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_mute_alpha;

/* define the union reg_vid_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_mute_bk;

/* define the union reg_vid_src_info */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int data_type : 3; /* [2..0]  */
        unsigned int data_fmt : 2; /* [4..3]  */
        unsigned int reserved_0 : 3; /* [7..5]  */
        unsigned int data_width : 2; /* [9..8]  */
        unsigned int reserved_1 : 2; /* [11..10]  */
        unsigned int field_type : 1; /* [12]  */
        unsigned int reserved_2 : 3; /* [15..13]  */
        unsigned int disp_mode : 4; /* [19..16]  */
        unsigned int dcmp_en  : 2; /* [21..20]  */
        unsigned int reserved_3 : 10 ; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_src_info;

/* define the union reg_vid_src_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_w : 16; /* [15..0]  */
        unsigned int src_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_src_reso;

/* define the union reg_vid_src_crop */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_crop_x : 16; /* [15..0]  */
        unsigned int src_crop_y : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_src_crop;

/* define the union reg_vid_in_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ireso_w : 16; /* [15..0]  */
        unsigned int ireso_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_in_reso;

/* define the union reg_vid_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_stride : 16; /* [15..0]  */
        unsigned int chm_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_stride;

/* define the union reg_vid_2bit_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_tile_stride : 16; /* [15..0]  */
        unsigned int chm_tile_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_2bit_stride;

/* define the union reg_vid_head_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_head_stride : 16; /* [15..0]  */
        unsigned int chm_head_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_head_stride;

/* define the union reg_vid_smmu_bypass */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_bypass_2d : 1; /* [0]  */
        unsigned int chm_bypass_2d : 1; /* [1]  */
        unsigned int lm_bypass_3d : 1; /* [2]  */
        unsigned int chm_bypass_3d : 1; /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_smmu_bypass;

/* define the union reg_vid_testpat_cfg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_speed : 10; /* [9..0]  */
        unsigned int reserved_0 : 2; /* [11..10]  */
        unsigned int tp_line_w : 1; /* [12]  */
        unsigned int tp_color_mode : 1; /* [13]  */
        unsigned int reserved_1 : 2; /* [15..14]  */
        unsigned int tp_mode : 2; /* [17..16]  */
        unsigned int reserved_2 : 14; /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_testpat_cfg;

/* define the union reg_vid_testpat_seed */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_seed : 30; /* [29..0]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_testpat_seed;

/* define the union reg_vid_dcmp_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int c_is_lossless : 1; /* [0]  */
        unsigned int l_is_lossless : 1; /* [1]  */
        unsigned int c_cmp_mode : 1; /* [2]  */
        unsigned int l_cmp_mode : 1; /* [3]  */
        unsigned int c_cmp_rate : 2; /* [5..4]  */
        unsigned int l_cmp_rate : 2; /* [7..6]  */
        unsigned int mem_mode : 1; /* [8]  */
        unsigned int reserved_0 : 23; /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_vid_dcmp_ctrl;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_glb_info */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ice_en                : 1  ; /* [0]  */
        unsigned int    is_lossless           : 1  ; /* [1]  */
        unsigned int    cmp_mode              : 1  ; /* [2]  */
        unsigned int    max_mb_qp_y           : 3  ; /* [5..3]  */
        unsigned int    reserved_0            : 10 ; /* [15..6]  */
        unsigned int    max_mb_qp_c           : 3  ; /* [18..16]  */
        unsigned int    seg_en                : 1  ; /* [19]  */
        unsigned int    bit_depth             : 1  ; /* [20]  */
        unsigned int    reserved_1            : 11 ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_glb_info;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_frame_size */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    frame_height          : 14 ; /* [13..0]  */
        unsigned int    reserved_0            : 2  ; /* [15..14]  */
        unsigned int    frame_width           : 14 ; /* [29..16]  */
        unsigned int    reserved_1            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_frame_size;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_smth_deltabits_thr */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    smooth_deltabits_thr  : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_smth_deltabits_thr;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_error_sta */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dcmp_error            : 1  ; /* [0]  */
        unsigned int    forgive               : 1  ; /* [1]  */
        unsigned int    consume               : 1  ; /* [2]  */
        unsigned int    reserved_0            : 29 ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_error_sta;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_glb_info_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ice_en                : 1  ; /* [0]  */
        unsigned int    is_lossless           : 1  ; /* [1]  */
        unsigned int    cmp_mode              : 1  ; /* [2]  */
        unsigned int    max_mb_qp_y           : 3  ; /* [5..3]  */
        unsigned int    reserved_0            : 10 ; /* [15..6]  */
        unsigned int    max_mb_qp_c           : 3  ; /* [18..16]  */
        unsigned int    seg_en                : 1  ; /* [19]  */
        unsigned int    bit_depth             : 1  ; /* [20]  */
        unsigned int    reserved_1            : 11 ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_glb_info_c;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_frame_size_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    frame_height          : 14 ; /* [13..0]  */
        unsigned int    reserved_0            : 2  ; /* [15..14]  */
        unsigned int    frame_width           : 14 ; /* [29..16]  */
        unsigned int    reserved_1            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_frame_size_c;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_smth_deltabits_thr_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    smooth_deltabits_thr  : 8  ; /* [7..0]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_smth_deltabits_thr_c;

/* Define the union reg_vdp_v3r2_lineseg_dcmp_error_sta_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dcmp_error            : 1  ; /* [0]  */
        unsigned int    forgive               : 1  ; /* [1]  */
        unsigned int    consume               : 1  ; /* [2]  */
        unsigned int    reserved_0            : 29 ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_dcmp_error_sta_c;

/* Define the union reg_gfx_read_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int read_mode : 2; /* [1..0]  */
        unsigned int reserved_0 : 2; /* [3..2]  */
        unsigned int draw_mode : 2; /* [5..4]  */
        unsigned int reserved_1 : 2; /* [7..6]  */
        unsigned int flip_en : 1; /* [8]  */
        unsigned int reserved_2 : 1; /* [9]  */
        unsigned int mute_en : 1; /* [10]  */
        unsigned int mute_req_en : 1; /* [11]  */
        unsigned int fdr_ck_gt_en : 1; /* [12]  ---- */
        unsigned int reserved_3 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_read_ctrl;

/* define the union reg_gfx_mac_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_ctrl : 2; /* [1..0]  */
        unsigned int req_len : 2; /* [3..2]  */
        unsigned int reserved_0 : 4; /* [7..4]  */
        unsigned int ofl_master : 1; /* [8]  */
        unsigned int reserved_1 : 23; /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_mac_ctrl;

/* define the union reg_gfx_out_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int palpha_range : 1; /* [0]  */
        unsigned int palpha_en : 1; /* [1]  */
        unsigned int reserved_0 : 2; /* [3..2]  */
        unsigned int key_mode : 1; /* [4]  */
        unsigned int key_en : 1; /* [5]  */
        unsigned int reserved_1 : 2; /* [7..6]  */
        unsigned int bitext : 2; /* [9..8]  */
        unsigned int premulti_en : 1; /* [10]  */
        unsigned int testpattern_en : 1; /* [11]  */
        unsigned int reserved_2 : 20; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_out_ctrl;

/* define the union reg_gfx_mute_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_mute_alpha;

/* define the union reg_gfx_mute_bk */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10; /* [9..0]  */
        unsigned int mute_cb : 10; /* [19..10]  */
        unsigned int mute_y : 10; /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_mute_bk;

/* define the union reg_gfx_smmu_bypass */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smmu_bypass_2d : 1; /* [0]  */
        unsigned int smmu_bypass_3d : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_smmu_bypass;

/* define the union reg_gfx_1555_alpha */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int alpha_0 : 8; /* [7..0]  */
        unsigned int alpha_1 : 8; /* [15..8]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_1555_alpha;

/* define the union reg_gfx_src_info */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ifmt : 8; /* [7..0]  */
        unsigned int reserved_0 : 8; /* [15..8]  */
        unsigned int disp_mode : 4; /* [19..16]  */
        unsigned int dcmp_en : 1; /* [20]  */
        unsigned int reserved_1 : 11; /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_src_info;

/* define the union reg_gfx_src_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_w : 16; /* [15..0]  */
        unsigned int src_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_src_reso;

/* define the union reg_gfx_src_crop */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_crop_x : 16; /* [15..0]  */
        unsigned int src_crop_y : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_src_crop;

/* define the union reg_gfx_ireso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ireso_w : 16; /* [15..0]  */
        unsigned int ireso_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_ireso;

/* define the union reg_gfx_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int surface_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_stride;

/* define the union reg_gfx_ckey_max */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int key_b_max : 8; /* [7..0]  */
        unsigned int key_g_max : 8; /* [15..8]  */
        unsigned int key_r_max : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_ckey_max;

/* define the union reg_gfx_ckey_min */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int key_b_min : 8; /* [7..0]  */
        unsigned int key_g_min : 8; /* [15..8]  */
        unsigned int key_r_min : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_ckey_min;

/* define the union reg_gfx_ckey_mask */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int key_b_msk : 8; /* [7..0]  */
        unsigned int key_g_msk : 8; /* [15..8]  */
        unsigned int key_r_msk : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_ckey_mask;

/* define the union reg_gfx_testpat_cfg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_speed : 10; /* [9..0]  */
        unsigned int reserved_0 : 2; /* [11..10]  */
        unsigned int tp_line_w : 1; /* [12]  */
        unsigned int tp_color_mode : 1; /* [13]  */
        unsigned int reserved_1 : 2; /* [15..14]  */
        unsigned int tp_mode : 2; /* [17..16]  */
        unsigned int reserved_2 : 14; /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_testpat_cfg;

/* define the union reg_gfx_testpat_seed */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_seed : 30; /* [29..0]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_testpat_seed;

/* define the union reg_gfx_dcmp_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int is_lossless : 1; /* [0]  */
        unsigned int is_lossless_a : 1; /* [1]  */
        unsigned int cmp_mode : 1; /* [2]  */
        unsigned int osd_mode : 2; /* [4..3]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_dcmp_ctrl;

/* define the union reg_gfx_dcmp_wrong_sta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bs_err : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_dcmp_wrong_sta;

/* define the union reg_wbc_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 4; /* [3..0]  */
        unsigned int data_width : 1; /* [4]  */
        unsigned int reserved_1 : 3; /* [7..5]  */
        unsigned int uv_order : 1; /* [8]  */
        unsigned int flip_en : 1; /* [9]  */
        unsigned int align_mode : 1; /* [10]  */
        unsigned int    reserved_2            : 3  ; /* [13..11]  */
        unsigned int    cap_ck_gt_en          : 1  ; /* [14]  */
        unsigned int    reserved_3            : 14 ; /* [28..15]  */
        unsigned int    wbc_cmp_en            : 1  ; /* [29]  */
        unsigned int    reserved_4            : 2  ; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_ctrl;

/* define the union reg_wbc_mac_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 2; /* [11..10]  */
        unsigned int wbc_len : 2; /* [13..12]  */
        unsigned int reserved_1 : 18; /* [31..14]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_mac_ctrl;

/* define the union reg_wbc_smmu_bypass */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_bypass : 1; /* [0]  */
        unsigned int c_bypass : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_smmu_bypass;

/* define the union reg_wbc_lowdlyctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wb_per_line_num : 12; /* [11..0]  */
        unsigned int partfns_line_num : 12; /* [23..12]  */
        unsigned int reserved_0 : 6; /* [29..24]  */
        unsigned int lowdly_test : 1; /* [30]  */
        unsigned int lowdly_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_lowdlyctrl;

/* define the union reg_wbc_lowdlysta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int part_finish : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_lowdlysta;

/* define the union reg_wbc_ystride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_ystride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_ystride;

/* define the union reg_wbc_cstride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_cstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cstride;

/* define the union reg_wbc_ynstride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_ynstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_ynstride;

/* define the union reg_wbc_cnstride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_cnstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cnstride;

/* define the union reg_wbc_sta */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_l_busy : 1; /* [0]  */
        unsigned int wbc_c_busy : 1; /* [1]  */
        unsigned int wbc_lh_busy : 1; /* [2]  */
        unsigned int wbc_ch_busy : 1; /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_sta;

/* define the union reg_wbc_line_num */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_l_linenum : 16; /* [15..0]  */
        unsigned int wbc_c_linenum : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_line_num;

/* define the union reg_wbc_cap_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cap_width : 16; /* [15..0]  */
        unsigned int cap_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cap_reso;

/* Define the union reg_vdp_v3r2_lineseg_cmp_glb_info */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ice_en                : 1  ; /* [0]  */
        unsigned int    cmp_mode              : 1  ; /* [1]  */
        unsigned int    is_lossless           : 1  ; /* [2]  */
        unsigned int    chroma_en             : 1  ; /* [3]  */
        unsigned int    esl_qp                : 3  ; /* [6..4]  */
        unsigned int    bit_depth             : 1  ; /* [7]  */
        unsigned int    mirror_en             : 1  ; /* [8]  */
        unsigned int    seg_en                : 1  ; /* [9]  */
        unsigned int    reserved_0            : 22 ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_glb_info;

/* Define the union reg_vdp_v3r2_lineseg_cmp_frame_size */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    frame_width           : 14 ; /* [13..0]  */
        unsigned int    reserved_0            : 2  ; /* [15..14]  */
        unsigned int    frame_height          : 14 ; /* [29..16]  */
        unsigned int    reserved_1            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_frame_size;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    big_grad_thr          : 8  ; /* [7..0]  */
        unsigned int    diff_thr              : 8  ; /* [15..8]  */
        unsigned int    noise_pix_num_thr     : 6  ; /* [21..16]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg0;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    qp_inc1_bits_thr      : 8  ; /* [7..0]  */
        unsigned int    qp_inc2_bits_thr      : 8  ; /* [15..8]  */
        unsigned int    qp_dec1_bits_thr      : 8  ; /* [23..16]  */
        unsigned int    qp_dec2_bits_thr      : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg1;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg12 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    buffer_init_bits      : 16 ; /* [15..0]  */
        unsigned int    buffer_size           : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg12;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg13 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    budget_mb_bits        : 10 ; /* [9..0]  */
        unsigned int    budget_mb_bits_last   : 10 ; /* [19..10]  */
        unsigned int    min_mb_bits           : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg13;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg16 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    smooth_status_thr     : 4  ; /* [3..0]  */
        unsigned int    smooth_deltabits_thr  : 8  ; /* [11..4]  */
        unsigned int    max_mb_qp             : 3  ; /* [14..12]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg16;

/* Define the union reg_vdp_v3r2_lineseg_cmp_glb_st */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    max_left_bits_buffer  : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_glb_st;

/* Define the union reg_vdp_v3r2_lineseg_cmp_glb_info_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    ice_en                : 1  ; /* [0]  */
        unsigned int    cmp_mode              : 1  ; /* [1]  */
        unsigned int    is_lossless           : 1  ; /* [2]  */
        unsigned int    chroma_en             : 1  ; /* [3]  */
        unsigned int    esl_qp                : 3  ; /* [6..4]  */
        unsigned int    bit_depth             : 1  ; /* [7]  */
        unsigned int    mirror_en             : 1  ; /* [8]  */
        unsigned int    seg_en                : 1  ; /* [9]  */
        unsigned int    reserved_0            : 22 ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_glb_info_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_frame_size_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    frame_width           : 14 ; /* [13..0]  */
        unsigned int    reserved_0            : 2  ; /* [15..14]  */
        unsigned int    frame_height          : 14 ; /* [29..16]  */
        unsigned int    reserved_1            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_frame_size_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg0_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    big_grad_thr          : 8  ; /* [7..0]  */
        unsigned int    diff_thr              : 8  ; /* [15..8]  */
        unsigned int    noise_pix_num_thr     : 6  ; /* [21..16]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg0_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg1_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    qp_inc1_bits_thr      : 8  ; /* [7..0]  */
        unsigned int    qp_inc2_bits_thr      : 8  ; /* [15..8]  */
        unsigned int    qp_dec1_bits_thr      : 8  ; /* [23..16]  */
        unsigned int    qp_dec2_bits_thr      : 8  ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg1_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg12_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    buffer_init_bits      : 16 ; /* [15..0]  */
        unsigned int    buffer_size           : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg12_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg13_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    budget_mb_bits        : 10 ; /* [9..0]  */
        unsigned int    budget_mb_bits_last   : 10 ; /* [19..10]  */
        unsigned int    min_mb_bits           : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg13_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_rc_cfg16_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    smooth_status_thr     : 4  ; /* [3..0]  */
        unsigned int    smooth_deltabits_thr  : 8  ; /* [11..4]  */
        unsigned int    max_mb_qp             : 3  ; /* [14..12]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_rc_cfg16_c;

/* Define the union reg_vdp_v3r2_lineseg_cmp_glb_st_c */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    max_left_bits_buffer  : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_vdp_v3r2_lineseg_cmp_glb_st_c;

/* Define the union reg_wbc_cmp_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 17; /* [26..10]  */
        unsigned int mem_mode : 1; /* [27]  */
        unsigned int data_width : 1; /* [28]  */
        unsigned int reserved_1 : 1; /* [29]  */
        unsigned int l_cmp_en : 1; /* [30]  */
        unsigned int wbc_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_ctrl;

/* define the union reg_wbc_cmp_upd */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_upd;

/* define the union reg_wbc_cmp_height */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int c_max_height : 13; /* [12..0]  */
        unsigned int l_max_height : 13; /* [25..13]  */
        unsigned int addr_mode : 1; /* [26]  */
        unsigned int fsize_mode : 1; /* [27]  */
        unsigned int rgb_cmp_mode : 2; /* [29..28]  */
        unsigned int pause_mode : 1; /* [30]  */
        unsigned int buffer_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_height;

/* define the union reg_wbc_cmp_oreso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12; /* [11..0]  */
        unsigned int oh : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_cmp_oreso;

/* define the union reg_wbc_od_state */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int addr_err : 1; /* [0]  */
        unsigned int he_addr_err0 : 1; /* [1]  */
        unsigned int he_addr_err1 : 1; /* [2]  */
        unsigned int he_addr_err2 : 1; /* [3]  */
        unsigned int w_addr_err : 1; /* [4]  */
        unsigned int he_fsize_err0 : 1; /* [5]  */
        unsigned int he_fsize_err1 : 1; /* [6]  */
        unsigned int he_fsize_err2 : 1; /* [7]  */
        unsigned int w_fsize_err : 1; /* [8]  */
        unsigned int he_fsize_war0 : 1; /* [9]  */
        unsigned int he_fsize_war1 : 1; /* [10]  */
        unsigned int he_fsize_war2 : 1; /* [11]  */
        unsigned int w_fsize_war : 1; /* [12]  */
        unsigned int reserved_0 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_wbc_od_state;

/* define the union reg_od_pic_osd_glb_info */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int is_lossless : 1; /* [0]  */
        unsigned int is_lossless_a : 1; /* [1]  */
        unsigned int cmp_mode : 1; /* [2]  */
        unsigned int source_mode : 3; /* [5..3]  */
        unsigned int part_cmp_en : 1; /* [6]  */
        unsigned int top_pred_en : 1; /* [7]  */
        unsigned int graphic_en : 1; /* [8]  */
        unsigned int reserved_0 : 23; /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_glb_info;

/* define the union reg_od_pic_osd_frame_size */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 13; /* [12..0]  */
        unsigned int reserved_0 : 3; /* [15..13]  */
        unsigned int frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3; /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_frame_size;

/* define the union reg_od_pic_osd_rc_cfg0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int min_mb_bits : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg0;

/* define the union reg_od_pic_osd_rc_cfg1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_qp : 4; /* [3..0]  */
        unsigned int reserved_0 : 4; /* [7..4]  */
        unsigned int sad_bits_gain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4; /* [15..12]  */
        unsigned int rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5; /* [23..19]  */
        unsigned int max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg1;

/* define the union reg_od_pic_osd_rc_cfg2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9; /* [15..7]  */
        unsigned int min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg2;

/* define the union reg_od_pic_osd_rc_cfg3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 1; /* [7]  */
        unsigned int still_thr : 7; /* [14..8]  */
        unsigned int reserved_1 : 1; /* [15]  */
        unsigned int big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg3;

/* define the union reg_od_pic_osd_rc_cfg4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_pix_num_thr : 6; /* [5..0]  */
        unsigned int reserved_0 : 2; /* [7..6]  */
        unsigned int still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2; /* [15..14]  */
        unsigned int noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg4;

/* define the union reg_od_pic_osd_rc_cfg5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int noise_sad : 7; /* [6..0]  */
        unsigned int reserved_0 : 9; /* [15..7]  */
        unsigned int pix_diff_thr : 10; /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg5;

/* define the union reg_od_pic_osd_rc_cfg6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25; /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg6;

/* define the union reg_od_pic_osd_rc_cfg7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int qp_inc1_bits_thr : 8; /* [7..0]  */
        unsigned int qp_inc2_bits_thr : 8; /* [15..8]  */
        unsigned int qp_dec1_bits_thr : 8; /* [23..16]  */
        unsigned int qp_dec2_bits_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg7;

/* define the union reg_od_pic_osd_rc_cfg8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int est_err_gain : 5; /* [4..0]  */
        unsigned int reserved_0 : 11; /* [15..5]  */
        unsigned int max_est_err_level : 9; /* [24..16]  */
        unsigned int reserved_1 : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg8;

/* define the union reg_od_pic_osd_rc_cfg9 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16; /* [15..0]  */
        unsigned int vbv_buf_loss1_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 1; /* [23]  */
        unsigned int vbv_buf_loss2_thr : 7; /* [30..24]  */
        unsigned int reserved_2 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg9;

/* define the union reg_od_pic_osd_rc_cfg10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int qp_thr0 : 3; /* [2..0]  */
        unsigned int reserved_0 : 5; /* [7..3]  */
        unsigned int qp_thr1 : 3; /* [10..8]  */
        unsigned int reserved_1 : 5; /* [15..11]  */
        unsigned int qp_thr2 : 3; /* [18..16]  */
        unsigned int reserved_2 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg10;

/* define the union reg_od_pic_osd_rc_cfg11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int grph_bias_bit_thr0 : 8; /* [7..0]  */
        unsigned int grph_bias_bit_thr1 : 8; /* [15..8]  */
        unsigned int grph_ideal_bit_thr : 10; /* [25..16]  */
        unsigned int reserved_0 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg11;

/* define the union reg_od_pic_osd_rc_cfg12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int force_rc_en : 1; /* [0]  */
        unsigned int reserved_0 : 7; /* [7..1]  */
        unsigned int forcerc_bits_diff_thr : 8; /* [15..8]  */
        unsigned int reserved_1 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg12;

/* define the union reg_od_pic_osd_rc_cfg13 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int maxdiff_ctrl_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg13;

/* define the union reg_od_pic_osd_rc_cfg14 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits_cap : 10; /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int init_buf_bits_cap : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg14;

/* define the union reg_od_pic_osd_rc_cfg15 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lfw_mb_len : 7; /* [6..0]  */
        unsigned int reserved_0 : 1; /* [7]  */
        unsigned int cmplx_sad_thr : 4; /* [11..8]  */
        unsigned int reserved_1 : 4; /* [15..12]  */
        unsigned int err_thr0 : 4; /* [19..16]  */
        unsigned int reserved_2 : 4; /* [23..20]  */
        unsigned int err_thr1 : 4; /* [27..24]  */
        unsigned int reserved_3 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg15;

/* define the union reg_od_pic_osd_rc_cfg16 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int sim_num_thr : 3; /* [2..0]  */
        unsigned int reserved_0 : 5; /* [7..3]  */
        unsigned int sum_y_err_thr : 7; /* [14..8]  */
        unsigned int reserved_1 : 1; /* [15]  */
        unsigned int sum_c_err_thr : 7; /* [22..16]  */
        unsigned int reserved_2 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg16;

/* define the union reg_od_pic_osd_rc_cfg17 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cpmlx_sad_thr_y : 4; /* [3..0]  */
        unsigned int reserved_0 : 4; /* [7..4]  */
        unsigned int smpl_sad_thr_c : 4; /* [11..8]  */
        unsigned int reserved_1 : 4; /* [15..12]  */
        unsigned int smpl_sumsad_thr_y : 8; /* [23..16]  */
        unsigned int smpl_sumsad_thr_c : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg17;

/* define the union reg_od_pic_osd_rc_cfg18 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int future_sad_y_thr0 : 4; /* [3..0]  */
        unsigned int reserved_0 : 4; /* [7..4]  */
        unsigned int future_sad_c_thr0 : 4; /* [11..8]  */
        unsigned int reserved_1 : 4; /* [15..12]  */
        unsigned int future_sad_y_thr1 : 4; /* [19..16]  */
        unsigned int reserved_2 : 4; /* [23..20]  */
        unsigned int future_sad_c_thr1 : 4; /* [27..24]  */
        unsigned int reserved_3 : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg18;

/* define the union reg_od_pic_osd_rc_cfg19 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cmplx_sumsad_thr_y : 8; /* [7..0]  */
        unsigned int cmplx_sumsad_thr_c : 8; /* [15..8]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_rc_cfg19;

/* define the union reg_od_pic_osd_stat_thr */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_gap_bw_row_len_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25; /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_stat_thr;

/* define the union reg_od_pic_osd_pcmp */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int pcmp_start_hpos : 13; /* [12..0]  */
        unsigned int reserved_0 : 3; /* [15..13]  */
        unsigned int pcmp_end_hpos : 13; /* [28..16]  */
        unsigned int reserved_1 : 3; /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_pcmp;

/* define the union reg_od_pic_osd_bs_size */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_bs_size;

/* define the union reg_od_pic_osd_worst_row */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_worst_row;

/* define the union reg_od_pic_osd_best_row */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int min_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_best_row;

/* define the union reg_od_pic_osd_stat_info */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_gap_bw_row_len_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_od_pic_osd_stat_info;

/* define the union reg_v0_mrg_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    mrg_y_l4_addr         : 4  ; /* [3..0]  */
        unsigned int    mrg_c_l4_addr         : 4  ; /* [7..4]  */
        unsigned int    reserved_0            : 12 ; /* [19..8]  */
        unsigned int    mrg_edge_en           : 1  ; /* [20]  */
        unsigned int    reserved_1            : 4  ; /* [24..21]  */
        unsigned int mrg_edge_typ : 1; /* [25]  */
        unsigned int reserved_2 : 2; /* [27..26]  */
        unsigned int mrg_crop_en : 1; /* [28]  */
        unsigned int mrg_dcmp_en : 1; /* [29]  ---- */
        unsigned int mrg_mute_en : 1; /* [30]  */
        unsigned int mrg_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_ctrl;

/* define the union reg_v0_mrg_disp_pos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_xpos : 16; /* [15..0]  */
        unsigned int mrg_ypos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_disp_pos;

/* define the union reg_v0_mrg_disp_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_width : 16; /* [15..0]  */
        unsigned int mrg_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_disp_reso;

/* define the union reg_v0_mrg_src_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_width : 16; /* [15..0]  */
        unsigned int mrg_src_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_src_reso;

/* define the union reg_v0_mrg_src_offset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_hoffset : 16; /* [15..0]  */
        unsigned int mrg_src_voffset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_src_offset;

/* define the union reg_v0_mrg_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_c_stride : 16; /* [15..0]  */
        unsigned int mrg_y_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_stride;

/* define the union reg_v0_mrg_hstride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_ch_stride : 16; /* [15..0]  */
        unsigned int mrg_yh_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_hstride;

/* define the union reg_v0_mrg_read_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_region : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_read_ctrl;

/* define the union reg_v0_mrg_read_en */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v0_mrg_read_en;

/* define the union reg_v1_mrg_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int    mrg_y_l4_addr         : 4  ; /* [3..0]  */
        unsigned int    mrg_c_l4_addr         : 4  ; /* [7..4]  */
        unsigned int    reserved_0            : 12 ; /* [19..8]  */
        unsigned int    mrg_edge_en           : 1  ; /* [20]  */
        unsigned int reserved_1 : 4; /* [24..21]  */
        unsigned int mrg_edge_typ : 1; /* [25]  */
        unsigned int reserved_2 : 2; /* [27..26]  */
        unsigned int mrg_crop_en : 1; /* [28]  */
        unsigned int mrg_dcmp_en : 1; /* [29]  ---- */
        unsigned int mrg_mute_en : 1; /* [30]  */
        unsigned int mrg_en : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_ctrl;

/* define the union reg_v1_mrg_disp_pos */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_xpos : 16; /* [15..0]  */
        unsigned int mrg_ypos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_disp_pos;

/* define the union reg_v1_mrg_disp_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_width : 16; /* [15..0]  */
        unsigned int mrg_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_disp_reso;

/* define the union reg_v1_mrg_src_reso */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_width : 16; /* [15..0]  */
        unsigned int mrg_src_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_src_reso;

/* define the union reg_v1_mrg_src_offset */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_hoffset : 16; /* [15..0]  */
        unsigned int mrg_src_voffset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_src_offset;

/* define the union reg_v1_mrg_stride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_c_stride : 16; /* [15..0]  */
        unsigned int mrg_y_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_stride;

/* define the union reg_v1_mrg_hstride */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_ch_stride : 16; /* [15..0]  */
        unsigned int mrg_yh_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_hstride;

/* define the union reg_v1_mrg_read_ctrl */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_region : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_read_ctrl;

/* define the union reg_v1_mrg_read_en */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_v1_mrg_read_en;

/* define the union U_V0_ZME_HINFO */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    csc_ck_gt_en          : 1  ; /* [26]  */
        unsigned int    reserved_0            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_idc;

/* Define the union reg_v1_csc_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_odc;

/* Define the union reg_v1_csc_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_iodc;

/* Define the union reg_v1_csc_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_p0;

/* Define the union reg_v1_csc_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_p1;

/* Define the union reg_v1_csc_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_p2;

/* Define the union reg_v1_csc_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_p3;

/* Define the union reg_v1_csc_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc_p4;

/* Define the union reg_v1_csc1_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    reserved_0            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_idc;

/* Define the union reg_v1_csc1_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_odc;

/* Define the union reg_v1_csc1_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_iodc;

/* Define the union reg_v1_csc1_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_p0;

/* Define the union reg_v1_csc1_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_p1;

/* Define the union reg_v1_csc1_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_p2;

/* Define the union reg_v1_csc1_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_p3;

/* Define the union reg_v1_csc1_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v1_csc1_p4;

/* Define the union reg_v2_csc_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    csc_ck_gt_en          : 1  ; /* [26]  */
        unsigned int    reserved_0            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_idc;

/* Define the union reg_v2_csc_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_odc;

/* Define the union reg_v2_csc_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_iodc;

/* Define the union reg_v2_csc_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_p0;

/* Define the union reg_v2_csc_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_p1;

/* Define the union reg_v2_csc_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_p2;

/* Define the union reg_v2_csc_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_p3;

/* Define the union reg_v2_csc_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc_p4;

/* Define the union reg_v2_csc1_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    reserved_0            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_idc;

/* Define the union reg_v2_csc1_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_odc;

/* Define the union reg_v2_csc1_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_iodc;

/* Define the union reg_v2_csc1_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_p0;

/* Define the union reg_v2_csc1_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_p1;

/* Define the union reg_v2_csc1_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_p2;

/* Define the union reg_v2_csc1_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_p3;

/* Define the union reg_v2_csc1_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v2_csc1_p4;

/* Define the union reg_g1_csc_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    csc_ck_gt_en          : 1  ; /* [26]  */
        unsigned int    reserved_0            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_idc;

/* Define the union reg_g1_csc_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_odc;

/* Define the union reg_g1_csc_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_iodc;

/* Define the union reg_g1_csc_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_p0;

/* Define the union reg_g1_csc_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_p1;

/* Define the union reg_g1_csc_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_p2;

/* Define the union reg_g1_csc_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_p3;

/* Define the union reg_g1_csc_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc_p4;

/* Define the union reg_g1_csc1_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    reserved_0            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_idc;

/* Define the union reg_g1_csc1_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_odc;

/* Define the union reg_g1_csc1_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_iodc;

/* Define the union reg_g1_csc1_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_p0;

/* Define the union reg_g1_csc1_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_p1;

/* Define the union reg_g1_csc1_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_p2;

/* Define the union reg_g1_csc1_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_p3;

/* Define the union reg_g1_csc1_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g1_csc1_p4;

/* Define the union reg_g3_csc_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    csc_ck_gt_en          : 1  ; /* [26]  */
        unsigned int    reserved_0            : 5  ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_idc;

/* Define the union reg_g3_csc_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_odc;

/* Define the union reg_g3_csc_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_iodc;

/* Define the union reg_g3_csc_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_p0;

/* Define the union reg_g3_csc_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_p1;

/* Define the union reg_g3_csc_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_p2;

/* Define the union reg_g3_csc_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_p3;

/* Define the union reg_g3_csc_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc_p4;

/* Define the union reg_g3_csc1_idc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc0               : 11 ; /* [10..0]  */
        unsigned int    cscidc1               : 11 ; /* [21..11]  */
        unsigned int    csc_en                : 1  ; /* [22]  */
        unsigned int    csc_mode              : 3  ; /* [25..23]  */
        unsigned int    reserved_0            : 6  ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_idc;

/* Define the union reg_g3_csc1_odc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscodc0               : 11 ; /* [10..0]  */
        unsigned int    cscodc1               : 11 ; /* [21..11]  */
        unsigned int    csc_sign_mode         : 1  ; /* [22]  */
        unsigned int    reserved_0            : 9  ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_odc;

/* Define the union reg_g3_csc1_iodc */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscidc2               : 11 ; /* [10..0]  */
        unsigned int    cscodc2               : 11 ; /* [21..11]  */
        unsigned int    reserved_0            : 10 ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_iodc;

/* Define the union reg_g3_csc1_p0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp00                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp01                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_p0;

/* Define the union reg_g3_csc1_p1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp02                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp10                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_p1;

/* Define the union reg_g3_csc1_p2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp11                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp12                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_p2;

/* Define the union reg_g3_csc1_p3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp20                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 1  ; /* [15]  */
        unsigned int    cscp21                : 15 ; /* [30..16]  */
        unsigned int    reserved_1            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_p3;

/* Define the union reg_g3_csc1_p4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    cscp22                : 15 ; /* [14..0]  */
        unsigned int    reserved_0            : 17 ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_g3_csc1_p4;

/* Define the union reg_v0_cvfir_vinfo */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    out_height            : 16 ; /* [15..0]  */
        unsigned int    out_fmt               : 2  ; /* [17..16]  */
        unsigned int    out_pro               : 1  ; /* [18]  */
        unsigned int    vzme_ck_gt_en         : 1  ; /* [19]  */
        unsigned int    reserved_0            : 12 ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_vinfo;

/* Define the union reg_v0_cvfir_vsp */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vratio                : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 1  ; /* [16]  */
        unsigned int    reserved_1            : 8  ; /* [24..17]  */
        unsigned int    cvfir_mode            : 1  ; /* [25]  */
        unsigned int    reserved_2            : 1  ; /* [26]  */
        unsigned int    reserved_3            : 1  ; /* [27]  */
        unsigned int    cvmid_en              : 1  ; /* [28]  */
        unsigned int    reserved_4            : 1  ; /* [29]  */
        unsigned int    cvfir_en              : 1  ; /* [30]  */
        unsigned int    reserved_5            : 1  ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_vsp;

/* Define the union reg_v0_cvfir_voffset */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vchroma_offset        : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_voffset;

/* Define the union reg_v0_cvfir_vboffset */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vbchroma_offset       : 16 ; /* [15..0]  */
        unsigned int    reserved_0            : 16 ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_vboffset;

/* Define the union reg_v0_cvfir_vcoef0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vccoef02              : 10 ; /* [9..0]  */
        unsigned int    vccoef01              : 10 ; /* [19..10]  */
        unsigned int    vccoef00              : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_vcoef0;

/* Define the union reg_v0_cvfir_vcoef1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vccoef11              : 10 ; /* [9..0]  */
        unsigned int    vccoef10              : 10 ; /* [19..10]  */
        unsigned int    vccoef03              : 10 ; /* [29..20]  */
        unsigned int    reserved_0            : 2  ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_vcoef1;

/* Define the union reg_v0_cvfir_vcoef2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    vccoef13              : 10 ; /* [9..0]  */
        unsigned int    vccoef12              : 10 ; /* [19..10]  */
        unsigned int    reserved_0            : 12 ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} reg_v0_cvfir_vcoef2;

/* Define the union reg_gfx_osd_glb_info */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int    dcmp_en               : 1  ; /* [0]  */
        unsigned int    is_lossless           : 1  ; /* [1]  */
        unsigned int    is_lossless_a         : 1  ; /* [2]  */
        unsigned int    cmp_mode              : 1  ; /* [3]  */
        unsigned int    source_mode           : 3  ; /* [6..4]  */
        unsigned int    tpred_en              : 1  ; /* [7]  */
        unsigned int    reserved_0            : 24 ; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_osd_glb_info;

/* define the union reg_gfx_osd_frame_size */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 13; /* [12..0]  */
        unsigned int reserved_0 : 3; /* [15..13]  */
        unsigned int frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3; /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_osd_frame_size;

/* define the union reg_gfx_osd_dbg_reg */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 30; /* [29..0]  */
        unsigned int dcmp_err0 : 1; /* [30]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_osd_dbg_reg;

/* define the union reg_gfx_osd_dbg_reg1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 30; /* [29..0]  */
        unsigned int dcmp_err1 : 1; /* [30]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} reg_gfx_osd_dbg_reg1;

/* define the global struct */
typedef struct {
    volatile reg_voctrl voctrl; /* 0x0 */
    volatile reg_vointsta vointsta; /* 0x4 */
    volatile reg_vomskintsta vomskintsta; /* 0x8 */
    volatile reg_vointmsk vointmsk; /* 0xc */
    volatile reg_vodebug vodebug; /* 0x10 */
    volatile reg_vointsta1 vointsta1; /* 0x14 */
    volatile reg_vomskintsta1 vomskintsta1; /* 0x18 */
    volatile reg_vointmsk1 vointmsk1; /* 0x1c */
    volatile unsigned int vdpversion1; /* 0x20 */
    volatile unsigned int vdpversion2; /* 0x24 */
    volatile reg_volowpower_ctrl volowpower_ctrl; /* 0x28 */
    volatile reg_voufsta voufsta; /* 0x2c */
    volatile reg_voufclr voufclr; /* 0x30 */
    volatile reg_vointproc_tim vointproc_tim; /* 0x34 */
    volatile unsigned int vofpgatest; /* 0x38 */
    volatile unsigned int reserved_0[3]; /* 0x3c~0x44 3 regs */
    volatile reg_volowpower_ctrl1 volowpower_ctrl1; /* 0x48 */
    volatile reg_vofpgadef vofpgadef; /* 0x4c */
    volatile reg_volowpower_ctrl2     volowpower_ctrl2                ; /* 0x50 */
    volatile reg_volowpower_ctrl3     volowpower_ctrl3                ; /* 0x54 */
    volatile unsigned int           reserved_1[43]                  ; /* 0x58~0x100 43 regs */
    volatile reg_vomux_dac            vomux_dac                       ; /* 0x104 */
    volatile reg_vomux_testsync       vomux_testsync                  ; /* 0x108 */
    volatile reg_vomux_testdata       vomux_testdata                  ; /* 0x10c */
    volatile unsigned int           reserved_2[4]                   ; /* 0x110~0x11c 4 regs */
    volatile reg_vo_dac_ctrl          vo_dac_ctrl                     ; /* 0x120 */
    volatile reg_vo_dac_otp           vo_dac_otp                      ; /* 0x124 */
    volatile unsigned int           reserved_3[2]                   ; /* 0x128~0x12c 2 regs */
    volatile reg_vo_dac0_ctrl         vo_dac0_ctrl                    ; /* 0x130 */
    volatile reg_vo_dac1_ctrl         vo_dac1_ctrl                    ; /* 0x134 */
    volatile reg_vo_dac2_ctrl         vo_dac2_ctrl                    ; /* 0x138 */
    volatile reg_vo_dac3_ctrl         vo_dac3_ctrl                    ; /* 0x13c */
    volatile reg_vo_dac_stat0         vo_dac_stat0                    ; /* 0x140 */
    volatile unsigned int           reserved_4[111]                 ; /* 0x144~0x2fc 111 regs */
    volatile reg_cbm_bkg1 cbm_bkg1; /* 0x300 */
    volatile unsigned int reserved_5; /* 0x304 */
    volatile reg_cbm_mix1 cbm_mix1; /* 0x308 */
    volatile unsigned int reserved_6[14]; /* 0x30c~0x340 14 regs */
    volatile reg_wbc_bmp_thd wbc_bmp_thd; /* 0x344 */
    volatile unsigned int           reserved_7[2]                   ; /* 0x348~0x34c 2 regs */
    volatile unsigned int           cbm1_lay0_debug                 ; /* 0x350 */
    volatile unsigned int           cbm1_lay1_debug                 ; /* 0x354 */
    volatile unsigned int           cbm1_lay2_debug                 ; /* 0x358 */
    volatile unsigned int           cbm1_lay3_debug                 ; /* 0x35c */
    volatile unsigned int           cbm1_lay4_debug                 ; /* 0x360 */
    volatile unsigned int           cbm1_lay0_last_debug            ; /* 0x364 */
    volatile unsigned int           cbm1_lay1_last_debug            ; /* 0x368 */
    volatile unsigned int           cbm1_lay2_last_debug            ; /* 0x36c */
    volatile unsigned int           cbm1_lay3_last_debug            ; /* 0x370 */
    volatile unsigned int           cbm1_lay4_last_debug            ; /* 0x374 */
    volatile unsigned int           reserved_8[2]                   ; /* 0x378~0x37c 2 regs */
    volatile reg_cbm_bkg2 cbm_bkg2; /* 0x380 */
    volatile unsigned int reserved_9; /* 0x384 */
    volatile reg_cbm_mix2 cbm_mix2; /* 0x388 */
    volatile unsigned int reserved_10[14]; /* 0x38c~0x3c0 14 regs */
    volatile reg_hc_bmp_thd hc_bmp_thd; /* 0x3c4 */
    volatile unsigned int           reserved_11[2]                  ; /* 0x3c8~0x3cc 2 regs */
    volatile unsigned int           cbm2_lay0_debug                 ; /* 0x3d0 */
    volatile unsigned int           cbm2_lay1_debug                 ; /* 0x3d4 */
    volatile unsigned int           cbm2_lay2_debug                 ; /* 0x3d8 */
    volatile unsigned int           cbm2_lay3_debug                 ; /* 0x3dc */
    volatile unsigned int           cbm2_lay4_debug                 ; /* 0x3e0 */
    volatile unsigned int           cbm2_lay0_last_debug            ; /* 0x3e4 */
    volatile unsigned int           cbm2_lay1_last_debug            ; /* 0x3e8 */
    volatile unsigned int           cbm2_lay2_last_debug            ; /* 0x3ec */
    volatile unsigned int           cbm2_lay3_last_debug            ; /* 0x3f0 */
    volatile unsigned int           cbm2_lay4_last_debug            ; /* 0x3f4 */
    volatile unsigned int           reserved_12[2]                  ; /* 0x3f8~0x3fc 2 regs */
    volatile reg_cbm_bkg3 cbm_bkg3; /* 0x400 */
    volatile unsigned int reserved_13; /* 0x404 */
    volatile reg_cbm_mix3 cbm_mix3; /* 0x408 */
    volatile unsigned int           reserved_14[17]                 ; /* 0x40c~0x44c 17 regs */
    volatile unsigned int           cbm3_lay0_debug                 ; /* 0x450 */
    volatile unsigned int           cbm3_lay1_debug                 ; /* 0x454 */
    volatile unsigned int           cbm3_lay2_debug                 ; /* 0x458 */
    volatile unsigned int           cbm3_lay3_debug                 ; /* 0x45c */
    volatile unsigned int           cbm3_lay4_debug                 ; /* 0x460 */
    volatile unsigned int           cbm3_lay0_last_debug            ; /* 0x464 */
    volatile unsigned int           cbm3_lay1_last_debug            ; /* 0x468 */
    volatile unsigned int           cbm3_lay2_last_debug            ; /* 0x46c */
    volatile unsigned int           cbm3_lay3_last_debug            ; /* 0x470 */
    volatile unsigned int           cbm3_lay4_last_debug            ; /* 0x474 */
    volatile unsigned int           reserved_15[98]                 ; /* 0x478~0x5fc 98 regs */
    volatile reg_mixv0_bkg mixv0_bkg; /* 0x600 */
    volatile unsigned int reserved_16; /* 0x604 */
    volatile reg_mixv0_mix mixv0_mix; /* 0x608 */
    volatile unsigned int reserved_17[189]; /* 0x60c~0x8fc 189 regs */
    volatile reg_mixg0_bkg mixg0_bkg; /* 0x900 */
    volatile reg_mixg0_bkalpha mixg0_bkalpha; /* 0x904 */
    volatile reg_mixg0_mix mixg0_mix; /* 0x908 */
    volatile unsigned int reserved_18[189]; /* 0x90c~0xbfc 189 regs */
    volatile reg_link_ctrl link_ctrl; /* 0xc00 */
    volatile unsigned int reserved_19[63]; /* 0xc04~0xcfc 63 regs */
    volatile reg_vpss_ctrl vpss_ctrl; /* 0xd00 */
    volatile reg_vpss_miscellaneous vpss_miscellaneous; /* 0xd04 */
    volatile reg_vpss_ftconfig vpss_ftconfig; /* 0xd08 */
    volatile unsigned int reserved_20[5]; /* 0xd0c~0xd1c 5 regs */
    volatile unsigned int vpss_version; /* 0xd20 */
    volatile unsigned int vpss_debug0; /* 0xd24 */
    volatile unsigned int vpss_debug1; /* 0xd28 */
    volatile unsigned int vpss_debug2; /* 0xd2c */
    volatile unsigned int vpss_debug3; /* 0xd30 */
    volatile unsigned int vpss_debug4; /* 0xd34 */
    volatile unsigned int vpss_debug5; /* 0xd38 */
    volatile unsigned int vpss_debug6; /* 0xd3c */
    volatile unsigned int reserved_21[48]; /* 0xd40~0xdfc 48 regs */
    volatile unsigned int para_haddr_vhd_chn00; /* 0xe00 */
    volatile unsigned int para_addr_vhd_chn00; /* 0xe04 */
    volatile unsigned int para_haddr_vhd_chn01; /* 0xe08 */
    volatile unsigned int para_addr_vhd_chn01; /* 0xe0c */
    volatile unsigned int para_haddr_vhd_chn02; /* 0xe10 */
    volatile unsigned int para_addr_vhd_chn02; /* 0xe14 */
    volatile unsigned int para_haddr_vhd_chn03; /* 0xe18 */
    volatile unsigned int para_addr_vhd_chn03; /* 0xe1c */
    volatile unsigned int para_haddr_vhd_chn04; /* 0xe20 */
    volatile unsigned int para_addr_vhd_chn04; /* 0xe24 */
    volatile unsigned int para_haddr_vhd_chn05; /* 0xe28 */
    volatile unsigned int para_addr_vhd_chn05; /* 0xe2c */
    volatile unsigned int para_haddr_vhd_chn06; /* 0xe30 */
    volatile unsigned int para_addr_vhd_chn06; /* 0xe34 */
    volatile unsigned int para_haddr_vhd_chn07; /* 0xe38 */
    volatile unsigned int para_addr_vhd_chn07; /* 0xe3c */
    volatile unsigned int para_haddr_vhd_chn08; /* 0xe40 */
    volatile unsigned int para_addr_vhd_chn08; /* 0xe44 */
    volatile unsigned int para_haddr_vhd_chn09; /* 0xe48 */
    volatile unsigned int para_addr_vhd_chn09; /* 0xe4c */
    volatile unsigned int para_haddr_vhd_chn10; /* 0xe50 */
    volatile unsigned int para_addr_vhd_chn10; /* 0xe54 */
    volatile unsigned int para_haddr_vhd_chn11; /* 0xe58 */
    volatile unsigned int para_addr_vhd_chn11; /* 0xe5c */
    volatile unsigned int para_haddr_vhd_chn12; /* 0xe60 */
    volatile unsigned int para_addr_vhd_chn12; /* 0xe64 */
    volatile unsigned int para_haddr_vhd_chn13; /* 0xe68 */
    volatile unsigned int para_addr_vhd_chn13; /* 0xe6c */
    volatile unsigned int para_haddr_vhd_chn14; /* 0xe70 */
    volatile unsigned int para_addr_vhd_chn14; /* 0xe74 */
    volatile unsigned int para_haddr_vhd_chn15; /* 0xe78 */
    volatile unsigned int para_addr_vhd_chn15; /* 0xe7c */
    volatile unsigned int para_haddr_vhd_chn16; /* 0xe80 */
    volatile unsigned int para_addr_vhd_chn16; /* 0xe84 */
    volatile unsigned int para_haddr_vhd_chn17; /* 0xe88 */
    volatile unsigned int para_addr_vhd_chn17; /* 0xe8c */
    volatile unsigned int para_haddr_vhd_chn18; /* 0xe90 */
    volatile unsigned int para_addr_vhd_chn18; /* 0xe94 */
    volatile unsigned int para_haddr_vhd_chn19; /* 0xe98 */
    volatile unsigned int para_addr_vhd_chn19; /* 0xe9c */
    volatile unsigned int para_haddr_vhd_chn20; /* 0xea0 */
    volatile unsigned int para_addr_vhd_chn20; /* 0xea4 */
    volatile unsigned int para_haddr_vhd_chn21; /* 0xea8 */
    volatile unsigned int para_addr_vhd_chn21; /* 0xeac */
    volatile unsigned int para_haddr_vhd_chn22; /* 0xeb0 */
    volatile unsigned int para_addr_vhd_chn22; /* 0xeb4 */
    volatile unsigned int para_haddr_vhd_chn23; /* 0xeb8 */
    volatile unsigned int para_addr_vhd_chn23; /* 0xebc */
    volatile unsigned int para_haddr_vhd_chn24; /* 0xec0 */
    volatile unsigned int para_addr_vhd_chn24; /* 0xec4 */
    volatile unsigned int para_haddr_vhd_chn25; /* 0xec8 */
    volatile unsigned int para_addr_vhd_chn25; /* 0xecc */
    volatile unsigned int para_haddr_vhd_chn26; /* 0xed0 */
    volatile unsigned int para_addr_vhd_chn26; /* 0xed4 */
    volatile unsigned int para_haddr_vhd_chn27; /* 0xed8 */
    volatile unsigned int para_addr_vhd_chn27; /* 0xedc */
    volatile unsigned int para_haddr_vhd_chn28; /* 0xee0 */
    volatile unsigned int para_addr_vhd_chn28; /* 0xee4 */
    volatile unsigned int para_haddr_vhd_chn29; /* 0xee8 */
    volatile unsigned int para_addr_vhd_chn29; /* 0xeec */
    volatile unsigned int para_haddr_vhd_chn30; /* 0xef0 */
    volatile unsigned int para_addr_vhd_chn30; /* 0xef4 */
    volatile unsigned int para_haddr_vhd_chn31; /* 0xef8 */
    volatile unsigned int para_addr_vhd_chn31; /* 0xefc */
    volatile reg_para_up_vhd para_up_vhd; /* 0xf00 */
    volatile unsigned int para_haddr_vsd_chn00; /* 0xf04 */
    volatile unsigned int para_addr_vsd_chn00; /* 0xf08 */
    volatile unsigned int para_haddr_vsd_chn01; /* 0xf0c */
    volatile unsigned int para_addr_vsd_chn01; /* 0xf10 */
    volatile unsigned int para_haddr_vsd_chn02; /* 0xf14 */
    volatile unsigned int para_addr_vsd_chn02; /* 0xf18 */
    volatile unsigned int para_haddr_vsd_chn03; /* 0xf1c */
    volatile unsigned int para_addr_vsd_chn03; /* 0xf20 */
    volatile unsigned int para_haddr_vsd_chn04; /* 0xf24 */
    volatile unsigned int para_addr_vsd_chn04; /* 0xf28 */
    volatile unsigned int para_haddr_vsd_chn05; /* 0xf2c */
    volatile unsigned int para_addr_vsd_chn05; /* 0xf30 */
    volatile unsigned int para_haddr_vsd_chn06; /* 0xf34 */
    volatile unsigned int para_addr_vsd_chn06; /* 0xf38 */
    volatile unsigned int para_haddr_vsd_chn07; /* 0xf3c */
    volatile unsigned int para_addr_vsd_chn07; /* 0xf40 */
    volatile reg_para_up_vsd para_up_vsd; /* 0xf44 */
    volatile reg_para_conflict_clr para_conflict_clr; /* 0xf48 */
    volatile reg_para_conflict_sta para_conflict_sta; /* 0xf4c */
    volatile unsigned int reserved_22[44]; /* 0xf50~0xffc 44 regs */
    volatile reg_v0_ctrl v0_ctrl; /* 0x1000 */
    volatile reg_v0_upd v0_upd; /* 0x1004 */
    volatile reg_v0_0reso_read v0_0reso_read; /* 0x1008 */
    volatile unsigned int           reserved_23                     ; /* 0x100c */
    volatile reg_v0_ireso             v0_ireso                        ; /* 0x1010 */
    volatile unsigned int           reserved_24[27]                 ; /* 0x1014~0x107c 27 regs */
    volatile reg_v0_dfpos v0_dfpos; /* 0x1080 */
    volatile reg_v0_dlpos v0_dlpos; /* 0x1084 */
    volatile reg_v0_vfpos v0_vfpos; /* 0x1088 */
    volatile reg_v0_vlpos v0_vlpos; /* 0x108c */
    volatile reg_v0_bk v0_bk; /* 0x1090 */
    volatile reg_v0_alpha v0_alpha; /* 0x1094 */
    volatile reg_v0_mute_bk v0_mute_bk; /* 0x1098 */
    volatile unsigned int reserved_25; /* 0x109c */
    volatile reg_v0_rimwidth v0_rimwidth; /* 0x10a0 */
    volatile reg_v0_rimcol0 v0_rimcol0; /* 0x10a4 */
    volatile reg_v0_rimcol1 v0_rimcol1; /* 0x10a8 */
    volatile unsigned int reserved_26[85]; /* 0x10ac~0x11fc 85 regs */
    volatile reg_v0_hipp_csc_ctrl v0_hipp_csc_ctrl; /* 0x1200 */
    volatile reg_v0_hipp_csc_coef00 v0_hipp_csc_coef00; /* 0x1204 */
    volatile reg_v0_hipp_csc_coef01 v0_hipp_csc_coef01; /* 0x1208 */
    volatile reg_v0_hipp_csc_coef02 v0_hipp_csc_coef02; /* 0x120c */
    volatile reg_v0_hipp_csc_coef10 v0_hipp_csc_coef10; /* 0x1210 */
    volatile reg_v0_hipp_csc_coef11 v0_hipp_csc_coef11; /* 0x1214 */
    volatile reg_v0_hipp_csc_coef12 v0_hipp_csc_coef12; /* 0x1218 */
    volatile reg_v0_hipp_csc_coef20 v0_hipp_csc_coef20; /* 0x121c */
    volatile reg_v0_hipp_csc_coef21 v0_hipp_csc_coef21; /* 0x1220 */
    volatile reg_v0_hipp_csc_coef22 v0_hipp_csc_coef22; /* 0x1224 */
    volatile reg_v0_hipp_csc_scale v0_hipp_csc_scale; /* 0x1228 */
    volatile reg_v0_hipp_csc_idc0 v0_hipp_csc_idc0; /* 0x122c */
    volatile reg_v0_hipp_csc_idc1 v0_hipp_csc_idc1; /* 0x1230 */
    volatile reg_v0_hipp_csc_idc2 v0_hipp_csc_idc2; /* 0x1234 */
    volatile reg_v0_hipp_csc_odc0 v0_hipp_csc_odc0; /* 0x1238 */
    volatile reg_v0_hipp_csc_odc1 v0_hipp_csc_odc1; /* 0x123c */
    volatile reg_v0_hipp_csc_odc2 v0_hipp_csc_odc2; /* 0x1240 */
    volatile reg_v0_hipp_csc_min_y v0_hipp_csc_min_y; /* 0x1244 */
    volatile reg_v0_hipp_csc_min_c v0_hipp_csc_min_c; /* 0x1248 */
    volatile reg_v0_hipp_csc_max_y v0_hipp_csc_max_y; /* 0x124c */
    volatile reg_v0_hipp_csc_max_c v0_hipp_csc_max_c; /* 0x1250 */
    volatile reg_v0_hipp_csc2_coef00 v0_hipp_csc2_coef00; /* 0x1254 */
    volatile reg_v0_hipp_csc2_coef01 v0_hipp_csc2_coef01; /* 0x1258 */
    volatile reg_v0_hipp_csc2_coef02 v0_hipp_csc2_coef02; /* 0x125c */
    volatile reg_v0_hipp_csc2_coef10 v0_hipp_csc2_coef10; /* 0x1260 */
    volatile reg_v0_hipp_csc2_coef11 v0_hipp_csc2_coef11; /* 0x1264 */
    volatile reg_v0_hipp_csc2_coef12 v0_hipp_csc2_coef12; /* 0x1268 */
    volatile reg_v0_hipp_csc2_coef20 v0_hipp_csc2_coef20; /* 0x126c */
    volatile reg_v0_hipp_csc2_coef21 v0_hipp_csc2_coef21; /* 0x1270 */
    volatile reg_v0_hipp_csc2_coef22 v0_hipp_csc2_coef22; /* 0x1274 */
    volatile reg_v0_hipp_csc2_scale v0_hipp_csc2_scale; /* 0x1278 */
    volatile reg_v0_hipp_csc2_idc0 v0_hipp_csc2_idc0; /* 0x127c */
    volatile reg_v0_hipp_csc2_idc1 v0_hipp_csc2_idc1; /* 0x1280 */
    volatile reg_v0_hipp_csc2_idc2 v0_hipp_csc2_idc2; /* 0x1284 */
    volatile reg_v0_hipp_csc2_odc0 v0_hipp_csc2_odc0; /* 0x1288 */
    volatile reg_v0_hipp_csc2_odc1 v0_hipp_csc2_odc1; /* 0x128c */
    volatile reg_v0_hipp_csc2_odc2 v0_hipp_csc2_odc2; /* 0x1290 */
    volatile reg_v0_hipp_csc2_min_y v0_hipp_csc2_min_y; /* 0x1294 */
    volatile reg_v0_hipp_csc2_min_c v0_hipp_csc2_min_c; /* 0x1298 */
    volatile reg_v0_hipp_csc2_max_y v0_hipp_csc2_max_y; /* 0x129c */
    volatile reg_v0_hipp_csc2_max_c v0_hipp_csc2_max_c; /* 0x12a0 */
    volatile unsigned int reserved_27[19]; /* 0x12a4~0x12ec 19 regs */
    volatile reg_v0_hipp_csc_ink_ctrl v0_hipp_csc_ink_ctrl; /* 0x12f0 */
    volatile reg_v0_hipp_csc_ink_pos v0_hipp_csc_ink_pos; /* 0x12f4 */
    volatile unsigned int v0_hipp_csc_ink_data; /* 0x12f8 */
    volatile unsigned int v0_hipp_csc_ink_data2; /* 0x12fc */
    volatile reg_v0_zme_hinfo         v0_zme_hinfo                    ; /* 0x1300 */
    volatile reg_v0_zme_hsp           v0_zme_hsp                      ; /* 0x1304 */
    volatile reg_v0_zme_hloffset      v0_zme_hloffset                 ; /* 0x1308 */
    volatile reg_v0_zme_hcoffset      v0_zme_hcoffset                 ; /* 0x130c */
    volatile reg_v0_zme_hzone0delta   v0_zme_hzone0delta              ; /* 0x1310 */
    volatile reg_v0_zme_hzone2delta   v0_zme_hzone2delta              ; /* 0x1314 */
    volatile reg_v0_zme_hzoneend      v0_zme_hzoneend                 ; /* 0x1318 */
    volatile reg_v0_zme_hl_shootctrl   v0_zme_hl_shootctrl             ; /* 0x131c */
    volatile reg_v0_zme_hc_shootctrl   v0_zme_hc_shootctrl             ; /* 0x1320 */
    volatile reg_v0_zme_hcoef_ren     v0_zme_hcoef_ren                ; /* 0x1324 */
    volatile reg_v0_zme_hcoef_rdata   v0_zme_hcoef_rdata              ; /* 0x1328 */
    volatile unsigned int           reserved_28[53]                 ; /* 0x132c~0x13fc 53 regs */
    volatile reg_v0_zme_vinfo         v0_zme_vinfo                    ; /* 0x1400 */
    volatile reg_v0_zme_vsp           v0_zme_vsp                      ; /* 0x1404 */
    volatile reg_v0_zme_voffset       v0_zme_voffset                  ; /* 0x1408 */
    volatile reg_v0_zme_vboffset      v0_zme_vboffset                 ; /* 0x140c */
    volatile unsigned int           reserved_29[3]                  ; /* 0x1410~0x1418 3 regs */
    volatile reg_v0_zme_vl_shootctrl   v0_zme_vl_shootctrl             ; /* 0x141c */
    volatile reg_v0_zme_vc_shootctrl   v0_zme_vc_shootctrl             ; /* 0x1420 */
    volatile reg_v0_zme_vcoef_ren     v0_zme_vcoef_ren                ; /* 0x1424 */
    volatile reg_v0_zme_vcoef_rdata   v0_zme_vcoef_rdata              ; /* 0x1428 */
    volatile unsigned int           reserved_30[53]                 ; /* 0x142c~0x14fc 53 regs */
    volatile reg_v0_hfir_ctrl v0_hfir_ctrl; /* 0x1500 */
    volatile reg_v0_hfircoef01 v0_hfircoef01; /* 0x1504 */
    volatile reg_v0_hfircoef23 v0_hfircoef23; /* 0x1508 */
    volatile reg_v0_hfircoef45 v0_hfircoef45; /* 0x150c */
    volatile reg_v0_hfircoef67 v0_hfircoef67; /* 0x1510 */
    volatile unsigned int reserved_31[699]; /* 0x1514~0x1ffc 699 regs */
    volatile reg_v1_ctrl v1_ctrl; /* 0x2000 */
    volatile reg_v1_upd v1_upd; /* 0x2004 */
    volatile reg_v1_0reso_read v1_0reso_read; /* 0x2008 */
    volatile unsigned int           reserved_32                     ; /* 0x200c */
    volatile reg_v1_ireso             v1_ireso                        ; /* 0x2010 */
    volatile unsigned int           reserved_33[27]                 ; /* 0x2014~0x207c 27 regs */
    volatile reg_v1_dfpos v1_dfpos; /* 0x2080 */
    volatile reg_v1_dlpos v1_dlpos; /* 0x2084 */
    volatile reg_v1_vfpos v1_vfpos; /* 0x2088 */
    volatile reg_v1_vlpos v1_vlpos; /* 0x208c */
    volatile reg_v1_bk v1_bk; /* 0x2090 */
    volatile reg_v1_alpha v1_alpha; /* 0x2094 */
    volatile reg_v1_mute_bk v1_mute_bk; /* 0x2098 */
    volatile unsigned int reserved_34; /* 0x209c */
    volatile reg_v1_rimwidth v1_rimwidth; /* 0x20a0 */
    volatile reg_v1_rimcol0 v1_rimcol0; /* 0x20a4 */
    volatile reg_v1_rimcol1 v1_rimcol1; /* 0x20a8 */
    volatile unsigned int reserved_35[85]; /* 0x20ac~0x21fc 85 regs */
    volatile unsigned int reserved_36[64]; /* 0x2200~0x22fc v1 csc 64 regs */
    volatile unsigned int reserved_37[64]; /* 0x2300~0x23fc 64 regs */
    volatile reg_v1_cvfir_vinfo v1_cvfir_vinfo; /* 0x2400 */
    volatile reg_v1_cvfir_vsp v1_cvfir_vsp; /* 0x2404 */
    volatile reg_v1_cvfir_voffset v1_cvfir_voffset; /* 0x2408 */
    volatile reg_v1_cvfir_vboffset v1_cvfir_vboffset; /* 0x240c */
    volatile unsigned int reserved_38[8]; /* 0x2410~0x242c 8 regs */
    volatile reg_v1_cvfir_vcoef0 v1_cvfir_vcoef0; /* 0x2430 */
    volatile reg_v1_cvfir_vcoef1 v1_cvfir_vcoef1; /* 0x2434 */
    volatile reg_v1_cvfir_vcoef2 v1_cvfir_vcoef2; /* 0x2438 */
    volatile unsigned int reserved_39[49]; /* 0x243c~0x24fc 49 regs */
    volatile reg_v1_hfir_ctrl v1_hfir_ctrl; /* 0x2500 */
    volatile reg_v1_hfircoef01 v1_hfircoef01; /* 0x2504 */
    volatile reg_v1_hfircoef23 v1_hfircoef23; /* 0x2508 */
    volatile reg_v1_hfircoef45 v1_hfircoef45; /* 0x250c */
    volatile reg_v1_hfircoef67 v1_hfircoef67; /* 0x2510 */
    volatile unsigned int reserved_40[699]; /* 0x2514~0x2ffc 699 regs */
    volatile reg_v2_ctrl v2_ctrl; /* 0x3000 */
    volatile reg_v2_upd v2_upd; /* 0x3004 */
    volatile reg_v2_0reso_read v2_0reso_read; /* 0x3008 */
    volatile unsigned int           reserved_41                     ; /* 0x300c */
    volatile reg_v2_ireso             v2_ireso                        ; /* 0x3010 */
    volatile unsigned int           reserved_42[27]                 ; /* 0x3014~0x307c 27 regs */
    volatile reg_v2_dfpos v2_dfpos; /* 0x3080 */
    volatile reg_v2_dlpos v2_dlpos; /* 0x3084 */
    volatile reg_v2_vfpos v2_vfpos; /* 0x3088 */
    volatile reg_v2_vlpos v2_vlpos; /* 0x308c */
    volatile reg_v2_bk v2_bk; /* 0x3090 */
    volatile reg_v2_alpha v2_alpha; /* 0x3094 */
    volatile reg_v2_mute_bk v2_mute_bk; /* 0x3098 */
    volatile unsigned int reserved_43[89]; /* 0x309c~0x33fc 89 regs */
    volatile unsigned int reserved_44[64]; /* 0x309c~0x33fc v2 csc 64 regs */
    volatile unsigned int reserved_45[64]; /* 0x309c~0x33fc 64 regs */
    volatile reg_v2_cvfir_vinfo v2_cvfir_vinfo; /* 0x3400 */
    volatile reg_v2_cvfir_vsp v2_cvfir_vsp; /* 0x3404 */
    volatile reg_v2_cvfir_voffset v2_cvfir_voffset; /* 0x3408 */
    volatile reg_v2_cvfir_vboffset v2_cvfir_vboffset; /* 0x340c */
    volatile unsigned int reserved_46[8]; /* 0x3410~0x342c 8 regs */
    volatile reg_v2_cvfir_vcoef0 v2_cvfir_vcoef0; /* 0x3430 */
    volatile reg_v2_cvfir_vcoef1 v2_cvfir_vcoef1; /* 0x3434 */
    volatile reg_v2_cvfir_vcoef2 v2_cvfir_vcoef2; /* 0x3438 */
    volatile unsigned int reserved_47[49]; /* 0x343c~0x34fc 49 regs */
    volatile reg_v2_hfir_ctrl v2_hfir_ctrl; /* 0x3500 */
    volatile reg_v2_hfircoef01 v2_hfircoef01; /* 0x3504 */
    volatile reg_v2_hfircoef23 v2_hfircoef23; /* 0x3508 */
    volatile reg_v2_hfircoef45 v2_hfircoef45; /* 0x350c */
    volatile reg_v2_hfircoef67 v2_hfircoef67; /* 0x3510 */
    volatile unsigned int           reserved_48[699]                ; /* 0x3514~0x3ffc 699 regs */
    volatile reg_v3_ctrl              v3_ctrl                         ; /* 0x4000 */
    volatile reg_v3_upd               v3_upd                          ; /* 0x4004 */
    volatile reg_v3_0reso_read        v3_0reso_read                   ; /* 0x4008 */
    volatile unsigned int           reserved_49                     ; /* 0x400c */
    volatile reg_v3_ireso             v3_ireso                        ; /* 0x4010 */
    volatile unsigned int           reserved_50[27]                 ; /* 0x4014~0x407c 27 regs */
    volatile reg_v3_dfpos             v3_dfpos                        ; /* 0x4080 */
    volatile reg_v3_dlpos             v3_dlpos                        ; /* 0x4084 */
    volatile reg_v3_vfpos             v3_vfpos                        ; /* 0x4088 */
    volatile reg_v3_vlpos             v3_vlpos                        ; /* 0x408c */
    volatile reg_v3_bk                v3_bk                           ; /* 0x4090 */
    volatile reg_v3_alpha             v3_alpha                        ; /* 0x4094 */
    volatile reg_v3_mute_bk           v3_mute_bk                      ; /* 0x4098 */
    volatile unsigned int           reserved_51                     ; /* 0x409c */
    volatile reg_v3_rimwidth          v3_rimwidth                     ; /* 0x40a0 */
    volatile reg_v3_rimcol0           v3_rimcol0                      ; /* 0x40a4 */
    volatile reg_v3_rimcol1           v3_rimcol1                      ; /* 0x40a8 */
    volatile unsigned int           reserved_52[85]                 ; /* 0x40ac~0x41fc 85 regs */
    volatile unsigned int           reserved_53[64];                  /* 0x4200~0x42fc v3 csc 64 regs */
    volatile unsigned int           reserved_54[128]                ; /* 0x4300~0x44fc 128 regs */
    volatile reg_v3_hfir_ctrl         v3_hfir_ctrl                    ; /* 0x4500 */
    volatile reg_v3_hfircoef01        v3_hfircoef01                   ; /* 0x4504 */
    volatile reg_v3_hfircoef23        v3_hfircoef23                   ; /* 0x4508 */
    volatile reg_v3_hfircoef45        v3_hfircoef45                   ; /* 0x450c */
    volatile reg_v3_hfircoef67        v3_hfircoef67                   ; /* 0x4510 */
    volatile unsigned int           reserved_55[1211]               ; /* 0x4514~0x57fc 1211 regs */
    volatile unsigned int vp0_ctrl; /* 0x5800 */
    volatile reg_vp0_upd vp0_upd; /* 0x5804 */
    volatile reg_vp0_ireso vp0_ireso; /* 0x5808 */
    volatile unsigned int reserved_56[29]; /* 0x580c~0x587c 29 regs */
    volatile reg_vp0_lbox_ctrl vp0_lbox_ctrl; /* 0x5880 */
    volatile reg_vp0_galpha vp0_galpha; /* 0x5884 */
    volatile reg_vp0_dfpos vp0_dfpos; /* 0x5888 */
    volatile reg_vp0_dlpos vp0_dlpos; /* 0x588c */
    volatile reg_vp0_vfpos vp0_vfpos; /* 0x5890 */
    volatile reg_vp0_vlpos vp0_vlpos; /* 0x5894 */
    volatile reg_vp0_bk vp0_bk; /* 0x5898 */
    volatile reg_vp0_alpha vp0_alpha; /* 0x589c */
    volatile reg_vp0_mute_bk vp0_mute_bk; /* 0x58a0 */
    volatile unsigned int reserved_57[1495]; /* 0x58a4~0x6ffc 1495 regs */
    volatile reg_g0_ctrl g0_ctrl; /* 0x7000 */
    volatile reg_g0_upd g0_upd; /* 0x7004 */
    volatile unsigned int g0_galpha_sum; /* 0x7008 */
    volatile reg_g0_0reso_read g0_0reso_read; /* 0x700c */
    volatile reg_g0_ireso             g0_ireso                        ; /* 0x7010 */
    volatile unsigned int           reserved_58[27]                 ; /* 0x7014~0x707c 27 regs */
    volatile reg_g0_dfpos g0_dfpos; /* 0x7080 */
    volatile reg_g0_dlpos g0_dlpos; /* 0x7084 */
    volatile reg_g0_vfpos g0_vfpos; /* 0x7088 */
    volatile reg_g0_vlpos g0_vlpos; /* 0x708c */
    volatile reg_g0_bk g0_bk; /* 0x7090 */
    volatile reg_g0_alpha g0_alpha; /* 0x7094 */
    volatile reg_g0_mute_bk g0_mute_bk; /* 0x7098 */
    volatile reg_g0_lbox_ctrl g0_lbox_ctrl; /* 0x709c */
    volatile unsigned int reserved_59[24]; /* 0x70a0~0x70fc 24 regs */
    volatile reg_v0_hipp_csc_ctrl g0_hipp_csc_ctrl; /* 0x7100 */
    volatile reg_v0_hipp_csc_coef00 g0_hipp_csc_coef00; /* 0x7104 */
    volatile reg_v0_hipp_csc_coef01 g0_hipp_csc_coef01; /* 0x7108 */
    volatile reg_v0_hipp_csc_coef02 g0_hipp_csc_coef02; /* 0x710c */
    volatile reg_v0_hipp_csc_coef10 g0_hipp_csc_coef10; /* 0x7110 */
    volatile reg_v0_hipp_csc_coef11 g0_hipp_csc_coef11; /* 0x7114 */
    volatile reg_v0_hipp_csc_coef12 g0_hipp_csc_coef12; /* 0x7118 */
    volatile reg_v0_hipp_csc_coef20 g0_hipp_csc_coef20; /* 0x711c */
    volatile reg_v0_hipp_csc_coef21 g0_hipp_csc_coef21; /* 0x7120 */
    volatile reg_v0_hipp_csc_coef22 g0_hipp_csc_coef22; /* 0x7124 */
    volatile reg_v0_hipp_csc_scale g0_hipp_csc_scale; /* 0x7128 */
    volatile reg_v0_hipp_csc_idc0 g0_hipp_csc_idc0; /* 0x712c */
    volatile reg_v0_hipp_csc_idc1 g0_hipp_csc_idc1; /* 0x7130 */
    volatile reg_v0_hipp_csc_idc2 g0_hipp_csc_idc2; /* 0x7134 */
    volatile reg_v0_hipp_csc_odc0 g0_hipp_csc_odc0; /* 0x7138 */
    volatile reg_v0_hipp_csc_odc1 g0_hipp_csc_odc1; /* 0x713c */
    volatile reg_v0_hipp_csc_odc2 g0_hipp_csc_odc2; /* 0x7140 */
    volatile reg_v0_hipp_csc_min_y g0_hipp_csc_min_y; /* 0x7144 */
    volatile reg_v0_hipp_csc_min_c g0_hipp_csc_min_c; /* 0x7148 */
    volatile reg_v0_hipp_csc_max_y g0_hipp_csc_max_y; /* 0x714c */
    volatile reg_v0_hipp_csc_max_c g0_hipp_csc_max_c; /* 0x7150 */
    volatile reg_v0_hipp_csc2_coef00 g0_hipp_csc2_coef00; /* 0x7154 */
    volatile reg_v0_hipp_csc2_coef01 g0_hipp_csc2_coef01; /* 0x7158 */
    volatile reg_v0_hipp_csc2_coef02 g0_hipp_csc2_coef02; /* 0x715c */
    volatile reg_v0_hipp_csc2_coef10 g0_hipp_csc2_coef10; /* 0x7160 */
    volatile reg_v0_hipp_csc2_coef11 g0_hipp_csc2_coef11; /* 0x7164 */
    volatile reg_v0_hipp_csc2_coef12 g0_hipp_csc2_coef12; /* 0x7168 */
    volatile reg_v0_hipp_csc2_coef20 g0_hipp_csc2_coef20; /* 0x716c */
    volatile reg_v0_hipp_csc2_coef21 g0_hipp_csc2_coef21; /* 0x7170 */
    volatile reg_v0_hipp_csc2_coef22 g0_hipp_csc2_coef22; /* 0x7174 */
    volatile reg_v0_hipp_csc2_scale g0_hipp_csc2_scale; /* 0x7178 */
    volatile reg_v0_hipp_csc2_idc0 g0_hipp_csc2_idc0; /* 0x717c */
    volatile reg_v0_hipp_csc2_idc1 g0_hipp_csc2_idc1; /* 0x7180 */
    volatile reg_v0_hipp_csc2_idc2 g0_hipp_csc2_idc2; /* 0x7184 */
    volatile reg_v0_hipp_csc2_odc0 g0_hipp_csc2_odc0; /* 0x7188 */
    volatile reg_v0_hipp_csc2_odc1 g0_hipp_csc2_odc1; /* 0x718c */
    volatile reg_v0_hipp_csc2_odc2 g0_hipp_csc2_odc2; /* 0x7190 */
    volatile reg_v0_hipp_csc2_min_y g0_hipp_csc2_min_y; /* 0x7194 */
    volatile reg_v0_hipp_csc2_min_c g0_hipp_csc2_min_c; /* 0x7198 */
    volatile reg_v0_hipp_csc2_max_y g0_hipp_csc2_max_y; /* 0x719c */
    volatile reg_v0_hipp_csc2_max_c g0_hipp_csc2_max_c; /* 0x71a0 */
    volatile unsigned int reserved_60[19]; /* 0x71a4~0x71ec 19 regs */
    volatile reg_v0_hipp_csc_ink_ctrl g0_hipp_csc_ink_ctrl; /* 0x71f0 */
    volatile reg_v0_hipp_csc_ink_pos g0_hipp_csc_ink_pos; /* 0x71f4 */
    volatile unsigned int g0_hipp_csc_ink_data; /* 0x71f8 */
    volatile unsigned int g0_hipp_csc_ink_data2; /* 0x71fc */
    volatile reg_g0_dof_ctrl g0_dof_ctrl; /* 0x7200 */
    volatile reg_g0_dof_step g0_dof_step; /* 0x7204 */
    volatile reg_g0_dof_bkg g0_dof_bkg; /* 0x7208 */
    volatile reg_g0_dof_alpha g0_dof_alpha; /* 0x720c */
    volatile unsigned int reserved_61[60]; /* 0x7210~0x72fc 60 regs */
    volatile reg_g0_zme_hinfo g0_zme_hinfo; /* 0x7300 */
    volatile reg_g0_zme_hsp g0_zme_hsp; /* 0x7304 */
    volatile reg_g0_zme_hloffset g0_zme_hloffset; /* 0x7308 */
    volatile reg_g0_zme_hcoffset g0_zme_hcoffset; /* 0x730c */
    volatile unsigned int reserved_62[5]; /* 0x7310~0x7320 5 regs */
    volatile reg_g0_zme_coef_ren g0_zme_coef_ren; /* 0x7324 */
    volatile reg_g0_zme_coef_rdata g0_zme_coef_rdata; /* 0x7328 */
    volatile unsigned int reserved_63[21]; /* 0x732c~0x737c 21 regs */
    volatile reg_g0_zme_vinfo g0_zme_vinfo; /* 0x7380 */
    volatile reg_g0_zme_vsp g0_zme_vsp; /* 0x7384 */
    volatile reg_g0_zme_voffset g0_zme_voffset; /* 0x7388 */
    volatile unsigned int reserved_64[285]; /* 0x738c~0x77fc 285 regs */
    volatile reg_g1_ctrl g1_ctrl; /* 0x7800 */
    volatile reg_g1_upd g1_upd; /* 0x7804 */
    volatile unsigned int g1_galpha_sum; /* 0x7808 */
    volatile reg_g1_0reso_read g1_0reso_read; /* 0x780c */
    volatile reg_g1_ireso             g1_ireso                        ; /* 0x7810 */
    volatile unsigned int           reserved_65[27]                 ; /* 0x7814~0x787c 27 regs */
    volatile reg_g1_dfpos             g1_dfpos                        ; /* 0x7880 */
    volatile reg_g1_dlpos g1_dlpos; /* 0x7884 */
    volatile reg_g1_vfpos g1_vfpos; /* 0x7888 */
    volatile reg_g1_vlpos g1_vlpos; /* 0x788c */
    volatile reg_g1_bk g1_bk; /* 0x7890 */
    volatile reg_g1_alpha g1_alpha; /* 0x7894 */
    volatile reg_g1_mute_bk g1_mute_bk; /* 0x7898 */
    volatile reg_g1_lbox_ctrl g1_lbox_ctrl; /* 0x789c */
    volatile unsigned int reserved_66[24]; /* 0x78a0~0x78fc 24 regs */
    volatile unsigned int reserved_67[64]; /* 0x7900~0x79fc g1 csc 64 regs */
    volatile unsigned int reserved_68[384]; /* 0x7a00~0x7ffc g1 zme 384 regs */
    volatile reg_g2_ctrl              g2_ctrl                         ; /* 0x8000 */
    volatile reg_g2_upd               g2_upd                          ; /* 0x8004 */
    volatile unsigned int           g2_galpha_sum                   ; /* 0x8008 */
    volatile reg_g2_0reso_read        g2_0reso_read                   ; /* 0x800c */
    volatile reg_g2_ireso             g2_ireso                        ; /* 0x8010 */
    volatile unsigned int           reserved_72[27]                 ; /* 0x8014~0x807c 27 regs */
    volatile reg_g2_dfpos             g2_dfpos                        ; /* 0x8080 */
    volatile reg_g2_dlpos             g2_dlpos                        ; /* 0x8084 */
    volatile reg_g2_vfpos             g2_vfpos                        ; /* 0x8088 */
    volatile reg_g2_vlpos             g2_vlpos                        ; /* 0x808c */
    volatile reg_g2_bk                g2_bk                           ; /* 0x8090 */
    volatile reg_g2_alpha             g2_alpha                        ; /* 0x8094 */
    volatile reg_g2_mute_bk           g2_mute_bk                      ; /* 0x8098 */
    volatile reg_g2_lbox_ctrl         g2_lbox_ctrl                    ; /* 0x809c */
    volatile unsigned int           reserved_73[24]                 ; /* 0x80a0~0x80fc 24 regs */
    volatile unsigned int           reserved_74[64]                 ; /* 0x8100~0x81fc 64 regs */
    volatile unsigned int           reserved_75[384]                 ; /* 0x8200~0x87fc 384 regs */
    volatile reg_g3_ctrl g3_ctrl; /* 0x8800 */
    volatile reg_g3_upd g3_upd; /* 0x8804 */
    volatile unsigned int g3_galpha_sum; /* 0x8808 */
    volatile reg_g3_0reso_read g3_0reso_read; /* 0x880c */
    volatile reg_g3_ireso             g3_ireso                        ; /* 0x8810 */
    volatile unsigned int           reserved_76[27]                 ; /* 0x8814~0x887c 27 regs */
    volatile reg_g3_dfpos             g3_dfpos                        ; /* 0x8880 */
    volatile reg_g3_dlpos g3_dlpos; /* 0x8884 */
    volatile reg_g3_vfpos g3_vfpos; /* 0x8888 */
    volatile reg_g3_vlpos g3_vlpos; /* 0x888c */
    volatile reg_g3_bk g3_bk; /* 0x8890 */
    volatile reg_g3_alpha g3_alpha; /* 0x8894 */
    volatile reg_g3_mute_bk g3_mute_bk; /* 0x8898 */
    volatile reg_g3_lbox_ctrl g3_lbox_ctrl; /* 0x889c */
    volatile unsigned int reserved_77[24]; /* 0x88a0~0x88fc 24 regs */
    volatile unsigned int reserved_78[64]; /* 0x8900~0x89fc g3 csc 64 regs */
    volatile unsigned int reserved_79[896]; /* 0x8a00~0x97fc 896 regs */
    volatile unsigned int gp0_ctrl; /* 0x9800 */
    volatile reg_gp0_upd gp0_upd; /* 0x9804 */
    volatile reg_gp0_ireso gp0_ireso; /* 0x9808 */
    volatile unsigned int reserved_80[29]; /* 0x980c~0x987c 29 regs */
    volatile reg_gp0_lbox_ctrl gp0_lbox_ctrl; /* 0x9880 */
    volatile reg_gp0_galpha gp0_galpha; /* 0x9884 */
    volatile unsigned int gp0_galpha_sum; /* 0x9888 */
    volatile reg_gp0_dfpos gp0_dfpos; /* 0x988c */
    volatile reg_gp0_dlpos gp0_dlpos; /* 0x9890 */
    volatile reg_gp0_vfpos gp0_vfpos; /* 0x9894 */
    volatile reg_gp0_vlpos gp0_vlpos; /* 0x9898 */
    volatile reg_gp0_bk gp0_bk; /* 0x989c */
    volatile reg_gp0_alpha gp0_alpha; /* 0x98a0 */
    volatile reg_gp0_mute_bk gp0_mute_bk; /* 0x98a4 */
    volatile unsigned int reserved_81[22]; /* 0x98a8~0x98fc 22 regs */
    volatile reg_gp0_csc_idc gp0_csc_idc; /* 0x9900 */
    volatile reg_gp0_csc_odc gp0_csc_odc; /* 0x9904 */
    volatile reg_gp0_csc_iodc gp0_csc_iodc; /* 0x9908 */
    volatile reg_gp0_csc_p0 gp0_csc_p0; /* 0x990c */
    volatile reg_gp0_csc_p1 gp0_csc_p1; /* 0x9910 */
    volatile reg_gp0_csc_p2 gp0_csc_p2; /* 0x9914 */
    volatile reg_gp0_csc_p3 gp0_csc_p3; /* 0x9918 */
    volatile reg_gp0_csc_p4 gp0_csc_p4; /* 0x991c */
    volatile unsigned int reserved_82[1464]; /* 0x9920~0xaffc 1464 regs */
    volatile reg_wbc_g0_ctrl wbc_g0_ctrl; /* 0xb000 */
    volatile reg_wbc_g0_upd wbc_g0_upd; /* 0xb004 */
    volatile reg_wbc_g0_cmp wbc_g0_cmp; /* 0xb008 */
    volatile unsigned int reserved_83; /* 0xb00c */
    volatile unsigned int wbc_g0_ar_addr; /* 0xb010 */
    volatile unsigned int wbc_g0_gb_addr; /* 0xb014 */
    volatile reg_wbc_g0_stride wbc_g0_stride; /* 0xb018 */
    volatile unsigned int wbc_g0_offset; /* 0xb01c */
    volatile reg_wbc_g0_oreso wbc_g0_oreso; /* 0xb020 */
    volatile reg_wbc_g0_fcrop wbc_g0_fcrop; /* 0xb024 */
    volatile reg_wbc_g0_lcrop wbc_g0_lcrop; /* 0xb028 */
    volatile unsigned int reserved_84[501]; /* 0xb02c~0xb7fc 501 regs */
    volatile reg_wbc_gp0_ctrl wbc_gp0_ctrl; /* 0xb800 */
    volatile reg_wbc_gp0_upd wbc_gp0_upd; /* 0xb804 */
    volatile unsigned int reserved_85[2]; /* 0xb808~0xb80c 2 regs */
    volatile unsigned int wbc_gp0_yaddr; /* 0xb810 */
    volatile unsigned int wbc_gp0_caddr; /* 0xb814 */
    volatile reg_wbc_gp0_stride wbc_gp0_stride; /* 0xb818 */
    volatile unsigned int reserved_86; /* 0xb81c */
    volatile reg_wbc_gp0_oreso wbc_gp0_oreso; /* 0xb820 */
    volatile reg_wbc_gp0_fcrop wbc_gp0_fcrop; /* 0xb824 */
    volatile reg_wbc_gp0_lcrop wbc_gp0_lcrop; /* 0xb828 */
    volatile unsigned int reserved_87[53]; /* 0xb82c~0xb8fc 53 regs */
    volatile reg_wbc_gp0_dither_ctrl wbc_gp0_dither_ctrl; /* 0xb900 */
    volatile reg_wbc_gp0_dither_coef0 wbc_gp0_dither_coef0; /* 0xb904 */
    volatile reg_wbc_gp0_dither_coef1 wbc_gp0_dither_coef1; /* 0xb908 */
    volatile unsigned int reserved_88[17]; /* 0xb90c~0xb94c 17 regs */
    volatile reg_wbc_gp0_hpzme wbc_gp0_hpzme; /* 0xb950 */
    volatile unsigned int reserved_89[43]; /* 0xb954~0xb9fc 43 regs */
    volatile reg_wbc_me_ctrl wbc_me_ctrl; /* 0xba00 */
    volatile reg_wbc_me_upd wbc_me_upd; /* 0xba04 */
    volatile reg_wbc_me_wlen_sel wbc_me_wlen_sel; /* 0xba08 */
    volatile unsigned int reserved_90; /* 0xba0c */
    volatile unsigned int wbc_me_yaddr; /* 0xba10 */
    volatile unsigned int wbc_me_caddr; /* 0xba14 */
    volatile reg_wbc_me_stride wbc_me_stride; /* 0xba18 */
    volatile unsigned int reserved_91; /* 0xba1c */
    volatile reg_wbc_me_oreso wbc_me_oreso; /* 0xba20 */
    volatile unsigned int reserved_92[2]; /* 0xba24~0xba28 2 regs */
    volatile reg_wbc_me_smmu_bypass wbc_me_smmu_bypass; /* 0xba2c */
    volatile unsigned int reserved_93[4]; /* 0xba30~0xba3c 4 regs */
    volatile reg_wbc_me_paraup wbc_me_paraup; /* 0xba40 */
    volatile unsigned int reserved_94[3]; /* 0xba44~0xba4c 3 regs */
    volatile unsigned int wbc_me_hlcoefad; /* 0xba50 */
    volatile unsigned int wbc_me_hccoefad; /* 0xba54 */
    volatile unsigned int wbc_me_vlcoefad; /* 0xba58 */
    volatile unsigned int wbc_me_vccoefad; /* 0xba5c */
    volatile unsigned int reserved_95[36]; /* 0xba60~0xbaec 36 regs */
    volatile unsigned int wbc_me_checksum_y; /* 0xbaf0 */
    volatile unsigned int wbc_me_checksum_c; /* 0xbaf4 */
    volatile unsigned int reserved_96[2]; /* 0xbaf8~0xbafc 2 regs */
    volatile reg_wbc_me_dither_ctrl wbc_me_dither_ctrl; /* 0xbb00 */
    volatile reg_wbc_me_dither_coef0 wbc_me_dither_coef0; /* 0xbb04 */
    volatile reg_wbc_me_dither_coef1 wbc_me_dither_coef1; /* 0xbb08 */
    volatile unsigned int reserved_97[109]; /* 0xbb0c~0xbcbc 109 regs */
    volatile reg_wbc_me_zme_hsp wbc_me_zme_hsp; /* 0xbcc0 */
    volatile reg_wbc_me_zme_hloffset wbc_me_zme_hloffset; /* 0xbcc4 */
    volatile reg_wbc_me_zme_hcoffset wbc_me_zme_hcoffset; /* 0xbcc8 */
    volatile unsigned int reserved_98[3]; /* 0xbccc~0xbcd4 3 regs */
    volatile reg_wbc_me_zme_vsp wbc_me_zme_vsp; /* 0xbcd8 */
    volatile reg_wbc_me_zme_vsr wbc_me_zme_vsr; /* 0xbcdc */
    volatile reg_wbc_me_zme_voffset wbc_me_zme_voffset; /* 0xbce0 */
    volatile reg_wbc_me_zme_vboffset wbc_me_zme_vboffset; /* 0xbce4 */
    volatile unsigned int reserved_99[6]; /* 0xbce8~0xbcfc 6 regs */
    volatile reg_wbc_fi_ctrl wbc_fi_ctrl; /* 0xbd00 */
    volatile reg_wbc_fi_upd wbc_fi_upd; /* 0xbd04 */
    volatile reg_wbc_fi_wlen_sel wbc_fi_wlen_sel; /* 0xbd08 */
    volatile unsigned int reserved_100; /* 0xbd0c */
    volatile unsigned int wbc_fi_yaddr; /* 0xbd10 */
    volatile unsigned int wbc_fi_caddr; /* 0xbd14 */
    volatile reg_wbc_fi_stride wbc_fi_stride; /* 0xbd18 */
    volatile unsigned int reserved_101; /* 0xbd1c */
    volatile reg_wbc_fi_oreso wbc_fi_oreso; /* 0xbd20 */
    volatile unsigned int reserved_102[2]; /* 0xbd24~0xbd28 2 regs */
    volatile reg_wbc_fi_smmu_bypass wbc_fi_smmu_bypass; /* 0xbd2c */
    volatile unsigned int reserved_103[5]; /* 0xbd30~0xbd40 5 regs */
    volatile reg_wbc_fi_frame_size wbc_fi_frame_size; /* 0xbd44 */
    volatile unsigned int wbc_fi_y_raddr; /* 0xbd48 */
    volatile unsigned int wbc_fi_c_raddr; /* 0xbd4c */
    volatile unsigned int reserved_104[40]; /* 0xbd50~0xbdec 40 regs */
    volatile unsigned int wbc_fi_checksum_y; /* 0xbdf0 */
    volatile unsigned int wbc_fi_checksum_c; /* 0xbdf4 */
    volatile unsigned int reserved_105[6]; /* 0xbdf8~0xbe0c 6 regs */
    volatile reg_wbc_fi_hcds wbc_fi_hcds; /* 0xbe10 */
    volatile reg_wbc_fi_hcds_coef0 wbc_fi_hcds_coef0; /* 0xbe14 */
    volatile reg_wbc_fi_hcds_coef1 wbc_fi_hcds_coef1; /* 0xbe18 */
    volatile unsigned int reserved_106; /* 0xbe1c */
    volatile reg_wbc_fi_cmp_mb wbc_fi_cmp_mb; /* 0xbe20 */
    volatile reg_wbc_fi_cmp_max_min wbc_fi_cmp_max_min; /* 0xbe24 */
    volatile reg_wbc_fi_cmp_adj_thr wbc_fi_cmp_adj_thr; /* 0xbe28 */
    volatile reg_wbc_fi_cmp_big_grad wbc_fi_cmp_big_grad; /* 0xbe2c */
    volatile reg_wbc_fi_cmp_blk wbc_fi_cmp_blk; /* 0xbe30 */
    volatile reg_wbc_fi_cmp_graphic_judge wbc_fi_cmp_graphic_judge; /* 0xbe34 */
    volatile reg_wbc_fi_cmp_rc wbc_fi_cmp_rc; /* 0xbe38 */
    volatile reg_wbc_fi_cmp_frame_size wbc_fi_cmp_frame_size; /* 0xbe3c */
    volatile unsigned int reserved_107[48]; /* 0xbe40~0xbefc 48 regs */
    volatile reg_wbc_cmp_glb_info wbc_cmp_glb_info; /* 0xbf00 */
    volatile reg_wbc_cmp_framesize wbc_cmp_framesize; /* 0xbf04 */
    volatile reg_wbc_cmp_rc_cfg0 wbc_cmp_rc_cfg0; /* 0xbf08 */
    volatile reg_wbc_cmp_rc_cfg2 wbc_cmp_rc_cfg2; /* 0xbf0c */
    volatile reg_wbc_cmp_rc_cfg3 wbc_cmp_rc_cfg3; /* 0xbf10 */
    volatile reg_wbc_cmp_rc_cfg4 wbc_cmp_rc_cfg4; /* 0xbf14 */
    volatile reg_wbc_cmp_rc_cfg5 wbc_cmp_rc_cfg5; /* 0xbf18 */
    volatile reg_wbc_cmp_rc_cfg6 wbc_cmp_rc_cfg6; /* 0xbf1c */
    volatile reg_wbc_cmp_rc_cfg7 wbc_cmp_rc_cfg7; /* 0xbf20 */
    volatile reg_wbc_cmp_rc_cfg8 wbc_cmp_rc_cfg8; /* 0xbf24 */
    volatile reg_wbc_cmp_rc_cfg10 wbc_cmp_rc_cfg10; /* 0xbf28 */
    volatile reg_wbc_cmp_outsize0 wbc_cmp_outsize0; /* 0xbf2c */
    volatile unsigned int wbc_cmp_dbg_reg0; /* 0xbf30 */
    volatile reg_wbc_cmp_max_row wbc_cmp_max_row; /* 0xbf34 */
    volatile reg_wbc_bmp_ctrl wbc_bmp_ctrl; /* 0xbf38 */
    volatile reg_wbc_bmp_upd wbc_bmp_upd; /* 0xbf3c */
    volatile unsigned int wbc_bmp_yaddr; /* 0xbf40 */
    volatile unsigned int reserved_108[23]; /* 0xbf44~0xbf9c 23 regs */
    volatile reg_wbc_bmp_oreso wbc_bmp_oreso; /* 0xbfa0 */
    volatile reg_wbc_bmp_sum wbc_bmp_sum; /* 0xbfa4 */
    volatile unsigned int reserved_109[18]; /* 0xbfa8~0xbfec 18 regs */
    volatile unsigned int wbc_bmp_checksum_y; /* 0xbff0 */
    volatile unsigned int wbc_bmp_checksum_c; /* 0xbff4 */
    volatile unsigned int reserved_110[2]; /* 0xbff8~0xbffc 2 regs */
    volatile reg_wbc_dhd0_ctrl wbc_dhd0_ctrl; /* 0xc000 */
    volatile reg_wbc_dhd0_upd wbc_dhd0_upd; /* 0xc004 */
    volatile reg_wbc_dhd0_oreso wbc_dhd0_oreso; /* 0xc008 */
    volatile unsigned int reserved_111[29]; /* 0xc00c~0xc07c 29 regs */
    volatile reg_wd_hpzme_ctrl wd_hpzme_ctrl; /* 0xc080 */
    volatile reg_wd_hpzmecoef01 wd_hpzmecoef01; /* 0xc084 */
    volatile reg_wd_hpzmecoef23 wd_hpzmecoef23; /* 0xc088 */
    volatile reg_wd_hpzmecoef45 wd_hpzmecoef45; /* 0xc08c */
    volatile reg_wd_hpzmecoef67 wd_hpzmecoef67; /* 0xc090 */
    volatile unsigned int reserved_112[91]; /* 0xc094~0xc1fc 91 regs */
    volatile reg_wd_hcds_ctrl wd_hcds_ctrl; /* 0xc200 */
    volatile reg_wd_hcdscoef01 wd_hcdscoef01; /* 0xc204 */
    volatile reg_wd_hcdscoef23 wd_hcdscoef23; /* 0xc208 */
    volatile reg_wd_hcdscoef45 wd_hcdscoef45; /* 0xc20c */
    volatile reg_wd_hcdscoef67 wd_hcdscoef67; /* 0xc210 */
    volatile unsigned int reserved_113[27]; /* 0xc214~0xc27c 27 regs */
    volatile reg_dither_ctrl dither_ctrl; /* 0xc280 */
    volatile reg_dither_sed_y0 dither_sed_y0; /* 0xc284 */
    volatile reg_dither_sed_u0 dither_sed_u0; /* 0xc288 */
    volatile reg_dither_sed_v0 dither_sed_v0; /* 0xc28c */
    volatile reg_dither_sed_w0 dither_sed_w0; /* 0xc290 */
    volatile reg_dither_sed_y1 dither_sed_y1; /* 0xc294 */
    volatile reg_dither_sed_u1 dither_sed_u1; /* 0xc298 */
    volatile reg_dither_sed_v1 dither_sed_v1; /* 0xc29c */
    volatile reg_dither_sed_w1 dither_sed_w1; /* 0xc2a0 */
    volatile reg_dither_sed_y2 dither_sed_y2; /* 0xc2a4 */
    volatile reg_dither_sed_u2 dither_sed_u2; /* 0xc2a8 */
    volatile reg_dither_sed_v2 dither_sed_v2; /* 0xc2ac */
    volatile reg_dither_sed_w2 dither_sed_w2; /* 0xc2b0 */
    volatile reg_dither_sed_y3 dither_sed_y3; /* 0xc2b4 */
    volatile reg_dither_sed_u3 dither_sed_u3; /* 0xc2b8 */
    volatile reg_dither_sed_v3 dither_sed_v3; /* 0xc2bc */
    volatile reg_dither_sed_w3 dither_sed_w3; /* 0xc2c0 */
    volatile reg_dither_thr dither_thr; /* 0xc2c4 */
    volatile unsigned int reserved_114[14]; /* 0xc2c8~0xc2fc 14 regs */
    volatile reg_wd_zme_hinfo wd_zme_hinfo; /* 0xc300 */
    volatile reg_wd_zme_hsp wd_zme_hsp; /* 0xc304 */
    volatile reg_wd_zme_hloffset wd_zme_hloffset; /* 0xc308 */
    volatile reg_wd_zme_hcoffset wd_zme_hcoffset; /* 0xc30c */
    volatile unsigned int reserved_115[5]; /* 0xc310~0xc320 5 regs */
    volatile reg_wd_zme_hcoef_ren wd_zme_hcoef_ren; /* 0xc324 */
    volatile reg_wd_zme_hcoef_rdata wd_zme_hcoef_rdata; /* 0xc328 */
    volatile reg_wd_zme_hdraw wd_zme_hdraw; /* 0xc32c */
    volatile reg_wd_zme_hratio wd_zme_hratio; /* 0xc330 */
    volatile unsigned int reserved_116[51]; /* 0xc334~0xc3fc 51 regs */
    volatile reg_wd_zme_vinfo wd_zme_vinfo; /* 0xc400 */
    volatile reg_wd_zme_vsp wd_zme_vsp; /* 0xc404 */
    volatile reg_wd_zme_voffset wd_zme_voffset; /* 0xc408 */
    volatile reg_wd_zme_vboffset wd_zme_vboffset; /* 0xc40c */
    volatile unsigned int reserved_117[5]; /* 0xc410~0xc420 5 regs */
    volatile reg_wd_zme_vcoef_ren wd_zme_vcoef_ren; /* 0xc424 */
    volatile reg_wd_zme_vcoef_rdata wd_zme_vcoef_rdata; /* 0xc428 */
    volatile reg_wd_zme_vdraw wd_zme_vdraw; /* 0xc42c */
    volatile reg_wd_zme_vratio wd_zme_vratio; /* 0xc430 */
    volatile unsigned int reserved_118[755]; /* 0xc434~0xcffc 755 regs */
    volatile reg_dhd0_ctrl dhd0_ctrl; /* 0xd000 */
    volatile reg_dhd0_vsync1 dhd0_vsync1; /* 0xd004 */
    volatile reg_dhd0_vsync2 dhd0_vsync2; /* 0xd008 */
    volatile reg_dhd0_hsync1 dhd0_hsync1; /* 0xd00c */
    volatile reg_dhd0_hsync2 dhd0_hsync2; /* 0xd010 */
    volatile reg_dhd0_vplus1 dhd0_vplus1; /* 0xd014 */
    volatile reg_dhd0_vplus2 dhd0_vplus2; /* 0xd018 */
    volatile reg_dhd0_pwr dhd0_pwr; /* 0xd01c */
    volatile reg_dhd0_vtthd3 dhd0_vtthd3; /* 0xd020 */
    volatile reg_dhd0_vtthd dhd0_vtthd; /* 0xd024 */
    volatile reg_dhd0_parathd dhd0_parathd; /* 0xd028 */
    volatile reg_dhd0_precharge_thd dhd0_precharge_thd; /* 0xd02c */
    volatile reg_dhd0_start_pos dhd0_start_pos; /* 0xd030 */
    volatile reg_dhd0_start_pos1 dhd0_start_pos1; /* 0xd034 */
    volatile reg_dhd0_paraup dhd0_paraup; /* 0xd038 */
    volatile reg_dhd0_sync_inv dhd0_sync_inv; /* 0xd03c */
    volatile reg_dhd0_clk_dv_ctrl dhd0_clk_dv_ctrl; /* 0xd040 */
    volatile reg_dhd0_rgb_fix_ctrl dhd0_rgb_fix_ctrl; /* 0xd044 */
    volatile reg_dhd0_lockcfg dhd0_lockcfg; /* 0xd048 */
    volatile unsigned int dhd0_cap_frm_cnt; /* 0xd04c */
    volatile unsigned int dhd0_vdp_frm_cnt; /* 0xd050 */
    volatile unsigned int dhd0_vsync_cap_vdp_cnt; /* 0xd054 */
    volatile unsigned int dhd0_intf_chksum_y; /* 0xd058 */
    volatile unsigned int dhd0_intf_chksum_u; /* 0xd05c */
    volatile unsigned int dhd0_intf_chksum_v; /* 0xd060 */
    volatile unsigned int dhd0_intf1_chksum_y; /* 0xd064 */
    volatile unsigned int dhd0_intf1_chksum_u; /* 0xd068 */
    volatile unsigned int dhd0_intf1_chksum_v; /* 0xd06c */
    volatile reg_dhd0_intf_chksum_high1 dhd0_intf_chksum_high1; /* 0xd070 */
    volatile reg_dhd0_intf_chksum_high2 dhd0_intf_chksum_high2; /* 0xd074 */
    volatile unsigned int reserved_119[3]; /* 0xd078~0xd080 3 regs */
    volatile unsigned int dhd0_afifo_pre_thd; /* 0xd084 */
    volatile reg_dhd0_state dhd0_state; /* 0xd088 */
    volatile reg_dhd0_uf_state dhd0_uf_state; /* 0xd08c */
    volatile reg_vo_mux vo_mux; /* 0xd090 */
    volatile reg_vo_mux_sync vo_mux_sync; /* 0xd094 */
    volatile reg_vo_mux_data vo_mux_data; /* 0xd098 */
    volatile unsigned int reserved_120; /* 0xd09c */
    volatile reg_dhd0_vsync_te_state dhd0_vsync_te_state; /* 0xd0a0 */
    volatile reg_dhd0_vsync_te_state1 dhd0_vsync_te_state1; /* 0xd0a4 */
    volatile unsigned int           reserved_121[6]                 ; /* 0xd0a8~0xd0bc 6 regs */
    volatile reg_dhd0_ccdoimgmod      dhd0_ccdoimgmod                 ; /* 0xd0c0 */
    volatile reg_dhd0_ccdoposmskh     dhd0_ccdoposmskh                ; /* 0xd0c4 */
    volatile reg_dhd0_ccdoposmskl     dhd0_ccdoposmskl                ; /* 0xd0c8 */
    volatile unsigned int           reserved_122                    ; /* 0xd0cc */
    volatile reg_dhd0_dacdet1         dhd0_dacdet1                    ; /* 0xd0d0 */
    volatile reg_dhd0_dacdet2         dhd0_dacdet2                    ; /* 0xd0d4 */
    volatile unsigned int           reserved_123[2]                 ; /* 0xd0d8~0xd0dc 2 regs */
    volatile reg_dhd0_ccd_info1       dhd0_ccd_info1                  ; /* 0xd0e0 */
    volatile reg_dhd0_ccd_info2       dhd0_ccd_info2                  ; /* 0xd0e4 */
    volatile reg_dhd0_ccd_info3       dhd0_ccd_info3                  ; /* 0xd0e8 */
    volatile unsigned int           reserved_124[5]                 ; /* 0xd0ec~0xd0fc 5 regs */
    volatile reg_intf_hdmi_ctrl intf_hdmi_ctrl; /* 0xd100 */
    volatile reg_intf_hdmi_upd intf_hdmi_upd; /* 0xd104 */
    volatile reg_intf_hdmi_sync_inv intf_hdmi_sync_inv; /* 0xd108 */
    volatile unsigned int reserved_125; /* 0xd10c */
    volatile unsigned int hdmi_intf_chksum_y; /* 0xd110 */
    volatile unsigned int hdmi_intf_chksum_u; /* 0xd114 */
    volatile unsigned int hdmi_intf_chksum_v; /* 0xd118 */
    volatile reg_hdmi_intf_chksum_high hdmi_intf_chksum_high; /* 0xd11c */
    volatile unsigned int hdmi_intf1_chksum_y; /* 0xd120 */
    volatile unsigned int hdmi_intf1_chksum_u; /* 0xd124 */
    volatile unsigned int hdmi_intf1_chksum_v; /* 0xd128 */
    volatile reg_hdmi_intf1_chksum_high hdmi_intf1_chksum_high; /* 0xd12c */
    volatile unsigned int reserved_126[8]; /* 0xd130~0xd14c 8 regs */
    volatile reg_hdmi_hfir_coef0 hdmi_hfir_coef0; /* 0xd150 */
    volatile reg_hdmi_hfir_coef1 hdmi_hfir_coef1; /* 0xd154 */
    volatile reg_hdmi_hfir_coef2 hdmi_hfir_coef2; /* 0xd158 */
    volatile reg_hdmi_hfir_coef3 hdmi_hfir_coef3; /* 0xd15c */
    volatile reg_hdmi_csc_idc         hdmi_csc_idc                    ; /* 0xd160 */
    volatile reg_hdmi_csc_odc         hdmi_csc_odc                    ; /* 0xd164 */
    volatile reg_hdmi_csc_iodc        hdmi_csc_iodc                   ; /* 0xd168 */
    volatile reg_hdmi_csc_p0          hdmi_csc_p0                     ; /* 0xd16c */
    volatile reg_hdmi_csc_p1          hdmi_csc_p1                     ; /* 0xd170 */
    volatile reg_hdmi_csc_p2          hdmi_csc_p2                     ; /* 0xd174 */
    volatile reg_hdmi_csc_p3          hdmi_csc_p3                     ; /* 0xd178 */
    volatile reg_hdmi_csc_p4          hdmi_csc_p4                     ; /* 0xd17c */
    volatile reg_intf_mipi_ctrl intf_mipi_ctrl; /* 0xd180 */
    volatile reg_intf_mipi_upd intf_mipi_upd; /* 0xd184 */
    volatile reg_intf_mipi_sync_inv intf_mipi_sync_inv; /* 0xd188 */
    volatile unsigned int reserved_127; /* 0xd18c */
    volatile unsigned int mipi_intf_chksum_y; /* 0xd190 */
    volatile unsigned int mipi_intf_chksum_u; /* 0xd194 */
    volatile unsigned int mipi_intf_chksum_v; /* 0xd198 */
    volatile reg_mipi_intf_chksum_high mipi_intf_chksum_high; /* 0xd19c */
    volatile unsigned int mipi_intf1_chksum_y; /* 0xd1a0 */
    volatile unsigned int mipi_intf1_chksum_u; /* 0xd1a4 */
    volatile unsigned int mipi_intf1_chksum_v; /* 0xd1a8 */
    volatile reg_mipi_intf1_chksum_high mipi_intf1_chksum_high; /* 0xd1ac */
    volatile unsigned int reserved_128[8]; /* 0xd1b0~0xd1cc 8 regs */
    volatile reg_mipi_hfir_coef0 mipi_hfir_coef0; /* 0xd1d0 */
    volatile reg_mipi_hfir_coef1 mipi_hfir_coef1; /* 0xd1d4 */
    volatile reg_mipi_hfir_coef2 mipi_hfir_coef2; /* 0xd1d8 */
    volatile reg_mipi_hfir_coef3 mipi_hfir_coef3; /* 0xd1dc */
    volatile unsigned int reserved_129[8]; /* 0xd1e0~0xd1fc 8 regs */
    volatile reg_intf_bt_ctrl intf_bt_ctrl; /* 0xd200 */
    volatile reg_intf_bt_upd intf_bt_upd; /* 0xd204 */
    volatile reg_intf_bt_sync_inv intf_bt_sync_inv; /* 0xd208 */
    volatile unsigned int reserved_130; /* 0xd20c */
    volatile reg_bt_clip0_l bt_clip0_l; /* 0xd210 */
    volatile reg_bt_clip0_h bt_clip0_h; /* 0xd214 */
    volatile unsigned int reserved_131[26]; /* 0xd218~0xd27c 26 regs */
    volatile reg_bt_dither_ctrl bt_dither_ctrl; /* 0xd280 */
    volatile reg_bt_dither_sed_y0 bt_dither_sed_y0; /* 0xd284 */
    volatile reg_bt_dither_sed_u0 bt_dither_sed_u0; /* 0xd288 */
    volatile reg_bt_dither_sed_v0 bt_dither_sed_v0; /* 0xd28c */
    volatile reg_bt_dither_sed_w0 bt_dither_sed_w0; /* 0xd290 */
    volatile reg_bt_dither_sed_y1 bt_dither_sed_y1; /* 0xd294 */
    volatile reg_bt_dither_sed_u1 bt_dither_sed_u1; /* 0xd298 */
    volatile reg_bt_dither_sed_v1 bt_dither_sed_v1; /* 0xd29c */
    volatile reg_bt_dither_sed_w1 bt_dither_sed_w1; /* 0xd2a0 */
    volatile reg_bt_dither_sed_y2 bt_dither_sed_y2; /* 0xd2a4 */
    volatile reg_bt_dither_sed_u2 bt_dither_sed_u2; /* 0xd2a8 */
    volatile reg_bt_dither_sed_v2 bt_dither_sed_v2; /* 0xd2ac */
    volatile reg_bt_dither_sed_w2 bt_dither_sed_w2; /* 0xd2b0 */
    volatile reg_bt_dither_sed_y3 bt_dither_sed_y3; /* 0xd2b4 */
    volatile reg_bt_dither_sed_u3 bt_dither_sed_u3; /* 0xd2b8 */
    volatile reg_bt_dither_sed_v3 bt_dither_sed_v3; /* 0xd2bc */
    volatile reg_bt_dither_sed_w3 bt_dither_sed_w3; /* 0xd2c0 */
    volatile reg_bt_dither_thr bt_dither_thr; /* 0xd2c4 */
    volatile unsigned int reserved_132[10]; /* 0xd2c8~0xd2ec 10 regs */
    volatile unsigned int bt_intf_chksum_y; /* 0xd2f0 */
    volatile unsigned int bt_intf_chksum_u; /* 0xd2f4 */
    volatile unsigned int bt_intf_chksum_v; /* 0xd2f8 */
    volatile unsigned int reserved_133; /* 0xd2fc */
    volatile reg_intf_lcd_ctrl intf_lcd_ctrl; /* 0xd300 */
    volatile reg_intf_lcd_upd intf_lcd_upd; /* 0xd304 */
    volatile reg_intf_lcd_sync_inv intf_lcd_sync_inv; /* 0xd308 */
    volatile unsigned int reserved_134[29]; /* 0xd30c~0xd37c 29 regs */
    volatile reg_lcd_dither_ctrl lcd_dither_ctrl; /* 0xd380 */
    volatile reg_lcd_dither_sed_y0 lcd_dither_sed_y0; /* 0xd384 */
    volatile reg_lcd_dither_sed_u0 lcd_dither_sed_u0; /* 0xd388 */
    volatile reg_lcd_dither_sed_v0 lcd_dither_sed_v0; /* 0xd38c */
    volatile reg_lcd_dither_sed_w0 lcd_dither_sed_w0; /* 0xd390 */
    volatile reg_lcd_dither_sed_y1 lcd_dither_sed_y1; /* 0xd394 */
    volatile reg_lcd_dither_sed_u1 lcd_dither_sed_u1; /* 0xd398 */
    volatile reg_lcd_dither_sed_v1 lcd_dither_sed_v1; /* 0xd39c */
    volatile reg_lcd_dither_sed_w1 lcd_dither_sed_w1; /* 0xd3a0 */
    volatile reg_lcd_dither_sed_y2 lcd_dither_sed_y2; /* 0xd3a4 */
    volatile reg_lcd_dither_sed_u2 lcd_dither_sed_u2; /* 0xd3a8 */
    volatile reg_lcd_dither_sed_v2 lcd_dither_sed_v2; /* 0xd3ac */
    volatile reg_lcd_dither_sed_w2 lcd_dither_sed_w2; /* 0xd3b0 */
    volatile reg_lcd_dither_sed_y3 lcd_dither_sed_y3; /* 0xd3b4 */
    volatile reg_lcd_dither_sed_u3 lcd_dither_sed_u3; /* 0xd3b8 */
    volatile reg_lcd_dither_sed_v3 lcd_dither_sed_v3; /* 0xd3bc */
    volatile reg_lcd_dither_sed_w3 lcd_dither_sed_w3; /* 0xd3c0 */
    volatile reg_lcd_dither_thr lcd_dither_thr; /* 0xd3c4 */
    volatile unsigned int reserved_135[10]; /* 0xd3c8~0xd3ec 10 regs */
    volatile unsigned int lcd_intf_chksum_y; /* 0xd3f0 */
    volatile unsigned int lcd_intf_chksum_u; /* 0xd3f4 */
    volatile unsigned int lcd_intf_chksum_v; /* 0xd3f8 */
    volatile unsigned int           reserved_136                    ; /* 0xd3fc */
    volatile reg_intf_hdmi1_ctrl      intf_hdmi1_ctrl                 ; /* 0xd400 */
    volatile reg_intf_hdmi1_upd       intf_hdmi1_upd                  ; /* 0xd404 */
    volatile reg_intf_hdmi1_sync_inv   intf_hdmi1_sync_inv             ; /* 0xd408 */
    volatile unsigned int           reserved_137                    ; /* 0xd40c */
    volatile unsigned int           hdmi1_intf_chksum_y             ; /* 0xd410 */
    volatile unsigned int           hdmi1_intf_chksum_u             ; /* 0xd414 */
    volatile unsigned int           hdmi1_intf_chksum_v             ; /* 0xd418 */
    volatile reg_hdmi1_intf_chksum_high   hdmi1_intf_chksum_high          ; /* 0xd41c */
    volatile unsigned int           hdmi1_intf1_chksum_y            ; /* 0xd420 */
    volatile unsigned int           hdmi1_intf1_chksum_u            ; /* 0xd424 */
    volatile unsigned int           hdmi1_intf1_chksum_v            ; /* 0xd428 */
    volatile reg_hdmi1_intf1_chksum_high   hdmi1_intf1_chksum_high         ; /* 0xd42c */
    volatile unsigned int           reserved_138[8]                 ; /* 0xd430~0xd44c 8 regs */
    volatile reg_hdmi1_hfir_coef0     hdmi1_hfir_coef0                ; /* 0xd450 */
    volatile reg_hdmi1_hfir_coef1     hdmi1_hfir_coef1                ; /* 0xd454 */
    volatile reg_hdmi1_hfir_coef2     hdmi1_hfir_coef2                ; /* 0xd458 */
    volatile reg_hdmi1_hfir_coef3     hdmi1_hfir_coef3                ; /* 0xd45c */
    volatile unsigned int           reserved_139[40]                ; /* 0xd460~0xd4fc 40 regs */
    volatile reg_intf_vga_ctrl        intf_vga_ctrl                   ; /* 0xd500 */
    volatile reg_intf_vga_upd         intf_vga_upd                    ; /* 0xd504 */
    volatile reg_intf_vga_sync_inv    intf_vga_sync_inv               ; /* 0xd508 */
    volatile unsigned int           reserved_140[5]                 ; /* 0xd50c~0xd51c 5 regs */
    volatile reg_vga_csc_idc          vga_csc_idc                     ; /* 0xd520 */
    volatile reg_vga_csc_odc          vga_csc_odc                     ; /* 0xd524 */
    volatile reg_vga_csc_iodc         vga_csc_iodc                    ; /* 0xd528 */
    volatile reg_vga_csc_p0           vga_csc_p0                      ; /* 0xd52c */
    volatile reg_vga_csc_p1           vga_csc_p1                      ; /* 0xd530 */
    volatile reg_vga_csc_p2           vga_csc_p2                      ; /* 0xd534 */
    volatile reg_vga_csc_p3           vga_csc_p3                      ; /* 0xd538 */
    volatile reg_vga_csc_p4           vga_csc_p4                      ; /* 0xd53c */
    volatile reg_vga_hspcfg0          vga_hspcfg0                     ; /* 0xd540 */
    volatile reg_vga_hspcfg1          vga_hspcfg1                     ; /* 0xd544 */
    volatile unsigned int           reserved_141[3]                 ; /* 0xd548~0xd550 3 regs */
    volatile reg_vga_hspcfg5          vga_hspcfg5                     ; /* 0xd554 */
    volatile reg_vga_hspcfg6          vga_hspcfg6                     ; /* 0xd558 */
    volatile reg_vga_hspcfg7          vga_hspcfg7                     ; /* 0xd55c */
    volatile reg_vga_hspcfg8          vga_hspcfg8                     ; /* 0xd560 */
    volatile unsigned int           reserved_142[3]                 ; /* 0xd564~0xd56c 3 regs */
    volatile reg_vga_hspcfg12         vga_hspcfg12                    ; /* 0xd570 */
    volatile reg_vga_hspcfg13         vga_hspcfg13                    ; /* 0xd574 */
    volatile reg_vga_hspcfg14         vga_hspcfg14                    ; /* 0xd578 */
    volatile reg_vga_hspcfg15         vga_hspcfg15                    ; /* 0xd57c */
    volatile unsigned int           reserved_143[28]                ; /* 0xd580~0xd5ec 28 regs */
    volatile unsigned int           vga_intf_chksum_y               ; /* 0xd5f0 */
    volatile unsigned int           vga_intf_chksum_u               ; /* 0xd5f4 */
    volatile unsigned int           vga_intf_chksum_v               ; /* 0xd5f8 */
    volatile unsigned int           reserved_144                    ; /* 0xd5fc */
    volatile reg_intf_date_ctrl       intf_date_ctrl                  ; /* 0xd600 */
    volatile reg_intf_date_upd        intf_date_upd                   ; /* 0xd604 */
    volatile reg_intf_date_sync_inv   intf_date_sync_inv              ; /* 0xd608 */
    volatile unsigned int           reserved_145                    ; /* 0xd60c */
    volatile reg_date_clip0_l         date_clip0_l                    ; /* 0xd610 */
    volatile reg_date_clip0_h         date_clip0_h                    ; /* 0xd614 */
    volatile unsigned int           reserved_146[58]                ; /* 0xd618~0xd6fc 58 regs */
    volatile reg_intf0_dither_ctrl    intf0_dither_ctrl               ; /* 0xd700 */
    volatile reg_intf0_dither_sed_y0   intf0_dither_sed_y0             ; /* 0xd704 */
    volatile reg_intf0_dither_sed_u0   intf0_dither_sed_u0             ; /* 0xd708 */
    volatile reg_intf0_dither_sed_v0   intf0_dither_sed_v0             ; /* 0xd70c */
    volatile reg_intf0_dither_sed_w0   intf0_dither_sed_w0             ; /* 0xd710 */
    volatile reg_intf0_dither_sed_y1   intf0_dither_sed_y1             ; /* 0xd714 */
    volatile reg_intf0_dither_sed_u1   intf0_dither_sed_u1             ; /* 0xd718 */
    volatile reg_intf0_dither_sed_v1   intf0_dither_sed_v1             ; /* 0xd71c */
    volatile reg_intf0_dither_sed_w1   intf0_dither_sed_w1             ; /* 0xd720 */
    volatile reg_intf0_dither_sed_y2   intf0_dither_sed_y2             ; /* 0xd724 */
    volatile reg_intf0_dither_sed_u2   intf0_dither_sed_u2             ; /* 0xd728 */
    volatile reg_intf0_dither_sed_v2   intf0_dither_sed_v2             ; /* 0xd72c */
    volatile reg_intf0_dither_sed_w2   intf0_dither_sed_w2             ; /* 0xd730 */
    volatile reg_intf0_dither_sed_y3   intf0_dither_sed_y3             ; /* 0xd734 */
    volatile reg_intf0_dither_sed_u3   intf0_dither_sed_u3             ; /* 0xd738 */
    volatile reg_intf0_dither_sed_v3   intf0_dither_sed_v3             ; /* 0xd73c */
    volatile reg_intf0_dither_sed_w3   intf0_dither_sed_w3             ; /* 0xd740 */
    volatile reg_intf0_dither_thr     intf0_dither_thr                ; /* 0xd744 */
    volatile unsigned int           reserved_147[558]               ; /* 0xd748~0xdffc 558 regs */
    volatile reg_dhd1_ctrl dhd1_ctrl; /* 0xe000 */
    volatile reg_dhd1_vsync1 dhd1_vsync1; /* 0xe004 */
    volatile reg_dhd1_vsync2 dhd1_vsync2; /* 0xe008 */
    volatile reg_dhd1_hsync1 dhd1_hsync1; /* 0xe00c */
    volatile reg_dhd1_hsync2 dhd1_hsync2; /* 0xe010 */
    volatile reg_dhd1_vplus1 dhd1_vplus1; /* 0xe014 */
    volatile reg_dhd1_vplus2 dhd1_vplus2; /* 0xe018 */
    volatile reg_dhd1_pwr dhd1_pwr; /* 0xe01c */
    volatile reg_dhd1_vtthd3 dhd1_vtthd3; /* 0xe020 */
    volatile reg_dhd1_vtthd dhd1_vtthd; /* 0xe024 */
    volatile reg_dhd1_parathd dhd1_parathd; /* 0xe028 */
    volatile reg_dhd1_precharge_thd dhd1_precharge_thd; /* 0xe02c */
    volatile reg_dhd1_start_pos dhd1_start_pos; /* 0xe030 */
    volatile reg_dhd1_start_pos1 dhd1_start_pos1; /* 0xe034 */
    volatile reg_dhd1_paraup dhd1_paraup; /* 0xe038 */
    volatile reg_dhd1_sync_inv dhd1_sync_inv; /* 0xe03c */
    volatile reg_dhd1_clk_dv_ctrl dhd1_clk_dv_ctrl; /* 0xe040 */
    volatile reg_dhd1_rgb_fix_ctrl dhd1_rgb_fix_ctrl; /* 0xe044 */
    volatile reg_dhd1_lockcfg dhd1_lockcfg; /* 0xe048 */
    volatile unsigned int dhd1_cap_frm_cnt; /* 0xe04c */
    volatile unsigned int dhd1_vdp_frm_cnt; /* 0xe050 */
    volatile unsigned int dhd1_vsync_cap_vdp_cnt; /* 0xe054 */
    volatile unsigned int dhd1_intf_chksum_y; /* 0xe058 */
    volatile unsigned int dhd1_intf_chksum_u; /* 0xe05c */
    volatile unsigned int dhd1_intf_chksum_v; /* 0xe060 */
    volatile unsigned int dhd1_intf1_chksum_y; /* 0xe064 */
    volatile unsigned int dhd1_intf1_chksum_u; /* 0xe068 */
    volatile unsigned int dhd1_intf1_chksum_v; /* 0xe06c */
    volatile reg_dhd1_intf_chksum_high1 dhd1_intf_chksum_high1; /* 0xe070 */
    volatile reg_dhd1_intf_chksum_high2 dhd1_intf_chksum_high2; /* 0xe074 */
    volatile unsigned int reserved_148[3]; /* 0xe078~0xe080 3 regs */
    volatile unsigned int dhd1_afifo_pre_thd; /* 0xe084 */
    volatile reg_dhd1_state dhd1_state; /* 0xe088 */
    volatile reg_dhd1_uf_state dhd1_uf_state; /* 0xe08c */
    volatile unsigned int reserved_149[4]; /* 0xe090~0xe09c 4 regs */
    volatile reg_dhd1_vsync_te_state dhd1_vsync_te_state; /* 0xe0a0 */
    volatile reg_dhd1_vsync_te_state1 dhd1_vsync_te_state1; /* 0xe0a4 */
    volatile unsigned int           reserved_150[406]               ; /* 0xe0a8~0xe6fc 406 regs */
    volatile reg_intf1_dither_ctrl    intf1_dither_ctrl               ; /* 0xe700 */
    volatile reg_intf1_dither_sed_y0   intf1_dither_sed_y0             ; /* 0xe704 */
    volatile reg_intf1_dither_sed_u0   intf1_dither_sed_u0             ; /* 0xe708 */
    volatile reg_intf1_dither_sed_v0   intf1_dither_sed_v0             ; /* 0xe70c */
    volatile reg_intf1_dither_sed_w0   intf1_dither_sed_w0             ; /* 0xe710 */
    volatile reg_intf1_dither_sed_y1   intf1_dither_sed_y1             ; /* 0xe714 */
    volatile reg_intf1_dither_sed_u1   intf1_dither_sed_u1             ; /* 0xe718 */
    volatile reg_intf1_dither_sed_v1   intf1_dither_sed_v1             ; /* 0xe71c */
    volatile reg_intf1_dither_sed_w1   intf1_dither_sed_w1             ; /* 0xe720 */
    volatile reg_intf1_dither_sed_y2   intf1_dither_sed_y2             ; /* 0xe724 */
    volatile reg_intf1_dither_sed_u2   intf1_dither_sed_u2             ; /* 0xe728 */
    volatile reg_intf1_dither_sed_v2   intf1_dither_sed_v2             ; /* 0xe72c */
    volatile reg_intf1_dither_sed_w2   intf1_dither_sed_w2             ; /* 0xe730 */
    volatile reg_intf1_dither_sed_y3   intf1_dither_sed_y3             ; /* 0xe734 */
    volatile reg_intf1_dither_sed_u3   intf1_dither_sed_u3             ; /* 0xe738 */
    volatile reg_intf1_dither_sed_v3   intf1_dither_sed_v3             ; /* 0xe73c */
    volatile reg_intf1_dither_sed_w3   intf1_dither_sed_w3             ; /* 0xe740 */
    volatile reg_intf1_dither_thr     intf1_dither_thr                ; /* 0xe744 */
    volatile unsigned int           reserved_151[558]               ; /* 0xe748~0xeffc 558 regs */
    volatile reg_dhd2_ctrl            dhd2_ctrl                       ; /* 0xf000 */
    volatile reg_dhd2_vsync1          dhd2_vsync1                     ; /* 0xf004 */
    volatile reg_dhd2_vsync2          dhd2_vsync2                     ; /* 0xf008 */
    volatile reg_dhd2_hsync1          dhd2_hsync1                     ; /* 0xf00c */
    volatile reg_dhd2_hsync2          dhd2_hsync2                     ; /* 0xf010 */
    volatile reg_dhd2_vplus1          dhd2_vplus1                     ; /* 0xf014 */
    volatile reg_dhd2_vplus2          dhd2_vplus2                     ; /* 0xf018 */
    volatile reg_dhd2_pwr             dhd2_pwr                        ; /* 0xf01c */
    volatile reg_dhd2_vtthd3          dhd2_vtthd3                     ; /* 0xf020 */
    volatile reg_dhd2_vtthd           dhd2_vtthd                      ; /* 0xf024 */
    volatile reg_dhd2_parathd         dhd2_parathd                    ; /* 0xf028 */
    volatile reg_dhd2_precharge_thd   dhd2_precharge_thd              ; /* 0xf02c */
    volatile reg_dhd2_start_pos       dhd2_start_pos                  ; /* 0xf030 */
    volatile reg_dhd2_start_pos1      dhd2_start_pos1                 ; /* 0xf034 */
    volatile reg_dhd2_paraup          dhd2_paraup                     ; /* 0xf038 */
    volatile reg_dhd2_sync_inv        dhd2_sync_inv                   ; /* 0xf03c */
    volatile reg_dhd2_clk_dv_ctrl     dhd2_clk_dv_ctrl                ; /* 0xf040 */
    volatile reg_dhd2_rgb_fix_ctrl    dhd2_rgb_fix_ctrl               ; /* 0xf044 */
    volatile reg_dhd2_lockcfg         dhd2_lockcfg                    ; /* 0xf048 */
    volatile unsigned int           dhd2_cap_frm_cnt                ; /* 0xf04c */
    volatile unsigned int           dhd2_vdp_frm_cnt                ; /* 0xf050 */
    volatile unsigned int           dhd2_vsync_cap_vdp_cnt          ; /* 0xf054 */
    volatile unsigned int           dhd2_intf_chksum_y              ; /* 0xf058 */
    volatile unsigned int           dhd2_intf_chksum_u              ; /* 0xf05c */
    volatile unsigned int           dhd2_intf_chksum_v              ; /* 0xf060 */
    volatile unsigned int           dhd2_intf1_chksum_y             ; /* 0xf064 */
    volatile unsigned int           dhd2_intf1_chksum_u             ; /* 0xf068 */
    volatile unsigned int           dhd2_intf1_chksum_v             ; /* 0xf06c */
    volatile reg_dhd2_intf_chksum_high1   dhd2_intf_chksum_high1          ; /* 0xf070 */
    volatile reg_dhd2_intf_chksum_high2   dhd2_intf_chksum_high2          ; /* 0xf074 */
    volatile unsigned int           reserved_152[3]                 ; /* 0xf078~0xf080 3 regs */
    volatile unsigned int           dhd2_afifo_pre_thd              ; /* 0xf084 */
    volatile reg_dhd2_state           dhd2_state                      ; /* 0xf088 */
    volatile reg_dhd2_uf_state        dhd2_uf_state                   ; /* 0xf08c */
    volatile unsigned int           reserved_153[4]                 ; /* 0xf090~0xf09c 4 regs */
    volatile reg_dhd2_vsync_te_state   dhd2_vsync_te_state             ; /* 0xf0a0 */
    volatile reg_dhd2_vsync_te_state1   dhd2_vsync_te_state1            ; /* 0xf0a4 */
    volatile unsigned int           reserved_154[406]               ; /* 0xf0a8~0xf6fc 406 regs */
    volatile reg_intf2_dither_ctrl    intf2_dither_ctrl               ; /* 0xf700 */
    volatile reg_intf2_dither_sed_y0   intf2_dither_sed_y0             ; /* 0xf704 */
    volatile reg_intf2_dither_sed_u0   intf2_dither_sed_u0             ; /* 0xf708 */
    volatile reg_intf2_dither_sed_v0   intf2_dither_sed_v0             ; /* 0xf70c */
    volatile reg_intf2_dither_sed_w0   intf2_dither_sed_w0             ; /* 0xf710 */
    volatile reg_intf2_dither_sed_y1   intf2_dither_sed_y1             ; /* 0xf714 */
    volatile reg_intf2_dither_sed_u1   intf2_dither_sed_u1             ; /* 0xf718 */
    volatile reg_intf2_dither_sed_v1   intf2_dither_sed_v1             ; /* 0xf71c */
    volatile reg_intf2_dither_sed_w1   intf2_dither_sed_w1             ; /* 0xf720 */
    volatile reg_intf2_dither_sed_y2   intf2_dither_sed_y2             ; /* 0xf724 */
    volatile reg_intf2_dither_sed_u2   intf2_dither_sed_u2             ; /* 0xf728 */
    volatile reg_intf2_dither_sed_v2   intf2_dither_sed_v2             ; /* 0xf72c */
    volatile reg_intf2_dither_sed_w2   intf2_dither_sed_w2             ; /* 0xf730 */
    volatile reg_intf2_dither_sed_y3   intf2_dither_sed_y3             ; /* 0xf734 */
    volatile reg_intf2_dither_sed_u3   intf2_dither_sed_u3             ; /* 0xf738 */
    volatile reg_intf2_dither_sed_v3   intf2_dither_sed_v3             ; /* 0xf73c */
    volatile reg_intf2_dither_sed_w3   intf2_dither_sed_w3             ; /* 0xf740 */
    volatile reg_intf2_dither_thr     intf2_dither_thr                ; /* 0xf744 */
    volatile unsigned int           reserved_155[46]                ; /* 0xf748~0xf7fc 46 regs */
    volatile reg_date_coeff0          date_coeff0                     ; /* 0xf800 */
    volatile reg_date_coeff1          date_coeff1                     ; /* 0xf804 */
    volatile unsigned int           date_coeff2                     ; /* 0xf808 */
    volatile reg_date_coeff3          date_coeff3                     ; /* 0xf80c */
    volatile reg_date_coeff4          date_coeff4                     ; /* 0xf810 */
    volatile reg_date_coeff5          date_coeff5                     ; /* 0xf814 */
    volatile reg_date_coeff6          date_coeff6                     ; /* 0xf818 */
    volatile reg_date_coeff7          date_coeff7                     ; /* 0xf81c */
    volatile unsigned int           date_coeff8                     ; /* 0xf820 */
    volatile unsigned int           date_coeff9                     ; /* 0xf824 */
    volatile reg_date_coeff10         date_coeff10                    ; /* 0xf828 */
    volatile reg_date_coeff11         date_coeff11                    ; /* 0xf82c */
    volatile reg_date_coeff12         date_coeff12                    ; /* 0xf830 */
    volatile reg_date_coeff13         date_coeff13                    ; /* 0xf834 */
    volatile reg_date_coeff14         date_coeff14                    ; /* 0xf838 */
    volatile reg_date_coeff15         date_coeff15                    ; /* 0xf83c */
    volatile reg_date_coeff16         date_coeff16                    ; /* 0xf840 */
    volatile unsigned int           date_coeff17                    ; /* 0xf844 */
    volatile unsigned int           date_coeff18                    ; /* 0xf848 */
    volatile reg_date_coeff19         date_coeff19                    ; /* 0xf84c */
    volatile reg_date_coeff20         date_coeff20                    ; /* 0xf850 */
    volatile reg_date_coeff21         date_coeff21                    ; /* 0xf854 */
    volatile reg_date_coeff22         date_coeff22                    ; /* 0xf858 */
    volatile reg_date_coeff23         date_coeff23                    ; /* 0xf85c */
    volatile unsigned int           date_coeff24                    ; /* 0xf860 */
    volatile reg_date_coeff25         date_coeff25                    ; /* 0xf864 */
    volatile reg_date_coeff26         date_coeff26                    ; /* 0xf868 */
    volatile reg_date_coeff27         date_coeff27                    ; /* 0xf86c */
    volatile reg_date_coeff28         date_coeff28                    ; /* 0xf870 */
    volatile reg_date_coeff29         date_coeff29                    ; /* 0xf874 */
    volatile reg_date_coeff30         date_coeff30                    ; /* 0xf878 */
    volatile unsigned int           reserved_156                    ; /* 0xf87c */
    volatile reg_date_isrmask         date_isrmask                    ; /* 0xf880 */
    volatile reg_date_isrstate        date_isrstate                   ; /* 0xf884 */
    volatile reg_date_isr             date_isr                        ; /* 0xf888 */
    volatile unsigned int           reserved_157                    ; /* 0xf88c */
    volatile unsigned int           date_version                    ; /* 0xf890 */
    volatile reg_date_coeff37         date_coeff37                    ; /* 0xf894 */
    volatile reg_date_coeff38         date_coeff38                    ; /* 0xf898 */
    volatile reg_date_coeff39         date_coeff39                    ; /* 0xf89c */
    volatile reg_date_coeff40         date_coeff40                    ; /* 0xf8a0 */
    volatile reg_date_coeff41         date_coeff41                    ; /* 0xf8a4 */
    volatile reg_date_coeff42         date_coeff42                    ; /* 0xf8a8 */
    volatile unsigned int           reserved_158[5]                 ; /* 0xf8ac~0xf8bc 5 regs */
    volatile reg_date_dacdet1         date_dacdet1                    ; /* 0xf8c0 */
    volatile reg_date_dacdet2         date_dacdet2                    ; /* 0xf8c4 */
    volatile reg_date_coeff50         date_coeff50                    ; /* 0xf8c8 */
    volatile reg_date_coeff51         date_coeff51                    ; /* 0xf8cc */
    volatile reg_date_coeff52         date_coeff52                    ; /* 0xf8d0 */
    volatile reg_date_coeff53         date_coeff53                    ; /* 0xf8d4 */
    volatile reg_date_coeff54         date_coeff54                    ; /* 0xf8d8 */
    volatile reg_date_coeff55         date_coeff55                    ; /* 0xf8dc */
    volatile reg_date_coeff56         date_coeff56                   ; /* 0xf8e0 */
    volatile reg_date_coeff57         date_coeff57                   ; /* 0xf8e4 */
    volatile reg_date_coeff58         date_coeff58                   ; /* 0xf8e8 */
    volatile reg_date_coeff59         date_coeff59                   ; /* 0xf8ec */
    volatile reg_date_coeff60         date_coeff60                   ; /* 0xf8f0 */
    volatile reg_date_coeff61         date_coeff61                   ; /* 0xf8f4 */
    volatile unsigned int           date_coeff62                   ; /* 0xf8f8 */
    volatile unsigned int           date_coeff63                   ; /* 0xf8fc */
    volatile unsigned int           reserved_159[448]              ; /* 0xf900~0xfffc  448 regs */
    volatile reg_mac_outstanding mac_outstanding; /* 0x10000 */
    volatile reg_mac_ctrl mac_ctrl; /* 0x10004 */
    volatile unsigned int reserved_160[2]; /* 0x10008~0x1000c 2 regs */
    volatile reg_mac_rchn_prio mac_rchn_prio; /* 0x10010 */
    volatile unsigned int reserved_161; /* 0x10014 */
    volatile reg_mac_wchn_prio mac_wchn_prio; /* 0x10018 */
    volatile unsigned int reserved_162; /* 0x1001c */
    volatile reg_mac_rchn_sel0 mac_rchn_sel0; /* 0x10020 */
    volatile unsigned int mac_rchn_sel1; /* 0x10024 */
    volatile unsigned int reserved_163[2]; /* 0x10028~0x1002c 2 regs */
    volatile reg_mac_wchn_sel0 mac_wchn_sel0; /* 0x10030 */
    volatile unsigned int reserved_164[3]; /* 0x10034~0x1003c 3 regs */
    volatile reg_mac_bus_err_clr mac_bus_err_clr; /* 0x10040 */
    volatile reg_mac_bus_err mac_bus_err; /* 0x10044 */
    volatile unsigned int reserved_165[2]; /* 0x10048~0x1004c 2 regs */
    volatile unsigned int mac_src0_status0; /* 0x10050 */
    volatile unsigned int mac_src0_status1; /* 0x10054 */
    volatile unsigned int mac_src1_status0; /* 0x10058 */
    volatile unsigned int mac_src1_status1; /* 0x1005c */
    volatile unsigned int mac_src2_status0; /* 0x10060 */
    volatile unsigned int mac_src2_status1; /* 0x10064 */
    volatile unsigned int reserved_166[2]; /* 0x10068~0x1006c 2 regs */
    volatile reg_mac_debug_ctrl mac_debug_ctrl; /* 0x10070 */
    volatile reg_mac_debug_clr mac_debug_clr; /* 0x10074 */
    volatile unsigned int reserved_167[2]; /* 0x10078~0x1007c 2 regs */
    volatile unsigned int mac0_debug_info; /* 0x10080 */
    volatile unsigned int reserved_168[3]; /* 0x10084~0x1008c 3 regs */
    volatile unsigned int mac0_rd_info; /* 0x10090 */
    volatile unsigned int mac0_wr_info; /* 0x10094 */
    volatile unsigned int mac1_rd_info; /* 0x10098 */
    volatile unsigned int mac1_wr_info; /* 0x1009c */
    volatile unsigned int mac2_rd_info; /* 0x100a0 */
    volatile unsigned int mac2_wr_info; /* 0x100a4 */
    volatile unsigned int reserved_169[2]; /* 0x100a8~0x100ac 2 regs */
    volatile unsigned int mac0_det_latency0; /* 0x100b0 */
    volatile unsigned int mac0_det_latency1; /* 0x100b4 */
    volatile unsigned int mac0_det_latency2; /* 0x100b8 */
    volatile unsigned int mac0_det_latency3; /* 0x100bc */
    volatile unsigned int mac0_det_latency4; /* 0x100c0 */
    volatile unsigned int mac0_det_latency5; /* 0x100c4 */
    volatile unsigned int mac1_det_latency0; /* 0x100c8 */
    volatile unsigned int mac1_det_latency1; /* 0x100cc */
    volatile unsigned int mac1_det_latency2; /* 0x100d0 */
    volatile unsigned int mac1_det_latency3; /* 0x100d4 */
    volatile unsigned int mac1_det_latency4; /* 0x100d8 */
    volatile unsigned int mac1_det_latency5; /* 0x100dc */
    volatile unsigned int reserved_170[72]; /* 0x100e0~0x101fc 72 regs */
    volatile reg_vid_read_ctrl vid_read_ctrl; /* 0x10200 */
    volatile reg_vid_mac_ctrl vid_mac_ctrl; /* 0x10204 */
    volatile unsigned int reserved_171[2]; /* 0x10208~0x1020c 2 regs */
    volatile reg_vid_out_ctrl vid_out_ctrl; /* 0x10210 */
    volatile reg_vid_mute_alpha vid_mute_alpha; /* 0x10214 */
    volatile unsigned int reserved_172; /* 0x10218 */
    volatile reg_vid_mute_bk vid_mute_bk; /* 0x1021c */
    volatile unsigned int reserved_173[8]; /* 0x10220~0x1023c 8 regs */
    volatile reg_vid_src_info vid_src_info; /* 0x10240 */
    volatile reg_vid_src_reso vid_src_reso; /* 0x10244 */
    volatile reg_vid_src_crop vid_src_crop; /* 0x10248 */
    volatile reg_vid_in_reso vid_in_reso; /* 0x1024c */
    volatile unsigned int vid_addr_h; /* 0x10250 */
    volatile unsigned int vid_addr_l; /* 0x10254 */
    volatile unsigned int vid_caddr_h; /* 0x10258 */
    volatile unsigned int vid_caddr_l; /* 0x1025c */
    volatile unsigned int vid_naddr_h; /* 0x10260 */
    volatile unsigned int vid_naddr_l; /* 0x10264 */
    volatile unsigned int vid_ncaddr_h; /* 0x10268 */
    volatile unsigned int vid_ncaddr_l; /* 0x1026c */
    volatile reg_vid_stride vid_stride; /* 0x10270 */
    volatile reg_vid_2bit_stride vid_2bit_stride; /* 0x10274 */
    volatile reg_vid_head_stride vid_head_stride; /* 0x10278 */
    volatile unsigned int reserved_174; /* 0x1027c */
    volatile reg_vid_smmu_bypass vid_smmu_bypass; /* 0x10280 */
    volatile unsigned int reserved_175[3]; /* 0x10284~0x1028c 3 regs */
    volatile unsigned int vid_head_addr_h; /* 0x10290 */
    volatile unsigned int vid_head_addr_l; /* 0x10294 */
    volatile unsigned int vid_head_caddr_h; /* 0x10298 */
    volatile unsigned int vid_head_caddr_l; /* 0x1029c */
    volatile reg_vid_testpat_cfg vid_testpat_cfg; /* 0x102a0 */
    volatile reg_vid_testpat_seed vid_testpat_seed; /* 0x102a4 */
    volatile unsigned int vid_testpat_chksum_y; /* 0x102a8 */
    volatile unsigned int vid_testpat_chksum_c; /* 0x102ac */
    volatile unsigned int reserved_176[20]; /* 0x102b0~0x102fc 20 regs */
    volatile unsigned int vid_l_cur_flow; /* 0x10300 */
    volatile unsigned int vid_l_cur_sreq_time; /* 0x10304 */
    volatile unsigned int vid_c_cur_flow; /* 0x10308 */
    volatile unsigned int vid_c_cur_sreq_time; /* 0x1030c */
    volatile unsigned int vid_l_last_flow; /* 0x10310 */
    volatile unsigned int vid_l_last_sreq_time; /* 0x10314 */
    volatile unsigned int vid_c_last_flow; /* 0x10318 */
    volatile unsigned int vid_c_last_sreq_time; /* 0x1031c */
    volatile unsigned int vid_l_busy_time; /* 0x10320 */
    volatile unsigned int vid_l_neednordy_time; /* 0x10324 */
    volatile unsigned int vid_l2_neednordy_time; /* 0x10328 */
    volatile unsigned int vid_c_busy_time; /* 0x1032c */
    volatile unsigned int vid_c_neednordy_time; /* 0x10330 */
    volatile unsigned int vid_c2_neednordy_time; /* 0x10334 ---- */
    volatile unsigned int reserved_177[2]; /* 0x10338~0x1033c 2 regs */
    volatile reg_vid_dcmp_ctrl vid_dcmp_ctrl; /* 0x10340 */
    volatile unsigned int vid_dcmp_l_fsize; /* 0x10344 */
    volatile unsigned int reserved_178[14]; /* 0x10348~0x1037c 14 regs */
    volatile reg_vdp_v3r2_lineseg_dcmp_glb_info   vdp_v3r2_lineseg_dcmp_glb_info  ; /* 0x10380 */
    volatile reg_vdp_v3r2_lineseg_dcmp_frame_size   vdp_v3r2_lineseg_dcmp_frame_size; /* 0x10384 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_adpqp_thr0; /* 0x10388 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_adpqp_thr1; /* 0x1038c */
    volatile reg_vdp_v3r2_lineseg_dcmp_smth_deltabits_thr   vdp_v3r2_lineseg_dcmp_smth_deltabits_thr; /* 0x10390 */
    volatile reg_vdp_v3r2_lineseg_dcmp_error_sta   vdp_v3r2_lineseg_dcmp_error_sta ; /* 0x10394 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_extra     ; /* 0x10398 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_dbg_reg   ; /* 0x1039c */
    volatile unsigned int           reserved_179[8]                 ; /* 0x103a0~0x103bc 8 regs */
    volatile reg_vdp_v3r2_lineseg_dcmp_glb_info_c   vdp_v3r2_lineseg_dcmp_glb_info_c; /* 0x103c0 */
    volatile reg_vdp_v3r2_lineseg_dcmp_frame_size_c   vdp_v3r2_lineseg_dcmp_frame_size_c; /* 0x103c4 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_adpqp_thr0_c; /* 0x103c8 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_adpqp_thr1_c; /* 0x103cc */
    volatile reg_vdp_v3r2_lineseg_dcmp_smth_deltabits_thr_c   vdp_v3r2_lineseg_dcmp_smth_deltabits_thr_c; /* 0x103d0 */
    volatile reg_vdp_v3r2_lineseg_dcmp_error_sta_c   vdp_v3r2_lineseg_dcmp_error_sta_c; /* 0x103d4 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_extra_c   ; /* 0x103d8 */
    volatile unsigned int           vdp_v3r2_lineseg_dcmp_dbg_reg_c ; /* 0x103dc */
    volatile unsigned int           reserved_180[648]               ; /* 0x103e0~0x10dfc 648 regs */
    volatile reg_gfx_read_ctrl gfx_read_ctrl; /* 0x10e00 */
    volatile reg_gfx_mac_ctrl gfx_mac_ctrl; /* 0x10e04 */
    volatile reg_gfx_out_ctrl gfx_out_ctrl; /* 0x10e08 */
    volatile unsigned int reserved_181; /* 0x10e0c */
    volatile reg_gfx_mute_alpha gfx_mute_alpha; /* 0x10e10 */
    volatile reg_gfx_mute_bk gfx_mute_bk; /* 0x10e14 */
    volatile unsigned int reserved_182[2]; /* 0x10e18~0x10e1c 2 regs */
    volatile reg_gfx_smmu_bypass gfx_smmu_bypass; /* 0x10e20 */
    volatile unsigned int reserved_183; /* 0x10e24 */
    volatile reg_gfx_1555_alpha gfx_1555_alpha; /* 0x10e28 */
    volatile unsigned int reserved_184[5]; /* 0x10e2c~0x10e3c 5 regs */
    volatile reg_gfx_src_info gfx_src_info; /* 0x10e40 */
    volatile reg_gfx_src_reso gfx_src_reso; /* 0x10e44 */
    volatile reg_gfx_src_crop gfx_src_crop; /* 0x10e48 */
    volatile reg_gfx_ireso gfx_ireso; /* 0x10e4c */
    volatile unsigned int gfx_addr_h; /* 0x10e50 */
    volatile unsigned int gfx_addr_l; /* 0x10e54 */
    volatile unsigned int gfx_naddr_h; /* 0x10e58 */
    volatile unsigned int gfx_naddr_l; /* 0x10e5c */
    volatile reg_gfx_stride gfx_stride; /* 0x10e60 */
    volatile unsigned int reserved_185[3]; /* 0x10e64~0x10e6c 3 regs */
    volatile unsigned int gfx_dcmp_addr_h; /* 0x10e70 */
    volatile unsigned int gfx_dcmp_addr_l; /* 0x10e74 */
    volatile unsigned int gfx_dcmp_naddr_h; /* 0x10e78 */
    volatile unsigned int gfx_dcmp_naddr_l; /* 0x10e7c */
    volatile unsigned int reserved_186[32]; /* 0x10e80~0x10efc 32 regs */
    volatile reg_gfx_ckey_max gfx_ckey_max; /* 0x10f00 */
    volatile reg_gfx_ckey_min gfx_ckey_min; /* 0x10f04 */
    volatile reg_gfx_ckey_mask gfx_ckey_mask; /* 0x10f08 */
    volatile unsigned int reserved_187; /* 0x10f0c */
    volatile reg_gfx_testpat_cfg gfx_testpat_cfg; /* 0x10f10 */
    volatile reg_gfx_testpat_seed gfx_testpat_seed; /* 0x10f14 */
    volatile unsigned int reserved_188[2]; /* 0x10f18~0x10f1c 2 regs */
    volatile unsigned int gfx_dcmp_framesize0; /* 0x10f20 */
    volatile unsigned int gfx_dcmp_framesize1; /* 0x10f24 */
    volatile unsigned int reserved_189[2]; /* 0x10f28~0x10f2c 2 regs */
    volatile unsigned int gfx_cur_flow; /* 0x10f30 */
    volatile unsigned int gfx_cur_sreq_time; /* 0x10f34 */
    volatile unsigned int gfx_last_flow; /* 0x10f38 */
    volatile unsigned int gfx_last_sreq_time; /* 0x10f3c */
    volatile unsigned int gfx_busy_time; /* 0x10f40 */
    volatile unsigned int gfx_ar_neednordy_time; /* 0x10f44 */
    volatile unsigned int gfx_gb_neednordy_time; /* 0x10f48 */
    volatile unsigned int reserved_190[13]; /* 0x10f4c~0x10f7c 13 regs */
    volatile reg_gfx_dcmp_ctrl gfx_dcmp_ctrl; /* 0x10f80 */
    volatile unsigned int reserved_191[3]; /* 0x10f84~0x10f8c 3 regs */
    volatile reg_gfx_dcmp_wrong_sta gfx_dcmp_wrong_sta; /* 0x10f90 */
    volatile unsigned int gfx_dcmp_debug_sta0; /* 0x10f94 */
    volatile unsigned int reserved_192[538]; /* 0x10f98~0x117fc 538 regs */
    volatile reg_wbc_ctrl wbc_ctrl; /* 0x11800 */
    volatile reg_wbc_mac_ctrl wbc_mac_ctrl; /* 0x11804 */
    volatile unsigned int reserved_193[3]; /* 0x11808~0x11810 3 regs */
    volatile reg_wbc_smmu_bypass wbc_smmu_bypass; /* 0x11814 */
    volatile unsigned int reserved_194[2]; /* 0x11818~0x1181c 2 regs */
    volatile reg_wbc_lowdlyctrl wbc_lowdlyctrl; /* 0x11820 */
    volatile unsigned int wbc_tunladdr_h; /* 0x11824 */
    volatile unsigned int wbc_tunladdr_l; /* 0x11828 */
    volatile reg_wbc_lowdlysta wbc_lowdlysta; /* 0x1182c */
    volatile unsigned int reserved_195[8]; /* 0x11830~0x1184c 8 regs */
    volatile unsigned int wbc_yaddr_h; /* 0x11850 */
    volatile unsigned int wbc_yaddr_l; /* 0x11854 */
    volatile unsigned int wbc_caddr_h; /* 0x11858 */
    volatile unsigned int wbc_caddr_l; /* 0x1185c */
    volatile reg_wbc_ystride wbc_ystride; /* 0x11860 */
    volatile reg_wbc_cstride wbc_cstride; /* 0x11864 */
    volatile unsigned int reserved_196[2]; /* 0x11868~0x1186c 2 regs */
    volatile unsigned int wbc_ynaddr_h; /* 0x11870 */
    volatile unsigned int wbc_ynaddr_l; /* 0x11874 */
    volatile unsigned int wbc_cnaddr_h; /* 0x11878 */
    volatile unsigned int wbc_cnaddr_l; /* 0x1187c */
    volatile reg_wbc_ynstride wbc_ynstride; /* 0x11880 */
    volatile reg_wbc_cnstride wbc_cnstride; /* 0x11884 */
    volatile unsigned int reserved_197[10]; /* 0x11888~0x118ac 10 regs */
    volatile reg_wbc_sta wbc_sta; /* 0x118b0 */
    volatile reg_wbc_line_num wbc_line_num; /* 0x118b4 */
    volatile reg_wbc_cap_reso wbc_cap_reso; /* 0x118b8 */
    volatile unsigned int wbc_cap_info; /* 0x118bc */
    volatile unsigned int reserved_198[16]; /* 0x118c0~0x118fc 16 regs */
    volatile reg_vdp_v3r2_lineseg_cmp_glb_info   vdp_v3r2_lineseg_cmp_glb_info   ; /* 0x11900 */
    volatile reg_vdp_v3r2_lineseg_cmp_frame_size   vdp_v3r2_lineseg_cmp_frame_size ; /* 0x11904 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg0   vdp_v3r2_lineseg_cmp_rc_cfg0    ; /* 0x11908 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg1   vdp_v3r2_lineseg_cmp_rc_cfg1    ; /* 0x1190c */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg2    ; /* 0x11910 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg3    ; /* 0x11914 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg4    ; /* 0x11918 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg5    ; /* 0x1191c */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg6    ; /* 0x11920 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg7    ; /* 0x11924 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg8    ; /* 0x11928 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg9    ; /* 0x1192c */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg10   ; /* 0x11930 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg11   ; /* 0x11934 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg12   vdp_v3r2_lineseg_cmp_rc_cfg12   ; /* 0x11938 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg13   vdp_v3r2_lineseg_cmp_rc_cfg13   ; /* 0x1193c */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg14   ; /* 0x11940 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg15   ; /* 0x11944 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_adpqp_thr0 ; /* 0x11948 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_adpqp_thr1 ; /* 0x1194c */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg16   vdp_v3r2_lineseg_cmp_rc_cfg16   ; /* 0x11950 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_glb_cfg    ; /* 0x11954 */
    volatile reg_vdp_v3r2_lineseg_cmp_glb_st   vdp_v3r2_lineseg_cmp_glb_st     ; /* 0x11958 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_dbg_reg    ; /* 0x1195c */
    volatile unsigned int           reserved_199[8]                 ; /* 0x11960~0x1197c 8 regs */
    volatile reg_vdp_v3r2_lineseg_cmp_glb_info_c   vdp_v3r2_lineseg_cmp_glb_info_c ; /* 0x11980 */
    volatile reg_vdp_v3r2_lineseg_cmp_frame_size_c   vdp_v3r2_lineseg_cmp_frame_size_c; /* 0x11984 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg0_c   vdp_v3r2_lineseg_cmp_rc_cfg0_c  ; /* 0x11988 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg1_c   vdp_v3r2_lineseg_cmp_rc_cfg1_c  ; /* 0x1198c */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg2_c  ; /* 0x11990 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg3_c  ; /* 0x11994 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg4_c  ; /* 0x11998 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg5_c  ; /* 0x1199c */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg6_c  ; /* 0x119a0 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg7_c  ; /* 0x119a4 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg8_c  ; /* 0x119a8 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg9_c  ; /* 0x119ac */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg10_c ; /* 0x119b0 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg11_c ; /* 0x119b4 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg12_c   vdp_v3r2_lineseg_cmp_rc_cfg12_c ; /* 0x119b8 */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg13_c   vdp_v3r2_lineseg_cmp_rc_cfg13_c ; /* 0x119bc */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg14_c ; /* 0x119c0 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_rc_cfg15_c ; /* 0x119c4 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_adpqp_thr0_c; /* 0x119c8 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_adpqp_thr1_c; /* 0x119cc */
    volatile reg_vdp_v3r2_lineseg_cmp_rc_cfg16_c   vdp_v3r2_lineseg_cmp_rc_cfg16_c ; /* 0x119d0 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_glb_cfg_c  ; /* 0x119d4 */
    volatile reg_vdp_v3r2_lineseg_cmp_glb_st_c   vdp_v3r2_lineseg_cmp_glb_st_c   ; /* 0x119d8 */
    volatile unsigned int           vdp_v3r2_lineseg_cmp_dbg_reg_c  ; /* 0x119dc */
    volatile unsigned int           reserved_200[264]               ; /* 0x119e0~0x11dfc 264 regs */
    volatile reg_wbc_cmp_ctrl         wbc_cmp_ctrl                    ; /* 0x11e00 */
    volatile reg_wbc_cmp_upd wbc_cmp_upd; /* 0x11e04 */
    volatile reg_wbc_cmp_height wbc_cmp_height; /* 0x11e08 */
    volatile reg_wbc_cmp_oreso wbc_cmp_oreso; /* 0x11e0c */
    volatile unsigned int wbc_cmp_yaddr; /* 0x11e10 */
    volatile unsigned int wbc_cmp_yaddr1; /* 0x11e14 */
    volatile unsigned int wbc_cmp_caddr; /* 0x11e18 */
    volatile unsigned int wbc_cmp_caddr1; /* 0x11e1c */
    volatile unsigned int wbc_cmp_addr0_t0; /* 0x11e20 */
    volatile unsigned int wbc_cmp_addr1_t0; /* 0x11e24 */
    volatile unsigned int wbc_cmp_addr0_t1; /* 0x11e28 */
    volatile unsigned int wbc_cmp_addr1_t1; /* 0x11e2c */
    volatile unsigned int wbc_cmp_l_fsize; /* 0x11e30 */
    volatile unsigned int wbc_cmp_c_fsize; /* 0x11e34 */
    volatile unsigned int wbc_cmp_t0_fsize; /* 0x11e38 */
    volatile unsigned int wbc_cmp_t1_fsize; /* 0x11e3c */
    volatile unsigned int wbc_sety_fsize; /* 0x11e40 */
    volatile unsigned int wbc_setc_fsize; /* 0x11e44 */
    volatile unsigned int wbc_sett0_fsize; /* 0x11e48 */
    volatile unsigned int wbc_sett1_fsize; /* 0x11e4c */
    volatile reg_wbc_od_state wbc_od_state; /* 0x11e50 */
    volatile unsigned int reserved_201[43]; /* 0x11e54~0x11efc 43 regs */
    volatile reg_od_pic_osd_glb_info od_pic_osd_glb_info; /* 0x11f00 */
    volatile reg_od_pic_osd_frame_size od_pic_osd_frame_size; /* 0x11f04 */
    volatile reg_od_pic_osd_rc_cfg0 od_pic_osd_rc_cfg0; /* 0x11f08 */
    volatile reg_od_pic_osd_rc_cfg1 od_pic_osd_rc_cfg1; /* 0x11f0c */
    volatile reg_od_pic_osd_rc_cfg2 od_pic_osd_rc_cfg2; /* 0x11f10 */
    volatile reg_od_pic_osd_rc_cfg3 od_pic_osd_rc_cfg3; /* 0x11f14 */
    volatile reg_od_pic_osd_rc_cfg4 od_pic_osd_rc_cfg4; /* 0x11f18 */
    volatile reg_od_pic_osd_rc_cfg5 od_pic_osd_rc_cfg5; /* 0x11f1c */
    volatile reg_od_pic_osd_rc_cfg6 od_pic_osd_rc_cfg6; /* 0x11f20 */
    volatile reg_od_pic_osd_rc_cfg7 od_pic_osd_rc_cfg7; /* 0x11f24 */
    volatile reg_od_pic_osd_rc_cfg8 od_pic_osd_rc_cfg8; /* 0x11f28 */
    volatile reg_od_pic_osd_rc_cfg9 od_pic_osd_rc_cfg9; /* 0x11f2c */
    volatile reg_od_pic_osd_rc_cfg10 od_pic_osd_rc_cfg10; /* 0x11f30 */
    volatile reg_od_pic_osd_rc_cfg11 od_pic_osd_rc_cfg11; /* 0x11f34 */
    volatile reg_od_pic_osd_rc_cfg12 od_pic_osd_rc_cfg12; /* 0x11f38 */
    volatile reg_od_pic_osd_rc_cfg13 od_pic_osd_rc_cfg13; /* 0x11f3c */
    volatile reg_od_pic_osd_rc_cfg14 od_pic_osd_rc_cfg14; /* 0x11f40 */
    volatile reg_od_pic_osd_rc_cfg15 od_pic_osd_rc_cfg15; /* 0x11f44 */
    volatile reg_od_pic_osd_rc_cfg16 od_pic_osd_rc_cfg16; /* 0x11f48 */
    volatile reg_od_pic_osd_rc_cfg17 od_pic_osd_rc_cfg17; /* 0x11f4c */
    volatile reg_od_pic_osd_rc_cfg18 od_pic_osd_rc_cfg18; /* 0x11f50 */
    volatile reg_od_pic_osd_rc_cfg19 od_pic_osd_rc_cfg19; /* 0x11f54 */
    volatile unsigned int reserved_202[2]; /* 0x11f58~0x11f5c 2 regs */
    volatile reg_od_pic_osd_stat_thr od_pic_osd_stat_thr; /* 0x11f60 */
    volatile reg_od_pic_osd_pcmp od_pic_osd_pcmp; /* 0x11f64 */
    volatile unsigned int reserved_203[6]; /* 0x11f68~0x11f7c 6 regs */
    volatile reg_od_pic_osd_bs_size od_pic_osd_bs_size; /* 0x11f80 */
    volatile reg_od_pic_osd_worst_row od_pic_osd_worst_row; /* 0x11f84 */
    volatile reg_od_pic_osd_best_row od_pic_osd_best_row; /* 0x11f88 */
    volatile reg_od_pic_osd_stat_info od_pic_osd_stat_info; /* 0x11f8c */
    volatile unsigned int od_pic_osd_debug0; /* 0x11f90 */
    volatile unsigned int od_pic_osd_debug1; /* 0x11f94 */
    volatile unsigned int reserved_204[26]; /* 0x11f98~0x11ffc 26 regs */
    volatile reg_v0_mrg_ctrl v0_mrg_ctrl; /* 0x12000 */
    volatile reg_v0_mrg_disp_pos v0_mrg_disp_pos; /* 0x12004 */
    volatile reg_v0_mrg_disp_reso v0_mrg_disp_reso; /* 0x12008 */
    volatile reg_v0_mrg_src_reso v0_mrg_src_reso; /* 0x1200c */
    volatile reg_v0_mrg_src_offset v0_mrg_src_offset; /* 0x12010 */
    volatile unsigned int v0_mrg_y_addr; /* 0x12014 */
    volatile unsigned int v0_mrg_c_addr; /* 0x12018 */
    volatile reg_v0_mrg_stride v0_mrg_stride; /* 0x1201c */
    volatile unsigned int v0_mrg_yh_addr; /* 0x12020 */
    volatile unsigned int v0_mrg_ch_addr; /* 0x12024 */
    volatile reg_v0_mrg_hstride v0_mrg_hstride; /* 0x12028 */
    volatile unsigned int reserved_205[5]; /* 0x1202c~0x1203c 5 regs */
    volatile reg_v0_mrg_read_ctrl v0_mrg_read_ctrl; /* 0x12040 */
    volatile reg_v0_mrg_read_en v0_mrg_read_en; /* 0x12044 */
    volatile unsigned int reserved_206[750]; /* 0x12048~0x12bfc 750 regs */
    volatile reg_v1_mrg_ctrl v1_mrg_ctrl; /* 0x12c00 */
    volatile reg_v1_mrg_disp_pos v1_mrg_disp_pos; /* 0x12c04 */
    volatile reg_v1_mrg_disp_reso v1_mrg_disp_reso; /* 0x12c08 */
    volatile reg_v1_mrg_src_reso v1_mrg_src_reso; /* 0x12c0c */
    volatile reg_v1_mrg_src_offset v1_mrg_src_offset; /* 0x12c10 */
    volatile unsigned int v1_mrg_y_addr; /* 0x12c14 */
    volatile unsigned int v1_mrg_c_addr; /* 0x12c18 */
    volatile reg_v1_mrg_stride v1_mrg_stride; /* 0x12c1c */
    volatile unsigned int v1_mrg_yh_addr; /* 0x12c20 */
    volatile unsigned int v1_mrg_ch_addr; /* 0x12c24 */
    volatile reg_v1_mrg_hstride v1_mrg_hstride; /* 0x12c28 */
    volatile unsigned int reserved_207[5]; /* 0x12c2c~0x12c3c 5 regs */
    volatile reg_v1_mrg_read_ctrl v1_mrg_read_ctrl; /* 0x12c40 */
    volatile reg_v1_mrg_read_en v1_mrg_read_en; /* 0x12c44 */
    volatile unsigned int reserved_208[2286]; /* 0x12c48~0x14ffc 2286 regs */
    volatile reg_v1_csc_idc           v1_csc_idc                      ; /* 0x15000 */
    volatile reg_v1_csc_odc           v1_csc_odc                      ; /* 0x15004 */
    volatile reg_v1_csc_iodc          v1_csc_iodc                     ; /* 0x15008 */
    volatile reg_v1_csc_p0            v1_csc_p0                       ; /* 0x1500c */
    volatile reg_v1_csc_p1            v1_csc_p1                       ; /* 0x15010 */
    volatile reg_v1_csc_p2            v1_csc_p2                       ; /* 0x15014 */
    volatile reg_v1_csc_p3            v1_csc_p3                       ; /* 0x15018 */
    volatile reg_v1_csc_p4            v1_csc_p4                       ; /* 0x1501c */
    volatile reg_v1_csc1_idc          v1_csc1_idc                     ; /* 0x15020 */
    volatile reg_v1_csc1_odc          v1_csc1_odc                     ; /* 0x15024 */
    volatile reg_v1_csc1_iodc         v1_csc1_iodc                    ; /* 0x15028 */
    volatile reg_v1_csc1_p0           v1_csc1_p0                      ; /* 0x1502c */
    volatile reg_v1_csc1_p1           v1_csc1_p1                      ; /* 0x15030 */
    volatile reg_v1_csc1_p2           v1_csc1_p2                      ; /* 0x15034 */
    volatile reg_v1_csc1_p3           v1_csc1_p3                      ; /* 0x15038 */
    volatile reg_v1_csc1_p4           v1_csc1_p4                      ; /* 0x1503c */
    volatile unsigned int           reserved_209[48]                ; /* 0x15040~0x150fc 48 regs */
    volatile reg_v2_csc_idc           v2_csc_idc                      ; /* 0x15100 */
    volatile reg_v2_csc_odc           v2_csc_odc                      ; /* 0x15104 */
    volatile reg_v2_csc_iodc          v2_csc_iodc                     ; /* 0x15108 */
    volatile reg_v2_csc_p0            v2_csc_p0                       ; /* 0x1510c */
    volatile reg_v2_csc_p1            v2_csc_p1                       ; /* 0x15110 */
    volatile reg_v2_csc_p2            v2_csc_p2                       ; /* 0x15114 */
    volatile reg_v2_csc_p3            v2_csc_p3                       ; /* 0x15118 */
    volatile reg_v2_csc_p4            v2_csc_p4                       ; /* 0x1511c */
    volatile reg_v2_csc1_idc          v2_csc1_idc                     ; /* 0x15120 */
    volatile reg_v2_csc1_odc          v2_csc1_odc                     ; /* 0x15124 */
    volatile reg_v2_csc1_iodc         v2_csc1_iodc                    ; /* 0x15128 */
    volatile reg_v2_csc1_p0           v2_csc1_p0                      ; /* 0x1512c */
    volatile reg_v2_csc1_p1           v2_csc1_p1                      ; /* 0x15130 */
    volatile reg_v2_csc1_p2           v2_csc1_p2                      ; /* 0x15134 */
    volatile reg_v2_csc1_p3           v2_csc1_p3                      ; /* 0x15138 */
    volatile reg_v2_csc1_p4           v2_csc1_p4                      ; /* 0x1513c */
    volatile unsigned int           reserved_210[48]                ; /* 0x15140~0x151fc 48 regs */
    volatile reg_g1_csc_idc           g1_csc_idc                      ; /* 0x15200 */
    volatile reg_g1_csc_odc           g1_csc_odc                      ; /* 0x15204 */
    volatile reg_g1_csc_iodc          g1_csc_iodc                     ; /* 0x15208 */
    volatile reg_g1_csc_p0            g1_csc_p0                       ; /* 0x1520c */
    volatile reg_g1_csc_p1            g1_csc_p1                       ; /* 0x15210 */
    volatile reg_g1_csc_p2            g1_csc_p2                       ; /* 0x15214 */
    volatile reg_g1_csc_p3            g1_csc_p3                       ; /* 0x15218 */
    volatile reg_g1_csc_p4            g1_csc_p4                       ; /* 0x1521c */
    volatile reg_g1_csc1_idc          g1_csc1_idc                     ; /* 0x15220 */
    volatile reg_g1_csc1_odc          g1_csc1_odc                     ; /* 0x15224 */
    volatile reg_g1_csc1_iodc         g1_csc1_iodc                    ; /* 0x15228 */
    volatile reg_g1_csc1_p0           g1_csc1_p0                      ; /* 0x1522c */
    volatile reg_g1_csc1_p1           g1_csc1_p1                      ; /* 0x15230 */
    volatile reg_g1_csc1_p2           g1_csc1_p2                      ; /* 0x15234 */
    volatile reg_g1_csc1_p3           g1_csc1_p3                      ; /* 0x15238 */
    volatile reg_g1_csc1_p4           g1_csc1_p4                      ; /* 0x1523c */
    volatile unsigned int           reserved_211[48]                ; /* 0x15240~0x152fc 48 regs */
    volatile reg_g3_csc_idc           g3_csc_idc                      ; /* 0x15300 */
    volatile reg_g3_csc_odc           g3_csc_odc                      ; /* 0x15304 */
    volatile reg_g3_csc_iodc          g3_csc_iodc                     ; /* 0x15308 */
    volatile reg_g3_csc_p0            g3_csc_p0                       ; /* 0x1530c */
    volatile reg_g3_csc_p1            g3_csc_p1                       ; /* 0x15310 */
    volatile reg_g3_csc_p2            g3_csc_p2                       ; /* 0x15314 */
    volatile reg_g3_csc_p3            g3_csc_p3                       ; /* 0x15318 */
    volatile reg_g3_csc_p4            g3_csc_p4                       ; /* 0x1531c */
    volatile reg_g3_csc1_idc          g3_csc1_idc                     ; /* 0x15320 */
    volatile reg_g3_csc1_odc          g3_csc1_odc                     ; /* 0x15324 */
    volatile reg_g3_csc1_iodc         g3_csc1_iodc                    ; /* 0x15328 */
    volatile reg_g3_csc1_p0           g3_csc1_p0                      ; /* 0x1532c */
    volatile reg_g3_csc1_p1           g3_csc1_p1                      ; /* 0x15330 */
    volatile reg_g3_csc1_p2           g3_csc1_p2                      ; /* 0x15334 */
    volatile reg_g3_csc1_p3           g3_csc1_p3                      ; /* 0x15338 */
    volatile reg_g3_csc1_p4           g3_csc1_p4                      ; /* 0x1533c */
    volatile unsigned int           reserved_212[48]                ; /* 0x15340~0x153fc 48 regs */
    volatile reg_v0_cvfir_vinfo       v0_cvfir_vinfo                  ; /* 0x15400 */
    volatile reg_v0_cvfir_vsp         v0_cvfir_vsp                    ; /* 0x15404 */
    volatile reg_v0_cvfir_voffset     v0_cvfir_voffset                ; /* 0x15408 */
    volatile reg_v0_cvfir_vboffset    v0_cvfir_vboffset               ; /* 0x1540c */
    volatile unsigned int           reserved_213[8]                 ; /* 0x15410~0x1542c 8 regs */
    volatile reg_v0_cvfir_vcoef0      v0_cvfir_vcoef0                 ; /* 0x15430 */
    volatile reg_v0_cvfir_vcoef1      v0_cvfir_vcoef1                 ; /* 0x15434 */
    volatile reg_v0_cvfir_vcoef2      v0_cvfir_vcoef2                 ; /* 0x15438 */
    volatile unsigned int           reserved_214[721]               ; /* 0x1543c~0x15f7c 721 regs */
    volatile reg_gfx_osd_glb_info     gfx_osd_glb_info                ; /* 0x15f80 */
    volatile reg_gfx_osd_frame_size   gfx_osd_frame_size              ; /* 0x15f84 */
    volatile unsigned int           reserved_215[2]                 ; /* 0x15f88~0x15f8c 2 regs */
    volatile reg_gfx_osd_dbg_reg gfx_osd_dbg_reg; /* 0x15f90 */
    volatile reg_gfx_osd_dbg_reg1 gfx_osd_dbg_reg1; /* 0x15f94 */
} reg_vdp_regs;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* __HAL_VO_REG_H__ */
