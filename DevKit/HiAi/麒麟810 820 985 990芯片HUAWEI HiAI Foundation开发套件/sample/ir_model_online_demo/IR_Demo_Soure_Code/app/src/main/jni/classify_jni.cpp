/*
 * Copyright (C) 2019-2020. Huawei Technologies Co., Ltd. All rights reserved.
 * Description: classify sync jni
 */

#include <jni.h>
#include <string>
#include <memory.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <sys/time.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "hiai_ir_build.h"
#include "HiAiModelManagerService.h"

const char* const LOG_TAG = "SYNC_DDK_MSG";
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define IF_BOOL_EXEC(expr, exec_expr) do { \
    if (expr) { \
        exec_expr; \
    } \
} while (0)

static const int SUCCESS = 0;
static const int FAILED = -1;

using namespace std;
using namespace hiai;

static shared_ptr<AiModelMngerClient> g_clientSync = nullptr;
static vector<TensorDimension> inputDimension;
static vector<TensorDimension> outputDimension;
static vector<shared_ptr<AiTensor>> inputTensor;
static vector<shared_ptr<AiTensor>> outputTensor;
static const char* modelName = nullptr;

int UpdateTensorVec()
{
    inputTensor.clear();
    outputTensor.clear();

    for (auto inDim : inputDimension) {
        shared_ptr<AiTensor> input = make_shared<AiTensor>();
        int ret = input->Init(&inDim);
        IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_SYNC] model %s input AiTensor Init failed(input).", modelName);
                     return FAILED);
        inputTensor.push_back(input);
    }
    IF_BOOL_EXEC(inputTensor.size() == 0, LOGE("[HIAI_DEMO_SYNC] inputTensor.size() == 0"); return FAILED);

    for (auto outDim : outputDimension) {
        shared_ptr<AiTensor> output = make_shared<AiTensor>();
        int ret = output->Init(&outDim);
        IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_SYNC] model %s output AiTensor Init failed(output).", modelName);
                     return FAILED);
        outputTensor.push_back(output);
    }
    IF_BOOL_EXEC(outputTensor.size() == 0, LOGE("[HIAI_DEMO_SYNC] outputTensor.size() == 0"); return FAILED);

    return SUCCESS;
}

shared_ptr<AiModelMngerClient> LoadModelSync(const char* modelPath)
{
    shared_ptr<AiModelMngerClient> clientSync = make_shared<AiModelMngerClient>();
    IF_BOOL_EXEC(clientSync == nullptr, LOGE("[HIAI_DEMO_SYNC] Model Manager Client make_shared error.");
                 return nullptr);
    int ret = clientSync->Init(nullptr);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_SYNC] Model Manager Init Failed."); return nullptr);

    shared_ptr<AiModelBuilder> mcbuilder = make_shared<AiModelBuilder>(clientSync);
    // The codes here are for loading model from memory directly. You can choose this option
    // but may abandon the optimization of the model loading.

    // LOGI("[HIAI_DEMO_SYNC] model memory size is %d\n.", g_om_model_buff.length);
    // MemBuffer* buffer = mcbuilder->InputMemBufferCreate(g_om_model_buff.data, g_om_model_buff.length);

    // Suggest saving the built model to file system and reloading it. You can get
    // the optimization we supply.
    LOGI("[HIAI_DEMO_SYNC] modelPath is %s\n.", modelPath);
    MemBuffer* buffer = mcbuilder->InputMemBufferCreate(string(modelPath));
    IF_BOOL_EXEC(buffer == nullptr, LOGE("[HIAI_DEMO_SYNC] cannot find the model file."); return nullptr);

    shared_ptr<AiModelDescription> desc = make_shared<AiModelDescription>("hiai.om", 3, 0, 0, 0);
    desc->SetModelBuffer(buffer->GetMemBufferData(), buffer->GetMemBufferSize());
    LOGE("[HIAI_DEMO_SYNC] loadModel %s IO Tensor.", desc->GetName().c_str());
    vector<shared_ptr<AiModelDescription>> modelDesc;
    modelDesc.push_back(desc);

    ret = clientSync->Load(modelDesc);
    mcbuilder->MemBufferDestroy(buffer);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_SYNC] Model Load Failed."); return nullptr);

    inputDimension.clear();
    outputDimension.clear();
    LOGI("[HIAI_DEMO_SYNC] Get model %s IO Tensor.", modelName);
    ret = clientSync->GetModelIOTensorDim(string(modelName) + string(".om"), inputDimension, outputDimension);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_SYNC] Get Model IO Tensor Dimension failed,ret is %d.", ret);
                 return nullptr);
    IF_BOOL_EXEC(inputDimension.size() == 0, LOGE("[HIAI_DEMO_SYNC] inputDimension.size() == 0"); return nullptr);

    IF_BOOL_EXEC(UpdateTensorVec() != SUCCESS, return nullptr);

    return clientSync;
}

