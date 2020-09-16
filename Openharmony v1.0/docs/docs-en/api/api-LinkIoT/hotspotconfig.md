# HotspotConfig<a name="EN-US_TOPIC_0000001054595101"></a>

## **Overview**<a name="section1663277023191859"></a>

**Related Modules:**

[Wifiservice](wifiservice.md)

**Description:**

Represents the hotspot configuration. 

A hotspot configuration must contain the SSID \(or BSSID\), security type, and key \(if the security type is open\). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section600944657191859"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1271010545191859"></a>
<table><thead align="left"><tr id="row595248689191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1511519306191859"><a name="p1511519306191859"></a><a name="p1511519306191859"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p261841042191859"><a name="p261841042191859"></a><a name="p261841042191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1872769404191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p177570576191859"><a name="p177570576191859"></a><a name="p177570576191859"></a><a href="hotspotconfig.md#a8ecc1cc58ea265d86d17101872f831ab">ssid</a> [<a href="wifiservice.md#ga7e01d8c5079081de486637b4482c937a">WIFI_MAX_SSID_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2020436859191859"><a name="p2020436859191859"></a><a name="p2020436859191859"></a>char </p>
</td>
</tr>
<tr id="row1818297573191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841136542191859"><a name="p1841136542191859"></a><a name="p1841136542191859"></a><a href="hotspotconfig.md#a4e89326b43042b3c2cb8c75348f6e3cc">securityType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p280427230191859"><a name="p280427230191859"></a><a name="p280427230191859"></a>int </p>
</td>
</tr>
<tr id="row1736352202191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1625275169191859"><a name="p1625275169191859"></a><a name="p1625275169191859"></a><a href="hotspotconfig.md#ae14b1135cd30c75e0cd34a543c993c27">band</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p134904083191859"><a name="p134904083191859"></a><a name="p134904083191859"></a>int </p>
</td>
</tr>
<tr id="row249655207191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1308846415191859"><a name="p1308846415191859"></a><a name="p1308846415191859"></a><a href="hotspotconfig.md#ac9924aa9149b85d05f5a842b05f75845">channelNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650171445191859"><a name="p650171445191859"></a><a name="p650171445191859"></a>int </p>
</td>
</tr>
<tr id="row1845241973191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516661205191859"><a name="p1516661205191859"></a><a name="p1516661205191859"></a><a href="hotspotconfig.md#ace5ad4c26c9ca07adffc16309c4694ae">preSharedKey</a> [<a href="wifiservice.md#ga6017e2d011b6cffcd3663db81a2b52d8">WIFI_MAX_KEY_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628209720191859"><a name="p1628209720191859"></a><a name="p1628209720191859"></a>char </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section939904800191859"></a>

## **Field Documentation**<a name="section1384466232191859"></a>

## band<a name="ae14b1135cd30c75e0cd34a543c993c27"></a>

```
int HotspotConfig::band
```

 **Description:**

Frequency band 

## channelNum<a name="ac9924aa9149b85d05f5a842b05f75845"></a>

```
int HotspotConfig::channelNum
```

 **Description:**

Channel number 

## preSharedKey<a name="ace5ad4c26c9ca07adffc16309c4694ae"></a>

```
char HotspotConfig::preSharedKey[[WIFI_MAX_KEY_LEN](wifiservice.md#ga6017e2d011b6cffcd3663db81a2b52d8)]
```

 **Description:**

Key. For its length, see  [WIFI\_MAX\_SSID\_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a). 

## securityType<a name="a4e89326b43042b3c2cb8c75348f6e3cc"></a>

```
int HotspotConfig::securityType
```

 **Description:**

Security type 

## ssid<a name="a8ecc1cc58ea265d86d17101872f831ab"></a>

```
char HotspotConfig::ssid[[WIFI_MAX_SSID_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a)]
```

 **Description:**

[Service](service.md)  set ID \(SSID\). For its length, see  [WIFI\_MAX\_SSID\_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a). 

