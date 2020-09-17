TARGETS := $(APP)
LIB_MPLT := $(MAPLE_ROOT)/libjava-core/libjava-core.mplt
APP_CLASS := $(foreach APP, $(TARGETS), $(APP).class)
APP_JAR := $(foreach APP, $(TARGETS), $(APP).jar)
APP_MPL := $(foreach APP, $(TARGETS), $(APP).mpl)
APP_MPLT:=$(foreach APP, $(TARGETS), $(APP).mplt)
APP_VTABLEIMPL_MPL := $(foreach APP, $(TARGETS), $(APP).VtableImpl.mpl)
APP_S := $(foreach APP, $(TARGETS), $(APP).VtableImpl.s)

JAVA2JAR := $(MAPLE_ROOT)/out/bin/java2jar
JBC2MPL_BIN := $(MAPLE_ROOT)/out/bin/jbc2mpl
MAPLE_BIN := $(MAPLE_ROOT)/out/bin/maple
MPLCG_BIN := $(MAPLE_ROOT)/out/bin/mplcg
MPLME_FLAGS := --quiet
MPL2MPL_FLAGS := --quiet --regnativefunc --maplelinker
MPLCG_SO_FLAGS := --fpic
MPLCG_FLAGS := --quiet --no-pie --verbose-asm --maplelinker
MPLCOMBO_FLAGS := --run=me:mpl2mpl:mplcg --option="$(MPLME_FLAGS):$(MPL2MPL_FLAGS):$(MPLCG_FLAGS) $(MPLCG_SO_FLAGS)"
