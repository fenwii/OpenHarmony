// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2016 Google, Inc
 * Written by Amar <amarendra.xt@samsung.com>
 */

#include <common.h>
#include <mmc.h>
#include "mmc_private.h"

#include <asm/io.h>
#include <memalign.h>

/*
 * This function changes the size of boot partition and the size of rpmb
 * partition present on EMMC devices.
 *
 * Input Parameters:
 * struct *mmc: pointer for the mmc device strcuture
 * bootsize: size of boot partition
 * rpmbsize: size of rpmb partition
 *
 * Returns 0 on success.
 */

int mmc_boot_partition_size_change(struct mmc *mmc, unsigned long bootsize,
				unsigned long rpmbsize)
{
	int err;
	struct mmc_cmd cmd;

	/* Only use this command for raw EMMC moviNAND. Enter backdoor mode */
	cmd.cmdidx = MMC_CMD_RES_MAN;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = MMC_CMD62_ARG1;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err) {
		debug("mmc_boot_partition_size_change: Error1 = %d\n", err);
		return err;
	}

	/* Boot partition changing mode */
	cmd.cmdidx = MMC_CMD_RES_MAN;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = MMC_CMD62_ARG2;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err) {
		debug("mmc_boot_partition_size_change: Error2 = %d\n", err);
		return err;
	}
	/* boot partition size is multiple of 128KB */
	bootsize = (bootsize * 1024) / 128;

	/* Arg: boot partition size */
	cmd.cmdidx = MMC_CMD_RES_MAN;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = bootsize;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err) {
		debug("mmc_boot_partition_size_change: Error3 = %d\n", err);
		return err;
	}
	/* RPMB partition size is multiple of 128KB */
	rpmbsize = (rpmbsize * 1024) / 128;
	/* Arg: RPMB partition size */
	cmd.cmdidx = MMC_CMD_RES_MAN;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = rpmbsize;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err) {
		debug("mmc_boot_partition_size_change: Error4 = %d\n", err);
		return err;
	}
	return 0;
}

/*
 * Modify EXT_CSD[177] which is BOOT_BUS_WIDTH
 * based on the passed in values for BOOT_BUS_WIDTH, RESET_BOOT_BUS_WIDTH
 * and BOOT_MODE.
 *
 * Returns 0 on success.
 */
int mmc_set_boot_bus_width(struct mmc *mmc, u8 width, u8 reset, u8 mode)
{
	return mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BOOT_BUS_WIDTH,
			  EXT_CSD_BOOT_BUS_WIDTH_MODE(mode) |
			  EXT_CSD_BOOT_BUS_WIDTH_RESET(reset) |
			  EXT_CSD_BOOT_BUS_WIDTH_WIDTH(width));
}

/*
 * Modify EXT_CSD[179] which is PARTITION_CONFIG (formerly BOOT_CONFIG)
 * based on the passed in values for BOOT_ACK, BOOT_PARTITION_ENABLE and
 * PARTITION_ACCESS.
 *
 * Returns 0 on success.
 */
int mmc_set_part_conf(struct mmc *mmc, u8 ack, u8 part_num, u8 access)
{
	int ret;
	u8 part_conf;

	part_conf = EXT_CSD_BOOT_ACK(ack) |
		    EXT_CSD_BOOT_PART_NUM(part_num) |
		    EXT_CSD_PARTITION_ACCESS(access);

	ret = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PART_CONF,
			 part_conf);
	if (!ret)
		mmc->part_config = part_conf;

	return ret;
}

/*
 * Modify EXT_CSD[162] which is RST_n_FUNCTION based on the given value
 * for enable.  Note that this is a write-once field for non-zero values.
 *
 * Returns 0 on success.
 */
int mmc_set_rst_n_function(struct mmc *mmc, u8 enable)
{
	return mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_RST_N_FUNCTION,
			  enable);
}

u8 mmc_get_boot_mode(void)
{
#if defined(CONFIG_TARGET_HI3519AV100) || defined(CONFIG_TARGET_HI3556AV100) ||\
	defined(CONFIG_TARGET_HI3516DV300) || defined(CONFIG_TARGET_HI3516CV500) ||\
	defined(CONFIG_TARGET_HI3559V200)  || defined(CONFIG_TARGET_HI3556V200)  ||\
	defined(CONFIG_TARGET_HI3516AV300) || defined(CONFIG_TARGET_HI3531DV200) ||\
	defined(CONFIG_TARGET_HI3535AV100) || defined(CONFIG_TARGET_HI3562V100)  ||\
	defined(CONFIG_TARGET_HI3566V100)  || defined(CONFIG_TARGET_HI3521DV200) ||\
	defined(CONFIG_TARGET_HI3520DV500)
	u32 reg_val;
#endif
	u8 boot_mode;

#if defined(CONFIG_TARGET_HI3519AV100) || defined(CONFIG_TARGET_HI3556AV100) ||\
	defined(CONFIG_TARGET_HI3516DV300) || defined(CONFIG_TARGET_HI3516CV500) ||\
	defined(CONFIG_TARGET_HI3559V200)  || defined(CONFIG_TARGET_HI3556V200)  ||\
	defined(CONFIG_TARGET_HI3516AV300) || defined(CONFIG_TARGET_HI3562V100)  ||\
	defined(CONFIG_TARGET_HI3566V100)
	reg_val = readl(REG_BASE_SCTL + REG_PERISTAT);
	if (mmc_boot_clk_sel(reg_val) == MMC_BOOT_CLK_50M)
		boot_mode = 1;
	else
		boot_mode = 0;

#elif defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100) ||\
	defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
	reg_val = readl(REG_BASE_SCTL + REG_PERI_EMMC_STAT);
	if (mmc_boot_clk_sel(reg_val) == MMC_BOOT_CLK_50M)
		boot_mode = 1;
	else
		boot_mode = 0;
#else
		boot_mode = 0;
#endif
	return boot_mode;
}

#define EXT_CSD_REV_4_41	5

int mmc_set_boot_config(struct mmc *mmc)
{
	int err, changed = 0;
	u8 val, rev, rst_n_en;
	u8 boot_part, boot_bus_width, part_conf, bus_cond, boot_mode;
	ALLOC_CACHE_ALIGN_BUFFER(u8, ext_csd, MMC_MAX_BLOCK_LEN);

	err = mmc_send_ext_csd(mmc, ext_csd);
	if (err) {
		printf("Get ext_csd error!\n");
		return err;
	}

	rev = ext_csd[EXT_CSD_REV];
	rst_n_en = ext_csd[EXT_CSD_RST_N_FUNCTION] & EXT_CSD_RST_N_EN_MASK;
	if ((rev >= EXT_CSD_REV_4_41) && (rst_n_en != EXT_CSD_RST_N_ENABLED)) {
		err = mmc_set_rst_n_function(mmc, EXT_CSD_RST_N_ENABLED);
		if (err) {
			printf("mmc_set_rst_n_function error!\n");
			return err;
		}
	}

	if ((rev >= EXT_CSD_REV_4_41) &&
			(ext_csd[EXT_CSD_WR_REL_PARAM] & EXT_CSD_HS_CTRL_REL)) {
		val = ext_csd[EXT_CSD_WR_REL_SET];
		if (val != EXT_CSD_WR_REL_VALUE) {
			err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
					EXT_CSD_WR_REL_SET,
					EXT_CSD_WR_REL_VALUE);
			if (err) {
				printf("Set EXT_CSD_WR_REL_SET error!\n");
				return err;
			}
		}
	}

	boot_part = 0x7; /* user area enable for boot */
	if (readl(REG_BASE_SCTL + REG_SYSSTAT) & NF_BOOTBW_MASK)
		boot_bus_width = EXT_CSD_BUS_WIDTH_8; /* 8bits */
	else
		boot_bus_width = EXT_CSD_BUS_WIDTH_4; /* 4bits */

	boot_mode = mmc_get_boot_mode();
	part_conf = EXT_CSD_BOOT_ACK(0) |
		EXT_CSD_BOOT_PART_NUM(boot_part) |
		EXT_CSD_PARTITION_ACCESS(0);
	bus_cond = EXT_CSD_BOOT_BUS_WIDTH_MODE(boot_mode) |
		EXT_CSD_BOOT_BUS_WIDTH_RESET(0) |
		EXT_CSD_BOOT_BUS_WIDTH_WIDTH(boot_bus_width);

	if (ext_csd[EXT_CSD_PART_CONF] != part_conf) {
		err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
				EXT_CSD_PART_CONF, part_conf);
		if (err) {
			printf("Set EXT_CSD_PART_CONF error!\n");
			return err;
		}
		changed = 1;
	}

	if (ext_csd[EXT_CSD_BOOT_BUS_WIDTH] != bus_cond) {
		err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
				EXT_CSD_BOOT_BUS_WIDTH, bus_cond);
		if (err) {
			printf("Set EXT_CSD_BOOT_BUS_WIDTH error!\n");
			return err;
		}
		changed = 1;
	}

	if (!changed)
		return 0;

	err = mmc_send_ext_csd(mmc, ext_csd);
	if (err) {
		printf("Check ext_csd error!\n");
		return err;
	}

	if (part_conf != ext_csd[EXT_CSD_PART_CONF] ||
			bus_cond != ext_csd[EXT_CSD_BOOT_BUS_WIDTH]) {
		printf("EXT_CSD CONFIG Fail!\n");
		return -1;
	}

	printf("EXT_CSD CONFIG OK!\n");
	return 0;
}
