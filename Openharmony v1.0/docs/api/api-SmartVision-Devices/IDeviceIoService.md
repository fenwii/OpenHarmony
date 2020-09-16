# IDeviceIoService<a name="ZH-CN_TOPIC_0000001055198134"></a>

## **Overview**<a name="section1794109710093531"></a>

**Related Modules:**

[Core](Core.md)

**Description:**

Defines the driver service. 

When a driver releases services to user-level applications, the service interface must inherit this structure and implements the  **Dispatch**  function in the structure.

**Since:**

1.0

## **Summary**<a name="section1410067533093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table654708763093531"></a>
<table><thead align="left"><tr id="row1937724899093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1827615296093531"><a name="p1827615296093531"></a><a name="p1827615296093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1612335850093531"><a name="p1612335850093531"></a><a name="p1612335850093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row815244577093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1739787204093531"><a name="p1739787204093531"></a><a name="p1739787204093531"></a><a href="IDeviceIoService.md#ae79da6a452d1b93d09f1a034a4a7c8d2">object</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1440431049093531"><a name="p1440431049093531"></a><a name="p1440431049093531"></a>struct <a href="HdfObject.md">HdfObject</a>&nbsp;</p>
</td>
</tr>
<tr id="row411915200093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p23907002093531"><a name="p23907002093531"></a><a name="p23907002093531"></a><a href="IDeviceIoService.md#aa655b184dee58c697cd25c9a7367d401">Open</a> )(struct <a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a> *client)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923107083093531"><a name="p923107083093531"></a><a name="p923107083093531"></a>int32_t(*&nbsp;</p>
<p id="p1575316118093531"><a name="p1575316118093531"></a><a name="p1575316118093531"></a>Called when the driver service is enabled by a user-level application. </p>
</td>
</tr>
<tr id="row1065889639093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897925257093531"><a name="p897925257093531"></a><a name="p897925257093531"></a><a href="IDeviceIoService.md#acbd0a5848800672aaa0048b73ab725c8">Dispatch</a> )(struct <a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a> *client, int cmdId, struct <a href="HdfSBuf.md">HdfSBuf</a> *data, struct <a href="HdfSBuf.md">HdfSBuf</a> *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p753473922093531"><a name="p753473922093531"></a><a name="p753473922093531"></a>int32_t(*&nbsp;</p>
<p id="p1677678208093531"><a name="p1677678208093531"></a><a name="p1677678208093531"></a>Called when the driver service is invoked by a user-level application. </p>
</td>
</tr>
<tr id="row2071438043093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p880343166093531"><a name="p880343166093531"></a><a name="p880343166093531"></a><a href="IDeviceIoService.md#a45681535736fb530c71da45a259aa128">Release</a> )(struct <a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a> *client)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p409660434093531"><a name="p409660434093531"></a><a name="p409660434093531"></a>void(*&nbsp;</p>
<p id="p1178797666093531"><a name="p1178797666093531"></a><a name="p1178797666093531"></a>Called when the driver service is released by a user-level application. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1889724780093531"></a>

## **Field Documentation**<a name="section2074571978093531"></a>

## Dispatch<a name="acbd0a5848800672aaa0048b73ab725c8"></a>

```
int32_t(* IDeviceIoService::Dispatch) (struct [HdfDeviceIoClient](HdfDeviceIoClient.md) *client, int cmdId, struct [HdfSBuf](HdfSBuf.md) *data, struct [HdfSBuf](HdfSBuf.md) *reply)
```

 **Description:**

Called when the driver service is invoked by a user-level application. 

**Parameters:**

<a name="table556069814093531"></a>
<table><thead align="left"><tr id="row2122766139093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1500481834093531"><a name="p1500481834093531"></a><a name="p1500481834093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2076945099093531"><a name="p2076945099093531"></a><a name="p2076945099093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row801673048093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">client</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the client object of the service. </td>
</tr>
<tr id="row371372622093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cmdId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the command word of the service interface. </td>
</tr>
<tr id="row1454843982093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data passed by the invoker. </td>
</tr>
<tr id="row315107108093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">reply</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data that needs to be returned to the invoker. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## object<a name="ae79da6a452d1b93d09f1a034a4a7c8d2"></a>

```
struct [HdfObject](HdfObject.md) IDeviceIoService::object
```

 **Description:**

Driver service object ID 

## Open<a name="aa655b184dee58c697cd25c9a7367d401"></a>

```
int32_t(* IDeviceIoService::Open) (struct [HdfDeviceIoClient](HdfDeviceIoClient.md) *client)
```

 **Description:**

Called when the driver service is enabled by a user-level application. 

**Parameters:**

<a name="table500429541093531"></a>
<table><thead align="left"><tr id="row2017430816093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p122989958093531"><a name="p122989958093531"></a><a name="p122989958093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1239579637093531"><a name="p1239579637093531"></a><a name="p1239579637093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2044755266093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">client</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the client object of the service. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## Release<a name="a45681535736fb530c71da45a259aa128"></a>

```
void(* IDeviceIoService::Release) (struct [HdfDeviceIoClient](HdfDeviceIoClient.md) *client)
```

 **Description:**

Called when the driver service is released by a user-level application. 

**Parameters:**

<a name="table173566066093531"></a>
<table><thead align="left"><tr id="row640506499093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1158299121093531"><a name="p1158299121093531"></a><a name="p1158299121093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p889850179093531"><a name="p889850179093531"></a><a name="p889850179093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1088701668093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">client</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the client object of the service.</td>
</tr>
</tbody>
</table>

