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

#include "hal_vo_dev_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */
#if VO_DESC("UBOOT_VO")

#if VO_DESC("dev&intf")

hi_void hal_sys_set_rd_bus_id(hi_u32 mode)
{
    return;
}

hi_void hal_disp_set_intf_enable(hi_vo_dev dev, hi_bool intf)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_ctrl dhd0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_ctrl.u32));
    dhd0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_ctrl.bits.intf_en = intf;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_ctrl.u32);
}

hi_void hal_disp_get_intf_enable(hi_vo_dev dev, hi_bool *intf_en)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_ctrl dhd0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_ctrl.u32));
    dhd0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    *intf_en = dhd0_ctrl.bits.intf_en;
}

hi_void hal_disp_set_hdmi_mode(hi_vo_dev dev, hi_u32 color_space)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_ctrl dhd0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_ctrl.u32));
    dhd0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_ctrl.bits.hdmi_mode = color_space;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_ctrl.u32);
}

hi_void hal_disp_set_dev_multi_chn_en(hi_vo_dev dev, hal_multichn_en multi_chn_en)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_pwr dhd0_pwr;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_pwr.u32));
    dhd0_pwr.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_pwr.bits.multichn_en = multi_chn_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_pwr.u32);
}

hi_void hal_disp_set_vtthd_mode(hi_vo_dev dev, hi_u32 field_mode)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_vtthd dhd0_vtthd;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_vtthd.u32));
    dhd0_vtthd.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_vtthd.bits.thd1_mode = field_mode;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_vtthd.u32);
}

hi_void hal_disp_set_vtthd(hi_vo_dev dev, hi_u32 vtthd, hi_u32 vtthd2)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_vtthd dhd0_vtthd;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    /* for vtmgthd1 and vtmgthd2 */
    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_vtthd.u32));
    dhd0_vtthd.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_vtthd.bits.vtmgthd1 = vtthd;
    dhd0_vtthd.bits.vtmgthd2 = vtthd2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_vtthd.u32);
}

hi_void hal_disp_clear_int_status(hi_u32 int_msk)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();

    /* read interrupt status */
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->vomskintsta.u32), int_msk);
}

hi_void hal_intf_bt_set_dfir_en(hi_u32 dfir_en)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_intf_bt_ctrl intf_bt_ctrl;

    intf_bt_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->intf_bt_ctrl.u32));
    intf_bt_ctrl.bits.dfir_en = dfir_en;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->intf_bt_ctrl.u32), intf_bt_ctrl.u32);
}

hi_void hal_intf_bt_set_data_width(hi_u32 data_width)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_intf_bt_ctrl intf_bt_ctrl;

    intf_bt_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->intf_bt_ctrl.u32));
    intf_bt_ctrl.bits.data_width = data_width;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->intf_bt_ctrl.u32), intf_bt_ctrl.u32);
}

hi_void hal_disp_set_reg_up(hi_vo_dev dev)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_ctrl dhd0_ctrl;
    volatile hi_ulong addr_reg;

    vo_hal_check_phy_dev_return(dev);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_ctrl.u32));
    dhd0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_ctrl.bits.regup = 0x1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_ctrl.u32);
}

hi_u32 hal_disp_get_reg_up(hi_vo_dev dev)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    hi_u32 data;
    volatile reg_dhd0_ctrl dhd0_ctrl;
    volatile hi_ulong addr_reg;

    if (vo_hal_is_phy_dev(dev) != HI_TRUE) {
        return 0;
    }

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_ctrl.u32));
    dhd0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    data = dhd0_ctrl.bits.regup;
    return data & 0x1;
}

#endif

#if VO_DESC("dev intf")

static hi_bool vo_hal_is_valid_sd_dev(hi_vo_dev dev)
{
    if (dev == VO_DEV_DSD0) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static hi_void vo_hal_intf_set_mux_sel_sd(hi_vo_dev dev, hi_vo_intf_type intf)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_mux vo_mux;

    vo_mux.u32 = vo_reg->vo_mux.u32;
    if (intf == HI_VO_INTF_CVBS) {
        vo_mux.bits.sddate_sel = 2;   /* 2: DSD SDATE */
    }
    vo_reg->vo_mux.u32 = vo_mux.u32;
}

hi_void vo_hal_intf_set_mux_sel(hi_vo_dev dev, hi_vo_intf_type intf)
{
    vo_hal_check_phy_dev_return(dev);

    if (vo_hal_is_valid_sd_dev(dev)) {
        vo_hal_intf_set_mux_sel_sd(dev, intf);
        return;
    }

    vo_hal_intf_set_mux_sel_hd(dev, intf);
}

hi_void vo_hal_intf_set_bt_sync_inv(hal_disp_syncinv *inv)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_intf_bt_sync_inv intf_bt_sync_inv;

    intf_bt_sync_inv.u32 = vo_reg->intf_bt_sync_inv.u32;
    intf_bt_sync_inv.bits.dv_inv = inv->dv_inv;
    intf_bt_sync_inv.bits.hs_inv = inv->hs_inv;
    intf_bt_sync_inv.bits.vs_inv = inv->vs_inv;
    intf_bt_sync_inv.bits.f_inv = inv->f_inv;
    vo_reg->intf_bt_sync_inv.u32 = intf_bt_sync_inv.u32;
}

hi_void vo_hal_intf_set_cvbs_sync_inv(hal_disp_syncinv *inv)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_intf_date_sync_inv intf_date_sync_inv;

    intf_date_sync_inv.u32 = vo_reg->intf_date_sync_inv.u32;
    intf_date_sync_inv.bits.dv_inv = inv->dv_inv;
    intf_date_sync_inv.bits.hs_inv = inv->hs_inv;
    intf_date_sync_inv.bits.vs_inv = inv->vs_inv;
    intf_date_sync_inv.bits.f_inv = inv->f_inv;
    vo_reg->intf_date_sync_inv.u32 = intf_date_sync_inv.u32;
}

hi_void vo_hal_intf_set_vga_sync_inv(hal_disp_syncinv *inv)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_intf_vga_sync_inv intf_vga_sync_inv;

    intf_vga_sync_inv.u32 = vo_reg->intf_vga_sync_inv.u32;
    intf_vga_sync_inv.bits.dv_inv = inv->dv_inv;
    intf_vga_sync_inv.bits.hs_inv = inv->hs_inv;
    intf_vga_sync_inv.bits.vs_inv = inv->vs_inv;
    intf_vga_sync_inv.bits.f_inv = inv->f_inv;
    vo_reg->intf_vga_sync_inv.u32 = intf_vga_sync_inv.u32;
}

hi_void vo_hal_intf_set_hdmi_sync_inv(hal_disp_syncinv *inv)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_intf_hdmi_sync_inv intf_hdmi_sync_inv;

    intf_hdmi_sync_inv.u32 = vo_reg->intf_hdmi_sync_inv.u32;
    intf_hdmi_sync_inv.bits.dv_inv = inv->dv_inv;
    intf_hdmi_sync_inv.bits.hs_inv = inv->hs_inv;
    intf_hdmi_sync_inv.bits.vs_inv = inv->vs_inv;
    intf_hdmi_sync_inv.bits.f_inv = inv->f_inv;
    vo_reg->intf_hdmi_sync_inv.u32 = intf_hdmi_sync_inv.u32;
}

hi_void vo_hal_intf_set_hdmi_csc_dc_coef(vdp_csc_dc_coef *csc_dc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_hdmi_csc_idc hdmi_csc_idc;
    volatile reg_hdmi_csc_odc hdmi_csc_odc;
    volatile reg_hdmi_csc_iodc hdmi_csc_iodc;

    hdmi_csc_idc.u32 = vo_reg->hdmi_csc_idc.u32;
    hdmi_csc_odc.u32 = vo_reg->hdmi_csc_odc.u32;
    hdmi_csc_iodc.u32 = vo_reg->hdmi_csc_iodc.u32;

    hdmi_csc_idc.bits.cscidc0 = csc_dc_coef->csc_in_dc2;
    hdmi_csc_idc.bits.cscidc1 = csc_dc_coef->csc_in_dc1;
    hdmi_csc_iodc.bits.cscidc2 = csc_dc_coef->csc_in_dc0;

    hdmi_csc_odc.bits.cscodc0 = csc_dc_coef->csc_out_dc2;

    hdmi_csc_odc.bits.cscodc1 = csc_dc_coef->csc_out_dc1;
    hdmi_csc_iodc.bits.cscodc2 = csc_dc_coef->csc_out_dc0;

    vo_reg->hdmi_csc_idc.u32 = hdmi_csc_idc.u32;
    vo_reg->hdmi_csc_odc.u32 = hdmi_csc_odc.u32;
    vo_reg->hdmi_csc_iodc.u32 = hdmi_csc_iodc.u32;
}

hi_void vo_hal_intf_set_vga_csc_dc_coef(vdp_csc_dc_coef *csc_dc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_csc_idc vga_csc_idc;
    volatile reg_vga_csc_odc vga_csc_odc;
    volatile reg_vga_csc_iodc vga_csc_iodc;

    vga_csc_idc.u32 = vo_reg->vga_csc_idc.u32;
    vga_csc_odc.u32 = vo_reg->vga_csc_odc.u32;
    vga_csc_iodc.u32 = vo_reg->vga_csc_iodc.u32;

    vga_csc_idc.bits.cscidc0 = csc_dc_coef->csc_in_dc2;
    vga_csc_idc.bits.cscidc1 = csc_dc_coef->csc_in_dc1;
    vga_csc_iodc.bits.cscidc2 = csc_dc_coef->csc_in_dc0;
    vga_csc_odc.bits.cscodc0 = csc_dc_coef->csc_out_dc2;
    vga_csc_odc.bits.cscodc1 = csc_dc_coef->csc_out_dc1;
    vga_csc_iodc.bits.cscodc2 = csc_dc_coef->csc_out_dc0;

    vo_reg->vga_csc_idc.u32 = vga_csc_idc.u32;
    vo_reg->vga_csc_odc.u32 = vga_csc_odc.u32;
    vo_reg->vga_csc_iodc.u32 = vga_csc_iodc.u32;
}

hi_void vo_hal_intf_set_hdmi_csc_coef(vdp_csc_coef *csc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_hdmi_csc_p0 hdmi_csc_p0;
    volatile reg_hdmi_csc_p1 hdmi_csc_p1;
    volatile reg_hdmi_csc_p2 hdmi_csc_p2;
    volatile reg_hdmi_csc_p3 hdmi_csc_p3;
    volatile reg_hdmi_csc_p4 hdmi_csc_p4;

    hdmi_csc_p0.u32 = vo_reg->hdmi_csc_p0.u32;
    hdmi_csc_p1.u32 = vo_reg->hdmi_csc_p1.u32;
    hdmi_csc_p2.u32 = vo_reg->hdmi_csc_p2.u32;
    hdmi_csc_p3.u32 = vo_reg->hdmi_csc_p3.u32;
    hdmi_csc_p4.u32 = vo_reg->hdmi_csc_p4.u32;

    hdmi_csc_p0.bits.cscp00 = csc_coef->csc_coef00;
    hdmi_csc_p0.bits.cscp01 = csc_coef->csc_coef01;
    hdmi_csc_p1.bits.cscp02 = csc_coef->csc_coef02;
    hdmi_csc_p1.bits.cscp10 = csc_coef->csc_coef10;
    hdmi_csc_p2.bits.cscp11 = csc_coef->csc_coef11;
    hdmi_csc_p2.bits.cscp12 = csc_coef->csc_coef12;
    hdmi_csc_p3.bits.cscp20 = csc_coef->csc_coef20;
    hdmi_csc_p3.bits.cscp21 = csc_coef->csc_coef21;
    hdmi_csc_p4.bits.cscp22 = csc_coef->csc_coef22;

    vo_reg->hdmi_csc_p0.u32 = hdmi_csc_p0.u32;
    vo_reg->hdmi_csc_p1.u32 = hdmi_csc_p1.u32;
    vo_reg->hdmi_csc_p2.u32 = hdmi_csc_p2.u32;
    vo_reg->hdmi_csc_p3.u32 = hdmi_csc_p3.u32;
    vo_reg->hdmi_csc_p4.u32 = hdmi_csc_p4.u32;
}

hi_void vo_hal_intf_set_vga_csc_coef(vdp_csc_coef *csc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_csc_p0 vga_csc_p0;
    volatile reg_vga_csc_p1 vga_csc_p1;
    volatile reg_vga_csc_p2 vga_csc_p2;
    volatile reg_vga_csc_p3 vga_csc_p3;
    volatile reg_vga_csc_p4 vga_csc_p4;

    vga_csc_p0.u32 = vo_reg->vga_csc_p0.u32;
    vga_csc_p1.u32 = vo_reg->vga_csc_p1.u32;
    vga_csc_p2.u32 = vo_reg->vga_csc_p2.u32;
    vga_csc_p3.u32 = vo_reg->vga_csc_p3.u32;
    vga_csc_p4.u32 = vo_reg->vga_csc_p4.u32;

    vga_csc_p0.bits.cscp00 = csc_coef->csc_coef00;
    vga_csc_p0.bits.cscp01 = csc_coef->csc_coef01;
    vga_csc_p1.bits.cscp02 = csc_coef->csc_coef02;
    vga_csc_p1.bits.cscp10 = csc_coef->csc_coef10;
    vga_csc_p2.bits.cscp11 = csc_coef->csc_coef11;
    vga_csc_p2.bits.cscp12 = csc_coef->csc_coef12;
    vga_csc_p3.bits.cscp20 = csc_coef->csc_coef20;
    vga_csc_p3.bits.cscp21 = csc_coef->csc_coef21;
    vga_csc_p4.bits.cscp22 = csc_coef->csc_coef22;

    vo_reg->vga_csc_p0.u32 = vga_csc_p0.u32;
    vo_reg->vga_csc_p1.u32 = vga_csc_p1.u32;
    vo_reg->vga_csc_p2.u32 = vga_csc_p2.u32;
    vo_reg->vga_csc_p3.u32 = vga_csc_p3.u32;
    vo_reg->vga_csc_p4.u32 = vga_csc_p4.u32;
}

hi_void vo_hal_intf_set_csc_cfg(hi_vo_intf_type intf, csc_coef *coef)
{
    vo_hal_intf_set_csc_dc_coef(intf, (vdp_csc_dc_coef *)(&coef->csc_in_dc0));
    vo_hal_intf_set_csc_coef(intf, (vdp_csc_coef *)(&coef->csc_coef00));
}

hi_void vo_hal_intf_set_dac_sel(hi_vo_intf_type intf_type)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vomux_dac vomux_dac;

    vomux_dac.u32 = vo_reg->vomux_dac.u32;
    if (intf_type == HI_VO_INTF_VGA) {
        vomux_dac.bits.dac2_sel = 9;   /* 9: DAC2 VGA B */
        vomux_dac.bits.dac1_sel = 8;   /* 8: DAC2 VGA G */
        vomux_dac.bits.dac0_sel = 7;   /* 7: DAC2 VGA R */
    } else if (intf_type == HI_VO_INTF_CVBS) {
        vomux_dac.bits.dac3_sel = 0;
    }
    vo_reg->vomux_dac.u32 = vomux_dac.u32;
}

hi_void vo_hal_intf_set_vga_and_cvbs_dac_enable(hi_bool enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_dac_ctrl vo_dac_ctrl;

    vo_dac_ctrl.u32 = vo_reg->vo_dac_ctrl.u32;
    vo_dac_ctrl.bits.envbg = enable;
    vo_reg->vo_dac_ctrl.u32 = vo_dac_ctrl.u32;
}

