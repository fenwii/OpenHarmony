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
 * @file wifi_mac80211_ops.h
 *
 * @brief Declares Media Access Control (MAC) APIs and functions related to control flows.
 *
 * This file declares APIs for scanning, connection, disconnection, and mode conversion, as well as data
 * structures of the parameters of these APIs.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef _WIFI_MAC80211_OPS_H_
#define _WIFI_MAC80211_OPS_H_

#include "net_device.h"
#include "hdf_wifi_cmd.h"

#define WLAN_MAC_ADDR_LEN 6
/**
 * @brief Enumerates setting types of MAC addresses.
 *
 * @since 1.0
 */
enum MacSetType {
    MAC_BEACON_SET = 0, /**< Setting a beacon MAC address */
    MAC_BEACON_ADD = 1, /**< Adding a beacon MAC address */
};

/**
 * @brief Describes a key.
 *
 * @since 1.0
 */
struct KeyParams {
    uint8_t *key;     /**< Key content */
    uint8_t *seq;     /**< Content of a Temporal Key Integrity Protocol (TKIP) or Counter Mode Cipher Block Chaining
                       * Message Authentication Code Protocol (CCMP) key
                       */
    int32_t keyLen;   /**< Key length */
    int32_t seqLen;   /**< Length of a TKIP or CCMP key */
    uint32_t cipher;  /**< Cipher suite */
};

/**
 * @brief Enumerates frequency bands.
 *
 * @since 1.0
 */
enum Ieee80211Band {
    IEEE80211_BAND_2GHZ,  /**< 2.4 GHz */
    IEEE80211_BAND_5GHZ,  /**< 5 GHz */
    IEEE80211_NUM_BANDS   /**< Reserved */
};

#define IEEE80211_CHANNEL_RESV 3
/**
 * @brief Describes a communication channel.
 *
 * @since 1.0
 */
struct Ieee80211Channel {
    enum Ieee80211Band band;               /**< Frequency band, either 2.4 GHz or 5 GHz */
    uint16_t centerFreq;                   /**< Center frequency */
    uint16_t hwValue;                      /**< Hardware information */
    uint32_t flags;                        /**< WLAN channel flag */
    int32_t maxAntennaGain;                /**< Maximum antenna gain, in dBi */
    int32_t maxPower;                      /**< Maximum transmit power, in dBm */
    int8_t beaconFound;                    /**< When a beacon frame is found in this channel */
    uint8_t resv[IEEE80211_CHANNEL_RESV];  /**< Reserved field */
    uint32_t origFlags;                    /**< Channel flags */
    int32_t origMag;                       /**< Reserved field */
    int32_t origMpwr;                      /**< Reserved field */
};

#define IEEE80211_RATE_RESV 2
/**
 * @brief Describes the IEEE 802.11 rate.
 *
 * @since 1.0
 */
struct Ieee80211Rate {
    uint32_t flags;                    /**< Rate flag */
    uint16_t bitrate;                  /**< Bit rate, in 100 kbit/s */
    uint16_t hwValue;                  /**< Hardware information */
    uint16_t hwValueShort;             /**< Hardware information specified when a short preamble is used */
    uint8_t rsv[IEEE80211_RATE_RESV];  /**< Reserved field */
};

#define IEEE80211_HT_MCS_MASK_LEN 10
#define IEEE80211_MACINFO_RESV 3
/**
 * @brief Describes IEEE 802.11 Modulation and Coding Scheme (MCS) information.
 *
 * @since 1.0
 */
struct Ieee80211McsInfo {
    uint8_t rxMask[IEEE80211_HT_MCS_MASK_LEN];  /**< Mask for receiving data */
    uint16_t rxHighest;                         /**< Maximum rate for receiving data */
    uint8_t txParams;                           /**< Parameters for sending data */
    uint8_t reserved[IEEE80211_MACINFO_RESV];   /**< Reserved field */
};

#define IEEE80211_STAHTCAP_RESV 3
/**
 * @brief Describes the IEEE 802.11 high-throughput (HT) capability.
 *
 * @since 1.0
 */
struct Ieee80211StaHtCap {
    uint16_t cap;                             /**< HT capability table provided in 802.11n */
    uint8_t htSupported;                      /**< Whether the station supports HT */
    uint8_t ampduFactor;                      /**< Maximum length of an aggregated MAC Protocol Data Unit (A-MPDU) */
    uint8_t ampduDensity;                     /**< Minimum MPDU start spacing */
    uint8_t aucRsv[IEEE80211_STAHTCAP_RESV];  /**< Reserved field */
    struct Ieee80211McsInfo mcs;              /**< MCS rate */
};

/**
 * @brief Describes IEEE 802.11 band information.
 *
 * @since 1.0
 */
struct Ieee80211SupportedBand {
    struct Ieee80211Channel *channels;  /**< An array of supported channels */
    struct Ieee80211Rate *bitrates;     /**< An array of supported bit rates */
    enum Ieee80211Band band;            /**< Band matching this data structure description */
    int32_t nChannels;                  /**< Length of the array of supported channels */
    int32_t nBitrates;                  /**< Length of the array of supported bit rates */
    struct Ieee80211StaHtCap htCap;     /**< HT capability */
};

#define WIPHY_RSV_SIZE 2
#define WIPHY_PRIV_SIZE 4
/**
 * @brief Describes a wiphy device.
 *
 * @since 1.0
 */
struct Wiphy {
    uint8_t permAddr[WLAN_MAC_ADDR_LEN];  /**< Permanent MAC address of the wiphy device. For its length,
                                           * see {@link WLAN_MAC_ADDR_LEN}.
                                           */
    uint8_t addrMask[WLAN_MAC_ADDR_LEN];  /**< MAC address mask of the wiphy device. If the device supports multiple
                                           * virtual MAC addresses, the bit whose value is <b>1</b> in the mask
                                           * represents a variable part of the MAC address.
                                           */
    uint32_t flags;                       /**< Wiphy device attributes */
    uint8_t signalType;                   /**< Signal type */
    uint8_t maxScanSsids;                 /**< Maximum number of scanned service set identifiers (SSIDs) */
    uint16_t interfaceModes;              /**< Bitmask of an API type that is valid for the wiphy device */
    uint16_t maxScanIeLen;                /**< Maximum SSID length */
    uint8_t aucRsv[WIPHY_RSV_SIZE];       /**< Manual alignment of data structures */
    int32_t nCipherSuites;                /**< Number of supported cipher suites */
    const uint32_t *cipherSuites;         /**< Supported cipher suites */
    uint32_t fragThreshold;               /**< Fragment threshold */
    uint32_t rtsThreshold;                /**< Request To Send (RTS) threshold */
    struct Ieee80211SupportedBand *bands[IEEE80211_NUM_BANDS];
                                          /**< Supported bands */
    uint8_t priv[WIPHY_PRIV_SIZE];        /**< Reserved field */
};

#define IEEE80211_MAX_SSID_LEN 32
/**
 * @brief Describes an SSID.
 *
 * @since 1.0
 */
struct WifiSsid {
    uint8_t ssid[IEEE80211_MAX_SSID_LEN];  /**< SSID content, which contains a maximum of 32 bytes */
    uint8_t ssidLen;                       /**< SSID length */
};

/**
 * @brief Enumerates channel types.
 *
 * @since 1.0
 */
enum WifiChannelType {
    WIFI_CHAN_NO_HT,     /**< non-HT channel */
    WIFI_CHAN_HT20,      /**< 20 MHz HT channel */
    WIFI_CHAN_HT40MINUS, /**< 40 MHz minus HT channel (The channel is formed by two 20 MHz HT channels, one as
                          * the main channel and the other as the auxiliary channel. The center frequency of the main
                          * channel is lower than that of the auxiliary channel.)
                          */
    WIFI_CHAN_HT40PLUS   /**< 40 MHz plus HT channel (The channel is formed by two 20 MHz HT channels, one as
                          * the main channel and the other as the auxiliary channel. The center frequency of the main
                          * channel is higher than that of the auxiliary channel.)
                          */
};

/**
 * @brief Describes a communication channel.
 *
 * @since 1.0
 */
struct ChannelDef {
    struct Ieee80211Channel *chan;    /**< Channel information */
    enum WifiChannelType width;       /**< Bandwidth */
    int32_t centerFreq1;              /**< Center frequency 1 */
    int32_t centerFreq2;              /**< Center frequency 2 */
};

#define WIRELESS_DEV_RESV_SIZE 3
/**
 * @brief Describes a wireless device.
 *
 * @since 1.0
 */
struct WirelessDev {
    struct NetDevice *netdev;              /**< Network device */
    struct Wiphy *wiphy;                   /**< Wiphy device */
    uint8_t iftype;                        /**< API type */
    uint8_t resv[WIRELESS_DEV_RESV_SIZE];  /**< Reserved field */
    struct ChannelDef presetChandef;       /**< Channel information */
};

#define MAX_SCAN_CHANNELS 14
#define SCAN_REQUEST_RESV_SIZE 2
/**
 * @brief Describes scan request parameters.
 *
 * @since 1.0
 */
