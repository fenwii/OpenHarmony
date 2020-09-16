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

#ifndef __HAL_VO_VIDEO_H__
#define __HAL_VO_VIDEO_H__

#include "hal_vo_video_comm.h"
hi_void vo_hal_layer_set_cvfir_cfg(hal_disp_layer layer, hi_u32 vratio, vdp_v1_cvfir_cfg *cfg,
    vo_zme_comm_pq_cfg *pq_cfg);
hi_bool hal_cbm_get_cbm1_mixer_layer_id(hi_vo_layer layer, hi_u8 *layer_id);
hi_bool hal_cbm_get_cbm2_mixer_layer_id(hi_vo_layer layer, hi_u8 *layer_id);
hi_bool hal_cbm_get_cbm3_mixer_layer_id(hi_vo_layer layer, hi_u8 *layer_id);
#endif /* end of __HAL_VO_VIDEO_H__ */
