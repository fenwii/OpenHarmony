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

#ifndef __MKP_VO_COMM_H__
#define __MKP_VO_COMM_H__

#include "hi_inner_vo.h"

#define VO_RECT_INTERLACED_ALIGN  4

#if VO_DESC("check attr pub")
hi_s32 vo_check_bool_value(hi_bool bool_val);
hi_s32 vo_check_rect_align(const hi_rect *rect);
hi_s32 vo_check_csc_no_matrix(const hi_vo_csc *csc);
#endif

#if VO_DESC("check dev pub")
hi_bool vo_is_phy_dev(hi_vo_dev dev);
hi_bool vo_is_virt_dev(hi_vo_dev dev);
hi_bool vo_is_cas_dev(hi_vo_dev dev);
hi_bool vo_is_typical_intf_sync(hi_vo_intf_sync intf_sync);
hi_bool vo_is_user_intf_sync(hi_vo_intf_sync intf_sync);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* end of #ifndef __MKP_VO_COMM_H__ */
