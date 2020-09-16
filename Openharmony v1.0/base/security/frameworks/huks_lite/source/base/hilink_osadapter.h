/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HILINK_OSADAPTER_H
#define HILINK_OSADAPTER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HILINK_OK
#define HILINK_OK 0
#endif
#ifndef HILINK_ERROR
#define HILINK_ERROR (-1)
#endif
#define IP_LIST_LEN    40

typedef void* hilink_mutex_t;

typedef enum {
    NW_DISCONNECTED = 0, /* 网络连接断开 */
    NW_CONNECTED    = 1  /* 网络已连接 */
} network_state_t;

typedef enum {
    HILINK_SOCKET_READABLE = 1,
    HILINK_SOCKET_WRITEABLE = 2,
    HILINK_SOCKET_EXCEPTION = 4
} HiLinkSocketState;

/* HiLink Socket错误码 */
typedef enum {
    HILINK_SOCKET_NO_ERROR               = 0,
    HILINK_SOCKET_NULL_PTR               = -1,
    HILINK_SOCKET_CREAT_UDP_FD_FAILED    = -2,
    HILINK_SOCKET_SEND_UDP_PACKET_FAILED = -3,
    HILINK_SOCKET_READ_UDP_PACKET_FAILED = -4,
    HILINK_SOCKET_TCP_CONNECTING         = -5,
    HILINK_SOCKET_TCP_CONNECT_FAILED     = -6,
    HILINK_SOCKET_SEND_TCP_PACKET_FAILED = -7,
    HILINK_SOCKET_READ_TCP_PACKET_FAILED = -8,
    HILINK_SOCKET_REMOVE_UDP_FD_FAILED   = -9,
    HILINK_SOCKET_SELECT_TIMEOUT         = -10,
    HILINK_SOCKET_SELECT_ERROR           = -11
} hilink_socket_error_t;

/*
 * 获取远端主机名
 * 返回0-成功, 其他-失败
 */
int hilink_gethostbyname(const char *hostname, char ipList[][IP_LIST_LEN], int num);
/*
 * 获取系统时间
 * 返回0成功，返回其他失败
 */
int hilink_gettime(unsigned long *ms);

/*
 * 计算字符串的长度
 * 注意：
 *    1）遇到字符串中的'\0'即停止计算长度
 *    2）src字符串须保证以'\0'结尾
 */
unsigned int hilink_strlen(const char *src);

/*
 * 比较两个字符串str1和str2
 * 返回0表示str1和str2相等, 小于0表示str1 小于 str2, 返回大于0表示str1 大于 str2
 */
int hilink_strncmp(const char *str1, const char *str2, unsigned int len);

/*
 * 在字符串str中查找字符ch
 * 返回NULL表示没有查找到字符, 非NULL表示指向ch的指针
 */
char *hilink_strchr(const char *str, int ch);

/*
 * 在字符串str中逆向查找字符ch
 * 返回NULL表示没有查找到字符, 非NULL表示指向ch的指针
 */
char *hilink_strrchr(const char *str, char ch);

/*
 * 把字符串转换成int整形数字
 * 返回int整形数字
 */
int hilink_atoi(const char *str);

/*
 * 短整形主机字节序转网络字节序
 * 返回网络字节序数字
 */
unsigned short hilink_htons(unsigned short hs);

/*
 * 短整形网络字节序转主机字节序
 * 返回主机字节序数字
 */
unsigned short hilink_ntohs(unsigned short ns);

/*
 * 将字符串形式的json数据解析为json结构体类型的数据
 * 返回NULL-解析失败,非NULL-解析成功，返回值为json结构体指针
 */
void *hilink_json_parse(const char *value);

/*
 * 获取json结构体中的字符串value
 * 返回NULL-获取失败,非NULL-获取成功，返回值为字符串value首地址
 */
char *hilink_json_get_string_value(const void *object, const char *name, unsigned int *len);

/*
 * 获取json结构体中的数值value
 * 返回0-成功,-1-失败
 */
int hilink_json_get_number_value(const void *object, const char *name, int *value);

/*
 * 获取json结构体中的object
 * 返回NULL-解析失败,非NULL-解析成功，返回值为json object结构体指针
 */
void *hilink_json_get_object(const void *object, const char *name);

/*
 * 获取json结构体中的array元组
 * 返回NULL-解析失败, 非NULL-解析成功，返回值为json object结构体指针
 */
void *hilink_json_get_arrayitem(const void *array, int item);

/*
 * 获取json结构体中的array的大小
 * 返回元组数量
 */
int hilink_json_get_arraysize(const void *array);

/* 释放json结构体所占用的空间 */
void hilink_json_delete(void *object);

/* json对象内字符串数据清0 */
void hilink_json_clear_all_string(void *object);

/*
 * 创建系统任务
 * 返回0成功，返回非0失败
 * 注意：1）Contiki OS 不支持该接口
 *       2）任务优先级 level:
 *       mbed OS 固定传0;
 *       其他 OS 支持三个优先级, 含义及取值如下:
 *       TASK_PRIORITY_LOW    = 4,
 *       TASK_PRIORITY_MIDDLE = 3,
 *       TASK_PRIORITY_HIGH   = 2,
 */
int hilink_task_create(const void *handle, const void *taskName, int level,
    unsigned long stackLen, void *taskFunction, void *param);

/* 销毁任务 */
void hilink_task_delete(const void *handle, const void *taskName);

