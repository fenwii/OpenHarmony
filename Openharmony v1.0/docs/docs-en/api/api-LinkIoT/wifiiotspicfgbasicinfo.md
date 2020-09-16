# WifiIotSpiCfgBasicInfo<a name="EN-US_TOPIC_0000001054476505"></a>

## **Overview**<a name="section1852825785191905"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Defines data communication parameters. 

## **Summary**<a name="section1875527183191905"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table555694888191905"></a>
<table><thead align="left"><tr id="row117606363191905"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2133411790191905"><a name="p2133411790191905"></a><a name="p2133411790191905"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1081893289191905"><a name="p1081893289191905"></a><a name="p1081893289191905"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row498786598191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p972785714191905"><a name="p972785714191905"></a><a name="p972785714191905"></a><a href="wifiiotspicfgbasicinfo.md#ad9d835a2bbd3d2aaa1e4291157fa78e0">cpol</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p771379326191905"><a name="p771379326191905"></a><a name="p771379326191905"></a>unsigned int </p>
</td>
</tr>
<tr id="row1241766551191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1955867353191905"><a name="p1955867353191905"></a><a name="p1955867353191905"></a><a href="wifiiotspicfgbasicinfo.md#ae577ecd22389f1e8161608f19089300a">cpha</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1846646689191905"><a name="p1846646689191905"></a><a name="p1846646689191905"></a>unsigned int </p>
</td>
</tr>
<tr id="row403381680191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p652122748191905"><a name="p652122748191905"></a><a name="p652122748191905"></a><a href="wifiiotspicfgbasicinfo.md#a03d2d9ebd4e025c83c533b4845962c84">framMode</a>: 2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261359504191905"><a name="p1261359504191905"></a><a name="p1261359504191905"></a>unsigned int </p>
</td>
</tr>
<tr id="row2005489690191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1341777967191905"><a name="p1341777967191905"></a><a name="p1341777967191905"></a><a href="wifiiotspicfgbasicinfo.md#ac9da29834ed72d35e4b7a8fe1f7cfda9">dataWidth</a>: 4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549091007191905"><a name="p549091007191905"></a><a name="p549091007191905"></a>unsigned int </p>
</td>
</tr>
<tr id="row754329516191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1402130474191905"><a name="p1402130474191905"></a><a name="p1402130474191905"></a><a href="wifiiotspicfgbasicinfo.md#a06230e3384075867e9114575c3f0219d">endian</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1943431731191905"><a name="p1943431731191905"></a><a name="p1943431731191905"></a>unsigned int </p>
</td>
</tr>
<tr id="row79840177191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1669435409191905"><a name="p1669435409191905"></a><a name="p1669435409191905"></a><a href="wifiiotspicfgbasicinfo.md#abfe8fbc5fa2e0714402686af8314018b">pad</a>: 23</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650210543191905"><a name="p1650210543191905"></a><a name="p1650210543191905"></a>unsigned int </p>
</td>
</tr>
<tr id="row219048437191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p185530808191905"><a name="p185530808191905"></a><a name="p185530808191905"></a><a href="wifiiotspicfgbasicinfo.md#ae20c7f5802db8322a3760b33a370b1db">freq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824710688191905"><a name="p1824710688191905"></a><a name="p1824710688191905"></a>unsigned int </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1856654382191905"></a>

## **Field Documentation**<a name="section1230980318191905"></a>

## cpha<a name="ae577ecd22389f1e8161608f19089300a"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::cpha
```

 **Description:**

Communication phase. For details about available values, see  [WifiIotSpiCfgClockCpha](wifiiot.md#ga1eb13cffbbdec9da1d57c766763b94e5). 

## cpol<a name="ad9d835a2bbd3d2aaa1e4291157fa78e0"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::cpol
```

 **Description:**

Communication polarity. For details about available values, see  [WifiIotSpiCfgClockCpol](wifiiot.md#gad6674c8b0989b6a329d5fd5ff0d5d750). 

## dataWidth<a name="ac9da29834ed72d35e4b7a8fe1f7cfda9"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::dataWidth
```

 **Description:**

Communication data width. For details about available values, see  [WifiIotSpiCfgDataWidth](wifiiot.md#ga6f2e44db2698c33b81bd6caa438a55ea). 

## endian<a name="a06230e3384075867e9114575c3f0219d"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::endian
```

 **Description:**

Endian mode. For details about available values, see  [WifiIotSpiCfgEndian](wifiiot.md#ga31924085df23a024413fa6e63e13c41e). 

## framMode<a name="a03d2d9ebd4e025c83c533b4845962c84"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::framMode
```

 **Description:**

Communication protocol. For details about available values, see  [WifiIotSpiCfgFramMode](wifiiot.md#gaef7c192e049db14e2326c0bfba181670). 

## freq<a name="ae20c7f5802db8322a3760b33a370b1db"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::freq
```

 **Description:**

Communication frequency. The value ranges from 2460 Hz to 40 MHz. 

## pad<a name="abfe8fbc5fa2e0714402686af8314018b"></a>

```
unsigned int WifiIotSpiCfgBasicInfo::pad
```

 **Description:**

Padding bit 

