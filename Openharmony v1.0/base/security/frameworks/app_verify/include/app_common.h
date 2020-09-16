/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SECURITY_APP_COMMON_H
#define SECURITY_APP_COMMON_H

#include "app_verify_pub.h"
#include "log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_PRINT_LEN 1024
#define DOUBLE_SIZE  2
#define MAX_CHARACTER  9
#define BYTE_BITS  8
#define MAX_MALLOC_SIZE 0x100000  /* 1M */
#define MAX_HASH_SIZE 64

#define LOG_INFO(fmt, args...) HILOG_INFO(LOG_CORE, "["__FILE__":%d] :"fmt, __LINE__, ##args)
#define LOG_DEBUG(fmt, args...) HILOG_DEBUG(LOG_CORE, "["__FILE__":%d] :"fmt, __LINE__, ##args)
#define LOG_WARN(fmt, args...) HILOG_WARN(LOG_CORE, "["__FILE__":%d] :"fmt, __LINE__, ##args)
#define LOG_ERROR(fmt, args...) HILOG_ERROR(LOG_CORE, "["__FILE__":%d] :"fmt, __LINE__, ##args)
#define LOG_PRINT_STR(fmt, args...) HILOG_INFO(LOG_CORE, "["__FILE__":%d] :"fmt, __LINE__, ##args)

typedef struct TagVMemStats {
    void *buf;
    int len;
    int state;
    const char *fileName;
    int line;
    struct TagVMemStats *next;
} AppVMemStats;

typedef struct {
    AppVMemStats *head;
    int totalMem;
    int totalMallocCnt;
    int totalFree;
    int totalFreeCnt;
    int maxMemUsed;
} MemStastics;

#define P_NULL_RETURN_WTTH_LOG(v) \
do { \
    if ((v) == NULL) { \
        LOG_ERROR(#v" is null"); \
        return V_ERR; \
    } \
} \
while (0)

#define P_NULL_RETURN_RET_WTTH_LOG(v, ret) \
do { \
    if ((v) == NULL) { \
        LOG_ERROR(#v" is null"); \
        return ret; \
    } \
} \
while (0)

#define P_NULL_RETURN_NULL_WTTH_LOG(v) \
do { \
    if ((v) == NULL) { \
        LOG_ERROR(#v" is null"); \
        return NULL; \
    } \
} \
while (0)

#define P_ERR_RETURN_WTTH_LOG(v) \
do { \
    if ((v) != V_OK) { \
        LOG_ERROR(#v" not ok"); \
        return v; \
    } \
} \
while (0)

#define P_NULL_GOTO_WTTH_LOG(v) \
do { \
    if ((v) == NULL) { \
        LOG_ERROR(#v" is null"); \
        goto EXIT; \
    } \
} \
while (0)

#define P_ERR_GOTO_WTTH_LOG(v) \
do { \
    if ((v) != V_OK) { \
        LOG_ERROR(#v" not ok"); \
        goto EXIT; \
    } \
} \
while (0)

#define FREE_IF_NOT_NULL(p) \
do { \
    APPV_FREE(p); \
} \
while (0)

#define APPV_MALLOC(size) malloc(size)
#define APPV_FREE(buf) \
do { \
    if ((buf) != NULL) { \
        free(buf); \
        (buf) = NULL; \
    } \
} while (0)

long long HapGetInt64(const unsigned char *buf, int len);
int HapGetInt(const unsigned char *buf, int len);
short HapGetShort(const unsigned char *buf, int len);
void HapPutInt32(unsigned char *buf, int len, int value);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif