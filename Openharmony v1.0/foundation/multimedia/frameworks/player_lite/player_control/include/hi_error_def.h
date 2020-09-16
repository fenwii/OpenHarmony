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

#ifndef __HI_ERROR_DEF_H__
#define __HI_ERROR_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/** error level */
typedef enum hiAPP_ERR_LEVEL_E {
    APP_ERR_LEVEL_DEBUG = 0, /* debug-level */
    APP_ERR_LEVEL_INFO,      /* informational */
    APP_ERR_LEVEL_NOTICE,    /* normal but significant condition */
    APP_ERR_LEVEL_WARNING,   /* warning conditions */
    APP_ERR_LEVEL_ERROR,     /* error conditions */
    APP_ERR_LEVEL_CRIT,      /* critical conditions */
    APP_ERR_LEVEL_ALERT,     /* action must be taken immediately */
    APP_ERR_LEVEL_FATAL,     /* just for compatibility with previous version */
    APP_ERR_LEVEL_BUTT
} APP_ERR_LEVEL_E;

/** common error code  0x01~0x11,module private error code define from 0x40 */
typedef enum hiAPP_ERR_CODE_E {
    APP_ERR_ILLEGAL_PARAM = 0x01,   /* at lease one parameter is illagal
                               * eg, an illegal enumeration value */
    APP_ERR_NULL_PTR = 0x02,        /*  using a NULL point */
    APP_ERR_PARAM_OVERRANGE = 0x03, /* param out of range */
    APP_ERR_NOT_SUPPORT = 0x04,     /*  operation or type is not supported by NOW */
    APP_ERR_NOT_CONFIG = 0x05,      /*  try to enable or initialize system, device
                              ** or channel, before configing attribute */
    APP_ERR_NOT_PERM = 0x06,        /*  operation is not permitted
                              ** eg, try to change static attribute */
    APP_ERR_NOMEM = 0x07,           /*  failure caused by malloc memory */
    APP_ERR_SYS_NOTREADY = 0x08,        /*  System is not ready, maybe not initialed or
                              ** loaded. Returning the error code when opening
                              ** a device file failed. */
    APP_ERR_BADADDR = 0x09,         /*  bad address,
                              ** eg. used for copy_from_user & copy_to_user */
    APP_ERR_BUSY = 0x10,            /*  resource is busy,
                              ** eg. destroy a venc chn without unregister it */
    APP_ERR_BUTT = 0x11,            /*  maxium code, private error code of all modules
                              ** must be greater than it */
} APP_ERR_CODE_E;

#define HI_ERR_APP_APPID     (0x80000000L + 0x21000000L)
#define HI_ERR_EXT_APP_APPID (0x80000000L + 0x22000000L)

#define HI_APP_DEF_ERR(module, level, errid) \
    ((int32_t)((HI_ERR_APP_APPID) | ((module) << 16) | ((level) << 13) | (errid)))

#define HI_EXT_APP_DEF_ERR(module, level, errid) \
    ((int32_t)((HI_ERR_EXT_APP_APPID) | ((module) << 16) | ((level) << 13) | (errid)))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */
#endif  // __HI_ERROR_DEF_H__
