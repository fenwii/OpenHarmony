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
 * @file wifiiot_gpio_ex.h
 *
 * @brief Declares the extended GPIO interface functions.
 *
 * These functions are used for settings GPIO pulls and driver strength. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_GPIO_EX_H
#define WIFIIOT_GPIO_EX_H

/**
 * @brief Enumerates GPIO hardware pin IDs.
 */
typedef enum {
    /** GPIO hardware pin 0 */
    WIFI_IOT_IO_NAME_GPIO_0,
    /** GPIO hardware pin 1 */
    WIFI_IOT_IO_NAME_GPIO_1,
    /** GPIO hardware pin 2 */
    WIFI_IOT_IO_NAME_GPIO_2,
    /** GPIO hardware pin 3 */
    WIFI_IOT_IO_NAME_GPIO_3,
    /** GPIO hardware pin 4 */
    WIFI_IOT_IO_NAME_GPIO_4,
    /** GPIO hardware pin 5 */
    WIFI_IOT_IO_NAME_GPIO_5,
    /** GPIO hardware pin 6 */
    WIFI_IOT_IO_NAME_GPIO_6,
    /** GPIO hardware pin 7 */
    WIFI_IOT_IO_NAME_GPIO_7,
    /** GPIO hardware pin 8 */
    WIFI_IOT_IO_NAME_GPIO_8,
    /** GPIO hardware pin 9 */
    WIFI_IOT_IO_NAME_GPIO_9,
    /** GPIO hardware pin 10 */
    WIFI_IOT_IO_NAME_GPIO_10,
    /** GPIO hardware pin 11 */
    WIFI_IOT_IO_NAME_GPIO_11,
    /** GPIO hardware pin 12 */
    WIFI_IOT_IO_NAME_GPIO_12,
    /** GPIO hardware pin 13 */
    WIFI_IOT_IO_NAME_GPIO_13,
    /** GPIO hardware pin 14 */
    WIFI_IOT_IO_NAME_GPIO_14,
    /** Maximum value */
    WIFI_IOT_IO_NAME_MAX,
} WifiIotIoName;

/**
 * @brief Enumerates the functions of GPIO hardware pin 0.
 */
typedef enum {
    /** GPIO0 function */
    WIFI_IOT_IO_FUNC_GPIO_0_GPIO,
    /** Functions of UART1 TXD */
    WIFI_IOT_IO_FUNC_GPIO_0_UART1_TXD = 2,
    /** SPI1 CK function */
    WIFI_IOT_IO_FUNC_GPIO_0_SPI1_CK,
    /** Functions of JTAG TD0 */
    WIFI_IOT_IO_FUNC_GPIO_0_JTAG_TDO,
    /** PWM3 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_0_PWM3_OUT,
    /** I2C1 SDA function */
    WIFI_IOT_IO_FUNC_GPIO_0_I2C1_SDA,
} WifiIotIoFuncGpio0;

/**
 * @brief Enumerates the functions of GPIO hardware pin 1.
 */
typedef enum {
    /** GPIO1 function */
    WIFI_IOT_IO_FUNC_GPIO_1_GPIO,
    WIFI_IOT_IO_FUNC_GPIO_1_UART1_RXD = 2,
    WIFI_IOT_IO_FUNC_GPIO_1_SPI1_RXD,
    WIFI_IOT_IO_FUNC_GPIO_1_JTAG_TCK,
    WIFI_IOT_IO_FUNC_GPIO_1_PWM4_OUT,
    WIFI_IOT_IO_FUNC_GPIO_1_I2C1_SCL,
    WIFI_IOT_IO_FUNC_GPIO_1_BT_FREQ,
} WifiiIotIoFuncGpio1;

/**
 * @brief Enumerates the functions of GPIO hardware pin 2.
 */
typedef enum {
    /** GPIO2 function */
    WIFI_IOT_IO_FUNC_GPIO_2_GPIO,
    /** UART1 RTS function */
    WIFI_IOT_IO_FUNC_GPIO_2_UART1_RTS_N = 2,
    /** SPI1 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_2_SPI1_TXD,
    /** JTAG TRSTN function */
    WIFI_IOT_IO_FUNC_GPIO_2_JTAG_TRSTN,
    /** PWM2 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_2_PWM2_OUT,
    /** SSI CLK function */
    WIFI_IOT_IO_FUNC_GPIO_2_SSI_CLK = 7,
} WifiIotIoFuncGpio2;

/**
 * @brief Enumerates the functions of GPIO hardware pin 3.
 */
typedef enum {
    /** GPIO3 function */
    WIFI_IOT_IO_FUNC_GPIO_3_GPIO,
    /** UART0 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_3_UART0_TXD,
    /** UART1 CTS function */
    WIFI_IOT_IO_FUNC_GPIO_3_UART1_CTS_N,
    /** SPI CSN function */
    WIFI_IOT_IO_FUNC_GPIO_3_SPI1_CSN,
    /** JTAG TDI function */
    WIFI_IOT_IO_FUNC_GPIO_3_JTAG_TDI,
    /** PWM5 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_3_PWM5_OUT,
    /** I2C1 SDA function */
    WIFI_IOT_IO_FUNC_GPIO_3_I2C1_SDA,
    /** SSI DATA function */
    WIFI_IOT_IO_FUNC_GPIO_3_SSI_DATA,
} WifiIotIoFuncGpio3;

/**
 * @brief Enumerates the functions of GPIO hardware pin 4.
 */
typedef enum {
    /** GPIO4 function */
    WIFI_IOT_IO_FUNC_GPIO_4_GPIO,
    /** UART0 RXD function */
    WIFI_IOT_IO_FUNC_GPIO_4_UART0_RXD = 2,
    /** JTAG TMS function */
    WIFI_IOT_IO_FUNC_GPIO_4_JTAG_TMS = 4,
    /** PWM1 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_4_PWM1_OUT,
    /** I2C1 SCL function */
    WIFI_IOT_IO_FUNC_GPIO_4_I2C1_SCL,
} WifiIotIoFuncGpio4;

/**
 * @brief Enumerates the functions of GPIO hardware pin 5.
 */
typedef enum {
    /** GPIO5 function */
    WIFI_IOT_IO_FUNC_GPIO_5_GPIO,
    /** UART1 RXD function */
    WIFI_IOT_IO_FUNC_GPIO_5_UART1_RXD = 2,
    /** SPI0 CSN function */
    WIFI_IOT_IO_FUNC_GPIO_5_SPI0_CSN,
    /** PWM2 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_5_PWM2_OUT = 5,
    /** I2C0 MCLK function */
    WIFI_IOT_IO_FUNC_GPIO_5_I2S0_MCLK,
    /** BT STATUS function */
    WIFI_IOT_IO_FUNC_GPIO_5_BT_STATUS,
} WifiIotIoFuncGpio5;

/**
 * @brief Enumerates the functions of GPIO hardware pin 6.
 */
typedef enum {
    /** GPIO6 function */
    WIFI_IOT_IO_FUNC_GPIO_6_GPIO,
    /** UART1 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_6_UART1_TXD = 2,
    /** SPI0 CK function */
    WIFI_IOT_IO_FUNC_GPIO_6_SPI0_CK,
    /** PWM3 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_6_PWM3_OUT = 5,
    /** I2S0 TX function */
    WIFI_IOT_IO_FUNC_GPIO_6_I2S0_TX,
    /** COEX switch function */
    WIFI_IOT_IO_FUNC_GPIO_6_COEX_SWITCH,
} WifiIotIoFuncGpio6;

/**
 * @brief Enumerates the functions of GPIO hardware pin 7.
 */
typedef enum {
    /** GPIO7 function */
    WIFI_IOT_IO_FUNC_GPIO_7_GPIO,
    /** UART1 CTS function */
    WIFI_IOT_IO_FUNC_GPIO_7_UART1_CTS_N = 2,
    /** SPI0 RXD function */
    WIFI_IOT_IO_FUNC_GPIO_7_SPI0_RXD,
    /** PWM0 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_7_PWM0_OUT = 5,
    /** I2S0 BCLK function */
    WIFI_IOT_IO_FUNC_GPIO_7_I2S0_BCLK,
    /** BT ACTIVE function */
    WIFI_IOT_IO_FUNC_GPIO_7_BT_ACTIVE,
} WifiIotIoFuncGpio7;

/**
 * @brief Enumerates the functions of GPIO hardware pin 8.
 */
typedef enum {
    /** GPIO8 function */
    WIFI_IOT_IO_FUNC_GPIO_8_GPIO,
    /** UART1 RTS function */
    WIFI_IOT_IO_FUNC_GPIO_8_UART1_RTS_N = 2,
    /** SPI0 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_8_SPI0_TXD,
    /** PWM1 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_8_PWM1_OUT = 5,
    /** I2S0 WS function */
    WIFI_IOT_IO_FUNC_GPIO_8_I2S0_WS,
    /** WLAN ACTIVE function */
    WIFI_IOT_IO_FUNC_GPIO_8_WLAN_ACTIVE,
} WifiIotIoFuncGpio8;

/**
 * @brief Enumerates the functions of GPIO hardware pin 9.
 */
typedef enum {
    /** GPIO9 function */
    WIFI_IOT_IO_FUNC_GPIO_9_GPIO,
    /** I2C0 SCL function */
    WIFI_IOT_IO_FUNC_GPIO_9_I2C0_SCL,
    /** UART2 RTS function */
    WIFI_IOT_IO_FUNC_GPIO_9_UART2_RTS_N,
    /** SDIO D2 function */
    WIFI_IOT_IO_FUNC_GPIO_9_SDIO_D2,
    /** SPI0 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_9_SPI0_TXD,
    /** PWM0 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_9_PWM0_OUT,
    /** I2S0 MCLK function */
    WIFI_IOT_IO_FUNC_GPIO_9_I2S0_MCLK = 7,
} WifiIotIoFuncGpio9;

/**
 * @brief Enumerates the functions of GPIO hardware pin 10.
 */
typedef enum {
    /** GPIO10 function */
    WIFI_IOT_IO_FUNC_GPIO_10_GPIO,
    /** I2C0 SDA function */
    WIFI_IOT_IO_FUNC_GPIO_10_I2C0_SDA,
    /** UART2 CTS function */
    WIFI_IOT_IO_FUNC_GPIO_10_UART2_CTS_N,
    /** SDIO D3 function */
    WIFI_IOT_IO_FUNC_GPIO_10_SDIO_D3,
    /** SPI0 CK function */
    WIFI_IOT_IO_FUNC_GPIO_10_SPI0_CK,
    /** PWM1 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_10_PWM1_OUT,
    /** I2S0 TX function */
    WIFI_IOT_IO_FUNC_GPIO_10_I2S0_TX = 7,
} WifiIotIoFuncGpio10;

/**
 * @brief Enumerates the functions of GPIO hardware pin 11.
 */
typedef enum {
    /** GPIO11 function */
    WIFI_IOT_IO_FUNC_GPIO_11_GPIO,
    /** UART2 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_11_UART2_TXD = 2,
    /** SDIO CMD function */
    WIFI_IOT_IO_FUNC_GPIO_11_SDIO_CMD,
    /** SDIO RXD function */
    WIFI_IOT_IO_FUNC_GPIO_11_SPI0_RXD,
    /** PWM2 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_11_PWM2_OUT,
    /** RF TX_EN_EXT function */
    WIFI_IOT_IO_FUNC_GPIO_11_RF_TX_EN_EXT,
    /** I2S0 RX function */
    WIFI_IOT_IO_FUNC_GPIO_11_I2S0_RX,
} WifiIotIoFuncGpio11;

/**
 * @brief Enumerates the functions of GPIO hardware pin 12.
 */
typedef enum {
    /** GPIO12 function */
    WIFI_IOT_IO_FUNC_GPIO_12_GPIO,
    /** SUART2 RXD function */
    WIFI_IOT_IO_FUNC_GPIO_12_UART2_RXD = 2,
    /** SDIO CLK function */
    WIFI_IOT_IO_FUNC_GPIO_12_SDIO_CLK,
    /** SDIO CSN function */
    WIFI_IOT_IO_FUNC_GPIO_12_SPI0_CSN,
    /** PWM3 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_12_PWM3_OUT,
    /** RF RX_EN_EXT function */
    WIFI_IOT_IO_FUNC_GPIO_12_RF_RX_EN_EXT,
    /** I2S0 BCLK function */
    WIFI_IOT_IO_FUNC_GPIO_12_I2S0_BCLK,
} WifiIotIoFuncGpio12;

/**
 * @brief Enumerates the functions of GPIO hardware pin 13.
 */
typedef enum {
    /** SSI DATA function */
    WIFI_IOT_IO_FUNC_GPIO_13_SSI_DATA,
    /** UART0 TXD function */
    WIFI_IOT_IO_FUNC_GPIO_13_UART0_TXD,
    /** UART2 RTS function */
    WIFI_IOT_IO_FUNC_GPIO_13_UART2_RTS_N,
    /** SDIO D0 function */
    WIFI_IOT_IO_FUNC_GPIO_13_SDIO_D0,
    /** GPIO13 function */
    WIFI_IOT_IO_FUNC_GPIO_13_GPIO,
    /** PWM4 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_13_PWM4_OUT,
    /** I2C0 SDA function */
    WIFI_IOT_IO_FUNC_GPIO_13_I2C0_SDA,
    /** I2S0 WS function */
    WIFI_IOT_IO_FUNC_GPIO_13_I2S0_WS,
} WifiIotIoFuncGpio13;

/**
 * @brief Enumerates the functions of GPIO hardware pin 14.
 */
