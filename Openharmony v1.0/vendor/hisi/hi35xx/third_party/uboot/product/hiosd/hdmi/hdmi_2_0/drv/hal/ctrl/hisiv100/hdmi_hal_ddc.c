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
#include "hdmi_hal_ddc.h"
#include "hdmi_reg_aon.h"
#include "hdmi_reg_ctrl.h"
#include "hdmi_hal_intf.h"
#include "hdmi_hal_ctrl.h"
#include "hdmi_product_define.h"
#include "hdmi_osal.h"

#define DDC_EDID_SALVE_ADDR 0xa0
#define DDC_HDCP_SALVE_ADDR 0x74
#define DDC_SCDC_SALVE_ADDR 0xa8
#define DDC_MAX_FIFO_SIZE   16
#define DDC_GPIO_DELAY      8
#define DDC_DATA_FIFO_DELAY 1

typedef enum {
    DDC_CMD_READ_SINGLE_NO_ACK  = 0x00,
    DDC_CMD_READ_SINGLE_ACK     = 0x01,
    DDC_CMD_READ_MUTI_NO_ACK    = 0x02,
    DDC_CMD_READ_MUTI_ACK       = 0x03,
    DDC_CMD_READ_SEGMENT_NO_ACK = 0x04,
    DDC_CMD_READ_SEGMENT_ACK    = 0x05,
    DDC_CMD_WRITE_MUTI_NO_ACK   = 0x06,
    DDC_CMD_WRITE_MUTI_ACK      = 0x07,
    DDC_CMD_FIFO_CLR            = 0x09,
    DDC_CMD_SCL_DRV             = 0x0a,
    DDC_CMD_MASTER_ABORT        = 0x0f
} ddc_issue_cmd;

static ddc_info g_ddc_info[HDMI_DEVICE_ID_BUTT];

static ddc_info *ddc_info_get(hdmi_device_id hdmi_id)
{
    if (hdmi_id < HDMI_DEVICE_ID_BUTT) {
        return &g_ddc_info[hdmi_id];
    }
    return HI_NULL;
}

