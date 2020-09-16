# ntpdate<a name="ZH-CN_TOPIC_0000001052170282"></a>

## 命令功能<a name="section38494293815"></a>

命令用于从服务器同步系统时间。

## 命令格式<a name="section5503114413387"></a>

ntpdate \[_SERVER\_IP1_\] \[_SERVER\_IP2_\]...

## 参数说明<a name="section136934472383"></a>

**表 1**  参数说明

<a name="table2616mcpsimp"></a>
<table><thead align="left"><tr id="row2622mcpsimp"><th class="cellrowborder" valign="top" width="20.79%" id="mcps1.2.4.1.1"><p id="p2624mcpsimp"><a name="p2624mcpsimp"></a><a name="p2624mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52.480000000000004%" id="mcps1.2.4.1.2"><p id="p2626mcpsimp"><a name="p2626mcpsimp"></a><a name="p2626mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="26.729999999999997%" id="mcps1.2.4.1.3"><p id="p2628mcpsimp"><a name="p2628mcpsimp"></a><a name="p2628mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row2629mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2631mcpsimp"><a name="p2631mcpsimp"></a><a name="p2631mcpsimp"></a>SERVER_IP</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2633mcpsimp"><a name="p2633mcpsimp"></a><a name="p2633mcpsimp"></a>NTP服务器IP。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2634mcpsimpp0"><a name="entry2634mcpsimpp0"></a><a name="entry2634mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section121401651173816"></a>

直接执行ntpdate \[_SERVER\_IP1_\] \[_SERVER\_IP2_\]... ntpdate会获取第一个有效服务器IP的时间并显示。

## 使用实例<a name="section3431554203811"></a>

举例：使用ntpdate命令更新系统时间：ntpdate 192.168.1.3。

## 输出说明<a name="section18638194610115"></a>

```
OHOS # ntpdate 192.168.1.3
time server 192.168.1.3: Mon Jun 13 09:24:25 2016
```

因为板子和服务器时区的不同，获取后的显示时间可能和服务器时间有数小时的差别。

