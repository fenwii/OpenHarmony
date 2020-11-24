/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: image_defs
 */

#ifndef _HIAI_GRAPH_OP_GE_OP_IMAGE_DEFS_H
#define _HIAI_GRAPH_OP_GE_OP_IMAGE_DEFS_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "../operator_hiai_reg.h"

namespace hiai {

/*
 * Image data tensor.
 * <Input>
 *    x : the input tensor.
 * <Output>
 *   y : the output tensor
 * <Attr>
 *    input_format : input_format of original image, accepted format is in the range of
 *    [YUV420SP_U8, YUV422SP_U8, AYUV444_U8, YUYV_U8, YUV400_U8, RGB888_U8, XRGB8888_U8, ARGB8888_U8]
 *    src_image_size_w : original image size width
 *    src_image_size_h : original image size height
 *    image_type: accepted type is in the range of [JPEG, BT_601_NARROW, BT_601_FULL, BT_709_NARROW], default as JPEG
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGEDATA_ATTR_INPUT_FORMAT = "input_format";
const char* const IMAGEDATA_ATTR_SRC_IMAGE_SIZE_W = "src_image_size_w";
const char* const IMAGEDATA_ATTR_SRC_IMAGE_SIZE_H = "src_image_size_h";
const char* const IMAGEDATA_ATTR_IMAGE_TYPE = "image_type";

REG_OP(ImageData)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.REQUIRED_ATTR(input_format, AttrValue::STR)
.REQUIRED_ATTR(src_image_size_w, AttrValue::INT)
.REQUIRED_ATTR(src_image_size_h, AttrValue::INT)
.ATTR(image_type, AttrValue::STR { "JPEG" })
.OP_END()

/*
 * Dynamic image data tensor.
 * <Input>
 *    x : the input tensor.
 * <Output>
 *    y : the output tensor
 * <Attr>
 *    max_src_image_size : max src image size
 *    image_type: accepted type is in the range of [JPEG, BT_601_NARROW, BT_601_FULL, BT_709_NARROW], default as JPEG
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const DYNAMICIMAGEDATA_ATTR_MAX_SRC_IMAGE_SIZE = "max_src_image_size";
const char* const DYNAMICIMAGEDATA_ATTR_IMAGE_TYPE = "image_type";

REG_OP(DynamicImageData)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.REQUIRED_ATTR(max_src_image_size, AttrValue::INT)
.ATTR(image_type, AttrValue::STR { "JPEG" })
.OP_END()

/*
 * Extract crop from the input image tensor.
 * <Input>
 *    x : the input tensor.
 * <Output>
 * <Attr>
 *    load_start_pos_h : Y-axis of top left corner
 *    load_start_pos_w : X-axis of top left corner
 *    crop_size_h : height
 *    crop_size_w : width
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGECROP_ATTR_LOAD_START_POS_H = "load_start_pos_h";
const char* const IMAGECROP_ATTR_LOAD_START_POS_W = "load_start_pos_w";
const char* const IMAGECROP_ATTR_CROP_SIZE_H = "crop_size_h";
const char* const IMAGECROP_ATTR_CROP_SIZE_W = "crop_size_w";

REG_OP(ImageCrop)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.ATTR(load_start_pos_h, AttrValue::INT { 0 })
.ATTR(load_start_pos_w, AttrValue::INT { 0 })
.REQUIRED_ATTR(crop_size_h, AttrValue::INT)
.REQUIRED_ATTR(crop_size_w, AttrValue::INT)
.OP_END()

/*
 * Change image channel before Color Space Convertion
 * <Input>
 *    x : the input tensor.
 * <Output>
 *    y : the output tensor
 * <Attr>
 *    rbuv_swap_switch : whether to change the channel of R&B or U&V
 *    ax_swap_switch : whether to change GBA to ARGB or YUVA to AYUV
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGECHANNELSWAP_ATTR_RBUV_SWAP_SWITCH = "rbuv_swap_switch";
const char* const IMAGECHANNELSWAP_ATTR_AX_SWAP_SWITCH = "ax_swap_switch";

REG_OP(ImageChannelSwap)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.ATTR(rbuv_swap_switch, AttrValue::BOOL { false })
.ATTR(ax_swap_switch, AttrValue::BOOL { false })
.OP_END()

/*
 * YUV2RGB is color space conversion, it convert YUV444 to RGB888. The conversion expression is following:
 * RGB2YUV is also color space conversion, it convert RGB888 to YUV444. The conversion expression is following:
 * Set target_format, CSC_MATRIX and CSC_BIAS will be configured by system according to input_format,
 * image_type and target_format
 * <Input>
 *    x : the input tensor.
 * <Output>
 *    y : the output tensor
 * <Attr>
 *    target_format : target_format after color space conversion, accepted format is in the range of
 *    [YVU444SP_U8, YUV444SP_U8, RGB888_U8, BGR888_U8, YUV400_U8]
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGECOLORSPACECONVERTION_ATTR_TARGET_FORMAT = "target_format";

REG_OP(ImageColorSpaceConvertion)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.REQUIRED_ATTR(target_format, AttrValue::STR)
.OP_END()

/*
 * Resize the input image tensor, It use bilinear or nearest neighbor algorithm to support scale up and down
 * <Input>
 *    x : the input tensor.
 * <Output>
 *    y : the output tensor
 * <Attr>
 *    resize_output_h : height after resize
 *    resize_output_w : width after resize
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGERESIZE_ATTR_RESIZE_OUTPUT_H = "resize_output_h";
const char* const IMAGERESIZE_ATTR_RESIZE_OUTPUT_W = "resize_output_w";

REG_OP(ImageResize)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8 }))
.REQUIRED_ATTR(resize_output_h, AttrValue::INT)
.REQUIRED_ATTR(resize_output_w, AttrValue::INT)
.OP_END()

/*
 * AI core support feature map data type are: int8 and fp16. But image RGB888 or YUV444 data are all uint8 data type.
 * So we need data type conversion.
 * uint8->int8: pixel_out_chx(i) = pixel_in_chx(i) - mean_chn_i
 * uint8->fp16: pixel_out_chx(i) = (pixel_in_chx(i) - mean_chn_i - min_chn_i) * var_reci_chn
 * <Input>
 *    x : the input tensor.
 * <Output>
 *    mean_chn_0 : mean_chn_0
 *    mean_chn_1 : mean_chn_1
 *    mean_chn_2 : mean_chn_2
 *    mean_chn_3 : mean_chn_3
 *    min_chn_0 : min_chn_0
 *    min_chn_1 : min_chn_1
 *    min_chn_2 : min_chn_2
 *    min_chn_3 : min_chn_3
 *    var_reci_chn_0 : var_reci_chn_0
 *    var_reci_chn_1 : var_reci_chn_1
 *    var_reci_chn_2 : var_reci_chn_2
 *    var_reci_chn_3 : var_reci_chn_3
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGEDATATYPECONVERSION_ATTR_MEAN_CHN_0 = "mean_chn_0";
const char* const IMAGEDATATYPECONVERSION_ATTR_MEAN_CHN_1 = "mean_chn_1";
const char* const IMAGEDATATYPECONVERSION_ATTR_MEAN_CHN_2 = "mean_chn_2";
const char* const IMAGEDATATYPECONVERSION_ATTR_MEAN_CHN_3 = "mean_chn_3";
const char* const IMAGEDATATYPECONVERSION_ATTR_MIN_CHN_0 = "min_chn_0";
const char* const IMAGEDATATYPECONVERSION_ATTR_MIN_CHN_1 = "min_chn_1";
const char* const IMAGEDATATYPECONVERSION_ATTR_MIN_CHN_2 = "min_chn_2";
const char* const IMAGEDATATYPECONVERSION_ATTR_MIN_CHN_3 = "min_chn_3";
const char* const IMAGEDATATYPECONVERSION_ATTR_VAR_RECI_CHN_0 = "var_reci_chn_0";
const char* const IMAGEDATATYPECONVERSION_ATTR_VAR_RECI_CHN_1 = "var_reci_chn_1";
const char* const IMAGEDATATYPECONVERSION_ATTR_VAR_RECI_CHN_2 = "var_reci_chn_2";
const char* const IMAGEDATATYPECONVERSION_ATTR_VAR_RECI_CHN_3 = "var_reci_chn_3";

REG_OP(ImageDataTypeConversion)
.INPUT(x, TensorType({ DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_UINT8, DT_INT8, DT_FLOAT }))
.ATTR(mean_chn_0, AttrValue::INT { 0 })
.ATTR(mean_chn_1, AttrValue::INT { 0 })
.ATTR(mean_chn_2, AttrValue::INT { 0 })
.ATTR(mean_chn_3, AttrValue::INT { 0 })
.ATTR(min_chn_0, AttrValue::FLOAT { 0 })
.ATTR(min_chn_1, AttrValue::FLOAT { 0 })
.ATTR(min_chn_2, AttrValue::FLOAT { 0 })
.ATTR(min_chn_3, AttrValue::FLOAT { 0 })
.ATTR(var_reci_chn_0, AttrValue::FLOAT { 1.0 })
.ATTR(var_reci_chn_1, AttrValue::FLOAT { 1.0 })
.ATTR(var_reci_chn_2, AttrValue::FLOAT { 1.0 })
.ATTR(var_reci_chn_3, AttrValue::FLOAT { 1.0 })
.OP_END()

/*
 * Add padding to input image tensor
 * <Input>
 *    x : the input tensor.
 * <Output>
 * <Attr>
 *    left_padding_size : left_padding_size
 *    right_padding_size : right_padding_size
 *    top_padding_size : top_padding_size
 *    bottom_padding_size : bottom_padding_size
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const IMAGEPADDING_ATTR_LEFT_PADDING_SIZE = "left_padding_size";
const char* const IMAGEPADDING_ATTR_RIGHT_PADDING_SIZE = "right_padding_size";
const char* const IMAGEPADDING_ATTR_TOP_PADDING_SIZE = "top_padding_size";
const char* const IMAGEPADDING_ATTR_BOTTOM_PADDING_SIZE = "bottom_padding_size";

REG_OP(ImagePadding)
.INPUT(x, TensorType({ DT_UINT8, DT_INT8, DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_UINT8, DT_INT8, DT_FLOAT }))
.ATTR(left_padding_size, AttrValue::INT { 0 })
.ATTR(right_padding_size, AttrValue::INT { 0 })
.ATTR(top_padding_size, AttrValue::INT { 0 })
.ATTR(bottom_padding_size, AttrValue::INT { 0 })
.OP_END()

/*
 * Extracts crops from the input image tensor and resizes them.
 * <Input>
 *    x : 4-D tensor
 *    boxes : 2-D tensor
 *    box_index : 1-D tensor. The value of box_index[i] specifies the image that the i-th box refers to.
 *    crop_size : weight and height.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    extrapolation_value : Value for extrapolation, default 0.
 *    method : Sampling method for resizing either bilinear or nearest. Defaults to bilinear.
 * <Added in HiAI version>
 *    100.310.010.013
 */

const char* const CROPANDRESIZE_ATTR_EXTRAPOLATION_VALUE= "extrapolation_value";
const char* const CROPANDRESIZE_ATTR_METHOD= "method";

REG_OP(CropAndResize)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(boxes, TensorType({ DT_FLOAT }))
.INPUT(box_index, TensorType({ DT_INT32 }))
.INPUT(crop_size, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(extrapolation_value, AttrValue::FLOAT { 0 })
.ATTR(method, AttrValue::STR { "bilinear" })
.OP_END()

/*
 * Resizes images to 'size' using bilinear interpolation.
 * <Input>
 *    x : 4-D tensor
 *    size : 1-D tensor with shape [height, width], must be const op.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    align_corners : If true, the centers of the 4 corner pixels of the input and output tensors
 * are aligned, preserving the values at the corner pixels.
 * <Added in HiAI version>
 *    100.310.010.013
 */
const char* const RESIZE_BILINEAR_ATTR_ALIGN_CORNERS = "align_corners";

REG_OP(ResizeBilinear)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(size, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(align_corners, AttrValue::BOOL { false })
.OP_END()

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
 *      100.320.010.010
 */
REG_OP(ResizeBilinearV2)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(size, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(align_corners, AttrValue::BOOL { false })
.ATTR(half_pixel_centers, AttrValue::BOOL { false })
.OP_END()


/*
 * Resizes images to 'size' using nearest neighbor interpolation.
 * <Input>
 *    x : 4-D with shape [batch, height, width, channels].
 *    size  : 1-D of two elements
 * <Output>
 *    y     : Output tensor
 * <Attr>
 *    align_corners : If true, the centers of the 4 corner pixels of the input and output tensors are aligned,
 *                    preserving the values at the corner pixels. Defaults to false
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(ResizeNearestNeighbor)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(size, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(align_corners, AttrValue::BOOL { false })
.OP_END()

/*
 * The operator is used to adjust the shape according to the stride_h and stride_w.
 * <Input>
 *    x : The input tensor of 4-D.
 * <Output>
 *    y : The output tensor of 4-D.
 * <Attr>
 *    stride_h : Dimension-h amplification factor, must be greater than 0.
 *    stride_w : Dimension-w amplification factor, must be greater than 0.
 *    scale : Reserved attribute, not need to enter.
 * <Added in HiAI version>
 *    100.320.010.010
 */

const char* const UPSAMPLE_ATTR_STRIDE_H = "stride_h";
const char* const UPSAMPLE_ATTR_STRIDE_W = "stride_w";
const char* const UPSAMPLE_ATTR_SCALE = "scale";

REG_OP(Upsample)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(stride_h, AttrValue::INT { 1 })
.ATTR(stride_w, AttrValue::INT { 1 })
.ATTR(scale, AttrValue::FLOAT { 1.0 })
.OP_END()

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
REG_OP(Interp)
.INPUT(x, TensorType({DT_FLOAT}))
.OUTPUT(y, TensorType({DT_FLOAT}))
.ATTR(height, AttrValue::INT{0})
.ATTR(width, AttrValue::INT{0})
.ATTR(shrink_factor, AttrValue::INT{1})
.ATTR(zoom_factor, AttrValue::INT{1})
.ATTR(pad_begin, AttrValue::INT{0})
.ATTR(pad_end, AttrValue::INT{0})
.OP_END()

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
const char* const CROP_ATTR_NAME_OFFSETS = "offsets";
const char* const CROP_ATTR_NAME_AXIS = "axis";

REG_OP(Crop)
.INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.INPUT(size, TensorType({ DT_INT32 }))
.OUTPUT(y, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8, DT_BOOL }))
.ATTR(axis, AttrValue::INT{ 2 })
.REQUIRED_ATTR(offsets, AttrValue::LIST_INT)
.OP_END()

/*
 * Performs non-maximum suppression (NMS) on the boxes according to their intersection-over-union (IoU).
 * NMS iteratively removes lower scoring boxes which have an IoU greater than iou_threshold
 * with another (higher scoring) box.
 * <Input>
 *    boxes : Non const op, should be 2-D tensor, dim[0] of boxes should be equal to dim[0] of scores,
 *          dim[1] of boxes should be 4.
 *    scores : Non const op, should be 1-D tensor, dim[0] of scores should be equal to dim[0] of boxes.
 * <Output>
 *    y : A 1-D integer tensor with the shape-value less than or equal to max_output_size.
 * <Attr>
 *    max_output_size: Meaning the maximum number of boxes to be selected by non max suppression.
 *    iou_threshold: Meaning the threshold for deciding whether boxes overlap too much with respect to IOU.
 *    score_threshold: The threshold for deciding when to remove boxes based on score.
 * <Added in HiAI version>
 *    100.320.010.010
 */
const char* const NONMAXSUPPRESSION_ATTR_IOU_THRESHOLD = "iou_threshold";
const char* const NONMAXSUPPRESSION_ATTR_SCORE_THRESHOLD = "score_threshold";
const char* const NONMAXSUPPRESSION_ATTR_MAX_OUTPUT_SIZE = "max_output_size";

REG_OP(NonMaxSuppressionV3D)
.INPUT(boxes, TensorType({ DT_FLOAT }))
.INPUT(scores, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_INT32 }))
.REQUIRED_ATTR(max_output_size, AttrValue::INT)
.REQUIRED_ATTR(iou_threshold, AttrValue::FLOAT)
.REQUIRED_ATTR(score_threshold, AttrValue::FLOAT)
.OP_END()
}  // namespace hiai
#pragma GCC diagnostic pop
#endif  // _HIAI_GRAPH_OP_GE_OP_IMAGE_DEFS_H
