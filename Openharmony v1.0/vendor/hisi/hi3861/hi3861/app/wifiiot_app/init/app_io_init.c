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

#include <hi_io.h>

hi_void app_io_init(hi_void)
{
    /* 用户需根据应用场景，合理选择各外设的IO复用配置，此处仅列出示例 */
#ifdef CONFIG_UART0_SUPPORT
    /* uart0 调试串口 */
    hi_io_set_func(HI_IO_NAME_GPIO_3, HI_IO_FUNC_GPIO_3_UART0_TXD); /* uart0 tx */
    hi_io_set_func(HI_IO_NAME_GPIO_4, HI_IO_FUNC_GPIO_4_UART0_RXD); /* uart0 rx */
#endif

#ifdef CONFIG_UART1_SUPPORT
    /* uart1 AT命令串口 */
    hi_io_set_func(HI_IO_NAME_GPIO_5, HI_IO_FUNC_GPIO_5_UART1_RXD); /* uart1 rx */
    hi_io_set_func(HI_IO_NAME_GPIO_6, HI_IO_FUNC_GPIO_6_UART1_TXD); /* uart1 tx */
#endif

#ifdef CONFIG_UART2_SUPPORT
    /* uart2 sigma认证使用串口 */
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_UART2_TXD); /* uart2 tx */
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_UART2_RXD); /* uart2 rx */
#endif

    /* SPI MUX: */
#ifdef CONFIG_SPI_SUPPORT
    /* SPI IO复用也可以选择5/6/7/8;0/1/2/3, 根据产品设计选择 */
    hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_SPI0_TXD);
    hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_SPI0_CK);
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_SPI0_RXD);
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_SPI0_CSN);
    hi_io_set_driver_strength(HI_IO_NAME_GPIO_9, HI_IO_DRIVER_STRENGTH_0);
#endif

    /* I2C MUX: */
#ifdef CONFIG_I2C_SUPPORT
    /* I2C IO复用也可以选择3/4; 9/10，根据产品设计选择 */
    hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_I2C1_SDA);
    hi_io_set_func(HI_IO_NAME_GPIO_1, HI_IO_FUNC_GPIO_1_I2C1_SCL);
#endif

    /* PWM MUX: */
#ifdef CONFIG_PWM_SUPPORT
    /* PWM 0/2/3/4/5 配置同理 */
    hi_io_set_func(HI_IO_NAME_GPIO_8, HI_IO_FUNC_GPIO_8_PWM1_OUT);
#endif

    /* I2S MUX: */
#ifdef CONFIG_I2S_SUPPORT
    hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_I2S0_MCLK);
    hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_I2S0_TX);
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_I2S0_RX);
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_I2S0_BCLK);
    hi_io_set_func(HI_IO_NAME_GPIO_13, HI_IO_FUNC_GPIO_13_I2S0_WS);
#endif

    /* SDIO MUX: */
#ifdef CONFIG_SDIO_SUPPORT
    (hi_void)hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_SDIO_D2);
    (hi_void)hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_SDIO_D3);
    (hi_void)hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_SDIO_CMD);
    (hi_void)hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_SDIO_CLK);
    (hi_void)hi_io_set_func(HI_IO_NAME_GPIO_13, HI_IO_FUNC_GPIO_13_SDIO_D0);
    (hi_void)hi_io_set_func(HI_IO_NAME_GPIO_14, HI_IO_FUNC_GPIO_14_SDIO_D1);

    (hi_void)hi_io_set_pull(HI_IO_NAME_GPIO_9, HI_IO_PULL_UP);
    (hi_void)hi_io_set_pull(HI_IO_NAME_GPIO_10, HI_IO_PULL_UP);
    (hi_void)hi_io_set_pull(HI_IO_NAME_GPIO_11, HI_IO_PULL_UP);
    (hi_void)hi_io_set_pull(HI_IO_NAME_GPIO_13, HI_IO_PULL_UP);
    (hi_void)hi_io_set_pull(HI_IO_NAME_GPIO_14, HI_IO_PULL_UP);
#endif
}

