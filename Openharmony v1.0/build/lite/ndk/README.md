# 轻鸿蒙NDK使用指南

## 简介

NDK = Native Development Kit, 主要包括系统提供的c/c++接口库文件，编译工具链，工具和接口描述文档。

## 目录结构

├── build																						**编译框架**
│   ├── config
│   └── toolchain
├── doc																						 **native api接口描述文档**
├── gcc																						 **编译工具链**
│   ├── arm-linux-ohoseabi -> arm-linux-musleabi
│   ├── arm-linux-musleabi
│   ├── bin
│   ├── host_bin
│   ├── lib
│   ├── libexec
│   ├── runtime_musl
│   └── target
├── prebuilts																				**构建工具**
│   └── build-tools
├── sample																					**用户编译样例**
│   ├── include
│   └── src
└── sysroot																					**Native API**
    └── usr

## 编译框架

### 编译命令

编译使用gn构建系统，在根目录执行：`python build.py`即可启动编译。支持的命令如下：

**build:** `python build.py ` 或 ``python build.py build`

**clean:** `python build.py clean`

**debug/release**:`python build.py -v debug/release`

debug和release版本的区别：

debug版本：-g

release版本：-O2 + strip符号表

### 默认编译选项

1、安全编译选项：-fstack-protector-all，PIE，PIC，_FORTIFY_SOURCE=2，-Wl,-z,now，-Wl,-z,relro，-Wl,-z,noexecstack

2、告警级别：-Werror

### 应用编译示例

1、创建应用目录，并在目录下创建BUILD.gn:

```
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

static_library("hello_world") {	# 应用库文件target，也可是shared_library
    sources = [
        "src/hello_world.c",
    ]

    include_dirs = [
        "include",
    ]
}

executable("sample") {			# 应用可执行文件target
    ldflags = [
        "-lsys_parameter",  	# 应用需要使用的库
        "-lsec_shared"
    ]
    deps = [
        ":hello_world",
    ]
}

```

2、将sample加入到编译入口，编译入口为根目录下的BUILD.gn:

```
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

import("//build/toolchain/${ohos_build_compiler}.gni")

group("ohos") {
    deps = []
    if (target_os == "ohos") {
        deps += [
            "//sample" # 新加的应用
        ]
    }
}
```

3、编译输出：out/bin

## 烧录和运行

1、请先烧录内核和文件系统

2、将应用程序nfs或者tftp到usr/bin目录下, 运行即可