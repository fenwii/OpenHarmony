/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: operator_reg
 */

#ifndef HIAI_OP_REG_H
#define HIAI_OP_REG_H

#include "op_reg.h"

namespace hiai {
using namespace ge;

#define REG_OP(x) \
    namespace op { \
    class x : public Operator { \
        typedef x _THIS_TYPE; \
    \
    public: \
        explicit x(const string &name) : Operator(name, #x, 3) \
        { \
            __##x(); \
        } \
        explicit x() : Operator(#x) \
        { \
            __##x(); \
        } \
    \
    private: \
        void __##x() \
        { \
            OpReg()

#define ATTR(x, default_value) \
    N(); \
    __attr_##x(); \
    } \
    \
public: \
    static const string name_attr_##x() \
    { \
        return #x; \
    } \
    GraphGetType<decltype(default_value)> get_attr_##x() const \
    { \
        GraphGetType<decltype(default_value)> ret; \
        GetType<decltype(default_value)>().assign(ret, default_value); \
        AttrValue attr; \
        if (Operator::GetAttr(#x, attr) == GRAPH_FAILED) { \
            return ret; \
        } \
        attr.GetValue<decltype(default_value)>(ret); \
        return ret; \
    } \
    _THIS_TYPE &set_attr_##x(decltype(default_value) v) \
    { \
        auto attr = AttrValue::CreateFrom<decltype(default_value)>(v); \
        Operator::SetAttr(#x, std::move(attr)); \
        return *this; \
    } \
    _THIS_TYPE &set_attr_##x(function<decltype(default_value)()> v) \
    { \
        return *this; \
    } \
    \
private: \
    void __attr_##x() \
    { \
        auto defaultAttr = AttrValue::CreateFrom<decltype(default_value)>(default_value); \
        Operator::AttrRegister(#x, std::move(defaultAttr)); \
        string attr_name(#x); \
        OpReg()

#define REQUIRED_ATTR(x, type) \
    N(); \
    __required_attr_##x(); \
    } \
    \
public: \
    static const string name_attr_##x() \
    { \
        return #x; \
    } \
    GraphGetType<type> get_attr_##x() const \
    { \
        GraphGetType<type> ret; \
        AttrValue attr; \
        if (Operator::GetAttr(#x, attr) == GRAPH_FAILED) { \
            return ret; \
        } \
        attr.GetValue<type>(ret); \
        return ret; \
    } \
    _THIS_TYPE &set_attr_##x(type v) \
    { \
        auto attr = AttrValue::CreateFrom<type>(v); \
        Operator::SetAttr(#x, std::move(attr)); \
        return *this; \
    } \
    _THIS_TYPE &set_attr_##x(function<type()> v) \
    { \
        return *this; \
    } \
    \
private: \
    void __required_attr_##x() \
    { \
        Operator::RequiredAttrRegister(#x); \
        string attr_name(#x); \
        OpReg()

#define INPUT(x, t) \
    N(); \
    __input_##x(); \
    } \
    \
public: \
    static const string name_in_##x() \
    { \
        return #x; \
    } \
    _THIS_TYPE &set_input_##x(const Operator &v, const string &srcName) \
    { \
        Operator::SetInput(#x, v, srcName); \
        return *this; \
    } \
    _THIS_TYPE &set_input_##x(const Operator &v) \
    { \
        Operator::SetInput(#x, v); \
        return *this; \
    } \
    _THIS_TYPE &set_input_##x(OutHandler v) \
    { \
        Operator::SetInput(#x, v); \
        return *this; \
    } \
    TensorDesc get_input_desc_##x() const \
    { \
        return Operator::GetInputDesc(#x); \
    } \
    GraphErrCodeStatus update_input_desc_##x(const TensorDesc &tensorDesc) \
    { \
        return Operator::UpdateInputDesc(#x, tensorDesc); \
    } \
    \
private: \
    void __input_##x() \
    { \
        Operator::InputRegister(#x); \
        OpReg()

#define OPTIONAL_INPUT(x, t) \
    N(); \
    __optional_input_##x(); \
    } \
    \
public: \
    static const string name_in_##x() \
    { \
        return #x; \
    } \
    _THIS_TYPE &set_input_##x(const Operator &v) \
    { \
        Operator::SetInput(#x, v); \
        return *this; \
    } \
    _THIS_TYPE &set_input_##x(const Operator &v, const string &srcName) \
    { \
        Operator::SetInput(#x, v, srcName); \
        return *this; \
    } \
    TensorDesc get_input_desc_##x() const\
    { \
        return Operator::GetInputDesc(#x); \
    } \
    GraphErrCodeStatus update_input_desc_##x(const TensorDesc &tensorDesc) \
    { \
        return Operator::UpdateInputDesc(#x, tensorDesc); \
    } \
    \
private: \
    void __optional_input_##x() \
    { \
        Operator::OptionalInputRegister(#x); \
        OpReg()

#define OUTPUT(x, t) \
    N(); \
    __out_##x(); \
    } \
    \
public: \
    static const string name_out_##x() \
    { \
        return #x; \
    } \
    TensorDesc get_output_desc_##x() const\
    { \
        return Operator::GetOutputDesc(#x); \
    } \
    GraphErrCodeStatus update_output_desc_##x(const TensorDesc &tensorDesc) \
    { \
        return Operator::UpdateOutputDesc(#x, tensorDesc); \
    } \
    \
private: \
    void __out_##x() \
    { \
        Operator::OutputRegister(#x); \
        OpReg()

#define OPTIONAL_OUTPUT(x, t) \
    N(); \
    __out_##x(); \
    } \
    \
public: \
    static const string name_out_##x() \
    { \
        return #x; \
    } \
    TensorDesc get_output_desc_##x() const\
    { \
        return Operator::GetOutputDesc(#x); \
    } \
    GraphErrCodeStatus update_output_desc_##x(const TensorDesc &tensorDesc) \
    { \
        return Operator::UpdateOutputDesc(#x, tensorDesc); \
    } \
    \
private: \
    void __out_##x() \
    { \
        OpReg()

#define DYNAMIC_INPUT(x, t) \
    N(); \
    __dy_input_##x(); \
    } \
    \
public: \
    _THIS_TYPE &create_dynamic_input_##x(unsigned int num) \
    { \
        Operator::DynamicInputRegister(#x, num); \
        return *this; \
    } \
    TensorDesc get_dynamic_input_desc_##x(unsigned int index) const\
    { \
        return Operator::GetDynamicInputDesc(#x, index); \
    } \
    GraphErrCodeStatus update_dynamic_input_desc_##x(unsigned int index, const TensorDesc &tensorDesc) \
    { \
        return Operator::UpdateDynamicInputDesc(#x, index, tensorDesc); \
    } \
    _THIS_TYPE &set_dynamic_input_##x(unsigned int dstIndex, const Operator &v) \
    { \
        Operator::SetInput(#x, dstIndex, v); \
        return *this; \
    } \
    _THIS_TYPE &set_dynamic_input_##x(unsigned int dstIndex, const Operator &v, const string &srcName) \
    { \
        Operator::SetInput(#x, dstIndex, v, srcName); \
        return *this; \
    } \
    \
private: \
    void __dy_input_##x() \
    { \
        OpReg()

#define DYNAMIC_OUTPUT(x, t) \
    N(); \
    __dy_output_##x(); \
    } \
    \
public: \
    _THIS_TYPE &create_dynamic_output_##x(unsigned int num) \
    { \
        Operator::DynamicOutputRegister(#x, num); \
        return *this; \
    } \
    TensorDesc get_dynamic_output_desc_##x(unsigned int index) const\
    { \
        return Operator::GetDynamicOutputDesc(#x, index); \
    } \
    GraphErrCodeStatus update_dynamic_output_desc_##x(unsigned int index, const TensorDesc &tensorDesc) \
    { \
        return Operator::UpdateDynamicOutputDesc(#x, index, tensorDesc); \
    } \
    OutHandler get_output(unsigned int dstIndex) const\
    { \
        return Operator::GetOutput(dstIndex); \
    } \
 \
private: \
    void __dy_output_##x() \
    { \
        OpReg()

#define OP_END() \
    N(); \
    } \
    } \
    ; \
    }

/* specialized shape inferencer macro */
#define DECLARE_INFERFUNC(op_name, func_name) \
    namespace op { \
    class op_name; \
    } \
    static GraphErrCodeStatus func_name(op::op_name &op);

#define IMPLEMT_INFERFUNC(op_name, func_name) static GraphErrCodeStatus func_name(op::op_name &op)

/* specialized verifier macro */
#define DECLARE_VERIFIER(op_name, func_name) \
    namespace op { \
    class op_name; \
    } \
    static GraphErrCodeStatus func_name(op::op_name op);

#define IMPLEMT_VERIFIER(op_name, func_name) static GraphErrCodeStatus func_name(op::op_name op)

/* utilty macros */
#define GET_INPUT_SHAPE(op, name) op.GetInputDesc(name).GetShape().GetDims()

#define GET_DYNAMIC_INPUT_SHAPE(op, name, index) op.GetDynamicInputDesc(name, index).GetShape().GetDims()

#define SET_OUTPUT_SHAPE(op, name, shape) do { \
    TensorDesc td = op.GetOutputDesc(name); \
    td.SetShape(Shape(shape)); \
    op.UpdateOutputDesc(name, td); \
} while (0)

#define SET_DYNAMIC_OUTPUT_SHAPE(op, name, index, shape) do { \
    TensorDesc td = op.GetDynamicOutputDesc(name, index); \
    td.SetShape(Shape(shape)); \
    op.UpdateDynamicOutputDesc(name, index, td); \
} while (0)

#define GET_ATTR(op, name, type, val) do { \
    AttrValue attr; \
    op.GetAttr(name, attr); \
    attr.GetValue<type>(val); \
} while (0)
} // namespace hiai
#endif // HIAI_OP_REG_H