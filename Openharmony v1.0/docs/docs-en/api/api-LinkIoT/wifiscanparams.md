# WifiScanParams<a name="EN-US_TOPIC_0000001054476503"></a>

## **Overview**<a name="section675602872191903"></a>

**Related Modules:**

[Wifiservice](wifiservice.md)

**Description:**

Represents the Wi-Fi station configuration used to connect to a specified Wi-Fi device. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section116051070191903"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table110190731191903"></a>
<table><thead align="left"><tr id="row964003011191903"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p155400450191903"><a name="p155400450191903"></a><a name="p155400450191903"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1316231575191903"><a name="p1316231575191903"></a><a name="p1316231575191903"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2102632087191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p811222075191903"><a name="p811222075191903"></a><a name="p811222075191903"></a><a href="wifiscanparams.md#a5cc37be5e76726347282dc01743918fa">ssid</a> [<a href="wifiservice.md#ga7e01d8c5079081de486637b4482c937a">WIFI_MAX_SSID_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293427828191903"><a name="p293427828191903"></a><a name="p293427828191903"></a>char </p>
</td>
</tr>
<tr id="row1585496189191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p512192033191903"><a name="p512192033191903"></a><a name="p512192033191903"></a><a href="wifiscanparams.md#ac40d20764b11ef5204b986a2d895aa11">ssidLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p579307464191903"><a name="p579307464191903"></a><a name="p579307464191903"></a>char </p>
</td>
</tr>
<tr id="row665333700191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p516363752191903"><a name="p516363752191903"></a><a name="p516363752191903"></a><a href="wifiscanparams.md#a060f9889c6efbc35492a93cadf0cdf9b">bssid</a> [<a href="wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815">WIFI_MAC_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027370715191903"><a name="p1027370715191903"></a><a name="p1027370715191903"></a>char </p>
</td>
</tr>
<tr id="row1275523228191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139807557191903"><a name="p2139807557191903"></a><a name="p2139807557191903"></a><a href="wifiscanparams.md#a085d557f3c3764d74bae62d1331e504b">freqs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973844077191903"><a name="p1973844077191903"></a><a name="p1973844077191903"></a>int </p>
</td>
</tr>
<tr id="row1116434499191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659994741191903"><a name="p659994741191903"></a><a name="p659994741191903"></a><a href="wifiscanparams.md#ab198fc101067d815dc0cf14249fc51d9">band</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1344509006191903"><a name="p1344509006191903"></a><a name="p1344509006191903"></a>int </p>
</td>
</tr>
<tr id="row1244931885191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685340360191903"><a name="p1685340360191903"></a><a name="p1685340360191903"></a><a href="wifiscanparams.md#a7824a90a2ebedca5b375d7ef4bbf0694">scanType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p22686715191903"><a name="p22686715191903"></a><a name="p22686715191903"></a><a href="wifiservice.md#ga007bf5e22727debc02cad860e41a60a3">WifiScanType</a> </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1035711337191903"></a>

## **Field Documentation**<a name="section1963210175191903"></a>

## band<a name="ab198fc101067d815dc0cf14249fc51d9"></a>

```
int WifiScanParams::band
```

 **Description:**

Frequency band. 

## bssid<a name="a060f9889c6efbc35492a93cadf0cdf9b"></a>

```
char WifiScanParams::bssid[[WIFI_MAC_LEN](wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815)]
```

 **Description:**

Basic service set ID \(BSSID\). Its length is defined by  [WIFI\_MAC\_LEN](wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815). 

## freqs<a name="a085d557f3c3764d74bae62d1331e504b"></a>

```
int WifiScanParams::freqs
```

 **Description:**

Frequency. 

## scanType<a name="a7824a90a2ebedca5b375d7ef4bbf0694"></a>

```
[WifiScanType](wifiservice.md#ga007bf5e22727debc02cad860e41a60a3) WifiScanParams::scanType
```

 **Description:**

Wi-Fi scan type, which is defined by  [WifiScanType](wifiservice.md#ga007bf5e22727debc02cad860e41a60a3). 

## ssid<a name="a5cc37be5e76726347282dc01743918fa"></a>

```
char WifiScanParams::ssid[[WIFI_MAX_SSID_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a)]
```

 **Description:**

[Service](service.md)  set ID \(SSID\). Its maximum length is defined by  [WIFI\_MAX\_SSID\_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a). 

## ssidLen<a name="ac40d20764b11ef5204b986a2d895aa11"></a>

```
char WifiScanParams::ssidLen
```

 **Description:**

Length of the SSID. 

