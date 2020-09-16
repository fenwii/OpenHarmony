# OHOS::Audio::AudioCapturerInfo<a name="EN-US_TOPIC_0000001054598171"></a>

## **Overview**<a name="section1357251035093532"></a>

**Related Modules:**

[MultiMedia\_AudioCapturer](multimedia_audiocapturer.md)

**Description:**

Defines information about audio capture parameters, including the input source, audio codec format,sampling rate \(Hz\), number of audio channels, bit rate, and bit width. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section202618120093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1081591331093532"></a>
<table><thead align="left"><tr id="row1376939736093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1640721124093532"><a name="p1640721124093532"></a><a name="p1640721124093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1466845846093532"><a name="p1466845846093532"></a><a name="p1466845846093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row46781726093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p234967354093532"><a name="p234967354093532"></a><a name="p234967354093532"></a><a href="multimedia_audiocapturer.md#ga9c14165a8197521b8a539bd5408f66ed">inputSource</a> = <a href="multimedia_mediacommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda732604b3a24d137429e2b83b31849bce">AUDIO_MIC</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487811371093532"><a name="p1487811371093532"></a><a name="p1487811371093532"></a><a href="multimedia_mediacommon.md#gadc3158e093b995ca7b9b6aa32388ccdd">AudioSourceType</a> </p>
</td>
</tr>
<tr id="row1424769328093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p756132610093532"><a name="p756132610093532"></a><a name="p756132610093532"></a><a href="multimedia_audiocapturer.md#ga6a222ecc5112fb2925879dba686c12a3">audioFormat</a> = <a href="multimedia_mediacommon.md#ggaa4ea6f314644ed287e0704be26c768b7a4c4c5829b054bc468274700c56d65546">AUDIO_DEFAULT</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p302039369093532"><a name="p302039369093532"></a><a name="p302039369093532"></a><a href="multimedia_mediacommon.md#gaa4ea6f314644ed287e0704be26c768b7">AudioCodecFormat</a> </p>
</td>
</tr>
<tr id="row2020962536093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464519825093532"><a name="p1464519825093532"></a><a name="p1464519825093532"></a><a href="multimedia_audiocapturer.md#gab623e99855bc46fe9d3dbfacb67e419a">sampleRate</a> = 0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1944932835093532"><a name="p1944932835093532"></a><a name="p1944932835093532"></a>int32_t </p>
</td>
</tr>
<tr id="row932371580093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301637055093532"><a name="p301637055093532"></a><a name="p301637055093532"></a><a href="multimedia_audiocapturer.md#ga3219851b0a3e355a8519c9262f879e47">channelCount</a> = 0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309814103093532"><a name="p309814103093532"></a><a name="p309814103093532"></a>int32_t </p>
</td>
</tr>
<tr id="row1924962343093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1059789777093532"><a name="p1059789777093532"></a><a name="p1059789777093532"></a><a href="multimedia_audiocapturer.md#gace7d68d68754fc267117003f7fc76522">bitRate</a> = 0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478833880093532"><a name="p478833880093532"></a><a name="p478833880093532"></a>int32_t </p>
</td>
</tr>
<tr id="row848294108093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237635488093532"><a name="p1237635488093532"></a><a name="p1237635488093532"></a><a href="multimedia_audiocapturer.md#gaaa038f040e203e553aba28e80f26f733">streamType</a> = <a href="multimedia_mediacommon.md#ggae7077e4211e48131ae544adb20fc494aa431e273affaa22e18ec5a2a548b70e90">TYPE_MEDIA</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783640231093532"><a name="p783640231093532"></a><a name="p783640231093532"></a><a href="multimedia_mediacommon.md#gae7077e4211e48131ae544adb20fc494a">AudioStreamType</a> </p>
</td>
</tr>
<tr id="row25058526093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1968513177093532"><a name="p1968513177093532"></a><a name="p1968513177093532"></a><a href="multimedia_audiocapturer.md#ga110704c5058747a6180c250b0a77d685">bitWidth</a> = <a href="multimedia_mediacommon.md#ggae3e35ee2a2222a667fdebbc5b793ca7ca036f0b45813f96cb6b0f90de1722a780">BIT_WIDTH_16</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554558601093532"><a name="p554558601093532"></a><a name="p554558601093532"></a><a href="multimedia_mediacommon.md#gae3e35ee2a2222a667fdebbc5b793ca7c">AudioBitWidth</a> </p>
</td>
</tr>
</tbody>
</table>

