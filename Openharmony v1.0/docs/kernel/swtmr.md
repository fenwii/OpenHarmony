# swtmr<a name="ZH-CN_TOPIC_0000001051611538"></a>

## 命令功能<a name="section166171064814"></a>

swtmr命令用于查询系统软件定时器相关信息。

## 命令格式<a name="section424011111682"></a>

swtmr \[_ID_\]

## 参数说明<a name="section1268410459465"></a>

**表 1**  参数说明

<a name="table517mcpsimp"></a>
<table><thead align="left"><tr id="row523mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p525mcpsimp"><a name="p525mcpsimp"></a><a name="p525mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p527mcpsimp"><a name="p527mcpsimp"></a><a name="p527mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p529mcpsimp"><a name="p529mcpsimp"></a><a name="p529mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row530mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p532mcpsimp"><a name="p532mcpsimp"></a><a name="p532mcpsimp"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p534mcpsimp"><a name="p534mcpsimp"></a><a name="p534mcpsimp"></a>软件定时器ID号。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p536mcpsimp"><a name="p536mcpsimp"></a><a name="p536mcpsimp"></a>[0,0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section169806213815"></a>

-   参数缺省时，默认显示所有软件定时器的相关信息。
-   swtmr后加ID号时，显示ID对应的软件定时器相关信息。

## 使用实例<a name="section16676026389"></a>

举例：输入swtmr和swtmr 1

## 输出说明<a name="section1541991614710"></a>

**图 1**  查询所有软件定时器相关信息<a name="fig9860611451"></a>  
![](figures/查询所有软件定时器相关信息.png "查询所有软件定时器相关信息")

**图 2**  查询对应 ID 的软件定时器信息<a name="fig22051415124512"></a>  
![](figures/查询对应-ID-的软件定时器信息.png "查询对应-ID-的软件定时器信息")

**表 2**  输出说明

<a name="table551mcpsimp"></a>
<table><thead align="left"><tr id="row556mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p558mcpsimp"><a name="p558mcpsimp"></a><a name="p558mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p560mcpsimp"><a name="p560mcpsimp"></a><a name="p560mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row561mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p563mcpsimp"><a name="p563mcpsimp"></a><a name="p563mcpsimp"></a>SwTmrID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p565mcpsimp"><a name="p565mcpsimp"></a><a name="p565mcpsimp"></a>软件定时器ID。</p>
</td>
</tr>
<tr id="row566mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p568mcpsimp"><a name="p568mcpsimp"></a><a name="p568mcpsimp"></a>State</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p570mcpsimp"><a name="p570mcpsimp"></a><a name="p570mcpsimp"></a>软件定时器状态。</p>
<p id="p88402543474"><a name="p88402543474"></a><a name="p88402543474"></a>状态可能为："UnUsed", "Created", "Ticking"。</p>
</td>
</tr>
<tr id="row571mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p573mcpsimp"><a name="p573mcpsimp"></a><a name="p573mcpsimp"></a>Mode</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p575mcpsimp"><a name="p575mcpsimp"></a><a name="p575mcpsimp"></a>软件定时器模式。</p>
<p id="p657320204499"><a name="p657320204499"></a><a name="p657320204499"></a>模式可能为："Once", "Period", "NSD（单次定时器，定时结束后不会自动删除）"。</p>
</td>
</tr>
<tr id="row576mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p578mcpsimp"><a name="p578mcpsimp"></a><a name="p578mcpsimp"></a>Interval</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p580mcpsimp"><a name="p580mcpsimp"></a><a name="p580mcpsimp"></a>软件定时器使用的Tick数。</p>
</td>
</tr>
<tr id="row581mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p583mcpsimp"><a name="p583mcpsimp"></a><a name="p583mcpsimp"></a>Count</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p585mcpsimp"><a name="p585mcpsimp"></a><a name="p585mcpsimp"></a>软件定时器已经工作的次数。</p>
</td>
</tr>
<tr id="row586mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p588mcpsimp"><a name="p588mcpsimp"></a><a name="p588mcpsimp"></a>Arg</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p590mcpsimp"><a name="p590mcpsimp"></a><a name="p590mcpsimp"></a>传入的参数。</p>
</td>
</tr>
<tr id="row591mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p593mcpsimp"><a name="p593mcpsimp"></a><a name="p593mcpsimp"></a>handlerAddr</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p595mcpsimp"><a name="p595mcpsimp"></a><a name="p595mcpsimp"></a>回调函数的地址。</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>-   swtmr命令的ID参数输入形式以十进制形式表示或十六进制形式表示皆可。
>-   swtmr命令的ID参数在\[0, 当前软件定时器个数 - 1\]范围内时，返回对应ID的软件定时器的状态；其他取值时返回错误提示。

