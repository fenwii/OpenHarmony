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
#include "hdmi_reg_aon.h"
#include "hdmi_product_define.h"

volatile tx_aon_regs *g_tx_aon_all_reg = NULL;

int hdmi_tx_aon_regs_init(void)
{
    g_tx_aon_all_reg = (volatile tx_aon_regs *)(HDMI_TX_BASE_ADDR + (HDMI_TX_BASE_ADDR_AON));
    return HI_SUCCESS;
}

hi_void hdmi_tx_aon_regs_deinit(void)
{
    if (g_tx_aon_all_reg != HI_NULL) {
        g_tx_aon_all_reg = HI_NULL;
    }
    return;
}

hi_void hdmi_dcc_man_en_set(unsigned int dcc_man_en)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_ctrl mst_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_mst_ctrl.u32);
    mst_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    mst_ctrl.bits.dcc_man_en = dcc_man_en;
    hdmi_tx_reg_write(reg_addr, mst_ctrl.u32);

    return;
}

hi_void hdmi_ddc_sda_oen_set(unsigned int ddc_sda_oen)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl man_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_man_ctrl.u32);
    man_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    man_ctrl.bits.ddc_sda_oen = ddc_sda_oen;
    hdmi_tx_reg_write(reg_addr, man_ctrl.u32);

    return;
}

hi_void hdmi_ddc_scl_oen_set(unsigned int ddc_scl_oen)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl man_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_man_ctrl.u32);
    man_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    man_ctrl.bits.ddc_scl_oen = ddc_scl_oen;
    hdmi_tx_reg_write(reg_addr, man_ctrl.u32);

    return;
}

int hdmi_ddc_i2c_no_ack_get(void)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_state mst_state;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_mst_state.u32);
    mst_state.u32 = hdmi_tx_reg_read(reg_addr);
    return mst_state.bits.ddc_i2c_no_ack;
}

int hdmi_ddc_i2c_bus_low_get(void)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_state mst_state;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_mst_state.u32);
    mst_state.u32 = hdmi_tx_reg_read(reg_addr);
    return mst_state.bits.ddc_i2c_bus_low;
}

int hdmi_ddc_sda_st_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl man_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_man_ctrl.u32);
    man_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    return man_ctrl.bits.ddc_sda_st;
}

int hdmi_ddc_scl_st_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl man_ctrl;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->reg_ddc_man_ctrl.u32);
    man_ctrl.u32 = hdmi_tx_reg_read(reg_addr);
    return man_ctrl.bits.ddc_scl_st;
}

