# umount<a name="ZH-CN_TOPIC_0000001051451595"></a>

## 命令功能<a name="section365125133520"></a>

umount命令用来卸载指定文件系统。

## 命令格式<a name="section9615254123512"></a>

umount \[_dir_\]

## 参数说明<a name="section63446577355"></a>

**表 1**  参数说明

<a name="table1713mcpsimp"></a>
<table><thead align="left"><tr id="row1719mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1721mcpsimp"><a name="p1721mcpsimp"></a><a name="p1721mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1723mcpsimp"><a name="p1723mcpsimp"></a><a name="p1723mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1725mcpsimp"><a name="p1725mcpsimp"></a><a name="p1725mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1726mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1728mcpsimp"><a name="p1728mcpsimp"></a><a name="p1728mcpsimp"></a>dir</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1730mcpsimp"><a name="p1730mcpsimp"></a><a name="p1730mcpsimp"></a>需要卸载文件系统对应的目录。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1732mcpsimp"><a name="p1732mcpsimp"></a><a name="p1732mcpsimp"></a>系统已挂载的文件系统的目录。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section92931509368"></a>

umount后加上需要卸载的指定文件系统的目录，即将指定文件系统卸载。

## 使用实例<a name="section144311323616"></a>

举例：umount /bin1/vs/sd

## 输出说明<a name="section360525113611"></a>

将已在/bin1/vs/sd挂载的文件系统卸载

**图 1**  umount输出示例<a name="fig2304134118557"></a>  
![](figures/umount输出示例.png "umount输出示例")

