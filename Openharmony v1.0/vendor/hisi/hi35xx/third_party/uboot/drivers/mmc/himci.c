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

#include <config.h>
#include <common.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <cpu_func.h>
//#include <asm/errno.h>
#include <asm/io.h>
#include <himci_reg.h>

#include "mmc_private.h"
#include "himci.h"

#define MMC_CS_ERROR_MASK   0xFDFFA080

/*************************************************************************/
#ifdef CONFIG_TARGET_HI3516CV500
	#include "himci_hi3516cv500.c"
#endif
#if (defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300)
	#include "himci_hi3516dv300.c"
#endif
#ifdef CONFIG_TARGET_HI3556V200
	#include "himci_hi3556v200.c"
#endif
#ifdef CONFIG_TARGET_HI3559V200
	#include "himci_hi3559v200.c"
#endif
#ifdef CONFIG_TARGET_HI3562V100
	#include "himci_hi3559v200.c"
#endif
#ifdef CONFIG_TARGET_HI3566V100
	#include "himci_hi3559v200.c"
#endif
/*************************************************************************/

//#define TUNING_PROC_DEBUG

#if HI_MCI_DEBUG
int debug_type = HIMCI_DEBUG_TYPE;

char *get_debug_type_string(int type)
{
	if (type & HIMCI_DEBUG_TYPE_REG)
		return "REG";
	else if (type & HIMCI_DEBUG_TYPE_FUN)
		return "FUN";
	else if (type & HIMCI_DEBUG_TYPE_CMD)
		return "CMD";
	else if (type & HIMCI_DEBUG_TYPE_INFO)
		return "INFO";
	else if (type & HIMCI_DEBUG_TYPE_ERR)
		return "ERR";
	else
		return "UNKNOWN";
}
#endif

static unsigned int retry_count = MAX_RETRY_COUNT;

static struct himci_dma_des hi_dma_des[MAX_DMA_DES]
	__attribute__ ((aligned(512)));

/* reset MMC host controler */
static void hi_mci_sys_reset(struct himci_host *host)
{
	unsigned int tmp_reg;
	unsigned int time_out;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg |= BMOD_SWR;
	himci_writel(tmp_reg, host->base + MCI_BMOD);

	time_out = 1000;
	do {
		tmp_reg = himci_readl(host->base + MCI_BMOD);
		udelay(10);
	} while ((tmp_reg & BMOD_SWR) && time_out--);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg |= BURST_16 | BURST_INCR;
	himci_writel(tmp_reg, host->base + MCI_BMOD);

	tmp_reg = himci_readl(host->base + MCI_CTRL);
	tmp_reg |=  CTRL_RESET | FIFO_RESET | DMA_RESET;
	himci_writel(tmp_reg, host->base + MCI_CTRL);
}

static void hi_mci_ctrl_power(struct himci_host *host, int flag)
{
	int reg_value = 0;
	HIMCI_DEBUG_FUN("Function Call: flag %d", flag);
	HIMCI_ASSERT(host);

	if (flag)
		reg_value = 1 << host->port;
	else
		reg_value = 0;

	himci_writel(reg_value, host->base + MCI_PWREN);
}

static int tuning_reset_flag = 0;

static int hi_mci_wait_cmd(struct himci_host *host)
{
	unsigned int tmp_reg, wait_retry_count = 0;
	unsigned int retry_count_cmd = 500;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	do {
		tmp_reg = himci_readl(host->base + MCI_CMD);
		if ((tmp_reg & START_CMD) == 0)
			return 0;
		udelay(1);
		wait_retry_count++;
	} while (wait_retry_count < retry_count_cmd);
	if (host->is_tuning)
		tuning_reset_flag = 1;
	HIMCI_DEBUG_INFO("CMD send timeout");

	return -1;
}

static void hi_mci_control_cclk(struct himci_host *host, unsigned int flag)
{
	unsigned int reg;
	cmd_arg_s cmd_reg;

	HIMCI_DEBUG_FUN("Function Call: flag %d", flag);
	HIMCI_ASSERT(host);

	reg = himci_readl(host->base + MCI_CLKENA);
	if (flag == ENABLE)
		reg |= CCLK_ENABLE << host->port;
	else
		reg &= ~(CCLK_ENABLE << host->port);
	himci_writel(reg, host->base + MCI_CLKENA);

	cmd_reg.cmd_arg = himci_readl(host->base + MCI_CMD);
	cmd_reg.cmd_arg &= ~MCI_CMD_MASK;
	cmd_reg.bits.start_cmd = 1;
	cmd_reg.bits.card_number = host->port;
	cmd_reg.bits.update_clk_reg_only = 1;
	himci_writel(cmd_reg.cmd_arg, host->base + MCI_CMD);

	if (hi_mci_wait_cmd(host) != 0)
		HIMCI_DEBUG_ERR("Disable or enable CLK is timeout");

}

