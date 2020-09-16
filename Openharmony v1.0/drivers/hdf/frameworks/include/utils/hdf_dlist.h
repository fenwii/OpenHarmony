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
/**
 * @addtogroup DriverUtils
 * @{
 *
 * @brief Defines common macros and interfaces of the driver module.
 *
 * This module provides interfaces such as log printing, doubly linked list operations, and work queues.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hdf_dlist.h
 *
 * @brief Declares doubly linked list structures and interfaces.
 *
 * This file provides interfaces such as inserting a node from the head or tail of a doubly linked list,
 * checking whether a doubly linked list is empty, traversing a doubly linked list, and merging doubly linked lists.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HDF_LIST_H
#define HDF_LIST_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Describes a doubly linked list.
 */
struct DListHead {
    struct DListHead *next; /**< Pointer to the next node */
    struct DListHead *prev; /**< Pointer to the previous node */
};

/**
 * @brief Initializes a doubly linked list.
 *
 * @param head Indicates the pointer to the linked list {@link DListHead}. The parameter cannot be empty.
 * @since 1.0
 * @version 1.0
 */
static inline void DListHeadInit(struct DListHead *head)
{
    head->next = head;
    head->prev = head;
}

/**
 * @brief Checks whether a doubly linked list is empty.
 *
 * @param head Indicates the pointer to the linked list {@link DListHead}. The parameter cannot be empty.
 * @since 1.0
 * @version 1.0
 */
static inline bool DListIsEmpty(const struct DListHead *head)
{
    return (head->next == head) ? true : false;
}
/**
 * @brief Removes a node from a doubly linked list.
 *
 * @param entry Indicates the pointer to the node to remove. For details, see {@link DListHead}.
 *        The parameter cannot be empty.
 * @since 1.0
 * @version 1.0
 */
static inline void DListRemove(struct DListHead *entry)
{
    entry->prev->next = entry->next;
    entry->next->prev = entry->prev;

    entry->prev = NULL;
    entry->next = NULL;
}

/**
 * @brief Inserts a node from the head of a doubly linked list.
 *
 * @param entry Indicates the pointer to the node to insert. For details, see {@link DListHead}.
 *        The parameter cannot be empty.
 * @param head Indicates the pointer to the linked list {@link DListHead}. The parameter cannot be empty.
 * @since 1.0
 * @version 1.0
 */
static inline void DListInsertHead(struct DListHead *entry, struct DListHead *head)
{
    entry->next = head->next;
    entry->prev = head;

    head->next->prev = entry;
    head->next = entry;
}

/**
 * @brief Inserts a node from the tail of a doubly linked list.
 *
 * @param entry Indicates the pointer to the node to insert. For details, see {@link DListHead}.
 *        The parameter cannot be empty.
 * @param head Indicates the pointer to the linked list {@link DListHead}. The parameter cannot be empty.
 * @since 1.0
 * @version 1.0
 */
static inline void DListInsertTail(struct DListHead *entry, struct DListHead *head)
{
    entry->next = head;
    entry->prev = head->prev;

    head->prev->next = entry;
    head->prev = entry;
}

/**
 * @brief Merges two linked lists by adding the list specified by <b>list</b> to
 *        the head of the list specified by <b>head</b> and initializes the merged list.
 *
 * @param list Indicates the pointer to the linked list {@link DListHead}. The parameter cannot be empty.
 * @param head Indicates the pointer to the linked list {@link DListHead}. The parameter cannot be empty.
 * @since 1.0
 * @version 1.0
 */
static inline void DListMerge(struct DListHead *list, struct DListHead *head)
{
    list->next->prev = head;
    list->prev->next = head->next;

    head->next->prev = list->prev;
    head->next = list->next;

    DListHeadInit(list);
}

/**
 * @brief Obtains the address of a structure variable from its member address.
 *
 * @param ptr Indicates the structure member address.
 * @param type Indicates the structure type.
 * @param member Indicates the structure member.
 * @since 1.0
 * @version 1.0
 */
#define CONTAINER_OF(ptr, type, member) \
    (type *)((char *)(ptr) - (char *)&((type *)0)->member)

/**
 * @brief Obtains the first node of a doubly linked list.
 *
 * @param ptr Indicates the structure member address.
 * @param type Indicates the structure type.
 * @param member Indicates the structure member.
 * @since 1.0
 * @version 1.0
 */
#define DLIST_FIRST_ENTRY(ptr, type, member) \
    CONTAINER_OF((ptr)->next, type, member)

/**
 * @brief Obtains the last node of a doubly linked list.
 *
 * @param ptr Indicates the structure member address.
 * @param type Indicates the structure type.
 * @param member Indicates the structure member.
 * @since 1.0
 * @version 1.0
 */
#define DLIST_LAST_ENTRY(ptr, type, member) \
    CONTAINER_OF((ptr)->prev, type, member)

/**
 * @brief Traverses all nodes in a doubly linked list.
 *
 * @param pos Indicates the pointer to the structure variable.
 * @param head Indicates the pointer to the linked list head.
 * @param type Indicates the structure type.
 * @param member Indicates the member type of the structure.
 * @since 1.0
 * @version 1.0
 */
#define DLIST_FOR_EACH_ENTRY(pos, head, type, member) \
    for ((pos) = CONTAINER_OF((head)->next, type, member); \
        &(pos)->member != (head); \
        (pos) = CONTAINER_OF((pos)->member.next, type, member))

/**
 * @brief Traverses all nodes in a doubly linked list.
 *        This function is used to delete the nodes pointed to by <b>pos</b> during traversal.
 *
 * @param pos Indicates the pointer to the structure variable.
 * @param tmp Indicates the pointer to the structure variable, pointing to the next node of <b>pos</b>.
 * @param head Indicates the pointer to the linked list head.
 * @param type Indicates the structure type.
 * @param member Indicates the member type of the structure.
 * @since 1.0
 * @version 1.0
 */
#define DLIST_FOR_EACH_ENTRY_SAFE(pos, tmp, head, type, member) \
    for ((pos) = CONTAINER_OF((head)->next, type, member), \
        (tmp) = CONTAINER_OF((pos)->member.next, type, member); \
        &(pos)->member != (head); \
        (pos) = (tmp), (tmp) = CONTAINER_OF((pos)->member.next, type, member))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HDF_LIST_H */
/** @} */
