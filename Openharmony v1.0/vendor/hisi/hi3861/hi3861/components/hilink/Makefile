include $(MAIN_TOPDIR)/build/make_scripts/config.mk
include $(MAIN_TOPDIR)/$(MODULE_DIR)/module_config.mk
-include $(MAIN_TOPDIR)/$(MODULE_DIR)/srcs.mk

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

