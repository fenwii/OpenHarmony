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

#include "app_verify_hap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "app_centraldirectory.h"
#include "app_common.h"
#include "app_verify.h"
#include "securec.h"

int GetDigestAlgorithmId(unsigned int signAlgorithm)
{
    switch (signAlgorithm & ALGORITHM_MASK) {
        case ALGORITHM_SHA256:
        case ALGORITHM_PKCS1_SHA256:
            return HASH_ALG_SHA256;
        case ALGORITHM_SHA384:
        case ALGORITHM_PKCS1_SHA384:
            return HASH_ALG_SHA384;
        case ALGORITHM_SHA512:
        case ALGORITHM_PKCS1_SHA512:
            return HASH_ALG_SHA512;
        default:
            LOG_ERROR("signAlgorithm: %d error", signAlgorithm);
            return V_ERR;
    }
}

static int ComputeBlockHash(const char *block, int blockLen, int alg, const HapBuf *result, int *offset)
{
    int ret, readLen, rawBufLen;
    const mbedtls_md_info_t *mdInfo = mbedtls_md_info_from_type((mbedtls_md_type_t)alg);
    P_NULL_RETURN_WTTH_LOG(mdInfo);
    int pos = 0;
    rawBufLen = blockLen;
    mbedtls_md_context_t *mdCtx = APPV_MALLOC(sizeof(mbedtls_md_context_t));
    P_NULL_RETURN_WTTH_LOG(mdCtx);
    LOG_INFO("alg: %d wholelen: %d", alg, rawBufLen);
    while (rawBufLen > 0) {
        mbedtls_md_init(mdCtx);
        readLen = (rawBufLen > HASH_BLOB_LEN) ? HASH_BLOB_LEN : rawBufLen;
        ret = mbedtls_md_setup(mdCtx, mdInfo, 0);
        P_ERR_GOTO_WTTH_LOG(ret);
        size_t hlen = mbedtls_md_get_size(mdInfo);
        if (hlen == 0 || hlen > MAX_HASH_SIZE) {
            goto EXIT;
        }
        ret = mbedtls_md_starts(mdCtx);
        P_ERR_GOTO_WTTH_LOG(ret);
        unsigned char chunkContentPrefix[HAP_DIGEST_PRIFIX_LEN] = {HAP_SECOND_LEVEL_CHUNK_PREFIX, 0, 0, 0, 0};
        if (memcpy_s((chunkContentPrefix + 1), HAP_DIGEST_PRIFIX_LEN - 1, (&readLen), sizeof(int)) != EOK) {
            LOG_ERROR("memcpy_s fail");
            goto EXIT;
        }
        ret = mbedtls_md_update(mdCtx, chunkContentPrefix, HAP_DIGEST_PRIFIX_LEN);
        P_ERR_GOTO_WTTH_LOG(ret);
        LOG_INFO("content: %d, %d", rawBufLen, pos);
        ret = mbedtls_md_update(mdCtx, (unsigned char *)block + pos, readLen);
        P_ERR_GOTO_WTTH_LOG(ret);
        rawBufLen -= readLen;
        pos += readLen;
        unsigned char *outbuf = APPV_MALLOC(hlen);
        P_NULL_GOTO_WTTH_LOG(outbuf);
        ret = mbedtls_md_finish(mdCtx, outbuf);
        HapPutData(result, *offset, outbuf, hlen);
        *offset += hlen;
        (void)memset_s(outbuf, hlen, 0, hlen);
        APPV_FREE(outbuf);
        P_ERR_GOTO_WTTH_LOG(ret);
        mbedtls_md_free(mdCtx);
    }
    APPV_FREE(mdCtx);
    return V_OK;
EXIT:
    mbedtls_md_free(mdCtx);
    APPV_FREE(mdCtx);
    return V_ERR;
}

