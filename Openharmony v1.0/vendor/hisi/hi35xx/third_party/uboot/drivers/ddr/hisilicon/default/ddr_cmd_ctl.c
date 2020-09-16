/**
 * ddr_cmd_ctl.c
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
 * DDR training command control.
 */

#include <common.h>
#include "ddr_interface.h"
#include "ddr_training_impl.h"

#if PHY_DQ_BDL_LEVEL == 32
#define PRINT_DATAEYE_WIN(dq_num, range, dqs, dq, win) \
	do {\
		printf("%-4u", dq_num);\
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) {\
			if (k >= (range >> DDR_DATAEYE_RESULT_BIT)\
				&& k <= (range & DDR_DATAEYE_RESULT_MASK)) {\
				printf("%-3s", "-");\
			} else {\
				printf("%-3s", "X");\
			} \
		} \
		printf(" 0x%08x  0x%-4x%-4u%-4u\n", range, dqs, dq, win); \
	} while (0)

#define PRINT_DATAEYE_TITLE(phase) \
	do { \
		printf("%-4s", "DQ"); \
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) { \
			printf("%-3u", k); \
		} \
		printf(" %-10s  %-6s%-4s%-4s\n", \
			"RANGE", phase, "DQ", "WIN"); \
	} while (0)
#else
#define PRINT_DATAEYE_WIN(dq_num, range, dqs, dq, win) \
	do {\
		printf("%-4u", dq_num); \
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) { \
			if (k >= (range >> DDR_DATAEYE_RESULT_BIT)\
				&& k <= (range & DDR_DATAEYE_RESULT_MASK)) {\
				printf("%-1s", "-"); \
			} else {\
				printf("%-1s", "X"); \
			} \
		} \
		printf(" 0x%08x  0x%-4x%-4u%-4u\n", range, dqs, dq, win); \
	} while (0)

#define PRINT_DATAEYE_TITLE(phase) \
	do { \
		printf("%-4s", "DQ");\
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) { \
			if (0 == k % 4) \
				printf("%-4u", k); \
		} \
		printf(" %-10s  %-6s%-4s%-4s\n", \
			"RANGE", phase, "DQ", "WIN"); \
	} while (0)
#endif

#ifndef CONFIG_MINI_BOOT
extern char ddr_training_cmd_start[];  /* DDR training code start address */
extern char ddr_training_cmd_end[];    /* DDR training code end address */
#endif

