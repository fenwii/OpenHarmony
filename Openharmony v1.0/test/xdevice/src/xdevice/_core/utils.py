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
import socket
import time
import platform
import argparse
import subprocess
import signal
import uuid
import json
from tempfile import NamedTemporaryFile

from _core.executor.listener import SuiteResult
from _core.driver.parser_lite import ShellHandler
from _core.exception import ParamError
from _core.logger import platform_logger
from _core.report.suite_reporter import SuiteReporter
from _core.plugin import get_plugin
from _core.plugin import Plugin

LOG = platform_logger("Utils")


def get_filename_extension(file_path):
    _, fullname = os.path.split(file_path)
    filename, ext = os.path.splitext(fullname)
    return filename, ext


def unique_id(type_name, value):
    return "{}_{}_{:0>8}".format(type_name, value,
                                 str(uuid.uuid1()).split("-")[0])


def start_standing_subprocess(cmd, pipe=subprocess.PIPE, return_result=False):
    """Starts a non-blocking subprocess that is going to continue running after
    this function returns.

    A subprocess group is actually started by setting sid, so we can kill all
    the processes spun out from the subprocess when stopping it. This is
    necessary in case users pass in pipe commands.

    Args:
        cmd: Command to start the subprocess with.
        pipe: pipe to get execution result
        return_result: return execution result or not

    Returns:
        The subprocess that got started.
    """
    sys_type = platform.system()
    process = subprocess.Popen(cmd, stdout=pipe, shell=False,
                               preexec_fn=None if sys_type == "Windows"
                               else os.setsid)
    if not return_result:
        return process
    else:
        rev = process.stdout.read()
        return rev.decode("utf-8").strip()


def stop_standing_subprocess(process):
    """Stops a subprocess started by start_standing_subprocess.

    Catches and ignores the PermissionError which only happens on Macs.

    Args:
        process: Subprocess to terminate.
    """
    try:
        sys_type = platform.system()
        signal_value = signal.SIGINT if sys_type == "Windows" \
            else signal.SIGTERM
        os.kill(process.pid, signal_value)
    except (PermissionError, AttributeError, FileNotFoundError,
            SystemError) as error:
        LOG.error("stop standing subprocess error '%s'" % error)


def get_decode(stream):
    if not isinstance(stream, str) and not isinstance(stream, bytes):
        ret = str(stream)
    else:
        try:
            ret = stream.decode("utf-8", errors="ignore")
        except (ValueError, AttributeError, TypeError):
            ret = str(stream)
    return ret


def is_proc_running(pid, name=None):
    if platform.system() == "Windows":
        proc_sub = subprocess.Popen(["C:\\Windows\\System32\\tasklist"],
                                    stdout=subprocess.PIPE,
                                    shell=False)
        proc = subprocess.Popen(["C:\\Windows\\System32\\findstr", "%s" % pid],
                                stdin=proc_sub.stdout,
                                stdout=subprocess.PIPE, shell=False)
    else:
        proc_sub = subprocess.Popen(["/bin/ps", "-ef"],
                                    stdout=subprocess.PIPE,
                                    shell=False)
        proc = subprocess.Popen(["/bin/grep", "%s" % pid],
                                stdin=proc_sub.stdout,
                                stdout=subprocess.PIPE, shell=False)
    (out, _) = proc.communicate()
    out = get_decode(out).strip()
    if out == "":
        return False
    else:
        return True if name is None else out.find(name) != -1


def exec_cmd(cmd, timeout=5 * 60, error_print=True):
    """
    Executes commands in a new shell. Directing stderr to PIPE.

    This is fastboot's own exe_cmd because of its peculiar way of writing
    non-error info to stderr.

    Args:
        cmd: A sequence of commands and arguments.
        timeout: timeout for exe cmd.
        error_print: print error output or not.

    Returns:
        The output of the command run.
    """

    sys_type = platform.system()
    if sys_type == "Windows":
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, shell=False)
    elif sys_type == "Linux" or sys_type == "Darwin":
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, shell=False,
                                preexec_fn=os.setsid)  # @UndefinedVariable
    else:
        return
    try:
        (out, err) = proc.communicate(timeout=timeout)
        err = get_decode(err).strip()
        out = get_decode(out).strip()
        if err and error_print:
            LOG.exception(err)
        return err if err else out

    except (TimeoutError, KeyboardInterrupt, AttributeError, ValueError):
        sys_type = platform.system()
        if sys_type == "Windows":
            os.kill(proc.pid, signal.SIGINT)
        elif sys_type == "Linux" or sys_type == "Darwin":
            os.killpg(proc.pid, signal.SIGTERM)


def create_dir(path):
    """Creates a directory if it does not exist already.

    Args:
        path: The path of the directory to create.
    """
    full_path = os.path.abspath(os.path.expanduser(path))
    if not os.path.exists(full_path):
        os.makedirs(full_path, exist_ok=True)


def get_config_value(key, config_dict, is_list=True, default=None):
    if not isinstance(config_dict, dict):
        return default

    value = config_dict.get(key, "")
    if isinstance(value, bool):
        return value

    if not value:
        if default:
            return default
        return [] if is_list else ""

    if isinstance(value, list):
        return value if is_list else value[0]
    return [value] if is_list else value


def get_file_absolute_path(input_name, paths=None, alt_dir=None):
    abs_paths = set(paths) if paths else set()
    _update_paths(abs_paths)

    for path in abs_paths:
        if alt_dir:
            file_path = os.path.join(path, alt_dir, input_name)
            if os.path.exists(file_path):
                return os.path.abspath(file_path)

        file_path = os.path.join(path, input_name)
        if os.path.exists(file_path):
            return os.path.abspath(file_path)

    err_msg = "The file {} does not exist".format(input_name)
    LOG.error(err_msg)

    if alt_dir:
        LOG.debug("alt_dir is %s" % alt_dir)
    LOG.debug("paths is:")
    for path in abs_paths:
        LOG.debug(path)
    raise ParamError(err_msg)


def _update_paths(paths):
    from xdevice import Variables
    resource_dir = "resource"
    testcases_dir = "testcases"

    need_add_path = set()
    for path in paths:
        if not os.path.exists(path):
            continue
        head, tail = os.path.split(path)
        if not tail:
            head, tail = os.path.split(head)
        if tail in [resource_dir, testcases_dir]:
            need_add_path.add(head)
    paths.update(need_add_path)

    inner_dir = os.path.abspath(os.path.join(Variables.exec_dir,
                                             testcases_dir))
    top_inner_dir = os.path.abspath(os.path.join(Variables.top_dir,
                                                 testcases_dir))
    res_dir = os.path.abspath(os.path.join(Variables.exec_dir, resource_dir))
    top_res_dir = os.path.abspath(os.path.join(Variables.top_dir,
                                               resource_dir))
    paths.update([inner_dir, res_dir, top_inner_dir, top_res_dir,
                  Variables.exec_dir, Variables.top_dir])


def modify_props(device, local_prop_file, target_prop_file, new_props):
    """To change the props if need
    Args:
        device: the device to modify props
        local_prop_file : the local file to save the old props
        target_prop_file : the target prop file to change
        new_props  : the new props
    Returns:
        True : prop file changed
        False : prop file no need to change
    """
    is_changed = False
    device.pull_file(target_prop_file, local_prop_file)
    old_props = {}
    changed_prop_key = []
    lines = []
    with open(local_prop_file, 'r') as old_file:
        lines = old_file.readlines()
        if lines:
            lines[-1] = lines[-1] + '\n'
        for line in lines:
            line = line.strip()
            if not line.startswith("#") and line.find("=") > 0:
                key_value = line.split("=")
                if len(key_value) == 2:
                    old_props[line.split("=")[0]] = line.split("=")[1]

    for key, value in new_props.items():
        if key not in old_props.keys():
            lines.append("".join([key, "=", value, '\n']))
            is_changed = True
        elif old_props.get(key) != value:
            changed_prop_key.append(key)
            is_changed = True

    if is_changed:
        local_temp_prop_file = NamedTemporaryFile(mode='w', prefix='build',
                                                  suffix='.tmp', delete=False)
        for index, line in enumerate(lines):
            if not line.startswith("#") and line.find("=") > 0:
                key = line.split("=")[0]
                if key in changed_prop_key:
                    lines[index] = "".join([key, "=", new_props[key], '\n'])
        local_temp_prop_file.writelines(lines)
        local_temp_prop_file.close()
        device.push_file(local_temp_prop_file.name, target_prop_file)
        device.execute_shell_command(" ".join(["chmod 644", target_prop_file]))
        LOG.info("Changed the system property as required successfully")
        os.remove(local_temp_prop_file.name)

    return is_changed


def get_device_log_file(report_path, serial=None, log_name="device_log"):
    from xdevice import Variables
    log_path = os.path.join(report_path, Variables.report_vars.log_dir)
    os.makedirs(log_path, exist_ok=True)

    serial = serial or time.time_ns()
    device_file_name = "{}_{}.log".format(log_name, serial)
    device_log_file = os.path.join(log_path, device_file_name)
    return device_log_file


def check_result_report(report_path, report_file, error_message="",
                        report_name=""):
    if os.path.exists(report_file):
        return report_file
    result_dir = os.path.join(report_path, "result")
    os.makedirs(result_dir, exist_ok=True)
    LOG.error("report %s not exist, create empty report under %s" % (
        report_file, result_dir))

    suite_name = report_name
    if not suite_name:
        suite_name, _ = get_filename_extension(report_file)
    suite_result = SuiteResult()
    suite_result.suite_name = suite_name
    suite_result.stacktrace = error_message
    suite_reporter = SuiteReporter([(suite_result, [])], suite_name,
                                   result_dir)
    suite_reporter.create_empty_report()
    return "%s.xml" % os.path.join(result_dir, suite_name)


def is_config_str(content):
    return True if "{" in content and "}" in content else False


def get_version():
    from xdevice import Variables
    ver = ''
    ver_file_path = os.path.join(Variables.res_dir, 'version.txt')
    if not os.path.isfile(ver_file_path):
        return ver

    with open(ver_file_path, mode='r', encoding='UTF-8') as ver_file:
        line = ver_file.readline()
        if '-v' in line:
            ver = line.strip().split('-')[1]
            ver = ver.split(':')[0]

    return ver


def get_instance_name(instance):
    return instance.__class__.__name__


def convert_ip(origin_ip):
    addr = origin_ip.strip().split(".")
    if len(addr) == 4:
        return "{}.{}.{}.{}".format(
            addr[0], '*'*len(addr[1]), '*'*len(addr[2]), addr[-1])
    else:
        return origin_ip


def convert_port(port):
    if len(port) >= 2:
        return "{}**{}".format(port[0], port[-1])
    else:
        return "{}**".format(port)


def convert_serial(serial):
    if serial.startswith("local_"):
        return "local_{}".format('*'*(len(serial)-6))
    elif serial.startswith("remote_"):
        return "remote_{}".format(convert_ip(serial.split("_")[1]))
    else:
        length = len(serial)//3
        return "{}{}{}".format(
            serial[0:length], "*"*(len(serial)-length*2), serial[-length:])


def get_shell_handler(request, parser_type):
    suite_name = request.root.source.test_name
    parsers = get_plugin(Plugin.PARSER, parser_type)
    parser_instances = []
    for listener in request.listeners:
        listener.device_sn = request.config.environment.devices[0].device_sn
    for parser in parsers:
        parser_instance = parser.__class__()
        parser_instance.suite_name = suite_name
        parser_instance.listeners = request.listeners
        parser_instances.append(parser_instance)
    handler = ShellHandler(parser_instances)
    return handler


def get_kit_instances(json_config, resource_path, testcases_path):
    from _core.testkit.json_parser import JsonParser
    kit_instances = []
    if not isinstance(json_config, JsonParser):
        return kit_instances
    for kit in json_config.config.kits:
        kit["paths"] = [resource_path, testcases_path]
        kit_type = kit.get("type", "")
        if get_plugin(plugin_type=Plugin.TEST_KIT, plugin_id=kit_type):
            test_kit = \
                get_plugin(plugin_type=Plugin.TEST_KIT, plugin_id=kit_type)[0]
            test_kit_instance = test_kit.__class__()
            test_kit_instance.__check_config__(kit)
            kit_instances.append(test_kit_instance)
        else:
            raise ParamError("kit %s not exists" % kit_type)
    return kit_instances


def check_path_legal(path):
    if path and " " in path:
        return "\"%s\"" % path
    return path


def get_local_ip():
    sys_type = platform.system()
    if sys_type == "Windows":
        _list = socket.gethostbyname_ex(socket.gethostname())
        _list = _list[2]
        for ip_add in _list:
            if ip_add.startswith("10."):
                return ip_add

        return socket.gethostbyname(socket.getfqdn(socket.gethostname()))
    elif sys_type == "Darwin":
        hostname = socket.getfqdn(socket.gethostname())
        return socket.gethostbyname(hostname)
    elif sys_type == "Linux":
        real_ip = "/%s/%s" % ("hostip", "realip")
        if os.path.exists(real_ip):
            srw = None
            try:
                import codecs
                srw = codecs.open(real_ip, "r", "utf-8")
                lines = srw.readlines()
                local_ip = str(lines[0]).strip()
            except (IOError, ValueError) as error_message:
                LOG.error(error_message)
                local_ip = "127.0.0.1"
            finally:
                if srw is not None:
                    srw.close()
        else:
            local_ip = "127.0.0.1"
        return local_ip


class SplicingAction(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace, self.dest, " ".join(values))


def get_test_component_version(config):
    try:
        paths = [config.resource_path, config.testcases_path]
        test_file = get_file_absolute_path("test_component.json", paths)

        with open(test_file, encoding="utf-8") as file_content:
            json_content = json.load(file_content)
            version = json_content.get("version", "")
            return version
    except (ParamError, ValueError) as error:
        LOG.error(
            "The exception {} happened when get version".format(
                error))
    return ""
