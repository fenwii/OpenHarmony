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
#include "jstest_module.h"
#if (defined(JSFWK_TEST) && defined(OHOS_ACELITE_PRODUCT_WATCH))
#include <stdlib.h>
#include "ace_mem_base.h"
#include "test_fwk.h"
namespace OHOS {
namespace ACELite {
void JSTestModule::Init()
{
    const char * const funcName = "jstestPrint";
    CreateNamedFunction(funcName, JSTestPrint);
}

jerry_value_t JSTestModule::JSTestPrint(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t *args,
                                        const jerry_length_t argsNum)
{
    if (argsNum == 0) {
        return UNDEFINED;
    }

    char *msg = MallocStringOf(args[0]);

    if (msg != nullptr) {
        LiteTestPrint(msg);
        ace_free(msg);
        msg = nullptr;
    }

    return UNDEFINED;
}
} // namespace ACELite
} // namespace OHOS
#endif