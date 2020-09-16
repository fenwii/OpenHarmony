#!/usr/bin/env python
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

import sys
import os
import shutil
import argparse
from utils import exec_command
from utils import makedirs
import platform
import tarfile


def move_file(old_path, new_path):
    if os.path.exists(old_path):
        shutil.copytree(old_path, new_path)


def is_needed_copy(file, ignore_list):
    for ignore in ignore_list:
        if file.endswith(ignore):
            return False

    return True


def copy(source, target, ignore_list):
    for file in os.listdir(source):
        if is_needed_copy(file, ignore_list) and \
           os.path.isfile(os.path.join(source, file)):
            source_file = os.path.join(source, file)
            shutil.copy(source_file, target)


def mv_usr_libs(path):
    libs = [lib for lib in os.listdir(path) if lib.startswith('lib') and
            lib.endswith('.so')]
    target_path = os.path.join(path, 'libs/usr')
    if not os.path.exists(target_path):
        makedirs(target_path)
    for lib in libs:
        source_file = os.path.join(path, lib)
        shutil.move(source_file, target_path)


def check_strip(path, strip_cmd, log):
    if strip_cmd == "":
        return
    strip_cmd_list = strip_cmd.split(" ")
    for relpath, _, files in os.walk(path):
        for file in files:
            full_path = os.path.join(path, relpath, file)
            if os.path.isfile(full_path):
                cmd = strip_cmd_list + [full_path]
                exec_command(cmd, log_path=log)


def tee_into_userfs(output_path, userfs):
    vendor_bin_source_dir = os.path.join(output_path, 'vendor/bin')
    if not os.path.exists(vendor_bin_source_dir):
        return
    sec_storage_dir = os.path.join(userfs, 'data/sec_storage_data')
    makedirs(sec_storage_dir)

    sec_storage_root_dir = os.path.join(userfs, 'sec_storage')
    makedirs(sec_storage_root_dir)


def list_all_files(rootdir):
    _files = []
    filelist = os.listdir(rootdir)
    for i in filelist:
        path = os.path.join(rootdir, i)
        if os.path.isdir(path):
            _files.append(path)
            _files.extend(list_all_files(path))
        if os.path.isfile(path):
            _files.append(path)

    return _files


def chmod_files_mode(root_dir, dir_mode, file_mode):
    if os.path.isdir(root_dir):
        os.chmod(root_dir, dir_mode)
    filelist = list_all_files(root_dir)
    for i in filelist:
        if os.path.isdir(i):
            os.chmod(i, dir_mode)
        if os.path.isfile(i):
            os.chmod(i, file_mode)


def change_rootfs_filemode(path):
    # change all files filemode
    chmod_files_mode(path, 493, 365)
    # change special dirs filemode
    tmppath = os.path.join(path, "bin")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 365)
    tmppath = os.path.join(path, "usr")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 365)
    tmppath = os.path.join(path, "lib")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 365)
    tmppath = os.path.join(path, "vendor")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 292)
    tmppath = os.path.join(path, "system")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 292)
    tmppath = os.path.join(path, "etc")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 292)
    tmppath = os.path.join(path, "vendor/bin")
    if os.path.exists(tmppath):
        chmod_files_mode(tmppath, 365, 365)
    # change special files filemode
    tmppath = os.path.join(path, "etc/init.cfg")
    if os.path.exists(tmppath):
        os.chmod(tmppath, 256)
    tmppath = os.path.join(path, "bin/init")
    if os.path.exists(tmppath):
        os.chmod(tmppath, 320)
    tmppath = os.path.join(path, "bin/shell")
    if os.path.exists(tmppath):
        os.chmod(tmppath, 320)


def create_file_symlink(file_name, src_dir, dst_dir):
    src = os.path.join(src_dir, file_name)
    dst = os.path.join(dst_dir, file_name)
    tmppath = os.path.join("/usr/lib/", file_name)
    if os.path.exists(src):
        os.symlink(tmppath, dst)


