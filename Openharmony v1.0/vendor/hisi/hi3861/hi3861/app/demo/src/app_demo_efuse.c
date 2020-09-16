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

#include <app_demo_efuse.h>

hi_u32 get_efuse_id_size_test(hi_void)
{
    hi_s32 i;
    hi_u32 efuse_size;

    for (i = 0; i < HI_EFUSE_IDX_MAX; i++) {
        efuse_size = hi_efuse_get_id_size((hi_efuse_idx)i);
        if (efuse_size == HI_ERR_EFUSE_INVALIDATE_ID) {
            printf("***exception***! failed to get size of efuse ID%d(0x%02X)\n", i, i);
            return efuse_size;
        }

        printf("size of efuse ID%d(0x%02X) = %d\n", i, i, efuse_size);
    }

    return HI_ERR_SUCCESS;
}

hi_void efuse_get_lock_stat(hi_void)
{
    hi_u64 lock_data;

    hi_efuse_get_lockstat(&lock_data);
    printf("lock_stat = 0x%08X ", (hi_u32)((lock_data >> 32) & 0xFFFFFFFF)); /* right shift 32bits */
    printf("%08X\n", (hi_u32)(lock_data & 0xFFFFFFFF));
}

hi_u32 efuse_usr_read(hi_void)
{
    hi_u32 ret;
    hi_u32 read_data[EFUSE_USR_RW_SAMPLE_BUFF_MAX_LEN] = {0};
    hi_u16 start_bit = 0x75C;       /* The offset address of customer_rsvd0 is 0x75C */
    hi_u16 rw_bits = 64;            /* The lenth of customer_rsvd0 is 64bits */
    hi_u16 align_size;
    hi_u8 tmp_data[9] = {0}; /* 9 bytes(72 bits) for customer_rsvd0 field, length 8-bit aligned. */
    hi_u64 first_u64;
    hi_u8 second_u8;

    hi_u8 diff_head_read = start_bit % 8; /* The start address is read in 8-bit alignment mode. */
    start_bit = start_bit - diff_head_read;
    align_size = (((rw_bits + diff_head_read) >> 3) + 1) << 3; /* 3-bit offset */

    ret = hi_efuse_usr_read(start_bit, align_size, (hi_u8 *)tmp_data);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to read EFUSE at line%d! Err code = %X\n", __LINE__, ret);
        return ret;
    }

    first_u64 = *(hi_u64 *)&tmp_data[0];
    second_u8 = *(hi_u8 *)&tmp_data[8]; /* the last u8 bit */
    /* The lower bits of the first u64 multi-read are discarded.(The diff_head_read) */
    first_u64 = first_u64 >> diff_head_read;
    /*
     * The least significant eight bits of tmp_data are shifted leftward by 64-diff_head_read bits
     * as the most significant 64 bits of tmp_data.diff_head_read)
     */
    first_u64 = first_u64 | ((hi_u64)second_u8 << (64 - diff_head_read)); /* (64 - diff_head_read)bits */
    *(hi_u64 *)read_data = first_u64;

    printf("usr_data = 0x%08X %08X\n", read_data[0], read_data[1]);

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_usr_write(hi_void)
{
    hi_u32 ret;
    hi_u32 write_data[EFUSE_USR_RW_SAMPLE_BUFF_MAX_LEN] = {
        0x0,
        0x1,
    };
    hi_u16 start_bit = 0x75C;       /* Offset address:0x75C */
    hi_u16 rw_bits = 64;            /* length:64bits */

    ret = efuse_usr_read();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_efuse_usr_write(start_bit, rw_bits, (hi_u8 *)write_data);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to write EFUSE!\n");
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_usr_lock(hi_void)
{
    hi_u32 ret;
    hi_u8  lock_data = 0x1;
    hi_u16 lock_start_bit = 0x7FD;  /* Offset address:0x7FD */
    hi_u16 lock_bits = 1;           /* length:1bit  */

    efuse_get_lock_stat();

    ret = hi_efuse_usr_write(lock_start_bit, lock_bits, &lock_data);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to lock EFUSE!\n");
        return ret;
    }

    efuse_get_lock_stat();

    return HI_ERR_SUCCESS;
}

hi_u32 sample_usr_efuse(hi_void)
{
    hi_u32 ret;

#ifdef EFUSE_WRITE_ENABLE
    ret = efuse_usr_write();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
#endif

    ret = efuse_usr_read();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

#ifdef EFUSE_LOCK_ENABLE
    ret = efuse_usr_lock();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
#endif

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_id_read(hi_void)
{
    hi_u32 ret;
    hi_u32 read_data[EFUSE_USR_RW_SAMPLE_BUFF_MAX_LEN] = {0};
    hi_efuse_idx efuse_id = HI_EFUSE_CUSTOMER_RSVD0_RW_ID;

    ret = hi_efuse_read(efuse_id, (hi_u8 *)read_data, (hi_u8)sizeof(read_data));
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to read EFUSE at line%d! Err code = %X\n", __LINE__, ret);
        return ret;
    }
    printf("id_data = 0x%08X %08X\n", read_data[0], read_data[1]);

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_id_write(hi_void)
{
    hi_u32 ret;
    hi_u32 write_data[EFUSE_USR_RW_SAMPLE_BUFF_MAX_LEN] = {
        0x1,
        0x0,
    };
    hi_efuse_idx efuse_id = HI_EFUSE_CUSTOMER_RSVD0_RW_ID;

    ret = efuse_id_read();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_efuse_write(efuse_id, (hi_u8 *)write_data);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to write EFUSE!\n");
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_id_lock(hi_void)
{
    hi_u32 ret;
    hi_efuse_lock_id lock_id = HI_EFUSE_LOCK_CUSTOMER_RSVD0_ID;
    efuse_get_lock_stat();

    ret = hi_efuse_lock(lock_id);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to lock EFUSE!\n");
        return ret;
    }

    efuse_get_lock_stat();

    return HI_ERR_SUCCESS;
}

hi_u32 sample_id_efuse(hi_void)
{
    hi_u32 ret;

#ifdef EFUSE_WRITE_ENABLE
    ret = efuse_id_write();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
#endif

    ret = efuse_id_read();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

#ifdef EFUSE_LOCK_ENABLE
    ret = efuse_id_lock();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
#endif

    return HI_ERR_SUCCESS;
}

/*
 * This demo simply shows how to use efuse interface to write, read and lock customer_rsvd0 field.
 * -note: Efuse is a one-time programmable logic. Once set, it cannot be modified.
 *        Be careful when using write and lock interfaces.
 */
hi_void efuse_demo(hi_void)
{
    hi_u32 ret;

    ret = get_efuse_id_size_test();
    if (ret != HI_ERR_SUCCESS) {
        return;
    }

    ret = sample_id_efuse();
    if (ret != HI_ERR_SUCCESS) {
        return;
    }

    ret = sample_usr_efuse();
    if (ret != HI_ERR_SUCCESS) {
        return;
    }
}
