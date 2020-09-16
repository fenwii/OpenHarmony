# Hi3516dv300介绍<a name="ZH-CN_TOPIC_0000001054788038"></a>

## 简介<a name="section469617221261"></a>

上海海思媒体软件开发包用于适配不同芯片复杂的底层处理，为“媒体子系统”提供基础的多媒体处理功能。主要功能有：音视频采集、音视频编解码、音视频输出、视频前处理、封装、解封装、文件管理、存储管理、日志系统等。该软件包功能对应"媒体子系统"框架中红色框标注部分，如图1所示。

**图 1**  多媒体子系统框架图<a name="fig16620102217403"></a>  


![](figures/zh-cn_image_0000001054242379.png)

## 目录<a name="section1464106163817"></a>

上海海思媒体软件开发包所在的目录为vendor\\hisi\\hi35xx，子目录结构如以下7个表所示：

**表 1**  hardware目录结构

<a name="table15811112718910"></a>
<table><thead align="left"><tr id="row1181112718915"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1934518501188"><a name="p1934518501188"></a><a name="p1934518501188"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p1580541185"><a name="p1580541185"></a><a name="p1580541185"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row581122715917"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7463423141214"><a name="p7463423141214"></a><a name="p7463423141214"></a>hi35xx\hardware</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p164391323161216"><a name="p164391323161216"></a><a name="p164391323161216"></a>媒体南向接口实现、框架及芯片对接层库目录</p>
</td>
</tr>
</tbody>
</table>

**表 2**  hi35xx\_init目录结构

<a name="table78291813141320"></a>
<table><thead align="left"><tr id="row10829191361312"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p14686442191820"><a name="p14686442191820"></a><a name="p14686442191820"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p18412546191811"><a name="p18412546191811"></a><a name="p18412546191811"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row98296133139"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p582915130134"><a name="p582915130134"></a><a name="p582915130134"></a>hi35xx\hi35xx_init\hi3516dv300</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1882971311313"><a name="p1882971311313"></a><a name="p1882971311313"></a>编译打包16dv300内核镜像的编译脚本</p>
</td>
</tr>
<tr id="row1316718286548"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p167506431548"><a name="p167506431548"></a><a name="p167506431548"></a>hi35xx\hi35xx_init\hi3518ev300</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p5165122819547"><a name="p5165122819547"></a><a name="p5165122819547"></a>编译打包18ev300内核镜像的编译脚本</p>
</td>
</tr>
</tbody>
</table>

**表 3**  hi3516dv300目录结构

<a name="table13927142512394"></a>
<table><thead align="left"><tr id="row15927132514396"><th class="cellrowborder" valign="top" width="49.54%" id="mcps1.2.3.1.1"><p id="p11927325113916"><a name="p11927325113916"></a><a name="p11927325113916"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50.46000000000001%" id="mcps1.2.3.1.2"><p id="p1292722593913"><a name="p1292722593913"></a><a name="p1292722593913"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row292882517399"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p016319301785"><a name="p016319301785"></a><a name="p016319301785"></a>hi35xx\hi3516dv300</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p417918234"><a name="p417918234"></a><a name="p417918234"></a>Hi3516DV300芯片驱动软件，包括：设备配置信息目录、Camera南向接口业务功能适配目录、媒体驱动子目录、媒体用户态库子目录、uboot的差异化内容目录、OS安全启动编译目录、NOTICE文件</p>
</td>
</tr>
<tr id="row12433440114610"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p7433164013460"><a name="p7433164013460"></a><a name="p7433164013460"></a>hi35xx\hi3516dv300\config</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p44332040164615"><a name="p44332040164615"></a><a name="p44332040164615"></a>Hi3516DV300设备配置信息</p>
</td>
</tr>
<tr id="row10905180365"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p18913187366"><a name="p18913187366"></a><a name="p18913187366"></a>hi35xx\hi3516dv300\hi3516dv300_adapter</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p491141817367"><a name="p491141817367"></a><a name="p491141817367"></a>Hi3516DV300Camera南向接口业务功能适配</p>
</td>
</tr>
<tr id="row13791175961418"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p81728197910"><a name="p81728197910"></a><a name="p81728197910"></a>hi35xx\hi3516dv300\module_init\lib</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p1579211591149"><a name="p1579211591149"></a><a name="p1579211591149"></a>Hi3516DV300芯片媒体各模块驱动对应的库、LICENSE文件</p>
</td>
</tr>
<tr id="row19928225163913"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p1505235197"><a name="p1505235197"></a><a name="p1505235197"></a>hi35xx\hi3516dv300\module_init\src</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p1192882518398"><a name="p1192882518398"></a><a name="p1192882518398"></a>内核驱动初始化源代码、LICENSE文件</p>
</td>
</tr>
<tr id="row12928225173915"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p199281425143911"><a name="p199281425143911"></a><a name="p199281425143911"></a>hi35xx\hi3516dv300\soc\lib</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p792802515395"><a name="p792802515395"></a><a name="p792802515395"></a>Hi3516DV300芯片的媒体库文件、LICENSE文件</p>
</td>
</tr>
<tr id="row18928182533911"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p145973615257"><a name="p145973615257"></a><a name="p145973615257"></a>hi35xx\hi3516dv300\uboot\out\boot</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p41400225239"><a name="p41400225239"></a><a name="p41400225239"></a>采用hi35xx\third_party\uboot\u-boot-2020.01和hi35xx\hi3516dv300\uboot\reg\reg_info_hi3516dv300.bin编译成的uboot、README文件</p>
</td>
</tr>
<tr id="row15928132512396"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p3928172518391"><a name="p3928172518391"></a><a name="p3928172518391"></a>hi35xx\hi3516dv300\uboot\reg</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p0346235152311"><a name="p0346235152311"></a><a name="p0346235152311"></a>uboot配置文件、LICENSE文件</p>
</td>
</tr>
<tr id="row971803313228"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p13833522117"><a name="p13833522117"></a><a name="p13833522117"></a>hi35xx\hi3516dv300\uboot\secureboot_ohos</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p93264915116"><a name="p93264915116"></a><a name="p93264915116"></a>鸿蒙OS安全启动相关的编译脚本</p>
</td>
</tr>
<tr id="row15928192593911"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p12928182573915"><a name="p12928182573915"></a><a name="p12928182573915"></a>hi35xx\hi3516dv300\uboot\secureboot_release</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p05488436238"><a name="p05488436238"></a><a name="p05488436238"></a>生成安全uboot的源代码、License目录</p>
</td>
</tr>
</tbody>
</table>

