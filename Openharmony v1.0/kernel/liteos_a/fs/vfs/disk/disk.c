/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "disk.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/mount.h"
#include "pthread.h"
#include "linux/spinlock.h"
#include "inode/inode.h"

#ifdef LOSCFG_DRIVERS_MMC
#include "mmc/block.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

los_disk g_sysDisk[SYS_MAX_DISK];
los_part g_sysPart[SYS_MAX_PART];

UINT32 g_uwFatSectorsPerBlock = CONFIG_FS_FAT_SECTOR_PER_BLOCK;
UINT32 g_uwFatBlockNums = CONFIG_FS_FAT_BLOCK_NUMS;

spinlock_t g_diskSpinlock;
spinlock_t g_diskFatBlockSpinlock;

UINT32 g_usbMode = 0;

#define MEM_ADDR_ALIGN_BYTE  64
#define RWE_RW_RW            0755

#define DISK_LOCK(mux) do {                                              \
    if (pthread_mutex_lock(mux) != 0) {                                  \
        PRINT_ERR("%s %d, mutex lock failed\n", __FUNCTION__, __LINE__); \
    }                                                                    \
} while (0)

#define DISK_UNLOCK(mux) do {                                              \
    if (pthread_mutex_unlock(mux) != 0) {                                  \
        PRINT_ERR("%s %d, mutex unlock failed\n", __FUNCTION__, __LINE__); \
    }                                                                      \
} while (0)

typedef VOID *(*StorageHookFunction)(VOID *);

static UINT32 OsReHookFuncAddDiskRef(StorageHookFunction handler,
                                     VOID *param) __attribute__((weakref("osReHookFuncAdd")));

static UINT32 OsReHookFuncDelDiskRef(StorageHookFunction handler) __attribute__((weakref("osReHookFuncDel")));

#ifdef LOSCFG_FS_FAT_CACHE
UINT32 GetFatBlockNums(VOID)
{
    return g_uwFatBlockNums;
}

VOID SetFatBlockNums(UINT32 blockNums)
{
    g_uwFatBlockNums = blockNums;
}

UINT32 GetFatSectorsPerBlock(VOID)
{
    return g_uwFatSectorsPerBlock;
}

VOID SetFatSectorsPerBlock(UINT32 sectorsPerBlock)
{
    if (((sectorsPerBlock % UNSIGNED_INTEGER_BITS) == 0) &&
        ((sectorsPerBlock >> UNINT_LOG2_SHIFT) <= BCACHE_BLOCK_FLAGS)) {
        g_uwFatSectorsPerBlock = sectorsPerBlock;
    }
}
#endif

INT32 los_alloc_diskid_byname(const CHAR *diskName)
{
    INT32 diskID;
    los_disk *disk = NULL;
    UINT32 intSave;
    size_t nameLen;

    if (diskName == NULL) {
        PRINT_ERR("The paramter disk_name is NULL");
        return VFS_ERROR;
    }

    nameLen = strlen(diskName);
    if (nameLen > DISK_NAME) {
        PRINT_ERR("diskName is too long!\n");
        return VFS_ERROR;
    }
    spin_lock_irqsave(&g_diskSpinlock, intSave);

    for (diskID = 0; diskID < SYS_MAX_DISK; diskID++) {
        disk = get_disk(diskID);
        if ((disk != NULL) && (disk->disk_status == STAT_UNUSED)) {
            disk->disk_status = STAT_UNREADY;
            break;
        }
    }

    spin_unlock_irqrestore(&g_diskSpinlock, intSave);

    if ((disk == NULL) || (diskID == SYS_MAX_DISK)) {
        PRINT_ERR("los_alloc_diskid_byname failed %d!\n", diskID);
        return VFS_ERROR;
    }

    if (disk->disk_name != NULL) {
        LOS_MemFree(m_aucSysMem0, disk->disk_name);
        disk->disk_name = NULL;
    }

    disk->disk_name = LOS_MemAlloc(m_aucSysMem0, (nameLen + 1));
    if (disk->disk_name == NULL) {
        PRINT_ERR("los_alloc_diskid_byname alloc disk name failed\n");
        return VFS_ERROR;
    }

    if (strncpy_s(disk->disk_name, (nameLen + 1), diskName, nameLen) != EOK) {
        PRINT_ERR("The strncpy_s failed.\n");
        return VFS_ERROR;
    }

    disk->disk_name[nameLen] = '\0';

    return diskID;
}

INT32 los_get_diskid_byname(const CHAR *diskName)
{
    INT32 diskID;
    los_disk *disk = NULL;
    size_t diskNameLen;

    if (diskName == NULL) {
        PRINT_ERR("The paramter diskName is NULL");
        return VFS_ERROR;
    }

    diskNameLen = strlen(diskName);
    if (diskNameLen > DISK_NAME) {
        PRINT_ERR("diskName is too long!\n");
        return VFS_ERROR;
    }

    for (diskID = 0; diskID < SYS_MAX_DISK; diskID++) {
        disk = get_disk(diskID);
        if ((disk != NULL) && (disk->disk_name != NULL) && (disk->disk_status == STAT_INUSED)) {
            if (strlen(disk->disk_name) != diskNameLen) {
                continue;
            }
            if (strcmp(diskName, disk->disk_name) == 0) {
                break;
            }
        }
    }
    if ((disk == NULL) || (diskID == SYS_MAX_DISK)) {
        PRINT_ERR("los_get_diskid_byname failed!\n");
        return VFS_ERROR;
    }
    return diskID;
}

VOID OsSetUsbStatus(UINT32 diskID)
{
    if (diskID < SYS_MAX_DISK) {
        g_usbMode |= (1u << diskID) & UINT_MAX;
    }
}

VOID OsClearUsbStatus(UINT32 diskID)
{
    if (diskID < SYS_MAX_DISK) {
        g_usbMode &= ~((1u << diskID) & UINT_MAX);
    }
}

#ifdef LOSCFG_FS_FAT_CACHE
static BOOL GetDiskUsbStatus(UINT32 diskID)
{
    return (g_usbMode & (1u << diskID)) ? TRUE : FALSE;
}
#endif

los_disk *get_disk(INT32 id)
{
    if ((id >= 0) && (id < SYS_MAX_DISK)) {
        return &g_sysDisk[id];
    }

    return NULL;
}

los_part *get_part(INT32 id)
{
    if ((id >= 0) && (id < SYS_MAX_PART)) {
        return &g_sysPart[id];
    }

    return NULL;
}

static UINT64 GetFirstPartStart(const los_part *part)
{
    los_part *firstPart = NULL;
    los_disk *disk = get_disk((INT32)part->disk_id);
    firstPart = (disk == NULL) ? NULL : LOS_DL_LIST_ENTRY(disk->head.pstNext, los_part, list);
    return (firstPart == NULL) ? 0 : firstPart->sector_start;
}

