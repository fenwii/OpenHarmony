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
#include "scsi.h"
#include "ufs.h"

static int get_cmnd(uint32_t opcode, uint32_t lba, uint32_t size, uint8_t *cmd)
{
	ufs_memset(cmd, 0x0, 16);

	switch (opcode) {
	case UFS_OP_READ_10:
		cmd[0] = UFS_OP_READ_10;
		cmd[1] = 0;
		cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
		cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
		cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
		cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
		cmd[6] = 0;
		cmd[7] = (uint8_t)((size >> 8) & 0xff);
		cmd[8] = (uint8_t)((size) & 0xff);
		cmd[9] = 0;
		break;

	case UFS_OP_TEST_UNIT_READY:
		cmd[0] = UFS_OP_TEST_UNIT_READY;
		cmd[1] = 0;
		cmd[2] = 0;
		cmd[3] = 0;
		cmd[4] = 0;
		cmd[5] = 0;
		break;

	default:
		return -1;
	}
	return 0;
}
