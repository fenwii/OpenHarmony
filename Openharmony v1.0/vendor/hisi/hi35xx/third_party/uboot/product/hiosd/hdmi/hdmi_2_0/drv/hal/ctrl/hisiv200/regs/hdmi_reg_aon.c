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

volatile tx_aon_reg_type *g_tx_aon_all_reg = NULL;

int hdmi_tx_aon_reg_type_init(void)
{
    g_tx_aon_all_reg = (volatile tx_aon_reg_type *)(HDMI_TX_BASE_ADDR + (HDMI_TX_BASE_ADDR_AON));
    return HI_SUCCESS;
}

hi_void hdmi_tx_aon_reg_type_deinit(void)
{
    if (g_tx_aon_all_reg != NULL) {
        g_tx_aon_all_reg = NULL;
    }
    return;
}

int hdmi_dcc_man_en_set(unsigned int dcc_man_en)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->mst_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.dcc_man_en = dcc_man_en;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ddc_sda_oen_set(unsigned int dcc_sda_oen)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->man_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.ddc_sda_oen = dcc_sda_oen;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ddc_scl_oen_set(unsigned int dcc_scl_oen)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->man_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    tmp.bits.ddc_scl_oen = dcc_scl_oen;
    hdmi_tx_reg_write(reg_addr, tmp.u32);

    return HI_SUCCESS;
}

int hdmi_ddc_i2c_no_ack_get(void)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_state tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->mst_state.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.ddc_i2c_no_ack;
}

int hdmi_ddc_i2c_bus_low_get(void)
{
    hi_u32 *reg_addr = NULL;
    ddc_mst_state tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->mst_state.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.ddc_i2c_bus_low;
}

int hdmi_ddc_sda_st_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->man_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.ddc_sda_st;
}

int hdmi_ddc_scl_st_get(hi_void)
{
    hi_u32 *reg_addr = NULL;
    ddc_man_ctrl tmp;

    reg_addr = (hi_u32 *)&(g_tx_aon_all_reg->man_ctrl.u32);
    tmp.u32 = hdmi_tx_reg_read(reg_addr);
    return tmp.bits.ddc_scl_st;
}

