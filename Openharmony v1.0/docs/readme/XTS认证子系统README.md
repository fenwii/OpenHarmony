# XTS认证子系统<a name="ZH-CN_TOPIC_0000001051663004"></a>

## 简介<a name="section9242181211612"></a>

XTS是OpenHarmony生态认证测试套件的集合，当前包括acts（application compatibility test suite）应用兼容性测试套，后续会拓展dcts（device compatibility test suite）设备兼容性测试套等。

test/xts仓当前包括acts与tools软件包：

-   acts，存放acts相关测试用例源码与配置文件，其目的是帮助终端设备厂商尽早发现软件与OpenHarmony的不兼容性，确保软件在整个开发过程中满足OpenHarmony的兼容性要求。
-   tools，提供acts编写与编译所依赖的测试用例开发框架。

## 目录<a name="section36203291667"></a>

test/xts源代码目录结构：

├── acts

│   ├── BUILD.gn 测试用例编译配置

│   └── A测试子系统\_lite   A测试子系统测试用例源码

│   └── B测试子系统\_lite   B测试子系统测试用例源码

└── tools

│   └── build 测试用例编译相关的模板与脚本

│   └── hcpptest 智慧视觉类设备（Ipcamera）测试用例开发框架源码

│   └── hctest  联接类模组测试用例开发框架源码

│   └── BUILD.gn 编译配置

│   └── build.sh  编译入口

## 约束<a name="section755813411667"></a>

联接类模组acts用例开发语言是C，智慧视觉类设备（Ipcamera）acts用例开发语言是C++。

## 编写联接类模组acts测试用例<a name="section98382591568"></a>

当前使用的测试框架是hctest测试框架。

hctest测试框架支持使用C语言编写测试用例，在联接类模组上执行，是在开源测试框架unity的基础上进行增强和适配。

**1，用例目录规范：测试用例存储到test/xts/acts仓中。**

├── acts

│   ├── BUILD.gn

│   └──测试子系统\_lite

│   │   └── 测试模块\_hal

│   │   │   └──  BUILD.gn

│   │   │   └── src   存放测试用例源码

**2，src目录下用例编写样例：**

（1）引用测试框架

```
#include "hctest.h"
```

（2）使用宏定义LITE\_TEST\_SUIT定义子系统、模块、测试套件名称

```
/**  
* @brief  register a test suit named "IntTestSuite"  
* @param  test subsystem name  
* @param  example module name  
* @param  IntTestSuite test suit name  
*/
LITE_TEST_SUIT(test, example, IntTestSuite);
```

（3）定义Setup与TearDown

命名方式：测试套件名称+Setup，测试套件名称+TearDown。

Setup与TearDown必须存在，可以为空函数。

（4）使用宏定义LITE\_TEST\_CASE写测试用例

包括三个参数：测试套件名称，测试用例名称，用例级别。

用例级别取值为如下内容之一:

“Level0”,“Level1”,“Level2”,“Level3”，“Level4”。

```
LITE_TEST_CASE(IntTestSuite, TestCase001, Level0) 
{  
  //do something 
};
```

用例级别说明：

