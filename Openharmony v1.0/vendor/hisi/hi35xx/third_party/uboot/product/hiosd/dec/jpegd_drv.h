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
 * Description: jpegd drv level header file.
 */
#ifndef __JPEGD_DRV_H__
#define __JPEGD_DRV_H__
#include "jpegd_reg.h"
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

#ifdef CHIP_HI3559AV100
#define JPEGD_CRG_REG_ADDR    (0x1201013c)
#define JPEGD_REGS_ADDR       (0x11210000)
#define JPEGD_CKEN_OFFSET   1
#endif

#ifdef CHIP_HI3569V100
#define JPEGD_CRG_REG_ADDR    (0x1201013c)
#define JPEGD_REGS_ADDR       (0x11210000)
#define JPEGD_CKEN_OFFSET   1
#endif

#ifdef CHIP_HI3519AV100
#define JPEGD_CRG_REG_ADDR    (0x0451013c)
#define JPEGD_REGS_ADDR       (0x04ac0000)
#define JPEGD_CKEN_OFFSET   1
#endif

#ifdef CHIP_HI3516CV500
#define JPEGD_CRG_REG_ADDR    (0x120100c4)
#define JPEGD_REGS_ADDR       (0x11260000)
#define JPEGD_CKEN_OFFSET   1
#endif

#ifdef CHIP_HI3531DV200
#define JPEGD_CRG_REG_ADDR    (0x11017640)
#define JPEGD_REGS_ADDR       (0x17180000)
#define JPEGD_CKEN_OFFSET   4
#endif

#ifdef CHIP_HI3535AV100
#define JPEGD_CRG_REG_ADDR    (0x11017640)
#define JPEGD_REGS_ADDR       (0x17180000)
#define JPEGD_CKEN_OFFSET   4
#endif

#ifdef CHIP_HI3521DV200
#define JPEGD_CRG_REG_ADDR    (0x11017640)
#define JPEGD_REGS_ADDR       (0x17180000)
#define JPEGD_CKEN_OFFSET   4
#endif

#ifdef CHIP_HI3520DV500
#define JPEGD_CRG_REG_ADDR    (0x11017640)
#define JPEGD_REGS_ADDR       (0x17180000)
#define JPEGD_CKEN_OFFSET   4
#endif

#define JPEGD_REGS_SIZE       0x6BF

#define JPEGD_IP_NUM          1

#define QUANT_TABLE_SIZE      64
#define HDC_TABLE_SIZE        12
#define HAC_MIN_TABLE_SIZE    8
#define HAC_BASE_TABLE_SIZE   8
#define HAC_SYMBOL_TABLE_SIZE 176
#define ZIGZAG_TABLE_SIZE     64

typedef struct {
    hi_bool int_dec_finish;
    hi_bool int_dec_err;
    hi_bool int_over_time;
    hi_bool int_bs_res;
} jpegd_vpu_status;

typedef enum {
    PIXEL_FORMAT_RGB_444 = 0,
    PIXEL_FORMAT_RGB_555,
    PIXEL_FORMAT_RGB_565,
    PIXEL_FORMAT_RGB_888,

    PIXEL_FORMAT_BGR_444,
    PIXEL_FORMAT_BGR_555,
    PIXEL_FORMAT_BGR_565,
    PIXEL_FORMAT_BGR_888,

    PIXEL_FORMAT_ARGB_1555,
    PIXEL_FORMAT_ARGB_4444,
    PIXEL_FORMAT_ARGB_8565,
    PIXEL_FORMAT_ARGB_8888,

    PIXEL_FORMAT_ABGR_1555,
    PIXEL_FORMAT_ABGR_4444,
    PIXEL_FORMAT_ABGR_8565,
    PIXEL_FORMAT_ABGR_8888,

    PIXEL_FORMAT_RGB_BAYER_8BPP,
    PIXEL_FORMAT_RGB_BAYER_10BPP,
    PIXEL_FORMAT_RGB_BAYER_12BPP,
    PIXEL_FORMAT_RGB_BAYER_14BPP,
    PIXEL_FORMAT_RGB_BAYER_16BPP,

    PIXEL_FORMAT_YUV_PLANAR_422,
    PIXEL_FORMAT_YUV_PLANAR_420,
    PIXEL_FORMAT_YUV_PLANAR_444,

    PIXEL_FORMAT_YVU_SEMIPLANAR_422,
    PIXEL_FORMAT_YVU_SEMIPLANAR_420,
    PIXEL_FORMAT_YVU_SEMIPLANAR_444,

    PIXEL_FORMAT_UYVY_PACKAGE_422,
    PIXEL_FORMAT_YUYV_PACKAGE_422,
    PIXEL_FORMAT_VYUY_PACKAGE_422,

    PIXEL_FORMAT_YUV_400,

    PIXEL_FORMAT_BUTT
} hi_pixel_format;

typedef enum {
    PICTURE_FORMAT_YUV420 = 0,
    PICTURE_FORMAT_YUV422 = 1, /* 422 2x1 */
    PICTURE_FORMAT_YUV444 = 2,
    PICTURE_FORMAT_YUV422V = 3, /* 422 1x2 */
    PICTURE_FORMAT_YUV400 = 4,
    PICTURE_FORMAT_BUTT
} picture_format;

typedef struct {
    int chn_id;
    picture_format pic_format;
    hi_pixel_format pixel_format;
    hi_bool out_yuv;
    unsigned char v_fac;
    unsigned char u_fac;
    unsigned char y_fac;
    unsigned int dri;
    unsigned int width;
    unsigned int height;
    unsigned int width_in_mcu;
    unsigned int height_in_mcu;
    unsigned int y_stride;
    unsigned int c_stride;
    unsigned int pic_type;
    unsigned int rgb_stride;
    unsigned int alpha;

    unsigned long long y_phy_addr;
    unsigned long long c_phy_addr;
    unsigned long long phy_str_buf_start;
    unsigned long long phy_str_buf_end;
    unsigned long long phy_str_start;
    unsigned long long phy_str_end;
    unsigned long long phy_emar_buffer0;
    unsigned long long phy_emar_buffer1;

    unsigned int quant_table[QUANT_TABLE_SIZE];
    unsigned int huffman_table[HDC_TABLE_SIZE];
    unsigned int huffman_min_table[HAC_MIN_TABLE_SIZE];
    unsigned int huffman_base_table[HAC_BASE_TABLE_SIZE];
    unsigned int huffman_symbol_table[HAC_SYMBOL_TABLE_SIZE];
} jpegd_vpu_config;

void jpegd_drv_write_regs(S_JPGD_REGS_TYPE *reg_base, jpegd_vpu_config *vpu_config);

void jpegd_drv_read_regs(S_JPGD_REGS_TYPE *reg_base, jpegd_vpu_status *vpu_status);

void jpegd_set_clock_en(int vpu_id, hi_bool is_run);
void jpegd_reset_select(int vpu_id, hi_bool is_run);

void jpegd_set_outstanding(int vpu_id, int outstanding);
void *jpegd_get_reg_addr(int vpu_id);
unsigned int jpegd_read_int(int vpu_id);
void jpegd_clear_int(int vpu_id);
void jpegd_set_int_mask(int vpu_id);
void jpegd_reset(int vpu_id);
void jpegd_start_vpu(int vpu_id);
int jpegd_set_time_out(int vpu_id, int time_out);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif /* End of __JPEGD_DRV_H__ */
