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
 * Description: jpegd main file.
 */
#include "jpegd_image.h"
#include "jpegd_drv.h"
#include "jpegd_entry.h"

static const unsigned char g_zigzag_for_qtable[ZIGZAG_TABLE_SIZE] = {
    0,  1,  8, 16,  9,  2,  3, 10, 17, 24, 32, 25, 18, 11,  4,  5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13,  6,  7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
};

motion_jpeg_obj g_jpegd_ctx;

int jpegd_dec_baseline(motion_jpeg_obj *jpegd_hdl_ctx, unsigned char **str, unsigned int *flag,
    unsigned int *idx, unsigned int len)
{
    unsigned char *stream = *str;
    int result = HI_SUCCESS;
    if (*flag == 1) {
        int tmp_len = (stream[0] << 8) + stream[1]; /* shift left 8 bits */
        tmp_len = MIN(tmp_len, len - *idx);
        jpegd_hdl_ctx->stream_buffer = stream;
        *idx += (tmp_len + 2); /* 2 number of bytes */
        stream += (tmp_len);
        result = decode_sof0(jpegd_hdl_ctx, jpegd_hdl_ctx->stream_buffer);
        if (result == HI_JPEG_DEC_OK) {
            *flag = 2; /* 2 decode sof0 success */
        }
    }
    *str = stream;
    return result;
}

int jpegd_dec_dht(motion_jpeg_obj *jpegd_hdl_ctx, unsigned char **str, unsigned int len, unsigned int *idx)
{
    unsigned char *stream = *str;
    unsigned int tmp_len = (stream[0] << 8) + stream[1]; /* shift left 8 bits */
    tmp_len = MIN(tmp_len, len - *idx);
    jpegd_hdl_ctx->stream_buffer = stream;
    *idx += (tmp_len + 2); /* 2 number of bytes */
    stream += (tmp_len);

    if (decode_dht(jpegd_hdl_ctx, jpegd_hdl_ctx->stream_buffer)) {
        return HI_FAILURE;
    }
    *str = stream;
    return HI_SUCCESS;
}

int jpegd_dec_sos(motion_jpeg_obj *jpegd_hdl_ctx, unsigned char **str, unsigned int *flag, unsigned int *idx,
    unsigned int len)
{
    unsigned char *stream = *str;
    int result = HI_SUCCESS;
    if (*flag == 2) { /* 2 decode sof0 success */
        int tmp_len = (stream[0] << 8) + stream[1]; /* shift left 8 bits */
        tmp_len = MIN(tmp_len, len - *idx);
        jpegd_hdl_ctx->stream_buffer = stream;
        *idx += (tmp_len);
        stream += (tmp_len);
        jpegd_hdl_ctx->first_mcu = 0;
        result = decode_sos(jpegd_hdl_ctx, jpegd_hdl_ctx->stream_buffer);
        if (result == HI_JPEG_DEC_OK) {
            *flag = 3;  /* 3 scan header decoding success */
        } else {
            return HI_FAILURE;
        }
    }
    *str = stream;
    return HI_SUCCESS;
}

int jpegd_dec_dqt(motion_jpeg_obj *jpegd_hdl_ctx, unsigned char **str, unsigned int *idx, unsigned int len)
{
    unsigned char *stream = *str;
    int tmp_len = (stream[0] << 8) + stream[1]; /* shift left 8 bits */
    tmp_len = MIN(tmp_len, len - *idx);
    jpegd_hdl_ctx->stream_buffer = stream;
    *idx += (tmp_len + 2); /* 2 DQT number of bytes */
    stream += (tmp_len);

    if (decode_dqt(jpegd_hdl_ctx, jpegd_hdl_ctx->stream_buffer)) {
        return HI_FAILURE;
    }
    *str = stream;
    return HI_SUCCESS;
}

int jpegd_dec_dri(motion_jpeg_obj *jpegd_hdl_ctx, unsigned char **str, unsigned int *flag, unsigned int *idx)
{
    unsigned char *stream = *str;
    jpegd_hdl_ctx->stream_buffer = stream;
    if (decode_dri(jpegd_hdl_ctx, jpegd_hdl_ctx->stream_buffer)) { /* 4 dri len */
        *flag = 0;
        return HI_FAILURE;
    }
    *idx += 6; /* 6 define restart interval */
    stream += 4; /* 4 define restart interval */
    *str = stream;
    return HI_SUCCESS;
}

