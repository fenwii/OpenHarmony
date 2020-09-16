# media\_info.h<a name="ZH-CN_TOPIC_0000001054479537"></a>

## **Overview**<a name="section1527111774093526"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Declares the  **media\_info**  class and provides various audio, video, and codec types. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1379336588093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1474792470093526"></a>
<table><thead align="left"><tr id="row207189671093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1038546848093526"><a name="p1038546848093526"></a><a name="p1038546848093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p87440933093526"><a name="p87440933093526"></a><a name="p87440933093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row359263745093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p316172890093526"><a name="p316172890093526"></a><a name="p316172890093526"></a><a href="AudioDeviceDesc.md">AudioDeviceDesc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28103282093526"><a name="p28103282093526"></a><a name="p28103282093526"></a>Defines the audio Device Descriptor. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2142241697093526"></a>
<table><thead align="left"><tr id="row1206028194093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p768265632093526"><a name="p768265632093526"></a><a name="p768265632093526"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1848240648093526"><a name="p1848240648093526"></a><a name="p1848240648093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row612826305093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1015004773093526"><a name="p1015004773093526"></a><a name="p1015004773093526"></a><a href="MultiMedia_MediaCommon.md#gadc3158e093b995ca7b9b6aa32388ccdd">AudioSourceType</a> { &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccddad728113cb6300764f0131e28290706c0">AUDIO_SOURCE_INVALID</a> = -1, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda159b69cc6a9b75d6fed0da3e3db9a62f">AUDIO_SOURCE_DEFAULT</a> = 0, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda732604b3a24d137429e2b83b31849bce">AUDIO_MIC</a> = 1, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccddac94b34dbaa3e19d53b34096fbcd64d8d">AUDIO_VOICE_UPLINK</a> = 2, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda076ef2fc169a0b5f640e8433d77d1f45">AUDIO_VOICE_DOWNLINK</a> = 3, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda3d978f472db3ff575a1b4ab84acbc15c">AUDIO_VOICE_CALL</a> = 4, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda0d2b7337a260ae5c32abd843f5d52ec8">AUDIO_CAMCORDER</a> = 5, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda2491fee4b6ca4dce9c05babc3c1168e8">AUDIO_VOICE_RECOGNITION</a> = 6, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda09ce48df53dbaea4ef4273614bdc5445">AUDIO_VOICE_COMMUNICATION</a> = 7, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccddaef3dbfe38c377d77d0e40a9808012981">AUDIO_REMOTE_SUBMIX</a> = 8, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda2fd32b7e954f7988ae41b63167948caf">AUDIO_UNPROCESSED</a> = 9, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda532f7c38a1feb89c8cb3a4e07f0c2cbe">AUDIO_VOICE_PERFORMANCE</a> = 10, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda295b4d6de2ba41d7783fddbf1543e830">AUDIO_ECHO_REFERENCE</a> = 1997, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda5492fbdf785a745195f80020dba4f37e">AUDIO_RADIO_TUNER</a> = 1998, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccdda210886d5f821c08c5a36e71363d330f6">AUDIO_HOTWORD</a> = 1999, <a href="MultiMedia_MediaCommon.md#ggadc3158e093b995ca7b9b6aa32388ccddad0b4097d682e6cc4d7d92e5f0612a831">AUDIO_REMOTE_SUBMIX_EXTEND</a> = 10007 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412858286093526"><a name="p1412858286093526"></a><a name="p1412858286093526"></a>Enumerates audio source types. </p>
</td>
</tr>
<tr id="row568792149093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p122980251093526"><a name="p122980251093526"></a><a name="p122980251093526"></a><a href="MultiMedia_MediaCommon.md#gae7077e4211e48131ae544adb20fc494a">AudioStreamType</a> { &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa80d7bb9558588a28f24aec4c019fdbd6">TYPE_DEFAULT</a> = -1, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa431e273affaa22e18ec5a2a548b70e90">TYPE_MEDIA</a> = 0, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa5bfd254bb72236e9c463aefeb4343194">TYPE_VOICE_COMMUNICATION</a> = 1, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa0ae2b45a2675c159915c1e76f2f2c846">TYPE_SYSTEM</a> = 2, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aafe3e3697e6e9f7880cb90d40e1d4d708">TYPE_RING</a> = 3, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa801a700d4c9f12285930e9eeace6feb4">TYPE_MUSIC</a> = 4, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aae93097f5314613a0eb5465187102bd5f">TYPE_ALARM</a> = 5, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa7f3c9297ca35f503b5f7b6cb36610ef6">TYPE_NOTIFICATION</a> = 6, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aac47f3bf77df994414bd9514f8264e277">TYPE_BLUETOOTH_SCO</a> = 7, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa00376353eb14c2d326026e6a7cdf6674">TYPE_ENFORCED_AUDIBLE</a> = 8, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aad61d97f9466b24094407016ce4231f7b">TYPE_DTMF</a> = 9, <a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa8e6eb63161413e4bbb207dfb29efe95f">TYPE_TTS</a> = 10, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggae7077e4211e48131ae544adb20fc494aa38333aca1beda5f77cc1ce3d0c322262">TYPE_ACCESSIBILITY</a> = 11 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1801310808093526"><a name="p1801310808093526"></a><a name="p1801310808093526"></a>Enumerates audio stream types. </p>
</td>
</tr>
<tr id="row1387382207093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1642583390093526"><a name="p1642583390093526"></a><a name="p1642583390093526"></a><a href="MultiMedia_MediaCommon.md#ga797e6c5e38e23e730eff5bcc41427d7e">VideoCodecFormat</a> { <a href="MultiMedia_MediaCommon.md#gga797e6c5e38e23e730eff5bcc41427d7ea54ef59464d0b6788c6212bb1b5074503">VIDEO_DEFAULT</a> = 0, <a href="MultiMedia_MediaCommon.md#gga797e6c5e38e23e730eff5bcc41427d7eac3f3371ea9f44c4076fec8f0d8f818cf">H264</a> = 2, <a href="MultiMedia_MediaCommon.md#gga797e6c5e38e23e730eff5bcc41427d7eac2489c86e2690559ce3a00a03b15c324">HEVC</a> = 5 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1689123451093526"><a name="p1689123451093526"></a><a name="p1689123451093526"></a>Enumerates video codec formats. </p>
</td>
</tr>
<tr id="row1669022832093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484769561093526"><a name="p484769561093526"></a><a name="p484769561093526"></a><a href="MultiMedia_MediaCommon.md#gaa4ea6f314644ed287e0704be26c768b7">AudioCodecFormat</a> { &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7a4c4c5829b054bc468274700c56d65546">AUDIO_DEFAULT</a> = 0, <a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7a9f7c5945c7d9d679395a7b06652c51ec">AAC_LC</a> = 1, <a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7ac711be17b9264c9f814b11b7fcc3f1b6">AAC_HE_V1</a> = 2, <a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7abf3ac142be84c7ee471a84570745a136">AAC_HE_V2</a> = 3, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7a1ba0b2e0c3a69a989dec92fc6132d8f2">AAC_LD</a> = 4, <a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7a05b8c66394143a26c66268a39115c48a">AAC_ELD</a> = 5, <a href="MultiMedia_MediaCommon.md#ggaa4ea6f314644ed287e0704be26c768b7a5945910833e0d7ff1a9ff73208d9406a">FORMAT_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p862118676093526"><a name="p862118676093526"></a><a name="p862118676093526"></a>Enumerates audio codec formats. </p>
</td>
</tr>
<tr id="row2029883957093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509291216093526"><a name="p1509291216093526"></a><a name="p1509291216093526"></a><a href="MultiMedia_MediaCommon.md#gae3e35ee2a2222a667fdebbc5b793ca7c">AudioBitWidth</a> { <a href="MultiMedia_MediaCommon.md#ggae3e35ee2a2222a667fdebbc5b793ca7cac790b3e4ae89aa667da7dad7e79df6a8">BIT_WIDTH_8</a> = 8, <a href="MultiMedia_MediaCommon.md#ggae3e35ee2a2222a667fdebbc5b793ca7ca036f0b45813f96cb6b0f90de1722a780">BIT_WIDTH_16</a> = 16, <a href="MultiMedia_MediaCommon.md#ggae3e35ee2a2222a667fdebbc5b793ca7ca3d613870d00dad5bc83927eaef3c6ade">BIT_WIDTH_24</a> = 24, <a href="MultiMedia_MediaCommon.md#ggae3e35ee2a2222a667fdebbc5b793ca7cafe508a98e81909dc5985e7edc76104d4">BIT_WIDTH_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p810860874093526"><a name="p810860874093526"></a><a name="p810860874093526"></a>Enumerates audio bit widths. </p>
</td>
</tr>
</tbody>
</table>

