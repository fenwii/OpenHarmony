# sem<a name="ZH-CN_TOPIC_0000001052810290"></a>

## 命令功能<a name="section366714216619"></a>

sem命令用于查询系统内核信号量相关信息。

## 命令格式<a name="section8833164614615"></a>

sem \[_ID__ / fulldata_\]

## 参数说明<a name="section12809111019453"></a>

**表 1**  参数说明

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p453mcpsimp"><a name="p453mcpsimp"></a><a name="p453mcpsimp"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p455mcpsimp"><a name="p455mcpsimp"></a><a name="p455mcpsimp"></a>信号ID号。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p457mcpsimp"><a name="p457mcpsimp"></a><a name="p457mcpsimp"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row458mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p460mcpsimp"><a name="p460mcpsimp"></a><a name="p460mcpsimp"></a>fulldata</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p462mcpsimp"><a name="p462mcpsimp"></a><a name="p462mcpsimp"></a>查询所有在用的信号量信息，打印信息包括如下：SemID, Count, Original Count, Creater TaskEntry, Last Access Time。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="entry464mcpsimpp0"><a name="entry464mcpsimpp0"></a><a name="entry464mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section15935131220717"></a>

-   参数缺省时，显示所有的信号量的使用数及信号量总数。
-   sem后加ID，显示对应ID信号量的使用数。
-   参数fulldata依赖于LOSCFG\_DEBUG\_SEMAPHORE，使用时通过menuconfig在配置项中开启"Enable Semaphore Debugging"：

    Debug  ---\> Enable a Debug Version ---\> Enable Debug LiteOS Kernel Resource ---\> Enable Semaphore Debugging


## 使用实例<a name="section79281818476"></a>

举例1：输入 sem fulldata

## 输出说明<a name="section1975118519456"></a>

**图 1**  查询所有在用的信号量信息<a name="fig18750181620222"></a>  
![](figures/查询所有在用的信号量信息.png "查询所有在用的信号量信息")

**表 2**  输出说明

<a name="table487mcpsimp"></a>
<table><thead align="left"><tr id="row492mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p494mcpsimp"><a name="p494mcpsimp"></a><a name="p494mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p496mcpsimp"><a name="p496mcpsimp"></a><a name="p496mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row497mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p499mcpsimp"><a name="p499mcpsimp"></a><a name="p499mcpsimp"></a>SemID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p501mcpsimp"><a name="p501mcpsimp"></a><a name="p501mcpsimp"></a>信号量ID。</p>
</td>
</tr>
<tr id="row502mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p504mcpsimp"><a name="p504mcpsimp"></a><a name="p504mcpsimp"></a>Count</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p506mcpsimp"><a name="p506mcpsimp"></a><a name="p506mcpsimp"></a>信号量使用数。</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>● sem命令的ID参数输入形式以十进制形式表示或十六进制形式表示皆可。
>● sem命令的ID参数在\[0, 1023\]范围内时，返回对应ID的信号量的状态（如果对应ID的信号量未被使用则进行提示）；其他取值时返回参数错误的提示。

