# OHOS::Media::Recorder<a name="ZH-CN_TOPIC_0000001054598177"></a>

## **Overview**<a name="section1199858132093532"></a>

**Related Modules:**

[MultiMedia\_Recorder](MultiMedia_Recorder.md)

**Description:**

Provides functions for audio and video recording. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1270473123093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table269586618093532"></a>
<table><thead align="left"><tr id="row118862940093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1579431189093532"><a name="p1579431189093532"></a><a name="p1579431189093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2111840923093532"><a name="p2111840923093532"></a><a name="p2111840923093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1204948664093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p548879779093532"><a name="p548879779093532"></a><a name="p548879779093532"></a><a href="MultiMedia_Recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a> (<a href="MultiMedia_Recorder.md#gad252d27f9ce4b6ae0756bfeaa5f34490">VideoSourceType</a> source, int32_t &amp;sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1894157300093532"><a name="p1894157300093532"></a><a name="p1894157300093532"></a>int32_t&nbsp;</p>
<p id="p999408926093532"><a name="p999408926093532"></a><a name="p999408926093532"></a>Sets a video source for recording. </p>
</td>
</tr>
<tr id="row802759980093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758161151093532"><a name="p758161151093532"></a><a name="p758161151093532"></a><a href="MultiMedia_Recorder.md#gad9be6914af57fcf7acb7a5398118c614">SetVideoEncoder</a> (int32_t sourceId, <a href="MultiMedia_MediaCommon.md#ga797e6c5e38e23e730eff5bcc41427d7e">VideoCodecFormat</a> encoder)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1534215340093532"><a name="p1534215340093532"></a><a name="p1534215340093532"></a>int32_t&nbsp;</p>
<p id="p1393985056093532"><a name="p1393985056093532"></a><a name="p1393985056093532"></a>Sets a video encoder for recording. </p>
</td>
</tr>
<tr id="row1416875470093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725409702093532"><a name="p725409702093532"></a><a name="p725409702093532"></a><a href="MultiMedia_Recorder.md#ga43c0ee5b76f58a12c2c745839184a96b">SetVideoSize</a> (int32_t sourceId, int32_t width, int32_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576278420093532"><a name="p1576278420093532"></a><a name="p1576278420093532"></a>int32_t&nbsp;</p>
<p id="p136529356093532"><a name="p136529356093532"></a><a name="p136529356093532"></a>Sets the width and height of the video to record. </p>
</td>
</tr>
<tr id="row1428936691093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1471740625093532"><a name="p1471740625093532"></a><a name="p1471740625093532"></a><a href="MultiMedia_Recorder.md#gaeb90d4d75d80040aeaae354abd1d29d7">SetVideoFrameRate</a> (int32_t sourceId, int32_t frameRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990932206093532"><a name="p1990932206093532"></a><a name="p1990932206093532"></a>int32_t&nbsp;</p>
<p id="p1272252709093532"><a name="p1272252709093532"></a><a name="p1272252709093532"></a>Sets the frame rate of the video to record. </p>
</td>
</tr>
<tr id="row1467228112093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p624125060093532"><a name="p624125060093532"></a><a name="p624125060093532"></a><a href="MultiMedia_Recorder.md#ga4e05a76b50abf790f29f06a0c1d4ecb8">SetVideoEncodingBitRate</a> (int32_t sourceId, int32_t rate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074545947093532"><a name="p1074545947093532"></a><a name="p1074545947093532"></a>int32_t&nbsp;</p>
<p id="p1385305763093532"><a name="p1385305763093532"></a><a name="p1385305763093532"></a>Sets the encoding bit rate of the video to record. </p>
</td>
</tr>
<tr id="row1200460022093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1358664384093532"><a name="p1358664384093532"></a><a name="p1358664384093532"></a><a href="MultiMedia_Recorder.md#ga4f4a03fe881f48515874a699118fb84a">SetCaptureRate</a> (int32_t sourceId, double fps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351431187093532"><a name="p1351431187093532"></a><a name="p1351431187093532"></a>int32_t&nbsp;</p>
<p id="p938103206093532"><a name="p938103206093532"></a><a name="p938103206093532"></a>Sets the video capture rate. </p>
</td>
</tr>
<tr id="row881303142093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p45447370093532"><a name="p45447370093532"></a><a name="p45447370093532"></a><a href="MultiMedia_Recorder.md#gad633e33fbbd5efcf4057aff3cc6e2b38">GetSurface</a> (int32_t sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134812297093532"><a name="p2134812297093532"></a><a name="p2134812297093532"></a>std::shared_ptr&lt; <a href="OHOS-Surface.md">OHOS::Surface</a> &gt;&nbsp;</p>
<p id="p708914160093532"><a name="p708914160093532"></a><a name="p708914160093532"></a>Obtains the surface of the video source. </p>
</td>
</tr>
<tr id="row852829430093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p532180484093532"><a name="p532180484093532"></a><a name="p532180484093532"></a><a href="MultiMedia_Recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a">SetAudioSource</a> (<a href="MultiMedia_MediaCommon.md#gadc3158e093b995ca7b9b6aa32388ccdd">AudioSourceType</a> source, int32_t &amp;sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p544434135093532"><a name="p544434135093532"></a><a name="p544434135093532"></a>int32_t&nbsp;</p>
<p id="p1323886874093532"><a name="p1323886874093532"></a><a name="p1323886874093532"></a>Sets the audio source for recording. </p>
</td>
</tr>
<tr id="row380085041093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p159804188093532"><a name="p159804188093532"></a><a name="p159804188093532"></a><a href="MultiMedia_Recorder.md#gab37c9385fa1a56f686beb73c7dcc1b1b">SetAudioEncoder</a> (int32_t sourceId, <a href="MultiMedia_MediaCommon.md#gaa4ea6f314644ed287e0704be26c768b7">AudioCodecFormat</a> encoder)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557772345093532"><a name="p1557772345093532"></a><a name="p1557772345093532"></a>int32_t&nbsp;</p>
<p id="p213291964093532"><a name="p213291964093532"></a><a name="p213291964093532"></a>Sets an audio encoder for recording. </p>
</td>
</tr>
<tr id="row1547155181093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1565663265093532"><a name="p1565663265093532"></a><a name="p1565663265093532"></a><a href="MultiMedia_Recorder.md#gab2b98616da55ec294053c0c25645c845">SetAudioSampleRate</a> (int32_t sourceId, int32_t rate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023170269093532"><a name="p1023170269093532"></a><a name="p1023170269093532"></a>int32_t&nbsp;</p>
<p id="p1070190942093532"><a name="p1070190942093532"></a><a name="p1070190942093532"></a>Sets the audio sampling rate for recording. </p>
</td>
</tr>
<tr id="row655147901093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p290239041093532"><a name="p290239041093532"></a><a name="p290239041093532"></a><a href="MultiMedia_Recorder.md#ga77d76e5657cb3359e85521e08a456c7d">SetAudioChannels</a> (int32_t sourceId, int32_t num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1316867174093532"><a name="p1316867174093532"></a><a name="p1316867174093532"></a>int32_t&nbsp;</p>
<p id="p312435203093532"><a name="p312435203093532"></a><a name="p312435203093532"></a>Sets the number of audio channels to record. </p>
</td>
</tr>
<tr id="row2103434538093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1184214424093532"><a name="p1184214424093532"></a><a name="p1184214424093532"></a><a href="MultiMedia_Recorder.md#gac21a1a00c40cf58df84f1ba281b79a36">SetAudioEncodingBitRate</a> (int32_t sourceId, int32_t bitRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1478364380093532"><a name="p1478364380093532"></a><a name="p1478364380093532"></a>int32_t&nbsp;</p>
<p id="p404000164093532"><a name="p404000164093532"></a><a name="p404000164093532"></a>Sets the encoding bit rate of the audio to record. </p>
</td>
</tr>
<tr id="row854062482093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p624168310093532"><a name="p624168310093532"></a><a name="p624168310093532"></a><a href="MultiMedia_Recorder.md#gaf2806f0fddd17a3e59eb7c5c740470d6">SetMaxDuration</a> (int32_t duration)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p886630119093532"><a name="p886630119093532"></a><a name="p886630119093532"></a>int32_t&nbsp;</p>
<p id="p81386795093532"><a name="p81386795093532"></a><a name="p81386795093532"></a>Sets the maximum duration of a recorded file, in seconds. </p>
</td>
</tr>
<tr id="row109593246093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1299649012093532"><a name="p1299649012093532"></a><a name="p1299649012093532"></a><a href="MultiMedia_Recorder.md#gaffb7874aae331570ecedfe609a495468">SetOutputFormat</a> (<a href="MultiMedia_Recorder.md#ga3dfe2e61369bf1c081ce569e235354df">OutputFormatType</a> format)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1519448481093532"><a name="p1519448481093532"></a><a name="p1519448481093532"></a>int32_t&nbsp;</p>
<p id="p704398470093532"><a name="p704398470093532"></a><a name="p704398470093532"></a>Sets the output file format. </p>
</td>
</tr>
<tr id="row1228527075093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p174577146093532"><a name="p174577146093532"></a><a name="p174577146093532"></a><a href="MultiMedia_Recorder.md#gaa5c898c1ad051b5c9f115ef15d952f18">SetOutputPath</a> (const string &amp;path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p536821154093532"><a name="p536821154093532"></a><a name="p536821154093532"></a>int32_t&nbsp;</p>
<p id="p995109658093532"><a name="p995109658093532"></a><a name="p995109658093532"></a>Sets the output file path. </p>
</td>
</tr>
<tr id="row27876222093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p724544413093532"><a name="p724544413093532"></a><a name="p724544413093532"></a><a href="MultiMedia_Recorder.md#ga500d2bc895852fe292d7397d8450d091">SetOutputFile</a> (int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p371308302093532"><a name="p371308302093532"></a><a name="p371308302093532"></a>int32_t&nbsp;</p>
<p id="p1322156727093532"><a name="p1322156727093532"></a><a name="p1322156727093532"></a>Sets the file descriptor (FD) of the output file. </p>
</td>
</tr>
<tr id="row545955095093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1114218125093532"><a name="p1114218125093532"></a><a name="p1114218125093532"></a><a href="MultiMedia_Recorder.md#ga8545fe87eb4bd399525e4c5fb414d7cb">SetNextOutputFile</a> (int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p167499887093532"><a name="p167499887093532"></a><a name="p167499887093532"></a>int32_t&nbsp;</p>
<p id="p765475038093532"><a name="p765475038093532"></a><a name="p765475038093532"></a>Sets the FD of the next output file. </p>
</td>
</tr>
<tr id="row2056994610093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655625880093532"><a name="p655625880093532"></a><a name="p655625880093532"></a><a href="MultiMedia_Recorder.md#gaeed9ee49d9d1ac1497ec79bf9639c0bc">SetMaxFileSize</a> (int64_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213974397093532"><a name="p213974397093532"></a><a name="p213974397093532"></a>int32_t&nbsp;</p>
<p id="p136319636093532"><a name="p136319636093532"></a><a name="p136319636093532"></a>Sets the maximum size of a recorded file, in bytes. </p>
</td>
</tr>
<tr id="row1772219825093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550358041093532"><a name="p1550358041093532"></a><a name="p1550358041093532"></a><a href="MultiMedia_Recorder.md#ga882585460b0538680954ce6692610376">SetRecorderCallback</a> (const std::shared_ptr&lt; <a href="OHOS-Media-RecorderCallback.md">RecorderCallback</a> &gt; &amp;callback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646266398093532"><a name="p1646266398093532"></a><a name="p1646266398093532"></a>int32_t&nbsp;</p>
<p id="p1667112815093532"><a name="p1667112815093532"></a><a name="p1667112815093532"></a>Registers a recording listener. </p>
</td>
</tr>
<tr id="row425256762093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p602582632093532"><a name="p602582632093532"></a><a name="p602582632093532"></a><a href="MultiMedia_Recorder.md#ga15d2f3416bb735a0715e1e79be226387">Prepare</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369213349093532"><a name="p369213349093532"></a><a name="p369213349093532"></a>int32_t&nbsp;</p>
<p id="p609521601093532"><a name="p609521601093532"></a><a name="p609521601093532"></a>Prepares for recording. </p>
</td>
</tr>
<tr id="row1116635470093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p518058742093532"><a name="p518058742093532"></a><a name="p518058742093532"></a><a href="MultiMedia_Recorder.md#gac3aaa32627f0799dea65e51356b91bfb">Start</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288058230093532"><a name="p1288058230093532"></a><a name="p1288058230093532"></a>int32_t&nbsp;</p>
<p id="p689435494093532"><a name="p689435494093532"></a><a name="p689435494093532"></a>Starts recording. </p>
</td>
</tr>
<tr id="row1532435291093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944380716093532"><a name="p1944380716093532"></a><a name="p1944380716093532"></a><a href="MultiMedia_Recorder.md#ga71da5cc2720b336f0daadbe09d61c695">Pause</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676030007093532"><a name="p676030007093532"></a><a name="p676030007093532"></a>int32_t&nbsp;</p>
<p id="p1186613002093532"><a name="p1186613002093532"></a><a name="p1186613002093532"></a>Pauses recording. </p>
</td>
</tr>
<tr id="row823789107093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000455198093532"><a name="p1000455198093532"></a><a name="p1000455198093532"></a><a href="MultiMedia_Recorder.md#gafd32ed157821800936a258a73af936be">Resume</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157794111093532"><a name="p157794111093532"></a><a name="p157794111093532"></a>int32_t&nbsp;</p>
<p id="p698578014093532"><a name="p698578014093532"></a><a name="p698578014093532"></a>Resumes recording. </p>
</td>
</tr>
<tr id="row736093961093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620242820093532"><a name="p620242820093532"></a><a name="p620242820093532"></a><a href="MultiMedia_Recorder.md#ga1253f753cf9ed01dae5d57a37524dfa7">Stop</a> (bool block)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103199087093532"><a name="p1103199087093532"></a><a name="p1103199087093532"></a>int32_t&nbsp;</p>
<p id="p676744718093532"><a name="p676744718093532"></a><a name="p676744718093532"></a>Stops recording. </p>
</td>
</tr>
<tr id="row123791551093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1624752834093532"><a name="p1624752834093532"></a><a name="p1624752834093532"></a><a href="MultiMedia_Recorder.md#gaebb808d5dd73b94b769b69e2b464c744">Reset</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225360767093532"><a name="p225360767093532"></a><a name="p225360767093532"></a>int32_t&nbsp;</p>
<p id="p986252040093532"><a name="p986252040093532"></a><a name="p986252040093532"></a>Resets the recording. </p>
</td>
</tr>
<tr id="row660598439093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091987569093532"><a name="p1091987569093532"></a><a name="p1091987569093532"></a><a href="MultiMedia_Recorder.md#ga116583c0d649f447c2dd272aae465cca">Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p864209088093532"><a name="p864209088093532"></a><a name="p864209088093532"></a>int32_t&nbsp;</p>
<p id="p1971810982093532"><a name="p1971810982093532"></a><a name="p1971810982093532"></a>Releases recording resources. </p>
</td>
</tr>
<tr id="row502370220093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1417653222093532"><a name="p1417653222093532"></a><a name="p1417653222093532"></a><a href="MultiMedia_Recorder.md#ga952ce2fada10d701e38e4ee29139e2af">SetFileSplitDuration</a> (<a href="MultiMedia_Recorder.md#ga8759c7e5a74964a584a716f4ec0b7edb">FileSplitType</a> type, int64_t timestamp, uint32_t duration)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1272529990093532"><a name="p1272529990093532"></a><a name="p1272529990093532"></a>int32_t&nbsp;</p>
<p id="p589710659093532"><a name="p589710659093532"></a><a name="p589710659093532"></a>Manually splits a video. </p>
</td>
</tr>
<tr id="row1400352468093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1319267577093532"><a name="p1319267577093532"></a><a name="p1319267577093532"></a><a href="MultiMedia_Recorder.md#ga05cf279a460418b22d267527c83ede15">SetParameter</a> (int32_t sourceId, const <a href="OHOS-Media-Format.md">Format</a> &amp;format)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2044390357093532"><a name="p2044390357093532"></a><a name="p2044390357093532"></a>int32_t&nbsp;</p>
<p id="p849633858093532"><a name="p849633858093532"></a><a name="p849633858093532"></a>Sets an extended parameter for recording, for example, <strong id="b1511370470093532"><a name="b1511370470093532"></a><a name="b1511370470093532"></a>RCORDER_PRE_CACHE_DURATION</strong>. </p>
</td>
</tr>
</tbody>
</table>

