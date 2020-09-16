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
* Description: extract strings from .c file, then, generate .cfg file.
'''

import os
import time
import string
import re
import shutil
import hashlib
import binascii
import sys
import io
import subprocess

g_params = {}
g_file_id_dic = {}
g_mod_id_dic = {}

#convert sys argvs from str to dictionary
def mk_param_dic():
    key='default_key'
    key_val=''
    i=0
    while i< len(sys.argv):
        if sys.argv[i]=='_PYTHON_ARG_':
            if key!='default_key':
                g_params[key]=key_val
            else:
                pass

            key = sys.argv[i + 1]
            key_val = ''
            i = i + 1
        else:
            key_val = '%s%s '%(key_val, sys.argv[i])
        i = i + 1

    #last key process
    if key!='default_key':
        g_params[key]=key_val
    #add interl param
    g_params['I_FILE_DIR'] = os.path.join(g_params['PRIM_XML_TEMP_ROOT_DIR'].strip(), g_params['PRIM_XML_KEY_WORD'])

#convert file_id_file(lm_file_id.cfg) to dictionary
def create_file_id_dic(path = None):
    file_name = g_params['PRIM_XML_FILE_ID_FILE'].strip(' ') if path is None else path
    with open(file_name, 'r') as f1:
        for line in f1:
            list_temp=re.split('[ \t\n\r\f\v]+', line)
            if len(list_temp) >= 2 and list_temp[0][-2:]=='.c' and list_temp[1].isdigit():
                g_file_id_dic[list_temp[0]]=list_temp[1]
    print('g_file_id_dic', g_file_id_dic)
    return g_file_id_dic

#convert mod_id_file(lm_file_id.cfg) to dictionary
def create_mod_id_dic():
    file_name = g_params['PRIM_XML_MOD_ID_FILE'].strip(' ')
    with open(file_name, 'r') as f1:
        for line in f1:
            list_temp=re.split('[ \t\n\r\f\v]+', line)
            if len(list_temp) >= 2 and list_temp[0][-2:]=='.c' and list_temp[1].isdigit():
                g_mod_id_dic[list_temp[0]]=list_temp[1]
        print('g_mod_id_dic', g_mod_id_dic)

#Generates a list of files(.c) from all subdirectories
def creat_src_file_list():
    full_file_name_list = []
    sub_dir_list = g_params['PRIM_XML_SRC_SUB_DIR'].split(' ')
    print('sub_dir_list')
    print(sub_dir_list)
    for sub_dir in sub_dir_list:
        sub_dir=sub_dir.strip()
        if sub_dir:
            full_dir = g_params['PRIM_XML_SRC_ROOT_DIR']
            full_dir = full_dir.strip()
            full_dir = os.path.join(full_dir, sub_dir)
            print('full_dir=', full_dir)
            file_name_list = os.listdir(full_dir)
            print('file_name_list=', file_name_list)
            for file_name in file_name_list:
                full_file_name = os.path.join(full_dir, file_name)
                if os.path.isfile(full_file_name):
                    print('isfile=', full_file_name)
                    if full_file_name.endswith('.c'):
                        print('cfile=', full_file_name)
                        full_file_name_list.append(full_file_name)
    print('full_file_name_list=', full_file_name_list)
    return full_file_name_list

#pre-compile .c to .i
def conver_c_2_i(full_file_name_list):
    dst_full_file_name_list = []
    print('conver_c_2_i=', full_file_name_list)
    temp_dir = g_params['I_FILE_DIR'].strip()
    if os.path.isdir(temp_dir):
        shutil.rmtree(temp_dir)
    os.makedirs(temp_dir)
    cc=g_params['CC'].strip()
    cflag = g_params['CFLAGS'].strip()
    for src_full_file_name in full_file_name_list:
        src_file_name = src_full_file_name.split('/')[-1]

#        if src_file_name in g_file_id_dic and src_file_name in g_mod_id_dic:
        if src_file_name in g_file_id_dic:
            print('E2I:', src_file_name)
            dst_file_name = src_file_name
            dst_file_name=dst_file_name.replace('.c', '.i')
            dst_full_file_name = os.path.join(temp_dir, dst_file_name)

            cmd_line = [cc, '-E', src_full_file_name, cflag, '-D__FILE_NAME__=%s'%src_file_name,
                        '-D__FILE_IDX__=%s'%g_file_id_dic[src_file_name], '-P', '>', dst_full_file_name]
            print('cmd_line=', cmd_line)
            subprocess.run(cmd_line)
            dst_full_file_name_list.append(dst_full_file_name)
    return dst_full_file_name_list

def para_exist_i_file(file_name):
    key_word = g_params['PRIM_XML_KEY_WORD'].strip()
    parse_file = os.path.join(os.path.dirname(file_name), '%s.cfg'%key_word)
    print('file_name parse_file=', file_name, parse_file)
    with open(file_name, 'r') as f1, open(parse_file, 'w+') as f2:
        for line in f1:
            match=re.search('PRIM_XML_HI_DIAG_LOG_MSG_', line)
            if match:
                match_id=re.search('_PRIM_ID_:', line)
                match_sz=re.search(',_PRIM_SZ_:', line)
                match_line=re.search(',_PRIM_LINE_:', line)
                match_file=re.search(',_PRIM_FILE_:', line)
                match_file=re.search(',_PRIM_FILE_:', line)
#parse file :get print info
def cp_effect_content_on_file(cfg_fp, file_name):
    with open(file_name, 'r') as src_fp:
        print('file_name-----', file_name)
        #time.sleep(5)
        for line in src_fp:
            match=re.search('_PRIM_PRI_', line)
            if match:
                print('line-----', line)
                cfg_fp.write(line.encode("UTF-8"))

def cp_effect_content(dst_full_file_name_list, cfg_file = None, scons_flag = False):
    print('cfg file:', cfg_file)
    base_folder = g_params['PRIM_XML_TEMP_BASE_ROOT_DIR'].strip() if cfg_file is None else os.path.dirname(cfg_file)
    key_word = g_params['PRIM_XML_KEY_WORD'].strip() if cfg_file is None else None
    #cfg dir not exist-->mk dir
    print('base_folder', base_folder)
    #if scons_flag == False and not os.path.isdir(base_folder):
    if not os.path.isdir(base_folder):
        print('base_folder2', base_folder)
        os.makedirs(base_folder)

    cfg_file_name = os.path.join(base_folder, '%s.cfg'%key_word) if cfg_file is None else cfg_file
    #cfg file is exist-->recreate it
    if os.path.isfile(cfg_file_name):
        os.remove(cfg_file_name)

    with open(cfg_file_name, 'ab+') as cfg_fp:
    #cfg_fp=io.open(cfg_file_name, 'wb+')
        for src_file_name in dst_full_file_name_list:
            if os.path.isfile(src_file_name):
                cp_effect_content_on_file(cfg_fp, src_file_name)

    #cfg_fp.close()

#main func
def mk_prim_main():
    print('mk_prim_main in')
    #creat sys params dictionary
    mk_param_dic()
    #print('g_params', g_params)
    print('set_print_target')
    print(g_params['LOG_FILE_NAME'].strip())

    log_file_name = g_params['LOG_FILE_NAME'].strip()
    log_file_dir = os.path.dirname(log_file_name)
    if not os.path.isdir(log_file_dir):
        os.makedirs(log_file_dir)
    with open(log_file_name, 'w+') as log_file_fp:
        last_print_target = sys.stdout
        sys.stdout = log_file_fp

        print('create_file_id_dic')
        create_file_id_dic()
        #print('create_mod_id_dic')
        #create_mod_id_dic()
        full_file_name_list = creat_src_file_list()
        print('full_file*****')
        print(full_file_name_list)
        dst_full_file_name_list = conver_c_2_i(full_file_name_list)
        print(dst_full_file_name_list)
        cp_effect_content(dst_full_file_name_list)

        sys.stdout = last_print_target
    exit(0)

if __name__ == '__main__':
    mk_prim_main()
