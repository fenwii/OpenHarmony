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
 * Description:DDR training command define
 */

#include <common.h>
#include <command.h>
#include "ddr_interface.h"

#ifndef TEXT_BASE
#define TEXT_BASE (CONFIG_SYS_TEXT_BASE) /* for arm64 u-boot-2016.11 */
#endif

#define DDR_TRAINING_ENV            "ddrtr"
#define DDR_TRAINING_ENV_UN         "unddrtr"

#define DDR_TRAINING_DDRT_START_OFFSET  0x400000  /* 4M */
#define DDR_TRAINING_DDRT_LENGTH  0x400000  /* 4M  at lease 0x8000 */

#define DDR_CMD_SW_STR              "training"
#define DDR_CMD_TR_STR              "tr"
#define DDR_CMD_HW_STR              "hw"
#define DDR_CMD_MPR_STR             "mpr"
#define DDR_CMD_WL_STR              "wl"
#define DDR_CMD_GATE_STR            "gate"
#define DDR_CMD_DATAEYE_STR         "dataeye"
#define DDR_CMD_VREF_STR            "vref"
#define DDR_CMD_DCC_STR             "dcc"
#define DDR_CMD_PCODE_STR           "pcode"
#define DDR_CMD_AC_STR              "ac"
#define DDR_CMD_LPCA_STR            "lpca"
#define DDR_CMD_LOG_STR             "log"
#define DDR_CMD_BOOT_STR            "boot"
#define DDR_CMD_CONSOLE_STR         "console"

#ifndef CONFIG_MINI_BOOT
static struct ddr_training_result_st ddrtr_result_st; /* DDR training result */
static int ddr_log_level = DDR_LOG_ERROR;       /* DDR training log level */
#endif

#ifdef CONFIG_DDR_TRAINING_BOOTENV
extern int do_saveenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
#endif
#ifdef DDR_TRAINING_EXEC_TIME
/**
 * Start timer for calculate DDR training execute time.
 * NOTE: Just only for debug.
 */
static void cmd_exec_timer_start(void)
{
	/* timer start */
	ddr_write(0, 0xF8002000); /* REG_BASE_TIMER01 + REG_TIMER_RELOAD */
	/* TIMER_EN  | TIMER_MODE |TIMER_PRE | TIMER_SIZE, REG_TIMER_CONTROL */
	ddr_write(0xc2, 0xF8002008);
	ddr_write(0xffffffff, 0xF8002000);
}

/**
 * Stop timer for calculate DDR training execute time.
 * NOTE: Just only for debug.
 */
static void cmd_exec_timer_stop(void)
{
	/* timer stop */
	ddr_write(0, 0xF8002008); /* REG_TIMER_CONTROL */
	/* REG_TIMER_VALUE, 24MHz */
	printf("DDR training execute time: [%d]us\n",
		(0xffffffff - ddr_read(0xF8002004)) / 24);
}
#endif

#ifndef CONFIG_MINI_BOOT
/**
 * Match string command.
 * NOTE: Write leveling not support run repeatedly,
 * so limit WL only run one time.
 */
