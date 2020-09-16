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

#ifndef PLATFORM_HAL_PLATFORM_INTS_H
#define PLATFORM_HAL_PLATFORM_INTS_H

#include"los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * Maximum number of supported hardware devices that generate hardware interrupts.
 * The maximum number of hardware devices that generate hardware interrupts is 128.
 */
#define OS_HWI_MAX_NUM                  128

/**
 * Maximum interrupt number.
 */

#define OS_HWI_MAX                      ((OS_HWI_MAX_NUM) - 1)

/**
 * Minimum interrupt number.
 */

#define OS_HWI_MIN                      0

/**
 * Maximum usable interrupt number.
 */

#define OS_USER_HWI_MAX                 OS_HWI_MAX

/**
 * Minimum usable interrupt number.
 */

#define OS_USER_HWI_MIN                 OS_HWI_MIN

#define NUM_HAL_INTERRUPT_CNTPSIRQ      29
#define NUM_HAL_INTERRUPT_CNTPNSIRQ     30
#ifdef LOSCFG_TEE_ENABLE
#define OS_TICK_INT_NUM                 NUM_HAL_INTERRUPT_CNTPNSIRQ // use non-secure physical timer for now
#else
#define OS_TICK_INT_NUM                 NUM_HAL_INTERRUPT_CNTPSIRQ // use secure physical timer for now
#endif

#define NUM_HAL_INTERRUPT_TIMER0        33
#define NUM_HAL_INTERRUPT_TIMER1        33
#define NUM_HAL_INTERRUPT_TIMER2        34
#define NUM_HAL_INTERRUPT_TIMER3        34
#define NUM_HAL_INTERRUPT_TIMER4        35
#define NUM_HAL_INTERRUPT_TIMER5        35
#define NUM_HAL_INTERRUPT_TIMER6        36
#define NUM_HAL_INTERRUPT_TIMER7        36

#define NUM_HAL_INTERRUPT_DMAC          60
#define NUM_HAL_INTERRUPT_UART0         38
#define NUM_HAL_INTERRUPT_UART1         39
#define NUM_HAL_INTERRUPT_UART2         40
#define NUM_HAL_INTERRUPT_UART3         41
#define NUM_HAL_INTERRUPT_UART4         42

#define NUM_HAL_INTERRUPT_SDIO          62
#define NUM_HAL_INTERRUPT_SDIO1         63
#define NUM_HAL_INTERRUPT_EMMC          96
#define NUM_HAL_INTERRUPT_ETH           64

#define NUM_HAL_INTERRUPT_TIMER         NUM_HAL_INTERRUPT_TIMER4
#define NUM_HAL_INTERRUPT_HRTIMER       NUM_HAL_INTERRUPT_TIMER7

#define NUM_HAL_INTERRUPT_GPIO0         48
#define NUM_HAL_INTERRUPT_GPIO1         49
#define NUM_HAL_INTERRUPT_GPIO2         50
#define NUM_HAL_INTERRUPT_GPIO3         51
#define NUM_HAL_INTERRUPT_GPIO4         52
#define NUM_HAL_INTERRUPT_GPIO5         53
#define NUM_HAL_INTERRUPT_GPIO6         54
#define NUM_HAL_INTERRUPT_GPIO7         55
#define NUM_HAL_INTERRUPT_GPIO8         56
#define NUM_HAL_INTERRUPT_GPIO9         57
#define NUM_HAL_INTERRUPT_GPIO10        58
#define NUM_HAL_INTERRUPT_USB_XHCI      59
#define NUM_HAL_INTERRUPT_GPIO11        112

#define NUM_HAL_INTERRUPT_TEE_SPI_NOTIFY 105

#define NUM_HAL_INTERRUPT_NONE          -1

#define NUM_HAL_ISR_MIN                 OS_HWI_MIN
#define NUM_HAL_INTERRUPT_USB_DEV       NUM_HAL_INTERRUPT_USB_XHCI

#define IO_ADDRESS(x)       (x)

#define HAL_READ_UINT8(addr, data)  READ_UINT8(data, addr)

#define HAL_WRITE_UINT8(addr, data) WRITE_UINT8(data, addr)

#define HAL_READ_UINT32(addr, data) READ_UINT32(data, addr)

#define HAL_WRITE_UINT32(addr, data) WRITE_UINT32(data, addr)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif // PLATFORM_HAL_PLATFORM_INTS_H
