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

#ifndef UART_PL011_SAMPLE_H
#define UART_PL011_SAMPLE_H

#include <stdint.h>
#include <stdbool.h>
#include "hdf_device_desc.h"
#include "buf_fifo.h"

#ifdef __cplusplus
extern "C" {
#endif

struct UartRegisterMap {
    volatile uint32_t dr;            /* Offset: 0x000 TYPE: (RW) Data register */
    union {
        volatile uint32_t rsr;       /* Offset: 0x004 TYPE: (RO) Receive status register */
        volatile uint32_t ecr;       /* Offset: 0x004 TYPE: (WO) Error clear register */
    };
    volatile uint32_t reserved0[4];  /* Offset: 0x008-0x014 Reserved */
    volatile uint32_t fr;            /* Offset: 0x018 TYPE: (RO) Flag register */
    volatile uint32_t reserved1;     /* Offset: 0x01C Reserved */
    volatile uint32_t ilpr;          /* Offset: 0x020 TYPE: (RW) IrDA low-power counter register */
    volatile uint32_t ibrd;          /* Offset: 0x024 TYPE: (RW) Integer baud rate register */
    volatile uint32_t fbrd;          /* Offset: 0x028 TYPE: (RW) Fractional baud rate register */
    volatile uint32_t lcr;           /* Offset: 0x02C TYPE: (RW) Line control register */
    volatile uint32_t cr;            /* Offset: 0x030 TYPE: (RW) Control register */
    volatile uint32_t ifls;          /* Offset: 0x034 TYPE: (RW) Interrupt FIFO level select register */
    volatile uint32_t imsc;          /* Offset: 0x038 TYPE: (RW) Interrupt mask set/clear register */
    volatile uint32_t ris;           /* Offset: 0x03C TYPE: (RO) Raw interrupt status register */
    volatile uint32_t mis;           /* Offset: 0x040 TYPE: (RO) Masked interrupt status register */
    volatile uint32_t icr;           /* Offset: 0x044 TYPE: (WO) Interrupt clear register */
    volatile uint32_t dmacr;         /* Offset: 0x048 TYPE: (RW) DMA control register */
};

struct UartResource {
    uint32_t num;        /* UART port num */
    uint32_t base;       /* UART PL011 base address */
    uint32_t irqNum;     /* UART PL011 IRQ num */
    uint32_t baudrate;   /* Default baudrate */
    uint32_t wlen;       /* Default word length */
    uint32_t parity;     /* Default parity */
    uint32_t stopBit;    /* Default stop bits */
    uint32_t uartClk;    /* UART clock */
    unsigned long physBase;
};

enum UartDeviceState {
    UART_DEVICE_UNINITIALIZED = 0x0u,
    UART_DEVICE_INITIALIZED = 0x1u,
};

struct UartDevice {
    struct IDeviceIoService ioService;
    struct UartResource resource;
    enum UartDeviceState state;     /* UART State */
    uint32_t uartClk;               /* UART clock */
    uint32_t baudrate;              /* Baudrate */
    struct BufferFifo rxFifo;
};

/* Receive Status Register/Error Clear Register data */
#define UART_PL011_RSR_FRAMING_ERROR_MASK     (1 << 0x0u)  /* Framing error bit mask */
#define UART_PL011_RSR_PARITY_ERROR_MASK      (1 << 0x1u)  /* Parity error bit mask */
#define UART_PL011_RSR_BREAK_ERROR_MASK       (1 << 0x2u)  /* Break error bit mask */
#define UART_PL011_RSR_OVERRUN_ERROR_MASK     (1 << 0x3u)  /* Overrun error bit mask */

/* Receive Status Register Error Mask */
#define UART_PL011_RSR_RX_ERROR_MASK (         \
            UART_PL011_RSR_FRAMING_ERROR_MASK  \
          | UART_PL011_RSR_PARITY_ERROR_MASK   \
          | UART_PL011_RSR_BREAK_ERROR_MASK    \
          | UART_PL011_RSR_OVERRUN_ERROR_MASK)

#define UART_PL011_FR_CTS_MASK                (1 << 0x0u)  /* Clear to send bit mask */
#define UART_PL011_FR_DSR_MASK                (1 << 0x1u)  /* Data set ready bit mask */
#define UART_PL011_FR_DCD_MASK                (1 << 0x2u)  /* Data carrier detect bit mask */
#define UART_PL011_FR_BUSY_MASK               (1 << 0x3u)  /* UART busy bit mask */
#define UART_PL011_FR_RX_FIFO_EMPTY_MASK      (1 << 0x4u)  /* Receive FIFO empty bit mask */
#define UART_PL011_FR_TX_FIFO_FULL_MASK       (1 << 0x5u)  /* Transmit FIFO full bit mask */
#define UART_PL011_FR_RX_FIFO_FULL_MASK       (1 << 0x6u)  /* Receive FIFO full bit mask */
#define UART_PL011_FR_TX_FIFO_EMPTY_MASK      (1 << 0x7u)  /* Transmit FIFO empty. bit mask */
#define UART_PL011_FR_RI_MASK                 (1 << 0x8u)  /* Ring indicator  bit mask */

