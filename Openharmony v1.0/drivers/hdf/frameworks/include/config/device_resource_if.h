/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup DriverConfig
 * @{
 *
 * @brief Defines an API for HDF driver developers to read driver configuration information.
 *
 * During version compilation of the device resource source file defined by developers, the compilation tool
 * (for example, the compilation tool of the HCS file is hc-gen) generates bytecodes. When the HDF starts,
 * it transfers the bytecode memory to the <b>DriverConfig</b> module. The <b>DriverConfig</b> module converts
 * the bytecodes into a configuration tree and provides an API for developers to query the tree.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file device_resource_if.h
 *
 * @brief Declares the API for querying the configuration tree.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef DEVICE_RESOURCE_IF_H
#define DEVICE_RESOURCE_IF_H

#include "hdf_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Enumerates configuration file types.
 */
typedef enum {
    HDF_CONFIG_SOURCE = 0,               /**< HDF configuration file */
    INVALID,                             /**< Invalid configuration file type */
} DeviceResourceType;

/**
 * @brief Defines the attributes of a tree node in the configuration tree.
 *
 * The tree node attributes are saved in a linked list. The information about each node in the linked list contains
 * the attribute name, attribute value, and pointer that points to the next attribute.
 */
struct DeviceResourceAttr {
    const char *name;                     /**< Pointer to the attribute name */
    const char *value;                    /**< Pointer to the attribute value */
    struct DeviceResourceAttr *next;      /**< Pointer to the next attribute of the node in the configuration tree. */
};

/**
 * @brief Defines a tree node in the configuration tree.
 *
 * The tree node information includes the node name, unique node ID, node attributes, parent node, child nodes,
 * and sibling nodes.
 */
struct DeviceResourceNode {
    const char *name;                      /**< Pointer to the node name */
    uint32_t hashValue;                    /**< Unique ID of a node */
    struct DeviceResourceAttr *attrData;   /**< Pointer to the node attributes */
    struct DeviceResourceNode *parent;     /**< Pointer to the parent node */
    struct DeviceResourceNode *child;      /**< Pointer to a child node */
    struct DeviceResourceNode *sibling;    /**< Pointer to a sibling node */
};

/**
 * @brief Provides functions for obtaining information about the device resource configuration tree.
 *
 * This structure provides functions for obtaining information about the device resource configuration tree,
 * including the root node, the <b>unit</b> attribute data, and the <b>String</b> attribute data.
 *
 * @since 1.0
 * @version 1.0
 */
struct DeviceResourceIface {
    /**
     * @brief Obtains the root node of the configuration tree.
     *
     * When the driver framework is started, a configuration tree is created. You can use this function to obtain
     * the root node of the configuration tree.
     *
     * @return Returns the root node of the configuration tree if the operation is successful;
     * returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    const struct DeviceResourceNode *(*GetRootNode)(void);
    /**
     * @brief Obtains the value of a <b>BOOL</b> attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the attribute.
     *
     * @return Returns the value of the <b>BOOL</b> attribute if the operation is successful;
     * returns <b>false</b> if <b>node</b> and <b>attrName</b> are null pointers.
     * @since 1.0
     * @version 1.0
     */
    bool (*GetBool)(const struct DeviceResourceNode *node, const char *attrName);
    /**
     * @brief Obtains the value of a <b>Uint8</b> attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the attribute.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the attribute value is obtained successfully; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint8)(const struct DeviceResourceNode *node, const char *attrName, uint8_t *value, uint8_t def);
    /**
     * @brief Obtains the value of a <b>Unit8</b> array attribute numbered <b>index</b> of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param index Indicates the number of the index (counting from 0) where the value is to obtain.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the array attribute value is obtained successfully; returns a negative value
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint8ArrayElem)(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
        uint8_t *value, uint8_t def);
    /**
     * @brief Obtains the values of a <b>Uint8</b> array attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param value Indicates the pointer to the array that stores the obtained data. The memory of the array is applied
     * by the user.
     * @param len Indicates the length of the array.
     * @param def Indicates the value to fill into <b>value</b> if the operation fails. If the obtained attribute value
     * contains 16-bit, 32-bit, or 64-bit data, the element corresponding to the 16-bit, 32-bit, or 64-bit data in the
     * array is filled using the value of <b>def</b>, and the other elements are filled with the actual value obtained.
     * If the failure is caused by other exceptions, the first element in the array is filled using the value of
     * <b>def</b>.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint8Array)(const struct DeviceResourceNode *node, const char *attrName, uint8_t *value, uint32_t len,
        uint8_t def);
    /**
     * @brief Obtains the value of a <b>Uint16</b> attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the attribute.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint16)(const struct DeviceResourceNode *node, const char *attrName, uint16_t *value, uint16_t def);
    /**
     * @brief Obtains the value of a <b>Uint16</b> array attribute numbered <b>index</b> of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param index Indicates the number of the index (counting from 0) where the value is to obtain.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint16ArrayElem)(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
        uint16_t *value, uint16_t def);
    /**
     * @brief Obtains the values of a <b>Uint16</b> array attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param value Indicates the pointer to the array that stores the obtained data. The memory of the array is applied
     * by the user.
     * @param len Indicates the length of the array.
     * @param def Indicates the value to fill into <b>value</b> if the operation fails. If the obtained attribute value
     * contains 32-bit or 64-bit data, the element corresponding to the 32-bit or 64-bit data in the array is filled
     * using the value of <b>def</b>, and the other elements are filled with the actual value obtained. If the failure
     * is caused by other exceptions, the first element in the array is filled using the value of <b>def</b>.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint16Array)(const struct DeviceResourceNode *node, const char *attrName, uint16_t *value,
        uint32_t len, uint16_t def);
    /**
     * @brief Obtains the value of a <b>Uint32</b> attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the attribute.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint32)(const struct DeviceResourceNode *node, const char *attrName, uint32_t *value, uint32_t def);
    /**
     * @brief Obtains the value of a <b>Uint32</b> array attribute numbered <b>index</b> of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param index Indicates the number of the index (counting from 0) where the value is to obtain.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint32ArrayElem)(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
        uint32_t *value, uint32_t def);
    /**
     * @brief Obtains the values of a <b>Uint32</b> array attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param value Indicates the pointer to an array that stores the obtained data.
     * @param len Indicates the pointer to the array that stores the obtained data. The memory of the array is applied
     * by the user.
     * @param def Indicates the value to fill into <b>value</b> if the operation fails. If the obtained attribute value
     * contains 64-bit data, the element corresponding to the 64-bit data in the array is filled using the value of
     * <b>def</b>, and the other elements are filled with the actual value obtained. If the failure is caused by other
     * exceptions, the first element in the array is filled using the value of <b>def</b>.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint32Array)(const struct DeviceResourceNode *node, const char *attrName, uint32_t *value,
        uint32_t len, uint32_t def);
    /**
     * @brief Obtains the value of a <b>Uint64</b> attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the attribute.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint64)(const struct DeviceResourceNode *node, const char *attrName, uint64_t *value, uint64_t def);
    /**
     * @brief Obtains the value of a <b>Uint64</b> array attribute numbered <b>index</b> of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param index Indicates the number of the index (counting from 0) where the value is to obtain.
     * @param value Indicates the pointer to the memory that stores the obtained data. The memory is applied
     * by the user.
     * @param def Indicates the value to fill into the memory pointed by <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint64ArrayElem)(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
        uint64_t *value, uint64_t def);
    /**
     * @brief Obtains the values of a <b>Uint64</b> array attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param value Indicates the pointer to the array that stores the obtained data. The memory of the array is applied
     * by the user.
     * @param len Indicates the length of the array.
     * @param def Indicates the value to fill into the first element in the <b>value</b> array if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetUint64Array)(const struct DeviceResourceNode *node, const char *attrName, uint64_t *value,
        uint32_t len, uint64_t def);
    /**
     * @brief Obtains the value of a <b>String</b> attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the attribute.
     * @param value Indicates the double pointer to the memory where the obtained data is stored. The string memory is
     * provided by the function implementer. Users only need to transfer the double pointer. The memory cannot be
     * released after being used.
     * @param def Indicates the value to be passed to <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetString)(const struct DeviceResourceNode *node, const char *attrName, const char **value,
        const char *def);
    /**
     * @brief Obtains the value of a <b>String</b> array attribute numbered <b>index</b> of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     * @param index Indicates the number of the index (counting from 0) where the value is to obtain.
     * @param value Indicates the double pointer to the memory where the obtained data is stored. The string memory is
     * provided by the function implementer. Users only need to transfer the double pointer. The memory cannot be
     * released after being used.
     * @param def def Indicates the value to be passed to <b>value</b> if the operation fails.
     *
     * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetStringArrayElem)(const struct DeviceResourceNode *node, const char *attrName, uint32_t index,
        const char **value, const char *def);
    /**
     * @brief Obtains the number of values for an array attribute of a configuration tree node.
     *
     * @param node Indicates the pointer to the configuration tree node.
     * @param attrName Indicates the pointer to the name of the array attribute.
     *
     * @return Returns the number of values for an array attribute if the operation is successful;
     * return a negative value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetElemNum)(const struct DeviceResourceNode *node, const char *attrName);
    /**
     * @brief Obtains a specified child node of the current tree node based on the value of a specific reserved
     * attribute (for example, the reserved attribute of the HCS is <b>match_attr</b>).
     *
     * There is a specific reserved attribute in the syntax of the device resource configuration source file.
     * If this attribute is set for a tree node, you can obtain the node based on the attribute value.
     * Users can set the attribute value based on the usage of their own nodes, but they must ensure that the attribute
     * values are unique.
     *
     * @param node Indicates the pointer to the node for whom a child node is to be obtained. The node can be the child
     * node's parent node or grandparent node.
     * @param attrValue Indicates the pointer to the value of the reserved attribute configured for the child node.
     *
     * @return Returns the target node if the operation is successful; returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    const struct DeviceResourceNode *(*GetNodeByMatchAttr)(const struct DeviceResourceNode *node,
        const char *attrValue);
    /**
     * @brief Obtains the child node with a specified node name from a parent node.
     *
     * @param node Indicates the pointer to the parent node.
     * @param nodeName Indicates the pointer to the name of the child node to obtain.
     *
     * @return Returns the child nodes if the operation is successful; returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    const struct DeviceResourceNode *(*GetChildNode)(const struct DeviceResourceNode *node, const char *nodeName);
    /**
     * @brief Obtains the node that is specified by a node-type attribute of a configuration tree node.
     *
     * If the attribute value is a configuration tree node, the path of the node is converted to a globally unique
     * <b>hashValue</b> when the device resource source file is compiled (for example, the compilation tool of the HCS
     * source file is hc-gen). For details about the <b>hashValue</b>, see {@link struct DeviceResourceNode}.
     * When you obtain a tree node using the node-type attribute, you obtain the <b>hashValue</b> through the node-type
     * attribute first, and then traverse the tree to obtain the tree node corresponding to the <b>hashValue</b>.
     *
     * @param node Indicates the pointer to the tree node whose attribute is to obtain.
     * @param attrName Indicates the pointer to the name of attribute whose value is a node path.
     * @return Returns the target node if the operation is successful; returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    const struct DeviceResourceNode *(*GetNodeByRefAttr)(const struct DeviceResourceNode *node, const char *attrName);
};

/**
 * @brief Obtains the device resource interface handle of the corresponding configuration tree type.
 *
 * You can use the obtained handle to use the device resource interface.
 *
 * @param type Indicates the type of the device resource interface handle to obtain.
 *
 * @return Returns the device resource interface handle if the operation is successful; returns <b>NULL</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
struct DeviceResourceIface *DeviceResourceGetIfaceInstance(DeviceResourceType type);

/**
 * @brief Traverses the attributes of the current configuration tree node.
 *
 * This operation is a <b>for</b> loop in essence.
 *
 * @param node Indicates the configuration tree node to traverse.
 * @param attr Indicates the traversed attributes.
 * @since 1.0
 * @version 1.0
 */
#define DEV_RES_NODE_FOR_EACH_ATTR(node, attr) \
    for ((attr) = (node)->attrData; (attr) != NULL; (attr) = (attr)->next)

/**
 * @brief Traverses the child nodes of the current configuration tree node.
 *
 * This operation is a <b>for</b> loop in essence.
 *
 * @param node Indicates the configuration tree node to traverse.
 * @param childNode Indicates the traversed child nodes.
 * @since 1.0
 * @version 1.0
 */
#define DEV_RES_NODE_FOR_EACH_CHILD_NODE(node, childNode) \
    for ((childNode) = (node)->child; (childNode) != NULL; (childNode) = (childNode)->sibling)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // DEVICE_RESOURCE_IF_H
/** @} */
