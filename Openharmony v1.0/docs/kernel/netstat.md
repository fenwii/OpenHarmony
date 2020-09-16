# netstat<a name="ZH-CN_TOPIC_0000001052370301"></a>

## 命令功能<a name="section13469162113816"></a>

netstat是控制台命令,是一个监测TCP/IP网络的非常有用的工具，它可以显示实际的网络连接以及每一个网络接口设备的状态信息。netstat用于显示与TCP、UDP协议相关的统计数据，一般用于检验本设备（单板）各端口的网络连接情况。

## 命令格式<a name="section795712373812"></a>

netstat

## 参数说明<a name="section17629431193817"></a>

无

## 使用指南<a name="section5277153519380"></a>

直接输入命令。

## 使用实例<a name="section108141437163820"></a>

举例：输入netstat

**图 1**  netstat 打印信息<a name="fig51865585412"></a>  
![](figures/netstat-打印信息.png "netstat-打印信息")

## 输出说明<a name="section1357015107117"></a>

**表 1**  输出说明

<a name="table2526mcpsimp"></a>
<table><thead align="left"><tr id="row2531mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p2533mcpsimp"><a name="p2533mcpsimp"></a><a name="p2533mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p2535mcpsimp"><a name="p2535mcpsimp"></a><a name="p2535mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row2536mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2538mcpsimp"><a name="p2538mcpsimp"></a><a name="p2538mcpsimp"></a>Proto</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2540mcpsimp"><a name="p2540mcpsimp"></a><a name="p2540mcpsimp"></a>协议类型。</p>
</td>
</tr>
<tr id="row2546mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2548mcpsimp"><a name="p2548mcpsimp"></a><a name="p2548mcpsimp"></a>Recv-Q</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2550mcpsimp"><a name="p2550mcpsimp"></a><a name="p2550mcpsimp"></a>未被用户读取的数据量。</p>
<p id="p2551mcpsimp"><a name="p2551mcpsimp"></a><a name="p2551mcpsimp"></a>对于Listen TCP，此值为已完成三次握手，但是未被用户accept的TCP连接的数量。</p>
</td>
</tr>
<tr id="row2553mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2555mcpsimp"><a name="p2555mcpsimp"></a><a name="p2555mcpsimp"></a>Send-Q</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1250715415473"><a name="p1250715415473"></a><a name="p1250715415473"></a>对TCP连接，已发送但未确认的数据量。</p>
<p id="p1080412214470"><a name="p1080412214470"></a><a name="p1080412214470"></a>对UDP连接，由于IP地址解析未完成而缓存的数据量。</p>
</td>
</tr>
<tr id="row2558mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2560mcpsimp"><a name="p2560mcpsimp"></a><a name="p2560mcpsimp"></a>Local Address</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2562mcpsimp"><a name="p2562mcpsimp"></a><a name="p2562mcpsimp"></a>本地地址和端口。</p>
</td>
</tr>
<tr id="row2563mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2565mcpsimp"><a name="p2565mcpsimp"></a><a name="p2565mcpsimp"></a>Foreign Address</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2567mcpsimp"><a name="p2567mcpsimp"></a><a name="p2567mcpsimp"></a>远程地址和端口。</p>
</td>
</tr>
<tr id="row2568mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2570mcpsimp"><a name="p2570mcpsimp"></a><a name="p2570mcpsimp"></a>State</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2572mcpsimp"><a name="p2572mcpsimp"></a><a name="p2572mcpsimp"></a>TCP连接状态，UDP此项无意义。</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>形如“========== total sockets 32 ====== unused sockets 22 BootTime 27 s ========== ”，表示一共32个套接字，未使用套接字22个，距系统启动已经过27秒。

