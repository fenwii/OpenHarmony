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

#ifndef __HDMI_REG_TX_H__
#define __HDMI_REG_TX_H__

#include "hi_type.h"

typedef union {
    struct {
        unsigned int avi_pkt_hb0 : 8; /* [7:0] */
        unsigned int avi_pkt_hb1 : 8; /* [15:8] */
        unsigned int avi_pkt_hb2 : 8; /* [23:16] */
        unsigned int rsv_6       : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_pkt_header;

typedef union {
    struct {
        unsigned int avi_sub_pkt0_pb0 : 8; /* [7:0] */
        unsigned int avi_sub_pkt0_pb1 : 8; /* [15:8] */
        unsigned int avi_sub_pkt0_pb2 : 8; /* [23:16] */
        unsigned int avi_sub_pkt0_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt0_l;

typedef union {
    struct {
        unsigned int avi_sub_pkt0_pb4 : 8; /* [7:0] */
        unsigned int avi_sub_pkt0_pb5 : 8; /* [15:8] */
        unsigned int avi_sub_pkt0_pb6 : 8; /* [23:16] */
        unsigned int rsv_7            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt0_h;

typedef union {
    struct {
        unsigned int avi_sub_pkt1_pb0 : 8; /* [7:0] */
        unsigned int avi_sub_pkt1_pb1 : 8; /* [15:8] */
        unsigned int avi_sub_pkt1_pb2 : 8; /* [23:16] */
        unsigned int avi_sub_pkt1_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt1_l;

typedef union {
    struct {
        unsigned int avi_sub_pkt1_pb4 : 8; /* [7:0] */
        unsigned int avi_sub_pkt1_pb5 : 8; /* [15:8] */
        unsigned int avi_sub_pkt1_pb6 : 8; /* [23:16] */
        unsigned int rsv_8            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt1_h;

typedef union {
    struct {
        unsigned int avi_sub_pkt2_pb0 : 8; /* [7:0] */
        unsigned int avi_sub_pkt2_pb1 : 8; /* [15:8] */
        unsigned int avi_sub_pkt2_pb2 : 8; /* [23:16] */
        unsigned int avi_sub_pkt2_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt2_l;

typedef union {
    struct {
        unsigned int avi_sub_pkt2_pb4 : 8; /* [7:0] */
        unsigned int avi_sub_pkt2_pb5 : 8; /* [15:8] */
        unsigned int avi_sub_pkt2_pb6 : 8; /* [23:16] */
        unsigned int rsv_9            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt2_h;

typedef union {
    struct {
        unsigned int avi_sub_pkt3_pb0 : 8; /* [7:0] */
        unsigned int avi_sub_pkt3_pb1 : 8; /* [15:8] */
        unsigned int avi_sub_pkt3_pb2 : 8; /* [23:16] */
        unsigned int avi_sub_pkt3_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt3_l;

typedef union {
    struct {
        unsigned int avi_sub_pkt3_pb4 : 8; /* [7:0] */
        unsigned int avi_sub_pkt3_pb5 : 8; /* [15:8] */
        unsigned int avi_sub_pkt3_pb6 : 8; /* [23:16] */
        unsigned int rsv_10           : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} avi_sub_pkt3_h;

typedef union {
    struct {
        unsigned int vsif_pkt_hb0 : 8; /* [7:0] */
        unsigned int vsif_pkt_hb1 : 8; /* [15:8] */
        unsigned int vsif_pkt_hb2 : 8; /* [23:16] */
        unsigned int rsv_56       : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_pkt_header;

typedef union {
    struct {
        unsigned int vsif_sub_pkt0_pb0 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt0_pb1 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt0_pb2 : 8; /* [23:16] */
        unsigned int vsif_sub_pkt0_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt0_l;

typedef union {
    struct {
        unsigned int vsif_sub_pkt0_pb4 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt0_pb5 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt0_pb6 : 8; /* [23:16] */
        unsigned int rsv_57            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt0_h;

typedef union {
    struct {
        unsigned int vsif_sub_pkt1_pb0 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt1_pb1 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt1_pb2 : 8; /* [23:16] */
        unsigned int vsif_sub_pkt1_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt1_l;

typedef union {
    struct {
        unsigned int vsif_sub_pkt1_pb4 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt1_pb5 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt1_pb6 : 8; /* [23:16] */
        unsigned int rsv_58            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt1_h;

typedef union {
    struct {
        unsigned int vsif_sub_pkt2_pb0 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt2_pb1 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt2_pb2 : 8; /* [23:16] */
        unsigned int vsif_sub_pkt2_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt2_l;

typedef union {
    struct {
        unsigned int vsif_sub_pkt2_pb4 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt2_pb5 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt2_pb6 : 8; /* [23:16] */
        unsigned int rsv_59            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt2_h;

typedef union {
    struct {
        unsigned int vsif_sub_pkt3_pb0 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt3_pb1 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt3_pb2 : 8; /* [23:16] */
        unsigned int vsif_sub_pkt3_pb3 : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt3_l;

typedef union {
    struct {
        unsigned int vsif_sub_pkt3_pb4 : 8; /* [7:0] */
        unsigned int vsif_sub_pkt3_pb5 : 8; /* [15:8] */
        unsigned int vsif_sub_pkt3_pb6 : 8; /* [23:16] */
        unsigned int rsv_60            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} vsif_sub_pkt3_h;

typedef union {
    struct {
        unsigned int cea_avi_en     : 1;  /* [0] */
        unsigned int cea_avi_rpt_en : 1;  /* [1] */
        unsigned int rsv_61         : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} cea_avi_cfg;

typedef union {
    struct {
        unsigned int cea_gen_en     : 1;  /* [0] */
        unsigned int cea_gen_rpt_en : 1;  /* [1] */
        unsigned int rsv_65         : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} cea_gen_cfg;

typedef union {
    struct {
        unsigned int cea_cp_en      : 1;  /* [0] */
        unsigned int cea_cp_rpt_en  : 1;  /* [1] */
        unsigned int cea_cp_rpt_cnt : 8;  /* [2:7] */
        unsigned int rsv_66         : 22; /* [31:8] */
    } bits;
    unsigned int u32;
} cea_cp_cfg;

typedef union {
    struct {
        unsigned int cea_vsif_en     : 1;  /* [0] */
        unsigned int cea_vsif_rpt_en : 1;  /* [1] */
        unsigned int rsv_72          : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} cea_vsif_cfg;

typedef union {
    struct {
        unsigned int hdmi_mode           : 1;  /* [0] */
        unsigned int dc_pkt_en           : 1;  /* [1] */
        unsigned int null_pkt_en         : 1;  /* [2] */
        unsigned int null_pkt_en_vs_high : 1;  /* [3] */
        unsigned int intr_encryption     : 1;  /* [4] */
        unsigned int pb_ovr_dc_pkt_en    : 1;  /* [5] */
        unsigned int pb_priotity_ctl     : 1;  /* [6] */
        unsigned int pkt_bypass_mode     : 1;  /* [7] */
        unsigned int rsv_74              : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} avmixer_config;

typedef union {
    struct {
        unsigned int cp_set_avmute : 1;  /* [0] */
        unsigned int cp_clr_avmute : 1;  /* [1] */
        unsigned int rsv_75        : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} cp_pkt_avmute;

typedef union {
    struct {
        unsigned int enc_hdmi2_on   : 1;  /* [0] */
        unsigned int enc_scr_on     : 1;  /* [1] */
        unsigned int enc_scr_md     : 1;  /* [2] */
        unsigned int enc_hdmi_val   : 1;  /* [3] */
        unsigned int enc_hdmi_ovr   : 1;  /* [4] */
        unsigned int enc_bypass     : 1;  /* [5] */
        unsigned int enc_ck_div_sel : 2;  /* [7:6] */
        unsigned int rsv_78         : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} hdmi_enc_ctrl;

typedef union {
    struct {
        unsigned int htotal_hw : 15; /* [14:0] */
        unsigned int rsv_0     : 17; /* [31:15] */
    } bits;
    unsigned int u32;
} htotal_hw;

typedef union {
    struct {
        unsigned int ctl_type_config : 2;  /* [1:0] */
        unsigned int rsv_80          : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} ctl_type_config;

typedef struct {
    unsigned int             reserved_0[6];      /* 1800 - 1814 */
    volatile avi_pkt_header  avi_packet_header;  /* 1818 */
    volatile avi_sub_pkt0_l  avi_pck0_l;         /* 181C */
    volatile avi_sub_pkt0_h  avi_pck0_h;         /* 1820 */
    volatile avi_sub_pkt1_l  avi_pck1_l;         /* 1824 */
    volatile avi_sub_pkt1_h  avi_pck1_h;         /* 1828 */
    volatile avi_sub_pkt2_l  avi_pck2_l;         /* 182C */
    volatile avi_sub_pkt2_h  avi_pck2_h;         /* 1830 */
    volatile avi_sub_pkt3_l  avi_pck3_l;         /* 1834 */
    volatile avi_sub_pkt3_h  avi_pck3_h;         /* 1838 */
    unsigned int             reserved_1[81];     /* 183C - 197C */
    volatile vsif_pkt_header vsif_packet_header; /* 1980 */
    volatile vsif_sub_pkt0_l vsif_pck0_l;        /* 1984 */
    volatile vsif_sub_pkt0_h vsif_pck0_h;        /* 1988 */
    volatile vsif_sub_pkt1_l vsif_pck1_l;        /* 198C */
    volatile vsif_sub_pkt1_h vsif_pck1_h;        /* 1990 */
    volatile vsif_sub_pkt2_l vsif_pck2_l;        /* 1994 */
    volatile vsif_sub_pkt2_h vsif_pck2_h;        /* 1998 */
    volatile vsif_sub_pkt3_l vsif_pck3_l;        /* 199C */
    volatile vsif_sub_pkt3_h vsif_pck3_h;        /* 19A0 */
    volatile cea_avi_cfg     avi_cfg    ;        /* 19A4 */
    unsigned int             reserved_3[3];      /* 19A8 - 19B0 */
    volatile cea_gen_cfg     gen_cfg;            /* 19B4 */
    volatile cea_cp_cfg      cp_cfg;             /* 19B8 */
    unsigned int             reserved_4[5];      /* 19BC - 19CC */
    volatile cea_vsif_cfg    vsif_cfg;           /* 19D0 */
    unsigned int             reserved_5[13];     /* 19D4 - 1A04 */
    volatile avmixer_config  avmixer_cfg;        /* 1A08 */
    volatile cp_pkt_avmute   cp_avmute;          /* 1A0C */
    unsigned int             reserved_6[20];     /* 1A10 - 1A5C */
    volatile hdmi_enc_ctrl   enc_ctrl;           /* 1A60 */
    unsigned int             reserved_7[55];     /* 1A64 - 1B3C */
    volatile htotal_hw       htotal;             /* 1B40 */
    unsigned int             reserved_8;         /* 1B44 */
    volatile ctl_type_config ctl_type_cfg;       /* 1B48 */
} tx_hdmi_regs;

int hdmi_tx_reg_type_init(void);
hi_void hdmi_tx_reg_type_deinit(void);
int hdmi_avi_pkt_header_hb_set(unsigned int hb0, unsigned int hb1, unsigned int hb2);
int hdmi_avi_sub_pkt0_l_pb_set(unsigned int avi_pkt0_pb0, unsigned int avi_pkt0_pb1, unsigned int avi_pkt0_pb2,
    unsigned int avi_pkt0_pb3);
int hdmi_avi_sub_pkt0_h_pb_set(unsigned int avi_pkt0_pb4, unsigned int avi_pkt0_pb5, unsigned int avi_pkt0_pb6);
int hdmi_avi_sub_pkt1_l_pb_set(unsigned int avi_pkt1_pb0, unsigned int avi_pkt1_pb1, unsigned int avi_pkt1_pb2,
    unsigned int avi_pkt1_pb3);
int hdmi_avi_sub_pkt1_h_pb_set(unsigned int avi_pkt1_pb4, unsigned int avi_pkt1_pb5, unsigned int avi_pkt1_pb6);
int hdmi_avi_sub_pkt2_l_pb_set(unsigned int avi_pkt2_pb0, unsigned int avi_pkt2_pb1, unsigned int avi_pkt2_pb2,
    unsigned int avi_pkt2_pb3);
int hdmi_avi_sub_pkt2_h_pb_set(unsigned int avi_pkt2_pb4, unsigned int avi_pkt2_pb5, unsigned int avi_pkt2_pb6);
int hdmi_avi_sub_pkt3_l_pb_set(unsigned int avi_pkt3_pb0, unsigned int avi_pkt3_pb1, unsigned int avi_pkt3_pb2,
    unsigned int avi_pkt3_pb3);
int hdmi_avi_sub_pkt3_h_pb_set(unsigned int avi_pkt3_pb4, unsigned int avi_pkt3_pb5, unsigned int avi_pkt3_pb6);
int hdmi_vsif_pkt_header_hb_set(unsigned int hb0, unsigned int hb1, unsigned int hb2);
int hdmi_vsif_sub_pkt0_l_pb_set(unsigned int vsif_pkt0_pb0, unsigned int vsif_pkt0_pb1, unsigned int vsif_pkt0_pb2,
    unsigned int vsif_pkt0_pb3);
int hdmi_vsif_sub_pkt0_h_pb_set(unsigned int vsif_pkt0_pb4, unsigned int vsif_pkt0_pb5, unsigned int vsif_pkt0_pb6);
int hdmi_vsif_sub_pkt1_l_pb_set(unsigned int vsif_pkt1_pb0, unsigned int vsif_pkt1_pb1, unsigned int vsif_pkt1_pb2,
    unsigned int vsif_pkt1_pb3);
int hdmi_vsif_sub_pkt1_h_pb_set(unsigned int vsif_pkt1_pb4, unsigned int vsif_pkt1_pb5, unsigned int vsif_pkt1_pb6);
int hdmi_vsif_sub_pkt2_l_pb_set(unsigned int vsif_pkt2_pb0, unsigned int vsif_pkt2_pb1, unsigned int vsif_pkt2_pb2,
    unsigned int vsif_pkt2_pb3);
int hdmi_vsif_sub_pkt2_h_pb_set(unsigned int vsif_pkt2_pb4, unsigned int vsif_pkt2_pb5, unsigned int vsif_pkt2_pb6);
int hdmi_vsif_sub_pkt3_l_pb_set(unsigned int vsif_pkt3_pb0, unsigned int vsif_pkt3_pb1, unsigned int vsif_pkt3_pb2,
    unsigned int vsif_pkt3_pb3);
int hdmi_vsif_sub_pkt3_h_pb_set(unsigned int vsif_pkt3_pb4, unsigned int vsif_pkt3_pb5, unsigned int vsif_pkt3_pb6);
int hdmi_cea_avi_en_set(unsigned int cea_avi_en);
int hdmi_cea_avi_rpt_en_set(unsigned int cea_avi_rpt_en);
int hdmi_cea_gen_en_set(unsigned int cea_gen_en);
int hdmi_cea_cp_en_set(unsigned int cea_cp_en);
int hdmi_cea_cp_rpt_cnt_set(unsigned int cea_cp_rpt_cnt);
int hdmi_cea_cp_rpt_en_set(unsigned int cea_cp_rpt_en);
int hdmi_cea_vsif_en_set(unsigned int cea_vsif_en);
int hdmi_cea_vsif_rpt_en_set(unsigned int cea_vsif_rpt_en);
int hdmi_avmixer_config_hdmi_mode_set(unsigned int hdmi_mode);
int hdmi_avmixer_config_dc_pkt_en_set(unsigned int dc_pkt_en);
int hdmi_avmixer_config_null_pkt_en_set(unsigned int null_pkt_en);
int hdmi_cp_set_avmute_set(unsigned int cp_set_avmute);
int hdmi_cp_clr_avmute_set(unsigned int cp_clr_avmute);
int hdmi_enc_hdmi2_on_set(unsigned int enc_hdmi2_on);
int hdmi_enc_scr_on_set(unsigned int enc_scr_on);
int hdmi_enc_bypass_set(unsigned int enc_bypass);
int hdmi_ctl_type_config_set(unsigned int ctl_config);
int hdmi_cea_avi_en_get(hi_void);
int hdmi_cea_cp_rpt_en_get(hi_void);
int hdmi_avmixer_config_hdmi_mode_get(hi_void);
int hdmi_cp_set_avmute_get(hi_void);
int hdmi_enc_scr_on_get(hi_void);
int hdmi_htotal_hw_get(hi_void);

#endif /* __HDMI_REG_TX_H__ */

