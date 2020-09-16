#!/usr/bin/env python
# -*- coding: utf-8 -*-

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
import argparse

from .hdf_tool_commands import HdfToolCommands
from .hdf_tool_argument_parser import HdfToolArgumentParser
from command_line.hdf_command_error_code import CommandErrorCode
from hdf_tool_exception import HdfToolException


class Message(object):
    TYPE_REQ = 'request'
    TYPE_QUIT = 'quit'
    TYPE_ERROR = 'error'
    TYPE_SUCCESS = 'success'

    def __init__(self, msg_type, content):
        self.msg_type = msg_type
        self.content = content

    def is_quit(self):
        return self.msg_type.lower() == Message.TYPE_ERROR


def pack_message(msg_type, content, err_code=None):
    body = bytearray(content, 'utf-8')
    if not err_code:
        header = bytearray('{},{}\n'.format(msg_type, len(body)), 'utf-8')
    else:
        header = bytearray('{},{},{}\n'.format(msg_type, len(body), err_code),
                           'utf-8')
    bytes_packet = bytearray().join([header, body])
    return bytes_packet


def decode_header(header):
    header_parts = header.split(',')
    if len(header_parts) < 2:
        return -1, '', 0
    msg_type = header_parts[0]
    body_len = int(header_parts[1])
    return 0, msg_type, body_len


def decode_body(body):
    arg_parser = HdfToolArgumentParser()
    arg_parser.add_argument('cmd')
    arg_parser.add_argument('remainder_args', nargs=argparse.REMAINDER)
    args = arg_parser.parse_args(body.strip().split(' '))
    remainder = [arg for arg in args.remainder_args if len(arg) != 0]
    return args.cmd, remainder


class HdfCommandLineServer(object):
    def __init__(self, input_obj, output_obj):
        self.input_obj = input_obj
        self.output_obj = output_obj
        self.commands = HdfToolCommands()

    def _send_back(self, msg_type, content, error_code=None):
        message_bytes = pack_message(msg_type, content, error_code)
        self.output_obj.write(message_bytes)
        self.output_obj.flush()

    def _send_back_success(self, content):
        self._send_back(Message.TYPE_SUCCESS, content)

    def _send_back_error(self, error_code, content):
        self._send_back(Message.TYPE_ERROR, content, error_code)

    def _read_header(self):
        head_bytes = self.input_obj.readline()
        msg_header = str(head_bytes, encoding="utf-8")
        return decode_header(msg_header)

    def _read_body(self, body_len):
        body_bytes = self.input_obj.read(body_len)
        body = str(body_bytes, encoding='utf-8')
        return decode_body(body)

    def run(self):
        while True:
            try:
                ret, msg_type, body_len = self._read_header()
                if ret != 0:
                    err_code = CommandErrorCode.MESSAGE_FORMAT_WRONG
                    self._send_back_error(err_code, 'header wrong')
                    continue
                if msg_type == Message.TYPE_QUIT:
                    self._send_back_success('Bye bye!')
                    break
                if body_len < 0:
                    err_code = CommandErrorCode.MESSAGE_FORMAT_WRONG
                    self._send_back_error(err_code, 'body len wrong')
                    continue
                cmd, args = self._read_body(body_len)
                ret = self.commands.run(cmd, args)
                if ret:
                    self._send_back_success(str(ret))
                else:
                    self._send_back_success('')
            except HdfToolException as exc:
                try:
                    self._send_back_error(exc.error_code, exc.exc_msg)
                except OSError:
                    sys.exit(-1)
            except Exception as exc:
                try:
                    self._send_back_error(CommandErrorCode.UNKNOWN_ERROR,
                                          str(exc))
                except OSError:
                    sys.exit(-1)
