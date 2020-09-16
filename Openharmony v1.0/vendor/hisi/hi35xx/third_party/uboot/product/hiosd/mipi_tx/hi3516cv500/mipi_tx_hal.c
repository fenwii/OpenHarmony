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

#include "mipi_tx_hal.h"
#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include "type.h"
#include "mipi_tx_reg.h"

#define MIPI_TX_REGS_ADDR 0x11270000
#define MIPI_TX_REGS_SIZE 0x10000

#define MIPI_TX_CRG 0x1201010C

#define MIPI_TX_REF_CLK 27

#define TLPX                60
#define TCLK_PREPARE        60
#define TCLK_ZERO           250
#define TCLK_TRAIL          80
#define TPRE_DELAY          100
#define THS_PREPARE         80
#define THS_ZERO            180
#define THS_TRAIL           110

/* phy addr */
#define PLL_SET0 0x60
#define PLL_SET1 0x64
#define PLL_SET2 0x65
#ifdef HI_FPGA
#define PLL_SET3 0x17
#endif
#define PLL_SET4 0x66
#define PLL_SET5 0x67

#define DATA0_TPRE_DELAY 0x28
#define DATA1_TPRE_DELAY 0x38
#define DATA2_TPRE_DELAY 0x48
#define DATA3_TPRE_DELAY 0x58

#define CLK_TLPX         0x10
#define CLK_TCLK_PREPARE 0x11
#define CLK_TCLK_ZERO    0x12
#define CLK_TCLK_TRAIL   0x13

#define DATA0_TLPX        0x20
#define DATA0_THS_PREPARE 0x21
#define DATA0_THS_ZERO    0x22
#define DATA0_THS_TRAIL   0x23
#define DATA1_TLPX        0x30
#define DATA1_THS_PREPARE 0x31
#define DATA1_THS_ZERO    0x32
#define DATA1_THS_TRAIL   0x33
#define DATA2_TLPX        0x40
#define DATA2_THS_PREPARE 0x41
#define DATA2_THS_ZERO    0x42
#define DATA2_THS_TRAIL   0x43
#define DATA3_TLPX        0x50
#define DATA3_THS_PREPARE 0x51
#define DATA3_THS_ZERO    0x52
#define DATA3_THS_TRAIL   0x53

#define MIPI_TX_READ_TIMEOUT_CNT 1000
#define MIPI_TX_MAX_RESET_PHY_TIMES 10

#define PREPARE_COMPENSATE    10
#define ROUNDUP_VALUE     7999
#define INNER_PEROID    8000   /* 8 * 1000 ,1000 is 1us = 1000ns, 8 is division ratio */

#define IO_ADDRESS(x) (x)

volatile mipi_tx_regs_type_t *g_mipi_tx_regs_va = HI_NULL;

unsigned int g_actual_phy_data_rate;

static inline void write_reg32(unsigned long addr, unsigned int value, unsigned int mask)
{
    unsigned int t;

    t = readl((void *)(uintptr_t)addr);
    t &= ~mask;
    t |= value & mask;
    writel(t, (void *)(uintptr_t)addr);
}

int mipi_tx_drv_reset_phy(const combo_dev_cfg_t *dev_cfg)
{
    static int count = 0;
    count++;
#if MIPI_TX_DEBUG
    printf("reset phy count ===================================== %d\n", count);
#endif
    /* set phy config */
    mipi_tx_drv_set_phy_cfg(dev_cfg);

    return count;
}

static void set_phy_reg(unsigned int addr, unsigned char value)
{
    /* the numbers are register config, not magic number. */
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL1.u32 = (0x10000 + addr);
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x2;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x0;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL1.u32 = value;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x2;
    isb();
    dsb();
    dmb();
    g_mipi_tx_regs_va->PHY_TST_CTRL0.u32 = 0x0;
    isb();
    dsb();
    dmb();
}

void mipi_tx_pll_status_check(const combo_dev_cfg_t *dev_cfg);

static void mipi_tx_drv_get_phy_clk_prepare(unsigned char *clk_prepare)
{
    unsigned char temp0;
    unsigned char temp1;

    temp0 = ((g_actual_phy_data_rate * TCLK_PREPARE + ROUNDUP_VALUE) / INNER_PEROID - 1 +
            ((g_actual_phy_data_rate * PREPARE_COMPENSATE + ROUNDUP_VALUE) / INNER_PEROID) -
            ((((g_actual_phy_data_rate * TCLK_PREPARE + ROUNDUP_VALUE) / INNER_PEROID +
            ((g_actual_phy_data_rate * PREPARE_COMPENSATE + ROUNDUP_VALUE) / INNER_PEROID)) * INNER_PEROID -
            PREPARE_COMPENSATE * g_actual_phy_data_rate - TCLK_PREPARE * g_actual_phy_data_rate) / INNER_PEROID));
    if (temp0 > 0) {
        temp1 = temp0;
    } else {
        temp1 = 0;
    }

    if (((temp1 + 1) * INNER_PEROID - PREPARE_COMPENSATE * g_actual_phy_data_rate) > /* temp + 1 is next level period */
        94 * g_actual_phy_data_rate) {  /* 94 is the  maximum refer to mipi protocol */
        if (temp0 > 0) {
            *clk_prepare = temp0 - 1;
        } else {
            *clk_prepare = 255; /* set 255 will easy to found mistake */
            printf("err when calc phy timing \n");
        }
    } else {
        if (temp0 > 0) {
            *clk_prepare = temp0;
        } else {
            *clk_prepare = 0; /* 0 register config */
        }
    }
}

static void mipi_tx_drv_get_phy_data_prepare(unsigned char *data_prepare)
{
    unsigned char temp0;
    unsigned char temp1;

    /* DATA_THS_PREPARE */
    temp0 = ((g_actual_phy_data_rate * THS_PREPARE + ROUNDUP_VALUE) / INNER_PEROID - 1 +
            ((g_actual_phy_data_rate * PREPARE_COMPENSATE + ROUNDUP_VALUE) / INNER_PEROID) -
            ((((g_actual_phy_data_rate * THS_PREPARE + ROUNDUP_VALUE) / INNER_PEROID +
            ((g_actual_phy_data_rate * PREPARE_COMPENSATE + ROUNDUP_VALUE) / INNER_PEROID)) * INNER_PEROID -
            PREPARE_COMPENSATE * g_actual_phy_data_rate - THS_PREPARE * g_actual_phy_data_rate) / INNER_PEROID));
    if (temp0 > 0) {
        temp1 = temp0;
    } else {
        temp1 = 0; /* 0 register config */
    }

    if ((g_actual_phy_data_rate > 105) && /* data rate bigger than 105 */
        (((temp1 + 1) * INNER_PEROID - PREPARE_COMPENSATE * g_actual_phy_data_rate) >
        (85 * g_actual_phy_data_rate + 6 * 1000))) {  /* 85 + 6 * 1000 is the maximum in mipi protocol */
        if (temp0 > 0) {
            *data_prepare = temp0 - 1;
        } else {
            *data_prepare = 255; /* set 255 will easy to found mistake */
            printf("err when calc phy timing \n");
        }
    } else {
        if (temp0 > 0) {
            *data_prepare = temp0;
        } else {
            *data_prepare = 0; /* 0 register config */
        }
    }
}

void mipi_tx_drv_set_phy_cfg(const combo_dev_cfg_t *dev_cfg)
{
    unsigned char pll_set0;
    unsigned char pll_set1;
    unsigned char pll_set2;
#ifdef HI_FPGA
    unsigned char pll_set3;
#endif
    unsigned char pll_set4;
    unsigned char pll_set5;

    unsigned char data_tpre_delay;
    unsigned char clk_tlpx;
    unsigned char clk_tclk_prepare;
    unsigned char clk_tclk_zero;
    unsigned char clk_tclk_trail;
    unsigned char data_tlpx;
    unsigned char data_ths_prepare;
    unsigned char data_ths_zero;
    unsigned char data_ths_trail;
    int datarate_clk;
    int pll_ref;
    /* the numbers below are register config, not magic number. */
    /* pll_set0 */
    if (dev_cfg->phy_data_rate > 750) { /* data rate bigger than 750 */
        pll_set0 = 0x0;
    } else if (dev_cfg->phy_data_rate > 375) { /* data rate bigger than 375 */
        pll_set0 = 0x8;
    } else if (dev_cfg->phy_data_rate > 188) { /* data rate bigger than 188 */
        pll_set0 = 0xa;
    } else if (dev_cfg->phy_data_rate > 94) { /* data rate bigger than 94 */
        pll_set0 = 0xc;
    } else {
        pll_set0 = 0xe;
    }
    set_phy_reg(PLL_SET0, pll_set0);

    datarate_clk = (dev_cfg->phy_data_rate + MIPI_TX_REF_CLK - 1) / MIPI_TX_REF_CLK;

    /* the numbers below are register config, not magic number. */
    if (pll_set0 / 2 == 4) { /* 2 4 cal pll */
        pll_ref = 2; /* 2 pll cfg */
    } else if (pll_set0 / 2 == 5) { /* 2 5 cal pll */
        pll_ref = 4; /* 4 pll cfg */
    } else if (pll_set0 / 2 == 6) { /* 2 6 cal pll */
        pll_ref = 8; /* 8 pll cfg */
    } else if (pll_set0 / 2 == 7) { /* 2 7 cal pll */
        pll_ref = 16; /* 16 pll cfg */
    } else {
        pll_ref = 1;
    }
    if ((datarate_clk * pll_ref) % 2) { /* 2 cal pll */
        pll_set1 = 0x10;
        pll_set5 = (datarate_clk * pll_ref - 1) / 2; /* 2 cal pll */
    } else {
        pll_set1 = 0x20;
        pll_set5 = datarate_clk * pll_ref / 2 - 1; /* 2 cal pll */
    }

    set_phy_reg(PLL_SET1, pll_set1);
    pll_set2 = 0x2;
    set_phy_reg(PLL_SET2, pll_set2);
    pll_set4 = 0x0;
    set_phy_reg(PLL_SET4, pll_set4);

#ifdef HI_FPGA
    pll_set3 = 0x1;
    set_phy_reg(PLL_SET3, pll_set3);
#endif

    /* pll_set5 */
    set_phy_reg(PLL_SET5, pll_set5);

    /* DATA0~3 TPRE-DELAY */
    data_tpre_delay = (g_actual_phy_data_rate * TPRE_DELAY + ROUNDUP_VALUE) / INNER_PEROID - 1; /* 1 is compensate */
    set_phy_reg(DATA0_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA1_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA2_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA3_TPRE_DELAY, data_tpre_delay);

    /* CLK_TLPX */
    clk_tlpx = (g_actual_phy_data_rate * TLPX + ROUNDUP_VALUE) / INNER_PEROID - 1;
    set_phy_reg(CLK_TLPX, clk_tlpx);

    /* CLK_TCLK_PREPARE */
    mipi_tx_drv_get_phy_clk_prepare(&clk_tclk_prepare);
    set_phy_reg(CLK_TCLK_PREPARE, clk_tclk_prepare);

    /* CLK_TCLK_ZERO */
    if ((g_actual_phy_data_rate * TCLK_ZERO + ROUNDUP_VALUE) / INNER_PEROID > 4) {  /* 4 is compensate */
        clk_tclk_zero = (g_actual_phy_data_rate * TCLK_ZERO + ROUNDUP_VALUE) / INNER_PEROID - 4; /* 4 is compensate */
    } else {
        clk_tclk_zero = 0;
    }
    set_phy_reg(CLK_TCLK_ZERO, clk_tclk_zero);

    /* CLK_TCLK_TRAIL */
    clk_tclk_trail = (g_actual_phy_data_rate * TCLK_TRAIL + ROUNDUP_VALUE) / INNER_PEROID;
    set_phy_reg(CLK_TCLK_TRAIL, clk_tclk_trail);

    /*
     * DATA_TLPX
     * DATA_THS_PREPARE
     * DATA_THS_ZERO
     * DATA_THS_TRAIL
     */
    data_tlpx = (g_actual_phy_data_rate * TLPX + ROUNDUP_VALUE) / INNER_PEROID - 1;

    mipi_tx_drv_get_phy_data_prepare(&data_ths_prepare);

    if ((g_actual_phy_data_rate * THS_ZERO + ROUNDUP_VALUE) / INNER_PEROID > 4) { /* 4 is compensate */
        data_ths_zero = (g_actual_phy_data_rate * THS_ZERO + ROUNDUP_VALUE) / INNER_PEROID - 4; /* 4 is compensate */
    } else {
        data_ths_zero = 0;
    }

    data_ths_trail = (g_actual_phy_data_rate * THS_TRAIL + ROUNDUP_VALUE) / INNER_PEROID + 1;

    set_phy_reg(DATA0_TLPX, data_tlpx);
    set_phy_reg(DATA0_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA0_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA0_THS_TRAIL, data_ths_trail);
    set_phy_reg(DATA1_TLPX, data_tlpx);
    set_phy_reg(DATA1_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA1_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA1_THS_TRAIL, data_ths_trail);
    set_phy_reg(DATA2_TLPX, data_tlpx);
    set_phy_reg(DATA2_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA2_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA2_THS_TRAIL, data_ths_trail);
    set_phy_reg(DATA3_TLPX, data_tlpx);
    set_phy_reg(DATA3_THS_PREPARE, data_ths_prepare);
    set_phy_reg(DATA3_THS_ZERO, data_ths_zero);
    set_phy_reg(DATA3_THS_TRAIL, data_ths_trail);
    /* the numbers below are register config, not magic number. */
    /* data lp2hs,hs2lp time */
    g_mipi_tx_regs_va->PHY_TMR_CFG.u32 = ((data_ths_trail - 1) << 16) + /* 16 cal cfg */
        data_tpre_delay + data_tlpx + data_ths_prepare + data_ths_zero + 7; /* 7 cal cfg */
    /* clk lp2hs,hs2lp time */
    g_mipi_tx_regs_va->PHY_TMR_LPCLK_CFG.u32 = ((31 + data_ths_trail) << 16) + /* 31 16 cal cfg */
        clk_tlpx + clk_tclk_prepare + clk_tclk_zero + 6; /* 6 cal cfg */
    /* edpi_cmd_size */
    g_mipi_tx_regs_va->EDPI_CMD_SIZE.u32 = 0xF0;

    /* phy enable */
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0xf;

    /* the number is register config, not magic number. */
    if (dev_cfg->output_mode == OUTPUT_MODE_CSI) {
        if (dev_cfg->output_format == OUT_FORMAT_YUV420_8_BIT_NORMAL) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x10218;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x1111;
        } else if (dev_cfg->output_format == OUT_FORMAT_YUV422_8_BIT) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x1021A;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x1111;
        }
    } else {
        if (dev_cfg->output_format == OUT_FORMAT_RGB_16_BIT) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x111213D;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x10100;
        } else if (dev_cfg->output_format == OUT_FORMAT_RGB_18_BIT) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x111213D;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x10100;
        } else if (dev_cfg->output_format == OUT_FORMAT_RGB_24_BIT) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x111213D;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x10100;
        }
    }

    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0XF;

    udelay(1000); /* delay 1000 us */

    g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x0;
}

