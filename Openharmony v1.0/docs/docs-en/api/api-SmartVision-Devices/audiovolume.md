# AudioVolume<a name="EN-US_TOPIC_0000001054598153"></a>

## **Overview**<a name="section891844076093529"></a>

**Related Modules:**

[Audio](audio.md)

**Description:**

Provides volume-related APIs for audio rendering or capturing, including functions to set the mute operation, volume, and gain. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section170702415093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table935442422093529"></a>
<table><thead align="left"><tr id="row1362139157093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p6782264093529"><a name="p6782264093529"></a><a name="p6782264093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1776037723093529"><a name="p1776037723093529"></a><a name="p1776037723093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row690396245093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997491488093529"><a name="p997491488093529"></a><a name="p997491488093529"></a><a href="audiovolume.md#a79c127fa37eb2dbf8dc5fe9f0ed4421e">SetMute</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, bool mute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202809094093529"><a name="p1202809094093529"></a><a name="p1202809094093529"></a>int32_t(* </p>
<p id="p1179793263093529"><a name="p1179793263093529"></a><a name="p1179793263093529"></a>Sets the mute operation for the audio. </p>
</td>
</tr>
<tr id="row816291286093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p669363454093529"><a name="p669363454093529"></a><a name="p669363454093529"></a><a href="audiovolume.md#a75fcb5bda7e0ca9b823187f6056ad1d4">GetMute</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, bool *mute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264433287093529"><a name="p264433287093529"></a><a name="p264433287093529"></a>int32_t(* </p>
<p id="p1122515558093529"><a name="p1122515558093529"></a><a name="p1122515558093529"></a>Obtains the mute operation set for the audio. </p>
</td>
</tr>
<tr id="row1234034709093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p502038161093529"><a name="p502038161093529"></a><a name="p502038161093529"></a><a href="audiovolume.md#aebf67caf924cba5f3be9d0f395390908">SetVolume</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, float volume)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p95070023093529"><a name="p95070023093529"></a><a name="p95070023093529"></a>int32_t(* </p>
<p id="p1381585916093529"><a name="p1381585916093529"></a><a name="p1381585916093529"></a>Sets the audio volume. </p>
</td>
</tr>
<tr id="row933920953093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302109921093529"><a name="p1302109921093529"></a><a name="p1302109921093529"></a><a href="audiovolume.md#a649524ce280ecdb62ddacb78e1a63439">GetVolume</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, float *volume)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1277071742093529"><a name="p1277071742093529"></a><a name="p1277071742093529"></a>int32_t(* </p>
<p id="p1712955929093529"><a name="p1712955929093529"></a><a name="p1712955929093529"></a>Obtains the audio volume. </p>
</td>
</tr>
<tr id="row1517800626093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044450501093529"><a name="p2044450501093529"></a><a name="p2044450501093529"></a><a href="audiovolume.md#aa42ff18fa2b7e6780acf120ea49054ed">GetGainThreshold</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, float *min, float *max)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867974546093529"><a name="p867974546093529"></a><a name="p867974546093529"></a>int32_t(* </p>
<p id="p1595973203093529"><a name="p1595973203093529"></a><a name="p1595973203093529"></a>Obtains the range of the audio gain. </p>
</td>
</tr>
<tr id="row1610683547093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2017776776093529"><a name="p2017776776093529"></a><a name="p2017776776093529"></a><a href="audiovolume.md#a5ff7f9e5b763d20822a1fadecc5a8db7">GetGain</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, float *gain)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114369398093529"><a name="p114369398093529"></a><a name="p114369398093529"></a>int32_t(* </p>
<p id="p3372462093529"><a name="p3372462093529"></a><a name="p3372462093529"></a>Obtains the audio gain. </p>
</td>
</tr>
<tr id="row224241809093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1188053879093529"><a name="p1188053879093529"></a><a name="p1188053879093529"></a><a href="audiovolume.md#ab667c5f8754d0b10121451a57abbe429">SetGain</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, float gain)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1081553004093529"><a name="p1081553004093529"></a><a name="p1081553004093529"></a>int32_t(* </p>
<p id="p1982363719093529"><a name="p1982363719093529"></a><a name="p1982363719093529"></a>Sets the audio gain. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section297976481093529"></a>

## **Field Documentation**<a name="section570513943093529"></a>

## GetGain<a name="a5ff7f9e5b763d20822a1fadecc5a8db7"></a>

```
int32_t(* AudioVolume::GetGain) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, float *gain)
```

 **Description:**

Obtains the audio gain. 

**Parameters:**

<a name="table1629564564093529"></a>
<table><thead align="left"><tr id="row266958968093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p296790972093529"><a name="p296790972093529"></a><a name="p296790972093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1479496832093529"><a name="p1479496832093529"></a><a name="p1479496832093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2095789939093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row605196641093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gain</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio gain. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the audio gain is obtained; returns a negative value otherwise. 

**See also:**

