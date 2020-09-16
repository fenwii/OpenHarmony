cflags-y	+= -I$(srctree)/product/hiotp/include
cflags-y	+= -I$(srctree)/product/hiotp/api
cflags-y	+= -I$(srctree)/product/hiotp/drv/include

ifeq ($(CONFIG_PRODUCTNAME), $(filter $(CONFIG_PRODUCTNAME), "hi3521dv200" "hi3520dv500"))
cflags-y	+= -DCHIP_TYPE_hi3521dv200
else ifeq ($(CONFIG_PRODUCTNAME), $(filter $(CONFIG_PRODUCTNAME), "hi3531dv200" "hi3535av100"))
cflags-y	+= -DCHIP_TYPE_hi3531dv200
endif

ccflags-y  	+= $(cflags-y)

obj-y 	+= api/mpi_otp.o
obj-y 	+= api/sys_otp.o

obj-y 	+= drv/drv_ioctl_otp.o
obj-y 	+= drv/drv_otp.o
obj-y 	+= drv/hal_otp.o
obj-y 	+= drv/drv_lib.o

