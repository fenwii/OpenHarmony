ifeq ($(CONFIG_PRODUCTNAME), "hi3521dv200")
VO_ARCH_NAME = hi3521dv200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3520dv500")
VO_ARCH_NAME = hi3521dv200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3531dv200")
VO_ARCH_NAME = hi3531dv200
VO_SUB_ARCH_NAME = hi3531dv200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3535av100")
VO_ARCH_NAME = hi3535av100
VO_SUB_ARCH_NAME = hi3535av100
endif

cflags-y     += -I$(srctree)/product/hiosd/include
cflags-y     += -I$(srctree)/product/hiosd/vo/ext_inc
cflags-y     += -I$(srctree)/product/hiosd/vo/include
cflags-y     += -I$(srctree)/product/hiosd/vo/mkp/include
cflags-y     += -I$(srctree)/product/hiosd/vo/mkp/src
cflags-y     += -I$(srctree)/product/hiosd/vo/mkp/src/dev
cflags-y     += -I$(srctree)/product/hiosd/vo/mkp/src/intf
cflags-y     += -I$(srctree)/product/hiosd/vo/mkp/src/layer
cflags-y     += -I$(srctree)/product/hiosd/vo/mkp/src/common
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/include
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/comm/src
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/comm/include
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/$(VO_ARCH_NAME)/include
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/include
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/$(VO_ARCH_NAME)/include/$(VO_SUB_ARCH_NAME)

ccflags-y  += $(cflags-y)
#HOSTCFLAGS += $(cflags-y)
#CPPFLAGS   += $(cflags-y)

CBB_VO_ARCH_COMM_SRC = arch/comm/src
CBB_VO_ARCH_HAL = arch/$(VO_ARCH_NAME)/hal

#enum mkp src files
obj-y += mkp/src/vo.o
obj-y += mkp/src/mkp_vo_user.o
obj-y += mkp/src/dev/mkp_vo_dev.o
obj-y += mkp/src/intf/mkp_vo_intf.o
obj-y += mkp/src/layer/mkp_vo_video.o
obj-y += mkp/src/layer/mkp_vo_gfx.o
obj-y += mkp/src/common/mkp_vo_comm.o
obj-y += mkp/src/common/mkp_vo_init.o
obj-y += mkp/src/mkp_vo_bmp.o

#enum arch comm src files
obj-y += $(CBB_VO_ARCH_COMM_SRC)/drv_vo_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/drv_vo_dev_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/drv_vo_layer_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/drv_vo_video_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/drv_vo_gfx_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/drv_vo_coef_org_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/hal_vo_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/hal_vo_dev_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/hal_vo_layer_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/hal_vo_video_comm.o
obj-y += $(CBB_VO_ARCH_COMM_SRC)/hal_vo_gfx_comm.o

#enum vo hal src files
obj-y += $(CBB_VO_ARCH_HAL)/drv_vo.o
obj-y += $(CBB_VO_ARCH_HAL)/drv_vo_dev.o
obj-y += $(CBB_VO_ARCH_HAL)/drv_vo_video.o
obj-y += $(CBB_VO_ARCH_HAL)/drv_vo_gfx.o
obj-y += $(CBB_VO_ARCH_HAL)/hal_vo.o
obj-y += $(CBB_VO_ARCH_HAL)/hal_vo_dev.o
obj-y += $(CBB_VO_ARCH_HAL)/hal_vo_video.o

#enum vo sys hal src files
obj-y += $(CBB_VO_ARCH_HAL)/sys_drv.o
obj-y += $(CBB_VO_ARCH_HAL)/sys_hal.o

ifeq ($(CONFIG_PRODUCTNAME), "hi3531dv200")
ccflags-y += -DCHIP_HI3531DV200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3535av100")
ccflags-y += -DCHIP_HI3535AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3521dv200")
ccflags-y += -DCHIP_HI3521DV200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3520dv500")
ccflags-y += -DCHIP_HI3520DV500
endif
