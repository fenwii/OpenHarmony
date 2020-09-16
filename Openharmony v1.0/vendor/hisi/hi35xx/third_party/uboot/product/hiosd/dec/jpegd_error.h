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
 * Description: jpegd error header file.
 */
#ifndef __JPEGD_ERROR_H__
#define __JPEGD_ERROR_H__

#include <common.h>

/* for SOF error */
#define HI_ERR_NOT_BASELINE        0x00000001
#define HI_UNSUPPORT_GRAY_PIC      0x00000002
#define HI_UNSUPPORT_PIC_SIZE      0x00000004
#define HI_UNSUPPORT_PIC_STRUCT    0x00000008
#define HI_UNSUPPORT_YUV411        0x00000010

#define HI_ERR_QUANT_TABLE         0x00000020
#define HI_ERR_HUFFMAN_TABLE       0x00000040
#define HI_ERR_FRAME_HEADER        0x00000080
#define HI_ERR_SCAN_HEADER         0x00000100
#define HI_ERR_RESTART_ERROR       0x00000200
#define HI_ERR_UNSUPPORT_DNL       0x00000400

#define hi_trace(fmt...)                             \
    do {                                             \
        printf("[%s]-%d: ", __FUNCTION__, __LINE__); \
        printf(fmt);                                 \
    } while (0)

#endif /* End of __JPEGD_ERROR_H__ */