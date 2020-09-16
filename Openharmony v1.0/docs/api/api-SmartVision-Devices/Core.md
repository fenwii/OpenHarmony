# Core<a name="ZH-CN_TOPIC_0000001054718073"></a>

## **Overview**<a name="section159915875093520"></a>

Provides OpenHarmony Driver Foundation \(HDF\) APIs. 

The HDF implements driver framework capabilities such as driver loading, service management, and driver message model. You can develop drivers based on the HDF.

**Since:**

1.0

## **Summary**<a name="section220072147093520"></a>

## Files<a name="files"></a>

<a name="table1280572832093520"></a>
<table><thead align="left"><tr id="row1274193222093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p657963093093520"><a name="p657963093093520"></a><a name="p657963093093520"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1396243990093520"><a name="p1396243990093520"></a><a name="p1396243990093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row628382986093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1074243164093520"><a name="p1074243164093520"></a><a name="p1074243164093520"></a><a href="hdf_device_desc-h.md">hdf_device_desc.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p450170528093520"><a name="p450170528093520"></a><a name="p450170528093520"></a>Declares functions related to driver loading, service obtaining, and power management. </p>
</td>
</tr>
<tr id="row1091208480093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2130941053093520"><a name="p2130941053093520"></a><a name="p2130941053093520"></a><a href="hdf_io_service_if-h.md">hdf_io_service_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812542240093520"><a name="p1812542240093520"></a><a name="p1812542240093520"></a>Declares the structures defining driver service objects and event listeners, as well as the functions for obtaining a driver service object, dispatching a driver service call, and registering or unregistering an event listener. </p>
</td>
</tr>
<tr id="row1282720466093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p824572075093520"><a name="p824572075093520"></a><a name="p824572075093520"></a><a href="hdf_object-h.md">hdf_object.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58249150093520"><a name="p58249150093520"></a><a name="p58249150093520"></a>Declares the base object provided by the HDF for the driver. </p>
</td>
</tr>
<tr id="row675173294093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152495271093520"><a name="p1152495271093520"></a><a name="p1152495271093520"></a><a href="hdf_sbuf-h.md">hdf_sbuf.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1896707653093520"><a name="p1896707653093520"></a><a name="p1896707653093520"></a>Defines functions related to a <strong id="b1737075112093520"><a name="b1737075112093520"></a><a name="b1737075112093520"></a><a href="HdfSBuf.md">HdfSBuf</a></strong>. The HDF provides data serialization and deserialization capabilities for data transmission between user-mode applications and kernel-mode drivers. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table2143967733093520"></a>
<table><thead align="left"><tr id="row1593119112093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1552941547093520"><a name="p1552941547093520"></a><a name="p1552941547093520"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1174237824093520"><a name="p1174237824093520"></a><a name="p1174237824093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row385063563093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1409424120093520"><a name="p1409424120093520"></a><a name="p1409424120093520"></a><a href="HdfDeviceObject.md">HdfDeviceObject</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1476269048093520"><a name="p1476269048093520"></a><a name="p1476269048093520"></a>Defines the device object. </p>
</td>
</tr>
<tr id="row848911123093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116966599093520"><a name="p2116966599093520"></a><a name="p2116966599093520"></a><a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851557766093520"><a name="p1851557766093520"></a><a name="p1851557766093520"></a>Defines the client object structure of the I/O service. </p>
</td>
</tr>
<tr id="row1514393508093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1915264128093520"><a name="p1915264128093520"></a><a name="p1915264128093520"></a><a href="IDeviceIoService.md">IDeviceIoService</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1174095247093520"><a name="p1174095247093520"></a><a name="p1174095247093520"></a>Defines the driver service. </p>
</td>
</tr>
<tr id="row1472497538093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858341172093520"><a name="p858341172093520"></a><a name="p858341172093520"></a><a href="SubscriberCallback.md">SubscriberCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2146545058093520"><a name="p2146545058093520"></a><a name="p2146545058093520"></a>Called when the driver subscribes to other driver services. </p>
</td>
</tr>
<tr id="row1467895313093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139408524093520"><a name="p2139408524093520"></a><a name="p2139408524093520"></a><a href="IPowerEventListener.md">IPowerEventListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882466703093520"><a name="p882466703093520"></a><a name="p882466703093520"></a>Defines the power management functions provided by the HDF for the driver. </p>
</td>
</tr>
<tr id="row1327338175093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1572532217093520"><a name="p1572532217093520"></a><a name="p1572532217093520"></a><a href="HdfDriverEntry.md">HdfDriverEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1183513222093520"><a name="p1183513222093520"></a><a name="p1183513222093520"></a>Defines the entry structure of the driver in the HDF. </p>
</td>
</tr>
<tr id="row982150199093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340747327093520"><a name="p1340747327093520"></a><a name="p1340747327093520"></a><a href="HdfDevEventlistener.md">HdfDevEventlistener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79286470093520"><a name="p79286470093520"></a><a name="p79286470093520"></a>Defines a driver event listener object. </p>
</td>
</tr>
<tr id="row2084335610093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1224261164093520"><a name="p1224261164093520"></a><a name="p1224261164093520"></a><a href="HdfIoDispatcher.md">HdfIoDispatcher</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021535799093520"><a name="p2021535799093520"></a><a name="p2021535799093520"></a>Defines a driver service call dispatcher. </p>
</td>
</tr>
<tr id="row12294622093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p736031344093520"><a name="p736031344093520"></a><a name="p736031344093520"></a><a href="HdfIoService.md">HdfIoService</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1584817460093520"><a name="p1584817460093520"></a><a name="p1584817460093520"></a>Defines a driver service object. </p>
</td>
</tr>
<tr id="row1251356955093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p522719899093520"><a name="p522719899093520"></a><a name="p522719899093520"></a><a href="HdfObject.md">HdfObject</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p651001588093520"><a name="p651001588093520"></a><a name="p651001588093520"></a>Describes base class objects defined by the HDF. </p>
</td>
</tr>
<tr id="row1919394093093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p915132851093520"><a name="p915132851093520"></a><a name="p915132851093520"></a><a href="HdfSBuf.md">HdfSBuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2091269350093520"><a name="p2091269350093520"></a><a name="p2091269350093520"></a>Defines a <strong id="b1044096059093520"><a name="b1044096059093520"></a><a name="b1044096059093520"></a><a href="HdfSBuf.md">HdfSBuf</a></strong>. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table76455774093520"></a>
<table><thead align="left"><tr id="row119884794093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1008990009093520"><a name="p1008990009093520"></a><a name="p1008990009093520"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p624464990093520"><a name="p624464990093520"></a><a name="p624464990093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row335879575093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2061474992093520"><a name="p2061474992093520"></a><a name="p2061474992093520"></a><em id="ga5957e60db74b1b0703ebd1c53f964d48"><a name="ga5957e60db74b1b0703ebd1c53f964d48"></a><a name="ga5957e60db74b1b0703ebd1c53f964d48"></a></em>MAX_PRIORITY_NUM &nbsp;&nbsp;&nbsp;200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033476149093520"><a name="p2033476149093520"></a><a name="p2033476149093520"></a>The maximum priority for loading the host and device. </p>
</td>
</tr>
<tr id="row1868032789093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p138828708093520"><a name="p138828708093520"></a><a name="p138828708093520"></a><a href="Core.md#ga99831072fdca13e3c423a14fa6a83c34">HDF_INIT</a>(module)&nbsp;&nbsp;&nbsp;HDF_DRIVER_INIT(module)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p56090990093520"><a name="p56090990093520"></a><a name="p56090990093520"></a>Registers the driver with the HDF. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table483831516093520"></a>
<table><thead align="left"><tr id="row474000123093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1434949191093520"><a name="p1434949191093520"></a><a name="p1434949191093520"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p78403676093520"><a name="p78403676093520"></a><a name="p78403676093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row117936737093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p168682151093520"><a name="p168682151093520"></a><a name="p168682151093520"></a><a href="Core.md#gae314b850ba4b0927007038cf8cc32580">OnEventReceived</a>) (void *priv, uint32_t id, struct <a href="HdfSBuf.md">HdfSBuf</a> *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462899077093520"><a name="p1462899077093520"></a><a name="p1462899077093520"></a>typedef int(*&nbsp;</p>
<p id="p680101924093520"><a name="p680101924093520"></a><a name="p680101924093520"></a>Called when a driver event occurs. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table646736647093520"></a>
<table><thead align="left"><tr id="row30276813093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p320116503093520"><a name="p320116503093520"></a><a name="p320116503093520"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p423441895093520"><a name="p423441895093520"></a><a name="p423441895093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1837450865093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p116734746093520"><a name="p116734746093520"></a><a name="p116734746093520"></a><a href="Core.md#ga172844da8a6908bf7226eee703ad9f80">ServicePolicy</a> { &nbsp;&nbsp;<a href="Core.md#gga172844da8a6908bf7226eee703ad9f80aeed8de39f7a8c5a5be1f7b8beb7221e1">SERVICE_POLICY_NONE</a> = 0, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80a5ec1b4a05e5ba37c9bf58f039fe2c245">SERVICE_POLICY_PUBLIC</a>, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80a9a398765ae7bad9ce86e12a91683334c">SERVICE_POLICY_CAPACITY</a>, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80ac2fe21ccc86fbb38747c733716a6b2e0">SERVICE_POLICY_FRIENDLY</a>, &nbsp;&nbsp;<a href="Core.md#gga172844da8a6908bf7226eee703ad9f80ac7918e4a8fa4a2c29ccc8bf97537b61c">SERVICE_POLICY_PRIVATE</a>, <a href="Core.md#gga172844da8a6908bf7226eee703ad9f80a423a5d22d00f6a45f0281dd287fc3b4d">SERVICE_POLICY_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1355269588093520"><a name="p1355269588093520"></a><a name="p1355269588093520"></a>Enumerates policies for releasing driver services developed based on the HDF. </p>
</td>
</tr>
<tr id="row826510488093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p36948161093520"><a name="p36948161093520"></a><a name="p36948161093520"></a><a href="Core.md#ga0f3d81b5ff5d3896f7d8cf15f76b451e">DevicePreload</a> { <a href="Core.md#gga0f3d81b5ff5d3896f7d8cf15f76b451ea0fd51c3697833ef66f7ff68adb96a04d">DEVICE_PRELOAD_ENABLE</a> = 0, <a href="Core.md#gga0f3d81b5ff5d3896f7d8cf15f76b451ea2c36597f3f647a621ab56b666ed6cb3e">DEVICE_PRELOAD_DISABLE</a>, <a href="Core.md#gga0f3d81b5ff5d3896f7d8cf15f76b451ea679c4d6dabdd7795bdbfaee5cc26367e">DEVICE_PRELOAD_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922383314093520"><a name="p922383314093520"></a><a name="p922383314093520"></a>Enumerates driver loading policies. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1030204112093520"></a>
<table><thead align="left"><tr id="row659038987093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1475537620093520"><a name="p1475537620093520"></a><a name="p1475537620093520"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p683361160093520"><a name="p683361160093520"></a><a name="p683361160093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1070143246093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1486262894093520"><a name="p1486262894093520"></a><a name="p1486262894093520"></a><a href="Core.md#gab28c6481fc79bd055e2551abebb841bf">DevSvcManagerClntGetService</a> (const char *svcName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296366009093520"><a name="p1296366009093520"></a><a name="p1296366009093520"></a>const struct <a href="HdfObject.md">HdfObject</a> *&nbsp;</p>
<p id="p189531101093520"><a name="p189531101093520"></a><a name="p189531101093520"></a>Obtains the driver service object based on a driver service name. </p>
</td>
</tr>
<tr id="row1444193638093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1975946739093520"><a name="p1975946739093520"></a><a name="p1975946739093520"></a><a href="Core.md#gac899589dfa47b45f43b8dd027b65b5d9">HdfDeviceGetServiceName</a> (const struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884796540093520"><a name="p1884796540093520"></a><a name="p1884796540093520"></a>const char *&nbsp;</p>
<p id="p2113557171093520"><a name="p2113557171093520"></a><a name="p2113557171093520"></a>Obtains the service name of a driver. </p>
</td>
</tr>
<tr id="row1596975947093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p487523592093520"><a name="p487523592093520"></a><a name="p487523592093520"></a><a href="Core.md#ga224908f55daa1b9553841735e5f1f65c">HdfDeviceSubscribeService</a> (struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject, const char *serviceName, struct <a href="SubscriberCallback.md">SubscriberCallback</a> callback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1692875014093520"><a name="p1692875014093520"></a><a name="p1692875014093520"></a>int32_t&nbsp;</p>
<p id="p1837164470093520"><a name="p1837164470093520"></a><a name="p1837164470093520"></a>Subscribes to a driver service. </p>
</td>
</tr>
<tr id="row553293963093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1066728465093520"><a name="p1066728465093520"></a><a name="p1066728465093520"></a><a href="Core.md#gac9670df1316b5ddd651a50ebee0b6557">HdfDeviceSendEvent</a> (const struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject, uint32_t id, const struct <a href="HdfSBuf.md">HdfSBuf</a> *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720343804093520"><a name="p1720343804093520"></a><a name="p1720343804093520"></a>int32_t&nbsp;</p>
<p id="p550379745093520"><a name="p550379745093520"></a><a name="p550379745093520"></a>Sends event messages. </p>
</td>
</tr>
<tr id="row543432741093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p880034953093520"><a name="p880034953093520"></a><a name="p880034953093520"></a><a href="Core.md#ga9c47da8d82820bce2d32051324480f45">HdfDeviceSendEventToClient</a> (const struct <a href="HdfDeviceIoClient.md">HdfDeviceIoClient</a> *client, uint32_t id, const struct <a href="HdfSBuf.md">HdfSBuf</a> *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1192586522093520"><a name="p1192586522093520"></a><a name="p1192586522093520"></a>int32_t&nbsp;</p>
<p id="p1708702328093520"><a name="p1708702328093520"></a><a name="p1708702328093520"></a>Sends an event message to a specified client object. </p>
</td>
</tr>
<tr id="row250911761093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p4825961093520"><a name="p4825961093520"></a><a name="p4825961093520"></a><a href="Core.md#gac250f27d434eafce709a7e03411ef4d1">HdfIoServiceBind</a> (const char *serviceName, mode_t permission)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327018475093520"><a name="p1327018475093520"></a><a name="p1327018475093520"></a>struct <a href="HdfIoService.md">HdfIoService</a> *&nbsp;</p>
<p id="p1971854366093520"><a name="p1971854366093520"></a><a name="p1971854366093520"></a>Obtains a driver service object. </p>
</td>
</tr>
<tr id="row1649827025093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p914866231093520"><a name="p914866231093520"></a><a name="p914866231093520"></a><a href="Core.md#gada2867af690aac9e6c3b2c8812b3037c">HdfIoServiceRecycle</a> (struct <a href="HdfIoService.md">HdfIoService</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1504312473093520"><a name="p1504312473093520"></a><a name="p1504312473093520"></a>void&nbsp;</p>
<p id="p729873681093520"><a name="p729873681093520"></a><a name="p729873681093520"></a>Destroys a specified driver service object to release resources if it is no longer required. </p>
</td>
</tr>
<tr id="row508343294093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p734899807093520"><a name="p734899807093520"></a><a name="p734899807093520"></a><a href="Core.md#gaa7855b3930b5378954927548e5623663">HdfDeviceRegisterEventListener</a> (struct <a href="HdfIoService.md">HdfIoService</a> *target, struct <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2079131701093520"><a name="p2079131701093520"></a><a name="p2079131701093520"></a>int&nbsp;</p>
<p id="p677498777093520"><a name="p677498777093520"></a><a name="p677498777093520"></a>Registers a custom <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> for listening for events reported by a specified driver service object. </p>
</td>
</tr>
<tr id="row1502100807093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p306362439093520"><a name="p306362439093520"></a><a name="p306362439093520"></a><a href="Core.md#gab95668359f0b6a47f48c47541caed7fd">HdfDeviceUnregisterEventListener</a> (struct <a href="HdfIoService.md">HdfIoService</a> *target, struct <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p364382841093520"><a name="p364382841093520"></a><a name="p364382841093520"></a>int&nbsp;</p>
<p id="p2091842107093520"><a name="p2091842107093520"></a><a name="p2091842107093520"></a>Unregisters a previously registered <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> to release resources if it is no longer required. </p>
</td>
</tr>
<tr id="row2007347045093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685485392093520"><a name="p1685485392093520"></a><a name="p1685485392093520"></a><a href="Core.md#ga567eb533aa53051d0beec43f08e72dd8">HdfSbufWriteBuffer</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, const void *data, uint32_t writeSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348555644093520"><a name="p348555644093520"></a><a name="p348555644093520"></a>bool&nbsp;</p>
<p id="p1018455157093520"><a name="p1018455157093520"></a><a name="p1018455157093520"></a>Writes a data segment to a <strong id="b681463242093520"><a name="b681463242093520"></a><a name="b681463242093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1606764786093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953661182093520"><a name="p953661182093520"></a><a name="p953661182093520"></a><a href="Core.md#ga164de95ad00302b599290bdb476a032f">HdfSbufWriteUint64</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861519527093520"><a name="p861519527093520"></a><a name="p861519527093520"></a>bool&nbsp;</p>
<p id="p1560074898093520"><a name="p1560074898093520"></a><a name="p1560074898093520"></a>Writes a 64-bit unsigned integer to a <strong id="b807279493093520"><a name="b807279493093520"></a><a name="b807279493093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row309023482093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p515776657093520"><a name="p515776657093520"></a><a name="p515776657093520"></a><a href="Core.md#ga23f2331cdfb0bf91a29f47f20ffd50df">HdfSbufWriteUint32</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864637412093520"><a name="p1864637412093520"></a><a name="p1864637412093520"></a>bool&nbsp;</p>
<p id="p998693082093520"><a name="p998693082093520"></a><a name="p998693082093520"></a>Writes a 32-bit unsigned integer to a <strong id="b856814164093520"><a name="b856814164093520"></a><a name="b856814164093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1591884551093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527170410093520"><a name="p1527170410093520"></a><a name="p1527170410093520"></a><a href="Core.md#ga31c9edfd9b20d6e44d34839efa0e08f7">HdfSbufWriteUint16</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615140291093520"><a name="p615140291093520"></a><a name="p615140291093520"></a>bool&nbsp;</p>
<p id="p1006884126093520"><a name="p1006884126093520"></a><a name="p1006884126093520"></a>Writes a 16-bit unsigned integer to a <strong id="b477361686093520"><a name="b477361686093520"></a><a name="b477361686093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row64218046093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p771762676093520"><a name="p771762676093520"></a><a name="p771762676093520"></a><a href="Core.md#gafb4fe74246f85a158c140bf4c4951256">HdfSbufWriteUint8</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703071233093520"><a name="p1703071233093520"></a><a name="p1703071233093520"></a>bool&nbsp;</p>
<p id="p785829199093520"><a name="p785829199093520"></a><a name="p785829199093520"></a>Writes an 8-bit unsigned integer to a <strong id="b1820952276093520"><a name="b1820952276093520"></a><a name="b1820952276093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row2027029978093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1070266701093520"><a name="p1070266701093520"></a><a name="p1070266701093520"></a><a href="Core.md#ga7c63eb006b19e2aac43c23318c4ebe3b">HdfSbufWriteInt64</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p834404245093520"><a name="p834404245093520"></a><a name="p834404245093520"></a>bool&nbsp;</p>
<p id="p1064865379093520"><a name="p1064865379093520"></a><a name="p1064865379093520"></a>Writes a 64-bit signed integer to a <strong id="b630275438093520"><a name="b630275438093520"></a><a name="b630275438093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row835543831093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295943886093520"><a name="p295943886093520"></a><a name="p295943886093520"></a><a href="Core.md#ga3913510d670da2f8ffa3103b5ff293f1">HdfSbufWriteInt32</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287730276093520"><a name="p287730276093520"></a><a name="p287730276093520"></a>bool&nbsp;</p>
<p id="p389594582093520"><a name="p389594582093520"></a><a name="p389594582093520"></a>Writes a 32-bit signed integer to a <strong id="b2097533918093520"><a name="b2097533918093520"></a><a name="b2097533918093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row453878089093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p349804135093520"><a name="p349804135093520"></a><a name="p349804135093520"></a><a href="Core.md#gaaa278bf9aa182a4c65c390c6c9ff06d2">HdfSbufWriteInt16</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164675014093520"><a name="p1164675014093520"></a><a name="p1164675014093520"></a>bool&nbsp;</p>
<p id="p310351269093520"><a name="p310351269093520"></a><a name="p310351269093520"></a>Writes a 16-bit signed integer to a <strong id="b164299085093520"><a name="b164299085093520"></a><a name="b164299085093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1425799531093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p613204392093520"><a name="p613204392093520"></a><a name="p613204392093520"></a><a href="Core.md#gac514c3debd605043ad1bfa9c05a115a0">HdfSbufWriteInt8</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327929283093520"><a name="p327929283093520"></a><a name="p327929283093520"></a>bool&nbsp;</p>
<p id="p1313338697093520"><a name="p1313338697093520"></a><a name="p1313338697093520"></a>Writes an 8-bit signed integer to a <strong id="b1836763553093520"><a name="b1836763553093520"></a><a name="b1836763553093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1546914537093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2054546720093520"><a name="p2054546720093520"></a><a name="p2054546720093520"></a><a href="Core.md#gaf782f8a08dcd81f4038ab9d9bbc1cf9b">HdfSbufWriteString</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1611197882093520"><a name="p1611197882093520"></a><a name="p1611197882093520"></a>bool&nbsp;</p>
<p id="p832986348093520"><a name="p832986348093520"></a><a name="p832986348093520"></a>Writes a string to a <strong id="b1621130374093520"><a name="b1621130374093520"></a><a name="b1621130374093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1933518964093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1187486099093520"><a name="p1187486099093520"></a><a name="p1187486099093520"></a><a href="Core.md#ga345e8524a6cea44a0424e23b8f659792">HdfSbufReadBuffer</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, const void **data, uint32_t *readSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851421692093520"><a name="p1851421692093520"></a><a name="p1851421692093520"></a>bool&nbsp;</p>
<p id="p2079189638093520"><a name="p2079189638093520"></a><a name="p2079189638093520"></a>Reads a data segment from a <strong id="b1063619289093520"><a name="b1063619289093520"></a><a name="b1063619289093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row904075811093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p750691210093520"><a name="p750691210093520"></a><a name="p750691210093520"></a><a href="Core.md#gabb10a71c031d3633c5745ba6fd62b0a4">HdfSbufReadUint64</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint64_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201508702093520"><a name="p1201508702093520"></a><a name="p1201508702093520"></a>bool&nbsp;</p>
<p id="p394402085093520"><a name="p394402085093520"></a><a name="p394402085093520"></a>Reads a 64-bit unsigned integer from a <strong id="b1745988956093520"><a name="b1745988956093520"></a><a name="b1745988956093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1184814336093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414794883093520"><a name="p414794883093520"></a><a name="p414794883093520"></a><a href="Core.md#gac953788575b0c22947f18fa9f19a5bf5">HdfSbufReadUint32</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint32_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p717312933093520"><a name="p717312933093520"></a><a name="p717312933093520"></a>bool&nbsp;</p>
<p id="p1595366348093520"><a name="p1595366348093520"></a><a name="p1595366348093520"></a>Reads a 32-bit unsigned integer from a <strong id="b791182444093520"><a name="b791182444093520"></a><a name="b791182444093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1233688988093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1602396031093520"><a name="p1602396031093520"></a><a name="p1602396031093520"></a><a href="Core.md#gabc151ad38bdecd5589623a6298c31930">HdfSbufReadUint16</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint16_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p562776251093520"><a name="p562776251093520"></a><a name="p562776251093520"></a>bool&nbsp;</p>
<p id="p1029806643093520"><a name="p1029806643093520"></a><a name="p1029806643093520"></a>Reads a 16-bit unsigned integer from a <strong id="b1553210562093520"><a name="b1553210562093520"></a><a name="b1553210562093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1137585627093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2101765651093520"><a name="p2101765651093520"></a><a name="p2101765651093520"></a><a href="Core.md#ga07d93e6bcd8a6a8646067783d6f46e74">HdfSbufReadUint8</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, uint8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751031205093520"><a name="p1751031205093520"></a><a name="p1751031205093520"></a>bool&nbsp;</p>
<p id="p147826289093520"><a name="p147826289093520"></a><a name="p147826289093520"></a>Reads an 8-bit unsigned integer from a <strong id="b1878761464093520"><a name="b1878761464093520"></a><a name="b1878761464093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1763892452093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p840269357093520"><a name="p840269357093520"></a><a name="p840269357093520"></a><a href="Core.md#ga7fb121b4351f85e1735c6e63a5c951cc">HdfSbufReadInt64</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int64_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p692494166093520"><a name="p692494166093520"></a><a name="p692494166093520"></a>bool&nbsp;</p>
<p id="p42152142093520"><a name="p42152142093520"></a><a name="p42152142093520"></a>Reads a 64-bit signed integer from a <strong id="b1891825427093520"><a name="b1891825427093520"></a><a name="b1891825427093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1895711021093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367402086093520"><a name="p1367402086093520"></a><a name="p1367402086093520"></a><a href="Core.md#ga22e7b97735f54e57c0d3bed2fa3a47c4">HdfSbufReadInt32</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int32_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1981433277093520"><a name="p1981433277093520"></a><a name="p1981433277093520"></a>bool&nbsp;</p>
<p id="p2031486761093520"><a name="p2031486761093520"></a><a name="p2031486761093520"></a>Reads a 32-bit signed integer from a <strong id="b1886069066093520"><a name="b1886069066093520"></a><a name="b1886069066093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1704345073093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217590151093520"><a name="p1217590151093520"></a><a name="p1217590151093520"></a><a href="Core.md#ga3fce62cbc34a70259d21399d5ff91b32">HdfSbufReadInt16</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int16_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809732583093520"><a name="p1809732583093520"></a><a name="p1809732583093520"></a>bool&nbsp;</p>
<p id="p2019008455093520"><a name="p2019008455093520"></a><a name="p2019008455093520"></a>Reads a 16-bit signed integer from a <strong id="b1540845616093520"><a name="b1540845616093520"></a><a name="b1540845616093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row739043620093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315183937093520"><a name="p315183937093520"></a><a name="p315183937093520"></a><a href="Core.md#gafff778f76f9142602ef25e8afff47c83">HdfSbufReadInt8</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf, int8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1390571798093520"><a name="p1390571798093520"></a><a name="p1390571798093520"></a>bool&nbsp;</p>
<p id="p1305969119093520"><a name="p1305969119093520"></a><a name="p1305969119093520"></a>Reads an 8-bit signed integer from a <strong id="b862949664093520"><a name="b862949664093520"></a><a name="b862949664093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row865075820093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p972951365093520"><a name="p972951365093520"></a><a name="p972951365093520"></a><a href="Core.md#gab03aa25c90fda50138496b0f874a664e">HdfSbufReadString</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p363152515093520"><a name="p363152515093520"></a><a name="p363152515093520"></a>const char *&nbsp;</p>
<p id="p466804159093520"><a name="p466804159093520"></a><a name="p466804159093520"></a>Reads a string from a <strong id="b914437600093520"><a name="b914437600093520"></a><a name="b914437600093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1467573994093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298071089093520"><a name="p298071089093520"></a><a name="p298071089093520"></a><a href="Core.md#ga3f4f5fdb03f64c23f318ecf7c602ac59">HdfSbufGetData</a> (const struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1668192986093520"><a name="p1668192986093520"></a><a name="p1668192986093520"></a>uint8_t *&nbsp;</p>
<p id="p1472392481093520"><a name="p1472392481093520"></a><a name="p1472392481093520"></a>Obtains the pointer to the data stored in a<strong id="b1333959275093520"><a name="b1333959275093520"></a><a name="b1333959275093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row302514878093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1002365273093520"><a name="p1002365273093520"></a><a name="p1002365273093520"></a><a href="Core.md#ga2b7a5750bf42151edd7bd686fb11a39d">HdfSbufFlush</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899285636093520"><a name="p899285636093520"></a><a name="p899285636093520"></a>void&nbsp;</p>
<p id="p1324966914093520"><a name="p1324966914093520"></a><a name="p1324966914093520"></a>Clears the data stored in a <strong id="b231818209093520"><a name="b231818209093520"></a><a name="b231818209093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row2286515093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1968359768093520"><a name="p1968359768093520"></a><a name="p1968359768093520"></a><a href="Core.md#ga74941de5883ae39cb6103591f67dbea0">HdfSbufGetCapacity</a> (const struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554208969093520"><a name="p554208969093520"></a><a name="p554208969093520"></a>size_t&nbsp;</p>
<p id="p761852378093520"><a name="p761852378093520"></a><a name="p761852378093520"></a>Obtains the capacity of a <strong id="b39746532093520"><a name="b39746532093520"></a><a name="b39746532093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1978256895093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496940954093520"><a name="p1496940954093520"></a><a name="p1496940954093520"></a><a href="Core.md#gaf983c174acfb5b1f8f9dc5b6c2f52e0d">HdfSbufGetDataSize</a> (const struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711307407093520"><a name="p711307407093520"></a><a name="p711307407093520"></a>size_t&nbsp;</p>
<p id="p1539811479093520"><a name="p1539811479093520"></a><a name="p1539811479093520"></a>Obtains the size of the data stored in a <strong id="b1025325508093520"><a name="b1025325508093520"></a><a name="b1025325508093520"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1020173126093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p900592811093520"><a name="p900592811093520"></a><a name="p900592811093520"></a><a href="Core.md#ga5e3dee8b1a2128da70cc5718b631c8ba">HdfSBufObtain</a> (size_t capacity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p631391287093520"><a name="p631391287093520"></a><a name="p631391287093520"></a>struct <a href="HdfSBuf.md">HdfSBuf</a> *&nbsp;</p>
<p id="p618785474093520"><a name="p618785474093520"></a><a name="p618785474093520"></a>Obtains a <strong id="b1304101305093520"><a name="b1304101305093520"></a><a name="b1304101305093520"></a>SBuf</strong> instance. </p>
</td>
</tr>
<tr id="row1864858179093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111762597093520"><a name="p111762597093520"></a><a name="p111762597093520"></a><a href="Core.md#ga479315c09d0d927aa211de829388122d">HdfSBufObtainDefaultSize</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399500253093520"><a name="p1399500253093520"></a><a name="p1399500253093520"></a>struct <a href="HdfSBuf.md">HdfSBuf</a> *&nbsp;</p>
<p id="p178197027093520"><a name="p178197027093520"></a><a name="p178197027093520"></a>Obtains a <strong id="b190832915093520"><a name="b190832915093520"></a><a name="b190832915093520"></a>SBuf</strong> instance of the default capacity (256 bytes). </p>
</td>
</tr>
<tr id="row1102938505093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870733785093520"><a name="p1870733785093520"></a><a name="p1870733785093520"></a><a href="Core.md#gabcc9a442a3b2615828d60a1d4664b4a9">HdfSBufBind</a> (uintptr_t base, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1998507815093520"><a name="p1998507815093520"></a><a name="p1998507815093520"></a>struct <a href="HdfSBuf.md">HdfSBuf</a> *&nbsp;</p>
<p id="p1201249096093520"><a name="p1201249096093520"></a><a name="p1201249096093520"></a>Creates a <strong id="b1418226026093520"><a name="b1418226026093520"></a><a name="b1418226026093520"></a>SBuf</strong> instance with the specified data and size. The pointer to the data stored in the <strong id="b534722274093520"><a name="b534722274093520"></a><a name="b534722274093520"></a>SBuf</strong> is released by the caller, and the written data size should not exceed the specified value of <strong id="b1198983910093520"><a name="b1198983910093520"></a><a name="b1198983910093520"></a>size</strong>. </p>
</td>
</tr>
<tr id="row751226359093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946699056093520"><a name="p946699056093520"></a><a name="p946699056093520"></a><a href="Core.md#gaa0041d238cfc7cf00779191aa58e7ee0">HdfSBufRecycle</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124122358093520"><a name="p124122358093520"></a><a name="p124122358093520"></a>void&nbsp;</p>
<p id="p1175489627093520"><a name="p1175489627093520"></a><a name="p1175489627093520"></a>Releases a <strong id="b485594666093520"><a name="b485594666093520"></a><a name="b485594666093520"></a>SBuf </strong>. </p>
</td>
</tr>
<tr id="row842889593093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1803366112093520"><a name="p1803366112093520"></a><a name="p1803366112093520"></a><a href="Core.md#ga22d4a953c89a941337e593647ebe2f5b">HdfSBufMove</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p389082311093520"><a name="p389082311093520"></a><a name="p389082311093520"></a>struct <a href="HdfSBuf.md">HdfSBuf</a> *&nbsp;</p>
<p id="p137432256093520"><a name="p137432256093520"></a><a name="p137432256093520"></a>Creates a <strong id="b941555039093520"><a name="b941555039093520"></a><a name="b941555039093520"></a>SBuf</strong> instance with an original <strong id="b809228131093520"><a name="b809228131093520"></a><a name="b809228131093520"></a>SBuf</strong>. This function moves the data stored in the original <strong id="b1169849203093520"><a name="b1169849203093520"></a><a name="b1169849203093520"></a>SBuf</strong> to the new one without memory copy. </p>
</td>
</tr>
<tr id="row1930037521093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1866486347093520"><a name="p1866486347093520"></a><a name="p1866486347093520"></a><a href="Core.md#ga406275df686ff556fd5bdb20349e4972">HdfSBufCopy</a> (const struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p406053276093520"><a name="p406053276093520"></a><a name="p406053276093520"></a>struct <a href="HdfSBuf.md">HdfSBuf</a> *&nbsp;</p>
<p id="p538848196093520"><a name="p538848196093520"></a><a name="p538848196093520"></a>Creates a <strong id="b1543823289093520"><a name="b1543823289093520"></a><a name="b1543823289093520"></a>SBuf</strong> instance with an original <strong id="b2082507324093520"><a name="b2082507324093520"></a><a name="b2082507324093520"></a>SBuf</strong>. This function copies the data stored in the original <strong id="b1561712374093520"><a name="b1561712374093520"></a><a name="b1561712374093520"></a>SBuf</strong> to the new one. </p>
</td>
</tr>
<tr id="row670914511093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390297569093520"><a name="p390297569093520"></a><a name="p390297569093520"></a><a href="Core.md#gaf391e9f47cc668daf3150c00f369bf1f">HdfSbufTransDataOwnership</a> (struct <a href="HdfSBuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p995143175093520"><a name="p995143175093520"></a><a name="p995143175093520"></a>void&nbsp;</p>
<p id="p1020468416093520"><a name="p1020468416093520"></a><a name="p1020468416093520"></a>Transfers the data ownership to a <strong id="b1853609631093520"><a name="b1853609631093520"></a><a name="b1853609631093520"></a>SBuf</strong>. Once the <strong id="b1923945424093520"><a name="b1923945424093520"></a><a name="b1923945424093520"></a>SBuf</strong> is released, the bound data memory is also released. This function is used together with <a href="Core.md#gabcc9a442a3b2615828d60a1d4664b4a9">HdfSBufBind</a>. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1986207385093520"></a>

## **Macro Definition Documentation**<a name="section2092081455093520"></a>

## HDF\_INIT<a name="ga99831072fdca13e3c423a14fa6a83c34"></a>

```
#define HDF_INIT( module)   HDF_DRIVER_INIT(module)
```

 **Description:**

Registers the driver with the HDF. 

For a driver developed based on the HDF,  [HDF\_INIT](Core.md#ga99831072fdca13e3c423a14fa6a83c34)  must be used to register an entry with the HDF, and the registered object must be of the  [HdfDriverEntry](HdfDriverEntry.md)  type.

**Parameters:**

<a name="table1591905727093520"></a>
<table><thead align="left"><tr id="row1275486152093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2011605630093520"><a name="p2011605630093520"></a><a name="p2011605630093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1574015004093520"><a name="p1574015004093520"></a><a name="p1574015004093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1455532031093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">module</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the global variable of the <a href="HdfDriverEntry.md">HdfDriverEntry</a> type</td>
</tr>
</tbody>
</table>

## **Typedef Documentation**<a name="section142559424093520"></a>

## OnEventReceived<a name="gae314b850ba4b0927007038cf8cc32580"></a>

```
typedef int(* OnEventReceived) (void *priv, uint32_t id, struct [HdfSBuf](HdfSBuf.md) *data)
```

 **Description:**

Called when a driver event occurs. 

You can implement this function and bind it to the custom  [HdfDevEventlistener](HdfDevEventlistener.md)  object. 

**Parameters:**

<a name="table1954702115093520"></a>
<table><thead align="left"><tr id="row620368304093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p844114073093520"><a name="p844114073093520"></a><a name="p844114073093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1364529410093520"><a name="p1364529410093520"></a><a name="p1364529410093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row162908869093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priv</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the private data bound to this listener. </td>
</tr>
<tr id="row28972035093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the serial number of the driver event occurred. </td>
</tr>
<tr id="row1657659784093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the content data of the driver event. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## **Enumeration Type Documentation**<a name="section676884263093520"></a>

## DevicePreload<a name="ga0f3d81b5ff5d3896f7d8cf15f76b451e"></a>

```
enum [DevicePreload](Core.md#ga0f3d81b5ff5d3896f7d8cf15f76b451e)
```

 **Description:**

Enumerates driver loading policies. 

If a driver developed based on the HDF needs to use the on-demand loading mechanism in the HDF, the  **PRELOAD**  field must be correctly set in the driver configuration information to control the driver loading mode.

<a name="table101577989093520"></a>
<table><thead align="left"><tr id="row865607444093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2017569624093520"><a name="p2017569624093520"></a><a name="p2017569624093520"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p773699882093520"><a name="p773699882093520"></a><a name="p773699882093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row917191010093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0f3d81b5ff5d3896f7d8cf15f76b451ea0fd51c3697833ef66f7ff68adb96a04d"><a name="gga0f3d81b5ff5d3896f7d8cf15f76b451ea0fd51c3697833ef66f7ff68adb96a04d"></a><a name="gga0f3d81b5ff5d3896f7d8cf15f76b451ea0fd51c3697833ef66f7ff68adb96a04d"></a></strong>DEVICE_PRELOAD_ENABLE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p932157411093520"><a name="p932157411093520"></a><a name="p932157411093520"></a>The driver is loaded during system startup by default. </p>
 </td>
</tr>
<tr id="row1988285196093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0f3d81b5ff5d3896f7d8cf15f76b451ea2c36597f3f647a621ab56b666ed6cb3e"><a name="gga0f3d81b5ff5d3896f7d8cf15f76b451ea2c36597f3f647a621ab56b666ed6cb3e"></a><a name="gga0f3d81b5ff5d3896f7d8cf15f76b451ea2c36597f3f647a621ab56b666ed6cb3e"></a></strong>DEVICE_PRELOAD_DISABLE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p534646180093520"><a name="p534646180093520"></a><a name="p534646180093520"></a>The driver is not loaded during system startup by default. </p>
 </td>
</tr>
<tr id="row1938534211093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0f3d81b5ff5d3896f7d8cf15f76b451ea679c4d6dabdd7795bdbfaee5cc26367e"><a name="gga0f3d81b5ff5d3896f7d8cf15f76b451ea679c4d6dabdd7795bdbfaee5cc26367e"></a><a name="gga0f3d81b5ff5d3896f7d8cf15f76b451ea679c4d6dabdd7795bdbfaee5cc26367e"></a></strong>DEVICE_PRELOAD_INVALID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1329548132093520"><a name="p1329548132093520"></a><a name="p1329548132093520"></a>The loading policy is incorrect. </p>
 </td>
</tr>
</tbody>
</table>

## ServicePolicy<a name="ga172844da8a6908bf7226eee703ad9f80"></a>

```
enum [ServicePolicy](Core.md#ga172844da8a6908bf7226eee703ad9f80)
```

 **Description:**

Enumerates policies for releasing driver services developed based on the HDF. 

If a driver is developed based on the HDF and uses the service management feature of the HDF, you need to configure the policy for releasing services to external systems.

<a name="table1008739459093520"></a>
<table><thead align="left"><tr id="row2070319444093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p82557312093520"><a name="p82557312093520"></a><a name="p82557312093520"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p862628876093520"><a name="p862628876093520"></a><a name="p862628876093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row997427100093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga172844da8a6908bf7226eee703ad9f80aeed8de39f7a8c5a5be1f7b8beb7221e1"><a name="gga172844da8a6908bf7226eee703ad9f80aeed8de39f7a8c5a5be1f7b8beb7221e1"></a><a name="gga172844da8a6908bf7226eee703ad9f80aeed8de39f7a8c5a5be1f7b8beb7221e1"></a></strong>SERVICE_POLICY_NONE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420693139093520"><a name="p1420693139093520"></a><a name="p1420693139093520"></a>The driver does not provide services externally. </p>
 </td>
</tr>
<tr id="row816456922093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga172844da8a6908bf7226eee703ad9f80a5ec1b4a05e5ba37c9bf58f039fe2c245"><a name="gga172844da8a6908bf7226eee703ad9f80a5ec1b4a05e5ba37c9bf58f039fe2c245"></a><a name="gga172844da8a6908bf7226eee703ad9f80a5ec1b4a05e5ba37c9bf58f039fe2c245"></a></strong>SERVICE_POLICY_PUBLIC&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2122409495093520"><a name="p2122409495093520"></a><a name="p2122409495093520"></a>The driver provides services for kernel-level applications. </p>
 </td>
</tr>
<tr id="row1299608875093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga172844da8a6908bf7226eee703ad9f80a9a398765ae7bad9ce86e12a91683334c"><a name="gga172844da8a6908bf7226eee703ad9f80a9a398765ae7bad9ce86e12a91683334c"></a><a name="gga172844da8a6908bf7226eee703ad9f80a9a398765ae7bad9ce86e12a91683334c"></a></strong>SERVICE_POLICY_CAPACITY&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2049773383093520"><a name="p2049773383093520"></a><a name="p2049773383093520"></a>The driver provides services for both kernel- and user-level applications. </p>
 </td>
</tr>
<tr id="row1169738604093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga172844da8a6908bf7226eee703ad9f80ac2fe21ccc86fbb38747c733716a6b2e0"><a name="gga172844da8a6908bf7226eee703ad9f80ac2fe21ccc86fbb38747c733716a6b2e0"></a><a name="gga172844da8a6908bf7226eee703ad9f80ac2fe21ccc86fbb38747c733716a6b2e0"></a></strong>SERVICE_POLICY_FRIENDLY&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1655795303093520"><a name="p1655795303093520"></a><a name="p1655795303093520"></a>Driver services are not released externally but can be subscribed to. </p>
 </td>
</tr>
<tr id="row1249272668093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga172844da8a6908bf7226eee703ad9f80ac7918e4a8fa4a2c29ccc8bf97537b61c"><a name="gga172844da8a6908bf7226eee703ad9f80ac7918e4a8fa4a2c29ccc8bf97537b61c"></a><a name="gga172844da8a6908bf7226eee703ad9f80ac7918e4a8fa4a2c29ccc8bf97537b61c"></a></strong>SERVICE_POLICY_PRIVATE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492804247093520"><a name="p492804247093520"></a><a name="p492804247093520"></a>Driver services are only internally available. They are not released externally and cannot be subscribed to by external users. </p>
 </td>
</tr>
<tr id="row2113931703093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga172844da8a6908bf7226eee703ad9f80a423a5d22d00f6a45f0281dd287fc3b4d"><a name="gga172844da8a6908bf7226eee703ad9f80a423a5d22d00f6a45f0281dd287fc3b4d"></a><a name="gga172844da8a6908bf7226eee703ad9f80a423a5d22d00f6a45f0281dd287fc3b4d"></a></strong>SERVICE_POLICY_INVALID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1696397999093520"><a name="p1696397999093520"></a><a name="p1696397999093520"></a>The service policy is incorrect. </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section10179672093520"></a>

## DevSvcManagerClntGetService\(\)<a name="gab28c6481fc79bd055e2551abebb841bf"></a>

```
const struct [HdfObject](HdfObject.md)* DevSvcManagerClntGetService (const char * svcName)
```

 **Description:**

Obtains the driver service object based on a driver service name. 

**Parameters:**

<a name="table1444245509093520"></a>
<table><thead align="left"><tr id="row937894434093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p751625154093520"><a name="p751625154093520"></a><a name="p751625154093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p733888455093520"><a name="p733888455093520"></a><a name="p733888455093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row674358553093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">serviceName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the released driver service name.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the driver service object if the operation is successful; returns  **NULL**  otherwise. 



## HdfDeviceGetServiceName\(\)<a name="gac899589dfa47b45f43b8dd027b65b5d9"></a>

```
const char* HdfDeviceGetServiceName (const struct [HdfDeviceObject](HdfDeviceObject.md) * deviceObject)
```

 **Description:**

Obtains the service name of a driver. 

If a driver does not save its service name, it can use this function to obtain the service name. 

**Parameters:**

<a name="table1051426897093520"></a>
<table><thead align="left"><tr id="row430345579093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1339534490093520"><a name="p1339534490093520"></a><a name="p1339534490093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1109512164093520"><a name="p1109512164093520"></a><a name="p1109512164093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row489255912093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceObject</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver device object.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the service name if the operation is successful; returns  **NULL**  otherwise. 



## HdfDeviceRegisterEventListener\(\)<a name="gaa7855b3930b5378954927548e5623663"></a>

```
int HdfDeviceRegisterEventListener (struct [HdfIoService](HdfIoService.md) * target, struct [HdfDevEventlistener](HdfDevEventlistener.md) * listener )
```

 **Description:**

Registers a custom  [HdfDevEventlistener](HdfDevEventlistener.md)  for listening for events reported by a specified driver service object. 

**Parameters:**

<a name="table1957924252093520"></a>
<table><thead align="left"><tr id="row440261375093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1533376141093520"><a name="p1533376141093520"></a><a name="p1533376141093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p474737843093520"><a name="p474737843093520"></a><a name="p474737843093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1857998876093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">target</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver service object to listen, which is obtained through the <a href="Core.md#gac250f27d434eafce709a7e03411ef4d1">HdfIoServiceBind</a> function. </td>
</tr>
<tr id="row1737320949093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">listener</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the listener to register. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## HdfDeviceSendEvent\(\)<a name="gac9670df1316b5ddd651a50ebee0b6557"></a>

```
int32_t HdfDeviceSendEvent (const struct [HdfDeviceObject](HdfDeviceObject.md) * deviceObject, uint32_t id, const struct [HdfSBuf](HdfSBuf.md) * data )
```

 **Description:**

Sends event messages. 

When the driver service invokes this function to send a message, all user-level applications that have registered listeners through  [HdfDeviceRegisterEventListener](Core.md#gaa7855b3930b5378954927548e5623663)  will receive the message.

**Parameters:**

<a name="table1534359986093520"></a>
<table><thead align="left"><tr id="row173167593093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p452320181093520"><a name="p452320181093520"></a><a name="p452320181093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p567288812093520"><a name="p567288812093520"></a><a name="p567288812093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row598098507093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceObject</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver device object. </td>
</tr>
<tr id="row1513806347093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the message sending event. </td>
</tr>
<tr id="row295569020093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the message content sent by the driver.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## HdfDeviceSendEventToClient\(\)<a name="ga9c47da8d82820bce2d32051324480f45"></a>

```
int32_t HdfDeviceSendEventToClient (const struct [HdfDeviceIoClient](HdfDeviceIoClient.md) * client, uint32_t id, const struct [HdfSBuf](HdfSBuf.md) * data )
```

 **Description:**

Sends an event message to a specified client object. 

When the driver service invokes this function to send a message, the user-level applications that have registered listeners through  [HdfDeviceRegisterEventListener](Core.md#gaa7855b3930b5378954927548e5623663)  and correspond to this client object will receive the message.

**Parameters:**

<a name="table1049326834093520"></a>
<table><thead align="left"><tr id="row1912519129093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1004395837093520"><a name="p1004395837093520"></a><a name="p1004395837093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1467824149093520"><a name="p1467824149093520"></a><a name="p1467824149093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row617061970093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">client</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the client object of the driver service. </td>
</tr>
<tr id="row162501748093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the message sending event. </td>
</tr>
<tr id="row20784777093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the message content sent by the driver.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## HdfDeviceSubscribeService\(\)<a name="ga224908f55daa1b9553841735e5f1f65c"></a>

```
int32_t HdfDeviceSubscribeService (struct [HdfDeviceObject](HdfDeviceObject.md) * deviceObject, const char * serviceName, struct [SubscriberCallback](SubscriberCallback.md) callback )
```

 **Description:**

Subscribes to a driver service. 

If the driver loading time is not perceived, this function can be used to subscribe to the driver service. \(The driver service and the subscriber must be on the same host.\) After the subscribed-to driver service is loaded by the HDF, the framework proactively releases the service interface to the subscriber. 

**Parameters:**

<a name="table646114309093520"></a>
<table><thead align="left"><tr id="row199960324093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1879131321093520"><a name="p1879131321093520"></a><a name="p1879131321093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1610342655093520"><a name="p1610342655093520"></a><a name="p1610342655093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2033789380093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceObject</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver device object of the subscriber. </td>
</tr>
<tr id="row1831475765093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">serviceName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver service name. </td>
</tr>
<tr id="row2079845930093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">callback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback invoked by the HDF after the subscribed-to driver service is loaded.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## HdfDeviceUnregisterEventListener\(\)<a name="gab95668359f0b6a47f48c47541caed7fd"></a>

```
int HdfDeviceUnregisterEventListener (struct [HdfIoService](HdfIoService.md) * target, struct [HdfDevEventlistener](HdfDevEventlistener.md) * listener )
```

 **Description:**

Unregisters a previously registered  [HdfDevEventlistener](HdfDevEventlistener.md)  to release resources if it is no longer required. 

**Parameters:**

<a name="table1309934865093520"></a>
<table><thead align="left"><tr id="row1861891144093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1268954052093520"><a name="p1268954052093520"></a><a name="p1268954052093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1718422134093520"><a name="p1718422134093520"></a><a name="p1718422134093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1042472410093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">target</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver service object that has been listened. </td>
</tr>
<tr id="row1874985683093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">listener</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the listener object registered by <a href="Core.md#gaa7855b3930b5378954927548e5623663">HdfDeviceRegisterEventListener</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## HdfIoServiceBind\(\)<a name="gac250f27d434eafce709a7e03411ef4d1"></a>

```
struct [HdfIoService](HdfIoService.md)* HdfIoServiceBind (const char * serviceName, mode_t permission )
```

 **Description:**

Obtains a driver service object. 

**Parameters:**

<a name="table958448496093520"></a>
<table><thead align="left"><tr id="row297343767093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1165879004093520"><a name="p1165879004093520"></a><a name="p1165879004093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1863069537093520"><a name="p1863069537093520"></a><a name="p1863069537093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1519965661093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">serviceName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the service to obtain. </td>
</tr>
<tr id="row597039278093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permission</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the permission to create device nodes. The default value <strong id="b1538012578093520"><a name="b1538012578093520"></a><a name="b1538012578093520"></a>0</strong> can be used when this function is called from user space. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the driver service object if the operation is successful; returns  **NULL**  otherwise.



## HdfIoServiceRecycle\(\)<a name="gada2867af690aac9e6c3b2c8812b3037c"></a>

```
void HdfIoServiceRecycle (struct [HdfIoService](HdfIoService.md) * service)
```

 **Description:**

Destroys a specified driver service object to release resources if it is no longer required. 

**Parameters:**

<a name="table836563591093520"></a>
<table><thead align="left"><tr id="row431169115093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1392011169093520"><a name="p1392011169093520"></a><a name="p1392011169093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p416031243093520"><a name="p416031243093520"></a><a name="p416031243093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row204590272093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the driver service object to destroy.</td>
</tr>
</tbody>
</table>

## HdfSBufBind\(\)<a name="gabcc9a442a3b2615828d60a1d4664b4a9"></a>

```
struct [HdfSBuf](HdfSBuf.md)* HdfSBufBind (uintptr_t base, size_t size )
```

 **Description:**

Creates a  **SBuf**  instance with the specified data and size. The pointer to the data stored in the  **SBuf**  is released by the caller, and the written data size should not exceed the specified value of  **size**. 

**Parameters:**

<a name="table1434570985093520"></a>
<table><thead align="left"><tr id="row1397099745093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1816544648093520"><a name="p1816544648093520"></a><a name="p1816544648093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1641321084093520"><a name="p1641321084093520"></a><a name="p1641321084093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1292878246093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">base</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the base of the data to use. </td>
</tr>
<tr id="row1497214182093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the data to use. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **SBuf**  instance.



## HdfSBufCopy\(\)<a name="ga406275df686ff556fd5bdb20349e4972"></a>

```
struct [HdfSBuf](HdfSBuf.md)* HdfSBufCopy (const struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Creates a  **SBuf**  instance with an original  **SBuf**. This function copies the data stored in the original  **SBuf**  to the new one. 

**Parameters:**

<a name="table1495658844093520"></a>
<table><thead align="left"><tr id="row758960149093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p719909649093520"><a name="p719909649093520"></a><a name="p719909649093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1285286086093520"><a name="p1285286086093520"></a><a name="p1285286086093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1411880681093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original <strong id="b1697462513093520"><a name="b1697462513093520"></a><a name="b1697462513093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the new  **SBuf**  instance.



## HdfSbufFlush\(\)<a name="ga2b7a5750bf42151edd7bd686fb11a39d"></a>

```
void HdfSbufFlush (struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Clears the data stored in a  **SBuf**. 

**Parameters:**

<a name="table1252645161093520"></a>
<table><thead align="left"><tr id="row1421592856093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1980562563093520"><a name="p1980562563093520"></a><a name="p1980562563093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1238747411093520"><a name="p1238747411093520"></a><a name="p1238747411093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row495986533093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b752073733093520"><a name="b752073733093520"></a><a name="b752073733093520"></a>SBuf</strong>.</td>
</tr>
</tbody>
</table>

## HdfSbufGetCapacity\(\)<a name="ga74941de5883ae39cb6103591f67dbea0"></a>

```
size_t HdfSbufGetCapacity (const struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Obtains the capacity of a  **SBuf**. 

**Parameters:**

<a name="table1241004132093520"></a>
<table><thead align="left"><tr id="row2137124208093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2076998132093520"><a name="p2076998132093520"></a><a name="p2076998132093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2083831368093520"><a name="p2083831368093520"></a><a name="p2083831368093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1203238946093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1390810570093520"><a name="b1390810570093520"></a><a name="b1390810570093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **SBuf**  capacity. 



## HdfSbufGetData\(\)<a name="ga3f4f5fdb03f64c23f318ecf7c602ac59"></a>

```
uint8_t* HdfSbufGetData (const struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Obtains the pointer to the data stored in a**SBuf**. 

**Parameters:**

<a name="table1166569159093520"></a>
<table><thead align="left"><tr id="row1434410207093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p89890874093520"><a name="p89890874093520"></a><a name="p89890874093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p74389923093520"><a name="p74389923093520"></a><a name="p74389923093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1124007861093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b405226209093520"><a name="b405226209093520"></a><a name="b405226209093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the data stored in the target  **SBuf**.



## HdfSbufGetDataSize\(\)<a name="gaf983c174acfb5b1f8f9dc5b6c2f52e0d"></a>

```
size_t HdfSbufGetDataSize (const struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Obtains the size of the data stored in a  **SBuf**. 

**Parameters:**

<a name="table280744867093520"></a>
<table><thead align="left"><tr id="row1529760323093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1701095838093520"><a name="p1701095838093520"></a><a name="p1701095838093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p957224889093520"><a name="p957224889093520"></a><a name="p957224889093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2036451074093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1081057093520"><a name="b1081057093520"></a><a name="b1081057093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the data size.



## HdfSBufMove\(\)<a name="ga22d4a953c89a941337e593647ebe2f5b"></a>

```
struct [HdfSBuf](HdfSBuf.md)* HdfSBufMove (struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Creates a  **SBuf**  instance with an original  **SBuf**. This function moves the data stored in the original  **SBuf**  to the new one without memory copy. 

**Parameters:**

<a name="table695093094093520"></a>
<table><thead align="left"><tr id="row843869908093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p901860975093520"><a name="p901860975093520"></a><a name="p901860975093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p307381701093520"><a name="p307381701093520"></a><a name="p307381701093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row598804287093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original <strong id="b1380668251093520"><a name="b1380668251093520"></a><a name="b1380668251093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the new  **SBuf**  instance.



## HdfSBufObtain\(\)<a name="ga5e3dee8b1a2128da70cc5718b631c8ba"></a>

```
struct [HdfSBuf](HdfSBuf.md)* HdfSBufObtain (size_t capacity)
```

 **Description:**

Obtains a  **SBuf**  instance. 

**Parameters:**

<a name="table1075900968093520"></a>
<table><thead align="left"><tr id="row1438722681093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p322830453093520"><a name="p322830453093520"></a><a name="p322830453093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p316262134093520"><a name="p316262134093520"></a><a name="p316262134093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1592356188093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">capacity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the initial capacity of the<strong id="b1256669093093520"><a name="b1256669093093520"></a><a name="b1256669093093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **SBuf**  instance.



## HdfSBufObtainDefaultSize\(\)<a name="ga479315c09d0d927aa211de829388122d"></a>

```
struct [HdfSBuf](HdfSBuf.md)* HdfSBufObtainDefaultSize (void )
```

 **Description:**

Obtains a  **SBuf**  instance of the default capacity \(256 bytes\). 

**Returns:**

Returns the  **SBuf**  instance.



## HdfSbufReadBuffer\(\)<a name="ga345e8524a6cea44a0424e23b8f659792"></a>

```
bool HdfSbufReadBuffer (struct [HdfSBuf](HdfSBuf.md) * sbuf, const void ** data, uint32_t * readSize )
```

 **Description:**

Reads a data segment from a  **SBuf**. 

**Parameters:**

<a name="table1296437508093520"></a>
<table><thead align="left"><tr id="row13815134093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1012761570093520"><a name="p1012761570093520"></a><a name="p1012761570093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2135614177093520"><a name="p2135614177093520"></a><a name="p2135614177093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1297875876093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1742507757093520"><a name="b1742507757093520"></a><a name="b1742507757093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1097662621093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the data read. The data read is stored in <strong id="b1770560517093520"><a name="b1770560517093520"></a><a name="b1770560517093520"></a>*data</strong>, which is requested by the caller. The memory pointed to by <strong id="b1392784079093520"><a name="b1392784079093520"></a><a name="b1392784079093520"></a>*data</strong> is managed by the <strong id="b1946861985093520"><a name="b1946861985093520"></a><a name="b1946861985093520"></a>SBuf</strong> and they share the same lifecycle. </td>
</tr>
<tr id="row252068993093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">readSize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the size of the data read. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadInt16\(\)<a name="ga3fce62cbc34a70259d21399d5ff91b32"></a>

```
bool HdfSbufReadInt16 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int16_t * value )
```

 **Description:**

Reads a 16-bit signed integer from a  **SBuf**. 

**Parameters:**

<a name="table1461489747093520"></a>
<table><thead align="left"><tr id="row1077280459093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p110914656093520"><a name="p110914656093520"></a><a name="p110914656093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p66907188093520"><a name="p66907188093520"></a><a name="p66907188093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1786599404093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b2019164033093520"><a name="b2019164033093520"></a><a name="b2019164033093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1510001678093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 16-bit signed integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadInt32\(\)<a name="ga22e7b97735f54e57c0d3bed2fa3a47c4"></a>

```
bool HdfSbufReadInt32 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int32_t * value )
```

 **Description:**

Reads a 32-bit signed integer from a  **SBuf**. 

**Parameters:**

<a name="table1255553038093520"></a>
<table><thead align="left"><tr id="row1287625142093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1628213651093520"><a name="p1628213651093520"></a><a name="p1628213651093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1630089518093520"><a name="p1630089518093520"></a><a name="p1630089518093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1177187202093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b783662837093520"><a name="b783662837093520"></a><a name="b783662837093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row326383138093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 32-bit signed integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadInt64\(\)<a name="ga7fb121b4351f85e1735c6e63a5c951cc"></a>

```
bool HdfSbufReadInt64 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int64_t * value )
```

 **Description:**

Reads a 64-bit signed integer from a  **SBuf**. 

**Parameters:**

<a name="table1652817178093520"></a>
<table><thead align="left"><tr id="row1811522055093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p594361441093520"><a name="p594361441093520"></a><a name="p594361441093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1015368981093520"><a name="p1015368981093520"></a><a name="p1015368981093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row733402487093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b732129867093520"><a name="b732129867093520"></a><a name="b732129867093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1781781604093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 64-bit signed integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadInt8\(\)<a name="gafff778f76f9142602ef25e8afff47c83"></a>

```
bool HdfSbufReadInt8 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int8_t * value )
```

 **Description:**

Reads an 8-bit signed integer from a  **SBuf**. 

**Parameters:**

<a name="table439621743093520"></a>
<table><thead align="left"><tr id="row1640453247093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p451836395093520"><a name="p451836395093520"></a><a name="p451836395093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1126200555093520"><a name="p1126200555093520"></a><a name="p1126200555093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row256768427093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1184761011093520"><a name="b1184761011093520"></a><a name="b1184761011093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1292680563093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 8-bit signed integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadString\(\)<a name="gab03aa25c90fda50138496b0f874a664e"></a>

```
const char* HdfSbufReadString (struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Reads a string from a  **SBuf**. 

**Parameters:**

<a name="table619116537093520"></a>
<table><thead align="left"><tr id="row662961178093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1030845599093520"><a name="p1030845599093520"></a><a name="p1030845599093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1900865127093520"><a name="p1900865127093520"></a><a name="p1900865127093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row621313280093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b188331748093520"><a name="b188331748093520"></a><a name="b188331748093520"></a>SBuf</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the string read if the operation is successful; returns  **NULL**  otherwise. The memory pointed to by this pointer is managed by the  **SBuf**  and they share the same lifecycle.



## HdfSbufReadUint16\(\)<a name="gabc151ad38bdecd5589623a6298c31930"></a>

```
bool HdfSbufReadUint16 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint16_t * value )
```

 **Description:**

Reads a 16-bit unsigned integer from a  **SBuf**. 

**Parameters:**

<a name="table1039159996093520"></a>
<table><thead align="left"><tr id="row1142972188093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1606436049093520"><a name="p1606436049093520"></a><a name="p1606436049093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1199783921093520"><a name="p1199783921093520"></a><a name="p1199783921093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row797227575093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b483253304093520"><a name="b483253304093520"></a><a name="b483253304093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row626045310093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 16-bit unsigned integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadUint32\(\)<a name="gac953788575b0c22947f18fa9f19a5bf5"></a>

```
bool HdfSbufReadUint32 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint32_t * value )
```

 **Description:**

Reads a 32-bit unsigned integer from a  **SBuf**. 

**Parameters:**

<a name="table520832944093520"></a>
<table><thead align="left"><tr id="row1764219508093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p777045275093520"><a name="p777045275093520"></a><a name="p777045275093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p825614948093520"><a name="p825614948093520"></a><a name="p825614948093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1384298060093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b501744050093520"><a name="b501744050093520"></a><a name="b501744050093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row418682058093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 32-bit unsigned integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadUint64\(\)<a name="gabb10a71c031d3633c5745ba6fd62b0a4"></a>

```
bool HdfSbufReadUint64 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint64_t * value )
```

 **Description:**

Reads a 64-bit unsigned integer from a  **SBuf**. 

**Parameters:**

<a name="table1780111408093520"></a>
<table><thead align="left"><tr id="row797236490093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p817562233093520"><a name="p817562233093520"></a><a name="p817562233093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1586372843093520"><a name="p1586372843093520"></a><a name="p1586372843093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row281850972093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1719414858093520"><a name="b1719414858093520"></a><a name="b1719414858093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1464459262093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 64-bit unsigned integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufReadUint8\(\)<a name="ga07d93e6bcd8a6a8646067783d6f46e74"></a>

```
bool HdfSbufReadUint8 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint8_t * value )
```

 **Description:**

Reads an 8-bit unsigned integer from a  **SBuf**. 

**Parameters:**

<a name="table2086147610093520"></a>
<table><thead align="left"><tr id="row1408486935093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2050064845093520"><a name="p2050064845093520"></a><a name="p2050064845093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p728694712093520"><a name="p728694712093520"></a><a name="p728694712093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1735976906093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1934840241093520"><a name="b1934840241093520"></a><a name="b1934840241093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row571135069093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the 8-bit unsigned integer read, which is requested by the caller. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSBufRecycle\(\)<a name="gaa0041d238cfc7cf00779191aa58e7ee0"></a>

```
void HdfSBufRecycle (struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Releases a  **SBuf **. 

**Parameters:**

<a name="table529273952093520"></a>
<table><thead align="left"><tr id="row1069116824093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p280890878093520"><a name="p280890878093520"></a><a name="p280890878093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p159617533093520"><a name="p159617533093520"></a><a name="p159617533093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row374127302093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1317691314093520"><a name="b1317691314093520"></a><a name="b1317691314093520"></a>SBuf</strong> to release.</td>
</tr>
</tbody>
</table>

## HdfSbufTransDataOwnership\(\)<a name="gaf391e9f47cc668daf3150c00f369bf1f"></a>

```
void HdfSbufTransDataOwnership (struct [HdfSBuf](HdfSBuf.md) * sbuf)
```

 **Description:**

Transfers the data ownership to a  **SBuf**. Once the  **SBuf**  is released, the bound data memory is also released. This function is used together with  [HdfSBufBind](Core.md#gabcc9a442a3b2615828d60a1d4664b4a9). 

**Parameters:**

<a name="table100381321093520"></a>
<table><thead align="left"><tr id="row497620957093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1662199348093520"><a name="p1662199348093520"></a><a name="p1662199348093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1725563679093520"><a name="p1725563679093520"></a><a name="p1725563679093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1588729365093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1523914331093520"><a name="b1523914331093520"></a><a name="b1523914331093520"></a>SBuf</strong>.</td>
</tr>
</tbody>
</table>

## HdfSbufWriteBuffer\(\)<a name="ga567eb533aa53051d0beec43f08e72dd8"></a>

```
bool HdfSbufWriteBuffer (struct [HdfSBuf](HdfSBuf.md) * sbuf, const void * data, uint32_t writeSize )
```

 **Description:**

Writes a data segment to a  **SBuf**. 

**Parameters:**

<a name="table2030308957093520"></a>
<table><thead align="left"><tr id="row474570369093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1287260439093520"><a name="p1287260439093520"></a><a name="p1287260439093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1638797912093520"><a name="p1638797912093520"></a><a name="p1638797912093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1952629546093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b467155535093520"><a name="b467155535093520"></a><a name="b467155535093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1478411122093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data segment to write. </td>
</tr>
<tr id="row394151752093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">writeSize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the data segment to write. The maximum value is 512 KB. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteInt16\(\)<a name="gaaa278bf9aa182a4c65c390c6c9ff06d2"></a>

```
bool HdfSbufWriteInt16 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int16_t value )
```

 **Description:**

Writes a 16-bit signed integer to a  **SBuf**. 

**Parameters:**

<a name="table742203968093520"></a>
<table><thead align="left"><tr id="row633056848093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1582348638093520"><a name="p1582348638093520"></a><a name="p1582348638093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1508272193093520"><a name="p1508272193093520"></a><a name="p1508272193093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1973276552093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b126134639093520"><a name="b126134639093520"></a><a name="b126134639093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row761570654093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 16-bit signed integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteInt32\(\)<a name="ga3913510d670da2f8ffa3103b5ff293f1"></a>

```
bool HdfSbufWriteInt32 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int32_t value )
```

 **Description:**

Writes a 32-bit signed integer to a  **SBuf**. 

**Parameters:**

<a name="table160157953093520"></a>
<table><thead align="left"><tr id="row1445508697093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2123388777093520"><a name="p2123388777093520"></a><a name="p2123388777093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p286788018093520"><a name="p286788018093520"></a><a name="p286788018093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row835019700093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b420493507093520"><a name="b420493507093520"></a><a name="b420493507093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row1330008350093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 32-bit signed integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteInt64\(\)<a name="ga7c63eb006b19e2aac43c23318c4ebe3b"></a>

```
bool HdfSbufWriteInt64 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int64_t value )
```

 **Description:**

Writes a 64-bit signed integer to a  **SBuf**. 

**Parameters:**

<a name="table969500311093520"></a>
<table><thead align="left"><tr id="row1136286871093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1254852820093520"><a name="p1254852820093520"></a><a name="p1254852820093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1813149740093520"><a name="p1813149740093520"></a><a name="p1813149740093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row381904346093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1956510988093520"><a name="b1956510988093520"></a><a name="b1956510988093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row620910762093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 64-bit signed integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteInt8\(\)<a name="gac514c3debd605043ad1bfa9c05a115a0"></a>

```
bool HdfSbufWriteInt8 (struct [HdfSBuf](HdfSBuf.md) * sbuf, int8_t value )
```

 **Description:**

Writes an 8-bit signed integer to a  **SBuf**. 

**Parameters:**

<a name="table318014631093520"></a>
<table><thead align="left"><tr id="row786761575093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p858242111093520"><a name="p858242111093520"></a><a name="p858242111093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p758781212093520"><a name="p758781212093520"></a><a name="p758781212093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1659143603093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b803228351093520"><a name="b803228351093520"></a><a name="b803228351093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row2134247992093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 8-bit signed integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteString\(\)<a name="gaf782f8a08dcd81f4038ab9d9bbc1cf9b"></a>

```
bool HdfSbufWriteString (struct [HdfSBuf](HdfSBuf.md) * sbuf, const char * value )
```

 **Description:**

Writes a string to a  **SBuf**. 

**Parameters:**

<a name="table1891862574093520"></a>
<table><thead align="left"><tr id="row77982122093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p770822050093520"><a name="p770822050093520"></a><a name="p770822050093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1161503308093520"><a name="p1161503308093520"></a><a name="p1161503308093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1474388607093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1933105231093520"><a name="b1933105231093520"></a><a name="b1933105231093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row443044163093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the string to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteUint16\(\)<a name="ga31c9edfd9b20d6e44d34839efa0e08f7"></a>

```
bool HdfSbufWriteUint16 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint16_t value )
```

 **Description:**

Writes a 16-bit unsigned integer to a  **SBuf**. 

**Parameters:**

<a name="table676012115093520"></a>
<table><thead align="left"><tr id="row1797554762093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p907591366093520"><a name="p907591366093520"></a><a name="p907591366093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1059628084093520"><a name="p1059628084093520"></a><a name="p1059628084093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1285406630093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1095323554093520"><a name="b1095323554093520"></a><a name="b1095323554093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row391876340093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 16-bit unsigned integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteUint32\(\)<a name="ga23f2331cdfb0bf91a29f47f20ffd50df"></a>

```
bool HdfSbufWriteUint32 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint32_t value )
```

 **Description:**

Writes a 32-bit unsigned integer to a  **SBuf**. 

**Parameters:**

<a name="table446744247093520"></a>
<table><thead align="left"><tr id="row585500495093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p651306678093520"><a name="p651306678093520"></a><a name="p651306678093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1527324398093520"><a name="p1527324398093520"></a><a name="p1527324398093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row194218944093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b1352821624093520"><a name="b1352821624093520"></a><a name="b1352821624093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row31293187093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 32-bit unsigned integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteUint64\(\)<a name="ga164de95ad00302b599290bdb476a032f"></a>

```
bool HdfSbufWriteUint64 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint64_t value )
```

 **Description:**

Writes a 64-bit unsigned integer to a  **SBuf**. 

**Parameters:**

<a name="table496751644093520"></a>
<table><thead align="left"><tr id="row664508560093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p20407176093520"><a name="p20407176093520"></a><a name="p20407176093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1382812587093520"><a name="p1382812587093520"></a><a name="p1382812587093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row834237783093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b2058329670093520"><a name="b2058329670093520"></a><a name="b2058329670093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row587927168093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 64-bit unsigned integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



## HdfSbufWriteUint8\(\)<a name="gafb4fe74246f85a158c140bf4c4951256"></a>

```
bool HdfSbufWriteUint8 (struct [HdfSBuf](HdfSBuf.md) * sbuf, uint8_t value )
```

 **Description:**

Writes an 8-bit unsigned integer to a  **SBuf**. 

**Parameters:**

<a name="table1160686527093520"></a>
<table><thead align="left"><tr id="row1890115905093520"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1032949187093520"><a name="p1032949187093520"></a><a name="p1032949187093520"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1401276575093520"><a name="p1401276575093520"></a><a name="p1401276575093520"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2138704187093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sbuf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target <strong id="b857162438093520"><a name="b857162438093520"></a><a name="b857162438093520"></a>SBuf</strong>. </td>
</tr>
<tr id="row2051303019093520"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the 8-bit unsigned integer to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise.



