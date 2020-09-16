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

/*
 * macro definition
 */
#define MIPI_TX_REGS_ADDR 0x04780000
#define MIPI_TX_REGS_SIZE 0x10000

#define MIPI_TX_CRG 0x0451011C
#ifndef HI_FPGA
#define MIPI_TX_IO_CONFIG 0x1F001088
#define MIPI_TX_GPIO0_0   0x12140010
#define MIPI_TX_GPIO0_1   0x12140400
#define MIPI_TX_GPIO6_0   0x12146004
#define MIPI_TX_GPIO6_1   0x12146400
#endif

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
#define PLL_SET0 0x14
#define PLL_SET1 0x15
#define PLL_SET2 0x16
#ifdef HI_FPGA
#define PLL_SET3 0x17
#endif
#define PLL_SET4  0x1E
#define PLL_SET12 0x12
#define PLL_SET13 0x13

#define DATA0_TPRE_DELAY 0x30
#define DATA1_TPRE_DELAY 0x40
#define DATA2_TPRE_DELAY 0x50
#define DATA3_TPRE_DELAY 0x60

#define CLK_TLPX         0x22
#define CLK_TCLK_PREPARE 0x23
#define CLK_TCLK_ZERO    0x24
#define CLK_TCLK_TRAIL   0x25

#define DATA0_TLPX        0x32
#define DATA0_THS_PREPARE 0x33
#define DATA0_THS_ZERO    0x34
#define DATA0_THS_TRAIL   0x35
#define DATA1_TLPX        0x42
#define DATA1_THS_PREPARE 0x43
#define DATA1_THS_ZERO    0x44
#define DATA1_THS_TRAIL   0x45
#define DATA2_TLPX        0x52
#define DATA2_THS_PREPARE 0x53
#define DATA2_THS_ZERO    0x54
#define DATA2_THS_TRAIL   0x55
#define DATA3_TLPX        0x62
#define DATA3_THS_PREPARE 0x63
#define DATA3_THS_ZERO    0x64
#define DATA3_THS_TRAIL   0x65

#define MIPI_TX_READ_TIMEOUT_CNT 1000
#define MIPI_TX_MAX_RESET_PHY_TIMES 10

#define PREPARE_COMPENSATE 10
#define ROUNDUP_VALUE 7999
#define INNER_PEROID 8000   /* 8 * 1000 ,1000 is 1us = 1000ns, 8 is division ratio */

#define IO_ADDRESS(x) (x)

volatile mipi_tx_regs_type_t *g_mipi_tx_regs_va = HI_NULL;

unsigned int g_actual_phy_data_rate;

