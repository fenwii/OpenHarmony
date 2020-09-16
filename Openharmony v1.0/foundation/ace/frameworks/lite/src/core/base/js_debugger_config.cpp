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
#include "js_debugger_config.h"
#include <cstring>
#include "ace_log.h"
#include "debugger.h"
#include "handler.h"
#include "jerryscript-port-default.h"
#include "jerryscript-port.h"
#include "js_fwk_common.h"

namespace OHOS {
namespace ACELite {
#if ENABLED(ENGINE_DEBUGGER)
bool Debugger::IsDebuggerEnabled()
{
    return debuggerConfig_.startDebuggerServer;
}

void Debugger::ConfigEngineDebugger(DebuggerConfig &config)
{
    if (memcpy_s(&debuggerConfig_, sizeof(DebuggerConfig), &config, sizeof(DebuggerConfig)) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "ConfigEngineDebugger memcpy_s failed!");
        return;
    }
    ConfigDebugger();
}

void Debugger::StartDebugger()
{
    if ((!debuggerConfig_.startDebuggerServer) || !(jerry_is_feature_enabled(JERRY_FEATURE_DEBUGGER))) {
        return;
    }

    if (debuggerStarted_) {
        // already started, avoid creating tcp repeat
        return;
    }
    // increase jerry log level to see the Waiting for client connection message
    jerry_port_default_set_log_level(JERRY_LOG_LEVEL_DEBUG);
    // currently, only support tcp::websocket
    HILOG_INFO(HILOG_MODULE_ACE, "please connect to debugger server with localhost:%d", debuggerConfig_.port);
    bool protocol = jerryx_debugger_tcp_create(debuggerConfig_.port);
    bool connected = jerryx_debugger_ws_create();
    jerryx_debugger_after_connect(protocol && connected);
    debuggerStarted_ = true;
}
void Debugger::TearDownDebugger()
{
    if (consoleLogFileHandler_ != nullptr) {
        fclose(consoleLogFileHandler_);
        consoleLogFileHandler_ = nullptr;
    }
    if ((!debuggerConfig_.startDebuggerServer) || !(jerry_is_feature_enabled(JERRY_FEATURE_DEBUGGER))) {
        return;
    }
    // no need to check debuggerStarted_ flag, as the lower interface is reenterable
    jerry_debugger_stop();
    debuggerStarted_ = false;
}

void Debugger::ConfigDebugger()
{
    if (consoleLogFileHandler_ != nullptr) {
        fclose(consoleLogFileHandler_);
        consoleLogFileHandler_ = nullptr;
    }

    if ((debuggerConfig_.logToFile)) {
        if ((debuggerConfig_.logFilePath != nullptr) && (strlen(debuggerConfig_.logFilePath) > 0)) {
            consoleLogFileHandler_ = fopen(debuggerConfig_.logFilePath, "w+");
            if (consoleLogFileHandler_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "can not open the console log output file");
            }
        }
    }
}

void Debugger::Output(const char * const str)
{
    // if debugger enabled, get config from debugger config
    if (consoleLogFileHandler_ != nullptr) {
        int res = fputs(str, consoleLogFileHandler_);
        if (res == EOF) {
            // write file error
            HILOG_ERROR(HILOG_MODULE_ACE, "write log file failed");
        }
    }
    // print out the log into stdout anyway
    printf("%s", str);
}
void Debugger::FlushOutput()
{
    if (consoleLogFileHandler_ != nullptr) {
        fflush(consoleLogFileHandler_);
    }
    fflush(stdout);
}

#ifdef JS_ENGINE_EXTERNAL_CONTEXT
static void *AllocEngineContext(size_t size, void *cbDataP)
{
    (void)(cbDataP);
    return ace_malloc(size);
}
#endif // JS_ENGINE_EXTERNAL_CONTEXT

void Debugger::SetupJSContext()
{
#ifdef JS_ENGINE_EXTERNAL_CONTEXT
    if (engineContext_ != nullptr) {
        // do not repeat the setup process
        return;
    }
    uint32_t heapSize = debuggerConfig_.heapSize;
    if (heapSize == 0) {
        // default is 48KB
        const uint32_t DEFAULT_HEAP_SIZE = 48 * 1024;
        heapSize = DEFAULT_HEAP_SIZE;
    }
    engineContext_ = jerry_create_context(heapSize, AllocEngineContext, nullptr);
    if (engineContext_ == nullptr) {
        return;
    }
    jerry_port_default_set_current_context(static_cast<jerry_context_t *>(engineContext_));
#endif // JS_ENGINE_EXTERNAL_CONTEXT
}

void Debugger::ReleaseJSContext()
{
#ifdef JS_ENGINE_EXTERNAL_CONTEXT
    if (engineContext_ == nullptr) {
        return;
    }
    ace_free(engineContext_);
    engineContext_ = nullptr;
#endif // JS_ENGINE_EXTERNAL_CONTEXT
}
#else // ENABLED(ENGINE_DEBUGGER)
bool Debugger::IsDebuggerEnabled()
{
    return true;
}
void Debugger::ConfigEngineDebugger(DebuggerConfig &config)
{
    UNUSED(config);
}
void Debugger::StartDebugger()
{
}
void Debugger::TearDownDebugger()
{
}
void Debugger::ConfigDebugger()
{
}
void Debugger::Output(const char * const str)
{
    UNUSED(str);
}
void Debugger::FlushOutput()
{
}
void Debugger::SetupJSContext()
{
}
void Debugger::ReleaseJSContext()
{
}
#endif // ENABLED(ENGINE_DEBUGGER)
} // namespace ACELite
} // namespace OHOS
