/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: graph
 */

#ifndef GE_GRAPH_H
#define GE_GRAPH_H

#include <memory>
#include "operator.h"

namespace ge {
class GraphImpl;

using GraphImplPtr = std::shared_ptr<GraphImpl>;

class GE_FUNC_HOST_VISIBILITY GE_FUNC_DEV_VISIBILITY Graph {
    friend class GraphUtils;

public:
    explicit Graph(const std::string &name);

    Graph() = default;

    ~Graph() = default;

    Graph &SetInputs(std::vector<Operator> &inputs);

    Graph &SetOutputs(std::vector<Operator> &outputs);

    bool IsValid() const;

    GraphErrCodeStatus AddOp(ge::Operator &op);

    ge::Operator FindOpByName(const string &name) const;

    GraphErrCodeStatus CheckOpByName(const string &name) const;

    GraphErrCodeStatus GetAllOpName(std::vector<string> &opName) const;

private:
    GraphImplPtr impl_{ nullptr };
};
} // namespace ge

#endif // GE_MODEL_H
