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
 * Description: jpegd register header file.
 */
#ifndef __JPEGD_REG_H__
#define __JPEGD_REG_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

/* Define the union U_JPEG_DEC_START */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jpeg_dec_start : 1; /* [0]  */
        unsigned int rst_busy : 1; /* [1]  */
        unsigned int axi_sep_bypass : 1; /* [2]  */
        unsigned int reserved_0 : 1; /* [3]  */
        unsigned int axi_sep_typ : 1; /* [4]  */
        unsigned int reserved_1 : 27; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_JPEG_DEC_START;

/* Define the union U_JPEG_RESUME_START */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jpeg_resume_start : 1;  /* [0] */
        unsigned int last_resume_in_pic : 1;  /* [1] */
        unsigned int reserved : 30;  /* [31..2] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_JPEG_RESUME_START;

/* Define the union U_JPEG_STRIDE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int y_stride : 16;  /* [15..0] */
        unsigned int uv_stride : 16;  /* [31..16] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_JPEG_STRIDE;

/* Define the union U_PICTURE_SIZE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int pic_width_in_mcu : 12;  /* [11..0] */
        unsigned int reserved_0 : 4;  /* [15..12] */
        unsigned int pic_height_in_mcu : 12;  /* [27..16] */
        unsigned int reserved_1 : 4;  /* [31..28] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PICTURE_SIZE;

/* Define the union PICTURE_TYPE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int pic_type : 3;  /* [2..0] */
        unsigned int reserved : 29;  /* [31..3] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PICTURE_TYPE;

/* Define the union U_RGB_OUT_STRIDE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jdo_out_stride : 16;  /* [15..0] */
        unsigned int reserved : 16;  /* [31..16] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_RGB_OUT_STRIDE;

/* Define the union U_PD_SUM_CFG_CBCR */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jvld_pd_cb : 16;  /* [15..0] */
        unsigned int jcfg2jvld_pd_cr : 16;  /* [31..16] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PD_SUM_CFG_CBCR;

/* Define the union U_PD_SUM_CFG_Y */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jvld_pd_y : 16;  /* [15..0] */
        unsigned int jcfg2jbs_flag_cur : 1;  /* [16] */
        unsigned int reserved : 15;  /* [31..17] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PD_SUM_CFG_Y;

/* Define the union U_FREQ_SCALE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int freq_scale : 2; /* [1..0]  */
        unsigned int jidct_emar_en : 1; /* [2] */
        unsigned int ck_gt_en : 1; /* [3]  */
        unsigned int outstanding : 4; /* [7..4]  */
        unsigned int axi_id : 4; /* [11..8] */
        unsigned int reserved : 20; /* [31..12] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_FREQ_SCALE;

/* Define the union U_OUT_TYPE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int out_rgb_type_old : 2; /* [1..0]  */
        unsigned int jidct_yuv420_en : 1; /* [2]  */
        unsigned int hor_med_en : 1; /* [3]  */
        unsigned int ver_med_en : 1; /* [4]  */
        unsigned int dither_en : 1; /* [5]  */
        unsigned int reserved_0 : 2; /* [7..6]  */
        unsigned int out_rgb_type : 3; /* [10..8]  */
        unsigned int reserved_1 : 21; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_OUT_TYPE;

