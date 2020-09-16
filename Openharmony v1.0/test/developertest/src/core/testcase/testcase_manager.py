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
import copy
from core.utils import get_file_list_by_postfix
from core.config.config_manager import FilterConfigManager
from xdevice import platform_logger

TESTFILE_TYPE_DATA_DIC = {"DEX": [], "HAP": [], "PYT": [],
                          "CXX": [], "BIN": []}
FILTER_SUFFIX_NAME_LIST = [".TOC", ".info", ".pyc"]


class TestCaseManager(object):
    case_log = platform_logger("TestCaseManager")

    def get_test_files(self, test_case_path, options):
        self.case_log.info("test case path: " + test_case_path)
        self.case_log.info("test type list: " + str(options.testtype))
        suit_file_dictionary = copy.deepcopy(TESTFILE_TYPE_DATA_DIC)
        if os.path.exists(test_case_path):
            if len(options.testtype) != 0:
                test_type_list = options.testtype
                suit_file_dictionary = self.get_test_file_data(test_case_path,
                                                               test_type_list,
                                                               options)
        else:
            self.case_log.error("%s is not exist." % test_case_path)
        return suit_file_dictionary

    def get_test_file_data(self, test_case_path, test_type_list, options):
        suit_file_dictionary = copy.deepcopy(TESTFILE_TYPE_DATA_DIC)
        for test_type in test_type_list:
            temp_dictionary = \
                self.get_test_file_data_by_test_type(test_case_path,
                                                     test_type,
                                                     options)
            for key, value in suit_file_dictionary.items():
                suit_file_dictionary[key] = value + temp_dictionary[key]
        return suit_file_dictionary

    def get_test_file_data_by_test_type(self, test_case_path,
                                        test_type, options):
        suit_file_dictionary = copy.deepcopy(TESTFILE_TYPE_DATA_DIC)
        test_case_out_path = os.path.join(test_case_path, test_type)
        if os.path.exists(test_case_out_path):
            self.case_log.info("The test case directory: %s" %
                               test_case_out_path)
            return self.get_all_test_file(test_case_out_path, options)
        else:
            self.case_log.error("The test case directory does not exist. %s" %
                                test_case_out_path)
        return suit_file_dictionary

    def get_all_test_file(self, test_case_out_path, options):
        suite_file_dictionary = copy.deepcopy(TESTFILE_TYPE_DATA_DIC)
        filter_list_subsystem = FilterConfigManager().get_filtering_list(
            "subsystem_name", options.productform)
        filter_list_test_file = FilterConfigManager().get_filtering_list(
            "testfile_name", options.productform)

        for subsystem_name in os.listdir(test_case_out_path):
            subsystem_case_dir = os.path.join(test_case_out_path,
                                              subsystem_name)
            if not os.path.isdir(subsystem_case_dir):
                continue

            if subsystem_name in filter_list_subsystem:
                continue

            suit_file_list = get_file_list_by_postfix(subsystem_case_dir)
            for suite_file in suit_file_list:
                if -1 != suite_file.replace(test_case_out_path, "").find(
                        os.sep + "resource" + os.sep):
                    continue

                file_name = os.path.basename(suite_file)
                if file_name in filter_list_test_file:
                    continue

                _, suffix_name = os.path.splitext(file_name)
                if suffix_name in FILTER_SUFFIX_NAME_LIST:
                    continue

                if not self._get_valid_suite_file(test_case_out_path,
                                                  suite_file,
                                                  options.subsystem,
                                                  options.testmodule,
                                                  options.testsuit):
                    continue

                if suffix_name == ".dex":
                    suite_file_dictionary["DEX"].append(suite_file)
                elif suffix_name == ".hap":
                    suite_file_dictionary["HAP"].append(suite_file)
                elif suffix_name == ".py":
                    if not self._check_python_test_file(suite_file):
                        continue
                    suite_file_dictionary["PYT"].append(suite_file)
                elif suffix_name == "":
                    suite_file_dictionary["CXX"].append(suite_file)
                elif suffix_name == ".bin":
                    suite_file_dictionary["BIN"].append(suite_file)

        return suite_file_dictionary

    @classmethod
    def _get_valid_suite_file(cls,
                              test_case_out_path,
                              suit_file,
                              test_subsystem,
                              test_module,
                              test_suit):
        is_valid_status = False
        if suit_file.startswith(test_case_out_path):
            if test_suit == "":
                suite_file_sub_path = suit_file.replace(
                    test_case_out_path, "").strip(os.sep)
                if test_subsystem != "":
                    if test_module != "":
                        if suite_file_sub_path.startswith(test_subsystem +
                                                          os.sep +
                                                          test_module +
                                                          os.sep):
                            is_valid_status = True
                    else:
                        if suite_file_sub_path.startswith(
                                test_subsystem + os.sep):
                            is_valid_status = True
                else:
                    if test_module != "":
                        dir_item_list = suite_file_sub_path.split(os.sep)
                        if len(dir_item_list) > 2 \
                                and test_module == dir_item_list[1]:
                            is_valid_status = True
                    else:
                        is_valid_status = True
            else:
                short_name, _ = os.path.splitext(
                    os.path.basename(suit_file))
                if short_name == test_suit:
                    is_valid_status = True
        return is_valid_status

    @classmethod
    def _check_python_test_file(cls, suite_file):
        if suite_file.endswith(".py"):
            filename = os.path.basename(suite_file)
            if filename.startswith("test_"):
                return True
        return False
