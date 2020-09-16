/**
 * @file hi_btcoex_api.h
 *
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

/**
* @defgroup hi_wifi_btcoex BTCOEX
* @ingroup hi_wifi
*/

#ifndef __HI_BTCOEX_API_H__
#define __HI_BTCOEX_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
* @ingroup  hi_wifi_btcoex
* @brief    Set wifi & bt coexist on/off.
*           CNcomment:蓝牙共存打开/关闭。CNend
*
* @par Description:
*           Set wifi & bt coexist on while wifi and bt are both turned on.
*           or set wifi & bt coexist off while bt is turned off.
*           CNcomment:wifi & bt 都打开时打开coexist共存，bt 关闭时关掉coexist共存。CNend
*
* @param  ifname          [IN]     Type  #const char *, device name, e.g. wlan0.CNcomment:设备名称，如 wlan0。CNend
* @param  enable          [IN]     Type  #enable, whether turn wifi & bt coexist on or off, 0:off, 1:on.
*                                        CNcomment:是否打开蓝牙wifi共存，0:关闭, 1:打开。CNend
* @param  mode            [IN]     Type  #mode,  wifi & bt coexist mode, 1:2-wired, 2:3-wired.
*                                        CNcomment:蓝牙wifi共存模式，1:二线, 2:三线。CNend
* @param  share_ant       [IN]     Type  #share_ant, whether wifi & bt share ant, 0:no share ant, 1:share ant.
*                                        CNcomment:蓝牙wifi是否共用天线，0:不共用,1:共用。CNend
* @param  preempt         [IN]     Type  #preempt, whether send wifi & bt preempt frame (NULL data), 0:no send, 1:send.
*                                        CNcomment:是否发送共存preemp帧(NULL data)，0:不发送,1:发送。CNend
*
* @attention
*    It will occupy some space time for sending preempt frame (NULL data), the performance of not sending preempt frame
*    is better than sending in lab test, while sending preempt frame could tell the peer sta that the bt is working
*    at this moment.CNcomment:发送共存preemp帧(NULL data)，会占用一定空口资源，实测不发送preemp帧
*    性能比发送preemp帧性能更高，发送preemp帧可以明确告知对端AP当前wifi的工作状态。CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_btcoex_api.h: WiFi API
* @see  NULL
*/
hi_u32 hi_wifi_btcoex_enable(const hi_char *ifname, hi_bool enable, hi_u8 mode, hi_u8 share_ant, hi_u8 preempt);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of hi_btcoex_api.h */
