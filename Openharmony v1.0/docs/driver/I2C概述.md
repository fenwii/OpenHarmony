# I2C概述<a name="ZH-CN_TOPIC_0000001052778273"></a>

## 简介<a name="section5361140416"></a>

-   I2C\(Inter Integrated Circuit\)总线是由Philips公司开发的一种简单、双向二线制同步串行总线。
-   I2C以主从方式工作，通常有一个主设备和一个或者多个从设备，主从设备通过SDA\(SerialData\)串行数据线以及SCL\(SerialClock\)串行时钟线两根线相连，如[图1 ](#fig1135561232714)所示。

-   I2C数据的传输必须以一个起始信号作为开始条件，以一个结束信号作为传输的停止条件。数据传输以字节为单位，高位在前，逐个bit进行传输。
-   I2C总线上的每一个设备都可以作为主设备或者从设备，而且每一个设备都会对应一个唯一的地址，当主设备需要和某一个从设备通信时，通过广播的方式，将从设备地址写到总线上，如果某个从设备符合此地址，将会发出应答信号，建立传输。

-   I2C接口定义了完成I2C传输的通用方法集合，包括：

    -   I2C控制器管理:  打开或关闭I2C控制器
    -   I2C消息传输：通过消息传输结构体数组进行自定义传输

    **图 1**  I2C物理连线示意图<a name="fig1135561232714"></a>  
    ![](figures/I2C物理连线示意图.png "I2C物理连线示意图")


## 接口说明<a name="section7606310210"></a>

**表 1**  I2C驱动API接口功能介绍

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="18.63%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>功能分类</p>
</th>
<th class="cellrowborder" valign="top" width="28.03%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>接口名</p>
</th>
<th class="cellrowborder" valign="top" width="53.339999999999996%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="18.63%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>I2C控制器管理接口</p>
</td>
<td class="cellrowborder" valign="top" width="28.03%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>I2cOpen</p>
</td>
<td class="cellrowborder" valign="top" width="53.339999999999996%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>打开I2C控制器</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>I2cClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p573815197171"><a name="p573815197171"></a><a name="p573815197171"></a>关闭I2C控制器</p>
</td>
</tr>
<tr id="row15108165391412"><td class="cellrowborder" valign="top" width="18.63%" headers="mcps1.2.4.1.1 "><p id="p91084533141"><a name="p91084533141"></a><a name="p91084533141"></a>I2c消息传输接口</p>
</td>
<td class="cellrowborder" valign="top" width="28.03%" headers="mcps1.2.4.1.2 "><p id="p13901730101511"><a name="p13901730101511"></a><a name="p13901730101511"></a>I2cTransfer</p>
</td>
<td class="cellrowborder" valign="top" width="53.339999999999996%" headers="mcps1.2.4.1.3 "><p id="p12738111912171"><a name="p12738111912171"></a><a name="p12738111912171"></a>自定义传输</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>本文涉及的所有接口，仅限内核态使用，不支持在用户态使用。

