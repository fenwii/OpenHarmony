/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: detection_defs
 */
#ifndef _CCE_GRAPH_OP_GE_OP_DETECTION_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_DETECTION_DEFS_H

#include "./operator_reg.h"
#include "../op/detection_defs.h"

namespace ge {
/*
 * Permutes the dimensions of the input according to a given pattern.
 * <Input>
 *    x : Input tensor, of the same type as Data.
 *    w : Deprecated, will be removed in a future version.
 * <Output>
 *    y : Has the same shape as the input, but with the dimensions re-ordered according to the specified pattern.
 * <Attr>
 *    order : Tuple of dimension indices indicating the permutation pattern, whose size >= dimensions of 'x'.
 *    For instance, x = (4, 4, 4), order = (0, 2, 1).
 * <Added in HiAI version>
 *    100.300.010.011
 */
using hiai::PERMUTE_ATTR_ORDER;

CPT_REG_OP(Permute)
.CPT_INPUT(x, TensorType ({ DT_FLOAT }))
.CPT_OPTIONAL_INPUT(w, TensorType ({ DT_FLOAT }))
.CPT_OUTPUT(y, TensorType ({ DT_FLOAT }))
.CPT_ATTR(order, AttrValue::LIST_INT { 0 })
.CPT_OP_END()
}  // namespace ge

#endif  // _CCE_GRAPH_OP_GE_OP_DETECTION_DEFS_H
