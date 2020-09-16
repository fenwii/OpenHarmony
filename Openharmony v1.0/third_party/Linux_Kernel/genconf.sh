make HOSTCC=gcc srctree=. -f ./scripts/Makefile.build obj=scripts/basic
make HOSTCC=gcc srctree=. -f ./scripts/Makefile.build obj=scripts/kconfig menuconfig
make HOSTCC=gcc srctree=. -f ./scripts/Makefile.build obj=scripts/kconfig silentoldconfig

cp scripts/kconfig/mconf ../../kernel/liteos_a/tools/menuconfig
cp scripts/kconfig/conf ../../kernel/liteos_a/tools/menuconfig
