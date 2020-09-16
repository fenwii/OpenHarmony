# discovery\_service.h<a name="EN-US_TOPIC_0000001055078103"></a>

## **Overview**<a name="section1231789754084829"></a>

**Related Modules:**

[Softbus](softbus.md)

**Description:**

Declares unified device service publishing interfaces. 

This file provides capabilities related to device service publishing, including publishing services, unpublishing services, and setting device parameters. After multiple nearby devices are discovered and networked, these interfaces can be used to perform service publishing-related operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2131725057084829"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1181422204084829"></a>
<table><thead align="left"><tr id="row414086995084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1251617356084829"><a name="p1251617356084829"></a><a name="p1251617356084829"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1268416049084829"><a name="p1268416049084829"></a><a name="p1268416049084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1141893673084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1132515937084829"><a name="p1132515937084829"></a><a name="p1132515937084829"></a><a href="publishinfo.md">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1525417816084829"><a name="p1525417816084829"></a><a name="p1525417816084829"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row1315069622084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024813539084829"><a name="p1024813539084829"></a><a name="p1024813539084829"></a><a href="capabilitymap.md">CapabilityMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p180410913084829"><a name="p180410913084829"></a><a name="p180410913084829"></a>Defines the mapping between supported capabilities and bitmaps. </p>
</td>
</tr>
<tr id="row223004731084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2050096100084829"><a name="p2050096100084829"></a><a name="p2050096100084829"></a><a href="devicemap.md">DeviceMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1359017063084829"><a name="p1359017063084829"></a><a name="p1359017063084829"></a>Defines the mappings between the device type enumerations and device type names. </p>
</td>
</tr>
<tr id="row179998896084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645941396084829"><a name="p645941396084829"></a><a name="p645941396084829"></a><a href="ipublishcallback.md">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012806537084829"><a name="p1012806537084829"></a><a name="p1012806537084829"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row1795833105084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1320471579084829"><a name="p1320471579084829"></a><a name="p1320471579084829"></a><a href="commondeviceinfo.md">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96926203084829"><a name="p96926203084829"></a><a name="p96926203084829"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table2118076936084829"></a>
<table><thead align="left"><tr id="row402592891084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1293936484084829"><a name="p1293936484084829"></a><a name="p1293936484084829"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p677418605084829"><a name="p677418605084829"></a><a name="p677418605084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1770861383084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1814793193084829"><a name="p1814793193084829"></a><a name="p1814793193084829"></a><a href="softbus.md#gae0bb52450c28ea9be1c5475d0d89830e">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1130179853084829"><a name="p1130179853084829"></a><a name="p1130179853084829"></a>typedef struct <a href="publishinfo.md">PublishInfo</a> </p>
<p id="p1371666815084829"><a name="p1371666815084829"></a><a name="p1371666815084829"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row1255817346084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p281522908084829"><a name="p281522908084829"></a><a name="p281522908084829"></a><a href="softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4">DeviceType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p918373677084829"><a name="p918373677084829"></a><a name="p918373677084829"></a>typedef enum <a href="softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a> </p>
<p id="p1392609150084829"><a name="p1392609150084829"></a><a name="p1392609150084829"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row831641204084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7136796084829"><a name="p7136796084829"></a><a name="p7136796084829"></a><a href="softbus.md#gab622f2f40d12121620d464e43635a09b">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417245575084829"><a name="p1417245575084829"></a><a name="p1417245575084829"></a>typedef struct <a href="ipublishcallback.md">IPublishCallback</a> </p>
<p id="p789162881084829"><a name="p789162881084829"></a><a name="p789162881084829"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row1880837001084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2081741278084829"><a name="p2081741278084829"></a><a name="p2081741278084829"></a><a href="softbus.md#ga8dc0eb993aea9593f96da339edf042ff">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1777766772084829"><a name="p1777766772084829"></a><a name="p1777766772084829"></a>typedef struct <a href="commondeviceinfo.md">CommonDeviceInfo</a> </p>
<p id="p410458846084829"><a name="p410458846084829"></a><a name="p410458846084829"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2144524186084829"></a>
<table><thead align="left"><tr id="row632299668084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1642967045084829"><a name="p1642967045084829"></a><a name="p1642967045084829"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p357303118084829"><a name="p357303118084829"></a><a name="p357303118084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1007889117084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1061727002084829"><a name="p1061727002084829"></a><a name="p1061727002084829"></a><a href="softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b">ExchanageMedium</a> { <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6">AUTO</a> = 0, <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a">BLE</a> = 1, <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195">COAP</a> = 2, <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761">USB</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1272596469084829"><a name="p1272596469084829"></a><a name="p1272596469084829"></a>Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services. </p>
</td>
</tr>
<tr id="row1754036231084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1015327798084829"><a name="p1015327798084829"></a><a name="p1015327798084829"></a><a href="softbus.md#gacf2c77bd7e2c82784078762978123ea3">ExchangeFre</a> { <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8">LOW</a> = 0, <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236">MID</a> = 1, <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893">HIGH</a> = 2, <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc">SUPER_HIGH</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68222552084829"><a name="p68222552084829"></a><a name="p68222552084829"></a>Enumerates frequencies for publishing services. This enumeration is involved only in Bluetooth and is not supported currently. </p>
</td>
</tr>
<tr id="row862508646084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p575056219084829"><a name="p575056219084829"></a><a name="p575056219084829"></a><a href="softbus.md#ga7369479474cf45e9ca9c0f756473c74f">DiscoverMode</a> { <a href="softbus.md#gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf">DISCOVER_MODE_PASSIVE</a> = 0x55, <a href="softbus.md#gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb">DISCOVER_MODE_ACTIVE</a> = 0xAA }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1520813352084829"><a name="p1520813352084829"></a><a name="p1520813352084829"></a>Enumerates the modes in which services are published. The publishing service supports the passive mode. Lite devices support the passive mode only. </p>
</td>
</tr>
<tr id="row758538390084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p352273398084829"><a name="p352273398084829"></a><a name="p352273398084829"></a><a href="softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620">PublishFailReason</a> { <a href="softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d">PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM</a> = 1, <a href="softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca">PUBLISH_FAIL_REASON_PARAMETER_INVALID</a> = 2, <a href="softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f">PUBLISH_FAIL_REASON_UNKNOWN</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423365486084829"><a name="p423365486084829"></a><a name="p423365486084829"></a>Enumerates failure reasons for publishing services. </p>
</td>
</tr>
<tr id="row142090791084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1533621369084829"><a name="p1533621369084829"></a><a name="p1533621369084829"></a><a href="softbus.md#gab839c7f1fd448f52f003ab0693f27bb4">DataBitMap</a> {   <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c">HICALL_CAPABILITY_BITMAP</a> = 0, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3">PROFILE_CAPABILITY_BITMAP</a> = 1, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2">HOMEVISIONPIC_CAPABILITY_BITMAP</a> = 2, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f">CASTPLUS_CAPABILITY_BITMAP</a>,   <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3">AA_CAPABILITY_BITMAP</a>, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8">DVKIT_CAPABILITY_BITMAP</a>, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b">DDMP_CAPABILITY_BITMAP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p318507935084829"><a name="p318507935084829"></a><a name="p318507935084829"></a>Enumerates supported capabilities published by a device. </p>
</td>
</tr>
<tr id="row1507670522084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500300172084829"><a name="p500300172084829"></a><a name="p500300172084829"></a><a href="softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a> {   <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9">UNKOWN</a> = 0x00, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1">PHONE</a> = 0x0E, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2">PAD</a> = 0x11, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2">TV</a> = 0x9C,   <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46">PC</a> = 0x0C, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd">AUDIO</a> = 0x0A, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40">CAR</a> = 0x83, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9">L0</a> = 0xF1,   <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543">L1</a> = 0xF2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963513798084829"><a name="p963513798084829"></a><a name="p963513798084829"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row907013790084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p88349120084829"><a name="p88349120084829"></a><a name="p88349120084829"></a><a href="softbus.md#ga25be99ffbe88e41f7ce51d2678010254">CommonDeviceKey</a> { <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10">COMM_DEVICE_KEY_DEVID</a> = 0, <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816">COMM_DEVICE_KEY_DEVTYPE</a> = 1, <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341">COMM_DEVICE_KEY_DEVNAME</a> = 2, <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84">COMM_DEVICE_KEY_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1836727706084829"><a name="p1836727706084829"></a><a name="p1836727706084829"></a>Enumerates device information, such as its ID, type, and name. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2133294844084829"></a>
<table><thead align="left"><tr id="row1357710724084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1629864132084829"><a name="p1629864132084829"></a><a name="p1629864132084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2125937335084829"><a name="p2125937335084829"></a><a name="p2125937335084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1184919613084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870839655084829"><a name="p1870839655084829"></a><a name="p1870839655084829"></a><a href="softbus.md#ga010557e05b3f0b0b1a05157f1724e13a">PublishService</a> (const char *moduleName, const struct <a href="publishinfo.md">PublishInfo</a> *info, const struct <a href="ipublishcallback.md">IPublishCallback</a> *cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647305267084829"><a name="p647305267084829"></a><a name="p647305267084829"></a>int </p>
<p id="p69917097084829"><a name="p69917097084829"></a><a name="p69917097084829"></a>Publishes a service to the discovering device in the LAN. </p>
</td>
</tr>
<tr id="row120982794084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p698689724084829"><a name="p698689724084829"></a><a name="p698689724084829"></a><a href="softbus.md#gac9463e62e324155634c01facdf642ea7">UnPublishService</a> (const char *moduleName, int publishId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565879832084829"><a name="p1565879832084829"></a><a name="p1565879832084829"></a>int </p>
<p id="p402413612084829"><a name="p402413612084829"></a><a name="p402413612084829"></a>Unpublishes a service based on the <strong id="b12455991084829"><a name="b12455991084829"></a><a name="b12455991084829"></a>publicId</strong> and <strong id="b649837484084829"><a name="b649837484084829"></a><a name="b649837484084829"></a>moduleName</strong>. </p>
</td>
</tr>
<tr id="row1676186209084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873873801084829"><a name="p1873873801084829"></a><a name="p1873873801084829"></a><a href="softbus.md#gaca3ae566d98727d111befb4a642bafc4">SetCommonDeviceInfo</a> (const struct <a href="commondeviceinfo.md">CommonDeviceInfo</a> *devInfo, unsigned int num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p363254311084829"><a name="p363254311084829"></a><a name="p363254311084829"></a>int </p>
<p id="p430277308084829"><a name="p430277308084829"></a><a name="p430277308084829"></a>Sets common device information, such as its ID, type, and name. </p>
</td>
</tr>
</tbody>
</table>

