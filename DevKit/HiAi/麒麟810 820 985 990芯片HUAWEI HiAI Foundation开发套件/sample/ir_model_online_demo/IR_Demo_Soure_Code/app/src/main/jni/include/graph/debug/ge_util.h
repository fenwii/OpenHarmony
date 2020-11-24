/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: ge_util
 */

#ifndef _GE_COMMON_UTIL_H_
#define _GE_COMMON_UTIL_H_

#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <cmath>
#include "ge_log.h"
#include "ge_error_codes.h"

#if !defined(__ANDROID__) && !defined(ANDROID)
#define GE_DYNAMIC_CAST dynamic_cast
#define GE_DYNAMIC_POINTER_CAST std::dynamic_pointer_cast
#else
#define GE_DYNAMIC_CAST static_cast
#define GE_DYNAMIC_POINTER_CAST std::static_pointer_cast
#endif

#if defined(HIAI_IR_ONLINE_BUILD)
inline std::string ToString(int idx)
{
    std::stringstream stream;
    stream << idx;
    return stream.str();
}
#endif

#define GE_RETURN_IF_ERROR(expr) do { \
    const ::ge::OptStatus _status = (expr); \
    if (_status) { \
        return _status; \
    } \
} while (0)

#define GE_RETURN_WITH_LOG_IF_INFO(expr, ...) do { \
    const ::ge::OptStatus _status = (expr); \
    if (_status) { \
        GE_LOGI(__VA_ARGS__); \
        return _status; \
    } \
} while (0)

// 校验参数是否为true. 如果是，返回 GRAPH_FAILED，并记录error日志
#define GE_RETURN_WITH_LOG_IF_TRUE(condition, ...) do { \
    if (condition) { \
        GE_LOGE(__VA_ARGS__); \
        return ge::GRAPH_FAILED; \
    } \
} while (0)

// 校验参数是否为false. 如果是，返回 GRAPH_FAILED，并记录error日志
#define GE_RETURN_WITH_LOG_IF_FALSE(condition, ...) do { \
    bool _condition = (condition); \
    if (!_condition) { \
        GE_LOGE(__VA_ARGS__); \
        return ge::GRAPH_FAILED; \
    } \
} while (0)

// 校验参数是否为true. 如果是，返回 GRAPH_PARAM_INVALID，并记录error日志
#define GE_RT_PARAM_INVALID_WITH_LOG_IF_TRUE(condition, ...) do { \
    if (condition) { \
        GE_LOGE(__VA_ARGS__); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验参数是否为false. 如果是，返回 GRAPH_PARAM_INVALID，并记录error日志
#define GE_RT_PARAM_INVALID_WITH_LOG_IF_FALSE(condition, ...) do { \
    bool _condition = (condition); \
    if (!_condition) { \
        GE_LOGE(__VA_ARGS__); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验参数是否为null. 如果是，返回 GRAPH_PARAM_INVALID， 并记录error日志
#define GE_CHECK_NOTNULL(val) do { \
    if (val == nullptr) { \
        GE_LOGE(param[#val] must not be null.); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验参数是否为null. 如果是，返回 GRAPH_PARAM_INVALID， 并记录error日志
#define GE_CHECK_NOTNULL_EXEC(val, expr) do { \
    if (val == nullptr) { \
        GE_LOGE(param[#val] must not be null.); \
        expr; \
    } \
} while (0)

// 校验参数是否为null. 如果是，返回false， 并记录error日志
#define GE_RT_FALSE_CHECK_NOTNULL(val) do { \
    if (val == nullptr) { \
        GE_LOGE(param[#val] must not be null.); \
        return false; \
    } \
} while (0)

// 校验参数是否越界
#define GE_CHECK_SIZE(size) do { \
    if (size == 0) { \
        GE_LOGE(param[#size] is out of range); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

/*
 * @ingroup GE_common
 * @brief 定义size变量的宏
 * 使用举例：
 * GE_DEFINE_BYTE_SIZE(filter_byte, filter.data().size(), sizeof(float));
 */
#define GE_DEFINE_BYTE_SIZE(_var_name, _expr, _sizeof) do { \
    uint32_t _var_name; \
    uint32_t _expr_size = (_expr); \
    uint32_t _sizeof_size = (_sizeof); \
    if (_expr_size > (0xffffffff) / _sizeof_size) { \
        GE_LOGE(byte size : #_var_name is out of range); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
    _var_name = _sizeof_size * _expr_size; \
} while (0);

// 校验容器是否为空,
#define GE_CHECK_VECTOR_NOT_EMPTY(vector) do { \
    if (vector.empty()) { \
        GE_LOGE(param[#vector] is empty !); \
        return ge::GRAPH_FAILED; \
    } \
} while (0)

// 校验容器是否为空,返回指定状态码
#define GE_CHECK_VECTOR_NOT_EMPTY_RET_STATUS(vector, _status) do { \
    if (vector.empty()) { \
        GE_LOGE(param[#vector] is empty !); \
        return _status; \
    } \
} while (0)

/*
 * @ingroup GE_common
 * @brief 该宏提供禁止拷贝构造函数和赋值操作符能力，一般放在private 下面
 */
#define GE_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete; \
    void operator = (const TypeName &) = delete

/*
 * 校验size是否为0或者越界
 * @param：size：待校验的size
 */
#define GE_CHECK_SIZE_RANGE(size) do { \
    if (size == 0 || size >= UINT_MAX / 4) { \
        GE_LOGE(param[#size] is out of range); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

#define GE_CHECK_SHORT_SIZE_RANGE(size) do { \
    if (size == 0 || size >= UINT_MAX / 2) { \
        GE_LOGE(param[#size] is out of range); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

#define GE_CHECK_POSITIVE_SIZE_RANGE(size) do { \
    if (size <= 0) { \
        GE_LOGE(param[#size] is not a positive number); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

#define GE_CHECK_POSITIVE_SHORT_SIZE_RANGE(size) do { \
    if (size <= 0 || size == 0 || size >= UINT_MAX / 4) { \
        GE_LOGE(param[#size] is out of range); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验左边的值是否大于等于右边的值
#define GE_CHECK_GE(lhs, rhs) do { \
    if (lhs < rhs) { \
        GE_LOGE(param[#lhs] is less than[#rhs]); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验参数是否相等
#define GE_CHECK_EQ(val1, val2) do { \
    if (val1 != val2) { \
        GE_LOGE(param[#val1] is not equals to[#val2]); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验左边的值是否小于等于右边的值
#define GE_CHECK_LE(lhs, rhs) do { \
    if (lhs > rhs) { \
        GE_LOGE(param[#lhs] is greater than[#rhs]); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 校验参数是否相等
#define GE_CHECK_EQ_WITH_LOG(val1, val2, ...) do { \
    if (val1 != val2) { \
        GE_LOGE(__VA_ARGS__); \
        return ge::GRAPH_PARAM_INVALID; \
    } \
} while (0)

// 如果expr为false, 则执行自定义的语句
#ifdef CHECK_FALSE_EXEC
#undef CHECK_FALSE_EXEC
#endif
#define CHECK_FALSE_EXEC(expr, exec_expr, ...) do { \
    bool b = (expr); \
    if (!b) { \
        exec_expr; \
    } \
} while (0);

#define GE_DELETE_NEW_SINGLE(var) do { \
    if (nullptr != var) { \
        delete var; \
        var = nullptr; \
    } \
} while (0); \
;

#define GE_DELETE_NEW_ARRAY(var) do { \
    if (nullptr != var) { \
        delete[] var; \
        var = nullptr; \
    } \
} while (0); \
;
#endif