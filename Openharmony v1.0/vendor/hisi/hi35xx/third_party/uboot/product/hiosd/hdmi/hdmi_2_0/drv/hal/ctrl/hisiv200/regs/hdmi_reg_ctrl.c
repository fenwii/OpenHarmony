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

volatile tx_ctrl_reg_type *g_tx_ctrl_all_reg = NULL;

int hdmi_tx_ctrl_reg_type_init(void)
{
    g_tx_ctrl_all_reg = (volatile tx_ctrl_reg_type *)(HDMI_TX_BASE_ADDR);

    return HI_SUCCESS;
}

hi_void hdmi_tx_ctrl_reg_type_deinit(void)
{
    if (g_tx_ctrl_all_reg != NULL) {
        g_tx_ctrl_all_reg = NULL;
    }
    return;
}

int hdmi_tx_channel_reg_vid_bypass_sel_set(unsigned int reg_vid_bypass_sel)
{
    hi_u32 *reg_addr = NULL;
    tx_channel_sel tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->channel_sel.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_vid_bypass_sel = reg_vid_bypass_sel;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tx_channel_reg_vid_bypass_sel_get(void)
{
    hi_u32 *reg_addr = NULL;
    tx_channel_sel tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->channel_sel.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.reg_vid_bypass_sel;
}

int hdmi_tx_hdmi_srst_req_set(unsigned int tx_hdmi_srst_req)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->tx_rst_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.tx_hdmi_srst_req = tx_hdmi_srst_req;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tx_pwd_srst_req_set(unsigned int tx_pwd_srst_req)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->tx_rst_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.tx_pwd_srst_req = tx_pwd_srst_req;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vidpath_dout_clk_sel_set(unsigned int vidpath_dout_clk_sel)
{
    hi_u32 *reg_addr = NULL;
    tx_pwd_rst_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->tx_rst_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vidpath_dout_clk_sel = vidpath_dout_clk_sel;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_yuv_rgb_cfg_reg_set(unsigned int reg_yuv_rgb_cfg)
{
    hi_u32 *reg_addr = NULL;
    yuv_rgb_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->yuv_rgb.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_yuv_rgb_cfg = reg_yuv_rgb_cfg;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_fifo_wdata_set(unsigned int pwd_fifo_data_in)
{
    hi_u32 *reg_addr = NULL;
    pwd_fifo_wdata tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_wdata.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.pwd_fifo_data_in = pwd_fifo_data_in;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_data_out_cnt_set(unsigned int pwd_data_out_cnt)
{
    hi_u32 *reg_addr = NULL;
    pwd_data_cnt tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_cnt.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.pwd_data_out_cnt = pwd_data_out_cnt;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_slave_seg_set(unsigned int pwd_slave_seg)
{
    hi_u32 *reg_addr = NULL;
    pwd_slave_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_slave.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.pwd_slave_seg = pwd_slave_seg;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_slave_offset_set(unsigned int pwd_slave_offset)
{
    hi_u32 *reg_addr = NULL;
    pwd_slave_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_slave.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.pwd_slave_offset = pwd_slave_offset;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_slave_addr_set(unsigned int pwd_slave_addr)
{
    hi_u32 *reg_addr = NULL;
    pwd_slave_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_slave.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.pwd_slave_addr = pwd_slave_addr;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_mst_cmd_set(unsigned int pwd_cmd)
{
    hi_u32 *reg_addr = NULL;
    pwd_mst_cmd tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_cmd.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.pwd_mst_cmd = pwd_cmd;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ddc_mst_arb_req_set(unsigned int cpu_ddc_req)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_arb_req tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->ddc_arb_req.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cpu_ddc_req = cpu_ddc_req;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_pwd_fifo_rdata_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_fifo_rdata tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_rdata.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.pwd_fifo_data_out;
}

int hdmi_pwd_fifo_data_cnt_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_data_cnt tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_cnt.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.pwd_fifo_data_cnt;
}

int hdmi_pwd_fifo_empty_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_mst_state tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_state.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.pwd_fifo_empty;
}

int hdmi_pwd_i2c_in_prog_get(void)
{
    hi_u32 *reg_addr = NULL;
    pwd_mst_state tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->pwd_state.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.pwd_i2c_in_prog;
}

int hdmi_ddc_mst_arb_ack_cpu_ddc_req_ack_get(void)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_arb_ack tmp;

    reg_addr = (hi_u32 *)&(g_tx_ctrl_all_reg->ddc_arb_ack.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.cpu_ddc_req_ack;
}

unsigned int hdmi_tx_ctrl_read(unsigned int tx_crl_addr)
{
    hi_char *addr = NULL;
    hi_u32  reg_val = 0;

    if (g_tx_ctrl_all_reg != NULL) {
        addr = (hi_char *)g_tx_ctrl_all_reg + tx_crl_addr;
        reg_val = hdmi_tx_reg_read((hi_u32 *)addr);
    }

    return reg_val;
}

int hdmi_tx_ctrl_write(unsigned int tx_crl_addr, unsigned int val)
{
    hi_char *addr = NULL;

    if (g_tx_ctrl_all_reg != NULL) {
        addr = (hi_char *)g_tx_ctrl_all_reg + tx_crl_addr;
        hdmi_tx_reg_write((hi_u32 *)addr, val);
    }

    return HI_SUCCESS;
}

