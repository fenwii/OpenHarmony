# AudioControl<a name="EN-US_TOPIC_0000001055078129"></a>

## **Overview**<a name="section1292093309093529"></a>

**Related Modules:**

[Audio](audio.md)

**Description:**

Provides control-related APIs for audio rendering or capturing, including functions to start, stop, pause, and resume audio rendering or capturing, and flush data in the audio buffer. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section528807826093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1313765846093529"></a>
<table><thead align="left"><tr id="row105031931093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1376424132093529"><a name="p1376424132093529"></a><a name="p1376424132093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1206642964093529"><a name="p1206642964093529"></a><a name="p1206642964093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1627808900093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p922727782093529"><a name="p922727782093529"></a><a name="p922727782093529"></a><a href="audiocontrol.md#a80ddae13819bb1eb348ad4b57597e930">Start</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164116476093529"><a name="p1164116476093529"></a><a name="p1164116476093529"></a>int32_t(* </p>
<p id="p579336198093529"><a name="p579336198093529"></a><a name="p579336198093529"></a>Starts audio rendering or capturing. </p>
</td>
</tr>
<tr id="row521428968093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1055060287093529"><a name="p1055060287093529"></a><a name="p1055060287093529"></a><a href="audiocontrol.md#a62e385e391ba1efed35021ee67ab9449">Stop</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380195099093529"><a name="p380195099093529"></a><a name="p380195099093529"></a>int32_t(* </p>
<p id="p74751282093529"><a name="p74751282093529"></a><a name="p74751282093529"></a>Stops audio rendering or capturing. </p>
</td>
</tr>
<tr id="row1037966422093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1543130650093529"><a name="p1543130650093529"></a><a name="p1543130650093529"></a><a href="audiocontrol.md#a16a26deffa17b9f143f602763a260908">Pause</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1980836348093529"><a name="p1980836348093529"></a><a name="p1980836348093529"></a>int32_t(* </p>
<p id="p1698706658093529"><a name="p1698706658093529"></a><a name="p1698706658093529"></a>Pauses audio rendering or capturing. </p>
</td>
</tr>
<tr id="row339933741093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087710218093529"><a name="p1087710218093529"></a><a name="p1087710218093529"></a><a href="audiocontrol.md#ac59c3e9a5ff9041989871f67253a1e8d">Resume</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199755923093529"><a name="p1199755923093529"></a><a name="p1199755923093529"></a>int32_t(* </p>
<p id="p1285224893093529"><a name="p1285224893093529"></a><a name="p1285224893093529"></a>Resumes audio rendering or capturing. </p>
</td>
</tr>
<tr id="row742108357093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p286365082093529"><a name="p286365082093529"></a><a name="p286365082093529"></a><a href="audiocontrol.md#acebc54c385b91ddc52b6b7849ddf12d0">Flush</a> )(<a href="audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246705083093529"><a name="p246705083093529"></a><a name="p246705083093529"></a>int32_t(* </p>
<p id="p1544741887093529"><a name="p1544741887093529"></a><a name="p1544741887093529"></a>Flushes data in the audio buffer. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section471987161093529"></a>

## **Field Documentation**<a name="section1745247793093529"></a>

## Flush<a name="acebc54c385b91ddc52b6b7849ddf12d0"></a>

```
int32_t(* AudioControl::Flush) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle)
```

 **Description:**

Flushes data in the audio buffer. 

**Parameters:**

<a name="table986688071093529"></a>
<table><thead align="left"><tr id="row2121388092093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p463612065093529"><a name="p463612065093529"></a><a name="p463612065093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1420316507093529"><a name="p1420316507093529"></a><a name="p1420316507093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row672252771093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the flush is successful; returns a negative value otherwise. 



## Pause<a name="a16a26deffa17b9f143f602763a260908"></a>

```
int32_t(* AudioControl::Pause) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle)
```

 **Description:**

Pauses audio rendering or capturing. 

**Parameters:**

<a name="table1029364314093529"></a>
<table><thead align="left"><tr id="row705900441093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1153417946093529"><a name="p1153417946093529"></a><a name="p1153417946093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p267949451093529"><a name="p267949451093529"></a><a name="p267949451093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1655868003093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the rendering or capturing is successfully paused; returns a negative value otherwise. 

**See also:**

[Resume](audiocontrol.md#ac59c3e9a5ff9041989871f67253a1e8d) 

## Resume<a name="ac59c3e9a5ff9041989871f67253a1e8d"></a>

```
int32_t(* AudioControl::Resume) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle)
```

 **Description:**

Resumes audio rendering or capturing. 

**Parameters:**

<a name="table1685574613093529"></a>
<table><thead align="left"><tr id="row1196862347093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p683099292093529"><a name="p683099292093529"></a><a name="p683099292093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1743947570093529"><a name="p1743947570093529"></a><a name="p1743947570093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1082952657093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the rendering or capturing is successfully resumed; returns a negative value otherwise. 

**See also:**

[Pause](audiocontrol.md#a16a26deffa17b9f143f602763a260908) 

## Start<a name="a80ddae13819bb1eb348ad4b57597e930"></a>

```
int32_t(* AudioControl::Start) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle)
```

 **Description:**

Starts audio rendering or capturing. 

**Parameters:**

<a name="table1925879294093529"></a>
<table><thead align="left"><tr id="row719680072093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p543638970093529"><a name="p543638970093529"></a><a name="p543638970093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p756634070093529"><a name="p756634070093529"></a><a name="p756634070093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row75112197093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the rendering or capturing is successfully started; returns a negative value otherwise. 

**See also:**

[Stop](audiocontrol.md#a62e385e391ba1efed35021ee67ab9449) 

## Stop<a name="a62e385e391ba1efed35021ee67ab9449"></a>

```
int32_t(* AudioControl::Stop) ([AudioHandle](audio.md#ga18675ddb073465fdeac33a897f675d79) handle)
```

 **Description:**

Stops audio rendering or capturing. 

**Parameters:**

<a name="table263706491093529"></a>
<table><thead align="left"><tr id="row1309391234093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1218960347093529"><a name="p1218960347093529"></a><a name="p1218960347093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1312910437093529"><a name="p1312910437093529"></a><a name="p1312910437093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row144953910093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the rendering or capturing is successfully stopped; returns a negative value otherwise. 

**See also:**

[Start](audiocontrol.md#a80ddae13819bb1eb348ad4b57597e930) 

