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

#ifndef __VOU_REG_H__
#define __VOU_REG_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of #ifdef __cplusplus */

/* define the union U_VOCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 25;      /* [24..0]  */
        unsigned int wbc_dhd_ck_gt_en : 1; /* [25]  */
        unsigned int g1_ck_gt_en : 1;      /* [26]  */
        unsigned int v1_ck_gt_en : 1;      /* [27]  */
        unsigned int g0_ck_gt_en : 1;      /* [28]  */
        unsigned int v0_ck_gt_en : 1;      /* [29]  */
        unsigned int chk_sum_en : 1;       /* [30]  */
        unsigned int vo_ck_gt_en : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOCTRL;

/* define the union U_VOINTSTA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_int : 1;   /* [0]  */
        unsigned int dhd0vtthd2_int : 1;   /* [1]  */
        unsigned int dhd0vtthd3_int : 1;   /* [2]  */
        unsigned int dhd0uf_int : 1;       /* [3]  */
        unsigned int dhd1vtthd1_int : 1;   /* [4]  */
        unsigned int dhd1vtthd2_int : 1;   /* [5]  */
        unsigned int dhd1vtthd3_int : 1;   /* [6]  */
        unsigned int dhd1uf_int : 1;       /* [7]  */
        unsigned int dsdvtthd1_int : 1;    /* [8]  */
        unsigned int dsdvtthd2_int : 1;    /* [9]  */
        unsigned int dsdvtthd3_int : 1;    /* [10]  */
        unsigned int dsduf_int : 1;        /* [11]  */
        unsigned int b0_err_int : 1;       /* [12]  */
        unsigned int b1_err_int : 1;       /* [13]  */
        unsigned int b2_err_int : 1;       /* [14]  */
        unsigned int wbc_dhd_over_int : 1; /* [15]  */
        unsigned int vdac0_int : 1;        /* [16]  */
        unsigned int vdac1_int : 1;        /* [17]  */
        unsigned int vdac2_int : 1;        /* [18]  */
        unsigned int vdac3_int : 1;        /* [19]  */
        unsigned int reserved_0 : 12;      /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOINTSTA;

/* define the union U_VOMSKINTSTA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_clr : 1;   /* [0]  */
        unsigned int dhd0vtthd2_clr : 1;   /* [1]  */
        unsigned int dhd0vtthd3_clr : 1;   /* [2]  */
        unsigned int dhd0uf_clr : 1;       /* [3]  */
        unsigned int dhd1vtthd1_clr : 1;   /* [4]  */
        unsigned int dhd1vtthd2_clr : 1;   /* [5]  */
        unsigned int dhd1vtthd3_clr : 1;   /* [6]  */
        unsigned int dhd1uf_clr : 1;       /* [7]  */
        unsigned int dsdvtthd1_clr : 1;    /* [8]  */
        unsigned int dsdvtthd2_clr : 1;    /* [9]  */
        unsigned int dsdvtthd3_clr : 1;    /* [10]  */
        unsigned int dsduf_clr : 1;        /* [11]  */
        unsigned int b0_err_clr : 1;       /* [12]  */
        unsigned int b1_err_clr : 1;       /* [13]  */
        unsigned int b2_err_clr : 1;       /* [14]  */
        unsigned int wbc_dhd_over_clr : 1; /* [15]  */
        unsigned int vdac0_clr : 1;        /* [16]  */
        unsigned int vdac1_clr : 1;        /* [17]  */
        unsigned int vdac2_clr : 1;        /* [18]  */
        unsigned int vdac3_clr : 1;        /* [19]  */
        unsigned int reserved_0 : 12;      /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOMSKINTSTA;

/* define the union U_VOINTMSK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_intmask : 1;   /* [0]  */
        unsigned int dhd0vtthd2_intmask : 1;   /* [1]  */
        unsigned int dhd0vtthd3_intmask : 1;   /* [2]  */
        unsigned int dhd0uf_intmask : 1;       /* [3]  */
        unsigned int dhd1vtthd1_intmask : 1;   /* [4]  */
        unsigned int dhd1vtthd2_intmask : 1;   /* [5]  */
        unsigned int dhd1vtthd3_intmask : 1;   /* [6]  */
        unsigned int dhd1uf_intmask : 1;       /* [7]  */
        unsigned int dsdvtthd1_intmask : 1;    /* [8]  */
        unsigned int dsdvtthd2_intmask : 1;    /* [9]  */
        unsigned int dsdvtthd3_intmask : 1;    /* [10]  */
        unsigned int dsduf_intmask : 1;        /* [11]  */
        unsigned int b0_err_intmask : 1;       /* [12]  */
        unsigned int b1_err_intmask : 1;       /* [13]  */
        unsigned int b2_err_intmask : 1;       /* [14]  */
        unsigned int wbc_dhd_over_intmask : 1; /* [15]  */
        unsigned int vdac0_intmask : 1;        /* [16]  */
        unsigned int vdac1_intmask : 1;        /* [17]  */
        unsigned int vdac2_intmask : 1;        /* [18]  */
        unsigned int vdac3_intmask : 1;        /* [19]  */
        unsigned int reserved_0 : 12;          /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOINTMSK;

/* define the union U_VODEBUG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rm_chn : 4;     /* [3..0]  */
        unsigned int dhd0_ff_info : 2;  /* [5..4]  */
        unsigned int dhd1_ff_info : 2;  /* [7..6]  */
        unsigned int dsd0_ff_info : 2;  /* [9..8]  */
        unsigned int bfm_vga_en : 1;    /* [10]  */
        unsigned int bfm_cvbs_en : 1;   /* [11]  */
        unsigned int bfm_lcd_en : 1;    /* [12]  */
        unsigned int bfm_bt1120_en : 1; /* [13]  */
        unsigned int wbc2_ff_info : 2;  /* [15..14]  */
        unsigned int wbc_mode : 4;      /* [19..16]  */
        unsigned int node_num : 4;      /* [23..20]  */
        unsigned int wbc_cmp_mode : 2;  /* [25..24]  */
        unsigned int bfm_mode : 3;      /* [28..26]  */
        unsigned int bfm_clk_sel : 3;   /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VODEBUG;

/* define the union U_VOINTSTA1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_int : 1;   /* [0]  */
        unsigned int dhd0vtthd2_int : 1;   /* [1]  */
        unsigned int dhd0vtthd3_int : 1;   /* [2]  */
        unsigned int dhd0uf_int : 1;       /* [3]  */
        unsigned int dhd1vtthd1_int : 1;   /* [4]  */
        unsigned int dhd1vtthd2_int : 1;   /* [5]  */
        unsigned int dhd1vtthd3_int : 1;   /* [6]  */
        unsigned int dhd1uf_int : 1;       /* [7]  */
        unsigned int dsdvtthd1_int : 1;    /* [8]  */
        unsigned int dsdvtthd2_int : 1;    /* [9]  */
        unsigned int dsdvtthd3_int : 1;    /* [10]  */
        unsigned int dsduf_int : 1;        /* [11]  */
        unsigned int b0_err_int : 1;       /* [12]  */
        unsigned int b1_err_int : 1;       /* [13]  */
        unsigned int b2_err_int : 1;       /* [14]  */
        unsigned int wbc_dhd_over_int : 1; /* [15]  */
        unsigned int vdac0_int : 1;        /* [16]  */
        unsigned int vdac1_int : 1;        /* [17]  */
        unsigned int vdac2_int : 1;        /* [18]  */
        unsigned int vdac3_int : 1;        /* [19]  */
        unsigned int reserved_0 : 12;      /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOINTSTA1;

/* define the union U_VOMSKINTSTA1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_clr : 1;   /* [0]  */
        unsigned int dhd0vtthd2_clr : 1;   /* [1]  */
        unsigned int dhd0vtthd3_clr : 1;   /* [2]  */
        unsigned int dhd0uf_clr : 1;       /* [3]  */
        unsigned int dhd1vtthd1_clr : 1;   /* [4]  */
        unsigned int dhd1vtthd2_clr : 1;   /* [5]  */
        unsigned int dhd1vtthd3_clr : 1;   /* [6]  */
        unsigned int dhd1uf_clr : 1;       /* [7]  */
        unsigned int dsdvtthd1_clr : 1;    /* [8]  */
        unsigned int dsdvtthd2_clr : 1;    /* [9]  */
        unsigned int dsdvtthd3_clr : 1;    /* [10]  */
        unsigned int dsduf_clr : 1;        /* [11]  */
        unsigned int b0_err_clr : 1;       /* [12]  */
        unsigned int b1_err_clr : 1;       /* [13]  */
        unsigned int b2_err_clr : 1;       /* [14]  */
        unsigned int wbc_dhd_over_clr : 1; /* [15]  */
        unsigned int vdac0_clr : 1;        /* [16]  */
        unsigned int vdac1_clr : 1;        /* [17]  */
        unsigned int vdac2_clr : 1;        /* [18]  */
        unsigned int vdac3_clr : 1;        /* [19]  */
        unsigned int reserved_0 : 12;      /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOMSKINTSTA1;

/* define the union U_VOINTMSK1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dhd0vtthd1_intmask : 1;   /* [0]  */
        unsigned int dhd0vtthd2_intmask : 1;   /* [1]  */
        unsigned int dhd0vtthd3_intmask : 1;   /* [2]  */
        unsigned int dhd0uf_intmask : 1;       /* [3]  */
        unsigned int dhd1vtthd1_intmask : 1;   /* [4]  */
        unsigned int dhd1vtthd2_intmask : 1;   /* [5]  */
        unsigned int dhd1vtthd3_intmask : 1;   /* [6]  */
        unsigned int dhd1uf_intmask : 1;       /* [7]  */
        unsigned int dsdvtthd1_intmask : 1;    /* [8]  */
        unsigned int dsdvtthd2_intmask : 1;    /* [9]  */
        unsigned int dsdvtthd3_intmask : 1;    /* [10]  */
        unsigned int dsduf_intmask : 1;        /* [11]  */
        unsigned int b0_err_intmask : 1;       /* [12]  */
        unsigned int b1_err_intmask : 1;       /* [13]  */
        unsigned int b2_err_intmask : 1;       /* [14]  */
        unsigned int wbc_dhd_over_intmask : 1; /* [15]  */
        unsigned int vdac0_intmask : 1;        /* [16]  */
        unsigned int vdac1_intmask : 1;        /* [17]  */
        unsigned int vdac2_intmask : 1;        /* [18]  */
        unsigned int vdac3_intmask : 1;        /* [19]  */
        unsigned int reserved_0 : 12;          /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOINTMSK1;

/* define the union U_VOLOWPOWER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfs_ema : 3;      /* [2..0]  */
        unsigned int rfs_emaw : 2;     /* [4..3]  */
        unsigned int ret1n : 1;        /* [5]  */
        unsigned int rft_emaa : 3;     /* [8..6]  */
        unsigned int rft_emab : 3;     /* [11..9]  */
        unsigned int rfs_colldisn : 1; /* [12]  */
        unsigned int rft_emasa : 1;    /* [13]  */
        unsigned int rfsuhd_wtsel : 2; /* [15..14]  */
        unsigned int rfsuhd_rtsel : 2; /* [17..16]  */
        unsigned int rfs_wtsel : 2;    /* [19..18]  */
        unsigned int rfs_rtsel : 2;    /* [21..20]  */
        unsigned int rfts_wct : 2;     /* [23..22]  */
        unsigned int rfts_rct : 2;     /* [25..24]  */
        unsigned int rfts_kp : 3;      /* [28..26]  */
        unsigned int rftf_wct : 2;     /* [30..29]  */
        unsigned int reserved_0 : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOLOWPOWER_CTRL;

/* define the union U_VOUFSTA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_uf_sta : 1;   /* [0]  */
        unsigned int v1_uf_sta : 1;   /* [1]  */
        unsigned int reserved_0 : 1;  /* [2]  */
        unsigned int v3_uf_sta : 1;   /* [3]  */
        unsigned int reserved_1 : 4;  /* [7..4]  */
        unsigned int g0_uf_sta : 1;   /* [8]  */
        unsigned int g1_uf_sta : 1;   /* [9]  */
        unsigned int g2_uf_sta : 1;   /* [10]  */
        unsigned int g3_uf_sta : 1;   /* [11]  */
        unsigned int g4_uf_sta : 1;   /* [12]  */
        unsigned int reserved_2 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOUFSTA;

/* define the union U_VOUFCLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_uf_clr : 1;   /* [0]  */
        unsigned int v1_uf_clr : 1;   /* [1]  */
        unsigned int reserved_0 : 1;  /* [2]  */
        unsigned int v3_uf_clr : 1;   /* [3]  */
        unsigned int reserved_1 : 4;  /* [7..4]  */
        unsigned int g0_uf_clr : 1;   /* [8]  */
        unsigned int g1_uf_clr : 1;   /* [9]  */
        unsigned int g2_uf_clr : 1;   /* [10]  */
        unsigned int g3_uf_clr : 1;   /* [11]  */
        unsigned int g4_uf_clr : 1;   /* [12]  */
        unsigned int reserved_2 : 19; /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOUFCLR;

/* define the union U_VOINTPROC_TIM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vointproc_time : 24; /* [23..0]  */
        unsigned int reserved_0 : 8;      /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOINTPROC_TIM;

/* define the union U_VOLOWPOWER_CTRL1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rftf_rct : 2;      /* [1..0]  */
        unsigned int rftf_kp : 3;       /* [4..2]  */
        unsigned int rft_wtsel : 2;     /* [6..5]  */
        unsigned int rft_rtsel : 2;     /* [8..7]  */
        unsigned int rft_mtsel : 2;     /* [10..9]  */
        unsigned int rasshds_wtsel : 2; /* [12..11]  */
        unsigned int rasshds_rtsel : 2; /* [14..13]  */
        unsigned int rasshdm_wtsel : 2; /* [16..15]  */
        unsigned int rasshdm_rtsel : 2; /* [18..17]  */
        unsigned int rashds_wtsel : 2;  /* [20..19]  */
        unsigned int rashds_rtsel : 2;  /* [22..21]  */
        unsigned int rashdm_wtsel : 2;  /* [24..23]  */
        unsigned int rashdm_rtsel : 2;  /* [26..25]  */
        unsigned int ras_wtsel : 2;     /* [28..27]  */
        unsigned int ras_rtsel : 2;     /* [30..29]  */
        unsigned int reserved_0 : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOLOWPOWER_CTRL1;

/* define the union U_VOFPGADEF */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_v_def : 1;  /* [0]  */
        unsigned int hihdr_g_def : 1;  /* [1]  */
        unsigned int hihdr_wd_def : 1; /* [2]  */
        unsigned int reserved_0 : 29;  /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VOFPGADEF;

/* define the union U_CBM_BKG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm_bkgcr1 : 10; /* [9..0]  */
        unsigned int cbm_bkgcb1 : 10; /* [19..10]  */
        unsigned int cbm_bkgy1 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2;  /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CBM_BKG1;

/* define the union U_CBM_MIX1 */
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
} U_CBM_MIX1;

/* define the union U_WBC_BMP_THD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_bmp_thd : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_BMP_THD;

/* define the union U_CBM_BKG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm_bkgcr2 : 10; /* [9..0]  */
        unsigned int cbm_bkgcb2 : 10; /* [19..10]  */
        unsigned int cbm_bkgy2 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2;  /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CBM_BKG2;

/* define the union U_CBM_MIX2 */
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
} U_CBM_MIX2;

/* define the union U_HC_BMP_THD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hc_bmp_thd : 8;  /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HC_BMP_THD;

/* define the union U_CBM_BKG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm_bkgcr3 : 10; /* [9..0]  */
        unsigned int cbm_bkgcb3 : 10; /* [19..10]  */
        unsigned int cbm_bkgy3 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2;  /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CBM_BKG3;

/* define the union U_CBM_MIX3 */
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
} U_CBM_MIX3;

/* define the union U_MIXV0_BKG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_bkgcr : 10; /* [9..0]  */
        unsigned int mixer_bkgcb : 10; /* [19..10]  */
        unsigned int mixer_bkgy : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIXV0_BKG;

/* define the union U_MIXV0_MIX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_prio0 : 4; /* [3..0]  */
        unsigned int mixer_prio1 : 4; /* [7..4]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIXV0_MIX;

/* define the union U_MIXG0_BKG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_bkgcr : 10; /* [9..0]  */
        unsigned int mixer_bkgcb : 10; /* [19..10]  */
        unsigned int mixer_bkgy : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIXG0_BKG;

/* define the union U_MIXG0_BKALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mixer_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIXG0_BKALPHA;

/* define the union U_MIXG0_MIX */
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
} U_MIXG0_MIX;

/* define the union U_LINK_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cbm0_sel : 1;    /* [0]  */
        unsigned int cbm1_sel : 1;    /* [1]  */
        unsigned int hc_link : 1;     /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LINK_CTRL;

/* define the union U_VPSS_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vpss_en : 1;         /* [0]  */
        unsigned int chk_sum_en : 1;      /* [1]  */
        unsigned int dei_en : 1;          /* [2]  */
        unsigned int mcdi_en : 1;         /* [3]  */
        unsigned int nx2_vc1_en : 1;      /* [4]  */
        unsigned int rgme_en : 1;         /* [5]  */
        unsigned int meds_en : 1;         /* [6]  */
        unsigned int hsp_en : 1;          /* [7]  */
        unsigned int snr_en : 1;          /* [8]  */
        unsigned int tnr_en : 1;          /* [9]  */
        unsigned int rfr_en : 1;          /* [10]  */
        unsigned int ifmd_en : 1;         /* [11]  */
        unsigned int igbm_en : 1;         /* [12]  */
        unsigned int cue_en : 1;          /* [13]  */
        unsigned int scd_en : 1;          /* [14]  */
        unsigned int blk_det_en : 1;      /* [15]  */
        unsigned int reserved_0 : 7;      /* [22..16]  */
        unsigned int vpss_node_init : 1;  /* [23]  */
        unsigned int ram_bank : 4;        /* [27..24]  */
        unsigned int dei_debug_en : 1;    /* [28]  */
        unsigned int dei_repeat_mode : 1; /* [29]  */
        unsigned int reserved_1 : 2;      /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CTRL;

/* define the union U_VPSS_MISCELLANEOUS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 4;    /* [3..0]  */
        unsigned int reserved_1 : 4;    /* [7..4]  */
        unsigned int reserved_2 : 16;   /* [23..8]  */
        unsigned int ck_gt_en : 1;      /* [24]  */
        unsigned int ck_gt_calc : 1; /* [25]  */
        unsigned int reserved_3 : 2;    /* [27..26]  */
        unsigned int reserved_4 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_MISCELLANEOUS;

/* define the union U_VPSS_FTCONFIG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int node_rst_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_FTCONFIG;

/* define the union U_PARA_UP_VHD */
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
} U_PARA_UP_VHD;

/* define the union U_PARA_UP_VSD */
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
        unsigned int reserved_0 : 24;       /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PARA_UP_VSD;

/* define the union U_PARA_CONFLICT_CLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_conflict_clr_hd : 1; /* [0]  */
        unsigned int para_conflict_clr_sd : 1; /* [1]  */
        unsigned int reserved_0 : 30;          /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PARA_CONFLICT_CLR;

/* define the union U_PARA_CONFLICT_STA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_conflict_hd : 1; /* [0]  */
        unsigned int para_conflict_sd : 1; /* [1]  */
        unsigned int reserved_0 : 30;      /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PARA_CONFLICT_STA;

/* define the union U_V0_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;      /* [7..0]  */
        unsigned int reserved_0 : 20; /* [27..8]  */
        unsigned int rupd_field : 1;  /* [28]  */
        unsigned int rgup_mode : 1;   /* [29]  */
        unsigned int nosec_flag : 1;  /* [30]  */
        unsigned int surface_en : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_CTRL;

/* define the union U_V0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_UPD;

/* define the union U_V0_0RESO_READ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_0RESO_READ;

/* define the union U_V0_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_DFPOS;

/* define the union U_V0_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_DLPOS;

/* define the union U_V0_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_VFPOS;

/* define the union U_V0_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_VLPOS;

/* define the union U_V0_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_BK;

/* define the union U_V0_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ALPHA;

/* define the union U_V0_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 1; /* [30]  */
        unsigned int mute_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MUTE_BK;

/* define the union U_V0_RIMWIDTH */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_width : 5; /* [4..0]  */
        unsigned int reserved_0 : 27;  /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_RIMWIDTH;

/* define the union U_V0_RIMCOL0 */
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
} U_V0_RIMCOL0;

/* define the union U_V0_RIMCOL1 */
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
} U_V0_RIMCOL1;

/* define the union U_V0_ZME_HINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_width : 16;    /* [15..0]  */
        unsigned int hzme_ck_gt_en : 1; /* [16]  */
        unsigned int reserved_0 : 15;   /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HINFO;

/* define the union U_V0_ZME_HSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 24;    /* [23..0]  */
        unsigned int hfir_order : 1; /* [24]  */
        unsigned int chfir_mode : 1; /* [25]  */
        unsigned int lhfir_mode : 1; /* [26]  */
        unsigned int non_lnr_en : 1; /* [27]  */
        unsigned int chmid_en : 1;   /* [28]  */
        unsigned int lhmid_en : 1;   /* [29]  */
        unsigned int chfir_en : 1;   /* [30]  */
        unsigned int lhfir_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HSP;

/* define the union U_V0_ZME_HLOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lhfir_offset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HLOFFSET;

/* define the union U_V0_ZME_HCOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chfir_offset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HCOFFSET;

/* define the union U_V0_ZME_HZONE0DELTA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int zone0_delta : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;  /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HZONE0DELTA;

/* define the union U_V0_ZME_HZONE2DELTA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int zone2_delta : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;  /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HZONE2DELTA;

/* define the union U_V0_ZME_HZONEEND */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int zone0_end : 12; /* [11..0]  */
        unsigned int zone1_end : 12; /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HZONEEND;

/* define the union U_V0_ZME_HL_SHOOTCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hl_coring : 8;         /* [7..0]  */
        unsigned int hl_gain : 6;           /* [13..8]  */
        unsigned int hl_coringadj_en : 1;   /* [14]  */
        unsigned int hl_flatdect_mode : 1;  /* [15]  */
        unsigned int hl_shootctrl_mode : 1; /* [16]  */
        unsigned int reserved_0 : 1;        /* [17]  */
        unsigned int hl_shootctrl_en : 1;   /* [18]  */
        unsigned int reserved_1 : 13;       /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HL_SHOOTCTRL;

/* define the union U_V0_ZME_HC_SHOOTCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hc_coring : 8;         /* [7..0]  */
        unsigned int hc_gain : 6;           /* [13..8]  */
        unsigned int hc_coringadj_en : 1;   /* [14]  */
        unsigned int hc_flatdect_mode : 1;  /* [15]  */
        unsigned int hc_shootctrl_mode : 1; /* [16]  */
        unsigned int reserved_0 : 1;        /* [17]  */
        unsigned int hc_shootctrl_en : 1;   /* [18]  */
        unsigned int reserved_1 : 13;       /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HC_SHOOTCTRL;

/* define the union U_V0_ZME_HCOEF_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_hf_cren : 1; /* [0]  */
        unsigned int apb_vhd_hf_lren : 1; /* [1]  */
        unsigned int reserved_0 : 30;     /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HCOEF_REN;

/* define the union U_V0_ZME_HCOEF_RDATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_hcoef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24;         /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_HCOEF_RDATA;

/* define the union U_V0_ZME_VINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16;   /* [15..0]  */
        unsigned int out_fmt : 2;       /* [17..16]  */
        unsigned int out_pro : 1;       /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12;   /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VINFO;

/* define the union U_V0_ZME_VSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16;      /* [15..0]  */
        unsigned int graphdet_en : 1;  /* [16]  */
        unsigned int reserved_0 : 8;   /* [24..17]  */
        unsigned int cvfir_mode : 1;   /* [25]  */
        unsigned int lvfir_mode : 1;   /* [26]  */
        unsigned int vfir_1tap_en : 1; /* [27]  */
        unsigned int cvmid_en : 1;     /* [28]  */
        unsigned int lvmid_en : 1;     /* [29]  */
        unsigned int cvfir_en : 1;     /* [30]  */
        unsigned int lvfir_en : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VSP;

/* define the union U_V0_ZME_VOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int vluma_offset : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VOFFSET;

/* define the union U_V0_ZME_VBOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int vbluma_offset : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VBOFFSET;

/* define the union U_V0_ZME_VL_SHOOTCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vl_coring : 8;         /* [7..0]  */
        unsigned int vl_gain : 6;           /* [13..8]  */
        unsigned int vl_coringadj_en : 1;   /* [14]  */
        unsigned int vl_flatdect_mode : 1;  /* [15]  */
        unsigned int vl_shootctrl_mode : 1; /* [16]  */
        unsigned int reserved_0 : 1;        /* [17]  */
        unsigned int vl_shootctrl_en : 1;   /* [18]  */
        unsigned int reserved_1 : 13;       /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VL_SHOOTCTRL;

/* define the union U_V0_ZME_VC_SHOOTCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vc_coring : 8;         /* [7..0]  */
        unsigned int vc_gain : 6;           /* [13..8]  */
        unsigned int vc_coringadj_en : 1;   /* [14]  */
        unsigned int vc_flatdect_mode : 1;  /* [15]  */
        unsigned int vc_shootctrl_mode : 1; /* [16]  */
        unsigned int reserved_0 : 1;        /* [17]  */
        unsigned int vc_shootctrl_en : 1;   /* [18]  */
        unsigned int reserved_1 : 13;       /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VC_SHOOTCTRL;

/* define the union U_V0_ZME_VCOEF_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_vf_cren : 1; /* [0]  */
        unsigned int apb_vhd_vf_lren : 1; /* [1]  */
        unsigned int reserved_0 : 30;     /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VCOEF_REN;

/* define the union U_V0_ZME_VCOEF_RDATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_vcoef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24;         /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_ZME_VCOEF_RDATA;

/* define the union U_V0_HFIR_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;  /* [0]  */
        unsigned int hfir_mode : 2;   /* [2..1]  */
        unsigned int mid_en : 1;      /* [3]  */
        unsigned int ck_gt_en : 1;    /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_HFIR_CTRL;

/* define the union U_V0_HFIRCOEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_HFIRCOEF01;

/* define the union U_V0_HFIRCOEF23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_HFIRCOEF23;

/* define the union U_V0_HFIRCOEF45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef4 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef5 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_HFIRCOEF45;

/* define the union U_V0_HFIRCOEF67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef6 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef7 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_HFIRCOEF67;

/* define the union U_V1_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;      /* [7..0]  */
        unsigned int reserved_0 : 20; /* [27..8]  */
        unsigned int rupd_field : 1;  /* [28]  */
        unsigned int rgup_mode : 1;   /* [29]  */
        unsigned int nosec_flag : 1;  /* [30]  */
        unsigned int surface_en : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CTRL;

/* define the union U_V1_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_UPD;

/* define the union U_V1_0RESO_READ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_0RESO_READ;

/* define the union U_V1_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_DFPOS;

/* define the union U_V1_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_DLPOS;

/* define the union U_V1_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_VFPOS;

/* define the union U_V1_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_VLPOS;

/* define the union U_V1_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_BK;

/* define the union U_V1_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_ALPHA;

/* define the union U_V1_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 1; /* [30]  */
        unsigned int mute_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MUTE_BK;

/* define the union U_V1_RIMWIDTH */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v0_rim_width : 5; /* [4..0]  */
        unsigned int reserved_0 : 27;  /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_RIMWIDTH;

/* define the union U_V1_RIMCOL0 */
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
} U_V1_RIMCOL0;

/* define the union U_V1_RIMCOL1 */
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
} U_V1_RIMCOL1;

/* define the union U_V1_CSC_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;     /* [10..0]  */
        unsigned int cscidc1 : 11;     /* [21..11]  */
        unsigned int csc_en : 1;       /* [22]  */
        unsigned int csc_mode : 3;     /* [25..23]  */
        unsigned int csc_ck_gt_en : 1; /* [26]  */
        unsigned int reserved_0 : 5;   /* [31..27]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_IDC;

/* define the union U_V1_CSC_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_ODC;

/* define the union U_V1_CSC_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_IODC;

/* define the union U_V1_CSC_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_P0;

/* define the union U_V1_CSC_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_P1;

/* define the union U_V1_CSC_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_P2;

/* define the union U_V1_CSC_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_P3;

/* define the union U_V1_CSC_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC_P4;

/* define the union U_V1_CSC1_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;   /* [10..0]  */
        unsigned int cscidc1 : 11;   /* [21..11]  */
        unsigned int csc_en : 1;     /* [22]  */
        unsigned int csc_mode : 3;   /* [25..23]  */
        unsigned int reserved_0 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_IDC;

/* define the union U_V1_CSC1_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_ODC;

/* define the union U_V1_CSC1_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_IODC;

/* define the union U_V1_CSC1_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_P0;

/* define the union U_V1_CSC1_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_P1;

/* define the union U_V1_CSC1_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_P2;

/* define the union U_V1_CSC1_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_P3;

/* define the union U_V1_CSC1_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CSC1_P4;

/* define the union U_V1_CVFIR_VINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16;   /* [15..0]  */
        unsigned int out_fmt : 2;       /* [17..16]  */
        unsigned int out_pro : 1;       /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12;   /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VINFO;

/* define the union U_V1_CVFIR_VSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16;    /* [15..0]  */
        unsigned int reserved_0 : 1; /* [16]  */
        unsigned int reserved_1 : 8; /* [24..17]  */
        unsigned int cvfir_mode : 1; /* [25]  */
        unsigned int reserved_2 : 1; /* [26]  */
        unsigned int reserved_3 : 1; /* [27]  */
        unsigned int cvmid_en : 1;   /* [28]  */
        unsigned int reserved_4 : 1; /* [29]  */
        unsigned int cvfir_en : 1;   /* [30]  */
        unsigned int reserved_5 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VSP;

/* define the union U_V1_CVFIR_VOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VOFFSET;

/* define the union U_V1_CVFIR_VBOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VBOFFSET;

/* define the union U_V1_CVFIR_VCOEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef02 : 10;  /* [9..0]  */
        unsigned int vccoef01 : 10;  /* [19..10]  */
        unsigned int vccoef00 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VCOEF0;

/* define the union U_V1_CVFIR_VCOEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef11 : 10;  /* [9..0]  */
        unsigned int vccoef10 : 10;  /* [19..10]  */
        unsigned int vccoef03 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VCOEF1;

/* define the union U_V1_CVFIR_VCOEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef13 : 10;   /* [9..0]  */
        unsigned int vccoef12 : 10;   /* [19..10]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_CVFIR_VCOEF2;

/* define the union U_V1_HFIR_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;  /* [0]  */
        unsigned int hfir_mode : 2;   /* [2..1]  */
        unsigned int mid_en : 1;      /* [3]  */
        unsigned int ck_gt_en : 1;    /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_HFIR_CTRL;

/* define the union U_V1_HFIRCOEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_HFIRCOEF01;

/* define the union U_V1_HFIRCOEF23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_HFIRCOEF23;

/* define the union U_V1_HFIRCOEF45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef4 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef5 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_HFIRCOEF45;

/* define the union U_V1_HFIRCOEF67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef6 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef7 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_HFIRCOEF67;

/* define the union U_V2_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;      /* [7..0]  */
        unsigned int reserved_0 : 20; /* [27..8]  */
        unsigned int rupd_field : 1;  /* [28]  */
        unsigned int rgup_mode : 1;   /* [29]  */
        unsigned int nosec_flag : 1;  /* [30]  */
        unsigned int surface_en : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CTRL;

/* define the union U_V2_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_UPD;

/* define the union U_V2_0RESO_READ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_0RESO_READ;

/* define the union U_V2_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_DFPOS;

/* define the union U_V2_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_DLPOS;

/* define the union U_V2_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_VFPOS;

/* define the union U_V2_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_VLPOS;

/* define the union U_V2_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_BK;

/* define the union U_V2_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_ALPHA;

/* define the union U_V2_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_MUTE_BK;

/* define the union U_V2_LBOX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1;     /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_LBOX_CTRL;

/* define the union U_V2_CSC_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;     /* [10..0]  */
        unsigned int cscidc1 : 11;     /* [21..11]  */
        unsigned int csc_en : 1;       /* [22]  */
        unsigned int csc_mode : 3;     /* [25..23]  */
        unsigned int csc_ck_gt_en : 1; /* [26]  */
        unsigned int reserved_0 : 5;   /* [31..27]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_IDC;

/* define the union U_V2_CSC_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_ODC;

/* define the union U_V2_CSC_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_IODC;

/* define the union U_V2_CSC_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_P0;

/* define the union U_V2_CSC_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_P1;

/* define the union U_V2_CSC_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_P2;

/* define the union U_V2_CSC_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_P3;

/* define the union U_V2_CSC_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC_P4;

/* define the union U_V2_CSC1_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;   /* [10..0]  */
        unsigned int cscidc1 : 11;   /* [21..11]  */
        unsigned int csc_en : 1;     /* [22]  */
        unsigned int csc_mode : 3;   /* [25..23]  */
        unsigned int reserved_0 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_IDC;

/* define the union U_V2_CSC1_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_ODC;

/* define the union U_V2_CSC1_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_IODC;

/* define the union U_V2_CSC1_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_P0;

/* define the union U_V2_CSC1_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_P1;

/* define the union U_V2_CSC1_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_P2;

/* define the union U_V2_CSC1_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_P3;

/* define the union U_V2_CSC1_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CSC1_P4;

/* define the union U_V2_CVFIR_VINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16;   /* [15..0]  */
        unsigned int out_fmt : 2;       /* [17..16]  */
        unsigned int out_pro : 1;       /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12;   /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VINFO;

/* define the union U_V2_CVFIR_VSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16;    /* [15..0]  */
        unsigned int reserved_0 : 1; /* [16]  */
        unsigned int reserved_1 : 8; /* [24..17]  */
        unsigned int cvfir_mode : 1; /* [25]  */
        unsigned int reserved_2 : 1; /* [26]  */
        unsigned int reserved_3 : 1; /* [27]  */
        unsigned int cvmid_en : 1;   /* [28]  */
        unsigned int reserved_4 : 1; /* [29]  */
        unsigned int cvfir_en : 1;   /* [30]  */
        unsigned int reserved_5 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VSP;

/* define the union U_V2_CVFIR_VOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VOFFSET;

/* define the union U_V2_CVFIR_VBOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VBOFFSET;

/* define the union U_V2_CVFIR_VCOEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef02 : 10;  /* [9..0]  */
        unsigned int vccoef01 : 10;  /* [19..10]  */
        unsigned int vccoef00 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VCOEF0;

/* define the union U_V2_CVFIR_VCOEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef11 : 10;  /* [9..0]  */
        unsigned int vccoef10 : 10;  /* [19..10]  */
        unsigned int vccoef03 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VCOEF1;

/* define the union U_V2_CVFIR_VCOEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vccoef13 : 10;   /* [9..0]  */
        unsigned int vccoef12 : 10;   /* [19..10]  */
        unsigned int reserved_0 : 12; /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_CVFIR_VCOEF2;

/* define the union U_V2_HFIR_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;  /* [0]  */
        unsigned int hfir_mode : 2;   /* [2..1]  */
        unsigned int mid_en : 1;      /* [3]  */
        unsigned int ck_gt_en : 1;    /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_HFIR_CTRL;

/* define the union U_V2_HFIRCOEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_HFIRCOEF01;

/* define the union U_V2_HFIRCOEF23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_HFIRCOEF23;

/* define the union U_V2_HFIRCOEF45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef4 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef5 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_HFIRCOEF45;

/* define the union U_V2_HFIRCOEF67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef6 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef7 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V2_HFIRCOEF67;

/* define the union U_VP0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_UPD;

/* define the union U_VP0_IRESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int iw : 16; /* [15..0]  */
        unsigned int ih : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_IRESO;

/* define the union U_VP0_LBOX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1;     /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_LBOX_CTRL;

/* define the union U_VP0_GALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;      /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_GALPHA;

/* define the union U_VP0_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 12; /* [11..0]  */
        unsigned int disp_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_DFPOS;

/* define the union U_VP0_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 12; /* [11..0]  */
        unsigned int disp_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_DLPOS;

/* define the union U_VP0_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 12; /* [11..0]  */
        unsigned int video_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;   /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_VFPOS;

/* define the union U_VP0_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 12; /* [11..0]  */
        unsigned int video_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;   /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_VLPOS;

/* define the union U_VP0_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_BK;

/* define the union U_VP0_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_ALPHA;

/* define the union U_VP0_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VP0_MUTE_BK;

/* define the union U_G0_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;       /* [7..0]  */
        unsigned int reserved_0 : 19;  /* [26..8]  */
        unsigned int g0_depremult : 1; /* [27]  */
        unsigned int rupd_field : 1;   /* [28]  */
        unsigned int rgup_mode : 1;    /* [29]  */
        unsigned int nosec_flag : 1;   /* [30]  */
        unsigned int surface_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_CTRL;

/* define the union U_G0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_UPD;

/* define the union U_G0_0RESO_READ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_0RESO_READ;

/* define the union U_G0_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_DFPOS;

/* define the union U_G0_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_DLPOS;

/* define the union U_G0_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_VFPOS;

/* define the union U_G0_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_VLPOS;

/* define the union U_G0_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_BK;

/* define the union U_G0_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ALPHA;

/* define the union U_G0_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_MUTE_BK;

/* define the union U_G0_LBOX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1;     /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_LBOX_CTRL;

/* define the union U_G0_DOF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int dof_en : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_DOF_CTRL;

/* define the union U_G0_DOF_STEP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int left_step : 8;   /* [7..0]  */
        unsigned int right_step : 8;  /* [15..8]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_DOF_STEP;

/* define the union U_G0_DOF_BKG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dof_bk_cr : 10; /* [9..0]  */
        unsigned int dof_bk_cb : 10; /* [19..10]  */
        unsigned int dof_bk_y : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_DOF_BKG;

/* define the union U_G0_DOF_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dof_bk_alpha : 8; /* [7..0]  */
        unsigned int reserved_0 : 24;  /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_DOF_ALPHA;

/* define the union U_G0_ZME_HINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_width : 16;  /* [15..0]  */
        unsigned int ck_gt_en : 1;    /* [16]  */
        unsigned int reserved_0 : 15; /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_HINFO;

/* define the union U_G0_ZME_HSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 24;      /* [23..0]  */
        unsigned int hfir_order : 1;   /* [24]  */
        unsigned int ahfir_mode : 1;   /* [25]  */
        unsigned int lhfir_mode : 1;   /* [26]  */
        unsigned int reserved_0 : 1;   /* [27]  */
        unsigned int chfir_mid_en : 1; /* [28]  */
        unsigned int lhfir_mid_en : 1; /* [29]  */
        unsigned int ahfir_mid_en : 1; /* [30]  */
        unsigned int hfir_en : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_HSP;

/* define the union U_G0_ZME_HLOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lhfir_offset : 24; /* [23..0]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_HLOFFSET;

/* define the union U_G0_ZME_HCOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chfir_offset : 24; /* [23..0]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_HCOFFSET;

/* define the union U_G0_ZME_COEF_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;     /* [0]  */
        unsigned int apb_g0_vf_lren : 1; /* [1]  */
        unsigned int reserved_1 : 1;     /* [2]  */
        unsigned int apb_g0_hf_lren : 1; /* [3]  */
        unsigned int reserved_2 : 28;    /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_COEF_REN;

/* define the union U_G0_ZME_COEF_RDATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_coef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24;        /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_COEF_RDATA;

/* define the union U_G0_ZME_VINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16; /* [15..0]  */
        unsigned int reserved_0 : 2;  /* [17..16]  */
        unsigned int out_pro : 1;     /* [18]  */
        unsigned int reserved_1 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_VINFO;

/* define the union U_G0_ZME_VSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16;      /* [15..0]  */
        unsigned int reserved_0 : 9;   /* [24..16]  */
        unsigned int vafir_mode : 1;   /* [25]  */
        unsigned int lvfir_mode : 1;   /* [26]  */
        unsigned int reserved_1 : 1;   /* [27]  */
        unsigned int cvfir_mid_en : 1; /* [28]  */
        unsigned int lvfir_mid_en : 1; /* [29]  */
        unsigned int avfir_mid_en : 1; /* [30]  */
        unsigned int vfir_en : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_VSP;

/* define the union U_G0_ZME_VOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbtm_offset : 16; /* [15..0]  */
        unsigned int vtp_offset : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G0_ZME_VOFFSET;

/* define the union U_G1_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;       /* [7..0]  */
        unsigned int reserved_0 : 19;  /* [26..8]  */
        unsigned int g1_depremult : 1; /* [27]  */
        unsigned int rupd_field : 1;   /* [28]  */
        unsigned int rgup_mode : 1;    /* [29]  */
        unsigned int nosec_flag : 1;   /* [30]  */
        unsigned int surface_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CTRL;

/* define the union U_G1_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_UPD;

/* define the union U_G1_0RESO_READ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_0RESO_READ;

/* define the union U_G1_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_DFPOS;

/* define the union U_G1_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_DLPOS;

/* define the union U_G1_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_VFPOS;

/* define the union U_G1_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_VLPOS;

/* define the union U_G1_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_BK;

/* define the union U_G1_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_ALPHA;

/* define the union U_G1_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_MUTE_BK;

/* define the union U_G1_LBOX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1;     /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_LBOX_CTRL;

/* define the union U_G1_CSC_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;     /* [10..0]  */
        unsigned int cscidc1 : 11;     /* [21..11]  */
        unsigned int csc_en : 1;       /* [22]  */
        unsigned int csc_mode : 3;     /* [25..23]  */
        unsigned int csc_ck_gt_en : 1; /* [26]  */
        unsigned int reserved_0 : 5;   /* [31..27]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_IDC;

/* define the union U_G1_CSC_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_ODC;

/* define the union U_G1_CSC_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_IODC;

/* define the union U_G1_CSC_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_P0;

/* define the union U_G1_CSC_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_P1;

/* define the union U_G1_CSC_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_P2;

/* define the union U_G1_CSC_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_P3;

/* define the union U_G1_CSC_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC_P4;

/* define the union U_G1_CSC1_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;   /* [10..0]  */
        unsigned int cscidc1 : 11;   /* [21..11]  */
        unsigned int csc_en : 1;     /* [22]  */
        unsigned int csc_mode : 3;   /* [25..23]  */
        unsigned int reserved_0 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_IDC;

/* define the union U_G1_CSC1_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_ODC;

/* define the union U_G1_CSC1_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_IODC;

/* define the union U_G1_CSC1_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_P0;

/* define the union U_G1_CSC1_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_P1;

/* define the union U_G1_CSC1_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_P2;

/* define the union U_G1_CSC1_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_P3;

/* define the union U_G1_CSC1_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G1_CSC1_P4;

/* define the union U_G3_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;       /* [7..0]  */
        unsigned int reserved_0 : 19;  /* [26..8]  */
        unsigned int g1_depremult : 1; /* [27]  */
        unsigned int rupd_field : 1;   /* [28]  */
        unsigned int rgup_mode : 1;    /* [29]  */
        unsigned int nosec_flag : 1;   /* [30]  */
        unsigned int surface_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CTRL;

/* define the union U_G3_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_UPD;

/* define the union U_G3_0RESO_READ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_0RESO_READ;

/* define the union U_G3_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 16; /* [15..0]  */
        unsigned int disp_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_DFPOS;

/* define the union U_G3_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 16; /* [15..0]  */
        unsigned int disp_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_DLPOS;

/* define the union U_G3_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 16; /* [15..0]  */
        unsigned int video_yfpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_VFPOS;

/* define the union U_G3_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 16; /* [15..0]  */
        unsigned int video_ylpos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_VLPOS;

/* define the union U_G3_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_BK;

/* define the union U_G3_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_ALPHA;

/* define the union U_G3_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_MUTE_BK;

/* define the union U_G3_LBOX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1;     /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_LBOX_CTRL;

/* define the union U_G3_CSC_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;     /* [10..0]  */
        unsigned int cscidc1 : 11;     /* [21..11]  */
        unsigned int csc_en : 1;       /* [22]  */
        unsigned int csc_mode : 3;     /* [25..23]  */
        unsigned int csc_ck_gt_en : 1; /* [26]  */
        unsigned int reserved_0 : 5;   /* [31..27]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_IDC;

/* define the union U_G3_CSC_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_ODC;

/* define the union U_G3_CSC_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_IODC;

/* define the union U_G3_CSC_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_P0;

/* define the union U_G3_CSC_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_P1;

/* define the union U_G3_CSC_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_P2;

/* define the union U_G3_CSC_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_P3;

/* define the union U_G3_CSC_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC_P4;

/* define the union U_G3_CSC1_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;   /* [10..0]  */
        unsigned int cscidc1 : 11;   /* [21..11]  */
        unsigned int csc_en : 1;     /* [22]  */
        unsigned int csc_mode : 3;   /* [25..23]  */
        unsigned int reserved_0 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_IDC;

/* define the union U_G3_CSC1_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_ODC;

/* define the union U_G3_CSC1_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_IODC;

/* define the union U_G3_CSC1_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_P0;

/* define the union U_G3_CSC1_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_P1;

/* define the union U_G3_CSC1_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_P2;

/* define the union U_G3_CSC1_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_P3;

/* define the union U_G3_CSC1_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_G3_CSC1_P4;

/* define the union U_GP0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_UPD;

/* define the union U_GP0_IRESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int iw : 16; /* [15..0]  */
        unsigned int ih : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_IRESO;

/* define the union U_GP0_LBOX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_en : 1;     /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_LBOX_CTRL;

/* define the union U_GP0_GALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int galpha : 8;      /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_GALPHA;

/* define the union U_GP0_DFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xfpos : 12; /* [11..0]  */
        unsigned int disp_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_DFPOS;

/* define the union U_GP0_DLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int disp_xlpos : 12; /* [11..0]  */
        unsigned int disp_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_DLPOS;

/* define the union U_GP0_VFPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xfpos : 12; /* [11..0]  */
        unsigned int video_yfpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;   /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_VFPOS;

/* define the union U_GP0_VLPOS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int video_xlpos : 12; /* [11..0]  */
        unsigned int video_ylpos : 12; /* [23..12]  */
        unsigned int reserved_0 : 8;   /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_VLPOS;

/* define the union U_GP0_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_cr : 10;    /* [9..0]  */
        unsigned int vbk_cb : 10;    /* [19..10]  */
        unsigned int vbk_y : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_BK;

/* define the union U_GP0_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbk_alpha : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_ALPHA;

/* define the union U_GP0_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_MUTE_BK;

/* define the union U_GP0_CSC_IDC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc0 : 11;   /* [10..0]  */
        unsigned int cscidc1 : 11;   /* [21..11]  */
        unsigned int csc_en : 1;     /* [22]  */
        unsigned int reserved_0 : 9; /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_IDC;

/* define the union U_GP0_CSC_ODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscodc0 : 11;      /* [10..0]  */
        unsigned int cscodc1 : 11;      /* [21..11]  */
        unsigned int csc_sign_mode : 1; /* [22]  */
        unsigned int reserved_0 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_ODC;

/* define the union U_GP0_CSC_IODC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscidc2 : 11;    /* [10..0]  */
        unsigned int cscodc2 : 11;    /* [21..11]  */
        unsigned int reserved_0 : 10; /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_IODC;

/* define the union U_GP0_CSC_P0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp00 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp01 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_P0;

/* define the union U_GP0_CSC_P1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp02 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp10 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_P1;

/* define the union U_GP0_CSC_P2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp11 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp12 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_P2;

/* define the union U_GP0_CSC_P3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp20 : 15;    /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int cscp21 : 15;    /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_P3;

/* define the union U_GP0_CSC_P4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cscp22 : 15;     /* [14..0]  */
        unsigned int reserved_0 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GP0_CSC_P4;

/* define the union U_WBC_G0_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int auto_stop_en : 1;  /* [10]  */
        unsigned int reserved_0 : 15;   /* [25..11]  */
        unsigned int format_out : 2;    /* [27..26]  */
        unsigned int reserved_1 : 3;    /* [30..28]  */
        unsigned int wbc_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_CTRL;

/* define the union U_WBC_G0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_UPD;

/* define the union U_WBC_G0_CMP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cmp_lossy_en : 1; /* [0]  */
        unsigned int reserved_0 : 3;   /* [3..1]  */
        unsigned int cmp_drr : 4;      /* [7..4]  */
        unsigned int reserved_1 : 23;  /* [30..8]  */
        unsigned int cmp_en : 1;       /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_CMP;

/* define the union U_WBC_G0_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbcstride : 16;  /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_STRIDE;

/* define the union U_WBC_G0_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12;        /* [11..0]  */
        unsigned int oh : 12;        /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_ORESO;

/* define the union U_WBC_G0_FCROP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wfcrop : 12;    /* [11..0]  */
        unsigned int hfcrop : 12;    /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_FCROP;

/* define the union U_WBC_G0_LCROP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlcrop : 12;    /* [11..0]  */
        unsigned int hlcrop : 12;    /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_G0_LCROP;

/* define the union U_WBC_GP0_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10;  /* [9..0]  */
        unsigned int auto_stop_en : 1;   /* [10]  */
        unsigned int reserved_0 : 1;     /* [11]  */
        unsigned int wbc_vtthd_mode : 1; /* [12]  */
        unsigned int reserved_1 : 5;     /* [17..13]  */
        unsigned int three_d_mode : 2;   /* [19..18]  */
        unsigned int reserved_2 : 3;     /* [22..20]  */
        unsigned int flip_en : 1;        /* [23]  */
        unsigned int format_out : 4;     /* [27..24]  */
        unsigned int mode_out : 2;       /* [29..28]  */
        unsigned int reserved_3 : 1;     /* [30]  */
        unsigned int wbc_en : 1;         /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_CTRL;

/* define the union U_WBC_GP0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_UPD;

/* define the union U_WBC_GP0_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbclstride : 16; /* [15..0]  */
        unsigned int wbccstride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_STRIDE;

/* define the union U_WBC_GP0_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12;        /* [11..0]  */
        unsigned int oh : 12;        /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_ORESO;

/* define the union U_WBC_GP0_FCROP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wfcrop : 12;    /* [11..0]  */
        unsigned int hfcrop : 12;    /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_FCROP;

/* define the union U_WBC_GP0_LCROP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlcrop : 12;    /* [11..0]  */
        unsigned int hlcrop : 12;    /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_LCROP;

/* define the union U_WBC_GP0_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29;  /* [28..0]  */
        unsigned int dither_round : 1; /* [29]  */
        unsigned int dither_mode : 1;  /* [30]  */
        unsigned int dither_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_DITHER_CTRL;

/* define the union U_WBC_GP0_DITHER_COEF0 */
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
} U_WBC_GP0_DITHER_COEF0;

/* define the union U_WBC_GP0_DITHER_COEF1 */
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
} U_WBC_GP0_DITHER_COEF1;

/* define the union U_WBC_GP0_HPZME */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29;  /* [28..0]  */
        unsigned int hpzme_mode : 1;   /* [29]  */
        unsigned int hpzme_mid_en : 1; /* [30]  */
        unsigned int hpzme_en : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_GP0_HPZME;

/* define the union U_WBC_ME_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 10;   /* [19..10]  */
        unsigned int ofl_master : 1;    /* [20]  */
        unsigned int reserved_1 : 2;    /* [22..21]  */
        unsigned int mad_data_mode : 1; /* [23]  */
        unsigned int format_out : 4;    /* [27..24]  */
        unsigned int reserved_2 : 1;    /* [28]  */
        unsigned int c_wbc_en : 1;      /* [29]  */
        unsigned int reserved_3 : 1;    /* [30]  */
        unsigned int wbc_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_CTRL;

/* define the union U_WBC_ME_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_UPD;

/* define the union U_WBC_ME_WLEN_SEL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlen_sel : 2;    /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_WLEN_SEL;

/* define the union U_WBC_ME_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbclstride : 16; /* [15..0]  */
        unsigned int wbccstride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_STRIDE;

/* define the union U_WBC_ME_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12;        /* [11..0]  */
        unsigned int oh : 12;        /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ORESO;

/* define the union U_WBC_ME_SMMU_BYPASS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_bypass : 1;    /* [0]  */
        unsigned int c_bypass : 1;    /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_SMMU_BYPASS;

/* define the union U_WBC_ME_PARAUP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_hlcoef_upd : 1; /* [0]  */
        unsigned int wbc_hccoef_upd : 1; /* [1]  */
        unsigned int wbc_vlcoef_upd : 1; /* [2]  */
        unsigned int wbc_vccoef_upd : 1; /* [3]  */
        unsigned int reserved_0 : 28;    /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_PARAUP;

/* define the union U_WBC_ME_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29;  /* [28..0]  */
        unsigned int dither_round : 1; /* [29]  */
        unsigned int dither_mode : 1;  /* [30]  */
        unsigned int dither_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_DITHER_CTRL;

/* define the union U_WBC_ME_DITHER_COEF0 */
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
} U_WBC_ME_DITHER_COEF0;

/* define the union U_WBC_ME_DITHER_COEF1 */
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
} U_WBC_ME_DITHER_COEF1;

/* define the union U_WBC_ME_ZME_HSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 24;    /* [23..0]  */
        unsigned int hfir_order : 1; /* [24]  */
        unsigned int hchfir_en : 1;  /* [25]  */
        unsigned int hlfir_en : 1;   /* [26]  */
        unsigned int reserved_0 : 1; /* [27]  */
        unsigned int hchmid_en : 1;  /* [28]  */
        unsigned int hlmid_en : 1;   /* [29]  */
        unsigned int hchmsc_en : 1;  /* [30]  */
        unsigned int hlmsc_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_HSP;

/* define the union U_WBC_ME_ZME_HLOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hor_loffset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;   /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_HLOFFSET;

/* define the union U_WBC_ME_ZME_HCOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hor_coffset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;   /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_HCOFFSET;

/* define the union U_WBC_ME_ZME_VSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 19; /* [18..0]  */
        unsigned int zme_in_fmt : 2;  /* [20..19]  */
        unsigned int zme_out_fmt : 2; /* [22..21]  */
        unsigned int vchfir_en : 1;   /* [23]  */
        unsigned int vlfir_en : 1;    /* [24]  */
        unsigned int reserved_1 : 3;  /* [27..25]  */
        unsigned int vchmid_en : 1;   /* [28]  */
        unsigned int vlmid_en : 1;    /* [29]  */
        unsigned int vchmsc_en : 1;   /* [30]  */
        unsigned int vlmsc_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_VSP;

/* define the union U_WBC_ME_ZME_VSR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 16;     /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_VSR;

/* define the union U_WBC_ME_ZME_VOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int vluma_offset : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_VOFFSET;

/* define the union U_WBC_ME_ZME_VBOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int vbluma_offset : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_ME_ZME_VBOFFSET;

/* define the union U_WBC_FI_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 3;    /* [12..10]  */
        unsigned int addr_mode : 1;     /* [13]  */
        unsigned int fsize_mode : 1;    /* [14]  */
        unsigned int tnr_nrds_en : 1;   /* [15]  */
        unsigned int reserved_1 : 4;    /* [19..16]  */
        unsigned int ofl_master : 1;    /* [20]  */
        unsigned int data_width : 1;    /* [21]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int format_out : 4;    /* [27..24]  */
        unsigned int reserved_3 : 2;    /* [29..28]  */
        unsigned int cmp_en : 1;        /* [30]  */
        unsigned int wbc_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CTRL;

/* define the union U_WBC_FI_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_UPD;

/* define the union U_WBC_FI_WLEN_SEL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wlen_sel : 2;    /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_WLEN_SEL;

/* define the union U_WBC_FI_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbclstride : 16; /* [15..0]  */
        unsigned int wbccstride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_STRIDE;

/* define the union U_WBC_FI_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12;        /* [11..0]  */
        unsigned int oh : 12;        /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_ORESO;

/* define the union U_WBC_FI_SMMU_BYPASS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_bypass : 1;    /* [0]  */
        unsigned int c_bypass : 1;    /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_SMMU_BYPASS;

/* define the union U_WBC_FI_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size : 23; /* [22..0]  */
        unsigned int reserved_0 : 9;  /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_FRAME_SIZE;

/* define the union U_WBC_FI_HCDS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 29; /* [28..0]  */
        unsigned int hchfir_en : 1;   /* [29]  */
        unsigned int hchmid_en : 1;   /* [30]  */
        unsigned int hcds_en : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_HCDS;

/* define the union U_WBC_FI_HCDS_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10;     /* [9..0]  */
        unsigned int coef1 : 10;     /* [19..10]  */
        unsigned int coef2 : 10;     /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_HCDS_COEF0;

/* define the union U_WBC_FI_HCDS_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef3 : 10;      /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_HCDS_COEF1;

/* define the union U_WBC_FI_CMP_MB */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits : 10;    /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_MB;

/* define the union U_WBC_FI_CMP_MAX_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int min_bits_cnt : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;    /* [15..10]  */
        unsigned int max_bits_cnt : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;    /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_MAX_MIN;

/* define the union U_WBC_FI_CMP_ADJ_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int adj_sad_thr : 12;     /* [11..0]  */
        unsigned int reserved_0 : 4;       /* [15..12]  */
        unsigned int adj_sad_bit_thr : 8;  /* [23..16]  */
        unsigned int adj_spec_bit_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_ADJ_THR;

/* define the union U_WBC_FI_CMP_BIG_GRAD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int big_grad_thr : 7;     /* [6..0]  */
        unsigned int reserved_0 : 1;       /* [7]  */
        unsigned int big_grad_num_thr : 5; /* [12..8]  */
        unsigned int reserved_1 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_BIG_GRAD;

/* define the union U_WBC_FI_CMP_BLK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_thr : 6;     /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int blk_comp_thr : 3; /* [10..8]  */
        unsigned int reserved_1 : 21;  /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_BLK;

/* define the union U_WBC_FI_CMP_GRAPHIC_JUDGE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int graphic_en : 1;     /* [0]  */
        unsigned int reserved_0 : 15;    /* [15..1]  */
        unsigned int video_sad_thr : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_GRAPHIC_JUDGE;

/* define the union U_WBC_FI_CMP_RC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int sadbits_ngain : 3; /* [2..0]  */
        unsigned int reserved_0 : 5;    /* [7..3]  */
        unsigned int rc_smth_gain : 3;  /* [10..8]  */
        unsigned int reserved_1 : 5;    /* [15..11]  */
        unsigned int max_trow_bits : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;   /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_RC;

/* define the union U_WBC_FI_CMP_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size : 21; /* [20..0]  */
        unsigned int reserved_0 : 11; /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_FI_CMP_FRAME_SIZE;

/* define the union U_WBC_CMP_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int is_lossless : 1; /* [0]  */
        unsigned int cmp_mode : 1;    /* [1]  */
        unsigned int dw_mode : 1;     /* [2]  */
        unsigned int sep_cmp_en : 1;  /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_GLB_INFO;

/* define the union U_WBC_CMP_FRAMESIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;    /* [15..13]  */
        unsigned int frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_FRAMESIZE;

/* define the union U_WBC_CMP_RC_CFG0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits_y : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6;     /* [15..10]  */
        unsigned int min_mb_bits_y : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;     /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG0;

/* define the union U_WBC_CMP_RC_CFG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_qp_y : 4;       /* [3..0]  */
        unsigned int reserved_0 : 4;     /* [7..4]  */
        unsigned int sad_bits_ngain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;     /* [15..12]  */
        unsigned int rc_smth_ngain : 3;  /* [18..16]  */
        unsigned int reserved_2 : 5;     /* [23..19]  */
        unsigned int max_trow_bits : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG2;

/* define the union U_WBC_CMP_RC_CFG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9;  /* [15..7]  */
        unsigned int min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9;  /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG3;

/* define the union U_WBC_CMP_RC_CFG4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_thr : 7;      /* [6..0]  */
        unsigned int reserved_0 : 1;    /* [7]  */
        unsigned int still_thr : 7;     /* [14..8]  */
        unsigned int reserved_1 : 1;    /* [15]  */
        unsigned int big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6;    /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG4;

/* define the union U_WBC_CMP_RC_CFG5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_pix_num_thr : 6;  /* [5..0]  */
        unsigned int reserved_0 : 2;        /* [7..6]  */
        unsigned int still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;        /* [15..14]  */
        unsigned int noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;       /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG5;

/* define the union U_WBC_CMP_RC_CFG6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int noise_sad : 7;    /* [6..0]  */
        unsigned int reserved_0 : 9;   /* [15..7]  */
        unsigned int pix_diff_thr : 9; /* [24..16]  */
        unsigned int reserved_1 : 7;   /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG6;

/* define the union U_WBC_CMP_RC_CFG7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;      /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG7;

/* define the union U_WBC_CMP_RC_CFG8 */
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
} U_WBC_CMP_RC_CFG8;

/* define the union U_WBC_CMP_RC_CFG10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int est_err_gain : 5;         /* [4..0]  */
        unsigned int reserved_0 : 11;          /* [15..5]  */
        unsigned int max_est_err_level : 9;    /* [24..16]  */
        unsigned int max_vbv_buf_loss_thr : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_RC_CFG10;

/* define the union U_WBC_CMP_OUTSIZE0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size0_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;      /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_OUTSIZE0;

/* define the union U_WBC_CMP_MAX_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size1_reg : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_MAX_ROW;

/* define the union U_WBC_BMP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 10;   /* [19..10]  */
        unsigned int ofl_master : 1;    /* [20]  */
        unsigned int data_width : 1;    /* [21]  */
        unsigned int reserved_1 : 2;    /* [23..22]  */
        unsigned int format_out : 4;    /* [27..24]  */
        unsigned int reserved_2 : 3;    /* [30..28]  */
        unsigned int wbc_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_BMP_CTRL;

/* define the union U_WBC_BMP_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_BMP_UPD;

/* define the union U_WBC_BMP_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12;        /* [11..0]  */
        unsigned int oh : 12;        /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_BMP_ORESO;

/* define the union U_WBC_BMP_SUM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bmp_sum : 25;   /* [24..0]  */
        unsigned int reserved_0 : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_BMP_SUM;

/* define the union U_WBC_DHD0_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int p2i_en : 1;         /* [0]  */
        unsigned int root_path : 2;      /* [2..1]  */
        unsigned int reserved_0 : 19;    /* [21..3]  */
        unsigned int mode_out : 2;       /* [23..22]  */
        unsigned int three_d_mode : 2;   /* [25..24]  */
        unsigned int auto_stop_en : 1;   /* [26]  */
        unsigned int wbc_vtthd_mode : 1; /* [27]  */
        unsigned int rupd_field : 1;     /* [28]  */
        unsigned int rgup_mode : 1;      /* [29]  */
        unsigned int nosec_flag : 1;     /* [30]  */
        unsigned int wbc_en : 1;         /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_DHD0_CTRL;

/* define the union U_WBC_DHD0_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_DHD0_UPD;

/* define the union U_WBC_DHD0_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 16; /* [15..0]  */
        unsigned int oh : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_DHD0_ORESO;

/* define the union U_WD_HPZME_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_en : 1;     /* [0]  */
        unsigned int hfir_mode : 2;   /* [2..1]  */
        unsigned int mid_en : 1;      /* [3]  */
        unsigned int ck_gt_en : 1;    /* [4]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HPZME_CTRL;

/* define the union U_WD_HPZMECOEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6;  /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HPZMECOEF01;

/* define the union U_WD_HPZMECOEF23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6;  /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HPZMECOEF23;

/* define the union U_WD_HPZMECOEF45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6;  /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HPZMECOEF45;

/* define the union U_WD_HPZMECOEF67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6;  /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HPZMECOEF67;

/* define the union U_WD_HCDS_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_en : 1;     /* [0]  */
        unsigned int hfir_mode : 2;   /* [2..1]  */
        unsigned int mid_en : 1;      /* [3]  */
        unsigned int ck_gt_en : 1;    /* [4]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HCDS_CTRL;

/* define the union U_WD_HCDSCOEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef0 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef1 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HCDSCOEF01;

/* define the union U_WD_HCDSCOEF23 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int coef2 : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6; /* [15..10]  */
        unsigned int coef3 : 10;     /* [25..16]  */
        unsigned int reserved_1 : 6; /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HCDSCOEF23;

/* define the union U_WD_HCDSCOEF45 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6;  /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HCDSCOEF45;

/* define the union U_WD_HCDSCOEF67 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 10; /* [9..0]  */
        unsigned int reserved_1 : 6;  /* [15..10]  */
        unsigned int reserved_2 : 10; /* [25..16]  */
        unsigned int reserved_3 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_HCDSCOEF67;

/* define the union U_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_tap_mode : 2;     /* [1..0]  */
        unsigned int dither_domain_mode : 1;  /* [2]  */
        unsigned int dither_round : 1;        /* [3]  */
        unsigned int dither_mode : 1;         /* [4]  */
        unsigned int dither_en : 1;           /* [5]  */
        unsigned int dither_round_unlim : 1;  /* [6]  */
        unsigned int i_data_width_dither : 3; /* [9..7]  */
        unsigned int o_data_width_dither : 3; /* [12..10]  */
        unsigned int reserved_0 : 19;         /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_CTRL;

/* define the union U_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_Y0;

/* define the union U_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_U0;

/* define the union U_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_V0;

/* define the union U_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_W0;

/* define the union U_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_Y1;

/* define the union U_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_U1;

/* define the union U_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_V1;

/* define the union U_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_W1;

/* define the union U_DITHER_SED_Y2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_Y2;

/* define the union U_DITHER_SED_U2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_U2;

/* define the union U_DITHER_SED_V2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_V2;

/* define the union U_DITHER_SED_W2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_W2;

/* define the union U_DITHER_SED_Y3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_Y3;

/* define the union U_DITHER_SED_U3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_U3;

/* define the union U_DITHER_SED_V3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_V3;

/* define the union U_DITHER_SED_W3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_SED_W3;

/* define the union U_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_thr_min : 16; /* [15..0]  */
        unsigned int dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DITHER_THR;

/* define the union U_WD_ZME_HINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_width : 16;    /* [15..0]  */
        unsigned int hzme_ck_gt_en : 1; /* [16]  */
        unsigned int reserved_0 : 15;   /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HINFO;

/* define the union U_WD_ZME_HSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 24; /* [23..0]  */
        unsigned int hfir_order : 1;  /* [24]  */
        unsigned int chfir_mode : 1;  /* [25]  */
        unsigned int lhfir_mode : 1;  /* [26]  */
        unsigned int non_lnr_en : 1;  /* [27]  */
        unsigned int chmid_en : 1;    /* [28]  */
        unsigned int lhmid_en : 1;    /* [29]  */
        unsigned int chfir_en : 1;    /* [30]  */
        unsigned int lhfir_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HSP;

/* define the union U_WD_ZME_HLOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lhfir_offset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HLOFFSET;

/* define the union U_WD_ZME_HCOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chfir_offset : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HCOFFSET;

/* define the union U_WD_ZME_HCOEF_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_hf_cren : 1; /* [0]  */
        unsigned int apb_vhd_hf_lren : 1; /* [1]  */
        unsigned int reserved_0 : 30;     /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HCOEF_REN;

/* define the union U_WD_ZME_HCOEF_RDATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_hcoef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24;         /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HCOEF_RDATA;

/* define the union U_WD_ZME_HDRAW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hdraw_mode : 2;  /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HDRAW;

/* define the union U_WD_ZME_HRATIO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hratio : 27;    /* [26..0]  */
        unsigned int reserved_0 : 5; /* [31..27]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_HRATIO;

/* define the union U_WD_ZME_VINFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int out_height : 16;   /* [15..0]  */
        unsigned int out_fmt : 2;       /* [17..16]  */
        unsigned int out_pro : 1;       /* [18]  */
        unsigned int vzme_ck_gt_en : 1; /* [19]  */
        unsigned int reserved_0 : 12;   /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VINFO;

/* define the union U_WD_ZME_VSP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16;  /* [15..0]  */
        unsigned int graphdet_en : 1;  /* [16]  */
        unsigned int reserved_1 : 8;   /* [24..17]  */
        unsigned int cvfir_mode : 1;   /* [25]  */
        unsigned int lvfir_mode : 1;   /* [26]  */
        unsigned int vfir_1tap_en : 1; /* [27]  */
        unsigned int cvmid_en : 1;     /* [28]  */
        unsigned int lvmid_en : 1;     /* [29]  */
        unsigned int cvfir_en : 1;     /* [30]  */
        unsigned int lvfir_en : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VSP;

/* define the union U_WD_ZME_VOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vchroma_offset : 16; /* [15..0]  */
        unsigned int vluma_offset : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VOFFSET;

/* define the union U_WD_ZME_VBOFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbchroma_offset : 16; /* [15..0]  */
        unsigned int vbluma_offset : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VBOFFSET;

/* define the union U_WD_ZME_VCOEF_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_vf_cren : 1; /* [0]  */
        unsigned int apb_vhd_vf_lren : 1; /* [1]  */
        unsigned int reserved_0 : 30;     /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VCOEF_REN;

/* define the union U_WD_ZME_VCOEF_RDATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int apb_vhd_vcoef_raddr : 8; /* [7..0]  */
        unsigned int reserved_0 : 24;         /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VCOEF_RDATA;

/* define the union U_WD_ZME_VDRAW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vdraw_mode : 2;  /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VDRAW;

/* define the union U_WD_ZME_VRATIO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vratio : 19;     /* [18..0]  */
        unsigned int reserved_0 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WD_ZME_VRATIO;

/* define the union U_DHD0_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;          /* [0]  */
        unsigned int disp_mode : 3;      /* [3..1]  */
        unsigned int iop : 1;            /* [4]  */
        unsigned int intf_ivs : 1;       /* [5]  */
        unsigned int intf_ihs : 1;       /* [6]  */
        unsigned int intf_idv : 1;       /* [7]  */
        unsigned int reserved_0 : 1;     /* [8]  */
        unsigned int hdmi420c_sel : 1;   /* [9]  */
        unsigned int hdmi420_en : 1;     /* [10]  */
        unsigned int uf_offline_en : 1;  /* [11]  */
        unsigned int reserved_1 : 2;     /* [13..12]  */
        unsigned int hdmi_mode : 1;      /* [14]  */
        unsigned int twochn_debug : 1;   /* [15]  */
        unsigned int twochn_en : 1;      /* [16]  */
        unsigned int reserved_2 : 1;     /* [17]  */
        unsigned int cbar_mode : 1;      /* [18]  */
        unsigned int sin_en : 1;         /* [19]  */
        unsigned int fpga_lmt_width : 7; /* [26..20]  */
        unsigned int fpga_lmt_en : 1;    /* [27]  */
        unsigned int p2i_en : 1;         /* [28]  */
        unsigned int cbar_sel : 1;       /* [29]  */
        unsigned int cbar_en : 1;        /* [30]  */
        unsigned int intf_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_CTRL;

/* define the union U_DHD0_VSYNC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vact : 16; /* [15..0]  */
        unsigned int vbb : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_VSYNC1;

/* define the union U_DHD0_VSYNC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vfb : 16;        /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_VSYNC2;

/* define the union U_DHD0_HSYNC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hact : 16; /* [15..0]  */
        unsigned int hbb : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_HSYNC1;

/* define the union U_DHD0_HSYNC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfb : 16;  /* [15..0]  */
        unsigned int hmid : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_HSYNC2;

/* define the union U_DHD0_VPLUS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bvact : 16; /* [15..0]  */
        unsigned int bvbb : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_VPLUS1;

/* define the union U_DHD0_VPLUS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bvfb : 16;       /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_VPLUS2;

/* define the union U_DHD0_PWR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hpw : 16;        /* [15..0]  */
        unsigned int vpw : 8;         /* [23..16]  */
        unsigned int reserved_0 : 3;  /* [26..24]  */
        unsigned int multichn_en : 2; /* [28..27]  */
        unsigned int reserved_1 : 3;  /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_PWR;

/* define the union U_DHD0_VTTHD3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vtmgthd3 : 13;  /* [12..0]  */
        unsigned int reserved_0 : 2; /* [14..13]  */
        unsigned int thd3_mode : 1;  /* [15]  */
        unsigned int vtmgthd4 : 13;  /* [28..16]  */
        unsigned int reserved_1 : 2; /* [30..29]  */
        unsigned int thd4_mode : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_VTTHD3;

/* define the union U_DHD0_VTTHD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vtmgthd1 : 13;  /* [12..0]  */
        unsigned int reserved_0 : 2; /* [14..13]  */
        unsigned int thd1_mode : 1;  /* [15]  */
        unsigned int vtmgthd2 : 13;  /* [28..16]  */
        unsigned int reserved_1 : 2; /* [30..29]  */
        unsigned int thd2_mode : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_VTTHD;

/* define the union U_DHD0_PARATHD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_thd : 8;    /* [7..0]  */
        unsigned int reserved_0 : 23; /* [30..8]  */
        unsigned int dfs_en : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_PARATHD;

/* define the union U_DHD0_PRECHARGE_THD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tcon_precharge_thd : 17; /* [16..0]  */
        unsigned int reserved_0 : 15;         /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_PRECHARGE_THD;

/* define the union U_DHD0_START_POS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int start_pos : 8;        /* [7..0]  */
        unsigned int timing_start_pos : 8; /* [15..8]  */
        unsigned int fi_start_pos : 4;     /* [19..16]  */
        unsigned int req_start_pos : 12;   /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_START_POS;

/* define the union U_DHD0_START_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_start_pos1 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_START_POS1;

/* define the union U_DHD0_PARAUP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int paraup_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_PARAUP;

/* define the union U_DHD0_SYNC_INV */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lcd_dv_inv : 1;  /* [0]  */
        unsigned int lcd_hs_inv : 1;  /* [1]  */
        unsigned int lcd_vs_inv : 1;  /* [2]  */
        unsigned int reserved_0 : 1;  /* [3]  */
        unsigned int vga_dv_inv : 1;  /* [4]  */
        unsigned int vga_hs_inv : 1;  /* [5]  */
        unsigned int vga_vs_inv : 1;  /* [6]  */
        unsigned int reserved_1 : 1;  /* [7]  */
        unsigned int hdmi_dv_inv : 1; /* [8]  */
        unsigned int hdmi_hs_inv : 1; /* [9]  */
        unsigned int hdmi_vs_inv : 1; /* [10]  */
        unsigned int hdmi_f_inv : 1;  /* [11]  */
        unsigned int date_dv_inv : 1; /* [12]  */
        unsigned int date_hs_inv : 1; /* [13]  */
        unsigned int date_vs_inv : 1; /* [14]  */
        unsigned int date_f_inv : 1;  /* [15]  */
        unsigned int reserved_2 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_SYNC_INV;

/* define the union U_DHD0_CLK_DV_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int intf_clk_mux : 1;        /* [0]  */
        unsigned int intf_dv_mux : 1;         /* [1]  */
        unsigned int no_active_area_pos : 16; /* [17..2]  */
        unsigned int reserved_0 : 14;         /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_CLK_DV_CTRL;

/* define the union U_DHD0_RGB_FIX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int fix_b : 10;      /* [9..0]  */
        unsigned int fix_g : 10;      /* [19..10]  */
        unsigned int fix_r : 10;      /* [29..20]  */
        unsigned int rgb_fix_mux : 1; /* [30]  */
        unsigned int reserved_0 : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_RGB_FIX_CTRL;

/* define the union U_DHD0_LOCKCFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int measure_en : 1;     /* [0]  */
        unsigned int lock_cnt_en : 1;    /* [1]  */
        unsigned int vdp_measure_en : 1; /* [2]  */
        unsigned int reserved_0 : 29;    /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_LOCKCFG;

/* define the union U_DHD0_INTF_CHKSUM_HIGH1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int y0_sum_high : 8; /* [7..0]  */
        unsigned int g0_sum_high : 8; /* [15..8]  */
        unsigned int b0_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_INTF_CHKSUM_HIGH1;

/* define the union U_DHD0_INTF_CHKSUM_HIGH2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int y1_sum_high : 8; /* [7..0]  */
        unsigned int g1_sum_high : 8; /* [15..8]  */
        unsigned int b1_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_INTF_CHKSUM_HIGH2;

/* define the union U_DHD0_STATE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vback_blank : 1;  /* [0]  */
        unsigned int vblank : 1;       /* [1]  */
        unsigned int bottom_field : 1; /* [2]  */
        unsigned int vcnt : 13;        /* [15..3]  */
        unsigned int count_int : 8;    /* [23..16]  */
        unsigned int dhd_even : 1;     /* [24]  */
        unsigned int reserved_0 : 7;   /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_STATE;

/* define the union U_DHD0_UF_STATE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ud_first_cnt : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;    /* [15..13]  */
        unsigned int start_pos : 8;     /* [23..16]  */
        unsigned int reserved_1 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD0_UF_STATE;

/* define the union U_VO_MUX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mipi_sel : 4;    /* [3..0]  */
        unsigned int lcd_sel : 4;     /* [7..4]  */
        unsigned int bt_sel : 4;      /* [11..8]  */
        unsigned int reserved_0 : 16; /* [27..12]  */
        unsigned int digital_sel : 4; /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VO_MUX;

/* define the union U_VO_MUX_SYNC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int sync_dv : 1;        /* [0]  */
        unsigned int sync_hsync : 1;     /* [1]  */
        unsigned int sync_vsync : 1;     /* [2]  */
        unsigned int sync_field : 1;     /* [3]  */
        unsigned int reserved_0 : 27;    /* [30..4]  */
        unsigned int sync_test_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VO_MUX_SYNC;

/* define the union U_VO_MUX_DATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vomux_data : 30; /* [29..0]  */
        unsigned int reserved_0 : 2;  /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VO_MUX_DATA;

/* define the union U_INTF0_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_tap_mode : 2;     /* [1..0]  */
        unsigned int dither_domain_mode : 1;  /* [2]  */
        unsigned int dither_round : 1;        /* [3]  */
        unsigned int dither_mode : 1;         /* [4]  */
        unsigned int dither_en : 1;           /* [5]  */
        unsigned int dither_round_unlim : 1;  /* [6]  */
        unsigned int i_data_width_dither : 3; /* [9..7]  */
        unsigned int o_data_width_dither : 3; /* [12..10]  */
        unsigned int reserved_0 : 19;         /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_CTRL;

/* define the union U_INTF0_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_Y0;

/* define the union U_INTF0_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_U0;

/* define the union U_INTF0_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_V0;

/* define the union U_INTF0_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_W0;

/* define the union U_INTF0_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_Y1;

/* define the union U_INTF0_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_U1;

/* define the union U_INTF0_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_V1;

/* define the union U_INTF0_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_W1;

/* define the union U_INTF0_DITHER_SED_Y2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_Y2;

/* define the union U_INTF0_DITHER_SED_U2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_U2;

/* define the union U_INTF0_DITHER_SED_V2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_V2;

/* define the union U_INTF0_DITHER_SED_W2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_W2;

/* define the union U_INTF0_DITHER_SED_Y3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_Y3;

/* define the union U_INTF0_DITHER_SED_U3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_U3;

/* define the union U_INTF0_DITHER_SED_V3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_V3;

/* define the union U_INTF0_DITHER_SED_W3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_SED_W3;

/* define the union U_INTF0_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_thr_min : 16; /* [15..0]  */
        unsigned int dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF0_DITHER_THR;

/* define the union U_INTF_HDMI_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int intf_422_en : 1;   /* [0]  */
        unsigned int intf_420_en : 1;   /* [1]  */
        unsigned int intf_420_mode : 2; /* [3..2]  */
        unsigned int hdmi_mode : 2;     /* [5..4]  */
        unsigned int reserved_0 : 26;   /* [31..6]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_HDMI_CTRL;

/* define the union U_INTF_HDMI_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_HDMI_UPD;

/* define the union U_INTF_HDMI_SYNC_INV */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dv_inv : 1;      /* [0]  */
        unsigned int hs_inv : 1;      /* [1]  */
        unsigned int vs_inv : 1;      /* [2]  */
        unsigned int f_inv : 1;       /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_HDMI_SYNC_INV;

/* define the union U_HDMI_INTF_CHKSUM_HIGH */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int y0_sum_high : 8; /* [7..0]  */
        unsigned int g0_sum_high : 8; /* [15..8]  */
        unsigned int b0_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HDMI_INTF_CHKSUM_HIGH;

/* define the union U_HDMI_INTF1_CHKSUM_HIGH */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int y1_sum_high : 8; /* [7..0]  */
        unsigned int g1_sum_high : 8; /* [15..8]  */
        unsigned int b1_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HDMI_INTF1_CHKSUM_HIGH;

/* define the union U_HDMI_HFIR_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef0 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;  /* [15..10]  */
        unsigned int hfir_coef1 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HDMI_HFIR_COEF0;

/* define the union U_HDMI_HFIR_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef2 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;  /* [15..10]  */
        unsigned int hfir_coef3 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HDMI_HFIR_COEF1;

/* define the union U_HDMI_HFIR_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef4 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;  /* [15..10]  */
        unsigned int hfir_coef5 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HDMI_HFIR_COEF2;

/* define the union U_HDMI_HFIR_COEF3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef6 : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HDMI_HFIR_COEF3;

/* define the union U_INTF_MIPI_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int intf_422_en : 1;   /* [0]  */
        unsigned int intf_420_en : 1;   /* [1]  */
        unsigned int intf_420_mode : 2; /* [3..2]  */
        unsigned int reserved_0 : 28;   /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_MIPI_CTRL;

/* define the union U_INTF_MIPI_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_MIPI_UPD;

/* define the union U_INTF_MIPI_SYNC_INV */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dv_inv : 1;      /* [0]  */
        unsigned int hs_inv : 1;      /* [1]  */
        unsigned int vs_inv : 1;      /* [2]  */
        unsigned int f_inv : 1;       /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_MIPI_SYNC_INV;

/* define the union U_MIPI_INTF_CHKSUM_HIGH */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int b0_sum_high : 8; /* [7..0]  */
        unsigned int g0_sum_high : 8; /* [15..8]  */
        unsigned int r0_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIPI_INTF_CHKSUM_HIGH;

/* define the union U_MIPI_INTF1_CHKSUM_HIGH */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int b1_sum_high : 8; /* [7..0]  */
        unsigned int g1_sum_high : 8; /* [15..8]  */
        unsigned int r1_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIPI_INTF1_CHKSUM_HIGH;

/* define the union U_MIPI_HFIR_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef0 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;  /* [15..10]  */
        unsigned int hfir_coef1 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIPI_HFIR_COEF0;

/* define the union U_MIPI_HFIR_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef2 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;  /* [15..10]  */
        unsigned int hfir_coef3 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIPI_HFIR_COEF1;

/* define the union U_MIPI_HFIR_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef4 : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;  /* [15..10]  */
        unsigned int hfir_coef5 : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;  /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIPI_HFIR_COEF2;

/* define the union U_MIPI_HFIR_COEF3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfir_coef6 : 10; /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MIPI_HFIR_COEF3;

/* define the union U_INTF_BT_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 24;        /* [23..0]  */
        unsigned int yc_mode : 1;            /* [24]  */
        unsigned int lcd_parallel_mode : 1;  /* [25]  */
        unsigned int lcd_data_inv : 1;       /* [26]  */
        unsigned int lcd_parallel_order : 1; /* [27]  */
        unsigned int lcd_serial_perd : 1;    /* [28]  */
        unsigned int lcd_serial_mode : 1;    /* [29]  */
        unsigned int dfir_en : 1;            /* [30]  */
        unsigned int hdmi_mode : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_BT_CTRL;

/* define the union U_INTF_BT_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_BT_UPD;

/* define the union U_INTF_BT_SYNC_INV */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dv_inv : 1;      /* [0]  */
        unsigned int hs_inv : 1;      /* [1]  */
        unsigned int vs_inv : 1;      /* [2]  */
        unsigned int f_inv : 1;       /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_BT_SYNC_INV;

/* define the union U_BT_CLIP0_L */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int clip_cl0 : 10;  /* [9..0]  */
        unsigned int clip_cl1 : 10;  /* [19..10]  */
        unsigned int clip_cl2 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 1; /* [30]  */
        unsigned int clip_en : 1;    /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_CLIP0_L;

/* define the union U_BT_CLIP0_H */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int clip_ch0 : 10;  /* [9..0]  */
        unsigned int clip_ch1 : 10;  /* [19..10]  */
        unsigned int clip_ch2 : 10;  /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_CLIP0_H;

/* define the union U_BT_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_tap_mode : 2;     /* [1..0]  */
        unsigned int dither_domain_mode : 1;  /* [2]  */
        unsigned int dither_round : 1;        /* [3]  */
        unsigned int dither_mode : 1;         /* [4]  */
        unsigned int dither_en : 1;           /* [5]  */
        unsigned int dither_round_unlim : 1;  /* [6]  */
        unsigned int i_data_width_dither : 3; /* [9..7]  */
        unsigned int o_data_width_dither : 3; /* [12..10]  */
        unsigned int reserved_0 : 19;         /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_CTRL;

/* define the union U_BT_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_Y0;

/* define the union U_BT_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_U0;

/* define the union U_BT_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_V0;

/* define the union U_BT_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_W0;

/* define the union U_BT_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_Y1;

/* define the union U_BT_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_U1;

/* define the union U_BT_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_V1;

/* define the union U_BT_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_W1;

/* define the union U_BT_DITHER_SED_Y2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_Y2;

/* define the union U_BT_DITHER_SED_U2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_U2;

/* define the union U_BT_DITHER_SED_V2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_V2;

/* define the union U_BT_DITHER_SED_W2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_W2;

/* define the union U_BT_DITHER_SED_Y3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_Y3;

/* define the union U_BT_DITHER_SED_U3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_U3;

/* define the union U_BT_DITHER_SED_V3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_V3;

/* define the union U_BT_DITHER_SED_W3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_SED_W3;

/* define the union U_BT_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_thr_min : 16; /* [15..0]  */
        unsigned int dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BT_DITHER_THR;

/* define the union U_INTF_LCD_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 24;        /* [23..0]  */
        unsigned int yc_mode : 1;            /* [24]  */
        unsigned int lcd_parallel_mode : 1;  /* [25]  */
        unsigned int lcd_data_inv : 1;       /* [26]  */
        unsigned int lcd_parallel_order : 1; /* [27]  */
        unsigned int lcd_serial_perd : 1;    /* [28]  */
        unsigned int lcd_serial_mode : 1;    /* [29]  */
        unsigned int dfir_en : 1;            /* [30]  */
        unsigned int hdmi_mode : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_LCD_CTRL;

/* define the union U_INTF_LCD_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_LCD_UPD;

/* define the union U_INTF_LCD_SYNC_INV */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dv_inv : 1;      /* [0]  */
        unsigned int hs_inv : 1;      /* [1]  */
        unsigned int vs_inv : 1;      /* [2]  */
        unsigned int f_inv : 1;       /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF_LCD_SYNC_INV;

/* define the union U_LCD_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_tap_mode : 2;     /* [1..0]  */
        unsigned int dither_domain_mode : 1;  /* [2]  */
        unsigned int dither_round : 1;        /* [3]  */
        unsigned int dither_mode : 1;         /* [4]  */
        unsigned int dither_en : 1;           /* [5]  */
        unsigned int dither_round_unlim : 1;  /* [6]  */
        unsigned int i_data_width_dither : 3; /* [9..7]  */
        unsigned int o_data_width_dither : 3; /* [12..10]  */
        unsigned int reserved_0 : 19;         /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_CTRL;

/* define the union U_LCD_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_Y0;

/* define the union U_LCD_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_U0;

/* define the union U_LCD_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_V0;

/* define the union U_LCD_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_W0;

/* define the union U_LCD_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_Y1;

/* define the union U_LCD_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_U1;

/* define the union U_LCD_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_V1;

/* define the union U_LCD_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_W1;

/* define the union U_LCD_DITHER_SED_Y2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_Y2;

/* define the union U_LCD_DITHER_SED_U2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_U2;

/* define the union U_LCD_DITHER_SED_V2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_V2;

/* define the union U_LCD_DITHER_SED_W2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_W2;

/* define the union U_LCD_DITHER_SED_Y3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_Y3;

/* define the union U_LCD_DITHER_SED_U3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_U3;

/* define the union U_LCD_DITHER_SED_V3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_V3;

/* define the union U_LCD_DITHER_SED_W3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_SED_W3;

/* define the union U_LCD_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_thr_min : 16; /* [15..0]  */
        unsigned int dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LCD_DITHER_THR;

/* define the union U_DHD1_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;          /* [0]  */
        unsigned int disp_mode : 3;      /* [3..1]  */
        unsigned int iop : 1;            /* [4]  */
        unsigned int intf_ivs : 1;       /* [5]  */
        unsigned int intf_ihs : 1;       /* [6]  */
        unsigned int intf_idv : 1;       /* [7]  */
        unsigned int reserved_0 : 1;     /* [8]  */
        unsigned int hdmi420c_sel : 1;   /* [9]  */
        unsigned int hdmi420_en : 1;     /* [10]  */
        unsigned int uf_offline_en : 1;  /* [11]  */
        unsigned int reserved_1 : 2;     /* [13..12]  */
        unsigned int hdmi_mode : 1;      /* [14]  */
        unsigned int twochn_debug : 1;   /* [15]  */
        unsigned int twochn_en : 1;      /* [16]  */
        unsigned int reserved_2 : 1;     /* [17]  */
        unsigned int cbar_mode : 1;      /* [18]  */
        unsigned int sin_en : 1;         /* [19]  */
        unsigned int fpga_lmt_width : 7; /* [26..20]  */
        unsigned int fpga_lmt_en : 1;    /* [27]  */
        unsigned int p2i_en : 1;         /* [28]  */
        unsigned int cbar_sel : 1;       /* [29]  */
        unsigned int cbar_en : 1;        /* [30]  */
        unsigned int intf_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_CTRL;

/* define the union U_DHD1_VSYNC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vact : 16; /* [15..0]  */
        unsigned int vbb : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_VSYNC1;

/* define the union U_DHD1_VSYNC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vfb : 16;        /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_VSYNC2;

/* define the union U_DHD1_HSYNC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hact : 16; /* [15..0]  */
        unsigned int hbb : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_HSYNC1;

/* define the union U_DHD1_HSYNC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hfb : 16;  /* [15..0]  */
        unsigned int hmid : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_HSYNC2;

/* define the union U_DHD1_VPLUS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bvact : 16; /* [15..0]  */
        unsigned int bvbb : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_VPLUS1;

/* define the union U_DHD1_VPLUS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bvfb : 16;       /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_VPLUS2;

/* define the union U_DHD1_PWR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hpw : 16;        /* [15..0]  */
        unsigned int vpw : 8;         /* [23..16]  */
        unsigned int reserved_0 : 3;  /* [26..24]  */
        unsigned int multichn_en : 2; /* [28..27]  */
        unsigned int reserved_1 : 3;  /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_PWR;

/* define the union U_DHD1_VTTHD3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vtmgthd3 : 13;  /* [12..0]  */
        unsigned int reserved_0 : 2; /* [14..13]  */
        unsigned int thd3_mode : 1;  /* [15]  */
        unsigned int vtmgthd4 : 13;  /* [28..16]  */
        unsigned int reserved_1 : 2; /* [30..29]  */
        unsigned int thd4_mode : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_VTTHD3;

/* define the union U_DHD1_VTTHD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vtmgthd1 : 13;  /* [12..0]  */
        unsigned int reserved_0 : 2; /* [14..13]  */
        unsigned int thd1_mode : 1;  /* [15]  */
        unsigned int vtmgthd2 : 13;  /* [28..16]  */
        unsigned int reserved_1 : 2; /* [30..29]  */
        unsigned int thd2_mode : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_VTTHD;

/* define the union U_DHD1_PARATHD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_thd : 8;    /* [7..0]  */
        unsigned int reserved_0 : 23; /* [30..8]  */
        unsigned int dfs_en : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_PARATHD;

/* define the union U_DHD1_PRECHARGE_THD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tcon_precharge_thd : 17; /* [16..0]  */
        unsigned int reserved_0 : 15;         /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_PRECHARGE_THD;

/* define the union U_DHD1_START_POS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int start_pos : 8;        /* [7..0]  */
        unsigned int timing_start_pos : 8; /* [15..8]  */
        unsigned int fi_start_pos : 4;     /* [19..16]  */
        unsigned int req_start_pos : 12;   /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_START_POS;

/* define the union U_DHD1_START_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_start_pos1 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_START_POS1;

/* define the union U_DHD1_PARAUP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int paraup_mode : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_PARAUP;

/* define the union U_DHD1_SYNC_INV */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lcd_dv_inv : 1;  /* [0]  */
        unsigned int lcd_hs_inv : 1;  /* [1]  */
        unsigned int lcd_vs_inv : 1;  /* [2]  */
        unsigned int reserved_0 : 1;  /* [3]  */
        unsigned int vga_dv_inv : 1;  /* [4]  */
        unsigned int vga_hs_inv : 1;  /* [5]  */
        unsigned int vga_vs_inv : 1;  /* [6]  */
        unsigned int reserved_1 : 1;  /* [7]  */
        unsigned int hdmi_dv_inv : 1; /* [8]  */
        unsigned int hdmi_hs_inv : 1; /* [9]  */
        unsigned int hdmi_vs_inv : 1; /* [10]  */
        unsigned int hdmi_f_inv : 1;  /* [11]  */
        unsigned int date_dv_inv : 1; /* [12]  */
        unsigned int date_hs_inv : 1; /* [13]  */
        unsigned int date_vs_inv : 1; /* [14]  */
        unsigned int date_f_inv : 1;  /* [15]  */
        unsigned int reserved_2 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_SYNC_INV;

/* define the union U_DHD1_CLK_DV_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int intf_clk_mux : 1;        /* [0]  */
        unsigned int intf_dv_mux : 1;         /* [1]  */
        unsigned int no_active_area_pos : 16; /* [17..2]  */
        unsigned int reserved_0 : 14;         /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_CLK_DV_CTRL;

/* define the union U_DHD1_RGB_FIX_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int fix_b : 10;      /* [9..0]  */
        unsigned int fix_g : 10;      /* [19..10]  */
        unsigned int fix_r : 10;      /* [29..20]  */
        unsigned int rgb_fix_mux : 1; /* [30]  */
        unsigned int reserved_0 : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_RGB_FIX_CTRL;

/* define the union U_DHD1_LOCKCFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int measure_en : 1;     /* [0]  */
        unsigned int lock_cnt_en : 1;    /* [1]  */
        unsigned int vdp_measure_en : 1; /* [2]  */
        unsigned int reserved_0 : 29;    /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_LOCKCFG;

/* define the union U_DHD1_INTF_CHKSUM_HIGH1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int y0_sum_high : 8; /* [7..0]  */
        unsigned int g0_sum_high : 8; /* [15..8]  */
        unsigned int b0_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_INTF_CHKSUM_HIGH1;

/* define the union U_DHD1_INTF_CHKSUM_HIGH2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int y1_sum_high : 8; /* [7..0]  */
        unsigned int g1_sum_high : 8; /* [15..8]  */
        unsigned int b1_sum_high : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;  /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_INTF_CHKSUM_HIGH2;

/* define the union U_DHD1_STATE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vback_blank : 1;  /* [0]  */
        unsigned int vblank : 1;       /* [1]  */
        unsigned int bottom_field : 1; /* [2]  */
        unsigned int vcnt : 13;        /* [15..3]  */
        unsigned int count_int : 8;    /* [23..16]  */
        unsigned int dhd_even : 1;     /* [24]  */
        unsigned int reserved_0 : 7;   /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_STATE;

/* define the union U_DHD1_UF_STATE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ud_first_cnt : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;    /* [15..13]  */
        unsigned int start_pos : 8;     /* [23..16]  */
        unsigned int reserved_1 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DHD1_UF_STATE;

/* define the union U_INTF1_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_tap_mode : 2;     /* [1..0]  */
        unsigned int dither_domain_mode : 1;  /* [2]  */
        unsigned int dither_round : 1;        /* [3]  */
        unsigned int dither_mode : 1;         /* [4]  */
        unsigned int dither_en : 1;           /* [5]  */
        unsigned int dither_round_unlim : 1;  /* [6]  */
        unsigned int i_data_width_dither : 3; /* [9..7]  */
        unsigned int o_data_width_dither : 3; /* [12..10]  */
        unsigned int reserved_0 : 19;         /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_CTRL;

/* define the union U_INTF1_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_Y0;

/* define the union U_INTF1_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_U0;

/* define the union U_INTF1_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_V0;

/* define the union U_INTF1_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_W0;

/* define the union U_INTF1_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_Y1;

/* define the union U_INTF1_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_U1;

/* define the union U_INTF1_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_V1;

/* define the union U_INTF1_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_W1;

/* define the union U_INTF1_DITHER_SED_Y2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_Y2;

/* define the union U_INTF1_DITHER_SED_U2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_U2;

/* define the union U_INTF1_DITHER_SED_V2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_V2;

/* define the union U_INTF1_DITHER_SED_W2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w2 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_W2;

/* define the union U_INTF1_DITHER_SED_Y3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_y3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_Y3;

/* define the union U_INTF1_DITHER_SED_U3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_u3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_U3;

/* define the union U_INTF1_DITHER_SED_V3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_v3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_V3;

/* define the union U_INTF1_DITHER_SED_W3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_sed_w3 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;     /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_SED_W3;

/* define the union U_INTF1_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dither_thr_min : 16; /* [15..0]  */
        unsigned int dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INTF1_DITHER_THR;

/* define the union U_MAC_OUTSTANDING */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mstr0_routstanding : 4; /* [3..0]  */
        unsigned int mstr0_woutstanding : 4; /* [7..4]  */
        unsigned int mstr1_routstanding : 4; /* [11..8]  */
        unsigned int mstr1_woutstanding : 4; /* [15..12]  */
        unsigned int mstr2_routstanding : 4; /* [19..16]  */
        unsigned int mstr2_woutstanding : 4; /* [23..20]  */
        unsigned int reserved_0 : 8;         /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_OUTSTANDING;

/* define the union U_MAC_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int split_mode : 4;  /* [3..0]  */
        unsigned int arb_mode : 4;    /* [7..4]  */
        unsigned int mid_enable : 1;  /* [8]  */
        unsigned int reserved_0 : 23; /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_CTRL;

/* define the union U_MAC_RCHN_PRIO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_prio : 1;   /* [0]  */
        unsigned int v0l_prio : 1;    /* [1]  */
        unsigned int v0c_prio : 1;    /* [2]  */
        unsigned int v0lh_prio : 1;   /* [3]  */
        unsigned int v0ch_prio : 1;   /* [4]  */
        unsigned int v1l_prio : 1;    /* [5]  */
        unsigned int v1c_prio : 1;    /* [6]  */
        unsigned int v1lh_prio : 1;   /* [7]  */
        unsigned int v1ch_prio : 1;   /* [8]  */
        unsigned int g0ar_prio : 1;   /* [9]  */
        unsigned int g0gb_prio : 1;   /* [10]  */
        unsigned int g1ar_prio : 1;   /* [11]  */
        unsigned int g1gb_prio : 1;   /* [12]  */
        unsigned int v2l_prio : 1;    /* [13]  */
        unsigned int v2c_prio : 1;    /* [14]  */
        unsigned int v2lh_prio : 1;   /* [15]  */
        unsigned int v2ch_prio : 1;   /* [16]  */
        unsigned int g3ar_prio : 1;   /* [17]  */
        unsigned int g3gb_prio : 1;   /* [18]  */
        unsigned int reserved_0 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_RCHN_PRIO;

/* define the union U_MAC_WCHN_PRIO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbcl_prio : 1;   /* [0]  */
        unsigned int wbcc_prio : 1;   /* [1]  */
        unsigned int wbclh_prio : 1;  /* [2]  */
        unsigned int wbcch_prio : 1;  /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_WCHN_PRIO;

/* define the union U_MAC_RCHN_SEL0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int para_sel : 2;   /* [1..0]  */
        unsigned int v0l_sel : 2;    /* [3..2]  */
        unsigned int v0c_sel : 2;    /* [5..4]  */
        unsigned int v0lh_sel : 2;   /* [7..6]  */
        unsigned int v0ch_sel : 2;   /* [9..8]  */
        unsigned int v1l_sel : 2;    /* [11..10]  */
        unsigned int v1c_sel : 2;    /* [13..12]  */
        unsigned int v1lh_sel : 2;   /* [15..14]  */
        unsigned int v1ch_sel : 2;   /* [17..16]  */
        unsigned int g0ar_sel : 2;   /* [19..18]  */
        unsigned int g0gb_sel : 2;   /* [21..20]  */
        unsigned int g1ar_sel : 2;   /* [23..22]  */
        unsigned int g1gb_sel : 2;   /* [25..24]  */
        unsigned int v2_sel : 2;     /* [27..26]  */
        unsigned int g3_sel : 2;     /* [29..28]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_RCHN_SEL0;

/* define the union U_MAC_WCHN_SEL0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbcl_sel : 2;    /* [1..0]  */
        unsigned int wbcc_sel : 2;    /* [3..2]  */
        unsigned int wbclh_sel : 2;   /* [5..4]  */
        unsigned int wbcch_sel : 2;   /* [7..6]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_WCHN_SEL0;

/* define the union U_MAC_BUS_ERR_CLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bus_error_clr : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_BUS_ERR_CLR;

/* define the union U_MAC_BUS_ERR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mst0_r_error : 1; /* [0]  */
        unsigned int mst0_w_error : 1; /* [1]  */
        unsigned int mst1_r_error : 1; /* [2]  */
        unsigned int mst1_w_error : 1; /* [3]  */
        unsigned int mst2_r_error : 1; /* [4]  */
        unsigned int mst2_w_error : 1; /* [5]  */
        unsigned int reserved_0 : 26;  /* [31..6]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_BUS_ERR;

/* define the union U_MAC_DEBUG_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int axi_det_enable : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_DEBUG_CTRL;

/* define the union U_MAC_DEBUG_CLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int axi_det_clr : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MAC_DEBUG_CLR;

/* define the union U_VID_READ_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chm_rmode : 3;     /* [2..0]  */
        unsigned int reserved_0 : 1;    /* [3]  */
        unsigned int lm_rmode : 3;      /* [6..4]  */
        unsigned int reserved_1 : 1;    /* [7]  */
        unsigned int chm_draw_mode : 2; /* [9..8]  */
        unsigned int lm_draw_mode : 2;  /* [11..10]  */
        unsigned int flip_en : 1;       /* [12]  */
        unsigned int chm_copy_en : 1;   /* [13]  */
        unsigned int reserved_2 : 2;    /* [15..14]  */
        unsigned int mute_en : 1;       /* [16]  */
        unsigned int mute_req_en : 1;   /* [17]  */
        unsigned int vicap_mute_en : 1; /* [18]  */
        unsigned int mrg_enable : 1;    /* [19]  */
        unsigned int mrg_mute_mode : 1; /* [20]  */
        unsigned int reserved_3 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_READ_CTRL;

/* define the union U_VID_MAC_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_ctrl : 2;    /* [1..0]  */
        unsigned int req_len : 2;     /* [3..2]  */
        unsigned int reserved_0 : 4;  /* [7..4]  */
        unsigned int ofl_master : 1;  /* [8]  */
        unsigned int reserved_1 : 22; /* [30..9]  */
        unsigned int pre_rd_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_MAC_CTRL;

/* define the union U_VID_OUT_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int draw_pixel_mode : 3;  /* [2..0]  */
        unsigned int draw_pixel_en : 1;    /* [3]  */
        unsigned int uv_order_en : 1;      /* [4]  */
        unsigned int single_port_mode : 1; /* [5]  */
        unsigned int testpattern_en : 1;   /* [6]  */
        unsigned int reserved_0 : 25;      /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_OUT_CTRL;

/* define the union U_VID_MUTE_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_alpha : 8;  /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_MUTE_ALPHA;

/* define the union U_VID_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_MUTE_BK;

/* define the union U_VID_SRC_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int data_type : 3;   /* [2..0]  */
        unsigned int data_fmt : 2;    /* [4..3]  */
        unsigned int reserved_0 : 3;  /* [7..5]  */
        unsigned int data_width : 2;  /* [9..8]  */
        unsigned int reserved_1 : 2;  /* [11..10]  */
        unsigned int field_type : 1;  /* [12]  */
        unsigned int reserved_2 : 3;  /* [15..13]  */
        unsigned int disp_mode : 4;   /* [19..16]  */
        unsigned int dcmp_en : 1;     /* [20]  */
        unsigned int reserved_3 : 11; /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_SRC_INFO;

/* define the union U_VID_SRC_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_w : 16; /* [15..0]  */
        unsigned int src_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_SRC_RESO;

/* define the union U_VID_SRC_CROP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_crop_x : 16; /* [15..0]  */
        unsigned int src_crop_y : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_SRC_CROP;

/* define the union U_VID_IN_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ireso_w : 16; /* [15..0]  */
        unsigned int ireso_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_IN_RESO;

/* define the union U_VID_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_stride : 16;  /* [15..0]  */
        unsigned int chm_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_STRIDE;

/* define the union U_VID_2BIT_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_tile_stride : 16;  /* [15..0]  */
        unsigned int chm_tile_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_2BIT_STRIDE;

/* define the union U_VID_HEAD_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_head_stride : 16;  /* [15..0]  */
        unsigned int chm_head_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_HEAD_STRIDE;

/* define the union U_VID_SMMU_BYPASS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_bypass_2d : 1;  /* [0]  */
        unsigned int chm_bypass_2d : 1; /* [1]  */
        unsigned int lm_bypass_3d : 1;  /* [2]  */
        unsigned int chm_bypass_3d : 1; /* [3]  */
        unsigned int reserved_0 : 28;   /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_SMMU_BYPASS;

/* define the union U_VID_TESTPAT_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_speed : 10;     /* [9..0]  */
        unsigned int reserved_0 : 2;    /* [11..10]  */
        unsigned int tp_line_w : 1;     /* [12]  */
        unsigned int tp_color_mode : 1; /* [13]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int tp_mode : 2;       /* [17..16]  */
        unsigned int reserved_2 : 14;   /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_TESTPAT_CFG;

/* define the union U_VID_TESTPAT_SEED */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_seed : 30;   /* [29..0]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_TESTPAT_SEED;

/* define the union U_VID_LATENCY_CLC */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int latency_clc : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_LATENCY_CLC;

/* define the union U_VID_LATENCY_L_LINE0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lm_line_latency : 16; /* [15..0]  */
        unsigned int lm_line_max : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_LATENCY_L_LINE0;

/* define the union U_VID_LATENCY_L_LINE1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lt_line_latency : 16; /* [15..0]  */
        unsigned int lt_line_max : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_LATENCY_L_LINE1;

/* define the union U_VID_LATENCY_C_LINE0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chm_line_latency : 16; /* [15..0]  */
        unsigned int chm_line_max : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_LATENCY_C_LINE0;

/* define the union U_VID_LATENCY_C_LINE1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cht_line_latency : 16; /* [15..0]  */
        unsigned int cht_line_max : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_LATENCY_C_LINE1;

/* define the union U_VID_DEBUG_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_chk_bit8_sel : 4; /* [3..0]  */
        unsigned int l_check_sum_en : 1; /* [4]  */
        unsigned int reserved_0 : 11;    /* [15..5]  */
        unsigned int c_chk_bit8_sel : 4; /* [19..16]  */
        unsigned int c_check_sum_en : 1; /* [20]  */
        unsigned int reserved_1 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DEBUG_CTRL;

/* define the union U_VID_DEBUG_STATE_CLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_frame_end_clr : 1; /* [0]  */
        unsigned int l_out_end_clr : 1;   /* [1]  */
        unsigned int reserved_0 : 14;     /* [15..2]  */
        unsigned int c_frame_end_clr : 1; /* [16]  */
        unsigned int c_out_end_clr : 1;   /* [17]  */
        unsigned int reserved_1 : 14;     /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DEBUG_STATE_CLR;

/* define the union U_VID_DEBUG_L_STA0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_line_num : 16;  /* [15..0]  */
        unsigned int l_frame_busy : 1; /* [16]  */
        unsigned int l_frame_end : 1;  /* [17]  */
        unsigned int l_out_end : 1;    /* [18]  */
        unsigned int reserved_0 : 13;  /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DEBUG_L_STA0;

/* define the union U_VID_DEBUG_C_STA0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int c_line_num : 16;  /* [15..0]  */
        unsigned int c_frame_busy : 1; /* [16]  */
        unsigned int c_frame_end : 1;  /* [17]  */
        unsigned int c_out_end : 1;    /* [18]  */
        unsigned int reserved_0 : 13;  /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DEBUG_C_STA0;

/* define the union U_VID_DCMP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int c_is_lossless : 1; /* [0]  */
        unsigned int l_is_lossless : 1; /* [1]  */
        unsigned int c_cmp_mode : 1;    /* [2]  */
        unsigned int l_cmp_mode : 1;    /* [3]  */
        unsigned int c_cmp_rate : 2;    /* [5..4]  */
        unsigned int l_cmp_rate : 2;    /* [7..6]  */
        unsigned int mem_mode : 1;      /* [8]  */
        unsigned int reserved_0 : 23;   /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DCMP_CTRL;

/* define the union U_VID_DCMPERRCLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_l_errclr : 1;      /* [0]  */
        unsigned int dcmp_c_errclr : 1;      /* [1]  */
        unsigned int dcmp_head_l_errclr : 1; /* [2]  */
        unsigned int reserved_0 : 29;        /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DCMPERRCLR;

/* define the union U_VID_DCMP_ERR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_l_wrong : 1;      /* [0]  */
        unsigned int dcmp_c_wrong : 1;      /* [1]  */
        unsigned int dcmp_l_head_wrong : 1; /* [2]  */
        unsigned int dcmp_c_head_wrong : 1; /* [3]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_DCMP_ERR;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ice_en : 1;      /* [0]  */
        unsigned int cmp_mode : 1;    /* [1]  */
        unsigned int is_lossless : 1; /* [2]  */
        unsigned int reserved_0 : 3;  /* [5..3]  */
        unsigned int bitdepth : 1;    /* [6]  */
        unsigned int reserved_1 : 1;  /* [7]  */
        unsigned int fix_k : 3;       /* [10..8]  */
        unsigned int reserved_2 : 1;  /* [11]  */
        unsigned int max_qp : 3;      /* [14..12]  */
        unsigned int reserved_3 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_CTRL;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 14;  /* [13..0]  */
        unsigned int reserved_0 : 2;    /* [15..14]  */
        unsigned int frame_height : 14; /* [29..16]  */
        unsigned int reserved_1 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_RESO;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_STA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_error : 1;  /* [0]  */
        unsigned int forgive : 1;     /* [1]  */
        unsigned int consume : 1;     /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_STA;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_CTRL_2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ice_en : 1;      /* [0]  */
        unsigned int cmp_mode : 1;    /* [1]  */
        unsigned int is_lossless : 1; /* [2]  */
        unsigned int reserved_0 : 3;  /* [5..3]  */
        unsigned int bitdepth : 1;    /* [6]  */
        unsigned int reserved_1 : 1;  /* [7]  */
        unsigned int fix_k : 3;       /* [10..8]  */
        unsigned int reserved_2 : 1;  /* [11]  */
        unsigned int max_qp : 3;      /* [14..12]  */
        unsigned int reserved_3 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_CTRL_2P;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_RESO_2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 14;  /* [13..0]  */
        unsigned int reserved_0 : 2;    /* [15..14]  */
        unsigned int frame_height : 14; /* [29..16]  */
        unsigned int reserved_1 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_RESO_2P;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_STA_2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_error : 1;  /* [0]  */
        unsigned int forgive : 1;     /* [1]  */
        unsigned int consume : 1;     /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_STA_2P;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_CTRL_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ice_en : 1;      /* [0]  */
        unsigned int cmp_mode : 1;    /* [1]  */
        unsigned int is_lossless : 1; /* [2]  */
        unsigned int reserved_0 : 3;  /* [5..3]  */
        unsigned int bitdepth : 1;    /* [6]  */
        unsigned int reserved_1 : 1;  /* [7]  */
        unsigned int fix_k : 3;       /* [10..8]  */
        unsigned int reserved_2 : 1;  /* [11]  */
        unsigned int max_qp : 3;      /* [14..12]  */
        unsigned int reserved_3 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_CTRL_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_RESO_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 14;  /* [13..0]  */
        unsigned int reserved_0 : 2;    /* [15..14]  */
        unsigned int frame_height : 14; /* [29..16]  */
        unsigned int reserved_1 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_RESO_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_STA_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_error : 1;  /* [0]  */
        unsigned int forgive : 1;     /* [1]  */
        unsigned int consume : 1;     /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_STA_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_CTRL_2P_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ice_en : 1;      /* [0]  */
        unsigned int cmp_mode : 1;    /* [1]  */
        unsigned int is_lossless : 1; /* [2]  */
        unsigned int reserved_0 : 3;  /* [5..3]  */
        unsigned int bitdepth : 1;    /* [6]  */
        unsigned int reserved_1 : 1;  /* [7]  */
        unsigned int fix_k : 3;       /* [10..8]  */
        unsigned int reserved_2 : 1;  /* [11]  */
        unsigned int max_qp : 3;      /* [14..12]  */
        unsigned int reserved_3 : 17; /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_CTRL_2P_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_RESO_2P_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 14;  /* [13..0]  */
        unsigned int reserved_0 : 2;    /* [15..14]  */
        unsigned int frame_height : 14; /* [29..16]  */
        unsigned int reserved_1 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_RESO_2P_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_DCMP_STA_2P_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_error : 1;  /* [0]  */
        unsigned int forgive : 1;     /* [1]  */
        unsigned int consume : 1;     /* [2]  */
        unsigned int reserved_0 : 29; /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_DCMP_STA_2P_CHM;

/* define the union U_GFX_READ_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int read_mode : 2;   /* [1..0]  */
        unsigned int reserved_0 : 2;  /* [3..2]  */
        unsigned int draw_mode : 2;   /* [5..4]  */
        unsigned int reserved_1 : 2;  /* [7..6]  */
        unsigned int flip_en : 1;     /* [8]  */
        unsigned int reserved_2 : 1;  /* [9]  */
        unsigned int mute_en : 1;     /* [10]  */
        unsigned int mute_req_en : 1; /* [11]  */
        unsigned int reserved_3 : 20; /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_READ_CTRL;

/* define the union U_GFX_MAC_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_ctrl : 2;    /* [1..0]  */
        unsigned int req_len : 2;     /* [3..2]  */
        unsigned int reserved_0 : 4;  /* [7..4]  */
        unsigned int ofl_master : 1;  /* [8]  */
        unsigned int reserved_1 : 23; /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_MAC_CTRL;

/* define the union U_GFX_OUT_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int palpha_range : 1;   /* [0]  */
        unsigned int palpha_en : 1;      /* [1]  */
        unsigned int reserved_0 : 2;     /* [3..2]  */
        unsigned int key_mode : 1;       /* [4]  */
        unsigned int key_en : 1;         /* [5]  */
        unsigned int reserved_1 : 2;     /* [7..6]  */
        unsigned int bitext : 2;         /* [9..8]  */
        unsigned int premulti_en : 1;    /* [10]  */
        unsigned int testpattern_en : 1; /* [11]  */
        unsigned int reserved_2 : 20;    /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_OUT_CTRL;

/* define the union U_GFX_MUTE_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_alpha : 8;  /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_MUTE_ALPHA;

/* define the union U_GFX_MUTE_BK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mute_cr : 10;   /* [9..0]  */
        unsigned int mute_cb : 10;   /* [19..10]  */
        unsigned int mute_y : 10;    /* [29..20]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_MUTE_BK;

/* define the union U_GFX_SMMU_BYPASS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smmu_bypass_2d : 1; /* [0]  */
        unsigned int smmu_bypass_3d : 1; /* [1]  */
        unsigned int reserved_0 : 30;    /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_SMMU_BYPASS;

/* define the union U_GFX_1555_ALPHA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int alpha_0 : 8;     /* [7..0]  */
        unsigned int alpha_1 : 8;     /* [15..8]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_1555_ALPHA;

/* define the union U_GFX_SRC_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ifmt : 8;        /* [7..0]  */
        unsigned int reserved_0 : 8;  /* [15..8]  */
        unsigned int disp_mode : 4;   /* [19..16]  */
        unsigned int dcmp_en : 1;     /* [20]  */
        unsigned int reserved_1 : 11; /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_SRC_INFO;

/* define the union U_GFX_SRC_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_w : 16; /* [15..0]  */
        unsigned int src_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_SRC_RESO;

/* define the union U_GFX_SRC_CROP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int src_crop_x : 16; /* [15..0]  */
        unsigned int src_crop_y : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_SRC_CROP;

/* define the union U_GFX_IRESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ireso_w : 16; /* [15..0]  */
        unsigned int ireso_h : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_IRESO;

/* define the union U_GFX_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int surface_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_STRIDE;

/* define the union U_GFX_CKEY_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int key_max : 8;  /* [7..0]  */
        unsigned int key_g_max : 8;  /* [15..8]  */
        unsigned int key_r_max : 8;  /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_CKEY_MAX;

/* define the union U_GFX_CKEY_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int key_min : 8;  /* [7..0]  */
        unsigned int key_g_min : 8;  /* [15..8]  */
        unsigned int key_r_min : 8;  /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_CKEY_MIN;

/* define the union U_GFX_CKEY_MASK */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int key_msk : 8;  /* [7..0]  */
        unsigned int key_g_msk : 8;  /* [15..8]  */
        unsigned int key_r_msk : 8;  /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_CKEY_MASK;

/* define the union U_GFX_TESTPAT_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_speed : 10;     /* [9..0]  */
        unsigned int reserved_0 : 2;    /* [11..10]  */
        unsigned int tp_line_w : 1;     /* [12]  */
        unsigned int tp_color_mode : 1; /* [13]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int tp_mode : 2;       /* [17..16]  */
        unsigned int reserved_2 : 14;   /* [31..18]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_TESTPAT_CFG;

/* define the union U_GFX_TESTPAT_SEED */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tp_seed : 30;   /* [29..0]  */
        unsigned int reserved_0 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_TESTPAT_SEED;

/* define the union U_GFX_LATENCY_CLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int latency_clr : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_LATENCY_CLR;

/* define the union U_GFX_LINE_LATENCY */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int axi_line_num : 16; /* [15..0]  */
        unsigned int axi_line_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_LINE_LATENCY;

/* define the union U_GFX_DEBUG_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int chk_bit8_sel : 4; /* [3..0]  */
        unsigned int check_sum_en : 1; /* [4]  */
        unsigned int reserved_0 : 27;  /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_DEBUG_CTRL;

/* define the union U_GFX_STA_CLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_end_clr : 1; /* [0]  */
        unsigned int out_end_clr : 1;   /* [1]  */
        unsigned int reserved_0 : 30;   /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_STA_CLR;

/* define the union U_GFX_DCMPERRCLR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_errclr : 1;       /* [0]  */
        unsigned int dcmp_frm_end_clr : 1;  /* [1]  */
        unsigned int frame_size_errclr : 1; /* [2]  */
        unsigned int reserved_0 : 29;       /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_DCMPERRCLR;

/* define the union U_GFX_DCMP_ERR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_wrong : 1;       /* [0]  */
        unsigned int dcmp_frame_end : 1;   /* [1]  */
        unsigned int frame_size_wrong : 1; /* [2]  */
        unsigned int reserved_0 : 29;      /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_DCMP_ERR;

/* define the union U_GFX_OSD_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dcmp_en : 1;       /* [0]  */
        unsigned int is_lossless : 1;   /* [1]  */
        unsigned int is_lossless_a : 1; /* [2]  */
        unsigned int cmp_mode : 1;      /* [3]  */
        unsigned int source_mode : 3;   /* [6..4]  */
        unsigned int tpred_en : 1;      /* [7]  */
        unsigned int reserved_0 : 24;   /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_OSD_GLB_INFO;

/* define the union U_GFX_OSD_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;    /* [15..13]  */
        unsigned int frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_OSD_FRAME_SIZE;

/* define the union U_GFX_OSD_DBG_REG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 30; /* [29..0]  */
        unsigned int dcmp_err0 : 1;   /* [30]  */
        unsigned int reserved_1 : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_OSD_DBG_REG;

/* define the union U_GFX_OSD_DBG_REG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 30; /* [29..0]  */
        unsigned int dcmp_err1 : 1;   /* [30]  */
        unsigned int reserved_1 : 1;  /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GFX_OSD_DBG_REG1;

/* define the union U_WBC_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 4;  /* [3..0]  */
        unsigned int data_width : 1;  /* [4]  */
        unsigned int reserved_1 : 3;  /* [7..5]  */
        unsigned int uv_order : 1;    /* [8]  */
        unsigned int flip_en : 1;     /* [9]  */
        unsigned int align_mode : 1;  /* [10]  */
        unsigned int reserved_2 : 18; /* [28..11]  */
        unsigned int wbc_cmp_en : 1;  /* [29]  */
        unsigned int reserved_3 : 2;  /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CTRL;

/* define the union U_WBC_MAC_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 2;    /* [11..10]  */
        unsigned int wbc_len : 2;       /* [13..12]  */
        unsigned int reserved_1 : 18;   /* [31..14]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_MAC_CTRL;

/* define the union U_WBC_SMMU_BYPASS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int l_bypass : 1;    /* [0]  */
        unsigned int c_bypass : 1;    /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_SMMU_BYPASS;

/* define the union U_WBC_LOWDLYCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wb_per_line_num : 12;  /* [11..0]  */
        unsigned int partfns_line_num : 12; /* [23..12]  */
        unsigned int reserved_0 : 6;        /* [29..24]  */
        unsigned int lowdly_test : 1;       /* [30]  */
        unsigned int lowdly_en : 1;         /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_LOWDLYCTRL;

/* define the union U_WBC_LOWDLYSTA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 31; /* [30..0]  */
        unsigned int part_finish : 1; /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_LOWDLYSTA;

/* define the union U_WBC_YSTRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_ystride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_YSTRIDE;

/* define the union U_WBC_CSTRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_cstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CSTRIDE;

/* define the union U_WBC_YNSTRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_ynstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_YNSTRIDE;

/* define the union U_WBC_CNSTRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_cnstride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CNSTRIDE;

/* define the union U_WBC_STA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_l_busy : 1;  /* [0]  */
        unsigned int wbc_c_busy : 1;  /* [1]  */
        unsigned int wbc_lh_busy : 1; /* [2]  */
        unsigned int wbc_ch_busy : 1; /* [3]  */
        unsigned int reserved_0 : 28; /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_STA;

/* define the union U_WBC_LINE_NUM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int wbc_l_linenum : 16; /* [15..0]  */
        unsigned int wbc_c_linenum : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_LINE_NUM;

/* define the union U_WBC_CAP_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cap_width : 16;  /* [15..0]  */
        unsigned int cap_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CAP_RESO;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ice_en : 1;               /* [0]  */
        unsigned int cmp_mode : 1;             /* [1]  */
        unsigned int is_lossless : 1;          /* [2]  */
        unsigned int chroma_en : 1;            /* [3]  */
        unsigned int tile_en : 1;              /* [4]  */
        unsigned int reserved_0 : 1;           /* [5]  */
        unsigned int bitdepth : 1;             /* [6]  */
        unsigned int reserved_1 : 1;           /* [7]  */
        unsigned int fix_k : 3;                /* [10..8]  */
        unsigned int reserved_2 : 1;           /* [11]  */
        unsigned int max_qp : 3;               /* [14..12]  */
        unsigned int rc_qp_offset : 1;         /* [15]  */
        unsigned int mb_mode_sel_grad_thr : 8; /* [23..16]  */
        unsigned int tile_height : 5;          /* [28..24]  */
        unsigned int reserved_3 : 3;           /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_CTRL;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_SAD_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int grad_ave_thr0 : 8; /* [7..0]  */
        unsigned int grad_ave_thr1 : 8; /* [15..8]  */
        unsigned int grad_ave_thr2 : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_SAD_THR;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_SIM_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int simi_fct_thr0 : 8; /* [7..0]  */
        unsigned int simi_fct_thr1 : 8; /* [15..8]  */
        unsigned int simi_fct_thr2 : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_SIM_THR;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 14;  /* [13..0]  */
        unsigned int reserved_0 : 2;    /* [15..14]  */
        unsigned int frame_height : 14; /* [29..16]  */
        unsigned int reserved_1 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_RESO;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_MAX_BIT */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int seg_cfg_max_bit : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;       /* [15..12]  */
        unsigned int seg_cfg_tar_bit : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;       /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_MAX_BIT;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_SLC_BIT */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int slc_cfg_tar_bit : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;       /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_SLC_BIT;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_CTRL_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ice_en : 1;               /* [0]  */
        unsigned int cmp_mode : 1;             /* [1]  */
        unsigned int is_lossless : 1;          /* [2]  */
        unsigned int chroma_en : 1;            /* [3]  */
        unsigned int tile_en : 1;              /* [4]  */
        unsigned int reserved_0 : 1;           /* [5]  */
        unsigned int bitdepth : 1;             /* [6]  */
        unsigned int reserved_1 : 1;           /* [7]  */
        unsigned int fix_k : 3;                /* [10..8]  */
        unsigned int reserved_2 : 1;           /* [11]  */
        unsigned int max_qp : 3;               /* [14..12]  */
        unsigned int rc_qp_offset : 1;         /* [15]  */
        unsigned int mb_mode_sel_grad_thr : 8; /* [23..16]  */
        unsigned int tile_height : 5;          /* [28..24]  */
        unsigned int reserved_3 : 3;           /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_CTRL_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_SAD_THR_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int grad_ave_thr0 : 8; /* [7..0]  */
        unsigned int grad_ave_thr1 : 8; /* [15..8]  */
        unsigned int grad_ave_thr2 : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_SAD_THR_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_SIM_THR_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int simi_fct_thr0 : 8; /* [7..0]  */
        unsigned int simi_fct_thr1 : 8; /* [15..8]  */
        unsigned int simi_fct_thr2 : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_SIM_THR_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_RESO_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 14;  /* [13..0]  */
        unsigned int reserved_0 : 2;    /* [15..14]  */
        unsigned int frame_height : 14; /* [29..16]  */
        unsigned int reserved_1 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_RESO_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_MAX_BIT_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int seg_cfg_max_bit : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;       /* [15..12]  */
        unsigned int seg_cfg_tar_bit : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;       /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_MAX_BIT_CHM;

/* define the union U_ICE_V2R1_SEG_256X1_CMP_SLC_BIT_CHM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int slc_cfg_tar_bit : 28; /* [27..0]  */
        unsigned int reserved_0 : 4;       /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_ICE_V2R1_SEG_256X1_CMP_SLC_BIT_CHM;

/* define the union U_WBC_CMP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int req_interval : 10; /* [9..0]  */
        unsigned int reserved_0 : 17;   /* [26..10]  */
        unsigned int mem_mode : 1;      /* [27]  */
        unsigned int data_width : 1;    /* [28]  */
        unsigned int reserved_1 : 1;    /* [29]  */
        unsigned int l_cmp_en : 1;      /* [30]  */
        unsigned int wbc_en : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_CTRL;

/* define the union U_WBC_CMP_UPD */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int regup : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_UPD;

/* define the union U_WBC_CMP_HEIGHT */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int c_max_height : 13; /* [12..0]  */
        unsigned int l_max_height : 13; /* [25..13]  */
        unsigned int addr_mode : 1;     /* [26]  */
        unsigned int fsize_mode : 1;    /* [27]  */
        unsigned int rgb_cmp_mode : 2;  /* [29..28]  */
        unsigned int pause_mode : 1;    /* [30]  */
        unsigned int buffer_mode : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_HEIGHT;

/* define the union U_WBC_CMP_ORESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ow : 12;        /* [11..0]  */
        unsigned int oh : 12;        /* [23..12]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_CMP_ORESO;

/* define the union U_WBC_OD_STATE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int addr_err : 1;      /* [0]  */
        unsigned int he_addr_err0 : 1;  /* [1]  */
        unsigned int he_addr_err1 : 1;  /* [2]  */
        unsigned int he_addr_err2 : 1;  /* [3]  */
        unsigned int w_addr_err : 1;    /* [4]  */
        unsigned int he_fsize_err0 : 1; /* [5]  */
        unsigned int he_fsize_err1 : 1; /* [6]  */
        unsigned int he_fsize_err2 : 1; /* [7]  */
        unsigned int w_fsize_err : 1;   /* [8]  */
        unsigned int he_fsize_war0 : 1; /* [9]  */
        unsigned int he_fsize_war1 : 1; /* [10]  */
        unsigned int he_fsize_war2 : 1; /* [11]  */
        unsigned int w_fsize_war : 1;   /* [12]  */
        unsigned int reserved_0 : 19;   /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WBC_OD_STATE;

/* define the union U_OD_PIC_OSD_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int is_lossless : 1;   /* [0]  */
        unsigned int is_lossless_a : 1; /* [1]  */
        unsigned int cmp_mode : 1;      /* [2]  */
        unsigned int source_mode : 3;   /* [5..3]  */
        unsigned int part_cmp_en : 1;   /* [6]  */
        unsigned int top_pred_en : 1;   /* [7]  */
        unsigned int graphic_en : 1;    /* [8]  */
        unsigned int reserved_0 : 23;   /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_GLB_INFO;

/* define the union U_OD_PIC_OSD_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;    /* [15..13]  */
        unsigned int frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_FRAME_SIZE;

/* define the union U_OD_PIC_OSD_RC_CFG0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6;   /* [15..10]  */
        unsigned int min_mb_bits : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;   /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG0;

/* define the union U_OD_PIC_OSD_RC_CFG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_qp : 4;        /* [3..0]  */
        unsigned int reserved_0 : 4;    /* [7..4]  */
        unsigned int sad_bits_gain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;    /* [15..12]  */
        unsigned int rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5;    /* [23..19]  */
        unsigned int max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG1;

/* define the union U_OD_PIC_OSD_RC_CFG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9;  /* [15..7]  */
        unsigned int min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9;  /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG2;

/* define the union U_OD_PIC_OSD_RC_CFG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_thr : 7;      /* [6..0]  */
        unsigned int reserved_0 : 1;    /* [7]  */
        unsigned int still_thr : 7;     /* [14..8]  */
        unsigned int reserved_1 : 1;    /* [15]  */
        unsigned int big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6;    /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG3;

/* define the union U_OD_PIC_OSD_RC_CFG4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int smth_pix_num_thr : 6;  /* [5..0]  */
        unsigned int reserved_0 : 2;        /* [7..6]  */
        unsigned int still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;        /* [15..14]  */
        unsigned int noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;       /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG4;

/* define the union U_OD_PIC_OSD_RC_CFG5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int noise_sad : 7;     /* [6..0]  */
        unsigned int reserved_0 : 9;    /* [15..7]  */
        unsigned int pix_diff_thr : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;    /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG5;

/* define the union U_OD_PIC_OSD_RC_CFG6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;      /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG6;

/* define the union U_OD_PIC_OSD_RC_CFG7 */
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
} U_OD_PIC_OSD_RC_CFG7;

/* define the union U_OD_PIC_OSD_RC_CFG8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int est_err_gain : 5;      /* [4..0]  */
        unsigned int reserved_0 : 11;       /* [15..5]  */
        unsigned int max_est_err_level : 9; /* [24..16]  */
        unsigned int reserved_1 : 7;        /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG8;

/* define the union U_OD_PIC_OSD_RC_CFG9 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16;       /* [15..0]  */
        unsigned int vbv_buf_loss1_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 1;        /* [23]  */
        unsigned int vbv_buf_loss2_thr : 7; /* [30..24]  */
        unsigned int reserved_2 : 1;        /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG9;

/* define the union U_OD_PIC_OSD_RC_CFG10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int qp_thr0 : 3;     /* [2..0]  */
        unsigned int reserved_0 : 5;  /* [7..3]  */
        unsigned int qp_thr1 : 3;     /* [10..8]  */
        unsigned int reserved_1 : 5;  /* [15..11]  */
        unsigned int qp_thr2 : 3;     /* [18..16]  */
        unsigned int reserved_2 : 13; /* [31..19]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG10;

/* define the union U_OD_PIC_OSD_RC_CFG11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int grph_bias_bit_thr0 : 8;  /* [7..0]  */
        unsigned int grph_bias_bit_thr1 : 8;  /* [15..8]  */
        unsigned int grph_ideal_bit_thr : 10; /* [25..16]  */
        unsigned int reserved_0 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG11;

/* define the union U_OD_PIC_OSD_RC_CFG12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int force_rc_en : 1;           /* [0]  */
        unsigned int reserved_0 : 7;            /* [7..1]  */
        unsigned int forcerc_bits_diff_thr : 8; /* [15..8]  */
        unsigned int reserved_1 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG12;

/* define the union U_OD_PIC_OSD_RC_CFG13 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int maxdiff_ctrl_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;     /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG13;

/* define the union U_OD_PIC_OSD_RC_CFG14 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mb_bits_cap : 10;       /* [9..0]  */
        unsigned int reserved_0 : 6;         /* [15..10]  */
        unsigned int init_buf_bits_cap : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG14;

/* define the union U_OD_PIC_OSD_RC_CFG15 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lfw_mb_len : 7;    /* [6..0]  */
        unsigned int reserved_0 : 1;    /* [7]  */
        unsigned int cmplx_sad_thr : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;    /* [15..12]  */
        unsigned int err_thr0 : 4;      /* [19..16]  */
        unsigned int reserved_2 : 4;    /* [23..20]  */
        unsigned int err_thr1 : 4;      /* [27..24]  */
        unsigned int reserved_3 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG15;

/* define the union U_OD_PIC_OSD_RC_CFG16 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int sim_num_thr : 3;   /* [2..0]  */
        unsigned int reserved_0 : 5;    /* [7..3]  */
        unsigned int sum_y_err_thr : 7; /* [14..8]  */
        unsigned int reserved_1 : 1;    /* [15]  */
        unsigned int sum_c_err_thr : 7; /* [22..16]  */
        unsigned int reserved_2 : 9;    /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG16;

/* define the union U_OD_PIC_OSD_RC_CFG17 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cpmlx_sad_thr_y : 4;   /* [3..0]  */
        unsigned int reserved_0 : 4;        /* [7..4]  */
        unsigned int smpl_sad_thr_c : 4;    /* [11..8]  */
        unsigned int reserved_1 : 4;        /* [15..12]  */
        unsigned int smpl_sumsad_thr_y : 8; /* [23..16]  */
        unsigned int smpl_sumsad_thr_c : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG17;

/* define the union U_OD_PIC_OSD_RC_CFG18 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int future_sad_y_thr0 : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;        /* [7..4]  */
        unsigned int future_sad_c_thr0 : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;        /* [15..12]  */
        unsigned int future_sad_y_thr1 : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;        /* [23..20]  */
        unsigned int future_sad_c_thr1 : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;        /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG18;

/* define the union U_OD_PIC_OSD_RC_CFG19 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cmplx_sumsad_thr_y : 8; /* [7..0]  */
        unsigned int cmplx_sumsad_thr_c : 8; /* [15..8]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_RC_CFG19;

/* define the union U_OD_PIC_OSD_STAT_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_gap_bw_row_len_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;            /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_STAT_THR;

/* define the union U_OD_PIC_OSD_PCMP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int pcmp_start_hpos : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;       /* [15..13]  */
        unsigned int pcmp_end_hpos : 13;   /* [28..16]  */
        unsigned int reserved_1 : 3;       /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_PCMP;

/* define the union U_OD_PIC_OSD_BS_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int frame_size_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;     /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_BS_SIZE;

/* define the union U_OD_PIC_OSD_WORST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_WORST_ROW;

/* define the union U_OD_PIC_OSD_BEST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int min_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_BEST_ROW;

/* define the union U_OD_PIC_OSD_STAT_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int max_gap_bw_row_len_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;             /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OD_PIC_OSD_STAT_INFO;

/* define the union U_V0_MRG_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 20;    /* [19..0]  */
        unsigned int mrg_edge_en : 1;    /* [20]  */
        unsigned int reserved_1 : 4;     /* [24..21]  */
        unsigned int mrg_edge_typ : 1;   /* [25]  */
        unsigned int reserved_2 : 2;     /* [27..26]  */
        unsigned int mrg_crop_en : 1;    /* [28]  */
        unsigned int mrg_mmu_bypass : 1; /* [29]  */
        unsigned int mrg_mute_en : 1;    /* [30]  */
        unsigned int mrg_en : 1;         /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_CTRL;

/* define the union U_V0_MRG_DISP_POS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_xpos : 16; /* [15..0]  */
        unsigned int mrg_ypos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_DISP_POS;

/* define the union U_V0_MRG_DISP_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_width : 16;  /* [15..0]  */
        unsigned int mrg_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_DISP_RESO;

/* define the union U_V0_MRG_SRC_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_width : 16;  /* [15..0]  */
        unsigned int mrg_src_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_SRC_RESO;

/* define the union U_V0_MRG_SRC_OFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_hoffset : 16; /* [15..0]  */
        unsigned int mrg_src_voffset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_SRC_OFFSET;

/* define the union U_V0_MRG_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_c_stride : 16; /* [15..0]  */
        unsigned int mrg_y_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_STRIDE;

/* define the union U_V0_MRG_HSTRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_ch_stride : 16; /* [15..0]  */
        unsigned int mrg_yh_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_HSTRIDE;

/* define the union U_V0_MRG_READ_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_region : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_READ_CTRL;

/* define the union U_V0_MRG_READ_EN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_en : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V0_MRG_READ_EN;

/* define the union U_V1_MRG_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 20;    /* [19..0]  */
        unsigned int mrg_edge_en : 1;    /* [20]  */
        unsigned int reserved_1 : 4;     /* [24..21]  */
        unsigned int mrg_edge_typ : 1;   /* [25]  */
        unsigned int reserved_2 : 2;     /* [27..26]  */
        unsigned int mrg_crop_en : 1;    /* [28]  */
        unsigned int mrg_mmu_bypass : 1; /* [29]  */
        unsigned int mrg_mute_en : 1;    /* [30]  */
        unsigned int mrg_en : 1;         /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_CTRL;

/* define the union U_V1_MRG_DISP_POS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_xpos : 16; /* [15..0]  */
        unsigned int mrg_ypos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_DISP_POS;

/* define the union U_V1_MRG_DISP_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_width : 16;  /* [15..0]  */
        unsigned int mrg_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_DISP_RESO;

/* define the union U_V1_MRG_SRC_RESO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_width : 16;  /* [15..0]  */
        unsigned int mrg_src_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_SRC_RESO;

/* define the union U_V1_MRG_SRC_OFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_src_hoffset : 16; /* [15..0]  */
        unsigned int mrg_src_voffset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_SRC_OFFSET;

/* define the union U_V1_MRG_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_c_stride : 16; /* [15..0]  */
        unsigned int mrg_y_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_STRIDE;

/* define the union U_V1_MRG_HSTRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mrg_ch_stride : 16; /* [15..0]  */
        unsigned int mrg_yh_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_HSTRIDE;

/* define the union U_V1_MRG_READ_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_region : 8;   /* [7..0]  */
        unsigned int reserved_0 : 24; /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_READ_CTRL;

/* define the union U_V1_MRG_READ_EN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rd_en : 1;       /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V1_MRG_READ_EN;

/* define the union U_VPSS_RCH_DEI_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dei_format : 5;           /* [4..0]  */
        unsigned int dei_pix_bitw : 1;         /* [5]  */
        unsigned int dei_uv_invert : 1;        /* [6]  */
        unsigned int dei_tile_format : 1;      /* [7]  */
        unsigned int dei_vifir_en : 1;         /* [8]  */
        unsigned int dei_vdfir_en : 1;         /* [9]  */
        unsigned int dei_dcmp_en : 1;          /* [10]  */
        unsigned int dei_ldcmp_en : 1;         /* [11]  */
        unsigned int dei_fdcmp_en : 1;         /* [12]  */
        unsigned int dei_fdcmp_mode : 1;       /* [13]  */
        unsigned int dei_fdcmp_store_mode : 1; /* [14]  */
        unsigned int dei_is_lossless : 1;      /* [15]  */
        unsigned int dei_cycbuf_en : 1;        /* [16]  */
        unsigned int reserved_0 : 6;           /* [22..17]  */
        unsigned int rfr_mirror : 1;           /* [23]  */
        unsigned int rfr_flip : 1;             /* [24]  */
        unsigned int rfr_pix_bitw : 1;         /* [25]  */
        unsigned int rfr_uv_invert : 1;        /* [26]  */
        unsigned int rfr_cmp_en : 1;           /* [27]  */
        unsigned int rfr_lcmp_en : 1;          /* [28]  */
        unsigned int rfr_fcmp_en : 1;          /* [29]  */
        unsigned int rfr_dither_en : 1;        /* [30]  */
        unsigned int rfr_dither_mode : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DEI_BUF_CTRL;

/* define the union U_VPSS_RCH_DEI_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dei_width : 16;  /* [15..0]  */
        unsigned int dei_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DEI_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_DEI_BUF_OFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dei_hor_offset : 16; /* [15..0]  */
        unsigned int dei_ver_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DEI_BUF_OFFSET;

/* define the union U_VPSS_RCH_DEI_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dei_y_stride : 16; /* [15..0]  */
        unsigned int dei_c_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DEI_BUF_STRIDE;

/* define the union U_VPSS_RCH_RC_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ree_format : 5;           /* [4..0]  */
        unsigned int ree_pix_bitw : 1;         /* [5]  */
        unsigned int ree_uv_invert : 1;        /* [6]  */
        unsigned int ree_tile_format : 1;      /* [7]  */
        unsigned int ree_vifir_en : 1;         /* [8]  */
        unsigned int ree_vdfir_en : 1;         /* [9]  */
        unsigned int ree_dcmp_en : 1;          /* [10]  */
        unsigned int ree_ldcmp_en : 1;         /* [11]  */
        unsigned int ree_fdcmp_en : 1;         /* [12]  */
        unsigned int ree_fdcmp_mode : 1;       /* [13]  */
        unsigned int ree_fdcmp_store_mode : 1; /* [14]  */
        unsigned int ree_is_lossless : 1;      /* [15]  */
        unsigned int rc_cycbuf_en : 1;         /* [16]  */
        unsigned int reserved_0 : 6;           /* [22..17]  */
        unsigned int cue_mirror : 1;           /* [23]  */
        unsigned int cue_flip : 1;             /* [24]  */
        unsigned int cue_pix_bitw : 1;         /* [25]  */
        unsigned int cue_uv_invert : 1;        /* [26]  */
        unsigned int cue_cmp_en : 1;           /* [27]  */
        unsigned int cue_lcmp_en : 1;          /* [28]  */
        unsigned int cue_fcmp_en : 1;          /* [29]  */
        unsigned int cue_dither_en : 1;        /* [30]  */
        unsigned int cue_dither_mode : 1;      /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RC_BUF_CTRL;

/* define the union U_VPSS_RCH_RC_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rc_width : 16;  /* [15..0]  */
        unsigned int rc_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RC_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_RC_BUF_OFFSET */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rc_hor_offset : 16; /* [15..0]  */
        unsigned int rc_ver_offset : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RC_BUF_OFFSET;

/* define the union U_VPSS_RCH_RC_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rc_y_stride : 16; /* [15..0]  */
        unsigned int rc_c_stride : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RC_BUF_STRIDE;

/* define the union U_VPSS_RCH_NRMD_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int nrmd_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_NRMD_BUF_CTRL;

/* define the union U_VPSS_RCH_NRMD_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int nrmd_width : 16;  /* [15..0]  */
        unsigned int nrmd_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_NRMD_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_NRMD_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int nrmd_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_NRMD_BUF_STRIDE;

/* define the union U_VPSS_RCH_PRJH_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int prjh_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_PRJH_BUF_CTRL;

/* define the union U_VPSS_RCH_PRJH_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int prjh_width : 16;  /* [15..0]  */
        unsigned int prjh_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_PRJH_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_PRJH_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int prjh_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_PRJH_BUF_STRIDE;

/* define the union U_VPSS_RCH_DIMD_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dimd_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DIMD_BUF_CTRL;

/* define the union U_VPSS_RCH_DIMD_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dimd_width : 16;  /* [15..0]  */
        unsigned int dimd_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DIMD_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_DIMD_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int dimd_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_DIMD_BUF_STRIDE;

/* define the union U_VPSS_RCH_PRJV_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int prjv_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_PRJV_BUF_CTRL;

/* define the union U_VPSS_RCH_PRJV_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int prjv_width : 16;  /* [15..0]  */
        unsigned int prjv_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_PRJV_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_PRJV_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int prjv_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_PRJV_BUF_STRIDE;

/* define the union U_VPSS_RCH_RGMV_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rgmv_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RGMV_BUF_CTRL;

/* define the union U_VPSS_RCH_RGMV_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rgmv_width : 16;  /* [15..0]  */
        unsigned int rgmv_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RGMV_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_RGMV_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rgmv_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_RGMV_BUF_STRIDE;

/* define the union U_VPSS_RCH_BLKMT_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int blkmt_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;     /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_BLKMT_BUF_CTRL;

/* define the union U_VPSS_RCH_BLKMT_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int blkmt_width : 16;  /* [15..0]  */
        unsigned int blkmt_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_BLKMT_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_BLKMT_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int blkmt_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_BLKMT_BUF_STRIDE;

/* define the union U_VPSS_RCH_BLKMV_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int blkmv_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;     /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_BLKMV_BUF_CTRL;

/* define the union U_VPSS_RCH_BLKMV_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int blkmv_width : 16;  /* [15..0]  */
        unsigned int blkmv_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_BLKMV_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_BLKMV_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int blkmv_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_BLKMV_BUF_STRIDE;

/* define the union U_VPSS_RCH_CNT_BUF_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cccl_cnt_cycbuf_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;        /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_CNT_BUF_CTRL;

/* define the union U_VPSS_RCH_CNT_BUF_IMGSIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cccl_cnt_width : 16;  /* [15..0]  */
        unsigned int cccl_cnt_height : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_CNT_BUF_IMGSIZE;

/* define the union U_VPSS_RCH_CNT_BUF_STRIDE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cccl_cnt_stride : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RCH_CNT_BUF_STRIDE;

/* define the union U_VPSS_RFR_Y_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_is_lossless : 1; /* [0]  */
        unsigned int rfr_y_cmp_mode : 1;    /* [1]  */
        unsigned int rfr_y_dw_mode : 1;     /* [2]  */
        unsigned int rfr_y_part_cmp_en : 1; /* [3]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_GLB_INFO;

/* define the union U_VPSS_RFR_Y_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;          /* [15..13]  */
        unsigned int rfr_y_frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;          /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_FRAME_SIZE;

/* define the union U_VPSS_RFR_Y_RC_CFG0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_mb_bits : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6;         /* [15..10]  */
        unsigned int rfr_y_min_mb_bits : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;         /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG0;

/* define the union U_VPSS_RFR_Y_RC_CFG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_max_qp : 4;        /* [3..0]  */
        unsigned int reserved_0 : 4;          /* [7..4]  */
        unsigned int rfr_y_sad_bits_gain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;          /* [15..12]  */
        unsigned int rfr_y_rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5;          /* [23..19]  */
        unsigned int rfr_y_max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG1;

/* define the union U_VPSS_RFR_Y_RC_CFG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9;        /* [15..7]  */
        unsigned int rfr_y_min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9;        /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG2;

/* define the union U_VPSS_RFR_Y_RC_CFG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_smth_thr : 7;      /* [6..0]  */
        unsigned int reserved_0 : 1;          /* [7]  */
        unsigned int rfr_y_still_thr : 7;     /* [14..8]  */
        unsigned int reserved_1 : 1;          /* [15]  */
        unsigned int rfr_y_big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG3;

/* define the union U_VPSS_RFR_Y_RC_CFG4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_smth_pix_num_thr : 6;  /* [5..0]  */
        unsigned int reserved_0 : 2;              /* [7..6]  */
        unsigned int rfr_y_still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;              /* [15..14]  */
        unsigned int rfr_y_noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;             /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG4;

/* define the union U_VPSS_RFR_Y_RC_CFG5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_noise_sad : 7;     /* [6..0]  */
        unsigned int reserved_0 : 9;          /* [15..7]  */
        unsigned int rfr_y_pix_diff_thr : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG5;

/* define the union U_VPSS_RFR_Y_RC_CFG6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;            /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG6;

/* define the union U_VPSS_RFR_Y_RC_CFG7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_qp_inc1_bits_thr : 8; /* [7..0]  */
        unsigned int rfr_y_qp_inc2_bits_thr : 8; /* [15..8]  */
        unsigned int rfr_y_qp_dec1_bits_thr : 8; /* [23..16]  */
        unsigned int rfr_y_qp_dec2_bits_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG7;

/* define the union U_VPSS_RFR_Y_RC_CFG8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_est_err_gain : 5;      /* [4..0]  */
        unsigned int reserved_0 : 11;             /* [15..5]  */
        unsigned int rfr_y_max_est_err_level : 9; /* [24..16]  */
        unsigned int reserved_1 : 7;              /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG8;

/* define the union U_VPSS_RFR_Y_RC_CFG9 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16;             /* [15..0]  */
        unsigned int rfr_y_vbv_buf_loss1_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 1;              /* [23]  */
        unsigned int rfr_y_vbv_buf_loss2_thr : 7; /* [30..24]  */
        unsigned int reserved_2 : 1;              /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_RC_CFG9;

/* define the union U_VPSS_RFR_Y_STAT_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_max_gap_bw_row_len_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;                  /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_STAT_THR;

/* define the union U_VPSS_RFR_Y_PCMP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_pcmp_start_hpos : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;             /* [15..13]  */
        unsigned int rfr_y_pcmp_end_hpos : 13;   /* [28..16]  */
        unsigned int reserved_1 : 3;             /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_PCMP;

/* define the union U_VPSS_RFR_Y_BS_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_frame_size_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;           /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_BS_SIZE;

/* define the union U_VPSS_RFR_Y_WORST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_max_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_WORST_ROW;

/* define the union U_VPSS_RFR_Y_BEST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_min_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_BEST_ROW;

/* define the union U_VPSS_RFR_Y_STAT_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_y_max_gap_bw_row_len_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;                   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_Y_STAT_INFO;

/* define the union U_VPSS_RFR_C_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_is_lossless : 1; /* [0]  */
        unsigned int rfr_c_cmp_mode : 1;    /* [1]  */
        unsigned int rfr_c_dw_mode : 1;     /* [2]  */
        unsigned int rfr_c_part_cmp_en : 1; /* [3]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_GLB_INFO;

/* define the union U_VPSS_RFR_C_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;          /* [15..13]  */
        unsigned int rfr_c_frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;          /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_FRAME_SIZE;

/* define the union U_VPSS_RFR_C_RC_CFG0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_mb_bits : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6;         /* [15..10]  */
        unsigned int rfr_c_min_mb_bits : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;         /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG0;

/* define the union U_VPSS_RFR_C_RC_CFG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_max_qp : 4;        /* [3..0]  */
        unsigned int reserved_0 : 4;          /* [7..4]  */
        unsigned int rfr_c_sad_bits_gain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;          /* [15..12]  */
        unsigned int rfr_c_rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5;          /* [23..19]  */
        unsigned int rfr_c_max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG1;

/* define the union U_VPSS_RFR_C_RC_CFG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9;        /* [15..7]  */
        unsigned int rfr_c_min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9;        /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG2;

/* define the union U_VPSS_RFR_C_RC_CFG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_smth_thr : 7;      /* [6..0]  */
        unsigned int reserved_0 : 1;          /* [7]  */
        unsigned int rfr_c_still_thr : 7;     /* [14..8]  */
        unsigned int reserved_1 : 1;          /* [15]  */
        unsigned int rfr_c_big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG3;

/* define the union U_VPSS_RFR_C_RC_CFG4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_smth_pix_num_thr : 6;  /* [5..0]  */
        unsigned int reserved_0 : 2;              /* [7..6]  */
        unsigned int rfr_c_still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;              /* [15..14]  */
        unsigned int rfr_c_noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;             /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG4;

/* define the union U_VPSS_RFR_C_RC_CFG5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_noise_sad : 7;     /* [6..0]  */
        unsigned int reserved_0 : 9;          /* [15..7]  */
        unsigned int rfr_c_pix_diff_thr : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG5;

/* define the union U_VPSS_RFR_C_RC_CFG6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;            /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG6;

/* define the union U_VPSS_RFR_C_RC_CFG7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_qp_inc1_bits_thr : 8; /* [7..0]  */
        unsigned int rfr_c_qp_inc2_bits_thr : 8; /* [15..8]  */
        unsigned int rfr_c_qp_dec1_bits_thr : 8; /* [23..16]  */
        unsigned int rfr_c_qp_dec2_bits_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG7;

/* define the union U_VPSS_RFR_C_RC_CFG8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_est_err_gain : 5;      /* [4..0]  */
        unsigned int reserved_0 : 11;             /* [15..5]  */
        unsigned int rfr_c_max_est_err_level : 9; /* [24..16]  */
        unsigned int reserved_1 : 7;              /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG8;

/* define the union U_VPSS_RFR_C_RC_CFG9 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16;             /* [15..0]  */
        unsigned int rfr_c_vbv_buf_loss1_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 1;              /* [23]  */
        unsigned int rfr_c_vbv_buf_loss2_thr : 7; /* [30..24]  */
        unsigned int reserved_2 : 1;              /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_RC_CFG9;

/* define the union U_VPSS_RFR_C_STAT_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_max_gap_bw_row_len_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;                  /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_STAT_THR;

/* define the union U_VPSS_RFR_C_PCMP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_pcmp_start_hpos : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;             /* [15..13]  */
        unsigned int rfr_c_pcmp_end_hpos : 13;   /* [28..16]  */
        unsigned int reserved_1 : 3;             /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_PCMP;

/* define the union U_VPSS_RFR_C_BS_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_frame_size_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;           /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_BS_SIZE;

/* define the union U_VPSS_RFR_C_WORST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_max_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_WORST_ROW;

/* define the union U_VPSS_RFR_C_BEST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_min_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_BEST_ROW;

/* define the union U_VPSS_RFR_C_STAT_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int rfr_c_max_gap_bw_row_len_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;                   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_RFR_C_STAT_INFO;

/* define the union U_VPSS_CUE_Y_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_is_lossless : 1; /* [0]  */
        unsigned int cue_y_cmp_mode : 1;    /* [1]  */
        unsigned int cue_y_dw_mode : 1;     /* [2]  */
        unsigned int cue_y_part_cmp_en : 1; /* [3]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_GLB_INFO;

/* define the union U_VPSS_CUE_Y_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;          /* [15..13]  */
        unsigned int cue_y_frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;          /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_FRAME_SIZE;

/* define the union U_VPSS_CUE_Y_RC_CFG0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_mb_bits : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6;         /* [15..10]  */
        unsigned int cue_y_min_mb_bits : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;         /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG0;

/* define the union U_VPSS_CUE_Y_RC_CFG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_max_qp : 4;        /* [3..0]  */
        unsigned int reserved_0 : 4;          /* [7..4]  */
        unsigned int cue_y_sad_bits_gain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;          /* [15..12]  */
        unsigned int cue_y_rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5;          /* [23..19]  */
        unsigned int cue_y_max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG1;

/* define the union U_VPSS_CUE_Y_RC_CFG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9;        /* [15..7]  */
        unsigned int cue_y_min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9;        /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG2;

/* define the union U_VPSS_CUE_Y_RC_CFG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_smth_thr : 7;      /* [6..0]  */
        unsigned int reserved_0 : 1;          /* [7]  */
        unsigned int cue_y_still_thr : 7;     /* [14..8]  */
        unsigned int reserved_1 : 1;          /* [15]  */
        unsigned int cue_y_big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG3;

/* define the union U_VPSS_CUE_Y_RC_CFG4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_smth_pix_num_thr : 6;  /* [5..0]  */
        unsigned int reserved_0 : 2;              /* [7..6]  */
        unsigned int cue_y_still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;              /* [15..14]  */
        unsigned int cue_y_noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;             /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG4;

/* define the union U_VPSS_CUE_Y_RC_CFG5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_noise_sad : 7;     /* [6..0]  */
        unsigned int reserved_0 : 9;          /* [15..7]  */
        unsigned int cue_y_pix_diff_thr : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG5;

/* define the union U_VPSS_CUE_Y_RC_CFG6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;            /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG6;

/* define the union U_VPSS_CUE_Y_RC_CFG7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_qp_inc1_bits_thr : 8; /* [7..0]  */
        unsigned int cue_y_qp_inc2_bits_thr : 8; /* [15..8]  */
        unsigned int cue_y_qp_dec1_bits_thr : 8; /* [23..16]  */
        unsigned int cue_y_qp_dec2_bits_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG7;

/* define the union U_VPSS_CUE_Y_RC_CFG8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_est_err_gain : 5;      /* [4..0]  */
        unsigned int reserved_0 : 11;             /* [15..5]  */
        unsigned int cue_y_max_est_err_level : 9; /* [24..16]  */
        unsigned int reserved_1 : 7;              /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG8;

/* define the union U_VPSS_CUE_Y_RC_CFG9 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16;             /* [15..0]  */
        unsigned int cue_y_vbv_buf_loss1_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 1;              /* [23]  */
        unsigned int cue_y_vbv_buf_loss2_thr : 7; /* [30..24]  */
        unsigned int reserved_2 : 1;              /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_RC_CFG9;

/* define the union U_VPSS_CUE_Y_STAT_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_max_gap_bw_row_len_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;                  /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_STAT_THR;

/* define the union U_VPSS_CUE_Y_PCMP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_pcmp_start_hpos : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;             /* [15..13]  */
        unsigned int cue_y_pcmp_end_hpos : 13;   /* [28..16]  */
        unsigned int reserved_1 : 3;             /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_PCMP;

/* define the union U_VPSS_CUE_Y_BS_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_frame_size_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;           /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_BS_SIZE;

/* define the union U_VPSS_CUE_Y_WORST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_max_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_WORST_ROW;

/* define the union U_VPSS_CUE_Y_BEST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_min_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_BEST_ROW;

/* define the union U_VPSS_CUE_Y_STAT_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_y_max_gap_bw_row_len_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;                   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_Y_STAT_INFO;

/* define the union U_VPSS_CUE_C_GLB_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_is_lossless : 1; /* [0]  */
        unsigned int cue_c_cmp_mode : 1;    /* [1]  */
        unsigned int cue_c_dw_mode : 1;     /* [2]  */
        unsigned int cue_c_part_cmp_en : 1; /* [3]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_GLB_INFO;

/* define the union U_VPSS_CUE_C_FRAME_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_frame_width : 13;  /* [12..0]  */
        unsigned int reserved_0 : 3;          /* [15..13]  */
        unsigned int cue_c_frame_height : 13; /* [28..16]  */
        unsigned int reserved_1 : 3;          /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_FRAME_SIZE;

/* define the union U_VPSS_CUE_C_RC_CFG0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_mb_bits : 10;     /* [9..0]  */
        unsigned int reserved_0 : 6;         /* [15..10]  */
        unsigned int cue_c_min_mb_bits : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;         /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG0;

/* define the union U_VPSS_CUE_C_RC_CFG1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_max_qp : 4;        /* [3..0]  */
        unsigned int reserved_0 : 4;          /* [7..4]  */
        unsigned int cue_c_sad_bits_gain : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;          /* [15..12]  */
        unsigned int cue_c_rc_smth_ngain : 3; /* [18..16]  */
        unsigned int reserved_2 : 5;          /* [23..19]  */
        unsigned int cue_c_max_trow_bits : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG1;

/* define the union U_VPSS_CUE_C_RC_CFG2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_max_sad_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 9;        /* [15..7]  */
        unsigned int cue_c_min_sad_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 9;        /* [31..23]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG2;

/* define the union U_VPSS_CUE_C_RC_CFG3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_smth_thr : 7;      /* [6..0]  */
        unsigned int reserved_0 : 1;          /* [7]  */
        unsigned int cue_c_still_thr : 7;     /* [14..8]  */
        unsigned int reserved_1 : 1;          /* [15]  */
        unsigned int cue_c_big_grad_thr : 10; /* [25..16]  */
        unsigned int reserved_2 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG3;

/* define the union U_VPSS_CUE_C_RC_CFG4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_smth_pix_num_thr : 6;  /* [5..0]  */
        unsigned int reserved_0 : 2;              /* [7..6]  */
        unsigned int cue_c_still_pix_num_thr : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;              /* [15..14]  */
        unsigned int cue_c_noise_pix_num_thr : 6; /* [21..16]  */
        unsigned int reserved_2 : 10;             /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG4;

/* define the union U_VPSS_CUE_C_RC_CFG5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_noise_sad : 7;     /* [6..0]  */
        unsigned int reserved_0 : 9;          /* [15..7]  */
        unsigned int cue_c_pix_diff_thr : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;          /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG5;

/* define the union U_VPSS_CUE_C_RC_CFG6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_adj_sad_bits_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;            /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG6;

/* define the union U_VPSS_CUE_C_RC_CFG7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_qp_inc1_bits_thr : 8; /* [7..0]  */
        unsigned int cue_c_qp_inc2_bits_thr : 8; /* [15..8]  */
        unsigned int cue_c_qp_dec1_bits_thr : 8; /* [23..16]  */
        unsigned int cue_c_qp_dec2_bits_thr : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG7;

/* define the union U_VPSS_CUE_C_RC_CFG8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_est_err_gain : 5;      /* [4..0]  */
        unsigned int reserved_0 : 11;             /* [15..5]  */
        unsigned int cue_c_max_est_err_level : 9; /* [24..16]  */
        unsigned int reserved_1 : 7;              /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG8;

/* define the union U_VPSS_CUE_C_RC_CFG9 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 16;             /* [15..0]  */
        unsigned int cue_c_vbv_buf_loss1_thr : 7; /* [22..16]  */
        unsigned int reserved_1 : 1;              /* [23]  */
        unsigned int cue_c_vbv_buf_loss2_thr : 7; /* [30..24]  */
        unsigned int reserved_2 : 1;              /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_RC_CFG9;

/* define the union U_VPSS_CUE_C_STAT_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_max_gap_bw_row_len_thr : 7; /* [6..0]  */
        unsigned int reserved_0 : 25;                  /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_STAT_THR;

/* define the union U_VPSS_CUE_C_PCMP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_pcmp_start_hpos : 13; /* [12..0]  */
        unsigned int reserved_0 : 3;             /* [15..13]  */
        unsigned int cue_c_pcmp_end_hpos : 13;   /* [28..16]  */
        unsigned int reserved_1 : 3;             /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_PCMP;

/* define the union U_VPSS_CUE_C_BS_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_frame_size_reg : 22; /* [21..0]  */
        unsigned int reserved_0 : 10;           /* [31..22]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_BS_SIZE;

/* define the union U_VPSS_CUE_C_WORST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_max_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_WORST_ROW;

/* define the union U_VPSS_CUE_C_BEST_ROW */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_min_frm_row_len : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_BEST_ROW;

/* define the union U_VPSS_CUE_C_STAT_INFO */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cue_c_max_gap_bw_row_len_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;                   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VPSS_CUE_C_STAT_INFO;

/* define the global struct */
typedef struct {
    volatile U_VOCTRL VOCTRL;                                                           /* 0x0 */
    volatile U_VOINTSTA VOINTSTA;                                                       /* 0x4 */
    volatile U_VOMSKINTSTA VOMSKINTSTA;                                                 /* 0x8 */
    volatile U_VOINTMSK VOINTMSK;                                                       /* 0xc */
    volatile U_VODEBUG VODEBUG;                                                         /* 0x10 */
    volatile U_VOINTSTA1 VOINTSTA1;                                                     /* 0x14 */
    volatile U_VOMSKINTSTA1 VOMSKINTSTA1;                                               /* 0x18 */
    volatile U_VOINTMSK1 VOINTMSK1;                                                     /* 0x1c */
    volatile unsigned int VDPVERSION1;                                                  /* 0x20 */
    volatile unsigned int VDPVERSION2;                                                  /* 0x24 */
    volatile U_VOLOWPOWER_CTRL VOLOWPOWER_CTRL;                                         /* 0x28 */
    volatile U_VOUFSTA VOUFSTA;                                                         /* 0x2c */
    volatile U_VOUFCLR VOUFCLR;                                                         /* 0x30 */
    volatile U_VOINTPROC_TIM VOINTPROC_TIM;                                             /* 0x34 */
    volatile unsigned int VOFPGATEST;                                                   /* 0x38 */
    volatile unsigned int reserved_0[3];                                                /* 0x3c~0x44 */
    volatile U_VOLOWPOWER_CTRL1 VOLOWPOWER_CTRL1;                                       /* 0x48 */
    volatile U_VOFPGADEF VOFPGADEF;                                                     /* 0x4c */
    volatile unsigned int reserved_1[172];                                              /* 0x50~0x2fc */
    volatile U_CBM_BKG1 CBM_BKG1;                                                       /* 0x300 */
    volatile unsigned int reserved_2;                                                   /* 0x304 */
    volatile U_CBM_MIX1 CBM_MIX1;                                                       /* 0x308 */
    volatile unsigned int reserved_3[14];                                               /* 0x30c~0x340 */
    volatile U_WBC_BMP_THD WBC_BMP_THD;                                                 /* 0x344 */
    volatile unsigned int reserved_4[14];                                               /* 0x348~0x37c */
    volatile U_CBM_BKG2 CBM_BKG2;                                                       /* 0x380 */
    volatile unsigned int reserved_5;                                                   /* 0x384 */
    volatile U_CBM_MIX2 CBM_MIX2;                                                       /* 0x388 */
    volatile unsigned int reserved_6[14];                                               /* 0x38c~0x3c0 */
    volatile U_HC_BMP_THD HC_BMP_THD;                                                   /* 0x3c4 */
    volatile unsigned int reserved_7[14];                                               /* 0x3c8~0x3fc */
    volatile U_CBM_BKG3 CBM_BKG3;                                                       /* 0x400 */
    volatile unsigned int reserved_8;                                                   /* 0x404 */
    volatile U_CBM_MIX3 CBM_MIX3;                                                       /* 0x408 */
    volatile unsigned int reserved_9[125];                                              /* 0x40c~0x5fc */
    volatile U_MIXV0_BKG MIXV0_BKG;                                                     /* 0x600 */
    volatile unsigned int reserved_10;                                                  /* 0x604 */
    volatile U_MIXV0_MIX MIXV0_MIX;                                                     /* 0x608 */
    volatile unsigned int reserved_11[189];                                             /* 0x60c~0x8fc */
    volatile U_MIXG0_BKG MIXG0_BKG;                                                     /* 0x900 */
    volatile U_MIXG0_BKALPHA MIXG0_BKALPHA;                                             /* 0x904 */
    volatile U_MIXG0_MIX MIXG0_MIX;                                                     /* 0x908 */
    volatile unsigned int reserved_12[189];                                             /* 0x90c~0xbfc */
    volatile U_LINK_CTRL LINK_CTRL;                                                     /* 0xc00 */
    volatile unsigned int reserved_13[63];                                              /* 0xc04~0xcfc */
    volatile U_VPSS_CTRL VPSS_CTRL;                                                     /* 0xd00 */
    volatile U_VPSS_MISCELLANEOUS VPSS_MISCELLANEOUS;                                   /* 0xd04 */
    volatile U_VPSS_FTCONFIG VPSS_FTCONFIG;                                             /* 0xd08 */
    volatile unsigned int reserved_14[6];                                               /* 0xd0c~0xd20 */
    volatile unsigned int VPSS_DEBUG0;                                                  /* 0xd24 */
    volatile unsigned int VPSS_DEBUG1;                                                  /* 0xd28 */
    volatile unsigned int VPSS_DEBUG2;                                                  /* 0xd2c */
    volatile unsigned int VPSS_DEBUG3;                                                  /* 0xd30 */
    volatile unsigned int VPSS_DEBUG4;                                                  /* 0xd34 */
    volatile unsigned int VPSS_DEBUG5;                                                  /* 0xd38 */
    volatile unsigned int VPSS_DEBUG6;                                                  /* 0xd3c */
    volatile unsigned int reserved_15[48];                                              /* 0xd40~0xdfc */
    volatile unsigned int PARA_HADDR_VHD_CHN00;                                         /* 0xe00 */
    volatile unsigned int PARA_ADDR_VHD_CHN00;                                          /* 0xe04 */
    volatile unsigned int PARA_HADDR_VHD_CHN01;                                         /* 0xe08 */
    volatile unsigned int PARA_ADDR_VHD_CHN01;                                          /* 0xe0c */
    volatile unsigned int PARA_HADDR_VHD_CHN02;                                         /* 0xe10 */
    volatile unsigned int PARA_ADDR_VHD_CHN02;                                          /* 0xe14 */
    volatile unsigned int PARA_HADDR_VHD_CHN03;                                         /* 0xe18 */
    volatile unsigned int PARA_ADDR_VHD_CHN03;                                          /* 0xe1c */
    volatile unsigned int PARA_HADDR_VHD_CHN04;                                         /* 0xe20 */
    volatile unsigned int PARA_ADDR_VHD_CHN04;                                          /* 0xe24 */
    volatile unsigned int PARA_HADDR_VHD_CHN05;                                         /* 0xe28 */
    volatile unsigned int PARA_ADDR_VHD_CHN05;                                          /* 0xe2c */
    volatile unsigned int PARA_HADDR_VHD_CHN06;                                         /* 0xe30 */
    volatile unsigned int PARA_ADDR_VHD_CHN06;                                          /* 0xe34 */
    volatile unsigned int PARA_HADDR_VHD_CHN07;                                         /* 0xe38 */
    volatile unsigned int PARA_ADDR_VHD_CHN07;                                          /* 0xe3c */
    volatile unsigned int PARA_HADDR_VHD_CHN08;                                         /* 0xe40 */
    volatile unsigned int PARA_ADDR_VHD_CHN08;                                          /* 0xe44 */
    volatile unsigned int PARA_HADDR_VHD_CHN09;                                         /* 0xe48 */
    volatile unsigned int PARA_ADDR_VHD_CHN09;                                          /* 0xe4c */
    volatile unsigned int PARA_HADDR_VHD_CHN10;                                         /* 0xe50 */
    volatile unsigned int PARA_ADDR_VHD_CHN10;                                          /* 0xe54 */
    volatile unsigned int PARA_HADDR_VHD_CHN11;                                         /* 0xe58 */
    volatile unsigned int PARA_ADDR_VHD_CHN11;                                          /* 0xe5c */
    volatile unsigned int PARA_HADDR_VHD_CHN12;                                         /* 0xe60 */
    volatile unsigned int PARA_ADDR_VHD_CHN12;                                          /* 0xe64 */
    volatile unsigned int PARA_HADDR_VHD_CHN13;                                         /* 0xe68 */
    volatile unsigned int PARA_ADDR_VHD_CHN13;                                          /* 0xe6c */
    volatile unsigned int PARA_HADDR_VHD_CHN14;                                         /* 0xe70 */
    volatile unsigned int PARA_ADDR_VHD_CHN14;                                          /* 0xe74 */
    volatile unsigned int PARA_HADDR_VHD_CHN15;                                         /* 0xe78 */
    volatile unsigned int PARA_ADDR_VHD_CHN15;                                          /* 0xe7c */
    volatile unsigned int PARA_HADDR_VHD_CHN16;                                         /* 0xe80 */
    volatile unsigned int PARA_ADDR_VHD_CHN16;                                          /* 0xe84 */
    volatile unsigned int PARA_HADDR_VHD_CHN17;                                         /* 0xe88 */
    volatile unsigned int PARA_ADDR_VHD_CHN17;                                          /* 0xe8c */
    volatile unsigned int PARA_HADDR_VHD_CHN18;                                         /* 0xe90 */
    volatile unsigned int PARA_ADDR_VHD_CHN18;                                          /* 0xe94 */
    volatile unsigned int PARA_HADDR_VHD_CHN19;                                         /* 0xe98 */
    volatile unsigned int PARA_ADDR_VHD_CHN19;                                          /* 0xe9c */
    volatile unsigned int PARA_HADDR_VHD_CHN20;                                         /* 0xea0 */
    volatile unsigned int PARA_ADDR_VHD_CHN20;                                          /* 0xea4 */
    volatile unsigned int PARA_HADDR_VHD_CHN21;                                         /* 0xea8 */
    volatile unsigned int PARA_ADDR_VHD_CHN21;                                          /* 0xeac */
    volatile unsigned int PARA_HADDR_VHD_CHN22;                                         /* 0xeb0 */
    volatile unsigned int PARA_ADDR_VHD_CHN22;                                          /* 0xeb4 */
    volatile unsigned int PARA_HADDR_VHD_CHN23;                                         /* 0xeb8 */
    volatile unsigned int PARA_ADDR_VHD_CHN23;                                          /* 0xebc */
    volatile unsigned int PARA_HADDR_VHD_CHN24;                                         /* 0xec0 */
    volatile unsigned int PARA_ADDR_VHD_CHN24;                                          /* 0xec4 */
    volatile unsigned int PARA_HADDR_VHD_CHN25;                                         /* 0xec8 */
    volatile unsigned int PARA_ADDR_VHD_CHN25;                                          /* 0xecc */
    volatile unsigned int PARA_HADDR_VHD_CHN26;                                         /* 0xed0 */
    volatile unsigned int PARA_ADDR_VHD_CHN26;                                          /* 0xed4 */
    volatile unsigned int PARA_HADDR_VHD_CHN27;                                         /* 0xed8 */
    volatile unsigned int PARA_ADDR_VHD_CHN27;                                          /* 0xedc */
    volatile unsigned int PARA_HADDR_VHD_CHN28;                                         /* 0xee0 */
    volatile unsigned int PARA_ADDR_VHD_CHN28;                                          /* 0xee4 */
    volatile unsigned int PARA_HADDR_VHD_CHN29;                                         /* 0xee8 */
    volatile unsigned int PARA_ADDR_VHD_CHN29;                                          /* 0xeec */
    volatile unsigned int PARA_HADDR_VHD_CHN30;                                         /* 0xef0 */
    volatile unsigned int PARA_ADDR_VHD_CHN30;                                          /* 0xef4 */
    volatile unsigned int PARA_HADDR_VHD_CHN31;                                         /* 0xef8 */
    volatile unsigned int PARA_ADDR_VHD_CHN31;                                          /* 0xefc */
    volatile U_PARA_UP_VHD PARA_UP_VHD;                                                 /* 0xf00 */
    volatile unsigned int PARA_HADDR_VSD_CHN00;                                         /* 0xf04 */
    volatile unsigned int PARA_ADDR_VSD_CHN00;                                          /* 0xf08 */
    volatile unsigned int PARA_HADDR_VSD_CHN01;                                         /* 0xf0c */
    volatile unsigned int PARA_ADDR_VSD_CHN01;                                          /* 0xf10 */
    volatile unsigned int PARA_HADDR_VSD_CHN02;                                         /* 0xf14 */
    volatile unsigned int PARA_ADDR_VSD_CHN02;                                          /* 0xf18 */
    volatile unsigned int PARA_HADDR_VSD_CHN03;                                         /* 0xf1c */
    volatile unsigned int PARA_ADDR_VSD_CHN03;                                          /* 0xf20 */
    volatile unsigned int PARA_HADDR_VSD_CHN04;                                         /* 0xf24 */
    volatile unsigned int PARA_ADDR_VSD_CHN04;                                          /* 0xf28 */
    volatile unsigned int PARA_HADDR_VSD_CHN05;                                         /* 0xf2c */
    volatile unsigned int PARA_ADDR_VSD_CHN05;                                          /* 0xf30 */
    volatile unsigned int PARA_HADDR_VSD_CHN06;                                         /* 0xf34 */
    volatile unsigned int PARA_ADDR_VSD_CHN06;                                          /* 0xf38 */
    volatile unsigned int PARA_HADDR_VSD_CHN07;                                         /* 0xf3c */
    volatile unsigned int PARA_ADDR_VSD_CHN07;                                          /* 0xf40 */
    volatile U_PARA_UP_VSD PARA_UP_VSD;                                                 /* 0xf44 */
    volatile U_PARA_CONFLICT_CLR PARA_CONFLICT_CLR;                                     /* 0xf48 */
    volatile U_PARA_CONFLICT_STA PARA_CONFLICT_STA;                                     /* 0xf4c */
    volatile unsigned int reserved_16[44];                                              /* 0xf50~0xffc */
    volatile U_V0_CTRL V0_CTRL;                                                         /* 0x1000 */
    volatile U_V0_UPD V0_UPD;                                                           /* 0x1004 */
    volatile U_V0_0RESO_READ V0_0RESO_READ;                                             /* 0x1008 */
    volatile unsigned int reserved_17[29];                                              /* 0x100c~0x107c */
    volatile U_V0_DFPOS V0_DFPOS;                                                       /* 0x1080 */
    volatile U_V0_DLPOS V0_DLPOS;                                                       /* 0x1084 */
    volatile U_V0_VFPOS V0_VFPOS;                                                       /* 0x1088 */
    volatile U_V0_VLPOS V0_VLPOS;                                                       /* 0x108c */
    volatile U_V0_BK V0_BK;                                                             /* 0x1090 */
    volatile U_V0_ALPHA V0_ALPHA;                                                       /* 0x1094 */
    volatile U_V0_MUTE_BK V0_MUTE_BK;                                                   /* 0x1098 */
    volatile unsigned int reserved_18;                                                  /* 0x109c */
    volatile U_V0_RIMWIDTH V0_RIMWIDTH;                                                 /* 0x10a0 */
    volatile U_V0_RIMCOL0 V0_RIMCOL0;                                                   /* 0x10a4 */
    volatile U_V0_RIMCOL1 V0_RIMCOL1;                                                   /* 0x10a8 */
    volatile unsigned int reserved_19[149];                                             /* 0x10ac~0x12fc */
    volatile U_V0_ZME_HINFO V0_ZME_HINFO;                                               /* 0x1300 */
    volatile U_V0_ZME_HSP V0_ZME_HSP;                                                   /* 0x1304 */
    volatile U_V0_ZME_HLOFFSET V0_ZME_HLOFFSET;                                         /* 0x1308 */
    volatile U_V0_ZME_HCOFFSET V0_ZME_HCOFFSET;                                         /* 0x130c */
    volatile U_V0_ZME_HZONE0DELTA V0_ZME_HZONE0DELTA;                                   /* 0x1310 */
    volatile U_V0_ZME_HZONE2DELTA V0_ZME_HZONE2DELTA;                                   /* 0x1314 */
    volatile U_V0_ZME_HZONEEND V0_ZME_HZONEEND;                                         /* 0x1318 */
    volatile U_V0_ZME_HL_SHOOTCTRL V0_ZME_HL_SHOOTCTRL;                                 /* 0x131c */
    volatile U_V0_ZME_HC_SHOOTCTRL V0_ZME_HC_SHOOTCTRL;                                 /* 0x1320 */
    volatile U_V0_ZME_HCOEF_REN V0_ZME_HCOEF_REN;                                       /* 0x1324 */
    volatile U_V0_ZME_HCOEF_RDATA V0_ZME_HCOEF_RDATA;                                   /* 0x1328 */
    volatile unsigned int reserved_20[53];                                              /* 0x132c~0x13fc */
    volatile U_V0_ZME_VINFO V0_ZME_VINFO;                                               /* 0x1400 */
    volatile U_V0_ZME_VSP V0_ZME_VSP;                                                   /* 0x1404 */
    volatile U_V0_ZME_VOFFSET V0_ZME_VOFFSET;                                           /* 0x1408 */
    volatile U_V0_ZME_VBOFFSET V0_ZME_VBOFFSET;                                         /* 0x140c */
    volatile unsigned int reserved_21[3];                                               /* 0x1410~0x1418 */
    volatile U_V0_ZME_VL_SHOOTCTRL V0_ZME_VL_SHOOTCTRL;                                 /* 0x141c */
    volatile U_V0_ZME_VC_SHOOTCTRL V0_ZME_VC_SHOOTCTRL;                                 /* 0x1420 */
    volatile U_V0_ZME_VCOEF_REN V0_ZME_VCOEF_REN;                                       /* 0x1424 */
    volatile U_V0_ZME_VCOEF_RDATA V0_ZME_VCOEF_RDATA;                                   /* 0x1428 */
    volatile unsigned int reserved_22[53];                                              /* 0x142c~0x14fc */
    volatile U_V0_HFIR_CTRL V0_HFIR_CTRL;                                               /* 0x1500 */
    volatile U_V0_HFIRCOEF01 V0_HFIRCOEF01;                                             /* 0x1504 */
    volatile U_V0_HFIRCOEF23 V0_HFIRCOEF23;                                             /* 0x1508 */
    volatile U_V0_HFIRCOEF45 V0_HFIRCOEF45;                                             /* 0x150c */
    volatile U_V0_HFIRCOEF67 V0_HFIRCOEF67;                                             /* 0x1510 */
    volatile unsigned int reserved_23[699];                                             /* 0x1514~0x1ffc */
    volatile U_V1_CTRL V1_CTRL;                                                         /* 0x2000 */
    volatile U_V1_UPD V1_UPD;                                                           /* 0x2004 */
    volatile U_V1_0RESO_READ V1_0RESO_READ;                                             /* 0x2008 */
    volatile unsigned int reserved_24[29];                                              /* 0x200c~0x207c */
    volatile U_V1_DFPOS V1_DFPOS;                                                       /* 0x2080 */
    volatile U_V1_DLPOS V1_DLPOS;                                                       /* 0x2084 */
    volatile U_V1_VFPOS V1_VFPOS;                                                       /* 0x2088 */
    volatile U_V1_VLPOS V1_VLPOS;                                                       /* 0x208c */
    volatile U_V1_BK V1_BK;                                                             /* 0x2090 */
    volatile U_V1_ALPHA V1_ALPHA;                                                       /* 0x2094 */
    volatile U_V1_MUTE_BK V1_MUTE_BK;                                                   /* 0x2098 */
    volatile unsigned int reserved_25;                                                  /* 0x209c */
    volatile U_V1_RIMWIDTH V1_RIMWIDTH;                                                 /* 0x20a0 */
    volatile U_V1_RIMCOL0 V1_RIMCOL0;                                                   /* 0x20a4 */
    volatile U_V1_RIMCOL1 V1_RIMCOL1;                                                   /* 0x20a8 */
    volatile unsigned int reserved_26[85];                                              /* 0x20ac~0x21fc */
    volatile U_V1_CSC_IDC V1_CSC_IDC;                                                   /* 0x2200 */
    volatile U_V1_CSC_ODC V1_CSC_ODC;                                                   /* 0x2204 */
    volatile U_V1_CSC_IODC V1_CSC_IODC;                                                 /* 0x2208 */
    volatile U_V1_CSC_P0 V1_CSC_P0;                                                     /* 0x220c */
    volatile U_V1_CSC_P1 V1_CSC_P1;                                                     /* 0x2210 */
    volatile U_V1_CSC_P2 V1_CSC_P2;                                                     /* 0x2214 */
    volatile U_V1_CSC_P3 V1_CSC_P3;                                                     /* 0x2218 */
    volatile U_V1_CSC_P4 V1_CSC_P4;                                                     /* 0x221c */
    volatile U_V1_CSC1_IDC V1_CSC1_IDC;                                                 /* 0x2220 */
    volatile U_V1_CSC1_ODC V1_CSC1_ODC;                                                 /* 0x2224 */
    volatile U_V1_CSC1_IODC V1_CSC1_IODC;                                               /* 0x2228 */
    volatile U_V1_CSC1_P0 V1_CSC1_P0;                                                   /* 0x222c */
    volatile U_V1_CSC1_P1 V1_CSC1_P1;                                                   /* 0x2230 */
    volatile U_V1_CSC1_P2 V1_CSC1_P2;                                                   /* 0x2234 */
    volatile U_V1_CSC1_P3 V1_CSC1_P3;                                                   /* 0x2238 */
    volatile U_V1_CSC1_P4 V1_CSC1_P4;                                                   /* 0x223c */
    volatile unsigned int reserved_27[112];                                             /* 0x2240~0x23fc */
    volatile U_V1_CVFIR_VINFO V1_CVFIR_VINFO;                                           /* 0x2400 */
    volatile U_V1_CVFIR_VSP V1_CVFIR_VSP;                                               /* 0x2404 */
    volatile U_V1_CVFIR_VOFFSET V1_CVFIR_VOFFSET;                                       /* 0x2408 */
    volatile U_V1_CVFIR_VBOFFSET V1_CVFIR_VBOFFSET;                                     /* 0x240c */
    volatile unsigned int reserved_28[8];                                               /* 0x2410~0x242c */
    volatile U_V1_CVFIR_VCOEF0 V1_CVFIR_VCOEF0;                                         /* 0x2430 */
    volatile U_V1_CVFIR_VCOEF1 V1_CVFIR_VCOEF1;                                         /* 0x2434 */
    volatile U_V1_CVFIR_VCOEF2 V1_CVFIR_VCOEF2;                                         /* 0x2438 */
    volatile unsigned int reserved_29[49];                                              /* 0x243c~0x24fc */
    volatile U_V1_HFIR_CTRL V1_HFIR_CTRL;                                               /* 0x2500 */
    volatile U_V1_HFIRCOEF01 V1_HFIRCOEF01;                                             /* 0x2504 */
    volatile U_V1_HFIRCOEF23 V1_HFIRCOEF23;                                             /* 0x2508 */
    volatile U_V1_HFIRCOEF45 V1_HFIRCOEF45;                                             /* 0x250c */
    volatile U_V1_HFIRCOEF67 V1_HFIRCOEF67;                                             /* 0x2510 */
    volatile unsigned int reserved_30[699];                                             /* 0x2514~0x2ffc */
    volatile U_V2_CTRL V2_CTRL;                                                         /* 0x3000 */
    volatile U_V2_UPD V2_UPD;                                                           /* 0x3004 */
    volatile U_V2_0RESO_READ V2_0RESO_READ;                                             /* 0x3008 */
    volatile unsigned int reserved_31[29];                                              /* 0x300c~0x307c */
    volatile U_V2_DFPOS V2_DFPOS;                                                       /* 0x3080 */
    volatile U_V2_DLPOS V2_DLPOS;                                                       /* 0x3084 */
    volatile U_V2_VFPOS V2_VFPOS;                                                       /* 0x3088 */
    volatile U_V2_VLPOS V2_VLPOS;                                                       /* 0x308c */
    volatile U_V2_BK V2_BK;                                                             /* 0x3090 */
    volatile U_V2_ALPHA V2_ALPHA;                                                       /* 0x3094 */
    volatile U_V2_MUTE_BK V2_MUTE_BK;                                                   /* 0x3098 */
    volatile U_V2_LBOX_CTRL V2_LBOX_CTRL;                                               /* 0x309c */
    volatile unsigned int reserved_32[88];                                              /* 0x30a0~0x31fc */
    volatile U_V2_CSC_IDC V2_CSC_IDC;                                                   /* 0x3200 */
    volatile U_V2_CSC_ODC V2_CSC_ODC;                                                   /* 0x3204 */
    volatile U_V2_CSC_IODC V2_CSC_IODC;                                                 /* 0x3208 */
    volatile U_V2_CSC_P0 V2_CSC_P0;                                                     /* 0x320c */
    volatile U_V2_CSC_P1 V2_CSC_P1;                                                     /* 0x3210 */
    volatile U_V2_CSC_P2 V2_CSC_P2;                                                     /* 0x3214 */
    volatile U_V2_CSC_P3 V2_CSC_P3;                                                     /* 0x3218 */
    volatile U_V2_CSC_P4 V2_CSC_P4;                                                     /* 0x321c */
    volatile U_V2_CSC1_IDC V2_CSC1_IDC;                                                 /* 0x3220 */
    volatile U_V2_CSC1_ODC V2_CSC1_ODC;                                                 /* 0x3224 */
    volatile U_V2_CSC1_IODC V2_CSC1_IODC;                                               /* 0x3228 */
    volatile U_V2_CSC1_P0 V2_CSC1_P0;                                                   /* 0x322c */
    volatile U_V2_CSC1_P1 V2_CSC1_P1;                                                   /* 0x3230 */
    volatile U_V2_CSC1_P2 V2_CSC1_P2;                                                   /* 0x3234 */
    volatile U_V2_CSC1_P3 V2_CSC1_P3;                                                   /* 0x3238 */
    volatile U_V2_CSC1_P4 V2_CSC1_P4;                                                   /* 0x323c */
    volatile unsigned int reserved_33[112];                                             /* 0x3240~0x33fc */
    volatile U_V2_CVFIR_VINFO V2_CVFIR_VINFO;                                           /* 0x3400 */
    volatile U_V2_CVFIR_VSP V2_CVFIR_VSP;                                               /* 0x3404 */
    volatile U_V2_CVFIR_VOFFSET V2_CVFIR_VOFFSET;                                       /* 0x3408 */
    volatile U_V2_CVFIR_VBOFFSET V2_CVFIR_VBOFFSET;                                     /* 0x340c */
    volatile unsigned int reserved_34[8];                                               /* 0x3410~0x342c */
    volatile U_V2_CVFIR_VCOEF0 V2_CVFIR_VCOEF0;                                         /* 0x3430 */
    volatile U_V2_CVFIR_VCOEF1 V2_CVFIR_VCOEF1;                                         /* 0x3434 */
    volatile U_V2_CVFIR_VCOEF2 V2_CVFIR_VCOEF2;                                         /* 0x3438 */
    volatile unsigned int reserved_35[49];                                              /* 0x343c~0x34fc */
    volatile U_V2_HFIR_CTRL V2_HFIR_CTRL;                                               /* 0x3500 */
    volatile U_V2_HFIRCOEF01 V2_HFIRCOEF01;                                             /* 0x3504 */
    volatile U_V2_HFIRCOEF23 V2_HFIRCOEF23;                                             /* 0x3508 */
    volatile U_V2_HFIRCOEF45 V2_HFIRCOEF45;                                             /* 0x350c */
    volatile U_V2_HFIRCOEF67 V2_HFIRCOEF67;                                             /* 0x3510 */
    volatile unsigned int reserved_36[2235];                                            /* 0x3514~0x57fc */
    volatile unsigned int VP0_CTRL;                                                     /* 0x5800 */
    volatile U_VP0_UPD VP0_UPD;                                                         /* 0x5804 */
    volatile U_VP0_IRESO VP0_IRESO;                                                     /* 0x5808 */
    volatile unsigned int reserved_37[29];                                              /* 0x580c~0x587c */
    volatile U_VP0_LBOX_CTRL VP0_LBOX_CTRL;                                             /* 0x5880 */
    volatile U_VP0_GALPHA VP0_GALPHA;                                                   /* 0x5884 */
    volatile U_VP0_DFPOS VP0_DFPOS;                                                     /* 0x5888 */
    volatile U_VP0_DLPOS VP0_DLPOS;                                                     /* 0x588c */
    volatile U_VP0_VFPOS VP0_VFPOS;                                                     /* 0x5890 */
    volatile U_VP0_VLPOS VP0_VLPOS;                                                     /* 0x5894 */
    volatile U_VP0_BK VP0_BK;                                                           /* 0x5898 */
    volatile U_VP0_ALPHA VP0_ALPHA;                                                     /* 0x589c */
    volatile U_VP0_MUTE_BK VP0_MUTE_BK;                                                 /* 0x58a0 */
    volatile unsigned int reserved_38[1495];                                            /* 0x58a4~0x6ffc */
    volatile U_G0_CTRL G0_CTRL;                                                         /* 0x7000 */
    volatile U_G0_UPD G0_UPD;                                                           /* 0x7004 */
    volatile unsigned int G0_GALPHA_SUM;                                                /* 0x7008 */
    volatile U_G0_0RESO_READ G0_0RESO_READ;                                             /* 0x700c */
    volatile unsigned int reserved_39[28];                                              /* 0x7010~0x707c */
    volatile U_G0_DFPOS G0_DFPOS;                                                       /* 0x7080 */
    volatile U_G0_DLPOS G0_DLPOS;                                                       /* 0x7084 */
    volatile U_G0_VFPOS G0_VFPOS;                                                       /* 0x7088 */
    volatile U_G0_VLPOS G0_VLPOS;                                                       /* 0x708c */
    volatile U_G0_BK G0_BK;                                                             /* 0x7090 */
    volatile U_G0_ALPHA G0_ALPHA;                                                       /* 0x7094 */
    volatile U_G0_MUTE_BK G0_MUTE_BK;                                                   /* 0x7098 */
    volatile U_G0_LBOX_CTRL G0_LBOX_CTRL;                                               /* 0x709c */
    volatile unsigned int reserved_40[88];                                              /* 0x70a0~0x71fc */
    volatile U_G0_DOF_CTRL G0_DOF_CTRL;                                                 /* 0x7200 */
    volatile U_G0_DOF_STEP G0_DOF_STEP;                                                 /* 0x7204 */
    volatile U_G0_DOF_BKG G0_DOF_BKG;                                                   /* 0x7208 */
    volatile U_G0_DOF_ALPHA G0_DOF_ALPHA;                                               /* 0x720c */
    volatile unsigned int reserved_41[60];                                              /* 0x7210~0x72fc */
    volatile U_G0_ZME_HINFO G0_ZME_HINFO;                                               /* 0x7300 */
    volatile U_G0_ZME_HSP G0_ZME_HSP;                                                   /* 0x7304 */
    volatile U_G0_ZME_HLOFFSET G0_ZME_HLOFFSET;                                         /* 0x7308 */
    volatile U_G0_ZME_HCOFFSET G0_ZME_HCOFFSET;                                         /* 0x730c */
    volatile unsigned int reserved_42[5];                                               /* 0x7310~0x7320 */
    volatile U_G0_ZME_COEF_REN G0_ZME_COEF_REN;                                         /* 0x7324 */
    volatile U_G0_ZME_COEF_RDATA G0_ZME_COEF_RDATA;                                     /* 0x7328 */
    volatile unsigned int reserved_43[21];                                              /* 0x732c~0x737c */
    volatile U_G0_ZME_VINFO G0_ZME_VINFO;                                               /* 0x7380 */
    volatile U_G0_ZME_VSP G0_ZME_VSP;                                                   /* 0x7384 */
    volatile U_G0_ZME_VOFFSET G0_ZME_VOFFSET;                                           /* 0x7388 */
    volatile unsigned int reserved_44[285];                                             /* 0x738c~0x77fc */
    volatile U_G1_CTRL G1_CTRL;                                                         /* 0x7800 */
    volatile U_G1_UPD G1_UPD;                                                           /* 0x7804 */
    volatile unsigned int G1_GALPHA_SUM;                                                /* 0x7808 */
    volatile U_G1_0RESO_READ G1_0RESO_READ;                                             /* 0x780c */
    volatile unsigned int reserved_45[28];                                              /* 0x7810~0x787c */
    volatile U_G1_DFPOS G1_DFPOS;                                                       /* 0x7880 */
    volatile U_G1_DLPOS G1_DLPOS;                                                       /* 0x7884 */
    volatile U_G1_VFPOS G1_VFPOS;                                                       /* 0x7888 */
    volatile U_G1_VLPOS G1_VLPOS;                                                       /* 0x788c */
    volatile U_G1_BK G1_BK;                                                             /* 0x7890 */
    volatile U_G1_ALPHA G1_ALPHA;                                                       /* 0x7894 */
    volatile U_G1_MUTE_BK G1_MUTE_BK;                                                   /* 0x7898 */
    volatile U_G1_LBOX_CTRL G1_LBOX_CTRL;                                               /* 0x789c */
    volatile unsigned int reserved_46[24];                                              /* 0x78a0~0x78fc */
    volatile U_G1_CSC_IDC G1_CSC_IDC;                                                   /* 0x7900 */
    volatile U_G1_CSC_ODC G1_CSC_ODC;                                                   /* 0x7904 */
    volatile U_G1_CSC_IODC G1_CSC_IODC;                                                 /* 0x7908 */
    volatile U_G1_CSC_P0 G1_CSC_P0;                                                     /* 0x790c */
    volatile U_G1_CSC_P1 G1_CSC_P1;                                                     /* 0x7910 */
    volatile U_G1_CSC_P2 G1_CSC_P2;                                                     /* 0x7914 */
    volatile U_G1_CSC_P3 G1_CSC_P3;                                                     /* 0x7918 */
    volatile U_G1_CSC_P4 G1_CSC_P4;                                                     /* 0x791c */
    volatile U_G1_CSC1_IDC G1_CSC1_IDC;                                                 /* 0x7920 */
    volatile U_G1_CSC1_ODC G1_CSC1_ODC;                                                 /* 0x7924 */
    volatile U_G1_CSC1_IODC G1_CSC1_IODC;                                               /* 0x7928 */
    volatile U_G1_CSC1_P0 G1_CSC1_P0;                                                   /* 0x792c */
    volatile U_G1_CSC1_P1 G1_CSC1_P1;                                                   /* 0x7930 */
    volatile U_G1_CSC1_P2 G1_CSC1_P2;                                                   /* 0x7934 */
    volatile U_G1_CSC1_P3 G1_CSC1_P3;                                                   /* 0x7938 */
    volatile U_G1_CSC1_P4 G1_CSC1_P4;                                                   /* 0x793c */
    volatile unsigned int reserved_47[944];                                             /* 0x7940~0x87fc */
    volatile U_G3_CTRL G3_CTRL;                                                         /* 0x8800 */
    volatile U_G3_UPD G3_UPD;                                                           /* 0x8804 */
    volatile unsigned int G3_GALPHA_SUM;                                                /* 0x8808 */
    volatile U_G3_0RESO_READ G3_0RESO_READ;                                             /* 0x880c */
    volatile unsigned int reserved_48[28];                                              /* 0x8810~0x887c */
    volatile U_G3_DFPOS G3_DFPOS;                                                       /* 0x8880 */
    volatile U_G3_DLPOS G3_DLPOS;                                                       /* 0x8884 */
    volatile U_G3_VFPOS G3_VFPOS;                                                       /* 0x8888 */
    volatile U_G3_VLPOS G3_VLPOS;                                                       /* 0x888c */
    volatile U_G3_BK G3_BK;                                                             /* 0x8890 */
    volatile U_G3_ALPHA G3_ALPHA;                                                       /* 0x8894 */
    volatile U_G3_MUTE_BK G3_MUTE_BK;                                                   /* 0x8898 */
    volatile U_G3_LBOX_CTRL G3_LBOX_CTRL;                                               /* 0x889c */
    volatile unsigned int reserved_49[24];                                              /* 0x88a0~0x88fc */
    volatile U_G3_CSC_IDC G3_CSC_IDC;                                                   /* 0x8900 */
    volatile U_G3_CSC_ODC G3_CSC_ODC;                                                   /* 0x8904 */
    volatile U_G3_CSC_IODC G3_CSC_IODC;                                                 /* 0x8908 */
    volatile U_G3_CSC_P0 G3_CSC_P0;                                                     /* 0x890c */
    volatile U_G3_CSC_P1 G3_CSC_P1;                                                     /* 0x8910 */
    volatile U_G3_CSC_P2 G3_CSC_P2;                                                     /* 0x8914 */
    volatile U_G3_CSC_P3 G3_CSC_P3;                                                     /* 0x8918 */
    volatile U_G3_CSC_P4 G3_CSC_P4;                                                     /* 0x891c */
    volatile U_G3_CSC1_IDC G3_CSC1_IDC;                                                 /* 0x8920 */
    volatile U_G3_CSC1_ODC G3_CSC1_ODC;                                                 /* 0x8924 */
    volatile U_G3_CSC1_IODC G3_CSC1_IODC;                                               /* 0x8928 */
    volatile U_G3_CSC1_P0 G3_CSC1_P0;                                                   /* 0x892c */
    volatile U_G3_CSC1_P1 G3_CSC1_P1;                                                   /* 0x8930 */
    volatile U_G3_CSC1_P2 G3_CSC1_P2;                                                   /* 0x8934 */
    volatile U_G3_CSC1_P3 G3_CSC1_P3;                                                   /* 0x8938 */
    volatile U_G3_CSC1_P4 G3_CSC1_P4;                                                   /* 0x893c */
    volatile unsigned int reserved_50[944];                                             /* 0x8940~0x97fc */
    volatile unsigned int GP0_CTRL;                                                     /* 0x9800 */
    volatile U_GP0_UPD GP0_UPD;                                                         /* 0x9804 */
    volatile U_GP0_IRESO GP0_IRESO;                                                     /* 0x9808 */
    volatile unsigned int reserved_51[29];                                              /* 0x980c~0x987c */
    volatile U_GP0_LBOX_CTRL GP0_LBOX_CTRL;                                             /* 0x9880 */
    volatile U_GP0_GALPHA GP0_GALPHA;                                                   /* 0x9884 */
    volatile unsigned int GP0_GALPHA_SUM;                                               /* 0x9888 */
    volatile U_GP0_DFPOS GP0_DFPOS;                                                     /* 0x988c */
    volatile U_GP0_DLPOS GP0_DLPOS;                                                     /* 0x9890 */
    volatile U_GP0_VFPOS GP0_VFPOS;                                                     /* 0x9894 */
    volatile U_GP0_VLPOS GP0_VLPOS;                                                     /* 0x9898 */
    volatile U_GP0_BK GP0_BK;                                                           /* 0x989c */
    volatile U_GP0_ALPHA GP0_ALPHA;                                                     /* 0x98a0 */
    volatile U_GP0_MUTE_BK GP0_MUTE_BK;                                                 /* 0x98a4 */
    volatile unsigned int reserved_52[22];                                              /* 0x98a8~0x98fc */
    volatile U_GP0_CSC_IDC GP0_CSC_IDC;                                                 /* 0x9900 */
    volatile U_GP0_CSC_ODC GP0_CSC_ODC;                                                 /* 0x9904 */
    volatile U_GP0_CSC_IODC GP0_CSC_IODC;                                               /* 0x9908 */
    volatile U_GP0_CSC_P0 GP0_CSC_P0;                                                   /* 0x990c */
    volatile U_GP0_CSC_P1 GP0_CSC_P1;                                                   /* 0x9910 */
    volatile U_GP0_CSC_P2 GP0_CSC_P2;                                                   /* 0x9914 */
    volatile U_GP0_CSC_P3 GP0_CSC_P3;                                                   /* 0x9918 */
    volatile U_GP0_CSC_P4 GP0_CSC_P4;                                                   /* 0x991c */
    volatile unsigned int reserved_53[1464];                                            /* 0x9920~0xaffc */
    volatile U_WBC_G0_CTRL WBC_G0_CTRL;                                                 /* 0xb000 */
    volatile U_WBC_G0_UPD WBC_G0_UPD;                                                   /* 0xb004 */
    volatile U_WBC_G0_CMP WBC_G0_CMP;                                                   /* 0xb008 */
    volatile unsigned int reserved_54;                                                  /* 0xb00c */
    volatile unsigned int WBC_G0_AR_ADDR;                                               /* 0xb010 */
    volatile unsigned int WBC_G0_GB_ADDR;                                               /* 0xb014 */
    volatile U_WBC_G0_STRIDE WBC_G0_STRIDE;                                             /* 0xb018 */
    volatile unsigned int WBC_G0_OFFSET;                                                /* 0xb01c */
    volatile U_WBC_G0_ORESO WBC_G0_ORESO;                                               /* 0xb020 */
    volatile U_WBC_G0_FCROP WBC_G0_FCROP;                                               /* 0xb024 */
    volatile U_WBC_G0_LCROP WBC_G0_LCROP;                                               /* 0xb028 */
    volatile unsigned int reserved_55[501];                                             /* 0xb02c~0xb7fc */
    volatile U_WBC_GP0_CTRL WBC_GP0_CTRL;                                               /* 0xb800 */
    volatile U_WBC_GP0_UPD WBC_GP0_UPD;                                                 /* 0xb804 */
    volatile unsigned int reserved_56[2];                                               /* 0xb808~0xb80c */
    volatile unsigned int WBC_GP0_YADDR;                                                /* 0xb810 */
    volatile unsigned int WBC_GP0_CADDR;                                                /* 0xb814 */
    volatile U_WBC_GP0_STRIDE WBC_GP0_STRIDE;                                           /* 0xb818 */
    volatile unsigned int reserved_57;                                                  /* 0xb81c */
    volatile U_WBC_GP0_ORESO WBC_GP0_ORESO;                                             /* 0xb820 */
    volatile U_WBC_GP0_FCROP WBC_GP0_FCROP;                                             /* 0xb824 */
    volatile U_WBC_GP0_LCROP WBC_GP0_LCROP;                                             /* 0xb828 */
    volatile unsigned int reserved_58[53];                                              /* 0xb82c~0xb8fc */
    volatile U_WBC_GP0_DITHER_CTRL WBC_GP0_DITHER_CTRL;                                 /* 0xb900 */
    volatile U_WBC_GP0_DITHER_COEF0 WBC_GP0_DITHER_COEF0;                               /* 0xb904 */
    volatile U_WBC_GP0_DITHER_COEF1 WBC_GP0_DITHER_COEF1;                               /* 0xb908 */
    volatile unsigned int reserved_59[17];                                              /* 0xb90c~0xb94c */
    volatile U_WBC_GP0_HPZME WBC_GP0_HPZME;                                             /* 0xb950 */
    volatile unsigned int reserved_60[43];                                              /* 0xb954~0xb9fc */
    volatile U_WBC_ME_CTRL WBC_ME_CTRL;                                                 /* 0xba00 */
    volatile U_WBC_ME_UPD WBC_ME_UPD;                                                   /* 0xba04 */
    volatile U_WBC_ME_WLEN_SEL WBC_ME_WLEN_SEL;                                         /* 0xba08 */
    volatile unsigned int reserved_61;                                                  /* 0xba0c */
    volatile unsigned int WBC_ME_YADDR;                                                 /* 0xba10 */
    volatile unsigned int WBC_ME_CADDR;                                                 /* 0xba14 */
    volatile U_WBC_ME_STRIDE WBC_ME_STRIDE;                                             /* 0xba18 */
    volatile unsigned int reserved_62;                                                  /* 0xba1c */
    volatile U_WBC_ME_ORESO WBC_ME_ORESO;                                               /* 0xba20 */
    volatile unsigned int reserved_63[2];                                               /* 0xba24~0xba28 */
    volatile U_WBC_ME_SMMU_BYPASS WBC_ME_SMMU_BYPASS;                                   /* 0xba2c */
    volatile unsigned int reserved_64[4];                                               /* 0xba30~0xba3c */
    volatile U_WBC_ME_PARAUP WBC_ME_PARAUP;                                             /* 0xba40 */
    volatile unsigned int reserved_65[3];                                               /* 0xba44~0xba4c */
    volatile unsigned int WBC_ME_HLCOEFAD;                                              /* 0xba50 */
    volatile unsigned int WBC_ME_HCCOEFAD;                                              /* 0xba54 */
    volatile unsigned int WBC_ME_VLCOEFAD;                                              /* 0xba58 */
    volatile unsigned int WBC_ME_VCCOEFAD;                                              /* 0xba5c */
    volatile unsigned int reserved_66[36];                                              /* 0xba60~0xbaec */
    volatile unsigned int WBC_ME_CHECKSUM_Y;                                            /* 0xbaf0 */
    volatile unsigned int WBC_ME_CHECKSUM_C;                                            /* 0xbaf4 */
    volatile unsigned int reserved_67[2];                                               /* 0xbaf8~0xbafc */
    volatile U_WBC_ME_DITHER_CTRL WBC_ME_DITHER_CTRL;                                   /* 0xbb00 */
    volatile U_WBC_ME_DITHER_COEF0 WBC_ME_DITHER_COEF0;                                 /* 0xbb04 */
    volatile U_WBC_ME_DITHER_COEF1 WBC_ME_DITHER_COEF1;                                 /* 0xbb08 */
    volatile unsigned int reserved_68[109];                                             /* 0xbb0c~0xbcbc */
    volatile U_WBC_ME_ZME_HSP WBC_ME_ZME_HSP;                                           /* 0xbcc0 */
    volatile U_WBC_ME_ZME_HLOFFSET WBC_ME_ZME_HLOFFSET;                                 /* 0xbcc4 */
    volatile U_WBC_ME_ZME_HCOFFSET WBC_ME_ZME_HCOFFSET;                                 /* 0xbcc8 */
    volatile unsigned int reserved_69[3];                                               /* 0xbccc~0xbcd4 */
    volatile U_WBC_ME_ZME_VSP WBC_ME_ZME_VSP;                                           /* 0xbcd8 */
    volatile U_WBC_ME_ZME_VSR WBC_ME_ZME_VSR;                                           /* 0xbcdc */
    volatile U_WBC_ME_ZME_VOFFSET WBC_ME_ZME_VOFFSET;                                   /* 0xbce0 */
    volatile U_WBC_ME_ZME_VBOFFSET WBC_ME_ZME_VBOFFSET;                                 /* 0xbce4 */
    volatile unsigned int reserved_70[6];                                               /* 0xbce8~0xbcfc */
    volatile U_WBC_FI_CTRL WBC_FI_CTRL;                                                 /* 0xbd00 */
    volatile U_WBC_FI_UPD WBC_FI_UPD;                                                   /* 0xbd04 */
    volatile U_WBC_FI_WLEN_SEL WBC_FI_WLEN_SEL;                                         /* 0xbd08 */
    volatile unsigned int reserved_71;                                                  /* 0xbd0c */
    volatile unsigned int WBC_FI_YADDR;                                                 /* 0xbd10 */
    volatile unsigned int WBC_FI_CADDR;                                                 /* 0xbd14 */
    volatile U_WBC_FI_STRIDE WBC_FI_STRIDE;                                             /* 0xbd18 */
    volatile unsigned int reserved_72;                                                  /* 0xbd1c */
    volatile U_WBC_FI_ORESO WBC_FI_ORESO;                                               /* 0xbd20 */
    volatile unsigned int reserved_73[2];                                               /* 0xbd24~0xbd28 */
    volatile U_WBC_FI_SMMU_BYPASS WBC_FI_SMMU_BYPASS;                                   /* 0xbd2c */
    volatile unsigned int reserved_74[5];                                               /* 0xbd30~0xbd40 */
    volatile U_WBC_FI_FRAME_SIZE WBC_FI_FRAME_SIZE;                                     /* 0xbd44 */
    volatile unsigned int WBC_FI_Y_RADDR;                                               /* 0xbd48 */
    volatile unsigned int WBC_FI_C_RADDR;                                               /* 0xbd4c */
    volatile unsigned int reserved_75[40];                                              /* 0xbd50~0xbdec */
    volatile unsigned int WBC_FI_CHECKSUM_Y;                                            /* 0xbdf0 */
    volatile unsigned int WBC_FI_CHECKSUM_C;                                            /* 0xbdf4 */
    volatile unsigned int reserved_76[6];                                               /* 0xbdf8~0xbe0c */
    volatile U_WBC_FI_HCDS WBC_FI_HCDS;                                                 /* 0xbe10 */
    volatile U_WBC_FI_HCDS_COEF0 WBC_FI_HCDS_COEF0;                                     /* 0xbe14 */
    volatile U_WBC_FI_HCDS_COEF1 WBC_FI_HCDS_COEF1;                                     /* 0xbe18 */
    volatile unsigned int reserved_77;                                                  /* 0xbe1c */
    volatile U_WBC_FI_CMP_MB WBC_FI_CMP_MB;                                             /* 0xbe20 */
    volatile U_WBC_FI_CMP_MAX_MIN WBC_FI_CMP_MAX_MIN;                                   /* 0xbe24 */
    volatile U_WBC_FI_CMP_ADJ_THR WBC_FI_CMP_ADJ_THR;                                   /* 0xbe28 */
    volatile U_WBC_FI_CMP_BIG_GRAD WBC_FI_CMP_BIG_GRAD;                                 /* 0xbe2c */
    volatile U_WBC_FI_CMP_BLK WBC_FI_CMP_BLK;                                           /* 0xbe30 */
    volatile U_WBC_FI_CMP_GRAPHIC_JUDGE WBC_FI_CMP_GRAPHIC_JUDGE;                       /* 0xbe34 */
    volatile U_WBC_FI_CMP_RC WBC_FI_CMP_RC;                                             /* 0xbe38 */
    volatile U_WBC_FI_CMP_FRAME_SIZE WBC_FI_CMP_FRAME_SIZE;                             /* 0xbe3c */
    volatile unsigned int reserved_78[48];                                              /* 0xbe40~0xbefc */
    volatile U_WBC_CMP_GLB_INFO WBC_CMP_GLB_INFO;                                       /* 0xbf00 */
    volatile U_WBC_CMP_FRAMESIZE WBC_CMP_FRAMESIZE;                                     /* 0xbf04 */
    volatile U_WBC_CMP_RC_CFG0 WBC_CMP_RC_CFG0;                                         /* 0xbf08 */
    volatile U_WBC_CMP_RC_CFG2 WBC_CMP_RC_CFG2;                                         /* 0xbf0c */
    volatile U_WBC_CMP_RC_CFG3 WBC_CMP_RC_CFG3;                                         /* 0xbf10 */
    volatile U_WBC_CMP_RC_CFG4 WBC_CMP_RC_CFG4;                                         /* 0xbf14 */
    volatile U_WBC_CMP_RC_CFG5 WBC_CMP_RC_CFG5;                                         /* 0xbf18 */
    volatile U_WBC_CMP_RC_CFG6 WBC_CMP_RC_CFG6;                                         /* 0xbf1c */
    volatile U_WBC_CMP_RC_CFG7 WBC_CMP_RC_CFG7;                                         /* 0xbf20 */
    volatile U_WBC_CMP_RC_CFG8 WBC_CMP_RC_CFG8;                                         /* 0xbf24 */
    volatile U_WBC_CMP_RC_CFG10 WBC_CMP_RC_CFG10;                                       /* 0xbf28 */
    volatile U_WBC_CMP_OUTSIZE0 WBC_CMP_OUTSIZE0;                                       /* 0xbf2c */
    volatile unsigned int WBC_CMP_DBG_REG0;                                             /* 0xbf30 */
    volatile U_WBC_CMP_MAX_ROW WBC_CMP_MAX_ROW;                                         /* 0xbf34 */
    volatile U_WBC_BMP_CTRL WBC_BMP_CTRL;                                               /* 0xbf38 */
    volatile U_WBC_BMP_UPD WBC_BMP_UPD;                                                 /* 0xbf3c */
    volatile unsigned int WBC_BMP_YADDR;                                                /* 0xbf40 */
    volatile unsigned int reserved_79[23];                                              /* 0xbf44~0xbf9c */
    volatile U_WBC_BMP_ORESO WBC_BMP_ORESO;                                             /* 0xbfa0 */
    volatile U_WBC_BMP_SUM WBC_BMP_SUM;                                                 /* 0xbfa4 */
    volatile unsigned int reserved_80[18];                                              /* 0xbfa8~0xbfec */
    volatile unsigned int WBC_BMP_CHECKSUM_Y;                                           /* 0xbff0 */
    volatile unsigned int WBC_BMP_CHECKSUM_C;                                           /* 0xbff4 */
    volatile unsigned int reserved_81[2];                                               /* 0xbff8~0xbffc */
    volatile U_WBC_DHD0_CTRL WBC_DHD0_CTRL;                                             /* 0xc000 */
    volatile U_WBC_DHD0_UPD WBC_DHD0_UPD;                                               /* 0xc004 */
    volatile U_WBC_DHD0_ORESO WBC_DHD0_ORESO;                                           /* 0xc008 */
    volatile unsigned int reserved_82[29];                                              /* 0xc00c~0xc07c */
    volatile U_WD_HPZME_CTRL WD_HPZME_CTRL;                                             /* 0xc080 */
    volatile U_WD_HPZMECOEF01 WD_HPZMECOEF01;                                           /* 0xc084 */
    volatile U_WD_HPZMECOEF23 WD_HPZMECOEF23;                                           /* 0xc088 */
    volatile U_WD_HPZMECOEF45 WD_HPZMECOEF45;                                           /* 0xc08c */
    volatile U_WD_HPZMECOEF67 WD_HPZMECOEF67;                                           /* 0xc090 */
    volatile unsigned int reserved_83[91];                                              /* 0xc094~0xc1fc */
    volatile U_WD_HCDS_CTRL WD_HCDS_CTRL;                                               /* 0xc200 */
    volatile U_WD_HCDSCOEF01 WD_HCDSCOEF01;                                             /* 0xc204 */
    volatile U_WD_HCDSCOEF23 WD_HCDSCOEF23;                                             /* 0xc208 */
    volatile U_WD_HCDSCOEF45 WD_HCDSCOEF45;                                             /* 0xc20c */
    volatile U_WD_HCDSCOEF67 WD_HCDSCOEF67;                                             /* 0xc210 */
    volatile unsigned int reserved_84[27];                                              /* 0xc214~0xc27c */
    volatile U_DITHER_CTRL DITHER_CTRL;                                                 /* 0xc280 */
    volatile U_DITHER_SED_Y0 DITHER_SED_Y0;                                             /* 0xc284 */
    volatile U_DITHER_SED_U0 DITHER_SED_U0;                                             /* 0xc288 */
    volatile U_DITHER_SED_V0 DITHER_SED_V0;                                             /* 0xc28c */
    volatile U_DITHER_SED_W0 DITHER_SED_W0;                                             /* 0xc290 */
    volatile U_DITHER_SED_Y1 DITHER_SED_Y1;                                             /* 0xc294 */
    volatile U_DITHER_SED_U1 DITHER_SED_U1;                                             /* 0xc298 */
    volatile U_DITHER_SED_V1 DITHER_SED_V1;                                             /* 0xc29c */
    volatile U_DITHER_SED_W1 DITHER_SED_W1;                                             /* 0xc2a0 */
    volatile U_DITHER_SED_Y2 DITHER_SED_Y2;                                             /* 0xc2a4 */
    volatile U_DITHER_SED_U2 DITHER_SED_U2;                                             /* 0xc2a8 */
    volatile U_DITHER_SED_V2 DITHER_SED_V2;                                             /* 0xc2ac */
    volatile U_DITHER_SED_W2 DITHER_SED_W2;                                             /* 0xc2b0 */
    volatile U_DITHER_SED_Y3 DITHER_SED_Y3;                                             /* 0xc2b4 */
    volatile U_DITHER_SED_U3 DITHER_SED_U3;                                             /* 0xc2b8 */
    volatile U_DITHER_SED_V3 DITHER_SED_V3;                                             /* 0xc2bc */
    volatile U_DITHER_SED_W3 DITHER_SED_W3;                                             /* 0xc2c0 */
    volatile U_DITHER_THR DITHER_THR;                                                   /* 0xc2c4 */
    volatile unsigned int reserved_85[14];                                              /* 0xc2c8~0xc2fc */
    volatile U_WD_ZME_HINFO WD_ZME_HINFO;                                               /* 0xc300 */
    volatile U_WD_ZME_HSP WD_ZME_HSP;                                                   /* 0xc304 */
    volatile U_WD_ZME_HLOFFSET WD_ZME_HLOFFSET;                                         /* 0xc308 */
    volatile U_WD_ZME_HCOFFSET WD_ZME_HCOFFSET;                                         /* 0xc30c */
    volatile unsigned int reserved_86[5];                                               /* 0xc310~0xc320 */
    volatile U_WD_ZME_HCOEF_REN WD_ZME_HCOEF_REN;                                       /* 0xc324 */
    volatile U_WD_ZME_HCOEF_RDATA WD_ZME_HCOEF_RDATA;                                   /* 0xc328 */
    volatile U_WD_ZME_HDRAW WD_ZME_HDRAW;                                               /* 0xc32c */
    volatile U_WD_ZME_HRATIO WD_ZME_HRATIO;                                             /* 0xc330 */
    volatile unsigned int reserved_87[51];                                              /* 0xc334~0xc3fc */
    volatile U_WD_ZME_VINFO WD_ZME_VINFO;                                               /* 0xc400 */
    volatile U_WD_ZME_VSP WD_ZME_VSP;                                                   /* 0xc404 */
    volatile U_WD_ZME_VOFFSET WD_ZME_VOFFSET;                                           /* 0xc408 */
    volatile U_WD_ZME_VBOFFSET WD_ZME_VBOFFSET;                                         /* 0xc40c */
    volatile unsigned int reserved_88[5];                                               /* 0xc410~0xc420 */
    volatile U_WD_ZME_VCOEF_REN WD_ZME_VCOEF_REN;                                       /* 0xc424 */
    volatile U_WD_ZME_VCOEF_RDATA WD_ZME_VCOEF_RDATA;                                   /* 0xc428 */
    volatile U_WD_ZME_VDRAW WD_ZME_VDRAW;                                               /* 0xc42c */
    volatile U_WD_ZME_VRATIO WD_ZME_VRATIO;                                             /* 0xc430 */
    volatile unsigned int reserved_89[755];                                             /* 0xc434~0xcffc */
    volatile U_DHD0_CTRL DHD0_CTRL;                                                     /* 0xd000 */
    volatile U_DHD0_VSYNC1 DHD0_VSYNC1;                                                 /* 0xd004 */
    volatile U_DHD0_VSYNC2 DHD0_VSYNC2;                                                 /* 0xd008 */
    volatile U_DHD0_HSYNC1 DHD0_HSYNC1;                                                 /* 0xd00c */
    volatile U_DHD0_HSYNC2 DHD0_HSYNC2;                                                 /* 0xd010 */
    volatile U_DHD0_VPLUS1 DHD0_VPLUS1;                                                 /* 0xd014 */
    volatile U_DHD0_VPLUS2 DHD0_VPLUS2;                                                 /* 0xd018 */
    volatile U_DHD0_PWR DHD0_PWR;                                                       /* 0xd01c */
    volatile U_DHD0_VTTHD3 DHD0_VTTHD3;                                                 /* 0xd020 */
    volatile U_DHD0_VTTHD DHD0_VTTHD;                                                   /* 0xd024 */
    volatile U_DHD0_PARATHD DHD0_PARATHD;                                               /* 0xd028 */
    volatile U_DHD0_PRECHARGE_THD DHD0_PRECHARGE_THD;                                   /* 0xd02c */
    volatile U_DHD0_START_POS DHD0_START_POS;                                           /* 0xd030 */
    volatile U_DHD0_START_POS1 DHD0_START_POS1;                                         /* 0xd034 */
    volatile U_DHD0_PARAUP DHD0_PARAUP;                                                 /* 0xd038 */
    volatile U_DHD0_SYNC_INV DHD0_SYNC_INV;                                             /* 0xd03c */
    volatile U_DHD0_CLK_DV_CTRL DHD0_CLK_DV_CTRL;                                       /* 0xd040 */
    volatile U_DHD0_RGB_FIX_CTRL DHD0_RGB_FIX_CTRL;                                     /* 0xd044 */
    volatile U_DHD0_LOCKCFG DHD0_LOCKCFG;                                               /* 0xd048 */
    volatile unsigned int DHD0_CAP_FRM_CNT;                                             /* 0xd04c */
    volatile unsigned int DHD0_VDP_FRM_CNT;                                             /* 0xd050 */
    volatile unsigned int DHD0_VSYNC_CAP_VDP_CNT;                                       /* 0xd054 */
    volatile unsigned int DHD0_INTF_CHKSUM_Y;                                           /* 0xd058 */
    volatile unsigned int DHD0_INTF_CHKSUM_U;                                           /* 0xd05c */
    volatile unsigned int DHD0_INTF_CHKSUM_V;                                           /* 0xd060 */
    volatile unsigned int DHD0_INTF1_CHKSUM_Y;                                          /* 0xd064 */
    volatile unsigned int DHD0_INTF1_CHKSUM_U;                                          /* 0xd068 */
    volatile unsigned int DHD0_INTF1_CHKSUM_V;                                          /* 0xd06c */
    volatile U_DHD0_INTF_CHKSUM_HIGH1 DHD0_INTF_CHKSUM_HIGH1;                           /* 0xd070 */
    volatile U_DHD0_INTF_CHKSUM_HIGH2 DHD0_INTF_CHKSUM_HIGH2;                           /* 0xd074 */
    volatile unsigned int reserved_90[3];                                               /* 0xd078~0xd080 */
    volatile unsigned int DHD0_AFIFO_PRE_THD;                                           /* 0xd084 */
    volatile U_DHD0_STATE DHD0_STATE;                                                   /* 0xd088 */
    volatile U_DHD0_UF_STATE DHD0_UF_STATE;                                             /* 0xd08c */
    volatile U_VO_MUX VO_MUX;                                                           /* 0xd090 */
    volatile U_VO_MUX_SYNC VO_MUX_SYNC;                                                 /* 0xd094 */
    volatile U_VO_MUX_DATA VO_MUX_DATA;                                                 /* 0xd098 */
    volatile unsigned int reserved_91[5];                                               /* 0xd09c~0xd0ac */
    volatile U_INTF0_DITHER_CTRL INTF0_DITHER_CTRL;                                     /* 0xd0b0 */
    volatile U_INTF0_DITHER_SED_Y0 INTF0_DITHER_SED_Y0;                                 /* 0xd0b4 */
    volatile U_INTF0_DITHER_SED_U0 INTF0_DITHER_SED_U0;                                 /* 0xd0b8 */
    volatile U_INTF0_DITHER_SED_V0 INTF0_DITHER_SED_V0;                                 /* 0xd0bc */
    volatile U_INTF0_DITHER_SED_W0 INTF0_DITHER_SED_W0;                                 /* 0xd0c0 */
    volatile U_INTF0_DITHER_SED_Y1 INTF0_DITHER_SED_Y1;                                 /* 0xd0c4 */
    volatile U_INTF0_DITHER_SED_U1 INTF0_DITHER_SED_U1;                                 /* 0xd0c8 */
    volatile U_INTF0_DITHER_SED_V1 INTF0_DITHER_SED_V1;                                 /* 0xd0cc */
    volatile U_INTF0_DITHER_SED_W1 INTF0_DITHER_SED_W1;                                 /* 0xd0d0 */
    volatile U_INTF0_DITHER_SED_Y2 INTF0_DITHER_SED_Y2;                                 /* 0xd0d4 */
    volatile U_INTF0_DITHER_SED_U2 INTF0_DITHER_SED_U2;                                 /* 0xd0d8 */
    volatile U_INTF0_DITHER_SED_V2 INTF0_DITHER_SED_V2;                                 /* 0xd0dc */
    volatile U_INTF0_DITHER_SED_W2 INTF0_DITHER_SED_W2;                                 /* 0xd0e0 */
    volatile U_INTF0_DITHER_SED_Y3 INTF0_DITHER_SED_Y3;                                 /* 0xd0e4 */
    volatile U_INTF0_DITHER_SED_U3 INTF0_DITHER_SED_U3;                                 /* 0xd0e8 */
    volatile U_INTF0_DITHER_SED_V3 INTF0_DITHER_SED_V3;                                 /* 0xd0ec */
    volatile U_INTF0_DITHER_SED_W3 INTF0_DITHER_SED_W3;                                 /* 0xd0f0 */
    volatile U_INTF0_DITHER_THR INTF0_DITHER_THR;                                       /* 0xd0f4 */
    volatile unsigned int reserved_92[2];                                               /* 0xd0f8~0xd0fc */
    volatile U_INTF_HDMI_CTRL INTF_HDMI_CTRL;                                           /* 0xd100 */
    volatile U_INTF_HDMI_UPD INTF_HDMI_UPD;                                             /* 0xd104 */
    volatile U_INTF_HDMI_SYNC_INV INTF_HDMI_SYNC_INV;                                   /* 0xd108 */
    volatile unsigned int reserved_93;                                                  /* 0xd10c */
    volatile unsigned int HDMI_INTF_CHKSUM_Y;                                           /* 0xd110 */
    volatile unsigned int HDMI_INTF_CHKSUM_U;                                           /* 0xd114 */
    volatile unsigned int HDMI_INTF_CHKSUM_V;                                           /* 0xd118 */
    volatile U_HDMI_INTF_CHKSUM_HIGH HDMI_INTF_CHKSUM_HIGH;                             /* 0xd11c */
    volatile unsigned int HDMI_INTF1_CHKSUM_Y;                                          /* 0xd120 */
    volatile unsigned int HDMI_INTF1_CHKSUM_U;                                          /* 0xd124 */
    volatile unsigned int HDMI_INTF1_CHKSUM_V;                                          /* 0xd128 */
    volatile U_HDMI_INTF1_CHKSUM_HIGH HDMI_INTF1_CHKSUM_HIGH;                           /* 0xd12c */
    volatile unsigned int reserved_94[8];                                               /* 0xd130~0xd14c */
    volatile U_HDMI_HFIR_COEF0 HDMI_HFIR_COEF0;                                         /* 0xd150 */
    volatile U_HDMI_HFIR_COEF1 HDMI_HFIR_COEF1;                                         /* 0xd154 */
    volatile U_HDMI_HFIR_COEF2 HDMI_HFIR_COEF2;                                         /* 0xd158 */
    volatile U_HDMI_HFIR_COEF3 HDMI_HFIR_COEF3;                                         /* 0xd15c */
    volatile unsigned int reserved_95[8];                                               /* 0xd160~0xd17c */
    volatile U_INTF_MIPI_CTRL INTF_MIPI_CTRL;                                           /* 0xd180 */
    volatile U_INTF_MIPI_UPD INTF_MIPI_UPD;                                             /* 0xd184 */
    volatile U_INTF_MIPI_SYNC_INV INTF_MIPI_SYNC_INV;                                   /* 0xd188 */
    volatile unsigned int reserved_96;                                                  /* 0xd18c */
    volatile unsigned int MIPI_INTF_CHKSUM_Y;                                           /* 0xd190 */
    volatile unsigned int MIPI_INTF_CHKSUM_U;                                           /* 0xd194 */
    volatile unsigned int MIPI_INTF_CHKSUM_V;                                           /* 0xd198 */
    volatile U_MIPI_INTF_CHKSUM_HIGH MIPI_INTF_CHKSUM_HIGH;                             /* 0xd19c */
    volatile unsigned int MIPI_INTF1_CHKSUM_Y;                                          /* 0xd1a0 */
    volatile unsigned int MIPI_INTF1_CHKSUM_U;                                          /* 0xd1a4 */
    volatile unsigned int MIPI_INTF1_CHKSUM_V;                                          /* 0xd1a8 */
    volatile U_MIPI_INTF1_CHKSUM_HIGH MIPI_INTF1_CHKSUM_HIGH;                           /* 0xd1ac */
    volatile unsigned int reserved_97[8];                                               /* 0xd1b0~0xd1cc */
    volatile U_MIPI_HFIR_COEF0 MIPI_HFIR_COEF0;                                         /* 0xd1d0 */
    volatile U_MIPI_HFIR_COEF1 MIPI_HFIR_COEF1;                                         /* 0xd1d4 */
    volatile U_MIPI_HFIR_COEF2 MIPI_HFIR_COEF2;                                         /* 0xd1d8 */
    volatile U_MIPI_HFIR_COEF3 MIPI_HFIR_COEF3;                                         /* 0xd1dc */
    volatile unsigned int reserved_98[8];                                               /* 0xd1e0~0xd1fc */
    volatile U_INTF_BT_CTRL INTF_BT_CTRL;                                               /* 0xd200 */
    volatile U_INTF_BT_UPD INTF_BT_UPD;                                                 /* 0xd204 */
    volatile U_INTF_BT_SYNC_INV INTF_BT_SYNC_INV;                                       /* 0xd208 */
    volatile unsigned int reserved_99;                                                  /* 0xd20c */
    volatile U_BT_CLIP0_L BT_CLIP0_L;                                                   /* 0xd210 */
    volatile U_BT_CLIP0_H BT_CLIP0_H;                                                   /* 0xd214 */
    volatile unsigned int reserved_100[26];                                             /* 0xd218~0xd27c */
    volatile U_BT_DITHER_CTRL BT_DITHER_CTRL;                                           /* 0xd280 */
    volatile U_BT_DITHER_SED_Y0 BT_DITHER_SED_Y0;                                       /* 0xd284 */
    volatile U_BT_DITHER_SED_U0 BT_DITHER_SED_U0;                                       /* 0xd288 */
    volatile U_BT_DITHER_SED_V0 BT_DITHER_SED_V0;                                       /* 0xd28c */
    volatile U_BT_DITHER_SED_W0 BT_DITHER_SED_W0;                                       /* 0xd290 */
    volatile U_BT_DITHER_SED_Y1 BT_DITHER_SED_Y1;                                       /* 0xd294 */
    volatile U_BT_DITHER_SED_U1 BT_DITHER_SED_U1;                                       /* 0xd298 */
    volatile U_BT_DITHER_SED_V1 BT_DITHER_SED_V1;                                       /* 0xd29c */
    volatile U_BT_DITHER_SED_W1 BT_DITHER_SED_W1;                                       /* 0xd2a0 */
    volatile U_BT_DITHER_SED_Y2 BT_DITHER_SED_Y2;                                       /* 0xd2a4 */
    volatile U_BT_DITHER_SED_U2 BT_DITHER_SED_U2;                                       /* 0xd2a8 */
    volatile U_BT_DITHER_SED_V2 BT_DITHER_SED_V2;                                       /* 0xd2ac */
    volatile U_BT_DITHER_SED_W2 BT_DITHER_SED_W2;                                       /* 0xd2b0 */
    volatile U_BT_DITHER_SED_Y3 BT_DITHER_SED_Y3;                                       /* 0xd2b4 */
    volatile U_BT_DITHER_SED_U3 BT_DITHER_SED_U3;                                       /* 0xd2b8 */
    volatile U_BT_DITHER_SED_V3 BT_DITHER_SED_V3;                                       /* 0xd2bc */
    volatile U_BT_DITHER_SED_W3 BT_DITHER_SED_W3;                                       /* 0xd2c0 */
    volatile U_BT_DITHER_THR BT_DITHER_THR;                                             /* 0xd2c4 */
    volatile unsigned int reserved_101[10];                                             /* 0xd2c8~0xd2ec */
    volatile unsigned int BT_INTF_CHKSUM_Y;                                             /* 0xd2f0 */
    volatile unsigned int BT_INTF_CHKSUM_U;                                             /* 0xd2f4 */
    volatile unsigned int BT_INTF_CHKSUM_V;                                             /* 0xd2f8 */
    volatile unsigned int reserved_102;                                                 /* 0xd2fc */
    volatile U_INTF_LCD_CTRL INTF_LCD_CTRL;                                             /* 0xd300 */
    volatile U_INTF_LCD_UPD INTF_LCD_UPD;                                               /* 0xd304 */
    volatile U_INTF_LCD_SYNC_INV INTF_LCD_SYNC_INV;                                     /* 0xd308 */
    volatile unsigned int reserved_103[29];                                             /* 0xd30c~0xd37c */
    volatile U_LCD_DITHER_CTRL LCD_DITHER_CTRL;                                         /* 0xd380 */
    volatile U_LCD_DITHER_SED_Y0 LCD_DITHER_SED_Y0;                                     /* 0xd384 */
    volatile U_LCD_DITHER_SED_U0 LCD_DITHER_SED_U0;                                     /* 0xd388 */
    volatile U_LCD_DITHER_SED_V0 LCD_DITHER_SED_V0;                                     /* 0xd38c */
    volatile U_LCD_DITHER_SED_W0 LCD_DITHER_SED_W0;                                     /* 0xd390 */
    volatile U_LCD_DITHER_SED_Y1 LCD_DITHER_SED_Y1;                                     /* 0xd394 */
    volatile U_LCD_DITHER_SED_U1 LCD_DITHER_SED_U1;                                     /* 0xd398 */
    volatile U_LCD_DITHER_SED_V1 LCD_DITHER_SED_V1;                                     /* 0xd39c */
    volatile U_LCD_DITHER_SED_W1 LCD_DITHER_SED_W1;                                     /* 0xd3a0 */
    volatile U_LCD_DITHER_SED_Y2 LCD_DITHER_SED_Y2;                                     /* 0xd3a4 */
    volatile U_LCD_DITHER_SED_U2 LCD_DITHER_SED_U2;                                     /* 0xd3a8 */
    volatile U_LCD_DITHER_SED_V2 LCD_DITHER_SED_V2;                                     /* 0xd3ac */
    volatile U_LCD_DITHER_SED_W2 LCD_DITHER_SED_W2;                                     /* 0xd3b0 */
    volatile U_LCD_DITHER_SED_Y3 LCD_DITHER_SED_Y3;                                     /* 0xd3b4 */
    volatile U_LCD_DITHER_SED_U3 LCD_DITHER_SED_U3;                                     /* 0xd3b8 */
    volatile U_LCD_DITHER_SED_V3 LCD_DITHER_SED_V3;                                     /* 0xd3bc */
    volatile U_LCD_DITHER_SED_W3 LCD_DITHER_SED_W3;                                     /* 0xd3c0 */
    volatile U_LCD_DITHER_THR LCD_DITHER_THR;                                           /* 0xd3c4 */
    volatile unsigned int reserved_104[10];                                             /* 0xd3c8~0xd3ec */
    volatile unsigned int LCD_INTF_CHKSUM_Y;                                            /* 0xd3f0 */
    volatile unsigned int LCD_INTF_CHKSUM_U;                                            /* 0xd3f4 */
    volatile unsigned int LCD_INTF_CHKSUM_V;                                            /* 0xd3f8 */
    volatile unsigned int reserved_105[769];                                            /* 0xd3fc~0xdffc */
    volatile U_DHD1_CTRL DHD1_CTRL;                                                     /* 0xe000 */
    volatile U_DHD1_VSYNC1 DHD1_VSYNC1;                                                 /* 0xe004 */
    volatile U_DHD1_VSYNC2 DHD1_VSYNC2;                                                 /* 0xe008 */
    volatile U_DHD1_HSYNC1 DHD1_HSYNC1;                                                 /* 0xe00c */
    volatile U_DHD1_HSYNC2 DHD1_HSYNC2;                                                 /* 0xe010 */
    volatile U_DHD1_VPLUS1 DHD1_VPLUS1;                                                 /* 0xe014 */
    volatile U_DHD1_VPLUS2 DHD1_VPLUS2;                                                 /* 0xe018 */
    volatile U_DHD1_PWR DHD1_PWR;                                                       /* 0xe01c */
    volatile U_DHD1_VTTHD3 DHD1_VTTHD3;                                                 /* 0xe020 */
    volatile U_DHD1_VTTHD DHD1_VTTHD;                                                   /* 0xe024 */
    volatile U_DHD1_PARATHD DHD1_PARATHD;                                               /* 0xe028 */
    volatile U_DHD1_PRECHARGE_THD DHD1_PRECHARGE_THD;                                   /* 0xe02c */
    volatile U_DHD1_START_POS DHD1_START_POS;                                           /* 0xe030 */
    volatile U_DHD1_START_POS1 DHD1_START_POS1;                                         /* 0xe034 */
    volatile U_DHD1_PARAUP DHD1_PARAUP;                                                 /* 0xe038 */
    volatile U_DHD1_SYNC_INV DHD1_SYNC_INV;                                             /* 0xe03c */
    volatile U_DHD1_CLK_DV_CTRL DHD1_CLK_DV_CTRL;                                       /* 0xe040 */
    volatile U_DHD1_RGB_FIX_CTRL DHD1_RGB_FIX_CTRL;                                     /* 0xe044 */
    volatile U_DHD1_LOCKCFG DHD1_LOCKCFG;                                               /* 0xe048 */
    volatile unsigned int DHD1_CAP_FRM_CNT;                                             /* 0xe04c */
    volatile unsigned int DHD1_VDP_FRM_CNT;                                             /* 0xe050 */
    volatile unsigned int DHD1_VSYNC_CAP_VDP_CNT;                                       /* 0xe054 */
    volatile unsigned int DHD1_INTF_CHKSUM_Y;                                           /* 0xe058 */
    volatile unsigned int DHD1_INTF_CHKSUM_U;                                           /* 0xe05c */
    volatile unsigned int DHD1_INTF_CHKSUM_V;                                           /* 0xe060 */
    volatile unsigned int DHD1_INTF1_CHKSUM_Y;                                          /* 0xe064 */
    volatile unsigned int DHD1_INTF1_CHKSUM_U;                                          /* 0xe068 */
    volatile unsigned int DHD1_INTF1_CHKSUM_V;                                          /* 0xe06c */
    volatile U_DHD1_INTF_CHKSUM_HIGH1 DHD1_INTF_CHKSUM_HIGH1;                           /* 0xe070 */
    volatile U_DHD1_INTF_CHKSUM_HIGH2 DHD1_INTF_CHKSUM_HIGH2;                           /* 0xe074 */
    volatile unsigned int reserved_106[3];                                              /* 0xe078~0xe080 */
    volatile unsigned int DHD1_AFIFO_PRE_THD;                                           /* 0xe084 */
    volatile U_DHD1_STATE DHD1_STATE;                                                   /* 0xe088 */
    volatile U_DHD1_UF_STATE DHD1_UF_STATE;                                             /* 0xe08c */
    volatile unsigned int reserved_107[8];                                              /* 0xe090~0xe0ac */
    volatile U_INTF1_DITHER_CTRL INTF1_DITHER_CTRL;                                     /* 0xe0b0 */
    volatile U_INTF1_DITHER_SED_Y0 INTF1_DITHER_SED_Y0;                                 /* 0xe0b4 */
    volatile U_INTF1_DITHER_SED_U0 INTF1_DITHER_SED_U0;                                 /* 0xe0b8 */
    volatile U_INTF1_DITHER_SED_V0 INTF1_DITHER_SED_V0;                                 /* 0xe0bc */
    volatile U_INTF1_DITHER_SED_W0 INTF1_DITHER_SED_W0;                                 /* 0xe0c0 */
    volatile U_INTF1_DITHER_SED_Y1 INTF1_DITHER_SED_Y1;                                 /* 0xe0c4 */
    volatile U_INTF1_DITHER_SED_U1 INTF1_DITHER_SED_U1;                                 /* 0xe0c8 */
    volatile U_INTF1_DITHER_SED_V1 INTF1_DITHER_SED_V1;                                 /* 0xe0cc */
    volatile U_INTF1_DITHER_SED_W1 INTF1_DITHER_SED_W1;                                 /* 0xe0d0 */
    volatile U_INTF1_DITHER_SED_Y2 INTF1_DITHER_SED_Y2;                                 /* 0xe0d4 */
    volatile U_INTF1_DITHER_SED_U2 INTF1_DITHER_SED_U2;                                 /* 0xe0d8 */
    volatile U_INTF1_DITHER_SED_V2 INTF1_DITHER_SED_V2;                                 /* 0xe0dc */
    volatile U_INTF1_DITHER_SED_W2 INTF1_DITHER_SED_W2;                                 /* 0xe0e0 */
    volatile U_INTF1_DITHER_SED_Y3 INTF1_DITHER_SED_Y3;                                 /* 0xe0e4 */
    volatile U_INTF1_DITHER_SED_U3 INTF1_DITHER_SED_U3;                                 /* 0xe0e8 */
    volatile U_INTF1_DITHER_SED_V3 INTF1_DITHER_SED_V3;                                 /* 0xe0ec */
    volatile U_INTF1_DITHER_SED_W3 INTF1_DITHER_SED_W3;                                 /* 0xe0f0 */
    volatile U_INTF1_DITHER_THR INTF1_DITHER_THR;                                       /* 0xe0f4 */
    volatile unsigned int reserved_108[1986];                                           /* 0xe0f8~0xfffc */
    volatile U_MAC_OUTSTANDING MAC_OUTSTANDING;                                         /* 0x10000 */
    volatile U_MAC_CTRL MAC_CTRL;                                                       /* 0x10004 */
    volatile U_MAC_RCHN_PRIO MAC_RCHN_PRIO;                                             /* 0x10008 */
    volatile U_MAC_WCHN_PRIO MAC_WCHN_PRIO;                                             /* 0x1000c */
    volatile U_MAC_RCHN_SEL0 MAC_RCHN_SEL0;                                             /* 0x10010 */
    volatile unsigned int MAC_RCHN_SEL1;                                                /* 0x10014 */
    volatile U_MAC_WCHN_SEL0 MAC_WCHN_SEL0;                                             /* 0x10018 */
    volatile unsigned int reserved_109[3];                                              /* 0x1001c~0x10024 */
    volatile U_MAC_BUS_ERR_CLR MAC_BUS_ERR_CLR;                                         /* 0x10028 */
    volatile U_MAC_BUS_ERR MAC_BUS_ERR;                                                 /* 0x1002c */
    volatile unsigned int MAC_SRC0_STATUS0;                                             /* 0x10030 */
    volatile unsigned int MAC_SRC0_STATUS1;                                             /* 0x10034 */
    volatile unsigned int MAC_SRC1_STATUS0;                                             /* 0x10038 */
    volatile unsigned int MAC_SRC1_STATUS1;                                             /* 0x1003c */
    volatile unsigned int reserved_110[4];                                              /* 0x10040~0x1004c */
    volatile U_MAC_DEBUG_CTRL MAC_DEBUG_CTRL;                                           /* 0x10050 */
    volatile U_MAC_DEBUG_CLR MAC_DEBUG_CLR;                                             /* 0x10054 */
    volatile unsigned int reserved_111[2];                                              /* 0x10058~0x1005c */
    volatile unsigned int MST0_DET_LATENCY;                                             /* 0x10060 */
    volatile unsigned int MST1_DET_LATENCY;                                             /* 0x10064 */
    volatile unsigned int reserved_112[2];                                              /* 0x10068~0x1006c */
    volatile unsigned int MST0_RD_INFO;                                                 /* 0x10070 */
    volatile unsigned int MST0_WR_INFO;                                                 /* 0x10074 */
    volatile unsigned int MST1_RD_INFO;                                                 /* 0x10078 */
    volatile unsigned int MST1_WR_INFO;                                                 /* 0x1007c */
    volatile unsigned int reserved_113[96];                                             /* 0x10080~0x101fc */
    volatile U_VID_READ_CTRL VID_READ_CTRL;                                             /* 0x10200 */
    volatile U_VID_MAC_CTRL VID_MAC_CTRL;                                               /* 0x10204 */
    volatile unsigned int reserved_114[2];                                              /* 0x10208~0x1020c */
    volatile U_VID_OUT_CTRL VID_OUT_CTRL;                                               /* 0x10210 */
    volatile U_VID_MUTE_ALPHA VID_MUTE_ALPHA;                                           /* 0x10214 */
    volatile unsigned int reserved_115;                                                 /* 0x10218 */
    volatile U_VID_MUTE_BK VID_MUTE_BK;                                                 /* 0x1021c */
    volatile unsigned int reserved_116[8];                                              /* 0x10220~0x1023c */
    volatile U_VID_SRC_INFO VID_SRC_INFO;                                               /* 0x10240 */
    volatile U_VID_SRC_RESO VID_SRC_RESO;                                               /* 0x10244 */
    volatile U_VID_SRC_CROP VID_SRC_CROP;                                               /* 0x10248 */
    volatile U_VID_IN_RESO VID_IN_RESO;                                                 /* 0x1024c */
    volatile unsigned int VID_ADDR_H;                                                   /* 0x10250 */
    volatile unsigned int VID_ADDR_L;                                                   /* 0x10254 */
    volatile unsigned int VID_CADDR_H;                                                  /* 0x10258 */
    volatile unsigned int VID_CADDR_L;                                                  /* 0x1025c */
    volatile unsigned int VID_NADDR_H;                                                  /* 0x10260 */
    volatile unsigned int VID_NADDR_L;                                                  /* 0x10264 */
    volatile unsigned int VID_NCADDR_H;                                                 /* 0x10268 */
    volatile unsigned int VID_NCADDR_L;                                                 /* 0x1026c */
    volatile U_VID_STRIDE VID_STRIDE;                                                   /* 0x10270 */
    volatile U_VID_2BIT_STRIDE VID_2BIT_STRIDE;                                         /* 0x10274 */
    volatile U_VID_HEAD_STRIDE VID_HEAD_STRIDE;                                         /* 0x10278 */
    volatile unsigned int reserved_117;                                                 /* 0x1027c */
    volatile U_VID_SMMU_BYPASS VID_SMMU_BYPASS;                                         /* 0x10280 */
    volatile unsigned int reserved_118[3];                                              /* 0x10284~0x1028c */
    volatile unsigned int VID_HEAD_ADDR_H;                                              /* 0x10290 */
    volatile unsigned int VID_HEAD_ADDR_L;                                              /* 0x10294 */
    volatile unsigned int VID_HEAD_CADDR_H;                                             /* 0x10298 */
    volatile unsigned int VID_HEAD_CADDR_L;                                             /* 0x1029c */
    volatile U_VID_TESTPAT_CFG VID_TESTPAT_CFG;                                         /* 0x102a0 */
    volatile U_VID_TESTPAT_SEED VID_TESTPAT_SEED;                                       /* 0x102a4 */
    volatile unsigned int VID_TESTPAT_CHKSUM_Y;                                         /* 0x102a8 */
    volatile unsigned int VID_TESTPAT_CHKSUM_C;                                         /* 0x102ac */
    volatile unsigned int reserved_119[4];                                              /* 0x102b0~0x102bc */
    volatile U_VID_LATENCY_CLC VID_LATENCY_CLC;                                         /* 0x102c0 */
    volatile unsigned int VID_LATENCY_L_FRAM0;                                          /* 0x102c4 */
    volatile U_VID_LATENCY_L_LINE0 VID_LATENCY_L_LINE0;                                 /* 0x102c8 */
    volatile unsigned int VID_LATENCY_L_FRAM1;                                          /* 0x102cc */
    volatile U_VID_LATENCY_L_LINE1 VID_LATENCY_L_LINE1;                                 /* 0x102d0 */
    volatile unsigned int VID_LATENCY_C_FRAM0;                                          /* 0x102d4 */
    volatile U_VID_LATENCY_C_LINE0 VID_LATENCY_C_LINE0;                                 /* 0x102d8 */
    volatile unsigned int VID_LATENCY_C_FRAM1;                                          /* 0x102dc */
    volatile U_VID_LATENCY_C_LINE1 VID_LATENCY_C_LINE1;                                 /* 0x102e0 */
    volatile unsigned int reserved_120[7];                                              /* 0x102e4~0x102fc */
    volatile U_VID_DEBUG_CTRL VID_DEBUG_CTRL;                                           /* 0x10300 */
    volatile U_VID_DEBUG_STATE_CLR VID_DEBUG_STATE_CLR;                                 /* 0x10304 */
    volatile unsigned int reserved_121[2];                                              /* 0x10308~0x1030c */
    volatile U_VID_DEBUG_L_STA0 VID_DEBUG_L_STA0;                                       /* 0x10310 */
    volatile unsigned int VID_DEBUG_L_STA1;                                             /* 0x10314 */
    volatile unsigned int VID_DEBUG_L_STA2;                                             /* 0x10318 */
    volatile unsigned int reserved_122;                                                 /* 0x1031c */
    volatile U_VID_DEBUG_C_STA0 VID_DEBUG_C_STA0;                                       /* 0x10320 */
    volatile unsigned int VID_DEBUG_C_STA1;                                             /* 0x10324 */
    volatile unsigned int VID_DEBUG_C_STA2;                                             /* 0x10328 */
    volatile unsigned int reserved_123[5];                                              /* 0x1032c~0x1033c */
    volatile U_VID_DCMP_CTRL VID_DCMP_CTRL;                                             /* 0x10340 */
    volatile unsigned int reserved_124;                                                 /* 0x10344 */
    volatile unsigned int VID_DCMP_L_FSIZE;                                             /* 0x10348 */
    volatile unsigned int reserved_125;                                                 /* 0x1034c */
    volatile U_VID_DCMPERRCLR VID_DCMPERRCLR;                                           /* 0x10350 */
    volatile U_VID_DCMP_ERR VID_DCMP_ERR;                                               /* 0x10354 */
    volatile unsigned int reserved_126[10];                                             /* 0x10358~0x1037c */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_CTRL ICE_V2R1_SEG_256X1_DCMP_CTRL;               /* 0x10380 */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_RESO ICE_V2R1_SEG_256X1_DCMP_RESO;               /* 0x10384 */
    volatile unsigned int reserved_127[2];                                              /* 0x10388~0x1038c */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_STA ICE_V2R1_SEG_256X1_DCMP_STA;                 /* 0x10390 */
    volatile unsigned int ICE_V2R1_SEG_256X1_DCMP_DEBUG;                                /* 0x10394 */
    volatile unsigned int reserved_128[2];                                              /* 0x10398~0x1039c */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_CTRL_2P ICE_V2R1_SEG_256X1_DCMP_CTRL_2P;         /* 0x103a0 */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_RESO_2P ICE_V2R1_SEG_256X1_DCMP_RESO_2P;         /* 0x103a4 */
    volatile unsigned int reserved_129[2];                                              /* 0x103a8~0x103ac */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_STA_2P ICE_V2R1_SEG_256X1_DCMP_STA_2P;           /* 0x103b0 */
    volatile unsigned int ICE_V2R1_SEG_256X1_DCMP_DEBUG_2P;                             /* 0x103b4 */
    volatile unsigned int reserved_130[2];                                              /* 0x103b8~0x103bc */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_CTRL_CHM ICE_V2R1_SEG_256X1_DCMP_CTRL_CHM;       /* 0x103c0 */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_RESO_CHM ICE_V2R1_SEG_256X1_DCMP_RESO_CHM;       /* 0x103c4 */
    volatile unsigned int reserved_131[2];                                              /* 0x103c8~0x103cc */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_STA_CHM ICE_V2R1_SEG_256X1_DCMP_STA_CHM;         /* 0x103d0 */
    volatile unsigned int ICE_V2R1_SEG_256X1_DCMP_DEBUG_CHM;                            /* 0x103d4 */
    volatile unsigned int reserved_132[2];                                              /* 0x103d8~0x103dc */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_CTRL_2P_CHM ICE_V2R1_SEG_256X1_DCMP_CTRL_2P_CHM; /* 0x103e0 */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_RESO_2P_CHM ICE_V2R1_SEG_256X1_DCMP_RESO_2P_CHM; /* 0x103e4 */
    volatile unsigned int reserved_133[2];                                              /* 0x103e8~0x103ec */
    volatile U_ICE_V2R1_SEG_256X1_DCMP_STA_2P_CHM ICE_V2R1_SEG_256X1_DCMP_STA_2P_CHM;   /* 0x103f0 */
    volatile unsigned int ICE_V2R1_SEG_256X1_DCMP_DEBUG_2P_CHM;                         /* 0x103f4 */
    volatile unsigned int reserved_134[642];                                            /* 0x103f8~0x10dfc */
    volatile U_GFX_READ_CTRL GFX_READ_CTRL;                                             /* 0x10e00 */
    volatile U_GFX_MAC_CTRL GFX_MAC_CTRL;                                               /* 0x10e04 */
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;                                               /* 0x10e08 */
    volatile unsigned int reserved_135;                                                 /* 0x10e0c */
    volatile U_GFX_MUTE_ALPHA GFX_MUTE_ALPHA;                                           /* 0x10e10 */
    volatile U_GFX_MUTE_BK GFX_MUTE_BK;                                                 /* 0x10e14 */
    volatile unsigned int reserved_136[2];                                              /* 0x10e18~0x10e1c */
    volatile U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;                                         /* 0x10e20 */
    volatile unsigned int reserved_137;                                                 /* 0x10e24 */
    volatile U_GFX_1555_ALPHA GFX_1555_ALPHA;                                           /* 0x10e28 */
    volatile unsigned int reserved_138[5];                                              /* 0x10e2c~0x10e3c */
    volatile U_GFX_SRC_INFO GFX_SRC_INFO;                                               /* 0x10e40 */
    volatile U_GFX_SRC_RESO GFX_SRC_RESO;                                               /* 0x10e44 */
    volatile U_GFX_SRC_CROP GFX_SRC_CROP;                                               /* 0x10e48 */
    volatile U_GFX_IRESO GFX_IRESO;                                                     /* 0x10e4c */
    volatile unsigned int GFX_ADDR_H;                                                   /* 0x10e50 */
    volatile unsigned int GFX_ADDR_L;                                                   /* 0x10e54 */
    volatile unsigned int GFX_NADDR_H;                                                  /* 0x10e58 */
    volatile unsigned int GFX_NADDR_L;                                                  /* 0x10e5c */
    volatile U_GFX_STRIDE GFX_STRIDE;                                                   /* 0x10e60 */
    volatile unsigned int reserved_139[3];                                              /* 0x10e64~0x10e6c */
    volatile unsigned int GFX_DCMP_ADDR_H;                                              /* 0x10e70 */
    volatile unsigned int GFX_DCMP_ADDR_L;                                              /* 0x10e74 */
    volatile unsigned int GFX_DCMP_NADDR_H;                                             /* 0x10e78 */
    volatile unsigned int GFX_DCMP_NADDR_L;                                             /* 0x10e7c */
    volatile unsigned int reserved_140[32];                                             /* 0x10e80~0x10efc */
    volatile U_GFX_CKEY_MAX GFX_CKEY_MAX;                                               /* 0x10f00 */
    volatile U_GFX_CKEY_MIN GFX_CKEY_MIN;                                               /* 0x10f04 */
    volatile U_GFX_CKEY_MASK GFX_CKEY_MASK;                                             /* 0x10f08 */
    volatile unsigned int reserved_141;                                                 /* 0x10f0c */
    volatile U_GFX_TESTPAT_CFG GFX_TESTPAT_CFG;                                         /* 0x10f10 */
    volatile U_GFX_TESTPAT_SEED GFX_TESTPAT_SEED;                                       /* 0x10f14 */
    volatile unsigned int reserved_142[2];                                              /* 0x10f18~0x10f1c */
    volatile U_GFX_LATENCY_CLR GFX_LATENCY_CLR;                                         /* 0x10f20 */
    volatile U_GFX_LINE_LATENCY GFX_LINE_LATENCY;                                       /* 0x10f24 */
    volatile unsigned int GFX_FRAM_LATENCY;                                             /* 0x10f28 */
    volatile unsigned int reserved_143;                                                 /* 0x10f2c */
    volatile U_GFX_DEBUG_CTRL GFX_DEBUG_CTRL;                                           /* 0x10f30 */
    volatile U_GFX_STA_CLR GFX_STA_CLR;                                                 /* 0x10f34 */
    volatile unsigned int GFX_STATE0;                                                   /* 0x10f38 */
    volatile unsigned int GFX_STATE1;                                                   /* 0x10f3c */
    volatile unsigned int GFX_STATE2;                                                   /* 0x10f40 */
    volatile unsigned int GFX_STATE3;                                                   /* 0x10f44 */
    volatile unsigned int reserved_144[3];                                              /* 0x10f48~0x10f50 */
    volatile unsigned int GFX_DCMP_FRAMESIZE0;                                          /* 0x10f54 */
    volatile unsigned int GFX_DCMP_FRAMESIZE1;                                          /* 0x10f58 */
    volatile U_GFX_DCMPERRCLR GFX_DCMPERRCLR;                                           /* 0x10f5c */
    volatile U_GFX_DCMP_ERR GFX_DCMP_ERR;                                               /* 0x10f60 */
    volatile unsigned int GFX_DCMP_STATE;                                               /* 0x10f64 */
    volatile unsigned int reserved_145[6];                                              /* 0x10f68~0x10f7c */
    volatile U_GFX_OSD_GLB_INFO GFX_OSD_GLB_INFO;                                       /* 0x10f80 */
    volatile U_GFX_OSD_FRAME_SIZE GFX_OSD_FRAME_SIZE;                                   /* 0x10f84 */
    volatile unsigned int reserved_146[2];                                              /* 0x10f88~0x10f8c */
    volatile U_GFX_OSD_DBG_REG GFX_OSD_DBG_REG;                                         /* 0x10f90 */
    volatile U_GFX_OSD_DBG_REG1 GFX_OSD_DBG_REG1;                                       /* 0x10f94 */
    volatile unsigned int reserved_147[538];                                            /* 0x10f98~0x117fc */
    volatile U_WBC_CTRL WBC_CTRL;                                                       /* 0x11800 */
    volatile U_WBC_MAC_CTRL WBC_MAC_CTRL;                                               /* 0x11804 */
    volatile unsigned int reserved_148[3];                                              /* 0x11808~0x11810 */
    volatile U_WBC_SMMU_BYPASS WBC_SMMU_BYPASS;                                         /* 0x11814 */
    volatile unsigned int reserved_149[2];                                              /* 0x11818~0x1181c */
    volatile U_WBC_LOWDLYCTRL WBC_LOWDLYCTRL;                                           /* 0x11820 */
    volatile unsigned int WBC_TUNLADDR_H;                                               /* 0x11824 */
    volatile unsigned int WBC_TUNLADDR_L;                                               /* 0x11828 */
    volatile U_WBC_LOWDLYSTA WBC_LOWDLYSTA;                                             /* 0x1182c */
    volatile unsigned int reserved_150[8];                                              /* 0x11830~0x1184c */
    volatile unsigned int WBC_YADDR_H;                                                  /* 0x11850 */
    volatile unsigned int WBC_YADDR_L;                                                  /* 0x11854 */
    volatile unsigned int WBC_CADDR_H;                                                  /* 0x11858 */
    volatile unsigned int WBC_CADDR_L;                                                  /* 0x1185c */
    volatile U_WBC_YSTRIDE WBC_YSTRIDE;                                                 /* 0x11860 */
    volatile U_WBC_CSTRIDE WBC_CSTRIDE;                                                 /* 0x11864 */
    volatile unsigned int reserved_151[2];                                              /* 0x11868~0x1186c */
    volatile unsigned int WBC_YNADDR_H;                                                 /* 0x11870 */
    volatile unsigned int WBC_YNADDR_L;                                                 /* 0x11874 */
    volatile unsigned int WBC_CNADDR_H;                                                 /* 0x11878 */
    volatile unsigned int WBC_CNADDR_L;                                                 /* 0x1187c */
    volatile U_WBC_YNSTRIDE WBC_YNSTRIDE;                                               /* 0x11880 */
    volatile U_WBC_CNSTRIDE WBC_CNSTRIDE;                                               /* 0x11884 */
    volatile unsigned int reserved_152[10];                                             /* 0x11888~0x118ac */
    volatile U_WBC_STA WBC_STA;                                                         /* 0x118b0 */
    volatile U_WBC_LINE_NUM WBC_LINE_NUM;                                               /* 0x118b4 */
    volatile U_WBC_CAP_RESO WBC_CAP_RESO;                                               /* 0x118b8 */
    volatile unsigned int WBC_CAP_INFO;                                                 /* 0x118bc */
    volatile unsigned int reserved_153[16];                                             /* 0x118c0~0x118fc */
    volatile U_ICE_V2R1_SEG_256X1_CMP_CTRL ICE_V2R1_SEG_256X1_CMP_CTRL;                 /* 0x11900 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_SAD_THR ICE_V2R1_SEG_256X1_CMP_SAD_THR;           /* 0x11904 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_SIM_THR ICE_V2R1_SEG_256X1_CMP_SIM_THR;           /* 0x11908 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_RESO ICE_V2R1_SEG_256X1_CMP_RESO;                 /* 0x1190c */
    volatile U_ICE_V2R1_SEG_256X1_CMP_MAX_BIT ICE_V2R1_SEG_256X1_CMP_MAX_BIT;           /* 0x11910 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_SLC_BIT ICE_V2R1_SEG_256X1_CMP_SLC_BIT;           /* 0x11914 */
    volatile unsigned int reserved_154[2];                                              /* 0x11918~0x1191c */
    volatile unsigned int ICE_V2R1_SEG_256X1_CMP_DEBUG;                                 /* 0x11920 */
    volatile unsigned int reserved_155[23];                                             /* 0x11924~0x1197c */
    volatile U_ICE_V2R1_SEG_256X1_CMP_CTRL_CHM ICE_V2R1_SEG_256X1_CMP_CTRL_CHM;         /* 0x11980 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_SAD_THR_CHM ICE_V2R1_SEG_256X1_CMP_SAD_THR_CHM;   /* 0x11984 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_SIM_THR_CHM ICE_V2R1_SEG_256X1_CMP_SIM_THR_CHM;   /* 0x11988 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_RESO_CHM ICE_V2R1_SEG_256X1_CMP_RESO_CHM;         /* 0x1198c */
    volatile U_ICE_V2R1_SEG_256X1_CMP_MAX_BIT_CHM ICE_V2R1_SEG_256X1_CMP_MAX_BIT_CHM;   /* 0x11990 */
    volatile U_ICE_V2R1_SEG_256X1_CMP_SLC_BIT_CHM ICE_V2R1_SEG_256X1_CMP_SLC_BIT_CHM;   /* 0x11994 */
    volatile unsigned int reserved_156[2];                                              /* 0x11998~0x1199c */
    volatile unsigned int ICE_V2R1_SEG_256X1_CMP_DEBUG_CHM;                             /* 0x119a0 */
    volatile unsigned int reserved_157[279];                                            /* 0x119a4~0x11dfc */
    volatile U_WBC_CMP_CTRL WBC_CMP_CTRL;                                               /* 0x11e00 */
    volatile U_WBC_CMP_UPD WBC_CMP_UPD;                                                 /* 0x11e04 */
    volatile U_WBC_CMP_HEIGHT WBC_CMP_HEIGHT;                                           /* 0x11e08 */
    volatile U_WBC_CMP_ORESO WBC_CMP_ORESO;                                             /* 0x11e0c */
    volatile unsigned int WBC_CMP_YADDR;                                                /* 0x11e10 */
    volatile unsigned int WBC_CMP_YADDR1;                                               /* 0x11e14 */
    volatile unsigned int WBC_CMP_CADDR;                                                /* 0x11e18 */
    volatile unsigned int WBC_CMP_CADDR1;                                               /* 0x11e1c */
    volatile unsigned int WBC_CMP_ADDR0_T0;                                             /* 0x11e20 */
    volatile unsigned int WBC_CMP_ADDR1_T0;                                             /* 0x11e24 */
    volatile unsigned int WBC_CMP_ADDR0_T1;                                             /* 0x11e28 */
    volatile unsigned int WBC_CMP_ADDR1_T1;                                             /* 0x11e2c */
    volatile unsigned int WBC_CMP_L_FSIZE;                                              /* 0x11e30 */
    volatile unsigned int WBC_CMP_C_FSIZE;                                              /* 0x11e34 */
    volatile unsigned int WBC_CMP_T0_FSIZE;                                             /* 0x11e38 */
    volatile unsigned int WBC_CMP_T1_FSIZE;                                             /* 0x11e3c */
    volatile unsigned int WBC_SETY_FSIZE;                                               /* 0x11e40 */
    volatile unsigned int WBC_SETC_FSIZE;                                               /* 0x11e44 */
    volatile unsigned int WBC_SETT0_FSIZE;                                              /* 0x11e48 */
    volatile unsigned int WBC_SETT1_FSIZE;                                              /* 0x11e4c */
    volatile U_WBC_OD_STATE WBC_OD_STATE;                                               /* 0x11e50 */
    volatile unsigned int reserved_158[43];                                             /* 0x11e54~0x11efc */
    volatile U_OD_PIC_OSD_GLB_INFO OD_PIC_OSD_GLB_INFO;                                 /* 0x11f00 */
    volatile U_OD_PIC_OSD_FRAME_SIZE OD_PIC_OSD_FRAME_SIZE;                             /* 0x11f04 */
    volatile U_OD_PIC_OSD_RC_CFG0 OD_PIC_OSD_RC_CFG0;                                   /* 0x11f08 */
    volatile U_OD_PIC_OSD_RC_CFG1 OD_PIC_OSD_RC_CFG1;                                   /* 0x11f0c */
    volatile U_OD_PIC_OSD_RC_CFG2 OD_PIC_OSD_RC_CFG2;                                   /* 0x11f10 */
    volatile U_OD_PIC_OSD_RC_CFG3 OD_PIC_OSD_RC_CFG3;                                   /* 0x11f14 */
    volatile U_OD_PIC_OSD_RC_CFG4 OD_PIC_OSD_RC_CFG4;                                   /* 0x11f18 */
    volatile U_OD_PIC_OSD_RC_CFG5 OD_PIC_OSD_RC_CFG5;                                   /* 0x11f1c */
    volatile U_OD_PIC_OSD_RC_CFG6 OD_PIC_OSD_RC_CFG6;                                   /* 0x11f20 */
    volatile U_OD_PIC_OSD_RC_CFG7 OD_PIC_OSD_RC_CFG7;                                   /* 0x11f24 */
    volatile U_OD_PIC_OSD_RC_CFG8 OD_PIC_OSD_RC_CFG8;                                   /* 0x11f28 */
    volatile U_OD_PIC_OSD_RC_CFG9 OD_PIC_OSD_RC_CFG9;                                   /* 0x11f2c */
    volatile U_OD_PIC_OSD_RC_CFG10 OD_PIC_OSD_RC_CFG10;                                 /* 0x11f30 */
    volatile U_OD_PIC_OSD_RC_CFG11 OD_PIC_OSD_RC_CFG11;                                 /* 0x11f34 */
    volatile U_OD_PIC_OSD_RC_CFG12 OD_PIC_OSD_RC_CFG12;                                 /* 0x11f38 */
    volatile U_OD_PIC_OSD_RC_CFG13 OD_PIC_OSD_RC_CFG13;                                 /* 0x11f3c */
    volatile U_OD_PIC_OSD_RC_CFG14 OD_PIC_OSD_RC_CFG14;                                 /* 0x11f40 */
    volatile U_OD_PIC_OSD_RC_CFG15 OD_PIC_OSD_RC_CFG15;                                 /* 0x11f44 */
    volatile U_OD_PIC_OSD_RC_CFG16 OD_PIC_OSD_RC_CFG16;                                 /* 0x11f48 */
    volatile U_OD_PIC_OSD_RC_CFG17 OD_PIC_OSD_RC_CFG17;                                 /* 0x11f4c */
    volatile U_OD_PIC_OSD_RC_CFG18 OD_PIC_OSD_RC_CFG18;                                 /* 0x11f50 */
    volatile U_OD_PIC_OSD_RC_CFG19 OD_PIC_OSD_RC_CFG19;                                 /* 0x11f54 */
    volatile unsigned int reserved_159[2];                                              /* 0x11f58~0x11f5c */
    volatile U_OD_PIC_OSD_STAT_THR OD_PIC_OSD_STAT_THR;                                 /* 0x11f60 */
    volatile U_OD_PIC_OSD_PCMP OD_PIC_OSD_PCMP;                                         /* 0x11f64 */
    volatile unsigned int reserved_160[6];                                              /* 0x11f68~0x11f7c */
    volatile U_OD_PIC_OSD_BS_SIZE OD_PIC_OSD_BS_SIZE;                                   /* 0x11f80 */
    volatile U_OD_PIC_OSD_WORST_ROW OD_PIC_OSD_WORST_ROW;                               /* 0x11f84 */
    volatile U_OD_PIC_OSD_BEST_ROW OD_PIC_OSD_BEST_ROW;                                 /* 0x11f88 */
    volatile U_OD_PIC_OSD_STAT_INFO OD_PIC_OSD_STAT_INFO;                               /* 0x11f8c */
    volatile unsigned int OD_PIC_OSD_DEBUG0;                                            /* 0x11f90 */
    volatile unsigned int OD_PIC_OSD_DEBUG1;                                            /* 0x11f94 */
    volatile unsigned int reserved_161[26];                                             /* 0x11f98~0x11ffc */
    volatile U_V0_MRG_CTRL V0_MRG_CTRL;                                                 /* 0x12000 */
    volatile U_V0_MRG_DISP_POS V0_MRG_DISP_POS;                                         /* 0x12004 */
    volatile U_V0_MRG_DISP_RESO V0_MRG_DISP_RESO;                                       /* 0x12008 */
    volatile U_V0_MRG_SRC_RESO V0_MRG_SRC_RESO;                                         /* 0x1200c */
    volatile U_V0_MRG_SRC_OFFSET V0_MRG_SRC_OFFSET;                                     /* 0x12010 */
    volatile unsigned int V0_MRG_Y_ADDR;                                                /* 0x12014 */
    volatile unsigned int V0_MRG_C_ADDR;                                                /* 0x12018 */
    volatile U_V0_MRG_STRIDE V0_MRG_STRIDE;                                             /* 0x1201c */
    volatile unsigned int V0_MRG_YH_ADDR;                                               /* 0x12020 */
    volatile unsigned int V0_MRG_CH_ADDR;                                               /* 0x12024 */
    volatile U_V0_MRG_HSTRIDE V0_MRG_HSTRIDE;                                           /* 0x12028 */
    volatile unsigned int reserved_162[5];                                              /* 0x1202c~0x1203c */
    volatile U_V0_MRG_READ_CTRL V0_MRG_READ_CTRL;                                       /* 0x12040 */
    volatile U_V0_MRG_READ_EN V0_MRG_READ_EN;                                           /* 0x12044 */
    volatile unsigned int reserved_163[750];                                            /* 0x12048~0x12bfc */
    volatile U_V1_MRG_CTRL V1_MRG_CTRL;                                                 /* 0x12c00 */
    volatile U_V1_MRG_DISP_POS V1_MRG_DISP_POS;                                         /* 0x12c04 */
    volatile U_V1_MRG_DISP_RESO V1_MRG_DISP_RESO;                                       /* 0x12c08 */
    volatile U_V1_MRG_SRC_RESO V1_MRG_SRC_RESO;                                         /* 0x12c0c */
    volatile U_V1_MRG_SRC_OFFSET V1_MRG_SRC_OFFSET;                                     /* 0x12c10 */
    volatile unsigned int V1_MRG_Y_ADDR;                                                /* 0x12c14 */
    volatile unsigned int V1_MRG_C_ADDR;                                                /* 0x12c18 */
    volatile U_V1_MRG_STRIDE V1_MRG_STRIDE;                                             /* 0x12c1c */
    volatile unsigned int V1_MRG_YH_ADDR;                                               /* 0x12c20 */
    volatile unsigned int V1_MRG_CH_ADDR;                                               /* 0x12c24 */
    volatile U_V1_MRG_HSTRIDE V1_MRG_HSTRIDE;                                           /* 0x12c28 */
    volatile unsigned int reserved_164[5];                                              /* 0x12c2c~0x12c3c */
    volatile U_V1_MRG_READ_CTRL V1_MRG_READ_CTRL;                                       /* 0x12c40 */
    volatile U_V1_MRG_READ_EN V1_MRG_READ_EN;                                           /* 0x12c44 */
    volatile unsigned int reserved_165[238];                                            /* 0x12c48~0x12ffc */
    volatile U_VPSS_RCH_DEI_BUF_CTRL VPSS_RCH_DEI_BUF_CTRL;                             /* 0x13000 */
    volatile U_VPSS_RCH_DEI_BUF_IMGSIZE VPSS_RCH_DEI_BUF_IMGSIZE;                       /* 0x13004 */
    volatile U_VPSS_RCH_DEI_BUF_OFFSET VPSS_RCH_DEI_BUF_OFFSET;                         /* 0x13008 */
    volatile U_VPSS_RCH_DEI_BUF_STRIDE VPSS_RCH_DEI_BUF_STRIDE;                         /* 0x1300c */
    volatile unsigned int VPSS_RCH_DEI_BUF_Y_START_ADDR;                                /* 0x13010 */
    volatile unsigned int VPSS_RCH_DEI_BUF_Y_END_ADDR;                                  /* 0x13014 */
    volatile unsigned int VPSS_RCH_DEI_BUF_C_START_ADDR;                                /* 0x13018 */
    volatile unsigned int VPSS_RCH_DEI_BUF_C_END_ADDR;                                  /* 0x1301c */
    volatile unsigned int VPSS_RCH_REF_Y_ADDR;                                          /* 0x13020 */
    volatile unsigned int VPSS_RCH_REF_C_ADDR;                                          /* 0x13024 */
    volatile unsigned int VPSS_RCH_REF_Y_RADDR;                                         /* 0x13028 */
    volatile unsigned int VPSS_RCH_REF_C_RADDR;                                         /* 0x1302c */
    volatile unsigned int VPSS_RCH_CUR_Y_ADDR;                                          /* 0x13030 */
    volatile unsigned int VPSS_RCH_CUR_C_ADDR;                                          /* 0x13034 */
    volatile unsigned int VPSS_RCH_CUR_Y_RADDR;                                         /* 0x13038 */
    volatile unsigned int VPSS_RCH_CUR_C_RADDR;                                         /* 0x1303c */
    volatile unsigned int VPSS_RCH_NX1_Y_ADDR;                                          /* 0x13040 */
    volatile unsigned int VPSS_RCH_NX1_C_ADDR;                                          /* 0x13044 */
    volatile unsigned int VPSS_RCH_NX1_Y_RADDR;                                         /* 0x13048 */
    volatile unsigned int VPSS_RCH_NX1_C_RADDR;                                         /* 0x1304c */
    volatile unsigned int VPSS_WCH_RFR_Y_ADDR;                                          /* 0x13050 */
    volatile unsigned int VPSS_WCH_RFR_C_ADDR;                                          /* 0x13054 */
    volatile unsigned int VPSS_WCH_RFR_Y_WADDR;                                         /* 0x13058 */
    volatile unsigned int VPSS_WCH_RFR_C_WADDR;                                         /* 0x1305c */
    volatile unsigned int reserved_166[8];                                              /* 0x13060~0x1307c */
    volatile U_VPSS_RCH_RC_BUF_CTRL VPSS_RCH_RC_BUF_CTRL;                               /* 0x13080 */
    volatile U_VPSS_RCH_RC_BUF_IMGSIZE VPSS_RCH_RC_BUF_IMGSIZE;                         /* 0x13084 */
    volatile U_VPSS_RCH_RC_BUF_OFFSET VPSS_RCH_RC_BUF_OFFSET;                           /* 0x13088 */
    volatile U_VPSS_RCH_RC_BUF_STRIDE VPSS_RCH_RC_BUF_STRIDE;                           /* 0x1308c */
    volatile unsigned int VPSS_RCH_RC_BUF_Y_START_ADDR;                                 /* 0x13090 */
    volatile unsigned int VPSS_RCH_RC_BUF_Y_END_ADDR;                                   /* 0x13094 */
    volatile unsigned int VPSS_RCH_RC_BUF_C_START_ADDR;                                 /* 0x13098 */
    volatile unsigned int VPSS_RCH_RC_BUF_C_END_ADDR;                                   /* 0x1309c */
    volatile unsigned int VPSS_RCH_REE_Y_ADDR;                                          /* 0x130a0 */
    volatile unsigned int VPSS_RCH_REE_C_ADDR;                                          /* 0x130a4 */
    volatile unsigned int VPSS_RCH_REE_Y_RADDR;                                         /* 0x130a8 */
    volatile unsigned int VPSS_RCH_REE_C_RADDR;                                         /* 0x130ac */
    volatile unsigned int VPSS_WCH_CUE_Y_ADDR;                                          /* 0x130b0 */
    volatile unsigned int VPSS_WCH_CUE_C_ADDR;                                          /* 0x130b4 */
    volatile unsigned int VPSS_WCH_CUE_Y_WADDR;                                         /* 0x130b8 */
    volatile unsigned int VPSS_WCH_CUE_C_WADDR;                                         /* 0x130bc */
    volatile unsigned int reserved_167[16];                                             /* 0x130c0~0x130fc */
    volatile U_VPSS_RCH_NRMD_BUF_CTRL VPSS_RCH_NRMD_BUF_CTRL;                           /* 0x13100 */
    volatile U_VPSS_RCH_NRMD_BUF_IMGSIZE VPSS_RCH_NRMD_BUF_IMGSIZE;                     /* 0x13104 */
    volatile U_VPSS_RCH_NRMD_BUF_STRIDE VPSS_RCH_NRMD_BUF_STRIDE;                       /* 0x13108 */
    volatile unsigned int VPSS_RCH_NRMD_BUF_START_ADDR;                                 /* 0x1310c */
    volatile unsigned int VPSS_RCH_NRMD_BUF_END_ADDR;                                   /* 0x13110 */
    volatile unsigned int VPSS_RCH_TRMD_ADDR;                                           /* 0x13114 */
    volatile unsigned int VPSS_RCH_TRMD_RADDR;                                          /* 0x13118 */
    volatile unsigned int VPSS_RCH_SRMD_ADDR;                                           /* 0x1311c */
    volatile unsigned int VPSS_RCH_SRMD_RADDR;                                          /* 0x13120 */
    volatile unsigned int VPSS_WCH_TWMD_ADDR;                                           /* 0x13124 */
    volatile unsigned int VPSS_WCH_TWMD_WADDR;                                          /* 0x13128 */
    volatile unsigned int reserved_168[5];                                              /* 0x1312c~0x1313c */
    volatile U_VPSS_RCH_PRJH_BUF_CTRL VPSS_RCH_PRJH_BUF_CTRL;                           /* 0x13140 */
    volatile U_VPSS_RCH_PRJH_BUF_IMGSIZE VPSS_RCH_PRJH_BUF_IMGSIZE;                     /* 0x13144 */
    volatile U_VPSS_RCH_PRJH_BUF_STRIDE VPSS_RCH_PRJH_BUF_STRIDE;                       /* 0x13148 */
    volatile unsigned int VPSS_RCH_PRJH_BUF_START_ADDR;                                 /* 0x1314c */
    volatile unsigned int VPSS_RCH_PRJH_BUF_END_ADDR;                                   /* 0x13150 */
    volatile unsigned int VPSS_RCH_PRJHCUR_ADDR;                                        /* 0x13154 */
    volatile unsigned int VPSS_RCH_PRJHCUR_RADDR;                                       /* 0x13158 */
    volatile unsigned int VPSS_WCH_PRJHNX2_ADDR;                                        /* 0x1315c */
    volatile unsigned int VPSS_WCH_PRJHNX2_WADDR;                                       /* 0x13160 */
    volatile unsigned int reserved_169[7];                                              /* 0x13164~0x1317c */
    volatile U_VPSS_RCH_DIMD_BUF_CTRL VPSS_RCH_DIMD_BUF_CTRL;                           /* 0x13180 */
    volatile U_VPSS_RCH_DIMD_BUF_IMGSIZE VPSS_RCH_DIMD_BUF_IMGSIZE;                     /* 0x13184 */
    volatile U_VPSS_RCH_DIMD_BUF_STRIDE VPSS_RCH_DIMD_BUF_STRIDE;                       /* 0x13188 */
    volatile unsigned int VPSS_RCH_DIMD_BUF_START_ADDR;                                 /* 0x1318c */
    volatile unsigned int VPSS_RCH_DIMD_BUF_END_ADDR;                                   /* 0x13190 */
    volatile unsigned int VPSS_RCH_RST_ADDR;                                            /* 0x13194 */
    volatile unsigned int VPSS_RCH_RST_RADDR;                                           /* 0x13198 */
    volatile unsigned int VPSS_WCH_WST_ADDR;                                            /* 0x1319c */
    volatile unsigned int VPSS_WCH_WST_WADDR;                                           /* 0x131a0 */
    volatile unsigned int reserved_170[7];                                              /* 0x131a4~0x131bc */
    volatile U_VPSS_RCH_PRJV_BUF_CTRL VPSS_RCH_PRJV_BUF_CTRL;                           /* 0x131c0 */
    volatile U_VPSS_RCH_PRJV_BUF_IMGSIZE VPSS_RCH_PRJV_BUF_IMGSIZE;                     /* 0x131c4 */
    volatile U_VPSS_RCH_PRJV_BUF_STRIDE VPSS_RCH_PRJV_BUF_STRIDE;                       /* 0x131c8 */
    volatile unsigned int VPSS_RCH_PRJV_BUF_START_ADDR;                                 /* 0x131cc */
    volatile unsigned int VPSS_RCH_PRJV_BUF_END_ADDR;                                   /* 0x131d0 */
    volatile unsigned int VPSS_RCH_PRJVCUR_ADDR;                                        /* 0x131d4 */
    volatile unsigned int VPSS_RCH_PRJVCUR_RADDR;                                       /* 0x131d8 */
    volatile unsigned int VPSS_WCH_PRJVNX2_ADDR;                                        /* 0x131dc */
    volatile unsigned int VPSS_WCH_PRJVNX2_WADDR;                                       /* 0x131e0 */
    volatile unsigned int reserved_171[7];                                              /* 0x131e4~0x131fc */
    volatile U_VPSS_RCH_RGMV_BUF_CTRL VPSS_RCH_RGMV_BUF_CTRL;                           /* 0x13200 */
    volatile U_VPSS_RCH_RGMV_BUF_IMGSIZE VPSS_RCH_RGMV_BUF_IMGSIZE;                     /* 0x13204 */
    volatile U_VPSS_RCH_RGMV_BUF_STRIDE VPSS_RCH_RGMV_BUF_STRIDE;                       /* 0x13208 */
    volatile unsigned int VPSS_RCH_RGMV_BUF_START_ADDR;                                 /* 0x1320c */
    volatile unsigned int VPSS_RCH_RGMV_BUF_END_ADDR;                                   /* 0x13210 */
    volatile unsigned int VPSS_RCH_RGMVCUR_ADDR;                                        /* 0x13214 */
    volatile unsigned int VPSS_RCH_RGMVCUR_RADDR;                                       /* 0x13218 */
    volatile unsigned int VPSS_RCH_RGMVNX1_ADDR;                                        /* 0x1321c */
    volatile unsigned int VPSS_RCH_RGMVNX1_RADDR;                                       /* 0x13220 */
    volatile unsigned int VPSS_WCH_RGMVNX2_ADDR;                                        /* 0x13224 */
    volatile unsigned int VPSS_WCH_RGMVNX2_WADDR;                                       /* 0x13228 */
    volatile unsigned int reserved_172[5];                                              /* 0x1322c~0x1323c */
    volatile U_VPSS_RCH_BLKMT_BUF_CTRL VPSS_RCH_BLKMT_BUF_CTRL;                         /* 0x13240 */
    volatile U_VPSS_RCH_BLKMT_BUF_IMGSIZE VPSS_RCH_BLKMT_BUF_IMGSIZE;                   /* 0x13244 */
    volatile U_VPSS_RCH_BLKMT_BUF_STRIDE VPSS_RCH_BLKMT_BUF_STRIDE;                     /* 0x13248 */
    volatile unsigned int VPSS_RCH_BLKMT_BUF_START_ADDR;                                /* 0x1324c */
    volatile unsigned int VPSS_RCH_BLKMT_BUF_END_ADDR;                                  /* 0x13250 */
    volatile unsigned int VPSS_RCH_BLKMTREF_ADDR;                                       /* 0x13254 */
    volatile unsigned int VPSS_RCH_BLKMTREF_RADDR;                                      /* 0x13258 */
    volatile unsigned int VPSS_WCH_BLKMTCUR_ADDR;                                       /* 0x1325c */
    volatile unsigned int VPSS_WCH_BLKMTCUR_WADDR;                                      /* 0x13260 */
    volatile unsigned int reserved_173[7];                                              /* 0x13264~0x1327c */
    volatile U_VPSS_RCH_BLKMV_BUF_CTRL VPSS_RCH_BLKMV_BUF_CTRL;                         /* 0x13280 */
    volatile U_VPSS_RCH_BLKMV_BUF_IMGSIZE VPSS_RCH_BLKMV_BUF_IMGSIZE;                   /* 0x13284 */
    volatile U_VPSS_RCH_BLKMV_BUF_STRIDE VPSS_RCH_BLKMV_BUF_STRIDE;                     /* 0x13288 */
    volatile unsigned int VPSS_RCH_BLKMV_BUF_START_ADDR;                                /* 0x1328c */
    volatile unsigned int VPSS_RCH_BLKMV_BUF_END_ADDR;                                  /* 0x13290 */
    volatile unsigned int VPSS_RCH_BLKMVREF_ADDR;                                       /* 0x13294 */
    volatile unsigned int VPSS_RCH_BLKMVREF_RADDR;                                      /* 0x13298 */
    volatile unsigned int VPSS_RCH_BLKMVCUR_ADDR;                                       /* 0x1329c */
    volatile unsigned int VPSS_RCH_BLKMVCUR_RADDR;                                      /* 0x132a0 */
    volatile unsigned int VPSS_WCH_BLKMVNX1_ADDR;                                       /* 0x132a4 */
    volatile unsigned int VPSS_WCH_BLKMVNX1_WADDR;                                      /* 0x132a8 */
    volatile unsigned int reserved_174[5];                                              /* 0x132ac~0x132bc */
    volatile U_VPSS_RCH_CNT_BUF_CTRL VPSS_RCH_CNT_BUF_CTRL;                             /* 0x132c0 */
    volatile U_VPSS_RCH_CNT_BUF_IMGSIZE VPSS_RCH_CNT_BUF_IMGSIZE;                       /* 0x132c4 */
    volatile U_VPSS_RCH_CNT_BUF_STRIDE VPSS_RCH_CNT_BUF_STRIDE;                         /* 0x132c8 */
    volatile unsigned int VPSS_RCH_CNT_BUF_START_ADDR;                                  /* 0x132cc */
    volatile unsigned int VPSS_RCH_CNT_BUF_END_ADDR;                                    /* 0x132d0 */
    volatile unsigned int VPSS_RCH_CNT_ADDR;                                            /* 0x132d4 */
    volatile unsigned int VPSS_RCH_CNT_RADDR;                                           /* 0x132d8 */
    volatile unsigned int VPSS_WCH_CNT_ADDR;                                            /* 0x132dc */
    volatile unsigned int VPSS_WCH_CNT_WADDR;                                           /* 0x132e0 */
    volatile unsigned int reserved_175[7];                                              /* 0x132e4~0x132fc */
    volatile unsigned int VPSS_WCH_STT_ADDR;                                            /* 0x13300 */
    volatile unsigned int reserved_176[15];                                             /* 0x13304~0x1333c */
    volatile unsigned int VPSS_CHK_SUM_REF_Y;                                           /* 0x13340 */
    volatile unsigned int VPSS_CHK_SUM_REF_C;                                           /* 0x13344 */
    volatile unsigned int VPSS_CHK_SUM_CUR_Y;                                           /* 0x13348 */
    volatile unsigned int VPSS_CHK_SUM_CUR_C;                                           /* 0x1334c */
    volatile unsigned int VPSS_CHK_SUM_NX1_Y;                                           /* 0x13350 */
    volatile unsigned int VPSS_CHK_SUM_NX1_C;                                           /* 0x13354 */
    volatile unsigned int VPSS_CHK_SUM_REE_Y;                                           /* 0x13358 */
    volatile unsigned int VPSS_CHK_SUM_REE_C;                                           /* 0x1335c */
    volatile unsigned int VPSS_CHK_SUM_RFR_Y;                                           /* 0x13360 */
    volatile unsigned int VPSS_CHK_SUM_RFR_C;                                           /* 0x13364 */
    volatile unsigned int VPSS_CHK_SUM_CUE_Y;                                           /* 0x13368 */
    volatile unsigned int VPSS_CHK_SUM_CUE_C;                                           /* 0x1336c */
    volatile unsigned int VPSS_CHK_SUM_RST;                                             /* 0x13370 */
    volatile unsigned int VPSS_CHK_SUM_WST;                                             /* 0x13374 */
    volatile unsigned int VPSS_CHK_SUM_TRMD;                                            /* 0x13378 */
    volatile unsigned int VPSS_CHK_SUM_SRMD;                                            /* 0x1337c */
    volatile unsigned int VPSS_CHK_SUM_TWMD;                                            /* 0x13380 */
    volatile unsigned int VPSS_CHK_SUM_PRJHCUR;                                         /* 0x13384 */
    volatile unsigned int VPSS_CHK_SUM_PRJHNX2;                                         /* 0x13388 */
    volatile unsigned int VPSS_CHK_SUM_PRJVCUR;                                         /* 0x1338c */
    volatile unsigned int VPSS_CHK_SUM_PRJVNX2;                                         /* 0x13390 */
    volatile unsigned int VPSS_CHK_SUM_RGMVCUR;                                         /* 0x13394 */
    volatile unsigned int VPSS_CHK_SUM_RGMVNX1;                                         /* 0x13398 */
    volatile unsigned int VPSS_CHK_SUM_RGMVNX2;                                         /* 0x1339c */
    volatile unsigned int VPSS_CHK_SUM_BLKMVREF;                                        /* 0x133a0 */
    volatile unsigned int VPSS_CHK_SUM_BLKMVCUR;                                        /* 0x133a4 */
    volatile unsigned int VPSS_CHK_SUM_BLKMVNX1;                                        /* 0x133a8 */
    volatile unsigned int VPSS_CHK_SUM_BLKMTREF;                                        /* 0x133ac */
    volatile unsigned int VPSS_CHK_SUM_BLKMTCUR;                                        /* 0x133b0 */
    volatile unsigned int VPSS_CHK_SUM_CCCLRCNT;                                        /* 0x133b4 */
    volatile unsigned int VPSS_CHK_SUM_CCCLWCNT;                                        /* 0x133b8 */
    volatile unsigned int reserved_177[17];                                             /* 0x133bc~0x133fc */
    volatile U_VPSS_RFR_Y_GLB_INFO VPSS_RFR_Y_GLB_INFO;                                 /* 0x13400 */
    volatile U_VPSS_RFR_Y_FRAME_SIZE VPSS_RFR_Y_FRAME_SIZE;                             /* 0x13404 */
    volatile U_VPSS_RFR_Y_RC_CFG0 VPSS_RFR_Y_RC_CFG0;                                   /* 0x13408 */
    volatile U_VPSS_RFR_Y_RC_CFG1 VPSS_RFR_Y_RC_CFG1;                                   /* 0x1340c */
    volatile U_VPSS_RFR_Y_RC_CFG2 VPSS_RFR_Y_RC_CFG2;                                   /* 0x13410 */
    volatile U_VPSS_RFR_Y_RC_CFG3 VPSS_RFR_Y_RC_CFG3;                                   /* 0x13414 */
    volatile U_VPSS_RFR_Y_RC_CFG4 VPSS_RFR_Y_RC_CFG4;                                   /* 0x13418 */
    volatile U_VPSS_RFR_Y_RC_CFG5 VPSS_RFR_Y_RC_CFG5;                                   /* 0x1341c */
    volatile U_VPSS_RFR_Y_RC_CFG6 VPSS_RFR_Y_RC_CFG6;                                   /* 0x13420 */
    volatile U_VPSS_RFR_Y_RC_CFG7 VPSS_RFR_Y_RC_CFG7;                                   /* 0x13424 */
    volatile U_VPSS_RFR_Y_RC_CFG8 VPSS_RFR_Y_RC_CFG8;                                   /* 0x13428 */
    volatile U_VPSS_RFR_Y_RC_CFG9 VPSS_RFR_Y_RC_CFG9;                                   /* 0x1342c */
    volatile U_VPSS_RFR_Y_STAT_THR VPSS_RFR_Y_STAT_THR;                                 /* 0x13430 */
    volatile U_VPSS_RFR_Y_PCMP VPSS_RFR_Y_PCMP;                                         /* 0x13434 */
    volatile unsigned int reserved_178[2];                                              /* 0x13438~0x1343c */
    volatile U_VPSS_RFR_Y_BS_SIZE VPSS_RFR_Y_BS_SIZE;                                   /* 0x13440 */
    volatile unsigned int VPSS_RFR_Y_DEBUG;                                             /* 0x13444 */
    volatile U_VPSS_RFR_Y_WORST_ROW VPSS_RFR_Y_WORST_ROW;                               /* 0x13448 */
    volatile U_VPSS_RFR_Y_BEST_ROW VPSS_RFR_Y_BEST_ROW;                                 /* 0x1344c */
    volatile U_VPSS_RFR_Y_STAT_INFO VPSS_RFR_Y_STAT_INFO;                               /* 0x13450 */
    volatile unsigned int reserved_179[11];                                             /* 0x13454~0x1347c */
    volatile U_VPSS_RFR_C_GLB_INFO VPSS_RFR_C_GLB_INFO;                                 /* 0x13480 */
    volatile U_VPSS_RFR_C_FRAME_SIZE VPSS_RFR_C_FRAME_SIZE;                             /* 0x13484 */
    volatile U_VPSS_RFR_C_RC_CFG0 VPSS_RFR_C_RC_CFG0;                                   /* 0x13488 */
    volatile U_VPSS_RFR_C_RC_CFG1 VPSS_RFR_C_RC_CFG1;                                   /* 0x1348c */
    volatile U_VPSS_RFR_C_RC_CFG2 VPSS_RFR_C_RC_CFG2;                                   /* 0x13490 */
    volatile U_VPSS_RFR_C_RC_CFG3 VPSS_RFR_C_RC_CFG3;                                   /* 0x13494 */
    volatile U_VPSS_RFR_C_RC_CFG4 VPSS_RFR_C_RC_CFG4;                                   /* 0x13498 */
    volatile U_VPSS_RFR_C_RC_CFG5 VPSS_RFR_C_RC_CFG5;                                   /* 0x1349c */
    volatile U_VPSS_RFR_C_RC_CFG6 VPSS_RFR_C_RC_CFG6;                                   /* 0x134a0 */
    volatile U_VPSS_RFR_C_RC_CFG7 VPSS_RFR_C_RC_CFG7;                                   /* 0x134a4 */
    volatile U_VPSS_RFR_C_RC_CFG8 VPSS_RFR_C_RC_CFG8;                                   /* 0x134a8 */
    volatile U_VPSS_RFR_C_RC_CFG9 VPSS_RFR_C_RC_CFG9;                                   /* 0x134ac */
    volatile U_VPSS_RFR_C_STAT_THR VPSS_RFR_C_STAT_THR;                                 /* 0x134b0 */
    volatile U_VPSS_RFR_C_PCMP VPSS_RFR_C_PCMP;                                         /* 0x134b4 */
    volatile unsigned int reserved_180[2];                                              /* 0x134b8~0x134bc */
    volatile U_VPSS_RFR_C_BS_SIZE VPSS_RFR_C_BS_SIZE;                                   /* 0x134c0 */
    volatile unsigned int VPSS_RFR_C_DEBUG;                                             /* 0x134c4 */
    volatile U_VPSS_RFR_C_WORST_ROW VPSS_RFR_C_WORST_ROW;                               /* 0x134c8 */
    volatile U_VPSS_RFR_C_BEST_ROW VPSS_RFR_C_BEST_ROW;                                 /* 0x134cc */
    volatile U_VPSS_RFR_C_STAT_INFO VPSS_RFR_C_STAT_INFO;                               /* 0x134d0 */
    volatile unsigned int reserved_181[11];                                             /* 0x134d4~0x134fc */
    volatile U_VPSS_CUE_Y_GLB_INFO VPSS_CUE_Y_GLB_INFO;                                 /* 0x13500 */
    volatile U_VPSS_CUE_Y_FRAME_SIZE VPSS_CUE_Y_FRAME_SIZE;                             /* 0x13504 */
    volatile U_VPSS_CUE_Y_RC_CFG0 VPSS_CUE_Y_RC_CFG0;                                   /* 0x13508 */
    volatile U_VPSS_CUE_Y_RC_CFG1 VPSS_CUE_Y_RC_CFG1;                                   /* 0x1350c */
    volatile U_VPSS_CUE_Y_RC_CFG2 VPSS_CUE_Y_RC_CFG2;                                   /* 0x13510 */
    volatile U_VPSS_CUE_Y_RC_CFG3 VPSS_CUE_Y_RC_CFG3;                                   /* 0x13514 */
    volatile U_VPSS_CUE_Y_RC_CFG4 VPSS_CUE_Y_RC_CFG4;                                   /* 0x13518 */
    volatile U_VPSS_CUE_Y_RC_CFG5 VPSS_CUE_Y_RC_CFG5;                                   /* 0x1351c */
    volatile U_VPSS_CUE_Y_RC_CFG6 VPSS_CUE_Y_RC_CFG6;                                   /* 0x13520 */
    volatile U_VPSS_CUE_Y_RC_CFG7 VPSS_CUE_Y_RC_CFG7;                                   /* 0x13524 */
    volatile U_VPSS_CUE_Y_RC_CFG8 VPSS_CUE_Y_RC_CFG8;                                   /* 0x13528 */
    volatile U_VPSS_CUE_Y_RC_CFG9 VPSS_CUE_Y_RC_CFG9;                                   /* 0x1352c */
    volatile U_VPSS_CUE_Y_STAT_THR VPSS_CUE_Y_STAT_THR;                                 /* 0x13530 */
    volatile U_VPSS_CUE_Y_PCMP VPSS_CUE_Y_PCMP;                                         /* 0x13534 */
    volatile unsigned int reserved_182[2];                                              /* 0x13538~0x1353c */
    volatile U_VPSS_CUE_Y_BS_SIZE VPSS_CUE_Y_BS_SIZE;                                   /* 0x13540 */
    volatile unsigned int VPSS_CUE_Y_DEBUG;                                             /* 0x13544 */
    volatile U_VPSS_CUE_Y_WORST_ROW VPSS_CUE_Y_WORST_ROW;                               /* 0x13548 */
    volatile U_VPSS_CUE_Y_BEST_ROW VPSS_CUE_Y_BEST_ROW;                                 /* 0x1354c */
    volatile U_VPSS_CUE_Y_STAT_INFO VPSS_CUE_Y_STAT_INFO;                               /* 0x13550 */
    volatile unsigned int reserved_183[11];                                             /* 0x13554~0x1357c */
    volatile U_VPSS_CUE_C_GLB_INFO VPSS_CUE_C_GLB_INFO;                                 /* 0x13580 */
    volatile U_VPSS_CUE_C_FRAME_SIZE VPSS_CUE_C_FRAME_SIZE;                             /* 0x13584 */
    volatile U_VPSS_CUE_C_RC_CFG0 VPSS_CUE_C_RC_CFG0;                                   /* 0x13588 */
    volatile U_VPSS_CUE_C_RC_CFG1 VPSS_CUE_C_RC_CFG1;                                   /* 0x1358c */
    volatile U_VPSS_CUE_C_RC_CFG2 VPSS_CUE_C_RC_CFG2;                                   /* 0x13590 */
    volatile U_VPSS_CUE_C_RC_CFG3 VPSS_CUE_C_RC_CFG3;                                   /* 0x13594 */
    volatile U_VPSS_CUE_C_RC_CFG4 VPSS_CUE_C_RC_CFG4;                                   /* 0x13598 */
    volatile U_VPSS_CUE_C_RC_CFG5 VPSS_CUE_C_RC_CFG5;                                   /* 0x1359c */
    volatile U_VPSS_CUE_C_RC_CFG6 VPSS_CUE_C_RC_CFG6;                                   /* 0x135a0 */
    volatile U_VPSS_CUE_C_RC_CFG7 VPSS_CUE_C_RC_CFG7;                                   /* 0x135a4 */
    volatile U_VPSS_CUE_C_RC_CFG8 VPSS_CUE_C_RC_CFG8;                                   /* 0x135a8 */
    volatile U_VPSS_CUE_C_RC_CFG9 VPSS_CUE_C_RC_CFG9;                                   /* 0x135ac */
    volatile U_VPSS_CUE_C_STAT_THR VPSS_CUE_C_STAT_THR;                                 /* 0x135b0 */
    volatile U_VPSS_CUE_C_PCMP VPSS_CUE_C_PCMP;                                         /* 0x135b4 */
    volatile unsigned int reserved_184[2];                                              /* 0x135b8~0x135bc */
    volatile U_VPSS_CUE_C_BS_SIZE VPSS_CUE_C_BS_SIZE;                                   /* 0x135c0 */
    volatile unsigned int VPSS_CUE_C_DEBUG;                                             /* 0x135c4 */
    volatile U_VPSS_CUE_C_WORST_ROW VPSS_CUE_C_WORST_ROW;                               /* 0x135c8 */
    volatile U_VPSS_CUE_C_BEST_ROW VPSS_CUE_C_BEST_ROW;                                 /* 0x135cc */
    volatile U_VPSS_CUE_C_STAT_INFO VPSS_CUE_C_STAT_INFO;                               /* 0x135d0 */
} S_VDP_REGS_TYPE;

/* define the union U_HIPPCTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 28;   /* [27..0]  */
        unsigned int int_test_mode : 1; /* [28]  */
        unsigned int int_test : 1;      /* [29]  */
        unsigned int chk_sum_en : 1;    /* [30]  */
        unsigned int vo_ck_gt_en : 1;   /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIPPCTRL;

/* define the union U_HIHDR_V_YUV2RGB_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_en : 1;       /* [0]  */
        unsigned int hihdr_y2r_ck_gt_en : 1; /* [1]  */
        unsigned int hihdr_v0_cl_en : 1;     /* [2]  */
        unsigned int hihdr_v1_cl_en : 1;     /* [3]  */
        unsigned int hihdr_v0_y2r_en : 1;    /* [4]  */
        unsigned int hihdr_v1_y2r_en : 1;    /* [5]  */
        unsigned int hihdr_v0_vhdr_en : 1;   /* [6]  */
        unsigned int hihdr_v1_vhdr_en : 1;   /* [7]  */
        unsigned int reserved_0 : 4;         /* [11..8]  */
        unsigned int hihdr_v_demo_en : 1;    /* [12]  */
        unsigned int hihdr_v_demo_mode : 1;  /* [13]  */
        unsigned int reserved_1 : 2;         /* [15..14]  */
        unsigned int hihdr_v_demo_pos : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_CTRL;

/* define the union U_HIHDR_V_YUV2RGB_COEF00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF00;

/* define the union U_HIHDR_V_YUV2RGB_COEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF01;

/* define the union U_HIHDR_V_YUV2RGB_COEF02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF02;

/* define the union U_HIHDR_V_YUV2RGB_COEF03 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef03 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF03;

/* define the union U_HIHDR_V_YUV2RGB_COEF04 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef04 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF04;

/* define the union U_HIHDR_V_YUV2RGB_COEF05 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef05 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF05;

/* define the union U_HIHDR_V_YUV2RGB_COEF06 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef06 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF06;

/* define the union U_HIHDR_V_YUV2RGB_COEF07 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef07 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF07;

/* define the union U_HIHDR_V_YUV2RGB_COEF08 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef08 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF08;

/* define the union U_HIHDR_V_YUV2RGB_COEF10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF10;

/* define the union U_HIHDR_V_YUV2RGB_COEF11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF11;

/* define the union U_HIHDR_V_YUV2RGB_COEF12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF12;

/* define the union U_HIHDR_V_YUV2RGB_COEF13 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef13 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF13;

/* define the union U_HIHDR_V_YUV2RGB_COEF14 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef14 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF14;

/* define the union U_HIHDR_V_YUV2RGB_COEF15 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef15 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF15;

/* define the union U_HIHDR_V_YUV2RGB_COEF16 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef16 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF16;

/* define the union U_HIHDR_V_YUV2RGB_COEF17 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef17 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF17;

/* define the union U_HIHDR_V_YUV2RGB_COEF18 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef18 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_COEF18;

/* define the union U_HIHDR_V_YUV2RGB_SCALE2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_v0_scale2p : 4; /* [3..0]  */
        unsigned int hihdr_y2r_v1_scale2p : 4; /* [7..4]  */
        unsigned int reserved_0 : 24;          /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_SCALE2P;

/* define the union U_HIHDR_V_YUV2RGB_IN_DC00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc00 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_IN_DC00;

/* define the union U_HIHDR_V_YUV2RGB_IN_DC01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc01 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_IN_DC01;

/* define the union U_HIHDR_V_YUV2RGB_IN_DC02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc02 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_IN_DC02;

/* define the union U_HIHDR_V_YUV2RGB_OUT_DC00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc00 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_OUT_DC00;

/* define the union U_HIHDR_V_YUV2RGB_OUT_DC01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc01 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_OUT_DC01;

/* define the union U_HIHDR_V_YUV2RGB_OUT_DC02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc02 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_OUT_DC02;

/* define the union U_HIHDR_V_YUV2RGB_IN_DC10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc10 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_IN_DC10;

/* define the union U_HIHDR_V_YUV2RGB_IN_DC11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc11 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_IN_DC11;

/* define the union U_HIHDR_V_YUV2RGB_IN_DC12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc12 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_IN_DC12;

/* define the union U_HIHDR_V_YUV2RGB_OUT_DC10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc10 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_OUT_DC10;

/* define the union U_HIHDR_V_YUV2RGB_OUT_DC11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc11 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_OUT_DC11;

/* define the union U_HIHDR_V_YUV2RGB_OUT_DC12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc12 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_OUT_DC12;

/* define the union U_HIHDR_V_YUV2RGB_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_v0_clip_min : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;             /* [15..12]  */
        unsigned int hihdr_y2r_v1_clip_min : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;             /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_MIN;

/* define the union U_HIHDR_V_YUV2RGB_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_v0_clip_max : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;             /* [15..12]  */
        unsigned int hihdr_y2r_v1_clip_max : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;             /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_V_YUV2RGB_MAX;

/* define the union U_VHDR_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_en : 1;         /* [0]  */
        unsigned int vhdr_gamut_bind : 1; /* [1]  */
        unsigned int vhdr_ck_gt_en : 1;   /* [2]  */
        unsigned int reserved_0 : 29;     /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_CTRL;

/* define the union U_VHDR_DEGAMMA_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_degmm_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_CTRL;

/* define the union U_VHDR_DEGAMMA_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_degamma_rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;        /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_REN;

/* define the union U_VHDR_DEGAMMA_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x1_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;      /* [7..4]  */
        unsigned int v_degmm_x2_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;      /* [15..12]  */
        unsigned int v_degmm_x3_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;      /* [23..20]  */
        unsigned int v_degmm_x4_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_STEP1;

/* define the union U_VHDR_DEGAMMA_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x5_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;      /* [7..4]  */
        unsigned int v_degmm_x6_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;      /* [15..12]  */
        unsigned int v_degmm_x7_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;      /* [23..20]  */
        unsigned int v_degmm_x8_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_STEP2;

/* define the union U_VHDR_DEGAMMA_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x1_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x2_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_POS1;

/* define the union U_VHDR_DEGAMMA_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x3_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x4_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_POS2;

/* define the union U_VHDR_DEGAMMA_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x5_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x6_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_POS3;

/* define the union U_VHDR_DEGAMMA_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x7_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x8_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_POS4;

/* define the union U_VHDR_DEGAMMA_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;     /* [7..6]  */
        unsigned int v_degmm_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;     /* [15..14]  */
        unsigned int v_degmm_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;     /* [23..22]  */
        unsigned int v_degmm_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;     /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_NUM1;

/* define the union U_VHDR_DEGAMMA_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;     /* [7..6]  */
        unsigned int v_degmm_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;     /* [15..14]  */
        unsigned int v_degmm_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;     /* [23..22]  */
        unsigned int v_degmm_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;     /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DEGAMMA_NUM2;

/* define the union U_VHDR_GAMUT_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_CTRL;

/* define the union U_VHDR_GAMUT_COEF00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF00;

/* define the union U_VHDR_GAMUT_COEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF01;

/* define the union U_VHDR_GAMUT_COEF02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF02;

/* define the union U_VHDR_GAMUT_COEF10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF10;

/* define the union U_VHDR_GAMUT_COEF11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF11;

/* define the union U_VHDR_GAMUT_COEF12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF12;

/* define the union U_VHDR_GAMUT_COEF20 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF20;

/* define the union U_VHDR_GAMUT_COEF21 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF21;

/* define the union U_VHDR_GAMUT_COEF22 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_COEF22;

/* define the union U_VHDR_GAMUT_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;      /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_SCALE;

/* define the union U_VHDR_GAMUT_IDC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_idc0 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_IDC0;

/* define the union U_VHDR_GAMUT_IDC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_idc1 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_IDC1;

/* define the union U_VHDR_GAMUT_IDC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_idc2 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_IDC2;

/* define the union U_VHDR_GAMUT_ODC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_odc0 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_ODC0;

/* define the union U_VHDR_GAMUT_ODC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_odc1 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_ODC1;

/* define the union U_VHDR_GAMUT_ODC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_odc2 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_ODC2;

/* define the union U_VHDR_GAMUT_CLIP_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_clip_min : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;          /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_CLIP_MIN;

/* define the union U_VHDR_GAMUT_CLIP_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_clip_max : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;          /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMUT_CLIP_MAX;

/* define the union U_VHDR_TONEMAP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;  /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_CTRL;

/* define the union U_VHDR_TONEMAP_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_rd_en : 1; /* [0]  */
        unsigned int vhdr_sm_rd_en : 1;   /* [1]  */
        unsigned int reserved_0 : 30;     /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_REN;

/* define the union U_VHDR_TONEMAP_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x1_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_tmap_x2_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_tmap_x3_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_tmap_x4_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_STEP1;

/* define the union U_VHDR_TONEMAP_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x5_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_tmap_x6_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_tmap_x7_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_tmap_x8_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_STEP2;

/* define the union U_VHDR_TONEMAP_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x1_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS1;

/* define the union U_VHDR_TONEMAP_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x2_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS2;

/* define the union U_VHDR_TONEMAP_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x3_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS3;

/* define the union U_VHDR_TONEMAP_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x4_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS4;

/* define the union U_VHDR_TONEMAP_POS5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x5_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS5;

/* define the union U_VHDR_TONEMAP_POS6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x6_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS6;

/* define the union U_VHDR_TONEMAP_POS7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x7_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS7;

/* define the union U_VHDR_TONEMAP_POS8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x8_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_POS8;

/* define the union U_VHDR_TONEMAP_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_tmap_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_tmap_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_tmap_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_NUM1;

/* define the union U_VHDR_TONEMAP_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_tmap_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_tmap_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_tmap_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_NUM2;

/* define the union U_VHDR_TONEMAP_SM_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x1_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_smap_x2_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_smap_x3_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_smap_x4_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_STEP1;

/* define the union U_VHDR_TONEMAP_SM_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x5_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_smap_x6_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_smap_x7_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_smap_x8_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_STEP2;

/* define the union U_VHDR_TONEMAP_SM_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x1_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS1;

/* define the union U_VHDR_TONEMAP_SM_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x2_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS2;

/* define the union U_VHDR_TONEMAP_SM_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x3_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS3;

/* define the union U_VHDR_TONEMAP_SM_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x4_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS4;

/* define the union U_VHDR_TONEMAP_SM_POS5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x5_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS5;

/* define the union U_VHDR_TONEMAP_SM_POS6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x6_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS6;

/* define the union U_VHDR_TONEMAP_SM_POS7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x7_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS7;

/* define the union U_VHDR_TONEMAP_SM_POS8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x8_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_POS8;

/* define the union U_VHDR_TONEMAP_SM_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_smap_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_smap_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_smap_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_NUM1;

/* define the union U_VHDR_TONEMAP_SM_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_smap_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_smap_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_smap_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_SM_NUM2;

/* define the union U_VHDR_TONEMAP_LUMA_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_coef0 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_LUMA_COEF0;

/* define the union U_VHDR_TONEMAP_LUMA_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_coef1 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_LUMA_COEF1;

/* define the union U_VHDR_TONEMAP_LUMA_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_coef2 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_LUMA_COEF2;

/* define the union U_VHDR_TONEMAP_LUMA_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;          /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_LUMA_SCALE;

/* define the union U_VHDR_TONEMAP_COEF_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_coef_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;          /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_COEF_SCALE;

/* define the union U_VHDR_TONEMAP_OUT_CLIP_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_clip_min : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;             /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_OUT_CLIP_MIN;

/* define the union U_VHDR_TONEMAP_OUT_CLIP_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_clip_max : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;             /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_OUT_CLIP_MAX;

/* define the union U_VHDR_TONEMAP_OUT_DC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_dc0 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;        /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_OUT_DC0;

/* define the union U_VHDR_TONEMAP_OUT_DC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_dc1 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;        /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_OUT_DC1;

/* define the union U_VHDR_TONEMAP_OUT_DC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_dc2 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;        /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_TONEMAP_OUT_DC2;

/* define the union U_VHDR_GAMMA_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gmm_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_CTRL;

/* define the union U_VHDR_GAMMA_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamma_rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;      /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_REN;

/* define the union U_VHDR_GAMMA_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x1_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;    /* [7..5]  */
        unsigned int v_gmm_x2_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;    /* [15..13]  */
        unsigned int v_gmm_x3_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;    /* [23..21]  */
        unsigned int v_gmm_x4_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_STEP1;

/* define the union U_VHDR_GAMMA_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x5_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;    /* [7..5]  */
        unsigned int v_gmm_x6_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;    /* [15..13]  */
        unsigned int v_gmm_x7_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;    /* [23..21]  */
        unsigned int v_gmm_x8_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_STEP2;

/* define the union U_VHDR_GAMMA_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x1_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS1;

/* define the union U_VHDR_GAMMA_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x2_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS2;

/* define the union U_VHDR_GAMMA_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x3_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS3;

/* define the union U_VHDR_GAMMA_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x4_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS4;

/* define the union U_VHDR_GAMMA_POS5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x5_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS5;

/* define the union U_VHDR_GAMMA_POS6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x6_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS6;

/* define the union U_VHDR_GAMMA_POS7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x7_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS7;

/* define the union U_VHDR_GAMMA_POS8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x8_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_POS8;

/* define the union U_VHDR_GAMMA_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int v_gmm_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;   /* [15..14]  */
        unsigned int v_gmm_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;   /* [23..22]  */
        unsigned int v_gmm_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_NUM1;

/* define the union U_VHDR_GAMMA_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int v_gmm_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;   /* [15..14]  */
        unsigned int v_gmm_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;   /* [23..22]  */
        unsigned int v_gmm_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_GAMMA_NUM2;

/* define the union U_VHDR_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_tap_mode : 2;    /* [1..0]  */
        unsigned int vhdr_dither_domain_mode : 1; /* [2]  */
        unsigned int vhdr_dither_round : 1;       /* [3]  */
        unsigned int vhdr_dither_mode : 1;        /* [4]  */
        unsigned int vhdr_dither_en : 1;          /* [5]  */
        unsigned int vhdr_dither_round_unlim : 1; /* [6]  */
        unsigned int reserved_0 : 25;             /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_CTRL;

/* define the union U_VHDR_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_thr_min : 16; /* [15..0]  */
        unsigned int vhdr_dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_THR;

/* define the union U_VHDR_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_Y0;

/* define the union U_VHDR_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_U0;

/* define the union U_VHDR_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_V0;

/* define the union U_VHDR_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_W0;

/* define the union U_VHDR_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_Y1;

/* define the union U_VHDR_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_U1;

/* define the union U_VHDR_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_V1;

/* define the union U_VHDR_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_DITHER_SED_W1;

/* define the union U_VHDR_RGB2YUV_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_en : 1;  /* [0]  */
        unsigned int vhdr_cadj_en : 1; /* [1]  */
        unsigned int reserved_0 : 30;  /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_CTRL;

/* define the union U_VHDR_RGB2YUV_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF0;

/* define the union U_VHDR_RGB2YUV_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF1;

/* define the union U_VHDR_RGB2YUV_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF2;

/* define the union U_VHDR_RGB2YUV_COEF3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF3;

/* define the union U_VHDR_RGB2YUV_COEF4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF4;

/* define the union U_VHDR_RGB2YUV_COEF5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF5;

/* define the union U_VHDR_RGB2YUV_COEF6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF6;

/* define the union U_VHDR_RGB2YUV_COEF7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF7;

/* define the union U_VHDR_RGB2YUV_COEF8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_COEF8;

/* define the union U_VHDR_RGB2YUV_SCALE2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_scale2p : 4;  /* [3..0]  */
        unsigned int vhdr_cadj_scale2p : 4; /* [7..4]  */
        unsigned int reserved_0 : 24;       /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_SCALE2P;

/* define the union U_VHDR_RGB2YUV_IDC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_idc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_IDC0;

/* define the union U_VHDR_RGB2YUV_IDC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_idc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_IDC1;

/* define the union U_VHDR_RGB2YUV_IDC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_idc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_IDC2;

/* define the union U_VHDR_RGB2YUV_ODC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_odc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_ODC0;

/* define the union U_VHDR_RGB2YUV_ODC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_odc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_ODC1;

/* define the union U_VHDR_RGB2YUV_ODC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_odc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_ODC2;

/* define the union U_VHDR_RGB2YUV_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_clip_y_min : 10; /* [9..0]  */
        unsigned int vhdr_r2y_clip_c_min : 10; /* [19..10]  */
        unsigned int reserved_0 : 12;          /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_MIN;

/* define the union U_VHDR_RGB2YUV_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_clip_y_max : 10; /* [9..0]  */
        unsigned int vhdr_r2y_clip_c_max : 10; /* [19..10]  */
        unsigned int reserved_0 : 12;          /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VHDR_RGB2YUV_MAX;

/* define the union U_GHDR_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_en : 1;        /* [0]  */
        unsigned int ghdr_ck_gt_en : 1;  /* [1]  */
        unsigned int reserved_0 : 10;    /* [11..2]  */
        unsigned int ghdr_demo_en : 1;   /* [12]  */
        unsigned int ghdr_demo_mode : 1; /* [13]  */
        unsigned int reserved_1 : 2;     /* [15..14]  */
        unsigned int ghdr_demo_pos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_CTRL;

/* define the union U_GHDR_DEGAMMA_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_degmm_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DEGAMMA_CTRL;

/* define the union U_GHDR_DEGAMMA_STEP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_degmm_x1_step : 4; /* [3..0]  */
        unsigned int g_degmm_x2_step : 4; /* [7..4]  */
        unsigned int g_degmm_x3_step : 4; /* [11..8]  */
        unsigned int g_degmm_x4_step : 4; /* [15..12]  */
        unsigned int reserved_0 : 16;     /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DEGAMMA_STEP;

/* define the union U_GHDR_DEGAMMA_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_degmm_x1_pos : 10; /* [9..0]  */
        unsigned int g_degmm_x2_pos : 10; /* [19..10]  */
        unsigned int reserved_0 : 12;     /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DEGAMMA_POS1;

/* define the union U_GHDR_DEGAMMA_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_degmm_x3_pos : 10; /* [9..0]  */
        unsigned int g_degmm_x4_pos : 10; /* [19..10]  */
        unsigned int reserved_0 : 12;     /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DEGAMMA_POS2;

/* define the union U_GHDR_DEGAMMA_NUM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_degmm_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;     /* [7..6]  */
        unsigned int g_degmm_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;     /* [15..14]  */
        unsigned int g_degmm_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;     /* [23..22]  */
        unsigned int g_degmm_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;     /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DEGAMMA_NUM;

/* define the union U_GHDR_GAMUT_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_CTRL;

/* define the union U_GHDR_GAMUT_COEF00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF00;

/* define the union U_GHDR_GAMUT_COEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF01;

/* define the union U_GHDR_GAMUT_COEF02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF02;

/* define the union U_GHDR_GAMUT_COEF10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF10;

/* define the union U_GHDR_GAMUT_COEF11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF11;

/* define the union U_GHDR_GAMUT_COEF12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF12;

/* define the union U_GHDR_GAMUT_COEF20 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF20;

/* define the union U_GHDR_GAMUT_COEF21 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF21;

/* define the union U_GHDR_GAMUT_COEF22 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_COEF22;

/* define the union U_GHDR_GAMUT_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;      /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_SCALE;

/* define the union U_GHDR_GAMUT_CLIP_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_clip_min : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;          /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_CLIP_MIN;

/* define the union U_GHDR_GAMUT_CLIP_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamut_clip_max : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;          /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMUT_CLIP_MAX;

/* define the union U_GHDR_TONEMAP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;  /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_CTRL;

/* define the union U_GHDR_TONEMAP_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;     /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_REN;

/* define the union U_GHDR_TONEMAP_STEP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_tmap_x1_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;     /* [7..4]  */
        unsigned int g_tmap_x2_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;     /* [15..12]  */
        unsigned int g_tmap_x3_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;     /* [23..20]  */
        unsigned int g_tmap_x4_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;     /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_STEP;

/* define the union U_GHDR_TONEMAP_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_tmap_x1_pos : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;    /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_POS1;

/* define the union U_GHDR_TONEMAP_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_tmap_x2_pos : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;    /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_POS2;

/* define the union U_GHDR_TONEMAP_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_tmap_x3_pos : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;    /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_POS3;

/* define the union U_GHDR_TONEMAP_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_tmap_x4_pos : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;    /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_POS4;

/* define the union U_GHDR_TONEMAP_NUM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_tmap_x1_num : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;    /* [7..5]  */
        unsigned int g_tmap_x2_num : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;    /* [15..13]  */
        unsigned int g_tmap_x3_num : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;    /* [23..21]  */
        unsigned int g_tmap_x4_num : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_NUM;

/* define the union U_GHDR_TONEMAP_LUMA_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_luma_coef0 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_LUMA_COEF0;

/* define the union U_GHDR_TONEMAP_LUMA_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_luma_coef1 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_LUMA_COEF1;

/* define the union U_GHDR_TONEMAP_LUMA_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_luma_coef2 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_LUMA_COEF2;

/* define the union U_GHDR_TONEMAP_LUMA_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_luma_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;          /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_LUMA_SCALE;

/* define the union U_GHDR_TONEMAP_COEF_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_coef_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;          /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_COEF_SCALE;

/* define the union U_GHDR_TONEMAP_OUT_CLIP_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_out_clip_min : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;             /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_OUT_CLIP_MIN;

/* define the union U_GHDR_TONEMAP_OUT_CLIP_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_tmap_out_clip_max : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;             /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_TONEMAP_OUT_CLIP_MAX;

/* define the union U_GHDR_GAMMA_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gmm_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_CTRL;

/* define the union U_GHDR_GAMMA_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_gamma_rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;      /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_REN;

/* define the union U_GHDR_GAMMA_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x1_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;    /* [7..4]  */
        unsigned int g_gmm_x2_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;    /* [15..12]  */
        unsigned int g_gmm_x3_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;    /* [23..20]  */
        unsigned int g_gmm_x4_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_STEP1;

/* define the union U_GHDR_GAMMA_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x5_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;    /* [7..4]  */
        unsigned int g_gmm_x6_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;    /* [15..12]  */
        unsigned int g_gmm_x7_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;    /* [23..20]  */
        unsigned int g_gmm_x8_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;    /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_STEP2;

/* define the union U_GHDR_GAMMA_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x1_pos : 16; /* [15..0]  */
        unsigned int g_gmm_x2_pos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_POS1;

/* define the union U_GHDR_GAMMA_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x3_pos : 16; /* [15..0]  */
        unsigned int g_gmm_x4_pos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_POS2;

/* define the union U_GHDR_GAMMA_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x5_pos : 16; /* [15..0]  */
        unsigned int g_gmm_x6_pos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_POS3;

/* define the union U_GHDR_GAMMA_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x7_pos : 16; /* [15..0]  */
        unsigned int g_gmm_x8_pos : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_POS4;

/* define the union U_GHDR_GAMMA_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int g_gmm_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;   /* [15..14]  */
        unsigned int g_gmm_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;   /* [23..22]  */
        unsigned int g_gmm_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_NUM1;

/* define the union U_GHDR_GAMMA_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int g_gmm_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int g_gmm_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;   /* [15..14]  */
        unsigned int g_gmm_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;   /* [23..22]  */
        unsigned int g_gmm_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_GAMMA_NUM2;

/* define the union U_GHDR_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_tap_mode : 2;    /* [1..0]  */
        unsigned int ghdr_dither_domain_mode : 1; /* [2]  */
        unsigned int ghdr_dither_round : 1;       /* [3]  */
        unsigned int ghdr_dither_mode : 1;        /* [4]  */
        unsigned int ghdr_dither_en : 1;          /* [5]  */
        unsigned int ghdr_dither_round_unlim : 1; /* [6]  */
        unsigned int reserved_0 : 25;             /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_CTRL;

/* define the union U_GHDR_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_thr_min : 16; /* [15..0]  */
        unsigned int ghdr_dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_THR;

/* define the union U_GHDR_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_Y0;

/* define the union U_GHDR_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_U0;

/* define the union U_GHDR_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_V0;

/* define the union U_GHDR_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_W0;

/* define the union U_GHDR_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_Y1;

/* define the union U_GHDR_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_U1;

/* define the union U_GHDR_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_V1;

/* define the union U_GHDR_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ghdr_dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GHDR_DITHER_SED_W1;

/* define the union U_HIHDR_G_RGB2YUV_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;  /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_CTRL;

/* define the union U_HIHDR_G_RGB2YUV_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF0;

/* define the union U_HIHDR_G_RGB2YUV_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF1;

/* define the union U_HIHDR_G_RGB2YUV_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF2;

/* define the union U_HIHDR_G_RGB2YUV_COEF3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF3;

/* define the union U_HIHDR_G_RGB2YUV_COEF4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF4;

/* define the union U_HIHDR_G_RGB2YUV_COEF5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF5;

/* define the union U_HIHDR_G_RGB2YUV_COEF6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF6;

/* define the union U_HIHDR_G_RGB2YUV_COEF7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF7;

/* define the union U_HIHDR_G_RGB2YUV_COEF8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_COEF8;

/* define the union U_HIHDR_G_RGB2YUV_SCALE2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_scale2p : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_SCALE2P;

/* define the union U_HIHDR_G_RGB2YUV_IDC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_idc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;     /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_IDC0;

/* define the union U_HIHDR_G_RGB2YUV_IDC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_idc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;     /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_IDC1;

/* define the union U_HIHDR_G_RGB2YUV_IDC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_idc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;     /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_IDC2;

/* define the union U_HIHDR_G_RGB2YUV_ODC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_odc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;     /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_ODC0;

/* define the union U_HIHDR_G_RGB2YUV_ODC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_odc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;     /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_ODC1;

/* define the union U_HIHDR_G_RGB2YUV_ODC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_odc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;     /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_ODC2;

/* define the union U_HIHDR_G_RGB2YUV_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_clip_min : 10; /* [9..0]  */
        unsigned int reserved_0 : 22;         /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_MIN;

/* define the union U_HIHDR_G_RGB2YUV_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_r2y_clip_max : 10; /* [9..0]  */
        unsigned int reserved_0 : 22;         /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_G_RGB2YUV_MAX;

/* define the union U_HIHDR_WD_YUV2RGB_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_en : 1;       /* [0]  */
        unsigned int hihdr_y2r_ck_gt_en : 1; /* [1]  */
        unsigned int hihdr_v0_cl_en : 1;     /* [2]  */
        unsigned int hihdr_v1_cl_en : 1;     /* [3]  */
        unsigned int hihdr_v0_y2r_en : 1;    /* [4]  */
        unsigned int hihdr_v1_y2r_en : 1;    /* [5]  */
        unsigned int hihdr_v0_vhdr_en : 1;   /* [6]  */
        unsigned int hihdr_v1_vhdr_en : 1;   /* [7]  */
        unsigned int reserved_0 : 4;         /* [11..8]  */
        unsigned int hihdr_v_demo_en : 1;    /* [12]  */
        unsigned int hihdr_v_demo_mode : 1;  /* [13]  */
        unsigned int reserved_1 : 2;         /* [15..14]  */
        unsigned int hihdr_v_demo_pos : 16;  /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_CTRL;

/* define the union U_HIHDR_WD_YUV2RGB_COEF00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF00;

/* define the union U_HIHDR_WD_YUV2RGB_COEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF01;

/* define the union U_HIHDR_WD_YUV2RGB_COEF02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF02;

/* define the union U_HIHDR_WD_YUV2RGB_COEF03 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef03 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF03;

/* define the union U_HIHDR_WD_YUV2RGB_COEF04 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef04 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF04;

/* define the union U_HIHDR_WD_YUV2RGB_COEF05 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef05 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF05;

/* define the union U_HIHDR_WD_YUV2RGB_COEF06 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef06 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF06;

/* define the union U_HIHDR_WD_YUV2RGB_COEF07 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef07 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF07;

/* define the union U_HIHDR_WD_YUV2RGB_COEF08 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef08 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF08;

/* define the union U_HIHDR_WD_YUV2RGB_COEF10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF10;

/* define the union U_HIHDR_WD_YUV2RGB_COEF11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF11;

/* define the union U_HIHDR_WD_YUV2RGB_COEF12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF12;

/* define the union U_HIHDR_WD_YUV2RGB_COEF13 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef13 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF13;

/* define the union U_HIHDR_WD_YUV2RGB_COEF14 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef14 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF14;

/* define the union U_HIHDR_WD_YUV2RGB_COEF15 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef15 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF15;

/* define the union U_HIHDR_WD_YUV2RGB_COEF16 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef16 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF16;

/* define the union U_HIHDR_WD_YUV2RGB_COEF17 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef17 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF17;

/* define the union U_HIHDR_WD_YUV2RGB_COEF18 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_coef18 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;       /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_COEF18;

/* define the union U_HIHDR_WD_YUV2RGB_SCALE2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_v0_scale2p : 4; /* [3..0]  */
        unsigned int hihdr_y2r_v1_scale2p : 4; /* [7..4]  */
        unsigned int reserved_0 : 24;          /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_SCALE2P;

/* define the union U_HIHDR_WD_YUV2RGB_IN_DC00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc00 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_IN_DC00;

/* define the union U_HIHDR_WD_YUV2RGB_IN_DC01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc01 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_IN_DC01;

/* define the union U_HIHDR_WD_YUV2RGB_IN_DC02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc02 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_IN_DC02;

/* define the union U_HIHDR_WD_YUV2RGB_OUT_DC00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc00 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_OUT_DC00;

/* define the union U_HIHDR_WD_YUV2RGB_OUT_DC01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc01 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_OUT_DC01;

/* define the union U_HIHDR_WD_YUV2RGB_OUT_DC02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc02 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_OUT_DC02;

/* define the union U_HIHDR_WD_YUV2RGB_IN_DC10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc10 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_IN_DC10;

/* define the union U_HIHDR_WD_YUV2RGB_IN_DC11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc11 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_IN_DC11;

/* define the union U_HIHDR_WD_YUV2RGB_IN_DC12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_idc12 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;      /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_IN_DC12;

/* define the union U_HIHDR_WD_YUV2RGB_OUT_DC10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc10 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_OUT_DC10;

/* define the union U_HIHDR_WD_YUV2RGB_OUT_DC11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc11 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_OUT_DC11;

/* define the union U_HIHDR_WD_YUV2RGB_OUT_DC12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_odc12 : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;      /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_OUT_DC12;

/* define the union U_HIHDR_WD_YUV2RGB_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_v0_clip_min : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;             /* [15..12]  */
        unsigned int hihdr_y2r_v1_clip_min : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;             /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_MIN;

/* define the union U_HIHDR_WD_YUV2RGB_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int hihdr_y2r_v0_clip_max : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;             /* [15..12]  */
        unsigned int hihdr_y2r_v1_clip_max : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;             /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_HIHDR_WD_YUV2RGB_MAX;

/* define the union U_WDHDR_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_en : 1;         /* [0]  */
        unsigned int vhdr_gamut_bind : 1; /* [1]  */
        unsigned int vhdr_ck_gt_en : 1;   /* [2]  */
        unsigned int reserved_0 : 29;     /* [31..3]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_CTRL;

/* define the union U_WDHDR_DEGAMMA_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_degmm_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_CTRL;

/* define the union U_WDHDR_DEGAMMA_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_degamma_rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;        /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_REN;

/* define the union U_WDHDR_DEGAMMA_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x1_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;      /* [7..4]  */
        unsigned int v_degmm_x2_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;      /* [15..12]  */
        unsigned int v_degmm_x3_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;      /* [23..20]  */
        unsigned int v_degmm_x4_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_STEP1;

/* define the union U_WDHDR_DEGAMMA_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x5_step : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;      /* [7..4]  */
        unsigned int v_degmm_x6_step : 4; /* [11..8]  */
        unsigned int reserved_1 : 4;      /* [15..12]  */
        unsigned int v_degmm_x7_step : 4; /* [19..16]  */
        unsigned int reserved_2 : 4;      /* [23..20]  */
        unsigned int v_degmm_x8_step : 4; /* [27..24]  */
        unsigned int reserved_3 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_STEP2;

/* define the union U_WDHDR_DEGAMMA_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x1_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x2_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_POS1;

/* define the union U_WDHDR_DEGAMMA_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x3_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x4_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_POS2;

/* define the union U_WDHDR_DEGAMMA_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x5_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x6_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_POS3;

/* define the union U_WDHDR_DEGAMMA_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x7_pos : 12; /* [11..0]  */
        unsigned int reserved_0 : 4;      /* [15..12]  */
        unsigned int v_degmm_x8_pos : 12; /* [27..16]  */
        unsigned int reserved_1 : 4;      /* [31..28]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_POS4;

/* define the union U_WDHDR_DEGAMMA_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;     /* [7..6]  */
        unsigned int v_degmm_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;     /* [15..14]  */
        unsigned int v_degmm_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;     /* [23..22]  */
        unsigned int v_degmm_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;     /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_NUM1;

/* define the union U_WDHDR_DEGAMMA_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_degmm_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;     /* [7..6]  */
        unsigned int v_degmm_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;     /* [15..14]  */
        unsigned int v_degmm_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;     /* [23..22]  */
        unsigned int v_degmm_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;     /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DEGAMMA_NUM2;

/* define the union U_WDHDR_GAMUT_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;   /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_CTRL;

/* define the union U_WDHDR_GAMUT_COEF00 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF00;

/* define the union U_WDHDR_GAMUT_COEF01 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF01;

/* define the union U_WDHDR_GAMUT_COEF02 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF02;

/* define the union U_WDHDR_GAMUT_COEF10 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF10;

/* define the union U_WDHDR_GAMUT_COEF11 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF11;

/* define the union U_WDHDR_GAMUT_COEF12 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF12;

/* define the union U_WDHDR_GAMUT_COEF20 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF20;

/* define the union U_WDHDR_GAMUT_COEF21 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF21;

/* define the union U_WDHDR_GAMUT_COEF22 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_COEF22;

/* define the union U_WDHDR_GAMUT_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;      /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_SCALE;

/* define the union U_WDHDR_GAMUT_IDC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_idc0 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_IDC0;

/* define the union U_WDHDR_GAMUT_IDC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_idc1 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_IDC1;

/* define the union U_WDHDR_GAMUT_IDC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_idc2 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_IDC2;

/* define the union U_WDHDR_GAMUT_ODC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_odc0 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_ODC0;

/* define the union U_WDHDR_GAMUT_ODC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_odc1 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_ODC1;

/* define the union U_WDHDR_GAMUT_ODC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_odc2 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;      /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_ODC2;

/* define the union U_WDHDR_GAMUT_CLIP_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_clip_min : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;          /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_CLIP_MIN;

/* define the union U_WDHDR_GAMUT_CLIP_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamut_clip_max : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;          /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMUT_CLIP_MAX;

/* define the union U_WDHDR_TONEMAP_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;  /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_CTRL;

/* define the union U_WDHDR_TONEMAP_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_rd_en : 1; /* [0]  */
        unsigned int vhdr_sm_rd_en : 1;   /* [1]  */
        unsigned int reserved_0 : 30;     /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_REN;

/* define the union U_WDHDR_TONEMAP_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x1_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_tmap_x2_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_tmap_x3_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_tmap_x4_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_STEP1;

/* define the union U_WDHDR_TONEMAP_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x5_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_tmap_x6_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_tmap_x7_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_tmap_x8_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_STEP2;

/* define the union U_WDHDR_TONEMAP_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x1_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS1;

/* define the union U_WDHDR_TONEMAP_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x2_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS2;

/* define the union U_WDHDR_TONEMAP_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x3_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS3;

/* define the union U_WDHDR_TONEMAP_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x4_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS4;

/* define the union U_WDHDR_TONEMAP_POS5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x5_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS5;

/* define the union U_WDHDR_TONEMAP_POS6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x6_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS6;

/* define the union U_WDHDR_TONEMAP_POS7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x7_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS7;

/* define the union U_WDHDR_TONEMAP_POS8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x8_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_POS8;

/* define the union U_WDHDR_TONEMAP_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_tmap_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_tmap_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_tmap_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_NUM1;

/* define the union U_WDHDR_TONEMAP_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_tmap_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_tmap_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_tmap_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_tmap_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_NUM2;

/* define the union U_WDHDR_TONEMAP_SM_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x1_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_smap_x2_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_smap_x3_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_smap_x4_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_STEP1;

/* define the union U_WDHDR_TONEMAP_SM_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x5_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;     /* [7..5]  */
        unsigned int v_smap_x6_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;     /* [15..13]  */
        unsigned int v_smap_x7_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;     /* [23..21]  */
        unsigned int v_smap_x8_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;     /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_STEP2;

/* define the union U_WDHDR_TONEMAP_SM_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x1_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS1;

/* define the union U_WDHDR_TONEMAP_SM_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x2_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS2;

/* define the union U_WDHDR_TONEMAP_SM_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x3_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS3;

/* define the union U_WDHDR_TONEMAP_SM_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x4_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS4;

/* define the union U_WDHDR_TONEMAP_SM_POS5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x5_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS5;

/* define the union U_WDHDR_TONEMAP_SM_POS6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x6_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS6;

/* define the union U_WDHDR_TONEMAP_SM_POS7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x7_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS7;

/* define the union U_WDHDR_TONEMAP_SM_POS8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x8_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;    /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_POS8;

/* define the union U_WDHDR_TONEMAP_SM_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_smap_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_smap_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_smap_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_NUM1;

/* define the union U_WDHDR_TONEMAP_SM_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_smap_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;    /* [7..6]  */
        unsigned int v_smap_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;    /* [15..14]  */
        unsigned int v_smap_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;    /* [23..22]  */
        unsigned int v_smap_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;    /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_SM_NUM2;

/* define the union U_WDHDR_TONEMAP_LUMA_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_coef0 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_LUMA_COEF0;

/* define the union U_WDHDR_TONEMAP_LUMA_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_coef1 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_LUMA_COEF1;

/* define the union U_WDHDR_TONEMAP_LUMA_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_coef2 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;           /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_LUMA_COEF2;

/* define the union U_WDHDR_TONEMAP_LUMA_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_luma_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;          /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_LUMA_SCALE;

/* define the union U_WDHDR_TONEMAP_COEF_SCALE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_coef_scale : 4; /* [3..0]  */
        unsigned int reserved_0 : 28;          /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_COEF_SCALE;

/* define the union U_WDHDR_TONEMAP_OUT_CLIP_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_clip_min : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;             /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_OUT_CLIP_MIN;

/* define the union U_WDHDR_TONEMAP_OUT_CLIP_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_clip_max : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;             /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_OUT_CLIP_MAX;

/* define the union U_WDHDR_TONEMAP_OUT_DC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_dc0 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;        /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_OUT_DC0;

/* define the union U_WDHDR_TONEMAP_OUT_DC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_dc1 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;        /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_OUT_DC1;

/* define the union U_WDHDR_TONEMAP_OUT_DC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_tmap_out_dc2 : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;        /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_TONEMAP_OUT_DC2;

/* define the union U_WDHDR_GAMMA_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gmm_en : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_CTRL;

/* define the union U_WDHDR_GAMMA_REN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_gamma_rd_en : 1; /* [0]  */
        unsigned int reserved_0 : 31;      /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_REN;

/* define the union U_WDHDR_GAMMA_STEP1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x1_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;    /* [7..5]  */
        unsigned int v_gmm_x2_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;    /* [15..13]  */
        unsigned int v_gmm_x3_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;    /* [23..21]  */
        unsigned int v_gmm_x4_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_STEP1;

/* define the union U_WDHDR_GAMMA_STEP2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x5_step : 5; /* [4..0]  */
        unsigned int reserved_0 : 3;    /* [7..5]  */
        unsigned int v_gmm_x6_step : 5; /* [12..8]  */
        unsigned int reserved_1 : 3;    /* [15..13]  */
        unsigned int v_gmm_x7_step : 5; /* [20..16]  */
        unsigned int reserved_2 : 3;    /* [23..21]  */
        unsigned int v_gmm_x8_step : 5; /* [28..24]  */
        unsigned int reserved_3 : 3;    /* [31..29]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_STEP2;

/* define the union U_WDHDR_GAMMA_POS1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x1_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS1;

/* define the union U_WDHDR_GAMMA_POS2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x2_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS2;

/* define the union U_WDHDR_GAMMA_POS3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x3_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS3;

/* define the union U_WDHDR_GAMMA_POS4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x4_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS4;

/* define the union U_WDHDR_GAMMA_POS5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x5_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS5;

/* define the union U_WDHDR_GAMMA_POS6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x6_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS6;

/* define the union U_WDHDR_GAMMA_POS7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x7_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS7;

/* define the union U_WDHDR_GAMMA_POS8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x8_pos : 21; /* [20..0]  */
        unsigned int reserved_0 : 11;   /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_POS8;

/* define the union U_WDHDR_GAMMA_NUM1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x1_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int v_gmm_x2_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;   /* [15..14]  */
        unsigned int v_gmm_x3_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;   /* [23..22]  */
        unsigned int v_gmm_x4_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_NUM1;

/* define the union U_WDHDR_GAMMA_NUM2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_gmm_x5_num : 6; /* [5..0]  */
        unsigned int reserved_0 : 2;   /* [7..6]  */
        unsigned int v_gmm_x6_num : 6; /* [13..8]  */
        unsigned int reserved_1 : 2;   /* [15..14]  */
        unsigned int v_gmm_x7_num : 6; /* [21..16]  */
        unsigned int reserved_2 : 2;   /* [23..22]  */
        unsigned int v_gmm_x8_num : 6; /* [29..24]  */
        unsigned int reserved_3 : 2;   /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_GAMMA_NUM2;

/* define the union U_WDHDR_DITHER_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_tap_mode : 2;    /* [1..0]  */
        unsigned int vhdr_dither_domain_mode : 1; /* [2]  */
        unsigned int vhdr_dither_round : 1;       /* [3]  */
        unsigned int vhdr_dither_mode : 1;        /* [4]  */
        unsigned int vhdr_dither_en : 1;          /* [5]  */
        unsigned int vhdr_dither_round_unlim : 1; /* [6]  */
        unsigned int reserved_0 : 25;             /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_CTRL;

/* define the union U_WDHDR_DITHER_THR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_thr_min : 16; /* [15..0]  */
        unsigned int vhdr_dither_thr_max : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_THR;

/* define the union U_WDHDR_DITHER_SED_Y0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_y0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_Y0;

/* define the union U_WDHDR_DITHER_SED_U0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_u0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_U0;

/* define the union U_WDHDR_DITHER_SED_V0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_v0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_V0;

/* define the union U_WDHDR_DITHER_SED_W0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_w0 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_W0;

/* define the union U_WDHDR_DITHER_SED_Y1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_y1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_Y1;

/* define the union U_WDHDR_DITHER_SED_U1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_u1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_U1;

/* define the union U_WDHDR_DITHER_SED_V1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_v1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_V1;

/* define the union U_WDHDR_DITHER_SED_W1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_dither_sed_w1 : 31; /* [30..0]  */
        unsigned int reserved_0 : 1;          /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_DITHER_SED_W1;

/* define the union U_WDHDR_RGB2YUV_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_en : 1;  /* [0]  */
        unsigned int vhdr_cadj_en : 1; /* [1]  */
        unsigned int reserved_0 : 30;  /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_CTRL;

/* define the union U_WDHDR_RGB2YUV_COEF0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef00 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF0;

/* define the union U_WDHDR_RGB2YUV_COEF1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef01 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF1;

/* define the union U_WDHDR_RGB2YUV_COEF2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef02 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF2;

/* define the union U_WDHDR_RGB2YUV_COEF3 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef10 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF3;

/* define the union U_WDHDR_RGB2YUV_COEF4 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef11 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF4;

/* define the union U_WDHDR_RGB2YUV_COEF5 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef12 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF5;

/* define the union U_WDHDR_RGB2YUV_COEF6 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef20 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF6;

/* define the union U_WDHDR_RGB2YUV_COEF7 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef21 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF7;

/* define the union U_WDHDR_RGB2YUV_COEF8 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_coef22 : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;      /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_COEF8;

/* define the union U_WDHDR_RGB2YUV_SCALE2P */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_scale2p : 4;  /* [3..0]  */
        unsigned int vhdr_cadj_scale2p : 4; /* [7..4]  */
        unsigned int reserved_0 : 24;       /* [31..8]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_SCALE2P;

/* define the union U_WDHDR_RGB2YUV_IDC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_idc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_IDC0;

/* define the union U_WDHDR_RGB2YUV_IDC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_idc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_IDC1;

/* define the union U_WDHDR_RGB2YUV_IDC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_idc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_IDC2;

/* define the union U_WDHDR_RGB2YUV_ODC0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_odc0 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_ODC0;

/* define the union U_WDHDR_RGB2YUV_ODC1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_odc1 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_ODC1;

/* define the union U_WDHDR_RGB2YUV_ODC2 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_odc2 : 11; /* [10..0]  */
        unsigned int reserved_0 : 21;    /* [31..11]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_ODC2;

/* define the union U_WDHDR_RGB2YUV_MIN */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_clip_y_min : 10; /* [9..0]  */
        unsigned int vhdr_r2y_clip_c_min : 10; /* [19..10]  */
        unsigned int reserved_0 : 12;          /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_MIN;

/* define the union U_WDHDR_RGB2YUV_MAX */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vhdr_r2y_clip_y_max : 10; /* [9..0]  */
        unsigned int vhdr_r2y_clip_c_max : 10; /* [19..10]  */
        unsigned int reserved_0 : 12;          /* [31..20]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_WDHDR_RGB2YUV_MAX;

/* define the global struct */
typedef struct {
    volatile U_HIPPCTRL HIPPCTRL;                                     /* 0x0 */
    volatile unsigned int reserved_0[20991];                          /* 0x4~0x147fc */
    volatile U_HIHDR_V_YUV2RGB_CTRL HIHDR_V_YUV2RGB_CTRL;             /* 0x14800 */
    volatile U_HIHDR_V_YUV2RGB_COEF00 HIHDR_V_YUV2RGB_COEF00;         /* 0x14804 */
    volatile U_HIHDR_V_YUV2RGB_COEF01 HIHDR_V_YUV2RGB_COEF01;         /* 0x14808 */
    volatile U_HIHDR_V_YUV2RGB_COEF02 HIHDR_V_YUV2RGB_COEF02;         /* 0x1480c */
    volatile U_HIHDR_V_YUV2RGB_COEF03 HIHDR_V_YUV2RGB_COEF03;         /* 0x14810 */
    volatile U_HIHDR_V_YUV2RGB_COEF04 HIHDR_V_YUV2RGB_COEF04;         /* 0x14814 */
    volatile U_HIHDR_V_YUV2RGB_COEF05 HIHDR_V_YUV2RGB_COEF05;         /* 0x14818 */
    volatile U_HIHDR_V_YUV2RGB_COEF06 HIHDR_V_YUV2RGB_COEF06;         /* 0x1481c */
    volatile U_HIHDR_V_YUV2RGB_COEF07 HIHDR_V_YUV2RGB_COEF07;         /* 0x14820 */
    volatile U_HIHDR_V_YUV2RGB_COEF08 HIHDR_V_YUV2RGB_COEF08;         /* 0x14824 */
    volatile U_HIHDR_V_YUV2RGB_COEF10 HIHDR_V_YUV2RGB_COEF10;         /* 0x14828 */
    volatile U_HIHDR_V_YUV2RGB_COEF11 HIHDR_V_YUV2RGB_COEF11;         /* 0x1482c */
    volatile U_HIHDR_V_YUV2RGB_COEF12 HIHDR_V_YUV2RGB_COEF12;         /* 0x14830 */
    volatile U_HIHDR_V_YUV2RGB_COEF13 HIHDR_V_YUV2RGB_COEF13;         /* 0x14834 */
    volatile U_HIHDR_V_YUV2RGB_COEF14 HIHDR_V_YUV2RGB_COEF14;         /* 0x14838 */
    volatile U_HIHDR_V_YUV2RGB_COEF15 HIHDR_V_YUV2RGB_COEF15;         /* 0x1483c */
    volatile U_HIHDR_V_YUV2RGB_COEF16 HIHDR_V_YUV2RGB_COEF16;         /* 0x14840 */
    volatile U_HIHDR_V_YUV2RGB_COEF17 HIHDR_V_YUV2RGB_COEF17;         /* 0x14844 */
    volatile U_HIHDR_V_YUV2RGB_COEF18 HIHDR_V_YUV2RGB_COEF18;         /* 0x14848 */
    volatile U_HIHDR_V_YUV2RGB_SCALE2P HIHDR_V_YUV2RGB_SCALE2P;       /* 0x1484c */
    volatile U_HIHDR_V_YUV2RGB_IN_DC00 HIHDR_V_YUV2RGB_IN_DC00;       /* 0x14850 */
    volatile U_HIHDR_V_YUV2RGB_IN_DC01 HIHDR_V_YUV2RGB_IN_DC01;       /* 0x14854 */
    volatile U_HIHDR_V_YUV2RGB_IN_DC02 HIHDR_V_YUV2RGB_IN_DC02;       /* 0x14858 */
    volatile U_HIHDR_V_YUV2RGB_OUT_DC00 HIHDR_V_YUV2RGB_OUT_DC00;     /* 0x1485c */
    volatile U_HIHDR_V_YUV2RGB_OUT_DC01 HIHDR_V_YUV2RGB_OUT_DC01;     /* 0x14860 */
    volatile U_HIHDR_V_YUV2RGB_OUT_DC02 HIHDR_V_YUV2RGB_OUT_DC02;     /* 0x14864 */
    volatile U_HIHDR_V_YUV2RGB_IN_DC10 HIHDR_V_YUV2RGB_IN_DC10;       /* 0x14868 */
    volatile U_HIHDR_V_YUV2RGB_IN_DC11 HIHDR_V_YUV2RGB_IN_DC11;       /* 0x1486c */
    volatile U_HIHDR_V_YUV2RGB_IN_DC12 HIHDR_V_YUV2RGB_IN_DC12;       /* 0x14870 */
    volatile U_HIHDR_V_YUV2RGB_OUT_DC10 HIHDR_V_YUV2RGB_OUT_DC10;     /* 0x14874 */
    volatile U_HIHDR_V_YUV2RGB_OUT_DC11 HIHDR_V_YUV2RGB_OUT_DC11;     /* 0x14878 */
    volatile U_HIHDR_V_YUV2RGB_OUT_DC12 HIHDR_V_YUV2RGB_OUT_DC12;     /* 0x1487c */
    volatile U_HIHDR_V_YUV2RGB_MIN HIHDR_V_YUV2RGB_MIN;               /* 0x14880 */
    volatile U_HIHDR_V_YUV2RGB_MAX HIHDR_V_YUV2RGB_MAX;               /* 0x14884 */
    volatile unsigned int reserved_1[30];                             /* 0x14888~0x148fc */
    volatile U_VHDR_CTRL VHDR_CTRL;                                   /* 0x14900 */
    volatile unsigned int reserved_2[63];                             /* 0x14904~0x149fc */
    volatile U_VHDR_DEGAMMA_CTRL VHDR_DEGAMMA_CTRL;                   /* 0x14a00 */
    volatile U_VHDR_DEGAMMA_REN VHDR_DEGAMMA_REN;                     /* 0x14a04 */
    volatile unsigned int VHDR_DEGAMMA_DATA;                          /* 0x14a08 */
    volatile U_VHDR_DEGAMMA_STEP1 VHDR_DEGAMMA_STEP1;                 /* 0x14a0c */
    volatile U_VHDR_DEGAMMA_STEP2 VHDR_DEGAMMA_STEP2;                 /* 0x14a10 */
    volatile U_VHDR_DEGAMMA_POS1 VHDR_DEGAMMA_POS1;                   /* 0x14a14 */
    volatile U_VHDR_DEGAMMA_POS2 VHDR_DEGAMMA_POS2;                   /* 0x14a18 */
    volatile U_VHDR_DEGAMMA_POS3 VHDR_DEGAMMA_POS3;                   /* 0x14a1c */
    volatile U_VHDR_DEGAMMA_POS4 VHDR_DEGAMMA_POS4;                   /* 0x14a20 */
    volatile U_VHDR_DEGAMMA_NUM1 VHDR_DEGAMMA_NUM1;                   /* 0x14a24 */
    volatile U_VHDR_DEGAMMA_NUM2 VHDR_DEGAMMA_NUM2;                   /* 0x14a28 */
    volatile unsigned int reserved_3[53];                             /* 0x14a2c~0x14afc */
    volatile U_VHDR_GAMUT_CTRL VHDR_GAMUT_CTRL;                       /* 0x14b00 */
    volatile U_VHDR_GAMUT_COEF00 VHDR_GAMUT_COEF00;                   /* 0x14b04 */
    volatile U_VHDR_GAMUT_COEF01 VHDR_GAMUT_COEF01;                   /* 0x14b08 */
    volatile U_VHDR_GAMUT_COEF02 VHDR_GAMUT_COEF02;                   /* 0x14b0c */
    volatile U_VHDR_GAMUT_COEF10 VHDR_GAMUT_COEF10;                   /* 0x14b10 */
    volatile U_VHDR_GAMUT_COEF11 VHDR_GAMUT_COEF11;                   /* 0x14b14 */
    volatile U_VHDR_GAMUT_COEF12 VHDR_GAMUT_COEF12;                   /* 0x14b18 */
    volatile U_VHDR_GAMUT_COEF20 VHDR_GAMUT_COEF20;                   /* 0x14b1c */
    volatile U_VHDR_GAMUT_COEF21 VHDR_GAMUT_COEF21;                   /* 0x14b20 */
    volatile U_VHDR_GAMUT_COEF22 VHDR_GAMUT_COEF22;                   /* 0x14b24 */
    volatile U_VHDR_GAMUT_SCALE VHDR_GAMUT_SCALE;                     /* 0x14b28 */
    volatile U_VHDR_GAMUT_IDC0 VHDR_GAMUT_IDC0;                       /* 0x14b2c */
    volatile U_VHDR_GAMUT_IDC1 VHDR_GAMUT_IDC1;                       /* 0x14b30 */
    volatile U_VHDR_GAMUT_IDC2 VHDR_GAMUT_IDC2;                       /* 0x14b34 */
    volatile U_VHDR_GAMUT_ODC0 VHDR_GAMUT_ODC0;                       /* 0x14b38 */
    volatile U_VHDR_GAMUT_ODC1 VHDR_GAMUT_ODC1;                       /* 0x14b3c */
    volatile U_VHDR_GAMUT_ODC2 VHDR_GAMUT_ODC2;                       /* 0x14b40 */
    volatile U_VHDR_GAMUT_CLIP_MIN VHDR_GAMUT_CLIP_MIN;               /* 0x14b44 */
    volatile U_VHDR_GAMUT_CLIP_MAX VHDR_GAMUT_CLIP_MAX;               /* 0x14b48 */
    volatile unsigned int reserved_4[45];                             /* 0x14b4c~0x14bfc */
    volatile U_VHDR_TONEMAP_CTRL VHDR_TONEMAP_CTRL;                   /* 0x14c00 */
    volatile U_VHDR_TONEMAP_REN VHDR_TONEMAP_REN;                     /* 0x14c04 */
    volatile unsigned int VHDR_TONEMAP_DATA;                          /* 0x14c08 */
    volatile unsigned int VHDR_TONEMAP_SM_DATA;                       /* 0x14c0c */
    volatile U_VHDR_TONEMAP_STEP1 VHDR_TONEMAP_STEP1;                 /* 0x14c10 */
    volatile U_VHDR_TONEMAP_STEP2 VHDR_TONEMAP_STEP2;                 /* 0x14c14 */
    volatile U_VHDR_TONEMAP_POS1 VHDR_TONEMAP_POS1;                   /* 0x14c18 */
    volatile U_VHDR_TONEMAP_POS2 VHDR_TONEMAP_POS2;                   /* 0x14c1c */
    volatile U_VHDR_TONEMAP_POS3 VHDR_TONEMAP_POS3;                   /* 0x14c20 */
    volatile U_VHDR_TONEMAP_POS4 VHDR_TONEMAP_POS4;                   /* 0x14c24 */
    volatile U_VHDR_TONEMAP_POS5 VHDR_TONEMAP_POS5;                   /* 0x14c28 */
    volatile U_VHDR_TONEMAP_POS6 VHDR_TONEMAP_POS6;                   /* 0x14c2c */
    volatile U_VHDR_TONEMAP_POS7 VHDR_TONEMAP_POS7;                   /* 0x14c30 */
    volatile U_VHDR_TONEMAP_POS8 VHDR_TONEMAP_POS8;                   /* 0x14c34 */
    volatile U_VHDR_TONEMAP_NUM1 VHDR_TONEMAP_NUM1;                   /* 0x14c38 */
    volatile U_VHDR_TONEMAP_NUM2 VHDR_TONEMAP_NUM2;                   /* 0x14c3c */
    volatile U_VHDR_TONEMAP_SM_STEP1 VHDR_TONEMAP_SM_STEP1;           /* 0x14c40 */
    volatile U_VHDR_TONEMAP_SM_STEP2 VHDR_TONEMAP_SM_STEP2;           /* 0x14c44 */
    volatile U_VHDR_TONEMAP_SM_POS1 VHDR_TONEMAP_SM_POS1;             /* 0x14c48 */
    volatile U_VHDR_TONEMAP_SM_POS2 VHDR_TONEMAP_SM_POS2;             /* 0x14c4c */
    volatile U_VHDR_TONEMAP_SM_POS3 VHDR_TONEMAP_SM_POS3;             /* 0x14c50 */
    volatile U_VHDR_TONEMAP_SM_POS4 VHDR_TONEMAP_SM_POS4;             /* 0x14c54 */
    volatile U_VHDR_TONEMAP_SM_POS5 VHDR_TONEMAP_SM_POS5;             /* 0x14c58 */
    volatile U_VHDR_TONEMAP_SM_POS6 VHDR_TONEMAP_SM_POS6;             /* 0x14c5c */
    volatile U_VHDR_TONEMAP_SM_POS7 VHDR_TONEMAP_SM_POS7;             /* 0x14c60 */
    volatile U_VHDR_TONEMAP_SM_POS8 VHDR_TONEMAP_SM_POS8;             /* 0x14c64 */
    volatile U_VHDR_TONEMAP_SM_NUM1 VHDR_TONEMAP_SM_NUM1;             /* 0x14c68 */
    volatile U_VHDR_TONEMAP_SM_NUM2 VHDR_TONEMAP_SM_NUM2;             /* 0x14c6c */
    volatile U_VHDR_TONEMAP_LUMA_COEF0 VHDR_TONEMAP_LUMA_COEF0;       /* 0x14c70 */
    volatile U_VHDR_TONEMAP_LUMA_COEF1 VHDR_TONEMAP_LUMA_COEF1;       /* 0x14c74 */
    volatile U_VHDR_TONEMAP_LUMA_COEF2 VHDR_TONEMAP_LUMA_COEF2;       /* 0x14c78 */
    volatile U_VHDR_TONEMAP_LUMA_SCALE VHDR_TONEMAP_LUMA_SCALE;       /* 0x14c7c */
    volatile U_VHDR_TONEMAP_COEF_SCALE VHDR_TONEMAP_COEF_SCALE;       /* 0x14c80 */
    volatile U_VHDR_TONEMAP_OUT_CLIP_MIN VHDR_TONEMAP_OUT_CLIP_MIN;   /* 0x14c84 */
    volatile U_VHDR_TONEMAP_OUT_CLIP_MAX VHDR_TONEMAP_OUT_CLIP_MAX;   /* 0x14c88 */
    volatile U_VHDR_TONEMAP_OUT_DC0 VHDR_TONEMAP_OUT_DC0;             /* 0x14c8c */
    volatile U_VHDR_TONEMAP_OUT_DC1 VHDR_TONEMAP_OUT_DC1;             /* 0x14c90 */
    volatile U_VHDR_TONEMAP_OUT_DC2 VHDR_TONEMAP_OUT_DC2;             /* 0x14c94 */
    volatile unsigned int reserved_5[26];                             /* 0x14c98~0x14cfc */
    volatile U_VHDR_GAMMA_CTRL VHDR_GAMMA_CTRL;                       /* 0x14d00 */
    volatile U_VHDR_GAMMA_REN VHDR_GAMMA_REN;                         /* 0x14d04 */
    volatile unsigned int VHDR_GAMMMA_DATA;                           /* 0x14d08 */
    volatile U_VHDR_GAMMA_STEP1 VHDR_GAMMA_STEP1;                     /* 0x14d0c */
    volatile U_VHDR_GAMMA_STEP2 VHDR_GAMMA_STEP2;                     /* 0x14d10 */
    volatile U_VHDR_GAMMA_POS1 VHDR_GAMMA_POS1;                       /* 0x14d14 */
    volatile U_VHDR_GAMMA_POS2 VHDR_GAMMA_POS2;                       /* 0x14d18 */
    volatile U_VHDR_GAMMA_POS3 VHDR_GAMMA_POS3;                       /* 0x14d1c */
    volatile U_VHDR_GAMMA_POS4 VHDR_GAMMA_POS4;                       /* 0x14d20 */
    volatile U_VHDR_GAMMA_POS5 VHDR_GAMMA_POS5;                       /* 0x14d24 */
    volatile U_VHDR_GAMMA_POS6 VHDR_GAMMA_POS6;                       /* 0x14d28 */
    volatile U_VHDR_GAMMA_POS7 VHDR_GAMMA_POS7;                       /* 0x14d2c */
    volatile U_VHDR_GAMMA_POS8 VHDR_GAMMA_POS8;                       /* 0x14d30 */
    volatile U_VHDR_GAMMA_NUM1 VHDR_GAMMA_NUM1;                       /* 0x14d34 */
    volatile U_VHDR_GAMMA_NUM2 VHDR_GAMMA_NUM2;                       /* 0x14d38 */
    volatile unsigned int reserved_6[49];                             /* 0x14d3c~0x14dfc */
    volatile U_VHDR_DITHER_CTRL VHDR_DITHER_CTRL;                     /* 0x14e00 */
    volatile U_VHDR_DITHER_THR VHDR_DITHER_THR;                       /* 0x14e04 */
    volatile U_VHDR_DITHER_SED_Y0 VHDR_DITHER_SED_Y0;                 /* 0x14e08 */
    volatile U_VHDR_DITHER_SED_U0 VHDR_DITHER_SED_U0;                 /* 0x14e0c */
    volatile U_VHDR_DITHER_SED_V0 VHDR_DITHER_SED_V0;                 /* 0x14e10 */
    volatile U_VHDR_DITHER_SED_W0 VHDR_DITHER_SED_W0;                 /* 0x14e14 */
    volatile U_VHDR_DITHER_SED_Y1 VHDR_DITHER_SED_Y1;                 /* 0x14e18 */
    volatile U_VHDR_DITHER_SED_U1 VHDR_DITHER_SED_U1;                 /* 0x14e1c */
    volatile U_VHDR_DITHER_SED_V1 VHDR_DITHER_SED_V1;                 /* 0x14e20 */
    volatile U_VHDR_DITHER_SED_W1 VHDR_DITHER_SED_W1;                 /* 0x14e24 */
    volatile unsigned int reserved_7[54];                             /* 0x14e28~0x14efc */
    volatile U_VHDR_RGB2YUV_CTRL VHDR_RGB2YUV_CTRL;                   /* 0x14f00 */
    volatile U_VHDR_RGB2YUV_COEF0 VHDR_RGB2YUV_COEF0;                 /* 0x14f04 */
    volatile U_VHDR_RGB2YUV_COEF1 VHDR_RGB2YUV_COEF1;                 /* 0x14f08 */
    volatile U_VHDR_RGB2YUV_COEF2 VHDR_RGB2YUV_COEF2;                 /* 0x14f0c */
    volatile U_VHDR_RGB2YUV_COEF3 VHDR_RGB2YUV_COEF3;                 /* 0x14f10 */
    volatile U_VHDR_RGB2YUV_COEF4 VHDR_RGB2YUV_COEF4;                 /* 0x14f14 */
    volatile U_VHDR_RGB2YUV_COEF5 VHDR_RGB2YUV_COEF5;                 /* 0x14f18 */
    volatile U_VHDR_RGB2YUV_COEF6 VHDR_RGB2YUV_COEF6;                 /* 0x14f1c */
    volatile U_VHDR_RGB2YUV_COEF7 VHDR_RGB2YUV_COEF7;                 /* 0x14f20 */
    volatile U_VHDR_RGB2YUV_COEF8 VHDR_RGB2YUV_COEF8;                 /* 0x14f24 */
    volatile U_VHDR_RGB2YUV_SCALE2P VHDR_RGB2YUV_SCALE2P;             /* 0x14f28 */
    volatile U_VHDR_RGB2YUV_IDC0 VHDR_RGB2YUV_IDC0;                   /* 0x14f2c */
    volatile U_VHDR_RGB2YUV_IDC1 VHDR_RGB2YUV_IDC1;                   /* 0x14f30 */
    volatile U_VHDR_RGB2YUV_IDC2 VHDR_RGB2YUV_IDC2;                   /* 0x14f34 */
    volatile U_VHDR_RGB2YUV_ODC0 VHDR_RGB2YUV_ODC0;                   /* 0x14f38 */
    volatile U_VHDR_RGB2YUV_ODC1 VHDR_RGB2YUV_ODC1;                   /* 0x14f3c */
    volatile U_VHDR_RGB2YUV_ODC2 VHDR_RGB2YUV_ODC2;                   /* 0x14f40 */
    volatile U_VHDR_RGB2YUV_MIN VHDR_RGB2YUV_MIN;                     /* 0x14f44 */
    volatile U_VHDR_RGB2YUV_MAX VHDR_RGB2YUV_MAX;                     /* 0x14f48 */
    volatile unsigned int reserved_8[3117];                           /* 0x14f4c~0x17ffc */
    volatile U_GHDR_CTRL GHDR_CTRL;                                   /* 0x18000 */
    volatile unsigned int reserved_9[63];                             /* 0x18004~0x180fc */
    volatile U_GHDR_DEGAMMA_CTRL GHDR_DEGAMMA_CTRL;                   /* 0x18100 */
    volatile U_GHDR_DEGAMMA_STEP GHDR_DEGAMMA_STEP;                   /* 0x18104 */
    volatile U_GHDR_DEGAMMA_POS1 GHDR_DEGAMMA_POS1;                   /* 0x18108 */
    volatile U_GHDR_DEGAMMA_POS2 GHDR_DEGAMMA_POS2;                   /* 0x1810c */
    volatile U_GHDR_DEGAMMA_NUM GHDR_DEGAMMA_NUM;                     /* 0x18110 */
    volatile unsigned int reserved_10[59];                            /* 0x18114~0x181fc */
    volatile U_GHDR_GAMUT_CTRL GHDR_GAMUT_CTRL;                       /* 0x18200 */
    volatile U_GHDR_GAMUT_COEF00 GHDR_GAMUT_COEF00;                   /* 0x18204 */
    volatile U_GHDR_GAMUT_COEF01 GHDR_GAMUT_COEF01;                   /* 0x18208 */
    volatile U_GHDR_GAMUT_COEF02 GHDR_GAMUT_COEF02;                   /* 0x1820c */
    volatile U_GHDR_GAMUT_COEF10 GHDR_GAMUT_COEF10;                   /* 0x18210 */
    volatile U_GHDR_GAMUT_COEF11 GHDR_GAMUT_COEF11;                   /* 0x18214 */
    volatile U_GHDR_GAMUT_COEF12 GHDR_GAMUT_COEF12;                   /* 0x18218 */
    volatile U_GHDR_GAMUT_COEF20 GHDR_GAMUT_COEF20;                   /* 0x1821c */
    volatile U_GHDR_GAMUT_COEF21 GHDR_GAMUT_COEF21;                   /* 0x18220 */
    volatile U_GHDR_GAMUT_COEF22 GHDR_GAMUT_COEF22;                   /* 0x18224 */
    volatile U_GHDR_GAMUT_SCALE GHDR_GAMUT_SCALE;                     /* 0x18228 */
    volatile U_GHDR_GAMUT_CLIP_MIN GHDR_GAMUT_CLIP_MIN;               /* 0x1822c */
    volatile U_GHDR_GAMUT_CLIP_MAX GHDR_GAMUT_CLIP_MAX;               /* 0x18230 */
    volatile unsigned int reserved_11[51];                            /* 0x18234~0x182fc */
    volatile U_GHDR_TONEMAP_CTRL GHDR_TONEMAP_CTRL;                   /* 0x18300 */
    volatile U_GHDR_TONEMAP_REN GHDR_TONEMAP_REN;                     /* 0x18304 */
    volatile unsigned int GHDR_TONEMAP_DATA;                          /* 0x18308 */
    volatile U_GHDR_TONEMAP_STEP GHDR_TONEMAP_STEP;                   /* 0x1830c */
    volatile U_GHDR_TONEMAP_POS1 GHDR_TONEMAP_POS1;                   /* 0x18310 */
    volatile U_GHDR_TONEMAP_POS2 GHDR_TONEMAP_POS2;                   /* 0x18314 */
    volatile U_GHDR_TONEMAP_POS3 GHDR_TONEMAP_POS3;                   /* 0x18318 */
    volatile U_GHDR_TONEMAP_POS4 GHDR_TONEMAP_POS4;                   /* 0x1831c */
    volatile U_GHDR_TONEMAP_NUM GHDR_TONEMAP_NUM;                     /* 0x18320 */
    volatile U_GHDR_TONEMAP_LUMA_COEF0 GHDR_TONEMAP_LUMA_COEF0;       /* 0x18324 */
    volatile U_GHDR_TONEMAP_LUMA_COEF1 GHDR_TONEMAP_LUMA_COEF1;       /* 0x18328 */
    volatile U_GHDR_TONEMAP_LUMA_COEF2 GHDR_TONEMAP_LUMA_COEF2;       /* 0x1832c */
    volatile U_GHDR_TONEMAP_LUMA_SCALE GHDR_TONEMAP_LUMA_SCALE;       /* 0x18330 */
    volatile U_GHDR_TONEMAP_COEF_SCALE GHDR_TONEMAP_COEF_SCALE;       /* 0x18334 */
    volatile U_GHDR_TONEMAP_OUT_CLIP_MIN GHDR_TONEMAP_OUT_CLIP_MIN;   /* 0x18338 */
    volatile U_GHDR_TONEMAP_OUT_CLIP_MAX GHDR_TONEMAP_OUT_CLIP_MAX;   /* 0x1833c */
    volatile unsigned int reserved_12[48];                            /* 0x18340~0x183fc */
    volatile U_GHDR_GAMMA_CTRL GHDR_GAMMA_CTRL;                       /* 0x18400 */
    volatile U_GHDR_GAMMA_REN GHDR_GAMMA_REN;                         /* 0x18404 */
    volatile unsigned int GHDR_GAMMMA_DATA;                           /* 0x18408 */
    volatile U_GHDR_GAMMA_STEP1 GHDR_GAMMA_STEP1;                     /* 0x1840c */
    volatile U_GHDR_GAMMA_STEP2 GHDR_GAMMA_STEP2;                     /* 0x18410 */
    volatile U_GHDR_GAMMA_POS1 GHDR_GAMMA_POS1;                       /* 0x18414 */
    volatile U_GHDR_GAMMA_POS2 GHDR_GAMMA_POS2;                       /* 0x18418 */
    volatile U_GHDR_GAMMA_POS3 GHDR_GAMMA_POS3;                       /* 0x1841c */
    volatile U_GHDR_GAMMA_POS4 GHDR_GAMMA_POS4;                       /* 0x18420 */
    volatile U_GHDR_GAMMA_NUM1 GHDR_GAMMA_NUM1;                       /* 0x18424 */
    volatile U_GHDR_GAMMA_NUM2 GHDR_GAMMA_NUM2;                       /* 0x18428 */
    volatile unsigned int reserved_13[53];                            /* 0x1842c~0x184fc */
    volatile U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;                     /* 0x18500 */
    volatile U_GHDR_DITHER_THR GHDR_DITHER_THR;                       /* 0x18504 */
    volatile U_GHDR_DITHER_SED_Y0 GHDR_DITHER_SED_Y0;                 /* 0x18508 */
    volatile U_GHDR_DITHER_SED_U0 GHDR_DITHER_SED_U0;                 /* 0x1850c */
    volatile U_GHDR_DITHER_SED_V0 GHDR_DITHER_SED_V0;                 /* 0x18510 */
    volatile U_GHDR_DITHER_SED_W0 GHDR_DITHER_SED_W0;                 /* 0x18514 */
    volatile U_GHDR_DITHER_SED_Y1 GHDR_DITHER_SED_Y1;                 /* 0x18518 */
    volatile U_GHDR_DITHER_SED_U1 GHDR_DITHER_SED_U1;                 /* 0x1851c */
    volatile U_GHDR_DITHER_SED_V1 GHDR_DITHER_SED_V1;                 /* 0x18520 */
    volatile U_GHDR_DITHER_SED_W1 GHDR_DITHER_SED_W1;                 /* 0x18524 */
    volatile unsigned int reserved_14[54];                            /* 0x18528~0x185fc */
    volatile U_HIHDR_G_RGB2YUV_CTRL HIHDR_G_RGB2YUV_CTRL;             /* 0x18600 */
    volatile U_HIHDR_G_RGB2YUV_COEF0 HIHDR_G_RGB2YUV_COEF0;           /* 0x18604 */
    volatile U_HIHDR_G_RGB2YUV_COEF1 HIHDR_G_RGB2YUV_COEF1;           /* 0x18608 */
    volatile U_HIHDR_G_RGB2YUV_COEF2 HIHDR_G_RGB2YUV_COEF2;           /* 0x1860c */
    volatile U_HIHDR_G_RGB2YUV_COEF3 HIHDR_G_RGB2YUV_COEF3;           /* 0x18610 */
    volatile U_HIHDR_G_RGB2YUV_COEF4 HIHDR_G_RGB2YUV_COEF4;           /* 0x18614 */
    volatile U_HIHDR_G_RGB2YUV_COEF5 HIHDR_G_RGB2YUV_COEF5;           /* 0x18618 */
    volatile U_HIHDR_G_RGB2YUV_COEF6 HIHDR_G_RGB2YUV_COEF6;           /* 0x1861c */
    volatile U_HIHDR_G_RGB2YUV_COEF7 HIHDR_G_RGB2YUV_COEF7;           /* 0x18620 */
    volatile U_HIHDR_G_RGB2YUV_COEF8 HIHDR_G_RGB2YUV_COEF8;           /* 0x18624 */
    volatile U_HIHDR_G_RGB2YUV_SCALE2P HIHDR_G_RGB2YUV_SCALE2P;       /* 0x18628 */
    volatile U_HIHDR_G_RGB2YUV_IDC0 HIHDR_G_RGB2YUV_IDC0;             /* 0x1862c */
    volatile U_HIHDR_G_RGB2YUV_IDC1 HIHDR_G_RGB2YUV_IDC1;             /* 0x18630 */
    volatile U_HIHDR_G_RGB2YUV_IDC2 HIHDR_G_RGB2YUV_IDC2;             /* 0x18634 */
    volatile U_HIHDR_G_RGB2YUV_ODC0 HIHDR_G_RGB2YUV_ODC0;             /* 0x18638 */
    volatile U_HIHDR_G_RGB2YUV_ODC1 HIHDR_G_RGB2YUV_ODC1;             /* 0x1863c */
    volatile U_HIHDR_G_RGB2YUV_ODC2 HIHDR_G_RGB2YUV_ODC2;             /* 0x18640 */
    volatile U_HIHDR_G_RGB2YUV_MIN HIHDR_G_RGB2YUV_MIN;               /* 0x18644 */
    volatile U_HIHDR_G_RGB2YUV_MAX HIHDR_G_RGB2YUV_MAX;               /* 0x18648 */
    volatile unsigned int reserved_15[2669];                          /* 0x1864c~0x1affc */
    volatile U_HIHDR_WD_YUV2RGB_CTRL HIHDR_WD_YUV2RGB_CTRL;           /* 0x1b000 */
    volatile U_HIHDR_WD_YUV2RGB_COEF00 HIHDR_WD_YUV2RGB_COEF00;       /* 0x1b004 */
    volatile U_HIHDR_WD_YUV2RGB_COEF01 HIHDR_WD_YUV2RGB_COEF01;       /* 0x1b008 */
    volatile U_HIHDR_WD_YUV2RGB_COEF02 HIHDR_WD_YUV2RGB_COEF02;       /* 0x1b00c */
    volatile U_HIHDR_WD_YUV2RGB_COEF03 HIHDR_WD_YUV2RGB_COEF03;       /* 0x1b010 */
    volatile U_HIHDR_WD_YUV2RGB_COEF04 HIHDR_WD_YUV2RGB_COEF04;       /* 0x1b014 */
    volatile U_HIHDR_WD_YUV2RGB_COEF05 HIHDR_WD_YUV2RGB_COEF05;       /* 0x1b018 */
    volatile U_HIHDR_WD_YUV2RGB_COEF06 HIHDR_WD_YUV2RGB_COEF06;       /* 0x1b01c */
    volatile U_HIHDR_WD_YUV2RGB_COEF07 HIHDR_WD_YUV2RGB_COEF07;       /* 0x1b020 */
    volatile U_HIHDR_WD_YUV2RGB_COEF08 HIHDR_WD_YUV2RGB_COEF08;       /* 0x1b024 */
    volatile U_HIHDR_WD_YUV2RGB_COEF10 HIHDR_WD_YUV2RGB_COEF10;       /* 0x1b028 */
    volatile U_HIHDR_WD_YUV2RGB_COEF11 HIHDR_WD_YUV2RGB_COEF11;       /* 0x1b02c */
    volatile U_HIHDR_WD_YUV2RGB_COEF12 HIHDR_WD_YUV2RGB_COEF12;       /* 0x1b030 */
    volatile U_HIHDR_WD_YUV2RGB_COEF13 HIHDR_WD_YUV2RGB_COEF13;       /* 0x1b034 */
    volatile U_HIHDR_WD_YUV2RGB_COEF14 HIHDR_WD_YUV2RGB_COEF14;       /* 0x1b038 */
    volatile U_HIHDR_WD_YUV2RGB_COEF15 HIHDR_WD_YUV2RGB_COEF15;       /* 0x1b03c */
    volatile U_HIHDR_WD_YUV2RGB_COEF16 HIHDR_WD_YUV2RGB_COEF16;       /* 0x1b040 */
    volatile U_HIHDR_WD_YUV2RGB_COEF17 HIHDR_WD_YUV2RGB_COEF17;       /* 0x1b044 */
    volatile U_HIHDR_WD_YUV2RGB_COEF18 HIHDR_WD_YUV2RGB_COEF18;       /* 0x1b048 */
    volatile U_HIHDR_WD_YUV2RGB_SCALE2P HIHDR_WD_YUV2RGB_SCALE2P;     /* 0x1b04c */
    volatile U_HIHDR_WD_YUV2RGB_IN_DC00 HIHDR_WD_YUV2RGB_IN_DC00;     /* 0x1b050 */
    volatile U_HIHDR_WD_YUV2RGB_IN_DC01 HIHDR_WD_YUV2RGB_IN_DC01;     /* 0x1b054 */
    volatile U_HIHDR_WD_YUV2RGB_IN_DC02 HIHDR_WD_YUV2RGB_IN_DC02;     /* 0x1b058 */
    volatile U_HIHDR_WD_YUV2RGB_OUT_DC00 HIHDR_WD_YUV2RGB_OUT_DC00;   /* 0x1b05c */
    volatile U_HIHDR_WD_YUV2RGB_OUT_DC01 HIHDR_WD_YUV2RGB_OUT_DC01;   /* 0x1b060 */
    volatile U_HIHDR_WD_YUV2RGB_OUT_DC02 HIHDR_WD_YUV2RGB_OUT_DC02;   /* 0x1b064 */
    volatile U_HIHDR_WD_YUV2RGB_IN_DC10 HIHDR_WD_YUV2RGB_IN_DC10;     /* 0x1b068 */
    volatile U_HIHDR_WD_YUV2RGB_IN_DC11 HIHDR_WD_YUV2RGB_IN_DC11;     /* 0x1b06c */
    volatile U_HIHDR_WD_YUV2RGB_IN_DC12 HIHDR_WD_YUV2RGB_IN_DC12;     /* 0x1b070 */
    volatile U_HIHDR_WD_YUV2RGB_OUT_DC10 HIHDR_WD_YUV2RGB_OUT_DC10;   /* 0x1b074 */
    volatile U_HIHDR_WD_YUV2RGB_OUT_DC11 HIHDR_WD_YUV2RGB_OUT_DC11;   /* 0x1b078 */
    volatile U_HIHDR_WD_YUV2RGB_OUT_DC12 HIHDR_WD_YUV2RGB_OUT_DC12;   /* 0x1b07c */
    volatile U_HIHDR_WD_YUV2RGB_MIN HIHDR_WD_YUV2RGB_MIN;             /* 0x1b080 */
    volatile U_HIHDR_WD_YUV2RGB_MAX HIHDR_WD_YUV2RGB_MAX;             /* 0x1b084 */
    volatile unsigned int reserved_16[30];                            /* 0x1b088~0x1b0fc */
    volatile U_WDHDR_CTRL WDHDR_CTRL;                                 /* 0x1b100 */
    volatile unsigned int reserved_17[63];                            /* 0x1b104~0x1b1fc */
    volatile U_WDHDR_DEGAMMA_CTRL WDHDR_DEGAMMA_CTRL;                 /* 0x1b200 */
    volatile U_WDHDR_DEGAMMA_REN WDHDR_DEGAMMA_REN;                   /* 0x1b204 */
    volatile unsigned int WDHDR_DEGAMMA_DATA;                         /* 0x1b208 */
    volatile U_WDHDR_DEGAMMA_STEP1 WDHDR_DEGAMMA_STEP1;               /* 0x1b20c */
    volatile U_WDHDR_DEGAMMA_STEP2 WDHDR_DEGAMMA_STEP2;               /* 0x1b210 */
    volatile U_WDHDR_DEGAMMA_POS1 WDHDR_DEGAMMA_POS1;                 /* 0x1b214 */
    volatile U_WDHDR_DEGAMMA_POS2 WDHDR_DEGAMMA_POS2;                 /* 0x1b218 */
    volatile U_WDHDR_DEGAMMA_POS3 WDHDR_DEGAMMA_POS3;                 /* 0x1b21c */
    volatile U_WDHDR_DEGAMMA_POS4 WDHDR_DEGAMMA_POS4;                 /* 0x1b220 */
    volatile U_WDHDR_DEGAMMA_NUM1 WDHDR_DEGAMMA_NUM1;                 /* 0x1b224 */
    volatile U_WDHDR_DEGAMMA_NUM2 WDHDR_DEGAMMA_NUM2;                 /* 0x1b228 */
    volatile unsigned int reserved_18[53];                            /* 0x1b22c~0x1b2fc */
    volatile U_WDHDR_GAMUT_CTRL WDHDR_GAMUT_CTRL;                     /* 0x1b300 */
    volatile U_WDHDR_GAMUT_COEF00 WDHDR_GAMUT_COEF00;                 /* 0x1b304 */
    volatile U_WDHDR_GAMUT_COEF01 WDHDR_GAMUT_COEF01;                 /* 0x1b308 */
    volatile U_WDHDR_GAMUT_COEF02 WDHDR_GAMUT_COEF02;                 /* 0x1b30c */
    volatile U_WDHDR_GAMUT_COEF10 WDHDR_GAMUT_COEF10;                 /* 0x1b310 */
    volatile U_WDHDR_GAMUT_COEF11 WDHDR_GAMUT_COEF11;                 /* 0x1b314 */
    volatile U_WDHDR_GAMUT_COEF12 WDHDR_GAMUT_COEF12;                 /* 0x1b318 */
    volatile U_WDHDR_GAMUT_COEF20 WDHDR_GAMUT_COEF20;                 /* 0x1b31c */
    volatile U_WDHDR_GAMUT_COEF21 WDHDR_GAMUT_COEF21;                 /* 0x1b320 */
    volatile U_WDHDR_GAMUT_COEF22 WDHDR_GAMUT_COEF22;                 /* 0x1b324 */
    volatile U_WDHDR_GAMUT_SCALE WDHDR_GAMUT_SCALE;                   /* 0x1b328 */
    volatile U_WDHDR_GAMUT_IDC0 WDHDR_GAMUT_IDC0;                     /* 0x1b32c */
    volatile U_WDHDR_GAMUT_IDC1 WDHDR_GAMUT_IDC1;                     /* 0x1b330 */
    volatile U_WDHDR_GAMUT_IDC2 WDHDR_GAMUT_IDC2;                     /* 0x1b334 */
    volatile U_WDHDR_GAMUT_ODC0 WDHDR_GAMUT_ODC0;                     /* 0x1b338 */
    volatile U_WDHDR_GAMUT_ODC1 WDHDR_GAMUT_ODC1;                     /* 0x1b33c */
    volatile U_WDHDR_GAMUT_ODC2 WDHDR_GAMUT_ODC2;                     /* 0x1b340 */
    volatile U_WDHDR_GAMUT_CLIP_MIN WDHDR_GAMUT_CLIP_MIN;             /* 0x1b344 */
    volatile U_WDHDR_GAMUT_CLIP_MAX WDHDR_GAMUT_CLIP_MAX;             /* 0x1b348 */
    volatile unsigned int reserved_19[45];                            /* 0x1b34c~0x1b3fc */
    volatile U_WDHDR_TONEMAP_CTRL WDHDR_TONEMAP_CTRL;                 /* 0x1b400 */
    volatile U_WDHDR_TONEMAP_REN WDHDR_TONEMAP_REN;                   /* 0x1b404 */
    volatile unsigned int WDHDR_TONEMAP_DATA;                         /* 0x1b408 */
    volatile unsigned int WDHDR_TONEMAP_SM_DATA;                      /* 0x1b40c */
    volatile U_WDHDR_TONEMAP_STEP1 WDHDR_TONEMAP_STEP1;               /* 0x1b410 */
    volatile U_WDHDR_TONEMAP_STEP2 WDHDR_TONEMAP_STEP2;               /* 0x1b414 */
    volatile U_WDHDR_TONEMAP_POS1 WDHDR_TONEMAP_POS1;                 /* 0x1b418 */
    volatile U_WDHDR_TONEMAP_POS2 WDHDR_TONEMAP_POS2;                 /* 0x1b41c */
    volatile U_WDHDR_TONEMAP_POS3 WDHDR_TONEMAP_POS3;                 /* 0x1b420 */
    volatile U_WDHDR_TONEMAP_POS4 WDHDR_TONEMAP_POS4;                 /* 0x1b424 */
    volatile U_WDHDR_TONEMAP_POS5 WDHDR_TONEMAP_POS5;                 /* 0x1b428 */
    volatile U_WDHDR_TONEMAP_POS6 WDHDR_TONEMAP_POS6;                 /* 0x1b42c */
    volatile U_WDHDR_TONEMAP_POS7 WDHDR_TONEMAP_POS7;                 /* 0x1b430 */
    volatile U_WDHDR_TONEMAP_POS8 WDHDR_TONEMAP_POS8;                 /* 0x1b434 */
    volatile U_WDHDR_TONEMAP_NUM1 WDHDR_TONEMAP_NUM1;                 /* 0x1b438 */
    volatile U_WDHDR_TONEMAP_NUM2 WDHDR_TONEMAP_NUM2;                 /* 0x1b43c */
    volatile U_WDHDR_TONEMAP_SM_STEP1 WDHDR_TONEMAP_SM_STEP1;         /* 0x1b440 */
    volatile U_WDHDR_TONEMAP_SM_STEP2 WDHDR_TONEMAP_SM_STEP2;         /* 0x1b444 */
    volatile U_WDHDR_TONEMAP_SM_POS1 WDHDR_TONEMAP_SM_POS1;           /* 0x1b448 */
    volatile U_WDHDR_TONEMAP_SM_POS2 WDHDR_TONEMAP_SM_POS2;           /* 0x1b44c */
    volatile U_WDHDR_TONEMAP_SM_POS3 WDHDR_TONEMAP_SM_POS3;           /* 0x1b450 */
    volatile U_WDHDR_TONEMAP_SM_POS4 WDHDR_TONEMAP_SM_POS4;           /* 0x1b454 */
    volatile U_WDHDR_TONEMAP_SM_POS5 WDHDR_TONEMAP_SM_POS5;           /* 0x1b458 */
    volatile U_WDHDR_TONEMAP_SM_POS6 WDHDR_TONEMAP_SM_POS6;           /* 0x1b45c */
    volatile U_WDHDR_TONEMAP_SM_POS7 WDHDR_TONEMAP_SM_POS7;           /* 0x1b460 */
    volatile U_WDHDR_TONEMAP_SM_POS8 WDHDR_TONEMAP_SM_POS8;           /* 0x1b464 */
    volatile U_WDHDR_TONEMAP_SM_NUM1 WDHDR_TONEMAP_SM_NUM1;           /* 0x1b468 */
    volatile U_WDHDR_TONEMAP_SM_NUM2 WDHDR_TONEMAP_SM_NUM2;           /* 0x1b46c */
    volatile U_WDHDR_TONEMAP_LUMA_COEF0 WDHDR_TONEMAP_LUMA_COEF0;     /* 0x1b470 */
    volatile U_WDHDR_TONEMAP_LUMA_COEF1 WDHDR_TONEMAP_LUMA_COEF1;     /* 0x1b474 */
    volatile U_WDHDR_TONEMAP_LUMA_COEF2 WDHDR_TONEMAP_LUMA_COEF2;     /* 0x1b478 */
    volatile U_WDHDR_TONEMAP_LUMA_SCALE WDHDR_TONEMAP_LUMA_SCALE;     /* 0x1b47c */
    volatile U_WDHDR_TONEMAP_COEF_SCALE WDHDR_TONEMAP_COEF_SCALE;     /* 0x1b480 */
    volatile U_WDHDR_TONEMAP_OUT_CLIP_MIN WDHDR_TONEMAP_OUT_CLIP_MIN; /* 0x1b484 */
    volatile U_WDHDR_TONEMAP_OUT_CLIP_MAX WDHDR_TONEMAP_OUT_CLIP_MAX; /* 0x1b488 */
    volatile U_WDHDR_TONEMAP_OUT_DC0 WDHDR_TONEMAP_OUT_DC0;           /* 0x1b48c */
    volatile U_WDHDR_TONEMAP_OUT_DC1 WDHDR_TONEMAP_OUT_DC1;           /* 0x1b490 */
    volatile U_WDHDR_TONEMAP_OUT_DC2 WDHDR_TONEMAP_OUT_DC2;           /* 0x1b494 */
    volatile unsigned int reserved_20[26];                            /* 0x1b498~0x1b4fc */
    volatile U_WDHDR_GAMMA_CTRL WDHDR_GAMMA_CTRL;                     /* 0x1b500 */
    volatile U_WDHDR_GAMMA_REN WDHDR_GAMMA_REN;                       /* 0x1b504 */
    volatile unsigned int WDHDR_GAMMMA_DATA;                          /* 0x1b508 */
    volatile U_WDHDR_GAMMA_STEP1 WDHDR_GAMMA_STEP1;                   /* 0x1b50c */
    volatile U_WDHDR_GAMMA_STEP2 WDHDR_GAMMA_STEP2;                   /* 0x1b510 */
    volatile U_WDHDR_GAMMA_POS1 WDHDR_GAMMA_POS1;                     /* 0x1b514 */
    volatile U_WDHDR_GAMMA_POS2 WDHDR_GAMMA_POS2;                     /* 0x1b518 */
    volatile U_WDHDR_GAMMA_POS3 WDHDR_GAMMA_POS3;                     /* 0x1b51c */
    volatile U_WDHDR_GAMMA_POS4 WDHDR_GAMMA_POS4;                     /* 0x1b520 */
    volatile U_WDHDR_GAMMA_POS5 WDHDR_GAMMA_POS5;                     /* 0x1b524 */
    volatile U_WDHDR_GAMMA_POS6 WDHDR_GAMMA_POS6;                     /* 0x1b528 */
    volatile U_WDHDR_GAMMA_POS7 WDHDR_GAMMA_POS7;                     /* 0x1b52c */
    volatile U_WDHDR_GAMMA_POS8 WDHDR_GAMMA_POS8;                     /* 0x1b530 */
    volatile U_WDHDR_GAMMA_NUM1 WDHDR_GAMMA_NUM1;                     /* 0x1b534 */
    volatile U_WDHDR_GAMMA_NUM2 WDHDR_GAMMA_NUM2;                     /* 0x1b538 */
    volatile unsigned int reserved_21[49];                            /* 0x1b53c~0x1b5fc */
    volatile U_WDHDR_DITHER_CTRL WDHDR_DITHER_CTRL;                   /* 0x1b600 */
    volatile U_WDHDR_DITHER_THR WDHDR_DITHER_THR;                     /* 0x1b604 */
    volatile U_WDHDR_DITHER_SED_Y0 WDHDR_DITHER_SED_Y0;               /* 0x1b608 */
    volatile U_WDHDR_DITHER_SED_U0 WDHDR_DITHER_SED_U0;               /* 0x1b60c */
    volatile U_WDHDR_DITHER_SED_V0 WDHDR_DITHER_SED_V0;               /* 0x1b610 */
    volatile U_WDHDR_DITHER_SED_W0 WDHDR_DITHER_SED_W0;               /* 0x1b614 */
    volatile U_WDHDR_DITHER_SED_Y1 WDHDR_DITHER_SED_Y1;               /* 0x1b618 */
    volatile U_WDHDR_DITHER_SED_U1 WDHDR_DITHER_SED_U1;               /* 0x1b61c */
    volatile U_WDHDR_DITHER_SED_V1 WDHDR_DITHER_SED_V1;               /* 0x1b620 */
    volatile U_WDHDR_DITHER_SED_W1 WDHDR_DITHER_SED_W1;               /* 0x1b624 */
    volatile unsigned int reserved_22[54];                            /* 0x1b628~0x1b6fc */
    volatile U_WDHDR_RGB2YUV_CTRL WDHDR_RGB2YUV_CTRL;                 /* 0x1b700 */
    volatile U_WDHDR_RGB2YUV_COEF0 WDHDR_RGB2YUV_COEF0;               /* 0x1b704 */
    volatile U_WDHDR_RGB2YUV_COEF1 WDHDR_RGB2YUV_COEF1;               /* 0x1b708 */
    volatile U_WDHDR_RGB2YUV_COEF2 WDHDR_RGB2YUV_COEF2;               /* 0x1b70c */
    volatile U_WDHDR_RGB2YUV_COEF3 WDHDR_RGB2YUV_COEF3;               /* 0x1b710 */
    volatile U_WDHDR_RGB2YUV_COEF4 WDHDR_RGB2YUV_COEF4;               /* 0x1b714 */
    volatile U_WDHDR_RGB2YUV_COEF5 WDHDR_RGB2YUV_COEF5;               /* 0x1b718 */
    volatile U_WDHDR_RGB2YUV_COEF6 WDHDR_RGB2YUV_COEF6;               /* 0x1b71c */
    volatile U_WDHDR_RGB2YUV_COEF7 WDHDR_RGB2YUV_COEF7;               /* 0x1b720 */
    volatile U_WDHDR_RGB2YUV_COEF8 WDHDR_RGB2YUV_COEF8;               /* 0x1b724 */
    volatile U_WDHDR_RGB2YUV_SCALE2P WDHDR_RGB2YUV_SCALE2P;           /* 0x1b728 */
    volatile U_WDHDR_RGB2YUV_IDC0 WDHDR_RGB2YUV_IDC0;                 /* 0x1b72c */
    volatile U_WDHDR_RGB2YUV_IDC1 WDHDR_RGB2YUV_IDC1;                 /* 0x1b730 */
    volatile U_WDHDR_RGB2YUV_IDC2 WDHDR_RGB2YUV_IDC2;                 /* 0x1b734 */
    volatile U_WDHDR_RGB2YUV_ODC0 WDHDR_RGB2YUV_ODC0;                 /* 0x1b738 */
    volatile U_WDHDR_RGB2YUV_ODC1 WDHDR_RGB2YUV_ODC1;                 /* 0x1b73c */
    volatile U_WDHDR_RGB2YUV_ODC2 WDHDR_RGB2YUV_ODC2;                 /* 0x1b740 */
    volatile U_WDHDR_RGB2YUV_MIN WDHDR_RGB2YUV_MIN;                   /* 0x1b744 */
    volatile U_WDHDR_RGB2YUV_MAX WDHDR_RGB2YUV_MAX;                   /* 0x1b748 */
} S_HIPP_REGS_TYPE;

#ifdef __cplusplus
}
#endif /* end of #ifdef __cplusplus */

#endif /* __VOU_REG_H__ */
