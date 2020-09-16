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

/**
 * @addtogroup wifiiot
 * @{
 *
 * @brief Provides dedicated device operation interfaces on the Wi-Fi module,
 * including ADC, AT, flash, GPIO, I2C, I2S, partition, PWM, SDIO, UART, and watchdog.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hal_wifiiot_partition.h
 *
 * @brief Declares the partition interface functions.
 *
 * These functions are used to initialize partitions and obtain partition tables. \n
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef HAL_WIFIIOT_PARTITION_H
#define HAL_WIFIIOT_PARTITION_H

/**
 * @brief Indicates the maximum number of partition tables.
 */
#define HAL_WIFI_IOT_FLASH_PARTITON_MAX 12

/**
 * @brief Indicates the partition table ID.
 */
typedef enum {
    /** Boot partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_BOOT = 0,
    /** Factory NV partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_FACTORY_NV,
    /** Normal NV partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_NORMAL_NV,
    /** Normal backup NV partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_NORMAL_NV_BACKUP,
    /** Kernel A running partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_KERNEL_A,
    /** Kernel B running partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_KERNEL_B,
    /** HiLink partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_HILINK,
    /** File system partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_FILE_SYSTEM,
    /** User reserved partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_USR_RESERVE,
    /** HiLink PKI partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_HILINK_PKI,
    /** Crash log partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_CRASH_INFO,
    /** Backup boot partition ID */
    HAL_WIFI_IOT_FLASH_PARTITON_BOOT_BACK,
} HalWifiIotFlashPartitionTableId;

/**
 * @brief Describes an entry in a flash partition table.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /** Address of a flash partition. The value is 16 MB.
     * If the address is in reverse order,
     * the value is the end low address.
     */
    unsigned int  addr : 24;
    /** Flash partition ID */
    unsigned int  id : 7;
    /** Storage direction of the flash partition.
     * The value <b>0</b> indicates the regular order,
     * and <b>1</b> indicates the reverse order.
     */
    unsigned int  dir : 1;
    /** Size of the flash partition */
    unsigned int  size : 24;
    /** Padding bit */
    unsigned int  reserve : 8;
    /** Custom flash partition information */
    unsigned int  addition;
} HalWifiIotFlashPartitionInfo;


/**
 * @brief Describes a flash partition table.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /** Description for an entry in a flash partition table.
     * For details on the number of entries, see {@link WIFI_IOT_FLASH_PARTITON_MAX}.
     */
    HalWifiIotFlashPartitionInfo table[HAL_WIFI_IOT_FLASH_PARTITON_MAX];
} HalWifiIotFlashPartitionTable;

/**
 * @brief Initializes a flash partition.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalFlashPartitionInit(void);

/**
 * @brief Obtains a flash partition table.
 *
 * @return Returns the pointer to the partition table.
 * @since 1.0
 * @version 1.0
 */
HalWifiIotFlashPartitionTable *HalGetPartitionTable(void);

#endif
/** @} */
