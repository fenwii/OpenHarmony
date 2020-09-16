/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "js_profiler.h"
// invoked into compiling only if performance measurement enabled
#if ENABLED(JS_PROFILER)
#include "ace_log.h"
#include "ace_mem_base.h"
#include "js_async_work.h"
#include "js_fwk_common.h"
#include "key_parser.h"
#if defined(FEATURE_ACELITE_MC_JS_PROFILER)
#include "common/file.h"
#include "los_swtmr.h"
#elif defined(FEATURE_ACELITE_JS_PROFILER)
#include <sys/time.h>
#else
#include <time.h>
#endif // FEATURE_ACELITE_MC_JS_PROFILER
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#else // ENABLED(SECURE_C_FUNCTION)
#include <string.h>
#endif // ENABLED(SECURE_C_FUNCTION)

#include <stdlib.h>

namespace OHOS {
namespace ACELite {
/**
 * Global instance, will be initialized when the first call of JSProfiler::GetInstance().
 */

static bool g_isFirst = true;
#if defined(FEATURE_ACELITE_MC_JS_PROFILER)
static uint16_t g_profiler_msg_index = 0;
#else
static constexpr uint8_t PHASE_NAME_LENGTH = 50;
#endif

struct ProfilerPhase {
    uint8_t phaseId;
#ifndef FEATURE_ACELITE_MC_JS_PROFILER
    char phaseName[PHASE_NAME_LENGTH];
#endif
    PerformanceTag parentPhase;
};

/**
 * Use static const strings other than accepting strings from tracing apis's caller,
 * as that will need to do the string copy, which may make the cost bigger.
 * NOTE: Keep this array sync with PerformanceTag definations
 */
static const ProfilerPhase g_profilerPhaseConfig[] = {
#if defined(FEATURE_ACELITE_MC_JS_PROFILER)
    // id, parent
    {P_UNKNOWN, P_UNKNOWN},
    {LAUNCH, P_UNKNOWN},
    {ENGINE_INIT, LAUNCH},
    {FWK_INIT, LAUNCH},
    {JS_BEGIN, P_UNKNOWN},
    {JS_FWK_EVAL, PAGE_CODE_EVAL},
    {JS_APP_INIT, FWK_CODE_EVAL},
    {JS_INIT_STATE, JS_FWK_EVAL},
    {JS_INIT_DATA_GET_DATA, JS_INIT_STATE},
    {JS_INIT_DATA_PROXY, JS_INIT_STATE},
    {JS_INIT_DATA_OBSERVE, JS_INIT_STATE},
    {JS_END, P_UNKNOWN},
    {FWK_CODE_LOAD, FWK_INIT},
    {FWK_CODE_EVAL, FWK_INIT},
    {APP_CODE_LOAD, LAUNCH},
    {APP_CODE_EVAL, LAUNCH},
    {PAGE_CODE_LOAD, ROUTER_REPLACE},
    {PAGE_CODE_EVAL, ROUTER_REPLACE},
    {STYLESHEET_INIT, JS_FWK_EVAL},
    {APP_ON_CREATE, LAUNCH},
    {APP_ON_DESTROY, LAUNCH},
    {ROUTER_REPLACE, LAUNCH},
    {PAGE_TRANSFER_DATA, ROUTER_REPLACE},
    {PAGE_ON_INIT, ROUTER_REPLACE},
    {PAGE_ON_READY, ROUTER_REPLACE},
    {PAGE_ON_SHOW, ROUTER_REPLACE},
    {PAGE_ON_DESTROY, P_UNKNOWN},
    {RENDER, ROUTER_REPLACE},
    {ADD_TO_ROOT_VIEW, LAUNCH},
    {RENDER_CREATE_COMPONENT, RENDER},
    {RENDER_COMBINE_STYLE, RENDER},
    {RENDER_BIND_JS_OBJECT, RENDER},
    {RENDER_PARSE_ATTR, RENDER},
    {RENDER_PARSE_EVENT, RENDER},
    {RENDER_APPLY_STYLE, RENDER},
    {RENDER_PROCESS_CHILDREN, RENDER},
    {SET_ATTR_PARSE_EXPRESSION, RENDER_PARSE_ATTR},
    {SET_ATTR_STRING_OF, RENDER_PARSE_ATTR},
    {SET_ATTR_PARSE_KEY_ID, RENDER_PARSE_ATTR},
    {SET_ATTR_SET_TO_NATIVE, RENDER_PARSE_ATTR},
    {APPLY_STYLE_ITEM, RENDER_APPLY_STYLE},
    {WATCHER_CALLBACK_FUNC, P_UNKNOWN},
    {FOR_WATCHER_CALLBACK_FUNC, P_UNKNOWN},
    {WATCHER_CONSTRUCT, SET_ATTR_PARSE_EXPRESSION}
#else
    // id, name, parent
    {P_UNKNOWN, "UNKNOWN", P_UNKNOWN},
    {LAUNCH, "LAUNCH", P_UNKNOWN},
    {ENGINE_INIT, "ENGINE_INIT", LAUNCH},
    {FWK_INIT, "FWK_INIT", LAUNCH},
    {JS_BEGIN, "JS_BEGIN", P_UNKNOWN},                               // not used
    {JS_FWK_EVAL, "JS_FWK_EVAL", PAGE_CODE_EVAL},                    // 5
    {JS_APP_INIT, "JS_APP_INIT", FWK_CODE_EVAL},                     // 6
    {JS_INIT_STATE, "JS_INIT_STATE", JS_FWK_EVAL},                   // 7
    {JS_INIT_DATA_GET_DATA, "JS_INIT_DATA_GET_DATA", JS_INIT_STATE}, // 8
    {JS_INIT_DATA_PROXY, "JS_INIT_DATA_PROXY", JS_INIT_STATE},       // 9
    {JS_INIT_DATA_OBSERVE, "JS_INIT_DATA_OBSERVE", JS_INIT_STATE},   // 10
    {JS_END, "JS_END", P_UNKNOWN},                                   // not used
    {FWK_CODE_LOAD, "FWK_CODE_LOAD", FWK_INIT},
    {FWK_CODE_EVAL, "FWK_CODE_EVAL", FWK_INIT},
    {APP_CODE_LOAD, "APP_CODE_LOAD", LAUNCH},
    {APP_CODE_EVAL, "APP_CODE_EVAL", LAUNCH},
    {PAGE_CODE_LOAD, "PAGE_CODE_LOAD", ROUTER_REPLACE},
    {PAGE_CODE_EVAL, "PAGE_CODE_EVAL", ROUTER_REPLACE},
    {STYLESHEET_INIT, "STYLESHEET_INIT", JS_FWK_EVAL},
    {APP_ON_CREATE, "APP_ON_CREATE", LAUNCH},
    {APP_ON_DESTROY, "APP_ON_DESTROY", LAUNCH},
    {ROUTER_REPLACE, "ROUTER_REPLACE", LAUNCH},
    {PAGE_TRANSFER_DATA, "PAGE_TRANSFER_DATA", ROUTER_REPLACE},
    {PAGE_ON_INIT, "PAGE_ON_INIT", ROUTER_REPLACE},
    {PAGE_ON_READY, "PAGE_ON_READY", ROUTER_REPLACE},
    {PAGE_ON_SHOW, "PAGE_ON_SHOW", ROUTER_REPLACE},
    {PAGE_ON_DESTROY, "PAGE_ON_DESTROY", P_UNKNOWN},
    {RENDER, "RENDER", ROUTER_REPLACE},
    {ADD_TO_ROOT_VIEW, "ADD_TO_ROOT_VIEW", LAUNCH},
    {RENDER_CREATE_COMPONENT, "RENDER_CREATE_COMPONENT", RENDER},
    {RENDER_COMBINE_STYLE, "RENDER_COMBINE_STYLE", RENDER},
    {RENDER_BIND_JS_OBJECT, "RENDER_BIND_JS_OBJECT", RENDER},
    {RENDER_PARSE_ATTR, "RENDER_PARSE_ATTR", RENDER},
    {RENDER_PARSE_EVENT, "RENDER_PARSE_EVENT", RENDER},
    {RENDER_APPLY_STYLE, "RENDER_APPLY_STYLE", RENDER},
    {RENDER_PROCESS_CHILDREN, "RENDER_PROCESS_CHILDREN", RENDER},
    {SET_ATTR_PARSE_EXPRESSION, "SET_ATTR_PARSE_EXPRESSION", RENDER_PARSE_ATTR},
    {SET_ATTR_STRING_OF, "SET_ATTR_STRING_OF", RENDER_PARSE_ATTR},
    {SET_ATTR_PARSE_KEY_ID, "SET_ATTR_PARSE_KEY_ID", RENDER_PARSE_ATTR},
    {SET_ATTR_SET_TO_NATIVE, "SET_ATTR_SET_TO_NATIVE", RENDER_PARSE_ATTR},
    {APPLY_STYLE_ITEM, "APPLY_STYLE_ITEM", RENDER_APPLY_STYLE},
    {WATCHER_CALLBACK_FUNC, "WATCHER_CALLBACK_FUNC", P_UNKNOWN},
    {FOR_WATCHER_CALLBACK_FUNC, "FOR_WATCHER_CALLBACK_FUNC", P_UNKNOWN},
    {WATCHER_CONSTRUCT, "WATCHER_CONSTRUCT", SET_ATTR_PARSE_EXPRESSION}
#endif
};

#ifdef FEATURE_ACELITE_MC_JS_PROFILER
JSProfiler::JSProfiler() : data_(nullptr), dataCount_(0), traceIdSlot_(0), enabled_(false), msg_(nullptr) {}
#else
JSProfiler::JSProfiler() : data_(nullptr), dataCount_(0), traceIdSlot_(0), enabled_(false) {}
#endif

JSProfiler::~JSProfiler()
{
}

JSProfiler *JSProfiler::GetInstance()
{
    static JSProfiler profilerInstance;
    return &profilerInstance;
}

bool JSProfiler::IsEnabled()
{
    bool isEnabled = enabled_ && (data_ != nullptr);
#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    isEnabled = isEnabled && (msg_ != nullptr);
#endif
    return isEnabled;
}

void JSProfiler::PrepareDataBuffer()
{
    enabled_ = IsFileExisted(PROFILER_ENABLE_FLAG_FILE);
    if (!enabled_) {
        return;
    }
    data_ = static_cast<PerformanceData *>(ace_malloc(maxTracingDataCount * sizeof(PerformanceData)));
    if (data_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc performance data buffer failed");
        return;
    }
#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    msg_ = static_cast<ProfilerMsg *>(ace_malloc(PROFILER_MSG_LENGTH * sizeof(ProfilerMsg)));
    if (msg_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc performance data buffer failed");
        ace_free(data_);
        data_ = nullptr;
        return;
    }
#endif
    ResetData();
}

#ifdef FEATURE_ACELITE_MC_JS_PROFILER
void JSProfiler::FlushProfilerMsg(void *data)
{
    if (data == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "sync js profiler msg error");
        return;
    }

