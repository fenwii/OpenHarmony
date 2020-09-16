ALL_LIBS := demo
demo_srcs := init src
CCFLAGS +=
CCFLAGS += -D_PRE_WLAN_FEATURE_CSI -D_PRE_WLAN_FEATURE_P2P -DLWIP_ENABLE_DIAG_CMD=0
CCFLAGS += -I$(MAIN_TOPDIR)/components/iperf2/include -I$(MAIN_TOPDIR)/app/demo/include -I$(MAIN_TOPDIR)/app/demo/init -I$(MAIN_TOPDIR)/app/demo/src -I$(MAIN_TOPDIR)/config/app -I$(MAIN_TOPDIR)/config/diag -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/net/ripple/exports -I$(MAIN_TOPDIR)/components/ripple/exports
