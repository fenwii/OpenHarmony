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

#include "mailbox_mempool.h"
#include <securec.h>
#include "smc.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"
#include "tzdriver_compat.h"

#define MAILBOX_PAGE_MAX (MAILBOX_POOL_SIZE >> PAGE_SHIFT)
#define MAILBOX_ORDER_MAX GET_ORDER(MAILBOX_POOL_SIZE)
static unsigned int g_mailboxMaxOrder = MAILBOX_ORDER_MAX;

struct MbPageT {
    struct list_head node;
    LosVmPage *page;
    int order; // block size
    unsigned int count; // whether be used
};

struct MbFreeAreaT {
    struct list_head pageList;
    int order;
};

struct MbZoneT {
    LosVmPage *allPages;
    struct MbPageT pages[MAILBOX_PAGE_MAX];
    struct MbFreeAreaT freeAreas[MAILBOX_ORDER_MAX + 1];
};

static struct MbZoneT g_mZone;
static mutex_t g_mbLock;

#ifdef DEF_ENG
static void MailboxShowStatus(void)
{
    unsigned int i;
    struct MbPageT *pos = NULL;
    struct list_head *head = NULL;
    unsigned int used = 0;

    pr_info("########################################\n");
    mutex_lock(&g_mbLock);
    for (i = 0; i < MAILBOX_PAGE_MAX; i++) {
        if (g_mZone.pages[i].count) {
            pr_info("page[%02d], order=%02d, count=%d\n", i, g_mZone.pages[i].order, g_mZone.pages[i].count);
            used += (1UL << (uint32_t)g_mZone.pages[i].order);
        }
    }
    pr_info("total usage:%u/%u\n", used, MAILBOX_PAGE_MAX);
    pr_info("----------------------------------------\n");

    for (i = 0; i < g_mailboxMaxOrder; i++) {
        head = &g_mZone.freeAreas[i].pageList;
        if (list_empty(head)) {
            pr_info("order[%02d] is empty\n", i);
        } else {
            list_for_each_entry(pos, head, node)
                pr_info("order[%02d]\n", i);
        }
    }
    mutex_unlock(&g_mbLock);

    pr_info("########################################\n");
}

#define MB_SHOW_LINE 64
#define BITS_OF_BYTE  8
static void MailboxShowDetails(void)
{
    unsigned int i;
    unsigned int used = 0;
    unsigned int left = 0;
    unsigned int order = 0;

    pr_info("----- show mailbox details -----");
    mutex_lock(&g_mbLock);
    for (i = 0; i < MAILBOX_PAGE_MAX; i++) {
        if ((i % MB_SHOW_LINE) == 0) {
            PRINTK("\n");
            PRINTK("%04d-%04d:", i, i + MB_SHOW_LINE);
        }

        if (g_mZone.pages[i].count) {
            left = 1 << (uint32_t)g_mZone.pages[i].order;
            order = g_mZone.pages[i].order;
            used += (1UL << (uint32_t)g_mZone.pages[i].order);
        }

        if (left) {
            left--;
            PRINTK("%01d", order);
        } else {
            PRINTK("X");
        }

        if (i > 1 && (i + 1) % (MB_SHOW_LINE / BITS_OF_BYTE) == 0) {
            PRINTK(" ");
        }
    }
    pr_info("\ntotal usage:%u/%u\n", used, MAILBOX_PAGE_MAX);
    mutex_unlock(&g_mbLock);
}
#endif

void *MailboxAlloc(size_t size, unsigned int flag)
{
    unsigned int i;
    struct MbPageT *pos = (struct MbPageT *)NULL;
    struct list_head *head = NULL;
    unsigned int order = GET_ORDER(ALIGN(size, SZ_4K));
    void *addr = NULL;

    if (size == 0) {
        tlogw("alloc 0 size mailbox\n");
        return NULL;
    }

    if (order > g_mailboxMaxOrder) {
        tloge("invalid order %d\n", order);
        return NULL;
    }

    mutex_lock(&g_mbLock);
    for (i = order; i <= g_mailboxMaxOrder; i++) {
        unsigned int j;

        head = &g_mZone.freeAreas[i].pageList;
        if (list_empty(head)) {
            continue;
        }

        pos = list_first_entry(head, struct MbPageT, node);

        pos->count = 1;
        pos->order = order;

        /* split and add free list */
        for (j = order; j < i; j++) {
            struct MbPageT *newPage = NULL;

            newPage = pos + (1UL << j);
            newPage->count = 0;
            newPage->order = j;
            list_add_tail(&newPage->node, &g_mZone.freeAreas[j].pageList);
        }
        list_del(&pos->node);
        addr = OsVmPageToVaddr(pos->page);
        break;
    }
    mutex_unlock(&g_mbLock);

    if (addr != NULL && (flag & MB_FLAG_ZERO)) {
        if (memset_s(addr, ALIGN(size, SZ_4K), 0,
            ALIGN(size, SZ_4K)) != EOK) {
            tloge("clean mailbox failed\n");
            MailboxFree(addr);
            return NULL;
        }
    }
    return addr;
}

