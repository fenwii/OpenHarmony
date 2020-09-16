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


#ifndef __HI35XX_VO_H__
#define __HI35XX_VO_H__

#define CFG_MAXARGS 10

#define HI_353X_VO  1
#define PIC_MAX_WIDTH   4096
#define PIC_MAX_HEIGHT  4096
#define GFX0_PIC_MAX_WIDTH   3840
#define GFX0_PIC_MAX_HEIGHT  3840
#define GFX1_PIC_MAX_WIDTH   1920
#define GFX1_PIC_MAX_HEIGHT  1920
#define VHD0_PIC_MAX_WIDTH   4096
#define VHD0_PIC_MAX_HEIGHT  4096
#define VHD1_PIC_MAX_WIDTH   1920
#define VHD1_PIC_MAX_HEIGHT  1920

#define PIC_MIN_LENTH   16

/* VO video output interface type */
#define VO_INTF_CVBS        (0x01L<<0)
#define VO_INTF_YPBPR       (0x01L<<1)
#define VO_INTF_VGA         (0x01L<<2)
#define VO_INTF_BT656       (0x01L<<3)
#define VO_INTF_BT1120      (0x01L<<4)
#define VO_INTF_HDMI        (0x01L<<5)
#define VO_INTF_LCD         (0x01L<<6)
#define VO_INTF_BT656_H     (0x01L<<7)
#define VO_INTF_BT656_L     (0x01L<<8)
#define VO_INTF_LCD_6BIT    (0x01L<<9)
#define VO_INTF_LCD_8BIT    (0x01L<<10)
#define VO_INTF_LCD_16BIT   (0x01L<<11)
#define VO_INTF_LCD_18BIT   (0x01L<<12)
#define VO_INTF_LCD_24BIT   (0x01L<<13)
#define VO_INTF_MIPI        (0x01L<<14)
#define VO_INTF_MIPI_SLAVE  (0x01L<<15)


typedef enum {
    VO_OUTPUT_PAL = 0,               /* PAL standard */
    VO_OUTPUT_NTSC,                  /* NTSC standard */

    VO_OUTPUT_1080P24,               /* 1920 x 1080 at 24 Hz. */
    VO_OUTPUT_1080P25,               /* 1920 x 1080 at 25 Hz. */
    VO_OUTPUT_1080P30,               /* 1920 x 1080 at 30 Hz. */

    VO_OUTPUT_720P50,                /* 1280 x  720 at 50 Hz. */
    VO_OUTPUT_720P60,                /* 1280 x  720 at 60 Hz. */
    VO_OUTPUT_1080I50,               /* 1920 x 1080 at 50 Hz, interlace. */
    VO_OUTPUT_1080I60,               /* 1920 x 1080 at 60 Hz, interlace. */
    VO_OUTPUT_1080P50,               /* 1920 x 1080 at 50 Hz. */
    VO_OUTPUT_1080P60,               /* 1920 x 1080 at 60 Hz. */

    VO_OUTPUT_576P50,                /* 720  x  576 at 50 Hz. */
    VO_OUTPUT_480P60,                /* 720  x  480 at 60 Hz. */

    VO_OUTPUT_800x600_60,            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1024x768_60,           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1280x1024_60,          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1366x768_60,           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1440x900_60,           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
    VO_OUTPUT_1280x800_60,           /* 1280*800@60Hz VGA@60Hz */
    VO_OUTPUT_1600x1200_60,          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1680x1050_60,          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
    VO_OUTPUT_1920x1200_60,          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking) */
    VO_OUTPUT_640x480_60,            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
    VO_OUTPUT_960H_PAL,              /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced) */
    VO_OUTPUT_960H_NTSC,             /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced) */
    VO_OUTPUT_1920x2160_30,          /* 1920x2160_30 */
    VO_OUTPUT_2560x1440_30,          /* 2560x1440_30 */
    VO_OUTPUT_2560x1440_60,          /* 2560x1440_60 */
    VO_OUTPUT_2560x1600_60,          /* 2560x1600_60 */
    VO_OUTPUT_3840x2160_24,          /* 3840x2160_24 */
    VO_OUTPUT_3840x2160_25,          /* 3840x2160_25 */
    VO_OUTPUT_3840x2160_30,          /* 3840x2160_30 */
    VO_OUTPUT_3840x2160_50,          /* 3840x2160_50 */
    VO_OUTPUT_3840x2160_60,          /* 3840x2160_60 */
    VO_OUTPUT_4096x2160_24,          /* 4096x2160_24 */
    VO_OUTPUT_4096x2160_25,          /* 4096x2160_25 */
    VO_OUTPUT_4096x2160_30,          /* 4096x2160_30 */
    VO_OUTPUT_4096x2160_50,          /* 4096x2160_50 */
    VO_OUTPUT_4096x2160_60,          /* 4096x2160_60 */
    VO_OUTPUT_320x240_60,            /* For ota5182 at 60 Hz (8bit)  */
    VO_OUTPUT_320x240_50,            /* For ili9342 at 50 Hz (6bit)  */
    VO_OUTPUT_240x320_50,            /* For ili9341 at 50 Hz (6bit)  */
    VO_OUTPUT_240x320_60,            /* For ili9341 at 60 Hz (16bit) */
    VO_OUTPUT_800x600_50,            /* For LCD     at 50 Hz (24bit) */
    VO_OUTPUT_720x1280_60,           /* For MIPI DSI Tx 720 x1280 at 60 Hz */
    VO_OUTPUT_1080x1920_60,          /* For MIPI DSI Tx 1080x1920 at 60 Hz */
    VO_OUTPUT_7680x4320_30,          /* For HDMI2.0 at 30 Hz         */
    VO_OUTPUT_USER,                  /* User timing. */
    VO_OUTPUT_BUTT
} vo_intf_sync;

