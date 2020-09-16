# message.h<a name="ZH-CN_TOPIC_0000001054879506"></a>

## **Overview**<a name="section227787345093526"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Provides message communication APIs that help you to implement asynchronous functions of  [IUnknown](IUnknown.md). 

This API is used to implement asynchronous functions of  [IUnknown](IUnknown.md). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1945027327093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1984817618093526"></a>
<table><thead align="left"><tr id="row845826189093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1840314261093526"><a name="p1840314261093526"></a><a name="p1840314261093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1483616085093526"><a name="p1483616085093526"></a><a name="p1483616085093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row579042232093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2063318584093526"><a name="p2063318584093526"></a><a name="p2063318584093526"></a><a href="Identity.md">Identity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369297118093526"><a name="p369297118093526"></a><a name="p369297118093526"></a>Identifies a service and feature. </p>
</td>
</tr>
<tr id="row272507447093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1556938471093526"><a name="p1556938471093526"></a><a name="p1556938471093526"></a><a href="Request.md">Request</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1222338606093526"><a name="p1222338606093526"></a><a name="p1222338606093526"></a>Defines a request. </p>
</td>
</tr>
<tr id="row1549077053093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626580529093526"><a name="p1626580529093526"></a><a name="p1626580529093526"></a><a href="Response.md">Response</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p251647726093526"><a name="p251647726093526"></a><a name="p251647726093526"></a>Defines a response. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1959315431093526"></a>
<table><thead align="left"><tr id="row855498101093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1531887401093526"><a name="p1531887401093526"></a><a name="p1531887401093526"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1396761948093526"><a name="p1396761948093526"></a><a name="p1396761948093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1919315426093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382619945093526"><a name="p382619945093526"></a><a name="p382619945093526"></a><a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a>) (const <a href="Request.md">Request</a> *request, const <a href="Response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201637423093526"><a name="p1201637423093526"></a><a name="p1201637423093526"></a>typedef void(*&nbsp;</p>
<p id="p140611525093526"><a name="p140611525093526"></a><a name="p140611525093526"></a>Handles asynchronous responses. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1297312720093526"></a>
<table><thead align="left"><tr id="row1356259142093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1519625187093526"><a name="p1519625187093526"></a><a name="p1519625187093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p550021568093526"><a name="p550021568093526"></a><a name="p550021568093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1475436851093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1228834805093526"><a name="p1228834805093526"></a><a name="p1228834805093526"></a><a href="Samgr.md#ga03b440d8dff9fcc8694ca8a3baa83462">SAMGR_SendRequest</a> (const <a href="Identity.md">Identity</a> *identity, const <a href="Request.md">Request</a> *request, <a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1641387521093526"><a name="p1641387521093526"></a><a name="p1641387521093526"></a>int32&nbsp;</p>
<p id="p1645440575093526"><a name="p1645440575093526"></a><a name="p1645440575093526"></a>Sends a request to a service or feature of a specified identity. </p>
</td>
</tr>
<tr id="row1155718773093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1625079962093526"><a name="p1625079962093526"></a><a name="p1625079962093526"></a><a href="Samgr.md#gae7c4d087b251949d10d81e88a47e8dbd">SAMGR_SendSharedRequest</a> (const <a href="Identity.md">Identity</a> *identity, const <a href="Request.md">Request</a> *request, uint32 *token, <a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059266169093526"><a name="p1059266169093526"></a><a name="p1059266169093526"></a>uint32 *&nbsp;</p>
<p id="p1380049087093526"><a name="p1380049087093526"></a><a name="p1380049087093526"></a>Sends a request to multiple services or features to save memory. </p>
</td>
</tr>
<tr id="row1764535691093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907851227093526"><a name="p907851227093526"></a><a name="p907851227093526"></a><a href="Samgr.md#ga0c8c20d2265f4eb8ec8b516300a94a63">SAMGR_SendSharedDirectRequest</a> (const <a href="Identity.md">Identity</a> *id, const <a href="Request.md">Request</a> *req, const <a href="Response.md">Response</a> *resp, uint32 **ref, <a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904777534093526"><a name="p904777534093526"></a><a name="p904777534093526"></a>int32&nbsp;</p>
<p id="p1269799530093526"><a name="p1269799530093526"></a><a name="p1269799530093526"></a>Sends a request and response of a caller to the feature thread. The handler is directly called to process the request and response without using the message processing functions. (Customized function for the broadcast service) </p>
</td>
</tr>
<tr id="row28775903093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p976938072093526"><a name="p976938072093526"></a><a name="p976938072093526"></a><a href="Samgr.md#gadba5f2881a6e1403cb642726d5fec3e2">SAMGR_SendResponse</a> (const <a href="Request.md">Request</a> *request, const <a href="Response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p652813020093526"><a name="p652813020093526"></a><a name="p652813020093526"></a>int32&nbsp;</p>
<p id="p1743162153093526"><a name="p1743162153093526"></a><a name="p1743162153093526"></a>Sends a response after processing a request. </p>
</td>
</tr>
<tr id="row1092612673093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662212202093526"><a name="p662212202093526"></a><a name="p662212202093526"></a><a href="Samgr.md#ga44ab9b4c98e2dd6ba3338d1d2664a6fe">SAMGR_SendResponseByIdentity</a> (const <a href="Identity.md">Identity</a> *id, const <a href="Request.md">Request</a> *request, const <a href="Response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p638789290093526"><a name="p638789290093526"></a><a name="p638789290093526"></a>int32&nbsp;</p>
<p id="p93977709093526"><a name="p93977709093526"></a><a name="p93977709093526"></a>Sends a response to a specified service or feature after processing the original request. (Customized function for <strong id="b1506306185093526"><a name="b1506306185093526"></a><a name="b1506306185093526"></a>bootstrap</strong>) </p>
</td>
</tr>
</tbody>
</table>

