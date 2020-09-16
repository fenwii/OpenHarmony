/*
 * @file hi_any_api.h
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
 * @defgroup hi_wifi_any ANY API
 * @ingroup hi_wifi
 */

#ifndef __HI_ANY_API_H__
#define __HI_ANY_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @ingroup hi_wifi_any
 *
 * Max length of data for a single ANY transmit.CNcomment:单次ANY发送允许的最大数据长度。CNend
 */
#define WIFI_ANY_MAX_USER_DATA 250
/**
 * @ingroup hi_wifi_any
 *
 * Length of key in octets used in ANY communication.CNcomment:ANY加密通信的密钥长度，固定为16字节。CNend
 */
#define WIFI_ANY_KEY_LEN       16
/**
 * @ingroup hi_wifi_any
 *
 * Length of MAC address.CNcomment:MAC地址长度定义CNend
 */
#define WIFI_ANY_MAC_LEN        6
/**
 * @ingroup hi_wifi_any
 *
 * Max length of wlan ssid(for driver).CNcomment:wifi驱动SSID最大长度,+1为\0预留空间CNend
 */
#define WIFI_ANY_MAX_SSID_LEN       (32 + 1)

/**
 * @ingroup hi_wifi_any
 *
 * Struct of peer's information.CNcomment:用户向驱动配置的对端设备信息数据CNend
 */
typedef struct {
    unsigned char mac[WIFI_ANY_MAC_LEN]; /**< the MAC address for peer device. */
                                         /**< CNcomment: 收发操作的对端MAC地址 */
    unsigned char channel;               /**< the channel number of peer device,the value
                                              0xFF means current channel. */
                                         /**< CNcomment: 对端所在信道号，驱动对该信息仅做存储，0xFF表示当前信道 */
    bool          has_key;               /**< whether need key for packet encryption,if true,key shall be specified. */
                                         /**< CNcomment: 是否配置通信密钥，是则填true，并在key中传入密钥，否则填false */
    unsigned char key[WIFI_ANY_KEY_LEN]; /**< the key for packet encryption,it consists of 16 bytes. */
                                         /**< CNcomment: 用于加密通信的密钥，填充的密钥固定为16字节长度 */
} hi_wifi_any_peer_info;

/**
 * @ingroup hi_wifi_any
 *
 * Struct of information of ANY device discovered.CNcomment:扫描发现的ANY设备的参数定义CNend
 */
typedef struct {
    unsigned char bssid[WIFI_ANY_MAC_LEN];      /**< the MAC address of peer device. */
                                                /**< CNcomment: BSSID,若对端为STA则为其MAC地址 */
    unsigned char channel;                      /**< the channel number of peer device. */
                                                /**< CNcomment: 信道号，取值范围1-14，不同区域取值范围有差异 */
    unsigned char sta_flag;                     /**< if peer device is a STA,the value is true,otherwise false. */
                                                /**< CNcomment: true表示对端是STA，否则为普通AP */
    unsigned char ssid[WIFI_ANY_MAX_SSID_LEN];  /**< SSID. *//**< CNcomment: SSID */
    unsigned char ssid_len;                     /**< the string length of SSID. *//**< CNcomment: SSID字符串长度 */
    char          rssi;                         /**< RSSI value of peer device. *//**< CNcomment: 信号强度 */
    unsigned char resv;                         /**< Reserved. *//**< CNcomment: 保留 */
} hi_wifi_any_device;

/**
* @ingroup  hi_wifi_any
* @brief  Callback function invoked when ANY scan is finished.CNcomment:ANY扫描完成回调函数CNend
*
* @par Description:
*           When registered,the driver uses this callback to deliver ANY devices found after an ANY scan. \n
*           CNcomment:注册该回调函数之后，驱动每次完成ANY扫描调用该接口反馈结果给上层.CNend
*
* @attention  1. This function is called in driver context,should not be blocked or do long time waiting.\n
                 CNcomment:1. 该回调函数运行于驱动线程，不能阻塞或长时间等待.CNend \n
*             2. The memories of <devices> are requested and freed by the driver automatically.\n
*                CNcomment:2. <devices>由驱动申请内存，也由驱动释放，回调中不应释放.CNend
* @param  devices [IN]  Type  #hi_wifi_any_device *, array of poniter of ANY devices found.CNcomment:发现的ANY设备信息,
*                       该参数为指针类型的数组。CNend
* @param  num     [IN]  Type  #unsigned char, the number of ANY devices found, maximum is 32.CNcomment:发现的设备数量,
*                       最大不超过32.CNend
*
* @retval #void  no return value.CNcomment:无返回值.CNend
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  hi_wifi_any_discover_peer
*/
typedef void (*hi_wifi_any_scan_result_cb)(hi_wifi_any_device *devices[], unsigned char num);

