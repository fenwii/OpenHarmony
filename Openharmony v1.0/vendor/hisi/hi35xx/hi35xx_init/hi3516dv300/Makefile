
LITEOSTOPDIR := $(shell pwd)/../../../../../kernel/liteos_a
CONFIG_FILE := $(LITEOSTOPDIR)/.config

ifeq ($(wildcard $(CONFIG_FILE)), )
$(error  "########################kernel is not compiled################################")
endif
include $(LITEOSTOPDIR)/config.mk

MPP_DIR := $(shell pwd)/../../hi3516dv300/module_init/

include hi3516dv300.mak
