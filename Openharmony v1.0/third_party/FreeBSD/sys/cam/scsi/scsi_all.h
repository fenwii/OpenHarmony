/*-
 * Largely written by Julian Elischer (julian@tfs.com)
 * for TRW Financial Systems.
 *
 * TRW Financial Systems, in accordance with their agreement with Carnegie
 * Mellon University, makes this software available to CMU to distribute
 * or use in any manner that they see fit as long as this message is kept with
 * the software. For this reason TFS also grants any other persons or
 * organisations permission to use or modify this software.
 *
 * TFS supplies this software to be publicly redistributed
 * on the understanding that TFS is not responsible for the correct
 * functioning of this software in any circumstances.
 *
 * Ported to run under 386BSD by Julian Elischer (julian@tfs.com) Sept 1992
 *
 * $FreeBSD: releng/11.4/sys/cam/scsi/scsi_all.h 351582 2019-08-28 20:23:08Z mav $
 */

#ifndef __INCLUDE_SCSI_ALL_H
#define	__INCLUDE_SCSI_ALL_H

#define	SC_SCSI_1 0x01
#define	SC_SCSI_2 0x03

#define	SCSI_REV_2 0x02

/*
 * Opcodes
 */

#define	TEST_UNIT_READY		0x00
#define	REQUEST_SENSE		0x03
#define	READ_6				0x08
#define	WRITE_6				0x0A
#define	INQUIRY				0x12
#define	MODE_SELECT_6		0x15
#define	MODE_SENSE_6		0x1A
#define	START_STOP_UNIT		0x1B
#define	START_STOP			0x1B
#define	RESERVE				0x16
#define	RELEASE				0x17
#define	RECEIVE_DIAGNOSTIC	0x1C
#define	SEND_DIAGNOSTIC		0x1D
#define	PREVENT_ALLOW		0x1E
#define	READ_CAPACITY		0x25
#define	READ_10				0x28
#define	WRITE_10			0x2A
#define	POSITION_TO_ELEMENT	0x2B
#define	WRITE_VERIFY_10		0x2E
#define	VERIFY_10			0x2F
#define	SYNCHRONIZE_CACHE	0x35
#define	READ_DEFECT_DATA_10	0x37
#define	WRITE_BUFFER		0x3B
#define	READ_BUFFER			0x3C
#define	CHANGE_DEFINITION	0x40
#define	WRITE_SAME_10		0x41
#define	UNMAP				0x42
#define	LOG_SELECT			0x4C
#define	LOG_SENSE			0x4D
#define	MODE_SELECT_10		0x55
#define	RESERVE_10			0x56
#define	RELEASE_10			0x57
#define	MODE_SENSE_10		0x5A
#define	PERSISTENT_RES_IN	0x5E
#define	PERSISTENT_RES_OUT	0x5F
#define	EXTENDED_COPY		0x83
#define	RECEIVE_COPY_STATUS	0x84
#define	ATA_PASS_16			0x85
#define	READ_16				0x88
#define	COMPARE_AND_WRITE	0x89
#define	WRITE_16			0x8A
#define	WRITE_VERIFY_16		0x8E
#define	VERIFY_16			0x8F
#define	SYNCHRONIZE_CACHE_16	0x91
#define	WRITE_SAME_16		0x93
#define	SERVICE_ACTION_IN	0x9E
#define	REPORT_LUNS			0xA0
#define	ATA_PASS_12			0xA1
#define	MAINTENANCE_IN		0xA3
#define	MAINTENANCE_OUT		0xA4
#define	MOVE_MEDIUM			0xA5
#define	READ_12				0xA8
#define	WRITE_12			0xAA
#define	WRITE_VERIFY_12		0xAE
#define	VERIFY_12			0xAF
#define	READ_ELEMENT_STATUS	0xB8
#define	READ_CD				0xBE

