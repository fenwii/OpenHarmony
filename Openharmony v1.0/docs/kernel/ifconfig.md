# ifconfig<a name="ZH-CN_TOPIC_0000001052170309"></a>

## 命令功能<a name="section174940284379"></a>

ifconfig命令用来查询和设置网卡的IP地址、网络掩码、网关、硬件mac地址等参数。并能够启用/关闭网卡。

## 命令格式<a name="section136073203715"></a>

ifconfig

\[_-a_\]

<_interface_\> <_address_\> \[_netmask <mask\>_\] \[_gateway <address\>_\]

\[_hw ether <address\>_\] \[_mtu <size\>_\]

\[_inet6 add <address\>_\]

\[_inet6 del <address\>_\]

\[_up|down_\]

## 参数说明<a name="section6493235203710"></a>

**表 1**  参数说明

<a name="table2005mcpsimp"></a>
<table><thead align="left"><tr id="row2011mcpsimp"><th class="cellrowborder" valign="top" width="17.93%" id="mcps1.2.4.1.1"><p id="p2013mcpsimp"><a name="p2013mcpsimp"></a><a name="p2013mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="53.669999999999995%" id="mcps1.2.4.1.2"><p id="p2015mcpsimp"><a name="p2015mcpsimp"></a><a name="p2015mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="28.4%" id="mcps1.2.4.1.3"><p id="p2017mcpsimp"><a name="p2017mcpsimp"></a><a name="p2017mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row2018mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2020mcpsimp"><a name="p2020mcpsimp"></a><a name="p2020mcpsimp"></a>不带参数</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2022mcpsimp"><a name="p2022mcpsimp"></a><a name="p2022mcpsimp"></a>打印所有网卡的IP地址、网络掩码、网</p>
<p id="p2023mcpsimp"><a name="p2023mcpsimp"></a><a name="p2023mcpsimp"></a>关、硬件mac地址、MTU、运行状态等信息。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2025mcpsimp"><a name="p2025mcpsimp"></a><a name="p2025mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2026mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2028mcpsimp"><a name="p2028mcpsimp"></a><a name="p2028mcpsimp"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2030mcpsimp"><a name="p2030mcpsimp"></a><a name="p2030mcpsimp"></a>打印协议栈收发数据信息。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2032mcpsimp"><a name="p2032mcpsimp"></a><a name="p2032mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2033mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2035mcpsimp"><a name="p2035mcpsimp"></a><a name="p2035mcpsimp"></a>interface</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2037mcpsimp"><a name="p2037mcpsimp"></a><a name="p2037mcpsimp"></a>指定网卡名，比如eth0。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2039mcpsimp"><a name="p2039mcpsimp"></a><a name="p2039mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2040mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2042mcpsimp"><a name="p2042mcpsimp"></a><a name="p2042mcpsimp"></a>address</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2044mcpsimp"><a name="p2044mcpsimp"></a><a name="p2044mcpsimp"></a>设置IP地址，比如192.168.1.10，需指定网卡名。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2046mcpsimp"><a name="p2046mcpsimp"></a><a name="p2046mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2047mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2049mcpsimp"><a name="p2049mcpsimp"></a><a name="p2049mcpsimp"></a>netmask</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2051mcpsimp"><a name="p2051mcpsimp"></a><a name="p2051mcpsimp"></a>设置子网掩码，后面要掩码参数，比如</p>
<p id="p2052mcpsimp"><a name="p2052mcpsimp"></a><a name="p2052mcpsimp"></a>255.255.255.0。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2054mcpsimp"><a name="p2054mcpsimp"></a><a name="p2054mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2055mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2057mcpsimp"><a name="p2057mcpsimp"></a><a name="p2057mcpsimp"></a>gateway</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2059mcpsimp"><a name="p2059mcpsimp"></a><a name="p2059mcpsimp"></a>设置网关，后面跟网关参数，比如</p>
<p id="p2060mcpsimp"><a name="p2060mcpsimp"></a><a name="p2060mcpsimp"></a>192.168.1.1。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2062mcpsimp"><a name="p2062mcpsimp"></a><a name="p2062mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2063mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2065mcpsimp"><a name="p2065mcpsimp"></a><a name="p2065mcpsimp"></a>hw ether</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2067mcpsimp"><a name="p2067mcpsimp"></a><a name="p2067mcpsimp"></a>设置mac地址， 后面是MAC地址，比如</p>
<p id="p2068mcpsimp"><a name="p2068mcpsimp"></a><a name="p2068mcpsimp"></a>00:11:22:33:44:55。目前只支持ether硬件类</p>
<p id="p2069mcpsimp"><a name="p2069mcpsimp"></a><a name="p2069mcpsimp"></a>型。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2071mcpsimp"><a name="p2071mcpsimp"></a><a name="p2071mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2072mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2074mcpsimp"><a name="p2074mcpsimp"></a><a name="p2074mcpsimp"></a>mtu</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2076mcpsimp"><a name="p2076mcpsimp"></a><a name="p2076mcpsimp"></a>设置mtu大小，后面是mtu大小，比如1000。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><a name="ul10290630142713"></a><a name="ul10290630142713"></a><ul id="ul10290630142713"><li>仅支持ipv4情况下的范围为<p id="p7324133522720"><a name="p7324133522720"></a><a name="p7324133522720"></a>[68,1500]。</p>
</li><li>支持ipv6情况下的范围为<p id="p15794114813278"><a name="p15794114813278"></a><a name="p15794114813278"></a>[1280,1500]。</p>
</li></ul>
</td>
</tr>
<tr id="row2079mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2081mcpsimp"><a name="p2081mcpsimp"></a><a name="p2081mcpsimp"></a>add</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2083mcpsimp"><a name="p2083mcpsimp"></a><a name="p2083mcpsimp"></a>设置ipv6的地址，比如2001:a:b:c:d:e:f:d，需指定网卡名和inet6。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2085mcpsimp"><a name="p2085mcpsimp"></a><a name="p2085mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2086mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2088mcpsimp"><a name="p2088mcpsimp"></a><a name="p2088mcpsimp"></a>del</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2090mcpsimp"><a name="p2090mcpsimp"></a><a name="p2090mcpsimp"></a>删除ipv6的地址，需指定网卡名和inet6。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2092mcpsimp"><a name="p2092mcpsimp"></a><a name="p2092mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2100mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2102mcpsimp"><a name="p2102mcpsimp"></a><a name="p2102mcpsimp"></a>up</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2104mcpsimp"><a name="p2104mcpsimp"></a><a name="p2104mcpsimp"></a>启用网卡数据处理，需指定网卡名。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2106mcpsimp"><a name="p2106mcpsimp"></a><a name="p2106mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2107mcpsimp"><td class="cellrowborder" valign="top" width="17.93%" headers="mcps1.2.4.1.1 "><p id="p2109mcpsimp"><a name="p2109mcpsimp"></a><a name="p2109mcpsimp"></a>down</p>
</td>
<td class="cellrowborder" valign="top" width="53.669999999999995%" headers="mcps1.2.4.1.2 "><p id="p2111mcpsimp"><a name="p2111mcpsimp"></a><a name="p2111mcpsimp"></a>关闭网卡数据处理，需指定网卡名。</p>
</td>
<td class="cellrowborder" valign="top" width="28.4%" headers="mcps1.2.4.1.3 "><p id="p2113mcpsimp"><a name="p2113mcpsimp"></a><a name="p2113mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section05763403371"></a>

-   命令需要启动TCP/IP协议栈后才能使用。
-   由于IP冲突检测需要反应时间，每次使用ifconfig设置IP后会有2S左右的延时。

## 使用实例<a name="section168802042123717"></a>

1.  ifconfig eth0 192.168.100.31 netmask 255.255.255.0 gateway 192.168.100.1 hw ether 00:49:cb:6c:a1:31
2.  ifconfig -a
3.  ifconfig eth0 inet6 add 2001:a:b:c:d:e:f:d
4.  ifconfig eth0 inet6 del 2001:a:b:c:d:e:f:d

## 输出说明<a name="section124638211109"></a>

1.  设置网络参数

    ```
    OHOS # ifconfig eth0 192.168.100.31 netmask 255.255.255.0 gateway 192.168.100.1 hw ether 00:49:cb:6c:a1:31
    OHOS # ifconfig
    eth0     ip:192.168.100.31 netmask:255.255.255.0 gateway:192.168.100.1
    HWaddr 00:49:cb:6c:a1:31 MTU:1500 Running Default Link UP
    lo         ip:127.0.0.1 netmask:255.0.0.0 gateway:127.0.0.1
    ip6: ::1/64
    HWaddr 00 MTU:0 Running Link UP
    ```

    输出的各参数说明如下表所示：

    **表 2**  参数说明

    <a name="table2147mcpsimp"></a>
    <table><thead align="left"><tr id="row2152mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p2154mcpsimp"><a name="p2154mcpsimp"></a><a name="p2154mcpsimp"></a>参数</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p2156mcpsimp"><a name="p2156mcpsimp"></a><a name="p2156mcpsimp"></a>说明</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row2157mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2159mcpsimp"><a name="p2159mcpsimp"></a><a name="p2159mcpsimp"></a>ip</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2161mcpsimp"><a name="p2161mcpsimp"></a><a name="p2161mcpsimp"></a>板子IP地址。</p>
    </td>
    </tr>
    <tr id="row2162mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2164mcpsimp"><a name="p2164mcpsimp"></a><a name="p2164mcpsimp"></a>netmask</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2166mcpsimp"><a name="p2166mcpsimp"></a><a name="p2166mcpsimp"></a>网络掩码。</p>
    </td>
    </tr>
    <tr id="row2167mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2169mcpsimp"><a name="p2169mcpsimp"></a><a name="p2169mcpsimp"></a>gateway</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2171mcpsimp"><a name="p2171mcpsimp"></a><a name="p2171mcpsimp"></a>网关。</p>
    </td>
    </tr>
    <tr id="row2177mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2179mcpsimp"><a name="p2179mcpsimp"></a><a name="p2179mcpsimp"></a>HWaddr</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2181mcpsimp"><a name="p2181mcpsimp"></a><a name="p2181mcpsimp"></a>板子硬件mac地址。</p>
    </td>
    </tr>
    <tr id="row2182mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2184mcpsimp"><a name="p2184mcpsimp"></a><a name="p2184mcpsimp"></a>MTU</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2186mcpsimp"><a name="p2186mcpsimp"></a><a name="p2186mcpsimp"></a>网络最大传输单元。</p>
    </td>
    </tr>
    <tr id="row2187mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2189mcpsimp"><a name="p2189mcpsimp"></a><a name="p2189mcpsimp"></a>Running/Stop</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2191mcpsimp"><a name="p2191mcpsimp"></a><a name="p2191mcpsimp"></a>网卡是否正在运行。</p>
    </td>
    </tr>
    <tr id="row2192mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2194mcpsimp"><a name="p2194mcpsimp"></a><a name="p2194mcpsimp"></a>Default</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2196mcpsimp"><a name="p2196mcpsimp"></a><a name="p2196mcpsimp"></a>有这项说明此网卡连接到默认网关。</p>
    </td>
    </tr>
    <tr id="row2197mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2199mcpsimp"><a name="p2199mcpsimp"></a><a name="p2199mcpsimp"></a>Link UP/Down</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2201mcpsimp"><a name="p2201mcpsimp"></a><a name="p2201mcpsimp"></a>网卡连接状态。</p>
    </td>
    </tr>
    </tbody>
    </table>

