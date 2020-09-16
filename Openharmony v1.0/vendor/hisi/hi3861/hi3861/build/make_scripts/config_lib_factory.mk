ifeq ($(CONFIG_TARGET_CHIP_HI3861), y)
	ifeq ($(CONFIG_DIAG_SUPPORT), y)
		LIBPATH += -Lbuild/libs/hi3861/debug/factory
	endif
else
	ifeq ($(CONFIG_DIAG_SUPPORT), y)
		LIBPATH += -Lbuild/libs/hi3861l/debug/factory
	endif
endif

ifeq ($(CONFIG_TARGET_CHIP_HI3861), y)
	ifneq ($(CONFIG_DIAG_SUPPORT), y)
		LIBPATH += -Lbuild/libs/hi3861/release/factory
	endif
else
	ifneq ($(CONFIG_DIAG_SUPPORT), y)
		LIBPATH += -Lbuild/libs/hi3861l/release/factory
	endif
endif

ifeq ($(CONFIG_HILINK), y)
	LIBPATH += -Lcomponents/hilink/lib
endif
