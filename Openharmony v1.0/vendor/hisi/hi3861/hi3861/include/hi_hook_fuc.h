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

#ifndef __HI_HOOK_FUC_H__
#define __HI_HOOK_FUC_H__

#include <hi_task.h>
#include <hi_mem.h>
#include <hi_os_stat.h>
#include <hi_timer.h>
#include <hi_isr.h>

#define  fuc_type_name(name)    pfn_##name##_hook

typedef hi_u32 (*fuc_type_name(hi_task_create))(hi_u32 *taskid,
                                                const hi_task_attr *attr,
                                                hi_void* (*task_route)(hi_void *),
                                                hi_void *arg);

typedef hi_u32  (*fuc_type_name(hi_task_delete))(hi_u32 taskid);

typedef hi_u32  (*fuc_type_name(hi_task_suspend))(hi_u32 taskid);

typedef hi_u32  (*fuc_type_name(hi_task_resume))(hi_u32 taskid);

typedef hi_u32  (*fuc_type_name(hi_task_get_priority))(hi_u32 taskid,
                                                       hi_u32 *priority);

typedef hi_u32  (*fuc_type_name(hi_task_set_priority))(hi_u32 taskid,
                                                       hi_u32 priority);

typedef hi_u32  (*fuc_type_name(hi_task_get_current_id))(hi_void);

typedef hi_void (*fuc_type_name(hi_task_lock))(hi_void);

typedef hi_void (*fuc_type_name(hi_task_unlock))(hi_void);

typedef hi_u32  (*fuc_type_name(hi_sleep))(hi_u32 ms);

typedef hi_u32 (*fuc_type_name(hi_event_create))(HI_OUT hi_u32 * id);

typedef hi_u32 (*fuc_type_name(hi_event_init))(hi_u8 max_event_cnt,
                                               hi_pvoid event_space);

typedef hi_u32 (*fuc_type_name(hi_event_send))(hi_u32 id,
                                               hi_u32 event_bits);

typedef hi_u32 (*fuc_type_name(hi_event_wait))(hi_u32 id,
                                               hi_u32 mask,
                                               HI_OUT hi_u32 *event_bits,
                                               hi_u32 timeout,
                                               hi_u32 flag);

typedef hi_u32 (*fuc_type_name(hi_event_clear))(hi_u32 id,
                                                hi_u32 event_bits);

typedef hi_u32 (*fuc_type_name(hi_event_delete))(hi_u32 id);

typedef hi_pvoid (*fuc_type_name(hi_malloc))(hi_u32 mod_id,
                                             hi_u32 size);

typedef hi_void  (*fuc_type_name(hi_free))(hi_u32 mod_id,
                                           hi_pvoid addr);

typedef hi_u32 (*fuc_type_name(hi_msg_queue_create))(HI_OUT hi_u32* id,
                                                     hi_u16 queue_len,
                                                     hi_u32 msg_size);

typedef hi_u32 (*fuc_type_name(hi_msg_queue_wait))(hi_u32 id,
                                                   hi_pvoid msg,
                                                   hi_u32 timeout_ms,
                                                   hi_u32* msg_size);

typedef hi_u32 (*fuc_type_name(hi_msg_queue_send))(hi_u32 id,
                                                   hi_pvoid msg,
                                                   hi_u32 timeout_ms,
                                                   hi_u32 msg_size);

typedef hi_u32 (*fuc_type_name(hi_msg_queue_delete))(hi_u32 id);


typedef hi_u32 (*fuc_type_name(hi_mux_create))(hi_u32* mux_id);

typedef hi_u32 (*fuc_type_name(hi_mux_delete))(hi_u32 mux_id);

typedef hi_u32 (*fuc_type_name(hi_mux_pend))(hi_u32 mux_id,
                                             hi_u32 timeout_ms);

typedef hi_u32 (*fuc_type_name(hi_mux_post))(hi_u32 mux_id);

typedef hi_u32 (*fuc_type_name(hi_sem_create))(hi_u32* sem_id, hi_u16 init_value);

typedef hi_u32 (*fuc_type_name(hi_sem_bcreate))(hi_u32* sem_id, hi_u8 init_value);

typedef hi_u32 (*fuc_type_name(hi_sem_delete))(hi_u32 sem_id);

typedef hi_u32 (*fuc_type_name(hi_sem_wait))(hi_u32 sem_id, hi_u32 timeout);

typedef hi_u32 (*fuc_type_name(hi_sem_signal))(hi_u32 sem_id);


typedef hi_u32 (*fuc_type_name(hi_get_tick))(hi_void);

typedef hi_u64 (*fuc_type_name(hi_get_tick64))(hi_void);

typedef hi_u32 (*fuc_type_name(hi_get_milli_seconds))(hi_void);

typedef hi_u32 (*fuc_type_name(hi_get_seconds))(hi_void);

typedef hi_u64 (*fuc_type_name(hi_get_us))(hi_void);

typedef hi_u32 (*fuc_type_name(hi_get_real_time))(hi_void);

typedef hi_u32 (*fuc_type_name(hi_set_real_time))(hi_u32 sec);

