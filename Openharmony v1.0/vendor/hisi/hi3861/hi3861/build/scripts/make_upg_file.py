#!/usr/bin/env python3
# coding=utf-8

'''
* Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Description: part of hupg build scripts
'''

import os
import re
import hashlib
import sys
import subprocess
import struct
from ctypes import *
from Crypto.Hash import SHA
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
from Crypto.Signature import PKCS1_v1_5 as Signature_pkcs1_v1_5
from Crypto.Signature import PKCS1_PSS as Signature_pss
from ecdsa import SigningKey
from ecdsa import VerifyingKey
import make_upg_user_info as USER_INFO

###############################定义基本类型###############################################
hi_char=c_char
hi_s8=c_byte
hi_u8=c_ubyte
hi_s16=c_short
hi_u16=c_ushort
hi_s32=c_int
hi_u32=c_uint

class sign_alg_param(Structure):
    _fields_ = [
        ("hash_alg", hi_u32, 16),
        ("sign_alg", hi_u32, 6),
        ("sign_param", hi_u32, 10),
        ]

class upg_rsa_key(Structure):
    _fields_ = [
        ("mod_n", hi_u8*256),
        ("exp_e", hi_u8*4),
        ("padding", hi_u8*28),
        ]

class upg_rsa_sign(Structure):
    _fields_ = [
        ("sign", hi_u8*256),
        ]

class upg_ecc_key(Structure):
    _fields_ = [
        ("px", hi_u8*32),
        ("py", hi_u8*32),
        ("padding", hi_u8*224),
        ]

class upg_ecc_sign(Structure):
    _fields_ = [
        ("r", hi_u8*32),
        ("s", hi_u8*32),
        ("padding", hi_u8*192),
        ]

class upg_sha256_key(Structure):
    _fields_ = [
        ("padding", hi_u8*288),
        ]

class upg_sha256_sign(Structure):
    _fields_ = [
        ("check_sum", hi_u8*32),
        ("padding", hi_u8*224),
        ]

class hi_upg_user_info(Structure):
    _fields_ = [
        ("reserved", hi_u8*32),
        ]

class hi_upg_common_head(Structure):
    _fields_ = [
        ("image_id", hi_u32),
        ("struct_version", hi_u32),
        ("section_offset", hi_u32),
        ("section_len", hi_u32),
        ("user_info", hi_upg_user_info),
        ("file_type", hi_u8),
        ("file_version", hi_u8),
        ("encrypt_flag", hi_u8),
        ("file_attr", hi_u8),
        ("file_len", hi_u32),
        ("key_len", hi_u32),
        ("param", sign_alg_param),
        ("aes_key", hi_u8*16),
        ("aes_iv", hi_u8*16),
        ]

class hi_upg_section_head(Structure):
    _fields_ = [
        ("image_id", hi_u32),
        ("struct_version", hi_u32),
        ("param", sign_alg_param),
        ("section_count", hi_u8),
        ("reserved", hi_u8*27),
        ("section0_compress", hi_u8),
        ("pad0", hi_u8*3),
        ("section0_offset", hi_u32),
        ("section0_len", hi_u32),
        ("section1_compress", hi_u8),
        ("pad1", hi_u8*3),
        ("section1_offset", hi_u32),
        ("section1_len", hi_u32),
        ]

def lzma_compress_bin(src_file, dst_file, lzma_tool):
    print('lzma compress tool :', lzma_tool)
    print('lzma    src   file :', src_file)
    print('lzma    out   file :', dst_file)
    cmd_list = []
    cmd_list.append(lzma_tool)
    cmd_list.append('-d16 -lc2 -lp2 e')
    cmd_list.append(src_file)
    cmd_list.append(dst_file)
    str_cmd=' '.join(cmd_list)
    subprocess.run(str_cmd, shell=True)

def aes_encrypt_bin(src_file, dst_file, offset, size, aes_key_file, aes_encrypt_tool):
    print('aes encrypt src file:', src_file)
    print('aes encrypt out file:', dst_file)
    print('aes key file :', aes_key_file)
    print('aes encrypt tool :', aes_encrypt_tool)
    cmd_list = []
    cmd_list.append(aes_encrypt_tool)
    cmd_list.append('-i')
    cmd_list.append(src_file)
    cmd_list.append('-o')
    cmd_list.append(dst_file)
    cmd_list.append('-u')
    cmd_list.append(aes_key_file)
    cmd_list.append('-f %x'%(offset))
    cmd_list.append('-z %x'%(size))
    str_cmd=' '.join(cmd_list)
    print("[aes-str-cmd]", str_cmd)
    subprocess.run(str_cmd, shell=True)

