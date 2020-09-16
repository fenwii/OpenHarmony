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

#include "bcache.h"
#include "assert.h"
#include "stdlib.h"
#include "linux/delay.h"
#include "disk_pri.h"
#include "fs_other.h"
#include "user_copy.h"

#undef HALARC_ALIGNMENT
#define DMA_ALLGN          64
#define HALARC_ALIGNMENT   DMA_ALLGN
#define BCACHE_MAGIC_NUM   20132016
#define BCACHE_STATCK_SIZE 0x3000
#define ASYNC_EVENT_BIT    0x01

#ifdef DEBUG
#define D(args) printf(args)
#else
#define D(args)
#endif

#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD

UINT32 g_syncThreadPrio = CONFIG_FS_FAT_SYNC_THREAD_PRIO;
UINT32 g_dirtyRatio = CONFIG_FS_FAT_DIRTY_RATIO;
UINT32 g_syncInterval = CONFIG_FS_FAT_SYNC_INTERVAL;

VOID LOS_SetDirtyRatioThreshold(UINT32 dirtyRatio)
{
    if ((dirtyRatio != g_dirtyRatio) && (dirtyRatio <= 100)) { /* The ratio cannot exceed 100% */
        g_dirtyRatio = dirtyRatio;
    }
}

VOID LOS_SetSyncThreadInterval(UINT32 interval)
{
    g_syncInterval = interval;
}

INT32 LOS_SetSyncThreadPrio(UINT32 prio, const CHAR *name)
{
    INT32 ret = VFS_ERROR;
    INT32 diskID;
    los_disk *disk = NULL;
    if ((prio == 0) || (prio >= OS_TASK_PRIORITY_LOWEST)) { /* The priority can not be zero */
        return ret;
    }

    g_syncThreadPrio = prio;

    /*
     * If the name is NULL, it only sets the value of a global variable,
     * and takes effect the next time the thread is created.
     */
    if (name == NULL) {
        return ENOERR;
    }

    /* If the name is not NULL, it shall return an error if can't find the disk corresponding to name. */
    diskID = los_get_diskid_byname(name);
    disk = get_disk(diskID);
    if (disk == NULL) {
        return ret;
    }

    if (pthread_mutex_lock(&disk->disk_mutex) != ENOERR) {
        PRINT_ERR("%s %d, mutex lock fail!\n", __FUNCTION__, __LINE__);
        return ret;
    }
    if ((disk->disk_status == STAT_INUSED) && (disk->bcache != NULL)) {
        ret = LOS_TaskPriSet(disk->bcache->syncTaskId, prio);
    }
    if (pthread_mutex_unlock(&disk->disk_mutex) != ENOERR) {
        PRINT_ERR("%s %d, mutex unlock fail!\n", __FUNCTION__, __LINE__);
        return VFS_ERROR;
    }
    return ret;
}
#endif

static OsBcacheBlock *RbFindBlock(const OsBcache *bc, UINT64 num)
{
    OsBcacheBlock *block = NULL;
    struct rb_node *node = bc->rbRoot.rb_node;

    for (; node != NULL; node = (block->num < num) ? node->rb_right : node->rb_left) {
        block = rb_entry(node, OsBcacheBlock, rbNode);
        if (block->num == num) {
            return block;
        }
    }
    return NULL;
}

static VOID RbAddBlock(OsBcache *bc, OsBcacheBlock *block)
{
    struct rb_node *node = bc->rbRoot.rb_node;
    struct rb_node **link = NULL;
    OsBcacheBlock *b = NULL;

    if (node == NULL) {
        rb_link_node(&block->rbNode, NULL, &bc->rbRoot.rb_node);
    } else {
        for (; node != NULL; link = (b->num > block->num) ? &node->rb_left : &node->rb_right, node = *link) {
            b = rb_entry(node, OsBcacheBlock, rbNode);
            if (b->num == block->num) {
                PRINT_ERR("RbAddBlock fail, b->num = %llu, block->num = %llu\n", b->num, block->num);
                return;
            }
        }
        rb_link_node(&block->rbNode, &b->rbNode, link);
    }
    rb_insert_color(&block->rbNode, &bc->rbRoot);
}

static inline VOID RbDelBlock(OsBcache *bc, OsBcacheBlock *block)
{
    rb_erase(&block->rbNode, &bc->rbRoot);
}

static inline VOID ListMoveBlockToHead(OsBcache *bc, OsBcacheBlock *block)
{
    LOS_ListDelete(&block->listNode);
    LOS_ListAdd(&bc->listHead, &block->listNode);
}

static inline VOID FreeBlock(OsBcache *bc, OsBcacheBlock *block)
{
    block->used = FALSE;
    LOS_ListAdd(&bc->freeListHead, &block->listNode);
}

