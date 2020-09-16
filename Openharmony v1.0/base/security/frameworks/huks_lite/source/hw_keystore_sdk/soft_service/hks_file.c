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

#include "hks_file.h"

#include "common/hks_common.h"
#include "common/hks_mem.h"
#include "common/hks_utility.h"
#include "hks_errno.h"

#ifdef _SECURE_ENVIREMENT_NMI_
#include "hks_file_liteos.h"
#endif

/* the max size of file IO */
#define HKS_FILE_IO_SIZE_MAX 1024

static struct hks_file_callbacks g_file_callbacks;

int32_t hks_file_register_callbacks(const struct hks_file_callbacks *callbacks)
{
    hks_if_true_return_error((callbacks == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((callbacks->read == NULL ||
        callbacks->write == NULL || callbacks->file_size == NULL),
        HKS_ERROR_NULL_POINTER);

    g_file_callbacks.file_size = callbacks->file_size;
    g_file_callbacks.read = callbacks->read;
    g_file_callbacks.write = callbacks->write;

    return HKS_STATUS_OK;
}

#ifdef _SECURE_ENVIREMENT_NMI_
static struct hks_flash_operation_callbacks g_flash_operation_callbacks;

void hks_file_liteos_init(void)
{
    /* hi1131 file operation call interal interfaces, hks_init may be called by hichain for multiple times. */
    if ((g_file_callbacks.read == hks_file_liteos_read) &&
        (g_file_callbacks.write == hks_file_liteos_write) &&
        (g_file_callbacks.file_size == hks_file_liteos_size))
        return;

    g_file_callbacks.file_size = hks_file_liteos_size;
    g_file_callbacks.read = hks_file_liteos_read;
    g_file_callbacks.write = hks_file_liteos_write;

    return;
}

#endif

int32_t hks_file_read(const char *file_name, uint32_t offset, uint8_t *buf,
    uint32_t buf_len, int32_t *len)
{
    int32_t real_len;

    if ((g_file_callbacks.read == NULL) || (file_name == NULL) || (buf == NULL) || (len == NULL))
        return HKS_ERROR_NULL_POINTER;

    real_len = g_file_callbacks.read(file_name, offset, buf, buf_len);
    if (real_len < 0)
        return HKS_ERROR_READ_FILE_FAIL;
    else
        *len = real_len;

    return HKS_STATUS_OK;
}

int32_t hks_file_write(const char *file_name, uint32_t offset, const uint8_t *buf,
    uint32_t len)
{
    int32_t status;

    if ((g_file_callbacks.write == NULL) || (file_name == NULL) || (buf == NULL))
        return HKS_ERROR_NULL_POINTER;

    status = g_file_callbacks.write(file_name, offset, buf, len);
    if (status != 0)
        return HKS_ERROR_WRITE_FILE_FAIL;
    else
        return HKS_STATUS_OK;
}

int32_t hks_file_size(const char *file_name, uint32_t *size)
{
    int file_size;

    if ((g_file_callbacks.file_size == NULL) || (file_name == NULL) || (size == NULL))
        return HKS_ERROR_NULL_POINTER;

    file_size = g_file_callbacks.file_size(file_name);
    if (file_size < 0)
        return HKS_ERROR_FILE_SIZE_FAIL;

    *size = file_size;

    return HKS_STATUS_OK;
}

/*
 * initialize file data
 * parameter:
 *     file_name - [in] - filename
 *     file_size - [in] - file size
 *     data_type - [in] - data type
 * return value: none
 */
static int32_t hks_file_init_data(const char *file_name, uint32_t file_size,
    uint8_t data_type)
{
    uint8_t *file_buf = (uint8_t *)HKS_MALLOC(HKS_FILE_IO_SIZE_MAX);

    if (file_buf == NULL) {
        log_error("malloc file buffer fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    int32_t rc = 0;
    uint32_t offset = 0;
    uint32_t write_len;

    while (offset < file_size) {
        if ((offset + HKS_FILE_IO_SIZE_MAX) < file_size)
            write_len = HKS_FILE_IO_SIZE_MAX;
        else
            write_len = file_size - offset;

        rc = hks_init_buf_data(data_type, file_buf, write_len);
        if (rc != HKS_STATUS_OK)
            break;

        rc = hks_file_write(file_name, offset, file_buf, write_len);
        if (rc != HKS_STATUS_OK)
            break;

        offset += write_len;
    }

    hks_free_ptr(file_buf);

    return rc;
}

/*
 * cancel callbacks
 * parameter: none
 * return value: none
 */
void hks_file_cancel_callbacks(void)
{
    g_file_callbacks.file_size = NULL;
    g_file_callbacks.read = NULL;
    g_file_callbacks.write = NULL;

    return;
}

/*
 * delete file safely
 * parameter:
 *     file_name - [in] - file name
 * return value: none
 */
void hks_file_del_s(const char *file_name)
{
    if (file_name == NULL)
        return;

    uint8_t init_data_type[HKS_INIT_DATA_TYPE_NUM] = {
        HKS_INIT_DATA_TYPE_ALL_ZERO,
        HKS_INIT_DATA_TYPE_ALL_ONE,
        HKS_INIT_DATA_TYPE_RANDOM
    };

    uint32_t file_size = 0;
    int32_t rc = hks_file_size(file_name, &file_size);

    if ((rc != HKS_STATUS_OK) || (file_size == 0))
        return;

    uint32_t i = 0;

    for (; i < HKS_INIT_DATA_TYPE_NUM; ++i) {
        rc = hks_file_init_data(file_name, file_size,
            init_data_type[i]);
        if (rc != HKS_STATUS_OK)
            break;
    }

    return;
}