static int cmd_ddr_match(const char *str, int *cmd)
{
	static int wl_done;  /* Write leveling control */

	if (!strncmp(str, DDR_CMD_SW_STR, sizeof(DDR_CMD_SW_STR))) {
		*cmd = DDR_TRAINING_CMD_SW_NO_WL;
	} else if (!strncmp(str, DDR_CMD_TR_STR, sizeof(DDR_CMD_TR_STR))) {
		if (wl_done) {
			*cmd = DDR_TRAINING_CMD_SW_NO_WL;
		} else {
			wl_done++;
			*cmd = DDR_TRAINING_CMD_SW;
		}
	} else if (!strncmp(str, DDR_CMD_HW_STR, sizeof(DDR_CMD_HW_STR))) {
		*cmd = DDR_TRAINING_CMD_HW;
	} else if (!strncmp(str, DDR_CMD_MPR_STR, sizeof(DDR_CMD_MPR_STR))) {
		*cmd = DDR_TRAINING_CMD_MPR;
	} else if (!strncmp(str, DDR_CMD_WL_STR, sizeof(DDR_CMD_WL_STR))) {
		if (wl_done) {
			printf("WL not support run repeatedly. %s",
				"Already done once, can not do again.\n");
			return -1;
		} else {
			*cmd = DDR_TRAINING_CMD_WL;
			wl_done++;
		}
	} else if (!strncmp(str, DDR_CMD_GATE_STR, sizeof(DDR_CMD_GATE_STR))) {
		*cmd = DDR_TRAINING_CMD_GATE;
	} else if (!strncmp(str, DDR_CMD_DATAEYE_STR,
				sizeof(DDR_CMD_DATAEYE_STR))) {
		*cmd = DDR_TRAINING_CMD_DATAEYE;
	} else if (!strncmp(str, DDR_CMD_VREF_STR, sizeof(DDR_CMD_VREF_STR))) {
		*cmd = DDR_TRAINING_CMD_VREF;
	} else if (!strncmp(str, DDR_CMD_AC_STR, sizeof(DDR_CMD_AC_STR))) {
		*cmd = DDR_TRAINING_CMD_AC;
	} else if (!strncmp(str, DDR_CMD_LPCA_STR, sizeof(DDR_CMD_LPCA_STR))) {
		*cmd = DDR_TRAINING_CMD_LPCA;
	} else if (!strncmp(str, DDR_CMD_DCC_STR, sizeof(DDR_CMD_DCC_STR))) {
		*cmd = DDR_TRAINING_CMD_DCC;
	} else if (!strncmp(str, DDR_CMD_PCODE_STR, sizeof(DDR_CMD_PCODE_STR))) {
		*cmd = DDR_TRAINING_CMD_PCODE;
	} else if (!strncmp(str, DDR_CMD_CONSOLE_STR, sizeof(DDR_CMD_CONSOLE_STR))) {
		*cmd = DDR_TRAINING_CMD_CONSOLE;
	} else {
		printf("Command [ddr %s] is unsupport.\n", str);
		return -1;
	}

	return 0;
}

/**
 * Handle DDR training.
 * Copy training codes from DDR to SRAM.
 */
static int cmd_ddr_handle(int cmd)
{
	struct ddr_training_result_st *result_st = NULL;
	struct ddr_cmd_st cmd_st;

	cmd_st.cmd = cmd;
	cmd_st.level = ddr_log_level;
	cmd_st.start = TEXT_BASE + DDR_TRAINING_DDRT_START_OFFSET;
	cmd_st.length = DDR_TRAINING_DDRT_LENGTH;

	printf("DDR training area: 0x%08X - 0x%08X\n",
		   cmd_st.start, cmd_st.start + cmd_st.length);

#ifdef DDR_TRAINING_EXEC_TIME
	cmd_exec_timer_start();
#endif

	result_st = ddr_cmd_training_if(&cmd_st);

#ifdef DDR_TRAINING_EXEC_TIME
	cmd_exec_timer_stop();
#endif

	if (!result_st)
		return -1;

	if (sizeof(ddrtr_result_st) != sizeof(*result_st))
		return -1;

	/* copy training result from SRAM to DDR */
	memcpy((void *)&ddrtr_result_st, result_st,
			sizeof(*result_st));
	printf("DDR training finished.\n");

	return 0;
}

