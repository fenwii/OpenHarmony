obj-y += jpegd_entry.o
obj-y += jpegd.o
obj-y += jpegd_drv.o
obj-y += jpegd_image.o

ifeq ($(CONFIG_PRODUCTNAME), "hi3559av100")
ccflags-y  += -DCHIP_HI3559AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3569v100")
ccflags-y  += -DCHIP_HI3569V100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3519av100")
ccflags-y  += -DCHIP_HI3519AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516dv300")
ccflags-y  += -DCHIP_HI3516CV500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3559v200")
ccflags-y  += -DCHIP_HI3516CV500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3556v200")
ccflags-y  += -DCHIP_HI3516CV500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3516av300")
ccflags-y  += -DCHIP_HI3516CV500
else ifeq ($(CONFIG_PRODUCTNAME), "hi3531dv200")
ccflags-y  += -DCHIP_HI3531DV200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3535av100")
ccflags-y  += -DCHIP_HI3535AV100
else ifeq ($(CONFIG_PRODUCTNAME), "hi3521dv200")
ccflags-y  += -DCHIP_HI3521DV200
else ifeq ($(CONFIG_PRODUCTNAME), "hi3520dv500")
ccflags-y  += -DCHIP_HI3520DV500
endif

