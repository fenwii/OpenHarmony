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

#include "hdmi_reg_dphy.h"
#include "hdmi_product_define.h"

volatile hdmitx21_dphy_regs_type *g_hi3559a_dphy_reg_all_reg = HI_NULL;

hi_s32 hdmi_hdmitx_phy_reg_init(hi_void)
{
    g_hi3559a_dphy_reg_all_reg = (hdmitx21_dphy_regs_type *)(HDMI_TX_PHY_ADDR);
    if (g_hi3559a_dphy_reg_all_reg == HI_NULL) {
        hdmi_err("ioremap_nocache hi3559a_dphy_regAllReg failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

hi_s32 hdmi_hdmitx_phy_reg_deinit(hi_void)
{
    if (g_hi3559a_dphy_reg_all_reg != HI_NULL) {
        g_hi3559a_dphy_reg_all_reg = HI_NULL;
    }
    return HI_SUCCESS;
}

static hi_void hdmi21_txreg_write(hi_u32 *reg_addr, hi_u32 value)
{
    *(volatile hi_u32 *)reg_addr = value;
    return;
}

static hi_u32 hdmi21_txreg_read(hi_u32 *reg_addr)
{
    return *(volatile hi_u32 *)(reg_addr);
}

int hdmi_phy_csen_stb_cs_en_set(unsigned int stb_cs_en)
{
    hi_u32 *reg_addr = NULL;
    phy_csen tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_phy_csen.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_cs_en = stb_cs_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_phy_wr_stb_wen_set(unsigned int stb_wen)
{
    hi_u32 *reg_addr = NULL;
    phy_wr tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_phy_wr.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_wen = stb_wen;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_resetn_resetn_set(unsigned int reset_n)
{
    hi_u32 *reg_addr = NULL;
    resetn tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_resetn.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.reset = reset_n;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_resetn_resetn_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    resetn tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_resetn.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.reset;
}

int hdmi_fdsrcparam_src_enable_set(unsigned int src_enable)
{
    hi_u32 *reg_addr = NULL;
    fd_src_param tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fd_src_param.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.src_enable = src_enable;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_phy_wdata_stb_wdata_set(unsigned int stb_wdata)
{
    hi_u32 *reg_addr = NULL;
    phy_wdata tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_phy_wdata.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_wdata = stb_wdata;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcgset_p_fcg_lock_en_set(unsigned int fcg_lock_en)
{
    hi_u32 *reg_addr = NULL;
    fcgset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcgset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcg_lock_en = fcg_lock_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_phy_addr_stb_addr_set(unsigned int stb_addr)
{
    hi_u32 *reg_addr = NULL;
    phy_addr tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_phy_addr.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_addr = stb_addr;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_phy_rdata_stb_rdata_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    phy_rdata tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_phy_rdata.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.stb_rdata;
}

int hdmi_fdsrcparam_src_lock_cnt_set(unsigned int src_lock_cnt)
{
    hi_u32 *reg_addr = NULL;
    fd_src_param tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fd_src_param.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.src_lock_cnt = src_lock_cnt;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcparam_src_lock_val_set(unsigned int src_lock_val)
{
    hi_u32 *reg_addr = NULL;
    fd_src_param tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fd_src_param.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.src_lock_val = src_lock_val;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcfreq_src_freq_ext_set(unsigned int src_freq_ext)
{
    hi_u32 *reg_addr = NULL;
    fdsrcfreq tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcfreq.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.src_freq_ext = src_freq_ext;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcfreq_unused_2_set(unsigned int fdsrcfreq_unused_2)
{
    hi_u32 *reg_addr = NULL;
    fdsrcfreq tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcfreq.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fdsrcfreq_unused_2 = fdsrcfreq_unused_2;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_txfifoset0_unused_set(unsigned int txfifoset0_unused)
{
    hi_u32 *reg_addr = NULL;
    txfifoset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->tx_fifo_set0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.txfifoset0_unused = txfifoset0_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcfreq_src_freq_opt_set(unsigned int src_freq_opt)
{
    hi_u32 *reg_addr = NULL;
    fdsrcfreq tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcfreq.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.src_freq_opt = src_freq_opt;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcfreq_unused_1_set(unsigned int fdsrcfreq_unused_1)
{
    hi_u32 *reg_addr = NULL;
    fdsrcfreq tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcfreq.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fdsrcfreq_unused_1 = fdsrcfreq_unused_1;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcfreq_src_cnt_opt_set(unsigned int src_cnt_opt)
{
    hi_u32 *reg_addr = NULL;
    fdsrcfreq tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcfreq.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.src_cnt_opt = src_cnt_opt;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcres_src_cnt_out_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fdsrcres tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcres.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.src_cnt_out;
}

int hdmi_fdsrcres_src_det_stat_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fdsrcres tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdsrcres.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.src_det_stat;
}

int hdmi_ctset0_unused_set(unsigned int ctset0_unused)
{
    hi_u32 *reg_addr = NULL;
    ctset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_ctset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.ctset0_unused = ctset0_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ctset0_i_run_set(unsigned int run)
{
    hi_u32 *reg_addr = NULL;
    ctset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_ctset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_run = run;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ctset0_i_enable_set(unsigned int enable)
{
    hi_u32 *reg_addr = NULL;
    ctset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_ctset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_enable = enable;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccntr0_i_ref_cnt_len_set(unsigned int ref_cnt_len)
{
    hi_u32 *reg_addr = NULL;
    fccntr0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccntr0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ref_cnt_len = ref_cnt_len;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccntr0_i_vco_end_wait_len_set(unsigned int vco_end_wait_len)
{
    hi_u32 *reg_addr = NULL;
    fccntr0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccntr0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_vco_end_wait_len = vco_end_wait_len;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccntr0_i_vco_st_wait_len_set(unsigned int vco_st_wait_len)
{
    hi_u32 *reg_addr = NULL;
    fccntr0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccntr0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_vco_st_wait_len = vco_st_wait_len;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_unused_set(unsigned int fcopt_unused)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcopt_unused = fcopt_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_i_ct_idx_sel_set(unsigned int ct_idx_sel)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ct_idx_sel = ct_idx_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_unused_2_set(unsigned int fcopt_unused_2)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcopt_unused_2 = fcopt_unused_2;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_i_ct_en_set(unsigned int ct_en)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ct_en = ct_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_unused_1_set(unsigned int fcopt_unused_1)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcopt_unused_1 = fcopt_unused_1;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_i_ct_mode_set(unsigned int ct_mode)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ct_mode = ct_mode;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_i_clkdet_sel_set(unsigned int clkdet_sel)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_clkdet_sel = clkdet_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcopt_i_ct_sel_set(unsigned int ct_sel)
{
    hi_u32 *reg_addr = NULL;
    fcopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ct_sel = ct_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcstat_busy_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fcstat tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcstat.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.busy;
}

int hdmi_fcdstepset_up_sampler_ratio_sel_set(unsigned int sampler_ratio_sel)
{
    hi_u32 *reg_addr = NULL;
    fcdstepset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcdstepset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.up_sampler_ratio_sel = sampler_ratio_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcdstepset_unused_set(unsigned int fcdstepset_unused)
{
    hi_u32 *reg_addr = NULL;
    fcdstepset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcdstepset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcdstepset_unused = fcdstepset_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcdstepset_p_divn_h20_set(unsigned int divn_h20)
{
    hi_u32 *reg_addr = NULL;
    fcdstepset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcdstepset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.divn_h20 = divn_h20;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccntr1_i_ref_cnt_set(unsigned int ref_cnt)
{
    hi_u32 *reg_addr = NULL;
    fccntr1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccntr1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ref_cnt = ref_cnt;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset0_p_contin_upd_step_set(unsigned int contin_upd_step)
{
    hi_u32 *reg_addr = NULL;
    fccontinset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_step = contin_upd_step;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset0_unused_set(unsigned int fccontinset0_unused)
{
    hi_u32 *reg_addr = NULL;
    fccontinset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fccontinset0_unused = fccontinset0_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset0_p_contin_upd_pol_set(unsigned int contin_upd_pol)
{
    hi_u32 *reg_addr = NULL;
    fccontinset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_pol = contin_upd_pol;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset0_p_contin_upd_opt_set(unsigned int contin_upd_opt)
{
    hi_u32 *reg_addr = NULL;
    fccontinset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_opt = contin_upd_opt;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset0_p_contin_upd_en_set(unsigned int contin_upd_en)
{
    hi_u32 *reg_addr = NULL;
    fccontinset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_en = contin_upd_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset1_p_contin_upd_time_set(unsigned int contin_upd_time)
{
    hi_u32 *reg_addr = NULL;
    fccontinset1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_time = contin_upd_time;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset1_p_contin_upd_rate_set(unsigned int contin_upd_rate)
{
    hi_u32 *reg_addr = NULL;
    fccontinset1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_rate = contin_upd_rate;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset2_p_contin_upd_th_up_set(unsigned int contin_upd_th_up)
{
    hi_u32 *reg_addr = NULL;
    fccontinset2 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset2.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_th_up = contin_upd_th_up;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset2_unused_set(unsigned int fccontinset2_unused)
{
    hi_u32 *reg_addr = NULL;
    fccontinset2 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset2.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fccontinset2_unused = fccontinset2_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fccontinset2_p_contin_upd_th_dn_set(unsigned int contin_upd_th_dn)
{
    hi_u32 *reg_addr = NULL;
    fccontinset2 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fccontinset2.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.contin_upd_th_dn = contin_upd_th_dn;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset0_en_sdm_set(unsigned int sdm)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sdm = sdm;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_hdmi_mode_reg_hdmi_mode_en_set(unsigned int reg_hdmi_mode_en)
{
    hi_u32 *reg_addr = NULL;
    hdmi_mode tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_hdmi_mode.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.reg_hdmi_mode_en = reg_hdmi_mode_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset0_en_sdm_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.sdm;
}

int hdmi_fdivset0_en_mod_set(unsigned int mod)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.mod = mod;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset0_en_mod_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.mod;
}

int hdmi_fdivset0_en_ctrl_set(unsigned int ctrl)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.ctrl = ctrl;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset0_en_ctrl_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.ctrl;
}

int hdmi_fdivset0_init_set(unsigned int init)
{
    hi_u32 *reg_addr = NULL;
    fdivset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.init = init;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset3_mod_n_set(unsigned int mod_n)
{
    hi_u32 *reg_addr = NULL;
    fdivset3 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset3.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.mod_n = mod_n;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset3_mod_t_set(unsigned int mod_t)
{
    hi_u32 *reg_addr = NULL;
    fdivset3 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset3.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.mod_t = mod_t;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset3_mod_len_set(unsigned int mod_len)
{
    hi_u32 *reg_addr = NULL;
    fdivset3 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset3.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.mod_len = mod_len;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivset4_mod_d_set(unsigned int mod_d)
{
    hi_u32 *reg_addr = NULL;
    fdivset4 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivset4.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.mod_d = mod_d;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdsrcparam_unused_set(unsigned int fdsrcparam_unused)
{
    hi_u32 *reg_addr = NULL;
    fd_src_param tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fd_src_param.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fdsrcparam_unused = fdsrcparam_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivstat1_i_fdiv_in_set(unsigned int fdiv_in)
{
    hi_u32 *reg_addr = NULL;
    fdivstat1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivstat1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_fdiv_in = fdiv_in;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivmanual_i_mdiv_set(unsigned int mdiv)
{
    hi_u32 *reg_addr = NULL;
    fdivmanual tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivmanual.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_mdiv = mdiv;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_frl_clock_set(unsigned int sw_reset_frl_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_frl_clock = sw_reset_frl_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fdivmanual_i_manual_en_set(unsigned int manual_en)
{
    hi_u32 *reg_addr = NULL;
    fdivmanual tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fdivmanual.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_manual_en = manual_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_stbopt_stb_delay1_set(unsigned int stb_delay1)
{
    hi_u32 *reg_addr = NULL;
    stbopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_stbopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_delay1 = stb_delay1;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_refclksel_i_ref_clk_sel_set(unsigned int ref_clk_sel)
{
    hi_u32 *reg_addr = NULL;
    refclksel tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_refclksel.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_ref_clk_sel = ref_clk_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcgset_p_fcg_dither_en_set(unsigned int fcg_dither_en)
{
    hi_u32 *reg_addr = NULL;
    fcgset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcgset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcg_dither_en = fcg_dither_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcgset_p_fcg_dlf_en_set(unsigned int fcg_dlf_en)
{
    hi_u32 *reg_addr = NULL;
    fcgset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcgset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcg_dlf_en = fcg_dlf_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcgset_p_fcg_en_set(unsigned int fcg_en)
{
    hi_u32 *reg_addr = NULL;
    fcgset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcgset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fcg_en = fcg_en;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_txfifoset0_p_enable_h20_set(unsigned int enable_h20)
{
    hi_u32 *reg_addr = NULL;
    txfifoset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->tx_fifo_set0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.enable_h20 = enable_h20;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_txfifoset0_p_pr_en_h20_set(unsigned int pr_en_h20)
{
    hi_u32 *reg_addr = NULL;
    txfifoset0 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->tx_fifo_set0.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.pr_en_h20 = pr_en_h20;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_txdataoutsel_p_ch_out_sel_set(unsigned int ch_out_sel)
{
    hi_u32 *reg_addr = NULL;
    txdataoutsel tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->tx_data_out_sel.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.ch_out_sel = ch_out_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_hsset_p_hsset_set(unsigned int hs_set)
{
    hi_u32 *reg_addr = NULL;
    hsset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_hsset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.hsset = hs_set;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_global_reset_set(unsigned int global_reset)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.global_reset = global_reset;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_unused_set(unsigned int swreset_unused)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.swreset_unused = swreset_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_dac_clock_gat_set(unsigned int dac_clock_gat)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.dac_clock_gat = dac_clock_gat;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_stbopt_stb_delay2_set(unsigned int stb_delay2)
{
    hi_u32 *reg_addr = NULL;
    stbopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_stbopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_delay2 = stb_delay2;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_stbopt_stb_cs_sel_set(unsigned int stb_cs_sel)
{
    hi_u32 *reg_addr = NULL;
    stbopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_stbopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_cs_sel = stb_cs_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_stbopt_stb_acc_sel_set(unsigned int stb_acc_sel)
{
    hi_u32 *reg_addr = NULL;
    stbopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_stbopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_acc_sel = stb_acc_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_stbopt_stb_delay0_set(unsigned int stb_delay0)
{
    hi_u32 *reg_addr = NULL;
    stbopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_stbopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.stb_delay0 = stb_delay0;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_clkset_p_fd_clk_sel_set(unsigned int fd_clk_sel)
{
    hi_u32 *reg_addr = NULL;
    clkset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_clkset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fd_clk_sel = fd_clk_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_clkset_p_refclk_sel_set(unsigned int refclk_sel)
{
    hi_u32 *reg_addr = NULL;
    clkset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_clkset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.refclk_sel = refclk_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_clkset_p_ctman_set(unsigned int ctman)
{
    hi_u32 *reg_addr = NULL;
    clkset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_clkset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.ctman = ctman;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_stbopt_req_length_set(unsigned int req_length)
{
    hi_u32 *reg_addr = NULL;
    stbopt tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_stbopt.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.req_length = req_length;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_clkset_p_fdivclk_sel_set(unsigned int fdivclk_sel)
{
    hi_u32 *reg_addr = NULL;
    clkset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_clkset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.fdivclk_sel = fdivclk_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_clkset_mod_div_val_set(unsigned int mod_div_val)
{
    hi_u32 *reg_addr = NULL;
    clkset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_clkset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.mod_div_val = mod_div_val;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_clkset_p_modclk_sel_set(unsigned int modclk_sel)
{
    hi_u32 *reg_addr = NULL;
    clkset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_clkset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.modclk_sel = modclk_sel;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ctset1_i_mpll_fcon_set(unsigned int mpll_fcon)
{
    hi_u32 *reg_addr = NULL;
    ctset1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_ctset1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_mpll_fcon = mpll_fcon;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ctset1_i_mpll_ctlck_set(unsigned int mpll_ctlck)
{
    hi_u32 *reg_addr = NULL;
    ctset1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_ctset1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.i_mpll_ctlck = mpll_ctlck;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ctset1_ctset1_unused_set(unsigned int ctset1_unused)
{
    hi_u32 *reg_addr = NULL;
    ctset1 tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_ctset1.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.ctset1_unused = ctset1_unused;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_fcstat_error_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fcstat tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcstat.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.error;
}

int hdmi_fcstat_done_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fcstat tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcstat.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.done;
}

int hdmi_fcstat_clk_ok_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    fcstat tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_fcstat.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    return tmp.bits.clk_ok;
}

int hdmi_swreset_sw_reset_mod_clock_set(unsigned int sw_reset_mod_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_mod_clock = sw_reset_mod_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_tmds_clock_set(unsigned int sw_reset_tmds_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_tmds_clock = sw_reset_tmds_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_mpll_clock_set(unsigned int sw_reset_mpll_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_mpll_clock = sw_reset_mpll_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_nco_clock_set(unsigned int sw_reset_nco_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_nco_clock = sw_reset_nco_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_fd_clock_set(unsigned int sw_reset_fd_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_fd_clock = sw_reset_fd_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_mod_and_mpll_clock_set(unsigned int sw_reset_mod_and_mpll_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_mod_and_mpll_clock = sw_reset_mod_and_mpll_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_mod_and_nco_clock_set(unsigned int sw_reset_mod_and_nco_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_mod_and_nco_clock = sw_reset_mod_and_nco_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_mod_and_fd_clock_set(unsigned int sw_reset_mod_and_fd_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_mod_and_fd_clock = sw_reset_mod_and_fd_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_hsfifo_clock_set(unsigned int sw_reset_hsfifo_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_hsfifo_clock = sw_reset_hsfifo_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_txfifo_clock_set(unsigned int sw_reset_txfifo_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_txfifo_clock = sw_reset_txfifo_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_data_clock_set(unsigned int sw_reset_data_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_data_clock = sw_reset_data_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_hs_clock_set(unsigned int sw_reset_hs_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_hs_clock = sw_reset_hs_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_pllref_clock_set(unsigned int sw_reset_pllref_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_pllref_clock = sw_reset_pllref_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_sw_reset_dac_clock_set(unsigned int sw_reset_dac_clock)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.sw_reset_dac_clock = sw_reset_dac_clock;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_swreset_up_sample_fifo_clock_swrst_set(unsigned int sample_fifo_clock_swrst)
{
    hi_u32 *reg_addr = NULL;
    swreset tmp;

    reg_addr = (hi_u32 *)&(g_hi3559a_dphy_reg_all_reg->reg_swreset.u32);
    tmp.u32 = hdmi21_txreg_read(reg_addr);
    tmp.bits.up_sample_fifo_clock_swrst = sample_fifo_clock_swrst;
    hdmi21_txreg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

