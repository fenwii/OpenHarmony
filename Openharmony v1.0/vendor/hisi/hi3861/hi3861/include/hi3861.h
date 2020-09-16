/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: HI3816
 * Author: xiyuhao
 * Create: 2019-01-30
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */

#ifndef __HI3861_H__
#define __HI3861_H__

typedef enum IRQn {
    /******  RISC-V  Privilege Interrupts ***************************************************/
    MACHINE_SOFTWARE_IRQ            = 3,
    MACHINE_TIMER_IRQ               = 7,
    MACHINE_EXTERNAL_IRQ            = 11,
    NMI_IRQ                         = 12,

    /******  HiMedeer local Interrupts ***************************************************/
    TIMER_0_IRQ                     = 26,
    TIMER_1_IRQ                     = 27,
    TIMER_2_IRQ                     = 28,
    RTC_0_IRQ                       = 29,
    RTC_1_IRQ                       = 30,
    RTC_2_IRQ                       = 31,
    RTC_3_IRQ                       = 32,
    WDT_IRQ                         = 33,
    WLAN_IRQ                        = 34,
    DMA_IRQ                         = 35,
    SFC_IRQ                         = 36,
    SDIO_IRQ                        = 37,
    UART_0_IRQ                      = 38,
    UART_1_IRQ                      = 39,
    UART_2_IRQ                      = 40,
    I2C_0_IRQ                       = 41,
    I2C_1_IRQ                       = 42,
    SSP_0_IRQ                       = 43,
    SSP_1_IRQ                       = 44,
    GPIO_IRQ                        = 45,
    TSENSOR_IRQ                     = 46,
    WLAN_SLEEP_IRQ                  = 47,
    WLAN_WAKEUPT_IRQ                = 48,
    OVER_TEMP_IRQ                   = 49,
    PMU_CMU_ERR_IRQ                 = 50,
    CPU_SOFT_0_IRQ                  = 51,
    CPU_SOFT_1_IRQ                  = 52,
    CPU_SOFT_2_IRQ                  = 53,
    CPU_SOFT_3_IRQ                  = 54,
    SSS_PKE_IRQ                     = 55,
    SSS_SYM_IRQ                     = 56,
    SSS_TRNG_IRQ                    = 57,
    ISADC_IRQ                       = 58,
    I2S_IRQ                         = 59,
    UDSLEEP_IRQ                     = 60,
    RAMMONITOR_IRQ                  = 61
} IRQn_Type;

#endif // __HI3861_H__

