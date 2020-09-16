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
import xml.etree.ElementTree as ElementTree
from xdevice import platform_logger

DEFAULT_TIMEOUT = "300"


##############################################################################
##############################################################################

class ResourceManager(object):
    resource_log = platform_logger("ResourceManager")

    def __init__(self):
        self.resource_path = ""

    def _find_node_by_target(self, file_path, targe_tname):
        node = None
        try:
            if os.path.exists(file_path):
                tree = ElementTree.parse(file_path)
                root = tree.getroot()
                targets = root.getiterator("target")
                for target in targets:
                    curr_dic = target.attrib
                    if curr_dic.get("name") == targe_tname:
                        node = target
                        break
        except ElementTree.ParseError as node_exception:
            self.resource_log.error("resource_test.xml parsing failed." +
                                    node_exception.args)
        return node

    ##########################################################################
    ##########################################################################

    @classmethod
    def _get_file_name_extension(cls, filepath):
        _, fullname = os.path.split(filepath)
        filename, ext = os.path.splitext(fullname)
        cls.resource_log.debug("file path:{}".format(filepath))
        return filename, ext

    def process_resource_file(self, resource_dir, preparer_list, device):
        for item in preparer_list:
            if "name" not in item.keys():
                continue

            if item["name"] == "push":
                push_value = item["value"]

                find_key = "->"
                pos = push_value.find(find_key)
                src = os.path.join(resource_dir, push_value[0:pos].strip())
                dst = push_value[pos + len(find_key):len(push_value)].strip()

                self.resource_log.info("create_dir: dst = %s" % (dst))
                device.create_dir(dst)
                self.resource_log.info("push_file: src = %s, dst = %s" %
                                       (src, dst))
                device.push_file(src, dst)
            elif item["name"] == "pull":
                push_value = item["value"]
                find_key = "->"
                pos = push_value.find(find_key)
                src = os.path.join(resource_dir, push_value[0:pos].strip())
                dst = push_value[pos + len(find_key):len(push_value)].strip()
                self.resource_log.info("pull_file: src = %s, dst = %s" %
                                       (src, dst))
                device.pull_file(src, dst)
            elif item["name"] == "shell":
                command = item["value"].strip()
                print("shell = " + command)
                device.execute_shell_command(command)
            else:
                command = item["name"] + " " + item["value"]
                command = command.strip()
                self.resource_log.info("others = " + command)
                device.execute_command(command)

    @classmethod
    def _get_environment_data(cls, environment_list):
        env_data_dic = {}
        device_name = ""
        option_dic = {}

        for item in environment_list:
            if "type" in item.keys():
                if device_name != "":
                    temp_dic = option_dic.copy()
                    env_data_dic[device_name] = temp_dic
                    device_name = ""
                    option_dic.clear()
                device_name = item["type"]

            if "name" in item.keys():
                name = item["name"]
                value = item["value"]
                option_dic[name] = value

        if device_name != "":
            temp_dic = option_dic.copy()
            env_data_dic[device_name] = temp_dic
            device_name = ""
            option_dic.clear()
        cls.resource_log.debug("get environment data finish")
        return env_data_dic

    def _get_resource_xml_file_path(self, test_suit_file_path):
        current_dir = os.path.dirname(test_suit_file_path)
        while True:
            if current_dir.endswith(os.sep + "tests"):
                current_dir = ""
                break
            if current_dir == "/" or current_dir.endswith(":\\"):
                current_dir = ""
                break
            if os.path.exists(os.path.join(current_dir, "resource")):
                break
            current_dir = os.path.dirname(current_dir)

        if current_dir != "":
            xml_filepath = os.path.join(
                current_dir, "resource", "resource_test.xml")
        else:
            xml_filepath = ""
        self.resource_log.info("xml_filepath = %s" % xml_filepath)
        return xml_filepath

    @classmethod
    def get_nodeattrib_data(cls, data_dic):
        curr_timeout = DEFAULT_TIMEOUT
        if "nodeattrib" in data_dic.keys():
            print("++++++++++++++nodeattrib+++++++++++++++")
            nodeattrib_list = data_dic["nodeattrib"]
            if len(nodeattrib_list) != 0:
                node_item_dic = nodeattrib_list[0]
                if "timeout" in node_item_dic:
                    curr_timeout = node_item_dic["timeout"]
        return curr_timeout

    def get_environment_data(self, data_dic):
        env_data_dic = {}
        if "environment" in data_dic.keys():
            print("++++++++++++++environment+++++++++++++++")
            environment_list = data_dic["environment"]
            env_data_dic = self._get_environment_data(environment_list)
        return env_data_dic

    def process_preparer_data(self, data_dic, resource_dir, device):
        if "preparer" in data_dic.keys():
            print("++++++++++++++preparer+++++++++++++++")
            preparer_list = data_dic["preparer"]
            self.process_resource_file(resource_dir, preparer_list, device)
        return

    def process_cleaner_data(self, data_dic, resource_dir, device):
        if "cleaner" in data_dic.keys():
            print("++++++++++++++cleaner+++++++++++++++")
            cleaner_list = data_dic["cleaner"]
            self.process_resource_file(resource_dir, cleaner_list, device)
        return

    def get_resource_xml_file_version(self, xml_filepath):
        xml_file_version = ""
        try:
            if os.path.exists(xml_filepath):
                tree = ElementTree.parse(xml_filepath)
                root = tree.getroot()
                curr_dic = root.attrib
                xml_file_version = curr_dic.get("ver", "")
        except ElementTree.ParseError as xml_exception:
            self.resource_log.error("Error: resource_test.xml parse fail." +
                                    xml_exception.args)
        return xml_file_version


##############################################################################
##############################################################################
