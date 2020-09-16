# AudioRender<a name="ZH-CN_TOPIC_0000001054918145"></a>

## **Overview**<a name="section2000426298093529"></a>

**Related Modules:**

[Audio](Audio.md)

**Description:**

Provides capabilities for audio rendering, including controlling the rendering, setting audio attributes, scenes, and volume, obtaining hardware latency, and rendering audio frames. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1695985147093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1459979959093529"></a>
<table><thead align="left"><tr id="row627848022093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2138670895093529"><a name="p2138670895093529"></a><a name="p2138670895093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p321138032093529"><a name="p321138032093529"></a><a name="p321138032093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2007957727093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503626553093529"><a name="p1503626553093529"></a><a name="p1503626553093529"></a><em id="a954721a6d70c6cc96d8a772740b5749b"><a name="a954721a6d70c6cc96d8a772740b5749b"></a><a name="a954721a6d70c6cc96d8a772740b5749b"></a></em>control </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090945373093529"><a name="p2090945373093529"></a><a name="p2090945373093529"></a><strong id="a954721a6d70c6cc96d8a772740b5749b_1"><a name="a954721a6d70c6cc96d8a772740b5749b_1"></a><a name="a954721a6d70c6cc96d8a772740b5749b_1"></a></strong> struct <a href="AudioControl.md">AudioControl</a>&nbsp;</p>
<p id="p153211130093529"><a name="p153211130093529"></a><a name="p153211130093529"></a>Defines the audio control. For details, see <a href="AudioControl.md">AudioControl</a>. </p>
</td>
</tr>
<tr id="row1841984408093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1433989772093529"><a name="p1433989772093529"></a><a name="p1433989772093529"></a><em id="a6933f5dbf34758cea050e2e5d25e69e6"><a name="a6933f5dbf34758cea050e2e5d25e69e6"></a><a name="a6933f5dbf34758cea050e2e5d25e69e6"></a></em>attr </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963155598093529"><a name="p963155598093529"></a><a name="p963155598093529"></a><strong id="a6933f5dbf34758cea050e2e5d25e69e6_1"><a name="a6933f5dbf34758cea050e2e5d25e69e6_1"></a><a name="a6933f5dbf34758cea050e2e5d25e69e6_1"></a></strong> struct <a href="AudioAttribute.md">AudioAttribute</a>&nbsp;</p>
<p id="p1042286076093529"><a name="p1042286076093529"></a><a name="p1042286076093529"></a>Defines the audio attribute. For details, see <a href="AudioAttribute.md">AudioAttribute</a>. </p>
</td>
</tr>
<tr id="row1745890986093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859519262093529"><a name="p1859519262093529"></a><a name="p1859519262093529"></a><em id="adcbcb3e0a5c11e507bbf2f9a8809b099"><a name="adcbcb3e0a5c11e507bbf2f9a8809b099"></a><a name="adcbcb3e0a5c11e507bbf2f9a8809b099"></a></em>scene </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105830543093529"><a name="p2105830543093529"></a><a name="p2105830543093529"></a><strong id="adcbcb3e0a5c11e507bbf2f9a8809b099_1"><a name="adcbcb3e0a5c11e507bbf2f9a8809b099_1"></a><a name="adcbcb3e0a5c11e507bbf2f9a8809b099_1"></a></strong> struct <a href="AudioScene.md">AudioScene</a>&nbsp;</p>
<p id="p1863771863093529"><a name="p1863771863093529"></a><a name="p1863771863093529"></a>Defines the audio scene. For details, see <a href="AudioScene.md">AudioScene</a>. </p>
</td>
</tr>
<tr id="row451243574093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p561827211093529"><a name="p561827211093529"></a><a name="p561827211093529"></a><em id="aff73e1461efbc8b133418f0571f4b3a8"><a name="aff73e1461efbc8b133418f0571f4b3a8"></a><a name="aff73e1461efbc8b133418f0571f4b3a8"></a></em>volume </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089467282093529"><a name="p2089467282093529"></a><a name="p2089467282093529"></a><strong id="aff73e1461efbc8b133418f0571f4b3a8_1"><a name="aff73e1461efbc8b133418f0571f4b3a8_1"></a><a name="aff73e1461efbc8b133418f0571f4b3a8_1"></a></strong> struct <a href="AudioVolume.md">AudioVolume</a>&nbsp;</p>
<p id="p916508016093529"><a name="p916508016093529"></a><a name="p916508016093529"></a>Defines audio volume. For details, see <a href="AudioVolume.md">AudioVolume</a>. </p>
</td>
</tr>
<tr id="row2074215241093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797017029093529"><a name="p1797017029093529"></a><a name="p1797017029093529"></a><a href="AudioRender.md#a56dff6bbe1c5ac8361b2e3238ab09563">GetLatency</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, uint32_t *ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313839283093529"><a name="p1313839283093529"></a><a name="p1313839283093529"></a>int32_t(*&nbsp;</p>
<p id="p390046843093529"><a name="p390046843093529"></a><a name="p390046843093529"></a>Obtains the estimated latency of the audio device driver. </p>
</td>
</tr>
<tr id="row276977799093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p398448113093529"><a name="p398448113093529"></a><a name="p398448113093529"></a><a href="AudioRender.md#a463cab04d0805a5c7b3ba5884c468246">RenderFrame</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, const void *frame, uint64_t requestBytes, uint64_t *replyBytes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p939637104093529"><a name="p939637104093529"></a><a name="p939637104093529"></a>int32_t(*&nbsp;</p>
<p id="p1456099619093529"><a name="p1456099619093529"></a><a name="p1456099619093529"></a>Writes a frame of output data (downlink data) into the audio driver for rendering. </p>
</td>
</tr>
<tr id="row584537330093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p822109862093529"><a name="p822109862093529"></a><a name="p822109862093529"></a><a href="AudioRender.md#a24072bec0e2cd75727b57ec3e14f7ccb">GetRenderPosition</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, uint64_t *frames, struct <a href="AudioTimeStamp.md">AudioTimeStamp</a> *<a href="zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447022631093529"><a name="p447022631093529"></a><a name="p447022631093529"></a>int32_t(*&nbsp;</p>
<p id="p1964350547093529"><a name="p1964350547093529"></a><a name="p1964350547093529"></a>Obtains the last number of output audio frames. </p>
</td>
</tr>
<tr id="row227992507093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740040602093529"><a name="p740040602093529"></a><a name="p740040602093529"></a><a href="AudioRender.md#a5589427ae5a4ba6a8d2a19dd8eddbcd8">SetRenderSpeed</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, float speed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p521982719093529"><a name="p521982719093529"></a><a name="p521982719093529"></a>int32_t(*&nbsp;</p>
<p id="p1282932925093529"><a name="p1282932925093529"></a><a name="p1282932925093529"></a>Sets the audio rendering speed. </p>
</td>
</tr>
<tr id="row1060396809093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1194427754093529"><a name="p1194427754093529"></a><a name="p1194427754093529"></a><a href="AudioRender.md#af0a19dacb293d3fbe600902b93af1ee9">GetRenderSpeed</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, float *speed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2102555257093529"><a name="p2102555257093529"></a><a name="p2102555257093529"></a>int32_t(*&nbsp;</p>
<p id="p1352540305093529"><a name="p1352540305093529"></a><a name="p1352540305093529"></a>Obtains the current audio rendering speed. </p>
</td>
</tr>
<tr id="row173790015093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2103236435093529"><a name="p2103236435093529"></a><a name="p2103236435093529"></a><a href="AudioRender.md#ae5aad5b26ccdd65ba501620851c5ecec">SetChannelMode</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, enum <a href="Audio.md#ga78aab1fafb9657451804e42b42897123">AudioChannelMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p753755891093529"><a name="p753755891093529"></a><a name="p753755891093529"></a>int32_t(*&nbsp;</p>
<p id="p565312761093529"><a name="p565312761093529"></a><a name="p565312761093529"></a>Sets the channel mode for audio rendering. </p>
</td>
</tr>
<tr id="row1500017285093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p840139834093529"><a name="p840139834093529"></a><a name="p840139834093529"></a><a href="AudioRender.md#aad3d5e4104167620eacb2ba23edce50e">GetChannelMode</a> )(struct <a href="AudioRender.md">AudioRender</a> *render, enum <a href="Audio.md#ga78aab1fafb9657451804e42b42897123">AudioChannelMode</a> *mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459292041093529"><a name="p459292041093529"></a><a name="p459292041093529"></a>int32_t(*&nbsp;</p>
<p id="p1248647415093529"><a name="p1248647415093529"></a><a name="p1248647415093529"></a>Obtains the current channel mode for audio rendering. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2093810079093529"></a>

## **Field Documentation**<a name="section485337278093529"></a>

## GetChannelMode<a name="aad3d5e4104167620eacb2ba23edce50e"></a>

```
int32_t(* AudioRender::GetChannelMode) (struct [AudioRender](AudioRender.md) *render, enum [AudioChannelMode](Audio.md#ga78aab1fafb9657451804e42b42897123) *mode)
```

 **Description:**

Obtains the current channel mode for audio rendering. 

**Parameters:**

<a name="table152255529093529"></a>
<table><thead align="left"><tr id="row454010964093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1901105570093529"><a name="p1901105570093529"></a><a name="p1901105570093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2011764168093529"><a name="p2011764168093529"></a><a name="p2011764168093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1051070001093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b2025394423093529"><a name="b2025394423093529"></a><a name="b2025394423093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row2111023463093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the channel mode to obtain. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the mode is successfully obtained; returns a negative value otherwise. 

**See also:**

[SetChannelMode](AudioRender.md#ae5aad5b26ccdd65ba501620851c5ecec) 

## GetLatency<a name="a56dff6bbe1c5ac8361b2e3238ab09563"></a>

```
int32_t(* AudioRender::GetLatency) (struct [AudioRender](AudioRender.md) *render, uint32_t *ms)
```

 **Description:**

Obtains the estimated latency of the audio device driver. 

**Parameters:**

<a name="table1322704572093529"></a>
<table><thead align="left"><tr id="row714317588093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1771266111093529"><a name="p1771266111093529"></a><a name="p1771266111093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1207712711093529"><a name="p1207712711093529"></a><a name="p1207712711093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1772715070093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1081126803093529"><a name="b1081126803093529"></a><a name="b1081126803093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row612026893093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ms</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the latency (in milliseconds) to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the latency is obtained; returns a negative value otherwise. 



## GetRenderPosition<a name="a24072bec0e2cd75727b57ec3e14f7ccb"></a>

```
int32_t(* AudioRender::GetRenderPosition) (struct [AudioRender](AudioRender.md) *render, uint64_t *frames, struct [AudioTimeStamp](AudioTimeStamp.md) *[time](zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c))
```

 **Description:**

Obtains the last number of output audio frames. 

**Parameters:**

<a name="table1610198850093529"></a>
<table><thead align="left"><tr id="row158685199093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1469853976093529"><a name="p1469853976093529"></a><a name="p1469853976093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p691855517093529"><a name="p691855517093529"></a><a name="p691855517093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row140163604093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1566484032093529"><a name="b1566484032093529"></a><a name="b1566484032093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row1094248506093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frames</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the last number of output audio frames. </td>
</tr>
<tr id="row908324837093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timestamp associated with the frame. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the last number is obtained; returns a negative value otherwise. 

**See also:**

[RenderFrame](AudioRender.md#a463cab04d0805a5c7b3ba5884c468246) 

## GetRenderSpeed<a name="af0a19dacb293d3fbe600902b93af1ee9"></a>

```
int32_t(* AudioRender::GetRenderSpeed) (struct [AudioRender](AudioRender.md) *render, float *speed)
```

 **Description:**

Obtains the current audio rendering speed. 

**Parameters:**

<a name="table1026647496093529"></a>
<table><thead align="left"><tr id="row1716199609093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1867866308093529"><a name="p1867866308093529"></a><a name="p1867866308093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1526727964093529"><a name="p1526727964093529"></a><a name="p1526727964093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row762573241093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b829284074093529"><a name="b829284074093529"></a><a name="b829284074093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row320766646093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">speed</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the current rendering speed to obtain. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the speed is successfully obtained; returns a negative value otherwise. 

**See also:**

[SetRenderSpeed](AudioRender.md#a5589427ae5a4ba6a8d2a19dd8eddbcd8) 

## RenderFrame<a name="a463cab04d0805a5c7b3ba5884c468246"></a>

```
int32_t(* AudioRender::RenderFrame) (struct [AudioRender](AudioRender.md) *render, const void *frame, uint64_t requestBytes, uint64_t *replyBytes)
```

 **Description:**

Writes a frame of output data \(downlink data\) into the audio driver for rendering. 

**Parameters:**

<a name="table2017355772093529"></a>
<table><thead align="left"><tr id="row1535336451093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1695575131093529"><a name="p1695575131093529"></a><a name="p1695575131093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1144008438093529"><a name="p1144008438093529"></a><a name="p1144008438093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2106997272093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1275277871093529"><a name="b1275277871093529"></a><a name="b1275277871093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row867632539093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frame</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the frame to write. </td>
</tr>
<tr id="row1887586639093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">requestBytes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the frame, in bytes. </td>
</tr>
<tr id="row1789967755093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">replyBytes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the actual length (in bytes) of the audio data to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the data is written successfully; returns a negative value otherwise. 



## SetChannelMode<a name="ae5aad5b26ccdd65ba501620851c5ecec"></a>

```
int32_t(* AudioRender::SetChannelMode) (struct [AudioRender](AudioRender.md) *render, enum [AudioChannelMode](Audio.md#ga78aab1fafb9657451804e42b42897123) mode)
```

 **Description:**

Sets the channel mode for audio rendering. 

**Parameters:**

<a name="table146828453093529"></a>
<table><thead align="left"><tr id="row463189493093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1457072568093529"><a name="p1457072568093529"></a><a name="p1457072568093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2073183254093529"><a name="p2073183254093529"></a><a name="p2073183254093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row863003140093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1597534075093529"><a name="b1597534075093529"></a><a name="b1597534075093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row1898880801093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the channel mode to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetChannelMode](AudioRender.md#aad3d5e4104167620eacb2ba23edce50e) 

## SetRenderSpeed<a name="a5589427ae5a4ba6a8d2a19dd8eddbcd8"></a>

```
int32_t(* AudioRender::SetRenderSpeed) (struct [AudioRender](AudioRender.md) *render, float speed)
```

 **Description:**

Sets the audio rendering speed. 

**Parameters:**

<a name="table1408214066093529"></a>
<table><thead align="left"><tr id="row1603531149093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p305349587093529"><a name="p305349587093529"></a><a name="p305349587093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1109444655093529"><a name="p1109444655093529"></a><a name="p1109444655093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1984273724093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b998391012093529"><a name="b998391012093529"></a><a name="b998391012093529"></a><a href="AudioRender.md">AudioRender</a></strong> object to operate. </td>
</tr>
<tr id="row102845991093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">speed</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the rendering speed to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetRenderSpeed](AudioRender.md#af0a19dacb293d3fbe600902b93af1ee9) 

