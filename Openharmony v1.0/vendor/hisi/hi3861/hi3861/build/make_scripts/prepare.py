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
* Description: .config parser, bases on kconfig format.
'''

import os
import sys
import shutil
proj_top_dir = os.path.realpath(os.path.join(__file__, '..', '..', '..'))
print('proj_top_dir:',proj_top_dir)
sys.path.append(os.path.join(proj_top_dir, 'build'))
from scripts.scons_env_cfg import SconsEnvCfg as EnvCfg
from scripts.scons_utils import flag
from scripts.scons_utils import flag_r
from scripts.common_env import get_fixed_config
from scripts.common_env import get_make_str
from scripts import scons_app

def mkdir(path):
    isExists=os.path.exists(path)
    if not isExists:
        os.makedirs(path)
        print ('%s create success'% path)
        return True
    else:
        return False

def create_output_dirs(env_cfg):
    dir_list = [env_cfg.bin_path, env_cfg.log_path, env_cfg.cache_path, env_cfg.link_path]
    #env_cfg.obj_path, env_cfg.lib_path,
    [mkdir(x) for x in dir_list]

def transform_env_to_make(env_cfg, module = 'common'):
    fixed_env_cfg = get_fixed_config('env_cfg')
    line = ''
    for flg in flag:
        flg_cfg = None
        if flg != 'CPPPATH':
            flg_cfg = fixed_env_cfg[flag[flg]][module] if module in fixed_env_cfg[flag[flg]] else None
        else:
            cfg_list = []
            common_inc = fixed_env_cfg['common_inc_path']
            inc_path = common_inc[module] if module in common_inc else None
            if inc_path is not None:
                for x in inc_path:
                    if x.startswith('#'):
                        cfg_list.append(x[2:])
                    else:
                        cfg_list.append(x)
            os_inc = fixed_env_cfg['liteos_inc_path']
            inc_path = os_inc[module] if module in os_inc else None
            if inc_path is not None:
                cfg_list.extend([os.path.join(os.path.relpath(env_cfg.os_root, env_cfg.root), y) for y in inc_path])
            flg_cfg = cfg_list

        if flg_cfg is None:
            continue
        if flg == 'CPPDEFINES':
            defines = ['-D%s'%x for x in flg_cfg if isinstance(x, str)]
            defines.extend(['-D%s=%s'%x for x in flg_cfg if isinstance(x, tuple)])
            line = '%sDEFINES := %s\n'%(line, ' \\\n\t'.join(defines))
        elif flg == 'CPPPATH':
            line = '%sINCLUDE := -I$(MAIN_TOPDIR)/%s\n'%(line, ' \\\n\t-I$(MAIN_TOPDIR)/'.join(flg_cfg))
        elif flg == 'LINK_SCRIPTS_FLAG':
            line = '\n'.join([
                line,
                '%s := -I$(MAIN_TOPDIR)/%s'%(flg, ' -I$(MAIN_TOPDIR)/'.join([x[2:] for x in flg_cfg if x.startswith('-I')])),
                '%s += %s'%(flg, ' '.join([x for x in flg_cfg if not x.startswith('-I')]))
            ])
        else:
            line = '%s%s := %s\n'%(line, flg, ' '.join(flg_cfg))
    return line

def prepare_config_file(env_cfg):
    config_file = os.path.join(proj_top_dir, 'build', 'make_scripts', 'config.mk')
    with open(config_file, 'w+') as fp:
        environs = env_cfg.get_makefile_environs()
        var = environs['var']
        append_var = environs['append_var']
        mod_dir = environs['mod_dir']
        modules = get_fixed_config('module')
        lib_cfg = get_fixed_config('lib_cfg')
        #env_cfg = get_fixed_config('env_cfg')
        line = '\n'.join(['include $(MAIN_TOPDIR)/build/config/sdk.mk',
                          'include $(MAIN_TOPDIR)/build/make_scripts/usr.mk',
                          'SHELL = /bin/bash',
                          'COMPILE_MODULE += %s\n'%(' '.join(modules))])
        for item in mod_dir:
            line = '%s%s := %s\n'%(line, item, mod_dir[item])

        for module_name in lib_cfg:
            libs = list(lib_cfg[module_name].keys())
            line = '%s%s_libs := %s\n'%(line, module_name, ' '.join(libs))

        for item in var:
            line = '%s%s := %s\n'%(line, item, var[item])

        #for item in append_var:
            #line = '%s%s += %s\n'%(line, item, append_var[item])

        line = '\n'.join([line,
                        'LIBS += $(patsubst lib%.a, -l%, $(notdir $(wildcard $(MAIN_TOPDIR)/build/libs/*.a)))',
                        '\n'.join(['%s += %s'%(item, append_var[item]) for item in append_var]),
                        'ifeq ($(USR_APP_ON), n)',
                        'COMPILE_MODULE += $(APP_NAME)',
                        '$(APP_NAME)_dir := app/$(APP_NAME)',
                        '$(APP_NAME)_libs := $(APP_NAME)',
                        'endif',
                        'LIBS += $(USR_LIBS)\n'])
        #line = '\n'.join([line,
                        #'LIBS += $(patsubst lib%.a, -l%, $(notdir $(wildcard $(MAIN_TOPDIR)/build/libs/*.a)))'])
        line = '\n'.join([line,
                        'PYTHON_SCRIPTS = y',
                        'ifeq ($(PYTHON_SCRIPTS),y)',
                        'NV_TOOL := python3 $(MAIN_TOPDIR)/tools/nvtool/build_nv.py',
                        'OTA_TOOL := python3 $(MAIN_TOPDIR)/build/scripts/pkt_builder.py',
                        'else',
                        'NV_TOOL := cd $(MAIN_TOPDIR)/tools/nvtool;\\',
                        '    $(MAIN_TOPDIR)/tools/nvtool/nv_builder',
                        'OTA_TOOL := cd $(MAIN_TOPDIR)/build/scripts;\\',
                        '    $(MAIN_TOPDIR)/build/scripts/ota_builder',
                        'endif\n\n'])

        line = '\n'.join([line,
                        transform_env_to_make(env_cfg = env_cfg),
                        get_make_str(),
                        'ifeq ($(FACTORY_MODE), y)',
                        'DEFINES += -DCONFIG_FACTORY_TEST_MODE',
                        'endif',
                        'LIBS += $(addprefix -l, $(foreach module, $(COMPILE_MODULE), $($(module)_libs)))',
                        'ifeq ($(CONFIG_CE_SUPPORT), y)',
                        '\tNV_CFG_NAME = mss_nvi_db.xml',
                        'endif',
                        'ifeq ($(CONFIG_FCC_SUPPORT), y)',
                        '\tNV_CFG_NAME = mss_nvi_db_fcc.xml',
                        'endif',
                        'ifeq ($(CONFIG_MAX_POWER_SUPPORT), y)',
                        '\tNV_CFG_NAME = mss_nvi_db_max.xml',
                        'endif',
                        'CCFLAGS += $(DEFINES) $(INCLUDE)\n'])
        print('+'*20,'config.mk','+'*20,'\n',line)
        fp.write(line)
#
def prepare_module_makefile(env_cfg):
    modules = env_cfg.get_all_modules()
    for x in modules:
        dst_dir = os.path.join(proj_top_dir, env_cfg.get_module_dir(x))
        dst_makefile = os.path.join(dst_dir, 'Makefile')
        print("---------dst_dir: %s proj_top_dir :%s -"%(dst_dir, proj_top_dir))
        module_mk = os.path.join(dst_dir, 'module.mk')
        if not os.path.exists(module_mk):
            src_makefile = os.path.join(proj_top_dir, 'build', 'make_scripts', 'module.mk')
            shutil.copyfile(src_makefile, dst_makefile)
        else:
            shutil.move(module_mk, dst_makefile)
#
def prepare_module_lib_cfg(env_cfg, module):
    src_makefile = os.path.join(proj_top_dir, env_cfg.get_module_dir(module), 'module_config.mk')
    print('module:',module)
    if os.path.exists(src_makefile):
        return

    with open(src_makefile, 'w+') as fp:
        lib_cfg = get_fixed_config('lib_cfg')[module]
        line = ''
        for lib_name in lib_cfg:
            line = '%s%s_srcs := %s\n'%(line, lib_name, ' '.join(lib_cfg[lib_name]))

        #transform_env_to_make(env_cfg, module)
        fixed_env_cfg = get_fixed_config('env_cfg')
        for flg in flag:
            #flg_cfg = env_cfg.get_module_cfg(module, flg, fixed=True)
            flg_cfg = None
            if flg != 'CPPPATH':
                flg_cfg = fixed_env_cfg[flag[flg]][module] if module in fixed_env_cfg[flag[flg]] else None
            else:
                cfg_list = []
                common_inc = fixed_env_cfg['common_inc_path']
                inc_path = common_inc[module] if module in common_inc else None
                if inc_path is not None:
                    for x in inc_path:
                        if x.startswith('#'):
                            cfg_list.append(x[2:])
                        else:
                            cfg_list.append(x)
                os_inc = fixed_env_cfg['liteos_inc_path']
                inc_path = os_inc[module] if module in os_inc else None
                if inc_path is not None:
                    cfg_list.extend([os.path.join(os.path.relpath(env_cfg.os_root, env_cfg.root), y) for y in inc_path])
                flg_cfg = cfg_list

            if flg_cfg is None:
                continue
            if flg == 'CPPDEFINES':
                defines = ['-D%s'%x for x in flg_cfg if isinstance(x, str)]
                defines.extend(['-D%s=%s'%x for x in flg_cfg if isinstance(x, tuple)])
                line = '%sCCFLAGS += %s\n'%(line, ' '.join(defines))
            elif flg == 'CPPPATH':
                line = '%sCCFLAGS += -I$(MAIN_TOPDIR)/%s\n'%(line, ' \\\n\t-I$(MAIN_TOPDIR)/'.join(flg_cfg))
            else:
                line = '%s%s += %s\n'%(line, flg, ' '.join(flg_cfg))

        module_cfg = get_make_str(module)
        line = '%s%s\n'%(line, module_cfg) if module_cfg is not None else line
        print('+'*10, ' %s module config'%module, '+'*10, '\n', line)
        fp.write(line)
#
def do_prepare(env_cfg):
    create_output_dirs(env_cfg)
    print("------------------------------------env_cfg1: %s"%(env_cfg))
    prepare_config_file(env_cfg)
    print("------------------------------------env_cfg2: %s"%(env_cfg))
    prepare_module_makefile(env_cfg)
    print("------------------------------------env_cfg3: %s"%(env_cfg))
    [prepare_module_lib_cfg(env_cfg, module) for module in env_cfg.get_all_modules()]



if __name__ == "__main__":
    args = len(sys.argv)
    print('+'*40, 'PREPARE', '+'*40)
    env_cfg = EnvCfg()
    #app_builder = scons_app.AppTarget('demo')
    #env_cfg.set_app_builder(app_builder)
    do_prepare(env_cfg)

    #print('common str','+'*50)
    #print(get_make_str())
    #print('+'*50)
