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

#ifndef __MIPI_TX_H__
#define __MIPI_TX_H__

#include <common.h>

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define CMD_MAX_NUM  4
#define LANE_MAX_NUM 4

#define hi_err(x...)                                \
    do {                                            \
        printf("%s(%d): ", __FUNCTION__, __LINE__); \
        printf(x);                                  \
    } while (0)

#define mipi_tx_check_null_ptr_return(ptr)     \
    do {                               \
        if ((ptr) == HI_NULL) {        \
            hi_err("NULL point \r\n"); \
            return (-1);               \
        }                              \
    } while (0)

typedef enum {
    OUTPUT_MODE_CSI = 0x0,       /* csi mode */
    OUTPUT_MODE_DSI_VIDEO = 0x1, /* dsi video mode */
    OUTPUT_MODE_DSI_CMD = 0x2,   /* dsi command mode */

    OUTPUT_MODE_BUTT
} output_mode_t;

typedef enum {
    BURST_MODE = 0x0,
    NON_BURST_MODE_SYNC_PULSES = 0x1,
    NON_BURST_MODE_SYNC_EVENTS = 0x2,
} video_mode_t;

typedef enum {
    OUT_FORMAT_RGB_16_BIT = 0x0,
    OUT_FORMAT_RGB_18_BIT = 0x1,
    OUT_FORMAT_RGB_24_BIT = 0x2,
    OUT_FORMAT_YUV420_8_BIT_NORMAL = 0x3,
    OUT_FORMAT_YUV420_8_BIT_LEGACY = 0x4,
    OUT_FORMAT_YUV422_8_BIT = 0x5,

    OUT_FORMAT_BUTT
} output_format_t;

typedef struct {
    unsigned short vid_pkt_size;
    unsigned short vid_hsa_pixels;
    unsigned short vid_hbp_pixels;
    unsigned short vid_hline_pixels;
    unsigned short vid_vsa_lines;
    unsigned short vid_vbp_lines;
    unsigned short vid_vfp_lines;
    unsigned short vid_active_lines;
    unsigned short edpi_cmd_size;
} sync_info_t;

typedef struct {
    unsigned int devno;          /* device number */
    short lane_id[LANE_MAX_NUM]; /* lane_id: -1 - disable */
    output_mode_t output_mode;   /* output mode: CSI/DSI_VIDEO/DSI_CMD */
    video_mode_t video_mode;
    output_format_t output_format;
    sync_info_t sync_info;
    unsigned int phy_data_rate; /* mbps */
    unsigned int pixel_clk;     /* KHz */
} combo_dev_cfg_t;

typedef struct {
    unsigned int devno; /* device number */
    unsigned short data_type;
    unsigned short cmd_size;
    unsigned char *cmd;
} cmd_info_t;

typedef struct {
    unsigned int   devno;          /* device number */
    unsigned short data_type;      /* DSI data type */
    unsigned short data_param;     /* data param,low 8 bit:first param.high 8 bit:second param, set 0 if not use */
    unsigned short get_data_size;  /* read data size */
    unsigned char  *get_data;      /* read data memery address, should  malloc by user */
} get_cmd_info_t;

#define HI_MIPI_TX_SET_DEV_CFG 0x01
#define HI_MIPI_TX_SET_CMD     0x02
#define HI_MIPI_TX_ENABLE      0x03
#define HI_MIPI_TX_GET_CMD     0x04
#define HI_MIPI_TX_DISABLE     0x05

int mipi_tx_display(unsigned int vosync);
int mipi_tx_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
