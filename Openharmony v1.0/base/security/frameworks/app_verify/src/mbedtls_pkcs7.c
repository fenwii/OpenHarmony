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

#include "mbedtls_pkcs7.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "app_common.h"
#include "mbedtls/platform.h" // for mbedtls_calloc
#include "securec.h"

#define VERIFY_BUF_LEN 512
#define MAX_SIG_SIZE 1024

#ifndef MBEDTLS_OID_PKCS7
#define MBEDTLS_OID_PKCS7 MBEDTLS_OID_PKCS "\x07"
#endif

#ifndef MBEDTLS_OID_PKCS7_DATA
#define MBEDTLS_OID_PKCS7_DATA MBEDTLS_OID_PKCS7 "\x01"
#endif

#ifndef MBEDTLS_OID_PKCS7_SIGNED_DATA
#define MBEDTLS_OID_PKCS7_SIGNED_DATA MBEDTLS_OID_PKCS7 "\x02"
#endif

#ifndef MBEDTLS_OID_PKCS9_MSG_DIGEST
#define MBEDTLS_OID_PKCS9_MSG_DIGEST MBEDTLS_OID_PKCS9 "\x04"
#endif

#define PKCS7_SIGNED_DATA_VERSION 1
#define PEM_FORMAT_SINGED_DATA 1
#define DER_FORMAT_SINGED_DATA 2

#define PKCS7_ERR_RETURN_WITH_LOG(rc) \
    do { \
        if ((rc) != PKCS7_SUCC) \
        { \
            LOG_ERROR("%s:%u, error occured, ret:%d", __FUNCTION__, __LINE__, (rc)); \
            return rc; \
        } \
    } while (0)

static mbedtls_x509_crt g_rootCaG2Cert;
static bool g_rootCertLoaded;
static const unsigned char g_rootCaG2CertInPem[] =
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIICGjCCAaGgAwIBAgIIShhpn519jNAwCgYIKoZIzj0EAwMwUzELMAkGA1UEBhMC\r\n"
    "Q04xDzANBgNVBAoMBkh1YXdlaTETMBEGA1UECwwKSHVhd2VpIENCRzEeMBwGA1UE\r\n"
    "AwwVSHVhd2VpIENCRyBSb290IENBIEcyMB4XDTIwMDMxNjAzMDQzOVoXDTQ5MDMx\r\n"
    "NjAzMDQzOVowUzELMAkGA1UEBhMCQ04xDzANBgNVBAoMBkh1YXdlaTETMBEGA1UE\r\n"
    "CwwKSHVhd2VpIENCRzEeMBwGA1UEAwwVSHVhd2VpIENCRyBSb290IENBIEcyMHYw\r\n"
    "EAYHKoZIzj0CAQYFK4EEACIDYgAEWidkGnDSOw3/HE2y2GHl+fpWBIa5S+IlnNrs\r\n"
    "GUvwC1I2QWvtqCHWmwFlFK95zKXiM8s9yV3VVXh7ivN8ZJO3SC5N1TCrvB2lpHMB\r\n"
    "wcz4DA0kgHCMm/wDec6kOHx1xvCRo0IwQDAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0T\r\n"
    "AQH/BAUwAwEB/zAdBgNVHQ4EFgQUo45a9Vq8cYwqaiVyfkiS4pLcIAAwCgYIKoZI\r\n"
    "zj0EAwMDZwAwZAIwMypeB7P0IbY7c6gpWcClhRznOJFj8uavrNu2PIoz9KIqr3jn\r\n"
    "BlBHJs0myI7ntYpEAjBbm8eDMZY5zq5iMZUC6H7UzYSix4Uy1YlsLVV738PtKP9h\r\n"
    "FTjgDHctXJlC5L7+ZDY=\r\n"
    "-----END CERTIFICATE-----\r\n";

static mbedtls_x509_crt g_debugModeRootCert;
static bool g_debugModeEnabled;
static const unsigned char g_debugModeRootCertInPem[] =
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIICJTCCAaugAwIBAgIIb/9KnVieVTgwCgYIKoZIzj0EAwMwWDELMAkGA1UEBhMC\r\n"
    "Q04xDzANBgNVBAoMBkh1YXdlaTETMBEGA1UECwwKSHVhd2VpIENCRzEjMCEGA1UE\r\n"
    "AwwaSHVhd2VpIENCRyBSb290IENBIEcyIFRlc3QwHhcNMjAwMzEyMTI0NDAwWhcN\r\n"
    "NDkwMzEyMTI0NDAwWjBYMQswCQYDVQQGEwJDTjEPMA0GA1UECgwGSHVhd2VpMRMw\r\n"
    "EQYDVQQLDApIdWF3ZWkgQ0JHMSMwIQYDVQQDDBpIdWF3ZWkgQ0JHIFJvb3QgQ0Eg\r\n"
    "RzIgVGVzdDB2MBAGByqGSM49AgEGBSuBBAAiA2IABLS4fgvaYKKfyMZW/4nNTsSv\r\n"
    "xqVxqOEDfLySZK/fSEN0IDQj0sK/qK5hvnf0OxWhwI49P3dKGmQ+cSujXvy0me2D\r\n"
    "JTjY127XYZJrvJwwMkrT/vMrZC5kSOEJbt1qAgSmiaNCMEAwDgYDVR0PAQH/BAQD\r\n"
    "AgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFGldwFjx9Tzm/QpA8R1gc9wc\r\n"
    "eMbFMAoGCCqGSM49BAMDA2gAMGUCMQCCUDRaglmycUGrHmF+L8owKJhbqOUqbwuX\r\n"
    "7XL/vJcp3HeHjiXu7XZmYQ+QAvHPhU0CMCiwWFbDl8ETw4VK25QbwhL/QiUfiRfC\r\n"
    "J6LzteOvjLTEV5iebQMz/nS1j7/oj3Rsqg==\r\n"
    "-----END CERTIFICATE-----\r\n";

