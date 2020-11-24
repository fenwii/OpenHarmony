/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: array_defs
 */

#ifndef _HIAI_GRAPH_OP_GE_OP_ARRAY_DEFS_H
#define _HIAI_GRAPH_OP_GE_OP_ARRAY_DEFS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#ifdef _MSC_VER
#undef __out_z
#endif

#include "../operator_hiai_reg.h"

namespace hiai {
/*
 * Data tensor
 * <Input>
 *      x : Input tensor
 * <Output>
 *      y : Output tensor
 * <Attr>
 *      index : Reserved. The index of input data in network, only support 0 currently.
 * <Added in HiAI version>
 *    100.300.010.011
 */
REG_OP(Data)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT8, DT_UINT8, DT_INT32, DT_BOOL }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT8, DT_UINT8, DT_INT32, DT_BOOL }))
.ATTR(index, AttrValue::INT { 0 })
.OP_END()

/*
 * Concatenates a list of tensors into a single tensor along one dimension.
 * The number of dimensions of the input tensors must match, and all dimensions except axis must be equal.
 * <Input>
 *      x : List of tensors for concatenation
 * <Output>
 *      y : Concatenated tensor
 * <Attr>
 *      concat_dim : Dimension along which to concatenate
 *      N : Number of inputs
 * <Added in HiAI version>
 *    100.300.010.011
 */
const char* const CONCAT_ATTR_NAME_AXIS = "concat_dim";
const char* const CONCAT_ATTR_NAME_NUM = "N";

REG_OP(ConcatD)
.DYNAMIC_INPUT(x, TensorType({ DT_FLOAT, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.REQUIRED_ATTR(concat_dim, AttrValue::INT)
.ATTR(N, AttrValue::INT { 1 })
.OP_END()

/*
 * Fake-quantize the inputs tensor of type float via global float scalars.
 * <Input>
 *      x : A Tensor of type float32.
 *      min : 0D (scalar), A Tensor of type float32.
 *      max : 0D (scalar), A Tensor of type float32.
 * <Output>
 *      y : A Tensor of type float32.
 * <Attr>
 *      num_bits : An optional int. Defaults to 8.
 *      narrow_range: An optional bool. Defaults to False.
 * <Added in HiAI version>
 *    100.500.010.011
 */
const char* const FAKEQUANTWITHMINMAXVARS_ATTR_NUMBITS = "num_bits";
const char* const FAKEQUANTWITHMINMAXVARS_ATTR_NARROWRANGE = "narrow_range";

REG_OP(FakeQuantWithMinMaxVars)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(min, TensorType({ DT_FLOAT }))
.INPUT(max, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(num_bits, AttrValue::INT{ 8 })
.ATTR(narrow_range, AttrValue::BOOL{ false })
.OP_END()


/*
 * Reshape the input tensor.
 * <Input>
 *    x : Input tensor, of the same type as Data
 *    shape : The shape to be resized, must be const op
 * <Output>
 *    y : Reshaped tensor that has the same values as Attr 'shape'
 * <Attr>
 *    axis     : Dimension along which to reshape
 *    num_axes : Used to calculate the output shape
 *               When 'num_axes' is -1, output.size() = shape.size() + axis.
 *               When 'num_axes' is not -1, output.size() = shape.size() + tensor.size() - num_axes.
 * <Added in HiAI version>
 *    100.300.010.011
 */
const char* const RESHAPE_ATTR_AXIS = "axis";
const char* const RESHAPE_ATTR_NUM_AXES = "num_axes";
const char* const RESHAPE_ATTR_SHAPE = "shape";

REG_OP(Reshape)
.INPUT(x, TensorType({ DT_FLOAT,DT_INT32,DT_INT64,DT_BOOL }))
.INPUT(shape, TensorType({ DT_INT32, DT_INT64 }))
.OUTPUT(y, TensorType({ DT_FLOAT,DT_INT32,DT_INT64,DT_BOOL }))
.ATTR(axis, AttrValue::INT { 0 })
.ATTR(num_axes, AttrValue::INT { -1 })
.OP_END()

/*
 * Splits a tensor into a list of tensors along the split_dim.
 * <Input>
 *      x : Input tensor, of the same type as Data
 * <Output>
 *      y : (Mandatory) splited tensors, whose number is specified by num_split
 * <Attr>
 *      split_dim : Which axis to split on, the value should be in range of [-RANK(X), RANK(X)).
 *      num_split : Number of outputs, x.shape[split_dim] % num_split should be 0.
 * <Added in HiAI version>
 *    100.300.010.011
 */
const char* const SPLIT_ATTR_NAME_SPLIT_DIM = "split_dim";
const char* const SPLIT_ATTR_NAME_NUM_SPLIT = "num_split";

REG_OP(SplitD)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL }))
.DYNAMIC_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL }))
.REQUIRED_ATTR(split_dim, AttrValue::INT)
.REQUIRED_ATTR(num_split, AttrValue::INT)
.OP_END()