int jpegd_dec_err(unsigned char **str, unsigned int *idx, unsigned int type, unsigned int *flag)
{
    unsigned char *stream = *str;
    int result = HI_SUCCESS;
    if ((type & 0xE0) == 0xE0) { /* 0xE0:APP_0 value */
        int tmp_len = (stream[0] << 8) + stream[1]; /* shift left 8 bits */
        *idx += (tmp_len + 2); /* 2 number of bytes */
        stream += (tmp_len);
    } else if ((type & 0xF0) == 0xC0) { /* 0xF0:JPG_0 0xC0:baseline */
        *flag = 0;
        result = HI_FAILURE;
    } else {
        *idx += 2; /* 2 number of bytes */
    }
    *str = stream;
    return result;
}

void jpegd_dec_sos_success(motion_jpeg_obj *jpegd_hdl_ctx, mjpeg_dec_frame *tmp_dec_frame,
    bool quant_table_valid, bool huffman_table_valid, unsigned int idx)
{
    jpegd_hdl_ctx->stream_offest = idx + 2; /* 2 number of bytes */
    tmp_dec_frame->width = jpegd_hdl_ctx->frame.y_width;
    tmp_dec_frame->height = jpegd_hdl_ctx->frame.y_height;
    tmp_dec_frame->y_stride = jpegd_hdl_ctx->y_stride;
    tmp_dec_frame->c_stride = jpegd_hdl_ctx->c_stride;
    tmp_dec_frame->pic_format = jpegd_hdl_ctx->pic_format;
    tmp_dec_frame->pts = jpegd_hdl_ctx->stream.pts;
    tmp_dec_frame->reserved = 0;
    tmp_dec_frame->user_data = NULL;
    jpegd_hdl_ctx->valid_frame ^= 0x1;  /*  0x1:change to another buffer */

    if (quant_table_valid == HI_FALSE) {
        init_default_quant_table(jpegd_hdl_ctx);
    }
    if (huffman_table_valid == HI_FALSE) {
        init_default_huffman_table(jpegd_hdl_ctx);
    }
    return;
}

void jpegd_dec_sos_failed(mjpeg_dec_frame *tmp_dec_frame)
{
    tmp_dec_frame->y = NULL;
    tmp_dec_frame->u = NULL;
    tmp_dec_frame->v = NULL;
    tmp_dec_frame->width = 0;
    tmp_dec_frame->height = 0;
    tmp_dec_frame->y_stride = 0;
    tmp_dec_frame->c_stride = 0;
    tmp_dec_frame->pic_format = PICTURE_FORMAT_BUTT;
    tmp_dec_frame->pts = 0;
    tmp_dec_frame->reserved = 0;
    tmp_dec_frame->user_data = NULL;
    return;
}

