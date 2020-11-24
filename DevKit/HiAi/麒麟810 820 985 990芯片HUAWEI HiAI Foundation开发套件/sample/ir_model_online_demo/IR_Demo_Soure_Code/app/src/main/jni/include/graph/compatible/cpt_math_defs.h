/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: math_defs
 */
#ifndef _CCE_GRAPH_OP_GE_OP_MATH_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_MATH_DEFS_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#ifdef _MSC_VER
// CPT_OUTPUT(z, xx), __out_z is defined in sal.h, should undef here
#undef __out_z
#endif

#include "./operator_reg.h"
#include "../op/math_defs.h"

namespace ge {
/*
 * Performs tensor addition.
 *   Inputs 'x1' and 'x2' must meet the following constraints:
 *       1. The input shape can be 1D-4D.
 *           1D: 1 is added to the front and 2 is added in the back. For example, 5 is padded into: 1,5,1,1
 *           2D: 1 is added to the front and back. For example, 5,5 is padded into: 1,5,5,1
 *           3D: 1 is added to the front. For example, 5,5,5 is padded into: 1,5,5,5
 *       2. For the two inputs, the corresponding dimensions must have the same value, or one of them is 1.
 * <Input>
 *    x1 : First operand
 *    x2 : Second operand
 * <Output>
 *    y  : Result of same element type as the two inputs
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(Add)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Performs tensor multiplication.
 * <Input>
 *    x : A Tensor
 *    y : A Tensor, Must have the same type and dimensions as x
 * <Output>
 *    z : Result of the same element type as the two inputs
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(Mul)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(y, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(z, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes exp(x) - 1 element-wise. y = exp(x) - 1
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Expm1)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes smallest integer not less than x.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Ceil)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes sin of 'x' element-wise.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Sin)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes cos of 'x' element-wise.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Cos)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes element-wise largest integer not greater than 'x'.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Floor)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes natural logarithm of (1 + x) element-wise.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Log1p)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Returns the logical and truth value of 'x1' and 'x2' element-wise.
 * <Input>
 *    x1 : First input operand
 *    x2 : Second input operand
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(LogicalAnd)
.CPT_INPUT(x1, TensorType({ DT_BOOL }))
.CPT_INPUT(x2, TensorType({ DT_BOOL }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL }))
.CPT_OP_END()

/*
 * Returns the truth value of NOT 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(LogicalNot)
.CPT_INPUT(x, TensorType({ DT_BOOL }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL }))
.CPT_OP_END()

/*
 * Computes the maximum of input tensors 'x1' and 'x2' element-wise.
 * The dimension of 'x1' and 'x2' must be the same unless 'x2' is a scalar.
 * <Input>
 *    x1 : Input tensor. Must be non const OP
 *    x2 : Input tensor. Must be non const OP
 * <Output>
 *    y : Maximum of 'x1' and 'x2'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Maximum)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Computes the minimum of input tensors 'x1' and 'x2' element-wise.
 * <Input>
 *    x1 : Input tensor
 *    x2 : Input tensor
 * <Output>
 *    y  : Minimum of 'x1' and 'x2'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Minimum)
.CPT_INPUT(x1, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_OP_END()

/*
 * Computes inverse hyperbolic cosine of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Acosh)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Computes inverse hyperbolic sine of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Asinh)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Calculates whether the input tensors 'x1' and 'x2' are equal, if equal, returns the truth value element-wise.
 * <Input>
 *    x1 : First input operand
 *    x2 : Second input operand
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Equal)
.CPT_INPUT(x1, TensorType({ DT_UINT8, DT_FLOAT, DT_BOOL, DT_INT32 }))
.CPT_INPUT(x2, TensorType({ DT_UINT8, DT_FLOAT, DT_BOOL, DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL }))
.CPT_OP_END()

/*
 * Computes the reciprocal of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Reciprocal)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Computes the square root of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Sqrt)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Computes the square of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Square)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Computes the 'logical and' of elements across dimensions of a tensor. Reduces 'input_tensor'
 * along the dimensions given in 'axis'.
 * <Input>
 *    x      : Boolean tensor
 * <Output>
 *    output : Reduced tensor
 * <Attr>
 *    axes: The dimensions to reduce. If None (the default), reduces all dimensions.
 *         Must be in the range [-rank(x), rank(x)).
 *    keep_dims : If false,the rank of the tensor is reduced by 1 for each entry in axis.
 *              If true, the reduced dimensions are retained with length 1.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(ReduceAll)
.CPT_INPUT(x, TensorType({ DT_BOOL }))
.CPT_OUTPUT(output, TensorType({ DT_BOOL }))
.CPT_ATTR(axes, AttrValue::LIST_INT({ 0 }))
.CPT_ATTR(keep_dims, AttrValue::BOOL { false })
.CPT_OP_END()

/*
 * Casts 'x' of input type 'SrcT' to 'y' of 'DstT'.
 * <Input>
 *    x : Input tensor to be cast. Must be non const OP.
 * <Output>
 *    y : Output tensor with the same shape as input
 * <Attr>
 *    SrcT : Data type of the input tensor
 *    DstT : Data type which will be cast to
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::CAST_ATTR_DSTT;
using hiai::CAST_ATTR_SRCT;

CPT_REG_OP(Cast)
.CPT_INPUT(x, TensorType({ DT_BOOL, DT_INT32, DT_UINT8, DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL, DT_INT32, DT_UINT8, DT_FLOAT }))
.CPT_REQUIRED_ATTR(SrcT, AttrValue::INT)
.CPT_REQUIRED_ATTR(DstT, AttrValue::INT)
.CPT_OP_END()

/*
 * Returns an indication of the sign of a number.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Sign)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_OP_END()

/*
 * Computes and returns hyperbolic cosine of 'x' element-wise
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Cosh)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Computes exponential of 'x' element-wise. y = e^x
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Exp)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_DOUBLE}))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_DOUBLE}))
.CPT_OP_END()
/*
 * Computes element-wise remainder of division, discarding decimal places in the negative infinity direction.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(FloorMod)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Returns the truth value of (x1 >= x2) element-wise.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(GreaterEqual)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL }))
.CPT_OP_END()
/*
 * Returns the truth value of (x1 < x2) element-wise.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Less)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL }))
.CPT_OP_END()
/*
 * Multiplies matrix 'x1' by matrix 'x2'.
 * The inputs must be two-dimensional matrices and the inner dimension of 'x1' (after being
 * transposed if 'transpose_x1' is true)
 * must match the outer dimension of 'x2' (after being transposed if 'transposed_x2' is true).
 * <Input>
 *    x1 : First input tensor. Must be non const OP
 *    x2 : Second input tensor. Must be const OP
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    transpose_x1: If true, 'x1' is transposed before multiplication.
 *    transpose_x2: If true, 'x2' is transposed before multiplication.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(MatMul)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(transpose_x1, AttrValue::BOOL { false })
.CPT_ATTR(transpose_x2, AttrValue::BOOL { false })
.CPT_OP_END()
/*
 * Returns x1/x2 element-wise for real types.
 * For the two inputs, the corresponding dimensions must have the same value, or one of them is 1.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(RealDiv)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Finds and returns the integer closest to 'x', and if the result is between two representable values,
 * select an even representation.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Rint)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Rounds the value of tensor to the nearest integer by element.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Round)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Calculates the reciprocal of the square root for input 'x'.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : the output tensor, has the same type as x
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Rsqrt)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Computes and returns hyperbolic sine of 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Sinh)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Returns x1 - x2.
 * For the two inputs, the corresponding dimensions must have the same value, or one of them is 1.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Sub)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * According to the input requirements, creates a sequence of numbers.
 * <Input>
 *    start : 0-D Tensor (scalar). Acts as first entry in the range
 *    limit : 0-D Tensor (scalar). Upper limit of sequence
 *    delta : 0-D Tensor (scalar). Number that increments 'start'.
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Range)
.CPT_INPUT(start, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_INPUT(limit, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_INPUT(delta, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_OP_END()

/*
 * Computes acos of input 'x'.
 * <Input>
 *    x : Input tensor, of range [-1, 1]
 * <Output>
 *    y : Output tensor of range [0, pi]. Has the same type as 'x'.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Acos)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Computes asin of input 'x'.
 * <Input>
 *    x : Input tensor, of range [-1, 1]
 * <Output>
 *    y : Output tensor of range [-pi/2, pi/2]. Has the same type as 'x'.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Asin)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Returns a new tensor with the inverse hyperbolic tangent of input 'x'.
 * <Input>
 *    x : Input tensor, of range [-1, 1]
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Atanh)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Computes natural logarithm of 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Log)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Computes natural logarithm of input 'x'.
 * <Input>
 *    x1 : Tensor of type bool
 *    x2 : Tensor of type bool
 * <Output>
 *    y : Tensor of type bool
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(LogicalOr)
.CPT_INPUT(x1, TensorType({ DT_BOOL }))
.CPT_INPUT(x2, TensorType({ DT_BOOL }))
.CPT_OUTPUT(y, TensorType({ DT_BOOL }))
.CPT_OP_END()
/*
 * Computes numerical negative value input.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Neg)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()
/*
 * Returns the product of elements across dimensions of the input tensor.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    keep_dims : If true, retains reduced dimensions with length 1.
 *    axes : Dimensions to reduce. If None (the default), reduces all dimensions.
 *         Must be in the range [-rank(x), rank(x)).
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(ReduceProd)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_ATTR(keep_dims, AttrValue::BOOL { false })
.CPT_REQUIRED_ATTR(axes, AttrValue::LIST_INT )
.CPT_OP_END()
/*
 * Returns the sum of elements across dimensions of the input tensor.
 * <Input>
 *    x : Tensor to reduce
 *    w : Dimensions to reduce
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    keep_dims : If true, retains reduced dimensions with length 1.
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::SUM_ATTR_KEEP_DIMS;

CPT_REG_OP(ReduceSum)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_INPUT(w, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_ATTR(keep_dims, AttrValue::BOOL { false })
.CPT_OP_END()

/*
 * Computes tan of input 'x'.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Tan)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * [ Deprecated ] Will be removed in a future version. Recommended Use ArgMaxExt2.
 * Determine the largest value of inputs. Returns the index with the largest value across axes of a tensor.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor, must be const op. Axis of the input tensor to reduce
 * <Output>
 *    y : Output tensor, max value index or max value
 * <Attr>
 *    axis: Deprecated, not recommended to use.
 *    output_type: Data type of output tensor
 *    keep_dims : If false,the rank of the tensor is reduced by 1 for each entry in axis.
 *              If true, the reduced dimensions are retained with length 1.
 *    outmaxval: If true, the max value is returned; if false, the max value index or value is returned.
 *            Only outMaxVal = false is supported.
 *    topk: (Optional) Only topk = 1 is supported.
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::ARGMAX_ATTR_NAME_AXIS;
using hiai::ARGMAX_ATTR_NAME_KEEPDIMS;
using hiai::ARGMAX_ATTR_NAME_OUTMAX;
using hiai::ARGMAX_ATTR_NAME_TOPK;

CPT_REG_OP(ArgMax)
.CPT_INPUT(x1, TensorType({ DT_FLOAT }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_INT32 }))
.CPT_ATTR(axis, AttrValue::INT { 0 })
.CPT_ATTR(output_type, AttrValue::INT { 3 })
.CPT_ATTR(keep_dims, AttrValue::BOOL{ false })
.CPT_ATTR(outmaxval, AttrValue::BOOL{ false })
.CPT_ATTR(topk, AttrValue::INT { 1 })
.CPT_OP_END()

/*
 * Divides x1/x2 element-wise, rounding toward the most negative integer.
 * <Input>
 *    x1 : First input tensor
 *    x2 : Second input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(FloorDiv)
.CPT_INPUT(x1, TensorType({ DT_FLOAT, DT_INT32}))
.CPT_INPUT(x2, TensorType({ DT_FLOAT, DT_INT32}))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32}))
.CPT_OP_END()
} // namespace ge
#pragma GCC diagnostic pop
#endif  // _CCE_GRAPH_OP_GE_OP_MATH_DEFS_H