static inline void write_reg32(unsigned long addr, unsigned int value, unsigned int mask)
{
    unsigned int t;

    t = readl((void *)addr);
    t &= ~mask;
    t |= value & mask;
    writel(t, (void *)addr);
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
            *clk_prepare = 255;  /* set 255 will easy to found mistake */
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
        (85 * g_actual_phy_data_rate + 6 * 1000))) { /* 85 + 6 * 1000 is the maximum in mipi protocol */
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
    unsigned char pll_set12;
#ifdef HI_FPGA
    unsigned char pll_set3;
#endif
    unsigned char pll_set4;
    unsigned char data_tpre_delay;
    unsigned char clk_tlpx;
    unsigned char clk_tclk_prepare;
    unsigned char clk_tclk_zero;
    unsigned char clk_tclk_trail;
    unsigned char data_tlpx;
    unsigned char data_ths_prepare;
    unsigned char data_ths_zero;
    unsigned char data_ths_trail;
    /* the numbers below are register config, not magic number. */
    /* disable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x0;

    /* pwr_up unreset */
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x0;
    udelay(1);
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x1;

    /* stop phy driver output */
    pll_set12 = 0x20;
    set_phy_reg(PLL_SET12, pll_set12);
    pll_set12 = 0x30;
    set_phy_reg(PLL_SET12, pll_set12);

    /* step1: phy exit ulps mode */
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.u32 = 0x0;

    /* phy power down */
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0x0;
    udelay(5); /* delay 5 us */

    pll_set0 = 0x0;
    set_phy_reg(PLL_SET0, pll_set0);
    pll_set1 = 0xf;
    set_phy_reg(PLL_SET1, pll_set1);
    pll_set2 = 0x61;
    set_phy_reg(PLL_SET2, pll_set2);
    pll_set4 = 0x68;
    set_phy_reg(PLL_SET4, pll_set4);

    /* step3 :phy power on */
    g_mipi_tx_regs_va->PHY_RSTZ.u32 = 0xf;
    /* step4 */
    udelay(100); /* delay 100 us */
    /* the numbers below are register config, not magic number. */
    /* step5:999M start pll  */
    pll_set1 = 0x25;
    set_phy_reg(PLL_SET1, pll_set1);
    pll_set4 = 0x68;
    set_phy_reg(PLL_SET4, pll_set4);
    pll_set0 = 0x02;
    set_phy_reg(PLL_SET0, pll_set0);
    pll_set2 = 0xe1;
    set_phy_reg(PLL_SET2, pll_set2);

    udelay(100); /* delay 100 us */

    pll_set0 = 0x0;
    set_phy_reg(PLL_SET0, pll_set0);
    pll_set2 = 0x61;
    set_phy_reg(PLL_SET2, pll_set2);

#ifndef HI_FPGA
    if (dev_cfg->phy_data_rate >= 320) { /* data rate bigger than 320 */
        pll_set1 = (dev_cfg->phy_data_rate + MIPI_TX_REF_CLK - 1) / MIPI_TX_REF_CLK;
        g_actual_phy_data_rate = pll_set1 * MIPI_TX_REF_CLK;
    } else {
        pll_set1 = (dev_cfg->phy_data_rate * 4 + MIPI_TX_REF_CLK - 1) / MIPI_TX_REF_CLK; /* 4 get cfg */
        g_actual_phy_data_rate = pll_set1 * MIPI_TX_REF_CLK / 4; /* 4 get cfg */
    }
#else
    if (dev_cfg->phy_data_rate >= 320) { /* data rate bigger than 320 */
        pll_set1 = dev_cfg->phy_data_rate / MIPI_TX_REF_CLK / 2; /* 2 get cfg */
        g_actual_phy_data_rate = dev_cfg->phy_data_rate / MIPI_TX_REF_CLK * MIPI_TX_REF_CLK;
    } else {
        pll_set1 = dev_cfg->phy_data_rate * 4 / MIPI_TX_REF_CLK / 2;  /* 4 2 get cfg */
        g_actual_phy_data_rate = dev_cfg->phy_data_rate * 4 / MIPI_TX_REF_CLK * MIPI_TX_REF_CLK / 4; /* 4 2 get cfg */
    }
#endif
    set_phy_reg(PLL_SET1, pll_set1);
    /* the numbers below are register config, not magic number. */
    /* pll_set4 */
#ifndef HI_FPGA
    if (dev_cfg->phy_data_rate >= 320) { /* data rate bigger than 320 */
        pll_set4 = 0x68;
    } else {
        pll_set4 = 0x6c;
    }
#else
    if (dev_cfg->phy_data_rate >= 320) { /* data rate bigger than 320 */
        if (dev_cfg->phy_data_rate >= 750) { /* data rate bigger than 750 */
            pll_set4 = 0x68;
        } else {
            pll_set4 = 0x28;
        }
    } else {
        pll_set4 = 0x2c;
    }
#endif
    set_phy_reg(PLL_SET4, pll_set4);

#ifdef HI_FPGA
    pll_set3 = 0x1;
    set_phy_reg(PLL_SET3, pll_set3);
#endif

    /* DATA0~3 TPRE-DELAY */
    data_tpre_delay = (g_actual_phy_data_rate * TPRE_DELAY + ROUNDUP_VALUE) / INNER_PEROID - 1; /* 1 is compensate */
    set_phy_reg(DATA0_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA1_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA2_TPRE_DELAY, data_tpre_delay);
    set_phy_reg(DATA3_TPRE_DELAY, data_tpre_delay);

    clk_tlpx = (g_actual_phy_data_rate * TLPX + ROUNDUP_VALUE) / INNER_PEROID - 1;
    set_phy_reg(CLK_TLPX, clk_tlpx);
    mipi_tx_drv_get_phy_clk_prepare(&clk_tclk_prepare);
    set_phy_reg(CLK_TCLK_PREPARE, clk_tclk_prepare);
    if ((g_actual_phy_data_rate * TCLK_ZERO + ROUNDUP_VALUE) / INNER_PEROID > 5) { /* 5 is compensate */
        clk_tclk_zero = (g_actual_phy_data_rate * TCLK_ZERO + ROUNDUP_VALUE) / INNER_PEROID - 5; /* 5 is compensate */
    } else {
        clk_tclk_zero = 0;
    }
    set_phy_reg(CLK_TCLK_ZERO, clk_tclk_zero);
    clk_tclk_trail = (g_actual_phy_data_rate * TCLK_TRAIL + ROUNDUP_VALUE) / INNER_PEROID + 3; /* 3 is compensate */
    set_phy_reg(CLK_TCLK_TRAIL, clk_tclk_trail);

    /*
     * DATA_TLPX
     * DATA_THS_PREPARE
     * DATA_THS_ZERO
     * DATA_THS_TRAIL
     */
    data_tlpx = (g_actual_phy_data_rate * TLPX + ROUNDUP_VALUE) / INNER_PEROID - 1;

    mipi_tx_drv_get_phy_data_prepare(&data_ths_prepare);

    if ((g_actual_phy_data_rate * THS_ZERO + ROUNDUP_VALUE) / INNER_PEROID > 5) { /* 5 is compensate */
        data_ths_zero = (g_actual_phy_data_rate * THS_ZERO + ROUNDUP_VALUE) / INNER_PEROID - 5; /* 5 is compensate */
    } else {
        data_ths_zero = 0;
    }

    data_ths_trail = (g_actual_phy_data_rate * THS_TRAIL + ROUNDUP_VALUE) / INNER_PEROID + 3; /* 3 to cal cfg */

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

    /* data lp2hs,hs2lp time */
    g_mipi_tx_regs_va->PHY_TMR_CFG.u32 = ((data_ths_trail - 2) << 16) + /* 2 16 to cal cfg */
        data_tpre_delay + data_tlpx + data_ths_prepare + data_ths_zero + 8; /* 8 to cal cfg */
    /* clk lp2hs,hs2lp time */
    g_mipi_tx_regs_va->PHY_TMR_LPCLK_CFG.u32 = ((30 + data_ths_trail) << 16) + /* 30 16 to cal cfg */
        clk_tlpx + clk_tclk_prepare + clk_tclk_zero + 7;  /* 7 to cal cfg */

    udelay(1000); /* delay 1000 us */
}

static void set_output_format(const combo_dev_cfg_t *dev_cfg)
{
    int color_coding = 0;
    /* the numbers are register config, not magic number. */
    if (dev_cfg->output_mode == OUTPUT_MODE_CSI) {
        if (dev_cfg->output_format == OUT_FORMAT_YUV420_8_BIT_NORMAL) {
            color_coding = 0xd;
        } else if (dev_cfg->output_format == OUT_FORMAT_YUV422_8_BIT) {
            color_coding = 0x1;
        }
    } else {
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
    U_LANE_ID lane_id_reg;

    for (i = 0; i < n; i++) {
        if (lane_id[i] != -1) {
            lane_num++;
        }
    }

    g_mipi_tx_regs_va->PHY_IF_CFG.u32 = lane_num - 1;

    lane_id_reg.u32 = g_mipi_tx_regs_va->LANE_ID.u32;
    if (lane_id[0] >= 0) {
        lane_id_reg.bits.lane0_id = lane_id[0];
    }
    if (lane_id[1] >= 0) {
        lane_id_reg.bits.lane1_id = lane_id[1];
    }
    if (lane_id[2] >= 0) { /* land 2 */
        lane_id_reg.bits.lane2_id = lane_id[2]; /* land 2 */
    }
    if (lane_id[3] >= 0) { /* land 3 */
        lane_id_reg.bits.lane3_id = lane_id[3]; /* land 3 */
    }
    g_mipi_tx_regs_va->LANE_ID.u32 = lane_id_reg.u32;

#ifdef MIPI_TX_DEBUG
    printf("LANE_ID(0x250): 0x%x\n", lane_id_reg.u32);
#endif
}

int mipi_tx_drv_get_phy_status_phy_stopstateclk(void);
int mipi_tx_drv_get_phy_status_phy_hsstateclk(void);

void mipi_tx_drv_phy_reset(void)
{
    g_mipi_tx_regs_va->PHY_RSTZ.bits.phy_rstz = 0x0;
}

void mipi_tx_drv_phy_unreset(void)
{
    g_mipi_tx_regs_va->PHY_RSTZ.bits.phy_rstz = 0x1;
}

void mipi_tx_check_clkstopstate(void)
{
    int i = 0;
    const unsigned int trytimes = 4; /* try 4 times */
    while (i < trytimes) {
        if (mipi_tx_drv_get_phy_status_phy_stopstateclk() == 1) {
            /* check clock stop */
            break;
        } else {
            udelay(5); /* delay 5 us */
        }
        i++;
    }
    if (i == trytimes) {
        printf("%s,%d check clkstop state failed.\n", __FUNCTION__, __LINE__);
    }
}

void mipi_tx_check_clkhsstate(void)
{
    int i = 0;
    const unsigned int trytimes = 4; /* try 4 times */
    while (i < trytimes) {
        if (mipi_tx_drv_get_phy_status_phy_hsstateclk() == 0) {
            /* check clock hs */
            break;
        } else {
            g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x0;
            udelay(1); /* delay 1 us */
            g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x1;
            udelay(5); /* delay 5 us */
        }
        i++;
    }
    if (i == trytimes) {
        printf("%s,%d check clk hs state failed.\n", __FUNCTION__, __LINE__);
    }
}

void mipi_tx_drv_set_clkmgr_cfg(void)
{
    if (g_actual_phy_data_rate / 160 < 2) { /* 160 cal div, should not samller than 2 */
        g_mipi_tx_regs_va->CLKMGR_CFG.u32 = 0x102;
    } else {
        g_mipi_tx_regs_va->CLKMGR_CFG.u32 = 0x100 + (g_actual_phy_data_rate + 159) / 160; /* 159 160 cal div */
    }
}

void mipi_tx_drv_set_controller_cfg(const combo_dev_cfg_t *dev_cfg)
{
    /* vc_id */
    g_mipi_tx_regs_va->VCID.u32 = 0x0;

    /* output format */
    set_output_format(dev_cfg);

    /* txescclk,timeout */
    mipi_tx_drv_set_clkmgr_cfg();

    /* the numbers below are register config, not magic numbers. */
    /* cmd transmission mode */
    g_mipi_tx_regs_va->CMD_MODE_CFG.u32 = 0xffffff00;
    g_mipi_tx_regs_va->PCKHDL_CFG.u32 = 0x1e;
    g_mipi_tx_regs_va->GEN_VCID.u32 = 0x0;

    /* mode config */
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

    /* invact,outvact time */
    g_mipi_tx_regs_va->LP_CMD_TIM.u32 = 0x0;
    g_mipi_tx_regs_va->LP_WR_TO_CNT.u32 = 0x0;
    g_mipi_tx_regs_va->BTA_TO_CNT.u32 = 0x0;
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.u32 = 0x0;

    /* the numbers below are register config, not magic numbers. */
    if (dev_cfg->output_mode == OUTPUT_MODE_CSI) {
        if (dev_cfg->output_format == OUT_FORMAT_YUV420_8_BIT_NORMAL) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x10218;
            g_mipi_tx_regs_va->DATATYPE1 = 0x31081909;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x1111;
        } else if (dev_cfg->output_format == OUT_FORMAT_YUV422_8_BIT) {
            g_mipi_tx_regs_va->DATATYPE0.u32 = 0x1021E;
            g_mipi_tx_regs_va->DATATYPE1 = 0x31081909;
            g_mipi_tx_regs_va->CSI_CTRL.u32 = 0x1111;
        }
    }

    /* pll status check program */
    udelay(100); /* delay 100 us */
    mipi_tx_pll_status_check(dev_cfg);

    /* lanes */
    set_lane_config(dev_cfg->lane_id, LANE_MAX_NUM);

    g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x0;
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
            hi_err("malloc fail,please check,need %u bytes\n", cmd_info->cmd_size);
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
    U_INT_ST1 int_st1 ;
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
        if (wait_count >  MIPI_TX_READ_TIMEOUT_CNT) {
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
    /* the numbers are register config, not magic number. */
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
    unsigned char* data_buf = HI_NULL;

    if (get_cmd_info->get_data_size > 200 || get_cmd_info->get_data_size == 0) { /* 200 max data size */
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

    /* the numbers below are register config, not magic number. */
    udelay(1);
    /* B0 [2] = 1 */
    mipi_tx_check_clkstopstate();
    g_mipi_tx_regs_va->LPCLK_CTRL.u32 = 0x1;
    udelay(1);
    /* B0 [2] = 0 */
    mipi_tx_check_clkhsstate();

    /* enable input */
    g_mipi_tx_regs_va->OPERATION_MODE.u32 = 0x80150000; /* 0x80150000 register operation mode */
    /* reset mipi_tx */
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x0;
    mipi_tx_drv_phy_reset();
    udelay(1);
    mipi_tx_drv_phy_unreset();
    g_mipi_tx_regs_va->PWR_UP.u32 = 0x1;
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
    g_mipi_tx_regs_va = (mipi_tx_regs_type_t *)IO_ADDRESS(MIPI_TX_REGS_ADDR);

    return 0;
}

static void mipi_tx_drv_reg_exit(void)
{
}

static void mipi_tx_drv_hw_init(void)
{
    unsigned long mipi_tx_crg_addr;

    mipi_tx_crg_addr = (unsigned long)IO_ADDRESS(MIPI_TX_CRG);
    /* the numbers below are register config, not magic number. */
    /* mipi_tx gate clk enable */
    write_reg32(mipi_tx_crg_addr, 1, 0x1);

    /* unreset */
    write_reg32(mipi_tx_crg_addr, 0, 0x1 << 2);  /* set bit 2 */

    /* ref clk */
    write_reg32(mipi_tx_crg_addr, 1 << 4, 0x1 << 4); /* set bit 4 */
}

unsigned int mipi_tx_drv_get_phy_status_phy_lock(void)
{
    unsigned int u32phy_lock;

    u32phy_lock = g_mipi_tx_regs_va->PHY_STATUS.bits.phy_lock;
    return u32phy_lock;
}

int hal_phy_getphy_statusphy_stopstate_xlane(unsigned int x, unsigned int *phy_stopstate_xlane)
{
    U_PHY_STATUS phy_status;
    phy_status.u32 = g_mipi_tx_regs_va->PHY_STATUS.u32;
    switch (x) {
        /* 0lane */
        case 0:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate0lane;
            break;
        /* 1lane */
        case 1:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate1lane;
            break;
        /* 2lane */
        case 2:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate2lane;
            break;
        /* 3lane */
        case 3:
            *phy_stopstate_xlane = phy_status.bits.phy_stopstate3lane;
            break;
        default:
            /* do nothing. */
            break;
    }

    return 1;
}

int hal_phy_getphy_statusphy_stopstateclk(unsigned int *phy_stopstateclk)
{
    *phy_stopstateclk = g_mipi_tx_regs_va->PHY_STATUS.bits.phy_stopstateclklane;
    return 1;
}

int hal_phy_getphy_statusphy_hsstateclk(unsigned int *phy_hsstateclk)
{
    *phy_hsstateclk = g_mipi_tx_regs_va->PHY_STATUS.bits.phy_stopstateclklane;
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txrequlpslan(unsigned int uphy_txrequlpslan)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txrequlpslan = uphy_txrequlpslan;
    return 1;
}

int hal_phy_getphy_statusphy_ulpsactivenot_xlane(unsigned int x, unsigned int *phy_ulpsactivenot_xlane)
{
    U_PHY_STATUS phy_status;
    phy_status.u32 = g_mipi_tx_regs_va->PHY_STATUS.u32;

    switch (x) {
        /* 0lane */
        case 0:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot0lane;
            break;
        /* 1lane */
        case 1:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot1lane;
            break;
        /* 2lane */
        case 2:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot2lane;
            break;
        /* 3lane */
        case 3:
            *phy_ulpsactivenot_xlane = phy_status.bits.phy_ulpsactivenot3lane;
            break;
        default:
            /* do nothing. */
            break;
    }
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txexitulpslan(unsigned int uphy_txexitulpslan)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txexitulpslan = uphy_txexitulpslan;
    return 1;
}

int hal_phy_getphy_statusphy_ulpsactivenotclk(unsigned int *phy_ulpsactivenotclk)
{
    *phy_ulpsactivenotclk = g_mipi_tx_regs_va->PHY_STATUS.bits.phy_ulpsactivenotclk;
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txrequlpsclk(unsigned int uphy_txrequlpsclk)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txrequlpsclk = uphy_txrequlpsclk;
    return 1;
}

int hal_phy_setphy_ulps_ctrlphy_txexitulpsclk(unsigned int uphy_txexitulpsclk)
{
    g_mipi_tx_regs_va->PHY_ULPS_CTRL.bits.phy_txexitulpsclk = uphy_txexitulpsclk;
    return 1;
}

int mipi_tx_drv_get_phy_status_phy_stopstate_xlane(unsigned int xlane)
{
    unsigned int phy_stopstate_xlane = 0;

    hal_phy_getphy_statusphy_stopstate_xlane(xlane, &phy_stopstate_xlane);
    return phy_stopstate_xlane;
}

int mipi_tx_drv_get_phy_status_phy_stopstateclk(void)
{
    unsigned int phy_stopstateclk = 0;

    hal_phy_getphy_statusphy_stopstateclk(&phy_stopstateclk);
    return phy_stopstateclk;
}

int mipi_tx_drv_get_phy_status_phy_hsstateclk(void)
{
    unsigned int phy_hsstateclk = 0;

    hal_phy_getphy_statusphy_hsstateclk(&phy_hsstateclk);
    return phy_hsstateclk;
}

unsigned int mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(unsigned int xlane)
{
    unsigned int phy_ulpsactivenot_xlane = 0;

    hal_phy_getphy_statusphy_ulpsactivenot_xlane(xlane, &phy_ulpsactivenot_xlane);
    return phy_ulpsactivenot_xlane;
}

void mipi_tx_drv_set_ulps_mode(void)
{
    hal_phy_setphy_ulps_ctrlphy_txrequlpslan(0x1); /* 0x1 register config. */
}

void mipi_tx_drv_exit_ulps_mode(void)
{
    /* the numbers below are register config, not magic number. */
    hal_phy_setphy_ulps_ctrlphy_txrequlpslan(0x1);
    hal_phy_setphy_ulps_ctrlphy_txexitulpslan(0x1);
    hal_phy_setphy_ulps_ctrlphy_txrequlpsclk(0x0);
    hal_phy_setphy_ulps_ctrlphy_txexitulpsclk(0x0);
}

unsigned int mipi_tx_drv_get_phy_status_phy_stopstateclklane(void)
{
    unsigned int phy_ulpsactivenotclk = 0;

    hal_phy_getphy_statusphy_ulpsactivenotclk(&phy_ulpsactivenotclk);

    return phy_ulpsactivenotclk;
}

static unsigned int mipi_tx_check_phy_lock(unsigned int try_times)
{
    unsigned int i = 0;

    while (i < try_times) {
        if (mipi_tx_drv_get_phy_status_phy_lock() == 1) {
            /* check phy lock */
            break;
        } else {
            udelay(15); /* delay 15 us */
        }
        i++;
    }
    return i;
}

static unsigned int mipi_tx_check_datalane_stopstatus(unsigned int try_times)
{
    unsigned int i = 0;
    while (i < try_times) {
        if ((mipi_tx_drv_get_phy_status_phy_stopstate_xlane(0) == 1) &&  /* lane 0 */
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(1) == 1) &&  /* lane 1 */
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(2) == 1) &&  /* lane 2 */
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(3) == 1)) {  /* lane 3 */
            /* check data lane stop status */
            break;
        } else {
            udelay(15); /* delay 15 us */
        }
        i++;
    }
    return i;
}

