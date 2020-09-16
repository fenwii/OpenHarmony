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

#ifndef __ASM_PLATFORM_H__
#define __ASM_PLATFORM_H__

#include "menuconfig.h"
#include "los_bitmap.h"
#include "asm/hal_platform_ints.h"
#include "hisoc/timer.h"
#include "hisoc/uart.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*------------------------------------------------
 * GIC reg base address
 *------------------------------------------------*/
#define GIC_BASE_ADDR             IO_DEVICE_ADDR(0x10300000)
#define GICD_OFFSET               0x1000     /* interrupt distributor offset */
#define GICC_OFFSET               0x2000     /* CPU interface register offset */

#define FMC_MEM_PBASE             0x14000000
#define FMC_MEM_OFFSIZE           0x8
#define FMC_REG_PBASE             0x10000000
#define FMC_REG_OFFSIZE           0xdc

#define PERIPH_REG_BASE           IO_DEVICE_ADDR(0x12000000)
#define IO_CTL_REG_VBASE          IO_DEVICE_ADDR(0x10F00000)

#define SDIO0_REG_PBASE           0x10010000
#define SDIO1_REG_PBASE           0x10020000
#define MMC_REG_OFFSIZE           0x600

#define ETH_REG_PBASE             0x10040000
#define ETH_REG_BASE              IO_DEVICE_ADDR(0x10040000)
#define ETH_REG_OFFSIZE           0x2000
#define DMAC_REG_BASE             IO_DEVICE_ADDR(0x100b0000)
#define IO_MUX_REG_BASE           IO_DEVICE_ADDR(0x100c0000)

#define IO_CTL_REG_BASE           IO_DEVICE_ADDR(0x10FF0000)

#define GPIO_REG_BASE             IO_DEVICE_ADDR(0x120b0000)
#define GPIO0_REG_BASE            (GPIO_REG_BASE + 0x0000)
#define GPIO1_REG_BASE            (GPIO_REG_BASE + 0x1000)
#define GPIO2_REG_BASE            (GPIO_REG_BASE + 0x2000)
#define GPIO3_REG_BASE            (GPIO_REG_BASE + 0x3000)
#define GPIO4_REG_BASE            (GPIO_REG_BASE + 0x4000)
#define GPIO5_REG_BASE            (GPIO_REG_BASE + 0x5000)
#define GPIO6_REG_BASE            (GPIO_REG_BASE + 0x6000)
#define GPIO7_REG_BASE            (GPIO_REG_BASE + 0x7000)
#define GPIO8_REG_BASE            (GPIO_REG_BASE + 0x8000)
#define GPIO9_REG_BASE            (GPIO_REG_BASE + 0x9000)

#define SPI0_REG_BASE             IO_DEVICE_ADDR(0x12070000)
#define SPI1_REG_BASE             IO_DEVICE_ADDR(0x12071000)

#define I2C0_REG_PBASE            0x12060000
#define I2C1_REG_PBASE            0x12061000
#define I2C2_REG_PBASE            0x12062000
#define I2C0_REG_BASE             IO_DEVICE_ADDR(0x12060000)
#define I2C1_REG_BASE             IO_DEVICE_ADDR(0x12061000)
#define I2C2_REG_BASE             IO_DEVICE_ADDR(0x12062000)

#define UART0_REG_BASE            IO_DEVICE_ADDR(0x12040000)
#define UART1_REG_BASE            IO_DEVICE_ADDR(0x12041000)
#define UART2_REG_BASE            IO_DEVICE_ADDR(0x12042000)

#define UART0_REG_PBASE           0x12040000
#define UART1_REG_PBASE           0x12041000
#define UART2_REG_PBASE           0x12042000

#if (CONSOLE_UART == UART0)
    #define UART_BASE             UART0_REG_BASE
    #define UART0_INT_NUM    NUM_HAL_INTERRUPT_UART0
#elif (CONSOLE_UART == UART1)
    #define UART_BASE             UART1_REG_BASE
    #define UART0_INT_NUM    NUM_HAL_INTERRUPT_UART1
#elif (CONSOLE_UART == UART2)
    #define UART_BASE             UART2_REG_BASE
    #define UART0_INT_NUM    NUM_HAL_INTERRUPT_UART2
#endif

#define MISC_REG_BASE             IO_DEVICE_ADDR(0x12028000)
#define SYS_CTRL_REG_BASE         IO_DEVICE_ADDR(0x12020000)
#define CRG_REG_BASE              IO_DEVICE_ADDR(0x12010000)

#define TIMER0_ENABLE             BIT(16)
#define TIMER1_ENABLE             BIT(17)
#define TIMER2_ENABLE             BIT(18)
#define TIMER3_ENABLE             BIT(19)

#define TIMER0_REG_BASE           IO_DEVICE_ADDR(0x12000000)
#define TIMER1_REG_BASE           IO_DEVICE_ADDR(0x12000020)
#define TIMER2_REG_BASE           IO_DEVICE_ADDR(0x12001000)
#define TIMER3_REG_BASE           IO_DEVICE_ADDR(0x12001020)

#define TIMER_TICK_REG_BASE       TIMER0_REG_BASE   /* timer for tick */
#define TIMER_TICK_ENABLE         TIMER0_ENABLE
#define TIMER_TIME_REG_BASE       TIMER1_REG_BASE   /* timer for time */
#define TIMER_TIME_ENABLE         TIMER1_ENABLE
#define HRTIMER_TIMER_REG_BASE    TIMER3_REG_BASE /* timer for hrtimer */
#define HRTIMER_TIMER_ENABLE      TIMER3_ENABLE

#define DDR_MEM_BASE              0x40000000
#define CACHE_ALIGNED_SIZE        64

#define write_reg_bit(value, offset, addr) ({ \
        unsigned long t, mask; \
        mask = 1 << (offset); \
        t = GET_UINT32(addr); \
        t &= ~mask;            \
        t |= (value << (offset)) & mask; \
        WRITE_UINT32(t, addr);   \
    })

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif

