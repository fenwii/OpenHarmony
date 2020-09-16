/**
 * @file hi_config.h
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

#ifndef __HI_CONFIG_H__
#define __HI_CONFIG_H__
/*****************************************************************************/
#include <hi_types_base.h>

/*
 * Global module/submodule ID setting.CNcomment:全局模块/子模块ID设置
 * Note that HI_MOD_MAX_NUM needs to be increased or decreased after the number of modules is increased or decreased.
 * CNcomment:注意增减模块个数后，需要增减 HI_MOD_MAX_NUM
 * SAL : [200, 300)
 * BSP : [300, 400)   -- [12c, 190)
 * MAC : [500, 600)   -- [1F4, 258)
 * APP : [800, 900)   -- [320, 384)
 */
#ifndef PRODUCT_CFG_DIAG_MODULE_ID_MAX_NUM
#define PRODUCT_CFG_DIAG_MODULE_ID_MAX_NUM 60
#endif
#define HI_MOD_MAX_NUM    (PRODUCT_CFG_DIAG_MODULE_ID_MAX_NUM) /* Number of Modules */

/* SAL: [200,  300) */
#define HI_MOD_ID_SAL_SYS    201
#define HI_MOD_ID_SAL_NVM    203
#define HI_MOD_ID_SAL_DIAG   204
#define HI_MOD_ID_SAL_DFX    205
#define HI_MOD_ID_CPUP_DFX   210
#define HI_MOD_ID_CIPHER     211

/* BSP: [300, 400) */
#define HI_MOD_ID_DRV        300 /* 0x12C */
#define HI_MOD_ID_DRV_SPI    307 /* 0x133 */
#define HI_MOD_ID_DRV_DMA    316 /* 0x13c */
#define HI_MOD_ID_UPG        317
#define HI_MOD_ID_CRYPTO     318
#define HI_MOD_ID_I2S        319
#define HI_MOD_ID_UART       320
#define HI_MOD_ID_WIFI_DRV       400 /* 0x190 */

/* APP : [800, 900) */
#define HI_MOD_ID_APP_COMMON 812 /* 32C */
#define HI_MOD_ID_APP_AT     813 /* 32C */

/* Module name size in bytes */
#define HI_SYS_MOD_NAME_LEN 16
#ifdef __NEW_FILE_ID__
#define HI_DIAG_LOG_MSG_MOD_ID  __NEW_MOD_ID__
#define HI_DIAG_LOG_MSG_FILE_ID __NEW_FILE_ID__
#else
#define HI_DIAG_LOG_MSG_MOD_ID  0
#define HI_DIAG_LOG_MSG_FILE_ID 0
#endif

/* Maximum size of a single DIAG packet buffer.CNcomment:DIAG包缓存单包最大大小设置 */
#define HI_DIAG_BUFFERING_MSG_MAX_LEN 100
#define HI_DIAG_BUFFERING_CMD_MAX_LEN 100

/* Sets the buffer queue size in a DAIG channel. CNcomment:DAIG 通道中缓存队列大小设置 */
/* Messages,if the memory usage is greater than the threshold, the memory is dynamically allocated.
   CNcomment:消息 大于该门限则动态分配内存 */
#define HI_DIAG_BUFFERING_MSG_NUM 5
/* Command,if the memory usage is greater than the threshold, the memory is dynamically allocated.
   CNcomment:命令 大于该门限则动态分配内存 */
#define HI_DIAG_BUFFERING_CMD_NUM 2


/*****************************************************************************
 Global Static Settings
 *****************************************************************************/
#define HI_MAC_ADDR_LEN      6

/* Maximum size of the received DIAG packet, including the channel frame header and payload.
   CNcomment:接收DIAG包最大大小，包括通道帧头和payload */
#define HI_DIAG_PACKET_REQ_CACHE_MAX_SIZE 320
#define HI_DIAG_PACKET_ACK_MAX_SIZE       1024
#define HI_DIAG_PACKET_REQ_DATA_MAX_SIZE  320

/* Task waiting exception. */
#define HI_SYS_TASK_WAIT_EXCEPTION_TIME_OUT 10000

/* The total size of the RAM */
HI_EXTERN hi_u32 g_halSectorsRamSize;
/* The start address of RAM */
HI_EXTERN hi_void *g_halSectorsRamStart;

#define hi_is_valid_ram_addr(_x) (((hi_u32)(_x) >= (hi_u32)(uintptr_t)g_halSectorsRamStart) && \
    ((hi_u32)(_x) < ((hi_u32)(uintptr_t)g_halSectorsRamStart + (uintptr_t)g_halSectorsRamSize)))
#define hi_is_valid_code_addr(_x) (_x)


/*******************************************************************************
   NV range
 *****************************************************************************/
/**
* @ingroup  iot_nv
*
* Factory NV area start ID (including this ID).CNcomment:工厂NV区起始ID（包含此ID）。CNend
*/
#define HI_NV_FACTORY_ID_START      0x0

/**
* @ingroup  iot_nv
*
* Factory NV area end ID (not included).CNcomment:工厂NV区结束ID（不包含此ID）。CNend
*/
#define HI_NV_FACTORY_ID_END        0x16

/**
* @ingroup  iot_nv
*
* Factory NV user area start ID (including this ID).CNcomment:工厂NV区用户区起始ID（包含此ID）。CNend
*/
#define HI_NV_FACTORY_USR_ID_START   HI_NV_FACTORY_ID_END

/**
* @ingroup  iot_nv
*
* Factory NV user area end ID (not included).CNcomment:工厂NV区用户区结束ID（不包含此ID）。CNend
*/
#define HI_NV_FACTORY_USR_ID_END    0x20

/**
* @ingroup  iot_nv
*
* Non factory NV area start ID (including this ID).CNcomment:非工厂NV区起始ID（包含此ID）。CNend
*/
#define HI_NV_NORMAL_ID_START        HI_NV_FACTORY_USR_ID_END

/**
* @ingroup  iot_nv
*
* Non factory NV user area end ID (not included).CNcomment:非工厂NV区结束ID（不包含此ID）。CNend
*/
#define HI_NV_NORMAL_ID_END          0x80

/**
* @ingroup  iot_nv
*
* Non factory NV Upgrade Reserved area start ID (including this ID).CNcomment:非工厂NV升级保留区起始ID(包含此ID)。CNend
*/
#define HI_NV_STABLE_ID_START         HI_NV_NORMAL_ID_END

/**
* @ingroup  iot_nv
*
* Non factory NV Upgrade Reserved area end ID (not included).CNcomment:非工厂NV升级保留区结束ID(不包含此ID)。CNend
*/
#define HI_NV_STABLE_ID_END           0x98

/**
* @ingroup  hct_nv
*
* Non factory NV user Upgrade Reserved area start ID (including this ID).
  CNcomment:非工厂NV升级保留区用户区起始ID(包含此ID)。CNend
*/
#define HI_NV_STABLE_USR_ID_START     HI_NV_STABLE_ID_END

/**
* @ingroup  iot_nv
*
* Non factory NV user Upgrade Reserved area end ID (not included).
  CNcomment:非工厂NV升级保留区用户区结束ID(不包含此ID)。CNend
*/
#define HI_NV_STABLE_USR_ID_END       0xA0

/**
* @ingroup  iot_nv
*
* Non factory NV user Reserved area start ID (including this ID).CNcomment:非工厂NV区用户预留区起始ID(包含此ID)。CNend
*/
#define HI_NV_NORMAL_USR_ID_START     HI_NV_STABLE_USR_ID_END

/**
* @ingroup  hct_nv
*
* Non factory NV user Reserved area end ID (including this ID).CNcomment:非工厂NV区用户预留区结束ID(包含此ID)。CNend
*/
#define HI_NV_NORMAL_USR_ID_END       0xFF

/*****************************************************************************
 Channel Settings
*****************************************************************************/
/* UART port number supported by the DIAG channel. The value must be smaller than the value of
   HI_DMS_CHL_UART_PORT_NUM_MAX. CNcomment:DIAG通道支持的UART端口号, 必须小于 HI_DMS_CHL_UART_PORT_NUM_MAX */
#define HI_DMS_CHL_UART_PORT_DIAG 1 /*  */
#define HI_DMS_CHL_PORT_ANY     0xFFF0

#define HI_DIAG_CHL_UART_BLOCK_WRITE_TIMEOUT 10    /* ms block write timeout */
#define HI_DMS_CHL_UART_BLOCK_WRITE_TIMEOUT  10    /* ms block write timeout */
#define HI_DMS_CHL_EXCEPTION_POLLING_WAIT    5000  /* ms task read dev task waiting exception Sleep */
#define HI_DMS_CHL_FLASH_BLOCK_WRITE_TIMEOUT 10    /* ms block write timeout */
#define HI_DMS_UART_EXCEPTION_POLLING_WAIT   1000  /* ms UART waiting exception Sleep */
#define HI_DMS_CHL_CONNECT_DETECT_NUM        3     /* Number of client detection failures in heartbeat
                                                      mode after the channel is connected */
#define HI_DMS_CHL_REPORT_PACKET_TIMEOUT     10    /* Batch report delay */
#define HI_DIAG_MODULE_SYS                   5     /* MSG SYS numbers of configurable categories */
#define HI_DIAG_MODULE_DEV                   30    /* MSG DEV numbers of configurable Module */
#define HI_DIAG_MODULE_USR                   5     /* MSG USR numbers of configurable categories */

#ifndef PRODUCT_CFG_DIAG_MSG_CFG_MAX_NUM
#define PRODUCT_CFG_DIAG_MSG_CFG_MAX_NUM     10
#endif
#define HI_DIAG_MSG_ID_NUM (PRODUCT_CFG_DIAG_MSG_CFG_MAX_NUM)  /* Number of configuration messages */

#define HI_DIAG_WAIT_MESSAGE_TIMEOUT         50  /* ms */
#define HI_DIAG_WAI_DIAG_MESSAGE_TIMEOUT     100 /* Minimum interval for reporting DIAG packets. ms */

/* Definition range of system diagnosis IDs.CNcomment:系统诊断ID定义范围 */
#define HI_DFX_STAT_ID_BASE_SYS 0xA000  /* SYS STAT的包ID范围: [0xA000, 0xF000) */
#define HI_DFX_STAT_ID_MAX_SYS  0xF000

/* MSG SYS USR Subcategory Definition(16bit) */
#define HI_MSG_SYS_L0 0xff10 // MSG SYS Level0
#define HI_MSG_SYS_L1 0xff20 // MSG SYS Level1
#define HI_MSG_SYS_L2 0xff01 // MSG SYS Level2

#define HI_MSG_USR_L0 0xf3e8 // MSG USR Level0
#define HI_MSG_USR_L1 0xf3e9 // MSG USR Level1
#define HI_MSG_USR_L2 0xf3ea // MSG USR Level2
#define HI_MSG_USR_L3 0xf3eb // MSG USR Level3
#define HI_MSG_USR_L4 0xf3ec // MSG USR Level4

#define DIAG_PROC_TASK_STACK_SIZE    2048
#define DIAG_UART_TASK_STACK_SIZE    1536
#define FLASH_PROTECT_TASK_STACK_SIZE 1024
#define DATA_COLLECT_TASK_STACK_SIZE 2048    /* this statck will destroy after dc finish */

#ifdef HI_BOARD_ASIC
#define DIAG_QUEUE_MSG_NUM           48
#else
#define DIAG_QUEUE_MSG_NUM           100
#endif
#define DIAG_PROC_TASK_PRIO          25
#define DIAG_UART_TASK_PRIO          20
#define FLASH_PROTECT_TASK_PRIO      1
#define DATA_COLLECT_TASK_PRIO       21

#define HI_MILLISECOND_PER_TICK  10

#define PRODUCT_CFG_FLASH_BLOCK_SIZE             0x1000
#define PRODUCT_CFG_AUTO_WDG_RESET_SYSTEM_TIMEOUT    30000

#if (PRODUCT_CFG_AUTO_WDG_RESET_SYSTEM_TIMEOUT < 6500)
#error "watchdog timeout value must be more than 6500ms!"
#endif

#define PRODUCT_CFG_DEEP_SLEEP_DEFAULT_MAX_MS    (0xFFFFFFFF / 64)

#endif /* __HI_CONFIG_H__ */

