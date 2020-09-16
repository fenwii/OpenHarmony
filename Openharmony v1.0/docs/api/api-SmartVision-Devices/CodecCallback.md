# CodecCallback<a name="ZH-CN_TOPIC_0000001055358102"></a>

## **Overview**<a name="section87295616093529"></a>

**Related Modules:**

[Codec](Codec.md)

**Description:**

Defines callbacks and their parameters. 

## **Summary**<a name="section521263066093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table789735841093529"></a>
<table><thead align="left"><tr id="row1727490008093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1780348465093529"><a name="p1780348465093529"></a><a name="p1780348465093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p58887533093529"><a name="p58887533093529"></a><a name="p58887533093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2019435105093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858600075093529"><a name="p858600075093529"></a><a name="p858600075093529"></a><a href="CodecCallback.md#a039d0a4af8c4e3d10f49426d46f0b0f3">OnEvent</a> )(<a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> comp, <a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> appData, <a href="Codec.md#ga2628ea8d12e8b2563c32f05dc7fff6fa">EventType</a> event, uint32_t data1, uint32_t data2, <a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> eventData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p781303354093529"><a name="p781303354093529"></a><a name="p781303354093529"></a>int(*&nbsp;</p>
<p id="p1022344303093529"><a name="p1022344303093529"></a><a name="p1022344303093529"></a>Reports an event. </p>
</td>
</tr>
<tr id="row855466205093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p930086669093529"><a name="p930086669093529"></a><a name="p930086669093529"></a><a href="CodecCallback.md#a97ba05617547d79b459bfed6172b4d75">InputBufferAvailable</a> )(<a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> comp, <a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> appData, <a href="InputInfo.md">InputInfo</a> *inBuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p317315628093529"><a name="p317315628093529"></a><a name="p317315628093529"></a>int(*&nbsp;</p>
<p id="p1222664697093529"><a name="p1222664697093529"></a><a name="p1222664697093529"></a>Reports that the input data has been used. </p>
</td>
</tr>
<tr id="row116410082093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1412142815093529"><a name="p1412142815093529"></a><a name="p1412142815093529"></a><a href="CodecCallback.md#ad99eedd9953bdf22e426a181b08b8d0d">OutputBufferAvailable</a> )(<a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> comp, <a href="Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> appData, <a href="OutputInfo.md">OutputInfo</a> *outBuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399460281093529"><a name="p1399460281093529"></a><a name="p1399460281093529"></a>int(*&nbsp;</p>
<p id="p1964008067093529"><a name="p1964008067093529"></a><a name="p1964008067093529"></a>Reports that the output is complete. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1654929580093529"></a>

## **Field Documentation**<a name="section537644690093529"></a>

## InputBufferAvailable<a name="a97ba05617547d79b459bfed6172b4d75"></a>

```
int(* CodecCallback::InputBufferAvailable) ([UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) comp, [UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) appData, [InputInfo](InputInfo.md) *inBuf)
```

 **Description:**

Reports that the input data has been used. 

This callback is invoked in asynchronous mode.

**Parameters:**

<a name="table2026327068093529"></a>
<table><thead align="left"><tr id="row1563919601093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1690930735093529"><a name="p1690930735093529"></a><a name="p1690930735093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1444249441093529"><a name="p1444249441093529"></a><a name="p1444249441093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row402401904093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hComponent</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the handle of the codec component. </td>
</tr>
<tr id="row1509102165093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pAppData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates upper-layer data, which is generally an upper-layer instance passed when this callback is set. </td>
</tr>
<tr id="row1873903997093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pBuffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the input data that has been used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## OnEvent<a name="a039d0a4af8c4e3d10f49426d46f0b0f3"></a>

```
int(* CodecCallback::OnEvent) ([UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) comp, [UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) appData, [EventType](Codec.md#ga2628ea8d12e8b2563c32f05dc7fff6fa) event, uint32_t data1, uint32_t data2, [UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) eventData)
```

 **Description:**

Reports an event. 

Reports event errors and output format changes.

**Parameters:**

<a name="table1937838759093529"></a>
<table><thead align="left"><tr id="row482936026093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1972430986093529"><a name="p1972430986093529"></a><a name="p1972430986093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p552530744093529"><a name="p552530744093529"></a><a name="p552530744093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1609658673093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hComponent</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the handle of the codec component. </td>
</tr>
<tr id="row2117974192093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pAppData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates upper-layer data, which is generally an upper-layer instance passed when this callback is set. </td>
</tr>
<tr id="row2030981122093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">EVENTTYPE</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event type. </td>
</tr>
<tr id="row798984275093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nData1</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the first value contained in the reported event. This parameter is optional. </td>
</tr>
<tr id="row731031831093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nData2</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the second value contained in the reported event. This parameter is optional. </td>
</tr>
<tr id="row860646524093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pEventData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to data contained in the reported event. This parameter is optional. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## OutputBufferAvailable<a name="ad99eedd9953bdf22e426a181b08b8d0d"></a>

```
int(* CodecCallback::OutputBufferAvailable) ([UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) comp, [UINTPTR](Codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) appData, [OutputInfo](OutputInfo.md) *outBuf)
```

 **Description:**

Reports that the output is complete. 

This callback is invoked in asynchronous mode.

**Parameters:**

<a name="table1924364636093529"></a>
<table><thead align="left"><tr id="row372155209093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p428836838093529"><a name="p428836838093529"></a><a name="p428836838093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1989854781093529"><a name="p1989854781093529"></a><a name="p1989854781093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1320293361093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hComponent</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the handle of the codec component. </td>
</tr>
<tr id="row1000675120093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pAppData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates upper-layer data, which is generally an upper-layer instance passed when this callback is registered. </td>
</tr>
<tr id="row741086265093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pBuffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the output data that has been generated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



