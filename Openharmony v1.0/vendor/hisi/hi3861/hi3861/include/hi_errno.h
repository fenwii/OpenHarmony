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

#ifndef __HI_ERRNO_H__
#define __HI_ERRNO_H__

/*****************************************************************************
* 1、Common error code. Note: 0x8000 0000 is not recommended. If a truncation error occurs, it is considered successful.
* CNcomment:通用错误码。注意0x8000 0000最好别用，产生截断误判为成功
*****************************************************************************/
#define  HI_ERR_SUCCESS                                     0
#define  HI_ERR_FAILURE                                     (hi_u32)(-1)
#define  HI_ERR_S_FAILURE                                   (-1)
#define  HI_ERR_MALLOC_FAILUE                               0x80000001
#define  HI_ERR_TIMEOUT                                     0x80000002
#define  HI_ERR_RECVING                                     0x80000003
#define  HI_ERR_MEMCPY_S                                    0x80000004
#define  HI_ERR_MEMSET_S                                    0x80000005
#define  HI_ERR_SPRINTF_S                                   0x80000006
#define  HI_ERR_STRCPY_S                                    0x80000007

/*****************************************************************************
* 2、Error codes of the system adaptation layer.CNcomment:系统适配层错误码
*****************************************************************************/
/* Task */
#define HI_ERR_TASK_INVALID_PARAM                           0x80000080
#define HI_ERR_TASK_CREATE_FAIL                             0x80000081
#define HI_ERR_TASK_DELETE_FAIL                             0x80000082
#define HI_ERR_TASK_SUPPEND_FAIL                            0x80000083
#define HI_ERR_TASK_RESUME_FAIL                             0x80000084
#define HI_ERR_TASK_GET_PRI_FAIL                            0x80000085
#define HI_ERR_TASK_SET_PRI_FAIL                            0x80000086
#define HI_ERR_TASK_LOCK_FAIL                               0x80000087
#define HI_ERR_TASK_UNLOCK_FAIL                             0x80000088
#define HI_ERR_TASK_DELAY_FAIL                              0x80000089
#define HI_ERR_TASK_GET_INFO_FAIL                           0x8000008A
#define HI_ERR_TASK_REGISTER_SCHEDULE_FAIL                  0x8000008B
#define HI_ERR_TASK_NOT_CREATED                             0x8000008C

/* ISR */
#define HI_ERR_ISR_INVALID_PARAM                            0x800000C0
#define HI_ERR_ISR_REQ_IRQ_FAIL                             0x800000C1
#define HI_ERR_ISR_ADD_JOB_MALLOC_FAIL                      0x800000C2
#define HI_ERR_ISR_ADD_JOB_SYS_FAIL                         0x800000C3
#define HI_ERR_ISR_DEL_IRQ_FAIL                             0x800000C4
#define HI_ERR_ISR_ALREADY_CREATED                          0x800000C5
#define HI_ERR_ISR_NOT_CREATED                              0x800000C6
#define HI_ERR_ISR_ENABLE_IRQ_FAIL                          0x800000C7
#define HI_ERR_ISR_IRQ_ADDR_NOK                             0x800000C8

/* Memory */
#define HI_ERR_MEM_INVALID_PARAM                            0x80000100
#define HI_ERR_MEM_CREAT_POOL_FAIL                          0x80000101
#define HI_ERR_MEM_CREATE_POOL_NOT_ENOUGH_HANDLE            0x80000102
#define HI_ERR_MEM_FREE_FAIL                                0x80000103
#define HI_ERR_MEM_RE_INIT                                  0x80000104
#define HI_ERR_MEM_NOT_INIT                                 0x80000105
#define HI_ERR_MEM_CREAT_POOL_MALLOC_FAIL                   0x80000106
#define HI_ERR_MEM_GET_INFO_FAIL                            0x80000107
#define HI_ERR_MEM_GET_OS_INFO_NOK                          0x80000108

/* OSTIMER */
#define HI_ERR_TIMER_FAILURE                                0x80000140
#define HI_ERR_TIMER_INVALID_PARAM                          0x80000141
#define HI_ERR_TIMER_CREATE_HANDLE_FAIL                     0x80000142
#define HI_ERR_TIMER_START_FAIL                             0x80000143
#define HI_ERR_TIMER_HANDLE_NOT_CREATE                      0x80000144
#define HI_ERR_TIMER_HANDLE_INVALID                         0x80000145
#define HI_ERR_TIMER_STATUS_INVALID                         0x80000146
#define HI_ERR_TIMER_STATUS_START                           0x80000147
#define HI_ERR_TIMER_INVALID_MODE                           0x80000148
#define HI_ERR_TIMER_EXPIRE_INVALID                         0x80000149
#define HI_ERR_TIMER_FUNCTION_NULL                          0x8000014A
#define HI_ERR_TIMER_HANDLE_MAXSIZE                         0x8000014B
#define HI_ERR_TIMER_MALLOC_FAIL                            0x8000014C
#define HI_ERR_TIMER_NOT_INIT                               0x8000014D

