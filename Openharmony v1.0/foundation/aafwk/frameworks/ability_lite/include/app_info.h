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

#ifndef OHOS_APP_INFO_H
#define OHOS_APP_INFO_H

#include <list>
#include <string>

typedef struct {
    std::string bundleName;
    std::string srcPath;
    std::string dataPath;
    bool isNativeApp;
    std::list<std::string> moduleNames;
} AppInfo;

#endif // OHOS_APP_INFO_H
