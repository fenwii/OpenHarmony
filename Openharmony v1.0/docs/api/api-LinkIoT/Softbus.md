# Softbus<a name="ZH-CN_TOPIC_0000001055355032"></a>

## **Overview**<a name="section1027932487090251"></a>

Provides high-speed, secure communication between devices. 

This module implements unified distributed communication capability management between nearby devices, and provides link-independent device discovery and transmission interfaces to support service publishing and data transmission.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1927595905090251"></a>

## Files<a name="files"></a>

<a name="table1610373701090251"></a>
<table><thead align="left"><tr id="row1818816449090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1865502979090251"><a name="p1865502979090251"></a><a name="p1865502979090251"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1343590517090251"><a name="p1343590517090251"></a><a name="p1343590517090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1900041131090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934424276090251"><a name="p1934424276090251"></a><a name="p1934424276090251"></a><a href="discovery_service-h.md">discovery_service.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1954844322090251"><a name="p1954844322090251"></a><a name="p1954844322090251"></a>Declares unified device service publishing interfaces. </p>
</td>
</tr>
<tr id="row1901283385090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p324735557090251"><a name="p324735557090251"></a><a name="p324735557090251"></a><a href="session-h.md">session.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p317258697090251"><a name="p317258697090251"></a><a name="p317258697090251"></a>Declares unified data transmission interfaces. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1572709730090251"></a>
<table><thead align="left"><tr id="row190613298090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1601355355090251"><a name="p1601355355090251"></a><a name="p1601355355090251"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1486502883090251"><a name="p1486502883090251"></a><a name="p1486502883090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row775008478090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p865050452090251"><a name="p865050452090251"></a><a name="p865050452090251"></a><a href="PublishInfo.md">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2107043188090251"><a name="p2107043188090251"></a><a name="p2107043188090251"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row2044893405090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1680110881090251"><a name="p1680110881090251"></a><a name="p1680110881090251"></a><a href="CapabilityMap.md">CapabilityMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527629920090251"><a name="p527629920090251"></a><a name="p527629920090251"></a>Defines the mapping between supported capabilities and bitmaps. </p>
</td>
</tr>
<tr id="row951906172090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p675073925090251"><a name="p675073925090251"></a><a name="p675073925090251"></a><a href="DeviceMap.md">DeviceMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485595688090251"><a name="p1485595688090251"></a><a name="p1485595688090251"></a>Defines the mappings between the device type enumerations and device type names. </p>
</td>
</tr>
<tr id="row1091217858090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056404804090251"><a name="p2056404804090251"></a><a name="p2056404804090251"></a><a href="IPublishCallback.md">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1583909598090251"><a name="p1583909598090251"></a><a name="p1583909598090251"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row1292235181090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031352657090251"><a name="p1031352657090251"></a><a name="p1031352657090251"></a><a href="CommonDeviceInfo.md">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091691281090251"><a name="p1091691281090251"></a><a name="p1091691281090251"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
<tr id="row1935396615090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039181388090251"><a name="p1039181388090251"></a><a name="p1039181388090251"></a><a href="ISessionListener.md">ISessionListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967387052090251"><a name="p967387052090251"></a><a name="p967387052090251"></a>Defines session callbacks. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table911129777090251"></a>
<table><thead align="left"><tr id="row605100206090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p9027484090251"><a name="p9027484090251"></a><a name="p9027484090251"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1764160925090251"><a name="p1764160925090251"></a><a name="p1764160925090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1303212961090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101455491090251"><a name="p1101455491090251"></a><a name="p1101455491090251"></a><a href="Softbus.md#gae0bb52450c28ea9be1c5475d0d89830e">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313506167090251"><a name="p313506167090251"></a><a name="p313506167090251"></a>typedef struct <a href="PublishInfo.md">PublishInfo</a>&nbsp;</p>
<p id="p1552741673090251"><a name="p1552741673090251"></a><a name="p1552741673090251"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row82406696090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993890688090251"><a name="p993890688090251"></a><a name="p993890688090251"></a><a href="Softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4">DeviceType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535864284090251"><a name="p1535864284090251"></a><a name="p1535864284090251"></a>typedef enum <a href="Softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a>&nbsp;</p>
<p id="p1710893764090251"><a name="p1710893764090251"></a><a name="p1710893764090251"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row1296745723090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1028353387090251"><a name="p1028353387090251"></a><a name="p1028353387090251"></a><a href="Softbus.md#gab622f2f40d12121620d464e43635a09b">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890115786090251"><a name="p1890115786090251"></a><a name="p1890115786090251"></a>typedef struct <a href="IPublishCallback.md">IPublishCallback</a>&nbsp;</p>
<p id="p1075206320090251"><a name="p1075206320090251"></a><a name="p1075206320090251"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row242144932090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p267178117090251"><a name="p267178117090251"></a><a name="p267178117090251"></a><a href="Softbus.md#ga8dc0eb993aea9593f96da339edf042ff">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p61178820090251"><a name="p61178820090251"></a><a name="p61178820090251"></a>typedef struct <a href="CommonDeviceInfo.md">CommonDeviceInfo</a>&nbsp;</p>
<p id="p231729899090251"><a name="p231729899090251"></a><a name="p231729899090251"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table798357339090251"></a>
<table><thead align="left"><tr id="row1542457554090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p961972496090251"><a name="p961972496090251"></a><a name="p961972496090251"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2143856394090251"><a name="p2143856394090251"></a><a name="p2143856394090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1076564511090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1441454526090251"><a name="p1441454526090251"></a><a name="p1441454526090251"></a><a href="Softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b">ExchanageMedium</a> { <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6">AUTO</a> = 0, <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a">BLE</a> = 1, <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195">COAP</a> = 2, <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761">USB</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68981581090251"><a name="p68981581090251"></a><a name="p68981581090251"></a>Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services. </p>
</td>
</tr>
<tr id="row1369427418090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p622830566090251"><a name="p622830566090251"></a><a name="p622830566090251"></a><a href="Softbus.md#gacf2c77bd7e2c82784078762978123ea3">ExchangeFre</a> { <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8">LOW</a> = 0, <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236">MID</a> = 1, <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893">HIGH</a> = 2, <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc">SUPER_HIGH</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727756426090251"><a name="p727756426090251"></a><a name="p727756426090251"></a>Enumerates frequencies for publishing services. This enumeration is involved only in Bluetooth and is not supported currently. </p>
</td>
</tr>
<tr id="row204582901090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084740668090251"><a name="p2084740668090251"></a><a name="p2084740668090251"></a><a href="Softbus.md#ga7369479474cf45e9ca9c0f756473c74f">DiscoverMode</a> { <a href="Softbus.md#gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf">DISCOVER_MODE_PASSIVE</a> = 0x55, <a href="Softbus.md#gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb">DISCOVER_MODE_ACTIVE</a> = 0xAA }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p65429730090251"><a name="p65429730090251"></a><a name="p65429730090251"></a>Enumerates the modes in which services are published. The publishing service supports the passive mode. Lite devices support the passive mode only. </p>
</td>
</tr>
<tr id="row1128060464090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879783342090251"><a name="p879783342090251"></a><a name="p879783342090251"></a><a href="Softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620">PublishFailReason</a> { <a href="Softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d">PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM</a> = 1, <a href="Softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca">PUBLISH_FAIL_REASON_PARAMETER_INVALID</a> = 2, <a href="Softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f">PUBLISH_FAIL_REASON_UNKNOWN</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671390006090251"><a name="p671390006090251"></a><a name="p671390006090251"></a>Enumerates failure reasons for publishing services. </p>
</td>
</tr>
<tr id="row1714772312090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1089621796090251"><a name="p1089621796090251"></a><a name="p1089621796090251"></a><a href="Softbus.md#gab839c7f1fd448f52f003ab0693f27bb4">DataBitMap</a> { &nbsp;&nbsp;<a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c">HICALL_CAPABILITY_BITMAP</a> = 0, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3">PROFILE_CAPABILITY_BITMAP</a> = 1, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2">HOMEVISIONPIC_CAPABILITY_BITMAP</a> = 2, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f">CASTPLUS_CAPABILITY_BITMAP</a>, &nbsp;&nbsp;<a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3">AA_CAPABILITY_BITMAP</a>, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8">DVKIT_CAPABILITY_BITMAP</a>, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b">DDMP_CAPABILITY_BITMAP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1731247042090251"><a name="p1731247042090251"></a><a name="p1731247042090251"></a>Enumerates supported capabilities published by a device. </p>
</td>
</tr>
<tr id="row2063703637090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p208997638090251"><a name="p208997638090251"></a><a name="p208997638090251"></a><a href="Softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a> { &nbsp;&nbsp;<a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9">UNKOWN</a> = 0x00, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1">PHONE</a> = 0x0E, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2">PAD</a> = 0x11, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2">TV</a> = 0x9C, &nbsp;&nbsp;<a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46">PC</a> = 0x0C, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd">AUDIO</a> = 0x0A, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40">CAR</a> = 0x83, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9">L0</a> = 0xF1, &nbsp;&nbsp;<a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543">L1</a> = 0xF2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1138016762090251"><a name="p1138016762090251"></a><a name="p1138016762090251"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row1042987750090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p814019363090251"><a name="p814019363090251"></a><a name="p814019363090251"></a><a href="Softbus.md#ga25be99ffbe88e41f7ce51d2678010254">CommonDeviceKey</a> { <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10">COMM_DEVICE_KEY_DEVID</a> = 0, <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816">COMM_DEVICE_KEY_DEVTYPE</a> = 1, <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341">COMM_DEVICE_KEY_DEVNAME</a> = 2, <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84">COMM_DEVICE_KEY_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p737622246090251"><a name="p737622246090251"></a><a name="p737622246090251"></a>Enumerates device information, such as its ID, type, and name. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1295071134090251"></a>
<table><thead align="left"><tr id="row1679785418090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1359095529090251"><a name="p1359095529090251"></a><a name="p1359095529090251"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1762443188090251"><a name="p1762443188090251"></a><a name="p1762443188090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1088481369090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709512966090251"><a name="p709512966090251"></a><a name="p709512966090251"></a><a href="Softbus.md#ga010557e05b3f0b0b1a05157f1724e13a">PublishService</a> (const char *moduleName, const struct <a href="PublishInfo.md">PublishInfo</a> *info, const struct <a href="IPublishCallback.md">IPublishCallback</a> *cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121367024090251"><a name="p1121367024090251"></a><a name="p1121367024090251"></a>int&nbsp;</p>
<p id="p915738166090251"><a name="p915738166090251"></a><a name="p915738166090251"></a>Publishes a service to the discovering device in the LAN. </p>
</td>
</tr>
<tr id="row1078619605090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p938526378090251"><a name="p938526378090251"></a><a name="p938526378090251"></a><a href="Softbus.md#gac9463e62e324155634c01facdf642ea7">UnPublishService</a> (const char *moduleName, int publishId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1013764836090251"><a name="p1013764836090251"></a><a name="p1013764836090251"></a>int&nbsp;</p>
<p id="p1006350985090251"><a name="p1006350985090251"></a><a name="p1006350985090251"></a>Unpublishes a service based on the <strong id="b440594227090251"><a name="b440594227090251"></a><a name="b440594227090251"></a>publicId</strong> and <strong id="b1875836676090251"><a name="b1875836676090251"></a><a name="b1875836676090251"></a>moduleName</strong>. </p>
</td>
</tr>
<tr id="row1218893063090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007122966090251"><a name="p2007122966090251"></a><a name="p2007122966090251"></a><a href="Softbus.md#gaca3ae566d98727d111befb4a642bafc4">SetCommonDeviceInfo</a> (const struct <a href="CommonDeviceInfo.md">CommonDeviceInfo</a> *devInfo, unsigned int num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569851790090251"><a name="p569851790090251"></a><a name="p569851790090251"></a>int&nbsp;</p>
<p id="p1728641598090251"><a name="p1728641598090251"></a><a name="p1728641598090251"></a>Sets common device information, such as its ID, type, and name. </p>
</td>
</tr>
<tr id="row551775724090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2060339286090251"><a name="p2060339286090251"></a><a name="p2060339286090251"></a><a href="Softbus.md#gad7e95cced3378e8f489553d70b121392">CreateSessionServer</a> (const char *mouduleName, const char *sessionName, struct <a href="ISessionListener.md">ISessionListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989669712090251"><a name="p989669712090251"></a><a name="p989669712090251"></a>int&nbsp;</p>
<p id="p530726056090251"><a name="p530726056090251"></a><a name="p530726056090251"></a>Creates a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row86120042090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034327576090251"><a name="p1034327576090251"></a><a name="p1034327576090251"></a><a href="Softbus.md#ga225a1e178544457263d94078e638b7b5">RemoveSessionServer</a> (const char *mouduleName, const char *sessionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994724500090251"><a name="p1994724500090251"></a><a name="p1994724500090251"></a>int&nbsp;</p>
<p id="p1550920516090251"><a name="p1550920516090251"></a><a name="p1550920516090251"></a>Removes a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row399997864090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1248908738090251"><a name="p1248908738090251"></a><a name="p1248908738090251"></a><a href="Softbus.md#ga0333c76724dbef71bca48fb2a82e6980">SendBytes</a> (int sessionId, const void *data, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238770910090251"><a name="p1238770910090251"></a><a name="p1238770910090251"></a>int&nbsp;</p>
<p id="p217221350090251"><a name="p217221350090251"></a><a name="p217221350090251"></a>Sends data based on a session ID. </p>
</td>
</tr>
<tr id="row1979996814090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006471411090251"><a name="p2006471411090251"></a><a name="p2006471411090251"></a><a href="Softbus.md#ga00611f717919f4156c74b7919b28c7d8">GetMySessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060463878090251"><a name="p1060463878090251"></a><a name="p1060463878090251"></a>int&nbsp;</p>
<p id="p1805850097090251"><a name="p1805850097090251"></a><a name="p1805850097090251"></a>Obtains the session name registered by the local device based on the session ID. </p>
</td>
</tr>
<tr id="row974478291090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1070489663090251"><a name="p1070489663090251"></a><a name="p1070489663090251"></a><a href="Softbus.md#ga92d5a47fcdf97a0e01797c77e644033e">GetPeerSessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775745334090251"><a name="p1775745334090251"></a><a name="p1775745334090251"></a>int&nbsp;</p>
<p id="p257440264090251"><a name="p257440264090251"></a><a name="p257440264090251"></a>Obtains the session name registered by the peer device based on the session ID. </p>
</td>
</tr>
<tr id="row618681930090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1334566379090251"><a name="p1334566379090251"></a><a name="p1334566379090251"></a><a href="Softbus.md#ga21b9a889069eea6e7fe653820e601c04">GetPeerDeviceId</a> (int sessionId, char *devId, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p489139503090251"><a name="p489139503090251"></a><a name="p489139503090251"></a>int&nbsp;</p>
<p id="p904148288090251"><a name="p904148288090251"></a><a name="p904148288090251"></a>Obtains the peer device ID based on a session ID. </p>
</td>
</tr>
<tr id="row672341413090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2120900613090251"><a name="p2120900613090251"></a><a name="p2120900613090251"></a><a href="Softbus.md#ga5b0c0b334f387f9c2753146ee0890780">CloseSession</a> (int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1044976699090251"><a name="p1044976699090251"></a><a name="p1044976699090251"></a>void&nbsp;</p>
<p id="p218320236090251"><a name="p218320236090251"></a><a name="p218320236090251"></a>Closes a connected session based on a session ID. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1232758238090251"></a>

## **Typedef Documentation**<a name="section1493837137090251"></a>

## CommonDeviceInfo<a name="ga8dc0eb993aea9593f96da339edf042ff"></a>

```
typedef struct [CommonDeviceInfo](CommonDeviceInfo.md) [CommonDeviceInfo](CommonDeviceInfo.md)
```

 **Description:**

Defines the type and content of a device to set. 

## DeviceType<a name="ga9334bacb3ded964dc3c3367a6b70bcf4"></a>

```
typedef enum [DeviceTypeEnum](Softbus.md#gab20b49630026f3118d6c05b0a022f230) [DeviceType](Softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4)
```

 **Description:**

Enumerates device types. 

## IPublishCallback<a name="gab622f2f40d12121620d464e43635a09b"></a>

```
typedef struct [IPublishCallback](IPublishCallback.md) [IPublishCallback](IPublishCallback.md)
```

 **Description:**

Defines the callbacks for successful and failed service publishing. 

## PublishInfo<a name="gae0bb52450c28ea9be1c5475d0d89830e"></a>

```
typedef struct [PublishInfo](PublishInfo.md) [PublishInfo](PublishInfo.md)
```

 **Description:**

Defines service provisioning information sent to a discovering device. 

## **Enumeration Type Documentation**<a name="section579841242090251"></a>

## CommonDeviceKey<a name="ga25be99ffbe88e41f7ce51d2678010254"></a>

```
enum [CommonDeviceKey](Softbus.md#ga25be99ffbe88e41f7ce51d2678010254)
```

 **Description:**

Enumerates device information, such as its ID, type, and name. 

<a name="table1112910279090251"></a>
<table><thead align="left"><tr id="row2109733053090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1049648054090251"><a name="p1049648054090251"></a><a name="p1049648054090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1428426491090251"><a name="p1428426491090251"></a><a name="p1428426491090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row685596261090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10"><a name="gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10"></a><a name="gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10"></a></strong>COMM_DEVICE_KEY_DEVID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1247382436090251"><a name="p1247382436090251"></a><a name="p1247382436090251"></a>Device ID. The value contains a maximum of 64 characters. </p>
 </td>
</tr>
<tr id="row587131009090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816"><a name="gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816"></a><a name="gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816"></a></strong>COMM_DEVICE_KEY_DEVTYPE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1073118769090251"><a name="p1073118769090251"></a><a name="p1073118769090251"></a>Device type. Currently, only <strong id="b1525678955090251"><a name="b1525678955090251"></a><a name="b1525678955090251"></a>ddmpCapability</strong> is supported. </p>
 </td>
</tr>
<tr id="row1826738360090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341"><a name="gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341"></a><a name="gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341"></a></strong>COMM_DEVICE_KEY_DEVNAME&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481560918090251"><a name="p1481560918090251"></a><a name="p1481560918090251"></a>Device name. The value contains a maximum of 63 characters. </p>
 </td>
</tr>
<tr id="row595165604090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84"><a name="gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84"></a><a name="gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84"></a></strong>COMM_DEVICE_KEY_MAX&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182849705090251"><a name="p182849705090251"></a><a name="p182849705090251"></a>Reserved </p>
 </td>
</tr>
</tbody>
</table>

## DataBitMap<a name="gab839c7f1fd448f52f003ab0693f27bb4"></a>

```
enum [DataBitMap](Softbus.md#gab839c7f1fd448f52f003ab0693f27bb4)
```

 **Description:**

Enumerates supported capabilities published by a device. 

<a name="table2058602134090251"></a>
<table><thead align="left"><tr id="row467948524090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1768463101090251"><a name="p1768463101090251"></a><a name="p1768463101090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p971733499090251"><a name="p971733499090251"></a><a name="p971733499090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1072572430090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c"></a></strong>HICALL_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003166889090251"><a name="p2003166889090251"></a><a name="p2003166889090251"></a>MeeTime </p>
 </td>
</tr>
<tr id="row789691348090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3"></a></strong>PROFILE_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2038279116090251"><a name="p2038279116090251"></a><a name="p2038279116090251"></a>Video reverse connection in the smart domain </p>
 </td>
</tr>
<tr id="row741289994090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2"></a></strong>HOMEVISIONPIC_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1661362917090251"><a name="p1661362917090251"></a><a name="p1661362917090251"></a>Gallery in Vision </p>
 </td>
</tr>
<tr id="row1691836055090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f"><a name="ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f"></a></strong>CASTPLUS_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1536260454090251"><a name="p1536260454090251"></a><a name="p1536260454090251"></a>cast+ </p>
 </td>
</tr>
<tr id="row2036539988090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3"></a></strong>AA_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p619260502090251"><a name="p619260502090251"></a><a name="p619260502090251"></a>Input method in Vision </p>
 </td>
</tr>
<tr id="row1739916511090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8"><a name="ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8"></a></strong>DVKIT_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882500045090251"><a name="p882500045090251"></a><a name="p882500045090251"></a>Device virtualization tool package </p>
 </td>
</tr>
<tr id="row1606449831090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b"><a name="ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b"></a></strong>DDMP_CAPABILITY_BITMAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114749324090251"><a name="p114749324090251"></a><a name="p114749324090251"></a>Distributed middleware </p>
 </td>
</tr>
</tbody>
</table>

## DeviceTypeEnum<a name="gab20b49630026f3118d6c05b0a022f230"></a>

```
enum [DeviceTypeEnum](Softbus.md#gab20b49630026f3118d6c05b0a022f230)
```

 **Description:**

Enumerates device types. 

<a name="table1408288523090251"></a>
<table><thead align="left"><tr id="row385325297090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1140780246090251"><a name="p1140780246090251"></a><a name="p1140780246090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1964427718090251"><a name="p1964427718090251"></a><a name="p1964427718090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row974252925090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9"><a name="ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9"></a><a name="ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9"></a></strong>UNKOWN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1983336423090251"><a name="p1983336423090251"></a><a name="p1983336423090251"></a>Unknown </p>
 </td>
</tr>
<tr id="row564615824090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1"><a name="ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1"></a><a name="ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1"></a></strong>PHONE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p968094733090251"><a name="p968094733090251"></a><a name="p968094733090251"></a>Smartphone </p>
 </td>
</tr>
<tr id="row1067728132090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2"><a name="ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2"></a><a name="ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2"></a></strong>PAD&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1503794489090251"><a name="p1503794489090251"></a><a name="p1503794489090251"></a>Tablet </p>
 </td>
</tr>
<tr id="row1090338967090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2"><a name="ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2"></a><a name="ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2"></a></strong>TV&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p585960308090251"><a name="p585960308090251"></a><a name="p585960308090251"></a>Smart TV </p>
 </td>
</tr>
<tr id="row1871723564090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46"><a name="ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46"></a><a name="ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46"></a></strong>PC&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p553830525090251"><a name="p553830525090251"></a><a name="p553830525090251"></a>PC </p>
 </td>
</tr>
<tr id="row2047984870090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd"><a name="ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd"></a><a name="ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd"></a></strong>AUDIO&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1454856811090251"><a name="p1454856811090251"></a><a name="p1454856811090251"></a>Audio device </p>
 </td>
</tr>
<tr id="row2109617652090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40"><a name="ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40"></a><a name="ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40"></a></strong>CAR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842355300090251"><a name="p842355300090251"></a><a name="p842355300090251"></a>Vehicle-mounted device </p>
 </td>
</tr>
<tr id="row834738502090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9"><a name="ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9"></a><a name="ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9"></a></strong>L0&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p998161115090251"><a name="p998161115090251"></a><a name="p998161115090251"></a>Light device L0 </p>
 </td>
</tr>
<tr id="row957014797090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543"><a name="ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543"></a><a name="ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543"></a></strong>L1&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p655460710090251"><a name="p655460710090251"></a><a name="p655460710090251"></a>Light device L1 </p>
 </td>
</tr>
</tbody>
</table>

## DiscoverMode<a name="ga7369479474cf45e9ca9c0f756473c74f"></a>

```
enum [DiscoverMode](Softbus.md#ga7369479474cf45e9ca9c0f756473c74f)
```

 **Description:**

Enumerates the modes in which services are published. The publishing service supports the passive mode. Lite devices support the passive mode only. 

<a name="table363650979090251"></a>
<table><thead align="left"><tr id="row239034307090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1926547482090251"><a name="p1926547482090251"></a><a name="p1926547482090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p305707398090251"><a name="p305707398090251"></a><a name="p305707398090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row518407353090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf"><a name="gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf"></a><a name="gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf"></a></strong>DISCOVER_MODE_PASSIVE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743224009090251"><a name="p1743224009090251"></a><a name="p1743224009090251"></a>Passive </p>
 </td>
</tr>
<tr id="row1505044303090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb"><a name="gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb"></a><a name="gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb"></a></strong>DISCOVER_MODE_ACTIVE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1856698671090251"><a name="p1856698671090251"></a><a name="p1856698671090251"></a>Proactive </p>
 </td>
</tr>
</tbody>
</table>

## ExchanageMedium<a name="gaf5c7c122990f0ab5bd46b9bc47b5868b"></a>

```
enum [ExchanageMedium](Softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b)
```

 **Description:**

Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services. 

Currently, the media can only be set to coap. 

<a name="table590117228090251"></a>
<table><thead align="left"><tr id="row809751068090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1354059198090251"><a name="p1354059198090251"></a><a name="p1354059198090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1140916155090251"><a name="p1140916155090251"></a><a name="p1140916155090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2146816422090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6"></a></strong>AUTO&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p482524822090251"><a name="p482524822090251"></a><a name="p482524822090251"></a>Automatic medium selection </p>
 </td>
</tr>
<tr id="row80981379090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a"></a></strong>BLE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669683817090251"><a name="p669683817090251"></a><a name="p669683817090251"></a>Bluetooth </p>
 </td>
</tr>
<tr id="row132538445090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195"></a></strong>COAP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1982586383090251"><a name="p1982586383090251"></a><a name="p1982586383090251"></a>Wi-Fi </p>
 </td>
</tr>
<tr id="row296958715090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761"></a></strong>USB&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053315918090251"><a name="p2053315918090251"></a><a name="p2053315918090251"></a>USB </p>
 </td>
</tr>
</tbody>
</table>

## ExchangeFre<a name="gacf2c77bd7e2c82784078762978123ea3"></a>

```
enum [ExchangeFre](Softbus.md#gacf2c77bd7e2c82784078762978123ea3)
```

 **Description:**

Enumerates frequencies for publishing services. This enumeration is involved only in Bluetooth and is not supported currently. 

<a name="table473473868090251"></a>
<table><thead align="left"><tr id="row1048966384090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p450609470090251"><a name="p450609470090251"></a><a name="p450609470090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p638576808090251"><a name="p638576808090251"></a><a name="p638576808090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1774607601090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8"><a name="ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8"></a></strong>LOW&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1612727747090251"><a name="p1612727747090251"></a><a name="p1612727747090251"></a>Low </p>
 </td>
</tr>
<tr id="row493978754090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236"><a name="ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236"></a></strong>MID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85929192090251"><a name="p85929192090251"></a><a name="p85929192090251"></a>Medium </p>
 </td>
</tr>
<tr id="row763188569090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893"><a name="ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893"></a></strong>HIGH&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802488509090251"><a name="p1802488509090251"></a><a name="p1802488509090251"></a>High </p>
 </td>
</tr>
<tr id="row1866441559090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc"><a name="ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc"></a></strong>SUPER_HIGH&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395703267090251"><a name="p395703267090251"></a><a name="p395703267090251"></a>Super-high </p>
 </td>
</tr>
</tbody>
</table>

## PublishFailReason<a name="ga6632fcae1db4a3a13370e3fb49e5e620"></a>

```
enum [PublishFailReason](Softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620)
```

 **Description:**

Enumerates failure reasons for publishing services. 

The failure reason is returned to the caller through the callback function. 

<a name="table136323911090251"></a>
<table><thead align="left"><tr id="row1910828253090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p845714099090251"><a name="p845714099090251"></a><a name="p845714099090251"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1898146320090251"><a name="p1898146320090251"></a><a name="p1898146320090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1969620486090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d"><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d"></a><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d"></a></strong>PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p163568673090251"><a name="p163568673090251"></a><a name="p163568673090251"></a>Unsupported medium </p>
 </td>
</tr>
<tr id="row1235501544090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca"><a name="gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca"></a><a name="gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca"></a></strong>PUBLISH_FAIL_REASON_PARAMETER_INVALID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2143676221090251"><a name="p2143676221090251"></a><a name="p2143676221090251"></a>Invalid parameter </p>
 </td>
</tr>
<tr id="row297284351090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f"><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f"></a><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f"></a></strong>PUBLISH_FAIL_REASON_UNKNOWN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1115840384090251"><a name="p1115840384090251"></a><a name="p1115840384090251"></a>Unknown reason </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section300217993090251"></a>

## CloseSession\(\)<a name="ga5b0c0b334f387f9c2753146ee0890780"></a>

```
void CloseSession (int sessionId)
```

 **Description:**

Closes a connected session based on a session ID. 

**Parameters:**

<a name="table552539316090251"></a>
<table><thead align="left"><tr id="row1711958300090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1375917977090251"><a name="p1375917977090251"></a><a name="p1375917977090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1051783562090251"><a name="p1051783562090251"></a><a name="p1051783562090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1896986274090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
</tbody>
</table>

## CreateSessionServer\(\)<a name="gad7e95cced3378e8f489553d70b121392"></a>

```
int CreateSessionServer (const char * mouduleName, const char * sessionName, struct [ISessionListener](ISessionListener.md) * listener )
```

 **Description:**

Creates a session server based on a module name and session name. 

A maximum of 18 session servers can be created.

**Parameters:**

<a name="table2056085318090251"></a>
<table><thead align="left"><tr id="row1163083309090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1829951427090251"><a name="p1829951427090251"></a><a name="p1829951427090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p820403734090251"><a name="p820403734090251"></a><a name="p820403734090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1620678294090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module name, which can be used to check whether the session server is in this module. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
<tr id="row298013180090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the session name, which is the unique ID of the session server. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
<tr id="row195641624090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">listener</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the session callback structure, which cannot be empty. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 

**See also:**

[RemoveSessionServer](Softbus.md#ga225a1e178544457263d94078e638b7b5) 

## GetMySessionName\(\)<a name="ga00611f717919f4156c74b7919b28c7d8"></a>

```
int GetMySessionName (int sessionId, char * sessionName, unsigned int len )
```

 **Description:**

Obtains the session name registered by the local device based on the session ID. 

**Parameters:**

<a name="table1891435641090251"></a>
<table><thead align="left"><tr id="row1750904168090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1854414313090251"><a name="p1854414313090251"></a><a name="p1854414313090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p476147796090251"><a name="p476147796090251"></a><a name="p476147796090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1769491698090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row1730654910090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the session name. </td>
</tr>
<tr id="row1768096566090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## GetPeerDeviceId\(\)<a name="ga21b9a889069eea6e7fe653820e601c04"></a>

```
int GetPeerDeviceId (int sessionId, char * devId, unsigned int len )
```

 **Description:**

Obtains the peer device ID based on a session ID. 

**Parameters:**

<a name="table256881836090251"></a>
<table><thead align="left"><tr id="row1218378517090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p557447088090251"><a name="p557447088090251"></a><a name="p557447088090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1273574897090251"><a name="p1273574897090251"></a><a name="p1273574897090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1383512552090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row727580359090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the device ID. </td>
</tr>
<tr id="row1128812152090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## GetPeerSessionName\(\)<a name="ga92d5a47fcdf97a0e01797c77e644033e"></a>

```
int GetPeerSessionName (int sessionId, char * sessionName, unsigned int len )
```

 **Description:**

Obtains the session name registered by the peer device based on the session ID. 

**Parameters:**

<a name="table614247009090251"></a>
<table><thead align="left"><tr id="row2095818633090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1552800046090251"><a name="p1552800046090251"></a><a name="p1552800046090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1274358184090251"><a name="p1274358184090251"></a><a name="p1274358184090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1772785441090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row1696063843090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the session name. </td>
</tr>
<tr id="row785764881090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## PublishService\(\)<a name="ga010557e05b3f0b0b1a05157f1724e13a"></a>

```
int PublishService (const char * moduleName, const struct [PublishInfo](PublishInfo.md) * info, const struct [IPublishCallback](IPublishCallback.md) * cb )
```

 **Description:**

Publishes a service to the discovering device in the LAN. 

The  **publicId**  and  **moduleName**  uniquely identify a service. A maximum of three services can be published.

**Parameters:**

<a name="table2101351807090251"></a>
<table><thead align="left"><tr id="row951468239090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2065230889090251"><a name="p2065230889090251"></a><a name="p2065230889090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2062206376090251"><a name="p2062206376090251"></a><a name="p2062206376090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row403414396090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module name of the upper-layer service. The value contains a maximum of 63 bytes. </td>
</tr>
<tr id="row871930780090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service to publish. For details, see <a href="PublishInfo.md">PublishInfo</a>. </td>
</tr>
<tr id="row1823471079090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the callback for service publishing. For details, see <a href="IPublishCallback.md">IPublishCallback</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## RemoveSessionServer\(\)<a name="ga225a1e178544457263d94078e638b7b5"></a>

```
int RemoveSessionServer (const char * mouduleName, const char * sessionName )
```

 **Description:**

Removes a session server based on a module name and session name. 

**Parameters:**

<a name="table1971326013090251"></a>
<table><thead align="left"><tr id="row1488898466090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p647127274090251"><a name="p647127274090251"></a><a name="p647127274090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1031562463090251"><a name="p1031562463090251"></a><a name="p1031562463090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1331267110090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the registered module, which can be used to check whether the session server is in this module. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
<tr id="row999176827090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the session name. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 

**See also:**

[CreateSessionServer](Softbus.md#gad7e95cced3378e8f489553d70b121392) 

## SendBytes\(\)<a name="ga0333c76724dbef71bca48fb2a82e6980"></a>

```
int SendBytes (int sessionId, const void * data, unsigned int len )
```

 **Description:**

Sends data based on a session ID. 

**Parameters:**

<a name="table1068254827090251"></a>
<table><thead align="left"><tr id="row1147245637090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p204816729090251"><a name="p204816729090251"></a><a name="p204816729090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1580472701090251"><a name="p1580472701090251"></a><a name="p1580472701090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1802590787090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row613598494090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to send, which cannot be <strong id="b536932803090251"><a name="b536932803090251"></a><a name="b536932803090251"></a>NULL</strong>. </td>
</tr>
<tr id="row776148386090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to send. The maximum length cannot exceed 984 characters. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the function is called successfully; returns  **-1**  otherwise. 



## SetCommonDeviceInfo\(\)<a name="gaca3ae566d98727d111befb4a642bafc4"></a>

```
int SetCommonDeviceInfo (const struct [CommonDeviceInfo](CommonDeviceInfo.md) * devInfo, unsigned int num )
```

 **Description:**

Sets common device information, such as its ID, type, and name. 

**Parameters:**

<a name="table886731667090251"></a>
<table><thead align="left"><tr id="row1551397114090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1638904144090251"><a name="p1638904144090251"></a><a name="p1638904144090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p239419703090251"><a name="p239419703090251"></a><a name="p239419703090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row258692776090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device information array. </td>
</tr>
<tr id="row909850787090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">2</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">num Indicates the number of elements in the device information array. If the value is inconsistent with the length of the device information array, the program breaks down. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 

**See also:**

[PublishService](Softbus.md#ga010557e05b3f0b0b1a05157f1724e13a) 

## UnPublishService\(\)<a name="gac9463e62e324155634c01facdf642ea7"></a>

```
int UnPublishService (const char * moduleName, int publishId )
```

 **Description:**

Unpublishes a service based on the  **publicId**  and  **moduleName**. 

**Parameters:**

<a name="table2119025221090251"></a>
<table><thead align="left"><tr id="row1079429768090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p981745730090251"><a name="p981745730090251"></a><a name="p981745730090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p348900106090251"><a name="p348900106090251"></a><a name="p348900106090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1583755362090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module name of the upper-layer service. The value contains a maximum of 63 bytes. </td>
</tr>
<tr id="row539837362090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">publishId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the service to unpublish. The value must be greater than <strong id="b1156396152090251"><a name="b1156396152090251"></a><a name="b1156396152090251"></a>0</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## **Variable Documentation**<a name="section942184640090251"></a>

## bitmap<a name="gaccfbfe7a48ef51a2bada9a711dfe8cdb"></a>

```
[DataBitMap](Softbus.md#gab839c7f1fd448f52f003ab0693f27bb4) CapabilityMap::bitmap
```

 **Description:**

Bitmaps. For details, see  [DataBitMap](Softbus.md#gab839c7f1fd448f52f003ab0693f27bb4). 

## capability \[1/2\]<a name="gacf7c1f9daf2bf9c148ab9d8048d75358"></a>

```
const char* PublishInfo::capability
```

 **Description:**

[Service](Service.md)  publishing capabilities. For details, see  **g\_capabilityMap**. 

## capability \[2/2\]<a name="gaba08ca6b519055898dd60b6e98a796d4"></a>

```
char* CapabilityMap::capability
```

 **Description:**

Capability. For details, see  **g\_capabilityMap**. 

## capabilityData<a name="ga0d267dd5f6f198120f91759094f07ab7"></a>

```
unsigned char* PublishInfo::capabilityData
```

 **Description:**

Capability data for service publishing 

## dataLen<a name="ga0ae4b95fd8ba4fd0fca6d02dee79e643"></a>

```
unsigned int PublishInfo::dataLen
```

 **Description:**

Maximum length of the capability data for service publishing \(2 bytes\) 

## devType<a name="ga0e85f0b19c5d5d8368b93b9751473fb1"></a>

```
[DeviceType](Softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4) DeviceMap::devType
```

 **Description:**

Enumeration of a device type. Only enumerations defined in  **g\_devMap**  are supported. 

## freq<a name="gaf850489236b0efbc4b27ea5a867ec001"></a>

```
[ExchangeFre](Softbus.md#gacf2c77bd7e2c82784078762978123ea3) PublishInfo::freq
```

 **Description:**

[Service](Service.md)  publishing frequency 

## key<a name="gaf3ee5a07a887ab31517318e0d4ea8cc4"></a>

```
[CommonDeviceKey](Softbus.md#ga25be99ffbe88e41f7ce51d2678010254) CommonDeviceInfo::key
```

 **Description:**

Device information type. For details, see  [CommonDeviceKey](Softbus.md#ga25be99ffbe88e41f7ce51d2678010254). 

## medium<a name="ga3997803d8bfec79f5ba6e264f8e35b52"></a>

```
[ExchanageMedium](Softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b) PublishInfo::medium
```

 **Description:**

[Service](Service.md)  publishing medium 

## mode<a name="ga1e1635bcdb216cd4a4756c4962c3f595"></a>

```
int PublishInfo::mode
```

 **Description:**

[Service](Service.md)  publishing mode, which can be  [DISCOVER\_MODE\_PASSIVE](Softbus.md#gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf)  or  [DISCOVER\_MODE\_ACTIVE](Softbus.md#gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb) 

## onBytesReceived<a name="ga95243f25fa04ef29f7f8f0b3a440dbd3"></a>

```
void(* ISessionListener::onBytesReceived) (int sessionId, const void *data, unsigned int dataLen)
```

 **Description:**

Called when data is received. 

This function is used to notify that data is received.

**Parameters:**

<a name="table1912182732090251"></a>
<table><thead align="left"><tr id="row1547159206090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1375637235090251"><a name="p1375637235090251"></a><a name="p1375637235090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p372308249090251"><a name="p372308249090251"></a><a name="p372308249090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1455816652090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row664996707090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data received. </td>
</tr>
<tr id="row1647671885090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dataLen</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data received. </td>
</tr>
</tbody>
</table>

## onPublishFail<a name="ga0f84feec4640c176938bbce26b8f25c8"></a>

```
void(* IPublishCallback::onPublishFail) (int publishId, [PublishFailReason](Softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620) reason)
```

 **Description:**

Callback for failed publishing 

## onPublishSuccess<a name="gade0a74f5ae9b16a1fa7f03df5d9fbdf1"></a>

```
void(* IPublishCallback::onPublishSuccess) (int publishId)
```

 **Description:**

Callback for successful publishing 

## onSessionClosed<a name="ga2088a4e0e196030d8e428a828298eba0"></a>

```
void(* ISessionListener::onSessionClosed) (int sessionId)
```

 **Description:**

Called when a session is closed. 

This function can be used to release resources related to the session. You do not need to call  [CloseSession](Softbus.md#ga5b0c0b334f387f9c2753146ee0890780).

**Parameters:**

<a name="table953269052090251"></a>
<table><thead align="left"><tr id="row223284704090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p801591808090251"><a name="p801591808090251"></a><a name="p801591808090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p646325842090251"><a name="p646325842090251"></a><a name="p646325842090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1863322132090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
</tbody>
</table>

## onSessionOpened<a name="ga2b042b85e03d66f1988c348414b2db6e"></a>

```
int(* ISessionListener::onSessionOpened) (int sessionId)
```

 **Description:**

Called when a session is opened. 

This function can be used to verify the session or initialize resources related to the session.

**Parameters:**

<a name="table2114799108090251"></a>
<table><thead align="left"><tr id="row1707397256090251"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1595760511090251"><a name="p1595760511090251"></a><a name="p1595760511090251"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p469251962090251"><a name="p469251962090251"></a><a name="p469251962090251"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1931875473090251"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the session connection is accepted; returns a non-zero value otherwise \(you do not need to call  [CloseSession](Softbus.md#ga5b0c0b334f387f9c2753146ee0890780)  to close the session\). 



## publishId<a name="ga44a9b46ef719d882d4438a0c34a7f657"></a>

```
int PublishInfo::publishId
```

 **Description:**

[Service](Service.md)  publishing ID 

## value \[1/2\]<a name="gaddf75957b595adaddd4f227b9834e20b"></a>

```
char* DeviceMap::value
```

 **Description:**

Name of a device type. Only names defined in  **g\_devMap**  are supported. 

## value \[2/2\]<a name="ga84452c64348251edfe90fc61a5c561ac"></a>

```
const char* CommonDeviceInfo::value
```

 **Description:**

Content to set 