static struct ddr_reg_val_st training_reg_val_rank0[] = {
	/* rank, byte, offset, value, name */
	{0, 0, DDR_PHY_DXWDQSDLY(0, 0), 0, "WDQS Byte0"},
	{0, 1, DDR_PHY_DXWDQSDLY(0, 1), 0, "WDQS Byte1"},
	{0, 2, DDR_PHY_DXWDQSDLY(0, 2), 0, "WDQS Byte2"},
	{0, 3, DDR_PHY_DXWDQSDLY(0, 3), 0, "WDQS Byte3"},
	{0, 0, DDR_PHY_DXNWDQDLY(0, 0), 0, "WDQ Phase Byte0"},
	{0, 1, DDR_PHY_DXNWDQDLY(0, 1), 0, "WDQ Phase Byte1"},
	{0, 2, DDR_PHY_DXNWDQDLY(0, 2), 0, "WDQ Phase Byte2"},
	{0, 3, DDR_PHY_DXNWDQDLY(0, 3), 0, "WDQ Phase Byte3"},
	{0, 0, DDR_PHY_DXNWDQNBDL0(0, 0), 0, "WDQ BDL DQ0-DQ3"},
	{0, 0, DDR_PHY_DXNWDQNBDL1(0, 0), 0, "WDQ BDL DQ4-DQ7"},
	{0, 1, DDR_PHY_DXNWDQNBDL0(0, 1), 0, "WDQ BDL DQ8-DQ11"},
	{0, 1, DDR_PHY_DXNWDQNBDL1(0, 1), 0, "WDQ BDL DQ12-DQ15"},
	{0, 2, DDR_PHY_DXNWDQNBDL0(0, 2), 0, "WDQ BDL DQ16-DQ19"},
	{0, 2, DDR_PHY_DXNWDQNBDL1(0, 2), 0, "WDQ BDL DQ20-DQ23"},
	{0, 3, DDR_PHY_DXNWDQNBDL0(0, 3), 0, "WDQ BDL DQ24-DQ27"},
	{0, 3, DDR_PHY_DXNWDQNBDL1(0, 3), 0, "WDQ BDL DQ28-DQ31"},
	{0, 0, DDR_PHY_DXNWDQNBDL2(0, 0), 0, "WDM Byte0"},
	{0, 1, DDR_PHY_DXNWDQNBDL2(0, 1), 0, "WDM Byte1"},
	{0, 2, DDR_PHY_DXNWDQNBDL2(0, 2), 0, "WDM Byte2"},
	{0, 3, DDR_PHY_DXNWDQNBDL2(0, 3), 0, "WDM Byte3"},
	{0, 0, DDR_PHY_DXNOEBDL(0, 0), 0, "Write DQ/DQS OE Byte0"},
	{0, 1, DDR_PHY_DXNOEBDL(0, 1), 0, "Write DQ/DQS OE Byte1"},
	{0, 2, DDR_PHY_DXNOEBDL(0, 2), 0, "Write DQ/DQS OE Byte2"},
	{0, 3, DDR_PHY_DXNOEBDL(0, 3), 0, "Write DQ/DQS OE Byte3"},
	{0, 0, DDR_PHY_DXNRDQSDLY(0), 0, "RDQS Byte0"},
	{0, 1, DDR_PHY_DXNRDQSDLY(1), 0, "RDQS Byte1"},
	{0, 2, DDR_PHY_DXNRDQSDLY(2), 0, "RDQS Byte2"},
	{0, 3, DDR_PHY_DXNRDQSDLY(3), 0, "RDQS Byte3"},
	{0, 0, DDR_PHY_DXNRDQNBDL0(0, 0), 0, "RDQ BDL DQ0-DQ3"},
	{0, 0, DDR_PHY_DXNRDQNBDL1(0, 0), 0, "RDQ BDL DQ4-DQ7"},
	{0, 1, DDR_PHY_DXNRDQNBDL0(0, 1), 0, "RDQ BDL DQ8-DQ11"},
	{0, 1, DDR_PHY_DXNRDQNBDL1(0, 1), 0, "RDQ BDL DQ12-DQ15"},
	{0, 2, DDR_PHY_DXNRDQNBDL0(0, 2), 0, "RDQ BDL DQ16-DQ19"},
	{0, 2, DDR_PHY_DXNRDQNBDL1(0, 2), 0, "RDQ BDL DQ20-DQ23"},
	{0, 3, DDR_PHY_DXNRDQNBDL0(0, 3), 0, "RDQ BDL DQ24-DQ27"},
	{0, 3, DDR_PHY_DXNRDQNBDL1(0, 3), 0, "RDQ BDL DQ28-DQ31"},
	{0, 0, DDR_PHY_DXNRDQSGDLY(0, 0), 0, "Gate Byte0"},
	{0, 1, DDR_PHY_DXNRDQSGDLY(0, 1), 0, "Gate Byte1"},
	{0, 2, DDR_PHY_DXNRDQSGDLY(0, 2), 0, "Gate Byte2"},
	{0, 3, DDR_PHY_DXNRDQSGDLY(0, 3), 0, "Gate Byte3"},
	{0, 0, DDR_PHY_ACCMDBDL2, 0, "CS"},
	{0, 0, DDR_PHY_ACPHYCTL7, 0, "CLK"},
	DDR_PHY_VREF_HOST_DISPLAY
	DDR_PHY_VREF_DRAM_DISPLAY
	DDR_PHY_ADDRPH_DISPLAY
	DDR_PHY_ADDRBDL_DISPLAY
	DDR_PHY_DCC_DISPLAY
};


