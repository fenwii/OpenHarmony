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
from dataclasses import dataclass

from _core.config.config_manager import UserConfigManager
from _core.exception import DeviceError
from _core.exception import ParamError
from _core.logger import platform_logger
from _core.plugin import Plugin
from _core.plugin import get_plugin
from _core.utils import convert_serial

__all__ = ["EnvironmentManager", "DeviceSelectionOption",
           "DeviceAllocationState"]

LOG = platform_logger("ManagerEnv")


class Environment(object):
    """
    Environment required for each dispatch
    """

    def __init__(self):
        self.devices = []
        self.phone = 0
        self.wifiiot = 0
        self.ipcamera = 0

    def __get_serial__(self):
        device_serials = []
        for device in self.devices:
            device_serials.append(convert_serial(device.__get_serial__()))
        return ";".join(device_serials)

    def get_devices(self):
        return self.devices

    def check_serial(self):
        if self.__get_serial__():
            return True
        return False

    def add_device(self, device):
        if device.label == "phone":
            self.phone += 1
            device.device_id = "phone%s" % str(self.phone)
        self.devices.append(device)


class EnvironmentManager(object):
    """
    Class representing environment manager
    managing the set of available devices for testing
    """
    __instance = None
    __init_flag = False

    def __new__(cls, *args, **kwargs):
        """
        Singleton instance
        """
        del args, kwargs
        if cls.__instance is None:
            cls.__instance = super(EnvironmentManager, cls).__new__(cls)
        return cls.__instance

    def __init__(self, environment=""):
        if EnvironmentManager.__init_flag:
            return
        self.manager_device = None
        self.manager_lite = None
        self._get_device_manager(environment)
        EnvironmentManager.__init_flag = True

    def _get_device_manager(self, environment=""):
        try:
            result = UserConfigManager(env=environment).get_user_config(
                "environment/support_device")
        except ParamError as error:
            LOG.exception("ParamError: %s" % error.args, exc_info=False)
            if not environment:
                sys.exit(0)
            else:
                raise error
        if result.get("device") == "true":
            managers_device = get_plugin(plugin_type=Plugin.MANAGER,
                                         plugin_id="device")
            if managers_device:
                self.manager_device = managers_device[0]
                self.manager_device.init_environment(environment)
        if result.get("device_lite") == "true":
            managers_lite = get_plugin(plugin_type=Plugin.MANAGER,
                                       plugin_id="device_lite")
            if managers_lite:
                self.manager_lite = managers_lite[0]
                self.manager_lite.init_environment(environment)

    def env_stop(self):
        if self.manager_device:
            self.manager_device.env_stop()
            self.manager_device = None
        if self.manager_lite:
            self.manager_lite.devices_list = []
            self.manager_lite = None
        EnvironmentManager.__init_flag = False

    def apply_environment(self, device_options):
        environment = Environment()
        for device_option in device_options:
            device = self.apply_device(device_option)
            if device is not None:
                environment.add_device(device)

        return environment

    def release_environment(self, environment):
        for device in environment.devices:
            self.release_device(device)

    def apply_device(self, device_option, timeout=10):

        if not device_option.label or device_option.label == "phone":
            device_manager = self.manager_device
        else:
            device_manager = self.manager_lite

        if device_manager:
            return device_manager.apply_device(device_option, timeout)
        else:
            raise DeviceError(
                "%s is not supported, please check %s and "
                "environment config user_config.xml" %
                (str(device_option.test_driver), device_option.source_file))

    def check_device_exist(self, device_options):
        """
        Check if there are matched devices which can be allocated or available.
        """
        for device_option in device_options:
            device_exist = False
            if self.manager_device:
                for device in self.manager_device.devices_list:
                    if device_option.matches(device, False):
                        device_exist = True
            if self.manager_lite:
                for device in self.manager_lite.devices_list:
                    if device_option.matches(device, False):
                        device_exist = True
            if not device_exist:
                return False

        return True

    def release_device(self, device):
        if self.manager_device and \
                device in self.manager_device.devices_list:
            self.manager_device.release_device(device)
        elif self.manager_lite and \
                device in self.manager_lite.devices_list:
            self.manager_lite.release_device(device)

    def list_devices(self):
        LOG.info("list devices.")
        if self.manager_device:
            self.manager_device.list_devices()
        if self.manager_lite:
            self.manager_lite.list_devices()


class DeviceSelectionOption(object):
    """
    Class representing device selection option
    """

    def __init__(self, options, label=None, test_source=None):
        self.device_sn = [x for x in options["device_sn"].split(";") if x]
        self.label = label
        self.test_driver = test_source.test_type
        self.source_file = ""

    def get_label(self):
        return self.label

    def matches(self, device, allocate=True):
        if allocate and device.device_allocation_state != \
                DeviceAllocationState.available:
            return False

        if not allocate and device.device_allocation_state == \
                DeviceAllocationState.ignored:
            return False

        if len(self.device_sn) != 0 and device.device_sn not in self.device_sn:
            return False

        if self.label and self.label != device.label:
            return False

        return True


@dataclass
class DeviceAllocationState:
    ignored = "Ignored"
    available = "Available"
    allocated = "Allocated"
