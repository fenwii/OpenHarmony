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
#include "hdmi_osal.h"
#include "hdmi_reg_aon.h"
#include "hdmi_reg_ctrl.h"
#include "hdmi_hal_intf.h"
#include "hdmi_hal_ctrl.h"
#include "hdmi_product_define.h"

#define DDC_EDID_SALVE_ADDR  0xa0
#define DDC_HDCP_SALVE_ADDR  0x74
#define DDC_SCDC_SALVE_ADDR  0xa8
#define DDC_MAX_FIFO_SIZE    16
#define DDC_EXT_BLOCK_OFFSET 0x7e
#define DDC_MAX_EDID_EXT_NUM 3 /* 3: 4(max block num) - 1(base block) */
#define DDC_DATA_FIFO_DELAY  1
#define DDC_GPIO_DELAY       8 /* 8us */

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

    hdmi_ddc_mst_arb_req_set(HI_TRUE);
    while (!hdmi_ddc_mst_arb_ack_cpu_ddc_req_ack_get()) {
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

    hdmi_ddc_mst_arb_req_set(HI_FALSE);
    while (hdmi_ddc_mst_arb_ack_cpu_ddc_req_ack_get()) {
        mdelay(1);
        tmp_time++;
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
        tmp_time++;
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
        /* STOP contition */
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
            hdmi_info("ddc deadlock clear success\n");
            ret = HI_SUCCESS;
        } else {
            hdmi_warn("ddc deadlock clear  fail\n");
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
        tmp_time++;
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
    hi_u32 segment, offset;
    hi_u32 data_size;

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
             (i < timeout) &&
             (hdmi_pwd_fifo_empty_get() || (hdmi_pwd_fifo_data_cnt_get() == 0));
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
            *p = hdmi_pwd_fifo_rdata_get();
            /*
             * the fifo status is not refresh promptly,
             * so re-read the fifo status and delay 1us if the fifo is empty,
             * wait the data ready. it must delay 1us(from wzg @2015.12.28) after read fifo data.
             */
            udelay(DDC_DATA_FIFO_DELAY);
        } else {
            hdmi_err("edid &data_size[%u]=null\n", data_size);
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
            hdmi_pwd_fifo_wdata_set(*data);
            udelay(DDC_DATA_FIFO_DELAY);
        } else {
            hdmi_err("edid &data_size[%u]=null\n", data_size);
            return HI_FAILURE;
        }
    }
    return data_size;
}

static hi_s32 ddc_data_issue(ddc_cfg *cfg, hi_bool read_issue)
{
    hi_u32 timeout, data_size;

    timeout = cfg->issue_timeout < DDC_DEFAULT_TIMEOUT_ISSUE ? DDC_DEFAULT_TIMEOUT_ISSUE : cfg->sda_timeout;
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        if (read_issue) {
            data_size = ddc_read(cfg->data, cfg->data_size, timeout);
        } else {
            data_size = ddc_write(cfg->data, cfg->data_size, timeout);
        }
        return data_size;
    } else {
        hdmi_err("ddc unknow master_mode=%u,fail!\n", cfg->master_mode);
        return HI_FAILURE;
    }
}

