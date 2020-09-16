/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#ifndef __APP_IO_INIT_H__
#define __APP_IO_INIT_H__

#include <hi_types_base.h>

HI_CPP_START

hi_void app_io_init(hi_void);
hi_void app_io_set_gpio2_clkout_enable(hi_bool enable);

HI_CPP_END
#endif /* __APP_IO_INIT_H__ */

