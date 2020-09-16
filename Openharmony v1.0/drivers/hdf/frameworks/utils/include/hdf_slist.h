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

#ifndef HDF_SINGLE_LIST_H
#define HDF_SINGLE_LIST_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct HdfSListNode {
    struct HdfSListNode *next; // next element in list, or NULL
};

struct HdfSList {
    struct HdfSListNode *root;
};

struct HdfSListIterator {
    int stepOnNext;
    struct HdfSListNode *previous; // points to the item before the current one
    struct HdfSListNode *current; // points to the current item (to detect item removal)
};

typedef void (*HdfSListDeleter)(struct HdfSListNode *);

typedef bool (*HdfSListSearchCompare)(struct HdfSListNode *, uint32_t);

typedef bool (*HdfSListAddCompare)(struct HdfSListNode *, struct HdfSListNode *);

/*
 * @brief Init the list
 *
 * @param[in] list :the operation list.
 *
 * @return None
 */
void HdfSListInit(struct HdfSList *list);

/*
 * @brief search to see whether specific element is attach into the list.
 *
 * @param[in] list the operation list.
 * @param[in] searchKey -search key of list node.
 * @param[in] comparer -comparer of list node.
 *
 * @return struct HdfSListNode of search result
 *  -# NULL if not found.
 */
struct HdfSListNode *HdfSListSearch(struct HdfSList *list, uint32_t searchKey, HdfSListSearchCompare compare);

/*
 * @brief tests if list is empty
 *
 * @param[in] list the operation list.
 *
 * @return bool result of queue status.
 */
bool HdfSListIsEmpty(struct HdfSList *list);

/*
 * @brief find the last item in the list
 *
 * @param[in] list the operation list.
 *
 * @return last link of list.
 */
struct HdfSListNode *HdfSListGetLast(struct HdfSList *list);

/*
 * @brief add item to the head of the list
 *
 * @param[in] list :the operation list.
 * @param[in] p_node :the new element to add.
 *
 * @return None
 */
void HdfSListAdd(struct HdfSList *list, struct HdfSListNode *link);

/*
 * @brief add item to list as last element
 *
 * @param[in] list the operation list.
 * @param[in] p_node :the new element to add.
 *
 * @return None
 */
void HdfSListAddTail(struct HdfSList *list, struct HdfSListNode *link);

/*
 * @brief add item to list as ordered
 *
 * @param[in] list the operation list.
 * @param[in] p_node :the new element to add.
 * @param[in] comparer :compared.
 *
 * @return bool result of queue status.
 */
bool HdfSListAddOrder(struct HdfSList *list, struct HdfSListNode *link, HdfSListAddCompare compare);

/*
 * @brief remove item from list
 *
 * @param[in] list :the operation list.
 * @param[in] p_node :the element to remove.
 *
 * @return the result of remove node.
 *  -# HDF_SUCCESS link has been successfully removed.
 *  -# HDF_FAILURE link was not found in the list.
 */
void HdfSListRemove(struct HdfSList *list, struct HdfSListNode *link);

/*
 * @brief flush the list and free memory
 *
 * @param[in] list the operation list.
 * @param[in] deleter :the func of free memory.
 *
 * @return None
 */
void HdfSListFlush(struct HdfSList *list, HdfSListDeleter deleter);

/*
 * @brief calculate the element count in the list.
 *
 * @param[in] list :the list to count.
 *
 * @return the count of list.
 */
int HdfSListCount(struct HdfSList *list);

/*
 * @brief get first element
 *
 * @param[in] list the operation list.
 *
 * @return the first element in the list.
 */
struct HdfSListNode *HdfSListPeek(struct HdfSList *list);

/*
 * @brief get next element of p_link;
 *
 * @param[in] p_link: the operation link.
 *
 * @return the next element of the link pass in
 */
struct HdfSListNode *HdfSListNext(struct HdfSListNode *link);

/*
 * @brief get and remove first element
 *
 * @param[in] list the operation list.
 *
 * @return the first element in the list.
 */
struct HdfSListNode *HdfSListPop(struct HdfSList *list);

/*
 * @brief initialize iterator
 *
 * @param[in] iterator the point of iterator.
 * @param[in] list the point of operation list.
 *
 * @return None
 */
void HdfSListIteratorInit(struct HdfSListIterator *iterator, struct HdfSList *list);

/*
 * @brief check whether list has next node.
 *
 * @param[in] iterator the point of iterator.
 *
 * @return the result of check next.
 */
bool HdfSListIteratorHasNext(struct HdfSListIterator *iterator);

/*
 * @brief get next link in the list and move iterator to next.
 *
 * @param[in] iterator the point of iterator.
 *
 * @return point to next element of it.
 */
struct HdfSListNode *HdfSListIteratorNext(struct HdfSListIterator *iterator);

/*
 * @brief remove current node that iterator point to and move iterator to next node
 *
 * @param[in] iterator the point of iterator.
 *
 * @return None
 */
void HdfSListIteratorRemove(struct HdfSListIterator *iterator);

/*
 * @brief insert new node before the node that iterator point to.and hold current iterator.
 *
 * @param[in] list the operation list.
 *
 * @return None
 */
void HdfSListIteratorInsert(struct HdfSListIterator *iterator, struct HdfSListNode *link);

#define OFFSET_OF(type, mem)   ((size_t) &((type *)0)->mem)

#define HDF_SLIST_CONTAINER_OF(mtype, ptr, type, mem)  ({           \
        const mtype*__mptr = (ptr);                        \
        (type *)((char *)__mptr - OFFSET_OF(type, mem));  \
})

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HDF_SINGLE_LIST_H */
