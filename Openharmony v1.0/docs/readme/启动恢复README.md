# 启动恢复<a name="ZH-CN_TOPIC_0000001051344323"></a>

## 简介<a name="section11660541593"></a>

启动恢复负责在内核启动之后，应用启动之前的操作系统中间层的启动。涉及以下模块：

-   init启动引导

支持使用LiteOS-A内核的平台，当前包括：Hi3516DV300平台和Hi3518EV300平台。

负责处理从内核加载第一个用户态进程开始，到第一个应用程序启动之间的系统服务进程启动过程。启动恢复子系统除负责加载各系统关键进程之外，还需在启动的同时设置其对应权限，并在子进程启动后对指定进程实行保活（若进程意外退出要重新启动），对于特殊进程意外退出时，启动恢复子系统还要执行系统复位操作。

-   appspawn应用孵化

    支持使用LiteOS-A内核的平台，当前包括：Hi3516DV300平台和Hi3518EV300平台。

    负责接受应用程序框架的命令孵化应用进程，设置其对应权限，并调用应用程序框架的入口。

-   bootstrap启动服务模块

    支持使用LiteOS-M内核的平台，当前包括：Hi3861平台。

    提供了各服务和功能的启动入口标识。在SAMGR启动时，会调用boostrap标识的入口函数，并启动系统服务。

-   系统属性

    支持使用LiteOS-M内核和LiteOS-A内核的平台，包括：Hi3861平台，Hi3516DV300平台，Hi3518EV300平台。

    负责提供获取与设置操作系统相关的系统属性。

    系统属性包括：默认系统属性、OEM厂商系统属性和自定义系统属性。OEM厂商部分仅提供默认值，具体值需OEM产品方按需进行调整，详见“使用”部分。


## 目录<a name="section1464106163817"></a>

**表 1**  启动恢复源代码目录结构