/*
 * Splits a tensor into 'num_split' tensors along one dimension.
 * <Input>
 *    x          : Input tensor, of the same type as Data
 *    size_splits :Tensor of type int32, must be const op
 *    split_dim  : Tensor of type int32, must be const op
 * <Output>
 *    y          : (Mandatory) spited tensors, whose number is specified by 'num_split'
 * <Attr>
 *   num_split   : int (>= 1), number of outputs
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(SplitV)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(size_splits, TensorType({ DT_INT32 }))
.INPUT(split_dim, TensorType({ DT_INT32 }))
.ATTR(num_split, AttrValue::INT { 0 })
.DYNAMIC_OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Unpacks the given dimension of a rank-R tensor into rank-(R-1) tensors.
 * <Input>
 *    x     : Input tensor
 * <Output>
 *    y     : List of Tensor objects unstacked from x
 * <Attr>
 *    num   : Output number of tensor after split
 *    axis  : Axis to unpack along
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const UNPACK_ATTR_NAME_NUM = "num";

REG_OP(Unpack)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32 }))
.DYNAMIC_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.REQUIRED_ATTR(num, AttrValue::INT)
.ATTR(axis, AttrValue::INT { 0 })
.OP_END()

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
REG_OP(Flatten)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Extracts a slice of size 'size' from a tensor input starting at the location specified by 'offsets '.
 * The slice 'size' is represented as a tensor shape,
 * where size[i] is the number of elements of the ith dimension to slice.
 * The starting location (offsets) for the slice is represented as an offset in each dimension of input.
 * In other words, offsets[i] is the offset into the ith dimension of input to slice.
 * <Input>
 *      x : Input tensor
 *      offsets : Const, starting location for each dimension of input
 *      size :  Const, number of elements for each dimension of input
 * <Output>
 *      y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Slice)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.INPUT(offsets, TensorType({ DT_INT32 }))
.INPUT(size, TensorType({ DT_INT32  }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OP_END()

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
REG_OP(ExpandDims)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.INPUT(axis, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OP_END()

/*
 * Gathers slices from 'x' axis according to 'indices'.
 * <Input>
 *      x : Tensor from which to gather values
 *      indices : Input tensor
 * <Output>
 *      y : Output tensor
 * <Attr>
 *      axis : which axis to gather values.
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const GATHERV2D_ATTR_NAME_AXIS = "axis";

REG_OP(GatherV2D)
.INPUT(x, TensorType({ DT_FLOAT , DT_INT32 }))
.INPUT(indices, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32 }))
.REQUIRED_ATTR(axis, AttrValue::INT)
.OP_END()

/*
 * Gathers slices from 'x' into a Tensor with shape specified by 'indices'.
 * <Input>
 *    x       : Tensor from which to gather values
 *    indices :Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(GatherNd)
.INPUT(x, TensorType({ DT_FLOAT , DT_INT32  }))
.INPUT(indices, TensorType({ DT_FLOAT , DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32  }))
.OP_END()

/*
 * Stacks a list of rank-R tensors into one rank-(R+1) tensor.
 * <Input>
 *    x : List of Tensor objects with the same shape and type
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    axis : Axis to stack along
 *    N    : Number of values
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const PACK_ATTR_NAME_NUM = "N";
const char* const PACK_ATTR_NAME_AXIS = "axis";

REG_OP(Pack)
.DYNAMIC_INPUT(x, TensorType({ DT_FLOAT , DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32 }))
.ATTR(axis, AttrValue::INT { 0 })
.REQUIRED_ATTR(N, AttrValue::INT)
.OP_END()

/*
 * Rearranges blocks of spatial data, into depth. More specifically, this op outputs a copy of
 * the input tensor where values from the height and width dimensions are moved to the depth dimension.
 * The attr block_size indicates the input block size.
 * <Input>
 *    x : Input tensor with shape [n, c, h, w] or [n, h, w, c], where h and w must be divisible by 'block_size'
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    block_size  : int (>= 1), size of the spatial block
 *    data_format  : Format of input, 'NCHW' or 'NHWC'. Default is 'NHWC'
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const SPACETODEPTH_ATTR_NAME_BLOCK_SIZE = "block_size";
const char* const SPACETODEPTH_ATTR_NAME_DATA_FORMAT = "data_format";

REG_OP(SpaceToDepth)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.REQUIRED_ATTR(block_size, AttrValue::INT)
.ATTR(data_format, AttrValue::STR { "NHWC" })
.OP_END()

/*
 * Rearranges data from depth into blocks of spatial data.This is the reverse transformation of SpaceToDepth.
 * More specifically, this op outputs a copy of the input tensor where values from the depth dimension are moved
 * in spatial blocks to the height and width dimensions.
 * <Input>
 *    x : The input tensor with shape [ batch, height, width, channels ], channels
 *        must be divided by block_size*block_size.
 * <Output>
 *    y: The output tensor
 * <Attr>
 *    block_size : The size of the spatial block, must be greater than 0.
 *    mode : DCR (default) for depth-column-row order re-arrangement.
 *          CRD for column-row-depth order.
 *    data_format : The data format of input, now only support : NHWC.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const DEPTH_SPACE_ATTR_BLOCK_SIZE = "block_size";
const char* const DEPTH_SPACE_ATTR_DATA_FORMAT = "data_format";
const char* const DEPTH_SPACE_ATTR_MODE = "mode";

REG_OP(DepthToSpace)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.REQUIRED_ATTR(block_size, AttrValue::INT)
.ATTR(mode, AttrValue::STR { "DCR" })
.ATTR(data_format, AttrValue::STR { "NHWC" })
.OP_END()

/*
 * Extracts a strided slice of a tensor
 * <Input>
 *    x       : Input tensor
 *    begin   : An int32 tensor, must be const op
 *    end     : An int32 tensor, must be const op
 *    strides  : An int32 tensor, must be const op
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    begin_mask       : An int32 mask ,defaults to 0.
 *    end_mask         : An int32 mask ,defaults to 0.
 *    ellipsis_mask    : An int32 mask ,defaults to 0.
 *    new_axis_mask    : An int32 mask ,defaults to 0.
 *    shrink_axis_mask : Defaults to 0.
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const STRIDE_SLICE_ATTR_BEGIN_MASK = "begin_mask";
const char* const STRIDE_SLICE_ATTR_END_MASK = "end_mask";
const char* const STRIDE_SLICE_ATTR_ELLIPSIS_MASK = "ellipsis_mask";
const char* const STRIDE_SLICE_ATTR_NEW_AXIS_MASK = "new_axis_mask";
const char* const STRIDE_SLICE_ATTR_SHRINK_AXIS_MASK = "shrink_axis_mask";

REG_OP(StridedSlice)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.INPUT(begin, TensorType({ DT_INT32  }))
.INPUT(end, TensorType({ DT_INT32  }))
.INPUT(strides, TensorType({ DT_INT32  }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.ATTR(begin_mask, AttrValue::INT { 0 })
.ATTR(end_mask, AttrValue::INT { 0 })
.ATTR(ellipsis_mask, AttrValue::INT { 0 })
.ATTR(new_axis_mask, AttrValue::INT { 0 })
.ATTR(shrink_axis_mask, AttrValue::INT { 0 })
.OP_END()

/*
 * Zero-pads and then rearranges blocks of spatial data into batch.The operation outputs
 * a copy of the input tensor, in which the values from the height and width dimensions
 * are moved to the batch dimension.
 * <Input>
 *    x : 4-D tensor with shape [batch, depth, height, width]. Both height and width must be divisible
 *        by 'block_shape'.
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
REG_OP(SpaceToBatchND)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(block_shape, TensorType({ DT_INT32 }))
.INPUT(paddings, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * This operation reshapes the "batch" dimension 0 into M + 1 dimensions of shape block_shape + [batch].
 * Interleaves these blocks back into the grid defined by the spatial dimensions [1, ..., M], to obtain a result
 * with the same rank as the input.The spatial dimensions of this intermediate result are then optionally cropped
 * according to crops to produce the output.
 * <Input>
 *    x : 4-D tensor. It is required that the elements of x.dimension[0]
 * must be divided by block_shape.dimension[0] * block_shape.dimension[1].
 *    block_shape : Const OP, 1-D with shape [M], where all values must be >= 1
 *    crops : Const OP, 2-D with shape [M, 2], where all values must be >= 0. crops[i] = [crop_start, crop_end]
 * specifies the amount to crop from input dimension i + 1, which corresponds to spatial dimension i. It is required
 * that crop_start[i] + crop_end[i] <= block_shape[i] * input_shape[i + 1].
 * <Output>
 *    y : Tensor of the same type as 'x'
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(BatchToSpaceND)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(block_shape, TensorType({ DT_INT32 }))
.INPUT(crops, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.OP_END()

/*
 * Constructs a tensor by tiling a given tensor.
 * <Input>
 *    x : Input tensor
 *    multiples : Const OP
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Tile)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.INPUT(multiples, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OP_END()

/*
 * Returns the size of a tensor.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    dtype : Reserved. data type of the output y.
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const SIZE_ATTR_DTYPE = "dtype";

REG_OP(Size)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OUTPUT(y, TensorType({ DT_INT32 }))
.ATTR(dtype, AttrValue::INT { DT_INT32 })
.OP_END()
/*
 * Creates a tensor of shape 'dims' and fills it with 'value'.
 * <Input>
 *    dims : Const OP, 1-D, shape of the output tensor
 *    value : 0-D, value to fill the returned tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(Fill)
.INPUT(dims, TensorType({ DT_INT32 }))
.INPUT(value, TensorType({ DT_FLOAT, DT_BOOL, DT_INT32, DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_BOOL, DT_INT32, DT_UINT8 }))
.OP_END()
/*
 * Returns the inverse permutation of a tensor.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(InvertPermutation)
.INPUT(x, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_INT32 }))
.OP_END()

/*
 * Performs tensor select.
 * <Input>
 *    condition : the condition of select. Only support first dimension broadcast.
 *    x1 : First operand.
 *    x2 : Second operand, has the same shape of x1.
 * <Output>
 *    y : Result, has same element type as two inputs.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(Select)
.INPUT(condition, TensorType({ DT_BOOL }))
.INPUT(x1, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.INPUT(x2, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OUTPUT(y, TensorType({DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.OP_END()

/*
 * Reverses variable length slices.
 * <Input>
 *    x : A rank R >0 tensor to reverse
 *    seq_lengths : 1-D with length input, seq_lengths.dimension[0] == x.dimension[batch_dim]
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    seq_dim : dimension partially reversed. 'seq_dim' should not equal to 'batch_dim'.
 *            'seq_dim' must be in range [-R, R).
 *    batch_dim : dimension along which reversal is performed, default to 0.
 *              'batch_dim' must not equal to 'seq_dim'.
 *              'batch_dim' must be in range [-R,R).
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const REVERSE_SEQUENCE_ATTR_SEQ_DIM = "seq_dim";
const char* const REVERSE_SEQUENCE_ATTR_BATCH_DIM = "batch_dim";

REG_OP(ReverseSequence)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.INPUT(seq_lengths, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.REQUIRED_ATTR(seq_dim, AttrValue::INT)
.ATTR(batch_dim, AttrValue::INT { 0 })
.OP_END()

/*
 * The operation pads input according to the paddings and constant_values.
 * <Input>
 *    x : The input tensor.
 *    paddings : The values of paddings, as a role of dimensions to be added on the input tensor x,
 *               must be a Const-OP.
 *    constant_values : A tensor of the same type as x, that indicates the value to use for padding input,
 *                      must be a Const-OP.
 * <Output>
 *    y : The output tensor.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(PadV2)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32 }))
.INPUT(paddings, TensorType({ DT_INT32 }))
.INPUT(constant_values, TensorType({ DT_FLOAT, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32 }))
.OP_END()

/*
 * Given a tensor input, this operation returns a tensor of the same type with all dimensions of size 1 removed.
 * If you do not want to remove all size with 1 dimensions, you can remove specific size 1 dimensions by specifying axis.
 * <Input>
 *    x : The input to be squeezed.
 * <Output>
 *    y : The output tensor.
 * <Attr>
 *    axis : The dimensions which to remove.
 * <Added in HiAI version>
 *    100.320.010.010
 */
