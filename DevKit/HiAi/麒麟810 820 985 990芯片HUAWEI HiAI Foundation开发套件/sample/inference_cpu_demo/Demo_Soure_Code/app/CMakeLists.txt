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
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/main/libs/${ANDROID_ABI})

add_library(libai_client SHARED IMPORTED )
set_target_properties(libai_client PROPERTIES
    IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libai_client.so")

add_library( # Sets the name of the library.
             hiai

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/classify_jni.cpp
             src/main/cpp/classify_async_jni.cpp
             src/main/cpp/buildmodel.cpp)


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
                       hiai android libai_client

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )