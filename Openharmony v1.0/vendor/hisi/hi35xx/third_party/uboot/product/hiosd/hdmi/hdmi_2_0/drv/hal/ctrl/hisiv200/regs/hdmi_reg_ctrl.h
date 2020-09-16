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
        unsigned int reg_vid_bypass_sel : 1;  /* [0] */
        unsigned int reg_rx_frl_sel     : 1;  /* [1] */
        unsigned int flbk_sel           : 1;  /* [2] */
        unsigned int rsv_0              : 29; /* [31:3] */
    } bits;
    unsigned int u32;
} tx_channel_sel;

typedef union {
    struct {
        unsigned int reg_yuv_rgb_cfg : 1;  /* [0] */
        unsigned int rsv_0           : 31; /* [31:1] */
    } bits;
    unsigned int u32;
} yuv_rgb_cfg;

typedef union {
    struct {
        unsigned int tx_pwd_srst_req      : 1; /* [0] */
        unsigned int tx_sys_srst_req      : 1; /* [1] */
        unsigned int tx_vid_srst_req      : 1; /* [2] */
        unsigned int tx_hdmi_srst_req     : 1; /* [3] */
        unsigned int tx_hdcp1x_srst_req   : 1; /* [4] */
        unsigned int tx_phy_srst_req      : 1; /* [5] */
        unsigned int tx_aud_srst_req      : 1; /* [6] */
        unsigned int tx_acr_srst_req      : 1; /* [7] */
        unsigned int tx_afifo_srst_req    : 1; /* [8] */
        unsigned int tx_hdcp2x_srst_req   : 1; /* [9] */
        unsigned int tx_mcu_srst_req      : 1; /* [10] */
        unsigned int frl_soft_arst_req    : 1; /* [11] */
        unsigned int frl_fast_arst_req    : 1; /* [12] */
        unsigned int rsv_0                : 3; /* [15:13] */
        unsigned int vidpath_dout_clk_sel : 1; /* [16] */
        unsigned int vidpath_div4_clk_sel : 1; /* [17] */
        unsigned int hdmi_clk_sel         : 1; /* [18] */
        unsigned int hdmi_clk_div_sel     : 1; /* [19] */
        unsigned int audpath_acr_clk_sel  : 1; /* [20] */
        unsigned int clk_tmds_source_sel  : 1; /* [21] */
        unsigned int clk_frl_source_sel   : 1; /* [22] */
        unsigned int clk_test_out_sel     : 1; /* [23] */
        unsigned int rsv_1                : 8; /* [31:24] */
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
    volatile tx_channel_sel  channel_sel;    /* 00 */
    volatile yuv_rgb_cfg     yuv_rgb;        /* 04 */
    unsigned int             reserved_0[2];  /* 8-C */
    volatile tx_pwd_rst_ctrl tx_rst_ctrl;    /* 10 */
    unsigned int             reserved_1[9];  /* 14-34 */
    volatile pwd_fifo_rdata  pwd_rdata;      /* 38 */
    volatile pwd_fifo_wdata  pwd_wdata;      /* 3C */
    volatile pwd_data_cnt    pwd_cnt;        /* 40 */
    volatile pwd_slave_cfg   pwd_slave;      /* 44 */
    volatile pwd_mst_state   pwd_state;      /* 48 */
    volatile pwd_mst_cmd     pwd_cmd;        /* 4C */
    unsigned int             reserved_2[6];  /* 50-64 */
    volatile ddc_mst_arb_req ddc_arb_req;    /* 68 */
    volatile ddc_mst_arb_ack ddc_arb_ack;    /* 6C */
    unsigned int             reserved_3[49]; /* 70-130 */
} tx_ctrl_reg_type;

int hdmi_tx_ctrl_reg_type_init(void);
hi_void hdmi_tx_ctrl_reg_type_deinit(void);
int hdmi_tx_channel_reg_vid_bypass_sel_set(unsigned int reg_vid_bypass_sel);
int hdmi_tx_channel_reg_vid_bypass_sel_get(void);
int hdmi_yuv_rgb_cfg_reg_set(unsigned int reg_yuv_rgb_cfg);
int hdmi_tx_afifo_srst_req_set(unsigned int tx_afifo_srst_req);
int hdmi_tx_pwd_srst_req_set(unsigned int tx_pwd_srst_req);
int hdmi_tx_acr_srst_req_set(unsigned int tx_acr_srst_req);
int hdmi_tx_hdmi_srst_req_set(unsigned int tx_hdmi_srst_req);
int hdmi_tx_aud_srst_req_set(unsigned int tx_aud_srst_req);
int hdmi_pwd_fifo_wdata_set(unsigned int pwd_fifo_data_in);
int hdmi_pwd_data_out_cnt_set(unsigned int pwd_data_out_cnt);
int hdmi_pwd_slave_addr_set(unsigned int pwd_slave_addr);
int hdmi_pwd_slave_offset_set(unsigned int pwd_slave_offset);
int hdmi_pwd_slave_seg_set(unsigned int pwd_slave_seg);
int hdmi_pwd_mst_cmd_set(unsigned int pwd_cmd);
int hdmi_ddc_mst_arb_req_set(unsigned int cpu_ddc_req);
int hdmi_tx_mcu_srst_req_set(unsigned int tx_mcu_srst_req);
int hdmi_vidpath_dout_clk_sel_set(unsigned int vidpath_dout_clk_sel);
int hdmi_pwd_fifo_rdata_get(void);
int hdmi_pwd_fifo_data_cnt_get(void);
int hdmi_pwd_i2c_in_prog_get(void);
int hdmi_pwd_fifo_empty_get(void);
int hdmi_ddc_mst_arb_ack_cpu_ddc_req_ack_get(void);
unsigned int hdmi_tx_ctrl_read(unsigned int tx_crl_addr);
int hdmi_tx_ctrl_write(unsigned int tx_crl_addr, unsigned int val);
#endif /* __HDMI_REG_CTRL_H__ */

