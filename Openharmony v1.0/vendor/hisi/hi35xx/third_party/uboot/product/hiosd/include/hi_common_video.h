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

#ifndef __HI_COMMON_VIDEO_H__
#define __HI_COMMON_VIDEO_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef enum  {
    HI_OP_MODE_AUTO   = 0,
    HI_OP_MODE_MANUAL = 1,
    HI_OP_MODE_BUTT
} hi_op_mode;

typedef enum  {
    HI_VB_SRC_COMMON  = 0,
    HI_VB_SRC_MOD  = 1,
    HI_VB_SRC_PRIVATE = 2,
    HI_VB_SRC_USER    = 3,
    HI_VB_SRC_BUTT
} hi_vb_src;

typedef enum  {
    HI_ASPECT_RATIO_NONE   = 0,        /* full screen */
    HI_ASPECT_RATIO_AUTO   = 1,        /* ratio no change, 1:1*/
    HI_ASPECT_RATIO_MANUAL = 2,        /* ratio manual set */
    HI_ASPECT_RATIO_BUTT
} hi_aspect_ratio_type;


typedef enum  {
    HI_VIDEO_FIELD_TOP         = 1,    /* even field */
    HI_VIDEO_FIELD_BOTTOM      = 2,    /* odd field */
    HI_VIDEO_FIELD_INTERLACED  = 3,    /* two interlaced fields */
    HI_VIDEO_FIELD_FRAME       = 4,    /* frame */

    HI_VIDEO_FIELD_BUTT
} hi_video_field;

typedef enum  {
    HI_VIDEO_FORMAT_LINEAR = 0,       /* nature video line */
    HI_VIDEO_FORMAT_TILE_64x16,       /* tile cell: 64pixel x 16line */
    HI_VIDEO_FORMAT_BUTT
} hi_video_format;

typedef enum  {
    HI_COMPRESS_MODE_NONE = 0,      /* no compress */
    HI_COMPRESS_MODE_SEG,           /* compress unit is 256x1 bytes as a segment.*/
    HI_COMPRESS_MODE_SEG_COMPACT,   /* compact compress unit is 256x1 bytes as a segment.*/
    HI_COMPRESS_MODE_TILE,          /* compress unit is a tile.*/
    HI_COMPRESS_MODE_LINE,          /* compress unit is the whole line.*/
    HI_COMPRESS_MODE_FRAME,         /* compress unit is the whole frame. YUV for VPSS(3DNR) */

    HI_COMPRESS_MODE_BUTT
} hi_compress_mode;

typedef enum  {
    HI_VIDEO_DISPLAY_MODE_PREVIEW  = 0,
    HI_VIDEO_DISPLAY_MODE_PLAYBACK = 1,

    HI_VIDEO_DISPLAY_MODE_BUTT
} hi_video_display_mode;

typedef enum  {
    HI_FRAME_FLAG_SNAP_FLASH  = 0x1 << 0,
    HI_FRAME_FLAG_SNAP_CUR    = 0x1 << 1,
    HI_FRAME_FLAG_SNAP_REF    = 0x1 << 2,
    HI_FRAME_FLAG_SNAP_END    = 0x1 << 3,
    HI_FRAME_FLAG_MIRROR      = 0x1 << 4,
    HI_FRAME_FLAG_FLIP        = 0x1 << 5,
    HI_FRAME_FLAG_BUTT
} hi_frame_flag;


typedef enum  {
    HI_COLOR_GAMUT_BT601 = 0,
    HI_COLOR_GAMUT_BT709,
    HI_COLOR_GAMUT_BT2020,
    HI_COLOR_GAMUT_USER,
    HI_COLOR_GAMUT_BUTT
} hi_color_gamut;

