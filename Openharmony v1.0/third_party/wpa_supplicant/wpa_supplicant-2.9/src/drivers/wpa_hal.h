/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef _WPA_HAL_H_
#define _WPA_HAL_H_

#include <stdint.h>
#include <stddef.h>

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
#define IFNAMSIZ 16
#define WEP_KEY_NUM 4
#define DEFAULT_NUM_MODES 2
#define WPA_BANDWIDTH_20 20
#define WPA_BANDWIDTH_40 40

#define SCAN_AP_LIMIT 64
#define SCAN_TIME_OUT 5

#define NETDEV_UP 0x0001
#define NETDEV_DOWN 0x0002

#define EAPOL_PKT_BUF_SIZE 800
#define CHECK_DHCP_TIME 30

#define WPA_WEP40_KEY_LEN 5
#define WPA_WEP104_KEY_LEN 13

#define WPA_FLAG_ON     1
#define WPA_FLAG_OFF    0

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
    WIFI_MESH_ENABLE_AUTO_PEER,
    WIFI_MESH_ENABLE_ACCEPT_PEER,
    WIFI_MESH_ENABLE_ACCEPT_STA,
    WIFI_MESH_ENABLE_FLAG_BUTT
} WifiMeshEnableFlagType;

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
    WIFI_IFTYPE_UNSPECIFIED,
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
    uint8_t *macAddr;
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
    uint8_t dst[ETH_ADDR_LEN];
    uint8_t src[ETH_ADDR_LEN];
    uint8_t bssid[ETH_ADDR_LEN];
    uint8_t *data;
    size_t dataLen;
} WifiActionData;

typedef struct {
    uint8_t *addr;
    uint8_t plinkState;
    uint8_t set;
    uint8_t meshBcnPriority;
    uint8_t meshIsMbr;
    uint8_t meshInitiativePeering;
} WifiMeshUsrParams;

typedef struct {
    uint8_t *addr;
    uint8_t *gtk;
    uint8_t gtkLen;
    uint8_t resv[3];
} WifiSetMeshUsrGtk;

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
    uint8_t type;
} WifiIfAdd;

typedef struct {
    int32_t start;
    int32_t duration;
    uint8_t count;
    uint8_t resv[3];
} WifiP2pNoa;

typedef struct {
    int32_t legacyPs;
    int8_t oppPs;
    uint8_t ctWindow;
    int8_t resv[2];
} WifiP2pPowerSave;

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
    uint8_t *bssid;
    uint8_t rsv[2];
    uint16_t status;
    uint16_t freq;
} WifiConnectResult;

typedef struct {
    int32_t flags;
    uint8_t *bssid;
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

typedef struct {
    uint8_t macAddr[ETH_ADDR_LEN];
    uint16_t reason;
} WifiMeshClosePeer;

typedef struct {
    uint8_t peerAddr[ETH_ADDR_LEN];
    uint8_t meshBcnPriority;
    uint8_t meshIsMbr;
    int8_t rssi;
    int8_t reserved[3];
} WifiMeshNewPeerCandidate;

typedef struct {
    struct hostapd_data *hapd;
    char iface[IFNAMSIZ + 1];
    int8_t resv[3];
    uint64_t actionCookie;
    void *ctx;
    void *eventQueue;

    struct l2_packet_data *eapolSock;
    uint8_t ownAddr[ETH_ADDR_LEN];

    uint32_t associated;
    uint8_t bssid[ETH_ADDR_LEN];
    uint8_t ssid[MAX_SSID_LEN];
    int32_t ssidLen;

    struct wpa_scan_res *scanRes[SCAN_AP_LIMIT];
    uint32_t scanNum;
    uint32_t beaconSet;
    uint8_t mode;
} WifiDriverData;

WifiDriverData *GetDrvData();
void WifiWpaScanTimeout(void *eloop, void *ctx);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of wpa_hal.h */
