# 编译构建子系统<a name="ZH-CN_TOPIC_0000001052340730"></a>

## 简介<a name="section11660541593"></a>

编译构建提供了一个在GN与ninja基础上的编译构建框架。支持以下功能：

1.  构建不同芯片平台的产品。如：Hi3518EV300平台的ipcamera产品，Hi3516DV300平台的ipcamera产品，Hi3861平台的wifi模组产品。
2.  构建HPM包管理配置生成的自定义产品。

## 目录<a name="section1464106163817"></a>

```
build/lite               # 编译构建主目录
├── config               # 编译相关的配置项
│   ├── boards           # 开发板相关的变量定义。包括：开发板名、目标架构、目标CPU等
│   ├── component        # OpenHarmony组件相关的模板定义。包括：静态库、动态库、扩展组件、模拟器库等
│   ├── kernel           # OpenHarmony内核的编译变量定义与配置参数
│   └── subsystem        # OpenHarmony子系统列表
├── ndk                  # NDK相关编译脚本与配置参数
├── platform             # 平台相关的配置文件
│   ├── hi3516dv300_liteos_a    # hi3516dv300, liteos_a平台。包括：平台全量配置表，启动文件。
│   ├── hi3518ev300_liteos_a    # hi3518ev300, liteos_a平台。包括：平台全量配置表，启动文件。
│   └── hi3861v100_liteos_riscv # hi3861v100, liteos_riscv平台。包括：平台全量配置表，启动文件。
├── product                     # 产品全量配置表。包括：配置单元、子系统列表、编译器等。
├── toolchain                   # 编译工具链相关。包括：编译器路径、编译选项、链接选项等。
└── tools                       # 编译构建依赖的工具。包括：mkfs等。
```

## 约束<a name="section1718733212019"></a>

编译构建框架开发者需预装GN和ninja构建工具，且加入环境变量。

## 使用<a name="section641210360552"></a>

-   编译已有产品

```
# 编译WIFI-IOT平台
python build.py wifiiot

# 编译基于Hi3518ev300的ipcamera：
python build.py ipcamera_hi3518ev300

# 编译基于Hi3516dv300的ipcamera：
python build.py ipcamera_hi3516dv300
```

- 编译组件

    本节以添加一个自定义的组件为例，描述了如何编译组件、编译库、编译可执行文件。

    示例组件example由两个功能feature1和feature2组成。feture1的目标为一个动态库，feature2的目标为一个可执行文件。

    示例组件example的完整目录结构如下：

    ```
    example                    # 自定义组件
    ├── BUILD.gn               # 自定义组件gn脚本，BUILD.gn为固定名称
    ├── feature1               # 自定义单元1
    │   ├── BUILD.gn           # 自定义单元1的gn脚本，BUILD.gn为固定名称
    │   ├── include            # 头文件文件夹
    │   │   └── helloworld1.h  # 头文件1
    │   └── src                # 源文件文件夹
    │       └── helloworld1.c  # 源文件1
    ├── feature2               # 自定义单元2
    │   ├── BUILD.gn           # 自定义单元2的gn脚本，BUILD.gn为固定名称
    │   ├── include            # 头文件文件夹
    │   │   └── helloworld2.h  # 头文件2
    │   └── src                # 源文件文件夹
    │       └── helloworld2.c  # 源文件2
    ├── build.sh               # 自定义组件build.sh脚本，非必要
    └── Makefile               # 自定义组件Makefile脚本，非必
    ```

    第一步：编写example/feature1/BUILD.gn，动态库的gn脚本

    使用lite\_library模板，可以编译出动态库与静态库。示例如下：

    ```
    # helloworld动态库编译示例
    # helloworld的Build.gn文件
    lite_library("helloworld_lib") {
        target_type = "shared_library"  # 编译动态库
        #target_type = "static_library" # 编译静态库
        sources = [
            "src/helloworld1.c"
        ]
        include_dirs = [
            "include",
            "../feature2_example/include"    # 如果依赖 feature2_example 可以加入该include
        ]
    }
    ```

    第二步：编写example/feature2/BUILD.gn，可执行文件的gn脚本

    使用gn自带模板executable，可编译出可执行文件。示例如下：

    ```
    #编译可执行.bin文件
    executable("hello_world_bin") {
        sources = [
            "src/helloworld.c"
        ]
        include_dirs = [
            "include",
            #"../feature2_example/include"    # 如果依赖 feature2_example 可以加入该include
        ]
        # 如果依赖 feature1_example 可以加入该deps
        #deps = [
        #    "../feature1_example:helloworld1"
        #]
    }
    ```
    第三步：编写example/BUILD.gn，组件gn脚本

    ```
    import("//build/lite/config/component/lite_component.gni")
    #工程全篇使用BUILD.gn脚本编译
    lite_component("example_gn") {
        features = [
            "feature_example1:helloworld_lib",
            "feature_example2:hello_world_bin",
        ]
    }
    #融入自带build.sh或Makefile工程, 用gn脚本调用混合编译
    build_ext_component("example_mk") {
        exec_path = rebase_path(rebase_path(".", root_build_dir))
        outdir = rebase_path(get_path_info(".", "out_dir"))
        prebuilts = "sh build.sh"
        command = "make clean && make"
    }
    ```


