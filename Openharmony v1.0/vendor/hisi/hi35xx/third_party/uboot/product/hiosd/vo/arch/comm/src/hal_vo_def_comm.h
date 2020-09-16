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

#ifndef __HAL_VO_COMM_DEF_H__
#define __HAL_VO_COMM_DEF_H__

#include "hi_type.h"
#include "hi_defines.h"
#include "hi_inner_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

typedef enum {
    HAL_INPUTFMT_YCBCR_SEMIPLANAR_400 = 0x1,
    HAL_INPUTFMT_YCBCR_SEMIPLANAR_420 = 0x2,
    HAL_INPUTFMT_YCBCR_SEMIPLANAR_422 = 0x3,
    HAL_INPUTFMT_YCBCR_SEMIPLANAR_444 = 0x4,
    HAL_INPUTFMT_YCBCR_SEMIPLANAR_411_4X1 = 0x6,
    HAL_INPUTFMT_YCBCR_SEMIPLANAR_422_2X1 = 0x7,

    HAL_INPUTFMT_CBYCRY_PACKAGE_422 = 0x9,
    HAL_INPUTFMT_YCBYCR_PACKAGE_422 = 0xa,
    HAL_INPUTFMT_YCRYCB_PACKAGE_422 = 0xb,
    HAL_INPUTFMT_YCBCR_PACKAGE_444 = 0x1000,

    HAL_INPUTFMT_CLUT_1BPP = 0x00,
    HAL_INPUTFMT_CLUT_2BPP = 0x10,
    HAL_INPUTFMT_CLUT_4BPP = 0x20,
    HAL_INPUTFMT_CLUT_8BPP = 0x30,
    HAL_INPUTFMT_ACLUT_44 = 0x38,

    HAL_INPUTFMT_RGB_444 = 0x40,
    HAL_INPUTFMT_RGB_555 = 0x41,
    HAL_INPUTFMT_RGB_565 = 0x42,
    HAL_INPUTFMT_CBYCRY_PACKAGE_422_GRC = 0x43,
    HAL_INPUTFMT_YCBYCR_PACKAGE_422_GRC = 0x44,
    HAL_INPUTFMT_YCRYCB_PACKAGE_422_GRC = 0x45,
    HAL_INPUTFMT_ACLUT_88 = 0x46,
    HAL_INPUTFMT_ARGB_4444 = 0x48,
    HAL_INPUTFMT_ARGB_1555 = 0x49,

    HAL_INPUTFMT_RGB_888 = 0x50,
    HAL_INPUTFMT_YCBCR_888 = 0x51,
    HAL_INPUTFMT_ARGB_8565 = 0x5a,
    HAL_INPUTFMT_ARGB_6666 = 0x5b,

    HAL_INPUTFMT_KRGB_888 = 0x60,
    HAL_INPUTFMT_ARGB_8888 = 0x68,
    HAL_INPUTFMT_AYCBCR_8888 = 0x69,

    HAL_INPUTFMT_RGBA_4444 = 0xc8,
    HAL_INPUTFMT_RGBA_5551 = 0xc9,

    HAL_INPUTFMT_RGBA_6666 = 0xd8,
    HAL_INPUTFMT_RGBA_5658 = 0xda,

    HAL_INPUTFMT_RGBA_8888 = 0xe8,
    HAL_INPUTFMT_YCBCRA_8888 = 0xe9,

    HAL_DISP_PIXELFORMAT_BUTT
} hal_disp_pixel_format;

typedef enum {
    HAL_DISP_ZME_OUTFMT420 = 0,
    HAL_DISP_ZME_OUTFMT422,
    HAL_DISP_ZME_OUTFMT444,
    HAL_DISP_ZME_OUTFMT_BUTT
} hal_disp_zme_outfmt;

/* vou CBM MIXER */
typedef enum {
    HAL_CBMMIX1 = 0,
    HAL_CBMMIX2 = 1,
    HAL_CBMMIX3 = 2,

    HAL_CBMMIX1_BUTT
} hal_cbmmix;

typedef enum {
    HAL_HFIRMODE_MEDEN = 0,  /* median filtering enable */
    HAL_HFIRMODE_COPY,  /* chroma HFIR copy */
    HAL_HFIRMODE_DOUBLE,  /* bilinear interpolation */
    HAL_HFIRMODE_6TAPFIR,  /* 6 order FIR */

    HAL_HFIRMODE_BUTT
} hal_hfirmode;

typedef struct {
    hi_u32 syncm;
    hi_u32 iop;
    hi_u8 intfb;

    hi_u16 vact;
    hi_u16 vbb;
    hi_u16 vfb;

    hi_u16 hact;
    hi_u16 hbb;
    hi_u16 hfb;
    hi_u16 hmid;

    hi_u16 bvact;
    hi_u16 bvbb;
    hi_u16 bvfb;

    hi_u16 hpw;
    hi_u16 vpw;

    hi_u32 idv;
    hi_u32 ihs;
    hi_u32 ivs;
} hal_disp_syncinfo;

typedef struct {
    hi_u32 f_inv;
    hi_u32 vs_inv;
    hi_u32 hs_inv;
    hi_u32 dv_inv;
} hal_disp_syncinv;

typedef enum {
    HAL_MULTICHN_EN_1P1C = 0x1,  /* 1 pixel / 1 cycle */
    HAL_MULTICHN_EN_2P1C = 0x2,  /* 2 pixel / 1 cycle */
} hal_multichn_en;

typedef struct {
    hi_u16 bkg_a;
    hi_u16 bkg_y;
    hi_u16 bkg_cb;
    hi_u16 bkg_cr;
} hal_disp_bkcolor;

typedef struct {
    hi_u16 clip_low_y;
    hi_u16 clip_low_cb;
    hi_u16 clip_low_cr;

    hi_u16 clip_high_y;
    hi_u16 clip_high_cb;
    hi_u16 clip_high_cr;
} hal_disp_clip;

typedef enum {
    VDP_LAYER_VID0 = 0,
    VDP_LAYER_VID1 = 1,
    VDP_LAYER_VID2 = 2,
    VDP_LAYER_VID3 = 3,
    VDP_LAYER_VID4 = 4,
    VDP_LAYER_VID5 = 5,
    VDP_LAYER_VID6 = 6,  /* for FI pixel */
    VDP_LAYER_VID7 = 7,  /* for FI info */

    VDP_LAYER_VID_BUTT
} vdp_layer_vid;

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
    VDP_PROC_FMT_SP_420 = 0x0,
    VDP_PROC_FMT_SP_422 = 0x1,
    VDP_PROC_FMT_SP_444 = 0x2,  /* plannar,in YUV color domain */
    VDP_PROC_FMT_RGB_888 = 0x3,  /* package,in RGB color domain */
    VDP_PROC_FMT_RGB_444 = 0x4,  /* plannar,in RGB color domain */

    VDP_PROC_FMT_BUTT
} vdp_proc_fmt;

typedef struct {
    hi_s32 luma;
    hi_s32 cont;
    hi_s32 hue;
    hi_s32 satu;
} hal_csc_value;
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
#endif /* end of __HAL_VO_COMM_DEF_H__ */
