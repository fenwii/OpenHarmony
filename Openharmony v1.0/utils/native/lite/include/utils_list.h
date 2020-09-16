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

/*
 * @defgroup utils_list Doubly linked list
 * @ingroup utils
 * @attention
 * <ul>
 * <li>All of the APIs provided in this module are not thread-safe.</li>
 * </ul>
 */

#ifndef _UTILS_LIST_H
#define _UTILS_LIST_H

#include <stdbool.h>
#include "ohos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct UTILS_DL_LIST {
    struct UTILS_DL_LIST *pstPrev; /* < Current node's pointer to the previous node */
    struct UTILS_DL_LIST *pstNext; /* < Current node's pointer to the next node */
} UTILS_DL_LIST;

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline void UtilsListInit(UTILS_DL_LIST *list)
{
    list->pstNext = list;
    list->pstPrev = list;
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_FIRST(object) ((object)->pstNext)

/*
 * @ingroup utils_list
 * @brief Node is the end of the list.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to test node is the end of the list.</li>
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_IS_END(list, node) ((list) == (node) ? TRUE : FALSE)

/*
 * @ingroup utils_list
 * @brief Node is on the list.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to test node is on the list.</li>
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_IS_ON_QUEUE(node) ((node)->pstPrev != NULL && (node)->pstNext != NULL)

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_LAST(object) ((object)->pstPrev)

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListDelete
 */
static inline void UtilsListAdd(UTILS_DL_LIST *list, UTILS_DL_LIST *node)
{
    node->pstNext = list->pstNext;
    node->pstPrev = list;
    list->pstNext->pstPrev = node;
    list->pstNext = node;
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListAdd | UtilsListHeadInsert
 */
static inline void UtilsListTailInsert(UTILS_DL_LIST *list, UTILS_DL_LIST *node)
{
    UtilsListAdd(list->pstPrev, node);
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListAdd | UtilsListTailInsert
 */
static inline void UtilsListHeadInsert(UTILS_DL_LIST *list, UTILS_DL_LIST *node)
{
    UtilsListAdd(list, node);
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListAdd
 */
static inline void UtilsListDelete(UTILS_DL_LIST *node)
{
    node->pstNext->pstPrev = node->pstPrev;
    node->pstPrev->pstNext = node->pstNext;
    node->pstNext = NULL;
    node->pstPrev = NULL;
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline bool UtilsListEmpty(UTILS_DL_LIST *list)
{
    return (bool)(list->pstNext == list);
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListDelete
 */
static inline void UtilsListAddList(UTILS_DL_LIST *oldList, UTILS_DL_LIST *newList)
{
    UTILS_DL_LIST *oldListHead = oldList->pstNext;
    UTILS_DL_LIST *oldListTail = oldList;
    UTILS_DL_LIST *newListHead = newList;
    UTILS_DL_LIST *newListTail = newList->pstPrev;

    oldListTail->pstNext = newListHead;
    newListHead->pstPrev = oldListTail;
    oldListHead->pstPrev = newListTail;
    newListTail->pstNext = oldListHead;
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListAddList | UtilsListHeadInsertList
 */
static inline void UtilsListTailInsertList(UTILS_DL_LIST *oldList, UTILS_DL_LIST *newList)
{
    UtilsListAddList(oldList->pstPrev, newList);
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see UtilsListAddList | UtilsListTailInsertList
 */
static inline void UtilsListHeadInsertList(UTILS_DL_LIST *oldList, UTILS_DL_LIST *newList)
{
    UtilsListAddList(oldList, newList);
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define OFFSET_OF_FIELD(type, field) ((unsigned int)&((type *)0)->field)

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_OFF_SET_OF(type, member) ((unsigned int)&((type *)0)->member)

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_ENTRY(item, type, member) \
    ((type *)(void *)((char *)(item) - UTILS_OFF_SET_OF(type, member)))

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_FOR_EACH_ENTRY(item, list, type, member)             \
    for (item = UTILS_DL_LIST_ENTRY((list)->pstNext, type, member);        \
         &(item)->member != (list);                                      \
         item = UTILS_DL_LIST_ENTRY((item)->member.pstNext, type, member))

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_FOR_EACH_ENTRY_SAFE(item, next, list, type, member)               \
    for (item = UTILS_DL_LIST_ENTRY((list)->pstNext, type, member),                     \
         next = UTILS_DL_LIST_ENTRY((item)->member.pstNext, type, member);              \
         &(item)->member != (list);                                                   \
         item = next, next = UTILS_DL_LIST_ENTRY((item)->member.pstNext, type, member))

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
static inline void UtilsListDelInit(UTILS_DL_LIST *list)
{
    list->pstNext->pstPrev = list->pstPrev;
    list->pstPrev->pstNext = list->pstNext;
    UtilsListInit(list);
}

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_FOR_EACH(item, list) \
    for (item = (list)->pstNext;         \
         (item) != (list);               \
         item = (item)->pstNext)

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_FOR_EACH_SAFE(item, next, list)      \
    for (item = (list)->pstNext, next = (item)->pstNext; \
         (item) != (list);                               \
         item = next, next = (item)->pstNext)

/*
 * @ingroup utils_list
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
 * <ul><li>utils_list.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define UTILS_DL_LIST_HEAD(list) UTILS_DL_LIST list = { &(list), &(list) }

#define UTILS_ListPeekHeadType(list, type, element)                    \
    do {                                                               \
        type *__t;                                                     \
        if ((list)->pstNext == list) {                                 \
            __t = NULL;                                                \
        } else {                                                       \
            __t = UTILS_DL_LIST_ENTRY((list)->pstNext, type, element); \
        }                                                              \
        __t;                                                           \
    } while (0)

#define UTILS_ListRemoveHeadType(list, type, element)                  \
    do {                                                               \
        type *__t;                                                     \
        if ((list)->pstNext == list) {                                 \
            __t = NULL;                                                \
        } else {                                                       \
            __t = UTILS_DL_LIST_ENTRY((list)->pstNext, type, element); \
            UtilsListDelete((list)->pstNext);                         \
        }                                                              \
        __t;                                                           \
    } while (0)

#define UTILS_ListNextType(list, item, type, element)                  \
    do {                                                               \
        type *__t;                                                     \
        if ((item)->pstNext == list) {                                 \
            __t = NULL;                                                \
        } else {                                                       \
            __t = UTILS_DL_LIST_ENTRY((item)->pstNext, type, element); \
        }                                                              \
        __t;                                                           \
    } while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _UTILS_LIST_H */