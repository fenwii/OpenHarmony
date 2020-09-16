# mount<a name="ZH-CN_TOPIC_0000001052530288"></a>

## 命令功能<a name="section11631837182"></a>

mount命令用来将设备挂载到指定目录。

## 命令格式<a name="section1697638111820"></a>

mount <_device_\> <_path_\> <_name_\> \[_uid gid_\]

## 参数说明<a name="section1650151221819"></a>

**表 1**  参数说明

<a name="table1338mcpsimp"></a>
<table><thead align="left"><tr id="row1344mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1346mcpsimp"><a name="p1346mcpsimp"></a><a name="p1346mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1348mcpsimp"><a name="p1348mcpsimp"></a><a name="p1348mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1350mcpsimp"><a name="p1350mcpsimp"></a><a name="p1350mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1351mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1353mcpsimp"><a name="p1353mcpsimp"></a><a name="p1353mcpsimp"></a>device</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1355mcpsimp"><a name="p1355mcpsimp"></a><a name="p1355mcpsimp"></a>要挂载的设备（格式为设备所在路径）。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1357mcpsimp"><a name="p1357mcpsimp"></a><a name="p1357mcpsimp"></a>系统拥有的设备。</p>
</td>
</tr>
<tr id="row1358mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1360mcpsimp"><a name="p1360mcpsimp"></a><a name="p1360mcpsimp"></a>path</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1362mcpsimp"><a name="p1362mcpsimp"></a><a name="p1362mcpsimp"></a>指定目录。</p>
<p id="p1363mcpsimp"><a name="p1363mcpsimp"></a><a name="p1363mcpsimp"></a>用户必须具有指定目录中的执行（搜索）许可权。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1365mcpsimp"><a name="p1365mcpsimp"></a><a name="p1365mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1366mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1368mcpsimp"><a name="p1368mcpsimp"></a><a name="p1368mcpsimp"></a>name</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1370mcpsimp"><a name="p1370mcpsimp"></a><a name="p1370mcpsimp"></a>文件系统的种类。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1372mcpsimp"><a name="p1372mcpsimp"></a><a name="p1372mcpsimp"></a>vfat, yaffs, jffs, ramfs, nfs，procfs, romfs.</p>
</td>
</tr>
<tr id="row138821392219"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p15883891213"><a name="p15883891213"></a><a name="p15883891213"></a>uid gid</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p158834917217"><a name="p158834917217"></a><a name="p158834917217"></a>uid是指用户ID。</p>
<p id="p18500185615215"><a name="p18500185615215"></a><a name="p18500185615215"></a>gid是指组ID。</p>
<p id="p519052614387"><a name="p519052614387"></a><a name="p519052614387"></a>可选参数，缺省值uid:0，gid:0。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p178835919211"><a name="p178835919211"></a><a name="p178835919211"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section124541520171912"></a>

mount后加需要挂载的设备信息、指定目录以及设备文件格式，就能成功挂载文件系统到指定目录。

## 使用实例<a name="section7424625171917"></a>

举例：mount /dev/mmcblk0p0 /bin1/vs/sd vfat

## 输出说明<a name="section14757018116"></a>

将/dev/mmcblk0p0 挂载到/bin1/vs/sd目录

![](figures/zh-cn_image_0000001051690323.png)