/* rank 1*/
static struct ddr_reg_val_st training_reg_val_rank1[] = {
	{1, 0, DDR_PHY_DXWDQSDLY(1, 0), 0, "WDQS Byte0"},
	{1, 1, DDR_PHY_DXWDQSDLY(1, 1), 0, "WDQS Byte1"},
	{1, 2, DDR_PHY_DXWDQSDLY(1, 2), 0, "WDQS Byte2"},
	{1, 3, DDR_PHY_DXWDQSDLY(1, 3), 0, "WDQS Byte3"},
	{1, 0, DDR_PHY_DXNWDQDLY(1, 0), 0, "WDQ Phase Byte0"},
	{1, 1, DDR_PHY_DXNWDQDLY(1, 1), 0, "WDQ Phase Byte1"},
	{1, 2, DDR_PHY_DXNWDQDLY(1, 2), 0, "WDQ Phase Byte2"},
	{1, 3, DDR_PHY_DXNWDQDLY(1, 3), 0, "WDQ Phase Byte3"},
	{1, 0, DDR_PHY_DXNWDQNBDL0(1, 0), 0, "WDQ BDL DQ0-DQ3"},
	{1, 0, DDR_PHY_DXNWDQNBDL1(1, 0), 0, "WDQ BDL DQ4-DQ7"},
	{1, 1, DDR_PHY_DXNWDQNBDL0(1, 1), 0, "WDQ BDL DQ8-DQ11"},
	{1, 1, DDR_PHY_DXNWDQNBDL1(1, 1), 0, "WDQ BDL DQ12-DQ15"},
	{1, 2, DDR_PHY_DXNWDQNBDL0(1, 2), 0, "WDQ BDL DQ16-DQ19"},
	{1, 2, DDR_PHY_DXNWDQNBDL1(1, 2), 0, "WDQ BDL DQ20-DQ23"},
	{1, 3, DDR_PHY_DXNWDQNBDL0(1, 3), 0, "WDQ BDL DQ24-DQ27"},
	{1, 3, DDR_PHY_DXNWDQNBDL1(1, 3), 0, "WDQ BDL DQ28-DQ31"},
	{1, 0, DDR_PHY_DXNWDQNBDL2(1, 0), 0, "WDM Byte0"},
	{1, 1, DDR_PHY_DXNWDQNBDL2(1, 1), 0, "WDM Byte1"},
	{1, 2, DDR_PHY_DXNWDQNBDL2(1, 2), 0, "WDM Byte2"},
	{1, 3, DDR_PHY_DXNWDQNBDL2(1, 3), 0, "WDM Byte3"},
	{1, 0, DDR_PHY_DXNOEBDL(1, 0), 0, "Write DQ/DQS OE Byte0"},
	{1, 1, DDR_PHY_DXNOEBDL(1, 1), 0, "Write DQ/DQS OE Byte1"},
	{1, 2, DDR_PHY_DXNOEBDL(1, 2), 0, "Write DQ/DQS OE Byte2"},
	{1, 3, DDR_PHY_DXNOEBDL(1, 3), 0, "Write DQ/DQS OE Byte3"},

	{1, 0, DDR_PHY_DXNRDQSDLY(0), 0, "RDQS Byte0"},
	{1, 1, DDR_PHY_DXNRDQSDLY(1), 0, "RDQS Byte1"},
	{1, 2, DDR_PHY_DXNRDQSDLY(2), 0, "RDQS Byte2"},
	{1, 3, DDR_PHY_DXNRDQSDLY(3), 0, "RDQS Byte3"},

	{1, 0, DDR_PHY_DXNRDQNBDL0(1, 0), 0, "RDQ BDL DQ0-DQ3"},
	{1, 0, DDR_PHY_DXNRDQNBDL1(1, 0), 0, "RDQ BDL DQ4-DQ7"},
	{1, 1, DDR_PHY_DXNRDQNBDL0(1, 1), 0, "RDQ BDL DQ8-DQ11"},
	{1, 1, DDR_PHY_DXNRDQNBDL1(1, 1), 0, "RDQ BDL DQ12-DQ15"},
	{1, 2, DDR_PHY_DXNRDQNBDL0(1, 2), 0, "RDQ BDL DQ16-DQ19"},
	{1, 2, DDR_PHY_DXNRDQNBDL1(1, 2), 0, "RDQ BDL DQ20-DQ23"},
	{1, 3, DDR_PHY_DXNRDQNBDL0(1, 3), 0, "RDQ BDL DQ24-DQ27"},
	{1, 3, DDR_PHY_DXNRDQNBDL1(1, 3), 0, "RDQ BDL DQ28-DQ31"},
	{1, 0, DDR_PHY_DXNRDQSGDLY(1, 0), 0, "Gate Byte0"},
	{1, 1, DDR_PHY_DXNRDQSGDLY(1, 1), 0, "Gate Byte1"},
	{1, 2, DDR_PHY_DXNRDQSGDLY(1, 2), 0, "Gate Byte2"},
	{1, 3, DDR_PHY_DXNRDQSGDLY(1, 3), 0, "Gate Byte3"},
	{1, 0, DDR_PHY_ACCMDBDL2, 0, "CS"},
	{1, 0, DDR_PHY_ACPHYCTL7, 0, "CLK"},