/*
 * 系统sleep, 让出CPU
 * 返回0成功，非0失败
 * 注意：1）Contiki OS 不支持该接口
 *       2）在esp8266上该时间最小单位为10ms
 */
int hilink_msleep(unsigned long ms);

/*
 * 创建UDP通讯套接字
 * 返回小于0发送出错，返回大于或等于0 UDP套接字fd
 */
int hilink_udp_new(unsigned short lport);

/* 关闭UDP通讯套接字 */
void hilink_udp_remove(int fd);

/*
 * UDP发送数据
 * 返回小于0发送出错，返回大于等于0实际发送的字节数
 */
int hilink_udp_send(int fd, const unsigned char *buf, unsigned short len,
    const char *rip, unsigned short port);

/*
 * UDP读取数据
 * 返回小于或等于0读取出错，返回大于0实际接收的数据长度
 */
int hilink_udp_read(int fd, unsigned char *buf, unsigned short len,
    char *rip, unsigned short ripLen, unsigned short *port);

/*
 * 建立TCP连接
 * 返回小于0失败，返回大于或等于0 TCP套接字
 */
int hilink_tcp_connect(const char *dst, unsigned short port);

/*
 * TCP连接状态获取
 * 返回0连接正常，返回其他失败
 */
int hilink_tcp_state(int fd);

/* 断开TCP连接 */
void hilink_tcp_disconnect(int fd);

/*
 * TCP发送数据
 * 返回小于0发送出错，返回大于或等于0实际发送的字节数
 */
int hilink_tcp_send(int fd, const unsigned char *buf, unsigned short len);

/*
 * TCP读取数据
 * 返回小于或等于0读取出错，返回大于0实际读取的字节数
 */
int hilink_tcp_read(int fd, unsigned char *buf, unsigned short len);

/*
 * 内存申请
 * 返回NULL 内存申请失败, 非NULL 成功返回申请的内存指针
 * 注意内存不再使用时, 须使用hilink_free释放
 */
void *hilink_malloc(unsigned int size);

/*
 * 内存释放
 * 注意pt指向的内存须为hilink_malloc申请的内存
 */
void hilink_free(void *pt);

/*
 * 复制源缓冲区的数据到目的缓冲区
 * 返回0-成功, 非0-失败
 * 注意: 1）确保count <= dest所指向的内存区域大小
 *       2）确保dest和src指向的内存没有重叠区域
 */
int hilink_memcmp(const void *buf1, const void *buf2, unsigned int len);

/*
 * 设置目的缓冲区为特定值
 * 返回0-成功, 非0-失败
 * 注意事项：确保count <= dest所指向的内存区域大小
 */
int hilink_memset_s(void *dest, unsigned int destMax, int c, unsigned int count);

/*
 * 复制源缓冲区的数据到目的缓冲区
 * 返回0-成功, 非0-失败
 * 注意: 1）确保count <= dest所指向的内存区域大小
 *       2）确保dest和src指向的内存没有重叠区域
 */
int hilink_memcpy_s(void *dest, unsigned int destMax, const void *src, unsigned int count);

/*
 * 复制指定长度的源字符串到目的缓冲区
 * 返回0-成功, 非0-失败
 * 注意：确保strDest所指内存空间足够容纳拷贝的字符内容
 */
int hilink_strncpy_s(char *strDest, unsigned int destMax, const char *strSrc, unsigned int count);

/*
 * 将指定长度的源字符串连接到目的字符串后面
 * 返回0-成功, 非0-失败
 * 注意：确保strDest所指内存空间足够容纳strDest原有字符及追加的strSrc字符内容
 */
int hilink_strncat_s(char *strDest, unsigned int destMax, const char *strSrc, unsigned int count);

/*
 * 将数据格式化输出到目的缓冲区
 * 返回-1-失败, 其他-实际写入strDest的字节数
 * 注意：strDest要有足够的空间容纳格式化的字符内容
 */
int hilink_sprintf_s(char *strDest, unsigned int destMax, const char *format, ...);

/*
 * 将数据按照指定长度格式化输出到目的缓冲区
 * 返回-1-失败, 其他-欲写入strDest的字节数
 */
int hilink_snprintf_s(char *strDest, unsigned int destMax, unsigned int count, const char *format, ...);

/*
 * 创建互斥锁
 * 返回HILINK_OK成功, HILINK_ERROR失败
 */
int hilink_mutex_create(hilink_mutex_t *mutex);

/*
 * 获取互斥锁
 * 返回HILINK_OK成功, HILINK_ERROR失败
 */
int hilink_mutex_lock(hilink_mutex_t *mutex);

/*
 * 释放互斥锁
 * 返回HILINK_OK成功, HILINK_ERROR失败
 */
int hilink_mutex_unlock(hilink_mutex_t *mutex);

/*
 * 销毁互斥锁
 * 返回HILINK_OK成功, HILINK_ERROR失败
 */
int hilink_mutex_destroy(hilink_mutex_t *mutex);

/*
 * Hilink SDK外部诊断信息记录接口
 * 该接口已经对外提供给第三方厂商使用，为了前向兼容，暂不按最新编码规范整改
 */
void hilink_diagnosis_record_ex(int errCode);

/*
 * 格式化输出字符串
 * 返回值小于0失败, 返回值其他实际输出的字节数
 */
int hilink_printf(const char *format, ...);

/*
 * 获取网络操作失败时的错误码errno
 * 返回网络操作错误码
 */
int HiLinkGetNetWorkErrno(int fd);

#ifdef __cplusplus
}
#endif

#endif /* HILINK_OSADAPTER_H */

