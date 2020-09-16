ifeq ($(CONFIG_TARGET_CHIP_HI3861), y)
	ifeq ($(CONFIG_DIAG_SUPPORT), y)
		ifeq ($(CONFIG_QUICK_SEND_MODE), y)
			LIBPATH += -Lbuild/libs/hi3861/debug/no_mesh_quick_start
		else ifeq ($(CONFIG_MESH_SUPPORT), y)
			LIBPATH += -Lbuild/libs/hi3861/debug/mesh
		else
			LIBPATH += -Lbuild/libs/hi3861/debug/no_mesh
		endif
	endif
else
	ifeq ($(CONFIG_DIAG_SUPPORT), y)
		ifeq ($(CONFIG_CHIP_PKT_48K), y)
			LIBPATH += -Lbuild/libs/hi3861l/debug/no_mesh_pkt_48k
		else ifeq ($(CONFIG_MESH_SUPPORT), y)
			LIBPATH += -Lbuild/libs/hi3861l/debug/mesh
		else
			LIBPATH += -Lbuild/libs/hi3861l/debug/no_mesh
		endif
	endif
endif

ifeq ($(CONFIG_TARGET_CHIP_HI3861), y)
	ifneq ($(CONFIG_DIAG_SUPPORT), y)
		ifeq ($(CONFIG_QUICK_SEND_MODE), y)
			LIBPATH += -Lbuild/libs/hi3861/release/no_mesh_quick_start
		else ifeq ($(CONFIG_MESH_SUPPORT), y)
			LIBPATH += -Lbuild/libs/hi3861/release/mesh
		else
			LIBPATH += -Lbuild/libs/hi3861/release/no_mesh
		endif
	endif
else
	ifneq ($(CONFIG_DIAG_SUPPORT), y)
		ifeq ($(CONFIG_CHIP_PKT_48K), y)
			LIBPATH += -Lbuild/libs/hi3861l/release/no_mesh_pkt_48k
		else ifeq ($(CONFIG_MESH_SUPPORT), y)
			LIBPATH += -Lbuild/libs/hi3861l/release/mesh
		else
			LIBPATH += -Lbuild/libs/hi3861l/release/no_mesh
		endif
	endif
endif

ifeq ($(CONFIG_HILINK), y)
	LIBPATH += -Lcomponents/hilink/lib
endif
