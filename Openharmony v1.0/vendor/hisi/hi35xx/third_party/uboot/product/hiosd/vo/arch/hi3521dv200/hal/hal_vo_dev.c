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
    mac_outstanding.bits.mstr0_woutstanding = 0x7;  /* 0x7: master 0 write outstanding */
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) & (vo_reg->mac_outstanding.u32), mac_outstanding.u32);
}

#if VO_DESC("dev intf")

hi_void vo_hal_intf_set_date_cvbs_gain(hi_u32 data)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    vo_reg->date_coeff57.u32 = data;
}

static hi_void vo_hal_intf_set_rgb_sync_inv(hal_disp_syncinv *inv)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_intf_lcd_sync_inv intf_lcd_sync_inv;

    intf_lcd_sync_inv.u32 = vo_reg->intf_lcd_sync_inv.u32;
    intf_lcd_sync_inv.bits.dv_inv = inv->dv_inv;
    intf_lcd_sync_inv.bits.hs_inv = inv->hs_inv;
    intf_lcd_sync_inv.bits.vs_inv = inv->vs_inv;
    intf_lcd_sync_inv.bits.f_inv = inv->f_inv;
    vo_reg->intf_lcd_sync_inv.u32 = intf_lcd_sync_inv.u32;
}

hi_void vo_hal_intf_set_sync_inv(hi_vo_intf_type intf_type, hal_disp_syncinv *inv)
{
    switch (intf_type) {
        case HI_VO_INTF_BT1120:
        case HI_VO_INTF_BT656:
            vo_hal_intf_set_bt_sync_inv(inv);
            break;

        case HI_VO_INTF_CVBS:
            vo_hal_intf_set_cvbs_sync_inv(inv);
            break;

        case HI_VO_INTF_VGA:
            vo_hal_intf_set_vga_sync_inv(inv);
            break;

        case HI_VO_INTF_HDMI:
            vo_hal_intf_set_hdmi_sync_inv(inv);
            break;

        case HI_VO_INTF_RGB_6BIT:
        case HI_VO_INTF_RGB_8BIT:
        case HI_VO_INTF_RGB_16BIT:
        case HI_VO_INTF_RGB_18BIT:
        case HI_VO_INTF_RGB_24BIT:
            vo_hal_intf_set_rgb_sync_inv(inv);
            break;

        default:
            return;
    }
}

hi_void vo_hal_intf_set_mux_sel_hd(hi_vo_dev dev, hi_vo_intf_type intf)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_vo_mux vo_mux;

    vo_mux.u32 = vo_reg->vo_mux.u32;

    switch (intf) {
        case HI_VO_INTF_HDMI:
            vo_mux.bits.hdmi_sel = dev;
            break;

        case HI_VO_INTF_VGA:
            vo_mux.bits.vga_sel = dev;
            break;

        case HI_VO_INTF_BT1120:
            vo_mux.bits.digital_sel = 0;
            vo_mux.bits.bt_sel = dev;
            break;

        case HI_VO_INTF_BT656:
            vo_mux.bits.digital_sel = 0x1;
            vo_mux.bits.bt_sel = dev;
            break;

        case HI_VO_INTF_RGB_6BIT:
        case HI_VO_INTF_RGB_8BIT:
        case HI_VO_INTF_RGB_16BIT:
        case HI_VO_INTF_RGB_18BIT:
        case HI_VO_INTF_RGB_24BIT:
            vo_mux.bits.digital_sel = 0x2;
            vo_mux.bits.bt_sel = dev;
            break;

        default:
            return;
    }

    vo_reg->vo_mux.u32 = vo_mux.u32;
}

