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

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Defines the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module harmonizes OS interface differences and provides unified OS interfaces externally,
 * including the memory management, thread, mutex, spinlock, semaphore, timer, file, interrupt, time,
 * atomic, firmware, and I/O operation modules.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file osal_io.h
 *
 * @brief Declares I/O interfaces.
 *
 * This file provides operations, such as reading data from and writing data into an I/O address space,
 * remapping an I/O address space to its virtual address space, and unmapping an I/O virtual address
 * associated with the physical address.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OSAL_IO_H
#define OSAL_IO_H

#include <linux/io.h>
#include <linux/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Writes one byte of data into an I/O address space.
 *
 * @param value Indicates the data to write.
 * @param address Indicates the address to write.
 *
 * @since 1.0
 * @version 1.0
 */
#define OSAL_WRITEB(value, address) writeb(value, address)
/**
 * @brief Writes a short integer into an I/O address space.
 *
 * @param value Indicates the data to write.
 * @param address Indicates the address to write.
 *
 * @since 1.0
 * @version 1.0
 */
#define OSAL_WRITEW(value, address) writew(value, address)
/**
 * @brief Writes an integer into an I/O address space.
 *
 * @param value Indicates the data to write.
 * @param address Indicates the address to write.
 *
 * @since 1.0
 * @version 1.0
 */
#define OSAL_WRITEL(value, address) writel(value, address)

/**
 * @brief Reads one byte of data from an I/O address space.
 *
 * @param address Indicates the address to read.
 * @return Returns the byte.
 *
 * @since 1.0
 * @version 1.0
 */
#define OSAL_READB(address) readb(address)
/**
 * @brief Reads a short integer from an I/O address space.
 *
 * @param address Indicates the address to read.
 * @return Returns the short integer.
 *
 * @since 1.0
 * @version 1.0
 */
#define OSAL_READW(address) readw(address)
/**
 * @brief Reads an integer from an I/O address space.
 *
 * @param address Indicates the address to read.
 * @return Returns the integer.
 *
 * @since 1.0
 * @version 1.0
 */
#define OSAL_READL(address) readl(address)

/**
 * @brief Remaps an I/O physical address to its virtual address.
 *
 * @param phys_addr Indicates the I/O physical address.
 * @param size Indicates the size of the physical address to remap.
 * @return Returns the virtual address.
 *
 * @since 1.0
 * @version 1.0
 */
static inline void *OsalIoRemap(unsigned long phys_addr, unsigned long size)
{
    return ioremap(phys_addr, size);
}

/**
 * @brief Unmaps an I/O virtual address associated with the physical address.
 *
 * The virtual address is the one returned by calling {@link OsalIoRemap}.
 *
 * @param addr Indicates the pointer to the virtual address to unmap.
 *
 * @since 1.0
 * @version 1.0
 */
static inline void OsalIoUnmap(void *addr)
{
    iounmap(addr);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_IO_H */
/** @} */
