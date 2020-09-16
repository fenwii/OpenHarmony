# arp<a name="ZH-CN_TOPIC_0000001052530290"></a>

## 命令功能<a name="section201149459368"></a>

在以太网中，主机之间的通信是直接使用MAC地址（非IP地址）来通信的，所以，对于使用IP通信的协议，必须能够将IP地址转换成MAC地址，才能在局域网（以太网）内通信。解决这个问题的方法就是主机存储一张IP和MAC地址对应的表，即ARP缓存，主机要往一个局域网内的目的IP地址发送IP包时，就可以从ARP缓存表中查询到目的MAC地址。ARP缓存是由TCP/IP协议栈维护的，用户可通过ARP命令查看和修改ARP表。

## 命令格式<a name="section579813484364"></a>

arp

arp \[_-i IF_\] -s  _IPADDR HWADDR_

arp \[_-i IF_\] -d  _IPADDR_

## 参数说明<a name="section168065311366"></a>

**表 1**  参数说明

<a name="table1845mcpsimp"></a>
<table><thead align="left"><tr id="row1851mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1853mcpsimp"><a name="p1853mcpsimp"></a><a name="p1853mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1855mcpsimp"><a name="p1855mcpsimp"></a><a name="p1855mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1857mcpsimp"><a name="p1857mcpsimp"></a><a name="p1857mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1858mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1860mcpsimp"><a name="p1860mcpsimp"></a><a name="p1860mcpsimp"></a>无</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1862mcpsimp"><a name="p1862mcpsimp"></a><a name="p1862mcpsimp"></a>打印整个ARP缓存的内容。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1864mcpsimp"><a name="p1864mcpsimp"></a><a name="p1864mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1865mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1867mcpsimp"><a name="p1867mcpsimp"></a><a name="p1867mcpsimp"></a>-i IF</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1869mcpsimp"><a name="p1869mcpsimp"></a><a name="p1869mcpsimp"></a>指定的网络接口（可选参数）。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1871mcpsimp"><a name="p1871mcpsimp"></a><a name="p1871mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1872mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1874mcpsimp"><a name="p1874mcpsimp"></a><a name="p1874mcpsimp"></a>-s IPADDR</p>
<p id="p1875mcpsimp"><a name="p1875mcpsimp"></a><a name="p1875mcpsimp"></a>HWADDR</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1877mcpsimp"><a name="p1877mcpsimp"></a><a name="p1877mcpsimp"></a>增加一条ARP表项，后面的参数是局域网中另一台主机的IP地址及其对应的MAC地址。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1879mcpsimp"><a name="p1879mcpsimp"></a><a name="p1879mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1880mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1882mcpsimp"><a name="p1882mcpsimp"></a><a name="p1882mcpsimp"></a>-d IPADDR</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1884mcpsimp"><a name="p1884mcpsimp"></a><a name="p1884mcpsimp"></a>删除一条ARP表项。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1886mcpsimp"><a name="p1886mcpsimp"></a><a name="p1886mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section19190125723612"></a>

-   arp命令用来查询和修改TCP/IP协议栈的ARP缓存表，增加非同一子网内的IP地址的ARP表项是没有意义的，协议栈会返回失败。
-   命令需要启动TCP/IP协议栈后才能使用。

## 使用实例<a name="section10383416372"></a>

举例：

1.  输入arp

    **图 1**  打印整个 ARP 缓存表<a name="fig19980104045317"></a>  
    ![](figures/打印整个-ARP-缓存表.png "打印整个-ARP-缓存表")

    **表 2**  参数说明

    <a name="table1901mcpsimp"></a>
    <table><thead align="left"><tr id="row1906mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1908mcpsimp"><a name="p1908mcpsimp"></a><a name="p1908mcpsimp"></a>参数</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p1910mcpsimp"><a name="p1910mcpsimp"></a><a name="p1910mcpsimp"></a>说明</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row1911mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1913mcpsimp"><a name="p1913mcpsimp"></a><a name="p1913mcpsimp"></a>Address</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1915mcpsimp"><a name="p1915mcpsimp"></a><a name="p1915mcpsimp"></a>表示网络设备的IPv4地址。</p>
    </td>
    </tr>
    <tr id="row1916mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1918mcpsimp"><a name="p1918mcpsimp"></a><a name="p1918mcpsimp"></a>HWaddress</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1920mcpsimp"><a name="p1920mcpsimp"></a><a name="p1920mcpsimp"></a>表示网络设备的MAC地址。</p>
    </td>
    </tr>
    <tr id="row1921mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1923mcpsimp"><a name="p1923mcpsimp"></a><a name="p1923mcpsimp"></a>Iface</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1925mcpsimp"><a name="p1925mcpsimp"></a><a name="p1925mcpsimp"></a>表示该ARP表项使用的接口名。</p>
    </td>
    </tr>
    <tr id="row1926mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1928mcpsimp"><a name="p1928mcpsimp"></a><a name="p1928mcpsimp"></a>Type</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1930mcpsimp"><a name="p1930mcpsimp"></a><a name="p1930mcpsimp"></a>表示该ARP表项是动态的还是静态的，动态是指ARP表项由协议栈自动创建，静态是指ARP表项是由用户增加的。</p>
    </td>
    </tr>
    </tbody>
    </table>