<a name="table2977131081412"></a>
<table><thead align="left"><tr id="row7977610131417"><th class="cellrowborder" valign="top" width="19.439999999999998%" id="mcps1.2.4.1.1"><p id="p18792459121314"><a name="p18792459121314"></a><a name="p18792459121314"></a>名称</p>
</th>
<th class="cellrowborder" valign="top" width="66.64%" id="mcps1.2.4.1.2"><p id="p77921459191317"><a name="p77921459191317"></a><a name="p77921459191317"></a>描述</p>
</th>
<th class="cellrowborder" valign="top" width="13.919999999999998%" id="mcps1.2.4.1.3"><p id="p101617019356"><a name="p101617019356"></a><a name="p101617019356"></a>适配平台</p>
</th>
</tr>
</thead>
<tbody><tr id="row17977171010144"><td class="cellrowborder" valign="top" width="19.439999999999998%" headers="mcps1.2.4.1.1 "><p id="p2793159171311"><a name="p2793159171311"></a><a name="p2793159171311"></a>base/startup/services/appspawn_lite</p>
</td>
<td class="cellrowborder" valign="top" width="66.64%" headers="mcps1.2.4.1.2 "><p id="p879375920132"><a name="p879375920132"></a><a name="p879375920132"></a>应用孵化模块，appspawn进程，负责通过轻量级IPC机制接收AMS消息，然后根据消息解析结果启动应用进程并赋予其对应权限。</p>
</td>
<td class="cellrowborder" valign="top" width="13.919999999999998%" headers="mcps1.2.4.1.3 "><p id="p63463619360"><a name="p63463619360"></a><a name="p63463619360"></a>Hi3516DV300</p>
<p id="p141611802359"><a name="p141611802359"></a><a name="p141611802359"></a>Hi3518EV300</p>
</td>
</tr>
<tr id="row6978161091412"><td class="cellrowborder" valign="top" width="19.439999999999998%" headers="mcps1.2.4.1.1 "><p id="p37931659101311"><a name="p37931659101311"></a><a name="p37931659101311"></a>base/startup/services/bootstrap_lite</p>
</td>
<td class="cellrowborder" valign="top" width="66.64%" headers="mcps1.2.4.1.2 "><p id="p6793059171318"><a name="p6793059171318"></a><a name="p6793059171318"></a>服务启动模块，启动系统核心服务外的其他服务。</p>
</td>
<td class="cellrowborder" valign="top" width="13.919999999999998%" headers="mcps1.2.4.1.3 "><p id="p101610019353"><a name="p101610019353"></a><a name="p101610019353"></a>Hi3861</p>
</td>
</tr>
<tr id="row6978201031415"><td class="cellrowborder" align="left" valign="top" width="19.439999999999998%" headers="mcps1.2.4.1.1 "><p id="p117935599130"><a name="p117935599130"></a><a name="p117935599130"></a>base/startup/services/init_lite</p>
</td>
<td class="cellrowborder" valign="top" width="66.64%" headers="mcps1.2.4.1.2 "><p id="p0793185971316"><a name="p0793185971316"></a><a name="p0793185971316"></a>启动引导模块，init进程，内核完成初始化后加载的第一个用户态进程，启动后解析/etc/init.cfg配置文件，并根据解析结果拉起其他系统关键进程，同时分别赋予其对应权限。</p>
</td>
<td class="cellrowborder" valign="top" width="13.919999999999998%" headers="mcps1.2.4.1.3 "><p id="p2176757193619"><a name="p2176757193619"></a><a name="p2176757193619"></a>Hi3516DV300</p>
<p id="p51611013358"><a name="p51611013358"></a><a name="p51611013358"></a>Hi3518EV300</p>
</td>
</tr>
<tr id="row1897841071415"><td class="cellrowborder" valign="top" width="19.439999999999998%" headers="mcps1.2.4.1.1 "><p id="p16793185961315"><a name="p16793185961315"></a><a name="p16793185961315"></a>base/startup/interfaces</p>
</td>
<td class="cellrowborder" valign="top" width="66.64%" headers="mcps1.2.4.1.2 "><p id="p20413161014013"><a name="p20413161014013"></a><a name="p20413161014013"></a>服务启动模块对外接口，由main函数来调用，启动服务框架。</p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="13.919999999999998%" headers="mcps1.2.4.1.3 "><p id="p1956516512380"><a name="p1956516512380"></a><a name="p1956516512380"></a>Hi3861</p>
<p id="p2670195353812"><a name="p2670195353812"></a><a name="p2670195353812"></a>Hi3516DV300</p>
<p id="p116118053518"><a name="p116118053518"></a><a name="p116118053518"></a>Hi3518EV300</p>
</td>
</tr>
<tr id="row178841725886"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p88841825887"><a name="p88841825887"></a><a name="p88841825887"></a>base/startup/frameworks/syspara_lite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p98851625589"><a name="p98851625589"></a><a name="p98851625589"></a>系统属性模块。提供获取设备信息接口，如：产品名、品牌名、品类名、厂家名等。</p>
</td>
</tr>
</tbody>
</table>

```
base
├──startup    启动恢复子系统根目录
├──── frameworks
│     └── syspara_lite
│         ├── LICENSE     开源LICENSE文件
│         ├── parameter   系统属性模块源文件目录
│         │   ├── BUILD.gn
│         │   └── src
│         │       ├── BUILD.gn
│         │       ├── param_impl_hal     系统属性模块基于LiteOS-M核实现
│         │       └── param_impl_posix   系统属性模块基于LiteOS-A核实现
│         └── token
│             ├── BUILD.gn
│             └── src
│                 ├── token_impl_hal
│                 └── token_impl_posix
├──── hals         
│     └── syspara_lite       系统属性模块硬件抽象层头文件目录   
├──── interfaces
│     └── kits
│         └── syspara_lite   系统属性模块对外接口目录
└──── services
      ├── appspawn_lite    应用孵化模块
      │   ├── BUILD.gn    应用孵化模块编译配置
      │   ├── include     应用孵化模块头文件目录
      │   ├── LICENSE     开源LICENSE文件
      │   ├── moduletest  应用孵化模块自测试代码目录
      │   └── src         应用孵化木块源文件目录
      ├── bootstrap_lite   启动服务模块
      │   ├── BUILD.gn    启动服务模块编译配置
      │   ├── LICENSE     开源LICENSE文件
      │   └── source      启动服务模块源文件目录
      └── init_lite       启动引导模块
          ├── BUILD.gn    启动引导模块编译配置
          ├── include     启动引导模块头文件目录
          ├── LICENSE     开源LICENSE文件
          ├── moduletest  启动引导模块自测试代码目录
          └── src         启动引导模块源文件目录
vendor
└──huawei
        └──camera
                └──init_configs  启动引导模块配置文件目录（json格式，部署于/etc/目录下）
```

