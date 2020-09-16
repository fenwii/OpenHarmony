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

#include <linux/types.h>

#ifndef _TEE_CLIENT_LIST_H_
#define _TEE_CLIENT_LIST_H_
/*
 * @ingroup TEEC_List
 * Linked list type
 */
struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
};

#define TEEK_INIT_LIST_HEAD(list) do { \
    (list)->next = (list);        \
    (list)->prev = (list);        \
} while (0)

#define LIST_FOR_EACH(node, list)  for ((node) = (list)->next; (node) != (list); (node) = (node)->next)

/*
 * @ingroup TEEC_List
 * @brief Define a linked list node.
 * @par Description
 * Defines a linked list node and initializes it.
 * @param name [IN] linked list node name
 */
#define LIST_DECLARE(name) \
    struct ListNode (name) = { \
        .next = &(name), \
        .prev = &(name), \
    }

#ifndef NULL
#define NULL 0
#endif

/*
 * @ingroup TEEC_List
 * Obtains the prev node of the linked list.
 */
#define LIST_TAIL(list) ((list)->prev)

/*
 * @ingroup TEEC_List
 * Check whether the linked list is empty.
 */
#define LIST_EMPTY(list) ((list) == (list)->next)

/*
 * @ingroup  TEEC_List
 * @brief Inserts a new node from the head of a linked list.
 *
 * @par Description
 * Inserts a new node from the head of a linked list
 *
 * @param list [IN/OUT]Pointer to the linked list header, the value cannot be empty.
 * @param entry [IN/OUT]Pointer to the new linked list node, the value cannot be empty.
 */
static inline void ListInsertHead(struct ListNode *list,
    struct ListNode *entry)
{
    list->next->prev = entry;
    entry->next = list->next;
    entry->prev = list;
    list->next = entry;
}

/*
 * @ingroup  TEEC_List
 * @brief Inserts a new node at the end of the linked list.
 *
 * @par Description
 * Inserts a new node at the end of the linked list.
 *
 * @param list [IN/OUT]Pointer to the linked list header, the value cannot be empty.
 * @param entry [IN/OUT]Pointer to the new linked list node, the value cannot be empty.
 */
static inline void ListInsertTail(struct ListNode *list,
    struct ListNode *entry)
{
    entry->next = list;
    entry->prev = list->prev;
    list->prev->next = entry;
    list->prev = entry;
}

/*
 * @ingroup  TEEC_List
 * @brief Delete node
 *
 * @par Description
 * Deletes a specified node.
 *
 * @attention Release the memory of the node to be deleted.
 * @param entry [IN]Pointer to the linked list node to be deleted. The value cannot be null.
 */
static inline void ListRemove(struct ListNode *entry)
{
    entry->prev->next = entry->next;
    entry->next->prev = entry->prev;
}

/*
 * @ingroup  TEEC_List
 * @brief Delete the head node of the linked list.
 *
 * @par Description
 * Deletes the head node of a specified linked list.
 *
 * @attention After return, the memory of the deleted node should be release.
 * @param list [IN]Pointer to the linked list header, the value cannot be empty.
 *
 * @retval #NULL The linked list is empty.
 * @retval not #NULL Linked list header node
 */
static inline struct ListNode *ListRemoveHead(struct ListNode *list)
{
    struct ListNode *entry = NULL;
    if (!LIST_EMPTY(list)) {
        entry = list->next;
        ListRemove(entry);
    }
    return entry;
}

/*
 * @ingroup  TEEC_List
 * @brief Delete the tail node of the linked list.
 *
 * @par Description
 * Delete the tail node of the linked list.
 *
 * @attention After return, the memory of the deleted node should be release.
 * @param list [IN]Pointer to the linked list header, the value cannot be empty.
 *
 * @retval NULL The linked list is empty.
 * @retval not #NULL Linked list header node
 */
static inline struct ListNode *ListRemoveTail(struct ListNode *list)
{
    struct ListNode *entry = NULL;
    if (!LIST_EMPTY(list)) {
        entry = list->prev;
        ListRemove(entry);
    }
    return entry;
}
#endif
