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

int hdmi_tx_reg_type_init(void)
{
    g_tx_hdmi_all_reg = (volatile tx_hdmi_regs *)(HDMI_TX_BASE_ADDR + HDMI_TX_BASE_ADDR_HDMITX);

    return HI_SUCCESS;
}

hi_void hdmi_tx_reg_type_deinit(void)
{
    if (g_tx_hdmi_all_reg != NULL) {
        g_tx_hdmi_all_reg = HI_NULL;
    }

    return;
}

int hdmi_avi_pkt_header_hb_set(unsigned int hb0, unsigned int hb1, unsigned int hb2)
{
    hi_u32 *reg_addr = NULL;
    avi_pkt_header tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_packet_header.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_pkt_hb2 = hb2;
    tmp.bits.avi_pkt_hb1 = hb1;
    tmp.bits.avi_pkt_hb0 = hb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);
    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt0_l_pb_set(unsigned int avi_pkt0_pb0, unsigned int avi_pkt0_pb1, unsigned int avi_pkt0_pb2,
    unsigned int avi_pkt0_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt0_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck0_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt0_pb3 = avi_pkt0_pb3;
    tmp.bits.avi_sub_pkt0_pb2 = avi_pkt0_pb2;
    tmp.bits.avi_sub_pkt0_pb1 = avi_pkt0_pb1;
    tmp.bits.avi_sub_pkt0_pb0 = avi_pkt0_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt0_h_pb_set(unsigned int avi_pkt0_pb4, unsigned int avi_pkt0_pb5, unsigned int avi_pkt0_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt0_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck0_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt0_pb6 = avi_pkt0_pb6;
    tmp.bits.avi_sub_pkt0_pb5 = avi_pkt0_pb5;
    tmp.bits.avi_sub_pkt0_pb4 = avi_pkt0_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt1_l_pb_set(unsigned int avi_pkt1_pb0, unsigned int avi_pkt1_pb1, unsigned int avi_pkt1_pb2,
    unsigned int avi_pkt1_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt1_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck1_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt1_pb3 = avi_pkt1_pb3;
    tmp.bits.avi_sub_pkt1_pb2 = avi_pkt1_pb2;
    tmp.bits.avi_sub_pkt1_pb1 = avi_pkt1_pb1;
    tmp.bits.avi_sub_pkt1_pb0 = avi_pkt1_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt1_h_pb_set(unsigned int avi_pkt1_pb4, unsigned int avi_pkt1_pb5, unsigned int avi_pkt1_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt1_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck1_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt1_pb6 = avi_pkt1_pb6;
    tmp.bits.avi_sub_pkt1_pb5 = avi_pkt1_pb5;
    tmp.bits.avi_sub_pkt1_pb4 = avi_pkt1_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt2_l_pb_set(unsigned int avi_pkt2_pb0, unsigned int avi_pkt2_pb1, unsigned int avi_pkt2_pb2,
    unsigned int avi_pkt2_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt2_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck2_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt2_pb3 = avi_pkt2_pb3;
    tmp.bits.avi_sub_pkt2_pb2 = avi_pkt2_pb2;
    tmp.bits.avi_sub_pkt2_pb1 = avi_pkt2_pb1;
    tmp.bits.avi_sub_pkt2_pb0 = avi_pkt2_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt2_h_pb_set(unsigned int avi_pkt2_pb4, unsigned int avi_pkt2_pb5, unsigned int avi_pkt2_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt2_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck2_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt2_pb6 = avi_pkt2_pb6;
    tmp.bits.avi_sub_pkt2_pb5 = avi_pkt2_pb5;
    tmp.bits.avi_sub_pkt2_pb4 = avi_pkt2_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt3_l_pb_set(unsigned int avi_pkt3_pb0, unsigned int avi_pkt3_pb1, unsigned int avi_pkt3_pb2,
    unsigned int avi_pkt3_pb3)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt3_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck3_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt3_pb3 = avi_pkt3_pb3;
    tmp.bits.avi_sub_pkt3_pb2 = avi_pkt3_pb2;
    tmp.bits.avi_sub_pkt3_pb1 = avi_pkt3_pb1;
    tmp.bits.avi_sub_pkt3_pb0 = avi_pkt3_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avi_sub_pkt3_h_pb_set(unsigned int avi_pkt3_pb4, unsigned int avi_pkt3_pb5, unsigned int avi_pkt3_pb6)
{
    hi_u32 *reg_addr = NULL;
    avi_sub_pkt3_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_pck3_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.avi_sub_pkt3_pb6 = avi_pkt3_pb6;
    tmp.bits.avi_sub_pkt3_pb5 = avi_pkt3_pb5;
    tmp.bits.avi_sub_pkt3_pb4 = avi_pkt3_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_pkt_header_hb_set(unsigned int hb0, unsigned int hb1, unsigned int hb2)
{
    hi_u32 *reg_addr = NULL;
    vsif_pkt_header tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_packet_header.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_pkt_hb2 = hb2;
    tmp.bits.vsif_pkt_hb1 = hb1;
    tmp.bits.vsif_pkt_hb0 = hb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt0_l_pb_set(unsigned int vsif_pkt0_pb0, unsigned int vsif_pkt0_pb1, unsigned int vsif_pkt0_pb2,
    unsigned int vsif_pkt0_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt0_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck0_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt0_pb3 = vsif_pkt0_pb3;
    tmp.bits.vsif_sub_pkt0_pb2 = vsif_pkt0_pb2;
    tmp.bits.vsif_sub_pkt0_pb1 = vsif_pkt0_pb1;
    tmp.bits.vsif_sub_pkt0_pb0 = vsif_pkt0_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt0_h_pb_set(unsigned int vsif_pkt0_pb4, unsigned int vsif_pkt0_pb5, unsigned int vsif_pkt0_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt0_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck0_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt0_pb6 = vsif_pkt0_pb6;
    tmp.bits.vsif_sub_pkt0_pb5 = vsif_pkt0_pb5;
    tmp.bits.vsif_sub_pkt0_pb4 = vsif_pkt0_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt1_l_pb_set(unsigned int vsif_pkt1_pb0, unsigned int vsif_pkt1_pb1, unsigned int vsif_pkt1_pb2,
    unsigned int vsif_pkt1_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt1_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck1_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt1_pb3 = vsif_pkt1_pb3;
    tmp.bits.vsif_sub_pkt1_pb2 = vsif_pkt1_pb2;
    tmp.bits.vsif_sub_pkt1_pb1 = vsif_pkt1_pb1;
    tmp.bits.vsif_sub_pkt1_pb0 = vsif_pkt1_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt1_h_pb_set(unsigned int vsif_pkt1_pb4, unsigned int vsif_pkt1_pb5, unsigned int vsif_pkt1_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt1_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck1_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt1_pb6 = vsif_pkt1_pb6;
    tmp.bits.vsif_sub_pkt1_pb5 = vsif_pkt1_pb5;
    tmp.bits.vsif_sub_pkt1_pb4 = vsif_pkt1_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt2_l_pb_set(unsigned int vsif_pkt2_pb0, unsigned int vsif_pkt2_pb1, unsigned int vsif_pkt2_pb2,
    unsigned int vsif_pkt2_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt2_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck2_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt2_pb3 = vsif_pkt2_pb3;
    tmp.bits.vsif_sub_pkt2_pb2 = vsif_pkt2_pb2;
    tmp.bits.vsif_sub_pkt2_pb1 = vsif_pkt2_pb1;
    tmp.bits.vsif_sub_pkt2_pb0 = vsif_pkt2_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt2_h_pb_set(unsigned int vsif_pkt2_pb4, unsigned int vsif_pkt2_pb5, unsigned int vsif_pkt2_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt2_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck2_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt2_pb6 = vsif_pkt2_pb6;
    tmp.bits.vsif_sub_pkt2_pb5 = vsif_pkt2_pb5;
    tmp.bits.vsif_sub_pkt2_pb4 = vsif_pkt2_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt3_l_pb_set(unsigned int vsif_pkt3_pb0, unsigned int vsif_pkt3_pb1, unsigned int vsif_pkt3_pb2,
    unsigned int vsif_pkt3_pb3)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt3_l tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck3_l.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt3_pb3 = vsif_pkt3_pb3;
    tmp.bits.vsif_sub_pkt3_pb2 = vsif_pkt3_pb2;
    tmp.bits.vsif_sub_pkt3_pb1 = vsif_pkt3_pb1;
    tmp.bits.vsif_sub_pkt3_pb0 = vsif_pkt3_pb0;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_vsif_sub_pkt3_h_pb_set(unsigned int vsif_pkt3_pb4, unsigned int vsif_pkt3_pb5, unsigned int vsif_pkt3_pb6)
{
    hi_u32 *reg_addr = NULL;
    vsif_sub_pkt3_h tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_pck3_h.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.vsif_sub_pkt3_pb6 = vsif_pkt3_pb6;
    tmp.bits.vsif_sub_pkt3_pb5 = vsif_pkt3_pb5;
    tmp.bits.vsif_sub_pkt3_pb4 = vsif_pkt3_pb4;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_avi_rpt_en_set(unsigned int cea_avi_rpt_en)
{
    hi_u32 *reg_addr = NULL;
    cea_avi_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_avi_rpt_en = cea_avi_rpt_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_avi_en_set(unsigned int cea_avi_en)
{
    hi_u32 *reg_addr = NULL;
    cea_avi_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_avi_en = cea_avi_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_gen_en_set(unsigned int cea_gen_en)
{
    hi_u32 *reg_addr = NULL;
    cea_gen_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->gen_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_gen_en = cea_gen_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_cp_rpt_cnt_set(unsigned int cea_cp_rpt_cnt)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_cp_rpt_cnt = cea_cp_rpt_cnt;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_cp_rpt_en_set(unsigned int cea_cp_rpt_en)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_cp_rpt_en = cea_cp_rpt_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_cp_en_set(unsigned int cea_cp_en)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_cp_en = cea_cp_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_vsif_rpt_en_set(unsigned int cea_vsif_rpt_en)
{
    hi_u32 *reg_addr = NULL;
    cea_vsif_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_vsif_rpt_en = cea_vsif_rpt_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_vsif_en_set(unsigned int cea_vsif_en)
{
    hi_u32 *reg_addr = NULL;
    cea_vsif_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->vsif_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cea_vsif_en = cea_vsif_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avmixer_config_dc_pkt_en_set(unsigned int dc_pkt_en)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avmixer_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.dc_pkt_en = dc_pkt_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avmixer_config_hdmi_mode_set(unsigned int hdmi_mode)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avmixer_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.hdmi_mode = hdmi_mode;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cp_clr_avmute_set(unsigned int cp_clr_avmute)
{
    hi_u32 *reg_addr = NULL;
    cp_pkt_avmute tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_avmute.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cp_clr_avmute = cp_clr_avmute;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cp_set_avmute_set(unsigned int cp_set_avmute)
{
    hi_u32 *reg_addr = NULL;
    cp_pkt_avmute tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_avmute.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.cp_set_avmute = cp_set_avmute;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_enc_bypass_set(unsigned int enc_bypass)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.enc_bypass = enc_bypass;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_enc_scr_on_set(unsigned int enc_scr_on)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.enc_scr_on = enc_scr_on;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_enc_hdmi2_on_set(unsigned int enc_hdmi2_on)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.enc_hdmi2_on = enc_hdmi2_on;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_cea_avi_en_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    cea_avi_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avi_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.cea_avi_en;
}

int hdmi_cea_cp_rpt_en_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    cea_cp_cfg tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.cea_cp_rpt_en;
}

int hdmi_avmixer_config_null_pkt_en_set(unsigned int null_pkt_en)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avmixer_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.null_pkt_en = null_pkt_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_avmixer_config_hdmi_mode_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    avmixer_config tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->avmixer_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.hdmi_mode;
}

int hdmi_cp_set_avmute_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    cp_pkt_avmute tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->cp_avmute.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.cp_set_avmute;
}

int hdmi_enc_scr_on_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    hdmi_enc_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->enc_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.enc_scr_on;
}

int hdmi_ctl_type_config_set(unsigned int ctl_config)
{
    hi_u32 *reg_addr = NULL;
    ctl_type_config tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->ctl_type_cfg.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.ctl_type_config = ctl_config;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_htotal_hw_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    htotal_hw tmp;

    reg_addr = (hi_u32 *)&(g_tx_hdmi_all_reg->htotal.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.htotal_hw;
}

