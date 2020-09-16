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

#include "hdmi_reg_tx.h"
#include "hdmi_product_define.h"

volatile tx_hdmi_regs *g_tx_hdmi_all_reg = NULL;

int hdmi_tx_hdmi_regs_init(void)
{
    g_tx_hdmi_all_reg = (volatile tx_hdmi_regs *)(HDMI_TX_BASE_ADDR + HDMI_TX_BASE_ADDR_HDMITX);
    return HI_SUCCESS;
}

hi_void hdmi_tx_hdmi_regs_deinit(void)
{
    if (g_tx_hdmi_all_reg != HI_NULL) {
        g_tx_hdmi_all_reg = HI_NULL;
    }
    return;
}

hi_void hdmi_tx_tmds_pack_mode_set(unsigned int tmds_pack_mode)
{
    hi_u32 *reg_addr = NULL;
    tx_pack_fifo_ctrl pack_fifo_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->pack_fifo_ctrl.u32);
    pack_fifo_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    pack_fifo_ctrl.bits.tmds_pack_mode = tmds_pack_mode;
    hdmi_tx_reg_write(reg_addr, pack_fifo_ctrl.u32);

    return;
}

hi_void hdmi_avi_pkt_header_hb_set(unsigned int hb0, unsigned int hb1, unsigned int hb2)
{
    hi_u32 *reg_addr = NULL;
    avi_pkt_header pkt_header;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_header.u32);
    pkt_header.u32 = hdmi_tx_reg_read(reg_addr);
    pkt_header.bits.avi_pkt_hb2 = hb2;
    pkt_header.bits.avi_pkt_hb1 = hb1;
    pkt_header.bits.avi_pkt_hb0 = hb0;
    hdmi_tx_reg_write(reg_addr, pkt_header.u32);
    return;
}

hi_void hdmi_l_avi_pkt0_pb_set(unsigned int avi_pkt0_pb0, unsigned int avi_pkt0_pb1,
                               unsigned int avi_pkt0_pb2, unsigned int avi_pkt0_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt0_l sub_pkt0_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt0_l.u32);
    sub_pkt0_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt0_l.bits.avi_sub_pkt0_pb3 = avi_pkt0_pb3;
    sub_pkt0_l.bits.avi_sub_pkt0_pb2 = avi_pkt0_pb2;
    sub_pkt0_l.bits.avi_sub_pkt0_pb1 = avi_pkt0_pb1;
    sub_pkt0_l.bits.avi_sub_pkt0_pb0 = avi_pkt0_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt0_l.u32);

    return;
}

hi_void hdmi_h_avi_pkt0_pb_set(unsigned int avi_pkt0_pb4, unsigned int avi_pkt0_pb5,
                               unsigned int avi_pkt0_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt0_h sub_pkt0_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt0_h.u32);
    sub_pkt0_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt0_h.bits.avi_sub_pkt0_pb6 = avi_pkt0_pb6;
    sub_pkt0_h.bits.avi_sub_pkt0_pb5 = avi_pkt0_pb5;
    sub_pkt0_h.bits.avi_sub_pkt0_pb4 = avi_pkt0_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt0_h.u32);

    return;
}

hi_void hdmi_l_avi_pkt1_pb_set(unsigned int avi_pkt1_pb0, unsigned int avi_pkt1_pb1,
                               unsigned int avi_pkt1_pb2, unsigned int avi_pkt1_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt1_l sub_pkt1_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt1_l.u32);
    sub_pkt1_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt1_l.bits.avi_sub_pkt1_pb3 = avi_pkt1_pb3;
    sub_pkt1_l.bits.avi_sub_pkt1_pb2 = avi_pkt1_pb2;
    sub_pkt1_l.bits.avi_sub_pkt1_pb1 = avi_pkt1_pb1;
    sub_pkt1_l.bits.avi_sub_pkt1_pb0 = avi_pkt1_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt1_l.u32);

    return;
}

