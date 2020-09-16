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

#ifndef __VOU_DRV_H__
#define __VOU_DRV_H__

#include "hi_type.h"
#include "hi3516ev200_vo.h"
#include "vou_def.h"
#include "vou_coef.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of #ifdef __cplusplus */

/*
 * yuv(y,u,v)    assemble the y,u,v to 24bit color
 * yuv_y(c)      get Y from 24bit color
 * yuv_u(c)      get U from 24bit color
 * yuv_v(c)      get V from 24bit color
 */
#define yuv(y, u, v) ((((y) & 0x03ff) << 20) | (((u) & 0x03ff) << 10) | ((v) & 0x03ff))
#define yuv_y(c)     (((c) & 0x3ff00000) >> 20)
#define yuv_u(c)     (((c) & 0x000ffc00) >> 10)
#define yuv_v(c)     ((c) & 0x000003ff)

#define GFX_CSC_SCALE    0x8
#define GFX_CSC_CLIP_MIN 0x0
#define GFX_CSC_CLIP_MAX 0x3ff

typedef hi_s32 vo_hal_dev;
typedef hi_s32 vo_hal_layer;
typedef hi_s32 vo_hal_chn;
typedef hi_s32 vo_hal_wbc;
typedef hi_s32 graphic_hal_layer;
typedef hi_u32 vo_intf_type;

typedef enum {
    VO_INT_MODE_FRAME = 0x0,
    VO_INT_MODE_FIELD = 0x1,
    VO_INT_MODE_BUTT
} vo_int_mode;

/* vou mixer prio id */
typedef enum {
    VO_MIX_PRIO0 = 0,
    VO_MIX_PRIO1,
    VO_MIX_PRIO2,
    VO_MIX_PRIO3,
    VO_MIX_PRIO4,
    VO_MIX_PRIO5,
    VO_MIX_PRIO_CLR,
    VO_MIX_BUTT
} vo_mix_prio;

typedef enum {
    /* for video surface interface */
    VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_400 = 0x1,
    VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_420 = 0x2,
    VO_LAYER_PIXERL_FORMAT_SP_Y_CB_CR_422 = 0x3,
    VO_LAYER_PIXERL_FORMAT_BUTT
} vo_layer_pixerl_format;

typedef enum {
    /* for device interface */
    VO_INTF_PIXERL_FORMAT_YCBCR422 = 0x0,
    VO_INTF_PIXERL_FORMAT_YCBCR444 = 0xC,
    VO_INTF_PIXERL_FORMAT_RGB888 = 0xC,
    VO_INTF_PIXERL_FORMAT_BUTT
} vo_intf_pixerl_format;

typedef enum {
    VO_CSC_DEF_VAL = 50,
    VO_CSC_LUMA_MAX = 100,
    VO_CSC_LUMA_MIN = 0,

    VO_CSC_CONT_MAX = 100,
    VO_CSC_CONT_MIN = 0,

    VO_CSC_HUE_MAX = 100,
    VO_CSC_HUE_MIN = 0,

    VO_CSC_SAT_MAX = 100,
    VO_CSC_SAT_MIN = 0,
} vo_csc_range;

typedef struct {
    hi_u32 acm_blk_en;

    hi_u8 u_index;
    hi_u8 v_index;

    hi_s8 u_offset_a;
    hi_s8 u_offset_b;
    hi_s8 u_offset_c;
    hi_s8 u_offset_d;

    hi_s8 v_offset_a;
    hi_s8 v_offset_b;
    hi_s8 v_offset_c;
    hi_s8 v_offset_d;
} vou_acm_blkinfo;

/* vou zoom mode */
typedef enum {
    VO_DISP_ZMEMODE_HORL = 0,
    VO_DISP_ZMEMODE_HORC,
    VO_DISP_ZMEMODE_VERL,
    VO_DISP_ZMEMODE_VERC,

    VO_DISP_ZMEMODE_HOR,
    VO_DISP_ZMEMODE_VER,
    VO_DISP_ZMEMODE_ALPHA,
    VO_DISP_ZMEMODE_ALPHAV,
    VO_DISP_ZMEMODE_VERT,
    VO_DISP_ZMEMODE_VERB,

    VO_DISP_ZMEMODE_ALL,
    VO_DISP_ZMEMODE_NONL,
    VO_DISP_ZMEMODE_BUTT
} vo_disp_zmemode;

