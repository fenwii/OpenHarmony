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

#include "hdmi_reg_ctrl.h"
#include "hdmi_product_define.h"

volatile tx_ctrl_regs *g_tx_ctrl_all_reg = NULL;

int hdmi_tx_ctrl_regs_init(void)
{
    g_tx_ctrl_all_reg = (volatile tx_ctrl_regs *)(HDMI_TX_BASE_ADDR + HDMI_TX_BASE_ADDR_CTRL);
    return HI_SUCCESS;
}

hi_void hdmi_tx_ctrl_regs_deinit(void)
{
    if (g_tx_ctrl_all_reg != HI_NULL) {
        g_tx_ctrl_all_reg = HI_NULL;
    }
    return;
}

hi_void hdmi_pwd_tx_afifo_srst_req_set(unsigned int tx_afifo_srst_req)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl pwd_rst_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_rst_ctrl.u32);
    pwd_rst_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    pwd_rst_ctrl.bits.tx_afifo_srst_req = tx_afifo_srst_req;
    hdmi_tx_reg_write(reg_addr, pwd_rst_ctrl.u32);

    return;
}

hi_void hdmi_pwd_tx_acr_srst_req_set(unsigned int tx_acr_srst_req)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl pwd_rst_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_rst_ctrl.u32);
    pwd_rst_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    pwd_rst_ctrl.bits.tx_acr_srst_req = tx_acr_srst_req;
    hdmi_tx_reg_write(reg_addr, pwd_rst_ctrl.u32);

    return;
}

hi_void hdmi_pwd_tx_aud_srst_req_set(unsigned int tx_aud_srst_req)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl pwd_rst_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_rst_ctrl.u32);
    pwd_rst_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    pwd_rst_ctrl.bits.tx_aud_srst_req = tx_aud_srst_req;
    hdmi_tx_reg_write(reg_addr, pwd_rst_ctrl.u32);

    return;
}

hi_void hdmi_pwd_tx_hdmi_srst_req_set(unsigned int tx_hdmi_srst_req)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl pwd_rst_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_rst_ctrl.u32);
    pwd_rst_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    pwd_rst_ctrl.bits.tx_hdmi_srst_req = tx_hdmi_srst_req;
    hdmi_tx_reg_write(reg_addr, pwd_rst_ctrl.u32);

    return;
}

hi_void hdmi_pwd_fifo_data_in_set(unsigned int pwd_fifo_data_in)
{
    hi_u32 *reg_addr = NULL;
    pwd_fifo_wdata fifo_wdata;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->fifo_wdata.u32);
    fifo_wdata.u32 = hdmi_tx_reg_read(reg_addr);
    fifo_wdata.bits.pwd_fifo_data_in = pwd_fifo_data_in;
    hdmi_tx_reg_write(reg_addr, fifo_wdata.u32);

    return;
}

hi_void hdmi_pwd_data_out_cnt_set(unsigned int pwd_data_out_cnt)
{
    hi_u32 *reg_addr = NULL;
    pwd_data_cnt data_cnt;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->data_cnt.u32);
    data_cnt.u32 = hdmi_tx_reg_read(reg_addr);
    data_cnt.bits.pwd_data_out_cnt = pwd_data_out_cnt;
    hdmi_tx_reg_write(reg_addr, data_cnt.u32);

    return;
}

hi_void hdmi_pwd_slave_seg_set(unsigned int pwd_slave_seg)
{
    hi_u32 *reg_addr = NULL;
    pwd_slave_cfg slave_cfg;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->slave_cfg.u32);
    slave_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    slave_cfg.bits.pwd_slave_seg = pwd_slave_seg;
    hdmi_tx_reg_write(reg_addr, slave_cfg.u32);

    return;
}

hi_void hdmi_pwd_slave_offset_set(unsigned int pwd_slave_offset)
{
    hi_u32 *reg_addr = NULL;
    pwd_slave_cfg slave_cfg;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->slave_cfg.u32);
    slave_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    slave_cfg.bits.pwd_slave_offset = pwd_slave_offset;
    hdmi_tx_reg_write(reg_addr, slave_cfg.u32);

    return;
}

hi_void hdmi_pwd_slave_addr_set(unsigned int pwd_slave_addr)
{
    hi_u32 *reg_addr = NULL;
    pwd_slave_cfg slave_cfg;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->slave_cfg.u32);
    slave_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    slave_cfg.bits.pwd_slave_addr = pwd_slave_addr;
    hdmi_tx_reg_write(reg_addr, slave_cfg.u32);

    return;
}

hi_void hdmi_pwd_mst_cmd_set(unsigned int cmd)
{
    hi_u32 *reg_addr = NULL;
    pwd_mst_cmd mst_cmd;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->mst_cmd.u32);
    mst_cmd.u32 = hdmi_tx_reg_read(reg_addr);
    mst_cmd.bits.pwd_mst_cmd = cmd;
    hdmi_tx_reg_write(reg_addr, mst_cmd.u32);

    return;
}

hi_void hdmi_ddc_cpu_ddc_req_set(unsigned int cpu_ddc_req)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_arb_req mst_arb_req;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->ddc_mst_req.u32);
    mst_arb_req.u32 = hdmi_tx_reg_read(reg_addr);
    mst_arb_req.bits.cpu_ddc_req = cpu_ddc_req;
    hdmi_tx_reg_write(reg_addr, mst_arb_req.u32);

    return;
}

int hdmi_pwd_fifo_data_out_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_fifo_rdata fifo_rdata;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->fifo_rdata.u32);
    fifo_rdata.u32 = hdmi_tx_reg_read(reg_addr);
    return fifo_rdata.bits.pwd_fifo_data_out;
}

int hdmi_pwd_fifo_data_cnt_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_data_cnt data_cnt;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->data_cnt.u32);
    data_cnt.u32 = hdmi_tx_reg_read(reg_addr);
    return data_cnt.bits.pwd_fifo_data_cnt;
}

int hdmi_pwd_fifo_empty_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_mst_state mst_state;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->mst_state.u32);
    mst_state.u32 = hdmi_tx_reg_read(reg_addr);
    return mst_state.bits.pwd_fifo_empty;
}

int hdmi_pwd_i2c_in_prog_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_mst_state mst_state;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->mst_state.u32);
    mst_state.u32 = hdmi_tx_reg_read(reg_addr);
    return mst_state.bits.pwd_i2c_in_prog;
}

int hdmi_ddc_cpu_ddc_req_ack_get(void)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_arb_ack mst_arb_ack;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->ddc_mst_ack.u32);
    mst_arb_ack.u32 = hdmi_tx_reg_read(reg_addr);
    return mst_arb_ack.bits.cpu_ddc_req_ack;
}

