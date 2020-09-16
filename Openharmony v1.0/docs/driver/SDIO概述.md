# SDIO概述<a name="ZH-CN_TOPIC_0000001053055057"></a>

## 简介<a name="section1155271783811"></a>

-   SDIO是安全数字输入输出接口（Secure Digital Input and Output）的缩写，是从SD内存卡接口的基础上演化出来的一种外设接口。SDIO接口兼容以前的SD内存卡，并且可以连接支持SDIO接口的设备。
-   SDIO的应用比较广泛，目前，有许多手机都支持SDIO功能，并且很多SDIO外设也被开发出来，使得手机外接外设更加容易。常见的SDIO外设有WLAN、GPS、CAMERA、蓝牙等。
-   SDIO总线有两端，其中一端是主机端（HOST），另一端是设备端（DEVICE）。所有的通信都是由HOST端发出命令开始的，在DEVICE端只要能解析HOST的命令，就可以同HOST进行通信了。SDIO的HOST可以连接多个DEVICE，如下图所示：

    1.  CLK信号：HOST给DEVICE的时钟信号。
    2.  VDD信号：电源信号。
    3.  VSS信号：Ground信号。
    4.  D0-3信号：4条数据线，其中，DAT1信号线复用为中断线，在1BIT模式下DAT0用来传输数据，在4BIT模式下DAT0-DAT3用来传输数据。
    5.  CMD信号：用于HOST发送命令和DEVICE回复响应。

    **图 1**  SDIO的HOST-DEVICE连接示意图<a name="fig1185316527498"></a>  
    

    ![](figures/zh-cn_image_0000001054280608.png)

-   SDIO接口定义了操作SDIO的通用方法集合，包括打开/关闭SDIO控制器、独占/释放HOST、使能/去使能设备、申请/释放中断、读写、获取/设置公共信息等。

## 接口说明<a name="section10204143763819"></a>

