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
#
# 直接使用make进行编译的使用方法
# make 或 make all : 删除所有交付件再重新编译所有模块
# make clean : 删除交付件，不包括patch文件生成的中间件
# make all_clean : 删除所有交付件
# make link : 链接
THIRD_DIR = $(MAIN_TOPDIR)/third_party
U_BOOT_DIR = $(MAIN_TOPDIR)/third_party/u-boot-v2019.07

include $(MAIN_TOPDIR)/build/make_scripts/config.mk
include $(MAIN_TOPDIR)/build/make_scripts/config_lib_non_factory.mk

GCC_PATH := $(dir $(shell which $(CC)))
GCC_LIBPATH := -L$(GCC_PATH)../lib/gcc/riscv32-unknown-elf/$(GCC_VER_NUM)
LIBPATH += $(addprefix -Lbuild/build_tmp/libs/, $(foreach module, $(COMPILE_MODULE), $($(module)_dir)))
ifneq ($(USR_LIBS),)
	LIBPATH := $(foreach path, $(LIBPATH), $(patsubst -L%, -L$(MAIN_TOPDIR)/%, $(path)))
endif
COMPILE_MODULE += boot loaderboot
SIGN_CFG = A B
A_SIGN = 0x0040d3c0
B_SIGN = 0x004f13c0
FACTORY_SIGN = 0x0054d3c0

FIRM_WARE_VER := $(shell if [ $(CONFIG_TARGET_KERNEL_VER) -gt -1 ] && [ $(CONFIG_TARGET_KERNEL_VER) -lt 49 ];then echo $(CONFIG_TARGET_KERNEL_VER);fi;)
ifneq ($(FIRM_WARE_VER), $(CONFIG_TARGET_KERNEL_VER))
$(error [ERROR]:FIRM_WARE_VER=$(FIRM_WARE_VER) Ranges From 0 To 48)
endif

BOOT_VER = $(shell if [ $(CONFIG_TARGET_BOOT_VER) -gt -1 ] && [ $(CONFIG_TARGET_BOOT_VER) -lt 17 ];then echo $(CONFIG_TARGET_BOOT_VER);fi;)
ifneq ($(BOOT_VER), $(CONFIG_TARGET_BOOT_VER))
$(error [ERROR]:BOOT_VER Ranges From 0 To 16)
endif

ifeq ($(CONFIG_MESH_SUPPORT),y)
    LIBS += -lmeshautolink
endif
LIBS := $(filter-out -lboot -lloaderboot, $(LIBS))
ifeq ($(CONFIG_TARGET_SIG_RSA_V15), y)
    SIGN_ALG = 0x0
else ifeq ($(CONFIG_TARGET_SIG_RSA_PSS), y)
    SIGN_ALG = 0x1
else ifeq ($(CONFIG_TARGET_SIG_ECC), y)
    SIGN_ALG = 0x10
else ifeq ($(CONFIG_TARGET_SIG_SHA256), y)
    SIGN_ALG = 0x3F
endif

OUT_DIRS = $(MAIN_TOPDIR)/$(LOG_PATH) $(MAIN_TOPDIR)/$(CACHE_PATH) $(MAIN_TOPDIR)/$(LINK_PATH) $(MAIN_TOPDIR)/$(NV_PATH) $(MAIN_TOPDIR)/$(BIN_PATH)
all: prepare build_libs nv link check ota
	$(Q)echo "< ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ >"
	$(Q)echo "                              BUILD SUCCESS                              "
	$(Q)echo "< ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ >"

build_libs:
	$(Q)$(foreach module, $(COMPILE_MODULE), \
	$(foreach lib, $($(module)_libs), \
	$(MAKE) -C $(MAIN_TOPDIR)/$($(module)_dir) MODULE_DIR=$($(module)_dir) LIB=$(lib) all;))

nv:
	$(NV_TOOL) $(MAIN_TOPDIR)/$(NV_PATH) $(TARGET_NAME) $(NV_CFG_NAME)

#link: build_libs nv
link:
	$(CC) $(LINK_SCRIPTS_FLAG) -E $(MAIN_TOPDIR)/build/link/system_config.ld.S -o $(MAIN_TOPDIR)/$(LINK_PATH)/system_config.ld -P

ifeq ($(CONFIG_COMPRESSION_OTA_SUPPORT), y)
	$(CC) $(LINK_SCRIPTS_FLAG) -DFLASH_FIRM_START=$(A_SIGN) -E $(MAIN_TOPDIR)/build/link/link.ld.S -o $(MAIN_TOPDIR)/$(LINK_PATH)/link.lds -P
	$(LINK) $(LINKFLAGS) $(GCC_LIBPATH) $(sort $(LIBPATH)) -T$(MAIN_TOPDIR)/$(LINK_PATH)/link.lds -Map=$(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME).map -o $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME).out --start-group $(LIBS) --end-group
	$(OBJCOPY) -O binary $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME).out $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME).bin
	$(OBJDUMP) -d $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME).out >$(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME).asm
	dd if=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME).bin of=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_base.bin seek=0 count=278 bs=1K
	dd if=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME).bin of=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_kernel.bin skip=278 bs=1K
