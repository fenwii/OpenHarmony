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
* Description: efuse too scripts.
'''

import csv
import struct
import hashlib
import os
from sys import version_info

def str_to_hex(s):
    return ' '.join([hex(ord(c)).replace('0x', '') for c in s])

def print_bytes(bytes):
    if version_info.major == 3:
        c = bytes.hex()
        print(c)
    else:
        c = bytes.encode('hex')
        print(c)

number = 0
value_len = 0
buf = b''
csv_dir = os.path.split(os.path.realpath(__file__))[0]
csv_path = os.path.join(csv_dir, 'efuse.csv')
#print('csv_path:', csv_path)
bin_path = os.path.join(csv_dir, 'efuse_cfg.bin')
#print('bin_path:', bin_path)

# 用reader读取csv文件
with open(csv_path, 'r') as csvFile:
    reader = csv.reader(csvFile)
    for line in reader:
        if(line[0] == "1"):
            size = int(line[3])
            if (size <= 32):
                value_len = 4
            elif (size <= 64):
                value_len = 8
            else:
                value_len = size // 8
            result = struct.pack('BBHHH', 0, 8, int(line[2]), size, value_len)
            value_str = line[4]
            value_list = value_str.split(" ")
            value_struct = b''
            for i in range(value_len // 4):
                value = int(value_list[i], 16)
                value_struct = value_struct + struct.pack('I', value)
            print_bytes(value_struct)
            buf = buf + result + value_struct
            number = number + 1
header = struct.pack('BBHIII', 0, 48, number, len(buf) + 48, 0, 0)
data = header + buf
hash = hashlib.sha256(data).digest()
bin_data = hash + data
#print(bin_data)

with open(bin_path, 'wb') as f:
    f.write(bin_data)
