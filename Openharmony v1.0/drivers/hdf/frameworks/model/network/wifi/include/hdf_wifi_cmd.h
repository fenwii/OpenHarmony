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

#ifndef _WIFI_HAL_H_
#define _WIFI_HAL_H_

#include <stdint.h>
#include <stddef.h>
#include <net/if.h>
#include "hdf_device_desc.h"
#include "hdf_sbuf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define SUCC 0
#define EFAIL 1
#define EINVAL 22

#define ETH_ADDR_LEN 6
#define MAX_SSID_LEN 32
#define MAX_NR_CIPHER_SUITES 5
#define MAX_NR_AKM_SUITES 2
#define WPAS_MAX_SCAN_SSIDS 16
#define DRIVER_MAX_SCAN_SSIDS 2

#define SCAN_AP_LIMIT 64
#define SCAN_TIME_OUT 5

#define NETDEV_UP 0x0001
#define NETDEV_DOWN 0x0002

#define EAPOL_PKT_BUF_SIZE 800
#define CHECK_DHCP_TIME 30

#define WPA_WEP40_KEY_LEN 5
#define WPA_WEP104_KEY_LEN 13

typedef enum {
    WPA_VERSION_1 = 1 << 0,
    WPA_VERSION_2 = 1 << 1,
} WpaVersions;

typedef enum {
    WIFI_CHAN_WIDTH_20_NOHT,
    WIFI_CHAN_WIDTH_20,
    WIFI_CHAN_WIDTH_40,
    WIFI_CHAN_WIDTH_BUTT
} WifiChannelWidth;

typedef enum {
    WIFI_DISCONNECT,
    WIFI_CONNECT,
} WifiConnectStatus;

typedef enum {
    WIFI_KEYTYPE_GROUP,
    WIFI_KEYTYPE_PAIRWISE,
    WIFI_KEYTYPE_PEERKEY,
    WIFI_KEYTYPE_BUTT
} WifiKeyType;

typedef enum {
    WIFI_KEY_DEFAULT_TYPE_INVALID,
    WIFI_KEY_DEFAULT_TYPE_UNICAST,
    WIFI_KEY_DEFAULT_TYPE_MULTICAST,
    WIFI_KEY_DEFAULT_TYPES
} WifiKeyDefaultType;

typedef enum {
    WIFI_NO_SSID_HIDING,
    WIFI_HIDDEN_SSID_ZERO_LEN,
    WIFI_HIDDEN_SSID_ZERO_CONTENTS
} WifiHiddenSsid;

