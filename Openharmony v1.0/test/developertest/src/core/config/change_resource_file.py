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


##############################################################################
##############################################################################

class MakeNewResourceConfig(object):
    linefeed = '\n'

    def make_xml_file(self, src_filepath, dst_filepath):
        data_list = self.get_resource_list(src_filepath)
        if len(data_list) != 0:
            self._make_file_head(dst_filepath)
            for item in data_list:
                self._make_file_target(dst_filepath, item)
            self._make_file_tail(dst_filepath)
        else:
            return

    def get_resource_list(self, filepath):
        data_list = []
        if os.path.exists(filepath):
            attrib_list = self._parse_test_xml_file(filepath)
            if 0 != len(attrib_list):
                data_list = attrib_list
        return data_list

    @classmethod
    def _parse_test_xml_file(cls, filepath):
        data_list = []
        try:
            if os.path.exists(filepath):
                tree = ElementTree.parse(filepath)
                root = tree.getroot()
                for child in root:
                    temp_list = [child.attrib]
                    for sub in child:
                        temp_list.append(sub.attrib)
                    data_list.append(temp_list)
            else:
                print("Error: the %s is not exist." % filepath)
        except ElementTree.ParseError as xml_exception:
            print("Exception: parse resource_test.xml fail! %s" %
                  xml_exception.args)
        return data_list

    def _make_file_head(self, filepath):
        with open(filepath, "w") as resource_file:
            resource_file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>%s"
                                % self.linefeed)
            resource_file.write("<configuration ver=\"2.0\">%s" %
                                self.linefeed)

    def _make_file_tail(self, filepath):
        with open(filepath, "a") as resource_file:
            resource_file.write("</configuration>" + self.linefeed)

    def _make_file_target(self, filepath, data_list):
        print(data_list)
        with open(filepath, "a") as resource_file:
            for index, value in enumerate(data_list):
                print(index)
                print(value)
                if index == 0:
                    target_name = value.get("name")
                    resource_file.write("    <target name=\"%s\">%s" %
                                        (target_name, self.linefeed))
                    resource_file.write("        <preparer>%s" % self.linefeed)
                else:
                    resource = value.get("resource")
                    push_path = value.get("pushpath")
                    find_path = value.get("findpath")
                    resource_file.write("            <option name=\"push\" \
                        value=\"%s -> %s\" src=\"%s\"/>%s"
                                        % (resource, push_path, find_path,
                                           self.linefeed))
            resource_file.write("        </preparer>%s" % self.linefeed)
            resource_file.write("    </target>%s" % self.linefeed)
            resource_file.close()

    @property
    def default_resource_config(self):
        return self.linefeed

##############################################################################
##############################################################################