/* Maintenance In Service Action Codes */
#define	REPORT_IDENTIFYING_INFRMATION		0x05
#define	REPORT_TARGET_PORT_GROUPS			0x0A
#define	REPORT_ALIASES						0x0B
#define	REPORT_SUPPORTED_OPERATION_CODES	0x0C
#define	REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS	0x0D
#define	REPORT_PRIORITY						0x0E
#define	REPORT_TIMESTAMP					0x0F
#define	MANAGEMENT_PROTOCOL_IN				0x10
/* Maintenance Out Service Action Codes */
#define	SET_IDENTIFY_INFORMATION			0x06
#define	SET_TARGET_PORT_GROUPS				0x0A
#define	CHANGE_ALIASES						0x0B
#define	SET_PRIORITY						0x0E
#define	SET_TIMESTAMP						0x0F
#define	MANGAEMENT_PROTOCOL_OUT				0x10

/*
 * Device Types
 */
#define	T_DIRECT	0x00
#define	T_SEQUENTIAL	0x01
#define	T_PRINTER	0x02
#define	T_PROCESSOR	0x03
#define	T_WORM		0x04
#define	T_CDROM		0x05
#define	T_SCANNER	0x06
#define	T_OPTICAL	0x07
#define	T_CHANGER	0x08
#define	T_COMM		0x09
#define	T_ASC0		0x0a
#define	T_ASC1		0x0b
#define	T_STORARRAY	0x0c
#define	T_ENCLOSURE	0x0d
#define	T_RBC		0x0e
#define	T_OCRW		0x0f
#define	T_OSD		0x11
#define	T_ADC		0x12
#define	T_NODEVICE	0x1f
#define	T_ANY		0xff	/* Used in Quirk table matches */

#define	T_REMOV		1
#define	T_FIXED		0

/*
 * This length is the initial inquiry length used by the probe code, as
 * well as the length necessary for scsi_print_inquiry() to function
 * correctly.  If either use requires a different length in the future,
 * the two values should be de-coupled.
 */
#define	SHORT_INQUIRY_LENGTH	36

struct scsi_test_unit_ready
{
	uint8_t opcode;
	uint8_t byte2;
	uint8_t unused[3];
	uint8_t control;
};

struct scsi_sense
{
	uint8_t opcode;
	uint8_t byte2;
	uint8_t unused[2];
	uint8_t length;
	uint8_t control;
};

struct scsi_inquiry
{
	uint8_t opcode;
	uint8_t byte2;
#define	SI_EVPD		0x01
#define	SI_CMDDT	0x02
	uint8_t page_code;
	uint8_t length[2];
	uint8_t control;
};

struct scsi_sense_data
{
	uint8_t error_code;
	/*
	 * SPC-4 says that the maximum length of sense data is 252 bytes.
	 * So this structure is exactly 252 bytes log.
	 */
#define	SSD_FULL_SIZE 252
	uint8_t sense_buf[SSD_FULL_SIZE - 1];
	/*
	 * XXX KDM is this still a reasonable minimum size?
	 */
#define	SSD_MIN_SIZE 18
	/*
	 * Maximum value for the extra_len field in the sense data.
	 */
#define	SSD_EXTRA_MAX 244
};

struct scsi_start_stop_unit
{
	uint8_t opcode;
	uint8_t byte2;
#define	SSS_IMMED		0x01
	uint8_t reserved[2];
	uint8_t how;
#define	SSS_START			0x01
#define	SSS_LOEJ			0x02
#define	SSS_PC_MASK			0xf0
#define	SSS_PC_START_VALID	0x00
#define	SSS_PC_ACTIVE		0x10
#define	SSS_PC_IDLE			0x20
#define	SSS_PC_STANDBY		0x30
#define	SSS_PC_LU_CONTROL	0x70
#define	SSS_PC_FORCE_IDLE_0	0xa0
#define	SSS_PC_FORCE_STANDBY_0	0xb0
	uint8_t control;
};

/*
 * Opcodes
 */
#define	VERIFIED			0x2f
#define	REZERO_UNIT			0x01
#define	FORMAT_UNIT			0x04
#define	REASSIGN_BLOCKS		0x07
#define	MODE_SELECT			0x15
#define	MODE_SENSE			0x1a
#define	READ_FORMAT_CAPACITIES	0x23
#define	WRITE_AND_VERIFY	0x2e
#define	READ_DEFECT_DATA_10	0x37
#define	SANITIZE			0x48
#define	READ_DEFECT_DATA_12	0xb7

#endif