typedef enum {
    /** SSI CLK function */
    WIFI_IOT_IO_FUNC_GPIO_14_SSI_CLK,
    /** UART0 RXD function */
    WIFI_IOT_IO_FUNC_GPIO_14_UART0_RXD,
    /** UART2 CTS function */
    WIFI_IOT_IO_FUNC_GPIO_14_UART2_CTS_N,
    /** SDIO D1 function */
    WIFI_IOT_IO_FUNC_GPIO_14_SDIO_D1,
    /** GPIO14 function */
    WIFI_IOT_IO_FUNC_GPIO_14_GPIO,
    /** PWM5 OUT function */
    WIFI_IOT_IO_FUNC_GPIO_14_PWM5_OUT,
    /** I2C0 SCL function */
    WIFI_IOT_IO_FUNC_GPIO_14_I2C0_SCL,
} WifiIotIoFuncGpio14;

/**
 * @brief Enumerates I/O driver strength levels.
 *
 */
typedef enum {
    /** Driver strength level 0 (highest) */
    WIFI_IOT_IO_DRIVER_STRENGTH_0 = 0,
    /** Driver strength level 1 */
    WIFI_IOT_IO_DRIVER_STRENGTH_1,
    /** Driver strength level 2 */
    WIFI_IOT_IO_DRIVER_STRENGTH_2,
    /** Driver strength level 3 */
    WIFI_IOT_IO_DRIVER_STRENGTH_3,
    /** Driver strength level 4 */
    WIFI_IOT_IO_DRIVER_STRENGTH_4,
    /** Driver strength level 5 */
    WIFI_IOT_IO_DRIVER_STRENGTH_5,
    /** Driver strength level 6 */
    WIFI_IOT_IO_DRIVER_STRENGTH_6,
    /** Driver strength level 7 (lowest) */
    WIFI_IOT_IO_DRIVER_STRENGTH_7,
    /** Maximum value */
    WIFI_IOT_IO_DRIVER_STRENGTH_MAX,
} WifiIotIoDriverStrength;

/**
 * @brief Enumerates GPIO pull-up or pull-down settings.
 */
typedef enum {
    /** No pull */
    WIFI_IOT_IO_PULL_NONE,
    /** Pull-up */
    WIFI_IOT_IO_PULL_UP,
    /** Pull-down */
    WIFI_IOT_IO_PULL_DOWN,
    /** Maximum value */
    WIFI_IOT_IO_PULL_MAX,
} WifiIotIoPull;

/**
 * @brief Sets the pull for a GPIO pin.
 *
 * @param id Indicates the GPIO pin.
 * @param val Indicates the pull-up or pull-down to set.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int IoSetPull(WifiIotIoName id, WifiIotIoPull val);

/**
 * @brief Sets the multiplexing function for a GPIO pin.
 *
 * @param id Indicates the GPIO pin.
 * @param val Indicates the I/O multiplexing function. For example,
 * if the value of <b>id</b> is {@link WIFI_IOT_IO_NAME_GPIO_0},
 * the value type of <b>val</b> is {@link WifiIotIoFuncGpio0}.
 * If the value of <b>id</b> is {@link WIFI_IOT_IO_NAME_GPIO_1},
 * the value type of <b>val</b> is {@link WifiIotIoFuncGpio1}.
 * The same rule applies to other values.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int IoSetFunc(WifiIotIoName id, unsigned char val);

/**
 * @brief Obtains the pull type of a GPIO pin.
 *
 * @param id Indicates the GPIO pin.
 * @param val Indicates the pointer to the address where the pull type is to be stored.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int IoGetPull(WifiIotIoName id, WifiIotIoPull *val);

/**
 * @brief Obtains the multiplexing function for a GPIO pin.
 *
 * @param id Indicates the GPIO pin.
 * @param val Indicates the pointer to the address whether I/O multiplexing function is to be stored.
 * For example, if the value of <b>id</b> is {@link WIFI_IOT_IO_NAME_GPIO_0},
 * the value type of <b>val</b> is {@link WifiIotIoFuncGpio0}.
 * If the value of <b>id</b> is {@link WIFI_IOT_IO_NAME_GPIO_1},
 * the value type of <b>val</b> is {@link WifiIotIoFuncGpio1}.
 * The same rule applies to other values.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int IoGetFunc(WifiIotIoName id, unsigned char *val);

/**
 * @brief Obtains the driver strength of a GPIO pin.
 *
 * @param id Indicates the GPIO pin.
 * @param val Indicates the pointer to the address
 * where the I/O driver strength level is to be stored.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int IOGetDriverStrength(WifiIotIoName id, WifiIotIoDriverStrength *val);

/**
 * @brief Sets the driver strength of a GPIO pin.
 *
 * @param id Indicates the GPIO pin.
 * @param val Indicates the I/O driver strength level obtained.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int IOSetDriverStrength(WifiIotIoName id, WifiIotIoDriverStrength val);

#endif
/** @} */