def print_upg_info(image_file, upg_bin):
    st_hupg = hi_upg_common_head.from_buffer(upg_bin)

    print("-------------%s image info print start-------------"%(image_file))
    print("[image_id=0x%x][struct_version=0x%x]]"%(st_hupg.image_id, st_hupg.struct_version))
    print("[section_offset=0x%x][section_len=0x%x]"%(st_hupg.section_offset, st_hupg.section_len))
    print("[file_type=0x%x][file_version=0x%x][encrypt_flag=0x%x]"%(
        st_hupg.file_type, st_hupg.file_version, st_hupg.encrypt_flag))
    print("[file_len=0x%x][key_len=0x%x]"%(st_hupg.file_len, st_hupg.key_len))
    print("[file_attr=0x%x]"%(st_hupg.file_attr))
    print("[hash_alg=0x%x][sign_alg=0x%x][sign_param=0x%x]"%(
        st_hupg.param.hash_alg, st_hupg.param.sign_alg, st_hupg.param.sign_param))
    print("[aes_key[0-1-14-15]=[0x%x][0x%x][0x%x][0x%x]]"%(
        st_hupg.aes_key[0], st_hupg.aes_key[1], st_hupg.aes_key[14], st_hupg.aes_key[15]))
    print("[aes_iv [0-1-14-15]=[0x%x][0x%x][0x%x][0x%x]]"%(
        st_hupg.aes_iv[0], st_hupg.aes_iv[1], st_hupg.aes_iv[14], st_hupg.aes_iv[15]))

    #打印common段key信息、common段签名信息、section段签名信息
    if st_hupg.param.sign_alg < 0x10:
        common_key_offset = sizeof(hi_upg_common_head)
        common_sign_offset = sizeof(hi_upg_common_head) + st_hupg.key_len
        section_sign_offset = st_hupg.section_offset + sizeof(hi_upg_section_head)
        print('[common key][000]=[0x%x]'%(upg_bin[common_key_offset]))
        print('[common key][001]=[0x%x]'%(upg_bin[common_key_offset + 1]))
        print('[common key][254]=[0x%x]'%(upg_bin[common_key_offset + 254]))
        print('[common key][255]=[0x%x]'%(upg_bin[common_key_offset + 255]))
        print('[common sign][000]=[0x%x]'%(upg_bin[common_sign_offset]))
        print('[common sign][001]=[0x%x]'%(upg_bin[common_sign_offset + 1]))
        print('[common sign][254]=[0x%x]'%(upg_bin[common_sign_offset + 254]))
        print('[common sign][255]=[0x%x]'%(upg_bin[common_sign_offset + 255]))
        print('[section sign][000]=[0x%x]'%(upg_bin[section_sign_offset]))
        print('[section sign][001]=[0x%x]'%(upg_bin[section_sign_offset + 1]))
        print('[section sign][254]=[0x%x]'%(upg_bin[section_sign_offset + 254]))
        print('[section sign][255]=[0x%x]'%(upg_bin[section_sign_offset + 255]))
    elif st_hupg.param.sign_alg == 0x10:
        common_key_offset = sizeof(hi_upg_common_head)
        common_sign_offset = sizeof(hi_upg_common_head) + st_hupg.key_len
        section_sign_offset = st_hupg.section_offset + sizeof(hi_upg_section_head)
        print('[common key][00]=[0x%x]'%(upg_bin[common_key_offset]))
        print('[common key][01]=[0x%x]'%(upg_bin[common_key_offset + 1]))
        print('[common key][62]=[0x%x]'%(upg_bin[common_key_offset + 62]))
        print('[common key][63]=[0x%x]'%(upg_bin[common_key_offset + 63]))
        print('[common sign][00]=[0x%x]'%(upg_bin[common_sign_offset]))
        print('[common sign][01]=[0x%x]'%(upg_bin[common_sign_offset + 1]))
        print('[common sign][62]=[0x%x]'%(upg_bin[common_sign_offset + 62]))
        print('[common sign][63]=[0x%x]'%(upg_bin[common_sign_offset + 63]))
        print('[section sign][00]=[0x%x]'%(upg_bin[section_sign_offset]))
        print('[section sign][01]=[0x%x]'%(upg_bin[section_sign_offset + 1]))
        print('[section sign][62]=[0x%x]'%(upg_bin[section_sign_offset + 62]))
        print('[section sign][63]=[0x%x]'%(upg_bin[section_sign_offset + 63]))
    else:
        common_key_offset = sizeof(hi_upg_common_head)
        common_sign_offset = sizeof(hi_upg_common_head) + st_hupg.key_len
        section_sign_offset = st_hupg.section_offset + sizeof(hi_upg_section_head)
        print('[common key][00]=[0x%x]'%(upg_bin[common_key_offset]))
        print('[common key][01]=[0x%x]'%(upg_bin[common_key_offset+1]))
        print('[common key][30]=[0x%x]'%(upg_bin[common_key_offset+30]))
        print('[common key][31]=[0x%x]'%(upg_bin[common_key_offset+31]))
        print('[common sign][00]=[0x%x]'%(upg_bin[common_sign_offset]))
        print('[common sign][01]=[0x%x]'%(upg_bin[common_sign_offset+1]))
        print('[common sign][30]=[0x%x]'%(upg_bin[common_sign_offset+30]))
        print('[common sign][31]=[0x%x]'%(upg_bin[common_sign_offset+31]))
        print('[section sign][00]=[0x%x]'%(upg_bin[section_sign_offset]))
        print('[section sign][01]=[0x%x]'%(upg_bin[section_sign_offset+1]))
        print('[section sign][30]=[0x%x]'%(upg_bin[section_sign_offset+30]))
        print('[section sign][31]=[0x%x]'%(upg_bin[section_sign_offset+31]))

    #打印section段固定头信息
    section_head = hi_upg_section_head.from_buffer(
        upg_bin[st_hupg.section_offset:st_hupg.section_offset + sizeof(hi_upg_section_head)])
    print("[image_id=0x%x][struct_version=0x%x]]"%(
        section_head.image_id, section_head.struct_version))
    print("[hash_alg=0x%x][sign_alg=0x%x][sign_param=0x%x]"%(
        section_head.param.hash_alg, section_head.param.sign_alg, section_head.param.sign_param))
    print("[section_count=0x%x]"%(section_head.section_count))
    print("[section0_compress=0x%x][section0_offset=0x%x][section0_len=0x%x]"%(section_head.section0_compress, section_head.section0_offset, section_head.section0_len))
    print("[section1_compress=0x%x][section1_offset=0x%x][section1_len=0x%x]"%(section_head.section1_compress, section_head.section1_offset, section_head.section1_len))
    print("-------------%s image info print end--------------"%(image_file))

