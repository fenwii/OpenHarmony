/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: ge_error_codes
 */

#ifndef GE_ERROR_CODES_H
#define GE_ERROR_CODES_H

namespace ge {
#ifdef HOST_VISIBILITY
#define GE_FUNC_HOST_VISIBILITY __attribute__((visibility("default")))
#else
#define GE_FUNC_HOST_VISIBILITY
#endif
#ifdef DEV_VISIBILITY
#define GE_FUNC_DEV_VISIBILITY __attribute__((visibility("default")))
#else
#define GE_FUNC_DEV_VISIBILITY
#endif

using GraphErrCodeStatus = uint32_t;
const GraphErrCodeStatus GRAPH_FAILED = 0xFFFFFFFF;
const GraphErrCodeStatus GRAPH_SUCCESS = 0;
const GraphErrCodeStatus GRAPH_PARAM_INVALID = 50331649;
} // namespace ge

#endif // GE_ERROR_CODES_H
