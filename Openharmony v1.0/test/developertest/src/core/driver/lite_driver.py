#!/usr/bin/env python3
# coding=utf-8

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
import shutil

from xdevice import DeviceTestType
from xdevice import IDriver
from xdevice import Plugin
from xdevice import platform_logger

from core.config.config_manager import UserConfigManager

__all__ = ["LiteUnitTest"]


@Plugin(type=Plugin.DRIVER, id=DeviceTestType.lite_cpp_test)
class LiteUnitTest(IDriver):
    """
    lite gtest test driver for L1
    """
    config = None
    log = platform_logger("LiteUnitTest")
    nfs_dir = ""
    lite_device = None
    result = None

    @classmethod
    def __check_failed__(cls, msg):
        cls.log.error("check failed {}".format(msg))
        return None

    @classmethod
    def __check_environment__(cls, device_options):
        pass

    @classmethod
    def __check_config__(cls, config):
        """
        1. check serial protocol
        2. login device
        3. NFS is available
        :param config:包含serial_protocol，serial_device，nfs_operation
        :return:
        """
        cls.log.error("Lite driver check config:{}".format(config))

    @classmethod
    def __execute__(cls, request):
        """

        1. select test case by subsystem, module, suite
        2. open test dir
        3、execute single test case, eg. ./test_demo
        :param request: contains test condition, sub_system
            module_name，test_suit，
        test_case，test_level，test_case_dir
        :return:
        """
        cls.log.debug("Test suite FilePath: %s" %
                      request.root.source.source_file)
        cls.lite_device = request.config.environment.devices[0]
        cls.lite_device.connect()
        if not cls._before_execute_test():
            cls.log.error("open test dir failed")
            return
        cls.log.debug("open test dir success")
        if cls._execute_test(request) == "":
            cls.log.error("execute test command failed")
            return
        cls.log.info("execute test command success")
        if not cls._after_execute_test(request):
            cls.log.error("after execute test failed")
            return
        cls.log.info("lite device execute request success")

    @classmethod
    def _before_execute_test(cls):
        """
        need copy test case to nfs dir
        :param request: nfs dir, test case path
        :return:
        """
        cls.nfs_dir = \
            UserConfigManager().get_user_config("NFS").get("host_dir")
        if cls.nfs_dir == "":
            cls.log.error("no configure for nfs directory")
            return False
        pre_result, status, _ = \
            cls.lite_device.execute_command_with_timeout("cd /{}".format(
                UserConfigManager().get_user_config("NFS").get("board_dir")),
            case_type=DeviceTestType.lite_cpp_test)
        if not status:
            cls.log.error("pre execute command failed")
            return False
        cls.log.info("pre execute command success")
        return True

    @classmethod
    def _execute_test(cls, request):
        test_cases = request.config.testdict['BIN']
        cxx_test_cases = request.config.testdict['CXX']
        test_cases += cxx_test_cases
        for test_case in test_cases:
            case_name = os.path.basename(test_case)
            shutil.copyfile(test_case, os.path.join(cls.nfs_dir, case_name))
            case_result, status, _ = \
                cls.lite_device.execute_command_with_timeout(
                "./" + case_name, case_type=DeviceTestType.lite_cpp_test)
            if status:
                cls.log.info("test case result:\n %s" % case_result)
                continue
            cls.log.error("failed case: %s" % test_case)

    @classmethod
    def _after_execute_test(cls, request):
        """
        copy test result to result dir
        :param request:
        :return:
        """
        if request.config is None:
            cls.log.error("test config is null")
            return False
        report_path = request.config.report_path
        test_result = os.path.join(report_path, "result")
        test_cases = request.config.testdict['BIN']
        for test_case in test_cases:
            case_name = os.path.basename(test_case)
            result_name = case_name + ".xml"
            result_file = os.path.join(cls.nfs_dir, result_name)
            if not os.path.exists(result_file):
                cls.log.error("file %s not exist." % result_file)
                continue
            file_name = os.path.basename(result_file)
            if not os.path.exists(test_result):
                os.mkdir(test_result)
            final_result = os.path.join(test_result, file_name)
            shutil.copyfile(result_file,
                            final_result)
        cls.log.info("after execute test")
        cls.lite_device.close()
        return True

    @classmethod
    def show_help_info(cls):
        """
        show help info.
        """
        cls.log.info("this is test driver for cpp test")
        return None

    @classmethod
    def show_driver_info(cls):
        """
        show driver info.
        """
        cls.log.info("this is test driver for cpp test")
        return None

    @classmethod
    def __result__(cls):
        pass
