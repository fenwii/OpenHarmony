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

import re
import telnetlib
import time
import os

from _core.constants import DeviceOsType
from _core.constants import ComType
from _core.constants import DeviceLabelType
from _core.environment.dmlib_lite import LiteHelper
from _core.exception import LiteDeviceConnectError
from _core.exception import ParamError
from _core.exception import DeviceError
from _core.interface import IDevice
from _core.exception import ExecuteTerminate
from _core.logger import platform_logger
from _core.environment.manager_env import DeviceAllocationState
from _core.plugin import Plugin
from _core.utils import exec_cmd

LOG = platform_logger("DeviceLite")
TIMEOUT = 90
HDC = "litehdc.exe"


def get_hdc_path():
    from xdevice import Variables
    user_path = os.path.join(Variables.exec_dir, "resource/tools")
    top_user_path = os.path.join(Variables.top_dir, "config")
    config_path = os.path.join(Variables.res_dir, "config")
    paths = [user_path, top_user_path, config_path]

    file_path = ""
    for path in paths:
        if os.path.exists(os.path.abspath(os.path.join(
                path, HDC))):
            file_path = os.path.abspath(os.path.join(
                path, HDC))
            break

    if os.path.exists(file_path):
        return file_path
    else:
        raise ParamError("config file not found")


def parse_available_com(com_str):
    com_str = com_str.replace("\r", " ")
    com_list = com_str.split("\n")
    for index, item in enumerate(com_list):
        com_list[index] = item.strip().strip(b'\x00'.decode())
    return com_list


