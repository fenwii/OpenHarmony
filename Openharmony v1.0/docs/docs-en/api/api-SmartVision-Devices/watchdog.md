# WATCHDOG<a name="EN-US_TOPIC_0000001055203508"></a>

## **Overview**<a name="section804082357162106"></a>

Provides watchdog APIs, such as setting the watchdog timeout duration and feeding a watchdog \(resetting a watchdog timer\). 

If an error occurs in the main program of the system, for example, if the program crashes or the watchdog timer is not reset in time, the watchdog timer generates a reset signal, and the system restores from the suspending state to the normal state.

**Since:**

1.0

## **Summary**<a name="section502752646162106"></a>

## Files<a name="files"></a>

<a name="table12588835162106"></a>
<table><thead align="left"><tr id="row1817632168162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p480359445162106"><a name="p480359445162106"></a><a name="p480359445162106"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p967083658162106"><a name="p967083658162106"></a><a name="p967083658162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2074219842162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794254140162106"><a name="p1794254140162106"></a><a name="p1794254140162106"></a><a href="watchdog_if-h.md">watchdog_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1497337187162106"><a name="p1497337187162106"></a><a name="p1497337187162106"></a>Declares standard watchdog APIs. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1570916760162106"></a>
<table><thead align="left"><tr id="row2116456990162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2085773710162106"><a name="p2085773710162106"></a><a name="p2085773710162106"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p52468166162106"><a name="p52468166162106"></a><a name="p52468166162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1081438065162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635352800162106"><a name="p635352800162106"></a><a name="p635352800162106"></a><a href="watchdog.md#ga3c77a35e1051e3f99238029519ac1954">WatchdogStatus</a> { <a href="watchdog.md#gga3c77a35e1051e3f99238029519ac1954a2579c5f1c789b94d99988476031ec2a6">WATCHDOG_STOP</a>, <a href="watchdog.md#gga3c77a35e1051e3f99238029519ac1954aec39073df0b03eb51cc0e17380b86c68">WATCHDOG_START</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2011795849162106"><a name="p2011795849162106"></a><a name="p2011795849162106"></a>Enumerates watchdog statuses. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1363322977162106"></a>
<table><thead align="left"><tr id="row1021184540162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p459746260162106"><a name="p459746260162106"></a><a name="p459746260162106"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1095001996162106"><a name="p1095001996162106"></a><a name="p1095001996162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1021728838162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129389680162106"><a name="p1129389680162106"></a><a name="p1129389680162106"></a><a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a> (int16_t wdtId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1128676283162106"><a name="p1128676283162106"></a><a name="p1128676283162106"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p471223059162106"><a name="p471223059162106"></a><a name="p471223059162106"></a>Opens a watchdog. </p>
</td>
</tr>
<tr id="row505990931162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2097380686162106"><a name="p2097380686162106"></a><a name="p2097380686162106"></a><a href="watchdog.md#ga2090460cfbf603f7ac5d71f897a21bc5">WatchdogClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807033092162106"><a name="p807033092162106"></a><a name="p807033092162106"></a>void </p>
<p id="p167299083162106"><a name="p167299083162106"></a><a name="p167299083162106"></a>Closes a watchdog. </p>
</td>
</tr>
<tr id="row1356377214162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1320296319162106"><a name="p1320296319162106"></a><a name="p1320296319162106"></a><a href="watchdog.md#ga37d1311664523c25557b1280cb51ebdf">WatchdogGetStatus</a> (struct <a href="devhandle.md">DevHandle</a> *handle, int32_t *status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1585502134162106"><a name="p1585502134162106"></a><a name="p1585502134162106"></a>int32_t </p>
<p id="p1252714427162106"><a name="p1252714427162106"></a><a name="p1252714427162106"></a>Obtains the watchdog status. </p>
</td>
</tr>
<tr id="row2107830826162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1572075733162106"><a name="p1572075733162106"></a><a name="p1572075733162106"></a><a href="watchdog.md#ga9e0f7009b8b117c6ffa7d10bc0267260">WatchdogStart</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987893302162106"><a name="p987893302162106"></a><a name="p987893302162106"></a>int32_t </p>
<p id="p2124726476162106"><a name="p2124726476162106"></a><a name="p2124726476162106"></a>Starts a watchdog. </p>
</td>
</tr>
<tr id="row1084873804162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386300491162106"><a name="p386300491162106"></a><a name="p386300491162106"></a><a href="watchdog.md#ga0e45eae23d6fa67ebb2f5984d3b44c84">WatchdogStop</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2121095615162106"><a name="p2121095615162106"></a><a name="p2121095615162106"></a>int32_t </p>
<p id="p375598982162106"><a name="p375598982162106"></a><a name="p375598982162106"></a>Stops a watchdog. </p>
</td>
</tr>
<tr id="row420506125162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1389432283162106"><a name="p1389432283162106"></a><a name="p1389432283162106"></a><a href="watchdog.md#ga3a632198f1337342fba3bdb9c91d4b99">WatchdogSetTimeout</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t seconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1352390749162106"><a name="p1352390749162106"></a><a name="p1352390749162106"></a>int32_t </p>
<p id="p1151592591162106"><a name="p1151592591162106"></a><a name="p1151592591162106"></a>Sets the watchdog timeout duration. </p>
</td>
</tr>
<tr id="row343898873162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1280345361162106"><a name="p1280345361162106"></a><a name="p1280345361162106"></a><a href="watchdog.md#ga1dd8d1e262f8413826025cc868afc563">WatchdogGetTimeout</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t *seconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1573280649162106"><a name="p1573280649162106"></a><a name="p1573280649162106"></a>int32_t </p>
<p id="p806381058162106"><a name="p806381058162106"></a><a name="p806381058162106"></a>Obtains the watchdog timeout duration. </p>
</td>
</tr>
<tr id="row1608405122162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557476580162106"><a name="p557476580162106"></a><a name="p557476580162106"></a><a href="watchdog.md#ga4d7a6beafd6a2702ef2a2b32618c5732">WatchdogFeed</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367619410162106"><a name="p1367619410162106"></a><a name="p1367619410162106"></a>int32_t </p>
<p id="p1883104496162106"><a name="p1883104496162106"></a><a name="p1883104496162106"></a>Feeds a watchdog, that is, resets a watchdog timer. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section775356448162106"></a>

## **Enumeration Type Documentation**<a name="section1648468561162106"></a>

## WatchdogStatus<a name="ga3c77a35e1051e3f99238029519ac1954"></a>

```
enum [WatchdogStatus](watchdog.md#ga3c77a35e1051e3f99238029519ac1954)
```

 **Description:**

Enumerates watchdog statuses. 

To obtain the watchdog status, call the  [WatchdogGetStatus](watchdog.md#ga37d1311664523c25557b1280cb51ebdf)  function.

<a name="table711330702162106"></a>
<table><thead align="left"><tr id="row377571027162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1044780265162106"><a name="p1044780265162106"></a><a name="p1044780265162106"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1034715443162106"><a name="p1034715443162106"></a><a name="p1034715443162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1959016999162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3c77a35e1051e3f99238029519ac1954a2579c5f1c789b94d99988476031ec2a6"><a name="gga3c77a35e1051e3f99238029519ac1954a2579c5f1c789b94d99988476031ec2a6"></a><a name="gga3c77a35e1051e3f99238029519ac1954a2579c5f1c789b94d99988476031ec2a6"></a></strong>WATCHDOG_STOP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p990009137162106"><a name="p990009137162106"></a><a name="p990009137162106"></a>Stopped </p>
 </td>
</tr>
<tr id="row751198108162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3c77a35e1051e3f99238029519ac1954aec39073df0b03eb51cc0e17380b86c68"><a name="gga3c77a35e1051e3f99238029519ac1954aec39073df0b03eb51cc0e17380b86c68"></a><a name="gga3c77a35e1051e3f99238029519ac1954aec39073df0b03eb51cc0e17380b86c68"></a></strong>WATCHDOG_START </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699150563162106"><a name="p1699150563162106"></a><a name="p1699150563162106"></a>Started </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1023106393162106"></a>

## WatchdogClose\(\)<a name="ga2090460cfbf603f7ac5d71f897a21bc5"></a>

```
void WatchdogClose (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Closes a watchdog. 

If you no longer need a watchdog, call this function to close it and release its device handle to prevent unnecessary use of memory resources.

**Parameters:**

<a name="table702466403162106"></a>
<table><thead align="left"><tr id="row1798689070162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p844494267162106"><a name="p844494267162106"></a><a name="p844494267162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1650499444162106"><a name="p1650499444162106"></a><a name="p1650499444162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1926703764162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog device handle.</td>
</tr>
</tbody>
</table>

## WatchdogFeed\(\)<a name="ga4d7a6beafd6a2702ef2a2b32618c5732"></a>

```
int32_t WatchdogFeed (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Feeds a watchdog, that is, resets a watchdog timer. 

After a watchdog is started, you must feed it to reset the watchdog timer periodically. If you do not do so, the watchdog hardware will reset the system upon a timeout.

**Parameters:**

<a name="table673287416162106"></a>
<table><thead align="left"><tr id="row482410864162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p202177888162106"><a name="p202177888162106"></a><a name="p202177888162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1359530040162106"><a name="p1359530040162106"></a><a name="p1359530040162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1549542987162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog handle, which is obtained via <a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the watchdog is fed; returns a negative value otherwise. 



## WatchdogGetStatus\(\)<a name="ga37d1311664523c25557b1280cb51ebdf"></a>

```
int32_t WatchdogGetStatus (struct [DevHandle](devhandle.md) * handle, int32_t * status )
```

 **Description:**

Obtains the watchdog status. 

For the available watchdog statuses, see  [WatchdogStatus](watchdog.md#ga3c77a35e1051e3f99238029519ac1954).

**Parameters:**

<a name="table1109627385162106"></a>
<table><thead align="left"><tr id="row157512352162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1031245386162106"><a name="p1031245386162106"></a><a name="p1031245386162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p968141411162106"><a name="p968141411162106"></a><a name="p968141411162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row247205060162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog handle, which is obtained via <a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a>. </td>
</tr>
<tr id="row628262330162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog status.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the watchdog status is obtained; returns a negative value otherwise.



## WatchdogGetTimeout\(\)<a name="ga1dd8d1e262f8413826025cc868afc563"></a>

```
int32_t WatchdogGetTimeout (struct [DevHandle](devhandle.md) * handle, uint32_t * seconds )
```

 **Description:**

Obtains the watchdog timeout duration. 

**Parameters:**

<a name="table2146492457162106"></a>
<table><thead align="left"><tr id="row859695259162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1975717523162106"><a name="p1975717523162106"></a><a name="p1975717523162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1594818213162106"><a name="p1594818213162106"></a><a name="p1594818213162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1149375869162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog handle, which is obtained via <a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a>. </td>
</tr>
<tr id="row369429614162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">seconds</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timeout duration, in seconds.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the watchdog timeout duration is obtained; returns a negative value otherwise. 



## WatchdogOpen\(\)<a name="ga46db3382f1d577feb52a523b8fb5e921"></a>

```
struct [DevHandle](devhandle.md)* WatchdogOpen (int16_t wdtId)
```

 **Description:**

Opens a watchdog. 

Before operating a watchdog, you must call this function to open it and obtain its device handle.

**Parameters:**

<a name="table646005120162106"></a>
<table><thead align="left"><tr id="row1178732989162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1673687544162106"><a name="p1673687544162106"></a><a name="p1673687544162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p150451106162106"><a name="p150451106162106"></a><a name="p150451106162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1636017916162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">wdtId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the watchdog ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the device handle of the watch dog if the operation is successful; returns  **NULL**  otherwise.



## WatchdogSetTimeout\(\)<a name="ga3a632198f1337342fba3bdb9c91d4b99"></a>

```
int32_t WatchdogSetTimeout (struct [DevHandle](devhandle.md) * handle, uint32_t seconds )
```

 **Description:**

Sets the watchdog timeout duration. 

**Parameters:**

<a name="table870849905162106"></a>
<table><thead align="left"><tr id="row1864660057162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1295262164162106"><a name="p1295262164162106"></a><a name="p1295262164162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p55770614162106"><a name="p55770614162106"></a><a name="p55770614162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1926181627162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog handle, which is obtained via <a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a>. </td>
</tr>
<tr id="row995496575162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">seconds</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration, in seconds.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 



## WatchdogStart\(\)<a name="ga9e0f7009b8b117c6ffa7d10bc0267260"></a>

```
int32_t WatchdogStart (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Starts a watchdog. 

This function starts the watchdog timer. You must feed the watchdog periodically; otherwise, the watchdog hardware will reset the system upon a timeout.

**Parameters:**

<a name="table1333726643162106"></a>
<table><thead align="left"><tr id="row479109723162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p234009706162106"><a name="p234009706162106"></a><a name="p234009706162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1279652329162106"><a name="p1279652329162106"></a><a name="p1279652329162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row313875691162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog handle, which is obtained via <a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the watchdog is successfully started; returns a negative value otherwise. 

**Attention:**

If the watchdog timer has started before this function is called, calling this function will succeed; however, the watchdog hardware determines whether to reset the timer.



## WatchdogStop\(\)<a name="ga0e45eae23d6fa67ebb2f5984d3b44c84"></a>

```
int32_t WatchdogStop (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Stops a watchdog. 

If the watchdog has stopped before this function is called, calling this function will succeed.

**Parameters:**

<a name="table284815871162106"></a>
<table><thead align="left"><tr id="row2083959275162106"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p332295656162106"><a name="p332295656162106"></a><a name="p332295656162106"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1674035267162106"><a name="p1674035267162106"></a><a name="p1674035267162106"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1208057067162106"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the watchdog handle, which is obtained via <a href="watchdog.md#ga46db3382f1d577feb52a523b8fb5e921">WatchdogOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the watchdog is successfully stopped; returns a negative value otherwise. 



