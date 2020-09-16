# Softbus<a name="EN-US_TOPIC_0000001055678044"></a>

## **Overview**<a name="section352358142084826"></a>

Provides high-speed, secure communication between devices. 

This module implements unified distributed communication capability management between nearby devices, and provides link-independent device discovery and transmission interfaces to support service publishing and data transmission.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1849133813084826"></a>

## Files<a name="files"></a>

<a name="table2140505628084826"></a>
<table><thead align="left"><tr id="row1455608571084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1891135614084826"><a name="p1891135614084826"></a><a name="p1891135614084826"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1840523383084826"><a name="p1840523383084826"></a><a name="p1840523383084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row888298876084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119750213084826"><a name="p1119750213084826"></a><a name="p1119750213084826"></a><a href="discovery_service-h.md">discovery_service.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402839537084826"><a name="p402839537084826"></a><a name="p402839537084826"></a>Declares unified device service publishing interfaces. </p>
</td>
</tr>
<tr id="row1132313724084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p121539367084826"><a name="p121539367084826"></a><a name="p121539367084826"></a><a href="session-h.md">session.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1457475409084826"><a name="p1457475409084826"></a><a name="p1457475409084826"></a>Declares unified data transmission interfaces. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table2139954542084826"></a>
<table><thead align="left"><tr id="row1910957613084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1408141239084826"><a name="p1408141239084826"></a><a name="p1408141239084826"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1175180734084826"><a name="p1175180734084826"></a><a name="p1175180734084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row770885014084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p757382244084826"><a name="p757382244084826"></a><a name="p757382244084826"></a><a href="publishinfo.md">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1848096791084826"><a name="p1848096791084826"></a><a name="p1848096791084826"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row2013345933084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176535025084826"><a name="p176535025084826"></a><a name="p176535025084826"></a><a href="capabilitymap.md">CapabilityMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p621255296084826"><a name="p621255296084826"></a><a name="p621255296084826"></a>Defines the mapping between supported capabilities and bitmaps. </p>
</td>
</tr>
<tr id="row1885888274084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1058413366084826"><a name="p1058413366084826"></a><a name="p1058413366084826"></a><a href="devicemap.md">DeviceMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1282047040084826"><a name="p1282047040084826"></a><a name="p1282047040084826"></a>Defines the mappings between the device type enumerations and device type names. </p>
</td>
</tr>
<tr id="row1822655937084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619561714084826"><a name="p1619561714084826"></a><a name="p1619561714084826"></a><a href="ipublishcallback.md">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310607020084826"><a name="p1310607020084826"></a><a name="p1310607020084826"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row1449608605084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p757218573084826"><a name="p757218573084826"></a><a name="p757218573084826"></a><a href="commondeviceinfo.md">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1781252661084826"><a name="p1781252661084826"></a><a name="p1781252661084826"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
<tr id="row963433143084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p834540194084826"><a name="p834540194084826"></a><a name="p834540194084826"></a><a href="isessionlistener.md">ISessionListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p112168045084826"><a name="p112168045084826"></a><a name="p112168045084826"></a>Defines session callbacks. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1766153470084826"></a>
<table><thead align="left"><tr id="row11521638084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p48187010084826"><a name="p48187010084826"></a><a name="p48187010084826"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p893002590084826"><a name="p893002590084826"></a><a name="p893002590084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row579805314084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1201821514084826"><a name="p1201821514084826"></a><a name="p1201821514084826"></a><a href="softbus.md#gae0bb52450c28ea9be1c5475d0d89830e">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67695395084826"><a name="p67695395084826"></a><a name="p67695395084826"></a>typedef struct <a href="publishinfo.md">PublishInfo</a> </p>
<p id="p409707776084826"><a name="p409707776084826"></a><a name="p409707776084826"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row788728403084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p450466293084826"><a name="p450466293084826"></a><a name="p450466293084826"></a><a href="softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4">DeviceType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p692880543084826"><a name="p692880543084826"></a><a name="p692880543084826"></a>typedef enum <a href="softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a> </p>
<p id="p1962897187084826"><a name="p1962897187084826"></a><a name="p1962897187084826"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row1649975854084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2112338524084826"><a name="p2112338524084826"></a><a name="p2112338524084826"></a><a href="softbus.md#gab622f2f40d12121620d464e43635a09b">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199910831084826"><a name="p1199910831084826"></a><a name="p1199910831084826"></a>typedef struct <a href="ipublishcallback.md">IPublishCallback</a> </p>
<p id="p361927622084826"><a name="p361927622084826"></a><a name="p361927622084826"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row740098139084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1743457550084826"><a name="p1743457550084826"></a><a name="p1743457550084826"></a><a href="softbus.md#ga8dc0eb993aea9593f96da339edf042ff">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1582616954084826"><a name="p1582616954084826"></a><a name="p1582616954084826"></a>typedef struct <a href="commondeviceinfo.md">CommonDeviceInfo</a> </p>
<p id="p472532179084826"><a name="p472532179084826"></a><a name="p472532179084826"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1710038563084826"></a>
<table><thead align="left"><tr id="row1412486752084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1301739476084826"><a name="p1301739476084826"></a><a name="p1301739476084826"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p380656488084826"><a name="p380656488084826"></a><a name="p380656488084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row883183268084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567961531084826"><a name="p1567961531084826"></a><a name="p1567961531084826"></a><a href="softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b">ExchanageMedium</a> { <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6">AUTO</a> = 0, <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a">BLE</a> = 1, <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195">COAP</a> = 2, <a href="softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761">USB</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p337628627084826"><a name="p337628627084826"></a><a name="p337628627084826"></a>Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services. </p>
</td>
</tr>
<tr id="row443171285084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564541947084826"><a name="p1564541947084826"></a><a name="p1564541947084826"></a><a href="softbus.md#gacf2c77bd7e2c82784078762978123ea3">ExchangeFre</a> { <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8">LOW</a> = 0, <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236">MID</a> = 1, <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893">HIGH</a> = 2, <a href="softbus.md#ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc">SUPER_HIGH</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p78350382084826"><a name="p78350382084826"></a><a name="p78350382084826"></a>Enumerates frequencies for publishing services. This enumeration is involved only in Bluetooth and is not supported currently. </p>
</td>
</tr>
<tr id="row425637528084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1458522032084826"><a name="p1458522032084826"></a><a name="p1458522032084826"></a><a href="softbus.md#ga7369479474cf45e9ca9c0f756473c74f">DiscoverMode</a> { <a href="softbus.md#gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf">DISCOVER_MODE_PASSIVE</a> = 0x55, <a href="softbus.md#gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb">DISCOVER_MODE_ACTIVE</a> = 0xAA }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304811890084826"><a name="p304811890084826"></a><a name="p304811890084826"></a>Enumerates the modes in which services are published. The publishing service supports the passive mode. Lite devices support the passive mode only. </p>
</td>
</tr>
<tr id="row970941026084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735895014084826"><a name="p735895014084826"></a><a name="p735895014084826"></a><a href="softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620">PublishFailReason</a> { <a href="softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d">PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM</a> = 1, <a href="softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca">PUBLISH_FAIL_REASON_PARAMETER_INVALID</a> = 2, <a href="softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f">PUBLISH_FAIL_REASON_UNKNOWN</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513268860084826"><a name="p1513268860084826"></a><a name="p1513268860084826"></a>Enumerates failure reasons for publishing services. </p>
</td>
</tr>
<tr id="row579510567084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p258566176084826"><a name="p258566176084826"></a><a name="p258566176084826"></a><a href="softbus.md#gab839c7f1fd448f52f003ab0693f27bb4">DataBitMap</a> {   <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c">HICALL_CAPABILITY_BITMAP</a> = 0, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3">PROFILE_CAPABILITY_BITMAP</a> = 1, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2">HOMEVISIONPIC_CAPABILITY_BITMAP</a> = 2, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f">CASTPLUS_CAPABILITY_BITMAP</a>,   <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3">AA_CAPABILITY_BITMAP</a>, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8">DVKIT_CAPABILITY_BITMAP</a>, <a href="softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b">DDMP_CAPABILITY_BITMAP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p774992679084826"><a name="p774992679084826"></a><a name="p774992679084826"></a>Enumerates supported capabilities published by a device. </p>
</td>
</tr>
<tr id="row166654271084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p330144356084826"><a name="p330144356084826"></a><a name="p330144356084826"></a><a href="softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a> {   <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9">UNKOWN</a> = 0x00, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1">PHONE</a> = 0x0E, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2">PAD</a> = 0x11, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2">TV</a> = 0x9C,   <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46">PC</a> = 0x0C, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd">AUDIO</a> = 0x0A, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40">CAR</a> = 0x83, <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9">L0</a> = 0xF1,   <a href="softbus.md#ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543">L1</a> = 0xF2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p93936944084826"><a name="p93936944084826"></a><a name="p93936944084826"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row407461483084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1004340918084826"><a name="p1004340918084826"></a><a name="p1004340918084826"></a><a href="softbus.md#ga25be99ffbe88e41f7ce51d2678010254">CommonDeviceKey</a> { <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10">COMM_DEVICE_KEY_DEVID</a> = 0, <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816">COMM_DEVICE_KEY_DEVTYPE</a> = 1, <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341">COMM_DEVICE_KEY_DEVNAME</a> = 2, <a href="softbus.md#gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84">COMM_DEVICE_KEY_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1095997458084826"><a name="p1095997458084826"></a><a name="p1095997458084826"></a>Enumerates device information, such as its ID, type, and name. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1246075979084826"></a>
<table><thead align="left"><tr id="row1862776811084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p124837019084826"><a name="p124837019084826"></a><a name="p124837019084826"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1900097445084826"><a name="p1900097445084826"></a><a name="p1900097445084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1882894076084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1576494949084826"><a name="p1576494949084826"></a><a name="p1576494949084826"></a><a href="softbus.md#ga010557e05b3f0b0b1a05157f1724e13a">PublishService</a> (const char *moduleName, const struct <a href="publishinfo.md">PublishInfo</a> *info, const struct <a href="ipublishcallback.md">IPublishCallback</a> *cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2116880075084826"><a name="p2116880075084826"></a><a name="p2116880075084826"></a>int </p>
<p id="p762890552084826"><a name="p762890552084826"></a><a name="p762890552084826"></a>Publishes a service to the discovering device in the LAN. </p>
</td>
</tr>
<tr id="row454460556084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1112653090084826"><a name="p1112653090084826"></a><a name="p1112653090084826"></a><a href="softbus.md#gac9463e62e324155634c01facdf642ea7">UnPublishService</a> (const char *moduleName, int publishId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1891304307084826"><a name="p1891304307084826"></a><a name="p1891304307084826"></a>int </p>
<p id="p2099420213084826"><a name="p2099420213084826"></a><a name="p2099420213084826"></a>Unpublishes a service based on the <strong id="b437843222084826"><a name="b437843222084826"></a><a name="b437843222084826"></a>publicId</strong> and <strong id="b944085932084826"><a name="b944085932084826"></a><a name="b944085932084826"></a>moduleName</strong>. </p>
</td>
</tr>
<tr id="row1533114259084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772888179084826"><a name="p1772888179084826"></a><a name="p1772888179084826"></a><a href="softbus.md#gaca3ae566d98727d111befb4a642bafc4">SetCommonDeviceInfo</a> (const struct <a href="commondeviceinfo.md">CommonDeviceInfo</a> *devInfo, unsigned int num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1347007771084826"><a name="p1347007771084826"></a><a name="p1347007771084826"></a>int </p>
<p id="p835095383084826"><a name="p835095383084826"></a><a name="p835095383084826"></a>Sets common device information, such as its ID, type, and name. </p>
</td>
</tr>
<tr id="row42686537084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1374292058084826"><a name="p1374292058084826"></a><a name="p1374292058084826"></a><a href="softbus.md#gad7e95cced3378e8f489553d70b121392">CreateSessionServer</a> (const char *mouduleName, const char *sessionName, struct <a href="isessionlistener.md">ISessionListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2022856984084826"><a name="p2022856984084826"></a><a name="p2022856984084826"></a>int </p>
<p id="p674615282084826"><a name="p674615282084826"></a><a name="p674615282084826"></a>Creates a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row1275695126084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p343865432084826"><a name="p343865432084826"></a><a name="p343865432084826"></a><a href="softbus.md#ga225a1e178544457263d94078e638b7b5">RemoveSessionServer</a> (const char *mouduleName, const char *sessionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864101462084826"><a name="p1864101462084826"></a><a name="p1864101462084826"></a>int </p>
<p id="p1002144274084826"><a name="p1002144274084826"></a><a name="p1002144274084826"></a>Removes a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row2092952932084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p146489768084826"><a name="p146489768084826"></a><a name="p146489768084826"></a><a href="softbus.md#ga0333c76724dbef71bca48fb2a82e6980">SendBytes</a> (int sessionId, const void *data, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1113531567084826"><a name="p1113531567084826"></a><a name="p1113531567084826"></a>int </p>
<p id="p2120183718084826"><a name="p2120183718084826"></a><a name="p2120183718084826"></a>Sends data based on a session ID. </p>
</td>
</tr>
<tr id="row68912556084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1669378912084826"><a name="p1669378912084826"></a><a name="p1669378912084826"></a><a href="softbus.md#ga00611f717919f4156c74b7919b28c7d8">GetMySessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1291342699084826"><a name="p1291342699084826"></a><a name="p1291342699084826"></a>int </p>
<p id="p2089505870084826"><a name="p2089505870084826"></a><a name="p2089505870084826"></a>Obtains the session name registered by the local device based on the session ID. </p>
</td>
</tr>
<tr id="row1156361399084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628672787084826"><a name="p1628672787084826"></a><a name="p1628672787084826"></a><a href="softbus.md#ga92d5a47fcdf97a0e01797c77e644033e">GetPeerSessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798683379084826"><a name="p798683379084826"></a><a name="p798683379084826"></a>int </p>
<p id="p1394311469084826"><a name="p1394311469084826"></a><a name="p1394311469084826"></a>Obtains the session name registered by the peer device based on the session ID. </p>
</td>
</tr>
<tr id="row244828317084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1863446608084826"><a name="p1863446608084826"></a><a name="p1863446608084826"></a><a href="softbus.md#ga21b9a889069eea6e7fe653820e601c04">GetPeerDeviceId</a> (int sessionId, char *devId, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667636495084826"><a name="p667636495084826"></a><a name="p667636495084826"></a>int </p>
<p id="p658151567084826"><a name="p658151567084826"></a><a name="p658151567084826"></a>Obtains the peer device ID based on a session ID. </p>
</td>
</tr>
<tr id="row1902381658084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778035429084826"><a name="p1778035429084826"></a><a name="p1778035429084826"></a><a href="softbus.md#ga5b0c0b334f387f9c2753146ee0890780">CloseSession</a> (int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273007875084826"><a name="p1273007875084826"></a><a name="p1273007875084826"></a>void </p>
<p id="p516600274084826"><a name="p516600274084826"></a><a name="p516600274084826"></a>Closes a connected session based on a session ID. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1761302581084826"></a>

## **Typedef Documentation**<a name="section1514985769084826"></a>

## CommonDeviceInfo<a name="ga8dc0eb993aea9593f96da339edf042ff"></a>

```
typedef struct [CommonDeviceInfo](commondeviceinfo.md) [CommonDeviceInfo](commondeviceinfo.md)
```

 **Description:**

Defines the type and content of a device to set. 

## DeviceType<a name="ga9334bacb3ded964dc3c3367a6b70bcf4"></a>

```
typedef enum [DeviceTypeEnum](softbus.md#gab20b49630026f3118d6c05b0a022f230) [DeviceType](softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4)
```

 **Description:**

Enumerates device types. 

## IPublishCallback<a name="gab622f2f40d12121620d464e43635a09b"></a>

```
typedef struct [IPublishCallback](ipublishcallback.md) [IPublishCallback](ipublishcallback.md)
```

 **Description:**

Defines the callbacks for successful and failed service publishing. 

## PublishInfo<a name="gae0bb52450c28ea9be1c5475d0d89830e"></a>

```
typedef struct [PublishInfo](publishinfo.md) [PublishInfo](publishinfo.md)
```

 **Description:**

Defines service provisioning information sent to a discovering device. 

## **Enumeration Type Documentation**<a name="section363262538084826"></a>

## CommonDeviceKey<a name="ga25be99ffbe88e41f7ce51d2678010254"></a>

```
enum [CommonDeviceKey](softbus.md#ga25be99ffbe88e41f7ce51d2678010254)
```

 **Description:**

Enumerates device information, such as its ID, type, and name. 

<a name="table379779292084826"></a>
<table><thead align="left"><tr id="row367836083084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1707237655084826"><a name="p1707237655084826"></a><a name="p1707237655084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1354273044084826"><a name="p1354273044084826"></a><a name="p1354273044084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1586587207084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10"><a name="gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10"></a><a name="gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10"></a></strong>COMM_DEVICE_KEY_DEVID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p321377591084826"><a name="p321377591084826"></a><a name="p321377591084826"></a>Device ID. The value contains a maximum of 64 characters. </p>
 </td>
</tr>
<tr id="row324366149084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816"><a name="gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816"></a><a name="gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816"></a></strong>COMM_DEVICE_KEY_DEVTYPE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p617065833084826"><a name="p617065833084826"></a><a name="p617065833084826"></a>Device type. Currently, only <strong id="b2072708407084826"><a name="b2072708407084826"></a><a name="b2072708407084826"></a>ddmpCapability</strong> is supported. </p>
 </td>
</tr>
<tr id="row988073840084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341"><a name="gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341"></a><a name="gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341"></a></strong>COMM_DEVICE_KEY_DEVNAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p708028533084826"><a name="p708028533084826"></a><a name="p708028533084826"></a>Device name. The value contains a maximum of 63 characters. </p>
 </td>
</tr>
<tr id="row2116358203084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84"><a name="gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84"></a><a name="gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84"></a></strong>COMM_DEVICE_KEY_MAX </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437577523084826"><a name="p437577523084826"></a><a name="p437577523084826"></a>Reserved </p>
 </td>
</tr>
</tbody>
</table>

## DataBitMap<a name="gab839c7f1fd448f52f003ab0693f27bb4"></a>

```
enum [DataBitMap](softbus.md#gab839c7f1fd448f52f003ab0693f27bb4)
```

 **Description:**

Enumerates supported capabilities published by a device. 

<a name="table544553440084826"></a>
<table><thead align="left"><tr id="row1771648352084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1652666140084826"><a name="p1652666140084826"></a><a name="p1652666140084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1272847588084826"><a name="p1272847588084826"></a><a name="p1272847588084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row347469010084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c"></a></strong>HICALL_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2042378859084826"><a name="p2042378859084826"></a><a name="p2042378859084826"></a>MeeTime </p>
 </td>
</tr>
<tr id="row1221706438084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3"></a></strong>PROFILE_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122462696084826"><a name="p1122462696084826"></a><a name="p1122462696084826"></a>Video reverse connection in the smart domain </p>
 </td>
</tr>
<tr id="row422851111084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2"></a></strong>HOMEVISIONPIC_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155156506084826"><a name="p1155156506084826"></a><a name="p1155156506084826"></a>Gallery in Vision </p>
 </td>
</tr>
<tr id="row199989573084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f"><a name="ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f"></a></strong>CASTPLUS_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824687316084826"><a name="p1824687316084826"></a><a name="p1824687316084826"></a>cast+ </p>
 </td>
</tr>
<tr id="row1657174351084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3"><a name="ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3"></a></strong>AA_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1035431235084826"><a name="p1035431235084826"></a><a name="p1035431235084826"></a>Input method in Vision </p>
 </td>
</tr>
<tr id="row391846446084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8"><a name="ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8"></a></strong>DVKIT_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681301167084826"><a name="p1681301167084826"></a><a name="p1681301167084826"></a>Device virtualization tool package </p>
 </td>
</tr>
<tr id="row918633199084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b"><a name="ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b"></a><a name="ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b"></a></strong>DDMP_CAPABILITY_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1263495932084826"><a name="p1263495932084826"></a><a name="p1263495932084826"></a>Distributed middleware </p>
 </td>
</tr>
</tbody>
</table>

## DeviceTypeEnum<a name="gab20b49630026f3118d6c05b0a022f230"></a>

```
enum [DeviceTypeEnum](softbus.md#gab20b49630026f3118d6c05b0a022f230)
```

 **Description:**

Enumerates device types. 

<a name="table1834489418084826"></a>
<table><thead align="left"><tr id="row886841506084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1844878205084826"><a name="p1844878205084826"></a><a name="p1844878205084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1708810097084826"><a name="p1708810097084826"></a><a name="p1708810097084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row242128106084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9"><a name="ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9"></a><a name="ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9"></a></strong>UNKOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1645369544084826"><a name="p1645369544084826"></a><a name="p1645369544084826"></a>Unknown </p>
 </td>
</tr>
<tr id="row1369909725084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1"><a name="ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1"></a><a name="ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1"></a></strong>PHONE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p598352562084826"><a name="p598352562084826"></a><a name="p598352562084826"></a>Smartphone </p>
 </td>
</tr>
<tr id="row2041501042084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2"><a name="ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2"></a><a name="ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2"></a></strong>PAD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p294635870084826"><a name="p294635870084826"></a><a name="p294635870084826"></a>Tablet </p>
 </td>
</tr>
<tr id="row1396370946084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2"><a name="ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2"></a><a name="ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2"></a></strong>TV </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375660981084826"><a name="p375660981084826"></a><a name="p375660981084826"></a>Smart TV </p>
 </td>
</tr>
<tr id="row468128129084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46"><a name="ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46"></a><a name="ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46"></a></strong>PC </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1968208196084826"><a name="p1968208196084826"></a><a name="p1968208196084826"></a>PC </p>
 </td>
</tr>
<tr id="row325787577084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd"><a name="ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd"></a><a name="ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd"></a></strong>AUDIO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1534044239084826"><a name="p1534044239084826"></a><a name="p1534044239084826"></a>Audio device </p>
 </td>
</tr>
<tr id="row1853972830084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40"><a name="ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40"></a><a name="ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40"></a></strong>CAR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175518070084826"><a name="p1175518070084826"></a><a name="p1175518070084826"></a>Vehicle-mounted device </p>
 </td>
</tr>
<tr id="row1273227036084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9"><a name="ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9"></a><a name="ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9"></a></strong>L0 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1631600643084826"><a name="p1631600643084826"></a><a name="p1631600643084826"></a>Light device L0 </p>
 </td>
</tr>
<tr id="row1388296430084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543"><a name="ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543"></a><a name="ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543"></a></strong>L1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140196247084826"><a name="p140196247084826"></a><a name="p140196247084826"></a>Light device L1 </p>
 </td>
</tr>
</tbody>
</table>

## DiscoverMode<a name="ga7369479474cf45e9ca9c0f756473c74f"></a>

```
enum [DiscoverMode](softbus.md#ga7369479474cf45e9ca9c0f756473c74f)
```

 **Description:**

Enumerates the modes in which services are published. The publishing service supports the passive mode. Lite devices support the passive mode only. 

<a name="table1736942305084826"></a>
<table><thead align="left"><tr id="row485647326084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p93936816084826"><a name="p93936816084826"></a><a name="p93936816084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1296273094084826"><a name="p1296273094084826"></a><a name="p1296273094084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row381915687084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf"><a name="gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf"></a><a name="gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf"></a></strong>DISCOVER_MODE_PASSIVE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p774808019084826"><a name="p774808019084826"></a><a name="p774808019084826"></a>Passive </p>
 </td>
</tr>
<tr id="row1141752691084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb"><a name="gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb"></a><a name="gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb"></a></strong>DISCOVER_MODE_ACTIVE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348230146084826"><a name="p348230146084826"></a><a name="p348230146084826"></a>Proactive </p>
 </td>
</tr>
</tbody>
</table>

## ExchanageMedium<a name="gaf5c7c122990f0ab5bd46b9bc47b5868b"></a>

```
enum [ExchanageMedium](softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b)
```

 **Description:**

Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services. 

Currently, the media can only be set to coap. 

<a name="table1006376855084826"></a>
<table><thead align="left"><tr id="row1489335750084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2036322482084826"><a name="p2036322482084826"></a><a name="p2036322482084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1744521509084826"><a name="p1744521509084826"></a><a name="p1744521509084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1389763089084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6"></a></strong>AUTO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1368271923084826"><a name="p1368271923084826"></a><a name="p1368271923084826"></a>Automatic medium selection </p>
 </td>
</tr>
<tr id="row771870356084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a"></a></strong>BLE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003630719084826"><a name="p2003630719084826"></a><a name="p2003630719084826"></a>Bluetooth </p>
 </td>
</tr>
<tr id="row2024727910084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195"></a></strong>COAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1544201875084826"><a name="p1544201875084826"></a><a name="p1544201875084826"></a>Wi-Fi </p>
 </td>
</tr>
<tr id="row1297716956084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761"><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761"></a><a name="ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761"></a></strong>USB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310673453084826"><a name="p1310673453084826"></a><a name="p1310673453084826"></a>USB </p>
 </td>
</tr>
</tbody>
</table>

## ExchangeFre<a name="gacf2c77bd7e2c82784078762978123ea3"></a>

```
enum [ExchangeFre](softbus.md#gacf2c77bd7e2c82784078762978123ea3)
```

 **Description:**

Enumerates frequencies for publishing services. This enumeration is involved only in Bluetooth and is not supported currently. 

<a name="table458080930084826"></a>
<table><thead align="left"><tr id="row1574403379084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1038402190084826"><a name="p1038402190084826"></a><a name="p1038402190084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1145043548084826"><a name="p1145043548084826"></a><a name="p1145043548084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2134655078084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8"><a name="ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8"></a></strong>LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1613269007084826"><a name="p1613269007084826"></a><a name="p1613269007084826"></a>Low </p>
 </td>
</tr>
<tr id="row1311417290084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236"><a name="ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236"></a></strong>MID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202605610084826"><a name="p1202605610084826"></a><a name="p1202605610084826"></a>Medium </p>
 </td>
</tr>
<tr id="row947280872084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893"><a name="ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893"></a></strong>HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1262296288084826"><a name="p1262296288084826"></a><a name="p1262296288084826"></a>High </p>
 </td>
</tr>
<tr id="row813132537084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc"><a name="ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc"></a><a name="ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc"></a></strong>SUPER_HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1613433000084826"><a name="p1613433000084826"></a><a name="p1613433000084826"></a>Super-high </p>
 </td>
</tr>
</tbody>
</table>

## PublishFailReason<a name="ga6632fcae1db4a3a13370e3fb49e5e620"></a>

```
enum [PublishFailReason](softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620)
```

 **Description:**

Enumerates failure reasons for publishing services. 

The failure reason is returned to the caller through the callback function. 

<a name="table885960628084826"></a>
<table><thead align="left"><tr id="row1911374133084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2020363898084826"><a name="p2020363898084826"></a><a name="p2020363898084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1287138649084826"><a name="p1287138649084826"></a><a name="p1287138649084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row903429588084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d"><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d"></a><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d"></a></strong>PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p43603238084826"><a name="p43603238084826"></a><a name="p43603238084826"></a>Unsupported medium </p>
 </td>
</tr>
<tr id="row1868700142084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca"><a name="gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca"></a><a name="gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca"></a></strong>PUBLISH_FAIL_REASON_PARAMETER_INVALID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1728701152084826"><a name="p1728701152084826"></a><a name="p1728701152084826"></a>Invalid parameter </p>
 </td>
</tr>
<tr id="row1896688223084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f"><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f"></a><a name="gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f"></a></strong>PUBLISH_FAIL_REASON_UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140427638084826"><a name="p2140427638084826"></a><a name="p2140427638084826"></a>Unknown reason </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1492985913084826"></a>

## CloseSession\(\)<a name="ga5b0c0b334f387f9c2753146ee0890780"></a>

```
void CloseSession (int sessionId)
```

 **Description:**

Closes a connected session based on a session ID. 

**Parameters:**

<a name="table337010934084826"></a>
<table><thead align="left"><tr id="row871901384084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p147135690084826"><a name="p147135690084826"></a><a name="p147135690084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1675541190084826"><a name="p1675541190084826"></a><a name="p1675541190084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1462447443084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
</tbody>
</table>

## CreateSessionServer\(\)<a name="gad7e95cced3378e8f489553d70b121392"></a>

```
int CreateSessionServer (const char * mouduleName, const char * sessionName, struct [ISessionListener](isessionlistener.md) * listener )
```

 **Description:**

Creates a session server based on a module name and session name. 

A maximum of 18 session servers can be created.

**Parameters:**

<a name="table1824347628084826"></a>
<table><thead align="left"><tr id="row1994966528084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p633864518084826"><a name="p633864518084826"></a><a name="p633864518084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1072738826084826"><a name="p1072738826084826"></a><a name="p1072738826084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row705820965084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module name, which can be used to check whether the session server is in this module. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
<tr id="row628423559084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the session name, which is the unique ID of the session server. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
<tr id="row1846255882084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">listener</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the session callback structure, which cannot be empty. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 

**See also:**

[RemoveSessionServer](softbus.md#ga225a1e178544457263d94078e638b7b5) 

## GetMySessionName\(\)<a name="ga00611f717919f4156c74b7919b28c7d8"></a>

```
int GetMySessionName (int sessionId, char * sessionName, unsigned int len )
```

 **Description:**

Obtains the session name registered by the local device based on the session ID. 

**Parameters:**

<a name="table1876009271084826"></a>
<table><thead align="left"><tr id="row1093496448084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p175525575084826"><a name="p175525575084826"></a><a name="p175525575084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p395345183084826"><a name="p395345183084826"></a><a name="p395345183084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row481554885084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row200622033084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the session name. </td>
</tr>
<tr id="row223303878084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## GetPeerDeviceId\(\)<a name="ga21b9a889069eea6e7fe653820e601c04"></a>

```
int GetPeerDeviceId (int sessionId, char * devId, unsigned int len )
```

 **Description:**

Obtains the peer device ID based on a session ID. 

**Parameters:**

<a name="table19756429084826"></a>
<table><thead align="left"><tr id="row680664922084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p475906289084826"><a name="p475906289084826"></a><a name="p475906289084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2095272769084826"><a name="p2095272769084826"></a><a name="p2095272769084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row858809078084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row19881490084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the device ID. </td>
</tr>
<tr id="row1472277011084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## GetPeerSessionName\(\)<a name="ga92d5a47fcdf97a0e01797c77e644033e"></a>

```
int GetPeerSessionName (int sessionId, char * sessionName, unsigned int len )
```

 **Description:**

Obtains the session name registered by the peer device based on the session ID. 

**Parameters:**

<a name="table111264919084826"></a>
<table><thead align="left"><tr id="row926642518084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1492548738084826"><a name="p1492548738084826"></a><a name="p1492548738084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1689539876084826"><a name="p1689539876084826"></a><a name="p1689539876084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row137617519084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row1248343140084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the session name. </td>
</tr>
<tr id="row494303810084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## PublishService\(\)<a name="ga010557e05b3f0b0b1a05157f1724e13a"></a>

```
int PublishService (const char * moduleName, const struct [PublishInfo](publishinfo.md) * info, const struct [IPublishCallback](ipublishcallback.md) * cb )
```

 **Description:**

Publishes a service to the discovering device in the LAN. 

The  **publicId**  and  **moduleName**  uniquely identify a service. A maximum of three services can be published.

**Parameters:**

<a name="table78367569084826"></a>
<table><thead align="left"><tr id="row1058939735084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p345043156084826"><a name="p345043156084826"></a><a name="p345043156084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p24658190084826"><a name="p24658190084826"></a><a name="p24658190084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row145621336084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module name of the upper-layer service. The value contains a maximum of 63 bytes. </td>
</tr>
<tr id="row893817337084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the service to publish. For details, see <a href="publishinfo.md">PublishInfo</a>. </td>
</tr>
<tr id="row378192610084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the callback for service publishing. For details, see <a href="ipublishcallback.md">IPublishCallback</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## RemoveSessionServer\(\)<a name="ga225a1e178544457263d94078e638b7b5"></a>

```
int RemoveSessionServer (const char * mouduleName, const char * sessionName )
```

 **Description:**

Removes a session server based on a module name and session name. 

**Parameters:**

<a name="table1016640419084826"></a>
<table><thead align="left"><tr id="row829994423084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p254741406084826"><a name="p254741406084826"></a><a name="p254741406084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1498719025084826"><a name="p1498719025084826"></a><a name="p1498719025084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1411272163084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the registered module, which can be used to check whether the session server is in this module. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
<tr id="row1552367579084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the session name. The value cannot be empty and can contain a maximum of 64 characters. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 

**See also:**

[CreateSessionServer](softbus.md#gad7e95cced3378e8f489553d70b121392) 

## SendBytes\(\)<a name="ga0333c76724dbef71bca48fb2a82e6980"></a>

```
int SendBytes (int sessionId, const void * data, unsigned int len )
```

 **Description:**

Sends data based on a session ID. 

**Parameters:**

<a name="table1248745023084826"></a>
<table><thead align="left"><tr id="row782536415084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p358749403084826"><a name="p358749403084826"></a><a name="p358749403084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2039521941084826"><a name="p2039521941084826"></a><a name="p2039521941084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row871148033084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row266312763084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to send, which cannot be <strong id="b1337171376084826"><a name="b1337171376084826"></a><a name="b1337171376084826"></a>NULL</strong>. </td>
</tr>
<tr id="row1435373753084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to send. The maximum length cannot exceed 984 characters. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the function is called successfully; returns  **-1**  otherwise. 



## SetCommonDeviceInfo\(\)<a name="gaca3ae566d98727d111befb4a642bafc4"></a>

```
int SetCommonDeviceInfo (const struct [CommonDeviceInfo](commondeviceinfo.md) * devInfo, unsigned int num )
```

 **Description:**

Sets common device information, such as its ID, type, and name. 

**Parameters:**

<a name="table769129421084826"></a>
<table><thead align="left"><tr id="row2129973445084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1417875425084826"><a name="p1417875425084826"></a><a name="p1417875425084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1788286578084826"><a name="p1788286578084826"></a><a name="p1788286578084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row720930152084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device information array. </td>
</tr>
<tr id="row952103749084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">2</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">num Indicates the number of elements in the device information array. If the value is inconsistent with the length of the device information array, the program breaks down. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 

**See also:**

[PublishService](softbus.md#ga010557e05b3f0b0b1a05157f1724e13a) 

## UnPublishService\(\)<a name="gac9463e62e324155634c01facdf642ea7"></a>

```
int UnPublishService (const char * moduleName, int publishId )
```

 **Description:**

Unpublishes a service based on the  **publicId**  and  **moduleName**. 

**Parameters:**

<a name="table932275683084826"></a>
<table><thead align="left"><tr id="row1538782133084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1831169438084826"><a name="p1831169438084826"></a><a name="p1831169438084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1482533808084826"><a name="p1482533808084826"></a><a name="p1482533808084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row163848431084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module name of the upper-layer service. The value contains a maximum of 63 bytes. </td>
</tr>
<tr id="row1182410031084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">publishId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the service to unpublish. The value must be greater than <strong id="b617011476084826"><a name="b617011476084826"></a><a name="b617011476084826"></a>0</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## **Variable Documentation**<a name="section1086104357084826"></a>

## bitmap<a name="gaccfbfe7a48ef51a2bada9a711dfe8cdb"></a>

```
[DataBitMap](softbus.md#gab839c7f1fd448f52f003ab0693f27bb4) CapabilityMap::bitmap
```

 **Description:**

Bitmaps. For details, see  [DataBitMap](softbus.md#gab839c7f1fd448f52f003ab0693f27bb4). 

## capability \[1/2\]<a name="gacf7c1f9daf2bf9c148ab9d8048d75358"></a>

```
const char* PublishInfo::capability
```

 **Description:**

[Service](service.md)  publishing capabilities. For details, see  **g\_capabilityMap**. 

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
[DeviceType](softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4) DeviceMap::devType
```

 **Description:**

Enumeration of a device type. Only enumerations defined in  **g\_devMap**  are supported. 

## freq<a name="gaf850489236b0efbc4b27ea5a867ec001"></a>

```
[ExchangeFre](softbus.md#gacf2c77bd7e2c82784078762978123ea3) PublishInfo::freq
```

 **Description:**

[Service](service.md)  publishing frequency 

## key<a name="gaf3ee5a07a887ab31517318e0d4ea8cc4"></a>

```
[CommonDeviceKey](softbus.md#ga25be99ffbe88e41f7ce51d2678010254) CommonDeviceInfo::key
```

 **Description:**

Device information type. For details, see  [CommonDeviceKey](softbus.md#ga25be99ffbe88e41f7ce51d2678010254). 

## medium<a name="ga3997803d8bfec79f5ba6e264f8e35b52"></a>

```
[ExchanageMedium](softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b) PublishInfo::medium
```

 **Description:**

[Service](service.md)  publishing medium 

## mode<a name="ga1e1635bcdb216cd4a4756c4962c3f595"></a>

```
int PublishInfo::mode
```

 **Description:**

[Service](service.md)  publishing mode, which can be  [DISCOVER\_MODE\_PASSIVE](softbus.md#gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf)  or  [DISCOVER\_MODE\_ACTIVE](softbus.md#gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb) 

## onBytesReceived<a name="ga95243f25fa04ef29f7f8f0b3a440dbd3"></a>

```
void(* ISessionListener::onBytesReceived) (int sessionId, const void *data, unsigned int dataLen)
```

 **Description:**

Called when data is received. 

This function is used to notify that data is received.

**Parameters:**

<a name="table1262076809084826"></a>
<table><thead align="left"><tr id="row1009597054084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p188721995084826"><a name="p188721995084826"></a><a name="p188721995084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p459862056084826"><a name="p459862056084826"></a><a name="p459862056084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1640466112084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
<tr id="row1747869998084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data received. </td>
</tr>
<tr id="row1716113810084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dataLen</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data received. </td>
</tr>
</tbody>
</table>

## onPublishFail<a name="ga0f84feec4640c176938bbce26b8f25c8"></a>

```
void(* IPublishCallback::onPublishFail) (int publishId, [PublishFailReason](softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620) reason)
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

This function can be used to release resources related to the session. You do not need to call  [CloseSession](softbus.md#ga5b0c0b334f387f9c2753146ee0890780).

**Parameters:**

<a name="table966909473084826"></a>
<table><thead align="left"><tr id="row1757202305084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p58142490084826"><a name="p58142490084826"></a><a name="p58142490084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1722434752084826"><a name="p1722434752084826"></a><a name="p1722434752084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row553055851084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
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

<a name="table375165388084826"></a>
<table><thead align="left"><tr id="row454081133084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p135036345084826"><a name="p135036345084826"></a><a name="p135036345084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1595251020084826"><a name="p1595251020084826"></a><a name="p1595251020084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1115500261084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sessionId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the session ID. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the session connection is accepted; returns a non-zero value otherwise \(you do not need to call  [CloseSession](softbus.md#ga5b0c0b334f387f9c2753146ee0890780)  to close the session\). 



## publishId<a name="ga44a9b46ef719d882d4438a0c34a7f657"></a>

```
int PublishInfo::publishId
```

 **Description:**

[Service](service.md)  publishing ID 

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