/* semaphore */
#define HI_ERR_SEM_INVALID_PARAM                            0x80000180
#define HI_ERR_SEM_CREATE_FAIL                              0x80000181
#define HI_ERR_SEM_DELETE_FAIL                              0x80000182
#define HI_ERR_SEM_WAIT_FAIL                                0x80000183
#define HI_ERR_SEM_SIG_FAIL                                 0x80000184
#define HI_ERR_SEM_WAIT_TIME_OUT                            0x80000185

/* Mutex */
#define HI_ERR_MUX_INVALID_PARAM                            0x800001C0
#define HI_ERR_MUX_CREATE_FAIL                              0x800001C1
#define HI_ERR_MUX_DELETE_FAIL                              0x800001C2
#define HI_ERR_MUX_PEND_FAIL                                0x800001C3
#define HI_ERR_MUX_POST_FAIL                                0x800001C4

/* message */
#define HI_ERR_MSG_INVALID_PARAM                            0x80000200
#define HI_ERR_MSG_CREATE_Q_FAIL                            0x80000201
#define HI_ERR_MSG_DELETE_Q_FAIL                            0x80000202
#define HI_ERR_MSG_WAIT_FAIL                                0x80000203
#define HI_ERR_MSG_SEND_FAIL                                0x80000204
#define HI_ERR_MSG_GET_Q_INFO_FAIL                          0x80000205
#define HI_ERR_MSG_Q_DELETE_FAIL                            0x80000206
#define HI_ERR_MSG_WAIT_TIME_OUT                            0x80000207

/* events */
#define HI_ERR_EVENT_INVALID_PARAM                          0x80000240
#define HI_ERR_EVENT_CREATE_NO_HADNLE                       0x80000241
#define HI_ERR_EVENT_CREATE_SYS_FAIL                        0x80000242
#define HI_ERR_EVENT_SEND_FAIL                              0x80000243
#define HI_ERR_EVENT_WAIT_FAIL                              0x80000244
#define HI_ERR_EVENT_CLEAR_FAIL                             0x80000245
#define HI_ERR_EVENT_RE_INIT                                0x80000246
#define HI_ERR_EVENT_NOT_ENOUGH_MEMORY                      0x80000247
#define HI_ERR_EVENT_NOT_INIT                               0x80000248
#define HI_ERR_EVENT_DELETE_FAIL                            0x80000249
#define HI_ERR_EVENT_WAIT_TIME_OUT                          0x8000024A

/* os Maintenance and test */
#define HI_ERR_OSSTAT_INVALID_PARAM                         0x80000280
#define HI_ERR_OSSTAT_SYSTEM_CALL_ERROR                     0x80000281

/* liteos fpb */
#define HI_ERR_FPB_COMP_REPEAT                              0x800002C0
#define HI_ERR_FPB_NO_COMP                                  0x800002C1
#define HI_ERR_FPB_TYPE                                     0x800002C2
#define HI_ERR_FPB_NO_FREE_COMP                             0x800002C3
#define HI_ERR_FPB_ADDR_NOT_ALIGN                           0x800002C4
#define HI_ERR_FPB_TARGET_ADDR                              0x800002C5
#define HI_ERR_FPB_BUSY                                     0x800002C6 /* ????????? */
#define HI_ERR_FPB_ERROR_INPUT                              0x800002C7

/* CPU */
#define HI_ERR_CPUP_NOT_INIT                                0x80000300
#define HI_ERR_CPUP_INVALID_PARAM                           0x80000301
#define HI_ERR_CPU_CLK_INVALID_PARAM                        0x80000302

/* file system */
#define HI_ERR_FS_INVALID_PARAM                             0x80000400
#define HI_ERR_FS_NO_DEVICE                                 0x80000401
#define HI_ERR_FS_NO_SPACE                                  0x80000402  /* No space left on device */
#define HI_ERR_FS_BAD_DESCRIPTOR                            0x80000403
#define HI_ERR_FS_FILE_EXISTS                               0x80000404
#define HI_ERR_FS_NOT_FOUND                                 0x80000405
#define HI_ERR_FS_NAME_TOO_LONG                             0x80000406
#define HI_ERR_FS_READ_ONLY_FS                              0x80000407 /* Read-only file system */
#define HI_ERR_FS_IO_ERROR                                  0x80000408
#define HI_ERR_FS_NO_MORE_FILES                             0x80000409

