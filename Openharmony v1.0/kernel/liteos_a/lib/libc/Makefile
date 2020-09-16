include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := c

$(shell ln -snf $(LITEOSTHIRDPARTY)/musl/kernel/ musl)

LOCAL_SRCS = $(wildcard musl/src/ctype/*.c) \
    $(wildcard musl/src/env/*.c) \
    $(wildcard musl/src/errno/*.c) \
    $(wildcard musl/src/exit/*.c) \
    $(wildcard musl/src/internal/*.c) \
    $(wildcard musl/src/linux/*.c) \
    $(wildcard musl/src/locale/*.c) \
    $(wildcard musl/src/malloc/*.c) \
    $(wildcard musl/src/math/*.c) \
    $(wildcard musl/src/multibyte/*.c) \
    $(wildcard musl/src/network/*.c) \
    $(wildcard musl/src/prng/*.c) \
    $(wildcard musl/src/sched/*.c) \
    $(wildcard musl/src/stdio/*.c) \
    $(wildcard musl/src/stdlib/*.c) \
    $(wildcard musl/src/string/*.c) \
    $(wildcard musl/src/time/*.c)

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/lib/libc/musl/include \
    -I $(LITEOSTOPDIR)/lib/libc/musl/arch/arm \
    -I $(LITEOSTOPDIR)/lib/libc/musl/arch/generic \
    -I $(LITEOSTOPDIR)/lib/libc/musl/obj/include \
    -I $(LITEOSTOPDIR)/lib/libc/musl/src/include \
    -I $(LITEOSTOPDIR)/lib/libc/musl/src/dirent \
    -I $(LITEOSTOPDIR)/lib/libc/musl/src/errno \
    -I $(LITEOSTOPDIR)/lib/libc/musl/src/internal \
    -I $(LITEOSTOPDIR)/lib/libc/musl/src/multibyte \
    -I $(LITEOSTOPDIR)/lib/libc/musl/src/time \
    -I $(LITEOSTOPDIR)/syscall \
    -I $(LITEOSTOPDIR)/bsd/dev/random \
    -I $(LITEOSTOPDIR)/bsd/compat/linuxkpi/include
ifeq ($(LOSCFG_LLTSER), y)
LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/tools/gcov_ser
endif

LOCAL_FLAGS := $(LOCAL_INCLUDE)
ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LOCAL_FLAGS +=-Wno-char-subscripts -Wno-unknown-pragmas
else
LOCAL_FLAGS += -frounding-math -Wno-unused-but-set-variable -Wno-unknown-pragmas
endif

include $(MODULE)
