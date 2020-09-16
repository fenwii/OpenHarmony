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
#ifndef __BOOT_HDMI_INTF_H__
#define __BOOT_HDMI_INTF_H__

#include "hi_type.h"
#include "hdmi_hal.h"
#include "drv_hdmi_common.h"
#include "ubi_uboot.h"

#define hdmi_info(fmt...)
#define hdmi_warn(fmt...)
#define hdmi_err(fmt...)

#undef offsetof
#define offsetof(TYPE, MEMBER)    ((size_t)&((TYPE *)0)->MEMBER)

#undef container_of
#define container_of(ptr, type, member) ({             \
    const typeof(((type *)0)->member) *__mptr = (ptr); \
    (type *)((char *)__mptr - offsetof(type, member));})

#define HDMI_CONTAINER_OF  container_of

typedef struct {
    hi_u32 hdmi_dev_id;
    hdmi_tmds_mode tmds_mode;
    hdmi_attr attr;
    hdmi_infoframe_str infoframe;
    hdmi_hal *hal;
    hdmi_mode_param mode_param;
} hdmi_device;

typedef enum {
    VO_OUTPUT_PAL,
    VO_OUTPUT_NTSC,
    VO_OUTPUT_1080P24,
    VO_OUTPUT_1080P25,
    VO_OUTPUT_1080P30,
    VO_OUTPUT_720P50,
    VO_OUTPUT_720P60,
    VO_OUTPUT_1080I50,
    VO_OUTPUT_1080I60,
    VO_OUTPUT_1080P50,
    VO_OUTPUT_1080P60,
    VO_OUTPUT_576P50,
    VO_OUTPUT_480P60,
    VO_OUTPUT_800X600_60,
    VO_OUTPUT_1024X768_60,
    VO_OUTPUT_1280X1024_60,
    VO_OUTPUT_1366X768_60,
    VO_OUTPUT_1440X900_60,
    VO_OUTPUT_1280X800_60,
    VO_OUTPUT_1600X1200_60,
    VO_OUTPUT_1680X1050_60,
    VO_OUTPUT_1920X1200_60,
    VO_OUTPUT_640X480_60,
    VO_OUTPUT_960H_PAL,
    VO_OUTPUT_960H_NTSC,
    VO_OUTPUT_1920X2160_30,
    VO_OUTPUT_2560X1440_30,
    VO_OUTPUT_2560X1440_60,
    VO_OUTPUT_2560X1600_60,
    VO_OUTPUT_3840X2160_24,
    VO_OUTPUT_3840X2160_25,
    VO_OUTPUT_3840X2160_30,
    VO_OUTPUT_3840X2160_50,
    VO_OUTPUT_3840X2160_60,
    VO_OUTPUT_4096X2160_24,
    VO_OUTPUT_4096X2160_25,
    VO_OUTPUT_4096X2160_30,
    VO_OUTPUT_4096X2160_50,
    VO_OUTPUT_4096X2160_60,
    VO_OUTPUT_320X240_60,
    VO_OUTPUT_320X240_50,
    VO_OUTPUT_240X320_50,
    VO_OUTPUT_240X320_60,
    VO_OUTPUT_800X600_50,
    VO_OUTPUT_720X1280_60,
    VO_OUTPUT_1080X1920_60,
    VO_OUTPUT_7680X4320_30,
    VO_OUTPUT_USER,
    VO_OUTPUT_BUTT
} vo_intf_sync;
#endif /* __BOOT_HDMI_INTF_H__ */

