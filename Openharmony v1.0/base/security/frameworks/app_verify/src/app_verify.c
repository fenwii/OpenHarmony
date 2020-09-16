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

#include "app_verify.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "app_centraldirectory.h"
#include "app_common.h"
#include "app_file.h"
#include "app_provision.h"
#include "app_verify_hap.h"
#include "mbedtls/base64.h"
#include "mbedtls/md.h"
#include "mbedtls/pk.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls_pkcs7.h"
#include "securec.h"

static const TrustAppCert g_trustAppList[] = {
    {
        .maxCertPath = CERT_MAX_DEPTH,
        .name = "huawei app gallary",
        .appSignCert = "C=CN, O=Huawei, OU=HOS AppGallery, CN=HOS AppGallery Application Release",
        .profileSignCert = "C=CN, O=Huawei, OU=HOS AppGallery, CN=HOS Profile Management",
        .profileDebugSignCert = "C=CN, O=Huawei, OU=HOS AppGallery, CN=HOS Profile Management Debug",
        .issueCA = "C=CN, O=Huawei, OU=Huawei CBG, CN=Huawei CBG Software Signing Service CA",
    },
    {
        .maxCertPath = CERT_MAX_DEPTH,
        .name = "huawei system apps",
        .appSignCert = "C=CN, O=Huawei CBG, OU=HOS Development Team, CN=HOS Application Provision Release",
        .profileSignCert = "C=CN, O=Huawei CBG, OU=HOS Development Team, CN=HOS Application Provision Profile Release",
        .profileDebugSignCert =
            "C=CN, O=Huawei CBG, OU=HOS Development Team, CN=HOS Application Provision Profile Release_Debug",
        .issueCA = "C=CN, O=Huawei, OU=Huawei CBG, CN=Huawei CBG Software Signing Service CA",
    },
};

static const TrustAppCert g_trustAppListTest[] = {
    {
        .maxCertPath = CERT_MAX_DEPTH,
        .name = "huawei app gallary",
        .appSignCert = "C=CN, O=Huawei, OU=HOS AppGallery, CN=HOS AppGallery Application Release",
        .profileSignCert = "C=CN, O=Huawei, OU=HOS AppGallery, CN=HOS Profile Management",
        .profileDebugSignCert = "C=CN, O=Huawei, OU=HOS AppGallery, CN=HOS Profile Management Debug",
        .issueCA = "C=CN, O=Huawei, OU=Huawei CBG, CN=Huawei CBG Software Signing Service CA Test",
    },
    {
        .maxCertPath = CERT_MAX_DEPTH,
        .name = "huawei system apps",
        .appSignCert = "C=CN, O=Huawei CBG, OU=HOS Development Team, CN=HOS Application Provision Dev",
        .profileSignCert = "C=CN, O=Huawei CBG, OU=HOS Development Team, CN=HOS Application Provision Profile Dev",
        .profileDebugSignCert =
            "C=CN, O=Huawei CBG, OU=HOS Development Team, CN=HOS Application Provision Profile Dev_Debug",
        .issueCA = "C=CN, O=Huawei, OU=Huawei CBG, CN=Huawei CBG Software Signing Service CA Test",
    },
};

static bool g_isDebugMode = false;

static void SignHeadN2H(HwSignHead *signHead)
{
    signHead->blockNum = HapGetInt((unsigned char *)&signHead->blockNum, sizeof(signHead->blockNum));
    signHead->size = HapGetInt64((unsigned char *)&signHead->size, sizeof(signHead->size));
    signHead->magicLow = HapGetInt64((unsigned char *)&signHead->magicLow, sizeof(signHead->magicLow));
    signHead->magicHigh = HapGetInt64((unsigned char *)&signHead->magicHigh, sizeof(signHead->magicHigh));
    signHead->version = HapGetInt((unsigned char *)&signHead->version, sizeof(signHead->version));
    return;
}

static void BlockHeadN2H(BlockHead *blockHead)
{
    blockHead->type = HapGetInt((unsigned char *)&blockHead->type, sizeof(blockHead->type));
    blockHead->length = HapGetInt((unsigned char *)&blockHead->length, sizeof(blockHead->length));
    blockHead->offset = HapGetInt((unsigned char *)&blockHead->offset, sizeof(blockHead->offset));
    return;
}

static void ContentN2H(ContentInfo *content)
{
    content->blockNum = HapGetInt((unsigned char *)&content->blockNum, sizeof(content->blockNum));
    content->size = HapGetInt((unsigned char *)&content->size, sizeof(content->size));
    content->algId = HapGetInt((unsigned char *)&content->algId, sizeof(content->algId));
    content->length = HapGetInt((unsigned char *)&content->length, sizeof(content->length));
    return;
}

static int GetSignHead(const FileRead *file, SignatureInfo *signInfo)
{
    struct stat fileSt;
    int ret = fstat(file->fp, &fileSt);
    if ((ret != 0) || (fileSt.st_size < sizeof(HwSignHead))) {
        LOG_ERROR("fstat error, %d, filelen: %d", ret, (int)fileSt.st_size);
        return V_ERR_GET_SIGNHEAD;
    }
    if (!FindSignature(file, signInfo)) {
        LOG_ERROR("find signature error");
        return V_ERR_GET_SIGNHEAD;
    }
    if (signInfo->hapCoreDirOffset < sizeof(HwSignHead)) {
        LOG_ERROR("hapCoreDirOffset error, %d", signInfo->hapCoreDirOffset);
        return V_ERR_GET_SIGNHEAD;
    }
    ret = lseek(file->fp, signInfo->hapCoreDirOffset - sizeof(HwSignHead), SEEK_SET);
    if (ret < 0) {
        LOG_ERROR("lseek error, %d", ret);
        return V_ERR_GET_SIGNHEAD;
    }
    HwSignHead *signHead = APPV_MALLOC(sizeof(HwSignHead));
    P_NULL_RETURN_WTTH_LOG(signHead);
    int readLen = read(file->fp, signHead, sizeof(HwSignHead));
    if (readLen != sizeof(HwSignHead)) {
        LOG_ERROR("readLen %d, %d", readLen, (int)sizeof(HwSignHead));
        APPV_FREE(signHead);
        return V_ERR_GET_SIGNHEAD;
    }
    SignHeadN2H(signHead);
    if (signHead->magicLow != HAP_SIG_BLOCK_MAGIC_LO || signHead->magicHigh != HAP_SIG_BLOCK_MAGIC_HI) {
        LOG_ERROR("sign head magic invalid");
        APPV_FREE(signHead);
        return V_ERR_GET_SIGNHEAD;
    }
    LOG_INFO("sign head: size: %llu, blockNum:0x%x", signHead->size, signHead->blockNum);
    signInfo->signHead = signHead;
    signInfo->fullSignBlockOffset = signInfo->hapCoreDirOffset - (int)signHead->size;
    signInfo->fileSize = fileSt.st_size;
    if (signInfo->fullSignBlockOffset <= 0 || signInfo->fullSignBlockOffset >= signInfo->hapCoreDirOffset) {
        LOG_ERROR("fullSignBlockOffset invalid");
        APPV_FREE(signHead);
        return V_ERR_GET_SIGNHEAD;
    }
    return V_OK;
}

static int FindBlockHead(const SignatureInfo *signInfo, int fp, int blockType, BlockHead *block)
{
    HwSignHead *signH = signInfo->signHead;
    /* find signature block */
    lseek(fp, signInfo->fullSignBlockOffset, SEEK_SET);
    int num = signH->blockNum;
    if (num > MAX_BLOCK_NUM) {
        return V_ERR;
    }
    while (num-- > 0) {
        int readLen = read(fp, block, sizeof(BlockHead));
        if (readLen != sizeof(BlockHead)) {
            LOG_ERROR("find block head , read err %d, %d", readLen, (int)sizeof(BlockHead));
            return V_ERR;
        }
        int type = HapGetInt((unsigned char *)&block->type, sizeof(block->type));
        LOG_ERROR("find block type: %0x", type);
        if (type == blockType) {
            BlockHeadN2H(block);
            return V_OK;
        }
    }
    LOG_ERROR("get sign block by type failed, type: %d", blockType);
    return V_ERR;
}

char *GetSignBlockByType(const SignatureInfo *signInfo, int fp, int blockType, int *len, BlockHead *blockHead)
{
    if (signInfo == NULL || blockHead == NULL) {
        return NULL;
    }
    int ret = FindBlockHead(signInfo, fp, blockType, blockHead);
    if (ret != V_OK) {
        LOG_ERROR("find block head error");
        return NULL;
    }
    LOG_INFO("type: %u, len: %u, offset: %u signoffset: %d",
        blockHead->type, blockHead->length, blockHead->offset, signInfo->fullSignBlockOffset);
    /* sign block head length always 0
        rawdata
        xx block head
        signdata
        hwsignhead
    */
    if (blockHead->length == 0 || blockHead->length > (signInfo->hapCoreDirOffset - signInfo->fullSignBlockOffset)) {
        return NULL;
    }
    char *buf = APPV_MALLOC(blockHead->length + 1);
    if (buf == NULL) {
        LOG_ERROR("malloc error");
        return NULL;
    }
    buf[blockHead->length] = '\0';
    struct stat fileSt;
    ret = fstat(fp, &fileSt);
    if ((ret != 0) || (fileSt.st_size < signInfo->fullSignBlockOffset + blockHead->offset + blockHead->length)) {
        LOG_ERROR("fstat error, %d, filelen: %d", ret, (int)fileSt.st_size);
        APPV_FREE(buf);
        return NULL;
    }
    lseek(fp, signInfo->fullSignBlockOffset + blockHead->offset, SEEK_SET);
    int readLen = read(fp, buf, blockHead->length);
    if (readLen != blockHead->length) {
        LOG_ERROR("read error: %d, %d", readLen, blockHead->length);
        APPV_FREE(buf);
        return NULL;
    }
    *len = readLen;
    LOG_INFO("buf begin");
    return buf;
}

int GetHashUnitLen(int hashAlg)
{
    LOG_INFO("algId: %d", hashAlg);
    return mbedtls_md_get_size(mbedtls_md_info_from_type((mbedtls_md_type_t)hashAlg));
}

int CalculateHash(const unsigned char *input, int len, int hashAlg, unsigned char *output)
{
    if (input == NULL || output == NULL || len < 0) {
        return V_ERR;
    }
    int ret = mbedtls_md(mbedtls_md_info_from_type((mbedtls_md_type_t)hashAlg), input, len, output);
    if (ret) {
        LOG_ERROR("Error: calc digest failed");
        return ret;
    }
    return ret;
}

static int CalcCmpContHash(const Pkcs7 *pkcs7, const SignerInfo *signer,
                           mbedtls_md_type_t algType, unsigned char *hash, size_t *hashLen)
{
    int rc;
    unsigned char *input = NULL;
    size_t inputLen;

    /* calc orinal context hash */
    rc = PKCS7_GetContentData((Pkcs7 *)pkcs7, &input, &inputLen);
    P_ERR_RETURN_WTTH_LOG(rc);

    rc = mbedtls_md(mbedtls_md_info_from_type(algType), input, inputLen, hash);
    if (rc) {
        LOG_ERROR("Error: calc digest failed");
        return rc;
    }
    *hashLen = mbedtls_md_get_size(mbedtls_md_info_from_type(algType));

    /* compare the calc hash with the attributes hash */
    unsigned char *digInAttr = NULL;
    size_t digInAttrLen;
    rc = PKCS7_GetDigestInSignerAuthAttr((SignerInfo *)signer, &digInAttr, &digInAttrLen);
    if (rc != V_OK) {
        LOG_ERROR("PKCS7_GetDigestInSignerAuthAttr error: %d", rc);
        return rc;
    }
    if (digInAttrLen != *hashLen) {
        LOG_ERROR("Error: content hash len is not equal with attr's hash len");
        return V_ERR;
    }
    if (memcmp(hash, digInAttr, digInAttrLen) != 0) {
        LOG_ERROR("Error: content hash not equal with attr hash");
        return V_ERR;
    }
    return V_OK;
}

static int CalcDigest(const Pkcs7 *pkcs7, const SignerInfo *signer,
                      mbedtls_md_type_t algType, unsigned char *hash, size_t *hashLen)
{
    int rc;
    unsigned char *input = NULL;
    size_t inputLen;
    rc = CalcCmpContHash(pkcs7, signer, algType, hash, hashLen);
    if (rc != V_OK) {
        LOG_ERROR("Error: content hash not equal with attr hash");
        return rc;
    }
    LOG_INFO("signer context hash equal with attr hash");

    /* calc the attribute hash */
    rc = PKCS7_GetSignerAuthAttr(signer, &input, &inputLen);
    if (rc != V_OK) {
        LOG_ERROR("Error: PKCS7_GetSignerAuthAttr failed ret: %d", rc);
        return rc;
    }
    rc = mbedtls_md(mbedtls_md_info_from_type(algType), input, inputLen, hash);
    if (rc != V_OK) {
        LOG_ERROR("Error: calc digest failed ret: %d", rc);
        return rc;
    }
    *hashLen = mbedtls_md_get_size(mbedtls_md_info_from_type(algType));
    return V_OK;
}

static int VerifyRawHash(const SignatureInfo *signInfo, const FileRead *fileRead, const Pkcs7 *pkcs7Handle)
{
    /* parse content */
    unsigned char *input = NULL;
    size_t inputLen = 0;
    /* calc orinal context hash */
    int ret = PKCS7_GetContentData((Pkcs7 *)pkcs7Handle, &input, &inputLen);
    if (ret != V_OK) {
        LOG_ERROR("get content info error: %d", ret);
        return ret;
    }
    LOG_INFO("content: len: %d", (int)inputLen);

    ContentInfo *content = APPV_MALLOC(sizeof(ContentInfo));
    P_NULL_RETURN_WTTH_LOG(content);

    ret = memcpy_s(content, sizeof(ContentInfo), input, inputLen);
    if (ret != V_OK) {
        LOG_ERROR("mem cpy error, ret: %d", ret);
        APPV_FREE(content);
        return ret;
    }
    ContentN2H(content);
    content->algId = GetDigestAlgorithmId((unsigned int)content->algId);
    if (content->algId != HASH_ALG_SHA256 && content->algId != HASH_ALG_SHA384 && content->algId != HASH_ALG_SHA512) {
        LOG_ERROR("hash alg invalid");
        APPV_FREE(content);
        return ret;
    }
    HapBuf actualDigest = {0};
    int rootHashLen = GetHashUnitLen(content->algId);
    if (!CreateHapBuffer(&actualDigest, rootHashLen)) {
        LOG_ERROR("create buf fail");
        APPV_FREE(content);
        return V_ERR;
    }
    if (!VerifyIntegrityChunk(content->algId, fileRead->fp, signInfo, &actualDigest)) {
        LOG_ERROR("get raw hash failed");
        ClearHapBuffer(&actualDigest);
        APPV_FREE(content);
        return V_ERR;
    }
    if ((actualDigest.len != content->length) || (memcmp(actualDigest.buffer, content->hash, actualDigest.len) != 0)) {
        LOG_ERROR("hash diff");
        APPV_FREE(content);
        ClearHapBuffer(&actualDigest);
        return V_ERR_GET_HASH_DIFF;
    }
    APPV_FREE(content);
    ClearHapBuffer(&actualDigest);
    return V_OK;
}

static int GetCertTypeBySourceName(const TrustAppCert *cert)
{
    if (cert == NULL) {
        return CERT_TYPE_OTHER;
    } else if (strcmp(cert->name, "huawei app gallary") == 0) {
        return CERT_TYPE_APPGALLARY;
    } else if (strcmp(cert->name, "huawei system apps") == 0) {
        return CERT_TYPE_SYETEM;
    } else {
        return CERT_TYPE_OTHER;
    }
}

static const TrustAppCert *GetProfSourceBySigningCert(const SignerResovledInfo *signer,
                                                      const TrustAppCert* trustList, int num)
{
    for (int i = 0; i < num; i++) {
        if (strcmp(trustList[i].issueCA, signer->issuer) == 0) {
            if (strcmp(trustList[i].profileSignCert, signer->subject) == 0 ||
                strcmp(trustList[i].profileDebugSignCert, signer->subject) == 0) {
                LOG_PRINT_STR("profile source name : %s", g_trustAppList[i].name);
                return  &trustList[i];
            }
        }
    }
    return NULL;
}

static int GetProfileCertTypeBySignInfo(SignerResovledInfo *signer, int *certType)
{
    /* only support first signer cert */
    const TrustAppCert *trustCert = GetProfSourceBySigningCert(signer, g_trustAppList,
                                                               sizeof(g_trustAppList) / sizeof(TrustAppCert));
    if (g_isDebugMode && trustCert == NULL) {
        trustCert = GetProfSourceBySigningCert(signer, g_trustAppListTest,
                                               sizeof(g_trustAppListTest) / sizeof(TrustAppCert));
    }
    /* check level */
    if (trustCert != NULL && trustCert->maxCertPath < signer->depth) {
        LOG_ERROR("cert maxdepth error: %d", signer->depth);
        return V_ERR;
    }
    *certType = GetCertTypeBySourceName(trustCert);
    return V_OK;
}


static const TrustAppCert *GetAppSourceBySigningCert(const SignerResovledInfo *signer,
                                                     const TrustAppCert* trustList, int num)
{
    for (int i = 0; i < num; i++) {
        if (strcmp(trustList[i].appSignCert, signer->subject) == 0 &&
            strcmp(trustList[i].issueCA, signer->issuer) == 0) {
                return  &trustList[i];
        }
    }
    return NULL;
}

