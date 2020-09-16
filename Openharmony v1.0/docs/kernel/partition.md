# partition<a name="ZH-CN_TOPIC_0000001052170307"></a>

## 命令功能<a name="section255095212257"></a>

partition命令用来查看flash分区信息。

## 命令格式<a name="section10258056122515"></a>

partition \[_nand / spinor_\]

## 参数说明<a name="section177200581256"></a>

**表 1**  参数说明

<a name="table1425mcpsimp"></a>
<table><thead align="left"><tr id="row1431mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1433mcpsimp"><a name="p1433mcpsimp"></a><a name="p1433mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1435mcpsimp"><a name="p1435mcpsimp"></a><a name="p1435mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1437mcpsimp"><a name="p1437mcpsimp"></a><a name="p1437mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1438mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1440mcpsimp"><a name="p1440mcpsimp"></a><a name="p1440mcpsimp"></a>nand</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1442mcpsimp"><a name="p1442mcpsimp"></a><a name="p1442mcpsimp"></a>显示nand flash分区信息。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1444mcpsimp"><a name="p1444mcpsimp"></a><a name="p1444mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1445mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1447mcpsimp"><a name="p1447mcpsimp"></a><a name="p1447mcpsimp"></a>spinor</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1449mcpsimp"><a name="p1449mcpsimp"></a><a name="p1449mcpsimp"></a>显示spinor flash分区信息。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1451mcpsimp"><a name="p1451mcpsimp"></a><a name="p1451mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section17866411262"></a>

-   partition命令用来查看flash分区信息。
-   仅当使能yaffs文件系统时才可以查看nand flash分区信息，使能jffs或romfs文件系统时可以查看spinor flash分区信息。

## 使用实例<a name="section1927174202610"></a>

举例：partition spinor

## 输出说明<a name="section11321011223"></a>

查看spinor flash分区信息

![](figures/zh-cn_image_0000001052810300.png)