typedef struct {
    vou_acm_blkinfo acm_blk[4]; /* 4 acm blk num */
} vou_acm;

typedef enum {
    VOU_HD_HW_DEV = 0,
    VOU_SD_HW_DEV,
    VOU_CAS_DEV,
    VOU_VIRT_DEV,
    VOU_DEV_TYPE_BUTT,
} vou_dev_type;

typedef struct {
    vou_dev_type vo_dev_type;
    hi_bool hd_vpss_rciv;
    hi_bool sd_tde_disp;
    hi_bool support_wbc;
    hi_bool spt_get_screen_frm;
} vou_dev_capability;

typedef enum {
    VOU_SW_LAYER_VHD0 = 0,
    VOU_SW_LAYER_VHD1 = 1,
    VOU_SW_LAYER_VP = 2,
    VOU_SW_LAYER_VSD0 = 3,
    VOU_SW_LAYER_VIRT0 = 4,
    VOU_SW_LAYER_VIRT1 = 5,
    VOU_SW_LAYER_VIRT2 = 6,
    VOU_SW_LAYER_VIRT3 = 7,
    VOU_SW_LAYER_BUTT
} vou_sw_layer;

typedef struct {
    hi_bool synm; /* sync mode(0:timing,as BT.656; 1:signal,as LCD) */
    hi_bool iop;  /* interlaced or progressive display(0:i; 1:p) */
    hi_u8 intfb; /* interlace bit width while output */

    hi_u16 vact; /* vertical active area */
    hi_u16 vbb;  /* vertical back blank porch */
    hi_u16 vfb;  /* vertical front blank porch */

    hi_u16 hact; /* herizontal active area */
    hi_u16 hbb;  /* herizontal back blank porch */
    hi_u16 hfb;  /* herizontal front blank porch */
    hi_u16 hmid; /* bottom herizontal active area */

    hi_u16 bvact; /* bottom vertical active area */
    hi_u16 bvbb;  /* bottom vertical back blank porch */
    hi_u16 bvfb;  /* bottom vertical front blank porch */

    hi_u16 hpw; /* horizontal pulse width */
    hi_u16 vpw; /* vertical pulse width */

    hi_bool idv; /* inverse data valid of output */
    hi_bool ihs; /* inverse horizontal synch signal */
    hi_bool ivs; /* inverse vertical synch signal */
} vo_sync_info;

typedef enum {
    VOU_LAYER_DDR0 = 0,
    VOU_LAYER_DDR1 = 1,
    VOU_LAYER_DDR_BUTT
} vou_layer_ddr;

typedef struct {
    vo_csc_matrix csc_matrix;
    hi_u32 luma;      /* luminance:   0 ~ 100 default: 50 */
    hi_u32 contrast;  /* contrast :   0 ~ 100 default: 50 */
    hi_u32 hue;       /* hue      :   0 ~ 100 default: 50 */
    hi_u32 satuature; /* satuature:   0 ~ 100 default: 50 */
} vo_csc;

typedef struct {
    vo_csc csc;
    hi_u32 gain; /* current gain of VGA signals. [0, 64). default:0x30 */
} vo_vga_param;

typedef struct {
    hi_u32 width;
    hi_u32 height;
} size;

typedef struct {
    hi_u32 bg_color;        /* background color of a device, in RGB format. */
    vo_intf_type intf_type; /* type of a VO interface */
    vo_intf_sync intf_sync; /* type of a VO interface timing */
    vo_sync_info sync_info; /* information about VO interface timings */
} vo_pub_attr;

typedef struct {
    hi_u32 vhdr_en;
    hi_u32 vhdr_ck_gt_en;
    hi_u32 vhdr_degmm_en;
    hi_u32 vhdr_gamut_en;
    hi_u32 vhdr_tmap_en;
    hi_u32 vhdr_gmm_en;
    hi_u32 vhdr_dither_en;
    hi_u32 vhdr_r2y_en;
    hi_u32 vhdr_cadj_en;
    hi_u32 vhdr_gamut_bind;

    hi_u32 vhdr_dither_round_unlim;
    hi_u32 vhdr_dither_round;
    hi_u32 vhdr_dither_domain_mode;
    hi_u32 vhdr_dither_tap_mode;
} vo_hihdr_v_cfg;

