at_srcs := src
CCFLAGS += -D_PRE_WLAN_FEATURE_MFG_TEST
CCFLAGS += -I$(MAIN_TOPDIR)/platform/drivers/uart \
	-I$(MAIN_TOPDIR)/platform/system/cpup \
	-I$(MAIN_TOPDIR)/platform/at \
	-I$(MAIN_TOPDIR)/components/at/src \
	-I$(MAIN_TOPDIR)/components/wifi/include \
	-I$(MAIN_TOPDIR)/components/iperf2/include \
	-I$(MAIN_TOPDIR)/config/diag \
	-I$(MAIN_TOPDIR)/third_party/lwip_sack/include \
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/commons
