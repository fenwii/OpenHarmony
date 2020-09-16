# dns<a name="ZH-CN_TOPIC_0000001051930305"></a>

## 命令功能<a name="section997513673713"></a>

命令用于查看和设置单板dns服务器地址。

## 命令格式<a name="section146015943711"></a>

dns <_1-2_\> <_IP_\>

dns  _-a_

## 参数说明<a name="section5732111163716"></a>

**表 1**  参数说明

<a name="table1942mcpsimp"></a>
<table><thead align="left"><tr id="row1948mcpsimp"><th class="cellrowborder" valign="top" width="20.79%" id="mcps1.2.4.1.1"><p id="p1950mcpsimp"><a name="p1950mcpsimp"></a><a name="p1950mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52.480000000000004%" id="mcps1.2.4.1.2"><p id="p1952mcpsimp"><a name="p1952mcpsimp"></a><a name="p1952mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="26.729999999999997%" id="mcps1.2.4.1.3"><p id="p1954mcpsimp"><a name="p1954mcpsimp"></a><a name="p1954mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1955mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p1957mcpsimp"><a name="p1957mcpsimp"></a><a name="p1957mcpsimp"></a>&lt;1-2&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p1959mcpsimp"><a name="p1959mcpsimp"></a><a name="p1959mcpsimp"></a>选择设置第一个还是第二个DNS服务器。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="p1961mcpsimp"><a name="p1961mcpsimp"></a><a name="p1961mcpsimp"></a>1~2</p>
</td>
</tr>
<tr id="row1962mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p1964mcpsimp"><a name="p1964mcpsimp"></a><a name="p1964mcpsimp"></a>&lt;IP&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p1966mcpsimp"><a name="p1966mcpsimp"></a><a name="p1966mcpsimp"></a>服务器IP地址。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry1967mcpsimpp0"><a name="entry1967mcpsimpp0"></a><a name="entry1967mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row1968mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p1970mcpsimp"><a name="p1970mcpsimp"></a><a name="p1970mcpsimp"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p1972mcpsimp"><a name="p1972mcpsimp"></a><a name="p1972mcpsimp"></a>显示当前设置情况。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry1973mcpsimpp0"><a name="entry1973mcpsimpp0"></a><a name="entry1973mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section15642141417371"></a>

无。

## 使用实例<a name="section1995841617370"></a>

举例：

1.  检查当前DNS设置。
2.  设置第二个DNS服务器IP。
3.  检查DNS设置是否成功。

## 输出说明<a name="section1114210258917"></a>

1.  检查当前DNS设置：

    ```
    OHOS # dns -a
    dns1: 208.61.222.222
    dns2: 0.0.0.0
    ```

2.  设置第二个DNS服务器IP：

    ```
    OHOS # dns 2 192.168.1.2
    ```

3.  检查DNS设置是否成功：

    ```
    OHOS # dns -a
    dns1: 208.61.222.222
    dns2: 192.168.1.2
    ```


