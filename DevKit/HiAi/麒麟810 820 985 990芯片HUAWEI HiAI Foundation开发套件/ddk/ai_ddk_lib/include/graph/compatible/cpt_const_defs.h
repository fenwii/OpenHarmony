/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: const_defs
 */

#ifndef _CCE_GRAPH_OP_GE_OP_CONST_DEFS_H
#define _CCE_GRAPH_OP_GE_OP_CONST_DEFS_H

#include "./operator_reg.h"

namespace ge {
/*
 * Constant tensor
 * <Output>
 *    y : Output tensor containing the same value of the provided tensor
 * <Attr>
 *    value : Value for the elements of the output tensor
 * <Added in HiAI version>
 *    100.300.010.011
 */
CPT_REG_OP(Const)
.CPT_OUTPUT(y, TensorType({ DT_FLOAT, DT_INT8, DT_INT32, DT_BOOL }))
.CPT_ATTR(value, AttrValue::TENSOR(new (std::nothrow) Tensor(TensorDesc())))
.CPT_OP_END()
} // namespace ge

#endif // _CCE_GRAPH_OP_GE_OP_CONST_DEFS_H
