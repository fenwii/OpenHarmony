# rm<a name="ZH-CN_TOPIC_0000001052370299"></a>

## 命令功能<a name="section181141523142613"></a>

rm命令用来删除文件或文件夹。

## 命令格式<a name="section8800926132619"></a>

rm \[_-r_\] \[_dirname / filename_\]

## 参数说明<a name="section15476229152617"></a>

**表 1**  参数说明

<a name="table1507mcpsimp"></a>
<table><thead align="left"><tr id="row1513mcpsimp"><th class="cellrowborder" valign="top" width="22.220000000000002%" id="mcps1.2.4.1.1"><p id="p1515mcpsimp"><a name="p1515mcpsimp"></a><a name="p1515mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="51.519999999999996%" id="mcps1.2.4.1.2"><p id="p1517mcpsimp"><a name="p1517mcpsimp"></a><a name="p1517mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="26.26%" id="mcps1.2.4.1.3"><p id="p1519mcpsimp"><a name="p1519mcpsimp"></a><a name="p1519mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1520mcpsimp"><td class="cellrowborder" valign="top" width="22.220000000000002%" headers="mcps1.2.4.1.1 "><p id="p1522mcpsimp"><a name="p1522mcpsimp"></a><a name="p1522mcpsimp"></a>-r</p>
</td>
<td class="cellrowborder" valign="top" width="51.519999999999996%" headers="mcps1.2.4.1.2 "><p id="p1524mcpsimp"><a name="p1524mcpsimp"></a><a name="p1524mcpsimp"></a>可选参数，若是删除目录则需要该参数。</p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="p1526mcpsimp"><a name="p1526mcpsimp"></a><a name="p1526mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1527mcpsimp"><td class="cellrowborder" valign="top" width="22.220000000000002%" headers="mcps1.2.4.1.1 "><p id="p1529mcpsimp"><a name="p1529mcpsimp"></a><a name="p1529mcpsimp"></a>dirname/filename</p>
</td>
<td class="cellrowborder" valign="top" width="51.519999999999996%" headers="mcps1.2.4.1.2 "><p id="p1531mcpsimp"><a name="p1531mcpsimp"></a><a name="p1531mcpsimp"></a>要删除文件或文件夹的名称，支持输入路径。</p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="p1533mcpsimp"><a name="p1533mcpsimp"></a><a name="p1533mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section10578163215262"></a>

-   rm命令一次只能删除一个文件或文件夹。
-   rm -r命令可以删除非空目录。

## 使用实例<a name="section18548133511263"></a>

举例：

1.  输入rm log1.txt
2.  输入rm -r sd

## 输出说明<a name="section1565323814265"></a>

**图 1**  用 rm 命令删除文件 log1.txt<a name="fig886111415523"></a>  
![](figures/用-rm-命令删除文件-log1-txt.png "用-rm-命令删除文件-log1-txt")

**图 2**  用 rm -r 删除目录 sd<a name="fig20659194885211"></a>  
![](figures/用-rm--r-删除目录-sd.png "用-rm--r-删除目录-sd")