/* Define the union U_JPGE_ALPHA; */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jpgd_a : 8;  /* [7..0] */
        unsigned int reserved : 24;  /* [31..8] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_JPGD_ALPHA;

/* Define the union U_HOR_PHASE0_COEF01 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase0_coef0 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase0_coef1 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE0_COEF01;

/* Define the union U_HOR_PHASE0_COEF23 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase0_coef2 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase0_coef3 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE0_COEF23;

/* Define the union U_HOR_PHASE0_COEF45 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase0_coef4 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase0_coef5 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE0_COEF45;

/* Define the union U_HOR_PHASE0_COEF67 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase0_coef6 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase0_coef7 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE0_COEF67;

/* Define the union U_HOR_PHASE2_COEF01 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase2_coef0 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase2_coef1 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE2_COEF01;

/* Define the union U_HOR_PHASE2_COEF23 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase2_coef2 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase2_coef3 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE2_COEF23;

/* Define the union U_HOR_PHASE2_COEF45 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase2_coef4 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase2_coef5 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE2_COEF45;

/* Define the union U_HOR_PHASE2_COEF67 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hor_phase2_coef6 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int hor_phase2_coef7 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HOR_PHASE2_COEF67;

/* Define the union U_VER_PHASE0_COEF01 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int ver_phase0_coef0 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int ver_phase0_coef1 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_VER_PHASE0_COEF01;

/* Define the union U_VER_PHASE0_COEF23 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int ver_phase0_coef2 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int ver_phase0_coef3 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_VER_PHASE0_COEF23;

/* Define the union U_VER_PHASE2_COEF01 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int ver_phase2_coef0 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int ver_phase2_coef1 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_VER_PHASE2_COEF01;

/* Define the union U_VER_PHASE2_COEF23 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int ver_phase2_coef2 : 10;  /* [9..0] */
        unsigned int reserved_0 : 6;  /* [15..10] */
        unsigned int ver_phase2_coef3 : 10;  /* [25..16] */
        unsigned int reserved_1 : 6;  /* [31..26] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_VER_PHASE2_COEF23;

/* Define the union U_CSC_IN_DC_COEF */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_in_dc_coef0 : 9;  /* [8..0] */
        unsigned int reserved_0 : 1;  /* [9] */
        unsigned int csc_in_dc_coef1 : 9;  /* [18..10] */
        unsigned int reserved_1 : 1;  /* [19] */
        unsigned int csc_in_dc_coef2 : 9;  /* [28..20] */
        unsigned int reserved_2 : 3;  /* [31..29] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_IN_DC_COEF;

/* Define the union U_CSC_OUT_DC_COEF */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_out_dc_coef0 : 9;  /* [8..0] */
        unsigned int reserved_0 : 1;  /* [9] */
        unsigned int csc_out_dc_coef1 : 9;  /* [18..10] */
        unsigned int reserved_1 : 1;  /* [19] */
        unsigned int csc_out_dc_coef2 : 9;  /* [28..20] */
        unsigned int reserved_2 : 3;  /* [31..29] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_OUT_DC_COEF;

/* Define the union U_CSC_TRANS_COEF0 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_p_00 : 15;  /* [14..0] */
        unsigned int reserved_0 : 1;  /* [15] */
        unsigned int csc_p_01 : 15;  /* [30..16] */
        unsigned int reserved_1 : 1;  /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_TRANS_COEF0;

/* Define the union U_CSC_TRANS_COEF1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_p_02 : 15;  /* [14..0] */
        unsigned int reserved_0 : 1;  /* [15] */
        unsigned int csc_p_10 : 15;  /* [30..16] */
        unsigned int reserved_1 : 1;  /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_TRANS_COEF1;

/* Define the union U_CSC_TRANS_COEF2 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_p_11 : 15;  /* [14..0] */
        unsigned int reserved_0 : 1;  /* [15] */
        unsigned int csc_p_12 : 15;  /* [30..16] */
        unsigned int reserved_1 : 1;  /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_TRANS_COEF2;

/* Define the union U_CSC_TRANS_COEF3 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_p_20 : 15;  /* [14..0] */
        unsigned int reserved_0 : 1;  /* [15] */
        unsigned int csc_p_21 : 15;  /* [30..16] */
        unsigned int reserved_1 : 1;  /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_TRANS_COEF3;

/* Define the union U_CSC_TRANS_COEF4 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int csc_p_22 : 15;  /* [14..0] */
        unsigned int reserved : 17;  /* [31..15] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_CSC_TRANS_COEF4;

/* Define the union U_MCU_PRO_STARTPOS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jvld_mcu_starty : 12;  /* [11..0] */
        unsigned int reserved : 20;  /* [31..12] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_MCU_PRO_STARTPOS;

/* Define the union U_PICCUT_STARTPOS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jytr_pic_startx : 15; /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int jcfg2jytr_pic_starty : 15; /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PICCUT_STARTPOS;

/* Define the union U_PICCUT_ENDPOS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jytr_pic_endx : 15; /* [14..0]  */
        unsigned int reserved_0 : 1; /* [15]  */
        unsigned int jcfg2jytr_pic_endy : 15; /* [30..16]  */
        unsigned int reserved_1 : 1; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PICCUT_ENDPOS;

/* Define the union U_MCU_PRO_CURPOS */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jvld2jcfg_mcu_y : 12;  /* [11..0] */
        unsigned int reserved : 20;  /* [31..12] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_MCU_PRO_CURPOS;

/* Define the union U_BS_RES_BIT_CFG */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jbs_bs_remain : 7;  /* [6..0] */
        unsigned int reserved : 25;  /* [31..7] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_BS_RES_BIT_CFG;

/* Define the union U_JPEG_INT */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int int_dec_fnsh : 1;  /* [0] */
        unsigned int int_dec_err : 1;  /* [1] */
        unsigned int int_bs_res : 1;  /* [2] */
        unsigned int debug_state : 1;  /* [3] */
        unsigned int int_over_time : 1;  /* [4] */
        unsigned int reserved : 27;  /* [31..5] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_JPEG_INT;

/* Define the union U_INT_MASK */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int intm_dec_fnsh : 1;  /* [0] */
        unsigned int intm_dec_err : 1;  /* [1] */
        unsigned int intm_bs_res : 1;  /* [2] */
        unsigned int reserved_0 : 1;  /* [3] */
        unsigned int intm_over_time : 1;  /* [4] */
        unsigned int reserved_1 : 27;  /* [31..5] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_INT_MASK;

/* Define the union U_PD_SUM_Y */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jvld2jcfg_pd_y : 16;  /* [15..0] */
        unsigned int jbs2jcfg_flag_cur : 1;  /* [16] */
        unsigned int reserved : 15;  /* [31..17] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PD_SUM_Y;

/* Define the union U_PD_SUM_CBCR */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jvld2jcfg_pd_cb : 16;  /* [15..0] */
        unsigned int jvld2jcfg_pd_cr : 16;  /* [31..16] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PD_SUM_CBCR;

/* Define the union U_LUMA_PIX_SUM1 */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int luma_pix_sum1 : 4;  /* [3..0] */
        unsigned int reserved : 27;  /* [30..4] */
        unsigned int jidct_luma_sum_en : 1;  /* [31] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_LUMA_PIX_SUM1;

/* Define the union U_AXI_4K_CNT */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int wr_over_4k_cnt : 16;  /* [15..0] */
        unsigned int rd_over_4k_cnt : 16;  /* [31..16] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_AXI_4K_CNT;

/* Define the union U_AXI_16M_CNT */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int wr_over_16m_cnt : 16;  /* [15..0] */
        unsigned int rd_over_16m_cnt : 16;  /* [31..16] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_AXI_16M_CNT;

/* Define the union U_SAMPLING_FACTOR */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int v_fac : 8;  /* [7..0] */
        unsigned int u_fac : 8;  /* [15..8] */
        unsigned int y_fac : 8;  /* [23..16] */
        unsigned int reserved : 8;  /* [31..24] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_SAMPLING_FACTOR;

/* Define the union U_DRI */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jvld_ri : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_DRI;

/* Define the union U_DRI_CNT_CFG */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jcfg2jvld_dri_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_DRI_CNT_CFG;

/* Define the union U_DRI_CNT */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int jvld2jcfg_dri_cnt : 16; /* [15..0]  */
        unsigned int reserved_0 : 16; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_DRI_CNT;

/* Define the union U_MEM_CTRL */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int mem_ctrl_rfs : 16; /* [15..0]  */
        unsigned int mem_ctrl_rft : 16; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_MEM_CTRL;

/* Define the union U_BITBUFFER_STADDR_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int bb_staddr_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_BITBUFFER_STADDR_MSB;

/* Define the union U_BITBUFFER_ENDADDR_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int bb_endaddr_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_BITBUFFER_ENDADDR_MSB;

/* Define the union U_BITSTREAM_STADDR_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int bs_staddr_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_BITSTREAMS_STADDR_MSB;

/* Define the union U_BITSTREAM_ENDADDR_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int bs_endaddr_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_BITSTREAMS_ENDADDR_MSB;

/* Define the union U_PICTURE_YSTADDR_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int pic_ystaddr_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PICTURE_YSTADDR_MSB;

/* Define the union U_PICTURE_UVSTADDR_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int pic_uvstaddr_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_PICTURE_UVSTADDR_MSB;

/* Define the union U_MTN_ADDRESS0_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int mtn_address0_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_MTN_ADDRESS0_MSB;

/* Define the union U_MTN_ADDRESS1_MSB */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int mtn_address1_msb : 2; /* [1..0]  */
        unsigned int reserved_0 : 30; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_MTN_ADDRESS1_MSB;

/* Define the union U_QUANT_TABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int qtab_y : 8;  /* [7..0] */
        unsigned int qtab_cb : 8;  /* [15..8] */
        unsigned int qtab_cr : 8;  /* [23..16] */
        unsigned int reserved : 8;  /* [31..24] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_QUANT_TABLE;

/* Define the union U_HDC_TABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hdc_lu : 12;  /* [11..0] */
        unsigned int hdc_ch : 12;  /* [23..12] */
        unsigned int reserved : 8;  /* [31..24] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HDC_TABLE;

/* Define the union U_HAC_MIN_TABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hac_lu_mincode_even : 8;  /* [7..0] */
        unsigned int hac_lu_mincode_odd : 8;  /* [15..8] */
        unsigned int hac_ch_mincode_even : 8;  /* [23..16] */
        unsigned int hac_ch_mincode_odd : 8;  /* [31..24] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HAC_MIN_TABLE;

/* Define the union U_HAC_BASE_TABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int hac_lu_base_even : 8;  /* [7..0] */
        unsigned int hac_lu_base_odd : 8;  /* [15..8] */
        unsigned int hac_ch_base_even : 8;  /* [23..16] */
        unsigned int hac_ch_base_odd : 8;  /* [31..24] */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HAC_BASE_TABLE;

/* Define the union U_HAC_SYMBOL_TABLE */
typedef union {
    /* Define the struct bits */
    struct {
        unsigned int sel2_chn_wr : 8; /* [7..0]  */
        unsigned int sel1_chn_wr : 8; /* [15..8]  */
        unsigned int sel2_chn_rd : 8; /* [23..16]  */
        unsigned int reserved_0 : 8; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int u32;
} U_HAC_SYMBOL_TABLE;

/* Define the global struct */
typedef struct {
    volatile U_JPEG_DEC_START JPEG_DEC_START;  /* 0x00 */
    volatile U_JPEG_RESUME_START JPEG_RESUME_START;  /* 0x04 */
    volatile unsigned int PIC_VLD_NUM;  /* 0x08 */
    volatile U_JPEG_STRIDE JPEG_STRIDE;  /* 0x0c */
    volatile U_PICTURE_SIZE PICTURE_SIZE;  /* 0x10 */
    volatile U_PICTURE_TYPE PICTURE_TYPE;  /* 0x14 */
    volatile unsigned int PICDEC_TIME;  /* 0x18 */
    volatile U_RGB_OUT_STRIDE RGB_OUT_STRIDE;  /* 0x1c */
    volatile unsigned int BITBUFFER_STADDR_LSB;  /* 0x20 */
    volatile unsigned int BITBUFFER_ENDADDR_LSB;  /* 0x24 */
    volatile unsigned int BITSTREAMS_STADDR_LSB;  /* 0x28 */
    volatile unsigned int BITSTREAMS_ENDADDR_LSB;  /* 0x2C */
    volatile unsigned int PICTURE_YSTADDR_LSB;  /* 0x30 */
    volatile unsigned int PICTURE_UVSTADDR_LSB;
    volatile U_PD_SUM_CFG_CBCR PD_SUM_CFG_CBCR;
    volatile U_PD_SUM_CFG_Y PD_SUM_CFG_Y;
    volatile U_FREQ_SCALE FREQ_SCALE;  /* 0x40 */
    volatile U_OUT_TYPE OUT_TYPE;
    volatile U_JPGD_ALPHA JPGD_ALPHA;
    volatile U_HOR_PHASE0_COEF01 HOR_PHASE0_COEF01;  /* 0x4c */
    volatile U_HOR_PHASE0_COEF23 HOR_PHASE0_COEF23;  /* 0x50 */
    volatile U_HOR_PHASE0_COEF45 HOR_PHASE0_COEF45;  /* 0x54 */
    volatile U_HOR_PHASE0_COEF67 HOR_PHASE0_COEF67;  /* 0x58 */
    volatile unsigned int RESERVED0[4];  /* 0x5c 0x60 0x64 0x68 */
    volatile U_HOR_PHASE2_COEF01 HOR_PHASE2_COEF01;  /* 0x6c */
    volatile U_HOR_PHASE2_COEF23 HOR_PHASE2_COEF23;  /* 0x70 */
    volatile U_HOR_PHASE2_COEF45 HOR_PHASE2_COEF45;  /* 0x74 */
    volatile U_HOR_PHASE2_COEF67 HOR_PHASE2_COEF67;  /* 0x78 */
    volatile unsigned int RESERVED1[4];  /* 0x7c 0x80 0x84 0x88 */
    volatile U_VER_PHASE0_COEF01 VER_PHASE0_COEF01;  /* 0x8C */
    volatile U_VER_PHASE0_COEF23 VER_PHASE0_COEF23;  /* 0x90 */
    volatile unsigned int RESERVED2[2];  /* 2:0x94 0x98 */
    volatile U_VER_PHASE2_COEF01 VER_PHASE2_COEF01;  /* 0x9c */
    volatile U_VER_PHASE2_COEF23 VER_PHASE2_COEF23;  /* 0xA0 */
    volatile unsigned int RESERVED3[2];  /* 2:0xA4 0xA8 */
    volatile U_CSC_IN_DC_COEF CSC_IN_DC_COEF;  /* 0xAC */
    volatile U_CSC_OUT_DC_COEF CSC_OUT_DC_COEF;  /* 0xB0 */
    volatile U_CSC_TRANS_COEF0 CSC_TRANS_COEF0;  /* 0xB4 */
    volatile U_CSC_TRANS_COEF1 CSC_TRANS_COEF1;  /* 0xB8 */
    volatile U_CSC_TRANS_COEF2 CSC_TRANS_COEF2;  /* 0xBC */
    volatile U_CSC_TRANS_COEF3 CSC_TRANS_COEF3;  /* 0xC0 */
    volatile U_CSC_TRANS_COEF4 CSC_TRANS_COEF4;  /* 0xC4 */
    volatile unsigned int MTN_ADDRESS0_LSB;  /* 0xC8 */
    volatile unsigned int MTN_ADDRESS1_LSB;  /* 0xCC */
    volatile unsigned int RESERVED4;  /* 0xD0 */
    volatile U_MCU_PRO_STARTPOS MCU_PRO_STARTPOS;  /* 0xD4 */
    volatile U_PICCUT_STARTPOS PICCUT_STARTPOS;  /* 0xD8 */
    volatile U_PICCUT_ENDPOS PICCUT_ENDPOS;  /* 0xDC */
    volatile U_MCU_PRO_CURPOS MCU_PRO_CURPOS;  /* 0xE0 */
    volatile unsigned int BS_CONSU;  /* 0xE4 */
    volatile unsigned int BS_RESUME_DATA0;  /* 0xE8 */
    volatile unsigned int BS_RESUME_DATA1;  /* 0xEC */
    volatile unsigned int BS_RESUME_BIT;  /* 0xF0 */
    volatile unsigned int BS_RES_DATA_CFG0;  /* 0xF4 */
    volatile unsigned int BS_RES_DATA_CFG1;  /* 0xF8 */
    volatile U_BS_RES_BIT_CFG BS_RES_BIT_CFG;  /* 0xFC */
    volatile U_JPEG_INT JPEG_INT;  /* 0x100 */
    volatile U_INT_MASK INT_MASK;  /* 0x104 */
    volatile unsigned int OVER_TIME_THD;  /* 0x108 */
    volatile U_PD_SUM_Y PD_SUM_Y;  /* 0x10C */
    volatile U_PD_SUM_CBCR PD_SUM_CBCR;  /* 0x110 */
    volatile unsigned int LUMA_PIX_SUM0;  /* 0x114 */
    volatile U_LUMA_PIX_SUM1 LUMA_PIX_SUM1;  /* 0x118 */
    volatile U_AXI_4K_CNT AXI_4K_CNT;  /* 0x11C */
    volatile U_AXI_16M_CNT AXI_16M_CNT;  /* 0x120 */
    volatile U_SAMPLING_FACTOR SAMPLING_FACTOR;  /* 0x124 */
    volatile U_DRI DRI; /* 0x128 */
    volatile U_DRI_CNT_CFG DRI_CNT_CFG; /* 0x12c */
    volatile U_DRI_CNT DRI_CNT; /* 0x130 */
    volatile unsigned int RESERVED5[3];  /* 0x134 0x138    0x13c */
    volatile U_MEM_CTRL MEM_CTRL; /* 0x140 */
    volatile unsigned int RESERVED6; /* 0x144 */
    volatile U_BITBUFFER_STADDR_MSB BITBUFFER_STADDR_MSB; /* 0x148 */
    volatile U_BITBUFFER_ENDADDR_MSB BITBUFFER_ENDADDR_MSB; /* 0x14c */
    volatile U_BITSTREAMS_STADDR_MSB BITSTREAMS_STADDR_MSB; /* 0x150 */
    volatile U_BITSTREAMS_ENDADDR_MSB BITSTREAMS_ENDADDR_MSB; /* 0x154 */
    volatile U_PICTURE_YSTADDR_MSB PICTURE_YSTADDR_MSB; /* 0x158 */
    volatile U_PICTURE_UVSTADDR_MSB PICTURE_UVSTADDR_MSB; /* 0x15c */
    volatile U_MTN_ADDRESS0_MSB MTN_ADDRESS0_MSB; /* 0x160 */
    volatile U_MTN_ADDRESS1_MSB MTN_ADDRESS1_MSB; /* 0x164 */
    volatile unsigned int RESERVED7[38]; /* 38:0x168~0x1fc */
    volatile U_QUANT_TABLE QUANT_TABLE[64]; /* 64:0x200~0x2fc */
    volatile U_HDC_TABLE HDC_TABLE[12]; /* 12:0x300~0x32c */
    volatile unsigned int RESERVED8[4]; /* 4:0x330~0x33c */
    volatile U_HAC_MIN_TABLE HAC_MIN_TABLE[8]; /* 8:0x340~0x35c */
    volatile U_HAC_BASE_TABLE HAC_BASE_TABLE[8]; /* 8:0x360~0x37c */
    volatile unsigned int RESERVED9[32]; /* 32:0x380~0x3fc */
    volatile unsigned int HAC_SYMBOL_TABLE[176]; /* 176:0x400~0x6c0 */
} S_JPGD_REGS_TYPE;

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif
