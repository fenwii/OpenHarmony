# Service<a name="ZH-CN_TOPIC_0000001055198168"></a>

## **Overview**<a name="section79551014093536"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Indicates the basic type of a service. 

You need to implement the function pointers of  **[Service](Service.md)**. 

## **Summary**<a name="section2132820964093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table436981971093536"></a>
<table><thead align="left"><tr id="row523255791093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1152172618093536"><a name="p1152172618093536"></a><a name="p1152172618093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1800789237093536"><a name="p1800789237093536"></a><a name="p1800789237093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1531211061093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p404149656093536"><a name="p404149656093536"></a><a name="p404149656093536"></a><a href="Service.md#a7d6fe59023a0e6ad2ad7c625c0d117d6">GetName</a> )(<a href="Service.md">Service</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773426721093536"><a name="p1773426721093536"></a><a name="p1773426721093536"></a>const char *(*&nbsp;</p>
<p id="p1032738568093536"><a name="p1032738568093536"></a><a name="p1032738568093536"></a>Obtains the name of a service. </p>
</td>
</tr>
<tr id="row104407929093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498743818093536"><a name="p498743818093536"></a><a name="p498743818093536"></a><a href="Service.md#a80b0715ef9129631d5f622cb199ff8ae">Initialize</a> )(<a href="Service.md">Service</a> *service, <a href="Identity.md">Identity</a> identity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p302026545093536"><a name="p302026545093536"></a><a name="p302026545093536"></a>BOOL(*&nbsp;</p>
<p id="p2059916953093536"><a name="p2059916953093536"></a><a name="p2059916953093536"></a>Initializes the service. </p>
</td>
</tr>
<tr id="row761920194093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1752466601093536"><a name="p1752466601093536"></a><a name="p1752466601093536"></a><a href="Service.md#aa2b7015639906efbadd36aa87eea269b">MessageHandle</a> )(<a href="Service.md">Service</a> *service, <a href="Request.md">Request</a> *request)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038483563093536"><a name="p1038483563093536"></a><a name="p1038483563093536"></a>BOOL(*&nbsp;</p>
<p id="p1254048349093536"><a name="p1254048349093536"></a><a name="p1254048349093536"></a>Processes service messages. </p>
</td>
</tr>
<tr id="row1445873306093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p145862224093536"><a name="p145862224093536"></a><a name="p145862224093536"></a><a href="Service.md#abc4b1868a77fafe434fe63c8a4685aeb">GetTaskConfig</a> )(<a href="Service.md">Service</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2047430508093536"><a name="p2047430508093536"></a><a name="p2047430508093536"></a><a href="TaskConfig.md">TaskConfig</a>(*&nbsp;</p>
<p id="p821279904093536"><a name="p821279904093536"></a><a name="p821279904093536"></a>Obtains task configurations of a service. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section970822250093536"></a>

## **Field Documentation**<a name="section792546837093536"></a>

## GetName<a name="a7d6fe59023a0e6ad2ad7c625c0d117d6"></a>

```
const char*(* Service::GetName) ([Service](Service.md) *service)
```

 **Description:**

Obtains the name of a service. 

This function is called by Samgr during service registration and startup. You need to implement this function. 

**Parameters:**

<a name="table1947554745093536"></a>
<table><thead align="left"><tr id="row1324681248093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1587705902093536"><a name="p1587705902093536"></a><a name="p1587705902093536"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p228571465093536"><a name="p228571465093536"></a><a name="p228571465093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row860361115093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a constant string no more than 16 bytes if the service name is obtained successfully; returns  **NULL**  if the service name fails to be obtained. 



## GetTaskConfig<a name="abc4b1868a77fafe434fe63c8a4685aeb"></a>

```
[TaskConfig](TaskConfig.md)(* Service::GetTaskConfig) ([Service](Service.md) *service)
```

 **Description:**

Obtains task configurations of a service. 

This function is used to return task configurations. You need to implement this function. 

**Parameters:**

<a name="table1857807112093536"></a>
<table><thead align="left"><tr id="row1899857823093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2124294009093536"><a name="p2124294009093536"></a><a name="p2124294009093536"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p769560455093536"><a name="p769560455093536"></a><a name="p769560455093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1552270508093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [TaskConfig](TaskConfig.md).



## Initialize<a name="a80b0715ef9129631d5f622cb199ff8ae"></a>

```
BOOL(* Service::Initialize) ([Service](Service.md) *service, [Identity](Identity.md) identity)
```

 **Description:**

Initializes the service. 

After Samgr assigns tasks to a service, the service calls the function in its own tasks. You need to implement this function. 

**Parameters:**

<a name="table2136037797093536"></a>
<table><thead align="left"><tr id="row1256055440093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1692049749093536"><a name="p1692049749093536"></a><a name="p1692049749093536"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1897454389093536"><a name="p1897454389093536"></a><a name="p1897454389093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1901857093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
<tr id="row886751655093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID allocated by the system to the service. For details, see <a href="Identity.md">Identity</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the initialization is successful; returns  **FALSE**  otherwise. 



## MessageHandle<a name="aa2b7015639906efbadd36aa87eea269b"></a>

```
BOOL(* Service::MessageHandle) ([Service](Service.md) *service, [Request](Request.md) *request)
```

 **Description:**

Processes service messages. 

This function is used to process requests sent by the caller through  [IUnknown](IUnknown.md). You need to implement this function. 

**Parameters:**

<a name="table580300253093536"></a>
<table><thead align="left"><tr id="row2130554311093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2052279832093536"><a name="p2052279832093536"></a><a name="p2052279832093536"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1614905002093536"><a name="p1614905002093536"></a><a name="p1614905002093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row334696117093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service. </td>
</tr>
<tr id="row1458828076093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the request data. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the message processing is successful; returns  **FALSE**  if the processing fails. 



