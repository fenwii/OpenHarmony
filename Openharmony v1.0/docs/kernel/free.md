# free<a name="ZH-CN_TOPIC_0000001051930299"></a>

## 命令功能<a name="section175151514841"></a>

free命令可显示系统内存的使用情况，同时显示系统的text段、data段、rodata段、bss段大小。

## 命令格式<a name="section8488721749"></a>

free \[_-k | -m_\]

## 参数说明<a name="section27272181949"></a>

**表 1**  参数说明

<a name="table110mcpsimp"></a>
<table><thead align="left"><tr id="row116mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p118mcpsimp"><a name="p118mcpsimp"></a><a name="p118mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p120mcpsimp"><a name="p120mcpsimp"></a><a name="p120mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p122mcpsimp"><a name="p122mcpsimp"></a><a name="p122mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row123mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p125mcpsimp"><a name="p125mcpsimp"></a><a name="p125mcpsimp"></a>无参数</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p127mcpsimp"><a name="p127mcpsimp"></a><a name="p127mcpsimp"></a>以Byte为单位显示。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p129mcpsimp"><a name="p129mcpsimp"></a><a name="p129mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row130mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p132mcpsimp"><a name="p132mcpsimp"></a><a name="p132mcpsimp"></a>-k</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p134mcpsimp"><a name="p134mcpsimp"></a><a name="p134mcpsimp"></a>以KB为单位显示。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p136mcpsimp"><a name="p136mcpsimp"></a><a name="p136mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row137mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p139mcpsimp"><a name="p139mcpsimp"></a><a name="p139mcpsimp"></a>-m</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p141mcpsimp"><a name="p141mcpsimp"></a><a name="p141mcpsimp"></a>以MB为单位显示。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p143mcpsimp"><a name="p143mcpsimp"></a><a name="p143mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section148661259410"></a>

无。

## 使用实例<a name="section68081530242"></a>

举例：分别输入free、free -k、free -m.

## 输出说明<a name="section171235517543"></a>

**图 1**  以三种方式显示内存使用情况<a name="fig478715471421"></a>  
![](figures/以三种方式显示内存使用情况.png "以三种方式显示内存使用情况")

**表 2**  输出说明

<a name="table633mcpsimp"></a>
<table><thead align="left"><tr id="row638mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p640mcpsimp"><a name="p640mcpsimp"></a><a name="p640mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p642mcpsimp"><a name="p642mcpsimp"></a><a name="p642mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row643mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p645mcpsimp"><a name="p645mcpsimp"></a><a name="p645mcpsimp"></a>total</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p647mcpsimp"><a name="p647mcpsimp"></a><a name="p647mcpsimp"></a>表示系统动态内存池总量。</p>
</td>
</tr>
<tr id="row648mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p650mcpsimp"><a name="p650mcpsimp"></a><a name="p650mcpsimp"></a>used</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p652mcpsimp"><a name="p652mcpsimp"></a><a name="p652mcpsimp"></a>表示已使用内存总量。</p>
</td>
</tr>
<tr id="row653mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p655mcpsimp"><a name="p655mcpsimp"></a><a name="p655mcpsimp"></a>free</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p657mcpsimp"><a name="p657mcpsimp"></a><a name="p657mcpsimp"></a>表示未被分配的内存大小。</p>
</td>
</tr>
<tr id="row658mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p660mcpsimp"><a name="p660mcpsimp"></a><a name="p660mcpsimp"></a>heap</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p662mcpsimp"><a name="p662mcpsimp"></a><a name="p662mcpsimp"></a>表示已分配堆大小。</p>
</td>
</tr>
<tr id="row10101624938"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p610724734"><a name="p610724734"></a><a name="p610724734"></a>text</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1510024539"><a name="p1510024539"></a><a name="p1510024539"></a>表示代码段大小。</p>
</td>
</tr>
<tr id="row207288271839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p572872713317"><a name="p572872713317"></a><a name="p572872713317"></a>data</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p272852716315"><a name="p272852716315"></a><a name="p272852716315"></a>表示数据段大小。</p>
</td>
</tr>
<tr id="row1774316321731"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p274343218317"><a name="p274343218317"></a><a name="p274343218317"></a>rodata</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1974319321133"><a name="p1974319321133"></a><a name="p1974319321133"></a>表示只读数据段大小。</p>
</td>
</tr>
<tr id="row121618371536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p0161183720314"><a name="p0161183720314"></a><a name="p0161183720314"></a>bss</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p09295155511"><a name="p09295155511"></a><a name="p09295155511"></a>表示未初始化全局变量占用内存大小。</p>
</td>
</tr>
</tbody>
</table>