typedef struct {
    hi_u32 hihdr_y2r_en;
    hi_u32 hihdr_y2r_ck_gt_en;

    hi_u32 hihdr_v0_y2r_en;
    hi_u32 hihdr_v1_y2r_en;
    hi_u32 hihdr_v0_vhdr_en;
    hi_u32 hihdr_v1_vhdr_en;
    hi_u32 hihdr_v0_cl_en;
    hi_u32 hihdr_v1_cl_en;

    hi_u32 hihdr_v_demo_en;
    hi_u32 hihdr_v_demo_mode;
    hi_u32 hihdr_v_demo_pos;
} vo_csc_v0_cfg;

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 hfir_order;
    hi_u32 lhfir_en;
    hi_u32 chfir_en;
    hi_u32 lhmid_en;
    hi_u32 chmid_en;
    hi_u32 non_lnr_en;
    hi_u32 lhfir_mode;
    hi_u32 chfir_mode;
    hi_u32 hl_shootctrl_en;
    hi_u32 hl_shootctrl_mode;
    hi_u32 hc_shootctrl_en;
    hi_u32 hc_shootctrl_mode;

    hi_u32 in_pro;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u64 in_height;
    hi_u64 out_height;
    hi_u64 in_width;
    hi_u64 out_width;
    hi_u32 graphdet_en;

    hi_u32 lvfir_en;
    hi_u32 cvfir_en;
    hi_u32 lvmid_en;
    hi_u32 cvmid_en;
    hi_u32 vfir_1tap_en;
    hi_u32 lvfir_mode;
    hi_u32 cvfir_mode;
    hi_u32 vl_shootctrl_en;
    hi_u32 vl_shootctrl_mode;
    hi_u32 vc_shootctrl_en;
    hi_u32 vc_shootctrl_mode;
} vo_v0_zme_cfg;

typedef struct {
    hi_u32 vluma_offset;
    hi_u32 vchroma_offset;
    hi_u32 vbluma_offset;
    hi_u32 vbchroma_offset;
    hi_u32 lhfir_offset;
    hi_u32 chfir_offset;
    hi_u32 vl_flatdect_mode;
    hi_u32 vl_coringadj_en;
    hi_u32 vl_gain;
    hi_u32 vl_coring;
    hi_u32 vc_flatdect_mode;
    hi_u32 vc_coringadj_en;
    hi_u32 vc_gain;
    hi_u32 vc_coring;
    hi_u32 hl_flatdect_mode;
    hi_u32 hl_coringadj_en;
    hi_u32 hl_gain;
    hi_u32 hl_coring;
    hi_u32 hc_flatdect_mode;
    hi_u32 hc_coringadj_en;
    hi_u32 hc_gain;
    hi_u32 hc_coring;
} vo_zme_comm_pq_cfg;

typedef struct {
    hi_u32 zme_vprec;
    hi_u32 zme_hprec;
} vo_zme_ds_info;

typedef enum {
    VO_ZME_TYP = 0,
    VO_ZME_TYP1,
    VO_ZME_RAND,
    VO_ZME_MAX,
    VO_ZME_MIN,
    VO_ZME_ZERO,
    VO_ZME_BUTT
} vo_zme_mode;

typedef enum {
    VDP_V0_HFIR_TYP = 0,
    VDP_V0_HFIR_TYP1,
    VDP_V0_HFIR_RAND,
    VDP_V0_HFIR_MAX,
    VDP_V0_HFIR_MIN,
    VDP_V0_HFIR_ZERO,
    VDP_V0_HFIR_BUTT
} vo_v0_hfir_mode;

typedef enum {
    XDP_V0_HFIR_BYPASS = 0,
    XDP_V0_HFIR_COPY,
    XDP_V0_HFIR_BILT,
    XDP_V0_HFIR_FILT,
    XDP_V0_HFIR_BUTT
} xdp_v0_hfir_mode;

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 mid_en;
    xdp_v0_hfir_mode hfir_mode;
} vo_v0_hfir_cfg;