/**
* @ingroup  hi_wifi_any
* @brief  Callback function for ANY RX.CNcomment:ANY驱动接收回调函数CNend
*
* @par Description:
*           When registered,the driver uses this callback to deliver data received. \n
*           CNcomment:注册该回调函数之后，驱动收到ANY报文则调用该回调函数传递给上层应用.CNend
*
* @attention  1. This function is called in driver context,should not be blocked or do long time waiting.\n
                 CNcomment:1. 该回调函数运行于驱动线程，不能阻塞或长时间等待.CNend\n
*             2. The memories of <mac> and <data> are requested and freed by the driver.\n
*                CNcomment:2. <mac>和<data>由驱动申请内存,也由驱动释放，回调中不应释放.CNend
* @param  mac        [IN]  Type  #unsigned char *, MAC address with 6 octets length.CNcomment:6字节长度MAC地址.CNend
* @param  data       [IN]  Type  #unsigned char *, the address of data received.CNcomment:接收到数据的缓存地址.CNend
* @param  len        [IN]  Type  #unsigned short, the length in octet of data received.CNcomment:接收的数据长度，
*                                最大为250字节.CNend
* @param  seqnum     [IN]  Type  #unsigned char, the sequence number of the ANY frame, range [0-255].
*                                CNcomment:接收到的ANY帧的序列号,范围0-255.CNend
*
* @retval #void no return value.CNcomment:无返回值.CNend
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  hi_wifi_any_set_callback
*/
typedef void (*hi_wifi_any_recv_cb)(unsigned char *mac, unsigned char *data, unsigned short len, unsigned char seqnum);

/**
* @ingroup  hi_wifi_any
* @brief  Callback function for ANY TX.CNcomment:ANY驱动发送回调函数CNend
*
* @par Description:
*           When registered,the driver uses this callback to notify whether an ACK has received. \n
*           CNcomment:注册该回调函数之后，驱动将发送结果(是否收到ACK)反馈给上层应用.CNend
*
* @attention  1. This function is called in driver context,should not be blocked or do long time waiting.\n
                 CNcomment:1. 该回调函数运行于驱动线程，不能阻塞或长时间等待.CNend \n
*             2. The memories of <mac> are requested and freed by the driver.\n
*                CNcomment:2. <mac>由驱动申请内存，也由驱动释放，回调中不应释放.CNend
* @param  mac        [IN]  Type  #unsigned char *, MAC address with 6 octets length.CNcomment:6字节长度MAC地址.CNend
* @param  status     [IN]  Type  #unsigned char, the result of a single transmit,return 1 if transmitted successfully.
                                 CNcomment:单次发送的结果, 值为1代表发送成功，其他值代表发送失败.CNend
* @param  seqnum     [IN]  Type  #unsigned char, the sequence number of the ANY frame, range [0-255].
*                                CNcomment:接收到的ANY帧的序列号,范围0-255.CNend
*
* @retval #void no return value.CNcomment:无返回值.CNend
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  hi_wifi_any_set_callback
*/
typedef void (*hi_wifi_any_send_complete_cb)(unsigned char *mac, unsigned char status, unsigned char seqnum);

/**
 * @ingroup hi_wifi_any
 *
 * Struct of ANY callback function.CNcomment:ANY收发回调接口定义CNend
 */
typedef struct {
    hi_wifi_any_send_complete_cb send_cb; /**< the callback function invoked when an ANY frame is sent. */
                                          /**< CNcomment: ANY发送完成驱动回调函数，用于将驱动发送结果反馈给上层 */
    hi_wifi_any_recv_cb recv_cb;          /**< the callback function invoked when an ANY frame is received. */
                                          /**< CNcomment: ANY接收数据驱动回调函数，用于将驱动接收的数据传递给上层 */
} hi_wifi_any_callback;

