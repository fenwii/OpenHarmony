/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "auth_conn.h"

#include <string.h>

#include "aes_gcm.h"
#include "auth_interface.h"
#include "os_adapter.h"
#include "securec.h"
#include "tcp_socket.h"

int AuthConnSend(int fd, const char *buf, int offset, int count, int timeout)
{
    if ((buf == NULL) || (offset < 0) || (count <= 0) || (offset + count <= 0)) {
        return -1;
    }

    return TcpSendData(fd, buf + offset, count, timeout);
}

int AuthConnRecv(int fd, char *buf, int offset, int count, int timeout)
{
    if ((buf == NULL) || (offset < 0) || (count <= 0) || (offset + count <= 0)) {
        return -1;
    }

    return TcpRecvData(fd, buf + offset, count, timeout);
}

bool ModuleUseCipherText(int module)
{
    if (module >= MODULE_TRUST_ENGINE && module <= MODULE_HICHAIN_SYNC) {
        return false;
    }
    if (module >= MODULE_AUTH_CHANNEL && module <= MODULE_AUTH_MSG) {
        return false;
    }
    return true;
}

static int GetEncryptTransData(long long seqNum, const char *dataIn, unsigned char *data, unsigned int dataLen,
    int *bufLen)
{
    SessionKey *skey = AuthGetNewSessionKey();
    if (skey == NULL) {
        return -1;
    }

    if (memcpy_s(data, sizeof(int), &skey->index, sizeof(int)) != EOK) {
        return -1;
    }
    data += sizeof(int);

    AesGcmCipherKey cipherKey = {0};
    cipherKey.keybits = GCM_KEY_BITS_LEN_128;
    int ret = memcpy_s(cipherKey.key, SESSION_KEY_LENGTH, skey->key, AUTH_SESSION_KEY_LEN);
    unsigned char* randomIv = GenerateRandomIv();
    if (randomIv == NULL) {
        return -1;
    }
    ret += memcpy_s(cipherKey.iv, IV_LEN, randomIv, IV_LEN);
    free(randomIv);
    ret += memcpy_s(cipherKey.iv, sizeof(seqNum), &seqNum, sizeof(seqNum));
    if (ret != 0) {
        return -1;
    }

    int cipherLen = EncryptTransData(&cipherKey, (const unsigned char*)dataIn, strlen(dataIn), data, dataLen);
    if (cipherLen <= 0) {
        return -1;
    }

    *bufLen = cipherLen + PACKET_HEAD_SIZE + MESSAGE_INDEX_LEN;
    return 0;
}

unsigned char* AuthConnPackBytes(int module, int flags, long long seqNum, const char *str, int *bufLen)
{
    if ((str == NULL) || (bufLen == NULL)) {
        return NULL;
    }

    bool isCipherText = ModuleUseCipherText(module);
    int dataLen = isCipherText ? (strlen(str) + MESSAGE_ENCRYPT_OVER_HEAD_LEN) : strlen(str);
    int len = dataLen + PACKET_HEAD_SIZE;
    unsigned char *buf = (unsigned char *)calloc(1, sizeof(unsigned char) * len);
    if (buf == NULL) {
        return NULL;
    }

    unsigned char *data = buf;
    int identifier = PKG_HEADER_IDENTIFIER;
    unsigned int ret = (unsigned int)memcpy_s(data, sizeof(int), &identifier, sizeof(int));
    data += sizeof(int);
    ret |= (unsigned int)memcpy_s(data, sizeof(int), &module, sizeof(int));
    data += sizeof(int);
    ret |= (unsigned int)memcpy_s(data, sizeof(long long), &seqNum, sizeof(long long));
    data += sizeof(long long);
    ret |= (unsigned int)memcpy_s(data, sizeof(int), &flags, sizeof(int));
    data += sizeof(int);
    ret |= (unsigned int)memcpy_s(data, sizeof(int), &dataLen, sizeof(int));
    data += sizeof(int);
    if (ret != 0) {
        free(buf);
        return NULL;
    }

    if (isCipherText) {
        if (GetEncryptTransData(seqNum, str, data, dataLen, bufLen) != 0) {
            free(buf);
            return NULL;
        }
    } else {
        if (memcpy_s(data, dataLen, str, dataLen) != EOK) {
            free(buf);
            return NULL;
        }
        *bufLen = len;
    }

    return buf;
}

int AuthConnPostBytes(int fd, int module, int flags, long long seq, const char *data)
{
    if (data == NULL) {
        return -1;
    }
    int bufLen = 0;
    unsigned char *buf = AuthConnPackBytes(module, flags, seq, data, &bufLen);
    if (buf == NULL) {
        return -1;
    }
    int ret = AuthConnSend(fd, (char *)buf, 0, bufLen, 0);
    free(buf);
    buf = NULL;

    if (ret != bufLen) {
        SOFTBUS_PRINT("[AUTH] AuthConnPostBytes send fail\n");
        return -1;
    }

    return 0;
}

int AuthConnPostMessage(int fd, int module, int flags, long long seqNum, const cJSON *msg)
{
    if (msg == NULL) {
        return -1;
    }

    char *msgStr = cJSON_PrintUnformatted(msg);
    if (msgStr == NULL) {
        return -1;
    }

    int ret = AuthConnPostBytes(fd, module, flags, seqNum, msgStr);
    free(msgStr);
    msgStr = NULL;

    return ret;
}