**表 4**  hi3518ev300目录结构

<a name="table13215173091517"></a>
<table><thead align="left"><tr id="row142151300157"><th class="cellrowborder" valign="top" width="49.54%" id="mcps1.2.3.1.1"><p id="p621573013151"><a name="p621573013151"></a><a name="p621573013151"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50.46000000000001%" id="mcps1.2.3.1.2"><p id="p17215730121510"><a name="p17215730121510"></a><a name="p17215730121510"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row182151730121511"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p1421613011152"><a name="p1421613011152"></a><a name="p1421613011152"></a>hi35xx\hi3518ev300</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p1216113013158"><a name="p1216113013158"></a><a name="p1216113013158"></a>Hi3518EV300芯片驱动软件，包括：设备配置信息目录、Camera南向接口业务功能适配目录、媒体驱动子目录、媒体用户态库子目录、uboot的差异化内容目录、OS安全启动编译目录、NOTICE文件</p>
</td>
</tr>
<tr id="row52295515460"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p17230175184614"><a name="p17230175184614"></a><a name="p17230175184614"></a>hi35xx\hi3518ev300\config</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p822544125611"><a name="p822544125611"></a><a name="p822544125611"></a>Hi3518EV300设备配置信息</p>
</td>
</tr>
<tr id="row31652035113710"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p316616358374"><a name="p316616358374"></a><a name="p316616358374"></a>hi35xx\hi3518ev300\hi3518ev300_adapter</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p316683511373"><a name="p316683511373"></a><a name="p316683511373"></a>Hi3518EV300Camera南向接口业务功能适配</p>
</td>
</tr>
<tr id="row621623012152"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p2417546181513"><a name="p2417546181513"></a><a name="p2417546181513"></a>hi35xx\hi3518ev300\module_init\lib</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p22161630161512"><a name="p22161630161512"></a><a name="p22161630161512"></a>Hi3518EV300芯片媒体各模块驱动对应的库、LICENSE文件</p>
</td>
</tr>
<tr id="row1721673013157"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p175919515150"><a name="p175919515150"></a><a name="p175919515150"></a>hi35xx\hi3518ev300\module_init\src</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p1621683081514"><a name="p1621683081514"></a><a name="p1621683081514"></a>内核驱动初始化源代码、LICENSE文件</p>
</td>
</tr>
<tr id="row12216830171513"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p6216123061511"><a name="p6216123061511"></a><a name="p6216123061511"></a>hi35xx\hi3518ev300\soc\lib</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p521673071510"><a name="p521673071510"></a><a name="p521673071510"></a>Hi3518EV300芯片的媒体库文件、LICENSE文件</p>
</td>
</tr>
<tr id="row8216930101511"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p12216173091514"><a name="p12216173091514"></a><a name="p12216173091514"></a>hi35xx\hi3518ev300\uboot\out\boot</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p3216133071518"><a name="p3216133071518"></a><a name="p3216133071518"></a>采用hi35xx\third_party\uboot\u-boot-2020.01和hi35xx\hi3518ev300\uboot\reg\reg_info_hi3518ev300.bin编译成的uboot、README文件</p>
</td>
</tr>
<tr id="row15216153091518"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p122167306159"><a name="p122167306159"></a><a name="p122167306159"></a>hi35xx\hi3518ev300\uboot\reg</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p1821663017152"><a name="p1821663017152"></a><a name="p1821663017152"></a>uboot配置文件、LICENSE文件</p>
</td>
</tr>
<tr id="row192160309156"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p192164307151"><a name="p192164307151"></a><a name="p192164307151"></a>hi35xx\hi3518ev300\uboot\secureboot_ohos</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p92161630121517"><a name="p92161630121517"></a><a name="p92161630121517"></a>鸿蒙OS安全启动相关的编译脚本</p>
</td>
</tr>
<tr id="row1121612304158"><td class="cellrowborder" valign="top" width="49.54%" headers="mcps1.2.3.1.1 "><p id="p11216530151510"><a name="p11216530151510"></a><a name="p11216530151510"></a>hi35xx\hi3518ev300\uboot\secureboot_release</p>
</td>
<td class="cellrowborder" valign="top" width="50.46000000000001%" headers="mcps1.2.3.1.2 "><p id="p42162301157"><a name="p42162301157"></a><a name="p42162301157"></a>生成安全uboot的源代码、License目录</p>
</td>
</tr>
</tbody>
</table>

