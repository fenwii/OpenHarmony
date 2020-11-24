/**
 *@file classify_async_jni.cpp
 *
 * Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <jni.h>
#include <string>
#include <memory.h>
#include "HiAiModelManagerService.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <unistd.h>

#define LOG_TAG "ASYNC_DDK_MSG"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
// 如果expr为true，则执行exec_expr，不打印日志
#define IF_BOOL_EXEC(expr, exec_expr) \
    { \
        if (expr) { \
            exec_expr; \
        } \
    }

using namespace std;
using namespace hiai;
static jclass callbacksClass;
static jobject callbacksInstance;
JavaVM* jvm;

static float time_use;
struct timeval tpstart, tpend;

static map<int32_t, vector<shared_ptr<AiTensor>>*> g_mapInputTensor;

static mutex g_mutexMap;
static condition_variable g_condition;

// extern bool g_isAIPP;
static const int SUCCESS = 0;
static const int FAILED = -1;

static map<string, int> g_asyncNameToIndex;

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
    if (result != 0) {
        LOGI("[HIAI_DEMO_ASYNC] AYSNC infrence error is %d.", result);
        return;
    }
    gettimeofday(&tpend, nullptr);
    time_use = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    LOGI("[HIAI_DEMO_ASYNC] AYSNC inference time %f ms, JNI layer onRunDone istamp: %d", time_use / 1000, istamp);
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
    jmethodID list_add = env->GetMethodID(outputListClass, "add", "(Ljava/lang/Object;)Z");
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
        jboolean output_add = env->CallBooleanMethod(outputList, list_add, result);
    }
    jfloat infertime = time_use;
    if (callbacksInstance == nullptr) {
        return;
    }
    jmethodID onValueReceived = env->GetMethodID(callbacksClass, "OnProcessDone", "(ILjava/util/ArrayList;F)V");
    if (onValueReceived == nullptr) {
        LOGI("[HIAI_DEMO_ASYNC] jni onValueReceived null");
    }
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
static vector<vector<TensorDimension>> inputDimension;
static vector<vector<TensorDimension>> outputDimension;
static vector<vector<shared_ptr<AiTensor>>> input_tensor1_vec;
static vector<vector<shared_ptr<AiTensor>>> input_tensor2_vec;
static vector<vector<shared_ptr<AiTensor>>> output_tensor_vec;

vector<shared_ptr<AiTensor>>* findInputTensor(int vecIdx)
{
    vector<shared_ptr<AiTensor>>& input_tensor1 = input_tensor1_vec[vecIdx];
    vector<shared_ptr<AiTensor>>& input_tensor2 = input_tensor2_vec[vecIdx];
    std::unique_lock<std::mutex> ulock(g_mutexMap);
    while (g_mapInputTensor.size() == 2) {
        g_condition.wait_for(ulock, chrono::seconds(1));
    }
    if (g_mapInputTensor.size() == 0) {
        return &input_tensor1;
    } else if (g_mapInputTensor.size() == 1) {
        map<int32_t, vector<shared_ptr<AiTensor>>*>::iterator ite;
        ite = g_mapInputTensor.begin();
        if (ite->second == &input_tensor1) {
            return &input_tensor2;
        } else {
            return &input_tensor1;
        }
    }
    return nullptr;
}

void AsyncResourceDestroy(shared_ptr<AiModelBuilder>& modelBuilder, vector<MemBuffer*>& memBuffers)
{
    if (modelBuilder == nullptr) {
        LOGE("[HIAI_DEMO_ASYNC] modelBuilder is null.");
        return;
    }

    for (auto tmpBuffer : memBuffers) {
        modelBuilder->MemBufferDestroy(tmpBuffer);
    }
    return;
}

shared_ptr<JNIListener> listener = make_shared<JNIListener>();

int LoadASync(vector<string>& names, vector<string>& modelPaths, shared_ptr<AiModelMngerClient>& client)
{
    int ret;
    vector<shared_ptr<AiModelDescription>> modelDescs;
    vector<MemBuffer*> memBuffers;
    shared_ptr<AiModelBuilder> modelBuilder = make_shared<AiModelBuilder>(client);
    if (modelBuilder == nullptr) {
        LOGE("[HIAI_DEMO_ASYNC] creat mcbuilder failed.");
        return FAILED;
    }

    for (size_t i = 0; i < modelPaths.size(); ++i) {
        string modelPath = modelPaths[i];
        string modelName = names[i];
        g_asyncNameToIndex[modelName] = i;
        // We can achieve the optimization by loading model from OM file.
        LOGI("[HIAI_DEMO_ASYNC] modelpath is %s\n.", modelPath.c_str());
        MemBuffer* buffer = modelBuilder->InputMemBufferCreate(modelPath);
        if (buffer == nullptr) {
            LOGE("[HIAI_DEMO_ASYNC] cannot find the model file.");
            return FAILED;
        }
        memBuffers.push_back(buffer);
        string modelNameFull = string(modelName) + string(".om");
        shared_ptr<AiModelDescription> desc =
            make_shared<AiModelDescription>(modelNameFull, AiModelDescription_Frequency_HIGH, HIAI_FRAMEWORK_NONE,
                HIAI_MODELTYPE_ONLINE, AiModelDescription_DeviceType_NPU);
        if (desc == nullptr) {
            LOGE("[HIAI_DEMO_ASYNC] LoadASync: desc make_shared error.");
            AsyncResourceDestroy(modelBuilder, memBuffers);
            return FAILED;
        }
        desc->SetModelBuffer(buffer->GetMemBufferData(), buffer->GetMemBufferSize());

        LOGE("[HIAI_DEMO_ASYNC] loadModel %s IO Tensor.", desc->GetName().c_str());
        modelDescs.push_back(desc);
    }

    ret = client->Load(modelDescs);
    AsyncResourceDestroy(modelBuilder, memBuffers);
    if (ret != 0) {
        LOGE("[HIAI_DEMO_ASYNC] Model Load Failed.");
        return FAILED;
    }
    return SUCCESS;
}

int UpdateAsyncInputTensorVec(vector<TensorDimension>& inputDims, bool isUseAipp, string& modelName)
{
    input_tensor1_vec.clear();
    input_tensor2_vec.clear();
    vector<shared_ptr<AiTensor>> inputTensors1, inputTensors2;
    int ret = FAILED;
    // input 1
    for (auto inDim : inputDims) {
        shared_ptr<AiTensor> input = make_shared<AiTensor>();
        if (isUseAipp) {
            ret = input->Init(inDim.GetNumber(), inDim.GetHeight(), inDim.GetWidth(), AiTensorImage_YUV420SP_U8);
            LOGI("[HIAI_DEMO_ASYNC] model %s uses AIPP(input1).", modelName.c_str());
        } else {
            ret = input->Init(&inDim);
            LOGI("[HIAI_DEMO_ASYNC] model %s does not use AIPP(input1).", modelName.c_str());
        }
        if (ret != 0) {
            LOGE("[HIAI_DEMO_ASYNC] model %s AiTensor Init failed(input1).", modelName.c_str());
            return FAILED;
        }
        inputTensors1.push_back(input);
    }
    input_tensor1_vec.push_back(inputTensors1);
    if (input_tensor1_vec.size() == 0) {
        LOGE("[HIAI_DEMO_ASYNC] input_tensor1_vec.size() == 0");
        return FAILED;
    }
    LOGE("[HIAI_DEMO_ASYNC] input_tensor1_vec.size %zu ", input_tensor1_vec.size());
    // input 2
    for (auto inDim : inputDims) {
        shared_ptr<AiTensor> input = make_shared<AiTensor>();
        if (isUseAipp) {
            ret = input->Init(inDim.GetNumber(), inDim.GetHeight(), inDim.GetWidth(), AiTensorImage_YUV420SP_U8);
            LOGI("[HIAI_DEMO_ASYNC] model %s uses AIPP(input2).", modelName.c_str());
        } else {
            ret = input->Init(&inDim);
            LOGI("[HIAI_DEMO_ASYNC] model %s does not use AIPP(input2).", modelName.c_str());
        }
        if (ret != 0) {
            LOGE("[HIAI_DEMO_ASYNC] model %s AiTensor Init failed(input2).", modelName.c_str());
            return FAILED;
        }
        inputTensors2.push_back(input);
    }
    input_tensor2_vec.push_back(inputTensors2);
    if (input_tensor2_vec.size() == 0) {
        LOGE("[HIAI_DEMO_ASYNC] input_tensor2_vec.size() == 0");
        return FAILED;
    }
    LOGE("[HIAI_DEMO_ASYNC] input_tensor2_vec.size %zu ", input_tensor2_vec.size());
    return SUCCESS;
}

int UpdateAsyncOutputTensorVec(vector<TensorDimension>& outputDims, string& modelName)
{
    output_tensor_vec.clear();
    vector<shared_ptr<AiTensor>> outputTensors;
    int ret = FAILED;
    // output
    for (auto out_dim : outputDims) {
        shared_ptr<AiTensor> output = make_shared<AiTensor>();
        ret = output->Init(&out_dim);
        if (ret != 0) {
            LOGE("[HIAI_DEMO_ASYNC] model %s AiTensor Init failed(output).", modelName.c_str());
            return FAILED;
        }
        outputTensors.push_back(output);
    }
    output_tensor_vec.push_back(outputTensors);
    // In this demo, model may has many output
    if (output_tensor_vec.size() == 0) {
        LOGE("[HIAI_DEMO_ASYNC] output_tensor_vec.size() == 0");
        return FAILED;
    }
    return SUCCESS;
}

shared_ptr<AiModelMngerClient> LoadModelASync(vector<string> names, vector<string> modelPaths, vector<bool> Aipps)
{
    shared_ptr<AiModelMngerClient> ptrClient = make_shared<AiModelMngerClient>();
    IF_BOOL_EXEC(ptrClient == nullptr, LOGE("[HIAI_DEMO_ASYNC] Model Manager Client make_shared error.");
                 return nullptr);
    int ret = ptrClient->Init(listener);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Model Manager Init Failed."); return nullptr);
    ret = LoadASync(names, modelPaths, ptrClient);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] LoadASync Failed."); return nullptr);

    inputDimension.clear();
    outputDimension.clear();
    for (size_t i = 0; i < names.size(); ++i) {
        string modelName = names[i];
        bool isUseAipp = Aipps[i];
        LOGI("[HIAI_DEMO_ASYNC] Get model %s IO Tensor. Use AIPP %d", modelName.c_str(), isUseAipp);
        vector<TensorDimension> inputDims, outputDims;
        ret = ptrClient->GetModelIOTensorDim(string(modelName) + string(".om"), inputDims, outputDims);
        IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Get Model IO Tensor Dimension failed,ret is %d.", ret);
                     return nullptr);
        IF_BOOL_EXEC(inputDims.size() == 0, LOGE("[HIAI_DEMO_ASYNC] inputDims.size() == 0"); return nullptr);
        inputDimension.push_back(inputDims);
        outputDimension.push_back(outputDims);
        // two identical input tensors for async runmodel
        IF_BOOL_EXEC(UpdateAsyncInputTensorVec(inputDims, isUseAipp, modelName) != SUCCESS, return nullptr);
        IF_BOOL_EXEC(UpdateAsyncOutputTensorVec(outputDims, modelName) != SUCCESS, return nullptr);
    }
    return ptrClient;
}

int setAsyncField(JNIEnv* env, int len, jobject& modelInfo, jmethodID listGet)
{
    for (int i = 0; i < len; i++) {
        jobject modelInfoObj = env->CallObjectMethod(modelInfo, listGet, i);
        jclass modelInfoClass = env->GetObjectClass(modelInfoObj);
        jfieldID inputIdN = env->GetFieldID(modelInfoClass, "input_N", "I");
        jfieldID inputIdC = env->GetFieldID(modelInfoClass, "input_C", "I");
        jfieldID inputIdH = env->GetFieldID(modelInfoClass, "input_H", "I");
        jfieldID inputIdW = env->GetFieldID(modelInfoClass, "input_W", "I");
        jfieldID inputNumber = env->GetFieldID(modelInfoClass, "input_Number", "I");
        env->SetIntField(modelInfoObj, inputIdN, inputDimension[i][0].GetNumber());
        env->SetIntField(modelInfoObj, inputIdC, inputDimension[i][0].GetChannel());
        env->SetIntField(modelInfoObj, inputIdH, inputDimension[i][0].GetHeight());
        env->SetIntField(modelInfoObj, inputIdW, inputDimension[i][0].GetWidth());
        env->SetIntField(modelInfoObj, inputNumber, inputDimension[i].size());

        jfieldID outputIdN = env->GetFieldID(modelInfoClass, "output_N", "I");
        jfieldID outputIdC = env->GetFieldID(modelInfoClass, "output_C", "I");
        jfieldID outputIdH = env->GetFieldID(modelInfoClass, "output_H", "I");
        jfieldID outputIdW = env->GetFieldID(modelInfoClass, "output_W", "I");
        jfieldID outputNumber = env->GetFieldID(modelInfoClass, "output_Number", "I");

        env->SetIntField(modelInfoObj, outputIdN, outputDimension[i][0].GetNumber());
        env->SetIntField(modelInfoObj, outputIdC, outputDimension[i][0].GetChannel());
        env->SetIntField(modelInfoObj, outputIdH, outputDimension[i][0].GetHeight());
        env->SetIntField(modelInfoObj, outputIdW, outputDimension[i][0].GetWidth());
        env->SetIntField(modelInfoObj, outputNumber, outputDimension[i].size());
    }

    return SUCCESS;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_loadModelAsync(
    JNIEnv* env, jclass type, jobject modelInfo)
{
    jclass classList = env->GetObjectClass(modelInfo);
    IF_BOOL_EXEC(classList == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find List class."); return nullptr);
    jmethodID listGet = env->GetMethodID(classList, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(classList, "size", "()I");
    int len = static_cast<int>(env->CallIntMethod(modelInfo, listSize));

    vector<string> names, modelPaths;
    vector<bool> aipps;
    for (int i = 0; i < len; i++) {
        jobject modelInfoObj = env->CallObjectMethod(modelInfo, listGet, i);
        jclass modelInfoClass = env->GetObjectClass(modelInfoObj);
        jmethodID getOfflineModelName = env->GetMethodID(modelInfoClass, "getOfflineModelName", "()Ljava/lang/String;");
        jmethodID getModelPath = env->GetMethodID(modelInfoClass, "getModelPath", "()Ljava/lang/String;");
        jmethodID getUseAIPP = env->GetMethodID(modelInfoClass, "getUseAIPP", "()Z");
        IF_BOOL_EXEC(getOfflineModelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getOfflineModelName method.");
                     return nullptr);
        IF_BOOL_EXEC(getModelPath == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getModelPath method.");
                     return nullptr);
        IF_BOOL_EXEC(getUseAIPP == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getUseAIPP method."); return nullptr);
        jboolean useaipp = (jboolean)env->CallBooleanMethod(modelInfoObj, getUseAIPP);
        jstring modelname = (jstring)env->CallObjectMethod(modelInfoObj, getOfflineModelName);
        jstring modelpath = (jstring)env->CallObjectMethod(modelInfoObj, getModelPath);
        const char* modelName = env->GetStringUTFChars(modelname, 0);
        LOGI("[HIAI_DEMO_ASYNC] modelName is %s .", modelName);
        IF_BOOL_EXEC(modelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelName is invalid."); return nullptr);
        const char* modelPath = env->GetStringUTFChars(modelpath, 0);
        IF_BOOL_EXEC(modelPath == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelPath is invalid."); return nullptr);
        LOGI("[HIAI_DEMO_ASYNC] useaipp is %d.", bool(useaipp == JNI_TRUE));
        aipps.push_back(bool(useaipp == JNI_TRUE));
        names.push_back(string(modelName));
        modelPaths.push_back(string(modelPath));
    }
    // load
    if (!mclientAsync) {
        mclientAsync = LoadModelASync(names, modelPaths, aipps);
        IF_BOOL_EXEC(mclientAsync == nullptr, LOGE("[HIAI_DEMO_ASYNC] mclientAsync loadModel is nullptr.");
                     return nullptr);
    }
    // load model
    LOGI("[HIAI_DEMO_ASYNC] sync load model INPUT NCHW : %d %d %d %d.", inputDimension[0][0].GetNumber(),
        inputDimension[0][0].GetChannel(), inputDimension[0][0].GetHeight(), inputDimension[0][0].GetWidth());
    LOGI("[HIAI_DEMO_ASYNC] sync load model OUTPUT NCHW : %d %d %d %d.", outputDimension[0][0].GetNumber(),
        outputDimension[0][0].GetChannel(), outputDimension[0][0].GetHeight(), outputDimension[0][0].GetWidth());
    setAsyncField(env, len, modelInfo, listGet);

    return modelInfo;
}

int runAsyncProcess(JNIEnv* env, jobject bufList, jmethodID listGet, int vecIndex, int listLength, const char* modelName)
{
    auto input_tensor0 = findInputTensor(vecIndex);
    for (int i = 0; i < listLength; i++) {
        jbyteArray buf_ = (jbyteArray)(env->CallObjectMethod(bufList, listGet, i));
        IF_BOOL_EXEC(buf_ == nullptr, LOGE("[HIAI_DEMO_ASYNC] buf_ is nullptr."); return FAILED);
        jbyte* dataBuff = nullptr;
        int databuffsize = 0;
        dataBuff = env->GetByteArrayElements(buf_, nullptr);
        databuffsize = env->GetArrayLength(buf_);
        if (((*input_tensor0)[i]->GetSize() != databuffsize)) {
            LOGE("[HIAI_DEMO_ASYNC] input->GetSize(%d) != databuffsize(%d) ", (*input_tensor0)[i]->GetSize(),
                databuffsize);
            return FAILED;
        }
        memmove((*input_tensor0)[i]->GetBuffer(), dataBuff, (size_t)databuffsize);
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
    int ret = mclientAsync->Process(context, *input_tensor0, output_tensor_vec[vecIndex], 300, istamp);
    IF_BOOL_EXEC(ret != SUCCESS, LOGE("[HIAI_DEMO_ASYNC] Runmodel Failed! ret=%d.", ret); return FAILED);
    LOGI("[HIAI_DEMO_ASYNC] Runmodel Succ! istamp=%d.", istamp);

    std::unique_lock<std::mutex> lock(g_mutexMap);
    g_mapInputTensor.insert(pair<int32_t, vector<shared_ptr<AiTensor>>*>(istamp, input_tensor0));
    g_condition.notify_all();

    return SUCCESS;
}

extern "C" JNIEXPORT void JNICALL Java_com_huawei_hiaidemo_utils_ModelManager_runModelAsync(
    JNIEnv* env, jclass type, jobject modelInfo, jobject bufList, jobject callbacks)
{
    IF_BOOL_EXEC(env == nullptr, LOGE("[HIAI_DEMO_ASYNC] runModelAsync env is null"); return);
    jclass ModelInfo = env->GetObjectClass(modelInfo);
    IF_BOOL_EXEC(ModelInfo == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find ModelInfo class."); return);
    IF_BOOL_EXEC(bufList == nullptr, LOGE("[HIAI_DEMO_ASYNC] bufList is null."); return);
    jmethodID getOfflineModelName = env->GetMethodID(ModelInfo, "getOfflineModelName", "()Ljava/lang/String;");
    jmethodID getModelPath = env->GetMethodID(ModelInfo, "getModelPath", "()Ljava/lang/String;");
    IF_BOOL_EXEC(getOfflineModelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getOfflineModelName method.");
                 return);
    IF_BOOL_EXEC(getModelPath == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find getModelPath method."); return);
    jstring modelname = (jstring)env->CallObjectMethod(modelInfo, getOfflineModelName);
    jstring modelpath = (jstring)env->CallObjectMethod(modelInfo, getModelPath);
    const char* modelName = env->GetStringUTFChars(modelname, 0);
    IF_BOOL_EXEC(modelName == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelName is invalid."); return);
    int vecIndex = g_asyncNameToIndex[modelName];
    const char* modelPath = env->GetStringUTFChars(modelpath, 0);
    IF_BOOL_EXEC(modelPath == nullptr, LOGE("[HIAI_DEMO_ASYNC] modelPath is invalid."); return);
    // buf_list
    jclass classList = env->GetObjectClass(bufList);
    IF_BOOL_EXEC(classList == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find List class."); return);
    // method in class
    jmethodID listGet = env->GetMethodID(classList, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(classList, "size", "()I");
    IF_BOOL_EXEC(listGet == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find get method."); return);
    IF_BOOL_EXEC(listSize == nullptr, LOGE("[HIAI_DEMO_ASYNC] can not find size method."); return);
    int listLength = static_cast<int>(env->CallIntMethod(bufList, listSize));
    IF_BOOL_EXEC(listLength > 0, LOGI("[HIAI_DEMO_ASYNC] input data length is %d .", listLength));
    callbacksInstance = env->NewGlobalRef(callbacks);
    jclass objClass = env->GetObjectClass(callbacks);
    IF_BOOL_EXEC(!objClass, LOGE("[HIAI_DEMO_ASYNC] objClass is nullptr."); return);
    env->GetJavaVM(&jvm);
    callbacksClass = reinterpret_cast<jclass>(env->NewGlobalRef(objClass));
    env->DeleteLocalRef(objClass);
    // load
    IF_BOOL_EXEC(!mclientAsync, LOGE("[HIAI_DEMO_ASYNC] mclientAsync is nullptr."); return);
    env->ReleaseStringUTFChars(modelpath, modelPath);
    // run
    LOGI("[HIAI_DEMO_ASYNC] INPUT NCHW : %d %d %d %d.", inputDimension[0][0].GetNumber(),
        inputDimension[0][0].GetChannel(), inputDimension[0][0].GetHeight(), inputDimension[0][0].GetWidth());
    LOGI("[HIAI_DEMO_ASYNC] OUTPUT NCHW : %d %d %d %d.", outputDimension[0][0].GetNumber(),
        outputDimension[0][0].GetChannel(), outputDimension[0][0].GetHeight(), outputDimension[0][0].GetWidth());

    IF_BOOL_EXEC(runAsyncProcess(env, bufList, listGet, vecIndex, listLength, modelName), return);

    env->ReleaseStringUTFChars(modelname, modelName);
}