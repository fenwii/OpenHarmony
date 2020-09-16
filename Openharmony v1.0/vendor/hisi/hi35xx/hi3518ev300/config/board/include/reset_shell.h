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

#ifndef _RESET_SHELL_H
#define _RESET_SHELL_H
#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


typedef VOID* (*STORAGE_HOOK_FUNC)(VOID*);

typedef struct tagHookFuncNode {
    STORAGE_HOOK_FUNC  pHandler;
    VOID *pParam;
    struct tagHookFuncNode *pNext;
}Hook_Func_Node;

extern Hook_Func_Node *g_hook_func_node;

UINT32 osReHookFuncAdd(STORAGE_HOOK_FUNC handler, VOID *param);
UINT32 osReHookFuncDel(STORAGE_HOOK_FUNC handler);
VOID osReHookFuncHandle(VOID);
extern void cmd_reset(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
