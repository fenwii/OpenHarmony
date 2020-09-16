/*
 * ----------------------------------------------------------------------
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ----------------------------------------------------------------------
 */

#include <errno.h>
#include "stdarg.h"
#include "stdbool.h"
#include "pthread_impl.h"

struct user_param {
	unsigned long user_area;
	unsigned long user_sp;
	unsigned long map_base;
	unsigned int map_size;
};

int __thread_clone(int (*func)(void *), int flags, struct pthread *thread, unsigned char *sp)
{
	int ret;
	bool join_flag = false;
	struct user_param param;

	if (thread->detach_state == DT_JOINABLE) {
		join_flag = true;
	}

	param.user_area = TP_ADJ(thread);
	param.user_sp = sp;
	param.map_base = thread->map_base;
	param.map_size = thread->map_size;
	ret = __syscall(SYS_creat_user_thread , func, &param, join_flag);
	if (ret < 0) {
		return ret;
	}

	thread->tid = (unsigned long)ret;
	return 0;
}