typedef struct {
    hi_u32 vid_iw;
    hi_u32 vid_ih;
    hi_u32 vid_ow;
    hi_u32 vid_oh;

    hi_u32 zme_en;
    hi_u32 hfir_en;
    hi_u32 csc_en;
    hi_u32 hdr_en;

    vo_v0_zme_cfg zme_cfg;
    vo_v0_hfir_cfg hfir_cfg;
    vo_csc_v0_cfg yuv2_rgb_cfg;
    vo_hihdr_v_cfg v_hihdr_cfg;
} vdp_vid_ip_cfg;

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 out_pro;
    hi_u32 out_fmt;
    hi_u64 in_height;
    hi_u64 out_height;
    hi_u64 in_width;
    hi_u64 out_width;
    hi_u32 cvfir_en;
    hi_u32 cvmid_en;
    hi_u32 cvfir_mode;

    hi_u32 hfir_order;
    hi_u32 lhfir_en;
    hi_u32 chfir_en;
    hi_u32 lhmid_en;
    hi_u32 chmid_en;
    hi_u32 non_lnr_en;
    hi_u32 lhfir_mode;
    hi_u32 chfir_mode;
    hi_u32 hl_shootctrl_en;
    hi_u32 hl_shootctrl_mode;
    hi_u32 hc_shootctrl_en;
    hi_u32 hc_shootctrl_mode;

    hi_u32 in_pro;
    hi_u32 graphdet_en;

    hi_u32 lvfir_en;
    hi_u32 lvmid_en;
    hi_u32 vfir_1tap_en;
    hi_u32 lvfir_mode;
    hi_u32 vl_shootctrl_en;
    hi_u32 vl_shootctrl_mode;
    hi_u32 vc_shootctrl_en;
    hi_u32 vc_shootctrl_mode;
} vdp_v1_cvfir_cfg;

typedef enum {
    VDP_V1_HFIR_TYP = 0,
    VDP_V1_HFIR_TYP1,
    VDP_V1_HFIR_RAND,
    VDP_V1_HFIR_MAX,
    VDP_V1_HFIR_MIN,
    VDP_V1_HFIR_ZERO,
    VDP_V1_HFIR_BUTT
} vdp_v1_hfir_mode;

typedef enum {
    XDP_HFIR_BYPASS = 0,
    XDP_HFIR_COPY,
    XDP_HFIR_BILT,
    XDP_HFIR_FILT,
    XDP_HFIR_BUTT
} xdp_hfir_mode;

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 mid_en;
    xdp_hfir_mode hfir_mode;
} vdp_v1_hfir_cfg;

typedef struct {
    hi_u32 csc_en;
    hi_u32 csc_ck_gt_en;
} vdp_csc_v1_cfg;

typedef enum {
    VDP_RMODE_INTERFACE = 0,
    VDP_RMODE_INTERLACE = 0,
    VDP_RMODE_PROGRESSIVE = 1,
    VDP_RMODE_TOP = 2,
    VDP_RMODE_BOTTOM = 3,
    VDP_RMODE_PRO_TOP = 4,
    VDP_RMODE_PRO_BOTTOM = 5,
    VDP_RMODE_BUTT
} vdp_data_rmode;

typedef enum {
    VDP_G0_ZME_TYP = 0,
    VDP_G0_ZME_TYP1,
    VDP_G0_ZME_RAND,
    VDP_G0_ZME_MAX,
    VDP_G0_ZME_MIN,
    VDP_G0_ZME_ZERO,
    VDP_G0_ZME_BUTT
} gf_g0_zme_mode;

typedef enum {
    VDP_G0_ZME_FIR_COPY = 0,
    VDP_G0_ZME_FIR_FILT = 1
} gf_g0_zme_fir_mode;

typedef struct {
    hi_u32 ck_gt_en;
    hi_u32 in_width;
    hi_u32 out_width;
    hi_u32 out_pro;

    hi_u32 hfir_en;
    hi_u32 lhmid_en;
    hi_u32 ahmid_en;
    hi_u32 lhfir_mode;
    hi_u32 ahfir_mode;

    hi_u32 in_height;
    hi_u32 out_height;

    hi_u32 vfir_en;
    hi_u32 lvmid_en;
    hi_u32 avmid_en;
    hi_u32 lvfir_mode;
    hi_u32 avfir_mode;
} gf_g0_zme_cfg;

