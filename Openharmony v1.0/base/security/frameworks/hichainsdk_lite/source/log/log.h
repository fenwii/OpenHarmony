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

#ifndef __LOG_H__
#define __LOG_H__

typedef void (*log_f)(const char *tag, const char *func_name, const char *format, ...);

struct log_f_group {
    log_f log_d;
    log_f log_i;
    log_f log_w;
    log_f log_e;
};

log_f get_logd(void);
log_f get_logi(void);
log_f get_logw(void);
log_f get_loge(void);

#if !(defined(_CUT_LOG_))
#define DBG_OUT(...) get_logd()("[HiChain]", __func__, __VA_ARGS__)
#define LOGI(...) get_logi()("[HiChain]", __func__, __VA_ARGS__)
#define LOGW(...) get_logw()("[HiChain]", __func__, __VA_ARGS__)
#define LOGE(...) get_loge()("[HiChain]", __func__, __VA_ARGS__)
#else
#define DBG_OUT(...) {}
#define LOGI(...) {}
#define LOGW(...) {}
#define LOGE(...) {}
#endif

#endif /* __LOG_H__ */
