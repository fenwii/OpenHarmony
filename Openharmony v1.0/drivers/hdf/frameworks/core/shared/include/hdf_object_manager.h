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

#ifndef HDF_OBJECT_MANAGER_H
#define HDF_OBJECT_MANAGER_H

#include <stdio.h>
#include "hdf_object.h"

enum {
    HDF_OBJECT_ID_DEVMGR_SERVICE = 0,
    HDF_OBJECT_ID_DEVSVC_MANAGER,
    HDF_OBJECT_ID_DEVHOST_SERVICE,
    HDF_OBJECT_ID_DRIVER_INSTALLER,
    HDF_OBJECT_ID_DRIVER_LOADER,
    HDF_OBJECT_ID_DEVICE,
    HDF_OBJECT_ID_DEVICE_TOKEN,
    HDF_OBJECT_ID_DEVICE_SERVICE,
    HDF_OBJECT_ID_REMOTE_SERVICE,
    HDF_OBJECT_ID_MAX
};

struct HdfObjectCreator {
    struct HdfObject *(*Create)(void);
    void (*Release)(struct HdfObject *);
};

const struct HdfObjectCreator *HdfObjectManagerGetCreators(int objectId);
struct HdfObject *HdfObjectManagerGetObject(int ObjectId);
void HdfObjectManagerFreeObject(struct HdfObject *object);

#endif /* HDF_OBJECT_MANAGER_H */
