#!/bin/bash
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
set -e

echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
date +%F' '%H:%M:%S
echo $@

BASE_HOME_PATH=$(cd $(dirname $0);pwd)
RET=0

do_make()
{
    pushd ${BASE_HOME_PATH}/src
        hos_python_filepath="${BASE_HOME_PATH}/../../prebuilts/python/linux-x86/3.7.3/bin/python3"
        usr_python_filepath="${BASE_HOME_PATH}/python/bin/python3"

        if [[ -f "${hos_python_filepath}" ]]; then
            python_filepath="${hos_python_filepath}"
        elif [[ -f "${usr_python_filepath}" ]]; then
            python_filepath="${usr_python_filepath}"
        else
            python_filepath="python3"
        fi

        ${python_filepath} -m main "$@"
        if [ "$?" != 0 ]; then
            echo "xdevice failed!"
            $RET=1
        fi
    popd
}

main()
{
    do_make "$@"
    exit $RET
}

main "$@"

date +%F' '%H:%M:%S
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