<a name="table34971832145813"></a>
<table><thead align="left"><tr id="row175461132115812"><th class="cellrowborder" valign="top" width="13.751375137513753%" id="mcps1.1.4.1.1"><p id="p5546193210584"><a name="p5546193210584"></a><a name="p5546193210584"></a><strong id="b1854623265818"><a name="b1854623265818"></a><a name="b1854623265818"></a>级别名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="11.08110811081108%" id="mcps1.1.4.1.2"><p id="p15546133255813"><a name="p15546133255813"></a><a name="p15546133255813"></a><strong id="b1454673255811"><a name="b1454673255811"></a><a name="b1454673255811"></a>基本定义</strong></p>
</th>
<th class="cellrowborder" valign="top" width="75.16751675167517%" id="mcps1.1.4.1.3"><p id="p454693295816"><a name="p454693295816"></a><a name="p454693295816"></a><strong id="b654623216588"><a name="b654623216588"></a><a name="b654623216588"></a>测试范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row054663212583"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p4546732205817"><a name="p4546732205817"></a><a name="p4546732205817"></a>Level0</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p75464323584"><a name="p75464323584"></a><a name="p75464323584"></a>冒烟</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p10547232135819"><a name="p10547232135819"></a><a name="p10547232135819"></a>验证关键功能点基本功能/最基本DFX属性在最常见输入下的表现，通过表示功能基本可运行。</p>
</td>
</tr>
<tr id="row1054743225819"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p35471932105811"><a name="p35471932105811"></a><a name="p35471932105811"></a>Level1</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p135471328585"><a name="p135471328585"></a><a name="p135471328585"></a>基本</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p195475329589"><a name="p195475329589"></a><a name="p195475329589"></a>验证各功能点基本功能/基本DFX属性在常见输入下的表现，通过表示功能基本可测试。</p>
</td>
</tr>
<tr id="row654713285815"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p1954793265810"><a name="p1954793265810"></a><a name="p1954793265810"></a>Level2</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p3547232135812"><a name="p3547232135812"></a><a name="p3547232135812"></a>重要</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p5547832195811"><a name="p5547832195811"></a><a name="p5547832195811"></a>验证各功能点的基本功能/基本DFX属性在常规输入/常见异常情况下的表现，通过表示功能基本正常可用，可开展Beta。</p>
</td>
</tr>
<tr id="row85471332135818"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p185471320586"><a name="p185471320586"></a><a name="p185471320586"></a>Level3</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p2547153212582"><a name="p2547153212582"></a><a name="p2547153212582"></a>一般</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p17547133245813"><a name="p17547133245813"></a><a name="p17547133245813"></a>验证各功能点的全部功能/全部DFX属性在各种常规/非常规输入组合下，或各种正常/异常预置条件组合下的表现。</p>
</td>
</tr>
<tr id="row1254710325584"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p554713329584"><a name="p554713329584"></a><a name="p554713329584"></a>Level4</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p1454711328588"><a name="p1454711328588"></a><a name="p1454711328588"></a>生僻</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p105479324587"><a name="p105479324587"></a><a name="p105479324587"></a>验证关键功能点在极端异常预置条件下、用户难以触及的异常输入组合下的表现。</p>
</td>
</tr>
</tbody>
</table>

（5）使用宏定义 RUN\_TEST\_SUITE注册测试套件；

```
RUN_TEST_SUITE(IntTestSuite);
```

**3，测试模块的配置文件样例：（BUILD.gn）**

每个测试模块目录下新建BUILD.gn编译文件，用于指定编译后静态库的名称、依赖的头文件、依赖的库等；具体写法如下：

```
import("//test/xts/tools/build/suite_lite.gni")
hctest_suite("ActsDemoTest") {
    suite_name = "acts"
    sources = [
        "src/test_demo.c",
    ]
    include_dirs = [ ]
    cflags = [ "-Wno-error" ]
}
```

**4，acts下BUILD.gn增加编译选项**

如何将编写的测试代码加入到版本编译中，需要将测试模块加入到acts目录下的编译脚本中，编译脚本为：test/xts/acts/BUILD.gn。

```
lite_component("acts") {  
    ...
    if(board_name == "liteos_riscv") {
        features += [    
            ...
            "//xts/acts/测试子系统_lite/测试模块_hal:ActsDemoTest"
        ]    
    }
}
```

**5，测试套件编译命令**

1\) 命令：python build.py wifiiot -b debug

2\) 输出：out/wifiiot

备注：联接类模组acts测试编译中间件为静态库，最终会链接到版本镜像中 ：Hi3861\_wifiiot\_app\_allinone.bin；

## 编写智慧视觉类设备（Ipcamera）acts测试用例<a name="section1997532920813"></a>

hcpptest测试框架是在开源的googletest测试框架的基础上进行的增强和适配。

**1，用例目录规范：测试用例存储到test/xts/acts仓中。**

├── acts

│   ├── BUILD.gn

│   └──测试子系统\_lite

│   │   └── 测试模块\_posix

│   │   │   └──  BUILD.gn

│   │   │   └── src   存放测试用例源码

**2，测试模块src下用例编写样例：**

