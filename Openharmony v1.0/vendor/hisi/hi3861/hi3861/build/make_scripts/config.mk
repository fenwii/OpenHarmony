include $(MAIN_TOPDIR)/build/config/sdk.mk
include $(MAIN_TOPDIR)/build/make_scripts/usr.mk
SHELL = /bin/bash
COMPILE_MODULE += drv sys at
boot_dir := boot/flashboot
loaderboot_dir := boot/loaderboot
drv_dir := platform/drivers
sys_dir := platform/system
at_dir := components/at
hilink_dir := components/hilink
boot_libs := boot
loaderboot_libs := loaderboot
drv_libs := uart adc tsensor
sys_libs := cfg parttab upg
at_libs := at
hilink_libs := hilink
RM := rm -rf
MAKE := make
MV := mv
MAKE_DIR := mkdir -p
CC := $(TOOLS_PREFIX)gcc
AR := $(TOOLS_PREFIX)ar
AS := $(TOOLS_PREFIX)as
CXX := $(TOOLS_PREFIX)cpp
LINK := $(TOOLS_PREFIX)ld
RANLIB := $(TOOLS_PREFIX)ranlib
OBJCOPY := $(TOOLS_PREFIX)objcopy
OBJDUMP := $(TOOLS_PREFIX)objdump
NV_CFG_NAME := mss_nvi_db.xml
BASE_NUM := d11133fff0d435d699e27817e165cf1d10c1a951452bd07d40da5bcfc41ef773
LOG_PATH := build/build_tmp/logs
OBJ_PATH := build/build_tmp/objs
LIB_PATH := build/build_tmp/libs
CACHE_PATH := build/build_tmp/cache
LINK_PATH := build/build_tmp/scripts
NV_PATH := build/build_tmp/nv