## 约束<a name="section1718733212019"></a>

启动恢复使用C语言开发。

-   系统属性：OEM厂商相关仅提供默认值，具体值需产品方按需进行调整。

## 使用<a name="section674513182447"></a>

-   init启动引导的配置文件

启动引导模块配置文件包含了所有需要由init进程启动的系统关键服务的服务名、可执行文件路径、权限和其他属性信息，该文件位于代码仓库/vendor/huawei/camera/init\_configs/目录，部署在/etc/下，文件名称为init.cfg，采用json格式，文件大小目前限制在10KB以内。

init进程启动后首先读取/etc/init.cfg，然后解析其json内容，并根据解析结果依次加载系统服务。配置文件格式和内容说明如下所示：

```
{
    "jobs" : [{
            "name" : "pre-init",      -------- 在init之前执行的job，可以放置一些启动进程之前的预操作（如新建文件夹等）
            "cmds" : [
                "mkdir /testdir",      -------- 创建文件夹命令，mkdir和目标文件夹之间有且只能有一个空格
                "chmod 0700 /testdir", -------- 修改权限命令，chmod 权限 目标  之间间隔有且仅有一个空格，权限必须为0xxxx格式
                "chown 99 99 /testdir",-------- 修改属组命令，chown uid gid 目标  之间间隔有且仅有一个空格
                "mkdir /testdir2",
                "mount vfat /dev/mmcblk0p0 /testdir2 noexec nosuid" -------- mount命令，格式为：mount 文件系统类型 source target flags data
                                                                    -------- flags当前仅支持nodev、noexec、nosuid和 rdonly，各项均以一个空格分开
            ]
        }, {
            "name" : "init",          -------- init进程支持的job名称，如扩展请确保job名称不超过32字节
            "cmds" : [                -------- 当前job支持的命令集合，命令名称（10字节以内）和后面参数（32字节以内）之间有且只能有一个空格
                "start service1",     -------- 当前job的第一条命令
                "start service2"      -------- 当前job的第二条命令（可以根据需要调整命令在数组中的顺序，init进程将根据解析顺序依次执行）
             ]
        }, {
             "name" : "post-init",    -------- 在init之后执行的 job，可以放置一些启动进程之后的操作
             "cmds" : []
        }
    ],
    "services" : [{                         -------- service集合（数组形式），包含了init进程需要启动的所有系统服务
            "name" : "service1",            -------- 当前服务的服务名，须确保非空且长度在32字节以内
            "path" : "/bin/process1"        -------- 当前服务的可执行文件全路径，须确保非空且长度在64字节以内
            "uid" : 1,                      -------- 当前服务进程的uid值
            "gid" : 1,                      -------- 当前服务进程的gid值
            "once" : 0,                     -------- 当前服务进程是否为一次性进程
                                                     0 --- 当前服务非一次性进程，当进程因任何原因退出时，init收到SIGCHLD信号后将重新启动该服务进程
                                                   非0 --- 当前服务为一次性进程，当进程因任何原因退出时，init不会重新启动该服务进程
            "importance" : 1,               -------- 当前服务是否为关键系统进程
                                                     0 --- 当前服务非关键系统进程，当进程因任何原因退出时，init不会做系统复位操作
                                                   非0 --- 当前服务为关键系统进程，当进程因任何原因退出时，init收到SIGCHLD信号后进行系统复位重启
            "caps" : [0, 1, 2, 5]           -------- 当前服务所需的capability值，根据安全子系统已支持的capability，评估所需的capability，遵循最小权限原则配置
    }, {
            "name" : "service2",            -------- 下一个需要init启动的服务。此处服务的顺序与启动顺序无关，启动顺序取决于上面job中的cmd顺序。
            "path" : "/bin/process2",
            "uid" : 2,
            "gid" : 2,
            "once" : 1,
            "importance" : 0,
            "caps" : [ ]
        }
    ]
}
```

