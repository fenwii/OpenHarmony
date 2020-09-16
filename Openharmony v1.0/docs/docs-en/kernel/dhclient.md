# dhclient<a name="EN-US_TOPIC_0000001053200896"></a>

## Command Function<a name="section366714216619"></a>

This command is used to set and view  **dhclient**  parameters.

## Syntax<a name="section8833164614615"></a>

dhclient <_netif name_\>

dhclient -x <_netif name_\>

dhclient -gb <_netif name_\>

dhclient -sv <_vendor_\>

dhclient -gv

dhclient -gd <_index_\>

dhclient -sd <_dns\_ip_\>

## Parameter Description<a name="section12809111019453"></a>

**Table  1**  Parameters

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a><strong id="b20999054421160"><a name="b20999054421160"></a><a name="b20999054421160"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a><strong id="b16991513175018"><a name="b16991513175018"></a><a name="b16991513175018"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a><strong id="b9837196561160"><a name="b9837196561160"></a><a name="b9837196561160"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2500105121818"><a name="p2500105121818"></a><a name="p2500105121818"></a>&lt;netif name&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>Starts the DHCP request of the network interface card (NIC).</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>NIC name, <strong id="b178511243205513"><a name="b178511243205513"></a><a name="b178511243205513"></a>eth0</strong></p>
</td>
</tr>
<tr id="row1110416513817"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p110445143817"><a name="p110445143817"></a><a name="p110445143817"></a>-x &lt;netif name&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1510414514386"><a name="p1510414514386"></a><a name="p1510414514386"></a>Disables the DHCP function for the NIC.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1410445183811"><a name="p1410445183811"></a><a name="p1410445183811"></a>NIC name, <strong id="b2042412121517"><a name="b2042412121517"></a><a name="b2042412121517"></a>eth0</strong></p>
</td>
</tr>
<tr id="row8809123074012"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p180913307408"><a name="p180913307408"></a><a name="p180913307408"></a>-gb &lt;netif name&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p280913309400"><a name="p280913309400"></a><a name="p280913309400"></a>Checks whether the DHCP request of the NIC is complete.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p43801815411"><a name="p43801815411"></a><a name="p43801815411"></a>NIC name, <strong id="b223722716111"><a name="b223722716111"></a><a name="b223722716111"></a>eth0</strong></p>
</td>
</tr>
<tr id="row46581611174117"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3658171124116"><a name="p3658171124116"></a><a name="p3658171124116"></a>-sv &lt;vendor&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3658131111410"><a name="p3658131111410"></a><a name="p3658131111410"></a>Sets the vendor information of a DHCP request.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p14658311184115"><a name="p14658311184115"></a><a name="p14658311184115"></a>Vendor information (The value is a string of 32 characters.)</p>
</td>
</tr>
<tr id="row14729211134217"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p972915115426"><a name="p972915115426"></a><a name="p972915115426"></a>-gv</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p272951113426"><a name="p272951113426"></a><a name="p272951113426"></a>Displays the vendor information in a DHCP request.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p117291111134216"><a name="p117291111134216"></a><a name="p117291111134216"></a>N/A</p>
</td>
</tr>
<tr id="row4940853114219"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p13940185310423"><a name="p13940185310423"></a><a name="p13940185310423"></a>-gd &lt;index&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1194095374213"><a name="p1194095374213"></a><a name="p1194095374213"></a>Obtains information about the DNS server at the specified index.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p694025334210"><a name="p694025334210"></a><a name="p694025334210"></a>Index, <strong id="b85246422320"><a name="b85246422320"></a><a name="b85246422320"></a>0</strong> or <strong id="b178720401738"><a name="b178720401738"></a><a name="b178720401738"></a>1</strong></p>
</td>
</tr>
<tr id="row196815382432"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p14681238154317"><a name="p14681238154317"></a><a name="p14681238154317"></a>-sd &lt;dns_ip&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4681038144316"><a name="p4681038144316"></a><a name="p4681038144316"></a>Indicates the IP address of the active DNS server.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p4681173884313"><a name="p4681173884313"></a><a name="p4681173884313"></a>IP address of the DNS server</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section15935131220717"></a>

dhclient eth0

dhclient -x eth0

dhclient -gb eth0

dhclient -sv MFSI

dhclient -gv

dhclient -gd 0

dhclient -sd 8.8.8.8

## Example<a name="section79281818476"></a>

![](figures/en-us_image_0000001053224218.png)

## Output<a name="section12742311179"></a>

**Table  2**  Output description

<a name="table487mcpsimp"></a>
<table><thead align="left"><tr id="row492mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p494mcpsimp"><a name="p494mcpsimp"></a><a name="p494mcpsimp"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p496mcpsimp"><a name="p496mcpsimp"></a><a name="p496mcpsimp"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row502mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p583513382179"><a name="p583513382179"></a><a name="p583513382179"></a>dhclient: set vendor info [MFSI] success</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19833143819174"><a name="p19833143819174"></a><a name="p19833143819174"></a>Indicates that the MFSI information is successfully set.</p>
</td>
</tr>
<tr id="row1990234224612"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p3902144294612"><a name="p3902144294612"></a><a name="p3902144294612"></a>dns[0]: 192.168.1.100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p13903144284610"><a name="p13903144284610"></a><a name="p13903144284610"></a>Indicates that the IP address of the DNS server is 192.168.1.100.</p>
</td>
</tr>
</tbody>
</table>

