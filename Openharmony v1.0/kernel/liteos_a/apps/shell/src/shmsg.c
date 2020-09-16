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
#include "unistd.h"
#include "sys/prctl.h"
#include "sys/ioctl.h"
#include "syscall.h"
#include "sys/wait.h"
#include "pthread.h"
#include "securec.h"
#include "shmsg.h"
#include "shell_pri.h"
#include "shcmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


char *GetCmdline(ShellCB *shellCB)
{
    CmdKeyLink *cmdkey = shellCB->cmdKeyLink;
    CmdKeyLink *cmdNode = NULL;

    (void)pthread_mutex_lock(&shellCB->keyMutex);
    if ((cmdkey == NULL) || SH_ListEmpty(&cmdkey->list)) {
        (void)pthread_mutex_unlock(&shellCB->keyMutex);
        return NULL;
    }

    cmdNode = SH_LIST_ENTRY(cmdkey->list.pstNext, CmdKeyLink, list);
    SH_ListDelete(&(cmdNode->list));
    (void)pthread_mutex_unlock(&shellCB->keyMutex);

    return cmdNode->cmdString;
}

static void ShellSaveHistoryCmd(char *string, ShellCB *shellCB)
{
    CmdKeyLink *cmdHistory = shellCB->cmdHistoryKeyLink;
    CmdKeyLink *cmdkey = SH_LIST_ENTRY(string, CmdKeyLink, cmdString);
    CmdKeyLink *cmdNxt = NULL;

    if ((string == NULL) || (*string == '\n') || (strlen(string) == 0)) {
        return;
    }

    (void)pthread_mutex_lock(&shellCB->historyMutex);
    if (cmdHistory->count != 0) {
        cmdNxt = SH_LIST_ENTRY(cmdHistory->list.pstPrev, CmdKeyLink, list);
        if (strcmp(string, cmdNxt->cmdString) == 0) {
            free((void *)cmdkey);
            (void)pthread_mutex_unlock(&shellCB->historyMutex);
            return;
        }
    }

    if (cmdHistory->count == CMD_HISTORY_LEN) {
        cmdNxt = SH_LIST_ENTRY(cmdHistory->list.pstNext, CmdKeyLink, list);
        SH_ListDelete(&(cmdNxt->list));
        SH_ListTailInsert(&(cmdHistory->list), &(cmdkey->list));
        free((void *)cmdNxt);
        (void)pthread_mutex_unlock(&shellCB->historyMutex);
        return;
    }

    SH_ListTailInsert(&(cmdHistory->list), &(cmdkey->list));
    cmdHistory->count++;

    (void)pthread_mutex_unlock(&shellCB->historyMutex);
    return;
}

int ShellPend(ShellCB *shellCB)
{
    if (shellCB == NULL) {
        return SH_NOK;
    }

    return sem_wait(&shellCB->shellSem);
}

int ShellNotify(ShellCB *shellCB)
{
    if (shellCB == NULL) {
        return SH_NOK;
    }

    return sem_post(&shellCB->shellSem);
}

enum {
    STAT_NOMAL_KEY,
    STAT_ESC_KEY,
    STAT_MULTI_KEY
};

