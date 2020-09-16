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

#include "hiview_hievent.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "los_memory.h"
#include "los_task_pri.h"
#include "los_process_pri.h"
#include "los_task_pri.h"
#include "los_mux.h"
#include "los_mp.h"
#include "los_typedef.h"

#include "hievent_driver.h"

#define INT_TYPE_MAX_LEN    21

#define MAX_PATH_LEN        256
#define MAX_STR_LEN         (10 * 1024)

/* 64K is max length of /dev/hwlog_exception */
#define EVENT_INFO_BUF_LEN         (64 * 1024)
#define EVENT_INFO_PACK_BUF_LEN    (2 * 1024)

#define HWLOG_ERR  PRINT_ERR
#define HWLOG_INFO PRINT_INFO

#define BUF_POINTER_FORWARD                     \
    do {                                        \
        if (tmplen < len) {                     \
            tmp += tmplen;                      \
            len -= tmplen;                      \
        } else {                                \
            HWLOG_ERR("string over length");    \
            tmp += len;                         \
            len = 0;                            \
        }                                       \
    } while (0)

struct HiviewHieventPayload {
    char *key;
    char *value;
    struct HiviewHieventPayload *next;
};

static int HiviewHieventConvertString(struct HiviewHievent *event, char **pbuf);

static struct HiviewHieventPayload *HiviewHieventPayloadCreate(void);

static void HiviewHieventPayloadDestroy(struct HiviewHieventPayload *p);

static struct HiviewHieventPayload *HiviewHieventGetPayload(struct HiviewHieventPayload *head,
                                                            const char *key);

static void HiviewHieventAddPayload(struct HiviewHievent *obj,
                                    struct HiviewHieventPayload *payload);

static struct HiviewHieventPayload *HiviewHieventPayloadCreate(void)
{
    struct HiviewHieventPayload *payload = NULL;

    payload = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR,
                           sizeof(struct HiviewHieventPayload));
    if (!payload) {
        return NULL;
    }

    payload->key = NULL;
    payload->value = NULL;
    payload->next = NULL;

    return payload;
}

static void HiviewHieventPayloadDestroy(struct HiviewHieventPayload *p)
{
    if (!p) {
        return;
    }

    if (p->value) {
        LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, p->value);
    }

    LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, p->key);
    LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, p);
}

static struct HiviewHieventPayload *HiviewHieventGetPayload(struct HiviewHieventPayload *head,
                                                            const char *key)
{
    struct HiviewHieventPayload *p = head;

    while (p) {
        if (key && p->key) {
            if (strcmp(p->key, key) == 0) {
                return p;
            }
        }
        p = p->next;
    }

    return NULL;
}

static void HiviewHieventAddPayload(struct HiviewHievent *obj,
                                    struct HiviewHieventPayload *payload)
{
    if (!obj->head) {
        obj->head = payload;
    } else {
        struct HiviewHieventPayload *p = obj->head;

        while (p->next) {
            p = p->next;
        }
        p->next = payload;
    }
}

struct HiviewHievent *HiviewHieventCreate(unsigned int eventid)
{
    struct HiviewHievent *event = NULL;

    /* combined event obj struct */
    event = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, sizeof(*event));
    if (!event) {
        return NULL;
    }

    (VOID)memset_s(event, sizeof(*event), 0, sizeof(*event));
    event->eventid = eventid;
    HWLOG_INFO("%s : %u\n", __func__, eventid);

    return (void *)event;
}

int HiviewHieventPutIntegral(struct HiviewHievent *event,
                             const char *key, long value)
{
    int ret;
    struct HiviewHieventPayload *payload = NULL;

    if ((!event) || (!key)) {
        HWLOG_ERR("Bad input event or key for %s", __func__);
        return -EINVAL;
    }

    payload = HiviewHieventGetPayload(event->head, key);
    if (!payload) {
        payload = HiviewHieventPayloadCreate();
        if (!payload) {
            return -ENOMEM;
        }
        payload->key = strdup(key);
        HiviewHieventAddPayload(event, payload);
    }

    if (payload->value) {
        LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, payload->value);
    }

    payload->value = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, INT_TYPE_MAX_LEN);
    if (!payload->value) {
        return -ENOMEM;
    }
    (VOID)memset_s(payload->value, INT_TYPE_MAX_LEN, 0, INT_TYPE_MAX_LEN);
    ret = snprintf_s(payload->value, INT_TYPE_MAX_LEN, INT_TYPE_MAX_LEN - 1,
                     "%d", (int)value);
    if (ret < 0) {
        return -ENOMEM;
    }

    return 0;
}

int HiviewHieventPutString(struct HiviewHievent *event,
                           const char *key, const char *value)
{
    struct HiviewHieventPayload *payload = NULL;
    int len;

    if ((!event) || (!key) || (!value)) {
        HWLOG_ERR("Bad key for %s", __func__);
        return -EINVAL;
    }

    payload = HiviewHieventGetPayload(event->head, key);
    if (!payload) {
        payload = HiviewHieventPayloadCreate();
        if (!payload) {
            return -ENOMEM;
        }
        payload->key = strdup(key);
        HiviewHieventAddPayload(event, payload);
    }

    if (payload->value) {
        LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, payload->value);
    }

    len = strlen(value);
    /* prevent length larger than MAX_STR_LEN */
    if (len > MAX_STR_LEN) {
        len = MAX_STR_LEN;
    }
    payload->value = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, len + 1);
    if (!payload->value) {
        return -ENOMEM;
    }
    (VOID)memset_s(payload->value, len + 1, 0, len + 1);
    if (EOK == strncpy_s(payload->value, len + 1, value, len)) {
        payload->value[len] = '\0';
    }

    return 0;
}

int HiviewHieventSetTime(struct HiviewHievent *event, long long seconds)
{
    if ((!event) || (seconds == 0)) {
        HWLOG_ERR("Bad input for %s", __func__);
        return -EINVAL;
    }
    event->time = seconds;
    return 0;
}

static int AppendArrayItem(char **pool, int poolLen, const char *path)
{
    int i;

    if ((!path) || (path[0] == 0)) {
        HWLOG_ERR("Bad path %s", __func__);
        return -EINVAL;
    }

    if (strlen(path) > MAX_PATH_LEN) {
        HWLOG_ERR("file path over max: %d", MAX_PATH_LEN);
        return -EINVAL;
    }

    for (i = 0; i < poolLen; i++) {
        if (pool[i] != 0) {
            continue;
        }
        pool[i] = strdup(path);
        if (pool[i] == NULL) {
            return -ENOMEM;
        }
        break;
    }

    if (i == MAX_PATH_NUMBER) {
        HWLOG_ERR("Too many pathes");
        return -EINVAL;
    }

    return 0;
}

int HiviewHieventAddFilePath(struct HiviewHievent *event, const char *path)
{
    if (!event) {
        HWLOG_ERR("Bad path %s", __func__);
        return -EINVAL;
    }
    return AppendArrayItem(event->filePath, MAX_PATH_NUMBER, path);
}

/* make string ":" to "::", ";" to ";;", and remove newline character
 * for example: "abc:def;ghi" transfer to "abc::def;;ghi"
 */
static char *HiviewHieventMakeRegular(char *value)
{
    int count = 0;
    int len = 0;
    char *temp = value;
    char *regular = NULL;
    char *regularTemp = NULL;

    while (*temp != '\0') {
        if (*temp == ':') {
            count++;
        } else if (*temp == ';') {
            count++;
        } else if ((*temp == '\n') || (*temp == '\r')) {
            *temp = ' ';
        }
        temp++;
        len++;
    }

    /* no need to transfer, just return old value */
    if (count == 0) {
        return value;
    }

    size_t regularLen = len + count * 2 + 1; // 2 char in a byte
    regular = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, regularLen);
    if (!regular) {
        return NULL;
    }
    (VOID)memset_s(regular, regularLen, 0, regularLen);
    regularTemp = regular;
    temp = value;
    while (*temp != 0) {
        if ((*temp == ':') || (*temp == ';')) {
            *regularTemp++ = *temp;
        }
        *regularTemp++ = *temp;
        temp++;
    }
    *regularTemp = '\0';

    return regular;
}

int LogBufToException(char category, int level, char logType,
                      char sn, const char *msg, int msglen)
{
    struct IdapHeader *hdr;
    size_t bufLen = sizeof(int) + sizeof(struct IdapHeader) + msglen;
    char *buffer = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, bufLen);
    if (!buffer) {
        return -ENOMEM;
    }

    int *checkCode = (int *)buffer;
    *checkCode = CHECK_CODE;

    hdr = (struct IdapHeader *)(buffer + sizeof(int));
    hdr->level = level;
    hdr->category = category;
    hdr->logType = logType;
    hdr->sn = sn;

    int ret = memcpy_s(buffer + sizeof(int) + sizeof(struct IdapHeader),
                       msglen, msg, msglen);
    if (ret != EOK) {
        goto out;
    }

    ret = HieventWriteInternal(buffer, bufLen);

out:
    LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, buffer);

    return ret;
}

