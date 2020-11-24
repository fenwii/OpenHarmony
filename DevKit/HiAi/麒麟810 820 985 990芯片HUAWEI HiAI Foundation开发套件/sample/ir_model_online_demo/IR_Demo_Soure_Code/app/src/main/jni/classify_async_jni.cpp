/*
 * Copyright (C) 2019-2020. Huawei Technologies Co., Ltd. All rights reserved.
 * Description: classify async jni
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
#include <unistd.h>
#include "hiai_ir_build.h"
#include "HiAiModelManagerService.h"

const char* const LOG_TAG = "ASYNC_DDK_MSG";
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
static jclass callbacksClass;
static jobject callbacksInstance;
JavaVM* jvm;
float timeUse;
struct timeval tpstart, tpend;
static map<int32_t, vector<shared_ptr<AiTensor>>*> g_mapInputTensor;

mutex g_mutexMap;
condition_variable g_condition;

class JNIListener : public AiModelManagerClientListener {
public:
    JNIListener()
    {
    }
    ~JNIListener()
    {
    }

    void OnProcessDone(
        const AiContext& context, int32_t result, const vector<shared_ptr<AiTensor>>& outData, int32_t istamp);
    void OnServiceDied();
};

void JNIListener::OnProcessDone(
    const AiContext& context, int result, const vector<shared_ptr<AiTensor>>& outputTensor, int32_t istamp)
{
    std::unique_lock<std::mutex> lock(g_mutexMap);
    g_mapInputTensor.erase(istamp);
    g_condition.notify_all();
    IF_BOOL_EXEC(result != SUCCESS, LOGI("[HIAI_DEMO_ASYNC] AYSNC infrence error is %d.", result); return);
    gettimeofday(&tpend, nullptr);
    timeUse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    LOGI("[HIAI_DEMO_ASYNC] AYSNC infrence time %f ms, JNI layer onRunDone istamp: %d", timeUse / 1000, istamp);
    JNIEnv* env = nullptr;
    jvm->AttachCurrentThread(&env, nullptr);
    vector<string> keys;
    ((AiContext)context).GetAllKeys(keys);
    for (auto key : keys) {
        string value = ((AiContext)context).GetPara(key);
        LOGI("[HIAI_DEMO_ASYNC] key: %s, value: %s.", key.c_str(), value.c_str());
    }
    jclass outputListClass = env->FindClass("java/util/ArrayList");
    jmethodID outputListInit = env->GetMethodID(outputListClass, "<init>", "()V");
    jobject outputList = env->NewObject(outputListClass, outputListInit, "");
    jmethodID listAdd = env->GetMethodID(outputListClass, "add", "(Ljava/lang/Object;)Z");
    long outputTensorSize = outputTensor.size();
    for (long j = 0; j < outputTensorSize; j++) {
        jfloat* outputBuffer = (jfloat*)outputTensor[j]->GetBuffer();
        auto outputCount = outputTensor[j]->GetSize() / sizeof(jfloat);
        jfloatArray result = env->NewFloatArray(outputCount);
        jfloat temp[outputCount];
        for (int i = 0; i < outputCount; i++) {
            temp[i] = outputBuffer[i];
        }
        env->SetFloatArrayRegion(result, 0, outputCount, temp);
        jboolean outputAdd = env->CallBooleanMethod(outputList, listAdd, result);
    }
    jfloat infertime = timeUse;
    IF_BOOL_EXEC(callbacksInstance == nullptr, return);
    jmethodID onValueReceived = env->GetMethodID(callbacksClass, "OnProcessDone", "(ILjava/util/ArrayList;F)V");
    IF_BOOL_EXEC(onValueReceived == nullptr, LOGI("[HIAI_DEMO_ASYNC] jni onValueReceived null"));
    env->CallVoidMethod(callbacksInstance, onValueReceived, istamp, outputList, infertime);
}

void JNIListener::OnServiceDied()
{
    LOGE("[HIAI_DEMO_ASYNC] JNI layer OnServiceDied:");

    JNIEnv* env = nullptr;
    jvm->AttachCurrentThread(&env, nullptr);

    if (callbacksInstance == nullptr) {
        return;
    } else {
        jmethodID onValueReceived = env->GetMethodID(callbacksClass, "OnServiceDied", "()V");
        env->CallVoidMethod(callbacksInstance, onValueReceived);
    }
}

static shared_ptr<AiModelMngerClient> mclientAsync = nullptr;
static vector<TensorDimension> inputDimension;
static vector<TensorDimension> outputDimension;
static vector<shared_ptr<AiTensor>> inputTensor1;
static vector<shared_ptr<AiTensor>> inputTensor2;
static vector<shared_ptr<AiTensor>> outputTensor;
static const char* modelName = nullptr;

vector<shared_ptr<AiTensor>>* findInputTensor()
{
    std::unique_lock<std::mutex> ulock(g_mutexMap);
    while (g_mapInputTensor.size() == 2) {
        g_condition.wait_for(ulock, chrono::seconds(1));
    }
    if (g_mapInputTensor.size() == 0) {
        return &inputTensor1;
    } else if (g_mapInputTensor.size() == 1) {
        map<int32_t, vector<shared_ptr<AiTensor>>*>::iterator ite;
        ite = g_mapInputTensor.begin();
        if (ite->second == &inputTensor1) {
            return &inputTensor2;
        } else {
            return &inputTensor1;
        }
    }
    return nullptr;
}

shared_ptr<JNIListener> listener = make_shared<JNIListener>();

int UpdateAsyncInputTensorVec()
{
    inputTensor1.clear();
    inputTensor2.clear();
    for (auto inDim : inputDimension) {
        shared_ptr<AiTensor> input = make_shared<AiTensor>();
        int ret = input->Init(&inDim);
        IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] model %s AiTensor Init failed(input1).", modelName);
                     return FAILED);
        inputTensor1.push_back(input);
        shared_ptr<AiTensor> input2 = make_shared<AiTensor>();
        ret = input2->Init(&inDim);
        IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] model %s AiTensor Init failed(input2).", modelName);
                     return FAILED);
        inputTensor2.push_back(input2);
    }
    IF_BOOL_EXEC(inputTensor1.size() == 0, LOGE("[HIAI_DEMO_ASYNC] inputTensor1.size() == 0"); return FAILED);
    LOGE("[HIAI_DEMO_ASYNC] inputTensor1.size %zu ", inputTensor1.size());
    IF_BOOL_EXEC(inputTensor2.size() == 0, LOGE("[HIAI_DEMO_ASYNC] inputTensor2.size() == 0"); return FAILED);
    LOGE("[HIAI_DEMO_ASYNC] inputTensor2.size %zu ", inputTensor2.size());

    return SUCCESS;
}

int UpdateAsyncOutputTensorVec()
{
    outputTensor.clear();
    for (auto outDim : outputDimension) {
        shared_ptr<AiTensor> output = make_shared<AiTensor>();
        int ret = output->Init(&outDim);
        IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] model %s AiTensor Init failed(output).", modelName);
                     return FAILED);
        outputTensor.push_back(output);
    }
    // In this demo, model may has many output
    IF_BOOL_EXEC(outputTensor.size() == 0, LOGE("[HIAI_DEMO_ASYNC] outputTensor.size() == 0"); return FAILED);

    return SUCCESS;
}

shared_ptr<AiModelMngerClient> LoadModelASync(const char* modelPath)
{
    shared_ptr<AiModelMngerClient> clientPtr = make_shared<AiModelMngerClient>();
    IF_BOOL_EXEC(clientPtr == nullptr, LOGE("[HIAI_DEMO_ASYNC] Model Manager Client make_shared error.");
                 return nullptr);
    int ret = clientPtr->Init(listener);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Model Manager Init Failed."); return nullptr);
    shared_ptr<AiModelBuilder> mcbuilder = make_shared<AiModelBuilder>(clientPtr);

    // The codes here are for loading model from memory directly. You can choose this option
    // but may abandon the optimization of the model loading.

    // LOGI("[HIAI_DEMO_ASYNC] model memory size is %d\n.", g_om_model_buff.length);
    // MemBuffer* buffer = mcbuilder->InputMemBufferCreate(g_om_model_buff.data, g_om_model_buff.length);

    // Suggest saving the built model to file system and reloading it. You can get
    // the optimization we supply.
    LOGI("[HIAI_DEMO_ASYNC] modelPath is %s\n.", modelPath);
    MemBuffer* buffer = mcbuilder->InputMemBufferCreate(string(modelPath));
    IF_BOOL_EXEC(buffer == nullptr, LOGE("[HIAI_DEMO_ASYNC] cannot find the model file."); return nullptr);

    string modelNameLoad = string(modelName) + string(".om");
    shared_ptr<AiModelDescription> desc = make_shared<AiModelDescription>(modelNameLoad, 3, 0, 0, 0);
    desc->SetModelBuffer(buffer->GetMemBufferData(), buffer->GetMemBufferSize());
    LOGE("[HIAI_DEMO_ASYNC] loadModel %s IO Tensor.", desc->GetName().c_str());
    vector<shared_ptr<AiModelDescription>> modelDesc;
    modelDesc.push_back(desc);
    ret = clientPtr->Load(modelDesc);
    mcbuilder->MemBufferDestroy(buffer);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Model Load Failed."); return nullptr);

    inputDimension.clear();
    outputDimension.clear();
    LOGI("[HIAI_DEMO_ASYNC] Get model %s IO Tensor.", modelName);
    ret = clientPtr->GetModelIOTensorDim(string(modelName) + string(".om"), inputDimension, outputDimension);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Get Model IO Tensor Dimension failed."); return nullptr);

    IF_BOOL_EXEC(UpdateAsyncInputTensorVec() != SUCCESS, return nullptr);
    IF_BOOL_EXEC(UpdateAsyncOutputTensorVec() != SUCCESS, return nullptr);

    return clientPtr;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_loadModelAsync(
    JNIEnv* env, jclass type, jobject modelInfo)
{
    jclass modelInfoClass = env->GetObjectClass(modelInfo);
    jmethodID getOfflineModelName = env->GetMethodID(modelInfoClass, "getOfflineModelName", "()Ljava/lang/String;");
    jmethodID getModelPath = env->GetMethodID(modelInfoClass, "getModelPath", "()Ljava/lang/String;");
    IF_BOOL_EXEC(getOfflineModelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getOfflineModelName method.");
                 return nullptr);
    jstring strModelName = (jstring)env->CallObjectMethod(modelInfo, getOfflineModelName);
    jstring strModelPath = (jstring)env->CallObjectMethod(modelInfo, getModelPath);
    modelName = env->GetStringUTFChars(strModelName, 0);
    LOGI("[HIAI_DEMO_ASYNC] modelName is %s .", modelName);
    IF_BOOL_EXEC(modelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelName is invalid."); return nullptr);
    const char* modelPath = env->GetStringUTFChars(strModelPath, 0);
    IF_BOOL_EXEC(modelPath == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelPath is invalid."); return nullptr);

    // load
    IF_BOOL_EXEC(!mclientAsync, mclientAsync = LoadModelASync(modelPath); IF_BOOL_EXEC(
        mclientAsync == nullptr, LOGE("[HIAI_DEMO_ASYNC] mclientAsync loadModel is nullptr."); return nullptr));
    // load model
    LOGI("[HIAI_DEMO_ASYNC] appStart load model INPUT NCHW : %d %d %d %d.", inputDimension[0].GetNumber(),
        inputDimension[0].GetChannel(), inputDimension[0].GetHeight(), inputDimension[0].GetWidth());
    LOGI("[HIAI_DEMO_ASYNC] appStart load model OUTPUT NCHW : %d %d %d %d.", outputDimension[0].GetNumber(),
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

int runAsyncProcess(JNIEnv* env, jobject bufList, jmethodID listGet, int listLength)
{
    auto inputTensor0 = findInputTensor();
    for (int i = 0; i < listLength; i++) {
        jbyteArray buf_ = (jbyteArray)(env->CallObjectMethod(bufList, listGet, i));
        IF_BOOL_EXEC(buf_ == nullptr, LOGE("[HIAI_DEMO_ASYNC] buf_ is nullptr."); return FAILED);

        jbyte* dataBuff = nullptr;
        int databuffsize = 0;
        dataBuff = env->GetByteArrayElements(buf_, nullptr);
        databuffsize = env->GetArrayLength(buf_);
        IF_BOOL_EXEC((*inputTensor0)[i]->GetSize() != databuffsize,
                     LOGE("[HIAI_DEMO_ASYNC] input->GetSize(%d) != databuffsize(%d) ", (*inputTensor0)[i]->GetSize(),
                         databuffsize);
                     return FAILED);
        memcpy((*inputTensor0)[i]->GetBuffer(), dataBuff, (size_t)databuffsize);
        env->ReleaseByteArrayElements(buf_, dataBuff, 0);
    }

    AiContext context;
    string key = "model_name";
    string value = modelName;
    value += ".om";
    context.AddPara(key, value);
    LOGI("[HIAI_DEMO_ASYNC] JNI runModel modelname:%s", value.c_str());

    int istamp = 0;
    gettimeofday(&tpstart, nullptr);
    int ret = mclientAsync->Process(context, *inputTensor0, outputTensor, 300, istamp);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Runmodel Failed! ret=%d.", ret); return FAILED);
    LOGI("[HIAI_DEMO_ASYNC] Runmodel Succ! istamp=%d.", istamp);

    std::unique_lock<std::mutex> lock(g_mutexMap);
    g_mapInputTensor.insert(pair<int32_t, vector<shared_ptr<AiTensor>>*>(istamp, inputTensor0));
    g_condition.notify_all();

    return SUCCESS;
}

extern "C" JNIEXPORT void JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_runModelAsync(
    JNIEnv* env, jclass type, jobject modelInfo, jobject bufList, jobject callbacks)
{
    // check params
    IF_BOOL_EXEC(env == nullptr, LOGE("[HIAI_DEMO_ASYNC] runModelAsync env is null"); return);
    jclass ModelInfo = env->GetObjectClass(modelInfo);
    IF_BOOL_EXEC(ModelInfo == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find ModelInfo class."); return);
    jmethodID getOfflineModelName = env->GetMethodID(ModelInfo, "getOfflineModelName", "()Ljava/lang/String;");
    jmethodID getModelPath = env->GetMethodID(ModelInfo, "getModelPath", "()Ljava/lang/String;");
    IF_BOOL_EXEC(getOfflineModelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getOfflineModelName method.");
                 return);
    jstring strModelName = (jstring)env->CallObjectMethod(modelInfo, getOfflineModelName);
    jstring strModelPath = (jstring)env->CallObjectMethod(modelInfo, getModelPath);

    modelName = env->GetStringUTFChars(strModelName, 0);
    IF_BOOL_EXEC(modelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelName is invalid."); return);
    const char* modelPath = env->GetStringUTFChars(strModelPath, 0);
    IF_BOOL_EXEC(modelPath == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelPath is invalid."); return);
    // get the ArrayList class
    jclass classList = env->GetObjectClass(bufList);
    IF_BOOL_EXEC(classList == NULL, LOGE("[HIAI_DEMO_ASYNC] can not find List class."); return);
    // method in class
    jmethodID listGet = env->GetMethodID(classList, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(classList, "size", "()I");
    IF_BOOL_EXEC(listGet == NULL, LOGE("[HIAI_DEMO_ASYNC] can not find get method."); return);
    IF_BOOL_EXEC(listSize == NULL, LOGE("[HIAI_DEMO_ASYNC] can not find size method."); return);

    int listLength = static_cast<int>(env->CallIntMethod(bufList, listSize));
    IF_BOOL_EXEC(listLength > 0, LOGI("[HIAI_DEMO_ASYNC] input data length is %d .", listLength));

    callbacksInstance = env->NewGlobalRef(callbacks);
    jclass objClass = env->GetObjectClass(callbacks);
    IF_BOOL_EXEC(!objClass, LOGE("[HIAI_DEMO_ASYNC] objClass is nullptr."); return);

    env->GetJavaVM(&jvm);
    callbacksClass = reinterpret_cast<jclass>(env->NewGlobalRef(objClass));
    env->DeleteLocalRef(objClass);
    // load
    IF_BOOL_EXEC(!mclientAsync, mclientAsync = LoadModelASync(modelPath);
                 IF_BOOL_EXEC(mclientAsync == nullptr, LOGE("[HIAI_DEMO_ASYNC] mclientAsync is nullptr."); return ));
    // run
    LOGI("[HIAI_DEMO_ASYNC] INPUT NCHW : %d %d %d %d.", inputDimension[0].GetNumber(), inputDimension[0].GetChannel(),
        inputDimension[0].GetHeight(), inputDimension[0].GetWidth());
    LOGI("[HIAI_DEMO_ASYNC] OUTPUT NCHW : %d %d %d %d.", outputDimension[0].GetNumber(),
        outputDimension[0].GetChannel(), outputDimension[0].GetHeight(), outputDimension[0].GetWidth());

    IF_BOOL_EXEC(runAsyncProcess(env, bufList, listGet, listLength), return);

    env->ReleaseStringUTFChars(strModelName, modelName);
}
