# WifiModuleIface<a name="EN-US_TOPIC_0000001054918197"></a>

## **Overview**<a name="section1969554721093537"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Defines WLAN module APIs. 

The APIs can be used to obtain, initialize, update, and perform other operations on a WLAN module.

**Since:**

1.0

## **Summary**<a name="section1028366441093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table504346895093537"></a>
<table><thead align="left"><tr id="row137536927093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p368915545093537"><a name="p368915545093537"></a><a name="p368915545093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p586328264093537"><a name="p586328264093537"></a><a name="p586328264093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1501288385093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p939958949093537"><a name="p939958949093537"></a><a name="p939958949093537"></a><a href="wlan.md#gad7c080e7ac22daf18529184da55e910c">getModule</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088827981093537"><a name="p1088827981093537"></a><a name="p1088827981093537"></a>struct <a href="wifimodule.md">WifiModule</a> *(* </p>
</td>
</tr>
<tr id="row638951967093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1697179578093537"><a name="p1697179578093537"></a><a name="p1697179578093537"></a><a href="wlan.md#ga5166022e5100e57fe0b307a4254e3dc1">updateModule</a> )(struct <a href="wifimodule.md">WifiModule</a> *module)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p668537916093537"><a name="p668537916093537"></a><a name="p668537916093537"></a>int32_t(* </p>
</td>
</tr>
<tr id="row231887122093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953464139093537"><a name="p953464139093537"></a><a name="p953464139093537"></a><a href="wlan.md#gadf3d907844092764d8c8d3ce150e1712">init</a> )(struct <a href="wifimodule.md">WifiModule</a> *module)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699470693093537"><a name="p699470693093537"></a><a name="p699470693093537"></a>int32_t(* </p>
</td>
</tr>
<tr id="row1935224814093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1919576405093537"><a name="p1919576405093537"></a><a name="p1919576405093537"></a><a href="wlan.md#ga378c89a04bb867068d3c86c5680ca9c0">deInit</a> )(struct <a href="wifimodule.md">WifiModule</a> *module)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p704557417093537"><a name="p704557417093537"></a><a name="p704557417093537"></a>int32_t(* </p>
</td>
</tr>
<tr id="row1745514708093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1111611606093537"><a name="p1111611606093537"></a><a name="p1111611606093537"></a><a href="wlan.md#gadfa86fac18c68b890d3b33a269931efc">addFeature</a> )(struct <a href="wifimodule.md">WifiModule</a> *module, uint16_t featureType, struct <a href="wififeature.md">WifiFeature</a> *featureData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078284828093537"><a name="p1078284828093537"></a><a name="p1078284828093537"></a>int32_t(* </p>
</td>
</tr>
<tr id="row151829896093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p182905719093537"><a name="p182905719093537"></a><a name="p182905719093537"></a><a href="wlan.md#ga764ebf11b82c57d5185df50fab72a1d8">delFeature</a> )(struct <a href="wifimodule.md">WifiModule</a> *module, uint16_t featureType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851828361093537"><a name="p1851828361093537"></a><a name="p1851828361093537"></a>int32_t(* </p>
</td>
</tr>
</tbody>
</table>

