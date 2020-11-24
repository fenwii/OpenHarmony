/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: Basic Type Define
 */
#ifndef _HIAI_TYPE_H_
#define _HIAI_TYPE_H_
#include <stdint.h>
#include <map>
#include <string>

#ifndef HIAI_API_EXPORT
#if (defined HOST_VISIBILITY) || (defined DEV_VISIBILITY)
#ifdef _MSC_VER
#define HIAI_API_EXPORT __declspec(dllexport)
#else
#define HIAI_API_EXPORT __attribute__((__visibility__("default")))
#endif
#else
#define HIAI_API_EXPORT
#endif
#endif

namespace hiai {
class Context {
public:
    std::string GetValue(const std::string& key) const;
    void SetValue(const std::string& key, const std::string& value);
    void RemoveValue(const std::string& key);
    const std::map<std::string, std::string>& GetContent() const;

private:
    std::map<std::string, std::string> paras_;
};

inline std::string Context::GetValue(const std::string& key) const
{
    auto it = paras_.find(key);
    return it != paras_.end() ? it->second : "";
}

inline void Context::SetValue(const std::string& key, const std::string& value)
{
    paras_[key] = value;
}

inline void Context::RemoveValue(const std::string& key)
{
    paras_.erase(key);
}

inline const std::map<std::string, std::string>& Context::GetContent() const
{
    return paras_;
}

struct NativeHandle {
    int fd;
    int size;
    int offset;
};

}; // namespace hiai

#endif
