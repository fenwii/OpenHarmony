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
#include <asm/io.h>

uint64_t ufsboot_static_space_address = 0;

#include "ufs.h"
#include "scsi.c"

static int send_uic_command(uint32_t command, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	int retry = 10;
	unsigned int tick;
	uint32_t reg = 0;
	unsigned int tick_ready;

	tick_ready = current_time();
	for (;;) {
		if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_UCRDY_BIT) {
			break;
		}
		if (time_passed_ms(tick_ready) > UFS_HC_WAIT_UCRDY_TIMEOUT_MS) {
			break;
		}
	}

	do {
		//debug_printf("send_uic_command: cmd = 0x%x, arg1 = 0x%x, retry = %d\n", command, arg1, retry);
		dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
		dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, arg1);
		dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, arg2);
		dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, arg3);

		dwc_ufs_write_reg(UFS_UICCMD_OFF, (command & 0xFF));

		tick = current_time();
		for (;;) {
			if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT) {
				reg = dwc_ufs_read_reg(UFS_UICCMDARG2_OFF) & UFS_UICCMDARG2_RET_MASK;
				if (!reg) {
					dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
					return UFS_SUCCESS;
				} else {
					debug_printf("send_uic_command: get error resp, resp = 0x%x\n", reg);
					ufs_waitms(1);
					break;
				}
			}

			if (time_passed_ms(tick) > UFS_SEND_UIC_CMD_TIMEOUT_MS) {
				debug_printf("send_uic_command: wait UCCS int timeout\n");
				break;
			}
		}
	} while (--retry > 0);

	dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
	debug_printf("send_uic_command: return error, ret = -0x%x\n", ((reg & 0xf) + RET_UIC_CONFIG_ERROR_OFF));
	return -((reg & 0xf) + RET_UIC_CONFIG_ERROR_OFF);
}

static void ufs_config_init(void)
{
	int i = 0;
	struct dwc_ufs_utrd *p_utrd = NULL;

	/* Unipro DL_AFC0CreditThreshold */
	send_uic_command(DME_SET, 0x20440000, 0, 0x0);
	/* Unipro DL_TC0OutAckThreshold */
	send_uic_command(DME_SET, 0x20450000, 0, 0x0);
	/* Unipro DL_TC0TXFCThreshold */
	send_uic_command(DME_SET, 0x20400000, 0, 0x9);

	ufsboot_static_space_address = UFS_START_WORK_SPACE_START;
	ufs_memset((void*)ufsboot_static_space_address, 0, UFS_STATIC_WORK_SPACE_SIZE);
	ufsboot_static_space_address = BYTES_ALIGN_1024(ufsboot_static_space_address);
	if (!ufsboot_static_space_address) {
		return ;
	}

	p_utrd = (struct dwc_ufs_utrd *)UFS_TR_UTP_BASE;
	/* UTRD init */
	ufs_memset((void *)UFS_TR_UTP_BASE, 0, MAX_TR_TASK * sizeof(struct dwc_ufs_utrd));
	writel(0x1, STATIC_UFS_TAG_ADDR);

	dwc_ufs_write_reg(UFS_UTRLBA_OFF, UFS_TR_UTP_BASE);
	dwc_ufs_write_reg(UFS_UTRLBAU_OFF, 0);

	for (i = 0; i < MAX_TR_TASK; i++) {
		//debug_printf("init UTRD, p_utrd addr = 0x%x\n", (uint32_t)p_utrd);
		p_utrd->ucdba = UFS_CMD_UPIU_BASE;
		p_utrd->ucdbau = 0x0;
		p_utrd->resp_upiu_offset = (UFS_RESP_UPIU_BASE - UFS_CMD_UPIU_BASE) >> 2;
		p_utrd->prdt_offset = (UFS_PRDT_BASE - UFS_CMD_UPIU_BASE) >> 2;
		p_utrd += 1;
	}
	/* UTMRD init */
	ufs_memset((void *)UFS_TMR_UTP_BASE, 0, 20 * 4);
	dwc_ufs_write_reg(UFS_UTMRLBA_OFF, UFS_TMR_UTP_BASE);
	dwc_ufs_write_reg(UFS_UTMRLBAU_OFF, 0);

	dwc_ufs_write_reg(UFS_UTRLRSR_OFF, UFS_UTP_RUN_BIT);
	dwc_ufs_write_reg(UFS_UTMRLRSR_OFF, UFS_UTP_RUN_BIT);
	return;
}

static int wait_for_cmd_completion(uint32_t tag, uint32_t timeout_ms)
{
	unsigned int tick;

	if ((tag < 1) || (tag > MAX_TR_TASK)) {
		debug_printf("wait_for_cmd_completion: input tag invalid, tag = %u\n", tag);
		tag = 1;
	}

	/* Set the doorbell for processing the request */
	dwc_ufs_write_reg(UFS_UTRLDBR_OFF, 0x1 << (tag - 1));

	tick = current_time();
	/* Wait for the DoorBell to clear */
	for (;;) {
		if((dwc_ufs_read_reg(UFS_UTRLDBR_OFF) & (0x1 << (tag - 1))) == 0) {
			break;
		}

		if(time_passed_ms(tick) > timeout_ms) {
			debug_printf("UTRL DoorBell Not Cleared and Timed Out\n");
			dwc_ufs_write_reg(UFS_UTRLCLR_OFF, 0);
			return UFS_UTRD_DOORBELL_TIMEOUT;
		}
	}

	return UFS_SUCCESS;
}

static void create_nop_out_upiu(uint32_t tag)
{
	struct dwc_ufs_nop_req_upiu *cmd_upiu_ptr = NULL;
	struct dwc_ufs_utrd *utrd_desc = NULL;
	int i;

	if ((tag < 1) || (tag > MAX_TR_TASK)) {
		debug_printf("create_nop_out_upiu: input tag invalid, tag = %u\n", tag);
		tag = 1;
	}

	cmd_upiu_ptr = (struct dwc_ufs_nop_req_upiu*)UFS_CMD_UPIU_BASE;
	utrd_desc = (struct dwc_ufs_utrd *)UFS_TR_UTP_BASE;
	utrd_desc += tag - 1;
	debug_printf("create_nop_out_upiu: utrd_desc addr 0x%x\n", (unsigned int)(uintptr_t)utrd_desc);

	/* clean response upiu */
	ufs_memset((void *)UFS_RESP_UPIU_BASE, 0, sizeof(struct dwc_ufs_nop_resp_upiu));

	utrd_desc->ct_and_flags = (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);

	utrd_desc->resp_upiu_length = to_littleendian16((uint16_t)sizeof(struct dwc_ufs_nop_resp_upiu) >> 2);
	utrd_desc->prdt_length = 0;
	utrd_desc->ocs = 0xf;

	cmd_upiu_ptr->trans_type = 0x00;
	cmd_upiu_ptr->flags = 0x00;
	cmd_upiu_ptr->reserved_1 = 0x00;
	cmd_upiu_ptr->task_tag = tag;
	cmd_upiu_ptr->reserved_2 = 0x0;
	cmd_upiu_ptr->tot_ehs_len = 0x00;
	cmd_upiu_ptr->reserved_3 = 0x00;
	cmd_upiu_ptr->data_seg_len = 0x00;
	for (i = 0; i < 20; i++) {
		cmd_upiu_ptr->reserved_4[i] = 0x00;
	}

	return;
}

static int read_nop_rsp(uint32_t tag)
{
	struct dwc_ufs_nop_resp_upiu *resp_upiu = NULL;
	struct dwc_ufs_utrd *utrd_desc = NULL;

	if ((tag < 1) || (tag > MAX_TR_TASK)) {
		debug_printf("read_nop_rsp: input tag invalid, tag = %u\n", tag);
		tag = 1;
	}

	resp_upiu = (struct dwc_ufs_nop_resp_upiu *)UFS_RESP_UPIU_BASE;
	utrd_desc = (struct dwc_ufs_utrd *)UFS_TR_UTP_BASE;
	utrd_desc += tag - 1;

	debug_printf("read_nop_rsp: utrd_desc addr 0x%x\n", (unsigned int)(uintptr_t)utrd_desc);

	if (utrd_desc->ocs != UFS_SUCCESS) {
		return -((utrd_desc->ocs & 0xf) + RET_UTRD_OCS_ERROR_OFF);
	}

	if ((resp_upiu->trans_type & 0x3F) != NOP_TRANS_TYPE) {
		debug_printf("invalid nop in\n");
		return UFS_INVALID_NOP_IN;
	}

	if (resp_upiu->response != UFS_SUCCESS) {
		debug_printf("nop in response error, resp = 0x%x\n", resp_upiu->response);
		return UFS_NOP_RESP_FAIL;
	}

	return UFS_SUCCESS;
}