	DDR_PHY_VREF_HOST_DISPLAY_RANK1
	DDR_PHY_VREF_DRAM_DISPLAY
	DDR_PHY_ADDRPH_DISPLAY
	DDR_PHY_ADDRBDL_DISPLAY
	DDR_PHY_DCC_DISPLAY
};

/**
 * ddr_cmd_result_print_dataeye
 * @ddrtr_data
 *
 *
 */
static void ddr_cmd_result_print_dataeye(
	struct ddr_training_data_st *ddrtr_data)
{
	unsigned int i, k, j;
	unsigned int dq_num, dqs, dq, win, win_min, win_max, win_sum;

	win_min = PHY_DQ_BDL_LEVEL;
	win_max = 0;
	win_sum = 0;
	printf("Write window of prebit-deskew:\n");
	printf("--------------------------------------------------------\n");
	PRINT_DATAEYE_TITLE("DQPH");
	for (j = 0; j < ddrtr_data->byte_num; j++) {
		dqs = (ddr_read(ddrtr_data->base_phy + DDR_PHY_DXNWDQDLY(ddrtr_data->rank_idx, j))
				>> PHY_WDQ_PHASE_BIT) & PHY_WDQ_PHASE_MASK;
		for (i = 0; i < DDR_PHY_BIT_NUM; i++) {
			dq_num = (j << 3) + i;
			win = ddrtr_data->write.ddr_bit_best[dq_num]
				>> DDR_DATAEYE_RESULT_BIT;
			if (win < win_min)
				win_min = win;
			if (win > win_max)
				win_max = win;
			win_sum += win;
			dq =  ddrtr_data->write.ddr_bit_best[dq_num]
				& DDR_DATAEYE_RESULT_MASK;
			PRINT_DATAEYE_WIN(dq_num,
					ddrtr_data->write.ddr_bit_result[dq_num],
					dqs, dq, win);
		}
	}
	printf("--------------------------------------------------------\n");
	printf("Sum WIN: %u. Avg WIN: %u\n", win_sum,
		win_sum / (ddrtr_data->byte_num * DDR_PHY_BIT_NUM));
	printf("Min WIN: %u. DQ Index: ", win_min);
	for (i = 0; i < DDR_PHY_BIT_MAX; i++) {
		win = ddrtr_data->write.ddr_bit_best[i]
			>> DDR_DATAEYE_RESULT_BIT;
		if (win == win_min)
			printf("%u ", i);
	}
	printf("\nMax WIN: %u. DQ Index: ", win_max);
	for (i = 0; i < DDR_PHY_BIT_MAX; i++) {
		win = ddrtr_data->write.ddr_bit_best[i]
			>> DDR_DATAEYE_RESULT_BIT;
		if (win == win_max)
			printf("%u ", i);
	}
	printf("\n\n");

