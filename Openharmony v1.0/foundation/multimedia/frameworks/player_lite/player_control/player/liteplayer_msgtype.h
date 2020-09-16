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

#ifndef LITEPLAYER_MSGTYPE_H
#define LITEPLAYER_MSGTYPE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

enum LiteplayerMsgType {
    LITEPLAYER_MSG_SETATTR = 0,  // setmedia
    LITEPLAYER_MSG_REGCALLBACK,
    LITEPLAYER_MSG_SET_DATASOURCE_FD,
    LITEPLAYER_MSG_SET_DATASOURCE_URI,
    LITEPLAYER_MSG_SET_DATASOURCE_STREAM,
    LITEPLAYER_MSG_PREPARE,
    LITEPLAYER_MSG_PLAY,
    LITEPLAYER_MSG_SEEK,
    LITEPLAYER_MSG_PAUSE,
    LITEPLAYER_MSG_TPLAY,
    LITEPLAYER_MSG_STOP,
    LITEPLAYER_MSG_GETFILEINFO,
    LITEPLAYER_MSG_HANDLEDATA,
    LITEPLAYER_MSG_ERROR,
    LITEPLAYER_MSG_SET_VOLUME,
    LITEPLAYER_MSG_BUTT
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* LITEPLAYER_MSG_TYPE_H */
