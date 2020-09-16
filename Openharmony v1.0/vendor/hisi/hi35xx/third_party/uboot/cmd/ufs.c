// SPDX-License-Identifier: GPL-2.0+
/**
 * ufs.c - UFS specific U-boot commands
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 *
 */
#include <common.h>
#include <command.h>
#include <ufs.h>

#ifndef CONFIG_UFS
static int do_ufs(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int dev, ret;

	if (argc >= 2) {
		if (!strcmp(argv[1], "init")) {
			if (argc == 3) {
				dev = simple_strtoul(argv[2], NULL, 10);
				ret = ufs_probe_dev(dev);
				if (ret)
					return CMD_RET_FAILURE;
			} else {
				ufs_probe();
			}

			return CMD_RET_SUCCESS;
		}
	}

	return CMD_RET_USAGE;
}

U_BOOT_CMD(ufs, 3, 1, do_ufs,
	   "UFS  sub system",
	   "init [dev] - init UFS subsystem\n"
);
#else

#define UFS_BLKSIZE_SHIFT 12
#define b2m(a) (((a) >> 10) / 1000)
#define b2k(a) (((a) >> 10) % 1000)
static int curr_device = 0;

static int do_ufs_read(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 blk, cnt;
	u64 addr;
	unsigned long long start_ticks, end_ticks;
	unsigned long long size, speed;

	if (argc != 5) /* 5 arg */
		return CMD_RET_USAGE;

	addr = (u64)simple_strtoul(argv[2], NULL, 16); /* arg 2: ddr addr, 16 in hex */
	blk = simple_strtoul(argv[3], NULL, 16);       /* arg 3: start block, 16 in hex */
	cnt = simple_strtoul(argv[4], NULL, 16);       /* arg 4: block count, 16 in hex */

	printf("\nUFS read: dev # %d, block # %d, count %d ... ", curr_device, blk, cnt);

	ufs_storage_init();
	start_ticks = get_ticks();
	if (ufs_read_storage(addr, (u64)blk << UFS_BLKSIZE_SHIFT, cnt << UFS_BLKSIZE_SHIFT)) {
		printf("0 blocks read: ERROR\n");
		return CMD_RET_FAILURE;
	}
	end_ticks = get_ticks();
	printf("%d blocks read: OK\n", cnt);

	size = cnt << UFS_BLKSIZE_SHIFT;
	speed = (size * CONFIG_SYS_TIMER_RATE) / (end_ticks - start_ticks);
	printf("%llu.%03llu MB/s\n", b2m(speed), b2k(speed));

	return CMD_RET_SUCCESS;
}

static int do_ufs_write(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 blk, cnt;
	u64 addr;
	unsigned long long start_ticks, end_ticks;
	unsigned long long size, speed;

	if (argc != 5) /* 5 arg */
		return CMD_RET_USAGE;

	addr = (u64)simple_strtoul(argv[2], NULL, 16); /* arg 2: ddr addr, 16 in hex */
	blk = simple_strtoul(argv[3], NULL, 16);       /* arg 3: start block, 16 in hex */
	cnt = simple_strtoul(argv[4], NULL, 16);       /* arg 4: block count, 16 in hex */

	if (strncmp(argv[0], "write.ext4sp", sizeof("write.ext4sp")) == 0) {
#ifdef CONFIG_EXT4_SPARSE
		printf("\nUFS write ext4 sparse: dev # %d, block # %d, count %d ...\n",
		       curr_device, blk, cnt);

		return ufs_ext4_unsparse((void *)(uintptr_t)addr, blk, cnt);
#else
		printf("Not support.\n");
		return CMD_RET_SUCCESS;
#endif
	}

	printf("\nUFS write: dev # %d, block # %d, count %d ... ", curr_device, blk, cnt);

	ufs_storage_init();
	start_ticks = get_ticks();
	if (ufs_write_storage(addr, (u64)blk << UFS_BLKSIZE_SHIFT, cnt << UFS_BLKSIZE_SHIFT)) {
		printf("0 blocks write: ERROR\n");
		return CMD_RET_FAILURE;
	}
	end_ticks = get_ticks();
	printf("%d blocks written: OK\n", cnt);

	size = cnt << UFS_BLKSIZE_SHIFT;
	speed = (size * CONFIG_SYS_TIMER_RATE) / (end_ticks - start_ticks);
	printf("%llu.%03llu MB/s\n", b2m(speed), b2k(speed));

	/* must write boot data to boot lun due to bootup demand,
	 * start from block 0, no longer than 0x400 blocks(4M).
	 */
	if ((blk == 0) && (cnt <= 0x400)) {
		/* write boot data */
		if (ufs_write_boot_storage(addr, (u64)blk << UFS_BLKSIZE_SHIFT,
				cnt << UFS_BLKSIZE_SHIFT)) {
			printf("boot write: ERROR\n");
			return CMD_RET_FAILURE;
		}
	}

	return CMD_RET_SUCCESS;
}

static int do_ufs_bootread(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 blk, cnt;
	u64 addr;

	if (argc != 5) /* 5 arg */
		return CMD_RET_USAGE;

	addr = (u64)simple_strtoul(argv[2], NULL, 16); /* arg 2: ddr addr, 16 in hex */
	blk = simple_strtoul(argv[3], NULL, 16);       /* arg 3: start block, 16 in hex */
	cnt = simple_strtoul(argv[4], NULL, 16);       /* arg 4: block count, 16 in hex */

	printf("\nUFS read: dev # %d, block # %d, count %d ... ", curr_device, blk, cnt);

	ufs_storage_init();
	if (ufs_read_boot_storage(addr, (u64)blk << UFS_BLKSIZE_SHIFT,
			cnt << UFS_BLKSIZE_SHIFT)) {
		printf("boot read: ERROR\n");
		return CMD_RET_FAILURE;
	}
	printf("%d blocks read: OK\n", cnt);

	return CMD_RET_SUCCESS;
}

static int do_ufs_bootwrite(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 blk, cnt;
	u64 addr;

	if (argc != 5) /* 5 arg */
		return CMD_RET_USAGE;

	addr = (u64)simple_strtoul(argv[2], NULL, 16); /* arg 2: ddr addr, 16 in hex */
	blk = simple_strtoul(argv[3], NULL, 16);       /* arg 3: start block, 16 in hex */
	cnt = simple_strtoul(argv[4], NULL, 16);       /* arg 4: block count, 16 in hex */

	printf("\nUFS write: dev # %d, block # %d, count %d ... ", curr_device, blk, cnt);

	ufs_storage_init();
	if (ufs_write_boot_storage(addr, (u64)blk << UFS_BLKSIZE_SHIFT,
			cnt << UFS_BLKSIZE_SHIFT)) {
		printf("boot write: ERROR\n");
		return CMD_RET_FAILURE;
	}
	printf("%d blocks write: OK\n", cnt);

	return CMD_RET_SUCCESS;
}

static int do_ufs_reinit(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (argc != 2) /* 2 arg */
		return CMD_RET_USAGE;

	ufs_reinit();

	return CMD_RET_SUCCESS;
}

static int do_ufs_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (argc != 2) /* 2 arg */
		return CMD_RET_USAGE;

	ufs_reg_dump();

	return CMD_RET_SUCCESS;
}

static int do_ufs_setlun(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 lun_num;

	if (argc != 2) /* 2 arg */
		return CMD_RET_USAGE;

	lun_num = simple_strtoul(argv[1], NULL, 16); /* arg 1: lun, 16 in hex */
	ufs_set_active_lun(lun_num);

	return CMD_RET_SUCCESS;
}

static int do_ufs_bootlun(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 lun_num;

	if (argc != 2) /* 2 arg */
		return CMD_RET_USAGE;

	lun_num = simple_strtoul(argv[1], NULL, 16); /* arg 1: lun, 16 in hex */
	ufs_set_bootlun(lun_num);

	return CMD_RET_SUCCESS;
}

static int do_ufs_hi(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret;

	if (argc != 2) /* 2 arg */
		return CMD_RET_USAGE;

	ret = ufs_hibernate_enter();
	if (ret)
		return CMD_RET_FAILURE;
	printf("hibernate in ok\n");
	return CMD_RET_SUCCESS;
}

static int do_ufs_ho(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret;

	if (argc != 2) /* 2 arg */
		return CMD_RET_USAGE;

	ret = ufs_hibernate_exit();
	if (ret)
		return CMD_RET_FAILURE;
	printf("hibernate out ok\n");
	return CMD_RET_SUCCESS;
}