static int GetAppCertTypeBySignInfo(SignerResovledInfo *signer, int *certType)
{
    /* only support first signer cert */
    const TrustAppCert *trustCert = GetAppSourceBySigningCert(signer, g_trustAppList,
                                                              sizeof(g_trustAppList) / sizeof(TrustAppCert));
    if (g_isDebugMode && trustCert == NULL) {
        trustCert = GetAppSourceBySigningCert(signer, g_trustAppListTest,
                                              sizeof(g_trustAppListTest) / sizeof(TrustAppCert));
    }
    /* check level */
    if (trustCert != NULL && trustCert->maxCertPath < signer->depth) {
        LOG_ERROR("cert maxdepth error: %d %d", trustCert->maxCertPath, signer->depth);
        return V_ERR;
    }
    *certType = GetCertTypeBySourceName(trustCert);
    return V_OK;
}

/* get singer cert type by trust list */
static int GetAppSingerCertType(Pkcs7 *pkcs7Handle, int *certType)
{
    SignersResovedInfo *sri = PKCS7_GetAllSignersResolvedInfo(pkcs7Handle);
    if (sri == NULL || sri->nrOfSigners == 0) {
        PKCS7_FreeAllSignersResolvedInfo(sri);
        LOG_ERROR("Get all signer's resolved info failed");
        return V_ERR;
    }
    int ret = GetAppCertTypeBySignInfo(&sri->signers[0], certType);
    if (ret != V_OK) {
        LOG_ERROR("get cert type by sign info failed: %d", ret);
        PKCS7_FreeAllSignersResolvedInfo(sri);
        return V_ERR;
    }
    PKCS7_FreeAllSignersResolvedInfo(sri);
    return V_OK;
}

/* get singer cert type by trust list */
static int GetProfileSingerCertType(Pkcs7 *pkcs7Handle, int *certType)
{
    SignersResovedInfo *sri = PKCS7_GetAllSignersResolvedInfo(pkcs7Handle);
    if (sri == NULL) {
        LOG_ERROR("Get all signer's resolved info failed");
        return V_ERR;
    }
    int ret = GetProfileCertTypeBySignInfo(&sri->signers[0], certType);
    if (ret != V_OK) {
        LOG_ERROR("get cert type by sign info failed: %d", ret);
        PKCS7_FreeAllSignersResolvedInfo(sri);
        return V_ERR;
    }
    PKCS7_FreeAllSignersResolvedInfo(sri);
    return V_OK;
}

/* verfiy profile data integrity with sign */
static int VerifyProfileSignGetRaw(const char *buf, int len, char **profileContent, int *contentLen)
{
    /* verfiy */
    char *profileData = NULL;
    int certType;
    unsigned char *input = NULL;
    size_t inputLen;
    Pkcs7 *pkcs7 = APPV_MALLOC(sizeof(Pkcs7));
    P_NULL_RETURN_WTTH_LOG(pkcs7);

    int ret = PKCS7_ParseSignedData((unsigned char *)buf, (size_t)len, pkcs7);
    P_ERR_GOTO_WTTH_LOG(ret);

    LOG_INFO("pkcs7 parse message sucess");

    /* verify sign, rawdata */
    ret = PKCS7_VerifyCertsChain(pkcs7);
    P_ERR_GOTO_WTTH_LOG(ret);

    LOG_INFO("Verify certs success");

    ret = GetProfileSingerCertType(pkcs7, &certType);
    P_ERR_GOTO_WTTH_LOG(ret);

    if (certType == CERT_TYPE_OTHER) {
        LOG_ERROR("cert type invalid");
        ret = V_ERR;
        goto EXIT;
    }
    ret = PKCS7_VerifySignerSignature(pkcs7, CalcDigest);
    P_ERR_GOTO_WTTH_LOG(ret);
    LOG_INFO("verify profile ok");

    /* raw profile data: content */
    ret = PKCS7_GetContentData(pkcs7, &input, &inputLen);
    P_ERR_GOTO_WTTH_LOG(ret);

    LOG_INFO("get profile sign content ok");

    if (inputLen > MAX_PROFILE_SIZE || inputLen == 0) {
        ret = V_ERR;
        goto EXIT;
    }
    profileData = APPV_MALLOC(inputLen + 1);
    P_NULL_GOTO_WTTH_LOG(profileData);

    ret = memcpy_s(profileData, inputLen, input, inputLen);
    profileData[inputLen] = '\0';
    P_ERR_GOTO_WTTH_LOG(ret);

    PKCS7_FreeRes(pkcs7);
    APPV_FREE(pkcs7);
    *profileContent = profileData;
    *contentLen = (int)inputLen;
    LOG_INFO("verify profile get raw data ok");
    return V_OK;
EXIT:
    PKCS7_FreeRes(pkcs7);
    APPV_FREE(pkcs7);
    APPV_FREE(profileData);
    return V_ERR;
}
static unsigned char *GetRsaPk(const mbedtls_pk_context *pk, int *len)
{
    unsigned char *buf = APPV_MALLOC(MAX_PK_BUF);
    if (buf == NULL) {
        LOG_ERROR("malloc error");
        return NULL;
    }
    int ret = memset_s(buf, MAX_PK_BUF, 0, MAX_PK_BUF);
    if (ret != V_OK) {
        LOG_ERROR("memset error");
        APPV_FREE(buf);
        return NULL;
    }
    unsigned char *c = buf + MAX_PK_BUF;
    int pkLen = mbedtls_pk_write_pubkey(&c, buf, pk);
    LOG_INFO("GetRsaPk pkLen %d", pkLen);
    if (pkLen < 0 || pkLen > MAX_PK_BUF) {
        LOG_ERROR("get pk buf error");
        APPV_FREE(buf);
        return NULL;
    }
    unsigned char *pkBuf = APPV_MALLOC(pkLen);
    if (pkBuf == NULL) {
        LOG_ERROR("malloc error");
        APPV_FREE(buf);
        return NULL;
    }
    ret = memcpy_s(pkBuf, pkLen, c, pkLen);
    if (ret != V_OK) {
        LOG_ERROR("mem copy error: %d", ret);
        APPV_FREE(buf);
        APPV_FREE(pkBuf);
        return NULL;
    }
    *len = pkLen;
    APPV_FREE(buf);
    return pkBuf;
}

static unsigned char *GetEcPk(const mbedtls_pk_context *pk, int *len)
{
    mbedtls_ecp_keypair *ecCtx = mbedtls_pk_ec(*pk);
    if (ecCtx == NULL) {
        LOG_ERROR("get ec pk error");
        return NULL;
    }
    unsigned char *buf = APPV_MALLOC(MBEDTLS_ECP_MAX_PT_LEN);
    if (buf == NULL) {
        LOG_ERROR("malloc error");
        return NULL;
    }
    int ret = mbedtls_ecp_point_write_binary(&ecCtx->grp, &ecCtx->Q,
                                             MBEDTLS_ECP_PF_UNCOMPRESSED, (size_t *)len, buf, MBEDTLS_ECP_MAX_PT_LEN);
    if (ret != V_OK) {
        LOG_ERROR("get ecc pk key error");
        APPV_FREE(buf);
        return NULL;
    }
    LOG_INFO("GetEcPk *len %d", *len);
    if (*len <= 0 || *len > MBEDTLS_ECP_MAX_PT_LEN) {
        APPV_FREE(buf);
        return NULL;
    }
    unsigned char *pkBuf = APPV_MALLOC(*len);
    if (pkBuf == NULL) {
        LOG_ERROR("malloc error");
        APPV_FREE(buf);
        return NULL;
    }
    ret = memcpy_s(pkBuf, *len, buf, *len);
    if (ret != V_OK) {
        LOG_ERROR("mem copy error: %d", ret);
        APPV_FREE(buf);
        APPV_FREE(pkBuf);
        return NULL;
    }
    APPV_FREE(buf);
    return pkBuf;
}

static unsigned char *GetPkBuf(const mbedtls_pk_context *pk, int *len)
{
    unsigned char *bufA = NULL;
    if (mbedtls_pk_get_type(pk) == MBEDTLS_PK_RSA || mbedtls_pk_get_type(pk) == MBEDTLS_PK_RSASSA_PSS) {
        bufA = GetRsaPk(pk, len);
    } else if (mbedtls_pk_get_type(pk) == MBEDTLS_PK_ECDSA || mbedtls_pk_get_type(pk) == MBEDTLS_PK_ECKEY) {
        bufA = GetEcPk(pk, len);
    }
    return bufA;
}

static int ParseCertGetPk(const char *certEncoded, AppSignPk *pk)
{
    mbedtls_x509_crt *cert = APPV_MALLOC(sizeof(mbedtls_x509_crt));
    P_NULL_RETURN_WTTH_LOG(cert);

    mbedtls_x509_crt_init(cert);
    int ret = mbedtls_x509_crt_parse(cert, (unsigned char *)certEncoded, strlen(certEncoded) + 1);
    if (ret != V_OK) {
        LOG_ERROR("load cert failed, ret: %d", ret);
        APPV_FREE(cert);
        return V_ERR;
    }
    int len = 0;
    unsigned char *pkBuf = GetPkBuf(&cert->pk, &len);
    if (pkBuf == NULL) {
        LOG_ERROR("get pk error");
        mbedtls_x509_crt_free(cert);
        APPV_FREE(cert);
        return V_ERR;
    }
    pk->pk = (char *)pkBuf;
    pk->len = len;
    mbedtls_x509_crt_free(cert);
    APPV_FREE(cert);
    return V_OK;
}

static int GetAppSignPublicKey(const ProfileProf *profile, AppSignPk *pk)
{
    int ret;
    /* release cert */
    if (profile->bundleInfo.releaseCert &&
        strlen((char *)profile->bundleInfo.releaseCert) != 0) {
        ret = ParseCertGetPk((char *)profile->bundleInfo.releaseCert, pk);
    } else {
        ret = ParseCertGetPk((char *)profile->bundleInfo.devCert, pk);
    }
    if (ret != V_OK) {
        LOG_ERROR("GetSignCertpk failed, ret: %d", ret);
        return V_ERR_GET_CERT_PK;
    }
    return V_OK;
}

static void FreeAppSignPublicKey(AppSignPk *pk)
{
    if (pk->pk != NULL) {
        APPV_FREE(pk->pk);
    }
    return;
}

int GetAppid(ProfileProf *profile)
{
    P_NULL_RETURN_RET_WTTH_LOG(profile, V_ERR);
    AppSignPk pk = {0};
    int ret = GetAppSignPublicKey(profile, &pk);
    if (ret != V_OK) {
        LOG_ERROR("get sign pk failed");
        return ret;
    }
    /* base64 */
    size_t useLen = 0;
    mbedtls_base64_encode(NULL, 0, &useLen, (unsigned char *)pk.pk, pk.len);
    int bundleNameLen = strlen(profile->bundleInfo.bundleName);
    int appidLen = bundleNameLen + useLen + 1 + 1;

    LOG_INFO("GetAppid %d", appidLen);
    if (useLen > MAX_KEY_PAIR_SIZE) {
        return V_ERR;
    }
    char *appid = APPV_MALLOC(appidLen);
    if (appid == NULL) {
        LOG_ERROR("malloc failed");
        FreeAppSignPublicKey(&pk);
        return V_ERR_MALLOC;
    }
    appid[appidLen - 1] = '\0';
    ret = snprintf_s(appid, appidLen, bundleNameLen + 1, "%s_", profile->bundleInfo.bundleName);
    if (ret < 0) {
        LOG_ERROR("snprintf error ret: %d", ret);
        APPV_FREE(appid);
        FreeAppSignPublicKey(&pk);
        return V_ERR_GET_APPID;
    }
    ret = mbedtls_base64_encode((unsigned char *)appid + bundleNameLen + 1,
        appidLen - bundleNameLen - 1, &useLen, (unsigned char *)pk.pk, pk.len);
    if (ret != V_OK) {
        LOG_ERROR("base 64 encode error");
        APPV_FREE(appid);
        FreeAppSignPublicKey(&pk);
        return V_ERR_GET_APPID;
    }
    profile->appid = appid;
    LOG_INFO("appid len: %d, bL len: %d, base64: %d", appidLen, bundleNameLen, (int)useLen);
    LOG_PRINT_STR("%s", appid);
    FreeAppSignPublicKey(&pk);
    return V_OK;
}

static int VerifyProfGetContent(int fp, const SignatureInfo *signInfo, int certType, ProfileProf *pf)
{
    char *profBuf = NULL;
    int len = 0;
    BlockHead blockHead = {0};
    int ret;
    int rawLen = 0;
    char *rawBuf = GetSignBlockByType(signInfo, fp, PROFILE_BLOCK_WITHSIGN_TYPE, &rawLen, &blockHead);
    P_NULL_RETURN_RET_WTTH_LOG(rawBuf, V_ERR_GET_PROFILE_DATA);
    LOG_INFO("certType %d", certType);
    /* app gallary with no sign */
    if (certType == CERT_TYPE_APPGALLARY) {
        profBuf = rawBuf;
        len = rawLen;
    } else {
        /* verify profile */
        ret = VerifyProfileSignGetRaw(rawBuf, rawLen, &profBuf, &len);
        APPV_FREE(rawBuf);
        P_ERR_RETURN_WTTH_LOG(ret);
    }

    ret = ParseProfile(profBuf, len, pf);
    if (ret != V_OK) {
        LOG_ERROR("GetSignBlock error");
        APPV_FREE(profBuf);
        return V_ERR_GET_PARSE_PROFILE;
    }
    APPV_FREE(profBuf);

    ret = VerifyProfileContent(pf);
    P_ERR_GOTO_WTTH_LOG(ret);

    ret = GetAppid(pf);
    P_ERR_GOTO_WTTH_LOG(ret);

    return V_OK;
EXIT:
    ProfFreeData(pf);
    return ret;
}

static int CmpCert(const mbedtls_x509_crt *certA, const CertInfo *binSignCert)
{
    P_NULL_RETURN_RET_WTTH_LOG(certA, V_ERR);
    P_NULL_RETURN_RET_WTTH_LOG(binSignCert, V_ERR);
    /* cmp subject and issuer */
    if (certA->subject_raw.len != binSignCert->subjectLen ||
        memcmp(certA->subject_raw.p, binSignCert->subject, certA->subject_raw.len)) {
        LOG_ERROR("cert subject diff");
        return V_ERR;
    }

    if (certA->issuer_raw.len != binSignCert->issuerLen ||
        memcmp(certA->issuer_raw.p, binSignCert->issuer, certA->issuer_raw.len)) {
        LOG_ERROR("cert issuer diff");
        return V_ERR;
    }

    /* V_OK means same */
    if (mbedtls_pk_get_type(&certA->pk) != binSignCert->pkType) {
        LOG_ERROR("pk type diff");
        return V_ERR;
    }
    int lenA = 0;
    unsigned char *bufA = GetPkBuf(&certA->pk, &lenA);
    P_NULL_RETURN_RET_WTTH_LOG(bufA, V_ERR);

    if (lenA != binSignCert->pkLen) {
        LOG_ERROR("pkA len diff %d, %d", lenA, binSignCert->pkLen);
        APPV_FREE(bufA);
        return V_ERR;
    }

    if (memcmp(bufA, binSignCert->pkBuf, lenA)) {
        LOG_ERROR("pk content diffrent");
        APPV_FREE(bufA);
        return V_ERR;
    }
    APPV_FREE(bufA);
    LOG_INFO("compare cert consistent");
    return V_OK;
}

int LoadCertAndCmpDest(const unsigned char *certBase64, const CertInfo *binSignCert)
{
    if (certBase64 == NULL || binSignCert == NULL) {
        return V_ERR;
    }
    mbedtls_x509_crt cert;
    mbedtls_x509_crt_init(&cert);
    int ret = mbedtls_x509_crt_parse(&cert, certBase64, strlen((char *)certBase64) + 1);
    if (ret != V_OK) {
        LOG_ERROR("load release cert failed");
        LOG_PRINT_STR("%s", certBase64);
        return V_ERR;
    }
    /* cmp cert */
    if (CmpCert(&cert, binSignCert) == V_OK) {
        LOG_INFO("cert consistent");
        mbedtls_x509_crt_free(&cert);
        return V_OK;
    }
    LOG_ERROR("cert inconsistent");
    mbedtls_x509_crt_free(&cert);
    return V_ERR;
}

static int CheckReleaseAppSign(const CertInfo *binSignCert, const ProfileProf *pf)
{
    /* if distribution type is app_gallery, return error */
    if (strcmp(pf->appDistType, "app_gallery") == 0) {
        LOG_ERROR("app release, distribution type is app_gallery, return error");
        return V_ERR;
    }

    if (strlen((char *)pf->bundleInfo.releaseCert) == 0) {
        LOG_ERROR("release app, release Cert null");
        return V_ERR;
    }
    int ret = LoadCertAndCmpDest(pf->bundleInfo.releaseCert, binSignCert);
    if (ret == V_OK) {
        LOG_INFO("dev cert consistent");
        return V_OK;
    }
    LOG_ERROR("app sign cert not consistent with profile cert");
    return V_ERR;
}

static int CheckDebugAppSign(CertInfo *binSignCert, const ProfileProf *pf)
{
    if (strlen((char *)pf->bundleInfo.devCert) == 0) {
        LOG_ERROR("debug app, devCert null");
        return V_ERR;
    }
    int ret = LoadCertAndCmpDest(pf->bundleInfo.devCert, binSignCert);
    if (ret == V_OK) {
        LOG_INFO("dev cert consistent");
        return V_OK;
    }
    if (strlen((char *)pf->bundleInfo.releaseCert) != 0) {
        ret = LoadCertAndCmpDest(pf->bundleInfo.releaseCert, binSignCert);
        if (ret == V_OK) {
            LOG_INFO("release cert consistent");
            return V_OK;
        }
    }
    LOG_ERROR("app sign cert not consistent with profile cert");
    return V_ERR;
}

