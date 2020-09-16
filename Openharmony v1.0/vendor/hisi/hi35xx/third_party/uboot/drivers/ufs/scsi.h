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
 * Description: scsi header
 */

#ifndef __HISILICON_KIRIN_SCSI_H__
#define __HISILICON_KIRIN_SCSI_H__

/* Ref [2], Sec 11.3 */
#define UFS_OP_FORMAT_UNIT            0x04
#define UFS_OP_INQUIRY                0x12
#define UFS_OP_MODE_SELECT_10         0x55
#define UFS_OP_MODE_SENSE_10          0x5A
#define UFS_OP_PRE_FETCH_10           0x34
#define UFS_OP_PRE_FETCH_16           0x90
#define UFS_OP_READ_6                 0x08
#define UFS_OP_READ_10                0x28
#define UFS_OP_READ_16                0x88
#define UFS_OP_READ_BUFFER            0x3C
#define UFS_OP_READ_CAPACITY_10       0x25
#define UFS_OP_READ_CAPACITY_16       0x9E
#define UFS_OP_REPORT_LUNS            0xA0
#define UFS_OP_REQUEST_SENSE          0x03
#define UFS_OP_SECURITY_PROTOCOL_IN   0xA2
#define UFS_OP_SECURITY_PROTOCOL_OUT  0xB5
#define UFS_OP_SEND_DIAGNOSTIC        0x1D
#define UFS_OP_START_STOP_UNIT        0x1B
#define UFS_OP_SYNCHRONIZE_CACHE_10   0x35
#define UFS_OP_SYNCHRONIZE_CACHE_16   0x91
#define UFS_OP_TEST_UNIT_READY        0x00
#define UFS_OP_UNMAP                  0x42
#define UFS_OP_VERIFY_10              0x2F
#define UFS_OP_WRITE_6                0x0A
#define UFS_OP_WRITE_10               0x2A
#define UFS_OP_WRITE_16               0x8A
#define UFS_OP_WRITE_BUFFER           0x3B
#define SECURITY_PROTOCOL             0xEC

/* SCSI Status Macros */
#define SAM_STAT_GOOD                 0x00
#define SAM_STAT_CHECK_CONDITION      0x02
#define SAM_STAT_CONDITION_MET        0x04
#define SAM_STAT_BUSY                 0x08
#define SAM_STAT_RESERVATION_CONFLICT 0x18
#define SAM_STAT_TASK_SET_FULL        0x28
#define SAM_STAT_ACA_ACTIVE           0x30
#define SAM_STAT_TASK_ABORTED         0x40

void get_cmnd(uint32_t opcode, uint32_t lba, uint32_t size, uint8_t *cmd);

#endif /*__HISILICON_KIRIN_SCSI_H__*/