@Plugin(type=Plugin.DEVICE, id=DeviceOsType.lite)
class DeviceLite(IDevice):
    """
    Class representing an device lite device.

    Each object of this class represents one device lite device in xDevice.

    Attributes:
        device_connect_type: A string that's the type of lite device
    """
    device_os_type = DeviceOsType.lite
    device_allocation_state = DeviceAllocationState.available

    def __init__(self):
        self.error_message = ""
        self.device_sn = ""
        self.label = ""
        self.device_connect_type = ""
        self.device_kernel = ""
        self.remote_device = None
        self.local_device = None

    def __set_serial__(self, device=None):
        for item in device:
            if "ip" in item.keys():
                self.device_sn = "remote_%s" % item.get("ip")
                break
            elif "type" in item.keys() and ComType.deploy_com == item.get(
                    "type"):
                self.device_sn = "local_%s" % item.get("com")
                break

    def __get_serial__(self):
        return self.device_sn

    def __set_device_kernel__(self, kernel_type=""):
        self.device_kernel = kernel_type

    def __get_device_kernel__(self):
        return self.device_kernel

    def __check_watch__(self, device):
        for item in device:
            if "label" not in item.keys():
                if "com" not in item.keys() or ("com" in item.keys() and
                                                not item.get("com")):
                    self.error_message = "watch local com cannot be " \
                                         "empty, please check"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)
                else:
                    hdc = get_hdc_path()
                    result = exec_cmd([hdc])
                    com_list = parse_available_com(result)
                    if item.get("com").upper() in com_list:
                        return True
                    else:
                        self.error_message = "watch local com does not exist"
                        LOG.error(self.error_message)
                        raise ParamError(self.error_message)

    def __check_wifiiot_config__(self, device):
        com_type_set = set()
        for item in device:
            if "label" not in item.keys():
                if "com" not in item.keys() or ("com" in item.keys() and
                                                not item.get("com")):
                    self.error_message = "wifiiot local com cannot be " \
                                         "empty, please check"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)

                if "type" not in item.keys() or ("type" not in item.keys() and
                                                 not item.get("type")):
                    self.error_message = "wifiiot com type cannot be " \
                                         "empty, please check"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)
                else:
                    com_type_set.add(item.get("type"))
        if len(com_type_set) < 2:
            self.error_message = "wifiiot need cmd com and deploy com" \
                                 " at the same time, please check"
            LOG.error(self.error_message)
            raise ParamError(self.error_message)

    def __check_ipcamera_local__(self, device):
        for item in device:
            if "label" not in item.keys():
                if "com" not in item.keys() or ("com" in item.keys() and
                                                not item.get("com")):
                    self.error_message = "ipcamera local com cannot be " \
                                         "empty, please check"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)

    def __check_ipcamera_remote__(self, device=None):
        for item in device:
            if "label" not in item.keys():
                if "port" in item.keys() and item.get("port") and not item.get(
                        "port").isnumeric():
                    self.error_message = "ipcamera remote port should be " \
                                         "a number, please check"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)
                elif "port" not in item.keys():
                    self.error_message = "ipcamera remote port cannot be" \
                                         " empty, please check"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)

    def __check_config__(self, device=None):
        self.set_connect_type(device)
        if self.label == DeviceLabelType.wifiiot:
            self.__check_wifiiot_config__(device)
        elif self.label == DeviceLabelType.ipcamera and \
                self.device_connect_type == "local":
            self.__check_ipcamera_local__(device)
        elif self.label == DeviceLabelType.ipcamera and \
                self.device_connect_type == "remote":
            self.__check_ipcamera_remote__(device)
        elif self.label == DeviceLabelType.watch:
            self.__check_watch__(device)

    def set_connect_type(self, device):
        pattern = r'^((25[0-5]|2[0-4]\d|[01]?\d\d?)\.){3}(25[0-5]|2[0-4]\d|[' \
                  r'01]?\d\d?)$'
        for item in device:
            if "label" in item.keys():
                self.label = item.get("label")
            if "com" in item.keys():
                self.device_connect_type = "local"
            if "ip" in item.keys():
                if re.match(pattern, item.get("ip")):
                    self.device_connect_type = "remote"
                else:
                    self.error_message = "Remote device ip not in right" \
                                         "format, please check user_config.xml"
                    LOG.error(self.error_message)
                    raise ParamError(self.error_message)
        if not self.label:
            self.error_message = "device label cannot be empty, " \
                                 "please check"
            LOG.error(self.error_message)
            raise ParamError(self.error_message)
        else:
            if self.label != DeviceLabelType.wifiiot and self.label != \
                    DeviceLabelType.ipcamera and self.label != \
                    DeviceLabelType.watch:
                self.error_message = "device label should be ipcamera or" \
                                     " wifiiot, please check"
                LOG.error(self.error_message)
                raise ParamError(self.error_message)
        if not self.device_connect_type:
            self.error_message = "device com or ip cannot be empty, " \
                                 "please check"
            LOG.error(self.error_message)
            raise ParamError(self.error_message)

    def __init_device__(self, device=None):
        if not device:
            LOG.error(
                "no available device, please config it in lite_config.xml.")
            raise DeviceError(
                "no available device, please config it in lite_config.xml.")

        self.__check_config__(device)
        self.__set_serial__(device)
        if self.device_connect_type == "remote":
            self.remote_device = RemoteController(device)
        else:
            self.local_device = LocalController(device)

    def connect(self):
        """
        connect the device

        """
        if self.device_connect_type == "remote":
            self.remote_device.connect()
        else:
            self.local_device.connect()

    def execute_command_with_timeout(self, command="", case_type="",
                                     timeout=TIMEOUT, receiver=None):
        """
        Executes command on the device.

        Parameters:
            command: the command to execute
            case_type: CTest or CppTest
            receiver: parser handler
            timeout: timeout for read result
        """
        try:
            if self.device_connect_type == "remote":
                filter_result, status, error_message = \
                    self.remote_device.execute_command_with_timeout(
                        command=command,
                        timeout=timeout,
                        receiver=receiver)
            else:
                filter_result, status, error_message = \
                    self.local_device.execute_command_with_timeout(
                        command=command,
                        case_type=case_type,
                        timeout=timeout,
                        receiver=receiver)
            LOG.debug("execute result:%s", filter_result)
            if not status:
                LOG.debug("error_message:%s", error_message)
            return filter_result, status, error_message
        except ExecuteTerminate:
            error_message = "Execute terminate."
            return "", False, error_message

    def close(self):
        """
        Unmount the testcase from device server and close the telnet connection
         with device server or close the local serial
        """
        if self.device_connect_type == "remote":
            return self.remote_device.close()
        else:
            return self.local_device.close()


