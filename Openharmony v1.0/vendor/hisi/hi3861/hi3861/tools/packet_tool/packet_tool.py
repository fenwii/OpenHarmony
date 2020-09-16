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
* Description: allinone.bin packet too scripts.
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
    #sizeof(IMAGE_INFO) is 52, sizeof(FWPKG_HEAD) is 12
    headLen = imageNum * 52 + 12
    #each image has 16byte 0 in the end
    padLen = 16 * imageNum 
    totalFileSize = sum(imageSizeList) + headLen + padLen
    with open(outputPath, 'wb+') as file:
        file.write(struct.pack('IHHI', flag, crc, imageNum, totalFileSize))
        startIndex = headLen
        times = 0
        for path in pathList:
            pathName = os.path.basename(path)
            file.write(
                struct.pack('32sIIIII', bytes(pathName, 'ascii'), startIndex, imageSizeList[times], burnAddrList[times],
                            burnSizeList[times], typeList[times]))
            #separate each image with 16 bytes 0
            startIndex = startIndex + imageSizeList[times] + 16
            times += 1

        for path in pathList:
            subfile = open(path, 'rb+')
            data = subfile.read()
            file.write(data)
            file.write(struct.pack('IIII', 0, 0, 0, 0))

        file.flush()
        #crc range is FWPKG_HEAD.imageNum to end, begin index is 6bytes
        file.seek(6)
        newdata = file.read(headLen - 6)
        crc16 = t.crcb(newdata)
        file.seek(4)
        file.write(struct.pack('H', crc16))
        file.close()
def update_bin(packet_path, inputList):
    pathNameList = []
    burnAddrList = []
    burnSizeList = []
    imageSizeList = []
    typeList = []
    startIndexList = []
    fileInfoList = []

    pathNameListNew = []
    burnAddrListNew = []
    burnSizeListNew = []
    imageSizeListNew = []
    typeListNew = []
    for item in inputList:
        path, burnAddr, burnSize, type = item.split("|")
        imageSize = os.path.getsize(path)
        pathNameListNew.append(path)
        burnAddrListNew.append(int(burnAddr))
        burnSizeListNew.append(int(burnSize))
        imageSizeListNew.append(imageSize)
        typeListNew.append(int(type))

    with open(packet_path, 'rb+') as file:
        info = file.read(struct.calcsize('IHHI'))
        flag, crc, imageNum, totalFileSize = struct.unpack('IHHI', info)
        times = 0
        for index in range(0, imageNum):
            info = file.read(struct.calcsize('32sIIIII'))
            pathName, startIndex, imageSize, burnAddr, burnSize, type2 = struct.unpack('32sIIIII', info)
            #separate each image with 16 bytes 0
            pathName = str(pathName, encoding="utf-8")
            pathNameNew = ''
            for char in pathName:
                if char != '\x00':
                    pathNameNew += char
            print(pathNameNew)
            pathNameList.append(pathNameNew)
            startIndexList.append(startIndex)
            burnAddrList.append(burnAddr)
            burnSizeList.append(burnSize)
            imageSizeList.append(imageSize)
            typeList.append(type2)

        for index in range(0, imageNum):
            file.seek(startIndexList[index])
            fileInfoList.append(file.read(imageSizeList[index]))

        for index in range(0, len(pathNameListNew)):
            pathNew = pathNameListNew[index]
            print(os.path.basename(pathNew))
            pathIn32Byte = os.path.basename(pathNew)
            if len(pathIn32Byte) > 32:
                pathIn32Byte = pathIn32Byte[0:32]
            if pathIn32Byte in pathNameList:
                for index2 in range(0, imageNum):
                    path = pathNameList[index2]
                    if path == pathIn32Byte:
                        subfile = open(pathNew, 'rb+')
                        fileInfoList[index2] = subfile.read()
                        subfile.close()
                        pathNameList[index2] = os.path.basename(pathNew)
                        burnAddrList[index2] = burnAddrListNew[index]
                        burnSizeList[index2] = burnSizeListNew[index]
                        imageSizeList[index2] = imageSizeListNew[index]
                        typeList[index2] = typeListNew[index]
                        break
            else:
                pathNameList.append(pathNameListNew[index])
                burnAddrList.append(burnAddrListNew[index])
                burnSizeList.append(burnSizeListNew[index])
                imageSizeList.append(imageSizeListNew[index])
                typeList.append(typeListNew[index])
                subfile = open(pathNew, 'rb+')
                fileInfoList.append(subfile.read())
                subfile.close()
        file.close()
    print(pathNameList)
    print(burnAddrList)
    print(burnSizeList)
    print(imageSizeList)
    print(typeList)

    flag = 0xefbeaddf
    print(flag)
    crc = 0
    imageNum = len(pathNameList)
    #sizeof(IMAGE_INFO) is 52, sizeof(FWPKG_HEAD) is 12
    headLen = imageNum * 52 + 12
    #each image has 16byte 0 in the end
    padLen = 16 * imageNum
    totalFileSize = sum(imageSizeList) + headLen + padLen
    with open(outputPath, 'wb+') as file:
        file.write(struct.pack('IHHI', flag, crc, imageNum, totalFileSize))
        startIndex = headLen
        times = 0
        for path in pathNameList:
            pathName = os.path.basename(path)
            file.write(
                struct.pack('32sIIIII', bytes(pathName, 'ascii'), startIndex, imageSizeList[times], burnAddrList[times],
                            burnSizeList[times], typeList[times]))
            #separate each image with 16 bytes 0
            startIndex = startIndex + imageSizeList[times] + 16
            times += 1

        for info in fileInfoList:
            file.write(info)
            file.write(struct.pack('IIII', 0, 0, 0, 0))

        file.flush()
        #crc range is FWPKG_HEAD.imageNum to end, begin index is 6bytes
        file.seek(6)
        newdata = file.read(headLen - 6)
        crc16 = t.crcb(newdata)
        file.seek(4)
        file.write(struct.pack('H', crc16))
        file.close()
def delete_bin(packet_path, name_list):
    pathNameList = []
    burnAddrList = []
    burnSizeList = []
    imageSizeList = []
    typeList = []
    startIndexList = []
    fileInfoList = []

    pathNameListNew = name_list

    with open(packet_path, 'rb+') as file:
        info = file.read(struct.calcsize('IHHI'))
        flag, crc, imageNum, totalFileSize = struct.unpack('IHHI', info)
        times = 0
        for index in range(0, imageNum):
            info = file.read(struct.calcsize('32sIIIII'))
            pathName, startIndex, imageSize, burnAddr, burnSize, type2 = struct.unpack('32sIIIII', info)
            #separate each image with 16 bytes 0
            pathName = str(pathName, encoding="utf-8")
            pathNameNew = ''
            for char in pathName:
                if char != '\x00':
                    pathNameNew += char
            print(pathNameNew)
            pathNameList.append(pathNameNew)
            startIndexList.append(startIndex)
            burnAddrList.append(burnAddr)
            burnSizeList.append(burnSize)
            imageSizeList.append(imageSize)
            typeList.append(type2)

        for index in range(0, imageNum):
            file.seek(startIndexList[index])
            fileInfoList.append(file.read(imageSizeList[index]))

        for pathNew in pathNameListNew:
            print(os.path.basename(pathNew))
            pathIn32Byte = os.path.basename(pathNew)
            if len(pathIn32Byte) > 32:
                pathIn32Byte = pathIn32Byte[0:32]
            if pathIn32Byte in pathNameList:
                for index2 in range(0, imageNum):
                    path = pathNameList[index2]
                    if path == pathIn32Byte:
                        del fileInfoList[index2]
                        del pathNameList[index2]
                        del burnAddrList[index2]
                        del burnSizeList[index2]
                        del imageSizeList[index2]
                        del typeList[index2]
                        break
        file.close()
    print(pathNameList)
    print(burnAddrList)
    print(burnSizeList)
    print(imageSizeList)
    print(typeList)

    flag = 0xefbeaddf
    print(flag)
    crc = 0
    imageNum = len(pathNameList)
    #sizeof(IMAGE_INFO) is 52, sizeof(FWPKG_HEAD) is 12
    headLen = imageNum * 52 + 12
    #each image has 16byte 0 in the end
    padLen = 16 * imageNum
    totalFileSize = sum(imageSizeList) + headLen + padLen
    with open(outputPath, 'wb+') as file:
        file.write(struct.pack('IHHI', flag, crc, imageNum, totalFileSize))
        startIndex = headLen
        times = 0
        for path in pathNameList:
            pathName = os.path.basename(path)
            file.write(
                struct.pack('32sIIIII', bytes(pathName, 'ascii'), startIndex, imageSizeList[times], burnAddrList[times],
                            burnSizeList[times], typeList[times]))
            #separate each image with 16 bytes 0
            startIndex = startIndex + imageSizeList[times] + 16
            times += 1

        for info in fileInfoList:
            file.write(info)
            file.write(struct.pack('IIII', 0, 0, 0, 0))

        file.flush()
        #crc range is FWPKG_HEAD.imageNum to end, begin index is 6bytes
        file.seek(6)
        newdata = file.read(headLen - 6)
        crc16 = t.crcb(newdata)
        file.seek(4)
        file.write(struct.pack('H', crc16))
        file.close()
def split_bin(packet_path, output_path):
    pathNameList = []
    burnAddrList = []
    burnSizeList = []
    imageSizeList = []
    typeList = []
    startIndexList = []
    fileInfoList = []

    pathNameListNew = []
    burnAddrListNew = []
    burnSizeListNew = []
    imageSizeListNew = []
    typeListNew = []
    with open(packet_path, 'rb+') as file:
        info = file.read(struct.calcsize('IHHI'))
        flag, crc, imageNum, totalFileSize = struct.unpack('IHHI', info)
        times = 0
        for index in range(0, imageNum):
            info = file.read(struct.calcsize('32sIIIII'))
            pathName, startIndex, imageSize, burnAddr, burnSize, type2 = struct.unpack('32sIIIII', info)
            #separate each image with 16 bytes 0
            pathName = str(pathName, encoding="utf-8")
            pathNameNew = ''
            for char in pathName:
                if char != '\x00':
                    pathNameNew += char
            print(pathNameNew)
            pathNameList.append(pathNameNew)
            startIndexList.append(startIndex)
            burnAddrList.append(burnAddr)
            burnSizeList.append(burnSize)
            imageSizeList.append(imageSize)
            typeList.append(type2)

        for index in range(0, imageNum):
            file.seek(startIndexList[index])
            fileInfoList.append(file.read(imageSizeList[index]))

        file.close()
    print(pathNameList)
    print(burnAddrList)
    print(burnSizeList)
    print(imageSizeList)
    print(typeList)

    imageNum = len(pathNameList)
    for index in range(0, imageNum):
        pathName = os.path.join(output_path, pathNameList[index])
        print(pathName)
        with open(pathName, 'wb+') as file:
            file.write(fileInfoList[index])
            file.close()
def show_bin(packet_path):
    pathNameList = []
    burnAddrList = []
    burnSizeList = []
    imageSizeList = []
    typeList = []
    startIndexList = []
    fileInfoList = []

    with open(packet_path, 'rb+') as file:
        info = file.read(struct.calcsize('IHHI'))
        flag, crc, imageNum, totalFileSize = struct.unpack('IHHI', info)
        times = 0
        for index in range(0, imageNum):
            info = file.read(struct.calcsize('32sIIIII'))
            pathName, startIndex, imageSize, burnAddr, burnSize, type2 = struct.unpack('32sIIIII', info)
            #separate each image with 16 bytes 0
            pathName = str(pathName, encoding="utf-8")
            pathNameNew = ''
            for char in pathName:
                if char != '\x00':
                    pathNameNew += char
            print(pathNameNew)
            pathNameList.append(pathNameNew)
            startIndexList.append(startIndex)
            burnAddrList.append(burnAddr)
            burnSizeList.append(burnSize)
            imageSizeList.append(imageSize)
            typeList.append(type2)

        for index in range(0, imageNum):
            file.seek(startIndexList[index])
            fileInfoList.append(file.read(imageSizeList[index]))

        file.close()
    print(pathNameList)
    print(burnAddrList)
    print(burnSizeList)
    print(imageSizeList)
    print(typeList)

if __name__=="__main__":
    args = len(sys.argv)
    argv = sys.argv
    if(args <= 1):
        print("parma error, please use -help for usage")
        sys.exit()
    if (argv[1] == '-packet'):
        outputPath = argv[2]
        print(outputPath)
        del argv[2]
        del argv[1]
        del argv[0]
        packet_bin(outputPath, argv)
    elif (argv[1] == '-update'):
        outputPath = argv[2]
        print(outputPath)
        del argv[2]
        del argv[1]
        del argv[0]
        update_bin(outputPath, argv)
    elif (argv[1] == '-split'):
        input_file = argv[2]
        outputPath = argv[3]
        split_bin(input_file, outputPath)
    elif (argv[1] == '-show'):
        input_file = argv[2]
        show_bin(input_file)
    elif (argv[1] == '-delete'):
        outputPath = argv[2]
        print(outputPath)
        del argv[2]
        del argv[1]
        del argv[0]
        delete_bin(outputPath, argv)
    elif (argv[1] == '-help'):
        print("\
        -packet,param should be : python packet_create.py -packet \"outputPath\" \"name|burnAddr|burnSize|type\"...\r\n\
        -split,param should be : python packet_create.py -split \"inputefile\" \"outputPath\"\r\n\
        -update,param should be : python packet_create.py -update \"outputPath\" \"name|burnAddr|burnSize|type\"...\r\n\
        -delete,param should be : python packet_create.py -delete \"inputefile\" \"name1\"...\r\n\
        -show\r\n\
        -help\r\n")
    else:
        print("parma error, please use -help for usage")
