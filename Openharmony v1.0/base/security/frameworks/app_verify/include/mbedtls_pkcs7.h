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

#ifndef MBEDTLS_PKCS7_H
#define MBEDTLS_PKCS7_H
#include <stdbool.h>
#include <mbedtls/asn1.h>
#include <mbedtls/x509.h>
#include <mbedtls/x509_crt.h>
#include <mbedtls/x509_crl.h>
#include <mbedtls/pem.h>
#include <mbedtls/oid.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 * if the pkcs7 format is pem, add this define in this header file
 * or in build env
 * #define PARSE_PEM_FORMAT_SIGNED_DATA 1
 */
#define MAX_SIGNER_NAME_LEN 512

typedef enum {
    PKCS7_SUCC = 0,
    PKCS7_PARSING_ERROR,
    PKCS7_INVALID_PARAM,
    PKCS7_INVALID_VALUE,
    PKCS7_INVALID_CONTENT_TYPE_OR_NO_CONTENT,
    PKCS7_CERTIFICATE_NOT_FOUND,
    PKCS7_INVALID_VERSION,
    PKCS7_INVALID_DIGEST_ALG,
    PKCS7_INVALID_SIGNING_ALG,
    PKCS7_MEMORY_EXHAUST,
    PKCS7_ROOT_CA_NOT_VALID,
    PKCS7_BUILD_CERT_PATH_FAIL,
    PKCS7_HAS_NO_AUTH_ATTR_IN_SIGNER,
    PKCS7_HAS_NO_SIGNER_INFO,
    PKCS7_HAS_NO_SIGNER_CRT,
    PKCS7_IS_REVOKED,
    PKCS7_VERIFY_FAIL,
} PKCS7_RetCode;

typedef struct {
    char issuer[MAX_SIGNER_NAME_LEN];
    char subject[MAX_SIGNER_NAME_LEN];
    int depth;
} SignerResovledInfo;

typedef struct {
    SignerResovledInfo *signers;
    int nrOfSigners;
} SignersResovedInfo;

/*
 * The structure bellow used the mbedtls open source structure which definition is kernel-like style,
 * We do not redefine it to Camel style
 *
 * the PKCS7 signer's cert path header
 * depth is the signer's cert path depth
 * crt is the certs list header, the lower ca cert is at front
 */
typedef struct {
    int depth;
    mbedtls_x509_crt *crt;
} SignerCertPath;

/*
 * PKCS7 signer info structure, as defined in PKCS7
 * rootCert is not defined in PKCS7, this is the signer's root cert preinstall in system
 * certPath is for cert chain verify
 * next is point to the next signer info, as PKCS7 definination, maybe there are multi signer
 */
typedef struct tagSignerInfo {
    int version;
    mbedtls_x509_buf serial;
    mbedtls_x509_name issuer;
    mbedtls_x509_crt *rootCert;
    mbedtls_x509_buf issuerRaw;
    mbedtls_x509_buf digestAlgId;
    mbedtls_x509_buf authAttr;
    mbedtls_x509_buf authAttrRaw;
    mbedtls_x509_buf digestEncAlgId;
    mbedtls_x509_buf signature;
    mbedtls_x509_buf unAuthAttr;
    SignerCertPath certPath;
    struct tagSignerInfo *next;
} SignerInfo;

/*
 * PKCS7 signed data content info
 */
typedef struct tagContent {
    mbedtls_asn1_buf oid;
    mbedtls_asn1_buf data;
} Content;

/*
 * PKCS7 signed data digest algorithm identifiers
 */
typedef struct tagDigestAlgId {
    mbedtls_asn1_buf algBuf;
    struct tagDigestAlgId *next;
} DigestAlgId;

/*
 * PKCS7 signed-data structure
 */
typedef struct {
    int version;
    DigestAlgId digestAlgIds;
    Content content;
    mbedtls_x509_crt *certs;
    mbedtls_x509_crl crl;
    SignerInfo signers;
} SignedData;

/*
 * PKCS7 signed data total structure header
 * contentTypeOid must be the pkcs7 signed-data oid 1.2.840.113549.1.7.2
 */
typedef struct {
    mbedtls_asn1_buf contentTypeOid;
    SignedData signedData;
#ifdef PARSE_PEM_FORMAT_SIGNED_DATA
    mbedtls_pem_context pem;
#endif
} Pkcs7;

/*******************************************************************************
 * Function    : PKCS7_ParseSignedData
 * Description : parse the pkcs7 signed data, store the resolved data to pkcs7
 * Input       : buf     - pkcs7 signed data
 *               bufLen  - pkcs7 signed data length
 * Output      : pkcs7   - resolved pkcs7 data, caller provide this arg, malloc
 *                         from heap memory or use stack memory, if malloced
 *                         from heap memory, caller must freed the memroy after
 *                         called PKCS7_FreeRes
 * Return      : 0 on success, others on fail
 * Note        : need to call PKCS7_FreeRes to free the resource when success
 *               parse and use, no need to call PKCS7_FreeRes when parse failed
 *******************************************************************************/
int PKCS7_ParseSignedData(const unsigned char *buf, size_t bufLen, Pkcs7 *pkcs7);