void MailboxFree(const void *ptr)
{
    unsigned int i;
    LosVmPage *page = NULL;
    struct MbPageT *self = NULL;
    struct MbPageT *buddy = NULL;
    unsigned int selfIdx;
    unsigned int buddyIdx;

    if (ptr == NULL) {
        tloge("invalid ptr\n");
        return;
    }

    page = OsVmVaddrToPage((void *)ptr);
    if (page < g_mZone.allPages ||
        page >= (g_mZone.allPages + MAILBOX_PAGE_MAX)) {
        tloge("invalid ptr to free in mailbox\n");
        return;
    }

    mutex_lock(&g_mbLock);
    selfIdx = page - g_mZone.allPages;
    self = &g_mZone.pages[selfIdx];
    if (!self->count) {
        tloge("already freed in mailbox\n");
        mutex_unlock(&g_mbLock);
        return;
    }

    for (i = (unsigned int)self->order; i <=
        g_mailboxMaxOrder; i++) {
        selfIdx = page - g_mZone.allPages;
        buddyIdx = selfIdx ^ (1UL << i);
        self = &g_mZone.pages[selfIdx];
        buddy = &g_mZone.pages[buddyIdx];
        self->count = 0;
        /* is buddy free  */
        if ((unsigned int)buddy->order == i && buddy->count == 0) {
            /* release buddy */
            list_del(&buddy->node);
            /* combine self and buddy */
            if (selfIdx > buddyIdx) {
                page = buddy->page;
                buddy->order = (int)i + 1;
                self->order = -1;
            } else {
                self->order = (int)i + 1;
                buddy->order = -1;
            }
        } else {
            /* release self */
            list_add_tail(&self->node, &g_mZone.freeAreas[i].pageList);
            mutex_unlock(&g_mbLock);
            return;
        }
    }
    mutex_unlock(&g_mbLock);
}

struct MbCmdPack *MailboxAllocCmdPack(void)
{
    void *pack = MailboxAlloc(SZ_4K, MB_FLAG_ZERO);

    if (pack == NULL) {
        tloge("alloc mb cmd pack failed\n");
    }
    return (struct MbCmdPack *)pack;
}

void *MailboxCopyAlloc(const void *src, size_t size)
{
    void *mbPtr = NULL;

    if ((src == NULL) || (size == 0)) {
        tloge("invali src to alloc mailbox copy\n");
        return NULL;
    }

    mbPtr = MailboxAlloc(size, 0);
    if (mbPtr == NULL) {
        tloge("alloc size(%zu) mailbox failed\n", size);
        return NULL;
    }

    if (memcpy_s(mbPtr, size, src, size)) {
        tloge("memcpy to mailbox failed\n");
        MailboxFree(mbPtr);
        return NULL;
    }

    return mbPtr;
}

#ifdef DEF_ENG
struct MbDbgEntry {
    struct list_head node;
    unsigned int idx;
    void *ptr;
};

static LINUX_LIST_HEAD(g_mbDbgList);
static DEFINE_MUTEX(g_mbDbgLock);
static unsigned int g_mbDbgEntryCount = 1;
static unsigned int g_mbDbgLastRes; /* only cache 1 opt result */

static unsigned int MbDbgAddEntry(void *ptr)
{
    struct MbDbgEntry *newEntry = NULL;

    newEntry = malloc(sizeof(*newEntry));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)newEntry)) {
        tloge("alloc entry failed\n");
        return 0;
    }
    INIT_LIST_HEAD(&newEntry->node);
    newEntry->ptr = ptr;
    mutex_lock(&g_mbDbgLock);
    newEntry->idx = g_mbDbgEntryCount;
    /* to make sure g_mbDbgEntryCount==0 is invalid */
    if ((g_mbDbgEntryCount++) == 0) {
        g_mbDbgEntryCount++;
    }
    list_add_tail(&newEntry->node, &g_mbDbgList);
    mutex_unlock(&g_mbDbgLock);

    return newEntry->idx;
}

static void MbDbgRemoveEntry(unsigned int idx)
{
    struct MbDbgEntry *pos = NULL;

    mutex_lock(&g_mbDbgLock);
    list_for_each_entry(pos, &g_mbDbgList, node) {
        if (pos->idx == idx) {
            MailboxFree(pos->ptr);
            list_del(&pos->node);
            free(pos);
            mutex_unlock(&g_mbDbgLock);
            return;
        }
    }
    mutex_unlock(&g_mbDbgLock);

    tloge("entry %u invalid\n", idx);
}

static void MbDbgReset(void)
{
    struct MbDbgEntry *pos = NULL;
    struct MbDbgEntry *tmp = NULL;

    mutex_lock(&g_mbDbgLock);
    list_for_each_entry_safe(pos, tmp, &g_mbDbgList, node) {
        MailboxFree(pos->ptr);
        list_del(&pos->node);
        free(pos);
    }
    g_mbDbgEntryCount = 0;
    mutex_unlock(&g_mbDbgLock);
}

#define MB_WRITE_SIZE 64

static int CheckDbgOptWrite(struct file *filp, const char __user *ubuf, char *obuf, size_t cnt)
{
    bool checkValue = (filp == NULL);
    if (checkValue || ubuf == NULL) {
        return -EINVAL;
    }
    if (cnt >= MB_WRITE_SIZE || cnt == 0) {
        return -EINVAL;
    }
    if (copy_from_user(obuf, ubuf, cnt)) {
        return -EFAULT;
    }
    return 0;
}

static ssize_t MbDbgOptWrite(struct file *filp, const char __user *ubuf, size_t cnt)
{
    char buf[MB_WRITE_SIZE] = {0};
    char *cmd = NULL;
    char *value = NULL;
    char *endPtr = NULL;
    int ret = CheckDbgOptWrite(filp, ubuf, buf, cnt);
    if (ret) {
        return ret;
    }

    buf[cnt] = 0;
    value = buf;
    if (!strncmp(value, "reset", strlen("reset"))) {
        tlogi("mb dbg reset\n");
        MbDbgReset();
        return cnt;
    }

    cmd = strsep(&value, ":");
    if (cmd == NULL || value == NULL) {
        tloge("no valid cmd or value for mb dbg\n");
        return -EFAULT;
    }

    if (!strncmp(cmd, "alloc", strlen("alloc"))) {
        unsigned int allocSize = strtoul(value, &endPtr, 0);
        if ((endPtr == NULL) || (*endPtr != 0)) {
            tloge("invalid value format for mb dbg\n");
            return cnt;
        }

        unsigned int idx;
        void *ptr = MailboxAlloc(allocSize, 0);
        if (ptr != NULL) {
            idx = MbDbgAddEntry(ptr);
            if (idx == 0) {
                MailboxFree(ptr);
            }
            g_mbDbgLastRes = idx;
        } else {
            tloge("alloc order=%u in mailbox failed\n", allocSize);
        }
    } else if (!strncmp(cmd, "free", strlen("free"))) {
        unsigned int freeIdx = strtoul(value, &endPtr, 0);
        if ((endPtr == NULL) || (*endPtr != 0)) {
            tloge("invalid value format for mb dbg\n");
            return cnt;
        }

        MbDbgRemoveEntry(freeIdx);
    } else {
        tloge("invalid format for mb dbg\n");
    }

    return cnt;
}

#define DBG_READ_BUFSIZE 16
static ssize_t MbDbgOptRead(struct file *filp, char __user *ubuf,
    size_t cnt)
{
    char buf[DBG_READ_BUFSIZE] = {0};
    ssize_t ret;

    (void)(filp);

    ret = snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "%u\n", g_mbDbgLastRes);
    if (ret < 0) {
        tloge("snprintf idx failed\n");
        return -EINVAL;
    }

    return SimpleReadFromBuffer(ubuf, cnt, buf, ret);
}

