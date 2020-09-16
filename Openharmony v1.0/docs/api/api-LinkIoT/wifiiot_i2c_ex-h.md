# wifiiot\_i2c\_ex.h<a name="ZH-CN_TOPIC_0000001054476497"></a>

## **Overview**<a name="section546141968090254"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the extended I2C interface functions. 

These functions are used for I2C baud rate setting and device exception callback. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section6931137090254"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table120455103090254"></a>
<table><thead align="left"><tr id="row412950117090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2114037150090254"><a name="p2114037150090254"></a><a name="p2114037150090254"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1845771333090254"><a name="p1845771333090254"></a><a name="p1845771333090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row522704749090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p525403582090254"><a name="p525403582090254"></a><a name="p525403582090254"></a><a href="WifiIotI2cFunc.md">WifiIotI2cFunc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1178357067090254"><a name="p1178357067090254"></a><a name="p1178357067090254"></a>Defines I2C callbacks. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table752362859090254"></a>
<table><thead align="left"><tr id="row1851669680090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1462128290090254"><a name="p1462128290090254"></a><a name="p1462128290090254"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2129263178090254"><a name="p2129263178090254"></a><a name="p2129263178090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row606782986090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901653248090254"><a name="p1901653248090254"></a><a name="p1901653248090254"></a><a href="Wifiiot.md#ga1176c2c06eca906f3e662027df156109">I2CResetFunc</a>) (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p110730136090254"><a name="p110730136090254"></a><a name="p110730136090254"></a>typedef void(*&nbsp;</p>
<p id="p1904008099090254"><a name="p1904008099090254"></a><a name="p1904008099090254"></a>Indicates the callback invoked when a device exception occurs. </p>
</td>
</tr>
<tr id="row1633772608090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1002725206090254"><a name="p1002725206090254"></a><a name="p1002725206090254"></a><a href="Wifiiot.md#ga1f0c8fe1deb1cf1fc8b19d69c2fca729">I2cPrepareFunc</a>) (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p607876226090254"><a name="p607876226090254"></a><a name="p607876226090254"></a>typedef void(*&nbsp;</p>
<p id="p1328378452090254"><a name="p1328378452090254"></a><a name="p1328378452090254"></a>Indicates the callback invoked for device preparation. </p>
</td>
</tr>
<tr id="row1451252445090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883772090090254"><a name="p883772090090254"></a><a name="p883772090090254"></a><a href="Wifiiot.md#ga16779c755404f2ec8543452268a9fb3b">I2cRestoreFunc</a>) (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p663719268090254"><a name="p663719268090254"></a><a name="p663719268090254"></a>typedef void(*&nbsp;</p>
<p id="p1979542557090254"><a name="p1979542557090254"></a><a name="p1979542557090254"></a>Indicates the callback invoked for device recovery. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1472389815090254"></a>
<table><thead align="left"><tr id="row1331520197090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1014737649090254"><a name="p1014737649090254"></a><a name="p1014737649090254"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p42802180090254"><a name="p42802180090254"></a><a name="p42802180090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1067040578090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908694942090254"><a name="p908694942090254"></a><a name="p908694942090254"></a><a href="Wifiiot.md#gae4c60ea6732bbee9f779540cb431fe85">I2cWriteread</a> (<a href="Wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id, unsigned short deviceAddr, const <a href="WifiIotI2cData.md">WifiIotI2cData</a> *i2cData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1691496564090254"><a name="p1691496564090254"></a><a name="p1691496564090254"></a>unsigned int&nbsp;</p>
<p id="p1346621255090254"><a name="p1346621255090254"></a><a name="p1346621255090254"></a>Sends data to and receives data responses from an I2C device. </p>
</td>
</tr>
<tr id="row1000219078090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p594145585090254"><a name="p594145585090254"></a><a name="p594145585090254"></a><a href="Wifiiot.md#ga76d3fad576fe209eedb203bc61ad4f6b">I2cRegisterResetBusFunc</a> (<a href="Wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id, <a href="WifiIotI2cFunc.md">WifiIotI2cFunc</a> pfn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2136536298090254"><a name="p2136536298090254"></a><a name="p2136536298090254"></a>void&nbsp;</p>
<p id="p126479557090254"><a name="p126479557090254"></a><a name="p126479557090254"></a>Registers an I2C callback. </p>
</td>
</tr>
<tr id="row559568445090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425917828090254"><a name="p425917828090254"></a><a name="p425917828090254"></a><a href="Wifiiot.md#gaf4962dc9dd012c125294fe5683955454">I2cSetBaudrate</a> (<a href="Wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id, unsigned int baudrate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1470377029090254"><a name="p1470377029090254"></a><a name="p1470377029090254"></a>unsigned int&nbsp;</p>
<p id="p2026667778090254"><a name="p2026667778090254"></a><a name="p2026667778090254"></a>Sets the baud rate for an I2C device. </p>
</td>
</tr>
</tbody>
</table>