2.  获取协议栈统计信息

    ```
    OHOS # ifconfig -a
    RX packets:6922  errors:0        ip dropped:4312         link dropped:67         overrun:0       bytes:0 (0.0 B)
    RX packets(ip6):3     errors:0        dropped:0       overrun:0       bytes:0 (0.0 B)
    TX packets:1394  errors:0        link dropped:67         overrun:0       bytes:0(0.0 B)
    TX packets(ip6):3     errors:0        overrun:0       bytes:0(0.0 B)
    ```

    输出的各参数说明如下表所示：

    **表 3**  ifconfig -a 参数说明

    <a name="table2209mcpsimp"></a>
    <table><thead align="left"><tr id="row2214mcpsimp"><th class="cellrowborder" valign="top" width="28.999999999999996%" id="mcps1.2.3.1.1"><p id="p2216mcpsimp"><a name="p2216mcpsimp"></a><a name="p2216mcpsimp"></a>参数</p>
    </th>
    <th class="cellrowborder" valign="top" width="71%" id="mcps1.2.3.1.2"><p id="p2218mcpsimp"><a name="p2218mcpsimp"></a><a name="p2218mcpsimp"></a>说明</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row2219mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2221mcpsimp"><a name="p2221mcpsimp"></a><a name="p2221mcpsimp"></a>RX packets</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2223mcpsimp"><a name="p2223mcpsimp"></a><a name="p2223mcpsimp"></a>IP层已接收的正常数据包的个数。</p>
    </td>
    </tr>
    <tr id="row2224mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2226mcpsimp"><a name="p2226mcpsimp"></a><a name="p2226mcpsimp"></a>RX error</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2228mcpsimp"><a name="p2228mcpsimp"></a><a name="p2228mcpsimp"></a>IP层已接收的错误数据包的个数，错误类型包括长度错误，校验错误，IP option错误，IP首部protocol错误等。</p>
    </td>
    </tr>
    <tr id="row2229mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2231mcpsimp"><a name="p2231mcpsimp"></a><a name="p2231mcpsimp"></a>RX dropped</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2233mcpsimp"><a name="p2233mcpsimp"></a><a name="p2233mcpsimp"></a>IP层已丢弃的数据包的个数，丢弃原因包括数据包错误，封包无法转发，本地网卡处于关闭状态等。</p>
    </td>
    </tr>
    <tr id="row2234mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2236mcpsimp"><a name="p2236mcpsimp"></a><a name="p2236mcpsimp"></a>RX overrun</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2238mcpsimp"><a name="p2238mcpsimp"></a><a name="p2238mcpsimp"></a>MAC层向上层协议栈投递封包失败的个数，失败原因主要是协议栈资源不足。</p>
    </td>
    </tr>
    <tr id="row2239mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2241mcpsimp"><a name="p2241mcpsimp"></a><a name="p2241mcpsimp"></a>RX bytes</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2243mcpsimp"><a name="p2243mcpsimp"></a><a name="p2243mcpsimp"></a>IP层已接收的正常数据包的总长度，不包括重组未完成的分片的长度。</p>
    </td>
    </tr>
    <tr id="row2244mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2246mcpsimp"><a name="p2246mcpsimp"></a><a name="p2246mcpsimp"></a>TX packets</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2248mcpsimp"><a name="p2248mcpsimp"></a><a name="p2248mcpsimp"></a>IP层已正常发送或转发的数据包的个数。</p>
    </td>
    </tr>
    <tr id="row2249mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2251mcpsimp"><a name="p2251mcpsimp"></a><a name="p2251mcpsimp"></a>TX error</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2253mcpsimp"><a name="p2253mcpsimp"></a><a name="p2253mcpsimp"></a>IP层发送失败的数据包的个数，失败原因包括封包无法路由，封包在协议栈内处理失败等。</p>
    </td>
    </tr>
    <tr id="row2254mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2256mcpsimp"><a name="p2256mcpsimp"></a><a name="p2256mcpsimp"></a>TX dropped</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2258mcpsimp"><a name="p2258mcpsimp"></a><a name="p2258mcpsimp"></a>MAC层由于发送失败而丢弃的数据包个数，失败原因包括网卡驱动处理封包失败等。</p>
    </td>
    </tr>
    <tr id="row2259mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2261mcpsimp"><a name="p2261mcpsimp"></a><a name="p2261mcpsimp"></a>TX overrun</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2263mcpsimp"><a name="p2263mcpsimp"></a><a name="p2263mcpsimp"></a>暂未使用。</p>
    </td>
    </tr>
    <tr id="row2264mcpsimp"><td class="cellrowborder" valign="top" width="28.999999999999996%" headers="mcps1.2.3.1.1 "><p id="p2266mcpsimp"><a name="p2266mcpsimp"></a><a name="p2266mcpsimp"></a>TX bytes</p>
    </td>
    <td class="cellrowborder" valign="top" width="71%" headers="mcps1.2.3.1.2 "><p id="p2268mcpsimp"><a name="p2268mcpsimp"></a><a name="p2268mcpsimp"></a>IP层已正常发送或者转发的数据包的总长度。</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  设置IPv6的地址信息

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

4.  删除IPv6的地址信息

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