hi_void vo_hal_intf_set_cvbs_dac_cfg(hi_void)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_dac_ctrl vo_dac_ctrl;
    volatile reg_vo_dac_otp vo_dac_otp;

    vo_dac_ctrl.u32 = vo_reg->vo_dac_ctrl.u32;
    vo_dac_otp.u32 = vo_reg->vo_dac_otp.u32;
    vo_dac_ctrl.bits.dac_reg_rev = 0xF;       /* 0xF: CVBS hardware test need it */
    vo_dac_otp.bits.dac_otp_reg = 0x7900;   /* 0x7900: CVBS hardware test need it */
    vo_reg->vo_dac_ctrl.u32 = vo_dac_ctrl.u32;
    vo_reg->vo_dac_otp.u32 = vo_dac_otp.u32;
}

hi_void vo_hal_intf_set_dac_chn_enable(hi_vo_intf_type intf_type, hi_bool enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_dac0_ctrl vo_dac0_ctrl;
    volatile reg_vo_dac1_ctrl vo_dac1_ctrl;
    volatile reg_vo_dac2_ctrl vo_dac2_ctrl;
    volatile reg_vo_dac3_ctrl vo_dac3_ctrl;

    if (intf_type == HI_VO_INTF_VGA) {
        vo_dac0_ctrl.u32 = vo_reg->vo_dac0_ctrl.u32;
        vo_dac1_ctrl.u32 = vo_reg->vo_dac1_ctrl.u32;
        vo_dac2_ctrl.u32 = vo_reg->vo_dac2_ctrl.u32;
        vo_dac0_ctrl.bits.dac_en = enable;
        vo_dac1_ctrl.bits.dac_en = enable;
        vo_dac2_ctrl.bits.dac_en = enable;
        vo_reg->vo_dac0_ctrl.u32 = vo_dac0_ctrl.u32;
        vo_reg->vo_dac1_ctrl.u32 = vo_dac1_ctrl.u32;
        vo_reg->vo_dac2_ctrl.u32 = vo_dac2_ctrl.u32;
    } else if (intf_type == HI_VO_INTF_CVBS) {
        vo_dac3_ctrl.u32 = vo_reg->vo_dac3_ctrl.u32;
        vo_dac3_ctrl.bits.dac_en = enable;
        vo_reg->vo_dac3_ctrl.u32 = vo_dac3_ctrl.u32;
    }
}

hi_void vo_hal_intf_set_dac_gc(hi_vo_intf_type intf_type, hi_u32 dac_gc)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_dac0_ctrl vo_dac0_ctrl;
    volatile reg_vo_dac1_ctrl vo_dac1_ctrl;
    volatile reg_vo_dac2_ctrl vo_dac2_ctrl;
    volatile reg_vo_dac3_ctrl vo_dac3_ctrl;

    if (intf_type == HI_VO_INTF_VGA) {
        vo_dac0_ctrl.u32 = vo_reg->vo_dac0_ctrl.u32;
        vo_dac1_ctrl.u32 = vo_reg->vo_dac1_ctrl.u32;
        vo_dac2_ctrl.u32 = vo_reg->vo_dac2_ctrl.u32;
        vo_dac0_ctrl.bits.dacgc = dac_gc;
        vo_dac1_ctrl.bits.dacgc = dac_gc;
        vo_dac2_ctrl.bits.dacgc = dac_gc;
        vo_reg->vo_dac0_ctrl.u32 = vo_dac0_ctrl.u32;
        vo_reg->vo_dac1_ctrl.u32 = vo_dac1_ctrl.u32;
        vo_reg->vo_dac2_ctrl.u32 = vo_dac2_ctrl.u32;
    } else if (intf_type == HI_VO_INTF_CVBS) {
        vo_dac3_ctrl.u32 = vo_reg->vo_dac3_ctrl.u32;
        vo_dac3_ctrl.bits.dacgc = dac_gc;
        vo_reg->vo_dac3_ctrl.u32 = vo_dac3_ctrl.u32;
    }
}

hi_void vo_hal_intf_set_dac_cablectr(hi_vo_intf_type intf_type, hi_u32 cablectr)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_dac0_ctrl vo_dac0_ctrl;
    volatile reg_vo_dac1_ctrl vo_dac1_ctrl;
    volatile reg_vo_dac2_ctrl vo_dac2_ctrl;
    volatile reg_vo_dac3_ctrl vo_dac3_ctrl;

    if (intf_type == HI_VO_INTF_VGA) {
        vo_dac0_ctrl.u32 = vo_reg->vo_dac0_ctrl.u32;
        vo_dac1_ctrl.u32 = vo_reg->vo_dac1_ctrl.u32;
        vo_dac2_ctrl.u32 = vo_reg->vo_dac2_ctrl.u32;
        vo_dac0_ctrl.bits.cablectr = cablectr;
        vo_dac1_ctrl.bits.cablectr = cablectr;
        vo_dac2_ctrl.bits.cablectr = cablectr;
        vo_reg->vo_dac0_ctrl.u32 = vo_dac0_ctrl.u32;
        vo_reg->vo_dac1_ctrl.u32 = vo_dac1_ctrl.u32;
        vo_reg->vo_dac2_ctrl.u32 = vo_dac2_ctrl.u32;
    } else if (intf_type == HI_VO_INTF_CVBS) {
        vo_dac3_ctrl.u32 = vo_reg->vo_dac3_ctrl.u32;
        vo_dac3_ctrl.bits.cablectr = cablectr;
        vo_reg->vo_dac3_ctrl.u32 = vo_dac3_ctrl.u32;
    }
}

