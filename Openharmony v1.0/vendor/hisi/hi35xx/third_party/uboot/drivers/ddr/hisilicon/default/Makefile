obj-y := ddr_training_impl.o
obj-y += ddr_training_ctl.o
obj-y += ddr_training_boot.o
obj-y += ddr_training_console.o
obj-y += ddr_training_custom.o
ifndef CONFIG_MINI_BOOT
obj-y += ddr_cmd_loc.o
obj-y += ddr_cmd_ctl.o
obj-y += cmd_ddr_training_v2.o
else
obj-y += ddr_cmd_null.o
endif