/* PL011 Line Control Register Data bits */
#define UART_PL011_LCR_H_BRK_MASK             (1 << 0x0u)  /* Send Break bit mask */
#define UART_PL011_LCR_H_PEN_MASK             (1 << 0x1u)  /* Parity enable bit mask */
#define UART_PL011_LCR_H_EPS_MASK             (1 << 0x2u)  /* Even parity select bit mask . */
#define UART_PL011_LCR_H_FEN_MASK             (1 << 0x4u)  /* Enable FIFOs bit mask */
#define UART_PL011_LCR_H_SPS_MASK             (1 << 0x7u)  /* Stick parity select bit mask */

#define UART_PL011_LCR_H_WLEN_BIT_OFFSET      0x5u  /* Word length  bit offset */
#define UART_PL011_LCR_H_WLEN_MASK (  \
            0x3u << UART_PL011_LCR_H_WLEN_BIT_OFFSET)

#define UART_PL011_WLEN_5BITS                 (0x0u << UART_PL011_LCR_H_WLEN_BIT_OFFSET)
#define UART_PL011_WLEN_6BITS                 (0x1u << UART_PL011_LCR_H_WLEN_BIT_OFFSET)
#define UART_PL011_WLEN_7BITS                 (0x2u << UART_PL011_LCR_H_WLEN_BIT_OFFSET)
#define UART_PL011_WLEN_8BITS                 (0x3u << UART_PL011_LCR_H_WLEN_BIT_OFFSET)

#define UART_PL011_NONE_PARITY_CHECKED  0

#define UART_PL011_LCR_H_STP2_BIT_OFFSET        0x3u  /* Two stop bits select */

#define UART_PL011_STOPBIT_1                  (0x0u << UART_PL011_LCR_H_STP2_BIT_OFFSET)
#define UART_PL011_STOPBIT_2                  (0x1u << UART_PL011_LCR_H_STP2_BIT_OFFSET)

#define UART_PL011_LCR_H_PARITY_MASK (         \
              UART_PL011_LCR_H_PEN_MASK        \
            | UART_PL011_LCR_H_EPS_MASK        \
            | UART_PL011_LCR_H_SPS_MASK)

#define UART_PL011_LCR_H_STOPBIT_MASK          \
              (0x1u << UART_PL011_LCR_H_STP2_BIT_OFFSET)

#define UART_PL011_DATA_FORMAT_MASK (          \
              UART_PL011_LCR_H_PARITY_MASK     \
            | UART_PL011_LCR_H_STOPBIT_MASK    \
            | UART_PL011_LCR_H_WLEN_MASK)

/* Control Register */
#define UART_PL011_CR_UARTEN_MASK           (0x1u << 0x0u)  /* Uart enable bit mask */
#define UART_PL011_CR_SIREN_MASK            (0x1u << 0x1u)  /* Sir enable bit mask */
#define UART_PL011_CR_SIRLP_MASK            (0x1u << 0x2u)  /* SIR low-power IrDA mode bit mask */
#define UART_PL011_CR_LBE_MASK              (0x1u << 0x7u)  /* Loopback enable bit mask */
#define UART_PL011_CR_TXE_MASK              (0x1u << 0x8u)  /* Transmit enable bit mask */
#define UART_PL011_CR_RXE_MASK              (0x1u << 0x9u)  /* Receive enable bit mask */
#define UART_PL011_CR_DTR_MASK              (0x1u << 0xAu)  /* Data transmit ready.bit mask */
#define UART_PL011_CR_RTS_MASK              (0x1u << 0xBu)  /* Request to send bit mask */
#define UART_PL011_CR_OUT1_MASK             (0x1u << 0xCu)  /* Out1 bit field mask */
#define UART_PL011_CR_OUT2_MASK             (0x1u << 0xDu)  /* Out2 bit field mask */
#define UART_PL011_CR_RTSE_MASK             (0x1u << 0xEu)  /* RTS hardware flow control enable bit mask */
#define UART_PL011_CR_CTSE_MASK             (0x1u << 0xFu)  /* CTS hardware flow control enable bit mask */


/* Interrupt FIFO Level Select Register Transmit bit offset */
#define UART_PL011_IFLS_TX_BIT_OFFSET           0x0u
/* Interrupt FIFO Level Select Register Receive bit offset */
#define UART_PL011_IFLS_RX_BIT_OFFSET           0x3u

#define UART_PL011_RX_FIFO_LVL_1_8          (0x0u << UART_PL011_IFLS_RX_BIT_OFFSET)
#define UART_PL011_RX_FIFO_LVL_1_4          (0x1u << UART_PL011_IFLS_RX_BIT_OFFSET)
#define UART_PL011_RX_FIFO_LVL_1_2          (0x2u << UART_PL011_IFLS_RX_BIT_OFFSET)
#define UART_PL011_RX_FIFO_LVL_3_4          (0x3u << UART_PL011_IFLS_RX_BIT_OFFSET)
#define UART_PL011_RX_FIFO_LVL_7_8          (0x4u << UART_PL011_IFLS_RX_BIT_OFFSET)