static int send_nop_out_cmd(void)
{
	int ret;
	uint32_t tag = 0;
	int i;

	tag = readl(STATIC_UFS_TAG_ADDR);
	debug_printf("in send nop out: read tag = %u\n", tag);
	for (i = 0; i < 3; i++) {
		if ((tag > MAX_TR_TASK) || (tag < 1)) {
			tag = 1;
		}
		debug_printf("create nop out: tag = %u\n", tag);
		create_nop_out_upiu(tag);
		ret = wait_for_cmd_completion(tag, UFS_SEND_NOP_OUT_TIMEOUT_MS);
		if (ret == UFS_SUCCESS) {
			ret = read_nop_rsp(tag);
		}

		if (ret == UFS_SUCCESS) {
			break;
		}

		debug_printf("nop out nop in fail, ret = %d, retry = %d\n", ret, i);
		ufs_waitms(1);
		if (ret == UFS_UTRD_DOORBELL_TIMEOUT) {
			tag++;
			writel(tag, STATIC_UFS_TAG_ADDR);
		}
	}

	return ret;
}

static int create_cmd_upiu(uint32_t opcode,
			   enum dma_data_direction direction,
			   uint64_t buf_addr, uint32_t rel_addr,
			   uint32_t size, uint32_t tag)
{
	struct dwc_ufs_cmd_upiu *cmd_upiu_ptr = NULL;
	struct dwc_ufs_utrd *utrd_desc = NULL;
	struct dwc_ufs_prd *prdt_table = NULL;
	uint32_t data_direction;
	uint8_t upiu_flags;
	const uint32_t prdt_buf_size = PRDT_BUFFER_SIZE;
	uint64_t buf_addr_phy;
	uint32_t i;
	int ret;

	if (opcode == UFS_OP_READ_10) {
		if (rel_addr % LOGICAL_BLK_SIZE) {
			return UFS_SOFTWARE_ERROR;
		}
		if (size % LOGICAL_BLK_SIZE) {
			return UFS_SOFTWARE_ERROR;
		}
	}

	cmd_upiu_ptr = (struct dwc_ufs_cmd_upiu *)UFS_CMD_UPIU_BASE;
	utrd_desc = (struct dwc_ufs_utrd *)UFS_TR_UTP_BASE;
	utrd_desc += tag - 1;
	debug_printf("create_cmd_upiu: utrd_desc addr 0x%x\n", (unsigned int)(uintptr)utrd_desc);

	prdt_table = (struct dwc_ufs_prd *)UFS_PRDT_BASE;

	if (direction == DMA_FROM_DEVICE) {
		data_direction = UTP_DEVICE_TO_HOST;
		upiu_flags = UPIU_CMD_FLAGS_READ;
	} else if (direction == DMA_NONE) {
		data_direction = UTP_NO_DATA_TRANSFER;
		upiu_flags = UPIU_CMD_FLAGS_NONE;
	} else {
		return UFS_SOFTWARE_ERROR;
	}

	/* clean response upiu */
	ufs_memset((void *)UFS_RESP_UPIU_BASE, 0, sizeof(struct dwc_ufs_xfer_resp_upiu));

	/* Update cmd_type, flags and response upiu length for transfer requests */
	utrd_desc->ct_and_flags =
		(uint8_t)(data_direction | UTP_UFS_STORAGE_COMMAND);
	utrd_desc->resp_upiu_length = to_littleendian16((uint16_t)
				      (sizeof(struct dwc_ufs_xfer_resp_upiu) >> 2));
	utrd_desc->ocs = 0xf;
	utrd_desc->prdt_length = to_littleendian16((uint16_t)
				 ((size + PRDT_BUFFER_SIZE - 1) / PRDT_BUFFER_SIZE));

	cmd_upiu_ptr->trans_type       = 0x01;
	cmd_upiu_ptr->flags            = upiu_flags;
	cmd_upiu_ptr->lun              = UFS_BOOT_LUN;
	cmd_upiu_ptr->task_tag         = tag;
	cmd_upiu_ptr->cmd_set_type     = 0x0;
	cmd_upiu_ptr->reserved_1_0     = 0x0;
	cmd_upiu_ptr->reserved_1_1     = 0x0;
	cmd_upiu_ptr->reserved_1_2     = 0x0;
	cmd_upiu_ptr->tot_ehs_len      = 0x0;
	cmd_upiu_ptr->reserved_2       = 0x0;
	cmd_upiu_ptr->data_seg_len     = 0x0;
	cmd_upiu_ptr->exp_data_xfer_len = to_bigendian32(size);

	ret = get_cmnd(opcode, (rel_addr / LOGICAL_BLK_SIZE),
		       (size / LOGICAL_BLK_SIZE), cmd_upiu_ptr->cdb);
	if (ret) {
		return UFS_SOFTWARE_ERROR;
	}

	buf_addr_phy =
		(uint64_t)LPRAM_ADDR_FROM_LPM3_TO_CPU((uint64_t)buf_addr);

	/* Fill PRD Table Info */
	if (direction != DMA_NONE) {
		for (i = 0; (size); i++) {
			prdt_table[i].base_addr =
				to_littleendian32((uint32_t)
						  (buf_addr_phy & 0xffffffff) +
						  (i * prdt_buf_size));
			prdt_table[i].upper_addr =
				to_littleendian32((uint32_t)
						  ((buf_addr_phy >> 32) & 0xffffffff));
			prdt_table[i].reserved1 = 0x0;
			prdt_table[i].size = to_littleendian32
					     (((prdt_buf_size < size) ? prdt_buf_size : size) - 1);
			size -= (prdt_buf_size < size) ? prdt_buf_size : size;
		}
	}

	return UFS_SUCCESS;
}

static int send_scsi_cmd(uint32_t opcode,
			 enum dma_data_direction direction,
			 uint64_t buf_addr, uint32_t rel_addr,
			 uint32_t size, uint32_t tag)
{
	int ret;
	uint32_t timeout_ms;

	if (size % 0x4) {
		return UFS_SOFTWARE_ERROR;
	}
	if (size / PRDT_BUFFER_SIZE >= MAX_PRDT_ENTRIES) {
		return UFS_SOFTWARE_ERROR;
	}

	if (opcode == UFS_OP_TEST_UNIT_READY) {
		timeout_ms = 10;
	} else if (opcode == UFS_OP_READ_10)
		//timeout_ms = 1000;
		//debug for reset bug
	{
		timeout_ms = 50000;
	} else {
		return UFS_SOFTWARE_ERROR;
	}

	ret = create_cmd_upiu(opcode, direction, buf_addr, rel_addr, size, tag);
	if (ret != UFS_SUCCESS) {
		return ret;
	}

	ret = wait_for_cmd_completion(tag, timeout_ms);
	return ret;
}

static int handle_scsi_completion(uint32_t tag)
{
	struct dwc_ufs_xfer_resp_upiu *resp_upiu;
	struct dwc_ufs_utrd *utrd_desc;
	uint8_t status;

	resp_upiu = (struct dwc_ufs_xfer_resp_upiu *)UFS_RESP_UPIU_BASE;
	utrd_desc = (struct dwc_ufs_utrd *)UFS_TR_UTP_BASE;
	utrd_desc += tag - 1;
	debug_printf("handle_scsi_completion: utrd_desc addr 0x%x\n", (unsigned int)(uintptr_t)utrd_desc);

	if (utrd_desc->ocs == UFS_SUCCESS) {
		status = resp_upiu->status;
		if (status == SAM_STAT_GOOD) {
			return UFS_SUCCESS;
		}

		if (status == SAM_STAT_CHECK_CONDITION) {
			return -(RET_SENSE_KEY_OFF + (resp_upiu->sense_data[2] & 0xf));
		}

		switch (status) {
		case SAM_STAT_CONDITION_MET:
			return RESP_STAT_CONDITION_MET;
		case SAM_STAT_BUSY:
			return RESP_STAT_BUSY;
		case SAM_STAT_RESERVATION_CONFLICT:
			return RESP_STAT_RESERVATION_CONFLICT;
		case SAM_STAT_TASK_SET_FULL:
			return RESP_STAT_TASK_SET_FULL;
		case SAM_STAT_ACA_ACTIVE:
			return RESP_STAT_ACA_ACTIVE;
		case SAM_STAT_TASK_ABORTED:
			return RESP_STAT_TASK_ABORTED;
		default:
			return RESP_STAT_UNKNOW;
		}
	} else {
		return -((utrd_desc->ocs & 0xf) + RET_UTRD_OCS_ERROR_OFF);
	}

	return UFS_SUCCESS;
}

