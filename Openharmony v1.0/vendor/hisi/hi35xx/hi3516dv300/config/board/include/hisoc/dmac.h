/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HISOC_DMAC_H__
#define __HISOC_DMAC_H__
#include "asm/io.h"
#include "asm/platform.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define DDRAM_ADRS    DDR_MEM_BASE      /* fixed */
#define DDRAM_SIZE    0x3FFFFFFF        /* 1GB DDR. */


#define DMAC_INTSTATUS            (DMAC_REG_BASE + 0X00)
#define DMAC_INTTCSTATUS        (DMAC_REG_BASE + 0X04)
#define DMAC_INTTCCLEAR            (DMAC_REG_BASE + 0X08)
#define DMAC_INTERRORSTATUS        (DMAC_REG_BASE + 0X0C)
#define DMAC_INTERRCLR            (DMAC_REG_BASE + 0X10)

#define DMAC_RAWINTTCSTATUS        (DMAC_REG_BASE + 0X14)
#define DMAC_RAWINTERRORSTATUS    (DMAC_REG_BASE + 0X18)

#define DMAC_ENBLDCHNS            (DMAC_REG_BASE + 0X1C)
#define DMAC_SOFT_BREQ          (DMAC_REG_BASE + 0X20)
#define DMAC_SOFT_SREQ          (DMAC_REG_BASE + 0X24)
#define DMAC_SOFT_LBREQ         (DMAC_REG_BASE + 0X28)
#define DMAC_SOFT_LSREQ         (DMAC_REG_BASE + 0X2C)

#define DMAC_CONFIG                (DMAC_REG_BASE + 0X30)
#define DMAC_SYNC                (DMAC_REG_BASE + 0X34)

/* the definition for DMAC channel register */
#define DMAC_CxBASE(i)        (DMAC_REG_BASE + 0x100+i*0x20)

#define DMAC_CxSRCADDR(i)    (DMAC_CxBASE(i) + 0x00)
#define DMAC_CxDESTADDR(i)    (DMAC_CxBASE(i) + 0x04)
#define DMAC_CxLLI(i)        (DMAC_CxBASE(i) + 0x08)
#define DMAC_CxCONTROL(i)    (DMAC_CxBASE(i) + 0x0C)
#define DMAC_CxCONFIG(i)    (DMAC_CxBASE(i) + 0x10)

#define DMAC_MAXTRANSFERSIZE    0x0fff /* the max length is denoted by 0-11bit */
#define DMAC_CxDISABLE            0x00
#define DMAC_CxENABLE            0x01

/* the means the bit in the channel control register */
#define DMAC_CxCONTROL_M2M        0x8d489000  /* Dwidth=32,burst size=4 */
#define DMAC_CxCONTROL_LLIM2M    0x0d489000  /* Dwidth=32,burst size=4 */
#define DMAC_CxCONTROL_LLIP2M    0x0a000000            // 0x09409000
#define DMAC_CxCONTROL_LLIM2P    0x86089000

#define DMAC_CxCONTROL_INT_EN   (0x01 << 31)  /* bit:31,enable interrupt */

#define DMAC_CxLLI_LM            0x01
#define DMAC_TRANS_SIZE         0xff0

#define DMAC_CHANNEL_ENABLE        1
#define DMAC_CHANNEL_DISABLE    0xfffffffe

#define DMAC_CxCONFIG_M2M        0xc000
#define DMAC_CxCONFIG_LLIM2M    0xc000

#define DMAC_CxCONFIG_P2M        0xd000
#define DMAC_CxCONFIG_M2P        0xc800

#define DMAC_CxCONFIG_SIO_P2M    0x0000d000
#define DMAC_CxCONFIG_SIO_M2P    0x0000c800

/* default the config and sync regsiter for DMAC controller */
/* M1,M2 little endian, enable DMAC */
#define DMAC_CONFIG_VAL            0x01
/* enable the sync logic for the 16 peripheral */
#define DMAC_SYNC_VAL            0x0