static hi_s32 ddc_access_enable_wait(hi_u32 timeout)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 tmp_time = 0;

    hdmi_ddc_cpu_ddc_req_set(HI_TRUE);
    while (!hdmi_ddc_cpu_ddc_req_ack_get()) {
        mdelay(1);
        tmp_time++;
        if (tmp_time > timeout) {
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

static hi_s32 ddc_access_disable_wait(hi_u32 timeout)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 tmp_time = 0;

    hdmi_ddc_cpu_ddc_req_set(HI_FALSE);
    while (hdmi_ddc_cpu_ddc_req_ack_get()) {
        mdelay(1);
        tmp_time += 1;
        if (tmp_time > timeout) {
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

static hi_s32 ddc_scl_wait(hi_u32 timeout)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 tmp_time = 0;

    while (!hdmi_ddc_scl_st_get()) {
        mdelay(1);
        tmp_time += 1;
        if (tmp_time > timeout) {
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

static hi_s32 ddc_sda_wait(hi_u32 timeout)
{
    hi_u32 tmp_timeout = 0;
    hi_s32 ret = HI_SUCCESS;

    if (!hdmi_ddc_sda_st_get()) {
        hdmi_dcc_man_en_set(HI_TRUE);
        while ((!hdmi_ddc_sda_st_get()) && tmp_timeout++ < timeout) {
            /* pull scl high */
            hdmi_ddc_scl_oen_set(HI_TRUE);
            udelay(DDC_GPIO_DELAY);
            /* pull scl low */
            hdmi_ddc_scl_oen_set(HI_FALSE);
            udelay(DDC_GPIO_DELAY);
        }
        if (tmp_timeout < timeout && (hdmi_ddc_sda_st_get())) {
            /* pull sda low */
            hdmi_ddc_sda_oen_set(HI_FALSE);
            udelay(DDC_GPIO_DELAY);
            /* pull scl high */
            hdmi_ddc_scl_oen_set(HI_TRUE);
            udelay(DDC_GPIO_DELAY);
            /* pull sda high */
            hdmi_ddc_sda_oen_set(HI_TRUE);
            udelay(DDC_GPIO_DELAY);
            hdmi_info("deadlock clear success\n");
            ret = HI_SUCCESS;
        } else {
            hdmi_warn("deadlock clear fail\n");
            ret = HI_FAILURE;
        }
        hdmi_dcc_man_en_set(HI_FALSE);
    }

    return ret;
}

static hi_s32 ddc_in_prog_wait(hi_u32 timeout)
{
    hi_s32 ret = HI_SUCCESS;
    hi_u32 tmp_time = 0;

    while (hdmi_pwd_i2c_in_prog_get()) {
        mdelay(1);
        tmp_time += 1;
        if (tmp_time > timeout) {
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

static hi_s32 ddc_cmd_issue(const ddc_cfg *cfg, hi_bool read_issue)
{
    hi_u32 slave_addr = 0;
    hi_u32 segment, offset, data_size;

    hdmi_if_null_return(cfg, HI_FAILURE);
    segment = cfg->segment;
    offset = cfg->offset;
    data_size = cfg->data_size;
    switch (cfg->func_type) {
        case DDC_FUNC_TYPE_EDID:
            slave_addr = DDC_EDID_SALVE_ADDR;
            break;
        case DDC_FUNC_TYPE_HDCP:
            slave_addr = DDC_HDCP_SALVE_ADDR;
            break;
        case DDC_FUNC_TYPE_SCDC:
            slave_addr = DDC_SCDC_SALVE_ADDR;
            break;
        default:
            hdmi_warn("invalid DDC function type, wrong slaveaddr!\n");
            break;
    }
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        hdmi_pwd_mst_cmd_set(DDC_CMD_FIFO_CLR);
        hdmi_pwd_slave_addr_set(slave_addr);
        hdmi_pwd_slave_seg_set(segment);
        hdmi_pwd_slave_offset_set(offset);
        hdmi_pwd_data_out_cnt_set(data_size);
        udelay(DDC_GPIO_DELAY);
        hdmi_pwd_mst_cmd_set(cfg->issue_mode);
    } else {
        hdmi_err("invalid master_mode=%u\n", cfg->master_mode);
    }

    return HI_SUCCESS;
}

static hi_s32 ddc_read(hi_u8 *data, hi_u32 len, hi_u32 timeout)
{
    hi_u32 i, data_size;
    hi_u8 *p = HI_NULL;

    p = data;
    for (data_size = 0; data_size < len; data_size++, p++) {
        /* when read-fifo empty, every byte wait a max timeout */
        for (i = 0;
            (i < timeout) && (hdmi_pwd_fifo_empty_get() || (hdmi_pwd_fifo_data_cnt_get() == 0));
             i++) {
            /* wait ddc status update after DDC cmd set. */
            mdelay(DDC_DATA_FIFO_DELAY);
            if (hdmi_ddc_i2c_no_ack_get() || hdmi_ddc_i2c_bus_low_get()) {
                hdmi_pwd_mst_cmd_set(DDC_CMD_MASTER_ABORT);
                hdmi_warn("DDC status error!\n");
                return HI_FAILURE;
            }
        }
        if (i >= timeout) {
            hdmi_warn("read fifo timeout=%u ms, size=%u!\n", timeout, len);
            return HI_FAILURE;
        }
        if (p != HI_NULL) {
            *p = hdmi_pwd_fifo_data_out_get();
            /*
             * the fifo status is not refresh promptly,
             * so re-read the fifo status and delay 1us if the fifo is empty,
             * wait the data ready. it must delay 1us(from wzg @2015.12.28) after read fifo data.
             */
            udelay(DDC_DATA_FIFO_DELAY);
        } else {
            hdmi_err("edid &data[%u]=null\n", data_size);
            return HI_FAILURE;
        }
    }

    return data_size;
}

static hi_s32 ddc_write(hi_u8 *data, hi_u32 len, hi_u32 timeout)
{
    hi_u32 i, data_size;
    hi_u8 *p = HI_NULL;

    p = data;
    for (data_size = 0; data_size < len; data_size++, p++) {
        /* when write-fifo full, every byte wait a max timeout and retry times */
        for (i = 0; (((i < timeout) && (hdmi_pwd_fifo_data_cnt_get() >= DDC_MAX_FIFO_SIZE))); i++) {
            /* wait ddc status update after DDC cmd set. */
            mdelay(DDC_DATA_FIFO_DELAY);
            if (hdmi_ddc_i2c_no_ack_get() || hdmi_ddc_i2c_bus_low_get()) {
                hdmi_pwd_mst_cmd_set(DDC_CMD_MASTER_ABORT);
                hdmi_warn("DDC status error!\n");
                return HI_FAILURE;
            }
        }
        if (i >= timeout) {
            hdmi_err("write fifo timeout=%u ms, size=%u\n", timeout, len);
            return HI_FAILURE;
        }
        if (p != HI_NULL) {
            hdmi_pwd_fifo_data_in_set(*data);
            udelay(DDC_DATA_FIFO_DELAY);
        } else {
            hdmi_err("edid &data[%u]=null\n", data_size);
            return HI_FAILURE;
        }
    }

    return data_size;
}

static hi_s32 ddc_data_issue(ddc_cfg *cfg, hi_bool read_issue)
{
    hi_u32 data_size, timeout;

    timeout = (cfg->issue_timeout < DDC_DEFAULT_TIMEOUT_ISSUE) ? DDC_DEFAULT_TIMEOUT_ISSUE : cfg->sda_timeout;
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        if (read_issue) {
            data_size = ddc_read(cfg->data, cfg->data_size, timeout);
        } else {
            data_size = ddc_write(cfg->data, cfg->data_size, timeout);
        }
        return data_size;
    } else {
        hdmi_err("invalid master_mode=%u, fail!\n", cfg->master_mode);
        return HI_FAILURE;
    }
}

hi_s32 hal_hdmi_ddc_init(hdmi_device_id hdmi_id)
{
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    if (!info->run.init) {
        info->run.init = HI_TRUE;
    }

    return HI_SUCCESS;
}

hi_s32 hal_hdmi_ddc_deinit(hdmi_device_id hdmi_id)
{
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    hdmi_if_false_return(info->run.init, HI_FAILURE);
    info->run.init = HI_FALSE;

    return HI_SUCCESS;
}

hi_s32 hal_hdmi_ddc_err_clear(hdmi_device_id hdmi_id)
{
    hi_s32 ret = HI_SUCCESS;
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    hdmi_if_false_return(info->run.init, HI_FAILURE);

    /* In prog check */
    if (ddc_in_prog_wait(DDC_DEFAULT_TIMEOUT_IN_PROG) != HI_SUCCESS) {
        hdmi_warn("error clr, wait in prog timeout!\n");
        ret = HI_FAILURE;
    }
    /* scl check */
    if (ddc_scl_wait(DDC_DEFAULT_TIMEOUT_SCL) != HI_SUCCESS) {
        hdmi_warn("error clr, wait scl timeout!\n");
        ret = HI_FAILURE;
    }
    /* sda check */
    if (ddc_sda_wait(DDC_DEFAULT_TIMEOUT_SDA) != HI_SUCCESS) {
        hdmi_warn("error clr, wait sda timeout!\n");
        ret = HI_FAILURE;
    }
    if (ret == HI_SUCCESS) {
        hdmi_info("error clr success!\n");
    }

    return ret;
}

hi_s32 hal_hdmi_ddc_issue(hdmi_device_id hdmi_id, ddc_cfg *cfg)
{
    hi_s32 ret = HI_SUCCESS;
    hi_bool read_issue = HI_FALSE;
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    hdmi_if_null_return(cfg, HI_FAILURE);
    hdmi_if_false_return(info->run.init, HI_FAILURE);

    /* Access check */
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        if (ddc_access_enable_wait(cfg->access_timeout) != HI_SUCCESS) {
            hdmi_err("wait access bus timeout!\n");
            goto exit;
        }
    }
    /* scl check */
    if (ddc_scl_wait(cfg->scl_timeout) != HI_SUCCESS) {
        hdmi_err("wait scl timeout!\n");
        goto exit;
    }
    /* sda check */
    if (ddc_sda_wait(cfg->sda_timeout) != HI_SUCCESS) {
        hdmi_err("wait sda timeout!\n");
        goto exit;
    }
    /* jude read/write issue */
    if (cfg->issue_mode <= DDC_MODE_READ_SEGMENT_ACK) {
        read_issue = HI_TRUE;
    } else if (cfg->issue_mode < DDC_MODE_BUTT) {
        read_issue = HI_FALSE;
    } else {
        hdmi_err("invalid ddc issue mode!\n");
        goto exit;
    }
    /* Issue command */
    if (ddc_cmd_issue(cfg, read_issue) != HI_SUCCESS) {
        hdmi_err("command issue fail!\n");
        goto exit;
    }
    /* issue data */
    ret = ddc_data_issue(cfg, read_issue);
    if (ret <= 0) {
        hdmi_info("data issue fail!\n");
        goto exit;
    }

exit:
    if (ddc_in_prog_wait(cfg->in_prog_timeout) != HI_SUCCESS) {
        hdmi_warn("wait in prog timeout!\n");
    }

    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        if (ddc_access_disable_wait(cfg->access_timeout) != HI_SUCCESS) {
            hdmi_warn("wait access disalbe timeout!\n");
        }
    }

    return ret;
}

hi_void hal_hdmi_ddc_default_cfg_get(hdmi_device_id hdmi, ddc_cfg *cfg)
{
    ddc_info *info = ddc_info_get(hdmi);

    hdmi_if_null_return_void(info);
    hdmi_if_null_return_void(cfg);
    hdmi_if_false_return_void(info->run.init);

    cfg->segment     = 0;
    cfg->offset      = 0;
    cfg->func_type   = DDC_FUNC_TYPE_EDID;
    cfg->issue_mode  = DDC_MODE_READ_MUTIL_NO_ACK;
    cfg->speed       = 0;
    cfg->master_mode = DDC_MASTER_MODE_PWD;
    cfg->access_timeout  = DDC_DEFAULT_TIMEOUT_ACCESS;
    cfg->hpd_timeout     = DDC_DEFAULT_TIMEOUT_HPD;
    cfg->in_prog_timeout = DDC_DEFAULT_TIMEOUT_IN_PROG;
    cfg->scl_timeout     = DDC_DEFAULT_TIMEOUT_SCL;
    cfg->sda_timeout     = DDC_DEFAULT_TIMEOUT_SDA;
    cfg->issue_timeout   = DDC_DEFAULT_TIMEOUT_ISSUE;
    cfg->data_size       = 0;
    cfg->data            = HI_NULL;

    return;
}

