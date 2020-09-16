# Hisilicon Hi3518ev300 Makefile.param
REL_LIB := $(MPP_DIR)/lib
REL_INC := $(MPP_DIR)/include
ARCH_LIBNAME := hi3516ev200

INC_FLAGS := -I$(REL_INC)

ISP_VERSION := ISP_V2

CFLAGS += -Wall $(INC_FLAGS) -D$(ISP_VERSION)

################ select audio codec type for your sample ################
ACODEC_TYPE ?= ACODEC_TYPE_INNER
#external acodec
#ACODEC_TYPE ?= ACODEC_TYPE_TLV320AIC31
INNER_HDMI ?= n

ifeq ($(ACODEC_TYPE), ACODEC_TYPE_INNER)
	CFLAGS += -DHI_ACODEC_TYPE_INNER
endif

ifeq ($(ACODEC_TYPE), ACODEC_TYPE_TLV320AIC31)
	CFLAGS += -DHI_ACODEC_TYPE_TLV320AIC31
	INC_FLAGS += -I$(SDK_PATH)/$(EXTDRV)/tlv320aic31
endif

ifeq ($(INNER_HDMI), y)
	CFLAGS += -DHI_ACODEC_TYPE_HDMI
endif

#########################################################################

TARGET := OHOS_Image

TARGET_PATH := $(PWD)

# compile OHOS

SDK_LIB_PATH := -L$(REL_LIB) -L$(REL_LIB)/extdrv

SDK_LIB := $(SDK_LIB_PATH) --start-group -lsys_config -lhi_osal -l$(ARCH_LIBNAME)_base -l$(ARCH_LIBNAME)_sys -l$(ARCH_LIBNAME)_isp -l$(ARCH_LIBNAME)_vi \
							-l$(ARCH_LIBNAME)_vo -lhifb -l$(ARCH_LIBNAME)_vpss -l$(ARCH_LIBNAME)_vgs -l$(ARCH_LIBNAME)_tde -lhi_mipi_rx \
							-l$(ARCH_LIBNAME)_chnl -l$(ARCH_LIBNAME)_rc -l$(ARCH_LIBNAME)_rgn -l$(ARCH_LIBNAME)_vedu \
							-l$(ARCH_LIBNAME)_venc -l$(ARCH_LIBNAME)_h265e -l$(ARCH_LIBNAME)_jpege -l$(ARCH_LIBNAME)_h264e \
							-lhi_sensor_i2c -lhi_sensor_spi \
							-l$(ARCH_LIBNAME)_ai -l$(ARCH_LIBNAME)_ao -l$(ARCH_LIBNAME)_aio -l$(ARCH_LIBNAME)_aenc -l$(ARCH_LIBNAME)_adec -l$(ARCH_LIBNAME)_acodec\
							-lhi_sensor_spi -lhi_pwm -lhi_piris \
							-l$(ARCH_LIBNAME)_ive -l$(ARCH_LIBNAME)_cipher\
							--end-group


LITEOS_LIBDEPS = --start-group $(LITEOS_LIBDEP) --end-group $(LITEOS_TABLES_LDFLAGS)

LDFLAGS := -L$(OUTDIR)/obj/kernel/liteos_a/lib $(LITEOS_LDFLAGS) --gc-sections

# target source
SRCS  := $(MPP_DIR)/src/system_init.c
SRCS  += $(MPP_DIR)/src/sdk_init.c

OBJS  := $(SRCS:%.c=%.o)
OBJS += $(COMM_OBJ)

BIN := $(TARGET_PATH)/$(TARGET).bin
MAP := $(TARGET_PATH)/$(TARGET).map

all: $(BIN)

$(BIN):$(TARGET)
	@$(OBJCOPY) -O binary $(TARGET_PATH)/$(TARGET) $(BIN)
	cp $(TARGET_PATH)/$(TARGET)* $(OUTDIR)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -Map=$(MAP) -o $(TARGET_PATH)/$(TARGET) $(OBJS) $(SDK_LIB) $(LITEOS_LIBDEPS)
	@$(OBJDUMP) -d $(TARGET_PATH)/$(TARGET) > $(TARGET_PATH)/$(TARGET).asm

$(OBJS):%.o:%.c
	@$(CC) $(CFLAGS) $(LITEOS_CFLAGS) -c $< -o $@

clean:
	@rm -f $(TARGET_PATH)/$(TARGET) $(BIN) $(MAP) $(TARGET_PATH)/*.asm
	@rm -f $(OBJS)

.PHONY : clean all

