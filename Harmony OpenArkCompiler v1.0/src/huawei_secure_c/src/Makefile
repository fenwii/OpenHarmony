######
###     This is a sample file for linux platform, please write the Makefile according to the actual situation of the product
######

PROJECT=libsecurec.so
#if you need a debug version library, use "-g" instead of "-s -DNDEBUG -O2".
# If you compiler report a warning on "break strict-aliasing rules", there is no problem. If you need to clear all warnings, you can add "-fno-strict-aliasing" option to your compiler, but this will impact the performance a little.

#for linux secure compile options from stdandard 2018.8
SECURE_CFLAG_FOR_SHARED_LIBRARY  = -fstack-protector-all -fPIC
SECURE_LDFLAG_FOR_SHARED_LIBRARY += -Wl,-z,relro,-z,now,-z,noexecstack


#-fvisibility=hidden need modify source code
#SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL += -fvisibility=hidden

#-ftrapv -D_FORTIFY_SOURCE=2 -fstack-check May result in performance degradation after opening
#SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL += -D_FORTIFY_SOURCE=2 -O2
#SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL += -ftrapv
#SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL += -fstack-check


SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL += -s
SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL +=  -Wformat=2 -Wfloat-equal -Wshadow
# about pie option , We compiled a dynamic library, so we did not use it. ,If you want to compile executable files, please open this option 
#SECURE_CFLAG_FOR_EXE = -fPIE -pie



## code standard options
SECUREC_CODE_STANDARD_OPTION = -Wconversion
SECUREC_CODE_STANDARD_OPTION += -Wformat-security
SECUREC_CODE_STANDARD_OPTION += -Wextra
SECUREC_CODE_STANDARD_OPTION += --param ssp-buffer-size=4
#repeat options
#SECUREC_CODE_STANDARD_OPTION += -D_FORTIFY_SOURCE=2
#SECUREC_CODE_STANDARD_OPTION += -Wl,-z,relro,-z,now
#SECUREC_CODE_STANDARD_OPTION += -fstack-protector
#this option just break compile
#SECUREC_CODE_STANDARD_OPTION  += -Werror

#from product options
PRODUCT_OPTION  = -Warray-bounds
PRODUCT_OPTION += -Wpointer-arith
PRODUCT_OPTION += -Wcast-qual
PRODUCT_OPTION += -Wstrict-prototypes
PRODUCT_OPTION += -Wmissing-prototypes
PRODUCT_OPTION += -Wstrict-overflow=1
PRODUCT_OPTION += -Wstrict-aliasing=2
PRODUCT_OPTION += -Wswitch -Wswitch-default 

CFLAG   =  -Wall  -s -DNDEBUG -O2 $(SECURE_CFLAG_FOR_SHARED_LIBRARY) $(SECURE_CFLAG_FOR_EXE) $(SECURE_CFLAG_FOR_SHARED_LIBRARY_OPTIONAL) $(SECUREC_CODE_STANDARD_OPTION) $(PRODUCT_OPTION)
#CFLAG += -DSECUREC_VXWORKS_PLATFORM
#CFLAG += -DSECUREC_SUPPORT_STRTOLD
#CFLAG += -DSECUREC_VXWORKS_VERSION_5_4
#CFLAG += -D__STDC_WANT_LIB_EXT1__=0
CFLAG  += $(CFLAG_EXT)


CC?=gcc
ARCH:=$(shell getconf LONG_BIT)

#The GCC High version will report an alarm with no break in the switch case statement, using this option to suppress
#There is a case statement without break in code, in order to reduce code size.
#GCCVERSION = $(shell $(CC)  --version | head -1 | sed -e 's/^[^0-9]*\([0-9]\).*/\1/g')
#CHKVERSION= $(shell if [ $(GCCVERSION) -ge 5 ];then echo 1;else echo 0;fi)
#ifeq "$(CHKVERSION)" "1"
#CFLAG += -Wno-implicit-fallthrough
#endif

ifeq ($(MAKECMDGOALS),lib)
#Set static library related options
CFLAG :=$(filter-out "xxxxx",$(CFLAG))
endif

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

.PHONY:clean lib kernel

ENABLE_SCANF_FILE=$(findstring SECUREC_ENABLE_SCANF_FILE=0,$(CFLAG))
ifeq ($(ENABLE_SCANF_FILE),SECUREC_ENABLE_SCANF_FILE=0)
OBJECTS:=$(filter-out fscanf_s.o vfscanf_s.o vscanf_s.o scanf_s.o vwscanf_s.o wscanf_s.o fwscanf_s.o vfwscanf_s.o,$(OBJECTS))
endif


ifneq ($(CFLAGS),)
CFLAG :=$(CFLAGS)
endif
CFLAG += -I../include
LD_FLAG ?= $(SECURE_LDFLAG_FOR_SHARED_LIBRARY) $(SECURE_CFLAG_FOR_SHARED_LIBRARY)
AR ?=ar
RANLIB ?=ranlib

$(PROJECT):$(OBJECTS)
	@mkdir -p ../obj
	mkdir -p ../lib
	$(CC)  -shared -o ../lib/$@ $(patsubst %.o,../obj/%.o,$^) $(LD_FLAG)
	@echo "finish $(PROJECT)"
	#you may add you custom commands here

lib:$(OBJECTS)
	$(AR) crv libsecurec.a $(patsubst %.o,../obj/%.o,$^)
	$(RANLIB) libsecurec.a
	-mkdir -p ../lib
	-cp libsecurec.a ../lib
	@echo "finish libsecurec.a"
	#you may add you custom commands here
.c.o:
	@mkdir -p ../obj
	$(CC) -c $< $(CFLAG) -o ../obj/$(patsubst %.c,%.o,$<)

EXTRA_CFLAGS += -I$(INCDIR) -fstack-protector

# provide the default value to module name and ccflags-y
ifeq ($(MODULE),)
	MODULE := ksecurec
endif
ifeq ($(DEBUG),y)
	ccflags-y += -DDEBUG
endif

ifneq ($(KERNELRELEASE),)
    obj-m := ksecurec.o
    ksecurec-objs := memcpy_s.o memmove_s.o memset_s.o  securecutil.o  strcat_s.o strcpy_s.o strncat_s.o strncpy_s.o # sprintf_s.o vsprintf_s.o snprintf_s.o vsnprintf_s.o secureprintoutput_a.o sscanf_s.o vsscanf_s.o secureinput_a.o
else
    KERNELDIR := /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)
kernel:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) INCDIR=$(PWD)/../include modules
endif

clean:
	echo "cleaning ...."
	-rm modules.order Module.symvers  $(MODULE).ko $(MODULE).mod.c  $(MODULE).mod.o $(MODULE).o *.o
	-rm -rf *.o ../obj ../lib $(PROJECT)
	echo "clean up"

