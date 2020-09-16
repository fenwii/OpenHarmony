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

import sys
import os
import xml.etree.ElementTree as ET

from xdevice import platform_logger

CONFIG_PATH = os.path.join(sys.framework_res_dir, "config")


class ConfigFileConst(object):
    FRAMECONFIG_FILEPATH = "framework_config.xml"
    BUILDCONFIG_FILEPATH = "build_config.xml"
    USERCONFIG_FILEPATH = "user_config.xml"
    FILTERCONFIG_FILEPATH = "filter_config.xml"
    RESOURCECONFIG_FILEPATH = "resource_test.xml"
    SCENECONFIG_FILEPATH = "scene_config.xml"

    @property
    def framework_config_file(self):
        return ConfigFileConst.FRAMECONFIG_FILEPATH

    @property
    def user_config_file(self):
        return ConfigFileConst.USERCONFIG_FILEPATH


class FrameworkConfigManager(object):
    def __init__(self, filepath=""):
        if filepath == "":
            self.filepath = os.path.abspath(os.path.join(
                CONFIG_PATH, ConfigFileConst.FRAMECONFIG_FILEPATH))
        else:
            self.filepath = filepath
        self.framework_log = platform_logger("FrameworkConfigManager")

    def get_framework_config(self, targe_tname):
        data_list = []
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()
                node = root.find(targe_tname)
                for sub in node:
                    value = sub.attrib.get("name")
                    if value and value != "":
                        data_list.append(value)
        except ET.ParseError as config_exception:
            self.framework_log.error(("Parse %s fail!" % self.filepath) +
                                     config_exception.args)
        return data_list

    def get_test_category_info(self, target_name="test_category"):
        test_type_timeout_dic = {}
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()
                node = root.find(target_name)
                for sub in node:
                    name = sub.attrib.get("name")
                    desc = sub.attrib.get("desc")
                    timeout = sub.attrib.get("timeout")
                    if name and desc and timeout:
                        test_type_timeout_dic[name] = (desc, timeout)
            else:
                self.framework_log.error("The %s file does not exist." %
                                         self.filepath)
        except ET.ParseError as category_exception:
            self.framework_log.error(("Parse %s fail!" % self.filepath) +
                                     category_exception.args)
        return test_type_timeout_dic

    def get_all_category_info(self, target_name="all_category"):
        return self.get_framework_config(target_name)


class FilterConfigManager(object):
    def __init__(self, filepath=""):
        if filepath == "":
            self.filepath = os.path.abspath(
                os.path.join(CONFIG_PATH,
                             ConfigFileConst.FILTERCONFIG_FILEPATH))
        else:
            self.filepath = filepath
        self.filter_log = platform_logger("FilterConfigManager")

    def get_filtering_list(self, target_name, product_form):
        filter_data_list = []
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()
                for child in root:
                    if child.tag == target_name:
                        for child2 in child:
                            if child2.tag == product_form.lower():
                                for child3 in child2:
                                    if child3.text != "" \
                                            and child3.text is not None:
                                        filter_data_list.append(child3.text)
            else:
                self.filter_log.error("The %s file does not exist." %
                                      self.filepath)
        except ET.ParseError as filter_exception:
            self.filter_log.error(("Parse %s fail!" % self.filepath) +
                                  filter_exception.args)
        return filter_data_list

    def get_filter_config_path(self):
        return self.filepath


class ResourceConfigManager(object):
    def __init__(self, filepath=""):
        if filepath == "":
            self.filepath = os.path.abspath(os.path.join(
                CONFIG_PATH, ConfigFileConst.RESOURCECONFIG_FILEPATH))
        else:
            self.filepath = filepath
        self.resource_log = platform_logger("ResourceConfigManager")

    def get_resource_config(self):
        data_list = []
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()
                for child in root:
                    temp_list = [child.attrib]
                    for sub in child:
                        temp_list.append(sub.attrib)
                    data_list.append(temp_list)
            else:
                self.resource_log.error("The %s is not exist." % self.filepath)
        except ET.ParseError as config_exception:
            self.resource_log.error(("Parse %s fail!" % self.filepath) +
                                    config_exception.args)
        return data_list

    def get_resource_config_path(self):
        return self.filepath


