# SPDX-License-Identifier: GPL-2.0+

ifndef CONFIG_SANDBOX

ifdef FTRACE
subdir-ccflags-y += -finstrument-functions -DFTRACE
endif
ifndef CONFIG_HISI_MC
subdir-y += standalone
endif
subdir-$(CONFIG_API) += api
endif
