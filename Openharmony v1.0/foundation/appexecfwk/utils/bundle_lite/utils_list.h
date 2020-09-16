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

#ifndef OHOS_UTILS_LIST_H
#define OHOS_UTILS_LIST_H

namespace OHOS {
template<class T>
struct Node {
    Node() = default;
    explicit Node(T value) : value_(value), next_(nullptr), prev_(nullptr) {}

    T value_;
    Node<T> *next_;
    Node<T> *prev_;
};

template<class T>
class List {
public:
    List() : count_(0)
    {
        head_ = new Node<T>();
        head_->next_ = head_;
        head_->prev_ = head_;
    }

    ~List()
    {
        RemoveAll();
        delete head_;
        head_ = nullptr;
    }

    const T Front() const
    {
        if (count_ == 0) {
            return head_->value_;
        }

        return head_->next_->value_;
    }

    void PushFront(T value)
    {
        auto node = new Node<T>(value);
        if (node == nullptr) {
            return;
        }

        node->prev_ = head_;
        node->next_ = head_->next_;
        head_->next_->prev_ = node;
        head_->next_ = node;
        count_++;
    }

    void PopFront()
    {
        if (count_ == 0) {
            return;
        }

        Node<T> *node = head_->next_;
        node->next_->prev_ = head_;
        head_->next_ = node->next_;
        delete node;
        count_--;
    }

    const T Back() const
    {
        if (count_ == 0) {
            return head_->value_;
        }

        return head_->prev_->value_;
    }

    void PushBack(T value)
    {
        auto node = new Node<T>(value);

        node->next_ = head_;
        node->prev_ = head_->prev_;
        head_->prev_->next_ = node;
        head_->prev_ = node;
        count_++;
    }

    void PopBack()
    {
        if (count_ == 0) {
            return;
        }

        Node<T> *node = head_->prev_;
        node->prev_->next_ = head_;
        head_->prev_ = node->prev_;
        delete node;
        count_--;
    }

    void Remove(Node<T> *node)
    {
        if ((count_ == 0) || (node == nullptr)) {
            return;
        }

        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;

        delete node;
        count_--;
    }

    void RemoveAll()
    {
        Node<T> *node = head_->next_;
        while (node != head_) {
            Node<T> *temp = node;
            node = node->next_;
            delete temp;
        }
    }

    Node<T> *Begin() const
    {
        return head_->next_;
    }

    const Node<T> *End() const
    {
        return head_;
    }

    uint32_t Size()
    {
        return count_;
    }

    bool IsEmpty()
    {
        return count_ == 0;
    }

private:
    Node<T> *head_;
    int count_;
};
} // namespace OHOS
#endif  // OHOS_UTILS_LIST_H