/*****************************************************************************
* 3、Driver error code
*****************************************************************************/
/* Serial port */
#define HI_ERR_UART_INVALID_PARAMETER                       0x80001000
#define HI_ERR_UART_INVALID_SUSPEND                         0x80001001
#define HI_ERR_UART_INVALID_PARITY                          0x80001002
#define HI_ERR_UART_INVALID_DATA_BITS                       0x80001003
#define HI_ERR_UART_INVALID_STOP_BITS                       0x80001004
#define HI_ERR_UART_INVALID_BAUD                            0x80001005
#define HI_ERR_UART_INVALID_COM_PORT                        0x80001006
#define HI_ERR_UART_NOT_SUPPORT_DMA                         0x80001007
#define HI_ERR_UART_NOT_BLOCK_MODE                          0x80001008

/* gpio */
#define HI_ERR_GPIO_INVALID_PARAMETER                       0x80001040
#define HI_ERR_GPIO_REPEAT_INIT                             0x80001041
#define HI_ERR_GPIO_NOT_INIT                                0x80001042
#define HI_ERR_GPIO_NOT_SUPPORT                             0x80001043

/* watchdog */
#define HI_ERR_WATCHDOG_PARA_ERROR                          0x80001080

/* Flash */
#define HI_ERR_FLASH_NOT_INIT                               0x800010C0
#define HI_ERR_FLASH_INVALID_PARAM                          0x800010C1
#define HI_ERR_FLASH_INVALID_PARAM_BEYOND_ADDR              0x800010C2
#define HI_ERR_FLASH_INVALID_PARAM_SIZE_ZERO                0x800010C3
#define HI_ERR_FLASH_INVALID_PARAM_ERASE_NOT_ALIGN          0x800010C4
#define HI_ERR_FLASH_INVALID_PARAM_IOCTRL_DATA_NULL         0x800010C5
#define HI_ERR_FLASH_INVALID_PARAM_DATA_NULL                0x800010C6
#define HI_ERR_FLASH_INVALID_PARAM_PKI_MODIFY               0x800010C7
#define HI_ERR_FLASH_INVALID_PARAM_PAD1                     0x800010C8
#define HI_ERR_FLASH_INVALID_PARAM_PAD2                     0x800010C9
#define HI_ERR_FLASH_INVALID_PARAM_PAD3                     0x800010CA
#define HI_ERR_FLASH_TIME_OUT_WAIT_READY                    0x800010CB
#define HI_ERR_FLASH_QUAD_MODE_READ_REG1                    0x800010CC
#define HI_ERR_FLASH_QUAD_MODE_READ_REG2                    0x800010CD
#define HI_ERR_FLASH_QUAD_MODE_COMPARE_REG                  0x800010CE
#define HI_ERR_FLASH_NO_MATCH_FLASH                         0x800010CF
#define HI_ERR_FLASH_WRITE_ENABLE                           0x800010D0
#define HI_ERR_FLASH_NO_MATCH_ERASE_SIZE                    0x800010D1
#define HI_ERR_FLASH_MAX_SPI_OP                             0x800010D2
#define HI_ERR_FLASH_NOT_SUPPORT_IOCTRL_ID                  0x800010D3
#define HI_ERR_FLASH_INVALID_CHIP_ID                        0x800010D4
#define HI_ERR_FLASH_RE_INIT                                0x800010D5
#define HI_ERR_FLASH_WRITE_NOT_SUPPORT_ERASE                0x800010D6
#define HI_ERR_FLASH_WRITE_COMPARE_WRONG                    0x800010D7
#define HI_ERR_FLASH_WAIT_CFG_START_TIME_OUT                0x800010D8
#define HI_ERR_FLASH_PATITION_INIT_FAIL                     0x800010D9
#define HI_ERR_FLASH_INITILIZATION                          0x800010DA
#define HI_ERR_FLASH_ERASE_NOT_4K_ALIGN                     0x800010DB
#define HI_ERR_FLASH_PROTECT_NOT_SUPPORT                    0x800010DC
#define HI_ERR_FLASH_PROTECT_NOT_INIT                       0x800010DD
#define HI_ERR_FLASH_PROTECT_RE_INIT                        0x800010DE
#define HI_ERR_FLASH_PROTECT_NOT_FIND_CHIP                  0x800010DF
#define HI_ERR_FLASH_PROTECT_ADDR_WRONG                     0x800010E0
#define HI_ERR_FLASH_CRYPTO_INVALID_PARAM                   0x800010F0
#define HI_ERR_FLASH_CRYPTO_BEYOND_ADDR_SIZE                0x800010F1
#define HI_ERR_FLASH_CRYPTO_MALLOC_FAIL                     0x800001F2
#define HI_ERR_FLASH_CRYPTO_DATA_ENCRYPT_ERR                0x800001F3
#define HI_ERR_FLASH_CRYPTO_DATA_DECRYPT_ERR                0x800001F4
#define HI_ERR_FLASH_CRYPTO_KEY_EMPTY_ERR                   0x800001F5
#define HI_ERR_FLASH_CRYPTO_MEMCPY_FAIL                     0x800001F6
#define HI_ERR_FLASH_CRYPTO_NOT_SUPPORT                     0x800001F7
#define HI_ERR_FLASH_CRYPTO_PREPARE_ERR                     0x800001F8
#define HI_ERR_FLASH_CRYPTO_KEY_INVALID_ERR                 0x800001F9
#define HI_ERR_FLASH_CRYPTO_KEY_SAVE_ERR                    0x800001FA
#define HI_ERR_FLASH_CRYPTO_KERNEL_ADDR_ERR                 0x800001FB
#define HI_ERR_FLASH_CRYPTO_ROOT_SALT_EMPTY_ERR             0x800001FC

