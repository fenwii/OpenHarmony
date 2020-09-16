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
 * Description: jpegd image file.
 */
#include "jpegd_image.h"

static const unsigned char g_default_huffman_table[418] = { 0x01, 0xA2,    /* 418 :huffman_table size */
    /* table K.3 - table for luminance DC coefficient differences */
    0x00,
    0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0A, 0x0B,

    /* table K.4 - table for chrominance DC coefficient differences */
    0x01,
    0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0A, 0x0B,

    /* table K.5 - table for luminance AC coefficients */
    0x10,
    0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7D,
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5,
    0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
    0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA,

    /* table K.6 - table for chrominance AC coefficients */
    0x11,
    0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77,
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0,
    0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26,
    0x27, 0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5,
    0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
    0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,
    0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA,
};

static const unsigned char g_default_quant_table[160] = { 0x00, 0x84,    /* 160 :quant_table size */
    /* table K.1 - luminance quantization table */
    0x00,
    16,  11,  12,  14,  12,  10,  16,  14,  13,  14,  18,  17,  16,  19,  24,  40,
    26,  24,  22,  22,  24,  49,  35,  37,  29,  40,  58,  51,  61,  60,  57,  51,
    56,  55,  64,  72,  92,  78,  64,  68,  87,  69,  55,  56,  80, 109,  81,  87,
    95,  98, 103, 104, 103,  62,  77, 113, 121, 112, 100, 120,  92, 101, 103,  99,

    /* table K.2 - chrominance quantization table */
    0x01,
    17, 18, 18, 24, 21, 24, 47, 26, 26, 47, 99, 66, 56, 66, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
};

unsigned int jpegd_decode_dht_huffman_length(huffman_tab *huffman, const unsigned char **str,
    unsigned char *ptr, unsigned int *error_flag)
{
    unsigned int i, tab_len;
    int max_code = 0;
    const unsigned char *stream = *str;
    for (i = 0, tab_len = 0; i < JPEGD_CODE_LEN; i++) {
        ptr[i] = *stream++;

        if (ptr[i]) {
            huffman->min_code[i] = (unsigned int)(max_code) << 1;
            huffman->max_code[i] = huffman->min_code[i] + ptr[i] - 1;
            huffman->max_code16[i] =
                ((unsigned int)(huffman->max_code[i] + 1) << (15 - i)) - 1; /* 16bit maximum shift left number15 */
            huffman->len[i] = ptr[i];
            huffman->huffman_val_ptr[i] = tab_len;
            max_code = huffman->max_code[i] + 1;
            *error_flag |= (unsigned int)((huffman->max_code[i] + 1) > (1 << (i + 1)));
        } else {
            huffman->min_code[i] = (unsigned int)max_code << 1;
            huffman->max_code[i] = -1;
            huffman->max_code16[i] = -1;
            huffman->len[i] = 0;
            huffman->huffman_val_ptr[i] = tab_len;
            max_code = (unsigned int)max_code << 1;
        }
        tab_len += ptr[i];
    }
    huffman->max_code16[JPEGD_CODE_LEN - 1] = 0x0000ffff; /* 0x0000ffff:default value */
    huffman->max_code[JPEGD_CODE_LEN - 1] = huffman->min_code[JPEGD_CODE_LEN - 1] + ptr[JPEGD_CODE_LEN - 1] - 1;
    *str += JPEGD_CODE_LEN;
    return tab_len;
}

void jpegd_decode_dht_huffman_val(huffman_tab *huffman, const unsigned char **str, const unsigned char *ptr,
    unsigned int tab_len)
{
    unsigned int i;
    unsigned int ii = 0;
    unsigned int jj;
    const unsigned char *stream = *str;
    for (i = 0; i < sizeof(huffman->huffman_val); i++) {
        huffman->huffman_val[i] = 0;
    }
    for (i = 0; (i < tab_len) && (i < JPEGD_HUFFMAN_LEN); i++) {
        huffman->huffman_val[i] = *stream++;
    }

    for (i = 0, jj = 0; i < 8; i++) { /* finds the first 8 codes when Lookup table */
        for (ii = 0; ii < ptr[i]; ii++) {
            int count = 1 << (7 - i); /* 7:finds the first 8 codes when Lookup table */
            unsigned char huffmancode = huffman->huffman_val[huffman->huffman_val_ptr[i] + ii];
            while ((count-- != 0) && (jj < JPEGD_HUFFMAN_LEN)) {
                huffman->fast_huffman_len[jj] = i + 1;
                huffman->fast_huffman_code[jj++] = huffmancode;
            }
        }
    }
    huffman->u_code32 = (jj - 1) << 24; /* Extended 32 bit, set 0 to low 24 bits */
    *str += tab_len;
    return;
}

int decode_dht(motion_jpeg_obj *mjpeg, const unsigned char *stream)
{
    huffman_tab *huffman = &mjpeg->huffman_tmp;
    unsigned int error_flag = 0;
    unsigned int tab_len;
    unsigned char ptr[JPEGD_CODE_LEN];
    unsigned int k = 2; /* 2:DHT maker takes 2 bytes */
    unsigned int lh;
    unsigned char code, tc, th;

    lh = (stream[0] << 8) + stream[1]; /* 0,1:The first two bytes are dht length, shift left 8 bits */
    stream += 2; /* Data length is 2 bytes */

    while (k < lh) {
        code = *stream++;
        tc = (code >> 4) & 0x1; /* get top 4 bits 0x1:get 0 bit value */
        th = code & 0x1; /* 0x1:get 0 bit value */
        error_flag |= (unsigned int)(code & 0xEE); /* 0xEE:lh max value */
        if (error_flag != 0) {
            return HI_JPEG_DEC_DHT_ERR;
        }
        tab_len = jpegd_decode_dht_huffman_length(huffman, &stream, ptr, &error_flag);
        k += 17 + tab_len; /* 17:tc and th take one byte, length take 16 bytes */
        error_flag |= (unsigned int)(tab_len > 255); /* 255 max table length */
        if ((k > lh) || error_flag) {
            return HI_JPEG_DEC_DHT_ERR;
        }

        jpegd_decode_dht_huffman_val(huffman, &stream, ptr, tab_len);
        mjpeg->h_tab[(tc << 1) + th] = *huffman;
    }

    return HI_JPEG_DEC_OK;
}

unsigned int check_sof_bit(frame_header *header, motion_jpeg_obj *mjpeg, int ls)
{
    if (header->color_depth != 8) { /* only support 8 sample precision */
        return HI_ERR_NOT_BASELINE;
    }

    if (ls != (header->nf * 3 + 8)) { /* every components takes 3 bytes, previous info take 8 bytes */
        return HI_ERR_FRAME_HEADER;
    }

    if ((header->y_height > mjpeg->max_height) || (header->y_height == 0)) {
        return HI_UNSUPPORT_PIC_SIZE;
    }

    if ((header->y_width > mjpeg->max_width) || (header->y_width == 0)) {
        return HI_UNSUPPORT_PIC_SIZE;
    }
    if ((header->nf != 3) && (header->nf != 1)) { /* number of components in frame can be 1 or 3 */
        return HI_UNSUPPORT_PIC_STRUCT;
    }
    return HI_SUCCESS;
}

unsigned int check_sof_component_bit(frame_header *header, motion_jpeg_obj *mjpeg)
{
    if (header->nf == 1) {
        if (header->h[COM0] != 0x11) { /* 0x11: only support H = V = 1 */
            return HI_UNSUPPORT_PIC_STRUCT;
        }
        if (header->tq[COM0] & 0xfc) { /* 0xfc: tq range[0, 3] */
            return HI_UNSUPPORT_PIC_STRUCT;
        }
    } else {
         /* 0xfc: tq range[0, 3] */
        if ((header->tq[COM0] & 0xfc) || (header->tq[COM1] & 0xfc) || (header->tq[COM2] & 0xfc)) {
            return HI_ERR_NOT_BASELINE;
        }
         /* 0x41:not support H=4,V=1, 0x14:not support H=1, V=4 */
        if ((header->h[COM0] == 0x41) || (header->h[COM0] == 0x14)) {
            return HI_UNSUPPORT_YUV411;
        }

        if ((header->h[COM1] != 0x11) || (header->h[COM2] != 0x11)) { /* 0x11: chroma component H = V = 1 */
            return HI_UNSUPPORT_PIC_STRUCT;
        }
    }
    return HI_SUCCESS;
}

