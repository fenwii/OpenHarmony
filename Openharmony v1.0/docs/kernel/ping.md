# ping<a name="ZH-CN_TOPIC_0000001052810296"></a>

## 命令功能<a name="section119672573385"></a>

ping命令用于测试网络连接是否正常。

## 命令格式<a name="section869419010390"></a>

ping_ _\[_-n cnt_\] \[_-w interval_\] \[_-l data\_len_\]_ <IP\>_

ping \[_-t_\] \[_-w interval_\]  _<IP\>_

ping  _-k_

## 参数说明<a name="section9877183173918"></a>

**表 1**  参数说明

<a name="table2664mcpsimp"></a>
<table><thead align="left"><tr id="row2670mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p2672mcpsimp"><a name="p2672mcpsimp"></a><a name="p2672mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p2674mcpsimp"><a name="p2674mcpsimp"></a><a name="p2674mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p2676mcpsimp"><a name="p2676mcpsimp"></a><a name="p2676mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row2677mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2679mcpsimp"><a name="p2679mcpsimp"></a><a name="p2679mcpsimp"></a>IP</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2681mcpsimp"><a name="p2681mcpsimp"></a><a name="p2681mcpsimp"></a>要测试是否网络连通的IPv4地址。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="entry2682mcpsimpp0"><a name="entry2682mcpsimpp0"></a><a name="entry2682mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row2690mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2692mcpsimp"><a name="p2692mcpsimp"></a><a name="p2692mcpsimp"></a>-n cnt</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2694mcpsimp"><a name="p2694mcpsimp"></a><a name="p2694mcpsimp"></a>执行的次数，不带本参数则默认为4次。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2696mcpsimp"><a name="p2696mcpsimp"></a><a name="p2696mcpsimp"></a>1-65535</p>
</td>
</tr>
<tr id="row2697mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2699mcpsimp"><a name="p2699mcpsimp"></a><a name="p2699mcpsimp"></a>-w interval</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2701mcpsimp"><a name="p2701mcpsimp"></a><a name="p2701mcpsimp"></a>发送两次ping包的时间间隔，单位毫秒。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p971414819577"><a name="p971414819577"></a><a name="p971414819577"></a>&gt;0</p>
</td>
</tr>
<tr id="row2703mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2705mcpsimp"><a name="p2705mcpsimp"></a><a name="p2705mcpsimp"></a>-l data_len</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2707mcpsimp"><a name="p2707mcpsimp"></a><a name="p2707mcpsimp"></a>ping包，即ICMP echo request报文的数据长</p>
<p id="p2708mcpsimp"><a name="p2708mcpsimp"></a><a name="p2708mcpsimp"></a>度，不包含ICMP包头。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2710mcpsimp"><a name="p2710mcpsimp"></a><a name="p2710mcpsimp"></a>0-65500</p>
</td>
</tr>
<tr id="row2711mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2713mcpsimp"><a name="p2713mcpsimp"></a><a name="p2713mcpsimp"></a>-t</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2715mcpsimp"><a name="p2715mcpsimp"></a><a name="p2715mcpsimp"></a>表示永久ping，直到使用ping -k杀死ping线</p>
<p id="p2716mcpsimp"><a name="p2716mcpsimp"></a><a name="p2716mcpsimp"></a>程。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p20501182215720"><a name="p20501182215720"></a><a name="p20501182215720"></a>N/A</p>
</td>
</tr>
<tr id="row2718mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2720mcpsimp"><a name="p2720mcpsimp"></a><a name="p2720mcpsimp"></a>-k</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2722mcpsimp"><a name="p2722mcpsimp"></a><a name="p2722mcpsimp"></a>杀死ping线程，停止ping。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p940472325719"><a name="p940472325719"></a><a name="p940472325719"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section1097046193914"></a>

-   ping命令用来测试到目的IP的网络连接是否正常，参数为目的IP地址。
-   如果目的IP不可达，会显示请求超时。
-   如果显示发送错误，说明没有到目的IP的路由。
-   命令需要启动TCP/IP协议栈后才能使用。

## 使用实例<a name="section14564129113911"></a>

举例：输入ping 169.254.60.115

## 输出说明<a name="section1621732891215"></a>

**图 1**  ping tftp 服务器地址<a name="fig525762695417"></a>  
![](figures/ping-tftp-服务器地址.png "ping-tftp-服务器地址")