hi_void hdmi_h_avi_pkt1_pb_set(unsigned int avi_pkt1_pb4, unsigned int avi_pkt1_pb5,
                               unsigned int avi_pkt1_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt1_h sub_pkt1_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt1_h.u32);
    sub_pkt1_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt1_h.bits.avi_sub_pkt1_pb6 = avi_pkt1_pb6;
    sub_pkt1_h.bits.avi_sub_pkt1_pb5 = avi_pkt1_pb5;
    sub_pkt1_h.bits.avi_sub_pkt1_pb4 = avi_pkt1_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt1_h.u32);

    return;
}

hi_void hdmi_l_avi_pkt2_pb_set(unsigned int avi_pkt2_pb0, unsigned int avi_pkt2_pb1,
                               unsigned int avi_pkt2_pb2, unsigned int avi_pkt2_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt2_l sub_pkt2_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt2_l.u32);
    sub_pkt2_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt2_l.bits.avi_sub_pkt2_pb3 = avi_pkt2_pb3;
    sub_pkt2_l.bits.avi_sub_pkt2_pb2 = avi_pkt2_pb2;
    sub_pkt2_l.bits.avi_sub_pkt2_pb1 = avi_pkt2_pb1;
    sub_pkt2_l.bits.avi_sub_pkt2_pb0 = avi_pkt2_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt2_l.u32);

    return;
}

hi_void hdmi_h_avi_pkt2_pb_set(unsigned int avi_pkt2_pb4, unsigned int avi_pkt2_pb5,
                               unsigned int avi_pkt2_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt2_h sub_pkt2_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt2_h.u32);
    sub_pkt2_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt2_h.bits.avi_sub_pkt2_pb6 = avi_pkt2_pb6;
    sub_pkt2_h.bits.avi_sub_pkt2_pb5 = avi_pkt2_pb5;
    sub_pkt2_h.bits.avi_sub_pkt2_pb4 = avi_pkt2_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt2_h.u32);

    return;
}

hi_void hdmi_l_avi_pkt3_pb_set(unsigned int avi_pkt3_pb0, unsigned int avi_pkt3_pb1,
                               unsigned int avi_pkt3_pb2, unsigned int avi_pkt3_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt3_l sub_pkt3_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt3_l.u32);
    sub_pkt3_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt3_l.bits.avi_sub_pkt3_pb3 = avi_pkt3_pb3;
    sub_pkt3_l.bits.avi_sub_pkt3_pb2 = avi_pkt3_pb2;
    sub_pkt3_l.bits.avi_sub_pkt3_pb1 = avi_pkt3_pb1;
    sub_pkt3_l.bits.avi_sub_pkt3_pb0 = avi_pkt3_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt3_l.u32);

    return;
}

hi_void hdmi_h_avi_pkt3_pb_set(unsigned int avi_pkt3_pb4, unsigned int avi_pkt3_pb5,
                               unsigned int avi_pkt3_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt3_h sub_pkt3_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pkt3_h.u32);
    sub_pkt3_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt3_h.bits.avi_sub_pkt3_pb6 = avi_pkt3_pb6;
    sub_pkt3_h.bits.avi_sub_pkt3_pb5 = avi_pkt3_pb5;
    sub_pkt3_h.bits.avi_sub_pkt3_pb4 = avi_pkt3_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt3_h.u32);

    return;
}

hi_void hdmi_vsif_pkt_header_hb_set(unsigned int hb0, unsigned int hb1, unsigned int hb2)
{
    hi_u32 *reg_addr = NULL;
    vsif_pkt_header pkt_header;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_header.u32);
    pkt_header.u32 = hdmi_tx_reg_read(reg_addr);
    pkt_header.bits.vsif_pkt_hb2 = hb2;
    pkt_header.bits.vsif_pkt_hb1 = hb1;
    pkt_header.bits.vsif_pkt_hb0 = hb0;
    hdmi_tx_reg_write(reg_addr, pkt_header.u32);

    return;
}

hi_void hdmi_l_vsif_pkt0_pb_set(unsigned int vsif_pkt0_pb0, unsigned int vsif_pkt0_pb1,
                                unsigned int vsif_pkt0_pb2, unsigned int vsif_pkt0_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt0_l sub_pkt0_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt0_l.u32);
    sub_pkt0_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt0_l.bits.vsif_sub_pkt0_pb3 = vsif_pkt0_pb3;
    sub_pkt0_l.bits.vsif_sub_pkt0_pb2 = vsif_pkt0_pb2;
    sub_pkt0_l.bits.vsif_sub_pkt0_pb1 = vsif_pkt0_pb1;
    sub_pkt0_l.bits.vsif_sub_pkt0_pb0 = vsif_pkt0_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt0_l.u32);

    return;
}

