/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: securestl
 *
 */
#ifndef _SECURESTL_H_
#define _SECURESTL_H_
#include <memory>

namespace hiai {
template <typename T, typename... Ts>
std::shared_ptr<T> make_shared_nothrow(Ts&&... params)
{
    return std::shared_ptr<T>(new (std::nothrow) T(std::forward<Ts>(params)...));
}
}
#endif