    uint32_t timestamp = JSProfiler::GetInstance()->GetCurrentClockTick();
    char fileName[TEXT_LENGTH] = {'\0'};
    if (sprintf_s(fileName, TEXT_LENGTH, "ace_profiler_%d.log", timestamp) < 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler flushmsg sprintf error");
        return;
    }

    char *fullPath = RelocateJSSourceFilePath(DEFAULT_PROFILER_MSG_PATH, fileName);
    if (fullPath == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler create error");
        return;
    }

    int32_t fd = FileOpen(fullPath, O_CREAT | O_RDWR);
    if (fd < 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler open error");
        ace_free(fullPath);
        fullPath = nullptr;
        return;
    }

    for (uint16_t i = 0; i < g_profiler_msg_index; i++) {
        if (FileWrite(fd, JSProfiler::GetInstance()->msg_[i].msg, strlen(JSProfiler::GetInstance()->msg_[i].msg)) < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "ace dump js profiler msg error");
            break;
        }
    }

    if (FileClose(fd) < 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler close error");
    }

    ace_free(fullPath);
    fullPath = nullptr;
    g_profiler_msg_index = 0;
    JSProfiler::GetInstance()->ResetData();
}
#endif

void JSProfiler::Release()
{
    ACE_FREE(data_);
#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    ACE_FREE(msg_);
#endif
}

