/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: implementation for l3_msg_event
 * Author: none
 * Create: 2020
 */

#ifndef LWIP_HDR_L3EVENT_H
#define LWIP_HDR_L3EVENT_H

#include "lwip/opt.h"

/* define the app_callback function point type */
typedef void (*app_callback_fn)(u8_t, void *);

#if !NO_SYS /* don't build if not configured for use in lwipopts.h */
#if LWIP_L3_EVENT_MSG

typedef enum l3_event_msg_type {
#if LWIP_ROUTE_CHANGE_MSG
  L3_EVENT_MSG_ROUTE_CHANGE,
#endif
#if LWIP_RPL_JOIN_SUCC_MSG
  L3_EVENT_MSG_RPL_JOIN_SUCC,
#endif
#if LWIP_RPL_PARENT_CLEAR_MSG
  L3_EVENT_MSG_PARENT_CLEAR,
#endif
#if LWIP_RPL_BEACON_PRI_RESET
  L3_EVENT_MSG_BEACON_PRI_RESET,
#endif
#if LWIP_RPL_GET_IPV4_ADDR_FAIL
  L3_EVENT_MSG_GET_IPV4_ADDR_FAIL,
#endif
#if LWIP_RPL_MSTA_GET_IPV4_ADDR_FAIL
  L3_EVENT_MSG_MSTA_GET_IPV4_ADDR_FAIL,
#endif
#if LWIP_RPL_MG_FULL
  L3_EVENT_MSG_MG_FULL,
#endif
#if LWIP_RPL_RT_FULL
  L3_EVENT_MSG_RT_FULL,
#endif
  /* other MSG could be added here */
  L3_EVENT_MSG_MAX
} l3_event_msg_type_e;

/*
 * Func Name: l3_invoke_msg_callback
 */
/**
 * @brief
 *
 *  This is a thread safe API, used to invoke the l3_event_msg
 *
 * @param[IN]  evt_type: the event type
 *             msg: the carry msg for using afterwards, can be NULL.
 *
 * @returns NA \n
 *
 */
void l3_invoke_msg_callback(enum l3_event_msg_type evt_type, void *msg);

/*
 * Func Name: l3_event_msg_callback_reg
 */
/**
 * @brief
 *
 *  This is a thread safe API, used to register the l3_event_msg
 *
 * @param[IN]  evt_type: the event type
 *             app_callback: the register callback function, can be NULL if app unregister or don't want to register.
 *
 * @returns NA \n
 *
 */
void l3_event_msg_callback_reg(enum l3_event_msg_type evt_type, app_callback_fn app_callback);

#endif /* LWIP_L3_EVENT_MSG */
#endif /* !NO_SYS */

#endif /* LWIP_HDR_L3EVENT_H */