**表 2**  cmds支持列表

<a name="table9623104414018"></a>
<table><thead align="left"><tr id="row5623144194017"><th class="cellrowborder" valign="top" width="12.5%" id="mcps1.2.4.1.1"><p id="p56231449404"><a name="p56231449404"></a><a name="p56231449404"></a>命令名称</p>
</th>
<th class="cellrowborder" valign="top" width="31.05%" id="mcps1.2.4.1.2"><p id="p962313447401"><a name="p962313447401"></a><a name="p962313447401"></a>命令格式</p>
</th>
<th class="cellrowborder" valign="top" width="56.45%" id="mcps1.2.4.1.3"><p id="p88724434113"><a name="p88724434113"></a><a name="p88724434113"></a>命令说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row962344416405"><td class="cellrowborder" valign="top" width="12.5%" headers="mcps1.2.4.1.1 "><p id="p66231144104011"><a name="p66231144104011"></a><a name="p66231144104011"></a>start</p>
</td>
<td class="cellrowborder" valign="top" width="31.05%" headers="mcps1.2.4.1.2 "><p id="p862384484010"><a name="p862384484010"></a><a name="p862384484010"></a>start ServiceName      间隔有且仅有一个空格</p>
</td>
<td class="cellrowborder" valign="top" width="56.45%" headers="mcps1.2.4.1.3 "><p id="p17872104184113"><a name="p17872104184113"></a><a name="p17872104184113"></a>启动服务，服务名称与文件中services数组中服务名称相同</p>
</td>
</tr>
<tr id="row962311443404"><td class="cellrowborder" valign="top" width="12.5%" headers="mcps1.2.4.1.1 "><p id="p13837142094117"><a name="p13837142094117"></a><a name="p13837142094117"></a>mkdir</p>
</td>
<td class="cellrowborder" valign="top" width="31.05%" headers="mcps1.2.4.1.2 "><p id="p2624244204019"><a name="p2624244204019"></a><a name="p2624244204019"></a>mkdir  /xxxx/xxx        间隔有且仅有一个空格</p>
</td>
<td class="cellrowborder" valign="top" width="56.45%" headers="mcps1.2.4.1.3 "><p id="p158722484112"><a name="p158722484112"></a><a name="p158722484112"></a>创建目录</p>
</td>
</tr>
<tr id="row662404414406"><td class="cellrowborder" valign="top" width="12.5%" headers="mcps1.2.4.1.1 "><p id="p3624444154011"><a name="p3624444154011"></a><a name="p3624444154011"></a>chmod</p>
</td>
<td class="cellrowborder" valign="top" width="31.05%" headers="mcps1.2.4.1.2 "><p id="p7624344134020"><a name="p7624344134020"></a><a name="p7624344134020"></a>chmod 0xxx /xxx/xx   间隔有且仅有一个空格</p>
</td>
<td class="cellrowborder" valign="top" width="56.45%" headers="mcps1.2.4.1.3 "><p id="p18872945418"><a name="p18872945418"></a><a name="p18872945418"></a>修改权限，权限值必须为0xxx格式，如0755，0600等，需要遵循权限最小原则配置</p>
</td>
</tr>
<tr id="row1462404494017"><td class="cellrowborder" valign="top" width="12.5%" headers="mcps1.2.4.1.1 "><p id="p136241144144013"><a name="p136241144144013"></a><a name="p136241144144013"></a>chown</p>
</td>
<td class="cellrowborder" valign="top" width="31.05%" headers="mcps1.2.4.1.2 "><p id="p1624144194011"><a name="p1624144194011"></a><a name="p1624144194011"></a>chown uid gid /xxx/xx 间隔有且仅有一个空格</p>
</td>
<td class="cellrowborder" valign="top" width="56.45%" headers="mcps1.2.4.1.3 "><p id="p9872246417"><a name="p9872246417"></a><a name="p9872246417"></a>修改属组</p>
</td>
</tr>
<tr id="row1285512468412"><td class="cellrowborder" valign="top" width="12.5%" headers="mcps1.2.4.1.1 "><p id="p1385515468413"><a name="p1385515468413"></a><a name="p1385515468413"></a>mount</p>
</td>
<td class="cellrowborder" valign="top" width="31.05%" headers="mcps1.2.4.1.2 "><p id="p358535124815"><a name="p358535124815"></a><a name="p358535124815"></a>mount fileSysType source target flags data</p>
<p id="p178550463412"><a name="p178550463412"></a><a name="p178550463412"></a>间隔有且仅有一个空格</p>
</td>
<td class="cellrowborder" valign="top" width="56.45%" headers="mcps1.2.4.1.3 "><p id="p1085544611415"><a name="p1085544611415"></a><a name="p1085544611415"></a>挂载命令，其中flags目前仅支持nodev、noexec、nosuid和rdonly，其它字串均判定为data项</p>
</td>
</tr>
</tbody>
</table>