static int ShellCmdLineCheckUDRL(const char ch, ShellCB *shellCB)
{
    int ret = SH_OK;
    if (ch == 0x1b) { /* 0x1b: ESC */
        shellCB->shellKeyType = STAT_ESC_KEY;
        return ret;
    } else if (ch == 0x5b) { /* 0x5b: first Key combination */
        if (shellCB->shellKeyType == STAT_ESC_KEY) {
            shellCB->shellKeyType = STAT_MULTI_KEY;
            return ret;
        }
    } else if (ch == 0x41) { /* up */
        if (shellCB->shellKeyType == STAT_MULTI_KEY) {
            OsShellHistoryShow(CMD_KEY_UP, shellCB);
            shellCB->shellKeyType = STAT_NOMAL_KEY;
            return ret;
        }
    } else if (ch == 0x42) { /* down */
        if (shellCB->shellKeyType == STAT_MULTI_KEY) {
            shellCB->shellKeyType = STAT_NOMAL_KEY;
            OsShellHistoryShow(CMD_KEY_DOWN, shellCB);
            return ret;
        }
    } else if (ch == 0x43) { /* right */
        if (shellCB->shellKeyType == STAT_MULTI_KEY) {
            shellCB->shellKeyType = STAT_NOMAL_KEY;
            return ret;
        }
    } else if (ch == 0x44) { /* left */
        if (shellCB->shellKeyType == STAT_MULTI_KEY) {
            shellCB->shellKeyType = STAT_NOMAL_KEY;
            return ret;
        }
    }
    return SH_NOK;
}

void ShellTaskNotify(ShellCB *shellCB)
{
    int ret;

    (void)pthread_mutex_lock(&shellCB->keyMutex);
    OsShellCmdPush(shellCB->shellBuf, shellCB->cmdKeyLink);
    (void)pthread_mutex_unlock(&shellCB->keyMutex);

    ret = ShellNotify(shellCB);
    if (ret != SH_OK) {
        printf("command execute failed, \"%s\"", shellCB->shellBuf);
    }
}

void ParseEnterKey(OutputFunc outputFunc, ShellCB *shellCB)
{
    if ((shellCB == NULL) || (outputFunc == NULL)) {
        return;
    }

    if (shellCB->shellBufOffset == 0) {
        shellCB->shellBuf[shellCB->shellBufOffset] = '\n';
        shellCB->shellBuf[shellCB->shellBufOffset + 1] = '\0';
        goto NOTIFY;
    }

    if (shellCB->shellBufOffset <= (SHOW_MAX_LEN - 1)) {
        shellCB->shellBuf[shellCB->shellBufOffset] = '\0';
    }
NOTIFY:
    outputFunc("\n");
    shellCB->shellBufOffset = 0;
    ShellTaskNotify(shellCB);
}

void ParseDeleteKey(OutputFunc outputFunc, ShellCB *shellCB)
{
    if ((shellCB == NULL) || (outputFunc == NULL)) {
        return;
    }

    if ((shellCB->shellBufOffset > 0) && (shellCB->shellBufOffset <= (SHOW_MAX_LEN - 1))) {
        shellCB->shellBuf[shellCB->shellBufOffset - 1] = '\0';
        shellCB->shellBufOffset--;
        outputFunc("\b \b");
    }
}

void ParseTabKey(OutputFunc outputFunc, ShellCB *shellCB)
{
    int ret;

    if ((shellCB == NULL) || (outputFunc == NULL)) {
        return;
    }

    if ((shellCB->shellBufOffset > 0) && (shellCB->shellBufOffset < (SHOW_MAX_LEN - 1))) {
        ret = OsTabCompletion(shellCB->shellBuf, &shellCB->shellBufOffset);
        if (ret > 1) {
            outputFunc(SHELL_PROMPT"%s", shellCB->shellBuf);
        }
    }
}

void ParseNormalChar(char ch, OutputFunc outputFunc, ShellCB *shellCB)
{
    if ((shellCB == NULL) || (outputFunc == NULL)) {
        return;
    }

    if ((ch != '\0') && (shellCB->shellBufOffset < (SHOW_MAX_LEN - 1))) {
        shellCB->shellBuf[shellCB->shellBufOffset] = ch;
        shellCB->shellBufOffset++;
        outputFunc("%c", ch);
    }

    shellCB->shellKeyType = STAT_NOMAL_KEY;
}

