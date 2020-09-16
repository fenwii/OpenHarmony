# AudioAdapter<a name="EN-US_TOPIC_0000001054879522"></a>

## **Overview**<a name="section1018976419093529"></a>

**Related Modules:**

[Audio](audio.md)

**Description:**

Provides audio adapter capabilities, including initializing ports, creating rendering and capturing tasks, and obtaining the port capability set. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1265400870093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1418668503093529"></a>
<table><thead align="left"><tr id="row1588744881093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2091697081093529"><a name="p2091697081093529"></a><a name="p2091697081093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p120274640093529"><a name="p120274640093529"></a><a name="p120274640093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row248311549093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1232248440093529"><a name="p1232248440093529"></a><a name="p1232248440093529"></a><a href="audioadapter.md#a3c46c9291d4c08d489454ffd78d4a1ee">InitAllPorts</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p598107548093529"><a name="p598107548093529"></a><a name="p598107548093529"></a>int32_t(* </p>
<p id="p1979261033093529"><a name="p1979261033093529"></a><a name="p1979261033093529"></a>Initializes all ports of an audio adapter. </p>
</td>
</tr>
<tr id="row1578919531093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2095483610093529"><a name="p2095483610093529"></a><a name="p2095483610093529"></a><a href="audioadapter.md#a284ea2ad18ebac562ca7283652e61b50">CreateRender</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, const struct <a href="audiodevicedescriptor.md">AudioDeviceDescriptor</a> *desc, const struct <a href="audiosampleattributes.md">AudioSampleAttributes</a> *attrs, struct <a href="audiorender.md">AudioRender</a> **render)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1321298553093529"><a name="p1321298553093529"></a><a name="p1321298553093529"></a>int32_t(* </p>
<p id="p2051413093529"><a name="p2051413093529"></a><a name="p2051413093529"></a>Creates an <strong id="b1241774420093529"><a name="b1241774420093529"></a><a name="b1241774420093529"></a><a href="audiorender.md">AudioRender</a></strong> object. </p>
</td>
</tr>
<tr id="row1930427928093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1979069192093529"><a name="p1979069192093529"></a><a name="p1979069192093529"></a><a href="audioadapter.md#a070a8d60f88134c58c4439d4419af913">DestroyRender</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, struct <a href="audiorender.md">AudioRender</a> *render)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p433030640093529"><a name="p433030640093529"></a><a name="p433030640093529"></a>int32_t(* </p>
<p id="p1511403336093529"><a name="p1511403336093529"></a><a name="p1511403336093529"></a>Destroys an <strong id="b1769596322093529"><a name="b1769596322093529"></a><a name="b1769596322093529"></a><a href="audiorender.md">AudioRender</a></strong> object. </p>
</td>
</tr>
<tr id="row394017211093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1141353875093529"><a name="p1141353875093529"></a><a name="p1141353875093529"></a><a href="audioadapter.md#a8a46358cdad8e0a9d15ac079713535f2">CreateCapture</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, const struct <a href="audiodevicedescriptor.md">AudioDeviceDescriptor</a> *desc, const struct <a href="audiosampleattributes.md">AudioSampleAttributes</a> *attrs, struct <a href="audiocapture.md">AudioCapture</a> **capture)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p702542483093529"><a name="p702542483093529"></a><a name="p702542483093529"></a>int32_t(* </p>
<p id="p283582026093529"><a name="p283582026093529"></a><a name="p283582026093529"></a>Creates an <strong id="b2097703679093529"><a name="b2097703679093529"></a><a name="b2097703679093529"></a><a href="audiocapture.md">AudioCapture</a></strong> object. </p>
</td>
</tr>
<tr id="row1131785240093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p17211529093529"><a name="p17211529093529"></a><a name="p17211529093529"></a><a href="audioadapter.md#a1175a27c5273dab1acf8f8f3c4967637">DestroyCapture</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, struct <a href="audiocapture.md">AudioCapture</a> *capture)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2030831733093529"><a name="p2030831733093529"></a><a name="p2030831733093529"></a>int32_t(* </p>
<p id="p2047373094093529"><a name="p2047373094093529"></a><a name="p2047373094093529"></a>Destroys an <strong id="b1605525228093529"><a name="b1605525228093529"></a><a name="b1605525228093529"></a><a href="audiocapture.md">AudioCapture</a></strong> object. </p>
</td>
</tr>
<tr id="row1923185202093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p168289033093529"><a name="p168289033093529"></a><a name="p168289033093529"></a><a href="audioadapter.md#a525ec7f3f3bb9975790e27f75145d0f6">GetPortCapability</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, const struct <a href="audioport.md">AudioPort</a> *port, struct <a href="audioportcapability.md">AudioPortCapability</a> *capability)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025521960093529"><a name="p2025521960093529"></a><a name="p2025521960093529"></a>int32_t(* </p>
<p id="p2137140893093529"><a name="p2137140893093529"></a><a name="p2137140893093529"></a>Obtains the capability set of the port driver for the audio adapter. </p>
</td>
</tr>
<tr id="row5611995093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207872433093529"><a name="p1207872433093529"></a><a name="p1207872433093529"></a><a href="audioadapter.md#ac4e77085cdcc853de832a2b16b8dc69a">SetPassthroughMode</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, const struct <a href="audioport.md">AudioPort</a> *port, enum <a href="audio.md#ga186d2d4f9a2ecacb80cd2cce2bd26f0e">AudioPortPassthroughMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701476356093529"><a name="p1701476356093529"></a><a name="p1701476356093529"></a>int32_t(* </p>
<p id="p1891670679093529"><a name="p1891670679093529"></a><a name="p1891670679093529"></a>Sets the passthrough data transmission mode of the audio port driver. </p>
</td>
</tr>
<tr id="row708431657093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1105861462093529"><a name="p1105861462093529"></a><a name="p1105861462093529"></a><a href="audioadapter.md#ad4c41f3193c5ec3da254f33e24241ea6">GetPassthroughMode</a> )(struct <a href="audioadapter.md">AudioAdapter</a> *adapter, const struct <a href="audioport.md">AudioPort</a> *port, enum <a href="audio.md#ga186d2d4f9a2ecacb80cd2cce2bd26f0e">AudioPortPassthroughMode</a> *mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p984756588093529"><a name="p984756588093529"></a><a name="p984756588093529"></a>int32_t(* </p>
<p id="p635110041093529"><a name="p635110041093529"></a><a name="p635110041093529"></a>Obtains the passthrough data transmission mode of the audio port driver. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section629025505093529"></a>

## **Field Documentation**<a name="section1487695221093529"></a>

## CreateCapture<a name="a8a46358cdad8e0a9d15ac079713535f2"></a>

```
int32_t(* AudioAdapter::CreateCapture) (struct [AudioAdapter](audioadapter.md) *adapter, const struct [AudioDeviceDescriptor](audiodevicedescriptor.md) *desc, const struct [AudioSampleAttributes](audiosampleattributes.md) *attrs, struct [AudioCapture](audiocapture.md) **capture)
```

 **Description:**

Creates an  **[AudioCapture](audiocapture.md)**  object. 

**Parameters:**

<a name="table1123555756093529"></a>
<table><thead align="left"><tr id="row741826260093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p53065450093529"><a name="p53065450093529"></a><a name="p53065450093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1121781333093529"><a name="p1121781333093529"></a><a name="p1121781333093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row595104207093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row1820488407093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">desc</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the descriptor of the audio adapter to start. </td>
</tr>
<tr id="row152565446093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio sampling attributes to open. </td>
</tr>
<tr id="row1563208241093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">capture</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the <strong id="b141499044093529"><a name="b141499044093529"></a><a name="b141499044093529"></a><a href="audiocapture.md">AudioCapture</a></strong> object. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the  **[AudioCapture](audiocapture.md)**  object is created successfully; returns a negative value otherwise. 

**See also:**

[GetPortCapability](audioadapter.md#a525ec7f3f3bb9975790e27f75145d0f6) 

## CreateRender<a name="a284ea2ad18ebac562ca7283652e61b50"></a>

```
int32_t(* AudioAdapter::CreateRender) (struct [AudioAdapter](audioadapter.md) *adapter, const struct [AudioDeviceDescriptor](audiodevicedescriptor.md) *desc, const struct [AudioSampleAttributes](audiosampleattributes.md) *attrs, struct [AudioRender](audiorender.md) **render)
```

 **Description:**

Creates an  **[AudioRender](audiorender.md)**  object. 

**Parameters:**

<a name="table452064968093529"></a>
<table><thead align="left"><tr id="row1990641944093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1884553925093529"><a name="p1884553925093529"></a><a name="p1884553925093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1170544726093529"><a name="p1170544726093529"></a><a name="p1170544726093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row577617420093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row1647166663093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">desc</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the descriptor of the audio adapter to start. </td>
</tr>
<tr id="row813188173093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio sampling attributes to open. </td>
</tr>
<tr id="row1846563500093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the <strong id="b1347951882093529"><a name="b1347951882093529"></a><a name="b1347951882093529"></a><a href="audiorender.md">AudioRender</a></strong> object. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the  **[AudioRender](audiorender.md)**  object is created successfully; returns a negative value otherwise. 

**See also:**

[GetPortCapability](audioadapter.md#a525ec7f3f3bb9975790e27f75145d0f6) 

## DestroyCapture<a name="a1175a27c5273dab1acf8f8f3c4967637"></a>

```
int32_t(* AudioAdapter::DestroyCapture) (struct [AudioAdapter](audioadapter.md) *adapter, struct [AudioCapture](audiocapture.md) *capture)
```

 **Description:**

Destroys an  **[AudioCapture](audiocapture.md)**  object. 

**Parameters:**

<a name="table1415829245093529"></a>
<table><thead align="left"><tr id="row147817294093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1914011374093529"><a name="p1914011374093529"></a><a name="p1914011374093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p603528269093529"><a name="p603528269093529"></a><a name="p603528269093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row134151341093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row1538219665093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">capture</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b861511608093529"><a name="b861511608093529"></a><a name="b861511608093529"></a><a href="audiocapture.md">AudioCapture</a></strong> object to operate. </td>
</tr>
</tbody>
</table>

**Attention:**

Do not destroy the object during audio capturing.

**Returns:**

Returns  **0**  if the  **[AudioCapture](audiocapture.md)**  object is destroyed; returns a negative value otherwise. 

**See also:**

[CreateCapture](audioadapter.md#a8a46358cdad8e0a9d15ac079713535f2) 

## DestroyRender<a name="a070a8d60f88134c58c4439d4419af913"></a>

```
int32_t(* AudioAdapter::DestroyRender) (struct [AudioAdapter](audioadapter.md) *adapter, struct [AudioRender](audiorender.md) *render)
```

 **Description:**

Destroys an  **[AudioRender](audiorender.md)**  object. 

**Parameters:**

<a name="table1979905813093529"></a>
<table><thead align="left"><tr id="row363358699093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p343241280093529"><a name="p343241280093529"></a><a name="p343241280093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p677888803093529"><a name="p677888803093529"></a><a name="p677888803093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1339057211093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row551651422093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">render</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1252699254093529"><a name="b1252699254093529"></a><a name="b1252699254093529"></a><a href="audiorender.md">AudioRender</a></strong> object to operate. </td>
</tr>
</tbody>
</table>

**Attention:**

Do not destroy the object during audio rendering.

**Returns:**

Returns  **0**  if the  **[AudioRender](audiorender.md)**  object is destroyed; returns a negative value otherwise. 

**See also:**

[CreateRender](audioadapter.md#a284ea2ad18ebac562ca7283652e61b50) 

## GetPassthroughMode<a name="ad4c41f3193c5ec3da254f33e24241ea6"></a>

```
int32_t(* AudioAdapter::GetPassthroughMode) (struct [AudioAdapter](audioadapter.md) *adapter, const struct [AudioPort](audioport.md) *port, enum [AudioPortPassthroughMode](audio.md#ga186d2d4f9a2ecacb80cd2cce2bd26f0e) *mode)
```

 **Description:**

Obtains the passthrough data transmission mode of the audio port driver. 

**Parameters:**

<a name="table1874711416093529"></a>
<table><thead align="left"><tr id="row1839187508093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1167318499093529"><a name="p1167318499093529"></a><a name="p1167318499093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p511000365093529"><a name="p511000365093529"></a><a name="p511000365093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row955125389093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row806029126093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">port</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the port. </td>
</tr>
<tr id="row1123463413093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the passthrough transmission mode to obtain. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the mode is successfully obtained; returns a negative value otherwise. 

**See also:**

[SetPassthroughMode](audioadapter.md#ac4e77085cdcc853de832a2b16b8dc69a) 

## GetPortCapability<a name="a525ec7f3f3bb9975790e27f75145d0f6"></a>

```
int32_t(* AudioAdapter::GetPortCapability) (struct [AudioAdapter](audioadapter.md) *adapter, const struct [AudioPort](audioport.md) *port, struct [AudioPortCapability](audioportcapability.md) *capability)
```

 **Description:**

Obtains the capability set of the port driver for the audio adapter. 

**Parameters:**

<a name="table549604390093529"></a>
<table><thead align="left"><tr id="row1848349352093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1063966956093529"><a name="p1063966956093529"></a><a name="p1063966956093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p290167071093529"><a name="p290167071093529"></a><a name="p290167071093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row690529570093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row600527139093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">port</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the port. </td>
</tr>
<tr id="row1577303219093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">capability</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the capability set to obtain. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the capability set is successfully obtained; returns a negative value otherwise. 



## InitAllPorts<a name="a3c46c9291d4c08d489454ffd78d4a1ee"></a>

```
int32_t(* AudioAdapter::InitAllPorts) (struct [AudioAdapter](audioadapter.md) *adapter)
```

 **Description:**

Initializes all ports of an audio adapter. 

Call this function before calling other driver functions to check whether the initialization is complete. If the initialization is not complete, wait for a while \(for example, 100 ms\) and perform the check again until the port initialization is complete.

**Parameters:**

<a name="table143952381093529"></a>
<table><thead align="left"><tr id="row303632622093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p720824060093529"><a name="p720824060093529"></a><a name="p720824060093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p182933896093529"><a name="p182933896093529"></a><a name="p182933896093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1792937114093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the initialization is successful; returns a negative value otherwise. 



## SetPassthroughMode<a name="ac4e77085cdcc853de832a2b16b8dc69a"></a>

```
int32_t(* AudioAdapter::SetPassthroughMode) (struct [AudioAdapter](audioadapter.md) *adapter, const struct [AudioPort](audioport.md) *port, enum [AudioPortPassthroughMode](audio.md#ga186d2d4f9a2ecacb80cd2cce2bd26f0e) mode)
```

 **Description:**

Sets the passthrough data transmission mode of the audio port driver. 

**Parameters:**

<a name="table1133342490093529"></a>
<table><thead align="left"><tr id="row1057469914093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1166340731093529"><a name="p1166340731093529"></a><a name="p1166340731093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1137241494093529"><a name="p1137241494093529"></a><a name="p1137241494093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2107807824093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter to operate. </td>
</tr>
<tr id="row1337795731093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">port</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the port. </td>
</tr>
<tr id="row2069723204093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the passthrough transmission mode to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative value otherwise. 

**See also:**

[GetPassthroughMode](audioadapter.md#ad4c41f3193c5ec3da254f33e24241ea6) 

