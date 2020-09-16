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

#ifndef __TEE_LIST_H_
#define __TEE_LIST_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct tee_list {
    struct tee_list *pstPrev; /**< Current node's pointer to the previous node */
    struct tee_list *pstNext; /**< Current node's pointer to the next node */
} tee_list_t;

static inline void TeeListInit(tee_list_t *list)
{
    list->pstNext = list;
    list->pstPrev = list;
}

#define TEE_LIST_FIRST(object) ((object)->pstNext)

#define TEE_LIST_LAST(object) ((object)->pstPrev)

static inline void TeeListAdd(tee_list_t *list, tee_list_t *node)
{
    node->pstNext = list->pstNext;
    node->pstPrev = list;
    list->pstNext->pstPrev = node;
    list->pstNext = node;
}

static inline void TeeListTailInsert(tee_list_t *list, tee_list_t *node)
{
    TeeListAdd(list->pstPrev, node);
}

static inline void TeeListHeadInsert(tee_list_t *list, tee_list_t *node)
{
    TeeListAdd(list, node);
}

static inline void TeeListDelete(tee_list_t *node)
{
    node->pstNext->pstPrev = node->pstPrev;
    node->pstPrev->pstNext = node->pstNext;
    node->pstNext = NULL;
    node->pstPrev = NULL;
}

static inline int TeeListEmpty(tee_list_t *list)
{
    return (list->pstNext == list);
}

static inline void TeeListAddList(tee_list_t *oldList, tee_list_t *newList)
{
    tee_list_t *oldListHead = oldList->pstNext;
    tee_list_t *oldListTail = oldList;
    tee_list_t *newListHead = newList;
    tee_list_t *newListTail = newList->pstPrev;

    oldListTail->pstNext = newListHead;
    newListHead->pstPrev = oldListTail;
    oldListHead->pstPrev = newListTail;
    newListTail->pstNext = oldListHead;
}

static inline void TeeListTailInsertList(tee_list_t *oldList, tee_list_t *newList)
{
    TeeListAddList(oldList->pstPrev, newList);
}

static inline void TeeListHeadInsertList(tee_list_t *oldList, tee_list_t *newList)
{
    TeeListAddList(oldList, newList);
}

#define OFFSET_OF_FIELD(type, field) ((unsigned int)&((type *)0)->field)

#define TEE_OFF_SET_OF(type, member) ((unsigned int)&((type *)0)->member)

#define TEE_LIST_ENTRY(item, type, member) \
    ((type *)(void *)((char *)(item) - TEE_OFF_SET_OF(type, member)))

#define TEE_LIST_FOR_EACH_ENTRY(item, list, type, member)             \
    for (item = TEE_LIST_ENTRY((list)->pstNext, type, member);        \
         &(item)->member != (list);                                      \
         item = TEE_LIST_ENTRY((item)->member.pstNext, type, member))

#define TEE_LIST_FOR_EACH_ENTRY_SAFE(item, next, list, type, member)               \
    for (item = TEE_LIST_ENTRY((list)->pstNext, type, member),                     \
         next = TEE_LIST_ENTRY((item)->member.pstNext, type, member);              \
         &(item)->member != (list);                                                   \
         item = next, next = TEE_LIST_ENTRY((item)->member.pstNext, type, member))

#define TEE_LIST_FOR_EACH(item, list) \
        for (item = (list)->pstNext;         \
             (item) != (list);               \
             item = (item)->pstNext)

#define TEE_LIST_FOR_EACH_SAFE(item, next, list)      \
        for (item = (list)->pstNext, next = (item)->pstNext; \
             (item) != (list);                               \
             item = next, next = (item)->pstNext)

#define TEE_LIST_HEAD(list) tee_list_t list = { &(list), &(list) }

#define TeeListPeekHeadType(list, type, element) ({            \
    type *__t;                                                  \
    if ((list)->pstNext == list) {                              \
        __t = NULL;                                             \
    } else {                                                    \
        __t = TEE_LIST_ENTRY((list)->pstNext, type, element); \
    }                                                           \
    __t;                                                        \
})

#define TeeListRemoveHeadType(list, type, element) ({          \
    type *__t;                                                  \
    if ((list)->pstNext == list) {                              \
        __t = NULL;                                             \
    } else {                                                    \
        __t = TEE_LIST_ENTRY((list)->pstNext, type, element); \
        TeeListDelete((list)->pstNext);                        \
    }                                                           \
    __t;                                                        \
})

#define TeeListNextType(list, item, type, element) ({          \
    type *__t;                                                  \
    if ((item)->pstNext == list) {                              \
        __t = NULL;                                             \
    } else {                                                    \
        __t = TEE_LIST_ENTRY((item)->pstNext, type, element); \
    }                                                           \
    __t;                                                        \
})

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __TEE_LIST_H_ */
