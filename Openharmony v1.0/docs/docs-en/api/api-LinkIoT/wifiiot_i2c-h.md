# wifiiot\_i2c.h<a name="EN-US_TOPIC_0000001055036450"></a>

## **Overview**<a name="section2018083028191855"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the I2C interface functions. 

These functions are used for I2C initialization and data transmission. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1626576018191855"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1781639232191855"></a>
<table><thead align="left"><tr id="row1255017532191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1619160708191855"><a name="p1619160708191855"></a><a name="p1619160708191855"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2141436209191855"><a name="p2141436209191855"></a><a name="p2141436209191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row481422701191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1121131093191855"><a name="p1121131093191855"></a><a name="p1121131093191855"></a><a href="wifiioti2cdata.md">WifiIotI2cData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p266690388191855"><a name="p266690388191855"></a><a name="p266690388191855"></a>Defines I2C data transmission attributes. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1529666355191855"></a>
<table><thead align="left"><tr id="row1517732322191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1273089795191855"><a name="p1273089795191855"></a><a name="p1273089795191855"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p459627612191855"><a name="p459627612191855"></a><a name="p459627612191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row522309174191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p951579701191855"><a name="p951579701191855"></a><a name="p951579701191855"></a><a href="wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> { <a href="wifiiot.md#ggaeeb58e02e3783d02e1ed4bad313cc0b8a626c3ef4caf51e1f1f7d8b4413e399bb">WIFI_IOT_I2C_IDX_0</a>, <a href="wifiiot.md#ggaeeb58e02e3783d02e1ed4bad313cc0b8ad35ceb88fb8b4b6b9cb123d4d32b9316">WIFI_IOT_I2C_IDX_1</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p543039868191855"><a name="p543039868191855"></a><a name="p543039868191855"></a>Enumerates I2C hardware indexes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table134771814191855"></a>
<table><thead align="left"><tr id="row312729765191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p761202498191855"><a name="p761202498191855"></a><a name="p761202498191855"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1659418160191855"><a name="p1659418160191855"></a><a name="p1659418160191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1628360607191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924333382191855"><a name="p924333382191855"></a><a name="p924333382191855"></a><a href="wifiiot.md#ga01f5b9b16ad378ad1ad5d3ee37d0c4c0">I2cInit</a> (<a href="wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id, unsigned int baudrate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159826856191855"><a name="p159826856191855"></a><a name="p159826856191855"></a>unsigned int </p>
<p id="p1379583344191855"><a name="p1379583344191855"></a><a name="p1379583344191855"></a>Initializes an I2C device with a specified baud rate. </p>
</td>
</tr>
<tr id="row983157453191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1677323409191855"><a name="p1677323409191855"></a><a name="p1677323409191855"></a><a href="wifiiot.md#gaaa7f69e289e203f40bff4289bc8e332f">I2cDeinit</a> (<a href="wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588582892191855"><a name="p1588582892191855"></a><a name="p1588582892191855"></a>unsigned int </p>
<p id="p1065433181191855"><a name="p1065433181191855"></a><a name="p1065433181191855"></a>Deinitializes an I2C device. </p>
</td>
</tr>
<tr id="row936410111191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p126228803191855"><a name="p126228803191855"></a><a name="p126228803191855"></a><a href="wifiiot.md#ga0c72d160332184ddddc264411e00fcc9">I2cWrite</a> (<a href="wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id, unsigned short deviceAddr, const <a href="wifiioti2cdata.md">WifiIotI2cData</a> *i2cData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p150707890191855"><a name="p150707890191855"></a><a name="p150707890191855"></a>unsigned int </p>
<p id="p1287234112191855"><a name="p1287234112191855"></a><a name="p1287234112191855"></a>Writes data to an I2C device. </p>
</td>
</tr>
<tr id="row1911357155191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245641637191855"><a name="p1245641637191855"></a><a name="p1245641637191855"></a><a href="wifiiot.md#gac058f6ee969c5873280c11220d04f026">I2cRead</a> (<a href="wifiiot.md#gaeeb58e02e3783d02e1ed4bad313cc0b8">WifiIotI2cIdx</a> id, unsigned short deviceAddr, const <a href="wifiioti2cdata.md">WifiIotI2cData</a> *i2cData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p296645547191855"><a name="p296645547191855"></a><a name="p296645547191855"></a>unsigned int </p>
<p id="p1536122064191855"><a name="p1536122064191855"></a><a name="p1536122064191855"></a>Reads data from an I2C device. </p>
</td>
</tr>
</tbody>
</table>

