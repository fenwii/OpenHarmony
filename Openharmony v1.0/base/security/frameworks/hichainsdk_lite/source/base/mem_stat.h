/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MEM_STAT_H__
#define __MEM_STAT_H__

#include <stdlib.h>

#ifndef _HC_DEBUG_

#ifndef _STD_LIB_SOUTH_

#define MALLOC(size) (((size) == 0) ? NULL : malloc(size))
#define FREE free

#else /* _STD_LIB_SOUTH_ */

#if (defined _HILINK_PRODUCT_)

#include "product_header/hilink_osadapter.h"
#define MALLOC  hilink_malloc
#define FREE    hilink_free

#endif /* defined product */

#endif /* _STD_LIB_SOUTH_ */

#else /* _HC_DEBUG_ */

#ifdef __cplusplus
extern "C" {
#endif
void *MALLOC(size_t size);
void FREE(void *ptr);
#ifdef __cplusplus
}
#endif

#endif /* _HC_DEBUG_ */

#endif /* __MEM_STAT_H__ */
