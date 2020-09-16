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

/*************************************************************/
#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/** system source configuration **/
/**
 * @ingroup los_config
 * Maximum supported number of tasks except the idle task rather than the number of usable tasks
 */
#define LOSCFG_BASE_CORE_TSK_CONFIG                 64
/**
 * @ingroup los_config
 * Maximum supported number of semaphores
 */
#define LOSCFG_BASE_IPC_SEM_CONFIG                  1024
/**
 * @ingroup los_config
 * Maximum supported number of mutexes
 */
#define LOSCFG_BASE_IPC_MUX_CONFIG                 1024
/**
 * @ingroup los_config
 * Maximum supported number of queues rather than the number of usable queues
 */
#define LOSCFG_BASE_IPC_QUEUE_CONFIG               1024
/**
 * @ingroup los_config
 * Maximum supported number of software timers rather than the number of usable software timers
 */
#define LOSCFG_BASE_CORE_SWTMR_CONFIG               1024

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif /* _SYSTEM_CONFIG_H */
/*************************************************************/