/* HRTIMER */
#define HI_ERR_HRTIMER_ALREADY_INIT                         0x80001100
#define HI_ERR_HRTIMER_NOT_INIT                             0x80001101
#define HI_ERR_HRTIMER_HAVE_NO_AVAILABLE_HANDLE             0x80001102
#define HI_ERR_HRTIMER_NOT_CREATE_HANDLE                    0x80001103
#define HI_ERR_HRTIMER_IN_START_STATUS                      0x80001104
#define HI_ERR_HRTIMER_NOT_START                            0x80001105
#define HI_ERR_HRTIMER_INVALID_ID                           0x80001106
#define HI_ERR_HRTIMER_INVALID_PARAMETER                    0x80001107
#define HI_ERR_HRTIMER_MALLOC_FAILUE                        0x80001108

/* hardware timer */
#define HI_ERR_HWTIMER_INVALID_PARAMETER                    0x80001140
#define HI_ERR_HWTIMER_INITILIZATION_ALREADY                0x80001141
#define HI_ERR_HWTIMER_NO_INIT                              0x80001142

/* i2c */
#define HI_ERR_I2C_NOT_INIT                                 0x80001180
#define HI_ERR_I2C_INVALID_PARAMETER                        0x80001181
#define HI_ERR_I2C_TIMEOUT_START                            0x80001182
#define HI_ERR_I2C_TIMEOUT_WAIT                             0x80001183
#define HI_ERR_I2C_TIMEOUT_STOP                             0x80001184
#define HI_ERR_I2C_TIMEOUT_RCV_BYTE                         0x80001185
#define HI_ERR_I2C_TIMEOUT_RCV_BYTE_PROC                    0x80001186
#define HI_ERR_I2C_WAIT_SEM_FAIL                            0x80001187
#define HI_ERR_I2C_START_ACK_ERR                            0x80001188
#define HI_ERR_I2C_WAIT_ACK_ERR                             0x80001189

/* spi */
#define HI_ERR_SPI_NOT_INIT                                 0x800011C0
#define HI_ERR_SPI_REINIT                                   0x800011C1
#define HI_ERR_SPI_PARAMETER_WRONG                          0x800011C2
#define HI_ERR_SPI_BUSY                                     0x800011C3
#define HI_ERR_SPI_WRITE_TIMEOUT                            0x800011C4
#define HI_ERR_SPI_READ_TIMEOUT                             0x800011C5
#define HI_ERR_SPI_NOT_SUPPORT_DMA                          0x800011C6

/* efuse */
#define HI_ERR_EFUSE_INVALIDATE_ID                          0x80001200
#define HI_ERR_EFUSE_INVALIDATE_PARA                        0x80001201
#define HI_ERR_EFUSE_WRITE_ERR                              0x80001202
#define HI_ERR_EFUSE_INVALIDATE_AUTH                        0x80001203
#define HI_ERR_EFUSE_BUSY                                   0x80001204
#define HI_ERR_EFUSE_TIMEOUT                                0x80001205

/* cipher */
#define HI_ERR_CIPHER_NOT_INIT                              0x80001240
#define HI_ERR_CIPHER_INVALID_POINT                         0x80001241
#define HI_ERR_CIPHER_INVALID_PARAMETER                     0x80001242
#define HI_ERR_CIPHER_NO_AVAILABLE_RNG                      0x80001243
#define HI_ERR_CIPHER_FAILED_MEM                            0x80001244
#define HI_ERR_CIPHER_OVERFLOW                              0x80001245
#define HI_ERR_CIPHER_TIMEOUT                               0x80001246
#define HI_ERR_CIPHER_UNSUPPORTED                           0x80001247
#define HI_ERR_CIPHER_REGISTER_IRQ                          0x80001248
#define HI_ERR_CIPHER_ILLEGAL_KEY                           0x80001249
#define HI_ERR_CIPHER_INVALID_ADDR                          0x8000124A
#define HI_ERR_CIPHER_INVALID_LENGTH                        0x8000124B
#define HI_ERR_CIPHER_ILLEGAL_DATA                          0x8000124C
#define HI_ERR_CIPHER_RSA_SIGN                              0x8000124D
#define HI_ERR_CIPHER_RSA_VERIFY                            0x8000124E
#define HI_ERR_CIPHER_RESULT_WARNING                        0x8000124F
#define HI_ERR_CIPHER_FLUSH_DCACHE_FAILED                   0x80001250

/* sdio */
#define HI_ERR_SDIO_INVALID_PARAMETER                       0x80001280

/* tsensor */
#define HI_ERR_TSENSOR_INVALID_PARAMETER                    0x800012C0

/* adc */
#define HI_ERR_ADC_PARAMETER_WRONG                          0x80001300
#define HI_ERR_ADC_INVALID_CHANNEL_ID                       0x80001301
#define HI_ERR_ADC_TIMEOUT                                  0x80001302
#define HI_ERR_ADC_NOT_INIT                                 0x80001303

/* pmw */
#define HI_ERR_PWM_NO_INIT                                  0x80001340
#define HI_ERR_PWM_INITILIZATION_ALREADY                    0x80001341
#define HI_ERR_PWM_INVALID_PARAMETER                        0x80001342


/* dma */
#define HI_ERR_DMA_INVALID_PARA                             0x80001380
#define HI_ERR_DMA_NOT_INIT                                 0x80001381
#define HI_ERR_DMA_BUSY                                     0x80001382
#define HI_ERR_DMA_TRANSFER_FAIL                            0x80001383
#define HI_ERR_DMA_TRANSFER_TIMEOUT                         0x80001384
#define HI_ERR_DMA_GET_NOTE_FAIL                            0x80001385
#define HI_ERR_DMA_LLI_NOT_CREATE                           0x80001386
#define HI_ERR_DMA_CH_IRQ_ENABLE_FAIL                       0x80001387
/* audio */
#define HI_ERR_AUDIO_BUSY                                   0x800013C0
#define HI_ERR_AUDIO_INVALID_PARAMETER                      0x800013C1

/* i2s */
#define HI_ERR_I2S_INVALID_PARAMETER                        0x80001400
#define HI_ERR_I2S_WRITE_TIMEOUT                            0x80001401
#define HI_ERR_I2S_MALLOC_FAIL                              0x80001402
#define HI_ERR_I2S_MEMCPY_FAIL                              0x80001403

/* shell */
#define HI_ERR_SHELL_NOT_INIT                               0x80001440
#define HI_ERR_SHELL_CMDREG_PARA_ERROR                      0x80001441
#define HI_ERR_SHELL_CMDREG_CMD_ERROR                       0x80001442
#define HI_ERR_SHELL_CMDREG_CMD_EXIST                       0x80001443
#define HI_ERR_SHELL_CMDREG_MEMALLOC_ERROR                  0x80001444

/*****************************************************************************
* 4、Intermediate application error code
*****************************************************************************/
/* NV */
#define HI_ERR_NV_FILE_ERR                                  0x80003000
#define HI_ERR_NV_MEMCPY_FAIL                               0x80003001
#define HI_ERR_NV_WRITE_FILE_FAIL                           0x80003002
#define HI_ERR_NV_UPDATA_DATA_FAIL                          0x80003003
#define HI_ERR_NV_UPDATA_FILE_FAIL                          0x80003004
#define HI_ERR_NV_NOT_SUPPORT_WRITE                         0x80003005
#define HI_ERR_NV_FSEC_TOTAL_NUM_INVALID                    0x80003006 /* 工厂NV项个数非法 */
#define HI_ERR_NV_FAIL_N_TIMES                              0x80003007
#define HI_ERR_NV_SEM_FAIL                                  0x80003008
#define HI_ERR_NV_LEN_ERR                                   0x80003009
#define HI_ERR_NV_NOT_FOUND                                 0x8000300A
#define HI_ERR_NV_FULL                                      0x8000300B
#define HI_ERR_NV_NOT_ENOUGH_MEMORY                         0x8000300C
#define HI_ERR_NV_NOT_SUPPORT                               0x8000300D
#define HI_ERR_NV_NOT_SUPPORT_ID                            0x8000300E
#define HI_ERR_NV_BAD_DATA                                  0x8000300F
#define HI_ERR_NV_INVALID_TYPE                              0x80003010
/* NV读取失败 CNcomment:Read NVIM Failure */
#define HI_ERR_NV_ERROR_READ                                0x80003011
/* NV写失败，长度过长CNcomment:Write Error for Length Overflow */
#define HI_ERR_NV_NOT_SUPPORT_LENTH                         0x80003012
/* NV写失败,Flash坏块 CNcomment:Write Error for Flash Bad Block */
#define HI_ERR_NV_BAD_BLOCK                                 0x80003013
/* NV写失败,其他错误 CNcomment:Write Error for Unknown Reason */
#define HI_ERR_NV_ERROR_WRITE                               0x80003014
#define HI_ERR_NV_INITILIZATION                             0x80003015
#define HI_ERR_NV_INVALID_PARAMETER                         0x80003016

/* Low power consumption */
#define HI_ERR_LOWPOWER_INVALID_PARAMETER                   0x80003040
#define HI_ERR_LOWPOWER_XTAL_UNSTABLE                       0x80003041
#define HI_ERR_LOWPOWER_XTAL_SAMPLING                       0x80003042

/* upgrade common error */
#define HI_ERR_UPG_COMMON                                   0x80003060
#define HI_ERR_UPG_NULL_POINTER                             (HI_ERR_UPG_COMMON + 0x0)
#define HI_ERR_UPG_PARAMETER                                (HI_ERR_UPG_COMMON + 0x1)
#define HI_ERR_UPG_BACKUP_ADDR                              (HI_ERR_UPG_COMMON + 0x2)
#define HI_ERR_UPG_BUSY                                     (HI_ERR_UPG_COMMON + 0x3)
#define HI_ERR_UPG_FLASH_BAD                                (HI_ERR_UPG_COMMON + 0x4)
#define HI_ERR_UPG_START_ADDR                               (HI_ERR_UPG_COMMON + 0x5)
#define HI_ERR_UPG_INITILIZATION_ALREADY                    (HI_ERR_UPG_COMMON + 0x6)
#define HI_ERR_UPG_FILE_LEN                                 (HI_ERR_UPG_COMMON + 0x7)
#define HI_ERR_UPG_NOT_START                                (HI_ERR_UPG_COMMON + 0x8)
#define HI_ERR_UPG_MALLOC_FAIL                              (HI_ERR_UPG_COMMON + 0x9)
#define HI_ERR_UPG_GET_SECTION_HEAD                         (HI_ERR_UPG_COMMON + 0xA)
#define HI_ERR_UPG_BUF_LEN                                  (HI_ERR_UPG_COMMON + 0xB)
#define HI_ERR_UPG_FLASH_SIZE                               (HI_ERR_UPG_COMMON + 0xC)
#define HI_ERR_UPG_NV_SIZE                                  (HI_ERR_UPG_COMMON + 0xD)
#define HI_ERR_UPG_ALREADY_FINISH                           (HI_ERR_UPG_COMMON + 0xE)
#define HI_ERR_UPG_RSA_KEY_ADDR                             (HI_ERR_UPG_COMMON + 0xF)
#define HI_ERR_UPG_ECC_KEY_ADDR                             (HI_ERR_UPG_COMMON + 0x10)
#define HI_ERR_UPG_FILE_LEN_OVER                            (HI_ERR_UPG_COMMON + 0x11)
#define HI_ERR_UPG_STOP                                     (HI_ERR_UPG_COMMON + 0x12)
#define HI_ERR_UPG_LOW_KERNEL_VER                           (HI_ERR_UPG_COMMON + 0x13)
#define HI_ERR_UPG_FULL_KERNEL_VER                          (HI_ERR_UPG_COMMON + 0x14)
#define HI_ERR_UPG_LOW_BOOT_VER                             (HI_ERR_UPG_COMMON + 0x15)
#define HI_ERR_UPG_FULL_BOOT_VER                            (HI_ERR_UPG_COMMON + 0x16)
#define HI_ERR_UPG_FIRST_PACKET_OFFSET                      (HI_ERR_UPG_COMMON + 0x17)
#define HI_ERR_UPG_UPDATE_VER_TIMEOUT                       (HI_ERR_UPG_COMMON + 0x18)
#define HI_ERR_UPG_UPDATE_VER_FAIL                          (HI_ERR_UPG_COMMON + 0x19)
#define HI_ERR_UPG_UPDATE_VER_INVALID_PARAM                 (HI_ERR_UPG_COMMON + 0x1A)
#define HI_ERR_UPG_KERNEL_VER_OVER                          (HI_ERR_UPG_COMMON + 0x1B)
#define HI_ERR_UPG_BOOT_VER_OVER                            (HI_ERR_UPG_COMMON + 0x1C)
#define HI_ERR_UPG_KERNEL_LEN                               (HI_ERR_UPG_COMMON + 0x1D)
#define HI_ERR_UPG_KEY_LEN                                  (HI_ERR_UPG_COMMON + 0x1E)

