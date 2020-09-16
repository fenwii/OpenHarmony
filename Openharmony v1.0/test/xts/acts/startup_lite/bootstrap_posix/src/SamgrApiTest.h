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

#ifndef XTS_HITS_SAMGR_API_EXPECT_H
#define XTS_HITS_SAMGR_API_EXPECT_H

constexpr int SAMGR_API_GROUP_NUM  = 8;
constexpr int SAMGR_API_CALL_NUM = 6;
#define GET_INIT_INDEX(G, pri) ((G)*(SAMGR_API_CALL_NUM)+(pri))

using SamgrApiGroup = enum TagSamgrApiGroup {
    CORE_INIT_E = 0,
    SYS_SERVICE_INIT_E,
    SYS_FEATURE_INIT_E,
    APP_SERVICE_INIT_E,
    SYSEX_SERVICE_INIT_E,
    APP_FEATURE_INIT_E,
    SYSEX_FEATURE_INIT,
    SYS_RUN_E,
};

using SamgrApiPri = enum TagSamgrApiPri {
    API_PRI0 = 0,
    API_PRI1,
    API_PRI_DEFAULT,
    API_PRI2,
    API_PRI3,
    API_PRI4,
    API_PRI_MAX,
};

#endif  // XTS_HITS_SAMGR_API_EXPECT_H