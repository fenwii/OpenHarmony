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

/**
 * @addtogroup Samgr
 * @{
 *
 * @brief Manages system capabilities.
 *
 * This module provides the development framework base of the service-oriented architecture (SOA).
 * You can develop your own abilities based on the Samgr development framework. \n
 * This module provides basic models of services, features, and functions, and registration and
 * discovery capabilities. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file iunknown.h
 *
 * @brief Provides the base class and default implementation for external functions of system capabilities.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_IUNKOWN_H
#define LITE_IUNKOWN_H

#include "common.h"
#include "ohos_errno.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct IUnknown IUnknown;

/**
 * @brief Defines the default IUnknown version. You can customize the version.
 *
 * The <b>IUnknown</b> interface of the default version can be called only in the current process.
 * Inter-process communication is not supported. \n
 *
 * @since 1.0
 * @version 1.0
 */
#define DEFAULT_VERSION 0x20

/**
 * @brief Defines the macro for inheriting the <b>IUnknown</b> interface.
 *
 * When developing a subclass of the <b>IUnknown</b> class, you can use this macro to inherit the
 * structures of the <b>IUnknown</b> interface. \n
 *
 */
#define INHERIT_IUNKNOWN                                                   \
    int (*QueryInterface)(IUnknown *iUnknown, int version, void **target); \
    int (*AddRef)(IUnknown *iUnknown);                                     \
    int (*Release)(IUnknown *iUnknown)

/**
 * @brief Defines the macro for inheriting the classes that implement the <b>IUnknown</b>
 * interface.
 *
 * When developing a subclass of a class that implements the <b>IUnknown</b> interface, you can use
 * this macro to inherit the structures of the <b>IUnknown</b> implementation class. \n
 *
 */
#define INHERIT_IUNKNOWNENTRY(T) \
    uint16 ver;                   \
    int16 ref;                   \
    T iUnknown

/**
 * @brief Defines the default marco for initializing the <b>IUnknown</b> interface.
 *
 * When creating a subclass object of the <b>IUnknown</b> interface, you can use this macro to
 * initialize members of the <b>IUnknown</b> interface to their default values. \n
 *
 */
#define DEFAULT_IUNKNOWN_IMPL                  \
    .QueryInterface = IUNKNOWN_QueryInterface, \
    .AddRef = IUNKNOWN_AddRef,                 \
    .Release = IUNKNOWN_Release

/**
 * @brief Defines the macro for initializing the classes that implement the <b>IUnknown</b>
 * interface.
 *
 * When creating a subclass object of a class that implements the <b>IUnknown</b> interface, you
 * can use this macro to initialize members of the <b>IUnknown</b> implementation class to their
 * default values. \n
 * You need to add the initialization of the customized member variable. \n
 *
 */