static int CheckAppSignCertWithProfile(int appCertType, CertInfo *binSignCert, ProfileProf *pf)
{
    /* cert type appgallary or system, not check */
    if (appCertType == CERT_TYPE_APPGALLARY || appCertType == CERT_TYPE_SYETEM) {
        LOG_INFO("app type : %d, return OK", appCertType);
        return V_OK;
    }

    int ret = V_ERR;
    /* debug app, app cert consistent with profile dev or release cert */
    if (strcmp(DEBUG_TYPE, (char *)pf->type) == 0) {
        ret = CheckDebugAppSign(binSignCert, pf);
    } else if (strcmp(RELEASE_TYPE, pf->type) == 0) {
        ret = CheckReleaseAppSign(binSignCert, pf);
    }

    LOG_INFO("check app sign cert ret : %d", ret);
    return ret;
}

static int CertInfoInit(CertInfo *certInfo)
{
    int ret = memset_s(certInfo, sizeof(CertInfo), 0, sizeof(CertInfo));
    if (ret != V_OK) {
        LOG_ERROR("memset error");
    }
    return ret;
}

void FreeCertInfo(CertInfo *certInfo)
{
    if (certInfo == NULL) {
        return;
    }
    if (certInfo->issuer != NULL) {
        APPV_FREE(certInfo->issuer);
        certInfo->issuerLen = 0;
    }

    if (certInfo->subject != NULL) {
        APPV_FREE(certInfo->subject);
        certInfo->subjectLen = 0;
    }

    if (certInfo->pkBuf != NULL) {
        APPV_FREE(certInfo->pkBuf);
        certInfo->pkLen = 0;
    }
    return;
}

static int GetCertInfo(const mbedtls_x509_crt *ctr, CertInfo **binSignCert)
{
    CertInfo *certInfo = APPV_MALLOC(sizeof(CertInfo));
    P_NULL_RETURN_RET_WTTH_LOG(certInfo, V_ERR_MALLOC);

    int ret = CertInfoInit(certInfo);
    if (ret != V_OK) {
        LOG_ERROR("cert info init");
        ret = V_ERR_MEMSET;
        goto EXIT;
    }
    certInfo->issuerLen = ctr->issuer_raw.len;
    certInfo->subjectLen = ctr->subject_raw.len;
    if (certInfo->issuerLen == 0 || certInfo->issuerLen > MAX_PROFILE_SIZE ||
        certInfo->subjectLen == 0 || certInfo->subjectLen > MAX_PROFILE_SIZE) {
        ret = V_ERR_MALLOC;
        goto EXIT;
    }
    certInfo->issuer = APPV_MALLOC(certInfo->issuerLen + 1);
    if (certInfo->issuer == NULL) {
        ret = V_ERR_MALLOC;
        goto EXIT;
    }
    certInfo->issuer[certInfo->issuerLen] = '\0';
    ret = memcpy_s(certInfo->issuer, certInfo->issuerLen, ctr->issuer_raw.p, ctr->issuer_raw.len);
    if (ret != V_OK) {
        ret = V_ERR_MEMCPY;
        goto EXIT;
    }
    certInfo->subject = APPV_MALLOC(certInfo->subjectLen + 1);
    if (certInfo->subject == NULL) {
        ret = V_ERR_MALLOC;
        goto EXIT;
    }
    certInfo->subject[certInfo->subjectLen] = '\0';
    ret = memcpy_s(certInfo->subject, certInfo->subjectLen, ctr->subject_raw.p, ctr->subject_raw.len);
    if (ret != V_OK) {
        ret = V_ERR_MEMCPY;
        goto EXIT;
    }
    certInfo->pkType = mbedtls_pk_get_type(&ctr->pk);
    certInfo->pkBuf = (char *)GetPkBuf(&ctr->pk, &certInfo->pkLen);
    if (certInfo->pkBuf == NULL) {
        LOG_ERROR("get pk error");
        ret = V_ERR;
        goto EXIT;
    }
    *binSignCert = certInfo;
    return V_OK;
EXIT:
    FreeCertInfo(certInfo);
    APPV_FREE(certInfo);
    return ret;
}

static int VerfiyAppSourceGetProfile(int fp, const SignatureInfo *signInfo,
    int certType, CertInfo *binSignCert, ProfileProf *pf)
{
    int ret = VerifyProfGetContent(fp, signInfo, certType, pf);
    if (ret != V_OK) {
        LOG_ERROR("VerifyProfGetContent error: %d", ret);
        return ret;
    }
    LOG_INFO("verify prof get content success");

    /* verfiy profile cert and app sign cert */
    ret = CheckAppSignCertWithProfile(certType, binSignCert, pf);
    if (ret != V_OK) {
        LOG_ERROR("CheckAppSignCertWithProfile error: %d", ret);
        ProfFreeData(pf);
        return V_ERR_VERFIY_PROF_CERT;
    }

    /* free cert */
    FREE_IF_NOT_NULL(pf->bundleInfo.devCert);
    FREE_IF_NOT_NULL(pf->bundleInfo.releaseCert);

    LOG_INFO("verfiy app source success");
    return V_OK;
}

static int VerifyAppSignPkcsData(const FileRead *fileRead, const SignatureInfo *signInfo, const Pkcs7 *pkcs7Handle)
{
    /*  verify sign, rawdata */
    int ret = PKCS7_VerifyCertsChain(pkcs7Handle);
    if (ret != V_OK) {
        LOG_ERROR("Verify certs failed, ret: %d", ret);
        return V_ERR_VERIFY_CERT_CHAIN;
    }
    LOG_INFO("Verify certs success");

    ret = VerifyRawHash(signInfo, fileRead, pkcs7Handle);
    if (ret != V_OK) {
        LOG_ERROR("VerifyRawHash failed : %d", ret);
        return ret;
    }
    LOG_INFO("VerifyRawHash success");

    ret = PKCS7_VerifySignerSignature(pkcs7Handle, CalcDigest);
    if (ret != V_OK) {
        LOG_ERROR("pkcs7 verify signer signature failed : %d", ret);
        return V_ERR_VERIFY_SIGNATURE;
    }

    return V_OK;
}

static Pkcs7 *GetBinSignPkcs(const char *signBuf, int len)
{
    Pkcs7 *pkcs7 = APPV_MALLOC(sizeof(Pkcs7));
    if (pkcs7 == NULL) {
        LOG_ERROR("malloc error");
        return NULL;
    }
    int ret = PKCS7_ParseSignedData((unsigned char *)signBuf, (size_t)len, pkcs7);
    if (ret != V_OK) {
        LOG_ERROR("pkcs7parse message failed, ret: %d", ret);
        APPV_FREE(pkcs7);
        return NULL;
    }
    return pkcs7;
}

