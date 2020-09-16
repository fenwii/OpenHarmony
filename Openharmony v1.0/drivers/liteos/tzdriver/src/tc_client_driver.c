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

#include "tc_client_driver.h"
#include "agent.h"
#include "gp_ops.h"
#include "mailbox_mempool.h"
#include "mem.h"
#include "smc.h"
#include "tc_client_sub_driver.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"
#include "teek_client_type.h"
#include "tz_spi_notify.h"
#include "tzdebug.h"
#include "tzdriver_compat.h"

struct workqueue_struct *g_tzdriverWq = NULL;

#define TEEC_PARAM_TYPES(param0_type, param1_type, param2_type, param3_type) \
    (((param3_type) << 12) | ((param2_type) << 8) | \
    ((param1_type) << 4) | (param0_type))

#define TEEC_PARAM_TYPE_GET(paramTypes, index) \
    (((paramTypes) >> ((index) << 2)) & 0x0F)

// record device_file count
static unsigned int g_deviceFileCnt = 1;
static DEFINE_MUTEX(g_deviceFileCntLock);

static LosTaskCB *g_teecdTask = NULL;
// dev node list and itself has mutex to avoid race
struct TcNsDevList g_tcNsDevList;

// record all service node and need mutex to avoid race
struct list_head g_serviceList;
DEFINE_MUTEX(g_serviceListLock);

#define TEECD_CERT_INDEX 0
// teecd must set 0 in g_arrayCertNativeVendor
static const unsigned char g_arrayCertNativeVendor[][SHA256_DIGEST_LENGTH] = {
    /* /vendor/bin/teecd0 */
    {0x99, 0xa2, 0xf1, 0xb3, 0xa3, 0x5f, 0x3f, 0x11, 0x8b, 0x33, 0xc1, 0x7e, 0xb9, 0xe8, 0x53, 0xbe,
     0x88, 0xf0, 0xc4, 0x6a, 0xf2, 0x7e, 0x72, 0x6e, 0x91, 0xb7, 0x59, 0xf0, 0x73, 0x9c, 0x93, 0xa5},

    /* /vendor/bin/teec_hello0 */
    {0x9a, 0xab, 0xac, 0x19, 0xaa, 0xb2, 0xeb, 0xf4, 0x99, 0x11, 0x94, 0x15, 0xee, 0xb0, 0x03, 0x09,
     0xd6, 0xe8, 0xfe, 0xe9, 0x32, 0x37, 0x48, 0xfd, 0x2b, 0xf2, 0x2c, 0x78, 0x74, 0xd6, 0xc3, 0x9c},

    /* /vendor/bin/tee_test_mem0 */
    {0x44, 0x7c, 0x8f, 0xc2, 0xa1, 0x1e, 0xfd, 0xab, 0x21, 0x63, 0x0e, 0xf8, 0x7d, 0x0b, 0xce, 0x06,
     0x05, 0x7f, 0x4a, 0xa8, 0x14, 0x17, 0x0f, 0xef, 0xa6, 0xa5, 0x77, 0x6c, 0xfe, 0xca, 0x4a, 0x8e},

    /* /vendor/bin/tee_test_sess0 */
    {0xa0, 0xe4, 0x1b, 0x61, 0x8c, 0xd5, 0xf4, 0x4c, 0xec, 0x29, 0x03, 0xcd, 0x2f, 0xce, 0x28, 0xa7,
     0x67, 0xba, 0x3a, 0x10, 0x20, 0xd7, 0x95, 0x2b, 0x41, 0xaf, 0x47, 0x7c, 0x3d, 0xed, 0xce, 0xa4},

    /* /vendor/bin/tee_test_invoke0 */
    {0xb5, 0x4e, 0x9d, 0x7b, 0x42, 0x10, 0x63, 0xcc, 0x4b, 0x7b, 0x16, 0x7d, 0xf6, 0xfe, 0xa8, 0x8e,
     0x6f, 0xca, 0x1b, 0xf1, 0x6a, 0xff, 0xed, 0xfd, 0xee, 0x09, 0xed, 0xbb, 0x18, 0x13, 0x75, 0x02},

    /* /vendor/bin/tee_test_ut0 */
    {0x45, 0x71, 0xd9, 0x4b, 0x5b, 0xc7, 0xc1, 0x29, 0x2f, 0x9f, 0x46, 0xf2, 0x92, 0xef, 0xd5, 0x44,
     0xda, 0xb4, 0x51, 0xfb, 0x75, 0xa4, 0xc7, 0x4f, 0x8d, 0x34, 0xca, 0x5e, 0x27, 0xa6, 0x08, 0x8c},

    /* /vendor/bin/tee_test_ca0 */
    {0xe9, 0x16, 0xde, 0x3f, 0x62, 0x27, 0x5b, 0x12, 0x04, 0x39, 0x9c, 0xc9, 0xf0, 0x34, 0x1f, 0xee,
     0xf0, 0x1a, 0x66, 0x31, 0xa9, 0xbf, 0x7d, 0x14, 0x30, 0x3d, 0xae, 0xe1, 0xb3, 0x07, 0xb9, 0x54},

    /* /vendor/bin/tee_test_agent0 */
    {0x20, 0x6f, 0x1c, 0x54, 0xd5, 0x5f, 0xa8, 0xa8, 0x88, 0x56, 0xc4, 0x0c, 0xc3, 0xf9, 0x9c, 0x9a,
     0xc3, 0x40, 0x86, 0x13, 0x61, 0xb0, 0xcf, 0x69, 0xdd, 0xb8, 0x6c, 0x1e, 0x53, 0xb4, 0x77, 0x55},

    /* /vendor/bin/tee_test_client_api0 */
    {0xae, 0xe9, 0x12, 0x90, 0x23, 0x9b, 0x99, 0x01, 0x99, 0x1d, 0xa5, 0x22, 0xe0, 0x26, 0x06, 0x12,
     0x2b, 0xad, 0x5e, 0xaf, 0x34, 0xbf, 0x1a, 0x16, 0x3e, 0x75, 0x97, 0x65, 0xe6, 0x39, 0x9d, 0xf3},
};

typedef struct {
    TcNsDevFile *devFile;
    char *fileBuffer;
    unsigned int fileSize;
} LoadImageParams;

mutex_t *GetServiceListLock(void)
{
    return &g_serviceListLock;
}

struct TcNsDevList *GetTcNsDevList(void)
{
    return &g_tcNsDevList;
}

struct list_head *GetServiceList(void)
{
    return &g_serviceList;
}

static int GetMemSpace(char **caCert, char **tpath)
{
    *tpath = malloc(MAX_PATH_SIZE);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*tpath))) {
        tloge("tpath malloc fail\n");
        return -EPERM;
    }
    *caCert = malloc(BUF_MAX_SIZE);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*caCert))) {
        tloge("caCert malloc fail\n");
        free(*tpath);
        *tpath = NULL;
        return -EPERM;
    }
    return 0;
}

static int CheckPathAndAccess(LosTaskCB *caTask,
    char *caCert, unsigned long messageSize,
    unsigned char *digest, unsigned int digLen)
{
    int ret;
    unsigned long index;

    if (digLen != SHA256_DIGEST_LENGTH) {
        tlogd("check process path digest len error\n");
        return CHECK_PATH_HASH_FAIL;
    }

    ret = CalcProcessPathHash((unsigned char *)caCert, messageSize, digest, digLen);
    if (ret != 0) {
        return ret;
    }

    for (index = 0; index < (sizeof(g_arrayCertNativeVendor) / SHA256_DIGEST_LENGTH); index++) {
        ret = memcmp(digest, g_arrayCertNativeVendor[index], digLen);
        if (ret == 0) {
            if (g_teecdTask == NULL && index == TEECD_CERT_INDEX) {
                g_teecdTask = GetProcessGroupLeader(caTask);
            }
            return 0;
        }
    }
    return CHECK_PATH_HASH_FAIL;
}

