# Registry<a name="EN-US_TOPIC_0000001055358060"></a>

## **Overview**<a name="section1571610145084827"></a>

Provides APIs for registering and discovering inter-process communication \(IPC\) capabilities. 

Based on the Samgr development framework, this module helps you to develop system capabilities and implement cross-process calls. This module is used when system capabilities need to be provided across processes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section142008546084827"></a>

## Files<a name="files"></a>

<a name="table423209442084827"></a>
<table><thead align="left"><tr id="row112523827084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p819560436084827"><a name="p819560436084827"></a><a name="p819560436084827"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1136875371084827"><a name="p1136875371084827"></a><a name="p1136875371084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row966121230084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p760668688084827"><a name="p760668688084827"></a><a name="p760668688084827"></a><a href="iproxy_client-h.md">iproxy_client.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487505542084827"><a name="p1487505542084827"></a><a name="p1487505542084827"></a>Provides the client proxy class. </p>
</td>
</tr>
<tr id="row462795068084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616108859084827"><a name="p1616108859084827"></a><a name="p1616108859084827"></a><a href="iproxy_server-h.md">iproxy_server.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330847962084827"><a name="p1330847962084827"></a><a name="p1330847962084827"></a>Provides the server proxy. </p>
</td>
</tr>
<tr id="row735174859084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1879483444084827"><a name="p1879483444084827"></a><a name="p1879483444084827"></a><a href="registry-h.md">registry.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052238857084827"><a name="p1052238857084827"></a><a name="p1052238857084827"></a>Provides basic APIs for remote service registration and discovery. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1948359459084827"></a>
<table><thead align="left"><tr id="row1689214566084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2040265981084827"><a name="p2040265981084827"></a><a name="p2040265981084827"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p838376888084827"><a name="p838376888084827"></a><a name="p838376888084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row406418592084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1843435540084827"><a name="p1843435540084827"></a><a name="p1843435540084827"></a><a href="iclientproxy.md">IClientProxy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p489200166084827"><a name="p489200166084827"></a><a name="p489200166084827"></a>Defines the client proxy object. </p>
</td>
</tr>
<tr id="row823064937084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p282270800084827"><a name="p282270800084827"></a><a name="p282270800084827"></a><a href="iserverproxy.md">IServerProxy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p128699271084827"><a name="p128699271084827"></a><a name="p128699271084827"></a>Defines the base class of the server proxy object. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1805918985084827"></a>
<table><thead align="left"><tr id="row664104587084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2066816544084827"><a name="p2066816544084827"></a><a name="p2066816544084827"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p989331980084827"><a name="p989331980084827"></a><a name="p989331980084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row728499191084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1190737157084827"><a name="p1190737157084827"></a><a name="p1190737157084827"></a><a href="registry.md#ga86734e6a03eb089309e87ec628002034">INHERIT_CLIENT_IPROXY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p955300597084827"><a name="p955300597084827"></a><a name="p955300597084827"></a>Indicates the inherited macro of the client proxy. </p>
</td>
</tr>
<tr id="row895390647084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1219145845084827"><a name="p1219145845084827"></a><a name="p1219145845084827"></a><a href="registry.md#ga9ad9b5f0e1f50f2528cbef67957b2319">INHERIT_IPROXY_ENTRY</a>(T)   <a href="samgr.md#gad6324fd90dd636180efa2a59b377e65c">INHERIT_IUNKNOWNENTRY</a>(T)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p956801964084827"><a name="p956801964084827"></a><a name="p956801964084827"></a>Inherits the server proxy class. </p>
</td>
</tr>
<tr id="row1893607541084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132985730084827"><a name="p2132985730084827"></a><a name="p2132985730084827"></a><a href="registry.md#ga59b6c10043506af716ce9052a5a964a7">IPROXY_END</a>   <a href="samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3">IUNKNOWN_ENTRY_END</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1600849810084827"><a name="p1600849810084827"></a><a name="p1600849810084827"></a>Defines the end of the default initialization for the server proxy class. </p>
</td>
</tr>
<tr id="row1061006930084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817411649084827"><a name="p1817411649084827"></a><a name="p1817411649084827"></a><a href="registry.md#gad513d97bfb873f27c9b8f69a5a418d55">SERVER_PROXY_VER</a>   0x80</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791563653084827"><a name="p791563653084827"></a><a name="p791563653084827"></a>Defines the default version number of the server proxy. </p>
</td>
</tr>
<tr id="row112252814084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p232443474084827"><a name="p232443474084827"></a><a name="p232443474084827"></a><a href="registry.md#ga58e6d24ef278dceb3fb9c77527acdb5c">INHERIT_SERVER_IPROXY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467422827084827"><a name="p467422827084827"></a><a name="p467422827084827"></a>Inherits the server proxy function. </p>
</td>
</tr>
<tr id="row2119385925084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982839624084827"><a name="p982839624084827"></a><a name="p982839624084827"></a><a href="registry.md#ga3c3f1e77cc1a495f48a4b3cd0f8934be">SERVER_IPROXY_BEGIN</a>   <a href="samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1">IUNKNOWN_ENTRY_BEGIN</a>(<a href="registry.md#gad513d97bfb873f27c9b8f69a5a418d55">SERVER_PROXY_VER</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p50798851084827"><a name="p50798851084827"></a><a name="p50798851084827"></a>Defines the beginning of the default initialization for the server proxy class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1780424930084827"></a>
<table><thead align="left"><tr id="row213166280084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1183586096084827"><a name="p1183586096084827"></a><a name="p1183586096084827"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1847727698084827"><a name="p1847727698084827"></a><a name="p1847727698084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row961452718084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35474087084827"><a name="p35474087084827"></a><a name="p35474087084827"></a><a href="registry.md#ga362a17c1bda1aace88d42dcbc88bdfac">INotify</a>) (IOwner owner, int code, IpcIo *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1912193013084827"><a name="p1912193013084827"></a><a name="p1912193013084827"></a>typedef int(* </p>
<p id="p2046656237084827"><a name="p2046656237084827"></a><a name="p2046656237084827"></a>Called when a client request is responded. </p>
</td>
</tr>
<tr id="row2141509408084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p794523028084827"><a name="p794523028084827"></a><a name="p794523028084827"></a><a href="registry.md#ga0c8aa2ef9883bd97b4f1309895adaa4c">Creator</a>) (const char *service, const char *feature, uint32 size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p562864898084827"><a name="p562864898084827"></a><a name="p562864898084827"></a>typedef void *(* </p>
<p id="p419254573084827"><a name="p419254573084827"></a><a name="p419254573084827"></a>Indicates the creator of the customized client proxy. </p>
</td>
</tr>
<tr id="row1206785248084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1726427226084827"><a name="p1726427226084827"></a><a name="p1726427226084827"></a><a href="registry.md#ga1e6298b1246357f70ad0b581e0eb9305">Destroyer</a>) (const char *service, const char *feature, void *iproxy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1669680763084827"><a name="p1669680763084827"></a><a name="p1669680763084827"></a>typedef void(* </p>
<p id="p2134877405084827"><a name="p2134877405084827"></a><a name="p2134877405084827"></a>Indicates the destroyer of the customized client proxy. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table7440957084827"></a>
<table><thead align="left"><tr id="row284964100084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p748639525084827"><a name="p748639525084827"></a><a name="p748639525084827"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1333946739084827"><a name="p1333946739084827"></a><a name="p1333946739084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1111232572084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p379448324084827"><a name="p379448324084827"></a><a name="p379448324084827"></a><a href="registry.md#gaa9bb385bfe593f4377a83cf513189bf1">SAMGR_GetRemoteIdentity</a> (const char *service, const char *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2108620922084827"><a name="p2108620922084827"></a><a name="p2108620922084827"></a>SvcIdentity </p>
<p id="p1682349934084827"><a name="p1682349934084827"></a><a name="p1682349934084827"></a>Obtains the IPC address of a remote service and feature based on the service name and feature name. </p>
</td>
</tr>
<tr id="row317447451084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121296929084827"><a name="p2121296929084827"></a><a name="p2121296929084827"></a><a href="registry.md#ga64797e3f63201c40dbdf21b90cff23d2">SAMGR_RegisterFactory</a> (const char *service, const char *feature, <a href="registry.md#ga0c8aa2ef9883bd97b4f1309895adaa4c">Creator</a> creator, <a href="registry.md#ga1e6298b1246357f70ad0b581e0eb9305">Destroyer</a> destroyer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304287369084827"><a name="p304287369084827"></a><a name="p304287369084827"></a>int </p>
<p id="p601742178084827"><a name="p601742178084827"></a><a name="p601742178084827"></a>Registers the factory method of the client proxy object with the Samgr. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section413186903084827"></a>

## **Macro Definition Documentation**<a name="section567314991084827"></a>

## INHERIT\_CLIENT\_IPROXY<a name="ga86734e6a03eb089309e87ec628002034"></a>

```
#define INHERIT_CLIENT_IPROXY
```

```
Values: [INHERIT_IUNKNOWN](samgr.md#gab74532a22d6993d0ffc014d36253397f); \

 int (*Invoke)([IClientProxy](iclientproxy.md) *proxy, int funcId, IpcIo *request, IOwner owner, [INotify](registry.md#ga362a17c1bda1aace88d42dcbc88bdfac) notify)


```

 **Description:**

Indicates the inherited macro of the client proxy. 

This constant is used when a client proxy needs to be customized or generated by a tool. 

## INHERIT\_IPROXY\_ENTRY<a name="ga9ad9b5f0e1f50f2528cbef67957b2319"></a>

```
#define INHERIT_IPROXY_ENTRY( T)   [INHERIT_IUNKNOWNENTRY](samgr.md#gad6324fd90dd636180efa2a59b377e65c)(T)
```

 **Description:**

Inherits the server proxy class. 

When the server provides cross-process system capabilities, it uses  **INHERIT\_IPROXY\_ENTRY**  to define the server proxy class. 

## INHERIT\_SERVER\_IPROXY<a name="ga58e6d24ef278dceb3fb9c77527acdb5c"></a>

```
#define INHERIT_SERVER_IPROXY
```

```
Values: [INHERIT_IUNKNOWN](samgr.md#gab74532a22d6993d0ffc014d36253397f); \

 int32 (*Invoke)([IServerProxy](iserverproxy.md) *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)


```

 **Description:**

Inherits the server proxy function. 

When the server provides cross-process system capabilities, it uses  **INHERIT\_SERVER\_IPROXY**  to define the server proxy function. 

## IPROXY\_END<a name="ga59b6c10043506af716ce9052a5a964a7"></a>

```
#define IPROXY_END   [IUNKNOWN_ENTRY_END](samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3)
```

 **Description:**

Defines the end of the default initialization for the server proxy class. 

This macro is used for developing the server proxy class. You can inherit this macro to reduce the code amount and prevent class definition inconsistency. 

## SERVER\_IPROXY\_BEGIN<a name="ga3c3f1e77cc1a495f48a4b3cd0f8934be"></a>

```
#define SERVER_IPROXY_BEGIN   [IUNKNOWN_ENTRY_BEGIN](samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1)([SERVER_PROXY_VER](registry.md#gad513d97bfb873f27c9b8f69a5a418d55))
```

 **Description:**

Defines the beginning of the default initialization for the server proxy class. 

This macro is used for developing the server proxy class. You can inherit this macro to reduce the code amount and prevent class definition inconsistency. 

## SERVER\_PROXY\_VER<a name="gad513d97bfb873f27c9b8f69a5a418d55"></a>

```
#define SERVER_PROXY_VER   0x80
```

 **Description:**

Defines the default version number of the server proxy. 

The cross-process system capabilities are registered when Samgr uses  **SERVER\_PROXY\_VER**  to query the registered server proxy. 

## **Typedef Documentation**<a name="section2062440209084827"></a>

## Creator<a name="ga0c8aa2ef9883bd97b4f1309895adaa4c"></a>

```
typedef void*(* Creator) (const char *service, const char *feature, uint32 size)
```

 **Description:**

Indicates the creator of the customized client proxy. 

This macro creates a local client proxy for remote service APIs. If you want to call the remote APIs in the way that local APIs are called, implement this macro to encapsulate serialized data into the proxy. The system automatically calls this macro when creating a proxy object. 

**Parameters:**

<a name="table2112129773084827"></a>
<table><thead align="left"><tr id="row2017480942084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2118264534084827"><a name="p2118264534084827"></a><a name="p2118264534084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p284304334084827"><a name="p284304334084827"></a><a name="p284304334084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1788198904084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the service to which the function belongs. </td>
</tr>
<tr id="row1671598904084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the feature to which the function belongs. </td>
</tr>
<tr id="row2010378390084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the head to be added when a client proxy is created. The required memory capacity is the head size plus the object size. </td>
</tr>
</tbody>
</table>

**Returns:**

void \* Returns the applied memory capacity and initialize the memory for the client proxy. 



## Destroyer<a name="ga1e6298b1246357f70ad0b581e0eb9305"></a>

```
typedef void(* Destroyer) (const char *service, const char *feature, void *iproxy)
```

 **Description:**

Indicates the destroyer of the customized client proxy. 

This macro destroys local client proxy for remote service APIs. If you want to call the remote APIs in the way that local APIs are called, implement this macro to encapsulate serialized data into the proxy. The system automatically calls this macro when destroying a proxy object. 

**Parameters:**

<a name="table432185036084827"></a>
<table><thead align="left"><tr id="row1059402118084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1638408950084827"><a name="p1638408950084827"></a><a name="p1638408950084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p19697541084827"><a name="p19697541084827"></a><a name="p19697541084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1250788881084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the service to which the function belongs. </td>
</tr>
<tr id="row503561448084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the feature to which the function belongs. </td>
</tr>
<tr id="row276166625084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iproxy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start address of the memory that is applied by <strong id="b1157908022084827"><a name="b1157908022084827"></a><a name="b1157908022084827"></a>Creator</strong>. </td>
</tr>
</tbody>
</table>

## INotify<a name="ga362a17c1bda1aace88d42dcbc88bdfac"></a>

```
typedef int(* INotify) (IOwner owner, int code, IpcIo *reply)
```

 **Description:**

Called when a client request is responded. 

The client implements this  **INotify**  callback to receive response data from the server.  **owner**  indicates the client proxy that receives the response data;  **code**  indicates the error code of the response data from the server;  **reply**  indicates the response data. 

## **Function Documentation**<a name="section599061359084827"></a>

## SAMGR\_GetRemoteIdentity\(\)<a name="gaa9bb385bfe593f4377a83cf513189bf1"></a>

```
SvcIdentity SAMGR_GetRemoteIdentity (const char * service, const char * feature )
```

 **Description:**

Obtains the IPC address of a remote service and feature based on the service name and feature name. 

This function is used when  [IClientProxy](iclientproxy.md)  cannot meet your requirements for calling IPCs. For example, if you need to receive the death notification of a remote service or feature, you can call this function to obtain the address of the remote service or feature and subscribe to the death notification from the IPC. 

**Parameters:**

<a name="table292773344084827"></a>
<table><thead align="left"><tr id="row1241772755084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1095716672084827"><a name="p1095716672084827"></a><a name="p1095716672084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1984256719084827"><a name="p1984256719084827"></a><a name="p1984256719084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row525146671084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the remote service. </td>
</tr>
<tr id="row804508936084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the remote feature. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the IPC address of the remote service or feature. When the handle of the obtained address structure  **SvcIdentity**  is  **0xFFFFFFFF**, the address is invalid. 

**Attention:**

This function can be called only after  **GetFeatureApi**  in  [SamgrLite](samgrlite.md)  is successfully called. Otherwise, an invalid address is returned. When the service or feature does not support IPC communication, an invalid address will be returned. 



## SAMGR\_RegisterFactory\(\)<a name="ga64797e3f63201c40dbdf21b90cff23d2"></a>

```
int SAMGR_RegisterFactory (const char * service, const char * feature, [Creator](registry.md#ga0c8aa2ef9883bd97b4f1309895adaa4c) creator, [Destroyer](registry.md#ga1e6298b1246357f70ad0b581e0eb9305) destroyer )
```

 **Description:**

Registers the factory method of the client proxy object with the Samgr. 

If you want to call the remote APIs in the way that local APIs are called, implement this function to encapsulate serialized data into the proxy. During system initialization, the module that uses the remote proxy calls the function as required. 

**Parameters:**

<a name="table1871366415084827"></a>
<table><thead align="left"><tr id="row481271593084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p760675351084827"><a name="p760675351084827"></a><a name="p760675351084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p454843587084827"><a name="p454843587084827"></a><a name="p454843587084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1428800229084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service name of the client proxy. </td>
</tr>
<tr id="row1363604020084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature name of the client proxy. </td>
</tr>
<tr id="row150709120084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">creator</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1149023798084827"><a name="b1149023798084827"></a><a name="b1149023798084827"></a>Creator</strong> function of the client proxy. </td>
</tr>
<tr id="row1754737552084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">destroyer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1112061685084827"><a name="b1112061685084827"></a><a name="b1112061685084827"></a>Destroyer</strong> function of the client proxy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the registration is successful; returns other error codes if the registration fails. 