LIBS += $(patsubst lib%.a, -l%, $(notdir $(wildcard $(MAIN_TOPDIR)/build/libs/*.a)))
LIBPATH += -Lbuild/scripts -Lbuild/libs -Lbuild/build_tmp/scripts
LIBS += -lwifi -lwifi_flash -lsystem -llitekernel_flash -lgcc
ifeq ($(USR_APP_ON), n)
COMPILE_MODULE += $(APP_NAME)
$(APP_NAME)_dir := app/$(APP_NAME)
$(APP_NAME)_libs := $(APP_NAME)
endif
LIBS += $(USR_LIBS)

PYTHON_SCRIPTS = y
ifeq ($(PYTHON_SCRIPTS),y)
NV_TOOL := python3 $(MAIN_TOPDIR)/tools/nvtool/build_nv.py
OTA_TOOL := python3 $(MAIN_TOPDIR)/build/scripts/pkt_builder.py
else
NV_TOOL := cd $(MAIN_TOPDIR)/tools/nvtool;\
    $(MAIN_TOPDIR)/tools/nvtool/nv_builder
OTA_TOOL := cd $(MAIN_TOPDIR)/build/scripts;\
    $(MAIN_TOPDIR)/build/scripts/ota_builder
endif


ARFLAGS := cr
CCFLAGS := -mabi=ilp32 -march=rv32imc -falign-functions=2 -msave-restore -fno-optimize-strlen -freorder-blocks-algorithm=simple -fno-schedule-insns -fno-inline-small-functions -fno-inline-functions-called-once -mtune=size -fno-strict-aliasing -msmall-data-limit=0 -nostdinc -fno-aggressive-loop-optimizations -fno-builtin -std=c99 -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-short-enums -fno-common -Wall -Wundef -DLOS_COMPILE_LDM -fstack-protector-strong -freg-struct-return -fvisibility=hidden -pipe
ASLAGS := 
DEFINES := -DCYGPKG_POSIX_SIGNALS \
	-D__ECOS__ \
	-D__RTOS_ \
	-DPRODUCT_CFG_HAVE_FEATURE_SYS_ERR_INFO \
	-D__LITEOS__ \
	-DLIB_CONFIGURABLE \
	-DLOSCFG_SHELL \
	-DLOSCFG_CACHE_STATICS \
	-DCUSTOM_AT_COMMAND \
	-DLOS_COMPILE_LDM \
	-DLOS_CONFIG_IPERF3 \
	-DPRODUCT_USR_SOFT_VER_STR=\"None\" \
	-DSECUREC_ENABLE_SCANF_FILE=0
INCLUDE := -I$(MAIN_TOPDIR)/include \
	-I$(MAIN_TOPDIR)/platform/include \
	-I$(MAIN_TOPDIR)/config \
	-I$(MAIN_TOPDIR)/config/nv \
	-I$(MAIN_TOPDIR)/../../../../utils/native/liteos/include \
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/kernel/include \
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/kernel/base/include \
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/include \
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/plat/riscv
LINKFLAGS := -nostartfiles -nostdlib -static --gc-sections

LINK_SCRIPTS_FLAG := -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/kernel/include -I$(MAIN_TOPDIR)/config
LINK_SCRIPTS_FLAG += 
ifeq ($(CONFIG_I2C_SUPPORT), y)
	drv_libs += i2c
endif
ifeq ($(CONFIG_SPI_SUPPORT), y)
	drv_libs += spi
endif
ifeq ($(CONFIG_PWM_SUPPORT), y)
	drv_libs += pwm
endif
ifeq ($(CONFIG_I2C_SUPPORT), y)
	DEFINES += -DCONFIG_I2C_SUPPORT
endif
ifeq ($(CONFIG_DMA_SUPPORT), y)
	DEFINES += -DCONFIG_DMA_SUPPORT
endif
ifeq ($(CONFIG_SPI_SUPPORT), y)
	DEFINES += -DCONFIG_SPI_SUPPORT
endif
ifeq ($(CONFIG_PWM_SUPPORT), y)
	DEFINES += -DCONFIG_PWM_SUPPORT
endif
ifeq ($(CONFIG_PWM_HOLD_AFTER_REBOOT), y)
	DEFINES += -DCONFIG_PWM_HOLD_AFTER_REBOOT
endif
ifeq ($(CONFIG_I2S_SUPPORT), y)
	DEFINES += -DCONFIG_I2S_SUPPORT
endif
ifeq ($(CONFIG_COMPRESSION_OTA_SUPPORT), y)
	DEFINES += -DCONFIG_COMPRESSION_OTA_SUPPORT
endif
ifeq ($(CONFIG_DUAL_PARTITION_OTA_SUPPORT), y)
	DEFINES += -DCONFIG_DUAL_PARTITION_OTA_SUPPORT
endif
ifeq ($(CONFIG_AT_SUPPORT), y)
	DEFINES += -DCONFIG_AT_COMMAND
endif
ifeq ($(LOSCFG_DAQ), y)
	DEFINES += -DFEATURE_DAQ
endif
ifeq ($(LOSCFG_BACKTRACE), y)
	DEFINES += -DLOS_BACKTRACE
endif
ifeq ($(CONFIG_UART0_SUPPORT), y)
	DEFINES += -DCONFIG_UART0_SUPPORT
endif
ifeq ($(CONFIG_UART1_SUPPORT), y)
	DEFINES += -DCONFIG_UART1_SUPPORT
endif
ifeq ($(CONFIG_UART2_SUPPORT), y)
	DEFINES += -DCONFIG_UART2_SUPPORT
endif
ifeq ($(CONFIG_TARGET_CHIP_HI3861), y)
	DEFINES += -DCHIP_VER_Hi3861 -DPRODUCT_CFG_CHIP_VER_STR=\"Hi3861V100\" -DCONFIG_CHIP_PRODUCT_NAME=\"Hi3861\"
endif
ifeq ($(CONFIG_CHIP_PKT_48K), y)
	DEFINES += -DCONFIG_CHIP_PKT_48K
endif
ifeq ($(CONFIG_CHIP_PKT_32K), y)
	DEFINES += -DCONFIG_CHIP_PKT_32K
endif
ifeq ($(LOSCFG_COMPILER_HI3861_ASIC), y)
	DEFINES += -DHI_BOARD_ASIC
else
	DEFINES += -DHI_BOARD_FPGA
endif
ifeq ($(LOSCFG_COMPILER_HI3861_FLASH), y)
	DEFINES += -DHI_ON_FLASH
else
	DEFINES += -DHI_ON_RAM
endif
ifeq ($(CONFIG_MESH_SUPPORT), y)
	DEFINES += -DCONFIG_MESH_SUPPORT -DLOS_CONFIG_MESH -DLOS_CONFIG_MESH_GTK -DCONFIG_MESH -DCONFIG_SAE -DCONFIG_ECC -DLOS_CONFIG_HOSTAPD_MGMT -DLOSCFG_APP_MESH -DLWIP_DEBUG_OPEN -DLWIP_SMALL_SIZE_MESH=1
else
	DEFINES += -DLWIP_SMALL_SIZE_MESH=0
endif
ifeq ($(CONFIG_LWIP_SMALL_SIZE), y)
	DEFINES += -DCONFIG_LWIP_SMALL_SIZE
endif
ifeq ($(CONFIG_LWIP_SMALL_SIZE_MESH), y)
	DEFINES += -DCONFIG_LWIP_SMALL_SIZE_MESH
endif
ifeq ($(CONFIG_NETIF_HOSTNAME), y)
	DEFINES += -DCONFIG_NETIF_HOSTNAME
endif
ifeq ($(CONFIG_DHCP_VENDOR_CLASS_IDENTIFIER), y)
	DEFINES += -DCONFIG_DHCP_VENDOR_CLASS_IDENTIFIER
endif
ifeq ($(CONFIG_DHCPS_GW), y)
	DEFINES += -DCONFIG_DHCPS_GW
endif
ifeq ($(CONFIG_UART_DMA_SUPPORT), y)
	DEFINES += -DCONFIG_UART_DMA_SUPPORT
endif
ifeq ($(CONFIG_SDIO_SUPPORT), y)
	DEFINES += -DCONFIG_SDIO_SUPPORT
endif
ifeq ($(CONFIG_SPI_DMA_SUPPORT), y)
	DEFINES += -DCONFIG_SPI_DMA_SUPPORT
endif
ifeq ($(CONFIG_TEE_HUKS_SUPPORT), y)
	DEFINES += -DCONFIG_TEE_HUKS_SUPPORT
endif
ifeq ($(CONFIG_TEE_HUKS_DEMO_SUPPORT), y)
	DEFINES += -DCONFIG_TEE_HUKS_DEMO_SUPPORT
endif
ifeq ($(CONFIG_FLASH_ENCRYPT_SUPPORT), y)
	DEFINES += -DCONFIG_FLASH_ENCRYPT_SUPPORT
endif
ifeq ($(LOSCFG_KASAN)_$(LOSCFG_KASAN_EXAMPLES_DEMO), y_y)
	DEFINES += -DLOSCFG_DEBUG_KASAN
endif
ifeq ($(LOSCFG_KASAN)_$(LOSCFG_KASAN_LITEOS_NET_COAP), y_y)
	DEFINES += -DLOSCFG_DEBUG_KASAN
endif
ifeq ($(LOSCFG_BACKTRACE), y)
	ASLAGS += -fno-omit-frame-pointer
endif
ifeq ($(HB_LITEOS_COMPILE_TESTCASE), y)
	LINK_SCRIPTS_FLAG += -DHI1131TEST
endif
ifeq ($(LOSCFG_KASAN), y)
	LINK_SCRIPTS_FLAG += -DLOSCFG_DEBUG_KASAN
endif
ifeq ($(CONFIG_FLASH_ENCRYPT_SUPPORT), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_FLASH_ENCRYPT_SUPPORT
endif
ifeq ($(CONFIG_TEE_HUKS_SUPPORT), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_TEE_HUKS_SUPPORT
endif
ifeq ($(CONFIG_TARGET_SIG_RSA_V15), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_TARGET_SIG_RSA_V15
endif
ifeq ($(CONFIG_TARGET_SIG_RSA_PSS), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_TARGET_SIG_RSA_PSS
endif
ifeq ($(CONFIG_TARGET_SIG_ECC), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_TARGET_SIG_ECC
endif
ifeq ($(CONFIG_CHIP_PKT_48K), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_CHIP_PKT_48K
endif
ifeq ($(CONFIG_CHIP_PKT_32K), y)
	LINK_SCRIPTS_FLAG += -DCONFIG_CHIP_PKT_32K
endif
ifeq ($(LOSCFG_COMPILER_HI3861_ASIC), y)
	LINK_SCRIPTS_FLAG += -DHI_BOARD_ASIC
else
	LINK_SCRIPTS_FLAG += -DHI_BOARD_FPGA
endif
ifeq ($(LOSCFG_COMPILER_HI3861_FLASH), y)
	LINK_SCRIPTS_FLAG += -DHI_ON_FLASH
else
	LINK_SCRIPTS_FLAG += -DHI_ON_RAM
endif
ifeq ($(LOSCFG_KERNEL_RUNSTOP), y)
	INCLUDE += -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/kernel/extended/runstop
endif
ifeq ($(LOSCFG_COMPAT_POSIX), y)
	INCLUDE += -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/posix/include
endif
ifeq ($(LOSCFG_COMPAT_LINUX), y)
	INCLUDE += -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/linux/include
endif
ifeq ($(LOSCFG_SHELL), y)
	INCLUDE += -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/shell/include
endif
ifeq ($(LOSCFG_NET_TELNET), y)
	INCLUDE += -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/net/telnet/include
endif
ifeq ($(LOSCFG_LIB_LIBC), y)
	INCLUDE += -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/lib/libc/hw/include\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/lib/libc/musl/include\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/lib/libc/musl/arch/generic\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/lib/libc/musl/arch/riscv32\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/lib/libc/nuttx/include\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/components/lib/libsec/include\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/config\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/user\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/plat\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/targets/hi3861v100/extend/include\
	-I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/arch
endif
ifeq ($(LOSCFG_NET_LWIP_SACK), y)
	INCLUDE += -I$(MAIN_TOPDIR)/third_party/lwip_sack/include
endif
ifeq ($(LOSCFG_BACKTRACE), y)
	CCFLAGS += -fno-omit-frame-pointer
endif
ifeq ($(LOSCFG_KASAN)_$(LOSCFG_KASAN_EXAMPLES_DEMO), y_y)
	CCFLAGS += -fsanitize=kernel-address -fasan-shadow-offset=1835008 --param asan-stack=1 -fsanitize=bounds-strict
endif
ifeq ($(LOSCFG_KASAN)_$(LOSCFG_KASAN_LITEOS_NET_COAP), y_y)
	CCFLAGS += -fsanitize=kernel-address -fasan-shadow-offset=1835008 --param asan-stack=1 -fsanitize=bounds-strict
endif
ifeq ($(CONFIG_HILINK), y)
	COMPILE_MODULE += hilink
endif
ifeq ($(CONFIG_HILINK), y)
	DEFINES += -DCONFIG_HILINK
endif

ifeq ($(FACTORY_MODE), y)
DEFINES += -DCONFIG_FACTORY_TEST_MODE
endif
LIBS += $(addprefix -l, $(foreach module, $(COMPILE_MODULE), $($(module)_libs)))
ifeq ($(CONFIG_CE_SUPPORT), y)
	NV_CFG_NAME = mss_nvi_db.xml
endif
ifeq ($(CONFIG_FCC_SUPPORT), y)
	NV_CFG_NAME = mss_nvi_db_fcc.xml
endif
ifeq ($(CONFIG_MAX_POWER_SUPPORT), y)
	NV_CFG_NAME = mss_nvi_db_max.xml
endif
CCFLAGS += $(DEFINES) $(INCLUDE)
