/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

/**
 * @addtogroup wifiiot
 * @{
 *
 * @brief Provides dedicated device operation interfaces on the Wi-Fi module,
 * including ADC, AT, flash, GPIO, I2C, I2S, partition, PWM, SDIO, UART, and watchdog.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hal_wifiiot_errno.h
 *
 * @brief Defines error codes used by the Wi-Fi module.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_ERRNO_H
#define HAL_WIFIIOT_ERRNO_H

/**
 * @brief Defines a module-level return value to indicate a successful operation.
 *
 */
#define HAL_WIFI_IOT_SUCCESS    0
/**
 * @brief Defines a module-level return value to indicate an operation failure.
 *
 */
#define HAL_WIFI_IOT_FAILURE   (-1)

/**
 * @brief Defines a UART error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_PARAMETER                       0x80001000
/**
 * @brief Defines a UART error code to indicate an invalid pause operation.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_SUSPEND                         0x80001001
/**
 * @brief Defines a UART error code to indicate an invalid parity check.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_PARITY                          0x80001002
/**
 * @brief Defines a UART error code to indicate an invalid data bit.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_DATA_BITS                       0x80001003
/**
 * @brief Defines a UART error code to indicate an invalid stop bit.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_STOP_BITS                       0x80001004
/**
 * @brief Defines a UART error code to indicate an invalid baud rate.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_BAUD                            0x80001005
/**
 * @brief Defines a UART error code to indicate an invalid port number.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_INVALID_COM_PORT                        0x80001006
/**
 * @brief Defines a UART error code to indicate a non-support for DMA.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_NOT_SUPPORT_DMA                         0x80001007
/**
 * @brief Defines a UART error code to indicate the non-block mode.
 *
 */
#define HAL_WIFI_IOT_ERR_UART_NOT_BLOCK_MODE                          0x80001008


/**
 * @brief Defines a GPIO error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_GPIO_INVALID_PARAMETER                       0x80001040
/**
 * @brief Defines a GPIO error code to indicate repeated initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_GPIO_REPEAT_INIT                             0x80001041
/**
 * @brief Defines a GPIO error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_GPIO_NOT_INIT                                0x80001042
/**
 * @brief Defines a GPIO error code to indicate a non-support.
 *
 */
#define HAL_WIFI_IOT_ERR_GPIO_NOT_SUPPORT                             0x80001043

