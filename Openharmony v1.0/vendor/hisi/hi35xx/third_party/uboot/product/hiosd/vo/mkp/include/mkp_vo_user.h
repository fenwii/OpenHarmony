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

#ifndef __MKP_VO_USER_H__
#define __MKP_VO_USER_H__

#include "hi_common_vo.h"
#include "hi_common.h"

hi_vo_sync_info *vo_get_dev_user_sync_timing(hi_vo_dev dev);
hi_vo_user_sync_info *vo_get_dev_user_sync_info(hi_vo_dev dev);

#endif /* end of __MKP_VO_USER_H__ */
