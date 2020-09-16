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

#ifndef KERNEL_LIBFS_H
#define KERNEL_LIBFS_H

/**
 * desc:   make a new directory
 * input:  dirname
 * output: -1 -- mkdir failed, detail info printed
 *          0 -- mkdir ok, or dirname already exists
 *          1 -- dirname already exists
 */
int MakeDir(const char *dirname);

/**
 * desc:   remove a dir, even it's not empty
 * input:  dirname
 * output: -1 -- rmdir failed, detail info printed
 *          0 -- remove ok
 */
int RemoveDir(const char *dirname);

/**
 * desc:   remove a file
 * input:  dirname
 * output: -1 -- rmdir failed, detail info printed
 *          0 -- remove ok
 */
int RemoveFile(const char *fpath);

/**
 * desc:   copy srcFile to dstFile. if dstFile exist, it will be reflashed
 * output: -1 -- copy failed, detail info printed
 *          0 -- copy ok
 */
int CopyFile(const char *srcFile, const char *dstFile);

/**
 * desc:   get current working directory
 * output: NULL   -- getcwd failed, detail info printed
 *         string -- the current working directory
 */
char* GetCurrentPath();

#endif // header