static int GetChunkSumCount(int fileSize, int coreDirectorySize, int eocdSize, int rootHashLen)
{
    int chunkSize = HASH_BLOB_LEN;
    int maxSize = INT_MAX - chunkSize;
    if (fileSize > maxSize || coreDirectorySize > maxSize || eocdSize > maxSize) {
        return 0;
    }
    int count = ((fileSize - 1 + chunkSize) / chunkSize) + ((coreDirectorySize - 1 + chunkSize) / chunkSize) +
        ((eocdSize - 1 + chunkSize) / chunkSize);
    if (rootHashLen < 0 || (((INT_MAX - HAP_DIGEST_PRIFIX_LEN) / count) < rootHashLen)) {
        LOG_ERROR("overflow count: %d, chunkDigestLen: %d", count, rootHashLen);
        return 0;
    }
    LOG_INFO("get sum count %d", count);
    return count;
}

static int ComputeDigestsWithOptionalBlock(const int digestAlgorithm, int fp, const SignatureInfo *signInfo,
    const HapBuf *chunkDigest, const HapBuf *fianlDigest)
{
    int ret, readLen;
    int rst = V_ERR;
    char *rawBuf = NULL;
    unsigned char* outbuf = NULL;
    int rootHashLen = GetHashUnitLen(digestAlgorithm);
    LOG_INFO("rootHashLen %d", rootHashLen);
    if (rootHashLen <= 0 || rootHashLen > MAX_HASH_SIZE) {
        return rst;
    }
    const mbedtls_md_info_t *mdInfo = mbedtls_md_info_from_type((mbedtls_md_type_t)digestAlgorithm);
    P_NULL_RETURN_WTTH_LOG(mdInfo);
    mbedtls_md_context_t *mdCtx = APPV_MALLOC(sizeof(mbedtls_md_context_t));
    P_NULL_RETURN_WTTH_LOG(mdCtx);
    mbedtls_md_init(mdCtx);
    ret = mbedtls_md_setup(mdCtx, mdInfo, 0);
    P_ERR_GOTO_WTTH_LOG(ret);
    ret = mbedtls_md_starts(mdCtx);
    P_ERR_GOTO_WTTH_LOG(ret);

    BlockHead blockHead = {0};
    readLen = chunkDigest->len;
    LOG_INFO("readLen %d", readLen);
    ret = mbedtls_md_update(mdCtx, chunkDigest->buffer, readLen);
    P_ERR_GOTO_WTTH_LOG(ret);
    int rawLen = 0;
    rawBuf = GetSignBlockByType(signInfo, fp, PROFILE_BLOCK_WITHSIGN_TYPE, &rawLen, &blockHead);
    P_NULL_GOTO_WTTH_LOG(rawBuf);
    readLen = rawLen;
    LOG_INFO("signBuf %0x %d", rawBuf[0], readLen);
    ret = mbedtls_md_update(mdCtx, (unsigned char *)rawBuf, readLen);
    P_ERR_GOTO_WTTH_LOG(ret);
    outbuf = (unsigned char *)APPV_MALLOC(rootHashLen);
    P_NULL_GOTO_WTTH_LOG(outbuf);
    ret = mbedtls_md_finish(mdCtx, outbuf);
    P_ERR_GOTO_WTTH_LOG(ret);
    HapPutData(fianlDigest, 0, outbuf, rootHashLen);
    (void)memset_s(outbuf, rootHashLen, 0, rootHashLen);
    rst = V_OK;
EXIT:
    mbedtls_md_free(mdCtx);
    APPV_FREE(mdCtx);
    APPV_FREE(rawBuf);
    APPV_FREE(outbuf);
    return rst;
}

static int HapUpdateDigistHead(int digestAlgorithm, mbedtls_md_context_t *mdCtx, const mbedtls_md_info_t *mdInfo,
    int readLen, size_t *hlen)
{
    mbedtls_md_init(mdCtx);
    int ret = mbedtls_md_setup(mdCtx, mdInfo, 0);
    if (ret != 0) {
        return V_ERR;
    }
    *hlen = mbedtls_md_get_size(mdInfo);
    if (*hlen == 0 || *hlen > MAX_HASH_SIZE) {
        return V_ERR;
    }
    ret = mbedtls_md_starts(mdCtx);
    if (ret != 0) {
        return V_ERR;
    }
    unsigned char chunkContentPrefix[HAP_DIGEST_PRIFIX_LEN] = {HAP_SECOND_LEVEL_CHUNK_PREFIX, 0, 0, 0, 0};
    if (memcpy_s((chunkContentPrefix + 1), HAP_DIGEST_PRIFIX_LEN - 1, (&readLen), sizeof(int)) != EOK) {
        return V_ERR;
    }
    ret = mbedtls_md_update(mdCtx, chunkContentPrefix, HAP_DIGEST_PRIFIX_LEN);
    if (ret != 0) {
        return V_ERR;
    }
    return V_OK;
}

