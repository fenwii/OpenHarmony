# Hi3861V100介绍<a name="ZH-CN_TOPIC_0000001054467126"></a>

## 简介<a name="section469617221261"></a>

Hi3861V100是一款高度集成的2.4GHz WiFi SoC芯片，集成IEEE 802.11b/g/n基带和RF电路，RF电路包括功率放大器PA、低 噪声放大器LNA、RF balun、天线开关以及电源管理等模块；支持20MHz标准带宽和5MHz/10MHz窄带宽，提供最大72.2Mbit/s 物理层速率。 Hi3861V100 WiFi基带支持正交频分复用（OFDM）技术，并向下兼容直接序列扩频（DSSS）和补码键控（CCK）技术，支 持IEEE 802.11 b/g/n协议的各种数据速率。 Hi3861V100芯片集成高性能32bit微处理器、硬件安全引擎以及丰富的外设接口，外设接口包括SPI、UART、I2C、PWM、 GPIO和多路ADC，同时支持高速SDIO2.0 Slave接口，最高时钟可达50MHz；芯片内置SRAM和Flash，可独立运行，并支持 在Flash上运行程序。 Hi3861V100芯片适应于智能家电等物联网智能终端领域。

## 架构<a name="section15884114210197"></a>

上海海思Hi3861系列的平台软件对应用层实现了底层屏蔽，并对应用软件直接提供API\(Application Programming Interface\)接口完成相应功能。典型的系统应用架构如下：

**图 1**  系统应用框架图<a name="fig16620102217403"></a>  


![](figures/zh-cn_image_0000001054797626.png)

该框架可以分为以下几个层次：

-   APP层：即应用层。SDK提供的代码示例在SDK的代码目录：app\\demo\\src。
-   API层：提供基于SDK开发的通用接口。
-   Platform平台层：提供SOC系统板级支持包，包括如下功能：
    -   芯片和外围器件驱动
    -   操作系统
    -   系统管理

-   Service服务层：提供包含WiFi等应用协议栈。用于上层应用软件进行数据收发等操作。
-   第三方库：提供给Service服务层或提供给应用层使用的第三方软件库。

## 特点<a name="section12212842173518"></a>

**稳定、可靠的通信能力**

-   支持复杂环境下 TPC、自动速率、弱干扰免疫等可靠性通信算法

**灵活的组网能力**

-   支持 256 节点 Mesh 组网
-   支持标准 20M 带宽组网和 5M/10M 窄带组网

**完善的网络支持**

-   支持 IPv4/IPv6 网络功能
-   支持 DHCPv4/DHCPv6 Client/Server
-   支持 DNS Client 功能
-   支持 mDNS 功能
-   支持 CoAP/MQTT/HTTP/JSON 基础组件

**强大的安全引擎**

-   硬件实现 AES128/256 加解密算法
-   硬件实现 HASH-SHA256、HMAC\_SHA256 算法
-   硬件实现 RSA、ECC 签名校验算法
-   硬件实现真随机数生成，满足 FIPS140-2 随机测试标准
-   硬件支持 TLS/DTLS 加速
-   内部集成 EFUSE，支持安全存储、安全启动、硬件 ID
-   内部集成 MPU 特性，支持内存隔离特性

**开放的操作系统**

-   丰富的低功耗、小内存、高稳定性、高实时性机制
-   灵活的协议支撑和扩展能力
-   二次开发接口
-   多层级开发接口：操作系统适配接口和系统诊断接口、 链路层接口、网络层接口

## 目录<a name="section1464106163817"></a>

SDK根目录结构如下图所示：

