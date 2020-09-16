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

#ifndef __MIPI_TX_REG_H__
#define __MIPI_TX_REG_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* define the union U_PWR_UP */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int pwr_up : 1;      /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PWR_UP;

/* define the union U_CLKMGR_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int tx_esc_clk_division : 8; /* [7..0]  */
        unsigned int reserved_0 : 8;          /* [15..8]  */
        unsigned int reserved_1 : 16;         /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CLKMGR_CFG;

/* define the union U_VCID */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vcid : 2;        /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VCID;

/* define the union U_COLOR_CODING */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int color_coding : 4; /* [3..0]  */
        unsigned int reserved_0 : 4;   /* [7..4]  */
        unsigned int loosely18_en : 1; /* [8]  */
        unsigned int reserved_1 : 23;  /* [31..9]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_COLOR_CODING;

/* define the union U_LP_CMD_TIM */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int invact_lpcmd_time : 8;  /* [7..0]  */
        unsigned int reserved_0 : 8;         /* [15..8]  */
        unsigned int outvact_lpcmd_time : 8; /* [23..16]  */
        unsigned int reserved_1 : 8;         /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LP_CMD_TIM;

/* define the union U_PCKHDL_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int eotp_tx_en : 1;  /* [0]  */
        unsigned int eotp_rx_en : 1;  /* [1]  */
        unsigned int bta_en : 1;      /* [2]  */
        unsigned int ecc_rx_en : 1;   /* [3]  */
        unsigned int crc_rx_en : 1;   /* [4]  */
        unsigned int reserved_0 : 27; /* [31..5]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PCKHDL_CFG;

/* define the union U_GEN_VCID */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int gen_vcid_rx : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GEN_VCID;

/* define the union U_MODE_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int cmd_video_mode : 1; /* [0]  */
        unsigned int reserved_0 : 31;    /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_MODE_CFG;

/* define the union U_VID_MODE_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_mode_type : 2;    /* [1..0]  */
        unsigned int reserved_0 : 6;       /* [7..2]  */
        unsigned int lp_vsa_en : 1;        /* [8]  */
        unsigned int lp_vbp_en : 1;        /* [9]  */
        unsigned int lp_vfp_en : 1;        /* [10]  */
        unsigned int lp_vact_en : 1;       /* [11]  */
        unsigned int lp_hbp_en : 1;        /* [12]  */
        unsigned int lp_hfp_en : 1;        /* [13]  */
        unsigned int frame_bta_ack_en : 1; /* [14]  */
        unsigned int lp_cmd_en : 1;        /* [15]  */
        unsigned int vpg_en : 1;           /* [16]  */
        unsigned int reserved_1 : 3;       /* [19..17]  */
        unsigned int vpg_mode : 1;         /* [20]  */
        unsigned int reserved_2 : 3;       /* [23..21]  */
        unsigned int vpg_orientation : 1;  /* [24]  */
        unsigned int reserved_3 : 7;       /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_MODE_CFG;

/* define the union U_VID_PKT_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_pkt_size : 14; /* [13..0]  */
        unsigned int reserved_0 : 18;   /* [31..14]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_PKT_SIZE;

/* define the union U_VID_NUM_CHUNKS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_num_chunks : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;     /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_NUM_CHUNKS;

/* define the union U_VID_NULL_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_null_size : 13; /* [12..0]  */
        unsigned int reserved_0 : 19;    /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_NULL_SIZE;

/* define the union U_VID_HSA_TIME */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_hsa_time : 12; /* [11..0]  */
        unsigned int reserved_0 : 20;   /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_HSA_TIME;

/* define the union U_VID_HBP_TIME */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_hbp_time : 12; /* [11..0]  */
        unsigned int reserved_0 : 20;   /* [31..12]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_HBP_TIME;

/* define the union U_VID_HLINE_TIME */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vid_hline_time : 15; /* [14..0]  */
        unsigned int reserved_0 : 17;     /* [31..15]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_HLINE_TIME;

/* define the union U_VID_VSA_LINES */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vsa_lines : 10;  /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_VSA_LINES;

/* define the union U_VID_VBP_LINES */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vbp_lines : 10;  /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_VBP_LINES;

/* define the union U_VID_VFP_LINES */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int vfp_lines : 10;  /* [9..0]  */
        unsigned int reserved_0 : 22; /* [31..10]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_VFP_LINES;

/* define the union U_VID_VACTIVE_LINES */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int v_active_lines : 14; /* [13..0]  */
        unsigned int reserved_0 : 18;     /* [31..14]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_VID_VACTIVE_LINES;

/* define the union U_EDPI_CMD_SIZE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int edpi_allowed_cmd_size : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;            /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_EDPI_CMD_SIZE;

/* define the union U_CMD_MODE_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;      /* [0]  */
        unsigned int reserved_1 : 1;      /* [1]  */
        unsigned int reserved_2 : 6;      /* [7..2]  */
        unsigned int gen_sw_0p_tx : 1;    /* [8]  */
        unsigned int gen_sw_1p_tx : 1;    /* [9]  */
        unsigned int gen_sw_2p_tx : 1;    /* [10]  */
        unsigned int gen_sr_0p_tx : 1;    /* [11]  */
        unsigned int gen_sr_1p_tx : 1;    /* [12]  */
        unsigned int gen_sr_2p_tx : 1;    /* [13]  */
        unsigned int gen_lw_tx : 1;       /* [14]  */
        unsigned int reserved_3 : 1;      /* [15]  */
        unsigned int dcs_sw_0p_tx : 1;    /* [16]  */
        unsigned int dcs_sw_1p_tx : 1;    /* [17]  */
        unsigned int dcs_sr_0p_tx : 1;    /* [18]  */
        unsigned int dcs_lw_tx : 1;       /* [19]  */
        unsigned int reserved_4 : 4;      /* [23..20]  */
        unsigned int max_rd_pkt_size : 1; /* [24]  */
        unsigned int reserved_5 : 7;      /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CMD_MODE_CFG;

/* define the union U_GEN_HDR */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int gen_dt : 6;        /* [5..0]  */
        unsigned int gen_vc : 2;        /* [7..6]  */
        unsigned int gen_wc_lsbyte : 8; /* [15..8]  */
        unsigned int gen_wc_msbyte : 8; /* [23..16]  */
        unsigned int reserved_0 : 8;    /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GEN_HDR;

/* define the union U_GEN_PLD_DATA */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int gen_pld_b1 : 8; /* [7..0]  */
        unsigned int gen_pld_b2 : 8; /* [15..8]  */
        unsigned int gen_pld_b3 : 8; /* [23..16]  */
        unsigned int gen_pld_b4 : 8; /* [31..24]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_GEN_PLD_DATA;

/* define the union U_CMD_PKT_STATUS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int gen_cmd_empty : 1;   /* [0]  */
        unsigned int gen_cmd_full : 1;    /* [1]  */
        unsigned int gen_pld_w_empty : 1; /* [2]  */
        unsigned int gen_pld_w_full : 1;  /* [3]  */
        unsigned int gen_pld_r_empty : 1; /* [4]  */
        unsigned int gen_pld_r_full : 1;  /* [5]  */
        unsigned int gen_rd_cmd_busy : 1; /* [6]  */
        unsigned int reserved_0 : 25;     /* [31..7]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CMD_PKT_STATUS;

/* define the union U_LP_WR_TO_CNT */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lp_wr_to_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16;   /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LP_WR_TO_CNT;

/* define the union U_BTA_TO_CNT */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int bta_to_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_BTA_TO_CNT;

/* define the union U_LPCLK_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_txrequestclkhs : 1; /* [0]  */
        unsigned int auto_clklane_ctrl : 1;  /* [1]  */
        unsigned int reserved_0 : 30;        /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LPCLK_CTRL;

/* define the union U_PHY_TMR_LPCLK_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_clklp2hs_time : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;         /* [15..10]  */
        unsigned int phy_clkhs2lp_time : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;         /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_TMR_LPCLK_CFG;

/* define the union U_PHY_TMR_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_lp2hs_time : 10; /* [9..0]  */
        unsigned int reserved_0 : 6;      /* [15..10]  */
        unsigned int phy_hs2lp_time : 10; /* [25..16]  */
        unsigned int reserved_1 : 6;      /* [31..26]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_TMR_CFG;

/* define the union U_PHY_RSTZ */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_shutdownz : 1; /* [0]  */
        unsigned int phy_rstz : 1;      /* [1]  */
        unsigned int phy_enableclk : 1; /* [2]  */
        unsigned int phy_forcepll : 1;  /* [3]  */
        unsigned int reserved_0 : 28;   /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_RSTZ;

/* define the union U_PHY_IF_CFG */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int n_lanes : 2;            /* [1..0]  */
        unsigned int reserved_0 : 6;         /* [7..2]  */
        unsigned int phy_stop_wait_time : 8; /* [15..8]  */
        unsigned int reserved_1 : 16;        /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_IF_CFG;

/* define the union U_PHY_ULPS_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_txrequlpsclk : 1;  /* [0]  */
        unsigned int phy_txexitulpsclk : 1; /* [1]  */
        unsigned int phy_txrequlpslan : 1;  /* [2]  */
        unsigned int phy_txexitulpslan : 1; /* [3]  */
        unsigned int reserved_0 : 28;       /* [31..4]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_ULPS_CTRL;

/* define the union U_PHY_STATUS */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_lock : 1;               /* [0]  */
        unsigned int phy_direction : 1;          /* [1]  */
        unsigned int phy_stopstateclklane : 1;   /* [2]  */
        unsigned int phy_ulpsactivenotclk : 1;   /* [3]  */
        unsigned int phy_stopstate0lane : 1;     /* [4]  */
        unsigned int phy_ulpsactivenot0lane : 1; /* [5]  */
        unsigned int phy_rxulpsesc0lane : 1;     /* [6]  */
        unsigned int phy_stopstate1lane : 1;     /* [7]  */
        unsigned int phy_ulpsactivenot1lane : 1; /* [8]  */
        unsigned int phy_stopstate2lane : 1;     /* [9]  */
        unsigned int phy_ulpsactivenot2lane : 1; /* [10]  */
        unsigned int phy_stopstate3lane : 1;     /* [11]  */
        unsigned int phy_ulpsactivenot3lane : 1; /* [12]  */
        unsigned int reserved_0 : 19;            /* [31..13]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_STATUS;

/* define the union U_PHY_TST_CTRL0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_testclr : 1; /* [0]  */
        unsigned int phy_testclk : 1; /* [1]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_TST_CTRL0;

/* define the union U_PHY_TST_CTRL1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int phy_testdin : 8;  /* [7..0]  */
        unsigned int phy_testdout : 8; /* [15..8]  */
        unsigned int phy_testen : 1;   /* [16]  */
        unsigned int reserved_0 : 15;  /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_TST_CTRL1;

/* define the union U_INT_ST0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int ack_with_err_0 : 1;  /* [0]  */
        unsigned int ack_with_err_1 : 1;  /* [1]  */
        unsigned int ack_with_err_2 : 1;  /* [2]  */
        unsigned int ack_with_err_3 : 1;  /* [3]  */
        unsigned int ack_with_err_4 : 1;  /* [4]  */
        unsigned int ack_with_err_5 : 1;  /* [5]  */
        unsigned int ack_with_err_6 : 1;  /* [6]  */
        unsigned int ack_with_err_7 : 1;  /* [7]  */
        unsigned int ack_with_err_8 : 1;  /* [8]  */
        unsigned int ack_with_err_9 : 1;  /* [9]  */
        unsigned int ack_with_err_10 : 1; /* [10]  */
        unsigned int ack_with_err_11 : 1; /* [11]  */
        unsigned int ack_with_err_12 : 1; /* [12]  */
        unsigned int ack_with_err_13 : 1; /* [13]  */
        unsigned int ack_with_err_14 : 1; /* [14]  */
        unsigned int ack_with_err_15 : 1; /* [15]  */
        unsigned int dphy_errors_0 : 1;   /* [16]  */
        unsigned int dphy_errors_1 : 1;   /* [17]  */
        unsigned int dphy_errors_2 : 1;   /* [18]  */
        unsigned int dphy_errors_3 : 1;   /* [19]  */
        unsigned int dphy_errors_4 : 1;   /* [20]  */
        unsigned int reserved_0 : 11;     /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INT_ST0;

