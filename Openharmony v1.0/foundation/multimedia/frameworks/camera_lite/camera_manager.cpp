/*
 * Copyright(c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "camera_manager.h"

#include <list>
#include <map>

#include "camera_impl.h"
#include "camera_service.h"

using namespace std;
namespace OHOS {
namespace Media {
class CameraManagerImpl : public CameraManager, public CameraServiceCallback {
public:
    CameraManagerImpl()
    {
        // get client instance of camera service
        cameraService_ = CameraService::GetInstance();
        // Since service is running in the current process now, it always succeed
        cameraService_->Initialize(this);
    }
    ~CameraManagerImpl()
    {
        for (auto &i : cameraMapCache_) {
            delete i.second;
        }
    }

    void OnCameraServiceInitialized(list<string> &availCameraIdList) override
    {
        MEDIA_DEBUG_LOG("Camera manager initializing.");
        /* cameraService_ cannot be nullptr as OnCameraServiceInitialized is a callback of cameraService_ */
        for (auto &cameraId : availCameraIdList) {
            InitCameraAbility(cameraId);
        }
    }

    void OnCameraStatusChange(string &cameraId, CameraStauts status, CameraDevice *device = nullptr) override
    {
        auto p = cameraMapCache_.find(cameraId);
        switch (status) {
            case CAMERA_STATUS_UNAVAIL:
                if (p != cameraMapCache_.end()) {
                    for (auto &i : deviceCbList_) {
                        i.second->Post(
                            [i, cameraId]() { i.first->OnCameraStatus(cameraId, CAMERA_DEVICE_STATE_UNAVAILABLE); });
                    }
                    // User may still using icamera now
                    delete p->second;
                    cameraMapCache_.erase(p);
                }
                break;
            case CAMERA_STATUS_AVAIL:
                InitCameraAbility(cameraId);
                if (p == cameraMapCache_.end()) {
                    for (auto &i : deviceCbList_) {
                        i.second->Post(
                            [i, cameraId]() { i.first->OnCameraStatus(cameraId, CAMERA_DEVICE_STATE_AVAILABLE); });
                    }
                }
                break;
            case CAMERA_STATUS_CREATED:
                if (p != cameraMapCache_.end()) {
                    p->second->OnCreate(device);
                }
                break;
            case CAMERA_STATUS_CREATE_FAILED:
                if (p != cameraMapCache_.end()) {
                    p->second->OnCreateFailed();
                }
                break;
            default:
                break;
        }
    }

    void RegisterCameraDeviceCallback(CameraDeviceCallback &callback, EventHandler &handler) override
    {
        deviceCbList_.emplace_back(make_pair(&callback, &handler));
        for (auto &i : cameraMapCache_) {
            string cameraId = i.first;
            handler.Post([&callback, cameraId]() { callback.OnCameraStatus(cameraId, CAMERA_DEVICE_STATE_AVAILABLE); });
        }
    }

    void UnregisterCameraDeviceCallback(CameraDeviceCallback &callback) override
    {
        for (auto p = deviceCbList_.begin(); p != deviceCbList_.end(); p++) {
            if (p->first == &callback) {
                deviceCbList_.erase(p);
                break;
            }
        }
    }

    list<string> GetCameraIds() override
    {
        list<string> cameraList;
        for (auto &i : cameraMapCache_) {
            MEDIA_DEBUG_LOG("%s", i.first.c_str());
            cameraList.emplace_back(i.first);
        }
        return cameraList;
    }

    const CameraAbility *GetCameraAbility(const string &cameraId) override
    {
        auto camera = cameraMapCache_.find(cameraId);
        return camera->second->GetAbility();
    }

    void CreateCamera(const string &cameraId, CameraStateCallback &callback, EventHandler &handler) override
    {
        auto p = cameraMapCache_.find(cameraId);
        if (p == cameraMapCache_.end()) {
            handler.Post([&callback, &cameraId] { callback.OnCreateFailed(cameraId, MEDIA_ERR); });
        }
        p->second->RegistCb(callback, handler);
        cameraService_->CreateCamera(cameraId);
    }

private:
    CameraService *cameraService_;
    map<string, CameraImpl *> cameraMapCache_;
    list<pair<CameraDeviceCallback *, EventHandler *>> deviceCbList_;

    void InitCameraAbility(string &cameraId)
    {
        auto ability = cameraService_->GetCameraAbility(cameraId);
        CameraImpl *cam = new (nothrow) CameraImpl(cameraId, ability);
        if (cam == nullptr) {
            MEDIA_FATAL_LOG("New object failed.");
            return;
        }
        cameraMapCache_[cameraId] = cam;
    }
};

CameraManager *CameraManager::GetInstance()
{
    static CameraManagerImpl cameraManagerImpl;
    return &cameraManagerImpl;
}
} // namespace Media
} // namespace OHOS