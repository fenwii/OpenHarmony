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

#include "hcs_parser.h"
#include "hcs_blob_if.h"
#include "hcs_generate_tree.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG hcs_parser

static int32_t GetHcsTreeSize(const char *blob, int32_t nodeLength)
{
    return GenerateCfgTree(blob, nodeLength, NULL, NULL);
}

bool HcsDecompile(const char *hcsBlob, uint32_t offset, struct DeviceResourceNode **root)
{
    int32_t nodeLength = HcsGetNodeLength(hcsBlob + offset);
    if (nodeLength < 0) {
        HDF_LOGE("%s failed, HcsGetNodeLength failed", __func__);
        return false;
    }

    int32_t treeMemLength = GetHcsTreeSize(hcsBlob + offset, nodeLength);
    if (treeMemLength <= 0) {
        HDF_LOGE("%s failed, GetHcsTreeSize failed", __func__);
        return false;
    }

    char *treeMem = (char *)OsalMemCalloc(treeMemLength);
    if (treeMem == NULL) {
        HDF_LOGE("%s failed, OsalMemCalloc Device tree memory failed", __func__);
        return false;
    }
    int32_t treeLayer = GenerateCfgTree(hcsBlob + offset, nodeLength, treeMem, root);
    if (treeLayer <= 0) {
        HDF_LOGE("%s failed, the treeLayer is %d", __func__, treeLayer);
        OsalMemFree(treeMem);
        *root = NULL;
        return false;
    }
    return true;
}