/**
 * @brief Defines a flash error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_NOT_INIT                               0x800010C0
/**
 * @brief Defines a flash error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM                          0x800010C1
/**
 * @brief Defines a flash error code to indicate that the address is out of range.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_BEYOND_ADDR              0x800010C2
/**
 * @brief Defines a flash error code to indicate that the parameter size is <b>0</b>
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_SIZE_ZERO                0x800010C3
/**
 * @brief Defines a flash error code to indicate that the erase size is not aligned.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_ERASE_NOT_ALIGN          0x800010C4
/**
 * @brief Defines a flash error code to indicate that the data of the I/O controller is empty.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_IOCTRL_DATA_NULL         0x800010C5
/**
 * @brief Defines a flash error code to indicate empty data.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_DATA_NULL                0x800010C6
/**
 * @brief Defines a flash error code to indicate that pad1 is incorrect.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD1                     0x800010C7
/**
 * @brief Defines a flash error code to indicate that pad2 is incorrect.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD2                     0x800010C8
/**
 * @brief Defines a flash error code to indicate that pad3 is incorrect.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD3                     0x800010C9
/**
 * @brief Defines a flash error code to indicate that pad4 is incorrect.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD4                     0x800010CA
/**
 * @brief Defines a flash error code to indicate a timeout on waiting for ready.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_TIME_OUT_WAIT_READY                    0x800010CB
/**
 * @brief Defines a flash error code to indicate that an error occurs when reading register 1.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_QUAD_MODE_READ_REG1                    0x800010CC
/**
 * @brief Defines a flash error code to indicate that an error occurs when reading register 2.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_QUAD_MODE_READ_REG2                    0x800010CD
/**
 * @brief Defines a flash error code to indicate that an error occurs when comparing registers.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_QUAD_MODE_COMPARE_REG                  0x800010CE
/**
 * @brief Defines a flash error code to indicate a flash mismatch
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_NO_MATCH_FLASH                         0x800010CF
/**
 * @brief Defines a flash error code to indicate a failure in enabling write.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_WRITE_ENABLE                           0x800010D0
/**
 * @brief Defines a flash error code to indicate a mismatch in the size of data to erase.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_NO_MATCH_ERASE_SIZE                    0x800010D1
/**
 * @brief Defines a flash error code to indicate the maximum value of the SPI operation.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_MAX_SPI_OP                             0x800010D2
/**
 * @brief Defines a flash error code to indicate an unsupported IO controller ID..
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_NOT_SUPPORT_IOCTRL_ID                  0x800010D3
/**
 * @brief Defines a flash error code to indicate an invalid chip ID.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INVALID_CHIP_ID                        0x800010D4
/**
 * @brief Defines a flash error code to indicate repeated initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_RE_INIT                                0x800010D5
/**
 * @brief Defines a flash error code to indicate a non-support for data erasure.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_WRITE_NOT_SUPPORT_ERASE                0x800010D6
/**
 * @brief Defines a flash error code to indicate that an error occurs when comparing the data written.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_WRITE_COMPARE_WRONG                    0x800010D7
/**
 * @brief Defines a flash error code to indicate a timeout on waiting for a configuration to start.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_WAIT_CFG_START_TIME_OUT                0x800010D8
/**
 * @brief Defines a flash error code to indicate a partition initialization failure.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_PATITION_INIT_FAIL                     0x800010D9
/**
 * @brief Defines a flash error code to indicate initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_INITILIZATION                          0x800010DA
/**
 * @brief Defines a flash error code to indicate that the size of data to erase is not a multiple of 4K bytes.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_ERASE_NOT_4K_ALIGN                     0x800010DB
/**
 * @brief Defines a flash error code to indicate a non-support.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_PROTECT_NOT_SUPPORT                    0x800010DC
/**
 * @brief Defines a flash error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_PROTECT_NOT_INIT                       0x800010DD
/**
 * @brief Defines a flash error code to indicate repeated initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_PROTECT_RE_INIT                        0x800010DE
/**
 * @brief Defines a flash error code to indicate that no chip is found.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_PROTECT_NOT_FIND_CHIP                  0x800010DF
/**
 * @brief Defines a flash error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_INVALID_PARAM                   0x800010F0
/**
 * @brief Defines a flash error code to indicate that the address is out of range.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_BEYOND_ADDR_SIZE                0x800010F1
/**
 * @brief Defines a flash error code to indicate a failure in applying for memory.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_MALLOC_FAIL                     0x800001F2
/**
 * @brief Defines a flash error code to indicate an encryption error.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_DATA_ENCRYPT_ERR                0x800001F3
/**
 * @brief Defines a flash error code to indicate a decryption error.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_DATA_DECRYPT_ERR                0x800001F4
/**
 * @brief Defines a flash error code to indicate an empty key value.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_KEY_EMPTY_ERR                   0x800001F5
/**
 * @brief Defines a flash error code to indicate a copy failure.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_MEMCPY_FAIL                     0x800001F6
/**
 * @brief Defines a flash error code to indicate a non-support for encryption.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_NOT_SUPPORT                     0x800001F7
/**
 * @brief Defines a flash error code to indicate an incorrect parameter during encryption.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_PREPARE_ERR                     0x800001F8
/**
 * @brief Defines a flash error code to indicate an invalid key.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_KEY_INVALID_ERR                 0x800001F9
/**
 * @brief Defines a flash error code to indicate a failure in saving the key.
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_KEY_SAVE_ERR                    0x800001FA
/**
 * @brief Defines a flash error code to indicate an incorrect kernel address..
 *
 */
#define HAL_WIFI_IOT_ERR_FLASH_CRYPTO_KERNEL_ADDR_ERR                 0x800001FB

