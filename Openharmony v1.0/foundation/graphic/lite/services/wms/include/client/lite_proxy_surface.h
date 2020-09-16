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

#ifndef GRAPHIC_LITE_PROXY_SURFACE_H
#define GRAPHIC_LITE_PROXY_SURFACE_H

#include "client/isurface.h"
#include "client/lite_win_requestor.h"
#include "server/lite_win.h"
#include "surface.h"

namespace OHOS {
class LiteProxySurface : public ISurface {
public:
    LiteProxySurface(Surface* surface, LiteWinRequestor* par);
    virtual ~LiteProxySurface();

    virtual void Lock(void** buf, void** phyMem, uint32_t* strideLen) override;
    virtual void Unlock() override;

private:
    SurfaceBuffer* buffer_;
    Surface* surface_;
};
}
#endif