[GetGainThreshold](audiovolume.md#aa42ff18fa2b7e6780acf120ea49054ed) 

## GetGainThreshold<a name="aa42ff18fa2b7e6780acf120ea49054ed"></a>

```
int32_t(* AudioVolume::GetGainThreshold) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, float *min, float *max)
```

 **Description:**

Obtains the range of the audio gain. 

The audio gain can be expressed in one of the following two ways \(depending on the chip platform\), corresponding to two types of value ranges: 

**Parameters:**

<a name="table868498390093529"></a>
<table><thead align="left"><tr id="row1661485470093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p906756001093529"><a name="p906756001093529"></a><a name="p906756001093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1726746302093529"><a name="p1726746302093529"></a><a name="p1726746302093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row62648005093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row2035432634093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">min</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the minimum value of the range. </td>
</tr>
<tr id="row894217910093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">max</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the maximum value of the range. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the range is obtained; returns a negative value otherwise. 

**See also:**

[GetGain](audiovolume.md#a5ff7f9e5b763d20822a1fadecc5a8db7) 

## GetMute<a name="a75fcb5bda7e0ca9b823187f6056ad1d4"></a>

```
int32_t(* AudioVolume::GetMute) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, bool *mute)
```

 **Description:**

Obtains the mute operation set for the audio. 

**Parameters:**

<a name="table460839496093529"></a>
<table><thead align="left"><tr id="row1292394694093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1841902693093529"><a name="p1841902693093529"></a><a name="p1841902693093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p822607811093529"><a name="p822607811093529"></a><a name="p822607811093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row422066367093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row135291710093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mute</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mute operation set for the audio. Value <strong id="b95882060093529"><a name="b95882060093529"></a><a name="b95882060093529"></a>true</strong> means that the audio is muted, and <strong id="b631635002093529"><a name="b631635002093529"></a><a name="b631635002093529"></a>false</strong> means the opposite. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the mute operation is obtained; returns a negative value otherwise. 

**See also:**

[SetMute](audiovolume.md#a79c127fa37eb2dbf8dc5fe9f0ed4421e) 

## GetVolume<a name="a649524ce280ecdb62ddacb78e1a63439"></a>

```
int32_t(* AudioVolume::GetVolume) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, float *volume)
```

 **Description:**

Obtains the audio volume. 

**Parameters:**

<a name="table538004873093529"></a>
<table><thead align="left"><tr id="row657959418093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p824423118093529"><a name="p824423118093529"></a><a name="p824423118093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1968750967093529"><a name="p1968750967093529"></a><a name="p1968750967093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1407553026093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row301105229093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">volume</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the volume to obtain. The value ranges from 0.0 to 1.0. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the volume is obtained; returns a negative value otherwise. 

**See also:**

[SetVolume](audiovolume.md#aebf67caf924cba5f3be9d0f395390908) 

## SetGain<a name="ab667c5f8754d0b10121451a57abbe429"></a>

```
int32_t(* AudioVolume::SetGain) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, float gain)
```

 **Description:**

Sets the audio gain. 

**Parameters:**

<a name="table1970568135093529"></a>
<table><thead align="left"><tr id="row367035938093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p944006992093529"><a name="p944006992093529"></a><a name="p944006992093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1410472517093529"><a name="p1410472517093529"></a><a name="p1410472517093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1545397542093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row810703336093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gain</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio gain to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetGainThreshold](audiovolume.md#aa42ff18fa2b7e6780acf120ea49054ed) 

## SetMute<a name="a79c127fa37eb2dbf8dc5fe9f0ed4421e"></a>

```
int32_t(* AudioVolume::SetMute) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, bool mute)
```

 **Description:**

Sets the mute operation for the audio. 

**Parameters:**

<a name="table1431097655093529"></a>
<table><thead align="left"><tr id="row601242116093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p409303485093529"><a name="p409303485093529"></a><a name="p409303485093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1239866234093529"><a name="p1239866234093529"></a><a name="p1239866234093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1216090141093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row1707240016093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mute</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to mute the audio. Value <strong id="b1218945662093529"><a name="b1218945662093529"></a><a name="b1218945662093529"></a>true</strong> means to mute the audio, and <strong id="b1512404052093529"><a name="b1512404052093529"></a><a name="b1512404052093529"></a>false</strong> means the opposite. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetMute](audiovolume.md#a75fcb5bda7e0ca9b823187f6056ad1d4) 

## SetVolume<a name="aebf67caf924cba5f3be9d0f395390908"></a>

```
int32_t(* AudioVolume::SetVolume) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, float volume)
```

 **Description:**

Sets the audio volume. 

The volume ranges from 0.0 to 1.0. If the volume level in an audio service ranges from 0 to 15,  **0.0**  indicates that the audio is muted, and  **1.0**  indicates the maximum volume level \(15\).

**Parameters:**

<a name="table203514513093529"></a>
<table><thead align="left"><tr id="row1316567439093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p879235417093529"><a name="p879235417093529"></a><a name="p879235417093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p221858954093529"><a name="p221858954093529"></a><a name="p221858954093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1767365621093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row293198829093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">volume</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the volume to set. The value ranges from 0.0 to 1.0. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetVolume](audiovolume.md#a649524ce280ecdb62ddacb78e1a63439) 

