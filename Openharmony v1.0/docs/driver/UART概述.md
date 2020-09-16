# UART概述<a name="ZH-CN_TOPIC_0000001052215244"></a>

## 简介<a name="section14770623164917"></a>

-   UART是通用异步收发传输器（Universal Asynchronous Receiver/Transmitter）的缩写，是通用串行数据总线，用于异步通信。该总线双向通信，可以实现全双工传输。
-   UART应用比较广泛，常用于输出打印信息，也可以外接各种模块，如GPS、蓝牙等。
-   两个UART设备的连接示意图如下，UART与其他模块一般用2线（图1）或4线（图2）相连，它们分别是：
    1.  TX：发送数据端，和对端的RX相连；
    2.  RX：接收数据端，和对端的TX相连；
    3.  RTS：发送请求信号，用于指示本设备是否准备好，可接受数据，和对端CTS相连；
    4.  CTS：允许发送信号，用于判断是否可以向对端发送数据，和对端RTS相连；

        **图 1**  2线UART设备连接示意图<a name="fig209936401896"></a>  
        

        ![](figures/zh-cn_image_0000001053926237.png)

        **图 2**  4线UART设备连接示意图<a name="fig1435614171015"></a>  
        

        ![](figures/zh-cn_image_0000001054007499.png)


-   UART通信之前，收发双方需要约定好一些参数：波特率、数据格式（起始位、数据位、校验位、停止位）等。通信过程中，UART通过TX发送给对端数据，通过RX接收对端发送的数据。当UART接收缓存达到预定的门限值时，RTS变为不可发送数据，对端的CTS检测到不可发送数据，则停止发送数据。
-   UART接口定义了操作UART端口的通用方法集合，包括获取、释放设备句柄、读写数据、获取和设置波特率、获取和设置设备属性。

## 接口说明<a name="section149505462492"></a>

**表 1**  UART驱动API接口功能介绍

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row1223152681611"><th class="cellrowborder" valign="top" width="26.619999999999997%" id="mcps1.2.4.1.1"><p id="p210413571619"><a name="p210413571619"></a><a name="p210413571619"></a>功能分类</p>
</th>
<th class="cellrowborder" valign="top" width="31.369999999999997%" id="mcps1.2.4.1.2"><p id="p810403511614"><a name="p810403511614"></a><a name="p810403511614"></a>接口名</p>
</th>
<th class="cellrowborder" valign="top" width="42.01%" id="mcps1.2.4.1.3"><p id="p110418354161"><a name="p110418354161"></a><a name="p110418354161"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row1638573613415"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p917154316414"><a name="p917154316414"></a><a name="p917154316414"></a>UART获取/释放设备句柄</p>
<p id="p9596111154212"><a name="p9596111154212"></a><a name="p9596111154212"></a></p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p20385163614412"><a name="p20385163614412"></a><a name="p20385163614412"></a>UartOpen</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p12101135184213"><a name="p12101135184213"></a><a name="p12101135184213"></a>UART获取设备句柄</p>
</td>
</tr>
<tr id="row5950143316415"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p149501733134113"><a name="p149501733134113"></a><a name="p149501733134113"></a>UartClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p371073520422"><a name="p371073520422"></a><a name="p371073520422"></a>UART释放设备句柄</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>UART读写接口</p>
<p id="p131072201215"><a name="p131072201215"></a><a name="p131072201215"></a></p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p8296182221219"><a name="p8296182221219"></a><a name="p8296182221219"></a>UartRead</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p16297172213125"><a name="p16297172213125"></a><a name="p16297172213125"></a>从UART设备中读取指定长度的数据</p>
</td>
</tr>
<tr id="row11585016539"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1095722493616"><a name="p1095722493616"></a><a name="p1095722493616"></a>UartWrite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p15297162215122"><a name="p15297162215122"></a><a name="p15297162215122"></a>向UART设备中写入指定长度的数据</p>
</td>
</tr>
<tr id="row8687115843715"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p196317143813"><a name="p196317143813"></a><a name="p196317143813"></a>UART获取/设置波特率接口</p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p166885582375"><a name="p166885582375"></a><a name="p166885582375"></a>UartGetBaud</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p13688358183716"><a name="p13688358183716"></a><a name="p13688358183716"></a>UART获取波特率</p>
</td>
</tr>
<tr id="row18987529382"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p698719214383"><a name="p698719214383"></a><a name="p698719214383"></a>UartSetBaud</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1398712123810"><a name="p1398712123810"></a><a name="p1398712123810"></a>UART设置波特率</p>
</td>
</tr>
<tr id="row1551850115317"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p1629782201218"><a name="p1629782201218"></a><a name="p1629782201218"></a>UART获取/设置设备属性</p>
<p id="p10308192211216"><a name="p10308192211216"></a><a name="p10308192211216"></a></p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p32972022151218"><a name="p32972022151218"></a><a name="p32972022151218"></a>UartGetAttribute</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p13297122216123"><a name="p13297122216123"></a><a name="p13297122216123"></a>UART获取设备属性</p>
</td>
</tr>
<tr id="row7545065311"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p102974224120"><a name="p102974224120"></a><a name="p102974224120"></a>UartSetAttribute</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p152971322111219"><a name="p152971322111219"></a><a name="p152971322111219"></a>UART设置设备属性</p>
</td>
</tr>
<tr id="row14614115403"><td class="cellrowborder" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p1746281144010"><a name="p1746281144010"></a><a name="p1746281144010"></a>UART设置传输模式</p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p1146215112405"><a name="p1146215112405"></a><a name="p1146215112405"></a>UartSetTransMode</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p11303181216414"><a name="p11303181216414"></a><a name="p11303181216414"></a>UART设置传输模式</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>本文涉及的所有接口，仅限内核态使用，不支持在用户态使用。

