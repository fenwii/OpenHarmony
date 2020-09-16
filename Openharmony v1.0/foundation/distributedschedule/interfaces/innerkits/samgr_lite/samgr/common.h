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
 * @file common.h
 *
 * @brief Provides common objects and functions for Samgr and external modules.
 *
 *
 * This file provides simplified vector containers and downcast functions. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_COMMON_H
#define LITE_COMMON_H

#include "ohos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef void *MQueueId;
typedef void *MutexId;
typedef void *ThreadId;

/**
 * @brief Calculates the offset of the member in the T type.
 *
 *
 *
 * @param Indicates the T type.
 * @param member Indicates the name of the T member variable.
 *
 * @since 1.0
 * @version 1.0
 */
#define GET_OFFSIZE(T, member) (long)((char *)&(((T *)(0))->member))

/**
 * @brief Downcasts the pointer to the T type.
 *
 *
 *
 * @param Ptr Indicates the current pointer, which is the address of the T member variable.
 * @param T Indicates the target type of the downcast.
 * @param member Indicates the name of the {@code Ptr} as a T member variable.
 *
 * @since 1.0
 * @version 1.0
 */
#define GET_OBJECT(Ptr, T, member) (T *)(((char *)(Ptr)) - GET_OFFSIZE(T, member))

/**
 * @brief Indicates an invalid vector index. The value is <b>-1</b>.
 *
 * This macro indicates that the vector operation fails. \n
 * <b>INVALID_INDEX</b> is returned if an element cannot be found by {@link VECTOR_Find} or added
 * to <b>VECTOR_Add</b>.
 *
 */
#define INVALID_INDEX (-1)
typedef void *(*VECTOR_Key)(const void *);
typedef int (*VECTOR_Compare)(const void *, const void *);

/**
 * @brief Defines the simplified vector class, which is extended by four elements.
 *
 *
 * This class is applicable to the C language development scenario where the data volume is small
 * and dynamic expansion is required. \n
 *
 */
typedef struct SimpleVector {
    /** Maximum number of data records that can be stored. The initial value is <b>0</b>. */
    int16 max;
    /** Peak value of the number of stored data records. The initial value is <b>0</b>. */
    int16 top;
    /** Number of data records that have been released. The initial value is <b>0</b>. */
    int16 free;
    /** Data storage pointer */
    void **data;
    /**
     * Converts a data element into a key for comparison. The key is provided by users, and the
     * default value is <b>NULL</b>.
     */
    VECTOR_Key key;
    /**
     * Compares the sizes of key1 and key2, which are provided by users. The value <b>1</b>
     * indicates that key1 is greater than key2, the value <b>0</b> indicates that key1 is equal
     * to key2, and the value <b>-1</b> indicates that key1 is less than key2. The default value
     * is <b>NULL</b>.
     */
    VECTOR_Compare compare;
} Vector;

/**
 * @brief Creates or initializes a vector object.
 *
 * This function is used to create or initialize a vector object. \n
 *
 * @param key Indicates the pointer to the function provided by users for converting data elements
 * into key values. If this function is not provided, set it to <b>NULL</b>.
 * @param compare Indicates the pointer to the function for comparing the sizes of two elements.
 * If this function is not provided, set it to <b>NULL</b>.
 * @return Returns the vector right value object.
 * @since 1.0
 * @version 1.0
 */
Vector VECTOR_Make(VECTOR_Key key, VECTOR_Compare compare);

/**
 * @brief Destruct a vector object.
 *
 * This function is used to clear the memory applied by the vector after the temporary vector in
 * the stack is used. \n
 *
 * @param vector Indicates the pointer to the vector to clear.
 * @since 1.0
 * @version 1.0
 */
void VECTOR_Clear(Vector *vector);

/**
 * @brief Adds an element to the vector.
 *
 * This function is used to add an element to the vector. \n
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @param element Indicates the element to add.
 * @return Returns the location of the element to be added if the operation is successful; returns
 * {@link INVALID_INDEX} if the operation fails.
 * @since 1.0
 * @version 1.0 */
int16 VECTOR_Add(Vector *vector, void *element);

/**
 * @brief Obtains the number of elements in the vector, including elements that have been set to
 * <b>NULL</b>.
 *
 * This function is used for full traversal. \n
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @return Returns the top value of the vector, which indicates the number of elements.
 * @since 1.0
 * @version 1.0
 */
int16 VECTOR_Size(Vector *vector);

/**
 * @brief Obtains the number of valid elements in the vector, excluding elements that have been set
 * to <b>NULL</b>.
 *
 * This function is used to check whether the number of elements reaches the upper limit. \n
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @return Returns the top - free value of the vector, which indicates the number of non-null
 * elements.
 * @since 1.0
 * @version 1.0
 */
int16 VECTOR_Num(Vector *vector);

/**
 * @brief Obtains the element at a specified position.
 *
 * This function is used to obtain the element at a specified position.
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @param index Indicates the subscript to be obtained.
 * @return Returns the element if obtained; returns <b>NULL</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
void *VECTOR_At(Vector *vector, int16 index);

/**
 * @brief Swaps the element at a specified position in a vector with another element.
 *
 * This function is used to clear, sort, or update elements in the vector. \n
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @param index Indicates the position of the element to be swapped.
 * @param element Indicates the pointer to the new element.
 * @attention Before using this function, ensure that the index is valid. You can use
 * <b>VECTOR_Size</b> to obtain the upper limit of the index.
 * @return Returns the original element if the swapping is successful; returns <b>NULL</b>
 * if the swapping fails.
 * @see VECTOR_Size
 * @since 1.0
 * @version 1.0
 */
void *VECTOR_Swap(Vector *vector, int16 index, void *element);

/**
 * @brief Checks the position of an element.
 *
 * This function is used to check whether a vector has a specified element. \n
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @param element Indicates the element to be checked.
 * @return Returns the index of the element that is not less than 0 if the check is successful;
 * returns {@link INVALID_INDEX} if the check fails.
 * @since 1.0
 * @version 1.0
 */
int16 VECTOR_Find(Vector *vector, const void *element);

/**
 * @brief Checks the position of the element with a specified key.
 *
 * This function is used to check an element based on its key value. \n
 *
 * @param vector Indicates the <b>this</b> pointer to the vector.
 * @param key Indicates the pointer to the key value of the element to check.
 * @return Returns the index of the key element that is not less than 0 if the check is successful;
 * returns {@link INVALID_INDEX} if the check fails.
 * @since 1.0
 * @version 1.0
 */
int16 VECTOR_FindByKey(Vector *vector, const void *key);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_COMMON_H
/** @} */