class RemoteController:
    """
    Class representing an device lite remote device.
    Each object of this class represents one device lite remote device
    in xDevice.
    """

    def __init__(self, device):
        self.host = device[1].get("ip")
        self.port = int(device[1].get("port"))
        self.directory = device[1].get("dir")
        self.telnet = None

    def connect(self):
        """
        connect the device server

        """
        now_time = time.strftime('%Y-%m-%d %H:%M:%S',
                                 time.localtime(time.time()))
        try:
            if self.telnet:
                return self.telnet
            self.telnet = telnetlib.Telnet(self.host, self.port,
                                           timeout=TIMEOUT)
        except Exception as err_msgs:
            LOG.error('TIME: %s IP: %s  STATUS: telnet failed\n error:%s' % (
                now_time, self.host, str(err_msgs)))
            raise LiteDeviceConnectError("connect lite_device failed")
        time.sleep(2)
        self.telnet.set_debuglevel(0)
        return self.telnet

    def execute_command_with_timeout(self, command="", timeout=TIMEOUT,
                                     receiver=None):
        """
        Executes command on the device.

        Parameters:
            command: the command to execute
            timeout: timeout for read result
            receiver: parser handler
        """
        return LiteHelper.execute_remote_cmd_with_timeout(
            self.telnet, command, timeout, receiver)

    def close(self):
        """
        Unmount the testcase directory from device server and close the telnet
        connection with device server
        """
        error_message = ""
        try:
            if not self.telnet:
                return
            self.telnet.close()
            self.telnet = None
        except (ConnectionError, Exception):
            error_message = "Remote device is disconnected abnormally"
            LOG.error(error_message)
        return error_message


class LocalController:
    def __init__(self, device):
        """
        Init Local device.
        Parameters:
            device: local device
        """
        self.com_dict = {}
        for item in device:
            if "com" in item.keys():
                if "type" in item.keys() and ComType.cmd_com == item.get(
                        "type"):
                    self.com_dict[ComType.cmd_com] = ComController(item)
                elif "type" in item.keys() and ComType.deploy_com == item.get(
                        "type"):
                    self.com_dict[ComType.deploy_com] = ComController(item)

    def connect(self, key=ComType.cmd_com):
        """
        Open serial.
        """
        try:
            self.com_dict.get(key).connect()
        except Exception:
            raise LiteDeviceConnectError("connect serial failed")

    def flush_input(self, key=ComType.cmd_com):
        self.com_dict.get(key).flush_input()

    def close(self, key=ComType.cmd_com):
        """
        Close serial.
        """
        if self.com_dict and self.com_dict.get(key):
            self.com_dict.get(key).close()

    def execute_command_with_timeout(self, **kwargs):
        """
        Execute command on the serial and read all the output from the serial.
        """
        args = kwargs
        key = args.get("key", ComType.cmd_com)
        command = args.get("command", None)
        case_type = args.get("case_type", "")
        receiver = args.get("receiver", None)
        timeout = args.get("timeout", TIMEOUT)
        return self.com_dict.get(key).execute_command_with_timeout(
            command=command, case_type=case_type,
            timeout=timeout, receiver=receiver)


class ComController:
    def __init__(self, device):
        """
        Init serial.
        Parameters:
            device: local com
        """
        self.serial_port = device.get("com") if device.get("com") else None
        self.baund_rate = int(device.get("baund_rate")) if device.get(
            "baund_rate") else 115200
        self.is_open = False
        self.timeout = int(device.get("timeout")) if device.get(
            "timeout") else TIMEOUT
        self.directory = device.get("dir") if device.get("dir") else None
        self.com = None

    def connect(self):
        """
        Open serial.
        """
        try:
            if not self.is_open:
                import serial
                self.com = serial.Serial(self.serial_port,
                                         baudrate=self.baund_rate,
                                         timeout=self.timeout)
                self.is_open = True
        except Exception:
            LOG.error(
                "connect %s serial failed, please make sure this port is not "
                "occupied." % self.serial_port)
            raise LiteDeviceConnectError("connect serial failed")

    def flush_input(self):
        self.com.flushInput()

    def close(self):
        """
        Close serial.
        """
        error_message = ""
        try:
            if not self.com:
                return
            if self.is_open:
                self.com.close()
            self.is_open = False
        except (ConnectionError, Exception):
            error_message = "Local device is disconnected abnormally"
            LOG.error(error_message)
        return error_message

    def execute_command_with_timeout(self, **kwargs):
        """
        Execute command on the serial and read all the output from the serial.
        """
        return LiteHelper.execute_local_cmd_with_timeout(self.com, **kwargs)

    def execute_command(self, command):
        """
        Execute command on the serial and read all the output from the serial.
        """
        LiteHelper.execute_local_command(self.com, command)