/* upgrade file check error */
#define HI_ERR_UPG_CHECK                                     0x80003080
#define HI_ERR_UPG_IMAGE_ID                                 (HI_ERR_UPG_CHECK + 0x0)
#define HI_ERR_UPG_FILE_TYPE                                (HI_ERR_UPG_CHECK + 0x1)
#define HI_ERR_UPG_HEAD_LEN                                 (HI_ERR_UPG_CHECK + 0x2)
#define HI_ERR_UPG_SIGN_ALG                                 (HI_ERR_UPG_CHECK + 0x3)
#define HI_ERR_UPG_RSA_KEY_LEN                              (HI_ERR_UPG_CHECK + 0x4)
#define HI_ERR_UPG_RSA_HEAD_SIGN                            (HI_ERR_UPG_CHECK + 0x5)
#define HI_ERR_UPG_ECC_KEY_LEN                              (HI_ERR_UPG_CHECK + 0x6)
#define HI_ERR_UPG_ECC_HEAD_SIGN                            (HI_ERR_UPG_CHECK + 0x7)
#define HI_ERR_UPG_COMMON_SHA256                            (HI_ERR_UPG_CHECK + 0x8)
#define HI_ERR_UPG_SECTION_SHA256                           (HI_ERR_UPG_CHECK + 0x9)
#define HI_ERR_UPG_KERNEL_VER                               (HI_ERR_UPG_CHECK + 0xA)
#define HI_ERR_UPG_BOOT_VER                                 (HI_ERR_UPG_CHECK + 0xB)
#define HI_ERR_UPG_BOOT_HEAD                                (HI_ERR_UPG_CHECK + 0xC)
#define HI_ERR_UPG_BOOT_LEN                                 (HI_ERR_UPG_CHECK + 0xD)
#define HI_ERR_UPG_BOOT_ROOT_KEY                            (HI_ERR_UPG_CHECK + 0xE)
#define HI_ERR_UPG_BOOT_ROOT_KEY_LEN                        (HI_ERR_UPG_CHECK + 0xF)
#define HI_ERR_UPG_BOOT_KEY_ID                              (HI_ERR_UPG_CHECK + 0x10)
#define HI_ERR_UPG_BOOT_SIGN_ALG                            (HI_ERR_UPG_CHECK + 0x11)
#define HI_ERR_UPG_BOOT_SUB_KEY                             (HI_ERR_UPG_CHECK + 0x12)
#define HI_ERR_UPG_BOOT_SUB_KEY_CAT                         (HI_ERR_UPG_CHECK + 0x13)
#define HI_ERR_UPG_BOOT_SUB_KEY_RSIM                        (HI_ERR_UPG_CHECK + 0x14)
#define HI_ERR_UPG_BOOT_DIE_ID                              (HI_ERR_UPG_CHECK + 0x15)
#define HI_ERR_UPG_BOOT_HASH                                (HI_ERR_UPG_CHECK + 0x16)
#define HI_ERR_UPG_BOOT_SUB_KEY_LEN                         (HI_ERR_UPG_CHECK + 0x17)
#define HI_ERR_UPG_USER_VERIFY                              (HI_ERR_UPG_CHECK + 0x18)
#define HI_ERR_UPG_BOOT_SUB_KEY_HASH                        (HI_ERR_UPG_CHECK + 0x19)
#define HI_ERR_UPG_BOOT_SECTION_HASH                        (HI_ERR_UPG_CHECK + 0x1A)
#define HI_ERR_UPG_COMMON_HASH                              (HI_ERR_UPG_CHECK + 0x1B)
#define HI_ERR_UPG_SECTION_HASH                             (HI_ERR_UPG_CHECK + 0x1C)
#define HI_ERR_UPG_ADD_START                                (HI_ERR_UPG_CHECK + 0x1D)
#define HI_ERR_UPG_ENCRYPT_NOT_MATCH                        (HI_ERR_UPG_CHECK + 0x1E)
#define HI_ERR_UPG_OTA_NOT_MATCH                            (HI_ERR_UPG_CHECK + 0x1F)

/* upgrade file crypto error */
#define HI_ERR_UPG_CRYPTO                                   0x800030A0
#define HI_ERR_UPG_CRYPTO_PREPARE_ERR                       (HI_ERR_UPG_CRYPTO + 0x0)
#define HI_ERR_UPG_FILE_DECRYPT_ERR                         (HI_ERR_UPG_CRYPTO + 0x1)
#define HI_ERR_UPG_NOT_WITH_CACHE_MODE_ERR                  (HI_ERR_UPG_CRYPTO + 0x2)
#define HI_ERR_UPG_NOT_DOWNLOAD_FINISH                      (HI_ERR_UPG_CRYPTO + 0x3)