static VOID DiskPartAddToDisk(los_disk *disk, los_part *part)
{
    part->disk_id = disk->disk_id;
    part->part_no_disk = disk->part_count;
    LOS_ListTailInsert(&disk->head, &part->list);
    disk->part_count++;
}

static VOID DiskPartDelFromDisk(los_disk *disk, los_part *part)
{
    LOS_ListDelete(&part->list);
    disk->part_count--;
}

static los_part *DiskPartAllocate(struct inode *dev, UINT64 start, UINT64 count)
{
    UINT32 i;
    los_part *part = get_part(0); /* traversing from the beginning of the array */

    for (i = 0; i < SYS_MAX_PART; i++) {
        if (part->dev == NULL) {
            part->part_id = i;
            part->part_no_mbr = 0;
            part->dev = dev;
            part->sector_start = start;
            part->sector_count = count;
            part->part_name = NULL;
            LOS_ListInit(&part->list);

            return part;
        }
        part++;
    }

    return NULL;
}

static VOID DiskPartRelease(los_part *part)
{
    part->dev = NULL;
    part->part_no_disk = 0;
    part->part_no_mbr = 0;
    if (part->part_name != NULL) {
        free(part->part_name);
        part->part_name = NULL;
    }
}

/*
 * name is a combination of disk_name, 'p' and part_count, such as "/dev/mmcblk0p0"
 * disk_name : DISK_NAME + 1
 * 'p' : 1
 * part_count: 1
 */
#define DEV_NAME_BUFF_SIZE  (DISK_NAME + 3)

static INT32 DiskAddPart(los_disk *disk, UINT64 sectorStart, UINT64 sectorCount)
{
    CHAR devName[DEV_NAME_BUFF_SIZE];
    struct inode *diskDev = NULL;
    struct inode *partDev = NULL;
    los_part *part = NULL;
    INT32 ret;
    struct inode_search_s desc;

    if ((disk == NULL) || (disk->disk_status == STAT_UNUSED) ||
        (disk->dev == NULL)) {
        return VFS_ERROR;
    }

    if ((sectorCount > disk->sector_count) || ((disk->sector_count - sectorCount) < sectorStart)) {
        PRINT_ERR("DiskAddPart failed: sector start is %llu, sector count is %llu\n", sectorStart, sectorCount);
        return VFS_ERROR;
    }

    ret = snprintf_s(devName, sizeof(devName), sizeof(devName) - 1, "%s%c%u",
                     (disk->disk_name == NULL ? "null" : disk->disk_name), 'p', disk->part_count);
    if (ret < 0) {
        return VFS_ERROR;
    }

    diskDev = disk->dev;
    if (register_blockdriver(devName, diskDev->u.i_bops, RWE_RW_RW, diskDev->i_private)) {
        PRINT_ERR("DiskAddPart : register %s fail!\n", devName);
        return VFS_ERROR;
    }

    SETUP_SEARCH(&desc, devName, false);
    ret = inode_find(&desc);
    if (ret < 0) {
        PRINT_ERR("DiskAddPart : find %s fail!\n", devName);
        return VFS_ERROR;
    }
    partDev = desc.node;

    PRINTK("DiskAddPart : register %s ok!\n", devName);

    part = DiskPartAllocate(partDev, sectorStart, sectorCount);
    inode_release(partDev);

    if (part == NULL) {
        (VOID)unregister_blockdriver(devName);
        return VFS_ERROR;
    }

    DiskPartAddToDisk(disk, part);
    if (disk->type == EMMC) {
        part->type = EMMC;
    }
    return (INT32)part->part_id;
}

static INT32 DiskDivide(los_disk *disk, struct disk_divide_info *info)
{
    UINT32 i;
    INT32 ret;

    disk->type = info->part[0].type;
    for (i = 0; i < info->part_count; i++) {
        if (info->sector_count < info->part[i].sector_start) {
            return VFS_ERROR;
        }
        if (info->part[i].sector_count > (info->sector_count - info->part[i].sector_start)) {
            PRINT_ERR("Part[%u] sector_start:%llu, sector_count:%llu, exceed emmc sector_count:%llu.\n", i,
                      info->part[i].sector_start, info->part[i].sector_count,
                      (info->sector_count - info->part[i].sector_start));
            info->part[i].sector_count = info->sector_count - info->part[i].sector_start;
            PRINT_ERR("Part[%u] sector_count change to %llu.\n", i, info->part[i].sector_count);

            ret = DiskAddPart(disk, info->part[i].sector_start, info->part[i].sector_count);
            if (ret == VFS_ERROR) {
                return VFS_ERROR;
            }
            break;
        }
        ret = DiskAddPart(disk, info->part[i].sector_start, info->part[i].sector_count);
        if (ret == VFS_ERROR) {
            return VFS_ERROR;
        }
    }

    return ENOERR;
}

static CHAR GPTPartitionTypeRecognition(const CHAR *parBuf)
{
    const CHAR *buf = parBuf;
    const CHAR *fsType = "FAT";
    const CHAR *str = "\xEB\x52\x90" "NTFS    "; /* NTFS Boot entry point */

    if (((LD_DWORD_DISK(&buf[BS_FILSYSTEMTYPE32]) & BS_FS_TYPE_MASK) == BS_FS_TYPE_VALUE) ||
        (strncmp(&buf[BS_FILSYSTYPE], fsType, strlen(fsType)) == 0)) {
        return BS_FS_TYPE_FAT;
    } else if (strncmp(&buf[BS_JMPBOOT], str, strlen(str)) == 0) {
        return BS_FS_TYPE_NTFS;
    }

    return ENOERR;
}

static INT32 DiskPartitionMemZalloc(size_t boundary, size_t size, CHAR **gptBuf, CHAR **partitionBuf)
{
    CHAR *buffer1 = NULL;
    CHAR *buffer2 = NULL;

    buffer1 = (CHAR *)memalign(boundary, size);
    if (buffer1 == NULL) {
        PRINT_ERR("%s buffer1 malloc %lu failed! %d\n", __FUNCTION__, size, __LINE__);
        return VFS_ERROR;
    }
    buffer2 = (CHAR *)memalign(boundary, size);
    if (buffer2 == NULL) {
        PRINT_ERR("%s buffer2 malloc %lu failed! %d\n", __FUNCTION__, size, __LINE__);
        free(buffer1);
        return VFS_ERROR;
    }
    (VOID)memset_s(buffer1, size, 0, size);
    (VOID)memset_s(buffer2, size, 0, size);

    *gptBuf = buffer1;
    *partitionBuf = buffer2;

    return ENOERR;
}

static INT32 GPTInfoGet(struct inode *blkDrv, CHAR *gptBuf)
{
    INT32 ret;

    ret = blkDrv->u.i_bops->read(blkDrv, (UINT8 *)gptBuf, 1, 1); /* Read the device first sector */
    if (ret != 1) { /* Read failed */
        PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
        return -EIO;
    }

    if (!VERIFY_GPT(gptBuf)) {
        PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
        return VFS_ERROR;
    }

    return ENOERR;
}

