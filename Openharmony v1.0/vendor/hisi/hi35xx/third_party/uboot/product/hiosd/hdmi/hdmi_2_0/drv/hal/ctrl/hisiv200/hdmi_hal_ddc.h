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
#ifndef __HDMI_HAL_DDC_H__
#define __HDMI_HAL_DDC_H__

#include "drv_hdmi_common.h"
#include "hdmi_reg_aon.h"

#define DDC_MAX_RECORD_NUM              1
#define DDC_DEFAULT_TIMEOUT_ACCESS      100
#define DDC_DEFAULT_TIMEOUT_HPD         100
#define DDC_DEFAULT_TIMEOUT_IN_PROG     20
#define DDC_DEFAULT_TIMEOUT_SCL         1
#define DDC_DEFAULT_TIMEOUT_SDA         30
#define DDC_DEFAULT_TIMEOUT_ISSUE       20
#define DDC_DEFAULT_RETRY_TIMEOUT_ISSUE 60

typedef enum {
    DDC_FUNC_TYPE_EDID,
    DDC_FUNC_TYPE_HDCP,
    DDC_FUNC_TYPE_SCDC,
    DDC_FUNC_TYPE_BUTT
} ddc_func_type;

typedef enum {
    DDC_MASTER_MODE_PWD,
    DDC_MASTER_MODE_AON
} ddc_master_mode;

typedef enum {
    DDC_MODE_READ_SINGLE_NO_ACK,
    DDC_MODE_READ_SINGLE_ACK,
    DDC_MODE_READ_MUTIL_NO_ACK,
    DDC_MODE_READ_MUTIL_ACK,
    DDC_MODE_READ_SEGMENT_NO_ACK,
    DDC_MODE_READ_SEGMENT_ACK,
    DDC_MODE_WRITE_MUTIL_NO_ACK,
    DDC_MODE_WRITE_MUTIL_ACK,
    DDC_MODE_BUTT
} ddc_issue_mode;

typedef union {
    struct {
        hi_u32 access_wait_timeout : 1;
        hi_u32 bus_low_scl         : 1;
        hi_u32 bus_low_sda         : 1;
        hi_u32 err_isseu_mode      : 1;
        hi_u32 issue_timeout       : 1;
        hi_u32 bus_no_ack          : 1;
        hi_u32 in_prog_timeout     : 1;
        hi_u32 hpd_no_exist        : 1;
        hi_u32 clr_err_fail        : 1;
        hi_u32 reserved            : 23;
    } u32;
    hi_u32 word;
} ddc_err;

typedef struct {
    hi_u8           segment;
    hi_u8           offset;
    ddc_func_type   func_type;
    ddc_issue_mode  issue_mode;
    ddc_master_mode master_mode;
    hi_u32          speed;
    hi_u32          access_timeout;
    hi_u32          hpd_timeout;
    hi_u32          in_prog_timeout;
    hi_u32          scl_timeout;
    hi_u32          sda_timeout;
    hi_u32          issue_timeout;
    hi_s32          data_size;
    hi_u8           *data;
} ddc_cfg;

typedef struct {
    hi_bool init;      /* is the DDC init */
    hi_u32  elem_ptr;  /* element pointer in the record array */
    hi_u32  total_num; /* total record size,max value is DDC_MAX_RECORD_NUM */
} ddc_run;

typedef struct {
    ddc_run run; /* DDC running control info */
} ddc_info;

hi_s32 hal_hdmi_ddc_init(hdmi_device_id hdmi_id);

hi_s32 hal_hdmi_ddc_deinit(hdmi_device_id hdmi_id);

hi_s32 hal_hdmi_ddc_issue(hdmi_device_id hhdmi_iddmi, ddc_cfg *cfg);

hi_s32 hal_hdmi_ddc_issue_trim(hdmi_device_id hdmi_id, const ddc_cfg *cfg);

hi_s32 hal_hdmi_ddc_default_cfg_get(hdmi_device_id hdmi_id, ddc_cfg *cfg);

#endif /* __HDMI_HAL_DDC_H__ */

