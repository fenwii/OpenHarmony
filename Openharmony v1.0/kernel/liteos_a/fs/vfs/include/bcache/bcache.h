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

#ifndef _BCACHE_H
#define _BCACHE_H

#include "pthread.h"
#include "linux/rbtree.h"
#include "los_list.h"

#ifdef LOSCFG_SHELL
#include "reset_shell.h"
#endif

#include "inode/inode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define ALIGN_LIB(x)          (((x) + (HALARC_ALIGNMENT - 1)) & ~(HALARC_ALIGNMENT - 1))
#define ALIGN_DISP(x)         (HALARC_ALIGNMENT - ((x) & (HALARC_ALIGNMENT - 1)))
#define BCACHE_PREREAD_PRIO   12
#define UNSIGNED_INTEGER_BITS 32
#define UNINT_MAX_SHIFT_BITS  31
#define UNINT_LOG2_SHIFT      5
#define PREREAD_BLOCK_NUM     2
#define EVEN_JUDGED           2
#define PERCENTAGE            100
#define PREREAD_EVENT_MASK    0xf

#if CONFIG_FS_FAT_SECTOR_PER_BLOCK < UNSIGNED_INTEGER_BITS
#error cache too small
#else
#define BCACHE_BLOCK_FLAGS (CONFIG_FS_FAT_SECTOR_PER_BLOCK / UNSIGNED_INTEGER_BITS)
#endif

typedef struct {
    LOS_DL_LIST listNode;   /* list node */
    LOS_DL_LIST numNode;    /* num node */
    struct rb_node rbNode;  /* red-black tree node */
    UINT64 num;             /* block number */
    UINT32 flag[BCACHE_BLOCK_FLAGS];
    UINT32 pgHit;
    UINT8 *data;            /* block data */
    BOOL modified;          /* is this block data modified (needs write) */
    BOOL readFlag;          /* is the block data have read from sd(real data) */
    BOOL readBuff;          /* read write buffer */
    BOOL used;              /* used or free for write buf */
    BOOL allDirty;          /* the whole block is dirty */
} OsBcacheBlock;

typedef INT32 (*BcacheReadFun)(struct inode *, /* private data */
                               UINT8 *,        /* block buffer */
                               UINT32,         /* number of blocks to read */
                               UINT64);        /* starting block number */

typedef INT32 (*BcacheWriteFun)(struct inode *, /* private data */
                                const UINT8 *,  /* block buffer */
                                UINT32,         /* number of blocks to write */
                                UINT64);        /* starting block number */

struct tagOsBcache;

typedef VOID (*BcachePrereadFun)(struct tagOsBcache *,   /* block cache instance space holder */
                                 const OsBcacheBlock *); /* block data */

typedef struct tagOsBcache {
    VOID *priv;                   /* private data */
    LOS_DL_LIST listHead;         /* head of block list */
    LOS_DL_LIST numHead;          /* block num list */
    struct rb_root rbRoot;        /* block red-black tree root */
    UINT32 blockSize;             /* block size in bytes */
    UINT32 blockSizeLog2;         /* block size log2 */
    UINT64 blockCount;            /* block count of the disk */
    UINT32 sectorSize;            /* device sector size in bytes */
    UINT32 sectorPerBlock;        /* sector count per block */
    UINT8 *memStart;              /* memory base */
    UINT32 prereadTaskId;         /* preread task id */
    UINT64 curBlockNum;           /* current preread block number */
    LOS_DL_LIST freeListHead;     /* list of free blocks */
    BcacheReadFun breadFun;       /* block read function */
    BcacheWriteFun bwriteFun;     /* block write function */
    BcachePrereadFun prereadFun;  /* block preread function */
    UINT8 *rwBuffer;              /* buffer for bcache block */
    pthread_mutex_t bcacheMutex;  /* mutex for bcache */
    EVENT_CB_S bcacheEvent;       /* event for bcache */
    UINT32 modifiedBlock;         /* number of modified blocks */
#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD
    UINT32 syncTaskId;            /* sync task id */
#endif
    OsBcacheBlock *wStart;        /* write start block */
    OsBcacheBlock *wEnd;          /* write end block */
    UINT64 sumNum;                /* block num sum val */
    UINT32 nBlock;                /* current block count */
} OsBcache;

