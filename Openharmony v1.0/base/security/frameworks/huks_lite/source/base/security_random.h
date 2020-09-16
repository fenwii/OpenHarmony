/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SECURITY_RANDOM_H
#define SECURITY_RANDOM_H

/*
 * 描述: 返回安全随机数, 其范围为[0,2^32)
 * 参数: unsigned int *securityRandom用于保存生成的安全随机数
 * 返回值: 成功返回0, 失败返回非0值
 */
int HILINK_RND_Random(unsigned int *securityRandom);

/*
 * 描述: 返回安全随机数, 其范围为[0, upperBound)
 * 参数: unsigned int *securityRandom用于保存生成的安全随机数
         unsigned int upperBound为生成随机数的上限.upperBound必须>=2,否则会返回失败
 * 返回值: 成功返回0, 失败返回非0值
 */
int HILINK_RND_UniformRandom(unsigned int *securityRandom, unsigned int upperBound);

/*
 *  描述:    hilink_rand，返回随机数
 *  返回值: 0      无
 */
int hilink_rand(void);

#endif