#define IUNKNOWN_ENTRY_BEGIN(version)   \
    .ver = (version),                   \
    .ref = 1,                           \
    .iUnknown = {                       \
        DEFAULT_IUNKNOWN_IMPL

/**
 * @brief IUnknown Defines the end macro for initializing the <b>IUnknown</b> implementation
 * object.
 *
 * This macro is used when a subclass object of the <b>IUnknown</b> implementation class is
 * initialized. \n
 *
 */
#define IUNKNOWN_ENTRY_END }

#define DEFAULT_IUNKNOWN_ENTRY_BEGIN IUNKNOWN_ENTRY_BEGIN(DEFAULT_VERSION)

#define DEFAULT_IUNKNOWN_ENTRY_END IUNKNOWN_ENTRY_END

/**
 * @brief Obtains the pointer of the <b>IUnknown</b> interface object from the subclass object T
 *  (generic macro) of the <b>IUnknown</b> implementation class.
 *
 * Use this macro when registering <b>IUnknown</b> interfaces with Samgr so that you can obtain
 * the interfaces from the subclass objects of different <b>IUnknown</b> implementation classes. \n
 *
 * @since 1.0
 * @version 1.0
 */
#define GET_IUNKNOWN(T) (IUnknown *)(&((T).iUnknown))

/**
 * @brief Defines the <b>IUnknown</b> class.
 *
 * You need to inherit this structure when developing a subclass of the <b>IUnknown</b> interface. \n
 *
 */
struct IUnknown {
    /**
     * Queries the subclass object of the <b>IUnknown</b> interface of a specified version
     * (downcasting).
     */
    int (*QueryInterface)(IUnknown *iUnknown, int version, void **target);
    /** Adds the reference count. */
    int (*AddRef)(IUnknown *iUnknown);
    /** Release the reference to an <b>IUnknown</b> interface. */
    int (*Release)(IUnknown *iUnknown);
};

/**
 * @brief Defines the <b>IUnknown</b> implementation class.
 *
 * You need to inherit this structure when developing a subclass of the <b>IUnknown</b>
 * implementation class. \n
 *
 * Each <b>IUnknown</b> interface must correspond to one or more <b>IUnknown</b> implementation
 * classes. \n
 *
 */
typedef struct IUnknownEntry {
    /** Version information of <b>IUnknown</b> interface. */
    uint16 ver;
    /** Reference count of <b>IUnknown</b> interface. */
    int16 ref;
    /**
     * Implementation of <b>IUnknown</b> interface, which is related to the specific definition
     * implementation.
     */
    IUnknown iUnknown;
} IUnknownEntry;

/**
 * @brief Increments the reference count in this <b>IUnknown</b> interface.
 *
 * This function is called in <b>QueryInterface</b>. Do not call this function in the
 * <b>IUnknown<b> interface. \n
 *
 * When the <b>QueryInterface</b> function is re-implemented, you need to call this function
 * in the new <b>QueryInterface</b>.
 *
 * The system does not provide a lock to protect functions. Therefore, you need to re-implement
 * functions if multiple developers are using them. \n
 *
 * @param iUnknown Indicates the pointer to the <b>IUnknown<b> interface object.
 * @return Indicates the number of objects that reference the <b>IUnknown<b> interface.
 *
 * @since 1.0
 * @version 1.0
 */
int IUNKNOWN_AddRef(IUnknown *iUnknown);

/**
 * @brief Queries the <b>IUnknown</b> interfaces of a specified version (downcasting).
 *
 * After obtaining the <b>IUnknown</b> interface object, the function caller uses
 * <b>QueryInterface</b> to convert the object to the required subclass type. \n
 * The system converts {@link DEFAULT_VERSION} into the subclass type required by the caller.
 * If the type conversion requirements cannot be met, you need to re-implement this function. \n
 *
 * @param iUnknown Indicates the pointer to the <b>IUnknown</b> interface.
 * @param version Indicates the version of the <b>IUnknown</b> interface object to be converted.
 * @param target Indicates the <b>IUnknown</b> subclass type required by the caller. This is an
 * output parameter.
 * @return Returns <b>EC_SUCCESS</b> if the conversion is successful; returns other error codes
 * if the conversion fails.
 *
 * @since 1.0
 * @version 1.0
 */
int IUNKNOWN_QueryInterface(IUnknown *iUnknown, int ver, void **target);

/**
 * @brief Releases a reference to an <b>IUnknown</b> interface that is no longer used.
 *
 * In the default implementation provided by the system, if the reference count is <b>0</b>,
 * the memory of the <b>IUnknown</b> interface object and implementation object is not released. \n
 *
 * If the memory of the <b>IUnknown</b> interface object and implementation object is dynamically
 * allocated, this function needs to be re-implemented. \n
 * If the reference count is <b>0</b>, the memory of the <b>IUnknown</b> interface object and
 * implementation object is released. \n
 *
 * @param iUnknown Indicates the pointer to the <b>IUnknown<b> interface object.
 * @return Indicates the number of <b>IUnknown<b> interface objects that are referenced after the
 * current reference is released.
 *
 * @since 1.0
 * @version 1.0
 */
int IUNKNOWN_Release(IUnknown *iUnknown);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_IUNKOWN_H
/** @} */
