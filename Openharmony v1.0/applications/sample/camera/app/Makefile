# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

BASE_DIR := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)

BUILD_SUBDIRS = src

MAKEFILE_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LITEOSTOPDIR = ${MAKEFILE_PATH}/../../../../kernel/liteos_a
CROSS_COMPILE = arm-linux-ohoseabi-
LITEOS_COMPILER_PATH := $(shell $(LITEOSTOPDIR)/tools/build/mk/get_compiler_path.sh  $(CROSS_COMPILE) $(LITEOSTOPDIR))
STRIP = ${LITEOS_COMPILER_PATH}/bin/$(CROSS_COMPILE)strip --strip-unneeded

APP_DIR = $(BASE_DIR)

FSIMG_SUBDIR = bin
FSIMG_DIR = $(APP_DIR)/$(FSIMG_SUBDIR)
APP_IMG = $(APP_DIR)/app.img

LIBCIMG_SUBDIR = lib
LIBCIMG_DIR = $(APP_DIR)/$(LIBCIMG_SUBDIR)
LIBCFS_IMG = $(APP_DIR)/libc.img

# Hide
Q = @

define DIR_template
$(1)_$(2):
	$(Q) $(MAKE) -C $(1) $(3) APP_DIR="$(APP_DIR)" FSIMG_DIR="$(FSIMG_DIR)" Q="$(Q)" LITEOS_COMPILER_PATH="$(LITEOS_COMPILER_PATH)" CROSS_COMPILE="$(CROSS_COMPILE)"
endef

all: $(APP_IMG) $(LIBCFS_IMG)
.PHONY: all build clean install populate

$(foreach DIR, $(BUILD_SUBDIRS), $(eval $(call DIR_template,$(DIR),build, all)))
$(foreach DIR, $(BUILD_SUBDIRS), $(eval $(call DIR_template,$(DIR),clean,clean)))
$(foreach DIR, $(BUILD_SUBDIRS), $(eval $(call DIR_template,$(DIR),install,install)))

# Build program(s) in each sud-directory

build: $(foreach DIR, $(BUILD_SUBDIRS), $(DIR)_build)

# Install each program in the file system image directory

install: $(foreach DIR, $(BUILD_SUBDIRS), $(DIR)_install)
	$(Q) $(STRIP) $(wildcard $(FSIMG_SUBDIR)/*)
	$(Q) $(STRIP) $(wildcard $(LIBCIMG_SUBDIR)/*)

# Create the file system image directory

$(FSIMG_DIR):
	$(Q) mkdir -p $(FSIMG_DIR)

# Populate the file system image directory

populate:  $(FSIMG_DIR) build install

# Create the img file from the populated fs directory

$(APP_IMG): populate

# Create the libc.img file

$(LIBCFS_IMG):
	$(Q) mkdir -p $(LIBCIMG_DIR)

# Clean each subdirectory

clean: $(foreach DIR, $(BUILD_SUBDIRS), $(DIR)_clean)
	$(Q) rm -f $(DIRLIST_HDR) $(APP_IMG) $(SYMTAB_SRC) $(LIBCFS_IMG)
	$(Q) rm -rf $(FSIMG_DIR) $(LIBCIMG_DIR)


