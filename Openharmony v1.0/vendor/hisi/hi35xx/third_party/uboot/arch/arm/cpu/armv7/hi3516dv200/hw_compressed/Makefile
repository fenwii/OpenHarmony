################################################################################
#    Create By Hisilicon
################################################################################

PWD           = $(shell pwd)
HW_CROSS_COMPILE = $(CROSS_COMPILE)
TOPDIR        =

################################################################################
CC       := $(HW_CROSS_COMPILE)gcc
AR       := $(HW_CROSS_COMPILE)ar
LD       := $(HW_CROSS_COMPILE)ld
OBJCOPY  := $(HW_CROSS_COMPILE)objcopy


################################################################################
BOOT     := u-boot-$(SOC)
TEXTBASE := 0x40700000

CFLAGS   :=-Os -fno-builtin -ffreestanding \
	-D__KERNEL__ -DTEXT_BASE=$(TEXTBASE) \
	-I$(TOPDIR)/include \
	-I$(TOPDIR)/drivers/ddr/hisilicon/default \
	-I$(TOPDIR)/drivers/ddr/hisilicon/$(SOC) \
	-I$(TOPDIR)/arch/arm/include \
	-I$(TOPDIR)/lib/hw_dec \
	-fno-pic -ffunction-sections \
	-fdata-sections -fno-common -ffixed-r9    \
	-fno-common -pipe -march=armv7-a \
	-Wall -Wstrict-prototypes -fno-stack-protector \
	-D__LINUX_ARM_ARCH__=7 -D__ARM__ \
	-DCONFIG_MMC\
	$(MKFLAGS) -fno-strict-aliasing

################################################################################

START := start.o
COBJS := lowlevel_init_v300.o \
	init_registers.o \
	emmc_boot.o \
	uart.o \
	ddr_training_impl.o \
	ddr_training_ctl.o \
	ddr_training_boot.o \
	ddr_training_custom.o \
	ddr_training_console.o \
	pll_trainning.o \
	startup.o \
	image_data.o \
	div0.o \
	reset.o

SSRC  := arch/arm/cpu/armv7/$(SOC)/start.S \
	arch/arm/cpu/armv7/$(SOC)/reset.S \
	arch/arm/cpu/armv7/$(SOC)/emmc_boot.c \
	arch/arm/cpu/armv7/$(SOC)/himci_boot.c \
	arch/arm/cpu/armv7/$(SOC)/uart.S \
	arch/arm/cpu/armv7/$(SOC)/init_registers.c \
	arch/arm/cpu/armv7/$(SOC)/lowlevel_init_v300.c \
	drivers/ddr/hisilicon/default/ddr_training_impl.c \
	drivers/ddr/hisilicon/default/ddr_training_ctl.c \
	drivers/ddr/hisilicon/default/ddr_training_boot.c \
	drivers/ddr/hisilicon/default/ddr_training_console.c \
	drivers/ddr/hisilicon/$(SOC)/ddr_training_custom.c \
	arch/arm/cpu/armv7/$(SOC)/pll_trainning.c \
	arch/arm/lib/div0.c \
	lib/hw_dec/hw_decompress.c \
	lib/hw_dec/hw_decompress_$(SOC).c \
	lib/hw_dec/hw_decompress_v1.c \
	lib/hw_dec/hw_decompress_v1.h

REG := $(wildcard $(TOPDIR)/*.reg $(TOPDIR)/.reg)
SRC := $(notdir $(SSRC))

################################################################################
.PHONY: $(BOOT).bin
$(BOOT).bin: $(BOOT).tmp regfile
	@dd if=./$(BOOT).tmp of=./tmp1 bs=1 count=64 2>/dev/null
	@dd if=$(REG) of=./tmp2 bs=5120 conv=sync 2>/dev/null
	@dd if=./$(BOOT).tmp of=./tmp3 bs=1 skip=5184 2>/dev/null
	@cat tmp1 tmp2 tmp3 > $(BOOT).bin
	@rm -f tmp1 tmp2 tmp3
	@chmod 754 $(BOOT).bin
	@cp -fv $@ $(TOPDIR)
	@echo $(BOOT).bin is Ready.

$(BOOT).tmp: $(BOOT).elf
	$(OBJCOPY) -O srec $< $(BOOT).srec
	$(OBJCOPY) -j .text -O binary $< $(BOOT).text
	$(OBJCOPY) --gap-fill=0xff -O binary $< $@

$(BOOT).elf: image_data.gzip $(SRC) $(START) $(COBJS)
	$(LD) -Bstatic -T u-boot.lds -Ttext $(TEXTBASE) $(START) \
		$(COBJS) -Map $(BOOT).map -o $@
	$(OBJDUMP) -d  $@ > $@.asm

.PHONY: regfile
regfile:
	@if [ "$(words $(REG))" = "0" ]; then ( \
		echo '***' Need '.reg' or '*.reg' file in directory $(TOPDIR); \
		exit 1; \
	) fi
	@if [ "$(words $(REG))" != "1" ]; then ( \
		echo '***' Found multi '.reg' or '*.reg' file in directory $(TOPDIR); \
		echo '***' Files: $(notdir $(REG)); \
		exit 1; \
	) fi

################################################################################
start.o: start.S
	$(CC) -D__ASSEMBLY__ $(CFLAGS) -o $@ $< -c

# -1 : --fast      -9 : --best
image_data.gzip: $(BINIMAGE)
	./gzip -fNqc -7 $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -Wall -Wstrict-prototypes \
		-fno-stack-protector -o $@ $< -c

%.o: %.S
	$(CC) -D__ASSEMBLY__ $(CFLAGS) -o $@ $< -c

image_data.o: image_data.S image_data.gzip
	$(CC) -D__ASSEMBLY__ $(CFLAGS) -o $@ $< -c

#############################################################################

$(SRC):
	ln -sf ../../../../../../$(filter %/$@,$(SSRC)) $@
################################################################################
TMPS := $(COBJS) start.o $(SRC) \
	$(BOOT).map $(BOOT).elf $(BOOT).srec $(BOOT).bin $(BOOT).text $(BOOT).tmp \
	image_data.gzip

distclean: clean

clean:
	-rm -f $(TMPS)

################################################################################
.PHONY: clean
################################################################################