static int HiviewHieventFillPayload(struct HiviewHievent *event, char **pbuf,
                                    char *tmp, int length)
{
    struct HiviewHieventPayload *p = event->head;
    int len = length;
    int tmplen = 0;
    unsigned int keycount = 0;
    while (p) {
        char *value = NULL;
        char *regularValue = NULL;
        int needFree = 1;

        if (!p->value) {
            p = p->next;
            continue;
        }
        if (keycount == 0) {
            tmplen = snprintf_s(tmp, len, len - 1, " --extra ");
            BUF_POINTER_FORWARD;
        }
        keycount++;

        /* fill key */
        if (p->key) {
            tmplen = snprintf_s(tmp, len, len - 1, "%s:", p->key);
        }
        BUF_POINTER_FORWARD;
        /* fill value */
        tmplen = 0;

        value = p->value;
        regularValue = HiviewHieventMakeRegular(value);
        if (!regularValue) {
            regularValue = "NULL";
            needFree = 0;
        }
        tmplen = snprintf_s(tmp, len, len - 1, "%s;", regularValue);
        if ((value != regularValue) && needFree) {
            free(regularValue);
        }
        BUF_POINTER_FORWARD;
        p = p->next;
    }
    return len;
}

static int HiviewHieventConvertString(struct HiviewHievent *event, char **pbuf)
{
    int len;
    char *tmp = NULL;
    int tmplen = 0;
    unsigned int i;

    char *buf = LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, EVENT_INFO_BUF_LEN);
    if (!buf) {
        *pbuf = NULL;
        return 0;
    }
    (VOID)memset_s(buf, EVENT_INFO_BUF_LEN, 0, EVENT_INFO_BUF_LEN);
    len = EVENT_INFO_BUF_LEN;
    tmp = buf;

    /* fill eventid */
    tmplen = snprintf_s(tmp, len, len - 1, "eventid %d", event->eventid);
    BUF_POINTER_FORWARD;

    /* fill the path */
    for (i = 0; i < MAX_PATH_NUMBER; i++) {
        if (!event->filePath[i]) {
            break;
        }
        tmplen = snprintf_s(tmp, len, len - 1, " -i %s",
                            event->filePath[i]);
        BUF_POINTER_FORWARD;
    }

    /* fill time */
    if (event->time) {
        tmplen = snprintf_s(tmp, len, len - 1, " -t %lld",  event->time);
        BUF_POINTER_FORWARD;
    }

    /* fill the payload info */
    len = HiviewHieventFillPayload(event, pbuf, tmp, len);
    *pbuf = buf;
    return (EVENT_INFO_BUF_LEN - len);
}

#define IDAP_LOGTYPE_CMD 1
static int HiviewHieventWriteLogException(char *str, const int strlen)
{
    char tempchr;
    char *strptr = str;
    int leftBufLen = strlen + 1;
    int sentcnt = 0;

    while (leftBufLen > 0) {
        if (leftBufLen > EVENT_INFO_PACK_BUF_LEN) {
            tempchr = strptr[EVENT_INFO_PACK_BUF_LEN - 1];
            strptr[EVENT_INFO_PACK_BUF_LEN - 1] = '\0';
            LogBufToException(0, 0, IDAP_LOGTYPE_CMD, 1,
                              strptr, EVENT_INFO_PACK_BUF_LEN);
            leftBufLen -= (EVENT_INFO_PACK_BUF_LEN - 1);
            strptr += (EVENT_INFO_PACK_BUF_LEN - 1);
            strptr[0] = tempchr;
            sentcnt++;
        } else {
            LogBufToException(0, 0, IDAP_LOGTYPE_CMD, 0,
                              strptr, leftBufLen);
            sentcnt++;
            break;
        }
    }

    return sentcnt;
}

int HiviewHieventReport(struct HiviewHievent *obj)
{
    char *str = NULL;
    int bufLen;
    int sentPacket;

    if (!obj) {
        HWLOG_ERR("Bad event %s", __func__);
        return -EINVAL;
    }

    bufLen = HiviewHieventConvertString(obj, &str);
    if (!str) {
        return -EINVAL;
    }
    sentPacket = HiviewHieventWriteLogException(str, bufLen);
    HWLOG_INFO("report: %s", str);
    LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, str);

    return sentPacket;
}

void HiviewHieventDestroy(struct HiviewHievent *event)
{
    int i;
    struct HiviewHieventPayload *p = NULL;

    if (!event) {
        return;
    }
    p = event->head;
    while (p) {
        struct HiviewHieventPayload *del = p;

        p = p->next;
        HiviewHieventPayloadDestroy(del);
    }
    event->head = NULL;
    for (i = 0; i < MAX_PATH_NUMBER; i++) {
        LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, event->filePath[i]);
        event->filePath[i] = NULL;
    }
    LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, event);
}