void JSProfiler::ResetData()
{
    if (data_) {
#if ENABLED(SECURE_C_FUNCTION)
        if (memset_s(data_, (maxTracingDataCount * sizeof(PerformanceData)), 0,
            (maxTracingDataCount * sizeof(PerformanceData))) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler memset_s failed");
            return;
        }
#else
        for (uint16_t i = 0; i < maxTracingDataCount; i++) {
            data_[i].start = 0;
            data_[i].end = 0;
            data_[i].label = 0;
            data_[i].description = 0;
            data_[i].component = 0;
        }
#endif
    }

#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    if (msg_) {
        if (memset_s(msg_, (PROFILER_MSG_LENGTH * sizeof(ProfilerMsg)), 0,
            (PROFILER_MSG_LENGTH * sizeof(ProfilerMsg))) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler memset_s failed");
            return;
        }
    }
#endif
    dataCount_ = 0;
    g_isFirst = true;
}

static uint64_t g_startOffset = 0;
void JSProfiler::PushTrace(PerformanceTag tag, uint8_t name, uint8_t description)
{
    if (!IsEnabled()) {
        return;
    }

    // skip some redundant modules
    if (g_isFirst) {
        if ((tag != LAUNCH) && (tag != ROUTER_REPLACE)) {
            return;
        } else {
            g_isFirst = false;
        }
    }

    if (g_startOffset == 0) {
        g_startOffset = GetCurrentClockTick();
    }
    if (traceIdSlot_ >= maxCountAllAtOnce) {
        // the trace id is running out, can not process this tracing request util any STOP_TRACING called
        return;
    }

    if (dataCount_ >= maxTracingDataCount) {
        return;
    }

    uint16_t dataIndex = dataCount_;
    // record current time stamp
    data_[dataIndex].start = GetCurrentClockTick() - g_startOffset;
    data_[dataIndex].label = tag;
    data_[dataIndex].component = name;
    data_[dataIndex].description = description;

    // record the new trace id into stack
    traceIdStack_[traceIdSlot_] = dataIndex;
    traceIdSlot_++;
    // increase data count
    dataCount_++;
}

/**
 * @brief Calculate time cost and output to trace.
 */
void JSProfiler::PopTrace()
{
    if (!IsEnabled()) {
        return;
    }
    if ((traceIdSlot_ == 0) || (traceIdSlot_ > maxCountAllAtOnce)) {
        return;
    }
    uint16_t traceId = traceIdStack_[traceIdSlot_ - 1];
    traceIdSlot_--;
    data_[traceId].end = GetCurrentClockTick() - g_startOffset;
}

void JSProfiler::Output()
{
    if (!IsEnabled()) {
        return;
    }
    for (uint16_t dataIndex = 0; dataIndex < dataCount_; dataIndex++) {
        PerformanceData data = data_[dataIndex];
        if ((data.label > ADD_TO_ROOT_VIEW) && (data.start >= data.end)) {
            // for too many round details, we just print out bigger than 0 items to save the log IO band width
            continue;
        }
#if defined(FEATURE_ACELITE_MC_JS_PROFILER)
        if (g_profiler_msg_index == 0) {
            if ((data.label != LAUNCH) && (data.label != ROUTER_REPLACE)) {
                continue;
            }
        }

        if (g_profiler_msg_index >= PROFILER_MSG_LENGTH) {
            continue;
        }

        char buf[MSG_LENGTH] = {'\0'};
        if (sprintf_s(buf, MSG_LENGTH, "%d %d %llu %d %d\n", data.component, data.label,
            CalculateElapsedTime(data.start, data.end), data.description, data.label) < 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler memset_s msg failed");
            return;
        }
        if (strcpy_s(msg_[g_profiler_msg_index].msg, MSG_LENGTH, buf) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "ace js profiler write msg failed");
            return;
        }
        g_profiler_msg_index++;

#else
        LOG_PROFILER("COST %s %s %llu ms [%s] %s", KeyParser::GetKeyById(data.component),
                     g_profilerPhaseConfig[data.label].phaseName, CalculateElapsedTime(data.start, data.end),
                     (data.description != 0) ? KeyParser::GetKeyById(data.description) : "",
                     g_profilerPhaseConfig[g_profilerPhaseConfig[data.label].parentPhase].phaseName);
#endif
    }
#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    JsAsyncWork::DispatchAsyncWork(FlushProfilerMsg, this);
#else
    // reset all records after output to trace
    ResetData();
#endif
}

uint64_t JSProfiler::GetCurrentClockTick() const
{
#if defined(FEATURE_ACELITE_MC_JS_PROFILER)
    // real device
    return LOS_TickCountGet(); // count in clock ticks, usually is ms
#elif defined(FEATURE_ACELITE_JS_PROFILER)
    const uint32_t unit = 1000;
    // ipcamera
    timeval timeVal;
    timezone timeZone;
    return (gettimeofday(&timeVal, &timeZone) == 0) ? (timeVal.tv_usec / unit + timeVal.tv_sec * unit) : 0;
#else
    // PC simulator
    return clock(); // count in clock ticks, usually is ms
#endif
}

// convert clock tick intervals into milliseconds
uint64_t JSProfiler::CalculateElapsedTime(uint64_t start, uint64_t end) const
{
#ifndef FEATURE_ACELITE_JS_PROFILER
    const uint32_t msPerSec = 1000;
#endif
    if (start >= end) {
        return 0;
    }

    uint64_t interval = end - start;
#if defined(FEATURE_ACELITE_MC_JS_PROFILER)
    // real device
    return (interval * msPerSec) / LOSCFG_BASE_CORE_TICK_PER_SECOND;
#elif defined(FEATURE_ACELITE_JS_PROFILER)
    return interval;
#else
    // PC simulator
    return (interval * msPerSec) / CLOCKS_PER_SEC;
#endif
}
} // namespace ACELite
} // namespace OHOS
#endif // ENABLED(JS_PROFILER)
