# HdfWifiChipData<a name="ZH-CN_TOPIC_0000001055678094"></a>

## **Overview**<a name="section1811296003093530"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Defines a WLAN chip. 

**Since:**

1.0

## **Summary**<a name="section969672700093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1626125086093530"></a>
<table><thead align="left"><tr id="row942416756093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p934707918093530"><a name="p934707918093530"></a><a name="p934707918093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1271794397093530"><a name="p1271794397093530"></a><a name="p1271794397093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1689771882093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102874664093530"><a name="p2102874664093530"></a><a name="p2102874664093530"></a><a href="WLAN.md#ga4c59fb9385e56ed8017ee48d36bac554">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499111885093530"><a name="p499111885093530"></a><a name="p499111885093530"></a>uint16_t&nbsp;</p>
</td>
</tr>
<tr id="row1906331512093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p949163880093530"><a name="p949163880093530"></a><a name="p949163880093530"></a><a href="WLAN.md#ga02ee61c30fc06116d5dee320eda37bfe">name</a> [<a href="WLAN.md#gaf460a45a5e365279ca6bc5b3e8750542">MAX_WIFI_COMPONENT_NAME_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902376632093530"><a name="p1902376632093530"></a><a name="p1902376632093530"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row1434138736093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1423873108093530"><a name="p1423873108093530"></a><a name="p1423873108093530"></a><a href="WLAN.md#ga920007113f95ee9ce9b0d51ca0cf42bc">ops</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926461961093530"><a name="p926461961093530"></a><a name="p926461961093530"></a>struct <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> *&nbsp;</p>
</td>
</tr>
<tr id="row2076538520093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1224410578093530"><a name="p1224410578093530"></a><a name="p1224410578093530"></a><a href="WLAN.md#gabbafd20c6c6cc8eb20777cdd588b46cd">init</a> )(struct <a href="HdfWifiChipData.md">HdfWifiChipData</a> *chipData, const struct HdfConfigWifiChip *chipConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356969169093530"><a name="p356969169093530"></a><a name="p356969169093530"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1334170103093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2031663405093530"><a name="p2031663405093530"></a><a name="p2031663405093530"></a><a href="WLAN.md#gaf4ad8f670757555c0535b5a5fa5fa8d9">deinit</a> )(struct <a href="HdfWifiChipData.md">HdfWifiChipData</a> *chipData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163581239093530"><a name="p1163581239093530"></a><a name="p1163581239093530"></a>int32_t(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

