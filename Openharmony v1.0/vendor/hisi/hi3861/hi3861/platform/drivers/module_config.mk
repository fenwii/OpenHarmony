uart_srcs := uart
adc_srcs := adc
tsensor_srcs := tsensor
CCFLAGS += -Werror -fsigned-char
CCFLAGS += -I$(MAIN_TOPDIR)/platform/drivers/dma \
	-I$(MAIN_TOPDIR)/platform/drivers/flash
ifeq ($(CONFIG_I2C_SUPPORT), y)
	i2c_srcs += i2c
endif
ifeq ($(CONFIG_SPI_SUPPORT), y)
	spi_srcs += spi
endif
ifeq ($(CONFIG_PWM_SUPPORT), y)
	pwm_srcs += pwm
endif

