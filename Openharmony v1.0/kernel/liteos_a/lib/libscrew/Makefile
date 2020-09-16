include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := screw

LOCAL_SRCS  := \
        $(wildcard src/*.c) \
        $(LITEOSTOPDIR)/../../third_party/FreeBSD/sys/libkern/crc32.c

LOCAL_INCLUDE := \
        -I $(LITEOSTOPDIR)/kernel/include \
        -I $(LITEOSTOPDIR)/lib/libscrew/include \

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