struct WifiScanRequest {
    struct WifiSsid *ssids;                                /**< SSIDs to scan for */
    uint32_t nSsids;                                       /**< Number of SSIDs to scan for */
    uint32_t nChannels;                                    /**< Number of channels to scan for */
    uint32_t ieLen;                                        /**< IEEE 802.11 buffer length */
    struct Wiphy *wiphy;                                   /**< A specified wiphy device to scan for */
    struct NetDevice *dev;                                 /**< A specified network device to scan for */
    struct WirelessDev *wdev;                              /**< A specified wireless device to scan for */
    uint8_t aborted;                                       /**< Whether to abort the scan */
    uint8_t prefixSsidScanFlag;                            /**< Reserved field */
    uint8_t resv[SCAN_REQUEST_RESV_SIZE];                  /**< Reserved field */
    uint8_t *ie;                                           /**< IEEE 802.11 buffer */
    struct Ieee80211Channel *channels[MAX_SCAN_CHANNELS];  /**< Channels to scan for. For details,
                                                            * see {@link MAX_SCAN_CHANNELS}.
                                                            */
};

#define NL80211_MAX_NR_CIPHER_SUITES 5
#define NL80211_MAX_NR_AKM_SUITES 2
/**
 * @brief Describes cryptography settings.
 *
 * @since 1.0
 */
struct CryptoSettings {
    uint32_t wpaVersions;           /**< WPA version */
    uint32_t cipherGroup;           /**< Cipher group */
    int32_t n_ciphersPairwise;      /**< Number of unicast ciphers supported by the access point (AP) */
    uint32_t ciphersPairwise[NL80211_MAX_NR_CIPHER_SUITES];
                                    /**< Unicast cipher suite. For details, see {@link NL80211_MAX_NR_CIPHER_SUITES}. */
    int32_t n_akmSuites;            /**< Number of authentication and key management (AKM) suites */
    uint32_t akmSuites[NL80211_MAX_NR_AKM_SUITES];
                                    /**< AKM suite data. For details, see {@link NL80211_MAX_NR_AKM_SUITES}. */
    uint16_t controlPortEthertype;  /**< Data can be transmitted over an unauthenticated port. */
    int8_t controlPort;             /**< Whether the user space control port is authorized. The value <b>true</b>
                                     * indicates that the user space control port is unauthorized.
                                     */
    int8_t controlPortNoEncrypt;    /**< Whether to encrypt frames transmitted over the control port.
                                     * The value <b>1</b> indicates that the frames are not encrypted.
                                     */
};

#define ETH_ADDR_LEN 6
/**
 * @brief Describes the device MAC address.
 *
 * @since 1.0
 */
struct MacAddress {
    uint8_t addr[ETH_ADDR_LEN];  /**< Device MAC address */
};

#define WIFI_CONNECT_PARM_RESV_SIZE 3
/**
 * @brief Describes parameters for a connection request.
 *
 * @since 1.0
 */
typedef struct WifiConnectParams {
    struct Ieee80211Channel *channel;  /**< Connection channel. If this parameter is not specified, the connection
                                        * channel is automatically obtained from the scan result.
                                        */
    uint8_t *bssid;                    /**< AP basic service set identifier (BSSID). If this parameter is not
                                        * specified, the AP BSSID is automatically obtained from the scan result.
                                        */
    uint8_t *ssid;                     /**< SSID */
    uint8_t *ie;                       /**< IEEE 802.11 information required for the connection */
    uint32_t ssidLen;                  /**< SSID length */
    uint32_t ieLen;                    /**< IEEE 802.11 length */
    struct CryptoSettings crypto;      /**< Cryptography information */
    const uint8_t *key;                /**< Wired Equivalent Privacy (WEP) key used for Shared Key
                                        * Authentication (SKA)
                                        */
    uint8_t authType;                  /**< Authorization type */
    uint8_t privacy;                   /**< Whether to use a privacy-enabled AP */
    uint8_t keyLen;                    /**< Key length */
    uint8_t keyIdx;                    /**< Index of the WEP key used for SKA */
    uint8_t mfp;                       /**< Whether to enable Management Frame Protection (MFP) */
    uint8_t aucResv[WIFI_CONNECT_PARM_RESV_SIZE];
                                       /**< Reserved field */
}  WifiConnectParams;

/**
 * @brief Describes virtual API parameters.
 *
 * @since 1.0
 */
struct VifParams {
    int32_t use4Addr;  /**< Whether to use a frame containing four addresses */
    uint8_t *macAddr;  /**< MAC address */
};

/**
 * @brief Describes parameters for canceling a connection.
 *
 * @since 1.0
 */
struct StationDelParameters {
    const uint8_t *mac;   /**< MAC address of the station to which the connection is to be canceled */
    uint8_t subtype;      /**< Cancellation type */
    uint16_t reasonCode;  /**< Cause of the cancellation */
};

/**
 * @brief Describes MAC configuration parameters.
 *
 * @since 1.0
 */
typedef struct MacConfigParam {
    uint8_t mac[WLAN_MAC_ADDR_LEN];  /**< MAC address. For details about its length, see {@link WLAN_MAC_ADDR_LEN}. */
    uint8_t p2pMode;                 /**< Whether the peer-to-peer (P2P) mode is used. */
} Mac80211SetMacParam;

