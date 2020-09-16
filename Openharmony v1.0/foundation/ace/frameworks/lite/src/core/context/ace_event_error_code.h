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

#ifndef OHOS_ACELITE_ACE_EVENT_ERROR_CODE_H
#define OHOS_ACELITE_ACE_EVENT_ERROR_CODE_H

#include "acelite_config.h"

#if defined(FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT)
#include "mc_hal_log.h"
#include "memory_heap.h"
#include "non_copyable.h"
#define ACE_EVENT_PRINT(info2, info3) \
    EventErrorCodePrint::GetInstance()->AceEventPrint(info2, info3)
#define ACE_FEATURE_EVENT_PRINT(info1, info2, info3) \
    EventErrorCodePrint::GetInstance()->AceEventPrint(info1, info2, info3)
#define ACE_ERROR_CODE_PRINT(info2, rfu) \
    EventErrorCodePrint::GetInstance()->AceErrorCodePrint(info2, rfu)
#else
#define ACE_EVENT_PRINT(info2, info3)
#define ACE_FEATURE_EVENT_PRINT(info1, info2, info3)
#define ACE_ERROR_CODE_PRINT(info2, rfu)
#endif // ENABLED(FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT)

#if defined(FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT)
namespace OHOS {
namespace ACELite {
class EventErrorCodePrint final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(EventErrorCodePrint);

    EventErrorCodePrint() = default;

    ~EventErrorCodePrint() = default;

    static EventErrorCodePrint *GetInstance();

    void AceEventPrint(MC_U8 info2, MC_U8 info3);

    void AceEventPrint(MC_U8 info1, MC_U8 info2, MC_U8 info3);

    void AceErrorCodePrint(MC_U8 info2, MC_U16 rfu);
};
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT
#endif // OHOS_ACELITE_ACE_EVENT_ERROR_CODE_H