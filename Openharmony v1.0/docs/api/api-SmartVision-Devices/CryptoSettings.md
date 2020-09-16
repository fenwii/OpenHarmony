# CryptoSettings<a name="ZH-CN_TOPIC_0000001054718121"></a>

## **Overview**<a name="section1509920861093529"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Describes cryptography settings. 

**Since:**

1.0

## **Summary**<a name="section84525700093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table769974887093529"></a>
<table><thead align="left"><tr id="row586347034093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1547159478093529"><a name="p1547159478093529"></a><a name="p1547159478093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p330083516093529"><a name="p330083516093529"></a><a name="p330083516093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2117812852093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1603241672093529"><a name="p1603241672093529"></a><a name="p1603241672093529"></a><a href="WLAN.md#ga2b21ef556b428238d4dc5009b82087ff">wpaVersions</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p840696152093529"><a name="p840696152093529"></a><a name="p840696152093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1889360482093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007065093529"><a name="p2007065093529"></a><a name="p2007065093529"></a><a href="WLAN.md#ga9be34adb7e26191321b38c37b341e20d">cipherGroup</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1769355431093529"><a name="p1769355431093529"></a><a name="p1769355431093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1396599412093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102711587093529"><a name="p2102711587093529"></a><a name="p2102711587093529"></a><a href="WLAN.md#gace9dbbf9c1a035b350224b1832d35377">n_ciphersPairwise</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2096894637093529"><a name="p2096894637093529"></a><a name="p2096894637093529"></a>int32_t&nbsp;</p>
</td>
</tr>
<tr id="row832080866093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542754088093529"><a name="p1542754088093529"></a><a name="p1542754088093529"></a><a href="WLAN.md#ga53c85b4e0f5f5e10bb16935fb8a77df0">ciphersPairwise</a> [NL80211_MAX_NR_CIPHER_SUITES]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338719286093529"><a name="p1338719286093529"></a><a name="p1338719286093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1381166722093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p767005194093529"><a name="p767005194093529"></a><a name="p767005194093529"></a><a href="WLAN.md#ga35627fc7ac0924a52e51427375501f8a">n_akmSuites</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p637092653093529"><a name="p637092653093529"></a><a name="p637092653093529"></a>int32_t&nbsp;</p>
</td>
</tr>
<tr id="row2123434980093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1478182254093529"><a name="p1478182254093529"></a><a name="p1478182254093529"></a><a href="WLAN.md#ga142aeeaed24db6cd329c0b8b78ab13bc">akmSuites</a> [NL80211_MAX_NR_AKM_SUITES]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1539132793093529"><a name="p1539132793093529"></a><a name="p1539132793093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1421696328093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p163675905093529"><a name="p163675905093529"></a><a name="p163675905093529"></a><a href="WLAN.md#ga67b6c08be0641796798513fbbb13dd73">controlPortEthertype</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061918958093529"><a name="p1061918958093529"></a><a name="p1061918958093529"></a>uint16_t&nbsp;</p>
</td>
</tr>
<tr id="row1267608238093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329466119093529"><a name="p329466119093529"></a><a name="p329466119093529"></a><a href="WLAN.md#ga2f49a07024546730d0cd60e93cb9e450">controlPort</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1198146887093529"><a name="p1198146887093529"></a><a name="p1198146887093529"></a>int8_t&nbsp;</p>
</td>
</tr>
<tr id="row1901579073093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1857541843093529"><a name="p1857541843093529"></a><a name="p1857541843093529"></a><a href="WLAN.md#ga020b34dbfd5f961c86ef416873a9c02c">controlPortNoEncrypt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929305188093529"><a name="p929305188093529"></a><a name="p929305188093529"></a>int8_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