/* decode jpeg picture */
int jpegd_dec_frame(jpegd_handle handle, unsigned int flags)
{
    motion_jpeg_obj *jpegd_hdl_ctx = (motion_jpeg_obj *)handle;
    unsigned int i;
    unsigned int jpeg_flag = 0;
    int result = 0;
    unsigned int type;
    unsigned char *stream = NULL;
    unsigned int len;
    mjpeg_dec_frame *tmp_dec_frame = NULL;
    mjpeg_dec_frame dec_frame;
    hi_bool quant_table_valid = HI_FALSE;
    hi_bool huffman_table_valid = HI_FALSE;

    if (jpegd_hdl_ctx == NULL) {
        hi_trace("jpegd handle is null!\n");
        return HI_MJPEG_ERR_HANDLE;
    }

    stream = jpegd_hdl_ctx->stream.vir_addr;
    len = jpegd_hdl_ctx->stream.len;
    tmp_dec_frame = &dec_frame;

    if (stream == NULL) {
        hi_trace("jpegd stream vir_addr is null!\n");
        return HI_MJPEG_ERR_HANDLE;
    }
    tmp_dec_frame->error_code = 0;
    tmp_dec_frame->error = 0;
    jpegd_hdl_ctx->frame.restart_interval = 0;

    for (i = 0; i < len;) {
        type = 0xFF; /* 0xFF:jpeg maker */
        while ((i < len) && (*(stream++) != 0xff)) { /* 0xFF:jpeg maker */
            i++;
        }
        type = *(stream++);
        while ((i < len) && (type == 0xff)) { /* 0xFF:jpeg maker */
            type = *(stream++);
            i++;
        }
        switch (type) {
            case BASELINE: {  /* sequential DCT */
                result = jpegd_dec_baseline(jpegd_hdl_ctx, &stream, &jpeg_flag, &i, len);
                if (result != HI_SUCCESS) {
                    tmp_dec_frame->error_code = result;
                    hi_trace("jpeg decode DCT error!\n");
                    goto end;
                }
            }
            break;

            case DHT: {  /* DHT */
                result = jpegd_dec_dht(jpegd_hdl_ctx, &stream, len, &i);
                if (result != HI_SUCCESS) {
                    tmp_dec_frame->error_code += HI_ERR_HUFFMAN_TABLE;
                    hi_trace("jpeg decode huffman error!\n");
                    goto end;
                }
                huffman_table_valid = HI_TRUE;
            }
            break;

            case SOS: {  /* scan header */
                result = jpegd_dec_sos(jpegd_hdl_ctx, &stream, &jpeg_flag, &i, len);
                if (result != HI_SUCCESS) {
                    hi_trace("jpeg decode SOS error!\n");
                    goto end;  /* scan header decoding error */
                }
                goto end;
            }
            break;

            case SOI: {  /* a new jpeg picture */
                i += 2; /* 2 SOI number of bytes */
                jpeg_flag = 1;
            }
            break;

            case EOI: {  /* end of jpeg picture */
                i += 2; /* 2 EOI number of bytes */
                goto end;
            }

            case DQT: {
                result = jpegd_dec_dqt(jpegd_hdl_ctx, &stream, &i, len);
                if (result != HI_SUCCESS) {
                    tmp_dec_frame->error_code += HI_ERR_HUFFMAN_TABLE;
                    hi_trace("jpeg decode DQT error!\n");
                    goto end;
                }
                quant_table_valid = HI_TRUE;
            }
            break;

            case DNL: {
                i += 6; /* 6 define number of lines */
                stream += 4; /* 4 number of lines' size */
                jpeg_flag = 0;
            }
            break;

            case DRI: {
                result = jpegd_dec_dri(jpegd_hdl_ctx, &stream, &jpeg_flag, &i);
                if (result != HI_SUCCESS) {
                    tmp_dec_frame->error_code = HI_ERR_RESTART_ERROR;
                    hi_trace("jpeg decode DRI error!\n");
                    goto end;
                }
            }
            break;

            default: {  /* do not support */
                result = jpegd_dec_err(&stream, &i, type, &jpeg_flag);
                if (result != HI_SUCCESS) {
                    tmp_dec_frame->error_code = HI_ERR_NOT_BASELINE;
                    hi_trace("jpeg decode error, unsupport type!\n");
                    goto end;
                }
            }
            break;
        }
    }

end:
    if (jpeg_flag == 3) { /* 3 scan header decoding success */
        jpegd_dec_sos_success(jpegd_hdl_ctx, tmp_dec_frame, quant_table_valid, huffman_table_valid, i);
        return HI_MJPEG_DEC_OK;
    } else {
        jpegd_dec_sos_failed(tmp_dec_frame);
        return HI_MJPEG_NO_PICTURE;
    }
}

/* create a JPEG decoder handle */
jpegd_handle jpegd_get_handle(void)
{
    motion_jpeg_obj *mjpeg = &g_jpegd_ctx;
    int pic_size;

    mjpeg->max_width = JPEGD_MAX_WIDTH;
    mjpeg->max_height = JPEGD_MAX_HEIGHT;

    pic_size = mjpeg->max_width * mjpeg->max_height;
    mjpeg->buf_size = pic_size + 0x10000; /* 0x10000:extra mem */
    mjpeg->stream_buffer = NULL;
    mjpeg->pic_buffer = NULL;
    mjpeg->valid_frame = 0;
    mjpeg->width_in_mcu = 1;
    mjpeg->height_in_mcu = 0;
    mjpeg->y_stride = 0;
    mjpeg->c_stride = 0;
    mjpeg->pic_format = PICTURE_FORMAT_BUTT;
    mjpeg->first_mcu = 0;
    mjpeg->bits.bit_len = 0;
    mjpeg->bits.bit_offset = 0;
    mjpeg->bits.buffer = NULL;
    mjpeg->frame.nf = 0;
    mjpeg->frame.y_height = 0;
    mjpeg->frame.y_width = 0;
    mjpeg->frame.restart_interval = 0;
    mjpeg->frame.restart_interval_logic = 0;
    mjpeg->frame.max_mcu_number = 0;

    init_default_huffman_table(mjpeg);
    init_default_quant_table(mjpeg);

    mjpeg->state = STATE_IDLE;

    return (jpegd_handle)mjpeg;
}

