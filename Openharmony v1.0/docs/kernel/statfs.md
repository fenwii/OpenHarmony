# statfs<a name="ZH-CN_TOPIC_0000001052810294"></a>

## 命令功能<a name="section153921657152613"></a>

statfs命令用来打印文件系统的信息，如该文件系统类型、总大小、可用大小等信息。

## 命令格式<a name="section135391102717"></a>

statfs \[_directory_\]

## 参数说明<a name="section074312314279"></a>

**表 1**  参数说明

<a name="table1597mcpsimp"></a>
<table><thead align="left"><tr id="row1603mcpsimp"><th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.1"><p id="p1605mcpsimp"><a name="p1605mcpsimp"></a><a name="p1605mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.2"><p id="p1607mcpsimp"><a name="p1607mcpsimp"></a><a name="p1607mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p1609mcpsimp"><a name="p1609mcpsimp"></a><a name="p1609mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1610mcpsimp"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p1612mcpsimp"><a name="p1612mcpsimp"></a><a name="p1612mcpsimp"></a>directory</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1615mcpsimp"><a name="p1615mcpsimp"></a><a name="p1615mcpsimp"></a>文件系统的路径。</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1617mcpsimp"><a name="p1617mcpsimp"></a><a name="p1617mcpsimp"></a>必须是存在的文件系统，并且其支持statfs命令，当前支持的文件系统有：JFFS2，FAT，NFS。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section133816772712"></a>

打印信息因文件系统而异。

## 使用实例<a name="section526149182717"></a>

以nfs文件系统为例：

statfs /nfs

**图 1**  statfs输出说明<a name="fig1810654276"></a>  
![](figures/statfs输出说明.png "statfs输出说明")