hi_void hdmi_h_vsif_pkt0_pb_set(unsigned int vsif_pkt0_pb4, unsigned int vsif_pkt0_pb5,
                                unsigned int vsif_pkt0_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt0_h sub_pkt0_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt0_h.u32);
    sub_pkt0_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt0_h.bits.vsif_sub_pkt0_pb6 = vsif_pkt0_pb6;
    sub_pkt0_h.bits.vsif_sub_pkt0_pb5 = vsif_pkt0_pb5;
    sub_pkt0_h.bits.vsif_sub_pkt0_pb4 = vsif_pkt0_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt0_h.u32);

    return;
}

hi_void hdmi_l_vsif_pkt1_pb_set(unsigned int vsif_pkt1_pb0, unsigned int vsif_pkt1_pb1,
                                unsigned int vsif_pkt1_pb2, unsigned int vsif_pkt1_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt1_l sub_pkt1_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt1_l.u32);
    sub_pkt1_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt1_l.bits.vsif_sub_pkt1_pb3 = vsif_pkt1_pb3;
    sub_pkt1_l.bits.vsif_sub_pkt1_pb2 = vsif_pkt1_pb2;
    sub_pkt1_l.bits.vsif_sub_pkt1_pb1 = vsif_pkt1_pb1;
    sub_pkt1_l.bits.vsif_sub_pkt1_pb0 = vsif_pkt1_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt1_l.u32);

    return;
}

hi_void hdmi_h_vsif_pkt1_pb_set(unsigned int vsif_pkt1_pb4, unsigned int vsif_pkt1_pb5,
                                unsigned int vsif_pkt1_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt1_h sub_pkt1_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt1_h.u32);
    sub_pkt1_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt1_h.bits.vsif_sub_pkt1_pb6 = vsif_pkt1_pb6;
    sub_pkt1_h.bits.vsif_sub_pkt1_pb5 = vsif_pkt1_pb5;
    sub_pkt1_h.bits.vsif_sub_pkt1_pb4 = vsif_pkt1_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt1_h.u32);

    return;
}

hi_void hdmi_l_vsif_pkt2_pb_set(unsigned int vsif_pkt2_pb0, unsigned int vsif_pkt2_pb1,
                                unsigned int vsif_pkt2_pb2, unsigned int vsif_pkt2_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt2_l sub_pkt2_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt2_l.u32);
    sub_pkt2_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt2_l.bits.vsif_sub_pkt2_pb3 = vsif_pkt2_pb3;
    sub_pkt2_l.bits.vsif_sub_pkt2_pb2 = vsif_pkt2_pb2;
    sub_pkt2_l.bits.vsif_sub_pkt2_pb1 = vsif_pkt2_pb1;
    sub_pkt2_l.bits.vsif_sub_pkt2_pb0 = vsif_pkt2_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt2_l.u32);

    return;
}

hi_void hdmi_h_vsif_pkt2_pb_set(unsigned int vsif_pkt2_pb4, unsigned int vsif_pkt2_pb5,
                                unsigned int vsif_pkt2_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt2_h sub_pkt2_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt2_h.u32);
    sub_pkt2_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt2_h.bits.vsif_sub_pkt2_pb6 = vsif_pkt2_pb6;
    sub_pkt2_h.bits.vsif_sub_pkt2_pb5 = vsif_pkt2_pb5;
    sub_pkt2_h.bits.vsif_sub_pkt2_pb4 = vsif_pkt2_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt2_h.u32);

    return;
}

