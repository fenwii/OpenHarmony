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

#ifndef __DRV_VO_COMM_COEF_ORG_H__
#define __DRV_VO_COMM_COEF_ORG_H__

#include "drv_vo_coef_comm.h"
#include "hal_vo_def.h"
#include "hi_common_vo.h"
#include "hi_inner_vo.h"

#if VO_DESC("UBOOT_VO")
const csc_coef *vo_get_csc_coef(hi_vo_csc_matrix csc_matrix);
const int *vo_get_sin_table(hi_void);
const int *vo_get_cos_table(hi_void);
#endif /* #if VO_DESC("UBOOT_VO") */

#endif
