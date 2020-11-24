#
#@file Android.mk
#
#Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
LOCAL_PATH := $(call my-dir)
DDK_LIB_PATH := $(LOCAL_PATH)/../../../libs/$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE    := hiai_ir
LOCAL_SRC_FILES := $(DDK_LIB_PATH)/libhiai_ir.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := hiai
LOCAL_SRC_FILES := $(DDK_LIB_PATH)/libhiai.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := hcl
LOCAL_SRC_FILES := $(DDK_LIB_PATH)/libhcl.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := cpucl
LOCAL_SRC_FILES := $(DDK_LIB_PATH)/libcpucl.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := hiaijni
LOCAL_SRC_FILES := \
    classify_sync_jni.cpp \
    classify_async_jni.cpp \
    buildmodel.cpp

LOCAL_SHARED_LIBRARIES :=  hiai_ir \
                           hiai \
                           hcl \
                           cpucl \

LOCAL_LDFLAGS := -L$(DDK_LIB_PATH)
LOCAL_LDLIBS += \
    -llog \
    -landroid

CPPFLAGS=-stdlib=libstdc++ LDLIBS=-lstdc++
LOCAL_CFLAGS += -std=c++14

include $(BUILD_SHARED_LIBRARY)
