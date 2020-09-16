/**
 * @file hi_wifi_csi_api.h
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
 * @defgroup hi_wifi_csi CSI
 * @ingroup hi_wifi
 */

#ifndef __HI_WIFI_CSI_API_H__
#define __HI_WIFI_CSI_API_H__

#include "hi_wifi_api.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @ingroup hi_wifi_csi
 *
 * Sample period of CSI.CNcomment:CSI 上报采样周期CNend
 */
typedef enum {
    CSI_REPORT_PERIOD_EVERY_FRAME = 0,
    CSI_REPORT_PERIOD_256US = 1,
    CSI_REPORT_PERIOD_512US = 2,
    CSI_REPORT_PERIOD_1024US = 3,
    CSI_REPORT_PERIOD_2048US = 4,
    CSI_REPORT_PERIOD_4096US = 5,
    CSI_REPORT_PERIOD_8192US = 6,
    CSI_REPORT_PERIOD_16384US = 7,
    CSI_REPORT_PERIOD_32768US = 8,
    CSI_REPORT_PERIOD_65536US = 9,
    CSI_REPORT_PERIOD_131072US = 10,
    CSI_REPORT_PERIOD_262144US = 11,
    CSI_REPORT_PERIOD_524288US = 12,
    CSI_REPORT_PERIOD_1048576US = 13,
    CSI_REPORT_PERIOD_2097152US = 14,
    CSI_REPORT_PERIOD_4194304US = 15,
    CSI_REPORT_PERIOD_BUTT
} hi_wifi_csi_period_enum;

/**
 * @ingroup hi_wifi_csi
 *
 * Frame type of CSI report.CNcomment:CSI 上报数据帧类型CNend
 */
typedef enum {
    CSI_FRAME_TYPE_DATA = 1,        /**< data. CNcomment: 数据帧.CNend */
    CSI_FRAME_TYPE_MGMT = 2,        /**< management. CNcomment: 管理帧.CNend */
    CSI_FRAME_TYPE_MGMT_DATA = 3,   /**< management and data. CNcomment: 管理帧和数据帧.CNend */
    CSI_FRAME_TYPE_CTRL = 4,        /**< control. CNcomment: 控制帧.CNend */
    CSI_FRAME_TYPE_CTRL_DATA = 5,   /**< control and data. CNcomment: 控制帧和数据帧.CNend */
    CSI_FRAME_TYPE_CTRL_MGMT = 6,   /**< control adn management. CNcomment: 控制帧和管理帧.CNend */
    CSI_FRAME_TYPE_ALL  = 7,        /**< control and data and management. CNcomment: 控制帧和数据帧和管理帧.CNend */
    CSI_FRAME_TYPE_BUTT
} hi_wifi_csi_frame_type_enum;

/**
 * @ingroup hi_wifi_csi
 *
 * Struct of CSI reporting config.CNcomment:CSI 上报参数配置CNend
 */
typedef struct {
    unsigned char mac[HI_WIFI_MAC_LEN];     /**< Mac address. CNcomment: MAC地址.CNend */
    hi_wifi_csi_frame_type_enum frame_type; /**< Report frame type. CNcomment: 上报帧类型.CNend */
    hi_wifi_csi_period_enum sample_period;  /**< Sample period. CNcomment: 信道采样周期.CNend */
} hi_wifi_csi_entry;

/**
* @ingroup  hi_wifi_csi
* @brief    CSI data report callback.
*
* @par Description:
*           user's callback to handle csi report data.
            CNcomment:用户注册的回调函数，用于处理CSI上报的数据。CNend
*
* @attention  NULL
* @param  csi_data        [IN]     Type  #unsigned char *, 4 bytes extend timestamp + 184 bytes 64bit big endian data.
                                         CNcomment:4字节扩展时间戳+184字节64位小端存储格式的CSI数据。CNend
* @param  len             [IN]     Type  #int, data length. CNcomment:数据长度,固定为188字节。CNend
*
* @retval void
* @par Dependency:
*            @li hi_wifi_csi_api.h: WiFi API
* @see  NULL
*/
typedef void (*hi_wifi_csi_data_cb)(unsigned char *csi_data, int len);

/**
* @ingroup  hi_wifi_csi
* @brief    Config CSI.
*
* @par Description:
*           Config CSI basic parameters, config csi will colse low power, stop csi can open low power again.
            CNcomment:配置CSI数据上报功能的基本参数，配置后会关闭低功耗，暂时不启用CSI可通过stop命令开启低功耗。CNend
*
* @attention  NULL
* @param  ifname               [IN]     Type  #char *,interface which enable CSI, wlan0 or ap0.
* @param  report_min_interval  [IN]     Type  #unsigned int, report period: minimum 50 ms.
                                              CNcomment:CSI数据上报最小间隔，最小周期50ms，小于50ms默认为50ms。CNend
* @param  entry_list           [IN]     Type  #hi_wifi_csi_entry *, configuration struct.
* @param  entry_num            [IN]     Type  #int, list number.CNcomment:entry_list的数量，可添加最大白名单数量为6。CNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_csi_api.h: WiFi API
* @see  NULL
*/
int hi_wifi_csi_set_config(const char *ifname, unsigned int report_min_interval,
                           const hi_wifi_csi_entry *entry_list, int entry_num);

/**
* @ingroup  hi_wifi_csi
* @brief    Register report callback of CSI.CNcomment:注册CSI数据上报回调函数。CNend
*
* @par Description:
*           CSI data report interface.CNcomment:由用户注册回调函数，用于上报CSI数据。CNend
*
* @attention  NULL
* @param  data_cb         [IN]     Type  #hi_wifi_csi_data_cb, callback pointer.
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_csi_api.h: WiFi API
* @see  NULL
*/
int hi_wifi_csi_register_data_recv_func(hi_wifi_csi_data_cb data_cb);

/**
* @ingroup  hi_wifi_csi
* @brief    Start CSI.
*
* @par Description:
*           Start CSI.
*
* @attention  NULL
* @param  NULL
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_csi_api.h: WiFi API
* @see  NULL
*/
int hi_wifi_csi_start(void);

/**
* @ingroup  hi_wifi_csi
* @brief    Close CSI.
*
* @par Description:
*           Close CSI.
*
* @attention  NULL
* @param  NULL
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_csi_api.h: WiFi API
* @see  NULL
*/
int hi_wifi_csi_stop(void);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of hi_wifi_csi_api.h */

