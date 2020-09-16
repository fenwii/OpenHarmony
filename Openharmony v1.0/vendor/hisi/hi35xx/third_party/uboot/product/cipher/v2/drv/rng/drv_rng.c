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
 * Description   : drivers for rng
 */

#include "cipher_adapt.h"

static hi_void *g_rng_reg_base;

#define REG_RNG_BASE_ADDR                   g_rng_reg_base
#define HISEC_COM_TRNG_CTRL                 (REG_RNG_BASE_ADDR + 0x200)
#define HISEC_COM_TRNG_FIFO_DATA            (REG_RNG_BASE_ADDR + 0x204)
#define HISEC_COM_TRNG_DATA_ST              (REG_RNG_BASE_ADDR + 0x208)

hi_s32 drv_rng_init(hi_void)
{
    hi_u32 rng_stat = 0;

    g_rng_reg_base = cipher_ioremap_nocache(CIPHER_RNG_REG_BASE_ADDR_PHY, 0x1000);
    if (g_rng_reg_base == HI_NULL) {
        hi_err_cipher("ioremap_nocache sha2 Reg failed\n");
        return HI_FAILURE;
    }

    hal_cipher_read_reg(CIPHER_RNG_CRG_ADDR_PHY, &rng_stat);
    rng_stat |= RNG_CRG_CLOCK_BIT;
    rng_stat &= ~RNG_CRG_RESET_BIT;
    hal_cipher_write_reg(CIPHER_RNG_CRG_ADDR_PHY, rng_stat);

    return HI_SUCCESS;
}

hi_void drv_rng_deinit(hi_void)
{
    cipher_iounmap(g_rng_reg_base);
}

static hi_s32 drv_cipher_get_random_number(cipher_rng_s *rng)
{
    hi_u32 rng_stat = 0;
    hi_u32 time_out = 0;

    if (rng->time_out_us == 0) {
        /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
        hal_cipher_read_reg(HISEC_COM_TRNG_DATA_ST, &rng_stat);
        if (((rng_stat >> 8) & 0x3F) <= 0) /* 8 right shift */
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
    } else {
        while (time_out++ < rng->time_out_us) {
            /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
            hal_cipher_read_reg(HISEC_COM_TRNG_DATA_ST, &rng_stat);
            if (((rng_stat >> 8) & 0x3F) > 0) /* 8 right shift */
                break;
        }

        if (time_out >= rng->time_out_us)
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
    }

    hal_cipher_read_reg(HISEC_COM_TRNG_FIFO_DATA, &rng->ci_rng);

    return HI_SUCCESS;
}

hi_u32 drv_cipher_rand(hi_void)
{
    cipher_rng_s rng;

    rng.time_out_us = -1;
    if (drv_cipher_get_random_number(&rng) != HI_SUCCESS)
        hi_err_cipher("Get random number failed!\n");

    return rng.ci_rng;
}

hi_s32 hi_drv_cipher_get_random_number(cipher_rng_s *rng)
{
    hi_s32 ret;

    if (rng == NULL) {
        hi_err_cipher("Invalid params!\n");
        return HI_FAILURE;
    }

    ret = drv_cipher_get_random_number(rng);

    return ret;
}