void ShellCmdLineParse(char c, OutputFunc outputFunc, ShellCB *shellCB)
{
    const char ch = c;
    int ret;

    if ((shellCB->shellBufOffset == 0) && (ch != '\n') && (ch != '\0')) {
        (void)memset_s(shellCB->shellBuf, SHOW_MAX_LEN, 0, SHOW_MAX_LEN);
    }

    switch (ch) {
        case '\r':
        case '\n': /* enter */
            ParseEnterKey(outputFunc, shellCB);
            break;
        case '\b': /* backspace */
        case 0x7F: /* delete(0x7F) */
            ParseDeleteKey(outputFunc, shellCB);
            break;
        case '\t': /* tab */
            ParseTabKey(outputFunc, shellCB);
            break;
        default:
            /* parse the up/down/right/left key */
            ret = ShellCmdLineCheckUDRL(ch, shellCB);
            if (ret == SH_OK) {
                return;
            }
            ParseNormalChar(ch, outputFunc, shellCB);
            break;
    }

    return;
}

unsigned int ShellMsgNameGet(CmdParsed *cmdParsed, const char *cmdType)
{
    (void)cmdParsed;
    (void)cmdType;
    return SH_ERROR;
}

char *GetCmdName(const char *cmdline, unsigned int len)
{
    unsigned int loop;
    const char *tmpStr = NULL;
    bool quotes = FALSE;
    char *cmdName = NULL;
    if (cmdline == NULL) {
        return NULL;
    }

    cmdName = (char *)malloc(len + 1);
    if (cmdName == NULL) {
        printf("malloc failure in %s[%d]\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    /* Scan the 'cmdline' string for command */
    /* Notice: Command string must not have any special name */
    for (tmpStr = cmdline, loop = 0; (*tmpStr != '\0') && (loop < len); ) {
        /* If reach a double quotes, switch the quotes matching status */
        if (*tmpStr == '\"') {
            SWITCH_QUOTES_STATUS(quotes);
            /* Ignore the double quote charactor itself */
            tmpStr++;
            continue;
        }
        /* If detected a space which the quotes matching status is false */
        /* which said has detected the first space for seperator, finish this scan operation */
        if ((*tmpStr == ' ') && (QUOTES_STATUS_CLOSE(quotes))) {
            break;
        }
        cmdName[loop] = *tmpStr++;
        loop++;
    }
    cmdName[loop] = '\0';

    return cmdName;
}

static void DoCmdExec(const char *cmdName, const char *cmdline, unsigned int len, const CmdParsed *cmdParsed)
{
    int ret;
    pid_t forkPid;

    if (strncmp(cmdline, SHELL_EXEC_COMMAND, SHELL_EXEC_COMMAND_BYTES) == 0) {
        forkPid = fork();
        if (forkPid < 0) {
            printf("Faild to fork from shell\n");
            return;
        } else if (forkPid == 0) {
            ret = setpgrp();
            if (ret == -1) {
                exit(1);
            }

            ret = execve((const char *)cmdParsed->paramArray[0], (char * const *)cmdParsed->paramArray, NULL);
            if (ret == -1) {
                perror("execve");
                exit(-1);
            }
        }
    } else {
        (void)syscall(__NR_shellexec, cmdName, cmdline);
    }
}

static void ParseAndExecCmdline(CmdParsed *cmdParsed, const char *cmdline, unsigned int len)
{
    int i;
    unsigned int ret;
    char shellWorkingDirectory[PATH_MAX + 1] = { 0 };
    char *cmdlineOrigin = NULL;
    char *cmdName = NULL;

    cmdlineOrigin = strdup(cmdline);
    if (cmdlineOrigin == NULL) {
        printf("malloc failure in %s[%d]\n", __FUNCTION__, __LINE__);
        return;
    }

    cmdName = GetCmdName(cmdline, len);
    if (cmdName == NULL) {
        free(cmdlineOrigin);
        printf("malloc failure in %s[%d]\n", __FUNCTION__, __LINE__);
        return;
    }

    ret = OsCmdParse((char *)cmdline, cmdParsed);
    if (ret != SH_OK) {
        printf("cmd parse failure in %s[%d]\n", __FUNCTION__, __LINE__);
        goto OUT;
    }

    DoCmdExec(cmdName, cmdlineOrigin, len, cmdParsed);

    if (getcwd(shellWorkingDirectory, PATH_MAX) != NULL) {
        (void)OsShellSetWorkingDirtectory(shellWorkingDirectory, (PATH_MAX + 1));
    }

OUT:
    for (i = 0; i < cmdParsed->paramCnt; i++) {
        if (cmdParsed->paramArray[i] != NULL) {
            free(cmdParsed->paramArray[i]);
            cmdParsed->paramArray[i] = NULL;
        }
    }
    free(cmdName);
    free(cmdlineOrigin);
}

unsigned int PreHandleCmdline(const char *input, char **output, unsigned int *outputlen)
{
    unsigned int shiftLen, execLen, newLen;
    unsigned int removeLen = strlen("./"); /* "./" needs to be removed if it exists */
    unsigned int ret;
    char *newCmd = NULL;
    char *execCmd = SHELL_EXEC_COMMAND;
    const char *cmdBuf = input;
    unsigned int cmdBufLen = strlen(cmdBuf);
    char *shiftStr = (char *)malloc(cmdBufLen + 1);
    errno_t err;

    if (shiftStr == NULL) {
        printf("malloc failure in %s[%d]\n", __FUNCTION__, __LINE__);
        return SH_NOK;
    }
    (void)memset_s(shiftStr, cmdBufLen + 1, 0, cmdBufLen + 1);

    /* Call function 'OsCmdKeyShift' to squeeze and clear useless or overmuch space if string buffer */
    ret = OsCmdKeyShift(cmdBuf, shiftStr, cmdBufLen + 1);
    shiftLen = strlen(shiftStr);
    if ((ret != SH_OK) || (shiftLen == 0)) {
        ret = SH_NOK;
        goto END_FREE_SHIFTSTR;
    }
    *output = shiftStr;
    *outputlen = shiftLen;

    /* Check and parse "./", located at the first two charaters of the cmd */
    if ((shiftLen > removeLen) && (shiftStr[0] == '.') && (shiftStr[1] == '/')) {
        execLen = strlen(execCmd);
        newLen = execLen + shiftLen - removeLen; /* i.e., newLen - execLen == shiftLen - removeLen */
        newCmd = (char *)malloc(newLen + 1);
        if (newCmd == NULL) {
            ret = SH_NOK;
            printf("malloc failure in %s[%d]\n", __FUNCTION__, __LINE__);
            goto END_FREE_SHIFTSTR;
        }

        err = memcpy_s(newCmd, newLen, execCmd, execLen);
        if (err != EOK) {
            printf("memcpy_s failure in %s[%d]\n", __FUNCTION__, __LINE__);
            ret = SH_NOK;
            goto END_FREE_NEWCMD;
        }

        err = memcpy_s(newCmd + execLen, newLen - execLen, shiftStr + removeLen, shiftLen - removeLen);
        if (err != EOK) {
            printf("memcpy_s failure in %s[%d]\n", __FUNCTION__, __LINE__);
            ret = SH_NOK;
            goto END_FREE_NEWCMD;
        }
        newCmd[newLen] = '\0';

        *output = newCmd;
        *outputlen = newLen;
        ret = SH_OK;
        goto END_FREE_SHIFTSTR;
    } else {
        ret = SH_OK;
        goto END;
    }
END_FREE_NEWCMD:
    free(newCmd);
END_FREE_SHIFTSTR:
    free(shiftStr);
END:
    return ret;
}

static void ExecCmdline(const char *cmdline)
{
    unsigned int ret;
    char *output = NULL;
    unsigned int outputlen;
    CmdParsed cmdParsed;

    if (cmdline == NULL) {
        return;
    }

    /* strip out unnecessary characters */
    ret = PreHandleCmdline(cmdline, &output, &outputlen);
    if (ret == SH_NOK) {
        return;
    }

    (void)memset_s(&cmdParsed, sizeof(CmdParsed), 0, sizeof(CmdParsed));
    ParseAndExecCmdline(&cmdParsed, output, outputlen);
    free(output);
}

void RecycleZombieChild(void)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        continue;
    }
}