void jpegd_config_huffman_dc(motion_jpeg_obj *jpeg_hdl_ctx, unsigned int *huffman_table, unsigned int cs)
{
    huffman_tab *huf_tab = &jpeg_hdl_ctx->h_tab[cs];
    unsigned int i, num, j, index;
    for (index = 0, i = 0; i < JPEGD_CODE_LEN; i++) {
        num = huf_tab->len[i];
        for (j = 0; (j < num) && (index < 12); j++, index++) { /* 12 max index */
            int pos = huf_tab->huffman_val[index];
            if (cs == 1) {
                huffman_table[pos] |= ((i + 1) << 20) + /* shift left 20 bits 0xFF000:overflow protection */
                (((j + (unsigned int)huf_tab->min_code[i]) << 12) & 0xFF000); /* shift left 12 bits */
            } else {
                huffman_table[pos] |=
                ((i + 1) << 8) + ((j + (unsigned int)huf_tab->min_code[i]) & 0xFF); /* shift left 8 bits */
            }
        }
    }
    return;
}

void jpegd_config_huffman_ac(motion_jpeg_obj *jpeg_hdl_ctx, unsigned char *ac_min_table,
    unsigned char *ac_base_table, unsigned int idx)
{
    huffman_tab *huf_tab = &jpeg_hdl_ctx->h_tab[idx];
    int i;

    for (i = 0; i < JPEGD_CODE_LEN; i++) {
        unsigned int base_code = 0;

        if (huf_tab->len[i]) {
            base_code = huf_tab->huffman_val_ptr[i] - huf_tab->min_code[i];
        }

        ac_min_table[i] = ((unsigned int)huf_tab->min_code[i]) & 0xFF; /* 0xFF:get low 8 bits */
        ac_base_table[i] = base_code & 0xFF; /* 0xFF:get low 8 bits */
    }
    return;
}

void jpegd_config_huffman_table(motion_jpeg_obj *jpeg_hdl_ctx)
{
    unsigned int i;
    unsigned int huffman_table[HDC_TABLE_SIZE] = {0};
    unsigned char luma_ac_min_table[JPEGD_CODE_LEN]    = {0};
    unsigned char luma_ac_base_table[JPEGD_CODE_LEN]   = {0};
    unsigned char chroma_ac_min_table[JPEGD_CODE_LEN]  = {0};
    unsigned char chroma_ac_base_table[JPEGD_CODE_LEN] = {0};

    /* config huffman dc */
    jpegd_config_huffman_dc(jpeg_hdl_ctx, huffman_table, 1);
    jpegd_config_huffman_dc(jpeg_hdl_ctx, huffman_table, 0);

    /* config huffman ac */
    jpegd_config_huffman_ac(jpeg_hdl_ctx, luma_ac_min_table, luma_ac_base_table, 2); /* 2:table index */
    jpegd_config_huffman_ac(jpeg_hdl_ctx, chroma_ac_min_table, chroma_ac_base_table, 3); /* 3:table index */

    /* config huffman table */
    for (i = 0; i < HDC_TABLE_SIZE; i++) {
        jpeg_hdl_ctx->vpu_config.huffman_table[i] = huffman_table[i];
    }

    /* config huffman_min_table table */
    for (i = 0; i < HAC_MIN_TABLE_SIZE; i++) {
        jpeg_hdl_ctx->vpu_config.huffman_min_table[i] =
            (chroma_ac_min_table[2 * i + 1] << 24) + /* 2 config chroma ac table shift left 24 bits */
            (chroma_ac_min_table[2 * i] << 16) + /* 2 config chroma ac table shift left 16 bits */
            (luma_ac_min_table[2 * i + 1] << 8) + /* 2 config luma ac table shift left 8 bits */
            (luma_ac_min_table[2 * i]); /* 2 config luma ac min table */
    }

    /* config huffman_base_table table */
    for (i = 0; i < HAC_BASE_TABLE_SIZE; i++) {
        jpeg_hdl_ctx->vpu_config.huffman_base_table[i] =
            (chroma_ac_base_table[2 * i + 1] << 24) + /* 2 config chroma ac base table shift left 24 bits */
            (chroma_ac_base_table[2 * i] << 16) + /* 2 config chroma ac base table shift left 16 bits */
            (luma_ac_base_table[2 * i + 1] << 8) + /* 2 config luma ac base table shift left 8 bits */
            (luma_ac_base_table[2 * i]); /* 2 config luma ac base table */
    }

    /* config huffman_symbol_table table */
    for (i = 0; i < HAC_SYMBOL_TABLE_SIZE; i++) {
        jpeg_hdl_ctx->vpu_config.huffman_symbol_table[i] =
            (jpeg_hdl_ctx->h_tab[3].huffman_val[i] << 8) + /* table 3 shift left 8 bits */
            jpeg_hdl_ctx->h_tab[2].huffman_val[i]; /* plus table 2 */
    }
    return;
}

