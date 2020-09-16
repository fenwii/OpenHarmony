#!/bin/bash

# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -e

readonly MUSL_DIR="$PWD/musl"
readonly MUSL_SOURCE="$PWD/../../../../../third_party/musl/*"
export SYSROOT="$PWD/../../../../../prebuilts/gcc/linux-x86/arm/arm-linux-ohoseabi-gcc/target"
readonly LITEOSTOPDIR="$PWD/../../../../../kernel/liteos_a"

BUILD=`gcc -dumpmachine`
HOST=`gcc -dumpmachine`
TARGET=arm-linux-ohoseabi
CROSS_COMPILER=arm-linux-ohoseabi-
CFLAGS_FOR_TARGET="-O2 -Wall -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wl,-z,relro,-z,now,-z,noexecstack -Wtrampolines"

PARALLEL=`grep ^processor /proc/cpuinfo|wc -l`
LITEOS_COMPILER_PATH=`${LITEOSTOPDIR}/tools/build/mk/get_compiler_path.sh  ${CROSS_COMPILER} ${LITEOSTOPDIR}`

export PATH="${LITEOS_COMPILER_PATH}/bin:$PATH"

#prepare to build musl
mkdir -p  $MUSL_DIR
cp -r $MUSL_SOURCE $MUSL_DIR

#build musl
pushd $MUSL_DIR
CC="${LITEOS_COMPILER_PATH}/bin/${CROSS_COMPILER}gcc $CFLAGS_FOR_TARGET" ./configure  --with-headers=$SYSROOT/usr/include  --build=$BUILD --host=$TARGET
make -j $PARALLEL CROSS=$CROSS_COMPILER
popd

