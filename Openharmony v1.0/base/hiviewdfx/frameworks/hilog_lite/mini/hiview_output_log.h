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

#ifndef HOS_LITE_HIVIEW_OUTPUT_LOG_H
#define HOS_LITE_HIVIEW_OUTPUT_LOG_H

#include "hos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

void InitCoreLogOutput(void);
void InitLogOutput(void);
void ClearLogOutput(void);

/**
 * Output the log to file.
 * @param data HiLogContent pointer.
 * @param len log data length.
 **/
void OutputLog(const uint8 *data, uint32 len);

/**
 * Get the log file size.
 * @retval File size.
 **/
uint32 GetLogFileSize(void);

/**
 * Read the log data form the log file.
 * @param buf Read buffer.
 * @param len Read buffer size.
 * @retval The length of read data.
 **/
uint32 ReadLogFile(uint8 *buf, uint32 len);

/**
 * Formatting log content.
 * @param outStr Output string buffer.
 * @param outStrLen Maximum length of the string buffer.
 * @param pLogContent Pointer to the HiLogContent object.
 * @retval The actual length of the formatted string.
 **/
int32 LogContentFmt(char *outStr, int32 outStrLen, const uint8 *pLogContent);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HOS_LITE_HIVIEW_OUTPUT_LOG_H */
