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

#ifndef  __HI_HDMI_H__
#define  __HI_HDMI_H__

#include "hi_type.h"

#define HI_HDMI_HW_PARAM_NUM 4

typedef enum hi_hdmi_video_fmt_ {
    HI_HDMI_VIDEO_FMT_1080P_60 = 0,
    HI_HDMI_VIDEO_FMT_1080P_50,
    HI_HDMI_VIDEO_FMT_1080P_30,
    HI_HDMI_VIDEO_FMT_1080P_25,
    HI_HDMI_VIDEO_FMT_1080P_24,

    HI_HDMI_VIDEO_FMT_1080I_60,
    HI_HDMI_VIDEO_FMT_1080I_50,

    HI_HDMI_VIDEO_FMT_720P_60,
    HI_HDMI_VIDEO_FMT_720P_50,

    HI_HDMI_VIDEO_FMT_576P_50,
    HI_HDMI_VIDEO_FMT_480P_60,

    HI_HDMI_VIDEO_FMT_PAL,                  /* B D G H I PAL */
    HI_HDMI_VIDEO_FMT_PAL_N,                /* (N)PAL        */
    HI_HDMI_VIDEO_FMT_PAL_NC,               /* (Nc)PAL       */

    HI_HDMI_VIDEO_FMT_NTSC,                 /* (M)NTSC       */
    HI_HDMI_VIDEO_FMT_NTSC_J,               /* NTSC-J        */
    HI_HDMI_VIDEO_FMT_NTSC_PAL_M,           /* (M)PAL        */

    HI_HDMI_VIDEO_FMT_SECAM_SIN,            /* SECAM_SIN */
    HI_HDMI_VIDEO_FMT_SECAM_COS,            /* SECAM_COS */

    HI_HDMI_VIDEO_FMT_861D_640X480_60,
    HI_HDMI_VIDEO_FMT_VESA_800X600_60,
    HI_HDMI_VIDEO_FMT_VESA_1024X768_60,
    HI_HDMI_VIDEO_FMT_VESA_1280X720_60,
    HI_HDMI_VIDEO_FMT_VESA_1280X800_60,
    HI_HDMI_VIDEO_FMT_VESA_1280X1024_60,
    HI_HDMI_VIDEO_FMT_VESA_1366X768_60,
    HI_HDMI_VIDEO_FMT_VESA_1440X900_60,
    HI_HDMI_VIDEO_FMT_VESA_1440X900_60_RB,
    HI_HDMI_VIDEO_FMT_VESA_1600X900_60_RB,
    HI_HDMI_VIDEO_FMT_VESA_1600X1200_60,
    HI_HDMI_VIDEO_FMT_VESA_1680X1050_60,
    HI_HDMI_VIDEO_FMT_VESA_1920X1080_60,
    HI_HDMI_VIDEO_FMT_VESA_1920X1200_60,
    HI_HDMI_VIDEO_FMT_VESA_2048X1152_60,    /* Currently, not support */
    HI_HDMI_VIDEO_FMT_VESA_CUSTOMER_DEFINE, /* Currently, not support */

    HI_HDMI_VIDEO_FMT_BUTT
} hi_hdmi_video_fmt;


typedef enum hi_hdmi_video_mode_ {
    HI_HDMI_VIDEO_MODE_RGB444,
    HI_HDMI_VIDEO_MODE_YCBCR422,
    HI_HDMI_VIDEO_MODE_YCBCR444,

    HI_HDMI_VIDEO_MODE_BUTT
} hi_hdmi_video_mode;

typedef enum hi_hdmi_id_ {
    HI_HDMI_ID_0         = 0,               /* HDMI 0 */
    HI_HDMI_ID_BUTT
} hi_hdmi_id;
typedef hi_hdmi_id hi_unf_hdmi_id;
typedef hi_hdmi_id hi_hdmi_id;

/* the config parameter of HDMI interface */
typedef struct {
    hi_bool            enable_hdmi;
    hi_u32             disp_fmt;
    hi_hdmi_video_mode vid_out_mode;
    hi_hdmi_video_mode vid_in_mode;
} hi_drv_hdmi_attr;

/* the config parameter of HDMI interface */
typedef struct hi_unf_hdmi_attr_ {
    hi_bool              enable_hdmi;
    hi_u32               disp_fmt;
    hi_hdmi_video_mode vid_out_mode;
    hi_hdmi_video_mode vid_in_mode;
} hi_unf_hdmi_attr;

typedef struct {
    hi_u32 i_de_main_clk;
    hi_u32 i_de_main_data;
    hi_u32 i_main_clk;
    hi_u32 i_main_data;
    hi_u32 ft_cap_clk;
    hi_u32 ft_cap_data;
} hi_hdmi_hw_param;

typedef struct {
    hi_hdmi_hw_param hw_param[HI_HDMI_HW_PARAM_NUM];
} hi_hdmi_hw_spec;

typedef enum {
    HI_HDMI_TRACE_LEN_0,
    HI_HDMI_TRACE_LEN_1,
    HI_HDMI_TRACE_LEN_2,
    HI_HDMI_TRACE_LEN_3,
    HI_HDMI_TRACE_LEN_4,
    HI_HDMI_TRACE_LEN_5,
    HI_HDMI_TRACE_LEN_6,
    HI_HDMI_TRACE_LEN_7,
    HI_HDMI_TRACE_LEN_8,
    HI_HDMI_TRACE_BUTT
} hi_hdmi_trace_len;

typedef struct {
    hi_bool emi_en; /* hdmi emi enable */
    hi_hdmi_trace_len trace_len; /* Phy parameters selection. */
} hi_hdmi_mod_param;

hi_s32 hi_drv_hdmi_init(void);
hi_s32 hi_drv_hdmi_de_init(void);
hi_s32 hi_drv_hdmi_open(hi_hdmi_id hdmi_id);
hi_s32 hi_drv_hdmi_set_attr(hi_hdmi_id hdmi_id, hi_drv_hdmi_attr *attr);
hi_s32 hi_drv_hdmi_start(hi_hdmi_id hdmi_id);
hi_s32 hi_drv_hdmi_close(hi_hdmi_id hdmi_id);




int hdmi_display(unsigned int vosync, unsigned int input, unsigned int output);
void hdmi_stop(void);

#endif
