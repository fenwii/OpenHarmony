# watchdog\_if.h<a name="EN-US_TOPIC_0000001055683462"></a>

## **Overview**<a name="section1177159512162113"></a>

**Related Modules:**

[WATCHDOG](watchdog.md)

**Description:**

Declares standard watchdog APIs. 

**Since:**

1.0

## **Summary**<a name="section1620543154162113"></a>

## Enumerations<a name="enum-members"></a>

<a name="table1934207372162113"></a>
<table><thead align="left"><tr id="row1652574881162113"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p639455541162113"><a name="p639455541162113"></a><a name="p639455541162113"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p712922103162113"><a name="p712922103162113"></a><a name="p712922103162113"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row715316518162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p632400594162113"><a name="p632400594162113"></a><a name="p632400594162113"></a><a href="watchdog.md#ga3c77a35e1051e3f99238029519ac1954">WatchdogStatus</a> { <a href="watchdog.md#gga3c77a35e1051e3f99238029519ac1954a2579c5f1c789b94d99988476031ec2a6">WATCHDOG_STOP</a>, <a href="watchdog.md#gga3c77a35e1051e3f99238029519ac1954aec39073df0b03eb51cc0e17380b86c68">WATCHDOG_START</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376475876162113"><a name="p376475876162113"></a><a name="p376475876162113"></a>Enumerates watchdog statuses. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table230945529162113"></a>
<table><thead align="left"><tr id="row1355399681162113"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1781456403162113"><a name="p1781456403162113"></a><a name="p1781456403162113"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p435291332162113"><a name="p435291332162113"></a><a name="p435291332162113"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row590289689162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p733925530162113"><a name="p733925530162113"></a><a name="p733925530162113"></a><a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a> (int16_t wdtId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p690404353162113"><a name="p690404353162113"></a><a name="p690404353162113"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p5586486162113"><a name="p5586486162113"></a><a name="p5586486162113"></a>Opens a watchdog. </p>
</td>
</tr>
<tr id="row1915179051162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085734822162113"><a name="p2085734822162113"></a><a name="p2085734822162113"></a><a href="watchdog.md#ga2090460cfbf603f7ac5d71f897a21bc5">WatchdogClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881147363162113"><a name="p881147363162113"></a><a name="p881147363162113"></a>void </p>
<p id="p284232915162113"><a name="p284232915162113"></a><a name="p284232915162113"></a>Closes a watchdog. </p>
</td>
</tr>
<tr id="row1164888691162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1903527601162113"><a name="p1903527601162113"></a><a name="p1903527601162113"></a><a href="watchdog.md#ga37d1311664523c25557b1280cb51ebdf">WatchdogGetStatus</a> (struct <a href="devhandle.md">DevHandle</a> *handle, int32_t *status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1098468300162113"><a name="p1098468300162113"></a><a name="p1098468300162113"></a>int32_t </p>
<p id="p685354432162113"><a name="p685354432162113"></a><a name="p685354432162113"></a>Obtains the watchdog status. </p>
</td>
</tr>
<tr id="row1239342195162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1422591149162113"><a name="p1422591149162113"></a><a name="p1422591149162113"></a><a href="watchdog.md#ga9e0f7009b8b117c6ffa7d10bc0267260">WatchdogStart</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124484602162113"><a name="p2124484602162113"></a><a name="p2124484602162113"></a>int32_t </p>
<p id="p999591563162113"><a name="p999591563162113"></a><a name="p999591563162113"></a>Starts a watchdog. </p>
</td>
</tr>
<tr id="row350076709162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1735041362162113"><a name="p1735041362162113"></a><a name="p1735041362162113"></a><a href="watchdog.md#ga0e45eae23d6fa67ebb2f5984d3b44c84">WatchdogStop</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p63724145162113"><a name="p63724145162113"></a><a name="p63724145162113"></a>int32_t </p>
<p id="p400542681162113"><a name="p400542681162113"></a><a name="p400542681162113"></a>Stops a watchdog. </p>
</td>
</tr>
<tr id="row800000607162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1879180127162113"><a name="p1879180127162113"></a><a name="p1879180127162113"></a><a href="watchdog.md#ga3a632198f1337342fba3bdb9c91d4b99">WatchdogSetTimeout</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t seconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1779077595162113"><a name="p1779077595162113"></a><a name="p1779077595162113"></a>int32_t </p>
<p id="p145104583162113"><a name="p145104583162113"></a><a name="p145104583162113"></a>Sets the watchdog timeout duration. </p>
</td>
</tr>
<tr id="row1187219659162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p843532110162113"><a name="p843532110162113"></a><a name="p843532110162113"></a><a href="watchdog.md#ga1dd8d1e262f8413826025cc868afc563">WatchdogGetTimeout</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t *seconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601172573162113"><a name="p601172573162113"></a><a name="p601172573162113"></a>int32_t </p>
<p id="p369400817162113"><a name="p369400817162113"></a><a name="p369400817162113"></a>Obtains the watchdog timeout duration. </p>
</td>
</tr>
<tr id="row78165635162113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267914808162113"><a name="p1267914808162113"></a><a name="p1267914808162113"></a><a href="watchdog.md#ga4d7a6beafd6a2702ef2a2b32618c5732">WatchdogFeed</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1418627566162113"><a name="p1418627566162113"></a><a name="p1418627566162113"></a>int32_t </p>
<p id="p757964831162113"><a name="p757964831162113"></a><a name="p757964831162113"></a>Feeds a watchdog, that is, resets a watchdog timer. </p>
</td>
</tr>
</tbody>
</table>

