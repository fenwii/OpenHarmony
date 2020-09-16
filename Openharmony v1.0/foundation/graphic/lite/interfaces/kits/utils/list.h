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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file list.h
 *
 * @brief Defines a linked list template class, which implements the data structure of bidirectional linked list and
 *        provides basic functions such as adding, deleting, inserting, clearing, popping up, and obtaining the size of
 *        the linked list.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_LIST_H
#define GRAPHIC_LITE_LIST_H
#include "heap_base.h"
#include <cstdint>

namespace OHOS {
/**
 * @brief Stores linked list data and contains pointers to the previous node and the next node.
 *
 * @param T Indicates the type of the data stored in the linked list.
 * @since 1.0
 * @version 1.0
 */
template<typename T>
class ListNode : public HeapBase {
public:
    ListNode<T>* prev_;
    ListNode<T>* next_;
    T data_;
};

/**
 * @brief Defines a linked list template class, which implements the data structure of bidirectional linked list and
 *        provides basic functions such as adding, deleting, inserting, clearing, popping up, and obtaining the size of
 *        the linked list.
 *
 * @param T Indicates the type of the data stored in the linked list.
 * @since 1.0
 * @version 1.0
 */
template<typename T>
class List : public HeapBase {
public:
    /**
     * @brief A default constructor used to create a <b>List</b> instance. The initial size is <b>0</b>.
     *
     * @since 1.0
     * @version 1.0
     */
    List() : size_(0)
    {
        head_.next_ = &head_;
        head_.prev_ = &head_;
    }

    /**
     * @brief A destructor used to delete the <b>List</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~List() {}

    /**
     * @brief Obtains the head node data of a linked list.
     *
     * @return Returns the head node data.
     * @since 1.0
     * @version 1.0
     */
    const T Front() const
    {
        return head_.next_->data_;
    }

    /**
     * @brief Obtains the tail node data of a linked list.
     *
     * @return Returns the tail node data.
     * @since 1.0
     * @version 1.0
     */
    const T Back() const
    {
        return head_.prev_->data_;
    }

    /**
     * @brief Inserts data at the end of a linked list.
     *
     * @param data Indicates the data to insert.
     * @since 1.0
     * @version 1.0
     */
    void PushBack(T data)
    {
        ListNode<T>* listNode = new ListNode<T>();
        listNode->data_ = data;

        listNode->prev_ = head_.prev_;
        listNode->next_ = &head_;
        head_.prev_->next_ = listNode;
        head_.prev_ = listNode;

        size_++;
    }

    /**
     * @brief Inserts data at the start of a linked list.
     *
     * @param data Indicates the data to insert.
     * @since 1.0
     * @version 1.0
     */
    void PushFront(T data)
    {
        ListNode<T>* listNode = new ListNode<T>();
        listNode->data_ = data;

        listNode->next_ = head_.next_;
        listNode->prev_ = &head_;
        head_.next_->prev_ = listNode;
        head_.next_ = listNode;

        size_++;
    }

    /**
     * @brief Pops up a data record at the end of a linked list.
     *
     * @since 1.0
     * @version 1.0
     */
    void PopBack()
    {
        if (IsEmpty()) {
            return;
        }
        ListNode<T>* tmpTail = head_.prev_;

        tmpTail->prev_->next_ = &head_;
        head_.prev_ = tmpTail->prev_;

        delete tmpTail;

        if (size_ > 0) {
            size_--;
        }
    }

    /**
     * @brief Pops up a data record at the start of a linked list.
     *
     * @since 1.0
     * @version 1.0
     */
    void PopFront()
    {
        if (IsEmpty()) {
            return;
        }
        ListNode<T>* tmpHead = head_.next_;

        head_.next_ = tmpHead->next_;
        tmpHead->next_->prev_ = &head_;

        delete tmpHead;

        if (size_ > 0) {
            size_--;
        }
    }

    /**
     * @brief Inserts data before a specified node, which follows the inserted data node.
     * @param node Indicates the pointer to the node holding the inserted data.
     * @param data Indicates the data to insert.
     * @since 1.0
     * @version 1.0
     */
    void Insert(ListNode<T>* node, T data)
    {
        if (node == nullptr) {
            return;
        }
        ListNode<T>* listNode = new ListNode<T>();
        listNode->data_ = data;

        listNode->next_ = node;
        listNode->prev_ = node->prev_;
        node->prev_->next_ = listNode;
        node->prev_ = listNode;

        size_++;
    }

    /**
     * @brief Deletes a data node.
     *
     * @param node Indicates the pointer to the node to delete.
     * @since 1.0
     * @version 1.0
     */
    void Remove(ListNode<T>* node)
    {
        if (IsEmpty()) {
            return;
        }
        if (node == nullptr) {
            return;
        }

        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;

        delete node;

        if (size_ > 0) {
            size_--;
        }
    }

    /**
     * @brief Deletes all nodes from a linked list.
     *
     * @since 1.0
     * @version 1.0
     */
    void Clear()
    {
        if (IsEmpty()) {
            return;
        }

        ListNode<T>* node = head_.next_;
        ListNode<T>* tmpNode = node->next_;
        do {
            delete node;
            node = tmpNode;
            tmpNode = tmpNode->next_;
        } while (node != &head_);

        head_.next_ = &head_;
        head_.prev_ = &head_;

        size_ = 0;
    }

    /**
     * @brief Obtains the head node address of a linked list.
     *
     * @return Returns the head node address.
     * @since 1.0
     * @version 1.0
     */
    ListNode<T>* Head() const
    {
        return head_.next_;
    }

    /**
     * @brief Obtains the tail node address of a linked list.
     *
     * @return Returns the tail node address.
     * @since 1.0
     * @version 1.0
     */
    ListNode<T>* Tail() const
    {
        return head_.prev_;
    }

    /**
     * @brief Obtains the head node address of a linked list.
     *
     * @return Returns the head node address.
     * @since 1.0
     * @version 1.0
     */
    ListNode<T>* Begin() const
    {
        return head_.next_;
    }

    /**
     * @brief Obtains the end node address of a linked list.
     *
     * @return Returns the end node address.
     * @since 1.0
     * @version 1.0
     */
    const ListNode<T>* End() const
    {
        return &head_;
    }

    /**
     * @brief Obtains the address of the node following the specified <b>node</b>.
     *
     * @param node Indicates the pointer to the data node in the linked list.
     * @return Returns the address of the node following <b>node</b>.
     * @since 1.0
     * @version 1.0
     */
    ListNode<T>* Next(const ListNode<T>* node) const
    {
        return node->next_;
    }

    /**
     * @brief Checks whether a linked list is empty.
     *
     * @return Returns <b>true</b> if the linked list is empty; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsEmpty() const
    {
        return (head_.next_ == &head_);
    }

    /**
     * @brief Obtains the size of a linked list.
     *
     * @return Returns the size of the linked list.
     * @since 1.0
     * @version 1.0
     */
    uint16_t Size() const
    {
        return size_;
    }

protected:
    ListNode<T> head_;
    uint16_t size_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_LIST_H