static INT32 OsGPTPartitionRecognitionSub(struct disk_divide_info *info, const CHAR *partitionBuf,
                                          UINT32 *partitionCount, UINT64 partitionStart, UINT64 partitionEnd)
{
    CHAR partitionType;

    if (VERIFY_FS(partitionBuf)) {
        partitionType = GPTPartitionTypeRecognition(partitionBuf);
        if (partitionType) {
            if (*partitionCount >= MAX_DIVIDE_PART_PER_DISK) {
                return VFS_ERROR;
            }
            info->part[*partitionCount].type = partitionType;
            info->part[*partitionCount].sector_start = partitionStart;
            info->part[*partitionCount].sector_count = (partitionEnd - partitionStart) + 1;
            (*partitionCount)++;
        } else {
            PRINT_ERR("The partition type is not allowed to use!\n");
        }
    } else {
        PRINT_ERR("Do not support the partition type!\n");
    }
    return ENOERR;
}

static INT32 OsGPTPartitionRecognition(struct inode *blkDrv, struct disk_divide_info *info,
                                       const CHAR *gptBuf, CHAR *partitionBuf, UINT32 *partitionCount)
{
    UINT32 j;
    INT32 ret = VFS_ERROR;
    UINT64 partitionStart, partitionEnd;

    for (j = 0; j < PAR_ENTRY_NUM_PER_SECTOR; j++) {
        if (!VERITY_AVAILABLE_PAR(&gptBuf[j * TABLE_SIZE])) {
            PRINTK("The partition type is ESP or MSR!\n");
            continue;
        }

        if (!VERITY_PAR_VALID(&gptBuf[j * TABLE_SIZE])) {
            return VFS_ERROR;
        }

        partitionStart = LD_QWORD_DISK(&gptBuf[(j * TABLE_SIZE) + GPT_PAR_START_OFFSET]);
        partitionEnd = LD_QWORD_DISK(&gptBuf[(j * TABLE_SIZE) + GPT_PAR_END_OFFSET]);
        if ((partitionStart >= partitionEnd) || (partitionEnd > info->sector_count)) {
            PRINT_ERR("GPT partition %u recognition failed : partitionStart = %llu, partitionEnd = %llu\n",
                      j, partitionStart, partitionEnd);
            return VFS_ERROR;
        }

        (VOID)memset_s(partitionBuf, info->sector_size, 0, info->sector_size);
        ret = blkDrv->u.i_bops->read(blkDrv, (UINT8 *)partitionBuf, partitionStart, 1);
        if (ret != 1) { /* read failed */
            PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
            return -EIO;
        }

        ret = OsGPTPartitionRecognitionSub(info, partitionBuf, partitionCount, partitionStart, partitionEnd);
        if (ret != ENOERR) {
            return VFS_ERROR;
        }
    }

    return ret;
}

static INT32 DiskGPTPartitionRecognition(struct inode *blkDrv, struct disk_divide_info *info)
{
    CHAR *gptBuf = NULL;
    CHAR *partitionBuf = NULL;
    UINT32 tableNum, i, index;
    UINT32 partitionCount = 0;
    INT32 ret;

    ret = DiskPartitionMemZalloc(MEM_ADDR_ALIGN_BYTE, info->sector_size, &gptBuf, &partitionBuf);
    if (ret != ENOERR) {
        return VFS_ERROR;
    }

    ret = GPTInfoGet(blkDrv, gptBuf);
    if (ret < 0) {
        goto OUT_WITH_MEM;
    }

    tableNum = LD_DWORD_DISK(&gptBuf[TABLE_NUM_OFFSET]);
    if (tableNum > TABLE_MAX_NUM) {
        tableNum = TABLE_MAX_NUM;
    }

    index = (tableNum % PAR_ENTRY_NUM_PER_SECTOR) ? ((tableNum / PAR_ENTRY_NUM_PER_SECTOR) + 1) :
            (tableNum / PAR_ENTRY_NUM_PER_SECTOR);

    for (i = 0; i < index; i++) {
        (VOID)memset_s(gptBuf, info->sector_size, 0, info->sector_size);
        ret = blkDrv->u.i_bops->read(blkDrv, (UINT8 *)gptBuf, TABLE_START_SECTOR + i, 1);
        if (ret != 1) { /* read failed */
            PRINT_ERR("%s %d\n", __FUNCTION__, __LINE__);
            ret = -EIO;
            goto OUT_WITH_MEM;
        }

        ret = OsGPTPartitionRecognition(blkDrv, info, gptBuf, partitionBuf, &partitionCount);
        if (ret < 0) {
            if (ret == VFS_ERROR) {
                ret = (INT32)partitionCount;
            }
            goto OUT_WITH_MEM;
        }
    }
    ret = (INT32)partitionCount;

OUT_WITH_MEM:
    free(gptBuf);
    free(partitionBuf);
    return ret;
}

static INT32 OsMBRInfoGet(struct inode *blkDrv, CHAR *mbrBuf)
{
    INT32 ret;

    /* read MBR, start from sector 0, length is 1 sector */
    ret = blkDrv->u.i_bops->read(blkDrv, (UINT8 *)mbrBuf, 0, 1);
    if (ret != 1) { /* read failed */
        PRINT_ERR("driver read return error: %d\n", ret);
        return -EIO;
    }

    /* Check boot record signature. */
    if (LD_WORD_DISK(&mbrBuf[BS_SIG55AA]) != BS_SIG55AA_VALUE) {
        return VFS_ERROR;
    }

    return ENOERR;
}

static INT32 OsEBRInfoGet(struct inode *blkDrv, const struct disk_divide_info *info,
                          CHAR *ebrBuf, const CHAR *mbrBuf)
{
    INT32 ret;

    if (VERIFY_FS(mbrBuf)) {
        if (info->sector_count <= LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_START_OFFSET])) {
            return VFS_ERROR;
        }

        ret = blkDrv->u.i_bops->read(blkDrv, (UINT8 *)ebrBuf,
                                     LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_START_OFFSET]), 1);
        if ((ret != 1) || (!VERIFY_FS(ebrBuf))) { /* read failed */
            PRINT_ERR("OsEBRInfoGet, verify_fs error, ret = %d\n", ret);
            return -EIO;
        }
    }

    return ENOERR;
}