const char* const SQUEEZE_ATTR_AXIS = "axis";

REG_OP(Squeeze)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(axis, AttrValue::LIST_INT({}))
.OP_END()

/*
 * Extracts, rearranges, and combines input data.
 * <Input>
 *    x : Input tensor
 *    reindex: Index of input tensor
 * <Output>
 *    y : Output tensor
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(BatchReindex)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(reindex, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT}))
.OP_END()
/*
 * Pads a tensor.
 * <Input>
 *    x : The input tensor
 *    paddings : The values of padding, as a role of dimensions to be added on the input tensor x,
 *              with shape [D, 2], D is the rank of x.
 * <Output>
 *    y : The output tensor
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(Pad)
.INPUT(x, TensorType({ DT_FLOAT , DT_INT32 }))
.INPUT(paddings, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32 }))
.OP_END()

/*
 * Pads a tensor with mirrored values.
 * <Input>
 *    x : The input tensor
 *    paddings : The values of paddings, as a role of dimensions to be added on the input tensor x,
 *               must be a Const-OP.
 * <Output>
 *    y : The output tensor
 * <Attr>
 *    mode : REFLECT or SYMMETRIC.
 *           SYMMETRIC  paddings must be no greater than the x dimension size
 *           REFLECT  paddings must be less than the x dimension size
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const MIRRORPAD_ATTR_MODE = "mode";

REG_OP(MirrorPad)
.INPUT(x, TensorType({ DT_FLOAT , DT_INT32, DT_BOOL, DT_INT64 }))
.INPUT(paddings, TensorType({ DT_INT32, DT_INT64 }))
.OUTPUT(y, TensorType({ DT_FLOAT , DT_INT32, DT_BOOL, DT_INT64 }))
.REQUIRED_ATTR(mode, AttrValue::STR)
.OP_END()

/*
 * Return a one-hot tensor
 * <Input>
 *    x : A index tensor.
 *    depth : A scalar defining the depth of the one hot dimension.
 *    on_value : A scalar defining the value to fill in output when x[j] = i. (default: 1).
 *    off_value : A scalar defining the value to fill in output when x[j] != i. (default: 0).
 * <Output>
 *    y : Result, has element type as T.
 * <Attr>
 *    axis : The axis to fill.(default: -1)
 * <added in HiAI version>
 *    100.320.010.010
 */