else
	$(Q)$(foreach X, $(SIGN_CFG), \
	$(CC) $(LINK_SCRIPTS_FLAG) -DFLASH_FIRM_START=$($(X)_SIGN) -E $(MAIN_TOPDIR)/build/link/link.ld.S -o $(MAIN_TOPDIR)/$(LINK_PATH)/link_$(X).lds -P; \
	$(LINK) $(LINKFLAGS) $(GCC_LIBPATH) $(sort $(LIBPATH)) -T$(MAIN_TOPDIR)/$(LINK_PATH)/link_$(X).lds -Map=$(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_$(X).map -o $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_$(X).out --start-group $(LIBS) --end-group; \
	$(OBJCOPY) -O binary $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_$(X).out $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_$(X).bin; \
	$(OBJDUMP) -d $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_$(X).out >$(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_$(X).asm; \
	dd if=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_$(X).bin of=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_base_$(X).bin seek=0 count=278 bs=1K; \
	dd if=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_$(X).bin of=$(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_kernel_$(X).bin skip=278 bs=1K; )
endif

ota:
	$(OTA_TOOL) boot_ota $(TARGET_NAME) $(SIGN_ALG) $(FIRM_WARE_VER) $(BOOT_VER) $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_flash_boot_ota.bin usr_output=$(USR_OUTPUT_DIR)
ifeq ($(CONFIG_COMPRESSION_OTA_SUPPORT), y)
	$(OTA_TOOL) ota $(TARGET_NAME) $(SIGN_ALG) $(FIRM_WARE_VER) $(BOOT_VER) $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_ota_temp.bin usr_output=$(USR_OUTPUT_DIR) $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_kernel.bin A;
	$(OTA_TOOL) burn_bin $(TARGET_NAME) $(SIGN_ALG) $(FIRM_WARE_VER) $(BOOT_VER) $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_burn.bin usr_output=$(USR_OUTPUT_DIR) $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_ota_temp.bin;
	$(OTA_TOOL) ota_compress $(TARGET_NAME) $(SIGN_ALG) $(FIRM_WARE_VER) $(BOOT_VER) $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_ota.bin usr_output=$(USR_OUTPUT_DIR) $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_ota_temp.bin;
else
	$(Q)$(foreach X, $(SIGN_CFG), \
	$(OTA_TOOL) ota $(TARGET_NAME) $(SIGN_ALG) $(FIRM_WARE_VER) $(BOOT_VER) $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_ota_$X.bin usr_output=$(USR_OUTPUT_DIR) $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_kernel_$(X).bin $X; )

	$(OTA_TOOL) burn_bin $(TARGET_NAME) $(SIGN_ALG) $(FIRM_WARE_VER) $(BOOT_VER) $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_NAME)_burn.bin usr_output=$(USR_OUTPUT_DIR) $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_kernel_A.bin
endif

check: link
ifeq ($(CONFIG_COMPRESSION_OTA_SUPPORT), y)
	@TARGET_SUM=$(shell sha256sum $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_base.bin | cut -d ' ' -f1) && \
	if [ "$$TARGET_SUM" == '$(BASE_NUM)' ]; \
	then echo "#########BASE BIN IS SAME WITH FIRST COMPILE!#########"; \
	else echo "\033[32m#########BASE BIN IS DIFFERENT WITH FIRST COMPILE!#########\033[0m"; exit 1; fi;
else
	$(Q)$(foreach X, $(SIGN_CFG), \
	TARGET_SUM=$(shell sha256sum $(MAIN_TOPDIR)/$(CACHE_PATH)/$(TARGET_NAME)_base_$(X).bin | cut -d ' ' -f1) && \
	if [ "$$TARGET_SUM" == '$(BASE_NUM)' ]; \
	then echo "#########BASE BIN IS SAME WITH FIRST COMPILE!#########"; \
	else echo "\033[32m#########BASE BIN IS DIFFERENT WITH FIRST COMPILE!#########\033[0m"; exit 1; fi; )
endif

prepare:
	$(Q)$(foreach x, $(OUT_DIRS),\
	if [ ! -d $x ]; \
	then \
	mkdir -p $x; \
	echo create dir $(x) success; \
	fi;)
	if [ ! -d $(MAIN_TOPDIR)/third_party/u-boot-v2019.07/u-boot-v2019.07/ ]; \
	then \
	cd $(THIRD_DIR)/u-boot-v2019.07; \
	tar -xvf u-boot-v2019.07.tar.gz; \
	cd $(U_BOOT_DIR)/u-boot-v2019.07; \
	patch -p1 < ./../patch/CVE-2019-13103.patch; \
	patch -p1 < ./../patch/CVE-2019-13104.patch; \
	patch -p1 < ./../patch/CVE-2019-13105.patch; \
	patch -p1 < ./../patch/CVE-2019-13106.patch; \
	patch -p1 < ./../patch/CVE-2019-14192-14193-14199.patch; \
	patch -p1 < ./../patch/CVE-2019-14194-14198.patch; \
	patch -p1 < ./../patch/CVE-2019-14195.patch; \
	patch -p1 < ./../patch/CVE-2019-14196.patch;  \
	patch -p1 < ./../patch/CVE-2019-14197-14200-14201-14202-14203-14204.patch; \
	patch -p1 < ./../hisilicon_patch/hisilicon-u-boot-v2019.07.patch ; \
	cd $(MAIN_TOPDIR);  \
	fi;

clean:
	$(Q)$(foreach x, $(OUT_DIRS),\
	if [ -d $(dir $x) ]; \
	then \
	$(RM) $(dir $x); \
	echo clean dir $(dir $x) success; \
	fi;)
	$(RM) $(MAIN_TOPDIR)/build/libs/factory_bin
	$(RM) $(MAIN_TOPDIR)/build/scripts/__pycache__/

all_clean:
	$(Q)$(foreach x, $(OUT_DIRS),\
	if [ -d $(dir $x) ]; \
	then \
	$(RM) $(dir $x); \
	echo clean dir $(dir $x) success; \
	fi;)
	$(RM) $(MAIN_TOPDIR)/build/libs/factory_bin
	$(RM) $(MAIN_TOPDIR)/build/scripts/__pycache__/
	$(RM) $(MAIN_TOPDIR)/third_party/u-boot-v2019.07/u-boot-v2019.07
	$(RM) $(MAIN_TOPDIR)/build/config/usr_config.mk.old