static int do_scsi_cmd(uint32_t opcode,
		       enum dma_data_direction direction,
		       uint64_t buf_addr, uint32_t rel_addr,
		       uint32_t size, uint32_t tag)
{
	int ret = 0;
	if ((tag < 1) || (tag > MAX_TR_TASK)) {
		debug_printf("do_scsi_cmd: input tag invalid, tag = %u\n", tag);
		tag = 1;
	}

	ret = send_scsi_cmd(opcode, direction, buf_addr, rel_addr, size, tag);
	if (ret != UFS_SUCCESS) {
		return ret;
	}

	ret = handle_scsi_completion(tag);
	if (ret != UFS_SUCCESS) {
		return ret;
	}
	return ret;
}

static int test_unit_ready(void)
{
	uint32_t tag = 0;
	int ret;
	int i;

	tag = readl(STATIC_UFS_TAG_ADDR);
	debug_printf("test_unit_ready: read tag = %u\n", tag);
	for (i = 0; i < 4; i++) {
		if ((tag > MAX_TR_TASK) || (tag < 1)) {
			tag = 1;
		}
		debug_printf("test_unit_ready: tag = %u\n", tag);

		ret = do_scsi_cmd(UFS_OP_TEST_UNIT_READY, DMA_NONE, 0, 0, 0, tag);
		if (ret == UFS_SUCCESS) {
			break;
		}
		debug_printf("test_unit_ready ret = %d, retry = %d\n", ret, i);
		ufs_waitms(1);
		if (ret == UFS_UTRD_DOORBELL_TIMEOUT) {
			tag++;
			writel(tag, STATIC_UFS_TAG_ADDR);
		}
	}

	return ret;
}

static int ufs_start_boot(void)
{
	int ret;

	ret = send_nop_out_cmd();
	if (ret) {
		debug_printf("ufs send nop out fail\n");
		return ret;
	}

	debug_printf("ufs nop in out OK\n");

	ret = test_unit_ready();
	if (ret) {
		debug_printf("ufs test unit ready fail\n");
		return ret;
	}

	debug_printf("ufs test unit ready OK\n");
	return UFS_SUCCESS;
}

static int ufs_read_boot_data(uint64_t buf_addr,
			      uint32_t rel_addr,
			      uint32_t size)
{
	int ret;
	int retry = 50;
	uint32_t tag = 0;

	size = BYTES_ALIGN_4096(size);
	tag = readl(STATIC_UFS_TAG_ADDR);
	debug_printf("ufs_read_boot_data: read tag = %u\n", tag);
	if ((tag > MAX_TR_TASK) || (tag < 1)) {
		tag = 1;
	}
	debug_printf("ufs_read_boot_data: tag = %u\n", tag);

	while (retry > 0) {
		ret = do_scsi_cmd(UFS_OP_READ_10, DMA_FROM_DEVICE, buf_addr, rel_addr, size, tag);
		if (ret == UFS_SUCCESS) {
			debug_printf("ufs read 10 OK\n");
			return ret;
		} else if ((ret == RESP_STAT_BUSY)
			   || (ret == RESP_STAT_TASK_SET_FULL)
			   || (ret == NOT_READY)) {
			ufs_waitms(1);
			retry--;
			debug_printf("ufs read 10 retry, ret = %d, retry = %d\n", ret, retry);
		} else {
			debug_printf("ufs read 10 FAIL, ret = %d\n", ret);
			break;
		}
	}
	return ret;
}

void ufs_boot_read(void *ptr, unsigned int size)
{
	ufs_memset(ptr, 0, size);
	ufs_config_init();
	ufs_start_boot();
	ufs_read_boot_data((uint64_t)ptr, 0, size);
}