/* valid digest alg now: sha256 sha384 sha512 */
static bool InvalidDigestAlg(const mbedtls_asn1_buf *alg)
{
    return MBEDTLS_OID_CMP(MBEDTLS_OID_DIGEST_ALG_SHA256, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_DIGEST_ALG_SHA384, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_DIGEST_ALG_SHA512, alg);
}

static int GetContentInfoType(unsigned char **p, const unsigned char *end,
                              mbedtls_asn1_buf *contentType, bool *hasContent)
{
    size_t seqLen = 0;
    size_t len = 0;
    int rc;

    rc = mbedtls_asn1_get_tag(p, end, &seqLen, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
    if (rc) {
        return rc;
    }
    unsigned char *start = *p;
    end = start + seqLen;
    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_OID);
    if (rc) {
        return rc;
    }
    contentType->tag = MBEDTLS_ASN1_OID;
    contentType->len = len;
    contentType->p = *p;
    *hasContent = (seqLen != len + (*p - start));
    *p += len; // pass the oid info to the real content location.

    return rc;
}

static int GetContentLenOfContentInfo(unsigned char **p, const unsigned char *end, size_t *len)
{
    return mbedtls_asn1_get_tag(p, end, len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC);
}

static int ParseSignerVersion(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    return mbedtls_asn1_get_int(p, end, &signer->version);
}

static int ParseSignerIssuerAndSerialNum(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    int rc;
    size_t len;

    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
    if (rc) {
        return rc;
    }

    signer->issuerRaw.p = *p;
    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
    if (rc) {
        return rc;
    }
    /* parse issuer name */
    rc = mbedtls_x509_get_name(p, *p + len, &signer->issuer);
    if (rc) {
        return rc;
    }
    signer->issuerRaw.len = *p - signer->issuerRaw.p; /* not include the serial. */

    rc = mbedtls_x509_get_serial(p, end, &signer->serial);

    return rc;
}

static int ParseSignerDigestAlg(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    int rc = mbedtls_asn1_get_alg_null(p, end, &signer->digestAlgId);
    if (rc) {
        return rc;
    }
    if (InvalidDigestAlg(&signer->digestAlgId)) {
        return PKCS7_INVALID_DIGEST_ALG;
    }
    return rc;
}

static int ParseSignerAuthAttr(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    int rc;
    size_t len = 0;
    unsigned char *raw = *p;

    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC);
    if (rc) {
        return PKCS7_SUCC; /* because this is optional item */
    }
    signer->authAttr.tag = MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC;
    signer->authAttr.p = *p;
    signer->authAttr.len = len;
    size_t tlLen = *p - raw;
    *p += len;

    signer->authAttrRaw.p = raw;
    signer->authAttrRaw.len = len + tlLen;
    return rc;
}

/*
 * check if enc alg is rsa/ecdsa 256/384/512
 */
static bool InvalidDigestEncAlg(const mbedtls_x509_buf *alg)
{
    return MBEDTLS_OID_CMP(MBEDTLS_OID_PKCS1_SHA256, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_PKCS1_SHA384, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_PKCS1_SHA512, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_ECDSA_SHA256, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_ECDSA_SHA384, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_ECDSA_SHA512, alg) &&
        MBEDTLS_OID_CMP(MBEDTLS_OID_RSASSA_PSS, alg);
}

static int ParseSignerEncAlg(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    int rc;
    mbedtls_asn1_buf params = {0};
    /* params not be used now */
    rc = mbedtls_asn1_get_alg(p, end, &signer->digestEncAlgId, &params);
    if (rc) {
        return rc;
    }
    if (InvalidDigestEncAlg(&signer->digestEncAlgId)) {
        return PKCS7_INVALID_SIGNING_ALG;
    }
    return rc;
}

/*
 * encryptedDigest EncryptedDigest,
 *   EncryptedDigest ::= OCTET STRING
 */
static int ParseSignerSignature(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    int rc;
    size_t len = 0;

    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_OCTET_STRING);
    if (rc) {
        return rc;
    }
    signer->signature.tag = MBEDTLS_ASN1_OCTET_STRING;
    signer->signature.len = len;
    signer->signature.p = *p;
    *p += len;
    return rc;
}

static int GetSignerSignature(const SignerInfo *signer, unsigned char **sig, size_t *sigLen)
{
    size_t len = signer->signature.len;
    unsigned char *buf = signer->signature.p;
    *sig = buf;
    *sigLen = len;
    return PKCS7_SUCC;
}

static int ParseSignerUnAuthAttr(unsigned char **p, const unsigned char *end, SignerInfo *signer)
{
    int rc;
    size_t len = 0;

    /* the optional unauth attr is not exist */
    if (end - *p < 1) {
        return PKCS7_SUCC;
    }
    rc = mbedtls_asn1_get_tag(p, end, &len, (MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC) + 1);
    if (rc) {
        return rc;
    }
    signer->unAuthAttr.tag = (MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC) + 1;
    signer->unAuthAttr.len = len;
    signer->unAuthAttr.p = *p;
    *p += len;
    return rc;
}

static int SerialCmp(const mbedtls_x509_buf *a, const mbedtls_x509_buf *b)
{
    if (a->len == b->len && memcmp(a->p, b->p, a->len) == 0) {
        return 0;
    }
    return -1;
}

#define DIFF_NUM 32
static bool IsLegitString(int tag)
{
    if (tag == MBEDTLS_ASN1_UTF8_STRING || tag == MBEDTLS_ASN1_PRINTABLE_STRING) {
        return true;
    }
    return false;
}