static int CheckProcessAccess(LosTaskCB *caTask)
{
    char *caCert = NULL;
    char *path = NULL;
    char *tpath = NULL;
    unsigned char digest[SHA256_DIGEST_LENTH] = {0};
    int messageSize;
    int ret;

    if (caTask == NULL) {
        tloge("task_struct is NULL\n");
        return -EPERM;
    }

    if (IsKernelThread(caTask)) {
        tlogd("kernel thread need not check\n");
        ret = ENTER_BYPASS_CHANNEL;
        return ret;
    }

    ret = GetMemSpace(&caCert, &tpath);
    if (ret != 0) {
        return ret;
    }

    path = GetProcessPath(caTask, tpath, MAX_PATH_SIZE);
    if (!IS_ERR_OR_NULL(path)) {
        errno_t sret;

        sret = memset_s(caCert, BUF_MAX_SIZE, 0x00, BUF_MAX_SIZE);
        if (sret != EOK) {
            tloge("memset error sret is %d\n", sret);
            free(tpath);
            free(caCert);
            return -EPERM;
        }

        messageSize = PackCaCert(caCert, path, caTask, GetTaskUid(caTask));
        if (messageSize > 0) {
            ret = CheckPathAndAccess(caTask, caCert,
                (unsigned long)messageSize, digest,
                (unsigned int)SHA256_DIGEST_LENTH);
        } else {
            ret = -EPERM;
        }
    } else {
        ret = -EPERM;
    }
    free(tpath);
    free(caCert);
    return ret;
}

/* Calculate the SHA256 file digest */
static int TeeCalcTaskHash(unsigned char *digest,
    uint32_t digLen, LosTaskCB *curStruct)
{
    TeeSha256Context ctx;
    LosVmSpace *space = OS_PCB_FROM_PID(curStruct->processID)->vmSpace;
    if (space == NULL) {
        return -EFAULT;
    }

    TeeSha256Init(&ctx);
    /* search the region list */
    if (space->codeStart != 0 && space->codeEnd > space->codeStart) {
        TeeSha256Update(&ctx, (void *)space->codeStart, space->codeEnd - space->codeStart);
    } else {
        return -EFAULT;
    }
    TeeSha256Final(&ctx, digest);
    return 0;
}

#define LIBTEEC_CODE_PAGE_SIZE 8
#define DEFAULT_TEXT_OFF 0
#define LIBTEEC_NAME_MAX_LEN 50

#define LIBTEEC_SO "/vendor/lib/libteec_vendor.so"

/* Calculate the SHA256 library digest */
static int TeeCalcTaskSoHash(unsigned char *digest, uint32_t digLen,
    LosTaskCB *curStruct, int soIndex)
{
    TeeSha256Context ctx;
    int findFlag = 0;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeNext = NULL;
    LosVmSpace *space = OS_PCB_FROM_PID(curStruct->processID)->vmSpace;
    if (space == NULL) {
        return -EFAULT;
    }

    TeeSha256Init(&ctx);
    /* search the region list */
    (VOID)LOS_MuxAcquire(&space->regionMux);
    RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeNext)
        LosVmMapRegion *region = (LosVmMapRegion *)pstRbNode;
        if (!LOS_IsRegionFileValid(region)) {
            continue;
        }
        struct file *fileRegion = region->unTypeData.rf.file;
        if (fileRegion != NULL && !strncmp(fileRegion->f_path, LIBTEEC_SO, strlen(LIBTEEC_SO))) {
            TeeSha256Update(&ctx, (void *)region->range.base, region->range.size);
            findFlag = 1;
            break;
        }
    RB_SCAN_SAFE_END(&space->regionRbTree, pstRbNode, pstRbNodeNext)
    (VOID)LOS_MuxRelease(&space->regionMux);

    if (findFlag == 0) {
        return -EFAULT;
    }
    TeeSha256Final(&ctx, digest);
    return 0;
}

/* Modify the client context so params id 2 and 3 contain temp pointers to the
 * public key and package name for the open session. This is used for the
 * TEEC_LOGIN_IDENTIFY open session method
 */
static int SetLoginInformation(TcNsDevFile *devFile,
    TcNsClientContext *context)
{
    /* The daemon has failed to get login information or not supplied */
    if (devFile->pkgNameLen == 0) {
        return -1;
    }
    /* The 3rd parameter buffer points to the pkg name buffer in the
     * device file pointer
     * get package name len and package name
     */
    context->params[TEE_PARAM_FOUR].memref.sizeAddr =
        (uintptr_t)&devFile->pkgNameLen;
    context->params[TEE_PARAM_FOUR].memref.buffer =
        (uintptr_t)devFile->PkgName;
    /* Set public key len and public key */
    if (devFile->pubKeyLen != 0) {
        context->params[TEE_PARAM_THREE].memref.sizeAddr =
            (uintptr_t)&devFile->pubKeyLen;
        context->params[TEE_PARAM_THREE].memref.buffer =
            (uintptr_t)devFile->pubKey;
    } else {
        /* If get public key failed, then get uid in kernel */
        uint32_t caUid = TcNsGetUid();
        if (caUid == (uint32_t)(-1)) {
            tloge("Failed to get uid of the task\n");
            goto error;
        }

        devFile->pubKeyLen = sizeof(caUid);
        context->params[TEE_PARAM_THREE].memref.sizeAddr =
            (uintptr_t)&devFile->pubKeyLen;
        if (memcpy_s(devFile->pubKey, MAX_PUBKEY_LEN, &caUid,
            devFile->pubKeyLen)) {
            tloge("Failed to copy pubkey, pubKeyLen=%u\n",
                  devFile->pubKeyLen);
            goto error;
        }
        context->params[TEE_PARAM_THREE].memref.buffer =
            (uint64_t)(uintptr_t)devFile->pubKey;
    }
    /* Now we mark the 2 parameters as input temp buffers */
    context->paramTypes = TEEC_PARAM_TYPES(
        TEEC_PARAM_TYPE_GET(context->paramTypes, TEE_PARAM_ONE),
        TEEC_PARAM_TYPE_GET(context->paramTypes, TEE_PARAM_TWO),
        TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    return 0;
error:
    return -1;
}

static int CheckProcessAndAllocParams(TcNsDevFile *devFile,
    uint8_t **certBuffer, unsigned int *certBufferSize)
{
    int ret;

#ifdef SECURITY_AUTH_ENHANCE
    ret = CheckProcessAccess(OsCurrTaskGet());
    if (ret) {
        tloge(KERN_ERR "tc client login: teecd verification failed ret 0x%x!\n", ret);
        return -EPERM;
    }
#endif
    mutex_lock(&devFile->LoginSetupLock);
    if (devFile->loginSetup) {
        tloge("Login information cannot be set twice!\n");
        mutex_unlock(&devFile->LoginSetupLock);
        return -EINVAL;
    }
    devFile->loginSetup = true;
    mutex_unlock(&devFile->LoginSetupLock);

    unsigned int bufSize = (unsigned int)(MAX_PACKAGE_NAME_LEN + MAX_PUBKEY_LEN +
        sizeof(devFile->pkgNameLen) + sizeof(devFile->pubKeyLen));
    *certBuffer = malloc(bufSize);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*certBuffer))) {
        tloge("Failed to allocate login buffer!");
        return -EFAULT;
    }
    *certBufferSize = bufSize;

    return 0;
}

static int TcNsGetTeeVersion(const TcNsDevFile *devFile, void *argp)
{
    unsigned int version;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    int smcRet;
    struct MbCmdPack *mbPack = NULL;

    if (argp == NULL || devFile == NULL) {
        tloge("error input parameter\n");
        return -1;
    }
    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc mb pack failed\n");
        return -ENOMEM;
    }

    mbPack->operation.paramTypes = TEEC_VALUE_OUTPUT;
    smcCmd.globalCmd = true;
    smcCmd.cmdId = GLOBAL_CMD_ID_GET_TEE_VERSION;
    smcCmd.devFileId = devFile->devFileId;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    smcRet = TcNsSmc(&smcCmd);
    if (smcRet != 0) {
        tloge("smc_call returns error ret 0x%x\n", smcRet);
    }

    version = mbPack->operation.params[0].value.a;
    if (copy_to_user(argp, &version, sizeof(unsigned int))) {
        if (smcRet != 0) {
            smcRet = -EFAULT;
        }
    }
    MailboxFree(mbPack);
    return smcRet;
}

#define MAX_BUF_LEN 4096

static int TcNsClientLogWithoutCert(TcNsDevFile *devFile)
{
    int ret;
    uint8_t *certBuffer = NULL;
    uint8_t *tempCertBuffer = NULL;
    errno_t sret;
    unsigned int certBufferSize = 0;
    char *path = NULL;

    ret = CheckProcessAndAllocParams(devFile, &certBuffer,
        &certBufferSize);
    if (ret != 0) {
        return ret;
    }
    tempCertBuffer = certBuffer;

    path = GetProcessPath(OsCurrTaskGet(), (char *)certBuffer, MAX_PACKAGE_NAME_LEN);
    if (path == NULL) {
        goto error;
    }
    devFile->pkgNameLen = strlen(path);

    sret = strncpy_s((char *)devFile->PkgName, MAX_PACKAGE_NAME_LEN, (char *)certBuffer,
        devFile->pkgNameLen);
    if (sret != EOK) {
        ret = -ENOMEM;
        goto error;
    }
    int uid = GetTaskUid(OsCurrTaskGet());
    devFile->pubKeyLen = sizeof(uid);
    if (memcpy_s((char *)devFile->pubKey, MAX_PUBKEY_LEN, (char *)&uid,
        devFile->pubKeyLen)) {
        tloge("Failed to copy cert, pubKeyLen=%u\n",
            devFile->pubKeyLen);
        ret = -EINVAL;
        goto error;
    }
error:
    free(tempCertBuffer);
    return ret;
}

static int TcNsClientLogWithCert(TcNsDevFile *devFile, const void *buffer)
{
    int ret;
    uint8_t *certBuffer = NULL;
    uint8_t *tempCertBuffer = NULL;
    errno_t sret;
    unsigned int certBufferSize = 0;

    // apk ca login
    ret = CheckProcessAndAllocParams(devFile, &certBuffer,
        &certBufferSize);
    if (ret != 0) {
        return ret;
    }

    tempCertBuffer = certBuffer;
    /* GET PACKAGE NAME AND APP CERTIFICATE:
     * The proc_info format is as follows:
     * package_name_len(4 bytes) || package_name ||
     * apk_cert_len(4 bytes) || apk_cert.
     * or package_name_len(4 bytes) || package_name
     * || exe_uid_len(4 bytes) || exe_uid.
     * The apk certificate format is as follows:
     * modulus_size(4bytes) ||modulus buffer
     * || exponent size || exponent buffer
     */
    if (certBufferSize > MAX_BUF_LEN) {
        tloge("cert buffer size is invalid!\n");
        ret = -EINVAL;
        goto error;
    }

    if (copy_from_user(certBuffer, buffer, certBufferSize)) {
        tloge("Failed to get user login info!\n");
        ret = -EINVAL;
        goto error;
    }
    /* get package name len */
    ret = GetPackNameLen(devFile, certBuffer, certBufferSize);
    if (ret != 0) {
        goto error;
    }
    certBuffer += sizeof(devFile->pkgNameLen);

    /* get package name */
    sret = strncpy_s((char *)devFile->PkgName, MAX_PACKAGE_NAME_LEN, (char *)certBuffer, devFile->pkgNameLen);
    if (sret != EOK) {
        ret = -ENOMEM;
        goto error;
    }
    certBuffer += devFile->pkgNameLen;

    /* get public key len */
    ret = GetPublicKeyLen(devFile, certBuffer, certBufferSize);
    if (ret != 0) {
        goto error;
    }

    /* get public key */
    if (devFile->pubKeyLen != 0) {
        certBuffer += sizeof(devFile->pubKeyLen);
        if (memcpy_s((char *)devFile->pubKey, MAX_PUBKEY_LEN, (char *)certBuffer, devFile->pubKeyLen)) {
            tloge("Failed to copy cert, pubKeyLen=%u\n", devFile->pubKeyLen);
            ret = -EINVAL;
            goto error;
        }
        certBuffer += devFile->pubKeyLen;
    }
    ret = 0;
error:
    free(tempCertBuffer);
    return ret;
}

static int TcNsClientLoginFunc(TcNsDevFile *devFile,
    const void *buffer)
{
    if (buffer == NULL) {
        return TcNsClientLogWithoutCert(devFile);
    } else {
        return TcNsClientLogWithCert(devFile, buffer);
    }
}

static int AllocForLoadImage(unsigned int *mbLoadSize,
    unsigned int fileSize, char **mbLoadMem,
    struct MbCmdPack **mbPack, TeecUuid **uuidReturn)
{
    /* we will try any possible to alloc mailbox mem to load TA */
    for (; *mbLoadSize > 0; *mbLoadSize >>= 1) {
        *mbLoadMem = MailboxAlloc(*mbLoadSize, 0);
        if (*mbLoadMem != NULL) {
            break;
        }
        tlogw("alloc mem(size=%u) for TA load mem fail, will retry\n", *mbLoadSize);
    }
    if (*mbLoadMem == NULL) {
        tloge("alloc TA load mem failed\n");
        return -ENOMEM;
    }
    *mbPack = MailboxAllocCmdPack();
    if (*mbPack == NULL) {
        MailboxFree(*mbLoadMem);
        *mbLoadMem = NULL;
        tloge("alloc mb pack failed\n");
        return -ENOMEM;
    }
    *uuidReturn = MailboxAlloc(sizeof(TeecUuid), 0);
    if (*uuidReturn == NULL) {
        MailboxFree(*mbLoadMem);
        *mbLoadMem = NULL;
        MailboxFree(*mbPack);
        *mbPack = NULL;
        tloge("alloc uuid failed\n");
        return -ENOMEM;
    }
    return 0;
}

static void PackDataForSmcCmd(uint32_t loadSize,
    const char *mbLoadMem, struct MbCmdPack *mbPack,
    TeecUuid *uuidReturn, TcNsSmcCmd *smcCmd)
{
    mbPack->operation.params[TEE_PARAM_ONE].memref.buffer =
        LOS_PaddrQuery((void *)mbLoadMem);
    mbPack->operation.bufferHaddr[TEE_PARAM_ONE] = 0;
    mbPack->operation.params[TEE_PARAM_ONE].memref.size = loadSize + sizeof(int);
    mbPack->operation.params[TEE_PARAM_THREE].memref.buffer =
        LOS_PaddrQuery((void *)uuidReturn);
    mbPack->operation.bufferHaddr[TEE_PARAM_THREE] = 0;
    mbPack->operation.params[TEE_PARAM_THREE].memref.size = sizeof(*uuidReturn);
    mbPack->operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,
        TEEC_VALUE_OUTPUT, TEEC_MEMREF_TEMP_OUTPUT, TEEC_VALUE_INPUT);
    /* load image smc command */
    smcCmd->globalCmd = true;
    smcCmd->cmdId = GLOBAL_CMD_ID_LOAD_SECURE_APP;
    smcCmd->contextId = 0;
    smcCmd->operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd->operationHphys = 0;
}

struct MbLoad {
    unsigned int mbLoadSize;
    char *mbLoadMem;
};

