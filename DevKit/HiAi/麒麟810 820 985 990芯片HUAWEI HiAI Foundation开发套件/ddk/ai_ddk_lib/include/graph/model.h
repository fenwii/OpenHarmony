/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: model
 */

#ifndef GE_MODEL_H
#define GE_MODEL_H

#include <string>
#include <vector>
#include <map>
#include "graph.h"
#include "attr_value.h"
#include "detail/attributes_holder.h"

namespace ge {
using std::map;
using std::string;
using std::vector;

class GE_FUNC_DEV_VISIBILITY GE_FUNC_HOST_VISIBILITY Model : public AttrHolder {
public:
    Model();

    ~Model() = default;

    explicit Model(const string &name, const string &customVersion);

    string GetName() const;

    void SetName(const string &name);

    uint32_t GetVersion() const;

    void SetVersion(uint32_t version)
    {
        version_ = version;
    }

    std::string GetPlatformVersion() const;

    void SetPlatformVersion(string version)
    {
        platform_version_ = version;
    }

    Graph GetGraph() const;

    void SetGraph(const Graph &graph);

    using AttrHolder::GetAllAttrNames;
    using AttrHolder::GetAllAttrs;
    using AttrHolder::GetAttr;
    using AttrHolder::HasAttr;
    using AttrHolder::SetAttr;

    GraphErrCodeStatus Save(Buffer &buffer) const;

    // model will be rewrite
    static GraphErrCodeStatus Load(const uint8_t *data, size_t len, Model &model);

    bool IsValid() const;

private:
    void Init();

private:
    ProtoAttrMapHelper MutableAttrMap() override;

    ConstProtoAttrMapHelper GetAttrMap() const override;

    ProtoAttrMapHelper attrs_;

    friend class ModelSerializeImp;

    friend class GraphDebugImp;

    string name_;
    uint32_t version_;
    std::string platform_version_{ "" };
    Graph graph_;
};

} // namespace ge

#endif // GE_MODEL_H