static INT32 OsPrimaryPartitionRecognition(const CHAR *mbrBuf, struct disk_divide_info *info,
                                           INT32 *extendedPos, INT32 *mbrCount)
{
    INT32 i;
    CHAR mbrPartitionType;
    INT32 extendedFlag = 0;
    INT32 count = 0;

    for (i = 0; i < MAX_PRIMARY_PART_PER_DISK; i++) {
        mbrPartitionType = mbrBuf[PAR_OFFSET + PAR_TYPE_OFFSET + (i * PAR_TABLE_SIZE)];
        if (mbrPartitionType) {
            info->part[i].type = mbrPartitionType;
            info->part[i].sector_start = LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_START_OFFSET + (i * PAR_TABLE_SIZE)]);
            info->part[i].sector_count = LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_COUNT_OFFSET + (i * PAR_TABLE_SIZE)]);
            if ((mbrPartitionType == EXTENDED_PAR) || (mbrPartitionType == EXTENDED_8G)) {
                extendedFlag = 1;
                *extendedPos = i;
                continue;
            }
            count++;
        }
    }
    *mbrCount = count;

    return extendedFlag;
}

static INT32 OsLogicalPartitionRecognition(struct inode *blkDrv, struct disk_divide_info *info,
                                           UINT32 extendedAddress, CHAR *ebrBuf, INT32 mbrCount)
{
    INT32 ret;
    UINT32 extendedOffset = 0;
    CHAR ebrPartitionType;
    INT32 ebrCount = 0;

    do {
        (VOID)memset_s(ebrBuf, info->sector_size, 0, info->sector_size);
        if (((UINT64)(extendedAddress) + extendedOffset) >= info->sector_count) {
            PRINT_ERR("extended partition is out of disk range: extendedAddress = %u, extendedOffset = %u\n",
                      extendedAddress, extendedOffset);
            break;
        }
        ret = blkDrv->u.i_bops->read(blkDrv, (UINT8 *)ebrBuf,
                                     extendedAddress + extendedOffset, 1);
        if (ret != 1) { /* read failed */
            PRINT_ERR("driver read return error: %d, extendedAddress = %u, extendedOffset = %u\n", ret,
                      extendedAddress, extendedOffset);
            return -EIO;
        }
        ebrPartitionType = ebrBuf[PAR_OFFSET + PAR_TYPE_OFFSET];
        if (ebrPartitionType && ((mbrCount + ebrCount) < MAX_DIVIDE_PART_PER_DISK)) {
            info->part[MAX_PRIMARY_PART_PER_DISK + ebrCount].type = ebrPartitionType;
            info->part[MAX_PRIMARY_PART_PER_DISK + ebrCount].sector_start = extendedAddress + extendedOffset +
                                                                            LD_DWORD_DISK(&ebrBuf[PAR_OFFSET +
                                                                                                  PAR_START_OFFSET]);
            info->part[MAX_PRIMARY_PART_PER_DISK + ebrCount].sector_count = LD_DWORD_DISK(&ebrBuf[PAR_OFFSET +
                                                                                                  PAR_COUNT_OFFSET]);
            ebrCount++;
        }
        extendedOffset = LD_DWORD_DISK(&ebrBuf[PAR_OFFSET + PAR_START_OFFSET + PAR_TABLE_SIZE]);
    } while ((ebrBuf[PAR_OFFSET + PAR_TYPE_OFFSET + PAR_TABLE_SIZE] != 0) &&
             ((mbrCount + ebrCount) < MAX_DIVIDE_PART_PER_DISK));

    return ebrCount;
}

static INT32 DiskPartitionRecognition(struct inode *blkDrv, struct disk_divide_info *info)
{
    INT32 ret;
    INT32 extendedFlag;
    INT32 extendedPos = 0;
    INT32 mbrCount = 0;
    UINT32 extendedAddress;
    CHAR *mbrBuf = NULL;
    CHAR *ebrBuf = NULL;

    if ((blkDrv == NULL) || (blkDrv->u.i_bops == NULL) || (blkDrv->u.i_bops->read == NULL)) {
        return VFS_ERROR;
    }

    ret = DiskPartitionMemZalloc(MEM_ADDR_ALIGN_BYTE, info->sector_size, &mbrBuf, &ebrBuf);
    if (ret != ENOERR) {
        return ret;
    }

    ret = OsMBRInfoGet(blkDrv, mbrBuf);
    if (ret < 0) {
        goto OUT_WITH_MEM;
    }

    /* The partition type is GPT */
    if (mbrBuf[PARTION_MODE_BTYE] == (CHAR)PARTION_MODE_GPT) {
        ret = DiskGPTPartitionRecognition(blkDrv, info);
        goto OUT_WITH_MEM;
    }

    ret = OsEBRInfoGet(blkDrv, info, ebrBuf, mbrBuf);
    if (ret < 0) {
        ret = 0; /* no mbr */
        goto OUT_WITH_MEM;
    }

    extendedFlag = OsPrimaryPartitionRecognition(mbrBuf, info, &extendedPos, &mbrCount);
    if (extendedFlag) {
        extendedAddress = LD_DWORD_DISK(&mbrBuf[PAR_OFFSET + PAR_START_OFFSET + (extendedPos * PAR_TABLE_SIZE)]);
        ret = OsLogicalPartitionRecognition(blkDrv, info, extendedAddress, ebrBuf, mbrCount);
        if (ret <= 0) {
            goto OUT_WITH_MEM;
        }
    }
    ret += mbrCount;

OUT_WITH_MEM:
    free(ebrBuf);
    free(mbrBuf);
    return ret;
}

INT32 DiskPartitionRegister(los_disk *disk)
{
    INT32 count;
    UINT32 i, partSize;
    los_part *part = NULL;
    struct disk_divide_info parInfo;

    /* Fill disk_divide_info structure to set partition's infomation. */
    (VOID)memset_s(parInfo.part, sizeof(parInfo.part), 0, sizeof(parInfo.part));
    partSize = sizeof(parInfo.part) / sizeof(parInfo.part[0]);

    parInfo.sector_size = disk->sector_size;
    parInfo.sector_count = disk->sector_count;
    count = DiskPartitionRecognition(disk->dev, &parInfo);
    if (count < 0) {
        return VFS_ERROR;
    }
    parInfo.part_count = count;
    if (count == 0) {
        part = get_part(DiskAddPart(disk, 0, disk->sector_count));
        if (part == NULL) {
            return VFS_ERROR;
        }
        part->part_no_mbr = 0;

        PRINTK("No MBR detected.\n");
        return ENOERR;
    }

    for (i = 0; i < partSize; i++) {
        /* Read the disk_divide_info structure to get partition's infomation. */
        if ((parInfo.part[i].type != 0) && (parInfo.part[i].type != EXTENDED_PAR) &&
            (parInfo.part[i].type != EXTENDED_8G)) {
            part = get_part(DiskAddPart(disk, parInfo.part[i].sector_start, parInfo.part[i].sector_count));
            if (part == NULL) {
                return VFS_ERROR;
            }
            part->part_no_mbr = i + 1;
            part->filesystem_type = parInfo.part[i].type;
        }
    }

    return ENOERR;
}