/* define the union U_INT_ST1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int to_hs_tx : 1;          /* [0]  */
        unsigned int to_lp_rx : 1;          /* [1]  */
        unsigned int ecc_single_err : 1;    /* [2]  */
        unsigned int ecc_multi_err : 1;     /* [3]  */
        unsigned int crc_err : 1;           /* [4]  */
        unsigned int pkt_size_err : 1;      /* [5]  */
        unsigned int eopt_err : 1;          /* [6]  */
        unsigned int dpi_pld_wr_err : 1;    /* [7]  */
        unsigned int gen_cmd_wr_err : 1;    /* [8]  */
        unsigned int gen_pld_wr_err : 1;    /* [9]  */
        unsigned int gen_pld_send_err : 1;  /* [10]  */
        unsigned int gen_pld_rd_err : 1;    /* [11]  */
        unsigned int gen_pld_recev_err : 1; /* [12]  */
        unsigned int reserved_0 : 3;        /* [15..13]  */
        unsigned int vsstart : 1;           /* [16]  */
        unsigned int reserved_1 : 3;        /* [19..17]  */
        unsigned int rxtrigger_0 : 1;       /* [20]  */
        unsigned int rxtrigger_1 : 1;       /* [21]  */
        unsigned int rxtrigger_2 : 1;       /* [22]  */
        unsigned int rxtrigger_3 : 1;       /* [23]  */
        unsigned int hss_abnormal : 1;      /* [24]  */
        unsigned int reserved_2 : 7;        /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INT_ST1;

/* define the union U_INT_MSK0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mask_ack_with_err_0 : 1;  /* [0]  */
        unsigned int mask_ack_with_err_1 : 1;  /* [1]  */
        unsigned int mask_ack_with_err_2 : 1;  /* [2]  */
        unsigned int mask_ack_with_err_3 : 1;  /* [3]  */
        unsigned int mask_ack_with_err_4 : 1;  /* [4]  */
        unsigned int mask_ack_with_err_5 : 1;  /* [5]  */
        unsigned int mask_ack_with_err_6 : 1;  /* [6]  */
        unsigned int mask_ack_with_err_7 : 1;  /* [7]  */
        unsigned int mask_ack_with_err_8 : 1;  /* [8]  */
        unsigned int mask_ack_with_err_9 : 1;  /* [9]  */
        unsigned int mask_ack_with_err_10 : 1; /* [10]  */
        unsigned int mask_ack_with_err_11 : 1; /* [11]  */
        unsigned int mask_ack_with_err_12 : 1; /* [12]  */
        unsigned int mask_ack_with_err_13 : 1; /* [13]  */
        unsigned int mask_ack_with_err_14 : 1; /* [14]  */
        unsigned int mask_ack_with_err_15 : 1; /* [15]  */
        unsigned int mask_dphy_errors_0 : 1;   /* [16]  */
        unsigned int mask_dphy_errors_1 : 1;   /* [17]  */
        unsigned int mask_dphy_errors_2 : 1;   /* [18]  */
        unsigned int mask_dphy_errors_3 : 1;   /* [19]  */
        unsigned int mask_dphy_errors_4 : 1;   /* [20]  */
        unsigned int reserved_0 : 11;          /* [31..21]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INT_MSK0;

/* define the union U_INT_MSK1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int mask_to_hs_tx : 1;          /* [0]  */
        unsigned int mask_to_lp_rx : 1;          /* [1]  */
        unsigned int mask_ecc_single_err : 1;    /* [2]  */
        unsigned int mask_ecc_multi_err : 1;     /* [3]  */
        unsigned int mask_crc_err : 1;           /* [4]  */
        unsigned int mask_pkt_size_err : 1;      /* [5]  */
        unsigned int mask_eopt_err : 1;          /* [6]  */
        unsigned int mask_dpi_pld_wr_err : 1;    /* [7]  */
        unsigned int mask_gen_cmd_wr_err : 1;    /* [8]  */
        unsigned int mask_gen_pld_wr_err : 1;    /* [9]  */
        unsigned int mask_gen_pld_send_err : 1;  /* [10]  */
        unsigned int mask_gen_pld_rd_err : 1;    /* [11]  */
        unsigned int mask_gen_pld_recev_err : 1; /* [12]  */
        unsigned int reserved_0 : 3;             /* [15..13]  */
        unsigned int mask_vsstart : 1;           /* [16]  */
        unsigned int reserved_1 : 3;             /* [19..17]  */
        unsigned int mask_trigger_0 : 1;         /* [20]  */
        unsigned int mask_trigger_1 : 1;         /* [21]  */
        unsigned int mask_trigger_2 : 1;         /* [22]  */
        unsigned int mask_trigger_3 : 1;         /* [23]  */
        unsigned int mask_hss_abnormal : 1;      /* [24]  */
        unsigned int reserved_2 : 7;             /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INT_MSK1;