typedef enum {
    GF_RM_COEF_MODE_TYP = 0x0,
    GF_RM_COEF_MODE_RAN = 0x1,
    GF_RM_COEF_MODE_MIN = 0x2,
    GF_RM_COEF_MODE_MAX = 0x3,
    GF_RM_COEF_MODE_ZRO = 0x4,
    GF_RM_COEF_MODE_CUS = 0x5,
    GF_RM_COEF_MODE_UP = 0x6,
    GF_RM_COEF_MODE_BUTT
} gf_rm_coef_mode;

typedef enum {
    GFX_DCMP_SRC_MODE_ARGB8888 = 0,
    GFX_DCMP_SRC_MODE_ARGB6888,
    GFX_DCMP_SRC_MODE_ARGB1555,
    GFX_DCMP_SRC_MODE_ARGB4444,

    GFX_DCMP_SRC_MODE_BUTT
} gfx_dcmp_src_mode;

typedef enum {
    VDP_DITHER_MODE_TYP = 0,
    VDP_DITHER_MODE_TYP1,
    VDP_DITHER_MODE_RAND,
    VDP_DITHER_MODE_MAX,
    VDP_DITHER_MODE_MIN,
    VDP_DITHER_MODE_ZERO,
    VDP_DITHER_MODE_BUTT
} vdp_dither_mode;

typedef enum {
    DITHER_MODE_10BIT = 0,
    DITHER_MODE_8BIT = 1,
    DITHER_MODE_BUTT
} dither_mode;

typedef enum {
    DITHER_OWIDTH_MODE_5BIT = 0,
    DITHER_OWIDTH_MODE_6BIT = 1,
    DITHER_OWIDTH_MODE_7BIT = 2,
    DITHER_OWIDTH_MODE_8BIT = 3,
    DITHER_OWIDTH_MODE_9BIT = 4,
    DITHER_OWIDTH_MODE_10BIT = 5,
    DITHER_OWIDTH_MODE_BUTT
} dither_owidth_mode;

typedef enum {
    DITHER_IWIDTH_MODE_8BIT = 0,
    DITHER_IWIDTH_MODE_9BIT = 1,
    DITHER_IWIDTH_MODE_10BIT = 2,
    DITHER_IWIDTH_MODE_11BIT = 3,
    DITHER_IWIDTH_MODE_12BIT = 4,
    DITHER_IWIDTH_MODE_BUTT
} dither_iwidth_mode;

typedef enum {
    DITHER_DOMAIN_MODE_SPACE = 0,
    DITHER_DOMAIN_MODE_TIME = 1,
    DITHER_DOMAIN_MODE_BUTT
} dither_domain_mode;

typedef enum {
    DITHER_TAP_MODE_7 = 0,
    DITHER_TAP_MODE_15 = 1,
    DITHER_TAP_MODE_23 = 2,
    DITHER_TAP_MODE_31 = 3,
    DITHER_TAP_MODE_BUTT
} dither_tap_mode;

typedef struct {
    hi_u32 dither_in_bit_width;
    hi_u32 dither_out_bit_width;
} vo_dither_info;

typedef enum {
    DITHER_IO_MODE_12_10 = 1,
    DITHER_IO_MODE_12_8 = 2,
    DITHER_IO_MODE_10_8 = 3,
    DITHER_IO_MODE_10_6 = 4,
    DITHER_IO_MODE_9_6 = 5,
    DITHER_IO_MODE_8_6 = 6,
    DITHER_IO_MODE_10_9_6 = 5,
    DITHER_IO_MODE_10_8_6 = 6,
    DITHER_IO_MODE_BUTT
} vo_dither_io_mode;

typedef struct {
    hi_u32 dither_en;
    hi_u32 dither_mode;
    hi_u32 dither_round;
    hi_u32 dither_round_unlim;
    hi_u32 i_data_width_dither;
    hi_u32 o_data_width_dither;
    hi_u32 dither_domain_mode;
    hi_u32 dither_tap_mode;
    hi_u32 dither_sed_y0;
    hi_u32 dither_sed_u0;
    hi_u32 dither_sed_v0;
    hi_u32 dither_sed_w0;
    hi_u32 dither_sed_y1;
    hi_u32 dither_sed_u1;
    hi_u32 dither_sed_v1;
    hi_u32 dither_sed_w1;
    hi_u32 dither_sed_y2;
    hi_u32 dither_sed_u2;
    hi_u32 dither_sed_v2;
    hi_u32 dither_sed_w2;
    hi_u32 dither_sed_y3;
    hi_u32 dither_sed_u3;
    hi_u32 dither_sed_v3;
    hi_u32 dither_sed_w3;
    hi_u32 dither_thr_max;
    hi_u32 dither_thr_min;
    vo_dither_io_mode dither_io_mode;
} vdp_dither_cfg;

