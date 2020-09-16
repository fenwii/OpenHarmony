/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _NDK_LIST_H
#define _NDK_LIST_H

#include "stdint.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct NDK_DL_LIST {
    struct NDK_DL_LIST *pstPrev; /**< Current node's pointer to the previous node */
    struct NDK_DL_LIST *pstNext; /**< Current node's pointer to the next node */
} NDK_DL_LIST;

static inline void NDK_ListInit(NDK_DL_LIST *list)
{
    list->pstNext = list;
    list->pstPrev = list;
}

static inline void NDK_ListAdd(NDK_DL_LIST *list, NDK_DL_LIST *node)
{
    node->pstNext = list->pstNext;
    node->pstPrev = list;
    list->pstNext->pstPrev = node;
    list->pstNext = node;
}

static inline void NDK_ListDelete(NDK_DL_LIST *node)
{
    node->pstNext->pstPrev = node->pstPrev;
    node->pstPrev->pstNext = node->pstNext;
    node->pstNext = NULL;
    node->pstPrev = NULL;
}

static inline bool NDK_ListEmpty(NDK_DL_LIST *list)
{
    return (bool)(list->pstNext == list);
}
#define NDK_OFF_SET_OF(type, member) ((uintptr_t)&((type *)0)->member)
#define NDK_DL_LIST_ENTRY(item, type, member) \
    ((type *)(void *)((char *)(item) - NDK_OFF_SET_OF(type, member)))

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _NDK_LIST_H */
