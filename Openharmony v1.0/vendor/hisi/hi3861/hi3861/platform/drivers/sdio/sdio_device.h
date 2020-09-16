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
 *
 * Description: sdio driver implementatioin.
 */

#ifndef __SDIO_SLAVE_H__
#define __SDIO_SLAVE_H__

#include "hi_types_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define HI_SDIO_BASE_ADDR               0x40340000

#define SDIO_ESW_CCCR                   0x004   /* Card Common Control Registers */
#define SDIO_AMDA_SYS_ADDR              0x008
#define SDIO_ESW_CARD_RDY               0x00C
#define SDIO_ESW_FUN_RDY                0x010
#define SDIO_INTRPT_EN                  0x014
#define SDIO_INTRPT_STA                 0x018
#define SDIO_SOFT_RST_VALID             0x01C
#define SDIO_AHB_MEM_INT_EN             0x020
#define SDIO_AHB_MEM_INT_STA            0x024
#define SDIO_GLOBAL_INT_EN              0x028
#define SDIO_GLOBAL_INT_STA             0x02C
#define SDIO_CSA_PTR                    0x030
#define SDIO_IO_ACCESS_MODE             0x034
#define SDIO_UHS_SUPPORT                0x038
#define SDIO_CLK_DELAY_TIMER            0x03C
#define SDIO_POWER_CTRL                 0x040
#define SDIO_POWER_STA                  0x044

/* SDIO FN1 Registers Definition */
#define SDIO_ESW_IO_OCR                 0x104
#define SDIO_AHB_XFER_COUNT             0x10C
#define SDIO_XFER_COUNT                 0x110
#define SDIO_AHB_INT_STA                0x114
#define SDIO_AHB_INT_EN                 0x118
#define SDIO_ESW_FBR1                   0x11C
#define SDIO_ESW_IOR                    0x120
#define SDIO_HOST_MSG                   0x124
#define SDIO_ARM_HOST                   0x128
#define SDIO_FUN1_RD_DAT_RDY            0x12C
#define GPIO_FUNCTION3                  3
#define START_TYPE_EFUSE_ADDR           1072

#define SDIO_FUN1_CREDIT_INFO_BASE      0x13c
#define SDIO_FUN1_EXTEND_REG_BASE       0x140
#define SDIO_FUN1_EXTEND_REG_LEN        64

#define SDIO_MEM_ADMA_FETCH_ADDR        0x204

/* SDIO MEM */
#define SDIO_BLOCK_SIZE_REG             0x244
#define SDIO_ARGUMENT_REG               0x248

/* Block Size Reg */
#define BLK_SIZE_MSK                    (hi_u32)0x00000fff

/* Argument Reg */
#define BLKCNT_OR_BYTES_MSK             (hi_u32)0x000001ff
#define CMD53_ADDR_MSK                  ((hi_u32)0x0000ffff << 9)
#define CMD53_OPCODE                    BIT26
#define CMD53_BLK_MODE                  BIT27
#define CMD53_FUN_NUM                   (BIT28 | BIT29 | BIT30)
#define CMD53_RW_FLAG                   BIT31

/* SDIO_INTRPT */
#define AHBSOFT_RST_INT                 BIT0
#define VOLT_SWITCH_CMD_INT             BIT1
#define CMD19_RD_STRT                   BIT2
#define CMD19_RD_TRANS_OVER             BIT3
#define FN0_WR_START                    BIT4
#define FN0_WR_TRN_OVER                 BIT5
#define FN0_RD_START                    BIT6
#define FN0_RD_TRN_OVER                 BIT7
#define FN0_RD_TRN_ERR                  BIT8
#define FN0_ADMA_END_INT                BIT9
#define FN0_ADMA_INT                    BIT10
#define FN0_ADMA_ERR                    BIT11

/* global interrupt */
#define INT_FRM_SOFT_RESET              BIT0
#define INT_FRM_MEM                     BIT1
#define INT_FRM_FN1                     BIT2

/* AHB Interrupt */
#define FN1_WR_OVER                     BIT0
#define FN1_RD_OVER                     BIT1
#define FN1_RD_ERROR                    BIT2
#define FN1_RST                         BIT3
#define SD_HOST_FN1_MSG_RDY             BIT4
#define FN1_ACK_TO_ARM                  BIT5
#define FN1_SDIO_RD_START               BIT6
#define FN1_SDIO_WR_START               BIT7
#define FN1_ADMA_END_INT                BIT8
#define FN1_SUSPEND                     BIT9
#define FN1_RESUME                      BIT10
#define FN1_ADMA_INT                    BIT11
#define FN1_ADMA_ERR                    BIT12
#define FN1_EN_INT                      BIT13

/* UHS Support */
#define UHS_SUPPORT                     BIT0
#define DDR_DLY_SELECT                  BIT1
#define CARD_VOLT_ACCEPTED              BIT2
#define SD_CLK_LINE_SWITCHED            BIT3
#define SD_CMD_LINE_SWITCHED            BIT4

#define CCCR_REVISION                   3           /* 4Bit 0~3: 1.0, 1.1, 2.0, 3.0, */
#define SDIO_REVISION                   (4 << 4)    /* 4Bit 0~4: 1.0, 1.1, 1.2, 2.0, 3.0 */
#define SD_REVISION                     (3 << 8)    /* 4Bit 0~3: 1.0, 1.1, 2.0, 3.0, */
#define CCCR_SCSI                       (0 << 12)
#define CCCR_SDC                        (1 << 13)
#define CCCR_SMB                        (1 << 14)
#define CCCR_SRW                        (0 << 15)
#define CCCR_SBS                        (1 << 16)
#define CCCR_S4MI                       (1 << 17)
#define CCCR_LSC                        (0 << 18)
#define CCCR_4BLS                       (0 << 19)
#define CCCR_SMPC                       (1 << 20)
#define CCCR_SHS                        (1 << 21)
#define CCCR_MEM_PRE                    (2 << 22)

#define SDIO_ESW_CCCR_SET  (hi_u32) \
    (CCCR_REVISION | SDIO_REVISION | SD_REVISION| CCCR_SCSI | CCCR_SDC  | CCCR_SMB | CCCR_SRW| \
     CCCR_SBS | CCCR_S4MI | CCCR_LSC | CCCR_4BLS| CCCR_SMPC | CCCR_SHS  | CCCR_MEM_PRE)

#define SDIO_ESW_IO_OCR_SET             (hi_u32)(0x00ff8000) /* Bit23~Bit8: 3.6~2.0  0.1/bit */

/* ESW FBR1 Register */
#define IO_DEVICE_CODE1                 7         /* 4Bit 7:SDIO WLAN interface
                                                     SDIO Simplified Specification Version 3.00 Chapter 6.10 */
#define FUN_CSA_SUPPORT                 (0 << 4)  /* 1Bit */
#define EXT_IO_DEVICE_CODE1             (0 << 5)  /* 8Bit */
#define FBR1_SPS                        (0 << 13) /* 1Bit Function1 supports high power */

#define SDIO_ESW_FBR1_SET               (hi_u32)(IO_DEVICE_CODE1 | FUN_CSA_SUPPORT | EXT_IO_DEVICE_CODE1 | FBR1_SPS)

#define SDIO_IO_ACCESS_SET              (hi_u32)0xffffffff

#define SDIO_CLK_DELAY_SET              (hi_u32)0x2f92

#define SDIO_ADMA_STEP                  8
#define SDIO_ADMA_VALID                 BIT0
#define SDIO_ADMA_END                   BIT1
#define SDIO_ADMA_INT                   BIT2
#define SDIO_ADMA_NOP                   0
#define SDIO_ADMA_TRAN                  BIT5
#define SDIO_ADMA_LINK                  (BIT5 | BIT4)
#define SDIO_ADMA_PARAM_MASK            (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5)

/* SDIO soft reset offset and bit. */
#define SDIO_RESET_OFFSET               0x0020
#define SDIO_SOFT_RESET                 BIT3

#define SDIO_TRANS_BLK_SIZE             512
#define PADDING_BLK                     SDIO_TRANS_BLK_SIZE
#define PADDING_BYTE                    4
#define padding(x, size)                (((x) + (size) - 1) & (~ ((size) - 1)))
#define hisdio_align_4_or_blk(len)     ((len) < HISDIO_BLOCK_SIZE ? padding((len), 4) : \
                                        padding((len), HISDIO_BLOCK_SIZE))
#define hisdio_shift_check(a, b)        ((a) == (((a)<<(b))>>(b)))

typedef enum {
    MSG_FLAG_OFF    = 0,
    MSG_FLAG_ON     = 1,
} msg_flag;

typedef struct {
    hi_u32      reg;
    hi_u32      value;
} sdio_reg_store;

enum _hcc_netbuf_queue_type_ {
    HCC_NETBUF_NORMAL_QUEUE = 0, /* netbuf is shared with others */
    HCC_NETBUF_HIGH_QUEUE = 1, /* netbuf is special for high pri */
    HCC_NETBUF_QUEUE_BUTT
};

hi_void sdio_soft_reset_valid(hi_void);

#ifdef HI_BOARD_ASIC
#define NON_IOT_START_TYPE            0
#else
#define NON_IOT_START_TYPE            1
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of sdio_slave.h */
