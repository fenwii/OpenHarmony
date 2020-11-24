/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: random_defs
 */

#ifndef _CCE_GRAPH_OP_GE_OP_RANDOM_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_RANDOM_DEFS_H

#include "./operator_reg.h"

namespace ge {
/*
 * Outputs random values from a uniform distribution.
 * <Input>
 *    shape : 1-D tensor, shape of the output tensor. Only a 1D-4D tensor can be generated.
 *    minval : 0-D const, lower bound on the range of random values to generate
 *    maxval : 0-D const, upper bound on the range of random values to generate
 * <Output>
 *    y : Result tensor of the same element type as 'shape'
 * <Added in HiAI version>
 *    100.310.010.013
 */
CPT_REG_OP(RandomUniform)
.CPT_INPUT(shape, TensorType ({ DT_INT32 }))
.CPT_INPUT(minval, TensorType ({ DT_FLOAT }))
.CPT_INPUT(maxval, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_OP_END()

/*
 * Extract samples from multiple distributions.
 * <Input>
 *    x : Input tensor
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
CPT_REG_OP(Multinomial)
.CPT_INPUT(x, TensorType({ DT_FLOAT }))
.CPT_INPUT(num_samples, TensorType({ DT_INT32,DT_FLOAT, DT_UINT8 }))
.CPT_OUTPUT(y, TensorType({ DT_INT32 }))
.CPT_ATTR(seed, AttrValue::INT { 0 })
.CPT_ATTR(seed2, AttrValue::INT { 0 })
.CPT_OP_END()
} // namespace ge

#endif // _CCE_GRAPH_OP_GE_OP_RANDOM_DEFS_H
