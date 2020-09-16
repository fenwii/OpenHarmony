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

#include "errno.h"
#include "los_process_pri.h"
#ifdef LOSCFG_SHELL
#include "shcmd.h"
#include "shmsg.h"
#endif
#include "sys/utsname.h"
#include "user_copy.h"
#include "los_strncpy_from_user.h"
#include "capability_type.h"
#include "capability_api.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

int SysUname(struct utsname *name)
{
    int ret;
    struct utsname tmpName;
    ret = LOS_ArchCopyFromUser(&tmpName, name, sizeof(struct utsname));
    if (ret != 0) {
        return -EFAULT;
    }
    ret = uname(&tmpName);
    if (ret < 0) {
        return ret;
    }
    ret = LOS_ArchCopyToUser(name, &tmpName, sizeof(struct utsname));
    if (ret != 0) {
        return -EFAULT;
    }
    return ret;
}

#ifdef LOSCFG_SHELL
int SysShellExec(const char *msgName, const char *cmdString)
{
    int ret;
    unsigned int uintRet;
    errno_t err;
    CmdParsed cmdParsed;
    char msgNameDup[CMD_KEY_LEN + 1] = { 0 };
    char cmdStringDup[CMD_MAX_LEN + 1] = { 0 };

    if (!IsCapPermit(CAP_SHELL_EXEC)) {
        return -EPERM;
    }

    ret = LOS_StrncpyFromUser(msgNameDup, msgName, CMD_KEY_LEN + 1);
    if (ret < 0) {
        return -EFAULT;
    } else if (ret > CMD_KEY_LEN) {
        return -ENAMETOOLONG;
    }

    ret = LOS_StrncpyFromUser(cmdStringDup, cmdString, CMD_MAX_LEN + 1);
    if (ret < 0) {
        return -EFAULT;
    } else if (ret > CMD_MAX_LEN) {
        return -ENAMETOOLONG;
    }

    err = memset_s(&cmdParsed, sizeof(CmdParsed), 0, sizeof(CmdParsed));
    if (err != EOK) {
        return -EFAULT;
    }

    uintRet = ShellMsgTypeGet(&cmdParsed, msgNameDup);
    if (uintRet != LOS_OK) {
        PRINTK("%s:command not found\n", msgNameDup);
        return -EFAULT;
    } else {
        (void)OsCmdExec(&cmdParsed, (char *)cmdStringDup);
    }

    return 0;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
