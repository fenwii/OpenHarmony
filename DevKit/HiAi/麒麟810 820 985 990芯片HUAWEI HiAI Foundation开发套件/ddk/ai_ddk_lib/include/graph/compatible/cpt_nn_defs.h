/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: nn_defs
 */

#ifndef _CCE_GRAPH_OP_GE_OP_NN_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_NN_DEFS_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "./operator_reg.h"
#include "../op/nn_defs.h"

namespace ge {
/*
 * The Activation op provide different types of nonlinearities for use in neural networks.
 * These include smooth nonlinearities (sigmoid, tanh, and softplus), continuous but not everywhere
 * differentiable functions (ReLU), and random regularization.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor with the same type as the input tensor
 * <Attr>
 *    mode  : Activation mode, with options as follows:
 *           0 : Sigmoid
 *           1 : ReLU
 *           2 : Tanh
 *           3 : Clipped ReLU
 *           4 : ELU
 *           5 : PReLU
 *           6 : Abs
 *           7 : Relu1
 *           8 : Softsign
 *           9 : Softplus
 *           10 : Hardsigmoid
 *           11 : Threshold ReLU
 *           12 : Selu
 *           13 : Linear
 *           14 : Relu6
 *           15 : GeLU.
 *           Defaults to 1 (ReLU). 1.
 *    coef  : Upper limit value in the clipped RELU, alpha value in the ELU and theta value in the
 * Threshold ReLU. It is not used in the original RELU. Use its default value 0.0.
 *    negative_slope : Angle of the negative slope for PReLU, if negative_slope is a very small
 * fixed value(for example, negative_slope = 0.01), then PReLU degenerates to Leaky_Relu.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::ACTIVATION_ATTR_MODE;
using hiai::ACTIVATION_ATTR_COEF;
using hiai::ATTR_NAME_NEGATIVE_SLOPE;

CPT_REG_OP(Activation)
.CPT_INPUT(x, TensorType({ DT_INT8, DT_INT32, DT_FLOAT, DT_BOOL, DT_INT64 }))
.CPT_OUTPUT(y, TensorType({ DT_INT8, DT_INT32, DT_FLOAT, DT_BOOL, DT_INT64 }))
.CPT_ATTR(mode, AttrValue::INT { 1 })
.CPT_ATTR(coef, AttrValue::FLOAT { 0.0 })
.CPT_ATTR(negative_slope, AttrValue::FLOAT { 0.0 })
.CPT_OP_END()

/*
 * Normalizes the input to have 0-mean and/or unit (1) variance across the batch (batch normalization).
 * <Input>
 *    x       : Input tensor
 *    scale   : Tensor for scaling factor, to scale the normalized 'x'
 *    b       : Tensor for bias, to shift to the normalized 'x'
 *    mean    : Tensor for population mean. Used for inference only.
 *    variance: Tensor for population variance. Used for inference only.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    momentum   : Momentum for the running mean and running variance
 *                 running_mean is equal to  [ running_mean * momentum + mean * (1 - momentum)].
 *    epsilon    : Small float number added to the variance of 'x'
 *    mode       : BatchNorm mode. 0: The bnScale and bnBias tensors are of size 1xCxHxW.
 *     1: The bnScale and bnBias tensors are of size 1xCx1x1.
 *    use_global_stats : Must be true.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::BATCHNORM_ATTR_MODE;
using hiai::BATCHNORM_ATTR_USE_GLOBAL_STATS;
using hiai::BATCHNORM_ATTR_EPSILON;

CPT_REG_OP(BatchNorm)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(scale, TensorType ({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(b, TensorType ({ DT_FLOAT }))
.CPT_INPUT(mean, TensorType ({ DT_FLOAT }))
.CPT_INPUT(variance, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(momentum, AttrValue::FLOAT { 0.9f })
.CPT_ATTR(epsilon, AttrValue::FLOAT { 1e-5f })
.CPT_ATTR(mode, AttrValue::INT { 1 })
.CPT_ATTR(use_global_stats, AttrValue::BOOL { true })
.CPT_OP_END()

/*
 * Normalizes the input to have 0-mean and/or unit (1) variance across the batch (batch normalization).
 * <Input>
 *    x       : Input tensor
 *    scale   : Tensor for scaling factor, to scale the normalized 'x'
 *    offset  : Tensor for bias, to shift to the normalized 'x'
 *    mean    : Tensor for population mean. Used for inference only.
 *    variance: Tensor for population variance. Used for inference only.
 * <Output>
 *    y        : Output tensor
 * <Attr>
 *    momentum  : Momentum for the running mean and running variance
 *                running_mean is equal to  [running_mean * momentum + mean * (1 - momentum)].
 *    epsilon   : Small float number added to the variance of 'x'
 *    mode      : BatchNorm mode, 0: The bnScale and bnBias tensors are of size 1xCxHxW.
 *        1: The bnScale and bnBias tensors are of size 1xCx1x1.
 *    use_global_stats : Must be true.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(BatchNormExt2)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_INPUT(scale, TensorType ({ DT_FLOAT }))
.CPT_INPUT(offset, TensorType ({ DT_FLOAT }))
.CPT_INPUT(mean, TensorType ({ DT_FLOAT }))
.CPT_INPUT(variance, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(momentum, AttrValue::FLOAT { 0.9f })
.CPT_ATTR(epsilon, AttrValue::FLOAT { 1e-5f })
.CPT_ATTR(mode, AttrValue::INT { 1 })
.CPT_ATTR(use_global_stats, AttrValue::BOOL { true })
.CPT_OP_END()

/*
 * Consumes an input tensor and a filter, and computes the output.
 * <Input>
 *    x : Input tensor of size NCHW.
 *    w : With shape [out_channels, in_channels/group, k_h, k_w], must be a Const-OP.
 *    b : With shape [out_channels], must be a Const-OP.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    mode       : Convolution mode. Only 1 (cross-correlation convolution) is supported.
 *                 Even if a different value is specified, 1 applies.
 *    group      : Number of groups input channels and output channels are divided into.
 *                 When group = 1, traditional convolution will be performed;
 *                 When group > 1, feature maps are grouped by group_count, and then each group
 *                 is convoluted separately. Specially, 'group' equal to the number of input feature
 *                 maps indicates Depthwise Convolution.
 *    num_output : Number of output tensors. Must be nonnegative.
 *    pad        : Padding for the beginning and ending along each axis [hh, ht, wh, wt].
 *                 Take effect when the specified 'pad_mode' is 0: NOTSET.
 *    stride     : Stride along each axis.
 *    dilation   : Dilation value along each axis of the filter.
 *    kernel     : (Optional) dimensions h and w of input 'w', used for verification.
 *    pad_mode   : Pad mode, either 0 (NOTSET), 5 (VALID), or 6 (SAME). Default to 0 (NOTSET).
 *                 5 (VALID) or 6 (SAME) means no padding.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::CONV_ATTR_NAME_PAD_MODE;
using hiai::CONV_ATTR_NAME_PAD;
using hiai::CONV_ATTR_NAME_STRIDE;
using hiai::CONV_ATTR_NAME_DILATION;
using hiai::CONV_ATTR_NAME_GROUP;
const char* const CONV_ATTR_NAME_MODE = "mode";
const char* const CONV_ATTR_NAME_NUM_OUTPUT = "num_output";
const char* const CONV_ATTR_NAME_KERNEL = "kernel";

CPT_REG_OP(Convolution)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_INPUT(w, TensorType({ DT_FLOAT, DT_INT8 }))
.CPT_OPTIONAL_INPUT(b, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(mode, AttrValue::INT { 1 })
.CPT_ATTR(group, AttrValue::INT { 1 })
.CPT_ATTR(num_output, AttrValue::INT { 0 })
.CPT_ATTR(pad, AttrValue::LIST_INT({ 0, 0,  0, 0 }))
.CPT_ATTR(stride, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(dilation, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(kernel, AttrValue::LIST_INT({ 0, 0 }))
.CPT_ATTR(pad_mode, AttrValue::INT { 0 })
.CPT_OP_END()

/*
 * Consumes an input tensor and a filter, and computes the output.
 * <Input>
 *    x : Input tensor.
 *    filter : With shape [out_channels, in_channels/group, k_h, k_w], must be a Const-OP.
 *             If QuantType = 1, shall use type 'tensor(int8)'.
 *    bias   : With shape [out_channels], must be a const OP.
 *             If QuantType = 1, shall use type 'tensor(int32)'.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    group      : Number of groups input channels and output channels are divided into. When group = 1,
 *                 traditional convolution will be performed;
 *                 When group > 1, feature maps are grouped by group_count,
 *                 and then each group is convoluted separately.
 *                 Specially, 'group' equal to the number of input feature maps indicates Depthwise Convolution.
 *    num_output : Number of output tensors. Must be nonnegative.
 *    pad        : Padding for the beginning and ending along each axis [hh, ht, wh, wt].
 *                 Take effect when the specified 'pad_mode' is 0: NOTSET.
 *    stride     : Stride along each axis.
 *    dilation   : Dilation value along each axis of the filter.
 *    kernel     : (Optional) dimensions h and w of input 'w', used for verification
 *    pad_mode   : Pad mode, either 0 (NOTSET), 5 (VALID), or 6 (SAME). Default to 0 (NOTSET).
 *                 5 (VALID) or 6 (SAME) means no padding.
 *    format     : Format of the input and output data.
 *                 With the default format 0 (NCHW), the data is stored in order of [batch, channels, height, width].
 *                 Alternatively, the format could be 1 (NHWC), the data is stored in order of [batch, height, width,
 *                 channels].
 *    x_quant_type        : Either 0-No quant or 1-Quant8 (linear); Reserved: 2-Quant4 (linear), 3-Quant2 (linear)
 *    filter_quant_type   : Either 0-No quant or 1-Quant8 (linear); Reserved: 2-Quant4 (linear), 3-Quant2 (linear)
 *    x_quant_scale       : If x_quant_type > 0, this Attr is required.
 *    x_quant_offset      : Data offset
 *    filter_quant_scales : List of scale factors of the filter. If filter_quant_type > 0, this Attr is required.
 * <Added in HiAI version>
 *    100.310.010.015
 */
CPT_REG_OP(QuantizedConvolution)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_INPUT(filter, TensorType({ DT_FLOAT, DT_INT8 }))
.CPT_OPTIONAL_INPUT(bias, TensorType ({ DT_FLOAT, DT_INT32 }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(group, AttrValue::INT { 1 })
.CPT_ATTR(num_output, AttrValue::INT { 0 })
.CPT_ATTR(pad, AttrValue::LIST_INT({ 0, 0,  0, 0 }))
.CPT_ATTR(stride, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(dilation, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(kernel, AttrValue::LIST_INT({ 0, 0 }))
.CPT_ATTR(pad_mode, AttrValue::INT { 0 })
.CPT_ATTR(format, AttrValue::INT { 0 })
.CPT_ATTR(x_quant_type, AttrValue::INT { 0 })
.CPT_ATTR(filter_quant_type, AttrValue::INT { 0 })
.CPT_ATTR(x_quant_scale, AttrValue::FLOAT { 1.0 })
.CPT_ATTR(x_quant_offset, AttrValue::INT { 0 })
.CPT_ATTR(filter_quant_scales, AttrValue::LIST_FLOAT({}))
.CPT_OP_END()

/*
 * Computes the gradients of convolution with respect to the input.
 * <Input>
 *    input_sizes : Integer vector representing the shape of input, where input is a 4-D [batch, height,
 * width, channels] tensor
 *    filter      : Filter tensor, with shape [H , W, filter_channel, filter_number], with filter_channel
 * equal to the channel of 'x'
 *    bias  : 1D tensor, must be a const OP.
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    format: Format of the input and output data
 *            With the default format 0 (NCHW), the data is stored in order of [batch, channels, height, width].
 *            Alternatively, the format could be 1 (NHWC), the data is stored in order of [batch, height,
 * width, channels].
 *    group : 1 (default), can support 1 ~ 1000 currently.
 *    num_output : 0 (default). num_output = (filter_channel * group)
 *    pad        : Padding for the beginning and ending along each axis [hh, ht, wh, wt]. Take effect
 * when the specified 'pad_mode' is 0: NOTSET
 *    stride     : Stride along each axis.
 *    dilation   : Dilation value along each axis of the filter.
 *    pad_mode   : Pad mode, either 0 (NOTSET), 5 (VALID), or 6 (SAME). Defaults to 0 (NOTSET).
 *                5 (VALID) or 6 (SAME) means no padding.
 *    bias_term  : 0 (default)
 *    kernel     : Shape of the convolution kernel
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(Deconvolution)
.CPT_INPUT(input_sizes, TensorType({ DT_UINT8 }))
.CPT_INPUT(filter, TensorType({ DT_FLOAT }))
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(bias, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(format, AttrValue::INT { 0 })
.CPT_ATTR(group, AttrValue::INT { 1 })
.CPT_ATTR(num_output, AttrValue::INT { 0 })
.CPT_ATTR(pad, AttrValue::LIST_INT ({  0, 0, 0, 0  }))
.CPT_ATTR(stride, AttrValue::LIST_INT ({  1, 1  }))
.CPT_ATTR(dilation, AttrValue::LIST_INT ({  1, 1  }))
.CPT_ATTR(pad_mode, AttrValue::INT { 0 })
.CPT_ATTR(bias_term, AttrValue::INT { 0 })
.CPT_ATTR(kernel, AttrValue::LIST_INT ({ 0, 0 }))
.CPT_OP_END()

/*
 * Adds bias to 'x'.
 * <Input>
 *    x    : Input tensor of any number of dimensions
 *    bias : 1D tensor of size equal to the C dimension of 'x'
 * <Output>
 *    y: Broadcast sum of 'x' and 'bias'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(BiasAdd)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(bias, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Adds all input tensors element-wise.
 * <Input>
 *    x1 : Input tensor, with same size and shape as 'x2'
 *    x2 : Input tensor, with same size and shape as 'x1'
 * <Output>
 *    y : Output tensor, with the same element type as the two inputs
 * <Attr>
 *   mode  : Either 0 (product), 1 (sum), or 2 (max). Defaults to 1 (sum).
 *   coeff : input_num = coeff
 *   weight: Deprecated, will be removed in a future version.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::ELTWISE_ATTR_MODE;
using hiai::ELTWISE_ATTR_COEFF;

CPT_REG_OP(Eltwise)
.CPT_INPUT(x1, TensorType({ DT_FLOAT, DT_BOOL }))
.CPT_INPUT(x2, TensorType({ DT_FLOAT, DT_BOOL }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_BOOL }))
.CPT_ATTR(mode, AttrValue::INT { 1 })
.CPT_ATTR(coeff, AttrValue::LIST_FLOAT({ 1, 1 }))
.CPT_ATTR(weight, AttrValue::LIST_TENSOR {})
.CPT_OP_END()

/*
 * Means Local Response Normalization.
 * <Input>
 *    x : Input tensor
 *    w : Dynamic input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    lrn_localsize: Number of channels to sum over
 *    lrn_alpha    : Scale factor, usually positive
 *    lrn_beta     : Exponent
 *    lrn_k        : Offset (usually positive to avoid dividing by 0)
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(LRN)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_DYNAMIC_INPUT(w, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(lrn_localsize, AttrValue::INT { 5 })
.CPT_ATTR(lrn_alpha, AttrValue::FLOAT { 1.0 })
.CPT_ATTR(lrn_beta, AttrValue::FLOAT { 0.5 })
.CPT_ATTR(lrn_k, AttrValue::FLOAT { 1.0 })
.CPT_OP_END()

/*
 * Computes a depthwise convolution from given input and filter tensors.
 * <Input>
 *    x     : Input tensor
 *    filter: With shape [in_channels, 1, k_h, k_w], must be a Const-OP.
 *    bias  : With shape [in_channels], must be a const OP.
 * <Output>
 *    y     : Has in_channels * channel_multiplier channels.
 * <Attr>
 *    num_output : Number of output tensors. Must be nonnegative.
 *    group      : Number of groups input channels and output channels are divided into.
 *                 In DepthwiseConvolution, 'group' must be equal to the input channel size.
 *    pad_mode   : Pad mode, either 5 (VALID) or 6 (SAME).
 *    mode       : Convolution mode. Only 1 (cross-correlation convolution) is supported.
 *                 Even if a different value is specified, 1 applies.
 *    algo       : Algorithm type, either 0 (matrix GEMM algorithm), 1 (Winograd transform algorithm ),
 *                 or 2 (accumulation in L0c with FP32)
 *    pad        : Padding for the beginning and ending along each axis [hh, ht, wh, wt].
 *                 Take effect when the specified 'pad_mode' is 0: NOTSET.
 *    stride     : Stride of the sliding window for each dimension of input
 *    dilation   : Dilation value along each spatial axis of the filter
 *    kernel     : Shape of the convolution kernel
 *    format     : Format of the input and output data
 *                 With the default format 0 (NCHW), the data is stored in order of [batch, channels,
 *                 height, width].
 *                 Alternatively, the format could be 1 (NHWC), the data is stored in order of [batch,
 *                 height, width, channels].
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(ConvolutionDepthwise)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(filter, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(bias, TensorType({ DT_FLOAT }))
.CPT_ATTR(num_output, AttrValue::INT{0})
.CPT_ATTR(group, AttrValue::INT{1})
.CPT_ATTR(pad_mode, AttrValue::INT{6})
.CPT_ATTR(mode, AttrValue::INT{1})
.CPT_ATTR(algo, AttrValue::INT{0})
.CPT_ATTR(pad, AttrValue::LIST_INT({ 0, 0, 0, 0}))
.CPT_ATTR(stride, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(dilation, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(kernel, AttrValue::LIST_INT{})
.CPT_ATTR(format, AttrValue::INT{0})
.CPT_OP_END()

/*
 * Computes a depthwise convolution from given input and filter tensors.
 * <Input>
 *    x     : Input tensor
 *    filter: With shape [in_channels, 1, k_h, k_w], must be a Const-OP.
 *            If QuantType = 1, shall use type 'tensor(int8)'.
 *    bias  : With shape [in_channels], must be a const OP.
 *            If QuantType = 1, shall use type 'tensor(int32)'.
 * <Output>
 *    y     : Has in_channels * channel_multiplier channels.
 * <Attr>
 *    num_output    : Number of output tensors. Must be nonnegative. This Attr is reserved.
 *    group         : Number of groups input channels and output channels are divided into. This Attr is reserved.
 *    pad_mode      : Pad mode, either 5 (VALID) or 6 (SAME).
 *    algo          : Algorithm type, either 0 (matrix GEMM algorithm), 1 (Winograd transform algorithm ),
 *                    or 2 (accumulation in FP32). Only 0 (matrix GEMM algorithm) is supported now.
 *    pad           : Padding for the beginning and ending along each axis [hh , ht, wh, wt].
 *    stride        : Stride of the sliding window for each dimension of input.
 *    dilation      : Dilation value along each spatial axis of the filter.
 *    kernel        : Shape of the convolution kernel. This Attr is reserved.
 *    format        : Format of the input and output data
 *                    With the default format 0 (NCHW), the data is stored in order of [batch,
 *                    channels, height, width].
 *                    Alternatively, the format could be 1 (NHWC), the data is stored in order of [batch,
 *                    height, width, channels].
 *    x_quant_type        : Either 0-No quant or 1-Quant8 (linear); Reserved: 2-Quant4 (linear), 3-Quant2 (linear)
 *    filter_quant_type   : Either 0-No quant or 1-Quant8 (linear); Reserved: 2-Quant4 (linear), 3-Quant2 (linear)
 *    x_quant_scale       : If x_quant_type > 0, this Attr is required.
 *    x_quant_offset      : Data offset
 *    filter_quant_scales : If filter_quant_type > 0, this Attr is required. The number of WeightQuantScales
 *                          must be 1 or n of [n,c,h,w] of 'Weights'.
 * <Added in HiAI version>
 *    100.310.010.015
 */
CPT_REG_OP(QuantizedConvolutionDepthwise)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(filter, TensorType({ DT_FLOAT, DT_INT8}))
.CPT_OPTIONAL_INPUT(bias, TensorType({ DT_FLOAT,  DT_INT32 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(num_output, AttrValue::INT{0})
.CPT_ATTR(group, AttrValue::INT{1})
.CPT_ATTR(pad_mode, AttrValue::INT{6})
.CPT_ATTR(algo, AttrValue::INT{0})
.CPT_ATTR(pad, AttrValue::LIST_INT({ 0, 0, 0, 0}))
.CPT_ATTR(stride, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(dilation, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(kernel, AttrValue::LIST_INT{})
.CPT_ATTR(format, AttrValue::INT{0})
.CPT_ATTR(x_quant_type, AttrValue::INT { 0 })
.CPT_ATTR(filter_quant_type, AttrValue::INT { 0 })
.CPT_ATTR(x_quant_scale, AttrValue::FLOAT { 1.0 })
.CPT_ATTR(x_quant_offset, AttrValue::INT { 0 })
.CPT_ATTR(filter_quant_scales, AttrValue::LIST_FLOAT({}))
.CPT_OP_END()

/*
 * Computes an inner product with an input tensor, a set of learned weights and adds biases.
 * <Input>
 *    x : Input tensor
 *    w : Weight tensor
 *    b : 1D tensor for bias.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    num_output : Number of neurons output after full connection
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::FULL_CONNECTION_ATTR_NUM_OUTPUT;

CPT_REG_OP(FullConnection)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(w, TensorType({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(b, TensorType({ DT_FLOAT, DT_INT32}))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(num_output, AttrValue::INT { 0 })
.CPT_OP_END()

/*
 * Computes an inner product with an input tensor, a set of learned weights and adds biases.
 * <Input>
 *    x      : Input tensor
 *    filter : Weight tensor. If QuantType = 1, shall use type 'tensor(int8)'.
 *    bias   : Tensor for bias. Optional 1D bias to be added to the convolution, has size of M.
 * If QuantType = 1, shall use type 'tensor(int32)'.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    num_output          : Number of neurons output after full connection
 *    x_quant_type        : Either 0-No quant or 1-Quant8 (linear); Reserved: 2-Quant4 (linear), 3-Quant2 (linear)
 *    filter_quant_type   : Either 0-No quant or 1-Quant8 (linear); Reserved: 2-Quant4 (linear), 3-Quant2 (linear)
 *    x_quant_scale       : If x_quant_type > 0, this Attr is required.
 *    x_quant_offset      : Data offset
 *    filter_quant_scales : If filter_quant_type > 0, this Attr is required. The number of WeightQuantScales
 * must be 1 or n of [n,c,h,w] of 'Weights'.
 * <Added in HiAI version>
 *    100.310.010.015
 */
CPT_REG_OP(QuantizedFullConnection)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(filter, TensorType({ DT_FLOAT, DT_INT8 }))
.CPT_OPTIONAL_INPUT(bias, TensorType({ DT_FLOAT, DT_INT32}))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(num_output, AttrValue::INT { 0 })
.CPT_ATTR(x_quant_type, AttrValue::INT { 0 })
.CPT_ATTR(filter_quant_type, AttrValue::INT { 0 })
.CPT_ATTR(x_quant_scale, AttrValue::FLOAT { 1.0 })
.CPT_ATTR(x_quant_offset, AttrValue::INT { 0 })
.CPT_ATTR(filter_quant_scales, AttrValue::LIST_FLOAT({}))
.CPT_OP_END()

/*
 * Pools the input tensors by taking the max, average, etc. within regions.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    mode           : Either 0 max pooling), 1 (avg pooling), or 2 (L2 pooling)
 *    pad_mode       : Pad mode, either 0 (NOTSET), 6 (SAME), or 5 (VALID). Defaults to 0 (NOTSET).
 *    global_pooling : Defaults to false.
 *    window         : Window size, specifying the height and width of each filter. Here the size must be 2
 * and value >= 1.
 *    pad            : Pad size, specifying the number of pixels to (implicitly) add to each side of the input.
 * Here the size must be 4 and value >= 0.
 *    stride         : Stride size, specifying the intervals at which to apply the filters to the input.
 * Here the size must be 2 and value >= 1.
 *    ceil_mode      : Pooling ceil mode, either 0 (POOLING_CEIL: The smallest integer greater than argument),
 *                    or 1 (POOLING_FLOOR: The largest integer not greater than the argument)
 *    data_mode      : Data mode, either 0 (rounded up) or 1 (rounded down)
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::POOLING_ATTR_MODE;
using hiai::POOLING_ATTR_PAD_MODE;
using hiai::POOLING_ATTR_GLOBAL_POOLING;
using hiai::POOLING_ATTR_WINDOW;
using hiai::POOLING_ATTR_PAD;
using hiai::POOLING_ATTR_STRIDE;
using hiai::POOLING_ATTR_CEIL_MODE;
using hiai::POOLING_ATTR_DATA_MODE;

CPT_REG_OP(Pooling)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT }))
.CPT_ATTR(mode, AttrValue::INT { 0 })
.CPT_ATTR(pad_mode, AttrValue::INT { 0 })
.CPT_ATTR(global_pooling, AttrValue::BOOL { false })
.CPT_ATTR(window, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(pad, AttrValue::LIST_INT({ 0, 0,  0,0 }))
.CPT_ATTR(stride, AttrValue::LIST_INT({ 1, 1 }))
.CPT_ATTR(ceil_mode, AttrValue::INT { 0 })
.CPT_ATTR(data_mode, AttrValue::INT { 1 })
.CPT_OP_END()

/*
 * Computes the element-wise product of input tensors, with the shape of the filter 'broadcast' to match
 * the shape of 'x': y = x * filter + bias.
 * <Input>
 *    x : Input tensor
 *    filter : Must be a const OP.
 *    bias : Must be a const OP.
 * <Output>
 *    y      : Output tensor, with the same shape as 'x'
 * <Attr>
 *    axis           : Axis of input tensor along which to apply other tensors (filter or bias). Defaults to 1.
 *                     This Attr is reserved.
 *    bias_term      : Whether to have bias terms. Defaults to false. This Attr is reserved.
 *    has_bias_value : If the input bias is set, the attr value must be set true.
 *                     If the input bias is not set, the attr value must be set false.
 *    filler_type    : If set to 'constant', filler_value will be used when filter not be set
 *                     If not set to 'constant', filler_value will not be used and filter must be input.
 *    filler_value   : filler_value is used as the filter when filler_type is set to 'constant'.
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(Scale)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(filter, TensorType ({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(bias, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(axis, AttrValue::INT { 1 })
.CPT_ATTR(bias_term, AttrValue::BOOL { false })
.CPT_ATTR(has_bias_value, AttrValue::BOOL { false })
.CPT_ATTR(filler_type, AttrValue::STR { "constant" })
.CPT_ATTR(filler_value, AttrValue::FLOAT { 1.0 })
.CPT_OP_END()

/*
 * Randomly shuffles channels followed by a group convolutional layer, usually utilized for ShuffleNet CNN
 * architecture.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Tensor of same shape and type as 'x', shuffled according to 'group'
 * <Attr>
 *    group : Number of groups that input channels and output channels are divided into. Must be positive.
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::SHUFFLE_CHANNEL_GROUP;

CPT_REG_OP(ShuffleChannel)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT8 }))
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT8 }))
.CPT_ATTR(group, AttrValue::INT { 1 })
.CPT_OP_END()

/*
 * Computes the softmax (normalized exponential) values for each layer in the batch of the given input.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output values, with the same shape as the input tensor
 * <Attr>
 *    axis : Dimension softmax would be performed on
 *    algo : Must be 1, indicating subtracting max from every point to avoid overflow
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::SOFTMAX_ATTR_AXIS;
const char* const SOFTMAX_ATTR_ALGO = "algo";

CPT_REG_OP(Softmax)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(axis, AttrValue::INT { 0 })
.CPT_ATTR(algo, AttrValue::INT { 1 })
.CPT_OP_END()

/*
 * Calculate values and indices of the k largest entries of the last dimension and output.
 * <Input>
 *    x : 1-D or higher Tensor with last dimension at least k
 *    k: Const OP. Number of top elements to look for along the last dimension
 * <Output>
 *    y1 : k largest elements along each last dimensional slice
 *    y2 : indices of values within the last dimension of input
 * <Attr>
 *    sorted : If true, the resulting k elements will be sorted by the values in descending order.
 *    format : Data format, either 0 (NCHW) or 1 (NHWC)
 * <Added in HiAI version>
 *    100.310.010.013
 */
using hiai::TOPKV2_ATTR_K;

CPT_REG_OP(TopK)
.CPT_INPUT(x, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_INPUT(k, TensorType({ DT_INT32 }))
.CPT_OUTPUT(y1, TensorType({ DT_FLOAT, DT_INT32, DT_UINT8 }))
.CPT_OUTPUT(y2, TensorType({ DT_INT32 }))
.CPT_ATTR(sorted, AttrValue::BOOL { false })
.CPT_ATTR(format, AttrValue::INT { 1 })
.CPT_OP_END()

/*
 * Computes the LogSoftmax (normalized exponential) values for each layer in the batch of the given input.
 * <Input>
 *    x : Input tensor
 * <Output>
 *    y : Output values, with the same shape as the input tensor
 * <Attr>
 *    axis : Dimension LogSoftmax would be performed on
 *    algo : Reserved. Defaults to 2. Even a different value is specified, 2 applies.
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(LogSoftmax)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(axis, AttrValue::INT { -1 })
.CPT_ATTR(algo, AttrValue::INT { 2 })
.CPT_OP_END()
}  // namespace ge
#pragma GCC diagnostic pop
#endif  // _CCE_GRAPH_OP_GE_OP_NN_DEFS_H