（1）引用测试框架：

需要引用gtest.h  如：\#include "gtest/gtest.h"

```
#include "gtest/gtest.h"
```

（2）定义Setup与TearDown

```
class TestSuite: public testing::Test {
protected:
// SetUpTestCase：测试套预置动作，在第一个TestCase之前执行
static void SetUpTestCase(void){
}
// TearDownTestCase：测试套清理动作，在最后一个TestCase之后执行
static void TearDownTestCase(void){
}
// 用例的预置动作
virtual void SetUp()
{
}
// 用例的清理动作
virtual void TearDown()
{
}
};
```

（3）使用宏定义HWTEST或HWTEST\_F写测试用例

普通测试用例的定义：HWTEST（测试套名称， 测试用例名称， 用例标注）。

包含SetUp和TearDown的测试用例的定义 ：HWTEST\_F（测试套名称， 测试用例名称，用例标注）。

宏定义包括三个参数：测试套件名称，测试用例名称，用例级别。

用例级别取值为如下内容之一:

“Level0”,“Level1”,“Level2”,“Level3”，“Level4”。

```
HWTEST_F(TestSuite, TestCase_0001, Level0) {
// do something
}
```

用例级别说明：

<a name="table10426001094"></a>
<table><thead align="left"><tr id="row342660796"><th class="cellrowborder" valign="top" width="13.751375137513753%" id="mcps1.1.4.1.1"><p id="p7426201917"><a name="p7426201917"></a><a name="p7426201917"></a><strong id="b44261609919"><a name="b44261609919"></a><a name="b44261609919"></a>级别名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="11.08110811081108%" id="mcps1.1.4.1.2"><p id="p18426201294"><a name="p18426201294"></a><a name="p18426201294"></a><strong id="b19426180399"><a name="b19426180399"></a><a name="b19426180399"></a>基本定义</strong></p>
</th>
<th class="cellrowborder" valign="top" width="75.16751675167517%" id="mcps1.1.4.1.3"><p id="p1426100993"><a name="p1426100993"></a><a name="p1426100993"></a><strong id="b134271401992"><a name="b134271401992"></a><a name="b134271401992"></a>测试范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row9427809912"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p124271401594"><a name="p124271401594"></a><a name="p124271401594"></a>Level0</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p1042715015915"><a name="p1042715015915"></a><a name="p1042715015915"></a>冒烟</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p174271501293"><a name="p174271501293"></a><a name="p174271501293"></a>验证关键功能点基本功能/最基本DFX属性在最常见输入下的表现，通过表示功能基本可运行。</p>
</td>
</tr>
<tr id="row7427300915"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p0427501495"><a name="p0427501495"></a><a name="p0427501495"></a>Level1</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p184276018920"><a name="p184276018920"></a><a name="p184276018920"></a>基本</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p1427706911"><a name="p1427706911"></a><a name="p1427706911"></a>验证各功能点基本功能/基本DFX属性在常见输入下的表现，通过表示功能基本可测试。</p>
</td>
</tr>
<tr id="row84271603919"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p11427701094"><a name="p11427701094"></a><a name="p11427701094"></a>Level2</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p84271208910"><a name="p84271208910"></a><a name="p84271208910"></a>重要</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p142711018915"><a name="p142711018915"></a><a name="p142711018915"></a>验证各功能点的基本功能/基本DFX属性在常规输入/常见异常情况下的表现，通过表示功能基本正常可用，可开展Beta。</p>
</td>
</tr>
<tr id="row642715014919"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p9427110794"><a name="p9427110794"></a><a name="p9427110794"></a>Level3</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p2427301499"><a name="p2427301499"></a><a name="p2427301499"></a>一般</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p1442730497"><a name="p1442730497"></a><a name="p1442730497"></a>验证各功能点的全部功能/全部DFX属性在各种常规/非常规输入组合下，或各种正常/异常预置条件组合下的表现。</p>
</td>
</tr>
<tr id="row14427110291"><td class="cellrowborder" valign="top" width="13.751375137513753%" headers="mcps1.1.4.1.1 "><p id="p2427201098"><a name="p2427201098"></a><a name="p2427201098"></a>Level4</p>
</td>
<td class="cellrowborder" valign="top" width="11.08110811081108%" headers="mcps1.1.4.1.2 "><p id="p342770794"><a name="p342770794"></a><a name="p342770794"></a>生僻</p>
</td>
<td class="cellrowborder" valign="top" width="75.16751675167517%" headers="mcps1.1.4.1.3 "><p id="p7427701094"><a name="p7427701094"></a><a name="p7427701094"></a>验证关键功能点在极端异常预置条件下、用户难以触及的异常输入组合下的表现。</p>
</td>
</tr>
</tbody>
</table>

**3，测试模块下用例配置文件样例：（BUILD.gn）**

每个测试模块目录下新建BUILD.gn编译文件，用于指定编译后可执行文件的名称、依赖的头文件、依赖的库等；具体写法如下。每个测试模块将独立编译成.bin可执行文件， 该文件可直接mount到单板上进行测试。

举例：

```
import("//test/xts/tools/build/suite_lite.gni")

hcpptest_suite("ActsDemoTest") {
    suite_name = "acts"
    sources = [
        "src/TestDemo.cpp"
    ]

    include_dirs = [
        "src",
        ...
    ]
    deps = [
        ...
    ]
    cflags = [ "-Wno-error" ]
}

```

4**，acts目录下增加编译选项（BUILD.gn）**

如何将编写的测试代码加入到版本编译中，需要将测试模块加入到acts目录下的编译脚本中，编译脚本为：test/xts/acts/BUILD.gn。

```
 lite_component("acts") {  
...
else if(board_name == "liteos_a") {
        features += [
            ...
            "//xts/acts/测试子系统_lite/测试模块_posix:ActsDemoTest"
        ]
    }
}
```

**5，测试套件编译命令**

1.1 hi3518ev300 :

1）命令：python build.py ipcamera\_hi3518ev300 -b debug

2）输出：out/ipcamera\_hi3518ev300

1.2 hi3516dv300：

1\)  命令：python build.py ipcamera\_hi3516dv300 -b debug

2）输出：out/ipcamera\_hi3516dv300

备注：智慧视觉类设备（Ipcamera）acts独立编译成.bin可执行文件， 该文件可直接mount到单板上进行测试。

## 执行联接类模组acts测试用例<a name="section7879204912"></a>

**1，获取测试大包：**

请在如下目录获取版本镜像，归档目录：out\\wifiiot\\Hi3861\_wifiiot\_app\_allinone.bin。

备注：判断当前版本镜像是否集成acts测试套件方法：在map文件中查看对应.a是否被编译即可，out\\wifiiot\\Hi3861\_wifiiot\_app.map。

**2，版本镜像烧录进开发板**

**3，测试步骤：**

（1）使用串口工具登录开发板，并保存串口打印信息；

（2）重启设备，查看串口日志；

**4，测试结果分析指导：**

（1）基于串口打印日志进行分析；

（2）每个测试套件执行以：Start to run test suite:开始，以xx Tests xx Failures xx Ignored结束。

## 执行智慧视觉类设备（Ipcamera）acts测试用例<a name="section204081752193"></a>

目前的用例执行采用nfs共享的方式，mount到单板去执行；

**1，环境搭建**

1.  使用有限网线或无线将Ipcamera开发板与PC进行连接。
2.  Ipcamera开发板配置IP、子网掩码、网关，确保Ipcamera开发板与PC处于同一个网段。
3.  PC安装nfs服务器并完成注册，启动nfs服务。
4.  Ipcamera开发板配置mount命令，确保Ipcamera开发板可以访问PC端的nfs共享文件。

    格式：mount \[nfs服务器IP\]:\[/nfs共享目录\] \[/Ipcamera开发板目录\] nfs

    举例：

    ```
    mount 192.168.1.10:/nfs /nfs nfs
    ```


**2，用例执行**

（1）基于串口打印日志进行分析；

（2）每个测试套件执行以./测试模块.bin 触发用例执行。

## 涉及仓<a name="section6299103515474"></a>

xts\_acts

xts\_tools\_lite

