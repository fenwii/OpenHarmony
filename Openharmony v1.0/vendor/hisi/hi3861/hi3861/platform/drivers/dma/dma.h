/**
 * @file dma.h
 *
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

/** @defgroup hct_dma
 *  @ingroup drivers
 */

#ifndef _DMA_H_
#define _DMA_H_

#include <hi_types_base.h>
#include <hi_dma.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef DMA_DEBUG
#define dma_print(fmt...)       \
    do {                        \
        printf(fmt);            \
        printf("\r\n"); \
    } while (0)
#else
#define dma_print(fmt...)
#endif

/* DMA registers address */
#define DMA_BASE_ADDR          0x40200000
#define DMA_INT_STAT           (DMA_BASE_ADDR + 0x000)
#define DMA_INT_TC_STAT        (DMA_BASE_ADDR + 0x004)
#define DMA_INT_TC_CLR         (DMA_BASE_ADDR + 0x008)
#define DMA_INT_ERR_STAT       (DMA_BASE_ADDR + 0x00C)
#define DMA_INT_ERR_CLR        (DMA_BASE_ADDR + 0x010)
#define DMA_RAW_INT_TC_STATUS  (DMA_BASE_ADDR + 0x014)
#define DMA_RAW_INT_ERR_STATUS (DMA_BASE_ADDR + 0x018)
#define DMA_ENBLD_CHNS         (DMA_BASE_ADDR + 0x01C)
#define DMA_SOFT_BREQ          (DMA_BASE_ADDR + 0x020)
#define DMA_SOFT_SREQ          (DMA_BASE_ADDR + 0x024)
#define DMA_SOFT_LBREQ         (DMA_BASE_ADDR + 0x028)
#define DMA_SOFT_LSREQ         (DMA_BASE_ADDR + 0x02C)
#define DMA_CFG_REG            (DMA_BASE_ADDR + 0x030)
#define DMA_SYNC               (DMA_BASE_ADDR + 0x034)
/* Source Address Register for Channel x */
#define dma_sar(x) (DMA_BASE_ADDR + 0x100 + (x)*0x020)
/* Destination Address Register for Channel x */
#define dma_dar(x) (DMA_BASE_ADDR + 0x104 + (x)*0x020)
/* Linked List Pointer Register for Channel x */
#define dma_lli(x) (DMA_BASE_ADDR + 0x108 + (x)*0x020)
/* Control Register for Channel x */
#define dma_ctl(x) (DMA_BASE_ADDR + 0x10C + (x)*0x020)
/* Configuration Register for Channel x */
#define dma_cfg(x) (DMA_BASE_ADDR + 0x110 + (x)*0x020)

#define DMA_MASK_INT   0
#define DMA_UNMASK_INT 1

#define DMA_CHANNEL_0 0x01
#define DMA_CHANNEL_1 0x02
#define DMA_CHANNEL_2 0x04
#define DMA_CHANNEL_3 0x08

#define DMA_CHANNEL_NUM_0 0
#define DMA_CHANNEL_NUM_1 1
#define DMA_CHANNEL_NUM_2 2
#define DMA_CHANNEL_NUM_3 3

#define DMA_CHANNEL_NUM 4

#define DMA_DISABLE 0
#define DMA_ENABLE  1

#define DMA_TR_ADDR_INCREMENT 1
#define DMA_TR_ADDR_NOCHANGE  0

#define DMA_WORD_WIDTH 4

#define DMA_TS_MAX 4095
#define DMA_TS_BLOCK 4092

#define DMA_TRANSFER_COMPLETE   0
#define DMA_TRANSFER_INCOMPLETE 1
#define DMA_TRANSFER_ERR        2

#define DMA_TIMEOUT_US 50000

#define dma_pkt_b_to_dma_addr(_virt_addr) ((hi_u32)(_virt_addr) + PKT_B_OFFSET)
#define dma_pkt_h_to_dma_addr(_virt_addr) ((hi_u32)(_virt_addr) + PKT_H_OFFSET)

#define DCACHE_ENABLE 1
#define DCACHE_EN_REG 0x7C1

/**
 * @ingroup hct_dma
 *
 * DMA transfer mode. CNcomment:DMA传输模式。CNend
 */
typedef enum {
    DMA_MEM_TO_MEM = 0,
    DMA_MEM_TO_PHL,
    DMA_PHL_TO_MEM,
    DMA_PHL_TO_PHL,
} hi_dma_tr_type;

/**
 * @ingroup hct_dma
 *
 * Peripheral ID that supports DMA transfer. CNcomment:支持DMA传输的外设ID。CNend
 */
typedef enum {
    UART0_RX = 0,
    UART0_TX,
    UART1_RX,
    UART1_TX,
    UART2_RX,
    UART2_TX,
    SPI0_RX,
    SPI0_TX,
    SPI1_RX,
    SPI1_TX,
    I2S0_RX,
    I2S0_TX,
    PHL_MAX,
} hi_dma_phl;

/**
 * @ingroup hct_dma
 *
 * One DMA burst transmission length. CNcomment:一次DMA burst传输长度。CNend
 */
typedef enum {
    DMA_BURST_MSIZE_1 = 0,
    DMA_BURST_MSIZE_4,
    DMA_BURST_MSIZE_8,
    DMA_BURST_MSIZE_16,
    DMA_BURST_MSIZE_32,
    DMA_BURST_MSIZE_64,
    DMA_BURST_MSIZE_128,
    DMA_BURST_MSIZE_256,
} hi_dma_burst_size;