static hi_void vo_hal_intf_set_vga_hsp_coef(hsp_coef *coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_hspcfg14 vga_hspcfg14;
    volatile reg_vga_hspcfg15 vga_hspcfg15;

    vga_hspcfg14.u32 = vo_reg->vga_hspcfg14.u32;
    vga_hspcfg15.u32 = vo_reg->vga_hspcfg15.u32;

    vga_hspcfg14.bits.hsp_cdti_gain = coef->vga_hsp_cdti_gain;
    vga_hspcfg14.bits.hsp_ldti_gain = coef->vga_hsp_ldti_gain;
    vga_hspcfg14.bits.hsp_lti_ratio = coef->vga_hsp_lti_ratio;
    vga_hspcfg14.bits.hsp_hf_shootdiv = coef->vga_hsp_hf_shootdiv;
    vga_hspcfg15.bits.hsp_glb_underth = coef->vga_hsp_glb_underth;
    vga_hspcfg15.bits.hsp_glb_overth = coef->vga_hsp_glb_overth;
    vga_hspcfg15.bits.hsp_peak_ratio = coef->vga_hsp_peak_ratio;

    vo_reg->vga_hspcfg14.u32 = vga_hspcfg14.u32;
    vo_reg->vga_hspcfg15.u32 = vga_hspcfg15.u32;
}

static hi_void vo_hal_intf_set_vga_hsp_h0_coef(hsp_hf_coef *coef0)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_hspcfg0 vga_hspcfg0;
    volatile reg_vga_hspcfg1 vga_hspcfg1;
    volatile reg_vga_hspcfg5 vga_hspcfg5;
    volatile reg_vga_hspcfg6 vga_hspcfg6;

    vga_hspcfg0.u32 = vo_reg->vga_hspcfg0.u32;
    vga_hspcfg1.u32 = vo_reg->vga_hspcfg1.u32;
    vga_hspcfg5.u32 = vo_reg->vga_hspcfg5.u32;
    vga_hspcfg6.u32 = vo_reg->vga_hspcfg6.u32;

    vga_hspcfg0.bits.hsp_hf0_tmp0 = coef0->vga_hsp_tmp0;
    vga_hspcfg0.bits.hsp_hf0_tmp1 = coef0->vga_hsp_tmp1;
    vga_hspcfg0.bits.hsp_hf0_tmp2 = coef0->vga_hsp_tmp2;
    vga_hspcfg0.bits.hsp_hf0_tmp3 = coef0->vga_hsp_tmp3;
    vga_hspcfg1.bits.hsp_hf0_coring = coef0->vga_hsp_coring;
    vga_hspcfg5.bits.hsp_hf0_gainpos = coef0->vga_hsp_gainpos;
    vga_hspcfg5.bits.hsp_hf0_gainneg = coef0->vga_hsp_gainneg;
    vga_hspcfg6.bits.hsp_hf0_overth = coef0->vga_hsp_overth;
    vga_hspcfg6.bits.hsp_hf0_underth = coef0->vga_hsp_underth;
    vga_hspcfg6.bits.hsp_hf0_mixratio = coef0->vga_hsp_mixratio;
    vga_hspcfg6.bits.hsp_hf0_winsize = coef0->vga_hsp_winsize;
    vga_hspcfg6.bits.hsp_hf0_adpshoot_en = coef0->vga_hsp_adpshooten;

    vo_reg->vga_hspcfg0.u32 = vga_hspcfg0.u32;
    vo_reg->vga_hspcfg1.u32 = vga_hspcfg1.u32;
    vo_reg->vga_hspcfg5.u32 = vga_hspcfg5.u32;
    vo_reg->vga_hspcfg6.u32 = vga_hspcfg6.u32;
}

static hi_void vo_hal_intf_set_vga_hsp_h1_coef(hsp_hf_coef *coef1)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_hspcfg7 vga_hspcfg7;
    volatile reg_vga_hspcfg8 vga_hspcfg8;
    volatile reg_vga_hspcfg12 vga_hspcfg12;
    volatile reg_vga_hspcfg13 vga_hspcfg13;

    vga_hspcfg7.u32 = vo_reg->vga_hspcfg7.u32;
    vga_hspcfg8.u32 = vo_reg->vga_hspcfg8.u32;
    vga_hspcfg12.u32 = vo_reg->vga_hspcfg12.u32;
    vga_hspcfg13.u32 = vo_reg->vga_hspcfg13.u32;

    vga_hspcfg7.bits.hsp_hf1_tmp0 = coef1->vga_hsp_tmp0;
    vga_hspcfg7.bits.hsp_hf1_tmp1 = coef1->vga_hsp_tmp1;
    vga_hspcfg7.bits.hsp_hf1_tmp2 = coef1->vga_hsp_tmp2;
    vga_hspcfg7.bits.hsp_hf1_tmp3 = coef1->vga_hsp_tmp3;
    vga_hspcfg8.bits.hsp_hf1_coring = coef1->vga_hsp_coring;
    vga_hspcfg12.bits.hsp_hf1_gainpos = coef1->vga_hsp_gainpos;
    vga_hspcfg12.bits.hsp_hf1_gainneg = coef1->vga_hsp_gainneg;
    vga_hspcfg13.bits.hsp_hf1_overth = coef1->vga_hsp_overth;
    vga_hspcfg13.bits.hsp_hf1_underth = coef1->vga_hsp_underth;
    vga_hspcfg13.bits.hsp_hf1_mixratio = coef1->vga_hsp_mixratio;
    vga_hspcfg13.bits.hsp_hf1_winsize = coef1->vga_hsp_winsize;
    vga_hspcfg13.bits.hsp_hf1_adpshoot_en = coef1->vga_hsp_adpshooten;

    vo_reg->vga_hspcfg7.u32 = vga_hspcfg7.u32;
    vo_reg->vga_hspcfg8.u32 = vga_hspcfg8.u32;
    vo_reg->vga_hspcfg12.u32 = vga_hspcfg12.u32;
    vo_reg->vga_hspcfg13.u32 = vga_hspcfg13.u32;
}

