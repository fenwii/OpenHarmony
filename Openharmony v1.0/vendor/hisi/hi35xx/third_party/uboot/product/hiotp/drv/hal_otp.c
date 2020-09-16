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

#include "hal_otp.h"
#include "drv_osal_lib.h"
#include "drv_ioctl_otp.h"

static hi_u8 *g_otp_base_vir_addr = HI_NULL;
static hi_bool g_otp_init = HI_FALSE;

#define otp_read(addr)                  readl(addr)
#define otp_write(addr, data)           writel(data, addr)
#define hal_otp_read(offset)            otp_read((volatile hi_u8 *)(g_otp_base_vir_addr + (offset)))
#define hal_otp_write(offset, data)     otp_write((volatile hi_u8 *)(g_otp_base_vir_addr + (offset)), data)

#define hal_check_init_fail_return() \
    do { \
        if (g_otp_init != HI_TRUE || g_otp_base_vir_addr == HI_NULL) { \
            hi_otp_err("device isn't init\n"); \
            return HI_ERR_OTP_NOT_INIT; \
        } \
    } while (0) \

hi_s32 hal_otp_init(hi_void)
{
    hi_u32 crg_value;
    hi_u32 *sys_addr = HI_NULL;

    if (g_otp_init == HI_TRUE) {
        return HI_SUCCESS;
    }

    /* otp clock configure */
    sys_addr = otp_ioremap_nocache(REG_SYS_OTP_CLK_ADDR_PHY, 0x100);
    hi_otp_func_fail_return(otp_ioremap_nocache, sys_addr == HI_NULL, HI_ERR_OTP_FAILED_MEM);

    crg_value = otp_read(sys_addr);
    crg_value |= OTP_CRG_CLOCK_BIT;   /* set the bit 0, clock opened */
    otp_write(sys_addr, crg_value);

    otp_iounmap(sys_addr, 0x100);

    /* otp reg addr map */
    g_otp_base_vir_addr = otp_ioremap_nocache(OTP_REG_BASE_ADDR_PHY, 0x1000);
    hi_otp_func_fail_return(otp_ioremap_nocache, g_otp_base_vir_addr == HI_NULL, HI_ERR_OTP_FAILED_MEM);

    g_otp_init = HI_TRUE;

    return HI_SUCCESS;
}

hi_void hal_otp_deinit(hi_void)
{
    if (g_otp_init == HI_FALSE) {
        return;
    }

    if (g_otp_base_vir_addr != HI_NULL) {
        otp_iounmap(g_otp_base_vir_addr, 0x1000);
        g_otp_base_vir_addr = HI_NULL;
    }
    g_otp_init = HI_FALSE;
}

hi_s32 hal_otp_read_word(hi_u32 offset, hi_u32 *value)
{
    hi_otp_check_formula_fail(value == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hal_check_init_fail_return();

    *value = hal_otp_read(offset);
    hi_otp_info(" read  offset %04X value %x\n", offset, *value);
    return HI_SUCCESS;
}

hi_s32 hal_otp_write_word(hi_u32 offset, hi_u32 value)
{
    hal_check_init_fail_return();

    hal_otp_write(offset, value);
    hi_otp_info("write offset %04X value %x\n", offset, value);
    return HI_SUCCESS;
}