typedef enum {
    WIFI_WPA_CMD_SET_AP = 0,
    WIFI_WPA_CMD_NEW_KEY,
    WIFI_WPA_CMD_DEL_KEY,
    WIFI_WPA_CMD_SET_KEY,
    WIFI_WPA_CMD_SEND_MLME,
    WIFI_WPA_CMD_SEND_EAPOL = 5,
    WIFI_WPA_CMD_RECEIVE_EAPOL,
    WIFI_WPA_CMD_ENALBE_EAPOL,
    WIFI_WPA_CMD_DISABLE_EAPOL,
    WIFI_WPA_CMD_GET_ADDR,
    WIFI_WPA_CMD_SET_POWER = 10,
    WIFI_WPA_CMD_SET_MODE,
    WIFI_WPA_CMD_GET_HW_FEATURE,
    WIFI_WPA_CMD_STOP_AP,
    WIFI_WPA_CMD_DEL_VIRTUAL_INTF,
    WIFI_WPA_CMD_SCAN = 15,
    WIFI_WPA_CMD_DISCONNECT,
    WIFI_WPA_CMD_ASSOC,
    WIFI_WPA_CMD_SET_NETDEV,
    WIFI_WPA_CMD_SET_AP_WPS_P2P_IE,
    WIFI_WPA_CMD_CHANGE_BEACON = 20,
    WIFI_WPA_CMD_DHCP_START,
    WIFI_WPA_CMD_DHCP_STOP,
    WIFI_WPA_CMD_DHCP_SUCC_CHECK,
    WIFI_WPA_CMD_SET_REKEY_INFO,
    WIFI_WPA_CMD_SET_PM_ON = 25,
    WIFI_WPA_CMD_IP_NOTIFY_DRIVER,
    WIFI_WPA_CMD_SET_MAX_STA,
    WIFI_WPA_CMD_STA_REMOVE,
    WIFI_WPA_CMD_SEND_ACTION,
    WIFI_WPA_CMD_SET_MESH_USER = 30,
    WIFI_WPA_CMD_SET_MESH_GTK,
    WIFI_WPA_CMD_EN_AUTO_PEER,
    WIFI_WPA_CMD_EN_ACCEPT_PEER,
    WIFI_WPA_CMD_EN_ACCEPT_STA,
    WIFI_WPA_CMD_ADD_IF = 35,
    WIFI_WPA_CMD_PROBE_REQUEST_REPORT,
    WIFI_WPA_CMD_REMAIN_ON_CHANNEL,
    WIFI_WPA_CMD_CANCEL_REMAIN_ON_CHANNEL,
    WIFI_WPA_CMD_SET_P2P_NOA,
    WIFI_WPA_CMD_SET_P2P_POWERSAVE = 40,
    WIFI_WPA_CMD_REMOVE_IF,
    WIFI_WPA_CMD_GET_P2P_MAC_ADDR,
    WIFI_WPA_CMD_GET_DRIVER_FLAGS,
    WIFI_WPA_CMD_SET_USR_APP_IE,
    WIFI_WPA_CMD_BUTT
} WifiWPACmdType;

typedef enum {
    WIFI_WPA_EVENT_NEW_STA = 0,
    WIFI_WPA_EVENT_DEL_STA,
    WIFI_WPA_EVENT_RX_MGMT,
    WIFI_WPA_EVENT_TX_STATUS,
    WIFI_WPA_EVENT_SCAN_DONE,
    WIFI_WPA_EVENT_SCAN_RESULT = 5,
    WIFI_WPA_EVENT_CONNECT_RESULT,
    WIFI_WPA_EVENT_DISCONNECT,
    WIFI_WPA_EVENT_MESH_CLOSE,
    WIFI_WPA_EVENT_NEW_PEER_CANDIDATE,
    WIFI_WPA_EVENT_REMAIN_ON_CHANNEL = 10,
    WIFI_WPA_EVENT_CANCEL_REMAIN_ON_CHANNEL,
    WIFI_WPA_EVENT_CHANNEL_SWITCH,
    WIFI_WPA_EVENT_EAPOL_RECV,
    WIFI_WPA_EVENT_TIMEOUT_DISCONN,
    WIFI_WPA_EVENT_BUTT
} WifiWpaEventType;

typedef enum {
    WIFI_AUTHTYPE_OPEN_SYSTEM = 0,
    WIFI_AUTHTYPE_SHARED_KEY,
    WIFI_AUTHTYPE_FT,
    WIFI_AUTHTYPE_EAP,
    WIFI_AUTHTYPE_SAE,
    WIFI_AUTHTYPE_AUTOMATIC,
    WIFI_AUTHTYPE_BUTT
} WifiAuthType;

typedef enum {
    WIFI_SCAN_SUCCESS,
    WIFI_SCAN_FAILED,
    WIFI_SCAN_REFUSED,
    WIFI_SCAN_TIMEOUT
} WifiScanStatus;

typedef enum {
    WIFI_MFP_NO,
    WIFI_MFP_OPTIONAL,
    WIFI_MFP_REQUIRED,
} WifiMfp;

