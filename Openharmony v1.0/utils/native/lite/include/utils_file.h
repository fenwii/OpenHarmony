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

/**
 * @addtogroup utils_file
 * @{
 *
 * @brief Performs operations on a file.
 *
 * This module allows you to performs file operations such as to open, close,
 * read, and write a file, and to obtain the file size.
 * The filing system varies according to the hardware platform.
 * The following limitations are imposed on a platform that
 * uses the Serial Peripheral Interface Flash Filing System (SPIFFS):
 * <ul>
 *    <li>Multi-level directories are not supported.</li>
 *    <li>A file name can have a maximum length of 32 bytes (including the end-of-text character in the string).</li>
 *    <li>A maximum of 32 files can be opened at the same time.</li>
 * </ul>
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file utils_file.h
 *
 * @brief Performs operations on a file, including to open, close, write, read, and delete a file.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef FILE_SYSTEM_API_H
#define FILE_SYSTEM_API_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Defines the offset position used by {@link UtilsFileSeek}
 * in a file to start offsetting from the file header.
 *
 */
#ifndef SEEK_SET_FS
#define SEEK_SET_FS  0
#endif

/**
 * @brief Defines the offset position used by {@link UtilsFileSeek}
 * in a file to start offsetting from the current read and write position.
 *
 */
#ifndef SEEK_CUR_FS
#define SEEK_CUR_FS  1
#endif

/**
 * @brief Defines the offset position used by {@link UtilsFileSeek}
 * in a file to start offsetting from the end of the file.
 *
 */
#ifndef SEEK_END_FS
#define SEEK_END_FS  2
#endif

/**
 * @brief Defines a flag used by{@link UtilsFileOpen} to open a file in read-only mode.
 *
 */
#ifndef O_RDONLY_FS
#define O_RDONLY_FS  00
#endif

/**
 * @brief Defines a flag used by {@link UtilsFileOpen} to open a file in write-only mode.
 *
 */
#ifndef O_WRONLY_FS
#define O_WRONLY_FS  01
#endif

/**
 * @brief Defines a flag used by {@link UtilsFileOpen} to open a file in read-and-write mode.
 *
 */
#ifndef O_RDWR_FS
#define O_RDWR_FS    02
#endif

/**
 * @brief Defines a flag used by {@link UtilsFileOpen} to create a file when the file to open does not exist.
 *
 */
#ifndef O_CREAT_FS
#define O_CREAT_FS   0100
#endif

/**
 * @brief Defines a flag used by {@link UtilsFileOpen} to check whether the file to open exists
 * when {@link O_CREAT_FS} is already set.
 *
 * If the file does not exist, a new file will be created. If the file exists, the file cannot be opened.
 *
 */
#ifndef O_EXCL_FS
#define O_EXCL_FS    0200
#endif

/**
 * @brief Defines a flag used by {@link UtilsFileOpen} to clear the file content
 * if the file exists and can be opened in write mode.
 *
 */
#ifndef O_TRUNC_FS
#define O_TRUNC_FS   01000
#endif

/**
 * @brief Defines a flag used by {@link UtilsFileOpen} to start reading or writing from the end of a file.
 *
 */
#ifndef O_APPEND_FS
#define O_APPEND_FS  02000
#endif

/**
 * @brief Opens or creates a file.
 *
 * @param path Indicates the file to open or create.
 * @param oflag Indicates the mode of opening a file. The following modes are supported.
 * oflag | Description
 * ------------|------------------------------------------------
 * O_RDONLY_FS | For details, see {@link O_RDONLY_FS}.
 * O_WRONLY_FS | For details, see {@link O_WRONLY_FS}.
 * O_RDWR_FS | For details, see {@link O_RDWR_FS}.
 * O_CREAT_FS | For details, see {@link O_CREAT_FS}.
 * O_EXCL_FS | For details, see {@link O_EXCL_FS}.
 * O_TRUNC_FS | For details, see {@link O_TRUNC_FS}.
 * O_APPEND_FS | For details, see {@link O_APPEND_FS}.
 * These modes can be used together, with each of them identified by "or".
 * @param mode Used for function compatibility. This parameter does not take effect in any scenario.
 * @return Returns the file descriptor if the file is opened or created; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileOpen(const char* path, int oflag, int mode);

/**
 * @brief Closes a file with the specified file descriptor.
 *
 * @param fd Indicates the file descriptor of the file to close.
 * @return Returns <b>0</b> if the file is closed; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileClose(int fd);

/**
 * @brief Reads a specified length of data from a file with the specified file descriptor
 * and writes the data into the buffer.
 *
 * @param fd Indicates the file descriptor of the file to read.
 * @param buf Indicates the buffer that stores the read data. This is an output parameter.
 * @param len Indicates the length of the data to read.
 * @return Returns the number of bytes of the data if the data is read; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileRead(int fd, char *buf, unsigned int len);

/**
 * @brief Writes a specified length of data into a file with the specified file descriptor.
 *
 * @param fd Indicates the file descriptor of the file where to write the data.
 * @param buf Indicates the data to write.
 * @param len Indicates the length of the data to write.
 * @return Returns the number of bytes of the data if the data is written; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileWrite(int fd, const char *buf, unsigned int len);

/**
 * @brief Deletes a specified file.
 *
 * @param path Indicates the file to delete.
 * @attention If the number of opened files reaches the upper limit (32), close any of them first.
 * Otherwise, the file cannot be deleted.
 * @return Returns <b>0</b> if the file is deleted; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileDelete(const char *path);

/**
 * @brief Obtains the file size.
 *
 * @param path Indicates the file name.
 * @param fileSize Indicates the file size. This is an output parameter.
 * @return Returns <b>0</b> if the file size is obtained; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileStat(const char *path, unsigned int *fileSize);

/**
 * @brief Adjusts the read and write position offset in a file.
 *
 * @param fd Indicates the file descriptor of the file where the read and write position offset needs adjustment.
 * @param offset Indicates the offset of the read and write position based on the <b>whence</b> parameter.
 * The value can be negative if the value of <b>whence</b> is <b>SEEK_CUR_FS</b> or <b>SEEK_END_FS</b>.
 * @param whence Indicates the start position of the offset. The following start positions are supported.
 * whence | Description
 * ------------|------------------------------------------------
 * SEEK_SET_FS | Adjusts the read and write position to the file header.
 *      ^      | Then adds the offset after the read and write position.
 * SEEK_CUR_FS | Adds the offset after the current read and write position.
 * SEEK_END_FS | Adjusts the read and write position to the end of the file.
 *      ^      | Then adds the offset after the read and write position.
 *
 * @return Returns the current read and write position if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileSeek(int fd, int offset, unsigned int whence);

/**
 * @brief Copies the source file to a target file.
 *
 * @param src Indicates the source file to copy.
 * @param dest Indicates the target file.
 * @attention If the number of opened files reaches the upper limit (32), close any two files first.
 * Otherwise, the file cannot be copied.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileCopy(const char* src, const char* dest);

/**
 * @brief Moves the source file into a target file.
 *
 * @param src Indicates the source file.
 * @param dest Indicates the target file.
 * @attention If the number of opened files reaches the upper limit (32), close any two files first.
 * Otherwise, the file cannot be moved.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int UtilsFileMove(const char* src, const char* dest);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // FILE_SYSTEM_API_H
/** @} */