static hi_void vo_hal_intf_set_vga_hsp_h_enable(hi_bool enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_hspcfg14 vga_hspcfg14;

    vga_hspcfg14.u32 = vo_reg->vga_hspcfg14.u32;
    vga_hspcfg14.bits.hsp_h0_en = enable;
    vga_hspcfg14.bits.hsp_h1_en = enable;
    vga_hspcfg14.bits.hsp_ltih_en = enable;
    vga_hspcfg14.bits.hsp_ctih_en = enable;
    vo_reg->vga_hspcfg14.u32 = vga_hspcfg14.u32;
}

static hi_void vo_hal_intf_set_vga_hsp_enable(hi_bool enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vga_hspcfg1 vga_hspcfg1;

    vga_hspcfg1.u32 = vo_reg->vga_hspcfg1.u32;
    vga_hspcfg1.bits.hsp_en = enable;
    vo_reg->vga_hspcfg1.u32 = vga_hspcfg1.u32;
}

static hi_void vo_hal_intf_set_vga_hsp_cfg_coef(hi_u32 strength)
{
    const hi_u32 pre = 8;
    hsp_coef coef = {0};

    coef.vga_hsp_peak_ratio = 128; /* 128 */
    coef.vga_hsp_glb_overth = 50;  /* 50 */
    coef.vga_hsp_hf_shootdiv = 4;  /* 4 */
    coef.vga_hsp_lti_ratio = 128;  /* 128 */
    coef.vga_hsp_ldti_gain = (192 * strength) >> pre;  /* 192 */
    coef.vga_hsp_cdti_gain = (192 * strength) >> pre;  /* 192 */
    coef.vga_hsp_glb_underth = 255;  /* 255 */

    vo_hal_intf_set_vga_hsp_coef(&coef);
}

static hi_void vo_hal_intf_set_vga_hsp_cfg_coef0(hi_u32 strength)
{
    const hi_u32 pre = 8;
    hsp_hf_coef coef0 = {0};

    coef0.vga_hsp_tmp0 = 0;
    coef0.vga_hsp_tmp1 = -84; /* -84: coef 1 */
    coef0.vga_hsp_tmp2 = 0;
    coef0.vga_hsp_tmp3 = 20;   /* 20: coef 3 */
    coef0.vga_hsp_coring = 2;  /* 2: coef */
    coef0.vga_hsp_gainpos = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((154 * strength) >> pre) /* 154:coef */
        : (2 * (strength - VO_VGA_SHARPEN_STRENGTH_DEF) + 77); /* 2:coef 77:coef  */
    coef0.vga_hsp_gainneg = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((154 * strength) >> pre) /* 154:coef */
        : (2 * (strength - VO_VGA_SHARPEN_STRENGTH_DEF) + 77); /* 2:coef 77:coef  */
    coef0.vga_hsp_adpshooten = 1; /* 1: enable */
    coef0.vga_hsp_winsize    = 2; /* 2: window size */
    coef0.vga_hsp_mixratio   = 64; /* 64: 0.5 * 128 */
    coef0.vga_hsp_underth    = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((36 * strength) >> pre) /* 36:coef */
        : ((72 * ((strength - VO_VGA_SHARPEN_STRENGTH_DEF) >> pre)) +  18);  /* 72:coef 18:coef */
    coef0.vga_hsp_overth     = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((24 * strength) >> pre) /* 24:coef */
        : ((48 * ((strength - VO_VGA_SHARPEN_STRENGTH_DEF) >> pre)) +  12);  /* 48:coef 12:coef */

    vo_hal_intf_set_vga_hsp_h0_coef(&coef0);
}

static hi_void vo_hal_intf_set_vga_hsp_cfg_coef1(hi_u32 strength)
{
    const hi_u32 pre = 8;
    hsp_hf_coef coef1 = {0};

    coef1.vga_hsp_tmp0 = 22;    /* 22: coef 0 */
    coef1.vga_hsp_tmp1 = -62;   /* -62: coef 1 */
    coef1.vga_hsp_tmp2 = -25;   /* -25: coef 2 */
    coef1.vga_hsp_tmp3 = 1;     /* 1: coef 3 */
    coef1.vga_hsp_coring = 2; /* 2: coef  */
    coef1.vga_hsp_gainpos = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((214 * strength) >> pre) /* 214:coef  */
        : ((712 * ((strength - VO_VGA_SHARPEN_STRENGTH_DEF) >> pre)) + 107); /* 712:coef 107:coef  */
    coef1.vga_hsp_gainneg = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((214 * strength) >> pre) /* 214:coef */
        : ((712 * ((strength - VO_VGA_SHARPEN_STRENGTH_DEF) >> pre)) + 107); /* 712:coef 107:coef  */
    coef1.vga_hsp_adpshooten = 1;  /* 1: coef  */
    coef1.vga_hsp_winsize    = 3;  /* 3: window size */
    coef1.vga_hsp_mixratio   = 102; /* 102:: 0.8 * 128 */
    coef1.vga_hsp_underth    = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((36 * strength) >> pre) /* 36:coef  */
        : ((72 * ((strength - VO_VGA_SHARPEN_STRENGTH_DEF) >> pre)) +  18);  /* 72:coef 18:coef  */
    coef1.vga_hsp_overth     = (strength <= VO_VGA_SHARPEN_STRENGTH_DEF) ? ((30 * strength) >> pre) /* 30:coef */
        : ((60 * ((strength - VO_VGA_SHARPEN_STRENGTH_DEF) >> pre)) +  15);  /* 60:coef 15:coef */

    vo_hal_intf_set_vga_hsp_h1_coef(&coef1);
}

hi_void vo_hal_intf_set_vga_hsp_cfg(hi_bool enable, hi_u32 strength)
{
    vo_hal_intf_set_vga_hsp_cfg_coef(strength);
    vo_hal_intf_set_vga_hsp_cfg_coef0(strength);
    vo_hal_intf_set_vga_hsp_cfg_coef1(strength);
    vo_hal_intf_set_vga_hsp_h_enable(enable);
    vo_hal_intf_set_vga_hsp_enable(enable);
}

static hi_void vo_hal_intf_set_date_coeff(hi_u32 data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    vo_reg->date_coeff0.u32 = data;
}

static hi_void vo_hal_intf_set_date_cgain(hi_u32 data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    vo_reg->date_coeff1.u32 = data;
}

static hi_void vo_hal_intf_set_date_out_ctrl(hi_u32 data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_date_coeff21 date_coeff21;
    volatile reg_date_coeff21 input_data;

    date_coeff21.u32 = vo_reg->date_coeff21.u32;
    input_data.u32 = data;

    date_coeff21.bits.dac0_in_sel = input_data.bits.dac0_in_sel;
    date_coeff21.bits.dac1_in_sel = input_data.bits.dac1_in_sel;
    date_coeff21.bits.dac2_in_sel = input_data.bits.dac2_in_sel;
    date_coeff21.bits.dac3_in_sel = input_data.bits.dac3_in_sel;
    date_coeff21.bits.dac4_in_sel = input_data.bits.dac4_in_sel;
    date_coeff21.bits.dac5_in_sel = input_data.bits.dac5_in_sel;

    vo_reg->date_coeff21.u32 = date_coeff21.u32;
}

static hi_void vo_hal_intf_set_date_delta(hi_u32 data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    vo_reg->date_coeff22.u32 = data;
}

hi_void vo_hal_intf_set_date_cvbs_color_burst(hi_void)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    vo_reg->date_coeff24 = 0x12099; /* 0x12099: color burst start position. */
}

hi_void vo_hal_intf_set_date_cvbs_burst_start(hi_void)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_date_coeff61 date_coeff61;

    date_coeff61.u32 = vo_reg->date_coeff61.u32;
    date_coeff61.bits.burst_start_ovrd = 0x1; /* 0x1: refresh */
    vo_reg->date_coeff61.u32 = date_coeff61.u32;
}

static hi_u32 vo_hal_intf_get_date_user(hi_u32 vact)
{
    if (vact == 288) { /* 288 = 576 / 2 */
        return VO_CVBS_DATE_PAL;
    } else if (vact == 240) { /* 240 = 480 / 2 */
        return VO_CVBS_DATE_NTSC;
    } else {
        vo_err_trace("HI_VO_OUT_USER wrong vact: %d\n", vact);
        return VO_CVBS_DATE_NTSC;
    }
}

hi_u32 vo_hal_intf_get_date(hi_vo_intf_sync intf_sync, hi_u32 vact)
{
    if (intf_sync == HI_VO_OUT_PAL) {
        return VO_CVBS_DATE_PAL;
    } else if (intf_sync == HI_VO_OUT_NTSC) {
        return VO_CVBS_DATE_NTSC;
    }
    return vo_hal_intf_get_date_user(vact);
}

hi_void vo_hal_intf_set_date_cfg(hi_vo_intf_sync intf_sync, hi_u32 date)
{
    vo_hal_intf_set_date_coeff(date);
    vo_hal_intf_set_date_cgain(0x20000000);   /* 0x20000000: data cgain */
    vo_hal_intf_set_date_out_ctrl(0x111111);  /* 0x111111: data out ctrl */
    vo_hal_intf_set_date_delta(0xa4);         /* 0xa4: data delta */
    vo_hal_intf_set_date_cvbs_gain(0x80808383); /* 0x80808383: cvbs gain */

    if (intf_sync == HI_VO_OUT_NTSC) {
        vo_hal_intf_set_date_cvbs_color_burst();
        vo_hal_intf_set_date_cvbs_burst_start();
    }
}

