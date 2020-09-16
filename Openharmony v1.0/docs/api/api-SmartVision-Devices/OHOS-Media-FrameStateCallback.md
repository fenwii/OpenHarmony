# OHOS::Media::FrameStateCallback<a name="ZH-CN_TOPIC_0000001055078153"></a>

## **Overview**<a name="section359024275084838"></a>

**Related Modules:**

[MultiMedia\_FrameStateCallback](MultiMedia_FrameStateCallback.md)

**Description:**

Provides functions to listen for frame states and response to the state changes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1253066797084838"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1572855582084838"></a>
<table><thead align="left"><tr id="row1108071138084838"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p5531768084838"><a name="p5531768084838"></a><a name="p5531768084838"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1078724048084838"><a name="p1078724048084838"></a><a name="p1078724048084838"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2113409666084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079613740084838"><a name="p2079613740084838"></a><a name="p2079613740084838"></a><a href="MultiMedia_FrameStateCallback.md#gab2557f65a2744911b66361a895450d67">FrameStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895394265084838"><a name="p1895394265084838"></a><a name="p1895394265084838"></a>&nbsp;</p>
<p id="p1620024328084838"><a name="p1620024328084838"></a><a name="p1620024328084838"></a>A constructor used to create a <strong id="b866105272084838"><a name="b866105272084838"></a><a name="b866105272084838"></a><a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row22040401084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p16429269084838"><a name="p16429269084838"></a><a name="p16429269084838"></a><a href="MultiMedia_FrameStateCallback.md#gad9ee33e328b523316313b79979b93abb">~FrameStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653222973084838"><a name="p1653222973084838"></a><a name="p1653222973084838"></a>&nbsp;</p>
<p id="p1670568140084838"><a name="p1670568140084838"></a><a name="p1670568140084838"></a>A destructor used to delete the <strong id="b1045684107084838"><a name="b1045684107084838"></a><a name="b1045684107084838"></a><a href="OHOS-Media-FrameStateCallback.md">FrameStateCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row701545083084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1397111661084838"><a name="p1397111661084838"></a><a name="p1397111661084838"></a><a href="MultiMedia_FrameStateCallback.md#gaad7c0bd2d27255a8b63d0f5fb75f3b1e">OnFrameFinished</a> (<a href="OHOS-Media-Camera.md">Camera</a> &amp;camera, <a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871168481084838"><a name="p1871168481084838"></a><a name="p1871168481084838"></a>virtual void&nbsp;</p>
<p id="p1012567487084838"><a name="p1012567487084838"></a><a name="p1012567487084838"></a>Called when the frame capture is finished. </p>
</td>
</tr>
<tr id="row899287386084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838089224084838"><a name="p1838089224084838"></a><a name="p1838089224084838"></a><a href="MultiMedia_FrameStateCallback.md#ga8692c0a7433e0a98b6a6e364081c3b6a">OnFrameError</a> (<a href="OHOS-Media-Camera.md">Camera</a> &amp;camera, <a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig, int32_t errorCode, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p827064277084838"><a name="p827064277084838"></a><a name="p827064277084838"></a>virtual void&nbsp;</p>
<p id="p1080535213084838"><a name="p1080535213084838"></a><a name="p1080535213084838"></a>Called when the frame capture fails. </p>
</td>
</tr>
</tbody>
</table>

