# date<a name="ZH-CN_TOPIC_0000001051770290"></a>

## 命令功能<a name="section56472016338"></a>

date命令用于查询及设置系统日期和时间。

## 命令格式<a name="section16635112512316"></a>

date

date --help

date +\[_Format_\]

date -s_ _\[_YY/MM/DD_\]

date_ _-s_ _\[_hh:mm:ss_\]__

date -r \[_Filename_\]

## 参数说明<a name="section15896030039"></a>

**表 1**  参数说明

<a name="table3825mcpsimp"></a>
<table><thead align="left"><tr id="row3831mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p3833mcpsimp"><a name="p3833mcpsimp"></a><a name="p3833mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.4.1.2"><p id="p3835mcpsimp"><a name="p3835mcpsimp"></a><a name="p3835mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="28.999999999999996%" id="mcps1.2.4.1.3"><p id="p3837mcpsimp"><a name="p3837mcpsimp"></a><a name="p3837mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row3838mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3840mcpsimp"><a name="p3840mcpsimp"></a><a name="p3840mcpsimp"></a>--help</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.4.1.2 "><p id="p3842mcpsimp"><a name="p3842mcpsimp"></a><a name="p3842mcpsimp"></a>使用帮助。</p>
</td>
<td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.4.1.3 "><p id="p3844mcpsimp"><a name="p3844mcpsimp"></a><a name="p3844mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3845mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3847mcpsimp"><a name="p3847mcpsimp"></a><a name="p3847mcpsimp"></a>+Format</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.4.1.2 "><p id="p3849mcpsimp"><a name="p3849mcpsimp"></a><a name="p3849mcpsimp"></a>根据<strong id="b3850mcpsimp"><a name="b3850mcpsimp"></a><a name="b3850mcpsimp"></a>Format</strong>格式打印日期和时间。</p>
</td>
<td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.4.1.3 "><p id="p3852mcpsimp"><a name="p3852mcpsimp"></a><a name="p3852mcpsimp"></a>--help中列出的占位符。</p>
</td>
</tr>
<tr id="row3853mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3855mcpsimp"><a name="p3855mcpsimp"></a><a name="p3855mcpsimp"></a>-s YY/MM/DD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.4.1.2 "><p id="p3857mcpsimp"><a name="p3857mcpsimp"></a><a name="p3857mcpsimp"></a>设置系统时间，用“/”分割的年月日。</p>
</td>
<td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.4.1.3 "><p id="p3859mcpsimp"><a name="p3859mcpsimp"></a><a name="p3859mcpsimp"></a>&gt;= 1970/01/01</p>
</td>
</tr>
<tr id="row3860mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3862mcpsimp"><a name="p3862mcpsimp"></a><a name="p3862mcpsimp"></a>-s hh:mm:ss</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.4.1.2 "><p id="p3864mcpsimp"><a name="p3864mcpsimp"></a><a name="p3864mcpsimp"></a>设置系统时间，用“:”分割的时分秒。</p>
</td>
<td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.4.1.3 "><p id="p3866mcpsimp"><a name="p3866mcpsimp"></a><a name="p3866mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3867mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3869mcpsimp"><a name="p3869mcpsimp"></a><a name="p3869mcpsimp"></a>-r Filename</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.4.1.2 "><p id="p3871mcpsimp"><a name="p3871mcpsimp"></a><a name="p3871mcpsimp"></a>查询Filename文件的修改时间。</p>
</td>
<td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.4.1.3 "><p id="p3873mcpsimp"><a name="p3873mcpsimp"></a><a name="p3873mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section116361036636"></a>

-   date参数缺省时，默认显示当前系统日期和时间。
-   --help、+Format、-s、-r不能混合使用。

## 使用实例<a name="section021711411237"></a>

举例：

输入date +%Y--%m--%d。

## 输出说明<a name="section17950184414312"></a>

**图 1**  按指定格式打印系统日期<a name="fig152576304517"></a>  
![](figures/按指定格式打印系统日期.png "按指定格式打印系统日期")