- 可用的编译构建变量

    全局可引用的变量定义在：//build/lite/ohos\_var.gni

    用户常用变量说明见表1：

    **表1**

    | 变量                | 取值范围                                   | 说明           |
    | ------------------- | ------------------------------------------ | -------------- |
    | ohos_kernel_type    | "liteos_a", "liteos_riscv"                 | 内核类型       |
    | board_name          | "hi3516dv300", "hi3518ev300", "hi3861v100" | 开发板类型     |
    | ohos_build_compiler | "gcc", "clang"                             | 编译工具链类型 |

    举例：ohos\_kernel\_type的使用，component\_example/feature2\_example/BUILD.gn

    ```
    lite_library("helloworld") {
        if (ohos_kernel_type == "liteos_a") {
            target_type = "shared_library"
        }
        else if (ohos_kernel_type == "liteos_riscv") {
            target_type = "static_library"
        }
        sources = [
            "src/helloworld1.c"
        ]
        include_dirs = [
            "include"
        ]
    }
    ```


- 编译HPM的解决方案

  通过HPM下载后，用户自定的全量模板在//build/lite/product 目录下。

  如ipcamera\_hi3516dv300.json，构建时会读取该文件包含所有用户自定义子系统、组件等配置。

- 编译输出

  编译所生产的文件都归档在out目录下，例在代码所在目录下，

  运行"python build.py wifiiot"，编译wifiiot完成后，会有如下结果生成：

  ```
  out/
  └── wifiiot                                # 产品名
      ├── args.gn                            # gn编译，用户自定义变量
      ├── build.log                          # 编译日志
      ├── build.ninja
      ├── build.ninja.d
      ├── gen
      ├── Hi3861_boot_signed_B.bin           # 带签名的bootloader备份文件 
      ├── Hi3861_boot_signed.bin             # 带签名的bootloader文件
      ├── Hi3861_loader_signed.bin           # 烧写工具使用的加载文件
      ├── Hi3861_wifiiot_app_allinone.bin    # 产线工装烧写文件(已经包含独立烧写程序和loader程序)
      ├── Hi3861_wifiiot_app.asm             # Kernel asm文件 
      ├── Hi3861_wifiiot_app_burn.bin        # 烧写文件
      ├── Hi3861_wifiiot_app_flash_boot_ota.bin # Flash Boot升级文件
      ├── Hi3861_wifiiot_app.map                # Kernel map文件
      ├── Hi3861_wifiiot_app_ota.bin            # Kernel 升级文件
      ├── Hi3861_wifiiot_app.out                # Kernel 输出文件
      ├── Hi3861_wifiiot_app_vercfg.bin         # 安全启动配置boot和kernel版本号，防版本回滚
      ├── libs                                  # 库文件夹
      ├── NOTICE_FILE
      ├── obj
      ├── suites
      └── toolchain.ninja
      注：烧写文件，烧写程序建议使用"Hi3861_wifiiot_app_allinone.bin"
  ```

  运行"python build.py ipcamera_hi3518ev300"，编译ipcamera_hi3518ev300完成后，会有如下结果生成(同ipcamera_hi3516dv300):

  ```
  out/
  └── ipcamera_hi3518ev300                # 产品名
      ├── args.gn                         # gn编译，用户自定义变量
      ├── bin                             # 链接bin所在文件夹
      ├── bm_tool.map                     # map文件
      ├── build.log                       # 编译日志
      ├── build.ninja
      ├── build.ninja.d
      ├── bundle_daemon_tool.map          # map文件
      ├── data                            # 媒体camera依赖底层资源配置文件
      ├── dev_tools                       # 研发自测试
      ├── foundation.map                  # map文件
      ├── gen
      ├── libaudio_api.so
      ├── libs                            # 镜像包含库文件
      ├── liteos.bin                      # liteos基础内核bin文件
      ├── media_server.map                # map文件
      ├── NOTICE_FILE
      ├── obj                             # 二进制文件，编译结果文件夹
      ├── OHOS_Image                      # liteos整包bin文件，未strip
      ├── OHOS_Image.asm                  # 汇编代码
      ├── OHOS_Image.bin                  # liteos整包烧录bin文件
      ├── OHOS_Image.map                  # map文件
      ├── rootfs.img                      # 编译出的库和app的镜像
      ├── rootfs.tar                      # rootfs的压缩
      ├── suites                          # xts编译结果
      ├── test                            # 测试用例编译结果
      ├── toolchain.ninja
      ├── userfs                          # 用户可读写的分区
      ├── userfs.img                      # img格式的用户可读写的分区，对应启动之后的/storage目录
      └── vendor                          # 芯片的Firmware文件及配置文件
  ```


## 涉及仓<a name="section6299103515474"></a>

build\_lite