/**
* @ingroup  hi_wifi_any
* @brief  Use this funtion to initialize ANY feature.CNcomment:ANY功能初始化函数CNend
*
* @par Description:
*           Use this funtion to initialize ANY feature.CNcomment:ANY功能初始化函数CNend
*
* @attention  A device shall be intialized only once, do de-initialzing first before perform a new initialization.\n
              CNcomment:一个设备只允许一次初始化，重新初始化之前需要先调用去ANY初始化.CNend \n
* @param  seqnum     [IN]  Type  #const char *, the interface name used to TX/RX ANY frames, eg.wlan0/ap0/mesh0.
*                                CNcomment:用于收发ANY报文的接口名称，常用值为"wlan0","ap0"或"mesh0".CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  NULL
*/
int hi_wifi_any_init(const char *ifname);

/**
* @ingroup  hi_wifi_any
* @brief  Use this funtion to de-initialize ANY feature.CNcomment:ANY功能去初始化函数CNend
*
* @par Description:
*           Use this funtion to de-initialize ANY feature.CNcomment:ANY功能去初始化函数CNend
*
* @attention  NULL
* @param  NULL
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  NULL
*/
int hi_wifi_any_deinit(void);

/**
* @ingroup  hi_wifi_any
* @brief  Register callback functions for ANY TX and RX.CNcomment:注册ANY驱动发送回调函数和接收回调函数CNend
*
* @par Description:
*           Register callback functions for ANY TX and RX.CNcomment:注册ANY驱动发送回调函数和接收回调函数CNend
*
* @attention  APP shall implement the TX/RX callbacks and register them to driver through this function.\n
              CNcomment:需要用户自己实现该回调函数功能并通过上述接口注册给驱动.CNend
* @param  send_cb  [IN]  Type  #hi_wifi_any_send_complete_cb, callback function for ANY TX.
*                              CNcomment:ANY驱动发送回调函数.CNend
* @param  recv_cb  [IN]  Type  #hi_wifi_any_recv_cb, callback function for ANY RX.
*                              CNcomment:ANY驱动接收回调函数.CNend
*
* @retval #void    no return value.CNcomment:无返回值.CNend
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  hi_wifi_any_send_complete_cb | hi_wifi_any_recv_cb
*/
void hi_wifi_any_set_callback(hi_wifi_any_send_complete_cb send_cb, hi_wifi_any_recv_cb recv_cb);

/**
* @ingroup  hi_wifi_any
* @brief    Send ANY frame to specific mac address.CNcomment:向指定MAC地址的设备发送ANY数据。CNend
*
* @par Description:
*           Frame TX interface of ANY, specify frame's sequece number by seq. \n
*           the mac_len shall be constant 6 and data_len for a frame should not exceed 250 octets. \n
*           CNcomment:ANY报文发送接口，可以通过seq指定该报文的发送序列号。\n
*           其中MAC地址长度固定填6字节，待发送的数据长度data_len不能超过250字节 CNend
*
* @attention     The memories of <mac> and <data> are requested and freed by user APP.\n
*                CNcomment:<mac>和<data>内存由用户申请和管理，执行完成后驱动不会释放.CNend
* @param  mac        [IN]  Type  #const unsigned char *, destination MAC address, it may be unicast or broadcast.
*                                CNcomment:6字节长度目的MAC地址, 可为单播或者广播地址, 不支持组播地址.CNend
* @param  mac_len    [IN]  Type  #unsigned char, length of MAC address which shall be 6 in octet.
*                                CNcomment:MAC地址长度, 需为6字节.CNend
* @param  data       [IN]  Type  #unsigned char *, the address of data.CNcomment:待发送数据的缓存地址.CNend
* @param  len        [IN]  Type  #unsigned short, the length in octet of data, maximum is 250.
*                                CNcomment:待发送的数据长度, 最大为250字节.CNend
* @param  seqnum     [IN]  Type  #unsigned char, the sequence number of the ANY frame, range [0-255].
*                                CNcomment:待发送的ANY帧的序列号,范围0-255.CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  hi_wifi_any_send_complete_cb
*/
int hi_wifi_any_send(const unsigned char *mac, unsigned char mac_len, unsigned char *data,
                     unsigned short data_len, unsigned char seq);

