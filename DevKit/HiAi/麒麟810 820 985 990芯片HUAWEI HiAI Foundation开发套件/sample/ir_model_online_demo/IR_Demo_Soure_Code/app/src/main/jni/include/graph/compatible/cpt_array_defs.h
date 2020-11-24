/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: array_defs
 */

#ifndef _CCE_GRAPH_OP_GE_OP_ARRAY_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_ARRAY_DEFS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#ifdef _MSC_VER
#undef __out_z
#endif

#include "./operator_reg.h"
#include "../op/array_defs.h"

namespace ge {
/*
 * Data tensor
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(Data)
.CPT_INPUT(x, TensorType({DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL}))
.CPT_OUTPUT(y, TensorType({DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL}))
.CPT_OP_END()

/*
 * Concatenates a list of tensors into a single tensor along one dimension.
 * The number of dimensions of the input tensors must match, and all dimensions except axis must be equal.
 * <Input>
 *    x    : List of tensors for concatenation
 * <Output>
 *    y    : Concatenated tensor
 * <Attr>
 *    axis : Dimension along which to concatenate
 *    N    : Number of inputs
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::CONCAT_ATTR_NAME_AXIS;

CPT_REG_OP(Concat)
.CPT_DYNAMIC_INPUT(x, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_ATTR(axis, AttrValue::INT { 1 })
.CPT_ATTR(N, AttrValue::INT { 1 })
.CPT_OP_END()

/*
 * Reshapes the input tensor.
 * <Input>
 *    tensor : Input tensor, of the same type as Data
 *    w      : Weight to be filled when the Attr 'shape' is not specified, and the input type is const
 * <Output>
 *    output : Reshaped tensor that has the same values as Attr 'shape'
 * <Attr>
 *    shape    : Tensor specifying the output shape
 *    axis     : Dimension along which to reshape
 *    num_axes : Used to calculate the output shape
 *               When 'num_axes' is -1, output.shape.size() = shape.size() + axis.
 *               When 'num_axes' is not -1, output.size() = shape.size() + tensor.size() - num_axes.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::RESHAPE_ATTR_AXIS;
using hiai::RESHAPE_ATTR_NUM_AXES;
using hiai::RESHAPE_ATTR_SHAPE;

CPT_REG_OP(Reshape)
.CPT_INPUT(tensor, TensorType({ DT_FLOAT, DT_INT32, DT_INT64, DT_BOOL }))
.CPT_OPTIONAL_INPUT(w, TensorType({ DT_FLOAT, DT_INT32, DT_INT64, DT_BOOL }))
.CPT_OUTPUT(output, TensorType({ DT_FLOAT, DT_INT32, DT_INT64, DT_BOOL }))
.CPT_REQUIRED_ATTR(shape, AttrValue::LIST_INT)
.CPT_ATTR(axis, AttrValue::INT { 0 })
.CPT_ATTR(num_axes, AttrValue::INT{ -1 })
.CPT_OP_END()

/*
 * Splits a tensor into a list of tensors along the axis.
 * <Input>
 *    x : Input tensor, of the same type as Data
 * <Output>
 *    y : (Mandatory) spited tensors, whose number is specified by 'output_num'
 * <Attr>
 *    axis        : Dimension along which to split, must be in the range [0, axis_dim_count),
 *                  axis_dim_count % output_num must be 0.
 *    output_num  : Number of outputs. axis_dim_count % output_num must be 0.
 *    slice_point : (Optional) number of splits. If set, slice_point.size = output_num - 1.
 *                  The slice_point.value should be incremented in the range of (0, axis_dim_count).
 *                  Set either or none of 'sce_point' and 'size_split'. If both are set, an error will be reported.
 *    size_split  : (Optional) sizes of each output tensor. If set, SUM (size_split.value) = axis_dim_count.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::SPLIT_ATTR_NAME_NUM_SPLIT;
using hiai::SPLIT_ATTR_NAME_SPLIT_DIM;

CPT_REG_OP(Split)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL }))
.CPT_DYNAMIC_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL }))
.CPT_REQUIRED_ATTR(axis, AttrValue::INT)
.CPT_REQUIRED_ATTR(output_num, AttrValue::INT)
.CPT_ATTR(slice_point, AttrValue::LIST_INT {})
.CPT_ATTR(size_split, AttrValue::LIST_INT {})
.CPT_OP_END()

/*
 * Splits a tensor into 'num_split' tensors along one dimension.
 * <Input>
 *    x          : Input tensor, of the same type as Data
 *    size_splits: Tensor of type int32
 *    split_dim  : Tensor of type int32
 * <Output>
 *    y          : (Mandatory) spited tensors, whose number is specified by 'output_num'
 * <Attr>
 *   num_split   : int (>= 1), number of outputs
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(SplitV)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(size_splits, TensorType({ DT_INT32 }))
.CPT_INPUT(split_dim, TensorType({ DT_INT32 }))
.CPT_ATTR(num_split, AttrValue::INT { 0 })
.CPT_DYNAMIC_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Unpacks the given dimension of a rank-R tensor into rank-(R-1) tensors.
 * <Input>
 *    x     : Input tensor, of the same type as Data
 * <Output>
 *    y     : List of Tensor objects unstacked from value
 * <Attr>
 *    axis  : Axis to unpack along
 *    num   : Length of the dimension 'axis'
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::UNPACK_ATTR_NAME_NUM;

CPT_REG_OP(Unpack)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_DYNAMIC_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.CPT_ATTR(axis, AttrValue::INT { 0 })
.CPT_ATTR(num, AttrValue::INT { 0 })
.CPT_OP_END()

/*
 * Flattens the input tensor into a 2D matrix.
 * <Input>
 *    x : Tensor of rank
 * <Output>
 *    y : 2D tensor with the contents of the input tensor, with input dimensions up to axis flattened to
 *       the outer dimension of the output and remaining input dimensions flattened into the inner dimension
 *       of the output.
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(Flatten)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Extracts a slice of size 'size' from a tensor input starting at the location specified by 'offsets'.
 * The slice 'size' is represented as a tensor shape, where size[i] is the number of elements of the ith
 * dimension to slice. The starting location (offsets) for the slice is represented as an offset in each
 * dimension of input. In other words, offsets[i] is the offset into the ith dimension of input to slice.
 * <Input>
 *      input : Input tensor
 *    offsets : Const, starting location for each dimension of input
 *       size : Const, number of elements for each dimension of input
 * <Output>
 *      y : Output tensor
 * <Attr>
 *   axis : Dimension of input to slice
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Slice)
.CPT_INPUT(input, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_INPUT(offsets, TensorType({ DT_INT32 }))
.CPT_INPUT(size, TensorType({ DT_INT32  }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_ATTR(axis, AttrValue::INT { 0 })
.CPT_OP_END()

/*
 * Inserts a dimension of 1 into a tensor's shape.
 * <Input>
 *    x   : Input tensor
 *   axis : 0D (scalar), dimension index at which to expand the shape of input
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(ExpandDims)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_INPUT(axis, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_OP_END()

/*
 * Gathers slices from 'params' axis 'axis' according to 'indices'.
 * <Input>
 *     params : Tensor from which to gather values
 *    indices : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    axis : Defaults to 0.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Gather)
.CPT_INPUT(params, TensorType({ DT_FLOAT , DT_INT32 }))
.CPT_INPUT(indices, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32 }))
.CPT_ATTR(axis, AttrValue::INT { 0 })
.CPT_OP_END()

/*
 * Gathers slices from 'params' into a Tensor with shape specified by 'indices'.
 * <Input>
 *    params : Tensor from which to gather values
 *    indices :Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(GatherNd)
.CPT_INPUT(params, TensorType({ DT_FLOAT , DT_INT32  }))
.CPT_INPUT(indices, TensorType({ DT_FLOAT , DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32  }))
.CPT_OP_END()

/*
 * Packs a tensor.
 * Stacks a list of rank-R tensors into one rank-(R+1) tensor.
 * <Input>
 *    values: List of Tensor objects with the same shape and type
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    axis : Axis to stack along
 *    N    : Number of values
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::PACK_ATTR_NAME_NUM;

CPT_REG_OP(Pack)
.CPT_DYNAMIC_INPUT(values, TensorType({ DT_FLOAT , DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32 }))
.CPT_REQUIRED_ATTR(axis, AttrValue::INT)
.CPT_REQUIRED_ATTR(N, AttrValue::INT)
.CPT_OP_END()

/*
 * Rearranges blocks of spatial data, into depth. More specifically, this op outputs a copy of
 * the input tensor where values from the height and width dimensions are moved to the depth dimension.
 * The attr block_size indicates the input block size.
 * <Input>
 *    x : Input tensor with shape [n, h, w, c], where h and w must be divisible by 'block_size'
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    block_size : int (>= 1), size of the spatial block
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(SpaceToDepth)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_REQUIRED_ATTR(block_size, AttrValue::INT)
.CPT_OP_END()

/*
 * Extracts a strided slice of a tensor
 * <Input>
 *    x       : Input tensor
 *    begin   : Input tensor
 *    end     : Input tensor
 *    strides : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    begin_mask       : Defaults to 0.
 *    end_mask         : Defaults to 0.
 *    ellipsis_mask    : Defaults to 0.
 *    new_axis_mask    : Defaults to 0.
 *    shrink_axis_mask : Defaults to 0.
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::STRIDE_SLICE_ATTR_BEGIN_MASK;
using hiai::STRIDE_SLICE_ATTR_END_MASK;
using hiai::STRIDE_SLICE_ATTR_ELLIPSIS_MASK;
using hiai::STRIDE_SLICE_ATTR_NEW_AXIS_MASK;
using hiai::STRIDE_SLICE_ATTR_SHRINK_AXIS_MASK;

CPT_REG_OP(StridedSlice)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_INPUT(begin, TensorType({ DT_INT32 }))
.CPT_INPUT(end, TensorType({ DT_INT32 }))
.CPT_INPUT(strides, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_REQUIRED_ATTR(begin_mask, AttrValue::INT)
.CPT_REQUIRED_ATTR(end_mask, AttrValue::INT)
.CPT_REQUIRED_ATTR(ellipsis_mask, AttrValue::INT)
.CPT_REQUIRED_ATTR(new_axis_mask, AttrValue::INT)
.CPT_REQUIRED_ATTR(shrink_axis_mask, AttrValue::INT)
.CPT_OP_END()

/*
 * Zero-pads and then rearranges blocks of spatial data into batch.The operation outputs
 * a copy of the input tensor, in which the values from the height and width dimensions
 * are moved to the batch dimension.
 * <Input>
 *    x : 4-D tensor with shape [batch, height, width, depth]. Both height and width must be divisible
 * by 'block_shape'.
 *    block_shape : Const OP, 1-D with shape [M], where all values must be >= 1
 *    paddings : Const OP, 2-D with shape [M, 2], where, all values must be >= 0
 *              paddings = [[pad_top, pad_bottom], [pad_left, pad_right]]
 *              The effective spatial dimensions of the zero-padded input tensor will be:
 *              height_pad = pad_top + height + pad_bottom
 *              width_pad = pad_left + width + pad_right
 *              Both 'height_pad' and 'width_pad' must be divisible by 'block_size'.
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(SpaceToBatchND)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(block_shape, TensorType({ DT_INT32 }))
.CPT_INPUT(paddings, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * This operation reshapes the "batch" dimension 0 into M + 1 dimensions of shape block_shape + [batch].
 * Interleaves these blocks back into the grid defined by the spatial dimensions [1, ..., M], to obtain a result
 * with the same rank as the input.The spatial dimensions of this intermediate result are then optionally cropped
 * according to crops to produce the output.
 * <Input>
 *    x : Input tensor. It is required that the elements of x.dimension[0] must be divided by
 * block_shape.dimension[0] * block_shape.dimension[1].
 *    block_shape : Const OP, 1-D with shape [M], where all values must be >= 1
 *    crops : Const OP, 2-D with shape [M, 2], where all values must be >= 0. crops[i] = [crop_start, crop_end]
 * specifies the amount to crop from input dimension i + 1, which corresponds to spatial dimension i. It is required
 * that crop_start[i] + crop_end[i] <= block_shape[i] * input_shape[i + 1].
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(BatchToSpaceND)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(block_shape, TensorType({ DT_INT32 }))
.CPT_INPUT(crops, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Constructs a tensor by tiling a given tensor.
 * <Input>
 *    x : Input tensor
 *    w : Const OP
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Tile)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_INPUT(w, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_OP_END()

/*
 * Returns the size of a tensor.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Size)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.CPT_OUTPUT(y, TensorType({ DT_INT32 }))
.CPT_OP_END()
/*
 * Creates a tensor of shape 'dims' and fills it with 'value'.
 * <Input>
 *    dims : 1-D, shape of the output tensor
 *    value : 0-D, value to fill the returned tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Fill)
.CPT_INPUT(dims, TensorType({ DT_INT32, DT_UINT8 }))
.CPT_INPUT(value, TensorType({ DT_FLOAT, DT_BOOL, DT_INT32, DT_UINT8 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_BOOL, DT_INT32, DT_UINT8 }))
.CPT_OP_END()
/*
 * Returns the inverse permutation of a tensor.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(InvertPermutation)
.CPT_INPUT(x, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_INT32 }))
.CPT_OP_END()

/*
 * Reverses variable length slices.
 * <Input>
 *    x : Input tensor to reverse
 *    seq_lengths : 1-D with length input, seq_lengths.dimension[0] == x.dimension[batch_dim]
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    seq_dim : dimension partially reversed, default to 1. 'seq_dim' should not equal to 'batch_dim' or
 * (x.dimension size + batch_dim). 'seq_dim' must be in range [-x.dimension size, x.dimension size).
 *    batch_dim : dimension along which reversal is performed, default to 0. 'batch_dim' must not equal to
 * seq_dim or (x.dimension + seq_dim). 'batch_dim' must be in range [-x.dimension size,x.dimension size).
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(ReverseSequence)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_INPUT(seq_lengths, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_ATTR(seq_dim, AttrValue::INT { 1 })
.CPT_ATTR(batch_dim, AttrValue::INT { 0 })
.CPT_OP_END()
}  // namespace ge
#pragma GCC diagnostic pop

#endif  // _CCE_GRAPH_OP_GE_OP_ARRAY_DEFS_H
