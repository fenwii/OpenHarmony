# InputController<a name="EN-US_TOPIC_0000001055518090"></a>

## **Overview**<a name="section697437093093530"></a>

**Related Modules:**

[Input](input.md)

**Description:**

Provides interfaces for controlling the business process of input devices. 

The interfaces can be called to control the power status, enable or disable a feature, get driver chip information, and control the production test. 

## **Summary**<a name="section1982707845093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table588765364093530"></a>
<table><thead align="left"><tr id="row1928330313093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p539113854093530"><a name="p539113854093530"></a><a name="p539113854093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p384735120093530"><a name="p384735120093530"></a><a name="p384735120093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row789801098093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1596513748093530"><a name="p1596513748093530"></a><a name="p1596513748093530"></a><a href="inputcontroller.md#a38da915fec2698dff480ed686503f692">SetPowerStatus</a> )(uint32_t devIndex, uint32_t status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646541901093530"><a name="p1646541901093530"></a><a name="p1646541901093530"></a>int32_t(* </p>
<p id="p861265943093530"><a name="p861265943093530"></a><a name="p861265943093530"></a>Sets the power status. </p>
</td>
</tr>
<tr id="row1886202784093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1184408218093530"><a name="p1184408218093530"></a><a name="p1184408218093530"></a><a href="inputcontroller.md#afd9ffc4a180609ad970df6fd79806372">GetPowerStatus</a> )(uint32_t devIndex, uint32_t *status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p208486215093530"><a name="p208486215093530"></a><a name="p208486215093530"></a>int32_t(* </p>
<p id="p1315609162093530"><a name="p1315609162093530"></a><a name="p1315609162093530"></a>Gets the power status. </p>
</td>
</tr>
<tr id="row895538343093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1131216117093530"><a name="p1131216117093530"></a><a name="p1131216117093530"></a><a href="inputcontroller.md#aec8d8a22b37f572a9df8ef7ce988a6d3">GetDeviceType</a> )(uint32_t devIndex, uint32_t *deviceType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701992983093530"><a name="p1701992983093530"></a><a name="p1701992983093530"></a>int32_t(* </p>
<p id="p82170012093530"><a name="p82170012093530"></a><a name="p82170012093530"></a>Gets the type of the input device based on the specified device index. </p>
</td>
</tr>
<tr id="row346466326093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658961123093530"><a name="p658961123093530"></a><a name="p658961123093530"></a><a href="inputcontroller.md#aa02ce599f0383c88e6efc301e31901b8">GetChipInfo</a> )(uint32_t devIndex, char *chipInfo, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941775462093530"><a name="p941775462093530"></a><a name="p941775462093530"></a>int32_t(* </p>
<p id="p248616328093530"><a name="p248616328093530"></a><a name="p248616328093530"></a>Gets the chip information of the specified device. </p>
</td>
</tr>
<tr id="row664935069093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p674704398093530"><a name="p674704398093530"></a><a name="p674704398093530"></a><a href="inputcontroller.md#ab011f8433b9c5aa8493320dac9c4a683">GetVendorName</a> )(uint32_t devIndex, char *vendorName, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p968572583093530"><a name="p968572583093530"></a><a name="p968572583093530"></a>int32_t(* </p>
<p id="p593222362093530"><a name="p593222362093530"></a><a name="p593222362093530"></a>Gets the module vendor name of the specified device. </p>
</td>
</tr>
<tr id="row1530189608093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p100985566093530"><a name="p100985566093530"></a><a name="p100985566093530"></a><a href="inputcontroller.md#aaa131995539b4c0b783cdcbdd67b9687">GetChipName</a> )(uint32_t devIndex, char *chipName, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p933225462093530"><a name="p933225462093530"></a><a name="p933225462093530"></a>int32_t(* </p>
<p id="p322446175093530"><a name="p322446175093530"></a><a name="p322446175093530"></a>Gets the driver chip name of the specified device. </p>
</td>
</tr>
<tr id="row1672577160093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2021711474093530"><a name="p2021711474093530"></a><a name="p2021711474093530"></a><a href="inputcontroller.md#a2a5b24dfc129b58ae4663ca44ab2ad91">SetGestureMode</a> )(uint32_t devIndex, uint32_t gestureMode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1748055144093530"><a name="p1748055144093530"></a><a name="p1748055144093530"></a>int32_t(* </p>
<p id="p938246591093530"><a name="p938246591093530"></a><a name="p938246591093530"></a>Sets the gesture mode. </p>
</td>
</tr>
<tr id="row1765527286093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p303770342093530"><a name="p303770342093530"></a><a name="p303770342093530"></a><a href="inputcontroller.md#afc470fb6e33a07aaa179980a4ded39db">RunCapacitanceTest</a> )(uint32_t devIndex, uint32_t testType, char *result, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485642442093530"><a name="p1485642442093530"></a><a name="p1485642442093530"></a>int32_t(* </p>
<p id="p2070920863093530"><a name="p2070920863093530"></a><a name="p2070920863093530"></a>Conducts a capacitance self-test. </p>
</td>
</tr>
<tr id="row72104589093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944333747093530"><a name="p1944333747093530"></a><a name="p1944333747093530"></a><a href="inputcontroller.md#a19c15b3b535f63fbc4e17bbad24492c9">RunExtraCommand</a> )(uint32_t devIndex, <a href="inputextracmd.md">InputExtraCmd</a> *cmd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1937640403093530"><a name="p1937640403093530"></a><a name="p1937640403093530"></a>int32_t(* </p>
<p id="p1253338651093530"><a name="p1253338651093530"></a><a name="p1253338651093530"></a>Executes the extra command. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1421563314093530"></a>

## **Field Documentation**<a name="section1150626833093530"></a>

## GetChipInfo<a name="aa02ce599f0383c88e6efc301e31901b8"></a>

```
int32_t(* InputController::GetChipInfo) (uint32_t devIndex, char *chipInfo, uint32_t length)
```

 **Description:**

Gets the chip information of the specified device. 

A product is usually equipped with modules and driver ICs provided by multiple vendors. An input service can call this function to get the specific information if needed.

**Parameters:**

<a name="table69695641093530"></a>
<table><thead align="left"><tr id="row856689106093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1847024968093530"><a name="p1847024968093530"></a><a name="p1847024968093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1990890433093530"><a name="p1990890433093530"></a><a name="p1990890433093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2143321405093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1495760722093530"><a name="b1495760722093530"></a><a name="b1495760722093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row1585992065093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">chipInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the chip information. </td>
</tr>
<tr id="row1045530419093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the chip information. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## GetChipName<a name="aaa131995539b4c0b783cdcbdd67b9687"></a>

```
int32_t(* InputController::GetChipName) (uint32_t devIndex, char *chipName, uint32_t length)
```

 **Description:**

Gets the driver chip name of the specified device. 

**Parameters:**

<a name="table1273281644093530"></a>
<table><thead align="left"><tr id="row660332278093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1155212526093530"><a name="p1155212526093530"></a><a name="p1155212526093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1011798820093530"><a name="p1011798820093530"></a><a name="p1011798820093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1995843575093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b257339669093530"><a name="b257339669093530"></a><a name="b257339669093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row739734918093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">chipName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver chip name. </td>
</tr>
<tr id="row1696220219093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the driver chip name. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## GetDeviceType<a name="aec8d8a22b37f572a9df8ef7ce988a6d3"></a>

```
int32_t(* InputController::GetDeviceType) (uint32_t devIndex, uint32_t *deviceType)
```

 **Description:**

Gets the type of the input device based on the specified device index. 

**Parameters:**

<a name="table104342715093530"></a>
<table><thead align="left"><tr id="row1105420135093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p503758972093530"><a name="p503758972093530"></a><a name="p503758972093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p644133137093530"><a name="p644133137093530"></a><a name="p644133137093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1323847672093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1728520093530"><a name="b1728520093530"></a><a name="b1728520093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row492275837093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device type. For details, see <a href="input.md#gaa8225ba155dfa1ef2c4119c832bc4dd3">InputDevType</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## GetPowerStatus<a name="afd9ffc4a180609ad970df6fd79806372"></a>

```
int32_t(* InputController::GetPowerStatus) (uint32_t devIndex, uint32_t *status)
```

 **Description:**

Gets the power status. 

The input service or the power management module can set the power status for the input device when the OS is in the Resume or Suspend status, so that the driver IC of the device can normally enter the specified status. You can call this function to obtain the power status.

**Parameters:**

<a name="table1483665951093530"></a>
<table><thead align="left"><tr id="row14195923093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1458245535093530"><a name="p1458245535093530"></a><a name="p1458245535093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p650724987093530"><a name="p650724987093530"></a><a name="p650724987093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1031976317093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b929800980093530"><a name="b929800980093530"></a><a name="b929800980093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row924712870093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the power status of the device. For details, see <a href="input.md#ga65e6bb4d942c22dba9975253b0a1d73f">PowerStatus</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## GetVendorName<a name="ab011f8433b9c5aa8493320dac9c4a683"></a>

```
int32_t(* InputController::GetVendorName) (uint32_t devIndex, char *vendorName, uint32_t length)
```

 **Description:**

Gets the module vendor name of the specified device. 

**Parameters:**

<a name="table2083527662093530"></a>
<table><thead align="left"><tr id="row1947662634093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1136705219093530"><a name="p1136705219093530"></a><a name="p1136705219093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1478333431093530"><a name="p1478333431093530"></a><a name="p1478333431093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1048804186093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1314711598093530"><a name="b1314711598093530"></a><a name="b1314711598093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row588761981093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">vendorName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module vendor name. </td>
</tr>
<tr id="row1496283923093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the vendor name. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## RunCapacitanceTest<a name="afc470fb6e33a07aaa179980a4ded39db"></a>

```
int32_t(* InputController::RunCapacitanceTest) (uint32_t devIndex, uint32_t testType, char *result, uint32_t length)
```

 **Description:**

Conducts a capacitance self-test. 

The capacitance self-test items are defined by the component vendor, such as the tests on the raw data, short circuit, open circuit, interference, and row/column difference.

**Parameters:**

<a name="table1001200583093530"></a>
<table><thead align="left"><tr id="row466107747093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2062502560093530"><a name="p2062502560093530"></a><a name="p2062502560093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p901812798093530"><a name="p901812798093530"></a><a name="p901812798093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row660227971093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1707476188093530"><a name="b1707476188093530"></a><a name="b1707476188093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row1342370918093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">testType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the capacitance test type. For details, see <a href="input.md#gae96e484cfd64ea37b5b7782f57f38a21">CapacitanceTest</a>. </td>
</tr>
<tr id="row1966970213093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">result</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the capacitance test result. The value is <strong id="b1437488732093530"><a name="b1437488732093530"></a><a name="b1437488732093530"></a>SUCC</strong> for a successful operation and is an error code for a failed operation. </td>
</tr>
<tr id="row1185785293093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the test result. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## RunExtraCommand<a name="a19c15b3b535f63fbc4e17bbad24492c9"></a>

```
int32_t(* InputController::RunExtraCommand) (uint32_t devIndex, [InputExtraCmd](inputextracmd.md) *cmd)
```

 **Description:**

Executes the extra command. 

**Parameters:**

<a name="table1572845133093530"></a>
<table><thead align="left"><tr id="row1512317628093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p693909946093530"><a name="p693909946093530"></a><a name="p693909946093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1935924597093530"><a name="p1935924597093530"></a><a name="p1935924597093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row396536149093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1450822977093530"><a name="b1450822977093530"></a><a name="b1450822977093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row1562231392093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cmd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the extra command data packet, including the command codes and parameters. For details, see <a href="inputextracmd.md">InputExtraCmd</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## SetGestureMode<a name="a2a5b24dfc129b58ae4663ca44ab2ad91"></a>

```
int32_t(* InputController::SetGestureMode) (uint32_t devIndex, uint32_t gestureMode)
```

 **Description:**

Sets the gesture mode. 

The input service can use this function to enable or disable the gesture mode by setting  **EnableBit**  of the gesture mode.

**Parameters:**

<a name="table419826342093530"></a>
<table><thead align="left"><tr id="row1579454552093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p758598910093530"><a name="p758598910093530"></a><a name="p758598910093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p683654500093530"><a name="p683654500093530"></a><a name="p683654500093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row573575260093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b527055708093530"><a name="b527055708093530"></a><a name="b527055708093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row520698610093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gestureMode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the gesture mode to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



## SetPowerStatus<a name="a38da915fec2698dff480ed686503f692"></a>

```
int32_t(* InputController::SetPowerStatus) (uint32_t devIndex, uint32_t status)
```

 **Description:**

Sets the power status. 

This function is called only when the power status of the OS is changed. The input service or the power management module can call this function to set the power status for the input device when the OS is in the Resume or Suspend status, so that the driver integrated circuit \(IC\) of the device can normally enter the specified status. 

**Parameters:**

<a name="table1787836622093530"></a>
<table><thead align="left"><tr id="row108570263093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p77564477093530"><a name="p77564477093530"></a><a name="p77564477093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1795801109093530"><a name="p1795801109093530"></a><a name="p1795801109093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row715871172093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1395435881093530"><a name="b1395435881093530"></a><a name="b1395435881093530"></a>0</strong> represents the first input device. </td>
</tr>
<tr id="row657233899093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the power status to set. The input service will notify the input device of entering the Resume or Suspend state specified by <a href="input.md#ga65e6bb4d942c22dba9975253b0a1d73f">PowerStatus</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



