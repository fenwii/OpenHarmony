# GPIO概述<a name="ZH-CN_TOPIC_0000001051777586"></a>

## 简介<a name="section15318165672215"></a>

GPIO（General-purpose input/output）即通用型输入输出。通常，GPIO控制器通过分组的方式管理所有GPIO管脚，每组GPIO有一个或多个寄存器与之关联，通过读写寄存器完成对GPIO管脚的操作。

GPIO接口定义了操作GPIO管脚的标准方法集合，包括：

-   设置管脚方向： 方向可以是输入或者输出\(暂不支持高阻态\)

-   读写管脚电平值： 电平值可以是低电平或高电平
-   设置管脚中断服务函数：设置一个管脚的中断响应函数，以及中断触发方式
-   使能和禁止管脚中断：禁止或使能管脚中断

## 接口说明<a name="section18977142162418"></a>

**表 1**  GPIO驱动API接口功能介绍

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="19.74%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>功能分类</p>
</th>
<th class="cellrowborder" valign="top" width="32.36%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>接口名</p>
</th>
<th class="cellrowborder" valign="top" width="47.9%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="19.74%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>GPIO读写</p>
</td>
<td class="cellrowborder" valign="top" width="32.36%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>GpioRead</p>
</td>
<td class="cellrowborder" valign="top" width="47.9%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>读管脚电平值</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>GpioWrite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p67306152404"><a name="p67306152404"></a><a name="p67306152404"></a>写管脚电平值</p>
</td>
</tr>
<tr id="row17493124814141"><td class="cellrowborder" rowspan="2" valign="top" width="19.74%" headers="mcps1.2.4.1.1 "><p id="p321814526178"><a name="p321814526178"></a><a name="p321814526178"></a>GPIO配置</p>
</td>
<td class="cellrowborder" valign="top" width="32.36%" headers="mcps1.2.4.1.2 "><p id="p16390153015156"><a name="p16390153015156"></a><a name="p16390153015156"></a>GpioSetDir</p>
</td>
<td class="cellrowborder" valign="top" width="47.9%" headers="mcps1.2.4.1.3 "><p id="p1873761519408"><a name="p1873761519408"></a><a name="p1873761519408"></a>设置管脚方向</p>
</td>
</tr>
<tr id="row10681146181417"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p15390153014151"><a name="p15390153014151"></a><a name="p15390153014151"></a>GpioGetDir</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p974061515406"><a name="p974061515406"></a><a name="p974061515406"></a>获取管脚方向</p>
</td>
</tr>
<tr id="row10288191441518"><td class="cellrowborder" rowspan="4" valign="top" width="19.74%" headers="mcps1.2.4.1.1 "><p id="p13927416134716"><a name="p13927416134716"></a><a name="p13927416134716"></a>GPIO中断设置</p>
<p id="p738165912472"><a name="p738165912472"></a><a name="p738165912472"></a></p>
<p id="p151691515483"><a name="p151691515483"></a><a name="p151691515483"></a></p>
<p id="p6742119204820"><a name="p6742119204820"></a><a name="p6742119204820"></a></p>
</td>
<td class="cellrowborder" valign="top" width="32.36%" headers="mcps1.2.4.1.2 "><p id="p17390113013158"><a name="p17390113013158"></a><a name="p17390113013158"></a>GpioSetIrq</p>
</td>
<td class="cellrowborder" valign="top" width="47.9%" headers="mcps1.2.4.1.3 "><p id="p10314104354416"><a name="p10314104354416"></a><a name="p10314104354416"></a>设置管脚对应的中断服务函数</p>
</td>
</tr>
<tr id="row163795912473"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p523618345323"><a name="p523618345323"></a><a name="p523618345323"></a>GpioUnSetIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1138195912478"><a name="p1138195912478"></a><a name="p1138195912478"></a>取消管脚对应的中断服务函数</p>
</td>
</tr>
<tr id="row155161515124816"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p657344273218"><a name="p657344273218"></a><a name="p657344273218"></a>GpioEnableIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p115163154488"><a name="p115163154488"></a><a name="p115163154488"></a>使能管脚中断</p>
</td>
</tr>
<tr id="row1742119174820"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1865114616324"><a name="p1865114616324"></a><a name="p1865114616324"></a>GpioDisableIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p97421219174820"><a name="p97421219174820"></a><a name="p97421219174820"></a>禁止管脚中断</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>本文涉及的所有接口，仅限内核态使用，不支持在用户态使用。

