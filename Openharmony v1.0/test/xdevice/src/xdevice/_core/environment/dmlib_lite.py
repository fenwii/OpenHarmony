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

import time
import re

from _core.constants import DeviceTestType
from _core.exception import ExecuteTerminate
from _core.exception import LiteDeviceConnectError
from _core.exception import LiteDeviceExecuteCommandError
from _core.logger import platform_logger


__all__ = ["generate_report", "LiteHelper"]

CPP_TEST_STANDARD_SIGN = "[==========]"
CPP_TEST_END_SIGN = "Global test environment tear-down"
CPP_SYS_STANDARD_SIGN = " #"
CPP_ERR_MESSAGE = "[ERR]No such file or directory: "

TIMEOUT = 90
CTEST_STANDARD_SIGN = "Start to run test suite"
AT_CMD_ENDS = "OK"
CTEST_END_SIGN = "Framework finished."
PATTERN = re.compile(r'\x1B(\[([0-9]{1,2}(;[0-9]{1,2})*)?m)*')
LOG = platform_logger("DmlibLite")


def check_read_test_end(result=None, input_command=None):
    if input_command not in result:
        return False
    index = result.find(input_command) + len(input_command)
    result_output = result[index:]
    if input_command.startswith("./"):
        if result_output.find(CPP_TEST_STANDARD_SIGN) != -1:
            if result_output.count(CPP_TEST_STANDARD_SIGN) == 2 or \
                    result_output.find(CPP_TEST_END_SIGN) != -1:
                return True
        if result_output.find(CPP_TEST_STANDARD_SIGN) == -1 and \
                ("test pass" in result_output.lower() or
                 "test fail" in result_output.lower()):
            return True
        if "%s%s" % (CPP_ERR_MESSAGE, input_command[2:]) in result_output:
            LOG.error("execute file not exist, result is %s" % result_output)
            raise LiteDeviceExecuteCommandError("execute file not exist")
    else:
        if " #" in result_output:
            if input_command == "reboot" or input_command == "reset":
                return False
            if input_command.startswith("mount"):
                if "Mount nfs finished." not in result_output:
                    return False
            return True
    return False


def generate_report(receiver, result):
    if result and receiver:
        if result:
            receiver.__read__(result)
            receiver.__done__()


def get_current_time():
    current_time = time.time()
    local_time = time.localtime(current_time)
    data_head = time.strftime("%Y-%m-%d %H:%M:%S", local_time)
    millisecond = (current_time - int(current_time)) * 1000
    return "%s.%03d" % (data_head, millisecond)


class LiteHelper:
    @staticmethod
    def execute_remote_cmd_with_timeout(telnet, command="", timeout=TIMEOUT,
                                        receiver=None):
        """
        Executes command on the device.

        Parameters:
            telnet:
            command: the command to execute
            timeout: timeout for read result
            receiver: parser handler
        """
        from xdevice import Scheduler
        time.sleep(2)
        start_time = time.time()
        status = True
        error_message = ""
        result = ""
        LOG.info("execute command shell %s with timeout %s" %
                 (command, str(timeout)))
        if not telnet:
            raise LiteDeviceConnectError("remote device is not connected.")

        telnet.write(command.encode('ascii') + b"\n")

        expect_result = [bytes(CPP_TEST_STANDARD_SIGN, encoding="utf8"),
                         bytes(CPP_SYS_STANDARD_SIGN, encoding="utf8"),
                         bytes(CPP_TEST_END_SIGN, encoding="utf8")]
        while time.time()-start_time < timeout:
            if not Scheduler.is_execute:
                raise ExecuteTerminate()
            _, _, data = telnet.expect(expect_result, timeout=1)
            data = PATTERN.sub('', data.decode('gbk', 'ignore'))
            result = result + data.replace("\r", "")

            if check_read_test_end(result, command):
                break
        else:
            error_message = "execute command with timeout=%s " % command
            LOG.debug("error_message=%s" % error_message)
            status = False

        if receiver:
            if command in result:
                index = result.find(command) + len(command)
                result_output = result[index:]
            else:
                result_output = result
            generate_report(receiver, result_output)

        return result, status, error_message

    @staticmethod
    def read_local_output_test(com=None, command=None, timeout=TIMEOUT,
                               receiver=None):
        input_command = command
        error_message = ""
        start_time = time.time()
        result = ""
        status = True
        from xdevice import Scheduler

        while time.time()-start_time < timeout:
            if not Scheduler.is_execute:
                raise ExecuteTerminate()
            data = com.readline().decode('gbk', errors='ignore')
            data = PATTERN.sub('', data)
            result = "{}{}".format(result, data.replace("\r", ""))
            if check_read_test_end(result, input_command):
                break
        else:
            error_message = "execute command with timeout=%s " % command
            LOG.debug("error_message:%s" % error_message)
            status = False

        if receiver:
            if command in result:
                index = result.find(command) + len(command)
                result_output = result[index:]
            else:
                result_output = result
            generate_report(receiver, result_output)

        LOG.info('Info: execute command success')
        return result, status, error_message

    @staticmethod
    def read_local_output_ctest(com=None, command=None, timeout=TIMEOUT,
                                receiver=None):
        result = ""
        input_command = command

        start = time.time()
        from xdevice import Scheduler
        while True:
            if not Scheduler.is_execute:
                raise ExecuteTerminate()
            data = com.readline().decode('gbk', errors='ignore')
            data = PATTERN.sub('', data)
            if isinstance(input_command, list):
                data = "{} {}".format(get_current_time(), data)
                result = "{}{}".format(result, data.replace("\r", ""))
                if re.search(r"\d+\s+Tests\s+\d+\s+Failures\s+\d+\s+"
                             r"Ignored", data):
                    start = time.time()
                if (int(time.time()) - int(start)) > timeout:
                    break
            else:
                result = "{}{}".format(
                    result, data.replace("\r", "").replace("\n", "").strip())
                if AT_CMD_ENDS in data:
                    return result, True, ""
                if (int(time.time()) - int(start)) > timeout:
                    return result, False, ""

        result = PATTERN.sub('', result)
        if receiver:
            result = "{}{}".format(
                result, "{} {}".format(get_current_time(), CTEST_END_SIGN))
            generate_report(receiver, result)
        LOG.info('Info: execute command success')
        return result, True, ""

    @staticmethod
    def read_local_output(com=None, command=None, case_type="",
                          timeout=TIMEOUT, receiver=None):
        if case_type == DeviceTestType.ctest_lite:
            return LiteHelper.read_local_output_ctest(com, command,
                                                      timeout, receiver)
        else:
            return LiteHelper.read_local_output_test(com, command,
                                                     timeout, receiver)

    @staticmethod
    def execute_local_cmd_with_timeout(com, **kwargs):
        """
        Execute command on the serial and read all the output from the serial.
        """
        args = kwargs
        command = args.get("command", None)
        input_command = command
        case_type = args.get("case_type", "")
        timeout = args.get("timeout", TIMEOUT)
        receiver = args.get("receiver", None)
        if not com:
            raise LiteDeviceConnectError("local device is not connected.")

        LOG.info("%s \n execute command shell %s with timeout %s" %
                 (com, command, str(timeout)))
        if isinstance(command, str):
            command = command.encode("utf-8")
            if command[-2:] != b"\r\n":
                command = command.rstrip() + b'\r\n'
                com.write(command)
        else:
            com.write(command)
        return LiteHelper.read_local_output(
            com, command=input_command, case_type=case_type, timeout=timeout,
            receiver=receiver)

    @staticmethod
    def execute_local_command(com, command):
        """
        Execute command on the serial and read all the output from the serial.
        """
        if not com:
            raise LiteDeviceConnectError("local device is not connected.")

        LOG.info(
            "%s \n execute command shell %s" % (com, command))
        command = command.encode("utf-8")
        if command[-2:] != b"\r\n":
            command = command.rstrip() + b'\r\n'
            com.write(command)
