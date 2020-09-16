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
import xml.etree.ElementTree as ET
from dataclasses import dataclass

from _core.exception import ParamError
from _core.logger import platform_logger

__all__ = ["UserConfigManager"]
LOG = platform_logger("ConfigManager")


@dataclass
class ConfigFileConst(object):
    userconfig_filepath = "user_config.xml"


class UserConfigManager(object):
    def __init__(self, config_file="", env=""):
        from xdevice import Variables
        if config_file:
            pass
        try:
            if env:
                self.config_content = ET.fromstring(env)
            else:
                user_path = os.path.join(Variables.exec_dir, "config")
                top_user_path = os.path.join(Variables.top_dir, "config")
                config_path = os.path.join(Variables.res_dir, "config")
                paths = [user_path, top_user_path, config_path]

                for path in paths:
                    if os.path.exists(os.path.abspath(os.path.join(
                            path, ConfigFileConst.userconfig_filepath))):
                        self.file_path = os.path.abspath(os.path.join(
                            path, ConfigFileConst.userconfig_filepath))
                        break

                if os.path.exists(self.file_path):
                    tree = ET.parse(self.file_path)
                    self.config_content = tree.getroot()
                else:
                    raise ParamError("config file not found")

        except SyntaxError as error:
            if env:
                raise ParamError(
                    "Parse environment parameter fail! Error: %s" % error.args)
            else:
                raise ParamError(
                    "Parse %s fail! Error: %s" % (self.file_path, error.args))

    def get_user_config_list(self, tag_name):
        data_dic = {}
        for child in self.config_content:
            if tag_name == child.tag:
                for sub in child:
                    data_dic[sub.tag] = sub.text
        return data_dic

    @staticmethod
    def remove_strip(value):
        return value.strip()

    @staticmethod
    def _verify_duplicate(items):
        if len(set(items)) != len(items):
            LOG.warning("find duplicate sn config, configuration incorrect")
            return False
        return True

    def _handle_str(self, input_string):
        config_list = map(self.remove_strip, input_string.split(';'))
        config_list = [item for item in config_list if item]
        if config_list:
            if not self._verify_duplicate(config_list):
                return []
        return config_list

    def get_sn_list(self):
        sn_select_list = []
        data_dic = {}
        for node in self.config_content.findall("environment/device"):
            if node.attrib["type"] != "usb-hdc":
                continue
            for sub in node:
                data_dic[sub.tag] = sub.text if sub.text else ""
            sn_config = data_dic.get("sn", "")
            if sn_config:
                sn_select_list = self._handle_str(sn_config)
            break
        return sn_select_list

    def get_remote_config(self):
        remote_dic = {}
        data_dic = self.get_user_config_list("remote")

        if "ip" in data_dic.keys() and "port" in data_dic.keys():
            remote_ip = data_dic.get("ip", "")
            remote_adb_port = data_dic.get("port", "")
        else:
            remote_ip = ""
            remote_adb_port = ""

        if (not remote_ip) or (not remote_adb_port):
            remote_ip = ""
            remote_adb_port = ""

        remote_dic["ip"] = remote_ip
        remote_dic["port"] = remote_adb_port
        return remote_dic

    def get_testcases_dir_config(self):
        data_dic = self.get_user_config_list("testcases")
        if "dir" in data_dic.keys():
            testcase_dir = data_dic.get("dir", "")
            if testcase_dir is None:
                testcase_dir = ""
        else:
            testcase_dir = ""
        return testcase_dir

    def get_user_config(self, target_name, filter_name=None):
        data_dic = {}
        all_nodes = self.config_content.findall(target_name)
        if not all_nodes:
            return data_dic

        for node in all_nodes:
            if filter_name:
                if node.get('label') != filter_name:
                    continue
            for sub in node:
                data_dic[sub.tag] = sub.text if sub.text else ""

        return data_dic

    def get_node_attr(self, target_name, attr_name):
        nodes = self.config_content.find(target_name)
        if attr_name in nodes.attrib:
            return nodes.attrib.get(attr_name)

    def get_com_device(self, target_name):
        devices = []

        for node in self.config_content.findall(target_name):
            if node.attrib["type"] != "com":
                continue

            device = [node.attrib]

            # get remote device
            data_dic = {}
            for sub in node:
                if sub.text is not None and sub.tag != "serial":
                    data_dic[sub.tag] = sub.text
            if data_dic:
                device.append(data_dic)
                devices.append(device)
                continue

            # get local device
            for serial in node.findall("serial"):
                data_dic = {}
                for sub in serial:
                    if sub.text is None:
                        data_dic[sub.tag] = ""
                    else:
                        data_dic[sub.tag] = sub.text
                device.append(data_dic)
            devices.append(device)
        return devices

    def get_device(self, target_name):
        data_dic = {}

        for node in self.config_content.findall(target_name):
            if node.attrib["type"] != "usb-hdc":
                continue
            for sub in node:
                if sub.text is None:
                    data_dic[sub.tag] = ""
                else:
                    data_dic[sub.tag] = sub.text
            break
        return data_dic

    def get_testcases_dir(self):
        from xdevice import Variables
        testcases_dir = self.get_testcases_dir_config()
        if testcases_dir:
            if os.path.isabs(testcases_dir):
                return testcases_dir
            return os.path.abspath(os.path.join(Variables.exec_dir,
                                                testcases_dir))

        return os.path.abspath(os.path.join(Variables.exec_dir, "testcases"))

    def get_resource_path(self):
        from xdevice import Variables
        data_dic = self.get_user_config_list("resource")
        if "dir" in data_dic.keys():
            resource_dir = data_dic.get("dir", "")
            if resource_dir:
                if os.path.isabs(resource_dir):
                    return resource_dir
                return os.path.abspath(
                    os.path.join(Variables.exec_dir, resource_dir))

        return os.path.abspath(
            os.path.join(Variables.exec_dir, "resource"))
