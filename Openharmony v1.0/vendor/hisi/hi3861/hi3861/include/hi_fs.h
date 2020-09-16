/*
 * @file hi_fs.h
 *
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

/**
 * @defgroup iot_fs Filesystem
 * @ingroup osa
 */
#ifndef __HI_FS_H__
#define __HI_FS_H__

#include <hi_types.h>

typedef struct {
    hi_u32  size;
    hi_u32  next_offset;
    hi_char name[1];
}hi_file_list;


#define HI_FS_SEEK_SET                 (0)  /**< set file offset to offset */
#define HI_FS_SEEK_CUR                 (1)  /**< set file offset to current plus offset */
#define HI_FS_SEEK_END                 (2)  /**< set file offset to EOF plus offset */

#define HI_FS_O_RDONLY       00
#define HI_FS_O_WRONLY       01
#define HI_FS_O_RDWR         02

#define HI_FS_O_CREAT        0100
#define HI_FS_O_EXCL         0200
#define HI_FS_O_TRUNC        01000
#define HI_FS_O_APPEND       02000
#define HI_FS_O_PATH         010000000


#define HI_FS_O_SEARCH       HI_FS_O_PATH
#define HI_FS_O_ACCMODE      (HI_FS_O_RDONLY | HI_FS_O_WRONLY | HI_FS_O_RDWR | HI_FS_O_SEARCH)

/**
* @ingroup  iot_fs
* @brief Get filesystem error code.CNcomment:获取错误码。CNend
*
* @par 描述:
*           @li Returns the filesystem's most recent error code value.CNcomment:返回文件系统最近的错误代码值。CNend
*
* @attention None
* @param  None
*
* @retval filesystem error code.CNcomment:文件系统错误码。CNend
* @par 依赖:
*            @li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see hi_get_fs_error
*/
hi_s32 hi_get_fs_error(hi_void);

/**
* @ingroup  iot_fs
* @brief Set filesystem check and repair.CNcomment:设置文件系统加载时是否自动检查并修复。CNend
*
* @par 描述:
*           @li Set filesystem check and repair, default True.
CNcomment:设置文件系统加载时是否自动检查并修复，默认自动检查并修复。CNend
*
* @attention set before fs init.CNcomment:在文件系统初始化之前调用。CNend
* @param  check      [IN] type  #hi_bool，whether check and repair when filesystem mount.
CNcomment:是否自动检查并修复。CNend
*
* @retval None
* @par 依赖:
*            @li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see hi_get_fs_check
*/
hi_void hi_set_fs_check(hi_bool check);

/**
* @ingroup  iot_fs
* @brief Get filesystem check and repair.CNcomment:获取文件系统加载时是否自动检查并修复。CNend
*
* @par 描述:
*           @li Get filesystem check and repair, default True.
CNcomment:获取文件系统加载时是否自动检查并修复，默认自动检查并修复。CNend
*
* @attention None
* @param  None
*
* @retval #HI_TRUE   auto check and repair when filesystem mount.
* @retval #HI_FALSE  not check and repair when filesystem mount.
* @par 依赖:
*            @li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see hi_set_fs_check
*/
hi_bool hi_get_fs_check(hi_void);

/**
* @ingroup  iot_fs
* @brief Initialize virtual filesystem.CNcomment:初始化虚拟文件系统。CNend
*
* @par 描述:
*           @li Initialize virtual file system configuration related parameters.
             CNcomment:初始化虚拟文件系统配置相关参数。CNend
*           @li Mount partition to virtual file system work buffer.CNcomment:挂载分区到虚拟文件系统工作缓冲区。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_fs.h：describes the file system APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see hi_fs_init
*/
hi_void hi_fs_init(hi_void);