static int UpdateSmallBlock(int readLen, const int fp, mbedtls_md_context_t *mdCtx)
{
    int readLenLeft = readLen;
    while (readLenLeft > 0) {
        int onceRead = (readLenLeft > ONCE_READ_LEN) ? ONCE_READ_LEN : readLenLeft;
        unsigned char *onceBuf = APPV_MALLOC(onceRead);
        P_NULL_RETURN_WTTH_LOG(onceBuf);
        int len = read(fp, onceBuf, sizeof(char) * onceRead);
        if (len != onceRead) {
            LOG_ERROR("fread err: %d, %d", len, onceRead);
            APPV_FREE(onceBuf);
            return V_ERR;
        }
        int ret = mbedtls_md_update(mdCtx, onceBuf, onceRead);
        APPV_FREE(onceBuf);
        P_ERR_RETURN_WTTH_LOG(ret);
        readLenLeft -= onceRead;
    }
    return V_OK;
}

static int ComputerFileHash(const SignatureInfo *signInfo, int digestAlgorithm, const int fp,
    const HapBuf *chunkDigest, int *offset)
{
    mbedtls_md_context_t *mdCtx = APPV_MALLOC(sizeof(mbedtls_md_context_t));
    P_NULL_RETURN_WTTH_LOG(mdCtx);
    lseek(fp, 0, SEEK_SET);
    int pos = 0;
    int rawBufLen = signInfo->fullSignBlockOffset;
    while (rawBufLen > 0) {
        size_t hlen = 0;
        int readLen = (rawBufLen > HASH_BLOB_LEN) ? HASH_BLOB_LEN : rawBufLen;
        const mbedtls_md_info_t *mdInfo = mbedtls_md_info_from_type((mbedtls_md_type_t)digestAlgorithm);
        if (mdInfo == NULL) {
            APPV_FREE(mdCtx);
            return V_ERR;
        }
        int ret = HapUpdateDigistHead(digestAlgorithm, mdCtx, mdInfo, readLen, &hlen);
        P_ERR_GOTO_WTTH_LOG(ret);
        LOG_INFO("content: %d, %d", rawBufLen, pos);
        ret = UpdateSmallBlock(readLen, fp, mdCtx);
        P_ERR_GOTO_WTTH_LOG(ret);
        rawBufLen -= readLen;
        pos += readLen;
        unsigned char *outbuf = APPV_MALLOC(hlen);
        P_NULL_GOTO_WTTH_LOG(outbuf);
        ret = mbedtls_md_finish(mdCtx, outbuf);
        HapPutData(chunkDigest, *offset, outbuf, hlen);
        (void)memset_s(outbuf, hlen, 0, hlen);
        *offset += hlen;
        APPV_FREE(outbuf);
        P_ERR_GOTO_WTTH_LOG(ret);
        mbedtls_md_free(mdCtx);
    }
    APPV_FREE(mdCtx);
    return V_OK;
EXIT:
    mbedtls_md_free(mdCtx);
    APPV_FREE(mdCtx);
    return V_ERR;
}

static int ComputerCoreDirHash(const SignatureInfo *signInfo, int digestAlgorithm, const int fp,
    const HapBuf *chunkDigest, int *offset)
{
    int centralDirSize = signInfo->hapEocdOffset - signInfo->hapCoreDirOffset;
    if (centralDirSize <= 0) {
        return V_ERR;
    }
    char *dirBuf = APPV_MALLOC(centralDirSize);
    P_NULL_RETURN_WTTH_LOG(dirBuf);
    lseek(fp, signInfo->hapCoreDirOffset, SEEK_SET);
    int len = read(fp, dirBuf, sizeof(char) * centralDirSize);
    if (len != centralDirSize) {
        LOG_ERROR("fread err: %d, %d", len, centralDirSize);
        APPV_FREE(dirBuf);
        return V_ERR;
    }
    int ret = ComputeBlockHash(dirBuf, centralDirSize, digestAlgorithm, chunkDigest, offset);
    (void)memset_s(dirBuf, centralDirSize, 0, centralDirSize);
    APPV_FREE(dirBuf);
    P_ERR_RETURN_WTTH_LOG(ret);
    return V_OK;
}

