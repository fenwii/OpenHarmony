# InputManager<a name="EN-US_TOPIC_0000001054799601"></a>

## **Overview**<a name="section878781904093530"></a>

**Related Modules:**

[Input](input.md)

**Description:**

Provides interfaces for managing input devices. 

The interfaces can be used to perform basic operations on the input devices, such as opening and closing the device files and querying information about the input device. 

## **Summary**<a name="section1311907669093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table124646860093530"></a>
<table><thead align="left"><tr id="row566375354093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p267664079093530"><a name="p267664079093530"></a><a name="p267664079093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1613400853093530"><a name="p1613400853093530"></a><a name="p1613400853093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row58713760093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1314530444093530"><a name="p1314530444093530"></a><a name="p1314530444093530"></a><a href="inputmanager.md#a9153e901b4811654d8dfc2e78aa29f07">OpenInputDevice</a> )(uint32_t devIndex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1446221317093530"><a name="p1446221317093530"></a><a name="p1446221317093530"></a>int32_t(* </p>
<p id="p1267277819093530"><a name="p1267277819093530"></a><a name="p1267277819093530"></a>Opens a specified input device file. </p>
</td>
</tr>
<tr id="row1737614172093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083449809093530"><a name="p2083449809093530"></a><a name="p2083449809093530"></a><a href="inputmanager.md#a41f3a8a5d8995c9a08bd90c1d367209d">CloseInputDevice</a> )(uint32_t devIndex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2081073080093530"><a name="p2081073080093530"></a><a name="p2081073080093530"></a>int32_t(* </p>
<p id="p1828820790093530"><a name="p1828820790093530"></a><a name="p1828820790093530"></a>Closes a specified input device file. </p>
</td>
</tr>
<tr id="row1597658332093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1172906737093530"><a name="p1172906737093530"></a><a name="p1172906737093530"></a><a href="inputmanager.md#abf32ba302df150d952714776e1707bc5">GetInputDevice</a> )(uint32_t devIndex, <a href="deviceinfo.md">DeviceInfo</a> **devInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p700480360093530"><a name="p700480360093530"></a><a name="p700480360093530"></a>int32_t(* </p>
<p id="p2075215123093530"><a name="p2075215123093530"></a><a name="p2075215123093530"></a>Gets information about a specified input device. </p>
</td>
</tr>
<tr id="row1654362203093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758389927093530"><a name="p758389927093530"></a><a name="p758389927093530"></a><a href="inputmanager.md#a74f11b9e24d19413f5eb9b35700be078">GetInputDeviceList</a> )(uint32_t *devNum, <a href="deviceinfo.md">DeviceInfo</a> **devList, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1409066650093530"><a name="p1409066650093530"></a><a name="p1409066650093530"></a>int32_t(* </p>
<p id="p1080841001093530"><a name="p1080841001093530"></a><a name="p1080841001093530"></a>Gets information about all input devices in the device list. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1051375939093530"></a>

## **Field Documentation**<a name="section184532249093530"></a>

## CloseInputDevice<a name="a41f3a8a5d8995c9a08bd90c1d367209d"></a>

```
int32_t(* InputManager::CloseInputDevice) (uint32_t devIndex)
```

 **Description:**

Closes a specified input device file. 

**Parameters:**

<a name="table926793260093530"></a>
<table><thead align="left"><tr id="row1060271724093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1956077124093530"><a name="p1956077124093530"></a><a name="p1956077124093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p215769271093530"><a name="p215769271093530"></a><a name="p215769271093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row40793774093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1664744801093530"><a name="b1664744801093530"></a><a name="b1664744801093530"></a>0</strong> represents the first input device. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## GetInputDevice<a name="abf32ba302df150d952714776e1707bc5"></a>

```
int32_t(* InputManager::GetInputDevice) (uint32_t devIndex, [DeviceInfo](deviceinfo.md) **devInfo)
```

 **Description:**

Gets information about a specified input device. 

**Parameters:**

<a name="table2105604690093530"></a>
<table><thead align="left"><tr id="row1478856302093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p296159088093530"><a name="p296159088093530"></a><a name="p296159088093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p442950648093530"><a name="p442950648093530"></a><a name="p442950648093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1379609664093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b237568275093530"><a name="b237568275093530"></a><a name="b237568275093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row365698105093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to information about the specified device. For details, see <a href="deviceinfo.md">DeviceInfo</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## GetInputDeviceList<a name="a74f11b9e24d19413f5eb9b35700be078"></a>

```
int32_t(* InputManager::GetInputDeviceList) (uint32_t *devNum, [DeviceInfo](deviceinfo.md) **devList, uint32_t size)
```

 **Description:**

Gets information about all input devices in the device list. 

**Parameters:**

<a name="table1984428354093530"></a>
<table><thead align="left"><tr id="row2108289900093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1607759312093530"><a name="p1607759312093530"></a><a name="p1607759312093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p497404522093530"><a name="p497404522093530"></a><a name="p497404522093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1455970221093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devNum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the total number of input devices which have been registered. </td>
</tr>
<tr id="row8726055093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devList</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to information about all devices in the device list. For details, see <a href="deviceinfo.md">DeviceInfo</a>. </td>
</tr>
<tr id="row1469819980093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of elements in the <strong id="b899706114093530"><a name="b899706114093530"></a><a name="b899706114093530"></a>devList</strong> array. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## OpenInputDevice<a name="a9153e901b4811654d8dfc2e78aa29f07"></a>

```
int32_t(* InputManager::OpenInputDevice) (uint32_t devIndex)
```

 **Description:**

Opens a specified input device file. 

**Parameters:**

<a name="table1921784919093530"></a>
<table><thead align="left"><tr id="row1304247433093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p657643181093530"><a name="p657643181093530"></a><a name="p657643181093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1241705614093530"><a name="p1241705614093530"></a><a name="p1241705614093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row907808251093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b200954485093530"><a name="b200954485093530"></a><a name="b200954485093530"></a>0</strong> represents the first input device. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



