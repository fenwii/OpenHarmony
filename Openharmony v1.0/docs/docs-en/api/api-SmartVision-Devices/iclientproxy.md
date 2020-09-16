# IClientProxy<a name="EN-US_TOPIC_0000001054918157"></a>

## **Overview**<a name="section2093507899093531"></a>

**Related Modules:**

[Registry](registry.md)

**Description:**

Defines the client proxy object. 

This object is used for the IPC with the server. If you want to use the same invocation mode as that on the server, create an object inherited from

 and implement serialization.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1154640433093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1090334434093531"></a>
<table><thead align="left"><tr id="row1639217921093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1508665079093531"><a name="p1508665079093531"></a><a name="p1508665079093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1888042182093531"><a name="p1888042182093531"></a><a name="p1888042182093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2016938570093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244823187093531"><a name="p1244823187093531"></a><a name="p1244823187093531"></a><a href="iclientproxy.md#ac0ffdbb3582a99ba237a70d26320075b">INHERIT_IUNKNOWN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
<tr id="row1756667270093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1209062151093531"><a name="p1209062151093531"></a><a name="p1209062151093531"></a><a href="iclientproxy.md#a18d8a9e57b05be9fd3e5772e445f474d">Invoke</a> )(<a href="iclientproxy.md">IClientProxy</a> *proxy, int funcId, IpcIo *request, IOwner owner, <a href="registry.md#ga362a17c1bda1aace88d42dcbc88bdfac">INotify</a> notify)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1546499307093531"><a name="p1546499307093531"></a><a name="p1546499307093531"></a>int(* </p>
<p id="p812857562093531"><a name="p812857562093531"></a><a name="p812857562093531"></a>Sends an IPC message from the client to the <strong id="b1489191094093531"><a name="b1489191094093531"></a><a name="b1489191094093531"></a><a href="iserverproxy.md">IServerProxy</a></strong>. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1159919578093531"></a>

## **Field Documentation**<a name="section1841888850093531"></a>

## INHERIT\_IUNKNOWN<a name="ac0ffdbb3582a99ba237a70d26320075b"></a>

```
IClientProxy::INHERIT_IUNKNOWN
```

 **Description:**

Inherites the  **[IUnknown](iunknown.md)**  base class. 

## Invoke<a name="a18d8a9e57b05be9fd3e5772e445f474d"></a>

```
int(* IClientProxy::Invoke) ([IClientProxy](iclientproxy.md) *proxy, int funcId, IpcIo *request, IOwner owner, [INotify](registry.md#ga362a17c1bda1aace88d42dcbc88bdfac) notify)
```

 **Description:**

Sends an IPC message from the client to the  **[IServerProxy](iserverproxy.md)**. 

This function is used for IPC. The passed  **proxy**  is used to obtain the server information. Then,  **request**  carries the request message to be sent to the server and processed by the function specified by  **funcId**.  **notify**  is a callback function used to process the response message. 

**Parameters:**

<a name="table871302558093531"></a>
<table><thead align="left"><tr id="row805987054093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p80575934093531"><a name="p80575934093531"></a><a name="p80575934093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p149863623093531"><a name="p149863623093531"></a><a name="p149863623093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1946282698093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">proxy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer of the client proxy object. </td>
</tr>
<tr id="row1171509472093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">funcId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the function implemented on the server. </td>
</tr>
<tr id="row79378237093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the serialized request message. </td>
</tr>
<tr id="row1069120584093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">owner</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the receiver (generics type) of the response message. </td>
</tr>
<tr id="row795229031093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">notify</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback function that notifies the client of the response message. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the IPC message is sent successfully; returns other error codes if the message fails to be sent. 



