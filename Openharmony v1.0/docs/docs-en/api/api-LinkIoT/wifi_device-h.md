# wifi\_device.h<a name="EN-US_TOPIC_0000001055675018"></a>

## **Overview**<a name="section290913651191853"></a>

**Related Modules:**

[Wifiservice](wifiservice.md)

**Description:**

Provides capabilities to enable and disable the station mode, connect to and disconnect from a station, query the station status, and listen for events. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1216900574191853"></a>

## Functions<a name="func-members"></a>

<a name="table2062700312191853"></a>
<table><thead align="left"><tr id="row581507208191853"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p673192764191853"><a name="p673192764191853"></a><a name="p673192764191853"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p889541737191853"><a name="p889541737191853"></a><a name="p889541737191853"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1324749149191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856265457191853"><a name="p1856265457191853"></a><a name="p1856265457191853"></a><a href="wifiservice.md#ga81afd7d5f0437260e93536b50437d99b">EnableWifi</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p7499655191853"><a name="p7499655191853"></a><a name="p7499655191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p418832470191853"><a name="p418832470191853"></a><a name="p418832470191853"></a>Enables the station mode. </p>
</td>
</tr>
<tr id="row2071055609191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p38809131191853"><a name="p38809131191853"></a><a name="p38809131191853"></a><a href="wifiservice.md#ga96b28d8f77966a4cd042a46c598b3a9a">DisableWifi</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1905255347191853"><a name="p1905255347191853"></a><a name="p1905255347191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p1300315416191853"><a name="p1300315416191853"></a><a name="p1300315416191853"></a>Disables the station mode. </p>
</td>
</tr>
<tr id="row2049486627191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p324047387191853"><a name="p324047387191853"></a><a name="p324047387191853"></a><a href="wifiservice.md#ga57ee7c4c4ee6092098cb35965f507fb9">IsWifiActive</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298660909191853"><a name="p298660909191853"></a><a name="p298660909191853"></a>int </p>
<p id="p985109107191853"><a name="p985109107191853"></a><a name="p985109107191853"></a>Checks whether the station mode is enabled. </p>
</td>
</tr>
<tr id="row142858618191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034923022191853"><a name="p1034923022191853"></a><a name="p1034923022191853"></a><a href="wifiservice.md#ga72d138ede38fbd6425f1fe7fbc35c262">Scan</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087987099191853"><a name="p2087987099191853"></a><a name="p2087987099191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p1923101878191853"><a name="p1923101878191853"></a><a name="p1923101878191853"></a>Starts a Wi-Fi scan. </p>
</td>
</tr>
<tr id="row621931012191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1432377812191853"><a name="p1432377812191853"></a><a name="p1432377812191853"></a><a href="wifiservice.md#gadbbc62c6d2a16d5f1547097992aa9369">GetScanInfoList</a> (<a href="wifiscaninfo.md">WifiScanInfo</a> *result, unsigned int *size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1683096515191853"><a name="p1683096515191853"></a><a name="p1683096515191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p847993520191853"><a name="p847993520191853"></a><a name="p847993520191853"></a>Obtains an array of hotspots detected in a Wi-Fi scan. </p>
</td>
</tr>
<tr id="row214096119191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984886430191853"><a name="p984886430191853"></a><a name="p984886430191853"></a><a href="wifiservice.md#gaa0a50013ff978d6f82c655403946d8c9">AddDeviceConfig</a> (const <a href="wifideviceconfig.md">WifiDeviceConfig</a> *config, int *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1651342390191853"><a name="p1651342390191853"></a><a name="p1651342390191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p1502713762191853"><a name="p1502713762191853"></a><a name="p1502713762191853"></a>Adds a specified hotspot configuration for connecting to a hotspot. </p>
</td>
</tr>
<tr id="row648270102191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p89298853191853"><a name="p89298853191853"></a><a name="p89298853191853"></a><a href="wifiservice.md#ga2202a6de3fdd8f463d827fc18f46e75b">GetDeviceConfigs</a> (<a href="wifideviceconfig.md">WifiDeviceConfig</a> *result, unsigned int *size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803196705191853"><a name="p1803196705191853"></a><a name="p1803196705191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p742188183191853"><a name="p742188183191853"></a><a name="p742188183191853"></a>Obtains all hotspot configurations. </p>
</td>
</tr>
<tr id="row1455103167191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p141530185191853"><a name="p141530185191853"></a><a name="p141530185191853"></a><a href="wifiservice.md#ga13d79f9dc92bf445b7ef2b98ab050c3a">RemoveDevice</a> (int networkId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2063805126191853"><a name="p2063805126191853"></a><a name="p2063805126191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p460306230191853"><a name="p460306230191853"></a><a name="p460306230191853"></a>Removes a hotspot configuration matching a specified <strong id="b1881027015191853"><a name="b1881027015191853"></a><a name="b1881027015191853"></a>networkId</strong>. </p>
</td>
</tr>
<tr id="row121490422191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099696918191853"><a name="p2099696918191853"></a><a name="p2099696918191853"></a><a href="wifiservice.md#ga775ec0cfc1d5b4bf620bbd7245492344">ConnectTo</a> (int networkId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p536721232191853"><a name="p536721232191853"></a><a name="p536721232191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p127874559191853"><a name="p127874559191853"></a><a name="p127874559191853"></a>Connects to a hotspot matching a specified <strong id="b990962035191853"><a name="b990962035191853"></a><a name="b990962035191853"></a>networkId</strong>. </p>
</td>
</tr>
<tr id="row325018268191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p305212883191853"><a name="p305212883191853"></a><a name="p305212883191853"></a><a href="wifiservice.md#gafbed9a87b5fef2c837a16c6de469652e">Disconnect</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1276338179191853"><a name="p1276338179191853"></a><a name="p1276338179191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p660136343191853"><a name="p660136343191853"></a><a name="p660136343191853"></a>Disconnects this Wi-Fi connection. </p>
</td>
</tr>
<tr id="row709267078191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1583175374191853"><a name="p1583175374191853"></a><a name="p1583175374191853"></a><a href="wifiservice.md#gaa8f07a31b01761da44f0fe90d461c168">GetLinkedInfo</a> (<a href="wifilinkedinfo.md">WifiLinkedInfo</a> *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p643156249191853"><a name="p643156249191853"></a><a name="p643156249191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p1591973955191853"><a name="p1591973955191853"></a><a name="p1591973955191853"></a>Obtains information about the connected hotspot. </p>
</td>
</tr>
<tr id="row1543693749191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088893449191853"><a name="p2088893449191853"></a><a name="p2088893449191853"></a><a href="wifiservice.md#ga0e4d452915d1588664b91837b821eada">RegisterWifiEvent</a> (<a href="wifievent.md">WifiEvent</a> *event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041454910191853"><a name="p1041454910191853"></a><a name="p1041454910191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p731885485191853"><a name="p731885485191853"></a><a name="p731885485191853"></a>Registers a callback for a specified Wi-Fi event. </p>
</td>
</tr>
<tr id="row1431850078191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p23193008191853"><a name="p23193008191853"></a><a name="p23193008191853"></a><a href="wifiservice.md#gaee648c923f6594e222d0c592b929b3f1">UnRegisterWifiEvent</a> (const <a href="wifievent.md">WifiEvent</a> *event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1254345849191853"><a name="p1254345849191853"></a><a name="p1254345849191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p2124976191191853"><a name="p2124976191191853"></a><a name="p2124976191191853"></a>Unregisters a callback previously registered for a specified Wi-Fi event. </p>
</td>
</tr>
<tr id="row68338882191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1973334294191853"><a name="p1973334294191853"></a><a name="p1973334294191853"></a><a href="wifiservice.md#ga951232a54faaa791a82b5e2456c44dcd">GetDeviceMacAddress</a> (unsigned char *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p5389647191853"><a name="p5389647191853"></a><a name="p5389647191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p1232103715191853"><a name="p1232103715191853"></a><a name="p1232103715191853"></a>Obtains the MAC address of this device. </p>
</td>
</tr>
<tr id="row1972846923191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726709410191853"><a name="p726709410191853"></a><a name="p726709410191853"></a><a href="wifiservice.md#gaafff61f96ad29922b524dc9514cfbfd0">AdvanceScan</a> (<a href="wifiscanparams.md">WifiScanParams</a> *params)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727949786191853"><a name="p727949786191853"></a><a name="p727949786191853"></a><a href="wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a> </p>
<p id="p61648187191853"><a name="p61648187191853"></a><a name="p61648187191853"></a>Starts a Wi-Fi scan based on a specified parameter. </p>
</td>
</tr>
</tbody>
</table>

