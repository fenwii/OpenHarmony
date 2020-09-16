# WifiScanInfo<a name="ZH-CN_TOPIC_0000001055355048"></a>

## **Overview**<a name="section874275482191903"></a>

**Related Modules:**

[Wifiservice](Wifiservice.md)

**Description:**

Represents the Wi-Fi scan result information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section157177152191903"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2026071518191903"></a>
<table><thead align="left"><tr id="row1976451109191903"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p589499066191903"><a name="p589499066191903"></a><a name="p589499066191903"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p542347270191903"><a name="p542347270191903"></a><a name="p542347270191903"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1509439210191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p262199285191903"><a name="p262199285191903"></a><a name="p262199285191903"></a><a href="WifiScanInfo.md#a3db396b51c99f58668b6b24d009516f5">ssid</a> [<a href="Wifiservice.md#ga7e01d8c5079081de486637b4482c937a">WIFI_MAX_SSID_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2123995045191903"><a name="p2123995045191903"></a><a name="p2123995045191903"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row1853849290191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p493971831191903"><a name="p493971831191903"></a><a name="p493971831191903"></a><a href="WifiScanInfo.md#acc73005402f532bce0c3cdc061a88c1d">bssid</a> [<a href="Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815">WIFI_MAC_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730137706191903"><a name="p1730137706191903"></a><a name="p1730137706191903"></a>unsigned char&nbsp;</p>
</td>
</tr>
<tr id="row1237794479191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1907448765191903"><a name="p1907448765191903"></a><a name="p1907448765191903"></a><a href="WifiScanInfo.md#a6465473afd5650694f599fd444f0cd3b">securityType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540195500191903"><a name="p1540195500191903"></a><a name="p1540195500191903"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row953574181191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2103197961191903"><a name="p2103197961191903"></a><a name="p2103197961191903"></a><a href="WifiScanInfo.md#a3c0579dd9ba9d2a0e20bac0a71ee0778">rssi</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1816521105191903"><a name="p1816521105191903"></a><a name="p1816521105191903"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row1126527978191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112261259191903"><a name="p112261259191903"></a><a name="p112261259191903"></a><a href="WifiScanInfo.md#a9045496401103c44d8d7826b019b3daa">band</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p248787847191903"><a name="p248787847191903"></a><a name="p248787847191903"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row1916948159191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1572223183191903"><a name="p1572223183191903"></a><a name="p1572223183191903"></a><a href="WifiScanInfo.md#ac17f7365ad3e9c181e1e3bddbc778a2c">frequency</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193397619191903"><a name="p1193397619191903"></a><a name="p1193397619191903"></a>int&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section462457712191903"></a>

## **Field Documentation**<a name="section105585086191903"></a>

## band<a name="a9045496401103c44d8d7826b019b3daa"></a>

```
int WifiScanInfo::band
```

 **Description:**

Frequency band 

## bssid<a name="acc73005402f532bce0c3cdc061a88c1d"></a>

```
unsigned char WifiScanInfo::bssid[[WIFI_MAC_LEN](Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815)]
```

 **Description:**

Basic service set ID \(BSSID\). For its length, see  [WIFI\_MAC\_LEN](Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815). 

## frequency<a name="ac17f7365ad3e9c181e1e3bddbc778a2c"></a>

```
int WifiScanInfo::frequency
```

 **Description:**

Frequency in MHz 

## rssi<a name="a3c0579dd9ba9d2a0e20bac0a71ee0778"></a>

```
int WifiScanInfo::rssi
```

 **Description:**

Received signal strength indicator \(RSSI\) 

## securityType<a name="a6465473afd5650694f599fd444f0cd3b"></a>

```
int WifiScanInfo::securityType
```

 **Description:**

Security type. For details, see  [WifiSecurityType](Wifiservice.md#ga97c133f7db7c1234babcde03c4ce1b05). 

## ssid<a name="a3db396b51c99f58668b6b24d009516f5"></a>

```
char WifiScanInfo::ssid[[WIFI_MAX_SSID_LEN](Wifiservice.md#ga7e01d8c5079081de486637b4482c937a)]
```

 **Description:**

[Service](Service.md)  set ID \(SSID\). For its length, see  [WIFI\_MAX\_SSID\_LEN](Wifiservice.md#ga7e01d8c5079081de486637b4482c937a). 

