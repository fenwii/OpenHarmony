# ifconfig<a name="EN-US_TOPIC_0000001052170309"></a>

## Command Function<a name="section174940284379"></a>

This command is used to query and set parameters of a NIC, such as the IP address, subnet mask, gateway, and MAC address, and enable or disable the NIC.

## Syntax<a name="section136073203715"></a>

ifconfig

\[_-a_\]

<_interface_\> <_address_\> \[_netmask <mask\>_\] \[_gateway <address\>_\]

\[_hw ether <address\>_\] \[_mtu <size\>_\]

\[_inet6 add <address\>_\]

\[_inet6 del <address\>_\]

\[_up|down_\]

## Parameter Description<a name="section6493235203710"></a>

**Table  1**  Parameters

<a name="table2005mcpsimp"></a>
<table><thead align="left"><tr id="row2011mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p2013mcpsimp"><a name="p2013mcpsimp"></a><a name="p2013mcpsimp"></a><strong id="b207545880811653"><a name="b207545880811653"></a><a name="b207545880811653"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p2015mcpsimp"><a name="p2015mcpsimp"></a><a name="p2015mcpsimp"></a><strong id="b519711279124"><a name="b519711279124"></a><a name="b519711279124"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p2017mcpsimp"><a name="p2017mcpsimp"></a><a name="p2017mcpsimp"></a><strong id="b19371475311653"><a name="b19371475311653"></a><a name="b19371475311653"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row2018mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2020mcpsimp"><a name="p2020mcpsimp"></a><a name="p2020mcpsimp"></a>No parameter</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2022mcpsimp"><a name="p2022mcpsimp"></a><a name="p2022mcpsimp"></a>Displays information about all NICs, including the IP addresses, subnet masks, gateways, MAC addresses, 	maximum transmission units (MTUs), and running statuses.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2025mcpsimp"><a name="p2025mcpsimp"></a><a name="p2025mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2026mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2028mcpsimp"><a name="p2028mcpsimp"></a><a name="p2028mcpsimp"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2030mcpsimp"><a name="p2030mcpsimp"></a><a name="p2030mcpsimp"></a>Displays data sent and received by the protocol stack.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2032mcpsimp"><a name="p2032mcpsimp"></a><a name="p2032mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2033mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2035mcpsimp"><a name="p2035mcpsimp"></a><a name="p2035mcpsimp"></a>interface</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2037mcpsimp"><a name="p2037mcpsimp"></a><a name="p2037mcpsimp"></a>Indicates the NIC name, for example, <strong id="b1368975571410"><a name="b1368975571410"></a><a name="b1368975571410"></a>eth0</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2039mcpsimp"><a name="p2039mcpsimp"></a><a name="p2039mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2040mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2042mcpsimp"><a name="p2042mcpsimp"></a><a name="p2042mcpsimp"></a>address</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2044mcpsimp"><a name="p2044mcpsimp"></a><a name="p2044mcpsimp"></a>Indicates the IP address, for example, <strong id="b530715731519"><a name="b530715731519"></a><a name="b530715731519"></a>192.168.1.10</strong>. The NIC name must be specified.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2046mcpsimp"><a name="p2046mcpsimp"></a><a name="p2046mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2047mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2049mcpsimp"><a name="p2049mcpsimp"></a><a name="p2049mcpsimp"></a>netmask</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2051mcpsimp"><a name="p2051mcpsimp"></a><a name="p2051mcpsimp"></a>Indicates the subnet mask, for example, <strong id="b235246162419"><a name="b235246162419"></a><a name="b235246162419"></a>255.255.255.0</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2054mcpsimp"><a name="p2054mcpsimp"></a><a name="p2054mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2055mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2057mcpsimp"><a name="p2057mcpsimp"></a><a name="p2057mcpsimp"></a>gateway</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2059mcpsimp"><a name="p2059mcpsimp"></a><a name="p2059mcpsimp"></a>Indicates the gateway, for example, <strong id="b7597165610246"><a name="b7597165610246"></a><a name="b7597165610246"></a>192.168.1.1</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2062mcpsimp"><a name="p2062mcpsimp"></a><a name="p2062mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2063mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2065mcpsimp"><a name="p2065mcpsimp"></a><a name="p2065mcpsimp"></a>hw ether</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2067mcpsimp"><a name="p2067mcpsimp"></a><a name="p2067mcpsimp"></a>Indicates the MAC address, for example, <strong id="b679715131255"><a name="b679715131255"></a><a name="b679715131255"></a>00:11:22:33:44:55</strong>. Currently, only the <strong id="b175610517419"><a name="b175610517419"></a><a name="b175610517419"></a>ether</strong> hardware type is supported.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2071mcpsimp"><a name="p2071mcpsimp"></a><a name="p2071mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2072mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2074mcpsimp"><a name="p2074mcpsimp"></a><a name="p2074mcpsimp"></a>mtu</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2076mcpsimp"><a name="p2076mcpsimp"></a><a name="p2076mcpsimp"></a>Indicates the MTU size, for example, <strong id="b2852192012261"><a name="b2852192012261"></a><a name="b2852192012261"></a>1000</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><a name="ul10290630142713"></a><a name="ul10290630142713"></a><ul id="ul10290630142713"><li>For IPv4:<p id="p7324133522720"><a name="p7324133522720"></a><a name="p7324133522720"></a>[68,1500]</p>
</li><li>For IPv6:<p id="p15794114813278"><a name="p15794114813278"></a><a name="p15794114813278"></a>[1280, 1500]</p>
</li></ul>
</td>
</tr>
<tr id="row2079mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2081mcpsimp"><a name="p2081mcpsimp"></a><a name="p2081mcpsimp"></a>add</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2083mcpsimp"><a name="p2083mcpsimp"></a><a name="p2083mcpsimp"></a>Indicates the IPv6 address, for example, <strong id="b12509153516279"><a name="b12509153516279"></a><a name="b12509153516279"></a>2001:a:b:c:d:e:f:d</strong>. The NIC name and <strong id="b912123842916"><a name="b912123842916"></a><a name="b912123842916"></a>inet6</strong> must be specified.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2085mcpsimp"><a name="p2085mcpsimp"></a><a name="p2085mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2086mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2088mcpsimp"><a name="p2088mcpsimp"></a><a name="p2088mcpsimp"></a>del</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2090mcpsimp"><a name="p2090mcpsimp"></a><a name="p2090mcpsimp"></a>Deletes an IPv6 address. The NIC name and <strong id="b81833812319"><a name="b81833812319"></a><a name="b81833812319"></a>inet6</strong> must be specified.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2092mcpsimp"><a name="p2092mcpsimp"></a><a name="p2092mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2100mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2102mcpsimp"><a name="p2102mcpsimp"></a><a name="p2102mcpsimp"></a>up</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2104mcpsimp"><a name="p2104mcpsimp"></a><a name="p2104mcpsimp"></a>Enables the data processing function of the NIC. The NIC name must be specified.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2106mcpsimp"><a name="p2106mcpsimp"></a><a name="p2106mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2107mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2109mcpsimp"><a name="p2109mcpsimp"></a><a name="p2109mcpsimp"></a>down</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2111mcpsimp"><a name="p2111mcpsimp"></a><a name="p2111mcpsimp"></a>Disables the data processing function of the NIC. The NIC name must be specified.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2113mcpsimp"><a name="p2113mcpsimp"></a><a name="p2113mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section05763403371"></a>

-   This command can be used only after the TCP/IP protocol stack is enabled.
-   Detecting the IP address conflict takes a period of time. Each time you run the  **ifconfig**  command to set an IP address, there is a delay of about 2 seconds.

## Example<a name="section168802042123717"></a>

1.  ifconfig eth0 192.168.100.31 netmask 255.255.255.0 gateway 192.168.100.1 hw ether 00:49:cb:6c:a1:31
2.  ifconfig -a
3.  ifconfig eth0 inet6 add 2001:a:b:c:d:e:f:d
4.  ifconfig eth0 inet6 del 2001:a:b:c:d:e:f:d

## Output<a name="section124638211109"></a>

1.  Setting network parameters:

    ```
    OHOS # ifconfig eth0 192.168.100.31 netmask 255.255.255.0 gateway 192.168.100.1 hw ether 00:49:cb:6c:a1:31
    OHOS # ifconfig
    eth0     ip:192.168.100.31 netmask:255.255.255.0 gateway:192.168.100.1
    HWaddr 00:49:cb:6c:a1:31 MTU:1500 Running Default Link UP
    lo         ip:127.0.0.1 netmask:255.0.0.0 gateway:127.0.0.1
    ip6: ::1/64
    HWaddr 00 MTU:0 Running Link UP
    ```

    The following table describes the output parameters.

    **Table  2**  Output description

    <a name="table2147mcpsimp"></a>
    <table><thead align="left"><tr id="row2152mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p2154mcpsimp"><a name="p2154mcpsimp"></a><a name="p2154mcpsimp"></a><strong id="b211311219311653"><a name="b211311219311653"></a><a name="b211311219311653"></a>Parameter</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p2156mcpsimp"><a name="p2156mcpsimp"></a><a name="p2156mcpsimp"></a><strong id="b336412763515"><a name="b336412763515"></a><a name="b336412763515"></a>Description</strong></p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row2157mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2159mcpsimp"><a name="p2159mcpsimp"></a><a name="p2159mcpsimp"></a>ip</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2161mcpsimp"><a name="p2161mcpsimp"></a><a name="p2161mcpsimp"></a>Indicates the IP address of the board.</p>
    </td>
    </tr>
    <tr id="row2162mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2164mcpsimp"><a name="p2164mcpsimp"></a><a name="p2164mcpsimp"></a>netmask</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2166mcpsimp"><a name="p2166mcpsimp"></a><a name="p2166mcpsimp"></a>Indicates the subnet mask.</p>
    </td>
    </tr>
    <tr id="row2167mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2169mcpsimp"><a name="p2169mcpsimp"></a><a name="p2169mcpsimp"></a>gateway</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2171mcpsimp"><a name="p2171mcpsimp"></a><a name="p2171mcpsimp"></a>Indicates the gateway.</p>
    </td>
    </tr>
    <tr id="row2177mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2179mcpsimp"><a name="p2179mcpsimp"></a><a name="p2179mcpsimp"></a>HWaddr</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2181mcpsimp"><a name="p2181mcpsimp"></a><a name="p2181mcpsimp"></a>Indicates the MAC address of the board.</p>
    </td>
    </tr>
    <tr id="row2182mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2184mcpsimp"><a name="p2184mcpsimp"></a><a name="p2184mcpsimp"></a>MTU</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2186mcpsimp"><a name="p2186mcpsimp"></a><a name="p2186mcpsimp"></a>Indicates the MTU.</p>
    </td>
    </tr>
    <tr id="row2187mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2189mcpsimp"><a name="p2189mcpsimp"></a><a name="p2189mcpsimp"></a>Running/Stop</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2191mcpsimp"><a name="p2191mcpsimp"></a><a name="p2191mcpsimp"></a>Indicates whether the NIC is running.</p>
    </td>
    </tr>
    <tr id="row2192mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2194mcpsimp"><a name="p2194mcpsimp"></a><a name="p2194mcpsimp"></a>Default</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2196mcpsimp"><a name="p2196mcpsimp"></a><a name="p2196mcpsimp"></a>Indicates that the NIC is connected to the default gateway.</p>
    </td>
    </tr>
    <tr id="row2197mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2199mcpsimp"><a name="p2199mcpsimp"></a><a name="p2199mcpsimp"></a>Link UP/Down</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2201mcpsimp"><a name="p2201mcpsimp"></a><a name="p2201mcpsimp"></a>Indicates the connection status of the NIC.</p>
    </td>
    </tr>
    </tbody>
    </table>

2.  Obtaining protocol stack statistics:

    ```
    OHOS # ifconfig -a
    RX packets:6922  errors:0        ip dropped:4312         link dropped:67         overrun:0       bytes:0 (0.0 B)
    RX packets(ip6):3     errors:0        dropped:0       overrun:0       bytes:0 (0.0 B)
    TX packets:1394  errors:0        link dropped:67         overrun:0       bytes:0(0.0 B)
    TX packets(ip6):3     errors:0        overrun:0       bytes:0(0.0 B)
    ```

    The following table describes the output parameters.

    **Table  3**  ifconfig -a output description

    <a name="table2209mcpsimp"></a>
    <table><thead align="left"><tr id="row2214mcpsimp"><th class="cellrowborder" valign="top" width="28.999999999999996%" id="mcps1.2.3.1.1"><p id="p2216mcpsimp"><a name="p2216mcpsimp"></a><a name="p2216mcpsimp"></a><strong id="b120972048811653"><a name="b120972048811653"></a><a name="b120972048811653"></a>Parameter</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="71%" id="mcps1.2.3.1.2"><p id="p2218mcpsimp"><a name="p2218mcpsimp"></a><a name="p2218mcpsimp"></a><strong id="b8227191303719"><a name="b8227191303719"></a><a name="b8227191303719"></a>Description</strong></p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row2219mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2221mcpsimp"><a name="p2221mcpsimp"></a><a name="p2221mcpsimp"></a>RX packets</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2223mcpsimp"><a name="p2223mcpsimp"></a><a name="p2223mcpsimp"></a>Indicates the number of normal packets that have been received at the IP layer.</p>
    </td>
    </tr>
    <tr id="row2224mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2226mcpsimp"><a name="p2226mcpsimp"></a><a name="p2226mcpsimp"></a>RX error</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2228mcpsimp"><a name="p2228mcpsimp"></a><a name="p2228mcpsimp"></a>Indicates the number of error packets that have been received at the IP layer. The errors include the length, verification, IP option, and IP header protocol errors.</p>
    </td>
    </tr>
    <tr id="row2229mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2231mcpsimp"><a name="p2231mcpsimp"></a><a name="p2231mcpsimp"></a>RX dropped</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2233mcpsimp"><a name="p2233mcpsimp"></a><a name="p2233mcpsimp"></a>Indicates the number of packets that have been discarded at the IP layer. Packets may be discarded due to packet errors, packet forwarding failures, and disabled local NICs.</p>
    </td>
    </tr>
    <tr id="row2234mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2236mcpsimp"><a name="p2236mcpsimp"></a><a name="p2236mcpsimp"></a>RX overrun</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2238mcpsimp"><a name="p2238mcpsimp"></a><a name="p2238mcpsimp"></a>Indicates the number of packets that the MAC layer fails to deliver to the upper-layer protocol stack. The failure is mainly caused by resource insufficiency at the protocol stack.</p>
    </td>
    </tr>
    <tr id="row2239mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2241mcpsimp"><a name="p2241mcpsimp"></a><a name="p2241mcpsimp"></a>RX bytes</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2243mcpsimp"><a name="p2243mcpsimp"></a><a name="p2243mcpsimp"></a>Indicates the total length of normal packets that have been received at the IP layer, excluding the length of the fragments that are not reassembled.</p>
    </td>
    </tr>
    <tr id="row2244mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2246mcpsimp"><a name="p2246mcpsimp"></a><a name="p2246mcpsimp"></a>TX packets</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2248mcpsimp"><a name="p2248mcpsimp"></a><a name="p2248mcpsimp"></a>Indicates the number of packets that have been normally sent or forwarded at the IP layer.</p>
    </td>
    </tr>
    <tr id="row2249mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2251mcpsimp"><a name="p2251mcpsimp"></a><a name="p2251mcpsimp"></a>TX error</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2253mcpsimp"><a name="p2253mcpsimp"></a><a name="p2253mcpsimp"></a>Indicates the number of packets that the IP layer fails to send. Packets may fail to be sent because the packets cannot be routed or the packets fail to be processed in the protocol stack.</p>
    </td>
    </tr>
    <tr id="row2254mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2256mcpsimp"><a name="p2256mcpsimp"></a><a name="p2256mcpsimp"></a>TX dropped</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2258mcpsimp"><a name="p2258mcpsimp"></a><a name="p2258mcpsimp"></a>Indicates the number of packets that the MAC layer discards due to sending failures, for example, the NIC driver fails to process the packets.</p>
    </td>
    </tr>
    <tr id="row2259mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2261mcpsimp"><a name="p2261mcpsimp"></a><a name="p2261mcpsimp"></a>TX overrun</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2263mcpsimp"><a name="p2263mcpsimp"></a><a name="p2263mcpsimp"></a>Reserved.</p>
    </td>
    </tr>
    <tr id="row2264mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2266mcpsimp"><a name="p2266mcpsimp"></a><a name="p2266mcpsimp"></a>TX bytes</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2268mcpsimp"><a name="p2268mcpsimp"></a><a name="p2268mcpsimp"></a>Indicates the total length of the packets that the IP layer has successfully sent or forwarded.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Setting the IPv6 address information:

    ```
    OHOS # ifconfig eth0 inet6 add 2001:a:b:c:d:e:f:d
    OHOS # ifconfig
    eth1    ip:192.168.3.60 netmask:255.255.255.0 gateway:0.0.0.0
    HWaddr 00:0e:c6:a8:5a:c2 MTU:1500 Running Link UP
    eth0    ip:192.168.2.60 netmask:255.255.255.0 gateway:0.0.0.0
    ip6: 2001:A:B:C:D:E:F:D/64
    HWaddr 46:44:02:02:03:03 MTU:1500 Running Link UP
    lo        ip:127.0.0.1 netmask:255.0.0.0 gateway:127.0.0.1
    ip6: ::1/64
    HWaddr 00 MTU:16436 Running Link UP
    ```

4.  Deleting the IPv6 address information:

    ```
    OHOS # ifconfig eth0 inet6 del 2001:a:b:c:d:e:f:d
    OHOS # ifconfig
    eth1    ip:192.168.3.60 netmask:255.255.255.0 gateway:0.0.0.0
    HWaddr 00:0e:c6:a8:5a:c2 MTU:1500 Running Link UP
    eth0    ip:192.168.2.60 netmask:255.255.255.0 gateway:0.0.0.0
    HWaddr 46:44:02:02:03:03 MTU:1500 Running Link UP
    lo        ip:127.0.0.1 netmask:255.0.0.0 gateway:127.0.0.1
    ip6: ::1/64
    HWaddr 00 MTU:16436 Running Link UP
    ```


