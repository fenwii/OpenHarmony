# AudioPortCapability<a name="EN-US_TOPIC_0000001055078131"></a>

## **Overview**<a name="section1896667738093529"></a>

**Related Modules:**

[Audio](audio.md)

**Description:**

Defines the audio port capability. 

## **Summary**<a name="section671729351093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table547692045093529"></a>
<table><thead align="left"><tr id="row1558672041093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1475832665093529"><a name="p1475832665093529"></a><a name="p1475832665093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p103905021093529"><a name="p103905021093529"></a><a name="p103905021093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row655718338093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1128380593093529"><a name="p1128380593093529"></a><a name="p1128380593093529"></a><a href="audio.md#ga00860eb6de81efe5b1654b45617fb902">deviceType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49918355093529"><a name="p49918355093529"></a><a name="p49918355093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row806391605093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p724120231093529"><a name="p724120231093529"></a><a name="p724120231093529"></a><a href="audio.md#ga0485197a750c63938602b339a3b9c77f">deviceId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074931927093529"><a name="p1074931927093529"></a><a name="p1074931927093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row512283429093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p165019672093529"><a name="p165019672093529"></a><a name="p165019672093529"></a><a href="audio.md#ga377ecdaf229087a7d17c220a65a7162f">hardwareMode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701831593093529"><a name="p1701831593093529"></a><a name="p1701831593093529"></a>bool </p>
</td>
</tr>
<tr id="row1915027978093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p862015866093529"><a name="p862015866093529"></a><a name="p862015866093529"></a><a href="audio.md#gaca895984cf53ddd8769d33c8298b0c6d">formatNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p701848105093529"><a name="p701848105093529"></a><a name="p701848105093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row135160024093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716229045093529"><a name="p716229045093529"></a><a name="p716229045093529"></a><a href="audio.md#gad01bfa329a21628287ee21df5000e34d">formats</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289887327093529"><a name="p289887327093529"></a><a name="p289887327093529"></a>enum <a href="audio.md#ga98d5d077cca088ddf77314871474fe59">AudioFormat</a> * </p>
</td>
</tr>
<tr id="row107842491093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p714573200093529"><a name="p714573200093529"></a><a name="p714573200093529"></a><a href="audio.md#ga30c8a08e5d939c0e9844d6d9a165c681">sampleRateMasks</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p355510940093529"><a name="p355510940093529"></a><a name="p355510940093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row744677577093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472440651093529"><a name="p1472440651093529"></a><a name="p1472440651093529"></a><a href="audio.md#ga357e90ee8116e04144f57e6f7d3d9efb">channelMasks</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403444554093529"><a name="p403444554093529"></a><a name="p403444554093529"></a>enum <a href="audio.md#ga137eb03027d5947ea294b32f5095b83c">AudioChannelMask</a> </p>
</td>
</tr>
<tr id="row2089742918093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236060804093529"><a name="p236060804093529"></a><a name="p236060804093529"></a><a href="audio.md#ga48253c4fbc171f241bb0494524891bb1">channelCount</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420704643093529"><a name="p1420704643093529"></a><a name="p1420704643093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row1634596460093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044722028093529"><a name="p1044722028093529"></a><a name="p1044722028093529"></a><a href="audio.md#gab784694fd6a60a3d5a3ae404cd6fe6fd">subPortsNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1079182593093529"><a name="p1079182593093529"></a><a name="p1079182593093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row1285135971093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p397777963093529"><a name="p397777963093529"></a><a name="p397777963093529"></a><a href="audio.md#gaccd18b70e7d121169f3df5e53fe055f9">subPorts</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1915068456093529"><a name="p1915068456093529"></a><a name="p1915068456093529"></a>struct <a href="audiosubportcapability.md">AudioSubPortCapability</a> * </p>
</td>
</tr>
</tbody>
</table>

