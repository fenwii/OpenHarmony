/*
 * hicpu_common.h
 *
 * The Flash Memory Controller v100 Device Driver for hisilicon
 *
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

#ifndef __HICPU_COMMON_H__
#define __HICPU_COMMON_H__

#include <command.h>

#ifdef CONFIG_EMMC
extern int target_dev;
extern int target_paratition;
#endif 

void reset_cpu(ulong addr);
void uart_early_init(void);
void uart_early_puts(const char *ss);
extern unsigned char input_data[];
extern unsigned char input_data_end[];
extern unsigned long _armboot_start;
extern int hisi_sdhci_add_port(int index, u32 regbase, u32 freq);
extern int hisi_mmc_init(int index);

#if (CONFIG_AUTO_UPDATE == 1)
extern int do_auto_update(void);
extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[]);
#endif /* CONFIG_AUTO_UPDATE */

#ifdef CONFIG_GENERIC_MMC
extern int himci_probe(int dev_num);
#endif /* CONFIG_GENERIC_MMC */

#ifdef CONFIG_SUPPORT_EMMC_BOOT
extern int himci_add_port(int index, u32 reg_base, u32 freq);
#endif /* CONFIG_SUPPORT_EMMC_BOOT */

#ifdef CONFIG_AUTO_SD_UPDATE
extern int himci_add_port(int index, u32 reg_base, u32 freq);
#endif /* CONFIG_AUTO_SD_UPDATE */

extern int mmc_phy_init(void);

#ifdef CONFIG_CMD_NAND
extern int nand_saveenv(void);
extern void nand_env_relocate_spec(void);
#endif /* CONFIG_CMD_NAND */

#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
extern int sf_saveenv(void);
extern void sf_env_relocate_spec(void);
#endif /* CONFIG_ENV_IS_IN_SPI_FLASH */

#ifdef CONFIG_ENV_IS_IN_MMC
extern int emmc_saveenv(void);
extern void emmc_env_relocate_spec(void);
#endif /* CONFIG_ENV_IS_IN_MMC */

#ifdef CONFIG_ENV_IS_IN_UFS
extern int ufs_saveenv(void);
extern void ufs_env_relocate_spec(void);
#endif /* CONFIG_ENV_IS_IN_UFS */

#endif /* __HICPU_COMMON_H__ */

