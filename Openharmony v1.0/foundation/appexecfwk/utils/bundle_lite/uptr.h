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

#ifndef OHOS_UPTR_H
#define OHOS_UPTR_H

namespace OHOS {
template<typename T>
struct RemoveRef {
    typedef T type;
};

template<class T>
struct RemoveRef<T &> {
    typedef T type;
};

template<class T>
struct RemoveRef<T &&> {
    typedef T type;
};

template<typename T>
typename RemoveRef<T>::type &&Move(T &&t)
{
    using Rtype = typename RemoveRef<T>::type &&;
    return static_cast<Rtype>(t);
}

template<typename T>
class Uptr {
public:
    explicit Uptr(T *p = nullptr) : ptr_(p)
    {
    }

    ~Uptr()
    {
        delete ptr_;
    }

    Uptr(Uptr &&ptr) : ptr_(ptr.ptr_)
    {
        ptr.ptr_ = nullptr;
    }

    void reset(T *p = nullptr)
    {
        if (p != ptr_) {
            delete ptr_;
            ptr_ = p;
        }
    }

    T &operator*() const
    {
        return *ptr_;
    }

    T *operator->() const
    {
        return ptr_;
    }

    T *get() const
    {
        return ptr_;
    }

    bool operator==(T *p) const
    {
        return ptr_ == p;
    }

    bool operator!=(T *p) const
    {
        return ptr_ != p;
    }

    void swap(Uptr &p2)
    {
        T* tmp = ptr_;
        ptr_ = p2.ptr_;
        p2.ptr_ = tmp;
    }

    T *release()
    {
        T *retVal = ptr_;
        ptr_ = nullptr;
        return retVal;
    }

private:
    T *ptr_ = nullptr;

    template<class T2> bool operator==(Uptr<T2> const &p2) const;
    template<class T2> bool operator!=(Uptr<T2> const &p2) const;

    Uptr(const Uptr &);
    void operator=(const Uptr&);
};
}  // namespace OHOS
#endif  // OHOS_UPTR_H