/* DDR training cmd dispatch */
static int cmd_ddr_dispatch(int cmd)
{
	int result = 0;

	result = cmd_ddr_handle(cmd);
	switch (cmd) {
	case DDR_TRAINING_CMD_SW:
	case DDR_TRAINING_CMD_SW_NO_WL:
	case DDR_TRAINING_CMD_CONSOLE:
		ddr_cmd_result_display(&ddrtr_result_st,
			DDR_TRAINING_CMD_DATAEYE
			| DDR_TRAINING_CMD_LPCA);
		break;
	case DDR_TRAINING_CMD_DATAEYE:
	case DDR_TRAINING_CMD_VREF:
		ddr_cmd_result_display(&ddrtr_result_st,
			DDR_TRAINING_CMD_DATAEYE);
		break;
	case DDR_TRAINING_CMD_WL:
	case DDR_TRAINING_CMD_GATE:
	case DDR_TRAINING_CMD_HW:
	case DDR_TRAINING_CMD_DCC:
	case DDR_TRAINING_CMD_PCODE:
		break;
	case DDR_TRAINING_CMD_LPCA:
		ddr_cmd_result_display(&ddrtr_result_st,
			DDR_TRAINING_CMD_LPCA);
		break;
	default:
		break;
	}

	ddr_reg_result_display(&ddrtr_result_st);
	return result;
}

/* Set DDR training log level */
int cmd_ddr_set_log_level(char * const argv[])
{
	int level;
	const char *str;

	str = argv[1];
	if (strncmp(str, DDR_CMD_LOG_STR, sizeof(DDR_CMD_LOG_STR))) {
		printf("Command [ddr %s] is unsupport.\n", str);
		return -1;
	}

	str = argv[2];
	if (!strncmp(str, DDR_LOG_INFO_STR, sizeof(DDR_LOG_INFO_STR))) {
		level = DDR_LOG_INFO;
	} else if (!strncmp(str, DDR_LOG_DEBUG_STR,
				sizeof(DDR_LOG_DEBUG_STR))) {
		level = DDR_LOG_DEBUG;
	} else if (!strncmp(str, DDR_LOG_WARNING_STR,
				sizeof(DDR_LOG_WARNING_STR))) {
		level = DDR_LOG_WARNING;
	} else if (!strncmp(str, DDR_LOG_ERROR_STR,
				sizeof(DDR_LOG_ERROR_STR))) {
		level = DDR_LOG_ERROR;
	} else if (!strncmp(str, DDR_LOG_FATAL_STR,
				sizeof(DDR_LOG_FATAL_STR))) {
		level = DDR_LOG_FATAL;
	} else {
		printf("Command [ddr log %s] is unsupport.\n", str);
		return -1;
	}

	ddr_log_level = level;
	printf("Set DDR training log level [%s] suc.\n", str);

	return 0;
}

/**
 * Accept DDR training cmd.
 * Set training result to env without save.
 */
static int do_ddr_training(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	const char *str = NULL;
	int cmd;

	if (argc < 2 || argc > 3) {
		/* cmd_usage(cmdtp); */
		return -1;
	} else if (argc == 3) {
		return cmd_ddr_set_log_level(argv);
	}

	str = argv[1];

	if (cmd_ddr_match(str, &cmd))
		return -1;

	if (cmd_ddr_dispatch(cmd))
		return -1;

	return 0;
}


U_BOOT_CMD(
	ddr, CONFIG_SYS_MAXARGS, 1,	do_ddr_training,
	"ddr training function",
	"training    - DDR sofeware(Gate/Dataeye/Vref) training.\n"
	"ddr tr          - DDR sofeware(WL/Gate/Dataeye/Vref) training.\n"
	"ddr wl          - DDR Write leveling training.\n"
	"ddr gate        - DDR gate training.\n"
	"ddr dataeye     - DDR dataeye training and display training result.\n"
	"ddr vref        - DDR vref training.\n"
	"ddr hw          - DDR hardware training.\n"
	"ddr mpr         - DDR Multi-Purpose Register training.\n"
	"ddr ac          - DDR address command training.\n"
	"ddr lpca        - LPDDR command address training.\n"
	"ddr dcc         - DDR Duty Correction Control training.\n"
	"ddr pcode       - DDR io pcode training.\n"
	"ddr console     - DDR do training in SRAM.\n"
	"ddr log [level] - DDR log level. [info,debug,warning,error,fatal]\n"
);
#endif
