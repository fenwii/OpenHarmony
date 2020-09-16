/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#ifndef _MMC_BLOCK_H
#define _MMC_BLOCK_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

struct mmc_block;
struct block_operations;

extern const char *mmc_block_get_node_name(const struct mmc_block *block);
extern const struct block_operations *mmc_block_get_bops(const struct mmc_block *block);
extern struct disk_divide_info *get_emmc(void);
extern ssize_t do_mmc_erase(unsigned int block_id, size_t start_sector, unsigned int nsectors);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif
