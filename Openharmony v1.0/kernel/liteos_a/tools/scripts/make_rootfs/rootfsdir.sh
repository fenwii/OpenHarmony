#!/bin/bash
#
# Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
# Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other materials
#    provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be used
#    to endorse or promote products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
set -e

BIN_DIR=$1
LIB_DIR=$2
ROOTFS_DIR=$3
mkdir -p ${ROOTFS_DIR}/bin ${ROOTFS_DIR}/lib ${ROOTFS_DIR}/usr/bin ${ROOTFS_DIR}/usr/lib ${ROOTFS_DIR}/etc \
${ROOTFS_DIR}/app ${ROOTFS_DIR}/data ${ROOTFS_DIR}/data/system ${ROOTFS_DIR}/data/system/param \
${ROOTFS_DIR}/system ${ROOTFS_DIR}/system/internal ${ROOTFS_DIR}/system/external
if [ -d "${BIN_DIR}" ] && [ "$(ls -A "${BIN_DIR}")" != "" ]; then
    cp -f ${BIN_DIR}/* ${ROOTFS_DIR}/bin
fi
cp -f ${LIB_DIR}/* ${ROOTFS_DIR}/lib
