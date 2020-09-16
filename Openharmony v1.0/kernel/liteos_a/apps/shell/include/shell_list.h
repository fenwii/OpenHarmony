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

#ifndef _SHELL_LIST_H
#define _SHELL_LIST_H

#include "sherr.h"
#include "stdint.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef size_t bool;

/**
 * @ingroup shell_list
 * Structure of a node in a doubly linked list.
 */
typedef struct SH_List {
    struct SH_List *pstPrev; /**< Current node's pointer to the previous node */
    struct SH_List *pstNext; /**< Current node's pointer to the next node */
} SH_List;

/**
 * @ingroup shell_list
 *
 * @par Description:
 * This API is used to initialize a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameter passed in should be ensured to be a legal pointer.</li>
 * </ul>
 *
 * @param list    [IN] Node in a doubly linked list.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline void SH_ListInit(SH_List *list)
{
    list->pstNext = list;
    list->pstPrev = list;
}

/**
 * @ingroup shell_list
 * @brief Point to the next node pointed to by the current node.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to point to the next node pointed to by the current node.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param object  [IN] Node in the doubly linked list.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_FIRST(object) ((object)->pstNext)

/**
 * @ingroup shell_list
 * @brief Point to the previous node pointed to by the current node.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to point to the previous node pointed to by the current node.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param object  [IN] Node in the doubly linked list.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_LAST(object) ((object)->pstPrev)

/**
 * @ingroup shell_list
 * @brief Insert a new node to a doubly linked list.
 *
 * @par Description:
 * This API is used to insert a new node to a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameters passed in should be ensured to be legal pointers.</li>
 * </ul>
 *
 * @param list    [IN] Doubly linked list where the new node is inserted.
 * @param node    [IN] New node to be inserted.
 *
 * @retval None
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListDelete
 */
static inline void SH_ListAdd(SH_List *list, SH_List *node)
{
    node->pstNext = list->pstNext;
    node->pstPrev = list;
    list->pstNext->pstPrev = node;
    list->pstNext = node;
}

/**
 * @ingroup shell_list
 * @brief Insert a node to the tail of a doubly linked list.
 *
 * @par Description:
 * This API is used to insert a new node to the tail of a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameters passed in should be ensured to be legal pointers.</li>
 * </ul>
 *
 * @param list     [IN] Doubly linked list where the new node is inserted.
 * @param node     [IN] New node to be inserted.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListAdd | SH_ListHeadInsert
 */
static inline void SH_ListTailInsert(SH_List *list, SH_List *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }

    SH_ListAdd(list->pstPrev, node);
}

/**
 * @ingroup shell_list
 * @brief Insert a node to the head of a doubly linked list.
 *
 * @par Description:
 * This API is used to insert a new node to the head of a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameters passed in should be ensured to be legal pointers.</li>
 * </ul>
 *
 * @param list     [IN] Doubly linked list where the new node is inserted.
 * @param node     [IN] New node to be inserted.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListAdd | SH_ListTailInsert
 */
static inline void SH_ListHeadInsert(SH_List *list, SH_List *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }

    SH_ListAdd(list, node);
}

/**
 * @ingroup shell_list
 *
 * @par Description:
 * <ul>
 * <li>This API is used to delete a specified node from a doubly linked list.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The parameter passed in should be ensured to be a legal pointer.</li>
 * </ul>
 *
 * @param node    [IN] Node to be deleted.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListAdd
 */
static inline void SH_ListDelete(SH_List *node)
{
    node->pstNext->pstPrev = node->pstPrev;
    node->pstPrev->pstNext = node->pstNext;
    node->pstNext = NULL;
    node->pstPrev = NULL;
}

