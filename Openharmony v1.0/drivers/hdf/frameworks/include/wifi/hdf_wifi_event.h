/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup WLAN
 * @{
 *
 * @brief Defines a WLAN module that supports cross-OS migration, component adaptation, and modular assembly and
 * compilation. Driver developers of WLAN vendors can adapt their driver code based on the unified APIs provided
 * by the WLAN module.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hdf_wifi_event.h
 *
 * @brief Declares WLAN driver events.
 *
 * The functions in this file are used to report events such as scanning results, scanning completion, and station
 * disconnection to the WPA interface.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef __HDF_WIFI_EVENT_H__
#define __HDF_WIFI_EVENT_H__

#include "hdf_wifi_cmd.h"
#include "wifi_mac80211_ops.h"
#include "net_device.h"
#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Defines the rate information received or sent over WLAN.
 *
 * @since 1.0
 */
struct RateInfo {
    uint8_t    flags;   /**< Flag field, used to indicate a specific rate transmission type of 802.11n */
    uint8_t    mcs;     /**< Modulation and Coding Scheme (MCS) index of the HT/VHT/HE rate */
    uint16_t   legacy;  /**< 100 kbit/s bit rate defined in 802.11a/b/g */
    uint8_t    nss;     /**< Number of streams (for VHT and HE only) */
    uint8_t    resv;    /**< Reserved */
};

/**
 * @brief Defines parameters related to the WLAN module that works in station mode.
 *
 * @since 1.0
 */
struct StaBssParameters {
    uint8_t  flags;           /**< Flag, used to indicate a specific rate transmission type of 802.11n */
    uint8_t  dtimPeriod;      /**< Delivery Traffic Indication Message (DTIM) period of BSS */
    uint16_t beaconInterval;  /**< Beacon interval */
};

/**
 * @brief Defines the update of the <b>Sta</b> flag.
 *
 * @since 1.0
 */
struct StaFlagUpdate {
    uint32_t mask;  /**< Flag mask */
    uint32_t set;   /**< Flag value */
};

/**
 * @brief Defines station information.
 *
 * @since 1.0
 */
struct StationInfo {
    uint32_t                          filled;           /**< Flag values of relevant structures */
    uint32_t                          connectedTime;    /**< Duration (in seconds) since the last station connection */
    uint32_t                          inactiveTime;     /**< Duration (in milliseconds) since the last station
                                                         * activity
                                                         */
    uint16_t                          llid;             /**< Local mesh ID */
    uint16_t                          plid;             /**< Peer mesh ID */

    uint64_t                          rxBytes;          /**< Received bytes */
    uint64_t                          txBytes;          /**< Transmitted bytes */
    struct RateInfo                   txRate;           /**< Transmission rate */
    struct RateInfo                   rxRate;           /**< Receive rate */

    uint32_t                          rxPackets;        /**< Received data packets */
    uint32_t                          txPackets;        /**< Transmitted data packets */
    uint32_t                          txPetries;        /**< Number of retransmissions */
    uint32_t                          txFailed;         /**< Number of failed transmissions */

    uint32_t                          rxDroppedMisc;    /**< Number of receive failures */
    int32_t                           generation;       /**< Generation number */
    struct StaBssParameters           bssParam;         /**< Current BSS parameters */
    struct StaFlagUpdate              staFlags;         /**< Station flag masks and values */

    int64_t                           offset;           /**< Time offset of station */
    const uint8_t                    *assocReqIes;      /**< Information Elements (IEs) in Association Request */
    uint32_t                          assocReqIesLen;   /**< IE length in Association Request */
    uint32_t                          beaconLossCount;  /**< Number of beacon loss events triggered */

    uint8_t                           plinkState;       /**< Mesh peer state */
    int8_t                            signal;           /**< Signal strength */
    int8_t                            signalAvg;        /**< Average signal strength */
    uint8_t                           resv1;            /**< Reserved */
};

/**
 * @brief Defines authentication information.
 *
 * @since 1.0
 */
struct Auth {
    uint16_t authAlg;          /**< Authentication algorithm */
    uint16_t authTransaction;  /**< Authentication transaction */
    uint16_t statusCode;       /**< Authentication status code */
    uint8_t variable[0];       /**< Algorithm challenge information stored in a flexible array */
};

/**
 * @brief Defines deauthentication information.
 *
 * @since 1.0
 */
struct Deauth {
    uint16_t reasonCode;  /**< Deauthentication cause code */
};

/**
 * @brief Defines station association request.
 *
 * @since 1.0
 */
struct AssocReq {
    uint16_t capabInfo;       /**< WLAN capability information */
    uint16_t listenInterval;  /**< Scan interval */
    uint8_t variable[0];      /**< SSID and rate information stored in a flexible array */
};

/**
 * @brief Defines station association response.
 *
 * @since 1.0
 */
struct AssocResp {
    uint16_t capabInfo;   /**< WLAN capability information */
    uint16_t statusCode;  /**< Status code */
    uint16_t aid;         /**< Authentication ID */
    uint8_t variable[0];  /**< Rate information stored in a flexible array */
};

/**
 * @brief Defines station reassociation request.
 *
 * @since 1.0
 */
struct ReassocReq {
    uint16_t capabInfo;       /**< WLAN capability information */
    uint16_t listenInterval;  /**< Scan interval */
    uint8_t currentAp[6];     /**< Current AP */
    uint8_t variable[0];      /**< SSID and rate information stored in a flexible array */
};

/**
 * @brief Defines station reassociation response.
 *
 * @since 1.0
 */
struct ReassocResp {
    uint16_t capabInfo;   /**< WLAN capability information */
    uint16_t statusCode;  /**< Status code */
    uint16_t aid;         /**< Authentication ID */
    uint8_t variable[0];  /**< Rate information stored in a flexible array */
};

/**
 * @brief Defines station disconnection.
 *
 * @since 1.0
 */
struct Disassoc {
    uint16_t reasonCode;  /**< Cause code */
};

/**
 * @brief Defines the update of the <b>Sta</b> flag.
 *
 * @since 1.0
 */
struct Beacon {
    uint64_t timestamp;   /**< Timestamp */
    uint16_t beaconInt;   /**< Beacon interval */
    uint16_t capabInfo;   /**< WLAN capability information */
    uint8_t variable[0];  /**< SSID and rate information */
};

/**
 * @brief Defines scanning response.
 *
 * @since 1.0
 */
struct ProbeResp {
    uint64_t timestamp;   /**< Timestamp */
    uint16_t beaconInt;   /**< Beacon interval */
    uint16_t capabInfo;   /**< WLAN capability information */
    uint8_t variable[0];  /**< SSID and rate information */
};

/**
 * @brief Defines management frame information.
 *
 * @since 1.0
 */
struct Ieee80211Mgmt {
    uint16_t frameControl;               /**< Frame control field */
    uint16_t duration;                   /**< Duration */
    uint8_t dstAddr[6];                  /**< Destination MAC address */
    uint8_t srcAddr[6];                  /**< Source MAC address */
    uint8_t bssid[6];                    /**< BSS ID */
    uint16_t seqCtrl;                    /**< Sequence control */
    union {
        struct Auth auth;                /**< Authentication Information */
        struct Deauth deauth;            /**< Deauthentication Information */
        struct AssocReq assocReq;        /**< Association request */
        struct AssocResp assocResp;      /**< Association response */
        struct ReassocReq reassocReq;    /**< Re-authentication */
        struct ReassocResp reassocResp;  /**< Re-authentication response */
        struct Disassoc disassoc;        /**< Disconnected */
        struct Beacon beacon;            /**< Beacon frame */
        struct ProbeResp probeResp;      /**< Probe response frame */
    } u;
};

/**
 * @brief Represents the scanned BSS information.
 *
 * @since 1.0
 */
struct ScannedBssInfo {
    int32_t                  signal;   /**< Signal strength */
    int16_t                  freq;     /**< Center frequency of the channel where the BSS is located */
    uint8_t                  arry[2];  /**< Reserved */
    uint32_t                 mgmtLen;  /**< Management frame length */
    struct Ieee80211Mgmt    *mgmt;     /**< Start address of the management frame */
};

/**
 * @brief Defines association results.
 *
 * @since 1.0
 */
struct ConnetResult {
    uint8_t   bssid[ETH_ADDR_LEN];  /**< MAC address of the AP associated with the station */
    uint16_t  statusCode;           /**< 16-bit status code defined in the IEEE protocol */
    uint8_t  *rspIe;                /**< Association response IE */
    uint8_t  *reqIe;                /**< Association request IE */
    uint32_t  reqIeLen;             /**< Length of the association request IE */
    uint32_t  rspIeLen;             /**< Length of the association response IE */
    uint16_t  connectStatus;        /**< Connection status */
    uint16_t  freq;                 /**< Frequency of the AP */
};

/**
 * @brief Enumerates MLME management statuses, indicating whether a device is successfully associated or
 * fails to be associated.
 *
 * @since 1.0
 */
enum WifiHmacMgmtStatus {
    WIFI_HMAC_MGMT_SUCCESS = 0,     /**< Association succeeds */
    WIFI_HMAC_MGMT_INVALID = 1,     /**< Association fails */
    WIFI_HMAC_MGMT_TIMEOUT = 2,     /**< Association timeout */
    WIFI_HMAC_MGMT_REFUSED = 3,     /**< Association refused */
    WIFI_HMAC_MGMT_TOMANY_REQ = 4,  /**< Repeated association request */
    WIFI_HMAC_MGMT_ALREADY_BSS = 5  /**< Associated with the BSS */
};

/**
 * @brief Reports a new STA event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param macAddr Indicates the pointer to the MAC address of the station. This parameter cannot be null.
 * @param addrLen Indicates the length of the MAC address of the station. The length is fixed to six bytes.
 * @param info Indicates the pointer to the station information.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventNewSta(const struct NetDevice *netdev, const uint8_t *macAddr, uint8_t addrLen,
    const struct StationInfo *info);

/**
 * @brief Reports a station deletion event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param macAddr Indicates the pointer to the MAC address of the station. This parameter cannot be null.
 * @param addrLen Indicates the length of the MAC address of the station. The length is fixed to six bytes.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventDelSta(struct NetDevice *netdev, const uint8_t *macAddr, uint8_t addrLen);

/**
 * @brief Reports a scanned BSS event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param wiphy Indicates the pointer to the physical layer of the wireless network. This parameter cannot be null.
 * @param channel Indicates the pointer to the channel information. This parameter cannot be null.
 * @param bssInfo Indicates the pointer to the BSS information. This parameter cannot be null.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventInformBssFrame(const struct NetDevice *netdev, struct Wiphy *wiphy,
    const struct Ieee80211Channel *channel, const struct ScannedBssInfo *bssInfo);

/**
 * @brief Reports a scanning completion event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param status Indicates the scanning completion status. Value <b>0</b> indicates that the scanning is successful,
 * and other values indicate that the scanning fails.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventScanDone(const struct NetDevice *netdev, WifiScanStatus status);

/**
 * @brief Reports a connection result event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param result Indicates the pointer to the connection result. This parameter cannot be null.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventConnectResult(const struct NetDevice *netdev, const struct ConnetResult *result);

/**
 * @brief Reports a disconnection event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param reason Indicates the reason for disconnection.
 * @param ie Indicates the pointer to the deauth/disassoc frame IE.
 * @param ieLen Indicates the length of the deauth/disassoc IE.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventDisconnected(const struct NetDevice *netdev, uint16_t reason, const uint8_t *ie, uint32_t len);

/**
 * @brief Reports a transmission management status event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param buf Indicates the pointer to the transmission management frame. This parameter cannot be null.
 * @param len Indicates the length of the transmission management frame.
 * @param ack Indicates whether the transmission management frame is acknowledged.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventMgmtTxStatus(const struct NetDevice *netdev, const uint8_t *buf, size_t len, uint8_t ack);

/**
 * @brief Reports a receive management status event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param freq Indicates the frequency of receiving management frame.
 * @param sigMbm Indicates the signal strength (in dBm).
 * @param buf Indicates the pointer to the receive management frame. This parameter cannot be null.
 * @param len Indicates the length of the receive management frame.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventRxMgmt(const struct NetDevice *netdev, int32_t freq, int32_t sigMbm,
    const uint8_t *buf, size_t len);

/**
 * @brief Reports a CSA channel switching event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 * @param freq Indicates the frequency of the channel.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventCsaChannelSwitch(const struct NetDevice *netdev, int32_t freq);

/**
 * @brief Reports a timeout disconnection event.
 *
 * @param netdev Indicates the pointer to the network device. This parameter cannot be null.
 *
 * @return Returns <b>0</b> if the event is reported successfully; returns <b>-1</b> otherwise.
 *
 * @since 1.0 */
int32_t HdfWifiEventTimeoutDisconnected(const struct NetDevice *netdev);

/**
 * @brief Reports the event of receiving the EAPOL frame and notifies WPA to read the EAPOL frame.
 *
 * @param name Indicates the pointer to the network port name, for example, <b>wlan0</b>.
 * @param context Indicates the pointer to the context. This parameter is reserved.
 *
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 *
 * @since 1.0
 */
int32_t HdfWifiEventEapolRecv(const char *name, void *context);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* __HDF_WIFI_EVENT_H__ */