static int CompareX509String(const mbedtls_x509_buf *first, const mbedtls_x509_buf *second)
{
    if (IsLegitString(first->tag) && IsLegitString(second->tag)) {
        for (int i = 0; i < first->len; i++) {
            if (first->p[i] == second->p[i] ||
                ((islower(first->p[i]) != 0) && (first->p[i] - DIFF_NUM == second->p[i])) ||
                ((isupper(first->p[i]) != 0) && (first->p[i] + DIFF_NUM == second->p[i]))) {
                continue;
            }
            return -1;
        }
        return 0;
    }
    return -1;
}

static int GetDeps(const mbedtls_x509_name *nameList)
{
    int deps = 0;
    while (nameList != NULL) {
        nameList = nameList->next;
        deps++;
    }
    return deps;
}

static int CompareX509NameList(const mbedtls_x509_name *first, const mbedtls_x509_name *second)
{
    if (first == NULL || second == NULL) {
        return -1;
    }
    int firstDeps = GetDeps(first);
    int secondDeps = GetDeps(second);
    if (firstDeps != secondDeps) {
        return -1;
    }
    for (int i = 0; i < firstDeps; i++) {
        if (first->oid.tag != second->oid.tag ||
            first->oid.len != second->oid.len ||
            memcmp(first->oid.p, second->oid.p, second->oid.len) != 0 ||
            first->next_merged != second->next_merged ||
            first->val.len != second->val.len) {
            return -1;
        }
        if (CompareX509String(&first->val, &second->val) != 0) {
            return -1;
        }
        first = first->next;
        second = second->next;
    }
    return 0;
}

static void *Pkcs7Calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

static void Pkcs7Free(void *ptr)
{
    free(ptr);
}