hi_void hdmi_l_vsif_pkt3_pb_set(unsigned int vsif_pkt3_pb0, unsigned int vsif_pkt3_pb1,
                                unsigned int vsif_pkt3_pb2, unsigned int vsif_pkt3_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt3_l sub_pkt3_l;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt3_l.u32);
    sub_pkt3_l.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt3_l.bits.vsif_sub_pkt3_pb3 = vsif_pkt3_pb3;
    sub_pkt3_l.bits.vsif_sub_pkt3_pb2 = vsif_pkt3_pb2;
    sub_pkt3_l.bits.vsif_sub_pkt3_pb1 = vsif_pkt3_pb1;
    sub_pkt3_l.bits.vsif_sub_pkt3_pb0 = vsif_pkt3_pb0;
    hdmi_tx_reg_write(reg_addr, sub_pkt3_l.u32);

    return;
}

hi_void hdmi_h_vsif_pkt3_pb_set(unsigned int vsif_pkt3_pb4, unsigned int vsif_pkt3_pb5,
                                unsigned int vsif_pkt3_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt3_h sub_pkt3_h;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pkt3_h.u32);
    sub_pkt3_h.u32 = hdmi_tx_reg_read(reg_addr);
    sub_pkt3_h.bits.vsif_sub_pkt3_pb6 = vsif_pkt3_pb6;
    sub_pkt3_h.bits.vsif_sub_pkt3_pb5 = vsif_pkt3_pb5;
    sub_pkt3_h.bits.vsif_sub_pkt3_pb4 = vsif_pkt3_pb4;
    hdmi_tx_reg_write(reg_addr, sub_pkt3_h.u32);

    return;
}

hi_void hdmi_cea_avi_rpt_en_set(unsigned int cea_avi_rpt_en)
{
    hi_u32 *reg_addr = NULL;
    cea_avi_cfg avi_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_cfg.u32);
    avi_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avi_cfg.bits.cea_avi_rpt_en = cea_avi_rpt_en;
    hdmi_tx_reg_write(reg_addr, avi_cfg.u32);

    return;
}

hi_void hdmi_cea_avi_en_set(unsigned int cea_avi_en)
{
    hi_u32 *reg_addr = NULL;
    cea_avi_cfg avi_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_cfg.u32);
    avi_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avi_cfg.bits.cea_avi_en = cea_avi_en;
    hdmi_tx_reg_write(reg_addr, avi_cfg.u32);

    return;
}

hi_void hdmi_cea_cp_rpt_cnt_set(unsigned int cea_cp_rpt_cnt)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg cp_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    cp_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    cp_cfg.bits.cea_cp_rpt_cnt = cea_cp_rpt_cnt;
    hdmi_tx_reg_write(reg_addr, cp_cfg.u32);

    return;
}

hi_void hdmi_cea_cp_rpt_en_set(unsigned int cea_cp_rpt_en)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg cp_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    cp_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    cp_cfg.bits.cea_cp_rpt_en = cea_cp_rpt_en;
    hdmi_tx_reg_write(reg_addr, cp_cfg.u32);

    return;
}

hi_void hdmi_cea_cp_en_set(unsigned int cea_cp_en)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg cp_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    cp_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    cp_cfg.bits.cea_cp_en = cea_cp_en;
    hdmi_tx_reg_write(reg_addr, cp_cfg.u32);

    return;
}

hi_void hdmi_cea_vsif_rpt_en_set(unsigned int cea_vsif_rpt_en)
{
    hi_u32 *reg_addr = NULL;
    cea_vsif_cfg vsif_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_cfg.u32);
    vsif_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    vsif_cfg.bits.cea_vsif_rpt_en = cea_vsif_rpt_en;
    hdmi_tx_reg_write(reg_addr, vsif_cfg.u32);

    return;
}

hi_void hdmi_cea_vsif_en_set(unsigned int cea_vsif_en)
{
    hi_u32 *reg_addr = NULL;
    cea_vsif_cfg vsif_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_cfg.u32);
    vsif_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    vsif_cfg.bits.cea_vsif_en = cea_vsif_en;
    hdmi_tx_reg_write(reg_addr, vsif_cfg.u32);

    return;
}

hi_void hdmi_avmixer_config_eess_mode_en_set(unsigned int eess_mode_en)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config avmixer_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->reg_avmixer_config.u32);
    avmixer_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avmixer_cfg.bits.eess_mode_en = eess_mode_en;
    hdmi_tx_reg_write(reg_addr, avmixer_cfg.u32);

    return;
}

