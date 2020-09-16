# MultiMedia\_AudioCapturer<a name="ZH-CN_TOPIC_0000001054718079"></a>

## **Overview**<a name="section651371981093523"></a>

Declares APIs in the  **AudioCapturer**  class for audio capture. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section903723904093523"></a>

## Files<a name="files"></a>

<a name="table466229125093523"></a>
<table><thead align="left"><tr id="row281774126093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p760854080093523"><a name="p760854080093523"></a><a name="p760854080093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p345087334093523"><a name="p345087334093523"></a><a name="p345087334093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row199056235093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832030572093523"><a name="p832030572093523"></a><a name="p832030572093523"></a><a href="audio_capturer-h.md">audio_capturer.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474215149093523"><a name="p1474215149093523"></a><a name="p1474215149093523"></a>Provides the <strong id="b245188437093523"><a name="b245188437093523"></a><a name="b245188437093523"></a>AudioCapturer</strong> class to implement operations related to audio capture. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1260205601093523"></a>
<table><thead align="left"><tr id="row1716835199093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p654037235093523"><a name="p654037235093523"></a><a name="p654037235093523"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1985363718093523"><a name="p1985363718093523"></a><a name="p1985363718093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row830400461093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1752177379093523"><a name="p1752177379093523"></a><a name="p1752177379093523"></a><a href="OHOS-Audio-AudioCapturerInfo.md">OHOS::Audio::AudioCapturerInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105439788093523"><a name="p1105439788093523"></a><a name="p1105439788093523"></a>Defines information about audio capture parameters, including the input source, audio codec format,sampling rate (Hz), number of audio channels, bit rate, and bit width. </p>
</td>
</tr>
<tr id="row827083412093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p605063776093523"><a name="p605063776093523"></a><a name="p605063776093523"></a><a href="OHOS-Audio-Timestamp.md">OHOS::Audio::Timestamp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1267127982093523"><a name="p1267127982093523"></a><a name="p1267127982093523"></a>Represents timestamp information, including the frame position information and high-resolution time source. </p>
</td>
</tr>
<tr id="row1206130843093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040341407093523"><a name="p2040341407093523"></a><a name="p2040341407093523"></a><a href="OHOS-Audio-AudioCapturer.md">OHOS::Audio::AudioCapturer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443405516093523"><a name="p443405516093523"></a><a name="p443405516093523"></a>Provides functions for applications to implement audio capturing. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table195611891093523"></a>
<table><thead align="left"><tr id="row626598362093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1398233995093523"><a name="p1398233995093523"></a><a name="p1398233995093523"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p627791589093523"><a name="p627791589093523"></a><a name="p627791589093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2097356607093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p16627530093523"><a name="p16627530093523"></a><a name="p16627530093523"></a><a href="MultiMedia_AudioCapturer.md#gacdafb362a7da91799fa96163bca2a619">OHOS::Audio::Timestamp::Timebase</a> : int32_t { <a href="MultiMedia_AudioCapturer.md#ggacdafb362a7da91799fa96163bca2a619a109ce01d0775b5372b9b2cc517630d39">OHOS::Audio::Timestamp::Timebase::MONOTONIC</a> = 0, <a href="MultiMedia_AudioCapturer.md#ggacdafb362a7da91799fa96163bca2a619aa0bb084304634f8cf8c9d41c5b87c0c3">OHOS::Audio::Timestamp::Timebase::BOOTTIME</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108117676093523"><a name="p1108117676093523"></a><a name="p1108117676093523"></a>Enumerates the time base of this <strong id="b1779833383093523"><a name="b1779833383093523"></a><a name="b1779833383093523"></a>Timestamp</strong>. Different timing methods are supported. </p>
</td>
</tr>
<tr id="row318899774093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p978432195093523"><a name="p978432195093523"></a><a name="p978432195093523"></a><a href="MultiMedia_AudioCapturer.md#ga3d8d6798a2346e57e241d16da673d508">OHOS::Audio::State</a> : uint32_t { <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508a368f9c124fa478d643e6b3884bd4931c">OHOS::Audio::PREPPARED</a>, <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508a6d83cfbb144468bcd7f1d0609ba1a401">OHOS::Audio::RECORDING</a>, <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508abc10d40a09b83e61c72dd68daa457399">OHOS::Audio::STOPPED</a>, <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508ab061f3539998a6bcec9b4c11357b5ff2">OHOS::Audio::RELEASED</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1384403572093523"><a name="p1384403572093523"></a><a name="p1384403572093523"></a>Enumerates the recording states of the current device. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table526365676093523"></a>
<table><thead align="left"><tr id="row832474254093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p741521712093523"><a name="p741521712093523"></a><a name="p741521712093523"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p767002807093523"><a name="p767002807093523"></a><a name="p767002807093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row697549128093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105092068093523"><a name="p105092068093523"></a><a name="p105092068093523"></a><a href="MultiMedia_AudioCapturer.md#gac3f12dec86f94438758ba1a6ff6ed7da">OHOS::Audio::AudioCapturer::GetMinFrameCount</a> (int32_t sampleRate, int32_t channelCount, <a href="MultiMedia_MediaCommon.md#gaa4ea6f314644ed287e0704be26c768b7">AudioCodecFormat</a> audioFormat, size_t &amp;frameCount)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099112656093523"><a name="p1099112656093523"></a><a name="p1099112656093523"></a>static bool&nbsp;</p>
<p id="p587438504093523"><a name="p587438504093523"></a><a name="p587438504093523"></a>Obtains the minimum number of frames required in a specified condition, in bytes per sample. </p>
</td>
</tr>
<tr id="row1849680075093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p185550020093523"><a name="p185550020093523"></a><a name="p185550020093523"></a><a href="MultiMedia_AudioCapturer.md#gaf603a793bb5e97f000b11f57fa944ce1">OHOS::Audio::AudioCapturer::GetFrameCount</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p281355757093523"><a name="p281355757093523"></a><a name="p281355757093523"></a>uint64_t&nbsp;</p>
<p id="p1488176989093523"><a name="p1488176989093523"></a><a name="p1488176989093523"></a>Obtains the number of frames required in the current condition, in bytes per sample. </p>
</td>
</tr>
<tr id="row1380145864093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410400896093523"><a name="p410400896093523"></a><a name="p410400896093523"></a><a href="MultiMedia_AudioCapturer.md#gae2cf055c840ece71e22cb64c98c68a19">OHOS::Audio::AudioCapturer::SetCapturerInfo</a> (const <a href="OHOS-Audio-AudioCapturerInfo.md">AudioCapturerInfo</a> info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453853380093523"><a name="p1453853380093523"></a><a name="p1453853380093523"></a>int32_t&nbsp;</p>
<p id="p1930998009093523"><a name="p1930998009093523"></a><a name="p1930998009093523"></a>Sets audio capture parameters. </p>
</td>
</tr>
<tr id="row2570519093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p318887357093523"><a name="p318887357093523"></a><a name="p318887357093523"></a><a href="MultiMedia_AudioCapturer.md#ga3921932035bfa99f7e7d8d0241344fca">OHOS::Audio::AudioCapturer::GetCapturerInfo</a> (<a href="OHOS-Audio-AudioCapturerInfo.md">AudioCapturerInfo</a> &amp;info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p373789560093523"><a name="p373789560093523"></a><a name="p373789560093523"></a>int32_t&nbsp;</p>
<p id="p929522756093523"><a name="p929522756093523"></a><a name="p929522756093523"></a>Obtains audio capture parameters. </p>
</td>
</tr>
<tr id="row2122078084093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p233934175093523"><a name="p233934175093523"></a><a name="p233934175093523"></a><a href="MultiMedia_AudioCapturer.md#gac3391374f9a180d84aa5bd19236743a1">OHOS::Audio::AudioCapturer::Start</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423486984093523"><a name="p423486984093523"></a><a name="p423486984093523"></a>bool&nbsp;</p>
<p id="p675042620093523"><a name="p675042620093523"></a><a name="p675042620093523"></a>Starts audio recording. </p>
</td>
</tr>
<tr id="row246760640093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1078306546093523"><a name="p1078306546093523"></a><a name="p1078306546093523"></a><a href="MultiMedia_AudioCapturer.md#ga75bccf0f21f7d9adc5e580f40abfc7d2">OHOS::Audio::AudioCapturer::Read</a> (uint8_t *buffer, size_t userSize, bool isBlockingRead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779980697093523"><a name="p779980697093523"></a><a name="p779980697093523"></a>int32_t&nbsp;</p>
<p id="p528029247093523"><a name="p528029247093523"></a><a name="p528029247093523"></a>Reads audio data. </p>
</td>
</tr>
<tr id="row399772575093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1706221505093523"><a name="p1706221505093523"></a><a name="p1706221505093523"></a><a href="MultiMedia_AudioCapturer.md#gaf022f9b98b1776799e86b689f7544a5e">OHOS::Audio::AudioCapturer::GetStatus</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881850132093523"><a name="p881850132093523"></a><a name="p881850132093523"></a><a href="MultiMedia_AudioCapturer.md#ga3d8d6798a2346e57e241d16da673d508">State</a>&nbsp;</p>
<p id="p464111639093523"><a name="p464111639093523"></a><a name="p464111639093523"></a>Obtains the audio capture state. </p>
</td>
</tr>
<tr id="row528923932093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p922758720093523"><a name="p922758720093523"></a><a name="p922758720093523"></a><a href="MultiMedia_AudioCapturer.md#gae24a95aeba747852373ef408bb9bab12">OHOS::Audio::AudioCapturer::GetAudioTime</a> (<a href="OHOS-Audio-Timestamp.md">Timestamp</a> &amp;timestamp, <a href="MultiMedia_AudioCapturer.md#gacdafb362a7da91799fa96163bca2a619">Timestamp::Timebase</a> base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267444225093523"><a name="p267444225093523"></a><a name="p267444225093523"></a>bool&nbsp;</p>
<p id="p1500676067093523"><a name="p1500676067093523"></a><a name="p1500676067093523"></a>Obtains the timestamp. </p>
</td>
</tr>
<tr id="row1944334400093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025601546093523"><a name="p2025601546093523"></a><a name="p2025601546093523"></a><a href="MultiMedia_AudioCapturer.md#ga498a8a4d0a2c09418944eab7728bdc7b">OHOS::Audio::AudioCapturer::Stop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2383751093523"><a name="p2383751093523"></a><a name="p2383751093523"></a>bool&nbsp;</p>
<p id="p1682546041093523"><a name="p1682546041093523"></a><a name="p1682546041093523"></a>Stops audio recording. </p>
</td>
</tr>
<tr id="row648029978093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p860836606093523"><a name="p860836606093523"></a><a name="p860836606093523"></a><a href="MultiMedia_AudioCapturer.md#gad68b60d6ca82d096cbfa0f4205f2ae9e">OHOS::Audio::AudioCapturer::Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1792460741093523"><a name="p1792460741093523"></a><a name="p1792460741093523"></a>bool&nbsp;</p>
<p id="p1751164000093523"><a name="p1751164000093523"></a><a name="p1751164000093523"></a>Releases a local <strong id="b2035689733093523"><a name="b2035689733093523"></a><a name="b2035689733093523"></a><a href="OHOS-Audio-AudioCapturer.md">AudioCapturer</a></strong> object. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section14781849093523"></a>

## **Enumeration Type Documentation**<a name="section1659123307093523"></a>

## State<a name="ga3d8d6798a2346e57e241d16da673d508"></a>

```
enum [OHOS::Audio::State](MultiMedia_AudioCapturer.md#ga3d8d6798a2346e57e241d16da673d508) : uint32_t
```

 **Description:**

Enumerates the recording states of the current device. 

<a name="table1166285207093523"></a>
<table><thead align="left"><tr id="row1555772384093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2018640151093523"><a name="p2018640151093523"></a><a name="p2018640151093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p266795546093523"><a name="p266795546093523"></a><a name="p266795546093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1783391805093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3d8d6798a2346e57e241d16da673d508a368f9c124fa478d643e6b3884bd4931c"><a name="gga3d8d6798a2346e57e241d16da673d508a368f9c124fa478d643e6b3884bd4931c"></a><a name="gga3d8d6798a2346e57e241d16da673d508a368f9c124fa478d643e6b3884bd4931c"></a></strong>PREPPARED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p831794065093523"><a name="p831794065093523"></a><a name="p831794065093523"></a>Prepared </p>
 </td>
</tr>
<tr id="row396975875093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3d8d6798a2346e57e241d16da673d508a6d83cfbb144468bcd7f1d0609ba1a401"><a name="gga3d8d6798a2346e57e241d16da673d508a6d83cfbb144468bcd7f1d0609ba1a401"></a><a name="gga3d8d6798a2346e57e241d16da673d508a6d83cfbb144468bcd7f1d0609ba1a401"></a></strong>RECORDING&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032019183093523"><a name="p1032019183093523"></a><a name="p1032019183093523"></a>Recording </p>
 </td>
</tr>
<tr id="row1571220907093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3d8d6798a2346e57e241d16da673d508abc10d40a09b83e61c72dd68daa457399"><a name="gga3d8d6798a2346e57e241d16da673d508abc10d40a09b83e61c72dd68daa457399"></a><a name="gga3d8d6798a2346e57e241d16da673d508abc10d40a09b83e61c72dd68daa457399"></a></strong>STOPPED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1762684314093523"><a name="p1762684314093523"></a><a name="p1762684314093523"></a>Stopped </p>
 </td>
</tr>
<tr id="row762332383093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3d8d6798a2346e57e241d16da673d508ab061f3539998a6bcec9b4c11357b5ff2"><a name="gga3d8d6798a2346e57e241d16da673d508ab061f3539998a6bcec9b4c11357b5ff2"></a><a name="gga3d8d6798a2346e57e241d16da673d508ab061f3539998a6bcec9b4c11357b5ff2"></a></strong>RELEASED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088942821093523"><a name="p2088942821093523"></a><a name="p2088942821093523"></a>Released </p>
 </td>
</tr>
</tbody>
</table>

## Timebase<a name="gacdafb362a7da91799fa96163bca2a619"></a>

```
enum [OHOS::Audio::Timestamp::Timebase](MultiMedia_AudioCapturer.md#gacdafb362a7da91799fa96163bca2a619) : int32_t
```

 **Description:**

Enumerates the time base of this  **[Timestamp](OHOS-Audio-Timestamp.md)**. Different timing methods are supported. 

<a name="table1506927937093523"></a>
<table><thead align="left"><tr id="row452738220093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1077304416093523"><a name="p1077304416093523"></a><a name="p1077304416093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p57268637093523"><a name="p57268637093523"></a><a name="p57268637093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row413882644093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacdafb362a7da91799fa96163bca2a619a109ce01d0775b5372b9b2cc517630d39"><a name="ggacdafb362a7da91799fa96163bca2a619a109ce01d0775b5372b9b2cc517630d39"></a><a name="ggacdafb362a7da91799fa96163bca2a619a109ce01d0775b5372b9b2cc517630d39"></a></strong>MONOTONIC&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2043101740093523"><a name="p2043101740093523"></a><a name="p2043101740093523"></a>Monotonically increasing time, excluding the system sleep time </p>
 </td>
</tr>
<tr id="row619950405093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacdafb362a7da91799fa96163bca2a619aa0bb084304634f8cf8c9d41c5b87c0c3"><a name="ggacdafb362a7da91799fa96163bca2a619aa0bb084304634f8cf8c9d41c5b87c0c3"></a><a name="ggacdafb362a7da91799fa96163bca2a619aa0bb084304634f8cf8c9d41c5b87c0c3"></a></strong>BOOTTIME&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672856329093523"><a name="p672856329093523"></a><a name="p672856329093523"></a>Monotonically increasing time, including the system sleep time </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1410231136093523"></a>

## GetAudioTime\(\)<a name="gae24a95aeba747852373ef408bb9bab12"></a>

```
bool OHOS::Audio::AudioCapturer::GetAudioTime ([Timestamp](OHOS-Audio-Timestamp.md) & timestamp, [Timestamp::Timebase](MultiMedia_AudioCapturer.md#gacdafb362a7da91799fa96163bca2a619) base )
```

 **Description:**

Obtains the timestamp. 

**Parameters:**

<a name="table1964744433093523"></a>
<table><thead align="left"><tr id="row59864883093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p275390714093523"><a name="p275390714093523"></a><a name="p275390714093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1323865753093523"><a name="p1323865753093523"></a><a name="p1323865753093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row21396200093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timestamp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a <a href="OHOS-Audio-Timestamp.md">Timestamp</a> instance reference provided by the caller. </td>
</tr>
<tr id="row431460639093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">base</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the time base, which can be <a href="MultiMedia_AudioCapturer.md#ggacdafb362a7da91799fa96163bca2a619aa0bb084304634f8cf8c9d41c5b87c0c3">Timestamp.Timebase.BOOTTIME</a> or <a href="MultiMedia_AudioCapturer.md#ggacdafb362a7da91799fa96163bca2a619a109ce01d0775b5372b9b2cc517630d39">Timestamp.Timebase.MONOTONIC</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the timestamp is successfully obtained; returns  **false**  otherwise. 



## GetCapturerInfo\(\)<a name="ga3921932035bfa99f7e7d8d0241344fca"></a>

```
int32_t OHOS::Audio::AudioCapturer::GetCapturerInfo ([AudioCapturerInfo](OHOS-Audio-AudioCapturerInfo.md) & info)
```

 **Description:**

Obtains audio capture parameters. 

This function can be called after  [SetCapturerInfo](MultiMedia_AudioCapturer.md#gae2cf055c840ece71e22cb64c98c68a19)  is successful.

**Parameters:**

<a name="table387606332093523"></a>
<table><thead align="left"><tr id="row1251500454093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1520900266093523"><a name="p1520900266093523"></a><a name="p1520900266093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1145789336093523"><a name="p1145789336093523"></a><a name="p1145789336093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1230004267093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates information about audio capture parameters. For details, see <a href="OHOS-Audio-AudioCapturerInfo.md">AudioCapturerInfo</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the parameter information is successfully obtained; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## GetFrameCount\(\)<a name="gaf603a793bb5e97f000b11f57fa944ce1"></a>

```
uint64_t OHOS::Audio::AudioCapturer::GetFrameCount ()
```

 **Description:**

Obtains the number of frames required in the current condition, in bytes per sample. 

**Returns:**

Returns the number of frames \(in bytes per sample\) if the operation is successful; returns  **-1**  if an exception occurs. 



## GetMinFrameCount\(\)<a name="gac3f12dec86f94438758ba1a6ff6ed7da"></a>

```
static bool OHOS::Audio::AudioCapturer::GetMinFrameCount (int32_t sampleRate, int32_t channelCount, [AudioCodecFormat](MultiMedia_MediaCommon.md#gaa4ea6f314644ed287e0704be26c768b7) audioFormat, size_t & frameCount )
```

 **Description:**

Obtains the minimum number of frames required in a specified condition, in bytes per sample. 

**Parameters:**

<a name="table1306854905093523"></a>
<table><thead align="left"><tr id="row1818033582093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p185118153093523"><a name="p185118153093523"></a><a name="p185118153093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p678619483093523"><a name="p678619483093523"></a><a name="p678619483093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1016102165093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sampleRate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio sampling rate, in Hz. </td>
</tr>
<tr id="row1302503898093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">channelCount</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of audio recording channels. </td>
</tr>
<tr id="row1233161577093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">audioFormat</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio data format. </td>
</tr>
<tr id="row38715845093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameCount</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the minimum number of frames, in bytes per sample. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the minimum number of frames is successfully obtained; returns  **false**  otherwise. 



## GetStatus\(\)<a name="gaf022f9b98b1776799e86b689f7544a5e"></a>

```
[State](MultiMedia_AudioCapturer.md#ga3d8d6798a2346e57e241d16da673d508) OHOS::Audio::AudioCapturer::GetStatus ()
```

 **Description:**

Obtains the audio capture state. 

**Returns:**

Returns the audio capture state defined in  [State](AbilityKit.md#ga5d74787dedbc4e11c1ab15bf487e61f8). 



## Read\(\)<a name="ga75bccf0f21f7d9adc5e580f40abfc7d2"></a>

```
int32_t OHOS::Audio::AudioCapturer::Read (uint8_t * buffer, size_t userSize, bool isBlockingRead )
```

 **Description:**

Reads audio data. 

**Parameters:**

<a name="table1034615180093523"></a>
<table><thead align="left"><tr id="row1929616111093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p421312409093523"><a name="p421312409093523"></a><a name="p421312409093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p611743463093523"><a name="p611743463093523"></a><a name="p611743463093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1859611739093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer into which the audio data is to be written. </td>
</tr>
<tr id="row1484100718093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">userSize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the buffer into which the audio data is to be written, in bytes. <strong id="b1894212223093523"><a name="b1894212223093523"></a><a name="b1894212223093523"></a>userSize &gt;= frameCount * channelCount * BytesPerSample</strong> must evaluate to <strong id="b1156165006093523"><a name="b1156165006093523"></a><a name="b1156165006093523"></a>true</strong>. You can call <a href="MultiMedia_AudioCapturer.md#gaf603a793bb5e97f000b11f57fa944ce1">GetFrameCount</a> to obtain the <strong id="b2049823216093523"><a name="b2049823216093523"></a><a name="b2049823216093523"></a>frameCount</strong> value. </td>
</tr>
<tr id="row613347253093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">isBlockingRead</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether data reading will be blocked. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the size of the audio data read from the device. The value ranges from  **0**  to  **userSize**. If the reading fails, one of the following error codes is returned:  **ERR\_INVALID\_PARAM**: The input parameter is incorrect.  **ERR\_ILLEGAL\_STATE**: The  **[AudioCapturer](OHOS-Audio-AudioCapturer.md)**  instance is not initialized.  **ERR\_SOURCE\_NOT\_SET**: The state of hardware device instance is abnormal. 



## Release\(\)<a name="gad68b60d6ca82d096cbfa0f4205f2ae9e"></a>

```
bool OHOS::Audio::AudioCapturer::Release ()
```

 **Description:**

Releases a local  **[AudioCapturer](OHOS-Audio-AudioCapturer.md)**  object. 

**Returns:**

Returns  **true**  if the object is successfully released; returns  **false**  otherwise. 



## SetCapturerInfo\(\)<a name="gae2cf055c840ece71e22cb64c98c68a19"></a>

```
int32_t OHOS::Audio::AudioCapturer::SetCapturerInfo (const [AudioCapturerInfo](OHOS-Audio-AudioCapturerInfo.md) info)
```

 **Description:**

Sets audio capture parameters. 

**Parameters:**

<a name="table464011820093523"></a>
<table><thead align="left"><tr id="row540741535093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1435211864093523"><a name="p1435211864093523"></a><a name="p1435211864093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p785800262093523"><a name="p785800262093523"></a><a name="p785800262093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row585017297093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates information about audio capture parameters to set. For details, see <a href="OHOS-Audio-AudioCapturerInfo.md">AudioCapturerInfo</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Start\(\)<a name="gac3391374f9a180d84aa5bd19236743a1"></a>

```
bool OHOS::Audio::AudioCapturer::Start ()
```

 **Description:**

Starts audio recording. 

**Returns:**

Returns  **true**  if the recording is successfully started; returns  **false**  otherwise. 



## Stop\(\)<a name="ga498a8a4d0a2c09418944eab7728bdc7b"></a>

```
bool OHOS::Audio::AudioCapturer::Stop ()
```

 **Description:**

Stops audio recording. 

**Returns:**

Returns  **true**  if the recording is successfully stopped; returns  **false**  otherwise. 



## **Variable Documentation**<a name="section89600772093523"></a>

## audioFormat<a name="ga6a222ecc5112fb2925879dba686c12a3"></a>

```
[AudioCodecFormat](MultiMedia_MediaCommon.md#gaa4ea6f314644ed287e0704be26c768b7) OHOS::Audio::AudioCapturerInfo::audioFormat = [AUDIO_DEFAULT](MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7a4c4c5829b054bc468274700c56d65546)
```

 **Description:**

Audio codec format 

## bitRate<a name="gace7d68d68754fc267117003f7fc76522"></a>

```
int32_t OHOS::Audio::AudioCapturerInfo::bitRate = 0
```

 **Description:**

Bit rate 

## bitWidth<a name="ga110704c5058747a6180c250b0a77d685"></a>

```
[AudioBitWidth](MultiMedia_MediaCommon.md#gae3e35ee2a2222a667fdebbc5b793ca7c) OHOS::Audio::AudioCapturerInfo::bitWidth = [BIT_WIDTH_16](MultiMedia_MediaCommon.md#ggae3e35ee2a2222a667fdebbc5b793ca7ca036f0b45813f96cb6b0f90de1722a780)
```

 **Description:**

Bit width 

## channelCount<a name="ga3219851b0a3e355a8519c9262f879e47"></a>

```
int32_t OHOS::Audio::AudioCapturerInfo::channelCount = 0
```

 **Description:**

Number of audio channels 

## inputSource<a name="ga9c14165a8197521b8a539bd5408f66ed"></a>

```
[AudioSourceType](MultiMedia_MediaCommon.md#gadc3158e093b995ca7b9b6aa32388ccdd) OHOS::Audio::AudioCapturerInfo::inputSource = [AUDIO_MIC](MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda732604b3a24d137429e2b83b31849bce)
```

 **Description:**

Audio source type 

## sampleRate<a name="gab623e99855bc46fe9d3dbfacb67e419a"></a>

```
int32_t OHOS::Audio::AudioCapturerInfo::sampleRate = 0
```

 **Description:**

Sampling rate 

## streamType<a name="gaaa038f040e203e553aba28e80f26f733"></a>

```
[AudioStreamType](MultiMedia_MediaCommon.md#gae7077e4211e48131ae544adb20fc494a) OHOS::Audio::AudioCapturerInfo::streamType = [TYPE_MEDIA](MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa431e273affaa22e18ec5a2a548b70e90)
```

 **Description:**

Audio stream type 

