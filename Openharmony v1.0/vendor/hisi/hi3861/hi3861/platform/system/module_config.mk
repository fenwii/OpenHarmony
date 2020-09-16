cfg_srcs := cfg
parttab_srcs := partition_table
upg_srcs := upg
CCFLAGS += -Werror -fsigned-char
CCFLAGS += -I$(MAIN_TOPDIR)/platform/system/include \
	-I$(MAIN_TOPDIR)/platform/system/upg \
	-I$(MAIN_TOPDIR)/platform/drivers/flash \
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/kernel/extended/include
