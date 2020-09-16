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
#ifndef __HDMI_HAL_INTF_H__
#define __HDMI_HAL_INTF_H__

#include "drv_hdmi_common.h"
#include "hdmi_hal_ctrl.h"
#include "hdmi_hal_ddc.h"
#include "hdmi_hal_scdc.h"

typedef struct {
    hi_bool            init;
    hdmi_tx_capability tx_capability;
    hi_u32             tmds_clk;
} hdmi_hal_cfg;

#endif /* __HDMI_HAL_INTF_H__ */

