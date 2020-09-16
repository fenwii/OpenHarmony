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
 * Description   : mpi rng api.
 */

#include "cipher_osal.h"

hi_s32 mpi_cipher_get_random_number(hi_u32 *random_number, hi_u32 time_out_us)
{
    hi_s32 ret;
    cipher_rng_s ci_rng;

    inlet_var_is_null_return(random_number);

    ci_rng.ci_rng = 0;
    ci_rng.time_out_us = time_out_us;

    ret = cipher_ioctl(g_cipher_dev_fd, CMD_CIPHER_GETRANDOMNUMBER, &ci_rng);

    if (ret == HI_SUCCESS)
        *random_number = ci_rng.ci_rng;

    return ret;
}

hi_s32 hi_mpi_cipher_get_random_number(hi_u32 *random_number)
{
    check_cipher_not_open_return();

    return mpi_cipher_get_random_number(random_number, 0);
}