INT32 los_disk_read(INT32 drvID, VOID *buf, UINT64 sector, UINT32 count)
{
#ifdef LOSCFG_FS_FAT_CACHE
    UINT32 len;
#endif
    INT32 result = VFS_ERROR;
    los_disk *disk = get_disk(drvID);

    if ((buf == NULL) || (count == 0)) { /* buff equal to NULL or count equal to 0 */
        return result;
    }

    if (disk == NULL) {
        return result;
    }

    DISK_LOCK(&disk->disk_mutex);

    if (disk->disk_status != STAT_INUSED) {
        goto ERROR_HANDLE;
    }

    if ((count > disk->sector_count) || ((disk->sector_count - count) < sector)) {
        goto ERROR_HANDLE;
    }

#ifdef LOSCFG_FS_FAT_CACHE
    if (disk->bcache != NULL) {
        if (((UINT64)(disk->bcache->sectorSize) * count) > UINT_MAX) {
            goto ERROR_HANDLE;
        }
        len = disk->bcache->sectorSize * count;
        result = BlockCacheRead(disk->bcache, (UINT8 *)buf, &len, sector);
        if (result != ENOERR) {
            PRINT_ERR("los_disk_read read err = %d, sector = %llu, len = %u\n", result, sector, len);
        }
    } else {
#endif
    if ((disk->dev != NULL) && (disk->dev->u.i_bops != NULL) && (disk->dev->u.i_bops->read != NULL)) {
        result = disk->dev->u.i_bops->read(disk->dev, (UINT8 *)buf, sector, count);
        if (result == (INT32)count) {
            result = ENOERR;
        }
    }
#ifdef LOSCFG_FS_FAT_CACHE
    }
#endif

    if (result != ENOERR) {
        goto ERROR_HANDLE;
    }

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

INT32 los_disk_write(INT32 drvID, const VOID *buf, UINT64 sector, UINT32 count)
{
#ifdef LOSCFG_FS_FAT_CACHE
    UINT32 len;
#endif
    INT32 result = VFS_ERROR;
    los_disk *disk = get_disk(drvID);
    if (disk == NULL) {
        return result;
    }

    if ((buf == NULL) || (count == 0)) { /* buff equal to NULL or count equal to 0 */
        return result;
    }

    DISK_LOCK(&disk->disk_mutex);

    if (disk->disk_status != STAT_INUSED) {
        goto ERROR_HANDLE;
    }

    if ((count > disk->sector_count) || ((disk->sector_count - count) < sector)) {
        goto ERROR_HANDLE;
    }

#ifdef LOSCFG_FS_FAT_CACHE
    if (disk->bcache != NULL) {
        if (((UINT64)(disk->bcache->sectorSize) * count) > UINT_MAX) {
            goto ERROR_HANDLE;
        }
        len = disk->bcache->sectorSize * count;
        result = BlockCacheWrite(disk->bcache, (const UINT8 *)buf, &len, sector);
        if (result != ENOERR) {
            PRINT_ERR("los_disk_write write err = %d, sector = %llu, len = %u\n", result, sector, len);
        }
    } else {
#endif
    if ((disk->dev != NULL) && (disk->dev->u.i_bops != NULL) && (disk->dev->u.i_bops->write != NULL)) {
        result = disk->dev->u.i_bops->write(disk->dev, (UINT8 *)buf, sector, count);
        if (result == (INT32)count) {
            result = ENOERR;
        }
    }
#ifdef LOSCFG_FS_FAT_CACHE
    }
#endif

    if (result != ENOERR) {
        goto ERROR_HANDLE;
    }

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

INT32 los_disk_ioctl(INT32 drvID, INT32 cmd, VOID *buf)
{
    struct geometry info;
    los_disk *disk = get_disk(drvID);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    DISK_LOCK(&disk->disk_mutex);

    if ((disk->dev == NULL) || (disk->disk_status != STAT_INUSED)) {
        goto ERROR_HANDLE;
    }

    if (cmd == DISK_CTRL_SYNC) {
        DISK_UNLOCK(&disk->disk_mutex);
        return ENOERR;
    }

    if (buf == NULL) {
        goto ERROR_HANDLE;
    }

    (VOID)memset_s(&info, sizeof(info), 0, sizeof(info));
    if ((disk->dev->u.i_bops == NULL) || (disk->dev->u.i_bops->geometry == NULL) ||
        (disk->dev->u.i_bops->geometry(disk->dev, &info) != 0)) {
        goto ERROR_HANDLE;
    }

    if (cmd == DISK_GET_SECTOR_COUNT) {
        *(UINT64 *)buf = info.geo_nsectors;
        if (info.geo_nsectors == 0) {
            goto ERROR_HANDLE;
        }
    } else if (cmd == DISK_GET_SECTOR_SIZE) {
        *(size_t *)buf = info.geo_sectorsize;
    } else if (cmd == DISK_GET_BLOCK_SIZE) { /* Get erase block size in unit of sectors (UINT32) */
        /* Block Num SDHC == 512, SD can be set to 512 or other */
        *(size_t *)buf = DISK_MAX_SECTOR_SIZE / info.geo_sectorsize;
    } else {
        goto ERROR_HANDLE;
    }

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

INT32 los_part_read(INT32 pt, VOID *buf, UINT64 sector, UINT32 count)
{
    const los_part *part = get_part(pt);
    los_disk *disk = NULL;
    INT32 ret;

    if (part == NULL) {
        return VFS_ERROR;
    }

    disk = get_disk((INT32)part->disk_id);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    DISK_LOCK(&disk->disk_mutex);
    if ((part->dev == NULL) || (disk->disk_status != STAT_INUSED)) {
        goto ERROR_HANDLE;
    }

    if (count > part->sector_count) {
        PRINT_ERR("los_part_read failed, invaild count, count = %u\n", count);
        goto ERROR_HANDLE;
    }

    /* Read from absolute sector. */
    if (part->type == EMMC) {
        if ((disk->sector_count - part->sector_start) > sector) {
            sector += part->sector_start;
        } else {
            PRINT_ERR("los_part_read failed, invaild sector, sector = %llu\n", sector);
            goto ERROR_HANDLE;
        }
    }

    if ((sector >= GetFirstPartStart(part)) &&
        (((sector + count) > (part->sector_start + part->sector_count)) || (sector < part->sector_start))) {
        PRINT_ERR("los_part_read error, sector = %llu, count = %u, part->sector_start = %llu, "
                  "part->sector_count = %llu\n", sector, count, part->sector_start, part->sector_count);
        goto ERROR_HANDLE;
    }

    ret = los_disk_read((INT32)part->disk_id, buf, sector, count);
    if (ret < 0) {
        goto ERROR_HANDLE;
    }

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

INT32 los_part_write(INT32 pt, VOID *buf, UINT64 sector, UINT32 count)
{
    const los_part *part = get_part(pt);
    los_disk *disk = NULL;
    INT32 ret;

    if (part == NULL) {
        return VFS_ERROR;
    }

    disk = get_disk((INT32)part->disk_id);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    DISK_LOCK(&disk->disk_mutex);
    if ((part->dev == NULL) || (disk->disk_status != STAT_INUSED)) {
        goto ERROR_HANDLE;
    }

    if (count > part->sector_count) {
        PRINT_ERR("los_part_write failed, invaild count, count = %u\n", count);
        goto ERROR_HANDLE;
    }

    /* Write to absolute sector. */
    if (part->type == EMMC) {
        if ((disk->sector_count - part->sector_start) > sector) {
            sector += part->sector_start;
        } else {
            PRINT_ERR("los_part_write failed, invaild sector, sector = %llu\n", sector);
            goto ERROR_HANDLE;
        }
    }

    if ((sector >= GetFirstPartStart(part)) &&
        (((sector + count) > (part->sector_start + part->sector_count)) || (sector < part->sector_start))) {
        PRINT_ERR("los_part_write, sector = %llu, count = %u, part->sector_start = %llu, "
                  "part->sector_count = %llu\n", sector, count, part->sector_start, part->sector_count);
        goto ERROR_HANDLE;
    }

    ret = los_disk_write((INT32)part->disk_id, (const VOID *)buf, sector, count);
    if (ret < 0) {
        goto ERROR_HANDLE;
    }

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

#define GET_ERASE_BLOCK_SIZE 0x2

INT32 los_part_ioctl(INT32 pt, INT32 cmd, VOID *buf)
{
    struct geometry info;
    los_part *part = get_part(pt);
    los_disk *disk = NULL;

    if (part == NULL) {
        return VFS_ERROR;
    }

    disk = get_disk((INT32)part->disk_id);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    DISK_LOCK(&disk->disk_mutex);
    if ((part->dev == NULL) || (disk->disk_status != STAT_INUSED)) {
        goto ERROR_HANDLE;
    }

    if (cmd == DISK_CTRL_SYNC) {
        DISK_UNLOCK(&disk->disk_mutex);
        return ENOERR;
    }

    if (buf == NULL) {
        goto ERROR_HANDLE;
    }

    (VOID)memset_s(&info, sizeof(info), 0, sizeof(info));
    if ((part->dev->u.i_bops == NULL) || (part->dev->u.i_bops->geometry == NULL) ||
        (part->dev->u.i_bops->geometry(part->dev, &info) != 0)) {
        goto ERROR_HANDLE;
    }

    if (cmd == DISK_GET_SECTOR_COUNT) {
        *(UINT64 *)buf = part->sector_count;
        if (*(UINT64 *)buf == 0) {
            goto ERROR_HANDLE;
        }
    } else if (cmd == DISK_GET_SECTOR_SIZE) {
        *(size_t *)buf = info.geo_sectorsize;
    } else if (cmd == DISK_GET_BLOCK_SIZE) { /* Get erase block size in unit of sectors (UINT32) */
        if ((part->dev->u.i_bops->ioctl == NULL) ||
            (part->dev->u.i_bops->ioctl(part->dev, GET_ERASE_BLOCK_SIZE, (UINTPTR)buf) != 0)) {
            goto ERROR_HANDLE;
        }
    } else {
        goto ERROR_HANDLE;
    }

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

#ifdef LOSCFG_FS_FAT_CACHE
static VOID DiskCacheThreadInit(UINT32 diskID, OsBcache *bc)
{
    bc->prereadFun = NULL;

    if (GetDiskUsbStatus(diskID) == FALSE) {
        if (BcacheAsyncPrereadInit(bc) == LOS_OK) {
            bc->prereadFun = ResumeAsyncPreread;
        }

#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD
        BcacheSyncThreadInit(bc, diskID);
#endif
    }

    if (OsReHookFuncAddDiskRef != NULL) {
        (VOID)OsReHookFuncAddDiskRef((StorageHookFunction)OsSdSync, (VOID *)0);
        (VOID)OsReHookFuncAddDiskRef((StorageHookFunction)OsSdSync, (VOID *)1);
    }
}

static OsBcache *DiskCacheInit(UINT32 diskID, const struct geometry *diskInfo, struct inode *blkDriver)
{
#define SECTOR_SIZE 512

    OsBcache *bc = NULL;
    UINT32 sectorPerBlock = diskInfo->geo_sectorsize / SECTOR_SIZE;
    if (sectorPerBlock != 0) {
        sectorPerBlock = g_uwFatSectorsPerBlock / sectorPerBlock;
        if (sectorPerBlock != 0) {
            bc = BlockCacheInit(blkDriver, diskInfo->geo_sectorsize, sectorPerBlock,
                                g_uwFatBlockNums, diskInfo->geo_nsectors / sectorPerBlock);
        }
    }

    if (bc == NULL) {
        PRINT_ERR("disk_init : disk have not init bcache cache!\n");
        return NULL;
    }

    DiskCacheThreadInit(diskID, bc);
    return bc;
}

static VOID DiskCacheDeinit(los_disk *disk)
{
    UINT32 diskID = disk->disk_id;
    if (GetDiskUsbStatus(diskID) == FALSE) {
        if (BcacheAsyncPrereadDeinit(disk->bcache) != LOS_OK) {
            PRINT_ERR("Blib async preread deinit failed in %s, %d\n", __FUNCTION__, __LINE__);
        }
#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD
        BcacheSyncThreadDeinit(disk->bcache);
#endif
    }

    BlockCacheDeinit(disk->bcache);
    disk->bcache = NULL;

    if (OsReHookFuncDelDiskRef != NULL) {
        (VOID)OsReHookFuncDelDiskRef((StorageHookFunction)OsSdSync);
    }
}
#endif

static VOID DiskStructInit(const CHAR *diskName, INT32 diskID, const struct geometry *diskInfo,
                           struct inode *blkDriver, los_disk *disk)
{
    size_t nameLen;
    disk->disk_id = diskID;
    disk->dev = blkDriver;
    disk->sector_start = 0;
    disk->sector_size = diskInfo->geo_sectorsize;
    disk->sector_count = diskInfo->geo_nsectors;

    nameLen = strlen(diskName); /* caller los_disk_init has chek name */

    if (disk->disk_name != NULL) {
        LOS_MemFree(m_aucSysMem0, disk->disk_name);
        disk->disk_name = NULL;
    }

    disk->disk_name = LOS_MemAlloc(m_aucSysMem0, (nameLen + 1));
    if (disk->disk_name == NULL) {
        PRINT_ERR("DiskStructInit alloc memory failed.\n");
        return;
    }

    if (strncpy_s(disk->disk_name, (nameLen + 1), diskName, nameLen) != EOK) {
        PRINT_ERR("DiskStructInit strncpy_s failed.\n");
        return;
    }
    disk->disk_name[nameLen] = '\0';
    LOS_ListInit(&disk->head);
}

static INT32 DiskDivideAndPartitionRegister(struct disk_divide_info *info, los_disk *disk)
{
    INT32 ret;

    if (info != NULL) {
        ret = DiskDivide(disk, info);
        if (ret != ENOERR) {
            PRINT_ERR("DiskDivide failed, ret = %d\n", ret);
            return ret;
        }
    } else {
        ret = DiskPartitionRegister(disk);
        if (ret != ENOERR) {
            PRINT_ERR("DiskPartitionRegister failed, ret = %d\n", ret);
            return ret;
        }
    }
    return ENOERR;
}

static INT32 DiskDeinit(los_disk *disk)
{
    los_part *part = NULL;
    char *diskName = NULL;
    CHAR devName[DEV_NAME_BUFF_SIZE];
    INT32 ret;

    if (LOS_ListEmpty(&disk->head) == FALSE) {
        part = LOS_DL_LIST_ENTRY(disk->head.pstNext, los_part, list);
        while (&part->list != &disk->head) {
            diskName = (disk->disk_name == NULL) ? "null" : disk->disk_name;
            ret = snprintf_s(devName, sizeof(devName), sizeof(devName) - 1, "%s%c%d",
                             diskName, 'p', disk->part_count - 1);
            if (ret < 0) {
                return -ENAMETOOLONG;
            }
            DiskPartDelFromDisk(disk, part);
            (VOID)unregister_blockdriver(devName);
            DiskPartRelease(part);

            part = LOS_DL_LIST_ENTRY(disk->head.pstNext, los_part, list);
        }
    }

    DISK_LOCK(&disk->disk_mutex);

#ifdef LOSCFG_FS_FAT_CACHE
    DiskCacheDeinit(disk);
#endif

    disk->dev = NULL;
    DISK_UNLOCK(&disk->disk_mutex);
    (VOID)unregister_blockdriver(disk->disk_name);
    if (disk->disk_name != NULL) {
        LOS_MemFree(m_aucSysMem0, disk->disk_name);
        disk->disk_name = NULL;
    }
    ret = pthread_mutex_destroy(&disk->disk_mutex);
    if (ret != 0) {
        PRINT_ERR("%s %d, mutex destroy failed, ret = %d\n", __FUNCTION__, __LINE__, ret);
        return -EFAULT;
    }

    disk->disk_status = STAT_UNUSED;

    return ENOERR;
}

static VOID OsDiskInitSub(const CHAR *diskName, INT32 diskID, los_disk *disk,
                          struct geometry *diskInfo, struct inode *blkDriver)
{
    pthread_mutexattr_t attr;
#ifdef LOSCFG_FS_FAT_CACHE
    OsBcache *bc = DiskCacheInit((UINT32)diskID, diskInfo, blkDriver);
    disk->bcache = bc;
#endif

    (VOID)pthread_mutexattr_init(&attr);
    attr.type = PTHREAD_MUTEX_RECURSIVE;
    (VOID)pthread_mutex_init(&disk->disk_mutex, &attr);

    DiskStructInit(diskName, diskID, diskInfo, blkDriver, disk);
}

INT32 los_disk_init(const CHAR *diskName, const struct block_operations *bops,
                    VOID *priv, INT32 diskID, VOID *info)
{
    struct geometry diskInfo;
    struct inode *blkDriver = NULL;
    los_disk *disk = get_disk(diskID);
    struct inode_search_s desc;
    INT32 ret;

    if ((diskName == NULL) || (disk == NULL) ||
        (disk->disk_status != STAT_UNREADY) || (strlen(diskName) > DISK_NAME)) {
        return VFS_ERROR;
    }

    if (register_blockdriver(diskName, bops, RWE_RW_RW, priv) != 0) {
        PRINT_ERR("disk_init : register %s fail!\n", diskName);
        return VFS_ERROR;
    }

    SETUP_SEARCH(&desc, diskName, false);
    ret = inode_find(&desc);
    if (ret < 0) {
        PRINT_ERR("disk_init : find %s fail!\n", diskName);
        ret = ENOENT;
        goto DISK_FIND_ERROR;
    }
    blkDriver = desc.node;

    if ((blkDriver->u.i_bops == NULL) || (blkDriver->u.i_bops->geometry == NULL) ||
        (blkDriver->u.i_bops->geometry(blkDriver, &diskInfo) != 0)) {
        goto DISK_BLKDRIVER_ERROR;
    }
    if (diskInfo.geo_sectorsize < DISK_MAX_SECTOR_SIZE) {
        goto DISK_BLKDRIVER_ERROR;
    }

    PRINTK("disk_init : register %s ok!\n", diskName);

    OsDiskInitSub(diskName, diskID, disk, &diskInfo, blkDriver);
    inode_release(blkDriver);

    if (DiskDivideAndPartitionRegister(info, disk) != ENOERR) {
        (VOID)DiskDeinit(disk);
        return VFS_ERROR;
    }

    disk->disk_status = STAT_INUSED;
    if (info != NULL) {
        disk->type = EMMC;
    } else {
        disk->type = OTHERS;
    }
    return ENOERR;

DISK_BLKDRIVER_ERROR:
    PRINT_ERR("disk_init : register %s ok but get disk info fail!\n", diskName);
    inode_release(blkDriver);
DISK_FIND_ERROR:
    (VOID)unregister_blockdriver(diskName);
    return VFS_ERROR;
}

INT32 los_disk_deinit(INT32 diskID)
{
    los_disk *disk = get_disk(diskID);
    if (disk == NULL) {
        return -EINVAL;
    }

    DISK_LOCK(&disk->disk_mutex);

    if (disk->disk_status != STAT_INUSED) {
        DISK_UNLOCK(&disk->disk_mutex);
        return -EINVAL;
    }

    disk->disk_status = STAT_UNREADY;
    DISK_UNLOCK(&disk->disk_mutex);

    return DiskDeinit(disk);
}

INT32 los_disk_sync(INT32 drvID)
{
    INT32 ret = ENOERR;
    los_disk *disk = get_disk(drvID);
    if (disk == NULL) {
        return EINVAL;
    }

    DISK_LOCK(&disk->disk_mutex);
    if (disk->disk_status != STAT_INUSED) {
        DISK_UNLOCK(&disk->disk_mutex);
        return EINVAL;
    }

#ifdef LOSCFG_FS_FAT_CACHE
        if (disk->bcache != NULL) {
            ret = BlockCacheSync(disk->bcache);
        }
#endif

    DISK_UNLOCK(&disk->disk_mutex);
    return ret;
}

INT32 los_disk_set_bcache(INT32 drvID, UINT32 sectorPerBlock, UINT32 blockNum)
{
#ifdef LOSCFG_FS_FAT_CACHE

    INT32 ret;
    UINT32 intSave;
    OsBcache *bc = NULL;
    los_disk *disk = get_disk(drvID);
    if ((disk == NULL) || (sectorPerBlock == 0)) {
        return EINVAL;
    }

    /*
     * Because we use UINT32 flag[BCACHE_BLOCK_FLAGS] in bcache for sectors bitmap tag, so it must
     * be less than 32 * BCACHE_BLOCK_FLAGS.
     */
    if (((sectorPerBlock % UNSIGNED_INTEGER_BITS) != 0) ||
        ((sectorPerBlock >> UNINT_LOG2_SHIFT) > BCACHE_BLOCK_FLAGS)) {
        return EINVAL;
    }

    DISK_LOCK(&disk->disk_mutex);

    if (disk->disk_status != STAT_INUSED) {
        goto ERROR_HANDLE;
    }

    if (disk->bcache != NULL) {
        ret = BlockCacheSync(disk->bcache);
        if (ret != ENOERR) {
            DISK_UNLOCK(&disk->disk_mutex);
            return ret;
        }
    }

    spin_lock_irqsave(&g_diskFatBlockSpinlock, intSave);
    DiskCacheDeinit(disk);

    g_uwFatBlockNums = blockNum;
    g_uwFatSectorsPerBlock = sectorPerBlock;

    bc = BlockCacheInit(disk->dev, disk->sector_size, sectorPerBlock, blockNum, disk->sector_count / sectorPerBlock);
    if ((bc == NULL) && (blockNum != 0)) {
        spin_unlock_irqrestore(&g_diskFatBlockSpinlock, intSave);
        DISK_UNLOCK(&disk->disk_mutex);
        return ENOMEM;
    }

    if (bc != NULL) {
        DiskCacheThreadInit((UINT32)drvID, bc);
    }

    disk->bcache = bc;
    spin_unlock_irqrestore(&g_diskFatBlockSpinlock, intSave);
    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return EINVAL;
#else
    return VFS_ERROR;
#endif
}

static los_part *OsPartFind(los_disk *disk, const struct inode *blkDriver)
{
    los_part *part = NULL;

    DISK_LOCK(&disk->disk_mutex);
    if ((disk->disk_status != STAT_INUSED) || (LOS_ListEmpty(&disk->head) == TRUE)) {
        goto EXIT;
    }
    part = LOS_DL_LIST_ENTRY(disk->head.pstNext, los_part, list);
    if (disk->dev == blkDriver) {
        goto EXIT;
    }

    while (&part->list != &disk->head) {
        if (part->dev == blkDriver) {
            goto EXIT;
        }
        part = LOS_DL_LIST_ENTRY(part->list.pstNext, los_part, list);
    }
    part = NULL;

EXIT:
    DISK_UNLOCK(&disk->disk_mutex);
    return part;
}

los_part *los_part_find(struct inode *blkDriver)
{
    INT32 i;
    los_disk *disk = NULL;
    los_part *part = NULL;

    if (blkDriver == NULL) {
        return NULL;
    }

    for (i = 0; i < SYS_MAX_DISK; i++) {
        disk = get_disk(i);
        if (disk == NULL) {
            continue;
        }
        part = OsPartFind(disk, blkDriver);
        if (part != NULL) {
            return part;
        }
    }

    return NULL;
}

INT32 los_part_access(const CHAR *dev, mode_t mode)
{
    los_part *part = NULL;
    struct inode *node = NULL;
    struct inode_search_s desc;
    (VOID)mode;

    SETUP_SEARCH(&desc, dev, false);
    if (inode_find(&desc) < 0) {
        return VFS_ERROR;
    }
    node = desc.node;

    part = los_part_find(node);
    inode_release(node);
    if (part == NULL) {
        return VFS_ERROR;
    }

    return ENOERR;
}

INT32 SetDiskPartName(los_part *part, const CHAR *src)
{
    size_t len;
    los_disk *disk = NULL;

    if ((part == NULL) || (src == NULL)) {
        return VFS_ERROR;
    }

    len = strlen(src);
    if ((len == 0) || (len >= DISK_NAME)) {
        return VFS_ERROR;
    }

    disk = get_disk((INT32)part->disk_id);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    DISK_LOCK(&disk->disk_mutex);
    if (disk->disk_status != STAT_INUSED) {
        goto ERROR_HANDLE;
    }

    part->part_name = (CHAR *)zalloc(len + 1);
    if (part->part_name == NULL) {
        PRINT_ERR("%s[%d] zalloc failure\n", __FUNCTION__, __LINE__);
        goto ERROR_HANDLE;
    }

    (VOID)strcpy_s(part->part_name, len + 1, src);

    DISK_UNLOCK(&disk->disk_mutex);
    return ENOERR;

ERROR_HANDLE:
    DISK_UNLOCK(&disk->disk_mutex);
    return VFS_ERROR;
}

INT32 add_mmc_partition(struct disk_divide_info *info, size_t sectorStart, size_t sectorCount)
{
    UINT32 index, i;

    if (info == NULL) {
        return VFS_ERROR;
    }

    if ((info->part_count >= MAX_DIVIDE_PART_PER_DISK) || (sectorCount == 0)) {
        return VFS_ERROR;
    }

    if ((sectorCount > info->sector_count) || ((info->sector_count - sectorCount) < sectorStart)) {
        return VFS_ERROR;
    }

    index = info->part_count;
    for (i = 0; i < index; i++) {
        if (sectorStart < (info->part[i].sector_start + info->part[i].sector_count)) {
            return VFS_ERROR;
        }
    }

    info->part[index].sector_start = sectorStart;
    info->part[index].sector_count = sectorCount;
    info->part[index].type = EMMC;
    info->part_count++;

    return ENOERR;
}

VOID show_part(los_part *part)
{
    if ((part == NULL) || (part->dev == NULL)) {
        PRINT_ERR("part is NULL\n");
        return;
    }

    PRINTK("\npart info :\n");
    PRINTK("disk id          : %u\n", part->disk_id);
    PRINTK("part_id in system: %u\n", part->part_id);
    PRINTK("part no in disk  : %u\n", part->part_no_disk);
    PRINTK("part no in mbr   : %u\n", part->part_no_mbr);
    PRINTK("part filesystem  : %02X\n", part->filesystem_type);
    PRINTK("part dev name    : %s\n", part->dev->i_name);
    PRINTK("part sec start   : %llu\n", part->sector_start);
    PRINTK("part sec count   : %llu\n", part->sector_count);
}

INT32 EraseDiskByID(UINT32 diskID, size_t startSector, UINT32 sectors)
{
    INT32 ret = VFS_ERROR;
#ifdef LOSCFG_DRIVERS_MMC
    los_disk *disk = get_disk((INT32)diskID);
    if (disk != NULL) {
        ret = do_mmc_erase(diskID, startSector, sectors);
    }
#endif

    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