/**
 * @ingroup shell_list
 * @brief Identify whether a specified doubly linked list is empty.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to return whether a doubly linked list is empty.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The parameter passed in should be ensured to be a legal pointer.</li>
 * </ul>
 *
 * @param list  [IN] Doubly linked list.
 *
 * @retval TRUE The doubly linked list is empty.
 * @retval FALSE The doubly linked list is not empty.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline bool SH_ListEmpty(SH_List *list)
{
    if (list == NULL) {
        return FALSE;
    }

    return (bool)(list->pstNext == list);
}

/**
 * @ingroup shell_list
 * @brief Insert a new list to a doubly linked list.
 *
 * @par Description:
 * This API is used to insert a new list to a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameters passed in should be ensured to be legal pointers.</li>
 * </ul>
 *
 * @param oldList    [IN] Doubly linked list where the new list is inserted.
 * @param newList    [IN] New list to be inserted.
 *
 * @retval None
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListDelete
 */
static inline void SH_ListAddList(SH_List *oldList, SH_List *newList)
{
    SH_List *oldListHead = oldList->pstNext;
    SH_List *oldListTail = oldList;
    SH_List *newListHead = newList;
    SH_List *newListTail = newList->pstPrev;

    oldListTail->pstNext = newListHead;
    newListHead->pstPrev = oldListTail;
    oldListHead->pstPrev = newListTail;
    newListTail->pstNext = oldListHead;
}

/**
 * @ingroup shell_list
 * @brief Insert a doubly list to the tail of a doubly linked list.
 *
 * @par Description:
 * This API is used to insert a new doubly list to the tail of a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameters passed in should be ensured to be legal pointers.</li>
 * </ul>
 *
 * @param oldList     [IN] Doubly linked list where the new list is inserted.
 * @param newList     [IN] New list to be inserted.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListAddList | SH_ListHeadInsertList
 */
static inline void SH_ListTailInsertList(SH_List *oldList, SH_List *newList)
{
    SH_ListAddList(oldList->pstPrev, newList);
}

/**
 * @ingroup shell_list
 * @brief Insert a doubly list to the head of a doubly linked list.
 *
 * @par Description:
 * This API is used to insert a new doubly list to the head of a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameters passed in should be ensured to be legal pointers.</li>
 * </ul>
 *
 * @param oldList     [IN] Doubly linked list where the new list is inserted.
 * @param newList     [IN] New list to be inserted.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see SH_ListAddList | SH_ListTailInsertList
 */
static inline void SH_ListHeadInsertList(SH_List *oldList, SH_List *newList)
{
    SH_ListAddList(oldList, newList);
}