hi_void vo_hal_intf_set_csc_enable(hi_vo_intf_type intf, hi_bool enable)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_hdmi_csc_idc hdmi_csc_idc;
    volatile reg_vga_csc_idc vga_csc_idc;
    volatile reg_lcd_csc_idc rgb_csc_idc;

    switch (intf) {
        case HI_VO_INTF_HDMI:
            hdmi_csc_idc.u32 = vo_reg->hdmi_csc_idc.u32;
            hdmi_csc_idc.bits.csc_en = enable;
            vo_reg->hdmi_csc_idc.u32 = hdmi_csc_idc.u32;
            break;

        case HI_VO_INTF_VGA:
            vga_csc_idc.u32 = vo_reg->vga_csc_idc.u32;
            vga_csc_idc.bits.csc_en = enable;
            vo_reg->vga_csc_idc.u32 = vga_csc_idc.u32;
            break;

        case HI_VO_INTF_RGB_6BIT:
        case HI_VO_INTF_RGB_8BIT:
        case HI_VO_INTF_RGB_16BIT:
        case HI_VO_INTF_RGB_18BIT:
        case HI_VO_INTF_RGB_24BIT:
            rgb_csc_idc.u32 = vo_reg->lcd_csc_idc.u32;
            rgb_csc_idc.bits.csc_en = enable;
            vo_reg->lcd_csc_idc.u32 = rgb_csc_idc.u32;
            break;

        default:
            return;
    }
}

static hi_void vo_hal_intf_set_rgb_csc_dc_coef(vdp_csc_dc_coef *csc_dc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_csc_idc rgb_csc_idc;
    volatile reg_lcd_csc_odc rgb_csc_odc;
    volatile reg_lcd_csc_iodc rgb_csc_iodc;

    rgb_csc_idc.u32 = vo_reg->lcd_csc_idc.u32;
    rgb_csc_odc.u32 = vo_reg->lcd_csc_odc.u32;
    rgb_csc_iodc.u32 = vo_reg->lcd_csc_iodc.u32;

    rgb_csc_idc.bits.cscidc0 = csc_dc_coef->csc_in_dc2;
    rgb_csc_idc.bits.cscidc1 = csc_dc_coef->csc_in_dc1;
    rgb_csc_iodc.bits.cscidc2 = csc_dc_coef->csc_in_dc0;
    rgb_csc_odc.bits.cscodc0 = csc_dc_coef->csc_out_dc2;
    rgb_csc_odc.bits.cscodc1 = csc_dc_coef->csc_out_dc1;
    rgb_csc_iodc.bits.cscodc2 = csc_dc_coef->csc_out_dc0;

    vo_reg->lcd_csc_idc.u32 = rgb_csc_idc.u32;
    vo_reg->lcd_csc_odc.u32 = rgb_csc_odc.u32;
    vo_reg->lcd_csc_iodc.u32 = rgb_csc_iodc.u32;
}

hi_void vo_hal_intf_set_csc_dc_coef(hi_vo_intf_type intf, vdp_csc_dc_coef *csc_dc_coef)
{
    switch (intf) {
        case HI_VO_INTF_HDMI:
            vo_hal_intf_set_hdmi_csc_dc_coef(csc_dc_coef);
            break;

        case HI_VO_INTF_VGA:
            vo_hal_intf_set_vga_csc_dc_coef(csc_dc_coef);
            break;

        case HI_VO_INTF_RGB_6BIT:
        case HI_VO_INTF_RGB_8BIT:
        case HI_VO_INTF_RGB_16BIT:
        case HI_VO_INTF_RGB_18BIT:
        case HI_VO_INTF_RGB_24BIT:
            vo_hal_intf_set_rgb_csc_dc_coef(csc_dc_coef);
            break;

        default:
            return;
    }
}

static hi_void vo_hal_intf_set_rgb_csc_coef(vdp_csc_coef *csc_coef)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_csc_p0 rgb_csc_p0;
    volatile reg_lcd_csc_p1 rgb_csc_p1;
    volatile reg_lcd_csc_p2 rgb_csc_p2;
    volatile reg_lcd_csc_p3 rgb_csc_p3;
    volatile reg_lcd_csc_p4 rgb_csc_p4;

    rgb_csc_p0.u32 = vo_reg->lcd_csc_p0.u32;
    rgb_csc_p1.u32 = vo_reg->lcd_csc_p1.u32;
    rgb_csc_p2.u32 = vo_reg->lcd_csc_p2.u32;
    rgb_csc_p3.u32 = vo_reg->lcd_csc_p3.u32;
    rgb_csc_p4.u32 = vo_reg->lcd_csc_p4.u32;

    rgb_csc_p0.bits.cscp00 = csc_coef->csc_coef00;
    rgb_csc_p0.bits.cscp01 = csc_coef->csc_coef01;
    rgb_csc_p1.bits.cscp02 = csc_coef->csc_coef02;
    rgb_csc_p1.bits.cscp10 = csc_coef->csc_coef10;
    rgb_csc_p2.bits.cscp11 = csc_coef->csc_coef11;
    rgb_csc_p2.bits.cscp12 = csc_coef->csc_coef12;
    rgb_csc_p3.bits.cscp20 = csc_coef->csc_coef20;
    rgb_csc_p3.bits.cscp21 = csc_coef->csc_coef21;
    rgb_csc_p4.bits.cscp22 = csc_coef->csc_coef22;

    vo_reg->lcd_csc_p0.u32 = rgb_csc_p0.u32;
    vo_reg->lcd_csc_p1.u32 = rgb_csc_p1.u32;
    vo_reg->lcd_csc_p2.u32 = rgb_csc_p2.u32;
    vo_reg->lcd_csc_p3.u32 = rgb_csc_p3.u32;
    vo_reg->lcd_csc_p4.u32 = rgb_csc_p4.u32;
}

hi_void vo_hal_intf_set_csc_coef(hi_vo_intf_type intf, vdp_csc_coef *csc_coef)
{
    switch (intf) {
        case HI_VO_INTF_HDMI:
            vo_hal_intf_set_hdmi_csc_coef(csc_coef);
            break;

        case HI_VO_INTF_VGA:
            vo_hal_intf_set_vga_csc_coef(csc_coef);
            break;

        case HI_VO_INTF_RGB_6BIT:
        case HI_VO_INTF_RGB_8BIT:
        case HI_VO_INTF_RGB_16BIT:
        case HI_VO_INTF_RGB_18BIT:
        case HI_VO_INTF_RGB_24BIT:
            vo_hal_intf_set_rgb_csc_coef(csc_coef);
            break;

        default:
            return;
    }
}

hi_bool hal_disp_set_lcd_serial_perd(hi_u32 serial_perd)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_intf_lcd_ctrl intf_lcd_ctrl;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf_lcd_ctrl.u32));
    intf_lcd_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);

    intf_lcd_ctrl.bits.lcd_serial_perd = serial_perd;

    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, intf_lcd_ctrl.u32);
    return HI_TRUE;
}

hi_bool vo_hal_set_intf_ctrl(hi_vo_intf_type intf, hi_u32 *ctrl_info)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    reg_intf_bt_ctrl intf_bt_ctrl;
    reg_intf_lcd_ctrl intf_lcd_ctrl;
    volatile hi_ulong addr_reg;

    reg_intf_bt_ctrl *bt_ctrl = HI_NULL;
    reg_intf_lcd_ctrl *lcd_ctrl = HI_NULL;

    if ((intf == HI_VO_INTF_BT1120) ||
        (intf == HI_VO_INTF_BT656)) {
        bt_ctrl = (reg_intf_bt_ctrl *)ctrl_info;
        addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf_bt_ctrl.u32));
        intf_bt_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        intf_bt_ctrl.bits.uv_mode = bt_ctrl->bits.uv_mode;
        intf_bt_ctrl.bits.hdmi_mode = bt_ctrl->bits.hdmi_mode;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, intf_bt_ctrl.u32);
    } else if ((intf == HI_VO_INTF_RGB_6BIT) ||
               (intf == HI_VO_INTF_RGB_8BIT) ||
               (intf == HI_VO_INTF_RGB_16BIT) ||
               (intf == HI_VO_INTF_RGB_18BIT) ||
               (intf == HI_VO_INTF_RGB_24BIT)) {
        lcd_ctrl = (reg_intf_lcd_ctrl *)ctrl_info;
        addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf_lcd_ctrl.u32));
        intf_lcd_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
        intf_lcd_ctrl.bits.lcd_format = lcd_ctrl->bits.lcd_format;
        intf_lcd_ctrl.bits.hdmi_mode = lcd_ctrl->bits.hdmi_mode;
        hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, intf_lcd_ctrl.u32);
    } else {
        return HI_FALSE;
    }

    return HI_TRUE;
}

#endif

#if VO_DESC("intf dither")

static hi_void vo_hal_intf_set_lcd_dither_sed0(vo_dihter_sed *dither_sed)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_dither_sed_y0 lcd_dither_sed_y0;
    volatile reg_lcd_dither_sed_u0 lcd_dither_sed_u0;
    volatile reg_lcd_dither_sed_v0 lcd_dither_sed_v0;
    volatile reg_lcd_dither_sed_w0 lcd_dither_sed_w0;
    volatile hi_ulong addr_reg;

    /* set sed_y0,sed_u0,sed_v0,sed_w0 */
    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_y0.u32));
    lcd_dither_sed_y0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_y0.bits.dither_sed_y0 = dither_sed->dither_sed_y0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_y0.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_u0.u32));
    lcd_dither_sed_u0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_u0.bits.dither_sed_u0 = dither_sed->dither_sed_u0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_u0.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_v0.u32));
    lcd_dither_sed_v0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_v0.bits.dither_sed_v0 = dither_sed->dither_sed_v0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_v0.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_w0.u32));
    lcd_dither_sed_w0.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_w0.bits.dither_sed_w0 = dither_sed->dither_sed_w0;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_w0.u32);
}

static hi_void vo_hal_intf_set_lcd_dither_sed1(vo_dihter_sed *dither_sed)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_dither_sed_y1 lcd_dither_sed_y1;
    volatile reg_lcd_dither_sed_u1 lcd_dither_sed_u1;
    volatile reg_lcd_dither_sed_v1 lcd_dither_sed_v1;
    volatile reg_lcd_dither_sed_w1 lcd_dither_sed_w1;
    volatile hi_ulong addr_reg;

    /* set sed_y1,sed_u1,sed_v1,sed_w1 */
    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_y1.u32));
    lcd_dither_sed_y1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_y1.bits.dither_sed_y1 = dither_sed->dither_sed_y1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_y1.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_u1.u32));
    lcd_dither_sed_u1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_u1.bits.dither_sed_u1 = dither_sed->dither_sed_u1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_u1.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_v1.u32));
    lcd_dither_sed_v1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_v1.bits.dither_sed_v1 = dither_sed->dither_sed_v1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_v1.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_w1.u32));
    lcd_dither_sed_w1.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_w1.bits.dither_sed_w1 = dither_sed->dither_sed_w1;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_w1.u32);
}

static hi_void vo_hal_intf_set_lcd_dither_sed2(vo_dihter_sed *dither_sed)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_dither_sed_y2 lcd_dither_sed_y2;
    volatile reg_lcd_dither_sed_u2 lcd_dither_sed_u2;
    volatile reg_lcd_dither_sed_v2 lcd_dither_sed_v2;
    volatile reg_lcd_dither_sed_w2 lcd_dither_sed_w2;
    volatile hi_ulong addr_reg;

    /* set sed_y2,sed_u2,sed_v2,sed_w2 */
    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf0_dither_sed_y2.u32));
    lcd_dither_sed_y2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_y2.bits.dither_sed_y2 = dither_sed->dither_sed_y2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_y2.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf0_dither_sed_u2.u32));
    lcd_dither_sed_u2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_u2.bits.dither_sed_u2 = dither_sed->dither_sed_u2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_u2.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf0_dither_sed_v2.u32));
    lcd_dither_sed_v2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_v2.bits.dither_sed_v2 = dither_sed->dither_sed_v2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_v2.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->intf0_dither_sed_w2.u32));
    lcd_dither_sed_w2.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_w2.bits.dither_sed_w2 = dither_sed->dither_sed_w2;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_w2.u32);
}

