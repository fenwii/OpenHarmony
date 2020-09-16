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
 * Description   : head file for cipher config
 */

#ifndef __CIPHER_CONFIG_H_
#define __CIPHER_CONFIG_H_

#define RSA_ENABLE
#define OTP_SUPPORT
#define CIPHER_HASH_SUPPORT
#define CIPHER_EFUSE_SUPPORT
#define CIPHER_KLAD_SUPPORT

#define CIPHER_IRQ_NUMBER                       59

#if defined(CONFIG_TARGET_HI3559AV100)
#define CIPHER_RNG_REG_BASE_ADDR_PHY            0x10230000
#define CIPHER_ENFUSE_REG_BASE_ADDR_PHY         (0x10250000)
#define CIPHER_CIPHER_REG_BASE_ADDR_PHY         (0x10200000)
#define CIPHER_RSA_REG_BASE_ADDR_PHY            (0x10220000)

#define CIPHER_RSA_CRG_ADDR_PHY                 (0x12010194)
#define RSA_CRG_CLOCK_BIT                       (0x01 << 15)
#define RSA_CRG_RESET_BIT                       (0x01 << 14)
#define CIPHER_SPACC_CRG_ADDR_PHY               (0x1201016C)
#define SPACC_CRG_CLOCK_BIT                     (0x01 << 1)
#define SPACC_CRG_RESET_BIT                     (0x01 << 0)
#define CIPHER_RNG_CRG_ADDR_PHY                 (0x12010194)
#define RNG_CRG_CLOCK_BIT                       (0x01 << 13)
#define RNG_CRG_RESET_BIT                       (0x01 << 12)

#define CIPHER_KLAD_REG_BASE_ADDR_PHY           (0x10210000)
#define CIPHER_OTP_REG_BASE_ADDR_PHY            (0x10240000)
#define CIPHER_KLAD_CRG_ADDR_PHY                (0x12010194)

#define KLAD_CRG_CLOCK_BIT                      (0x01 << 11)
#define KLAD_CRG_RESET_BIT                      (0x01 << 10)
#elif (defined(CONFIG_TARGET_HI3519AV100) || defined(CONFIG_TARGET_HI3556AV100))
#define CIPHER_RNG_REG_BASE_ADDR_PHY            (0x04090000)
#define CIPHER_CIPHER_REG_BASE_ADDR_PHY         (0x04060000)
#define CIPHER_RSA_REG_BASE_ADDR_PHY            (0x04088000)

#define CIPHER_RSA_CRG_ADDR_PHY                 (0x04510194)
#define RSA_CRG_CLOCK_BIT                       (0x01 << 23)
#define RSA_CRG_RESET_BIT                       (0x01 << 22)
#define CIPHER_SPACC_CRG_ADDR_PHY               (0x0451016c)
#define SPACC_CRG_CLOCK_BIT                     (0x01 << 1)
#define SPACC_CRG_RESET_BIT                     (0x01 << 0)
#define CIPHER_RNG_CRG_ADDR_PHY                 (0x04510194)
#define RNG_CRG_CLOCK_BIT                       (0x01 << 13)
#define RNG_CRG_RESET_BIT                       (0x01 << 12)

#define CIPHER_KLAD_REG_BASE_ADDR_PHY           (0x04070000)
#define CIPHER_OTP_REG_BASE_ADDR_PHY            (0x040A0000)
#define CIPHER_KLAD_CRG_ADDR_PHY                (0x04510194)

#define KLAD_CRG_CLOCK_BIT                      (0x01 << 11)
#define KLAD_CRG_RESET_BIT                      (0x01 << 10)
#elif (defined(CONFIG_TARGET_HI3516DV300) || defined(CONFIG_TARGET_HI3516CV500) || \
       defined(CONFIG_TARGET_HI3516AV300) || defined(CONFIG_TARGET_HI3556V200)  || \
       defined(CONFIG_TARGET_HI3559V200))
#define CIPHER_RNG_REG_BASE_ADDR_PHY            (0x10090000)
#define CIPHER_CIPHER_REG_BASE_ADDR_PHY         (0x100C0000)
#define CIPHER_RSA_REG_BASE_ADDR_PHY            (0x100D0000)