/**
 * @ingroup  bcache
 *
 * @par Description:
 * The BlockCacheRead() function shall read data from the bcache, and if it doesn't hit, read the data from disk.
 *
 * @param  bc    [IN]  block cache instance
 * @param  buf   [OUT] data buffer ptr
 * @param  len   [IN]  number of bytes to read
 * @param  num   [IN]  starting block number
 * @param  pos   [IN]  starting position inside starting block
 *
 * @attention
 * <ul>
 * <li>The block number is automatically adjusted if position is greater than block size.</li>
 * </ul>
 *
 * @retval #0           read succeded
 * @retval #INT32       read failed
 *
 * @par Dependency:
 * <ul><li>bcache.h</li></ul>
 *
 */
INT32 BlockCacheRead(OsBcache *bc,
                     UINT8 *buf,
                     UINT32 *len,
                     UINT64 pos);

/**
 * @ingroup  bcache
 *
 * @par Description:
 * The BlockCacheWrite() function shall write data to the bcache.
 *
 * @param  bc    [IN]  block cache instance
 * @param  buf   [IN]  data buffer ptr
 * @param  len   [IN]  number of bytes to write
 * @param  num   [IN]  starting block number
 * @param  pos   [IN]  starting position inside starting block
 *
 * @attention
 * <ul>
 * <li>The block number is automatically adjusted if position is greater than block size.</li>
 * </ul>
 *
 * @retval #0           write succeded
 * @retval #INT32       write failed
 *
 * @par Dependency:
 * <ul><li>bcache.h</li></ul>
 *
 */
INT32 BlockCacheWrite(OsBcache *bc,
                      const UINT8 *buf,
                      UINT32 *len,
                      UINT64 pos);

/**
 * @ingroup  bcache
 *
 * @par Description:
 * The BlockCacheSync() function shall write-back all dirty data in the bcache into the disk.
 *
 * @param  bc    [IN]  block cache instance
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval #0           sync succeded
 * @retval #INT32       sync failed
 *
 * @par Dependency:
 * <ul><li>bcache.h</li></ul>
 *
 */
INT32 BlockCacheSync(OsBcache *bc);

/**
 * @ingroup  bcache
 *
 * @par Description:
 * The BlockCacheInit() function shall alloc memory for bcache and init it.
 *
 * @param  devNode          [IN]  dev node instance
 * @param  sectorSize       [IN]  size of a sector
 * @param  sectorPerBlock   [IN]  sector count per block in bcache
 * @param  blockNum         [IN]  block number of bcache
 * @param  blockCount       [IN]  block count of the disk
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval #OsBcache *      init succeded
 * @retval #NULL            init failed
 *
 * @par Dependency:
 * <ul><li>bcache.h</li></ul>
 *
 */
OsBcache *BlockCacheInit(struct inode *devNode,
                         UINT32 sectorSize,
                         UINT32 sectorPerBlock,
                         UINT32 blockNum,
                         UINT64 blockCount);

/**
 * @ingroup  bcache
 *
 * @par Description:
 * The BlockCacheDeinit() function shall deinit the bcache and release resources.
 *
 * @param  bc    [IN]  block cache instance
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval #VOID None.
 *
 * @par Dependency:
 * <ul><li>bcache.h</li></ul>
 *
 */
VOID BlockCacheDeinit(OsBcache *bc);

INT32 OsSdSync(INT32 id);

#ifdef LOSCFG_FS_FAT_CACHE_SYNC_THREAD
VOID BcacheSyncThreadInit(OsBcache *bc, INT32 id);
VOID BcacheSyncThreadDeinit(const OsBcache *bc);
#endif

UINT32 BcacheAsyncPrereadInit(OsBcache *bc);

VOID ResumeAsyncPreread(OsBcache *arg1, const OsBcacheBlock *arg2);

UINT32 BcacheAsyncPrereadDeinit(OsBcache *bc);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */
#endif  /* _BCACHE_H */
