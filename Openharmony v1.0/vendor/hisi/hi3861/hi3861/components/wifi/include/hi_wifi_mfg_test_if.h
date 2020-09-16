/**
 * @file hi_wifi_mfg_test_if.h
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
 * Description: header file for wifi manufacturing test interference.CNcomment:描述：WiFi 产测接口头文件CNend\n
 */

/**
 * @defgroup hi_wifi_mfg_test_if
 */
/**
 * @defgroup hi_wifi_mfg_test_if Basic Settings
 * @ingroup hi_wifi
 */

#ifndef __HI_WIFI_MFG_TEST_IF_H__
#define __HI_WIFI_MFG_TEST_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum {
    HISI_AT_AL_TX,
    HISI_AT_AL_RX,
    HISI_AT_RX_INFO,
    HISI_AT_SET_COUNTRY,
    HISI_AT_GET_COUNTRY,
    HISI_AT_SET_WLAN0_BW,
    HISI_AT_SET_AP0_BW,
    HISI_AT_SET_MESH0_BW,
    HISI_AT_GET_WLAN0_MESHINFO,
    HISI_AT_GET_MESH0_MESHINFO,
    HISI_AT_SET_TPC,
    HISI_AT_SET_TRC,
    HISI_AT_SET_RATE,
    HISI_AT_SET_ARLOG,
    HISI_AT_GET_VAP_INFO,
    HISI_AT_GET_USR_INFO,

    HISI_AT_TYPE_BUTT
}hisi_at_type_enum;

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  Set cal rate power.CNcomment:对不同协议场景、不用速率分别做功率补偿CNend
*
* @par Description:
*           Set cal band power.CNcomment:对不同协议场景、不用速率分别做功率补偿CNend
*
* @attention  NULL
* @param  protol         [IN]     Type  #unsigned char protol.CNcomment:协议序号CNend
* @param  rate           [IN]     Type  #unsigned char rate.CNcomment:速率CNend
* @param  val            [IN]     Type  #int power val.CNcomment:补偿值CNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_set_cal_rate_power(unsigned char protol, unsigned char rate, int val);

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  Set cal freq.CNcomment:进行常温频偏功率补偿CNend
*
* @par Description:
*           Set cal freq.CNcomment:进行常温频偏功率补偿CNend
*
* @attention  NULL
* @param  freq_offset    [IN]     Type  #int freq offset.CNcomment:补偿值CNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_set_cal_freq(int freq_offset);

#ifdef _PRE_WLAN_FEATURE_MFG_TEST
/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  Set cal band power.CNcomment:设置各band平均功率补偿CNend
*
* @par Description:
*           Set cal band power.CNcomment:设置各band平均功率补偿CNend
*
* @attention  NULL
* @param  band_num         [IN]     Type  #unsigned char band num.CNcomment:band序号CNend
* @param  offset           [IN]     Type  #int power offset.CNcomment:功率补偿值CNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_set_cal_band_power(unsigned char band_num,  int offset);

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  set macefuse mac addr.CNcomment:将MAC地址写入efuse或nvCNend
*
* @par Description:
*           set macefuse mac addr.CNcomment:将MAC地址写入efuse或nvCNend
*
* @attention  NULL
* @param  mac_addr    [IN]     Type  #const char * mac addr.CNcomment:mac地址CNend
* @param  type        [IN]     Type  #unsigned char type.CNcomment:写入类型,0:efuse,1:nvCNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_set_customer_mac(const char *mac_addr, unsigned char type);

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  get macefuse mac addr.CNcomment:获取efuse中的MAC地址CNend
*
* @par Description:
*           get macefuse mac addr.CNcomment:获取efuse中的MAC地址CNend
*
* @attention  NULL
* @param  NULL
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_get_customer_mac(void);

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  write data into efuse.CNcomment:将校准值写入efuseCNend
*
* @par Description:
*           write data into efuse.CNcomment:将校准值写入efuseCNend
*
* @attention  NULL
* @param  type        [IN]     Type  #unsigned char type.CNcomment:写入类型,0:efuse,1:nvCNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_set_dataefuse(hi_u32 type);
#endif

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  get cur cal data.CNcomment:获取当前产测校准值CNend
*
* @par Description:
*           get cur cal data.CNcomment:获取当前产测校准值CNend
*
* @attention  NULL
* @param  NULL
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_get_cal_data(void);

#if defined(CONFIG_FACTORY_TEST_MODE) || defined(_PRE_WLAN_QUICK_SEND)
/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  add cfg vap.CNcomment:添加配置vapCNend
*
* @par Description:
*           add cfg vap.CNcomment:添加配置vapCNend
*
* @attention  NULL
* @param  NULL
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int wal_add_cfg_vap(void);
#endif

/**
* @ingroup  hi_wifi_mfg_test_if
* @brief  always rx/tx interference function.CNcomment:常发常收等接口函数CNend
*
* @par Description:
*           always rx/tx interference function.CNcomment:常发常收等接口函数CNend
*
* @attention  NULL
* @param  argc         [IN]     Type  #int argc.CNcomment:命令参数个数CNend
* @param  argv         [IN]     Type  #const char *argv.CNcomment:命令各参数对应的字符串数组CNend
* @param  cmd_type     [IN]     Type  #unsigned int cmd_type.CNcomment:命令类型CNend
*
* @retval #HI_ERR_SUCCESS  Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_wifi_mfg_test_if.h: WiFi mfg_test
* @see  NULL
*/
unsigned int hi_wifi_at_start(int argc, const char *argv[], unsigned int cmd_type);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif
