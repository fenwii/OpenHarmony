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
import json
from string import Template

from .hdf_command_handler_base import HdfCommandHandlerBase
from .hdf_command_error_code import CommandErrorCode
from .hdf_vendor_kconfig_file import HdfVendorKconfigFile
from .hdf_vendor_mk_file import HdfVendorMkFile
from .hdf_module_kconfig_file import HdfModuleKconfigFile
from .hdf_module_mk_file import HdfModuleMkFile
from .hdf_driver_config_file import HdfDriverConfigFile
from hdf_tool_settings import HdfToolSettings
from hdf_tool_exception import HdfToolException
import hdf_utils


class HdfAddHandler(HdfCommandHandlerBase):
    def __init__(self, args):
        super(HdfAddHandler, self).__init__()
        self.cmd = 'add'
        self.handlers = {
            'vendor': self._add_vendor_handler,
            'module': self._add_module_handler,
            'driver': self._add_driver_handler,
            'config': self._add_config_handler,
        }
        self.parser.add_argument("--action_type",
                                 help=' '.join(self.handlers.keys()),
                                 required=True)
        self.parser.add_argument("--root_dir", required=True)
        self.parser.add_argument("--vendor_name")
        self.parser.add_argument("--module_name")
        self.parser.add_argument("--driver_name")
        self.parser.add_argument("--board_name")
        self.args = self.parser.parse_args(args)

    @staticmethod
    def _render(template_path, output_path, data_model):
        if not os.path.exists(template_path):
            return
        raw_content = hdf_utils.read_file(template_path)
        contents = Template(raw_content).safe_substitute(data_model)
        hdf_utils.write_file(output_path, contents)

    def _file_gen_lite(self, template, out_dir, filename, model):
        templates_dir = hdf_utils.get_templates_lite_dir()
        template_path = os.path.join(templates_dir, template)
        file_path = os.path.join(out_dir, filename)
        self._render(template_path, file_path, model)

    def _add_vendor_handler(self):
        self.check_arg_raise_if_not_exist("vendor_name")
        root, vendor, _, _, board = self.get_args()
        target_dir = hdf_utils.get_vendor_hdf_dir(root, vendor)
        if os.path.exists(target_dir):
            raise HdfToolException("%s already exists" % target_dir,
                                   CommandErrorCode.TARGET_ALREADY_EXIST)
        os.makedirs(target_dir)
        self._file_gen_lite('hdf_vendor_kconfig.template', target_dir,
                            'Kconfig', {})
        board_parent_path = HdfToolSettings().get_board_parent_path(board)
        if not board_parent_path:
            board_parent_path = 'vendor/hisi/hi35xx'
        data_model = {
            "board_parent_path": board_parent_path
        }
        self._file_gen_lite('hdf_vendor_mk.template', target_dir,
                            'hdf_vendor.mk', data_model)

    def _add_module_handler(self):
        self.check_arg_raise_if_not_exist("vendor_name")
        self.check_arg_raise_if_not_exist("module_name")
        root, vendor, module, _, _ = self.get_args()
        converter = hdf_utils.WordsConverter(self.args.module_name)
        hdf = hdf_utils.get_vendor_hdf_dir(root, vendor)
        if not os.path.exists(hdf):
            raise HdfToolException('vendor "%s" not exist' % vendor,
                                   CommandErrorCode.TARGET_NOT_EXIST)
        drv_root_dir = hdf_utils.get_drv_root_dir(root, vendor, module)
        if os.path.exists(drv_root_dir):
            raise HdfToolException('module "%s" already exist' % module,
                                   CommandErrorCode.TARGET_ALREADY_EXIST)
        os.makedirs(drv_root_dir)
        hdi_dir = os.path.join(hdf, module, 'hdi')
        if not os.path.exists(hdi_dir):
            os.makedirs(hdi_dir)
        data_model = {
            "module_upper_case": converter.upper_case(),
            "module_lower_case": converter.lower_case()
        }
        self._file_gen_lite('hdf_module_kconfig.template', drv_root_dir,
                            'Kconfig', data_model)
        self._file_gen_lite('hdf_module_mk.template', drv_root_dir,
                            'Makefile', data_model)
        vendor_k = HdfVendorKconfigFile(root, vendor)
        vendor_k.add_module([module, 'driver', 'Kconfig'])
        vendor_mk = HdfVendorMkFile(root, vendor)
        vendor_mk.add_module(module)
        config_item = {
            'name': module,
            'config_item': 'DRIVERS_HDF_%s' % converter.upper_case(),
            'depends_on_item': 'DRIVERS_HDF',
            'enabled': False
        }
        return json.dumps(config_item)

    def _add_driver_handler(self):
        self.check_arg_raise_if_not_exist("vendor_name")
        self.check_arg_raise_if_not_exist("module_name")
        self.check_arg_raise_if_not_exist("driver_name")
        self.check_arg_raise_if_not_exist("board_name")
        root, vendor, module, driver, board = self.get_args()
        drv_converter = hdf_utils.WordsConverter(self.args.driver_name)
        drv_config = HdfDriverConfigFile(root, board, module, driver)
        module_k = \
            hdf_utils.get_module_kconfig_path(root, vendor, module)
        if not os.path.exists(module_k):
            raise HdfToolException('module "%s Kconfig" not exist' % module,
                                   CommandErrorCode.TARGET_NOT_EXIST)
        module_mk = \
            hdf_utils.get_module_mk_path(root, vendor, module)
        if not os.path.exists(module_mk):
            raise HdfToolException('module "%s Makefile" not exist' % module,
                                   CommandErrorCode.TARGET_NOT_EXIST)
        drv_src_dir = hdf_utils.get_drv_src_dir(root, vendor, module, driver)
        if os.path.exists(drv_src_dir):
            raise HdfToolException('driver "%s" already exist' % driver,
                                   CommandErrorCode.TARGET_ALREADY_EXIST)
        os.makedirs(drv_src_dir)
        drv_include_dir = \
            hdf_utils.get_drv_include_dir(root, vendor, module, driver)
        if not os.path.exists(drv_include_dir):
            os.makedirs(drv_include_dir)
        data_model = {
            'driver_lower_case': drv_converter.lower_case(),
            'driver_upper_camel_case': drv_converter.upper_camel_case(),
            'driver_lower_camel_case': drv_converter.lower_camel_case(),
            'driver_upper_case': drv_converter.upper_case()
        }
        self._file_gen_lite('hdf_driver.c.template', drv_src_dir,
                            '%s_driver.c' % driver, data_model)
        self._file_gen_lite('hdf_driver.h.template', drv_include_dir,
                            '%s_driver.h' % driver, data_model)
        k_path = hdf_utils.get_module_kconfig_path(root, vendor, module)
        module_config = HdfModuleKconfigFile(root, module, k_path)
        config = module_config.add_driver(driver)
        module_mk = HdfModuleMkFile(root, vendor, module)
        module_mk.add_driver(driver)
        drv_config.create_driver()
        return json.dumps(config)

    def _add_config_handler(self):
        self.check_arg_raise_if_not_exist("module_name")
        self.check_arg_raise_if_not_exist("driver_name")
        self.check_arg_raise_if_not_exist("board_name")
        root, _, module, driver, board = self.get_args()
        drv_config = HdfDriverConfigFile(root, board, module, driver)
        drv_config.create_driver()
        return drv_config.get_drv_config_path()
