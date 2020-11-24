/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: attributes_holder
 */

#ifndef GE_ATTRIBUTES_HOLDER_H
#define GE_ATTRIBUTES_HOLDER_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include "../debug/ge_error_codes.h"
namespace google {
namespace protobuf {
class MessageLite;

template <typename Key, typename T>
class Map;
} // namespace protobuf
} // namespace google

namespace ge {
using std::string;

class AttrValue;

namespace proto {
class AttrDef;

class TensorDef;

class TensorDescriptor;

class ShapeDef;

class NamedAttrs;

class ModelDef;

class OpDef;

class GraphDef;
} // namespace proto

using ProtoAttrMap = ::google::protobuf::Map<::std::string, ::ge::proto::AttrDef>;
using ProtoMsgOwner = std::shared_ptr<::google::protobuf::MessageLite>;

template <class ProtoType>
class GeIrProtoHelper {
public:
    GeIrProtoHelper(const ProtoMsgOwner &protoOwner, ProtoType *protoMsg)
            : protoOwner_(protoOwner),
              protoMsg_(protoMsg) {}

    GeIrProtoHelper()
    {
        protoOwner_ = std::shared_ptr<::google::protobuf::MessageLite>(nullptr);
        protoMsg_ = nullptr;
    }

    virtual ~GeIrProtoHelper() = default;

    template <typename T>
    GeIrProtoHelper(const GeIrProtoHelper<T> &other)
    {
        protoOwner_ = other.protoOwner_;
        protoMsg_ = other.protoMsg_;
    }

    template <typename T>
    GeIrProtoHelper &operator = (const GeIrProtoHelper<T> &other)
    {
        protoOwner_ = other.protoOnwer_;
        protoMsg_ = other.protoMsg_;
        return *this;
    }

    void InitDefault();

    template <typename T>
    bool operator == (const GeIrProtoHelper<T> &other) const
    {
        return protoOwner_ == other.protoOwner_ && protoMsg_ == other.protoMsg_;
    }

    inline const ProtoMsgOwner &GetProtoOwner() const
    {
        return protoOwner_;
    }

    inline ProtoType *GetProtoMsg() const
    {
        return protoMsg_;
    }

    void CopyValueFrom(const GeIrProtoHelper<ProtoType> &other)
    {
        if (other.protoMsg_ != nullptr && protoMsg_ != nullptr) {
            *protoMsg_ = *other.protoMsg_;
        }
    }

    void MoveValueFrom(GeIrProtoHelper<ProtoType> &&other)
    {
        if (other.protoMsg_ != nullptr && protoMsg_ != nullptr) {
            *protoMsg_ = std::move(*other.protoMsg_);
        }
    }

public:
    ProtoMsgOwner protoOwner_ = nullptr;
    ProtoType *protoMsg_ = nullptr;

    friend class GeIrProtoHelper<typename std::conditional<std::is_const<ProtoType>::value,
        typename std::remove_const<ProtoType>::type, const ProtoType>::type>;
};

using ProtoAttrMapHelper = GeIrProtoHelper<ProtoAttrMap>;
using ConstProtoAttrMapHelper = GeIrProtoHelper<const ProtoAttrMap>;

class GE_FUNC_DEV_VISIBILITY GE_FUNC_HOST_VISIBILITY AttrHolder {
public:
    AttrHolder() = default;

    virtual ~AttrHolder() = default;

    GraphErrCodeStatus SetAttr(const string &name, const AttrValue &value);

    GraphErrCodeStatus GetAttr(const string &name, AttrValue &value) const;

    bool HasAttr(const string &name) const;

    GraphErrCodeStatus DelAttr(const string &name);

protected:
    GraphErrCodeStatus AddRequiredAttr(const std::string &name);

    const std::unordered_set<string> GetAllAttrNames() const;

    const std::map<string, AttrValue> GetAllAttrs() const;
protected:
    virtual ProtoAttrMapHelper MutableAttrMap() = 0;

    virtual ConstProtoAttrMapHelper GetAttrMap() const = 0;

    friend class ModelSerializeImp;

    friend class AttrUtils;

    friend class AttrUtilsHelper;

    std::vector<string> requiredAttrs_;
};
} // namespace ge

#endif // GE_ATTRIBUTES_HOLDER_H
