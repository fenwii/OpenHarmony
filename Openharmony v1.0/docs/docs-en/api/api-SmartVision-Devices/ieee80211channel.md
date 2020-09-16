# Ieee80211Channel<a name="EN-US_TOPIC_0000001054879538"></a>

## **Overview**<a name="section691054124093531"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Describes a communication channel. 

**Since:**

1.0

## **Summary**<a name="section185932033093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1275558986093531"></a>
<table><thead align="left"><tr id="row1536907974093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p27690188093531"><a name="p27690188093531"></a><a name="p27690188093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1967543010093531"><a name="p1967543010093531"></a><a name="p1967543010093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row537609215093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047806183093531"><a name="p1047806183093531"></a><a name="p1047806183093531"></a><a href="wlan.md#gaab4e3330566d5b0b02e7c6117c7b9a73">band</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764668166093531"><a name="p764668166093531"></a><a name="p764668166093531"></a>enum <a href="wlan.md#ga9882f415202cf9acb0f4cdfbc456a88d">Ieee80211Band</a> </p>
</td>
</tr>
<tr id="row1705696616093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330009169093531"><a name="p1330009169093531"></a><a name="p1330009169093531"></a><a href="wlan.md#ga42300a5593bf6b40a4d823af2dbe2a5d">centerFreq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140727734093531"><a name="p140727734093531"></a><a name="p140727734093531"></a>uint16_t </p>
</td>
</tr>
<tr id="row767467343093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p421660051093531"><a name="p421660051093531"></a><a name="p421660051093531"></a><a href="wlan.md#ga88c500579917b7a4b0167623851abcf2">hwValue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p632745991093531"><a name="p632745991093531"></a><a name="p632745991093531"></a>uint16_t </p>
</td>
</tr>
<tr id="row294476051093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p604743865093531"><a name="p604743865093531"></a><a name="p604743865093531"></a><a href="wlan.md#gaadedfd33df129639f135a6f5d0322e4e">flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1344846879093531"><a name="p1344846879093531"></a><a name="p1344846879093531"></a>uint32_t </p>
</td>
</tr>
<tr id="row1596025200093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529129567093531"><a name="p529129567093531"></a><a name="p529129567093531"></a><a href="wlan.md#gacd256a8179e084497aad4cacfac77dc2">maxAntennaGain</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980992745093531"><a name="p980992745093531"></a><a name="p980992745093531"></a>int32_t </p>
</td>
</tr>
<tr id="row443399887093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p373956044093531"><a name="p373956044093531"></a><a name="p373956044093531"></a><a href="wlan.md#gaf998a486d7bc53071e68374a13aa18d8">maxPower</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163230080093531"><a name="p1163230080093531"></a><a name="p1163230080093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1351957326093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p6906171093531"><a name="p6906171093531"></a><a name="p6906171093531"></a><a href="wlan.md#ga55c6f1eaedc16b99dc299530a0dc6f83">beaconFound</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790765334093531"><a name="p790765334093531"></a><a name="p790765334093531"></a>int8_t </p>
</td>
</tr>
<tr id="row1719329093093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944889925093531"><a name="p1944889925093531"></a><a name="p1944889925093531"></a><a href="wlan.md#ga8ae51118ee5e1a121bad85055ecad454">resv</a> [IEEE80211_CHANNEL_RESV]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300824917093531"><a name="p1300824917093531"></a><a name="p1300824917093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row261584641093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p951153875093531"><a name="p951153875093531"></a><a name="p951153875093531"></a><a href="wlan.md#gaa8e6146a2fa16a47e794d7d9bbaccf1e">origFlags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p540756158093531"><a name="p540756158093531"></a><a name="p540756158093531"></a>uint32_t </p>
</td>
</tr>
<tr id="row1315811359093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1519868565093531"><a name="p1519868565093531"></a><a name="p1519868565093531"></a><a href="wlan.md#gaf5bc0d20f7c46fbcfd69cb62c3470dfe">origMag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514669926093531"><a name="p514669926093531"></a><a name="p514669926093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1224607338093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903176081093531"><a name="p903176081093531"></a><a name="p903176081093531"></a><a href="wlan.md#gaa9666ab4a0f723741328722d1ab74588">origMpwr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229307633093531"><a name="p1229307633093531"></a><a name="p1229307633093531"></a>int32_t </p>
</td>
</tr>
</tbody>
</table>