static unsigned int mipi_tx_check_datalane_ulpsstatus(unsigned int try_times)
{
    unsigned int i = 0;
    while (i < try_times) {
        if ((mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(0) == 0) &&  /* lane 0 */
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(1) == 0) &&  /* lane 1 */
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(2) == 0) &&  /* lane 2 */
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(3) == 0)) {  /* lane 3 */
            /* check data lane ulps status */
            break;
        } else {
            udelay(15); /* delay 15 us */
        }
        i++;
    }
    return i;
}

static unsigned int mipi_tx_check_datalane_exitulpsmode(unsigned int try_times)
{
    unsigned int i = 0;
    while (i < try_times) {
        if ((mipi_tx_drv_get_phy_status_phy_stopstateclklane() == 1) &&
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(0) == 1) &&  /* lane 0 */
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(1) == 1) &&  /* lane 1 */
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(2) == 1) &&  /* lane 2 */
            (mipi_tx_drv_get_phy_status_phy_ulpsactivenot_xlane(3) == 1)) {  /* lane 3 */
            /* check clklane and datalane exit ulps mode. */
            break;
        } else {
            udelay(15); /* delay 15 us */
        }
        i++;
    }
    return i;
}

static unsigned int mipi_tx_check_datalane_stopxlane(unsigned int try_times)
{
    unsigned int i = 0;
    while (i < try_times) {
        if ((mipi_tx_drv_get_phy_status_phy_stopstate_xlane(0) == 1) &&  /* lane 0 */
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(1) == 1) &&  /* lane 1 */
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(2) == 1) &&  /* lane 2 */
            (mipi_tx_drv_get_phy_status_phy_stopstate_xlane(3) == 1)) {  /* lane 3 */
            /* check phy lock */
            break;
        } else {
            udelay(15); /* delay 15 us */
        }
        i++;
    }
    return i;
}

