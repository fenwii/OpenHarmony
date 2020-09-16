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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Description: jpegd main header file.
 */
#ifndef __JPEGD_H__
#define __JPEGD_H__
#include "hi_type.h"
#include "jpegd_drv.h"

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

#define align_up(x, a) (((x) + ((a) - 1)) & (~((a) - 1)))

#define HI_JPEG_DEC_OK        0
#define HI_JPEG_DEC_FRAME_ERR 1
#define HI_JPEG_DEC_SCAN_ERR  2
#define HI_JPEG_DEC_MCU_ERR   3
#define HI_JPEG_DEC_DRI_ERR   4
#define HI_JPEG_DEC_DHT_ERR   5
#define HI_JPEG_DEC_DQT_ERR   6

#define JPEGD_MAX_WIDTH       8192
#define JPEGD_MAX_HEIGHT      8192
#define JPEGD_MIN_WIDTH       8
#define JPEGD_MIN_HEIGHT      8

#define ONE_EMAR_BUF_SIZE     (128 * ((JPEGD_MAX_WIDTH + 7) >> 3))

#define BASELINE              0xC0  /* baseline frame header */
#define PROGRESSIVE           0xC2  /* progressive frame header */
#define DHT                   0xC4
#define RST0                  0xD0
#define RST1                  0xD1
#define RST2                  0xD2
#define RST3                  0xD3
#define RST4                  0xD4
#define RST5                  0xD5
#define RST6                  0xD6
#define RST7                  0xD7
#define SOI                   0xD8
#define EOI                   0xD9
#define SOS                   0xDA
#define DQT                   0xDB
#define DNL                   0xDC
#define DRI                   0xDD

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define HI_MJPEG_DEC_OK       0
#define HI_MJPEG_NO_PICTURE   (-1)
#define HI_MJPEG_ERR_HANDLE   (-2)

#define JPEGD_MAX_HANDLE_NUM  3
#define JPEGD_CODE_LEN        16
#define JPEGD_HUFFMAN_LEN     256
#define JPEGD_QUANT_LEN       64
#define JPEGD_NF_LEN          4
#define JPEGD_NS_LEN          4
#define JPEGD_FRAME_COUNT     2
#define JPEGD_HUFFMAN_TAB     4
#define JPEGD_QUANT_TAB       4
#define JPEGD_DC_PRED         4
#define JPEGD_HUFFMAN_TAB_LEN 3
#define JPEGD_HUFFMAN_LEN     256

#define COM0  0
#define COM1  1
#define COM2  2

#define JPEGD_ALLOC_BUFF_CACHED

typedef void *jpegd_handle;

typedef enum {
    STATE_IDLE = 0,
    STATE_BUSY = 1,
    STATE_BUTT
} jpegd_state;

typedef struct {
    int max_code[JPEGD_CODE_LEN];
    int max_code16[JPEGD_CODE_LEN];
    int min_code[JPEGD_CODE_LEN];
    int len[JPEGD_CODE_LEN];
    unsigned short huffman_val_ptr[JPEGD_CODE_LEN];
    unsigned char huffman_val[JPEGD_HUFFMAN_LEN];

    unsigned char fast_huffman_code[JPEGD_HUFFMAN_LEN];
    unsigned char fast_huffman_len[JPEGD_HUFFMAN_LEN];
    unsigned int u_code32;
} huffman_tab;

typedef struct {
    unsigned char quant[JPEGD_QUANT_LEN];
} quant_tab;

typedef struct {
    unsigned int nf;
    unsigned int color_depth;
    unsigned int y_width;
    unsigned int y_height;
    unsigned char ci[JPEGD_NF_LEN]; /* NF:Number of image components in frame */
    unsigned char h[JPEGD_NF_LEN];
    unsigned char v[JPEGD_NF_LEN];
    unsigned char tq[JPEGD_NF_LEN];
    unsigned int restart_interval;
    unsigned int restart_interval_logic;
    unsigned int max_mcu_number;
} frame_header;

typedef struct {
    unsigned int ns;
    unsigned char cs[JPEGD_NS_LEN]; /* NS:Number of image components in scan */
    unsigned char td[JPEGD_NS_LEN];
    unsigned char ta[JPEGD_NS_LEN];
    unsigned char ss;
    unsigned char se;
    unsigned char ah;
    unsigned char al;
} scan_header;

typedef struct {
    unsigned char *buffer;
    unsigned int bit_len;
    unsigned int bit_offset;
} bitstream;

typedef struct {
    unsigned char *vir_addr;
    unsigned long long phy_addr;
    unsigned int len;
    unsigned int pts;
} jpegd_stream;

typedef struct {
    unsigned char *stream_buffer;
    unsigned char *pic_buffer;
    unsigned int stream_offest;
    jpegd_stream stream;
    bitstream bits;
    frame_header frame;
    scan_header scan;
    huffman_tab h_tab[JPEGD_HUFFMAN_TAB];
    quant_tab q_tab[JPEGD_QUANT_TAB];

    unsigned char *y[JPEGD_FRAME_COUNT];
    unsigned char *u[JPEGD_FRAME_COUNT];
    unsigned char *v[JPEGD_FRAME_COUNT];
    unsigned int valid_frame;
    unsigned int max_width;
    unsigned int max_height;
    unsigned int buf_size;
    unsigned int first_mcu;
    short jpeg_dc_pred[JPEGD_DC_PRED];  /* 0 for Y;  1 for U;   2 for V;  3 reserved total */

    unsigned int height_in_mcu;
    unsigned int width_in_mcu;
    unsigned int y_stride;
    unsigned int c_stride;
    picture_format pic_format;

    quant_tab *q_tab_components[JPEGD_HUFFMAN_TAB_LEN];
    huffman_tab *h_tab_components_dc[JPEGD_HUFFMAN_TAB_LEN];
    huffman_tab *h_tab_components_ac[JPEGD_HUFFMAN_TAB_LEN];
    huffman_tab huffman_tmp;

    unsigned int profile; /* 0: baseline; 1:progressive; other:unsupport; */
    jpegd_state state;
    jpegd_vpu_config vpu_config;
    jpegd_vpu_status vpu_status;
} motion_jpeg_obj;

typedef struct hi_mjpeg_userdata {
    unsigned int user_data_type;  /* type of userdata */
    unsigned int user_data_size;  /* length of userdata in byte */
    unsigned char *data;  /* buffer contains userdata stuff */
    struct hi_mjpeg_userdata *next;  /* pointer to next userdata */
} mjpeg_userdata;

typedef struct {
    unsigned char *y;
    unsigned char *u;
    unsigned char *v;
    unsigned int width;
    unsigned int height;
    unsigned int y_stride;
    unsigned int c_stride;
    int pic_format;  /* 0: YUV420; */
    /* 1: YUV422; */
    /* 2: YUV444; */
    /* 3: YUV422V; */
    /* 4: YUV400; */
    /* >=5: reserved */
    int error;  /* 0: no error */
    /* 1: MCU error */
    unsigned long long pts;  /* time stamp */
    unsigned int reserved;
    int error_code;
    mjpeg_userdata *user_data;  /* pointer to the first userdata */
} mjpeg_dec_frame;

jpegd_handle jpegd_get_handle(void);
int jpegd_dec_frame(jpegd_handle handle, unsigned int flags);
int jpegd_start_one_frame(jpegd_handle handle, unsigned int flags);
void jpegd_write_regs(jpegd_handle handle, S_JPGD_REGS_TYPE *reg_base);
void jpegd_read_regs(jpegd_handle handle, S_JPGD_REGS_TYPE *reg_base);
int jpegd_start_decoding(jpegd_handle handle);
void jpegd_finish_decoding(jpegd_handle handle);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif /* _JPEGD_H_ */
