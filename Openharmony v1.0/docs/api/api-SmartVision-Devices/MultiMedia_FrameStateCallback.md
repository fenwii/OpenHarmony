# MultiMedia\_FrameStateCallback<a name="ZH-CN_TOPIC_0000001055078093"></a>

## **Overview**<a name="section2046834183084827"></a>

Provides callbacks for frame state changes, in which you can implement operations to response to the changes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1831333501084827"></a>

## Files<a name="files"></a>

<a name="table1040951573084827"></a>
<table><thead align="left"><tr id="row896848536084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p240668431084827"><a name="p240668431084827"></a><a name="p240668431084827"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p58639810084827"><a name="p58639810084827"></a><a name="p58639810084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1128766948084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1866332840084827"><a name="p1866332840084827"></a><a name="p1866332840084827"></a><a href="camera_kit-h.md">camera_kit.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1846064823084827"><a name="p1846064823084827"></a><a name="p1846064823084827"></a>Declares functions in the <strong id="b688211481084827"><a name="b688211481084827"></a><a name="b688211481084827"></a>CameraKit</strong> class. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1924439737084827"></a>
<table><thead align="left"><tr id="row2115939018084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p842971279084827"><a name="p842971279084827"></a><a name="p842971279084827"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1849716536084827"><a name="p1849716536084827"></a><a name="p1849716536084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1058974826084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p288468808084827"><a name="p288468808084827"></a><a name="p288468808084827"></a><a href="OHOS-Media-FrameStateCallback.md">OHOS::Media::FrameStateCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005237177084827"><a name="p2005237177084827"></a><a name="p2005237177084827"></a>Provides functions to listen for frame states and response to the state changes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table12054418084827"></a>
<table><thead align="left"><tr id="row1142451324084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p277909438084827"><a name="p277909438084827"></a><a name="p277909438084827"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p212247278084827"><a name="p212247278084827"></a><a name="p212247278084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2027795754084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p551971445084827"><a name="p551971445084827"></a><a name="p551971445084827"></a><a href="MultiMedia_FrameStateCallback.md#gab2557f65a2744911b66361a895450d67">OHOS::Media::FrameStateCallback::FrameStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105247551084827"><a name="p105247551084827"></a><a name="p105247551084827"></a>&nbsp;</p>
<p id="p2097068793084827"><a name="p2097068793084827"></a><a name="p2097068793084827"></a>A constructor used to create a <strong id="b977980007084827"><a name="b977980007084827"></a><a name="b977980007084827"></a><a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row1836263861084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1718040287084827"><a name="p1718040287084827"></a><a name="p1718040287084827"></a><a href="MultiMedia_FrameStateCallback.md#gad9ee33e328b523316313b79979b93abb">OHOS::Media::FrameStateCallback::~FrameStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p104659010084827"><a name="p104659010084827"></a><a name="p104659010084827"></a>&nbsp;</p>
<p id="p1594079193084827"><a name="p1594079193084827"></a><a name="p1594079193084827"></a>A destructor used to delete the <strong id="b256911568084827"><a name="b256911568084827"></a><a name="b256911568084827"></a><a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row1503464953084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1699295248084827"><a name="p1699295248084827"></a><a name="p1699295248084827"></a><a href="MultiMedia_FrameStateCallback.md#gaad7c0bd2d27255a8b63d0f5fb75f3b1e">OHOS::Media::FrameStateCallback::OnFrameFinished</a> (<a href="OHOS-Media-Camera.md">Camera</a> &amp;camera, <a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1967267656084827"><a name="p1967267656084827"></a><a name="p1967267656084827"></a>virtual void&nbsp;</p>
<p id="p860467529084827"><a name="p860467529084827"></a><a name="p860467529084827"></a>Called when the frame capture is finished. </p>
</td>
</tr>
<tr id="row1659002539084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206946399084827"><a name="p206946399084827"></a><a name="p206946399084827"></a><a href="MultiMedia_FrameStateCallback.md#ga8692c0a7433e0a98b6a6e364081c3b6a">OHOS::Media::FrameStateCallback::OnFrameError</a> (<a href="OHOS-Media-Camera.md">Camera</a> &amp;camera, <a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig, int32_t errorCode, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1781113597084827"><a name="p1781113597084827"></a><a name="p1781113597084827"></a>virtual void&nbsp;</p>
<p id="p2122017245084827"><a name="p2122017245084827"></a><a name="p2122017245084827"></a>Called when the frame capture fails. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1573313800084827"></a>

## **Function Documentation**<a name="section707433427084827"></a>

## FrameStateCallback\(\)<a name="gab2557f65a2744911b66361a895450d67"></a>

```
OHOS::Media::FrameStateCallback::FrameStateCallback ()
```

 **Description:**

A constructor used to create a  **[FrameStateCallback](OHOS-Media-FrameStateCallback.md)**  instance. 

## OnFrameError\(\)<a name="ga8692c0a7433e0a98b6a6e364081c3b6a"></a>

```
virtual void OHOS::Media::FrameStateCallback::OnFrameError ([Camera](OHOS-Media-Camera.md) & camera, [FrameConfig](OHOS-Media-FrameConfig.md) & frameConfig, int32_t errorCode, FrameResult & frameResult )
```

 **Description:**

Called when the frame capture fails. 

**Parameters:**

<a name="table975786160084827"></a>
<table><thead align="left"><tr id="row387030947084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1971180708084827"><a name="p1971180708084827"></a><a name="p1971180708084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p170538246084827"><a name="p170538246084827"></a><a name="p170538246084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row830284243084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">camera</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the camera. </td>
</tr>
<tr id="row1917641691084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameConfig</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frame configuration. </td>
</tr>
<tr id="row1158203102084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error code. </td>
</tr>
<tr id="row961736205084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameResult</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the capture results. </td>
</tr>
</tbody>
</table>

## OnFrameFinished\(\)<a name="gaad7c0bd2d27255a8b63d0f5fb75f3b1e"></a>

```
virtual void OHOS::Media::FrameStateCallback::OnFrameFinished ([Camera](OHOS-Media-Camera.md) & camera, [FrameConfig](OHOS-Media-FrameConfig.md) & frameConfig, FrameResult & frameResult )
```

 **Description:**

Called when the frame capture is finished. 

**Parameters:**

<a name="table449638316084827"></a>
<table><thead align="left"><tr id="row153019766084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1713938246084827"><a name="p1713938246084827"></a><a name="p1713938246084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1839403364084827"><a name="p1839403364084827"></a><a name="p1839403364084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1793905757084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">camera</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the camera. </td>
</tr>
<tr id="row426342815084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameConfig</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frame configuration. </td>
</tr>
<tr id="row1182583855084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameResult</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the capture results. </td>
</tr>
</tbody>
</table>

## \~FrameStateCallback\(\)<a name="gad9ee33e328b523316313b79979b93abb"></a>

```
OHOS::Media::FrameStateCallback::~FrameStateCallback ()
```

 **Description:**

A destructor used to delete the  **[FrameStateCallback](OHOS-Media-FrameStateCallback.md)**  instance. 

