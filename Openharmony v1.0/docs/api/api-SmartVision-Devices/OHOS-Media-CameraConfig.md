# OHOS::Media::CameraConfig<a name="ZH-CN_TOPIC_0000001055198144"></a>

## **Overview**<a name="section187575610084838"></a>

**Related Modules:**

[MultiMedia\_CameraConfig](MultiMedia_CameraConfig.md)

**Description:**

Provides functions to configure camera parameters. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section614578258084838"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table427267154084838"></a>
<table><thead align="left"><tr id="row289769298084838"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p149880205084838"><a name="p149880205084838"></a><a name="p149880205084838"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1179545513084838"><a name="p1179545513084838"></a><a name="p1179545513084838"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row390608612084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p81273986084838"><a name="p81273986084838"></a><a name="p81273986084838"></a><a href="MultiMedia_CameraConfig.md#ga6730b1ff3808a97fe7095c1cd016d47c">~CameraConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96119399084838"><a name="p96119399084838"></a><a name="p96119399084838"></a>virtual&nbsp;</p>
<p id="p425279200084838"><a name="p425279200084838"></a><a name="p425279200084838"></a>A destructor used to delete the <strong id="b659897525084838"><a name="b659897525084838"></a><a name="b659897525084838"></a><a href="OHOS-Media-CameraAbility.md">CameraAbility</a></strong> instance. </p>
</td>
</tr>
<tr id="row1230189627084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1837959456084838"><a name="p1837959456084838"></a><a name="p1837959456084838"></a><a href="MultiMedia_CameraConfig.md#gaf6d7f82e9439dce13b0213f84a35ab59">SetFrameStateCallback</a> (<a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a> *callback, EventHandler *handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1972921581084838"><a name="p1972921581084838"></a><a name="p1972921581084838"></a>virtual void&nbsp;</p>
<p id="p1612539573084838"><a name="p1612539573084838"></a><a name="p1612539573084838"></a>Sets a frame state callback to responds to state changes. </p>
</td>
</tr>
<tr id="row1884408694084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298176385084838"><a name="p298176385084838"></a><a name="p298176385084838"></a><a href="MultiMedia_CameraConfig.md#ga65d8bb0bd5d996e51e4c6fa12a33931b">GetEventHandler</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p982853494084838"><a name="p982853494084838"></a><a name="p982853494084838"></a>virtual EventHandler *&nbsp;</p>
<p id="p1413526417084838"><a name="p1413526417084838"></a><a name="p1413526417084838"></a>Obtains the <strong id="b1010918611084838"><a name="b1010918611084838"></a><a name="b1010918611084838"></a>EventHandler</strong> object. </p>
</td>
</tr>
<tr id="row760788867084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p957282267084838"><a name="p957282267084838"></a><a name="p957282267084838"></a><a href="MultiMedia_CameraConfig.md#gae4864312836d34b9ad56675ed3e523a1">GetFrameStateCb</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075518973084838"><a name="p1075518973084838"></a><a name="p1075518973084838"></a>virtual <a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a> *&nbsp;</p>
<p id="p141494526084838"><a name="p141494526084838"></a><a name="p141494526084838"></a>Obtains a <strong id="b1190604924084838"><a name="b1190604924084838"></a><a name="b1190604924084838"></a><a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a></strong> object. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table1849377550084838"></a>
<table><thead align="left"><tr id="row2121946189084838"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1808415391084838"><a name="p1808415391084838"></a><a name="p1808415391084838"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p145898099084838"><a name="p145898099084838"></a><a name="p145898099084838"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row970808511084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p630162510084838"><a name="p630162510084838"></a><a name="p630162510084838"></a><a href="MultiMedia_CameraConfig.md#ga26f37610abb783b48d3e94662523fa94">CreateCameraConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477391060084838"><a name="p1477391060084838"></a><a name="p1477391060084838"></a>static <a href="OHOS-Media-CameraConfig.md">CameraConfig</a> *&nbsp;</p>
<p id="p2049619583084838"><a name="p2049619583084838"></a><a name="p2049619583084838"></a>Creates the <strong id="b55597945084838"><a name="b55597945084838"></a><a name="b55597945084838"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> instance of this singleton class to configure and read the required parameters. </p>
</td>
</tr>
</tbody>
</table>

## Protected Member Functions<a name="pro-methods"></a>

<a name="table1306880356084838"></a>
<table><thead align="left"><tr id="row312114822084838"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1293960392084838"><a name="p1293960392084838"></a><a name="p1293960392084838"></a>Protected Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p332266291084838"><a name="p332266291084838"></a><a name="p332266291084838"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1690188343084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1677021607084838"><a name="p1677021607084838"></a><a name="p1677021607084838"></a><a href="MultiMedia_CameraConfig.md#ga6cca70f5dea34d6ede94d0b258c0a350">CameraConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743429245084838"><a name="p1743429245084838"></a><a name="p1743429245084838"></a>&nbsp;</p>
<p id="p1431271929084838"><a name="p1431271929084838"></a><a name="p1431271929084838"></a>A constructor used to create a <strong id="b1979976929084838"><a name="b1979976929084838"></a><a name="b1979976929084838"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> instance. </p>
</td>
</tr>
</tbody>
</table>

