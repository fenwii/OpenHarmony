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

#include "hal_vo_dev.h"
#include "hal_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")

hi_void hal_sys_set_outstanding(hi_void)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_mac_outstanding mac_outstanding;

    mac_outstanding.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) & (vo_reg->mac_outstanding.u32));
    mac_outstanding.bits.mstr0_routstanding = 0xf;  /* 0xf: master 0 read outstanding */
    mac_outstanding.bits.mstr0_woutstanding = 0x6;  /* 0x6: master 0 write outstanding */
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->mac_outstanding.u32), mac_outstanding.u32);
}

#if VO_DESC("dev intf")

hi_void vo_hal_intf_set_date_cvbs_gain(hi_u32 data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    vo_reg->date_coeff57.u32 = data;
}

hi_void vo_hal_intf_set_sync_inv(hi_vo_intf_type intf_type, hal_disp_syncinv *inv)
{
    if (intf_type == HI_VO_INTF_HDMI) {
        vo_hal_intf_set_hdmi_sync_inv(inv);
    } else if (intf_type == HI_VO_INTF_VGA) {
        vo_hal_intf_set_vga_sync_inv(inv);
    }  else if (intf_type == HI_VO_INTF_BT1120) {
        vo_hal_intf_set_bt_sync_inv(inv);
    } else if (intf_type == HI_VO_INTF_CVBS) {
        vo_hal_intf_set_cvbs_sync_inv(inv);
    }
}

hi_void vo_hal_intf_set_mux_sel_hd(hi_vo_dev dev, hi_vo_intf_type intf)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_mux vo_mux;

    vo_mux.u32 = vo_reg->vo_mux.u32;

    if (intf == HI_VO_INTF_HDMI) {
        vo_mux.bits.hdmi_sel = dev;
    } else if (intf == HI_VO_INTF_VGA) {
        vo_mux.bits.vga_sel = dev;
    }  else if (intf == HI_VO_INTF_BT1120) {
        vo_mux.bits.digital_sel = 0;
        vo_mux.bits.bt_sel = dev;
    }
    vo_reg->vo_mux.u32 = vo_mux.u32;
}

hi_void vo_hal_intf_set_csc_enable(hi_vo_intf_type intf, hi_bool enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_hdmi_csc_idc hdmi_csc_idc;
    volatile reg_vga_csc_idc vga_csc_idc;

    if (intf == HI_VO_INTF_HDMI) {
        hdmi_csc_idc.u32 = vo_reg->hdmi_csc_idc.u32;
        hdmi_csc_idc.bits.csc_en = enable;
        vo_reg->hdmi_csc_idc.u32 = hdmi_csc_idc.u32;
    } else if (intf == HI_VO_INTF_VGA) {
        vga_csc_idc.u32 = vo_reg->vga_csc_idc.u32;
        vga_csc_idc.bits.csc_en = enable;
        vo_reg->vga_csc_idc.u32 = vga_csc_idc.u32;
    }
}

hi_void vo_hal_intf_set_csc_dc_coef(hi_vo_intf_type intf, vdp_csc_dc_coef *csc_dc_coef)
{
    if (intf == HI_VO_INTF_HDMI) {
        vo_hal_intf_set_hdmi_csc_dc_coef(csc_dc_coef);
    } else if (intf == HI_VO_INTF_VGA) {
        vo_hal_intf_set_vga_csc_dc_coef(csc_dc_coef);
    }
}

hi_void vo_hal_intf_set_csc_coef(hi_vo_intf_type intf, vdp_csc_coef *csc_coef)
{
    if (intf == HI_VO_INTF_HDMI) {
        vo_hal_intf_set_hdmi_csc_coef(csc_coef);
    } else if (intf == HI_VO_INTF_VGA) {
        vo_hal_intf_set_vga_csc_coef(csc_coef);
    }
}

#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
