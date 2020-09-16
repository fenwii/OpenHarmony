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

#ifndef __MIPI_TX_HAL_H__
#define __MIPI_TX_HAL_H__

#include "mipi_tx.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

void mipi_tx_drv_set_phy_cfg(const combo_dev_cfg_t *dev_cfg);

void mipi_tx_drv_set_controller_cfg(const combo_dev_cfg_t *dev_cfg);

int mipi_tx_drv_set_cmd_info(const cmd_info_t *cmd_info);
int mipi_tx_drv_get_cmd_info(get_cmd_info_t *get_cmd_info);

void mipi_tx_drv_enable_input(output_mode_t output_mode);

void mipi_tx_drv_disable_input(void);

int mipi_tx_drv_init(void);

void mipi_tx_drv_exit(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
