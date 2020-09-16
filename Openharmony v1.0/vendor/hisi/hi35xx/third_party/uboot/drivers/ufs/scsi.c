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
 * Description: scsi command
 */

#include <common.h>
#include <ufs.h>
#include "scsi.h"

struct scsi_adapt_func {
	uint32_t opcode;
	void (*func)(uint32_t lba, uint32_t size, uint8_t *cmd);
};

static void scsi_read_10(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_READ_10;                  /* 0: opcode */
	cmd[1] = 0;                               /* 1: DPO FUA */
	cmd[2] = (uint8_t)((lba >> 24) & 0xff);   /* 2: MSB, shift 24 */
	cmd[3] = (uint8_t)((lba >> 16) & 0xff);   /* 3: MSB, shift 16 */
	cmd[4] = (uint8_t)((lba >> 8) & 0xff);    /* 4: LSB, shift 8 */
	cmd[5] = (uint8_t)(lba & 0xff);           /* 5: LSB */
	cmd[6] = 0;                               /* 6: group */
	cmd[7] = (uint8_t)((size >> 8) & 0xff);   /* 7: MSB, shift 8 */
	cmd[8] = (uint8_t)(size & 0xff);          /* 8: LSB */
	cmd[9] = 0;                               /* 9: control */
}

static void scsi_write_10(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_WRITE_10;                 /* 0: opcode */
	cmd[1] = 0;                               /* 1: DPO FUA */
	cmd[2] = (uint8_t)((lba >> 24) & 0xff);   /* 2: MSB, shift 24 */
	cmd[3] = (uint8_t)((lba >> 16) & 0xff);   /* 3: MSB, shift 16 */
	cmd[4] = (uint8_t)((lba >> 8) & 0xff);    /* 4: LSB, shift 8 */
	cmd[5] = (uint8_t)(lba & 0xff);           /* 5: LSB */
	cmd[6] = 0;                               /* 6: group */
	cmd[7] = (uint8_t)((size >> 8) & 0xff);   /* 7: MSB, shift 8 */
	cmd[8] = (uint8_t)(size & 0xff);          /* 8: LSB */
	cmd[9] = 0;                               /* 9: control */
}

static void scsi_sync_cache_10(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_SYNCHRONIZE_CACHE_10;     /* 0: opcode */
	cmd[1] = 0;                               /* 1: IMMED */
	cmd[2] = (uint8_t)((lba >> 24) & 0xff);   /* 2: MSB, shift 24 */
	cmd[3] = (uint8_t)((lba >> 16) & 0xff);   /* 3: MSB, shift 16 */
	cmd[4] = (uint8_t)((lba >> 8) & 0xff);    /* 4: LSB, shift 8 */
	cmd[5] = (uint8_t)(lba & 0xff);           /* 5: LSB */
	cmd[6] = 0;                               /* 6: group */
	cmd[7] = (uint8_t)((size >> 8) & 0xff);   /* 7: MSB, shift 8 */
	cmd[8] = (uint8_t)(size & 0xff);          /* 8: LSB */
	cmd[9] = 0;                               /* 9: control */
}

static void scsi_read_capacity_10(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_READ_CAPACITY_10;         /* 0: opcode */
	cmd[1] = 0;                               /* 1: reserved */
	cmd[2] = 0;                               /* 2: MSB, 0 for UFS */
	cmd[3] = 0;                               /* 3: MSB, 0 for UFS */
	cmd[4] = 0;                               /* 4: LSB, 0 for UFS */
	cmd[5] = 0;                               /* 5: LSB, 0 for UFS */
	cmd[6] = 0;                               /* 6: reserved */
	cmd[7] = 0;                               /* 7: reserved */
	cmd[8] = 0;                               /* 8: reserved */
	cmd[9] = 0;                               /* 9: control */
}

