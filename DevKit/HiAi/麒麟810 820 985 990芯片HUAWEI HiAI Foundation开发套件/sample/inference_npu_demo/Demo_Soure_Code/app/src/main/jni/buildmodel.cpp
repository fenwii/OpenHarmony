/**
 *@file buildmodel.cpp
 *
 * Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <jni.h>
#include "string.h"
#include <sys/system_properties.h>
#include <string>
#include <dlfcn.h>
#include <stdlib.h>
#include <android/log.h>
#include "HiAiModelManagerService.h"

static const char* LOG_TAG = "buildmodel";
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
using namespace std;
using namespace hiai;
typedef enum {
    CHECK_OFFLINEMODEL_COMPATIBILITY_SUCCESS = 0,
    BUILD_OFFLINEMODEL_SUCCESS,
    BUILD_OFFLINEMODEL_FAILED,
    GENERATE_OFFLINE_MODEL_FAILED,
    INVALID_OFFLINE_MODEL,
    INVALID_ONLINE_MODEL,
    NO_NPU
} RESULT_CODE;

bool _fileExist(const char* path)
{
    if (path == NULL) {
        return false;
    }
    FILE* fp = fopen(path, "r+");
    if (fp == NULL) {
        return false;
    }
    fclose(fp);
    return true;
}

bool _modelCompatibilityProcessFromBuffeOutFile(shared_ptr<AiModelMngerClient> mclientBuild, const char* offlinemodel)
{
    bool rslt = _fileExist(offlinemodel);
    if (!rslt) {
        ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] offlinemodel is not in directory\n");
        return false;
    }

    std::string path(offlinemodel);
    int pos = path.rfind("/");
    std::string name = path.substr(pos + 1);
    ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] Model name : %s\n", name.c_str());
    AiModelDescription desc(name, 3, 0, 0, 0);
    MemBuffer* buffer = NULL;
    shared_ptr<AiModelBuilder> mcbuilder = make_shared<AiModelBuilder>(mclientBuild);
    buffer = mcbuilder->InputMemBufferCreate(string(offlinemodel));
    if (buffer == nullptr) {
        ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] cannot find the model file.");
        return false;
    }
    desc.SetModelBuffer(buffer->GetMemBufferData(), buffer->GetMemBufferSize());
    ALOGI("[HIAI_DEMO_CHECKMODEL_COPM] Get model %s IO Tensor.", desc.GetName().c_str());

    bool comp = false;
    int ret = mclientBuild->CheckModelCompatibility(desc, comp);
    if (ret != 0) {
        ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] CheckModelCompatibility ERROR: %d", ret);
        return false;
    }

    ALOGE("[HIAI_DEMO_CHECKMODEL_COPM] CheckModelCompatibility comp is : %d", comp);
    return comp;
}

RESULT_CODE _buildModel(shared_ptr<AiModelMngerClient> mclientBuild, const char* offlinemodel)
{
    MemBuffer* onlineBuffer = nullptr;
    MemBuffer* offlineBuffer = nullptr;
    uint32_t offModelSize = 0;
    vector<MemBuffer*> input_membuffer;
    shared_ptr<AiModelBuilder> mcbuilder = make_shared<AiModelBuilder>(mclientBuild);

    if (offlinemodel == nullptr) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] offlinemodel is null\n");
        return INVALID_ONLINE_MODEL;
    }
    onlineBuffer = mcbuilder->ReadBinaryProto(string(offlinemodel));
    if (onlineBuffer == nullptr) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] onlineBuffer is null,offlinemodel error %s\n", offlinemodel);
        return INVALID_ONLINE_MODEL;
    }
    input_membuffer.push_back(onlineBuffer);
    offlineBuffer = mcbuilder->OutputMemBufferCreate(0, input_membuffer);
    if (offlineBuffer == nullptr) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] offlineBuffer failed\n");
        return INVALID_OFFLINE_MODEL;
    }

    int ret = mcbuilder->BuildModel(input_membuffer, offlineBuffer, offModelSize);
    if (ret != 0) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] build model Failed! ret=%d\n", ret);
        return BUILD_OFFLINEMODEL_FAILED;
    }

    // Suggest saving the built model to file system and reloading it. You can get
    // the optimization we supply.
    ret = mcbuilder->MemBufferExportFile(offlineBuffer, offModelSize, string(offlinemodel));
    if (ret != 0) {
        ALOGE("[HIAI_DEMO_BUILDMODEL] export offline model Failed! ret=%d\n", ret);
        return GENERATE_OFFLINE_MODEL_FAILED;
    }
    ALOGI("[HIAI_DEMO_BUILDMODEL] build export model path:%s\n", offlinemodel);
    mcbuilder->MemBufferDestroy(offlineBuffer);
    mcbuilder->MemBufferDestroy(onlineBuffer);

    return BUILD_OFFLINEMODEL_SUCCESS;
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_modelCompatibilityProcessFromFile(
    JNIEnv* env, jclass type, jstring offlinemodel_)
{
    if (env == NULL) {
        ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] env is null");
        return false;
    }
    const char* offlinemodel = env->GetStringUTFChars(offlinemodel_, 0);
    if (offlinemodel == NULL) {
        ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] offlinemodel path is null");
        return false;
    }
    ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] offlinemodel : %s", offlinemodel);

    shared_ptr<AiModelMngerClient> mclientBuild = make_shared<AiModelMngerClient>();
    auto ret = mclientBuild->Init(NULL);
    if (ret) {
        ALOGE("[HIAI_DEMO_COMPATIBILITY_CHECK] AiModelMngerClient Init Failed!\n");
        return false;
    }

    const char* currentversion = mclientBuild->GetVersion();
    ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] ddk currentversion : %s", currentversion);
    RESULT_CODE result_code;
    if (currentversion != nullptr && string(currentversion) < "100.300.010.010") {
        result_code = NO_NPU;
    } else {
        bool checkret = _modelCompatibilityProcessFromBuffeOutFile(mclientBuild, offlinemodel);
        ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] check result : %d", checkret);
        if (checkret) {
            result_code = CHECK_OFFLINEMODEL_COMPATIBILITY_SUCCESS;
        } else {
            int res = _buildModel(mclientBuild, offlinemodel);
            ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] build offlinemodel result_code : %d", res);
            if (res != 1) {
                result_code = BUILD_OFFLINEMODEL_FAILED;
            } else {
                result_code = BUILD_OFFLINEMODEL_SUCCESS;
            }
        }
    }

    env->ReleaseStringUTFChars(offlinemodel_, offlinemodel);
    bool res = false;
    if (result_code == CHECK_OFFLINEMODEL_COMPATIBILITY_SUCCESS || result_code == BUILD_OFFLINEMODEL_SUCCESS) {
        res = true;
    }
    ALOGI("[HIAI_DEMO_COMPATIBILITY_CHECK] result_code value : %d", result_code);
    return res;
}
