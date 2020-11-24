#@file build.gradle
#
# Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)
set(libs "${CMAKE_SOURCE_DIR}/libs")
include_directories(${CMAKE_SOURCE_DIR}/src/main/jni/include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/main/libs/${ANDROID_ABI})

add_library(hiai SHARED IMPORTED )
set_target_properties(libhiai PROPERTIES
    IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libhiai.so")

add_library(hiai_ir SHARED IMPORTED )
set_target_properties(libhiai_ir PROPERTIES
    IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libhiai_ir.so")

add_library(hiai_ir_build SHARED IMPORTED )
set_target_properties(libhiai_ir_build PROPERTIES
    IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libhiai_ir_build.so")

add_library( # Sets the name of the library.
             hiaijni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/jni/classify_jni.cpp
             src/main/jni/classify_async_jni.cpp
             src/main/jni/buildmodel.cpp
             src/main/jni/createModel.cpp)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       hiaijni android libhiai libhiai_ir libhiai_ir_build

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )