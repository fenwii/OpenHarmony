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

#ifndef __HDMI_OSAL_H__
#define __HDMI_OSAL_H__

#include "hi_type.h"

typedef unsigned long hi_size_t;

typedef enum {
    OSAL_RDONLY, /* read file only */
    OSAL_WRONLY, /* write file only */
    OSAL_RDWR,   /* read and write file */
    OSAL_BUTT
} osal_file_flag;

#define IS_STR_EQUAL(p1, p2) ({ (((p1) != HI_NULL) && ((p2) != HI_NULL) && (HDMI_STRLEN(p1) == HDMI_STRLEN(p2)) && \
    (HDMI_STRNCMP(p1, p2, HDMI_STRLEN(p1)) == 0)) ? HI_TRUE : HI_FALSE;})

struct file *hdmi_osal_file_open(const hi_char *file_name, osal_file_flag flags);

hi_void hdmi_osal_file_close(struct file *file);

hi_s32 hdmi_osal_file_read(struct file *file,  hi_char *buf, hi_u32 len);

hi_s32 hdmi_osal_file_write(struct file *file, hi_char *buf, hi_u32 len);

hi_u32 hdmi_osal_get_time_in_ms(hi_void);

hi_u64 hdmi_osal_get_time_in_us(hi_void);

#endif

