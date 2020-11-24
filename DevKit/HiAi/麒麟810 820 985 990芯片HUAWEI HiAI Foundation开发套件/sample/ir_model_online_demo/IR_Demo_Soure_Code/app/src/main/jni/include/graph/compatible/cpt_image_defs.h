/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: image_defs
 */

#ifndef _CCE_GRAPH_OP_GE_OP_IMAGE_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_IMAGE_DEFS_H

#include "./operator_reg.h"
#include "../op/image_defs.h"

namespace ge {
/*
 * Extracts crops from the input image tensor and resizes them.
 * <Input>
 *    x : 4-D tensor
 *    boxes : 2-D tensor
 *    box_index : 1-D tensor. The value of box_index[i] specifies the image that the i-th box refers to.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    method : Sampling method for resizing either 0 (bilinear) or 1 (nearest). Defaults to 0 (bilinear).
 *    extrapolation_value : Dimensions to reduce
 *    crop_size_h : Height
 *    crop_size_w : Width
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(CropAndResize)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(boxes, TensorType({ DT_FLOAT }))
.CPT_INPUT(box_index, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(method, AttrValue::INT { 0 })
.CPT_ATTR(extrapolation_value, AttrValue::FLOAT { 0 })
.CPT_ATTR(crop_size_h, AttrValue::INT { 0 })
.CPT_ATTR(crop_size_w, AttrValue::INT { 0 })
.CPT_OP_END()

/*
 * Resizes images to 'size' using bilinear interpolation.
 * <Input>
 *    x : 4-D tensor
 *    size : 1-D tensor with shape [height, width]
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    align_corners : If true, the centers of the 4 corner pixels of the input and output tensors
 * are aligned, preserving the values at the corner pixels.
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::RESIZE_BILINEAR_ATTR_ALIGN_CORNERS;

CPT_REG_OP(ResizeBilinear)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(size, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(align_corners, AttrValue::BOOL { false })
.CPT_OP_END()

/*
 * Resizes images to 'size' using bilinear interpolation.
 * <Input>
 *      x : 4-D tensor
 *      size : 1-D tensor with shape [height, width]
 * <Output>
 *      y : Output tensor
 * <Attr>
 *      align_corners : If true, the centers of the 4 corner pixels of the input and output tensors
 * are aligned, preserving the values at the corner pixels.
  * <Attr>
 *      half_pixel_centers : If true, the align_corners must be false. and this attr change the mapping way
 * to src image, default value is false.
 * <Added in HiAI version>
 *      100.320.010.xxx
 */
CPT_REG_OP(ResizeBilinearExt2)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(size, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(align_corners, AttrValue::BOOL { false })
.CPT_ATTR(half_pixel_centers, AttrValue::BOOL { false })
.CPT_OP_END()


/*
 * Resizes images to 'size' using nearest neighbor interpolation.
 * <Input>
 *    image : 4-D with shape [batch, height, width, channels].
 *    size  : 1-D of two elements
 * <Output>
 *    y     : Output tensor
 * <Attr>
 *    align_corners : If true, the centers of the 4 corner pixels of the input and output tensors are aligned,
 * preserving the values at the corner pixels. Defaults to false
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(ResizeNearestNeighbor)
.CPT_INPUT(image, TensorType({ DT_FLOAT }))
.CPT_INPUT(size, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(align_corners, AttrValue::BOOL { false })
.CPT_OP_END()

/*
 * Interpolation operation to adjust image shape.
 * <Input>
 *    x : 4-D tensor with shape [batch, depth, height, width], and must be non const op.
 * <Output>
 *    y : the output tensor of 4-D.
 * <Attr>
 *    height : height of output, must be greater than 0.
 *    width : width of output, must be greater than 0.
 *    shrink_factor : shrink factor, must be greater than 0.
 *    zoom_factor : zoom factor, must be greater than 0.
 *    pad_begin : padding at begin of input, must be less than or equal to 0.
 *    pad_end : padding at end of input, must be less than or equal to 0.
 * <Added in HiAI version>
 *    100.320.010.010
 */
CPT_REG_OP(Interp)
.CPT_INPUT(x, TensorType({DT_FLOAT}))
.CPT_OUTPUT(y, TensorType({DT_FLOAT}))
.CPT_ATTR(height, AttrValue::INT{0})
.CPT_ATTR(width, AttrValue::INT{0})
.CPT_ATTR(shrink_factor, AttrValue::INT{1})
.CPT_ATTR(zoom_factor, AttrValue::INT{1})
.CPT_ATTR(pad_begin, AttrValue::INT{0})
.CPT_ATTR(pad_end, AttrValue::INT{0})
.CPT_OP_END()

/* To crop ,elements of the first input are selected to fit the dimensions of the second input.
 * <Input>
 *    x : The tensor to be croped.
 *    size : The size of the input x to be croped.
 * <Output>
 *    y : The output tensor.
 * <Attr>
 *    axis : The Dimension of input which to be croped.
 *    offsets : The offsets of input x.
 * <Added in HiAI version>
 *    100.320.010.010
 */
using hiai::CROP_ATTR_NAME_OFFSETS;
using hiai::CROP_ATTR_NAME_AXIS;

CPT_REG_OP(Crop)
.CPT_INPUT(x, TensorType({DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL}))
.CPT_INPUT(size, TensorType({DT_FLOAT, DT_INT32}))
.CPT_OUTPUT(y, TensorType({DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL}))
.CPT_ATTR(axis, AttrValue::INT{2})
.CPT_REQUIRED_ATTR(offsets, AttrValue::LIST_INT)
.CPT_OP_END()
}  // namespace ge

#endif  // _CCE_GRAPH_OP_GE_OP_IMAGE_DEFS_H
