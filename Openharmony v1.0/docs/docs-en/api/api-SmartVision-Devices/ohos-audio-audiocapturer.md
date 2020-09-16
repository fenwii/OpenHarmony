# OHOS::Audio::AudioCapturer<a name="EN-US_TOPIC_0000001054718137"></a>

## **Overview**<a name="section1640871111093532"></a>

**Related Modules:**

[MultiMedia\_AudioCapturer](multimedia_audiocapturer.md)

**Description:**

Provides functions for applications to implement audio capturing. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2010061002093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table390100090093532"></a>
<table><thead align="left"><tr id="row1594023007093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1088320394093532"><a name="p1088320394093532"></a><a name="p1088320394093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1649320134093532"><a name="p1649320134093532"></a><a name="p1649320134093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1451840568093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856972126093532"><a name="p1856972126093532"></a><a name="p1856972126093532"></a><a href="multimedia_audiocapturer.md#gaf603a793bb5e97f000b11f57fa944ce1">GetFrameCount</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1355784710093532"><a name="p1355784710093532"></a><a name="p1355784710093532"></a>uint64_t </p>
<p id="p287061157093532"><a name="p287061157093532"></a><a name="p287061157093532"></a>Obtains the number of frames required in the current condition, in bytes per sample. </p>
</td>
</tr>
<tr id="row435500575093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p126025003093532"><a name="p126025003093532"></a><a name="p126025003093532"></a><a href="multimedia_audiocapturer.md#gae2cf055c840ece71e22cb64c98c68a19">SetCapturerInfo</a> (const <a href="ohos-audio-audiocapturerinfo.md">AudioCapturerInfo</a> info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1465033936093532"><a name="p1465033936093532"></a><a name="p1465033936093532"></a>int32_t </p>
<p id="p248690569093532"><a name="p248690569093532"></a><a name="p248690569093532"></a>Sets audio capture parameters. </p>
</td>
</tr>
<tr id="row2019071026093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111654477093532"><a name="p111654477093532"></a><a name="p111654477093532"></a><a href="multimedia_audiocapturer.md#ga3921932035bfa99f7e7d8d0241344fca">GetCapturerInfo</a> (<a href="ohos-audio-audiocapturerinfo.md">AudioCapturerInfo</a> &amp;info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p781843846093532"><a name="p781843846093532"></a><a name="p781843846093532"></a>int32_t </p>
<p id="p508304369093532"><a name="p508304369093532"></a><a name="p508304369093532"></a>Obtains audio capture parameters. </p>
</td>
</tr>
<tr id="row1171447850093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p613031383093532"><a name="p613031383093532"></a><a name="p613031383093532"></a><a href="multimedia_audiocapturer.md#gac3391374f9a180d84aa5bd19236743a1">Start</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756624617093532"><a name="p756624617093532"></a><a name="p756624617093532"></a>bool </p>
<p id="p1531710869093532"><a name="p1531710869093532"></a><a name="p1531710869093532"></a>Starts audio recording. </p>
</td>
</tr>
<tr id="row966355974093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1746537899093532"><a name="p1746537899093532"></a><a name="p1746537899093532"></a><a href="multimedia_audiocapturer.md#ga75bccf0f21f7d9adc5e580f40abfc7d2">Read</a> (uint8_t *buffer, size_t userSize, bool isBlockingRead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594324914093532"><a name="p594324914093532"></a><a name="p594324914093532"></a>int32_t </p>
<p id="p915257357093532"><a name="p915257357093532"></a><a name="p915257357093532"></a>Reads audio data. </p>
</td>
</tr>
<tr id="row331783573093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p45328072093532"><a name="p45328072093532"></a><a name="p45328072093532"></a><a href="multimedia_audiocapturer.md#gaf022f9b98b1776799e86b689f7544a5e">GetStatus</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890526844093532"><a name="p1890526844093532"></a><a name="p1890526844093532"></a><a href="multimedia_audiocapturer.md#ga3d8d6798a2346e57e241d16da673d508">State</a> </p>
<p id="p415683920093532"><a name="p415683920093532"></a><a name="p415683920093532"></a>Obtains the audio capture state. </p>
</td>
</tr>
<tr id="row2063312818093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493778380093532"><a name="p1493778380093532"></a><a name="p1493778380093532"></a><a href="multimedia_audiocapturer.md#gae24a95aeba747852373ef408bb9bab12">GetAudioTime</a> (<a href="ohos-audio-timestamp.md">Timestamp</a> &amp;timestamp, <a href="multimedia_audiocapturer.md#gacdafb362a7da91799fa96163bca2a619">Timestamp::Timebase</a> base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974217739093532"><a name="p1974217739093532"></a><a name="p1974217739093532"></a>bool </p>
<p id="p1518237424093532"><a name="p1518237424093532"></a><a name="p1518237424093532"></a>Obtains the timestamp. </p>
</td>
</tr>
<tr id="row1246851032093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697776535093532"><a name="p697776535093532"></a><a name="p697776535093532"></a><a href="multimedia_audiocapturer.md#ga498a8a4d0a2c09418944eab7728bdc7b">Stop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81767798093532"><a name="p81767798093532"></a><a name="p81767798093532"></a>bool </p>
<p id="p1633089292093532"><a name="p1633089292093532"></a><a name="p1633089292093532"></a>Stops audio recording. </p>
</td>
</tr>
<tr id="row1376430365093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1999831239093532"><a name="p1999831239093532"></a><a name="p1999831239093532"></a><a href="multimedia_audiocapturer.md#gad68b60d6ca82d096cbfa0f4205f2ae9e">Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1782303644093532"><a name="p1782303644093532"></a><a name="p1782303644093532"></a>bool </p>
<p id="p1204076104093532"><a name="p1204076104093532"></a><a name="p1204076104093532"></a>Releases a local <strong id="b1377757873093532"><a name="b1377757873093532"></a><a name="b1377757873093532"></a><a href="ohos-audio-audiocapturer.md">AudioCapturer</a></strong> object. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table488239525093532"></a>
<table><thead align="left"><tr id="row1168708634093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1503500001093532"><a name="p1503500001093532"></a><a name="p1503500001093532"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2019443720093532"><a name="p2019443720093532"></a><a name="p2019443720093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1717388323093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785451538093532"><a name="p785451538093532"></a><a name="p785451538093532"></a><a href="multimedia_audiocapturer.md#gac3f12dec86f94438758ba1a6ff6ed7da">GetMinFrameCount</a> (int32_t sampleRate, int32_t channelCount, <a href="multimedia_mediacommon.md#gaa4ea6f314644ed287e0704be26c768b7">AudioCodecFormat</a> audioFormat, size_t &amp;frameCount)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106275006093532"><a name="p1106275006093532"></a><a name="p1106275006093532"></a>static bool </p>
<p id="p26217740093532"><a name="p26217740093532"></a><a name="p26217740093532"></a>Obtains the minimum number of frames required in a specified condition, in bytes per sample. </p>
</td>
</tr>
</tbody>
</table>