/*******************************************************************************
 * Function    : PKCS7_VerifyCertsChain
 * Description : Verify all signer's cert chain
 * Input       : pkcs7 -- the pkcs7 signed data header.
 * Return      : 0 on success, others on fail
 *******************************************************************************/
int PKCS7_VerifyCertsChain(const Pkcs7 *pkcs7);

/*******************************************************************************
 * Function    : PKCS7_FreeRes
 * Description : free the resource of resolved pkcs7 data
 * Input       : pkcs7   - resolved pkcs7 data
 * Return      : 0 on success, others on fail
 * Note        : need to call PKCS7_FreeRes to free the resource when success
 *               parse and use, no need to call PKCS7_FreeRes when parse failed
 *******************************************************************************/
void PKCS7_FreeRes(Pkcs7 *pkcs7);

/*******************************************************************************
 * Function    : PKCS7_CalcDigest
 * Description : is a callback defined by upper layer user, calculate the
 *               digest for final verify the signed data signature.
 * Input       : pkcs7   - pkcs7 signed data header
 *               signer  - pkcs7 signer info
 *               algType - digest algorithm type, defined in mbedtls, exp:
 *                         MBEDTLS_MD_SHA256/MBEDTLS_MD_SHA512
 * Output      : hash    - the calcuated digest hash
 *               hashLen - the length of calculated digest hash
 * Return      : 0 on success, others on fail
 *******************************************************************************/
typedef int (*PKCS7_CalcDigest)(const Pkcs7 *pkcs7, const SignerInfo *signer,
                                mbedtls_md_type_t algType, unsigned char *hash, size_t *hashLen);

/*******************************************************************************
 * Function    : PKCS7_GetContentData
 * Description : get the content data of PKCS#7 signed-data content
 * Input       : pkcs7   - pkcs7 signed data header
 * Output      : data    - pointer to the content data
 *                         user need not to free this var
 *               dataLen - the content data length
 * Return      : 0 on success, others on fail
 *******************************************************************************/
int PKCS7_GetContentData(const Pkcs7 *pkcs7, unsigned char **data, size_t *dataLen);

/*******************************************************************************
 * Function    : PKCS7_GetDigestInSignerAuthAttr
 * Description : get the digest which stored in signer's auth attribute.
 * Input       : signer  - pkcs7 signer info
 * Output      : dig     - pointer to the digest stored in signer's auth attribute
 *                         user need not to free this var
 *               digLen  - digest length
 * Return      : 0 on success, others on fail
 *******************************************************************************/
int PKCS7_GetDigestInSignerAuthAttr(const SignerInfo *signer, unsigned char **dig, size_t *digLen);

/*******************************************************************************
 * Function    : PKCS7_GetSignerAuthAttr
 * Description : get the signer's auth attribute content, which maybe signed by
 *               signer, so upper layer can call this to get to-be-signed data,
 *               then caculate digest of it for signature verification
 * Input       : signer  - pkcs7 signer info
 * Output      : data    - pointer to signer's auth attribute start location
 *                         user need not to free this var
 *               dataLen - signer auth attribute data length
 * Return      : 0 on success, others on fail
 *******************************************************************************/
int PKCS7_GetSignerAuthAttr(const SignerInfo *signer, unsigned char **data, size_t *dataLen);

/*******************************************************************************
 * Function    : PKCS7_VerifySignerSignature
 * Description : Verify all of signer's signature
 * Input       : pkcs7   - pkcs7 signed data header
 *               calcDigest - callback function for upper layer user to caculate
 *                            the digest of signature
 * Output      : NA
 * Return      : 0 on success, others on fail
 *******************************************************************************/
int PKCS7_VerifySignerSignature(const Pkcs7 *pkcs7, PKCS7_CalcDigest calcDigest);

/*******************************************************************************
 * Function    : PKCS7_GetAllSignersResolvedInfo
 * Description : Get all signer's associate info, now including subject/issuer/
 *               cert depth, used it for trustlist match.
 * Input       : pkcs7   - pkcs7 signed data header
 * Output      : the structure of associate signer's info
 * Return      : non-NULL on success, and user need to call
 *               PKCS7_FreeAllSignersResolvedInfo to free resource
 *******************************************************************************/
SignersResovedInfo *PKCS7_GetAllSignersResolvedInfo(const Pkcs7 *pkcs7);

/*******************************************************************************
 * Function    : PKCS7_FreeAllSignersResolvedInfo
 * Description : Free the signer associate info.
 * Input       : sri    - signer associate info
 * Output      : NA
 * Return      : void
 *******************************************************************************/
void PKCS7_FreeAllSignersResolvedInfo(SignersResovedInfo *sri);

/*******************************************************************************
 * Function    : PKCS7_EnableDebugMode
 * Description : Enable or disable debug mode, so it can install the app that
 *               signed by the test cert's private key.
 * Input       : mode    - true:enable, false:disable
 * Output      : NA
 * Return      : 0 on success, others on error
 *******************************************************************************/
int PKCS7_EnableDebugMode(bool mode);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // MBEDTLS_PKCS7_H
