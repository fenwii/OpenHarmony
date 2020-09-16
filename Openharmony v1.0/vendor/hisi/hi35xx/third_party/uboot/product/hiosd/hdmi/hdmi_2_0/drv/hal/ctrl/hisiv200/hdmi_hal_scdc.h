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
#ifndef __HDMI_HAL_SCDC_H__
#define __HDMI_HAL_SCDC_H__

#include "hi_type.h"
#include "hdmi_hal_ddc.h"
#include "drv_hdmi_common.h"

#define SCDC_DEFAULT_SCRAMBLE_TIMEOUT  200
#define SCDC_MAX_SCRAMBLE_TIMEOUT      1000
#define SCDC_DEFAULT_SCRAMBLE_INTERVAL 20

/* HDMI2.1 section 10.4.1.3,OFFSET 0x10 */
typedef union {
    struct {
        hi_u8 status_update     : 1;
        hi_u8 ced_update        : 1;
        hi_u8 rr_test           : 1;
        hi_u8 source_test_upate : 1;
        hi_u8 frl_start         : 1;
        hi_u8 flt_update        : 1;
        hi_u8 rsed_update       : 1;
        hi_u8 rsvd              : 1;
    } u8;
    hi_u8 byte;
} scdc_update0_flag;

/* HDMI2.1 section 10.4.1.4,OFFSET 0x20 */
typedef union {
    struct {
        hi_u8 screambling_enable   : 1;
        hi_u8 tmds_bit_clock_ratio : 1;
        hi_u8 rsvd                 : 6;
    } u8;
    hi_u8 byte;
} scdc_tmds_config;

/* HDMI2.1 section 10.4.1.5,OFFSET 0x21 */
typedef union {
    struct {
        hi_u8 screambling_status : 1;
        hi_u8 rsvd               : 7;
    } u8;
    hi_u8 byte;
} scdc_scramble_status;

/* HDMI2.1 section 10.4.1.6,OFFSET 0x31 */
typedef union {
    struct {
        hi_u8 frl_rate   : 4;
        hi_u8 ffe_levels : 4;
    } u8;
    hi_u8 byte;
} scdc_config1;

/* HDMI2.1 section 10.4.1.6,OFFSET 0x35 */
typedef union {
    struct {
        hi_u8 rsvd0           : 1;
        hi_u8 pre_shoot_only  : 1;
        hi_u8 de_emphasis_only: 1;
        hi_u8 no_ffe          : 1;
        hi_u8 rsvd1           : 1;
        hi_u8 flt_no_timeout  : 1;
        hi_u8 dsc_frl_max     : 1;
        hi_u8 frl_max         : 1;
    } u8;
    hi_u8 byte;
} scdc_test_config1;

/* HDMI2.1 section 10.4.1.7,OFFSET 0x40 */
typedef union {
    struct {
        hi_u8 colck_detected  : 1;
        hi_u8 ch0_locked      : 1;
        hi_u8 ch1_locked      : 1;
        hi_u8 ch2_locked      : 1;
        hi_u8 ch3_locked      : 1;
        hi_u8 rsvd            : 1;
        hi_u8 flt_ready       : 1;
        hi_u8 dsc_decode_fail : 1;
    } u8;
    hi_u8 byte;
} scdc_status_flag0;

/* HDMI2.1 section 10.4.1.7,OFFSET 0x41 */
typedef union {
    struct {
        hi_u8 ln0_ltp_req : 4;
        hi_u8 ln1_ltp_req : 4;
    } u8;
    hi_u8 byte;
} scdc_status_flag1;

/* HDMI2.1 section 10.4.1.7,OFFSET 0x42 */
typedef union {
    struct {
        hi_u8 ln2_ltp_req : 4;
        hi_u8 ln3_ltp_req : 4;
    } u8;
    hi_u8 byte;
} scdc_status_flag2;

typedef enum {
    SCDC_OFFSET_SINK_VERSION     = 0x01,
    SCDC_OFFSET_SRC_VERSION      = 0x02,
    SCDC_OFFSET_UPDATE_0         = 0x10,
    SCDC_OFFSET_UPDATE_1         = 0x11,
    SCDC_OFFSET_TMDS_CONFIG      = 0x20,
    SCDC_OFFSET_SCRAMBLER_STATUS = 0x21,
    SCDC_OFFSET_CONFIG_0         = 0x30,
    SCDC_OFFSET_CONFIG_1         = 0x31,
    SCDC_OFFSET_TEST_CONFIG      = 0x35,
    SCDC_OFFSET_STATUS_FLAG_0    = 0x40,
    SCDC_OFFSET_STATUS_FLAG_1    = 0x41,
    SCDC_OFFSET_STATUS_FLAG_2    = 0x42,
    SCDC_OFFSET_DRR_DET_0_L      = 0x50,
    SCDC_OFFSET_DRR_DET_0_H      = 0x51,
    SCDC_OFFSET_DRR_DET_1_L      = 0x52,
    SCDC_OFFSET_DRR_DET_1_H      = 0x53,
    SCDC_OFFSET_DRR_DET_2_L      = 0x54,
    SCDC_OFFSET_DRR_DET_2_H      = 0x55,
    SCDC_OFFSET_DRR_DET_CHKSUM   = 0x56,
    SCDC_OFFSET_TEST_CONFIG_0    = 0xC0,
    SCDC_OFFSET_IEEE_OUI_3TH     = 0xD0,
    SCDC_OFFSET_IEEE_OUI_2ND     = 0xD1,
    SCDC_OFFSET_IEEE_OUI_1ST     = 0xD2,
    SCDC_OFFSET_DEVICE_ID_HEAD   = 0xD3,
    SCDC_OFFSET_DEVICE_ID_TAIL   = 0xDD
} scdc_offset;

typedef struct {
    hi_bool sink_read_quest;
    hi_bool src_scramble;      /* HI_TRUE indicate enable;HI_FALSE indicate disable. */
    hi_bool sink_scramble;     /* HI_TRUE indicate enable;HI_FALSE indicate disable. */
    hi_bool tmds_clk_ratio40x; /* HI_TRUE indicate 40x;HI_FALSE indicate 10x. */
    hi_u32  scramble_timeout;  /* in unit of ms.for [0,200],force to default 200;or,set the value cfg(>200). */
    /* in unit of ms,range[20,200).for [0,20] or >=200,force to default 20;or,set the value cfg[20,200). */
    hi_u32  scramble_interval;
} scdc_attr;

typedef struct {
    hi_bool init;
    hdmi_device_id hdmi_id;
} scdc_status;

typedef struct {
    scdc_status status;
    scdc_attr attr;
} scdc_info;

hi_void hal_hdmi_scdc_init(hdmi_device_id hdmi_id);

hi_void hal_hdmi_scdc_deinit(hdmi_device_id hdmi_id);

hi_s32 hal_hdmi_scdc_attr_set(hdmi_device_id hdmi_id, scdc_attr *attr);

hi_void hal_hdmi_scdc_attr_get(hdmi_device_id hdmi_id, scdc_attr *attr);

#endif /* __HDMI_HAL_SCDC_H__ */

