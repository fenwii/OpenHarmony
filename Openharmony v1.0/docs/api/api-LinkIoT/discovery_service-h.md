# discovery\_service.h<a name="ZH-CN_TOPIC_0000001055075069"></a>

## **Overview**<a name="section1014348807090253"></a>

**Related Modules:**

[Softbus](Softbus.md)

**Description:**

Declares unified device service publishing interfaces. 

This file provides capabilities related to device service publishing, including publishing services, unpublishing services, and setting device parameters. After multiple nearby devices are discovered and networked, these interfaces can be used to perform service publishing-related operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2070788104090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1311708729090253"></a>
<table><thead align="left"><tr id="row907744138090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1977245706090253"><a name="p1977245706090253"></a><a name="p1977245706090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p674994225090253"><a name="p674994225090253"></a><a name="p674994225090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row773743802090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1868199937090253"><a name="p1868199937090253"></a><a name="p1868199937090253"></a><a href="PublishInfo.md">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p505311872090253"><a name="p505311872090253"></a><a name="p505311872090253"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row2009657402090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2081744149090253"><a name="p2081744149090253"></a><a name="p2081744149090253"></a><a href="CapabilityMap.md">CapabilityMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1062287069090253"><a name="p1062287069090253"></a><a name="p1062287069090253"></a>Defines the mapping between supported capabilities and bitmaps. </p>
</td>
</tr>
<tr id="row1145479363090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607076055090253"><a name="p607076055090253"></a><a name="p607076055090253"></a><a href="DeviceMap.md">DeviceMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p306102614090253"><a name="p306102614090253"></a><a name="p306102614090253"></a>Defines the mappings between the device type enumerations and device type names. </p>
</td>
</tr>
<tr id="row1827597504090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329295987090253"><a name="p329295987090253"></a><a name="p329295987090253"></a><a href="IPublishCallback.md">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1390193299090253"><a name="p1390193299090253"></a><a name="p1390193299090253"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row1380029524090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1783813532090253"><a name="p1783813532090253"></a><a name="p1783813532090253"></a><a href="CommonDeviceInfo.md">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238567183090253"><a name="p1238567183090253"></a><a name="p1238567183090253"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table12207286090253"></a>
<table><thead align="left"><tr id="row1297238380090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p660569662090253"><a name="p660569662090253"></a><a name="p660569662090253"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p986399404090253"><a name="p986399404090253"></a><a name="p986399404090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row143389890090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1158371923090253"><a name="p1158371923090253"></a><a name="p1158371923090253"></a><a href="Softbus.md#gae0bb52450c28ea9be1c5475d0d89830e">PublishInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1000368490090253"><a name="p1000368490090253"></a><a name="p1000368490090253"></a>typedef struct <a href="PublishInfo.md">PublishInfo</a>&nbsp;</p>
<p id="p162031656090253"><a name="p162031656090253"></a><a name="p162031656090253"></a>Defines service provisioning information sent to a discovering device. </p>
</td>
</tr>
<tr id="row168471488090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1456119219090253"><a name="p1456119219090253"></a><a name="p1456119219090253"></a><a href="Softbus.md#ga9334bacb3ded964dc3c3367a6b70bcf4">DeviceType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2146456532090253"><a name="p2146456532090253"></a><a name="p2146456532090253"></a>typedef enum <a href="Softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a>&nbsp;</p>
<p id="p11239047090253"><a name="p11239047090253"></a><a name="p11239047090253"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row2058637896090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1722871345090253"><a name="p1722871345090253"></a><a name="p1722871345090253"></a><a href="Softbus.md#gab622f2f40d12121620d464e43635a09b">IPublishCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764741101090253"><a name="p764741101090253"></a><a name="p764741101090253"></a>typedef struct <a href="IPublishCallback.md">IPublishCallback</a>&nbsp;</p>
<p id="p1539713823090253"><a name="p1539713823090253"></a><a name="p1539713823090253"></a>Defines the callbacks for successful and failed service publishing. </p>
</td>
</tr>
<tr id="row1475899461090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1016434066090253"><a name="p1016434066090253"></a><a name="p1016434066090253"></a><a href="Softbus.md#ga8dc0eb993aea9593f96da339edf042ff">CommonDeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764160030090253"><a name="p764160030090253"></a><a name="p764160030090253"></a>typedef struct <a href="CommonDeviceInfo.md">CommonDeviceInfo</a>&nbsp;</p>
<p id="p1028410221090253"><a name="p1028410221090253"></a><a name="p1028410221090253"></a>Defines the type and content of a device to set. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table33889119090253"></a>
<table><thead align="left"><tr id="row1886292022090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p42210489090253"><a name="p42210489090253"></a><a name="p42210489090253"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1551695649090253"><a name="p1551695649090253"></a><a name="p1551695649090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row573379789090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p522457574090253"><a name="p522457574090253"></a><a name="p522457574090253"></a><a href="Softbus.md#gaf5c7c122990f0ab5bd46b9bc47b5868b">ExchanageMedium</a> { <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868baeef9468d1b98bca652a04bf5063fd9d6">AUTO</a> = 0, <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba83ac6cc3119966e1e5a7908c9e2e3b6a">BLE</a> = 1, <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba8aebc0006e14100ba0e37073b1910195">COAP</a> = 2, <a href="Softbus.md#ggaf5c7c122990f0ab5bd46b9bc47b5868ba65f6b55fdc64778bf10632a795b97761">USB</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p645407247090253"><a name="p645407247090253"></a><a name="p645407247090253"></a>Enumerates media, such as Bluetooth, Wi-Fi, and USB, used for publishing services. </p>
</td>
</tr>
<tr id="row202308569090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236723361090253"><a name="p236723361090253"></a><a name="p236723361090253"></a><a href="Softbus.md#gacf2c77bd7e2c82784078762978123ea3">ExchangeFre</a> { <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a6a226f4143ca3b18999551694cdb72a8">LOW</a> = 0, <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a3bc56824c91d97fcda36dc99687bb236">MID</a> = 1, <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a0c3a1dacf94061154b3ee354359c5893">HIGH</a> = 2, <a href="Softbus.md#ggacf2c77bd7e2c82784078762978123ea3a4c5a6024301ee8c176da7226fda23cdc">SUPER_HIGH</a> = 3 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679419102090253"><a name="p1679419102090253"></a><a name="p1679419102090253"></a>Enumerates frequencies for publishing services. This enumeration is involved only in Bluetooth and is not supported currently. </p>
</td>
</tr>
<tr id="row1675518825090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p551680741090253"><a name="p551680741090253"></a><a name="p551680741090253"></a><a href="Softbus.md#ga7369479474cf45e9ca9c0f756473c74f">DiscoverMode</a> { <a href="Softbus.md#gga7369479474cf45e9ca9c0f756473c74fac6dc5925b6fb96b8e7e094dcb16b6ebf">DISCOVER_MODE_PASSIVE</a> = 0x55, <a href="Softbus.md#gga7369479474cf45e9ca9c0f756473c74fa9223119d2d3b76ce474ba46fcc2b2cdb">DISCOVER_MODE_ACTIVE</a> = 0xAA }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908450638090253"><a name="p908450638090253"></a><a name="p908450638090253"></a>Enumerates the modes in which services are published. The publishing service supports the passive mode. Lite devices support the passive mode only. </p>
</td>
</tr>
<tr id="row1759950538090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001982808090253"><a name="p1001982808090253"></a><a name="p1001982808090253"></a><a href="Softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620">PublishFailReason</a> { <a href="Softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1e11e7c898876b4060ae96986331250d">PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM</a> = 1, <a href="Softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620aae6c44a3f6e7d11bc6373ca48898d9ca">PUBLISH_FAIL_REASON_PARAMETER_INVALID</a> = 2, <a href="Softbus.md#gga6632fcae1db4a3a13370e3fb49e5e620a1cd5dc3834e78f257b99120932eaff8f">PUBLISH_FAIL_REASON_UNKNOWN</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p698021068090253"><a name="p698021068090253"></a><a name="p698021068090253"></a>Enumerates failure reasons for publishing services. </p>
</td>
</tr>
<tr id="row1692775405090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527768056090253"><a name="p1527768056090253"></a><a name="p1527768056090253"></a><a href="Softbus.md#gab839c7f1fd448f52f003ab0693f27bb4">DataBitMap</a> { &nbsp;&nbsp;<a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a773d83ceedb06bba15df8bf3f9c92f4c">HICALL_CAPABILITY_BITMAP</a> = 0, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a2234c533a7dc926001be295d5af77dc3">PROFILE_CAPABILITY_BITMAP</a> = 1, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a13f6092c03683a03ec1793a7fba9adc2">HOMEVISIONPIC_CAPABILITY_BITMAP</a> = 2, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4aa65f50213e151c5c1979639cba00e37f">CASTPLUS_CAPABILITY_BITMAP</a>, &nbsp;&nbsp;<a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4a48fb1fbadf08443a5209176d2c8cf8a3">AA_CAPABILITY_BITMAP</a>, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ade3b8cbbea290f02bdbccd8c200c5ab8">DVKIT_CAPABILITY_BITMAP</a>, <a href="Softbus.md#ggab839c7f1fd448f52f003ab0693f27bb4ae0134ba56bf2fe5ca4d6d0a160d8861b">DDMP_CAPABILITY_BITMAP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1604333221090253"><a name="p1604333221090253"></a><a name="p1604333221090253"></a>Enumerates supported capabilities published by a device. </p>
</td>
</tr>
<tr id="row439418683090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2000678037090253"><a name="p2000678037090253"></a><a name="p2000678037090253"></a><a href="Softbus.md#gab20b49630026f3118d6c05b0a022f230">DeviceTypeEnum</a> { &nbsp;&nbsp;<a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a1da3b620fee1e91433a53fc5559392f9">UNKOWN</a> = 0x00, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230ae1f8e5380dc0849533e4a3b81468ddb1">PHONE</a> = 0x0E, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a58a4470bc0f9a4fcaf059b26e95ab9c2">PAD</a> = 0x11, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a818aafb4e6e34b988f90964cd884b8a2">TV</a> = 0x9C, &nbsp;&nbsp;<a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230aa2c62b62b658ac45e83749e9e9c1cb46">PC</a> = 0x0C, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230ad45d481f1c1a6029ce6a398e52e53bfd">AUDIO</a> = 0x0A, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a5fc54ebcb1dd4bf1e1b93cbc77b57b40">CAR</a> = 0x83, <a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230a51451264203360e0ffacec9b6d8ef7c9">L0</a> = 0xF1, &nbsp;&nbsp;<a href="Softbus.md#ggab20b49630026f3118d6c05b0a022f230ae5bc7ee7d6dda5340a28f91834f10543">L1</a> = 0xF2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798466826090253"><a name="p1798466826090253"></a><a name="p1798466826090253"></a>Enumerates device types. </p>
</td>
</tr>
<tr id="row2126160349090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1402410320090253"><a name="p1402410320090253"></a><a name="p1402410320090253"></a><a href="Softbus.md#ga25be99ffbe88e41f7ce51d2678010254">CommonDeviceKey</a> { <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254a700842536bdaedb960842d6eaad40b10">COMM_DEVICE_KEY_DEVID</a> = 0, <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254af943e70b688809585638337aba3fb816">COMM_DEVICE_KEY_DEVTYPE</a> = 1, <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254a1e0a393d9715b263f5abe01d289fd341">COMM_DEVICE_KEY_DEVNAME</a> = 2, <a href="Softbus.md#gga25be99ffbe88e41f7ce51d2678010254af7be5714543eb5632b641dac82ef4d84">COMM_DEVICE_KEY_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783396070090253"><a name="p783396070090253"></a><a name="p783396070090253"></a>Enumerates device information, such as its ID, type, and name. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1231503105090253"></a>
<table><thead align="left"><tr id="row1969072315090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p59022275090253"><a name="p59022275090253"></a><a name="p59022275090253"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1430344193090253"><a name="p1430344193090253"></a><a name="p1430344193090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1762120235090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p539797665090253"><a name="p539797665090253"></a><a name="p539797665090253"></a><a href="Softbus.md#ga010557e05b3f0b0b1a05157f1724e13a">PublishService</a> (const char *moduleName, const struct <a href="PublishInfo.md">PublishInfo</a> *info, const struct <a href="IPublishCallback.md">IPublishCallback</a> *cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p849549818090253"><a name="p849549818090253"></a><a name="p849549818090253"></a>int&nbsp;</p>
<p id="p654805535090253"><a name="p654805535090253"></a><a name="p654805535090253"></a>Publishes a service to the discovering device in the LAN. </p>
</td>
</tr>
<tr id="row410402513090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906723982090253"><a name="p1906723982090253"></a><a name="p1906723982090253"></a><a href="Softbus.md#gac9463e62e324155634c01facdf642ea7">UnPublishService</a> (const char *moduleName, int publishId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1055214080090253"><a name="p1055214080090253"></a><a name="p1055214080090253"></a>int&nbsp;</p>
<p id="p900719817090253"><a name="p900719817090253"></a><a name="p900719817090253"></a>Unpublishes a service based on the <strong id="b752881491090253"><a name="b752881491090253"></a><a name="b752881491090253"></a>publicId</strong> and <strong id="b1350978185090253"><a name="b1350978185090253"></a><a name="b1350978185090253"></a>moduleName</strong>. </p>
</td>
</tr>
<tr id="row799413974090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858928627090253"><a name="p858928627090253"></a><a name="p858928627090253"></a><a href="Softbus.md#gaca3ae566d98727d111befb4a642bafc4">SetCommonDeviceInfo</a> (const struct <a href="CommonDeviceInfo.md">CommonDeviceInfo</a> *devInfo, unsigned int num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493724513090253"><a name="p493724513090253"></a><a name="p493724513090253"></a>int&nbsp;</p>
<p id="p264921489090253"><a name="p264921489090253"></a><a name="p264921489090253"></a>Sets common device information, such as its ID, type, and name. </p>
</td>
</tr>
</tbody>
</table>

