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
 * Description:DDR training command implement.
 */

#include <stdarg.h>
#include <command.h>
#include "ddr_interface.h"
#include "ddr_training_impl.h"

/* ddr training cmd result */
struct ddr_training_result_st ddrt_result_sram;
static unsigned int ddr_training_addr_start;
static unsigned int ddr_training_addr_end;
static int ddr_print_level = DDR_LOG_ERROR;

#ifdef DDR_TRAINING_LOG_CONFIG

/* Log ddr training info. */
void ddr_training_log(const char *func, int level, const char *fmt, ...)
{
	va_list args;

	if (ddr_print_level > level)
		return;

	DDR_PUTC('[');
	switch (level) {
	case DDR_LOG_INFO:
		DDR_PUTS("INFO");
		break;
	case DDR_LOG_DEBUG:
		DDR_PUTS("DEBUG");
		break;
	case DDR_LOG_WARNING:
		DDR_PUTS("WARNING");
		break;
	case DDR_LOG_ERROR:
		DDR_PUTS("ERROR");
		break;
	case DDR_LOG_FATAL:
		DDR_PUTS("FATAL");
		break;
	default:
		break;
	}
	DDR_PUTC(']');
	DDR_PUTC('[');
	DDR_PUTS(func);
	DDR_PUTC(']');

	va_start(args, fmt);
	while (*fmt != '\0') {
		if (*fmt != '%') {
			DDR_PUTC(*fmt);
		} else {
			fmt++;
			switch (*fmt) {
			case 'x':
			case 'X':
				DDR_PUTS("0x");
				DDR_PUT_HEX(va_arg(args, int));
				break;
			default:
				DDR_PUTC('%');
				DDR_PUTC(*fmt);
				break;
			} /* switch */
		}
		fmt++;
	} /* while */
	va_end(args);
	DDR_PUTS("\r\n");
}

/* Nothing to do in DDR command when defined DDR_TRAINING_LOG_CONFIG. */
void ddr_training_error(unsigned int mask, unsigned int phy, int byte, int dq)
{
	return;
}
#else
/* Display DDR training error. */
void ddr_training_error(unsigned int mask, unsigned int phy, int byte, int dq)
{
	switch (mask) {
	case DDR_ERR_WL:
		DDR_PUTS("WL");
		break;
	case DDR_ERR_HW_GATING:
		DDR_PUTS("HW Gate");
		break;
	case DDR_ERR_GATING:
		DDR_PUTS("Gate");
		break;
	case DDR_ERR_DDRT_TIME_OUT:
		DDR_PUTS("DDRT");
		break;
	case DDR_ERR_HW_RD_DATAEYE:
		DDR_PUTS("HW Dataeye");
		break;
	case DDR_ERR_MPR:
		DDR_PUTS("MPR");
		break;
	case DDR_ERR_DATAEYE:
		DDR_PUTS("Dataeye");
		break;
	case DDR_ERR_LPCA:
		DDR_PUTS("LPCA");
		break;
	default:
		break;
	}

	DDR_PUTS(" Err:");

	if (phy != 0) {
		DDR_PUTS(" Phy:");
		DDR_PUT_HEX(phy);
	}

	if (byte != -1) {
		DDR_PUTS(" Byte:");
		DDR_PUT_HEX(byte);
	}

	if (dq != -1) {
		DDR_PUTS(" DQ:");
		DDR_PUT_HEX(dq);
	}

	DDR_PUTS("\r\n");
}
#endif

/* Inint ddr training cmd result */
static void ddr_training_result_init(struct ddr_cfg_st *cfg, struct ddr_training_result_st *ddrtr_res)
{
	int i, j;

	ddrtr_memset(ddrtr_res, 0, sizeof(struct ddr_training_result_st));
	ddrtr_res->phy_num = cfg->phy_num;
	for (i = 0; i < cfg->phy_num; i++) {
		ddrtr_res->phy_st[i].rank_num = cfg->phy[i].rank_num;

		for (j = 0; j < cfg->phy[i].rank_num; j++) {
			ddrtr_res->phy_st[i].rank_st[j].item = cfg->phy[i].rank[j].item;
			ddrtr_res->phy_st[i].rank_st[j].ddrtr_data.base_phy = cfg->phy[i].addr;
			ddrtr_res->phy_st[i].rank_st[j].ddrtr_data.byte_num = cfg->phy[i].total_byte_num;
			ddrtr_res->phy_st[i].rank_st[j].ddrtr_data.rank_idx = j;
		}
	}
}

/* Save ddr training cmd result */
void ddr_result_data_save(struct ddr_cfg_st *cfg, struct training_data *training)
{
	unsigned int i;
	unsigned int offset;
	struct training_data *dest = NULL;
	struct ddr_training_result_st *ddrtr_res = (struct ddr_training_result_st *)cfg->res_st;

	if (!ddrtr_res)
		return;

	if (cfg->cur_mode == DDR_MODE_READ)
		dest = &ddrtr_res->phy_st[cfg->phy_idx].rank_st[cfg->rank_idx].ddrtr_data.read;
	else
		dest = &ddrtr_res->phy_st[cfg->phy_idx].rank_st[cfg->rank_idx].ddrtr_data.write;

	if (cfg->phy[cfg->phy_idx].dmc_num == 1)
		ddrtr_memcpy(dest, training, sizeof(struct training_data));
	else {
		/* dmc[0] + dmc[1] */
		offset = cfg->dmc_idx << 4;
		for (i = 0; i < GET_BYTE_NUM(cfg) << 3; i++) {
			dest->ddr_bit_result[i + offset] = training->ddr_bit_result[i + offset];
			dest->ddr_bit_best[i + offset]   = training->ddr_bit_best[i + offset];
		}
		dest->ddr_win_sum  += training->ddr_win_sum;
	}
}

/* Save lpca training data */
void ddr_lpca_data_save(struct ca_data_st *data)
{

#if 0
	unsigned int index;
	struct ddr_training_result_st *result_st
		= (struct ddr_training_result_st *)ddrtr_result;
	struct ddr_training_data_st *tr_data;

	for (index = 0; index < DDR_SUPPORT_PHY_MAX; index++) {
		if (result_st->ddrtr_data[index].base_phy == data->base_phy)
			break;
	}

	tr_data = &result_st->ddrtr_data[index];

	for (index = 0; index < DDR_PHY_CA_MAX; index++)
		tr_data->ca_addr[index] = (data->left[index]
			<< DDR_DATAEYE_RESULT_BIT) | data->right[index];
#endif

}

/* Get DDRT test addrress */
unsigned int ddr_ddrt_get_test_addr(void)
{
	if (ddr_training_addr_start <= DDRT_CFG_TEST_ADDR_CMD
	&&	ddr_training_addr_end >= DDRT_CFG_TEST_ADDR_CMD) {
		return DDRT_CFG_TEST_ADDR_CMD;
	} else {
		DDR_ERROR("DDRT test address[%x] out of range[%x, %x]",
			  DDRT_CFG_TEST_ADDR_CMD,
			  ddr_training_addr_start,
			  ddr_training_addr_end);
		return ddr_training_addr_start;
	}
}

/* Nothing to do in DDR command */
void ddr_training_suc(void) { return; }

/* Nothing to do in DDR command */
void ddr_training_start(void) { return; }

static void dump_result(struct ddr_training_data_st *ddrtr_data)
{
	unsigned int i;
	unsigned int base_phy = ddrtr_data->base_phy;
	unsigned int byte_num = ddrtr_data->byte_num;
	unsigned int rank = ddrtr_data->rank_idx;
	unsigned int ACPHYCTL7;

	/* Static register have to read two times to get the right value. */
	ACPHYCTL7 = ddr_read(base_phy + DDR_PHY_ACPHYCTL7);
	ACPHYCTL7 = ddr_read(base_phy + DDR_PHY_ACPHYCTL7);

	for (i = 0; i < ddrtr_data->byte_num << 3; i++) {
		DDR_INFO("Byte[%x] Write[%x][%x] Read[%x][%x]",
			 i, ddrtr_data->write.ddr_bit_result[i], ddrtr_data->write.ddr_bit_best[i],
			 ddrtr_data->read.ddr_bit_result[i], ddrtr_data->read.ddr_bit_best[i]);
	}

	for (i = 0; i < DDR_PHY_CA_MAX; i++) {
		if (ddrtr_data->ca_addr[i] != 0)
			DDR_INFO("CA[%x] Range[%x]", i, ddrtr_data->ca_addr[i]);
	}

	/* WDQS */
	for (i = 0; i < byte_num; i++) {
		DDR_INFO("[%x = %x] WDQS Byte(%x) ",
			 base_phy + DDR_PHY_DXWDQSDLY(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXWDQSDLY(rank, i)), i);
	}

	/* WDQ Phase */
	for (i = 0; i < byte_num; i++) {
		DDR_INFO("[%x = %x] WDQ Phase Byte(%x)",
			 base_phy + DDR_PHY_DXNWDQDLY(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNWDQDLY(rank, i)), i);
	}

	/* WDQ BDL */
	for (i = 0; i < byte_num; i++) {
		/* DQ0-DQ3 */
		DDR_INFO("[%x = %x] WDQ BDL DQ(%x-%x)",
			 base_phy + DDR_PHY_DXNWDQNBDL0(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNWDQNBDL0(rank, i)),
			 (i << 3), ((i << 3) + 3));

		/* DQ4-DQ7 */
		DDR_INFO("[%x = %x] WDQ BDL DQ(%x-%x)",
			 base_phy + DDR_PHY_DXNWDQNBDL1(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNWDQNBDL1(rank, i)),
			 ((i << 3) + 4), ((i << 3) + 7));
	}

	/* WDM */
	for (i = 0; i < byte_num; i++) {
		DDR_INFO("[%x = %x] WDM Byte(%x)",
			 base_phy + DDR_PHY_DXNWDQNBDL2(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNWDQNBDL2(rank, i)), i);
	}

	/* Write DO/DOS OE */
	for (i = 0; i < byte_num; i++) {
		DDR_INFO("[%x = %x] Write DQ/DQS OE Byte(%x)",
			 base_phy + DDR_PHY_DXNOEBDL(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNOEBDL(rank, i)), i);
	}

	/* RDQS */
	for (i = 0; i < byte_num; i++) {
		DDR_INFO("[%x = %x] RDQS Byte(%x)",
			 base_phy + DDR_PHY_DXNRDQSDLY(i),
			 ddr_read(base_phy + DDR_PHY_DXNRDQSDLY(i)), i);
	}

	/* RDQ BDL */
	for (i = 0; i < byte_num; i++) {
		/* DQ0-DQ3 */
		DDR_INFO("[%x = %x] RDQ BDL DQ(%x-%x)",
			 base_phy + DDR_PHY_DXNRDQNBDL0(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNRDQNBDL0(rank, i)),
			 (i << 3), ((i << 3) + 3));

		/* DQ4-DQ7 */
		DDR_INFO("[%x = %x] RDQ BDL DQ(%x-%x)",
			 base_phy + DDR_PHY_DXNRDQNBDL1(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNRDQNBDL1(rank, i)),
			 ((i << 3) + 4), ((i << 3) + 7));
	}

	/* Gate */
	for (i = 0; i < byte_num; i++) {
		DDR_INFO("[%x = %x] Gate Byte(%x)",
			 base_phy + DDR_PHY_DXNRDQSGDLY(rank, i),
			 ddr_read(base_phy + DDR_PHY_DXNRDQSGDLY(rank, i)), i);
	}

	DDR_INFO("[%x = %x] CS",
		 base_phy + DDR_PHY_ACCMDBDL2,
		 ddr_read(base_phy + DDR_PHY_ACCMDBDL2));

	DDR_INFO("[%x = %x] CLK",
		 base_phy + DDR_PHY_ACPHYCTL7, ACPHYCTL7);

	DDR_PHY_SWITCH_RANK(base_phy, rank);

	/* HOST Vref */
	DDR_PHY_VREF_HOST_DISPLAY_CMD(base_phy, rank, byte_num);

	/* DRAM Vref */
	DDR_PHY_VREF_DRAM_DISPLAY_CMD(base_phy, byte_num);

	/* Addr Phase */
	DDR_PHY_ADDRPH_DISPLAY_CMD(base_phy);

	/* Addr BDL */
	DDR_PHY_ADDRBDL_DISPLAY_CMD(base_phy);

	/* DCC */
	DDR_PHY_DCC_DISPLAY_CMD(base_phy);
}

static void dump_result_by_rank(struct ddr_training_result_st *ddrtr_result,
				unsigned int phy_index, unsigned int rank_index)
{
	unsigned int mask = 1 << phy_index; /* DDR_BYPASS_PHY0_MASK DDR_BYPASS_PHY1_MASK */
	struct rank_data_st *rank_st = &ddrtr_result->phy_st[phy_index].rank_st[rank_index];

	if (rank_st->item & mask)
		return;

	DDR_INFO("PHY[%x] RANK[%x]:", phy_index, rank_index);
	dump_result(&rank_st->ddrtr_data);
}