static void mipi_tx_drv_enter_ulps_mode(void)
{
    /* the numbers below are register config, not magic number. */
    hal_phy_setphy_ulps_ctrlphy_txrequlpslan(0x0);
    hal_phy_setphy_ulps_ctrlphy_txexitulpslan(0x0);
    hal_phy_setphy_ulps_ctrlphy_txrequlpsclk(0x0);
    hal_phy_setphy_ulps_ctrlphy_txexitulpsclk(0x0);
}

static void mipi_tx_drv_set_phy_lptx_force_value(void)
{
    unsigned int pll_set12;

    /* step11 */
    pll_set12 = 0x20;
    set_phy_reg(PLL_SET12, pll_set12);

    /* step 12 */
    pll_set12 = 0x0;
    set_phy_reg(PLL_SET12, pll_set12);
}

void mipi_tx_pll_status_check(const combo_dev_cfg_t *dev_cfg)
{
    unsigned int i;
    const unsigned int trytimes = 4; /* try 4 times */
    int count = 0;

    while (count < MIPI_TX_MAX_RESET_PHY_TIMES) {
        /* step2 */
        /* step3 */
        i = mipi_tx_check_phy_lock(trytimes);
        if (i == trytimes) {
            /* reset phy */
            count = mipi_tx_drv_reset_phy(dev_cfg);
            /* goto step2 */
            continue;
        }

        /* step 4 */
        i = mipi_tx_check_datalane_stopstatus(trytimes);
        if (i == trytimes) {
            /* reset phy */
            count = mipi_tx_drv_reset_phy(dev_cfg);
            /* goto step2 */
            continue;
        }

        /* step 5 */
        mipi_tx_drv_set_ulps_mode();

        /* step 6 */
        i = mipi_tx_check_datalane_ulpsstatus(trytimes);
        if (i == trytimes) {
            /* reset phy */
            count = mipi_tx_drv_reset_phy(dev_cfg);
            /* goto step2 */
            continue;
        }

        /* step 7 exit ulps mode */
        mipi_tx_drv_exit_ulps_mode();

        /* step 8 */
        i = mipi_tx_check_datalane_exitulpsmode(trytimes);
        if (i == trytimes) {
            /* reset phy */
            count = mipi_tx_drv_reset_phy(dev_cfg);
            /* goto step2 */
            continue;
        }

        /* step 9 */
        mipi_tx_drv_enter_ulps_mode();

        /* step 10 */
        i = mipi_tx_check_datalane_stopxlane(trytimes);
        if (i == trytimes) {
            /* reset phy */
            count = mipi_tx_drv_reset_phy(dev_cfg);
            /* goto step2 */
            continue;
        }

        /* step11, step 12  */
        mipi_tx_drv_set_phy_lptx_force_value();

        break;
    }

    if (count < MIPI_TX_MAX_RESET_PHY_TIMES) {
        printf("[%s][%d]check pll status success.\n", __FUNCTION__, __LINE__);
    } else {
#ifdef MIPI_TX_DEBUG
        printf("[%s][%d]check pll status failed.\n", __FUNCTION__, __LINE__);
#endif
    }
    return;
}

int mipi_tx_drv_init(void)
{
    int ret;

    ret = mipi_tx_drv_reg_init();
    if (ret < 0) {
        hi_err("mipi_tx_drv_reg_init fail!\n");
        goto fail0;
    }

    mipi_tx_drv_hw_init();

    return 0;

fail0:
    return -1;
}

void mipi_tx_drv_exit(void)
{
    mipi_tx_drv_reg_exit();
}

