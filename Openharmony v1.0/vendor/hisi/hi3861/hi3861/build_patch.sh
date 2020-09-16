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
#
# Description: Menuconfig entry
#
set -e
CROOT=$(pwd)

build_uboot_patch() {
	if [ ! -d $CROOT/third_party/u-boot-v2019.07/u-boot-v2019.07/ ]; then
		tar -zxf u-boot-v2019.07.tar.gz
		cd u-boot-v2019.07
		patch -p1 < ./../patch/CVE-2019-13103.patch
		patch -p1 < ./../patch/CVE-2019-13104.patch
		patch -p1 < ./../patch/CVE-2019-13105.patch
		patch -p1 < ./../patch/CVE-2019-13106.patch
		patch -p1 < ./../patch/CVE-2019-14192-14193-14199.patch
		patch -p1 < ./../patch/CVE-2019-14194-14198.patch
		patch -p1 < ./../patch/CVE-2019-14195.patch
		patch -p1 < ./../patch/CVE-2019-14196.patch
		patch -p1 < ./../patch/CVE-2019-14197-14200-14201-14202-14203-14204.patch
		patch -p1 < ./../hisilicon_patch/hisilicon-u-boot-v2019.07.patch
	fi
}