typedef enum {
    WIFI_IFTYPE_ADHOC,
    WIFI_IFTYPE_STATION,
    WIFI_IFTYPE_AP,
    WIFI_IFTYPE_AP_VLAN,
    WIFI_IFTYPE_WDS,
    WIFI_IFTYPE_MONITOR,
    WIFI_IFTYPE_MESH_POINT,
    WIFI_IFTYPE_P2P_CLIENT,
    WIFI_IFTYPE_P2P_GO,
    WIFI_IFTYPE_P2P_DEVICE,
    WIFI_IFTYPE_MAX,
} WifiIfType;

typedef enum {
    WIFI_PHY_MODE_11N = 0,
    WIFI_PHY_MODE_11G = 1,
    WIFI_PHY_MODE_11B = 2,
    WIFI_PHY_MODE_BUTT
} WifiPhyMode;

typedef struct {
    uint8_t status;
    WifiIfType ifType;
    WifiPhyMode mode;
} WifiSetNewDev;

typedef struct {
    int32_t numRates;
    int32_t mode;
} WifiModes;

typedef struct {
    int32_t reassoc;
    size_t ieLen;
    uint8_t *ie;
    uint8_t macAddr[ETH_ADDR_LEN];
    uint8_t resv[2];
} WifiNewStaInfo;

typedef struct {
    uint8_t *buf;
    uint32_t len;
    int32_t sigMbm;
    int32_t freq;
} WifiRxMgmt;

typedef struct {
    uint8_t *buf;
    uint32_t len;
    uint8_t ack;
    uint8_t resv[3];
} WifiTxStatus;

typedef struct {
    uint32_t freq;
    size_t dataLen;
    uint8_t *data;
    uint64_t *cookie;
} WifiMlmeData;

typedef struct {
    size_t headLen;
    size_t tailLen;
    uint8_t *head;
    uint8_t *tail;
} WifiBeaconData;

typedef struct {
    uint8_t *dst;
    uint8_t *src;
    uint8_t *bssid;
    uint8_t *data;
    size_t dataLen;
} WifiActionData;

typedef struct {
    int32_t mode;
    int32_t freq;
    int32_t channel;

    /* for HT */
    int32_t htEnabled;

    /*
     * 0 = HT40 disabled, -1 = HT40 enabled,
     * secondary channel below primary, 1 = HT40
     * enabled, secondary channel above primary
     */
    int32_t secChannelOffset;

    /* for VHT */
    int32_t vhtEnabled;

    /*
     * valid for both HT and VHT, center_freq2 is non-zero
     * only for bandwidth 80 and an 80+80 channel
     */
    int32_t centerFreq1;
    int32_t centerFreq2;
    int32_t bandwidth;
} WifiFreqParams;

typedef struct {
    int32_t type;
    uint32_t keyIdx;
    uint32_t keyLen;
    uint32_t seqLen;
    uint32_t cipher;
    uint8_t *addr;
    uint8_t *key;
    uint8_t *seq;
    uint8_t def;
    uint8_t defMgmt;
    uint8_t defaultTypes;
    uint8_t resv;
} WifiKeyExt;

typedef struct {
    WifiFreqParams freqParams;
    WifiBeaconData beaconData;
    size_t ssidLen;
    int32_t beaconInterval;
    int32_t dtimPeriod;
    uint8_t *ssid;
    uint8_t hiddenSsid;
    uint8_t authType;
    size_t meshSsidLen;
    uint8_t *meshSsid;
} WifiApSetting;

typedef struct {
    uint8_t bssid[ETH_ADDR_LEN];
    uint8_t iftype;
    uint8_t resv;
} WifiSetMode;

typedef struct {
    uint8_t *buf;
    uint32_t len;
} WifiTxEapol;

typedef struct {
    uint8_t *buf;
    uint32_t len;
} WifiRxEapol;

typedef struct {
    void *callback;
    void *contex;
} WifiEnableEapol;

typedef struct {
    uint16_t channel;
    uint32_t freq;
    uint32_t flags;
} WifiIeee80211Channel;