/**
* @ingroup  iot_fs
* @brief  Open or create a file.CNcomment:打开或创建文件。 CNend
*
* @par 描述:
*         Open or create a file.CNcomment:打开或创建指定的文件。CNend
*
* @attention The path length is less than 31 bytes, excluding the terminator.
             Maximum support for opening 32 files at the same time.

* @param  path      [IN] type  #const hi_char*，file name  CNcomment:要打开或创建的目标文件。CNend
*
* @param flags      [IN] type #hi_u32,The flag combination is as follows:
*             HI_FS_O_RDONLY:Open file as read-only.CNcomment:以只读的方式打开文件。CNend
*             HI_FS_O_WRONLY:Open the file in write-only mode.CNcomment:以只写的方式打开文件。CNend
*             HI_FS_O_RDWR:Open file in read-write mode.CNcomment:以读写的方式打开文件。CNend
*             HI_FS_O_CREAT:If the file you want to open does not exist, the file will be created automatically.
                  CNcomment:如果要打开的文件不存在则自动建立该文件。CNend
*             HI_FS_O_EXCL:If HI_FS_O_CREAT is also set, this command will check to see if the file exists.
                  If the file does not exist, create the file, otherwise it will cause a file error to open.
                  CNcomment:如果HI_FS_O_CREAT也被设置，此指令会去检查文件是否存在。
                            文件若不存在则建立该文件，否则将导致打开文件错误。CNend
*             HI_FS_O_TRUNC:If the file exists and is opened in write mode, this flag will make the file length
                            clear to 0, and the data originally stored in the file will disappear.
              CNcomment:若文件存在并且以可写的模式打开时，此标志会令文件长度清为0，而原来存于该文件的数据也会消失。CNend
*             HI_FS_O_APPEND:When reading and writing a file, it will start moving from the end of the file, that is,
                              the written data will be added to the file in an additional way.
                   CNcomment:当读写文件时会从文件尾开始移动，也就是所写入的数据会以附加的方式加入到文件后面。CNend
*             CNcomment:打开文件时，可以传入多个参数选项。CNend
*
* @retval #>0     Success. Return file descriptor
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_open(const hi_char* path, hi_u32 flags);

/**
* @ingroup  iot_fs
* @brief  Close an open file.CNcomment:关闭已经打开的文件。 CNend
*
* @par 描述:
*         Close an open file.CNcomment:关闭一个已经打开的文件。CNend
*
* @attention None
* @param  fd      [IN] type  #hi_s32，file descriptor  CNcomment:需要关闭的文件描述符。CNend
*
*
* @retval #0     Success.
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_close(hi_s32 fd);

/**
* @ingroup  iot_fs
* @brief  Read file data of the specified size:从文件中，读取指定大小的文件数据。CNend
*
* @par 描述:
*         Read file data of the specified size:从文件中，读取指定大小的文件数据。CNend
*
* @attention None
* @param  fd       [IN] type  #hi_s32，file descriptor  CNcomment:需要读文件的文件描述符。CNend
* @param  buf      [OUT] type #hi_char*，save read data buffer  CNcomment:保存读数据缓冲区。CNend
* @param  len      [IN] type  #hi_u32，The number of bytes requested to be read
                              CNcomment:需要读取数据的长度。CNend
*
*
* @retval #>=0     Success. Returns the number of bytes read, if it returns 0, it means that the end of the file
                   has been reached or there is no data to be read.
                   CNcomment:返回读取的字节数，如果返回0，表示已到达文件尾或无可读取的数据。CNend
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_read(hi_s32 fd, hi_char* buf, hi_u32 len);

/**
* @ingroup  iot_fs
* @brief  Write file data of the specified size:向文件中，写入指定大小的文件数据。CNend
*
* @par 描述:
*         Write file data of the specified size:向文件中，写入指定大小的文件数据。CNend
*
* @attention None
* @param  fd      [IN] type  #hi_s32，file descriptor  CNcomment:需要写文件的文件描述符。CNend
* @param  buf     [IN] type  #hi_char*，Store data that needs to be written to a file.
                             CNcomment:存放需要写入文件的数据。CNend
* @param  len     [IN] type  #hi_u32，The number of bytes requested to be write  CNcomment:需要写入数据的长度。CNend
*
*
* @retval #>=0     Success. Returns the number of bytes actually written, if it returns 0, it means nothing to do.
                   reached or there is no data to be read.
                   CNcomment:返回实际写入的字节数，如果返回0，表示什么也没有做。CNend
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_write(hi_s32 fd, const hi_char* buf, hi_u32 len);

/**
* @ingroup  iot_fs
* @brief  Delete a file.CNcomment:删除指定的文件。 CNend
*
* @par 描述:
*         Delete a file.CNcomment:删除指定的文件。CNend
*
* @attention If the number of file descriptors currently open has reached the upper limit (32),
*            then one of the file descriptors must be closed, otherwise the file will not be deleted.
*            CNcomment:如果当前已经打开的文件描述符数已达上限（32个），
*                      那么必须要关闭其中一个文件描述符，否则文件将不能被删除。CNend
* @attention The path length is less than 31 bytes, excluding the terminator.
*
* @param  path      [IN] type  #const hi_char*，file name  CNcomment:要删除的目标文件。CNend
*
*
* @retval #0     Success.
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_unlink(const hi_char *path);

/**
* @ingroup  iot_fs
* @brief  Relocate read/write file offsets.CNcomment:重新定位文件的读/写偏移量。 CNend
*
* @par 描述:
*         Relocate read/write file offsets.CNcomment:重新定位文件的读/写偏移量。 CNend
*
* @attention whence is one of the following:
             SEEK_SET Point the read and write position to the file header and then increase the offset amount.
                      CNcomment:将读写位置指向文件头后再增加offset个位移量。CNend
             SEEK_CUR Increase the offset by the current read and write position.
                      CNcomment:以目前的读写位置往后增加offset个位移量。 CNend
             SEEK_END Point the read and write position to the end of the file and then increase the offset amount,
                      only support offset values can only be negative.
                      CNcomment:将读写位置指向文件尾后再增加offset个位移量，只支持offset的值为负数。CNend
             When the whennce value is SEEK_CUR or SEEK_END, the parameter offet allows
                      the occurrence of a negative value.
                      CNcomment:当whence 值为SEEK_CUR 或SEEK_END时，参数offet允许负值的出现。CNend

* @param  fd      [IN] type  #hi_s32，file descriptor  CNcomment:需要重新定位读/写偏移量的文件描述符。CNend
* @param  offs    [IN] type  #hi_s32，Move the number of displacements of the read/write position
*                  according to the parameter whence  CNcomment:根据参数whence来移动读写位置的位移数。CNend
* @param  whence  [IN] type  #hi_u32，Read / write file offset. CNcomment:读/写文件偏移。CNend
*
* @retval #>=0    Success. Returns the current read and write position,
*                          which is how many bytes from the beginning of the file
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_lseek(hi_s32 fd, hi_s32 offs, hi_u32 whence);

/**
* @ingroup  iot_fs
* @brief  Relocate Enumerate all files in the directory, the file system does not support multi-level directories.
*         CNcomment:枚举目录下的所有文件，文件系统不支持多级目录。 CNend
*
* @par 描述:
*         Relocate Enumerate all files in the directory, the file system does not support multi-level directories.
*         CNcomment:枚举目录下的所有文件，文件系统不支持多级目录。CNend
*
* @attention
*
* @param  buf      [OUT] type  #hi_char**,Buf stores information about all files and is released by the user.
*         CNcomment:buf中存放所有文件的信息，由用户释放。CNend
*
* @retval #>=0     Success.
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_enum_file(hi_char** buf);

/**
* @ingroup  iot_fs
* @brief  Relocate Get file size. CNcomment:获取指定文件的大小。 CNend
*
* @par 描述:
*         Relocate Get file size. CNcomment:获取指定文件的大小。CNend
*
* @attention
*
* @param  file_name      [IN] type  #const hi_char*,file name  CNcomment:文件名。CNend
* @param  file_size      [OUT] type  #hi_u32*,file size. CNcomment:返回文件的大小。CNend
*
* @retval #>=0     Success.
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_stat(const hi_char *file_name, hi_u32* file_size);
/**
* @ingroup  iot_fs
* @brief  Relocate Get file size. CNcomment:获取指定文件的大小。 CNend
*
* @par 描述:
*         Relocate Get file size. CNcomment:获取指定文件的大小。CNend
*
* @attention
*
* @param  fd      [IN] type  #hi_s32，file descriptor  CNcomment:文件描述符。CNend
* @param  file_size      [OUT] type  #hi_u32*,file size. CNcomment:返回文件的大小。CNend
*
* @retval #>=0     Success.
* @retval #-1     Failure. For details,Get error code by hi_get_fs_error.
* @par 依赖:
@li hi_fs.h：describes the filesystem APIs.CNcomment:文件用于描述文件系统相关接口。CNend
* @see  hi_open
*/
hi_s32 hi_fstat(hi_s32 fd, hi_u32 *file_size);
#endif

