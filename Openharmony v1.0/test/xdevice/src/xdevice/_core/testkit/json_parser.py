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

import json
import os

from _core.exception import ParamError
from _core.logger import platform_logger
from _core.plugin import Config

__all__ = ["JsonParser"]
LOG = platform_logger("JsonParser")


class JsonParser:
    """
    This class parses json files or string, sample:
    {
        "description": "Config for lite cpp test cases",
        "environment": [
            {
                "type": "device",
                "label": "ipcamera"
            }
        ],
        "kits": [
            {
                "type": "MountKit",
                "nfs": "NfsServer",
                "bin_file": "CppTestLite/KvStoreTest.bin"
            }
        ],
        "driver": {
            "type": "CppTestLite",
            "xml-output": false,
            "rerun": false
        }
    }
    """

    def __init__(self, path_or_content):
        """Instantiate the class using the manifest file denoted by path or
        content
        """
        self.config = Config()
        self._do_parse(path_or_content)

    def _do_parse(self, path_or_content):
        try:
            if path_or_content.find("{") != -1:
                json_content = json.loads(
                    path_or_content, encoding="utf-8")
            else:
                if not os.path.exists(path_or_content):
                    raise ParamError("The json file {} does not exist".format(
                        path_or_content))
                with open(path_or_content, encoding="utf-8") as file_content:
                    json_content = json.load(file_content)
        except (TypeError, ValueError, AttributeError) as error:
            raise ParamError("%s %s" % (path_or_content, error))
        self._check_config(json_content)

        # set self.config
        self.config = Config()
        self.config.description = json_content.get("description", "")
        self.config.kits = json_content.get("kits", [])
        self.config.environment = json_content.get("environment", [])
        self.config.driver = json_content.get("driver", {})

    def _check_config(self, json_content):
        for kit in json_content.get("kits", []):
            self._check_type_key_exist("kits", kit)
        for device in json_content.get("environment", []):
            self._check_type_key_exist("environment", device)
        if json_content.get("driver", {}):
            self._check_type_key_exist("driver", json_content.get("driver"))

    @classmethod
    def _check_type_key_exist(cls, key, value):
        if not isinstance(value, dict):
            raise ParamError("%s under %s should be dict" % (value, key))
        if "type" not in value.keys():
            raise ParamError("'type' key not exists in %s under %s" % (
                value, key))

    def get_config(self):
        return self.config

    def get_description(self):
        return getattr(self.config, "description", "")

    def get_kits(self):
        return getattr(self.config, "kits", [])

    def get_environment(self):
        return getattr(self.config, "environment", [])

    def get_driver(self):
        return getattr(self.config, "driver", {})

    def get_driver_type(self):
        driver = getattr(self.config, "driver", {})
        return driver.get("type", "") if driver else ""
