/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HDF_SYSCALL_ADAPTER_H
#define HDF_SYSCALL_ADAPTER_H

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <osal_mutex.h>
#include <osal_thread.h>
#include <hdf_dlist.h>
#include "hdf_io_service.h"

struct HdfWriteReadBuf {
    int cmdCode;
    size_t writeSize; // bytes to write
    size_t writeConsumed; // bytes consumed by driver (for ERESTARTSYS)
    uintptr_t writeBuffer;
    size_t readSize; // bytes to read
    size_t readConsumed; // bytes consumed by driver (for ERESTARTSYS)
    uintptr_t readBuffer;
};

enum HdfDevListenerThreadStatus {
    LISTENER_UNINIT = 0,
    LISTENER_STOPPED,
    LISTENER_RUNNING,
    LISTENER_WAITING,
};

struct HdfDevListenerThread {
    struct OsalMutex mutex;
    struct HdfSyscallAdapter *adapter;
    struct OsalThread thread;
    uint8_t status;
    bool shouldStop;
};

struct HdfSyscallAdapter {
    struct HdfIoService super;
    struct OsalMutex mutex;
    struct DListHead listenerList;
    int fd;
    struct DListHead listNode;
    struct HdfDevListenerThread *thread;
};

#define HDF_WRITE_READ _IOWR('b', 1, struct HdfSBuf)
#define HDF_READ_DEV_EVENT _IOR('b', 2, struct HdfSBuf)
#define HDF_LISTEN_EVENT_START _IO('b', 3)
#define HDF_LISTEN_EVENT_STOP _IO('b', 4)

#endif /* HDF_SYSCALL_ADAPTER_H */