static void dump_result_by_phy(struct ddr_training_result_st *ddrtr_result,
			       unsigned int phy_index)
{
	int i;
	struct phy_data_st *phy_st = &ddrtr_result->phy_st[phy_index];

	for (i = 0; i < phy_st->rank_num; i++) {
		dump_result_by_rank(ddrtr_result, phy_index, i);
	}
}

/* Display ddr training result before return to DDR */
static void dump_result_all(struct ddr_training_result_st *ddrtr_result)
{
	int i;
	for (i = 0; i < ddrtr_result->phy_num; i++) {
		dump_result_by_phy(ddrtr_result, i);
	}
}

int ddr_training_cmd_func(struct ddr_cfg_st *cfg)
{
	int result = 0;
	struct ddr_cmd_st *cmd_st = (struct ddr_cmd_st *)cfg->cmd_st;
	unsigned int item = cfg->cur_item;

	DDR_DEBUG("DDR training cmd[%x]", cmd_st->cmd);

	switch (cmd_st->cmd) {
	case DDR_TRAINING_CMD_SW:
		/* todo */
		result = ddr_dataeye_training_func(cfg);
		result += ddr_vref_training_func(cfg);
		break;
	case DDR_TRAINING_CMD_DATAEYE:
		result = ddr_dataeye_training_func(cfg);
		break;
	case DDR_TRAINING_CMD_HW:
		result = ddr_hw_training_if();
		break;
	case DDR_TRAINING_CMD_MPR:
		result = ddr_mpr_training_func(cfg);
		break;
	case DDR_TRAINING_CMD_WL:
		result = ddr_wl_func(cfg);
		break;
	case DDR_TRAINING_CMD_GATE:
		result = ddr_gating_func(cfg);
		break;
	case DDR_TRAINING_CMD_VREF:
		result = ddr_vref_training_func(cfg);
		break;
	case DDR_TRAINING_CMD_AC:
		result = ddr_ac_training_func(cfg);
		break;
	case DDR_TRAINING_CMD_LPCA:
		result = ddr_lpca_training_func(cfg);
		break;
	case DDR_TRAINING_CMD_SW_NO_WL:
		/* wl bypass */
		ddr_write(item | DDR_BYPASS_WL_MASK,
			  DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG);
		result = ddr_dataeye_training_func(cfg);
		result += ddr_vref_training_func(cfg);
		/* restore cfg */
		ddr_write(item,
			  DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG);
		break;
	case DDR_TRAINING_CMD_CONSOLE:
		result = ddr_training_console_if((void *)&ddrt_result_sram);
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/* DDR training command entry. Call by cmd_ddr_handle(). */
struct ddr_training_result_st *ddr_training_cmd_entry(
		struct ddr_cmd_st *cmd_st)
{
	int result = 0;

	struct ddr_cfg_st ddr_cfg;
	struct ddr_cfg_st *cfg = &ddr_cfg;
	struct ddr_cmd_st cmd_in_sram;

	ddr_training_addr_start = cmd_st->start;
	ddr_training_addr_end   = cmd_st->start + cmd_st->length;
	ddr_print_level         = cmd_st->level;

	DDR_INFO("DDR Training Version: "DDR_TRAINING_VER);
	DDR_DEBUG("DDR training command entry. Sysctl[%x = %x]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG),
		ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG));

#ifdef SYSCTRL_DDR_TRAINING_CFG_SEC
	DDR_DEBUG("Rank1 Sysctl[%x = %x]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC),
		ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC));
#endif

	ddr_training_cfg_init(cfg);
	ddrtr_memcpy(&cmd_in_sram, cmd_st, sizeof(struct ddr_cmd_st));
	cfg->cmd_st = (void *)&cmd_in_sram;
	cfg->res_st = (void *)&ddrt_result_sram;

	ddr_training_result_init(cfg, &ddrt_result_sram);

	if (cmd_st->cmd == DDR_TRAINING_CMD_HW)
		result = ddr_hw_training(cfg);
	else if (cmd_st->cmd == DDR_TRAINING_CMD_PCODE)
		result = ddr_pcode_training(cfg);
	else if (cmd_st->cmd == DDR_TRAINING_CMD_DCC)
		result = ddr_dcc_training_func(cfg);
	else if (cmd_st->cmd == DDR_TRAINING_CMD_CONSOLE)
		result = ddr_training_console_if((void *)&ddrt_result_sram);
	else
		result = ddr_training_all(cfg);

	dump_result_all(&ddrt_result_sram);

	if (!result) {
		return &ddrt_result_sram;
	} else {
		DDR_DEBUG("DDR training result[%x]", result);
		return 0;
	}
}