unsigned int get_sof_pic_format(frame_header *header, motion_jpeg_obj *mjpeg)
{
    if (header->nf == 1) {
        mjpeg->width_in_mcu = (header->y_width + 7) >> 3; /* 7 3 each mcu is a DU */
        mjpeg->height_in_mcu = (header->y_height + 7) >> 3; /* 7 3 each mcu is a DU */
        mjpeg->y_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
        mjpeg->pic_format = PICTURE_FORMAT_YUV400;  /* YUV100 */
    } else {
        if (header->h[0] == 0x11) { /* 0x11: only support H = V = 1 */
            mjpeg->width_in_mcu = (header->y_width + 7) >> 3; /* 7 3 each mcu is a DU */
            mjpeg->height_in_mcu = (header->y_height + 7) >> 3; /* 7 3 each mcu is a DU */
            mjpeg->y_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
            mjpeg->c_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
            mjpeg->pic_format = PICTURE_FORMAT_YUV444;  /* YUV111 */
        } else if (header->h[0] == 0x22) { /* 0x22: only support H = V = 2 */
            mjpeg->width_in_mcu = (header->y_width + 15) >> 4; /* 15 4 2 DU wide for each mcu */
            mjpeg->height_in_mcu = (header->y_height + 15) >> 4; /* 15 4 2 DU height for each mcu */
            mjpeg->y_stride = mjpeg->width_in_mcu << 4; /* 4: 2 DU wide for each mcu */
            mjpeg->c_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
            mjpeg->pic_format = PICTURE_FORMAT_YUV420;  /* YUV420 */
        } else if (header->h[0] == 0x21) { /* 0x21:support H=2,V=1 */
            mjpeg->width_in_mcu = (header->y_width + 15) >> 4; /* 15 4 2 DU wide for each mcu */
            mjpeg->height_in_mcu = (header->y_height + 7) >> 3; /* 7 3 each mcu is a DU */
            mjpeg->y_stride = mjpeg->width_in_mcu << 4; /* 4: 2 DU wide for each mcu */
            mjpeg->c_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
            mjpeg->pic_format = PICTURE_FORMAT_YUV422;  /* YUV422 */
        } else if (header->h[0] == 0x12) { /* 0x12:support H=2,V=1 */
            mjpeg->width_in_mcu = (header->y_width + 7) >> 3; /* 7 3 each mcu is a DU */
            mjpeg->height_in_mcu = (header->y_height + 15) >> 4; /* 15 4 2 DU height for each mcu */
            mjpeg->y_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
            mjpeg->c_stride = mjpeg->width_in_mcu << 3; /* 3: each mcu is a DU */
            mjpeg->pic_format = PICTURE_FORMAT_YUV422V;
        } else {
            mjpeg->pic_format = PICTURE_FORMAT_BUTT;  /* do not support */
            return HI_UNSUPPORT_PIC_STRUCT;
        }
    }
    return HI_SUCCESS;
}

int decode_sof0(motion_jpeg_obj *mjpeg, const unsigned char *stream)  /* 0xFF C0 */
{
    unsigned int error_flag;
    frame_header header = {0};
    int ls;
    int i = 0;

    ls = (stream[0] << 8) + stream[1]; /* 0,1:The first two bytes are SOF length, shift left 8 bits */
    header.color_depth = stream[2]; /* 2: Sample precision */
    header.y_height = (stream[3] << 8) + stream[4]; /* 3,4,8:get height */
    header.y_width = (stream[5] << 8) + stream[6]; /* 5,6,8:get width */
    header.nf = stream[7]; /* 7:number of components in frame */
    stream += 8; /* 8:bit number */
    error_flag = check_sof_bit(&header, mjpeg, ls);
    if (error_flag != HI_SUCCESS) {
        hi_trace("CheckSOFBit error:0x%x!\n", error_flag);
        return error_flag;
    }

    header.ci[0] = stream[i++];
    header.h[0] = stream[i++];
    header.tq[0] = stream[i++]; /* 2 array index */

    if (header.nf == 3) { /* 3 number of components in frame */
        header.ci[1] = stream[i++]; /* 3 array index */
        header.h[1] = stream[i++]; /* 4 array index */
        header.tq[1] = stream[i++]; /* 5 array index */
        header.ci[2] = stream[i++]; /* 2 6 array index */
        header.h[2] = stream[i++]; /* 2 7 array index */
        header.tq[2] = stream[i++]; /* 2 8 array index */
    }
    error_flag = check_sof_component_bit(&header, mjpeg);
    if (error_flag != HI_SUCCESS) {
        hi_trace("check_sof_component_bit error:0x%x!\n", error_flag);
        return error_flag;
    }
    error_flag = get_sof_pic_format(&header, mjpeg);
    if (error_flag != HI_SUCCESS) {
        hi_trace("decode_sof_pic_format error:0x%x!\n", error_flag);
        return error_flag;
    }
    header.max_mcu_number = mjpeg->width_in_mcu * mjpeg->height_in_mcu;
    header.restart_interval_logic = mjpeg->frame.restart_interval;
    header.restart_interval = (mjpeg->frame.restart_interval != 0) ?
        mjpeg->frame.restart_interval : header.max_mcu_number;
    mjpeg->frame = header;
    return HI_JPEG_DEC_OK;
}

int check_sos_bit(motion_jpeg_obj *mjpeg, scan_header *scan, unsigned int index)
{
    frame_header *fh = &mjpeg->frame;
    if (scan->cs[index] != fh->ci[index]) {
        return HI_ERR_SCAN_HEADER;
    }
    if (scan->td[index] > 1 || scan->ta[index] > 1) {
        return HI_ERR_NOT_BASELINE;
    }
    return HI_SUCCESS;
}

