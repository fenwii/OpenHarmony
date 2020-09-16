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

#ifndef __HI_BOOT_ERR_H__
#define __HI_BOOT_ERR_H__

/* Generic errno */
#define HI_ERR_SUCCESS                                  0x3CA5965A
#define HI_ERR_FAILURE                                  0xC35A69A5
#define HI_ERR_MALLOC_FAILUE                            0x80000000
#define HI_ERR_TIMEOUT                                  0x80000001

/* gpio errno */
#define HI_ERR_GPIO_INVALID_PARAMETER                   0x80001040
#define HI_ERR_GPIO_REPEAT_INIT                         0x80001041
#define HI_ERR_GPIO_NOT_INIT                            0x80001042
#define HI_ERR_GPIO_NOT_SUPPORT                         0x80001043

/* Flash errno */
#define HI_ERR_FLASH_NOT_INIT                           0x800010C0
#define HI_ERR_FLASH_INVALID_PARAMETER                  0x800010C1
#define HI_ERR_FLASH_INVALID_PARAM_BEYOND_ADDR          0x800010C2
#define HI_ERR_FLASH_INVALID_PARAM_SIZE_ZERO            0x800010C3
#define HI_ERR_FLASH_INVALID_PARAM_ERASE_NOT_ALIGN      0x800010C4
#define HI_ERR_FLASH_INVALID_PARAM_IOCTRL_DATA_NULL     0x800010C5
#define HI_ERR_FLASH_INVALID_PARAM_DATA_NULL            0x800010C6
#define HI_ERR_FLASH_INVALID_PARAM_PAD1                 0x800010C7
#define HI_ERR_FLASH_INVALID_PARAM_PAD2                 0x800010C8
#define HI_ERR_FLASH_INVALID_PARAM_PAD3                 0x800010C9
#define HI_ERR_FLASH_INVALID_PARAM_PAD4                 0x800010CA
#define HI_ERR_FLASH_TIME_OUT_WAIT_READY                0x800010CB
#define HI_ERR_FLASH_QUAD_MODE_READ_REG1                0x800010CC
#define HI_ERR_FLASH_QUAD_MODE_READ_REG2                0x800010CD
#define HI_ERR_FLASH_QUAD_MODE_COMPARE_REG              0x800010CE
#define HI_ERR_FLASH_NO_MATCH_FLASH                     0x800010CF
#define HI_ERR_FLASH_WRITE_ENABLE                       0x800010D0
#define HI_ERR_FLASH_NO_MATCH_ERASE_SIZE                0x800010D1
#define HI_ERR_FLASH_MAX_SPI_OP                         0x800010D2
#define HI_ERR_FLASH_NOT_SUPPORT_IOCTRL_ID              0x800010D3
#define HI_ERR_FLASH_INVALID_CHIP_ID                    0x800010D4
#define HI_ERR_FLASH_RE_INIT                            0x800010D5
#define HI_ERR_FLASH_WRITE_NOT_SUPPORT_ERASE            0x800010D6
#define HI_ERR_FLASH_WRITE_COMPARE_WRONG                0x800010D7
#define HI_ERR_FLASH_WAIT_CFG_START_TIME_OUT            0x800010D8
#define HI_ERR_FLASH_PATITION_INIT_FAIL                 0x800010D9
#define HI_ERR_FLASH_INITILIZATION                      0x800010DA
#define HI_ERR_FLASH_ERASE_NOT_4K_ALIGN                 0x800010DB

/* efuse errno */
#define HI_ERR_EFUSE_INVALIDATE_ID                      0x80001200
#define HI_ERR_EFUSE_INVALIDATE_PARA                    0x80001201
#define HI_ERR_EFUSE_WRITE_ERR                          0x80001202
#define HI_ERR_EFUSE_INVALIDATE_AUTH                    0x80001203
#define HI_ERR_EFUSE_BUSY                               0x80001204
#define HI_ERR_EFUSE_TIMEOUT                            0x80001205

/* cipher errno */
#define HI_ERR_CIPHER_NOT_INIT                          0x80001240
#define HI_ERR_CIPHER_INVALID_POINT                     0x80001241
#define HI_ERR_CIPHER_INVALID_PARAMETER                 0x80001242
#define HI_ERR_CIPHER_NO_AVAILABLE_RNG                  0x80001243
#define HI_ERR_CIPHER_FAILED_MEM                        0x80001244
#define HI_ERR_CIPHER_OVERFLOW                          0x80001245
#define HI_ERR_CIPHER_TIMEOUT                           0x80001246
#define HI_ERR_CIPHER_UNSUPPORTED                       0x80001247
#define HI_ERR_CIPHER_REGISTER_IRQ                      0x80001248
#define HI_ERR_CIPHER_ILLEGAL_KEY                       0x80001249
#define HI_ERR_CIPHER_INVALID_ADDR                      0x8000124A
#define HI_ERR_CIPHER_INVALID_LENGTH                    0x8000124B
#define HI_ERR_CIPHER_ILLEGAL_DATA                      0x8000124C
#define HI_ERR_CIPHER_RSA_SIGN                          0x8000124D
#define HI_ERR_CIPHER_RSA_VERIFY                        0x8000124E
#define HI_ERR_CIPHER_RESULT_WARNING                    0x8000124F
#define HI_ERR_CIPHER_FLUSH_DCACHE_FAILED               0x80001250

#define HI_ERR_YMODEM_ERR_TIMEOUT                       0xC35A69A6
#define HI_ERR_YMODEM_ERR_CANCEL                        0xC35A69A7
#define HI_ERR_YMODEM_ERR_FRAME                         0xC35A69A8
#define HI_ERR_YMODEM_ERR_CS                            0xC35A69A9
#define HI_ERR_YMODEM_ERR_EOT                           0xC35A69AA
#define HI_ERR_YMODEM_ERR_SEQ                           0xC35A69AB
#define HI_ERR_YMODEM_ERR_LENTH                         0xC35A69AC

/* upgrade common error */
#define HI_ERR_UPG_NULL_POINTER                         0x80001300
#define HI_ERR_UPG_PARAMETER                            0x80001301
#define HI_ERR_UPG_BACKUP_ADDR                          0x80001302
#define HI_ERR_UPG_BUSY                                 0x80001303
#define HI_ERR_UPG_FLASH_BAD                            0x80001304
#define HI_ERR_UPG_START_ADDR                           0x80001305
#define HI_ERR_UPG_INITILIZATION_ALREADY                0x80001306
#define HI_ERR_UPG_FILE_LEN                             0x80001307
#define HI_ERR_UPG_NOT_START                            0x80001308
#define HI_ERR_UPG_MALLOC_FAIL                          0x80001309
#define HI_ERR_UPG_BOOT_MAGIC                           0x8000130A
#define HI_ERR_UPG_BOOT_LEN                             0x8000130B
#define HI_ERR_UPG_FILE_LEN_OVER                        0x8000130C
#define HI_ERR_UPG_FILE_LEN_ZERO                        0x8000130D

/* upgrade file check error */
#define HI_ERR_UPG_IMAGE_ID                             0x80001340
#define HI_ERR_UPG_FILE_TYPE                            0x80001341
#define HI_ERR_UPG_HEAD_LEN                             0x80001342
#define HI_ERR_UPG_SIGN_ALG                             0x80001343
#define HI_ERR_UPG_RSA_KEY_LEN                          0x80001344
#define HI_ERR_UPG_RSA_HEAD_SIGN                        0x80001345
#define HI_ERR_UPG_ECC_KEY_LEN                          0x80001346
#define HI_ERR_UPG_ECC_HEAD_SIGN                        0x80001347
#define HI_ERR_UPG_COMMON_SHA256                        0x80001348
#define HI_ERR_UPG_SECTION_SHA256                       0x80001349
#define HI_ERR_UPG_KERNEL_VER                           0x8000134A
#define HI_ERR_UPG_BOOT_VER                             0x8000134B
#define HI_ERR_UPG_DECOMPRESS_FILE_CRC                  0x8000134C
#define HI_ERR_UPG_CRC                                  0x8000134D

