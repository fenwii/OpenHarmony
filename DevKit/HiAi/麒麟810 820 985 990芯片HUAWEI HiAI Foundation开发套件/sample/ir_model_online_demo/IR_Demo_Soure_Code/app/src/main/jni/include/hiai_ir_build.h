/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: omg hiai ir build
 *
 */

#ifndef DOMI_OMG_HIAI_IR_BUILD_H_
#define DOMI_OMG_HIAI_IR_BUILD_H_
#include "graph/model.h"

namespace domi {
    struct ModelBufferData {
        void* data = nullptr;
        uint32_t length = 0;
    };
    class HiaiIrBuild {
    public:
        /**
         * @ingroup domi_omg
         * @brief 创建模型Buffer, 默认分配200M
         * @param [in] irModel 输入模型数据
         * @param [out] output 输出离线模型Buffer
         * @return bool 执行结果
         */
        bool CreateModelBuff(ge::Model& irModel, ModelBufferData& output);

        /**
         * @ingroup domi_omg
         * @brief 创建模型Buffer
         * @param [in] irModel 输入模型数据
         * @param [out] output 输出离线模型Buffer
         * @param [in] customSize 输入用户指定Buffer大小，单位字节，必须为非负整数，建议范围200M以内，当customSize设置为0时，接口内部根据irModel自动计算合适的Buffer大小
         * @return bool 执行结果
         */
        bool CreateModelBuff(ge::Model& irModel, ModelBufferData& output, uint32_t customSize);

        /*
         * @ingroup domi_omg
         * @brief 在线编译
         * @param [in] irModel 输入模型数据
         * @param [out] output 输出离线模型
         * @return bool 执行结果
         */
        bool BuildIRModel(ge::Model& irModel, ModelBufferData& output);

        void ReleaseModelBuff(ModelBufferData& output);
    private:
        /*
         * @ingroup domi_omg
         * @brief 获取Rom版本号
         * @return string IR在线编译返回Rom版本号，离线编译返回空字符串
         */
        std::string GetHiaiVersion();
        /*
         * @ingroup domi_omg
         * @brief 在线编译生成模型
         * @return bool 成功返回true，失败返回false
         */
        bool BuildModelOnline(const std::string& hiaiRomVersion,
            ge::ComputeGraphPtr graph, ge::Model& irModel, ModelBufferData& output);
        /*
         * @ingroup domi_omg
         * @brief 检查Rom版本是否支持IR量化模型
         * @return bool 成功返回true，失败返回false
         */
        bool IsSupportQuantize(const std::string& hiaiRomVersion);
        /*
         * @ingroup domi_omg
         * @brief 离线编译生成模型
         * @return bool 成功返回true，失败返回false
         */
        bool BuildModelOffline(const std::string& hiaiRomVersion,
            ge::ComputeGraphPtr graph, ge::Model& irModel, ModelBufferData& output);
    };
} // namespace domi
#endif // _H_HIAI_IR_BUILD_H_
