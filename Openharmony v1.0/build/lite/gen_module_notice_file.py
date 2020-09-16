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
import os
from utils import read_json_file
from utils import makedirs
from utils import encode
from utils import decode


def is_top_dir(src_path):
    return os.path.exists(os.path.join(src_path, '.gn'))


def find_config_parent_file(src_dir, target_cfg):
    if (not os.path.isdir(src_dir)) or is_top_dir(src_dir):
        return ''
    for file in os.listdir(src_dir):
        file_path = os.path.join(src_dir, file)
        if os.path.isfile(file_path):
            if os.path.basename(file_path) == target_cfg:
                return src_dir
    return find_config_parent_file(os.path.dirname(src_dir), target_cfg)


def get_notice_file_name(readme_file_path, copyright_file,
                         module_relative_src_path):
    if not os.path.exists(readme_file_path) or os.path.isdir(readme_file_path):
        return '', '', '', ''

    opensource_config = read_json_file(readme_file_path)
    if opensource_config is None:
        return '', '', '', ''

    license_file = ''
    license_name = None
    software_name = None
    for info in opensource_config:
        license_file = info.get('License File')
        license_name = info.get('License')
        software_name = '{} {}'.format(info.get('Name'), info.get('Version Number'))

    license_file_path = os.path.join(os.path.dirname(readme_file_path),
                                     license_file.strip())
    if not os.path.exists(license_file_path):
        return '', '', '', ''

    copyright_file_path = os.path.join(os.path.dirname(copyright_file),
                                       copyright_file.strip())
    if not os.path.exists(copyright_file_path):
        return '', '', '', ''

    return license_file_path, license_name, software_name, copyright_file_path


def get_opensource_config_file(module_source_dir, root_out_dir, target_cfg):
    config_file = ''

    expect_file = os.path.join(module_source_dir, target_cfg)
    if os.path.exists(expect_file):
        config_file = expect_file
    else:
        relpath = os.path.relpath(module_source_dir, root_out_dir)
        parent_cfg_dir = find_config_parent_file(os.path.dirname(relpath),
                                                 target_cfg)
        if parent_cfg_dir != '':
            config_file = os.path.join(parent_cfg_dir, target_cfg)

    return config_file


def get_notice_file(module_source_dir, root_out_dir,
                    module_relative_source_dir):
    cfg_file = get_opensource_config_file(module_source_dir, root_out_dir,
                                          'README.OpenSource')
    copyright_file = get_opensource_config_file(module_source_dir,
                                                root_out_dir,
                                                'COPYRIGHT.OpenSource')

    if cfg_file == '':
        return '', '', '', ''
    if copyright_file == '':
        return '', '', '', ''
    return get_notice_file_name(cfg_file, copyright_file,
                                module_relative_source_dir)


def get_notice_file_dest_path(root_out_dir, target_name):
    nf_dest_list = []
    nf_dest_dir = os.path.join(root_out_dir, 'NOTICE_FILE', target_name)

    license_num = 1
    while os.path.exists(os.path.join(nf_dest_dir,
                         "LICENSE{}.txt".format(license_num))):
        license_num += 1

    nf_dest_list.append(os.path.join(nf_dest_dir,
                        "LICENSE{}.txt".format(license_num)))
    return nf_dest_list


def create_dest_file(filename):
    dir_name = os.path.dirname(filename)
    if not os.path.exists(dir_name):
        makedirs(dir_name)


def gen_license(target_path, nf_dict, nf_src, cp_src):
    target_license_path = os.path.join(target_path, 'NOTICE')
    makedirs(target_path)

    with open(nf_src, 'rt') as f:
        nf_dict["license_content"] = decode(f.read())
    with open(cp_src, 'rt') as f:
        nf_dict["copyright"] = decode(f.read())

    with open(target_license_path, 'at') as f:
        f.write("Software: {}\n\n".format(encode(nf_dict["software"])))
        f.write("Copyright notice: \n{}\n".format(
            encode(nf_dict["copyright"])))
        f.write("License: {}\n{}\n\n".format(
            encode(nf_dict["license_name"]),
            encode(nf_dict["license_content"])))


def generate_notice_file(root_out_dir, module_source_dir,
                         module_relative_source_dir, target_name):
    nf_src = ''
    nf_dict = {
        "software": '',
        "copyright": '',
        "license_name": '',
        "license_content": ''
    }

    nf_src, nf_dict["license_name"], nf_dict["software"], cp_src = \
        get_notice_file(module_source_dir, root_out_dir,
                        module_relative_source_dir)
    target_path = os.path.join(root_out_dir, 'NOTICE_FILE', target_name)
    if os.path.exists(nf_src) and os.path.exists(cp_src):
        gen_license(target_path, nf_dict, nf_src, cp_src)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--root-out-dir', help='', required=True)
    parser.add_argument('--module-source-dir', help='', required=True)
    parser.add_argument('--module-relative-source-dir', help='', required=True)
    parser.add_argument('--target-name', help='', required=True)
    args = parser.parse_args()

    if 'third_party/' not in args.module_relative_source_dir:
        return 0

    generate_notice_file(args.root_out_dir,
                         args.module_source_dir,
                         args.module_relative_source_dir,
                         args.target_name)

    return 0


if __name__ == '__main__':
    sys.exit(main())
