# Service<a name="EN-US_TOPIC_0000001055675026"></a>

## **Overview**<a name="section409198877191902"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Indicates the basic type of a service. 

You need to implement the function pointers of  **[Service](service.md)**. 

## **Summary**<a name="section439584113191902"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2142070268191902"></a>
<table><thead align="left"><tr id="row60713272191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1885507364191902"><a name="p1885507364191902"></a><a name="p1885507364191902"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1819630238191902"><a name="p1819630238191902"></a><a name="p1819630238191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1127049834191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1518556210191902"><a name="p1518556210191902"></a><a name="p1518556210191902"></a><a href="service.md#a7d6fe59023a0e6ad2ad7c625c0d117d6">GetName</a> )(<a href="service.md">Service</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p698842218191902"><a name="p698842218191902"></a><a name="p698842218191902"></a>const char *(* </p>
<p id="p1989507559191902"><a name="p1989507559191902"></a><a name="p1989507559191902"></a>Obtains the name of a service. </p>
</td>
</tr>
<tr id="row1947051997191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780095557191902"><a name="p780095557191902"></a><a name="p780095557191902"></a><a href="service.md#a80b0715ef9129631d5f622cb199ff8ae">Initialize</a> )(<a href="service.md">Service</a> *service, <a href="identity.md">Identity</a> identity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1520955573191902"><a name="p1520955573191902"></a><a name="p1520955573191902"></a>BOOL(* </p>
<p id="p292486864191902"><a name="p292486864191902"></a><a name="p292486864191902"></a>Initializes the service. </p>
</td>
</tr>
<tr id="row1253690594191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1289134008191902"><a name="p1289134008191902"></a><a name="p1289134008191902"></a><a href="service.md#aa2b7015639906efbadd36aa87eea269b">MessageHandle</a> )(<a href="service.md">Service</a> *service, <a href="request.md">Request</a> *request)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122784469191902"><a name="p1122784469191902"></a><a name="p1122784469191902"></a>BOOL(* </p>
<p id="p1876415842191902"><a name="p1876415842191902"></a><a name="p1876415842191902"></a>Processes service messages. </p>
</td>
</tr>
<tr id="row1605592521191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261288775191902"><a name="p261288775191902"></a><a name="p261288775191902"></a><a href="service.md#abc4b1868a77fafe434fe63c8a4685aeb">GetTaskConfig</a> )(<a href="service.md">Service</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1373909554191902"><a name="p1373909554191902"></a><a name="p1373909554191902"></a><a href="taskconfig.md">TaskConfig</a>(* </p>
<p id="p523408060191902"><a name="p523408060191902"></a><a name="p523408060191902"></a>Obtains task configurations of a service. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section273198917191902"></a>

## **Field Documentation**<a name="section1986485814191902"></a>

## GetName<a name="a7d6fe59023a0e6ad2ad7c625c0d117d6"></a>

```
const char*(* Service::GetName) ([Service](service.md) *service)
```

 **Description:**

Obtains the name of a service. 

This function is called by Samgr during service registration and startup. You need to implement this function. 

**Parameters:**

<a name="table400506977191902"></a>
<table><thead align="left"><tr id="row2057375397191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1406449946191902"><a name="p1406449946191902"></a><a name="p1406449946191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1086582767191902"><a name="p1086582767191902"></a><a name="p1086582767191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1931982288191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a constant string no more than 16 bytes if the service name is obtained successfully; returns  **NULL**  if the service name fails to be obtained. 



## GetTaskConfig<a name="abc4b1868a77fafe434fe63c8a4685aeb"></a>

```
[TaskConfig](taskconfig.md)(* Service::GetTaskConfig) ([Service](service.md) *service)
```

 **Description:**

Obtains task configurations of a service. 

This function is used to return task configurations. You need to implement this function. 

**Parameters:**

<a name="table981642248191902"></a>
<table><thead align="left"><tr id="row316063158191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p30009119191902"><a name="p30009119191902"></a><a name="p30009119191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1532921989191902"><a name="p1532921989191902"></a><a name="p1532921989191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1402887261191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [TaskConfig](taskconfig.md).



## Initialize<a name="a80b0715ef9129631d5f622cb199ff8ae"></a>

```
BOOL(* Service::Initialize) ([Service](service.md) *service, [Identity](identity.md) identity)
```

 **Description:**

Initializes the service. 

After Samgr assigns tasks to a service, the service calls the function in its own tasks. You need to implement this function. 

**Parameters:**

<a name="table1409379728191902"></a>
<table><thead align="left"><tr id="row683424521191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p361182725191902"><a name="p361182725191902"></a><a name="p361182725191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p148554492191902"><a name="p148554492191902"></a><a name="p148554492191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row100386001191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
<tr id="row1894032351191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID allocated by the system to the service. For details, see <a href="identity.md">Identity</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the initialization is successful; returns  **FALSE**  otherwise. 



## MessageHandle<a name="aa2b7015639906efbadd36aa87eea269b"></a>

```
BOOL(* Service::MessageHandle) ([Service](service.md) *service, [Request](request.md) *request)
```

 **Description:**

Processes service messages. 

This function is used to process requests sent by the caller through  [IUnknown](iunknown.md). You need to implement this function. 

**Parameters:**

<a name="table1717508402191902"></a>
<table><thead align="left"><tr id="row348320836191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1220423646191902"><a name="p1220423646191902"></a><a name="p1220423646191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1915262792191902"><a name="p1915262792191902"></a><a name="p1915262792191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1437435348191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
<tr id="row1412591400191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request data. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the message processing is successful; returns  **FALSE**  if the processing fails. 



