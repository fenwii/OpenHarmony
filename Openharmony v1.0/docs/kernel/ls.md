# ls<a name="ZH-CN_TOPIC_0000001051451593"></a>

## 命令功能<a name="section6538163771614"></a>

ls命令用来显示当前目录的内容。

## 命令格式<a name="section45881743111616"></a>

ls \[_path_\]

## 参数说明<a name="section17528148171617"></a>

**表 1**  参数说明

<a name="table1244mcpsimp"></a>
<table><thead align="left"><tr id="row1250mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1252mcpsimp"><a name="p1252mcpsimp"></a><a name="p1252mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1254mcpsimp"><a name="p1254mcpsimp"></a><a name="p1254mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1256mcpsimp"><a name="p1256mcpsimp"></a><a name="p1256mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1257mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1259mcpsimp"><a name="p1259mcpsimp"></a><a name="p1259mcpsimp"></a>path</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1261mcpsimp"><a name="p1261mcpsimp"></a><a name="p1261mcpsimp"></a>path为空时，显示当前目录的内容。</p>
<p id="p1262mcpsimp"><a name="p1262mcpsimp"></a><a name="p1262mcpsimp"></a>path为无效文件名时，显示失败，提示：</p>
<p id="p1263mcpsimp"><a name="p1263mcpsimp"></a><a name="p1263mcpsimp"></a>ls error: No such directory。</p>
<p id="p1264mcpsimp"><a name="p1264mcpsimp"></a><a name="p1264mcpsimp"></a>path为有效目录路径时，会显示对应目录下的内容。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1266mcpsimp"><a name="p1266mcpsimp"></a><a name="p1266mcpsimp"></a>1.为空。</p>
<p id="p1267mcpsimp"><a name="p1267mcpsimp"></a><a name="p1267mcpsimp"></a>2.有效的目录路径。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section041212533166"></a>

-   ls命令显示当前目录的内容。
-   ls可以显示文件的大小。
-   proc下ls无法统计文件大小，显示为0。

## 使用实例<a name="section986105716167"></a>

举例：输入ls

## 输出说明<a name="section2036124918592"></a>

**图 1**  查看当前系统路径下的目录，显示的内容如下<a name="fig17933775508"></a>  
![](figures/查看当前系统路径下的目录-显示的内容如下.png "查看当前系统路径下的目录-显示的内容如下")