int decode_sos(motion_jpeg_obj *mjpeg, unsigned char *stream)  /* 0xFF DA */
{
    unsigned int error_flag = 0;
    scan_header scan;
    unsigned char code;
    unsigned int i;
    frame_header *fh = &mjpeg->frame;
    unsigned int ls = (stream[0] << 8) + stream[1]; /* 0,1:The first two bytes are SOF length, shift left 8 bits */
    unsigned int ns = stream[2]; /* 2:number of components in frame */
    stream += 3; /* 3 ls and ns 's number of bytes */

    if (ns != fh->nf || ls != ns * 2 + 6 || ns > 4) { /* 2:cs takes 1 byte, td and ta each take 4 bits, else take 6 */
        return HI_ERR_SCAN_HEADER;
    }

    for (i = 0; (i < ns) && (error_flag == 0); i++) {
        scan.cs[i] = *stream++;
        code = *stream++;
        scan.td[i] = code >> 4; /* the top 4 bits are ah */
        scan.ta[i] = code & 0xf; /* 0xf:get low 4 bits */
        if (i < 3) { /* 3 number of components in frame */
            mjpeg->q_tab_components[i] = &mjpeg->q_tab[(3 & fh->tq[i])]; /* 3 get low 2 bits */
            mjpeg->h_tab_components_dc[i] = &mjpeg->h_tab[(1 & scan.td[i])];
            mjpeg->h_tab_components_ac[i] =
                &mjpeg->h_tab[2 + (1 & scan.ta[i])]; /* 2 each dc and ac take half of huffman table */
        }

        error_flag = check_sos_bit(mjpeg, &scan, i);
        if (error_flag != HI_SUCCESS) {
            hi_trace("check_sos_bit0 err:0x%x\n", error_flag);
            return error_flag;
        }
    }
    scan.ns = ns;
    scan.ss = *stream++;
    scan.se = *stream++;
    code = *stream++;
    scan.ah = code >> 4; /* the top 4 bits are ah */
    scan.al = code & 0xf; /* 0xf:get low 4 bits */

    if ((scan.ss != 0) || (scan.se != 63) || (scan.ah != 0) || (scan.al != 0)) { /* baseline se must be 63 */
        return HI_ERR_NOT_BASELINE;
    }

    if (error_flag == 0) {
        mjpeg->scan = scan;
        return HI_JPEG_DEC_OK;
    } else {
        return HI_JPEG_DEC_SCAN_ERR;
    }
}

int decode_dri(motion_jpeg_obj *mjpeg, const unsigned char *stream)
{
    int lr = (stream[0] << 8) + stream[1]; /* 8:shift left */
    int ri = (stream[2] << 8) + stream[3]; /* 2,3:array index 8:shift left */

    if (lr != 4) { /* DRI data length is 4 */
        return 1;
    }

    mjpeg->frame.restart_interval = ri;
    mjpeg->frame.restart_interval_logic = ri;

    if (mjpeg->frame.max_mcu_number == 0) {
        mjpeg->frame.restart_interval = ri;
    } else {
        mjpeg->frame.restart_interval = (ri == 0) ? mjpeg->frame.max_mcu_number : ri;
    }

    return 0;
}

int decode_dqt(motion_jpeg_obj *mjpeg, const unsigned char *stream)
{
    unsigned int error_flag = 0;
    unsigned char *quant = NULL;
    unsigned int i, code, pq, tq;
    int k = 2;
    int lq = (stream[0] << 8) + stream[1]; /* 0,1:The first two bytes are DQT length, shift left 8 bits */
    stream += 2; /* 2: data length */

    while ((k < lq) && (error_flag == 0)) {
        k += 65; /* 65 jpegd quant length(64) + 1 */
        code = *stream++;
        pq = code >> 4; /* pq:top 4 bits */
        tq = code & 0xf; /* 0xf:get low 4 bits */
        error_flag |= (unsigned int)(pq != 0);  /* pq must be 0 in baseline */
        error_flag |= (unsigned int)(tq > 3);  /* tq should be (0 ~ 3), inclusive */
        error_flag |= (unsigned int)(k > lq);
        if (error_flag) {
            return HI_JPEG_DEC_FRAME_ERR;
        }

        quant = mjpeg->q_tab[tq & 3].quant; /* 3:Prevent decoding errors and array overflow */
        for (i = 0; i < 64; i++) { /* 64 jpegd quant length */
            quant[i] = *stream++;
        }
    }
    return 0;
}

void init_default_huffman_table(motion_jpeg_obj *mjpeg)
{
    int ret;
    ret = decode_dht(mjpeg, g_default_huffman_table);
    if (ret != HI_JPEG_DEC_OK) {
        hi_trace("jpeg decode DHT error!\n");
    }
}

void init_default_quant_table(motion_jpeg_obj *mjpeg)
{
    int ret;
    ret = decode_dqt(mjpeg, g_default_quant_table);
    if (ret != 0) {
        hi_trace("jpeg decode DQT error!\n");
    }
}