/* DIAG */
#define HI_ERR_DIAG_NOT_FOUND                               0x800030C0
#define HI_ERR_DIAG_INVALID_ID                              0x800030C1
#define HI_ERR_DIAG_FULL                                    0x800030C2
#define HI_ERR_DIAG_CONSUMED                                0x800030C3
#define HI_ERR_DIAG_CONTINUE                                0x800030C4
#define HI_ERR_DIAG_TOO_SMALL_BUFFER                        0x800030C5
#define HI_ERR_DIAG_NO_MORE_DATA                            0x800030C6
#define HI_ERR_DIAG_NOT_ENOUGH_MEMORY                       0x800030C7
#define HI_ERR_DIAG_INVALID_HEAP_ADDR                       0x800030C8
#define HI_ERR_DIAG_NOT_CONNECT                             0x800030C9
#define HI_ERR_DIAG_BUSY                                    0x800030CA
#define HI_ERR_DIAG_TOO_LARGE_FRAME                         0x800030CB
#define HI_ERR_DIAG_RAM_ALIGN                               0x800030CC
#define HI_ERR_DIAG_NOT_SUPPORT                             0x800030CD
#define HI_ERR_DIAG_UNAVAILABLE                             0x800030CE
#define HI_ERR_DIAG_CFG_NOT_ALLOW                           0x800030CF
#define HI_ERR_DIAG_INVALID_CODE_ADDR                       0x800030D0
#define HI_ERR_DIAG_OBJ_NOT_FOUND                           0x800030D1
#define HI_ERR_DIAG_QUEUE_FULL                              0x800030D2
#define HI_ERR_DIAG_NO_MORE_MEMORY                          0x800030D3
#define HI_ERR_DIAG_SYSTEM_CALL_ERROR                       0x800030D4
#define HI_ERR_DIAG_NO_INIT                                 0x800030D5
#define HI_ERR_DIAG_INVALID_PARAMETER                       0x800030D6
#define HI_ERR_DIAG_STAT_NOT_SUPPORT                        0x800030D7
#define HI_ERR_DIAG_ID_OR_CALLBACK_ALREADY_REGISTERED       0x800030D8
#define HI_ERR_DIAG_SET_CONN_ACK_INFO                       0x800030D9
#define HI_ERR_DIAG_CMD_NUM_EXCEED_UPPER_LIMIT              0x800030DA

/* reset */
#define HI_ERR_RESET_TOO_LARGE_DATA                         0x80003100
#define HI_ERR_RESET_INVALID_PARAMETER                      0x80003101

/* syserror */
#define HI_ERR_SYSERROR_NOT_FOUND                           0x80003140
#define HI_ERR_SYSERROR_INVALID_PARAMETER                   0x80003141


/* APP */
#define HI_ERR_APP_INITILIZATION_ALREADY                    0x80003180
#define HI_ERR_APP_INVALID_PARAMETER                        0x80003181

/* CRC */
#define HI_ERR_CRC_INVALID_PARAMETER                        0x800031C0


/* sigma */
#define HI_ERR_SIGMA_INVALID_PARAMETER                      0x80003200

/* data collect */
#define HI_ERR_DATACOLLECT_INVALID_PARAMETER                0x80003240
#define HI_ERR_DATACOLLECT_BUSY                             0x80003241

/* AT */
#define HI_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED           0x80003280
#define HI_ERR_AT_INVALID_PARAMETER                        0x80003281

/*****************************************************************************
* 5、Protocol stack error codes
*****************************************************************************/
/* wifi */
/* Note: The base value of the Wi-Fi error code hi_err_code_enum is changed to the start value,
 * and other error codes are delayed at one time.
 * CNcomment:说明:wifi错误码hi_err_code_enum 将base基值修改为起始值，其他错误码一次延顺
 */
/* dmac */
#define HI_ERR_WIFI_DMAC_NOT_SUPPORT                        0x80004000

/* hmac */
#define HI_ERR_WIFI_HMAC_INVALID_PARAMETER                  0x80004040

/* wal */
#define HI_ERR_WIFI_WAL_MALLOC_FAIL                         0x80004080
#define HI_ERR_WIFI_WAL_FAILURE                             0x80004081
#define HI_ERR_WIFI_WAL_BUSY                                0x80004082
#define HI_ERR_WIFI_WAL_INVALID_PARAMETER                   0x80004083

/*****************************************************************************
* 6、128 units reserved for Hisi.CNcomment:Hisi保留 unit128个
* 7、64 units reserved for customer use. CNcomment:客户使用预留 unit64个
*****************************************************************************/
#endif /* __HI_ERRNO_H__ */
