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
* Description: Utilities.
'''

import os
import shutil
from copy import deepcopy

from hi_config_parser import usr_cfg_main
from hi_config_parser import sys_cfg_main

class SconsBuildError(Exception):
    """
    Error exception.
    """
    pass

"""
Colors to display the messages.
"""
colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

flag = {
    'ARFLAGS' : 'ar_flags',
    'CCFLAGS' : 'opts', #'cc_flags',
    'ASLAGS' : 'as_flags',
    'CPPDEFINES' : 'defines',
    'CPPPATH' : ['liteos_inc_path', 'common_inc_path'],
    'LINKFLAGS' : 'link_flags',
    'LINK_SCRIPTS_FLAG' : 'link_scripts_flag'
}

flag_r = {
    'ar_flags' : 'ARFLAGS',
    'opts' : 'CCFLAGS',
    'as_flags' : 'ASLAGS',
    'defines' : 'CPPDEFINES',
    'liteos_inc_path' : 'CPPPATH',
    'common_inc_path' : 'CPPPATH',
    'link_flags' : 'LINKFLAGS',
    'link_scripts_flag' : 'LINK_SCRIPTS_FLAG'
}

def traverse_subdir(search_dir = '.', full_path = False):
    src_path = []
    for root, dirs, files in os.walk(search_dir):
        if files != []:
            src_path.append(os.path.relpath(root, search_dir)) if full_path == False else src_path.append(root)
            print('relative dir:',os.path.relpath(root, search_dir) if full_path == False else root)
    return src_path

#compiler check
def scons_env_param_check():
    env_path_param = os.environ['PATH'].split(':')
    for param in env_path_param:
        if (param.find('gcc_riscv32') >= 0) and ((param.endswith('bin') == True) or (param.endswith(r'bin%s'%os.sep) == True)):
            compiler = os.path.join(param, 'riscv32-unknown-elf-gcc')
            return os.path.isfile(compiler)
    return False

#settings check
def scons_pre_check(dir_list):
    if len(dir_list) > 0 :
        for dir in dir_list:
            os.makedir(dir)
    usr_config_path = os.path.join('build', 'config', 'usr_config.mk')
    if os.path.isfile(usr_config_path) == False:
        shutil.copyfile(os.path.join('tools', 'menuconfig', 'default.config'), usr_config_path)
    return scons_env_param_check()

#delete files while compiling.
def cleanup(target, source, env):
    for src in source:
        name = str(src)
        try:
            if os.path.isfile(name):
                os.remove(name)
            elif os.path.isdir(name):
                shutil.rmtree(name)
            else:
                print("%s not found! Skipped!"%src)
        except:
            print("Remove %s error! Skipped!"%src)

#Display tips
def show_burn_tips():
    burn_tips_str = ''.join(
                ["%s\n< ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ >\n"%colors['purple'],
                 "                              BUILD SUCCESS                              \n",
                 "< ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ >\n%s"%colors['end']
                ])
    print(burn_tips_str)

#Display alert
def show_alert(msg):
    print("%s%s%s"%(colors['red'], msg, colors['end']))

#Simple dd tool.
def scons_bin_dd(source, target, **kw):
    seek = kw.get('seek')
    skip = kw.get('skip')
    count = kw.get('count')
    bs = kw.get('bs', 1024)
    data = None
    img_data = None
    if seek is not None:
        with open(source, 'rb') as src:
            data = bytearray(src.read())
        mode = 'ab+'
        if os.path.exists(target):
            mode = 'rb+'
        with open(target, mode) as image:
            image.seek(0, 1)
            img_data = bytearray(image.read())
        with open(target, 'wb') as image:
            if count is not None:
                append_len = count*bs
            else:
                append_len = len(data)
            old_len = len(img_data)
            new_len = seek*bs + append_len
            if new_len > old_len:
                wr_data = bytearray(new_len)
                if old_len > 0:
                    wr_data[0:old_len] = img_data
                img_data = wr_data
            img_data[seek*bs : new_len] = data[0 : append_len]
            image.seek(0, 1)
            image.write(img_data)
        return True
    if skip is not None:
        with open(source, 'rb') as src:
            src.seek(skip*bs)
            data = src.read()
        with open(target, 'wb') as image:
            image.write(data)
        return True
    raise SconsBuildError("%s============== dd PARAMETER INPUT ERROR! =============%s"%(colors['red'], colors['end']))

def bf_to_str(bf):
    if bf is None:
        return '(unknown targets product None in list)'
    elif bf.node:
        return '%s: %s'%(str(bf.node), bf.errstr)
    elif bf.filename:
        return '%s: %s'%(bf.filename, bf.errstr)
    else:
        return str(bf)

"""
Interfaces for reading the settings made by menuconfig.
"""
def scons_usr_string_option(option):
    options = usr_cfg_main()
    value = options.get(option)
    if value:
        value = value.strip('"')
    return value

def scons_usr_int_option(option):
    options = usr_cfg_main()
    return int(options.get(option))

def scons_usr_bool_option(option):
    options = usr_cfg_main()
    if option in options.keys():
        return options[option].lower()
    return 'n'

"""
Interfaces for reading the settings of system.
"""
def scons_sys_string_option(option):
    options = sys_cfg_main()
    if option in options.keys():
        return options[option].strip('"')
    return None

def scons_sys_bool_option(option):
    options = sys_cfg_main()
    if option in options.keys():
        return options[option].lower()
    return 'n'

def get_opt_val(options, option):
    bool_list = ['Y', 'y', 'N', 'n']
    if options[option].isdigit():
        return int(options.get(option))
    elif options[option] in bool_list:
        return options[option].lower()
    else:
        return options[option].strip('"')

def scons_get_cfg_val(option):
    usr_config = usr_cfg_main()
    sys_config = sys_cfg_main()
    if option in usr_config.keys():
        return get_opt_val(usr_config, option)
    elif option in sys_config.keys():
        return get_opt_val(sys_config, option)
    else:
        return 'n'

def select_added_cfg(macro, macro_val, macro_cfg, depends=None):
    if isinstance(macro_val, str) and scons_get_cfg_val(macro) == macro_val:
        if depends is None:
            temp = deepcopy(macro_cfg)
            for cfg in macro_cfg:
                if '$' not in cfg:
                    pass
                else:
                    tmp_cfg = cfg.split('=')[1].strip('$').strip('(').strip(')').strip()
                    tmp_cfg_val = '%s=%s'%(cfg.split('=')[0], scons_get_cfg_val(tmp_cfg))
                    temp.append(tmp_cfg_val)
                    temp.remove(cfg)
            return temp
        (macro_2, macro_2_val) = depends
        if scons_get_cfg_val(macro_2) == macro_2_val:
            return macro_cfg
    elif not isinstance(macro_val, str):
        val = scons_get_cfg_val(macro)
        if 'others' in macro_val:
            except_list = deepcopy(macro_val)
            except_list.remove('others')
            if val in except_list:
                return macro_cfg[val]
            else:
                return macro_cfg['others']
        elif val in macro_val:
            return macro_cfg[val]

    return None

def translate_env_value_to_str(name, macro_cfg, mod_flag):
    if name == 'defines':
        if isinstance(macro_cfg, str):
            return 'DEFINES += -D%s'%macro_cfg if mod_flag is False else 'CCFLAGS += -D%s'%macro_cfg
        else:
            defines = ['-D%s'%x for x in macro_cfg if isinstance(x, str)]
            defines.extend(['-D%s=%s'%x for x in macro_cfg if isinstance(x, tuple)])
            return 'DEFINES += %s'%(' '.join(defines)) if mod_flag is False else 'CCFLAGS += %s'%(' '.join(defines))
    elif name == 'liteos_inc_path':
        os_path = '$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS'
        if isinstance(macro_cfg, str):
            return 'INCLUDE += -I%s/%s'%(os_path, macro_cfg) if mod_flag is False else 'CCFLAGS += -I%s/%s'%(os_path, macro_cfg)
        else:
            includes = ['-I%s/%s'%(os_path, x) for x in macro_cfg]
            return 'INCLUDE += %s'%('\\\n\t'.join(includes)) if mod_flag is False else 'CCFLAGS += %s'%('\\\n\t'.join(includes))
    elif name == 'common_inc_path':
        if isinstance(macro_cfg, str):
            inc_str = '-I%s'%(macro_cfg[2:] if macro_cfg.startswith('#') else macro_cfg)
            return 'INCLUDE += %s'%inc_str if mod_flag is False else 'CCFLAGS += %s'%inc_str
        else:
            inc_str = '-I$(MAIN_TOPDIR)/%s'%('\\\n\t-I$(MAIN_TOPDIR)/'.join([x[2:] for x in macro_cfg]))
            return 'INCLUDE += %s'%inc_str if mod_flag is False else 'CCFLAGS += %s'%inc_str
    else:
        if isinstance(macro_cfg, str):
            return '%s += %s'%(flag_r[name], macro_cfg)
        else:
            return '%s += %s'%(flag_r[name], ' '.join(macro_cfg))

def condition_str(macro, macro_val, macro_cfg, env_type, depends = None, mod_flag = False):
    if isinstance(macro_val, str):
        if depends is None:
            return 'ifeq ($(%s), %s)\n\t%s\nendif\n'%(macro, macro_val, translate_env_value_to_str(env_type, macro_cfg, mod_flag))
        else:
            (macro_2, macro_2_val) = depends
            return 'ifeq ($(%s)_$(%s), %s_%s)\n\t%s\nendif\n'%(macro, macro_2, macro_val, macro_2_val, translate_env_value_to_str(env_type, macro_cfg, mod_flag))
    else:
        strs = ''
        val_list = deepcopy(macro_val)
        val_list.remove('others') if 'others' in val_list else None
        strs = '%sifeq ($(%s), %s)\n\t%s\n'%(strs, macro, val_list[0], translate_env_value_to_str(env_type, macro_cfg[val_list[0]], mod_flag))
        for val in val_list[1:]:
            strs = '%selse ifeq ($(%s), %s)\n\t%s\n'%(strs, macro, val, translate_env_value_to_str(env_type, macro_cfg[val], mod_flag))
        strs = '%selse\n\t%s\n'%(strs, translate_env_value_to_str(env_type, macro_cfg['others'], mod_flag)) if 'others' in macro_val else None
        strs = '%sendif\n'%strs
        return strs