hi_s32 hal_hdmi_ddc_init(hdmi_device_id hdmi_id)
{
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    if (!info->run.init) {
        info->run.init = HI_TRUE;
        info->run.elem_ptr = 0;
        info->run.total_num = 0;
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

hi_s32 hal_hdmi_ddc_issue(hdmi_device_id hdmi_id, ddc_cfg *cfg)
{
    hi_s32  ret = HI_SUCCESS;
    hi_bool read_issue = HI_FALSE;
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    hdmi_if_null_return(cfg, HI_FAILURE);
    hdmi_if_false_return(info->run.init, HI_FAILURE);

    /* Access check */
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        if (ddc_access_enable_wait(cfg->access_timeout) != HI_SUCCESS) {
            hdmi_err("ddc wait access bus timeout!\n");
            goto issue_exit;
        }
    }
    /* scl check */
    if (ddc_scl_wait(cfg->scl_timeout) != HI_SUCCESS) {
        hdmi_err("ddc wait scl timeout!\n");
        goto issue_exit;
    }
    /* sda check */
    if (ddc_sda_wait(cfg->sda_timeout) != HI_SUCCESS) {
        hdmi_err("ddc wait sda timeout!\n");
        goto issue_exit;
    }
    /* jude read/write issue */
    if (cfg->issue_mode <= DDC_MODE_READ_SEGMENT_ACK) {
        read_issue = HI_TRUE;
    } else if (cfg->issue_mode < DDC_MODE_BUTT) {
        read_issue = HI_FALSE;
    } else {
        hdmi_err("un-know ddc issue mode!\n");
        goto issue_exit;
    }
    /* Issue command */
    if (ddc_cmd_issue(cfg, read_issue) != HI_SUCCESS) {
        hdmi_err("ddc command issue fail!\n");
        goto issue_exit;
    }
    /* issue data */
    ret = ddc_data_issue(cfg, read_issue);
    if (ret <= 0) {
        hdmi_info("ddc data issue fail!\n");
        goto issue_exit;
    }

issue_exit:
    /* In prog check */
    if (ddc_in_prog_wait(cfg->in_prog_timeout) != HI_SUCCESS) {
        hdmi_warn("ddc wait in prog timeout!\n");
    }

    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        if (ddc_access_disable_wait(cfg->access_timeout) != HI_SUCCESS) {
            hdmi_warn("ddc wait access disalbe timeout!\n");
        }
    }

    return ret;
}

/* Only for software training */
hi_s32 hal_hdmi_ddc_issue_trim(hdmi_device_id hdmi_id, const ddc_cfg *cfg)
{
    hi_s32 ret = HI_SUCCESS;
    hi_bool read_issue = HI_FALSE;
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    hdmi_if_null_return(cfg, HI_FAILURE);
    hdmi_if_false_return(info->run.init, HI_FAILURE);

    /* Access check */
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        /* ddc request */
        hdmi_ddc_mst_arb_req_set(HI_TRUE);
    }
    /* jude read/write issue */
    if (cfg->issue_mode <= DDC_MODE_READ_SEGMENT_ACK) {
        read_issue = HI_TRUE;
    } else if (cfg->issue_mode < DDC_MODE_BUTT) {
        read_issue = HI_FALSE;
    } else {
        goto trim_exit;
    }
    /* Issue command */
    if (ddc_cmd_issue(cfg, read_issue) != HI_SUCCESS) {
        goto trim_exit;
    }

trim_exit:
    if (cfg->master_mode == DDC_MASTER_MODE_PWD) {
        /* Disable ddc request */
        hdmi_ddc_mst_arb_req_set(HI_FALSE);
    }

    return ret;
}

hi_s32 hal_hdmi_ddc_default_cfg_get(hdmi_device_id hdmi_id, ddc_cfg *cfg)
{
    ddc_info *info = ddc_info_get(hdmi_id);

    hdmi_if_null_return(info, HI_FAILURE);
    hdmi_if_null_return(cfg, HI_FAILURE);
    hdmi_if_false_return(info->run.init, HI_FAILURE);

    cfg->segment         = 0;
    cfg->offset          = 0;
    cfg->func_type       = DDC_FUNC_TYPE_EDID;
    cfg->issue_mode      = DDC_MODE_READ_MUTIL_NO_ACK;
    cfg->speed           = 0;
    cfg->master_mode     = DDC_MASTER_MODE_PWD; /* DDC_MASTER_MODE_AON; */
    cfg->access_timeout  = DDC_DEFAULT_TIMEOUT_ACCESS;
    cfg->hpd_timeout     = DDC_DEFAULT_TIMEOUT_HPD;
    cfg->in_prog_timeout = DDC_DEFAULT_TIMEOUT_IN_PROG;
    cfg->scl_timeout     = DDC_DEFAULT_TIMEOUT_SCL;
    cfg->sda_timeout     = DDC_DEFAULT_TIMEOUT_SDA;
    cfg->issue_timeout   = DDC_DEFAULT_TIMEOUT_ISSUE;
    cfg->data_size       = 0;
    cfg->data            = HI_NULL;

    return HI_SUCCESS;
}