static int ComputerEocdHash(const SignatureInfo *signInfo, int digestAlgorithm, const int fp,
    const HapBuf *chunkDigest, int *offset)
{
    if (signInfo->hapEocdSize <= 0) {
        return V_ERR;
    }
    HapEocd *eocdBuf = APPV_MALLOC(signInfo->hapEocdSize);
    P_NULL_RETURN_WTTH_LOG(eocdBuf);
    lseek(fp, signInfo->hapEocdOffset, SEEK_SET);
    int len = read(fp, eocdBuf, signInfo->hapEocdSize);
    if (len != signInfo->hapEocdSize) {
        LOG_ERROR("fread err: %d, %d", len, signInfo->hapEocdSize);
        APPV_FREE(eocdBuf);
        return V_ERR;
    }
    HapPutInt32((unsigned char*)(&(eocdBuf->eocdHead.coreDirOffset)), sizeof(int), signInfo->fullSignBlockOffset);
    int ret = ComputeBlockHash((char *)(eocdBuf), len, digestAlgorithm, chunkDigest, offset);
    (void)memset_s(eocdBuf, signInfo->hapEocdSize, 0, signInfo->hapEocdSize);
    APPV_FREE(eocdBuf);
    P_ERR_RETURN_WTTH_LOG(ret);
    return V_OK;
}

bool VerifyIntegrityChunk(int digestAlgorithm, const int fp,
    const SignatureInfo *signInfo, const HapBuf *actualDigest)
{
    if (signInfo == NULL || actualDigest == NULL || actualDigest->buffer == NULL) {
        return false;
    }
    int centralDirSize = signInfo->hapEocdOffset - signInfo->hapCoreDirOffset;
    int rootHashLen = GetHashUnitLen(digestAlgorithm);
    if (rootHashLen < 0) {
        LOG_ERROR("alg error");
        return false;
    }
    int sumCount = GetChunkSumCount(signInfo->fullSignBlockOffset, centralDirSize, signInfo->hapEocdSize, rootHashLen);
    if (sumCount == 0) {
        LOG_ERROR("sum count error");
        return false;
    }
    int sumOfChunksLen = HAP_DIGEST_PRIFIX_LEN + sumCount * rootHashLen;
    HapBuf chunkDigest = {0};
    if (!CreateHapBuffer(&chunkDigest, sumOfChunksLen)) {
        return false;
    }
    LOG_INFO("alg: %d", digestAlgorithm);
    HapPutByte(&chunkDigest, 0, HAP_FIRST_LEVEL_CHUNK_PREFIX);
    HapSetInt32(&chunkDigest, 1, sumCount);
    int offset = HAP_DIGEST_PRIFIX_LEN;
    int ret;
    ret = ComputerFileHash(signInfo, digestAlgorithm, fp, &chunkDigest, &offset);
    P_ERR_GOTO_WTTH_LOG(ret);
    ret = ComputerCoreDirHash(signInfo, digestAlgorithm, fp, &chunkDigest, &offset);
    P_ERR_GOTO_WTTH_LOG(ret);
    ret = ComputerEocdHash(signInfo, digestAlgorithm, fp, &chunkDigest, &offset);
    P_ERR_GOTO_WTTH_LOG(ret);
    ret = ComputeDigestsWithOptionalBlock(digestAlgorithm, fp, signInfo, &chunkDigest, actualDigest);
    P_ERR_GOTO_WTTH_LOG(ret);
    ClearHapBuffer(&chunkDigest);
    LOG_INFO("finish");
    return true;
EXIT:
    LOG_ERROR("exit");
    ClearHapBuffer(&chunkDigest);
    return false;
}

