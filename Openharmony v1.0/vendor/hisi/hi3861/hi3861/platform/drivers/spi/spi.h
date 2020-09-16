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

#ifndef __SPI_H__
#define __SPI_H__

#include <hi_types_base.h>
#include <hi3861_platform_base.h>
#include <hi_spi.h>
#include <hi_time.h>
#include <hi_stdlib.h>
#include <hi_isr.h>
#include <hi_event.h>
#include <hi_sem.h>

/* if some print is needed :#define SPI_DEBUG */
#ifdef SPI_DEBUG
#define spi_printf(fmt...) do { \
    printf("[DEBUG]"fmt); \
    printf("\n"); \
} while (0)
#define spi_process_printf(fmt...) do { \
    printf("[PROCESS]"fmt); \
    printf("\n"); \
} while (0)
#else
#define spi_printf(fmt, ...)
#define spi_process_printf(fmt, ...)
#endif

#define SPI_NUM             2

#define REG_SPI_CR0         0x00
#define REG_SPI_CR1         0x04
#define REG_SPI_DR          0x08
#define REG_SPI_SR          0x0c
#define REG_SPI_CPSR        0x10
#define REG_SPI_IMSC        0x14
#define REG_SPI_RIS         0x18
#define REG_SPI_MIS         0x1c
#define REG_SPI_CR          0x20
#define REG_SPI_DMACR       0x24
#define REG_SPI_TXFIFOCR    0x28
#define REG_SPI_RXFIFOCR    0x2c

#define MASK_SPI_SR_TFE    (1<<0)
#define MASK_SPI_SR_TNF    (1<<1)
#define MASK_SPI_SR_RNE    (1<<2)
#define MASK_SPI_SR_RFF    (1<<3)
#define MASK_SPI_SR_BSY    (1<<4)

#define SPI_CR0_ST_BIT_DSS  0
#define SPI_CR0_ST_BIT_FRF  4
#define SPI_CR0_ST_BIT_SPO  6
#define SPI_CR0_ST_BIT_SPH  7
#define SPI_CR0_ST_BIT_SCR  8

#define SPI_CR0_BIT_WIDTH_DSS   4
#define SPI_CR0_BIT_WIDTH_FRF   2
#define SPI_CR0_BIT_WIDTH_SPO   1
#define SPI_CR0_BIT_WIDTH_SPH   1
#define SPI_CR0_BIT_WIDTH_SCR   8

#define SPI_CR1_ST_BIT_LBM      0
#define SPI_CR1_ST_BIT_SSE      1
#define SPI_CR1_ST_BIT_MS       2
#define SPI_CR1_ST_BIT_BIGEND   4
#define SPI_CR1_ST_BIT_WAITVAL  8
#define SPI_CR1_ST_BIT_WAITEN   15

#define SPI_CR1_BIT_WIDTH_LBM       1
#define SPI_CR1_BIT_WIDTH_SSE       1
#define SPI_CR1_BIT_WIDTH_MS        1
#define SPI_CR1_BIT_WIDTH_BIGEND    1
#define SPI_CR1_BIT_WIDTH_WAITVAL   7
#define SPI_CR1_BIT_WIDTH_WAITEN    1

#define SPI_INT_BIT_TX_FIFO_WATER_LINE (1<<3)
#define SPI_INT_BIT_RX_FIFO_WATER_LINE (1<<2)
#define SPI_INT_BIT_RX_FIFO_TIME_OUT   (1<<1)
#define SPI_INT_BIT_RX_FIFO_OVER_FLOW  (1<<0)

#define SPI_INT_BIT_RTIC (1<<1)
#define SPI_INT_BIT_RORIC (1<<0)

#define SPI_TX_DMAE (1<<1)
#define SPI_RX_DMAE (1<<0)

#define SPI_FIFO_LINE_OFFSET    3
#define SPI_FIFO_MAX_VAL        7
#define SPI_FIFO_LINE_MASK      0x7

#define SPI_UNUSE_DATA      0xFFFF

#define spi_get_transfer_size(burst) (((burst) == (DMA_BURST_MSIZE_1)) ? 1 : (1 << ((burst) + 1)))

#define MEM_TO_SPI 1
#define SPI_TO_MEM 2

#define SCR_MAX                 255
#define SCR_MIN                 0
#define CPSDVSR_MAX             254
#define CPSDVSR_MIN             4

#define SPI0_FIFO_LEN           256
#define SPI1_FIFO_LEN           64
#define SPI0_FIFO_THRESHOLD     128
#define SPI1_FIFO_THRESHOLD     32

#define SPI_HOST_TIMEOUT_US         1000000
#define SPI_HOST_TIMEOUT_MS         1000

#define SPI_SLAVE_TIMEOUT_US        10000000

#define SPI0_TX_FIFO_WATER_LINE     6
#define SPI0_RX_FIFO_WATER_LINE     6
#define SPI1_TX_FIFO_WATER_LINE     4
#define SPI1_RX_FIFO_WATER_LINE     3

#define SPI0_TX_FIFO_DMA_WLINE_64  7
#define SPI0_RX_FIFO_DMA_WLINE_128 6
#define SPI1_TX_FIFO_DMA_WLINE_16  4
#define SPI1_RX_FIFO_DMA_WLINE_32  4

/* 40 or 24M */
#define SPI_DEFAULT_CLK             160000000
#define spi_max_speed(clk) ((clk) / (((SCR_MIN) + 1) * (CPSDVSR_MIN)))
#define spi_min_speed(clk) ((clk) / (((SCR_MAX) + 1) * (CPSDVSR_MAX)))

#define SPI_WRITE_FLAG   0x1             /* 发送数据 */
#define SPI_READ_FLAG    0x2             /* 接收数据 */

#define GPIO_00_SEL 0x604
#define GPIO_01_SEL 0x608
#define GPIO_02_SEL 0x60c
#define GPIO_03_SEL 0x610

#define GPIO_05_SEL 0x618
#define GPIO_06_SEL 0x61c
#define GPIO_07_SEL 0x620
#define GPIO_08_SEL 0x624

#define GPIO_09_SEL 0x628
#define GPIO_10_SEL 0x62c
#define GPIO_11_SEL 0x630
#define GPIO_12_SEL 0x634

/**
 * SPI EVENT
 */
#define HI_EVENT_BIT_RX_DATA          0x1
#define HI_EVENT_BIT_TX_DATA          0x2
#define HI_EVENT_BIT_RX_DATA_TIME_OUT 0x4
#define HI_EVENT_BIT_RX_FIFO_OVER_FLOW 0x8

#define HI_EVENT_BIT_DMA_RX_DATA          0x10
#define HI_EVENT_BIT_DMA_RX_ERR_DATA      0x20
#define HI_EVENT_BIT_DMA_TX_DATA          0x40
#define HI_EVENT_BIT_DMA_TX_ERR_DATA      0x80

typedef enum {
    SPI_OPT_SET_CFG = 0x1,
    SPI_OPT_ENABLE_SPI = 0x2,
    SPI_OPT_DISABLE_SPI = 0x4,
    SPI_OPT_TASKED_SIGNAL = 0x8,
    SPI_OPT_SEND_FIX_DATA = 0x10,
    SPI_OPT_RCV_FIX_DATA = 0x20,
    SPI_OPT_WAIT_SIGNAL = 0x40,
    SPI_OPT_FREE_SIGNAL = 0x80,
} spi_opt;

/**
 * @ingroup hct_spi
 */
typedef enum {
    SPI_CFG_ROLE_MASTER,
    SPI_CFG_ROLE_SLAVE,
} spi_cfg_role;

/**
 * @ingroup hct_spi
 */
typedef enum {
    SPI_DATA_WIDTH_1BYTES = 1,
    SPI_DATA_WIDTH_2BYTES,
} spi_data_width;

/**
 * @ingroup hct_spi
 */
typedef enum {
    HI_SPI0_TX_FIFO_WATER_LINE_1,
    HI_SPI0_TX_FIFO_WATER_LINE_4,
    HI_SPI0_TX_FIFO_WATER_LINE_8,
    HI_SPI0_TX_FIFO_WATER_LINE_16,
    HI_SPI0_TX_FIFO_WATER_LINE_32,
    HI_SPI0_TX_FIFO_WATER_LINE_64,
    HI_SPI0_TX_FIFO_WATER_LINE_128,
    HI_SPI0_TX_FIFO_WATER_LINE_192,
} hi_spi0_tx_fifo_water_line;

/**
 * @ingroup hct_spi
 */
typedef enum {
    HI_SPI0_RX_FIFO_WATER_LINE_255,
    HI_SPI0_RX_FIFO_WATER_LINE_252,
    HI_SPI0_RX_FIFO_WATER_LINE_248,
    HI_SPI0_RX_FIFO_WATER_LINE_240,
    HI_SPI0_RX_FIFO_WATER_LINE_224,
    HI_SPI0_RX_FIFO_WATER_LINE_192,
    HI_SPI0_RX_FIFO_WATER_LINE_128,
    HI_SPI0_RX_FIFO_WATER_LINE_32,
} hi_spi0_rx_fifo_water_line;
/**
 * @ingroup hct_spi
 */
