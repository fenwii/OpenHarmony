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

#ifndef HKS_ERRNO_H
#define HKS_ERRNO_H

#include "hks_types.h"

/* MBEDTLS_SUCCESS */
#define HKS_SUCCESS                         ((int32_t)0)
/* MBEDTLS_ERROR_UNKNOWN_ERROR */
#define HKS_FAILURE                         ((int32_t)-132)
/* MBEDTLS_ERROR_NOT_PERMITTED */
#define HKS_ERROR_NOT_PERMITTED             ((int32_t)-133)
/* MBEDTLS_ERROR_NOT_SUPPORTED */
#define HKS_ERROR_NOT_SUPPORTED             ((int32_t)-134)
/* MBEDTLS_ERROR_INVALID_ARGUMENT */
#define HKS_ERROR_INVALID_ARGUMENT          ((int32_t)-135)
/* MBEDTLS_ERROR_INVALID_HANDLE */
#define HKS_ERROR_INVALID_HANDLE            ((int32_t)-136)
/* MBEDTLS_ERROR_BAD_STATE */
#define HKS_ERROR_BAD_STATE                 ((int32_t)-137)
/* MBEDTLS_ERROR_BUFFER_TOO_SMALL */
#define HKS_ERROR_BUFFER_TOO_SMALL          ((int32_t)-138)
/* MBEDTLS_ERROR_OCCUPIED_SLOT */
#define HKS_ERROR_OCCUPIED_SLOT             ((int32_t)-139)
/* MBEDTLS_ERROR_EMPTY_SLOT */
#define HKS_ERROR_EMPTY_SLOT                ((int32_t)-140)
/* MBEDTLS_ERROR_INSUFFICIENT_MEMORY */
#define HKS_ERROR_INSUFFICIENT_MEMORY       ((int32_t)-141)
/* MBEDTLS_ERROR_INSUFFICIENT_STORAGE */
#define HKS_ERROR_INSUFFICIENT_STORAGE      ((int32_t)-142)
/* MBEDTLS_ERROR_INSUFFICIENT_CAPACITY */
#define HKS_ERROR_INSUFFICIENT_CAPACITY     ((int32_t)-143)
/* MBEDTLS_ERROR_COMMUNICATION_FAILURE */
#define HKS_ERROR_COMMUNICATION_FAILURE     ((int32_t)-145)
/* MBEDTLS_ERROR_STORAGE_FAILURE */
#define HKS_ERROR_STORAGE_FAILURE           ((int32_t)-146)
/* MBEDTLS_ERROR_HARDWARE_FAILURE */
#define HKS_ERROR_HARDWARE_FAILURE          ((int32_t)-147)
/* MBEDTLS_ERROR_INSUFFICIENT_ENTROPY */
#define HKS_ERROR_INSUFFICIENT_ENTROPY      ((int32_t)-148)
/* MBEDTLS_ERROR_INVALID_SIGNATURE */
#define HKS_ERROR_INVALID_SIGNATURE         ((int32_t)-149)
/* MBEDTLS_ERROR_INVALID_PADDING */
#define HKS_ERROR_INVALID_PADDING           ((int32_t)-150)
/* MBEDTLS_ERROR_TAMPERING_DETECTED */
#define HKS_ERROR_TAMPERING_DETECTED        ((int32_t)-151)
/* MBEDTLS_ERROR_DATA_CORRUPT */
#define HKS_ERROR_DATA_CORRUPT              ((int32_t)-152)
#define HKS_ERROR_MBEDTLS_RANGE_MIN         ((int32_t)-153)

/*
 * Error code for hks
 * Add new error code before HKS_ERROR_RANGE_MIN
 * Modify the value of HKS_ERROR_RANGE_MIN when adding an error code
 * The value of HKS_ERROR_RANGE_MIN = The value of new error code - 1
 * Such as add HKS_ERROR_XXX(-1015),must modify HKS_ERROR_RANGE_MIN to be -1016
 */
#define HKS_STATUS_OK                       ((int32_t)0)
#define HKS_ERROR_NULL_POINTER              ((int32_t)-1000)
#define HKS_ERROR_DUPLICATED_REG            ((int32_t)-1001)
#define HKS_ERROR_FILE_SIZE_FAIL            ((int32_t)-1002)
#define HKS_ERROR_READ_FILE_FAIL            ((int32_t)-1003)
#define HKS_ERROR_INVALID_PUBLIC_KEY        ((int32_t)-1004)
#define HKS_ERROR_INVALID_PRIVATE_KEY       ((int32_t)-1005)
#define HKS_ERROR_INVALID_KEY_INFO          ((int32_t)-1006)
#define HKS_ERROR_BUF_TOO_SMALL             ((int32_t)-1007)
#define HKS_ERROR_UNKNOWN_ERROR             ((int32_t)-1008)
#define HKS_ERROR_ASSERT_FAIL               ((int32_t)-1009)
#define HKS_ERROR_KEY_NOT_EXIST             ((int32_t)-1010)
#define HKS_ERROR_HASH_NOT_EQUAL            ((int32_t)-1011)
#define HKS_ERROR_MALLOC_FAIL               ((int32_t)-1012)
#define HKS_ERROR_WRITE_FILE_FAIL           ((int32_t)-1013)
#define HKS_ERROR_REMOVE_FILE_FAIL          ((int32_t)-1014)
#define HKS_ERROR_INVALID_KEY_FILE          ((int32_t)-1015)
#define HKS_ERROR_IPC_INITIAL_FAIL          ((int32_t)-1016)
#define HKS_ERROR_GET_KEY_PARAM_FAIL        ((int32_t)-1017)
#define HKS_ERROR_AES_ENCRYPT_FAIL          ((int32_t)-1018)
#define HKS_ERROR_AES_DECRYPT_FAIL          ((int32_t)-1019)
#define HKS_ERROR_SIGN_FAIL                 ((int32_t)-1020)
#define HKS_ERROR_VERIFY_FAIL               ((int32_t)-1021)
#define HKS_ERROR_EXPORT_FAIL               ((int32_t)-1022)
#define HKS_ERROR_IMPORT_FAIL               ((int32_t)-1023)
#define HKS_ERROR_WRAP_FAIL                 ((int32_t)-1024)
#define HKS_ERROR_UNWRAP_FAIL               ((int32_t)-1025)
#define HKS_ERROR_DELETE_FAIL               ((int32_t)-1026)
#define HKS_ERROR_GENERATE_ASYM_FAIL        ((int32_t)-1027)
#define HKS_ERROR_GENERATE_SYM_FAIL         ((int32_t)-1028)
#define HKS_ERROR_KEY_ATTEST_FAIL           ((int32_t)-1029)
#define HKS_ERROR_CERT_CHAIN_FAIL           ((int32_t)-1030)
#define HKS_ERROR_GET_KEY_LIST_FAIL         ((int32_t)-1031)
#define HKS_ERROR_RANGE_MIN                 ((int32_t)-1032)
#define HKS_ERROR_CERT_NOT_EXIST            ((int32_t)-1033)
#define HKS_ERROR_INVALID_PKI_FILE          ((int32_t)-1034)
#define HKS_ERROR_CERT_VERIFY_FAIL          ((int32_t)-1035)
#define HKS_ERROR_WB_DECRYPT_FAIL           ((int32_t)-1036)
#define HKS_ERROR_EFUSE_WRITE_FAIL          ((int32_t)-1037)
#define HKS_ERROR_EFUSE_READ_FAIL           ((int32_t)-1038)
#define HKS_ERROR_EFUSE_LOCK_FAIL           ((int32_t)-1039)
#define HKS_ERROR_INTERNAL_UNKOWN           ((int32_t)-9999)
#define HKS_ERROR_IPC_RANGE_MIN             ((int32_t)65536)
#define HKS_ERROR_IPC_RANGE_MAX             ((int32_t)65556)
#define HKS_ERROR_PERMISSION_DENIED         ((int32_t)0xFF07)

#endif /* HKS_ERRNO_H */
