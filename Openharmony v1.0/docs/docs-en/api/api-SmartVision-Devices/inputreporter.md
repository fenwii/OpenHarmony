# InputReporter<a name="EN-US_TOPIC_0000001054479565"></a>

## **Overview**<a name="section143379340093530"></a>

**Related Modules:**

[Input](input.md)

**Description:**

Provides interfaces for reporting event data of input devices. 

The interfaces include the callback for reporting the input event data and the functions for obtaining the data in polling mode. 

## **Summary**<a name="section1933651002093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table216039712093530"></a>
<table><thead align="left"><tr id="row1978198969093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1793257611093530"><a name="p1793257611093530"></a><a name="p1793257611093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1449898226093530"><a name="p1449898226093530"></a><a name="p1449898226093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row621161935093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p110732521093530"><a name="p110732521093530"></a><a name="p110732521093530"></a><a href="inputreporter.md#a8cbea98a78a293bc8ab6f41c6adeb675">RegisterReportCallback</a> )(uint32_t devIndex, <a href="inputreporteventcb.md">InputReportEventCb</a> *callback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027923516093530"><a name="p1027923516093530"></a><a name="p1027923516093530"></a>int32_t(* </p>
<p id="p904686790093530"><a name="p904686790093530"></a><a name="p904686790093530"></a>Registers a callback for reporting subscribed data of specified input devices. </p>
</td>
</tr>
<tr id="row1080487534093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1959737256093530"><a name="p1959737256093530"></a><a name="p1959737256093530"></a><a href="inputreporter.md#a8c10af61e0c73c91292b806a7ea1d069">UnregisterReportCallback</a> )(uint32_t devIndex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967903278093530"><a name="p967903278093530"></a><a name="p967903278093530"></a>int32_t(* </p>
<p id="p785648154093530"><a name="p785648154093530"></a><a name="p785648154093530"></a>Unregisters the callback for reporting subscribed data of specified input devices. </p>
</td>
</tr>
<tr id="row201733741093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1731558391093530"><a name="p1731558391093530"></a><a name="p1731558391093530"></a><a href="inputreporter.md#a879d9272d932f566e667b7e768b5530e">GetInputEvent</a> )(uint32_t devIndex, <a href="inputeventdata.md">InputEventData</a> *eventData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p32233543093530"><a name="p32233543093530"></a><a name="p32233543093530"></a>int32_t(* </p>
<p id="p433164440093530"><a name="p433164440093530"></a><a name="p433164440093530"></a>Gets the input event data. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1622533260093530"></a>

## **Field Documentation**<a name="section184259465093530"></a>

## GetInputEvent<a name="a879d9272d932f566e667b7e768b5530e"></a>

```
int32_t(* InputReporter::GetInputEvent) (uint32_t devIndex, [InputEventData](inputeventdata.md) *eventData)
```

 **Description:**

Gets the input event data. 

This function enables the input service to proactively obtain the input event data in polling mode.

**Parameters:**

<a name="table356620096093530"></a>
<table><thead align="left"><tr id="row478848716093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p303588463093530"><a name="p303588463093530"></a><a name="p303588463093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1740011501093530"><a name="p1740011501093530"></a><a name="p1740011501093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1423861301093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b895478498093530"><a name="b895478498093530"></a><a name="b895478498093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row1094989499093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">eventData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the input event data reported by the input driver. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## RegisterReportCallback<a name="a8cbea98a78a293bc8ab6f41c6adeb675"></a>

```
int32_t(* InputReporter::RegisterReportCallback) (uint32_t devIndex, [InputReportEventCb](inputreporteventcb.md) *callback)
```

 **Description:**

Registers a callback for reporting subscribed data of specified input devices. 

After this callback is successfully registered, the driver can report the input event data to the input service through this callback.

**Parameters:**

<a name="table1126190846093530"></a>
<table><thead align="left"><tr id="row13701816093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p764532069093530"><a name="p764532069093530"></a><a name="p764532069093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p221575941093530"><a name="p221575941093530"></a><a name="p221575941093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1111091143093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1875289264093530"><a name="b1875289264093530"></a><a name="b1875289264093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row2029515980093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">callback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the callback to register. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## UnregisterReportCallback<a name="a8c10af61e0c73c91292b806a7ea1d069"></a>

```
int32_t(* InputReporter::UnregisterReportCallback) (uint32_t devIndex)
```

 **Description:**

Unregisters the callback for reporting subscribed data of specified input devices. 

**Parameters:**

<a name="table1757421544093530"></a>
<table><thead align="left"><tr id="row2060461188093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p239342790093530"><a name="p239342790093530"></a><a name="p239342790093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1993103579093530"><a name="p1993103579093530"></a><a name="p1993103579093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1557055674093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1825801013093530"><a name="b1825801013093530"></a><a name="b1825801013093530"></a>0</strong> represents the first input device. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