需要注意的是，init.cfg文件的修改需要保持json格式不被破坏，否则init进程解析失败后不会启动任何服务。对于配置的服务权限（uid/gid/capability）需要符合安全子系统要求且遵循权限最小原则。另外，对于once和importance项均为0的服务，若其在4分钟内连续退出次数超过4次，则init将终止重新启动该服务的操作。

-   系统参数

    -   OEM厂商相关系统属性

    Hi3516DV300，Hi3518EV300开发板需要修改vendor/huawei/camera/hals/utils/sys\_param目录下源文件：

    ```
    static const char HOS_PRODUCT_TYPE[] = {"****"};
    static const char HOS_MANUFACTURE[] = {"****"};
    static const char HOS_BRAND[] = {"****"};
    static const char HOS_MARKET_NAME[] = {"****"};
    static const char HOS_PRODUCT_SERIES[] = {"****"};
    static const char HOS_PRODUCT_MODEL[] = {"****"};
    static const char HOS_SOFTWARE_MODEL[] = {"****"};
    static const char HOS_HARDWARE_MODEL[] = {"****"};
    static const char HOS_HARDWARE_PROFILE[] = {"aout:true,display:true"};
    static const char HOS_BOOTLOADER_VERSION[] = {"bootloader"};
    static const char HOS_SECURE_PATCH_LEVEL[] = {"2020-6-5"};
    static const char HOS_ABI_LIST[] = {"****"};
    ```

    Hi3861开发板需要修改vendor/huawei/wifi-iot/hals/utils/sys\_param目录下源文件：

    ```
    static const char HOS_PRODUCT_TYPE[] = {"****"};
    static const char HOS_MANUFACTURE[] = {"****"};
    static const char HOS_BRAND[] = {"****"};
    static const char HOS_MARKET_NAME[] = {"****"};
    static const char HOS_PRODUCT_SERIES[] = {"****"};
    static const char HOS_PRODUCT_MODEL[] = {"****"};
    static const char HOS_SOFTWARE_MODEL[] = {"****"};
    static const char HOS_HARDWARE_MODEL[] = {"****"};
    static const char HOS_HARDWARE_PROFILE[] = {"aout:true,display:true"};
    static const char HOS_BOOTLOADER_VERSION[] = {"bootloader"};
    static const char HOS_SECURE_PATCH_LEVEL[] = {"2020-6-5"};
    static const char HOS_ABI_LIST[] = {"****"};
    ```

    -   获取默认系统属性

    ```
    char* value1 = GetProductType();
    printf("Product type =%s\n", value1);
    free(value1);
    char* value2 = GetManufacture();
    printf("Manufacture =%s\n", value2);
    free(value2);
    char* value3 = GetBrand();
    printf("GetBrand =%s\n", value3);
    free(value3);
    ```

    -   设置获取自定义系统属性

    ```
    const char* defSysParam = "data of sys param ***...";
    char key[] = "rw.parameter.key";
    char value[] = "OEM-hisi-10.1.0";
    int ret = SetParameter(key, value);
    char valueGet[128] = {0};
    ret = GetParameter(key, defSysParam, valueGet, 128);
    printf("value = %s\n", valueGet);
    ```


## 涉及仓<a name="section641143415335"></a>

startup\_frameworks\_syspara\_lite

startup\_hals\_syspara\_lite

startup\_interfaces\_kits\_syspara\_lite

startup\_appspawn\_lite

startup\_services\_bootstrap\_lite

startup\_init\_lite