static void set_output_format(const combo_dev_cfg_t *dev_cfg)
{
    int color_coding = 0;

    if (dev_cfg->output_mode == OUTPUT_MODE_CSI) {
        /* the number is register config, not magic number. */
        if (dev_cfg->output_format == OUT_FORMAT_YUV420_8_BIT_NORMAL) {
            color_coding = 0xd;
        } else if (dev_cfg->output_format == OUT_FORMAT_YUV422_8_BIT) {
            color_coding = 0x1;
        }
    } else {
        /* the number is register config, not magic number. */
        if (dev_cfg->output_format == OUT_FORMAT_RGB_16_BIT) {
            color_coding = 0x0;
        } else if (dev_cfg->output_format == OUT_FORMAT_RGB_18_BIT) {
            color_coding = 0x3;
        } else if (dev_cfg->output_format == OUT_FORMAT_RGB_24_BIT) {
            color_coding = 0x5;
        }
    }

    g_mipi_tx_regs_va->COLOR_CODING.u32 = color_coding;
#ifdef MIPI_TX_DEBUG
    printf("set_output_format: 0x%x\n", color_coding);
#endif
}

static void set_video_mode_cfg(const combo_dev_cfg_t *dev_cfg)
{
    int video_mode;
    /* the numbers below are register config, not magic number. */
    if (dev_cfg->video_mode == NON_BURST_MODE_SYNC_PULSES) {
        video_mode = 0;
    } else if (dev_cfg->video_mode == NON_BURST_MODE_SYNC_EVENTS) {
        video_mode = 1;
    } else {
        video_mode = 2; /* 2 register config */
    }

    if ((dev_cfg->output_mode == OUTPUT_MODE_CSI) || (dev_cfg->output_mode == OUTPUT_MODE_DSI_CMD)) {
        video_mode = 2; /* 2 register config */
    }

    g_mipi_tx_regs_va->VID_MODE_CFG.u32 = 0x3f00 + video_mode;
}

static void set_timing_config(const combo_dev_cfg_t *dev_cfg)
{
    unsigned int hsa_time;
    unsigned int hbp_time;
    unsigned int hline_time;

    if (dev_cfg->pixel_clk == 0) {
        printf("dev_cfg->pixel_clk is 0, illegal.\n");
        return;
    }

    hsa_time = g_actual_phy_data_rate * dev_cfg->sync_info.vid_hsa_pixels * 125 / /* 125 from algorithm */
               dev_cfg->pixel_clk;
    hbp_time = g_actual_phy_data_rate * dev_cfg->sync_info.vid_hbp_pixels * 125 / /* 125 from algorithm */
               dev_cfg->pixel_clk;
    hline_time = g_actual_phy_data_rate * dev_cfg->sync_info.vid_hline_pixels * 125 / /* 125 from algorithm */
                 dev_cfg->pixel_clk;

    g_mipi_tx_regs_va->VID_HSA_TIME.u32 = hsa_time;
    g_mipi_tx_regs_va->VID_HBP_TIME.u32 = hbp_time;
    g_mipi_tx_regs_va->VID_HLINE_TIME.u32 = hline_time;

    g_mipi_tx_regs_va->VID_VSA_LINES.u32 = dev_cfg->sync_info.vid_vsa_lines;
    g_mipi_tx_regs_va->VID_VBP_LINES.u32 = dev_cfg->sync_info.vid_vbp_lines;
    g_mipi_tx_regs_va->VID_VFP_LINES.u32 = dev_cfg->sync_info.vid_vfp_lines;
    g_mipi_tx_regs_va->VID_VACTIVE_LINES.u32 = dev_cfg->sync_info.vid_active_lines;

#ifdef MIPI_TX_DEBUG
    printf("VID_HSA_TIME(0x48): 0x%x\n", hsa_time);
    printf("VID_HBP_TIME(0x4c): 0x%x\n", hbp_time);
    printf("VID_HLINE_TIME(0x50): 0x%x\n", hline_time);
    printf("VID_VSA_LINES(0x54): 0x%x\n", dev_cfg->sync_info.vid_vsa_lines);
    printf("VID_VBP_LINES(0x58): 0x%x\n", dev_cfg->sync_info.vid_vbp_lines);
    printf("VID_VFP_LINES(0x5c): 0x%x\n", dev_cfg->sync_info.vid_vfp_lines);
    printf("VID_VACTIVE_LINES(0x60): 0x%x\n", dev_cfg->sync_info.vid_active_lines);
#endif
}

