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
* Description: APP utilities
'''

import os
import json
from scripts.common_env import insert_module
from scripts.common_env import insert_module_dir
from scripts.common_env import insert_lib_cfg
from scripts.common_env import insert_env_defs
from scripts.common_env import insert_os_include
from scripts.common_env import insert_common_include
from scripts.common_env import insert_ar_flags
from scripts.common_env import insert_as_flags
from scripts.common_env import insert_ld_flags
from scripts.common_env import insert_cc_flags
from scripts.common_env import set_factory_mode
from scons_utils import colors

__all__ = ["AppTarget"]

class AppBuildError(Exception):
    """
    Build exception.
    """
    pass

class AppTarget:
    """
    APP config
    """
    def __init__(self, app_name, factory_mode):
        self.app_name = app_name
        self.factory_mode = factory_mode
        self.app_env = None
        self.app_cfg_file = None
        self.proj_root = os.path.realpath(os.path.join(__file__, '..', '..', '..'))
        self.app_root = self.app_lookup()
        self.settings = {}
        self.app_ld_dirs = []

    def app_lookup(self):
        """
        Found app folder.
        """
        dirs = os.listdir(os.path.join(self.proj_root, 'app'))
        if self.app_name in dirs:
            return os.path.join('app', self.app_name)
        raise AppBuildError("%s============== Can NOT found the APP project --- %s! =============%s" %
            (colors['red'], self.app_name, colors['end']))

    def read_env(self):
        """
        Parse app settings
        """
        if self.app_pre_check() is False:
            return;
        try:
            with open(self.app_cfg_file) as app_cfg:
                self.settings = json.load(app_cfg)
        except Exception as e:
            raise AppBuildError("%s============== Read APP settings error: %s! =============%s" %
                (colors['red'], e, colors['end']))

        self.app_env_parse(self.settings)
        pass

    def get_app_libs(self):
        """
        Parse app libraries
        """
        libs = []
        for folder in self.app_ld_dirs:
            libs.extend([lib[3:-2] for lib in os.listdir(folder) if lib.startswith('lib') and lib.endswith('.a')])
        return list(map(lambda x:'-l%s'%x, libs))

    def get_app_lib_path(self):
        """
        Parse app library path
        """
        if len(self.app_ld_dirs) > 0:
            return list(map(lambda x:'-L%s'%x, self.app_ld_dirs))
        return []

    def get_app_name(self):
        return self.app_name

    def get_app_cfg(self, key):
        return self.settings.get(key, None)

    def app_pre_check(self):
        app_scons = os.path.join(self.proj_root, self.app_root, 'SConscript')
        if os.path.isfile(app_scons) == False:
            raise AppBuildError("%s============== Can NOT found the APP %s! =============%s" %
                (colors['red'], app_scons, colors['end']))
        self.app_cfg_file = os.path.join(self.proj_root, self.app_root, 'app.json')
        if os.path.isfile(self.app_cfg_file) == False:
            raise AppBuildError("%s============== Can NOT found the APP %s! =============%s" %
                (colors['red'], self.app_cfg_file, colors['end']))
        return True

    def app_env_parse(self, settings):
        try:
            insert_module(self.app_name)
            insert_module_dir(self.app_name, self.app_root)
            insert_lib_cfg(self.app_name, {settings["TARGET_LIB"] : settings["APP_SRCS"]})

            if settings.get("DEFINES") is not None:
                insert_env_defs(self.app_name, settings["DEFINES"])

            if settings.get("OS_INCLUDE") is not None:
                insert_os_include(self.app_name, settings["OS_INCLUDE"])
            if settings.get("INCLUDE") is not None:
                incs = []
                for inc in settings["INCLUDE"]:
                    incs.append(os.path.join('#', inc));
                insert_common_include(self.app_name, incs)

            if settings.get("LD_DIRS") is not None:
                self.app_ld_dirs.extend(settings.get("LD_DIRS"))
            if settings.get("AR_FLAGS") is not None:
                insert_ar_flags(self.app_name, settings["AR_FLAGS"])
            if settings.get("LD_FLAGS") is not None:
                insert_ld_flags(self.app_name, settings["LD_FLAGS"])
            if settings.get("CC_FLAGS") is not None:
                insert_cc_flags(self.app_name, settings["CC_FLAGS"])
            if settings.get("AS_FLAGS") is not None:
                insert_as_flags(self.app_name, settings["AS_FLAGS"])
            if self.factory_mode == 'yes':
                set_factory_mode()
        except Exception as e:
            raise AppBuildError("%s============== APP settings error: %s! =============%s" %
                (colors['red'], e, colors['end']))

"""
for test only
"""
def test():
    app_obj = AppTarget('demo')
    app_obj.read_env()

if __name__ == '__main__':
    test()