static const struct file_operations_vfs g_mbDbgOptFops = {
    .read = MbDbgOptRead,
    .write = MbDbgOptWrite,
};

static ssize_t MbDbgStateRead(struct file *filp, char __user *ubuf,
    size_t cnt)
{
    (void)(filp);
    (void)(ubuf);
    MailboxShowStatus();
    MailboxShowDetails();
    return 0;
}

static const struct file_operations_vfs mb_dbg_state_fops = {
    .read = MbDbgStateRead,
};
#endif

static int MailboxRegister(const void *mbPool, unsigned int size)
{
    TcNsOperation *operation = NULL;
    TcNsSmcCmd *smcCmd = NULL;
    int ret = 0;

    smcCmd = calloc(1, sizeof(*smcCmd));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)smcCmd)) {
        tloge("alloc smcCmd failed\n");
        return -EIO;
    }
    operation = calloc(1, sizeof(*operation));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)operation)) {
        tloge("alloc operation failed\n");
        ret = -EIO;
        goto FREE_SMC_CMD;
    }

    operation->paramTypes = TEE_PARAM_TYPE_VALUE_INPUT |
        (TEE_PARAM_TYPE_VALUE_INPUT << TEE_PARAM_NUM);
    operation->params[TEE_PARAM_ONE].value.a = LOS_PaddrQuery((void *)mbPool);
    operation->params[TEE_PARAM_ONE].value.b = 0;
    operation->params[TEE_PARAM_TWO].value.a = size;

    smcCmd->globalCmd = true;
    smcCmd->cmdId = GLOBAL_CMD_ID_REGISTER_MAILBOX;
    smcCmd->operationPhys = LOS_PaddrQuery(operation);
    smcCmd->operationHphys = 0;

    ret = TcNsSmc(smcCmd);
    if (ret != TEEC_SUCCESS) {
        tloge("resigter mailbox failed\n");
        ret = -EIO;
    }

    free(operation);
    operation = NULL;
FREE_SMC_CMD:
    free(smcCmd);
    smcCmd = NULL;
    return ret;
}

#define TC_NS_CLIENT_MEILBOX_OPT_NAME "/dev/tz_mailbox_opt"
#define TC_NS_CLIENT_MEILBOX_STATE_NAME "/dev/tz_mailbox_state"

int MailboxMempoolInit(void)
{
    int i;
    struct MbPageT *mbPage = NULL;
    struct MbFreeAreaT *area = NULL;
    LosVmPage *allPages = NULL;

    allPages = MailboxPoolAllocPages(g_mailboxMaxOrder);
    if (allPages == NULL) {
        tloge("fail to alloc mailbox mempool\n");
        return -ENOMEM;
    }
    if (MailboxRegister(OsVmPageToVaddr(allPages), MAILBOX_POOL_SIZE)) {
        tloge("register mailbox failed\n");
        MailboxPoolFreePages(allPages, g_mailboxMaxOrder);
        return -EIO;
    }
    for (i = 0; i < MAILBOX_PAGE_MAX; i++) {
        g_mZone.pages[i].order = -1;
        g_mZone.pages[i].count = 0;
        g_mZone.pages[i].page = &allPages[i];
    }
    g_mZone.pages[0].order = g_mailboxMaxOrder;
    for (i = 0; i <= g_mailboxMaxOrder; i++) {
        area = &g_mZone.freeAreas[i];
        INIT_LIST_HEAD(&area->pageList);
        area->order = i;
    }

    mbPage = &g_mZone.pages[0];
    list_add_tail(&mbPage->node, &area->pageList);
    g_mZone.allPages = allPages;
    mutex_init(&g_mbLock);

#ifdef DEF_ENG
    int ret = CreateTcClientDevice(TC_NS_CLIENT_MEILBOX_OPT_NAME, &g_mbDbgOptFops);
    if (ret != EOK) {
        return ret;
    }

    ret = CreateTcClientDevice(TC_NS_CLIENT_MEILBOX_STATE_NAME, &mb_dbg_state_fops);
    if (ret != EOK) {
        return ret;
    }
#endif
    return 0;
}

void MailboxMempoolDestroy(void)
{
    MailboxPoolFreePages(g_mZone.allPages, g_mailboxMaxOrder);
    g_mZone.allPages = NULL;
}
