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
from inspect import getsourcefile

__all__ = ["usr_cfg_main", "sys_cfg_main"]

class UsrCfgParserError(Exception):
    """
    Parser exception
    """
    pass

class Translator:
    def __init__(self):
        '''
        Insert MARCOS if there are different.
        '''
        self.marco_table = {
        }
        pass

    def translate(self, key):
        if key in self.marco_table.keys():
            return self.marco_table[key]
        return key

class UsrCfgParser:
    """
    Read menuconfig settings.
    """
    def __init__(self):
        #print('execute with exe...') if getattr(sys, 'frozen', False) else print('execute with python...')
        self.config_file = self.get_default_config_file()
        #print('config file:',self.config_file)
        if os.path.exists(self.config_file) is False:
            raise UsrCfgParserError("Config file not found! Please execute 'python usr_config.py' first!")
        self.translate = Translator()

    def local_main(self):
        pass

    def get_default_config_file(self):
        if getattr(sys, 'frozen', False):
            dir_path = os.path.dirname(os.path.dirname(os.path.realpath(getsourcefile(self.local_main))))
            return os.path.join(dir_path, 'config', 'usr_config.mk')
        else:
            return os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'config', 'usr_config.mk')

    def do_parse(self):
        cfg_options = {}
        if self.config_file is None:
            raise UsrCfgParserError("Config file not found! Please execute \'python usr_config.py\' first!")
        with open(self.config_file, 'r') as cfg:
            for option in cfg.readlines():
                option = option.strip()
                if self.cfg_is_valid(option) is True:
                    marco, value = self.parse_option(option)
                    marco = self.translate.translate(marco)
                    cfg_options[marco.strip()] = value.strip()
        return cfg_options

    def cfg_is_valid(self, option):
        if option is None:
            return False
        if option is '':
            return False
        if option.startswith('#') is True:
            return False
        if option.find('HiSilicon menuconfig tool') > 0:
            return False
        if option.find('#', 1) >= 0:
            raise UsrCfgParserError("Unknown format! Please execute \'python usr_config.py\' first!")
        return True

    def parse_option(self, option):
        cfg = option.split('=')
        if len(cfg) == 2: #Just one setting
            return cfg[0], cfg[1]
        else:
            raise UsrCfgParserError("Unknown format! Please execute \'python usr_config.py\' first!")

def usr_cfg_main():
    return UsrCfgParser().do_parse()

class SysCfgParser(UsrCfgParser):
    """
    Read system settings
    """
    def get_default_config_file(self):
        if getattr(sys, 'frozen', False):
            dir_path = os.path.dirname(os.path.dirname(os.path.realpath(getsourcefile(self.local_main))))
            return os.path.join(dir_path, 'config', 'sdk.mk')
        else:
            return os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'config', 'sdk.mk')

def sys_cfg_main():
    return SysCfgParser().do_parse()