void set_lane_config(const short lane_id[], unsigned int n)
{
    int lane_num = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (lane_id[i] != -1) {
            lane_num++;
        }
    }

    g_mipi_tx_regs_va->PHY_IF_CFG.u32 = lane_num - 1;
}

void mipi_tx_drv_set_clkmgr_cfg(void)
{
    if (g_actual_phy_data_rate / 160 < 2) { /* 160 cal div, should not samller than 2 */
        g_mipi_tx_regs_va->CLKMGR_CFG.u32 = 0x102; /* 0x102 register config */
    } else {
        g_mipi_tx_regs_va->CLKMGR_CFG.u32 = 0x100 + (g_actual_phy_data_rate + 159) / 160; /* 159 160 cal div */
    }
}

void mipi_tx_drv_set_controller_cfg(const combo_dev_cfg_t *dev_cfg)
{
    /* disable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x0;
    g_mipi_tx_regs_va->VCID.u32 = 0x0;

    /* output format,color coding */
    set_output_format(dev_cfg);

    /* txescclk,timeout */
    g_actual_phy_data_rate = ((dev_cfg->phy_data_rate + MIPI_TX_REF_CLK - 1) / MIPI_TX_REF_CLK) * MIPI_TX_REF_CLK;
    mipi_tx_drv_set_clkmgr_cfg();

    /* cmd transmission mode, register config, not magic number. */
    g_mipi_tx_regs_va->CMD_MODE_CFG.u32 = 0xffffff00;
    g_mipi_tx_regs_va->PCKHDL_CFG.u32 = 0x1e;
    g_mipi_tx_regs_va->GEN_VCID.u32 = 0x0;
    g_mipi_tx_regs_va->MODE_CFG.u32 = 0x1;

    /* video mode cfg */
    set_video_mode_cfg(dev_cfg);
    if ((dev_cfg->output_mode == OUTPUT_MODE_DSI_VIDEO) || (dev_cfg->output_mode == OUTPUT_MODE_CSI)) {
        g_mipi_tx_regs_va->VID_PKT_SIZE.u32 = dev_cfg->sync_info.vid_pkt_size;
    } else {
        g_mipi_tx_regs_va->EDPI_CMD_SIZE.u32 = dev_cfg->sync_info.edpi_cmd_size;
    }

    /* num_chunks/null_size */
    g_mipi_tx_regs_va->VID_NUM_CHUNKS.u32 = 0x0;
    g_mipi_tx_regs_va->VID_NULL_SIZE.u32 = 0x0;

    /* timing config */
    set_timing_config(dev_cfg);

    /*
     * invact,outvact time
     * the numbers are register config, not magic number.
     */
    g_mipi_tx_regs_va->LP_CMD_TIM.u32 = 0x0;
    g_mipi_tx_regs_va->PHY_TMR_CFG.u32 = 0x9002D;
    g_mipi_tx_regs_va->PHY_TMR_LPCLK_CFG.u32 = 0x29002E;
    g_mipi_tx_regs_va->EDPI_CMD_SIZE.u32 = 0xF0;
    g_mipi_tx_regs_va->LP_WR_TO_CNT.u32 = 0x0;
    g_mipi_tx_regs_va->BTA_TO_CNT.u32 = 0x0;

    /* lanes */
    set_lane_config(dev_cfg->lane_id, LANE_MAX_NUM);

    /* phy_txrequlpsclk */
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.u32 = 0x0;

    /* int msk0 */
    g_mipi_tx_regs_va->INT_MSK0.u32 = 0x0;

    /* pwr_up unreset */
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x0;
    g_mipi_tx_regs_va->PWR_UP.u32 = 0xf;
}

static int mipi_tx_wait_cmd_fifo_empty(void)
{
    U_CMD_PKT_STATUS cmd_pkt_status;
    unsigned int wait_count = 0;

    do {
        cmd_pkt_status.u32 = g_mipi_tx_regs_va->CMD_PKT_STATUS.u32;

        wait_count++;

        udelay(1);

        if (wait_count >  MIPI_TX_READ_TIMEOUT_CNT) {
            hi_err("timeout when send cmd buffer \n");
            return -1;
        }
    } while (cmd_pkt_status.bits.gen_cmd_empty == 0);

    return 0;
}

static int mipi_tx_wait_write_fifo_empty(void)
{
    U_CMD_PKT_STATUS cmd_pkt_status;
    unsigned int wait_count = 0;

    do {
        cmd_pkt_status.u32 = g_mipi_tx_regs_va->CMD_PKT_STATUS.u32;

        wait_count++;

        udelay(1);

        if (wait_count >  MIPI_TX_READ_TIMEOUT_CNT) {
            hi_err("timeout when send data buffer \n");
            return -1;
        }
    } while (cmd_pkt_status.bits.gen_pld_w_empty == 0);

    return 0;
}

static int mipi_tx_wait_write_fifo_not_full(void)
{
    U_CMD_PKT_STATUS cmd_pkt_status;
    unsigned int wait_count = 0;

    do {
        cmd_pkt_status.u32 = g_mipi_tx_regs_va->CMD_PKT_STATUS.u32;
        if (wait_count > 0) {
            udelay(1);
            hi_err("write fifo full happened wait count = %u\n", wait_count);
        }
        if (wait_count >  MIPI_TX_READ_TIMEOUT_CNT) {
            hi_err("timeout when wait write fifo not full buffer \n");
            return -1;
        }
        wait_count++;
    } while (cmd_pkt_status.bits.gen_pld_w_full == 1);

    return 0;
}

static void mipi_tx_drv_set_payload_data(const unsigned char *cmd, unsigned short cmd_size)
{
    U_GEN_PLD_DATA gen_pld_data;
    int i, j;

    gen_pld_data.u32 = g_mipi_tx_regs_va->GEN_PLD_DATA.u32;

    for (i = 0; i < (cmd_size / 4); i++) { /* 4 cmd a grp */
        gen_pld_data.bits.gen_pld_b1 = cmd[i * 4]; /* 0 in 4 */
        gen_pld_data.bits.gen_pld_b2 = cmd[i * 4 + 1]; /* 1 in 4 */
        gen_pld_data.bits.gen_pld_b3 = cmd[i * 4 + 2]; /* 2 in 4 */
        gen_pld_data.bits.gen_pld_b4 = cmd[i * 4 + 3]; /* 3 in 4 */

        mipi_tx_wait_write_fifo_not_full();
        g_mipi_tx_regs_va->GEN_PLD_DATA.u32 = gen_pld_data.u32;
    }

    j = cmd_size % 4; /* 4 remainder */
    if (j != 0) {
        if (j > 0) {
            gen_pld_data.bits.gen_pld_b1 = cmd[i * 4]; /* 0 in 4 */
        }
        if (j > 1) { /* have 1 */
            gen_pld_data.bits.gen_pld_b2 = cmd[i * 4 + 1]; /* 1 in 4 */
        }
        if (j > 2) { /* have 2 */
            gen_pld_data.bits.gen_pld_b3 = cmd[i * 4 + 2]; /* 2 in 4 */
        }

        mipi_tx_wait_write_fifo_not_full();
        g_mipi_tx_regs_va->GEN_PLD_DATA.u32 = gen_pld_data.u32;
    }

    return;
}

int mipi_tx_drv_set_cmd_info(const cmd_info_t *cmd_info)
{
    U_GEN_HDR gen_hdr;
    unsigned char *cmd = HI_NULL;

    gen_hdr.u32 = g_mipi_tx_regs_va->GEN_HDR.u32;

    if (cmd_info->cmd != HI_NULL) {
        if (cmd_info->cmd_size > 200 || cmd_info->cmd_size == 0) { /* 200 max cmd */
            hi_err("set cmd size illegal, size =%u\n", cmd_info->cmd_size);
            return -1;
        }

        cmd = (unsigned char *)malloc(cmd_info->cmd_size);
        if (cmd == HI_NULL) {
            hi_err("malloc fail, please check, need %u bytes\n", cmd_info->cmd_size);
            return -1;
        }
        memset(cmd, 0, cmd_info->cmd_size);

        memcpy(cmd, cmd_info->cmd, cmd_info->cmd_size);

        mipi_tx_drv_set_payload_data(cmd, cmd_info->cmd_size);

        free(cmd);
        cmd = HI_NULL;
    }

    gen_hdr.bits.gen_dt = cmd_info->data_type;
    gen_hdr.bits.gen_wc_lsbyte = cmd_info->cmd_size & 0xff; /* 0xff get low bits */
    gen_hdr.bits.gen_wc_msbyte = (cmd_info->cmd_size & 0xff00) >> 8; /* 8 get high byte */
    g_mipi_tx_regs_va->GEN_HDR.u32 = gen_hdr.u32;

    /* wait transfer end */
    udelay(350); /* delay 350 us */

    mipi_tx_wait_cmd_fifo_empty();
    mipi_tx_wait_write_fifo_empty();

    return 0;
}

