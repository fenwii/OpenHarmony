#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

import os
import distutils.spawn
from utils import exec_command
from utils import check_output
try:
    # Python3
    from configparser import ConfigParser
except ImportError:
    # Python2
    from ConfigParser import ConfigParser


class Config():
    def __init__(self, args):
        self.product = args.product[0]
        self.build_type = args.build_type[0]
        self.__set_path()
        self.config = os.path.join(self.get_build_path(), 'config.ini')
        self.log_path = os.path.join(self.get_out_path(), 'build.log')
        self.cfg = ConfigParser()
        self.cfg.read(self.config)
        self.args_list = []
        self.__test_cmd_check(args.test)
        self.__ndk_check(args.ndk)

    def __set_path(self):
        self.__root_path = os.getcwd()
        self.__build_path = os.path.join(self.__root_path, 'build', 'lite')
        if not os.path.exists(self.__build_path):
            raise Exception('Error: {} not exist, please check.'.format(
                            self.__build_path))
        self.__out_path = os.path.join(self.__root_path, 'out', self.product)

    def get_root_path(self):
        if self.__root_path is None:
            raise Exception('Error: set root_path first.')

        return self.__root_path

    def get_build_path(self):
        if self.__build_path is None:
            raise Exception('Error: set build_path first.')

        return self.__build_path

    def get_out_path(self):
        if self.__out_path is None:
            raise Exception('Error: set out_path first.')

        return self.__out_path

    def get_cmd(self, gn_path, ninja_path):
        if not os.path.exists(self.config):
            raise Exception('Error: {} not exist, please check.'.format(
                            self.config))
        return self.__parse_compile_config(gn_path, ninja_path)

    def __parse_compile_config(self, gn_path, ninja_path):
        self.cfg.set('env', 'build_path', self.get_build_path())
        self.cfg.set('env', 'out_path', self.get_out_path())
        self.cfg.set('env', 'gn_path', gn_path)
        self.cfg.set('env', 'ninja_path', ninja_path)
        self.cfg.set('env', 'gn_args', self.get_gn_args())
        return [self.cfg.get('env', 'gn_cmd'),
                self.cfg.get('env', 'ninja_cmd')]

    def __test_cmd_check(self, test_args):
        if test_args:
            cmd_list = ['xts']
            if test_args[0] in cmd_list:
                if len(test_args) > 1:
                    self.cfg.set('gn_args', 'test', test_args[1])
                    self.args_list.append(self.cfg.get('gn_args', 'test_args'))
            else:
                raise Exception('Error: wrong input of test')

    def __ndk_check(self, ndk):
        if ndk:
            self.args_list.append(self.cfg.get('gn_args', 'ndk_args'))

    def get_gn_args(self):
        self.cfg.set('gn_args', 'product', self.product)
        self.cfg.set('gn_args', 'build_type', self.build_type)
        self.args_list.append(self.cfg.get('gn_args', 'product_args'))
        self.args_list.append(self.cfg.get('gn_args', 'build_type_args'))
        return " ".join(self.args_list)


class Compile():
    compiler_path = None
    gn_path = None
    ninja_path = None
    sysroot_path = None

    def compile(self, config):
        cmd_list = config.get_cmd(self.gn_path, self.ninja_path)
        for cmd in cmd_list:
            exec_command(cmd, log_path=config.log_path, shell=True)

    @classmethod
    def get_tool_path(cls, config, json_content):
        compiler = json_content['compiler']

        if compiler == "clang":
            compiler_bin = "clang"
        elif compiler == "gcc":
            compiler_bin = "riscv32-unknown-elf-gcc"
        else:
            raise Exception('Error: Unsupport compiler {}.'.format(compiler))

        cls.compiler_path = distutils.spawn.find_executable(compiler_bin)
        if cls.compiler_path is None:
            compiler_cfg_path = config.cfg.get('ndk', '{}_path'
                                               .format(compiler_bin))
            if os.path.exists(compiler_cfg_path):
                cls.compiler_path = os.path.abspath(compiler_cfg_path)
            else:
                raise Exception('Error: Can\'t find compiler {}, '
                                'install it please.'.format(compiler_bin))
        cls.check_compiler(compiler, config)

        cls.gn_path = distutils.spawn.find_executable('gn')
        if cls.gn_path is None:
            gn_cfg_path = config.cfg.get('ndk', 'gn_path')
            if os.path.exists(gn_cfg_path):
                cls.gn_path = gn_cfg_path
            else:
                raise Exception('Error: Can\'t find gn, install it please.')

        cls.ninja_path = distutils.spawn.find_executable('ninja')
        if cls.ninja_path is None:
            ninja_cfg_path = config.cfg.get('ndk', 'ninja_path')
            if os.path.exists(ninja_cfg_path):
                cls.ninja_path = ninja_cfg_path
            else:
                raise Exception('Error: Can\'t find ninja, install it please.')

    @classmethod
    def check_compiler(cls, compiler, config):
        if compiler == 'gcc':
            return True

        cmd = [cls.compiler_path, '-v']
        ret = check_output(cmd)
        if 'OHOS' not in ret:
            raise Exception('Error: {} is not OHOS compiler, please install'
                            ' compiler.'.format(cls.compiler_path))

        compiler_path = os.path.join(os.path.dirname(cls.compiler_path),
                                     os.pardir)
        config.cfg.set('gn_args', 'compiler_path', compiler_path)
        config.args_list.append(config.cfg.get('gn_args', 'compiler_args'))

        return True
