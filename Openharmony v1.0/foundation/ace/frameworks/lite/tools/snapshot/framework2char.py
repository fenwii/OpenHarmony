# -*- coding: utf-8 -*-
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

import os

HMF_ACE_BASE_PATH = os.path.join("..", "..")
FRAMEWORK_SNAPSHOT_FILE_PATH = os.path.join(
    HMF_ACE_BASE_PATH, "packages", "runtime-core",
    "build", "framework.min.bc")
SNAPSHOT_OUTPUT_C_FILE_PATH = os.path.join(
    HMF_ACE_BASE_PATH, "src", "core", "base", "framework_min_bc.h")

FRAMEWORK_JS_FILE_PATH = os.path.join(
    HMF_ACE_BASE_PATH, "packages", "runtime-core",
    "build", "framework.min.js")
JS_OUTPUT_C_FILE_PATH = os.path.join(
    HMF_ACE_BASE_PATH, "src", "core", "base", "framework_min_js.h")


def output_copyright(output):
    output.write("/*\n")
    output.write(" * Copyright (c) 2020 Huawei Device Co., Ltd.\n")
    output.write(" * Licensed under the Apache License, Version 2.0")
    output.write(" (the \"License\");\n")
    output.write(" * you may not use this file except in compliance ")
    output.write("with the License.\n")
    output.write(" * You may obtain a copy of the License at\n")
    output.write(" *\n")
    output.write(" *     http://www.apache.org/licenses/LICENSE-2.0\n")
    output.write(" *\n")
    output.write(" * Unless required by applicable law or agreed to in ")
    output.write("writing, software\n")
    output.write(" * distributed under the License is distributed on an ")
    output.write("\"AS IS\" BASIS,\n")
    output.write(" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either ")
    output.write("express or implied.\n")
    output.write(" * See the License for the specific language governing ")
    output.write("permissions and\n")
    output.write(" * limitations under the License.\n")
    output.write(" */\n")
    output.write("\n")


def output_check_notes(output):
    output.write("// AUTO GENERATED, PLEASE DO NOT EDIT DIRECTLY\n\n")
    output.write("#ifndef ACELITE_FRAMEWORK_RAW_BUFFER\n")
    output.write("#error THIS FILE CAN ONLY BE INCLUDED BY RAW BUFFER CPP\n")
    output.write("#endif\n\n")


def convert_bc():
    with open(FRAMEWORK_SNAPSHOT_FILE_PATH, 'rb') as input_file:
        byte_code_buffer = input_file.read()
        with open(SNAPSHOT_OUTPUT_C_FILE_PATH, 'w') as output:
            output_copyright(output)
            output_check_notes(output)
            output.write(
                "#ifndef OHOS_ACELITE_FRAMEWORK_MIN_SNAPSHOT_BUFFER\n")
            output.write(
                "#define OHOS_ACELITE_FRAMEWORK_MIN_SNAPSHOT_BUFFER\n")
            output.write("const char g_frameworkBCBuffer[] =\n{\n    ")
            index = 1
            max_count = len(byte_code_buffer)
            for data in byte_code_buffer:
                hex_string = '0x%02x' % data
                final_hex_string = hex_string
                if index != max_count:
                    if index % 16 == 0:
                        final_hex_string = '%s,' % hex_string
                    else:
                        final_hex_string = '%s, ' % hex_string
                    output.write(final_hex_string)
                    if index % 16 == 0:
                        output.write("\n    ")
                else:
                    output.write(final_hex_string + '\n')
                index = index + 1
            output.write("};\n")
            output.write("#endif")



def convert_js():
    with open(FRAMEWORK_JS_FILE_PATH, 'r') as input_file:
        javascript_buffer = input_file.read()
        with open(JS_OUTPUT_C_FILE_PATH, 'w') as output:
            output_copyright(output)
            output_check_notes(output)
            output.write(
                "#ifndef OHOS_ACELITE_FRAMEWORK_MIN_JS_BUFFER\n")
            output.write(
                "#define OHOS_ACELITE_FRAMEWORK_MIN_JS_BUFFER\n")
            output.write(
                "const char * const g_frameworkJSBuffer =\n    \"")
            max_count = len(javascript_buffer)
            index = 0
            for data in javascript_buffer:
                cha = data
                if cha == '\"':
                    cha = '\''
                if cha == '\n':
                    continue
                final_string = '%c' % cha
                if index != (max_count - 1):
                    if (index != 0 and index % 90 == 0):
                        final_string = '%c\"' % cha
                    output.write(final_string)
                    if (index != 0 and index % 90 == 0):
                        output.write("\n    \"")
                else:
                    output.write(final_string)
                index = index + 1
            output.write("\";\n")
            output.write("#endif")


if __name__ == '__main__':
    convert_js()
    convert_bc()
