include $(MAIN_TOPDIR)/build/make_scripts/config.mk
-include $(MAIN_TOPDIR)/$(MODULE_DIR)/srcs.mk
include $(MAIN_TOPDIR)/$(MODULE_DIR)/module_config.mk

override CCFLAGS = $(BOOT_CCFLAGS) $(BOOT_DEFINE) $(BOOT_INC)
override ASFLAGS = $(BOOT_ASFLAGS) $(BOOT_DEFINE) $(BOOT_INC)

LIBDIR = $(MAIN_TOPDIR)/$(LIB_PATH)/$(MODULE_DIR)
OBJDIR = $(MAIN_TOPDIR)/$(OBJ_PATH)/flashboot
ID_CFG_FILE = $(MAIN_TOPDIR)/$(MODULE_DIR)/file_id.cfg

LIB_NAME = lib$(LIB).a
SRCS = $($(LIB)_srcs)
LIBOUT = $(LIBDIR)/$(MODULE_DIR)/$(LIB_NAME)

ifdef SRC_FILES
OBJ_SRCS = $(filter %.c, $(SRC_FILES))
ASM_SRCS = $(filter %.S, $(SRC_FILES))
else
OBJ_SRCS = $(foreach dir, $(SRCS), $(wildcard $(dir)/*.c))
ASM_SRCS = $(foreach dir, $(SRCS), $(wildcard $(dir)/*.S ))
OBJ_COMMON_SRCS = $(foreach dir, $($(LIB)_common_srcs), $(wildcard $(dir)/*.c))
ASM_COMMON_SRCS = $(foreach dir, $($(LIB)_common_srcs), $(wildcard $(dir)/*.S ))
endif
OBJ_SRCS += $(MAIN_TOPDIR)/third_party/u-boot-v2019.07/u-boot-v2019.07/lib/crc32.c \
            $(MAIN_TOPDIR)/third_party/u-boot-v2019.07/u-boot-v2019.07/lib/lzma/LzmaDec.c \
            $(MAIN_TOPDIR)/third_party/u-boot-v2019.07/u-boot-v2019.07/lib/lzma/LzmaTools.c
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(OBJ_SRCS))
ASM_OBJS = $(patsubst %.S, $(OBJDIR)/%.o, $(ASM_SRCS))
COMMON_OBJS = $(patsubst ../%.c, $(OBJDIR)/%.o, $(OBJ_COMMON_SRCS))
COMMON_ASM_OBJS = $(patsubst ../%.S, $(OBJDIR)/%.o, $(ASM_COMMON_SRCS))

SIGN_TOOL = $(MAIN_TOPDIR)/tools/sign_tool/sign_tool
ENCRYPT_KEY_PATH = $(MAIN_TOPDIR)/tools/sign_tool/aes_key.txt
ifeq ($(CONFIG_TARGET_SIG_SHA256), y)
    LINK_FILE = $(MAIN_TOPDIR)/build/link/flashboot_sha256.lds
    INPUT_LOADER = $(MAIN_TOPDIR)/build/basebin/Hi3861_loader_sha256.bin
else ifeq ($(CONFIG_TARGET_SIG_ECC), y)
    LINK_FILE = $(MAIN_TOPDIR)/build/link/flashboot_ecc.lds
    INPUT_LOADER = $(MAIN_TOPDIR)/build/basebin/Hi3861_loader_ecc.bin
    ROOT_KEY_PATH = $(MAIN_TOPDIR)/tools/sign_tool/root_ecc.pem
    SUB_KEY_PATH = $(MAIN_TOPDIR)/tools/sign_tool/sub_ecc.pem
    SIGN_TYPE = 2
else
    LINK_FILE = $(MAIN_TOPDIR)/build/link/flashboot_rsa.lds
    INPUT_LOADER = $(MAIN_TOPDIR)/build/basebin/Hi3861_loader_rsa.bin
    ROOT_KEY_PATH = $(MAIN_TOPDIR)/tools/sign_tool/root_rsa.pem
    SUB_KEY_PATH = $(MAIN_TOPDIR)/tools/sign_tool/sub_rsa.pem
    ifeq ($(CONFIG_TARGET_SIG_RSA_V15), y)
        SIGN_TYPE = 0
    else ifeq ($(CONFIG_TARGET_SIG_RSA_PSS), y)
        SIGN_TYPE = 1
    endif
endif

LIBS := $(patsubst lib%.a, -l%, $(notdir $(wildcard $(MAIN_TOPDIR)/build/libs/boot_libs/*.a)))
LIBPATH := -L$(MAIN_TOPDIR)/build/libs
LIBPATH += -L$(MAIN_TOPDIR)/build/libs/boot_libs
BOOT_ELF = $(MAIN_TOPDIR)/$(CACHE_PATH)/flash_boot.elf
BOOT_BIN = $(MAIN_TOPDIR)/$(CACHE_PATH)/hi_flash_boot.bin
BOOT_BIN_B = $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_CHIP)_boot_signed_B.bin
BOOT_SIGNED_BIN = $(MAIN_TOPDIR)/$(BIN_PATH)/$(TARGET_CHIP)_boot_signed.bin

all: $(OBJS) $(ASM_OBJS) $(COMMON_OBJS) $(COMMON_ASM_OBJS)
	$(LINK) $(BOOT_LINK_FLAGS) -T $(LINK_FILE) $(LIBPATH) $(sort $^) -o $(BOOT_ELF) --start-group $(LIBS) --end-group
	$(OBJCOPY) -Obinary -R .rom.text -R .rom.code.text -R .u_boot_cmd  -R .rom.data -R .rom.code.data -R .rom.bss -R .rom.code.bss -S $(BOOT_ELF) $(BOOT_BIN)
ifeq ($(CONFIG_TARGET_SIG_SHA256), y)
	$(SIGN_TOOL) -i $(BOOT_BIN) -o $(BOOT_SIGNED_BIN) -n -t$(BOOT_BIN_B)
else ifeq ($(CONFIG_BOOT_ENCRYPT), y)
	$(SIGN_TOOL) -i $(BOOT_BIN) -o $(BOOT_SIGNED_BIN) -r$(ROOT_KEY_PATH) -s$(SUB_KEY_PATH) -v $(CONFIG_TARGET_BOOT_VER) -a $(SIGN_TYPE) -e$(ENCRYPT_KEY_PATH) -t$(BOOT_BIN_B)
else
	$(SIGN_TOOL) -i $(BOOT_BIN) -o $(BOOT_SIGNED_BIN) -r$(ROOT_KEY_PATH) -s$(SUB_KEY_PATH) -v $(CONFIG_TARGET_BOOT_VER) -a $(SIGN_TYPE) -t$(BOOT_BIN_B)
endif
	$(Q)echo [BOOT] SUCCESS
	$(RM) $(BOOT_ELF) $(BOOT_BIN)


include $(MAIN_TOPDIR)/build/make_scripts/lib.mk
$(COMMON_OBJS): $(OBJDIR)/%.o : ../%.c
	$(Q)if [ ! -d $(dir $@) ]; then \
	mkdir -p $(dir $@); \
	fi;
	$(Q) echo Compile $<;
	$(Q)if [ -e $< ]; \
	then $(CC) $(CCFLAGS) -c $< -o $@; \
	if [ "$$?" != "0" ]; then \
	exit 1;\
	fi; \
	fi;

$(COMMON_ASM_OBJS): $(OBJDIR)/%.o : ../%.S
	$(Q)echo Compile  $<;
	$(Q)if [ ! -d $(dir $@) ]; \
	then \
	mkdir -p $(dir $@);\
	fi;
	$(Q)if [ -f $< ]; \
	then \
	$(CC) $(ASFLAGS)  -c $< -o $@ ; \
	if [ "$$?" != "0" ]; then \
	exit 1;\
	fi;\
	fi;