static int do_ufs_mode(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct pwr_mode_params pmp;
	uint32_t mode, gear, rate, lane;

	if (argc != 5) /* 5 arg */
		return CMD_RET_USAGE;

	mode = simple_strtoul(argv[1], NULL, 16); /* arg 1: mode, 16 in hex */
	gear = simple_strtoul(argv[2], NULL, 16); /* arg 2: gear, 16 in hex */
	rate = simple_strtoul(argv[3], NULL, 16); /* arg 3: rate, 16 in hex */
	lane = simple_strtoul(argv[4], NULL, 16); /* arg 4: lane, 16 in hex */
	mode = (mode << 4) | mode; /* rx shift 4 */

	pmp.pwr_mode = mode;
	pmp.tx_gear = gear;
	pmp.rx_gear = gear;
	pmp.hs_series = rate;
	pmp.tx_lanes = lane;
	pmp.rx_lanes = lane;

	printf("UFS %s Gear-%d Rate-%c Lane-%d\n",
		 ((mode == SLOW_MODE) ? "Slow" :
		 ((mode == SLOWAUTO_MODE) ? "SlowAuto" :
		 ((mode == FAST_MODE) ? "Fast" : "FastAuto"))),
		 gear, (rate == 1) ? 'A' : 'B', lane);

	if (do_mode_change(&pmp)) {
		printf("power mode change fail\n");
		return CMD_RET_FAILURE;
	} else {
		printf("power mode change ok\n");
	}
	return CMD_RET_SUCCESS;
}

static cmd_tbl_t cmd_ufs[] = {
	U_BOOT_CMD_MKENT(read, 5, 0, do_ufs_read, "", ""),
	U_BOOT_CMD_MKENT(write, 5, 0, do_ufs_write, "", ""),
	U_BOOT_CMD_MKENT(bootread, 5, 0, do_ufs_bootread, "", ""),
	U_BOOT_CMD_MKENT(bootwrite, 5, 0, do_ufs_bootwrite, "", ""),
	U_BOOT_CMD_MKENT(reinit, 2, 0, do_ufs_reinit, "", ""),
	U_BOOT_CMD_MKENT(reg, 2, 0, do_ufs_reg, "", ""),
	U_BOOT_CMD_MKENT(setlun, 2, 0, do_ufs_setlun, "", ""),
	U_BOOT_CMD_MKENT(bootlun, 2, 0, do_ufs_bootlun, "", ""),
	U_BOOT_CMD_MKENT(hi, 2, 0, do_ufs_hi, "", ""),
	U_BOOT_CMD_MKENT(ho, 2, 0, do_ufs_ho, "", ""),
	U_BOOT_CMD_MKENT(mode, 5, 0, do_ufs_mode, "", ""),
};

static int do_ufsops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *cp = NULL;

	if (argc == 1) {
		cmd_usage(cmdtp);
		return CMD_RET_SUCCESS;
	}

	cp = find_cmd_tbl(argv[1], cmd_ufs, ARRAY_SIZE(cmd_ufs));

	/* Drop the ufs command */
	argc--;
	argv++;

	if (cp == NULL || argc > cp->maxargs)
		return CMD_RET_USAGE;

	return cp->cmd(cmdtp, flag, argc, argv);
}

U_BOOT_CMD(
	ufs, 6, 0, do_ufsops,
	"UFS sub system",
	"read <device num> addr blk# cnt\n"
	"ufs write <device num> addr blk# cnt\n"
	"ufs write.ext4sp <device num> addr blk# cnt\n"
	"ufs bootread <device num> addr blk# cnt\n"
	"ufs bootwrite <device num> addr blk# cnt\n"
	"ufs reinit <device num>\n"
	"ufs reg <device num>\n"
);

static int do_ufsinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 type;

	switch (argc) {
	case 0: /* 0 arg */
	case 1: /* 1 arg */
		ufs_show_desc_info(0xF);
		break;
	case 2: /* 2 arg */
		if (strncmp(argv[1], "-h", sizeof("-h")) == 0) {
			cmd_usage(cmdtp);
			break;
		}

		type = simple_strtoul(argv[1], NULL, 16); /* arg 1: type, 16 in hex */
		ufs_show_desc_info(type);
		break;
	default:
		return CMD_RET_USAGE;
	}

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	ufsinfo, 2, 0, do_ufsinfo,
	"display UFS info",
	"<idn>\n"
	"    idn :0x0  -- device descriptor\n"
	"    idn :0x1  -- configuration descriptor\n"
	"    idn :0x2  -- unit descriptor\n"
	"    idn :0x4  -- interconnect descriptor\n"
	"    idn :0x5  -- string descriptor\n"
	"    idn :0x7  -- geometry descriptor\n"
	"    idn :0x9  -- health descriptor\n"
	"    idn :0xE  -- show all info\n"
	"    idn :0xF  -- show basic info\n"
);
#endif
