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
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ui_dump_dom_tree.h
 *
 * @brief Declares a function for exporting information about a Document Object Model (DOM) tree or DOM node.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef GRAPHIC_LITE_UI_DUMP_DOM_TREE_H
#define GRAPHIC_LITE_UI_DUMP_DOM_TREE_H

#include "graphic_config.h"
#include "heap_base.h"
#if ENABLE_DEBUG
#include "components/ui_view.h"
#include "cJSON.h"
#endif // ENABLE_DEBUG
namespace OHOS {
#if ENABLE_DEBUG
/**
 * @brief Enumerates export modes.
 */
enum DumpMode {
    /** DOM tree */
    DUMP_TREE,
    /** DOM node */
    DUMP_NODE
};
#endif // ENABLE_DEBUG

/**
 * @brief Provides functions for exporting information about a specified DOM node or information about the DOM tree
 * starting from a specified DOM node.
 *
 * @since 1.0
 * @version 1.0
 */
class UIDumpDomTree : public HeapBase {
public:
    /**
     * @brief Obtains an instance in singleton pattern.
     *
     * @return Returns the function instance for exporting DOM information.
     * @since 1.0
     * @version 1.0
     */
    static UIDumpDomTree* GetInstance()
    {
        static UIDumpDomTree instance;
        return &instance;
    }

    /**
     * @brief Exports information about a DOM tree starting from a specified DOM node and saves the information to
     * a specified path.
     *
     * @param id Indicates the pointer to the DOM node ID.
     * @param path Indicates the pointer to the specified path.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool DumpDomTree(const char* id, const char* path);

    /**
     * @brief Exports information about a DOM tree starting from a specified DOM node and saves the information to
     * the default path.
     * The default path is {@link DEFAULT_DUMP_DOM_TREE_PATH}.
     *
     * @param id Indicates the pointer to the DOM node ID.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool DumpDomTree(const char* id)
    {
        return DumpDomTree(id, nullptr);
    }

    /**
     * @brief Exports information about a specified DOM node.
     *
     * @param id Indicates the pointer to the DOM node ID.
     * @return Returns a character string about the DOM node information. The character string memory is released by
     * invoking <b>cJSON_free()</b>.
     * @since 1.0
     * @version 1.0
     */
    char* DumpDomNode(const char* id);

private:
#if ENABLE_DEBUG
    bool searchFlag_;     // Search flag, set when find the view with right id.
    bool allocErrorFlag_; // Alloc error flag, set when cJSON fails to allocate memory.
    char* pJson_;         // Pointer for returning cJSON string.
    cJSON* rootJson_;     // Root pointer of cJSON structure.
    const char* path_;

    void DumpJsonById(UIView* view, const char* id, DumpMode mode);

    void AddNameField(UIViewType type, cJSON* usr) const;
    void AddCommonField(UIView* view, cJSON* usr) const;
    void AddImageViewSpecialField(const UIView* view, cJSON* usr) const;
    void AddSpecialField(const UIView* view, cJSON* usr) const;
    void OutputDomNode(UIView* view);
    void OutputDomTree(UIView* view, cJSON* usr);
    bool WriteDumpFile() const;

    UIDumpDomTree() : searchFlag_(false), allocErrorFlag_(false), pJson_(nullptr),
        rootJson_(nullptr), path_(DEFAULT_DUMP_DOM_TREE_PATH) {}
#else
    UIDumpDomTree() {}
#endif // ENABLE_DEBUG
    virtual ~UIDumpDomTree() {}

    UIDumpDomTree(const UIDumpDomTree&) = delete;
    UIDumpDomTree& operator=(const UIDumpDomTree&) = delete;
    UIDumpDomTree(UIDumpDomTree&&) = delete;
    UIDumpDomTree& operator=(UIDumpDomTree&&) = delete;
};
}
#endif // GRAPHIC_LITE_UI_DUMP_DOM_TREE_H
