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
* Description: Default configrations of the project.
'''

import os
import hashlib

from scons_utils import colors
from scons_utils import flag_r
from scons_utils import flag
from scons_utils import scons_pre_check
from scons_utils import scons_usr_bool_option
from scons_utils import SconsBuildError
from scripts.common_env import *
from scripts.common_env import module_dir

class SconsEnvCfg:
    def __init__(self):
        """
        Make sure compiler is ready
        """
        if (scons_pre_check([]) == False):
            raise SconsBuildError("%s============== COULD NOT FIND COMPILER! =============%s"%
                (colors['red'], colors['end']))
        self.root = os.path.realpath(os.path.join(__file__, '..', '..', '..'))
        self.os_root = os.path.realpath(os.path.join(self.root, 'platform', 'os', 'Huawei_LiteOS'))
        self.tools_prefix = 'riscv32-unknown-elf-'

        #Set input/output folders
        tmp_dir = os.path.join('build', 'build_tmp')
        final_dir = 'output'
        self.log_path = os.path.join(tmp_dir, 'logs')
        self.obj_path = os.path.join(tmp_dir, 'objs')
        self.lib_path = os.path.join(tmp_dir, 'libs')
        self.cache_path = os.path.join(tmp_dir, 'cache')
        self.link_path = os.path.join(tmp_dir, 'scripts')
        self.nv_path = os.path.join(tmp_dir, 'nv')
        self.bin_path = os.path.join(final_dir, 'bin')

        #NV settings.
        self.nv_src_path = os.path.join('app', 'demo', 'nv')
        self.nv_factory_name = 'hi3861_demo_factory.hnv'
        self.nv_normal_name = 'hi3861_demo_normal.hnv'
        #mss_nvi_db_fcc.xml  FCC
        #mss_nvi_db.xml      CE
        #mss_nvi_db_max.xml  MAX_POWER
        if scons_usr_bool_option('CONFIG_CE_SUPPORT') == 'y':
            self.nv_cfg_name = 'mss_nvi_db.xml'

        if scons_usr_bool_option('CONFIG_FCC_SUPPORT') == 'y':
            self.nv_cfg_name = 'mss_nvi_db_fcc.xml'

        if scons_usr_bool_option('CONFIG_MAX_POWER_SUPPORT') == 'y':
            self.nv_cfg_name = 'mss_nvi_db_max.xml'

        #chip type
        if scons_usr_bool_option('CONFIG_TARGET_CHIP_HI3861') == 'y':
            self.chip_type = "Hi3861"
        else:
            self.chip_type = "Hi3861L"

        #Link settings
        self.base_sum = 'd11133fff0d435d699e27817e165cf1d10c1a951452bd07d40da5bcfc41ef773'
        self.link_file = os.path.join(self.link_path, 'link.lds')
        self.map_file = os.path.join(self.bin_path, '%s_demo.map'%(self.chip_type))
        self.gcc_ver_num = '7.3.0'
        self.app_name = None
        self.target_name = None
        self.app_builder = None
        self.clean_list = [tmp_dir, final_dir]
        self.clean_list.append(os.path.join('build', 'scripts', '__pycache__'))

    def set_tools(self, env, tool_name='all', tool_value='default'):
        #set compiler
        if tool_name != 'all' and tool_value != 'default' and env.get(tool_name):
            env[tool_name] = tool_value
            return

        if self.tools_prefix:
            env['CC'] = '%sgcc'%self.tools_prefix
            env['AR'] = '%sar'%self.tools_prefix
            env['AS'] = '%sas'%self.tools_prefix
            env['CXX'] = '%scpp'%self.tools_prefix
            env['LINK'] = '%sld'%self.tools_prefix
            env['RANLIB'] = '%sranlib'%self.tools_prefix
            env['OBJCOPY'] = '%sobjcopy'%self.tools_prefix
            env['OBJDUMP'] = '%sobjdump'%self.tools_prefix
        else:
            #default compiler without prefix, like gcc, g++, etc.
            print("USE DEFAULT COMPILER...")

    def get_tools(self, env, tool_name):
        if env.get(tool_name) is None:
            print('Not find tool:%s'%tool_name)
        return env.get(tool_name)

    def set_environs(self, env, env_name='all', env_value=None, module='common'):
        #Set default compile environment.
        if env_name != 'all' and env_value is not None and env.get(env_name):
            env[env_name] = env_value
            return

        env['CHIP_TYPE'] = self.chip_type
        env['ARFLAGS'] = get_proj_env_value('ar_flags', module)
        env.Append(CCFLAGS=get_proj_env_value('opts', module))
        env.Append(ASLAGS=get_proj_env_value('as_flags', module))
        env.Append(LINKFLAGS=get_proj_env_value('link_flags', module))
        env['LINK_SCRIPTS_FLAG'] = get_proj_env_value('link_scripts_flag', module)
        env['CCCOMSTR'] = 'Compiling $SOURCE'
        env['ARCOMSTR'] = 'Archiving $TARGET'
        env.Append(CPPPATH=get_proj_env_value('common_inc_path', module))
        env.Append(CPPDEFINES=get_proj_env_value('defines', module))
        if get_proj_env_value('liteos_inc_path', module) is not None:
            env.Append(CPPPATH = [os.path.join(self.os_root, x) for x in get_proj_env_value('liteos_inc_path', module)])

    def append_environs(self, env, module, env_name = None):
        if env_name is None:
            env_name = []
            for key in get_proj_env():
                if get_proj_env_value(key, module) is not None:
                    env_name.append(flag_r[key])

        for x in set(env_name):
            if x != 'CPPPATH':
                env[x].extend(get_proj_env_value(flag[x], module))
            else:
                env[x].extend(get_proj_env_value('common_inc_path', module))
                if get_proj_env_value('liteos_inc_path', module) is not None:
                    env[x].extend([os.path.join(self.os_root, y) for y in get_proj_env_value('liteos_inc_path', module)])

    def get_module_cfg(self, module, env_name, fixed=False):
        if env_name != 'CPPPATH':
            return get_proj_env_value(flag[env_name], module)
        else:
            cfg_list = []
            inc_path = get_proj_env_value('common_inc_path', module)
            if inc_path is not None:
                for x in inc_path:
                    if x.startswith('#'):
                        cfg_list.append(x[2:])
                    else:
                        cfg_list.append(x)
            if get_proj_env_value('liteos_inc_path', module) is not None:
                cfg_list.extend([os.path.join(os.path.relpath(self.os_root, self.root), y) for y in get_proj_env_value('liteos_inc_path', module)])
            return cfg_list

    def get_module_dir(self, module):
        """
        Get module folder.
        """
        if module in module_dir:
            return '%s'%(module_dir[module])
        else:
            print('PROJECT HAS NO MODULE NAMED [%s]'%module)
            sys.exit(1)

    def get_all_modules(self):
        module_names = list(module_dir.keys())
        return module_names

    def get_module_libs(self, module, lib_name_only=False):
        """
        Get build module library settings
        """
        if module in proj_lib_cfg:
            if lib_name_only == True:
                return [lib_name for lib_name in proj_lib_cfg[module]]
            else:
                return proj_lib_cfg[module]
        else:
            print('PROJECT HAS NO MODULE NAMED [%s]'%module)
            sys.exit(1)

    def get_build_modules(self):
        """
        Get default build modules
        """
        return compile_module

    def get_bootlib_path(self):
        """
        Get boot library path to be inclouded.
        """
        lib_paths = os_boot_path
        return list(map(lambda x:'-L%s'%x, lib_paths))

    def get_lib_path(self):
        """
        Get library path to be inclouded.
        """
        lib_paths = os_lib_path
        gcc = '%sgcc'%self.tools_prefix
        gcc_lib_path = ''
        # found and include libgcc.a
        env_path_param = os.environ['PATH'].split(':')
        for param in env_path_param:
            if (param.find('gcc_riscv32') >= 0) and (param.endswith('bin') == True):
                compiler = os.path.join(param, 'riscv32-unknown-elf-gcc')
                if os.path.isfile(compiler) == True: #make sure the dir is accessable
                    gcc_lib_path = param
                    break

        gcc_lib_path = os.path.join(gcc_lib_path, '..', 'lib', 'gcc', 'riscv32-unknown-elf', self.gcc_ver_num)
        lib_paths.append(gcc_lib_path)
        lib_paths.extend([os.path.join(self.lib_path, self.get_module_dir(module)) for module in self.get_build_modules()])
        lib_paths.append(self.link_path)
        return list(map(lambda x:'-L%s'%x, lib_paths))

    def get_boot_libs(self):
        """
        Get library name to be inclouded. Linker option -l follows the lib name without
        prefix "lib" and surffix ".a", has to remove those parts from a library file name.
        """
        libs = [lib[3:-2] for lib in os.listdir(os.path.join(self.root, 'build', 'libs', 'boot_libs')) if lib.startswith('lib') and lib.endswith('.a')]
        return libs

    def get_libs(self):
        """
        Get library name to be inclouded. Linker option -l follows the lib name without
        prefix "lib" and surffix ".a", has to remove those parts from a library file name.
        """
        libs = [lib[3:-2] for lib in os.listdir(os.path.join(self.root, 'build', 'libs')) if lib.startswith('lib') and lib.endswith('.a')]
        libs.append('gcc')
        for module_lib in [self.get_module_libs(module, True) for module in self.get_build_modules()]:
            libs.extend(module_lib)
        if scons_usr_bool_option('CONFIG_I2S_SUPPORT') == 'n':
            libs.remove('i2s')
        if scons_usr_bool_option('CONFIG_HILINK') == 'y':
            libs.extend(['hilinkdevicesdk', 'hilinkota'])
        return libs

    def get_ohos_libs(self):
        """
        Get library name to be inclouded. Linker option -l follows the lib name without
        prefix "lib" and surffix ".a", has to remove those parts from a library file name.
        """
        libs = [lib[3:-2] for lib in os.listdir(os.path.join(self.root, 'ohos', 'libs')) \
                if lib.startswith('lib') and lib.endswith('.a')]
        return libs

    def del_tmp_files(self, file_path):
        if os.path.isfile(file_path):
            os.unlink(file_path)

    def base_bin_check(self, target):
        """
        Check the output base bin everytime to make sure the binary would not break the core.
        """
        sha256sum = ''
        with open (target, "rb") as base_bin:
            bytes = base_bin.read()
            sha256sum = hashlib.sha256(bytes).hexdigest()
        #self.del_tmp_files(target)
        if self.base_sum == sha256sum:
            return None
        raise SconsBuildError("%s============== BASE BIN IS DIFFERENT WITH FIRST COMPILE! =============%s" %
            (colors['red'], colors['end']))

    def set_clean_items(self, items):
        """
        Hook the clean items. Items would be deleted with "scons -c".
        """
        if items is None:
            return
        if isinstance(items, list):
            self.clean_list.extend(items)
            return
        if isinstance(items, str):
            self.clean_list.append(items)
            return
        raise SconsBuildError("%s============== PLEASE INPUT A LIST OR A STRING! =============%s" %
            (colors['red'], colors['end']))

    def set_app_builder(self, builder):
        """
        For new app.
        """
        self.app_builder = builder
        self.app_builder.read_env()
        self.app_param_update(builder.get_app_name())

    def app_param_update(self, app_name):
        """
        Get settings for the new app.
        """
        self.app_name = app_name
        self.target_name = '%s_%s'%((self.chip_type), self.app_name)
        self.map_file = os.path.join(self.bin_path, '%s_%s.map'%((self.chip_type), self.app_name))

        self.nv_src_path = os.path.join('app', app_name, 'nv')
        self.nv_factory_name = '%s_%s_factory.hnv'%((self.chip_type), app_name)
        self.nv_normal_name = '%s_%s_normal.hnv'%((self.chip_type), app_name)

        if self.app_builder:
            items = self.app_builder.get_app_cfg('CLEAN')
            self.set_clean_items(items)
            self.set_clean_items([os.path.join("tools", "nvtool", "out_nv_bin"),
                                  os.path.join("tools", "nvtool", "__pycache__")])

    def get_makefile_environs(self, module = 'common'):
        makefile_environs = {
            'var' : {
                'RM':'rm -rf',
                'MAKE':'make',
                'MV':'mv',
                'MAKE_DIR':'mkdir -p',

                # set compiler
                'CC':'$(TOOLS_PREFIX)gcc',
                'AR':'$(TOOLS_PREFIX)ar',
                'AS':'$(TOOLS_PREFIX)as',
                'CXX':'$(TOOLS_PREFIX)cpp',
                'LINK':'$(TOOLS_PREFIX)ld',
                'RANLIB':'$(TOOLS_PREFIX)ranlib',
                'OBJCOPY':'$(TOOLS_PREFIX)objcopy',
                'OBJDUMP':'$(TOOLS_PREFIX)objdump',
                'NV_CFG_NAME':self.nv_cfg_name,
                'BASE_NUM':   self.base_sum,
                'LOG_PATH':   self.log_path,
                'OBJ_PATH':   self.obj_path,
                'LIB_PATH':   self.lib_path,
                'CACHE_PATH': self.cache_path,
                'LINK_PATH':  self.link_path,
                'NV_PATH':    self.nv_path
            },
            'append_var' : {
                'LIBPATH':'-L%s -L%s'%(' -L'.join(os_lib_path), self.link_path),
                #'LIBS':'-l%s'%(' -l'.join(self.get_libs())),
                'LIBS':'-l%s'%(' -l'.join(['wifi', 'wifi_flash', 'system', 'litekernel_flash', 'gcc'])),
            },
            'mod_dir': {
            }
        }

        for mod in module_dir:
            makefile_environs['mod_dir']['%s_dir'%mod] = module_dir[mod]
        print('-'*50,'\n',makefile_environs)
        # Set input/output folders
        '''
        for flg in flag:
            flg_cfg = self.get_module_cfg(module, flg, fixed=True)
            if flg_cfg is None:
                continue
            makefile_environs[flg] = flg_cfg
        '''
        return makefile_environs