/**
 * @ingroup shell_list
 * @brief Obtain the offset of a field to a structure address.
 *
 * @par  Description:
 * This API is used to obtain the offset of a field to a structure address.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param type   [IN] Structure name.
 * @param field  [IN] Name of the field of which the offset is to be measured.
 *
 * @retval Offset of the field to the structure address.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define OFFSET_OF_FIELD(type, field) ((uintptr_t)&((type *)0)->field)

/**
 * @ingroup shell_list
 * @brief Obtain the pointer to a doubly linked list in a structure.
 *
 * @par Description:
 * This API is used to obtain the pointer to a doubly linked list in a structure.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param type    [IN] Structure name.
 * @param member  [IN] Member name of the doubly linked list in the structure.
 *
 * @retval Pointer to the doubly linked list in the structure.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define LOS_OFF_SET_OF(type, member) ((uintptr_t)&((type *)0)->member)

/**
 * @ingroup shell_list
 * @brief Obtain the pointer to a structure that contains a doubly linked list.
 *
 * @par Description:
 * This API is used to obtain the pointer to a structure that contains a doubly linked list.
 * <ul>
 * <li>None.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param item    [IN] Current node's pointer to the next node.
 * @param type    [IN] Structure name.
 * @param member  [IN] Member name of the doubly linked list in the structure.
 *
 * @retval Pointer to the structure that contains the doubly linked list.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_ENTRY(item, type, member) \
    ((type *)(void *)((char *)(item) - LOS_OFF_SET_OF(type, member)))

/**
 * @ingroup shell_list
 * @brief Iterate over a doubly linked list of given type.
 *
 * @par Description:
 * This API is used to iterate over a doubly linked list of given type.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param item           [IN] Pointer to the structure that contains the doubly linked list that is to be traversed.
 * @param list           [IN] Pointer to the doubly linked list to be traversed.
 * @param type           [IN] Structure name.
 * @param member         [IN] Member name of the doubly linked list in the structure.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_FOR_EACH_ENTRY(item, list, type, member)             \
    for (item = SH_LIST_ENTRY((list)->pstNext, type, member);        \
         &(item)->member != (list);                                      \
         item = SH_LIST_ENTRY((item)->member.pstNext, type, member))

/**
 * @ingroup shell_list
 * @brief iterate over a doubly linked list safe against removal of list entry.
 *
 * @par Description:
 * This API is used to iterate over a doubly linked list safe against removal of list entry.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param item           [IN] Pointer to the structure that contains the doubly linked list that is to be traversed.
 * @param next           [IN] Save the next node.
 * @param list           [IN] Pointer to the doubly linked list to be traversed.
 * @param type           [IN] Structure name.
 * @param member         [IN] Member name of the doubly linked list in the structure.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_FOR_EACH_ENTRY_SAFE(item, next, list, type, member)               \
    for (item = SH_LIST_ENTRY((list)->pstNext, type, member),                     \
         next = SH_LIST_ENTRY((item)->member.pstNext, type, member);              \
         &(item)->member != (list);                                                   \
         item = next, next = SH_LIST_ENTRY((item)->member.pstNext, type, member))

/**
 * @ingroup shell_list
 * @brief Delete initialize a doubly linked list.
 *
 * @par Description:
 * This API is used to delete initialize a doubly linked list.
 * @attention
 * <ul>
 * <li>The parameter passed in should be ensured to be s legal pointer.</li>
 * </ul>
 *
 * @param list    [IN] Doubly linked list.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline void SH_ListDelInit(SH_List *list)
{
    list->pstNext->pstPrev = list->pstPrev;
    list->pstPrev->pstNext = list->pstNext;
    SH_ListInit(list);
}

/**
 * @ingroup shell_list
 * @brief iterate over a doubly linked list.
 *
 * @par Description:
 * This API is used to iterate over a doubly linked list.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param item           [IN] Pointer to the structure that contains the doubly linked list that is to be traversed.
 * @param list           [IN] Pointer to the doubly linked list to be traversed.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_FOR_EACH(item, list) \
    for (item = (list)->pstNext;         \
         (item) != (list);               \
         item = (item)->pstNext)

/**
 * @ingroup shell_list
 * @brief Iterate over a doubly linked list safe against removal of list entry.
 *
 * @par Description:
 * This API is used to iterate over a doubly linked list safe against removal of list entry.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param item           [IN] Pointer to the structure that contains the doubly linked list that is to be traversed.
 * @param next           [IN] Save the next node.
 * @param list           [IN] Pointer to the doubly linked list to be traversed.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_FOR_EACH_SAFE(item, next, list)      \
    for (item = (list)->pstNext, next = (item)->pstNext; \
         (item) != (list);                               \
         item = next, next = (item)->pstNext)

/**
 * @ingroup shell_list
 * @brief Initialize a double linked list.
 *
 * @par Description:
 * This API is used to initialize a double linked list.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param list           [IN] Pointer to the doubly linked list to be traversed.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>shell_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define SH_LIST_HEAD(list) SH_List list = { &(list), &(list) }

#define SH_ListPeekHeadType(list, type, element) do {            \
    type *__t;                                                  \
    if ((list)->pstNext == list) {                              \
        __t = NULL;                                             \
    } else {                                                    \
        __t = SH_LIST_ENTRY((list)->pstNext, type, element);    \
    }                                                           \
    __t;                                                        \
} while (0)

#define SH_ListRemoveHeadType(list, type, element) do {          \
    type *__t;                                                  \
    if ((list)->pstNext == list) {                              \
        __t = NULL;                                             \
    } else {                                                    \
        __t = SH_LIST_ENTRY((list)->pstNext, type, element);    \
        SH_ListDelete((list)->pstNext);                        \
    }                                                           \
    __t;                                                        \
} while (0)

#define SH_ListNextType(list, item, type, element) do {          \
    type *__t;                                                  \
    if ((item)->pstNext == list) {                              \
        __t = NULL;                                             \
    } else {                                                    \
        __t = SH_LIST_ENTRY((item)->pstNext, type, element);    \
    }                                                           \
    __t;                                                        \
} while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _SHELL_LIST_H */
