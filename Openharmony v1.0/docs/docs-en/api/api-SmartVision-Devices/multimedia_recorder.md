# MultiMedia\_Recorder<a name="EN-US_TOPIC_0000001054799553"></a>

## **Overview**<a name="section813603248093523"></a>

Defines the  **Recorder**  class and provides functions for audio and video recording. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2953648093523"></a>

## Files<a name="files"></a>

<a name="table1720554886093523"></a>
<table><thead align="left"><tr id="row724422408093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p962291851093523"><a name="p962291851093523"></a><a name="p962291851093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p887923986093523"><a name="p887923986093523"></a><a name="p887923986093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row358706440093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509528581093523"><a name="p509528581093523"></a><a name="p509528581093523"></a><a href="recorder-h.md">recorder.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1766380674093523"><a name="p1766380674093523"></a><a name="p1766380674093523"></a>Declares the <strong id="b1319555315093523"><a name="b1319555315093523"></a><a name="b1319555315093523"></a>Recorder</strong> class for audio and video recording. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1221641086093523"></a>
<table><thead align="left"><tr id="row1381956710093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p361122150093523"><a name="p361122150093523"></a><a name="p361122150093523"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p342510055093523"><a name="p342510055093523"></a><a name="p342510055093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1428479655093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p654847711093523"><a name="p654847711093523"></a><a name="p654847711093523"></a><a href="ohos-media-recordercallback.md">OHOS::Media::RecorderCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101469680093523"><a name="p101469680093523"></a><a name="p101469680093523"></a>Provides listeners for recording errors and information events. </p>
</td>
</tr>
<tr id="row1690965223093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204898035093523"><a name="p1204898035093523"></a><a name="p1204898035093523"></a><a href="ohos-media-recorder.md">OHOS::Media::Recorder</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182251503093523"><a name="p1182251503093523"></a><a name="p1182251503093523"></a>Provides functions for audio and video recording. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1216713834093523"></a>
<table><thead align="left"><tr id="row1064759830093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1221426325093523"><a name="p1221426325093523"></a><a name="p1221426325093523"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p364708938093523"><a name="p364708938093523"></a><a name="p364708938093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1261026490093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1068013999093523"><a name="p1068013999093523"></a><a name="p1068013999093523"></a><a href="multimedia_recorder.md#gad252d27f9ce4b6ae0756bfeaa5f34490">OHOS::Media::VideoSourceType</a> : int32_t { <a href="multimedia_recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490ad137c55cd463c87ff8ea66c116da2e57">OHOS::Media::VIDEO_SOURCE_SURFACE_YUV</a> = 0, <a href="multimedia_recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490afcca9aba53005db99434c74f62803d6d">OHOS::Media::VIDEO_SOURCE_SURFACE_RGB</a>, <a href="multimedia_recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490a9316951d19d2ed845d2c0ef92c541eb8">OHOS::Media::VIDEO_SOURCE_SURFACE_ES</a>, <a href="multimedia_recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490af19a30a10d95948a7dab0317a4e2447b">OHOS::Media::VIDEO_SOURCE_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029982052093523"><a name="p2029982052093523"></a><a name="p2029982052093523"></a>Enumerates video source types. </p>
</td>
</tr>
<tr id="row2045210593093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p475769915093523"><a name="p475769915093523"></a><a name="p475769915093523"></a><a href="multimedia_recorder.md#gaccc05bb178cecd760369ea096dceae4c">OHOS::Media::DataSourceType</a> : int32_t { <a href="multimedia_recorder.md#ggaccc05bb178cecd760369ea096dceae4ca18ab16c027cd6de93c4e64be806caed0">OHOS::Media::IMAGE</a> = 0 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088001454093523"><a name="p2088001454093523"></a><a name="p2088001454093523"></a>Enumerates data source types. </p>
</td>
</tr>
<tr id="row1965596020093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985802987093523"><a name="p1985802987093523"></a><a name="p1985802987093523"></a><a href="multimedia_recorder.md#ga3dfe2e61369bf1c081ce569e235354df">OHOS::Media::OutputFormatType</a> : int32_t { <a href="multimedia_recorder.md#gga3dfe2e61369bf1c081ce569e235354dfa5f2bb1abd7404320dcd46e7540a22586">OHOS::Media::FORMAT_DEFAULT</a> = 0, <a href="multimedia_recorder.md#gga3dfe2e61369bf1c081ce569e235354dfac7e010e743dca6fc60780bb745707d57">OHOS::Media::FORMAT_MPEG_4</a>, <a href="multimedia_recorder.md#gga3dfe2e61369bf1c081ce569e235354dfa2abf22281e8d5a30da1f0700d9bf45a3">OHOS::Media::FORMAT_TS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1956812075093523"><a name="p1956812075093523"></a><a name="p1956812075093523"></a>Enumerates output file formats. </p>
</td>
</tr>
<tr id="row1063334872093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498897192093523"><a name="p498897192093523"></a><a name="p498897192093523"></a><a href="multimedia_recorder.md#ga8759c7e5a74964a584a716f4ec0b7edb">OHOS::Media::FileSplitType</a> : int32_t { <a href="multimedia_recorder.md#gga8759c7e5a74964a584a716f4ec0b7edba9010fd43e012d61772ff5db3a9bdaf02">OHOS::Media::FILE_SPLIT_POST</a> = 0, <a href="multimedia_recorder.md#gga8759c7e5a74964a584a716f4ec0b7edba01981748b792c27773467ea70099be65">OHOS::Media::FILE_SPLIT_PRE</a>, <a href="multimedia_recorder.md#gga8759c7e5a74964a584a716f4ec0b7edbae05fb41e422f91399d2e2efc3e84943b">OHOS::Media::FILE_SPLIT_NORMAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1341343376093523"><a name="p1341343376093523"></a><a name="p1341343376093523"></a>Enumerates file split types. </p>
</td>
</tr>
<tr id="row130781735093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1225608326093523"><a name="p1225608326093523"></a><a name="p1225608326093523"></a><a href="multimedia_recorder.md#ga0db5cf9cc68d4b468e921a563248ffe0">OHOS::Media::RecorderCallback::RecorderInfoType</a> : int32_t {   <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0af47b2244ca5d4a906657ace804c62ab5">OHOS::Media::RecorderCallback::RECORDER_INFO_MAX_DURATION_APPROACHING</a> = 0, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0ace19eeffeb7bfd809c0eecd831dfc4c8">OHOS::Media::RecorderCallback::RECORDER_INFO_MAX_FILESIZE_APPROACHING</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0aa67fb963e882f4e45405e52a525d617e">OHOS::Media::RecorderCallback::RECORDER_INFO_MAX_DURATION_REACHED</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0ad33be678eb5f4ec5c5db92d324ec0b27">OHOS::Media::RecorderCallback::RECORDER_INFO_MAX_FILESIZE_REACHED</a>,   <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0ae27acecf4dec639f993091e2b4983d99">OHOS::Media::RecorderCallback::RECORDER_INFO_NEXT_OUTPUT_FILE_STARTED</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0a0a2e4851229314e2d019b7418a13ce82">OHOS::Media::RecorderCallback::RECORDER_INFO_FILE_SPLIT_FINISHED</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0abd5ed874b180a67a39c0edaa83a9e4d5">OHOS::Media::RecorderCallback::RECORDER_INFO_FILE_START_TIME_MS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393522808093523"><a name="p393522808093523"></a><a name="p393522808093523"></a>Enumerates recording information types. </p>
</td>
</tr>
<tr id="row672972126093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733371720093523"><a name="p1733371720093523"></a><a name="p1733371720093523"></a><a href="multimedia_recorder.md#ga5132172c298fc1497d12040b6bd511cf">OHOS::Media::RecorderCallback::RecorderErrorType</a> : int32_t { <a href="multimedia_recorder.md#gga5132172c298fc1497d12040b6bd511cfa0e5cc2daf43191929754b01659128d79">OHOS::Media::RecorderCallback::RECORDER_ERROR_UNKNOWN</a> = 0 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1370492358093523"><a name="p1370492358093523"></a><a name="p1370492358093523"></a>Enumerates recording error types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table911473189093523"></a>
<table><thead align="left"><tr id="row298029774093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1381964017093523"><a name="p1381964017093523"></a><a name="p1381964017093523"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1254649978093523"><a name="p1254649978093523"></a><a name="p1254649978093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row680952673093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p311949488093523"><a name="p311949488093523"></a><a name="p311949488093523"></a><a href="multimedia_recorder.md#ga822c915f1bfab8c380919f24f2ee4f54">OHOS::Media::RecorderCallback::OnError</a> (int32_t errorType, int32_t errorCode)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313409662093523"><a name="p1313409662093523"></a><a name="p1313409662093523"></a>virtual void </p>
<p id="p278837618093523"><a name="p278837618093523"></a><a name="p278837618093523"></a>Called when an error occurs during recording. This callback is used to report recording errors. </p>
</td>
</tr>
<tr id="row1070068931093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p619947014093523"><a name="p619947014093523"></a><a name="p619947014093523"></a><a href="multimedia_recorder.md#gac1f8bb191d90aac50119ea7ae4108407">OHOS::Media::RecorderCallback::OnInfo</a> (int32_t type, int32_t extra)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994195754093523"><a name="p1994195754093523"></a><a name="p1994195754093523"></a>virtual void </p>
<p id="p1348861506093523"><a name="p1348861506093523"></a><a name="p1348861506093523"></a>Called when an information event occurs during recording. This callback is used to report recording information. </p>
</td>
</tr>
<tr id="row1526380767093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p851817420093523"><a name="p851817420093523"></a><a name="p851817420093523"></a><a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">OHOS::Media::Recorder::SetVideoSource</a> (<a href="multimedia_recorder.md#gad252d27f9ce4b6ae0756bfeaa5f34490">VideoSourceType</a> source, int32_t &amp;sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861930323093523"><a name="p861930323093523"></a><a name="p861930323093523"></a>int32_t </p>
<p id="p342420130093523"><a name="p342420130093523"></a><a name="p342420130093523"></a>Sets a video source for recording. </p>
</td>
</tr>
<tr id="row1341511907093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730635022093523"><a name="p730635022093523"></a><a name="p730635022093523"></a><a href="multimedia_recorder.md#gad9be6914af57fcf7acb7a5398118c614">OHOS::Media::Recorder::SetVideoEncoder</a> (int32_t sourceId, <a href="multimedia_mediacommon.md#ga797e6c5e38e23e730eff5bcc41427d7e">VideoCodecFormat</a> encoder)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p511933924093523"><a name="p511933924093523"></a><a name="p511933924093523"></a>int32_t </p>
<p id="p1129969036093523"><a name="p1129969036093523"></a><a name="p1129969036093523"></a>Sets a video encoder for recording. </p>
</td>
</tr>
<tr id="row984175353093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1827890926093523"><a name="p1827890926093523"></a><a name="p1827890926093523"></a><a href="multimedia_recorder.md#ga43c0ee5b76f58a12c2c745839184a96b">OHOS::Media::Recorder::SetVideoSize</a> (int32_t sourceId, int32_t width, int32_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1648761074093523"><a name="p1648761074093523"></a><a name="p1648761074093523"></a>int32_t </p>
<p id="p971937993093523"><a name="p971937993093523"></a><a name="p971937993093523"></a>Sets the width and height of the video to record. </p>
</td>
</tr>
<tr id="row1502358505093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1715099754093523"><a name="p1715099754093523"></a><a name="p1715099754093523"></a><a href="multimedia_recorder.md#gaeb90d4d75d80040aeaae354abd1d29d7">OHOS::Media::Recorder::SetVideoFrameRate</a> (int32_t sourceId, int32_t frameRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p434750406093523"><a name="p434750406093523"></a><a name="p434750406093523"></a>int32_t </p>
<p id="p1135465591093523"><a name="p1135465591093523"></a><a name="p1135465591093523"></a>Sets the frame rate of the video to record. </p>
</td>
</tr>
<tr id="row659993171093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p754783501093523"><a name="p754783501093523"></a><a name="p754783501093523"></a><a href="multimedia_recorder.md#ga4e05a76b50abf790f29f06a0c1d4ecb8">OHOS::Media::Recorder::SetVideoEncodingBitRate</a> (int32_t sourceId, int32_t rate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245304126093523"><a name="p1245304126093523"></a><a name="p1245304126093523"></a>int32_t </p>
<p id="p399229193093523"><a name="p399229193093523"></a><a name="p399229193093523"></a>Sets the encoding bit rate of the video to record. </p>
</td>
</tr>
<tr id="row565451701093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883876237093523"><a name="p883876237093523"></a><a name="p883876237093523"></a><a href="multimedia_recorder.md#ga4f4a03fe881f48515874a699118fb84a">OHOS::Media::Recorder::SetCaptureRate</a> (int32_t sourceId, double fps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1834500411093523"><a name="p1834500411093523"></a><a name="p1834500411093523"></a>int32_t </p>
<p id="p2120855576093523"><a name="p2120855576093523"></a><a name="p2120855576093523"></a>Sets the video capture rate. </p>
</td>
</tr>
<tr id="row746956947093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092630755093523"><a name="p2092630755093523"></a><a name="p2092630755093523"></a><a href="multimedia_recorder.md#gad633e33fbbd5efcf4057aff3cc6e2b38">OHOS::Media::Recorder::GetSurface</a> (int32_t sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p824930314093523"><a name="p824930314093523"></a><a name="p824930314093523"></a>std::shared_ptr&lt; <a href="ohos-surface.md">OHOS::Surface</a> &gt; </p>
<p id="p375303447093523"><a name="p375303447093523"></a><a name="p375303447093523"></a>Obtains the surface of the video source. </p>
</td>
</tr>
<tr id="row1637444827093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106303438093523"><a name="p2106303438093523"></a><a name="p2106303438093523"></a><a href="multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a">OHOS::Media::Recorder::SetAudioSource</a> (<a href="multimedia_mediacommon.md#gadc3158e093b995ca7b9b6aa32388ccdd">AudioSourceType</a> source, int32_t &amp;sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1529812778093523"><a name="p1529812778093523"></a><a name="p1529812778093523"></a>int32_t </p>
<p id="p1674163893093523"><a name="p1674163893093523"></a><a name="p1674163893093523"></a>Sets the audio source for recording. </p>
</td>
</tr>
<tr id="row1599143268093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p962667576093523"><a name="p962667576093523"></a><a name="p962667576093523"></a><a href="multimedia_recorder.md#gab37c9385fa1a56f686beb73c7dcc1b1b">OHOS::Media::Recorder::SetAudioEncoder</a> (int32_t sourceId, <a href="multimedia_mediacommon.md#gaa4ea6f314644ed287e0704be26c768b7">AudioCodecFormat</a> encoder)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2145397412093523"><a name="p2145397412093523"></a><a name="p2145397412093523"></a>int32_t </p>
<p id="p1256882371093523"><a name="p1256882371093523"></a><a name="p1256882371093523"></a>Sets an audio encoder for recording. </p>
</td>
</tr>
<tr id="row41076208093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44305558093523"><a name="p44305558093523"></a><a name="p44305558093523"></a><a href="multimedia_recorder.md#gab2b98616da55ec294053c0c25645c845">OHOS::Media::Recorder::SetAudioSampleRate</a> (int32_t sourceId, int32_t rate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1017986136093523"><a name="p1017986136093523"></a><a name="p1017986136093523"></a>int32_t </p>
<p id="p233204830093523"><a name="p233204830093523"></a><a name="p233204830093523"></a>Sets the audio sampling rate for recording. </p>
</td>
</tr>
<tr id="row340783059093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p314499125093523"><a name="p314499125093523"></a><a name="p314499125093523"></a><a href="multimedia_recorder.md#ga77d76e5657cb3359e85521e08a456c7d">OHOS::Media::Recorder::SetAudioChannels</a> (int32_t sourceId, int32_t num)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348158986093523"><a name="p348158986093523"></a><a name="p348158986093523"></a>int32_t </p>
<p id="p986547458093523"><a name="p986547458093523"></a><a name="p986547458093523"></a>Sets the number of audio channels to record. </p>
</td>
</tr>
<tr id="row1620348805093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1018418847093523"><a name="p1018418847093523"></a><a name="p1018418847093523"></a><a href="multimedia_recorder.md#gac21a1a00c40cf58df84f1ba281b79a36">OHOS::Media::Recorder::SetAudioEncodingBitRate</a> (int32_t sourceId, int32_t bitRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67726740093523"><a name="p67726740093523"></a><a name="p67726740093523"></a>int32_t </p>
<p id="p1180978883093523"><a name="p1180978883093523"></a><a name="p1180978883093523"></a>Sets the encoding bit rate of the audio to record. </p>
</td>
</tr>
<tr id="row1010578046093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1837015058093523"><a name="p1837015058093523"></a><a name="p1837015058093523"></a><a href="multimedia_recorder.md#gaf2806f0fddd17a3e59eb7c5c740470d6">OHOS::Media::Recorder::SetMaxDuration</a> (int32_t duration)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712475210093523"><a name="p1712475210093523"></a><a name="p1712475210093523"></a>int32_t </p>
<p id="p2006472955093523"><a name="p2006472955093523"></a><a name="p2006472955093523"></a>Sets the maximum duration of a recorded file, in seconds. </p>
</td>
</tr>
<tr id="row822728472093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636672898093523"><a name="p636672898093523"></a><a name="p636672898093523"></a><a href="multimedia_recorder.md#gaffb7874aae331570ecedfe609a495468">OHOS::Media::Recorder::SetOutputFormat</a> (<a href="multimedia_recorder.md#ga3dfe2e61369bf1c081ce569e235354df">OutputFormatType</a> format)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1205080832093523"><a name="p1205080832093523"></a><a name="p1205080832093523"></a>int32_t </p>
<p id="p1723249559093523"><a name="p1723249559093523"></a><a name="p1723249559093523"></a>Sets the output file format. </p>
</td>
</tr>
<tr id="row67569527093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p90666847093523"><a name="p90666847093523"></a><a name="p90666847093523"></a><a href="multimedia_recorder.md#gaa5c898c1ad051b5c9f115ef15d952f18">OHOS::Media::Recorder::SetOutputPath</a> (const string &amp;path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105944087093523"><a name="p105944087093523"></a><a name="p105944087093523"></a>int32_t </p>
<p id="p1194503349093523"><a name="p1194503349093523"></a><a name="p1194503349093523"></a>Sets the output file path. </p>
</td>
</tr>
<tr id="row1417224560093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1528642964093523"><a name="p1528642964093523"></a><a name="p1528642964093523"></a><a href="multimedia_recorder.md#ga500d2bc895852fe292d7397d8450d091">OHOS::Media::Recorder::SetOutputFile</a> (int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2096877714093523"><a name="p2096877714093523"></a><a name="p2096877714093523"></a>int32_t </p>
<p id="p1736440839093523"><a name="p1736440839093523"></a><a name="p1736440839093523"></a>Sets the file descriptor (FD) of the output file. </p>
</td>
</tr>
<tr id="row1597450936093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1012707093093523"><a name="p1012707093093523"></a><a name="p1012707093093523"></a><a href="multimedia_recorder.md#ga8545fe87eb4bd399525e4c5fb414d7cb">OHOS::Media::Recorder::SetNextOutputFile</a> (int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p688967428093523"><a name="p688967428093523"></a><a name="p688967428093523"></a>int32_t </p>
<p id="p1143389253093523"><a name="p1143389253093523"></a><a name="p1143389253093523"></a>Sets the FD of the next output file. </p>
</td>
</tr>
<tr id="row136176043093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1887364289093523"><a name="p1887364289093523"></a><a name="p1887364289093523"></a><a href="multimedia_recorder.md#gaeed9ee49d9d1ac1497ec79bf9639c0bc">OHOS::Media::Recorder::SetMaxFileSize</a> (int64_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348672136093523"><a name="p348672136093523"></a><a name="p348672136093523"></a>int32_t </p>
<p id="p2093166439093523"><a name="p2093166439093523"></a><a name="p2093166439093523"></a>Sets the maximum size of a recorded file, in bytes. </p>
</td>
</tr>
<tr id="row1310396059093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p462346016093523"><a name="p462346016093523"></a><a name="p462346016093523"></a><a href="multimedia_recorder.md#ga882585460b0538680954ce6692610376">OHOS::Media::Recorder::SetRecorderCallback</a> (const std::shared_ptr&lt; <a href="ohos-media-recordercallback.md">RecorderCallback</a> &gt; &amp;callback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2020418399093523"><a name="p2020418399093523"></a><a name="p2020418399093523"></a>int32_t </p>
<p id="p1289408181093523"><a name="p1289408181093523"></a><a name="p1289408181093523"></a>Registers a recording listener. </p>
</td>
</tr>
<tr id="row1661232613093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p137661708093523"><a name="p137661708093523"></a><a name="p137661708093523"></a><a href="multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387">OHOS::Media::Recorder::Prepare</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801196611093523"><a name="p801196611093523"></a><a name="p801196611093523"></a>int32_t </p>
<p id="p1600774546093523"><a name="p1600774546093523"></a><a name="p1600774546093523"></a>Prepares for recording. </p>
</td>
</tr>
<tr id="row264294094093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963314626093523"><a name="p963314626093523"></a><a name="p963314626093523"></a><a href="multimedia_recorder.md#gac3aaa32627f0799dea65e51356b91bfb">OHOS::Media::Recorder::Start</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p744615776093523"><a name="p744615776093523"></a><a name="p744615776093523"></a>int32_t </p>
<p id="p1226381872093523"><a name="p1226381872093523"></a><a name="p1226381872093523"></a>Starts recording. </p>
</td>
</tr>
<tr id="row36417538093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785094087093523"><a name="p1785094087093523"></a><a name="p1785094087093523"></a><a href="multimedia_recorder.md#ga71da5cc2720b336f0daadbe09d61c695">OHOS::Media::Recorder::Pause</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193676080093523"><a name="p1193676080093523"></a><a name="p1193676080093523"></a>int32_t </p>
<p id="p923942917093523"><a name="p923942917093523"></a><a name="p923942917093523"></a>Pauses recording. </p>
</td>
</tr>
<tr id="row436389210093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1742531283093523"><a name="p1742531283093523"></a><a name="p1742531283093523"></a><a href="multimedia_recorder.md#gafd32ed157821800936a258a73af936be">OHOS::Media::Recorder::Resume</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588446860093523"><a name="p1588446860093523"></a><a name="p1588446860093523"></a>int32_t </p>
<p id="p1369556172093523"><a name="p1369556172093523"></a><a name="p1369556172093523"></a>Resumes recording. </p>
</td>
</tr>
<tr id="row39152720093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494107474093523"><a name="p1494107474093523"></a><a name="p1494107474093523"></a><a href="multimedia_recorder.md#ga1253f753cf9ed01dae5d57a37524dfa7">OHOS::Media::Recorder::Stop</a> (bool block)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1822612433093523"><a name="p1822612433093523"></a><a name="p1822612433093523"></a>int32_t </p>
<p id="p2105484633093523"><a name="p2105484633093523"></a><a name="p2105484633093523"></a>Stops recording. </p>
</td>
</tr>
<tr id="row1327466878093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935301857093523"><a name="p1935301857093523"></a><a name="p1935301857093523"></a><a href="multimedia_recorder.md#gaebb808d5dd73b94b769b69e2b464c744">OHOS::Media::Recorder::Reset</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1916936186093523"><a name="p1916936186093523"></a><a name="p1916936186093523"></a>int32_t </p>
<p id="p1782042779093523"><a name="p1782042779093523"></a><a name="p1782042779093523"></a>Resets the recording. </p>
</td>
</tr>
<tr id="row526526578093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662646081093523"><a name="p662646081093523"></a><a name="p662646081093523"></a><a href="multimedia_recorder.md#ga116583c0d649f447c2dd272aae465cca">OHOS::Media::Recorder::Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882489397093523"><a name="p882489397093523"></a><a name="p882489397093523"></a>int32_t </p>
<p id="p1430619621093523"><a name="p1430619621093523"></a><a name="p1430619621093523"></a>Releases recording resources. </p>
</td>
</tr>
<tr id="row1538317046093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1021960870093523"><a name="p1021960870093523"></a><a name="p1021960870093523"></a><a href="multimedia_recorder.md#ga952ce2fada10d701e38e4ee29139e2af">OHOS::Media::Recorder::SetFileSplitDuration</a> (<a href="multimedia_recorder.md#ga8759c7e5a74964a584a716f4ec0b7edb">FileSplitType</a> type, int64_t timestamp, uint32_t duration)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800583402093523"><a name="p800583402093523"></a><a name="p800583402093523"></a>int32_t </p>
<p id="p1930024465093523"><a name="p1930024465093523"></a><a name="p1930024465093523"></a>Manually splits a video. </p>
</td>
</tr>
<tr id="row1985417361093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p889404626093523"><a name="p889404626093523"></a><a name="p889404626093523"></a><a href="multimedia_recorder.md#ga05cf279a460418b22d267527c83ede15">OHOS::Media::Recorder::SetParameter</a> (int32_t sourceId, const <a href="ohos-media-format.md">Format</a> &amp;format)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p154156846093523"><a name="p154156846093523"></a><a name="p154156846093523"></a>int32_t </p>
<p id="p422488051093523"><a name="p422488051093523"></a><a name="p422488051093523"></a>Sets an extended parameter for recording, for example, <strong id="b1037967605093523"><a name="b1037967605093523"></a><a name="b1037967605093523"></a>RCORDER_PRE_CACHE_DURATION</strong>. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section709848852093523"></a>

## **Enumeration Type Documentation**<a name="section851210300093523"></a>

## DataSourceType<a name="gaccc05bb178cecd760369ea096dceae4c"></a>

```
enum [OHOS::Media::DataSourceType](multimedia_recorder.md#gaccc05bb178cecd760369ea096dceae4c) : int32_t
```

 **Description:**

Enumerates data source types. 

<a name="table1562758845093523"></a>
<table><thead align="left"><tr id="row770590823093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1910554636093523"><a name="p1910554636093523"></a><a name="p1910554636093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1042913223093523"><a name="p1042913223093523"></a><a name="p1042913223093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row12441992093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaccc05bb178cecd760369ea096dceae4ca18ab16c027cd6de93c4e64be806caed0"><a name="ggaccc05bb178cecd760369ea096dceae4ca18ab16c027cd6de93c4e64be806caed0"></a><a name="ggaccc05bb178cecd760369ea096dceae4ca18ab16c027cd6de93c4e64be806caed0"></a></strong>IMAGE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053372660093523"><a name="p2053372660093523"></a><a name="p2053372660093523"></a><a href="ohos-image.md">Image</a> data source </p>
 </td>
</tr>
</tbody>
</table>

## FileSplitType<a name="ga8759c7e5a74964a584a716f4ec0b7edb"></a>

```
enum [OHOS::Media::FileSplitType](multimedia_recorder.md#ga8759c7e5a74964a584a716f4ec0b7edb) : int32_t
```

 **Description:**

Enumerates file split types. 

<a name="table1276516214093523"></a>
<table><thead align="left"><tr id="row362078692093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p300431219093523"><a name="p300431219093523"></a><a name="p300431219093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1922922311093523"><a name="p1922922311093523"></a><a name="p1922922311093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1511002547093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8759c7e5a74964a584a716f4ec0b7edba9010fd43e012d61772ff5db3a9bdaf02"><a name="gga8759c7e5a74964a584a716f4ec0b7edba9010fd43e012d61772ff5db3a9bdaf02"></a><a name="gga8759c7e5a74964a584a716f4ec0b7edba9010fd43e012d61772ff5db3a9bdaf02"></a></strong>FILE_SPLIT_POST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831428027093523"><a name="p1831428027093523"></a><a name="p1831428027093523"></a>Delayed/Backward split </p>
 </td>
</tr>
<tr id="row1582277442093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8759c7e5a74964a584a716f4ec0b7edba01981748b792c27773467ea70099be65"><a name="gga8759c7e5a74964a584a716f4ec0b7edba01981748b792c27773467ea70099be65"></a><a name="gga8759c7e5a74964a584a716f4ec0b7edba01981748b792c27773467ea70099be65"></a></strong>FILE_SPLIT_PRE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1856106944093523"><a name="p1856106944093523"></a><a name="p1856106944093523"></a>Advanced/Forward split </p>
 </td>
</tr>
<tr id="row1612141546093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8759c7e5a74964a584a716f4ec0b7edbae05fb41e422f91399d2e2efc3e84943b"><a name="gga8759c7e5a74964a584a716f4ec0b7edbae05fb41e422f91399d2e2efc3e84943b"></a><a name="gga8759c7e5a74964a584a716f4ec0b7edbae05fb41e422f91399d2e2efc3e84943b"></a></strong>FILE_SPLIT_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448292730093523"><a name="p448292730093523"></a><a name="p448292730093523"></a>Normal split </p>
 </td>
</tr>
</tbody>
</table>

## OutputFormatType<a name="ga3dfe2e61369bf1c081ce569e235354df"></a>

```
enum [OHOS::Media::OutputFormatType](multimedia_recorder.md#ga3dfe2e61369bf1c081ce569e235354df) : int32_t
```

 **Description:**

Enumerates output file formats. 

<a name="table1989491426093523"></a>
<table><thead align="left"><tr id="row2068157643093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p591443768093523"><a name="p591443768093523"></a><a name="p591443768093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1207949339093523"><a name="p1207949339093523"></a><a name="p1207949339093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row401334839093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3dfe2e61369bf1c081ce569e235354dfa5f2bb1abd7404320dcd46e7540a22586"><a name="gga3dfe2e61369bf1c081ce569e235354dfa5f2bb1abd7404320dcd46e7540a22586"></a><a name="gga3dfe2e61369bf1c081ce569e235354dfa5f2bb1abd7404320dcd46e7540a22586"></a></strong>FORMAT_DEFAULT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474627517093523"><a name="p1474627517093523"></a><a name="p1474627517093523"></a>Default format </p>
 </td>
</tr>
<tr id="row525711402093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3dfe2e61369bf1c081ce569e235354dfac7e010e743dca6fc60780bb745707d57"><a name="gga3dfe2e61369bf1c081ce569e235354dfac7e010e743dca6fc60780bb745707d57"></a><a name="gga3dfe2e61369bf1c081ce569e235354dfac7e010e743dca6fc60780bb745707d57"></a></strong>FORMAT_MPEG_4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p724729632093523"><a name="p724729632093523"></a><a name="p724729632093523"></a>MPEG4 format </p>
 </td>
</tr>
<tr id="row363534513093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3dfe2e61369bf1c081ce569e235354dfa2abf22281e8d5a30da1f0700d9bf45a3"><a name="gga3dfe2e61369bf1c081ce569e235354dfa2abf22281e8d5a30da1f0700d9bf45a3"></a><a name="gga3dfe2e61369bf1c081ce569e235354dfa2abf22281e8d5a30da1f0700d9bf45a3"></a></strong>FORMAT_TS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1729314644093523"><a name="p1729314644093523"></a><a name="p1729314644093523"></a>TS format </p>
 </td>
</tr>
</tbody>
</table>

## RecorderErrorType<a name="ga5132172c298fc1497d12040b6bd511cf"></a>

```
enum [OHOS::Media::RecorderCallback::RecorderErrorType](multimedia_recorder.md#ga5132172c298fc1497d12040b6bd511cf) : int32_t
```

 **Description:**

Enumerates recording error types. 

<a name="table2001446455093523"></a>
<table><thead align="left"><tr id="row131020063093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p595048386093523"><a name="p595048386093523"></a><a name="p595048386093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1746122499093523"><a name="p1746122499093523"></a><a name="p1746122499093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1168494199093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga5132172c298fc1497d12040b6bd511cfa0e5cc2daf43191929754b01659128d79"><a name="gga5132172c298fc1497d12040b6bd511cfa0e5cc2daf43191929754b01659128d79"></a><a name="gga5132172c298fc1497d12040b6bd511cfa0e5cc2daf43191929754b01659128d79"></a></strong>RECORDER_ERROR_UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1068364417093523"><a name="p1068364417093523"></a><a name="p1068364417093523"></a>Unknown error </p>
 </td>
</tr>
</tbody>
</table>

## RecorderInfoType<a name="ga0db5cf9cc68d4b468e921a563248ffe0"></a>

```
enum [OHOS::Media::RecorderCallback::RecorderInfoType](multimedia_recorder.md#ga0db5cf9cc68d4b468e921a563248ffe0) : int32_t
```

 **Description:**

Enumerates recording information types. 

<a name="table31562850093523"></a>
<table><thead align="left"><tr id="row1068887372093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p125639071093523"><a name="p125639071093523"></a><a name="p125639071093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2108672840093523"><a name="p2108672840093523"></a><a name="p2108672840093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2016374018093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0af47b2244ca5d4a906657ace804c62ab5"><a name="gga0db5cf9cc68d4b468e921a563248ffe0af47b2244ca5d4a906657ace804c62ab5"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0af47b2244ca5d4a906657ace804c62ab5"></a></strong>RECORDER_INFO_MAX_DURATION_APPROACHING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1886640347093523"><a name="p1886640347093523"></a><a name="p1886640347093523"></a>The recording duration is reaching the threshold specified by <strong id="b476723362093523"><a name="b476723362093523"></a><a name="b476723362093523"></a>SetMaxDuration</strong>. This type of information is reported when only one second or 10% is left to reach the allowed duration. </p>
 </td>
</tr>
<tr id="row453829915093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0ace19eeffeb7bfd809c0eecd831dfc4c8"><a name="gga0db5cf9cc68d4b468e921a563248ffe0ace19eeffeb7bfd809c0eecd831dfc4c8"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0ace19eeffeb7bfd809c0eecd831dfc4c8"></a></strong>RECORDER_INFO_MAX_FILESIZE_APPROACHING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1853487662093523"><a name="p1853487662093523"></a><a name="p1853487662093523"></a>The recorded file size is reaching the threshold specified by <strong id="b101882487093523"><a name="b101882487093523"></a><a name="b101882487093523"></a>SetMaxFileSize</strong>. This type of information is reported when only 100 KB or 10% is left to reach the allowed size. </p>
 </td>
</tr>
<tr id="row1054656266093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0aa67fb963e882f4e45405e52a525d617e"><a name="gga0db5cf9cc68d4b468e921a563248ffe0aa67fb963e882f4e45405e52a525d617e"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0aa67fb963e882f4e45405e52a525d617e"></a></strong>RECORDER_INFO_MAX_DURATION_REACHED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679522627093523"><a name="p679522627093523"></a><a name="p679522627093523"></a>The threshold specified by <strong id="b1609674251093523"><a name="b1609674251093523"></a><a name="b1609674251093523"></a>SetMaxDuration</strong> is reached, and the recording ends. Before calling <strong id="b748198388093523"><a name="b748198388093523"></a><a name="b748198388093523"></a>SetOutputFile</strong>, you must close the file. </p>
 </td>
</tr>
<tr id="row114794316093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0ad33be678eb5f4ec5c5db92d324ec0b27"><a name="gga0db5cf9cc68d4b468e921a563248ffe0ad33be678eb5f4ec5c5db92d324ec0b27"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0ad33be678eb5f4ec5c5db92d324ec0b27"></a></strong>RECORDER_INFO_MAX_FILESIZE_REACHED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1034691151093523"><a name="p1034691151093523"></a><a name="p1034691151093523"></a>The threshold specified by <strong id="b143423453093523"><a name="b143423453093523"></a><a name="b143423453093523"></a>SetMaxFileSize</strong> is reached, and the recording ends. Before calling <strong id="b1564121198093523"><a name="b1564121198093523"></a><a name="b1564121198093523"></a>SetOutputFile</strong>, you must close the file. </p>
 </td>
</tr>
<tr id="row1960269044093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0ae27acecf4dec639f993091e2b4983d99"><a name="gga0db5cf9cc68d4b468e921a563248ffe0ae27acecf4dec639f993091e2b4983d99"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0ae27acecf4dec639f993091e2b4983d99"></a></strong>RECORDER_INFO_NEXT_OUTPUT_FILE_STARTED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326591732093523"><a name="p1326591732093523"></a><a name="p1326591732093523"></a>Recording started for the next output file. </p>
 </td>
</tr>
<tr id="row1216758142093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0a0a2e4851229314e2d019b7418a13ce82"><a name="gga0db5cf9cc68d4b468e921a563248ffe0a0a2e4851229314e2d019b7418a13ce82"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0a0a2e4851229314e2d019b7418a13ce82"></a></strong>RECORDER_INFO_FILE_SPLIT_FINISHED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91095480093523"><a name="p91095480093523"></a><a name="p91095480093523"></a>Manual file split completed. </p>
 </td>
</tr>
<tr id="row1941101101093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0db5cf9cc68d4b468e921a563248ffe0abd5ed874b180a67a39c0edaa83a9e4d5"><a name="gga0db5cf9cc68d4b468e921a563248ffe0abd5ed874b180a67a39c0edaa83a9e4d5"></a><a name="gga0db5cf9cc68d4b468e921a563248ffe0abd5ed874b180a67a39c0edaa83a9e4d5"></a></strong>RECORDER_INFO_FILE_START_TIME_MS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p245760745093523"><a name="p245760745093523"></a><a name="p245760745093523"></a>The start time position of the recording file is not supported. </p>
 </td>
</tr>
</tbody>
</table>

## VideoSourceType<a name="gad252d27f9ce4b6ae0756bfeaa5f34490"></a>

```
enum [OHOS::Media::VideoSourceType](multimedia_recorder.md#gad252d27f9ce4b6ae0756bfeaa5f34490) : int32_t
```

 **Description:**

Enumerates video source types. 

<a name="table801399580093523"></a>
<table><thead align="left"><tr id="row1205861817093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1469195750093523"><a name="p1469195750093523"></a><a name="p1469195750093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1963925989093523"><a name="p1963925989093523"></a><a name="p1963925989093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1528060699093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad252d27f9ce4b6ae0756bfeaa5f34490ad137c55cd463c87ff8ea66c116da2e57"><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490ad137c55cd463c87ff8ea66c116da2e57"></a><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490ad137c55cd463c87ff8ea66c116da2e57"></a></strong>VIDEO_SOURCE_SURFACE_YUV </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444084281093523"><a name="p444084281093523"></a><a name="p444084281093523"></a>YUV video data provided through <a href="surface.md">Surface</a> </p>
 </td>
</tr>
<tr id="row1745386000093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad252d27f9ce4b6ae0756bfeaa5f34490afcca9aba53005db99434c74f62803d6d"><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490afcca9aba53005db99434c74f62803d6d"></a><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490afcca9aba53005db99434c74f62803d6d"></a></strong>VIDEO_SOURCE_SURFACE_RGB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699753232093523"><a name="p1699753232093523"></a><a name="p1699753232093523"></a>RGB video data provided through <a href="surface.md">Surface</a> </p>
 </td>
</tr>
<tr id="row1876028535093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad252d27f9ce4b6ae0756bfeaa5f34490a9316951d19d2ed845d2c0ef92c541eb8"><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490a9316951d19d2ed845d2c0ef92c541eb8"></a><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490a9316951d19d2ed845d2c0ef92c541eb8"></a></strong>VIDEO_SOURCE_SURFACE_ES </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791679739093523"><a name="p791679739093523"></a><a name="p791679739093523"></a>Raw encoded data provided through <a href="surface.md">Surface</a> </p>
 </td>
</tr>
<tr id="row649505798093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad252d27f9ce4b6ae0756bfeaa5f34490af19a30a10d95948a7dab0317a4e2447b"><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490af19a30a10d95948a7dab0317a4e2447b"></a><a name="ggad252d27f9ce4b6ae0756bfeaa5f34490af19a30a10d95948a7dab0317a4e2447b"></a></strong>VIDEO_SOURCE_BUTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229968933093523"><a name="p229968933093523"></a><a name="p229968933093523"></a>Invalid value </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1910761112093523"></a>

## GetSurface\(\)<a name="gad633e33fbbd5efcf4057aff3cc6e2b38"></a>

```
std::shared_ptr<[OHOS::Surface](ohos-surface.md)> OHOS::Media::Recorder::GetSurface (int32_t sourceId)
```

 **Description:**

Obtains the surface of the video source. 

**Parameters:**

<a name="table925784930093523"></a>
<table><thead align="left"><tr id="row945082100093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1393130046093523"><a name="p1393130046093523"></a><a name="p1393130046093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1802972058093523"><a name="p1802972058093523"></a><a name="p1802972058093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row124823954093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID, which can be obtained from <a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the surface. 



## OnError\(\)<a name="ga822c915f1bfab8c380919f24f2ee4f54"></a>

```
virtual void OHOS::Media::RecorderCallback::OnError (int32_t errorType, int32_t errorCode )
```

 **Description:**

Called when an error occurs during recording. This callback is used to report recording errors. 

**Parameters:**

<a name="table1060410310093523"></a>
<table><thead align="left"><tr id="row122153233093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1553906841093523"><a name="p1553906841093523"></a><a name="p1553906841093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1099190524093523"><a name="p1099190524093523"></a><a name="p1099190524093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1796503621093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error type. For details, see <a href="multimedia_recorder.md#ga5132172c298fc1497d12040b6bd511cf">RecorderErrorType</a>. </td>
</tr>
<tr id="row213208190093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error code. </td>
</tr>
</tbody>
</table>

## OnInfo\(\)<a name="gac1f8bb191d90aac50119ea7ae4108407"></a>

```
virtual void OHOS::Media::RecorderCallback::OnInfo (int32_t type, int32_t extra )
```

 **Description:**

Called when an information event occurs during recording. This callback is used to report recording information. 

**Parameters:**

<a name="table1958876939093523"></a>
<table><thead align="left"><tr id="row360780068093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p9950185093523"><a name="p9950185093523"></a><a name="p9950185093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1467462054093523"><a name="p1467462054093523"></a><a name="p1467462054093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1563342110093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the information type. For details, see <a href="multimedia_recorder.md#ga0db5cf9cc68d4b468e921a563248ffe0">RecorderInfoType</a>. </td>
</tr>
<tr id="row529220958093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">extra</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates other information, for example, the start time position of a recording file. </td>
</tr>
</tbody>
</table>

## Pause\(\)<a name="ga71da5cc2720b336f0daadbe09d61c695"></a>

```
int32_t OHOS::Media::Recorder::Pause ()
```

 **Description:**

Pauses recording. 

After  [Start](multimedia_recorder.md#gac3aaa32627f0799dea65e51356b91bfb)  is called, you can call this function to pause recording. The audio and video source streams are not paused, and source data is discarded.

**Returns:**

Returns  **SUCCESS**  if the recording is paused; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Prepare\(\)<a name="ga15d2f3416bb735a0715e1e79be226387"></a>

```
int32_t OHOS::Media::Recorder::Prepare ()
```

 **Description:**

Prepares for recording. 

This function must be called before  [Start](multimedia_recorder.md#gac3aaa32627f0799dea65e51356b91bfb).

**Returns:**

Returns  **SUCCESS**  if the preparation is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Release\(\)<a name="ga116583c0d649f447c2dd272aae465cca"></a>

```
int32_t OHOS::Media::Recorder::Release ()
```

 **Description:**

Releases recording resources. 

**Returns:**

Returns  **SUCCESS**  if recording resources are released; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Reset\(\)<a name="gaebb808d5dd73b94b769b69e2b464c744"></a>

```
int32_t OHOS::Media::Recorder::Reset ()
```

 **Description:**

Resets the recording. 

After the function is called, add a recording source by calling  [SetVideoSource](multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca)  or  [SetAudioSource](multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a), set related parameters, and call  [Start](multimedia_recorder.md#gac3aaa32627f0799dea65e51356b91bfb)  to start recording again after  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387)  is called.

**Returns:**

Returns  **SUCCESS**  if the recording is reset; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Resume\(\)<a name="gafd32ed157821800936a258a73af936be"></a>

```
int32_t OHOS::Media::Recorder::Resume ()
```

 **Description:**

Resumes recording. 

You can call this function to resume recording after  [Pause](multimedia_recorder.md#ga71da5cc2720b336f0daadbe09d61c695)  is called.

**Returns:**

Returns  **SUCCESS**  if the recording is resumed; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetAudioChannels\(\)<a name="ga77d76e5657cb3359e85521e08a456c7d"></a>

```
int32_t OHOS::Media::Recorder::SetAudioChannels (int32_t sourceId, int32_t num )
```

 **Description:**

Sets the number of audio channels to record. 

This function must be called after  [SetAudioSource](multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table1402988510093523"></a>
<table><thead align="left"><tr id="row1686511852093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p664707833093523"><a name="p664707833093523"></a><a name="p664707833093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1087257130093523"><a name="p1087257130093523"></a><a name="p1087257130093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1635462250093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio source ID, which can be obtained from <a href="multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a">SetAudioSource</a>. </td>
</tr>
<tr id="row2132087717093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">num</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of audio channels to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetAudioEncoder\(\)<a name="gab37c9385fa1a56f686beb73c7dcc1b1b"></a>

```
int32_t OHOS::Media::Recorder::SetAudioEncoder (int32_t sourceId, [AudioCodecFormat](multimedia_mediacommon.md#gaa4ea6f314644ed287e0704be26c768b7) encoder )
```

 **Description:**

Sets an audio encoder for recording. 

If this function is not called, the output file does not contain the audio track. This function must be called after  [SetAudioSource](multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387). 

**Parameters:**

<a name="table1910870560093523"></a>
<table><thead align="left"><tr id="row740841607093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1277783970093523"><a name="p1277783970093523"></a><a name="p1277783970093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p728407760093523"><a name="p728407760093523"></a><a name="p728407760093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1444556306093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio source ID, which can be obtained from <a href="multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a">SetAudioSource</a>. </td>
</tr>
<tr id="row1640399120093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">encoder</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio encoder to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetAudioEncodingBitRate\(\)<a name="gac21a1a00c40cf58df84f1ba281b79a36"></a>

```
int32_t OHOS::Media::Recorder::SetAudioEncodingBitRate (int32_t sourceId, int32_t bitRate )
```

 **Description:**

Sets the encoding bit rate of the audio to record. 

This function must be called after  [SetAudioSource](multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table1560855400093523"></a>
<table><thead align="left"><tr id="row1352532493093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p577931526093523"><a name="p577931526093523"></a><a name="p577931526093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1368329758093523"><a name="p1368329758093523"></a><a name="p1368329758093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row805703230093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio source ID, which can be obtained from <a href="multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a">SetAudioSource</a>. </td>
</tr>
<tr id="row356917711093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bitRate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio encoding bit rate, in bit/s. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetAudioSampleRate\(\)<a name="gab2b98616da55ec294053c0c25645c845"></a>

```
int32_t OHOS::Media::Recorder::SetAudioSampleRate (int32_t sourceId, int32_t rate )
```

 **Description:**

Sets the audio sampling rate for recording. 

This function must be called after  [SetAudioSource](multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table161669542093523"></a>
<table><thead align="left"><tr id="row436334477093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p41560066093523"><a name="p41560066093523"></a><a name="p41560066093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2117572107093523"><a name="p2117572107093523"></a><a name="p2117572107093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2137761213093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio source ID, which can be obtained from <a href="multimedia_recorder.md#gae287f59da8b3f1b6ca9f1c0e58a6565a">SetAudioSource</a>. </td>
</tr>
<tr id="row746044201093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the sampling rate of the audio per second. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetAudioSource\(\)<a name="gae287f59da8b3f1b6ca9f1c0e58a6565a"></a>

```
int32_t OHOS::Media::Recorder::SetAudioSource ([AudioSourceType](multimedia_mediacommon.md#gadc3158e093b995ca7b9b6aa32388ccdd) source, int32_t & sourceId )
```

 **Description:**

Sets the audio source for recording. 

If this function is not called, the output file does not contain the audio track.

**Parameters:**

<a name="table2135997880093523"></a>
<table><thead align="left"><tr id="row1750629795093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p384507655093523"><a name="p384507655093523"></a><a name="p384507655093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p310601790093523"><a name="p310601790093523"></a><a name="p310601790093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row32836669093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">source</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio source type. For details, see <a href="multimedia_mediacommon.md#gadc3158e093b995ca7b9b6aa32388ccdd">AudioSourceType</a>. </td>
</tr>
<tr id="row61171699093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the audio source ID. The value <strong id="b625021619093523"><a name="b625021619093523"></a><a name="b625021619093523"></a>-1</strong> indicates an invalid ID and the setting fails. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetCaptureRate\(\)<a name="ga4f4a03fe881f48515874a699118fb84a"></a>

```
int32_t OHOS::Media::Recorder::SetCaptureRate (int32_t sourceId, double fps )
```

 **Description:**

Sets the video capture rate. 

This function must be called after  [SetVideoSource](multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387). It is valid when the video source is YUV or RGB.

**Parameters:**

<a name="table1140739416093523"></a>
<table><thead align="left"><tr id="row792612051093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p771839935093523"><a name="p771839935093523"></a><a name="p771839935093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p575443576093523"><a name="p575443576093523"></a><a name="p575443576093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2005987896093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID, which can be obtained from <a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a>. </td>
</tr>
<tr id="row15655614093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fps</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the rate at which frames are captured per second. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetFileSplitDuration\(\)<a name="ga952ce2fada10d701e38e4ee29139e2af"></a>

```
int32_t OHOS::Media::Recorder::SetFileSplitDuration ([FileSplitType](multimedia_recorder.md#ga8759c7e5a74964a584a716f4ec0b7edb) type, int64_t timestamp, uint32_t duration )
```

 **Description:**

Manually splits a video. 

This function must be called after  [Start](multimedia_recorder.md#gac3aaa32627f0799dea65e51356b91bfb). After this function is called, the file is split based on the manual split type. After the manual split is complete, the initial split type is used. This function can be called again only after  **RECORDER\_INFO\_FILE\_SPLIT\_FINISHED**  is reported.

**Parameters:**

<a name="table1499796811093523"></a>
<table><thead align="left"><tr id="row1077699032093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1036458169093523"><a name="p1036458169093523"></a><a name="p1036458169093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p880872691093523"><a name="p880872691093523"></a><a name="p880872691093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row505665887093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file split type. For details, see <strong id="b758643814093523"><a name="b758643814093523"></a><a name="b758643814093523"></a>FileSplitType</strong>. </td>
</tr>
<tr id="row98495752093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timestamp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file split timestamp. This parameter is not supported currently and can be set to <strong id="b536641529093523"><a name="b536641529093523"></a><a name="b536641529093523"></a>-1</strong>. The recording module splits a file based on the call time. </td>
</tr>
<tr id="row19983381093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">duration</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the duration for splitting the file. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the video is manually split; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetMaxDuration\(\)<a name="gaf2806f0fddd17a3e59eb7c5c740470d6"></a>

```
int32_t OHOS::Media::Recorder::SetMaxDuration (int32_t duration)
```

 **Description:**

Sets the maximum duration of a recorded file, in seconds. 

This method must be called before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387). If the setting is valid,  **RECORDER\_INFO\_MAX\_DURATION\_APPROACHING**  is reported through  **OnInfo**  in the  [RecorderCallback](ohos-media-recordercallback.md)  class when only one second or 10% is left to reach the allowed duration. If the recording output file is set by calling  [SetOutputFile](multimedia_recorder.md#ga500d2bc895852fe292d7397d8450d091), call  [SetNextOutputFile](multimedia_recorder.md#ga8545fe87eb4bd399525e4c5fb414d7cb)  to set the next output file. Otherwise, the current file will be overwritten when the allowed duration is reached. 

**Parameters:**

<a name="table2063335635093523"></a>
<table><thead align="left"><tr id="row1854934959093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1165096509093523"><a name="p1165096509093523"></a><a name="p1165096509093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p140226050093523"><a name="p140226050093523"></a><a name="p140226050093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row810209637093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">duration</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum recording duration to set. If the value is <strong id="b1714191270093523"><a name="b1714191270093523"></a><a name="b1714191270093523"></a>0</strong> or a negative number, a failure message is returned. The default duration is 60s. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetMaxFileSize\(\)<a name="gaeed9ee49d9d1ac1497ec79bf9639c0bc"></a>

```
int32_t OHOS::Media::Recorder::SetMaxFileSize (int64_t size)
```

 **Description:**

Sets the maximum size of a recorded file, in bytes. 

This function must be called before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387). If the setting is valid,  **RECORDER\_INFO\_MAX\_DURATION\_APPROACHING**  is reported through  **OnInfo**  in the  [RecorderCallback](ohos-media-recordercallback.md)  class when only 100 KB or 10% is left to reach the allowed size. If the recording output file is set by calling  [SetOutputFile](multimedia_recorder.md#ga500d2bc895852fe292d7397d8450d091), call  [SetNextOutputFile](multimedia_recorder.md#ga8545fe87eb4bd399525e4c5fb414d7cb)  to set the next output file. Otherwise, when the allowed size is reached, the current file will be overwritten. If  **MaxDuration**  is also set by calling  [SetMaxDuration](multimedia_recorder.md#gaf2806f0fddd17a3e59eb7c5c740470d6),  **MaxDuration**  or  **MaxFileSize**  prevails depending on which of them is first satisfied.

**Parameters:**

<a name="table160565079093523"></a>
<table><thead align="left"><tr id="row1078085092093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p735037982093523"><a name="p735037982093523"></a><a name="p735037982093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p100774930093523"><a name="p100774930093523"></a><a name="p100774930093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2042170376093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum file size to set. If the value is <strong id="b1321256820093523"><a name="b1321256820093523"></a><a name="b1321256820093523"></a>0</strong> or a negative number, a failure message is returned. By default, the maximum size of a single file supported by the current file system is used as the limit. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetNextOutputFile\(\)<a name="ga8545fe87eb4bd399525e4c5fb414d7cb"></a>

```
int32_t OHOS::Media::Recorder::SetNextOutputFile (int32_t fd)
```

 **Description:**

Sets the FD of the next output file. 

If  [SetOutputFile](multimedia_recorder.md#ga500d2bc895852fe292d7397d8450d091)  is successful, call this function to set the FD of the next output file after  **RECORDER\_INFO\_MAX\_DURATION\_APPROACHING**  or  **RECORDER\_INFO\_MAX\_FILESIZE\_APPROACHING**  is received.

**Parameters:**

<a name="table1599300756093523"></a>
<table><thead align="left"><tr id="row2045085927093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1329728947093523"><a name="p1329728947093523"></a><a name="p1329728947093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1419581590093523"><a name="p1419581590093523"></a><a name="p1419581590093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1717288422093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the FD of the next output file. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetOutputFile\(\)<a name="ga500d2bc895852fe292d7397d8450d091"></a>

```
int32_t OHOS::Media::Recorder::SetOutputFile (int32_t fd)
```

 **Description:**

Sets the file descriptor \(FD\) of the output file. 

This function must be called before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table1163095908093523"></a>
<table><thead align="left"><tr id="row503903268093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p190854775093523"><a name="p190854775093523"></a><a name="p190854775093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p250561632093523"><a name="p250561632093523"></a><a name="p250561632093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1577726309093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the FD of the file. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetOutputFormat\(\)<a name="gaffb7874aae331570ecedfe609a495468"></a>

```
int32_t OHOS::Media::Recorder::SetOutputFormat ([OutputFormatType](multimedia_recorder.md#ga3dfe2e61369bf1c081ce569e235354df) format)
```

 **Description:**

Sets the output file format. 

This function must be called before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table156791511093523"></a>
<table><thead align="left"><tr id="row1121026112093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2047003265093523"><a name="p2047003265093523"></a><a name="p2047003265093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p428555169093523"><a name="p428555169093523"></a><a name="p428555169093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1373044642093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">format</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the output file format. For details, see <strong id="b763665464093523"><a name="b763665464093523"></a><a name="b763665464093523"></a>OutputFormatType</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetOutputPath\(\)<a name="gaa5c898c1ad051b5c9f115ef15d952f18"></a>

```
int32_t OHOS::Media::Recorder::SetOutputPath (const string & path)
```

 **Description:**

Sets the output file path. 

This function must be called before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387)  and One of them  [SetOutputFile](multimedia_recorder.md#ga500d2bc895852fe292d7397d8450d091)  must be set.

**Parameters:**

<a name="table1381039281093523"></a>
<table><thead align="left"><tr id="row135672177093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2128402025093523"><a name="p2128402025093523"></a><a name="p2128402025093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p155107033093523"><a name="p155107033093523"></a><a name="p155107033093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row157074724093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the output file path. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetParameter\(\)<a name="ga05cf279a460418b22d267527c83ede15"></a>

```
int32_t OHOS::Media::Recorder::SetParameter (int32_t sourceId, const [Format](ohos-media-format.md) & format )
```

 **Description:**

Sets an extended parameter for recording, for example,  **RCORDER\_PRE\_CACHE\_DURATION**. 

**Parameters:**

<a name="table907234352093523"></a>
<table><thead align="left"><tr id="row2104769426093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p644415179093523"><a name="p644415179093523"></a><a name="p644415179093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1753167234093523"><a name="p1753167234093523"></a><a name="p1753167234093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1964450030093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data source ID. The value <strong id="b2129905607093523"><a name="b2129905607093523"></a><a name="b2129905607093523"></a>-1</strong> indicates all sources. </td>
</tr>
<tr id="row1669866038093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">format</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the string key and value. For details, see <a href="ohos-media-format.md">Format</a> and <strong id="b1165557306093523"><a name="b1165557306093523"></a><a name="b1165557306093523"></a>RCORDER_PRE_CACHE_DURATION</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetRecorderCallback\(\)<a name="ga882585460b0538680954ce6692610376"></a>

```
int32_t OHOS::Media::Recorder::SetRecorderCallback (const std::shared_ptr< [RecorderCallback](ohos-media-recordercallback.md) > & callback)
```

 **Description:**

Registers a recording listener. 

This function must be called before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table930505404093523"></a>
<table><thead align="left"><tr id="row746978212093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p634360728093523"><a name="p634360728093523"></a><a name="p634360728093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p250759816093523"><a name="p250759816093523"></a><a name="p250759816093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row145509120093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">callback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the recording listener to register. For details, see <a href="ohos-media-recordercallback.md">RecorderCallback</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the listener is registered; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetVideoEncoder\(\)<a name="gad9be6914af57fcf7acb7a5398118c614"></a>

```
int32_t OHOS::Media::Recorder::SetVideoEncoder (int32_t sourceId, [VideoCodecFormat](multimedia_mediacommon.md#ga797e6c5e38e23e730eff5bcc41427d7e) encoder )
```

 **Description:**

Sets a video encoder for recording. 

If this function is not called, the output file does not contain the video track. This function must be called after  [SetVideoSource](multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387). 

**Parameters:**

<a name="table1101313537093523"></a>
<table><thead align="left"><tr id="row967941843093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1660095126093523"><a name="p1660095126093523"></a><a name="p1660095126093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1561263200093523"><a name="p1561263200093523"></a><a name="p1561263200093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row11419313093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID, which can be obtained from <a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a>. </td>
</tr>
<tr id="row755126316093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">encoder</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video encoder to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetVideoEncodingBitRate\(\)<a name="ga4e05a76b50abf790f29f06a0c1d4ecb8"></a>

```
int32_t OHOS::Media::Recorder::SetVideoEncodingBitRate (int32_t sourceId, int32_t rate )
```

 **Description:**

Sets the encoding bit rate of the video to record. 

This function must be called after  [SetVideoSource](multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table1985947301093523"></a>
<table><thead align="left"><tr id="row1664726315093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1322866001093523"><a name="p1322866001093523"></a><a name="p1322866001093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p612793453093523"><a name="p612793453093523"></a><a name="p612793453093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2105995456093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID, which can be obtained from <a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a>. </td>
</tr>
<tr id="row1693311128093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the encoding bit rate to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetVideoFrameRate\(\)<a name="gaeb90d4d75d80040aeaae354abd1d29d7"></a>

```
int32_t OHOS::Media::Recorder::SetVideoFrameRate (int32_t sourceId, int32_t frameRate )
```

 **Description:**

Sets the frame rate of the video to record. 

This function must be called after  [SetVideoSource](multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table1594010924093523"></a>
<table><thead align="left"><tr id="row479381084093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1466951526093523"><a name="p1466951526093523"></a><a name="p1466951526093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p146326872093523"><a name="p146326872093523"></a><a name="p146326872093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2124305265093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID, which can be obtained from <a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a>. </td>
</tr>
<tr id="row548510772093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameRate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frame rate to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetVideoSize\(\)<a name="ga43c0ee5b76f58a12c2c745839184a96b"></a>

```
int32_t OHOS::Media::Recorder::SetVideoSize (int32_t sourceId, int32_t width, int32_t height )
```

 **Description:**

Sets the width and height of the video to record. 

This function must be called after  [SetVideoSource](multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca)  but before  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Parameters:**

<a name="table1020779248093523"></a>
<table><thead align="left"><tr id="row1906190270093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1310344516093523"><a name="p1310344516093523"></a><a name="p1310344516093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1346001596093523"><a name="p1346001596093523"></a><a name="p1346001596093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1462903783093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID, which can be obtained from <a href="multimedia_recorder.md#ga9e12ef9700d06c7620f9e3d7b4d844ca">SetVideoSource</a>. </td>
</tr>
<tr id="row389006095093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">width</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video width to set. </td>
</tr>
<tr id="row1307566025093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">height</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video height to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## SetVideoSource\(\)<a name="ga9e12ef9700d06c7620f9e3d7b4d844ca"></a>

```
int32_t OHOS::Media::Recorder::SetVideoSource ([VideoSourceType](multimedia_recorder.md#gad252d27f9ce4b6ae0756bfeaa5f34490) source, int32_t & sourceId )
```

 **Description:**

Sets a video source for recording. 

If this function is not called, the output file does not contain the video track.

**Parameters:**

<a name="table1884815916093523"></a>
<table><thead align="left"><tr id="row1191240458093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p386918077093523"><a name="p386918077093523"></a><a name="p386918077093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p355804425093523"><a name="p355804425093523"></a><a name="p355804425093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2020819680093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">source</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source type. For details, see <strong id="b1476985677093523"><a name="b1476985677093523"></a><a name="b1476985677093523"></a>VideoSourceType</strong>. </td>
</tr>
<tr id="row1340469496093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sourceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video source ID. The value <strong id="b1216175675093523"><a name="b1216175675093523"></a><a name="b1216175675093523"></a>-1</strong> indicates an invalid ID and the setting fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the setting is successful; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Start\(\)<a name="gac3aaa32627f0799dea65e51356b91bfb"></a>

```
int32_t OHOS::Media::Recorder::Start ()
```

 **Description:**

Starts recording. 

This function must be called after  [Prepare](multimedia_recorder.md#ga15d2f3416bb735a0715e1e79be226387).

**Returns:**

Returns  **SUCCESS**  if the recording is started; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## Stop\(\)<a name="ga1253f753cf9ed01dae5d57a37524dfa7"></a>

```
int32_t OHOS::Media::Recorder::Stop (bool block)
```

 **Description:**

Stops recording. 

**Parameters:**

<a name="table441629329093523"></a>
<table><thead align="left"><tr id="row2130562099093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1182862657093523"><a name="p1182862657093523"></a><a name="p1182862657093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2087437999093523"><a name="p2087437999093523"></a><a name="p2087437999093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1146062334093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">block</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the stop mode. The value <strong id="b354826720093523"><a name="b354826720093523"></a><a name="b354826720093523"></a>true</strong> indicates that the processing stops after all caches are processed, and <strong id="b1626112309093523"><a name="b1626112309093523"></a><a name="b1626112309093523"></a>false</strong> indicates that the processing stops immediately and all caches are discarded. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **SUCCESS**  if the recording is stopped; returns an error code defined in  [media\_errors.h](media_errors-h.md)  otherwise. 



## **Variable Documentation**<a name="section1323764135093523"></a>

## RCORDER\_PRE\_CACHE\_DURATION<a name="gaaa77dd5c1745b9d5ba4b23c90206e936"></a>

```
const string OHOS::Media::RCORDER_PRE_CACHE_DURATION = "pre-cache-duration"
```

 **Description:**

This constant can be used as the value of  [Format](ohos-media-format.md)  in  [SetParameter](parameter.md#ga2779b5e59d43308c51f7be38b9c98ddb)  to configure the duration for storing recorded data in the cache. 

