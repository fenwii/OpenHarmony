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

#include "hdmi_reg_video_path.h"
#include "hdmi_product_define.h"

volatile video_path_reg_type *g_video_path_all_reg = NULL;

int hdmi_tx_videopath_reg_type_init(void)
{
    g_video_path_all_reg = (volatile video_path_reg_type*)(HDMI_TX_BASE_ADDR + HDMI_TX_BASE_ADDR_AIDEO);

    return HI_SUCCESS;
}

hi_void hdmi_tx_videopath_reg_type_deinit(void)
{
    if (g_video_path_all_reg != NULL) {
        g_video_path_all_reg = HI_NULL;
    }

    return;
}

int hdmi_data_align_ctrl_reg_vert_cbcr_sel_set(unsigned int reg_vert_cbcr_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dwsm_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_vert_cbcr_sel = reg_vert_cbcr_sel;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tx_pack_fifo_ctrl_reg_fifo_manu_rst_set(unsigned int reg_fifo_manu_rst)
{
    hi_u32 *reg_addr = NULL;
    tx_pack_fifo_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->tx_fifo_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_fifo_manu_rst = reg_fifo_manu_rst;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_multi_csc_ctrl_reg_csc_mode_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->multi_csc.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.reg_csc_mode;
}

int hdmi_dither_config_mode_set(unsigned int dither_mode)
{
    hi_u32 *reg_addr = NULL;
    dither_config tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dither.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.dither_mode = dither_mode;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_dither_config_rnd_byp_set(unsigned int dither_rnd_byp)
{
    hi_u32 *reg_addr = NULL;
    dither_config tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dither.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.dither_rnd_byp = dither_rnd_byp;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_multi_csc_ctrl_reg_csc_mode_set(unsigned int reg_csc_mode)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->multi_csc.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_csc_mode = reg_csc_mode;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_multi_csc_ctrl_reg_csc_saturate_en_set(unsigned int reg_csc_saturate_en)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->multi_csc.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_csc_saturate_en = reg_csc_saturate_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_multi_csc_ctrl_reg_csc_en_set(unsigned int reg_csc_en)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->multi_csc.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_csc_en = reg_csc_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dwsm_ctrl_reg_dwsm_vert_en_set(unsigned int reg_dwsm_vert_en)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dwsm_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_dwsm_vert_en = reg_dwsm_vert_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dwsm_ctrl_reg_dwsm_hori_en_set(unsigned int reg_dwsm_hori_en)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dwsm_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_dwsm_hori_en = reg_dwsm_hori_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dwsm_ctrl_reg_hori_filter_en_set(unsigned int reg_hori_filter_en)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dwsm_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_hori_filter_en = reg_hori_filter_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_data_align_ctrl_reg_pxl_div_en_set(unsigned int reg_pxl_div_en)
{
    hi_u32 *reg_addr = NULL;
    data_align_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->data_align.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_pxl_div_en = reg_pxl_div_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_data_align_ctrl_reg_demux_420_en_set(unsigned int reg_demux_420_en)
{
    hi_u32 *reg_addr = NULL;
    data_align_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->data_align.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_demux_420_en = reg_demux_420_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dmux_ctrl_reg_inver_sync_set(unsigned int reg_inver_sync)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dmux_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_inver_sync = reg_inver_sync;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dmux_ctrl_reg_syncmask_en_set(unsigned int reg_syncmask_en)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dmux_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_syncmask_en = reg_syncmask_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dmux_ctrl_reg_vmux_cr_sel_set(unsigned int reg_vmux_cr_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dmux_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_vmux_cr_sel = reg_vmux_cr_sel;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dmux_ctrl_reg_vmux_cb_sel_set(unsigned int reg_vmux_cb_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dmux_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_vmux_cb_sel = reg_vmux_cb_sel;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_video_dmux_ctrl_reg_vmux_y_sel_set(unsigned int reg_vmux_y_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dmux_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_vmux_y_sel = reg_vmux_y_sel;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tx_pack_fifo_ctrl_tmds_pack_mode_set(unsigned int tmds_pack_mode)
{
    hi_u32 *reg_addr = NULL;
    tx_pack_fifo_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->tx_fifo_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.tmds_pack_mode = tmds_pack_mode;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tx_pack_fifo_ctrl_tmds_pack_mode_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    tx_pack_fifo_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->tx_fifo_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.tmds_pack_mode;
}

int hdmi_tx_pack_fifo_ctrl_reg_fifo_auto_rst_en_set(unsigned int reg_fifo_auto_rst_en)
{
    hi_u32 *reg_addr = NULL;
    tx_pack_fifo_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->tx_fifo_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_fifo_auto_rst_en = reg_fifo_auto_rst_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tclk_lower_threshold_reg_tcnt_lower_threshold_set(unsigned int reg_tcnt_lower_threshold)
{
    hi_u32 *reg_addr = NULL;
    tclk_lower_threshold tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->lower_threshold.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_tcnt_lower_threshold = reg_tcnt_lower_threshold;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_tclk_upper_threshold_reg_tcnt_upper_threshold_set(unsigned int reg_tcnt_upper_threshold)
{
    hi_u32 *reg_addr = NULL;
    tclk_upper_threshold tmp;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->lower_threshold.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.reg_tcnt_upper_threshold = reg_tcnt_upper_threshold;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

