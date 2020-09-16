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

#ifndef OHOS_DUMP_ABILITY_CLIENT_H
#define OHOS_DUMP_ABILITY_CLIENT_H

#include "liteipc_adapter.h"
#include "util/abilityms_status.h"
#include "want.h"

namespace OHOS {
class AbilityDumpClient {
public:
    explicit AbilityDumpClient(const Want &want);
    ~AbilityDumpClient();

    const Want &GetWant() const;
    AbilityMsStatus AbilityDumpTransaction(const char *info) const;
private:
    Want want_ = {};
};
} // namespace OHOS
#endif // OHOS_DUMP_ABILITY_CLIENT_H