static int ParseSignedDataSignerInfos(unsigned char **p, const unsigned char *end, SignerInfo *signers)
{
    int rc;
    size_t len = 0;

    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SET);
    if (rc || len == 0) {
        return PKCS7_HAS_NO_SIGNER_INFO;
    }
    end = *p + len; // update end to the SET end.

    while (*p < end) {
        size_t oneSignerLen;
        unsigned char *oneSignerEnd = NULL;
        /* parse one signer info */
        rc = mbedtls_asn1_get_tag(p, end, &oneSignerLen, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        oneSignerEnd = *p + oneSignerLen;
        /* parse version */
        rc = ParseSignerVersion(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        /* parse issuerAndSerialNum */
        rc = ParseSignerIssuerAndSerialNum(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        /* parse digestAlgorithm */
        rc = ParseSignerDigestAlg(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        /* parse authenticatedAttributes */
        rc = ParseSignerAuthAttr(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        /* parse digestEncryptionAlgorithm */
        rc = ParseSignerEncAlg(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        /* parse encryptedDigest */
        rc = ParseSignerSignature(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        /* parse unauthenticatedAttributes */
        rc = ParseSignerUnAuthAttr(p, oneSignerEnd, signers);
        PKCS7_ERR_RETURN_WITH_LOG(rc);

        if (*p < end) {
            signers->next = Pkcs7Calloc(1, sizeof(*signers));
            if (signers->next == NULL) {
                /* release resource in main entry. */
                return PKCS7_MEMORY_EXHAUST;
            }
            signers = signers->next;
        }
    }
    return rc;
}

static int ParseSignedDataVersion(unsigned char **p, const unsigned char *end, int *ver)
{
    int rc = mbedtls_asn1_get_int(p, end, ver);
    if (rc) {
        return rc;
    }

    if (*ver != PKCS7_SIGNED_DATA_VERSION) {
        LOG_ERROR("Invalid version : %d\n", *ver);
        return PKCS7_INVALID_VERSION;
    }
    LOG_INFO("Parse signed data version success\n");
    return PKCS7_SUCC;
}

static int ParseSignedDataDigestAlgs(unsigned char **p, const unsigned char *end, DigestAlgId *algIds)
{
    int rc;
    size_t len = 0;

    /* parse SET OF header */
    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SET);
    if (rc) {
        return rc;
    }
    end = *p + len;

    /* parse SET OF 's digest alg content */
    DigestAlgId *id = algIds;
    while (*p < end) {
        mbedtls_asn1_buf params = {0};
        /* alg param is supported, but not be used now */
        rc = mbedtls_asn1_get_alg(p, end, &id->algBuf, &params);
        if (rc) {
            return rc;
        }
        if (InvalidDigestAlg(&id->algBuf)) {
            return PKCS7_INVALID_DIGEST_ALG;
        }
        if (*p < end) {
            id->next = Pkcs7Calloc(1, sizeof(DigestAlgId));
            if (id->next == NULL) {
                /* resource will be released in parse main entry */
                return PKCS7_MEMORY_EXHAUST;
            }
            id = id->next;
        }
    }
    return PKCS7_SUCC;
}

static void DlogContentInfo(const Content *content)
{
    int len = content->data.len;
    if (len <= 0) {
        return;
    }
    char *info = Pkcs7Calloc(len + 1, sizeof(char));
    if (info == NULL) {
        return;
    }
    if (strncpy_s(info, len + 1, (char *)content->data.p, len) != EOK) {
        Pkcs7Free(info);
        return;
    }
    Pkcs7Free(info);
}

static int ParseSignedDataContentInfo(unsigned char **p, const unsigned char *end, Content *content)
{
    int rc;
    size_t len = 0;
    bool hasContent = false;

    rc = GetContentInfoType(p, end, &content->oid, &hasContent);
    if (rc) {
        return rc;
    }

    if (MBEDTLS_OID_CMP(MBEDTLS_OID_PKCS7_DATA, &content->oid) || !hasContent) {
        LOG_ERROR("Invalid content type or has no real content");
        return PKCS7_INVALID_CONTENT_TYPE_OR_NO_CONTENT;
    }
    rc = GetContentLenOfContentInfo(p, end, &len);
    if (rc) {
        return rc;
    }
    content->data.tag = MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC; // has no use
    content->data.p = *p;
    content->data.len = len;
    DlogContentInfo(content);
    *p += len;
    return rc;
}

static int ParseSignedDataCerts(unsigned char **p, const unsigned char *end, mbedtls_x509_crt **certs)
{
    int rc;
    size_t len = 0;

    rc = mbedtls_asn1_get_tag(p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC);
    if (rc) {
        LOG_ERROR("Has no certificates in signed data.");
        return PKCS7_SUCC;
    }
    *certs = mbedtls_calloc(1, sizeof(**certs));
    if (*certs == NULL) {
        return PKCS7_MEMORY_EXHAUST;
    }
    mbedtls_x509_crt_init(*certs);

    unsigned char *certsEnd = *p + len;
    int cnt = 0;
    while (*p < certsEnd) {
        /* scan every cert */
        size_t oneCertLen;
        unsigned char *seqBegin = *p;
        rc = mbedtls_asn1_get_tag(p, end, &oneCertLen, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
        if (rc) {
            return rc;
        }
        if (oneCertLen + (*p - seqBegin) > (certsEnd - seqBegin)) {
            return PKCS7_PARSING_ERROR;
        }
        rc = mbedtls_x509_crt_parse(*certs, seqBegin, oneCertLen + (*p - seqBegin));
        if (rc) {
            return rc;
        }
        *p += oneCertLen;
        cnt++;
    }
    LOG_INFO("Parse signed data certs success");
    return rc;
}

static int ParseSignedDataCrl(unsigned char **p, const unsigned char *end, mbedtls_x509_crl *crl)
{
    int rc;
    size_t len = 0;

    rc = mbedtls_asn1_get_tag(p, end, &len, (MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC) + 1);
    if (rc) {
        LOG_INFO("Has no crl in signed data.");
        return PKCS7_SUCC;
    }
    mbedtls_x509_crl_init(crl);
    rc = mbedtls_x509_crl_parse(crl, *p, len);
    *p += len;
    return rc;
}

static int ParseSignedData(unsigned char *buf, size_t bufLen, SignedData *signedData)
{
    unsigned char *p = buf;
    unsigned char *end = buf + bufLen;
    size_t len = 0;
    int rc;

    /* parse SignedData sequence header */
    rc = mbedtls_asn1_get_tag(&p, end, &len, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
    if (rc) {
        return rc;
    }

    /* parse version of signed data */
    rc = ParseSignedDataVersion(&p, end, &signedData->version);
    if (rc) {
        return rc;
    }

    /* parse digestAlgorithms */
    rc = ParseSignedDataDigestAlgs(&p, end, &signedData->digestAlgIds);
    if (rc) {
        return rc;
    }

    /* parse contentInfo */
    rc = ParseSignedDataContentInfo(&p, end, &signedData->content);
    if (rc) {
        return rc;
    }

    if (p >= end) {
        return PKCS7_PARSING_ERROR;
    }
    /* parse certificates (optional) */
    rc = ParseSignedDataCerts(&p, end, &signedData->certs);
    if (rc) {
        return rc;
    }

    /* parse crls (optional) */
    rc = ParseSignedDataCrl(&p, end, &signedData->crl);
    if (rc) {
        return rc;
    }

    /* parse signerInfos */
    rc = ParseSignedDataSignerInfos(&p, end, &signedData->signers);
    LOG_INFO("ParseSignedData %d", rc);
    return rc;
}

static bool IsSigedDataOid(const Pkcs7 *pkcs7)
{
    return !MBEDTLS_OID_CMP(MBEDTLS_OID_PKCS7_SIGNED_DATA, &pkcs7->contentTypeOid);
}

static void FreeSignedDataDigestAlgs(Pkcs7 *pkcs7)
{
    DigestAlgId *alg = pkcs7->signedData.digestAlgIds.next;
    DigestAlgId *next = NULL;

    while (alg != NULL) {
        next = alg->next;
        Pkcs7Free(alg);
        alg = next;
    }
    pkcs7->signedData.digestAlgIds.next = NULL;
}

static void FreeSignerCerts(SignerInfo *signer)
{
    if (signer->certPath.crt != NULL) {
        mbedtls_x509_crt_free(signer->certPath.crt);
        mbedtls_free(signer->certPath.crt);
        signer->certPath.crt = NULL;
    }
}

static void FreeSignerIssuer(SignerInfo *signer)
{
    mbedtls_x509_name *name_cur = NULL;
    mbedtls_x509_name *name_prv = NULL;
    name_cur = signer->issuer.next;
    while (name_cur != NULL) {
        name_prv = name_cur;
        name_cur = name_cur->next;
        mbedtls_free(name_prv);
    }
    signer->issuer.next = NULL;
}

static void FreeSignersInfo(Pkcs7 *pkcs7)
{
    SignerInfo *signer = pkcs7->signedData.signers.next;
    SignerInfo *next = NULL;

    while (signer != NULL) {
        next = signer->next;
        FreeSignerCerts(signer);
        FreeSignerIssuer(signer);
        Pkcs7Free(signer);
        signer = next;
    }
    pkcs7->signedData.signers.next = NULL;
    FreeSignerCerts(&pkcs7->signedData.signers);
    FreeSignerIssuer(&pkcs7->signedData.signers);
}

static void FreeSignedDataCerts(Pkcs7 *pkcs7)
{
    if (pkcs7->signedData.certs != NULL) {
        mbedtls_x509_crt_free(pkcs7->signedData.certs);
        mbedtls_free(pkcs7->signedData.certs);
        pkcs7->signedData.certs = NULL;
    }
}

static void FreeSignedDataCrl(Pkcs7 *pkcs7)
{
    mbedtls_x509_crl_free(&pkcs7->signedData.crl);
    return;
}

static int GetCertsNumOfSignedData(const mbedtls_x509_crt *crts)
{
    int cnt = 0;
    while (crts != NULL) {
        crts = crts->next;
        cnt++;
    }
    return cnt;
}

static mbedtls_x509_crt *FindSuperCert(mbedtls_x509_crt *cur, mbedtls_x509_crt *certsList)
{
    /* current level's subject is next level issuer */
    while (certsList != NULL) {
        if (CompareX509NameList(&cur->issuer, &certsList->subject) == 0) {
            break;
        }
        certsList = certsList->next;
    }
    return certsList;
}

static void DelCertOfSignedData(SignedData *signedData, mbedtls_x509_crt *crt)
{
    mbedtls_x509_crt *head = signedData->certs;
    if (crt == head) {
        signedData->certs = crt->next;
        crt->next = NULL;
    } else {
        mbedtls_x509_crt *prev = head;
        while (head != NULL) {
            if (head == crt) {
                prev->next = crt->next;
                crt->next = NULL;
                break;
            }
            prev = head;
            head = head->next;
        }
    }
}

static void AddCertToSignerCertPath(SignerInfo *signer, mbedtls_x509_crt *crt)
{
    mbedtls_x509_crt *prev = signer->certPath.crt;
    mbedtls_x509_crt *cur = prev;
    if (prev == NULL) {
        signer->certPath.crt = crt;
        crt->next = NULL;
    } else {
        while (cur != NULL) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = crt;
        crt->next = NULL;
    }

    signer->certPath.depth++;
}

static int BuildSignerCertPath(SignerInfo *signer, mbedtls_x509_crt *lowerCrt, SignedData *signeData)
{
    int scanCnt = 0;
    int rc = PKCS7_SUCC;
    if (!g_rootCertLoaded) {
        return PKCS7_ROOT_CA_NOT_VALID;
    }
    signer->rootCert = &g_rootCaG2Cert;

    mbedtls_x509_crt *certs = signeData->certs;
    /* From the root ca cert, to found the signer secondary ca , and use secondary cert to
     * find the next level ca cert */
    mbedtls_x509_crt *cur = lowerCrt;
    mbedtls_x509_crt *next = NULL;
    int certsCnt = GetCertsNumOfSignedData(certs);
    DelCertOfSignedData(signeData, cur);
    AddCertToSignerCertPath(signer, cur);
    while (true) {
        next = FindSuperCert(cur, signeData->certs);
        if (next == NULL) {
            break;
        } else {
            DelCertOfSignedData(signeData, next);
            AddCertToSignerCertPath(signer, next);
        }
        scanCnt++;
        if (scanCnt > certsCnt) {
            rc = PKCS7_BUILD_CERT_PATH_FAIL;
            break;
        }
        cur = next;
    }
    return rc;
}

static int ConstructSignerCerts(SignedData *signedData)
{
    /* scan all of the signers , and filter the signer's certs by serial and name */
    SignerInfo *signer = &signedData->signers;
    while (signer != NULL) {
        mbedtls_x509_buf *signerSerial = &signer->serial;
        mbedtls_x509_name *signerIssuer = &signer->issuer;
        mbedtls_x509_crt *cert = signedData->certs;
        LOG_INFO("To filter one signer's cert");
        while (cert != NULL) {
            if (SerialCmp(signerSerial, &cert->serial) == 0 &&
                CompareX509NameList(signerIssuer, &cert->issuer) == 0) {
                LOG_INFO("Found signer's low level cert");
                break;
            }
            cert = cert->next;
        }
        if (cert == NULL) {
            LOG_ERROR("Could not found signer's lowest cert");
            return PKCS7_INVALID_VALUE;
        }
        int rc = BuildSignerCertPath(signer, cert, signedData);
        if (rc != 0) {
            return rc;
        }
        signer = signer->next;
    }
    return 0;
}

/* get signer digest alg */
static int GetSignerDigestAlg(const SignerInfo *signer, mbedtls_md_type_t *algType)
{
    const mbedtls_x509_buf *alg = &signer->digestAlgId;
    if (!MBEDTLS_OID_CMP(MBEDTLS_OID_DIGEST_ALG_SHA256, alg)) {
        *algType = MBEDTLS_MD_SHA256;
        return PKCS7_SUCC;
    }
    if (!MBEDTLS_OID_CMP(MBEDTLS_OID_DIGEST_ALG_SHA384, alg)) {
        *algType = MBEDTLS_MD_SHA384;
        return PKCS7_SUCC;
    }
    if (!MBEDTLS_OID_CMP(MBEDTLS_OID_DIGEST_ALG_SHA512, alg)) {
        *algType = MBEDTLS_MD_SHA512;
        return PKCS7_SUCC;
    }
    return PKCS7_INVALID_DIGEST_ALG;
}

/* get signer pubkey of sign from signer cert */
static int GetSignerPubKeyOfSignature(const SignerInfo *signer, mbedtls_pk_context **pk)
{
    /* signer cert_path first cert is the lowest cert. yet is the signature cert */
    if (signer == NULL || pk == NULL) {
        return PKCS7_INVALID_PARAM;
    }
    if (signer->certPath.crt != NULL) {
        *pk = &signer->certPath.crt->pk;
        return PKCS7_SUCC;
    }
    return PKCS7_INVALID_VALUE;
}

int PKCS7_VerifySignerSignature(const Pkcs7 *pkcs7, PKCS7_CalcDigest calcDigest)
{
    int rc;
    if (pkcs7 == NULL || calcDigest == NULL) {
        return PKCS7_INVALID_PARAM;
    }
    const SignerInfo *signer = &pkcs7->signedData.signers;
    unsigned char *sig = NULL;
    size_t sigLen;
    while (signer != NULL) {
        rc = GetSignerSignature(signer, &sig, &sigLen);
        if (rc) {
            return rc;
        }
        LOG_INFO("get signer signature len : %zu", sigLen);

        mbedtls_pk_context *pk = NULL;
        rc = GetSignerPubKeyOfSignature(signer, &pk);
        if (rc) {
            return rc;
        }
        mbedtls_md_type_t digAlg;
        rc = GetSignerDigestAlg(signer, &digAlg);
        if (rc) {
            return rc;
        }
        unsigned char hash[MAX_HASH_SIZE];
        (void)memset_s(hash, MAX_HASH_SIZE, 0, MAX_HASH_SIZE);
        size_t hashLen = 0;
        rc = calcDigest(pkcs7, signer, digAlg, hash, &hashLen);
        if (rc) {
            LOG_ERROR("Calculate content hash failed by calling callback");
            return rc;
        }
        /* if is rsassa-pss, need to set padding version to V21, RFC3447 */
        if (!MBEDTLS_OID_CMP(MBEDTLS_OID_RSASSA_PSS, &signer->digestEncAlgId)) {
            mbedtls_rsa_set_padding(pk->pk_ctx, MBEDTLS_RSA_PKCS_V21, 0);
        }
        rc = mbedtls_pk_verify(pk, digAlg, hash, hashLen, sig, sigLen);
        (void)memset_s(hash, MAX_HASH_SIZE, 0, MAX_HASH_SIZE);
        if (rc) {
            LOG_ERROR("Verify signature failed, returned -0x%04x", rc);
            return rc;
        } else {
            LOG_INFO("Verify signer signature success\n");
        }
        signer = signer->next;
    }
    return rc;
}

static int LoadRootCert(void)
{
    int rc = 0;
    if (!g_rootCertLoaded) {
        mbedtls_x509_crt_init(&g_rootCaG2Cert);
        rc = mbedtls_x509_crt_parse(&g_rootCaG2Cert, g_rootCaG2CertInPem, sizeof(g_rootCaG2CertInPem));
        if (rc) {
            LOG_ERROR("load root ca failed");
            return rc;
        } else {
            LOG_INFO("load root ca success");
        }
        g_rootCertLoaded = true;
    }
    return rc;
}

static void UnLoadRootCert(void)
{
    if (g_rootCertLoaded) {
        mbedtls_x509_crt_free(&g_rootCaG2Cert);
        g_rootCertLoaded = false;
    }
}

static int LoadDebugModeRootCert(void)
{
    int rc;
    mbedtls_x509_crt_init(&g_debugModeRootCert);
    rc = mbedtls_x509_crt_parse(&g_debugModeRootCert, g_debugModeRootCertInPem, sizeof(g_debugModeRootCertInPem));
    if (rc) {
        LOG_ERROR("load debug mode root ca failed %d", rc);
        return rc;
    } else {
        LOG_INFO("load debug mode root ca success");
    }
    return rc;
}
static int UnLoadDebugModeRootCert(void)
{
    mbedtls_x509_crt_free(&g_debugModeRootCert);
    return PKCS7_SUCC;
}

static void DLogCrtVerifyInfo(unsigned int flags)
{
    char vrfyBuf[VERIFY_BUF_LEN];
    (void)memset_s(vrfyBuf, VERIFY_BUF_LEN, 0, VERIFY_BUF_LEN);
    mbedtls_x509_crt_verify_info(vrfyBuf, sizeof(vrfyBuf), " ! ", flags);
    LOG_DEBUG("%s", vrfyBuf);
}

static int IsRevoked(const mbedtls_x509_crt *crt, const mbedtls_x509_crl *crl)
{
    mbedtls_x509_crl_entry *cur = (mbedtls_x509_crl_entry *)(&crl->entry);
    while (cur != NULL) {
        if (cur->serial.len == 0) {
            return PKCS7_SUCC;
        }
        if (crt->serial.len != cur->serial.len) {
            cur = cur->next;
            continue;
        }
        if (memcmp(crt->serial.p, cur->serial.p, cur->serial.len) == 0) {
            return PKCS7_IS_REVOKED;
        }
        cur = cur->next;
    }
    return PKCS7_SUCC;
}

static int VerifyCrl(const mbedtls_x509_crt *crt, const mbedtls_x509_crl *crl)
{
    const mbedtls_x509_crl *crlList = crl;
    while (crlList != NULL) {
        if (crlList->version == 0 ||
            CompareX509NameList(&crlList->issuer, &crt->issuer) != 0) {
            crlList = crlList->next;
            continue;
        }
        LOG_INFO("find crl");
        if (IsRevoked(crt, crlList)) {
            return PKCS7_IS_REVOKED;
        }
        crlList = crlList->next;
    }
    return PKCS7_SUCC;
}

static int VerifyClicert(mbedtls_x509_crt *clicert, mbedtls_x509_crt *rootCert, const Pkcs7 *pkcs7)
{
    unsigned int flags;
    int rc = mbedtls_x509_crt_verify(clicert, rootCert,
        (mbedtls_x509_crl *)&pkcs7->signedData.crl, NULL, &flags, NULL, NULL);
    if (rc) {
        DLogCrtVerifyInfo(flags);
    } else {
        LOG_INFO("Verify signers cert chain root cert success");
        if (VerifyCrl(clicert, (mbedtls_x509_crl *)&pkcs7->signedData.crl) != PKCS7_SUCC) {
            LOG_ERROR("cert crl verify failed");
            return PKCS7_IS_REVOKED;
        }
        return PKCS7_SUCC;
    }
    return rc;
}

int PKCS7_VerifyCertsChain(const Pkcs7 *pkcs7)
{
    if (pkcs7 == NULL) {
        return PKCS7_INVALID_PARAM;
    }
    int cnt = 0;
    const SignerInfo *signer = &pkcs7->signedData.signers;
    while (signer != NULL) {
        mbedtls_x509_crt *clicert = signer->certPath.crt;
        if (clicert == NULL) {
            signer = signer->next;
            LOG_ERROR("Signer has no certs");
            return PKCS7_HAS_NO_SIGNER_CRT;
        }
        int rc;
        cnt++;
        LOG_INFO("signer : %d", cnt);
        if (g_debugModeEnabled) {
            rc = VerifyClicert(clicert, &g_debugModeRootCert, pkcs7);
            LOG_DEBUG("Verify inner: %d", rc);
            if (rc == PKCS7_SUCC) {
                signer = signer->next;
                continue;
            }
            if (rc == PKCS7_IS_REVOKED) {
                return PKCS7_IS_REVOKED;
            }
        }
        rc = VerifyClicert(clicert, signer->rootCert, pkcs7);
        LOG_DEBUG("Verify : %d", rc);
        if (rc == PKCS7_SUCC) {
            signer = signer->next;
            continue;
        }
        return rc;
    }
    return PKCS7_SUCC;
}

int PKCS7_GetSignerSignningCertSubject(const SignerInfo *signer, char *subject, size_t subjectLen)
{
    int rc;
    if (signer == NULL || subject == NULL) {
        return PKCS7_INVALID_PARAM;
    }
    const mbedtls_x509_crt *crt = signer->certPath.crt;
    rc = mbedtls_x509_dn_gets(subject, subjectLen, &crt->subject);
    if (rc < 0) {
        return rc;
    }
    return PKCS7_SUCC;
}

int PKCS7_GetSignerSignningCertIssuer(const SignerInfo *signer, char *issuer, size_t issuerLen)
{
    int rc;
    if (signer == NULL || issuer == NULL) {
        return PKCS7_INVALID_PARAM;
    }
    const mbedtls_x509_crt *crt = signer->certPath.crt;
    rc = mbedtls_x509_dn_gets(issuer, issuerLen, &crt->issuer);
    if (rc < 0) {
        return rc;
    }
    return PKCS7_SUCC;
}

static size_t GetSignersCnt(const SignerInfo *signers)
{
    size_t cnt = 0;
    while (signers != NULL) {
        cnt++;
        signers = signers->next;
    }
    return cnt;
}
static size_t GetSignerSignningCertDepth(const SignerInfo *signer)
{
    return signer->certPath.depth + 1; // 1 for root cert;
}

void PKCS7_FreeAllSignersResolvedInfo(SignersResovedInfo *sri)
{
    if (sri == NULL) {
        return;
    }
    if (sri->signers != NULL) {
        Pkcs7Free(sri->signers);
        sri->signers = NULL;
    }
    Pkcs7Free(sri);
}

SignersResovedInfo *PKCS7_GetAllSignersResolvedInfo(const Pkcs7 *pkcs7)
{
    SignersResovedInfo *sri = NULL;
    if (pkcs7 == NULL) {
        return NULL;
    }
    size_t signersCnt = GetSignersCnt(&pkcs7->signedData.signers);
    if (signersCnt == 0) {
        return NULL;
    }
    sri = Pkcs7Calloc(1, sizeof(*sri));
    if (sri == NULL) {
        return NULL;
    }
    sri->nrOfSigners = signersCnt;
    sri->signers = Pkcs7Calloc(signersCnt, sizeof(SignerResovledInfo));
    if (sri->signers == NULL) {
        Pkcs7Free(sri);
        return NULL;
    }
    int rc;
    const SignerInfo *signer = &pkcs7->signedData.signers;
    int idx = 0;
    while (signer != NULL && idx < signersCnt) {
        rc = PKCS7_GetSignerSignningCertSubject(signer, sri->signers[idx].subject, sizeof(sri->signers[idx].subject));
        if (rc) {
            goto OUT;
        }
        rc = PKCS7_GetSignerSignningCertIssuer(signer, sri->signers[idx].issuer, sizeof(sri->signers[idx].issuer));
        if (rc) {
            goto OUT;
        }
        sri->signers[idx].depth = GetSignerSignningCertDepth(signer);

        signer = signer->next;
        idx++;
    }
    return sri;
OUT:
    PKCS7_FreeAllSignersResolvedInfo(sri);
    return NULL;
}

int PKCS7_GetDigestInSignerAuthAttr(const SignerInfo *signer, unsigned char **dig, size_t *digLen)
{
    if (signer == NULL || dig == NULL || digLen == NULL) {
        return PKCS7_INVALID_VALUE;
    }
    unsigned char *p = signer->authAttr.p;
    unsigned char *end = p + signer->authAttr.len;
    size_t tmpLen = 0;
    int rc;

    if (p == NULL) {
        return PKCS7_HAS_NO_AUTH_ATTR_IN_SIGNER;
    }
    /* SET OF SEQUENCE */
    while (p < end) {
        size_t seqLen;
        unsigned char *seqEnd = NULL;
        rc = mbedtls_asn1_get_tag(&p, end, &seqLen, MBEDTLS_ASN1_SEQUENCE | MBEDTLS_ASN1_CONSTRUCTED);
        if (rc) {
            return rc;
        }
        seqEnd = p + seqLen;
        /* SEQUENCE : OID and SET */
        size_t oidLen;
        rc = mbedtls_asn1_get_tag(&p, seqEnd, &oidLen, MBEDTLS_ASN1_OID);
        if (rc) {
            return rc;
        }
        if (oidLen == MBEDTLS_OID_SIZE(MBEDTLS_OID_PKCS9_MSG_DIGEST) &&
            memcmp(p, MBEDTLS_OID_PKCS9_MSG_DIGEST, MBEDTLS_OID_SIZE(MBEDTLS_OID_PKCS9_MSG_DIGEST)) == 0) {
            p += oidLen;
            rc = mbedtls_asn1_get_tag(&p, seqEnd, &tmpLen, MBEDTLS_ASN1_SET | MBEDTLS_ASN1_CONSTRUCTED);
            if (rc) {
                return rc;
            }
            /* we just resolve one now. */
            rc = mbedtls_asn1_get_tag(&p, seqEnd, &tmpLen, MBEDTLS_ASN1_OCTET_STRING);
            if (rc) {
                return rc;
            }
            *dig = p;
            *digLen = tmpLen;
            return PKCS7_SUCC;
        } else {
            p = seqEnd;
        }
    }
    return PKCS7_INVALID_VALUE;
}

int PKCS7_GetSignerAuthAttr(const SignerInfo *signer, unsigned char **data, size_t *dataLen)
{
    if (signer == NULL || signer->authAttrRaw.p == NULL || data == NULL || dataLen == NULL) {
        return PKCS7_INVALID_VALUE;
    }
    *dataLen = signer->authAttrRaw.len;
    *data = signer->authAttrRaw.p;
    *(unsigned char *)signer->authAttrRaw.p = MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SET;
    return PKCS7_SUCC;
}

int PKCS7_GetContentData(const Pkcs7 *pkcs7, unsigned char **data, size_t *dataLen)
{
    if (pkcs7 == NULL || data == NULL || dataLen == NULL) {
        return PKCS7_INVALID_PARAM;
    }

    unsigned char *p = pkcs7->signedData.content.data.p;
    size_t len = pkcs7->signedData.content.data.len;
    unsigned char *end = p + len;
    size_t octetLen;
    int rc = mbedtls_asn1_get_tag(&p, end, &octetLen, MBEDTLS_ASN1_OCTET_STRING);
    if (rc != 0) {
        return rc;
    }
    *data = p;
    *dataLen = octetLen;
    return PKCS7_SUCC;
}

int PKCS7_EnableDebugMode(bool mode)
{
    if (g_debugModeEnabled == mode) {
        return PKCS7_SUCC;
    }
    int rc = ((mode == true) ? LoadDebugModeRootCert() : UnLoadDebugModeRootCert());
    if (rc) {
        return rc;
    }
    g_debugModeEnabled = mode;
    return rc;
}

#ifdef PARSE_PEM_FORMAT_SIGNED_DATA
static int ParsePemFormatSignedData(const unsigned char *buf, size_t bufLen, mbedtls_pem_context *pem, char *format)
{
    if (bufLen != 0 && strstr((const char *)buf, "-----BEGIN PKCS7-----") != NULL) {
        int ret;
        size_t useLen = 0;
        mbedtls_pem_init(pem);
        ret = mbedtls_pem_read_buffer(pem, "-----BEGIN PKCS7-----", "-----END PKCS7-----",
                                      buf, NULL, 0, &useLen);
        if (ret == 0 && useLen == bufLen) {
            *format = PEM_FORMAT_SINGED_DATA;
            return PKCS7_SUCC;
        }
        mbedtls_pem_free(pem);
    } else {
        *format = DER_FORMAT_SINGED_DATA;
        return PKCS7_SUCC; // DER format
    }
    return PKCS7_INVALID_PARAM;
}
#endif

int PKCS7_ParseSignedData(const unsigned char *buf, size_t bufLen, Pkcs7 *pkcs7)
{
    int rc;
    size_t len = 0;
    bool hasContent = false;
    unsigned char *start = NULL;
    unsigned char *end = NULL;
    if (buf == NULL || bufLen == 0 || pkcs7 == NULL) {
        return PKCS7_INVALID_PARAM;
    }
    (void)memset_s(pkcs7, sizeof(*pkcs7), 0, sizeof(*pkcs7));
    start = (unsigned char *)buf;
#ifdef PARSE_PEM_FORMAT_SIGNED_DATA
    char format = 0;
    rc = ParsePemFormatSignedData(buf, bufLen, &pkcs7->pem, &format);
    if (rc) {
        goto EXIT;
    }
    if (format == PEM_FORMAT_SINGED_DATA) {
        start = pkcs7->pem.buf;
        bufLen = pkcs7->pem.buflen;
    }
#endif
    end = start + bufLen;
    /* loaded the root ca cert */
    rc = LoadRootCert();
    P_ERR_GOTO_WTTH_LOG(rc);
    LOG_INFO("Begin to parse pkcs#7 signed data");
    /* parse the ContentInfo total head */
    rc = GetContentInfoType(&start, end, &(pkcs7->contentTypeOid), &hasContent);
    P_ERR_GOTO_WTTH_LOG(rc);
    if (!IsSigedDataOid(pkcs7) || !hasContent) {
        rc = PKCS7_INVALID_CONTENT_TYPE_OR_NO_CONTENT;
        LOG_ERROR("Input data is not pkcs#7 signed data format or has no content info");
        goto EXIT;
    }
    rc = GetContentLenOfContentInfo(&start, end, &len);
    P_ERR_GOTO_WTTH_LOG(rc);
    if (start + len > end) {
        goto EXIT;
    }
    rc = ParseSignedData(start, len, &(pkcs7->signedData));
    P_ERR_GOTO_WTTH_LOG(rc);
    LOG_INFO("Parse pkcs#7 signed data success");
    rc = ConstructSignerCerts(&pkcs7->signedData);
    P_ERR_GOTO_WTTH_LOG(rc);
    return rc;
EXIT:
    PKCS7_FreeRes(pkcs7);
    return rc;
}

void PKCS7_FreeRes(Pkcs7 *pkcs7)
{
    if (pkcs7 == NULL) {
        return;
    }
    FreeSignedDataDigestAlgs(pkcs7);
    FreeSignersInfo(pkcs7);
    FreeSignedDataCerts(pkcs7);
    FreeSignedDataCrl(pkcs7);
    UnLoadRootCert();
    return;
}