def print_hbin_info(image_file, upg_bin, bin_size):
    st_hupg = hi_upg_common_head.from_buffer(upg_bin)
    print("-------------%s image info print start-------------"%(image_file))
    print("[bin_size]=[0x%x]"%(bin_size))
    print("[image_id=0x%x][struct_version=0x%x]]"%(st_hupg.image_id, st_hupg.struct_version))
    print("[section_offset=0x%x][section_len=0x%x]"%(st_hupg.section_offset, st_hupg.section_len))
    print("[file_type=0x%x][file_version=0x%x][encrypt_flag=0x%x]"%(
        st_hupg.file_type, st_hupg.file_version, st_hupg.encrypt_flag))
    print("[file_len=0x%x][key_len=0x%x]"%(st_hupg.file_len, st_hupg.key_len))
    print("[hash_alg=0x%x][sign_alg=0x%x][sign_param=0x%x]"%(
        st_hupg.param.hash_alg, st_hupg.param.sign_alg, st_hupg.param.sign_param))
    print("[aes_key[0,1,14,15]=[0x%x][0x%x][0x%x][0x%x]]"%(
        st_hupg.aes_key[0], st_hupg.aes_key[1], st_hupg.aes_key[14], st_hupg.aes_key[15]))
    print("[aes_iv[0,1,14,15]=[0x%x][0x%x][0x%x][0x%x]]"%(
        st_hupg.aes_iv[0], st_hupg.aes_iv[1], st_hupg.aes_iv[14], st_hupg.aes_iv[15]))
    print("-------------%s image info print end--------------"%(image_file))

def int_2_bin_list(val, array_size):
    L = bytearray(array_size)
    i = array_size - 1

    while i != 0:
        L[i] = val%256
        val = val//256
        i = i - 1
    L[0] = val
    return (L)

def convert_int(value):
    match1 = re.match(r'\s*0x', value)
    match2 = re.match(r'\s*0X', value)
    if match1 or match2:
        return int(value, 16)
    else:
        return int(value, 10)

def make_secure_key(alg_dir_path, sign_alg):
    if sign_alg < 0x10:
        key_bin = bytearray(sizeof(upg_rsa_key))
        rsa_key = upg_rsa_key.from_buffer(key_bin)
        second_key_dir = os.path.join(alg_dir_path, r'upg_private_rsa_2.pem')
        with open(second_key_dir, 'rb') as f:
            temp_bin = f.read()
            second_key = RSA.importKey(temp_bin)
            key_n_2 = int_2_bin_list(second_key.n, sizeof(rsa_key.mod_n))
        key_bin[0:sizeof(rsa_key.mod_n)] = key_n_2
        key_bin[sizeof(rsa_key.mod_n):sizeof(rsa_key.mod_n) + sizeof(rsa_key.exp_e)] = int_2_bin_list(65537, sizeof(rsa_key.exp_e)) #exp_e
    elif sign_alg == 0x10:
        key_bin = bytearray(sizeof(upg_ecc_key))
        ecc_key = upg_ecc_key.from_buffer(key_bin)
        second_key_dir = os.path.join(alg_dir_path, r'upg_private_ecc_2.pem')
        with open(second_key_dir) as f:
            sk = SigningKey.from_pem(f.read())
            vk = sk.verifying_key
            second_key = vk.to_string().hex()
            key = bytearray.fromhex(second_key)
        key_bin[0:(sizeof(ecc_key.px) + sizeof(ecc_key.py))] = key
    else:
        key_bin = bytearray(sizeof(upg_sha256_key))
    return key_bin

def make_rsa_pss_signature(alg_dir_path, common_head_content, section_content):
    first_key_dir = os.path.join(alg_dir_path, r'upg_private_rsa_1.pem')
    second_key_dir = os.path.join(alg_dir_path, r'upg_private_rsa_2.pem')
    with open(first_key_dir, 'rb') as f:
        temp_bin = f.read()
        first_key = RSA.importKey(temp_bin)

    with open(second_key_dir, 'rb') as f:
        temp_bin = f.read()
        second_key = RSA.importKey(temp_bin)

    signer = Signature_pss.new(first_key)
    digest = SHA256.new()
    digest.update(bytes(common_head_content))
    signature_1 = signer.sign(digest)

    signer = Signature_pss.new(second_key)
    digest = SHA256.new()
    digest.update(bytes(section_content))
    signature_2 = signer.sign(digest)

    return (signature_1, signature_2)

def make_rsa_pkcs_signature(alg_dir_path, common_head_content, section_content):
    first_key_dir = os.path.join(alg_dir_path, r'upg_private_rsa_1.pem')
    second_key_dir = os.path.join(alg_dir_path, r'upg_private_rsa_2.pem')
    with open(first_key_dir, 'rb') as f:
        temp_bin = f.read()
        first_key = RSA.importKey(temp_bin)

    with open(second_key_dir, 'rb') as f:
        temp_bin = f.read()
        second_key = RSA.importKey(temp_bin)

    signer = Signature_pkcs1_v1_5.new(first_key)
    digest = SHA256.new()
    digest.update(bytes(common_head_content))
    signature_1 = signer.sign(digest)

    signer = Signature_pkcs1_v1_5.new(second_key)
    digest = SHA256.new()
    digest.update(bytes(section_content))
    signature_2 = signer.sign(digest)

    return (signature_1, signature_2)

def make_ecc_secure_signature(alg_dir_path, common_head_content, section_content):
    first_key_dir = os.path.join(alg_dir_path, r'upg_private_ecc_1.pem')
    second_key_dir = os.path.join(alg_dir_path, r'upg_private_ecc_2.pem')
    with open(first_key_dir, 'rb') as f:
        first_key = SigningKey.from_pem(f.read())

    with open(second_key_dir, 'rb') as f:
        second_key = SigningKey.from_pem(f.read())

    signature_1 = first_key.sign(common_head_content, hashfunc=hashlib.sha256)
    signature_2 = second_key.sign(section_content, hashfunc=hashlib.sha256)

    signature_1_bin = bytearray(sizeof(upg_ecc_sign))
    signature = upg_ecc_sign.from_buffer(signature_1_bin)
    signature_1_bin[0:sizeof(signature.r) + sizeof(signature.s)] = signature_1
    signature_2_bin = bytearray(sizeof(upg_ecc_sign))
    signature = upg_ecc_sign.from_buffer(signature_2_bin)
    signature_2_bin[0:sizeof(signature.r) + sizeof(signature.s)] = signature_2

    return (signature_1_bin, signature_2_bin)

def make_sha256_unsecure_signature(common_head_content, section_content):
    #common段非安全签名
    signature_1_bin = bytearray(sizeof(upg_sha256_sign))
    signature = upg_sha256_sign.from_buffer(signature_1_bin)
    common_head_sh = hashlib.sha256()
    common_head_sh.update(common_head_content)
    common_head_hash = common_head_sh.digest()
    signature_1_bin[0:sizeof(signature.check_sum)] = common_head_hash

    #section段非安全签名
    signature_2_bin = bytearray(sizeof(upg_sha256_sign))
    signature = upg_sha256_sign.from_buffer(signature_2_bin)
    section_head_sh = hashlib.sha256()
    section_head_sh.update(section_content)
    section_head_hash = section_head_sh.digest()
    signature_2_bin[0:sizeof(signature.check_sum)] = section_head_hash
    return (signature_1_bin, signature_2_bin)

def make_part_offset_size(temp_offset, bin_size):
    if bin_size != 0:
        section_offset = temp_offset[0]
        section_size = bin_size
    else:
        section_offset = 0
        section_size = 0

    temp_offset[0] = temp_offset[0] + section_size
    return (section_offset, section_size)

def make_upg_get_aes_key(alg_dir_path):
    aes_key_bin = bytearray(16)
    aes_key_file = os.path.join(alg_dir_path, r'upg_aes_key.txt')
    with open(aes_key_file) as f:
        lines = f.readlines()
    aes_key_bin = bytearray.fromhex(lines[1].split(':')[1].split(';')[0].strip())
    return aes_key_bin

def make_upg_get_aes_iv(alg_dir_path):
    aes_iv_bin = bytearray(16)
    aes_key_file = os.path.join(alg_dir_path, r'upg_aes_key.txt')
    with open(aes_key_file) as f:
        lines = f.readlines()
    aes_iv_bin = bytearray.fromhex(lines[2].split(':')[1].split(';')[0].strip())
    return aes_iv_bin

