/**
* @file hi_dma.h
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
*
* 描述：DMA module. CNcomment:DMA调用接口。CNend
* @li The DMA transfer is realized by calling internal DMA driver.
CNcomment:通过调用内部DMA驱动实现DMA传输CNend
* @li Supports four transmission modes: Memory to storage, memory to peripheral, peripheral to memory,
and peripheral to peripheral.CNcomment:支持存储器到存储器、存储器到外设、外设到存储器、
外设到外设四种传输方式CNend
* @li The DMA has four channels. If there is no idle channel, the HI_ERR_DMA_BUSY error is returned.
CNcomment:DMA共有4通道，无空闲通道时返回HI_ERR_DMA_BUSY错误CNend
* @li The callback function is executed in the interrupt context, so you need to comply with the programming
precautions for the interrupt context.CNcomment:回调函数执行在中断上下文，
因此需要遵守中断上下文的编程注意事项。CNend
* @li Before enabling the DMA channel, you need to set the channel parameters. After the channel parameters
are enabled and then modified, an unpredictable result is generated.CNcomment:在DMA通道使能前需设置完通道参数，
使能通道后再修改通道参数会产生无法预知的结果。CNend \n
*/

/** @defgroup iot_dma DMA
 *  @ingroup drivers
 */

#ifndef _HI_DMA_H
#define _HI_DMA_H

#include <hi_types.h>
#include "hi_mdm_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup iot_dma
 *
 * DMA Interruption type. CNcomment: DMA 中断类型。CNend
 */
 /* 传输完成中断类型 */
#define DMA_INT_TC  1
/* 传输错误中断类型 */
#define DMA_INT_ERR 2

/**
 * @ingroup iot_dma
 *
 * DMA transfer bit width. CNcomment:DMA传输位宽。CNend
 */
typedef enum {
    WIDTH_BIT8 = 0,
    WIDTH_BIT16,
    WIDTH_BIT32,
} hi_dma_data_width;

/**
 * @ingroup iot_dma
 *
 * DMA configuration structure transferred. CNcomment:用户传入的DMA设置结构体。CNend
 */
typedef struct hi_dma_user_para {
    hi_u32 ch_idx;         /* 接收DMA传输使用的channel id，不需用户设置, 通道申请成功时赋值 */
    uintptr_t src_addr;    /* 源地址，源地址必须4字节对齐 */
    uintptr_t dst_addr;    /* 目标地址，目的地址必须4字节对齐 */
    hi_u32 size_bytes;     /* 传输长度，以BYTE单位 */
    hi_void (*cb)(hi_u32);  /* 传输结束回调，参数为传输完成或传输错误 #DMA_INT_XXX */
} hi_dma_user_para;

/**
* @ingroup  iot_dma
* @brief  Create the dma transmission linked list. CNcomment:创建dma传输链表。CNend
*
* @par 描述:
*           Create the dma transmission linked list. CNcomment:创建dma传输链表，分配通道。CNend
*           After the command is executed successfully, the channel resources are allocated.
*           If the channel resources are not transmitted, the hi_dma_ch_close(usr_para->ch_idx) is invoked to
*           release the channels. CNcomment:执行成功后会分配通道资源，如果没有实际进行传输需要调用
hi_dma_ch_close(usr_para->ch_idx)释放通道。CNend
*
* @attention
* @param  usr_para         [IN/OUT] type #hi_dma_user_para，Transfer DMA transfer parameter settings
CNcomment:传入DMA传输参数设置。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 hi_dma_create_link_list(hi_dma_user_para *usr_para);

/**
* @ingroup  iot_dma
* @brief  Insert the DMA transmission linked list at behind. CNcomment:dma传输链表末尾添加结点。CNend
*
* @par 描述:
*           Insert the DMA transmission linked list at behind. CNcomment:dma传输链表末尾添加结点CNend
*
* @attention
* @param  usr_para         [IN] type #const hi_dma_user_para，Transfer DMA transfer parameter settings.
CNcomment:传入DMA传输参数设置。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 hi_dma_add_link_list_item(const hi_dma_user_para *usr_para);

/**
* @ingroup  iot_dma
* @brief  Start DMA linked list transmission. CNcomment:启动dma链表传输。CNend
*
* @par 描述:
*           Start DMA linked list transmission, channel would be released, no matter about the result.
CNcomment:启动dma链表传输，成功或失败后会释放通道。CNend
*
* @attention
* @param  ch_num           [IN]     type #hi_u32，Linked list transmission channel.
This parameter is assigned by the API when a linked list is created.
CNcomment:链表传输通道，创建链表时API内部赋值。CNend
* @param  block            [IN]     type #hi_bool，Indicates whether to block waiting for transmission completion.
CNcomment:是否阻塞等待传输完成。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 hi_dma_link_list_transfer(hi_u32 ch_num, hi_bool block);

/**
* @ingroup  iot_dma
* @brief  Data transmission from the memory to the memory through DMA.
CNcomment:通过DMA进行存储器到存储器数据传输。CNend
*
* @par 描述:
*           Data transmission from the memory to the memory through DMA.
CNcomment:通过DMA进行存储器到存储器数据传输。CNend
*
* @attention
* @param  dst_addr         [IN]     type #hi_u32，Destination address, which must be 4-byte-aligned.
CNcomment:目标地址，需4字节对齐。CNend
* @param  src_addr         [IN]     type #hi_u32，Source address, which must be 4-byte-aligned.
CNcomment:源地址，需4字节对齐。CNend
* @param  size_bytes       [IN]     type #hi_u32，Transmission length, in bytes.
CNcomment:传输长度，以BYTE为单位。CNend
* @param  block            [IN]     type #hi_bool，Indicates whether to block waiting for transmission completion.
CNcomment:是否阻塞等待传输完成。CNend
* @param  cb_func          [IN]     type #hi_void，Callback function for non-blocking transmission.
The parameter is the DMA interrupt type. Set this parameter to HI_NULL when blocking transmission.
CNcomment:非阻塞传输的回调函数，参数为DMA中断类型，阻塞传输时设为HI_NULL。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #HI_ERR_DMA_BUSY Channel busy. CNcomment:通道全忙。CNend
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 hi_dma_mem2mem_transfer(hi_u32 dst_addr, hi_u32 src_addr, hi_u32 size_bytes,
                               hi_bool block, hi_void (*cb_func)(hi_u32 int_type));

/**
* @ingroup  iot_dma
* @brief  Disables the DMA specified channel. CNcomment:关闭DMA指定通道。CNend
*
* @par 描述:
*           Disables the DMA specified channel and release rource.
CNcomment:关闭DMA指定通道并释放资源。CNend
*
* @attention None
* @param  ch_num           [IN]     type #hi_u32，DMA channel ID. Value range: 0-3.
CNcomment:DMA通道ID 取值0~3。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  hi_dma_create_link_list。
 */
hi_u32 hi_dma_ch_close(hi_u32 ch_num);

/**
* @ingroup  iot_dma
* @brief  DMA module initialization.CNcomment:DMA模块初始化。CNend
*
* @par 描述:
*           DMA module initialization, apply for rources. CNcomment:DMA模块初始化, 申请资源。CNend
*
* @attention None
* @param  None
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_u32 hi_dma_init(hi_void);

/**
* @ingroup  iot_dma
* @brief  Deinitializes the DMA module. CNcomment:DMA模块去初始化。CNend
*
* @par 描述:
*           Deinitializes the DMA module and release rources. CNcomment:DMA模块去初始化，释放资源。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
*/
hi_void hi_dma_deinit(hi_void);

/**
* @ingroup  iot_dma
* @brief  Judge is DMA module init. CNcomment:DMA模块是否初始化。CNend
*
* @par 描述:
*           Is DMA module init. CNcomment:DMA模块是否初始化。CNend
*
* @attention None
* @param  None
*
* @retval #HI_TURE   dma has been initialized.
* @retval #HI_FALSE  DMA has not been initialized.
* @par 依赖:
*            @li hi_dma.h：   Describes DMA driver APIs. CNcomment:DMA驱动实现接口。CNend
* @see  None
 */
hi_bool hi_dma_is_init(hi_void);

#ifdef __cplusplus
}
#endif

#endif