static void hi_mci_set_cclk(struct himci_host *host, unsigned int cclk)
{
	unsigned int reg_value;
	cmd_arg_s cmd_reg;

	HIMCI_DEBUG_FUN("Function Call: cclk %d", cclk);
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cclk);

	/*set card clk divider value, clk_divider = Fmmcclk/(Fmmc_cclk * 2) */
	reg_value = 0;
	if (cclk < MMC_CLK) {
		reg_value = MMC_CLK / (cclk * 2);
		if (MMC_CLK % (cclk * 2))
			reg_value++;
		if (reg_value > 0xFF)
			reg_value = 0xFF;
	}
	himci_writel(reg_value, host->base + MCI_CLKDIV);

	cmd_reg.cmd_arg = himci_readl(host->base + MCI_CMD);
	cmd_reg.cmd_arg &= ~MCI_CMD_MASK;
	cmd_reg.bits.start_cmd = 1;
	cmd_reg.bits.card_number = host->port;
	cmd_reg.bits.update_clk_reg_only = 1;
	himci_writel(cmd_reg.cmd_arg, host->base + MCI_CMD);

	if (hi_mci_wait_cmd(host) != 0)
		HIMCI_DEBUG_ERR("Set card CLK divider is failed");
}
/**********************************************
 *1: card off
 *0: card on
 ***********************************************/
static unsigned int hi_mci_sys_card_detect(struct himci_host *host)
{
		unsigned int card_status;

		card_status = readl((uintptr_t)(host->base + MCI_CDETECT));
		card_status &= (HIMCI_CARD0 << host->port);

		return card_status >> host->port;
}

static void hi_mci_init_card(struct himci_host *host)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	hi_mci_sys_reset(host);

	/* card reset */
	himci_writel(~(1<<host->port), host->base + MCI_RESET_N);
	__udelay(CONFIG_MMC_RESET_LOW_TIMEOUT);

	/* card power off and power on */
	hi_mci_ctrl_power(host, POWER_OFF);
	__udelay(CONFIG_MMC_POWER_OFF_TIMEOUT * 1000);
	hi_mci_ctrl_power(host, POWER_ON);
	__udelay(CONFIG_MMC_POWER_ON_TIMEROUT * 1000);

	/* card reset cancel */
	himci_writel(1<<host->port, host->base + MCI_RESET_N);
	__udelay(CONFIG_MMC_RESET_HIGH_TIMEROUT);

	/* set drv/smpl phase shift */
	tmp_reg = himci_readl(host->base + MCI_UHS_REG_EXT);
	tmp_reg &= ~(DRV_PHASE_MASK | SMPL_PHASE_MASK);
	tmp_reg |= DRV_PHASE_SHIFT | SMPL_PHASE_SHIFT;
	himci_writel(tmp_reg, host->base + MCI_UHS_REG_EXT);

	/* clear MMC host intr */
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

	/*read write threshold*/
	himci_writel(RW_THRESHOLD_SIZE, host->base + MMC_CARDTHRCTL);

	/* MASK MMC host intr */
	tmp_reg = himci_readl(host->base + MCI_INTMASK);
	tmp_reg &= ~ALL_INT_MASK;
	himci_writel(tmp_reg, host->base + MCI_INTMASK);

	/* enable inner DMA mode and close intr of MMC host controler */
	tmp_reg = himci_readl(host->base + MCI_CTRL);
	tmp_reg &= ~INTR_EN;
	tmp_reg |= USE_INTERNAL_DMA;
	himci_writel(tmp_reg, host->base + MCI_CTRL);

	/* enable dma intr */
	tmp_reg = TI | RI | NI;
	himci_writel(tmp_reg, host->base + MCI_IDINTEN);

	/* set timeout param */
	himci_writel(DATA_TIMEOUT | RESPONSE_TIMEOUT, host->base + MCI_TIMEOUT);

	/* set FIFO param */
	himci_writel(BURST_SIZE | RX_WMARK | TX_WMARK, host->base + MCI_FIFOTH);

	/* set dto fix bypass */
	tmp_reg = himci_readl(host->base + MCI_GPIO);
	tmp_reg |= DTO_FIX_BYPASS;
	himci_writel(tmp_reg, host->base + MCI_GPIO);
}

static void hi_mci_idma_start(struct himci_host *host, struct mmc_data *data)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(data);

	himci_writel((unsigned long)(uintptr_t)host->dma_des, host->base + MCI_DBADDR);
	HIMCI_DEBUG_INFO("host->dma_des is 0x%x", (unsigned int)host->dma_des);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg |= BMOD_DMA_EN;
	himci_writel(tmp_reg, host->base + MCI_BMOD);
}

static void hi_mci_idma_stop(struct himci_host *host)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	tmp_reg = himci_readl(host->base + MCI_BMOD);
	tmp_reg &= ~BMOD_DMA_EN;
	himci_writel(tmp_reg, host->base + MCI_BMOD);
	himci_writel(0, host->base + MCI_BYTCNT);
	himci_writel(0, host->base + MCI_BLKSIZ);
	himci_writel(0, host->base + MCI_DBADDR);
}

static void hi_mci_idma_reset(struct himci_host *host)
{
	unsigned int regval;

	regval = himci_readl(host->base + MCI_BMOD);
	regval |= BMOD_SWR;
	himci_writel(regval, host->base + MCI_BMOD);

	regval = himci_readl(host->base + MCI_CTRL);
	regval |= CTRL_RESET | FIFO_RESET | DMA_RESET;
	himci_writel(regval, host->base + MCI_CTRL);

	udelay(1);
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
}

static int hi_mci_setup_data(struct himci_host *host, struct mmc_data *data)
{
	struct himci_dma_des *des = host->dma_des;
	unsigned long des_cnt;
	unsigned long data_size = data->blocks * data->blocksize;
	unsigned long blk_size = data_size;
	unsigned long src = (uintptr_t)data->src;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(data);

	if (((data_size + 0x1000 - 1) / 0x1000) > MAX_DMA_DES) {
		HIMCI_ERROR("Data size outside the limit of DMA des, "
				"data size: 0x%08lx, limit of DMA des: 0x%08x",
				data_size, 0x1000 * MAX_DMA_DES);
		return -1;
	}

	des_cnt = 0;
	while (data_size) {
		des[des_cnt].idmac_des_ctrl = DMA_DES_OWN | DMA_DES_NEXT_DES;
		des[des_cnt].idmac_des_buf_addr = src;
		des[des_cnt].idmac_des_next_addr =
			(uintptr_t)(des + des_cnt + 1);

		if (data_size >= 0x1000) {
			des[des_cnt].idmac_des_buf_size = 0x1000;
			data_size -= 0x1000;
			src += 0x1000;
		} else {
			des[des_cnt].idmac_des_buf_size = data_size;
			data_size = 0;
		}

		HIMCI_DEBUG_INFO("des[%ld] vaddr is 0x%X", des_cnt,
				 (unsigned int)&des[des_cnt]);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_ctrl is 0x%X", des_cnt,
				 (unsigned int)des[des_cnt].idmac_des_ctrl);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_buf_size is 0x%X",
				 des_cnt,
				 (unsigned int)des[des_cnt].idmac_des_buf_size);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_buf_addr 0x%X", des_cnt,
				 (unsigned int)des[des_cnt].idmac_des_buf_addr);
		HIMCI_DEBUG_INFO("des[%ld].idmac_des_next_addr is 0x%X",
			des_cnt,
			(unsigned int)des[des_cnt].idmac_des_next_addr);

		des_cnt++;
	}

	des[0].idmac_des_ctrl |= DMA_DES_FIRST_DES;
	des[des_cnt - 1].idmac_des_ctrl |= DMA_DES_LAST_DES;
	des[des_cnt - 1].idmac_des_next_addr = 0;

	blk_size = ALIGN(blk_size, CONFIG_SYS_CACHELINE_SIZE);
	des_cnt = ALIGN(des_cnt, CONFIG_SYS_CACHELINE_SIZE);
	if (data->flags != MMC_DATA_READ){
		flush_cache((uintptr_t)data->src, blk_size);
	}
	else
		invalidate_dcache_range((uintptr_t)data->dest,(uintptr_t)data->dest + blk_size);

	flush_cache((uintptr_t)host->dma_des, sizeof(struct himci_dma_des)*(unsigned long)des_cnt);

	return 0;
}

static int hi_mci_exec_cmd(struct himci_host *host, struct mmc_cmd *cmd,
			   struct mmc_data *data)
{
	volatile cmd_arg_s cmd_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cmd);

	himci_writel(cmd->cmdarg, host->base + MCI_CMDARG);

	cmd_reg.cmd_arg = himci_readl(host->base + MCI_CMD);
	cmd_reg.cmd_arg &= ~MCI_CMD_MASK;
	if (data) {
		cmd_reg.bits.data_transfer_expected = 1;
		if (data->flags & (MMC_DATA_WRITE | MMC_DATA_READ))
			cmd_reg.bits.transfer_mode = 0;

		if (data->flags & MMC_DATA_WRITE)
			cmd_reg.bits.read_write = 1;
		else if (data->flags & MMC_DATA_READ)
			cmd_reg.bits.read_write = 0;
	} else {
		cmd_reg.bits.data_transfer_expected = 0;
		cmd_reg.bits.transfer_mode = 0;
		cmd_reg.bits.read_write = 0;
	}

	cmd_reg.bits.wait_prvdata_complete = 1;

	cmd_reg.bits.send_auto_stop = 0;
	if (!(host->is_tuning))
		cmd_reg.bits.send_auto_stop = 1;

	if (cmd->cmdidx == MMC_CMD_STOP_TRANSMISSION) {
		cmd_reg.bits.stop_abort_cmd = 1;
		cmd_reg.bits.wait_prvdata_complete = 0;
	} else {
		cmd_reg.bits.stop_abort_cmd = 0;
		cmd_reg.bits.wait_prvdata_complete = 1;
	}

	switch (cmd->resp_type) {
	case MMC_RSP_NONE:
		cmd_reg.bits.response_expect = 0;
		cmd_reg.bits.response_length = 0;
		cmd_reg.bits.check_response_crc = 0;
		break;
	case MMC_RSP_R1:
	case MMC_RSP_R1b:
		cmd_reg.bits.response_expect = 1;
		cmd_reg.bits.response_length = 0;
		cmd_reg.bits.check_response_crc = 1;
		break;
	case MMC_RSP_R2:
		cmd_reg.bits.response_expect = 1;
		cmd_reg.bits.response_length = 1;
		cmd_reg.bits.check_response_crc = 1;
		break;
	case MMC_RSP_R3:
		cmd_reg.bits.response_expect = 1;
		cmd_reg.bits.response_length = 0;
		cmd_reg.bits.check_response_crc = 0;
		break;
	default:
		HIMCI_ERROR("unhandled response type %02x", cmd->resp_type);
		return -1;
	}

	HIMCI_DEBUG_INFO("Send cmd of card is CMD %d", cmd->cmdidx);

	if (cmd->cmdidx == MMC_CMD_GO_IDLE_STATE)
		cmd_reg.bits.send_initialization = 1;
	else
		cmd_reg.bits.send_initialization = 0;

	cmd_reg.bits.card_number = host->port;
	cmd_reg.bits.cmd_index = cmd->cmdidx;
	cmd_reg.bits.send_auto_stop = 0;
	cmd_reg.bits.start_cmd = 1;
	cmd_reg.bits.update_clk_reg_only = 0;
	himci_writel(cmd_reg.cmd_arg, host->base + MCI_CMD);

	if (hi_mci_wait_cmd(host) != 0) {
		HIMCI_DEBUG_ERR("Send card cmd is failed");
		return -1;
	}
	return 0;
}

