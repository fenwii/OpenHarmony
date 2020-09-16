# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.16.5)

project(jsfwk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# compile options
add_compile_options(-fpermissive -Wno-narrowing)

set(ACE_LITE_CONFIG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/targets/simulator/win")
set(ACE_LITE_INNERKITS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../interfaces/innerkits/builtin")
set(JSFWK_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(JSFWK_INNERKITS_BUILTIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../foundation/ace/interfaces/innerkits/builtin")
set(JSFWK_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/core")
set(UIKIT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../foundation/graphic/lite")
set(THIRTY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_party")
set(JSFWK_SIMULATOR_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../tools/developer_tools_lite/graphic_tool/simulator")
set(JS_API_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../api/emui_band/MoltenCore/application/framework/ace/api")
set(AAFWK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../aafwk")

# add definitions
# temporarily set, when ui and graphic unifid, this can be removed
add_definitions(-DSCREENRESOLUTION_CMAKE)

# setup jerryscript
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(jerryscript
    SOURCE_DIR ${THIRTY_PATH}/jerryscript
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/jerryscript
    CMAKE_ARGS -DJERRY_EXTERNAL_CONTEXT=${JERRY_EXTERNAL_CONTEXT}
               -DJERRY_DEBUGGER=${JERRY_DEBUGGER}
               -DJERRY_CMDLINE=OFF
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DTOOLCHAIN_PATH=${TOOLCHAIN_PATH}
               -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    BUILD_COMMAND $(MAKE) VERBOSE=1 -j 8
    INSTALL_COMMAND ""
    BUILD_ALWAYS 1
)

# header files
include_directories(
    ${ACE_LITE_CONFIG_PATH}
    ${ACE_LITE_INNERKITS_PATH}/async
    ${ACE_LITE_INNERKITS_PATH}/base
    ${ACE_LITE_INNERKITS_PATH}/jsi
    ${JSFWK_INCLUDE_PATH}/async
    ${JSFWK_INCLUDE_PATH}/base
    ${JSFWK_INCLUDE_PATH}/context
    ${JSFWK_INCLUDE_PATH}/jsi
    ${JSFWK_SOURCE_PATH}
    ${JSFWK_SOURCE_PATH}/animation
    ${JSFWK_SOURCE_PATH}/base
    ${JSFWK_SOURCE_PATH}/components
    ${JSFWK_SOURCE_PATH}/context
    ${JSFWK_SOURCE_PATH}/directive
    ${JSFWK_SOURCE_PATH}/jsi
    ${JSFWK_SOURCE_PATH}/modules
    ${JSFWK_SOURCE_PATH}/modules/presets
    ${JSFWK_SOURCE_PATH}/router
    ${JSFWK_SOURCE_PATH}/stylemgr
    ${JSFWK_SOURCE_PATH}/wrapper
    ${CMAKE_CURRENT_SOURCE_DIR}/targets
    ${CMAKE_CURRENT_SOURCE_DIR}/test/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/test/unittest
    ${THIRTY_PATH}/cJSON
    ${THIRTY_PATH}/jerryscript/jerry-core/include
    ${THIRTY_PATH}/jerryscript/jerry-ext/include/jerryscript-ext
    ${THIRTY_PATH}/jerryscript/jerry-port/default/include
    ${THIRTY_PATH}/freetype/include
    ${JSFWK_SIMULATOR_PATH}/config
    ${JS_API_PATH}/timer
    ${AAFWK_PATH}/frameworks/abilitymgr_lite/include)

# source files
aux_source_directory(${JSFWK_SOURCE_PATH}/animation ANIMATION)
aux_source_directory(${JSFWK_SOURCE_PATH}/base BASE)
aux_source_directory(${JSFWK_SOURCE_PATH}/components COMPONENTS)
aux_source_directory(${JSFWK_SOURCE_PATH}/context CONTEXT)
aux_source_directory(${JSFWK_SOURCE_PATH}/directive DIRECTIVE)
aux_source_directory(${JSFWK_SOURCE_PATH}/jsi JSI)
aux_source_directory(${JSFWK_SOURCE_PATH}/modules MODULES)
aux_source_directory(${JSFWK_SOURCE_PATH}/modules/presets MODULES_PRESETS)
aux_source_directory(${JSFWK_SOURCE_PATH}/router ROUTER)
aux_source_directory(${JSFWK_SOURCE_PATH}/stylemgr STYLEMGR)
aux_source_directory(${JSFWK_SOURCE_PATH}/wrapper WRAPPER)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/targets TARGETS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test/unittest UNITTEST)

list(REMOVE_ITEM CONTEXT "${JSFWK_SOURCE_PATH}/context/ace_ability.cpp")
list(REMOVE_ITEM MODULES_PRESETS "${JSFWK_SOURCE_PATH}/modules/presets/jstest_module.cpp")
list(REMOVE_ITEM UNITTEST
    "${CMAKE_CURRENT_SOURCE_DIR}/test/unittest/tabs_tdd_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/unittest/js_async_work_tdd_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/unittest/message_queue_utils_tdd_test.cpp")

add_library(jsfwk STATIC
    ${ANIMATION}
    ${BASE}
    ${COMPONENTS}
    ${CONTEXT}
    ${DIRECTIVE}
    ${JSI}
    ${MODULES}
    ${MODULES_PRESETS}
    ${ROUTER}
    ${STYLEMGR}
    ${WRAPPER}
    ${TEST}
    ${TARGETS}
    )
target_include_directories(jsfwk PUBLIC
    ${JSFWK_INNERKITS_BUILTIN_PATH}
    ${JSFWK_INNERKITS_BUILTIN_PATH}/async
    ${JSFWK_INNERKITS_BUILTIN_PATH}/base
    ${JSFWK_INNERKITS_BUILTIN_PATH}/jsi
    ${JSFWK_INCLUDE_PATH}
    ${JSFWK_INCLUDE_PATH}/base
    ${JSFWK_INCLUDE_PATH}/context
    ${ACE_LITE_CONFIG_PATH}
    ${AAFWK_PATH}/frameworks/abilitymgr_lite/include)
add_dependencies(jsfwk jerryscript)
target_link_directories(jsfwk PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/jerryscript/lib)
target_link_libraries(jsfwk global_resmgr ui -Wl,--whole-archive jerry-port-default jerry-ext jerry-core -Wl,--no-whole-archive)

if (${JERRY_EXTERNAL_CONTEXT} STREQUAL ON)
    target_compile_definitions(jsfwk PUBLIC -DJS_ENGINE_EXTERNAL_CONTEXT)
endif()
