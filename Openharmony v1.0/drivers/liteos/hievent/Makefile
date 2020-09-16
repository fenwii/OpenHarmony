include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(notdir $(shell pwd))

LOCAL_SRCS += $(wildcard ./src/*.c)
LOCAL_FLAGS += -I$(LITEOSTOPDIR)/../../drivers/liteos/hievent/include

include $(MODULE)
