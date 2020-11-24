/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: operator
 */

#ifndef GE_OPERATOR_H
#define GE_OPERATOR_H

#include <map>
#include <memory>
#include <vector>
#include <functional>
#include "tensor.h"
#include "debug/ge_error_codes.h"

namespace ge {
class OperatorImpl;

using OperatorImplPtr = std::shared_ptr<OperatorImpl>;

class OpIO;

using OutHandler = std::shared_ptr<OpIO>;
using InHandler = std::shared_ptr<OpIO>;

class AttrValue;

using std::function;
using std::shared_ptr;
using std::string;

class ComputeGraph;

class OpDesc;

using ComputeGraphPtr = std::shared_ptr<ComputeGraph>;
using OpDescPtr = std::shared_ptr<OpDesc>;

class GE_FUNC_HOST_VISIBILITY GE_FUNC_DEV_VISIBILITY Operator {
public:
    friend class OperatorImpl;

    friend class GraphBuilderImpl;

public:
    Operator() {};

    explicit Operator(const string &type);

    explicit Operator(const string &name, const string &type);

    explicit Operator(const string &name, const string &type, int version);

    virtual ~Operator() = default;

    string GetName() const;

    Operator &SetInput(const string &dstName, const Operator &srcOprt); // only has one output index = 0

    Operator &SetInput(const string &dstName, const Operator &srcOprt, const string &name);

    Operator &SetInput(int dstIndex, const Operator &srcOprt, int srcIndex);

    TensorDesc GetInputDesc(const string &name) const;

    TensorDesc GetInputDesc(uint32_t index) const;

    bool TryGetInputDesc(const string &name, TensorDesc &tensorDesc) const;

    GraphErrCodeStatus UpdateInputDesc(const string &name, const TensorDesc &tensorDesc);

    TensorDesc GetOutputDesc(const string &name) const;

    TensorDesc GetOutputDesc(uint32_t index) const;

    GraphErrCodeStatus UpdateOutputDesc(const string &name, const TensorDesc &tensorDesc);

    TensorDesc GetDynamicInputDesc(const string &name, const unsigned int index) const;

    GraphErrCodeStatus UpdateDynamicInputDesc(const string &name, const unsigned int index,
        const TensorDesc &tensorDesc);

    TensorDesc GetDynamicOutputDesc(const string &name, const unsigned int index) const;

    GraphErrCodeStatus UpdateDynamicOutputDesc(const string &name, const unsigned int index,
        const TensorDesc &tensorDesc);

    Operator &SetAttr(const string &name, AttrValue &&attrValue);

    GraphErrCodeStatus GetAttr(const string &name, AttrValue &attrValue) const;

protected:
    explicit Operator(OperatorImplPtr &&opImpl);

    void InputRegister(const string &name);

    void OptionalInputRegister(const string &name);

    void OutputRegister(const string &name);

    void DynamicInputRegister(const string &name, const unsigned int num);

    void DynamicOutputRegister(const string &name, const unsigned int num);

    void AttrRegister(const string &name, AttrValue &&attrValue);

    void RequiredAttrRegister(const string &name);

    Operator &SetInput(const string &dstName, uint32_t dstIndex,
        const Operator &srcOprt); // only has one output index = 0
    Operator &SetInput(const string &dstName, uint32_t dstIndex, const Operator &srcOprt,
        const string &name);

    Operator &SetInput(const string &dstName, OutHandler outHandler);
    OutHandler GetOutput(const uint32_t srcIndex) const;

private:
    OutHandler GetOutput(const string &name) const;

    OperatorImplPtr GetOperatorImplPtr() const;

    string GetOpType() const;

    std::vector<bool> GetOpIsInputConst() const;

    void SetOpIsInputConst(bool inputConst, uint32_t index);

private:
    OperatorImplPtr operatorImpl_{ nullptr };
};

} // namespace ge

#endif // GE_OPERATOR_H