const char* const ONEHOT_ATTR_AXIS = "axis";

REG_OP(OneHot)
.INPUT(x, TensorType({ DT_INT32, DT_UINT8 }))
.INPUT(depth, TensorType({ DT_INT32 }))
.INPUT(on_value, TensorType({ DT_UINT8, DT_INT8, DT_FLOAT, DT_BOOL }))
.INPUT(off_value, TensorType({ DT_UINT8, DT_INT8, DT_FLOAT, DT_BOOL }))
.OUTPUT(y, TensorType({ DT_UINT8, DT_INT8, DT_FLOAT, DT_BOOL }))
.ATTR(axis, AttrValue::INT { -1 })
.OP_END()

/*
 * Obtain the shape of input tensor , expressed in the form of one-dimensional integer tensor.
 * <Input>
 *    x : The input tensor.
 * <Output>
 *    y: The output tensor.
 * <Attr>
 *    dtype : Reserved. data type of the output y.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const SHAPE_ATTR_DTYPE = "dtype";

REG_OP(Shape)
.INPUT(x, TensorType({ DT_FLOAT , DT_INT32, DT_BOOL, DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_INT32 }))
.ATTR(dtype, AttrValue::INT{ DT_INT32 })
.OP_END()

/*
 * Dequantizes the 'input' tensor into a float tensor.
 * <Input>
 *    x    : Tensor of type uint8.
 *    min_range  : Tensor of type float, defining the minimum scalar value possibly produced for the input.
 *           Min need lessequal 0.
 *    max_range  : Tensor of type float, defining the maximum scalar value possibly produced for the input.
 * <Output>
 *    y    : Tensor of type float.
 * <Attr>
 *    mode : Reserved.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const DEQUANTIZE_ATTR_MODE = "mode";

REG_OP(Dequantize)
.INPUT(x, TensorType({ DT_UINT8 }))
.INPUT(min_range, TensorType({ DT_FLOAT }))
.INPUT(max_range, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(mode, AttrValue::STR { "MIN_COMBINED" })
.OP_END()

/*
 * Quantizes the 'input' tensor of type float to 'output' tensor of type uint8.
 * <Input>
 *    x    : Tensor of type float.
 *    min_range  : Tensor of type float, defining the minimum scalar value possibly produced for the input.
 *           Min need lessequal 0.
 *    max_range  : Tensor of type float, defining the maximum scalar value possibly produced for the input.
 * <Output>
 *    y    : Tensor of type uint8.
 * <Attr>
 *    mode : Reserved.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const QUANTIZE_ATTR_MODE = "mode";

REG_OP(Quantize)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(min_range, TensorType({ DT_FLOAT }))
.INPUT(max_range, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.ATTR(mode, AttrValue::STR { "MIN_COMBINED" })
.OP_END()
} // namespace hiai
#pragma GCC diagnostic pop

#endif  // _HIAI_GRAPH_OP_GE_OP_ARRAY_DEFS_H