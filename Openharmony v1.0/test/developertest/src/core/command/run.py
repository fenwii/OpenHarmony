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
import sys
from core.constants import SchedulerType
from xdevice import Plugin
from xdevice import get_plugin
from xdevice import platform_logger
from core.command.parameter import Parameter
from core.testcase.testcase_manager import TestCaseManager
from core.config.config_manager import UserConfigManager


class Run(object):
    run_log = platform_logger("Run")

    def process_command_run(self, command, options):
        para = Parameter()
        test_type_list = para.get_testtype_list(options.testtype)
        if len(test_type_list) == 0:
            self.run_log.error("The testtype parameter is incorrect.")
            return
        options.testtype = test_type_list

        self.run_log.info("")
        self.run_log.info("------------------------------------")
        self.run_log.info("Input parameter:")
        self.run_log.info("productform   = %s" % options.productform)
        self.run_log.info("testtype      = %s" % options.testtype)
        self.run_log.info("subsystem     = %s" % options.subsystem)
        self.run_log.info("testmodule    = %s" % options.testmodule)
        self.run_log.info("testsuit      = %s" % options.testsuit)
        self.run_log.info("testcase      = %s" % options.testcase)
        self.run_log.info("testlevel     = %s" % options.testlevel)
        self.run_log.info("------------------------------------")
        self.run_log.info("")

        if not para.check_run_parameter(options):
            self.run_log.error("Input parameter is incorrect.")
            return

        if not self._build_test_cases(options):
            self.run_log.error("Build test cases failed.")
            return

        test_case_path = self._get_tests_out_path(
            options.productform, options.build_variant)
        if not os.path.exists(test_case_path):
            self.run_log.error("%s is not exist." % test_case_path)
            return

        test_dictionary = TestCaseManager().get_test_files(test_case_path,
                                                           options)
        if not self._check_test_dictionary(test_dictionary):
            self.run_log.error("The test file list is empty.")
            return

        setattr(options, "testdriver", "LiteUnitTest")
        options.testdict = test_dictionary
        options.target_outpath = self.get_target_out_path(
            options.productform, options.build_variant)

        scheduler = get_plugin(plugin_type=Plugin.SCHEDULER,
                               plugin_id=SchedulerType.SCHEDULER)[0]
        if scheduler is None:
            self.run_log.error("Can not find the scheduler plugin.")
        else:
            scheduler.exec_command(command, options)

        return

    ##############################################################
    ##############################################################

    @classmethod
    def get_target_out_path(cls, product_form, build_variant):
        target_out_path = UserConfigManager().get_user_config(
            "test_cases").get("dir", "")
        if target_out_path == "":
            target_out_path = os.path.join(
                sys.source_code_root_path,
                "out",
                build_variant,
                "packages",
                product_form)
        target_out_path = os.path.abspath(target_out_path)
        return target_out_path

    def _build_test_cases(self, options):
        if options.coverage == "coverage":
            self.run_log.info("Coverage testing, no need to compile testcases")
            return True

        project_root_path = sys.source_code_root_path
        if "testcase" in options.build and project_root_path != "":
            from core.build.build_manager import BuildManager
            build_manager = BuildManager()
            return build_manager.build_testcases(project_root_path, options)
        else:
            return True

    @classmethod
    def _check_test_dictionary(cls, test_dictionary):
        is_valid_status = False
        key_list = sorted(test_dictionary.keys())
        for key in key_list:
            file_list = test_dictionary[key]
            if len(file_list) > 0:
                is_valid_status = True
                break
        return is_valid_status

    @classmethod
    def _get_tests_out_path(cls, product_form, build_variant):
        tests_out_path = UserConfigManager().get_user_config(
            "test_cases").get("dir")
        if tests_out_path == "":
            tests_out_path = os.path.abspath(os.path.join(
                sys.source_code_root_path,
                "out",
                build_variant,
                "packages",
                product_form,
                "tests"))
        return tests_out_path
