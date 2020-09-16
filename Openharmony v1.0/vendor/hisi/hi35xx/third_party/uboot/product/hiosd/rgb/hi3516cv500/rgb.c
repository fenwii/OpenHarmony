/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "rgb.h"
#include <common.h>

#define IO_ADDRESS(x) (x)

#define SSP_BASE 0x120c1000
#define SSP_SIZE 0x1000
#define DEFAULT_MD_LEN 128

/* SSP register definition. */
#define SSP_CR0   IO_ADDRESS(SSP_BASE + 0x00)
#define SSP_CR1   IO_ADDRESS(SSP_BASE + 0x04)
#define SSP_DR    IO_ADDRESS(SSP_BASE + 0x08)
#define SSP_SR    IO_ADDRESS(SSP_BASE + 0x0C)
#define SSP_CPSR  IO_ADDRESS(SSP_BASE + 0x10)
#define SSP_IMSC  IO_ADDRESS(SSP_BASE + 0x14)
#define SSP_RIS   IO_ADDRESS(SSP_BASE + 0x18)
#define SSP_MIS   IO_ADDRESS(SSP_BASE + 0x1C)
#define SSP_ICR   IO_ADDRESS(SSP_BASE + 0x20)
#define SSP_DMACR IO_ADDRESS(SSP_BASE + 0x24)

#define SPI_SR_BSY     (0x1 << 4) /* spi busy flag */
#define SPI_SR_TFE     (0x1 << 0) /* Whether to send fifo is empty */
#define SPI_DATA_WIDTH 9
#define SPI_SPO        1
#define SPI_SPH        1
#define SPI_SCR        8
#define SPI_CPSDVSR    8
#define SPI_FRAMEMODE  0

#define MAX_WAIT 10000

#define ssp_readw(addr, ret)    ((ret) = (*(volatile unsigned int *)(addr)))
#define ssp_writew(addr, value) ((*(volatile unsigned int *)(addr)) = (value))

#if CONFIG_RGB_INTFACE
static int hi_spi_check_timeout(void)
{
    unsigned int value = 0;
    unsigned int tmp = 0;
    while (1) {
        ssp_readw(SSP_SR, value);
        if ((value & SPI_SR_TFE) && (!(value & SPI_SR_BSY))) {
            break;
        }

        if (tmp++ > MAX_WAIT) {
            printf("spi transfer wait timeout!\n");
            return -1;
        }
        udelay(1);
    }
    return 0;
}
#endif

static void hi_ssp_write_only(int is_write_only)
{
    unsigned int ret = 0;

    ssp_readw(SSP_CR1, ret);

    ret = ret & (~(0x1 << 5)); /* bit5 */

    ssp_writew(SSP_CR1, ret);
}

static void hi_ssp_enable(void)
{
    unsigned int ret = 0;
    ssp_readw(SSP_CR1, ret);
    ret = (ret & 0xFFFD) | 0x2;

    ret = ret | (0x1 << 4); /* 4 big/little end, 1: little, 0: big */

    ret = ret | (0x1 << 15); /* 15 wait en */

    ssp_writew(SSP_CR1, ret);

    hi_ssp_write_only(0);
}

static void hi_ssp_disable(void)
{
    unsigned int ret = 0;
    ssp_readw(SSP_CR1, ret);
    ret = ret & (~(0x1 << 1));
    ssp_writew(SSP_CR1, ret);
}

static int hi_ssp_set_frameform(unsigned char framemode, unsigned char spo, unsigned char sph,
                                unsigned char datawidth)
{
    unsigned int ret = 0;
    ssp_readw(SSP_CR0, ret);
    if (framemode > 3) { /* 3 frame mode */
        printf("set frame parameter err.\n");
        return -1;
    }
    ret = (ret & 0xFFCF) | (framemode << 4); /* 4 set frame mode */
    if ((ret & 0x30) == 0) {
        if (spo > 1) {
            printf("set spo parameter err.\n");
            return -1;
        }
        if (sph > 1) {
            printf("set sph parameter err.\n");
            return -1;
        }
        ret = (ret & 0xFF3F) | (sph << 7) | (spo << 6); /* 7 6 to  set */
    }
    if ((datawidth > 16) || (datawidth < 4)) { /* data width should be 4 - 16 */
        printf("set datawidth parameter err.\n");
        return -1;
    }
    ret = (ret & 0xFFF0) | (datawidth - 1);
    ssp_writew(SSP_CR0, ret);
    return 0;
}

static int hi_ssp_set_serialclock(unsigned char scr, unsigned char cpsdvsr)
{
    unsigned int ret = 0;
    ssp_readw(SSP_CR0, ret);
    ret = (ret & 0xFF) | (scr << 8); /* 8 to set clk */
    ssp_writew(SSP_CR0, ret);
    if ((cpsdvsr & 0x1)) {
        printf("set cpsdvsr parameter err.\n");
        return -1;
    }
    ssp_writew(SSP_CPSR, cpsdvsr);
    return 0;
}

static int hi_ssp_alt_mode_set(int enable)
{
    unsigned int ret = 0;

    ssp_readw(SSP_CR1, ret);
    if (enable) {
        ret = ret & (~0x40);
    } else {
        ret = (ret & 0xFF) | 0x40;
    }
    ssp_writew(SSP_CR1, ret);

    return 0;
}

#if CONFIG_RGB_INTFACE
static void spi_enable(void)
{
    ssp_writew(SSP_CR1, 0x42);
}
#endif

static void spi_disable(void)
{
    ssp_writew(SSP_CR1, 0x40);
}

#if CONFIG_RGB_INTFACE
static void spi_write_a8byte(unsigned char dat)
{
    unsigned short spi_data;

    spi_data = (unsigned short)dat;

    spi_enable();
    ssp_writew(SSP_DR, spi_data);
    printf("spi_data:0x%x\n", spi_data);
    udelay(10000); /* delay 10000 us */
    spi_disable();
}

static void spi_write_a9byte(unsigned char cmd_dat, unsigned char dat)
{
    unsigned short spi_data;
    int ret;
    if (cmd_dat) {
        spi_data = 1 << 8; /* 8 data */
    } else {
        spi_data = 0 << 8; /* 8 data */
    }

    spi_data = spi_data | dat;
    spi_enable();
    ssp_writew(SSP_DR, spi_data);
    ret = hi_spi_check_timeout();
    if (ret != 0) {
        printf("spi_send timeout\n");
    }
    spi_disable();
}

static void spi_write_a16byte(unsigned short spi_data)
{
    spi_enable();
    ssp_writew(SSP_DR, spi_data);
    printf("spi_data:0x%x\n", spi_data);
    udelay(10000); /* delay 10000 us */
    spi_disable();
}

static void ssp_write_dat(unsigned char dat)
{
    spi_write_a9byte(1, dat);
}

static void ssp_write_cmd(unsigned char dat)
{
    spi_write_a9byte(0, dat);
}
#endif

static void ssp_set(void)
{
    spi_disable();
    hi_ssp_set_frameform(SPI_FRAMEMODE, SPI_SPO, SPI_SPH, SPI_DATA_WIDTH);
    hi_ssp_set_serialclock(SPI_SCR, SPI_CPSDVSR);
    hi_ssp_alt_mode_set(1);
    hi_ssp_enable();
}

static void rgb_reset(void)
{
}

static void rgb_init_vertical(void)
{
    return;
}

static void rgb_init_display(void)
{
    /* spi_9bit_setting */
    ssp_set();

    rgb_reset();

    rgb_init_vertical();

    return;
}

static void rgb_setbacklight(void)
{
}
void spi_config(void)
{
}

void spi_pinmux(void)
{
}

void vo_rgb_pinmux(void)
{
}

void rgb_display(void)
{
    spi_config();

    spi_pinmux();

    vo_rgb_pinmux();

    rgb_init_display();

    rgb_setbacklight();

    return;
}

void rgb_stop(void)
{
    hi_ssp_disable();

    return;
}