typedef hi_u32 (*fuc_type_name(hi_timer_create))(hi_u32 *timer_handle);

typedef hi_u32 (*fuc_type_name(hi_timer_start))(hi_u32 timer_handle,
                                                hi_timer_type type,
                                                hi_u32 expire,
                                                hi_timer_callback_f timer_func,
                                                hi_u32 data);

typedef hi_u32 (*fuc_type_name(hi_timer_stop))(hi_u32 timer_handle);

typedef hi_u32 (*fuc_type_name(hi_timer_delete))(hi_u32 timer_handle);

typedef hi_u32 (*fuc_type_name(hi_irq_enable))(hi_u32 vector);

typedef hi_void (*fuc_type_name(hi_irq_disable))(hi_u32 vector);

typedef hi_u32 (*fuc_type_name(hi_irq_request))(hi_u32 vector,
                                                hi_u32 flags,
                                                irq_routine routine,
                                                hi_u32 param);

typedef hi_u32 (*fuc_type_name(hi_irq_free))(hi_u32 vector);

typedef hi_bool (*fuc_type_name(hi_is_int_context))(hi_void);

typedef struct {
    /* task */
    fuc_type_name(hi_task_create)         hi_task_create_hook;
    fuc_type_name(hi_task_delete)         hi_task_delete_hook;
    fuc_type_name(hi_task_suspend)        hi_task_suspend_hook;
    fuc_type_name(hi_task_resume)         hi_task_resume_hook;
    fuc_type_name(hi_task_get_priority)   hi_task_get_priority_hook;
    fuc_type_name(hi_task_set_priority)   hi_task_set_priority_hook;
    fuc_type_name(hi_task_get_current_id) hi_task_get_current_id_hook;
    fuc_type_name(hi_task_lock)           hi_task_lock_hook;
    fuc_type_name(hi_task_unlock)         hi_task_unlock_hook;
    fuc_type_name(hi_sleep)               hi_sleep_hook;
    /* event */
    fuc_type_name(hi_event_create)        hi_event_create_hook;
    fuc_type_name(hi_event_init)          hi_event_init_hook;
    fuc_type_name(hi_event_send)          hi_event_send_hook;
    fuc_type_name(hi_event_wait)          hi_event_wait_hook;
    fuc_type_name(hi_event_clear)         hi_event_clear_hook;
    fuc_type_name(hi_event_delete)        hi_event_delete_hook;
    /* memory */
    fuc_type_name(hi_malloc)              hi_malloc_hook;
    fuc_type_name(hi_free)                hi_free_hook;
    /* queue */
    fuc_type_name(hi_msg_queue_create)    hi_msg_queue_create_hook;
    fuc_type_name(hi_msg_queue_send)      hi_msg_queue_send_hook;
    fuc_type_name(hi_msg_queue_wait)      hi_msg_queue_wait_hook;
    fuc_type_name(hi_msg_queue_delete)    hi_msg_queue_delete_hook;
    /* mux */
    fuc_type_name(hi_mux_create)          hi_mux_create_hook;
    fuc_type_name(hi_mux_delete)          hi_mux_delete_hook;
    fuc_type_name(hi_mux_pend)            hi_mux_pend_hook;
    fuc_type_name(hi_mux_post)            hi_mux_post_hook;
    /* semaphore */
    fuc_type_name(hi_sem_create)          hi_sem_create_hook;
    fuc_type_name(hi_sem_bcreate)         hi_sem_bcreate_hook;
    fuc_type_name(hi_sem_delete)          hi_sem_delete_hook;
    fuc_type_name(hi_sem_wait)            hi_sem_wait_hook;
    fuc_type_name(hi_sem_signal)          hi_sem_signal_hook;
    /* time */
    fuc_type_name(hi_get_tick)            hi_get_tick_hook;
    fuc_type_name(hi_get_tick64)          hi_get_tick64_hook;
    fuc_type_name(hi_get_milli_seconds)   hi_get_milli_seconds_hook;
    fuc_type_name(hi_get_seconds)         hi_get_seconds_hook;
    fuc_type_name(hi_get_us)              hi_get_us_hook;
    fuc_type_name(hi_get_real_time)       hi_get_real_time_hook;
    fuc_type_name(hi_set_real_time)       hi_set_real_time_hook;
    /* timer */
    fuc_type_name(hi_timer_create)        hi_timer_create_hook;
    fuc_type_name(hi_timer_start)         hi_timer_start_hook;
    fuc_type_name(hi_timer_stop)          hi_timer_stop_hook;
    fuc_type_name(hi_timer_delete)        hi_timer_delete_hook;
    /* interrupt */
    fuc_type_name(hi_irq_enable)          hi_irq_enable_hook;
    fuc_type_name(hi_irq_disable)         hi_irq_disable_hook;
    fuc_type_name(hi_irq_request)         hi_irq_request_hook;
    fuc_type_name(hi_irq_free)            hi_irq_free_hook;
    fuc_type_name(hi_is_int_context)      hi_is_int_context_hook;
} hi_hook_osa;

HI_EXTERN hi_hook_osa g_hook_osa;

HI_EXTERN hi_u32 hi_init_hook_osa(const hi_hook_osa *osa);

#endif