def make_upg_only(image_id, file_ver, encrypt_flag, file_type, section_bin_list, section_compress_list, alg_dir_path, max_size, sign_alg, chip_name, file_attr):
    section_count = len(section_bin_list)
    section_offset_list = []
    section_size_list = []
    temp_offset = [0]

    #common固定头大小偏移
    (common_head_offset, common_head_size) = make_part_offset_size(temp_offset, sizeof(hi_upg_common_head))
    print('[common_head_offset=%d][common_head_size=%d]'%(common_head_offset, common_head_size))

    #common密钥区大小偏移、固定头签名大小偏移(不同签名算法统一按最大值处理(密钥288Byte/签名256Byte),填实际长度字节,多余的部分填0)
    if sign_alg < 0x10:
        #RSA2048
        (common_key_offset, common_key_size) = make_part_offset_size(temp_offset, sizeof(upg_rsa_key))
        (common_head_sign_offset, common_head_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_rsa_sign))
    elif sign_alg == 0x10:
        #ECDSA256
        (common_key_offset, common_key_size) = make_part_offset_size(temp_offset, sizeof(upg_ecc_key))
        (common_head_sign_offset, common_head_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_ecc_sign))
    else:
        #SHA256
        (common_key_offset, common_key_size) = make_part_offset_size(temp_offset, sizeof(upg_sha256_key))
        (common_head_sign_offset, common_head_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_sha256_sign))

    print('[common_key_offset=%d][common_key_size=%d]'%(common_key_offset, common_key_size))
    print('[common_head_sign_offset=%d][common_head_sign_size=%d]'%(common_head_sign_offset, common_head_sign_size))

    #section固定头大小偏移
    (section_head_offset, section_head_size) = make_part_offset_size(temp_offset, sizeof(hi_upg_section_head))
    print('[section_head_offset=%d][section_head_size=%d]'%(section_head_offset, section_head_size))
    #section签名大小偏移、秘钥信息。签名算法不同,填充大小不同
    if sign_alg < 0x10:
        (upg_file_sign_offset, upg_file_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_rsa_sign))
    elif sign_alg == 0x10:
        (upg_file_sign_offset, upg_file_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_ecc_sign))
    else:
        (upg_file_sign_offset, upg_file_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_sha256_sign))
    print('[upg_file_sign_offset=%d][upg_file_sign_size=%d]'%(upg_file_sign_offset, upg_file_sign_size))

    #section各个镜像大小和偏移
    i = 0
    while i < section_count:
        (offset, size) = make_part_offset_size(temp_offset, len(section_bin_list[i]))
        section_offset_list.append(offset)
        section_size_list.append(size)
        i = i + 1

    #section填充域大小和偏移:AES加密要求16字节对齐
    temp_size_1 = temp_offset[0]
    temp_size_2 = temp_size_1//16
    temp_size_2 = temp_size_2*16
    padding_size = temp_size_1 - temp_size_2
    if temp_size_1 == temp_size_2:
        padding_size = 0
    else:
        padding_size = temp_size_2 + 16 - temp_size_1

    (padding_offset, padding_size) = make_part_offset_size(temp_offset, padding_size)#hupg+nv部分大小
    print('[padding_offset=%d][padding_size=%d]'%(padding_offset, padding_size))

    #初始化upg_bin
    upg_bin = bytearray(temp_offset[0])

    #升级文件大小上限从分区获取
    if len(upg_bin) >  max_size:
        sys.exit("\033[91m[ERR]upg size>%dKB FROM:%s\033[0m"%(max_size/1024, os.path.realpath(__file__)))

    #填充common段固定头
    common_head_bin = upg_bin[common_head_offset:common_head_offset + common_head_size]
    common_head = hi_upg_common_head.from_buffer(common_head_bin)
    common_head.image_id = image_id
    common_head.struct_version = 0
    common_head.section_offset = section_head_offset
    common_head.section_len = len(upg_bin) - section_head_offset
    common_head.file_type = file_type
    common_head.file_version = file_ver
    common_head.encrypt_flag = encrypt_flag
    common_head.file_attr = file_attr
    common_head.file_len = len(upg_bin)
    common_head.key_len = common_key_size
    common_head.param.hash_alg = 0
    common_head.param.sign_alg = sign_alg
    common_head.param.sign_param = 0
    #image_id struct_version section_offset section_offset
    user_info_offset = sizeof(c_int) + sizeof(c_int) + sizeof(c_int) + sizeof(c_int)
    common_head_bin[user_info_offset : (user_info_offset + sizeof(hi_upg_user_info))] = USER_INFO.fill_user_info(chip_name)
    if encrypt_flag != 0x42:
        common_head_bin[(common_head_size - 32) : (common_head_size - 16)] = make_upg_get_aes_key(alg_dir_path)
        common_head_bin[(common_head_size - 16) : common_head_size] = make_upg_get_aes_iv(alg_dir_path)
    upg_bin[common_head_offset:common_head_offset + common_head_size] = common_head_bin

    #填充section段固定头
    section_head_bin = upg_bin[section_head_offset:section_head_offset+section_head_size]
    section_head = hi_upg_section_head.from_buffer(section_head_bin)
    section_head.image_id = image_id
    section_head.struct_version = 0
    section_head.param.hash_alg = 0
    section_head.param.sign_alg = sign_alg
    section_head.param.sign_param = 0
    section_head.section_count = section_count
    if section_count > 2:
        sys.exit("[ERR]upg section count more than 2 FROM:%s"%os.path.realpath(__file__))
    elif section_count == 2:
        section_head.section0_compress = section_compress_list[0]
        section_head.section0_offset = section_offset_list[0]
        section_head.section0_len = section_size_list[0]
        section_head.section1_compress = section_compress_list[1]
        section_head.section1_offset = section_offset_list[1]
        section_head.section1_len = section_size_list[1]
    elif section_count == 1:
        section_head.section0_compress = section_compress_list[0]
        section_head.section0_offset = section_offset_list[0]
        section_head.section0_len = section_size_list[0]
        section_head.section1_offset = 0
        section_head.section1_len = 0
    else:
        section_head.section0_offset = 0
        section_head.section0_len = 0
        section_head.section1_offset = 0
        section_head.section1_len = 0
    upg_bin[section_head_offset:section_head_offset + section_head_size] = section_head_bin

    #填充section段内容
    i = 0
    while i < section_count:
        upg_bin[section_offset_list[i]:section_offset_list[i] + section_size_list[i]] = section_bin_list[i]
        i = i + 1

    #填充common段key
    key_2_n = make_secure_key(alg_dir_path, common_head.param.sign_alg)
    upg_bin[common_key_offset:common_key_offset + common_key_size] = key_2_n

    #填充common段签名及section段签名(不同签名算法统一按最大值256Byte处理,填实际长度字节,多余的部分填0)
    if sign_alg == 0x0:
        (signature_1, signature_2) = make_rsa_pkcs_signature(alg_dir_path, upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])
    elif sign_alg == 0x1:
        (signature_1, signature_2) = make_rsa_pss_signature(alg_dir_path, upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])
    elif sign_alg == 0x10:
        (signature_1, signature_2) = make_ecc_secure_signature(alg_dir_path, upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])
    else:
        (signature_1, signature_2) = make_sha256_unsecure_signature(upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])

    upg_bin[common_head_sign_offset:common_head_sign_offset+common_head_sign_size] = signature_1
    upg_bin[upg_file_sign_offset:upg_file_sign_offset+upg_file_sign_size] = signature_2

    return upg_bin

