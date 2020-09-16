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

#ifndef __EXCHANGE_AUTH_INFO_CLIENT_H__
#define __EXCHANGE_AUTH_INFO_CLIENT_H__

#include "auth_info.h"
#include "pake_client.h"

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_CLIENT_) || defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_CLIENT_))

int32_t receive_exchange_response(const struct hichain *hichain, const struct message *receive);

#endif /* _CUT_XXX_ */
int32_t send_exchange_request(const struct hichain *hichain, struct message *send);
#endif /* __EXCHANGE_AUTH_INFO_CLIENT_H__ */