hi_void vo_hal_intf_set_clip_cfg(hi_vo_intf_type intf_type, hi_bool clip, hal_disp_clip *clip_data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_bt_clip0_l bt_clip0_l;
    volatile reg_bt_clip0_h bt_clip0_h;
    volatile reg_date_clip0_l date_clip0_l;
    volatile reg_date_clip0_h date_clip0_h;

    if ((intf_type == HI_VO_INTF_BT1120) || (intf_type == HI_VO_INTF_BT656)) {
        bt_clip0_l.u32 = vo_reg->bt_clip0_l.u32;
        bt_clip0_h.u32 = vo_reg->bt_clip0_h.u32;
        bt_clip0_l.bits.clip_en = clip;
        bt_clip0_l.bits.clip_cl2 = clip_data->clip_low_y;
        bt_clip0_l.bits.clip_cl1 = clip_data->clip_low_cb;
        bt_clip0_l.bits.clip_cl0 = clip_data->clip_low_cr;
        bt_clip0_h.bits.clip_ch2 = clip_data->clip_high_y;
        bt_clip0_h.bits.clip_ch1 = clip_data->clip_high_cb;
        bt_clip0_h.bits.clip_ch0 = clip_data->clip_high_cr;
        vo_reg->bt_clip0_l.u32 = bt_clip0_l.u32;
        vo_reg->bt_clip0_h.u32 = bt_clip0_h.u32;
    } else if (intf_type == HI_VO_INTF_CVBS) {
        date_clip0_l.u32 = vo_reg->date_clip0_l.u32;
        date_clip0_h.u32 = vo_reg->date_clip0_h.u32;
        date_clip0_l.bits.clip_en = clip;
        date_clip0_l.bits.clip_cl2 = clip_data->clip_low_y;
        date_clip0_l.bits.clip_cl1 = clip_data->clip_low_cb;
        date_clip0_l.bits.clip_cl0 = clip_data->clip_low_cr;
        date_clip0_h.bits.clip_ch2 = clip_data->clip_high_y;
        date_clip0_h.bits.clip_ch1 = clip_data->clip_high_cb;
        date_clip0_h.bits.clip_ch0 = clip_data->clip_high_cr;
        vo_reg->date_clip0_l.u32 = date_clip0_l.u32;
        vo_reg->date_clip0_h.u32 = date_clip0_h.u32;
    }
}

static hi_void vo_hal_intf_set_sync_info_hvsync(hi_vo_dev dev,
    hal_disp_syncinfo *sync_info)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_hsync1 dhd0_hsync1;
    volatile reg_dhd0_hsync2 dhd0_hsync2;
    volatile reg_dhd0_vsync1 dhd0_vsync1;
    volatile reg_dhd0_vsync2 dhd0_vsync2;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_hsync1.u32));
    dhd0_hsync1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_hsync1.bits.hact = sync_info->hact - 1;
    dhd0_hsync1.bits.hbb = (sync_info->hbb) - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_hsync1.u32);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_hsync2.u32));
    dhd0_hsync2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_hsync2.bits.hmid = (sync_info->hmid == 0) ? 0 : sync_info->hmid - 1;
    dhd0_hsync2.bits.hfb = (sync_info->hfb) - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_hsync2.u32);

    /* config VHD interface veritical timming */
    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_vsync1.u32));
    dhd0_vsync1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_vsync1.bits.vact = sync_info->vact - 1;
    dhd0_vsync1.bits.vbb = sync_info->vbb - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_vsync1.u32);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_vsync2.u32));
    dhd0_vsync2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_vsync2.bits.vfb = sync_info->vfb - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_vsync2.u32);
}

static hi_void vo_hal_intf_set_sync_info_other(hi_vo_dev dev,
    hal_disp_syncinfo *sync_info)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_dhd0_ctrl dhd0_ctrl;
    volatile reg_dhd0_vplus1 dhd0_vplus1;
    volatile reg_dhd0_vplus2 dhd0_vplus2;
    volatile reg_dhd0_pwr dhd0_pwr;
    volatile hi_ulong addr_reg;

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_ctrl.u32));
    dhd0_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_ctrl.bits.iop = sync_info->iop;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_ctrl.u32);

    /* config VHD interface veritical bottom timming,no use in progressive mode */
    addr_reg = vou_get_chn_abs_addr(dev, (hi_ulong)(hi_uintptr_t) & (vo_reg->dhd0_vplus1.u32));
    dhd0_vplus1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_vplus1.bits.bvact = sync_info->bvact - 1;
    dhd0_vplus1.bits.bvbb = sync_info->bvbb - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_vplus1.u32);

    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_vplus2.u32));
    dhd0_vplus2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_vplus2.bits.bvfb = sync_info->bvfb - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_vplus2.u32);

    /* config VHD interface veritical bottom timming, */
    addr_reg = vou_get_chn_abs_addr(dev, (hi_uintptr_t) & (vo_reg->dhd0_pwr.u32));
    dhd0_pwr.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    dhd0_pwr.bits.hpw = sync_info->hpw - 1;
    dhd0_pwr.bits.vpw = sync_info->vpw - 1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, dhd0_pwr.u32);
}

hi_void vo_hal_intf_set_sync_info(hi_vo_dev dev, hal_disp_syncinfo *sync_info)
{
    vo_hal_check_phy_dev_return(dev);

    vo_hal_intf_set_sync_info_hvsync(dev, sync_info);
    vo_hal_intf_set_sync_info_other(dev, sync_info);
}

#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