#define UART_PL011_TX_FIFO_LVL_1_8          (0x0u << UART_PL011_IFLS_TX_BIT_OFFSET)
#define UART_PL011_TX_FIFO_LVL_1_4          (0x1u << UART_PL011_IFLS_TX_BIT_OFFSET)
#define UART_PL011_TX_FIFO_LVL_1_2          (0x2u << UART_PL011_IFLS_TX_BIT_OFFSET)
#define UART_PL011_TX_FIFO_LVL_3_4          (0x3u << UART_PL011_IFLS_TX_BIT_OFFSET)
#define UART_PL011_TX_FIFO_LVL_7_8          (0x4u << UART_PL011_IFLS_TX_BIT_OFFSET)

/* Default register values of UART PL011 */
#define UART_PL011_DEFAULT_DATA_REG_VALUE     (0x0u)
#define UART_PL011_DEFAULT_ECR_VALUE          (0xFFu)
#define UART_PL011_DEFAULT_ILPR_VALUE         (0x0u)
#define UART_PL011_DEFAULT_IBRD_REG_VALUE     (0x0u)
#define UART_PL011_DEFAULT_FBRD_REG_VALUE     (0x0u)
/* Clear UARTLCR */
#define UART_PL011_DEFAULT_LCR_H_VALUE        (0x0u)
#define UART_PL011_DEFAULT_CTRL_REG_VALUE     (0x0300u)

#define UART_PL011_DEFAULT_IFLS_REG_VALUE (              \
            UART_PL011_RX_FIFO_LVL_1_2                   \
            | UART_PL011_TX_FIFO_LVL_7_8)

/* Clear interrupt mask */
#define UART_PL011_DEFAULT_IMSC_REG_VALUE     (0x0u)
/* Clear interrupt */
#define UART_PL011_DEFAULT_ICR_VALUE          (0x7FFu)
#define UART_PL011_DEFAULT_DMACR_VALUE        (0x0u)

#define FREQ_IRLPBAUD16_MIN                   (1420000u)     /* 1.42 MHz */
#define FREQ_IRLPBAUD16_MAX                   (2120000u)     /* 2.12 MHz */
#define SAMPLING_FACTOR                       (16u)
#define UART_PL011_FBRD_WIDTH                 (6u)

/**
 * \brief ARM UART PL011 error enumeration types
 */
typedef enum UartPl011Error {
    UART_PL011_ERR_NONE = (0x0u),
    UART_PL011_ERR_RX_FRAME = UART_PL011_RSR_FRAMING_ERROR_MASK,
    UART_PL011_ERR_RX_PARITY = UART_PL011_RSR_PARITY_ERROR_MASK,
    UART_PL011_ERR_RX_BREAK = UART_PL011_RSR_BREAK_ERROR_MASK,
    UART_PL011_ERR_RX_OVERFLOW = UART_PL011_RSR_OVERRUN_ERROR_MASK,
    UART_PL011_ERR_INVALID_ARG = (UART_PL011_RSR_RX_ERROR_MASK + 1),
    UART_PL011_ERR_NOT_READY,
    UART_PL011_ERR_INVALID_BAUD,
    UART_PL011_ERR_NOT_INIT,
} UartPl011Error;

static inline void UartPl011Enable(struct UartRegisterMap *regMap)
{
    regMap->cr |= UART_PL011_CR_UARTEN_MASK;
}

static inline void UartPl011Disable(struct UartRegisterMap *regMap)
{
    regMap->cr &= ~UART_PL011_CR_UARTEN_MASK;
}

static inline bool UartPl011IsEnabled(struct UartRegisterMap *regMap)
{
    return (bool)(regMap->cr & UART_PL011_CR_UARTEN_MASK);
}

static inline bool UartPl011IsBusy(struct UartRegisterMap *regMap)
{
    return (bool)(regMap->fr & UART_PL011_FR_BUSY_MASK);
}

void UartPl011SetLcrBits(struct UartRegisterMap *regMap, uint32_t bits);

static inline void UartPl011Write(struct UartRegisterMap *regMap, uint8_t byte)
{
    while (UartPl011IsBusy(regMap));
    regMap->dr = byte;
}

UartPl011Error UartPl011SetBaudrate(struct UartRegisterMap *regMap, uint32_t clk, uint32_t baudrate);

void UartPl011SetDataFormat(struct UartRegisterMap *regMap, uint32_t wordLen, uint32_t parity, uint32_t stopBits);

void UartPl011ResetRegisters(struct UartRegisterMap *regMap);

static inline void UartPl011EnableFifo(struct UartRegisterMap *regMap)
{
    UartPl011SetLcrBits(regMap, UART_PL011_LCR_H_FEN_MASK);
}

#ifdef __cplusplus
}
#endif
#endif /* UART_PL011_SAMPLE_H */

