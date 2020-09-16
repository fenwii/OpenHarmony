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

import datetime
import platform
import signal
import os
import json
import time
import subprocess
import re
from dataclasses import dataclass

from json import JSONDecodeError
from shutil import copyfile
from threading import Timer
from _core.constants import CKit
from _core.exception import ExecuteTerminate
from _core.exception import ParamError
from _core.logger import platform_logger
from _core.plugin import Plugin

TIMEOUT = 90
MAX_VALID_POSITION = 454
LOG = platform_logger("UiKitLite")


def timeout_callback(proc, timeout):
    try:
        timeout.is_timeout = True
        LOG.error("Error: execute command timeout.")
        LOG.error(proc.pid)
        if platform.system() != "Windows":
            os.killpg(proc.pid, signal.SIGKILL)
        else:
            subprocess.call(
                ["C:\\Windows\\System32\\taskkill", "/F", "/T", "/PID",
                 str(proc.pid)],
                shell=False)
    except (FileNotFoundError, KeyboardInterrupt, AttributeError) as error:
        LOG.exception("timeout callback exception: %s" % error)


def get_dump_str(dump_file):
    dump_str = ""
    if os.path.exists(dump_file):
        with open(dump_file, "r") as json_content:
            dump_str = json_content.read()
    return dump_str


def get_center_position(parsed_dict, attr_name, attr_value):
    if attr_value == parsed_dict.get(attr_name, ""):
        return _calculate_center_position(parsed_dict)

    child_dicts = parsed_dict.get("child", [])
    for child_dict in child_dicts:
        x_center, y_center = get_center_position(child_dict, attr_name,
                                                 attr_value)
        if check_position(x_center, y_center):
            return x_center, y_center

    return -1, -1


def check_position(x_position, y_position):
    return (0 <= x_position <= MAX_VALID_POSITION) and \
           (0 <= y_position <= MAX_VALID_POSITION)


def copy_file(destination_path, screen_file_name):
    from xdevice import Variables
    abs_paths = [Variables.exec_dir, Variables.top_dir, Variables.modules_dir]
    for path in abs_paths:
        if path:
            for file_name in os.listdir(path):
                if file_name.endswith(".bin") and os.path.exists(os.path.join(
                        path, file_name)):
                    dst_file = "%s%s" % (os.path.join(
                        destination_path, screen_file_name), ".bin")
                    copyfile(os.path.join(path, file_name), dst_file)
                    os.remove(os.path.join(path, file_name))
                    break


def _calculate_center_position(parsed_dict):
    x_value = parsed_dict.get("x", -1)
    y_value = parsed_dict.get("y", -1)
    if not check_position(x_value, y_value):
        LOG.info("error (x, y) value, (%s, %s)" % (x_value, y_value))
        return -1, -1
    width = parsed_dict.get("width", -1)
    height = parsed_dict.get("height", -1)
    if not check_position(width, height):
        LOG.info("error (width, height) value, (%s, %s)" % (width, height))
        return -1, -1
    return min((x_value + width / 2), 454), min((y_value + height / 2), 454)


def get_center(dump_str, attr_name, attr_value):
    """execute hd.click method

    Parameters:
        dump_str: json string
        attr_name: target attribute name like 'id' or 'text'
        attr_value: target attribute value

    Return:
        0: success  1: fail
    """
    try:
        parsed_dict = json.loads(dump_str, encoding="utf-8")
    except JSONDecodeError as error:
        LOG.info("format error, %s" % error.args)
        return 1
    x_center, y_center = get_center_position(parsed_dict, attr_name,
                                             attr_value)
    LOG.info("(x_center, y_center) value, (%s, %s)" % (x_center, y_center))
    if check_position(x_center, y_center):
        return True, (x_center, y_center)
    else:
        LOG.info("no valid center position (%s, %s)" % (x_center, y_center))
        return False, None


def get_hdc_command(command, shell=True):
    if shell:
        return " ".join(["hdc", "shell", command])
    else:
        return " ".join(["hdc", command])


def filter_json(result_str=""):
    result = "no such node"
    if result_str.find("{") != -1:
        result_str = result_str.replace("\n", "").strip()
        pattern = r"(.*)(\{.*\})(.*)"
        matcher = re.match(pattern, result_str)
        if matcher:
            return matcher.group(2)
    return result


@dataclass
class Timeout:
    is_timeout = False


@Plugin(type=Plugin.TEST_KIT, id=CKit.liteuikit)
class LiteUiKit:
    def __init__(self):
        pass

    def __set_device__(self, device):
        pass

    def __set_connect_type__(self, device):
        pass

    def __check_config__(self, config):
        pass

    def __setup__(self, device):
        pass

    def __teardown__(self, device):
        pass

    @staticmethod
    def execute_hdc_cmd_with_timeout(device, command, timeout=800,
                                     result_print=True):
        """
           Executes a command on the device with timeout.

           Parameters:
               device: device
               command: the command to execute
               timeout: time out value
               result_print:
        """
        from _core.environment.device_lite import get_hdc_path
        cmd = [get_hdc_path(), "-p", device.serial_port.upper().replace(
            "COM", "").strip()] + command.split(" ")
        ret_message = ""
        LOG.info("execute command: %s" % " ".join(cmd))

        start_time = datetime.datetime.now()
        LOG.info("starttime=%s with timeout=%s" % (
            start_time.strftime("%Y-%m-%d %H:%M:%S"), str(timeout)))

        proc = subprocess.Popen(
            cmd, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, shell=False,
            preexec_fn=os.setsid if platform.system() != 'Windows' else None)
        is_timeout = Timeout()
        proc_timer = Timer(timeout, timeout_callback, [proc, is_timeout])
        proc_timer.start()

        try:
            ret_message = LiteUiKit._result_hdc_out_process(
                proc, is_timeout, result_print)
        except (ExecuteTerminate, ValueError) as exception:
            LOG.exception("exception: %s", str(exception))
        finally:
            ret_message = "{}{}".format(
                ret_message, LiteUiKit._print_hdc_stdout(proc, result_print))
            error_message = LiteUiKit._print_hdc_stderr(proc, result_print)

            proc_timer.cancel()
            proc.stdout.close()
            proc.stderr.close()

        LOG.info("end time=%s delta=%s" % (
            datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"), str(
                (datetime.datetime.now() - start_time).seconds)))

        if proc.returncode == 0:
            LOG.info('Info: execute command success. command=%s', command)
            return_code = 0
        else:
            LOG.error('Error: execute command failed. command=%s', command)
            return_code = 1
        return ResultValue(return_code, error_message, ret_message)

    @staticmethod
    def _result_hdc_out_process(proc, timeout, result_print):
        result = ""
        from xdevice import Scheduler
        while proc.poll() is None:
            if not Scheduler.is_execute:
                raise ExecuteTerminate()
            line = proc.stdout.readline()
            line = line.strip()
            if isinstance(line, bytes):
                line = line.decode('utf-8', 'ignore').strip()
            if line != "":
                result = "%s%s%s" % (result, line, "\n")
                if result_print:
                    LOG.info(line)
            if timeout.is_timeout:
                LOG.info("timeout flag is True")
                timeout.is_timeout = False
                break
        return result

    @classmethod
    def _print_hdc_stdout(cls, proc, result_print=True):
        data = proc.stdout.read()
        if isinstance(data, bytes):
            data = data.decode('utf-8', 'ignore')
        if data != "":
            if not result_print:
                return data
            for line in data.rstrip("\n").split("\n"):
                LOG.info(line)
            return data.rstrip("\n")
        return ""

    @classmethod
    def _print_hdc_stderr(cls, proc, result_print=True):
        data = proc.stderr.read()
        if isinstance(data, bytes):
            data = data.decode('utf-8', 'ignore')
        if data != "":
            if not result_print:
                return data
            LOG.error("----------stderr info start------------")
            for error_message in data.rstrip("\n").split("\n"):
                LOG.error(error_message)
            LOG.error("----------stderr info ended------------")
            return data.rstrip("\n")
        return ""

    @staticmethod
    def click(device, x_coordinate, y_coordinate, timeout=800):
        press_command = "%s%s%s%s%s" % ("uievent ", str(x_coordinate), str(
            y_coordinate), " ", " PRESSDOWN")
        release_command = "%s%s%s%s%s" % ("uievent ", str(x_coordinate), " ",
                                          str(y_coordinate), " RELEASE")
        press_result = LiteUiKit.execute_hdc_cmd_with_timeout(
            device, get_hdc_command(press_command, True), timeout, True)
        if press_result.return_code == 0:
            time.sleep(timeout / 1000)
            release_result = LiteUiKit.execute_hdc_cmd_with_timeout(
                device, get_hdc_command(release_command, True), timeout, True)
            if release_result.return_code == 0:
                LOG.info("click success.")
                return True
        return False

    @staticmethod
    def click_id(device, node_id, timeout=800):
        if not node_id:
            raise ParamError("miss node id")
        status, point = LiteUiKit.ui_dump_id(
            device, node_id=node_id, timeout=timeout)
        if status:
            LiteUiKit.click(device, point[0], point[1], timeout)
        else:
            LOG.info("click failed")

    @staticmethod
    def click_text(device, text="", timeout=800):
        status = False
        if not text:
            raise ParamError("miss node text")
        dump_str = LiteUiKit.ui_dump_tree(
            device, timeout=timeout)
        if dump_str and text:
            status, point = get_center(dump_str, "text", text)
        if status:
            LiteUiKit.click(point[0], point[1], timeout)
        else:
            LOG.info("click failed")

    @staticmethod
    def screen_shot(device, screen_path, file_name, timeout=800):
        result_value = LiteUiKit.execute_hdc_cmd_with_timeout(
            device, get_hdc_command("screenshot"), timeout, True)
        if result_value.return_code == 0:
            retry_times = 2
            while retry_times > 0:
                command = "rfile user/log/screenshot.bin"
                if LiteUiKit.download_file(device, command, timeout=1400):
                    img_dir = os.path.join(screen_path, "img")
                    os.makedirs(img_dir, exist_ok=True)
                    copy_file(img_dir, file_name)
                    break
                retry_times -= 1
            LOG.info("screen shot success.")
            return True

    @staticmethod
    def ui_dump_id(device, **kwargs):
        args = kwargs
        node_id = args.get("node_id", "")
        timeout = args.get("timeout", "")
        dump_node_command = "%s%s" % ("uidump node ", str(node_id))
        dump_times = 5
        while dump_times > 0:
            dump_node_value = LiteUiKit.execute_hdc_cmd_with_timeout(
                device, get_hdc_command(dump_node_command), timeout, True)
            if dump_node_value.return_code == 0:
                result = filter_json(dump_node_value.return_message)
                if result != "no such node":
                    return get_center(result, "id", node_id)
            dump_times -= 1
        LOG.error("dump fail, please check node id")
        return None

    @staticmethod
    def ui_dump_tree(device, **kwargs):
        args = kwargs
        node_id = args.get("node_id", "")
        timeout = args.get("timeout", "")
        if node_id:
            dump_tree_command = "%s%s" % ("uidump tree ", node_id)
        else:
            dump_tree_command = "uidump tree"
        dump_tree_value = LiteUiKit.execute_hdc_cmd_with_timeout(
            device, get_hdc_command(dump_tree_command), timeout, True)
        if dump_tree_value.return_code == 0:
            dump_str = ""
            from _core.environment.device_lite import get_hdc_path
            local_path = get_hdc_path()
            retry_times = 2
            while retry_times > 0:
                command = "rfile user/log/dump_dom_tree.json"
                if LiteUiKit.download_file(device, command, timeout=1400):
                    with open(local_path, "r") as file_stream:
                        dump_str = file_stream.read()
                    break
                retry_times -= 1
            return dump_str
        else:
            LOG.error("dump failed")
            raise ParamError("dump failed")

    @staticmethod
    def swipe(device, start_point, end_point, timeout=800):
        if not isinstance(start_point, tuple) and not isinstance(
                end_point, tuple):
            raise ParamError(
                "The coordinates of the sliding point should be tuple")
        start_x, start_y = start_point
        end_x, end_y = end_point
        press_first_command = "%s%s%s%s%s" % ("uievent ", str(start_x), " ",
                                              str(start_y), " PRESSDOWN")
        press_end_command = "%s%s%s%s" % ("uievent ", str(end_x), str(end_y),
                                          " PRESSDOWN")
        release_end_command = "%s%s%s%s%s" % ("uievent ", str(end_x), " ",
                                              str(end_y), " RELEASE")
        press_first_point_result = LiteUiKit.execute_hdc_cmd_with_timeout(
            device, get_hdc_command(press_first_command, True), timeout)
        if press_first_point_result.return_code == 0:
            time.sleep(timeout / 1000)
            press_medium_point_result = \
                LiteUiKit.execute_hdc_cmd_with_timeout(
                    device, get_hdc_command(press_end_command, True),
                    timeout, True)
            if press_medium_point_result.return_code == 0:
                time.sleep(timeout / 1000)
                press_end_point_result = \
                    LiteUiKit.execute_hdc_cmd_with_timeout(
                        device, get_hdc_command(release_end_command, True),
                        timeout, True)
                if press_end_point_result.return_code == 0:
                    LOG.info("swipe success.")
                    return True
        return False

    @staticmethod
    def long_press(device, x_coordinate, y_coordinate, timeout=1200):
        press_command = "%s%s%s%s%s" % ("uievent ", str(x_coordinate), " ",
                                        str(y_coordinate), " PRESSDOWN")
        release_command = "%s%s%s%s%s" % ("uievent ", str(x_coordinate), " ",
                                          str(y_coordinate), " RELEASE")
        press_result = LiteUiKit.execute_hdc_cmd_with_timeout(
            device, get_hdc_command(press_command, True), timeout, True)
        if press_result.return_code == 0:
            time.sleep(timeout / 1000)
            release_result = LiteUiKit.execute_hdc_cmd_with_timeout(
                device, get_hdc_command(release_command, True), timeout, True)
            if release_result.return_code == 0:
                LOG.info("press success.")
                return True
        return False

    @staticmethod
    def download_file(device, command, timeout=1200):
        press_result = LiteUiKit.execute_hdc_cmd_with_timeout(
            device, command, timeout, True)
        if press_result.return_code == 0:
            LOG.info("download file success.")
            return True
        return False


class ResultValue(object):
    def __init__(self, return_code, error_message="", return_message=""):
        self.return_code = return_code
        self.error_message = error_message
        self.return_message = return_message

    def set_return_code(self, ret_code):
        self.return_code = ret_code

    def set_error_message(self, error_message):
        self.error_message = error_message

    def set_return_message(self, return_message):
        self.return_message = return_message

    def get_return_code(self):
        return self.return_code

    def get_error_message(self):
        return self.error_message

    def get_return_message(self):
        return self.return_message
