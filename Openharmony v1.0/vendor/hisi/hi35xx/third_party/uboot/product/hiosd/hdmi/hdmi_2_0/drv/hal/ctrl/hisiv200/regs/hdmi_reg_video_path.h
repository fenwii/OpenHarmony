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

#ifndef __HDMI_REG_VIDEO_PATH_H__
#define __HDMI_REG_VIDEO_PATH_H__

#include "hi_type.h"

typedef union {
    struct {
        unsigned int dither_rnd_byp      : 1;  /* [0] */
        unsigned int dither_mode         : 2;  /* [2:1] */
        unsigned int dither_rnd_en       : 1;  /* [3] */
        unsigned int dither_spatial_en   : 1;  /* [4] */
        unsigned int dither_spatial_dual : 1;  /* [5] */
        unsigned int rsv_31              : 26; /* [31:6] */
    } bits;
    unsigned int u32;
} dither_config;

typedef union {
    struct {
        unsigned int reg_csc_en          : 1;  /* [0] */
        unsigned int reg_csc_coef_ext    : 1;  /* [1] */
        unsigned int reg_csc_dither_en   : 1;  /* [2] */
        unsigned int reg_csc_saturate_en : 1;  /* [3] */
        unsigned int reg_csc_mode        : 8;  /* [11:4] */
        unsigned int rsv_41              : 20; /* [31:12] */
    } bits;
    unsigned int u32;
} multi_csc_ctrl;