hi_void hdmi_avmixer_config_hdmi_dvi_sel_set(unsigned int hdmi_dvi_sel)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config avmixer_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->reg_avmixer_config.u32);
    avmixer_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avmixer_cfg.bits.hdmi_dvi_sel = hdmi_dvi_sel;
    hdmi_tx_reg_write(reg_addr, avmixer_cfg.u32);

    return;
}

hi_void hdmi_avmixer_config_dc_pkt_en_set(unsigned int dc_pkt_en)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config avmixer_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->reg_avmixer_config.u32);
    avmixer_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avmixer_cfg.bits.dc_pkt_en = dc_pkt_en;
    hdmi_tx_reg_write(reg_addr, avmixer_cfg.u32);

    return;
}

hi_void hdmi_avmixer_config_null_pkt_en_set(unsigned int null_pkt_en)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config avmixer_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->reg_avmixer_config.u32);
    avmixer_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avmixer_cfg.bits.null_pkt_en = null_pkt_en;
    hdmi_tx_reg_write(reg_addr, avmixer_cfg.u32);

    return;
}

hi_void hdmi_avmixer_config_hdmi_mode_set(unsigned int hdmi_mode)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config avmixer_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->reg_avmixer_config.u32);
    avmixer_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    avmixer_cfg.bits.hdmi_mode = hdmi_mode;
    hdmi_tx_reg_write(reg_addr, avmixer_cfg.u32);

    return;
}

hi_void hdmi_cp_clr_avmute_set(unsigned int cp_clr_avmute)
{
    hi_u32 *reg_addr = NULL;
    cp_pkt_avmute pkt_avmute;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->pkt_avmute.u32);
    pkt_avmute.u32 = hdmi_tx_reg_read(reg_addr);
    pkt_avmute.bits.cp_clr_avmute = cp_clr_avmute;
    hdmi_tx_reg_write(reg_addr, pkt_avmute.u32);

    return;
}

hi_void hdmi_cp_set_avmute_set(unsigned int cp_set_avmute)
{
    hi_u32 *reg_addr = NULL;
    cp_pkt_avmute pkt_avmute;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->pkt_avmute.u32);
    pkt_avmute.u32 = hdmi_tx_reg_read(reg_addr);
    pkt_avmute.bits.cp_set_avmute = cp_set_avmute;
    hdmi_tx_reg_write(reg_addr, pkt_avmute.u32);

    return;
}

hi_void hdmi_enc_bypass_set(unsigned int enc_bypass)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl enc_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    enc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    enc_ctrl.bits.enc_bypass = enc_bypass;
    hdmi_tx_reg_write(reg_addr, enc_ctrl.u32);

    return;
}

hi_void hdmi_enc_scr_on_set(unsigned int enc_scr_on)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl enc_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    enc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    enc_ctrl.bits.enc_scr_on = enc_scr_on;
    hdmi_tx_reg_write(reg_addr, enc_ctrl.u32);

    return;
}

hi_void hdmi_enc_hdmi2_on_set(unsigned int enc_hdmi2_on)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl enc_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    enc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    enc_ctrl.bits.enc_hdmi2_on = enc_hdmi2_on;
    hdmi_tx_reg_write(reg_addr, enc_ctrl.u32);

    return;
}

int hdmi_tx_pclk2tclk_stable_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    tx_pack_fifo_st pack_fifo_st;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->pack_fifo_st.u32);
    pack_fifo_st.u32 = hdmi_tx_reg_read(reg_addr);
    return pack_fifo_st.bits.pclk2tclk_stable;
}

int hdmi_cea_cp_rpt_en_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg cp_cfg;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    cp_cfg.u32 = hdmi_tx_reg_read(reg_addr);
    return cp_cfg.bits.cea_cp_rpt_en;
}

int hdmi_cp_set_avmute_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    cp_pkt_avmute pkt_avmute;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->pkt_avmute.u32);
    pkt_avmute.u32 = hdmi_tx_reg_read(reg_addr);
    return pkt_avmute.bits.cp_set_avmute;
}

int hdmi_enc_scr_on_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl enc_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    enc_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    return enc_ctrl.bits.enc_scr_on;
}