static void ShellCmdProcess(ShellCB *shellCB)
{
    char *buf = NULL;
    while (1) {
        /* recycle zombine child process */
        RecycleZombieChild();
        buf = GetCmdline(shellCB);
        if (buf == NULL) {
            break;
        }

        ExecCmdline(buf);
        ShellSaveHistoryCmd(buf, shellCB);
        shellCB->cmdMaskKeyLink = shellCB->cmdHistoryKeyLink;
        printf(SHELL_PROMPT);
    }
}

void *ShellTask(void *argv)
{
    int ret;
    ShellCB *shellCB = (ShellCB *)argv;

    if (shellCB == NULL) {
        return NULL;
    }

    ret = prctl(PR_SET_NAME, "ShellTask");
    if (ret != SH_OK) {
        return NULL;
    }

    printf(SHELL_PROMPT);
    while (1) {
        ret = ShellPend(shellCB);
        if (ret == SH_OK) {
            ShellCmdProcess(shellCB);
        } else if (ret != SH_OK) {
            break;
        }
    }

    return NULL;
}

int ShellTaskInit(ShellCB *shellCB)
{
    unsigned int ret;
    size_t stackSize = SHELL_TASK_STACKSIZE;
    void *arg = NULL;
    pthread_attr_t attr;

    if (shellCB == NULL) {
        return SH_NOK;
    }

    ret = pthread_attr_init(&attr);
    if (ret != SH_OK) {
        return SH_NOK;
    }

    pthread_attr_setstacksize(&attr, stackSize);
    arg = (void *)shellCB;
    ret = pthread_create(&shellCB->shellTaskHandle, &attr, &ShellTask, arg);
    if (ret != SH_OK) {
        return SH_NOK;
    }

    return ret;
}