#define CIPHER_RSA_CRG_ADDR_PHY                 (0x120101A0)
#define RSA_CRG_CLOCK_BIT                       (0x01 << 7)
#define RSA_CRG_RESET_BIT                       (0x01 << 6)
#define CIPHER_SPACC_CRG_ADDR_PHY               (0x120101A0)
#define SPACC_CRG_CLOCK_BIT                     (0x01 << 9)
#define SPACC_CRG_RESET_BIT                     (0x01 << 8)
#define CIPHER_RNG_CRG_ADDR_PHY                 (0x120101A0)
#define RNG_CRG_CLOCK_BIT                       (0x01 << 3)
#define RNG_CRG_RESET_BIT                       (0x01 << 2)

#define CIPHER_KLAD_REG_BASE_ADDR_PHY           (0x10070000)
#define CIPHER_OTP_REG_BASE_ADDR_PHY            (0x100B0000)
#define CIPHER_KLAD_CRG_ADDR_PHY                (0x120101A0)

#define KLAD_CRG_CLOCK_BIT                      (0x01 << 1)
#define KLAD_CRG_RESET_BIT                      (0x01 << 0)
#elif (defined(CONFIG_TARGET_HI3516EV200) || defined(CONFIG_TARGET_HI3516EV300) || \
       defined(CONFIG_TARGET_HI3518EV300) || defined(CONFIG_TARGET_HI3516DV200))
#define CIPHER_RNG_REG_BASE_ADDR_PHY            (0x10080000)
#define CIPHER_CIPHER_REG_BASE_ADDR_PHY         (0x10050000)
#define CIPHER_RSA_REG_BASE_ADDR_PHY            (0x10070000)

#define CIPHER_RSA_CRG_ADDR_PHY                 (0x120101A0)
#define RSA_CRG_CLOCK_BIT                       (0x01 << 5)
#define RSA_CRG_RESET_BIT                       (0x01 << 4)
#define CIPHER_SPACC_CRG_ADDR_PHY               (0x120101A0)
#define SPACC_CRG_CLOCK_BIT                     (0x01 << 9)
#define SPACC_CRG_RESET_BIT                     (0x01 << 8)
#define CIPHER_RNG_CRG_ADDR_PHY                 (0x120101A0)
#define RNG_CRG_CLOCK_BIT                       (0x01 << 3)
#define RNG_CRG_RESET_BIT                       (0x01 << 2)

#define CIPHER_KLAD_REG_BASE_ADDR_PHY           (0x10060000)
#define CIPHER_OTP_REG_BASE_ADDR_PHY            (0x10090000)
#define CIPHER_KLAD_CRG_ADDR_PHY                (0x120101A0)

#define KLAD_CRG_CLOCK_BIT                      (0x01 << 1)
#define KLAD_CRG_RESET_BIT                      (0x01 << 0)
#elif (defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100) || \
       defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500))
#define CIPHER_RNG_REG_BASE_ADDR_PHY            (0x10130000)
#define CIPHER_CIPHER_REG_BASE_ADDR_PHY         (0x10100000)
#define CIPHER_RSA_REG_BASE_ADDR_PHY            (0x10120000)

#define CIPHER_RSA_CRG_ADDR_PHY                 (0x11012D00)
#define RSA_CRG_CLOCK_BIT                       (0x01 << 4)
#define RSA_CRG_RESET_BIT                       (0x01 << 0)
#define CIPHER_SPACC_CRG_ADDR_PHY               (0x11012C80)
#define SPACC_CRG_CLOCK_BIT                     (0x01 << 4)
#define SPACC_CRG_RESET_BIT                     (0x01 << 0)
#define CIPHER_RNG_CRG_ADDR_PHY                 (0x11012D80)
#define RNG_CRG_CLOCK_BIT                       (0x01 << 4)
#define RNG_CRG_RESET_BIT                       (0x01 << 0)

#define CIPHER_KLAD_REG_BASE_ADDR_PHY           (0x10110000)
#define CIPHER_OTP_REG_BASE_ADDR_PHY            (0x10200000)
#define CIPHER_KLAD_CRG_ADDR_PHY                (0x11012CC0)

#define KLAD_CRG_CLOCK_BIT                      (0x01 << 4)
#define KLAD_CRG_RESET_BIT                      (0x01 << 0)
#endif

#endif