/* lzma-decode */
#define HI_ERR_LZMA_DECODE                              0x80001360

/* lzma-common */
#define HI_ERR_LZMA_PARAM                               0x80001380
#define HI_ERR_LZMA_LEN                                 0x80001381

/* NV */
#define HI_ERR_NV_FILE_ERR                              0x80003000
#define HI_ERR_NV_MEMCPY_FAIL                           0x80003001
#define HI_ERR_NV_WRITE_FILE_FAIL                       0x80003002
#define HI_ERR_NV_UPDATA_DATA_FAIL                      0x80003003
#define HI_ERR_NV_UPDATA_FILE_FAIL                      0x80003004
#define HI_ERR_NV_NOT_SUPPORT_WRITE                     0x80003005
#define HI_ERR_NV_FSEC_TOTAL_NUM_INVALID                0x80003006
#define HI_ERR_NV_FAIL_N_TIMES                          0x80003007
#define HI_ERR_NV_SEM_FAIL                              0x80003008
#define HI_ERR_NV_LEN_ERR                               0x80003009
#define HI_ERR_NV_NOT_FOUND                             0x8000300A
#define HI_ERR_NV_FULL                                  0x8000300B
#define HI_ERR_NV_NOT_ENOUGH_MEMORY                     0x8000300C
#define HI_ERR_NV_NOT_SUPPORT                           0x8000300D
#define HI_ERR_NV_NOT_SUPPORT_ID                        0x8000300E
#define HI_ERR_NV_BAD_DATA                              0x8000300F
#define HI_ERR_NV_INVALID_TYPE                          0x80003010
/* Read NVIM Failure */
#define HI_ERR_NV_ERROR_READ                            0x80003011
/* Write Error for Length Overflow */
#define HI_ERR_NV_NOT_SUPPORT_LENTH                     0x80003012
/* Write Error for Flash Bad Block */
#define HI_ERR_NV_BAD_BLOCK                             0x80003013
/* Write Error for Unknown Reason */
#define HI_ERR_NV_ERROR_WRITE                           0x80003014
#define HI_ERR_NV_INITILIZATION                         0x80003015
#define HI_ERR_NV_INVALID_PARAMETER                     0x80003016

/* CRC */
#define HI_ERR_CRC_INVALID_PARAMETER                    0x800031C0

/* upgrade common error */
#define HI_ERR_UPG_COMMON                               0x80003060
#define HI_ERR_UPG_LOW_KERNEL_VER                       (HI_ERR_UPG_COMMON + 0x13)
#define HI_ERR_UPG_FULL_KERNEL_VER                      (HI_ERR_UPG_COMMON + 0x14)
#define HI_ERR_UPG_LOW_BOOT_VER                         (HI_ERR_UPG_COMMON + 0x15)
#define HI_ERR_UPG_FULL_BOOT_VER                        (HI_ERR_UPG_COMMON + 0x16)
#define HI_ERR_UPG_FIRST_PACKET_OFFSET                  (HI_ERR_UPG_COMMON + 0x17)
#define HI_ERR_UPG_UPDATE_VER_TIMEOUT                   (HI_ERR_UPG_COMMON + 0x18)
#define HI_ERR_UPG_UPDATE_VER_FAIL                      (HI_ERR_UPG_COMMON + 0x19)
#define HI_ERR_UPG_UPDATE_VER_INVALID_PARAM             (HI_ERR_UPG_COMMON + 0x1A)
#define HI_ERR_UPG_KERNEL_VER_OVER                      (HI_ERR_UPG_COMMON + 0x1B)
#define HI_ERR_UPG_BOOT_VER_OVER                        (HI_ERR_UPG_COMMON + 0x1C)

#define EOK              HI_ERR_SUCCESS

#endif