void jpegd_config_quant_table(motion_jpeg_obj *jpeg_hdl_ctx)
{
    unsigned int i;
    unsigned int q_tab_y_index = jpeg_hdl_ctx->frame.tq[COM0] & 3; /* 3 overflow protection */
    unsigned int q_tab_u_index = jpeg_hdl_ctx->frame.tq[COM1] & 3; /* 3 overflow protection */
    unsigned int q_tab_v_index = jpeg_hdl_ctx->frame.tq[COM2] & 3; /* 3 overflow protection */

    unsigned char *q_cr = (unsigned char *)&jpeg_hdl_ctx->q_tab[q_tab_v_index];
    unsigned char *q_cb = (unsigned char *)&jpeg_hdl_ctx->q_tab[q_tab_u_index];
    unsigned char *q_y = (unsigned char *)&jpeg_hdl_ctx->q_tab[q_tab_y_index];
    int pos;

    for (i = 0; i < QUANT_TABLE_SIZE; i++) {
        pos = g_zigzag_for_qtable[i & 0x3f]; /* 0x3f:get low 6bits */
        jpeg_hdl_ctx->vpu_config.quant_table[pos] =
            q_y[i] + (q_cb[i] << 8) + (q_cr[i] << 16); /* shift left 8 bits shift left 16 bits */
    }

    return;
}

void jpegd_config_rgb_info(motion_jpeg_obj *jpeg_hdl_ctx)
{
    if (jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_YVU_SEMIPLANAR_420) {
        jpeg_hdl_ctx->vpu_config.out_yuv = HI_TRUE;
    } else {
        jpeg_hdl_ctx->vpu_config.out_yuv = HI_FALSE;
        if ((jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_ARGB_8888) ||
            (jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_ABGR_8888)) {
            jpeg_hdl_ctx->vpu_config.rgb_stride = align_up(jpeg_hdl_ctx->frame.y_width * 4, 16); /* 4,16 align up */
        } else if ((jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_ARGB_1555) ||
                   (jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_ABGR_1555)) {
            jpeg_hdl_ctx->vpu_config.rgb_stride = align_up(jpeg_hdl_ctx->frame.y_width * 2, 16); /* 2,16 align up */
        } else if ((jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_RGB_888) ||
                   (jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_BGR_888)) {
            jpeg_hdl_ctx->vpu_config.rgb_stride = align_up(jpeg_hdl_ctx->frame.y_width * 3, 16); /* 3,16 align up */
        } else if ((jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_RGB_565) ||
                   (jpeg_hdl_ctx->vpu_config.pixel_format == PIXEL_FORMAT_BGR_565)) {
            jpeg_hdl_ctx->vpu_config.rgb_stride = align_up(jpeg_hdl_ctx->frame.y_width * 2, 16); /* 2,16 align up */
        }
    }
    return;
}

