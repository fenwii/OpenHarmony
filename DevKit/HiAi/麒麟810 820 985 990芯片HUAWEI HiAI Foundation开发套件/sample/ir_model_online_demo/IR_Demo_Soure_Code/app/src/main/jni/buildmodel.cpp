/*
 * Copyright (C) 2019-2020. Huawei Technologies Co., Ltd. All rights reserved.
 * Description: build model
 */

#include <jni.h>
#include <sys/system_properties.h>
#include <string>
#include <dlfcn.h>
#include <stdlib.h>
#include <android/log.h>
#include "HiAiModelManagerService.h"

const char* const LOG_TAG = "buildmodel";
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
using namespace std;
using namespace hiai;
enum RESULT_CODE {
    CHECK_OFFLINEMODEL_COMPATIBILITY_SUCCESS = 0,
    BUILD_OFFLINEMODEL_SUCCESS,
    BUILD_OFFLINEMODEL_FAILED,
    GENERATE_OFFLINE_MODEL_FAILED,
    INVALID_OFFLINE_MODEL,
    INVALID_ONLINE_MODEL,
    NO_NPU
};

bool FileExist(const char* path)
{
    if (path == nullptr) {
        return false;
    }
    FILE* fp = fopen(path, "r+");
    if (fp == nullptr) {
        return false;
    }
    fclose(fp);
    return true;
}

bool _modelCompatibilityProcessFromBuffeOutFile(shared_ptr<AiModelMngerClient> mclientBuild, const char* offlineModel)
{
    if (offlineModel == nullptr) {
        ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] offlineModel is null\n");
        return false;
    }

    bool rslt = FileExist(offlineModel);
    if (!rslt) {
        ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] offlineModel is not a ditectory\n");
        return false;
    }

    AiModelDescription desc("hiai.om", 3, 0, 0, 0);
    MemBuffer* buffer = nullptr;
    shared_ptr<AiModelBuilder> mcbuilder = make_shared<AiModelBuilder>(mclientBuild);
    buffer = mcbuilder->InputMemBufferCreate(string(offlineModel));
    desc.SetModelBuffer(buffer->GetMemBufferData(), buffer->GetMemBufferSize());
    ALOGI("[HIAI_DEMO_CHECKMODEL_COPM] Get model %s IO Tensor.", desc.GetName().c_str());

    bool comp = false;
    int ret = mclientBuild->CheckModelCompatibility(desc, comp);
    if (ret != 0) {
        ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] CheckModelCompatibility ERROR: %d", ret);
        return false;
    }

    ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] CheckModelCompatibility comp is : %d", comp);
    mcbuilder->MemBufferDestroy(buffer);
    return comp;
}

RESULT_CODE BuildModel(shared_ptr<AiModelMngerClient> mclientBuild, const char* offlineModel)
{
    MemBuffer* onlineBuffer = nullptr;
    MemBuffer* offlineBuffer = nullptr;
    uint32_t offModelSize = 0;
    vector<MemBuffer*> inputMemBuffer;
    shared_ptr<AiModelBuilder> mcbuilder = make_shared<AiModelBuilder>(mclientBuild);

    if (offlineModel == nullptr) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] offlineModel is null\n");
        return INVALID_ONLINE_MODEL;
    }
    onlineBuffer = mcbuilder->ReadBinaryProto(string(offlineModel));
    if (onlineBuffer == nullptr) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] onlineBuffer is null,offlineModel error %s\n", offlineModel);
        return INVALID_ONLINE_MODEL;
    }

    inputMemBuffer.push_back(onlineBuffer);
    offlineBuffer = mcbuilder->OutputMemBufferCreate(0, inputMemBuffer);
    if (offlineBuffer == nullptr) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] offlineBuffer failed\n");
        return INVALID_OFFLINE_MODEL;
    }

    int ret = mcbuilder->BuildModel(inputMemBuffer, offlineBuffer, offModelSize);
    if (ret != 0) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] build model Failed! ret=%d\n", ret);
        return BUILD_OFFLINEMODEL_FAILED;
    }

    // Suggest saving the built model to file system and reloading it. You can get
    // the optimization we supply.
    ret = mcbuilder->MemBufferExportFile(offlineBuffer, offModelSize, string(offlineModel));
    if (ret != 0) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] export offline model Failed! ret=%d\n", ret);
        return GENERATE_OFFLINE_MODEL_FAILED;
    }
    ALOGI("[HIAI_DEMO_BUILDMODEL] build export model path:%s\n", offlineModel);
    mcbuilder->MemBufferDestroy(offlineBuffer);
    mcbuilder->MemBufferDestroy(onlineBuffer);

    return BUILD_OFFLINEMODEL_SUCCESS;
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_modelCompatibilityProcessFromFile(
    JNIEnv* env, jclass type, jstring strOfflineModel)
{

    if (env == nullptr) {
        ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] env is null");
        return false;
    }
    const char* offlineModel = env->GetStringUTFChars(strOfflineModel, 0);
    if (offlineModel == nullptr) {
        ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] offlineModel path is null");
        return false;
    }
    ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] offlineModel : %s", offlineModel);

    shared_ptr<AiModelMngerClient> mclientBuild = make_shared<AiModelMngerClient>();
    auto ret = mclientBuild->Init(nullptr);
    if (ret) {
        ALOGE("[HIAI_DEMO_COMPATIBILITY_CHECK] AiModelMngerClient Init Failed!\n");
        return false;
    }

    const char* currentVersion = mclientBuild->GetVersion();
    ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] ddk currentVersion : %s", currentVersion);
    RESULT_CODE resultCode;
    if (string(currentVersion).compare("000.000.000.000") == 0) {
        resultCode = NO_NPU;
    } else {
        bool checkret = _modelCompatibilityProcessFromBuffeOutFile(mclientBuild, offlineModel);
        ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] check result : %d", checkret);
        if (checkret) {
            resultCode = CHECK_OFFLINEMODEL_COMPATIBILITY_SUCCESS;
        } else {
            int res = BuildModel(mclientBuild, offlineModel);
            ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] build offlineModel resultCode : %d", res);
            if (res != 1) {
                resultCode = BUILD_OFFLINEMODEL_FAILED;
            } else {
                resultCode = BUILD_OFFLINEMODEL_SUCCESS;
            }
        }
    }

    env->ReleaseStringUTFChars(strOfflineModel, offlineModel);

    bool res = false;
    if (resultCode == CHECK_OFFLINEMODEL_COMPATIBILITY_SUCCESS || resultCode == BUILD_OFFLINEMODEL_SUCCESS) {
        res = true;
    }
    ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] resultCode value : %d", resultCode);
    return res;
}
