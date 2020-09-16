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

#include "hdmi_osal.h"
#include "hi_osal.h"
#include "hdmi_product_define.h"

struct file* hdmi_osal_file_open(const hi_char *file_name, osal_file_flag flags)
{
    struct file *file = NULL;

    if (file_name == HI_NULL) {
        return HI_NULL;
    }

    flags = HDMI_O_RDWR | HDMI_O_CREAT;
    file = HDMI_FILP_OPEN(file_name, flags, HDMI_FILE_MODE);

    return file;
}

hi_void hdmi_osal_file_close(struct file *file)
{
    if (file != HI_NULL) {
        HDMI_FILP_CLOSE(file);
    }

    return;
}

hi_s32 hdmi_osal_file_read(struct file *file, hi_char *buf, hi_u32 len)
{
    hi_s32 read_len;

    if (buf == HI_NULL) {
        return 0;
    }

    read_len = HDMI_FILP_READ(buf, len, file);

    return read_len;
}

hi_s32 hdmi_osal_file_write(struct file *file, hi_char *buf, hi_u32 len)
{
    hi_s32 write_len;

    if (buf == HI_NULL) {
        return 0;
    }

    write_len = HDMI_FILP_FWRITE(buf, len, file);

    return write_len;
}

hi_u32 hdmi_osal_get_time_in_ms(hi_void)
{
    hi_u64 sys_time;

    sys_time = HDMI_DO_DIV64(HDMI_SCHED_LOCK(), 1000000);

    return (hi_u32)sys_time;
}


hi_u64 hdmi_osal_get_time_in_us(hi_void)
{
    hi_u64 curr_us;
    HDMI_TIMEVAL_S current_time;

    HDMI_GETTIMEOFDAY(&current_time);
    curr_us = ((hi_u64)current_time.tv_sec * 1000000 + current_time.tv_usec);

    return curr_us;
}

