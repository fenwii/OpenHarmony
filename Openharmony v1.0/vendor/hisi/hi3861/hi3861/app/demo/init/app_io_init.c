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

#include <hi_io.h>
#include <hi3861_platform.h>

hi_void app_io_set_gpio2_clkout_enable(hi_bool enable)
{
    if (enable == HI_TRUE) {
        hi_io_set_input_enable(HI_IO_NAME_GPIO_2, HI_TRUE);
        hi_reg_write16(DIAG_CTL_DIAG_MUX, 0x2);
        hi_reg_write16(DIAG_CTL_CLOCK_TEST_DIV, 0x0);
        hi_reg_write16(DIAG_CTL_CLOCK_TEST_EN, 0x3FFF);
        hi_reg_write16(DIAG_CTL_CLOCK_TEST_SEL, 0x1);
        hi_io_set_func(HI_IO_NAME_GPIO_2, 0x6); /* let gpio2 output clk. */
        hi_io_set_driver_strength(HI_IO_NAME_GPIO_2, HI_IO_DRIVER_STRENGTH_3);
    } else {
        hi_io_set_func(HI_IO_NAME_GPIO_2, HI_IO_FUNC_GPIO_2_GPIO);
        hi_io_set_input_enable(HI_IO_NAME_GPIO_2, HI_FALSE); /* set io enable false, for low power. */
        hi_io_set_pull(HI_IO_NAME_GPIO_2, HI_IO_PULL_NONE);
    }
}

hi_void app_io_init(hi_void)
{
    /*
     * You need to select the I/O multiplexing configuration of each peripheral
     * based on the application scenario. The following is an example.
     */
#ifdef CONFIG_UART0_SUPPORT
    /* Configure UART0 as the debugging serial port. */
    hi_io_set_func(HI_IO_NAME_GPIO_3, HI_IO_FUNC_GPIO_3_UART0_TXD); /* uart0 tx */
    hi_io_set_func(HI_IO_NAME_GPIO_4, HI_IO_FUNC_GPIO_4_UART0_RXD); /* uart0 rx */
#endif

#ifdef CONFIG_UART1_SUPPORT
    /* Configure UART1 as the AT command serial port. */
    hi_io_set_func(HI_IO_NAME_GPIO_5, HI_IO_FUNC_GPIO_5_UART1_RXD); /* uart1 rx */
    hi_io_set_func(HI_IO_NAME_GPIO_6, HI_IO_FUNC_GPIO_6_UART1_TXD); /* uart1 tx */
#endif

#ifdef CONFIG_UART2_SUPPORT
    /* Configure UART1 as the SIGMA authentication serial port. */
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_UART2_TXD); /* uart2 tx */
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_UART2_RXD); /* uart2 rx */
#endif

    /* SPI MUX: */
#ifdef CONFIG_SPI_SUPPORT
    /* The SPI I/O multiplexing mode can also be 5/6/7/8 or 0/1/2/3 based on the product design. */
    hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_SPI0_TXD);
    hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_SPI0_CK);
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_SPI0_RXD);
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_SPI0_CSN);
    hi_io_set_driver_strength(HI_IO_NAME_GPIO_9, HI_IO_DRIVER_STRENGTH_0);
#endif

    /* I2C MUX: */
#ifdef CONFIG_I2C_SUPPORT
    /* The I2C I/O multiplexing mode can also be 3/4 or 9/10 based on the product design. */
    hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_I2C1_SDA);
    hi_io_set_func(HI_IO_NAME_GPIO_1, HI_IO_FUNC_GPIO_1_I2C1_SCL);
#endif

    /* PWM MUX: */
#ifdef CONFIG_PWM_SUPPORT
    /* The configurations for multiplexing 0/2/3/4/5 into PWM are similar. */
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

