/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: math_defs
 */
#ifndef _FMK_GRAPH_OP_GE_OP_MATH_DEFS_H
#define _FMK_GRAPH_OP_GE_OP_MATH_DEFS_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#ifdef _MSC_VER
// OUTPUT(z, xx), __out_z is defined in sal.h, should undef here
#undef __out_z
#endif

#include "../operator_hiai_reg.h"

namespace hiai {
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
REG_OP(Add)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Performs tensor multiplication.
 * <Input>
 *    x1 : A Tensor
 *    x2 : A Tensor, Must have the same type and dimensions as x
 * <Output>
 *    y : Result of the same element type as the two inputs
 * <Added in HiAI version>
 *    100.300.010.011
 */
REG_OP(Mul)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes exp(x) - 1 element-wise. y = exp(x) - 1
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Expm1)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

/*
 * Computes smallest integer not less than x.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Ceil)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

/*
 * Computes sin of 'x' element-wise.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Sin)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

/*
 * Computes cos of 'x' element-wise.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Cos)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

/*
 * Computes element-wise largest integer not greater than 'x'.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Floor)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

/*
 * Computes natural logarithm of (1 + x) element-wise.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : A Tensor. Has the same type as x.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Log1p)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

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
REG_OP(LogicalAnd)
.INPUT(x1, TensorType({ DT_BOOL }))
.INPUT(x2, TensorType({ DT_BOOL }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

/*
 * Returns the truth value of NOT 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(LogicalNot)
.INPUT(x, TensorType({ DT_BOOL }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

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
REG_OP(Maximum)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

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
REG_OP(Minimum)
.INPUT(x1, TensorType({ DT_FLOAT, DT_INT32 }))
.INPUT(x2, TensorType({ DT_FLOAT, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.OP_END()

/*
 * Computes inverse hyperbolic cosine of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Acosh)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes inverse hyperbolic sine of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Asinh)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

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
REG_OP(Equal)
.INPUT(x1, TensorType({ DT_UINT8, DT_FLOAT, DT_BOOL, DT_INT32 }))
.INPUT(x2, TensorType({ DT_UINT8, DT_FLOAT, DT_BOOL, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

/*
 * Computes the reciprocal of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Reciprocal)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the square root of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Sqrt)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the square of the input tensor 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Square)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

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
 *                If true, the reduced dimensions are retained with length 1.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(ReduceAllD)
.INPUT(x, TensorType({ DT_BOOL }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.REQUIRED_ATTR(axes, AttrValue::LIST_INT)
.ATTR(keep_dims, AttrValue::BOOL { false })
.OP_END()

/*
 * Casts 'x' of input type 'src_dtype' to 'y' of 'dst_dtype'.
 * <Input>
 *    x : Input tensor to be cast. Must be non const OP.
 * <Output>
 *    y : Output tensor with the same shape as input
 * <Attr>
 *    src_dtype : Data type of the input tensor, same as x
 *    dst_dtype : Data type which will be cast to, same as y
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const CAST_ATTR_DSTT = "dst_dtype";
const char* const CAST_ATTR_SRCT = "src_dtype";

REG_OP(CastT)
.INPUT(x, TensorType({ DT_BOOL, DT_INT32, DT_UINT8, DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_BOOL, DT_INT32, DT_UINT8, DT_FLOAT }))
.REQUIRED_ATTR(src_dtype, AttrValue::INT)
.REQUIRED_ATTR(dst_dtype, AttrValue::INT)
.OP_END()

/*
 * Returns an indication of the sign of a number.
 * <Input>
 *    x : A Tensor
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Sign)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({DT_FLOAT}))
.OP_END()

/*
 * Computes and returns hyperbolic cosine of 'x' element-wise
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Cosh)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes exponential of 'x' element-wise. y = base^(scale*x+shift)
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    base : Default -1 for a value of e, only support default value.
 *    scale : The scale, only support default value.
 *    shift : The shift, only support default value.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Exp)
.INPUT(x, TensorType({ DT_FLOAT, DT_DOUBLE }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_DOUBLE }))
.ATTR(base, AttrValue::FLOAT { -1.0 })
.ATTR(scale, AttrValue::FLOAT { 1.0 })
.ATTR(shift, AttrValue::FLOAT { 0.0 })
.OP_END()

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
REG_OP(FloorMod)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
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
REG_OP(GreaterEqual)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

/*
 * Returns the truth value of (x1 > x2) element-wise..
 * <Input>
 *      x1 : The input tensor.
 *      x2 : The input tensor.
 * <Output>
 *      y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.022
 */
