# arp<a name="EN-US_TOPIC_0000001052530290"></a>

## Command Function<a name="section201149459368"></a>

On an Ethernet, hosts communicate with each other using MAC addresses \(non-IP addresses\). Therefore, IP addresses must be converted into MAC addresses so that hosts can communicate with each other on a LAN \(Ethernet\). To resolve this issue, the host stores a table containing the mapping between IP addresses and MAC addresses, that is, the ARP cache table. When the host needs to send an IP packet to the destination IP address on a LAN, the host can query the destination MAC address from the ARP cache table. The ARP cache table is maintained by the TCP/IP protocol stack. You can run the  **arp**  command to view and modify the ARP cache table.

## Syntax<a name="section579813484364"></a>

arp

arp \[_-i IF_\] -s  _IPADDR HWADDR_

arp \[_-i IF_\] -d  _IPADDR_

## Parameter Description<a name="section168065311366"></a>

**Table  1**  Parameters

<a name="table1845mcpsimp"></a>
<table><thead align="left"><tr id="row1851mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1853mcpsimp"><a name="p1853mcpsimp"></a><a name="p1853mcpsimp"></a><strong id="b24438529911613"><a name="b24438529911613"></a><a name="b24438529911613"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1855mcpsimp"><a name="p1855mcpsimp"></a><a name="p1855mcpsimp"></a><strong id="b665518251701"><a name="b665518251701"></a><a name="b665518251701"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1857mcpsimp"><a name="p1857mcpsimp"></a><a name="p1857mcpsimp"></a><strong id="b169031044911613"><a name="b169031044911613"></a><a name="b169031044911613"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1858mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1860mcpsimp"><a name="p1860mcpsimp"></a><a name="p1860mcpsimp"></a>No parameter</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1862mcpsimp"><a name="p1862mcpsimp"></a><a name="p1862mcpsimp"></a>Prints the content of the entire ARP cache table.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1864mcpsimp"><a name="p1864mcpsimp"></a><a name="p1864mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1865mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1867mcpsimp"><a name="p1867mcpsimp"></a><a name="p1867mcpsimp"></a>-i IF</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1869mcpsimp"><a name="p1869mcpsimp"></a><a name="p1869mcpsimp"></a>Indicates the network interface. This parameter is optional.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1871mcpsimp"><a name="p1871mcpsimp"></a><a name="p1871mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1872mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1874mcpsimp"><a name="p1874mcpsimp"></a><a name="p1874mcpsimp"></a>-s IPADDR</p>
<p id="p1875mcpsimp"><a name="p1875mcpsimp"></a><a name="p1875mcpsimp"></a>HWADDR</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1877mcpsimp"><a name="p1877mcpsimp"></a><a name="p1877mcpsimp"></a>Adds an ARP entry. The second parameter is the IP address and MAC address of the other host on the LAN.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1879mcpsimp"><a name="p1879mcpsimp"></a><a name="p1879mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1880mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1882mcpsimp"><a name="p1882mcpsimp"></a><a name="p1882mcpsimp"></a>-d IPADDR</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1884mcpsimp"><a name="p1884mcpsimp"></a><a name="p1884mcpsimp"></a>Deletes an ARP entry.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1886mcpsimp"><a name="p1886mcpsimp"></a><a name="p1886mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section19190125723612"></a>

-   The  **arp**  command is used to query and modify the ARP cache table of the TCP/IP protocol stack. If ARP entries for IP addresses on different subnets are added, the protocol stack returns a failure message.
-   This command can be used only after the TCP/IP protocol stack is enabled.

## Example<a name="section10383416372"></a>

Example:

1.  Enter  **arp**.

    **Figure  1**  Printing the entire ARP cache table<a name="fig19980104045317"></a>  
    ![](figures/printing-the-entire-arp-cache-table.png "printing-the-entire-arp-cache-table")

    **Table  2**  Output description

    <a name="table1901mcpsimp"></a>
    <table><thead align="left"><tr id="row1906mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1908mcpsimp"><a name="p1908mcpsimp"></a><a name="p1908mcpsimp"></a><strong id="b38103410311613"><a name="b38103410311613"></a><a name="b38103410311613"></a>Parameter</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p1910mcpsimp"><a name="p1910mcpsimp"></a><a name="p1910mcpsimp"></a><strong id="b6623104464810"><a name="b6623104464810"></a><a name="b6623104464810"></a>Description</strong></p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row1911mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1913mcpsimp"><a name="p1913mcpsimp"></a><a name="p1913mcpsimp"></a>Address</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1915mcpsimp"><a name="p1915mcpsimp"></a><a name="p1915mcpsimp"></a>Indicates the IPv4 address of a network device.</p>
    </td>
    </tr>
    <tr id="row1916mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1918mcpsimp"><a name="p1918mcpsimp"></a><a name="p1918mcpsimp"></a>HWaddress</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1920mcpsimp"><a name="p1920mcpsimp"></a><a name="p1920mcpsimp"></a>Indicates the MAC address of a network device.</p>
    </td>
    </tr>
    <tr id="row1921mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1923mcpsimp"><a name="p1923mcpsimp"></a><a name="p1923mcpsimp"></a>Iface</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1925mcpsimp"><a name="p1925mcpsimp"></a><a name="p1925mcpsimp"></a>Indicates the name of the interface used by the ARP entry.</p>
    </td>
    </tr>
    <tr id="row1926mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1928mcpsimp"><a name="p1928mcpsimp"></a><a name="p1928mcpsimp"></a>Type</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1930mcpsimp"><a name="p1930mcpsimp"></a><a name="p1930mcpsimp"></a>Indicates whether the ARP entry is dynamic or static. A dynamic ARP entry is automatically created by the protocol stack, and a static ARP entry is added by the user.</p>
    </td>
    </tr>
    </tbody>
    </table>


