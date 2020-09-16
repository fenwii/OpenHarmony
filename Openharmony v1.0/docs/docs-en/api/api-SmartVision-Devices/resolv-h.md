# resolv.h<a name="EN-US_TOPIC_0000001055308037"></a>

## **Overview**<a name="section129314424084832"></a>

**Related Modules:**

[NET](net.md)

**Description:**

Provides functions and data structures related to network operations. For example, you can use the functions to send and receive network data, manage network addresses, and convert bytes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1490096876084832"></a>

## Functions<a name="func-members"></a>

<a name="table1028871520084832"></a>
<table><thead align="left"><tr id="row1206933154084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1303850846084832"><a name="p1303850846084832"></a><a name="p1303850846084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2117307153084832"><a name="p2117307153084832"></a><a name="p2117307153084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1327861180084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934256015084832"><a name="p1934256015084832"></a><a name="p1934256015084832"></a><a href="net.md#ga0438570faf515401bffa1a0d9c94a266">dn_comp</a> (const char *src, unsigned char *dst, int space, unsigned char **dnptrs, unsigned char **lastdnptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p628871895084832"><a name="p628871895084832"></a><a name="p628871895084832"></a>int </p>
<p id="p1223790885084832"><a name="p1223790885084832"></a><a name="p1223790885084832"></a>Compresses a network domain name. </p>
</td>
</tr>
<tr id="row1285912204084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p249277312084832"><a name="p249277312084832"></a><a name="p249277312084832"></a><a href="net.md#ga91eb2055a64b28e4942a3a760d747243">dn_expand</a> (const unsigned char *base, const unsigned char *end, const unsigned char *src, char *dest, int space)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842897270084832"><a name="p842897270084832"></a><a name="p842897270084832"></a>int </p>
<p id="p596949304084832"><a name="p596949304084832"></a><a name="p596949304084832"></a>Expands a compressed domain name to a full domain name. </p>
</td>
</tr>
</tbody>
</table>

