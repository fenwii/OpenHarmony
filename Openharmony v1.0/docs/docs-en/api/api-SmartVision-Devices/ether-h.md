# ether.h<a name="EN-US_TOPIC_0000001054829483"></a>

## **Overview**<a name="section130979180084829"></a>

**Related Modules:**

[NET](net.md)

**Description:**

Provides functions and data structures related to network operations. For example, you can use the functions to send and receive network data, manage network addresses, and convert bytes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1328370174084829"></a>

## Functions<a name="func-members"></a>

<a name="table1920198241084829"></a>
<table><thead align="left"><tr id="row1953245232084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2067996324084829"><a name="p2067996324084829"></a><a name="p2067996324084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1466511907084829"><a name="p1466511907084829"></a><a name="p1466511907084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1709509553084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p711783456084829"><a name="p711783456084829"></a><a name="p711783456084829"></a><a href="net.md#ga07e34e6ee9e272c4799780915d11677c">ether_ntoa</a> (const struct ether_addr *p_a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305652762084829"><a name="p1305652762084829"></a><a name="p1305652762084829"></a>char * </p>
<p id="p1579897422084829"><a name="p1579897422084829"></a><a name="p1579897422084829"></a>Converts binary data in network byte order into a standard 48-bit Ethernet host address in the colon hexadecimal notation. </p>
</td>
</tr>
<tr id="row184993163084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393436889084829"><a name="p1393436889084829"></a><a name="p1393436889084829"></a><a href="net.md#gaab4c5b65c36fc0ea96a017daabc3770a">ether_aton</a> (const char *x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994921515084829"><a name="p994921515084829"></a><a name="p994921515084829"></a>struct ether_addr * </p>
<p id="p1873866681084829"><a name="p1873866681084829"></a><a name="p1873866681084829"></a>Converts a standard 48-bit Ethernet host address in the colon hexadecimal notation into binary data in network byte order. </p>
</td>
</tr>
<tr id="row334136274084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716382259084829"><a name="p716382259084829"></a><a name="p716382259084829"></a><a href="net.md#ga245e21de8e82756712a5182c2674c2ad">ether_ntoa_r</a> (const struct ether_addr *p_a, char *x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931209957084829"><a name="p931209957084829"></a><a name="p931209957084829"></a>char * </p>
<p id="p1793424847084829"><a name="p1793424847084829"></a><a name="p1793424847084829"></a>Converts binary data in network byte order into a standard 48-bit Ethernet host address in the colon hexadecimal notation. This function is reentrant. </p>
</td>
</tr>
<tr id="row144813171084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247050141084829"><a name="p1247050141084829"></a><a name="p1247050141084829"></a><a href="net.md#gac0954821754bace30f674e61bb9f4e5f">ether_aton_r</a> (const char *x, struct ether_addr *p_a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284852490084829"><a name="p284852490084829"></a><a name="p284852490084829"></a>struct ether_addr * </p>
<p id="p1469125427084829"><a name="p1469125427084829"></a><a name="p1469125427084829"></a>Converts a standard 48-bit Ethernet host address in the colon hexadecimal notation into binary data in network byte order. This function is reentrant. </p>
</td>
</tr>
</tbody>
</table>

