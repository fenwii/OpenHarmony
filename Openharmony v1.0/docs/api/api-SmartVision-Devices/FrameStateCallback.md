# FrameStateCallback<a name="ZH-CN_TOPIC_0000001054094213"></a>

## **Overview**<a name="section1601651146113033"></a>

**Related Modules:**

[MultiMedia\_FrameStateCallback](MultiMedia_FrameStateCallback.md)

**Description:**

Declares functions in the  **[FrameStateCallback](FrameStateCallback.md)**  class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1159498339113033"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameStateCallback.md#gab2557f65a2744911b66361a895450d67">FrameStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>constructed function; </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameStateCallback.md#gad9ee33e328b523316313b79979b93abb">~FrameStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>destructor function; </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameStateCallback.md#gaad7c0bd2d27255a8b63d0f5fb75f3b1e">OnFrameFinished</a> (<a href="Camera.md">Camera</a> &amp;camera, <a href="FrameConfig.md">FrameConfig</a> &amp;frameConfig, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the frame capture is finished. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameStateCallback.md#ga8692c0a7433e0a98b6a6e364081c3b6a">OnFrameError</a> (<a href="Camera.md">Camera</a> &amp;camera, <a href="FrameConfig.md">FrameConfig</a> &amp;frameConfig, int32_t errorCode, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the frame capture fails. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameStateCallback.md#gafda08e2b91429d15b2a851b9ca819dc3">OnFrameProgressed</a> (<a href="Camera.md">Camera</a> &amp;camera, <a href="FrameConfig.md">FrameConfig</a> &amp;frameConfig, FrameResult &amp;frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the frame capture is in process. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameStateCallback.md#ga6d34abc510e5068798914ca656b06dcb">OnFrameStarted</a> (<a href="Camera.md">Camera</a> &amp;camera, <a href="FrameConfig.md">FrameConfig</a> &amp;frameConfig, int32_t frameNumber, int32_t timestamp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the frame capture starts. </p>
</td>
</tr>
</tbody>
</table>

