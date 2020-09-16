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
from core.utils import get_file_list_by_postfix
from xdevice import platform_logger


##############################################################################
##############################################################################


class FilterTargets(object):
    def __init__(self, project_rootpath):
        self.log = platform_logger("FilterTargets")
        self.project_rootpath = project_rootpath

    def get_part_name_list_by_product(self, productform):
        platforms_parts_filepath = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            "build_configs",
            "target_platforms_parts.json")

        if not os.path.exists(platforms_parts_filepath):
            self.log.warning("Error: %s is not exist." %
                        platforms_parts_filepath)
            return []

        data_dic = None
        with open(platforms_parts_filepath, 'r') as platforms_parts_file:
            data_dic = json.load(platforms_parts_file)
            if not data_dic:
                self.log.warning("The %s file load error." %
                            platforms_parts_filepath)
                return []

        partname_list = []
        tmpdic = data_dic.get(productform, None)
        if tmpdic is None:
            self.log.warning("Error: tmpdic is None.")
            return []

        for data in tmpdic:
            partname_list.append(tmpdic.get(data))
        return partname_list

    def _get_parts_info_list(self, productform):
        parts_info_filepath = os.path.join(
            self.project_rootpath,
            "out",
            "release",
            "build_configs",
            "parts_info",
            "parts_info.json")

        if not os.path.exists(parts_info_filepath):
            return []

        data_dic = None
        with open(parts_info_filepath, 'r') as parts_info_file:
            data_dic = json.load(parts_info_file)
            if not data_dic:
                print("The %s file load error." % parts_info_filepath)
                return []

        parts_info_dic = {}
        for value in data_dic:
            tmp_list = data_dic.get(value)
            if len(tmp_list) == 1:
                parts_info_dic[value] = tmp_list[0]
                continue

            for item in tmp_list:
                variant_name = item.get("variant_name")
                if variant_name == productform:
                    parts_info_dic[value] = item
        return parts_info_dic

    def _get_part_path_list(self, productform):
        part_path_dic = {}

        partname_list = self.get_part_name_list_by_product(productform)
        if len(partname_list) == 0:
            self.log.warning("Error: partname_list is empty.")
            return part_path_dic

        parts_info_dic = self._get_parts_info_list(productform)
        if len(parts_info_dic) == 0:
            self.log.warning("Error: parts_info_dic is empty.")
            return part_path_dic

        for partname in partname_list:
            item = parts_info_dic.get(partname, None)
            if item is None:
                continue

            origin_part_name = item.get("origin_part_name")
            build_out_dir = item.get("build_out_dir")

            if build_out_dir == ".":
                partpath = os.path.join(
                    self.project_rootpath,
                    "out",
                    "release",
                    "module_list_files",
                    origin_part_name)
            else:
                partpath = os.path.join(
                    self.project_rootpath,
                    "out",
                    "release",
                    build_out_dir,
                    "module_list_files",
                    origin_part_name)

            part_path_dic[partname] = partpath
        return part_path_dic


    def _get_mlf_data_from_file(self, filepath):
        data_list = []

        if os.path.exists(filepath):
            with open(filepath, 'r') as mlf_file:
                data_list = json.load(mlf_file)
                if not data_list:
                    self.log.warning("The %s file load error." % filepath)
                    data_list = []

        return data_list

    def _get_target_list_from_path(self, typelist, check_path):
        target_list = []
        if os.path.exists(check_path):
            mlf_filepath_list = get_file_list_by_postfix(
                check_path, ".mlf")
            for filepath in mlf_filepath_list:
                mlf_info_list = self._get_mlf_data_from_file(filepath)
                for data in mlf_info_list:
                    test_type = data.get("test_type")
                    target_path = data.get("label")
                    if "ALL" in typelist:
                        target_list.append(target_path)
                        continue
                    if test_type in typelist:
                        target_list.append(target_path)
        return target_list

    def _get_target_list_by_type(self, productform, typelist):
        target_list = []
        part_path_dic = self._get_part_path_list(productform)
        for item in part_path_dic:
            part_path = part_path_dic.get(item)
            temp_list = self._get_target_list_from_path(typelist, part_path)
            target_list.extend(temp_list)
        return target_list

    def _get_target_list_by_part(self, productform, typelist, testpart):
        target_list = []
        part_path_dic = self._get_part_path_list(productform)
        testpart_path = part_path_dic.get(testpart, "")
        if testpart_path != "":
            target_list = self._get_target_list_from_path(typelist,
                testpart_path)
        return target_list

    def _get_target_list_by_module(self, productform, typelist, testpart,
                                   testmodule):
        target_list = []
        part_path_dic = self._get_part_path_list(productform)
        testpart_path = part_path_dic.get(testpart, "")
        if testpart_path != "":
            module_path = os.path.join(testpart_path, testmodule)
            target_list = self._get_target_list_from_path(typelist,
                module_path)
        return target_list


    def get_build_targets(self, productform, typelist, testpart, testmodule):
        target_list = []

        if productform == "" or len(typelist) == 0:
            self.log.warning("Error: productform or typelist is empty.")
            return []

        if testpart == "" and testmodule == "":
            target_list = self._get_target_list_by_type(productform, typelist)
            return target_list

        if testpart == "" and testmodule != "":
            self.log.warning(
                "The part cannot be empty When the module is not empty.")
            return target_list

        if testpart != "" and testmodule == "":
            target_list = self._get_target_list_by_part(productform, typelist,
                                                        testpart)
            return target_list

        if testpart != "" and testmodule != "":
            target_list = self._get_target_list_by_module(productform,
                                                          typelist,
                                                          testpart,
                                                          testmodule)

        return target_list

    def filter_build_targets(self, para):
        productform = para.productform
        typelist = para.testtype
        testpart = para.subsystem
        testmodule = para.testmodule

        target_list = self.get_build_targets(productform, typelist, testpart,
                                             testmodule)
        return target_list


##############################################################################
##############################################################################