static int LoadImageByFrame(const LoadImageParams *paramsIn,
    struct MbLoad *mb, struct MbCmdPack *mbPack, TeecUuid *uuidReturn,
    unsigned int loadTimes)
{
    char *p = mb->mbLoadMem;
    uint32_t loadSize;
    int loadFlag = 1; /* 0:it's last block, 1:not last block */
    uint32_t loadedSize = 0;
    unsigned int index;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    int smcRet;

    for (index = 0; index < loadTimes; index++) {
        if (index == (loadTimes - 1)) {
            loadFlag = 0;
            loadSize = paramsIn->fileSize - loadedSize;
        } else {
            loadSize = mb->mbLoadSize - sizeof(loadFlag);
        }
        *(int *)p = loadFlag;
        if (loadSize > mb->mbLoadSize - sizeof(loadFlag)) {
            tloge("invalid load size %u/%u\n", loadSize,
                mb->mbLoadSize);
            return  -1;
        }
        if (copy_from_user(mb->mbLoadMem + sizeof(loadFlag),
            (void __user *)(paramsIn->fileBuffer +
            loadedSize), loadSize)) {
            tloge("file buf get fail\n");
            return  -1;
        }
        PackDataForSmcCmd(loadSize, mb->mbLoadMem, mbPack,
            uuidReturn, &smcCmd);
        mbPack->operation.params[TEE_PARAM_FOUR].value.a = index;
        smcCmd.devFileId = paramsIn->devFile->devFileId;
        smcRet = TcNsSmc(&smcCmd);
        tlogd("smc cmd ret %d\n", smcRet);
        tlogd("configid=%u, ret=%d, loadFlag=%d, index=%u\n",
            mbPack->operation.params[1].value.a, smcRet,
            loadFlag, index);

        if (smcRet != 0) {
            tloge("smc_call returns error ret 0x%x\n", smcRet);
            return -1;
        }

        loadedSize += loadSize;
    }
    return 0;
}

int TcNsLoadImage(TcNsDevFile *devFile, char *fileBuffer,
    unsigned int fileSize)
{
    int ret;
    struct MbCmdPack *mbPack = NULL;
    unsigned int mbLoadSize;
    char *mbLoadMem = NULL;
    TeecUuid *uuidReturn = NULL;
    unsigned int loadTimes;
    LoadImageParams paramsIn = {devFile, fileBuffer, fileSize};
    bool checkValue = false;

    checkValue = (devFile == NULL || fileBuffer == NULL);
    if (checkValue) {
        tloge("devFile or fileBuffer is NULL!\n");
        return -EINVAL;
    }
    if (!IsValidTaSize(fileBuffer, fileSize)) {
        return -EINVAL;
    }

    mbLoadSize = (fileSize > (SZ_1M - sizeof(int))) ? SZ_1M : ALIGN(fileSize, SZ_4K);

    ret = AllocForLoadImage(&mbLoadSize, fileSize, &mbLoadMem,
        &mbPack, &uuidReturn);
    if (ret != 0) {
        return ret;
    }

    if (mbLoadSize <= sizeof(int)) {
        tloge("mbLoadSize is too small!\n");
        ret = -ENOMEM;
        goto FREE_MEM;
    }

    loadTimes = fileSize / (mbLoadSize - sizeof(int));
    if (fileSize % (mbLoadSize - sizeof(int))) {
        loadTimes += 1;
    }
    struct MbLoad mb;
    mb.mbLoadMem = mbLoadMem;
    mb.mbLoadSize = mbLoadSize;
    ret = LoadImageByFrame(&paramsIn, &mb, mbPack, uuidReturn, loadTimes);
FREE_MEM:
    MailboxFree(mbLoadMem);
    MailboxFree(mbPack);
    MailboxFree(uuidReturn);
    return ret;
}

static int CheckTaskState(LosTaskCB **halStruct,
    const TcNsClientContext *context)
{
    bool checkValue = false;

    checkValue = (context->callingPid && !IsKernelThread(OsCurrTaskGet()));
    if (checkValue == true) {
        tloge("non hal service pass non-zero callingpid , reject please!!!\n");
        return -EFAULT;
    }
    return 0;
}

static int CalcTaskHash(uint8_t kernelApi,
    TcNsSession *session, TcNsService *service,
    LosTaskCB *curStruct)
{
    int rc, i;
    int soFound = 0;
    if (kernelApi == TEE_REQ_FROM_USER_MODE) {
        for (i = 0; soFound < NUM_OF_SO && i < KIND_OF_SO; i++) {
            rc = TeeCalcTaskSoHash(session->authHashBuf + MAX_SHA_256_SZ * soFound,
                (uint32_t)SHA256_DIGEST_LENTH, curStruct, i);
            if (rc == 0) {
                soFound++;
            }
        }
        if (soFound != NUM_OF_SO) {
            tlogd("so library found: %d\n", soFound);
        }
    } else {
        tlogd("request from kernel\n");
    }

#ifdef CONFIG_ASAN_DEBUG
    tloge("so auth disabled for ASAN debug\n");
    uint32_t soHashLen = MAX_SHA_256_SZ * NUM_OF_SO;
    errno_t sret = memset_s(session->authHashBuf, soHashLen, 0, soHashLen);
    if (sret != EOK) {
        tloge("memset so hash failed\n");
        return -EFAULT;
    }
#endif
    rc = TeeCalcTaskHash(session->authHashBuf + MAX_SHA_256_SZ * NUM_OF_SO,
        (uint32_t)SHA256_DIGEST_LENTH, curStruct);
    if (rc != 0) {
        tloge("tee calc ca hash failed\n");
        return -EFAULT;
    }
    return 0;
}

static int CheckLoginMethod(TcNsDevFile *devFile,
    TcNsClientContext *context, uint8_t *flags)
{
    bool checkValue = false;
    int ret;

    if (devFile == NULL || context == NULL || flags == NULL) {
        return -EFAULT;
    }
    if (context->login.method == TEEC_LOGIN_IDENTIFY) {
        tlogd("login method is IDENTIFY\n");
        /* Check if params 0 and 1 are valid */
        checkValue = devFile->kernelApi == TEE_REQ_FROM_USER_MODE &&
            (TcUserParamValid(context, (unsigned int)TEE_PARAM_ONE) ||
            TcUserParamValid(context, (unsigned int)TEE_PARAM_TWO));
        if (checkValue == true) {
            return -EFAULT;
        }
        ret = SetLoginInformation(devFile, context);
        if (ret != 0) {
            tloge("SetLoginInformation failed ret =%d\n", ret);
            return ret;
        }
        *flags |= TC_CALL_LOGIN;
    } else {
        tlogd("login method is not supported\n");
        return -EINVAL;
    }
    return 0;
}

static TcNsService *FindService(TcNsDevFile *devFile,
    const TcNsClientContext *context)
{
    int ret;
    TcNsService *service = NULL;
    bool isNewService = false;
    bool isFull = false;

    mutex_lock(&devFile->serviceLock);
    service = TcRefServiceInDev(devFile, context->uuid,
        UUID_LEN, &isFull);
    /* if service has been opened in this dev or ref cnt is full */
    if (service != NULL || isFull == true) {
        /* If service has been reference by this dev, TcFindServiceInDev
         * will increase a ref count to declaim there's how many callers to
         * this service from the devFile, instead of increase service->usage.
         * While close session, dev->serviceRef[i] will decrease and till
         * it get to 0 PutServiceStruct will be called.
         */
        mutex_unlock(&devFile->serviceLock);
        return service;
    }
    mutex_lock(&g_serviceListLock);
    service = TcFindServiceFromAll(context->uuid, (uint32_t)UUID_LEN);
    /* if service has been opened in other dev */
    if (service != NULL) {
        GetServiceStruct(service);
        mutex_unlock(&g_serviceListLock);
        goto ADD_SERVICE;
    }
    /* Create a new service if we couldn't find it in list */
    ret = TcNsServiceInit(context->uuid, (uint32_t)UUID_LEN, &service);
    /* Put unlock after TcNsServiceInit to make sure TcFindServiceFromAll * is correct */
    mutex_unlock(&g_serviceListLock);
    if (ret) {
        tloge("service init failed");
        mutex_unlock(&devFile->serviceLock);
        return NULL;
    }
    isNewService = true;
ADD_SERVICE:
    ret = AddServiceToDev(devFile, service);
    mutex_unlock(&devFile->serviceLock);
    if (ret) {
        if (isNewService) {
            PutServiceStruct(service);
        }
        service = NULL;
        tloge("fail to add service to dev\n");
        return NULL;
    }
    return service;
}

static int ProcCalcTaskHash(TcNsDevFile *devFile,
    TcNsClientContext *context, TcNsSession *session,
    TcNsService *service, uint8_t *flags)
{
    int ret;
    LosTaskCB *curStruct = NULL;
    LosTaskCB *halStruct = NULL;

    ret = CheckLoginMethod(devFile, context, flags);
    if (ret != 0) {
        return ret;
    }
    context->cmdId = GLOBAL_CMD_ID_OPEN_SESSION;
    mutex_init(&session->taSessionLock);

    ret = CheckTaskState(&halStruct, context);
    if (ret != 0) {
        return ret;
    }
    if (halStruct != NULL) {
        curStruct = halStruct;
    } else {
        curStruct = OsCurrTaskGet();
    }
    /* lock reason:
     * TeeCalcTaskHash will use the global value g_tee_shash_tfm
     */
    ret = CalcTaskHash(devFile->kernelApi, session, service, curStruct);
    return ret;
}

static void ProcAfterSmcCmd(TcNsDevFile *devFile,
    const TcNsClientContext *context, TcNsService *service,
    TcNsSession *session)
{
    session->sessionId = context->sessionId;
#ifdef TC_ASYNC_NOTIFY_SUPPORT
    session->waitData.sendWaitFlag = 0;
    init_waitqueue_head(&session->waitData.sendCmdWq);
#endif
    atomic_set(&session->usage, 1);
    session->owner = devFile;
    mutex_lock(&service->SessionLock);
    list_add_tail(&session->head, &service->sessionList);
    mutex_unlock(&service->SessionLock);
}

static int ProcOpenSession(TcNsDevFile *devFile,
    TcNsClientContext *context, TcNsService *service,
    TcNsSession *session, uint8_t flags)
{
    int ret;

    mutex_lock(&service->operationLock);
    ret = LoadTaImage(devFile, context);
    if (ret != 0) {
        tloge("load ta image failed\n");
        mutex_unlock(&service->operationLock);
        return ret;
    }
    /* send smc */
#ifdef SECURITY_AUTH_ENHANCE
    ret = GetSessionSecureParams(devFile, context, session);
    if (ret) {
        tloge("Get session secure parameters failed, ret = %d.\n", ret);
        /* Clean this session secure information */
        CleanSessionSecureInformation(session);
        mutex_unlock(&service->operationLock);
        return ret;
    }
    session->TcNsToken.tokenBuffer =
        calloc(1, TOKEN_BUFFER_LEN);
    session->TcNsToken.tokenLen = TOKEN_BUFFER_LEN;
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)
        session->TcNsToken.tokenBuffer)) {
        tloge("calloc %d bytes token failed.\n", TOKEN_BUFFER_LEN);
        /* Clean this session secure information */
        CleanSessionSecureInformation(session);
        mutex_unlock(&service->operationLock);
        return -ENOMEM;
    }
    ret = TcClientCall(context, devFile, session, flags);
    if (ret != 0) {
        /* Clean this session secure information */
        CleanSessionSecureInformation(session);
    }
#else
    ret = TcClientCall(context, devFile, session, flags);
#endif
    if (ret != 0) {
        mutex_unlock(&service->operationLock);
        tloge("smc_call returns error, ret=0x%x\n", ret);
        return ret;
    }
    ProcAfterSmcCmd(devFile, context, service, session);
    /* sessionId in tee is unique, but in concurrency scene
     * same sessionId may appear in tzdriver, put sessionList
     * add/del in service->operationLock can avoid it.
     */
    mutex_unlock(&service->operationLock);
    return ret;
}

static void ProcErrorSituation(TcNsDevFile *devFile,
    TcNsClientContext *context, TcNsService *service,
    TcNsSession *session)
{
    ReleaseFreeSession(devFile, context, session);
    mutex_lock(&devFile->serviceLock);
    DelServiceFromDev(devFile, service);
    mutex_unlock(&devFile->serviceLock);
    free(session);
    return;
}

int TcNsOpenSession(TcNsDevFile *devFile,
    TcNsClientContext *context)
{
    int ret;
    TcNsService *service = NULL;
    TcNsSession *session = NULL;
    uint8_t flags = TC_CALL_GLOBAL;
    bool checkValue = (devFile == NULL || context == NULL);

    if (checkValue == true) {
        tloge("invalid devFile or context\n");
        return -EINVAL;
    }

    ret = CheckProcessAccess(OsCurrTaskGet());
    if (ret) {
        tloge("tee driver fd may be leak\n");
        return -EPERM;
    }

    service = FindService(devFile, context);
    if (service == NULL) {
        tloge("find service failed\n");
        return -ENOMEM;
    }
    session = calloc(1, sizeof(*session));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)session)) {
        tloge("calloc failed\n");
        mutex_lock(&devFile->serviceLock);
        DelServiceFromDev(devFile, service);
        mutex_unlock(&devFile->serviceLock);
        return -ENOMEM;
    }

    ret = ProcCalcTaskHash(devFile, context, session, service,
        &flags);
    if (ret != 0) {
        goto error;
    }
    ret = ProcOpenSession(devFile, context, service, session, flags);
    if (ret == 0) {
        return ret;
    }
error:
    ProcErrorSituation(devFile, context, service, session);
    return ret;
}

static TcNsService *GetService(TcNsDevFile *devFile,
    const TcNsClientContext *context)
{
    TcNsService *service = NULL;

    mutex_lock(&devFile->serviceLock);
    service = TcFindServiceInDev(devFile,
        context->uuid, UUID_LEN);
    GetServiceStruct(service);
    mutex_unlock(&devFile->serviceLock);
    return service;
}

void PutSessionStruct(struct TagTcNsSession *session)
{
    if (session == NULL || !atomic_dec_and_test(&session->usage)) {
        return;
    }

#ifdef SECURITY_AUTH_ENHANCE
    if (session->TcNsToken.tokenBuffer != NULL) {
        if (memset_s(
            (void *)session->TcNsToken.tokenBuffer,
            session->TcNsToken.tokenLen,
            0,
            session->TcNsToken.tokenLen) != EOK) {
            tloge("Caution, memset failed!\n");
        }
        free(session->TcNsToken.tokenBuffer);
        session->TcNsToken.tokenBuffer = NULL;
        (void)session->TcNsToken.tokenBuffer; /* avoid Codex warning */
    }
#endif
    if (memset_s((void *)session, sizeof(*session), 0, sizeof(*session)) != EOK) {
        tloge("Caution, memset failed!\n");
    }
    free(session);
}

static TcNsSession *GetSession(TcNsService *service,
    TcNsDevFile *devFile, const TcNsClientContext *context)
{
    TcNsSession *session = NULL;

    mutex_lock(&service->SessionLock);
    session = TcFindSessionWithOwner(&service->sessionList,
        context->sessionId, devFile);
    GetSessionStruct(session);
    mutex_unlock(&service->SessionLock);
    return session;
}

void GetServiceStruct(struct TagTcNsService *service)
{
    if (service != NULL) {
        atomic_inc(&service->usage);
        tlogd("service->usage = %d\n", atomic_read(&service->usage));
    }
}

void PutServiceStruct(struct TagTcNsService *service)
{
    if (service != NULL) {
        tlogd("service->usage = %d\n", atomic_read(&service->usage));
        mutex_lock(&g_serviceListLock);
        if (atomic_dec_and_test(&service->usage)) {
            tlogd("del service [0x%x] from service list\n",
                *(uint32_t *)service->uuid);
            list_del(&service->head);
            free(service);
        }
        mutex_unlock(&g_serviceListLock);
    }
}

