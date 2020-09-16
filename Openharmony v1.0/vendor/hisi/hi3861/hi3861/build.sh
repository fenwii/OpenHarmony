#!/bin/bash
#
# Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# Description: Menuconfig entry
#
set -e
set -o pipefail
CROOT=$(pwd)
source $CROOT/build_patch.sh
BUILD_SELECT=$1

cd $CROOT/third_party/u-boot-v2019.07
build_uboot_patch
cd $CROOT

if [ "$BUILD_SELECT" = "menuconfig" ]; then
	python3 $CROOT/tools/menuconfig/usr_config.py
elif [ "$BUILD_SELECT" = "clean" ]; then
	scons -c
elif [ "$BUILD_SELECT" = "all_clean" ]; then
	scons -c
	rm -rf third_party/u-boot-v2019.07/u-boot-v2019.07
	rm -rf .sconsign.dblite
	rm -rf build/config/usr_config.mk.old
elif [ "$BUILD_SELECT" = "all" ]; then
	if [ $(grep -cw "CONFIG_FACTORY_TEST_SUPPORT=y" $CROOT/build/config/usr_config.mk) != 0 ]; then
		echo Start build factory bin.
		rm -rf build/libs/factory_bin
		scons -c
		if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
			mkdir -p $CROOT/build/build_tmp/logs
		fi
		scons -Q factory_mode='yes' 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
		if [ -f build/libs/factory_bin/*_factory.bin ];  then
			scons -c
			if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
				mkdir -p $CROOT/build/build_tmp/logs
			fi
			scons -Q 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
			echo See build log from: $CROOT/build/build_tmp/logs/build_kernel.log
		fi
	else
		rm -rf build/libs/factory_bin
		if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
			mkdir -p $CROOT/build/build_tmp/logs
		fi
		scons -Q 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
		echo See build log from: $CROOT/build/build_tmp/logs/build_kernel.log
	fi
elif [ -z $BUILD_SELECT ]; then
	if [ -d "output/bin" ]; then
		rm -rf output/bin
	fi
	if [ $(grep -cw "CONFIG_FACTORY_TEST_SUPPORT=y" $CROOT/build/config/usr_config.mk) != 0 ]; then
		echo Start build factory bin.
		rm -rf build/libs/factory_bin
		scons -c
		if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
			mkdir -p $CROOT/build/build_tmp/logs
		fi
		scons -Q factory_mode='yes' 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
		if [ -f build/libs/factory_bin/*_factory.bin ];  then
			scons -c
			if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
				mkdir -p $CROOT/build/build_tmp/logs
			fi
			scons -Q 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
			echo See build log from: $CROOT/build/build_tmp/logs/build_kernel.log
		fi
	else
		rm -rf build/libs/factory_bin
		if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
			mkdir -p $CROOT/build/build_tmp/logs
		fi
		scons -Q 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
		echo See build log from: $CROOT/build/build_tmp/logs/build_kernel.log
	fi
else
	if [ $(grep -cw "CONFIG_FACTORY_TEST_SUPPORT=y" $CROOT/build/config/usr_config.mk) != 0 ]; then
		echo Start build factory bin.
		rm -rf build/libs/factory_bin
		scons -c
		if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
			mkdir -p $CROOT/build/build_tmp/logs
		fi
		scons -Q app=$BUILD_SELECT factory_mode='yes' 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
		if [ -f build/libs/factory_bin/*_factory.bin ];  then
			scons -c
			if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
				mkdir -p $CROOT/build/build_tmp/logs
			fi
			scons -Q app=$BUILD_SELECT 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
			echo See build log from: $CROOT/build/build_tmp/logs/build_kernel.log
		fi
	else
		rm -rf build/libs/factory_bin
		if [ ! -d $CROOT/build/build_tmp/logs/ ]; then
			mkdir -p $CROOT/build/build_tmp/logs
		fi
		scons -Q app=$BUILD_SELECT 2>&1 | tee $CROOT/build/build_tmp/logs/build_kernel.log
		echo See build log from: $CROOT/build/build_tmp/logs/build_kernel.log
	fi
fi
