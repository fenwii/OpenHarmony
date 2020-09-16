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

from core.constants import DeviceOsType
from xdevice import platform_logger
from core.build.filter_targets import FilterTargets
from core.build.build_testcases import BuildTestcases
from core.build.build_lite_manager import BuildLiteManager


##############################################################################
##############################################################################

class BuildManager(object):
    def __init__(self):
        self.log = platform_logger("BuildManager")

    def _make_gn_file(self, filepath, target_list):
        self.log.info("The gn file path: %s" % filepath)
        with open(filepath, "w") as gn_file:
            gn_file.write("group(\"make_temp_test\") {\n")
            gn_file.write("  testonly = true\n")
            gn_file.write("  deps = []\n")
            if target_list:
                gn_file.write("  deps += [\n")
                for target in target_list:
                    gn_file.write("    \"%s\",\n" % target)
                gn_file.write("  ]\n")
            gn_file.write("}\n")

    def _compile_test_cases_by_target(self, project_root_path, product_form,
                                      build_target):
        if BuildTestcases(project_root_path).build_testcases(product_form,
                                                             build_target):
            self.log.info("Test case compilation succeed.")
            build_result = True
        else:
            self.log.info("Test case compilation failed, please modify.")
            build_result = False
        return build_result

    def _compile_testcases(self, project_rootpath, para):
        if para.target_os_name == DeviceOsType.DEFAULT_OS:
            build_lite_manager = BuildLiteManager()
            return build_lite_manager.exec_build_test(para)
        if para.testsuit != "":
            return self._compile_test_cases_by_target(
                project_rootpath,
                para.productform,
                para.testsuit)

        if (para.subsystem == "" and para.testmodule == "" and
                "ALL" in para.testtype):
            return self._compile_test_cases_by_target(
                project_rootpath,
                para.productform,
                "make_test")

        target_list = FilterTargets(
            project_rootpath).filter_build_targets(para)
        if len(target_list) == 0:
            self.log.warning("No build target found.")
            return False

        build_cfg_filepath = os.path.join(project_rootpath,
                                          "test",
                                          "developer_test_runner",
                                          "BUILD.gn")

        self._make_gn_file(build_cfg_filepath, target_list)
        build_result = self._compile_test_cases_by_target(
            project_rootpath,
            para.productform,
            "make_temp_test")
        self._make_gn_file(build_cfg_filepath, [])

        return build_result

    def build_version(self, project_root_path, product_form):
        if BuildTestcases(project_root_path).build_version(product_form):
            self.log.info("The version compiled successfully.")
            build_result = True
        else:
            self.log.info("The version compilation failed, please modify.")
            build_result = False
        return build_result

    def build_gn_file(self, project_root_path, product_form):
        if BuildTestcases(project_root_path).build_gn_file(product_form):
            self.log.info("The gn compiled successfully.")
            build_result = True
        else:
            self.log.info("The gn compilation failed, please modify.")
            build_result = False
        return build_result

    def build_testcases(self, project_root_path, param):
        if not os.path.exists(project_root_path):
            self.log.error("%s is not exists." % project_root_path)
            return False

        self.log.info("--------------------------------------------------")
        self.log.info("Building parameter:")
        self.log.info("productform   = %s" % param.productform)
        self.log.info("testtype      = %s" % str(param.testtype))
        self.log.info("testpart      = %s" % param.subsystem)
        self.log.info("testmodule    = %s" % param.testmodule)
        self.log.info("testsuit      = %s" % param.testsuit)
        self.log.info("--------------------------------------------------")

        self.log.info("")
        self.log.info("**************************************************")
        self.log.info("*************** Start build testcases ************")
        self.log.info("**************************************************")
        self.log.info("")

        build_result = self._compile_testcases(project_root_path, param)

        self.log.info("")
        self.log.info("**************************************************")
        self.log.info("*************** Ended build testcases ************")
        self.log.info("**************************************************")
        self.log.info("")

        return build_result

##############################################################################
##############################################################################
