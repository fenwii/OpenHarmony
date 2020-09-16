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

#include <stdio.h>
#include "parameter.h"

int main(int argc, char **argv)
{
    printf("******To Obtain Product Params Start******\n");
    printf("The VersionID is [%s]\n", GetVersionId());
    printf("The Sdk Api Level is [%s]\n", GetFirstApiLevel());
    printf("The Security Patch is [%s]\n", GetSecurityPatchTag());
    printf("The AbiList is [%s]\n", GetAbiList());
    printf("The OS Version is [%s]\n", GetDisplayVersion());
    printf("The BuildRootHash is [%s]\n", GetBuildRootHash());
    printf("The HardwareModel is [%s]\n", GetHardwareModel());
    printf("The HardwareProfile is [%s]\n", GetHardwareProfile());
    printf("******To Obtain Product Params End  ******\n");
    return 0;
}