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

#include "stdlib.h"
#include "stdio.h"
#include "los_config.h"
#include "mtd_partition.h"
#include "inode/inode.h"

#ifdef LOSCFG_SHELL_CMD_DEBUG
#include "shcmd.h"

#if defined(LOSCFG_FS_JFFS)
extern partition_param *g_spinorPartParam;
#endif

INT32 osShellCmdPartitionShow(INT32 argc, const CHAR **argv)
{
#if defined(LOSCFG_FS_JFFS)
    mtd_partition *node = NULL;
    const CHAR *fs = NULL;
    partition_param *param = NULL;

    if (argc != 1) {
        PRINT_ERR("partition [nand/spinor]\n");
        return -EPERM;
    } else {
        fs = argv[0];
    }
#endif

#if defined(LOSCFG_FS_JFFS)
    if (strcmp(fs, "spinor") == 0) {
        param = g_spinorPartParam;
    } else
#endif
    {
        PRINT_ERR("not supported!\n");
        return -EINVAL;
    }

#if defined(LOSCFG_FS_JFFS)
    if ((param == NULL) || (param->flash_mtd == NULL)) {
        PRINT_ERR("no partition!\n");
        return -EINVAL;
    }

    LOS_DL_LIST_FOR_EACH_ENTRY(node, &param->partition_head->node_info, mtd_partition, node_info) {
        PRINTK("%s partition num:%u, blkdev name:%s, mountpt:%s, startaddr:0x%08x, length:0x%08x\n",
            fs, node->patitionnum, node->blockdriver_name, node->mountpoint_name,
            (node->start_block * param->block_size),
            ((node->end_block - node->start_block) + 1) * param->block_size);
    }
    return ENOERR;
#endif
}

SHELLCMD_ENTRY(partition_shellcmd, CMD_TYPE_EX, "partition", XARGS, (CmdCallBackFunc)osShellCmdPartitionShow);

#endif /* LOSCFG_SHELL */
