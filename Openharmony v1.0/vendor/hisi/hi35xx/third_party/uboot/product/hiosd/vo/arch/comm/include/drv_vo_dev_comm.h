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

#ifndef __DRV_VO_COMM_DEV_H__
#define __DRV_VO_COMM_DEV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
typedef enum {
    VO_HD_HW_DEV = 0,  /* HD dev */
    VO_SD_HW_DEV,  /* SD dev */
    VO_UHD_HW_DEV,  /* UHD dev */
    VO_CAS_DEV,  /* cascade dev */
    VO_VIRT_DEV,  /* virtual dev */
    VO_DEV_TYPE_BUTT,
} vo_dev_type;

/* 50000: 50ms */
#define VO_DEV_REG_UP_TIMEOUT 50

#define VO_MIN_DIV_MODE      1
#define VO_MAX_DIV_MODE      4
#define VO_INTF_HDMI_DIV_MODE      1
#define VO_INTF_CVBS_DIV_MODE      4
#define VO_INTF_BT656_DIV_MODE     2
#define VO_INTF_RGB_DIV_MODE_1     1
#define VO_INTF_RGB_DIV_MODE_3     3
#define VO_INTF_RGB_DIV_MODE_4     4
#define VO_MIN_PRE_DIV_MODE  1
#define VO_MAX_PRE_DIV_MODE  32
#define VO_INTF_NO_HDMI_PRE_DIV_MODE      1

#define VO_MAX_USER_SYNC_INTFB 255
#define VO_MAX_USER_SYNC_VACT  4096
#define VO_MIN_USER_SYNC_VACT  100
#define VO_MAX_USER_SYNC_VBB   256
#define VO_MIN_USER_SYNC_VBB   1
#define VO_MAX_USER_SYNC_VFB   256
#define VO_MIN_USER_SYNC_VFB   1
#define VO_MAX_USER_SYNC_HACT  4096
#define VO_MIN_USER_SYNC_HACT  1
#define VO_MAX_USER_SYNC_HBB   65535
#define VO_MIN_USER_SYNC_HBB   1
#define VO_MAX_USER_SYNC_HFB   65535
#define VO_MIN_USER_SYNC_HFB   1
#define VO_MAX_USER_SYNC_BVACT 4096
#define VO_MAX_USER_SYNC_BVBB  256
#define VO_MAX_USER_SYNC_BVFB  256
#define VO_MAX_USER_SYNC_HPW   65535
#define VO_MIN_USER_SYNC_HPW   1
#define VO_MAX_USER_SYNC_VPW   256
#define VO_MIN_USER_SYNC_VPW   1

#if VO_DESC("dev drv api")
hi_u32 vo_drv_get_dev_bg_color(hi_vo_dev dev);
hi_vo_intf_type vo_drv_get_dev_intf_type(hi_vo_dev dev);
hi_vo_intf_sync vo_drv_get_dev_intf_sync(hi_vo_dev dev);
hi_u32 vo_drv_get_dev_vtth(hi_vo_dev dev);
hi_u32 vo_drv_get_dev_vtth2(hi_vo_dev dev);
hi_void vou_drv_set_disp_max_size(hi_vo_dev dev, hi_u32 max_width, hi_u32 max_height);
#endif

#if VO_DESC("dev")
hi_void vo_drv_get_sync_info(hi_vo_dev dev, hal_disp_syncinfo *sync_info);
hi_void vo_drv_set_sync_info(hi_vo_dev dev, hal_disp_syncinfo *sync_info);
hi_bool vo_drv_is_progressive(hi_vo_dev dev);
hi_void vo_drv_int_reg_up_mode(hi_vo_layer layer, vo_int_mode int_mode);
hi_void vo_drv_set_dev_default_vtth(hi_vo_dev dev);
hi_s32 vo_drv_set_dev_vtth(hi_vo_dev dev, hi_u32 vtth);
hi_s32 vo_drv_set_dev_vtth2(hi_vo_dev dev, hi_u32 vtth);
hi_bool vou_drv_get_dev_enable(hi_vo_dev dev);
hi_s32 vo_drv_check_dev_clkvalue(hi_vo_dev dev, const hi_vo_user_sync_info *sync_info);
hi_s32 vou_drv_check_dsd_intf(hi_vo_dev dev, hi_vo_intf_type intf_type);
hi_s32 vou_drv_check_dev_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync);
hi_s32 vou_drv_check_dev_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *pub_attr);
hi_void vo_drv_get_dev_reg_up(hi_vo_dev dev);
#endif

#if VO_DESC("dev layer prio")
hi_void vou_drv_set_layer_priority(hi_vo_dev dev, hi_vo_layer layer, hi_u32 priority);
#endif

#if VO_DESC("dev intf")
hi_void vou_drv_intf_csc_config(hi_vo_intf_type intf, const hi_vo_csc *csc);
hi_void vo_drv_set_vga_param(hi_vo_dev dev, const hi_vo_vga_param *vga_param);
hi_void vo_drv_set_hdmi_param(hi_vo_dev dev, const hi_vo_hdmi_param *hdmi_param);
hi_void vo_drv_set_rgb_param(hi_vo_dev dev, const hi_vo_rgb_param *rgb_param);
hi_void vo_drv_set_dev_mpp_chn(hi_vo_dev dev, hi_mpp_chn *mpp_chn);
hi_bool vo_drv_is_hdmi_intf(hi_vo_intf_type intf_type);
hi_bool vo_drv_is_rgb_intf(hi_vo_intf_type intf_type);
hi_bool vo_drv_is_mipi_intf(hi_vo_intf_type intf_type);
hi_bool vo_drv_is_bt1120_intf(hi_vo_intf_type intf_type);
#endif

#if VO_DESC("dev interrupt")
hi_void vo_drv_int_set_mode(hi_vo_dev dev, vo_int_mode int_mode);
#endif

#if VO_DESC("check id")
hi_s32 vo_drv_check_dev_id_pub(hi_vo_dev dev);
hi_s32 vo_drv_check_layer_id_pub(hi_vo_layer layer);
#endif

hi_void vo_drv_set_pub_attr(hi_vo_dev dev, const hi_vo_pub_attr *vo_pub_attr);
hi_void vo_drv_enable(hi_vo_dev dev);
hi_void vo_drv_disable(hi_vo_dev dev);
hi_u32 vou_drv_get_dev_layer_num(hi_vo_dev dev);
hi_void vou_drv_get_dev_layer(hi_vo_dev dev, hi_vo_layer *layer, hi_u32 vo_layer_num);
hi_vo_layer vo_drv_get_gfx_layer(hi_vo_dev dev);

hi_bool vo_drv_is_phy_dev_uhd(hi_vo_dev dev);
hi_bool vo_drv_is_phy_dev_hd(hi_vo_dev dev);
hi_bool vo_drv_is_phy_dev_sd(hi_vo_dev dev);

#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of __DRV_VO_COMM_DEV_H__ */
