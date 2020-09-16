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

#ifndef __HI_EARLY_DEBUG_H__
#define __HI_EARLY_DEBUG_H__
#include <stdarg.h>

void edb_put_str_only(const char *s);
void edb_put_str_p0(char *str);
void edb_put_str_p1(char *str, unsigned int p1);
void edb_put_str_p2(char *str, unsigned int p1, unsigned int p2);
void edb_put_str_p3(char *str, unsigned int p1, unsigned int p2, unsigned int p3);
void edb_put_str_p4(char *str, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
void edb_put_buf(char *buf, unsigned int len);
int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list va);
int dprintf(const char *fmt, ...);
void edb_set_print_level(unsigned int level);
void hi_printf_alloc_uart_by_nv(void);
#endif

