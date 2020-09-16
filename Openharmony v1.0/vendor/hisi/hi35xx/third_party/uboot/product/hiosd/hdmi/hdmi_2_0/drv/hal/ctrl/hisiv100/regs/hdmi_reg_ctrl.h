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
#ifndef __HDMI_REG_CTRL_H__
#define __HDMI_REG_CTRL_H__

#include "hi_type.h"

typedef union {
    struct {
        unsigned int tx_pwd_srst_req    : 1;  /* [0] */
        unsigned int tx_sys_srst_req    : 1;  /* [1] */
        unsigned int tx_vid_srst_req    : 1;  /* [2] */
        unsigned int tx_hdmi_srst_req   : 1;  /* [3] */
        unsigned int tx_hdcp1x_srst_req : 1;  /* [4] */
        unsigned int tx_phy_srst_req    : 1;  /* [5] */
        unsigned int tx_aud_srst_req    : 1;  /* [6] */
        unsigned int tx_acr_srst_req    : 1;  /* [7] */
        unsigned int tx_afifo_srst_req  : 1;  /* [8] */
        unsigned int tx_hdcp2x_srst_req : 1;  /* [9] */
        unsigned int tx_mcu_srst_req    : 1;  /* [10] */
        unsigned int rsv_0              : 21; /* [31:11] */
    } bits;
    unsigned int u32;
} tx_pwd_rst_ctrl;

typedef union {
    struct {
        unsigned int pwd_fifo_data_out : 8;  /* [7:0] */
        unsigned int rsv_5             : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} pwd_fifo_rdata;

typedef union {
    struct {
        unsigned int pwd_fifo_data_in : 8;  /* [7:0] */
        unsigned int rsv_6            : 24; /* [31:8] */
    } bits;

    unsigned int u32;
} pwd_fifo_wdata;

typedef union {
    struct {
        unsigned int pwd_fifo_data_cnt : 5;  /* [4:0] */
        unsigned int rsv_7             : 3;  /* [7:5] */
        unsigned int pwd_data_out_cnt  : 10; /* [17:8] */
        unsigned int rsv_8             : 14; /* [31:18] */
    } bits;
    unsigned int u32;
} pwd_data_cnt;

typedef union {
    struct {
        unsigned int pwd_slave_addr   : 8; /* [7:0] */
        unsigned int pwd_slave_offset : 8; /* [15:8] */
        unsigned int pwd_slave_seg    : 8; /* [23:16] */
        unsigned int rsv_9            : 8; /* [31:24] */
    } bits;
    unsigned int u32;
} pwd_slave_cfg;

typedef union {
    struct {
        unsigned int pwd_i2c_no_ack     : 1;  /* [0] */
        unsigned int pwd_i2c_bus_low    : 1;  /* [1] */
        unsigned int pwd_i2c_in_prog    : 1;  /* [2] */
        unsigned int pwd_fifo_wr_in_use : 1;  /* [3] */
        unsigned int pwd_fifo_rd_in_use : 1;  /* [4] */
        unsigned int pwd_fifo_empty     : 1;  /* [5] */
        unsigned int pwd_fifo_half_full : 1;  /* [6] */
        unsigned int pwd_fifo_full      : 1;  /* [7] */
        unsigned int rsv_10             : 24; /* [31:8] */
    } bits;
    unsigned int u32;
} pwd_mst_state;

typedef union {
    struct {
        unsigned int pwd_mst_cmd : 4;  /* [3:0] */
        unsigned int rsv_11      : 28; /* [31:4] */
    } bits;
    unsigned int u32;
} pwd_mst_cmd;

typedef union {
    struct {
        unsigned int cpu_ddc_req : 1;  /* [0] */
        unsigned int rsv_14      : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} ddc_mst_arb_req;

typedef union {
    struct {
        unsigned int cpu_ddc_req_ack : 1;  /* [0] */
        unsigned int rsv_15          : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} ddc_mst_arb_ack;

typedef struct {
    unsigned int             reserved_0[4]; /* 0-C */
    volatile tx_pwd_rst_ctrl pwd_rst_ctrl;  /* 10 */
    unsigned int             reserved_1[9]; /* 14-2c */
    volatile pwd_fifo_rdata  fifo_rdata;    /* 38 */
    volatile pwd_fifo_wdata  fifo_wdata;    /* 3C */
    volatile pwd_data_cnt    data_cnt;      /* 40 */
    volatile pwd_slave_cfg   slave_cfg;     /* 44 */
    volatile pwd_mst_state   mst_state;     /* 48 */
    volatile pwd_mst_cmd     mst_cmd;       /* 4C */
    unsigned int             reserved_2[6]; /* 50-64 */
    volatile ddc_mst_arb_req ddc_mst_req;   /* 68 */
    volatile ddc_mst_arb_ack ddc_mst_ack;   /* 6C */
} tx_ctrl_regs;

int hdmi_tx_ctrl_regs_init(void);
hi_void hdmi_tx_ctrl_regs_deinit(void);
hi_void hdmi_pwd_tx_afifo_srst_req_set(unsigned int tx_afifo_srst_req);
hi_void hdmi_pwd_tx_acr_srst_req_set(unsigned int tx_acr_srst_req);
hi_void hdmi_pwd_tx_aud_srst_req_set(unsigned int tx_aud_srst_req);
hi_void hdmi_pwd_tx_hdmi_srst_req_set(unsigned int tx_hdmi_srst_req);
hi_void hdmi_pwd_fifo_data_in_set(unsigned int pwd_fifo_data_in);
hi_void hdmi_pwd_data_out_cnt_set(unsigned int pwd_data_out_cnt);
hi_void hdmi_pwd_slave_addr_set(unsigned int pwd_slave_addr);
hi_void hdmi_pwd_slave_offset_set(unsigned int pwd_slave_offset);
hi_void hdmi_pwd_slave_seg_set(unsigned int pwd_slave_seg);
hi_void hdmi_pwd_mst_cmd_set(unsigned int cmd);
hi_void hdmi_ddc_cpu_ddc_req_set(unsigned int cpu_ddc_req);
int hdmi_pwd_fifo_data_out_get(void);
int hdmi_pwd_fifo_data_cnt_get(void);
int hdmi_pwd_i2c_in_prog_get(void);
int hdmi_pwd_fifo_empty_get(void);
int hdmi_ddc_cpu_ddc_req_ack_get(void);
#endif /* __HDMI_REG_CTRL_H__ */

