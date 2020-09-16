# pmm<a name="ZH-CN_TOPIC_0000001054783044"></a>

## 命令功能<a name="section445335110416"></a>

查看系统内存物理页及pagecache物理页使用情况。

## 命令格式<a name="section1795712553416"></a>

pmm

## 参数说明<a name="section92544592410"></a>

无

## 使用指南<a name="section104151141252"></a>

Debug版本才具备的命令。

## 使用实例<a name="section11545171957"></a>

输入pmm

## 输出说明<a name="section075617368542"></a>

**图 1**  查看物理页使用情况<a name="fig19209202618618"></a>  
![](figures/查看物理页使用情况.png "查看物理页使用情况")

**表 1**  输出说明

<a name="table5579102611579"></a>
<table><thead align="left"><tr id="row12579162613572"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p18579122619578"><a name="p18579122619578"></a><a name="p18579122619578"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p11579182635718"><a name="p11579182635718"></a><a name="p11579182635718"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1457942675720"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2058042605713"><a name="p2058042605713"></a><a name="p2058042605713"></a>phys_seg</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1058062614579"><a name="p1058062614579"></a><a name="p1058062614579"></a>物理页控制块地址信息</p>
</td>
</tr>
<tr id="row14580192616575"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p858062615712"><a name="p858062615712"></a><a name="p858062615712"></a>base</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1858082617577"><a name="p1858082617577"></a><a name="p1858082617577"></a>第一个物理页地址，即物理页内存起始地址</p>
</td>
</tr>
<tr id="row17580826115719"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p5580226155713"><a name="p5580226155713"></a><a name="p5580226155713"></a>size</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p85808262572"><a name="p85808262572"></a><a name="p85808262572"></a>物理页内存大小</p>
</td>
</tr>
<tr id="row161931831175912"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p201931631185913"><a name="p201931631185913"></a><a name="p201931631185913"></a>free_pages</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1919383125911"><a name="p1919383125911"></a><a name="p1919383125911"></a>空闲物理页数量</p>
</td>
</tr>
<tr id="row1397105119596"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p0397951175918"><a name="p0397951175918"></a><a name="p0397951175918"></a>active anon</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1139715117599"><a name="p1139715117599"></a><a name="p1139715117599"></a>pagecache中，活跃的匿名页数量</p>
</td>
</tr>
<tr id="row16409173520010"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p941012351409"><a name="p941012351409"></a><a name="p941012351409"></a>inactive anon</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1341012355019"><a name="p1341012355019"></a><a name="p1341012355019"></a>pagecache中，不活跃的匿名页数量</p>
</td>
</tr>
<tr id="row467016386014"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p10670103818015"><a name="p10670103818015"></a><a name="p10670103818015"></a>active file</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1267012382019"><a name="p1267012382019"></a><a name="p1267012382019"></a>pagecache中，活跃的文件页数量</p>
</td>
</tr>
<tr id="row18966641507"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p5966741706"><a name="p5966741706"></a><a name="p5966741706"></a>inactive file</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p17966174115018"><a name="p17966174115018"></a><a name="p17966174115018"></a>pagecache中，不活跃的文件页数量</p>
</td>
</tr>
<tr id="row13183445101"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p318394514018"><a name="p318394514018"></a><a name="p318394514018"></a>pmm pages</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1218312452014"><a name="p1218312452014"></a><a name="p1218312452014"></a>total：总的物理页数，used：已使用的物理页数，free：空闲的物理页数</p>
</td>
</tr>
</tbody>
</table>

