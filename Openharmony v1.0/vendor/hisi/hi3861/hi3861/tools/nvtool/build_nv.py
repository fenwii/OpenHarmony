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
* Description: nv build scripts.
'''

import os
import sys
import re
import subprocess
import configparser
import shutil
import sys
import xml.etree.ElementTree as ET
import copy
from ctypes import *
import time
import hashlib
import binascii
import datetime
from zlib import crc32
import struct
sys.path.append("'..', '..', 'build'")
#from  scripts.analyze_dependence  import user_pannel_config

#-----------------------------------基本错误定义-----------------------------------
HI_ERR_SUCCESS = 0
#-----------------------------------基本类型定义-----------------------------------
HI_CHAR = c_char
HI_S8 = c_byte
HI_U8 = c_ubyte
HI_S16 = c_short
HI_U16 = c_ushort
HI_S32 = c_int
HI_U32 = c_uint
#-----------------------------------NV结构体定义-----------------------------------
class NV_FILE_STRU(Structure):
    _fields_ = [
        ("magic", HI_U32),
        ("crc", HI_U32),
        ("ver", HI_U8),
        ("head_len", HI_U8),
        ("total_num", HI_U16),
        ("seq", HI_U32),
        ("ver_magic", HI_U32),
        ("flash_size", HI_U32),
        ("keep_id_range", HI_U8*2),
        ("reserve", HI_U8*2),
        ("nv_item_index", HI_U8*0),
        ]

class NV_ITEM_INDEX_STRU(Structure):
    _fields_ = [
        ("nv_id", HI_U8),
        ("nv_len", HI_U8),
        ("nv_offset", HI_U16),
        ]
NV_ITEM_INDEX_LEN = 4
NV_ITEM_CRC_LEN = 4

HNV_MAGIC = 0x24564E48
FNV_MAGIC = 0x23564E46

#SEC_CONN_SALT = '"sec conn salt"'
#SEC_NV_ID = 0x8c

###############################NV 分区头格式 ###############################################
#Hi3921不再在NV中体现Factory/Modem/APP等不同分区头

###############################NV项头信息###############################################
#Hi3921各个NV项（条目）没有头信息.

#-----------------------------------生成HNV文件流程-----------------------------------
def nv_process_mk_section(element_root, src_bin_dic, is_factory):
    nv_id_list = []
    nv_keep_id_list = []
    nv_item_bin_list = []
    nv_item_index_bin_list = []
    nv_total_size = 0
    nv_offset = 0
    nv_len = 0
    nv_total_num = 0

    #1.遍历，取出工厂区或非工厂区的所有NV ID，并排序
    for element_grp in element_root:
#        print("element_grp: ", element_grp)
#        print("NAME: ", element_grp.attrib['NAME'])
        if True == is_factory:
            if element_grp.attrib['NAME'] == 'Factory':
                for nv_element in element_grp:
                    nv_id_list.append(int(nv_element.attrib['ID'], 16))
                break;
        else:
            if element_grp.attrib['NAME'] != 'Factory':
                for nv_element in element_grp:
                    nv_id_list.append(int(nv_element.attrib['ID'], 16))
                    if element_grp.attrib['NAME'] == 'Keep':
                        nv_keep_id_list.append(int(nv_element.attrib['ID'], 16))

    nv_id_list.sort()
    nv_keep_id_list.sort()
    nv_total_num = len(nv_id_list)
    nv_offset = sizeof(NV_FILE_STRU)+nv_total_num*4#NV相对本区的偏移初始化在索引区之后

    #print(nv_id_list)

    #2.按照ID顺序生成nv_item_bin(含nv_item头和nv_item内容),添加到nv_item_bin_list中
    for nv_id in nv_id_list:
        #申请nv_item_bin空间并转换成nv_item_st
        src_bin = src_bin_dic[hex(nv_id)]
        nv_len = len(src_bin)
        nv_item_bin = bytearray(nv_len+NV_ITEM_CRC_LEN)#申请空间

        #填充nv_item_bin,并将nv_item_bin添加到nv_item_bin_list中
        nv_item_bin[0:] = src_bin#拷贝bin
        nv_item_bin[nv_len:] = struct.pack('<L', crc32(src_bin))
        nv_item_bin_list.append(nv_item_bin)

        #累加nv_item_bin总大小
        nv_total_size = nv_total_size+nv_len+NV_ITEM_CRC_LEN#计算所有nv长度

        #NV索引
        nv_item_index_bin = bytearray(NV_ITEM_INDEX_LEN)
        nv_item_index_st = NV_ITEM_INDEX_STRU.from_buffer(nv_item_index_bin)
        nv_item_index_st.nv_id = nv_id
        nv_item_index_st.nv_len = nv_len
        nv_item_index_st.nv_offset = nv_offset
        nv_item_index_bin_list.append(nv_item_index_bin)
        nv_offset = nv_offset+nv_len+NV_ITEM_CRC_LEN

    #3.生成section_bin
    #申请section_bin空间
    section_bin = bytearray(nv_total_size)

    #将nv_item_bin依次拷贝到section_bin的后面
    offset = 0
    for nv_item_bin in nv_item_bin_list:
        section_bin[offset:] = nv_item_bin
        offset = offset+len(nv_item_bin)

    #4.生成index_bin
    index_bin = bytearray(NV_ITEM_INDEX_LEN*nv_total_num)
    offset = 0
    for nv_item_index_bin in nv_item_index_bin_list:
        index_bin[offset:] = nv_item_index_bin
        offset = offset+NV_ITEM_INDEX_LEN

    return (HI_ERR_SUCCESS, nv_total_num, section_bin, index_bin, nv_keep_id_list)

'''
功能:生成hnv文件
入参
element_root:nv根节点
src_bin_dic:nv bin字典  {'0xf01':bytearray(...),....}
is_factory：是否是工厂区NV文件
返回值
ret错误码
nv_file_Bin: 类型bytearray   nv文件内容
'''
def hi_nv_process_mk_hnv(element_root, src_bin_dic, nv_file_name, is_factory):
    #print(src_bin_dic)
    global g_nv_env

    #2.生成index_bin和section_bin
#    print("element_root: ", element_root)
    (ret, nv_total_num, section_bin, index_bin, nv_keep_id_list) = nv_process_mk_section(element_root, src_bin_dic, is_factory)
    if ret != HI_ERR_SUCCESS:
        return(ret, None)

    nv_name = ''
    if is_factory == True:
        nv_name = 'Factory NV'
    else:
        nv_name = 'Normal NV'

    print("%s total num:%d"%(nv_name,nv_total_num))

    nv_index_total_size = len(index_bin)
    nv_bin_total_size = len(section_bin)

    #3.申请nv_file_Bin空间,转成nv_file_st结构并填充nv_file_st
    nv_file_Bin = bytearray(g_nv_env.flash_size)

    nv_file_st = NV_FILE_STRU.from_buffer(nv_file_Bin)

    #填充nv_file_st
    if is_factory == True:
        nv_file_st.magic = FNV_MAGIC
    else:
        nv_file_st.magic = HNV_MAGIC
    nv_file_st.ver = 0
    nv_file_st.head_len = sizeof(NV_FILE_STRU)#TODO:头的定长部分暂时没有四字节对齐
    print('NV_FILE_STRU :'+str(nv_file_st.head_len))
    nv_file_st.total_num = nv_total_num
    nv_file_st.seq = 0
    nv_file_st.ver_magic = g_nv_env.ver_magic
    nv_file_st.flash_size = g_nv_env.flash_size
    nv_file_st.reserve[0] = 0
    nv_file_st.reserve[1] = 0
    if(len(nv_keep_id_list) == 0):
        nv_file_st.keep_id_range[0] = 0
        nv_file_st.keep_id_range[1] = 0
    else:
        nv_file_st.keep_id_range[0] = 0x80
        nv_file_st.keep_id_range[1] = 0x9f

    #将index_bin添加到管理区后面，作为管理区的索引
    offset = sizeof(NV_FILE_STRU)
    nv_file_Bin[offset:offset+nv_index_total_size] = index_bin
    offset = offset+nv_index_total_size

    #将section_bin添加到管理区的索引后面
    nv_file_Bin[offset:offset+nv_bin_total_size] = section_bin
    offset = offset+nv_bin_total_size

    print("%s total size:%d"%(nv_name, offset))
    if offset > g_nv_env.flash_size:
        print("Error: NV is larger than flash_size:%d"%(g_nv_env.flash_size))
        exit(-1)

    #将nv_flash空闲区域置为F
    for i in range(offset, g_nv_env.flash_size):
        nv_file_Bin[i] = 0xFF

    #计算整区的crc32
    nv_file_st.crc = crc32(nv_file_Bin[8:g_nv_env.flash_size])

    return (HI_ERR_SUCCESS, nv_file_Bin)

class NvEnv:
    def __init__(self):
        self.app_name = []#app名称
        self.root_dir = []#编译根目录
        self.mdm_xml = []#mdm_xml全路径
        self.app_xml = []#app_xml全路径
        self.app_sdk_level = []#app sdk等级
        self.app_cfg_dir = []#客制化文件夹路径,带产品形态路径
        self.src_bin_dir = []#原bin路径,带产品形态路径

        self.product_type = []#产品形态名称
        self.temp_dir = []#临时文件夹路径,带产品形态
        self.combin_xml = []#合并后xml全路径,带or不带产品形态
        self.nv_tool_dir = []#
        self.nv_h_dir = []#
        self.nv_bin_max_size = 0
        self.flash_size = 0
        self.ver_magic = 0

g_nv_env = NvEnv()

def hi_str_to_int(line, num):
    if num is not None:
        return int(line, num)
    match1 = re.match(r'\s*0x', line)
    match2 = re.match(r'\s*0X', line)
    if match1 or match2:
        return int(line, 16)
    else:
        return int(line, 10)

''' '''
def hi_nv_set_cfg(root_dir, product_lib_out, xml_hfile_dir, product_name, app_name, hnv_dir, flash_size, ver_magic, hnv_file_name):
    global g_nv_env
    subver = g_subver_name
    if subver =='common':
        subver = app_name

    if hnv_dir is None:#hnv存放位置
        g_nv_env.hnv_dir=product_lib_out
    else:
        g_nv_env.hnv_dir=hnv_dir

    g_nv_env.nv_h_dir=xml_hfile_dir#存放结构体txt文件存放位置
    g_nv_env.app_name=app_name#app名称
    g_nv_env.product_type=product_name#产品形态名称
    g_nv_env.root_dir=root_dir#根目录
    g_nv_env.temp_dir=os.path.join(product_lib_out, app_name, '%s%s'%(g_common_ver, g_subver_name))#临时文件目录
    print('root_dir:', root_dir)
    g_nv_env.mdm_xml=os.path.join(root_dir, 'xml_file', hnv_file_name)
    print('mdm_xml:', g_nv_env.mdm_xml)
    g_nv_env.app_xml=os.path.join(root_dir, 'xml_file', 'app_nvi_db.xml')
    g_nv_env.app_cfg_dir=os.path.join(root_dir, 'xml_file')#区分不同产品形态
    print('HNV NAME:' + hnv_file_name)
    g_nv_env.combin_xml=os.path.join(product_lib_out, app_name, hnv_file_name)#合并后combin.xml路径
    g_nv_env.combin_product_xml=os.path.join(g_nv_env.temp_dir, 'mss_nvi_db_%s.xml'%(g_nv_env.product_type))#合并分割后combin_coo.xml路径
    g_nv_env.combin_product_security_xml=os.path.join(g_nv_env.temp_dir, 'combin_%s_security.xml'%(g_nv_env.product_type))#合并分割后combin_coo.xml路径

    g_nv_env.src_bin_dir=os.path.join(root_dir, 'app', g_nv_env.app_name, 'nv', 'src_bin', g_nv_env.product_type)#存放必源src bin文件路径
    g_nv_env.nv_tool=os.path.join(root_dir, 'tools', 'nv', 'cdbm')#nv工具路径
    print('nv_tool:', g_nv_env.nv_tool)
    #g_nv_env.pwd_nv_tool=os.path.join(root_dir, 'tools', 'nv', 'pwd_nv_tool.exe')#pwd nv 制作工具路径
    g_nv_env.nv_bin_max_size=65536#暂定最大支持64K flash

    g_nv_env.flash_size=flash_size
    g_nv_env.ver_magic=ver_magic
    return 0

def hi_nv_fomat_nv_id(root):
    ret = 0
    for grp in root:
        for nv in grp:
            if 'ID' in nv.attrib.keys():
                str_id=nv.attrib['ID']
                int_id=hi_str_to_int(str_id, None)
                str_id=hex(int_id)
                nv.attrib['ID']=str_id
    return 0

"""
合并xml;nv id标准化;nv 按组号进行排序
"""
def HI_NV_XmlCombineXml(src_xml_list, combin_xml):
    root_list=[]
    group_dics={}
    exist_item_id_list=[]
    global g_nv_env

    for src_xml in src_xml_list:
        tree = ET.parse(src_xml)
        root = tree.getroot()
        hi_nv_fomat_nv_id(root)#标准化NVID
        root_list.append(root)

    new_root=ET.Element('HISTUDIO')
    print('root_list', root_list)

    #判断是否有重复的ID
    for root in root_list:
        grp_list=root.findall('GROUP')#找到所有的grp
        for grp in grp_list:
            item_list=grp.findall('NV')
            for item in item_list:
                str_id=item.attrib['ID']
                int_id=hi_str_to_int(str_id, None)
                if int_id in exist_item_id_list:
                    print(exist_item_id_list)
                    return -1
                exist_item_id_list.append(int_id)

    #合并xml
    for root in root_list:
        grp_list=root.findall('GROUP')#找到所有的grp
        for grp in grp_list:
            grp_name=grp.attrib['NAME']
            if not grp_name in group_dics.keys():
                new_root.append(grp)
                group_dics[grp_name]=grp
            else:
                old_grp=group_dics[grp_name]
                sub_elements=grp.findall('NV')
                old_grp.extend(sub_elements)

    #对新xml进行排序
    element_grp_list=[]
    for element_grp in new_root:
        element_grp_list.append(element_grp)

    element_grp_list.sort(key=lambda x:int(x.attrib['ID'], 16))
    i=0
    while i< len(element_grp_list):
        new_root[i]=element_grp_list[i]
        i=i+1

    #回写xml
    new_tree=ET.ElementTree(new_root)
    new_tree.write(combin_xml, encoding="utf-8")

def hi_nv_mk_temp_dir(temp_dir, hnv_dir):
    global g_nv_env
    if os.path.exists(temp_dir):
        shutil.rmtree(temp_dir)
        os.makedirs(temp_dir)
    else:
        os.makedirs(temp_dir)

    if hnv_dir is None:
        pass
    elif not os.path.exists(hnv_dir):
        os.makedirs(hnv_dir)
    else:
        pass

"""
合并mss和app xml
"""
def hi_nv_combine_mss_and_app_xml():
    global g_nv_env
    src_xml_list=[]
    src_xml_list.append(g_nv_env.mdm_xml)
    print('mdmxml:'+g_nv_env.mdm_xml)
    if os.path.exists(g_nv_env.app_xml):
        src_xml_list.append(g_nv_env.app_xml)
        print('appxml:'+g_nv_env.app_xml)
    print('src_xml_list:', src_xml_list)
    print('combin_xml:%s'%g_nv_env.combin_xml)
    HI_NV_XmlCombineXml(src_xml_list, g_nv_env.combin_xml)

def HI_NV_XmlSplitByProductType(src_xml, product_list, dst_xml_list):
    new_root_list=[]
    tree = ET.parse(src_xml)
    root = tree.getroot()
    i=0
    #print('src_xml', src_xml)
    #print('product_list', product_list)
    #print('dst_xml_list', dst_xml_list)
    while i<len(product_list):
        new_root=copy.deepcopy(root)
        for grp in new_root:
            del_nv_list=[]
            for nv in grp:
                list=nv.attrib['DEV'].lower().split('-')
                #print('list', list)
                if product_list[i] not in list:
                    del_nv_list.append(nv)
                else:
                    pass
                    #del nv.attrib['DEV']#删除dev属性
            for nv in del_nv_list:
                grp.remove(nv)
        new_tree=ET.ElementTree(new_root)
        new_tree.write(dst_xml_list[i], encoding="utf-8")
        i=i+1

def hi_nv_split_by_product_type():
    global g_nv_env
    product_list=[]
    product_list.append(g_nv_env.product_type)
    dst_xml_list=[]
    dst_xml_list.append(g_nv_env.combin_product_xml)
    HI_NV_XmlSplitByProductType(g_nv_env.combin_xml, product_list, dst_xml_list)

def nv_replace_val(root, str_id, str_val, bForce):
    #print(str_id, str_val)

    for grp in root:
        for nv in grp:
            if nv.attrib['ID'] == str_id:
                if 0:#nv.attrib['SECURITY'] == 'PRIVATE':
                    return -1#私有NV不允许客制化
                else:
                    nv.attrib['PARAM_VALUE']=str_val

    return 0

def HI_NV_XmlModifyByCfg(cfg_file, src_xml, dst_xml):
    tree = ET.parse(src_xml)
    root = tree.getroot()
    str_id=''
    str_val=''

    with open(cfg_file) as cfg_fp:
        for line in cfg_fp.readlines():
            L=line.split('=')
            if len(L) == 2:
                key=L[0].strip()
                val=L[1].strip()
                if key == 'ID':
                    int_id=hi_str_to_int(val, None)
                    str_id=hex(int_id)
                elif key == 'PARAM_VALUE':
                    str_val = val
                    nv_replace_val(root, str_id, str_val, False)
                else:
                    pass

    new_tree = ET.ElementTree(root)
    new_tree.write(dst_xml, encoding = "utf-8")

def HI_NV_Xml2Bin(nv_tool, src_xml, dst_bin_dir, include_dir):
    cmd_line = (nv_tool, src_xml, include_dir, dst_bin_dir)
    print("\ncmd_line=", cmd_line)

    ret = subprocess.run(cmd_line).returncode
    if ret!=0:
        print('error', cmd_line)
        print("============== NV Build Failed =============")
        sys.exit(ret)

def HI_NV_HNV_Build(src_xml, dst_hnv, bin_dir):
    global g_nv_env
    #print("src_xml=", src_xml)
    print("dst_hnv=", dst_hnv)
    #print("bin_dir=", bin_dir)
    #input("继续")

    src_bin_dic = {}
    tree = ET.parse(src_xml)
    root = tree.getroot()

    bin_file_list = os.listdir(bin_dir)

    #生成bin dictionary
    for bin_file in bin_file_list:
        if bin_file.endswith(".bin"):
            bin_id = bin_file[:-len('.bin')]
            bin_file_full_name = os.path.join(bin_dir, bin_file)
            with open(bin_file_full_name, 'rb') as fp:
                bin = fp.read()
                src_bin_dic[bin_id] = bin
                #print(src_bin_dic)
                #input("继续")

    #生成工厂区NV文件_factory.hnv
    (ret, bytearray_hnv) = hi_nv_process_mk_hnv(root, src_bin_dic, os.path.basename(dst_hnv), True)
    factory_hnv = dst_hnv.replace('.hnv', '_factory.hnv')
    if len(bytearray_hnv) >= g_nv_env.nv_bin_max_size:#检测NV文件大小,边界也有问题
        print(factory_hnv, "error nv size large than nv_bin_max_size(%u)"%(g_nv_env.nv_bin_max_size))
        exit(-1)
    if ret == HI_ERR_SUCCESS:
        with open(factory_hnv, 'wb+') as hnvfp:
            hnvfp.write(bytearray_hnv)
    g_target_hnv.append(factory_hnv)

    #生成非工厂区NV文件_normal.hnv
    (ret, bytearray_hnv) = hi_nv_process_mk_hnv(root, src_bin_dic, os.path.basename(dst_hnv), False)
    normal_hnv = dst_hnv.replace('.hnv', '_normal.hnv')
    if len(bytearray_hnv) >= g_nv_env.nv_bin_max_size:#检测NV文件大小,边界也有问题
        print(normal_hnv, "error nv size large than nv_bin_max_size(%u)"%(g_nv_env.nv_bin_max_size))
        exit(-1)
    if ret == HI_ERR_SUCCESS:
        with open(normal_hnv, 'wb+') as hnvfp:
            hnvfp.write(bytearray_hnv)
    g_target_hnv.append(normal_hnv)

#def generate_pwd_nv(nv_bin_dir):
    #cmd_line = (os.path.join(nv_bin_dir, ''.join([hex(SEC_NV_ID),'.bin'])))
    #print('conn pwd: ', g_diag_auth_pwd)
    #ret = os.system(cmd_line)
    #ret = subprocess.run(cmd_line).returncode
    #if ret!=0:
    #    print('error:', cmd_line)
    #    sys.exit(ret)

def check_hnv_result(file_name):
    if os.path.exists(file_name.replace('.hnv', '_factory.hnv')):
        if os.path.exists(file_name.replace('.hnv', '_normal.hnv')):
            return 0
    return -1

def hi_nv_modify_by_cfg():
    print('hi_nv_modify_by_cfg')
    global g_nv_env
    if os.path.exists(g_nv_env.app_cfg_dir):
        cfg_file_list = os.listdir(g_nv_env.app_cfg_dir)
    else:
        return 0
    for cfg_file in cfg_file_list:
        if cfg_file.endswith(".cfg"):
            cfg_file = cfg_file[:-len('.cfg')]
            print('cfg_file:', cfg_file)
            cfg_file_full_name = os.path.join(g_nv_env.app_cfg_dir, '%s.cfg'%cfg_file)
            cfg_xml_full_name = os.path.join(g_nv_env.temp_dir, '%s.xml'%cfg_file)
            cfg_hnv_full_name = os.path.join(g_nv_env.hnv_dir, '%s.hnv'%g_nv_env.app_name)
            cfg_bin_dir = os.path.join(g_nv_env.temp_dir, cfg_file)
            if os.path.exists(cfg_bin_dir):
                shutil.rmtree(cfg_bin_dir)
                os.makedirs(cfg_bin_dir)
            else:
                os.makedirs(cfg_bin_dir)

            HI_NV_XmlModifyByCfg(cfg_file_full_name, g_nv_env.combin_product_xml, cfg_xml_full_name)

            HI_NV_Xml2Bin(g_nv_env.nv_tool, cfg_xml_full_name, cfg_bin_dir, g_nv_env.nv_h_dir)
            #替换0x90安全连接NV
            #generate_pwd_nv(cfg_bin_dir)
            #将xml和bin文件合成hnv文件
            HI_NV_HNV_Build(cfg_xml_full_name, cfg_hnv_full_name, cfg_bin_dir)
            ret = check_hnv_result(cfg_hnv_full_name)
            if ret!=0:
                print('Build hnv ERROR:%s'%cfg_hnv_full_name)
                sys.exit(ret)
            print('build hnv OK:%s'%cfg_hnv_full_name)
    print('ENDING')

g_common_ver = 'bbit_'
g_subver_name = 'common'
def hi_nv_mk_app_subtemp_dir(product_lib_out, app_name):
    app_subver_temp_dir = os.path.join(product_lib_out, app_name, '%s%s'%(g_common_ver, g_subver_name))
    print('app_subver_temp_dir:%s'%app_subver_temp_dir)

    if os.path.exists(product_lib_out):
        if os.path.exists(app_subver_temp_dir):
            shutil.rmtree(app_subver_temp_dir)
        else:
            os.makedirs(app_subver_temp_dir)
            print('make app_subver_temp_dir')

def hi_app_subver_list_filter(app_name, subver_list):
    app_subver_list = []
    for sub_name in subver_list:
        if sub_name == app_name:
            app_subver_list.append('common')
        else:
            app_subver_list.append(sub_name)
    return app_subver_list

g_root_dir = os.path.abspath(os.path.dirname(__file__))
g_out_dir = os.path.join(g_root_dir, 'out_nv_bin')#sys.argv[2] #nv编译结果根目录，v1r1/build_tmp/HiMDL_release(该名称可变)
g_flash_size = 4096#int(sys.argv[3])
#g_diag_auth_pwd = 'cih518@AMR'#(sys.argv[4])
g_ver_magic = 0#ver_magic在制作hupg的时候会重新写入，此处默认0即可，可用于单独升级NV场景下（正常无此场景），固定赋值。
#g_user_pannel_config = user_pannel_config()
#g_project_name = g_user_pannel_config.get_project_name()
g_project_name = 'himdl'
g_target_hnv = []

def HI_NV_MakeMain(root_dir, product_lib_out, xml_hfile_dir, product_name, app_name, app_subver_list, hnv_dir,
                   flash_size, ver_magic, hnv_file_name):
    global g_common_ver
    global g_subver_name
    #common_ver_list = ['bbit_', 'outside_']
    common_ver_list = ['outside_']
    if app_subver_list == []:
        print(app_name.upper(), 'selected 0 nv config!!!please select at least one!!!')
        sys.exit(1)
    for common_ver in common_ver_list:
        g_common_ver = common_ver
        for subver_name in app_subver_list:
            print('current subver_name:%s'%subver_name)
            g_subver_name = subver_name
            ret = hi_nv_set_cfg(root_dir, product_lib_out, xml_hfile_dir, product_name, app_name, hnv_dir, flash_size,
                                ver_magic, hnv_file_name)
            if ret != 0:
                continue
            hi_nv_mk_app_subtemp_dir(product_lib_out, app_name)
            hi_nv_combine_mss_and_app_xml()
            hi_nv_split_by_product_type()
            hi_nv_modify_by_cfg()

def make_nv_bin(target_path = '.', target_name = 'hi3861', hnv_file_name = ''):
    product_name_list = ['sta']
    ''' analyse begin '''
    app_name_list = [target_name]
    print('product_name_list:', product_name_list)
    for product_name in product_name_list:
        product_out_dir = os.path.join(g_out_dir, product_name)
        product_lib_out = os.path.join(product_out_dir, 'nv')
        xml_hfile_dir = os.path.join(g_root_dir, 'h_file', 'nv')
        print('xml h file:', xml_hfile_dir)
        hnv_dir = os.path.join(product_out_dir, 'nv', 'hnv')
        hi_nv_mk_temp_dir(product_lib_out, hnv_dir)
        print(product_out_dir)
        for app_name in app_name_list:
            nv_total_list = ['demo']
            app_subver_list = hi_app_subver_list_filter(app_name, nv_total_list)
            print('app_subver_list:', app_subver_list)
            HI_NV_MakeMain(g_root_dir, product_lib_out, xml_hfile_dir, product_name, app_name, app_subver_list, hnv_dir,
                           g_flash_size, g_ver_magic, hnv_file_name)

    if len(g_target_hnv) > 0:
        for hnv in g_target_hnv:
            shutil.copy(hnv, target_path)

if __name__ == '__main__':
    if len(sys.argv) == 4:
        make_nv_bin(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        filename = sys.argv[1]
        target_name = sys.argv[2]
        default_target_path = os.path.join(g_root_dir, '..', '..', 'build', 'build_tmp', 'nv')
        if os.path.exists(default_target_path) is False:
            os.makedirs(default_target_path)
        make_nv_bin(default_target_path, target_name, filename)

