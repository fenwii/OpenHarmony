/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: ai model manager service
 *
 */

#ifndef AI_MODEL_MANGER_SERVICE_H
#define AI_MODEL_MANGER_SERVICE_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include "HiAiModelManagerType.h"
#include "HiAiAippPara.h"

namespace hiai {
class AiModelMngerClientImpl;
class ModelBuilderImplLegacy;
class AiModelMngerClient;
class AiModelBuilderImpl;
class HIAI_API_EXPORT AiModelBuilder {
public:
    AiModelBuilder(std::shared_ptr<AiModelMngerClient> client = nullptr);

    virtual ~AiModelBuilder();

    /*
    * @brief OM离线模型在线编译接口
    * @param [in] pinputMemBuffer 输入的OM离线模型buffer
    * @param [in] poutputModelBuffer 输出模型buffer
    * @param [out] poutputModelSize 输出模型大小
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus BuildModel(const std::vector<MemBuffer *> &pinputMemBuffer, MemBuffer *poutputModelBuffer,
                        uint32_t &poutputModelSize);

    /*
    * @brief 从文件读取OM离线模型proto信息
    * @param [in] path, 模型文件路径
    * @return MemBuffer * proto信息存储地址
    * @return nullptr 获取失败
    */
    MemBuffer* ReadBinaryProto(const std::string path);

    /*
    * @brief 从内存读取OM离线模型proto信息
    * @param [in] data, OM离线模型内存地址
    * @param [in] size, OM离线模型内存存储大小
    * @return MemBuffer * proto信息存储地址
    * @return nullptr 获取失败
    */
    MemBuffer* ReadBinaryProto(void* data, uint32_t size);

    /*
    * @brief 为输入OM离线模型用户内存buffer创建通用MemBuffer
    * @param [in] data, 模型用户内存地址
    * @param [in] size, 模型内存存储大小
    * @return MemBuffer * proto信息存储地址
    * @return nullptr 获取失败
    */
    MemBuffer* InputMemBufferCreate(void *data, uint32_t size);

    /*
    * @brief 为输入OM离线模型从文件创建MemBuffer
    * @param [in] path 文件路径
    * @return MemBuffer * 创建的输入MemBuffer内存指针
    * @return nullptr 创建失败
    */
    MemBuffer* InputMemBufferCreate(const std::string path);

    /*
    * @brief 为在线编译输出模型创建MemBuffer
    * @param [in] framework 模型平台类型
    * @param [in] pinputMemBuffer 输入的OM离线模型buffer
    * @return MemBuffer * 创建的输出模型MemBuffer内存指针
    * @return nullptr 创建失败
    */
    MemBuffer* OutputMemBufferCreate(const int32_t framework, const std::vector<MemBuffer *> &pinputMemBuffer);
    /*
    * @brief 注销MemBuffer内存，通过上述MemBuffer申请的内存最终都需要由此接口进行释放
    * @param [in] membuf, 创建的MemBuffer内存
    * @return void
    */
    void MemBufferDestroy(MemBuffer *membuf);

    /*
    * @brief 将模型buffer导出到文件
    * @param [in] membuf, 存储离线模型信息内存指针
    * @param [in] pbuildSize, 离线模型大小
    * @param [in] pbuildPath, 离线模型导出文件存储路径
    * @return AIStatus::AI_SUCCESS 导出成功
    * @return Others 导出失败
    */
    AIStatus MemBufferExportFile(MemBuffer *membuf, const uint32_t pbuildSize, const std::string pbuildPath);

private:
    std::shared_ptr<AiModelBuilderImpl> builderImpl_;
};

class HIAI_API_EXPORT AiModelMngerClient {
public:
    AiModelMngerClient();
    virtual ~AiModelMngerClient();

    /*
    * @brief 初始化接口
    * @param [in] listener 监听接口, 设置为nullptr时为同步调用, 否则为异步
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus Init(std::shared_ptr<AiModelManagerClientListener> listener);

    /*
    * @brief 加载模型
    * @param [in] pmodelDesc 模型信息
    * @param [in] piStamp 异步返回标识，基于该标识和模型名称做回调索引
    * @return AIStatus::AI_SUCCESS 成功
    * @return AIStatus::AI_INVALID_API 失败，表示设备不支持NPU
    * @return Others 失败
    */
    AIStatus Load(std::vector<std::shared_ptr<AiModelDescription>> &pmodelDesc);

    /*
    * @brief 模型处理接口, 运行加载模型的模型推理
    * @param [in] context, 模型运行上下文, 必须带model_name字段
    * @param [in] pinputTensor, 模型输入节点tensor信息
    * @param [in] poutputTensor, 模型输出节点tensor信息
    * @param [in] timeout, 推理超时时间
    * @param [in] piStamp 异步返回标识，基于该标识和模型名称做回调索引
    * @return AIStatus::AI_SUCCESS 成功
    * @return Others 失败
    */
    AIStatus Process(AiContext &context, std::vector<std::shared_ptr<AiTensor>> &pinputTensor, std::vector<std::shared_ptr<AiTensor>> &poutputTensor, uint32_t timeout, int32_t &piStamp);

    /*
    * @brief 模型兼容性检查接口
    * @param [in] pmodelDesc, 模型描述
    * @param [out] pisModelCompatibility, 兼容性检查标识
    * @return AIStatus::AI_SUCCESS 兼容性检查通过
    * @return Others 兼容性检查失败
    */
    AIStatus CheckModelCompatibility(AiModelDescription &pmodelDesc, bool &pisModelCompatibility);

    /*
    * @brief 获取模型输入输出tensor信息
    * @param [in] pmodelName, 模型名
    * @param [out] pinputTensor 输出参数, 存储模型输入节点tensor信息
    * @param [out] poutputTensor 输出参数, 存储模型输出节点tensor信息
    * @return AIStatus::AI_SUCCESS 获取成功
    * @return Others 获取失败
    */
    AIStatus GetModelIOTensorDim(const std::string& pmodelName, std::vector<TensorDimension>& pinputTensor, std::vector<TensorDimension>& poutputTensor);

    /*
    * @brief 获取模型AIPP 配置信息
    * @param [in] pmodelName, 模型名
    * @param [out] aippPara 输出参数, 模型中的AIPP配置参数
    * @return AIStatus::AI_SUCCESS 获取成功
    * @return Others 获取失败
    */
    AIStatus GetModelAippPara(const std::string& modelName, std::vector<std::shared_ptr<AippPara>>& aippPara);

    /*
    * @brief 获取模型对应输入的AIPP 配置信息
    * @param [in] pmodelName, 模型名
    * @param [in] index, 输入下标
    * @param [out] aippPara 输出参数, 模型对应输入的AIPP配置参数
    * @return AIStatus::AI_SUCCESS 获取成功
    * @return Others 获取失败
    */
    AIStatus GetModelAippPara(const std::string& modelName, uint32_t index, std::vector<std::shared_ptr<AippPara>>& aippPara);

    /*
    * @brief 获取DDK版本
    * @return char * DDK版本
    * @return nullptr 获取失败
    */
    char * GetVersion();

    /*
    * @brief 卸载模型
    * @return AIStatus::AI_SUCCESS 卸载成功
    * @return Others 卸载失败
    */
    AIStatus UnLoadModel();
private:
    friend class ModelBuilderImplLegacy;
    friend class AiModelBuilderImpl;
    std::shared_ptr<AiModelMngerClientImpl> clientImpl_;
};

} //end namespace hiai

#endif
