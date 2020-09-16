# AudioAttribute<a name="EN-US_TOPIC_0000001055198120"></a>

## **Overview**<a name="section936998558093529"></a>

**Related Modules:**

[Audio](audio.md)

**Description:**

Provides attribute-related APIs for audio rendering or capturing, including functions to obtain frame information and set audio sampling attributes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2045661001093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2033600214093529"></a>
<table><thead align="left"><tr id="row883343569093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p707424976093529"><a name="p707424976093529"></a><a name="p707424976093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1755597900093529"><a name="p1755597900093529"></a><a name="p1755597900093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row73012321093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1465201397093529"><a name="p1465201397093529"></a><a name="p1465201397093529"></a><a href="audioattribute.md#a74a23f0544ac688223e61fa71a307851">GetFrameSize</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, uint64_t *size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49165509093529"><a name="p49165509093529"></a><a name="p49165509093529"></a>int32_t(* </p>
<p id="p146074423093529"><a name="p146074423093529"></a><a name="p146074423093529"></a>Obtains the audio frame size, that is, the length (in bytes) of a frame. </p>
</td>
</tr>
<tr id="row885372838093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143100437093529"><a name="p143100437093529"></a><a name="p143100437093529"></a><a href="audioattribute.md#ab31fee582dc33b9320e0a0e5d16ae0e6">GetFrameCount</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, uint64_t *count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648035981093529"><a name="p648035981093529"></a><a name="p648035981093529"></a>int32_t(* </p>
<p id="p891047322093529"><a name="p891047322093529"></a><a name="p891047322093529"></a>Obtains the number of audio frames in the audio buffer. </p>
</td>
</tr>
<tr id="row1039736740093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584587342093529"><a name="p584587342093529"></a><a name="p584587342093529"></a><a href="audioattribute.md#a502fe4e4b97cd253244debcc67d45c4d">SetSampleAttributes</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, const struct <a href="audiosampleattributes.md">AudioSampleAttributes</a> *attrs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557400752093529"><a name="p1557400752093529"></a><a name="p1557400752093529"></a>int32_t(* </p>
<p id="p1014270069093529"><a name="p1014270069093529"></a><a name="p1014270069093529"></a>Sets audio sampling attributes. </p>
</td>
</tr>
<tr id="row1388192876093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1741835708093529"><a name="p1741835708093529"></a><a name="p1741835708093529"></a><a href="audioattribute.md#a2f92d8704ef677a07d664c33342e4318">GetSampleAttributes</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, struct <a href="audiosampleattributes.md">AudioSampleAttributes</a> *attrs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p454003813093529"><a name="p454003813093529"></a><a name="p454003813093529"></a>int32_t(* </p>
<p id="p795681825093529"><a name="p795681825093529"></a><a name="p795681825093529"></a>Obtains audio sampling attributes. </p>
</td>
</tr>
<tr id="row1156501298093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1763769235093529"><a name="p1763769235093529"></a><a name="p1763769235093529"></a><a href="audioattribute.md#ad070369ffa9d88df541aaf0ffbbcfbfd">GetCurrentChannelId</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, uint32_t *channelId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p593741241093529"><a name="p593741241093529"></a><a name="p593741241093529"></a>int32_t(* </p>
<p id="p30361972093529"><a name="p30361972093529"></a><a name="p30361972093529"></a>Obtains the data channel ID of the audio. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1926643650093529"></a>

## **Field Documentation**<a name="section2033546313093529"></a>

## GetCurrentChannelId<a name="ad070369ffa9d88df541aaf0ffbbcfbfd"></a>

```
int32_t(* AudioAttribute::GetCurrentChannelId) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, uint32_t *channelId)
```

 **Description:**

Obtains the data channel ID of the audio. 

**Parameters:**

<a name="table1676997330093529"></a>
<table><thead align="left"><tr id="row1483049894093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p460347542093529"><a name="p460347542093529"></a><a name="p460347542093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1368527856093529"><a name="p1368527856093529"></a><a name="p1368527856093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1486548316093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row1181347016093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">channelId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data channel ID. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the data channel ID is obtained; returns a negative value otherwise. 



## GetFrameCount<a name="ab31fee582dc33b9320e0a0e5d16ae0e6"></a>

```
int32_t(* AudioAttribute::GetFrameCount) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, uint64_t *count)
```

 **Description:**

Obtains the number of audio frames in the audio buffer. 

**Parameters:**

<a name="table2002532161093529"></a>
<table><thead align="left"><tr id="row1230897658093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1130963557093529"><a name="p1130963557093529"></a><a name="p1130963557093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2029274030093529"><a name="p2029274030093529"></a><a name="p2029274030093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row268093107093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row1411687481093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the number of audio frames in the audio buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the number of audio frames is obtained; returns a negative value otherwise. 



## GetFrameSize<a name="a74a23f0544ac688223e61fa71a307851"></a>

```
int32_t(* AudioAttribute::GetFrameSize) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, uint64_t *size)
```

 **Description:**

Obtains the audio frame size, that is, the length \(in bytes\) of a frame. 

**Parameters:**

<a name="table1627942691093529"></a>
<table><thead align="left"><tr id="row1326402869093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p71958469093529"><a name="p71958469093529"></a><a name="p71958469093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p174397629093529"><a name="p174397629093529"></a><a name="p174397629093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1751880161093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row453850506093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio frame size (in bytes). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the audio frame size is obtained; returns a negative value otherwise. 



## GetSampleAttributes<a name="a2f92d8704ef677a07d664c33342e4318"></a>

```
int32_t(* AudioAttribute::GetSampleAttributes) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, struct [AudioSampleAttributes](audiosampleattributes.md) *attrs)
```

 **Description:**

Obtains audio sampling attributes. 

**Parameters:**

<a name="table2116476084093529"></a>
<table><thead align="left"><tr id="row597786836093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1362800200093529"><a name="p1362800200093529"></a><a name="p1362800200093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p891542615093529"><a name="p891542615093529"></a><a name="p891542615093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1516734735093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row43380260093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio sampling attributes, such as the sampling rate, sampling precision, and channel. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if audio sampling attributes are obtained; returns a negative value otherwise. 

**See also:**

[SetSampleAttributes](audioattribute.md#a502fe4e4b97cd253244debcc67d45c4d) 

## SetSampleAttributes<a name="a502fe4e4b97cd253244debcc67d45c4d"></a>

```
int32_t(* AudioAttribute::SetSampleAttributes) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle, const struct [AudioSampleAttributes](audiosampleattributes.md) *attrs)
```

 **Description:**

Sets audio sampling attributes. 

**Parameters:**

<a name="table1735675839093529"></a>
<table><thead align="left"><tr id="row987449368093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1300741637093529"><a name="p1300741637093529"></a><a name="p1300741637093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p894873182093529"><a name="p894873182093529"></a><a name="p894873182093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2110365661093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row1784143841093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio sampling attributes to set, such as the sampling rate, sampling precision, and channel. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetSampleAttributes](audioattribute.md#a2f92d8704ef677a07d664c33342e4318) 