typedef enum {
    HI_SPI1_TX_FIFO_WATER_LINE_1,
    HI_SPI1_TX_FIFO_WATER_LINE_4,
    HI_SPI1_TX_FIFO_WATER_LINE_8,
    HI_SPI1_TX_FIFO_WATER_LINE_16,
    HI_SPI1_TX_FIFO_WATER_LINE_32,
    HI_SPI1_TX_FIFO_WATER_LINE_48,
    HI_SPI1_TX_FIFO_WATER_LINE_56,
    HI_SPI1_TX_FIFO_WATER_LINE_64,
} hi_spi1_tx_fifo_water_line;
/**
 * @ingroup hct_spi
 */
typedef enum {
    HI_SPI1_RX_FIFO_WATER_LINE_65,
    HI_SPI1_RX_FIFO_WATER_LINE_62,
    HI_SPI1_RX_FIFO_WATER_LINE_48,
    HI_SPI1_RX_FIFO_WATER_LINE_32,
    HI_SPI1_RX_FIFO_WATER_LINE_16,
    HI_SPI1_RX_FIFO_WATER_LINE_8,
    HI_SPI1_RX_FIFO_WATER_LINE_4,
    HI_SPI1_RX_FIFO_WATER_LINE_1,
} hi_spi1_rx_fifo_water_line;

typedef struct {
    hi_u16 cr0;
    hi_u16 cr1;
    hi_u16 cpsdvsr;
} spi_inner_cfg;

typedef struct {
    hi_u16 data_width : 4;
    hi_u16 fram_mode : 2;
    hi_u16 cpol : 1;
    hi_u16 cpha : 1;
    hi_u16 scr : 8;
    hi_u16 loop_back : 1;
    hi_u16 reserver_1 : 1;
    hi_u16 is_slave : 1;
    hi_u16 reserver_2 : 1;
    hi_u16 endian : 1;
    hi_u16 reserver_3 : 11;
    hi_u16 cpsdvsr;
    hi_u16 rx_fifo_line;
    hi_u16 tx_fifo_line;
    hi_u16 rx_fifo_dma_line;
    hi_u16 tx_fifo_dma_line;
    hi_u16 pad;
} spi_hw_cfg;

typedef struct {
    hi_u32 time_out_ms;
    hi_u32 trans_opt;
} spi_trans_attr;

typedef struct {
    hi_pvoid buf;
    volatile hi_u32 cur_pos;
    volatile hi_u32 cur_cnt;
} spi_buf;

typedef struct {
    hi_u32 reg_base;
    hi_u32 irq_num;
    hi_u32 sem_id;
    hi_u32 event_id;
    hi_bool use_dma;
    hi_bool use_irq;
    volatile hi_bool transferring;
    volatile hi_bool disable_later;
    hi_spi_usr_func prepare_func;
    hi_spi_usr_func restore_func;
    spi_hw_cfg spi_cfg;
    hi_u32 single_len;
    hi_u32 trans_len;
    spi_buf tx_buf;
    spi_buf rx_buf;
} spi_ctrl;

HI_EXTERN spi_ctrl *g_spi_ctrl[SPI_NUM];

hi_void spi_isr(spi_ctrl *spi_dev_ctrl);
hi_void spi_isr_enable(hi_u32 reg_base, hi_u16 enable_bits);
hi_void spi_isr_disable(hi_u32 reg_base, hi_u16 disable_bits);
hi_u32 spi_trans_prepare(spi_ctrl *spi_hw_ctrl, spi_trans_attr *trans_attr);
hi_void spi_trans_restore(spi_ctrl *spi_hw_ctrl, const spi_trans_attr *trans_attr);
hi_u32 spi_transfer_8bits_block(const spi_ctrl *spi_hw_ctrl, hi_u32 options);
hi_u32 spi_transfer_16bits_block(const spi_ctrl *spi_hw_ctrl, hi_u32 options);
hi_void spi_set_fifo_line(const spi_ctrl *spi_hw_ctrl);
hi_u32 spi_config(const spi_ctrl *spi_hw_ctrl);
hi_void spi_reset(const spi_ctrl *spi_hw_ctrl);
hi_void spi_disable(spi_ctrl *ctrl);
hi_void spi_flush_fifo(hi_u32 reg_base);

hi_void spi_isr_clear_cr(hi_u32 reg_base, hi_u16 clear_bit);
#ifdef CONFIG_SPI_DMA_SUPPORT
hi_u32 spi_hd_dma_read_fifo(spi_ctrl *spi_dev_ctrl, hi_u32 timeout_ms);
hi_u32 spi_hd_dma_write_fifo(spi_ctrl *spi_dev_ctrl, hi_u32 timeout_ms);
hi_void spi_set_dma_fifo_line(const spi_ctrl *spi_hw_ctrl);
hi_void spi_dma_enable(hi_u32 reg_base, hi_u16 enable_bits);
hi_void spi_dma_disable(hi_u32 reg_base, hi_u16 disable_bits);
#endif

#endif
