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

#include "source.h"

namespace OHOS {
namespace Media {
Source::Source(const std::string &uri)
    : uri_(uri),
      sourceType_(SourceType::SOURCE_TYPE_URI)
{}

Source::Source(const std::string &uri, const std::map<std::string, std::string> &header)
    : uri_(uri),
      sourceType_(SourceType::SOURCE_TYPE_URI),
      header_(header)
{}

Source::Source(const std::shared_ptr<StreamSource> &stream, const Format &formats)
    : sourceType_(SourceType::SOURCE_TYPE_STREAM),
      stream_(stream)
{
    format_.CopyFrom(formats);
}

SourceType Source::GetSourceType() const
{
    return sourceType_;
}

const std::string &Source::GetSourceUri() const
{
    return uri_;
}

const std::map<std::string, std::string> &Source::GetSourceHeader() const
{
    return header_;
}

const std::shared_ptr<StreamSource> &Source::GetSourceStream() const
{
    return stream_;
}
const Format &Source::GetSourceStreamFormat() const
{
    return format_;
}
}  // namespace Media
}  // namespace OHOS