**表 5**  middleware目录结构

<a name="table9651175972417"></a>
<table><thead align="left"><tr id="row1965112590241"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p52878711199"><a name="p52878711199"></a><a name="p52878711199"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p86951910151919"><a name="p86951910151919"></a><a name="p86951910151919"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row16653185915240"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p20653155942417"><a name="p20653155942417"></a><a name="p20653155942417"></a>hi35xx\middleware\source\common</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1065385913243"><a name="p1065385913243"></a><a name="p1065385913243"></a>南向组件公共模块库目录</p>
</td>
</tr>
<tr id="row186531759192419"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1865345914243"><a name="p1865345914243"></a><a name="p1865345914243"></a>hi35xx\middleware\source\component</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19653205992414"><a name="p19653205992414"></a><a name="p19653205992414"></a>南向组件非公共模块库目录</p>
</td>
</tr>
<tr id="row6653125952412"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p5653105910248"><a name="p5653105910248"></a><a name="p5653105910248"></a>hi35xx\middleware\source\thirdparty</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p17653135914241"><a name="p17653135914241"></a><a name="p17653135914241"></a>南向插件依赖第三方开源软件目录</p>
</td>
</tr>
</tbody>
</table>

**表 6**  platform目录结构

<a name="table397031661516"></a>
<table><thead align="left"><tr id="row109701916151514"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p67071239192"><a name="p67071239192"></a><a name="p67071239192"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p11213142711199"><a name="p11213142711199"></a><a name="p11213142711199"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row12971131610154"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p997151621512"><a name="p997151621512"></a><a name="p997151621512"></a>hi35xx\platform</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1971161620156"><a name="p1971161620156"></a><a name="p1971161620156"></a>hi35xx平台驱动</p>
</td>
</tr>
</tbody>
</table>

**表 7**  third\_party目录结构

<a name="table16381640161517"></a>
<table><thead align="left"><tr id="row33814041510"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1020912335191"><a name="p1020912335191"></a><a name="p1020912335191"></a>目录</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p770173621912"><a name="p770173621912"></a><a name="p770173621912"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row12381640101512"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p14505145412188"><a name="p14505145412188"></a><a name="p14505145412188"></a>hi35xx\third_party\uboot\u-boot-2020.01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p14381240161511"><a name="p14381240161511"></a><a name="p14381240161511"></a>uboot开源代码</p>
</td>
</tr>
</tbody>
</table>

## 约束<a name="section0364124983015"></a>

当前支持Hi3518EV300、Hi3516DV300芯片。

## 许可协议<a name="section1478215290"></a>

## hi3516dv300许可说明<a name="section172811306502"></a>

-   hi35xx\\hi3516dv300\\module\_init\\lib和hi35xx\\hi3516dv300\\soc\\lib里面为上海海思的自研库，遵循上海海思的LICENSE，这两个目录下均有LICENSE文件，LICENSE文件结尾可以看到版权信息：

    ```
    Copyright (C) 2020 Hisilicon (Shanghai) Technologies Co., Ltd. All rights reserved.
    ```

-   hi35xx\\hi3516dv300\\module\_init\\src目录下为上海海思自研代码，使用基于Apache License Version 2.0许可的Hisilicon \(Shanghai\) 版权声明，在该目录下有Apache License Version 2.0的LICENSE文件，许可信息和版权信息通常可以在文件开头看到：

    ```
     / *Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED. Licensed under the Apache License,* ... * / 
    ```

-   hi35xx\\hi3516dv300\\uboot\\reg为上海海思的二进制文件，遵循上海海思的LICENSE，该目录下有LICENSE文件，LICENSE文件结尾可以看到：

    ```
    Copyright (C) 2020 Hisilicon (Shanghai) Technologies Co., Ltd. All rights reserved.
    ```

-   hi35xx\\hi3516dv300\\uboot\\out\\boot是由u-boot-2020.01和reg\_info\_hi3516dv300.bin编译成的uboot二进制文件，完全遵从u-boot-2020.01的整体协议，具体请参看hi35xx\\third\_party\\uboot\\u-boot-2020.01\\Licenses目录下的README。
-   hi35xx\\hi3516dv300\\uboot\\secureboot\_release为安全uboot的开源代码，其中自研的部分使用基于GPL许可的Hisilicon \(Shanghai\) 版权声明，在该目录下有License目录，许可信息和版权信息通常可以在文件开头看到：

    ```
     / *Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED. 
       *
       * This program is free software; you can redistribute  it and/or modify it
       * under  the terms of  the GNU General  Public License as published by the
       * Free Software Foundation;  either version 2 of the  License, or (at your
       * option) any later version.
       * ... * / 
    ```


-   hi35xx\\hi3516dv300\\NOTICE文件描述了使用到的三款开源软件：Das U-Boot 2020.01、mbed TLS 2.16.6、fdk-aac v2.0.1。

## hi3518ev300许可说明<a name="section172983094910"></a>

-   hi35xx\\hi3518ev300\\module\_init\\lib和hi35xx\\hi3518ev300\\soc\\lib里面为上海海思的自研库，遵循上海海思的LICENSE，这两个目录下均有LICENSE文件，LICENSE文件结尾可以看到版权信息：

    ```
    Copyright (C) 2020 Hisilicon (Shanghai) Technologies Co., Ltd. All rights reserved.
    ```

-   hi35xx\\hi3518ev300\\module\_init\\src目录下为上海海思自研代码，使用基于Apache License Version 2.0许可的Hisilicon \(Shanghai\) 版权声明，在该目录下有Apache License Version 2.0的LICENSE文件，许可信息和版权信息通常可以在文件开头看到：

    ```
     / *Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED. Licensed under the Apache License,* ... * / 
    ```

-   hi35xx\\hi3518ev300\\uboot\\reg为上海海思的二进制文件，遵循上海海思的LICENSE，该目录下有LICENSE文件，LICENSE文件结尾可以看到：

    ```
    Copyright (C) 2020 Hisilicon (Shanghai) Technologies Co., Ltd. All rights reserved.
    ```

-   hi35xx\\hi3518ev300\\uboot\\out\\boot是由u-boot-2020.01和reg\_info\_hi3518ev300.bin编译成的uboot二进制文件，完全遵从u-boot-2020.01的整体协议，具体请参看hi35xx\\third\_party\\uboot\\u-boot-2020.01\\Licenses目录下的README。
-   hi35xx\\hi3518ev300\\uboot\\secureboot\_release为安全uboot的开源代码，其中自研的部分使用基于GPL许可的Hisilicon \(Shanghai\) 版权声明，在该目录下有License目录，许可信息和版权信息通常可以在文件开头看到：

    ```
     / *Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED. 
       *
       * This program is free software; you can redistribute  it and/or modify it
       * under  the terms of  the GNU General  Public License as published by the
       * Free Software Foundation;  either version 2 of the  License, or (at your
       * option) any later version.
       * ... * / 
    ```

-   hi35xx\\hi3518ev300\\NOTICE文件描述了使用到的三款开源软件：Das U-Boot 2020.01、mbed TLS 2.16.6、fdk-aac v2.0.1。

## third\_party许可说明<a name="section148702720527"></a>

hi35xx\\third\_party\\uboot\\u-boot-2020.01为uboot开源代码，遵循软件版本自带的开源许可声明，具体请参看hi35xx\\third\_party\\uboot\\u-boot-2020.01\\Licenses目录下的README。