def make_hupg(image_id, file_ver, encrypt_flag, kernel_file, normal_nv_file, image_file, alg_dir_path, max_size, sign_alg, chip_name, file_attr):
    print('upg kernel file    in:', kernel_file)
    print('upg normal nv file in:', normal_nv_file)
    print('upg file          out:', image_file)

    with open(kernel_file, 'rb') as fp:
        kernel_bin = fp.read()
    with open(normal_nv_file, 'rb') as fp:
        nv_bin = fp.read()

    section_bin_list = []
    section_bin_list.append(kernel_bin)
    section_bin_list.append(nv_bin)

    section_compress_list = []
    section_compress_list.append(0)
    section_compress_list.append(0)
    hupg_bin = make_upg_only(image_id, file_ver, encrypt_flag, 0xF0, section_bin_list, section_compress_list, alg_dir_path, max_size, sign_alg, chip_name, file_attr)

    print_upg_info(image_file, hupg_bin)
    #如果标记加密
    unencrypted = 0x42
    if encrypt_flag != unencrypted:
        (filepath, tempfilename) = os.path.split(kernel_file)
        (filename, extension) = os.path.splitext(tempfilename)
        upg_unenrypt_file = os.path.join(filepath, '%s_unencrypt.bin'%filename)
        with open(upg_unenrypt_file, 'wb+') as fp:
            fp.write(hupg_bin)

        aes_key_file = os.path.join(alg_dir_path, r'upg_aes_key.txt')
        aes_encrypt_tool = os.path.join(alg_dir_path, r'sign_tool')
        #双分区升级文件需要加密
        src_file_len = len(hupg_bin)
        if src_file_len < 0x1000:
            sys.exit("\033[91m[ERR]upg size %d< 0x1000 FROM:%s\033[0m"%(src_file_len, os.path.realpath(__file__)))
        aes_encrypt_bin(upg_unenrypt_file, image_file, 0x3C0, 0x1000, aes_key_file, aes_encrypt_tool)
    else:
        with open(image_file, 'wb+') as fp:
            fp.write(hupg_bin)
    return

