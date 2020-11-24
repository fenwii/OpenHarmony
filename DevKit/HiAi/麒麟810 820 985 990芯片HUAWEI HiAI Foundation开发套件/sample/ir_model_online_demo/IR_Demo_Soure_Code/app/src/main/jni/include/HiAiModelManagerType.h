/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: ai model manager type define
 *
 */

#ifndef AI_MODEL_MANGER_TYPE_H
#define AI_MODEL_MANGER_TYPE_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "hiai_types.h"

#ifndef HIAI_API_EXPORT
# ifndef _MSC_VER
#  define HIAI_API_EXPORT __attribute__ ((__visibility__ ("default")))
# else
#  define HIAI_API_EXPORT __declspec(dllexport)
# endif
#endif

/* Dynamic aipp is supported since 100.320.010.010 */
#define AIPP_BASE_VERSION "100.320.010.010"

namespace hiai {
using AIStatus = int32_t;

/* Error Numbers */
static const AIStatus AI_SUCCESS = 0;
static const AIStatus AI_FAILED = 1;
static const AIStatus AI_NOT_INIT = 2;
static const AIStatus AI_INVALID_PARA = 3;
static const AIStatus AI_INVALID_API = 7;
static const AIStatus AI_INVALID_POINTER = 8;

enum AiModelDescription_Frequency {
    AiModelDescription_Frequency_LOW = 1,
    AiModelDescription_Frequency_MEDIUM = 2,
    AiModelDescription_Frequency_HIGH = 3,
    AiModelDescription_Frequency_EXTREME = 4,
};

enum AiModelDescription_DeviceType {
    AiModelDescription_DeviceType_NPU = 0,
    AiModelDescription_DeviceType_IPU = 1,
    AiModelDescription_DeviceType_MLU = 2,
    AiModelDescription_DeviceType_CPU = 3,
};

enum AiModelDescription_Framework {
    HIAI_FRAMEWORK_NONE = 0,
    HIAI_FRAMEWORK_TENSORFLOW,
    HIAI_FRAMEWORK_KALDI,
    HIAI_FRAMEWORK_CAFFE,
    HIAI_FRAMEWORK_TENSORFLOW_8BIT,
    HIAI_FRAMEWORK_CAFFE_8BIT,
};

enum AiModelDescription_ModelType{
    HIAI_MODELTYPE_ONLINE = 0,
    HIAI_MODELTYPE_OFFLINE
};

enum AiTensorImage_Format{
    AiTensorImage_YUV420SP_U8 = 0,
    AiTensorImage_XRGB8888_U8,
    AiTensorImage_YUV400_U8,
    AiTensorImage_ARGB8888_U8,
    AiTensorImage_YUYV_U8,
    AiTensorImage_YUV422SP_U8,
    AiTensorImage_AYUV444_U8,
    AiTensorImage_RGB888_U8,
    AiTensorImage_BGR888_U8,
    AiTensorImage_YUV444SP_U8,
    AiTensorImage_YVU444SP_U8,
    AiTensorImage_INVALID= 255,
};
enum HIAI_DataType{
    HIAI_DATATYPE_UINT8 = 0,
    HIAI_DATATYPE_FLOAT32 = 1,
    HIAI_DATATYPE_FLOAT16 = 2,
    HIAI_DATATYPE_INT32 = 3,
    HIAI_DATATYPE_INT8 = 4,
    HIAI_DATATYPE_INT16 = 5,
    HIAI_DATATYPE_BOOL = 6,
    HIAI_DATATYPE_INT64 = 7,
    HIAI_DATATYPE_UINT32 = 8,
    HIAI_DATATYPE_DOUBLE = 9,
};

class HIAI_API_EXPORT AiContext {
public:
    std::string GetPara(const std::string &key) const;
    void AddPara(const std::string &key, const std::string &value);
    void SetPara(const std::string &key, const std::string &value);
    void DelPara(const std::string &key);
    void ClearPara();
    AIStatus GetAllKeys(std::vector<std::string> &keys);
private:
    std::map<std::string, std::string>paras_;
};

class HIAI_API_EXPORT TensorDimension {
public:
    TensorDimension();
    virtual ~TensorDimension();

    /*
    * @brief Tensor初始化接口
    * @param [in] number 输入的Tensor的数量
    * @param [in] channel 输入的Tensor的通道数
    * @param [in] height 输入的Tensor的高度
    * @param [in] width 输入的Tensor的宽度
    * @return 无
    */
    TensorDimension(uint32_t number, uint32_t channel, uint32_t height, uint32_t weight);

