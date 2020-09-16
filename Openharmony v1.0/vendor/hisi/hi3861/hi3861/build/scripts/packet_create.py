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
* Description: packet allinone bin file
'''
import struct
import sys
import os

class crc16:
    POLYNOMIAL = 0x1021
    PRESET = 0x0000
    _tab = []
    def __init__(self):
        self._tab = [self._initial(i) for i in range(256)]

    def _initial(self, c):
        crc = 0
        c = c << 8
        for j in range(8):
            if (crc ^ c) & 0x8000:
                crc = (crc << 1) ^ self.POLYNOMIAL
            else:
                crc = crc << 1
            c = c << 1
        return crc

    def _update_crc(self, crc, c):
        cc = 0xff & int(c)

        tmp = (crc >> 8) ^ cc
        crc = (crc << 8) ^ self._tab[tmp & 0xff]
        crc = crc & 0xffff

        return crc

    def crc(self, str):
        crc = self.PRESET
        for c in str:
            crc = self._update_crc(crc, ord(c))
        return crc

    def crcb(self, i):
        crc = self.PRESET
        for c in i:
            crc = self._update_crc(crc, c)
        return crc

t = crc16()
def packet_bin(outputPath, inputList):
    pathList = []
    burnAddrList = []
    burnSizeList = []
    imageSizeList = []
    typeList = []
    for item in inputList:
        path, burnAddr, burnSize, type = item.split("|")
        imageSize = os.path.getsize(path)
        pathList.append(path)
        burnAddrList.append(int(burnAddr))
        burnSizeList.append(int(burnSize))
        imageSizeList.append(imageSize)
        typeList.append(int(type))

    print(pathList)
    print(burnAddrList)
    print(burnSizeList)
    print(imageSizeList)
    print(typeList)

    flag = 0xefbeaddf
    print(flag)
    crc = 0
    imageNum = len(pathList)
    headLen = imageNum*52 + 12
    totalFileSize = sum(imageSizeList) + headLen

    with open(outputPath, 'wb+') as file:
        file.write(struct.pack('IHHI', flag, crc, imageNum, totalFileSize))
        startIndex = headLen
        times = 0
        for path in pathList:
            pathName = os.path.basename(path)
            file.write(
                struct.pack('32sIIIII', bytes(pathName, 'ascii'), startIndex, imageSizeList[times], burnAddrList[times],
                            burnSizeList[times], typeList[times]))
            startIndex = startIndex + imageSizeList[times] + 16
            times += 1

        for path in pathList:
            with  open(path, 'rb+') as subfile:
                data = subfile.read()
                file.write(data)
                file.write(struct.pack('IIII', 0, 0, 0, 0))

        file.flush()
        file.seek(6)
        newdata = file.read(headLen - 6)
        crc16 = t.crcb(newdata)
        file.seek(4)
        file.write(struct.pack('H', crc16))

if __name__=="__main__":
    print("main")
    args = len(sys.argv)
    argv = sys.argv
    print(args)
    print(argv)
    if(args <= 2):
        print("param should be : python main.py \"outputPath\" \"name|burnAddr|burnSize|type\"...")
        '''
        enum IMAGE_TYPE {
        IMAGE_TYPE_LOADER,
        IMAGE_TYPE_NORMAL,
        IMAGE_TYPE_PARAM,
        IMAGE_TYPE_EFUSE,
        IMAGE_TYPE_OTP,
        IMAGE_TYPE_FORMALBIN,
        };
        '''
        sys.exit()

    outputPath = argv[1]
    print(outputPath)
    del argv[1]
    del argv[0]
    packet_bin(outputPath, argv)

''''
pathList = []
burnAddrList = []
burnSizeList = []
imageSizeList = []
typeList = []

for arg in argv:
    path, burnAddr, burnSize, type = arg.split("|")
    imageSize = os.path.getsize(path)
    pathList.append(path)
    burnAddrList.append(int(burnAddr))
    burnSizeList.append(int(burnSize))
    imageSizeList.append(imageSize)
    typeList.append(int(type))

print(pathList)
print(burnAddrList)
print(burnSizeList)
print(imageSizeList)
print(typeList)

flag = 0xefbeaddf
print(flag)
crc = 0
imageNum = len(pathList)
headLen = imageNum*52 + 12
totalFileSize = sum(imageSizeList) + headLen

file = open(outputPath, 'wb+')

file.write(struct.pack('IHHI', flag, crc, imageNum, totalFileSize))
startIndex = headLen
times = 0
for path in pathList:
    pathName = path.split("\\")[-1]
    file.write(struct.pack('32sIIIII', bytes(pathName, 'ascii'), startIndex, imageSizeList[times], burnAddrList[times],
                           burnSizeList[times], typeList[times]))
    startIndex = startIndex + imageSizeList[times] + 16
    times += 1

for path in pathList:
    subfile = open(path, 'rb+')
    data = subfile.read()
    file.write(data)
    file.write(struct.pack('IIII', 0, 0, 0, 0))

file.flush()
file.seek(6)
newdata = file.read(headLen - 6)
t = crc16()
crc16 = t.crcb(newdata)
file.seek(4)
file.write(struct.pack('H', crc16))
file.close()
'''''