int TcNsCloseSession(TcNsDevFile *devFile,
    TcNsClientContext *context)
{
    int ret = -EINVAL;
    errno_t ret_err;
    TcNsService *service = NULL;
    TcNsSession *session = NULL;

    if (devFile == NULL || context == NULL) {
        tloge("invalid devFile or context\n");
        return ret;
    }
    service = GetService(devFile, context);
    if (service == NULL) {
        tloge("invalid service\n");
        return ret;
    }
    /*
     * sessionId in tee is unique, but in concurrency scene
     * same sessionId may appear in tzdriver, put sessionList
     * add/del in service->operationLock can avoid it.
     */
    mutex_lock(&service->operationLock);
    session = GetSession(service, devFile, context);
    if (session != NULL) {
        int ret2;
        mutex_lock(&session->taSessionLock);
        ret2 = CloseSession(devFile, session, context->uuid,
            (unsigned int)UUID_LEN, context->sessionId);
        mutex_unlock(&session->taSessionLock);
        if (ret2 != TEEC_SUCCESS) {
            tloge("close session smc failed!\n");
        }
#ifdef SECURITY_AUTH_ENHANCE
        /* Clean this session secure information */
        ret_err = memset_s((void *)&session->secureInfo,
            sizeof(session->secureInfo),
            0, sizeof(session->secureInfo));
        if (ret_err != EOK) {
            tloge("close session memset error=%d\n", ret_err);
        }
#endif
        mutex_lock(&service->SessionLock);
        list_del(&session->head);
        mutex_unlock(&service->SessionLock);

        PutSessionStruct(session);
        PutSessionStruct(session); /* pair with open session */

        ret = TEEC_SUCCESS;
        mutex_lock(&devFile->serviceLock);
        DelServiceFromDev(devFile, service);
        mutex_unlock(&devFile->serviceLock);
    } else {
        tloge("invalid session\n");
    }
    mutex_unlock(&service->operationLock);
    PutServiceStruct(service);
    return ret;
}

int TcNsSendCmd(TcNsDevFile *devFile,
    TcNsClientContext *context)
{
    int ret = -EINVAL;
    TcNsService *service = NULL;
    TcNsSession *session = NULL;
    bool checkValue = (devFile == NULL || context == NULL);

    if (checkValue == true) {
        tloge("invalid devFile or context\n");
        return ret;
    }
    tlogd("session id :%x\n", context->sessionId);
    service = GetService(devFile, context);
    /* check sessionid is validated or not */
    if (service != NULL) {
        session = GetSession(service, devFile, context);
        PutServiceStruct(service);
        if (session != NULL) {
            tlogd("send cmd find session id %x\n",
                context->sessionId);
            goto FIND_SESSION;
        }
    } else {
        tloge("can't find service\n");
    }
    tloge("send cmd can not find session id %u\n", context->sessionId);
    return ret;
FIND_SESSION:
    /* send smc */
    mutex_lock(&session->taSessionLock);
    ret = TcClientCall(context, devFile, session, 0);
    mutex_unlock(&session->taSessionLock);
    PutSessionStruct(session);
    if (ret != 0) {
        tloge("smc_call returns error, ret=0x%x\n", ret);
    }
    return ret;
}

int TcNsClientOpen(TcNsDevFile **devFile, uint8_t kernelApi)
{
    int ret = TEEC_ERROR_GENERIC;
    TcNsDevFile *dev = NULL;

    tlogd("TcClientOpen\n");
    if (devFile == NULL) {
        tloge("devFile is NULL\n");
        return -EFAULT;
    }
    dev = calloc(1, sizeof(*dev));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)dev)) {
        tloge("dev malloc failed\n");
        return ret;
    }
    mutex_lock(&g_tcNsDevList.devLock);
    list_add_tail(&dev->head, &g_tcNsDevList.devFileList);
    mutex_unlock(&g_tcNsDevList.devLock);
    mutex_lock(&g_deviceFileCntLock);
    dev->devFileId = g_deviceFileCnt;
    g_deviceFileCnt++;
    mutex_unlock(&g_deviceFileCntLock);
    INIT_LIST_HEAD(&dev->sharedMemList);
    dev->loginSetup = 0;
    dev->kernelApi = kernelApi;
    dev->loadAppFlag = 0;
    mutex_init(&dev->serviceLock);
    mutex_init(&dev->sharedMemLock);
    mutex_init(&dev->LoginSetupLock);
    *devFile = dev;
    ret = TEEC_SUCCESS;
    return ret;
}

void FreeDev(TcNsDevFile *dev)
{
    DelDevNode(dev);
    TeeAgentClearDevOwner(dev);
    if (memset_s((void *)dev, sizeof(*dev), 0, sizeof(*dev)) != EOK) {
        tloge("Caution, memset dev fail!\n");
    }
    free(dev);
}

int TcNsClientClose(TcNsDevFile *dev)
{
    int ret = TEEC_ERROR_GENERIC;
    uint32_t index;

    if (dev == NULL) {
        tloge("invalid dev(null)\n");
        return ret;
    }

    /* close unclosed session */
    for (index = 0; index < SERVICES_MAX_COUNT; index++) {
        CloseUnclosedSession(dev, index);
    }

    // for thirdparty agent, code runs here only when agent crashed
    SendCrashedEventResponseAll(dev);
    ret = TEEC_SUCCESS;
    FreeDev(dev);
    return ret;
}

static void ReleaseVmaSharedMem(TcNsDevFile *devFile,
    const LosVmMapRegion *vma)
{
    TcNsSharedMem *sharedMem = NULL;
    TcNsSharedMem *sharedMemTemp = NULL;
    bool find = false;

    mutex_lock(&devFile->sharedMemLock);
    list_for_each_entry_safe(sharedMem, sharedMemTemp,
        &devFile->sharedMemList, head) {
        if (sharedMem != NULL) {
            if (sharedMem->userAddr ==
                (void *)(uintptr_t)vma->range.base) {
                sharedMem->userAddr = NULL;
                find = true;
            } else if (sharedMem->userAddrCa ==
                (void *)(uintptr_t)vma->range.base) {
                sharedMem->userAddrCa = NULL;
                find = true;
            }

            if ((sharedMem->userAddr == NULL) &&
                (sharedMem->userAddrCa == NULL)) {
                list_del(&sharedMem->head);
            }

            /* pair with TcClientMmap */
            if (find == true) {
                PutSharememStruct(sharedMem);
                break;
            }
        }
    }
    mutex_unlock(&devFile->sharedMemLock);
}

static int TcNsSharedMemUnmap(TcNsDevFile *devFile, const unsigned int argp)
{
    if (devFile == NULL) {
        tloge("unmap input error\n");
        return -EINVAL;
    }

    LosVmMapRegion *vma = LOS_RegionFind(OsCurrProcessGet()->vmSpace, (vaddr_t)argp);
    if (vma == NULL) {
        tloge("unmap error memory\n");
        return -EINVAL;
    }

    bool checkValue = (IsTeecdProcess(g_teecdTask, OsCurrTaskGet())) && (!TcNsGetUid()) &&
        ((g_teecdTask->taskStatus & OS_TASK_STATUS_EXIT) || (OsCurrTaskGet()->taskStatus & OS_TASK_STATUS_EXIT));
    if (checkValue == true) {
        tlogd("teecd is killed, just return in vma close\n");
        return 0;
    }
    ReleaseVmaSharedMem(devFile, vma);
    return 0;
}

static TcNsSharedMem *AllocAndFindSharedMem(const LosVmMapRegion *vma,
    TcNsDevFile *devFile, bool *onlyRemap)
{
    TcNsSharedMem *shmTmp = NULL;
    unsigned long len = vma->range.size;

    /* using vma->vm_pgoff as share_mem index */
    /* check if aready allocated */
    list_for_each_entry(shmTmp, &devFile->sharedMemList, head) {
        if (atomic_read(&shmTmp->offset) == vma->pgOff) {
            tlogd("share_mem already allocated, shmTmp->offset=%d\n",
                atomic_read(&shmTmp->offset));
            /* args check:
             * 1. this shared mem is already mapped ?
             * 2. remap a different size sharedMem ?
             */
            if (shmTmp->userAddrCa != NULL ||
                vma->range.size != shmTmp->len) {
                tloge("already remap once!\n");
                return NULL;
            }
            /* return the same sharedmem specified by vma->vm_pgoff */
            *onlyRemap = true;
            GetSharememStruct(shmTmp);
            return shmTmp;
        }
    }

    /* if not find, alloc a new sharemem */
    return TcMemAllocate(len);
}

static int RemapSharedMem(LosVmMapRegion *vma, TcNsSharedMem *sharedMem)
{
    int ret;

    ret = RemapVmallocRange(vma, sharedMem->kernelAddr, 0);
    if (ret) {
        tloge("can't remap to user, ret = %d\n", ret);
        return -1;
    }
    return ret;
}

/* in this func, we need to deal with follow cases:
 * vendor CA alloc sharedmem (alloc and remap);
 * HAL alloc sharedmem (alloc and remap);
 * system CA alloc sharedmem (only just remap);
 */
static int TcClientMmap(struct file *filp, LosVmMapRegion *vma)
{
    int ret;
    TcNsDevFile *devFile = NULL;
    TcNsSharedMem *sharedMem = NULL;
    bool onlyRemap = false;
    bool checkValue = false;

    checkValue = (filp == NULL || vma == NULL || filp->f_priv == NULL);
    if (checkValue == true) {
        tloge("invalid args for tc mmap\n");
        return -EINVAL;
    }
    devFile = filp->f_priv;

    mutex_lock(&devFile->sharedMemLock);
    sharedMem = AllocAndFindSharedMem(vma, devFile, &onlyRemap);
    if (IS_ERR_OR_NULL(sharedMem)) {
        tloge("alloc shared mem failed\n");
        mutex_unlock(&devFile->sharedMemLock);
        return -ENOMEM;
    }

    ret = RemapSharedMem(vma, sharedMem);
    if (ret != 0) {
        if (onlyRemap) {
            PutSharememStruct(sharedMem);
        } else {
            TcMemFree(sharedMem);
        }
        mutex_unlock(&devFile->sharedMemLock);
        return ret;
    }

    if (onlyRemap) {
        sharedMem->userAddrCa = (void *)vma->range.base;
        mutex_unlock(&devFile->sharedMemLock);
        return ret;
    }
    sharedMem->userAddr = (void *)vma->range.base;
    atomic_set(&sharedMem->offset, vma->pgOff);
    GetSharememStruct(sharedMem);
    list_add_tail(&sharedMem->head, &devFile->sharedMemList);
    mutex_unlock(&devFile->sharedMemLock);
    return ret;
}

static int IoctlSessionSendCmd(TcNsDevFile *devFile,
    TcNsClientContext *context, void *argp)
{
    int ret;

    ret = TcNsSendCmd(devFile, context);
    if (ret) {
        tloge("TcNsSendCmd Failed ret is %d\n", ret);
    }
    if (copy_to_user(argp, context, sizeof(*context))) {
        if (ret == 0) {
            ret = -EFAULT;
        }
    }
    return ret;
}

static int TcClientSessionIoctl(struct file *file, unsigned int cmd,
    unsigned long arg)
{
    int ret = TEEC_ERROR_GENERIC;
    void *argp = (void __user *)(uintptr_t)arg;
    TcNsDevFile *devFile = file->f_priv;
    TcNsClientContext context;

    if (argp == NULL) {
        tloge("argp is NULL input buffer\n");
        ret = -EINVAL;
        return ret;
    }
    if (copy_from_user(&context, argp, sizeof(context))) {
        tloge("copy from user failed\n");
        return -EFAULT;
    }
    context.returns.origin = TEEC_ORIGIN_COMMS;
    switch (cmd) {
        case TC_NS_CLIENT_IOCTL_SES_OPEN_REQ: {
            ret = TcNsOpenSession(devFile, &context);
            if (ret) {
                tloge("TcNsOpenSession Failed ret is %d\n", ret);
            }
            if (copy_to_user(argp, &context, sizeof(context)) && ret == 0) {
                ret = -EFAULT;
            }
            break;
        }
        case TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ: {
            ret = TcNsCloseSession(devFile, &context);
            break;
        }
        case TC_NS_CLIENT_IOCTL_SEND_CMD_REQ: {
            ret = IoctlSessionSendCmd(devFile, &context, argp);
            break;
        }
        default:
            tloge("invalid cmd:0x%x!\n", cmd);
            return ret;
    }
    /*
     * Don't leak ERESTARTSYS to user space.
     *
     * CloseSession is not reentrant, so convert to -EINTR.
     * In other case, RestartSyscall().
     *
     * It is better to call it right after the error code
     * is generated (in TcClientCall), but kernel CAs are
     * still exist when these words are written. Setting TIF
     * flags for callers of those CAs is very hard to analysis.
     *
     * For kernel CA, when ERESTARTSYS is seen, loop in kernel
     * instead of notifying user.
     *
     * P.S. ret code in this function is in mixed naming space.
     * See the definition of ret. However, this function never
     * return its default value, so using -EXXX is safe.
     */
    if (ret == -ERESTARTSYS) {
        if (cmd == TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ) {
            ret = -EINTR;
        } else {
            return RestartSyscall();
        }
    }
    return ret;
}

static int IoctlRegisterAgent(TcNsDevFile *devFile, unsigned long arg)
{
    int ret;
    struct AgentIoctlArgs args;

    if (copy_from_user(&args, (void *)arg, sizeof(args))) {
        tloge("copy agent args failed\n");
        return -EFAULT;
    }

    ret = TcNsRegisterAgent(devFile, args.id, args.bufferSize,
        &args.buffer, true);
    if (ret == 0) {
        if (copy_to_user((void *)arg, &args, sizeof(args))) {
            tloge("copy agent user addr failed\n");
        }
    }

    return ret;
}

static int IoctlUnregisterAgent(const TcNsDevFile *devFile, unsigned long arg)
{
    int ret;
    struct SmcEventData *eventData = NULL;
    eventData = FindEventControl((unsigned int)arg);
    if (eventData == NULL) {
        tloge("invalid agent id\n");
        return TEEC_ERROR_GENERIC;
    }
    if (eventData->owner != devFile) {
        tloge("invalid unregister request\n");
        PutAgentEvent(eventData);
        return TEEC_ERROR_GENERIC;
    }
    PutAgentEvent(eventData);
    ret = TcNsUnregisterAgent((unsigned int)arg);
    return ret;
}

static long TcAgentIoctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = TEEC_ERROR_GENERIC;
    TcNsDevFile *devFile = file->f_priv;

    if (devFile == NULL) {
        tloge("invalid params\n");
        return ret;
    }
    switch (cmd) {
        case TC_NS_CLIENT_IOCTL_WAIT_EVENT: {
            ret = TcNsWaitEvent((unsigned int)arg);
            break;
        }
        case TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE: {
            ret = TcNsSendEventResponse((unsigned int)arg);
            break;
        }
        case TC_NS_CLIENT_IOCTL_REGISTER_AGENT: {
            ret = IoctlRegisterAgent(devFile, arg);
            break;
        }
        case TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT: {
            ret = IoctlUnregisterAgent(devFile, arg);
            break;
        }
        case TC_NS_CLIENT_IOCTL_SYC_SYS_TIME: {
            ret = TcNsSyncSysTime((TcNsClientTime *)(uintptr_t)arg);
            break;
        }
        case TC_NS_CLIENT_IOCTL_SET_NATIVECA_IDENTITY: {
            ret = TcNsSetNativeHash(arg, GLOBAL_CMD_ID_SET_CA_HASH);
            break;
        }
        case TC_NS_CLIENT_IOCTL_LATEINIT: {
            ret = TcNsLateInit(arg);
            break;
        }
        default:
            tloge("invalid cmd!\n");
            return ret;
    }
    tlogd("TC_NS_ClientIoctl ret = 0x%x\n", ret);
    return ret;
}

