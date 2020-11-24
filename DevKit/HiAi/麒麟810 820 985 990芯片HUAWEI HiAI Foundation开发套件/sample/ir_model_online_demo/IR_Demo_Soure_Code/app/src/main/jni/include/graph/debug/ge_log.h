/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: ge_log
 */

#ifndef _GE_DEBUG_LOG_H_
#define _GE_DEBUG_LOG_H_

#include "ge_error_codes.h"
#if !defined( __ANDROID__) && !defined(ANDROID)
#include "slog.h"
#elif defined(__HIAI_TA__)
extern "C" {
#define LOG_ON
constexpr int ARM_PAE = 1;
#include "tee_log.h"
}
#else
#if !defined(HIAI_IR_ONLINE_BUILD)
#include <utils/Log.h>
#else
#include <android/log.h>
#endif
#endif

#define GE_MOD_NAME "GE"

#ifdef _MSC_VER
#define FUNC_NAME __FUNCTION__
#define __FILENAME__ (strrchr(__FILE__, '\\'))
#else
#define FUNC_NAME __PRETTY_FUNCTION__
#endif

#if defined(_MSC_VER)
#define D_GE_LOGI(MOD_NAME, fmt, ...) \
    printf("[OPTIMIZER] [I] %s %s(%d)::"#fmt"\n", __FILENAME__, __FUNCTION__, __LINE__,##__VA_ARGS__)
#define D_GE_LOGW(MOD_NAME, fmt, ...) \
    printf("[OPTIMIZER] [W] %s %s(%d)::"#fmt"\n", __FILENAME__, __FUNCTION__, __LINE__,##__VA_ARGS__)
#define D_GE_LOGE(MOD_NAME, fmt, ...) \
    printf("[OPTIMIZER] [E] %s %s(%d)::"#fmt"\n", __FILENAME__, __FUNCTION__, __LINE__,##__VA_ARGS__)
#define D_GE_LOGD(MOD_NAME, fmt, ...) \
    printf("[OPTIMIZER] [D] %s %s(%d)::"#fmt"\n", __FILENAME__, __FUNCTION__, __LINE__,##__VA_ARGS__)
#elif !defined(__ANDROID__) && !defined(ANDROID)
#define D_GE_LOGI(MOD_NAME, fmt, ...) dlog_info(FMK, "%s:%s:%d:" #fmt, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define D_GE_LOGW(MOD_NAME, fmt, ...) dlog_warn(FMK, "%s:%s:%d:" #fmt, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define D_GE_LOGE(MOD_NAME, fmt, ...) dlog_error(FMK, "%s:%s:%d:" #fmt, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define D_GE_LOGD(MOD_NAME, fmt, ...) dlog_info(FMK, "%s:%s:%d:" #fmt, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define D_GE_LOGI(MOD_NAME, fmt, ...)
#define D_GE_LOGW(MOD_NAME, fmt, ...)
#define D_GE_LOGE(MOD_NAME, fmt, ...)
#define D_GE_LOGD(MOD_NAME, fmt, ...)
#endif

// compatible g++ and msvs
#define D_GE_LOG_EXPAND(...) __VA_ARGS__

#if defined(_MSC_VER)
#define GE_LOGI(...) D_GE_LOG_EXPAND(D_GE_LOGW(GE_MOD_NAME, __VA_ARGS__))
#define GE_LOGW(...) D_GE_LOG_EXPAND(D_GE_LOGW(GE_MOD_NAME, __VA_ARGS__))
#define GE_LOGE(...) D_GE_LOG_EXPAND(D_GE_LOGE(GE_MOD_NAME, __VA_ARGS__))
#define GE_LOGD(...) D_GE_LOG_EXPAND(D_GE_LOGD(GE_MOD_NAME, __VA_ARGS__))
#elif !defined( __ANDROID__) && !defined(ANDROID)
#define GE_LOGI(...) D_GE_LOGI(GE_MOD_NAME, __VA_ARGS__)
#define GE_LOGW(...) D_GE_LOGW(GE_MOD_NAME, __VA_ARGS__)
#define GE_LOGE(...) D_GE_LOGE(GE_MOD_NAME, __VA_ARGS__)
#define GE_LOGD(...) D_GE_LOGD(GE_MOD_NAME, __VA_ARGS__)
#elif defined(__HIAI_TA__)
#define GE_LOGD(fmt, ...) \
    tee_print(LOG_LEVEL_ERROR, "%s %d: %s: %s::" #fmt, TAG_DEBUG, __LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define GE_LOGI(fmt, ...) \
    tee_print(LOG_LEVEL_ERROR, "%s %d: %s: %s::" #fmt, TAG_INFO, __LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define GE_LOGW(fmt, ...) \
    tee_print(LOG_LEVEL_ON, "%s %d: %s: %s::" #fmt, TAG_WARN, __LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define GE_LOGE(fmt, ...) \
    tee_print(LOG_LEVEL_ERROR, "%s %d: %s: %s::" #fmt, TAG_ERROR, __LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define GE_LOGI(fmt, ...)
#define GE_LOGD(fmt, ...)
#define GE_LOGW(fmt, ...)
#define GE_LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "Optimizer", "%s %s(%d)::"#fmt, __FILE__, __FUNCTION__, __LINE__,##__VA_ARGS__)
#endif

#define GE_LOGI_IF(condition, ...) do { \
    if ((condition)) { \
        GE_LOGD(__VA_ARGS__); \
    } \
} while (0)

#define GE_LOGW_IF(condition, ...) do { \
    if ((condition)) { \
        GE_LOGW(__VA_ARGS__); \
    } \
} while (0)

#define GE_LOGE_IF(condition, ...) do { \
    if ((condition)) { \
        GE_LOGE(__VA_ARGS__); \
    } \
} while (0)

#define GE_CHK_STATUS_RET_NOLOG(expr) do { \
    const ge::GraphErrCodeStatus _status = (expr); \
    if (ge::GRAPH_SUCCESS != _status) { \
        return _status; \
    } \
} while (0)

#define GE_CHK_BOOL_RET_STATUS(expr, _status, ...) do { \
    if (!(expr)) { \
        GE_LOGE(__VA_ARGS__); \
        return _status; \
    } \
} while (0)

#define GE_CHK_BOOL_EXEC_NOLOG(expr, exec_expr) do { \
    if (!(expr)) { \
        exec_expr; \
    } \
} while (0)

#define GE_IF_BOOL_EXEC(expr, exec_expr) do { \
    if (expr) { \
        exec_expr; \
    } \
} while (0);

#define GE_RETURN_WITH_LOG_IF_ERROR(expr, ...) do { \
    const ge::GraphErrCodeStatus _status = (expr); \
    if (_status) { \
        GE_LOGE(__VA_ARGS__); \
        return _status; \
    } \
} while (0)

// 如果expr为true, 则打印日志并且执行自定义的语句
#define GE_CHK_BOOL_TRUE_EXEC_WITH_LOG(expr, exec_expr, ...) do { \
    if ((expr)) { \
        GE_LOGE(__VA_ARGS__); \
        exec_expr; \
    } \
} while (0)

// only check error log
#define GE_CHK_BOOL_ONLY_LOG(expr, ...) do { \
    if (!(expr)) { \
        GE_LOGI(__VA_ARGS__); \
    } \
} while (0)

// 如果expr不为true, 不打印日志并且return指定的status
#define GE_CHK_BOOL_RET_STATUS_NOLOG(expr, _status, ...) do { \
    if (!(expr)) { \
        return _status; \
    } \
} while (0)

// 如果expr不为true, 则打印日志并且执行自定义的语句
#define GE_CHK_BOOL_EXEC(expr, exec_expr, ...) do { \
    if (!(expr)) { \
        GE_LOGE(__VA_ARGS__); \
        exec_expr; \
    } \
} while (0);

// 如果expr不为true, 则打印日志并且执行自定义的语句
#define GE_CHK_BOOL_EXEC_INFO(expr, exec_expr, ...) \
{ \
    if (!(expr)) { \
        GE_LOGD(__VA_ARGS__); \
        exec_expr; \
    } \
}

// 如果expr不为GRAPH_SUCCESS,则打印日志并且return相同的值
#define GE_CHK_STATUS_RET(expr, ...) do { \
    const ge::GraphErrCodeStatus _status = (expr); \
    if (_status != ge::GRAPH_SUCCESS) { \
        GE_LOGE(__VA_ARGS__); \
        return _status; \
    } \
} while (0)

// ------------------------cce相关宏定义---------------------------
// 如果expr不为CC_STATUS_GRAPH_SUCCESS,则打印日志并返回
#define GE_CHK_CCE_RET(expr) do { \
    ccgraphStatus_t _cc_ret = (expr); \
    if (_cc_ret != CC_STATUS_GRAPH_SUCCESS) { \
        GE_LOGE("Call cce api failed, ret: 0x%X", _cc_ret); \
        return ge::GRAPH_FAILED; \
    } \
} while (0)
#endif