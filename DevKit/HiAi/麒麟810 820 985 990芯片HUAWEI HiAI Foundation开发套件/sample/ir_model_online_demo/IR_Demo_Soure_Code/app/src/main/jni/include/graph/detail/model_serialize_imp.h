/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: model_serialize_imp
 */

#include "anchor.h"
#include "graph.h"
#include "node.h"
#include "utils/type_utils.h"
#include "detail/attributes_holder.h"

#ifndef GE_MODEL_SERIALIZE_IMP_H
#define GE_MODEL_SERIALIZE_IMP_H

namespace ge {
using ComputeGraphPtr = std::shared_ptr<ComputeGraph>;

struct NodeNameGraphReq {
    string nodeName;
    int32_t index;
    ComputeGraphPtr graph;
};

struct NodeNameNodeReq {
    string srcNodeName;
    int32_t srcOutIndex;
    NodePtr dstNode;
    int32_t dstInIndex;
    string dstNodeName;
};

class ModelSerializeImp {
public:
    bool SerializeModel(const Model &model, proto::ModelDef *modeProto);

    bool SerializeGraph(const ConstComputeGraphPtr &graph, proto::GraphDef *graphProto);

    bool SerializeEdge(const NodePtr &node, proto::OpDef *opDefProto);

    bool SerializeOpDesc(const ConstOpDescPtr &node, proto::OpDef *opDefProto);

    bool SerializeNode(const NodePtr &node, proto::OpDef *opDefProto);

    bool UnserializeModel(Model &model, proto::ModelDef &modeProto);

    bool UnserializeGraphWithoutEdge(ComputeGraphPtr &graph, proto::GraphDef &graphProto);

    bool UnserializeGraph(ComputeGraphPtr &graph, proto::GraphDef &graphProto);

    bool HandleNodeNameRef();

    bool UnserializeOpDesc(OpDescPtr &opDesc, proto::OpDef &opDefProto);

    bool UnserializeNode(ComputeGraphPtr &graph, proto::OpDef &opDefProto);

    bool ParseNodeIndex(string nodeIndex, string &nodeName, int32_t &index);

    void SetProtobufOwner(const ProtoMsgOwner &bufferProtobufOnwer)
    {
        protobufOnwer_ = bufferProtobufOnwer;
    }

private:
    std::vector<NodeNameGraphReq> graphInputNodeNames_;
    std::vector<NodeNameGraphReq> graphOutputNodeNames_;
    std::vector<NodeNameNodeReq> nodeInputNodeNames_;
    std::map<string, NodePtr> nodeMap_;
    ProtoMsgOwner protobufOnwer_;
};
} // namespace ge

#endif // GE_MODEL_SERIALIZE_IMP_H
