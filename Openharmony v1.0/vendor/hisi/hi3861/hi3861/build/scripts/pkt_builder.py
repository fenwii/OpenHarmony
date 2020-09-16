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
* Description: hupg main build scripts
'''

import os
import time
import sys
import make_upg_file as MAKE_IMAGE
from packet_create import packet_bin
from scons_utils import scons_get_cfg_val
import shutil

root_path = os.path.join(os.getcwd(), '..', '..') if getattr(sys, 'frozen', False) else os.path.join(os.path.dirname(__file__), '..', '..')
print('execute ota_builder with exe...') if getattr(sys, 'frozen', False) else print('execute ota_builder with python...')
class ImageBuild:
    def __init__(self, app_name="Hi3861_demo", sign_alg=0x3F, kernel_file_ver=0, flashboot_file_ver=0, chip_product="Hi3861", usr_realtive_output='', ota_mode=0):
        self.__app_name = app_name
        self.__bootBinPath = os.path.join(root_path, usr_realtive_output, 'build', 'flashboot', 'Hi3861_flash_boot.bin')
        self.__kernelBinPath = os.path.join(root_path, usr_realtive_output, 'output', 'bin', '%s_non_rom.bin'%self.__app_name)
        self.__normalNvPath = os.path.join(root_path, 'build', 'build_tmp', 'nv', '%s_normal.hnv'%app_name)
        self.__factoryNvPath = os.path.join(root_path, 'build', 'build_tmp', 'nv', '%s_factory.hnv'%app_name)
        self.__pktPath = os.path.join(root_path, usr_realtive_output, 'output', 'bin')
        self.__key_dir_path = os.path.join(root_path, 'tools', 'sign_tool')
        self.__lzma_tool_path = os.path.join(root_path, r'tools', r'lzma_tool', r'lzma_tool')
        self.__build_tmp_path = os.path.join(root_path, usr_realtive_output, 'output', 'bin')
        self.__image_id = 0x3C78961E
        self.__kernel_file_ver = kernel_file_ver
        self.__flashboot_file_ver = flashboot_file_ver
        self.__encrypt_flag = 0x42
        self.__sign_alg = sign_alg
        self.__boot_bin_max_size = 32*1024 #32K
        self.__kernel_1st_bin_max_size = 912*1024 #912K
        self.__kernel_2nd_bin_max_size = 968*1024 #968K
        self.__kernel_bin_max_size = self.__kernel_1st_bin_max_size
        self.__kernel_upg_max_size = (912 + 968) * 1024
        self.__factory_bin_max_size = 600*1024 #600K
        self.__chip_product_name = chip_product
        self.__file_attr_encrypt = 0x2 # encrypt
        self.__kernel_file_attr_ota = 0x4 # compression ota
        self.__flashboot_file_attr_ota = 0x4 # compression ota
        self.__ota_mode = ota_mode #0：compression ota; 1: dual partition ota

    def set_file_attr_encrypt(self, attr_encrypt):
        self.__file_attr_encrypt = attr_encrypt

    def set_kernel_file_attr_ota(self, attr_ota):
        if attr_ota == 'A':
            attr_ota = 1
        elif attr_ota == 'B':
            attr_ota = 2
        self.__kernel_file_attr_ota = attr_ota

    def set_flashboot_file_attr_ota(self, attr_ota):
        self.__flashboot_file_attr_ota = attr_ota

    def set_chip_product_name(self, name):
        self.__chip_product_name = name

    def set_kernel_max_size(self, signature):
        if signature == 'A':
            self.__kernel_bin_max_size = self.__kernel_1st_bin_max_size
        elif signature == 'B':
            self.__kernel_bin_max_size = self.__kernel_2nd_bin_max_size
        elif signature == 0:
            self.__kernel_bin_max_size = self.__kernel_upg_max_size
        elif signature == 4:
            self.__kernel_bin_max_size = self.__factory_bin_max_size
        else:
            sys.exit("[ERR]signature err: < %s >, from: %s"%(signature, os.path.realpath(__file__)))

    def set_src_path(self, boot_bin_path = None, kernel_bin_path = None, normal_nv_path = None, factory_nv_path = None):
        self.__bootBinPath = boot_bin_path if boot_bin_path is not None else self.__bootBinPath
        self.__kernelBinPath = kernel_bin_path if kernel_bin_path is not None else self.__kernelBinPath
        self.__normalNvPath = normal_nv_path if normal_nv_path is not None else self.__normalNvPath
        self.__factoryNvPath = factory_nv_path if factory_nv_path is not None else self.__factoryNvPath

    def set_pkt_path(self, pkt_dir_path):
        self.__pktPath = pkt_dir_path

    def set_build_temp_path(self, build_temp_path):
        self.__build_tmp_path = build_temp_path

    def set_app_name(self, app_name):
        self.__app_name = app_name

    def set_image_id(self, image_id):
        self.__image_id = image_id

    def set_kernel_file_ver(self, file_version):
        self.__kernel_file_ver = file_version

    def set_flashboot_file_ver(self, file_version):
        self.__flashboot_file_ver = file_version

    def get_kernel_file_ver(self):
        return self.__kernel_file_ver

    def get_flashboot_file_ver(self):
        return self.__flashboot_file_ver

    def set_encrypt_flag(self, encrypt_flag):
        self.__encrypt_flag = encrypt_flag

    def set_sign_alg(self, sign_alg):
        self.__sign_alg = sign_alg

    def dual_partion_ota_work(self, signature = None):
        self.BuildUpgBoot()
        #制作升级文件和烧写文件先后顺序不能调整
        #self.set_encrypt_flag(0xFF) #顺序不能调整,需要在编译flupgbin结束后设置
        self.BuildUpgBin()
        self.BuildHiburnBin()

    def compress_ota_work(self, signature = None):
        app_name = self.__app_name
        pkt_dir_path = self.__pktPath
        ota_ori_file = os.path.join(pkt_dir_path, '%s_ota_tmp.bin'%app_name)
        self.BuildUpgBoot()
        #制作升级文件和烧写文件先后顺序不能调整
        self.BuildUpgBin(target = ota_ori_file)
        self.BuildHiburnBin(ota_file = ota_ori_file)
        #self.set_encrypt_flag(0xFF) #顺序不能调整,需要在编译upgbin结束后设置
        self.BuildCompressUpgBin(ota_file = ota_ori_file)

    def BuildUpgBoot(self, target = None, source = None):
        app_name = self.__app_name
        pkt_dir_path = self.__pktPath
        file_attr = (self.__file_attr_encrypt << 6) + self.__flashboot_file_attr_ota

        #bootupg配置
        flash_boot_file = self.__bootBinPath
        if not os.path.exists(flash_boot_file):
            print("flash_boot_file from: ", flash_boot_file)
            sys.exit("[ERR]flash boot file is not exist, from: %s"%os.path.realpath(__file__))

        # 构造输出文件名 #
        image_file = os.path.join(pkt_dir_path, '%s_flash_boot_ota.bin'%app_name) if target is None else target
        print("********************package boot upgrade file********************")
        MAKE_IMAGE.make_bootupg(self.__image_id, self.__flashboot_file_ver, self.__encrypt_flag, flash_boot_file, image_file, self.__key_dir_path, self.__boot_bin_max_size, self.__sign_alg, self.__chip_product_name, file_attr)
        return image_file

    def BuildUpgBin(self, target = None):
        app_name = self.__app_name
        pkt_dir_path = self.__pktPath
        file_attr = (self.__file_attr_encrypt << 6) + self.__kernel_file_attr_ota

        #升级文件配置
        kernel_file = self.__kernelBinPath
        normal_nv_file = self.__normalNvPath
        if not os.path.exists(normal_nv_file):
            print("normal_nv_file from: ", normal_nv_file)
            sys.exit("[ERR]normal nv file is not exist, from: %s"%os.path.realpath(__file__))

        if not os.path.exists(kernel_file):
            print("kernel_file from: ", kernel_file)
            sys.exit("[ERR]kernel file is not exist, from: %s"%os.path.realpath(__file__))

        # 构造输出文件名 #
        image_file = os.path.join(pkt_dir_path, '%s_ota.bin'%app_name) if target is None else target
        print("********************package kernel&nv upgrade file********************")
        MAKE_IMAGE.make_hupg(self.__image_id, self.__kernel_file_ver, self.__encrypt_flag, kernel_file, normal_nv_file, image_file, self.__key_dir_path, self.__kernel_bin_max_size, self.__sign_alg, self.__chip_product_name, file_attr)
        return image_file

    def BuildUpgBurnBin(self, target = None):
        app_name = self.__app_name
        pkt_dir_path = self.__build_tmp_path
        file_attr = (self.__file_attr_encrypt << 6) + self.__kernel_file_attr_ota

        #升级文件配置
        kernel_file = self.__kernelBinPath
        normal_nv_file = self.__normalNvPath
        if not os.path.exists(normal_nv_file):
            print("normal_nv_file from: ", normal_nv_file)
            sys.exit("[ERR]normal nv file is not exist, from: %s"%os.path.realpath(__file__))

        if not os.path.exists(kernel_file):
            print("kernel_file from: ", kernel_file)
            sys.exit("[ERR]kernel file is not exist, from: %s"%os.path.realpath(__file__))

        # 构造输出文件名 #
        image_file = os.path.join(pkt_dir_path, '%s_ota_unencrypt.bin'%app_name) if target is None else target
        print("********************package kernel&nv upgrade file********************")
        MAKE_IMAGE.make_hupg(self.__image_id, self.__kernel_file_ver, 0x42, kernel_file, normal_nv_file, image_file, self.__key_dir_path, self.__kernel_bin_max_size, self.__sign_alg, self.__chip_product_name, file_attr)
        return image_file

    def BuildHiburnBin(self, burn_bin = None, ota_file = None):
        app_name = self.__app_name
        pkt_dir_path = self.__pktPath
        ota_mode = self.__ota_mode

        #烧写文件配置
        flash_boot_file = self.__bootBinPath
        factory_nv_file = self.__factoryNvPath
        normal_nv_file = self.__normalNvPath
        if ota_mode == 1:
            upg_file = self.BuildUpgBurnBin()
        else:
            upg_file = os.path.join(pkt_dir_path, '%s_%s.%s'%(app_name, 'ota', 'bin')) if ota_file is None else ota_file

        if not os.path.exists(flash_boot_file):
            print("flash_boot_file from: ", flash_boot_file)
            sys.exit("[ERR]flash boot file is not exist, from: %s"%os.path.realpath(__file__))

        if not os.path.exists(factory_nv_file):
            print("factory_nv_file from: ", factory_nv_file)
            sys.exit("[ERR]factory nv file is not exist, from: %s"%os.path.realpath(__file__))

        if not os.path.exists(normal_nv_file):
            print("normal_nv_file from: ", normal_nv_file)
            sys.exit("[ERR]normal nv file is not exist, from: %s"%os.path.realpath(__file__))

        if not os.path.exists(upg_file):
            print("ota file from: ", upg_file)
            sys.exit("[ERR]ota file is not exist, from: %s"%os.path.realpath(__file__))

        # 构造输出文件名 #
        image_file = os.path.join(pkt_dir_path, '%s_burn.bin'%app_name) if burn_bin is None else burn_bin
        print("********************package hiburn file********************")
        MAKE_IMAGE.make_hbin(flash_boot_file, factory_nv_file, normal_nv_file, upg_file, image_file)
        return image_file

    def BuildCompressUpgBin(self, compress_ota_bin = None, ota_file = None):
        app_name = self.__app_name
        pkt_dir_path = self.__pktPath
        file_attr = (self.__file_attr_encrypt << 6) + self.__kernel_file_attr_ota

        #制作压缩升级文件依赖文件
        upg_file = os.path.join(pkt_dir_path, '%s_%s.%s'%(app_name, 'ota', 'bin')) if ota_file == None else ota_file

        if not os.path.exists(upg_file):
            print("compress ota file from: ", upg_file)
            sys.exit("[ERR]ota file is not exist, from: %s"%os.path.realpath(__file__))

        # 构造输出文件名 #
        image_file = os.path.join(pkt_dir_path, '%s_ota.bin'%app_name) if compress_ota_bin == None else compress_ota_bin
        print("********************package compress upgrade file********************")
        MAKE_IMAGE.make_compress_hupg(self.__image_id, self.__kernel_file_ver, self.__encrypt_flag, upg_file, image_file, self.__key_dir_path, self.__kernel_upg_max_size, self.__sign_alg, self.__lzma_tool_path, self.__build_tmp_path, self.__chip_product_name, file_attr)
        return image_file

# main function #
if __name__ == '__main__':
    args = len(sys.argv)
    list = ['boot_ota', 'ota', 'burn_bin', 'ota_compress', 'factory_bin']
    if args >= 6 and sys.argv[1] in list:
        type = sys.argv[1]
        app_name = sys.argv[2]
        sign_alg = int(sys.argv[3], 16)
        kernel_file_ver = int(sys.argv[4])
        flashboot_file_ver = int(sys.argv[5])
        target = sys.argv[6]
        usr_output = sys.argv[7].split('=')[1] if len(sys.argv[7].split('='))==2 else ''
        ota_flag = 1 if scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y' else 0
        chip_product = 'Hi3861' if scons_get_cfg_val('CONFIG_TARGET_CHIP_HI3861') == 'y' else 'Hi3861L'
        fu = ImageBuild(app_name, sign_alg, kernel_file_ver, flashboot_file_ver, chip_product, usr_realtive_output=usr_output, ota_mode=ota_flag)
        fu.set_pkt_path(os.path.join(root_path, usr_output, 'output', 'bin'))
        bootBinPath = os.path.join(root_path, usr_output, 'output', 'bin', '%s_boot_signed.bin'%chip_product)
        fu.set_src_path(bootBinPath)
        fu.set_file_attr_encrypt(0x1) if scons_get_cfg_val('CONFIG_FLASH_ENCRYPT_SUPPORT') != 'y' else None
        fu.set_flashboot_file_attr_ota(0x3) if scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y' else None
        fu.set_encrypt_flag(0x42)

        version_bin = bytearray(8)
        boot_ver_bytes = flashboot_file_ver.to_bytes(4, byteorder = 'little', signed = True)
        kernel_ver_bytes = kernel_file_ver.to_bytes(4, byteorder = 'little', signed = True)
        version_bin[0:4] = boot_ver_bytes
        version_bin[4:8] = kernel_ver_bytes
        version_file = os.path.join(os.path.dirname(target), '%s_vercfg.bin'%app_name)

        if type == 'boot_ota':
            print('boot_ota')
            fu.BuildUpgBoot(target)
        elif type == 'ota':
            print('ota')
            kernelBinPath = sys.argv[8]
            sign = sys.argv[9]
            fu.set_src_path(kernel_bin_path = kernelBinPath)
            fu.set_kernel_max_size(sign) if scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y' else fu.set_kernel_max_size(0)
            fu.set_kernel_file_attr_ota(sign) if scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y' else None
            if (scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y') and (scons_get_cfg_val('CONFIG_FLASH_ENCRYPT_SUPPORT') == 'y'):
                fu.set_encrypt_flag(0xFF)
            fu.BuildUpgBin(target)
        elif type == 'factory_bin':
            print('factory_bin')
            kernelBinPath = sys.argv[8]
            fu.set_src_path(kernel_bin_path = kernelBinPath)
            fu.set_kernel_max_size(0x4)
            fu.set_kernel_file_attr_ota('A')
            fu.BuildUpgBin(target)
        elif type == 'burn_bin':
            print('burn_bin')
            ota_bin = None if scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y' else sys.argv[8]
            fu.set_src_path(kernel_bin_path = sys.argv[8]) if scons_get_cfg_val('CONFIG_COMPRESSION_OTA_SUPPORT') != 'y' else None
            fu.set_build_temp_path(build_temp_path = os.path.join(root_path, 'build', 'build_tmp', 'cache'))
            fu.BuildHiburnBin(target, ota_bin)
            with open(version_file, 'wb+') as fp:
                fp.write(version_bin)

            hilink_enable = False
            if (scons_get_cfg_val('CONFIG_HILINK') == 'y'):
                hilink_enable = True

            burn_for_erase_bin = os.path.join(root_path, 'build', 'basebin', 'burn_for_erase_4k.bin')
            allinone = os.path.join(os.path.dirname(target), '%s_allinone.bin'%app_name)
            loader_bin = os.path.join(os.path.dirname(target), '%s_loader_signed.bin'%chip_product)
            efuse_bin = os.path.join(root_path, 'build', 'basebin', 'efuse_cfg.bin')
            efuse_bin = None if not os.path.exists(efuse_bin) else efuse_bin
            boot_b = os.path.join(os.path.dirname(target), "%s_boot_signed_B.bin"%(chip_product))
            boot_b_size = os.path.getsize(boot_b)
            factory_bin_path = os.path.join(root_path, 'build', 'libs', 'factory_bin')
            factory_bin = os.path.join(factory_bin_path, '%s_factory.bin'%app_name)
            #证书安全存储示例
            tee_cert1_file = os.path.join(root_path, 'build', 'basebin', 'tee_cert1.bin');
            tee_cert2_file = os.path.join(root_path, 'build', 'basebin', 'tee_cert2.bin');
            tee_key_file = os.path.join(root_path, 'build', 'basebin', 'tee_key.bin');
            tee_cert_key_bin_max = 12*1024; #必须为4KB证书倍，需匹配分区表确定烧写地址和大小
            tee_total_file_cnt = 3; #3个文件：2个证书，1个key。
            burn_tee_cert = False
            if ((os.path.exists(tee_cert1_file)) and (os.path.exists(tee_cert2_file)) and (os.path.exists(tee_key_file))):
                burn_tee_cert = True

            burn_bin_ease_size = 0x200000;
            if (hilink_enable == True):
                burn_bin_ease_size = 0x200000 - 0x8000 - 0x1000 - 0x2000
            if (burn_tee_cert == True):
                burn_bin_ease_size = 0x200000 - 0x8000 - 0x1000 - 0x2000 - 0x5000

            if os.path.exists(factory_bin):
                list = ['%s|0|0|0'%loader_bin, '%s|0|0|3'%efuse_bin, '%s|0|%d|1'%(target, burn_bin_ease_size), '%s|%d|%d|6'%(factory_bin, 0x14D000, 0x96000)] if efuse_bin!=None else ['%s|0|0|0'%loader_bin, '%s|0|%d|1'%(target, burn_bin_ease_size), '%s|%d|%d|6'%(factory_bin, 0x14D000, 0x96000)]
                shutil.copytree(factory_bin_path, os.path.join(os.path.dirname(target), 'factory_bin'))
            else:
                list = ['%s|0|0|0'%loader_bin, '%s|0|0|3'%efuse_bin, '%s|0|%d|1'%(target, burn_bin_ease_size)] if efuse_bin!=None else ['%s|0|0|0'%loader_bin, '%s|0|%d|1'%(target, burn_bin_ease_size)]

            if ((hilink_enable == True) or (burn_tee_cert == True)):
                list.append('%s|%d|%d|1'%(burn_for_erase_bin, 0x200000 - 0x8000 - 0x1000, 0x1000))

            list.append('%s|%d|%d|1'%(boot_b, 0x200000 - boot_b_size, boot_b_size));

            if (burn_tee_cert == True):
                cert_key_bin = bytearray(tee_cert_key_bin_max)
                tee_cert1_size = os.path.getsize(tee_cert1_file)
                tee_cert2_size = os.path.getsize(tee_cert2_file)
                tee_key_size = os.path.getsize(tee_key_file)
                total_cert_key_size = tee_cert1_size + tee_cert2_size + tee_key_size
                if (total_cert_key_size > tee_cert_key_bin_max - 4 - 4 - 4*tee_total_file_cnt):
                    print('[ERROR]: cert total len bigger than tee_cert_key_bin_max!!!')
                    sys.exit(1)
                else:
                    with open(tee_cert1_file, 'rb') as fp:
                        tee_cert1_bin = fp.read()
                    with open(tee_cert2_file, 'rb') as fp:
                        tee_cert2_bin = fp.read()
                    with open(tee_key_file, 'rb') as fp:
                        tee_key_bin = fp.read()

                    #填充头部结构
                    start_flag = 0xDEADBEEF
                    start_flag_bytes = start_flag.to_bytes(4, byteorder = 'little', signed = False)
                    cert_key_bin[0:4] = start_flag_bytes #填充魔术字
                    tee_total_file_cnt_bytes = tee_total_file_cnt.to_bytes(4, byteorder = 'little', signed = True)
                    cert_key_bin[4:8] = tee_total_file_cnt_bytes #填充总的文件数
                    #填充各文件的大小
                    cert_key_bin[8:12] = tee_cert1_size.to_bytes(4, byteorder = 'little', signed = True)
                    cert_key_bin[12:16] = tee_cert2_size.to_bytes(4, byteorder = 'little', signed = True)
                    cert_key_bin[16:20] = tee_key_size.to_bytes(4, byteorder = 'little', signed = True)
                    #填充各文件
                    cert_key_bin[20:20 + tee_cert1_size] = tee_cert1_bin
                    cert_key_bin[20 + tee_cert1_size:20 + tee_cert1_size + tee_cert2_size] = tee_cert2_bin
                    cert_key_bin[20 + tee_cert1_size + tee_cert2_size:20 + tee_cert1_size + tee_cert2_size + tee_key_size] = tee_key_bin
                    #写文件
                    cert_bin_file = os.path.join(root_path, "output", "bin", '%s_tee_cert_key.bin'%app_name)
                    with open(cert_bin_file, 'wb+') as fp:
                        fp.write(cert_key_bin)
                    list.append('%s|%d|%d|1'%(cert_bin_file, 0x200000 - 0x8000 - 0x1000 - 0x2000 - 0x5000, tee_cert_key_bin_max))

            if (sign_alg != 0x3F): #only need write ver file in secure boot mode.
                list.append('%s|0|0|7'%version_file)
            packet_bin(allinone, list)
            if os.path.exists(factory_bin_path):
                shutil.rmtree(factory_bin_path)
        elif type == 'ota_compress':
            print('ota_compress')
            ota_bin = sys.argv[8]
            fu.set_kernel_file_attr_ota(0x4)
            fu.set_kernel_max_size(0) #(912+968)KB
            fu.set_build_temp_path(build_temp_path = os.path.dirname(ota_bin))
            if scons_get_cfg_val('CONFIG_FLASH_ENCRYPT_SUPPORT') == 'y':
                fu.set_encrypt_flag(0xFF)
            fu.BuildCompressUpgBin(target, ota_bin)
    elif args == 5 or args == 3:
        sign_alg = int(sys.argv[1], 16)
        dual_ota_flag = sys.argv[2]
        flashboot_file_ver = 0 if args != 5 else int(sys.argv[3])
        kernel_file_ver = 0 if args != 5 else int(sys.argv[4])
        lib_path = os.path.join(root_path, 'build', 'scripts')
        sys.path.append(lib_path)
        from hi_config_parser import UsrCfgParser

        class BaseCfgParser(UsrCfgParser):
            def get_default_config_file(self):
                return os.path.join(root_path, 'platform', 'os', 'Huawei_LiteOS', '.config')

        options = BaseCfgParser().do_parse()
        chip_product = options.get('LOSCFG_COMPILER_CHIP_VER')
        app_name = chip_product + '_demo'
        if app_name:
            app_name = app_name.strip('"')

        t1 = time.time()
        print("&&&&&&&&&&&&&args", sign_alg, dual_ota_flag, flashboot_file_ver, kernel_file_ver)
        fu = ImageBuild(app_name, sign_alg, kernel_file_ver, flashboot_file_ver, chip_product, ota_mode=int(dual_ota_flag))
        fu.set_encrypt_flag(0x42)
        if int(dual_ota_flag) == 0:
            fu.set_kernel_max_size(0)
            fu.compress_ota_work()
        else:
            fu.set_kernel_file_attr_ota('A') #kernelA
            fu.set_flashboot_file_attr_ota(0x3) #kernelA|kernelB
            fu.dual_partion_ota_work()

        print ("Package finish!! \r\n")
        print('TOTAL TIME:%ss'%str(time.time() - t1))
    else:
        print('[ERROR]: build ota parameters err!!!')
        sys.exit(1)
