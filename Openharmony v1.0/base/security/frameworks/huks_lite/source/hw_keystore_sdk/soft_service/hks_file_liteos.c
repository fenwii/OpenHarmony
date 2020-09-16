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

#ifdef _SECURE_ENVIREMENT_NMI_
#include "hks_file_liteos.h"
#include "securec.h"
#include "hks_types.h"
#include "hks_errno.h"
#include "base/hi1131/hi_fs.h"
#include "hks_log_utils.h"

#define HKS_STORE_DIR "./hks_store/"
#define PATH_MAX_SIZE (256 + 64 + sizeof(HKS_STORE_DIR) + 1)

static int32_t __hks_get_key_path(struct hks_blob *path, const struct hks_blob *alias)
{
    if ((path == NULL) || (alias == NULL) || (path->data == NULL) || (alias->data == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((alias->size == 0) || (path->size == 0))
        return HKS_ERROR_INVALID_ARGUMENT;

    uint8_t *tmp = path->data;
    size_t store_dir_len = strlen(HKS_STORE_DIR);

    if (path->size <= store_dir_len)
        return HKS_ERROR_INVALID_ARGUMENT;

    if (memcpy_s(tmp, path->size, HKS_STORE_DIR, store_dir_len) != EOK)
        return HKS_ERROR_BAD_STATE;
    tmp = tmp + store_dir_len;
    if (memcpy_s(tmp, path->size - store_dir_len, alias->data, alias->size) != EOK)
        return HKS_ERROR_BAD_STATE;

    return 0;
}

static int32_t __hks_read_file(struct hks_blob *out, const char *path, size_t size)
{
    int32_t status = HKS_STATUS_OK;
    hi_s32 fd = hi_open(path, HI_FS_O_RDONLY);

    if (fd < 0) {
        log_error("%s: failed to open file\n", __func__);
        return HKS_FAILURE;
    }

    out->size = size;
    if (hi_read(fd, (hi_char *)out->data, size) < 0) {
        log_error("%s: failed to read file\n", __func__);
        status = HKS_FAILURE;
    }

    if (hi_close(fd) < 0) {
        log_error("%s: failed to close file\n", __func__);
        return HKS_FAILURE;
    }

    log_info("%s: size: %zu.\n", __func__, size);

    return status;
}

int32_t hks_file_liteos_read(const char *file_name, uint32_t offset, uint8_t *buf, uint32_t len)
{
    hks_if_true_return_error(((file_name == NULL) || (buf == NULL)), HKS_ERROR_NULL_POINTER);

    /* now offset is 0, but we maybe extend hi1131 file interfaces in the future */
    hks_if_true_return_error((offset != 0), HKS_ERROR_INVALID_ARGUMENT);

    hi_u32 file_size = -1;
    char path_buf[PATH_MAX_SIZE] = {0};

    /* id cannot be NULL, but we may be only interested in if the key exsits. in that case blob is NULL */
    struct hks_blob path = { HKS_BLOB_TYPE_ALIAS, (uint8_t *)path_buf, sizeof(path_buf) };
    const struct hks_blob alias = { HKS_BLOB_TYPE_ALIAS, (uint8_t *)file_name, strlen(file_name) };

    if (__hks_get_key_path(&path, &alias)) {
        log_error("%s: failed to get path for key.\n", __func__);
        return HKS_ERROR_STORAGE_FAILURE;
    }

    if (hi_stat((const hi_char *)path_buf, &file_size) < 0) {
        log_error("%s: stat file failed.\n", __func__);
        return HKS_ERROR_STORAGE_FAILURE;
    }

    if (len < file_size) {
        log_error("%s: key buffer too small for key file of size: %u\n", __func__, file_size);
        return HKS_ERROR_BUFFER_TOO_SMALL;
    }

    struct hks_blob blob = { 0, buf, len };

    if (__hks_read_file(&blob, (const char *)path_buf, file_size))
        return HKS_ERROR_STORAGE_FAILURE;
    else
        return blob.size;
}

int32_t hks_file_liteos_write(const char *file_name, uint32_t offset, const uint8_t *buf, uint32_t len)
{
    hks_if_true_return_error(((file_name == NULL) || (buf == NULL)), HKS_ERROR_NULL_POINTER);

    /* now offset is 0, but we maybe extend hi1131 file interfaces in the future */
    hks_if_true_return_error((offset != 0), HKS_ERROR_INVALID_ARGUMENT);

    int32_t status = HKS_STATUS_OK;
    char path_buf[PATH_MAX_SIZE] = {0};
    struct hks_blob path = { HKS_BLOB_TYPE_ALIAS, (uint8_t *)path_buf, sizeof(path_buf) };
    const struct hks_blob alias = { HKS_BLOB_TYPE_ALIAS, (uint8_t *)file_name, strlen(file_name) };

    if (__hks_get_key_path(&path, &alias)) {
        log_error("%s: failed to get path for key.\n", __func__);
        return HKS_ERROR_STORAGE_FAILURE;
    }

    hi_s32 fd = hi_open((const hi_char *)path_buf, HI_FS_O_CREAT | HI_FS_O_TRUNC | HI_FS_O_RDWR);

    if (fd < 0) {
        log_error("%s: failed to open key file, errno = 0x%x\n", __func__, hi_get_fs_error());
        return HKS_ERROR_STORAGE_FAILURE;
    }

    if (hi_write(fd, (hi_char *)buf, len) < 0) {
        log_error("%s: failed to write key file, errno = 0x%x\n", __func__, hi_get_fs_error());
        status = HKS_ERROR_STORAGE_FAILURE;
    }

    if (hi_close(fd) < 0) {
        log_error("%s: failed to close file, errno = 0x%x\n", __func__, hi_get_fs_error());
        return HKS_ERROR_STORAGE_FAILURE;
    }

    return status;
}

int32_t hks_file_liteos_size(const char *file_name)
{
    hks_if_true_return_error((file_name == NULL), HKS_ERROR_NULL_POINTER);

    hi_u32 file_size = -1;
    hi_s32 ret;
    char path_buf[PATH_MAX_SIZE] = {0};

    /* id cannot be NULL, but we may be only interested in if the key exsits. in that case blob is NULL */
    struct hks_blob path = { HKS_BLOB_TYPE_ALIAS, (uint8_t *)path_buf, sizeof(path_buf) };
    const struct hks_blob alias = { HKS_BLOB_TYPE_ALIAS, (uint8_t *)file_name, strlen(file_name) };

    if (__hks_get_key_path(&path, &alias)) {
        log_error("%s: failed to get path for key.\n", __func__);
        return HKS_ERROR_STORAGE_FAILURE;
    }

    ret = hi_stat((const hi_char *)path_buf, &file_size);
    if (ret < 0) {
        log_error("%s: stat file failed.\n", __func__);
        return HKS_ERROR_STORAGE_FAILURE;
    }
    return file_size;
}
#endif /* _SECURE_ENVIREMENT_NMI_ */
