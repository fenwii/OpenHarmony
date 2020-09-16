#DRV_PATH := $(srctree)/product/hiosd/hdmi

HDMI_VER := hdmi_2_0
ifeq ($(CONFIG_PRODUCTNAME), "hi3559av100")
CHIP_TYPE := hi3559av100
CTRL      := hisiv200
PHY       := hisiv200
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3559A
cflags-y  += -DCHIP_HI3559AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3569v100")
CHIP_TYPE := hi3559av100
CTRL      := hisiv200
PHY       := hisiv200
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3559A
cflags-y  += -DCHIP_HI3559AV100

else ifeq ($(CONFIG_PRODUCTNAME), "hi3519av100")
CHIP_TYPE := hi3519av100
CTRL      := hisiv100
PHY       := hisiv200
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3519A
cflags-y  += -DCHIP_HI3519AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3556av100")
CHIP_TYPE := hi3519av100
CTRL      := hisiv100
PHY       := hisiv200
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3519A
cflags-y  += -DCHIP_HI3519AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516dv300")
CHIP_TYPE := hi3516cv500
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3516CV500
cflags-y  += -DCHIP_TYPE_hi3516cv500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3559v200")
CHIP_TYPE := hi3516cv500
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3516CV500
cflags-y  += -DCHIP_TYPE_hi3516cv500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3556v200")
CHIP_TYPE := hi3516cv500
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3516CV500
cflags-y  += -DCHIP_TYPE_hi3516cv500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3562v100")
CHIP_TYPE := hi3516cv500
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3516CV500
cflags-y  += -DCHIP_TYPE_hi3516cv500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3566v100")
CHIP_TYPE := hi3516cv500
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3516CV500
cflags-y  += -DCHIP_TYPE_hi3516cv500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516av300")
CHIP_TYPE := hi3516cv500
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3516CV500
cflags-y  += -DCHIP_TYPE_hi3516cv500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3531dv200")
VO_ARCH_NAME = hi3531dv200
VO_SUB_ARCH_NAME = hi3531dv200
CHIP_TYPE := hi3531dv200
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3531DV200
cflags-y  += -DCHIP_TYPE_hi3531dv200
cflags-y  += -DPHY_CRAFT_S28
cflags-y  += -DHI_PLATFORM_H8
else ifeq ($(CONFIG_PRODUCTNAME), "hi3535av100")
VO_ARCH_NAME = hi3531dv200
VO_SUB_ARCH_NAME = hi3535av100
CHIP_TYPE := hi3531dv200
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3535AV100
cflags-y  += -DCHIP_TYPE_hi3535av100
cflags-y  += -DPHY_CRAFT_S28
cflags-y  += -DHI_PLATFORM_H8
cflags-y  += -DHI_HDMI_SUPPORT_1_4
else ifeq ($(CONFIG_PRODUCTNAME), "hi3521dv200")
VO_ARCH_NAME = hi3521dv200
CHIP_TYPE := hi3521dv200
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3521DV200
cflags-y  += -DCHIP_TYPE_hi3521dv200
cflags-y  += -DPHY_CRAFT_S28
cflags-y  += -DHI_PLATFORM_H8
cflags-y  += -DHI_HDMI_SUPPORT_1_4
else ifeq ($(CONFIG_PRODUCTNAME), "hi3520dv500")
VO_ARCH_NAME = hi3521dv200
CHIP_TYPE := hi3521dv200
CTRL      := hisiv100
PHY       := hisiv100
OSAL      := hisiv600
cflags-y  += -DHDMI_PRODUCT_HI3521DV200
cflags-y  += -DCHIP_TYPE_hi3521dv200
cflags-y  += -DPHY_CRAFT_S28
cflags-y  += -DHI_PLATFORM_H8
cflags-y  += -DHI_HDMI_SUPPORT_1_4
endif

CTRL_DIR    := $(srctree)/hal/ctrl/$(CTRL)
PHY_DIR     := $(srctree)/hal/phy/$(PHY)
PRODUCT_DIR := $(srctree)/product/$(CHIP_TYPE)

cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/hal
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/hal/ctrl/$(CTRL)
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/hal/ctrl/$(CTRL)/regs
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/hal/emi
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/hal/phy/$(PHY)
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/hal/phy/$(PHY)/regs
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/product/$(CHIP_TYPE)
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/product/$(CHIP_TYPE)/regs
cflags-y     += -I$(srctree)/product/hiosd/hdmi/$(HDMI_VER)/drv/osal/$(OSAL)
cflags-y     += -I$(srctree)/include
cflags-y     += -I$(PRODUCT_DIR)
cflags-y     += -I$(PRODUCT_DIR)/regs
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/$(VO_ARCH_NAME)/include
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/include
cflags-y     += -I$(srctree)/product/hiosd/vo/include
cflags-y     += -I$(srctree)/product/hiosd/vo/arch/$(VO_ARCH_NAME)/include/$(VO_SUB_ARCH_NAME)
cflags-y     += -I$(srctree)/product/hiosd/include

cflags-y += -DHDMI_SUPPORT_LOGIC_HISIV100
cflags-y += -DCONFIG_HDMI_BVT_SDK -DDVI_SUPPORT
cflags-y += -DDVI_SUPPORT
cflags-y += -DHDMI_SCDC_SUPPORT

ifeq ($(FPGA),y)
cflags-y  += -DHDMI_FPGA_SUPPORT
endif

ccflags-y  += $(cflags-y)
HOSTCFLAGS += $(cflags-y)
CPPFLAGS   += $(cflags-y)

#HDMI_EMI_ENABLE

OBJ    := ../boot_hdmi_intf.o
OBJ    += drv_hdmi_common.o
OBJ    += drv_hdmi_infoframe.o
OBJ    += $(CTRL_DIR)/hdmi_hal_intf.o

OBJ    +=   $(CTRL_DIR)/regs/hdmi_reg_aon.o \
            $(CTRL_DIR)/regs/hdmi_reg_ctrl.o \
            $(CTRL_DIR)/regs/hdmi_reg_tx.o \
            $(CTRL_DIR)/regs/hdmi_reg_video_path.o

OBJ += $(PRODUCT_DIR)/regs/hdmi_reg_crg.o

OBJ    +=   $(CTRL_DIR)/hdmi_hal_intf.o \
            $(CTRL_DIR)/hdmi_hal_ddc.o \
            $(CTRL_DIR)/hdmi_hal_ctrl.o \
            $(CTRL_DIR)/hdmi_hal_scdc.o

OBJ += $(PHY_DIR)/hdmi_hal_phy.o
OBJ += $(PHY_DIR)/regs/hdmi_reg_dphy.o
OBJ += $(PRODUCT_DIR)/hdmi_product_define.o

obj-y += $(OBJ)

#########################################################################
