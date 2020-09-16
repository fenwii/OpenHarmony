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

from _core.logger import platform_logger

LOG = platform_logger("ResourceManager")
DEFAULT_TIMEOUT = "300"


class ResourceManager(object):
    def __init__(self):
        pass

    def get_resource_data(self, xml_filepath, target_name):
        data_dic = {}
        if os.path.exists(xml_filepath):
            data_dic = self._parse_test_xml_file(xml_filepath,
                                                 target_name)
        return data_dic

    def _parse_test_xml_file(self, filepath, targetname):
        data_dic = {}

        node = self._find_node_by_target(filepath, targetname)
        if node:
            target_attrib_list = []
            target_attrib_list.append(node.attrib)
            environment_data_list = []
            env_node = node.find("environment")
            if env_node:
                environment_data_list.append(env_node.attrib)
                for element in env_node.findall("device"):
                    environment_data_list.append(element.attrib)
                    for option_element in element.findall("option"):
                        environment_data_list.append(option_element.attrib)

            preparer_data_list = []
            pre_node = node.find("preparer")
            if pre_node:
                preparer_data_list.append(pre_node.attrib)
                for element in pre_node.findall("option"):
                    preparer_data_list.append(element.attrib)

            cleaner_data_list = []
            clr_node = node.find("cleaner")
            if clr_node:
                cleaner_data_list.append(clr_node.attrib)
                for element in clr_node.findall("option"):
                    cleaner_data_list.append(element.attrib)

            data_dic["nodeattrib"] = target_attrib_list
            data_dic["environment"] = environment_data_list
            data_dic["preparer"] = preparer_data_list
            data_dic["cleaner"] = cleaner_data_list

        return data_dic

    @staticmethod
    def _find_node_by_target(filepath, targetname):
        node = None
        try:
            if os.path.exists(filepath):
                tree = ElementTree.parse(filepath)
                root = tree.getroot()
                targets = root.getiterator("target")
                for target in targets:
                    curr_dic = target.attrib
                    if curr_dic.get("name") == targetname:
                        node = target
                        break
        except (SyntaxError, ValueError, AttributeError, TypeError) as error:
            LOG.error("resource_test.xml parsing failed. %s", error.args)
        return node

    @staticmethod
    def _get_filename_extension(filepath):
        _, fullname = os.path.split(filepath)
        filename, ext = os.path.splitext(fullname)
        return filename, ext

    @staticmethod
    def process_resource_file(resource_dir, preparer_list, device):
        for item in preparer_list:
            if "name" not in item.keys():
                continue

            if item["name"] == "push":
                push_value = item["value"]

                find_key = "->"
                pos = push_value.find(find_key)
                src = os.path.join(resource_dir, push_value[0:pos].strip())
                dst = push_value[pos + len(find_key):len(push_value)].strip()

                LOG.info("create_dir: dst = %s" % (dst))
                device.execute_shell_command("mkdir -p %s" % dst)
                LOG.info("push_file: src = %s, dst = %s" % (src, dst))
                device.push_file(src, dst)
            elif item["name"] == "pull":
                push_value = item["value"]

                find_key = "->"
                pos = push_value.find(find_key)
                src = os.path.join(resource_dir, push_value[0:pos].strip())
                dst = push_value[pos + len(find_key):len(push_value)].strip()

                LOG.info("pull_file: src = %s, dst = %s" % (src, dst))
                device.pull_file(src, dst)
            elif item["name"] == "shell":
                command = item["value"].strip()
                LOG.info("shell = %s", command)
                device.execute_shell_command(command)
            else:
                command = "".join((item["name"], " ", item["value"]))
                command = command.strip()
                LOG.info("others = %s", command)
                device.execute_command(command)

    @staticmethod
    def _get_xml_filepath(testsuite_filepath):
        xml_filepath = ""
        resource_dir = os.path.join(os.path.dirname(testsuite_filepath),
                                    "resource")
        if os.path.exists(resource_dir):
            xml_filepath = os.path.join(resource_dir, "resource_test.xml")
        return xml_filepath

    def get_resource_data_dic(self, testsuit_filepath):
        resource_dir = ""
        data_dic = {}

        target_name, _ = self._get_filename_extension(testsuit_filepath)
        xml_filepath = self._get_xml_filepath(testsuit_filepath)
        if not os.path.exists(xml_filepath):
            return data_dic, resource_dir

        data_dic = self.get_resource_data(xml_filepath, target_name)
        resource_dir = os.path.abspath(os.path.dirname(xml_filepath))
        return data_dic, resource_dir

    def process_preparer_data(self, data_dic, resource_dir, device):
        if "preparer" in data_dic.keys():
            LOG.info("++++++++++++++preparer+++++++++++++++")
            preparer_list = data_dic["preparer"]
            self.process_resource_file(resource_dir, preparer_list, device)
        return

    def process_cleaner_data(self, data_dic, resource_dir, device):
        if "cleaner" in data_dic.keys():
            LOG.info("++++++++++++++cleaner+++++++++++++++")
            cleaner_list = data_dic["cleaner"]
            self.process_resource_file(resource_dir, cleaner_list, device)
        return
