# message.h<a name="ZH-CN_TOPIC_0000001054796529"></a>

## **Overview**<a name="section490867337191849"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Provides message communication APIs that help you to implement asynchronous functions of  [IUnknown](IUnknown.md). 

This API is used to implement asynchronous functions of  [IUnknown](IUnknown.md). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section252396881191849"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1572657226191849"></a>
<table><thead align="left"><tr id="row1876094938191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p380654742191849"><a name="p380654742191849"></a><a name="p380654742191849"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p487186827191849"><a name="p487186827191849"></a><a name="p487186827191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1426218609191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183785347191849"><a name="p1183785347191849"></a><a name="p1183785347191849"></a><a href="Identity.md">Identity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131010737191849"><a name="p2131010737191849"></a><a name="p2131010737191849"></a>Identifies a service and feature. </p>
</td>
</tr>
<tr id="row156646374191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1394956304191849"><a name="p1394956304191849"></a><a name="p1394956304191849"></a><a href="Request.md">Request</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74691266191849"><a name="p74691266191849"></a><a name="p74691266191849"></a>Defines a request. </p>
</td>
</tr>
<tr id="row811533833191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p684233563191849"><a name="p684233563191849"></a><a name="p684233563191849"></a><a href="Response.md">Response</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798310381191849"><a name="p1798310381191849"></a><a name="p1798310381191849"></a>Defines a response. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table2063407124191849"></a>
<table><thead align="left"><tr id="row388732638191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1622225474191849"><a name="p1622225474191849"></a><a name="p1622225474191849"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1772923660191849"><a name="p1772923660191849"></a><a name="p1772923660191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2096799255191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1173033849191849"><a name="p1173033849191849"></a><a name="p1173033849191849"></a><a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a>) (const <a href="Request.md">Request</a> *request, const <a href="Response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859541023191849"><a name="p859541023191849"></a><a name="p859541023191849"></a>typedef void(*&nbsp;</p>
<p id="p1193592317191849"><a name="p1193592317191849"></a><a name="p1193592317191849"></a>Handles asynchronous responses. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table534159506191849"></a>
<table><thead align="left"><tr id="row1603414473191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1270251826191849"><a name="p1270251826191849"></a><a name="p1270251826191849"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1788751212191849"><a name="p1788751212191849"></a><a name="p1788751212191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1314781942191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p880579016191849"><a name="p880579016191849"></a><a name="p880579016191849"></a><a href="Samgr.md#ga03b440d8dff9fcc8694ca8a3baa83462">SAMGR_SendRequest</a> (const <a href="Identity.md">Identity</a> *identity, const <a href="Request.md">Request</a> *request, <a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p390729667191849"><a name="p390729667191849"></a><a name="p390729667191849"></a>int32&nbsp;</p>
<p id="p1189575377191849"><a name="p1189575377191849"></a><a name="p1189575377191849"></a>Sends a request to a service or feature of a specified identity. </p>
</td>
</tr>
<tr id="row1719989144191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p193282323191849"><a name="p193282323191849"></a><a name="p193282323191849"></a><a href="Samgr.md#gae7c4d087b251949d10d81e88a47e8dbd">SAMGR_SendSharedRequest</a> (const <a href="Identity.md">Identity</a> *identity, const <a href="Request.md">Request</a> *request, uint32 *token, <a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308251603191849"><a name="p1308251603191849"></a><a name="p1308251603191849"></a>uint32 *&nbsp;</p>
<p id="p1471126357191849"><a name="p1471126357191849"></a><a name="p1471126357191849"></a>Sends a request to multiple services or features to save memory. </p>
</td>
</tr>
<tr id="row1749673311191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2063204798191849"><a name="p2063204798191849"></a><a name="p2063204798191849"></a><a href="Samgr.md#ga0c8c20d2265f4eb8ec8b516300a94a63">SAMGR_SendSharedDirectRequest</a> (const <a href="Identity.md">Identity</a> *id, const <a href="Request.md">Request</a> *req, const <a href="Response.md">Response</a> *resp, uint32 **ref, <a href="Samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375337849191849"><a name="p375337849191849"></a><a name="p375337849191849"></a>int32&nbsp;</p>
<p id="p1004908798191849"><a name="p1004908798191849"></a><a name="p1004908798191849"></a>Sends a request and response of a caller to the feature thread. The handler is directly called to process the request and response without using the message processing functions. (Customized function for the broadcast service) </p>
</td>
</tr>
<tr id="row1306128896191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p950612437191849"><a name="p950612437191849"></a><a name="p950612437191849"></a><a href="Samgr.md#gadba5f2881a6e1403cb642726d5fec3e2">SAMGR_SendResponse</a> (const <a href="Request.md">Request</a> *request, const <a href="Response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481074402191849"><a name="p1481074402191849"></a><a name="p1481074402191849"></a>int32&nbsp;</p>
<p id="p626501498191849"><a name="p626501498191849"></a><a name="p626501498191849"></a>Sends a response after processing a request. </p>
</td>
</tr>
<tr id="row427295344191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2141255017191849"><a name="p2141255017191849"></a><a name="p2141255017191849"></a><a href="Samgr.md#ga44ab9b4c98e2dd6ba3338d1d2664a6fe">SAMGR_SendResponseByIdentity</a> (const <a href="Identity.md">Identity</a> *id, const <a href="Request.md">Request</a> *request, const <a href="Response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177204681191849"><a name="p177204681191849"></a><a name="p177204681191849"></a>int32&nbsp;</p>
<p id="p360556508191849"><a name="p360556508191849"></a><a name="p360556508191849"></a>Sends a response to a specified service or feature after processing the original request. (Customized function for <strong id="b1968329545191849"><a name="b1968329545191849"></a><a name="b1968329545191849"></a>bootstrap</strong>) </p>
</td>
</tr>
</tbody>
</table>