static UINT32 GetValLog2(UINT32 val)
{
    UINT32 i, log2;

    i = val;
    log2 = 0;
    while ((i & 1) == 0) { /* Check if the last bit is 1 */
        i >>= 1;
        log2++;
    }
    if (i != 1) { /* Not the power of 2 */
        return 0;
    }

    return log2;
}

static INT32 FindFlagPos(const UINT32 *arr, UINT32 len, UINT32 *p1, UINT32 *p2)
{
    UINT32 *start = p1;
    UINT32 *end = p2;
    UINT32 i, j, tmp;
    UINT32 val = 1;

    *start = BCACHE_MAGIC_NUM;
    *end = 0;
    for (i = 0; i < len; i++) {
        for (j = 0; j < UNSIGNED_INTEGER_BITS; j++) {
            tmp = arr[i] << j;
            tmp = tmp >> UNINT_MAX_SHIFT_BITS;
            if (tmp != val) {
                continue;
            }
            if (val && (*start == BCACHE_MAGIC_NUM)) {
                *start = (i << UNINT_LOG2_SHIFT) + j;
                val = 1 - val; /* Control parity by 0 and 1 */
            } else if (val && (*start != BCACHE_MAGIC_NUM)) {
                *start = 0;
                return VFS_ERROR;
            } else {
                *end = (i << UNINT_LOG2_SHIFT) + j;
                val = 1 - val; /* Control parity by 0 and 1 */
            }
        }
    }
    if (*start == BCACHE_MAGIC_NUM) {
        *start = 0;
        return VFS_ERROR;
    }
    if (*end == 0) {
        *end = len << UNINT_LOG2_SHIFT;
    }

    return ENOERR;
}

static INT32 BlockRead(OsBcache *bc, OsBcacheBlock *block, UINT8 *buf)
{
    INT32 ret = bc->breadFun(bc->priv, buf, bc->sectorPerBlock,
                             (block->num) << GetValLog2(bc->sectorPerBlock));
    if (ret) {
        PRINT_ERR("BlockRead, brread_fn error, ret = %d\n", ret);
        if (block->modified == FALSE) {
            if (block->listNode.pstNext != NULL) {
                LOS_ListDelete(&block->listNode); /* list del block */
                RbDelBlock(bc, block);
            }
            FreeBlock(bc, block);
        }
        return ret;
    }

    block->readFlag = TRUE;
    return ENOERR;
}

static INT32 BcacheGetFlag(OsBcache *bc, OsBcacheBlock *block)
{
    UINT32 i, n, f, sectorPos, val, start, pos, currentSize;
    UINT32 flagUse = bc->sectorPerBlock >> UNINT_LOG2_SHIFT;
    UINT32 flag = UINT_MAX;
    INT32 ret, bits;

    if (block->readFlag == TRUE) {
        return ENOERR;
    }

    for (i = 0; i < flagUse; i++) {
        flag &= block->flag[i];
    }

    if (flag == UINT_MAX) {
        return ENOERR;
    }

    ret = BlockRead(bc, block, bc->rwBuffer);
    if (ret != ENOERR) {
        return ret;
    }

    for (i = 0, sectorPos = 0; i < flagUse; i++) {
        val = block->flag[i];
        /* use unsigned integer for bit map */
        for (f = 0, bits = UNSIGNED_INTEGER_BITS; bits > 0; val = ~(val << n), f++, bits = bits - (INT32)n) {
            if (val == 0) {
                n = UNSIGNED_INTEGER_BITS;
            } else {
                n = (UINT32)CLZ(val);
            }
            sectorPos += n;
            if (((f % EVEN_JUDGED) != 0) || (n == 0)) { /* Number of leading zeros of n is zero */
                goto LOOP;
            }
            if (sectorPos > ((i + 1) << UNINT_LOG2_SHIFT)) {
                start = sectorPos - n;
                currentSize = (((i + 1) << UNINT_LOG2_SHIFT) - start) * bc->sectorSize;
            } else {
                start = sectorPos - n;
                currentSize = n * bc->sectorSize;
            }
            pos = start * bc->sectorSize;
            if (memcpy_s(block->data + pos, bc->blockSize - pos, bc->rwBuffer + pos, currentSize) != EOK) {
                return VFS_ERROR;
            }
LOOP:
            if (sectorPos > ((i + 1) << UNINT_LOG2_SHIFT)) {
                sectorPos = (i + 1) << UNINT_LOG2_SHIFT;
            }
        }
    }

    return ENOERR;
}

static VOID BcacheSetFlag(const OsBcache *bc, OsBcacheBlock *block, UINT32 pos, UINT32 size)
{
    UINT32 start, num, i, j, k;

    if (bc->sectorSize == 0) {
        PRINT_ERR("BcacheSetFlag sectorSize is equal to zero! \n");
        return;
    }

    start = pos / bc->sectorSize;
    num = size / bc->sectorSize;

    i = start / UNSIGNED_INTEGER_BITS;
    j = start % UNSIGNED_INTEGER_BITS;
    for (k = 0; k < num; k++) {
        block->flag[i] |= 1u << (UNINT_MAX_SHIFT_BITS - j);
        j++;
        if (j == UNSIGNED_INTEGER_BITS) {
            j = 0;
            i++;
        }
    }
}

static INT32 BcacheSyncBlock(OsBcache *bc, OsBcacheBlock *block)
{
    INT32 ret = ENOERR;
    UINT32 len, start, end;

    if (block->modified == TRUE) {
        D(("bcache writting block = %llu\n", block->num));

        ret = FindFlagPos(block->flag, bc->sectorPerBlock >> UNINT_LOG2_SHIFT, &start, &end);
        if (ret == ENOERR) {
            len = end - start;
        } else {
            ret = BcacheGetFlag(bc, block);
            if (ret != ENOERR) {
                return ret;
            }

            len = bc->sectorPerBlock;
        }

        ret = bc->bwriteFun(bc->priv, (const UINT8 *)(block->data + (start * bc->sectorSize)),
                            len, (block->num * bc->sectorPerBlock) + start);
        if (ret == ENOERR) {
            block->modified = FALSE;
            bc->modifiedBlock--;
        } else {
            PRINT_ERR("BcacheSyncBlock fail, ret = %d, len = %u, block->num = %llu, start = %u\n",
                      ret, len, block->num, start);
        }
    }
    return ret;
}

static void NumListAdd(OsBcache *bc, OsBcacheBlock *block)
{
    OsBcacheBlock *temp = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(temp, &bc->numHead, OsBcacheBlock, numNode) {
        if (temp->num > block->num) {
            LOS_ListTailInsert(&temp->numNode, &block->numNode);
            return;
        }
    }

    LOS_ListTailInsert(&bc->numHead, &block->numNode);
}

static void AddBlock(OsBcache *bc, OsBcacheBlock *block)
{
    RbAddBlock(bc, block);
    NumListAdd(bc, block);
    bc->sumNum += block->num;
    bc->nBlock++;
    LOS_ListAdd(&bc->listHead, &block->listNode);
}

static void DelBlock(OsBcache *bc, OsBcacheBlock *block)
{
    LOS_ListDelete(&block->listNode); /* lru list del */
    LOS_ListDelete(&block->numNode);  /* num list del */
    bc->sumNum -= block->num;
    bc->nBlock--;
    RbDelBlock(bc, block);            /* rb  tree del */
    FreeBlock(bc, block);             /* free list add */
}

static BOOL BlockAllDirty(const OsBcache *bc, OsBcacheBlock *block)
{
    UINT32 start = 0;
    UINT32 end = 0;
    UINT32 len = bc->sectorPerBlock >> UNINT_LOG2_SHIFT;

    if (block->modified == TRUE) {
        if (block->allDirty) {
            return TRUE;
        }

        if (FindFlagPos(block->flag, len, &start, &end) == ENOERR) {
            if ((end - start) == bc->sectorPerBlock) {
                block->allDirty = TRUE;
                return TRUE;
            }
        }
    }

    return FALSE;
}

static OsBcacheBlock *GetBaseBlock(OsBcache *bc)
{
    OsBcacheBlock *base = bc->wStart;
    OsBcacheBlock *end = bc->wEnd;
    while (base < end) {
        if (base->used == FALSE) {
            base->used = TRUE;
            LOS_ListDelete(&base->listNode);
            return base;
        }
        base++;
    }

    return NULL;
}

/* try get free block first, if failed free a useless block */
static OsBcacheBlock *GetSlowBlock(OsBcache *bc, BOOL read)
{
    LOS_DL_LIST *node = NULL;
    OsBcacheBlock *block = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(block, &bc->freeListHead, OsBcacheBlock, listNode) {
        if (block->readBuff == read) {
            block->used = TRUE;
            LOS_ListDelete(&block->listNode);
            return block; /* get free one */
        }
    }

    node = bc->listHead.pstPrev;
    while (node != &bc->listHead) {
        block = LOS_DL_LIST_ENTRY(node, OsBcacheBlock, listNode);
        node = block->listNode.pstPrev;

        if (block->readBuff == read && read && !block->modified) {
            DelBlock(bc, block);
            block->used = TRUE;
            LOS_ListDelete(&block->listNode);
            return block; /* read only block */
        }
    }

    node = bc->listHead.pstPrev;
    while (node != &bc->listHead) {
        block = LOS_DL_LIST_ENTRY(node, OsBcacheBlock, listNode);
        node = block->listNode.pstPrev;

        if (block->readBuff == read) {
            if (block->modified == TRUE) {
                BcacheSyncBlock(bc, block);
            }

            DelBlock(bc, block);
            block->used = TRUE;
            LOS_ListDelete(&block->listNode);
            return block; /* get used one */
        }
    }

    return NULL;
}

