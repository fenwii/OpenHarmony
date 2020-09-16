# Samgr<a name="EN-US_TOPIC_0000001055078091"></a>

## **Overview**<a name="section572910077084827"></a>

Manages system capabilities. 

This module provides the development framework base of the service-oriented architecture \(SOA\). You can develop your own abilities based on the Samgr development framework. This module provides basic models of services, features, and functions, and registration and discovery capabilities. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1366250632084827"></a>

## Files<a name="files"></a>

<a name="table1672293128084827"></a>
<table><thead align="left"><tr id="row1087012152084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p84099068084827"><a name="p84099068084827"></a><a name="p84099068084827"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1837641440084827"><a name="p1837641440084827"></a><a name="p1837641440084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1713691753084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2066576351084827"><a name="p2066576351084827"></a><a name="p2066576351084827"></a><a href="common-h.md">common.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p314736075084827"><a name="p314736075084827"></a><a name="p314736075084827"></a>Provides common objects and functions for Samgr and external modules. </p>
</td>
</tr>
<tr id="row1754271254084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643812094084827"><a name="p1643812094084827"></a><a name="p1643812094084827"></a><a href="feature-h.md">feature.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p433535044084827"><a name="p433535044084827"></a><a name="p433535044084827"></a>Defines the base class of a feature. </p>
</td>
</tr>
<tr id="row865625999084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197777375084827"><a name="p1197777375084827"></a><a name="p1197777375084827"></a><a href="iunknown-h.md">iunknown.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p975947673084827"><a name="p975947673084827"></a><a name="p975947673084827"></a>Provides the base class and default implementation for external functions of system capabilities. </p>
</td>
</tr>
<tr id="row1874096405084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1289428444084827"><a name="p1289428444084827"></a><a name="p1289428444084827"></a><a href="message-h.md">message.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268754356084827"><a name="p268754356084827"></a><a name="p268754356084827"></a>Provides message communication APIs that help you to implement asynchronous functions of <a href="iunknown.md">IUnknown</a>. </p>
</td>
</tr>
<tr id="row1625120694084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149759562084827"><a name="p1149759562084827"></a><a name="p1149759562084827"></a><a href="samgr_lite-h.md">samgr_lite.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p489325550084827"><a name="p489325550084827"></a><a name="p489325550084827"></a>Manages system capabilities. </p>
</td>
</tr>
<tr id="row1096435911084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1331908262084827"><a name="p1331908262084827"></a><a name="p1331908262084827"></a><a href="service-h.md">service.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1585358557084827"><a name="p1585358557084827"></a><a name="p1585358557084827"></a>Provides basic types and constants of services. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table887845045084827"></a>
<table><thead align="left"><tr id="row1698546300084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1745980117084827"><a name="p1745980117084827"></a><a name="p1745980117084827"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2048833202084827"><a name="p2048833202084827"></a><a name="p2048833202084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1023732016084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116587178084827"><a name="p1116587178084827"></a><a name="p1116587178084827"></a><a href="simplevector.md">SimpleVector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p153640798084827"><a name="p153640798084827"></a><a name="p153640798084827"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
<tr id="row711993890084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p666731011084827"><a name="p666731011084827"></a><a name="p666731011084827"></a><a href="feature.md">Feature</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884737924084827"><a name="p1884737924084827"></a><a name="p1884737924084827"></a>Defines the base class of a feature. </p>
</td>
</tr>
<tr id="row195347723084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1908407212084827"><a name="p1908407212084827"></a><a name="p1908407212084827"></a><a href="iunknown.md">IUnknown</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p866110407084827"><a name="p866110407084827"></a><a name="p866110407084827"></a>Defines the <strong id="b380542748084827"><a name="b380542748084827"></a><a name="b380542748084827"></a><a href="iunknown.md">IUnknown</a></strong> class. </p>
</td>
</tr>
<tr id="row988905304084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p376570300084827"><a name="p376570300084827"></a><a name="p376570300084827"></a><a href="iunknownentry.md">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995337922084827"><a name="p1995337922084827"></a><a name="p1995337922084827"></a>Defines the <strong id="b309535095084827"><a name="b309535095084827"></a><a name="b309535095084827"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
<tr id="row683501105084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1168452740084827"><a name="p1168452740084827"></a><a name="p1168452740084827"></a><a href="identity.md">Identity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262697980084827"><a name="p262697980084827"></a><a name="p262697980084827"></a>Identifies a service and feature. </p>
</td>
</tr>
<tr id="row928744412084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p905685358084827"><a name="p905685358084827"></a><a name="p905685358084827"></a><a href="request.md">Request</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1479556180084827"><a name="p1479556180084827"></a><a name="p1479556180084827"></a>Defines a request. </p>
</td>
</tr>
<tr id="row1108606448084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1771956533084827"><a name="p1771956533084827"></a><a name="p1771956533084827"></a><a href="response.md">Response</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115748867084827"><a name="p115748867084827"></a><a name="p115748867084827"></a>Defines a response. </p>
</td>
</tr>
<tr id="row1463987609084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1160332745084827"><a name="p1160332745084827"></a><a name="p1160332745084827"></a><a href="samgrlite.md">SamgrLite</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829381634084827"><a name="p829381634084827"></a><a name="p829381634084827"></a>Represents the system ability management class. </p>
</td>
</tr>
<tr id="row288517771084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587397443084827"><a name="p1587397443084827"></a><a name="p1587397443084827"></a><a href="taskconfig.md">TaskConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1407148805084827"><a name="p1407148805084827"></a><a name="p1407148805084827"></a>Defines task configurations for a service. </p>
</td>
</tr>
<tr id="row1921229624084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2017029999084827"><a name="p2017029999084827"></a><a name="p2017029999084827"></a><a href="service.md">Service</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967484135084827"><a name="p967484135084827"></a><a name="p967484135084827"></a>Indicates the basic type of a service. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1039410683084827"></a>
<table><thead align="left"><tr id="row192672235084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p627420659084827"><a name="p627420659084827"></a><a name="p627420659084827"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p509104918084827"><a name="p509104918084827"></a><a name="p509104918084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1082939270084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509390940084827"><a name="p1509390940084827"></a><a name="p1509390940084827"></a><a href="samgr.md#gab094855efe05ae51eaaf3e0ddf0346cc">GET_OFFSIZE</a>(T, member)   (long)((char *)&amp;(((T *)(0))-&gt;member))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1684394854084827"><a name="p1684394854084827"></a><a name="p1684394854084827"></a>Calculates the offset of the member in the T type. </p>
</td>
</tr>
<tr id="row95827344084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092111564084827"><a name="p2092111564084827"></a><a name="p2092111564084827"></a><a href="samgr.md#ga63c2f681bde297cb28a9a300a462f3f4">INHERIT_FEATURE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106908795084827"><a name="p106908795084827"></a><a name="p106908795084827"></a>Inherits from the macro of the feature class. </p>
</td>
</tr>
<tr id="row1200693528084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p685816324084827"><a name="p685816324084827"></a><a name="p685816324084827"></a><a href="samgr.md#ga13dae059206df8d2d9b9b42e694b3f9c">DEFAULT_VERSION</a>   0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1600697705084827"><a name="p1600697705084827"></a><a name="p1600697705084827"></a>Defines the default <a href="iunknown.md">IUnknown</a> version. You can customize the version. </p>
</td>
</tr>
<tr id="row909047461084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662386054084827"><a name="p1662386054084827"></a><a name="p1662386054084827"></a><a href="samgr.md#gab74532a22d6993d0ffc014d36253397f">INHERIT_IUNKNOWN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1098342477084827"><a name="p1098342477084827"></a><a name="p1098342477084827"></a>Defines the macro for inheriting the <strong id="b1386993140084827"><a name="b1386993140084827"></a><a name="b1386993140084827"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1145592201084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1172399949084827"><a name="p1172399949084827"></a><a name="p1172399949084827"></a><a href="samgr.md#gad6324fd90dd636180efa2a59b377e65c">INHERIT_IUNKNOWNENTRY</a>(T)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1117728441084827"><a name="p1117728441084827"></a><a name="p1117728441084827"></a>Defines the macro for inheriting the classes that implement the <strong id="b2032140070084827"><a name="b2032140070084827"></a><a name="b2032140070084827"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1454447143084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1703528301084827"><a name="p1703528301084827"></a><a name="p1703528301084827"></a><a href="samgr.md#gac8d8c9671531f9340427153d50ca4a2b">DEFAULT_IUNKNOWN_IMPL</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p557254105084827"><a name="p557254105084827"></a><a name="p557254105084827"></a>Defines the default marco for initializing the <strong id="b227130028084827"><a name="b227130028084827"></a><a name="b227130028084827"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1588891837084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1107047548084827"><a name="p1107047548084827"></a><a name="p1107047548084827"></a><a href="samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1">IUNKNOWN_ENTRY_BEGIN</a>(version)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p973308134084827"><a name="p973308134084827"></a><a name="p973308134084827"></a>Defines the macro for initializing the classes that implement the <strong id="b1936589574084827"><a name="b1936589574084827"></a><a name="b1936589574084827"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row549404123084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331862266084827"><a name="p331862266084827"></a><a name="p331862266084827"></a><a href="samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3">IUNKNOWN_ENTRY_END</a>   }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p947806832084827"><a name="p947806832084827"></a><a name="p947806832084827"></a><a href="iunknown.md">IUnknown</a> Defines the end macro for initializing the <strong id="b40740204084827"><a name="b40740204084827"></a><a name="b40740204084827"></a><a href="iunknown.md">IUnknown</a></strong> implementation object. </p>
</td>
</tr>
<tr id="row998359490084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102108245084827"><a name="p1102108245084827"></a><a name="p1102108245084827"></a><a href="samgr.md#ga9403f55c3f75fd03854dcd37c231e05b">GET_IUNKNOWN</a>(T)   (<a href="iunknown.md">IUnknown</a> *)(&amp;((T).iUnknown))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p401512978084827"><a name="p401512978084827"></a><a name="p401512978084827"></a>Obtains the pointer of the <strong id="b1096249600084827"><a name="b1096249600084827"></a><a name="b1096249600084827"></a><a href="iunknown.md">IUnknown</a></strong> interface object from the subclass object T (generic macro) of the <strong id="b1775489521084827"><a name="b1775489521084827"></a><a name="b1775489521084827"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
<tr id="row882611732084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1519401640084827"><a name="p1519401640084827"></a><a name="p1519401640084827"></a><em id="gadc00f0568236d4538c867ed7194d8960"><a name="gadc00f0568236d4538c867ed7194d8960"></a><a name="gadc00f0568236d4538c867ed7194d8960"></a></em>BOOTSTRAP_SERVICE    "Bootstrap"</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012846381084827"><a name="p1012846381084827"></a><a name="p1012846381084827"></a>Starts a bootstrap service, which is used by samgr and implemented by system service developers. </p>
</td>
</tr>
<tr id="row1285116967084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1723087974084827"><a name="p1723087974084827"></a><a name="p1723087974084827"></a><a href="samgr.md#gae9253a7fc1d0acbab91414b4cacc1d84">INHERIT_SERVICE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p65663916084827"><a name="p65663916084827"></a><a name="p65663916084827"></a>Indicates the macro used to inherit the members from the <strong id="b2007131320084827"><a name="b2007131320084827"></a><a name="b2007131320084827"></a>service</strong> class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table663162190084827"></a>
<table><thead align="left"><tr id="row2029678779084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p216805329084827"><a name="p216805329084827"></a><a name="p216805329084827"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1354420624084827"><a name="p1354420624084827"></a><a name="p1354420624084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row817170725084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p614836901084827"><a name="p614836901084827"></a><a name="p614836901084827"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327587993084827"><a name="p327587993084827"></a><a name="p327587993084827"></a>typedef struct <a href="simplevector.md">SimpleVector</a> </p>
<p id="p1991510650084827"><a name="p1991510650084827"></a><a name="p1991510650084827"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
<tr id="row965708970084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1610578805084827"><a name="p1610578805084827"></a><a name="p1610578805084827"></a><a href="samgr.md#gacaa7db32a018a33a2bbf919cde8d8f9c">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359905373084827"><a name="p359905373084827"></a><a name="p359905373084827"></a>typedef struct <a href="iunknownentry.md">IUnknownEntry</a> </p>
<p id="p675232559084827"><a name="p675232559084827"></a><a name="p675232559084827"></a>Defines the <strong id="b829967816084827"><a name="b829967816084827"></a><a name="b829967816084827"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
<tr id="row1564921056084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p823341877084827"><a name="p823341877084827"></a><a name="p823341877084827"></a><a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a>) (const <a href="request.md">Request</a> *request, const <a href="response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415707742084827"><a name="p415707742084827"></a><a name="p415707742084827"></a>typedef void(* </p>
<p id="p1306959744084827"><a name="p1306959744084827"></a><a name="p1306959744084827"></a>Handles asynchronous responses. </p>
</td>
</tr>
<tr id="row22309771084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p828594437084827"><a name="p828594437084827"></a><a name="p828594437084827"></a><a href="samgr.md#gadc486c8d2698eab8a9f26f0eb6cc63c8">BootMessage</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1374165009084827"><a name="p1374165009084827"></a><a name="p1374165009084827"></a>typedef enum <a href="samgr.md#gaf39e482610dca95f0dba85613755eb40">BootMessage</a> </p>
<p id="p1555042967084827"><a name="p1555042967084827"></a><a name="p1555042967084827"></a>Enumerates the IDs of the message to be processed for starting the bootstrap service. </p>
</td>
</tr>
<tr id="row211431122084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793721045084827"><a name="p793721045084827"></a><a name="p793721045084827"></a><a href="samgr.md#gaad729fe4f36b7b42a122349af334fb28">SamgrLite</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p77118183084827"><a name="p77118183084827"></a><a name="p77118183084827"></a>typedef struct <a href="samgrlite.md">SamgrLite</a> </p>
<p id="p1551632355084827"><a name="p1551632355084827"></a><a name="p1551632355084827"></a>Represents the system ability management class. </p>
</td>
</tr>
<tr id="row135554709084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1630992824084827"><a name="p1630992824084827"></a><a name="p1630992824084827"></a><a href="samgr.md#gab265648f2dbef93878ad8c383712b43a">TaskType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481027735084827"><a name="p1481027735084827"></a><a name="p1481027735084827"></a>typedef enum <a href="samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a> </p>
<p id="p1291725831084827"><a name="p1291725831084827"></a><a name="p1291725831084827"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row525531971084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973646178084827"><a name="p973646178084827"></a><a name="p973646178084827"></a><a href="samgr.md#gae9c7eed07272a46851d61e646b6e86d5">SpecifyTag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435278756084827"><a name="p1435278756084827"></a><a name="p1435278756084827"></a>typedef enum <a href="samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a> </p>
<p id="p632009839084827"><a name="p632009839084827"></a><a name="p632009839084827"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row1212975967084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p5705428084827"><a name="p5705428084827"></a><a name="p5705428084827"></a><a href="samgr.md#gaef69bbb3353ea484414c3bbaf8ec362b">TaskPriority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p605663935084827"><a name="p605663935084827"></a><a name="p605663935084827"></a>typedef enum <a href="samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a> </p>
<p id="p1342982091084827"><a name="p1342982091084827"></a><a name="p1342982091084827"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1267317887084827"></a>
<table><thead align="left"><tr id="row1153572712084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p723242208084827"><a name="p723242208084827"></a><a name="p723242208084827"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1757239055084827"><a name="p1757239055084827"></a><a name="p1757239055084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row572077164084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440476002084827"><a name="p440476002084827"></a><a name="p440476002084827"></a><a href="samgr.md#gaf39e482610dca95f0dba85613755eb40">BootMessage</a> { <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7">BOOT_SYS_COMPLETED</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1">BOOT_APP_COMPLETED</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572">BOOT_REG_SERVICE</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec">BOOTSTRAP_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611276245084827"><a name="p611276245084827"></a><a name="p611276245084827"></a>Enumerates the IDs of the message to be processed for starting the bootstrap service. </p>
</td>
</tr>
<tr id="row2140007566084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1746629423084827"><a name="p1746629423084827"></a><a name="p1746629423084827"></a><a href="samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a> { <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99">SHARED_TASK</a> = 0, <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315">SINGLE_TASK</a> = 1, <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376">SPECIFIED_TASK</a> = 2, <a href="samgr.md#gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11">NO_TASK</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p797541715084827"><a name="p797541715084827"></a><a name="p797541715084827"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row1670420171084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1238013101084827"><a name="p1238013101084827"></a><a name="p1238013101084827"></a><a href="samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a> { <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955">LEVEL_HIGH</a> = 0, <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647">LEVEL_MIDDLE</a> = 1, <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5">LEVEL_LOW</a> = 2, <a href="samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263">LEVEL_CUSTOM_BEGIN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021770324084827"><a name="p1021770324084827"></a><a name="p1021770324084827"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row1507141821084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p563076420084827"><a name="p563076420084827"></a><a name="p563076420084827"></a><a href="samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a> {   <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402">PRI_LOW</a> = 9, <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258">PRI_BELOW_NORMAL</a> = 16, <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063">PRI_NORMAL</a> = 24, <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6">PRI_ABOVE_NORMAL</a> = 32,   <a href="samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b">PRI_BUTT</a> = 39 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452331322084827"><a name="p1452331322084827"></a><a name="p1452331322084827"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table552675195084827"></a>
<table><thead align="left"><tr id="row1439862156084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p854183053084827"><a name="p854183053084827"></a><a name="p854183053084827"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2023589296084827"><a name="p2023589296084827"></a><a name="p2023589296084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1061272160084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1257512488084827"><a name="p1257512488084827"></a><a name="p1257512488084827"></a><a href="samgr.md#gae790345f8a2863c143bfee4bab3fb6d7">VECTOR_Make</a> (VECTOR_Key key, VECTOR_Compare compare)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802752286084827"><a name="p1802752286084827"></a><a name="p1802752286084827"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> </p>
<p id="p1439730560084827"><a name="p1439730560084827"></a><a name="p1439730560084827"></a>Creates or initializes a vector object. </p>
</td>
</tr>
<tr id="row621226815084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645607473084827"><a name="p645607473084827"></a><a name="p645607473084827"></a><a href="samgr.md#gaebfe9ac38f2667d61bf39420aa8e7035">VECTOR_Clear</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1953923745084827"><a name="p1953923745084827"></a><a name="p1953923745084827"></a>void </p>
<p id="p1752298978084827"><a name="p1752298978084827"></a><a name="p1752298978084827"></a>Destruct a vector object. </p>
</td>
</tr>
<tr id="row748270231084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1381811827084827"><a name="p1381811827084827"></a><a name="p1381811827084827"></a><a href="samgr.md#ga234ba2452c973e9fa4a8be47eaea9d06">VECTOR_Add</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1332407263084827"><a name="p1332407263084827"></a><a name="p1332407263084827"></a>int16 </p>
<p id="p422713342084827"><a name="p422713342084827"></a><a name="p422713342084827"></a>Adds an element to the vector. </p>
</td>
</tr>
<tr id="row486392568084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875905902084827"><a name="p1875905902084827"></a><a name="p1875905902084827"></a><a href="samgr.md#ga1432f30c136d14bc00414d883d8be3bd">VECTOR_Size</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1079502690084827"><a name="p1079502690084827"></a><a name="p1079502690084827"></a>int16 </p>
<p id="p1421443057084827"><a name="p1421443057084827"></a><a name="p1421443057084827"></a>Obtains the number of elements in the vector, including elements that have been set to <strong id="b235872190084827"><a name="b235872190084827"></a><a name="b235872190084827"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row1914668881084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p18765677084827"><a name="p18765677084827"></a><a name="p18765677084827"></a><a href="samgr.md#ga90523bfd48091a0135f74670076af4d5">VECTOR_Num</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665603171084827"><a name="p1665603171084827"></a><a name="p1665603171084827"></a>int16 </p>
<p id="p1124612860084827"><a name="p1124612860084827"></a><a name="p1124612860084827"></a>Obtains the number of valid elements in the vector, excluding elements that have been set to <strong id="b1549085382084827"><a name="b1549085382084827"></a><a name="b1549085382084827"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row145787749084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p46960605084827"><a name="p46960605084827"></a><a name="p46960605084827"></a><a href="samgr.md#ga75210ba0bd37a38a1902c4904e61246a">VECTOR_At</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304258594084827"><a name="p304258594084827"></a><a name="p304258594084827"></a>void * </p>
<p id="p534982227084827"><a name="p534982227084827"></a><a name="p534982227084827"></a>Obtains the element at a specified position. </p>
</td>
</tr>
<tr id="row440386990084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386891961084827"><a name="p386891961084827"></a><a name="p386891961084827"></a><a href="samgr.md#ga7f435d33ba61d145de9d5892b68a0eda">VECTOR_Swap</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p378248941084827"><a name="p378248941084827"></a><a name="p378248941084827"></a>void * </p>
<p id="p1693948370084827"><a name="p1693948370084827"></a><a name="p1693948370084827"></a>Swaps the element at a specified position in a vector with another element. </p>
</td>
</tr>
<tr id="row995021145084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p632250178084827"><a name="p632250178084827"></a><a name="p632250178084827"></a><a href="samgr.md#gaabc5b0eda1ee6889411e6dacb233cb07">VECTOR_Find</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p117168994084827"><a name="p117168994084827"></a><a name="p117168994084827"></a>int16 </p>
<p id="p372815327084827"><a name="p372815327084827"></a><a name="p372815327084827"></a>Checks the position of an element. </p>
</td>
</tr>
<tr id="row288414522084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242227579084827"><a name="p1242227579084827"></a><a name="p1242227579084827"></a><a href="samgr.md#gac65bc6dc959a90d95dff93368abd97c7">VECTOR_FindByKey</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878633409084827"><a name="p878633409084827"></a><a name="p878633409084827"></a>int16 </p>
<p id="p386255529084827"><a name="p386255529084827"></a><a name="p386255529084827"></a>Checks the position of the element with a specified key. </p>
</td>
</tr>
<tr id="row1210504086084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328683935084827"><a name="p328683935084827"></a><a name="p328683935084827"></a><a href="samgr.md#ga9abef49ec89bf913c3bed03faf478c1e">IUNKNOWN_AddRef</a> (<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1582389987084827"><a name="p1582389987084827"></a><a name="p1582389987084827"></a>int </p>
<p id="p1761583135084827"><a name="p1761583135084827"></a><a name="p1761583135084827"></a>Increments the reference count in this <strong id="b1258341904084827"><a name="b1258341904084827"></a><a name="b1258341904084827"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1115671376084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49985063084827"><a name="p49985063084827"></a><a name="p49985063084827"></a><a href="samgr.md#gac857d12648500c7dab1cb43e85ae2ed4">IUNKNOWN_QueryInterface</a> (<a href="iunknown.md">IUnknown</a> *iUnknown, int ver, void **target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414018416084827"><a name="p1414018416084827"></a><a name="p1414018416084827"></a>int </p>
<p id="p1519927568084827"><a name="p1519927568084827"></a><a name="p1519927568084827"></a>Queries the <strong id="b1650458065084827"><a name="b1650458065084827"></a><a name="b1650458065084827"></a><a href="iunknown.md">IUnknown</a></strong> interfaces of a specified version (downcasting). </p>
</td>
</tr>
<tr id="row455961907084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1104491486084827"><a name="p1104491486084827"></a><a name="p1104491486084827"></a><a href="samgr.md#gabd462f8a5e6460a68760cd0719982296">IUNKNOWN_Release</a> (<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1620233973084827"><a name="p1620233973084827"></a><a name="p1620233973084827"></a>int </p>
<p id="p806651360084827"><a name="p806651360084827"></a><a name="p806651360084827"></a>Releases a reference to an <strong id="b479564833084827"><a name="b479564833084827"></a><a name="b479564833084827"></a><a href="iunknown.md">IUnknown</a></strong> interface that is no longer used. </p>
</td>
</tr>
<tr id="row1937784697084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p439900242084827"><a name="p439900242084827"></a><a name="p439900242084827"></a><a href="samgr.md#ga03b440d8dff9fcc8694ca8a3baa83462">SAMGR_SendRequest</a> (const <a href="identity.md">Identity</a> *identity, const <a href="request.md">Request</a> *request, <a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946689916084827"><a name="p1946689916084827"></a><a name="p1946689916084827"></a>int32 </p>
<p id="p339351578084827"><a name="p339351578084827"></a><a name="p339351578084827"></a>Sends a request to a service or feature of a specified identity. </p>
</td>
</tr>
<tr id="row1100704540084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7826961084827"><a name="p7826961084827"></a><a name="p7826961084827"></a><a href="samgr.md#gae7c4d087b251949d10d81e88a47e8dbd">SAMGR_SendSharedRequest</a> (const <a href="identity.md">Identity</a> *identity, const <a href="request.md">Request</a> *request, uint32 *token, <a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28457000084827"><a name="p28457000084827"></a><a name="p28457000084827"></a>uint32 * </p>
<p id="p1146004714084827"><a name="p1146004714084827"></a><a name="p1146004714084827"></a>Sends a request to multiple services or features to save memory. </p>
</td>
</tr>
<tr id="row1361687422084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376160620084827"><a name="p1376160620084827"></a><a name="p1376160620084827"></a><a href="samgr.md#ga0c8c20d2265f4eb8ec8b516300a94a63">SAMGR_SendSharedDirectRequest</a> (const <a href="identity.md">Identity</a> *id, const <a href="request.md">Request</a> *req, const <a href="response.md">Response</a> *resp, uint32 **ref, <a href="samgr.md#ga5e13d943cc6a87a5c99fe604f3bc01e4">Handler</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229809285084827"><a name="p1229809285084827"></a><a name="p1229809285084827"></a>int32 </p>
<p id="p750163943084827"><a name="p750163943084827"></a><a name="p750163943084827"></a>Sends a request and response of a caller to the feature thread. The handler is directly called to process the request and response without using the message processing functions. (Customized function for the broadcast service) </p>
</td>
</tr>
<tr id="row38756340084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1407379035084827"><a name="p1407379035084827"></a><a name="p1407379035084827"></a><a href="samgr.md#gadba5f2881a6e1403cb642726d5fec3e2">SAMGR_SendResponse</a> (const <a href="request.md">Request</a> *request, const <a href="response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p901733457084827"><a name="p901733457084827"></a><a name="p901733457084827"></a>int32 </p>
<p id="p150418359084827"><a name="p150418359084827"></a><a name="p150418359084827"></a>Sends a response after processing a request. </p>
</td>
</tr>
<tr id="row1743884511084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570781978084827"><a name="p570781978084827"></a><a name="p570781978084827"></a><a href="samgr.md#ga44ab9b4c98e2dd6ba3338d1d2664a6fe">SAMGR_SendResponseByIdentity</a> (const <a href="identity.md">Identity</a> *id, const <a href="request.md">Request</a> *request, const <a href="response.md">Response</a> *response)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p379415117084827"><a name="p379415117084827"></a><a name="p379415117084827"></a>int32 </p>
<p id="p1352661404084827"><a name="p1352661404084827"></a><a name="p1352661404084827"></a>Sends a response to a specified service or feature after processing the original request. (Customized function for <strong id="b1865301707084827"><a name="b1865301707084827"></a><a name="b1865301707084827"></a>bootstrap</strong>) </p>
</td>
</tr>
<tr id="row1640690991084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1332161064084827"><a name="p1332161064084827"></a><a name="p1332161064084827"></a><a href="samgr.md#ga21f168d6f97d6991115ae1cf8bbd8deb">SAMGR_GetInstance</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310924113084827"><a name="p1310924113084827"></a><a name="p1310924113084827"></a><a href="samgrlite.md">SamgrLite</a> * </p>
<p id="p1412454563084827"><a name="p1412454563084827"></a><a name="p1412454563084827"></a>Obtains the singleton Samgr instance. </p>
</td>
</tr>
<tr id="row82324249084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683608978084827"><a name="p683608978084827"></a><a name="p683608978084827"></a><a href="samgr.md#ga756ac1f5376c72aa5d14b855a302d7b6">SAMGR_Bootstrap</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910043933084827"><a name="p1910043933084827"></a><a name="p1910043933084827"></a>void </p>
<p id="p1004388570084827"><a name="p1004388570084827"></a><a name="p1004388570084827"></a>Starts system services and features. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section474390269084827"></a>

## **Macro Definition Documentation**<a name="section404828488084827"></a>

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

<a name="table2093797045084827"></a>
<table><thead align="left"><tr id="row941415986084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p117027420084827"><a name="p117027420084827"></a><a name="p117027420084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1589556434084827"><a name="p1589556434084827"></a><a name="p1589556434084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1443878669084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">Indicates</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">the T type. </td>
</tr>
<tr id="row157396553084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
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

## **Typedef Documentation**<a name="section1460640675084827"></a>

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

## **Enumeration Type Documentation**<a name="section1095520792084827"></a>

## BootMessage<a name="gaf39e482610dca95f0dba85613755eb40"></a>

```
enum [BootMessage](samgr.md#gaf39e482610dca95f0dba85613755eb40)
```

 **Description:**

Enumerates the IDs of the message to be processed for starting the bootstrap service. 

This function is implemented by developers of the system service. Messages sent to the bootstrap service when Samgr is started. 

<a name="table2071275155084827"></a>
<table><thead align="left"><tr id="row1826895657084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1246190226084827"><a name="p1246190226084827"></a><a name="p1246190226084827"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p467267960084827"><a name="p467267960084827"></a><a name="p467267960084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row664845097084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7"><a name="ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7"></a><a name="ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7"></a></strong>BOOT_SYS_COMPLETED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985724055084827"><a name="p1985724055084827"></a><a name="p1985724055084827"></a>Message indicating that the core system service is initialized </p>
 </td>
</tr>
<tr id="row63182364084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1"><a name="ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1"></a><a name="ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1"></a></strong>BOOT_APP_COMPLETED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1662024056084827"><a name="p1662024056084827"></a><a name="p1662024056084827"></a>Message indicating that the system and application-layer services are initialized </p>
 </td>
</tr>
<tr id="row897765696084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572"><a name="ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572"></a><a name="ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572"></a></strong>BOOT_REG_SERVICE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2052764445084827"><a name="p2052764445084827"></a><a name="p2052764445084827"></a>Message indicating service registration during running </p>
 </td>
</tr>
<tr id="row547584164084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec"><a name="ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec"></a><a name="ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec"></a></strong>BOOTSTRAP_BUTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p792013247084827"><a name="p792013247084827"></a><a name="p792013247084827"></a>Maximum number of message IDs </p>
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

<a name="table603293191084827"></a>
<table><thead align="left"><tr id="row1111592708084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p607493626084827"><a name="p607493626084827"></a><a name="p607493626084827"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p932022712084827"><a name="p932022712084827"></a><a name="p932022712084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1306264174084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955"></a></strong>LEVEL_HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1708317248084827"><a name="p1708317248084827"></a><a name="p1708317248084827"></a>Preset tag </p>
 </td>
</tr>
<tr id="row1259051043084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647"></a></strong>LEVEL_MIDDLE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p961934448084827"><a name="p961934448084827"></a><a name="p961934448084827"></a>Preset tag </p>
 </td>
</tr>
<tr id="row1091538983084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5"></a></strong>LEVEL_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1833340155084827"><a name="p1833340155084827"></a><a name="p1833340155084827"></a>Preset tag </p>
 </td>
</tr>
<tr id="row759440413084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263"><a name="gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263"></a><a name="gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263"></a></strong>LEVEL_CUSTOM_BEGIN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445366086084827"><a name="p445366086084827"></a><a name="p445366086084827"></a>Customized tag </p>
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

<a name="table1290677800084827"></a>
<table><thead align="left"><tr id="row1081326012084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1241923903084827"><a name="p1241923903084827"></a><a name="p1241923903084827"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p489196703084827"><a name="p489196703084827"></a><a name="p489196703084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row668870189084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402"><a name="ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402"></a></strong>PRI_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291174510084827"><a name="p291174510084827"></a><a name="p291174510084827"></a>Low-priority: (9, 15) </p>
 </td>
</tr>
<tr id="row1122742308084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258"><a name="ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258"></a></strong>PRI_BELOW_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1520339079084827"><a name="p1520339079084827"></a><a name="p1520339079084827"></a>Lower than the normal priority: [16, 23) </p>
 </td>
</tr>
<tr id="row2082342429084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063"><a name="ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063"></a></strong>PRI_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672626925084827"><a name="p672626925084827"></a><a name="p672626925084827"></a>Normal priority: [24, 31). The log service is available. </p>
 </td>
</tr>
<tr id="row350940836084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6"><a name="ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6"></a></strong>PRI_ABOVE_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449731203084827"><a name="p449731203084827"></a><a name="p449731203084827"></a>Higher than the normal priority: [32, 39). The communication service is available. </p>
 </td>
</tr>
<tr id="row1601389495084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b"><a name="ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b"></a><a name="ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b"></a></strong>PRI_BUTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3270449084827"><a name="p3270449084827"></a><a name="p3270449084827"></a>Upper limit of the priority </p>
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

<a name="table964092162084827"></a>
<table><thead align="left"><tr id="row183005029084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1755750180084827"><a name="p1755750180084827"></a><a name="p1755750180084827"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p320665494084827"><a name="p320665494084827"></a><a name="p320665494084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1348999600084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99"><a name="gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99"></a><a name="gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99"></a></strong>SHARED_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427736936084827"><a name="p1427736936084827"></a><a name="p1427736936084827"></a>Tasks shared based on their priority by services </p>
 </td>
</tr>
<tr id="row103339163084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315"><a name="gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315"></a><a name="gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315"></a></strong>SINGLE_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1806013450084827"><a name="p1806013450084827"></a><a name="p1806013450084827"></a>Task exclusively occupied by a service </p>
 </td>
</tr>
<tr id="row1293704136084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376"><a name="gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376"></a><a name="gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376"></a></strong>SPECIFIED_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087580924084827"><a name="p2087580924084827"></a><a name="p2087580924084827"></a>A specified task shared by multiple services </p>
 </td>
</tr>
<tr id="row834461537084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11"><a name="gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11"></a><a name="gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11"></a></strong>NO_TASK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021096930084827"><a name="p2021096930084827"></a><a name="p2021096930084827"></a>No task for the service. Generally, this situation does not occur. </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1023860979084827"></a>

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

<a name="table518420243084827"></a>
<table><thead align="left"><tr id="row943782988084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1848983872084827"><a name="p1848983872084827"></a><a name="p1848983872084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p646625709084827"><a name="p646625709084827"></a><a name="p646625709084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row873292132084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b659311851084827"><a name="b659311851084827"></a><a name="b659311851084827"></a><a href="iunknown.md">IUnknown</a></strong> interface. </td>
</tr>
<tr id="row621519575084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">version</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the version of the <strong id="b1665775214084827"><a name="b1665775214084827"></a><a name="b1665775214084827"></a><a href="iunknown.md">IUnknown</a></strong> interface object to be converted. </td>
</tr>
<tr id="row1285357531084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">target</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1334742177084827"><a name="b1334742177084827"></a><a name="b1334742177084827"></a><a href="iunknown.md">IUnknown</a></strong> subclass type required by the caller. This is an output parameter. </td>
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

<a name="table1649965470084827"></a>
<table><thead align="left"><tr id="row1851570677084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p967520095084827"><a name="p967520095084827"></a><a name="p967520095084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1896123941084827"><a name="p1896123941084827"></a><a name="p1896123941084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1579380233084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b300958708084827"><a name="b300958708084827"></a><a name="b300958708084827"></a><a href="iunknown.md">IUnknown</a><strong id="b734702877084827"><a name="b734702877084827"></a><a name="b734702877084827"></a> interface object. </strong></strong></td>
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

<a name="table363379609084827"></a>
<table><thead align="left"><tr id="row325528906084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1506535060084827"><a name="p1506535060084827"></a><a name="p1506535060084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1220123526084827"><a name="p1220123526084827"></a><a name="p1220123526084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1598926254084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the ID of the feature or service that processes the message. </td>
</tr>
<tr id="row219620400084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request. </td>
</tr>
<tr id="row685586445084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function handling the response. If the value is <strong id="b2135249609084827"><a name="b2135249609084827"></a><a name="b2135249609084827"></a>NULL</strong>, no response is required. </td>
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

<a name="table541358205084827"></a>
<table><thead align="left"><tr id="row985556219084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1662946455084827"><a name="p1662946455084827"></a><a name="p1662946455084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1059543708084827"><a name="p1059543708084827"></a><a name="p1059543708084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1619747852084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original request. </td>
</tr>
<tr id="row1647232201084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">response</td>
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

<a name="table1968567070084827"></a>
<table><thead align="left"><tr id="row71401478084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1223550055084827"><a name="p1223550055084827"></a><a name="p1223550055084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1180949390084827"><a name="p1180949390084827"></a><a name="p1180949390084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row641217016084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the ID of a service or feature. The response is sent to the thread of the service or feature for processing. </td>
</tr>
<tr id="row22852660084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original request. </td>
</tr>
<tr id="row644844266084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">response</td>
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

<a name="table1069679739084827"></a>
<table><thead align="left"><tr id="row970307468084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p84370070084827"><a name="p84370070084827"></a><a name="p84370070084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1184348500084827"><a name="p1184348500084827"></a><a name="p1184348500084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row29696998084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the IDs of services or features, to which the request and response are sent. </td>
</tr>
<tr id="row703292607084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request. </td>
</tr>
<tr id="row732971693084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">resp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the response. </td>
</tr>
<tr id="row1270172204084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ref</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the reference counting. </td>
</tr>
<tr id="row1485932502084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function for handling the request and response. This parameter cannot be <strong id="b957144007084827"><a name="b957144007084827"></a><a name="b957144007084827"></a>NULL</strong>. </td>
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

<a name="table952029608084827"></a>
<table><thead align="left"><tr id="row424898449084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1182177316084827"><a name="p1182177316084827"></a><a name="p1182177316084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p910411564084827"><a name="p910411564084827"></a><a name="p910411564084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row687559011084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the IDs of services or features, to which requests are sent. </td>
</tr>
<tr id="row1717368813084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request. </td>
</tr>
<tr id="row1523982061084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">token</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to reference counting. </td>
</tr>
<tr id="row1599203830084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function handling the response. If the value is <strong id="b1545327585084827"><a name="b1545327585084827"></a><a name="b1545327585084827"></a>NULL</strong>, no response is required. </td>
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

<a name="table525981561084827"></a>
<table><thead align="left"><tr id="row106012767084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1288498749084827"><a name="p1288498749084827"></a><a name="p1288498749084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1958028114084827"><a name="p1958028114084827"></a><a name="p1958028114084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row344942262084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b291096074084827"><a name="b291096074084827"></a><a name="b291096074084827"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row266141007084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
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

<a name="table327141331084827"></a>
<table><thead align="left"><tr id="row615753016084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p384100012084827"><a name="p384100012084827"></a><a name="p384100012084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1292591324084827"><a name="p1292591324084827"></a><a name="p1292591324084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1511351171084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b318151019084827"><a name="b318151019084827"></a><a name="b318151019084827"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row1520774900084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
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

<a name="table813719902084827"></a>
<table><thead align="left"><tr id="row288637707084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p969502873084827"><a name="p969502873084827"></a><a name="p969502873084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1367456151084827"><a name="p1367456151084827"></a><a name="p1367456151084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1767321718084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
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

<a name="table1819034887084827"></a>
<table><thead align="left"><tr id="row1034310467084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1977692582084827"><a name="p1977692582084827"></a><a name="p1977692582084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p106229066084827"><a name="p106229066084827"></a><a name="p106229066084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1849115575084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1749380914084827"><a name="b1749380914084827"></a><a name="b1749380914084827"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row1121108377084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
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

<a name="table1192640432084827"></a>
<table><thead align="left"><tr id="row1557712763084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1707346909084827"><a name="p1707346909084827"></a><a name="p1707346909084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1321658454084827"><a name="p1321658454084827"></a><a name="p1321658454084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1554643263084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1207175247084827"><a name="b1207175247084827"></a><a name="b1207175247084827"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row1391553920084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
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

<a name="table363366594084827"></a>
<table><thead align="left"><tr id="row877268616084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p751673413084827"><a name="p751673413084827"></a><a name="p751673413084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1150647680084827"><a name="p1150647680084827"></a><a name="p1150647680084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row848962605084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the function provided by users for converting data elements into key values. If this function is not provided, set it to <strong id="b878123162084827"><a name="b878123162084827"></a><a name="b878123162084827"></a>NULL</strong>. </td>
</tr>
<tr id="row2124002445084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">compare</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the function for comparing the sizes of two elements. If this function is not provided, set it to <strong id="b100346442084827"><a name="b100346442084827"></a><a name="b100346442084827"></a>NULL</strong>. </td>
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

<a name="table1978657962084827"></a>
<table><thead align="left"><tr id="row818903856084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p700847165084827"><a name="p700847165084827"></a><a name="p700847165084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p60130186084827"><a name="p60130186084827"></a><a name="p60130186084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1047826577084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1685444124084827"><a name="b1685444124084827"></a><a name="b1685444124084827"></a>this</strong> pointer to the vector. </td>
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

<a name="table1445175895084827"></a>
<table><thead align="left"><tr id="row397149397084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p245713471084827"><a name="p245713471084827"></a><a name="p245713471084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1196646563084827"><a name="p1196646563084827"></a><a name="p1196646563084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2112891313084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b551560491084827"><a name="b551560491084827"></a><a name="b551560491084827"></a>this</strong> pointer to the vector. </td>
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

<a name="table996271414084827"></a>
<table><thead align="left"><tr id="row169991328084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p994559027084827"><a name="p994559027084827"></a><a name="p994559027084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p736047863084827"><a name="p736047863084827"></a><a name="p736047863084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row721113098084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vector</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b2125193193084827"><a name="b2125193193084827"></a><a name="b2125193193084827"></a>this</strong> pointer to the vector. </td>
</tr>
<tr id="row91456032084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the position of the element to be swapped. </td>
</tr>
<tr id="row1744087056084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
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

