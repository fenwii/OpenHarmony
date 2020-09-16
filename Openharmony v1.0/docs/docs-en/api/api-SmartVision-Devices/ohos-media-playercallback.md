# OHOS::Media::PlayerCallback<a name="EN-US_TOPIC_0000001055678104"></a>

## **Overview**<a name="section722392915093532"></a>

**Related Modules:**

[MultiMedia\_Player](multimedia_player.md)

**Description:**

Provides listeners for events and exception notifications that occur during media playback. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1801377501093532"></a>

## Public Types<a name="pub-types"></a>

<a name="table1218188110093532"></a>
<table><thead align="left"><tr id="row500347804093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1786025334093532"><a name="p1786025334093532"></a><a name="p1786025334093532"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1720627417093532"><a name="p1720627417093532"></a><a name="p1720627417093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row276824304093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1365524983093532"><a name="p1365524983093532"></a><a name="p1365524983093532"></a><a href="multimedia_player.md#ga7dac9dac65cbbea7e411adcf2c314ac5">PlayerInfoType</a> : int32_t { <a href="multimedia_player.md#gga7dac9dac65cbbea7e411adcf2c314ac5ab5ccacbb568a9b3ce5fedc0ced4e683d">PLAYER_INFO_RENDER_START</a> = 0 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1369753489093532"></a>
<table><thead align="left"><tr id="row130099687093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2118539192093532"><a name="p2118539192093532"></a><a name="p2118539192093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1213591399093532"><a name="p1213591399093532"></a><a name="p1213591399093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row239784395093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040733274093532"><a name="p2040733274093532"></a><a name="p2040733274093532"></a><a href="multimedia_player.md#ga3b56f618340bf9a5590e6142b2311302">OnPlaybackComplete</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507267509093532"><a name="p1507267509093532"></a><a name="p1507267509093532"></a>virtual void </p>
<p id="p1517570560093532"><a name="p1517570560093532"></a><a name="p1517570560093532"></a>Called when the playback is complete. </p>
</td>
</tr>
<tr id="row153489363093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1763778335093532"><a name="p1763778335093532"></a><a name="p1763778335093532"></a><a href="multimedia_player.md#ga3d0fdad57045f5e049b56de031d3e0fb">OnError</a> (int32_t errorType, int32_t errorCode)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177252684093532"><a name="p177252684093532"></a><a name="p177252684093532"></a>virtual void </p>
<p id="p308871580093532"><a name="p308871580093532"></a><a name="p308871580093532"></a>Called when a playback error occurs. </p>
</td>
</tr>
<tr id="row1411731242093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1704948724093532"><a name="p1704948724093532"></a><a name="p1704948724093532"></a><a href="multimedia_player.md#gad2d3466c8a17ee4d622b87fa6a31b2bb">OnInfo</a> (int type, int extra)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531502406093532"><a name="p531502406093532"></a><a name="p531502406093532"></a>virtual void </p>
<p id="p2060300984093532"><a name="p2060300984093532"></a><a name="p2060300984093532"></a>Called when playback information is received. </p>
</td>
</tr>
<tr id="row263893761093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894753082093532"><a name="p894753082093532"></a><a name="p894753082093532"></a><a href="multimedia_player.md#gac5b641f93621d90e616d18adaa016e8a">OnVideoSizeChanged</a> (int width, int height)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698228856093532"><a name="p1698228856093532"></a><a name="p1698228856093532"></a>virtual void </p>
<p id="p1175271374093532"><a name="p1175271374093532"></a><a name="p1175271374093532"></a>Called when the video image size changes. </p>
</td>
</tr>
<tr id="row909802243093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1142946952093532"><a name="p1142946952093532"></a><a name="p1142946952093532"></a><a href="multimedia_player.md#ga765c499e47dfaad5e557197e964eaca3">OnRewindToComplete</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p300021697093532"><a name="p300021697093532"></a><a name="p300021697093532"></a>virtual void </p>
<p id="p1058234065093532"><a name="p1058234065093532"></a><a name="p1058234065093532"></a>Called when the rewind is complete. </p>
</td>
</tr>
</tbody>
</table>

