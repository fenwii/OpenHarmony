# wifi\_hotspot.h<a name="ZH-CN_TOPIC_0000001054476495"></a>

## **Overview**<a name="section1061477217191854"></a>

**Related Modules:**

[Wifiservice](Wifiservice.md)

**Description:**

Provides capabilities to enable and disable the hotspot mode, connect to and disconnect from a hotspot, query the hotspot status, and listen for events. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1728586742191854"></a>

## Macros<a name="define-members"></a>

<a name="table756254712191854"></a>
<table><thead align="left"><tr id="row2023946657191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p338636517191854"><a name="p338636517191854"></a><a name="p338636517191854"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1363770512191854"><a name="p1363770512191854"></a><a name="p1363770512191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1462442029191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p285183157191854"><a name="p285183157191854"></a><a name="p285183157191854"></a><a href="Wifiservice.md#gaa8e698699e6bd587bb936c3dbac2265f">HOTSPOT_DEFAULT_CHANNEL</a>&nbsp;&nbsp;&nbsp;6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812262984191854"><a name="p1812262984191854"></a><a name="p1812262984191854"></a>Defines the default channel of the hotspot mode. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table35556791191854"></a>
<table><thead align="left"><tr id="row426197945191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p697676823191854"><a name="p697676823191854"></a><a name="p697676823191854"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1718384030191854"><a name="p1718384030191854"></a><a name="p1718384030191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row248706391191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p54554556191854"><a name="p54554556191854"></a><a name="p54554556191854"></a><a href="Wifiservice.md#ga6b5f219980f4c378384efd1b5560a0b5">EnableHotspot</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108993027191854"><a name="p1108993027191854"></a><a name="p1108993027191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p1829708596191854"><a name="p1829708596191854"></a><a name="p1829708596191854"></a>Enables the hotspot mode. </p>
</td>
</tr>
<tr id="row1861769631191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1160264852191854"><a name="p1160264852191854"></a><a name="p1160264852191854"></a><a href="Wifiservice.md#gaf164ccd00830d8acd9093b28a77b6096">DisableHotspot</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367461105191854"><a name="p1367461105191854"></a><a name="p1367461105191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p88079579191854"><a name="p88079579191854"></a><a name="p88079579191854"></a>Disables the hotspot mode. </p>
</td>
</tr>
<tr id="row1876272897191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2108808557191854"><a name="p2108808557191854"></a><a name="p2108808557191854"></a><a href="Wifiservice.md#gafebbb0442cc9334441ff0edc979753ca">SetHotspotConfig</a> (const <a href="HotspotConfig.md">HotspotConfig</a> *config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1805903484191854"><a name="p1805903484191854"></a><a name="p1805903484191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p45895934191854"><a name="p45895934191854"></a><a name="p45895934191854"></a>Sets a specified hotspot configuration. </p>
</td>
</tr>
<tr id="row177710550191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1525056226191854"><a name="p1525056226191854"></a><a name="p1525056226191854"></a><a href="Wifiservice.md#ga0275a72cc29a7f331175726caa8444cd">GetHotspotConfig</a> (<a href="HotspotConfig.md">HotspotConfig</a> *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308893404191854"><a name="p308893404191854"></a><a name="p308893404191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p1356982499191854"><a name="p1356982499191854"></a><a name="p1356982499191854"></a>Obtains a specified hotspot configuration. </p>
</td>
</tr>
<tr id="row575000889191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096993308191854"><a name="p1096993308191854"></a><a name="p1096993308191854"></a><a href="Wifiservice.md#ga4085f013f3a4df6792bdbf780a938e89">IsHotspotActive</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p575900462191854"><a name="p575900462191854"></a><a name="p575900462191854"></a>int&nbsp;</p>
<p id="p1485144592191854"><a name="p1485144592191854"></a><a name="p1485144592191854"></a>Checks whether the hotspot mode is enabled. </p>
</td>
</tr>
<tr id="row3657209191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346602316191854"><a name="p346602316191854"></a><a name="p346602316191854"></a><a href="Wifiservice.md#ga7babac79dc6a618b5762b6436af2cb28">GetStationList</a> (<a href="StationInfo.md">StationInfo</a> *result, unsigned int *size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p902153046191854"><a name="p902153046191854"></a><a name="p902153046191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p220619769191854"><a name="p220619769191854"></a><a name="p220619769191854"></a>Obtains an array of stations connected to this hotspot. </p>
</td>
</tr>
<tr id="row629420892191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453633746191854"><a name="p453633746191854"></a><a name="p453633746191854"></a><a href="Wifiservice.md#ga8711a25e460e961dc32e1296be060f6d">GetSignalLevel</a> (int rssi, int band)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402617702191854"><a name="p1402617702191854"></a><a name="p1402617702191854"></a>int&nbsp;</p>
<p id="p1318315137191854"><a name="p1318315137191854"></a><a name="p1318315137191854"></a>Obtains the signal level indicated by a specified received signal strength indicator (RSSI) and frequency band. </p>
</td>
</tr>
</tbody>
</table>