static FileRead *GetFileRead(int fp, int offset, int size)
{
    /* raw buf len = sign block head offset */
    FileRead *fileRead = APPV_MALLOC(sizeof(FileRead));
    if (fileRead == NULL) {
        LOG_ERROR("malloc error");
        return NULL;
    }
    fileRead->fp = fp;
    fileRead->offset = offset;
    fileRead->len = size;
    return fileRead;
}
static int VerifyBinSign(SignatureInfo *signInfo, int fp, CertInfo **signCert, int *certType)
{
    int blockLen;
    BlockHead blockHead = {0};
    FileRead *fileRead = NULL;
    int ret;

    char *signBuf = GetSignBlockByType(signInfo, fp, SIGNATURE_BLOCK_TYPE, &blockLen, &blockHead);
    P_NULL_RETURN_RET_WTTH_LOG(signBuf, V_ERR_GET_SIGN_BLOCK);

    Pkcs7 *pkcs7 = GetBinSignPkcs(signBuf, (size_t)blockLen);
    if (pkcs7 == NULL) {
        LOG_ERROR("GetBinSignPkcs failed");
        APPV_FREE(signBuf);
        return V_ERR_PARSE_PKC7_DATA;
    }
    /* pkcs7 handle the content of signBuf, do not free signBuf */
    LOG_INFO("pkcs7 parse message sucess");

    /* raw buf len = sign block head offset */
    fileRead = GetFileRead(fp, 0, blockHead.offset);
    if (fileRead == NULL) {
        LOG_ERROR("malloc error");
        ret = V_ERR_MALLOC;
        goto EXIT;
    }
    ret = GetAppSingerCertType(pkcs7, certType);
    if (ret != V_OK) {
        LOG_ERROR("cert source invalid: %d", ret);
        ret = V_ERR_GET_CERT_TYPE;
        goto EXIT;
    }
    LOG_INFO("get cert Type : %d", *certType);
    signInfo->certType = *certType;
    ret = VerifyAppSignPkcsData(fileRead, signInfo, pkcs7);
    if (ret != V_OK) {
        LOG_ERROR("intergrity failed");
        ret = V_ERR_VERIFY_CERT_CHAIN;
        goto EXIT;
    }
    LOG_INFO("pkcs7 verify signer signature success");

    ret = GetCertInfo(pkcs7->signedData.signers.certPath.crt, signCert);
    if (ret != V_OK) {
        LOG_ERROR("get bin cert info  error: %d", ret);
        ret = V_ERR_GET_CERT_INFO;
        goto EXIT;
    }

EXIT:
    /* free sign */
    APPV_FREE(signBuf);
    /* free pkcs7Handle */
    PKCS7_FreeRes(pkcs7);
    APPV_FREE(pkcs7);
    APPV_FREE(fileRead);
    return ret;
}

static int VerifyIntegrity(SignatureInfo *signInfo, int fp, ProfileProf *pf)
{
    CertInfo *binSignCert = NULL;
    int certType = 0;

    int ret = VerifyBinSign(signInfo, fp, &binSignCert, &certType);
    if (ret != V_OK) {
        LOG_ERROR("verify bin sign error");
        return ret;
    }

    ret = VerfiyAppSourceGetProfile(fp, signInfo, certType, binSignCert, pf);
    if (ret != V_OK) {
        LOG_ERROR("verify app source failed : %d", ret);
        FreeCertInfo(binSignCert);
        APPV_FREE(binSignCert);
        return ret;
    }
    FreeCertInfo(binSignCert);
    APPV_FREE(binSignCert);
    return V_OK;
}

int APPVERI_AppVerify(const char *filePath, VerifyResult *verifyRst)
{
    if (filePath == NULL || verifyRst == NULL) {
        return V_ERR_FILE_OPEN;
    }
    int handle = 0;
    FileRead file = {0};
    if (InitVerify(&file, filePath, &handle) != V_OK) {
        close(handle);
        return V_ERR_FILE_OPEN;
    }
    SignatureInfo signInfo = {0};
    int ret = GetSignHead(&file, &signInfo);
    if (ret != V_OK) {
        LOG_ERROR("get sign head error");
        close(handle);
        return ret;
    }
    HwSignHead *signHead = signInfo.signHead;
    ret = VerifyIntegrity(&signInfo, handle, &verifyRst->profile);
    if (ret != V_OK) {
        LOG_ERROR("verify integrity failed");
        close(handle);
        APPV_FREE(signHead);
        return ret;
    }
    struct stat *fileSt = APPV_MALLOC(sizeof(struct stat));
    if (fileSt == NULL) {
        LOG_PRINT_STR("malloc error");
        close(handle);
        APPV_FREE(signHead);
        return V_ERR_MALLOC;
    }
    ret = fstat(handle, fileSt);
    if (ret != V_OK) {
        LOG_ERROR("fstat error");
        close(handle);
        APPV_FREE(signHead);
        APPV_FREE(fileSt);
        return V_ERR_FILE_STAT;
    }
    LOG_INFO("file len: %d", (int)fileSt->st_size);
    close(handle);
    APPV_FREE(signHead);
    APPV_FREE(fileSt);
    return ret;
}

/* set debug mode */
int APPVERI_SetDebugMode(bool mode)
{
    LOG_INFO("set debug mode: %d", mode);
    if (g_isDebugMode == mode) {
        return V_OK;
    }
    int ret = PKCS7_EnableDebugMode(mode);
    if (ret != V_OK) {
        LOG_ERROR("enable pcks7 debug mode failed");
        return ret;
    }
    g_isDebugMode = mode;
    return V_OK;
}

void APPVERI_FreeVerifyRst(VerifyResult *verifyRst)
{
    if (verifyRst == NULL) {
        return;
    }
    LOG_INFO("free verify rst data");
    ProfFreeData(&verifyRst->profile);
    return;
}