static int hi_mci_cmd_done(struct himci_host *host, unsigned int stat)
{
	struct mmc_cmd *cmd = host->cmd;

	HIMCI_DEBUG_FUN("Function Call: stat 0x%08x", stat);
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cmd);

	host->cmd = NULL;

	if (cmd->resp_type & MMC_RSP_PRESENT) {
		if (cmd->resp_type & MMC_RSP_136) {
			cmd->response[0] = himci_readl(host->base + MCI_RESP3);
			cmd->response[1] = himci_readl(host->base + MCI_RESP2);
			cmd->response[2] = himci_readl(host->base + MCI_RESP1);
			cmd->response[3] = himci_readl(host->base + MCI_RESP0);
			HIMCI_DEBUG_INFO("CMD Response of card is "
					"%08x %08x %08x %08x",
					 cmd->response[0], cmd->response[1],
					 cmd->response[2], cmd->response[3]);
		} else {
			cmd->response[0] = himci_readl(host->base + MCI_RESP0);
			HIMCI_DEBUG_INFO("CMD Response of card is %08x",
					 cmd->response[0]);
		}
		if (host->mmc->version && !IS_SD(host->mmc)) {
			if ((cmd->resp_type == MMC_RSP_R1)
			    || (cmd->resp_type == MMC_RSP_R1b)) {
				if (cmd->response[0] & MMC_CS_ERROR_MASK) {
					HIMCI_DEBUG_ERR("Card status"
							" stat = 0x%x"
							" is card error!",
							cmd->response[0]);
					return -1;
				}
			}
		}
	}

	if (stat & RTO_INT_STATUS) {
		HIMCI_DEBUG_ERR("CMD status stat = 0x%x is timeout error!",
				stat);
		return -ETIMEDOUT;
	} else if (stat & (RCRC_INT_STATUS | RE_INT_STATUS)) {
		HIMCI_DEBUG_ERR("CMD status stat = 0x%x is response error!",
				stat);
		return -1;
	}
	return 0;
}

static void hi_mci_data_done(struct himci_host *host, unsigned int stat)
{
	HIMCI_DEBUG_FUN("Function Call: stat 0x%08x", stat);
	HIMCI_ASSERT(host);

	if (stat & (HTO_INT_STATUS | DRTO_INT_STATUS)) {
		HIMCI_DEBUG_ERR("Data status stat = 0x%x is timeout error!",
				stat);
	} else if (stat & (EBE_INT_STATUS | SBE_INT_STATUS | FRUN_INT_STATUS
			   | DCRC_INT_STATUS)) {
		HIMCI_DEBUG_ERR("Data status stat = 0x%x is data error!", stat);
	}
}

static int hi_mci_wait_cmd_complete(struct himci_host *host)
{
	unsigned int wait_retry_count = 0;
	unsigned int reg_data = 0;
	int ret = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	do {
		reg_data = himci_readl(host->base + MCI_RINTSTS);
		if (reg_data & CD_INT_STATUS) {
			himci_writel(CD_INT_STATUS | RTO_INT_STATUS
					| RCRC_INT_STATUS | RE_INT_STATUS,
					host->base + MCI_RINTSTS);
			ret = hi_mci_cmd_done(host, reg_data);
			return ret;
		}
		udelay(100);
		wait_retry_count++;
	} while (wait_retry_count < retry_count);

	HIMCI_DEBUG_ERR("Wait cmd complete error! irq status is 0x%x",
			reg_data);

	return -1;
}

static int hi_mci_wait_data_complete(struct himci_host *host)
{
	unsigned int wait_retry_count = 0;
	unsigned int reg_data = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	do {
		reg_data = himci_readl(host->base + MCI_RINTSTS);
		if (reg_data & DTO_INT_STATUS) {
			hi_mci_idma_stop(host);
			hi_mci_data_done(host, reg_data);
			return 0;
		}

		if (host->is_tuning){
			if (reg_data & (HTO_INT_STATUS | DRTO_INT_STATUS |
				EBE_INT_STATUS | SBE_INT_STATUS |
				FRUN_INT_STATUS | DCRC_INT_STATUS)){
				hi_mci_idma_stop(host);
				hi_mci_data_done(host, reg_data);
				return -1;
			}
		}
		udelay(100);
		wait_retry_count++;
	} while (wait_retry_count < retry_count);

	HIMCI_DEBUG_ERR("Wait data complete error! irq status is 0x%x",
			reg_data);

	return -1;
}

