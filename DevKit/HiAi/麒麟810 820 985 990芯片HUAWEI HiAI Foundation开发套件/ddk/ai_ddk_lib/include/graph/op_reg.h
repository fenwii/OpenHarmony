/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: op_reg
 */

#ifndef HIAI_OP_REG_COM_H
#define HIAI_OP_REG_COM_H

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "types.h"
#include "tensor.h"
#include "operator.h"
#include "attr_value.h"

namespace ge {
using std::function;
using std::string;
using std::vector;
using TensorPtr = std::shared_ptr<Tensor>;

class OpDesc;

class OpReg {
public:
    OpReg &N()
    {
        return *this;
    }

    OpReg &ATTR()
    {
        return *this;
    }

    OpReg &REQUIRED_ATTR()
    {
        return *this;
    }

    OpReg &INPUT()
    {
        return *this;
    }

    OpReg &OPTIONAL_INPUT()
    {
        return *this;
    }

    OpReg &OUTPUT()
    {
        return *this;
    }

    OpReg &INFER_SHAPE_AND_TYPE()
    {
        return *this;
    }
};

template <typename T>
struct GetType {
    using type = T;

    void assign(type &left, const T &right)
    {
        left = right;
    }
};

template <>
struct GetType<TensorPtr> {
    using type = ConstTensorPtr;

    void assign(type &left, const TensorPtr &right)
    {
        left = right;
    }
};

template <>
struct GetType<ComputeGraphPtr> {
    using type = ConstComputeGraphPtr;

    void assign(type &left, const ComputeGraphPtr &right)
    {
        left = right;
    }
};

template <>
struct GetType<vector<TensorPtr>> {
    using type = vector<ConstTensorPtr>;

    void assign(type &left, const vector<TensorPtr> &right)
    {
        for (auto &item : right) {
            left.push_back(item);
        }
    }
};

template <>
struct GetType<vector<ComputeGraphPtr>> {
    using type = vector<ConstComputeGraphPtr>;

    void assign(type &left, const vector<ComputeGraphPtr> &right)
    {
        for (auto &item : right) {
            left.push_back(item);
        }
    }
};

template <typename T>
using GraphGetType = typename GetType<T>::type;
} // namespace ge
#endif // HIAI_OP_REG_COM_H