/**
 * @file hi_wifi_tmp_api.h
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
 *
 * Description: header file for wifi api.CNcomment:描述：WiFi api接口头文件CNend\n
 */

/**
 * @defgroup hi_wifi WiFi API
 */
/**
 * @defgroup hi_wifi_tmp TMP
 * @ingroup hi_wifi
 */

#ifndef __HI_WIFI_TMP_API_H__
#define __HI_WIFI_TMP_API_H__

#include "hi_wifi_api.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/**
* @ingroup  hi_wifi_pm
* @brief    Set dhcp offload on/off.CNcomment:设置dhcp offload 打开/关闭。CNend
*
* @par Description:
*           Set dhcp offload on with ip address, or set dhcp offload off.
*           CNcomment:设置arp offload打开、并且设置相应ip地址，或者设置arp offload关闭。CNend
*
* @attention  NULL
* @param  ifname         [IN]     Type  #const char *, device name.
* @param  en             [IN]     Type  #unsigned char, dhcp offload type, 1-on, 0-off.
* @param  ip             [IN]     Type  #unsigned int *, ip address in network byte order.
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_tmp_api.h: WiFi API
* @see  NULL
*/
unsigned char hi_wifi_dhcp_offload_setting(const char *ifname, unsigned char en, unsigned int ip);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif
