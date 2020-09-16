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

#include "drv_vo_layer_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"
#include "drv_vo_coef_org_comm.h"
#include "vo.h"
#include "hi_math.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT_VO")
#if VO_DESC("layer csc")

hi_s32 vo_drv_get_csc_matrix(hi_vo_csc_matrix csc_matrix, const csc_coef **csc_tmp)
{
    *csc_tmp = vo_get_csc_coef(csc_matrix);
    if (*csc_tmp == HI_NULL) {
        return HI_ERR_VO_NULL_PTR;
    }
    return HI_SUCCESS;
}

hi_void vo_drv_calculate_yuv2rgb(hal_csc_value *csc_value, const csc_coef *csc_tmp, csc_coef *coef)
{
    hi_s32 luma;
    hi_s32 contrast;
    hi_s32 hue;
    hi_s32 satu;
    const hi_s32 csc_value_times = 100;
    const hi_s32 table_times = 1000;
    hi_s32 square_cv_times = csc_value_times * csc_value_times;
    const int *cos_table = vo_get_cos_table();
    const int *sin_table = vo_get_sin_table();

    luma = csc_value->luma;
    contrast = csc_value->cont;
    hue = csc_value->hue;
    satu = csc_value->satu;

    coef->csc_coef00 = (contrast * csc_tmp->csc_coef00) / csc_value_times;
    coef->csc_coef01 = (contrast * satu * ((csc_tmp->csc_coef01 * cos_table[hue] - csc_tmp->csc_coef02 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef02 = (contrast * satu * ((csc_tmp->csc_coef01 * sin_table[hue] + csc_tmp->csc_coef02 *
                                            cos_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef10 = (contrast * csc_tmp->csc_coef10) / csc_value_times;
    coef->csc_coef11 = (contrast * satu * ((csc_tmp->csc_coef11 * cos_table[hue] - csc_tmp->csc_coef12 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef12 = (contrast * satu * ((csc_tmp->csc_coef11 * sin_table[hue] + csc_tmp->csc_coef12 *
                                            cos_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef20 = (contrast * csc_tmp->csc_coef20) / csc_value_times;
    coef->csc_coef21 = (contrast * satu * ((csc_tmp->csc_coef21 * cos_table[hue] - csc_tmp->csc_coef22 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef22 = (contrast * satu * ((csc_tmp->csc_coef21 * sin_table[hue] + csc_tmp->csc_coef22 *
                                            cos_table[hue]) / table_times)) / square_cv_times;
    coef->csc_in_dc0 += (contrast != 0) ? (luma * 100 / contrast) : luma * 100;  /* 100 */
}

hi_void vo_drv_calculate_rgb2yuv(hal_csc_value *csc_value, const csc_coef *csc_tmp, csc_coef *coef)
{
    hi_s32 luma;
    hi_s32 contrast;
    hi_s32 hue;
    hi_s32 satu;
    const hi_s32 csc_value_times = 100;
    const hi_s32 table_times = 1000;
    hi_s32 square_cv_times = csc_value_times * csc_value_times;
    const int *cos_table = vo_get_cos_table();
    const int *sin_table = vo_get_sin_table();

    luma = csc_value->luma;
    contrast = csc_value->cont;
    hue = csc_value->hue;
    satu = csc_value->satu;

    coef->csc_coef00 = (contrast * csc_tmp->csc_coef00) / csc_value_times;
    coef->csc_coef01 = (contrast * csc_tmp->csc_coef01) / csc_value_times;
    coef->csc_coef02 = (contrast * csc_tmp->csc_coef02) / csc_value_times;
    coef->csc_coef10 = (contrast * satu * ((csc_tmp->csc_coef10 * cos_table[hue] + csc_tmp->csc_coef20 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef11 = (contrast * satu * ((csc_tmp->csc_coef11 * cos_table[hue] + csc_tmp->csc_coef21 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef12 = (contrast * satu * ((csc_tmp->csc_coef12 * cos_table[hue] + csc_tmp->csc_coef22 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef20 = (contrast * satu * ((csc_tmp->csc_coef20 * cos_table[hue] - csc_tmp->csc_coef10 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef21 = (contrast * satu * ((csc_tmp->csc_coef21 * cos_table[hue] - csc_tmp->csc_coef11 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_coef22 = (contrast * satu * ((csc_tmp->csc_coef22 * cos_table[hue] - csc_tmp->csc_coef12 *
                                            sin_table[hue]) / table_times)) / square_cv_times;
    coef->csc_out_dc0 += luma;
}

hi_void vou_drv_calc_csc_matrix(const hi_vo_csc *csc, hi_vo_csc_matrix csc_matrix, csc_coef *coef)
{
    hi_s32 ret;
    const csc_coef *csc_tmp = HI_NULL;
    hal_csc_value csc_value;

    if (csc->ex_csc_en == HI_FALSE) {
        csc_value.luma = (hi_s32)csc->luma * 64 / 100 - 32; /* 64: -32~32 100  */
    } else {
        csc_value.luma = (hi_s32)csc->luma * 256 / 100 - 128; /* 256: -128~128 128 100  */
    }

    csc_value.cont = ((hi_s32)csc->contrast - 50) * 2 + 100; /* 50 2 100 */
    csc_value.hue = (hi_s32)csc->hue * 60 / 100;             /* 60 100  */
    csc_value.satu = ((hi_s32)csc->saturation - 50) * 2 + 100; /* 50 2 100  */

    ret = vo_drv_get_csc_matrix(csc_matrix, &csc_tmp);
    if (ret != HI_SUCCESS) {
        return;
    }

    coef->csc_in_dc0 = csc_tmp->csc_in_dc0;
    coef->csc_in_dc1 = csc_tmp->csc_in_dc1;
    coef->csc_in_dc2 = csc_tmp->csc_in_dc2;
    coef->csc_out_dc0 = csc_tmp->csc_out_dc0;
    coef->csc_out_dc1 = csc_tmp->csc_out_dc1;
    coef->csc_out_dc2 = csc_tmp->csc_out_dc2;

    if ((csc_matrix >= HI_VO_CSC_MATRIX_BT601LIMIT_TO_RGBFULL) &&
        (csc_matrix <= HI_VO_CSC_MATRIX_BT709FULL_TO_RGBLIMIT)) {
        vo_drv_calculate_yuv2rgb(&csc_value, csc_tmp, coef);
    } else {
        vo_drv_calculate_rgb2yuv(&csc_value, csc_tmp, coef);
    }
}

hi_void vo_drv_clip_layer_csc_coef(csc_coef *coef)
{
    hi_s32 min_coef = 0;
    hi_s32 max_coef = 0;

    vo_drv_get_layer_csc_coef_range(&min_coef, &max_coef);
    coef->csc_coef00 = CLIP3(coef->csc_coef00, min_coef, max_coef);
    coef->csc_coef01 = CLIP3(coef->csc_coef01, min_coef, max_coef);
    coef->csc_coef02 = CLIP3(coef->csc_coef02, min_coef, max_coef);

    coef->csc_coef10 = CLIP3(coef->csc_coef10, min_coef, max_coef);
    coef->csc_coef11 = CLIP3(coef->csc_coef11, min_coef, max_coef);
    coef->csc_coef12 = CLIP3(coef->csc_coef12, min_coef, max_coef);

    coef->csc_coef20 = CLIP3(coef->csc_coef20, min_coef, max_coef);
    coef->csc_coef21 = CLIP3(coef->csc_coef21, min_coef, max_coef);
    coef->csc_coef22 = CLIP3(coef->csc_coef22, min_coef, max_coef);
}

hi_void vou_drv_layer_csc_config(hi_vo_layer layer, hi_vo_csc *csc, csc_coef_param *csc_param)
{
    csc_coef coef;
    vo_drv_layer *drv_layer_ctx = HI_NULL;

    vou_drv_calc_csc_matrix(csc, csc->csc_matrix, &coef);

    drv_layer_ctx = vo_drv_get_layer_ctx(layer);
    coef.new_csc_clip_max = drv_layer_ctx->csc_param.csc_clip_max;
    coef.new_csc_clip_min = drv_layer_ctx->csc_param.csc_clip_min;
    coef.new_csc_scale2p = drv_layer_ctx->csc_param.csc_scale2p;

    vo_drv_csc_trans_to_register(&coef);

    vo_drv_clip_layer_csc_coef(&coef);
    hal_layer_set_csc_coef(layer, &coef);
}

hi_void vou_drv_get_layer_csc_param(hi_vo_layer layer, csc_coef_param *csc_param)
{
    vo_drv_layer *drv_layer_ctx  = vo_drv_get_layer_ctx(layer);
    memcpy(csc_param, &drv_layer_ctx->csc_param, sizeof(csc_coef_param));
}
#endif

#if VO_DESC("layer cfg")

hi_vo_layer vo_drv_get_hw_layer(hi_vo_layer layer)
{
    return layer;
}

hi_void vou_drv_layer_enable(hi_vo_layer layer, hi_bool enable)
{
    hi_vo_layer hw_layer = vo_drv_get_hw_layer(layer);

    hal_video_hfir_set_ck_gt_en(hw_layer, enable);
    hal_layer_enable_layer(hw_layer, enable);
}

hi_void vou_drv_set_layer_reg_up(hi_vo_layer layer)
{
    hi_vo_layer hw_layer = vo_drv_get_hw_layer(layer);
    hal_layer_set_reg_up(hw_layer);
}

hi_void vou_drv_set_layer_data_fmt(hi_vo_layer layer, vou_layer_pixerl_format data_fmt)
{
    hi_vo_layer hw_layer = vo_drv_get_hw_layer(layer);
    hal_disp_layer hal_layer;
    hal_disp_pixel_format disp_data_fmt;

    hal_layer = vou_drv_convert_layer(hw_layer);
    disp_data_fmt = vou_drv_convert_data_format(data_fmt);
    hal_layer_set_layer_data_fmt(hal_layer, disp_data_fmt);
}
#endif
#endif /* #if VO_DESC("UBOOT_VO") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