    void SetNumber(const uint32_t number);
    uint32_t GetNumber() const;
    void SetChannel(const uint32_t channel);
    uint32_t GetChannel() const;
    void SetHeight(const uint32_t height);
    uint32_t GetHeight() const;
    void SetWidth(const uint32_t width);
    uint32_t GetWidth() const;
    bool IsEqual(const TensorDimension &dim);

private:
    uint32_t n{0};
    uint32_t c{0};
    uint32_t h{0};
    uint32_t w{0};
};

class AiTensorLegacy;
class HIAI_API_EXPORT AiTensor {
public:
    AiTensor();
    virtual ~AiTensor();

    /*
    * @brief Tensor初始化接口
    * @param [in] dim 输入tensor的尺寸结构信息
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus Init(const TensorDimension* dim);
    /*
    * @brief Tensor初始化接口
    * @param [in] dim 输入tensor的尺寸结构信息
    * @param [in] DataType数据类型
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus Init(const TensorDimension* dim, HIAI_DataType pdataType);
    /*
    * @brief Tensor初始化接口
    * @param [in] handle ION内存信息
    * @param [in] dim 输入tensor的尺寸结构信息
    * @param [in] DataType数据类型
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus Init(const NativeHandle& handle, const TensorDimension* dim, HIAI_DataType pdataType);
    /*
    * @brief Tensor初始化接口
    * @param [in] number 输入的Tensor的数量
    * @param [in] height 输入的Tensor的高度
    * @param [in] width 输入的Tensor的宽度
    * @param [in] format 输入图片的格式AiTensorImage_Format类型
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus Init(uint32_t number, uint32_t height, uint32_t width, AiTensorImage_Format format);

    /*
    * @brief 获取Tensor buffer地址接口
    * @return void* tensor buffer地址
    */
    virtual void *GetBuffer() const;

    /*
    * @brief 获取Tensor buffer内存大小
    * @return void* tensor buffer内存大小
    */
    virtual uint32_t GetSize() const;

    AIStatus SetTensorDimension(const TensorDimension* dim);

    TensorDimension GetTensorDimension() const;

    void *GetTensorBuffer() const;
private:
    AiTensor(const AiTensor&) = delete;
    AiTensor& operator=(const AiTensor&) = delete;

    AIStatus InitWithSize(uint32_t n, uint32_t c, uint32_t h, uint32_t w, uint32_t size);

private:
    std::shared_ptr<AiTensorLegacy> tensorLegacy_;
    void* buffer_{nullptr};
    uint32_t size_{0};
    TensorDimension tensorDimension_;
};

class HIAI_API_EXPORT AiModelDescription {
public:
    /*
    * @brief AiModelDescription初始化描述的构造函数
    * @param [in] pmodelName 模型名称
    * @param [in] frequency 算力要求等级：AiModelDescription_Frequency
    * @param [in] framework 模型平台类型：AiModelDescription_Framework
    * @param [in] pmodelType 模型类型：AiModelDescription_ModelType
    * @param [in] pdeviceType 设备类型：AiModelDescription_DeviceType
    */
    AiModelDescription(const std::string& pmodelName, const int32_t frequency, const int32_t framework,
        const int32_t pmodelType, const int32_t pdeviceType);
    virtual ~AiModelDescription();
    std::string GetName() const;
    void* GetModelBuffer() const;
    AIStatus SetModelBuffer(const void* data, uint32_t size);
    int32_t GetFrequency() const;
    int32_t GetFramework() const;
    int32_t GetModelType() const;
    int32_t GetDeviceType() const;
    uint32_t GetModelNetSize() const;

private:
    friend class ModelManagerClientImplLegacy;
    std::string model_name_;
    int32_t frequency_{0};
    int32_t framework_{0};
    int32_t modelType_{0};
    int32_t deviceType_{0};
    void *modelNetBuffer_{nullptr};
    uint32_t modelNetSize_{0};
    std::string modelNetKey_;
};

class HIAI_API_EXPORT AiModelManagerClientListener {
public:
    virtual ~AiModelManagerClientListener(){}

    virtual void OnProcessDone(const AiContext &context, int32_t result, const std::vector<std::shared_ptr<AiTensor>> &poutTensor, int32_t piStamp) = 0;
    virtual void OnServiceDied() = 0;
};

class HIAI_API_EXPORT MemBuffer {
public:
    /*
    * @brief 获取通用MEMBuffer的内存地址
    * @return MEMBuffer的内存地址
    */
    void* GetMemBufferData();

    /*
    * @brief 获取通用MEMBuffer的内存大小
    * @return MEMBuffer的内存大小
    */
    uint32_t GetMemBufferSize();

public:
    void *data_{nullptr};

private:
    friend class MembufferUtil;

    void SetMemBufferSize(uint32_t size);
    void SetMemBufferData(void* data);

    void SetServerMem(void *serverMem);
    void SetAppAllocFlag(bool isAppAlloc);

    void *GetServerMem();
    bool GetAppAllocFlag();

    uint32_t size_{0};
    void *servermem_{nullptr};
    bool isAppAlloc_{0};
};

} //end namespace hiai

#endif