class UserConfigManager(object):
    def __init__(self, config_file=""):
        if config_file == "":
            self.filepath = os.path.abspath(os.path.join(
                CONFIG_PATH, ConfigFileConst.USERCONFIG_FILEPATH))
        else:
            if os.path.isabs(config_file):
                self.filepath = config_file
            else:
                self.filepath = os.path.abspath(
                    os.path.join(CONFIG_PATH, config_file))
        self.user_config_log = platform_logger("UserConfigManager")

    def get_user_config_list(self, tag_name):
        data_dic = {}
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()
                for child in root:
                    if tag_name == child.tag:
                        for sub in child:
                            data_dic[sub.tag] = sub.text
        except ET.ParseError as user_exception:
            self.user_config_log.error(("Parse %s fail!" % self.filepath) +
                                       user_exception.args)
        return data_dic

    @classmethod
    def command_strip(cls, command):
        return command.strip()

    def _verify_duplicate(self, items):
        if len(set(items)) != len(items):
            self.user_config_log.warning("find duplicate sn config, \
                configuration incorrect")
            return False
        return True

    def _handle_str(self, input_str):
        config_list = map(self.command_strip(input_str), input_str.split(';'))
        config_list = [item for item in config_list if item]
        if config_list:
            if not self._verify_duplicate(config_list):
                return []
        return config_list

    def get_sn_list(self):
        sn_select_list = []
        try:
            data_dic = {}
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()

                for node in root.findall("environment/device"):
                    if node.attrib["type"] != "usb-hdc":
                        continue
                    for sub in node:
                        data_dic[sub.tag] = sub.text if sub.text else ""
                    sn_config = data_dic.get("sn", "")
                    if sn_config:
                        sn_select_list = self._handle_str(sn_config)
                    break
        except ET.ParseError as config_exception:
            sn_select_list = []
            self.user_config_log.warning("occurs exception:{}".format(
                config_exception.args))
        return sn_select_list

    def get_remote_config(self):
        remote_dic = {}
        data_dic = self.get_user_config_list("remote")

        if "ip" in data_dic.keys() and "port" in data_dic.keys():
            remote_ip = data_dic.get("ip", "")
            remote_port = data_dic.get("port", "")
        else:
            remote_ip = ""
            remote_port = ""

        if remote_ip is None or remote_port is None:
            remote_ip = ""
            remote_port = ""

        remote_dic["ip"] = remote_ip
        remote_dic["port"] = remote_port
        return remote_dic

    def get_emulator_config(self):
        emulator_sn_list = []

        data_dic = self.get_user_config_list("emulator")
        if "ip" in data_dic.keys() and "port" in data_dic.keys():
            emulator_ip = data_dic.get("ip", "")
            emulator_port = data_dic.get("port", "")
        else:
            emulator_ip = ""
            emulator_port = ""

        if emulator_ip is None or emulator_port is None:
            emulator_ip = ""
            emulator_port = ""

        if emulator_ip != "" and emulator_port != "":
            port_list = emulator_port.split(";")
            for item in port_list:
                if item != "":
                    emulator_sn = emulator_ip + ":" + item
                    if emulator_sn not in emulator_sn_list:
                        emulator_sn_list.append(emulator_sn)

        return emulator_sn_list

    def get_test_case_dir_config(self):
        data_dic = self.get_user_config_list("test_cases")
        if "test_case_dir" in data_dic.keys():
            test_case_dir = data_dic.get("dir", "")
            if test_case_dir is None:
                test_case_dir = ""
        else:
            test_case_dir = ""
        return test_case_dir

    def get_build_example_flag(self):
        data_dic = self.get_user_config_list("build")
        if "example" in data_dic.keys():
            build_example_flag = data_dic.get("example", "")
            if build_example_flag is not None and build_example_flag == "true":
                return True
        return False

    def get_door_manager_config(self):
        data_dic = self.get_user_config_list("door_manager")

        door_test_flag = False
        if "door_test_flag" in data_dic.keys():
            door_test_value = data_dic.get("door_test_flag", "")
            if door_test_value is None:
                door_test_value = ""
            if door_test_value.lower() == "true":
                door_test_flag = True

        door_file_path = ""
        if "door_file_path" in data_dic.keys():
            door_file_path = data_dic.get("door_file_path", "")
            if door_file_path is None:
                door_file_path = ""

        return door_test_flag, door_file_path

    def get_user_config(self, target_name, sub_target=""):
        data_dic = {}
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()

                node = root.find(target_name)
                if not node:
                    return None

                if sub_target != "":
                    node = node.find(sub_target)
                if not node:
                    return None

                for sub in node:
                    if sub.text is None:
                        data_dic[sub.tag] = ""
                    else:
                        data_dic[sub.tag] = sub.text
        except ET.ParseError as data_dic_exception:
            self.user_config_log.error(("Parse %s fail!" % self.filepath) +
                                       data_dic_exception.args)
        return data_dic

    def get_user_config_flag(self, target_name, sub_target):
        config_flag = self.get_user_config(target_name).get(sub_target, "")
        if config_flag == "":
            return False
        return True if config_flag.lower() == "true" else False

    def get_device(self, target_name):
        data_dic = {}
        if os.path.exists(self.filepath):
            tree = ET.parse(self.filepath)
            config_content = tree.getroot()
            for node in config_content.findall(target_name):
                for sub in node:
                    if sub.text is None:
                        data_dic[sub.tag] = ""
                    else:
                        data_dic[sub.tag] = sub.text
                break
        return data_dic


class BuildConfigManager(object):
    def __init__(self, filepath=""):
        if filepath == "":
            self.filepath = os.path.abspath(os.path.join(
                CONFIG_PATH, ConfigFileConst.BUILDCONFIG_FILEPATH))
        else:
            self.filepath = filepath
        self.build_config_log = platform_logger("BuildConfigManager")

    def get_build_config(self, targe_tname):
        data_list = []
        try:
            if os.path.exists(self.filepath):
                tree = ET.parse(self.filepath)
                root = tree.getroot()
                node = root.find(targe_tname)
                for sub in node:
                    value = sub.attrib.get("name")
                    if value and value != "":
                        data_list.append(value)
        except ET.ParseError as build_config_exception:
            self.build_config_log.error(("Parse %s fail!" % self.filepath) +
                                        build_config_exception.args)
        return data_list

    def get_build_path(self):
        return self.filepath
