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

#include "hal_vo_video.h"
#include "hi_board.h"
#include "hi_common_vo.h"
#include "hi_math.h"
#include "drv_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */
#if VO_DESC("UBOOT_VO")

hi_void vo_hal_layer_set_cvfir_cfg(hal_disp_layer layer, hi_u32 vratio, vdp_v1_cvfir_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg)
{
    if (layer == HAL_DISP_LAYER_VHD1) {
        vo_hal_layer_set_v1_cvfir_cfg(vratio, cfg, pq_cfg);
        return;
    }

    if (layer == HAL_DISP_LAYER_VHD2) {
        vo_hal_layer_set_v2_cvfir_cfg(vratio, cfg, pq_cfg);
    }
}

hi_bool hal_cbm_get_cbm1_mixer_layer_id(hi_vo_layer layer, hi_u8 *layer_id)
{
    switch (layer) {
        case HI_VO_LAYER_V0:
            *layer_id = 0x1;
            break;

        case HI_VO_LAYER_V2:
            *layer_id = 0x3;
            break;

        case HI_VO_LAYER_G0:
            *layer_id = 0x2;
            break;

        case HI_VO_LAYER_G2:
            *layer_id = 0x4;
            break;

        case HI_VO_LAYER_G3:
            *layer_id = 0x5;
            break;

        case VO_LAYER_BUTT:
            *layer_id = 0x0;
            break;

        default:
            vo_err_trace("error layer id %d found\n", layer);
            return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_cbm_get_cbm2_mixer_layer_id(hi_vo_layer layer, hi_u8 *layer_id)
{
    switch (layer) {
        case HI_VO_LAYER_V1:
            *layer_id = 0x1;
            break;

        case HI_VO_LAYER_V2:
            *layer_id = 0x3;
            break;

        case HI_VO_LAYER_G1:
            *layer_id = 0x2;
            break;

        case HI_VO_LAYER_G2:
            *layer_id = 0x4;
            break;

        case HI_VO_LAYER_G3:
            *layer_id = 0x5;
            break;

        case VO_LAYER_BUTT:
            *layer_id = 0x0;
            break;

        default:
            vo_err_trace("error layer id %d found\n", layer);
            return HI_FALSE;
    }

    return HI_TRUE;
}

hi_bool hal_cbm_get_cbm3_mixer_layer_id(hi_vo_layer layer, hi_u8 *layer_id)
{
    switch (layer) {
        case HI_VO_LAYER_V3:
            *layer_id = 0x1;
            break;

        case HI_VO_LAYER_G2:
            *layer_id = 0x3;
            break;

        case HI_VO_LAYER_G3:
            *layer_id = 0x2;
            break;

        case VO_LAYER_BUTT:
            *layer_id = 0x0;
            break;

        default:
            vo_err_trace("error layer id %d found\n", layer);
            return HI_FALSE;
    }

    return HI_TRUE;
}

#endif /* #if VO_DESC("UBOOT_VO") */
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
