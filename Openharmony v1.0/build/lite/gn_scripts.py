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

import argparse
from datetime import datetime
import time
import sys


def get_build_time():
    build_time = datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S,%f")
    time_seconds, micro_seconds = build_time.split(',')
    time_array = time.strptime(time_seconds, "%Y-%m-%d %H:%M:%S")
    print(int(time.mktime(time_array) * 1000 + int(micro_seconds) * 10))
    return 0


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--time', help='Get build time',
                        action='store_true')

    args = parser.parse_args()

    if args.time:
        return get_build_time()


if __name__ == "__main__":
    sys.exit(main())