/* we ONLY define picture format used, all unused will be deleted! */
typedef enum {
    HI_PIXEL_FORMAT_RGB_444 = 0,
    HI_PIXEL_FORMAT_RGB_555,
    HI_PIXEL_FORMAT_RGB_565,
    HI_PIXEL_FORMAT_RGB_888,

    HI_PIXEL_FORMAT_BGR_444,
    HI_PIXEL_FORMAT_BGR_555,
    HI_PIXEL_FORMAT_BGR_565,
    HI_PIXEL_FORMAT_BGR_888,

    HI_PIXEL_FORMAT_ARGB_1555,
    HI_PIXEL_FORMAT_ARGB_4444,
    HI_PIXEL_FORMAT_ARGB_8565,
    HI_PIXEL_FORMAT_ARGB_8888,
    HI_PIXEL_FORMAT_ARGB_2BPP,
    HI_PIXEL_FORMAT_ARGB_CLUT2,
    HI_PIXEL_FORMAT_ARGB_CLUT4,

    HI_PIXEL_FORMAT_ABGR_1555,
    HI_PIXEL_FORMAT_ABGR_4444,
    HI_PIXEL_FORMAT_ABGR_8565,
    HI_PIXEL_FORMAT_ABGR_8888,

    HI_PIXEL_FORMAT_RGB_BAYER_8BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_10BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_12BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_14BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_16BPP,

    HI_PIXEL_FORMAT_YVU_PLANAR_422,
    HI_PIXEL_FORMAT_YVU_PLANAR_420,
    HI_PIXEL_FORMAT_YVU_PLANAR_444,

    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_422,
    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420,
    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_444,

    HI_PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    HI_PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    HI_PIXEL_FORMAT_YUV_SEMIPLANAR_444,

    HI_PIXEL_FORMAT_YUYV_PACKAGE_422,
    HI_PIXEL_FORMAT_YVYU_PACKAGE_422,
    HI_PIXEL_FORMAT_UYVY_PACKAGE_422,
    HI_PIXEL_FORMAT_VYUY_PACKAGE_422,
    HI_PIXEL_FORMAT_YYUV_PACKAGE_422,
    HI_PIXEL_FORMAT_YYVU_PACKAGE_422,
    HI_PIXEL_FORMAT_UVYY_PACKAGE_422,
    HI_PIXEL_FORMAT_VUYY_PACKAGE_422,
    HI_PIXEL_FORMAT_VY1UY0_PACKAGE_422,

    HI_PIXEL_FORMAT_YUV_400,
    HI_PIXEL_FORMAT_UV_420,

    /* SVP data format */
    HI_PIXEL_FORMAT_BGR_888_PLANAR,
    HI_PIXEL_FORMAT_HSV_888_PACKAGE,
    HI_PIXEL_FORMAT_HSV_888_PLANAR,
    HI_PIXEL_FORMAT_LAB_888_PACKAGE,
    HI_PIXEL_FORMAT_LAB_888_PLANAR,
    HI_PIXEL_FORMAT_S8C1,
    HI_PIXEL_FORMAT_S8C2_PACKAGE,
    HI_PIXEL_FORMAT_S8C2_PLANAR,
    HI_PIXEL_FORMAT_S8C3_PLANAR,
    HI_PIXEL_FORMAT_S16C1,
    HI_PIXEL_FORMAT_U8C1,
    HI_PIXEL_FORMAT_U16C1,
    HI_PIXEL_FORMAT_S32C1,
    HI_PIXEL_FORMAT_U32C1,
    HI_PIXEL_FORMAT_U64C1,
    HI_PIXEL_FORMAT_S64C1,

    HI_PIXEL_FORMAT_BUTT
} hi_pixel_format;


typedef enum  {
    HI_DYNAMIC_RANGE_SDR8 = 0,
    HI_DYNAMIC_RANGE_SDR10,
    HI_DYNAMIC_RANGE_HDR10,
    HI_DYNAMIC_RANGE_HLG,
    HI_DYNAMIC_RANGE_SLF,
    HI_DYNAMIC_RANGE_XDR,
    HI_DYNAMIC_RANGE_BUTT
} hi_dynamic_range;


typedef enum  {
    HI_DATA_BIT_WIDTH_8 = 0,
    HI_DATA_BIT_WIDTH_10,
    HI_DATA_BIT_WIDTH_12,
    HI_DATA_BIT_WIDTH_14,
    HI_DATA_BIT_WIDTH_16,
    HI_DATA_BIT_WIDTH_BUTT
} hi_data_bit_width;


typedef struct {
    hi_u32 top_width;
    hi_u32 bottom_width;
    hi_u32 left_width;
    hi_u32 right_width;
    hi_u32 color;
} hi_border;

typedef struct {
    hi_s32 x;
    hi_s32 y;
} hi_point;

typedef struct {
    hi_u32 width;
    hi_u32 height;
} hi_size;

typedef struct {
    hi_s32 x;
    hi_s32 y;
    hi_u32 width;
    hi_u32 height;
} hi_rect;

typedef enum {
    HI_COORD_ABS = 0,                          /* Absolute coordinate. */
    HI_COORD_RATIO,                            /* Ratio coordinate. */
    HI_COORD_BUTT
} hi_coord;

typedef enum {
    HI_COVER_RECT = 0,                         /* Rectangle cover. */
    HI_COVER_QUAD,                             /* Quadrangle cover. */
    HI_COVER_BUTT
} hi_cover_type;

typedef struct {
    hi_bool enable;
    hi_rect  rect;
} hi_crop_info;

typedef struct {
    hi_s32  src_frame_rate;        /* RW; source frame rate */
    hi_s32  dst_frame_rate;        /* RW; dest frame rate */
} hi_frame_rate_ctrl;

typedef struct {
    hi_aspect_ratio_type mode;          /* aspect ratio mode: none/auto/manual */
    hi_u32         bg_color;      /* background color, RGB 888 */
    hi_rect         video_rect;     /* valid in ASPECT_RATIO_MANUAL mode */
} hi_aspect_ratio;

typedef struct {
    hi_u32 vb_size;

    hi_u32 head_stride;
    hi_u32 head_size;
    hi_u32 head_y_size;

    hi_u32 main_stride;
    hi_u32 main_size;
    hi_u32 main_y_size;

    hi_u32 ex_stride;
    hi_u32 ex_y_size;
} hi_vb_calc_cfg;

/* Angle of rotation */
typedef enum  {
    HI_ROTATION_0   = 0,
    HI_ROTATION_90  = 1,
    HI_ROTATION_180 = 2,
    HI_ROTATION_270 = 3,
    HI_ROTATION_BUTT
} hi_rotation;

typedef enum  {
    HI_FRAME_INTERRUPT_START,
    HI_FRAME_INTERRUPT_EARLY,
    HI_FRAME_INTERRUPT_EARLY_END,
    HI_FRAME_INTERRUPT_BUTT,
} hi_frame_interrupt_type;

typedef struct {
    hi_frame_interrupt_type interrupt_type;
    hi_u32 early_line;
} hi_frame_interrupt_attr;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_COMMON_VIDEO_H__ */