REG_OP(Greater)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

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
REG_OP(Less)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()
/*
 * Multiplies matrix 'x1' by matrix 'x2'.
 * The inputs must be two-dimensional matrices and the inner dimension of 'x1' (after being
 * transposed if 'transpose_x1' is true)
 * must match the outer dimension of 'x2' (after being transposed if 'transposed_x2' is true).
 * <Input>
 *    x1 : First input tensor. Must be non const OP
 *    x2 : Second input tensor. Must be const OP
 *    bias : Reserved - Optional input tensor, bias data
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    transpose_x1: If true, 'x1' is transposed before multiplication.
 *    transpose_x2: If true, 'x2' is transposed before multiplication.
 * <Added in HiAI version>
 *    100.310.010.013
 */

const char* const MATMUL_ATTR_TRANSPOSE_X1 = "transpose_x1";
const char* const MATMUL_ATTR_TRANSPOSE_X2 = "transpose_x2";

REG_OP(MatMul)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OPTIONAL_INPUT(bias, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(transpose_x1, AttrValue::BOOL { false })
.ATTR(transpose_x2, AttrValue::BOOL { false })
.OP_END()
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
REG_OP(RealDiv)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
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
REG_OP(Rint)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Rounds the value of tensor to the nearest integer by element.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Round)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Calculates the reciprocal of the square root for input 'x'.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : the output tensor, has the same type as x
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Rsqrt)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Computes and returns hyperbolic sine of 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Sinh)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
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
REG_OP(Sub)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

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
REG_OP(Range)
.INPUT(start, TensorType({ DT_FLOAT, DT_INT32 }))
.INPUT(limit, TensorType({ DT_FLOAT, DT_INT32 }))
.INPUT(delta, TensorType({ DT_FLOAT, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.OP_END()

/*
 * Computes acos of input 'x'.
 * <Input>
 *    x : Input tensor, of range [-1, 1]
 * <Output>
 *    y : Output tensor of range [0, pi]. Has the same type as 'x'.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Acos)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Computes asin of input 'x'.
 * <Input>
 *    x : Input tensor, of range [-1, 1]
 * <Output>
 *    y : Output tensor of range [-pi/2, pi/2]. Has the same type as 'x'.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Asin)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Returns a new tensor with the inverse hyperbolic tangent of input 'x'.
 * <Input>
 *    x : Input tensor, of range [-1, 1]
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Atanh)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Computes natural logarithm of 'x' element-wise.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Log)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
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
REG_OP(LogicalOr)
.INPUT(x1, TensorType({ DT_BOOL }))
.INPUT(x2, TensorType({ DT_BOOL }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()
/*
 * Computes numerical negative value input.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Neg)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()
/*
 * Returns the product of elements across dimensions of the input tensor.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    axes : Dimensions to reduce. Must be in the range [-rank(x), rank(x)).
 *    keep_dims : If true, retains reduced dimensions with length 1.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(ReduceProdD)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.REQUIRED_ATTR(axes, AttrValue::LIST_INT)
.ATTR(keep_dims, AttrValue::BOOL { false })
.OP_END()
/*
 * Returns the sum of elements across dimensions of the input tensor.
 * <Input>
 *    x : Tensor to reduce
 *    axes : Dimensions to reduce
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    keep_dims : If true, retains reduced dimensions with length 1.
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const SUM_ATTR_KEEP_DIMS = "keep_dims";

REG_OP(ReduceSum)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.INPUT(axes, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.ATTR(keep_dims, AttrValue::BOOL { false })
.OP_END()

/*
 * Computes tan of input 'x'.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Tan)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes y = (alpha*x + beta)^gamma, as specified by the scale:alpha, shift:beta, and power:gamma.
 * <Input>
 *    x : the input tensor, must be non const op.
 * <Output>
 *    y : the computed outputs y = (alpha*x + beta)^gamma.
 * <Attr>
 *    scale :(optional, default 1) the scale : alpha.
 *    shift :(optional, default 0) the shift : beta.
 *    power :(optional, default 1) the power : gamma.
 * <Supported Device> CPU
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(Power)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(scale, AttrValue::FLOAT { 1.0 })
.ATTR(shift, AttrValue::FLOAT { 0.0 })
.ATTR(power, AttrValue::FLOAT { 1.0 })
.OP_END()

/*
 * Computes x1^x2 for corresponding elements in x1 and x2.
 * <Input>
 *    x1 : the input tensor.
 *    x2 : the exponent value, the datatype of x1 and x2 must be equal.
 * <Output>
 *    y : return a tensor for the result of x1^x2.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(Pow)
.INPUT(x1, TensorType({ DT_FLOAT, DT_INT32 }))
.INPUT(x2, TensorType({ DT_FLOAT, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.OP_END()

/*
 * Determine the largest value of inputs. Returns the index with the largest value across axis of a tensor.
 * <Input>
 *    x : First input tensor
 *    axis : Second input tensor, must be const op. Axis of the input tensor to reduce
 * <Output>
 *    y : Output tensor, max value index or max value
 * <Attr>
 *    output_type: Data type of output tensor
 *    keep_dims : If false,the rank of the tensor is reduced by 1 for each entry in axis.
 *              If true, the reduced dimensions are retained with length 1.
 *    outmaxval: If true, the max value is returned; if false, the max value index or value is returned.
 *            Only outmaxval = false is supported.
 *    topk: (Optional) Only topk = 1 is supported.
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const ARGMAX_ATTR_NAME_AXIS = "axis";
const char* const ARGMAX_ATTR_NAME_KEEPDIMS = "keep_dims";
const char* const ARGMAX_ATTR_NAME_OUTMAX = "outmaxval";
const char* const ARGMAX_ATTR_NAME_TOPK = "topk";

REG_OP(ArgMaxExt2)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(axis, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_INT32 }))
.ATTR(output_type, AttrValue::INT { 3 })
.ATTR(keep_dims, AttrValue::BOOL { false })
.ATTR(outmaxval, AttrValue::BOOL { false })
.ATTR(topk, AttrValue::INT { 1 })
.OP_END()

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
REG_OP(FloorDiv)
.INPUT(x1, TensorType({ DT_FLOAT, DT_INT32}))
.INPUT(x2, TensorType({ DT_FLOAT, DT_INT32}))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32}))
.OP_END()

/*
 * Returns the truth value of (x1 != x2) element-wise.
 * <Input>
 *    x1 : Tensor of type float.
 *    x2 : Tensor of the same type as 'x1'.
 * <Output>
 *    y : Tensor of type bool
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(NotEqual)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

/*
 * Returns the truth value of (x1 <= x2) element-wise.
 * <Input>
 *    x1 : Tensor of type float.
 *    x2 : Tensor of the same type as 'x1'.
 * <Output>
 *    y : Tensor of type bool.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(LessEqual)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_BOOL }))
.OP_END()

/*
 * z = a*x + y. x,y are the same dimension vectors,
 * a is the coefficient, a*x + y represents two vectors, and adds them by elements.
 * <Input>
 *    a : The input tensor,x1H,x1W must be 1.
 *    x : The input tensor,x2N,x2C must be the same with x1N,x1C.
 *    y : The input tensor,dimension vectors must be the same with x.
 * <Output>
 *    z : the output tensor
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(ChannelAxpy)
.INPUT(a, TensorType({ DT_FLOAT }))
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(y, TensorType({ DT_FLOAT }))
.OUTPUT(z, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Returns a new tensor of (x1 - x2)(x1 - x2).
 * <Input>
 *    x1 : the first input tensor.
 *    x2 : the second input tensor.
 * <Output>
 *    y : the output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(SquaredDifference)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the trignometric inverse tangent of x input.
 * <Input>
 *    x : the input tensor.
 * <Output>
 *    y : the output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(Atan)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the maximum along segments of a tensor.
 * <Input>
 *    x : The input tensor.
 *    segment_ids : A 1-D const,not supports negative index,starts from 0
 *    and should be sorted in ascending order and can be repeated.
 *    whose size is equal to the size of x first dimension.
 * <Output>
 *    y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(SegmentMax)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(segment_ids, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the minimum along segments of a tensor.
 * <Input>
 *    x : The input tensor.
 *    segment_ids : A 1-D const,not supports negative index,starts from 0
 *    and should be sorted in ascending order and can be repeated.
 *    whose size is equal to the size of x's first dimension.
 * <Output>
 *    y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(SegmentMin)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(segment_ids, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the mean along segments of a tensor.
 * <Input>
 *    x : The input tensor.
 *    segment_ids : A 1-D const,not supports negative index,starts from 0
 *    and should be sorted in ascending order and can be repeated.
 *    whose size is equal to the size of x's first dimension.
 * <Output>
 *    y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(SegmentMean)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(segment_ids, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the sum along segments of a tensor.
 * <Input>
 *    x : The input tensor.
 *    segment_ids : A 1-D const,not supports negative index,starts from 0
 *    and should be sorted in ascending order and can be repeated.
 *    whose size is equal to the size of x's first dimension.
 * <Output>
 *    y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(SegmentSum)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(segment_ids, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Computes the product along segments of a tensor.
 * <Input>
 *    x : The input tensor.
 *    segment_ids : A 1-D const,not supports negative index,starts from 0
 *    and should be sorted in ascending order and can be repeated.
 *    whose size is equal to the size of x's first dimension.
 * <Output>
 *    y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(SegmentProd)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(segment_ids, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Multiplies slices of two tensors in batches.
 * <Input>
 *    x1 : The input tensor
 *    x2 : The input tensor
 * <Output>
 *    y : The output tensor
 * <Attr>
 *    adj_x1 : adj_x1 is true, the input tensor x1  is  transposed, otherwise it will not be transposed.
 *             Default is false (The current version only supports false).
 *    adj_x2 : adj_x2 is true, the input tensor x2  is  transposed, otherwise it will not be transposed.
 *             Default is false.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const BATCHMATMUL_ATTR_NAME_ADJ_X1 = "adj_x1";
const char* const BATCHMATMUL_ATTR_NAME_ADJ_X2 = "adj_x2";

REG_OP(BatchMatMul)
.INPUT(x1, TensorType({ DT_FLOAT }))
.INPUT(x2, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(adj_x1, AttrValue::BOOL { false })
.ATTR(adj_x2, AttrValue::BOOL { false })
.OP_END()

/*
 * Given a tensor x, this operation returns a tensor of the same type and shape as x with its values clipped to
 * clip_value_min and clip_value_max. Any values less than clip_value_min are set to clip_value_min.
 * Any values greater than clip_value_max are set to clip_value_max.
 * <Input>
 *    x : A Tensor or IndexedSlices
 *    clip_value_min : It must be const Input, The value is a 0-D (scalar) Tensor,
 *                 or a Tensor with the same shape as x. The minimum value to clip by.
 *    clip_value_max : It must be const Input, The value is a 0-D (scalar) Tensor,
 *                 or a Tensor with the same shape as x. The maximum value to clip by.
 * <Output>
 *    y : the output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(ClipByValue)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(clip_value_min, TensorType({ DT_FLOAT }))
.INPUT(clip_value_max, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/* Standardize the specified dimension using the L2 norm.
 * <Input>
 *    x : the input tensor to be standardized.
 * <Output>
 *    y : the output tensor with the same shape as x.
 * <Attr>
 *    axis: the dimension which to be standardized. Support { 1 } or { 3 } now.
 *    eps: the lower limit of the standardization, when the calculated sum of the squares of the elements
 *        of x is less than eps, using eps instead of the sum of the elements of x.
 * <Added in HiAI version>
 *    100.320.010.010
 */
const char* const L2_NORMALIZE_ATTR_AXIS = "axis";
const char* const L2_NORMALIZE_ATTR_EPS = "eps";

REG_OP(L2Normalize)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(axis, AttrValue::LIST_INT({ 1 }))
.ATTR(eps, AttrValue::FLOAT { 1e-4f })
.OP_END()

/*
 * Computes the maximum of elements across dimensions of a tensor.
 * <Input>
 *    x : The tensor to reduce. Should have real numeric type.
 *    axes: The dimensions to reduce.Must be in the range [-rank(x), rank(x)). Const Op.
 * <Output>
 *    y : the output tensor.
 * <Attr>
 *     keep_dims: If true, retains reduced dimensions with length 1.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const REDUCEMAX_ATTR_NAME_KEEP_DIMS = "keep_dims";

REG_OP(ReduceMax)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.INPUT(axes, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.ATTR(keep_dims, AttrValue::BOOL{ false })
.OP_END()

/*
 * Computes the minimum of elements across axis of a tensor.
 * <Input>
 *    x :The tensor to reduce. Should have real numeric type.
 *    axes: The dimensions to reduce.Must be in the range [-rank(x), rank(x)).  Const Op.
 * <Output>
 *    y : The output tensor.
 * <Attr>
 *    keep_dims: If true, retains reduced dimensions with length 1, only support true.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const REDUCEMIN_ATTR_NAME_KEEP_DIMS = "keep_dims";

REG_OP(ReduceMin)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(axes, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(keep_dims, AttrValue::BOOL { false })
.OP_END()
} // namespace hiai
#pragma GCC diagnostic pop
#endif  // _HIAI_GRAPH_OP_GE_OP_MATH_DEFS_H
