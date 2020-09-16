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
#define IP_LIST_LEN 40

typedef void* hilink_mutex_t;

typedef enum {
    NW_DISCONNECTED = 0,
    NW_CONNECTED    = 1
} network_state_t;

typedef enum {
    HILINK_SOCKET_READABLE = 1,
    HILINK_SOCKET_WRITEABLE = 2,
    HILINK_SOCKET_EXCEPTION = 4
} HiLinkSocketState;

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

int hilink_gethostbyname(const char *hostname, char ipList[][IP_LIST_LEN], int num);
int hilink_gettime(unsigned long *ms);
unsigned int hilink_strlen(const char *src);
int hilink_strncmp(const char *str1, const char *str2, unsigned int len);
char *hilink_strchr(const char *str, int ch);
char *hilink_strrchr(const char *str, char ch);
int hilink_atoi(const char *str);
unsigned short hilink_htons(unsigned short hs);
unsigned short hilink_ntohs(unsigned short ns);
void *hilink_json_parse(const char *value);
char *hilink_json_get_string_value(const void *object, const char *name, unsigned int *len);
int hilink_json_get_number_value(const void *object, const char *name, int *value);
void *hilink_json_get_object(const void *object, const char *name);
void *hilink_json_get_arrayitem(const void *array, int item);
int hilink_json_get_arraysize(const void *array);
void hilink_json_delete(void *object);
void hilink_json_clear_all_string(void *object);
int hilink_task_create(const void *handle, const void *taskName, int level,
    unsigned long stackLen, void *taskFunction, void *param);
void hilink_task_delete(const void *handle, const void *taskName);
int hilink_msleep(unsigned long ms);
int hilink_udp_new(unsigned short lport);
void hilink_udp_remove(int fd);
int hilink_udp_send(int fd, const unsigned char *buf, unsigned short len,
    const char *rip, unsigned short port);
int hilink_udp_read(int fd, unsigned char *buf, unsigned short len,
    char *rip, unsigned short ripLen, unsigned short *port);
int hilink_tcp_connect(const char *dst, unsigned short port);
int hilink_tcp_state(int fd);
void hilink_tcp_disconnect(int fd);
int hilink_tcp_send(int fd, const unsigned char *buf, unsigned short len);
int hilink_tcp_read(int fd, unsigned char *buf, unsigned short len);
void *hilink_malloc(unsigned int size);
void hilink_free(void *pt);
int hilink_memcmp(const void *buf1, const void *buf2, unsigned int len);
int hilink_memset_s(void *dest, unsigned int destMax, int c, unsigned int count);
int hilink_memcpy_s(void *dest, unsigned int destMax, const void *src, unsigned int count);
int hilink_strncpy_s(char *strDest, unsigned int destMax, const char *strSrc, unsigned int count);
int hilink_strncat_s(char *strDest, unsigned int destMax, const char *strSrc, unsigned int count);
int hilink_sprintf_s(char *strDest, unsigned int destMax, const char *format, ...);
int hilink_snprintf_s(char *strDest, unsigned int destMax, unsigned int count, const char *format, ...);
int hilink_mutex_create(hilink_mutex_t *mutex);
int hilink_mutex_lock(hilink_mutex_t *mutex);
int hilink_mutex_unlock(hilink_mutex_t *mutex);
int hilink_mutex_destroy(hilink_mutex_t *mutex);
void hilink_diagnosis_record_ex(int errCode);
int hilink_printf(const char *format, ...);

int HiLinkGetNetWorkErrno(int fd);

#ifdef __cplusplus
}
#endif

#endif /* HILINK_OSADAPTER_H */