/* flush combined blocks */
static VOID WriteMergedBlocks(OsBcache *bc, OsBcacheBlock *begin, int blocks)
{
    INT32 ret;
    OsBcacheBlock *cur = NULL;
    OsBcacheBlock *next = NULL;
    UINT32 len = blocks * bc->sectorPerBlock;
    UINT64 pos = begin->num * bc->sectorPerBlock;

    ret = bc->bwriteFun(bc->priv, (const UINT8 *)begin->data, len, pos);
    if (ret != ENOERR) {
        PRINT_ERR("WriteMergedBlocks bwriteFun failed ret %d\n", ret);
        return;
    }

    bc->modifiedBlock -= blocks;
    cur = begin;
    while (blocks > 0) {
        next = LOS_DL_LIST_ENTRY(cur->numNode.pstNext, OsBcacheBlock, numNode);
        DelBlock(bc, cur);
        blocks--;
        cur = next;
    }
}

/* find continue blocks and flush them */
static VOID MergeSyncBlocks(OsBcache *bc, OsBcacheBlock *start)
{
    INT32 mergedBlock = 0;
    OsBcacheBlock *cur = start;
    OsBcacheBlock *last = NULL;

    while (cur <= bc->wEnd) {
        if (!cur->used || !BlockAllDirty(bc, cur)) {
            break;
        }

        if (last && (last->num + 1 != cur->num)) {
            break;
        }

        mergedBlock++;
        last = cur;
        cur++;
    }

    if (mergedBlock > 0) {
        WriteMergedBlocks(bc, start, mergedBlock);
    }
}

/* get the min write block num of block cache buffer */
static inline UINT64 GetMinWriteNum(OsBcache *bc)
{
    UINT64 ret = 0;
    OsBcacheBlock *block = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(block, &bc->numHead, OsBcacheBlock, numNode) {
        if (!block->readBuff) {
            ret = block->num;
            break;
        }
    }

    return ret;
}

static OsBcacheBlock *AllocNewBlock(OsBcache *bc, BOOL read, UINT64 num)
{
    OsBcacheBlock *last = NULL;
    OsBcacheBlock *prefer = NULL;

    if (read) { /* read */
        return GetSlowBlock(bc, TRUE);
    }

    /* fallback, this may happen when the block previously flushed, use read buffer */
    if (bc->nBlock && num < GetMinWriteNum(bc)) {
        return GetSlowBlock(bc, TRUE);
    }

    last = RbFindBlock(bc, num - 1);  /* num=0 is ok */
    if (last == NULL || last->readBuff) {
        return GetBaseBlock(bc);      /* new block */
    }

    prefer = last + 1;
    if (prefer > bc->wEnd) {
        prefer = bc->wStart;
    }

    /* this is a sync thread synced block! */
    if (prefer->used && !prefer->modified) {
        prefer->used = FALSE;
        DelBlock(bc, prefer);
    }

    if (prefer->used) {
        MergeSyncBlocks(bc, prefer);
    }

    if (prefer->used) {
        BcacheSyncBlock(bc, prefer);
        DelBlock(bc, prefer);
    }

    prefer->used = TRUE;
    LOS_ListDelete(&prefer->listNode); /* del from free list */

    return prefer;
}

static INT32 BcacheSync(OsBcache *bc)
{
    LOS_DL_LIST *node = NULL;
    OsBcacheBlock *block = NULL;
    INT32 ret = ENOERR;

    D(("bcache cache sync\n"));

    (VOID)pthread_mutex_lock(&bc->bcacheMutex);
    node = bc->listHead.pstPrev;
    while (&bc->listHead != node) {
        block = LOS_DL_LIST_ENTRY(node, OsBcacheBlock, listNode);
        ret = BcacheSyncBlock(bc, block);
        if (ret != ENOERR) {
            PRINT_ERR("BcacheSync error, ret = %d\n", ret);
            break;
        }
        node = node->pstPrev;
    }
    (VOID)pthread_mutex_unlock(&bc->bcacheMutex);

    return ret;
}

static VOID BlockInit(OsBcache *bc, OsBcacheBlock *block, UINT64 num)
{
    (VOID)memset_s(block->flag, sizeof(block->flag), 0, sizeof(block->flag));
    block->num = num;
    block->readFlag = FALSE;
    if (block->modified == TRUE) {
        block->modified = FALSE;
        bc->modifiedBlock--;
    }
    block->allDirty = FALSE;
}