def create_symlinks_for_dv(path):
    src_path = os.path.join(path, "usr/lib")
    dst_path = os.path.join(path, "lib")
    create_file_symlink("libmbedtls_shared.so", src_path, dst_path)
    create_file_symlink("libcjson_shared.so", src_path, dst_path)
    create_file_symlink("libsys_parameter.so", src_path, dst_path)
    create_file_symlink("libsec_shared.so", src_path, dst_path)
    create_file_symlink("libsamgr.so", src_path, dst_path)
    create_file_symlink("libliteipc_adapter.so", src_path, dst_path)
    create_file_symlink("libhilog_a_shared.so", src_path, dst_path)


def change_rootfs_filemode_linux(path):
    tmppath = os.path.join(path, "lib")
    chmod_files_mode(tmppath, 493, 420)
    tmppath = os.path.join(path, "lib/ld-uClibc-0.9.33.2.so")
    if os.path.exists(tmppath):
        os.chmod(tmppath, 365)
    tmppath = os.path.join(path, "lib/ld-2.24.so")
    if os.path.exists(tmppath):
        os.chmod(tmppath, 365)
    tmppath = os.path.join(path, "usr")
    os.chmod(tmppath, 493)
    tmppath = os.path.join(path, "usr/lib")
    chmod_files_mode(tmppath, 493, 420)
    tmppath = os.path.join(path, "etc/init.cfg")
    os.chmod(tmppath, 256)
    if "dv300" in path:
        create_symlinks_for_dv(path)


def change_userfs_filemode(path):
    # change all files filemode
    chmod_files_mode(path, 493, 365)
    # change special files filemode
    tmppath = os.path.join(path, "etc/cameradev.ini")
    if os.path.exists(tmppath):
        os.chmod(tmppath, 420)


def remove_file_in_rootfs(output_path):
    rootfs_app = os.path.join(output_path, 'rootfs/app')
    rootfs_data = os.path.join(output_path, 'rootfs/data')
    if os.path.exists(rootfs_app):
        shutil.rmtree(rootfs_app)
    if os.path.exists(rootfs_data):
        shutil.rmtree(rootfs_data)


def make_rootfs_tar(tar_filename, source_dir):
    with tarfile.open(tar_filename, "w") as tar:
        tar.add(source_dir, arcname=os.path.basename(source_dir))


def gen_rootfs(mkfs, fstype, output_path, rootfs_dirs_dict, kernel):
    mv_usr_libs(output_path)
    rootfs = os.path.join(output_path, 'rootfs')
    rootfs_tar = os.path.join(output_path, 'rootfs.tar')
    if not os.path.exists(rootfs):
        print('rootfs dir not exist in {}'.format(rootfs))
        return 0

    log = os.path.join(output_path, 'build.log')
    for path_part, value_list in rootfs_dirs_dict.items():
        source_path = os.path.join(output_path, path_part)
        target_path = os.path.join(rootfs, value_list[0])
        strip_cmd = value_list[2]
        if os.path.exists(source_path):
            if not os.path.exists(target_path):
                makedirs(target_path)
            ignore_list = value_list[1]
            copy(source_path, target_path, ignore_list)

        check_strip(target_path, strip_cmd, log)

    if kernel == "linux":
        change_rootfs_filemode_linux(rootfs)
        cmd = [mkfs, rootfs, "jffs2"]
        exec_command(cmd, log_path=log)
    if kernel == "liteos_a":
        remove_file_in_rootfs(output_path)
        change_rootfs_filemode(rootfs)
        cmd = [mkfs, rootfs, fstype]
        exec_command(cmd, log_path=log)
        make_rootfs_tar(rootfs_tar, rootfs)
        if os.path.exists(rootfs):
            chmod_files_mode(rootfs, 511, 511)
            shutil.rmtree(rootfs)

    return 0


def make_userfs_dir(dir_path):
    if not os.path.exists(dir_path):
        makedirs(dir_path)
    if not os.path.exists(dir_path):
        print('make' + str(dir_path) + 'fail')
        return -1


def move_rootfs_to_userfs(output_path):
    rootfs_app = os.path.join(output_path, 'rootfs/app')
    rootfs_data = os.path.join(output_path, 'rootfs/data')
    userfs_app = os.path.join(output_path, 'userfs/app')
    userfs_data = os.path.join(output_path, 'userfs/data')
    move_file(rootfs_app, userfs_app)
    move_file(rootfs_data, userfs_data)


def gen_userfs(mkfs, fstype, output_path, userfs_dirs_dict):
    userfs = os.path.join(output_path, 'userfs')
    userfs_etc = os.path.join(output_path, 'userfs/etc')
    if make_userfs_dir(userfs):
        return 0
    if make_userfs_dir(userfs_etc):
        return 0
    move_rootfs_to_userfs(output_path)
    log = os.path.join(output_path, 'build.log')
    tee_into_userfs(output_path, userfs)
    for path_part, value_list in userfs_dirs_dict.items():
        source_path = os.path.join(output_path, path_part)
        target_path = os.path.join(userfs, value_list[0])
        strip_cmd = value_list[2]
        if os.path.exists(source_path):
            if not os.path.exists(target_path):
                makedirs(target_path)
            ignore_list = value_list[1]
            copy(source_path, target_path, ignore_list)

        check_strip(target_path, strip_cmd, log)
    change_userfs_filemode(userfs)
    if fstype == "vfat":
        cmd = [mkfs, userfs, fstype, '52428800']
    else:
        cmd = [mkfs, userfs, fstype]
    exec_command(cmd, log_path=log)
    return 0


def main():
    parser = argparse.ArgumentParser(description='Generate rootfs')
    parser.add_argument('--path', help='Build output path')
    parser.add_argument('--board', help='Board type')
    parser.add_argument('--kernel', help='OHOS kernel type')
    parser.add_argument('--compile_so', help='So strip command')
    parser.add_argument('--compile_bin', help='Bin strip command')
    args = parser.parse_args()

    if args.board == 'hi3861v100':
        return

    if args.path:
        output_path = os.path.abspath(args.path)
        mkfs = os.path.join(
            output_path,
            '../../kernel/liteos_a/tools/scripts/make_rootfs/rootfsimg.sh')
        if not os.path.exists(mkfs):
            print('mkfs not exist in {}'.format(mkfs))
            return -1
    else:
        return -1

    if args.board:
        if args.board == 'hi3516dv300':
            fstype = 'vfat'
        else:
            fstype = 'jffs2'
    else:
        return -1

    so_strip_cmd = args.compile_so
    bin_strip_cmd = args.compile_bin
    kernel = args.kernel

    rootfs_dirs_dict = {
        'bin': ['bin', ['Test.bin', 'TestSuite.bin'], bin_strip_cmd],
        'libs': ['lib', ['.a'], so_strip_cmd],
        'libs/usr': ['usr/lib', ['.a'], so_strip_cmd],
        'bin/usr': ['usr/bin', [], bin_strip_cmd],
        'vendor/bin': ['vendor/bin', [], ""],
        'vendor/lib': ['vendor/lib', [], ""],
        'vendor/firmware/hisilicon': ['vendor/firmware/hisilicon', [], ""],
        'obj/vendor/huawei/camera/init_configs/config': ['etc', [], ""],
        'system/internal': ['system/internal', [], ""],
        'etc': ['etc', [], ""]
    }
    userfs_dirs_dict = {
        'obj/base/security/services/app_verify/config':
        ['data/verify', [], ""],
        'storage/etc': ['etc', [], ""],
        'data': ['data', [], ""]
    }
    if kernel == "liteos_a":
        ret = gen_userfs(mkfs, fstype, output_path, userfs_dirs_dict)
        if ret:
            return -1
    return gen_rootfs(mkfs, fstype, output_path, rootfs_dirs_dict, kernel)


if __name__ == "__main__":
    sys.exit(main())