#define DMAC_MAX_PERIPHERALS    16    // 12
#define MEM_MAX_NUM                1
#define CHANNEL_NUM                4
#define DMAC_MAX_CHANNELS    CHANNEL_NUM

#define PERI_CRG91  (CRG_REG_BASE + 0x16c)
#define DMAC_CLK_EN     (1 << 5)
#define DMAC_SRST_REQ   (1 << 4)


static void hidmac_clk_en(void)
{
    unsigned int tmp;

    tmp = readl(PERI_CRG91);
    tmp |= DMAC_CLK_EN;
    writel(tmp, PERI_CRG91);
}

static void hidmac_unreset(void)
{
    unsigned int tmp;

    tmp = readl(PERI_CRG91);
    tmp &= ~DMAC_SRST_REQ;
    writel(tmp, PERI_CRG91);
}

#define PERI_8BIT_MODE            0
#define PERI_16BIT_MODE           1
#define PERI_32BIT_MODE           2


// hidmac data structure

/* DMAC peripheral structure */
typedef struct dmac_peripheral {
    /* peripherial ID */
    unsigned int peri_id;
    /* peripheral data register address */
    unsigned int peri_addr;
    /* default channel control word */
    unsigned int transfer_ctrl;
    /* default channel configuration word */
    unsigned int transfer_cfg;
    /* default channel configuration word */
    unsigned int transfer_width;
} dmac_peripheral;

/*
 *    DMA config array!
 *    DREQ, FIFO, CONTROL, CONFIG, BITWIDTH
 */
static dmac_peripheral  g_peripheral[DMAC_MAX_PERIPHERALS] = {
    /* DREQ,  FIFO,   CONTROL,   CONFIG, WIDTH */
    /* periphal 0: I2C0/I2C1 RX */
    { 0, I2C1_REG_BASE + 0x10, 0, DMAC_CxCONTROL_LLIP2M | (0 << 1), PERI_8BIT_MODE},

    /* periphal 1: I2C0/I2C1 TX */
    { 1, I2C1_REG_BASE + 0x10, 0, DMAC_CxCONTROL_LLIP2M | (1 << 1), PERI_8BIT_MODE},

    /* periphal 2: I2C1/I2C2 RX */
    { 2, I2C1_REG_BASE + 0x10, 0x99000000, DMAC_CxCONTROL_LLIP2M | (2 << 1), PERI_8BIT_MODE},    /*  8bit width */

    /* periphal 3: I2C1/I2C2 TX */
    { 3, I2C1_REG_BASE + 0x10, 0x96000000, DMAC_CxCONTROL_LLIP2M | (3 << 1), PERI_8BIT_MODE},    /*  8bit width */

    /* periphal 4: UART0 RX */
    { 4, UART0_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (4 << 1), PERI_8BIT_MODE},

    /* periphal 5: UART0 TX */
    { 5, UART0_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (5 << 1), PERI_8BIT_MODE},

    /* periphal 6: UART1 RX */
    { 6, UART1_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (6 << 1), PERI_8BIT_MODE},

    /* periphal 7: UART1 TX */
    { 7, UART1_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (7 << 1), PERI_8BIT_MODE},

    /* periphal 8: UART2 RX */
    { 8, UART2_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (8 << 1), PERI_8BIT_MODE},

    /* periphal 9: UART2 TX */
    { 9, UART2_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (9 << 1), PERI_8BIT_MODE},

    /* periphal 10: UART3 RX */
    { 10, UART3_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (10 << 1), PERI_8BIT_MODE},

    /* periphal 11: UART0 TX */
    { 11, UART3_REG_BASE + 0x00, DMAC_CxCONTROL_LLIP2M, DMAC_CxCONFIG_P2M | (11 << 1), PERI_8BIT_MODE},

    /* periphal 12: SSP1 RX */
    { 12, 0, 0, 0, 0},

    /* periphal 13: SSP1 TX */
    { 13, 0, 0, 0, 0},

    /* periphal 14: SSP0 RX */
    { 14, 0, 0, 0, 0},

    /* periphal 15: SSP0 TX */
    { 15, 0, 0, 0, 0},

};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
