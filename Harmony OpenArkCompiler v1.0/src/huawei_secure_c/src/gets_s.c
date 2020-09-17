/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */

#include "securecutil.h"

static void SecTrimCRLF(char *buffer, size_t len)
{
    int i;
    /* No need to determine whether integer overflow exists */
    for (i = (int)(len - 1); i >= 0 && (buffer[i] == '\r' || buffer[i] == '\n'); --i) {
        buffer[i] = '\0';
    }
    return;
}

/*
 * <FUNCTION DESCRIPTION>
 *    The gets_s function reads at most one less than the number of characters
 *    specified by destMax from the stream pointed to by stdin, into the array pointed to by buffer
 *    The line consists of all characters up to and including
 *    the first newline character ('\n'). gets_s then replaces the newline
 *    character with a null character ('\0') before returning the line.
 *    If the first character read is the end-of-file character, a null character
 *    is stored at the beginning of buffer and NULL is returned.
 *
 * <INPUT PARAMETERS>
 *    buffer                         Storage location for input string.
 *    numberOfElements       The size of the buffer.
 *
 * <OUTPUT PARAMETERS>
 *    buffer                         is updated
 *
 * <RETURN VALUE>
 *    buffer                         Successful operation
 *    NULL                           Improper parameter or read fail
 */
char *gets_s(char *buffer, size_t numberOfElements)
{
    size_t len;
#ifdef SECUREC_COMPATIBLE_WIN_FORMAT
    size_t bufferSize = ((numberOfElements == (size_t)-1) ? SECUREC_STRING_MAX_LEN : numberOfElements);
#else
    size_t bufferSize = numberOfElements;
#endif

    if (buffer == NULL || bufferSize == 0 || bufferSize > SECUREC_STRING_MAX_LEN) {
        SECUREC_ERROR_INVALID_PARAMTER("gets_s");
        return NULL;
    }

    if (fgets(buffer, (int)bufferSize, stdin) == NULL) {
        return NULL;
    }

    len = strlen(buffer);
    if (len > 0 && len < bufferSize) {
        SecTrimCRLF(buffer, len);
    }

    return buffer;
}