static int mipi_tx_wait_read_fifo_not_empty(void)
{
    U_INT_ST0 int_st0;
    U_INT_ST1 int_st1;
    unsigned int wait_count;
    U_CMD_PKT_STATUS cmd_pkt_status;

    wait_count = 0;
    do {
        int_st1.u32 = g_mipi_tx_regs_va->INT_ST1.u32;
        int_st0.u32 = g_mipi_tx_regs_va->INT_ST0.u32;

        if ((int_st1.u32 & 0x3e) != 0) { /* 0x3e bits */
            hi_err("err happened when read data, int_st1 = 0x%x,int_st0 = %x\n", int_st1.u32, int_st0.u32);
            return -1;
        }

        if (wait_count > MIPI_TX_READ_TIMEOUT_CNT) {
            hi_err("timeout when read data\n");
            return -1;
        }

        wait_count++;

        udelay(1);

        cmd_pkt_status.u32 = g_mipi_tx_regs_va->CMD_PKT_STATUS.u32;
    } while (cmd_pkt_status.bits.gen_pld_r_empty == 0x1);

    return 0;
}

static int mipi_tx_wait_read_fifo_empty(void)
{
    U_GEN_PLD_DATA pld_data;
    U_INT_ST1 int_st1;
    unsigned int wait_count;
    pld_data.u32 = 0;
    int_st1.u32 = 0;
    wait_count = 0;
    do {
        int_st1.u32 = g_mipi_tx_regs_va->INT_ST1.u32;
        if ((int_st1.bits.gen_pld_rd_err) == 0x0) {
            pld_data.u32 = g_mipi_tx_regs_va->GEN_PLD_DATA.u32;
        }
        wait_count++;
        udelay(1);
        if (wait_count > MIPI_TX_READ_TIMEOUT_CNT) {
            hi_err("timeout when clear data buffer, the last read data is 0x%x \n", pld_data.u32);
            return -1;
        }
    } while ((int_st1.bits.gen_pld_rd_err) == 0x0);

    return 0;
}

static int mipi_tx_send_short_packet(unsigned char virtual_channel, unsigned short data_type,
    unsigned short data_param)
{
    U_GEN_HDR gen_hdr;

    gen_hdr.bits.gen_vc = virtual_channel;
    gen_hdr.bits.gen_dt = data_type;
    gen_hdr.bits.gen_wc_lsbyte = (data_param & 0xff); /* 0xff get low byte */
    gen_hdr.bits.gen_wc_msbyte = (data_param & 0xff00) >> 8; /* 0xff00 8 get high byte */
    g_mipi_tx_regs_va->GEN_HDR.u32 = gen_hdr.u32;

    if (mipi_tx_wait_cmd_fifo_empty() != 0) {
        return -1;
    }

    return 0;
}

static int mipi_tx_get_read_fifo_data(unsigned int get_data_size, unsigned char *data_buf)
{
    U_GEN_PLD_DATA pld_data;
    unsigned int i, j;

    for (i = 0; i < get_data_size / 4; i++) { /* 4 data group */
        if (mipi_tx_wait_read_fifo_not_empty() != 0) {
            return -1;
        }
        pld_data.u32 = g_mipi_tx_regs_va->GEN_PLD_DATA.u32;
        data_buf[i * 4] = pld_data.bits.gen_pld_b1; /* 0 in 4 */
        data_buf[i * 4 + 1] = pld_data.bits.gen_pld_b2; /* 1 in 4 */
        data_buf[i * 4 + 2] = pld_data.bits.gen_pld_b3; /* 2 in 4 */
        data_buf[i * 4 + 3] = pld_data.bits.gen_pld_b4; /* 3 in 4 */
    }

    j = get_data_size % 4; /* remainder of 4 */

    if (j != 0) {
        if (mipi_tx_wait_read_fifo_not_empty() != 0) {
            return -1;
        }
        pld_data.u32 = g_mipi_tx_regs_va->GEN_PLD_DATA.u32;
        if (j > 0) {
            data_buf[i * 4] = pld_data.bits.gen_pld_b1;  /* 0 in 4 */
        }
        if (j > 1) {
            data_buf[i * 4 + 1] = pld_data.bits.gen_pld_b2;  /* 1 in 4 */
        }
        if (j > 2) { /* have 2 */
            data_buf[i * 4 + 2] = pld_data.bits.gen_pld_b3; /* 2 in 4 */
        }
    }

    return 0;
}