/* define the union U_PHY_CAL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int txskewcalhs : 1; /* [0]  */
        unsigned int reserved_0 : 31; /* [31..1]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_PHY_CAL;

/* define the union U_INT_FORCE1 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;  /* [0]  */
        unsigned int reserved_1 : 1;  /* [1]  */
        unsigned int reserved_2 : 1;  /* [2]  */
        unsigned int reserved_3 : 1;  /* [3]  */
        unsigned int reserved_4 : 1;  /* [4]  */
        unsigned int reserved_5 : 1;  /* [5]  */
        unsigned int reserved_6 : 1;  /* [6]  */
        unsigned int reserved_7 : 1;  /* [7]  */
        unsigned int reserved_8 : 1;  /* [8]  */
        unsigned int reserved_9 : 1;  /* [9]  */
        unsigned int reserved_10 : 1; /* [10]  */
        unsigned int reserved_11 : 1; /* [11]  */
        unsigned int reserved_12 : 1; /* [12]  */
        unsigned int reserved_13 : 3; /* [15..13]  */
        unsigned int reserved_14 : 1; /* [16]  */
        unsigned int reserved_15 : 3; /* [19..17]  */
        unsigned int reserved_16 : 1; /* [20]  */
        unsigned int reserved_17 : 1; /* [21]  */
        unsigned int reserved_18 : 1; /* [22]  */
        unsigned int reserved_19 : 1; /* [23]  */
        unsigned int reserved_20 : 1; /* [24]  */
        unsigned int reserved_21 : 7; /* [31..25]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_INT_FORCE1;

/* define the union U_OPERATION_MODE */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 1;          /* [0]  */
        unsigned int mem_ck_en : 1;           /* [1]  */
        unsigned int reserved_1 : 2;          /* [3..2]  */
        unsigned int reserved_2 : 1;          /* [4]  */
        unsigned int init_skew_en : 1;        /* [5]  */
        unsigned int period_skew_en : 1;      /* [6]  */
        unsigned int reserved_3 : 1;          /* [7]  */
        unsigned int reserved_4 : 1;          /* [8]  */
        unsigned int reserved_5 : 1;          /* [9]  */
        unsigned int reserved_6 : 1;          /* [10]  */
        unsigned int reserved_7 : 1;          /* [11]  */
        unsigned int reserved_8 : 1;          /* [12]  */
        unsigned int reserved_9 : 1;          /* [13]  */
        unsigned int reserved_10 : 1;         /* [14]  */
        unsigned int reserved_11 : 1;         /* [15]  */
        unsigned int read_empty_vsync_en : 1; /* [16]  */
        unsigned int reserved_12 : 1;         /* [17]  */
        unsigned int buf_clr_en : 1;          /* [18]  */
        unsigned int reserved_13 : 1;         /* [19]  */
        unsigned int hss_abnormal_rst : 1;    /* [20]  */
        unsigned int reserved_14 : 3;         /* [23..21]  */
        unsigned int reserved_15 : 1;         /* [24]  */
        unsigned int reserved_16 : 1;         /* [25]  */
        unsigned int reserved_17 : 1;         /* [26]  */
        unsigned int reserved_18 : 1;         /* [27]  */
        unsigned int reserved_19 : 3;         /* [30..28]  */
        unsigned int input_en : 1;            /* [31]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_OPERATION_MODE;

/* define the union U_V_H_SEND */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int h_send : 16; /* [15..0]  */
        unsigned int v_send : 16; /* [31..16]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_V_H_SEND;

/* define the union U_DATATYPE0 */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int reserved_0 : 6; /* [5..0]  */
        unsigned int reserved_1 : 2; /* [7..6]  */
        unsigned int dt_hss : 6;     /* [13..8]  */
        unsigned int reserved_2 : 2; /* [15..14]  */
        unsigned int dt_vse : 6;     /* [21..16]  */
        unsigned int reserved_3 : 2; /* [23..22]  */
        unsigned int dt_vss : 6;     /* [29..24]  */
        unsigned int reserved_4 : 2; /* [31..30]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_DATATYPE0;

/* define the union U_CSI_CTRL */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int csi_en : 1;      /* [0]  */
        unsigned int reserved_0 : 3;  /* [3..1]  */
        unsigned int reserved_1 : 1;  /* [4]  */
        unsigned int reserved_2 : 3;  /* [7..5]  */
        unsigned int reserved_3 : 1;  /* [8]  */
        unsigned int reserved_4 : 3;  /* [11..9]  */
        unsigned int reserved_5 : 1;  /* [12]  */
        unsigned int reserved_6 : 3;  /* [15..13]  */
        unsigned int reserved_7 : 1;  /* [16]  */
        unsigned int reserved_8 : 15; /* [31..17]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_CSI_CTRL;

/* define the union U_SKEW_BEGIN */
typedef union {
    /* define the struct bits  */
    struct {
        unsigned int skew_begin : 32; /* [31..0]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_SKEW_BEGIN;
/* define the union U_SKEW_END */
typedef union {
    /* define the struct bits  */
    struct {
        unsigned int skew_end : 32; /* [31..0]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_SKEW_END;
/* define the union U_LANE_ID */
typedef union {
    /* define the struct bits */
    struct {
        unsigned int lane0_id : 2;    /* [1..0]  */
        unsigned int reserved_0 : 2;  /* [3..2]  */
        unsigned int lane1_id : 2;    /* [5..4]  */
        unsigned int reserved_1 : 2;  /* [7..6]  */
        unsigned int lane2_id : 2;    /* [9..8]  */
        unsigned int reserved_2 : 2;  /* [11..10]  */
        unsigned int lane3_id : 2;    /* [13..12]  */
        unsigned int reserved_3 : 18; /* [31..14]  */
    } bits;

    /* define an unsigned member */
    unsigned int u32;
} U_LANE_ID;

/* define the global struct */
typedef struct {
    unsigned int reserved_0;               /* 0x0 */
    U_PWR_UP PWR_UP;                       /* 0x4 */
    U_CLKMGR_CFG CLKMGR_CFG;               /* 0x8 */
    U_VCID VCID;                           /* 0xc */
    U_COLOR_CODING COLOR_CODING;           /* 0x10 */
    unsigned int reserved_1;               /* 0x14 */
    U_LP_CMD_TIM LP_CMD_TIM;               /* 0x18 */
    unsigned int reserved_2[4];            /* 0x1c~0x28 */
    U_PCKHDL_CFG PCKHDL_CFG;               /* 0x2c */
    U_GEN_VCID GEN_VCID;                   /* 0x30 */
    U_MODE_CFG MODE_CFG;                   /* 0x34 */
    U_VID_MODE_CFG VID_MODE_CFG;           /* 0x38 */
    U_VID_PKT_SIZE VID_PKT_SIZE;           /* 0x3c */
    U_VID_NUM_CHUNKS VID_NUM_CHUNKS;       /* 0x40 */
    U_VID_NULL_SIZE VID_NULL_SIZE;         /* 0x44 */
    U_VID_HSA_TIME VID_HSA_TIME;           /* 0x48 */
    U_VID_HBP_TIME VID_HBP_TIME;           /* 0x4c */
    U_VID_HLINE_TIME VID_HLINE_TIME;       /* 0x50 */
    U_VID_VSA_LINES VID_VSA_LINES;         /* 0x54 */
    U_VID_VBP_LINES VID_VBP_LINES;         /* 0x58 */
    U_VID_VFP_LINES VID_VFP_LINES;         /* 0x5c */
    U_VID_VACTIVE_LINES VID_VACTIVE_LINES; /* 0x60 */
    U_EDPI_CMD_SIZE EDPI_CMD_SIZE;         /* 0x64 */
    U_CMD_MODE_CFG CMD_MODE_CFG;           /* 0x68 */
    U_GEN_HDR GEN_HDR;                     /* 0x6c */
    U_GEN_PLD_DATA GEN_PLD_DATA;           /* 0x70 */
    U_CMD_PKT_STATUS CMD_PKT_STATUS;       /* 0x74 */
    unsigned int reserved_3[4];            /* 0x78~0x84 */
    U_LP_WR_TO_CNT LP_WR_TO_CNT;           /* 0x88 */
    U_BTA_TO_CNT BTA_TO_CNT;               /* 0x8c */
    unsigned int reserved_4;               /* 0x90 */
    U_LPCLK_CTRL LPCLK_CTRL;               /* 0x94 */
    U_PHY_TMR_LPCLK_CFG PHY_TMR_LPCLK_CFG; /* 0x98 */
    U_PHY_TMR_CFG PHY_TMR_CFG;             /* 0x9c */
    U_PHY_RSTZ PHY_RSTZ;                   /* 0xa0 */
    U_PHY_IF_CFG PHY_IF_CFG;               /* 0xa4 */
    U_PHY_ULPS_CTRL PHY_ULPS_CTRL;         /* 0xa8 */
    unsigned int reserved_5;               /* 0xac */
    U_PHY_STATUS PHY_STATUS;               /* 0xb0 */
    U_PHY_TST_CTRL0 PHY_TST_CTRL0;         /* 0xb4 */
    U_PHY_TST_CTRL1 PHY_TST_CTRL1;         /* 0xb8 */
    U_INT_ST0 INT_ST0;                     /* 0xbc */
    U_INT_ST1 INT_ST1;                     /* 0xc0 */
    U_INT_MSK0 INT_MSK0;                   /* 0xc4 */
    U_INT_MSK1 INT_MSK1;                   /* 0xc8 */
    U_PHY_CAL PHY_CAL;                     /* 0xcc */
    unsigned int reserved_6[3];            /* 0xd0~0xd8 */
    U_INT_FORCE1 INT_FORCE1;               /* 0xdc */
    unsigned int reserved_7[74];           /* 0xe0~0x204 */
    U_OPERATION_MODE OPERATION_MODE;       /* 0x208 */
    unsigned int reserved_8[6];            /* 0x20c~0x220 */
    U_V_H_SEND V_H_SEND;                   /* 0x224 */
    unsigned int reserved_9[2];            /* 0x228~0x22c */
    U_DATATYPE0 DATATYPE0;                 /* 0x230 */
    unsigned int DATATYPE1;                /* 0x234 */
    U_CSI_CTRL CSI_CTRL;                   /* 0x238 */
    U_SKEW_BEGIN SKEW_BEGIN;               /* 0x23c */
    U_SKEW_END SKEW_END;                   /* 0x240 */
    unsigned int reserved_11[3];           /* 0x244~0x24c */
    U_LANE_ID LANE_ID;                     /* 0x250 */
} mipi_tx_regs_type_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MIPI_TX_REG_H__ */
