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

#include "mkp_vo_intf.h"
#include "drv_vo.h"
#include "vo.h"
#include "mkp_vo.h"

#include "mkp_vo_comm.h"
#include "mkp_vo_dev.h"

#if VO_DESC("hdmi param")
hi_void vo_init_hdmi_param(hi_vo_hdmi_param *hdmi_param)
{
    hdmi_param->csc.csc_matrix = HI_VO_CSC_MATRIX_BT601FULL_TO_BT601FULL;
    hdmi_param->csc.luma = VO_CSC_DEF_VAL;
    hdmi_param->csc.contrast = VO_CSC_DEF_VAL;
    hdmi_param->csc.hue = VO_CSC_DEF_VAL;
    hdmi_param->csc.saturation = VO_CSC_DEF_VAL;
    hdmi_param->csc.ex_csc_en = HI_FALSE;
}
#endif
#if VO_DESC("vga param")
hi_void vo_init_vga_param(hi_vo_vga_param *vga_param)
{
    vga_param->csc.csc_matrix = HI_VO_CSC_MATRIX_BT601FULL_TO_RGBFULL;
    vga_param->csc.luma = VO_CSC_DEF_VAL;
    vga_param->csc.contrast = VO_CSC_DEF_VAL;
    vga_param->csc.hue = VO_CSC_DEF_VAL;
    vga_param->csc.saturation = VO_CSC_DEF_VAL;
    vga_param->csc.ex_csc_en = HI_FALSE;
    vga_param->gain = vo_drv_get_vga_gain_def();
    vga_param->sharpen_strength = VO_VGA_SHARPEN_STRENGTH_DEF;
}
#endif

#if VO_DESC("rgb param")
hi_void vo_init_rgb_param(hi_vo_rgb_param *rgb_param)
{
    rgb_param->csc.csc_matrix = HI_VO_CSC_MATRIX_BT601FULL_TO_RGBFULL;
    rgb_param->csc.luma = VO_CSC_DEF_VAL;
    rgb_param->csc.contrast = VO_CSC_DEF_VAL;
    rgb_param->csc.hue = VO_CSC_DEF_VAL;
    rgb_param->csc.saturation = VO_CSC_DEF_VAL;
    rgb_param->csc.ex_csc_en = HI_FALSE;
    rgb_param->rgb_inverted_en = HI_FALSE;
    rgb_param->bit_inverted_en = HI_FALSE;
}
#endif

#if VO_DESC("bt param")
hi_void vo_init_bt_param(hi_vo_bt_param *bt_param)
{
    bt_param->yc_inverted_en = HI_FALSE;
    bt_param->bit_inverted_en = HI_FALSE;
}
#endif
