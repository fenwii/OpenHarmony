# AudioScene<a name="ZH-CN_TOPIC_0000001054718117"></a>

## **Overview**<a name="section671646922093529"></a>

**Related Modules:**

[Audio](Audio.md)

**Description:**

Provides scene-related APIs for audio rendering or capturing, including functions to select an audio scene and check whether the configuration of an audio scene is supported. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1895641609093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table690093921093529"></a>
<table><thead align="left"><tr id="row1880598015093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1921960735093529"><a name="p1921960735093529"></a><a name="p1921960735093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1114817607093529"><a name="p1114817607093529"></a><a name="p1114817607093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row550278644093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870730747093529"><a name="p870730747093529"></a><a name="p870730747093529"></a><a href="AudioScene.md#a9b485404b2ec3b8bc2b8d1b73401d45c">CheckSceneCapability</a> )(<a href="Audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, const struct <a href="AudioSceneDescriptor.md">AudioSceneDescriptor</a> *scene, bool *supported)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p715933671093529"><a name="p715933671093529"></a><a name="p715933671093529"></a>int32_t(*&nbsp;</p>
<p id="p1610146790093529"><a name="p1610146790093529"></a><a name="p1610146790093529"></a>Checks whether the configuration of an audio scene is supported. </p>
</td>
</tr>
<tr id="row1693801844093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51217179093529"><a name="p51217179093529"></a><a name="p51217179093529"></a><a href="AudioScene.md#aacdbf3a9f488a7e71f3a5a23c68c0068">SelectScene</a> )(<a href="Audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a> handle, const struct <a href="AudioSceneDescriptor.md">AudioSceneDescriptor</a> *scene)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466310482093529"><a name="p1466310482093529"></a><a name="p1466310482093529"></a>int32_t(*&nbsp;</p>
<p id="p1873388709093529"><a name="p1873388709093529"></a><a name="p1873388709093529"></a>Selects an audio scene. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1200377729093529"></a>

## **Field Documentation**<a name="section1584546291093529"></a>

## CheckSceneCapability<a name="a9b485404b2ec3b8bc2b8d1b73401d45c"></a>

```
int32_t(* AudioScene::CheckSceneCapability) ([AudioHandle](Audio.md#ga18675ddb073465fdeac33a897f675d79) handle, const struct [AudioSceneDescriptor](AudioSceneDescriptor.md) *scene, bool *supported)
```

 **Description:**

Checks whether the configuration of an audio scene is supported. 

**Parameters:**

<a name="table1353674181093529"></a>
<table><thead align="left"><tr id="row1576079188093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2021541950093529"><a name="p2021541950093529"></a><a name="p2021541950093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p699574431093529"><a name="p699574431093529"></a><a name="p699574431093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row127553071093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row1925230772093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">scene</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the descriptor of the audio scene. </td>
</tr>
<tr id="row1165231778093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">supported</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable specifying whether the configuration is supported. Value <strong id="b508710465093529"><a name="b508710465093529"></a><a name="b508710465093529"></a>true</strong> means that the configuration is supported, and <strong id="b1672142105093529"><a name="b1672142105093529"></a><a name="b1672142105093529"></a>false</strong> means the opposite. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the result is obtained; returns a negative value otherwise. 

**See also:**

[SelectScene](AudioScene.md#aacdbf3a9f488a7e71f3a5a23c68c0068) 

## SelectScene<a name="aacdbf3a9f488a7e71f3a5a23c68c0068"></a>

```
int32_t(* AudioScene::SelectScene) ([AudioHandle](Audio.md#ga18675ddb073465fdeac33a897f675d79) handle, const struct [AudioSceneDescriptor](AudioSceneDescriptor.md) *scene)
```

 **Description:**

Selects an audio scene. 

**Parameters:**

<a name="table1279720363093529"></a>
<table><thead align="left"><tr id="row2092905717093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p390589325093529"><a name="p390589325093529"></a><a name="p390589325093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1699284080093529"><a name="p1699284080093529"></a><a name="p1699284080093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row620602691093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio handle. </td>
</tr>
<tr id="row1004770215093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">scene</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the descriptor of the audio scene to select. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the scene is selected successfully; returns a negative value otherwise. 

**See also:**

[CheckSceneCapability](AudioScene.md#a9b485404b2ec3b8bc2b8d1b73401d45c) 

