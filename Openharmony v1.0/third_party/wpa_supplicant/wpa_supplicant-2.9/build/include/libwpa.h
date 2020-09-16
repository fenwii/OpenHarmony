/*
 * interface in libwpa
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */
#ifndef LIB_WPA_H
#define LIB_WPA_H
void deinit_wifi_service();
int ap_main(int argc, char *argv[]);
int wpa_main(int argc, char *argv[]);
int pbkdf2_sha1(const char *passphrase, const uint8_t *ssid, size_t ssid_len,
                int iterations, uint8_t *buf, size_t buflen);
#endif // LIB_WPA_H

