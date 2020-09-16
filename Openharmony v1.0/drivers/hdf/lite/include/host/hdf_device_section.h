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

#ifndef HDF_DEVICE_SECTION_H
#define HDF_DEVICE_SECTION_H

#if !defined(NON_HDF_DRIVER_SECTION)
#define USED_ATTR __attribute__((used))
#define HDF_SECTION __attribute__((section(".hdf.driver")))
#define HDF_DRIVER_INIT(module) \
    const size_t USED_ATTR module##HdfEntry HDF_SECTION = (size_t)(&(module))

#if (defined(__GNUC__) || defined(__clang__))
#define HDF_DRIVER_SEC_NAME(type, name) \
        ({ extern type name;            \
           &name;                       \
        })
#define HDF_DRIVER_BEGIN() HDF_DRIVER_SEC_NAME(size_t, _hdf_drivers_start)
#define HDF_DRIVER_END() HDF_DRIVER_SEC_NAME(size_t, _hdf_drivers_end)

#elif defined(__ICCARM__)
#define HDF_DRIVER_BEGIN() __section_begin(".hdf.driver")
#define HDF_DRIVER_END() __section_end(".hdf.driver")
#pragma section = ".hdf.driver"
#else
#error "No support section begin and section end!"
#endif /* defined(__GNUC__) || defined(__clang__) */
#endif /* NON_HDF_DRIVER_SECTION */

#endif /* HDF_DEVICE_SECTION_H */