static int TcClientIoctlOthers(struct file *file, int cmd, unsigned long arg)
{
    void *argp = (void __user *)(uintptr_t)arg;
    int ret = TEEC_ERROR_GENERIC;

    switch (cmd) {
        /* IOCTLs for the secure storage daemon */
        case TC_NS_CLIENT_IOCTL_WAIT_EVENT:
        case TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE:
        case TC_NS_CLIENT_IOCTL_REGISTER_AGENT:
        case TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT:
        case TC_NS_CLIENT_IOCTL_SYC_SYS_TIME:
        case TC_NS_CLIENT_IOCTL_LOAD_TTF_FILE_AND_NOTCH_HEIGHT:
        case TC_NS_CLIENT_IOCTL_SET_NATIVECA_IDENTITY:
        case TC_NS_CLIENT_IOCTL_LATEINIT:
            ret = TcAgentIoctl(file, cmd, arg);
            break;
#ifdef DEF_ENG
        case TC_NS_CLIENT_IOCTL_TST_CMD_REQ: {
            tlogd("come into tst cmd\n");
            ret = TcNsTstCmd(file->f_priv, argp);
            break;
        }
#endif
        case TC_NS_CLIENT_IOCTL_GET_TEE_VERSION: {
            ret = TcNsGetTeeVersion(file->f_priv, argp);
            break;
        }
        case TC_NS_CLIENT_IOCTL_UNMAP_SHARED_MEM: {
            ret = TcNsSharedMemUnmap(file->f_priv, (unsigned int)(UINTPTR)argp);
            break;
        }
        default: {
            tloge("invalid cmd 0x%x!\n", cmd);
            break;
        }
    }
    return ret;
}

static int TcClientIoctl(struct file *file, int cmd, unsigned long arg)
{
    int ret = TEEC_ERROR_GENERIC;
    void *argp = (void __user *)(uintptr_t)arg;
    TcNsDevFile *devFile = file->f_priv;
    TcNsClientContext clientContext = {{0}};

    switch (cmd) {
        /* IOCTLs for the CAs */
        case TC_NS_CLIENT_IOCTL_SES_OPEN_REQ:
            /* Upvote for peripheral zone votage, needed by Coresight.
             * Downvote will be processed inside CFC_RETURN_PMCLK_ON_COND
             */
        /* Fall through */
        case TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ:
        case TC_NS_CLIENT_IOCTL_SEND_CMD_REQ:
            ret = TcClientSessionIoctl(file, cmd, arg);
            break;
        case TC_NS_CLIENT_IOCTL_LOAD_APP_REQ:
            ret = TcNsLoadSecfile(devFile, argp);
            break;
        case TC_NS_CLIENT_IOCTL_CANCEL_CMD_REQ:
            if (argp == NULL) {
                tloge("argp is NULL input buffer\n");
                ret = -EINVAL;
                break;
            }
            if (copy_from_user(&clientContext, argp,
                sizeof(clientContext))) {
                tloge("copy from user failed\n");
                ret = -ENOMEM;
                break;
            }
            ret = TcNsSendCmd(devFile, &clientContext);
            break;
        /* This is the login information
         * and is set teecd when client opens a new session
         */
        case TC_NS_CLIENT_IOCTL_LOGIN: {
            ret = TcNsClientLoginFunc(devFile, argp);
            break;
        }
        default:
            ret = TcClientIoctlOthers(file, cmd, arg);
            break;
    }

    tlogd("tc client ioctl ret = 0x%x\n", ret);
    return ret;
}

static int TcClientOpen(struct file *file)
{
    int ret;
    TcNsDevFile *dev = NULL;
    ret = CheckProcessAccess(OsCurrTaskGet());
    if (ret) {
        tloge(KERN_ERR "teecd service may be exploited 0x%x\n", ret);
        return -EPERM;
    }

    file->f_priv = NULL;
    ret = TcNsClientOpen(&dev, TEE_REQ_FROM_USER_MODE);
    if (ret == TEEC_SUCCESS) {
        file->f_priv = dev;
    }
    return ret;
}

static int TcClientClose(struct file *file)
{
    int ret = TEEC_ERROR_GENERIC;
    TcNsDevFile *dev = file->f_priv;
    bool checkValue = false;

    checkValue = (IsTeecdProcess(g_teecdTask, OsCurrTaskGet())) &&
        (!TcNsGetUid());
    if (checkValue == true) {
        /* for teecd close fd */
        checkValue = (g_teecdTask->taskStatus & OS_TASK_STATUS_EXIT) ||
            (OsCurrTaskGet()->taskStatus & OS_TASK_STATUS_EXIT);
        if (checkValue == true) {
            /* when teecd is be killed or crash */
            tloge("teecd is killed, something bad must be happened!!!\n");
            if (IsSystemAgent(dev)) {
                /* for teecd agent close fd */
                SendEventResponseSingle(dev);
                FreeDev(dev);
            } else {
                /* for ca damon close fd */
                ret = NsClientCloseTeecdNotAgent(dev);
            }
        } else {
            /* for ca damon close fd when ca damon close fd
             *  later than HAL thread
             */
            ret = TcNsClientClose(dev);
        }
    } else {
        /* for CA(HAL thread) close fd */
        ret = TcNsClientClose(dev);
    }
    file->f_priv = NULL;
    return ret;
}

static const struct file_operations_vfs g_tcNsClientFops = {
    .open = TcClientOpen,
    .close = TcClientClose,
    .ioctl = TcClientIoctl,
    .mmap = TcClientMmap,
};

bool ScheduleWorkOn(int cpu, struct work_struct *work)
{
    return queue_work(g_tzdriverWq, work);
}

static int TcNsClientInit(void)
{
    int ret;

    tlogd("TcNsClientInit\n");

    ret = CreateTcClientDevice(TC_NS_CLIENT_DEV_NAME, &g_tcNsClientFops);
    if (ret != EOK) {
        tloge("create tee device error.\n");
        return ret;
    }
    ret = memset_s(&g_tcNsDevList, sizeof(g_tcNsDevList), 0,
        sizeof(g_tcNsDevList));
    if (ret != EOK) {
        return ret;
    }

    INIT_LIST_HEAD(&g_tcNsDevList.devFileList);
    mutex_init(&g_tcNsDevList.devLock);
    INIT_LIST_HEAD(&g_serviceList);

    g_tzdriverWq = create_workqueue("g_tzdriverWq");
    if (g_tzdriverWq == NULL) {
        tloge("couldn't create workqueue.\n");
        return -ENOMEM;
    }
    return 0;
}

static int TcTeeosInit(void)
{
    int ret;

    ret = SmcInitData();
    if (ret < 0) {
        tloge("smc init failed\n");
        return ret;
    }

    ret = TcMemInit();
    if (ret < 0) {
        tloge("tcmem init failed\n");
        goto SMC_DATA_FREE;
    }

    // following failure don't block tzdriver init proc;
    AgentInit();

    ret = TzSpiInit();
    if (ret) {
        tloge("tz spi init failed\n");
    }
    return 0;

SMC_DATA_FREE:
    SmcFreeData();
    return ret;
}

static void TcReInit(void)
{
    int ret = 0;

    if (InitSmcSvcThread()) {
        tloge("init svc thread\n");
        ret = -EFAULT;
    }

    if (ret) {
        tloge("Caution! Running environment init failed!\n");
    }
}

int TcInit(void)
{
    int ret = TcNsClientInit();
    if (ret != 0) {
        goto TC_INIT_FAIL;
    }

    ret = TcTeeosInit();
    if (ret != 0) {
        goto TC_INIT_FAIL;
    }
    // run-time environment init failure don't block tzdriver init proc;
    TcReInit();

#ifdef DEF_ENG
    TzdebugInit();
#endif
    return 0;

TC_INIT_FAIL:
    ret = unregister_driver(TC_NS_CLIENT_DEV_NAME);
    if (g_tzdriverWq != NULL) {
        destroy_workqueue(g_tzdriverWq);
    }
    return ret;
}