static int hi_mci_wait_card_complete(struct himci_host *host)
{
	unsigned int wait_retry_count = 0;
	unsigned int reg_data = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(host);

	do {
		reg_data = himci_readl(host->base + MCI_STATUS);
		if (!(reg_data & DATA_BUSY))
			return 0;
		udelay(100);
		wait_retry_count++;
	} while (wait_retry_count < retry_count);

	HIMCI_DEBUG_ERR("Wait card complete error! status is 0x%x", reg_data);

	return -1;
}

static int hi_mci_request(struct mmc *mmc, struct mmc_cmd *cmd,
			  struct mmc_data *data)
{
	struct himci_host *host = mmc->priv;
	unsigned int blk_size;
	unsigned int tmp_reg, fifo_count = 0;
	int ret = 0;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(mmc);
	HIMCI_ASSERT(host);
	HIMCI_ASSERT(cmd);

	host->cmd = cmd;

	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);

	/* prepare data */
	if (data) {
		ret = hi_mci_setup_data(host, data);
		if (ret) {
			HIMCI_ERROR("Data setup is error!");
			goto request_end;
		}

		blk_size = data->blocks * data->blocksize;

		himci_writel(blk_size, host->base + MCI_BYTCNT);
		himci_writel(data->blocksize, host->base + MCI_BLKSIZ);

		tmp_reg = himci_readl(host->base + MCI_CTRL);
		tmp_reg |= FIFO_RESET;
		himci_writel(tmp_reg, host->base + MCI_CTRL);

		do {
			tmp_reg = himci_readl(host->base + MCI_CTRL);
			if (fifo_count > retry_count) {
				HIMCI_ERROR("FIFO reset error!");
				break;
			}
			fifo_count++;
		} while (tmp_reg & FIFO_RESET);

		/* start DMA */
		hi_mci_idma_start(host, data);
	} else {
		himci_writel(0, host->base + MCI_BYTCNT);
		himci_writel(0, host->base + MCI_BLKSIZ);
	}

	/* send command */
	ret = hi_mci_exec_cmd(host, cmd, data);
	if (ret) {
		HIMCI_ERROR("CMD execute is error!");
		goto request_end;
	}

	/* wait command send complete */
	ret = hi_mci_wait_cmd_complete(host);
	if (ret)
		goto request_end;

	/* start data transfer */
	if (data) {
		/* wait data transfer complete */
		ret = hi_mci_wait_data_complete(host);
		if (ret)
			goto request_end;

		/* wait card complete */
		ret = hi_mci_wait_card_complete(host);
		if (ret)
			goto request_end;
	}

	if (cmd->resp_type & MMC_RSP_BUSY) {
		/* wait card complete */
		ret = hi_mci_wait_card_complete(host);
		if (ret)
			goto request_end;
	}
request_end:
	/* clear MMC host intr */
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
	return ret;
}

static int hi_mci_set_ios(struct mmc *mmc)
{
	struct himci_host *host = mmc->priv;
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(mmc);
	HIMCI_ASSERT(host);

	if (mmc->clock) {
		hi_mci_control_cclk(host, DISABLE);
		hi_mci_set_cclk(host, mmc->clock);
		hi_mci_control_cclk(host, ENABLE);
	} else {
		hi_mci_control_cclk(host, DISABLE);
	}

	/* set bus_width */
	HIMCI_DEBUG_INFO("ios->bus_width = %d", mmc->bus_width);

	tmp_reg = himci_readl(host->base + MCI_CTYPE);
	tmp_reg &= ~CARD_WIDTH_MASK;

	if (mmc->bus_width == 8)
		tmp_reg |= (CARD_WIDTH_8BIT<<host->port);
	else if (mmc->bus_width == 4)
		tmp_reg |= (CARD_WIDTH_4BIT<<host->port);
	else
		tmp_reg |= (CARD_WIDTH_1BIT<<host->port);

	himci_writel(tmp_reg, host->base + MCI_CTYPE);

	hi_mci_set_drv_cap(mmc, 0);
	hi_mci_set_default_phase(mmc);
	
	return 0;
}

static int hi_mci_init(struct mmc *mmc)
{
	struct himci_host *host = mmc->priv;

	HIMCI_DEBUG_FUN("Function Call");

	hi_mci_init_card(host);

	return 0;
}

static int hi_mci_card_busy(struct mmc *mmc)
{
	struct himci_host *host = mmc->priv;
	unsigned int regval;

	HIMCI_DEBUG_FUN("Function Call");
	HIMCI_ASSERT(mmc);
	HIMCI_ASSERT(host);

	regval = himci_readl(host->base + MCI_STATUS);
	regval &= DATA_BUSY;

	return regval;
}

static void hi_mci_edge_tuning_enable(struct himci_host *host)
{
	unsigned int val;

	himci_writel(0x80001, 0x1201014c);

	val = himci_readl(host->base + MCI_TUNING_CTRL);
	val |= HW_TUNING_EN;
	himci_writel(val, host->base + MCI_TUNING_CTRL);
}

static void hi_mci_edge_tuning_disable(struct himci_host *host)
{
	unsigned int val;

	val = himci_readl(0x1201014c);
	val |= (1 << 16);
	himci_writel(val, 0x1201014c);

	val = himci_readl(host->base + MCI_TUNING_CTRL);
	val &= ~HW_TUNING_EN;
	himci_writel(val, host->base + MCI_TUNING_CTRL);
}

static void hi_mci_set_sap_phase(struct himci_host *host, unsigned int phase)
{
	unsigned int reg_value;

	reg_value = himci_readl(host->base + MCI_UHS_REG_EXT);
	reg_value &= ~CLK_SMPL_PHS_MASK;
	reg_value |= (phase << CLK_SMPL_PHS_SHIFT);
	himci_writel(reg_value, host->base + MCI_UHS_REG_EXT);
}

static int hi_mci_send_stop(struct mmc * mmc)
{
	struct mmc_cmd cmd = {0};
	int err;

	cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
	cmd.resp_type = MMC_RSP_R1;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	return err;
}

static int hi_mci_send_tuning(struct mmc * mmc, unsigned int opcode)
{
	int err = 0;
	unsigned int status = 1000;
	struct himci_host *host = mmc->priv;
	/* fix a problem that When the I/O voltage is increased to 1.89 V or 1.91V 
	 * at high and low temperatures, the system is suspended during the reboot test.
	 */
	unsigned cmd_count = 1000;

	hi_mci_control_cclk(host, DISABLE);
tuning_retry:
	hi_mci_idma_reset(host);
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
	hi_mci_control_cclk(host, ENABLE);
	if (tuning_reset_flag == 1){
		tuning_reset_flag = 0;
		cmd_count--;
		if (cmd_count == 0){
			printf("BUG_ON:controller reset is failed!!!\n");
			return -EINVAL;
		}
	 	goto tuning_retry;
	}
	err = mmc_send_tuning(mmc, opcode, NULL);
	hi_mci_send_stop(mmc);
	mmc_send_status(mmc ,&status);
	return err;
}

static unsigned int hi_mci_get_sap_dll_taps(void)
{
	unsigned int regval = 0;

	regval = himci_readl(0x12010150);

	return (regval & 0xff);
}

static void hi_mci_set_dll_element(unsigned int element)
{
	unsigned int regval;

	regval = himci_readl(0x1201014c);
	regval &=~(0xFF << 8);
	regval |= (element << 8);
	himci_writel(regval, 0x1201014c);

}

static void hi_mci_tuning_feedback(struct mmc * mmc)
{
	struct himci_host *host = mmc->priv;

	hi_mci_control_cclk(host, DISABLE);
	mdelay(1);
	hi_mci_sys_reset(host);
	mdelay(1);
	himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
	hi_mci_control_cclk(host, ENABLE);
	mdelay(1);
}

/*********************************************
 *********************************************
 EdgeMode A:
 |<---- totalphases(ele) ---->|
 _____________
 ______|||||||||||||||_______
 edge_p2f       edge_f2p
 (endp)         (startp)

 EdgeMode B:
 |<---- totalphases(ele) ---->|
 ________           _________
 ||||||||||_________|||||||||||
 edge_f2p     edge_p2f
 (startp)     (endp)

BestPhase:
if(endp < startp)
endp = endp + totalphases;
Best = ((startp + endp) / 2) % totalphases
 **********************************************
 **********************************************/
static int hi_mci_edgedll_mode_tuning(struct mmc *mmc, unsigned int opcode, int edge_p2f, int edge_f2p)
{
	unsigned int index;
	unsigned int found = 0;
	unsigned int startp =-1, endp = -1;
	unsigned int startp_init = 0, endp_init = 0;
	unsigned int phaseoffset = 0, totalphases = 0;
	unsigned short ele,start_ele, phase_dll_elements;
	unsigned char mdly_tap_flag = 0;
	int prev_err = 0, err = 0;
	struct himci_host *host = mmc->priv;
	unsigned int phase_num = HIMCI_PHASE_SCALE;

	mdly_tap_flag = hi_mci_get_sap_dll_taps();
	phase_dll_elements = mdly_tap_flag / HIMCI_PHASE_SCALE;
	totalphases = phase_dll_elements * phase_num;
	startp_init = edge_f2p * phase_dll_elements;
	endp_init = edge_p2f * phase_dll_elements;
	startp = startp_init;
	endp = endp_init;

	found = 1;
	start_ele = 2;

	/*Note: edgedll tuning must from edge_p2f to edge_f2p*/
	if(edge_f2p >=  edge_p2f) {
		phaseoffset = edge_p2f * phase_dll_elements;
		for (index = edge_p2f; index < edge_f2p; index++) {
			/* set phase shift */
			hi_mci_set_sap_phase(host, index);

			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				hi_mci_set_dll_element(ele);
				err = hi_mci_send_tuning(mmc, opcode);
				if (!err)
					found = 1;

				if (!prev_err && err && (endp == endp_init))
					endp = phaseoffset + ele;

				if (err)
					startp = phaseoffset + ele;

#ifdef TUNING_PROC_DEBUG
				printf("\tphase:%01u ele:%02u st:%03u end:%03u error:%d\n", index, ele, startp, endp, err);
#endif

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
		}
	} else {

		phaseoffset = edge_p2f * phase_dll_elements;
		for (index = edge_p2f ; index < phase_num ; index++) {
			/* set phase shift */
			hi_mci_set_sap_phase(host, index);
			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				hi_mci_set_dll_element(ele);
				err = hi_mci_send_tuning(mmc, opcode);

				if (!err)
					found = 1;

				if (!prev_err && err && (endp == endp_init))
					endp = phaseoffset + ele;

				if (err)
					startp = phaseoffset + ele;

#ifdef TUNING_PROC_DEBUG
				printf("\tphase:%02u ele:%02u st:%03u end:%03u error:%d\n", index, ele, startp, endp, err);
#endif

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
		}

		phaseoffset = 0;
		for (index = 0; index < edge_f2p; index++) {
			/* set phase shift */
			hi_mci_set_sap_phase(host, index);
			for (ele = start_ele; ele <= phase_dll_elements ; ele++) {
				hi_mci_set_dll_element(ele);

				err = hi_mci_send_tuning(mmc, opcode);
				if (!err)
					found = 1;

				if (!prev_err && err && (endp == endp_init))
					endp = phaseoffset + ele;

				if (err)
					startp = phaseoffset + ele;

#ifdef TUNING_PROC_DEBUG
				printf("\tphase:%02u ele:%02u st:%03u end:%03u error:%d\n", index, ele, startp, endp, err);
#endif

				prev_err = err;
				err = 0;
			}
			phaseoffset += phase_dll_elements;
		}
	}

	if (found) {
		printf("scan elemnts: startp:%u endp:%u\n", startp, endp);

		if (endp <= startp)
			endp += totalphases;

		phaseoffset = (( startp + endp ) / 2) % totalphases;
		index = (phaseoffset / phase_dll_elements);
		ele = (phaseoffset % phase_dll_elements);
		ele = ((ele > start_ele)?ele:start_ele);

		hi_mci_set_sap_phase(host, index);
		hi_mci_set_dll_element(ele);

		printf("Tuning SampleClock. mix set phase:[%02u/%02u] ele:[%0ud/%02u]\n",
			index, (phase_num - 1), ele, phase_dll_elements);
		himci_writel(ALL_INT_CLR, host->base + MCI_RINTSTS);
		return 0;
	}
	printf( "No valid phase shift! use default\n");
	return -1;
}

static int hi_mci_execute_mix_mode_tuning(struct mmc * mmc, unsigned int opcode)
{
	struct himci_host *host = mmc->priv;
	unsigned int index, regval;
	unsigned int found = 0,prefound = 0;
	unsigned int edge_p2f, edge_f2p;
	unsigned int edge_num = 0;
	int err;
	unsigned int phase_num = HIMCI_PHASE_SCALE;

	hi_mci_edge_tuning_enable(host);

	edge_p2f = 0;
	edge_f2p = phase_num;

	for (index = 0; index < phase_num; index++) {

		/* set phase shift */
		hi_mci_set_sap_phase(host, index);
		err = hi_mci_send_tuning(mmc, opcode);
		if (!err) {
			regval = himci_readl(host->base + MCI_TUNING_CTRL);
			found = ((regval & FOUND_EDGE) == FOUND_EDGE);
		} else {
			found = 1;
		}

		if (found)
			edge_num++;

		if (prefound && !found)
			edge_f2p = index;
		else if (!prefound && found)
			edge_p2f = index;

#ifdef TUNING_PROC_DEBUG
		printf("\tphase:%02u found:%02u p2f:%u f2p:%u error:%d\n",
			index, found, edge_p2f, edge_f2p, err);
#endif

		if ((edge_p2f != 0) && (edge_f2p != phase_num))
			break;

		prefound = found;
		found = 0;
	}

	if ((edge_p2f == 0) && (edge_f2p == phase_num)) {
		printf("unfound correct edge! check your config is correct!!\n");
		return -1;
	}

	printf("scan edges:%u p2f:%u f2p:%u\n", edge_num, edge_p2f, edge_f2p);

	if (edge_f2p < edge_p2f)
		index = ((edge_f2p + edge_p2f) / 2) % phase_num;
	else
		index = ((edge_f2p + phase_num + edge_p2f) / 2) % phase_num;
	printf("mix set temp-phase %u\n", index);
	hi_mci_set_sap_phase(host, index);
	err = hi_mci_send_tuning(mmc,opcode);

	hi_mci_edge_tuning_disable(host);
	err = hi_mci_edgedll_mode_tuning(mmc, opcode, edge_p2f, edge_f2p);

	return err;
}
static int hi_mci_execute_tuning(struct mmc *mmc, unsigned int opcode)
{
	struct himci_host *host = mmc->priv;
	int err;

	host->is_tuning = 1;
	err = hi_mci_execute_mix_mode_tuning(mmc, opcode);
	hi_mci_tuning_feedback(mmc);
	if (!err)
		err = hi_mci_send_tuning(mmc, opcode);

	host->is_tuning = 0;
	return err;
}

static void himci_shutdown(void)
{
	unsigned long base_addr;
	unsigned int value;

	base_addr = EMMC_REG_BASE;

	value = readl((uintptr_t)(base_addr + MCI_CTRL));
	value |= CTRL_RESET | FIFO_RESET | DMA_RESET;

	writel(value, (uintptr_t)(base_addr + MCI_CTRL));
	writel(POWER_OFF, (uintptr_t)(base_addr + MCI_PWREN));

	/* Delay 100ms, waiting for the eMMC device power off*/
	udelay(100 * 1000);
}

void print_ext_csd(struct mmc *mmc)
{
	unsigned char ext_csd[512];
	unsigned int tmp;

	HIMCI_DEBUG_FUN("Function Call");

	int err = mmc_send_ext_csd(mmc, ext_csd);
	if (err) {
		HIMCI_ERROR("Check est_csd error!");
		return;
	}

	HIMCI_DEBUG_INFO("Extended CSD register:");
	for (tmp = 0; tmp < 512; tmp += 8)
		HIMCI_DEBUG_INFO
		    ("%03d: %02x %02x %02x %02x %02x %02x %02x %02x", tmp,
		     ext_csd[tmp], ext_csd[tmp + 1], ext_csd[tmp + 2],
		     ext_csd[tmp + 3], ext_csd[tmp + 4], ext_csd[tmp + 5],
		     ext_csd[tmp + 6], ext_csd[tmp + 7]);
}

static void print_mmcinfo(struct mmc *mmc)
{
	HIMCI_DEBUG_FUN("Function Call");

	printf("MMC/SD Card:\n");
	printf("    MID:         0x%x\n", mmc->cid[0] >> 24);
	printf("    Read Block:  %d Bytes\n", mmc->read_bl_len);
	printf("    Write Block: %d Bytes\n", mmc->write_bl_len);
	printf("    Chip Size:   %s Bytes (%s)\n",
	       ultohstr(mmc->capacity),
	       mmc->high_capacity ? "High Capacity" : "Low Capacity");
	printf("    Name:        \"%c%c%c%c%c\"\n",
	       mmc->cid[0] & 0xff,
	       (mmc->cid[1] >> 24),
	       (mmc->cid[1] >> 16) & 0xff,
	       (mmc->cid[1] >> 8) & 0xff,
	       mmc->cid[1] & 0xff);

	printf("    Chip Type:   %s\n"
	       "    Version:     %d.%d\n",
	       IS_SD(mmc) ? "SD" : "MMC",
	       (mmc->version >> 4) & 0xf, mmc->version & 0xf);

	printf("    Speed:       %sHz\n", ultohstr(mmc->clock));
	printf("    Bus Width:   %dbit\n", mmc->bus_width);
}

int himci_probe(int dev_num)
{
	struct mmc *mmc = find_mmc_device(dev_num);
	int err = 0;

	puts("\nEMMC/MMC/SD controller initialization.\n");

	if (!mmc) {
		printf("mmc device not found!!\n");
		return -1;
	}

	err = mmc_init(mmc);
	if (err) {
		printf("mmc_init failed! err:%d\n", err);
		return err;
	}

	print_mmcinfo(mmc);
#ifdef CONFIG_SUPPORT_EMMC_BOOT
	if (!IS_SD(mmc))
		    return mmc_set_boot_config(mmc);
#endif
	return 0;
}

static const struct mmc_ops himci_ops = {
	.send_cmd   = hi_mci_request,
	.set_ios    = hi_mci_set_ios,
	.init       = hi_mci_init,
	.execute_tuning = hi_mci_execute_tuning,
	.card_busy = hi_mci_card_busy,
};

static void himci_setup_cfg(struct mmc_config *cfg, struct himci_host *host,
		unsigned int max_clk, unsigned int min_clk)
{
	cfg->name = host->name;
	cfg->f_min = min_clk;
	cfg->f_max = max_clk;

	cfg->voltages = MMC_VDD_32_33 | MMC_VDD_33_34;

	cfg->host_caps |= MMC_MODE_4BIT;
	cfg->host_caps |= MMC_MODE_HS | MMC_MODE_HS_52MHz | MMC_MODE_HS200;
	cfg->b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT;

	cfg->ops = &himci_ops;
}

int add_himci(struct himci_host *host, unsigned int max_clk, unsigned int min_clk)
{
	himci_setup_cfg(&host->cfg, host, max_clk, min_clk);

	host->mmc = mmc_create(&host->cfg, host);
	if (host->mmc == NULL)
		return -1;

	add_shutdown(himci_shutdown);
	return 0;
}

int himci_add_port(int index, unsigned int reg_base, unsigned int freq)
{
	struct himci_host *host = NULL;
	unsigned int regval;

	HIMCI_DEBUG_FUN("Function Call");
	hi_mci_sys_init(index, freq);

	/* check controller version. */
	regval = himci_readl(reg_base + MCI_VERID);
	if ((regval != MCI_VERID_VALUE) && (regval != MCI_VERID_VALUE2)
			&& (regval != MCI_VERID_VALUE3)) {
		printf("MMC/SD/EMMC controller version incorrect.\n");
		return -ENODEV;
	}

	host = calloc(1, sizeof(struct himci_host));
	if (!host) {
		puts("host malloc fail!\n");
		return -ENOMEM;
	}

	host->name = "himci";
	host->dev_id = index;
	host->base = (unsigned long)reg_base;
	host->dma_des = hi_dma_des;
	host->card_status = hi_mci_sys_card_detect(host);
	host->port = 0;
	host->is_tuning = 0;
	return add_himci(host, freq, MMC_CCLK_MIN);
}
