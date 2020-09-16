# netdb.h<a name="EN-US_TOPIC_0000001054909432"></a>

## **Overview**<a name="section2057642353084831"></a>

**Related Modules:**

[NET](net.md)

**Description:**

Provides functions and data structures related to network operations. For example, you can use the functions to send and receive network data, manage network addresses, and convert bytes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1762166014084831"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1357069486084831"></a>
<table><thead align="left"><tr id="row2001038320084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p404760213084831"><a name="p404760213084831"></a><a name="p404760213084831"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p174711582084831"><a name="p174711582084831"></a><a name="p174711582084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2025394960084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228288459084831"><a name="p228288459084831"></a><a name="p228288459084831"></a><a href="hostent.md">hostent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644586884084831"><a name="p644586884084831"></a><a name="p644586884084831"></a>Describes the host name and address information. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table139015476084831"></a>
<table><thead align="left"><tr id="row912427721084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1003447012084831"><a name="p1003447012084831"></a><a name="p1003447012084831"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p57829657084831"><a name="p57829657084831"></a><a name="p57829657084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1444474816084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1381165511084831"><a name="p1381165511084831"></a><a name="p1381165511084831"></a><a href="net.md#ga4d04a8261523c8f3473946257c12ce5b">h_addr</a>   h_addr_list[0]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287782825084831"><a name="p287782825084831"></a><a name="p287782825084831"></a>Defines the first address in <strong id="b1399310672084831"><a name="b1399310672084831"></a><a name="b1399310672084831"></a>h_addr_list</strong> for backward compatibility. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table945108315084831"></a>
<table><thead align="left"><tr id="row64423421084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2043201426084831"><a name="p2043201426084831"></a><a name="p2043201426084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1177444437084831"><a name="p1177444437084831"></a><a name="p1177444437084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1513610058084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p944137538084831"><a name="p944137538084831"></a><a name="p944137538084831"></a><a href="net.md#ga6a806414e4ae5bffb09e3a1d25d8db75">setprotoent</a> (int stayopen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313721507084831"><a name="p1313721507084831"></a><a name="p1313721507084831"></a>void </p>
<p id="p1905533569084831"><a name="p1905533569084831"></a><a name="p1905533569084831"></a>Opens a connection to the database and sets the next entry to the first entry. </p>
</td>
</tr>
<tr id="row1791127363084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p325387340084831"><a name="p325387340084831"></a><a name="p325387340084831"></a><a href="net.md#gaca0da70657afbc3e723990bb229deec3">getprotoent</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1067788513084831"><a name="p1067788513084831"></a><a name="p1067788513084831"></a>struct protoent * </p>
<p id="p752107161084831"><a name="p752107161084831"></a><a name="p752107161084831"></a>Retrieves the current protocol information. </p>
</td>
</tr>
<tr id="row438505839084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1366276791084831"><a name="p1366276791084831"></a><a name="p1366276791084831"></a><a href="net.md#ga83ac8a97dd9d895cda658af3aa46fd55">getprotobyname</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1033027255084831"><a name="p1033027255084831"></a><a name="p1033027255084831"></a>struct protoent * </p>
<p id="p1255048031084831"><a name="p1255048031084831"></a><a name="p1255048031084831"></a>Retrieves the information about a specified protocol. </p>
</td>
</tr>
<tr id="row1739474697084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p622390183084831"><a name="p622390183084831"></a><a name="p622390183084831"></a><a href="net.md#gac01697dc4a5b8e434522220913bd46ea">getprotobynumber</a> (int num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441956951084831"><a name="p1441956951084831"></a><a name="p1441956951084831"></a>struct protoent * </p>
<p id="p2138870863084831"><a name="p2138870863084831"></a><a name="p2138870863084831"></a>Retrieves the information about a protocol with the specified number. </p>
</td>
</tr>
<tr id="row186676689084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p573441978084831"><a name="p573441978084831"></a><a name="p573441978084831"></a><a href="net.md#gaa68de2578d4e0849f82d70b2f5b9af70">herror</a> (const char *msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1289792866084831"><a name="p1289792866084831"></a><a name="p1289792866084831"></a>void </p>
<p id="p2145388150084831"><a name="p2145388150084831"></a><a name="p2145388150084831"></a>Prints error information. </p>
</td>
</tr>
<tr id="row1890784669084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1996598602084831"><a name="p1996598602084831"></a><a name="p1996598602084831"></a><a href="net.md#gac1752c48d9cf2ff87e29f29df6caa585">hstrerror</a> (int ecode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1771534592084831"><a name="p1771534592084831"></a><a name="p1771534592084831"></a>const char * </p>
<p id="p895640661084831"><a name="p895640661084831"></a><a name="p895640661084831"></a>Retrieves error information associated with the specified error number. </p>
</td>
</tr>
</tbody>
</table>

