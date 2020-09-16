/*
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
#include "at_wifi.h"

#include <stdio.h>
#include <stdlib.h>

#include <hi_at.h>

#ifndef CONFIG_FACTORY_TEST_MODE
#include "lwip/netifapi.h"
#endif
#include "hi_early_debug.h"
#include "hi_stdlib.h"
#include "hi_wifi_api.h"
#include "hi_wifi_mfg_test_if.h"
#ifdef LOSCFG_APP_MESH
#include "hi_wifi_mesh_api.h"
#include "hi_mesh_autolink_api.h"
#endif

#include "at.h"
#ifndef CONFIG_FACTORY_TEST_MODE
#include "lwip/netifapi.h"
#include "lwip/dns.h"
#endif
#include "hi_wifi_mfg_test_if.h"
#include "at_demo_hks.h"
#include "at_general.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

hi_wifi_bw g_bw_setup_value = HI_WIFI_BW_LEGACY_20M;
#ifdef _PRE_PSK_CALC_USER
unsigned char g_psk_calc[HI_WIFI_STA_PSK_LEN] = {0};
#endif
hi_wifi_sta_psk_config g_set_psk_config = {
    .ssid = {0},
    .key = {0}
};

hi_u32 ssid_prefix_scan(hi_s32 argc, const hi_char *argv[], hi_u32 prefix_flag)
{
    hi_s32  ret;
    errno_t rc;
    char   *tmp = HI_NULL;
    size_t  ssid_len = 0;
    hi_wifi_scan_params scan_params = {0};

    if ((argc != 1) || (at_param_null_check(argc, argv) == HI_ERR_FAILURE)) {
        return HI_ERR_FAILURE;
    }

    /* get ssid */
    if (argv[0][0] == 'P') {
        if (strlen(argv[0]) > HI_WIFI_MAX_SSID_LEN * 4 + 3) { /* ssid length should less than 32*4+3 */
            return HI_ERR_FAILURE;
        }
    } else {
        if (strlen(argv[0]) > HI_WIFI_MAX_SSID_LEN + 2) { /* ssid length should less than 32+2 */
            return HI_ERR_FAILURE;
        }
    }
    /* ssid hex to string */
    tmp = at_parse_string(argv[0], &ssid_len);
    scan_params.ssid_len = (unsigned char)ssid_len;
    if (tmp == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    if ((scan_params.ssid_len > HI_WIFI_MAX_SSID_LEN) || (scan_params.ssid_len == 0)) {
        at_free(tmp);
        return HI_ERR_FAILURE;
    }
    rc = memcpy_s(scan_params.ssid, HI_WIFI_MAX_SSID_LEN + 1, tmp, strlen(tmp) + 1);
    at_free(tmp);
    if (rc != EOK) {
        return HI_ERR_FAILURE;
    }

    scan_params.ssid[scan_params.ssid_len] = '\0';

    scan_params.scan_type = (prefix_flag == 1) ? HI_WIFI_SSID_PREFIX_SCAN : HI_WIFI_SSID_SCAN;

    ret = hi_wifi_sta_advance_scan(&scan_params);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}


/*****************************************************************************
* Func description: wpa ssid scan
*****************************************************************************/
hi_u32 cmd_wpa_ssid_scan(hi_s32 argc, const hi_char *argv[])
{
    hi_u32 ret = ssid_prefix_scan(argc, argv, 0);
    return ret;
}

/*****************************************************************************
* Func description: wpa  channel scan
*****************************************************************************/
hi_u32 cmd_wpa_channel_scan(hi_s32 argc, const hi_char *argv[])
{
    hi_s32 ret;
    hi_wifi_scan_params scan_params = {0};

    if ((argc != 1) || (integer_check(argv[0]) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    scan_params.channel = (hi_uchar)atoi(argv[0]);
    if ((scan_params.channel < 1) || (scan_params.channel > 14)) { /* 信道范围1~14 */
        return HI_ERR_FAILURE;
    }
    scan_params.scan_type = HI_WIFI_CHANNEL_SCAN;
    ret = hi_wifi_sta_advance_scan(&scan_params);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: wpa scan
*****************************************************************************/
hi_u32 cmd_wpa_scan(hi_s32 argc, const hi_char *argv[])
{
    hi_s32 ret;

    hi_unref_param(argc);
    hi_unref_param(argv);

    ret = hi_wifi_sta_scan();
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: ssid prefix scan
* example: AT+SCANPRSSID="hisi"
*****************************************************************************/
hi_u32 cmd_ssid_prefix_scan(hi_s32 argc, const hi_char *argv[])
{
    hi_u32 ret = ssid_prefix_scan(argc, argv, 1);
    return ret;
}

hi_u32 at_check_ccharacter(const hi_char *tmp)
{
    if (tmp == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    for (; *tmp != '\0'; tmp++) {
        if (*tmp == '\\') {
            if (*(tmp + 1) == '\\') {
                tmp++;
                continue;
            } else if (*(tmp + 1) == 'x') {
                return HI_ERR_SUCCESS;
            }
        }
    }
    return HI_ERR_FAILURE;
}

/*****************************************************************************
* Func description: wpa get scan results
*****************************************************************************/
hi_u32 cmd_wpa_scan_results(hi_s32 argc, const hi_char *argv[])
{
    hi_u32  num = WIFI_SCAN_AP_LIMIT;
    hi_char ssid_str[HI_WIFI_MAX_SSID_LEN * 4 + 3]; /* ssid length should less 32*4+3 */

    hi_unref_param(argv);
    hi_unref_param(argc);

    hi_wifi_ap_info *results = malloc(sizeof(hi_wifi_ap_info) * WIFI_SCAN_AP_LIMIT);
    if (results == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    memset_s(results, sizeof(hi_wifi_ap_info) * WIFI_SCAN_AP_LIMIT, 0, sizeof(hi_wifi_ap_info) * WIFI_SCAN_AP_LIMIT);

    hi_s32 ret = hi_wifi_sta_scan_results(results, &num);
    if (ret != HISI_OK) {
        free(results);
        return HI_ERR_FAILURE;
    }

    for (hi_u32 ul_loop = 0; (ul_loop < num) && (ul_loop < WIFI_SCAN_AP_LIMIT); ul_loop++) {
        if ((results[ul_loop].auth < HI_WIFI_SECURITY_OPEN) || (results[ul_loop].auth > HI_WIFI_SECURITY_UNKNOWN)) {
            results[ul_loop].auth = HI_WIFI_SECURITY_UNKNOWN;
        }

        hi_u32 service_flag = 0;
        if (results[ul_loop].wps_flag) {
            service_flag = 1;
        } else if (results[ul_loop].hisi_mesh_flag) {
            service_flag = 2; /* 2:Mesh scenario.CNcomment:Mesh场景 */
        }

        size_t ssid_len = strlen(results[ul_loop].ssid);
        const char* tmp = at_ssid_txt((unsigned char*)results[ul_loop].ssid, ssid_len);
        if (at_check_ccharacter(tmp) == HI_ERR_SUCCESS) {
            ret = sprintf_s(ssid_str, HI_WIFI_MAX_SSID_LEN * 4 + 3, "P\"%s\"", tmp); /* ssid len should less 32*4+3 */
        } else {
            ret = sprintf_s(ssid_str, HI_WIFI_MAX_SSID_LEN * 4 + 3, "%s", results[ul_loop].ssid); /* less 32*4+3 */
        }
        if (ret < 0) {
            free(results);
            return HI_ERR_FAILURE;
        }

        if (service_flag != 0) {
            hi_at_printf("+SCANRESULT:%s,"AT_MACSTR",%d,%d,%d,%d\r\n", ssid_str, at_mac2str(results[ul_loop].bssid),
                results[ul_loop].channel, results[ul_loop].rssi / 100, results[ul_loop].auth, service_flag);
        } else {
            hi_at_printf("+SCANRESULT:%s,"AT_MACSTR",%d,%d,%d\r\n", ssid_str, at_mac2str(results[ul_loop].bssid),
                results[ul_loop].channel, results[ul_loop].rssi / 100, results[ul_loop].auth);
        }
    }

    free(results);

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: start sta
*****************************************************************************/
hi_u32 cmd_sta_start(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argv);
    hi_unref_param(argc);
#ifndef CONFIG_FACTORY_TEST_MODE
    hi_s32  ret;
    hi_char ifname[WIFI_IFNAME_MAX_SIZE + 1] = {0};
    hi_s32  len = sizeof(ifname);

    ret = hi_wifi_sta_start(ifname, &len);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }
#else
    if (wal_add_cfg_vap() != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }
#endif
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 sta_start_adv_param(hi_s32 argc, const hi_char *argv[], hi_wifi_bw *bw)
{
    hi_s32  ret, value, i;
    for (i = 0; i < argc; i++) {
        if ((argv[i] != HI_NULL) && (integer_check(argv[i]) != HI_ERR_SUCCESS)) {
            return HI_ERR_FAILURE;
        }
        switch (i) {
            case 0: /* case 0: Protocol Type */
                value = (argv[i] != HI_NULL) ? atoi(argv[i]) : HI_WIFI_PHY_MODE_11BGN;
                if ((value == HI_WIFI_PHY_MODE_11B) && (argv[1] != HI_NULL) && (strcmp(argv[1], "20"))) { /* 20:bw */
                    return HI_ERR_FAILURE;
                }
#ifndef CONFIG_FACTORY_TEST_MODE
                ret = hi_wifi_sta_set_protocol_mode((hi_wifi_protocol_mode)value);
#endif
                break;
            case 1: /* case 1: Bandwidth */
                if ((argv[i] == HI_NULL) || !(strcmp(argv[i], "20"))) { /* bw 20M */
                    *bw = HI_WIFI_BW_LEGACY_20M;
                } else if (!(strcmp(argv[i], "10"))) { /* bw 10M */
                    *bw = HI_WIFI_BW_HIEX_10M;
                } else if (!(strcmp(argv[i], "5"))) { /* bw 5M */
                    *bw = HI_WIFI_BW_HIEX_5M;
                } else {
                    return HI_ERR_FAILURE;
                }
                ret = HISI_OK;
                break;
            case 2: /* case 2: pmf */
#ifndef CONFIG_FACTORY_TEST_MODE
                value = (argv[i] != HI_NULL) ? atoi(argv[i]) : HI_WIFI_MGMT_FRAME_PROTECTION_OPTIONAL;
                ret = hi_wifi_set_pmf((hi_wifi_pmf_options)value);
#endif
                break;
            default:
                return HI_ERR_FAILURE;
        }
#ifndef CONFIG_FACTORY_TEST_MODE
        if (ret != HISI_OK) {
            return HI_ERR_FAILURE;
        }
#endif
    }
    hi_unref_param(ret);
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_sta_start_adv(hi_s32 argc, const hi_char *argv[])
{
    hi_s32  ret;
    hi_wifi_bw bw = HI_WIFI_BW_LEGACY_20M;

    if (argc != 3) { /* "+STARTSTA" command fix 3 parameters */
        return HI_ERR_FAILURE;
    }

    ret = (hi_s32)sta_start_adv_param(argc, argv, &bw);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }
#ifndef CONFIG_FACTORY_TEST_MODE
    hi_char ifname[WIFI_IFNAME_MAX_SIZE + 1] = {0};
    hi_s32  len = sizeof(ifname);
    ret = hi_wifi_sta_start(ifname, &len);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }
#endif
    ret = hi_wifi_set_bandwidth(DEFAULT_IFNAME_STA, strlen(DEFAULT_IFNAME_STA) + 1, bw);
    if (ret != HI_ERR_SUCCESS) {
#ifndef CONFIG_FACTORY_TEST_MODE
        hi_wifi_sta_stop();
#endif
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: stop station
*****************************************************************************/
hi_u32 cmd_sta_stop(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argv);
    hi_unref_param(argc);
#ifndef CONFIG_FACTORY_TEST_MODE
    hi_s32 ret = hi_wifi_sta_stop();
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    for (int index = 0; index < DNS_MAX_SERVERS; index++) {
        lwip_dns_setserver(index, HI_NULL);
    }
#endif
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_sta_connect_get_ssid(const hi_char *argv[], hi_wifi_assoc_request *assoc_req,
    hi_wifi_fast_assoc_request *fast_assoc_req, hi_u32 fast_flag)
{
    size_t ssid_len = 0;
    errno_t rc;

    if (argv[0][0] == 'P') {
        if (strlen(argv[0]) > HI_WIFI_MAX_SSID_LEN * 4 + 3) { /* ssid length should less than 32*4+3 */
            return HI_ERR_FAILURE;
        }
    } else {
        if (strlen(argv[0]) > HI_WIFI_MAX_SSID_LEN + 2) { /* ssid length should less than 32+2 */
            return HI_ERR_FAILURE;
        }
    }

    /* ssid hex to string */
    hi_char *tmp = at_parse_string(argv[0], &ssid_len);
    if (tmp == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    if ((ssid_len > HI_WIFI_MAX_SSID_LEN) || (ssid_len == 0)) {
        at_free(tmp);
        return HI_ERR_FAILURE;
    }

    if ((fast_flag == 0) && (assoc_req != HI_NULL)) {
        rc = memcpy_s(assoc_req->ssid, HI_WIFI_MAX_SSID_LEN + 1, tmp, strlen(tmp) + 1);
        at_free(tmp);
        if (rc != EOK) {
            return HI_ERR_FAILURE;
        }
    } else if ((fast_flag == 1) && (fast_assoc_req != HI_NULL)) {
        rc = memcpy_s(fast_assoc_req->req.ssid, HI_WIFI_MAX_SSID_LEN + 1, tmp, strlen(tmp) + 1);
        at_free(tmp);
        if (rc != EOK) {
            return HI_ERR_FAILURE;
        }
    } else {
        at_free(tmp);
    }
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_sta_connect_get_key(hi_s32 argc, const hi_char *argv[], hi_wifi_fast_assoc_request *fast_assoc_req)
{
    if ((fast_assoc_req->req.auth != HI_WIFI_SECURITY_OPEN) && (argc == 5)) { /* 5 parameters  */
        if (argv[4] == HI_NULL) { /* 4:key */
            return HI_ERR_FAILURE;
        }
        const hi_char *buf = argv[4]; /* 4:key */

        size_t len = strlen(argv[4]); /* 4:key */
        if ((atoi(argv[3]) == HI_WIFI_SECURITY_WEP) && (len != 9) && (len != 17) && /* 3:encrypt type, 9 17:len */
            (len != 12) && (len != 28)) { /* 12 28: password len */
            return HI_ERR_FAILURE;
        } else if ((atoi(argv[3]) != HI_WIFI_SECURITY_WEP) && ((len > HI_WIFI_AP_KEY_LEN_MAX + 2) ||    /* argc 3,2 */
            (len < HI_WIFI_AP_KEY_LEN_MIN + 2))) {  /* len plus 2 */
            return HI_ERR_FAILURE;
        }
        if ((buf == HI_NULL) || (*buf != '\"') || (*(buf + strlen(argv[4]) - 1) != '\"') || /* 4 */
            (memcpy_s(fast_assoc_req->req.key, HI_WIFI_MAX_KEY_LEN + 1, buf + 1, strlen(argv[4]) - 2)  /* 4 2 */
            != EOK)) {
            return HI_ERR_FAILURE;
        }
    }
    fast_assoc_req->psk_flag = HI_WIFI_WPA_PSK_NOT_USE;

    return HI_ERR_SUCCESS;
}

hi_u32 parse_conn_para(hi_s32 argc, const hi_char *argv[], hi_wifi_assoc_request *assoc_req)
{
    if ((argc < 3) || (argc > 4)) { /* The number of "+CONN" command parameters should be 3 or 4 */
        return HI_ERR_FAILURE;
    }

    /* get ssid */
    if ((argv[0] != HI_NULL) && (cmd_sta_connect_get_ssid(argv, assoc_req, HI_NULL, 0) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    /* get bssid */
    if (argv[1] == HI_NULL) {
        memset_s(assoc_req->bssid, sizeof(assoc_req->bssid), 0, sizeof(assoc_req->bssid));
    } else if (strlen(argv[1]) == HI_WIFI_TXT_ADDR_LEN) {
        if (cmd_strtoaddr(argv[1], assoc_req->bssid, HI_WIFI_MAC_LEN) != HISI_OK) {
            return HI_ERR_FAILURE;
        }
    } else {
        return HI_ERR_FAILURE;
    }

    /* get auth_type */
    if ((integer_check(argv[2]) != HI_ERR_SUCCESS) || (atoi(argv[2]) < HI_WIFI_SECURITY_OPEN) || 		      /* 2 */
        (atoi(argv[2]) > HI_WIFI_SECURITY_WPAPSK_WPA2PSK_MIX) || ((atoi(argv[2]) == HI_WIFI_SECURITY_OPEN) && /* 2 */
        (argc != 3)) || ((atoi(argv[2]) != HI_WIFI_SECURITY_OPEN) && (argc != 4))) {    /* argc 3/2/4 */
        return HI_ERR_FAILURE;
    }
    assoc_req->auth = (hi_wifi_auth_mode)atoi(argv[2]); /* 2 */

    /* The encipher mode is set to 0 by default, that is, HI_WIFI_PARIWISE_UNKNOWN.
       CNcomment:encipher mode 默认设置为0，即HI_WIFI_PARIWISE_UNKNOWN */
    assoc_req->pairwise = HI_WIFI_PARIWISE_UNKNOWN;

    /* get key */
    if (argc == 4) { /* 4 parameters */
        const hi_char *buf = argv[3]; /* 3:The fourth parameter */
        if (buf == HI_NULL) {
            return HI_ERR_FAILURE;
        }
        size_t len = strlen(argv[3]); /* 3:key */
        if ((atoi(argv[2]) == HI_WIFI_SECURITY_WEP) && (len != 9) && (len != 17) &&     /* argc 2, len 9/17 */
            (len != 12) && (len != 28)) {           /* len 12/28 */
            return HI_ERR_FAILURE;
        } else if ((atoi(argv[2]) != HI_WIFI_SECURITY_WEP) && ((len > HI_WIFI_AP_KEY_LEN_MAX + 2) ||    /* argc 2 */
            (len < HI_WIFI_AP_KEY_LEN_MIN + 2))) {  /* len plus 2 */
            return HI_ERR_FAILURE;
        }
        if ((*buf != '\"') || (*(buf + strlen(argv[3]) - 1) != '\"') ||     /* argc 3 */
            (memcpy_s(assoc_req->key, HI_WIFI_MAX_KEY_LEN + 1, buf + 1, strlen(argv[3]) - 2) != EOK)) { /* 3 2 */
            return HI_ERR_FAILURE;
        }
    }

    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: station connect network
* example: AT+CONN="hisilicon",,3,"123456789"
*****************************************************************************/
hi_u32 cmd_sta_secure_connect(hi_s32 argc, const hi_char *argv[])
{
    hi_wifi_assoc_request assoc_req = {0};

    if (parse_conn_para(argc, argv, &assoc_req) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    if (hi_wifi_sta_connect(&assoc_req) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_u32 ret = app_hks_encrypt_conn_para(&assoc_req);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("save enc conn param fail:0x%x\r\n", ret);
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_sta_secure_re_connect(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argc);
    hi_unref_param(argv);

    hi_wifi_assoc_request assoc_req = {0};

    hi_u32 ret = app_hks_decrypt_conn_param(&assoc_req);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("get reconn param fail:0x%x\r\n", ret);
        return HI_ERR_FAILURE;
    }
    hi_at_printf("get reconn param ok\r\n");

    if (hi_wifi_sta_connect(&assoc_req) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_generate_save_conn_key(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argc);
    hi_unref_param(argv);

    hi_u32 ret = app_hks_generate_conn_key();
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("generate conn key fail:0x%x\r\n", ret);
        return HI_ERR_FAILURE;
    }

    hi_at_printf("generate conn key ok\r\n");
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_generate_save_cert_key(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argc);
    hi_unref_param(argv);

    hi_u32 ret = app_hks_generate_cert_key();
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("generate cert key fail\r\n");
        return HI_ERR_FAILURE;
    }

    hi_at_printf("generate cert key ok\r\n");
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_encrypt_cert(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argc);
    hi_unref_param(argv);

    hi_u32 ret = app_hks_encrypt_cert();
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("encrpyt cert fail\r\n");
        return HI_ERR_FAILURE;
    }
    hi_at_printf("encrpyt cert success\r\n");

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

#define CERT_PLAIN_SIZE (1024*8)

hi_u32 cmd_decrypt_cert(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argc);
    hi_unref_param(argv);

    hi_u32 plain_size = CERT_PLAIN_SIZE;
    hi_u8 *plain_data = malloc(plain_size);
    if (plain_data == HI_NULL) {
        hi_at_printf("plain data malloc fail\r\n");
        return HI_ERR_FAILURE;
    }

    hi_u32 ret = app_hks_decrypt_cert(&plain_size, plain_data);
    if (ret != HI_ERR_SUCCESS) {
        free(plain_data);
        hi_at_printf("decrpyt cert fail:0x%x\r\n", ret);
        return HI_ERR_FAILURE;
    }

    hi_at_printf("decrpyt cert success, plain_size:%d\r\n", plain_size);
    hi_u32 print_size = 0x40;
    if (plain_size < print_size) {
        print_size = plain_size;
    }
    for (hi_u32 i = 1; i <= print_size; i++) {
        hi_at_printf("0x%x ", plain_data[i - 1]);
        if (i % 0x4 == 0) {
            hi_at_printf("\r\n");
        }
    }

    free(plain_data);

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: station connect network
* example: AT+CONN="hisilicon",,3,"123456789"
*****************************************************************************/
hi_u32 cmd_sta_connect(hi_s32 argc, const hi_char *argv[])
{
    hi_wifi_assoc_request assoc_req = {0};

    if ((argc < 3) || (argc > 4)) {     /* argc 3/4 */
        return HI_ERR_FAILURE;
    }

    /* get ssid */
    if ((argv[0] != HI_NULL) && (cmd_sta_connect_get_ssid(argv, &assoc_req, HI_NULL, 0) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    /* get bssid */
    if (argv[1] == HI_NULL) {
        memset_s(assoc_req.bssid, sizeof(assoc_req.bssid), 0, sizeof(assoc_req.bssid));
    } else if (strlen(argv[1]) == HI_WIFI_TXT_ADDR_LEN) {
        if (cmd_strtoaddr(argv[1], assoc_req.bssid, HI_WIFI_MAC_LEN) != HISI_OK) {
            return HI_ERR_FAILURE;
        }
    } else {
        return HI_ERR_FAILURE;
    }

    /* get auth_type */
    if ((integer_check(argv[2]) != HI_ERR_SUCCESS) || (atoi(argv[2]) < HI_WIFI_SECURITY_OPEN) ||    /* argc 2 */
        (atoi(argv[2]) == HI_WIFI_SECURITY_WPA) || (atoi(argv[2]) == HI_WIFI_SECURITY_WPA2) || /* argc 2 */
        (atoi(argv[2]) == HI_WIFI_SECURITY_WPAPSK) || (atoi(argv[2]) >= HI_WIFI_SECURITY_UNKNOWN) || /* argc 2 */
        ((atoi(argv[2]) == HI_WIFI_SECURITY_OPEN) && (argc != 3)) || /* argc 2/3/4 */
        ((atoi(argv[2]) != HI_WIFI_SECURITY_OPEN) && (argc != 4))) { /* argc 2/3/4 */
        return HI_ERR_FAILURE;
    }
    assoc_req.auth = (hi_wifi_auth_mode)atoi(argv[2]); /* 2 */

    assoc_req.pairwise = HI_WIFI_PARIWISE_UNKNOWN;

    /* get key */
    if (argc == 4) {    /* argc 4 */
        const hi_char *buf = argv[3];   /* argc 3 */
        if (buf == HI_NULL) {
            return HI_ERR_FAILURE;
        }
        size_t len = strlen(argv[3]); /* 3:key */
        if ((atoi(argv[2]) == HI_WIFI_SECURITY_WEP) && (len != 9) && (len != 17) && /* argc 2, len 9/17 */
            (len != 12) && (len != 28))  { /* 12 28: password len */
            return HI_ERR_FAILURE;
        } else if ((atoi(argv[2]) != HI_WIFI_SECURITY_WEP) && ((len > HI_WIFI_AP_KEY_LEN_MAX + 2) ||    /* argc 2 */
            (len < HI_WIFI_AP_KEY_LEN_MIN + 2))) {  /* len plus 2 */
            return HI_ERR_FAILURE;
        }
        if ((*buf != '\"') || (*(buf + strlen(argv[3]) - 1) != '\"') || /* argc 3 */
            (memcpy_s(assoc_req.key, HI_WIFI_MAX_KEY_LEN + 1, buf + 1, strlen(argv[3]) - 2) != EOK)) { /* 3 2 */
            return HI_ERR_FAILURE;
        }
    }

    if (hi_wifi_sta_connect(&assoc_req) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: station quick connect
* example: AT+FCONN="hisilicon",,6,2,"123456789"
           AT+FCONN=,90:2B:D2:E4:CE:28,6,2,"123456789"
*****************************************************************************/
hi_u32 cmd_sta_quick_connect(hi_s32 argc, const hi_char *argv[])
{
    hi_wifi_fast_assoc_request fast_assoc_req = {0};
    hi_u32 ret;

    if ((argc < 4) || (argc > 5)) { /* argc 4 / 5 */
        return HI_ERR_FAILURE;
    }

    /* get ssid */
    if (argv[0] != HI_NULL) {
        ret = cmd_sta_connect_get_ssid(argv, HI_NULL, &fast_assoc_req, 1);
        if (ret != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    /* get bssid */
    if (argv[1] == HI_NULL) {
        memset_s(fast_assoc_req.req.bssid, sizeof(fast_assoc_req.req.bssid), 0, sizeof(fast_assoc_req.req.bssid));
    } else if (strlen(argv[1]) == HI_WIFI_TXT_ADDR_LEN) {
        if (cmd_strtoaddr(argv[1], fast_assoc_req.req.bssid, HI_WIFI_MAC_LEN) != HISI_OK) {
            return HI_ERR_FAILURE;
        }
    } else {
        return HI_ERR_FAILURE;
    }

    /* get channel,Scope1~14 */
    if ((integer_check(argv[2]) != HI_ERR_SUCCESS) || (atoi(argv[2]) <= 0) || (atoi(argv[2]) > 14)) { /* 2 14 */
        return HI_ERR_FAILURE;
    }
    fast_assoc_req.channel = (hi_uchar)atoi(argv[2]); /* 2 */

    /* get auth_type */
    if ((integer_check(argv[3]) != HI_ERR_SUCCESS) || (atoi(argv[3]) < HI_WIFI_SECURITY_OPEN) || /* argv 3 */
        (atoi(argv[3]) == HI_WIFI_SECURITY_WPA) || (atoi(argv[3]) == HI_WIFI_SECURITY_WPA2) || /* argv 3 */
        (atoi(argv[3]) == HI_WIFI_SECURITY_WPAPSK) || (atoi(argv[3]) >= HI_WIFI_SECURITY_UNKNOWN) || /* argv 3 */
        ((atoi(argv[3]) == HI_WIFI_SECURITY_OPEN) && (argc != 4)) || /* argc 3/4/5 */
        ((atoi(argv[3]) != HI_WIFI_SECURITY_OPEN) && (argc != 5))) { /* argc 3/4/5 */
        return HI_ERR_FAILURE;
    }

    fast_assoc_req.req.auth = (hi_wifi_auth_mode)atoi(argv[3]); /* 3 */

    /* get encipher mode 0，HI_WIFI_PARIWISE_UNKNOWN */
    fast_assoc_req.req.pairwise = HI_WIFI_PARIWISE_UNKNOWN;

    /* get key */
    ret = cmd_sta_connect_get_key(argc, argv, &fast_assoc_req);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    if (hi_wifi_sta_fast_connect(&fast_assoc_req) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: sta disconnect network
*****************************************************************************/
hi_u32 cmd_sta_disconnect(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argv);
    hi_unref_param(argc);

    hi_s32 ret = hi_wifi_sta_disconnect();
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: get station connection status
*****************************************************************************/
hi_u32 cmd_sta_status(hi_s32 argc, const hi_char *argv[])
{
    hi_s32 ret;
    hi_wifi_status wifi_status;

    hi_unref_param(argv);
    hi_unref_param(argc);

    memset_s(&wifi_status, sizeof(hi_wifi_status), 0, sizeof(hi_wifi_status));

    ret = hi_wifi_sta_get_connect_info(&wifi_status);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }
    if (wifi_status.status == HI_WIFI_CONNECTED) {
        const hi_char *tmp = at_ssid_txt((unsigned char*)wifi_status.ssid, strlen(wifi_status.ssid));
        if (at_check_ccharacter(tmp) == HI_ERR_SUCCESS) {
            hi_at_printf("+STASTAT:1,P\"%s\","AT_MACSTR",%d\r\n", tmp, at_mac2str(wifi_status.bssid),
                wifi_status.channel);
        } else {
            hi_at_printf("+STASTAT:1,%s,"AT_MACSTR",%d\r\n", wifi_status.ssid, at_mac2str(wifi_status.bssid),
                wifi_status.channel);
        }
    } else {
        hi_at_printf("+STASTAT:0,0,0,0\r\n");
    }
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

#ifdef CONFIG_WPS_SUPPORT
/*****************************************************************************
* Func description: using wps pbc to connect network
* example: sta wps_pbc <bssid>
*****************************************************************************/
hi_u32 cmd_wpa_wps_pbc(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argv);
    hi_unref_param(argc);

    hi_s32 ret = hi_wifi_sta_wps_pbc(HI_NULL);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: get wps pin value
*****************************************************************************/
hi_u32 cmd_wpa_wps_pin_get(hi_s32 argc, const hi_char *argv[])
{
    hi_char pin_txt[WIFI_WPS_PIN_LEN + 1] = {0};
    hi_u32  len = WIFI_WPS_PIN_LEN + 1;
    hi_s32  ret;

    hi_unref_param(argv);
    hi_unref_param(argc);

    ret = hi_wifi_sta_wps_pin_get(pin_txt, len);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }
    pin_txt[WIFI_WPS_PIN_LEN] = '\0';

    hi_at_printf("+PINSHOW:%s\r\n", pin_txt);
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: using wps pin to connect network
* example: AT+PIN=03882368
*****************************************************************************/
hi_u32 cmd_wpa_wps_pin(hi_s32 argc, const hi_char *argv[])
{
    hi_char  pin[WIFI_WPS_PIN_LEN + 1] = {0};
    hi_char *ppin = pin;

    if ((argc != 1) || (at_param_null_check(argc, argv) == HI_ERR_FAILURE)) {
        return HI_ERR_FAILURE;
    }

    hi_u32 len = strlen(argv[0]);
    if ((len != WIFI_WPS_PIN_LEN) || (memcpy_s(pin, WIFI_WPS_PIN_LEN + 1, argv[0], len) != EOK)) {
        return HI_ERR_FAILURE;
    }

    if (hi_wifi_sta_wps_pin(ppin, HI_NULL) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}
#endif /* LOSCFG_APP_WPS */

hi_u32 cmd_set_reconn(hi_s32 argc, const hi_char *argv[])
{
    hi_s32 enable;
    hi_s32 seconds = RECONN_TIMEOUT_MIN;
    hi_u32 period = RECONN_PERIOD_MIN;
    hi_u32 max_try_count = RECONN_COUNT_MIN;
    if ((argc != 1) && (argc != 4)) {   /* argc 1/4 */
        return HI_ERR_FAILURE;
    }
    if (argc == 1) {
        if ((integer_check(argv[0]) != HI_ERR_SUCCESS) || (atoi(argv[0]) != 0)) {
            return HI_ERR_FAILURE;
        }
        enable = 0;
    } else {
        for (hi_s32 i = 0; i < argc - 1; i++) {
            if (integer_check(argv[i]) != HI_ERR_SUCCESS) {
                return HI_ERR_FAILURE;
            }
        }
        enable = atoi(argv[0]);
        if (enable == 0) {
            return HI_ERR_FAILURE;
        }
        period = (hi_u32)atoi(argv[1]);         /* argc 1 */
        max_try_count = (hi_u32)atoi(argv[2]);  /* argc 2 */
        if (argv[3] != HI_NULL) {               /* argc 3 */
            if (integer_check(argv[3]) != HI_ERR_SUCCESS) { /* argc 3 */
                return HI_ERR_FAILURE;
            }
            seconds = atoi(argv[3]);    /* argc 3 */
        }

        if (seconds < RECONN_TIMEOUT_MIN || period < RECONN_PERIOD_MIN || period > RECONN_PERIOD_MAX ||
            max_try_count < RECONN_COUNT_MIN || max_try_count > RECONN_COUNT_MAX) {
            return HI_ERR_FAILURE;
        }
    }
    hi_s32 ret = hi_wifi_sta_set_reconnect_policy(enable, seconds, period, max_try_count);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");

    return HI_ERR_SUCCESS;
}

const at_cmd_func g_sta_func_tbl[] = {
    {"+STOPSTA", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_stop},
    {"+SCAN", 5, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_scan},
    {"+SCANCHN", 8, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_channel_scan, HI_NULL},
    {"+SCANSSID", 9, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_ssid_scan, HI_NULL},
    {"+SCANPRSSID", 11, HI_NULL, HI_NULL, (at_call_back_func)cmd_ssid_prefix_scan, HI_NULL},
    {"+SCANRESULT", 11, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_scan_results},
    {"+CONN", 5, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_connect, HI_NULL},
    {"+FCONN", 6, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_quick_connect, HI_NULL},
    {"+DISCONN", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_disconnect},
    {"+STASTAT", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_status},
    {"+RECONN", 7, HI_NULL, HI_NULL, (at_call_back_func)cmd_set_reconn, HI_NULL},
#ifdef CONFIG_WPS_SUPPORT
    {"+PBC", 4, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_wps_pbc},
    {"+PIN", 4, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_wps_pin, HI_NULL},
    {"+PINSHOW", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_wpa_wps_pin_get},
#endif /* LOSCFG_APP_WPS */
#ifdef CONFIG_TEE_HUKS_DEMO_SUPPORT
    {"+GCONNKEY", 9, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_generate_save_conn_key},
    {"+SCONN", 6, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_secure_connect, HI_NULL},
    {"+SRCONN", 7, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_secure_re_connect},
#endif
};

#define AT_STA_FUNC_NUM (sizeof(g_sta_func_tbl) / sizeof(g_sta_func_tbl[0]))

hi_void hi_at_sta_cmd_register(hi_void)
{
    hi_at_register_cmd(g_sta_func_tbl, AT_STA_FUNC_NUM);
}

const at_cmd_func g_sta_factory_test_func_tbl[] = {
    {"+STARTSTA", 9, HI_NULL, HI_NULL, (at_call_back_func)cmd_sta_start_adv, (at_call_back_func)cmd_sta_start},
#ifdef CONFIG_TEE_HUKS_DEMO_SUPPORT
    {"+GCERTKEY", 9, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_generate_save_cert_key},
    {"+CERTENC", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_encrypt_cert},
    {"+CERTDEC", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_decrypt_cert},
#endif
};

#define AT_STA_FACTORY_TEST_FUNC_NUM (sizeof(g_sta_factory_test_func_tbl) / sizeof(g_sta_factory_test_func_tbl[0]))

hi_void hi_at_sta_factory_test_cmd_register(hi_void)
{
    hi_at_register_cmd(g_sta_factory_test_func_tbl, AT_STA_FACTORY_TEST_FUNC_NUM);
}

/*****************************************************************************
* Func description: show mesh or softap connected sta information
*****************************************************************************/
hi_u32 cmd_softap_show_sta(hi_s32 argc, const hi_char *argv[])
{
    hi_s32 ret;
    hi_u32 sta_index;
    hi_u32 sta_num = WIFI_DEFAULT_MAX_NUM_STA;
    hi_wifi_ap_sta_info  sta_list[WIFI_DEFAULT_MAX_NUM_STA];
    hi_wifi_ap_sta_info *sta_list_node = HI_NULL;

    hi_unref_param(argc);
    hi_unref_param(argv);

    ret = hi_wifi_softap_get_connected_sta(sta_list, &sta_num);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    sta_list_node = sta_list;
    for (sta_index = 0; sta_index < sta_num; sta_index++, sta_list_node++) {
        hi_at_printf("+SHOWSTA:" AT_MACSTR, at_mac2str(sta_list_node->mac));
        hi_at_printf("\r\n");
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: start softap
* example: AT+STARTAP="hisilicon",0,6,1,"123456789"
           AT+STARTAP="hisilicon",0,6,0
*****************************************************************************/
hi_u32 cmd_start_softap(hi_s32 argc, const hi_char *argv[])
{
    hi_wifi_softap_config hapd_conf          = {0};
    hi_char ifname[WIFI_IFNAME_MAX_SIZE + 1] = {0};
    hi_s32  ifname_len = sizeof(ifname);
    hi_s32  len;

    if (((argc != 4) && (argc != 5)) || (at_param_null_check(argc, argv) == HI_ERR_FAILURE)) {  /* argc 4/5 */
        return HI_ERR_FAILURE;
    }

    /* get ssid */
    if ((argv[0][0] != '\"') || (*(argv[0] + strlen(argv[0]) - 1) != '\"') ||
        (memcpy_s(hapd_conf.ssid, HI_WIFI_MAX_SSID_LEN + 1, argv[0] + 1, strlen(argv[0]) - 2) != EOK)) { /* 2 */
        return HI_ERR_FAILURE;
    }

    /* get ssid_hidden,Scope 0~1 */
    if ((integer_check(argv[1]) != HI_ERR_SUCCESS) || (atoi(argv[1]) < 0) || (atoi(argv[1]) > 1)) {
        return HI_ERR_FAILURE;
    }
    hapd_conf.ssid_hidden = atoi(argv[1]);

    /* get channel,Scope1~14 */
    if ((integer_check(argv[2]) != HI_ERR_SUCCESS) || (atoi(argv[2]) <= 0) || (atoi(argv[2]) > 14)) {   /* argc 2 */
        return HI_ERR_FAILURE;
    }
    hapd_conf.channel_num = (hi_uchar)atoi(argv[2]); /* 2 */

    if ((integer_check(argv[3]) == HI_ERR_FAILURE) || /* 3 */
        ((atoi(argv[3]) != HI_WIFI_SECURITY_OPEN) && (atoi(argv[3]) != HI_WIFI_SECURITY_WPA2PSK) && /* 3 */
        (atoi(argv[3]) != HI_WIFI_SECURITY_WPAPSK_WPA2PSK_MIX)) || /* 3 */
        ((atoi(argv[3]) == HI_WIFI_SECURITY_OPEN) && (argc != 4))) {    /* argc 3/4 */
        return HI_ERR_FAILURE;
    }
    hapd_conf.authmode = (hi_wifi_auth_mode)atoi(argv[3]); /* 3 */

    /* get authmode */
    if ((hapd_conf.authmode != HI_WIFI_SECURITY_OPEN)) {
        if ((argc != 5) || (strlen(argv[4]) > HI_WIFI_AP_KEY_LEN_MAX + 2) ||    /* argc 4/5, len plus 2 */
            (strlen(argv[4]) < HI_WIFI_AP_KEY_LEN_MIN + 2)) {   /* argc 4, len plus 2 */
            return HI_ERR_FAILURE;
        }
        const hi_char *buf = argv[4];   /* argc 4 */
        len = (int)strlen(argv[4]);     /* argc 4 */
        if ((*buf != '\"') || (*(buf + len - 1) != '\"') ||
            (memcpy_s((hi_char*)hapd_conf.key, HI_WIFI_AP_KEY_LEN + 1, buf + 1, len - 2) != EOK)) { /* len minus 2 */
            return HI_ERR_FAILURE;
        }
    }
    if (hi_wifi_softap_start(&hapd_conf, ifname, &ifname_len) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    if (hi_wifi_set_bandwidth(DEFAULT_IFNAME_AP, strlen(DEFAULT_IFNAME_AP) + 1, g_bw_setup_value) != HI_ERR_SUCCESS) {
        hi_wifi_softap_stop();
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: start softap
* example: AT+SETAPADV=2,10,100,2,3600,0
*****************************************************************************/
hi_u32 cmd_set_softap_advance(hi_s32 argc, const hi_char *argv[])
{
    hi_s32 ret, value, i;

    if (argc != 6) { /* The command has six fixed parameters.CNcomment:"+SETAPADV"命令固定6个命令参数 */
        return HI_ERR_FAILURE;
    }
    for (i = 0; i < argc; i++) {
        if ((argv[i] != HI_NULL) && (integer_check(argv[i]) != HI_ERR_SUCCESS)) {
            return HI_ERR_FAILURE;
        }

        if (i == 0) {
            value = (argv[i] != HI_NULL) ? atoi(argv[i]) : HI_WIFI_PHY_MODE_11BGN;
            if ((value == HI_WIFI_PHY_MODE_11B) && (argv[1] != HI_NULL) && (strcmp(argv[1], "20"))) { /* 20:bw */
                return HI_ERR_FAILURE;
            }
            ret = hi_wifi_softap_set_protocol_mode((hi_wifi_protocol_mode)value);
        } else if (i == 1) {
            if ((argv[i] == HI_NULL) || !(strcmp(argv[i], "20"))) { /* 20M */
                g_bw_setup_value = HI_WIFI_BW_LEGACY_20M;
            } else if (!(strcmp(argv[i], "10"))) { /* 10M */
                g_bw_setup_value = HI_WIFI_BW_HIEX_10M;
            } else if (!(strcmp(argv[i], "5"))) { /* 5M */
                g_bw_setup_value = HI_WIFI_BW_HIEX_5M;
            } else {
                return HI_ERR_FAILURE;
            }
            ret = HISI_OK;
        } else if (i == 2) {    /* i is 2 */
            ret = (argv[i] != HI_NULL) ? hi_wifi_softap_set_beacon_period(atoi(argv[i])) : HISI_OK;
        } else if (i == 3) {    /* i is 3 */
            ret = (argv[i] != HI_NULL) ? hi_wifi_softap_set_dtim_period(atoi(argv[i])) : HISI_OK;
        } else if (i == 4) {    /* i is 4 */
            ret = (argv[i] != HI_NULL) ? hi_wifi_softap_set_group_rekey(atoi(argv[i])) : HISI_OK;
        } else if (i == 5) {    /* i is 5 */
            ret = (argv[i] != HI_NULL) ? hi_wifi_softap_set_shortgi(atoi(argv[i])) : HISI_OK;
        } else {
            return HI_ERR_FAILURE;
        }
        if (ret != HISI_OK) {
            return HI_ERR_FAILURE;
        }
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: stop softap
*****************************************************************************/
hi_u32 cmd_stop_softap(hi_s32 argc, const hi_char *argv[])
{
    hi_unref_param(argc);
    hi_unref_param(argv);

    if (hi_wifi_softap_stop() != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: softap disconnect station
* example: AT+DEAUTHSTA=90:2B:D2:E4:CE:28
*****************************************************************************/
hi_u32 cmd_softap_deauth_sta(hi_s32 argc, const hi_char *argv[])
{
    hi_uchar mac_addr[HI_WIFI_MAC_LEN + 1] = {0};
    hi_s32 ret;

    if ((argc != 1) || (argv[0] == HI_NULL) || (strlen(argv[0]) != HI_WIFI_TXT_ADDR_LEN)) {
        return HI_ERR_FAILURE;
    }

    if (cmd_strtoaddr(argv[0], mac_addr, HI_WIFI_MAC_LEN) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    ret = hi_wifi_softap_deauth_sta(mac_addr, HI_WIFI_MAC_LEN);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 at_ap_scan(hi_void)
{
    hi_at_printf("ERROR:TBD\r\n");
    return HI_ERR_SUCCESS;
}

const at_cmd_func g_at_ap_func_tbl[] = {
    {"+STARTAP", 8, HI_NULL, HI_NULL, (at_call_back_func)cmd_start_softap, HI_NULL},
    {"+SETAPADV", 9, HI_NULL, HI_NULL, (at_call_back_func)cmd_set_softap_advance, HI_NULL},
    {"+STOPAP", 7, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_stop_softap},
    {"+SHOWSTA", 8, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_softap_show_sta},
    {"+DEAUTHSTA", 10, HI_NULL, HI_NULL, (at_call_back_func)cmd_softap_deauth_sta, HI_NULL},
    {"+APSCAN", 7, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)at_ap_scan},
};

#define AT_AP_FUNC_NUM (sizeof(g_at_ap_func_tbl) / sizeof(g_at_ap_func_tbl[0]))

hi_void hi_at_softap_cmd_register(void)
{
    hi_at_register_cmd(g_at_ap_func_tbl, AT_AP_FUNC_NUM);
}

#ifdef LOSCFG_APP_MESH
hi_u32 cmd_mesh_auto_get_ssid(const hi_char *argv[], hi_mesh_autolink_config *mesh_auto_config)
{
    size_t ssid_len = 0;
    errno_t rc;

    /* get ssid */
    if (argv[1][0] == 'P') {
        if (strlen(argv[1]) > HI_WIFI_MAX_SSID_LEN * 4 + 3) { /* ssid length should less than 32*4+3 */
            return HI_ERR_FAILURE;
        }
    } else if (strlen(argv[1]) > HI_WIFI_MAX_SSID_LEN + 2) { /* ssid length should less than 32+2 */
        return HI_ERR_FAILURE;
    }

    /* ssid hex to string */
    hi_char *tmp = at_parse_string(argv[1], &ssid_len);
    if (tmp == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    if ((ssid_len > HI_WIFI_MAX_SSID_LEN) || (ssid_len == 0)) {
        at_free(tmp);
        return HI_ERR_FAILURE;
    }

    rc = memcpy_s(mesh_auto_config->ssid, HI_WIFI_MAX_SSID_LEN + 1, tmp, strlen(tmp) + 1);
    at_free(tmp);
    if (rc != EOK) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: start mesh auto join
* example: AT+MAUTOJOIN=1,"router_mesh",0
AT+MAUTOJOIN=1,"router_mesh",1,"123456789"
*****************************************************************************/
hi_s32 cmd_mesh_auto_connect(hi_s32 argc, const hi_char* argv[])
{
    hi_mesh_autolink_config mesh_auto_config = {0};

    if ((argc < 3) || (argc > 4)) { /* argc 3/4 */
        return HI_ERR_FAILURE;
    }

    /* get usr config mesh type */
    if ((integer_check(argv[0]) != HI_ERR_SUCCESS) || (atoi(argv[0]) < HI_MESH_USRCONFIG_MBR) ||
        (atoi(argv[0]) > HI_MESH_USRCONFIG_AUTO)) {
        return HI_ERR_FAILURE;
    }
    mesh_auto_config.usr_cfg_role = (hi_mesh_autolink_usrcfg_node_type)atoi(argv[0]);

    /* get ssid */
    if (cmd_mesh_auto_get_ssid(argv, &mesh_auto_config) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    /* get auth_type */
    if ((integer_check(argv[2]) == HI_ERR_FAILURE) ||   /* argc 2 */
        ((atoi(argv[2]) != HI_MESH_OPEN) && (atoi(argv[2]) != HI_MESH_AUTH)) || /* argc 2 */
        ((atoi(argv[2]) == HI_MESH_OPEN) && (argc != 3))) { /* argc 2/3 */
        return HI_ERR_FAILURE;
    }
    mesh_auto_config.auth = (hi_mesh_autolink_auth_type)atoi(argv[2]); /* 2 */

    /* get key */
    if (mesh_auto_config.auth == HI_MESH_AUTH) {
        if ((argc != 4) || (strlen(argv[3]) > HI_WIFI_MS_KEY_LEN_MAX + 2) || /* 4,3,2 */
            (strlen(argv[3]) < HI_WIFI_MS_KEY_LEN_MIN + 2)) { /* 3,2 */
            return HI_ERR_FAILURE;
        }
        const hi_char *buf = argv[3]; /* 3 */
        size_t len = strlen(argv[3]); /* 3 */
        if ((*buf != '\"') || (*(buf + len - 1) != '\"') ||
            (memcpy_s((hi_char*)mesh_auto_config.key, HI_WIFI_MESH_KEY_LEN_MAX + 1, buf + 1, len - 2) != EOK)) { /* 2 */
            return HI_ERR_FAILURE;
        }
    }

    if (hi_mesh_start_autolink(&mesh_auto_config) != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: exit mesh network
* example: AT+MEXIT
* AT+MEXIT
*****************************************************************************/
hi_s32 cmd_mesh_exit_network(hi_s32 argc, const hi_char* argv[])
{
    hi_s32  ret;

    hi_unref_param(argv);
    hi_unref_param(argc);

    ret = hi_mesh_exit_autolink();
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: set mesh router rssi threshold
* example: AT+MSETRSSI=-50
*****************************************************************************/
hi_s32 cmd_mesh_set_rssi_threshold(hi_s32 argc, const hi_char* argv[])
{
    hi_s32 ret;
    hi_s32 usr_rssi_config;

    if ((argc != 1) || (argv[0] == HI_NULL)) {
        return HI_ERR_FAILURE;
    }

    usr_rssi_config = atoi(argv[0]);
    if ((usr_rssi_config < -127) || (usr_rssi_config > 10)) {   /* range -127,10 */
        return HI_ERR_FAILURE;
    }
    ret = hi_mesh_autolink_set_router_rssi_threshold(usr_rssi_config);
    if (ret != HISI_OK) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

/*****************************************************************************
* Func description: set mesh autonetwork bw value
* example: AT+MSETBW=5
*****************************************************************************/
hi_s32 cmd_mesh_set_autonetwork_bw(hi_s32 argc, const hi_char* argv[])
{
    hi_wifi_bw bw_value;
    if (argc != 1) { /* "+MSETBW"命令固定1个命令参数 */
        return HI_ERR_FAILURE;
    }

    if ((argv[0] != HI_NULL) && (integer_check(argv[0]) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    if ((argv[0] != HI_NULL) && (atoi(argv[0]) == 5)) { /* bw 5 */
        bw_value = HI_WIFI_BW_HIEX_5M;
    } else if ((argv[0] != HI_NULL) && (atoi(argv[0]) == 10)) { /* bw 10 */
        bw_value = HI_WIFI_BW_HIEX_10M;
    } else {
        bw_value = HI_WIFI_BW_LEGACY_20M;
    }

    hi_mesh_autolink_set_bw(bw_value);
    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

const at_cmd_func g_at_mesh_func_tbl[] = {
    {"+MAUTOJOIN", 10, HI_NULL, HI_NULL, (at_call_back_func)cmd_mesh_auto_connect, HI_NULL},
    {"+MEXIT", 6, HI_NULL, HI_NULL, HI_NULL, (at_call_back_func)cmd_mesh_exit_network},
    {"+MSETRSSI", 9, HI_NULL, HI_NULL, (at_call_back_func)cmd_mesh_set_rssi_threshold, HI_NULL},
    {"+MSETBW", 7, HI_NULL, HI_NULL, (at_call_back_func)cmd_mesh_set_autonetwork_bw, HI_NULL},
};

#define AT_MESH_FUNC_NUM (sizeof(g_at_mesh_func_tbl) / sizeof(g_at_mesh_func_tbl[0]))

hi_void hi_at_mesh_cmd_register(void)
{
    hi_at_register_cmd(g_at_mesh_func_tbl, AT_MESH_FUNC_NUM);
}
#endif
#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