#define OAL_IEEE80211_MAX_SSID_LEN 32
/**
 * @brief Describes disconnection parameters.
 *
 * @since 1.0
 */
typedef struct {
    uint8_t macAddr[WLAN_MAC_ADDR_LEN];  /**< Device MAC address */
    uint16_t reasonCode;                 /**< Disconnection reason code */
} Mac80211DisconnectParam;

#define MAC80211_SSIDS_AUC_SIZE 3
/**
 * @brief Describes SSIDs.
 *
 * @since 1.0
 */
typedef struct {
    uint8_t aucSsid[OAL_IEEE80211_MAX_SSID_LEN]; /**< SSID array */
    uint8_t ssidLen;                             /**< SSID length */
    uint8_t aucArry[MAC80211_SSIDS_AUC_SIZE];    /**< AuC data array */
} Mac80211Ssids;

#define WLAN_SCAN_REQ_MAX_BSS 2
/**
 * @brief Describes beacon parameters.
 *
 * @since 1.0
 */
typedef struct {
    int32_t interval;            /**< Beacon interval */
    int32_t dtimPeriod;          /**< Delivery Traffic Indication Message (DTIM) interval */
    WifiBeaconData *beaconData;  /**< Beacon frame data */
    uint8_t hiddenSsid;          /**< Whether to hide the SSID */
    uint8_t operationType;       /**< Operation type */
} Mac80211beaconParam;

/**
 * @brief Describes MAC-layer control APIs that need to be implemented by the driver.
 *
 * @since 1.0
 */
struct WifiMac80211Ops {
    int32_t (*changeVirtualIntf)(NetDevice *netDev, uint8_t iftype, uint32_t *flags,
        struct VifParams *params);                                                   /**< Changing virtual APIs */
    int32_t (*setSsid)(NetDevice *netDev, const uint8_t *ssid, uint32_t ssidLen);    /**< Setting the SSID */
    int32_t (*setMeshId)(NetDevice *netDev, const char *meshId, uint32_t meshIdLen); /**< Setting the mesh ID */
    int32_t (*setMacAddr)(NetDevice *netDev, Mac80211SetMacParam *param);            /**< Setting the MAC address */
    int32_t (*changeBeacon)(NetDevice *netDev, Mac80211beaconParam *param);          /**< Setting the beacon frame
                                                                                      * based on specified parameters
                                                                                      */
    int32_t (*setChannel)(NetDevice *netDev);                                        /**< Setting the channel */
    int32_t (*addKey)(struct NetDevice *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr,
        struct KeyParams *params);                                                   /**< Adding a key with specified
                                                                                      * parameters
                                                                                      */
    int32_t (*delKey)(struct NetDevice *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr);
                                                                                     /**< Deleting a key based on a
                                                                                      * specified MAC address
                                                                                      */
    int32_t (*setDefaultKey)(struct NetDevice *netdev, uint8_t keyIndex, bool unicast, bool multicas);
                                                                                     /**< Setting the default key */
    int32_t (*startAp)(NetDevice *netDev);                                           /**< Starting an AP */
    int32_t (*stopAp)(NetDevice *netDev);                                            /**< Stopping an AP */
    int32_t (*delStation)(NetDevice *netDev, const uint8_t *macAddr);                /**< Deleting a station with a
                                                                                      * specified MAC address
                                                                                      */
    int32_t (*connect)(NetDevice *netDev, WifiConnectParams *param);                 /**< Starting a connection based
                                                                                      * on the specified parameters
                                                                                      */
    int32_t (*disconnect)(NetDevice *netDev, uint16_t reasonCode);                   /**< Canceling a connection */
    int32_t (*startScan)(NetDevice *netDev, struct WifiScanRequest *param);          /**< Starting a scan based on the
                                                                                      * specified parameters
                                                                                      */
    int32_t (*abortScan)(NetDevice *netDev);                                         /**< Stopping a scan */
};

/**
 * @brief Registers a {@link WifiMac80211Ops} object.
 *
 * @param ops Indicates the pointer to the {@link WifiMac80211Ops} object to register.
 *
 * @return Returns <b>0</b> if the {@link WifiMac80211Ops} object is registered successfully;
 * returns a non-zero value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t Mac80211RegisterOps(struct WifiMac80211Ops *ops) __attribute__((weak));

/**
 * @brief Obtains the {@link WifiMac80211Ops} object that the driver needs to implement.
 *
 * @return Returns the pointer to the {@link WifiMac80211Ops} object.
 *
 * @since 1.0
 * @version 1.0
 */
struct WifiMac80211Ops *Mac80211GetOps(void);

#endif // _WIFI_MAC80211_OPS_H_