<a name="table13927142512394"></a>
<table><thead align="left"><tr id="row15927132514396"><th class="cellrowborder" valign="top" width="27.38%" id="mcps1.1.3.1.1"><p id="p11927325113916"><a name="p11927325113916"></a><a name="p11927325113916"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="72.61999999999999%" id="mcps1.1.3.1.2"><p id="p1292722593913"><a name="p1292722593913"></a><a name="p1292722593913"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row292882517399"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p159281025163910"><a name="p159281025163910"></a><a name="p159281025163910"></a>app</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p417918234"><a name="p417918234"></a><a name="p417918234"></a>应用层代码（其中包含demo程序为参考示例）。</p>
</td>
</tr>
<tr id="row13791175961418"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p1279265920148"><a name="p1279265920148"></a><a name="p1279265920148"></a>boot</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p1579211591149"><a name="p1579211591149"></a><a name="p1579211591149"></a>Flash bootloader代码。</p>
</td>
</tr>
<tr id="row19928225163913"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p2928122511393"><a name="p2928122511393"></a><a name="p2928122511393"></a>build</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p1192882518398"><a name="p1192882518398"></a><a name="p1192882518398"></a>SDK构建所需的库文件、链接文件、配置文件。</p>
</td>
</tr>
<tr id="row12928225173915"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p199281425143911"><a name="p199281425143911"></a><a name="p199281425143911"></a>config</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p792802515395"><a name="p792802515395"></a><a name="p792802515395"></a>SDK系统配置文件。</p>
</td>
</tr>
<tr id="row18928182533911"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p145973615257"><a name="p145973615257"></a><a name="p145973615257"></a>documents</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p41400225239"><a name="p41400225239"></a><a name="p41400225239"></a>文档目录（包括：SDK说明文档）。</p>
</td>
</tr>
<tr id="row15928132512396"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p3928172518391"><a name="p3928172518391"></a><a name="p3928172518391"></a>include</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p0346235152311"><a name="p0346235152311"></a><a name="p0346235152311"></a>API头文件存放目录。</p>
</td>
</tr>
<tr id="row971803313228"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p171813332218"><a name="p171813332218"></a><a name="p171813332218"></a>license</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p14718533192216"><a name="p14718533192216"></a><a name="p14718533192216"></a>SDK开源license声明</p>
</td>
</tr>
<tr id="row15928192593911"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p12928182573915"><a name="p12928182573915"></a><a name="p12928182573915"></a>output</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p05488436238"><a name="p05488436238"></a><a name="p05488436238"></a>编译时生成的目标文件与中间文件（包括：库文件、打印log、生成的二进制文件等）。</p>
</td>
</tr>
<tr id="row2050315115427"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p9503161154215"><a name="p9503161154215"></a><a name="p9503161154215"></a>platform</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p155032116427"><a name="p155032116427"></a><a name="p155032116427"></a>SDK平台相关的文件（包括：镜像、内核驱动模块等）。</p>
</td>
</tr>
<tr id="row1783061594218"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p2083021554215"><a name="p2083021554215"></a><a name="p2083021554215"></a>third_party</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p15830715194212"><a name="p15830715194212"></a><a name="p15830715194212"></a>开源第三方软件目录。</p>
</td>
</tr>
<tr id="row69981918194210"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p159981318154216"><a name="p159981318154216"></a><a name="p159981318154216"></a>tools</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p5998121854210"><a name="p5998121854210"></a><a name="p5998121854210"></a>SDK提供的Linux系统和Windows系统上使用的工具（包括：NV制作工具、签名工具、Menuconfig等）。</p>
</td>
</tr>
<tr id="row415218166102"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p515281614109"><a name="p515281614109"></a><a name="p515281614109"></a>SConstruct</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p1615231614109"><a name="p1615231614109"></a><a name="p1615231614109"></a>SCons编译脚本。</p>
</td>
</tr>
<tr id="row75842056117"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p2058415591118"><a name="p2058415591118"></a><a name="p2058415591118"></a>build.sh</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p558420511112"><a name="p558420511112"></a><a name="p558420511112"></a>启动编译脚本，同时支持“sh build.sh menuconfig”进行客制化配置。</p>
</td>
</tr>
<tr id="row152262035269"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p42263352615"><a name="p42263352615"></a><a name="p42263352615"></a>build_patch.sh</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p1422613353614"><a name="p1422613353614"></a><a name="p1422613353614"></a>解压开源源码包和patch文件编译脚本。</p>
</td>
</tr>
<tr id="row07472124410"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p1574821211416"><a name="p1574821211416"></a><a name="p1574821211416"></a>Makefile</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p126461354552"><a name="p126461354552"></a><a name="p126461354552"></a>支持makefile编译，使用“make”或“make all”启动编译。</p>
</td>
</tr>
<tr id="row26011201747"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p1601420844"><a name="p1601420844"></a><a name="p1601420844"></a>non_factory.mk</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p14611201340"><a name="p14611201340"></a><a name="p14611201340"></a>非厂测版本编译脚本。</p>
</td>
</tr>
<tr id="row17747172410413"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p974719241849"><a name="p974719241849"></a><a name="p974719241849"></a>factory.mk</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p87471724848"><a name="p87471724848"></a><a name="p87471724848"></a>厂测版本编译脚本。</p>
</td>
</tr>
<tr id="row28411416998"><td class="cellrowborder" valign="top" width="27.38%" headers="mcps1.1.3.1.1 "><p id="p1842161613918"><a name="p1842161613918"></a><a name="p1842161613918"></a>NOTICE</p>
</td>
<td class="cellrowborder" valign="top" width="72.61999999999999%" headers="mcps1.1.3.1.2 "><p id="p58427168912"><a name="p58427168912"></a><a name="p58427168912"></a>第三方软件开源声明</p>
</td>
</tr>
</tbody>
</table>

## 许可协议<a name="section1478215290"></a>

-   Hi3861V100自研代码使用基于Apache License Version 2.0许可的hisi版权声明。许可信息和版权信息通常可以在代码开头看到：

```
  / *Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.Licensed under the Apache License,* ... * / 
```

-   Hi3861V100使用的第三方代码遵循软件版本自带的开源许可声明。
-   将生成的库文件统一存放于根目录下的build/libs下。
-   本软件中可能会使用一些开源软件组件。如果这些开源软件组件所适用的许可与本协议内容冲突，则以该开源软件组件的许可为准。