unsigned int jpegd_prepare_pic_type(picture_format pic_format)
{
    unsigned int pic_type = 0;
    switch (pic_format) {
        case PICTURE_FORMAT_YUV420:
            pic_type = 3; /* 3: value of hardware regulation */
            break;
        case PICTURE_FORMAT_YUV422:
            pic_type = 4; /* 4: value of hardware regulation */
            break;
        case PICTURE_FORMAT_YUV444:
            pic_type = 6; /* 6: value of hardware regulation */
            break;
        case PICTURE_FORMAT_YUV422V:
            pic_type = 5; /* 5: value of hardware regulation */
            break;
        case PICTURE_FORMAT_YUV400:
            pic_type = 0; /* 0: value of hardware regulation */
            break;
        default:
            printf("Unkonwn picture format %d!", pic_format);
    }
    return pic_type;
}

/* Prepare the jpegd Hardware Info */
int jpegd_prepare_hardware_info(motion_jpeg_obj *jpeg_hdl_ctx)
{
    unsigned int ysize;

    ysize = align_up(jpeg_hdl_ctx->frame.y_width, 64) * /* 64 align up */
        align_up(jpeg_hdl_ctx->frame.y_height, 16); /* 16 align up */
    jpeg_hdl_ctx->vpu_config.width = jpeg_hdl_ctx->frame.y_width;
    jpeg_hdl_ctx->vpu_config.height = jpeg_hdl_ctx->frame.y_height;
    jpeg_hdl_ctx->vpu_config.width_in_mcu = jpeg_hdl_ctx->width_in_mcu;
    jpeg_hdl_ctx->vpu_config.height_in_mcu = jpeg_hdl_ctx->height_in_mcu;
    jpeg_hdl_ctx->vpu_config.c_phy_addr = jpeg_hdl_ctx->vpu_config.y_phy_addr + ysize;
    jpeg_hdl_ctx->vpu_config.y_stride = align_up(jpeg_hdl_ctx->frame.y_width, 64); /* 64 align up */
    jpeg_hdl_ctx->vpu_config.c_stride = align_up(jpeg_hdl_ctx->frame.y_width, 64); /* 64 align up */
    jpeg_hdl_ctx->vpu_config.phy_str_start = jpeg_hdl_ctx->vpu_config.phy_str_start + jpeg_hdl_ctx->stream_offest;
    jpeg_hdl_ctx->vpu_config.y_fac = jpeg_hdl_ctx->frame.h[0];
    jpeg_hdl_ctx->vpu_config.u_fac = jpeg_hdl_ctx->frame.h[1];
    jpeg_hdl_ctx->vpu_config.v_fac = jpeg_hdl_ctx->frame.h[2]; /* 2 array index */
    jpeg_hdl_ctx->vpu_config.dri = jpeg_hdl_ctx->frame.restart_interval_logic;
    jpeg_hdl_ctx->vpu_config.pic_format = jpeg_hdl_ctx->pic_format;
    jpeg_hdl_ctx->vpu_config.pic_type = jpegd_prepare_pic_type(jpeg_hdl_ctx->vpu_config.pic_format);

    /* config RGB info */
    jpegd_config_rgb_info(jpeg_hdl_ctx);

    /* config quant table */
    jpegd_config_quant_table(jpeg_hdl_ctx);

    /* config huffman table */
    jpegd_config_huffman_table(jpeg_hdl_ctx);

    return HI_SUCCESS;
}

int jpegd_start_one_frame(jpegd_handle handle, unsigned int flags)
{
    int ret;
    motion_jpeg_obj *jpegd_hdl_ctx = (motion_jpeg_obj *)handle;

    ret = jpegd_dec_frame(handle, flags);
    if (ret != HI_SUCCESS) {
        hi_trace("vdec_start_one_frame: decode stream fail for 0x%x\n", ret);
        return ret;
    }

    ret = jpegd_prepare_hardware_info(jpegd_hdl_ctx);
    if (ret != HI_SUCCESS) {
        hi_trace("vdec_start_one_frame: decode stream fail for 0x%x\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

/* write the jpegd register */
void jpegd_write_regs(jpegd_handle handle, S_JPGD_REGS_TYPE *reg_base)
{
    motion_jpeg_obj *jpeg_hdl_ctx = (motion_jpeg_obj *)handle;

    jpegd_drv_write_regs(reg_base, &jpeg_hdl_ctx->vpu_config);
    return;
}

/* read the jpegd register */
void jpegd_read_regs(jpegd_handle handle, S_JPGD_REGS_TYPE *reg_base)
{
    motion_jpeg_obj *jpeg_hdl_ctx = (motion_jpeg_obj *)handle;

    jpegd_drv_read_regs(reg_base, &jpeg_hdl_ctx->vpu_status);
    return;
}

int jpegd_start_decoding(jpegd_handle handle)
{
    motion_jpeg_obj *jpegd_hld_ctx = NULL;
    int ret;

    jpegd_hld_ctx = (motion_jpeg_obj *)handle;
    jpegd_hld_ctx->vpu_config.y_phy_addr = get_video_data_base();
    jpegd_hld_ctx->vpu_config.phy_str_buf_start = get_hilogo();
    jpegd_hld_ctx->vpu_config.phy_str_buf_end = get_hilogo() + align_up(get_jpeg_size_val(), 128); /* 128 align up */
    jpegd_hld_ctx->vpu_config.phy_str_start = get_hilogo();
    jpegd_hld_ctx->vpu_config.phy_str_end = get_hilogo() + get_jpeg_size_val();
    jpegd_hld_ctx->vpu_config.phy_emar_buffer0 = get_jpegd_emar_buf();
    jpegd_hld_ctx->vpu_config.phy_emar_buffer1 = get_jpegd_emar_buf() + ONE_EMAR_BUF_SIZE;
    jpegd_hld_ctx->stream.vir_addr = (unsigned char *)(uintptr_t)get_hilogo();
    jpegd_hld_ctx->stream.len = get_jpeg_size_val();
    jpegd_hld_ctx->stream.phy_addr = get_hilogo();
    jpegd_hld_ctx->stream.pts = 0;
    jpegd_hld_ctx->vpu_config.chn_id = 0;
    jpegd_hld_ctx->vpu_config.alpha = 255; /* 255 transparency */

    if (get_output_format() == 0) {
        jpegd_hld_ctx->vpu_config.pixel_format = PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    } else if (get_output_format() == 1) {
        jpegd_hld_ctx->vpu_config.pixel_format = PIXEL_FORMAT_ARGB_1555;
    } else if (get_output_format() == 2) { /* 2 output format */
        jpegd_hld_ctx->vpu_config.pixel_format = PIXEL_FORMAT_ARGB_8888;
    } else {
        jpegd_hld_ctx->vpu_config.pixel_format = PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    }

    ret = jpegd_start_one_frame(handle, 0);
    if (ret != HI_SUCCESS) {
        hi_trace("jpegd_start_decoding: decode stream fail for 0x%x\n", ret);
        return ret;
    }

    jpegd_set_clock_en(0, HI_TRUE);
    jpegd_reset(0);
    jpegd_set_time_out(0, 0xFFFFFFFF); /* 0xFFFFFFFF:time out value */

    jpegd_write_regs(handle, (S_JPGD_REGS_TYPE *)JPEGD_REGS_ADDR);

    jpegd_start_vpu(0);

    return HI_SUCCESS;
}

void jpegd_finish_decoding(jpegd_handle handle)
{
    unsigned int int_statue;
    unsigned int cnt = 0;
    motion_jpeg_obj *jpegd_hld_ctx = (motion_jpeg_obj *)handle;

    while (1) {
        udelay(10); /* 10 delay time */
        int_statue = jpegd_read_int(0);
        if (int_statue & 0x1f) {
            break;
        }
        if (cnt++ > 2000) { /* 2000:Maximum decoding time */
            hi_trace("jpeg decode over time\n");
            break;
        }
    }

    jpegd_read_regs(handle, (S_JPGD_REGS_TYPE *)JPEGD_REGS_ADDR);
    if (jpegd_hld_ctx->vpu_status.int_dec_finish == 0) {
        printf("hardware decoding error!\n");
    } else {
        if (jpegd_hld_ctx->vpu_config.out_yuv != HI_TRUE) {
            printf("hardware decoding success! %ux%u, stride %u.\n",
                   jpegd_hld_ctx->frame.y_width, jpegd_hld_ctx->frame.y_height, jpegd_hld_ctx->vpu_config.rgb_stride);
        } else {
            printf("hardware decoding success! %ux%u, stride %u.\n",
                   jpegd_hld_ctx->frame.y_width, jpegd_hld_ctx->frame.y_height, jpegd_hld_ctx->vpu_config.y_stride);
        }
    }

    jpegd_clear_int(0);
    jpegd_reset_select(0, HI_TRUE);

    return;
}

