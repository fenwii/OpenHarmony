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

#ifndef    __ASM_PLATFORM_H__
#define    __ASM_PLATFORM_H__

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
#define GICD_OFFSET               0x1000                          /* interrupt distributor offset */
#define GICC_OFFSET               0x2000                          /* CPU interface register offset */

#define DDR_MEM_BASE              0x80000000

#define FMC_MEM_PBASE             0x14000000
#define FMC_MEM_OFFSIZE           0x8

#define IO_CTL_REG_BASE           IO_DEVICE_ADDR(0x10FF0000)

#define GPIO_REG_ADDR             0x120d0000
#define GPIO11_REG_BASE           IO_DEVICE_ADDR(GPIO_REG_ADDR + 0xb000)
#define GPIO10_REG_BASE           IO_DEVICE_ADDR(GPIO_REG_ADDR + 0xa000)
#define GPIO9_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x9000)
#define GPIO8_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x8000)
#define GPIO7_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x7000)
#define GPIO6_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x6000)
#define GPIO5_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x5000)
#define GPIO4_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x4000)
#define GPIO3_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x3000)
#define GPIO2_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x2000)
#define GPIO1_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x1000)
#define GPIO0_REG_BASE            IO_DEVICE_ADDR(GPIO_REG_ADDR + 0x0000)

#define SPI_REG_ADDR              IO_DEVICE_ADDR(0x120c0000)
#define SPI2_REG_BASE             (SPI_REG_ADDR + 0x2000)
#define SPI1_REG_BASE             (SPI_REG_ADDR + 0x1000)
#define SPI0_REG_BASE             (SPI_REG_ADDR + 0x0000)

#define I2C_REG_ADDR              0x120b0000
#define I2C7_REG_PBASE            (I2C_REG_ADDR + 0x7000)
#define I2C6_REG_PBASE            (I2C_REG_ADDR + 0x6000)
#define I2C5_REG_PBASE            (I2C_REG_ADDR + 0x5000)
#define I2C4_REG_PBASE            (I2C_REG_ADDR + 0x4000)
#define I2C3_REG_PBASE            (I2C_REG_ADDR + 0x3000)
#define I2C2_REG_PBASE            (I2C_REG_ADDR + 0x2000)
#define I2C1_REG_PBASE            (I2C_REG_ADDR + 0x1000)
#define I2C0_REG_PBASE            (I2C_REG_ADDR + 0x0000)

#define I2C7_REG_BASE             IO_DEVICE_ADDR(I2C7_REG_PBASE)
#define I2C6_REG_BASE             IO_DEVICE_ADDR(I2C6_REG_PBASE)
#define I2C5_REG_BASE             IO_DEVICE_ADDR(I2C5_REG_PBASE)
#define I2C4_REG_BASE             IO_DEVICE_ADDR(I2C4_REG_PBASE)
#define I2C3_REG_BASE             IO_DEVICE_ADDR(I2C3_REG_PBASE)
#define I2C2_REG_BASE             IO_DEVICE_ADDR(I2C2_REG_PBASE)
#define I2C1_REG_BASE             IO_DEVICE_ADDR(I2C1_REG_PBASE)
#define I2C0_REG_BASE             IO_DEVICE_ADDR(I2C0_REG_PBASE)

#define UART_REG_ADDR             0x120a0000
#define UART4_REG_PBASE           (UART_REG_ADDR + 0x4000)
#define UART3_REG_PBASE           (UART_REG_ADDR + 0x3000)
#define UART2_REG_PBASE           (UART_REG_ADDR + 0x2000)
#define UART1_REG_PBASE           (UART_REG_ADDR + 0x1000)
#define UART0_REG_PBASE           (UART_REG_ADDR + 0x0000)
#define UART4_REG_BASE            IO_DEVICE_ADDR(UART4_REG_PBASE)
#define UART3_REG_BASE            IO_DEVICE_ADDR(UART3_REG_PBASE)
#define UART2_REG_BASE            IO_DEVICE_ADDR(UART2_REG_PBASE)
#define UART1_REG_BASE            IO_DEVICE_ADDR(UART1_REG_PBASE)
#define UART0_REG_BASE            IO_DEVICE_ADDR(UART0_REG_PBASE)

#define MISC_REG_BASE             IO_DEVICE_ADDR(0x12030000)
#define SYS_CTRL_REG_BASE         IO_DEVICE_ADDR(0x12020000)

#define CRG_REG_ADDR              0x12010000
#define CRG_REG_BASE              IO_DEVICE_ADDR(CRG_REG_ADDR)
#define PERI_CRG30_BASE           IO_DEVICE_ADDR(CRG_REG_ADDR + 0x0078)  /* cpu freq-mode & reset CRG */

#define GSF_REG_BASE              IO_DEVICE_ADDR(0x12050000)
#define SDIO0_REG_PBASE           0x100f0000
#define SDIO1_REG_PBASE           0x10020000
#define EMMC_REG_PBASE            0x10100000
#define MMC_REG_OFFSIZE           0x118

#define ETH_REG_BASE              IO_DEVICE_ADDR(0x10010000)
#define ETH_REG_OFFSIZE           0x2000

#define VIC_REG_BASE              IO_DEVICE_ADDR(0x10040000)
#define IRQ_REG_BASE              VIC_REG_BASE

#define DMAC_REG_BASE             IO_DEVICE_ADDR(0x10060000)
#define IO_MUX_REG_BASE           IO_DEVICE_ADDR(0x12040000)
#define FMC_REG_PBASE             0x10000000
#define FMC_REG_OFFSIZE           0xdc

#define TIMER0_ENABLE             BIT(16)
#define TIMER1_ENABLE             BIT(17)
#define TIMER2_ENABLE             BIT(18)
#define TIMER3_ENABLE             BIT(19)
#define TIMER4_ENABLE             BIT(20)
#define TIMER5_ENABLE             BIT(21)
#define TIMER6_ENABLE             BIT(22)
#define TIMER7_ENABLE             BIT(23)

#define TIMER7_REG_BASE           IO_DEVICE_ADDR(0x12003020)
#define TIMER6_REG_BASE           IO_DEVICE_ADDR(0x12003000)
#define TIMER5_REG_BASE           IO_DEVICE_ADDR(0x12002020)
#define TIMER4_REG_BASE           IO_DEVICE_ADDR(0x12002000)
#define TIMER3_REG_BASE           IO_DEVICE_ADDR(0x12001020)
#define TIMER2_REG_BASE           IO_DEVICE_ADDR(0x12001000)
#define TIMER1_REG_BASE           IO_DEVICE_ADDR(0x12000020)
#define TIMER0_REG_BASE           IO_DEVICE_ADDR(0x12000000)

#define TIMER_TICK_REG_BASE       TIMER4_REG_BASE   /* timer for tick */
#define TIMER_TICK_ENABLE         TIMER4_ENABLE
#define TIMER_TIME_REG_BASE       TIMER5_REG_BASE   /* timer for time */
#define TIMER_TIME_ENABLE         TIMER5_ENABLE
#define HRTIMER_TIMER_REG_BASE    TIMER7_REG_BASE /* timer for hrtimer */
#define HRTIMER_TIMER_ENABLE      TIMER7_ENABLE

#define CACHE_ALIGNED_SIZE        64

#define ARM_REG_BASE              IO_DEVICE_ADDR(0x10300000)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