typedef union {
    struct {
        unsigned int reg_dwsm_hori_en   : 1;  /* [0] */
        unsigned int reg_hori_filter_en : 1;  /* [1] */
        unsigned int reg_dwsm_vert_en   : 1;  /* [2] */
        unsigned int reg_vert_cbcr_sel  : 1;  /* [3] */
        unsigned int rsv_57             : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} video_dwsm_ctrl;

typedef union {
    struct {
        unsigned int reg_demux_420_en     : 1;  /* [0] */
        unsigned int reg_ddr_en           : 1;  /* [1] */
        unsigned int reg_yc_mux_en        : 1;  /* [2] */
        unsigned int reg_blank_replace_en : 1;  /* [3] */
        unsigned int reg_pixel_rate       : 2;  /* [5:4] */
        unsigned int reg_ddr_polarity     : 1;  /* [6] */
        unsigned int reg_yc_mux_polarity  : 1;  /* [7] */
        unsigned int reg_cbcr_order       : 1;  /* [8] */
        unsigned int reg_demux_cb_or_cr   : 1;  /* [9] */
        unsigned int reg_pxl_div_en       : 1;  /* [10] */
        unsigned int rsv_58               : 21; /* [31:11] */
    } bits;
    unsigned int u32;
} data_align_ctrl;

typedef union {
    struct {
        unsigned int reg_vmux_y_sel  : 3; /* [2:0] */
        unsigned int reg_vmux_cb_sel : 3; /* [5:3] */
        unsigned int reg_vmux_cr_sel : 3; /* [8:6] */
        unsigned int reg_bitmask_y   : 2; /* [10:9] */
        unsigned int reg_bitmask_cb  : 2; /* [12:11] */
        unsigned int reg_bitmask_cr  : 2; /* [14:13] */
        unsigned int reg_bitrev_en   : 3; /* [17:15] */
        unsigned int reg_datamask_en : 3; /* [20:18] */
        unsigned int reg_syncmask_en : 4; /* [24:21] */
        unsigned int reg_inver_sync  : 4; /* [28:25] */
        unsigned int rsv_62          : 3; /* [31:29] */
    } bits;
    unsigned int u32;
} video_dmux_ctrl;

typedef union {
    struct {
        unsigned int tmds_pack_mode       : 2;  /* [1:0] */
        unsigned int reg_fifo_auto_rst_en : 1;  /* [2] */
        unsigned int reg_fifo_manu_rst    : 1;  /* [3] */
        unsigned int reg_clock_det_en     : 1;  /* [4] */
        unsigned int reg_ext_tmds_para    : 1;  /* [5] */
        unsigned int reg_tmds_delay_sel   : 1;  /* [6] */
        unsigned int rsv_0                : 1;  /* [7] */
        unsigned int reg_fifo_delay_cnt   : 8;  /* [15..8] */
        unsigned int rsv_63               : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} tx_pack_fifo_ctrl;

typedef union {
    struct {
        unsigned int pclk2tclk_stable  : 1;  /* [0] */
        unsigned int tmds_fifo_rerror  : 1;  /* [1] */
        unsigned int tmds_fifo_raempty : 1;  /* [2] */
        unsigned int tmds_fifo_rempty  : 1;  /* [3] */
        unsigned int tmds_fifo_werror  : 1;  /* [4] */
        unsigned int tmds_fifo_wafull  : 1;  /* [5] */
        unsigned int tmds_fifo_wfull   : 1;  /* [6] */
        unsigned int rsv_64            : 25; /* [31:7] */
    } bits;
    unsigned int u32;
} tx_pack_fifo_st;

typedef union {
    struct {
        unsigned int reg_tcnt_lower_threshold : 18; /* [17:0] */
        unsigned int rsv_66                   : 14; /* [31:18] */
    } bits;
    unsigned int u32;
} tclk_lower_threshold;

typedef union {
    struct {
        unsigned int reg_tcnt_upper_threshold : 18; /* [17:0] */
        unsigned int rsv_66                   : 14; /* [31:18] */
    } bits;
    unsigned int u32;
} tclk_upper_threshold;

typedef struct {
    volatile dither_config        dither ;         /* 8EC */
    unsigned int                  reserved_1[17];  /* 8F0-930 */
    volatile multi_csc_ctrl       multi_csc;       /* 934 */
    unsigned int                  reserved_2[18];  /* 938-97c */
    volatile video_dwsm_ctrl      dwsm_ctrl;       /* 980 */
    unsigned int                  reserved_3[2];   /* 984-988 */
    volatile data_align_ctrl      data_align;      /* 98C */
    unsigned int                  reserved_4[6];   /* 990-9A4 */
    volatile video_dmux_ctrl      dmux_ctrl;       /* 9A8 */
    volatile video_dmux_ctrl      reserved_5[21];  /* 9AC-9FC */
    volatile tx_pack_fifo_ctrl    tx_fifo_ctrl;    /* A00 */
    volatile tx_pack_fifo_st      tx_fifo_st;      /* A04 */
    unsigned int                  reserved_6;      /* A08 */
    volatile tclk_lower_threshold lower_threshold; /* A0c */
    volatile tclk_upper_threshold upper_threshold; /* A10 */
} video_path_reg_type;

int hdmi_tx_videopath_reg_type_init(void);
hi_void hdmi_tx_videopath_reg_type_deinit(void);
int hdmi_dither_config_rnd_byp_set(unsigned int dither_rnd_byp);
int hdmi_dither_config_mode_set(unsigned int dither_mode);
int hdmi_multi_csc_ctrl_reg_csc_en_set(unsigned int reg_csc_en);
int hdmi_multi_csc_ctrl_reg_csc_saturate_en_set(unsigned int reg_csc_saturate_en);
int hdmi_multi_csc_ctrl_reg_csc_mode_set(unsigned int reg_csc_mode);
int hdmi_multi_csc_ctrl_reg_csc_mode_get(hi_void);
int hdmi_video_dwsm_ctrl_reg_dwsm_hori_en_set(unsigned int reg_dwsm_hori_en);
int hdmi_video_dwsm_ctrl_reg_hori_filter_en_set(unsigned int reg_hori_filter_en);
int hdmi_video_dwsm_ctrl_reg_dwsm_vert_en_set(unsigned int reg_dwsm_vert_en);
int hdmi_data_align_ctrl_reg_demux_420_en_set(unsigned int reg_demux_420_en);
int hdmi_data_align_ctrl_reg_vert_cbcr_sel_set(unsigned int reg_vert_cbcr_sel);
int hdmi_data_align_ctrl_reg_pxl_div_en_set(unsigned int reg_pxl_div_en);
int hdmi_video_dmux_ctrl_reg_vmux_y_sel_set(unsigned int reg_vmux_y_sel);
int hdmi_video_dmux_ctrl_reg_vmux_cb_sel_set(unsigned int reg_vmux_cb_sel);
int hdmi_video_dmux_ctrl_reg_vmux_cr_sel_set(unsigned int reg_vmux_cr_sel);
int hdmi_video_dmux_ctrl_reg_syncmask_en_set(unsigned int reg_syncmask_en);
int hdmi_video_dmux_ctrl_reg_inver_sync_set(unsigned int reg_inver_sync);
int hdmi_tx_pack_fifo_ctrl_reg_fifo_manu_rst_set(unsigned int reg_fifo_manu_rst);
int hdmi_tx_pack_fifo_ctrl_tmds_pack_mode_set(unsigned int tmds_pack_mode);
int hdmi_tx_pack_fifo_ctrl_tmds_pack_mode_get(hi_void);
int hdmi_tx_pack_fifo_ctrl_reg_fifo_auto_rst_en_set(unsigned int reg_fifo_auto_rst_en);

#endif /* __HDMI_REG_VIDEO_PATH_H__ */