static int ShellKernelReg(unsigned int shellHandle)
{
    return ioctl(0, CONSOLE_CONTROL_REG_USERTASK, shellHandle);
}

void *ShellEntry(void *argv)
{
    char ch;
    int ret;
    int n;
    pid_t tid = syscall(__NR_gettid);
    ShellCB *shellCB = (ShellCB *)argv;

    if (shellCB == NULL) {
        return NULL;
    }

    (void)memset_s(shellCB->shellBuf, SHOW_MAX_LEN, 0, SHOW_MAX_LEN);

    ret = prctl(PR_SET_NAME, "ShellEntry");
    if (ret != SH_OK) {
        return NULL;
    }

    ret = ShellKernelReg((int)tid);
    if (ret != 0) {
        printf("another shell is already running!\n");
        exit(-1);
    }

    while (1) {
        /* is console ready for shell ? */
        if (ret != SH_OK)
            break;

        n = read(0, &ch, 1);
        if (n == 1) {
            ShellCmdLineParse(ch, (OutputFunc)printf, shellCB);
        }
    }
    return NULL;
}

int ShellEntryInit(ShellCB *shellCB)
{
    int ret;
    size_t stackSize = SHELL_ENTRY_STACKSIZE;
    void *arg = NULL;
    pthread_attr_t attr;

    if (shellCB == NULL) {
        return SH_NOK;
    }

    ret = pthread_attr_init(&attr);
    if (ret != SH_OK) {
        return SH_NOK;
    }

    pthread_attr_setstacksize(&attr, stackSize);
    arg = (void *)shellCB;
    ret = pthread_create(&shellCB->shellEntryHandle, &attr, &ShellEntry, arg);
    if (ret != SH_OK) {
        return SH_NOK;
    }

    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
