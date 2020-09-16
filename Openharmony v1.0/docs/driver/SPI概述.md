# SPI概述<a name="ZH-CN_TOPIC_0000001053057951"></a>

## 简介<a name="section9202632114011"></a>

-   SPI是串行外设接口（Serial Peripheral Interface）的缩写，是一种高速的，全双工，同步的通信总线。
-   SPI是由Motorola公司开发，用于在主设备和从设备之间进行通信，常用于与闪存、实时时钟、传感器以及模数转换器等进行通信。
-   SPI以主从方式工作，通常有一个主设备和一个或者多个从设备。主设备和从设备之间一般用4根线相连，它们分别是：
    -   SCLK – 时钟信号，由主设备产生；
    -   MOSI – 主设备数据输出，从设备数据输入；
    -   MISO – 主设备数据输入，从设备数据输出；
    -   CS – 片选，从设备使能信号，由主设备控制。


-   一个主设备和两个从设备的连接示意图如[图1](#fig15227181812587)所示，Device A和Device B共享主设备的SCLK、MISO和MOSI三根引脚，Device A的片选CS0连接主设备的CS0，Device B的片选CS1连接主设备的CS1。

**图 1**  SPI主从设备连接示意图。<a name="fig15227181812587"></a>  


![](figures/zh-cn_image_0000001054142582.png)

-   SPI通信通常由主设备发起，通过以下步骤完成一次通信：

1.  通过CS选中要通信的从设备，在任意时刻，一个主设备上最多只能有一个从设备被选中。
2.  通过SCLK给选中的从设备提供时钟信号。
3.  基于SCLK时钟信号，主设备数据通过MOSI发送给从设备，同时通过MISO接收从设备发送的数据，完成通信。

-   根据SCLK时钟信号的CPOL（Clock Polarity，时钟极性）和CPHA（Clock Phase，时钟相位）的不同组合，SPI有以下四种工作模式：
    -   CPOL=0，CPHA=0 时钟信号idle状态为低电平，第一个时钟边沿采样数据。
    -   CPOL=0，CPHA=1 时钟信号idle状态为低电平，第二个时钟边沿采样数据。
    -   CPOL=1，CPHA=0 时钟信号idle状态为高电平，第一个时钟边沿采样数据。
    -   CPOL=1，CPHA=1 时钟信号idle状态为高电平，第二个时钟边沿采样数据。


-   SPI接口定义了操作SPI设备的通用方法集合，包括：
    -   SPI设备句柄获取和释放。
    -   SPI读写:  从SPI设备读取或写入指定长度数据。
    -   SPI自定义传输：通过消息传输结构体执行任意读写组合过程。
    -   SPI设备配置：获取和设置SPI设备属性。


>![](public_sys-resources/icon-note.gif) **说明：** 
>当前只支持主机模式，不支持从机模式。

## 接口说明<a name="section1859594134119"></a>

**表 1**  SPI驱动API接口功能介绍

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" align="left" valign="top" width="20.857914208579142%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>功能分类</p>
</th>
<th class="cellrowborder" align="left" valign="top" width="23.36766323367663%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>接口名</p>
</th>
<th class="cellrowborder" align="left" valign="top" width="55.77442255774422%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row1651292212306"><td class="cellrowborder" rowspan="2" valign="top" width="20.857914208579142%" headers="mcps1.2.4.1.1 "><p id="p1387414255305"><a name="p1387414255305"></a><a name="p1387414255305"></a>SPI设备句柄获取释放接口</p>
</td>
<td class="cellrowborder" valign="top" width="23.36766323367663%" headers="mcps1.2.4.1.2 "><p id="p8874825143014"><a name="p8874825143014"></a><a name="p8874825143014"></a>SpiOpen</p>
</td>
<td class="cellrowborder" valign="top" width="55.77442255774422%" headers="mcps1.2.4.1.3 "><p id="p1087432513307"><a name="p1087432513307"></a><a name="p1087432513307"></a>获取SPI设备句柄</p>
</td>
</tr>
<tr id="row1429083612305"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1956614106311"><a name="p1956614106311"></a><a name="p1956614106311"></a>SpiClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p829111362306"><a name="p829111362306"></a><a name="p829111362306"></a>释放SPI设备句柄</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="3" valign="top" width="20.857914208579142%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>SPI读写接口</p>
</td>
<td class="cellrowborder" valign="top" width="23.36766323367663%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>SpiRead</p>
</td>
<td class="cellrowborder" valign="top" width="55.77442255774422%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>读取指定长度的数据</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>SpiWrite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p573815197171"><a name="p573815197171"></a><a name="p573815197171"></a>写入指定长度的数据</p>
</td>
</tr>
<tr id="row1766145611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p183904373018"><a name="p183904373018"></a><a name="p183904373018"></a>SpiTransfer</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1639011313303"><a name="p1639011313303"></a><a name="p1639011313303"></a>SPI数据传输接口</p>
</td>
</tr>
<tr id="row1020919129159"><td class="cellrowborder" rowspan="2" valign="top" width="20.857914208579142%" headers="mcps1.2.4.1.1 "><p id="p82092126154"><a name="p82092126154"></a><a name="p82092126154"></a>SPI设备配置接口</p>
<p id="p6794153701111"><a name="p6794153701111"></a><a name="p6794153701111"></a></p>
</td>
<td class="cellrowborder" valign="top" width="23.36766323367663%" headers="mcps1.2.4.1.2 "><p id="p1739013012154"><a name="p1739013012154"></a><a name="p1739013012154"></a>SpiSetCfg</p>
</td>
<td class="cellrowborder" valign="top" width="55.77442255774422%" headers="mcps1.2.4.1.3 "><p id="p073910197173"><a name="p073910197173"></a><a name="p073910197173"></a>根据指定参数，配置SPI设备</p>
</td>
</tr>
<tr id="row379443710118"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p4333154919111"><a name="p4333154919111"></a><a name="p4333154919111"></a>SpiGetCfg</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p11333649171117"><a name="p11333649171117"></a><a name="p11333649171117"></a>获取SPI设备配置参数</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>本文涉及的所有接口，仅限内核态使用，不支持在用户态使用。

