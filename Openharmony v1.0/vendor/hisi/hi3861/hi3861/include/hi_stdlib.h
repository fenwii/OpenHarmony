/**
* @file hi_stdlib.h
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
*
* Description: A parameter is added to the security C APIs based on the standard C interface, that is, the upper
*              limit of the write operation address space to prevent out-of-bounds write.
CNcomment:安全C接口主要是基于标准C接口增加了一个参数，即写操作地址空间上限，从而防止写越界。CNend   \n
* Create: 2019-12-18
*/

/**
 * @defgroup iot_secure_c Secure C library APIs
 * @ingroup iot_secure
 */

#ifndef __HI_STDLIB_H__
#define __HI_STDLIB_H__
#include <hi_types_base.h>

HI_START_HEADER

#ifndef EOK
#define EOK 0
#endif

#ifndef errno_t
typedef int errno_t;
#endif

#ifndef size_t
typedef unsigned int size_t;
#endif

/**
* @ingroup  iot_secure_c
* @brief  Copies the source string to the destination buffer.CNcomment:复制源字符串到目的缓冲区。CNend
*
* @par 描述: Copies the source string to the destination buffer.
CNcomment:复制源字符串到目的缓冲区。CNend
*
* @attention None
*
* @param dest     [OUT] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN]  type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN]  type #const #char *, Source buffer.CNcomment:源缓冲区。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t strcpy_s(char *dest, size_t dest_max, const char *src);

/**
* @ingroup  iot_secure_c
* @brief  Copies the source string of a specified length to the destination buffer.
CNcomment:复制指定长度源字符串到目的缓冲区。CNend
*
* @par 描述:Copies the source string of a specified length to the destination buffer.
CNcomment:复制指定长度源字符串到目的缓冲区。CNend
* @attention None
*
* @param dest     [IN] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN] type #const #char *, Source buffer.CNcomment:源缓冲区。CNend
* @param count    [IN] type #size_t, Number of characters copied from the source buffer.
CNcomment:从源缓冲区中复制的字符数。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t strncpy_s(char *dest, size_t dest_max, const char *src, size_t count);

/**
* @ingroup  iot_secure_c
* @brief  Concatenates the source string to the end of the destination string.
CNcomment:将源字符串连接到目的字符串后面CNend
*
* @par 描述:Concatenates the source string to the end of the destination string.
CNcomment:将源字符串连接到目的字符串后面。CNend
* @attention None
*
* @param dest     [IN] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN] type #const #char *, Source buffer.CNcomment:源缓冲区。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t strcat_s(char *dest, size_t dest_max, const char *src);

/**
* @ingroup  iot_secure_c
* @brief  Concatenates the source string of a specified length to the end of the destination string.
CNcomment:将指定长度的源字符串连接到目的字符串后面。CNend
*
* @par 描述: Concatenates the source string of a specified length to the end of the destination string.
CNcomment:将指定长度的源字符串连接到目的字符串后面。CNend
* @attention None
*
* @param dest     [IN] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN] type #const #char *, Source buffer.CNcomment:源缓冲区。CNend
* @param count    [IN] type #size_t, Number of characters copied from the source buffer.
CNcomment:从源缓冲区连接的字符数。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t strncat_s(char *dest, size_t dest_max, const char *src, size_t count);

/**
* @ingroup  iot_secure_c
* @brief  Copies the data from the source buffer to the destination buffer.
CNcomment:复制源缓冲区的数据到目的缓冲区。CNend
*
* @par 描述: Copies the data from the source buffer to the destination buffer.
CNcomment:复制源缓冲区的数据到目的缓冲区。CNend
* @attention None
*
* @param dest     [IN] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN] type #const #char *, Source buffer.CNcomment:源缓冲区。CNend
* @param count    [IN] type #size_t, Number of characters copied from the source buffer.
CNcomment:从源缓冲区中复制的字符数。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t memcpy_s(void *dest, size_t dest_max, const void *src, size_t count);

/**
* @ingroup  iot_secure_c
* @brief  Sets the size of the destination buffer to a specific value.
CNcomment:设置目的缓冲区为特定值。CNend
*
* @par 描述: Sets the size of the destination buffer to a specific value.
CNcomment:设置目的缓冲区为特定值。CNend
* @attention None
*
* @param dest     [IN] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param c        [IN] type #const #char *, Source buffer.CNcomment:特定值。CNend
* @param count    [IN] type #size_t, Number of characters copied from the source buffer.
CNcomment:设置为特定值的字符数。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t memset_s(void *dest, size_t dest_max, int c, size_t count);

/**
* @ingroup  iot_secure_c
* @brief  Moves the data from the source buffer to the destination buffer.
CNcomment:移动源缓冲区的数据到目的缓冲区。CNend
*
* @par 描述:Moves the data from the source buffer to the destination buffer.
CNcomment:移动源缓冲区的数据到目的缓冲区。CNend
* @attention None
*
* @param dest     [IN] type #char *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #size_t, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN] type #const #char *, Source buffer.CNcomment:源缓冲区。CNend
* @param count    [IN] type #size_t, Number of characters copied from the source buffer.
CNcomment:从源缓冲区中移动的字符数。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern errno_t memmove_s(void *dest, size_t dest_max, const void *src, size_t count);

/**
* @ingroup  iot_secure_c
* @brief  Splits a string into substrings according to the specified separators.
CNcomment:将字符串按照指定的分隔符分割成子字符串。CNend
*
* @par 描述: Splits a string into substrings according to the specified separators.
CNcomment:将字符串按照指定的分隔符分割成子字符串。CNend
* @attention None
*
* @param token   [IN] type #char *。 String to be split.CNcomment:要分割的字符串。CNend
* @param delimit [IN] type #const char *。 String separator.CNcomment:字符串分隔符。CNend
* @param context [IN] type #char** 。Position information after a call to HI_strtok_s is saved.
CNcomment:保存调用HI_strtok_s后的位置信息。CNend
*
* @retval #char* Point to the next token. CNcomment:指向在token中的下一个token。CNend
* @retval #HI_NULL A specified substring is not found or an error occurs.
CNcomment:没有找到指定的子字符串或者发生错误。CNend
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern char *strtok_s(char *token, const char *delimit, char **context);

/**
* @ingroup  iot_secure_c
* @brief  Formats the data and outputs it to the destination buffer.
CNcomment:将数据格式化输出到目的缓冲区。CNend
*
* @par 描述: Formats the data and outputs it to the destination buffer.
CNcomment:将数据格式化输出到目的缓冲区。CNend
* @attention None
*
* @param dest     [OUT] type #char *。 Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN]  type #size_t。 Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param format   [IN]  type #const #char *。 Formatting control string.CNcomment:格式化控制字符串。CNend
* @param ...      [IN]  Optional parameter CNcomment:可选参数。CNend
*
* @retval #>=0 Return the number of bytes stored in dest, not counting the terminating null character.
CNcomment:返回存储在dest的字节数，不包括结束符CNend
* @retval #-1 Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern int sprintf_s(char *dest, size_t dest_max, const char *format, ...);

/**
* @ingroup  iot_secure_c
* @brief Formats the data according to a specified length and outputs the data to the destination buffer.
CNcomment:将数据按照指定长度格式化输出到目的缓冲区。CNend
*
* @par 描述: Formats the data according to a specified length and outputs the data to the destination buffer.
CNcomment:将数据按照指定长度格式化输出到目的缓冲区。CNend
* @attention None
*
* @param dest     [OUT] type #char *。 Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN]  type #size_t。 Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param count    [IN]  type #size_t。 Number of formatted characters to be output to the destination buffer.
CNcomment:要输出到目的缓冲区的格式化字符个数。CNend
* @param format   [IN]  type #const #char *。 Formatting control string.CNcomment:格式化控制字符串。CNend
* @param ...      [IN]  Optional parameter CNcomment:可选参数。CNend
*
* @retval #>=0 Return the number of bytes stored in dest, not counting the terminating null character.
CNcomment:返回存储在dest的字节数，不包括结束符CNend
* @retval #-1 Failure
*
* @par 依赖:
* @li hi_stdlib.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
extern int snprintf_s(char *dest, size_t dest_max, size_t count, const char *format, ...);

extern int memcmp(const void *str1, const void *str2, size_t n);
extern size_t strlen(const char *src);
extern int strcmp(const char *str1, const char *str2);
extern int strncmp(const char *str1, const char *str2, size_t n);

#if defined(HAVE_PCLINT_CHECK)
#define UT_CONST const
#else
#define UT_CONST
#endif

extern unsigned long strtoul(const char *nptr, char **endptr, int base);
extern UT_CONST char *strstr(const char *str1, const char *str2);
extern UT_CONST char *strchr(const char *s, int c);
extern char *strcpy(char* dest, const char *src);
extern char* strsep(char** __s_ptr, const char* __delimiter);
extern long strtol(const char *nptr, char **endptr, int base);

extern int atoi (const char *s);

extern void *memset(void *s, int ch, size_t n);
extern void* memmove(void* dst, const void* src, size_t n);
extern void* memcpy(void* dst, const void* src, size_t n);


HI_END_HEADER
#endif /* __HI_STDLIB_H__ */

