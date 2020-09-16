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

volatile video_path_regs *g_video_path_all_reg = NULL;

int hdmi_videopath_regs_init(void)
{
    g_video_path_all_reg = (volatile video_path_regs *)(HDMI_TX_BASE_ADDR + HDMI_TX_BASE_ADDR_AIDEO);
    return HI_SUCCESS;
}

hi_void hdmi_videopath_regs_deinit(void)
{
    if (g_video_path_all_reg != HI_NULL) {
        g_video_path_all_reg = HI_NULL;
    }
    return;
}

int hdmi_reg_csc_mode_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl csc_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->csc_ctrl.u32);
    csc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    return csc_ctrl.bits.reg_csc_mode;
}

hi_void hdmi_dither_mode_set(unsigned int dither_mode)
{
    hi_u32 *reg_addr = NULL;
    dither_config dither_cfg;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dither_cfg.u32);
    dither_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    dither_cfg.bits.dither_mode = dither_mode;
    hdmi_tx_reg_write(reg_addr, dither_cfg.u32);

    return;
}

hi_void hdmi_dither_rnd_byp_set(unsigned int dither_rnd_byp)
{
    hi_u32 *reg_addr = NULL;
    dither_config dither_cfg;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->dither_cfg.u32);
    dither_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    dither_cfg.bits.dither_rnd_byp = dither_rnd_byp;
    hdmi_tx_reg_write(reg_addr, dither_cfg.u32);

    return;
}

hi_void hdmi_reg_csc_mode_set(unsigned int reg_csc_mode)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl csc_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->csc_ctrl.u32);
    csc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    csc_ctrl.bits.reg_csc_mode = reg_csc_mode;
    hdmi_tx_reg_write(reg_addr, csc_ctrl.u32);

    return;
}

hi_void hdmi_reg_csc_saturate_en_set(unsigned int reg_csc_saturate_en)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl csc_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->csc_ctrl.u32);
    csc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    csc_ctrl.bits.reg_csc_saturate_en = reg_csc_saturate_en;
    hdmi_tx_reg_write(reg_addr, csc_ctrl.u32);

    return;
}

hi_void hdmi_reg_csc_en_set(unsigned int reg_csc_en)
{
    hi_u32 *reg_addr = NULL;
    multi_csc_ctrl csc_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->csc_ctrl.u32);
    csc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    csc_ctrl.bits.reg_csc_en = reg_csc_en;
    hdmi_tx_reg_write(reg_addr, csc_ctrl.u32);

    return;
}

hi_void hdmi_reg_dwsm_vert_byp_set(unsigned int reg_dwsm_vert_byp)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl dwsm_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dwsm_ctrl.u32);
    dwsm_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dwsm_ctrl.bits.reg_dwsm_vert_byp = reg_dwsm_vert_byp;
    hdmi_tx_reg_write(reg_addr, dwsm_ctrl.u32);

    return;
}

hi_void hdmi_reg_dwsm_vert_en_set(unsigned int reg_dwsm_vert_en)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl dwsm_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dwsm_ctrl.u32);
    dwsm_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dwsm_ctrl.bits.reg_dwsm_vert_en = reg_dwsm_vert_en;
    hdmi_tx_reg_write(reg_addr, dwsm_ctrl.u32);

    return;
}

hi_void hdmi_reg_hori_filter_en_set(unsigned int reg_hori_filter_en)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl dwsm_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dwsm_ctrl.u32);
    dwsm_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dwsm_ctrl.bits.reg_hori_filter_en = reg_hori_filter_en;
    hdmi_tx_reg_write(reg_addr, dwsm_ctrl.u32);

    return;
}

hi_void hdmi_reg_dwsm_hori_en_set(unsigned int reg_dwsm_hori_en)
{
    hi_u32 *reg_addr = NULL;
    video_dwsm_ctrl dwsm_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dwsm_ctrl.u32);
    dwsm_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dwsm_ctrl.bits.reg_dwsm_hori_en = reg_dwsm_hori_en;
    hdmi_tx_reg_write(reg_addr, dwsm_ctrl.u32);

    return;
}

hi_void hdmi_reg_pxl_div_en_set(unsigned int reg_pxl_div_en)
{
    hi_u32 *reg_addr = NULL;
    data_align_ctrl align_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->align_ctrl.u32);
    align_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    align_ctrl.bits.reg_pxl_div_en = reg_pxl_div_en;
    hdmi_tx_reg_write(reg_addr, align_ctrl.u32);

    return;
}

hi_void hdmi_reg_demux_420_en_set(unsigned int reg_demux_420_en)
{
    hi_u32 *reg_addr = NULL;
    data_align_ctrl align_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->align_ctrl.u32);
    align_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    align_ctrl.bits.reg_demux_420_en = reg_demux_420_en;
    hdmi_tx_reg_write(reg_addr, align_ctrl.u32);

    return;
}

hi_void hdmi_reg_inver_sync_set(unsigned int reg_inver_sync)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl dmux_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dmux_ctrl.u32);
    dmux_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dmux_ctrl.bits.reg_inver_sync = reg_inver_sync;
    hdmi_tx_reg_write(reg_addr, dmux_ctrl.u32);

    return;
}

hi_void hdmi_reg_syncmask_en_set(unsigned int reg_syncmask_en)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl dmux_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dmux_ctrl.u32);
    dmux_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dmux_ctrl.bits.reg_syncmask_en = reg_syncmask_en;
    hdmi_tx_reg_write(reg_addr, dmux_ctrl.u32);

    return;
}

hi_void hdmi_reg_vmux_cr_sel_set(unsigned int reg_vmux_cr_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl dmux_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dmux_ctrl.u32);
    dmux_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dmux_ctrl.bits.reg_vmux_cr_sel = reg_vmux_cr_sel;
    hdmi_tx_reg_write(reg_addr, dmux_ctrl.u32);

    return;
}

hi_void hdmi_reg_vmux_cb_sel_set(unsigned int reg_vmux_cb_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl dmux_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dmux_ctrl.u32);
    dmux_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dmux_ctrl.bits.reg_vmux_cb_sel = reg_vmux_cb_sel;
    hdmi_tx_reg_write(reg_addr, dmux_ctrl.u32);

    return;
}

hi_void hdmi_reg_vmux_y_sel_set(unsigned int reg_vmux_y_sel)
{
    hi_u32 *reg_addr = NULL;
    video_dmux_ctrl dmux_ctrl;

    reg_addr = (hi_u32 *)&(g_video_path_all_reg->vo_dmux_ctrl.u32);
    dmux_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    dmux_ctrl.bits.reg_vmux_y_sel = reg_vmux_y_sel;
    hdmi_tx_reg_write(reg_addr, dmux_ctrl.u32);

    return;
}