def make_compress_hupg(image_id, file_ver, encrypt_flag, upg_file, image_file, alg_dir_path, kernel_upg_max_size, sign_alg, lzma_tool, build_tmp, chip_name, file_attr):
    print('compress upg file in: ', upg_file)
    print('compress upg file out:', image_file)

    (filepath, tempfilename) = os.path.split(upg_file)
    (filename, extension) = os.path.splitext(tempfilename)
    upg_lzma_file = os.path.join(build_tmp, '%s.lzma'%filename)
    lzma_compress_bin(upg_file, upg_lzma_file, lzma_tool)

    with open(upg_lzma_file, 'rb') as fp:
        upg_lzma_file_bin = fp.read()

    with open(upg_file, 'rb') as fp:
        upg_bin = fp.read()

    section_bin_list = []
    if encrypt_flag != 0x42:
        upg_lzma_encrypt_file = os.path.join(build_tmp, '%s_encrypt.bin'%filename)
        aes_key_file = os.path.join(alg_dir_path, r'upg_aes_key.txt')
        aes_encrypt_tool = os.path.join(alg_dir_path, r'sign_tool')
        #压缩文件文件需要加密
        src_file_len = len(upg_lzma_file_bin)
        if src_file_len < 0x13CD:
            sys.exit("\033[91m[ERR]upg size %d< 0x13C0 FROM:%s\033[0m"%(src_file_len, os.path.realpath(__file__)))
        aes_encrypt_bin(upg_lzma_file, upg_lzma_encrypt_file, 0xd, 0x13C0, aes_key_file, aes_encrypt_tool)
        with open(upg_lzma_encrypt_file, 'rb') as fp:
            upg_lzma_encrypt_file_bin = fp.read()
        section_bin_list.append(upg_lzma_encrypt_file_bin)
    else:
        section_bin_list.append(upg_lzma_file_bin)

    section_compress_list = []
    section_compress_list.append(1)
    #计算压缩文件大小上限
    upg_bin_len = len(upg_bin)
    upg_align_len = (upg_bin_len//4096) * 4096
    upg_len = upg_align_len
    if upg_bin_len != upg_align_len:
        upg_len = upg_align_len + 4096
    max_compress_size = kernel_upg_max_size - upg_len
    print("[upgbin-compressbin]0x%x-0x%x"%(upg_bin_len, max_compress_size))
    hupg_bin = make_upg_only(image_id, file_ver, encrypt_flag, 0xF0, section_bin_list, section_compress_list, alg_dir_path, max_compress_size, sign_alg, chip_name, file_attr)
    print_upg_info(image_file, hupg_bin)
    with open(image_file, 'wb+') as fp:
        fp.write(hupg_bin)
    return

def make_hbin(flash_boot_file, factory_nv_file, normal_nv_file, upg_file, image_file):
    print('hbin flash boot file in :', flash_boot_file)
    print('hbin factory nv file in :', factory_nv_file)
    print('hbin normal nv file  in :', upg_file)
    print('hbin upg file        in :', factory_nv_file)
    print('hbin file           out :', image_file)

    with open(flash_boot_file, 'rb') as fp:
        flash_boot_bin = fp.read()

    with open(factory_nv_file, 'rb') as fp:
        factory_nv_bin = fp.read()

    with open(normal_nv_file, 'rb') as fp:
        normal_nv_bin = fp.read()

    with open(upg_file, 'rb') as fp:
        upg_file_bin = fp.read()

    #Todo:从分表获取信息
    boot_st_addr = 0 #BOOT 32KB
    boot_size = 0x8000
    ftm1_st_addr = 0x8000 #工厂区NV 4KB+4KB
    ftm1_size = 0x1000
    ftm2_st_addr = 0x9000
    ftm2_size = 0x1000
    nv_file_st_addr = 0xa000 #NV工作区 4KB+4KB
    nv_file_size = 0x1000
    nv_file_origin_st_addr = 0xc000 #NV工作区的原始备份
    kernel_st_addr = 0xd000 #KernelA 912KB

    bin_total_size = boot_size + ftm1_size + ftm2_size + nv_file_size + nv_file_size + nv_file_size + len(upg_file_bin)

    boot_nv_kernel_bin = bytearray(bin_total_size)
    boot_nv_kernel_bin[boot_st_addr:boot_st_addr + boot_size] = flash_boot_bin
    boot_nv_kernel_bin[ftm1_st_addr:ftm1_st_addr + ftm1_size] = factory_nv_bin
    #boot_nv_kernel_bin[ftm2_st_addr:ftm2_st_addr + ftm2_size] = factory_nv_bin 当前只放1份工厂区NV
    boot_nv_kernel_bin[nv_file_st_addr:nv_file_st_addr + nv_file_size] = normal_nv_bin
    boot_nv_kernel_bin[nv_file_origin_st_addr:nv_file_origin_st_addr + nv_file_size] = normal_nv_bin #NV区原始备份
    boot_nv_kernel_bin[kernel_st_addr:kernel_st_addr + len(upg_file_bin)] = upg_file_bin
    print_hbin_info(image_file, boot_nv_kernel_bin[kernel_st_addr:kernel_st_addr + len(upg_file_bin)], bin_total_size)
    with open(image_file, "wb+") as fp:
        fp.write(boot_nv_kernel_bin)
    return

def make_bootupg(image_id, file_ver, encrypt_flag, flash_boot_file, image_file, alg_dir_path, max_size, sign_alg, chip_name, file_attr):
    print('boot upg file  in:', flash_boot_file)
    print('boot upg file out:', image_file)
    with open(flash_boot_file, 'rb') as fp:
        boot_bin = fp.read()

    hupg_bin = make_upg_boot_only(image_id, file_ver, encrypt_flag, 0xE1, boot_bin, alg_dir_path, max_size, sign_alg, chip_name, file_attr)
    print_upg_info(image_file, hupg_bin)
    with open(image_file, 'wb+') as fp:
        fp.write(hupg_bin)
    return

#配置romboot下用法boot升级文件的填充字段放到section前面
def make_upg_boot_only(image_id, file_ver, encrypt_flag, file_type, section_bin, alg_dir_path, max_size, sign_alg, chip_name, file_attr):
    temp_offset = [0]

    #common固定头大小偏移
    (common_head_offset, common_head_size) = make_part_offset_size(temp_offset, sizeof(hi_upg_common_head))
    print('[common_head_offset=%d][common_head_size=%d]'%(common_head_offset, common_head_size))

    #common密钥区大小偏移、固定头签名大小偏移
    if sign_alg < 0x10:
        #RSA2048
        (common_key_offset, common_key_size) = make_part_offset_size(temp_offset, sizeof(upg_rsa_key))
        (common_head_sign_offset, common_head_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_rsa_sign))
    elif sign_alg == 0x10:
        #ECDSA256
        (common_key_offset, common_key_size) = make_part_offset_size(temp_offset, sizeof(upg_ecc_key))
        (common_head_sign_offset, common_head_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_ecc_sign))
    else:
        #SHA256
        (common_key_offset, common_key_size) = make_part_offset_size(temp_offset, sizeof(upg_sha256_key))
        (common_head_sign_offset, common_head_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_sha256_sign))
    print('[common_key_offset=%d][common_key_size=%d]'%(common_key_offset, common_key_size))
    print('[common_head_sign_offset=%d][common_head_sign_size=%d]'%(common_head_sign_offset, common_head_sign_size))
    #section固定头大小偏移
    (section_head_offset, section_head_size) = make_part_offset_size(temp_offset, sizeof(hi_upg_section_head))
    print('[section_head_offset=%d][section_head_size=%d]'%(section_head_offset, section_head_size))
    #section签名大小偏移、秘钥信息。签名算法不同,填充大小不同
    if sign_alg < 0x10:
        (upg_file_sign_offset, upg_file_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_rsa_sign))
    elif sign_alg == 0x10:
        (upg_file_sign_offset, upg_file_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_ecc_sign))
    else:
        (upg_file_sign_offset, upg_file_sign_size) = make_part_offset_size(temp_offset, sizeof(upg_sha256_sign))
    print('[upg_file_sign_offset=%d][upg_file_sign_size=%d]'%(upg_file_sign_offset, upg_file_sign_size))
    #填充大小和偏移
    temp_size_1 = temp_offset[0] + len(section_bin)
    temp_size_2 = temp_size_1//16
    temp_size_2 = temp_size_2*16
    padding_size = temp_size_1 - temp_size_2
    if temp_size_1 == temp_size_2:
        padding_size = 0
    else:
        padding_size = temp_size_2 + 16 - temp_size_1

    (padding_offset, padding_size) = make_part_offset_size(temp_offset, padding_size)
    print('[padding_offset=%d][padding_size=%d]'%(padding_offset, padding_size))

    #镜像大小和偏移
    (section_offset, section_size) = make_part_offset_size(temp_offset, len(section_bin))#BOOT部分大小

    #初始化upg_bin
    upg_bin = bytearray(temp_offset[0])

    #升级文件大小上限从分区获取
    if len(upg_bin) >  max_size:
        sys.exit("\033[91m[ERR]upg boot size>%dKB FROM:%s\033[0m"%(max_size/1024, os.path.realpath(__file__)))

    #填充common段固定头
    common_head_bin = upg_bin[common_head_offset:common_head_offset + common_head_size]
    common_head = hi_upg_common_head.from_buffer(common_head_bin)
    common_head.image_id = image_id
    common_head.struct_version = 0
    common_head.section_offset = section_head_offset
    common_head.section_len = len(upg_bin) - section_head_offset
    common_head.file_type = file_type
    common_head.file_version = file_ver
    common_head.encrypt_flag = encrypt_flag
    common_head.file_attr = file_attr
    common_head.file_len = len(upg_bin)
    common_head.key_len = common_key_size
    common_head.param.hash_alg = 0
    common_head.param.sign_alg = sign_alg
    common_head.param.sign_param = 0
    #common_head.aes_key[16] =
    #common_head.aes_iv[16] =
    #image_id struct_version section_offset section_offset
    user_info_offset = sizeof(c_int) + sizeof(c_int) + sizeof(c_int) + sizeof(c_int)
    common_head_bin[user_info_offset : (user_info_offset + sizeof(hi_upg_user_info))] = USER_INFO.fill_user_info(chip_name)
    upg_bin[common_head_offset:common_head_offset+common_head_size] = common_head_bin

    #填充section段固定头
    section_head_bin = upg_bin[section_head_offset:section_head_offset+section_head_size]
    section_head = hi_upg_section_head.from_buffer(section_head_bin)
    section_head.image_id = image_id
    section_head.struct_version = 0
    section_head.param.hash_alg = 0
    section_head.param.sign_alg = sign_alg
    section_head.param.sign_param = 0
    section_head.section_count = 1
    section_head.section0_compress = 0
    section_head.section0_offset = section_offset
    section_head.section0_len = section_size
    section_head.section1_compress = 0
    section_head.section1_offset = 0
    section_head.section1_len = 0
    upg_bin[section_head_offset:section_head_offset + section_head_size] = section_head_bin

    #填充section段内容
    upg_bin[section_offset:section_offset + section_size] = section_bin

    #填充common段key
    key_2_n = make_secure_key(alg_dir_path, common_head.param.sign_alg)
    upg_bin[common_key_offset:common_key_offset + common_key_size] = key_2_n

    #填充common段签名及section段签名
    if sign_alg == 0x0:
        (signature_1, signature_2) = make_rsa_pkcs_signature(alg_dir_path, upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])
    elif sign_alg == 0x1:
        (signature_1, signature_2) = make_rsa_pss_signature(alg_dir_path, upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])
    elif sign_alg == 0x10:
        (signature_1, signature_2) = make_ecc_secure_signature(alg_dir_path, upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])
    else:
        (signature_1, signature_2) = make_sha256_unsecure_signature(upg_bin[common_head_offset:common_head_sign_offset], upg_bin[section_head_offset:section_head_offset+sizeof(hi_upg_section_head)]+upg_bin[upg_file_sign_offset+upg_file_sign_size:common_head.file_len])

    upg_bin[common_head_sign_offset:common_head_sign_offset+common_head_sign_size] = signature_1
    upg_bin[upg_file_sign_offset:upg_file_sign_offset+upg_file_sign_size] = signature_2

    return upg_bin