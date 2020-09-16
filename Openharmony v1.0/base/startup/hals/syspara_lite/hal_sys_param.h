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

#ifndef HAL_SYS_PARAM_H
#define HAL_SYS_PARAM_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

char* HalGetProductType(void);
char* HalGetManufacture(void);
char* HalGetBrand(void);
char* HalGetMarketName(void);
char* HalGetProductSeries(void);
char* HalGetProductModel(void);
char* HalGetSoftwareModel(void);
char* HalGetHardwareModel(void);
char* HalGetHardwareProfile(void);
char* HalGetSerial(void);
char* HalGetBootloaderVersion(void);
char* HalGetSecurityPatchTag(void);
char* HalGetAbiList(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // HAL_SYS_PARAM_H