# Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

include $(MAIN_TOPDIR)/build/make_scripts/config.mk
-include $(MAIN_TOPDIR)/$(MODULE_DIR)/srcs.mk
include $(MAIN_TOPDIR)/$(MODULE_DIR)/module_config.mk

OBJDIR = $(MAIN_TOPDIR)/$(OBJ_PATH)/$(MODULE_DIR)

ID_CFG_FILE = $(MAIN_TOPDIR)/$(MODULE_DIR)/file_id.cfg

LIB_NAME = lib$(LIB).a
SRCS = $($(LIB)_srcs)
LIBOUT = $(MAIN_TOPDIR)/$(LIB_PATH)/$(MODULE_DIR)/$(LIB_NAME)

ifdef SRC_FILES
OBJ_SRCS := $(filter %.c, $(SRC_FILES))
ASM_SRCS := $(filter %.S, $(SRC_FILES))
else
OBJ_SRCS := $(foreach dir, $(SRCS), $(wildcard $(dir)/*.c))
ASM_SRCS := $(foreach dir, $(SRCS), $(wildcard $(dir)/*.S ))
endif

OBJ_SRCS := $(filter-out %/ethernetif.c, $(OBJ_SRCS))
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(OBJ_SRCS))
ASM_OBJS = $(patsubst %.S, $(OBJDIR)/%.o, $(ASM_SRCS))

all: $(LIBOUT)
include $(MAIN_TOPDIR)/build/make_scripts/lib.mk

clean:
	$(Q)$(foreach x, $(OBJS) $(ASM_OBJS) $(LIBOUT), \
	if [ -d $(dir $x) ]; \
	then $(RM) $(dir $x); \
	echo clean dir $(dir $x) success; \
	fi;)

.PHONY: all clean