void mipi_tx_reset(void)
{
    /* the number is register config, not magic number. */
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x0;
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0xd;
    udelay(1);
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x1;
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0xf;
    udelay(1);
    return;
}

int mipi_tx_drv_get_cmd_info(get_cmd_info_t *get_cmd_info)
{
    unsigned char *data_buf = HI_NULL;

    if ((get_cmd_info->get_data_size > 200) || (get_cmd_info->get_data_size == 0)) { /* 200 max data size */
        hi_err("get_data_size illegal, size =%u\n", get_cmd_info->get_data_size);
        return -1;
    }

    if (get_cmd_info->get_data == HI_NULL) {
        hi_err("get_data is NULL,illegal\n");
        return -1;
    }

    data_buf = (unsigned char*)malloc(get_cmd_info->get_data_size);
    if (data_buf == HI_NULL) {
        return -1;
    }
    memset(data_buf, 0, get_cmd_info->get_data_size);
    if (mipi_tx_wait_read_fifo_empty() != 0) {
        goto fail0;
    }

    if (mipi_tx_send_short_packet(0, get_cmd_info->data_type, get_cmd_info->data_param) != 0) {
        goto fail0;
    }

    if (mipi_tx_get_read_fifo_data(get_cmd_info->get_data_size, data_buf) != 0) {
        /* fail will block mipi data lane ,so need reset  */
        mipi_tx_reset();
        goto fail0;
    }

    memcpy(get_cmd_info->get_data, data_buf, get_cmd_info->get_data_size);

    free(data_buf);
    data_buf = HI_NULL;

    return 0;

fail0:
    free(data_buf);
    data_buf = HI_NULL;
    return -1;
}

void mipi_tx_drv_enable_input(output_mode_t output_mode)
{
    /* the numbers below are register config, not magic number. */
    if ((output_mode == OUTPUT_MODE_DSI_VIDEO) || (output_mode == OUTPUT_MODE_CSI)) {
        g_mipi_tx_regs_va->MODE_CFG.u32 = 0x0;
    }

    if (output_mode == OUTPUT_MODE_DSI_CMD) {
        g_mipi_tx_regs_va->CMD_MODE_CFG.u32 = 0x0;
    }

    /* enable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x80150000;  /* 0x80150000 register operation mode */

    g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x1;

    mipi_tx_reset();
}

void mipi_tx_drv_disable_input(void)
{
    /* the numbers below are register config, not magic number. */
    /* disable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x0;
    g_mipi_tx_regs_va->CMD_MODE_CFG.u32 = 0xffffff00;

    /* command mode */
    g_mipi_tx_regs_va->MODE_CFG.u32 = 0x1;
    g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x0;

    mipi_tx_reset();
}

static int mipi_tx_drv_reg_init(void)
{
    if (g_mipi_tx_regs_va == HI_NULL) {
        g_mipi_tx_regs_va = (mipi_tx_regs_type_t *)IO_ADDRESS(MIPI_TX_REGS_ADDR);
        if (g_mipi_tx_regs_va == HI_NULL) {
            hi_err("remap mipi_tx reg addr fail\n");
            return -1;
        }
    }

    return 0;
}

static void mipi_tx_drv_hw_init(void)
{
    unsigned long mipi_tx_crg_addr;

    mipi_tx_crg_addr = (unsigned long)IO_ADDRESS(MIPI_TX_CRG);
    /* the numbers below are register config, not magic number. */
    /* mipi_tx gate clk enable */
    write_reg32(mipi_tx_crg_addr, 1, 0x1);

    /* unreset */
    write_reg32(mipi_tx_crg_addr, 1 << 1, 0x1 << 1);

    /* ref clk */
    write_reg32(mipi_tx_crg_addr, 1 << 2, 0x1 << 2); /* set bit 2 */

    /* mipi_tx gate clk enable */
    write_reg32(mipi_tx_crg_addr, 1, 0x1);

    /* unreset */
    write_reg32(mipi_tx_crg_addr, 0 << 1, 0x1 << 1);

    /* ref clk */
    write_reg32(mipi_tx_crg_addr, 1 << 2, 0x1 << 2); /* set bit 2 */
}

int mipi_tx_drv_init(void)
{
    int ret;

    ret = mipi_tx_drv_reg_init();
    if (ret < 0) {
        hi_err("mipi_tx_drv_reg_init fail!\n");
        return -1;
    }

    mipi_tx_drv_hw_init();

    return 0;
}

void mipi_tx_drv_exit(void)
{
}

