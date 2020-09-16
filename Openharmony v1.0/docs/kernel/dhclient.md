# dhclient<a name="ZH-CN_TOPIC_0000001053200896"></a>

## 命令功能<a name="section366714216619"></a>

设置和查看dhclient的参数。

## 命令格式<a name="section8833164614615"></a>

dhclient <_netif name_\>

dhclient -x <_netif name_\>

dhclient -gb <_netif name_\>

dhclient -sv <_vendor_\>

dhclient -gv

dhclient -gd <_index_\>

dhclient -sd <_dns\_ip_\>

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
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2500105121818"><a name="p2500105121818"></a><a name="p2500105121818"></a>&lt;netif name&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>启动对应网卡的dhcp请求。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>网卡名字，eth0。</p>
</td>
</tr>
<tr id="row1110416513817"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p110445143817"><a name="p110445143817"></a><a name="p110445143817"></a>-x &lt;netif name&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1510414514386"><a name="p1510414514386"></a><a name="p1510414514386"></a>关闭对应网卡的dhcp功能。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1410445183811"><a name="p1410445183811"></a><a name="p1410445183811"></a>网卡名字，eth0。</p>
</td>
</tr>
<tr id="row8809123074012"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p180913307408"><a name="p180913307408"></a><a name="p180913307408"></a>-gb &lt;netif name&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p280913309400"><a name="p280913309400"></a><a name="p280913309400"></a>查看对应网卡的dhcp请求是否完成。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p43801815411"><a name="p43801815411"></a><a name="p43801815411"></a>网卡名字，eth0。</p>
</td>
</tr>
<tr id="row46581611174117"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3658171124116"><a name="p3658171124116"></a><a name="p3658171124116"></a>-sv &lt;vendor&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3658131111410"><a name="p3658131111410"></a><a name="p3658131111410"></a>设置dhcp请求的厂商信息。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p14658311184115"><a name="p14658311184115"></a><a name="p14658311184115"></a>厂商信息，长度是32个字符。</p>
</td>
</tr>
<tr id="row14729211134217"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p972915115426"><a name="p972915115426"></a><a name="p972915115426"></a>-gv</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p272951113426"><a name="p272951113426"></a><a name="p272951113426"></a>查看dhcp请求的厂商信息。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p117291111134216"><a name="p117291111134216"></a><a name="p117291111134216"></a>N/A</p>
</td>
</tr>
<tr id="row4940853114219"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p13940185310423"><a name="p13940185310423"></a><a name="p13940185310423"></a>-gd &lt;index&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1194095374213"><a name="p1194095374213"></a><a name="p1194095374213"></a>获取第index个dns server的信息。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p694025334210"><a name="p694025334210"></a><a name="p694025334210"></a>index，0或者1。</p>
</td>
</tr>
<tr id="row196815382432"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p14681238154317"><a name="p14681238154317"></a><a name="p14681238154317"></a>-sd &lt;dns_ip&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4681038144316"><a name="p4681038144316"></a><a name="p4681038144316"></a>设置主dns server的ip。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p4681173884313"><a name="p4681173884313"></a><a name="p4681173884313"></a>dns的ip地址。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section15935131220717"></a>

dhclient eth0

dhclient -x eth0

dhclient -gb eth0

dhclient -sv MFSI

dhclient -gv

dhclient -gd 0

dhclient -sd 8.8.8.8

## 使用实例<a name="section79281818476"></a>

![](figures/zh-cn_image_0000001053224218.png)

## 输出说明<a name="section12742311179"></a>

**表 2**  输出说明

<a name="table487mcpsimp"></a>
<table><thead align="left"><tr id="row492mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p494mcpsimp"><a name="p494mcpsimp"></a><a name="p494mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p496mcpsimp"><a name="p496mcpsimp"></a><a name="p496mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row502mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p583513382179"><a name="p583513382179"></a><a name="p583513382179"></a>dhclient: set vendor info [MFSI] success</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19833143819174"><a name="p19833143819174"></a><a name="p19833143819174"></a>设置厂商信息MFSI信息成功。</p>
</td>
</tr>
<tr id="row1990234224612"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p3902144294612"><a name="p3902144294612"></a><a name="p3902144294612"></a>dns[0]: 192.168.1.100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p13903144284610"><a name="p13903144284610"></a><a name="p13903144284610"></a>dns server ip地址为192.168.1.100。</p>
</td>
</tr>
</tbody>
</table>