/**
 * @brief Defines an I2C error code to indicate a non-support.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_NOT_INIT                                 0x80001180
/**
 * @brief Defines an I2C error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_INVALID_PARAMETER                        0x80001181
/**
 * @brief Defines an I2C error code to indicate a start timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_TIMEOUT_START                            0x80001182
/**
 * @brief Defines an I2C error code to indicate a wait timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_TIMEOUT_WAIT                             0x80001183
/**
 * @brief Defines an I2C error code to indicate a stop timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_TIMEOUT_STOP                             0x80001184
/**
 * @brief Defines an I2C error code to indicate a receive timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_TIMEOUT_RCV_BYTE                         0x80001185
/**
 * @brief Defines an I2C error code to indicate a processing timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_TIMEOUT_RCV_BYTE_PROC                    0x80001186
/**
 * @brief Defines an I2C error code to indicate a waiting failure.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_WAIT_SEM_FAIL                            0x80001187
/**
 * @brief Defines an I2C error code to indicate a responding failure.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_START_ACK_ERR                            0x80001188
/**
 * @brief Defines an I2C error code to indicate a failure in waiting for a response.
 *
 */
#define HAL_WIFI_IOT_ERR_I2C_WAIT_ACK_ERR                             0x80001189

/**
 * @brief Defines an SPI error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_NOT_INIT                                 0x800011C0
/**
 * @brief Defines an SPI error code to indicate repeated initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_REINIT                                   0x800011C1
/**
 * @brief Defines an SPI error code to indicate a parameter error.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_PARAMETER_WRONG                          0x800011C2
/**
 * @brief Defines an SPI error code to indicate the busy state.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_BUSY                                     0x800011C3
/**
 * @brief Defines an SPI error code to indicate a write timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_WRITE_TIMEOUT                            0x800011C4
/**
 * @brief Defines an SPI error code to indicate a read timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_READ_TIMEOUT                             0x800011C5
/**
 * @brief Defines an SPI error code to indicate a non-support for DMA.
 *
 */
#define HAL_WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA                          0x800011C6

/**
 * @brief Defines an SDIO error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_SDIO_INVALID_PARAMETER                       0x80001280


/**
 * @brief Defines an ADC error code to indicate a parameter error.
 *
 */
#define HAL_WIFI_IOT_ERR_ADC_PARAMETER_WRONG                          0x80001300
/**
 * @brief Defines an ADC error code to indicate an invalid channel.
 *
 */
#define HAL_WIFI_IOT_ERR_ADC_INVALID_CHANNEL_ID                       0x80001301
/**
 * @brief Defines an ADC error code to indicate a timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_ADC_TIMEOUT                                  0x80001302
/**
 * @brief Defines an ADC error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_ADC_NOT_INIT                                 0x80001303

/**
 * @brief Defines a PWM error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_PWM_NO_INIT                                  0x80001340
/**
 * @brief Defines a PWM error code to indicate an initialization error.
 *
 */
#define HAL_WIFI_IOT_ERR_PWM_INITILIZATION_ALREADY                    0x80001341
/**
 * @brief Defines a PWM error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_PWM_INVALID_PARAMETER                        0x80001342

/**
 * @brief Defines a DMA error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_INVALID_PARA                             0x80001380
/**
 * @brief Defines a DMA error code to indicate non-initialization.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_NOT_INIT                                 0x80001381
/**
 * @brief Defines a DMA error code to indicate the busy state.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_BUSY                                     0x80001382
/**
 * @brief Defines a DMA error code to indicate a transmission failure.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_TRANSFER_FAIL                            0x80001383
/**
 * @brief Defines a DMA error code to indicate a transmission timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_TRANSFER_TIMEOUT                         0x80001384
/**
 * @brief Defines a DMA error code to indicate a retrieval failure.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_GET_NOTE_FAIL                            0x80001385
/**
 * @brief Defines a DMA error code to indicate that the LLI is not created.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_LLI_NOT_CREATE                           0x80001386
/**
 * @brief Defines a DMA error code to indicate a failure in enabling channel interrupt.
 *
 */
#define HAL_WIFI_IOT_ERR_DMA_CH_IRQ_ENABLE_FAIL                       0x80001387

/**
 * @brief Defines an I2S error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_I2S_INVALID_PARAMETER                        0x80001400
/**
 * @brief Defines an I2S error code to indicate a write timeout.
 *
 */
#define HAL_WIFI_IOT_ERR_I2S_WRITE_TIMEOUT                            0x80001401

/**
 * @brief Defines an AT error code to indicate repeated function registration.
 *
 */
#define HAL_WIFI_IOT_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED           0x80003280
/**
 * @brief Defines an AT error code to indicate an invalid parameter.
 *
 */
#define HAL_WIFI_IOT_ERR_AT_INVALID_PARAMETER                        0x80003281

#endif
/** @} */
