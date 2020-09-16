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
        unsigned int tx_hw_day   : 8;  /* [7:0] */
        unsigned int tx_hw_month : 8;  /* [15:8] */
        unsigned int tx_hw_year  : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} tx_hw_info;

typedef union {
    struct {
        unsigned int tx_reg_version : 8; /* [7:0] */
        unsigned int tx_drv_version : 8; /* [15:8] */
        unsigned int tx_rtl_version : 8; /* [23:16] */
        unsigned int rsv_0          : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} tx_hw_version;

typedef union {
    struct {
        unsigned int rsv_1 : 32; /* [31:0] */
    } bits;
    unsigned int u32;
} tx_hw_feature;

typedef union {
    struct {
        unsigned int tx_aon_soft_arst_req : 1;  /* [0] */
        unsigned int rsv_2                : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} tx_aon_rst_ctrl;

typedef union {
    struct {
        unsigned int hpd_fillter_en   : 1;  /* [0] */
        unsigned int hpd_override_en  : 1;  /* [1] */
        unsigned int hpd_polarity_ctl : 1;  /* [2] */
        unsigned int hpd_soft_value   : 1;  /* [3] */
        unsigned int osc_div_cnt      : 12; /* [15:4] */
        unsigned int rsv_3            : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} hotplug_st_cfg;

typedef union {
    struct {
        unsigned int hpd_high_reshold : 16; /* [15:0] */
        unsigned int hpd_low_reshold  : 16; /* [31:16] */
    } bits;
    unsigned int u32;
} hotplug_fillter_cfg;

typedef union {
    struct {
        unsigned int hotplug_state : 1;  /* [0] */
        unsigned int phy_rx_sense  : 1;  /* [1] */
        unsigned int rsv_4         : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} tx_aon_state;

typedef union {
    struct {
        unsigned int aon_intr_mask0  : 1;  /* [0] */
        unsigned int aon_intr_mask1  : 1;  /* [1] */
        unsigned int rsv_5           : 1;  /* [2] */
        unsigned int rsv_6           : 1;  /* [3] */
        unsigned int aon_intr_mask4  : 1;  /* [4] */
        unsigned int aon_intr_mask5  : 1;  /* [5] */
        unsigned int aon_intr_mask6  : 1;  /* [6] */
        unsigned int aon_intr_mask7  : 1;  /* [7] */
        unsigned int aon_intr_mask8  : 1;  /* [8] */
        unsigned int aon_intr_mask9  : 1;  /* [9] */
        unsigned int aon_intr_mask10 : 1;  /* [10] */
        unsigned int aon_intr_mask11 : 1;  /* [11] */
        unsigned int aon_intr_mask12 : 1;  /* [12] */
        unsigned int aon_intr_mask13 : 1;  /* [13] */
        unsigned int rsv_7           : 18; /* [31:14] */
    } bits;
    unsigned int u32;
} tx_aon_intr_mask;

typedef union {
    struct {
        unsigned int aon_intr_stat0  : 1;  /* [0] */
        unsigned int aon_intr_stat1  : 1;  /* [1] */
        unsigned int rsv_8           : 1;  /* [2] */
        unsigned int rsv_9           : 1;  /* [3] */
        unsigned int aon_intr_stat4  : 1;  /* [4] */
        unsigned int aon_intr_stat5  : 1;  /* [5] */
        unsigned int aon_intr_stat6  : 1;  /* [6] */
        unsigned int aon_intr_stat7  : 1;  /* [7] */
        unsigned int aon_intr_stat8  : 1;  /* [8] */
        unsigned int aon_intr_stat9  : 1;  /* [9] */
        unsigned int aon_intr_stat10 : 1;  /* [10] */
        unsigned int aon_intr_stat11 : 1;  /* [11] */
        unsigned int aon_intr_stat12 : 1;  /* [12] */
        unsigned int aon_intr_stat13 : 1;  /* [13] */
        unsigned int rsv_10          : 18; /* [31:14] */
    } bits;
    unsigned int u32;
} tx_aon_intr_state;

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
        unsigned int ddc_fifo_data_out : 8;  /* [7:0] */
        unsigned int rsv_13            : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} ddc_fifo_rdata;

typedef union {
    struct {
        unsigned int ddc_fifo_data_in : 8;  /* [7:0] */
        unsigned int rsv_14           : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} ddc_fifo_wdata;

typedef union {
    struct {
        unsigned int ddc_fifo_data_cnt : 5;  /* [4:0] */
        unsigned int rsv_15            : 3;  /* [7:5] */
        unsigned int ddc_data_out_cnt  : 10; /* [17:8] */
        unsigned int rsv_16            : 14; /* [31:18] */
    } bits;
    unsigned int u32;
} ddc_data_cnt;

typedef union {
    struct {
        unsigned int ddc_slave_addr   : 8; /* [7:0] */
        unsigned int ddc_slave_offset : 8; /* [15:8] */
        unsigned int ddc_slave_seg    : 8; /* [23:16] */
        unsigned int rsv_17           : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} ddc_slave_cfg;

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
        unsigned int ddc_mst_cmd : 4;  /* [3:0] */
        unsigned int rsv_19      : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} ddc_mst_cmd;

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

typedef union {
    struct {
        unsigned int ddc_clr_bus_low : 1;  /* [0] */
        unsigned int ddc_clr_no_ack  : 1;  /* [1] */
        unsigned int rsv_21          : 30; /* [31:2] */
    } bits;
    unsigned int u32;
} ddc_state_clr;

typedef struct {
    volatile tx_hw_info          hw_info;            /* 4000 */
    volatile tx_hw_version       hw_version;         /* 4004 */
    volatile tx_hw_feature       hw_feature;         /* 4008 */
    unsigned int                 reserved_0[4];      /* 400C-4018 */
    volatile tx_aon_rst_ctrl     aon_rst_ctrl;       /* 401C */
    volatile hotplug_st_cfg      hph_st_cfg;         /* 4020 */
    volatile hotplug_fillter_cfg hpd_fillter_cfg;    /* 4024 */
    volatile tx_aon_state        aon_state;          /* 4028 */
    unsigned int                 reserved_2[1];      /* 402C */
    volatile tx_aon_intr_mask    aon_intr_mask;      /* 4030 */
    volatile tx_aon_intr_state   aon_intr_state;     /* 4034 */
    unsigned int                 reserved_3[2];      /* 4038-403C */
    volatile ddc_mst_ctrl        reg_ddc_mst_ctrl;   /* 4040 */
    volatile ddc_fifo_rdata      reg_ddc_fifo_rdata; /* 4044 */
    volatile ddc_fifo_wdata      reg_ddc_fifo_wdata; /* 4048 */
    volatile ddc_data_cnt        reg_ddc_data_cnt;   /* 404C */
    volatile ddc_slave_cfg       reg_ddc_slave_cfg;  /* 4050 */
    volatile ddc_mst_state       reg_ddc_mst_state;  /* 4054 */
    volatile ddc_mst_cmd         reg_ddc_mst_cmd;    /* 4058 */
    volatile ddc_man_ctrl        reg_ddc_man_ctrl;   /* 405C */
    volatile ddc_state_clr       reg_ddc_state_clr;  /* 4060 */
} tx_aon_regs;

int hdmi_tx_aon_regs_init(void);
hi_void hdmi_tx_aon_regs_deinit(void);
hi_void hdmi_dcc_man_en_set(unsigned int man_en);
hi_void hdmi_ddc_scl_oen_set(unsigned int scl_oen);
hi_void hdmi_ddc_sda_oen_set(unsigned int sda_oen);
int hdmi_ddc_i2c_bus_low_get(void);
int hdmi_ddc_i2c_no_ack_get(void);
int hdmi_ddc_scl_st_get(void);
int hdmi_ddc_sda_st_get(void);

#endif /* __HDMI_REG_AON_H__ */