static void scsi_request_sense(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_REQUEST_SENSE;            /* 0: opcode */
	cmd[1] = 0;                               /* 1: reserved */
	cmd[2] = 0;                               /* 2: reserved */
	cmd[3] = 0;                               /* 3: reserved */
	cmd[4] = (uint8_t)(size & 0xff);          /* 4: allocation length */
	cmd[5] = 0;                               /* 5: control */
}

static void scsi_unmap(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_UNMAP;                    /* 0: opcode */
	cmd[1] = 0;                               /* 1: reserved */
	cmd[2] = 0;                               /* 2: reserved */
	cmd[3] = 0;                               /* 3: reserved */
	cmd[4] = 0;                               /* 4: reserved */
	cmd[5] = 0;                               /* 5: reserved */
	cmd[6] = 0;                               /* 6: group */
	cmd[7] = (uint8_t)((size >> 8) & 0xff);   /* 7: MSB, shift 8 */
	cmd[8] = (uint8_t)(size & 0xff);          /* 8: LSB */
	cmd[9] = 0;                               /* 9: control */
}

static void scsi_secproc_in(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_SECURITY_PROTOCOL_IN;     /* 0: opcode */
	cmd[1] = 0xEC;                            /* 1: security protocal */
	cmd[2] = 0;                               /* 2: specific */
	cmd[3] = 0x1;                             /* 3: specific */
	cmd[4] = 0;                               /* 4: reserved */
	cmd[5] = 0;                               /* 5: reserved */
	cmd[6] = (uint8_t)((lba >> 24) & 0xff);   /* 6: MSB, shift 24 */
	cmd[7] = (uint8_t)((lba >> 16) & 0xff);   /* 7: MSB, shift 16 */
	cmd[8] = (uint8_t)((lba >> 8) & 0xff);    /* 8: LSB, shift 8 */
	cmd[9] = (uint8_t)(lba & 0xff);           /* 9: LSB */
	cmd[10] = 0;                              /* 10: reserved */
	cmd[11] = 0;                              /* 11: control */
}

static void scsi_secproc_out(uint32_t lba, uint32_t size, uint8_t *cmd)
{
	cmd[0] = UFS_OP_SECURITY_PROTOCOL_OUT;    /* 0: opcode */
	cmd[1] = 0xEC;                            /* 1: security protocal */
	cmd[2] = 0;                               /* 2: specific */
	cmd[3] = 0x1;                             /* 3: specific */
	cmd[4] = 0;                               /* 4: reserved */
	cmd[5] = 0;                               /* 5: reserved */
	cmd[6] = (uint8_t)((lba >> 24) & 0xff);   /* 6: MSB, shift 24 */
	cmd[7] = (uint8_t)((lba >> 16) & 0xff);   /* 7: MSB, shift 16 */
	cmd[8] = (uint8_t)((lba >> 8) & 0xff);    /* 8: LSB, shift 8 */
	cmd[9] = (uint8_t)(lba & 0xff);           /* 9: LSB */
	cmd[10] = 0;                              /* 10: reserved */
	cmd[11] = 0;                              /* 11: control */
}

void get_cmnd(uint32_t opcode, uint32_t lba, uint32_t size, uint8_t *cmd)
{
	int i;

	struct scsi_adapt_func funclist[] = {
		{UFS_OP_READ_10, scsi_read_10},
		{UFS_OP_WRITE_10, scsi_write_10},
		{UFS_OP_SYNCHRONIZE_CACHE_10, scsi_sync_cache_10},
		{UFS_OP_READ_CAPACITY_10, scsi_read_capacity_10},
		{UFS_OP_REQUEST_SENSE, scsi_request_sense},
		{UFS_OP_UNMAP, scsi_unmap},
		{UFS_OP_SECURITY_PROTOCOL_IN, scsi_secproc_in},
		{UFS_OP_SECURITY_PROTOCOL_OUT, scsi_secproc_out}
	};

	for (i = 0; i < sizeof(funclist) / sizeof(funclist[0]); i++) {
		if (funclist[i].opcode == opcode) {
			funclist[i].func(lba, size, cmd);
			return;
		}
	}
	printf("opcode: 0x%x not support\n", opcode);
}

