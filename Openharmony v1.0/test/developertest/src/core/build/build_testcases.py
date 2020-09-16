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
import json
import shutil
import subprocess
import platform
from xdevice import platform_logger
from core.config.config_manager import UserConfigManager

BUILD_FILEPATH = "./build.sh"
DEFAULT_TARGET_OS = "OHOS"


##############################################################################
##############################################################################

class BuildTestcases(object):
    def __init__(self, project_rootpath):
        self.log = platform_logger("BuildTestcases")
        self.project_rootpath = project_rootpath
        self.is_doublefwk = UserConfigManager().get_user_config_flag(
            "common", "doublefwk")
        self.is_build_example = UserConfigManager().get_user_config_flag(
            "build", "example")

    def _copy_folder(self, source_dir, target_dir):
        if not os.path.exists(target_dir):
            os.makedirs(target_dir)

        if platform.system() == 'Windows':
            command = ["xcopy", "/f", "/s", "/e", "/y",
                       "/b", "/q", source_dir, target_dir]
        else:
            command = ["cp", "-rf", source_dir, target_dir]

        self.log.info("command: %s" % str(command))
        return subprocess.call(command) == 0

    def _get_testcase_outname_by_productform(self, productform):
        if productform == "phone":
            return ""

        testcase_outpath = ""
        toolchain_filepath = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            "build_configs",
            "platforms_info",
            "toolchain_to_variant.json")
        if os.path.exists(toolchain_filepath):
            data_dic = []
            with open(toolchain_filepath, 'r') as toolchain_file:
                data_dic = json.load(toolchain_file)
                if not data_dic:
                    self.log.warning("The %s file load error." %
                                     toolchain_filepath)
                    data_dic = []
            paltform_toolchain_dic = data_dic.get("paltform_toolchain")
            testcase_outpath = paltform_toolchain_dic.get(productform, "")
            pos = testcase_outpath.rfind(':') + 1
            testcase_outpath = testcase_outpath[pos:len(testcase_outpath)]
        return testcase_outpath

    def _delete_testcase_dir(self, productform):
        package_out_dir = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            "packages",
            productform, "tests")
        self.log.info("package_out_dir=%s" % package_out_dir)
        if os.path.exists(package_out_dir):
            shutil.rmtree(package_out_dir)

        phone_out_dir = os.path.join(
            self.project_rootpath, "out", "release", "tests")
        self.log.info("phone_out_dir=%s" % phone_out_dir)
        if os.path.exists(phone_out_dir):
            shutil.rmtree(phone_out_dir)

        curr_productform_outname = self._get_testcase_outname_by_productform(
            productform)
        if curr_productform_outname == "":
            return

        curr_productform_outdir = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            curr_productform_outname,
            "tests")
        self.log.info("curr_productform_outdir=%s" % curr_productform_outdir)
        if os.path.exists(curr_productform_outdir):
            shutil.rmtree(curr_productform_outdir)

    def _merge_testcase_dir(self, productform):
        package_out_dir = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            "packages",
            productform)
        if platform.system() == 'Windows':
            package_out_dir = os.path.join(package_out_dir, "tests")

        phone_out_dir = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            "tests")
        if os.path.exists(phone_out_dir):
            self._copy_folder(phone_out_dir, package_out_dir)

        curr_productform_outname = self._get_testcase_outname_by_productform(
            productform)
        if curr_productform_outname == "":
            return

        curr_productform_outdir = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            curr_productform_outname,
            "tests")
        self.log.info("curr_productform_outdir=%s" % curr_productform_outdir)
        if os.path.exists(curr_productform_outdir):
            self._copy_folder(curr_productform_outdir, package_out_dir)

    def _execute_build_command(self, command):
        build_result = False
        current_path = os.getcwd()
        os.chdir(self.project_rootpath)

        if os.path.exists(BUILD_FILEPATH):
            build_command = [BUILD_FILEPATH]
            build_command.extend(command)
            self.log.info("build_command: %s" % str(build_command))
            if subprocess.call(build_command) == 0:
                build_result = True
            else:
                build_result = False
        else:
            self.log.warning("Error: The %s is not exist" % BUILD_FILEPATH)

        os.chdir(current_path)
        return build_result

    def build_testcases(self, productform, target,
        target_os=DEFAULT_TARGET_OS):
        command = []
        command.append("target_os=" + target_os)
        command.append("target_platform=" + productform.lower())
        command.append("build_target=" + target)

        if self.is_build_example:
            command.append("build_example=true")

        if self.is_doublefwk:
            command.append("double_framework=true")

        self._delete_testcase_dir(productform)
        build_result = self._execute_build_command(command)
        self._merge_testcase_dir(productform)
        return build_result

    def build_gn_file(self, productform, target_os=DEFAULT_TARGET_OS):
        module_list_files_dir = os.path.join(
            self.project_rootpath, "out", "release", "module_list_files")
        if os.path.exists(module_list_files_dir):
            return True

        command = []
        command.append("target_os=" + target_os)
        command.append("target_platform=" + productform.lower())
        command.append("build_only_gn=true")

        if self.is_doublefwk:
            command.append("double_framework=true")

        return self._execute_build_command(command)

    def build_version(self, productform, target_os=DEFAULT_TARGET_OS):
        command = []
        command.append("target_os=" + target_os)
        command.append("target_platform=" + productform.lower())
        command.append("build_target=make_all")

        if self.is_doublefwk:
            command.append("double_framework=true")

        return self._execute_build_command(command)


##############################################################################
##############################################################################
