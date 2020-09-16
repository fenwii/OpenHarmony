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

#ifndef KERNEL_CONSTANTS_H
#define KERNEL_CONSTANTS_H

/**
 * ================ DAC and Caps ================
 */
const int SHELL_UID = 2;
const int SHELL_GID = 2;


/**
 * ================ Process Manager ================
 */
const int MAX_PROCESS_GROUPS = 255;  // max number of groups a process can have
const int MAX_PROCESS_NUMBER = 63;   // max allowd process [0,63]
const int MAX_TASK_NUMBER = 128;     // max allowd task(process+thread)


/**
 * ================ IPC ================
 */
const int MAX_SIGNAL_NUMBER = 64;   // max number of allowed signal, [1,64]
const int MAX_PIPE_BUFFER = 1023;   // max size of a pipe buffer
const int MAX_PIPE_NUMBER = 32;     // max pipe number

const int MAX_MQ_NUMBER   = 1024;   // max mqueue number
const int MAX_MQ_NAME_LEN = 256;    // max mqueue name length
const int MAX_MQ_MSG_SIZE = 65530;  // max mqueue message size


/**
 * ================ FS ================
 */
const int MAX_PATH_SIZE = 256;      // max size of path string


/**
 * ================ XTS ================
 */
// top dir of test resource of kernel
#define RES_DIR_KERNEL "/test_root/kernel/"

#endif
