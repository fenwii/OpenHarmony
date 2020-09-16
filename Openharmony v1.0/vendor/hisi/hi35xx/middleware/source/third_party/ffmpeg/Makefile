LOCAL_DIR := $(shell pwd)
include $(LOCAL_DIR)/cfg.mak

GREEN="\e[32;1m"
DONE="\e[39m"
RED="\e[31m"

COMPILE_ROOT := $(LOCAL_DIR)
FFMPEG_VER := ffmpeg-y

FF_CONFIG_SH := disable_decoder_config.sh

export LITEOS_MACRO
export LITEOS_OSDRV_INCLUDE
export LITEOS_USR_INCLUDE
export LITEOS_CMACRO
export LITEOS_INCLUDE
export LITEOSTOPDIR

#override CFLAGS to avoid ffmpeg configure use
CFLAGS:=
FF_ADAPT_LITEOS=y

ORG_FFMPEG := $(FFMPEG_VER)
MODNAME := $(FFMPEG_VER)

all: $(ORG_FFMPEG)

.PHONY: $(ORG_FFMPEG) clean

install:$(ORG_FFMPEG)

clean:
	@if  [ -d $(ORG_FFMPEG)/install ]; then \
	cd $(COMPILE_ROOT)/$(ORG_FFMPEG);$(MAKE) $(MFLAGS) $(CFG_COMPILE_DIR) distclean;$(MAKE) $(MFLAGS) uninstall;rm -rf $(COMPILE_ROOT)/$(ORG_FFMPEG)/install; \
	fi

$(ORG_FFMPEG):
	@if  [ -d $(FFMPEG_VER) ]; then cd $@; chmod 777 ./* -R; ./$(FF_CONFIG_SH) $(CFG_CHIP_TYPE) $(CFG_COMPILE_DIR); cd -; fi
	@if  [ $(FF_ADAPT_LITEOS) = 'y' ]; then cd $@; ./adapt_liteos_config.sh; cd -; fi
	$(MAKE) $(MFLAGS) -j16 -C $(COMPILE_ROOT)/$@
	$(MAKE) $(MFLAGS) -C $(@) install