typedef enum {
    VO_DEV_DHD0  = 0,        /* high definition device */
    VO_DEV_DHD1  = 1,        /* assistant device */
    VO_DEV_BUTT
} vo_dev;

typedef enum {
    VO_GRAPHC_G0 = 0,
    VO_GRAPHC_G1 = 1,
    VO_GRAPHC_BUTT
} vo_graphic;

typedef enum {
    VO_LAYER_VHD0 = 0,
    VO_LAYER_VHD1 = 1,
    VO_LAYER_VP = 2,
    VO_LAYER_VSD0 = 3,
    VO_LAYER_G0 = 4,    /* fb0 */
    VO_LAYER_G1 = 5,    /* fb2 */
    VO_LAYER_HC0 = 6,    /* G2 is HC0 --- fb3 */
    VO_LAYER_HC1 = 7,   /* G3 is HC1  --- fb4 */
    VO_LAYER_G4 = 8,   /* fb1 */
    VO_LAYER_WBC_G0 = 9,
    VO_LAYER_WBC_G4 = 10,
    VO_LAYER_WBC_D = 11,
    VO_LAYER_BUTT
} hi_vo_layer;

#define VO_LAYER_G2 VO_LAYER_HC0

typedef enum {
    VO_CSC_MATRIX_IDENTITY = 0,       /* Identity CSC matrix. */

    VO_CSC_MATRIX_BT601_TO_BT709,     /* BT601 to BT709 */
    VO_CSC_MATRIX_BT709_TO_BT601,     /* BT709 to BT601 */

    VO_CSC_MATRIX_BT601_TO_RGB_PC,    /* BT601 to RGB */
    VO_CSC_MATRIX_BT709_TO_RGB_PC,    /* BT709 to RGB */

    VO_CSC_MATRIX_RGB_TO_BT601_PC,    /* RGB to BT601 FULL */
    VO_CSC_MATRIX_RGB_TO_BT709_PC,    /* RGB to BT709 FULL */

    VO_CSC_MATRIX_RGB_TO_BT2020_PC,   /* RGB to BT.2020 */
    VO_CSC_MATRIX_BT2020_TO_RGB_PC,   /* BT.2020 to RGB */

    VO_CSC_MATRIX_RGB_TO_BT601_TV,    /* RGB to BT601 LIMIT */
    VO_CSC_MATRIX_RGB_TO_BT709_TV,    /* RGB to BT709 LIMIT */

    VO_CSC_MATRIX_BUTT
} vo_csc_matrix;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
} hi_vo_rect;

#endif

