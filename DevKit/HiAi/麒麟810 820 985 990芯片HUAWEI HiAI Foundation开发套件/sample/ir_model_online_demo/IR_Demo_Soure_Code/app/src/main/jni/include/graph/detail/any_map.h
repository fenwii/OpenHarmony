/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Apache License Version 2.0.You may not use this file except in compliance with the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Apache License for more details at
 * http: // www.apache.org/licenses/LICENSE-2.0
 *
 * @file any_map.h
 *
 * @brief
 *
 * @version 1.0
 *
 */
#ifndef GE_ANY_MAP_H
#define GE_ANY_MAP_H

#include <string>
#include <map>
#include <memory>
#include <utility>

namespace ge {
using std::shared_ptr;
using std::string;

class TypeID {
public:
    template <class T>
    static TypeID Of()
    {
        return TypeID(__PRETTY_FUNCTION__);
    }

public:
    bool operator == (const TypeID &__arg) const
    {
        return type_ == __arg.type_;
    }

private:
    explicit TypeID(string type) : type_(std::move(type))
    {} //lint !e30 !e32

private:
    string type_;
};

class AnyMap {
public:
    template <class DT>
    bool Set(const string &name, const DT &val);

    template <class T>
    bool Get(const string &name, T &retValue) const;

    bool Has(const string &name) const
    {
        return anyValues_.find(name) != anyValues_.end();
    }

private:
    class Placeholder {
    public:
        virtual ~Placeholder() = default;

        virtual const TypeID &GetTypeInfo() const = 0;
    };

    template <typename VT>
    class Holder : public Placeholder {
    public:
        explicit Holder(const VT &value) : value_(value) {}

        const TypeID &GetTypeInfo() const override
        {
            return TypeID::Of<VT>();
        }

        const VT value_;
    };

private:
    std::map<string, shared_ptr<Placeholder>> anyValues_;
};

template <class DT>
bool AnyMap::Set(const string &name, const DT &val)
{
    auto it = anyValues_.find(name);
    if (it == anyValues_.end()) {
        std::shared_ptr<Holder<DT>> tmp = nullptr;
        try {
            tmp = std::make_shared<Holder<DT>>(val);
        } catch (...) {
            tmp = nullptr;
        }
        anyValues_.emplace(name, tmp);
    } else {
        if (it->second && it->second->GetTypeInfo() == TypeID::Of<DT>()) {
            *it->second = Holder<DT>(val);
        } else {
            return false;
        }
    }
    return true;
}

template <class T>
bool AnyMap::Get(const string &name, T &retValue) const
{
    auto it = anyValues_.find(name);
    if (it != anyValues_.end() && it->second && it->second->GetTypeInfo() == TypeID::Of<T>()) {
        auto retPtr = std::static_pointer_cast<Holder<T>>(it->second);
        retValue = retPtr->value_;
        return true;
    }
    return false;
}
} // namespace ge

#endif // GE_ANY_MAP_H
