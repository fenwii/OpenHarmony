/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HIVIEW_HIEVENT_H
#define HIVIEW_HIEVENT_H

#define MAX_PATH_NUMBER     10

/* hievent struct */
struct HiviewHievent {
    unsigned int eventid;

    long long time;

    /* payload linked list */
    struct HiviewHieventPayload *head;

    /* file path needs uploaded */
    char *filePath[MAX_PATH_NUMBER];
};


struct HiviewHievent *HiviewHieventCreate(unsigned int eventid);
int HiviewHieventPutIntegral(struct HiviewHievent *event,
                             const char *key, long value);
int HiviewHieventPutString(struct HiviewHievent *event,
                           const char *key, const char *value);
int HiviewHieventSetTime(struct HiviewHievent *event, long long seconds);
int HiviewHieventAddFilePath(struct HiviewHievent *event, const char *path);
int HiviewHieventReport(struct HiviewHievent *obj);
void HiviewHieventDestroy(struct HiviewHievent *event);

#endif /* HIVIEW_HIEVENT_H */