/**
* @ingroup  hi_wifi_any
* @brief    Add information of ANY peer device.CNcomment:添加ANY对端设备信息。CNend
*
* @par Description:
*           Add information of ANY peer device(mac address, channel and key). \n
*           the number of peer devices must not exceed 16, among which the encrypted must not exceed 6. \n
*           CNcomment:添加对端设备的MAC地址，所在信道信息和用于加密通信的密钥。\n
*                     对端设备总数最多16个，其中加密通信的对端个数最多6个。CNend
*
* @attention   1. The driver just stores the channels of peer devices.\n
*                 It will not switch to a channel automatically which differs with the current channel. \n
*                 CNcomment:1. 驱动仅保存对端设备的信道号，通信过程不会自动切到对应信道.CNend \n
*              2. The memories of <peer_info> are requested and freed by user APP.\n
*                 CNcomment:2. <peer_info>内存由用户管理，驱动接口中不会释放.CNend
* @param  peer_info       [IN]     Type  #hi_wifi_any_peer_info *, information of peer device.
*                                  CNcomment:对端设备的信息.CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  NULL
*/
int hi_wifi_any_add_peer(const hi_wifi_any_peer_info *peer_info);

/**
* @ingroup  hi_wifi_any
* @brief    Delete specific peer device.CNcomment:删除指定MAC地址的对端设备信息。CNend
*
* @par Description:
*           Delete peer device specified by MAC address, the <len> should be constant 6. \n
*           CNcomment:删除指定MAC地址的对端设备信息,MAC地址长度需固定填6字节。CNend
*
* @attention  The memories of <mac> are requested and freed by user APP. \n
*             CNcomment:<mac>内存由用户申请和管理，执行完成后驱动不会释放.CNend
* @param  mac   [IN]     Type  #const unsigned char *, peer device's MAC address.
*                        CNcomment:待删除的对端设备的MAC地址.CNend
* @param  len   [IN]     Type  #unsigned char, length of MAC address which shall be constant 6.
*                        CNcomment:对端设备的MAC地址长度，固定填6字节.CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  NULL
*/
int hi_wifi_any_del_peer(const unsigned char *mac, unsigned char len);

/**
* @ingroup  hi_wifi_any
* @brief    Get ANY peer device's information by index.CNcomment:获取指定索引的对端设备信息。CNend
*
* @par Description:
*           Get ANY peer device's information by index.Index starts from 0 and should not exceed 15. \n
*           CNcomment:获取指定索引的对端设备信息。其中传入的index从0开始指定查询第几个对端，最大不能超过15。CNend
*
* @attention  The memories of <peer> are requested and freed by user APP. \n
*             CNcomment:<peer>内存由用户申请和管理，由驱动填充查询到的信息.CNend
* @param  index           [IN]     Type  #unsigned char, peer device's index, start from 0.
*                                  CNcomment:待查询的对端设备的索引，从0开始.CNend
* @param  peer            [OUT]    Type  #hi_wifi_any_peer_info *, peer device's information.
*                                  CNcomment:查询到的对端设备的信息.CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  NULL
*/
int hi_wifi_any_fetch_peer(unsigned char index, hi_wifi_any_peer_info *peer);

/**
* @ingroup  hi_wifi_any
* @brief    Start ANY scan and register callback to handle scan results. \n
*           CNcomment:发起ANY扫描并注册回调函数处理扫描完成之后的结果。CNend
*
* @par Description:
*           Start ANY scan and register callback to handle scan results. \n
*           The limit to the number of peers discoverd is 32 for a single scan. \n
*           CNcomment:发起ANY扫描并注册回调函数处理扫描完成之后的结果,单次扫描最多返回32个对端设备信息。CNend
*
* @attention  NULL
* @param  p_fn_cb    [IN]     Type  #hi_wifi_any_scan_result_cb, callback function to handle scan results.
*                             CNcomment:由用户实现的回调函数, 扫描完成之后驱动调用该回调处理扫描结果.CNend
*
* @retval #HISI_OK         Excute successfully
* @retval #Other           Error code
* @par Dependency:
*            @li hi_any_api.h: ANY API
* @see  hi_wifi_any_scan_result_cb
*/
int hi_wifi_any_discover_peer(hi_wifi_any_scan_result_cb p_fn_cb);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of hi_any_api.h */

