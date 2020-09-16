include $(MAIN_TOPDIR)/build/config/usr_config.mk

COMPILE_MODULE :=
USR_APP_ON ?= n
APP_NAME ?= demo
Q := @
TOOLS_PREFIX := riscv32-unknown-elf-
GCC_VER_NUM := 7.3.0
USR_OUTPUT_DIR ?=
USR_LIBS ?=
LIBPATH :=
ifeq ($(USR_OUTPUT_DIR), )
BIN_PATH := output/bin
else
BIN_PATH := $(USR_OUTPUT_DIR)/output/bin
endif
ifeq ($(CONFIG_TARGET_CHIP_HI3861), y)
TARGET_CHIP ?= Hi3861
else
TARGET_CHIP ?= Hi3861L
endif
TARGET_NAME ?= $(TARGET_CHIP)_$(APP_NAME)
