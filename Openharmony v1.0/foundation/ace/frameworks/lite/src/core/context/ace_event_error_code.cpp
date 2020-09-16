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


#include "ace_event_error_code.h"
#ifdef FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT
namespace OHOS {
namespace ACELite {
EventErrorCodePrint *EventErrorCodePrint::GetInstance()
{
    static EventErrorCodePrint printInstance;
    return &printInstance;
}

void EventErrorCodePrint::AceEventPrint(MC_U8 info2, MC_U8 info3)
{
    EventPrintf(MT_ACE, MT_ACE_FWK, info2, info3);
}

void EventErrorCodePrint::AceEventPrint(MC_U8 info1, MC_U8 info2, MC_U8 info3)
{
    EventPrintf(MT_ACE, info1, info2, info3);
}

void EventErrorCodePrint::AceErrorCodePrint(MC_U8 info2, MC_U16 rfu)
{
    ErrorCodePrintf(EXCE_ACE, EXCE_ACE_FWK, info2, rfu);
}
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT
