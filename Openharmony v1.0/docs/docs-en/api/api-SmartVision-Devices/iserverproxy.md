# IServerProxy<a name="EN-US_TOPIC_0000001054718129"></a>

## **Overview**<a name="section1874964126093531"></a>

**Related Modules:**

[Registry](registry.md)

**Description:**

Defines the base class of the server proxy object. 

When the server provides cross-process system capabilities, it uses  **INHERIT\_SERVER\_IPROXY**  to define the server proxy. 

## **Summary**<a name="section223041189093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table734188863093531"></a>
<table><thead align="left"><tr id="row602411228093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1248951396093531"><a name="p1248951396093531"></a><a name="p1248951396093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p349887087093531"><a name="p349887087093531"></a><a name="p349887087093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1515144113093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p86391199093531"><a name="p86391199093531"></a><a name="p86391199093531"></a><a href="iserverproxy.md#a98683c7eaf7a11036cddf8207ddcadbe">INHERIT_IUNKNOWN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
<tr id="row1596986543093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p439236462093531"><a name="p439236462093531"></a><a name="p439236462093531"></a><a href="iserverproxy.md#a0275e8b826a3de89ab9021906c8360a7">Invoke</a> )(<a href="iserverproxy.md">IServerProxy</a> *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1960918505093531"><a name="p1960918505093531"></a><a name="p1960918505093531"></a>int32(* </p>
<p id="p2087984609093531"><a name="p2087984609093531"></a><a name="p2087984609093531"></a>Unmarshals the IPC message received by the server. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section195104731093531"></a>

## **Field Documentation**<a name="section1024945591093531"></a>

## INHERIT\_IUNKNOWN<a name="a98683c7eaf7a11036cddf8207ddcadbe"></a>

```
IServerProxy::INHERIT_IUNKNOWN
```

 **Description:**

This class inherits from  **[IUnknown](iunknown.md)**. 

## Invoke<a name="a0275e8b826a3de89ab9021906c8360a7"></a>

```
int32(* IServerProxy::Invoke) ([IServerProxy](iserverproxy.md) *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
```

 **Description:**

Unmarshals the IPC message received by the server. 

This function is implemented by developers and called by the system. This function runs in the message processing thread of the service. Do not block the message processing thread; otherwise, the function may fail to be executed. 

**Parameters:**

<a name="table1262536353093531"></a>
<table><thead align="left"><tr id="row1187246595093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p967129292093531"><a name="p967129292093531"></a><a name="p967129292093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2099926678093531"><a name="p2099926678093531"></a><a name="p2099926678093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1630857098093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">Proxy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the server proxy object. </td>
</tr>
<tr id="row742325200093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">funcId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the server function to be invoked by the client. </td>
</tr>
<tr id="row2072628977093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">origin</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the original IPC message, from which the header information can be obtained. </td>
</tr>
<tr id="row2125531190093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">req</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">ipc Indicates the message body, from which data can be obtained. </td>
</tr>
<tr id="row1814045086093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">reply</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the output parameter, which is used to respond to the message. The value can contain a maximum of five objects and 200 bytes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the unmarshalling is successful; returns other error codes if the unmarshalling fails. 