static INT32 BcacheGetBlock(OsBcache *bc, UINT64 num, BOOL readData, OsBcacheBlock **dblock)
{
    INT32 ret;
    OsBcacheBlock *block = NULL;
    OsBcacheBlock *first = NULL;

    /*
     * First check if the most recently used block is the requested block,
     * this can improve performance when using byte access functions.
     */
    if (LOS_ListEmpty(&bc->listHead) == FALSE) {
        first = LOS_DL_LIST_ENTRY(bc->listHead.pstNext, OsBcacheBlock, listNode);
        block = (first->num == num) ? first : RbFindBlock(bc, num);
    }

    if (block != NULL) {
        D(("bcache block = %llu found in cache\n", num));

        if (first != block) {
            ListMoveBlockToHead(bc, block);
        }
        *dblock = block;

        if ((bc->prereadFun != NULL) && (readData == TRUE) && (block->pgHit == 1)) {
            block->pgHit = 0;
            bc->prereadFun(bc, block);
        }

        return ENOERR;
    }

    D(("bcache block = %llu NOT found in cache\n", num));

    block = AllocNewBlock(bc, readData, num);
    if (block == NULL) {
        block = GetSlowBlock(bc, readData);
    }

    BlockInit(bc, block, num);

    if (readData == TRUE) {
        D(("bcache reading block = %llu\n", block->num));

        ret = BlockRead(bc, block, block->data);
        if (ret != ENOERR) {
            return ret;
        }
        if (bc->prereadFun != NULL) {
            bc->prereadFun(bc, block);
        }
    }

    AddBlock(bc, block);

    *dblock = block;
    return ENOERR;
}

static INT32 BcacheInitCache(OsBcache *bc,
                             UINT8 *memStart,
                             UINT32 memSize,
                             UINT32 blockSize)
{
    UINT8 *blockMem = NULL;
    UINT8 *dataMem = NULL;
    OsBcacheBlock *block = NULL;
    UINT32 blockNum, i;

    LOS_ListInit(&bc->listHead);
    LOS_ListInit(&bc->numHead);
    bc->sumNum = 0;
    bc->nBlock = 0;

    if (!GetValLog2(blockSize)) {
        PRINT_ERR("GetValLog2(%u) return 0.\n", blockSize);
        return -EINVAL;
    }

    bc->rbRoot.rb_node = NULL;
    bc->memStart = memStart;
    bc->blockSize = blockSize;
    bc->blockSizeLog2 = GetValLog2(blockSize);
    bc->modifiedBlock = 0;

    /* init block memory pool */
    LOS_ListInit(&bc->freeListHead);

    blockNum = (memSize - DMA_ALLGN) / (sizeof(OsBcacheBlock) + bc->blockSize);
    blockMem = bc->memStart;
    dataMem = blockMem + (sizeof(OsBcacheBlock) * blockNum);
    dataMem += ALIGN_DISP((UINTPTR)dataMem);

    for (i = 0; i < blockNum; i++) {
        block = (OsBcacheBlock *)(VOID *)blockMem;
        block->data = dataMem;
        block->readBuff = (i < CONFIG_FS_FAT_READ_NUMS) ? TRUE : FALSE;

        if (i == CONFIG_FS_FAT_READ_NUMS) {
            bc->wStart = block;
        }

        LOS_ListAdd(&bc->freeListHead, &block->listNode);

        blockMem += sizeof(OsBcacheBlock);
        dataMem += bc->blockSize;
    }

    bc->wEnd = block;

    return ENOERR;
}

static INT32 DrvBread(struct inode *priv, UINT8 *buf, UINT32 len, UINT64 pos)
{
    INT32 ret = priv->u.i_bops->read(priv, buf, pos, len);
    if (ret != (INT32)len) {
        PRINT_ERR("%s failure\n", __FUNCTION__);
        return ret;
    }
    return ENOERR;
}

static INT32 DrvBwrite(struct inode *priv, const UINT8 *buf, UINT32 len, UINT64 pos)
{
    INT32 ret = priv->u.i_bops->write(priv, buf, pos, len);
    if (ret != (INT32)len) {
        PRINT_ERR("%s failure\n", __FUNCTION__);
        return ret;
    }
    return ENOERR;
}

INT32 BlockCacheDrvCreate(VOID *handle,
                          UINT8 *memStart,
                          UINT32 memSize,
                          UINT32 blockSize,
                          OsBcache *bc)
{
    INT32 ret;
    bc->priv = handle;
    bc->breadFun = DrvBread;
    bc->bwriteFun = DrvBwrite;

    ret = BcacheInitCache(bc, memStart, memSize, blockSize);
    if (ret != ENOERR) {
        return ret;
    }

    if (pthread_mutex_init(&bc->bcacheMutex, NULL) != ENOERR) {
        return VFS_ERROR;
    }
    bc->bcacheMutex.attr.type = PTHREAD_MUTEX_RECURSIVE;

    return ENOERR;
}

