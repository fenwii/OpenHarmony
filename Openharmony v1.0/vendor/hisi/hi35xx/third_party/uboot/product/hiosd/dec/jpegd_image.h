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
 * Description: jpegd image header file.
 */
#ifndef __JPEGD_IMAGE_H__
#define __JPEGD_IMAGE_H__
#include "jpegd.h"
#include "jpegd_error.h"

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

int decode_sof0(motion_jpeg_obj *mjpeg, const unsigned char *stream);
int decode_sos(motion_jpeg_obj *mjpeg, unsigned char *stream);
int decode_dht(motion_jpeg_obj *mjpeg, const unsigned char *stream);
int decode_dqt(motion_jpeg_obj *mjpeg, const unsigned char *stream);
int decode_dri(motion_jpeg_obj *mjpeg, const unsigned char *stream);
void init_default_huffman_table(motion_jpeg_obj *mjpeg);
void init_default_quant_table(motion_jpeg_obj *mjpeg);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif
