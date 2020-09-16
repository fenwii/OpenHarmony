# format<a name="ZH-CN_TOPIC_0000001051611540"></a>

## 命令功能<a name="section1922331919169"></a>

format指令用于格式化磁盘。

## 命令格式<a name="section249226169"></a>

format <_dev\_inodename_\> <_sectors_\> <_option_\> \[_label_\]

## 参数说明<a name="section985173416177"></a>

**表 1**  参数说明

<a name="table1183mcpsimp"></a>
<table><thead align="left"><tr id="row1188mcpsimp"><th class="cellrowborder" valign="top" width="34%" id="mcps1.2.3.1.1"><p id="p1190mcpsimp"><a name="p1190mcpsimp"></a><a name="p1190mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="66%" id="mcps1.2.3.1.2"><p id="p1192mcpsimp"><a name="p1192mcpsimp"></a><a name="p1192mcpsimp"></a>参数说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1193mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1195mcpsimp"><a name="p1195mcpsimp"></a><a name="p1195mcpsimp"></a>dev_inodename</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><p id="p1197mcpsimp"><a name="p1197mcpsimp"></a><a name="p1197mcpsimp"></a>设备名。</p>
</td>
</tr>
<tr id="row1203mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1205mcpsimp"><a name="p1205mcpsimp"></a><a name="p1205mcpsimp"></a>sectors</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><p id="p1207mcpsimp"><a name="p1207mcpsimp"></a><a name="p1207mcpsimp"></a>分配的单元内存或扇区大小，如果输入0表示参数为空。（取值必须为0或2的幂，fat32下最大值为128，取值0表示自动选择合适的簇大小，不同size的分区，可用的簇大小范围不同，错误的簇大小指定可能导致格式化失败）。</p>
</td>
</tr>
<tr id="row1208mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1210mcpsimp"><a name="p1210mcpsimp"></a><a name="p1210mcpsimp"></a>option</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><div class="p" id="p1212mcpsimp"><a name="p1212mcpsimp"></a><a name="p1212mcpsimp"></a>格式化选项，用来选择文件系统的类型，有如下几种参数选择：<a name="ul10971366369"></a><a name="ul10971366369"></a><ul id="ul10971366369"><li>0x01：FMT_FAT</li><li>0x02：FMT_FAT32</li><li>0x07：FMT_ANY</li><li>0x08：FMT_ERASE （USB不支持该选项）</li></ul>
</div>
<p id="p28366459374"><a name="p28366459374"></a><a name="p28366459374"></a>传入其他值皆为非法值，将由系统自动选择格式化方式。若格式化U盘时低格位为 1，会出现错误打印。</p>
</td>
</tr>
<tr id="row1213mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1215mcpsimp"><a name="p1215mcpsimp"></a><a name="p1215mcpsimp"></a>label</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><p id="p1217mcpsimp"><a name="p1217mcpsimp"></a><a name="p1217mcpsimp"></a>该参数为可选参数，输入值应为字符串，用来指定卷标名。当输入字符串"null"时，则把之前设置的卷标名清空。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section1510162714162"></a>

-   format指令用于格式化磁盘，设备名可以在dev目录下查找。format时必须安装存储卡。
-   format只能格式化U盘、sd和mmc卡，对Nand flash和Nor flash格式化不起作用。
-   sectors参数必须传入合法值，传入非法参数可能引发异常。

## 使用实例<a name="section25691431161611"></a>

举例：输入format /dev/mmcblk0 128 2

## 输出说明<a name="section17368112365920"></a>

结果如下

![](figures/zh-cn_image_0000001052370307.png)