typedef union dma_ch_sel {
    struct {
        hi_u32 channel_0 : 1;
        hi_u32 channel_1 : 1;
        hi_u32 channel_2 : 1;
        hi_u32 channel_3 : 1;
        hi_u32 reserved : 28;
    } ch_bit;
    hi_u32 ch_set_u32;
} dma_ch_sel;

typedef union dma_init_cfg {
    struct {
        hi_u32 dma_en : 1;
        hi_u32 master1_endianness : 1;
        hi_u32 master2_endianness : 1;
        hi_u32 reserved : 29;
    } dma_cfg_bit;
    hi_u32 dma_cfg_u32;
} dma_init_cfg;

typedef union dma_ch_cfg {
    struct {
        hi_u32 en : 1;
        hi_u32 src_peripheral : 4;
        hi_u32 reserved0 : 1;
        hi_u32 dst_peripheral : 4;
        hi_u32 reserved1 : 1;
        hi_u32 flow_cntrl : 3;
        hi_u32 err_int_mask : 1;
        hi_u32 tc_int_mask : 1;
        hi_u32 lock : 1;
        hi_u32 active : 1;
        hi_u32 halt : 1;
        hi_u32 reserved2 : 13;
    } ch_cfg_bit;
    hi_u32 ch_cfg_u32;
} dma_ch_cfg;

typedef union dma_llp {
    struct {
        hi_u32 lms : 1;
        hi_u32 reserved : 1;
        hi_u32 loc : 30;
    } llp_bit;
    hi_u32 llp_u32;
} dma_llp;

typedef struct dma_channel_para dma_channel_para_t;

/**
 * @ingroup dma
 *
 * The channel control register structure of DMA. CNcomment:DMA 通道控制寄存器结构。CNend
 */
typedef struct dma_ch_ctl_t dma_ch_ctl;
typedef union dma_ch_ctl {
    struct {
        hi_u32 transfer_size : 12;
        hi_u32 src_burst_size : 3;
        hi_u32 dst_burst_size : 3;
        hi_u32 src_width : 3;
        hi_u32 dst_width : 3;
        hi_u32 master_src_sel : 1;
        hi_u32 master_dst_sel : 1;
        hi_u32 src_inc : 1;
        hi_u32 dst_inc : 1;
        hi_u32 prot : 3;
        hi_u32 lli_tc_int_en : 1;
    } ch_ctl_bit;
    hi_u32 ch_ctl_u32;
} dma_ch_ctl_t;

/**
 * @ingroup dma
 *
 * The link structure of DMA link list item. CNcomment:DMA link list item链表结构。CNend
 */
typedef struct dma_lli_stru dma_lli_stru_t;
typedef struct dma_lli_stru {
    hi_u32 saddr;
    hi_u32 daddr;
    dma_lli_stru_t *llp_next;
    dma_ch_ctl_t st_ctl;
} dma_lli_stru_t;

typedef struct dma_channel_para {
    dma_llp llp;
    dma_ch_ctl_t ch_ctl;
    dma_ch_cfg ch_cfg;
    hi_void (*cb)(hi_u32);
    volatile hi_u32 is_transfering;
    dma_lli_stru_t *ch_lli;
} dma_channel_para;

typedef struct dma_data {
    hi_bool is_inited;
    volatile hi_u32 ch_mask;
    dma_channel_para ch_data[DMA_CHANNEL_NUM];
} dma_data;

/**
 * @ingroup hct_dma
 *
 * The general setting structure of the user's incoming DMA. It is used for the transmission participated by IO.
 CNcomment:用户传入DMA的通用设置结构，主要用于外设参与的传输。CNend
 */
typedef struct hi_dma_para {
    hi_u32 tr_type;
    hi_u32 src_phl;
    hi_u32 dst_phl;
    uintptr_t src_addr;
    uintptr_t dst_addr;
    hi_u32 src_burst_size;
    hi_u32 dst_burst_size;
    hi_u32 src_width;
    hi_u32 dst_width;
    hi_u32 transfer_size;
    hi_void (*cb)(hi_u32);
} hi_dma_para;

/**
* @ingroup  hct_dma
* @brief  Start dma transmission. CNcomment:启动dma传输。CNend
*
* @par 描述:
*           Start dma transmission and channel will be released after success or failure.
CNcomment:启动dma传输，成功或失败后会释放通道。CNend
*
* @attention
* @param  dma_para         [IN/OUT] type #hi_dma_user_para_sSetting incoming dma transfer parameter.
CNcomment:传入DMA传输参数设置。CNend
* @param  block            [IN]     type #hi_bool，Whether to block for waiting dma tranmission completeness
CNcomment:是否阻塞等待DMA传输完成。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   DMA driver implementation interface.  CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 hi_dma_transfer(const hi_dma_para *dma_para, hi_bool block);
/**
* @ingroup  hct_dma
* @brief  Start dma transmission. CNcomment:启动dma传输。CNend
*
* @par 描述:
*           Start dma transmission and channel will be released after success or failure.
CNcomment:启动dma传输，成功或失败后会释放通道。CNend
*
* @attention
* @param  dma_para         [IN/OUT] type #hi_dma_user_para_sSetting incoming dma transfer parameter.
CNcomment:传入DMA传输参数设置。CNend
* @param  dma_ch            [IN]     type #hi_bool，return dma channel number
CNcomment:返回申请的通道号。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   DMA driver implementation interface.  CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 dma_hw_request_transfer(const hi_dma_para *dma_para, hi_u32 *dma_ch);
void dma_write_data(hi_u32 ch_num, const hi_dma_para *dma_para);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
