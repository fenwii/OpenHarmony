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

# Choose the type of compiling:
# "STATIC_COMPILE = y" means compiling in a static way,
# "STATIC_COMPILE = n" means compiling in a dynamic way.
STATIC_COMPILE = n

BIN = helloworld
BIN_ASM = $(BIN).asm
OBJEXT = .o

CC = ${LITEOS_COMPILER_PATH}/bin/$(CROSS_COMPILE)gcc
CPP = ${LITEOS_COMPILER_PATH}/bin/$(CROSS_COMPILE)g++
LD = ${LITEOS_COMPILER_PATH}/bin/$(CROSS_COMPILE)ld
OBJDUMP = ${LITEOS_COMPILER_PATH}/bin/$(CROSS_COMPILE)objdump

COMMON_INCLUDE = -I $(APP_DIR)/include/
COMMON_FLAGS = -fPIE -D_XOPEN_SOURCE=700

CFLAGS += -fno-omit-frame-pointer -std=c99 $(COMMON_INCLUDE) $(COMMON_FLAGS)
CXXFLAGS += $(COMMON_INCLUDE) $(COMMON_FLAGS)

ifeq ($(STATIC_COMPILE), y)
	LDFLAGS = --static
else
	LDFLAGS = -pie
endif

CCSRCS := $(wildcard *.c)
CCOBJS = $(CCSRCS:.c=$(OBJEXT))
CXXSRCS := $(wildcard *.cpp)
CXXOBJS = $(CXXSRCS:.cpp=$(OBJEXT))

MUSL = musl/lib/libc.so

all: $(MUSL) $(BIN) $(BIN_ASM)

$(CCOBJS): %$(OBJEXT): %.c
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(CXXOBJS): %$(OBJEXT): %.cpp
	@echo "CPP: $<"
	$(Q) $(CPP) -c $(CXXFLAGS) $< -o $@

$(BIN_ASM): $(BIN)
	$(Q) rm -rf $(CCOBJS) $(CXXOBJS)
	$(Q) $(OBJDUMP) -d $(BIN) > $(BIN_ASM)

$(MUSL):
	$(Q) rm -rf musl/
	$(Q) ./build_musl.sh &> build_musl.log

$(BIN): $(MUSL) $(CCOBJS) $(CXXOBJS)
ifeq ($(STATIC_COMPILE), y)
	@echo "LD: $^"
	$(Q) $(CC) $(LDFLAGS) -o $@ $^
else
	@echo "LD: $^"
	$(Q)mkdir -p $(APP_DIR)/lib/
	$(Q)cp -f $(APP_DIR)/src/musl/lib/libc.so $(APP_DIR)/lib/libc.so
	$(Q)$(CC) $(LDFLAGS) -o $@ $(CCOBJS) $(CXXOBJS)
endif

clean:
	$(Q) rm -rf $(CCOBJS) $(CXXOBJS) $(BIN) $(BIN_ASM)
	$(Q) rm -rf musl/
	$(Q) rm -rf build_musl.log

install:
	$(Q) mkdir -p $(FSIMG_DIR)
	$(Q) install $(BIN) $(FSIMG_DIR)/$(BIN)