static hi_void vo_hal_intf_set_lcd_dither_sed3(vo_dihter_sed *dither_sed)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_dither_sed_y3 lcd_dither_sed_y3;
    volatile reg_lcd_dither_sed_u3 lcd_dither_sed_u3;
    volatile reg_lcd_dither_sed_v3 lcd_dither_sed_v3;
    volatile reg_lcd_dither_sed_w3 lcd_dither_sed_w3;
    volatile hi_ulong addr_reg;

    /* set sed_y3,sed_u3,sed_v3,sed_w3 */
    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_y3.u32));
    lcd_dither_sed_y3.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_y3.bits.dither_sed_y3 = dither_sed->dither_sed_y3;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_y3.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_u3.u32));
    lcd_dither_sed_u3.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_u3.bits.dither_sed_u3 = dither_sed->dither_sed_u3;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_u3.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_v3.u32));
    lcd_dither_sed_v3.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_v3.bits.dither_sed_v3 = dither_sed->dither_sed_v3;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_v3.u32);

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_sed_w3.u32));
    lcd_dither_sed_w3.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_sed_w3.bits.dither_sed_w3 = dither_sed->dither_sed_w3;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_sed_w3.u32);
}

static hi_void vo_hal_intf_set_lcd_dither_sed(vo_dihter_sed *dither_sed)
{
    vo_hal_intf_set_lcd_dither_sed0(dither_sed);
    vo_hal_intf_set_lcd_dither_sed1(dither_sed);
    vo_hal_intf_set_lcd_dither_sed2(dither_sed);
    vo_hal_intf_set_lcd_dither_sed3(dither_sed);
}

static hi_void vo_hal_intf_set_lcd_dither_thr_min_max(hi_u32 thr_min, hi_u32 thr_max)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_dither_thr lcd_dither_thr;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_thr.u32));
    lcd_dither_thr.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_thr.bits.dither_thr_min = thr_min;
    lcd_dither_thr.bits.dither_thr_max = thr_max;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_thr.u32);
}

static hi_void vo_hal_intf_set_lcd_dither_ctrl(vdp_dither_cfg *cfg)
{
    volatile reg_vdp_regs *vo_reg = vo_hal_get_reg();
    volatile reg_lcd_dither_ctrl lcd_dither_ctrl;
    volatile hi_ulong addr_reg;

    addr_reg = (hi_ulong)((hi_uintptr_t) & (vo_reg->lcd_dither_ctrl.u32));
    lcd_dither_ctrl.u32 = hal_read_reg((hi_u32 *)(hi_uintptr_t) addr_reg);
    lcd_dither_ctrl.bits.dither_round_unlim = cfg->dither_round_unlim;
    lcd_dither_ctrl.bits.i_data_width_dither = cfg->i_data_width_dither;
    lcd_dither_ctrl.bits.o_data_width_dither = cfg->o_data_width_dither;
    lcd_dither_ctrl.bits.dither_en = cfg->dither_en;
    lcd_dither_ctrl.bits.dither_mode = cfg->dither_mode;
    lcd_dither_ctrl.bits.dither_round = cfg->dither_round;
    lcd_dither_ctrl.bits.dither_domain_mode = cfg->dither_domain_mode;
    lcd_dither_ctrl.bits.dither_tap_mode = cfg->dither_tap_mode;
    hal_write_reg ((hi_u32 *)(hi_uintptr_t) addr_reg, lcd_dither_ctrl.u32);
}

hi_void vo_hal_intf_set_lcd_dither(vdp_dither_cfg *cfg)
{
    /* lcd_dither_ctrl */
    vo_hal_intf_set_lcd_dither_ctrl(cfg);

    /* lcd_dither_sed */
    vo_hal_intf_set_lcd_dither_sed(&cfg->dither_sed);

    /* lcd_dither_thr */
    vo_hal_intf_set_lcd_dither_thr_min_max(cfg->dither_thr_min, cfg->dither_thr_max);
}

#endif

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
