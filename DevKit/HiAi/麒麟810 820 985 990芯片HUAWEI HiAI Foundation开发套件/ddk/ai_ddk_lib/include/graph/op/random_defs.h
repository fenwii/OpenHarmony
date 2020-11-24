/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: random_defs
 */

#ifndef _HIAI_GRAPH_OP_GE_OP_RANDOM_DEFS_H
#define _HIAI_GRAPH_OP_GE_OP_RANDOM_DEFS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "../operator_hiai_reg.h"

namespace hiai {
/*
 * Outputs random values from a uniform distribution.
 * <Input>
 *    shape : 1-D const, shape of the output tensor. Only a 1D-4D tensor can be generated.
 *    minval : 0-D const, lower bound on the range of random values to generate.
 *    maxval : 0-D const, upper bound on the range of random values to generate.
 * <Output>
 *    y : Result tensor of the same element shape as 'shape'.
 * <Added in HiAI version>
 *    100.310.010.013
 */
REG_OP(RandomUniformNoSeed)
.INPUT(shape, TensorType ({ DT_INT32 }))
.INPUT(minval, TensorType ({ DT_FLOAT }))
.INPUT(maxval, TensorType ({ DT_FLOAT }))
.OUTPUT(y, TensorType ({ DT_FLOAT }))
.OP_END()

/*
 * generate random values from a normal distributions.
 * <Input>
 *    shape : 1-D const, shape of the output tensor. Only a 1D-4D tensor can be generated.
 *    mean  : 0-D const. The mean of the normal distribution.
 *    stddev : 0-D const. The standard deviation of the normal distribution.
 * <Output>
 *    y : Result tensor of the same element shape as 'shape'.
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(RandomNormalNoSeed)
.INPUT(shape, TensorType ({ DT_INT32 }))
.INPUT(mean, TensorType ({ DT_FLOAT }))
.INPUT(stddev, TensorType ({ DT_FLOAT }))
.OUTPUT(y, TensorType ({ DT_FLOAT }))
.OP_END()

/*
 * Randomly shuffles a tensor along its first dimension
 * <Input>
 *    x : A tensor.
 * <Output>
 *    y : A tensor
 * <Added in HiAI version>
 *    100.320.010.010
 */
REG_OP(RandomShuffleNoSeed)
.INPUT(x, TensorType({ DT_UINT8, DT_FLOAT, DT_BOOL, DT_INT32 }))
.OUTPUT(y, TensorType({ DT_UINT8, DT_FLOAT, DT_BOOL, DT_INT32 }))
.OP_END()

/*
 * Extract samples from multiple distributions.
 * <Input>
 *    x : Input tensor, only support 2-D.
 *    num_samples :  0-D, number of independent samples to draw for each row slice. If the datatype of size is
 * DT_FOLAT, the elements must be >= 1.
 * <Output>
 *    y : Output tensor
 * <Attr>
 *    seed  : If either 'seed' or 'seed2' is set to non-zero, the internal random number generator is seeded by
 * the given seed. Otherwise, a random seed is used.
 *    seed2 : Second seed to avoid seed collision
 * <Added in HiAI version>
 *    100.310.010.013
 */

const char* const MULTNOMIAL_ATTR_SEED = "seed";
const char* const MULTNOMIAL_ATTR_SEED2 = "seed2";

REG_OP(Multinomial)
.INPUT(x, TensorType({ DT_FLOAT }))
.INPUT(num_samples, TensorType({ DT_INT32,DT_FLOAT, DT_UINT8 }))
.OUTPUT(y, TensorType({ DT_INT32 }))
.ATTR(seed, AttrValue::INT { 0 })
.ATTR(seed2, AttrValue::INT { 0 })
.OP_END()

} // namespace hiai

#pragma GCC diagnostic pop
#endif // _HIAI_GRAPH_OP_GE_OP_RANDOM_DEFS_H