INT32 BlockCacheRead(OsBcache *bc, UINT8 *buf, UINT32 *len, UINT64 sector)
{
    OsBcacheBlock *block = NULL;
    UINT8 *tempBuf = buf;
    UINT32 size;
    UINT32 currentSize;
    INT32 ret = ENOERR;
    UINT64 pos;
    UINT64 num;

    if (bc == NULL || buf == NULL || len == NULL) {
        return -EPERM;
    }

    size = *len;
    pos = sector * bc->sectorSize;
    num = pos >> bc->blockSizeLog2;
    pos = pos & (bc->blockSize - 1);

    while (size > 0) {
        if ((size + pos) > bc->blockSize) {
            currentSize = bc->blockSize - (UINT32)pos;
        } else {
            currentSize = size;
        }

        (VOID)pthread_mutex_lock(&bc->bcacheMutex);

        ret = BcacheGetBlock(bc, num, TRUE, &block);
        if (ret != ENOERR) {
            (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
            break;
        }

        if ((block->readFlag == FALSE) && (block->modified == TRUE)) {
            ret = BcacheGetFlag(bc, block);
            if (ret != ENOERR) {
                (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
                return ret;
            }
        } else if ((block->readFlag == FALSE) && (block->modified == FALSE)) {
            ret = BlockRead(bc, block, block->data);
            if (ret != ENOERR) {
                (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
                return ret;
            }
        }

        if (LOS_CopyFromKernel((VOID *)tempBuf, size, (VOID *)(block->data + pos), currentSize) != EOK) {
            (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
            return VFS_ERROR;
        }

        (VOID)pthread_mutex_unlock(&bc->bcacheMutex);

        tempBuf += currentSize;
        size -= currentSize;
        pos = 0;
        num++;
    }
    *len -= size;
    return ret;
}

INT32 BlockCacheWrite(OsBcache *bc, const UINT8 *buf, UINT32 *len, UINT64 sector)
{
    OsBcacheBlock *block = NULL;
    const UINT8 *tempBuf = buf;
    UINT32 size = *len;
    INT32 ret = ENOERR;
    UINT32 currentSize;
    UINT64 pos;
    UINT64 num;

    pos = sector * bc->sectorSize;
    num = pos >> bc->blockSizeLog2;
    pos = pos & (bc->blockSize - 1);

    D(("bcache write len = %u pos = %llu bnum = %llu\n", *len, pos, num));

    while (size > 0) {
        if ((size + pos) > bc->blockSize) {
            currentSize = bc->blockSize - (UINT32)pos;
        } else {
            currentSize = size;
        }

        (VOID)pthread_mutex_lock(&bc->bcacheMutex);
        ret = BcacheGetBlock(bc, num, FALSE, &block);
        if (ret != ENOERR) {
            (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
            break;
        }

        if (LOS_CopyToKernel((VOID *)(block->data + pos), bc->blockSize - (UINT32)pos,
            (VOID *)tempBuf, currentSize) != EOK) {
            (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
            return VFS_ERROR;
        }
        if (block->modified == FALSE) {
            block->modified = TRUE;
            bc->modifiedBlock++;
        }
        if ((pos == 0) && (currentSize == bc->blockSize)) {
            memset_s(block->flag, sizeof(block->flag), 0xFF, sizeof(block->flag));
            block->allDirty = TRUE;
        } else {
            BcacheSetFlag(bc, block, (UINT32)pos, currentSize);
        }
        (VOID)pthread_mutex_unlock(&bc->bcacheMutex);

        tempBuf += currentSize;
        size -= currentSize;
        pos = 0;
        num++;
    }
    *len -= size;
    return ret;
}

INT32 BlockCacheSync(OsBcache *bc)
{
    return BcacheSync(bc);
}

INT32 OsSdSync(INT32 id)
{
#ifdef LOSCFG_FS_FAT_CACHE
    INT32 ret;
    los_disk *disk = get_disk(id);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    if (pthread_mutex_lock(&disk->disk_mutex) != ENOERR) {
        PRINT_ERR("%s %d, mutex lock fail!\n", __FUNCTION__, __LINE__);
        return VFS_ERROR;
    }
    if ((disk->disk_status == STAT_INUSED) && (disk->bcache != NULL)) {
        ret = BcacheSync(disk->bcache);
    } else {
        ret = VFS_ERROR;
    }
    if (pthread_mutex_unlock(&disk->disk_mutex) != ENOERR) {
        PRINT_ERR("%s %d, mutex unlock fail!\n", __FUNCTION__, __LINE__);
        return VFS_ERROR;
    }
    return ret;
#else
    return VFS_ERROR;
#endif
}

INT32 LOS_BcacheSyncByName(const CHAR *name)
{
    INT32 diskID = los_get_diskid_byname(name);
    return OsSdSync(diskID);
}

INT32 BcacheGetDirtyRatio(INT32 id)
{
#ifdef LOSCFG_FS_FAT_CACHE
    INT32 ret;
    los_disk *disk = get_disk(id);
    if (disk == NULL) {
        return VFS_ERROR;
    }

    if (pthread_mutex_lock(&disk->disk_mutex) != ENOERR) {
        PRINT_ERR("%s %d, mutex lock fail!\n", __FUNCTION__, __LINE__);
        return VFS_ERROR;
    }
    if ((disk->disk_status == STAT_INUSED) && (disk->bcache != NULL)) {
        ret = (INT32)((disk->bcache->modifiedBlock * PERCENTAGE) / GetFatBlockNums());
    } else {
        ret = VFS_ERROR;
    }
    if (pthread_mutex_unlock(&disk->disk_mutex) != ENOERR) {
        PRINT_ERR("%s %d, mutex unlock fail!\n", __FUNCTION__, __LINE__);
        return VFS_ERROR;
    }
    return ret;
#else
    return VFS_ERROR;
#endif
}

INT32 LOS_GetDirtyRatioByName(const CHAR *name)
{
    INT32 diskID = los_get_diskid_byname(name);
    return BcacheGetDirtyRatio(diskID);
}

#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD
static VOID BcacheSyncThread(UINT32 id)
{
    INT32 diskID = (INT32)id;
    INT32 dirtyRatio;
    while (1) {
        dirtyRatio = BcacheGetDirtyRatio(diskID);
        if (dirtyRatio > (INT32)g_dirtyRatio) {
            (VOID)OsSdSync(diskID);
        }
        msleep(g_syncInterval);
    }
}

VOID BcacheSyncThreadInit(OsBcache *bc, INT32 id)
{
    UINT32 ret;
    TSK_INIT_PARAM_S appTask;

    (VOID)memset_s(&appTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    appTask.pfnTaskEntry = (TSK_ENTRY_FUNC)BcacheSyncThread;
    appTask.uwStackSize = BCACHE_STATCK_SIZE;
    appTask.pcName = "bcache_sync_task";
    appTask.usTaskPrio = g_syncThreadPrio;
    appTask.auwArgs[0] = (UINTPTR)id;
    appTask.uwResved = LOS_TASK_STATUS_DETACHED;
    ret = LOS_TaskCreate(&bc->syncTaskId, &appTask);
    if (ret != ENOERR) {
        PRINT_ERR("Bcache sync task create failed in %s, %d\n", __FUNCTION__, __LINE__);
    }
}

VOID BcacheSyncThreadDeinit(const OsBcache *bc)
{
    if (bc != NULL) {
        if (LOS_TaskDelete(bc->syncTaskId) != ENOERR) {
            PRINT_ERR("Bcache sync task delete failed in %s, %d\n", __FUNCTION__, __LINE__);
        }
    }
}
#endif

OsBcache *BlockCacheInit(struct inode *devNode, UINT32 sectorSize, UINT32 sectorPerBlock,
                         UINT32 blockNum, UINT64 blockCount)
{
    OsBcache *bcache = NULL;
    struct inode *blkDriver = devNode;
    UINT8 *bcacheMem = NULL;
    UINT8 *rwBuffer = NULL;
    UINT32 blockSize, memSize;

    if ((blkDriver == NULL) || (sectorSize * sectorPerBlock * blockNum == 0) || (blockCount == 0)) {
        return NULL;
    }

    blockSize = sectorSize * sectorPerBlock;
    if ((((UINT64)(sizeof(OsBcacheBlock) + blockSize) * blockNum) + DMA_ALLGN) > UINT_MAX) {
        return NULL;
    }
    memSize = ((sizeof(OsBcacheBlock) + blockSize) * blockNum) + DMA_ALLGN;

    bcache = (OsBcache *)zalloc(sizeof(OsBcache));
    if (bcache == NULL) {
        PRINT_ERR("bcache_init : malloc %u Bytes failed!\n", sizeof(OsBcache));
        return NULL;
    }

    set_sd_sync_fn(OsSdSync);

    bcacheMem = (UINT8 *)zalloc(memSize);
    if (bcacheMem == NULL) {
        PRINT_ERR("bcache_init : malloc %u Bytes failed!\n", memSize);
        goto ERROR_OUT_WITH_BCACHE;
    }

    rwBuffer = (UINT8 *)memalign(DMA_ALLGN, blockSize);
    if (rwBuffer == NULL) {
        PRINT_ERR("bcache_init : malloc %u Bytes failed!\n", blockSize);
        goto ERROR_OUT_WITH_MEM;
    }

    bcache->rwBuffer = rwBuffer;
    bcache->sectorSize = sectorSize;
    bcache->sectorPerBlock = sectorPerBlock;
    bcache->blockCount = blockCount;

    if (BlockCacheDrvCreate(blkDriver, bcacheMem, memSize, blockSize, bcache) != ENOERR) {
        goto ERROR_OUT_WITH_BUFFER;
    }

    return bcache;

ERROR_OUT_WITH_BUFFER:
    free(rwBuffer);
ERROR_OUT_WITH_MEM:
    free(bcacheMem);
ERROR_OUT_WITH_BCACHE:
    free(bcache);
    return NULL;
}

VOID BlockCacheDeinit(OsBcache *bcache)
{
    if (bcache != NULL) {
        (VOID)pthread_mutex_destroy(&bcache->bcacheMutex);
        free(bcache->memStart);
        bcache->memStart = NULL;
        free(bcache->rwBuffer);
        bcache->rwBuffer = NULL;
        free(bcache);
    }
}

static VOID BcacheAsyncPrereadThread(VOID *arg)
{
    OsBcache *bc = (OsBcache *)arg;
    OsBcacheBlock *block = NULL;
    INT32 ret;
    UINT32 i;

    for (;;) {
        ret = (INT32)LOS_EventRead(&bc->bcacheEvent, PREREAD_EVENT_MASK,
                                   LOS_WAITMODE_OR | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
        if (ret != ASYNC_EVENT_BIT) {
            PRINT_ERR("The event read in %s, %d is error!!!\n", __FUNCTION__, __LINE__);
            continue;
        }

        for (i = 1; i <= PREREAD_BLOCK_NUM; i++) {
            if ((bc->curBlockNum + i) >= bc->blockCount) {
                break;
            }

            (VOID)pthread_mutex_lock(&bc->bcacheMutex);
            ret = BcacheGetBlock(bc, bc->curBlockNum + i, TRUE, &block);
            if (ret != ENOERR) {
                PRINT_ERR("read block %llu error : %d!\n", bc->curBlockNum, ret);
            }

            (VOID)pthread_mutex_unlock(&bc->bcacheMutex);
        }

        if (block != NULL) {
            block->pgHit = 1; /* preread complete */
        }
    }
}

VOID ResumeAsyncPreread(OsBcache *arg1, const OsBcacheBlock *arg2)
{
    UINT32 ret;
    OsBcache *bc = arg1;
    const OsBcacheBlock *block = arg2;

    if (OsCurrTaskGet()->taskID != bc->prereadTaskId) {
        bc->curBlockNum = block->num;
        ret = LOS_EventWrite(&bc->bcacheEvent, ASYNC_EVENT_BIT);
        if (ret != ENOERR) {
            PRINT_ERR("Write event failed in %s, %d\n", __FUNCTION__, __LINE__);
        }
    }
}

UINT32 BcacheAsyncPrereadInit(OsBcache *bc)
{
    UINT32 ret;
    TSK_INIT_PARAM_S appTask;

    ret = LOS_EventInit(&bc->bcacheEvent);
    if (ret != ENOERR) {
        PRINT_ERR("Async event init failed in %s, %d\n", __FUNCTION__, __LINE__);
        return ret;
    }

    (VOID)memset_s(&appTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    appTask.pfnTaskEntry = (TSK_ENTRY_FUNC)BcacheAsyncPrereadThread;
    appTask.uwStackSize = BCACHE_STATCK_SIZE;
    appTask.pcName = "bcache_async_task";
    appTask.usTaskPrio = BCACHE_PREREAD_PRIO;
    appTask.auwArgs[0] = (UINTPTR)bc;
    appTask.uwResved = LOS_TASK_STATUS_DETACHED;
    ret = LOS_TaskCreate(&bc->prereadTaskId, &appTask);
    if (ret != ENOERR) {
        PRINT_ERR("Bcache async task create failed in %s, %d\n", __FUNCTION__, __LINE__);
    }

    return ret;
}

UINT32 BcacheAsyncPrereadDeinit(OsBcache *bc)
{
    UINT32 ret = LOS_NOK;

    if (bc != NULL) {
        ret = LOS_TaskDelete(bc->prereadTaskId);
        if (ret != ENOERR) {
            PRINT_ERR("Bcache async task delete failed in %s, %d\n", __FUNCTION__, __LINE__);
        }

        ret = LOS_EventDestroy(&bc->bcacheEvent);
        if (ret != ENOERR) {
            PRINT_ERR("Async event destroy failed in %s, %d\n", __FUNCTION__, __LINE__);
            return ret;
        }
    }

    return ret;
}