typedef struct {
    int32_t channelNum;
    uint16_t bitrate[12];
    uint16_t htCapab;
    uint8_t resv[2];
    WifiIeee80211Channel iee80211Channel[14];
} WifiHwFeatureData;

typedef struct {
    uint8_t ssid[MAX_SSID_LEN];
    size_t ssidLen;
} WifiDriverScanSsid;

typedef struct {
    WifiDriverScanSsid *ssids;
    int32_t *freqs;
    uint8_t *extraIes;
    uint8_t *bssid;
    uint8_t numSsids;
    uint8_t numFreqs;
    uint8_t prefixSsidScanFlag;
    uint8_t fastConnectFlag;
    int32_t extraIesLen;
} WifiScan;

typedef struct {
    uint32_t freq;
    uint32_t duration;
} WifiOnChannel;


typedef struct {
    uint8_t ifname[IFNAMSIZ];
} WifiIfRemove;

typedef struct {
    uint8_t type;
    uint8_t macAddr[ETH_ADDR_LEN];
    uint8_t resv;
} WifiGetP2pAddr;

typedef struct {
    WifiIfType iftype;
    uint8_t *macAddr;
} WifiIftypeMacAddr;

typedef struct {
    uint64_t drvFlags;
} WifiGetDrvFlags;

typedef struct {
    int32_t freq;
} WifiChannelSwitch;

typedef struct {
    uint32_t wpaVersions;
    uint32_t cipherGroup;
    int32_t nCiphersPairwise;
    uint32_t ciphersPairwise[MAX_NR_CIPHER_SUITES];
    int32_t nAkmSuites;
    uint32_t akmSuites[MAX_NR_AKM_SUITES];
} WifiCryptoSetting;

typedef struct {
    uint8_t *bssid;
    uint8_t *ssid;
    uint8_t *ie;
    uint8_t *key;
    uint8_t authType;
    uint8_t privacy;
    uint8_t keyLen;
    uint8_t keyIdx;
    uint8_t mfp;
    uint8_t rsv[3];
    uint32_t freq;
    uint32_t ssidLen;
    uint32_t ieLen;
    WifiCryptoSetting *crypto;
} WifiAssociateParams;

typedef struct {
    uint8_t *reqIe;
    size_t reqIeLen;
    uint8_t *respIe;
    size_t respIeLen;
    uint8_t bssid[ETH_ADDR_LEN];
    uint8_t rsv[2];
    uint16_t status;
    uint16_t freq;
} WifiConnectResult;

typedef struct {
    int32_t flags;
    uint8_t bssid[ETH_ADDR_LEN];
    int16_t caps;
    int32_t freq;
    int16_t beaconInt;
    int32_t qual;
    uint32_t beaconIeLen;
    int32_t level;
    uint32_t age;
    uint32_t ieLen;
    uint8_t *variable;
} WifiScanResult;

typedef struct {
    uint8_t *ie;
    uint16_t reason;
    uint8_t rsv[2];
    uint32_t ieLen;
} WifiDisconnect;

typedef enum {
    WIFI_CHAN_DISABLED      = 1 << 0,
    WIFI_CHAN_PASSIVE_SCAN  = 1 << 1,
    WIFI_CHAN_NO_IBSS       = 1 << 2,
    WIFI_CHAN_RADAR         = 1 << 3,
    WIFI_CHAN_NO_HT40PLUS   = 1 << 4,
    WIFI_CHAN_NO_HT40MINUS  = 1 << 5,
    WIFI_CHAN_NO_OFDM       = 1 << 6,
    WIFI_CHAN_NO_80MHZ      = 1 << 7,
    WIFI_CHAN_NO_160MHZ     = 1 << 8,
} WifiChannelFlags;

int32_t WifiCmdProcess(struct HdfDeviceObject *device, int32_t cmd, struct HdfSBuf *reqData, struct HdfSBuf *rspData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of hdf_wifi_cmd.h */
