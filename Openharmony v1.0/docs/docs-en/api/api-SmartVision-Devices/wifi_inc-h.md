# wifi\_inc.h<a name="EN-US_TOPIC_0000001054479551"></a>

## **Overview**<a name="section311110060093528"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Describes the data structure of WLAN features and bus. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1130205758093528"></a>

## Macros<a name="define-members"></a>

<a name="table1293054911093528"></a>
<table><thead align="left"><tr id="row613467771093528"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p311574772093528"><a name="p311574772093528"></a><a name="p311574772093528"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p385120038093528"><a name="p385120038093528"></a><a name="p385120038093528"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row959598406093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p313677076093528"><a name="p313677076093528"></a><a name="p313677076093528"></a><a href="wlan.md#gaf460a45a5e365279ca6bc5b3e8750542">MAX_WIFI_COMPONENT_NAME_LEN</a>   10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1936851092093528"><a name="p1936851092093528"></a><a name="p1936851092093528"></a>Indicates the length of the name of a WLAN module or feature. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table826223971093528"></a>
<table><thead align="left"><tr id="row1046069109093528"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p149511304093528"><a name="p149511304093528"></a><a name="p149511304093528"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p474764435093528"><a name="p474764435093528"></a><a name="p474764435093528"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row545700462093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442699867093528"><a name="p442699867093528"></a><a name="p442699867093528"></a><a href="wlan.md#gaec03ba36d71cc2d5f3209bc24aa6ee10">WifiMainFeatureType</a> {   <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a038fb1847d290b75b15949b6471b46ad">HDF_WIFI_FEATURE_BASE</a>, <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10aaec6c1686d47187e64fd108e0e797133">HDF_WIFI_FEATURE_AP</a>, <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a0e814bd1cfc59a253cc575d3548a9d4e">HDF_WIFI_FEATURE_STA</a>, <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a8e87c1727fa86bf92ee05cad85e7f872">HDF_WIFI_FEATURE_P2P</a>,   <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10ae30b51638bc2c2fb739b3ddec6c5b92b">HDF_WIFI_FEATURE_NAN</a>, <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10ac12422e335003fbd392bff47c53c0352">HDF_WIFI_FEATURE_RTT</a>, <a href="wlan.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a28ff5971d579c1754e03a5f79a0c9e6f">HDF_WIFI_FEATURE_NUM</a> = 10 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1617315834093528"><a name="p1617315834093528"></a><a name="p1617315834093528"></a>Enumerates feature types of a WLAN module. </p>
</td>
</tr>
<tr id="row1072707714093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944332345093528"><a name="p1944332345093528"></a><a name="p1944332345093528"></a><a href="wlan.md#ga1c5537e64f05b5e91b951ddeb66d4261">WifiBusType</a> { <a href="wlan.md#gga1c5537e64f05b5e91b951ddeb66d4261a0eba50f5eecb33326083a82adbaa0848">BUS_SDIO</a>, <a href="wlan.md#gga1c5537e64f05b5e91b951ddeb66d4261a2f4f9ff60278d511660c21e211133666">BUS_USB</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p784671194093528"><a name="p784671194093528"></a><a name="p784671194093528"></a>Enumerates bus types of a WLAN module. </p>
</td>
</tr>
</tbody>
</table>