typedef struct {
    hi_u16 bi_size;
    hi_u32 bi_width;
    hi_s32 bi_height;
    hi_u16 bi_planes;
    hi_u16 bi_bit_count;
    hi_u32 bi_compression;
    hi_u32 bi_size_image;
    hi_u32 bi_x_pels_per_meter;
    hi_u32 bi_y_pels_per_meter;
    hi_u32 bi_clr_used;
    hi_u32 bi_clr_important;
} osd_bitmap_info_header;

typedef struct {
    hi_u8 rgb_blue;
    hi_u8 rgb_green;
    hi_u8 rgb_red;
    hi_u8 rgb_reserved;
} osd_rgb_quad;

typedef struct {
    hi_u32 bf_size;
    hi_u16 bf_reserved1;
    hi_u16 bf_reserved2;
    hi_u32 bf_off_bits;
} osd_bitmap_file_header;

typedef struct {
    osd_bitmap_info_header bmi_header;
    osd_rgb_quad bmi_colors[1];
} osd_bitmap_info;

typedef struct {
    hi_u32 width;       /* out */
    hi_u32 height;      /* out */
    hi_u32 stride;      /* in */
    hi_phys_addr_t rgb_buffer; /* in */
} osd_logo_t;

typedef enum {
    OSD_BI_BIT_COUNT_1BPP = 1,
    OSD_BI_BIT_COUNT_4BPP = 4,
    OSD_BI_BIT_COUNT_8BPP = 8,
    OSD_BI_BIT_COUNT_16BPP = 16,
    OSD_BI_BIT_COUNT_24BPP = 24,
    OSD_BI_BIT_COUNT_32BPP = 32,
} osd_bi_bit_count;

hi_void vo_drv_board_init(hi_void);
hi_void vo_drv_int_reg_up_mode(vo_hal_layer vo_layer, vo_int_mode int_mode);
hi_void vo_drv_set_dev_intf_type(vo_hal_dev vo_dev, vo_intf_type intf_type);
hi_void vo_drv_set_dev_bk_grd(vo_hal_dev vo_dev, hi_u32 bg_color);
hi_void vo_drv_set_dev_out_sync(vo_hal_dev vo_dev, vo_intf_sync vo_out_mode);

hi_void vo_drv_dev_int_enable(vo_hal_dev vo_dev, hi_bool enable);
hi_void vo_drv_int_set_mode(vo_hal_dev vo_dev, vo_int_mode int_mode);

hi_void vo_drv_layer_enable(vo_hal_layer vo_layer, hi_bool enable);

hi_void vo_drv_set_all_crg_clk(hi_bool clk_en);
hi_u32 vo_drv_get_dev_intf_type(vo_hal_dev vo_dev);
hi_void vo_drv_open(vo_hal_dev vo_dev);
hi_void vo_drv_close(vo_hal_dev vo_dev);
hi_void vo_drv_default_setting(hi_void);

hi_void vo_drv_set_dev_clk(vo_hal_dev vo_dev);
hi_void vo_vid_set_zme_enable(hi_u32 layer, const vdp_vid_ip_cfg *vid_cfg);

hi_s32 graphic_drv_set_csc_coef(hal_disp_layer gfx_layer, const vo_csc *gfx_csc, const csc_coef_param *coef_param);
hi_s32 vo_drv_video_set_csc_coef(vo_hal_layer vo_layer, vo_csc_matrix csc_matrix);
hi_s32 load_bmp(hi_phys_addr_t bmp_addr, osd_logo_t *video_logo);

hi_void vo_drv_def_layer_bind_dev(hi_void);

#ifdef __cplusplus
}
#endif /* end of #ifdef __cplusplus */

#endif /* end of __VOU_DRV_H__ */