	win_min = PHY_DQ_BDL_LEVEL;
	win_max = 0;
	win_sum = 0;
	printf("Read window of prebit-deskew:\n");
	printf("--------------------------------------------------------\n");
	PRINT_DATAEYE_TITLE("DQS");
	for (j = 0; j < ddrtr_data->byte_num; j++) {
		dqs = ddr_read(ddrtr_data->base_phy + DDR_PHY_DXNRDQSDLY(j))
				& PHY_RDQS_BDL_MASK;
		for (i = 0; i < DDR_PHY_BIT_NUM; i++) {
			dq_num = (j << 3) + i;
			win = ddrtr_data->read.ddr_bit_best[dq_num]
				>> DDR_DATAEYE_RESULT_BIT;
			if (win < win_min)
				win_min = win;
			if (win > win_max)
				win_max = win;
			win_sum += win;
			dq =  ddrtr_data->read.ddr_bit_best[dq_num]
				& DDR_DATAEYE_RESULT_MASK;
			PRINT_DATAEYE_WIN(dq_num,
					ddrtr_data->read.ddr_bit_result[dq_num],
					dqs, dq, win);
		}
	}
	printf("--------------------------------------------------------\n");
	printf("Sum WIN: %u. Avg WIN: %u\n", win_sum,
		win_sum / (ddrtr_data->byte_num * DDR_PHY_BIT_NUM));
	printf("Min WIN: %u. DQ Index: ", win_min);
	for (i = 0; i < DDR_PHY_BIT_MAX; i++) {
		win = ddrtr_data->read.ddr_bit_best[i]
			>> DDR_DATAEYE_RESULT_BIT;
		if (win == win_min)
			printf("%u ", i);
	}
	printf("\nMax WIN: %u. DQ Index: ", win_max);
	for (i = 0; i < DDR_PHY_BIT_MAX; i++) {
		win = ddrtr_data->read.ddr_bit_best[i]
			>> DDR_DATAEYE_RESULT_BIT;
		if (win == win_max)
			printf("%u ", i);
	}
	printf("\n\n");
}

static void ddr_cmd_result_print_ca(struct ddr_training_data_st *ddrtr_data)
{
	unsigned int i, j;
	unsigned int left, right, mid, win, min, max, sum;

	for (i = 0; i < DDR_PHY_CA_MAX; i++) {
		if (0 != ddrtr_data->ca_addr[i])
			break;
		if (i == (DDR_PHY_CA_MAX - 1))
			return; /* no result to print */
	}

	min = PHY_DQ_BDL_LEVEL;
	max = 0;
	sum = 0;

	printf("Command address window:\n");
	printf("--------------------------------------------------------\n");

	/* title */
	printf("%-4s", "CA");
	for (i = 0; i < PHY_DQ_BDL_LEVEL; i++) {
		if (0 == i % 4)
			printf("%-4u", i);
	}
	printf(" %-10s  %-6s%-4s\n", "RANGE", "BDL", "WIN");

	/* data */
	for (i = 0; i < DDR_PHY_CA_MAX; i++) {
		left = ddrtr_data->ca_addr[i] >> DDR_DATAEYE_RESULT_BIT;
		right = ddrtr_data->ca_addr[i] & DDR_DATAEYE_RESULT_MASK;
		mid = (left + right) >> 1;
		win = right - left + 1;

		printf("%-4u", i);
		for (j = 0; j < PHY_DQ_BDL_LEVEL; j++) {
			if (j >= left && j <= right)
				printf("%-1s", "-");
			else
				printf("%-1s", "X");
		}
		printf(" 0x%08x  %-6u%-4u\n",
			ddrtr_data->ca_addr[i], mid, win);

		if (win < min)
			min = win;
		if (win > max)
			max = win;
		sum += win;
	}
	printf("--------------------------------------------------------\n");

	printf("Sum WIN: %u. Avg WIN: %u\n", sum, sum / DDR_PHY_CA_MAX);
	printf("Min WIN: %u. CA Index: ", min);
	for (i = 0; i < DDR_PHY_CA_MAX; i++) {
		win = (ddrtr_data->ca_addr[i] & DDR_DATAEYE_RESULT_MASK)
			- (ddrtr_data->ca_addr[i] >> DDR_DATAEYE_RESULT_BIT)
			+ 1;
		if (win == min)
			printf("%u ", i);
	}
	printf("\nMax WIN: %u. CA Index: ", max);
	for (i = 0; i < DDR_PHY_CA_MAX; i++) {
		win = (ddrtr_data->ca_addr[i] & DDR_DATAEYE_RESULT_MASK)
			- (ddrtr_data->ca_addr[i] >> DDR_DATAEYE_RESULT_BIT)
			+ 1;
		if (win == max)
			printf("%u ", i);
	}
	printf("\n\n");
}

static void ddr_cmd_result_print_by_rank(struct ddr_training_result_st *ddrtr_result,
					 unsigned int cmd, unsigned int phy_index,
					 unsigned int rank_index)
{
	unsigned int mask = 1 << phy_index ; /* DDR_BYPASS_PHY0_MASK DDR_BYPASS_PHY1_MASK */
	struct rank_data_st *rank_st = &ddrtr_result->phy_st[phy_index].rank_st[rank_index];

	if (rank_st->item & mask)
		return;

	printf("\r\n[PHY%u][RANK%u]:\r\n", phy_index, rank_index);
	if (DDR_TRAINING_CMD_DATAEYE & cmd)
		ddr_cmd_result_print_dataeye(&rank_st->ddrtr_data);

	if (DDR_TRAINING_CMD_LPCA & cmd)
		ddr_cmd_result_print_ca(&rank_st->ddrtr_data);
}

static void ddr_cmd_result_print_by_phy(struct ddr_training_result_st *ddrtr_result,
					unsigned int cmd, unsigned int phy_index)
{
	int i;

	for (i = 0; i < ddrtr_result->phy_st[phy_index].rank_num; i++) {
		ddr_cmd_result_print_by_rank(ddrtr_result, cmd, phy_index, i);
	}
}

void ddr_cmd_result_display(struct ddr_training_result_st *ddrtr_result,
			    unsigned int cmd)
{
	int i;

	for (i = 0; i < ddrtr_result->phy_num; i++) {
		ddr_cmd_result_print_by_phy(ddrtr_result, cmd, i);
	}
}

void ddr_reg_result_display_by_rank(struct ddr_training_result_st *ddrtr_result,
				    unsigned int phy_index, unsigned int rank_index)
{
	int i;
	unsigned int base_phy = ddrtr_result->phy_st[phy_index].rank_st[rank_index].ddrtr_data.base_phy;
	unsigned int num;
	unsigned int byte_num = ddrtr_result->phy_st[phy_index].rank_st[rank_index].ddrtr_data.byte_num;
	unsigned int rank_num = ddrtr_result->phy_st[phy_index].rank_num;
	struct ddr_reg_val_st *ddr_reg = NULL;


	if (0 == rank_index) {
		num = sizeof(training_reg_val_rank0) / sizeof(struct ddr_reg_val_st);
		ddr_reg = &training_reg_val_rank0[0];
	} else {
		num = sizeof(training_reg_val_rank1) / sizeof(struct ddr_reg_val_st);
		ddr_reg = &training_reg_val_rank1[0];
	}

	printf("\r\n[PHY%u][RANK%u]:\r\n", phy_index, rank_index);
	for (i = 0; i < num; i++) {
		if (i != 0)
			ddr_reg++;

		if (0 == ddr_reg->offset)
			continue;

		if (ddr_reg->byte_index >= byte_num)
			continue;

		if (ddr_reg->rank_index >= rank_num)
			continue;

		ddr_reg->val = ddr_read(base_phy + ddr_reg->offset);

		printf("[0x%08x = 0x%08x] %-32s", base_phy + ddr_reg->offset,
				ddr_reg->val, ddr_reg->name);

		if (0 == (i + 1) % 2)
			printf("\r\n");
	}
}


void ddr_reg_result_display_by_phy(struct ddr_training_result_st *ddrtr_result,
				   unsigned int phy_index)
{
	unsigned int i;
	unsigned int mask = 1 << phy_index; /* DDR_BYPASS_PHY0_MASK or DDR_BYPASS_PHY1_MASK */
	unsigned int item;
	unsigned int enable = 0;
	unsigned int rank_num = ddrtr_result->phy_st[phy_index].rank_num;

	/* check rank0 and rank1 training item */
	for (i = 0; i < rank_num; i++) {
		item = ddrtr_result->phy_st[phy_index].rank_st[i].item;
		if (!(item & mask))
			enable = 1;
	}

	if (!enable)
		return;

	for (i = 0; i < rank_num; i++) {
		DDR_PHY_SWITCH_RANK((unsigned int)ddrtr_result->phy_st[phy_index].rank_st[i].ddrtr_data.base_phy, i);
		ddr_reg_result_display_by_rank(ddrtr_result, phy_index, i);
	}
}

