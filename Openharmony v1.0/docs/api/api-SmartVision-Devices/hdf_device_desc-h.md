# hdf\_device\_desc.h<a name="ZH-CN_TOPIC_0000001055678062"></a>

## **Overview**<a name="section1737432962093525"></a>

**Related Modules:**

[Core](Core.md)

**Description:**

Declares functions related to driver loading, service obtaining, and power management. 

**Since:**

1.0

## **Summary**<a name="section1414273757093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1615576317093525"></a>
<table><thead align="left"><tr id="row249312794093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2036701464093525"><a name="p2036701464093525"></a><a name="p2036701464093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1541178526093525"><a name="p1541178526093525"></a><a name="p1541178526093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2105905920093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872112381093525"><a name="p1872112381093525"></a><a name="p1872112381093525"></a><a href="HdfDeviceObject.md">HdfDeviceObject</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p247201228093525"><a name="p247201228093525"></a><a name="p247201228093525"></a>Defines the device object. </p>
</td>
</tr>
<tr id="row996500043093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496364495093525"><a name="p496364495093525"></a><a name="p496364495093525"></a><a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1855460586093525"><a name="p1855460586093525"></a><a name="p1855460586093525"></a>Defines the client object structure of the I/O service. </p>
</td>
</tr>
<tr id="row1144510175093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1009313805093525"><a name="p1009313805093525"></a><a name="p1009313805093525"></a><a href="IDeviceIoService.md">IDeviceIoService</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1291704356093525"><a name="p1291704356093525"></a><a name="p1291704356093525"></a>Defines the driver service. </p>
</td>
</tr>
<tr id="row1808633238093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264834011093525"><a name="p264834011093525"></a><a name="p264834011093525"></a><a href="SubscriberCallback.md">SubscriberCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1503322350093525"><a name="p1503322350093525"></a><a name="p1503322350093525"></a>Called when the driver subscribes to other driver services. </p>
</td>
</tr>
<tr id="row1793067247093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p801873926093525"><a name="p801873926093525"></a><a name="p801873926093525"></a><a href="IPowerEventListener.md">IPowerEventListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498009304093525"><a name="p498009304093525"></a><a name="p498009304093525"></a>Defines the power management functions provided by the HDF for the driver. </p>
</td>
</tr>
<tr id="row423337702093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p562657615093525"><a name="p562657615093525"></a><a name="p562657615093525"></a><a href="HdfDriverEntry.md">HdfDriverEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1719190571093525"><a name="p1719190571093525"></a><a name="p1719190571093525"></a>Defines the entry structure of the driver in the HDF. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table272762568093525"></a>
<table><thead align="left"><tr id="row1447587700093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1047158572093525"><a name="p1047158572093525"></a><a name="p1047158572093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1527894755093525"><a name="p1527894755093525"></a><a name="p1527894755093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row357212175093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p77550075093525"><a name="p77550075093525"></a><a name="p77550075093525"></a><a href="Core.md#ga5957e60db74b1b0703ebd1c53f964d48">MAX_PRIORITY_NUM</a>&nbsp;&nbsp;&nbsp;200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331139774093525"><a name="p1331139774093525"></a><a name="p1331139774093525"></a>The maximum priority for loading the host and device. </p>
</td>
</tr>
<tr id="row1395294998093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1193279969093525"><a name="p1193279969093525"></a><a name="p1193279969093525"></a><a href="Core.md#ga99831072fdca13e3c423a14fa6a83c34">HDF_INIT</a>(module)&nbsp;&nbsp;&nbsp;HDF_DRIVER_INIT(module)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2050599731093525"><a name="p2050599731093525"></a><a name="p2050599731093525"></a>Registers the driver with the HDF. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1826361902093525"></a>
<table><thead align="left"><tr id="row911755256093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p657482174093525"><a name="p657482174093525"></a><a name="p657482174093525"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1688768041093525"><a name="p1688768041093525"></a><a name="p1688768041093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row727936250093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1117127727093525"><a name="p1117127727093525"></a><a name="p1117127727093525"></a><a href="Core.md#ga172844da8a6908bf7226eee703ad9f80">ServicePolicy</a> { &nbsp;&nbsp;<a href="Core.md#gga172844da8a6908bf7226eee703ad9f80aeed8de39f7a8c5a5be1f7b8beb7221e1">SERVICE_POLICY_NONE</a> = 0, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80a5ec1b4a05e5ba37c9bf58f039fe2c245">SERVICE_POLICY_PUBLIC</a>, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80a9a398765ae7bad9ce86e12a91683334c">SERVICE_POLICY_CAPACITY</a>, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80ac2fe21ccc86fbb38747c733716a6b2e0">SERVICE_POLICY_FRIENDLY</a>, &nbsp;&nbsp;<a href="Core.md#gga172844da8a6908bf7226eee703ad9f80ac7918e4a8fa4a2c29ccc8bf97537b61c">SERVICE_POLICY_PRIVATE</a>, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80a423a5d22d00f6a45f0281dd287fc3b4d">SERVICE_POLICY_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85142274093525"><a name="p85142274093525"></a><a name="p85142274093525"></a>Enumerates policies for releasing driver services developed based on the HDF. </p>
</td>
</tr>
<tr id="row270775501093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p933912710093525"><a name="p933912710093525"></a><a name="p933912710093525"></a><a href="Core.md#ga0f3d81b5ff5d3896f7d8cf15f76b451e">DevicePreload</a> { <a href="Core.md#gga0f3d81b5ff5d3896f7d8cf15f76b451ea0fd51c3697833ef66f7ff68adb96a04d">DEVICE_PRELOAD_ENABLE</a> = 0, <a href="Core.md#gga0f3d81b5ff5d3896f7d8cf15f76b451ea2c36597f3f647a621ab56b666ed6cb3e">DEVICE_PRELOAD_DISABLE</a>, <a href="Core.md#gga0f3d81b5ff5d3896f7d8cf15f76b451ea679c4d6dabdd7795bdbfaee5cc26367e">DEVICE_PRELOAD_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p932878422093525"><a name="p932878422093525"></a><a name="p932878422093525"></a>Enumerates driver loading policies. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table570557563093525"></a>
<table><thead align="left"><tr id="row1073209224093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1111635338093525"><a name="p1111635338093525"></a><a name="p1111635338093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p289822128093525"><a name="p289822128093525"></a><a name="p289822128093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row392506183093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p682224968093525"><a name="p682224968093525"></a><a name="p682224968093525"></a><a href="Core.md#gab28c6481fc79bd055e2551abebb841bf">DevSvcManagerClntGetService</a> (const char *svcName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675847843093525"><a name="p675847843093525"></a><a name="p675847843093525"></a>const struct <a href="HdfObject.md">HdfObject</a> *&nbsp;</p>
<p id="p2138887200093525"><a name="p2138887200093525"></a><a name="p2138887200093525"></a>Obtains the driver service object based on a driver service name. </p>
</td>
</tr>
<tr id="row376270575093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1599891838093525"><a name="p1599891838093525"></a><a name="p1599891838093525"></a><a href="Core.md#gac899589dfa47b45f43b8dd027b65b5d9">HdfDeviceGetServiceName</a> (const struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257646452093525"><a name="p257646452093525"></a><a name="p257646452093525"></a>const char *&nbsp;</p>
<p id="p1265963171093525"><a name="p1265963171093525"></a><a name="p1265963171093525"></a>Obtains the service name of a driver. </p>
</td>
</tr>
<tr id="row1835512242093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838331174093525"><a name="p838331174093525"></a><a name="p838331174093525"></a><a href="Core.md#ga224908f55daa1b9553841735e5f1f65c">HdfDeviceSubscribeService</a> (struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject, const char *serviceName, struct <a href="SubscriberCallback.md">SubscriberCallback</a> callback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493516961093525"><a name="p493516961093525"></a><a name="p493516961093525"></a>int32_t&nbsp;</p>
<p id="p2015365149093525"><a name="p2015365149093525"></a><a name="p2015365149093525"></a>Subscribes to a driver service. </p>
</td>
</tr>
<tr id="row1705493351093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073076846093525"><a name="p2073076846093525"></a><a name="p2073076846093525"></a><a href="Core.md#gac9670df1316b5ddd651a50ebee0b6557">HdfDeviceSendEvent</a> (const struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject, uint32_t id, const struct <a href="HdfSBuf.md">HdfSBuf</a> *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061255455093525"><a name="p2061255455093525"></a><a name="p2061255455093525"></a>int32_t&nbsp;</p>
<p id="p828385689093525"><a name="p828385689093525"></a><a name="p828385689093525"></a>Sends event messages. </p>
</td>
</tr>
<tr id="row1452762028093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1508250397093525"><a name="p1508250397093525"></a><a name="p1508250397093525"></a><a href="Core.md#ga9c47da8d82820bce2d32051324480f45">HdfDeviceSendEventToClient</a> (const struct <a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a> *client, uint32_t id, const struct <a href="HdfSBuf.md">HdfSBuf</a> *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2081069927093525"><a name="p2081069927093525"></a><a name="p2081069927093525"></a>int32_t&nbsp;</p>
<p id="p263252430093525"><a name="p263252430093525"></a><a name="p263252430093525"></a>Sends an event message to a specified client object. </p>
</td>
</tr>
</tbody>
</table>

