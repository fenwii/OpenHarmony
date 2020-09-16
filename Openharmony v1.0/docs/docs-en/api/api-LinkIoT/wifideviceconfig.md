# WifiDeviceConfig<a name="EN-US_TOPIC_0000001055036456"></a>

## **Overview**<a name="section1138857977191903"></a>

**Related Modules:**

[Wifiservice](wifiservice.md)

**Description:**

Represents the Wi-Fi station configuration used to connect to a specified Wi-Fi device. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1979855845191903"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2084918789191903"></a>
<table><thead align="left"><tr id="row1002206906191903"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p380703197191903"><a name="p380703197191903"></a><a name="p380703197191903"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1598813006191903"><a name="p1598813006191903"></a><a name="p1598813006191903"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row350617302191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p70915236191903"><a name="p70915236191903"></a><a name="p70915236191903"></a><a href="wifideviceconfig.md#a9da672d383a32be93aaefda5973c4d9d">ssid</a> [<a href="wifiservice.md#ga7e01d8c5079081de486637b4482c937a">WIFI_MAX_SSID_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1828550615191903"><a name="p1828550615191903"></a><a name="p1828550615191903"></a>char </p>
</td>
</tr>
<tr id="row1960674038191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898658796191903"><a name="p1898658796191903"></a><a name="p1898658796191903"></a><a href="wifideviceconfig.md#abf19215ed365c6da58e53146cdfd7c72">bssid</a> [<a href="wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815">WIFI_MAC_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p428876637191903"><a name="p428876637191903"></a><a name="p428876637191903"></a>unsigned char </p>
</td>
</tr>
<tr id="row2082652590191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p492952589191903"><a name="p492952589191903"></a><a name="p492952589191903"></a><a href="wifideviceconfig.md#ad452587e97bca974dcebf9be1b276260">preSharedKey</a> [<a href="wifiservice.md#ga6017e2d011b6cffcd3663db81a2b52d8">WIFI_MAX_KEY_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182861002191903"><a name="p1182861002191903"></a><a name="p1182861002191903"></a>char </p>
</td>
</tr>
<tr id="row547775743191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p409339088191903"><a name="p409339088191903"></a><a name="p409339088191903"></a><a href="wifideviceconfig.md#a771eb907ee35c3df1558bb7b1dca70e5">securityType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331417719191903"><a name="p1331417719191903"></a><a name="p1331417719191903"></a>int </p>
</td>
</tr>
<tr id="row1291587731191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p582973978191903"><a name="p582973978191903"></a><a name="p582973978191903"></a><a href="wifideviceconfig.md#a1445931113ffb1d24835cccc04a4aee0">netId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124659733191903"><a name="p2124659733191903"></a><a name="p2124659733191903"></a>int </p>
</td>
</tr>
<tr id="row1978830716191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p438399985191903"><a name="p438399985191903"></a><a name="p438399985191903"></a><a href="wifideviceconfig.md#a08b204eb1261ce4eca133d50cca19add">freq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p689365236191903"><a name="p689365236191903"></a><a name="p689365236191903"></a>unsigned int </p>
</td>
</tr>
<tr id="row264341955191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1679131359191903"><a name="p1679131359191903"></a><a name="p1679131359191903"></a><a href="wifideviceconfig.md#a8ccce2cc3cdd39a48821a0d921bb75ea">wapiPskType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073684517191903"><a name="p2073684517191903"></a><a name="p2073684517191903"></a>int </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section404227860191903"></a>

## **Field Documentation**<a name="section1527979478191903"></a>

## bssid<a name="abf19215ed365c6da58e53146cdfd7c72"></a>

```
unsigned char WifiDeviceConfig::bssid[[WIFI_MAC_LEN](wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815)]
```

 **Description:**

Basic service set ID \(BSSID\). For its length, see  [WIFI\_MAC\_LEN](wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815). 

## freq<a name="a08b204eb1261ce4eca133d50cca19add"></a>

```
unsigned int WifiDeviceConfig::freq
```

 **Description:**

Frequency 

## netId<a name="a1445931113ffb1d24835cccc04a4aee0"></a>

```
int WifiDeviceConfig::netId
```

 **Description:**

Allocated  **networkId** 

## preSharedKey<a name="ad452587e97bca974dcebf9be1b276260"></a>

```
char WifiDeviceConfig::preSharedKey[[WIFI_MAX_KEY_LEN](wifiservice.md#ga6017e2d011b6cffcd3663db81a2b52d8)]
```

 **Description:**

Key. For its length, see  [WIFI\_MAX\_KEY\_LEN](wifiservice.md#ga6017e2d011b6cffcd3663db81a2b52d8). 

## securityType<a name="a771eb907ee35c3df1558bb7b1dca70e5"></a>

```
int WifiDeviceConfig::securityType
```

 **Description:**

Security type. It is defined in  [WifiSecurityType](wifiservice.md#ga97c133f7db7c1234babcde03c4ce1b05). 

## ssid<a name="a9da672d383a32be93aaefda5973c4d9d"></a>

```
char WifiDeviceConfig::ssid[[WIFI_MAX_SSID_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a)]
```

 **Description:**

[Service](service.md)  set ID \(SSID\). For its length, see  [WIFI\_MAX\_SSID\_LEN](wifiservice.md#ga7e01d8c5079081de486637b4482c937a). 

## wapiPskType<a name="a8ccce2cc3cdd39a48821a0d921bb75ea"></a>

```
int WifiDeviceConfig::wapiPskType
```

 **Description:**

PSK type, see  [WifiPskType](wifiservice.md#gaa1a44d23b8478232f14d2adfc82cee77). 

