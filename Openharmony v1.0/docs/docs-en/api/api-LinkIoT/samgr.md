# Samgr<a name="EN-US_TOPIC_0000001054715047"></a>

## **Overview**<a name="section1198410470090251"></a>

Manages system capabilities. 

This module provides the development framework base of the service-oriented architecture \(SOA\). You can develop your own abilities based on the Samgr development framework. This module provides basic models of services, features, and functions, and registration and discovery capabilities. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1129403243090251"></a>

## Files<a name="files"></a>

<a name="table2044835365090251"></a>
<table><thead align="left"><tr id="row345291593090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p786054434090251"><a name="p786054434090251"></a><a name="p786054434090251"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1466968346090251"><a name="p1466968346090251"></a><a name="p1466968346090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1682363436090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2066921740090251"><a name="p2066921740090251"></a><a name="p2066921740090251"></a><a href="common-h.md">common.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266324314090251"><a name="p1266324314090251"></a><a name="p1266324314090251"></a>Provides common objects and functions for Samgr and external modules. </p>
</td>
</tr>
<tr id="row867069756090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2093919664090251"><a name="p2093919664090251"></a><a name="p2093919664090251"></a><a href="feature-h.md">feature.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p119649395090251"><a name="p119649395090251"></a><a name="p119649395090251"></a>Defines the base class of a feature. </p>
</td>
</tr>
<tr id="row2108474342090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p547452597090251"><a name="p547452597090251"></a><a name="p547452597090251"></a><a href="iunknown-h.md">iunknown.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1991147643090251"><a name="p1991147643090251"></a><a name="p1991147643090251"></a>Provides the base class and default implementation for external functions of system capabilities. </p>
</td>
</tr>
<tr id="row796779364090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2048475469090251"><a name="p2048475469090251"></a><a name="p2048475469090251"></a><a href="message-h.md">message.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561654959090251"><a name="p1561654959090251"></a><a name="p1561654959090251"></a>Provides message communication APIs that help you to implement asynchronous functions of <a href="iunknown.md">IUnknown</a>. </p>
</td>
</tr>
<tr id="row1932977983090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1559543293090251"><a name="p1559543293090251"></a><a name="p1559543293090251"></a><a href="samgr_lite-h.md">samgr_lite.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673971483090251"><a name="p1673971483090251"></a><a name="p1673971483090251"></a>Manages system capabilities. </p>
</td>
</tr>
<tr id="row2143098297090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p341521057090251"><a name="p341521057090251"></a><a name="p341521057090251"></a><a href="service-h.md">service.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p887721653090251"><a name="p887721653090251"></a><a name="p887721653090251"></a>Provides basic types and constants of services. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table2075354683090251"></a>
<table><thead align="left"><tr id="row324001174090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p527272444090251"><a name="p527272444090251"></a><a name="p527272444090251"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1844913962090251"><a name="p1844913962090251"></a><a name="p1844913962090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row90952491090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087860125090251"><a name="p2087860125090251"></a><a name="p2087860125090251"></a><a href="simplevector.md">SimpleVector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1360796389090251"><a name="p1360796389090251"></a><a name="p1360796389090251"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
<tr id="row1104533812090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p884304604090251"><a name="p884304604090251"></a><a name="p884304604090251"></a><a href="feature.md">Feature</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1667246312090251"><a name="p1667246312090251"></a><a name="p1667246312090251"></a>Defines the base class of a feature. </p>
</td>
</tr>
<tr id="row388485771090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1804715358090251"><a name="p1804715358090251"></a><a name="p1804715358090251"></a><a href="iunknown.md">IUnknown</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p641648004090251"><a name="p641648004090251"></a><a name="p641648004090251"></a>Defines the <strong id="b1590895935090251"><a name="b1590895935090251"></a><a name="b1590895935090251"></a><a href="iunknown.md">IUnknown</a></strong> class. </p>
</td>
</tr>
<tr id="row1292128046090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p178598111090251"><a name="p178598111090251"></a><a name="p178598111090251"></a><a href="iunknownentry.md">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638863698090251"><a name="p1638863698090251"></a><a name="p1638863698090251"></a>Defines the <strong id="b471568877090251"><a name="b471568877090251"></a><a name="b471568877090251"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
<tr id="row1674093872090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521085203090251"><a name="p521085203090251"></a><a name="p521085203090251"></a><a href="identity.md">Identity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p633635469090251"><a name="p633635469090251"></a><a name="p633635469090251"></a>Identifies a service and feature. </p>
</td>
</tr>
<tr id="row1029830504090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1457351485090251"><a name="p1457351485090251"></a><a name="p1457351485090251"></a><a href="request.md">Request</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090323063090251"><a name="p2090323063090251"></a><a name="p2090323063090251"></a>Defines a request. </p>
</td>
</tr>
<tr id="row229030773090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014719945090251"><a name="p2014719945090251"></a><a name="p2014719945090251"></a><a href="response.md">Response</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206473900090251"><a name="p206473900090251"></a><a name="p206473900090251"></a>Defines a response. </p>
</td>
</tr>
<tr id="row531185981090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1592868998090251"><a name="p1592868998090251"></a><a name="p1592868998090251"></a><a href="samgrlite.md">SamgrLite</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p314008953090251"><a name="p314008953090251"></a><a name="p314008953090251"></a>Represents the system ability management class. </p>
</td>
</tr>
<tr id="row1867724626090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935578751090251"><a name="p935578751090251"></a><a name="p935578751090251"></a><a href="taskconfig.md">TaskConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1116648357090251"><a name="p1116648357090251"></a><a name="p1116648357090251"></a>Defines task configurations for a service. </p>
</td>
</tr>
<tr id="row1323183419090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p729490945090251"><a name="p729490945090251"></a><a name="p729490945090251"></a><a href="service.md">Service</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1294208744090251"><a name="p1294208744090251"></a><a name="p1294208744090251"></a>Indicates the basic type of a service. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table931454424090251"></a>
<table><thead align="left"><tr id="row891967589090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1478405054090251"><a name="p1478405054090251"></a><a name="p1478405054090251"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p365649652090251"><a name="p365649652090251"></a><a name="p365649652090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row727337731090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1983579211090251"><a name="p1983579211090251"></a><a name="p1983579211090251"></a><a href="samgr.md#gab094855efe05ae51eaaf3e0ddf0346cc">GET_OFFSIZE</a>(T, member)   (long)((char *)&amp;(((T *)(0))-&gt;member))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1654863425090251"><a name="p1654863425090251"></a><a name="p1654863425090251"></a>Calculates the offset of the member in the T type. </p>
</td>
</tr>
<tr id="row1857742699090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p551951255090251"><a name="p551951255090251"></a><a name="p551951255090251"></a><a href="samgr.md#ga63c2f681bde297cb28a9a300a462f3f4">INHERIT_FEATURE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1957458352090251"><a name="p1957458352090251"></a><a name="p1957458352090251"></a>Inherits from the macro of the feature class. </p>
</td>
</tr>
<tr id="row209527492090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1212062395090251"><a name="p1212062395090251"></a><a name="p1212062395090251"></a><a href="samgr.md#ga13dae059206df8d2d9b9b42e694b3f9c">DEFAULT_VERSION</a>   0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303318244090251"><a name="p1303318244090251"></a><a name="p1303318244090251"></a>Defines the default <a href="iunknown.md">IUnknown</a> version. You can customize the version. </p>
</td>
</tr>
<tr id="row272102842090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p900671566090251"><a name="p900671566090251"></a><a name="p900671566090251"></a><a href="samgr.md#gab74532a22d6993d0ffc014d36253397f">INHERIT_IUNKNOWN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73206041090251"><a name="p73206041090251"></a><a name="p73206041090251"></a>Defines the macro for inheriting the <strong id="b110001570090251"><a name="b110001570090251"></a><a name="b110001570090251"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1921264422090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1355983873090251"><a name="p1355983873090251"></a><a name="p1355983873090251"></a><a href="samgr.md#gad6324fd90dd636180efa2a59b377e65c">INHERIT_IUNKNOWNENTRY</a>(T)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p821347630090251"><a name="p821347630090251"></a><a name="p821347630090251"></a>Defines the macro for inheriting the classes that implement the <strong id="b2104295071090251"><a name="b2104295071090251"></a><a name="b2104295071090251"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row892687642090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024681541090251"><a name="p2024681541090251"></a><a name="p2024681541090251"></a><a href="samgr.md#gac8d8c9671531f9340427153d50ca4a2b">DEFAULT_IUNKNOWN_IMPL</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1208606483090251"><a name="p1208606483090251"></a><a name="p1208606483090251"></a>Defines the default marco for initializing the <strong id="b1193898754090251"><a name="b1193898754090251"></a><a name="b1193898754090251"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row2019181798090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1137038963090251"><a name="p1137038963090251"></a><a name="p1137038963090251"></a><a href="samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1">IUNKNOWN_ENTRY_BEGIN</a>(version)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p538936643090251"><a name="p538936643090251"></a><a name="p538936643090251"></a>Defines the macro for initializing the classes that implement the <strong id="b682949395090251"><a name="b682949395090251"></a><a name="b682949395090251"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row2020027773090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761953018090251"><a name="p1761953018090251"></a><a name="p1761953018090251"></a><a href="samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3">IUNKNOWN_ENTRY_END</a>   }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p433759306090251"><a name="p433759306090251"></a><a name="p433759306090251"></a><a href="iunknown.md">IUnknown</a> Defines the end macro for initializing the <strong id="b209691124090251"><a name="b209691124090251"></a><a name="b209691124090251"></a><a href="iunknown.md">IUnknown</a></strong> implementation object. </p>
</td>
</tr>
<tr id="row1236569301090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p187609433090251"><a name="p187609433090251"></a><a name="p187609433090251"></a><a href="samgr.md#ga9403f55c3f75fd03854dcd37c231e05b">GET_IUNKNOWN</a>(T)   (<a href="iunknown.md">IUnknown</a> *)(&amp;((T).iUnknown))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1051372482090251"><a name="p1051372482090251"></a><a name="p1051372482090251"></a>Obtains the pointer of the <strong id="b1339386364090251"><a name="b1339386364090251"></a><a name="b1339386364090251"></a><a href="iunknown.md">IUnknown</a></strong> interface object from the subclass object T (generic macro) of the <strong id="b1813502175090251"><a name="b1813502175090251"></a><a name="b1813502175090251"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
<tr id="row1762820117090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p324382283090251"><a name="p324382283090251"></a><a name="p324382283090251"></a><em id="gadc00f0568236d4538c867ed7194d8960"><a name="gadc00f0568236d4538c867ed7194d8960"></a><a name="gadc00f0568236d4538c867ed7194d8960"></a></em>BOOTSTRAP_SERVICE    "Bootstrap"</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567994412090251"><a name="p1567994412090251"></a><a name="p1567994412090251"></a>Starts a bootstrap service, which is used by samgr and implemented by system service developers. </p>
</td>
</tr>
<tr id="row1500298556090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p694884275090251"><a name="p694884275090251"></a><a name="p694884275090251"></a><a href="samgr.md#gae9253a7fc1d0acbab91414b4cacc1d84">INHERIT_SERVICE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099296592090251"><a name="p1099296592090251"></a><a name="p1099296592090251"></a>Indicates the macro used to inherit the members from the <strong id="b866250399090251"><a name="b866250399090251"></a><a name="b866250399090251"></a>service</strong> class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table2100433725090251"></a>
<table><thead align="left"><tr id="row1816888183090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1240500193090251"><a name="p1240500193090251"></a><a name="p1240500193090251"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p851258433090251"><a name="p851258433090251"></a><a name="p851258433090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1289022097090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p330845254090251"><a name="p330845254090251"></a><a name="p330845254090251"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1858442784090251"><a name="p1858442784090251"></a><a name="p1858442784090251"></a>typedef struct <a href="simplevector.md">SimpleVector</a> </p>
<p id="p1487905068090251"><a name="p1487905068090251"></a><a name="p1487905068090251"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
<tr id="row1820871402090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p563625076090251"><a name="p563625076090251"></a><a name="p563625076090251"></a><a href="samgr.md#gacaa7db32a018a33a2bbf919cde8d8f9c">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p242508138090251"><a name="p242508138090251"></a><a name="p242508138090251"></a>typedef struct <a href="iunknownentry.md">IUnknownEntry</a> </p>
<p id="p1789794500090251"><a name="p1789794500090251"></a><a name="p1789794500090251"></a>Defines the <strong id="b1178206765090251"><a name="b1178206765090251"></a><a name="b1178206765090251"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
<tr id="row2059445640090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1919228543090251"><a name="p1919228543090251"></a><a name="p1919228543090251"></a><a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a>) (const <a href="request.md">Request</a> *request, const <a href="response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p691786619090251"><a name="p691786619090251"></a><a name="p691786619090251"></a>typedef void(* </p>
<p id="p214877384090251"><a name="p214877384090251"></a><a name="p214877384090251"></a>Handles asynchronous responses. </p>
</td>
</tr>
<tr id="row1549273024090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1679518249090251"><a name="p1679518249090251"></a><a name="p1679518249090251"></a><a href="samgr.md#gadc486c8d2698eab8a9f26f0eb6cc63c8">BootMessage</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207009928090251"><a name="p1207009928090251"></a><a name="p1207009928090251"></a>typedef enum <a href="samgr.md#gaf39e482610dca95f0dba85613755eb40">BootMessage</a> </p>
<p id="p1182093202090251"><a name="p1182093202090251"></a><a name="p1182093202090251"></a>Enumerates the IDs of the message to be processed for starting the bootstrap service. </p>
</td>
</tr>
<tr id="row591448736090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1486203205090251"><a name="p1486203205090251"></a><a name="p1486203205090251"></a><a href="samgr.md#gaad729fe4f36b7b42a122349af334fb28">SamgrLite</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073746405090251"><a name="p2073746405090251"></a><a name="p2073746405090251"></a>typedef struct <a href="samgrlite.md">SamgrLite</a> </p>
<p id="p2106179950090251"><a name="p2106179950090251"></a><a name="p2106179950090251"></a>Represents the system ability management class. </p>
</td>
</tr>
<tr id="row452053792090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236533271090251"><a name="p236533271090251"></a><a name="p236533271090251"></a><a href="samgr.md#gab265648f2dbef93878ad8c383712b43a">TaskType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p573309501090251"><a name="p573309501090251"></a><a name="p573309501090251"></a>typedef enum <a href="samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a> </p>
<p id="p926357161090251"><a name="p926357161090251"></a><a name="p926357161090251"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row822093909090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892982340090251"><a name="p1892982340090251"></a><a name="p1892982340090251"></a><a href="samgr.md#gae9c7eed07272a46851d61e646b6e86d5">SpecifyTag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1212075030090251"><a name="p1212075030090251"></a><a name="p1212075030090251"></a>typedef enum <a href="samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a> </p>
<p id="p899307972090251"><a name="p899307972090251"></a><a name="p899307972090251"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row59495320090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671906240090251"><a name="p671906240090251"></a><a name="p671906240090251"></a><a href="samgr.md#gaef69bbb3353ea484414c3bbaf8ec362b">TaskPriority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1718077584090251"><a name="p1718077584090251"></a><a name="p1718077584090251"></a>typedef enum <a href="samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a> </p>
<p id="p1000751757090251"><a name="p1000751757090251"></a><a name="p1000751757090251"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table3186092090251"></a>
<table><thead align="left"><tr id="row1671966725090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1083420467090251"><a name="p1083420467090251"></a><a name="p1083420467090251"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p591266479090251"><a name="p591266479090251"></a><a name="p591266479090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row232057888090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850461181090251"><a name="p1850461181090251"></a><a name="p1850461181090251"></a><a href="samgr.md#gaf39e482610dca95f0dba85613755eb40">BootMessage</a> { <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7">BOOT_SYS_COMPLETED</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1">BOOT_APP_COMPLETED</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572">BOOT_REG_SERVICE</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec">BOOTSTRAP_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p148427384090251"><a name="p148427384090251"></a><a name="p148427384090251"></a>Enumerates the IDs of the message to be processed for starting the bootstrap service. </p>
</td>
</tr>
<tr id="row1239314926090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132298402090251"><a name="p2132298402090251"></a><a name="p2132298402090251"></a><a href="samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a> { <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99">SHARED_TASK</a> = 0, <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315">SINGLE_TASK</a> = 1, <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376">SPECIFIED_TASK</a> = 2, <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11">NO_TASK</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1252298568090251"><a name="p1252298568090251"></a><a name="p1252298568090251"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row1635974821090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401922982090251"><a name="p1401922982090251"></a><a name="p1401922982090251"></a><a href="samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a> { <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955">LEVEL_HIGH</a> = 0, <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647">LEVEL_MIDDLE</a> = 1, <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5">LEVEL_LOW</a> = 2, <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263">LEVEL_CUSTOM_BEGIN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1580416024090251"><a name="p1580416024090251"></a><a name="p1580416024090251"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row1155328802090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274186846090251"><a name="p1274186846090251"></a><a name="p1274186846090251"></a><a href="samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a> {   <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402">PRI_LOW</a> = 9, <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258">PRI_BELOW_NORMAL</a> = 16, <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063">PRI_NORMAL</a> = 24, <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6">PRI_ABOVE_NORMAL</a> = 32,   <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b">PRI_BUTT</a> = 39 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844021317090251"><a name="p1844021317090251"></a><a name="p1844021317090251"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table774085563090251"></a>
<table><thead align="left"><tr id="row1457473510090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p992391663090251"><a name="p992391663090251"></a><a name="p992391663090251"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p355965946090251"><a name="p355965946090251"></a><a name="p355965946090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1393981896090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712340226090251"><a name="p1712340226090251"></a><a name="p1712340226090251"></a><a href="samgr.md#gae790345f8a2863c143bfee4bab3fb6d7">VECTOR_Make</a> (VECTOR_Key key, VECTOR_Compare compare)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p22909296090251"><a name="p22909296090251"></a><a name="p22909296090251"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> </p>
<p id="p829171923090251"><a name="p829171923090251"></a><a name="p829171923090251"></a>Creates or initializes a vector object. </p>
</td>
</tr>
<tr id="row797479647090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476563010090251"><a name="p476563010090251"></a><a name="p476563010090251"></a><a href="samgr.md#gaebfe9ac38f2667d61bf39420aa8e7035">VECTOR_Clear</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453530426090251"><a name="p453530426090251"></a><a name="p453530426090251"></a>void </p>
<p id="p1216293216090251"><a name="p1216293216090251"></a><a name="p1216293216090251"></a>Destruct a vector object. </p>
</td>
</tr>
<tr id="row1749273782090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p818402421090251"><a name="p818402421090251"></a><a name="p818402421090251"></a><a href="samgr.md#ga234ba2452c973e9fa4a8be47eaea9d06">VECTOR_Add</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p438487713090251"><a name="p438487713090251"></a><a name="p438487713090251"></a>int16 </p>
<p id="p360672133090251"><a name="p360672133090251"></a><a name="p360672133090251"></a>Adds an element to the vector. </p>
</td>
</tr>
<tr id="row2012771576090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1208565096090251"><a name="p1208565096090251"></a><a name="p1208565096090251"></a><a href="samgr.md#ga1432f30c136d14bc00414d883d8be3bd">VECTOR_Size</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1786185710090251"><a name="p1786185710090251"></a><a name="p1786185710090251"></a>int16 </p>
<p id="p1823639713090251"><a name="p1823639713090251"></a><a name="p1823639713090251"></a>Obtains the number of elements in the vector, including elements that have been set to <strong id="b949060399090251"><a name="b949060399090251"></a><a name="b949060399090251"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row1247621836090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974688218090251"><a name="p1974688218090251"></a><a name="p1974688218090251"></a><a href="samgr.md#ga90523bfd48091a0135f74670076af4d5">VECTOR_Num</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512082388090251"><a name="p1512082388090251"></a><a name="p1512082388090251"></a>int16 </p>
<p id="p1248043151090251"><a name="p1248043151090251"></a><a name="p1248043151090251"></a>Obtains the number of valid elements in the vector, excluding elements that have been set to <strong id="b196263952090251"><a name="b196263952090251"></a><a name="b196263952090251"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row959546128090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242887967090251"><a name="p1242887967090251"></a><a name="p1242887967090251"></a><a href="samgr.md#ga75210ba0bd37a38a1902c4904e61246a">VECTOR_At</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 index)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296913045090251"><a name="p1296913045090251"></a><a name="p1296913045090251"></a>void * </p>
<p id="p1829240686090251"><a name="p1829240686090251"></a><a name="p1829240686090251"></a>Obtains the element at a specified position. </p>
</td>
</tr>
<tr id="row1102282513090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1499802438090251"><a name="p1499802438090251"></a><a name="p1499802438090251"></a><a href="samgr.md#ga7f435d33ba61d145de9d5892b68a0eda">VECTOR_Swap</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 index, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1885708610090251"><a name="p1885708610090251"></a><a name="p1885708610090251"></a>void * </p>
<p id="p313693973090251"><a name="p313693973090251"></a><a name="p313693973090251"></a>Swaps the element at a specified position in a vector with another element. </p>
</td>
</tr>
<tr id="row962769553090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1865149794090251"><a name="p1865149794090251"></a><a name="p1865149794090251"></a><a href="samgr.md#gaabc5b0eda1ee6889411e6dacb233cb07">VECTOR_Find</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209570894090251"><a name="p209570894090251"></a><a name="p209570894090251"></a>int16 </p>
<p id="p1159407766090251"><a name="p1159407766090251"></a><a name="p1159407766090251"></a>Checks the position of an element. </p>
</td>
</tr>
<tr id="row986056407090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p728934019090251"><a name="p728934019090251"></a><a name="p728934019090251"></a><a href="samgr.md#gac65bc6dc959a90d95dff93368abd97c7">VECTOR_FindByKey</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p128844508090251"><a name="p128844508090251"></a><a name="p128844508090251"></a>int16 </p>
<p id="p1974386226090251"><a name="p1974386226090251"></a><a name="p1974386226090251"></a>Checks the position of the element with a specified key. </p>
</td>
</tr>
<tr id="row1049225753090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p744846362090251"><a name="p744846362090251"></a><a name="p744846362090251"></a><a href="samgr.md#ga9abef49ec89bf913c3bed03faf478c1e">IUNKNOWN_AddRef</a> (<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2024727768090251"><a name="p2024727768090251"></a><a name="p2024727768090251"></a>int </p>
<p id="p2134401529090251"><a name="p2134401529090251"></a><a name="p2134401529090251"></a>Increments the reference count in this <strong id="b1112086242090251"><a name="b1112086242090251"></a><a name="b1112086242090251"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1653093334090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50183179090251"><a name="p50183179090251"></a><a name="p50183179090251"></a><a href="samgr.md#gac857d12648500c7dab1cb43e85ae2ed4">IUNKNOWN_QueryInterface</a> (<a href="iunknown.md">IUnknown</a> *iUnknown, int ver, void **target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1230713787090251"><a name="p1230713787090251"></a><a name="p1230713787090251"></a>int </p>
<p id="p771393535090251"><a name="p771393535090251"></a><a name="p771393535090251"></a>Queries the <strong id="b1619974969090251"><a name="b1619974969090251"></a><a name="b1619974969090251"></a><a href="iunknown.md">IUnknown</a></strong> interfaces of a specified version (downcasting). </p>
</td>
</tr>
<tr id="row1497238672090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1170978906090251"><a name="p1170978906090251"></a><a name="p1170978906090251"></a><a href="samgr.md#gabd462f8a5e6460a68760cd0719982296">IUNKNOWN_Release</a> (<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1493993492090251"><a name="p1493993492090251"></a><a name="p1493993492090251"></a>int </p>
<p id="p1719071053090251"><a name="p1719071053090251"></a><a name="p1719071053090251"></a>Releases a reference to an <strong id="b640790898090251"><a name="b640790898090251"></a><a name="b640790898090251"></a><a href="iunknown.md">IUnknown</a></strong> interface that is no longer used. </p>
</td>
</tr>
<tr id="row2071601977090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096801232090251"><a name="p1096801232090251"></a><a name="p1096801232090251"></a><a href="samgr.md#ga03b440d8dff9fcc8694ca8a3baa83462">SAMGR_SendRequest</a> (const <a href="identity.md">Identity</a> *identity, const <a href="request.md">Request</a> *request, <a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342487079090251"><a name="p1342487079090251"></a><a name="p1342487079090251"></a>int32 </p>
<p id="p1495268878090251"><a name="p1495268878090251"></a><a name="p1495268878090251"></a>Sends a request to a service or feature of a specified identity. </p>
</td>
</tr>
<tr id="row2014465149090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1913916835090251"><a name="p1913916835090251"></a><a name="p1913916835090251"></a><a href="samgr.md#gae7c4d087b251949d10d81e88a47e8dbd">SAMGR_SendSharedRequest</a> (const <a href="identity.md">Identity</a> *identity, const <a href="request.md">Request</a> *request, uint32 *token, <a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1792842355090251"><a name="p1792842355090251"></a><a name="p1792842355090251"></a>uint32 * </p>
<p id="p1065800656090251"><a name="p1065800656090251"></a><a name="p1065800656090251"></a>Sends a request to multiple services or features to save memory. </p>
</td>
</tr>
<tr id="row2067371477090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1585004814090251"><a name="p1585004814090251"></a><a name="p1585004814090251"></a><a href="samgr.md#ga0c8c20d2265f4eb8ec8b516300a94a63">SAMGR_SendSharedDirectRequest</a> (const <a href="identity.md">Identity</a> *id, const <a href="request.md">Request</a> *req, const <a href="response.md">Response</a> *resp, uint32 **ref, <a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1337028684090251"><a name="p1337028684090251"></a><a name="p1337028684090251"></a>int32 </p>
<p id="p352395311090251"><a name="p352395311090251"></a><a name="p352395311090251"></a>Sends a request and response of a caller to the feature thread. The handler is directly called to process the request and response without using the message processing functions. (Customized function for the broadcast service) </p>
</td>
</tr>
<tr id="row1959048863090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1299787508090251"><a name="p1299787508090251"></a><a name="p1299787508090251"></a><a href="samgr.md#gadba5f2881a6e1403cb642726d5fec3e2">SAMGR_SendResponse</a> (const <a href="request.md">Request</a> *request, const <a href="response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1244401644090251"><a name="p1244401644090251"></a><a name="p1244401644090251"></a>int32 </p>
<p id="p662626517090251"><a name="p662626517090251"></a><a name="p662626517090251"></a>Sends a response after processing a request. </p>
</td>
</tr>
<tr id="row1721952813090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1085117495090251"><a name="p1085117495090251"></a><a name="p1085117495090251"></a><a href="samgr.md#ga44ab9b4c98e2dd6ba3338d1d2664a6fe">SAMGR_SendResponseByIdentity</a> (const <a href="identity.md">Identity</a> *id, const <a href="request.md">Request</a> *request, const <a href="response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357478251090251"><a name="p1357478251090251"></a><a name="p1357478251090251"></a>int32 </p>
<p id="p1956977053090251"><a name="p1956977053090251"></a><a name="p1956977053090251"></a>Sends a response to a specified service or feature after processing the original request. (Customized function for <strong id="b1314371574090251"><a name="b1314371574090251"></a><a name="b1314371574090251"></a>bootstrap</strong>) </p>
</td>
</tr>
<tr id="row1567962255090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2067783248090251"><a name="p2067783248090251"></a><a name="p2067783248090251"></a><a href="samgr.md#ga21f168d6f97d6991115ae1cf8bbd8deb">SAMGR_GetInstance</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635963009090251"><a name="p1635963009090251"></a><a name="p1635963009090251"></a><a href="samgrlite.md">SamgrLite</a> * </p>
<p id="p432777252090251"><a name="p432777252090251"></a><a name="p432777252090251"></a>Obtains the singleton Samgr instance. </p>
</td>
</tr>
<tr id="row1269219194090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842163964090251"><a name="p842163964090251"></a><a name="p842163964090251"></a><a href="samgr.md#ga756ac1f5376c72aa5d14b855a302d7b6">SAMGR_Bootstrap</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p560445270090251"><a name="p560445270090251"></a><a name="p560445270090251"></a>void </p>
<p id="p1507353627090251"><a name="p1507353627090251"></a><a name="p1507353627090251"></a>Starts system services and features. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1619231329090251"></a>

## **Macro Definition Documentation**<a name="section715252145090251"></a>

## DEFAULT\_IUNKNOWN\_IMPL<a name="gac8d8c9671531f9340427153d50ca4a2b"></a>

```
#define DEFAULT_IUNKNOWN_IMPL
```

```
Values: .QueryInterface = [IUNKNOWN_QueryInterface](samgr.md#gac857d12648500c7dab1cb43e85ae2ed4), \

 .AddRef = [IUNKNOWN_AddRef](samgr.md#ga9abef49ec89bf913c3bed03faf478c1e), \

 .Release = [IUNKNOWN_Release](samgr.md#gabd462f8a5e6460a68760cd0719982296)


```

 **Description:**

Defines the default marco for initializing the  **[IUnknown](iunknown.md)**  interface. 

When creating a subclass object of the  **[IUnknown](iunknown.md)**  interface, you can use this macro to initialize members of the  **[IUnknown](iunknown.md)**  interface to their default values. 

## DEFAULT\_VERSION<a name="ga13dae059206df8d2d9b9b42e694b3f9c"></a>

```
#define DEFAULT_VERSION   0x20
```

 **Description:**

Defines the default  [IUnknown](iunknown.md)  version. You can customize the version. 

The  **[IUnknown](iunknown.md)**  interface of the default version can be called only in the current process. Inter-process communication is not supported. 

## GET\_IUNKNOWN<a name="ga9403f55c3f75fd03854dcd37c231e05b"></a>

```
#define GET_IUNKNOWN( T)   ([IUnknown](iunknown.md) *)(&((T).iUnknown))
```

 **Description:**

Obtains the pointer of the  **[IUnknown](iunknown.md)**  interface object from the subclass object T \(generic macro\) of the  **[IUnknown](iunknown.md)**  implementation class. 

Use this macro when registering  **[IUnknown](iunknown.md)**  interfaces with Samgr so that you can obtain the interfaces from the subclass objects of different  **[IUnknown](iunknown.md)**  implementation classes. 

## GET\_OFFSIZE<a name="gab094855efe05ae51eaaf3e0ddf0346cc"></a>

```
#define GET_OFFSIZE( T,  member )   (long)((char *)&(((T *)(0))->member))
```

 **Description:**

Calculates the offset of the member in the T type. 

**Parameters:**

<a name="table1756430419090251"></a>
<table><thead align="left"><tr id="row947316109090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1526311938090251"><a name="p1526311938090251"></a><a name="p1526311938090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p492333796090251"><a name="p492333796090251"></a><a name="p492333796090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row724526608090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">Indicates</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">the T type. </td>
</tr>
<tr id="row541021051090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the T member variable.</td>
</tr>
</tbody>
</table>

## INHERIT\_FEATURE<a name="ga63c2f681bde297cb28a9a300a462f3f4"></a>

```
#define INHERIT_FEATURE
```

```
Values: const char *(*GetName)([Feature](feature.md) *feature); \

 void (*OnInitialize)([Feature](feature.md) *feature, [Service](service.md) *parent, [Identity](identity.md) identity); \

 void (*OnStop)([Feature](feature.md) *feature, [Identity](identity.md) identity); \

 BOOL (*OnMessage)([Feature](feature.md) *feature, [Request](request.md) *request)


```

 **Description:**

Inherits from the macro of the feature class. 

This macro provides the capability of inheriting the feature lifecycle. 

## INHERIT\_IUNKNOWN<a name="gab74532a22d6993d0ffc014d36253397f"></a>

```
#define INHERIT_IUNKNOWN
```

```
Values: int (*QueryInterface)([IUnknown](iunknown.md) *iUnknown, int version, void **target); \

 int (*AddRef)([IUnknown](iunknown.md) *iUnknown); \

 int (*Release)([IUnknown](iunknown.md) *iUnknown)


```

 **Description:**

Defines the macro for inheriting the  **[IUnknown](iunknown.md)**  interface. 

When developing a subclass of the  **[IUnknown](iunknown.md)**  class, you can use this macro to inherit the structures of the  **[IUnknown](iunknown.md)**  interface. 

## INHERIT\_IUNKNOWNENTRY<a name="gad6324fd90dd636180efa2a59b377e65c"></a>

```
#define INHERIT_IUNKNOWNENTRY( T)
```

```
Values: uint16 ver; \

 int16 ref; \

 T iUnknown


```

 **Description:**

Defines the macro for inheriting the classes that implement the  **[IUnknown](iunknown.md)**  interface. 

When developing a subclass of a class that implements the  **[IUnknown](iunknown.md)**  interface, you can use this macro to inherit the structures of the  **[IUnknown](iunknown.md)**  implementation class. 

## INHERIT\_SERVICE<a name="gae9253a7fc1d0acbab91414b4cacc1d84"></a>

```
#define INHERIT_SERVICE
```

```
Values: const char *(*GetName)([Service](service.md) * service); \

 BOOL (*Initialize)([Service](service.md) * service, [Identity](identity.md) identity); \

 BOOL (*MessageHandle)([Service](service.md) * service, [Request](request.md) * request); \

 TaskConfig (*GetTaskConfig)([Service](service.md) * service)


```

 **Description:**

Indicates the macro used to inherit the members from the  **service**  class. 

This macro provides the capability of inheriting the lifecycle functions of the  **service**  class. You can use this macro to customize the service structure. 

## IUNKNOWN\_ENTRY\_BEGIN<a name="ga52ec6b5b03d56b0dfe7277785246bda1"></a>

```
#define IUNKNOWN_ENTRY_BEGIN( version)
```

```
Values: .ver = (version), \

 .ref = 1, \

 .iUnknown = { \

 DEFAULT_IUNKNOWN_IMPL


```

 **Description:**

Defines the macro for initializing the classes that implement the  **[IUnknown](iunknown.md)**  interface. 

When creating a subclass object of a class that implements the  **[IUnknown](iunknown.md)**  interface, you can use this macro to initialize members of the  **[IUnknown](iunknown.md)**  implementation class to their default values. You need to add the initialization of the customized member variable. 

## IUNKNOWN\_ENTRY\_END<a name="ga4ef734474ece49aa938d8ebd5b54bdb3"></a>

```
#define IUNKNOWN_ENTRY_END   }
```

 **Description:**

[IUnknown](iunknown.md)  Defines the end macro for initializing the  **[IUnknown](iunknown.md)**  implementation object. 

This macro is used when a subclass object of the  **[IUnknown](iunknown.md)**  implementation class is initialized. 

## **Typedef Documentation**<a name="section834860599090251"></a>

## BootMessage<a name="gadc486c8d2698eab8a9f26f0eb6cc63c8"></a>

```
typedef enum [BootMessage](samgr.md#gaf39e482610dca95f0dba85613755eb40) [BootMessage](samgr.md#gaf39e482610dca95f0dba85613755eb40)
```

 **Description:**

Enumerates the IDs of the message to be processed for starting the bootstrap service. 

This function is implemented by developers of the system service. Messages sent to the bootstrap service when Samgr is started. 

## Handler<a name="ga5e13d943cc6a87a5c99fe604f3bc01e4"></a>

```
typedef void(* Handler) (const [Request](request.md) *request, const [Response](response.md) *response)
```

 **Description:**

Handles asynchronous responses. 

This function will be used when a service or feature uses  [IUnknown](iunknown.md)  to send a request. If the caller is a feature, this function is used to handle the response that is sent after the feature processes a request. If the caller is a service,  **Handler**  will run in the service thread. 

## IUnknownEntry<a name="gacaa7db32a018a33a2bbf919cde8d8f9c"></a>

```
typedef struct [IUnknownEntry](iunknownentry.md) [IUnknownEntry](iunknownentry.md)
```

 **Description:**

Defines the  **[IUnknown](iunknown.md)**  implementation class. 

You need to inherit this structure when developing a subclass of the  **[IUnknown](iunknown.md)**  implementation class. Each  **[IUnknown](iunknown.md)**  interface must correspond to one or more  **[IUnknown](iunknown.md)**  implementation classes. 

## SamgrLite<a name="gaad729fe4f36b7b42a122349af334fb28"></a>

```
typedef struct [SamgrLite](samgrlite.md) [SamgrLite](samgrlite.md)
```

 **Description:**

Represents the system ability management class. 

This class is used for registering and discovering services, features, and functions. 

## SpecifyTag<a name="gae9c7eed07272a46851d61e646b6e86d5"></a>

```
typedef enum [SpecifyTag](samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0) [SpecifyTag](samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0)
```

 **Description:**

Specifies the tag for the task shared by multiple services. 

These enumerations are used for specifying a multi-service sharing task. 

## TaskPriority<a name="gaef69bbb3353ea484414c3bbaf8ec362b"></a>

```
typedef enum [TaskPriority](samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa) [TaskPriority](samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa)
```

 **Description:**

Enumerates task priority. 

These enumerations are used for configuring the task priority. The valid range of the priority is \(9, 39\). 

## TaskType<a name="gab265648f2dbef93878ad8c383712b43a"></a>

```
typedef enum [TaskType](samgr.md#ga026844c14ab62f42a2e19b54d622609b) [TaskType](samgr.md#ga026844c14ab62f42a2e19b54d622609b)
```

 **Description:**

Enumerates task types. 

These enumerations are used for configuring the task type. 

## Vector<a name="ga255ca81c214b8a94a90f786ceef94514"></a>

```
typedef struct [SimpleVector](simplevector.md) [Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514)
```

 **Description:**

Defines the simplified vector class, which is extended by four elements. 

This class is applicable to the C language development scenario where the data volume is small and dynamic expansion is required. 

## **Enumeration Type Documentation**<a name="section1672972997090251"></a>

## BootMessage<a name="gaf39e482610dca95f0dba85613755eb40"></a>

```
enum [BootMessage](samgr.md#gaf39e482610dca95f0dba85613755eb40)
```

 **Description:**

Enumerates the IDs of the message to be processed for starting the bootstrap service. 

This function is implemented by developers of the system service. Messages sent to the bootstrap service when Samgr is started. 

<a name="table348358584090251"></a>
<table><thead align="left"><tr id="row947724544090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p436492665090251"><a name="p436492665090251"></a><a name="p436492665090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p897636635090251"><a name="p897636635090251"></a><a name="p897636635090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2117310933090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7"><a name="ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7"></a><a name="ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7"></a></strong>BOOT_SYS_COMPLETED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1894481283090251"><a name="p1894481283090251"></a><a name="p1894481283090251"></a>Message indicating that the core system service is initialized </p>
 </td>
</tr>
<tr id="row836553795090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1"><a name="ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1"></a><a name="ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1"></a></strong>BOOT_APP_COMPLETED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232863397090251"><a name="p1232863397090251"></a><a name="p1232863397090251"></a>Message indicating that the system and application-layer services are initialized </p>
 </td>
</tr>
<tr id="row1247837705090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572"><a name="ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572"></a><a name="ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572"></a></strong>BOOT_REG_SERVICE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628140731090251"><a name="p1628140731090251"></a><a name="p1628140731090251"></a>Message indicating service registration during running </p>
 </td>
</tr>
<tr id="row1406519059090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec"><a name="ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec"></a><a name="ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec"></a></strong>BOOTSTRAP_BUTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p645293632090251"><a name="p645293632090251"></a><a name="p645293632090251"></a>Maximum number of message IDs </p>
 </td>
</tr>
</tbody>
</table>

## SpecifyTag<a name="ga704a59a45a705ef7a15d16e3cab8c1b0"></a>

```
enum [SpecifyTag](samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0)
```

 **Description:**

Specifies the tag for the task shared by multiple services. 

These enumerations are used for specifying a multi-service sharing task. 

<a name="table1915880318090251"></a>
<table><thead align="left"><tr id="row528105841090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1920091288090251"><a name="p1920091288090251"></a><a name="p1920091288090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1745238769090251"><a name="p1745238769090251"></a><a name="p1745238769090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row541115062090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955"></a></strong>LEVEL_HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734543630090251"><a name="p734543630090251"></a><a name="p734543630090251"></a>Preset tag </p>
 </td>
</tr>
<tr id="row656745566090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647"></a></strong>LEVEL_MIDDLE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310710628090251"><a name="p1310710628090251"></a><a name="p1310710628090251"></a>Preset tag </p>
 </td>
</tr>
<tr id="row1000984084090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5"></a></strong>LEVEL_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p60765292090251"><a name="p60765292090251"></a><a name="p60765292090251"></a>Preset tag </p>
 </td>
</tr>
<tr id="row994026916090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263"></a></strong>LEVEL_CUSTOM_BEGIN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85149525090251"><a name="p85149525090251"></a><a name="p85149525090251"></a>Customized tag </p>
 </td>
</tr>
</tbody>
</table>

## TaskPriority<a name="gaee057e5f06a7b2533e6f58bde34d15fa"></a>

```
enum [TaskPriority](samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa)
```

 **Description:**

Enumerates task priority. 

These enumerations are used for configuring the task priority. The valid range of the priority is \(9, 39\). 

<a name="table1154680132090251"></a>
<table><thead align="left"><tr id="row1316398369090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1187457994090251"><a name="p1187457994090251"></a><a name="p1187457994090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1252812569090251"><a name="p1252812569090251"></a><a name="p1252812569090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1771927474090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402"><a name="ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402"></a></strong>PRI_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p57230093090251"><a name="p57230093090251"></a><a name="p57230093090251"></a>Low-priority: (9, 15) </p>
 </td>
</tr>
<tr id="row1452179012090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258"><a name="ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258"></a></strong>PRI_BELOW_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338560472090251"><a name="p1338560472090251"></a><a name="p1338560472090251"></a>Lower than the normal priority: [16, 23) </p>
 </td>
</tr>
<tr id="row626429694090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063"><a name="ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063"></a></strong>PRI_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p668769884090251"><a name="p668769884090251"></a><a name="p668769884090251"></a>Normal priority: [24, 31). The log service is available. </p>
 </td>
</tr>
<tr id="row1867972967090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6"><a name="ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6"></a></strong>PRI_ABOVE_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p984415169090251"><a name="p984415169090251"></a><a name="p984415169090251"></a>Higher than the normal priority: [32, 39). The communication service is available. </p>
 </td>
</tr>
<tr id="row1326124243090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b"><a name="ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b"></a></strong>PRI_BUTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051676968090251"><a name="p2051676968090251"></a><a name="p2051676968090251"></a>Upper limit of the priority </p>
 </td>
</tr>
</tbody>
</table>

## TaskType<a name="ga026844c14ab62f42a2e19b54d622609b"></a>

```
enum [TaskType](samgr.md#ga026844c14ab62f42a2e19b54d622609b)
```

 **Description:**

Enumerates task types. 

These enumerations are used for configuring the task type. 

<a name="table148741816090251"></a>
<table><thead align="left"><tr id="row1685905641090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2025684354090251"><a name="p2025684354090251"></a><a name="p2025684354090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p977134890090251"><a name="p977134890090251"></a><a name="p977134890090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1826480641090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99"><a name="gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99"></a><a name="gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99"></a></strong>SHARED_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p136205250090251"><a name="p136205250090251"></a><a name="p136205250090251"></a>Tasks shared based on their priority by services </p>
 </td>
</tr>
<tr id="row268702970090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315"><a name="gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315"></a><a name="gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315"></a></strong>SINGLE_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1654484694090251"><a name="p1654484694090251"></a><a name="p1654484694090251"></a>Task exclusively occupied by a service </p>
 </td>
</tr>
<tr id="row859542571090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376"><a name="gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376"></a><a name="gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376"></a></strong>SPECIFIED_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140548709090251"><a name="p140548709090251"></a><a name="p140548709090251"></a>A specified task shared by multiple services </p>
 </td>
</tr>
<tr id="row1843825509090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11"><a name="gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11"></a><a name="gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11"></a></strong>NO_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p668010185090251"><a name="p668010185090251"></a><a name="p668010185090251"></a>No task for the service. Generally, this situation does not occur. </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1213665318090251"></a>

## IUNKNOWN\_AddRef\(\)<a name="ga9abef49ec89bf913c3bed03faf478c1e"></a>

```
int IUNKNOWN_AddRef ([IUnknown](iunknown.md) * iUnknown)
```

 **Description:**

Increments the reference count in this  **[IUnknown](iunknown.md)**  interface. 

This function is called in  **QueryInterface**. Do not call this function in the  **[IUnknown](iunknown.md)** interface. When the  **QueryInterface**  function is re-implemented, you need to call this function in the new  **QueryInterface**.****

****The system does not provide a lock to protect functions. Therefore, you need to re-implement functions if multiple developers are using them. ****

**Parameters:**

## IUNKNOWN\_QueryInterface\(\)<a name="gac857d12648500c7dab1cb43e85ae2ed4"></a>

```
int IUNKNOWN_QueryInterface ([IUnknown](iunknown.md) * iUnknown, int ver, void ** target )
```

 **Description:**

Queries the  **[IUnknown](iunknown.md)**  interfaces of a specified version \(downcasting\). 

After obtaining the  **[IUnknown](iunknown.md)**  interface object, the function caller uses  **QueryInterface**  to convert the object to the required subclass type. The system converts  [DEFAULT\_VERSION](samgr.md#ga13dae059206df8d2d9b9b42e694b3f9c)  into the subclass type required by the caller. If the type conversion requirements cannot be met, you need to re-implement this function. 

**Parameters:**

<a name="table742826877090251"></a>
<table><thead align="left"><tr id="row105581912090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p656629405090251"><a name="p656629405090251"></a><a name="p656629405090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p760583562090251"><a name="p760583562090251"></a><a name="p760583562090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row822542141090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b769189289090251"><a name="b769189289090251"></a><a name="b769189289090251"></a><a href="iunknown.md">IUnknown</a></strong> interface. </td>
</tr>
<tr id="row1669303117090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">version</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the version of the <strong id="b1862338958090251"><a name="b1862338958090251"></a><a name="b1862338958090251"></a><a href="iunknown.md">IUnknown</a></strong> interface object to be converted. </td>
</tr>
<tr id="row1631904826090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">target</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1615838590090251"><a name="b1615838590090251"></a><a name="b1615838590090251"></a><a href="iunknown.md">IUnknown</a></strong> subclass type required by the caller. This is an output parameter. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the conversion is successful; returns other error codes if the conversion fails.



## IUNKNOWN\_Release\(\)<a name="gabd462f8a5e6460a68760cd0719982296"></a>

```
int IUNKNOWN_Release ([IUnknown](iunknown.md) * iUnknown)
```

 **Description:**

Releases a reference to an  **[IUnknown](iunknown.md)**  interface that is no longer used. 

In the default implementation provided by the system, if the reference count is  **0**, the memory of the  **[IUnknown](iunknown.md)**  interface object and implementation object is not released. If the memory of the  **[IUnknown](iunknown.md)**  interface object and implementation object is dynamically allocated, this function needs to be re-implemented. If the reference count is  **0**, the memory of the  **[IUnknown](iunknown.md)**  interface object and implementation object is released. 

**Parameters:**

<a name="table703196136090251"></a>
<table><thead align="left"><tr id="row1252968894090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1962261185090251"><a name="p1962261185090251"></a><a name="p1962261185090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p492350853090251"><a name="p492350853090251"></a><a name="p492350853090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row112491798090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1925610403090251"><a name="b1925610403090251"></a><a name="b1925610403090251"></a><a href="iunknown.md">IUnknown</a><strong id="b1042498741090251"><a name="b1042498741090251"></a><a name="b1042498741090251"></a> interface object. </strong></strong></td>
</tr>
</tbody>
</table>

**Returns:**

**** Indicates the number of  **[IUnknown](iunknown.md)** interface objects that are referenced after the current reference is released.******** 

## SAMGR\_Bootstrap\(\)<a name="ga756ac1f5376c72aa5d14b855a302d7b6"></a>

```
void SAMGR_Bootstrap (void )
```

 **Description:**

Starts system services and features. 

This function is called in the  **main**  function to start all services when an independent process is developed. This function is called after the dynamic library \(containing system services and features\) is loaded during system running. 

**Attention:**

This function cannot be called frequently. Otherwise, problems such as repeated service startup may occur. It is recommended that this function be called once in the  **main**  function or after the dynamic library is loaded. 



## SAMGR\_GetInstance\(\)<a name="ga21f168d6f97d6991115ae1cf8bbd8deb"></a>

```
[SamgrLite](samgrlite.md)* SAMGR_GetInstance (void )
```

 **Description:**

Obtains the singleton Samgr instance. 

You need to call this function before using the Samgr capabilities. 

**Returns:**

Returns the pointer to the singleton instance  [SamgrLite](samgrlite.md). 



## SAMGR\_SendRequest\(\)<a name="ga03b440d8dff9fcc8694ca8a3baa83462"></a>

```
int32 SAMGR_SendRequest (const [Identity](identity.md) * identity, const [Request](request.md) * request, [Handler](samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4) handler )
```

 **Description:**

Sends a request to a service or feature of a specified identity. 

This function is called by a service to send messages to its own features through the asynchronous function of  [IUnknown](iunknown.md). 

**Parameters:**

<a name="table1489386047090251"></a>
<table><thead align="left"><tr id="row351040454090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p670008735090251"><a name="p670008735090251"></a><a name="p670008735090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p995961987090251"><a name="p995961987090251"></a><a name="p995961987090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1052999698090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the ID of the feature or service that processes the message. </td>
</tr>
<tr id="row994889845090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request. </td>
</tr>
<tr id="row1485365702090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function handling the response. If the value is <strong id="b1772255131090251"><a name="b1772255131090251"></a><a name="b1772255131090251"></a>NULL</strong>, no response is required. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the request is sent successfully; returns other error codes if the request fails to be sent. The caller needs to release the memory applied in the request. 



## SAMGR\_SendResponse\(\)<a name="gadba5f2881a6e1403cb642726d5fec3e2"></a>

```
int32 SAMGR_SendResponse (const [Request](request.md) * request, const [Response](response.md) * response )
```

 **Description:**

Sends a response after processing a request. 

This function is called to send a response after processing a request by  **MessageHandle**  of a service or  **OnMessage**  of a feature. 

**Parameters:**

<a name="table1754027874090251"></a>
<table><thead align="left"><tr id="row1810582354090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1844917566090251"><a name="p1844917566090251"></a><a name="p1844917566090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p350331469090251"><a name="p350331469090251"></a><a name="p350331469090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1921776010090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original request. </td>
</tr>
<tr id="row1722084287090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">response</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the response content. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the response is sent successfully; returns other error codes if the response fails to be sent. 

**Attention:**

-    This function can be called only in  **MessageHandle**  or  **OnMessage**. 
-    The request must be the original one passed from  **MessageHandle**  or  **OnMessage**. Otherwise, a memory exception occurs. 
-    When the caller sends a request, the  **handler**  callback function must be carried. 
-    The response is sent to the message queue of the service to which the requester belongs for processing. Therefore, the requester should wait for the response in non-blocking mode. 

## SAMGR\_SendResponseByIdentity\(\)<a name="ga44ab9b4c98e2dd6ba3338d1d2664a6fe"></a>

```
int32 SAMGR_SendResponseByIdentity (const [Identity](identity.md) * id, const [Request](request.md) * request, const [Response](response.md) * response )
```

 **Description:**

Sends a response to a specified service or feature after processing the original request. \(Customized function for  **bootstrap**\) 

This function is called to send a response after processing a request by  **MessageHandle**  of a service or  **OnMessage**  of a feature. This function can be customized to implement phased startup of different types of services. 

**Parameters:**

<a name="table2056350964090251"></a>
<table><thead align="left"><tr id="row485641331090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p507306099090251"><a name="p507306099090251"></a><a name="p507306099090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p10525329090251"><a name="p10525329090251"></a><a name="p10525329090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row220904329090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the ID of a service or feature. The response is sent to the thread of the service or feature for processing. </td>
</tr>
<tr id="row450921479090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original request. </td>
</tr>
<tr id="row715689479090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">response</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the response content. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the response is sent successfully; returns other error codes if the response fails to be sent. 

**Attention:**

-    This function can be called only in  **MessageHandle**  or  **OnMessage**. 
-    The request must be the original one passed from  **MessageHandle**  or  **OnMessage**. Otherwise, a memory exception occurs. 
-    When the caller sends a request, the  **handler**  callback function must be carried. 
-    The response is sent to the message queue of a specified ID for processing. Therefore, wait for the response in non-blocking mode. 

## SAMGR\_SendSharedDirectRequest\(\)<a name="ga0c8c20d2265f4eb8ec8b516300a94a63"></a>

```
int32 SAMGR_SendSharedDirectRequest (const [Identity](identity.md) * id, const [Request](request.md) * req, const [Response](response.md) * resp, uint32 ** ref, [Handler](samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4) handler )
```

 **Description:**

Sends a request and response of a caller to the feature thread. The handler is directly called to process the request and response without using the message processing functions. \(Customized function for the broadcast service\) 

This function is used to publish topics for the  [Broadcast](broadcast.md)  service to broadcast messages. The value of reference counting is incremented by one each time this function is called. 

**Parameters:**

<a name="table963096795090251"></a>
<table><thead align="left"><tr id="row751329307090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1794574380090251"><a name="p1794574380090251"></a><a name="p1794574380090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1337534818090251"><a name="p1337534818090251"></a><a name="p1337534818090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1229926829090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the IDs of services or features, to which the request and response are sent. </td>
</tr>
<tr id="row1264721591090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request. </td>
</tr>
<tr id="row2147327729090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">resp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the response. </td>
</tr>
<tr id="row1548932120090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ref</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the reference counting. </td>
</tr>
<tr id="row790427849090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function for handling the request and response. This parameter cannot be <strong id="b1756474801090251"><a name="b1756474801090251"></a><a name="b1756474801090251"></a>NULL</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the request and response are sent successfully; returns other error codes if the request and response fail to be sent. 

**Attention:**

-    Ensure that the thread specified by  **identity**  processes the message after all messages are sent. Common practice: Add a lock before sending a request and add the same lock during processing. 
-    If  **NULL**  is returned, the caller needs to release the memory of the request and response. 
-    If the response changes each time when a request is sent, ensure that the response will not be released. \(Set  **len**  to  **0**, the  **data**  of response will be the resident memory.\) 

## SAMGR\_SendSharedRequest\(\)<a name="gae7c4d087b251949d10d81e88a47e8dbd"></a>

```
uint32* SAMGR_SendSharedRequest (const [Identity](identity.md) * identity, const [Request](request.md) * request, uint32 * token, [Handler](samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4) handler )
```

 **Description:**

Sends a request to multiple services or features to save memory. 

This function is used to publish topics for the  [Broadcast](broadcast.md)  service to broadcast messages. 

**Parameters:**

<a name="table2113480396090251"></a>
<table><thead align="left"><tr id="row647618199090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1746216097090251"><a name="p1746216097090251"></a><a name="p1746216097090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p163918959090251"><a name="p163918959090251"></a><a name="p163918959090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row145796023090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the IDs of services or features, to which requests are sent. </td>
</tr>
<tr id="row1068314224090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request. </td>
</tr>
<tr id="row1482008274090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">token</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to reference counting. </td>
</tr>
<tr id="row1769501324090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function handling the response. If the value is <strong id="b1381900031090251"><a name="b1381900031090251"></a><a name="b1381900031090251"></a>NULL</strong>, no response is required. </td>
</tr>
</tbody>
</table>

**Attention:**

-    Ensure that the thread specified by  **identity**  processes the message after all messages are sent. Common practice: Add a lock before sending a request and add the same lock during processing. 
-    If  **NULL**  is returned, the caller needs to release the memory of the request. 

## VECTOR\_Add\(\)<a name="ga234ba2452c973e9fa4a8be47eaea9d06"></a>

```
int16 VECTOR_Add ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector, void * element )
```

 **Description:**

Adds an element to the vector. 

This function is used to add an element to the vector. 

**Parameters:**

<a name="table1354561184090251"></a>
<table><thead align="left"><tr id="row1593595227090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p62292398090251"><a name="p62292398090251"></a><a name="p62292398090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2074663425090251"><a name="p2074663425090251"></a><a name="p2074663425090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row639986577090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1180583133090251"><a name="b1180583133090251"></a><a name="b1180583133090251"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row846073089090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the element to add. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the location of the element to be added if the operation is successful; returns  **INVALID\_INDEX**  if the operation fails. 



## VECTOR\_At\(\)<a name="ga75210ba0bd37a38a1902c4904e61246a"></a>

```
void* VECTOR_At ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector, int16 index )
```

 **Description:**

Obtains the element at a specified position. 

This function is used to obtain the element at a specified position.

**Parameters:**

<a name="table2013301416090251"></a>
<table><thead align="left"><tr id="row1530484190090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1133547827090251"><a name="p1133547827090251"></a><a name="p1133547827090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1874236448090251"><a name="p1874236448090251"></a><a name="p1874236448090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row144984992090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b116586379090251"><a name="b116586379090251"></a><a name="b116586379090251"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row315879884090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the subscript to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the element if obtained; returns  **NULL**  otherwise. 



## VECTOR\_Clear\(\)<a name="gaebfe9ac38f2667d61bf39420aa8e7035"></a>

```
void VECTOR_Clear ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector)
```

 **Description:**

Destruct a vector object. 

This function is used to clear the memory applied by the vector after the temporary vector in the stack is used. 

**Parameters:**

<a name="table1185242614090251"></a>
<table><thead align="left"><tr id="row1444891260090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2136077429090251"><a name="p2136077429090251"></a><a name="p2136077429090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p319605303090251"><a name="p319605303090251"></a><a name="p319605303090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1209698915090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the vector to clear. </td>
</tr>
</tbody>
</table>

## VECTOR\_Find\(\)<a name="gaabc5b0eda1ee6889411e6dacb233cb07"></a>

```
int16 VECTOR_Find ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector, const void * element )
```

 **Description:**

Checks the position of an element. 

This function is used to check whether a vector has a specified element. 

**Parameters:**

<a name="table231611146090251"></a>
<table><thead align="left"><tr id="row977784952090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1650996307090251"><a name="p1650996307090251"></a><a name="p1650996307090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p238311038090251"><a name="p238311038090251"></a><a name="p238311038090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row804768399090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1132940730090251"><a name="b1132940730090251"></a><a name="b1132940730090251"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row2097072755090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the element to be checked. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the index of the element that is not less than 0 if the check is successful; returns  **INVALID\_INDEX**  if the check fails. 



## VECTOR\_FindByKey\(\)<a name="gac65bc6dc959a90d95dff93368abd97c7"></a>

```
int16 VECTOR_FindByKey ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector, const void * key )
```

 **Description:**

Checks the position of the element with a specified key. 

This function is used to check an element based on its key value. 

**Parameters:**

<a name="table296072994090251"></a>
<table><thead align="left"><tr id="row1483315555090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1854922059090251"><a name="p1854922059090251"></a><a name="p1854922059090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p722939948090251"><a name="p722939948090251"></a><a name="p722939948090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row510079002090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1054809783090251"><a name="b1054809783090251"></a><a name="b1054809783090251"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row1070626273090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the key value of the element to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the index of the key element that is not less than 0 if the check is successful; returns  **INVALID\_INDEX**  if the check fails. 



## VECTOR\_Make\(\)<a name="gae790345f8a2863c143bfee4bab3fb6d7"></a>

```
[Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) VECTOR_Make (VECTOR_Key key, VECTOR_Compare compare )
```

 **Description:**

Creates or initializes a vector object. 

This function is used to create or initialize a vector object. 

**Parameters:**

<a name="table388428710090251"></a>
<table><thead align="left"><tr id="row1825551265090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p789711233090251"><a name="p789711233090251"></a><a name="p789711233090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1153175451090251"><a name="p1153175451090251"></a><a name="p1153175451090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1976615794090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the function provided by users for converting data elements into key values. If this function is not provided, set it to <strong id="b2139304868090251"><a name="b2139304868090251"></a><a name="b2139304868090251"></a>NULL</strong>. </td>
</tr>
<tr id="row1864757177090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">compare</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the function for comparing the sizes of two elements. If this function is not provided, set it to <strong id="b1705212463090251"><a name="b1705212463090251"></a><a name="b1705212463090251"></a>NULL</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the vector right value object. 



## VECTOR\_Num\(\)<a name="ga90523bfd48091a0135f74670076af4d5"></a>

```
int16 VECTOR_Num ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector)
```

 **Description:**

Obtains the number of valid elements in the vector, excluding elements that have been set to  **NULL**. 

This function is used to check whether the number of elements reaches the upper limit. 

**Parameters:**

<a name="table1930590146090251"></a>
<table><thead align="left"><tr id="row58039475090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1874895703090251"><a name="p1874895703090251"></a><a name="p1874895703090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p126619804090251"><a name="p126619804090251"></a><a name="p126619804090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1053391398090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b829310144090251"><a name="b829310144090251"></a><a name="b829310144090251"></a>this</strong> pointer to the vector. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the top - free value of the vector, which indicates the number of non-null elements. 



## VECTOR\_Size\(\)<a name="ga1432f30c136d14bc00414d883d8be3bd"></a>

```
int16 VECTOR_Size ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector)
```

 **Description:**

Obtains the number of elements in the vector, including elements that have been set to  **NULL**. 

This function is used for full traversal. 

**Parameters:**

<a name="table1627158409090251"></a>
<table><thead align="left"><tr id="row1902226744090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1161063466090251"><a name="p1161063466090251"></a><a name="p1161063466090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p306757255090251"><a name="p306757255090251"></a><a name="p306757255090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row736962300090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b2011326778090251"><a name="b2011326778090251"></a><a name="b2011326778090251"></a>this</strong> pointer to the vector. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the top value of the vector, which indicates the number of elements. 



## VECTOR\_Swap\(\)<a name="ga7f435d33ba61d145de9d5892b68a0eda"></a>

```
void* VECTOR_Swap ([Vector](samgr.md#ga255ca81c214b8a94a90f786ceef94514) * vector, int16 index, void * element )
```

 **Description:**

Swaps the element at a specified position in a vector with another element. 

This function is used to clear, sort, or update elements in the vector. 

**Parameters:**

<a name="table1527830940090251"></a>
<table><thead align="left"><tr id="row1641012864090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1300222266090251"><a name="p1300222266090251"></a><a name="p1300222266090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1392510338090251"><a name="p1392510338090251"></a><a name="p1392510338090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1485720599090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1449520728090251"><a name="b1449520728090251"></a><a name="b1449520728090251"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row1928563881090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the position of the element to be swapped. </td>
</tr>
<tr id="row1006347094090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the new element. </td>
</tr>
</tbody>
</table>

**Attention:**

Before using this function, ensure that the index is valid. You can use  **VECTOR\_Size**  to obtain the upper limit of the index. 

**Returns:**

Returns the original element if the swapping is successful; returns  **NULL**  if the swapping fails. 

**See also:**

[VECTOR\_Size](samgr.md#ga1432f30c136d14bc00414d883d8be3bd) 

