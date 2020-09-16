# wifiiot\_i2s.h<a name="ZH-CN_TOPIC_0000001054876472"></a>

## **Overview**<a name="section1525112284191856"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the I2S interface functions. 

These functions are used for I2S initialization and data transmission. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1215234947191856"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1949356943191856"></a>
<table><thead align="left"><tr id="row1656280646191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1719549429191856"><a name="p1719549429191856"></a><a name="p1719549429191856"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1240897249191856"><a name="p1240897249191856"></a><a name="p1240897249191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row224251853191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p714490329191856"><a name="p714490329191856"></a><a name="p714490329191856"></a><a href="WifiIotI2sAttribute.md">WifiIotI2sAttribute</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1276405889191856"><a name="p1276405889191856"></a><a name="p1276405889191856"></a>Defines I2S attributes. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1193541769191856"></a>
<table><thead align="left"><tr id="row959976259191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p786122757191856"><a name="p786122757191856"></a><a name="p786122757191856"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1831889028191856"><a name="p1831889028191856"></a><a name="p1831889028191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1026027457191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p913687871191856"><a name="p913687871191856"></a><a name="p913687871191856"></a><a href="Wifiiot.md#ga5e124d70b18cf4cff40bcce78445f689">WifiIotI2sSampleRate</a> { <a href="Wifiiot.md#gga5e124d70b18cf4cff40bcce78445f689ace40be85474a4c93a09f249c217a6e41">WIFI_IOT_I2S_SAMPLE_RATE_8K</a> = 8, <a href="Wifiiot.md#gga5e124d70b18cf4cff40bcce78445f689a70144626b7f06acc91ca0439d44ad1b7">WIFI_IOT_I2S_SAMPLE_RATE_16K</a> = 16, <a href="Wifiiot.md#gga5e124d70b18cf4cff40bcce78445f689a4ccb67a70dc96f4faf074ab676728258">WIFI_IOT_I2S_SAMPLE_RATE_32K</a> = 32, <a href="Wifiiot.md#gga5e124d70b18cf4cff40bcce78445f689aa8987a10f3c5206bae1f875d45cc854c">WIFI_IOT_I2S_SAMPLE_RATE_48K</a> = 48 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954734062191856"><a name="p954734062191856"></a><a name="p954734062191856"></a>Enumerates I2S sampling rates. </p>
</td>
</tr>
<tr id="row201323961191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1845882942191856"><a name="p1845882942191856"></a><a name="p1845882942191856"></a><a href="Wifiiot.md#gac024b870d63e802d8119e88a82953807">WifiIotI2sResolution</a> { <a href="Wifiiot.md#ggac024b870d63e802d8119e88a82953807af441b8fd738e63fc6237077d018b0eda">WIFI_IOT_I2S_RESOLUTION_16BIT</a> = 16, <a href="Wifiiot.md#ggac024b870d63e802d8119e88a82953807a0a73e0bc3019668a6d75a1200a899db9">WIFI_IOT_I2S_RESOLUTION_24BIT</a> = 24 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878403747191856"><a name="p878403747191856"></a><a name="p878403747191856"></a>Enumerates I2S resolution. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1822849435191856"></a>
<table><thead align="left"><tr id="row630166751191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1671136285191856"><a name="p1671136285191856"></a><a name="p1671136285191856"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p881903394191856"><a name="p881903394191856"></a><a name="p881903394191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1355385446191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1239145999191856"><a name="p1239145999191856"></a><a name="p1239145999191856"></a><a href="Wifiiot.md#gaab1affd53de2567a6eb3803649d1c706">I2sInit</a> (const <a href="WifiIotI2sAttribute.md">WifiIotI2sAttribute</a> *i2sAttribute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p986504598191856"><a name="p986504598191856"></a><a name="p986504598191856"></a>unsigned int&nbsp;</p>
<p id="p1257684881191856"><a name="p1257684881191856"></a><a name="p1257684881191856"></a>Initializes the I2S device. </p>
</td>
</tr>
<tr id="row1079767227191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p405790398191856"><a name="p405790398191856"></a><a name="p405790398191856"></a><a href="Wifiiot.md#ga2f47b7e0c350d305cb0b495bda78450c">I2sDeinit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893034418191856"><a name="p893034418191856"></a><a name="p893034418191856"></a>unsigned int&nbsp;</p>
<p id="p797132977191856"><a name="p797132977191856"></a><a name="p797132977191856"></a>Deinitializes the I2S device. </p>
</td>
</tr>
<tr id="row4332468191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214981648191856"><a name="p214981648191856"></a><a name="p214981648191856"></a><a href="Wifiiot.md#gad30ea8ed658514b8864ab8ddba4fd4f0">I2sWrite</a> (unsigned char *wrData, unsigned int wrLen, unsigned int timeOutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1761548226191856"><a name="p1761548226191856"></a><a name="p1761548226191856"></a>unsigned int&nbsp;</p>
<p id="p450719441191856"><a name="p450719441191856"></a><a name="p450719441191856"></a>Writes data to the I2S device. </p>
</td>
</tr>
<tr id="row1993668062191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139665860191856"><a name="p2139665860191856"></a><a name="p2139665860191856"></a><a href="Wifiiot.md#ga8d2e8cc248252007325cace65bedb742">I2sRead</a> (unsigned char *rdData, unsigned int rdLen, unsigned int timeOutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p863021962191856"><a name="p863021962191856"></a><a name="p863021962191856"></a>unsigned int&nbsp;</p>
<p id="p1062170916191856"><a name="p1062170916191856"></a><a name="p1062170916191856"></a>Reads data from the I2S device. </p>
</td>
</tr>
</tbody>
</table>