**表 1**  SDIO驱动API接口功能介绍

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row1625342317507"><th class="cellrowborder" valign="top" width="21.07%" id="mcps1.2.4.1.1"><p id="p1779183435016"><a name="p1779183435016"></a><a name="p1779183435016"></a>功能分类</p>
</th>
<th class="cellrowborder" valign="top" width="34.04%" id="mcps1.2.4.1.2"><p id="p1879163417502"><a name="p1879163417502"></a><a name="p1879163417502"></a>接口名</p>
</th>
<th class="cellrowborder" valign="top" width="44.89%" id="mcps1.2.4.1.3"><p id="p1379113410506"><a name="p1379113410506"></a><a name="p1379113410506"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row1351945135614"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p146755118566"><a name="p146755118566"></a><a name="p146755118566"></a>SDIO设备打开/关闭接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p1151945185614"><a name="p1151945185614"></a><a name="p1151945185614"></a>SdioOpen</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p85110451565"><a name="p85110451565"></a><a name="p85110451565"></a>打开指定总线号的SDIO控制器</p>
</td>
</tr>
<tr id="row1062610995616"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p136261793568"><a name="p136261793568"></a><a name="p136261793568"></a>SdioClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p062614919566"><a name="p062614919566"></a><a name="p062614919566"></a>关闭SDIO控制器</p>
</td>
</tr>
<tr id="row337105133315"><td class="cellrowborder" rowspan="6" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p07631557153319"><a name="p07631557153319"></a><a name="p07631557153319"></a>SDIO读写接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p34551320121416"><a name="p34551320121416"></a><a name="p34551320121416"></a>SdioReadBytes</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p748062291415"><a name="p748062291415"></a><a name="p748062291415"></a>从指定地址开始，增量读取指定长度的数据</p>
</td>
</tr>
<tr id="row9317134301618"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p10345104001412"><a name="p10345104001412"></a><a name="p10345104001412"></a>SdioWriteBytes</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p113452040141418"><a name="p113452040141418"></a><a name="p113452040141418"></a>从指定地址开始，增量写入指定长度的数据</p>
</td>
</tr>
<tr id="row131301734171616"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p713025410166"><a name="p713025410166"></a><a name="p713025410166"></a>SdioReadBytesFromFixedAddr</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14130165418168"><a name="p14130165418168"></a><a name="p14130165418168"></a>从固定地址读取指定长度的数据</p>
</td>
</tr>
<tr id="row1434434011147"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1913013546161"><a name="p1913013546161"></a><a name="p1913013546161"></a>SdioWriteBytesToFixedAddr</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p111301954131614"><a name="p111301954131614"></a><a name="p111301954131614"></a>向固定地址写入指定长度的数据</p>
</td>
</tr>
<tr id="row364393591410"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1851815711620"><a name="p1851815711620"></a><a name="p1851815711620"></a>SdioReadBytesFromFunc0</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p751875761611"><a name="p751875761611"></a><a name="p751875761611"></a>从SDIO function 0的指定地址空间读取指定长度的数据</p>
</td>
</tr>
<tr id="row17455333175"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1645519318173"><a name="p1645519318173"></a><a name="p1645519318173"></a>SdioWriteBytesToFunc0</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p114552320176"><a name="p114552320176"></a><a name="p114552320176"></a>向SDIO function 0的指定地址空间写入指定长度的数据</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>SDIO设置块大小接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p74531720181413"><a name="p74531720181413"></a><a name="p74531720181413"></a>SdioSetBlockSize</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p247972241411"><a name="p247972241411"></a><a name="p247972241411"></a>设置块的大小</p>
</td>
</tr>
<tr id="row778816813238"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p1578958142317"><a name="p1578958142317"></a><a name="p1578958142317"></a>SDIO获取/设置公共信息接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p378918842311"><a name="p378918842311"></a><a name="p378918842311"></a>SdioGetCommonInfo</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p1078919892313"><a name="p1078919892313"></a><a name="p1078919892313"></a>获取公共信息</p>
</td>
</tr>
<tr id="row5667102342417"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2668623182411"><a name="p2668623182411"></a><a name="p2668623182411"></a>SdioSetCommonInfo</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14668192362419"><a name="p14668192362419"></a><a name="p14668192362419"></a>设置公共信息</p>
</td>
</tr>
<tr id="row1165101111256"><td class="cellrowborder" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p8166161192511"><a name="p8166161192511"></a><a name="p8166161192511"></a>SDIO刷新数据接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p121662112256"><a name="p121662112256"></a><a name="p121662112256"></a>SdioFlushData</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p171661711112519"><a name="p171661711112519"></a><a name="p171661711112519"></a>刷新数据</p>
</td>
</tr>
<tr id="row17388101522515"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p53101413268"><a name="p53101413268"></a><a name="p53101413268"></a>SDIO独占/释放HOST接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p1638881562520"><a name="p1638881562520"></a><a name="p1638881562520"></a>SdioClaimHost</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p143881715152517"><a name="p143881715152517"></a><a name="p143881715152517"></a>独占Host</p>
</td>
</tr>
<tr id="row5352175517251"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p93537557259"><a name="p93537557259"></a><a name="p93537557259"></a>SdioReleaseHost</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1235355511254"><a name="p1235355511254"></a><a name="p1235355511254"></a>释放Host</p>
</td>
</tr>
<tr id="row8759125415269"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p272143815359"><a name="p272143815359"></a><a name="p272143815359"></a>SDIO使能/去使能功能设备接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p6760195452615"><a name="p6760195452615"></a><a name="p6760195452615"></a>SdioEnableFunc</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p9760135417263"><a name="p9760135417263"></a><a name="p9760135417263"></a>使能SDIO功能设备</p>
</td>
</tr>
<tr id="row1166105762620"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p5662175782616"><a name="p5662175782616"></a><a name="p5662175782616"></a>SdioDisableFunc</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p3662135722618"><a name="p3662135722618"></a><a name="p3662135722618"></a>去使能SDIO功能设备</p>
</td>
</tr>
<tr id="row12332331113517"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p188181849203614"><a name="p188181849203614"></a><a name="p188181849203614"></a>SDIO申请/释放中断接口</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p933383133517"><a name="p933383133517"></a><a name="p933383133517"></a>SdioClaimIrq</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p20333431203510"><a name="p20333431203510"></a><a name="p20333431203510"></a>申请中断</p>
</td>
</tr>
<tr id="row173103413357"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2073123413515"><a name="p2073123413515"></a><a name="p2073123413515"></a>SdioReleaseIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1773634153518"><a name="p1773634153518"></a><a name="p1773634153518"></a>释放中断</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>本文涉及的所有接口，目前只支持在内核态使用，不支持在用户态使用。