/* Display DDR training register */
void ddr_reg_result_display(struct ddr_training_result_st *ddrtr_result)
{
	int i;

	for (i = 0; i < ddrtr_result->phy_num; i++) {
		ddr_reg_result_display_by_phy(ddrtr_result, i);
	}
	printf("\r\n");
}

#ifndef CONFIG_MINI_BOOT
static int ddr_cmd_is_disable(void)
{
	unsigned int cfg;
	unsigned int mask;
	unsigned int i;
	unsigned int disable = 1;

	cfg = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG);
	for (i = 0; i < DDR_PHY_NUM; i++) {
		mask = 1 << i;
		if (!(cfg & mask))
			disable = 0;
	}

#ifdef SYSCTRL_DDR_TRAINING_CFG_SEC
	cfg = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC);
	for (i = 0; i < DDR_PHY_NUM; i++) {
		mask = 1 << i;
		if (!(cfg & mask))
			disable = 0;
	}
#endif

	return disable;
}

/* Get DDR training command function entry address */
void *ddr_cmd_get_entry(void)
{
	char *src_ptr = 0;
	char *dst_ptr;
	unsigned int length = 0;

	src_ptr = ddr_training_cmd_start;
	dst_ptr = (char *)(DDR_TRAINING_RUN_STACK);
	length  = (uintptr_t)ddr_training_cmd_end - (uintptr_t)src_ptr;

	if (!src_ptr || !length) {
		printf("DDR training is unsupport.\n");
		return 0;
	}

	printf("DDR training cmd entry[0x%08X] size[%u]byte cfg[0x%08X = 0x%08X]",
		DDR_TRAINING_RUN_STACK, length,
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG),
		ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG));

#ifdef SYSCTRL_DDR_TRAINING_CFG_SEC
	printf("[0x%08X = 0x%08X]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC),
		ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC));
#endif
	printf("\n");

	if (ddr_cmd_is_disable()) {
		printf("Please config DDR training item. Bypass bit:\n"
			"[0]PHY0            : 0x1\n"
			"[1]PHY1            : 0x2\n"
			"[4]Write Leveling  : 0x10\n"
			"[8]Gate            : 0x100\n"
			"[16]Dataeye        : 0x10000\n"
			"[18]Pcode          : 0x40000\n"
			"[20]HW             : 0x100000\n"
			"[21]MPR            : 0x200000\n"
			"[22]AC             : 0x400000\n"
			"[23]LPCA           : 0x800000\n"
			"[24]Host Vref      : 0x1000000\n"
			"[25]Dram Vref      : 0x2000000\n"
			"[27]DCC            : 0x8000000\n"
			"[28]Dataeye Adjust : 0x10000000\n"
			"[29]WL Write Adjust: 0x20000000\n"
			"[30]HW Read Adjust : 0x40000000\n");
		return 0;
	}

	ddr_cmd_prepare_copy();
	memcpy(dst_ptr, src_ptr, length);
	return (void *) dst_ptr;
}

/* Copy training codes from DDR to SRAM and do ddr training */
struct ddr_training_result_st *ddr_cmd_training_if(struct ddr_cmd_st *cmd_st)
{
	ddr_cmd_entry_func entry;
	struct ddr_training_result_st *result_st = NULL;
	struct tr_relate_reg reg;

	entry = (ddr_cmd_entry_func)ddr_cmd_get_entry();
	if (!entry)
		return 0;

#ifdef CONFIG_ARM64
	asm("isb");
	asm("dsb sy");
#else
	asm("mcr p15, 0, r0, c7, c5, 0");  /* instruction cache invalidate all to PoU */
	asm("mcr p15, 0, r0, c7, c10, 4"); /* data synchronization barrier operation */
#endif

	ddr_boot_cmd_save_func(&reg);
	/* save site before execute cmd */
	ddr_cmd_site_save();

	/* entry = ddr_training_cmd_entry() */
	result_st = entry(cmd_st);

	/* restore site before execute cmd */
	ddr_cmd_site_restore();

	ddr_boot_cmd_restore_func(&reg);

	if (!result_st) {
		printf("DDR training fail\n");
		return 0;
	}

	return result_st;
}
#endif
