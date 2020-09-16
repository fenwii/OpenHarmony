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
#ifndef __HDMI_REG_AON_H__
#define __HDMI_REG_AON_H__

#include "hi_type.h"

typedef union {
    struct {
        unsigned int ddc_aon_access : 1;  /* [0] */
        unsigned int dcc_man_en     : 1;  /* [1] */
        unsigned int rsv_11         : 2;  /* [3:2] */
        unsigned int ddc_speed_cnt  : 9;  /* [12:4] */
        unsigned int rsv_12         : 19; /* [31:13] */
    } bits;
    unsigned int u32;
} ddc_mst_ctrl;

typedef union {
    struct {
        unsigned int ddc_i2c_no_ack     : 1;  /* [0] */
        unsigned int ddc_i2c_bus_low    : 1;  /* [1] */
        unsigned int ddc_i2c_in_prog    : 1;  /* [2] */
        unsigned int ddc_fifo_wr_in_use : 1;  /* [3] */
        unsigned int ddc_fifo_rd_in_use : 1;  /* [4] */
        unsigned int ddc_fifo_empty     : 1;  /* [5] */
        unsigned int ddc_fifo_half_full : 1;  /* [6] */
        unsigned int ddc_fifo_full      : 1;  /* [7] */
        unsigned int rsv_18             : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} ddc_mst_state;

typedef union {
    struct {
        unsigned int ddc_scl_st  : 1;  /* [0] */
        unsigned int ddc_sda_st  : 1;  /* [1] */
        unsigned int ddc_scl_oen : 1;  /* [2] */
        unsigned int ddc_sda_oen : 1;  /* [3] */
        unsigned int rsv_20      : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} ddc_man_ctrl;

typedef struct {
    volatile ddc_mst_ctrl  mst_ctrl;      /* 4040 */
    unsigned int           reserved_1[4]; /* 4044-4050 */
    volatile ddc_mst_state mst_state;     /* 4054 */
    unsigned int           reserved_2;    /* 4058 */
    volatile ddc_man_ctrl  man_ctrl;      /* 405C */
    unsigned int           reserved_3;    /* 4060 */
} tx_aon_reg_type;

int hdmi_tx_aon_reg_type_init(void);
hi_void hdmi_tx_aon_reg_type_deinit(void);
int hdmi_dcc_man_en_set(unsigned int dcc_man_en);
int hdmi_ddc_scl_oen_set(unsigned int ddc_scl_oen);
int hdmi_ddc_sda_oen_set(unsigned int ddc_sda_oen);
int hdmi_ddc_i2c_bus_low_get(void);
int hdmi_ddc_i2c_no_ack_get(void);
int hdmi_ddc_speed_cnt_set(unsigned int ddc_speed_cnt);
int hdmi_ddc_scl_st_get(void);
int hdmi_ddc_sda_st_get(void);

#endif /* __HDMI_REG_AON_H__ */