long timeUseSync = 0;

extern "C" JNIEXPORT jlong JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_GetTimeUseSync()
{
    return timeUseSync;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_loadModelSync(
    JNIEnv* env, jclass type, jobject modelInfo)
{
    jclass modelInfoClass = env->GetObjectClass(modelInfo);
    jmethodID getOfflineModelName = env->GetMethodID(modelInfoClass, "getOfflineModelName", "()Ljava/lang/String;");
    jmethodID getModelPath = env->GetMethodID(modelInfoClass, "getModelPath", "()Ljava/lang/String;");
    IF_BOOL_EXEC(getOfflineModelName == nullptr, LOGE("[HIAI_DEMO_SYNC] can not find getOfflineModelName method.");
                 return nullptr);
    jstring strModelName = (jstring)env->CallObjectMethod(modelInfo, getOfflineModelName);
    jstring strModelPath = (jstring)env->CallObjectMethod(modelInfo, getModelPath);
    modelName = env->GetStringUTFChars(strModelName, 0);
    LOGI("[HIAI_DEMO_SYNC] modelName is %s .", modelName);
    IF_BOOL_EXEC(modelName == nullptr, LOGE("[HIAI_DEMO_SYNC] modelName is invalid."); return nullptr);
    const char* modelPath = env->GetStringUTFChars(strModelPath, 0);
    IF_BOOL_EXEC(modelPath == nullptr, LOGE("[HIAI_DEMO_SYNC] modelPath is invalid."); return nullptr);
    // load
    IF_BOOL_EXEC(!g_clientSync, g_clientSync = LoadModelSync(modelPath); IF_BOOL_EXEC(
        g_clientSync == nullptr, LOGE("[HIAI_DEMO_SYNC] g_clientSync loadModel is nullptr."); return nullptr));
    // load model
    LOGI("[HIAI_DEMO_SYNC] sync load model INPUT NCHW : %d %d %d %d.", inputDimension[0].GetNumber(),
        inputDimension[0].GetChannel(), inputDimension[0].GetHeight(), inputDimension[0].GetWidth());
    LOGI("[HIAI_DEMO_SYNC] sync load model OUTPUT NCHW : %d %d %d %d.", outputDimension[0].GetNumber(),
        outputDimension[0].GetChannel(), outputDimension[0].GetHeight(), outputDimension[0].GetWidth());

    jfieldID inputIdN = env->GetFieldID(modelInfoClass, "input_N", "I");
    jfieldID inputIdC = env->GetFieldID(modelInfoClass, "input_C", "I");
    jfieldID inputIdH = env->GetFieldID(modelInfoClass, "input_H", "I");
    jfieldID inputIdW = env->GetFieldID(modelInfoClass, "input_W", "I");
    jfieldID inputNumber = env->GetFieldID(modelInfoClass, "input_Number", "I");
    env->SetIntField(modelInfo, inputIdN, inputDimension[0].GetNumber());
    env->SetIntField(modelInfo, inputIdC, inputDimension[0].GetChannel());
    env->SetIntField(modelInfo, inputIdH, inputDimension[0].GetHeight());
    env->SetIntField(modelInfo, inputIdW, inputDimension[0].GetWidth());
    env->SetIntField(modelInfo, inputNumber, inputDimension.size());

    jfieldID outputIdN = env->GetFieldID(modelInfoClass, "output_N", "I");
    jfieldID outputIdC = env->GetFieldID(modelInfoClass, "output_C", "I");
    jfieldID outputIdH = env->GetFieldID(modelInfoClass, "output_H", "I");
    jfieldID outputIdW = env->GetFieldID(modelInfoClass, "output_W", "I");
    jfieldID outputNumber = env->GetFieldID(modelInfoClass, "output_Number", "I");

    env->SetIntField(modelInfo, outputIdN, outputDimension[0].GetNumber());
    env->SetIntField(modelInfo, outputIdC, outputDimension[0].GetChannel());
    env->SetIntField(modelInfo, outputIdH, outputDimension[0].GetHeight());
    env->SetIntField(modelInfo, outputIdW, outputDimension[0].GetWidth());
    env->SetIntField(modelInfo, outputNumber, outputDimension.size());
    return modelInfo;
}

int runJniProcess(JNIEnv* env, jobject bufList, jmethodID listGet, int len)
{
    LOGI("[HIAI_DEMO_SYNC] INPUT NCHW : %d %d %d %d.", inputDimension[0].GetNumber(), inputDimension[0].GetChannel(),
        inputDimension[0].GetHeight(), inputDimension[0].GetWidth());
    LOGI("[HIAI_DEMO_SYNC] OUTPUT NCHW : %d %d %d %d.", outputDimension[0].GetNumber(), outputDimension[0].GetChannel(),
        outputDimension[0].GetHeight(), outputDimension[0].GetWidth());
    for (int i = 0; i < len; i++) {
        jbyteArray buf_ = (jbyteArray)(env->CallObjectMethod(bufList, listGet, i));
        jbyte* dataBuff = nullptr;
        int dataBuffSize = 0;
        dataBuff = env->GetByteArrayElements(buf_, nullptr);
        dataBuffSize = env->GetArrayLength(buf_);
        IF_BOOL_EXEC(
            inputTensor[i]->GetSize() != dataBuffSize,
            LOGE("[HIAI_DEMO_SYNC] input->GetSize(%d) != dataBuffSize(%d) ", inputTensor[i]->GetSize(), dataBuffSize);
            return FAILED);
        memcpy(inputTensor[i]->GetBuffer(), dataBuff, (size_t)dataBuffSize);
        env->ReleaseByteArrayElements(buf_, dataBuff, 0);
    }

    AiContext context;
    string key = "model_name";
    string value = modelName;
    value += ".om";
    context.AddPara(key, value);
    LOGI("[HIAI_DEMO_SYNC] runModel modelName:%s", modelName);
    // before process
    struct timeval tpstart, tpend;
    gettimeofday(&tpstart, nullptr);
    int istamp;
    int ret = g_clientSync->Process(context, inputTensor, outputTensor, 1000, istamp);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_SYNC] Runmodel Failed!, ret=%d\n", ret); return FAILED);
    // after process
    gettimeofday(&tpend, nullptr);
    float timeUse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    timeUseSync = timeUse / 1000;
    LOGI("[HIAI_DEMO_SYNC] infrence time %f ms.\n", timeUse / 1000);

    return SUCCESS;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_runModelSync(
    JNIEnv* env, jclass type, jobject modelInfo, jobject bufList)
{
    IF_BOOL_EXEC(env == nullptr, LOGE("[HIAI_DEMO_SYNC] runModelSync env is null"); return nullptr);
    jclass ModelInfo = env->GetObjectClass(modelInfo);
    IF_BOOL_EXEC(ModelInfo == nullptr, LOGE("[HIAI_DEMO_SYNC] can not find ModelInfo class."); return nullptr);
    IF_BOOL_EXEC(bufList == nullptr, LOGE("[HIAI_DEMO_SYNC] buf_ is null."); return nullptr);
    jmethodID getOfflineModelName = env->GetMethodID(ModelInfo, "getOfflineModelName", "()Ljava/lang/String;");
    jmethodID getModelPath = env->GetMethodID(ModelInfo, "getModelPath", "()Ljava/lang/String;");
    IF_BOOL_EXEC(getOfflineModelName == nullptr, LOGE("[HIAI_DEMO_SYNC] can not find getOfflineModelName method.");
                 return nullptr);
    jstring strModelName = (jstring)env->CallObjectMethod(modelInfo, getOfflineModelName);
    jstring strModelPath = (jstring)env->CallObjectMethod(modelInfo, getModelPath);
    modelName = env->GetStringUTFChars(strModelName, 0);
    IF_BOOL_EXEC(modelName == nullptr, LOGE("[HIAI_DEMO_SYNC] modelName is invalid."); return nullptr);
    const char* modelPath = env->GetStringUTFChars(strModelPath, 0);
    IF_BOOL_EXEC(modelPath == nullptr, LOGE("[HIAI_DEMO_SYNC] modelPath is invalid."); return nullptr);
    jclass classList = env->GetObjectClass(bufList);
    IF_BOOL_EXEC(classList == nullptr, LOGE("[HIAI_DEMO_SYNC] can not find List class."); return nullptr);
    jmethodID listGet = env->GetMethodID(classList, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(classList, "size", "()I");
    IF_BOOL_EXEC(listGet == nullptr, LOGE("[HIAI_DEMO_SYNC] can not find get method."); return nullptr);
    IF_BOOL_EXEC(listSize == nullptr, LOGE("[HIAI_DEMO_SYNC] can not find size method."); return nullptr);

    int len = static_cast<int>(env->CallIntMethod(bufList, listSize));
    // load
    IF_BOOL_EXEC(!g_clientSync, g_clientSync = LoadModelSync(modelPath); IF_BOOL_EXEC(
        g_clientSync == nullptr, LOGE("[HIAI_DEMO_SYNC] Model Manager Client is nullptr."); return nullptr));
    // run
    IF_BOOL_EXEC(runJniProcess(env, bufList, listGet, len), return nullptr);
    // outputTensor
    jclass outputListClass = env->FindClass("java/util/ArrayList");
    jmethodID outputListInit = env->GetMethodID(outputListClass, "<init>", "()V");
    jmethodID listAdd = env->GetMethodID(outputListClass, "add", "(Ljava/lang/Object;)Z");
    jobject outputList = env->NewObject(outputListClass, outputListInit, "");

    long outputTensorSize = outputTensor.size();
    LOGI("[HIAI_DEMO_SYNC] outputTensorSize is %ld .", outputTensorSize);
    for (long j = 0; j < outputTensorSize; j++) {
        float* outputBuffer = reinterpret_cast<float*>(outputTensor[j]->GetBuffer());
        int outputsize = outputDimension[j].GetNumber() * outputDimension[j].GetChannel() *
            outputDimension[j].GetHeight() * outputDimension[j].GetWidth();
        jfloatArray result = env->NewFloatArray(outputsize);
        jfloat temp[outputsize];
        for (int i = 0; i < outputsize; i++) {
            temp[i] = outputBuffer[i];
        }
        env->SetFloatArrayRegion(result, 0, outputsize, temp);
        jboolean output_add = env->CallBooleanMethod(outputList, listAdd, result);
        LOGI("[HIAI_DEMO_SYNC] output_add result  is %d .", output_add);
    }
    env->ReleaseStringUTFChars(strModelName, modelName);
    return outputList;
}
