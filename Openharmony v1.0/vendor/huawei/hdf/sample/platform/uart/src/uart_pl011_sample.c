/* Copyright 2020 Huawei Device Co., Ltd.
 *
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

#include "uart_pl011_sample.h"

void UartPl011SetLcrBits(struct UartRegisterMap *regMap, uint32_t bits)
{
    bool uartEnabled = UartPl011IsEnabled(regMap);
    /* UART must be disabled before UARTLCR_H are reprogrammed */
    UartPl011Disable(regMap);
    regMap->lcr |= (bits);
    /* Restore uart enable state */
    if (uartEnabled) {
        UartPl011Enable(regMap);
    }
}

void UartPl011UpdateLcr(struct UartRegisterMap *regMap)
{
    bool uartEnabled = UartPl011IsEnabled(regMap);
    /* UART must be disabled before UARTLCR_H are reprogrammed */
    UartPl011Disable(regMap);
    regMap->lcr = regMap->lcr;
    /* restore uart enable state */
    if (uartEnabled) {
        UartPl011Enable(regMap);
    }
}

UartPl011Error UartPl011SetBaudrate(struct UartRegisterMap *regMap, uint32_t clk, uint32_t baudrate)
{
    if (baudrate == 0) {
        return UART_PL011_ERR_INVALID_ARG;
    }

    uint32_t value = SAMPLING_FACTOR * baudrate;
    uint32_t divider = clk / value;
    uint32_t remainder = clk % value;
    uint32_t fraction;
    value = (SAMPLING_FACTOR * remainder) / baudrate;
    fraction = (value >> 1) + (value & 1);

    regMap->ibrd = divider;
    regMap->fbrd = fraction;
    /* to internally update the contents of UARTIBRD or
     * UARTFBRD, a UARTLCR_H write must always be performed at the end.
     */
    UartPl011UpdateLcr(regMap);
    return UART_PL011_ERR_NONE;
}

void UartPl011SetDataFormat(
    struct UartRegisterMap *regMap, uint32_t wordLen, uint32_t parity, uint32_t stopBits)
{
    bool uartEnabled = UartPl011IsEnabled(regMap);
    uint32_t lcr = regMap->lcr & (~UART_PL011_DATA_FORMAT_MASK);
    lcr |= wordLen & UART_PL011_LCR_H_WLEN_MASK;
    lcr |= parity & UART_PL011_LCR_H_PARITY_MASK;
    lcr |= stopBits & UART_PL011_LCR_H_STOPBIT_MASK;
    /* UART must be disabled before UARTLCR_H are reprogrammed */
    UartPl011Disable(regMap);
    regMap->lcr = lcr;
    if (uartEnabled) {
        UartPl011Enable(regMap);
    }
}

void UartPl011ResetRegisters(struct UartRegisterMap *regMap)
{
    regMap->cr = UART_PL011_DEFAULT_CTRL_REG_VALUE;
    regMap->dr = UART_PL011_DEFAULT_DATA_REG_VALUE;
    /* Clear all the errors */
    regMap->ecr = UART_PL011_DEFAULT_ECR_VALUE;
    regMap->ilpr = UART_PL011_DEFAULT_ILPR_VALUE;
    regMap->ibrd = UART_PL011_DEFAULT_IBRD_REG_VALUE;
    regMap->fbrd = UART_PL011_DEFAULT_FBRD_REG_VALUE;
    regMap->lcr = UART_PL011_DEFAULT_LCR_H_VALUE;
    regMap->ifls = UART_PL011_DEFAULT_IFLS_REG_VALUE;
    /* Clear all interrupt mask */
    regMap->imsc = UART_PL011_DEFAULT_IMSC_REG_VALUE;
    /* Clear all interrupts */
    regMap->icr = UART_PL011_DEFAULT_ICR_VALUE;
    regMap->dmacr = UART_PL011_DEFAULT_DMACR_VALUE;
}

