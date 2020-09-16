#ifndef __SCSI_H__
#define __SCSI_H__

#define UFS_OP_TEST_UNIT_READY       0x00
#define UFS_OP_READ_10               0x28

/* SCSI Status Macros */
#define SAM_STAT_GOOD                 0x00
#define SAM_STAT_CHECK_CONDITION      0x02
#define SAM_STAT_CONDITION_MET        0x04
#define SAM_STAT_BUSY                 0x08
#define SAM_STAT_RESERVATION_CONFLICT 0x18
#define SAM_STAT_TASK_SET_FULL        0x28
#define SAM_STAT_ACA_ACTIVE           0x30
#define SAM_STAT_TASK_ABORTED         0x40

#endif

