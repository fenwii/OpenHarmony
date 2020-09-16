#!/bin/bash
# Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
# Description: This script is used to generate .S files.
# Create: 2020-05-30

set -e

error()
{
    echo ===========================================
    echo Create asm file FAIL!
    echo ===========================================
    exit 1
}

success()
{
    echo ===========================================
    echo Create asm file Sucess!
    echo ===========================================
    exit 0
}

rm -rf crypto/aes/asm/arm32
rm -rf crypto/modes/asm/arm32
mkdir crypto/aes/asm/arm32
mkdir crypto/modes/asm/arm32
# for arm32:
perl crypto/aes/asm/aes-armv4.pl void crypto/aes/asm/arm32/aes-armv4.S
perl crypto/aes/asm/aesv8-armx.pl void crypto/aes/asm/arm32/aesv8-armx.S
perl crypto/aes/asm/bsaes-armv7.pl void crypto/aes/asm/arm32/bsaes-armv7.S
perl crypto/armv4cpuid.pl void crypto/armv4cpuid.S
perl crypto/bn/asm/armv4-gf2m.pl void crypto/bn/armv4-gf2m.S
perl crypto/bn/asm/armv4-mont.pl void crypto/bn/armv4-mont.S
perl crypto/chacha/asm/chacha-armv4.pl void crypto/chacha/chacha-armv4.S
perl crypto/ec/asm/ecp_nistz256-armv4.pl void crypto/ec/ecp_nistz256-armv4.S
perl crypto/modes/asm/ghash-armv4.pl void crypto/modes/asm/arm32/ghash-armv4.S
perl crypto/modes/asm/ghashv8-armx.pl void crypto/modes/asm/arm32/ghashv8-armx.S
perl crypto/poly1305/asm/poly1305-armv4.pl void crypto/poly1305/poly1305-armv4.S
perl crypto/sha/asm/keccak1600-armv4.pl void crypto/sha/keccak1600-armv4.S
perl crypto/sha/asm/sha1-armv4-large.pl void crypto/sha/sha1-armv4-large.S
perl crypto/sha/asm/sha256-armv4.pl void crypto/sha/sha256-armv4.S
perl crypto/sha/asm/sha512-armv4.pl void crypto/sha/sha512-armv4.S

rm -rf crypto/aes/asm/arm64
rm -rf crypto/modes/asm/arm64
mkdir crypto/aes/asm/arm64
mkdir crypto/modes/asm/arm64
# for arm64:
perl crypto/aes/asm/aesv8-armx.pl linux64 crypto/aes/asm/arm64/aesv8-armx.S
perl crypto/aes/asm/vpaes-armv8.pl linux64 crypto/aes/asm/arm64/vpaes-armv8.S
perl crypto/arm64cpuid.pl linux64 crypto/arm64cpuid.S
perl crypto/bn/asm/armv8-mont.pl linux64 crypto/bn/armv8-mont.S
perl crypto/chacha/asm/chacha-armv8.pl linux64 crypto/chacha/chacha-armv8.S
perl crypto/ec/asm/ecp_nistz256-armv8.pl linux64 crypto/ec/ecp_nistz256-armv8.S
perl crypto/modes/asm/ghashv8-armx.pl linux64 crypto/modes/asm/arm64/ghashv8-armx.S
perl crypto/poly1305/asm/poly1305-armv8.pl linux64 crypto/poly1305/poly1305-armv8.S
perl crypto/sha/asm/keccak1600-armv8.pl linux64 crypto/sha/keccak1600-armv8.S
perl crypto/sha/asm/sha1-armv8.pl linux64 crypto/sha/sha1-armv8.S
perl crypto/sha/asm/sha512-armv8.pl linux64 crypto/sha/sha256-armv8.S
perl crypto/sha/asm/sha512-armv8.pl linux64 crypto/sha/sha512-armv8.S
if [ $? -ne 0 ]; then
    error
else
    success
fi