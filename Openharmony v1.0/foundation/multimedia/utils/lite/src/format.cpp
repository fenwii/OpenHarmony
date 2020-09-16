/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "format.h"
#include <cstdio>

namespace OHOS {
namespace Media {
const char *CODEC_MIME = "mime";
const char *MIME_AUDIO_AAC = "audio/mp4a-latm";
const char *MIME_AUDIO_RAW = "audio/raw";

#define SET_INT32_FORMAT(type, func)   \
do { \
    type val;                    \
    if (formatData->func(val)) { \
        PutIntValue(key, val);     \
    } \
} while (0)

#define SET_INT64_FORMAT(type, func)   \
do { \
    type val;                    \
    if (formatData->func(val)) { \
        PutLongValue(key, val);     \
    } \
} while (0)

#define SET_FLOAT_FORMAT(type, func)   \
do { \
    type val;                    \
    if (formatData->func(val)) { \
        PutFloatValue(key, val);     \
    } \
} while (0)

#define SET_DOUBLE_FORMAT(type, func)   \
do { \
    type val;                    \
    if (formatData->func(val)) { \
        PutDoubleValue(key, val);     \
    } \
} while (0)

#define SET_STRING_FORMAT(type, func)   \
do { \
    type val;                    \
    if (formatData->func(val)) { \
        PutStringValue(key, val);     \
    } \
} while (0)

// For Class FormatData
FormatData::FormatData() : type_(FORMAT_TYPE_NONE), val_({ 0 })
{}

FormatData::FormatData(FormatDataType type) : type_(type), val_({ 0 })
{}

FormatData::~FormatData()
{
    if (type_ == FORMAT_TYPE_STRING) {
        if (val_.stringVal != nullptr) {
            delete val_.stringVal;
        }
    }
}

bool FormatData::SetValue(int32_t val)
{
    if (type_ != FORMAT_TYPE_INT32) {
        printf("FormatData set int32 value error, current type is %u", type_);
        return false;
    }
    val_.int32Val = val;
    return true;
}

bool FormatData::SetValue(int64_t val)
{
    if (type_ != FORMAT_TYPE_INT64) {
        printf("FormatData set int64 value error, current type is %u", type_);
        return false;
    }
    val_.int64Val = val;
    return true;
}

bool FormatData::SetValue(float val)
{
    if (type_ != FORMAT_TYPE_FLOAT) {
        printf("FormatData set float value error, current type is %u", type_);
        return false;
    }
    val_.floatVal = val;
    return true;
}

bool FormatData::SetValue(double val)
{
    if (type_ != FORMAT_TYPE_DOUBLE) {
        printf("FormatData set double value error, current type is %u", type_);
        return false;
    }
    val_.doubleVal = val;
    return true;
}

bool FormatData::SetValue(const std::string &val)
{
    if (type_ != FORMAT_TYPE_STRING) {
        printf("FormatData set string value error, current type is %u", type_);
        return false;
    }
    val_.stringVal = new (std::nothrow) std::string();
    if (val_.stringVal == nullptr) {
        type_ = FORMAT_TYPE_NONE;
        printf("FormatData set string value error, new string failed");
        return false;
    }
    *(val_.stringVal) = val;
    return true;
}

bool FormatData::GetInt32Value(int32_t &val) const
{
    if (type_ != FORMAT_TYPE_INT32) {
        printf("FormatData get int32 value error, current type is %u", type_);
        return false;
    }
    val = val_.int32Val;
    return true;
}

bool FormatData::GetInt64Value(int64_t &val) const
{
    if (type_ != FORMAT_TYPE_INT64) {
        printf("FormatData get int64 value error, current type is %u", type_);
        return false;
    }
    val = val_.int64Val;
    return true;
}

bool FormatData::GetFloatValue(float &val) const
{
    if (type_ != FORMAT_TYPE_FLOAT) {
        printf("FormatData get float value error, current type is %u", type_);
        return false;
    }
    val = val_.floatVal;
    return true;
}

bool FormatData::GetDoubleValue(double &val) const
{
    if (type_ != FORMAT_TYPE_DOUBLE) {
        printf("FormatData get double value error, current type is %u", type_);
        return false;
    }
    val = val_.doubleVal;
    return true;
}

bool FormatData::GetStringValue(std::string &val) const
{
    if (type_ != FORMAT_TYPE_STRING) {
        printf("FormatData get string value error, current type is %u", type_);
        return false;
    }
    if (val_.stringVal == nullptr) {
        printf("FormatData get string value error, stringVal is null");
        return false;
    }
    val = *(val_.stringVal);
    return true;
}

// For Class Format
Format::Format()
{}

Format::~Format()
{
    for (auto &iter : formatMap_) {
        if (iter.second != nullptr) {
            delete iter.second;
        }
    }
    formatMap_.clear();
}

bool Format::PutIntValue(const std::string &key, int32_t value)
{
    return SetFormatCommon(key, value, FORMAT_TYPE_INT32);
}

bool Format::PutLongValue(const std::string &key, int64_t value)
{
    return SetFormatCommon(key, value, FORMAT_TYPE_INT64);
}

bool Format::PutFloatValue(const std::string &key, float value)
{
    return SetFormatCommon(key, value, FORMAT_TYPE_FLOAT);
}

bool Format::PutDoubleValue(const std::string &key, double value)
{
    return SetFormatCommon(key, value, FORMAT_TYPE_DOUBLE);
}

bool Format::PutStringValue(const std::string &key, const std::string &value)
{
    return SetFormatCommon(key, value, FORMAT_TYPE_STRING);
}

template<typename T>
bool Format::SetFormatCommon(const std::string &key, const T &value, FormatDataType type)
{
    auto iter = formatMap_.find(key);
    if (iter != formatMap_.end()) {
        delete iter->second;
        iter->second = nullptr;
        formatMap_.erase(iter);
    }
    FormatData *data = new (std::nothrow) FormatData(type);
    if (data == nullptr) {
        printf("Format::SetFormatCommon new FormatData failed");
        return false;
    }
    if (!data->SetValue(value)) {
        printf("Format::SetFormatCommon failed. Key: %s", key.c_str());
        delete data;
        return false;
    }
    formatMap_[key] = data;
    return true;
}

bool Format::GetStringValue(const std::string &key, std::string &value) const
{
    auto iter = formatMap_.find(key);
    if (iter == formatMap_.end() || iter->second == nullptr) {
        printf("Format::GetFormat failed. Key: %s", key.c_str());
        return false;
    }

    return (*iter->second).GetStringValue(value);
}

bool Format::GetIntValue(const std::string &key, int32_t &value) const
{
    auto iter = formatMap_.find(key);
    if ((iter == formatMap_.end()) || (iter->second == nullptr)) {
        printf("Format::GetFormat failed. Key: %s", key.c_str());
        return false;
    }

    return (*iter->second).GetInt32Value(value);
}

bool Format::GetLongValue(const std::string &key, int64_t &value) const
{
    auto iter = formatMap_.find(key);
    if ((iter == formatMap_.end()) || (iter->second == nullptr)) {
        printf("Format::GetFormat failed. Key: %s", key.c_str());
        return false;
    }

    return (*iter->second).GetInt64Value(value);
}

bool Format::GetFloatValue(const std::string &key, float &value) const
{
    auto iter = formatMap_.find(key);
    if ((iter == formatMap_.end()) || (iter->second == nullptr)) {
        printf("Format::GetFormat failed. Key: %s", key.c_str());
        return false;
    }

    return (*iter->second).GetFloatValue(value);
}

bool Format::GetDoubleValue(const std::string &key, double &value) const
{
    auto iter = formatMap_.find(key);
    if ((iter == formatMap_.end()) || (iter->second == nullptr)) {
        printf("Format::GetFormat failed. Key: %s", key.c_str());
        return false;
    }

    return (*iter->second).GetDoubleValue(value);
}

const std::map<std::string, FormatData *> &Format::GetFormatMap() const
{
    return formatMap_;
}

bool Format::CopyFrom(const Format &format)
{
    printf("CopyFrom begin");
    std::map<std::string, FormatData *> formatMap = format.GetFormatMap();
    for (auto &iter : formatMap) {
        std::string key = iter.first;
        FormatData *formatData = iter.second;
        if (formatData == nullptr) {
            printf("CopyFrom FormatData is null, key is %s", key.c_str());
            continue;
        }
        FormatDataType type = formatData->GetType();
        switch (type) {
            case FORMAT_TYPE_INT32: {
                SET_INT32_FORMAT(int32_t, GetInt32Value);
                break;
            }
            case FORMAT_TYPE_INT64: {
                SET_INT64_FORMAT(int64_t, GetInt64Value);
                break;
            }
            case FORMAT_TYPE_FLOAT: {
                SET_FLOAT_FORMAT(float, GetFloatValue);
                break;
            }
            case FORMAT_TYPE_DOUBLE: {
                SET_DOUBLE_FORMAT(double, GetDoubleValue);
                break;
            }
            case FORMAT_TYPE_STRING: {
                SET_STRING_FORMAT(std::string, GetStringValue);
                break;
            }
            default: {
                printf("CopyFrom unknown type, type is %d", type);
                break;
            }
        }
    }
    return true;
}
}  // namespace Media
}  // namespace OHOS
